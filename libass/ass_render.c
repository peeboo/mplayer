// -*- c-basic-offset: 8; indent-tabs-mode: t -*-
// vim:ts=8:sw=8:noet:ai:
/*
  Copyright (C) 2006 Evgeniy Stepanov <eugeni.stepanov@gmail.com>

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
*/

#include "config.h"

#include <assert.h>
#include <math.h>
#include <inttypes.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_STROKER_H
#include FT_GLYPH_H
#include FT_SYNTHESIS_H

#include "mp_msg.h"

#include "ass.h"
#include "ass_bitmap.h"
#include "ass_cache.h"
#include "ass_utils.h"
#include "ass_fontconfig.h"

#include "libvo/sub.h" // for utf8_get_char

#define MAX_GLYPHS 1000
#define MAX_LINES 100

char *get_path(char *);

extern char *font_name;
#ifdef HAVE_FONTCONFIG
extern int font_fontconfig;
#else
static int font_fontconfig = 0;
#endif

static int last_render_id = 0;

struct ass_instance_s {
	FT_Library library;
	fc_instance_t* fontconfig_priv;
	ass_settings_t settings;
	int render_id;
	ass_synth_priv_t* synth_priv;

	ass_image_t* images_root; // rendering result is stored here
};

int no_more_font_messages = 0;  // don't print font warnings

typedef enum {EF_NONE = 0, EF_KARAOKE, EF_KARAOKE_KF, EF_KARAOKE_KO} effect_t;

// describes a glyph
// glyph_info_t and text_info_t are used for text centering and word-wrapping operations
typedef struct glyph_info_s {
	unsigned symbol;
	FT_Glyph glyph;
	FT_Glyph outline_glyph;
	bitmap_t* bm; // glyph bitmap
	bitmap_t* bm_o; // outline bitmap
	bitmap_t* bm_s; // shadow bitmap
	FT_BBox bbox;
	FT_Vector pos;
	char linebreak; // the first (leading) glyph of some line ?
	uint32_t c[4]; // colors
	FT_Vector advance; // 26.6
	effect_t effect_type;
	int effect_timing; // time duration of current karaoke word
	                   // after process_karaoke_effects: distance in pixels from the glyph origin.
	                   // part of the glyph to the left of it is displayed in a different color.
	int effect_skip_timing; // delay after the end of last karaoke word
	int asc, desc; // font max ascender and descender
//	int height;
	int be; // blur edges
	int shadow;
	
	glyph_hash_key_t hash_key;
} glyph_info_t;

typedef struct line_info_s {
	int asc, desc;
} line_info_t;

typedef struct text_info_s {
	glyph_info_t* glyphs;
	int length;
	line_info_t lines[MAX_LINES];
	int n_lines;
	int height;
} text_info_t;


// Renderer state.
// Values like current font face, color, screen position, clipping and so on are stored here.
typedef struct render_context_s {
	ass_event_t* event;
	ass_style_t* style;
	
	FT_Face face;
	char* font_path;
	int font_size;
	
	FT_Stroker stroker;
	int alignment; // alignment overrides go here; if zero, style value will be used
	double rotation;
	enum {	EVENT_NORMAL, // "normal" top-, sub- or mid- title
		EVENT_POSITIONED, // happens after pos(,), margins are ignored
		EVENT_HSCROLL, // "Banner" transition effect, text_width is unlimited
		EVENT_VSCROLL // "Scroll up", "Scroll down" transition effects
		} evt_type;
	int pos_x, pos_y; // position
	int org_x, org_y; // origin
	double scale_x, scale_y;
	int hspacing; // distance between letters, in pixels
	double border; // outline width
	uint32_t c[4]; // colors(Primary, Secondary, so on) in RGBA
	int clip_x0, clip_y0, clip_x1, clip_y1;
	char detect_collisions;
	uint32_t fade; // alpha from \fad
	char be; // blur edges
	int shadow;

	effect_t effect_type;
	int effect_timing;
	int effect_skip_timing;

	enum { SCROLL_LR, // left-to-right
	       SCROLL_RL,
	       SCROLL_TB, // top-to-bottom
	       SCROLL_BT
	       } scroll_direction; // for EVENT_HSCROLL, EVENT_VSCROLL
	int scroll_shift;

	// face properties
	char* family;
	unsigned bold;
	unsigned italic;
	
} render_context_t;

// frame-global data
typedef struct frame_context_s {
	ass_instance_t* ass_priv;
	int width, height; // screen dimensions
	int orig_height; // frame height ( = screen height - margins )
	int orig_width; // frame width ( = screen width - margins )
	ass_track_t* track;
	long long time; // frame's timestamp, ms
	double font_scale;
	double font_scale_x; // x scale applied to all glyphs to preserve text aspect ratio
	double border_scale;
} frame_context_t;

static ass_instance_t* ass_instance;
static ass_settings_t* global_settings;
static text_info_t text_info;
static render_context_t render_context;
static frame_context_t frame_context;

// a rendered event
typedef struct event_images_s {
	ass_image_t* imgs;
	int top, height;
	int detect_collisions;
	int shift_direction;
	ass_event_t* event;
} event_images_t;

struct render_priv_s {
	int top, height;
	int render_id;
};

static void ass_lazy_track_init(void)
{
	ass_track_t* track = frame_context.track;
	if (track->PlayResX && track->PlayResY)
		return;
	if (!track->PlayResX && !track->PlayResY) {
		mp_msg(MSGT_GLOBAL, MSGL_WARN, "Neither PlayResX nor PlayResY defined. Assuming 384x288.  \n");
		track->PlayResX = 384;
		track->PlayResY = 288;
	} else {
		double orig_aspect = (global_settings->aspect * frame_context.height * frame_context.orig_width) /
			frame_context.orig_height / frame_context.width;
		if (!track->PlayResY) {
			track->PlayResY = track->PlayResX / orig_aspect + .5;
			mp_msg(MSGT_GLOBAL, MSGL_WARN, "PlayResY undefined, setting %d  \n", track->PlayResY);
		} else if (!track->PlayResX) {
			track->PlayResX = track->PlayResY * orig_aspect + .5;
			mp_msg(MSGT_GLOBAL, MSGL_WARN, "PlayResX undefined, setting %d  \n", track->PlayResX);
		}
	}
}

ass_instance_t* ass_init(void)
{
	char* family = 0;
	char* path = 0;
	char* fonts_path = 0;
	int error;
	fc_instance_t* fc_priv;
	FT_Library ft;
	ass_instance_t* priv = 0;
	
	memset(&render_context, 0, sizeof(render_context));
	memset(&frame_context, 0, sizeof(frame_context));
	memset(&text_info, 0, sizeof(text_info));

	if (font_fontconfig && font_name)
		family = strdup(font_name);
	
	if (!font_fontconfig && font_name)
		path = strdup(font_name);
	else
		path = get_path("subfont.ttf");

	fonts_path = get_path("fonts");
	
	fc_priv = fontconfig_init(fonts_path, family, path);

	free(fonts_path);
	if (path) free(path);
	if (family) free(family);

	if (!fc_priv)
		goto ass_init_exit;
	
	error = FT_Init_FreeType( &ft );
	if ( error ) { 
		mp_msg(MSGT_GLOBAL, MSGL_FATAL, "FT_Init_FreeType failed\n");
		fontconfig_done(fc_priv);
		goto ass_init_exit;
	}

	priv = calloc(1, sizeof(ass_instance_t));
	if (!priv) {
		FT_Done_FreeType(ft);
		fontconfig_done(fc_priv);
		goto ass_init_exit;
	}

	priv->synth_priv = ass_synth_init();

	priv->library = ft;
	priv->fontconfig_priv = fc_priv;
	// images_root and related stuff is zero-filled in calloc
	
	ass_face_cache_init();
	ass_glyph_cache_init();

	text_info.glyphs = calloc(MAX_GLYPHS, sizeof(glyph_info_t));
	
ass_init_exit:
	if (priv) mp_msg(MSGT_GLOBAL, MSGL_INFO, "[ass] Init\n");
	else mp_msg(MSGT_GLOBAL, MSGL_ERR, "[ass] Init failed\n");

	return priv;
}

void ass_done(ass_instance_t* priv)
{
	ass_face_cache_done();
	ass_glyph_cache_done();
	if (render_context.stroker) {
		FT_Stroker_Done(render_context.stroker);
		render_context.stroker = 0;
	}
	if (priv && priv->library) FT_Done_FreeType(priv->library);
	if (priv && priv->fontconfig_priv) fontconfig_done(priv->fontconfig_priv);
	if (priv && priv->synth_priv) ass_synth_done(priv->synth_priv);
	if (priv) free(priv);
	if (text_info.glyphs) free(text_info.glyphs);
}

/**
 * \brief Create a new ass_image_t
 * Parameters are the same as ass_image_t fields.
 */
static ass_image_t* my_draw_bitmap(unsigned char* bitmap, int bitmap_w, int bitmap_h, int stride, int dst_x, int dst_y, uint32_t color)
{
	ass_image_t* img = calloc(1, sizeof(ass_image_t));
	
	img->w = bitmap_w;
	img->h = bitmap_h;
	img->stride = stride;
	img->bitmap = bitmap;
	img->color = color;
	img->dst_x = dst_x;
	img->dst_y = dst_y;

	return img;
}

/**
 * \brief convert bitmap glyph into ass_image_t struct(s)
 * \param bit freetype bitmap glyph, FT_PIXEL_MODE_GRAY
 * \param dst_x bitmap x coordinate in video frame
 * \param dst_y bitmap y coordinate in video frame
 * \param color first color, RGBA
 * \param color2 second color, RGBA
 * \param brk x coordinate relative to glyph origin, color is used to the left of brk, color2 - to the right
 * \param tail pointer to the last image's next field, head of the generated list should be stored here
 * \return pointer to the new list tail
 * Performs clipping. Uses my_draw_bitmap for actual bitmap convertion.
 */
static ass_image_t** render_glyph(bitmap_t* bm, int dst_x, int dst_y, uint32_t color, uint32_t color2, int brk, ass_image_t** tail)
{
	// brk is relative to dst_x
	// color = color left of brk
	// color2 = color right of brk
	int b_x0, b_y0, b_x1, b_y1; // visible part of the bitmap
	int clip_x0, clip_y0, clip_x1, clip_y1;
	int tmp;
	ass_image_t* img;

	dst_x += bm->left;
	dst_y += bm->top;
	brk -= bm->left;
	
	// clipping
	clip_x0 = render_context.clip_x0;
	clip_y0 = render_context.clip_y0;
	clip_x1 = render_context.clip_x1;
	clip_y1 = render_context.clip_y1;
	b_x0 = 0;
	b_y0 = 0;
	b_x1 = bm->w;
	b_y1 = bm->h;
	
	tmp = dst_x - clip_x0;
	if (tmp < 0) {
		mp_msg(MSGT_GLOBAL, MSGL_DBG2, "clip left\n");
		b_x0 = - tmp;
	}
	tmp = dst_y - clip_y0;
	if (tmp < 0) {
		mp_msg(MSGT_GLOBAL, MSGL_DBG2, "clip top\n");
		b_y0 = - tmp;
	}
	tmp = clip_x1 - dst_x - bm->w;
	if (tmp < 0) {
		mp_msg(MSGT_GLOBAL, MSGL_DBG2, "clip right\n");
		b_x1 = bm->w + tmp;
	}
	tmp = clip_y1 - dst_y - bm->h;
	if (tmp < 0) {
		mp_msg(MSGT_GLOBAL, MSGL_DBG2, "clip bottom\n");
		b_y1 = bm->h + tmp;
	}
	
	if ((b_y0 >= b_y1) || (b_x0 >= b_x1))
		return tail;

	if (brk > b_x0) { // draw left part
		if (brk > b_x1) brk = b_x1;
		img = my_draw_bitmap(bm->buffer + bm->w * b_y0 + b_x0, 
			brk - b_x0, b_y1 - b_y0, bm->w,
			dst_x + b_x0, dst_y + b_y0, color);
		*tail = img;
		tail = &img->next;
	}
	if (brk < b_x1) { // draw right part
		if (brk < b_x0) brk = b_x0;
		img = my_draw_bitmap(bm->buffer + bm->w * b_y0 + brk, 
			b_x1 - brk, b_y1 - b_y0, bm->w,
			dst_x + brk, dst_y + b_y0, color2);
		*tail = img;
		tail = &img->next;
	}
	return tail;
}

/**
 * \brief Render text_info_t struct into ass_images_t list
 * Rasterize glyphs and put them in glyph cache.
 */
static ass_image_t* render_text(text_info_t* text_info, int dst_x, int dst_y)
{
	int pen_x, pen_y;
	int i, error;
	bitmap_t* bm;
	glyph_hash_val_t hash_val;
	ass_image_t* head;
	ass_image_t** tail = &head;

	for (i = 0; i < text_info->length; ++i) {
		if (text_info->glyphs[i].glyph) {
			if ((text_info->glyphs[i].symbol == '\n') || (text_info->glyphs[i].symbol == 0))
				continue;
			error = glyph_to_bitmap(ass_instance->synth_priv,
					text_info->glyphs[i].glyph, text_info->glyphs[i].outline_glyph,
					&text_info->glyphs[i].bm, &text_info->glyphs[i].bm_o,
					&text_info->glyphs[i].bm_s, text_info->glyphs[i].be);
			if (error)
				text_info->glyphs[i].symbol = 0;
			FT_Done_Glyph(text_info->glyphs[i].glyph);
			if (text_info->glyphs[i].outline_glyph)
				FT_Done_Glyph(text_info->glyphs[i].outline_glyph);

			// cache
			hash_val.bbox_scaled = text_info->glyphs[i].bbox;
			hash_val.bm_o = text_info->glyphs[i].bm_o;
			hash_val.bm = text_info->glyphs[i].bm;
			hash_val.bm_s = text_info->glyphs[i].bm_s;
			hash_val.advance.x = text_info->glyphs[i].advance.x;
			hash_val.advance.y = text_info->glyphs[i].advance.y;
			cache_add_glyph(&(text_info->glyphs[i].hash_key), &hash_val);

		}
	}

	for (i = 0; i < text_info->length; ++i) {
		glyph_info_t* info = text_info->glyphs + i;
		if ((info->symbol == 0) || (info->symbol == '\n') || !info->bm_s || (info->shadow == 0))
			continue;

		pen_x = dst_x + info->pos.x + info->shadow;
		pen_y = dst_y + info->pos.y + info->shadow;
		bm = info->bm_s;

		tail = render_glyph(bm, pen_x, pen_y, info->c[3], 0, 1000000, tail);
	}

	for (i = 0; i < text_info->length; ++i) {
		glyph_info_t* info = text_info->glyphs + i;
		if ((info->symbol == 0) || (info->symbol == '\n') || !info->bm_o)
			continue;

		pen_x = dst_x + info->pos.x;
		pen_y = dst_y + info->pos.y;
		bm = info->bm_o;
		
		if ((info->effect_type == EF_KARAOKE_KO) && (info->effect_timing <= info->bbox.xMax)) {
			// do nothing
		} else
			tail = render_glyph(bm, pen_x, pen_y, info->c[2], 0, 1000000, tail);
	}
	for (i = 0; i < text_info->length; ++i) {
		glyph_info_t* info = text_info->glyphs + i;
		if ((info->symbol == 0) || (info->symbol == '\n') || !info->bm)
			continue;

		pen_x = dst_x + info->pos.x;
		pen_y = dst_y + info->pos.y;
		bm = info->bm;

		if ((info->effect_type == EF_KARAOKE) || (info->effect_type == EF_KARAOKE_KO)) {
			if (info->effect_timing > info->bbox.xMax)
				tail = render_glyph(bm, pen_x, pen_y, info->c[0], 0, 1000000, tail);
			else
				tail = render_glyph(bm, pen_x, pen_y, info->c[1], 0, 1000000, tail);
		} else if (info->effect_type == EF_KARAOKE_KF) {
			tail = render_glyph(bm, pen_x, pen_y, info->c[0], info->c[1], info->effect_timing, tail);
		} else
			tail = render_glyph(bm, pen_x, pen_y, info->c[0], 0, 1000000, tail);
	}

	*tail = 0;
	return head;
}

/**
 * \brief Mapping between script and screen coordinates
 */
static int x2scr(int x) {
	return x*frame_context.orig_width / frame_context.track->PlayResX + global_settings->left_margin;
}
/**
 * \brief Mapping between script and screen coordinates
 */
static int y2scr(int y) {
	return y * frame_context.orig_height / frame_context.track->PlayResY + global_settings->top_margin;
}
// the same for toptitles
static int y2scr_top(int y) {
	if (global_settings->use_margins)
		return y * frame_context.orig_height / frame_context.track->PlayResY;
	else
		return y * frame_context.orig_height / frame_context.track->PlayResY + global_settings->top_margin;
}
// the same for subtitles
static int y2scr_sub(int y) {
	if (global_settings->use_margins)
		return y * frame_context.orig_height / frame_context.track->PlayResY +
		       global_settings->top_margin + global_settings->bottom_margin;
	else
		return y * frame_context.orig_height / frame_context.track->PlayResY + global_settings->top_margin;
}

static void vmirror_bbox(FT_BBox* orig, FT_BBox* pbbox) {
	pbbox->xMin = orig->xMin;
	pbbox->xMax = orig->xMax;
	pbbox->yMin = - orig->yMax;
	pbbox->yMax = - orig->yMin;
}

static void compute_string_bbox( text_info_t* info, FT_BBox *abbox ) {
	FT_BBox bbox;
	int n;
	
	/* initialize string bbox to "empty" values */
	bbox.xMin = bbox.yMin = 32000;
	bbox.xMax = bbox.yMax = -32000;
	
	/* for each glyph image, compute its bounding box, */
	/* translate it, and grow the string bbox */
	for ( n = 0; n < info->length; n++ ) {
		FT_BBox glyph_bbox;
		vmirror_bbox( &(info->glyphs[n].bbox), &glyph_bbox );
		glyph_bbox.xMin += info->glyphs[n].pos.x;
		glyph_bbox.xMax += info->glyphs[n].pos.x;
		glyph_bbox.yMin += info->glyphs[n].pos.y;
		glyph_bbox.yMax += info->glyphs[n].pos.y;
		if ( glyph_bbox.xMin < bbox.xMin ) bbox.xMin = glyph_bbox.xMin;
		if ( glyph_bbox.yMin < bbox.yMin ) bbox.yMin = glyph_bbox.yMin;
		if ( glyph_bbox.xMax > bbox.xMax ) bbox.xMax = glyph_bbox.xMax;
		if ( glyph_bbox.yMax > bbox.yMax ) bbox.yMax = glyph_bbox.yMax;
	}
	
	/* check that we really grew the string bbox */
	if ( bbox.xMin > bbox.xMax ) {
		bbox.xMin = 0;
		bbox.yMin = 0;
		bbox.xMax = 0;
		bbox.yMax = 0;
	}

	/* return string bbox */
	*abbox = bbox;
}


/**
 * \brief Check if starting part of (*p) matches sample. If true, shift p to the first symbol after the matching part.
 */
static inline int mystrcmp(char** p, const char* sample) {
	int len = strlen(sample);
	if (strncmp(*p, sample, len) == 0) {
		(*p) += len;
		return 1;
	} else
		return 0;
}

double ass_internal_font_size_coeff = 0.8;

static void change_font_size(int sz)
{
	double size = sz * frame_context.font_scale;

	if (size < 1)
		size = 1;
	else if (size > frame_context.height * 2)
		size = frame_context.height * 2;
	
	FT_Set_Pixel_Sizes(render_context.face, 0, size);

	render_context.font_size = sz;
}

/**
 * \brief Change current font, using setting from render_context.
 */
static void update_font(void)
{
	int error;
	unsigned val;
	ass_instance_t* priv = frame_context.ass_priv;
	face_desc_t desc;
	desc.family = strdup(render_context.family);

	val = render_context.bold;
	// 0 = normal, 1 = bold, >1 = exact weight
	if (val == 0) val = 80; // normal
	else if (val == 1) val = 200; // bold
	desc.bold = val;

	val = render_context.italic;
	if (val == 0) val = 0; // normal
	else if (val == 1) val = 110; //italic
	desc.italic = val;

	error = ass_new_face(priv->library, priv->fontconfig_priv, &desc, &(render_context.face));
	if (error) {
		render_context.face = 0;
	}
	
	if (render_context.face)
		change_font_size(render_context.font_size);
}

/**
 * \brief Change border width
 * negative value resets border to style value
 */
static void change_border(double border)
{
	int b;
	if (!render_context.face) return;

	if (border < 0) {
		if (render_context.style->BorderStyle == 1) {
			if (render_context.style->Outline == 0 && render_context.style->Shadow > 0)
				border = 1.;
			else
				border = render_context.style->Outline;
		} else
			border = 1.;
	}
	render_context.border = border;

	b = 64 * border * frame_context.border_scale;
	if (b > 0) {
		if (!render_context.stroker) {
			int error;
#if (FREETYPE_MAJOR > 2) || ((FREETYPE_MAJOR == 2) && (FREETYPE_MINOR > 1))
			error = FT_Stroker_New( ass_instance->library, &render_context.stroker );
#else // < 2.2
			error = FT_Stroker_New( render_context.face->memory, &render_context.stroker );
#endif
			if (error) {
				mp_msg(MSGT_GLOBAL, MSGL_V, "failed to get stroker\n");
				render_context.stroker = 0;
			}
		}
		if (render_context.stroker)
			FT_Stroker_Set( render_context.stroker, b,
					FT_STROKER_LINECAP_ROUND,
					FT_STROKER_LINEJOIN_ROUND,
					0 );
	} else {
		FT_Stroker_Done(render_context.stroker);
		render_context.stroker = 0;
	}
}

#define _r(c)  ((c)>>24)
#define _g(c)  (((c)>>16)&0xFF)
#define _b(c)  (((c)>>8)&0xFF)
#define _a(c)  ((c)&0xFF)

/**
 * \brief Calculate a weighted average of two colors
 * calculates c1*(1-a) + c2*a, but separately for each component except alpha
 */
static void change_color(uint32_t* var, uint32_t new, double pwr)
{
	(*var)= ((uint32_t)(_r(*var) * (1 - pwr) + _r(new) * pwr) << 24) +
		((uint32_t)(_g(*var) * (1 - pwr) + _g(new) * pwr) << 16) +
		((uint32_t)(_b(*var) * (1 - pwr) + _b(new) * pwr) << 8) +
		_a(*var);
}

// like change_color, but for alpha component only
static void change_alpha(uint32_t* var, uint32_t new, double pwr)
{
	*var = (_r(*var) << 24) + (_g(*var) << 16) + (_b(*var) << 8) + (_a(*var) * (1 - pwr) + _a(new) * pwr);
}

/**
 * \brief Multiply two alpha values
 * \param a first value
 * \param b second value
 * \return result of multiplication
 * Parameters and result are limited by 0xFF.
 */
static uint32_t mult_alpha(uint32_t a, uint32_t b)
{
	return 0xFF - (0xFF - a) * (0xFF - b) / 0xFF;
}

/**
 * \brief Calculate alpha value by piecewise linear function
 * Used for \fad, \fade implementation.
 */
static unsigned interpolate_alpha(long long now, 
		long long t1, long long t2, long long t3, long long t4,
		unsigned a1, unsigned a2, unsigned a3)
{
	unsigned a;
	double cf;
	if (now <= t1) {
		a = a1;
	} else if (now >= t4) {
		a = a3;
	} else if (now < t2) { // and > t1
		cf = ((double)(now - t1)) / (t2 - t1);
		a = a1 * (1 - cf) + a2 * cf;
	} else if (now > t3) {
		cf = ((double)(now - t3)) / (t4 - t3);
		a = a2 * (1 - cf) + a3 * cf;
	} else { // t2 <= now <= t3
		a = a2;
	}

	return a;
}

static void reset_render_context();

/**
 * \brief Parse style override tag.
 * \param p string to parse
 * \param pwr multiplier for some tag effects (comes from \t tags)
 */
static char* parse_tag(char* p, double pwr) {
#define skip_all(x) if (*p == (x)) ++p; else { \
	while ((*p != (x)) && (*p != '}') && (*p != 0)) {++p;} }
#define skip(x) if (*p == (x)) ++p; else { return p; }
	
	skip_all('\\');
	if ((*p == '}') || (*p == 0))
		return p;

	if (mystrcmp(&p, "fsc")) {
		char tp = *p++;
		double val;
		if (tp == 'x') {
			if (mystrtod(&p, &val)) {
				val /= 100;
				render_context.scale_x = (val - 1.) * pwr + 1.;
			} else
				render_context.scale_x = render_context.style->ScaleX;
		} else if (tp == 'y') {
			if (mystrtod(&p, &val)) {
				val /= 100;
				render_context.scale_y = (val - 1.) * pwr + 1.;
			} else
				render_context.scale_y = render_context.style->ScaleY;
		}
	} else if (mystrcmp(&p, "fsp")) {
		int val;
		if (mystrtoi(&p, 10, &val))
			render_context.hspacing = val * pwr;
		else
			render_context.hspacing = 0;
	} else if (mystrcmp(&p, "fs")) {
		int val;
		if (mystrtoi(&p, 10, &val))
			val = render_context.font_size * ( 1 - pwr ) + val * pwr;
		else
			val = render_context.style->FontSize;
		if (render_context.face)
			change_font_size(val);
	} else if (mystrcmp(&p, "bord")) {
		double val;
		if (mystrtod(&p, &val))
			val = render_context.border * ( 1 - pwr ) + val * pwr;
		else
			val = -1.; // reset to default
		change_border(val);
	} else if (mystrcmp(&p, "move")) {
		int x1, x2, y1, y2;
		long long t1, t2, delta_t, t;
		int x, y;
		double k;
		skip('(');
		x1 = strtol(p, &p, 10);
		skip(',');
		y1 = strtol(p, &p, 10);
		skip(',');
		x2 = strtol(p, &p, 10);
		skip(',');
		y2 = strtol(p, &p, 10);
		if (*p == ',') {
			skip(',');
			t1 = strtoll(p, &p, 10);
			skip(',');
			t2 = strtoll(p, &p, 10);
			mp_msg(MSGT_GLOBAL, MSGL_DBG2, "movement6: (%d, %d) -> (%d, %d), (%" PRId64 " .. %" PRId64 ")\n", 
				x1, y1, x2, y2, (int64_t)t1, (int64_t)t2);
		} else {
			t1 = 0;
			t2 = render_context.event->Duration;
			mp_msg(MSGT_GLOBAL, MSGL_DBG2, "movement: (%d, %d) -> (%d, %d)\n", x1, y1, x2, y2);
		}
		skip(')');
		delta_t = t2 - t1;
		t = frame_context.time - render_context.event->Start;
		if (t < t1)
			k = 0.;
		else if (t > t2)
			k = 1.;
		else k = ((double)(t - t1)) / delta_t;
		x = k * (x2 - x1) + x1;
		y = k * (y2 - y1) + y1;
		render_context.pos_x = x;
		render_context.pos_y = y;
		render_context.detect_collisions = 0;
		render_context.evt_type = EVENT_POSITIONED;
	} else if (mystrcmp(&p, "frx") || mystrcmp(&p, "fry")) {
		double val;
		mystrtod(&p, &val);
		mp_msg(MSGT_GLOBAL, MSGL_V, "frx/fry unimplemented \n");
	} else if (mystrcmp(&p, "frz") || mystrcmp(&p, "fr")) {
		double angle;
		double val;
		mystrtod(&p, &val);
		mp_msg(MSGT_GLOBAL, MSGL_DBG2, "setting rotation to %.2f\n", val * pwr);
		angle = M_PI * val / 180;
		render_context.rotation = angle * pwr;
	} else if (mystrcmp(&p, "fn")) {
		char* start = p;
		char* family;
		skip_all('\\');
		family = malloc(p - start + 1);
		strncpy(family, start, p - start);
		family[p - start] = '\0';
		if (render_context.family)
			free(render_context.family);
		render_context.family = family;
		update_font();
	} else if (mystrcmp(&p, "alpha")) {
		uint32_t val;
		int i;
		if (strtocolor(&p, &val)) {
			unsigned char a = val >> 24;
			for (i = 0; i < 4; ++i)
				change_alpha(&render_context.c[i], a, pwr);
		} else {
			change_alpha(&render_context.c[0], render_context.style->PrimaryColour, pwr);
			change_alpha(&render_context.c[1], render_context.style->SecondaryColour, pwr);
			change_alpha(&render_context.c[2], render_context.style->OutlineColour, pwr);
			change_alpha(&render_context.c[3], render_context.style->BackColour, pwr);
		}
		// FIXME: simplify
	} else if (mystrcmp(&p, "an")) {
		int val = strtol(p, &p, 10);
		int v = (val - 1) / 3; // 0, 1 or 2 for vertical alignment
		mp_msg(MSGT_GLOBAL, MSGL_DBG2, "an %d\n", val);
		if (v != 0) v = 3 - v;
		val = ((val - 1) % 3) + 1; // horizontal alignment
		val += v*4;
		mp_msg(MSGT_GLOBAL, MSGL_DBG2, "align %d\n", val);
		render_context.alignment = val;
	} else if (mystrcmp(&p, "a")) {
		int val = strtol(p, &p, 10);
		render_context.alignment = val;
	} else if (mystrcmp(&p, "pos")) {
		int v1, v2;
		skip('(');
		v1 = strtol(p, &p, 10);
		skip(',');
		v2 = strtol(p, &p, 10);
		skip(')');
		mp_msg(MSGT_GLOBAL, MSGL_DBG2, "pos(%d, %d)\n", v1, v2);
		render_context.evt_type = EVENT_POSITIONED;
		render_context.detect_collisions = 0;
		render_context.pos_x = v1;
		render_context.pos_y = v2;
	} else if (mystrcmp(&p, "fad")) {
		int a1, a2, a3;
		long long t1, t2, t3, t4;
		if (*p == 'e') ++p; // either \fad or \fade
		skip('(');
		a1 = strtol(p, &p, 10);
		skip(',');
		a2 = strtol(p, &p, 10);
		if (*p == ')') {
			// 2-argument version (\fad, according to specs)
			// a1 and a2 are fade-in and fade-out durations
			t1 = 0;
			t4 = render_context.event->Duration;
			t2 = a1;
			t3 = t4 - a2;
			a1 = 0xFF;
			a2 = 0;
			a3 = 0xFF;
		} else {
			// 6-argument version (\fade)
			// a1 and a2 (and a3) are opacity values
			skip(',');
			a3 = strtol(p, &p, 10);
			skip(',');
			t1 = strtoll(p, &p, 10);
			skip(',');
			t2 = strtoll(p, &p, 10);
			skip(',');
			t3 = strtoll(p, &p, 10);
			skip(',');
			t4 = strtoll(p, &p, 10);
		}
		skip(')');
		render_context.fade = interpolate_alpha(frame_context.time - render_context.event->Start, t1, t2, t3, t4, a1, a2, a3);
	} else if (mystrcmp(&p, "org")) {
		int v1, v2;
		skip('(');
		v1 = strtol(p, &p, 10);
		skip(',');
		v2 = strtol(p, &p, 10);
		skip(')');
		mp_msg(MSGT_GLOBAL, MSGL_DBG2, "org(%d, %d)\n", v1, v2);
		//				render_context.evt_type = EVENT_POSITIONED;
		render_context.org_x = v1;
		render_context.org_y = v2;
	} else if (mystrcmp(&p, "t")) {
		double v[3];
		int v1, v2;
		double v3;
		int cnt;
		long long t1, t2, t, delta_t;
		double k;
		skip('(');
		for (cnt = 0; cnt < 3; ++cnt) {
			if (*p == '\\')
				break;
			v[cnt] = strtod(p, &p);
			skip(',');
		}
		if (cnt == 3) {
			v1 = v[0]; v2 = v[1]; v3 = v[2];
		} else if (cnt == 2) {
			v1 = v[0]; v2 = v[1]; v3 = 1.;
		} else if (cnt == 1) {
			v1 = 0; v2 = render_context.event->Duration; v3 = v[0];
		} else { // cnt == 0
			v1 = 0; v2 = render_context.event->Duration; v3 = 1.;
		}
		render_context.detect_collisions = 0;
		t1 = v1;
		t2 = v2;
		delta_t = v2 - v1;
		t = frame_context.time - render_context.event->Start; // FIXME: move to render_context
		if (t < t1)
			k = 0.;
		else if (t > t2)
			k = 1.;
		else k = ((double)(t - t1)) / delta_t;
		while (*p == '\\')
			p = parse_tag(p, k); // maybe k*pwr ? no, specs forbid nested \t's 
		skip_all(')'); // FIXME: better skip(')'), but much more tags support required
	} else if (mystrcmp(&p, "clip")) {
		int x0, y0, x1, y1;
		int res = 1;
		skip('(');
		res &= mystrtoi(&p, 10, &x0);
		skip(',');
		res &= mystrtoi(&p, 10, &y0);
		skip(',');
		res &= mystrtoi(&p, 10, &x1);
		skip(',');
		res &= mystrtoi(&p, 10, &y1);
		skip(')');
		if (res) {
			render_context.clip_x0 = render_context.clip_x0 * (1-pwr) + x0 * pwr;
			render_context.clip_x1 = render_context.clip_x1 * (1-pwr) + x1 * pwr;
			render_context.clip_y0 = render_context.clip_y0 * (1-pwr) + y0 * pwr;
			render_context.clip_y1 = render_context.clip_y1 * (1-pwr) + y1 * pwr;
		} else {
			render_context.clip_x0 = 0;
			render_context.clip_y0 = 0;
			render_context.clip_x1 = frame_context.track->PlayResX;
			render_context.clip_y1 = frame_context.track->PlayResY;
		}
	} else if (mystrcmp(&p, "c")) {
		uint32_t val;
		if (!strtocolor(&p, &val))
			val = render_context.style->PrimaryColour;
		mp_msg(MSGT_GLOBAL, MSGL_DBG2, "color: %X\n", val);
		change_color(&render_context.c[0], val, pwr);
	} else if ((*p >= '1') && (*p <= '4') && (++p) && (mystrcmp(&p, "c") || mystrcmp(&p, "a"))) {
		char n = *(p-2);
		int cidx = n - '1';
		char cmd = *(p-1);
		uint32_t val;
		assert((n >= '1') && (n <= '4'));
		if (!strtocolor(&p, &val))
			switch(n) {
				case '1': val = render_context.style->PrimaryColour; break;
				case '2': val = render_context.style->SecondaryColour; break;
				case '3': val = render_context.style->OutlineColour; break;
				case '4': val = render_context.style->BackColour; break;
				default : val = 0; break; // impossible due to assert; avoid compilation warning
			}
		switch (cmd) {
			case 'c': change_color(render_context.c + cidx, val, pwr); break;
			case 'a': change_alpha(render_context.c + cidx, val >> 24, pwr); break;
			default: mp_msg(MSGT_GLOBAL, MSGL_WARN, "Bad command: %c%c\n", n, cmd); break;
		}
		mp_msg(MSGT_GLOBAL, MSGL_DBG2, "single c/a at %f: %c%c = %X   \n", pwr, n, cmd, render_context.c[cidx]);
	} else if (mystrcmp(&p, "r")) {
		reset_render_context();
	} else if (mystrcmp(&p, "be")) {
		int val;
		if (mystrtoi(&p, 10, &val))
			render_context.be = val ? 1 : 0;
		else
			render_context.be = 0;
	} else if (mystrcmp(&p, "b")) {
		int b;
		if (mystrtoi(&p, 10, &b))
			render_context.bold = b;
		else
			render_context.bold = - render_context.style->Bold;
		update_font();
	} else if (mystrcmp(&p, "i")) {
		int i;
		if (mystrtoi(&p, 10, &i))
			render_context.italic = i;
		else
			render_context.italic = - render_context.style->Italic;
		update_font();
	} else if (mystrcmp(&p, "kf") || mystrcmp(&p, "K")) {
		int val = strtol(p, &p, 10);
		render_context.effect_type = EF_KARAOKE_KF;
		if (render_context.effect_timing)
			render_context.effect_skip_timing += render_context.effect_timing;
		render_context.effect_timing = val * 10;
	} else if (mystrcmp(&p, "ko")) {
		int val = strtol(p, &p, 10);
		render_context.effect_type = EF_KARAOKE_KO;
		if (render_context.effect_timing)
			render_context.effect_skip_timing += render_context.effect_timing;
		render_context.effect_timing = val * 10;
	} else if (mystrcmp(&p, "k")) {
		int val = strtol(p, &p, 10);
		render_context.effect_type = EF_KARAOKE;
		if (render_context.effect_timing)
			render_context.effect_skip_timing += render_context.effect_timing;
		render_context.effect_timing = val * 10;
	} else if (mystrcmp(&p, "shad")) {
		int val;
		if (mystrtoi(&p, 10, &val))
			render_context.shadow = val;
		else
			render_context.shadow = render_context.style->Shadow;
	}

	return p;

#undef skip
#undef skip_all
}

/**
 * \brief Get next ucs4 char from string, parsing and executing style overrides
 * \param str string pointer
 * \return ucs4 code of the next char
 * On return str points to the unparsed part of the string
 */
static unsigned get_next_char(char** str)
{
	char* p = *str;
	unsigned chr;
	if (*p == '{') { // '\0' goes here
		p++;
		while (1) {
			p = parse_tag(p, 1.);
			if (*p == '}') { // end of tag
				p++;
				if (*p == '{') {
					p++;
					continue;
				} else
					break;
			} else if (*p != '\\')
				mp_msg(MSGT_GLOBAL, MSGL_V, "Unable to parse: \"%s\" \n", p);
			if (*p == 0)
				break;
		}
	}
	if (*p == '\t') {
		++p;
		*str = p;
		return ' ';
	}
	if (*p == '\\') {
		if ((*(p+1) == 'N') || ((*(p+1) == 'n') && (frame_context.track->WrapStyle == 2))) {
			p += 2;
			*str = p;
			return '\n';
		} else if (*(p+1) == 'n') {
			p += 2;
			*str = p;
			return ' ';
		}
	}
	chr = utf8_get_char(&p);
	*str = p;
	return chr;
}

static void apply_transition_effects(ass_event_t* event)
{
	int v[4];
	int cnt;
	char* p = event->Effect;

	if (!p || !*p) return;

	cnt = 0;
	while (cnt < 4 && (p = strchr(p, ';'))) {
		v[cnt++] = atoi(++p);
	}
	
	if (strncmp(event->Effect, "Banner;", 7) == 0) {
		int delay;
		if (cnt < 1) {
			mp_msg(MSGT_GLOBAL, MSGL_V, "Error parsing effect: %s \n", event->Effect);
			return;
		}
		if (cnt >= 2 && v[1] == 0) // right-to-left
			render_context.scroll_direction = SCROLL_RL;
		else // left-to-right
			render_context.scroll_direction = SCROLL_LR;

		delay = v[0];
		if (delay == 0) delay = 1; // ?
		render_context.scroll_shift = (frame_context.time - render_context.event->Start) / delay;
		render_context.evt_type = EVENT_HSCROLL;
		return;
	}

	if (strncmp(event->Effect, "Scroll up;", 10) == 0) {
		render_context.scroll_direction = SCROLL_BT;
	} else if (strncmp(event->Effect, "Scroll down;", 12) == 0) {
		render_context.scroll_direction = SCROLL_TB;
	} else {
		mp_msg(MSGT_GLOBAL, MSGL_V, "Unknown transition effect: %s \n", event->Effect);
		return;
	}
	// parse scroll up/down parameters
	{
		int delay;
		int y0, y1;
		if (cnt < 3) {
			mp_msg(MSGT_GLOBAL, MSGL_V, "Error parsing effect: %s \n", event->Effect);
			return;
		}
		delay = v[2];
		if (delay == 0) delay = 1; // ?
		render_context.scroll_shift = (frame_context.time - render_context.event->Start) / delay;
		if (v[0] < v[1]) {
			y0 = v[0]; y1 = v[1];
		} else {
			y0 = v[1]; y1 = v[0];
		}
		if (y1 == 0)
			y1 = frame_context.track->PlayResY; // y0=y1=0 means fullscreen scrolling
		render_context.clip_y0 = y0;
		render_context.clip_y1 = y1;
		render_context.evt_type = EVENT_VSCROLL;
		render_context.detect_collisions = 0;
	}

}

/**
 * \brief partially reset render_context to style values
 * Works like {\r}: resets some style overrides
 */
static void reset_render_context(void)
{
	render_context.c[0] = render_context.style->PrimaryColour;
	render_context.c[1] = render_context.style->SecondaryColour;
	render_context.c[2] = render_context.style->OutlineColour;
	render_context.c[3] = render_context.style->BackColour;
	render_context.font_size = render_context.style->FontSize;

	if (render_context.family)
		free(render_context.family);
	render_context.family = strdup(render_context.style->FontName);
	render_context.bold = - render_context.style->Bold;
	render_context.italic = - render_context.style->Italic;
	update_font();

	change_border(-1.);
	render_context.scale_x = render_context.style->ScaleX;
	render_context.scale_y = render_context.style->ScaleY;
	render_context.hspacing = 0; // FIXME
	render_context.be = 0;
	render_context.shadow = render_context.style->Shadow;

	// FIXME: does not reset unsupported attributes.
}

/**
 * \brief Start new event. Reset render_context.
 */
static void init_render_context(ass_event_t* event)
{
	render_context.event = event;
	render_context.style = frame_context.track->styles + event->Style;

	reset_render_context();

	render_context.evt_type = EVENT_NORMAL;
	render_context.alignment = 0;
	render_context.rotation = M_PI * render_context.style->Angle / 180.;
	render_context.pos_x = 0;
	render_context.pos_y = 0;
	render_context.org_x = 0;
	render_context.org_y = 0;
	render_context.clip_x0 = 0;
	render_context.clip_y0 = 0;
	render_context.clip_x1 = frame_context.track->PlayResX;
	render_context.clip_y1 = frame_context.track->PlayResY;
	render_context.detect_collisions = 1;
	render_context.fade = 0;
	render_context.effect_type = EF_NONE;
	render_context.effect_timing = 0;
	render_context.effect_skip_timing = 0;
	
	apply_transition_effects(event);
}

static void free_render_context(void)
{
}

/**
 * \brief Get normal and outline glyphs from cache (if possible) or font face
 * \param index face glyph index
 * \param symbol ucs4 char
 * \param info out: struct filled with extracted data
 * \param advance advance vector of the extracted glyph
 * \return 0 on success
 */
static int get_glyph(int index, int symbol, glyph_info_t* info, FT_Vector* advance)
{
	int error;
	glyph_hash_val_t* val;
	glyph_hash_key_t* key = &(info->hash_key);
	
	key->face = render_context.face;
	key->size = render_context.font_size;
	key->index = index;
	key->outline = (render_context.border * 0xFFFF); // convert to 16.16
	key->scale_x = (render_context.scale_x * 0xFFFF);
	key->scale_y = (render_context.scale_y * 0xFFFF);
	key->angle = (render_context.rotation * 0xFFFF);
	key->advance = *advance;
	key->bold = render_context.bold;
	key->italic = render_context.italic;
	key->be = render_context.be;

	val = cache_find_glyph(key);
//	val = 0;
	
	if (val) {
		info->glyph = info->outline_glyph = 0;
		info->bm = val->bm;
		info->bm_o = val->bm_o;
		info->bm_s = val->bm_s;
		info->bbox = val->bbox_scaled;
		info->advance.x = val->advance.x;
		info->advance.y = val->advance.y;

		return 0;
	}

	// not found, get a new outline glyph from face
//	mp_msg(MSGT_GLOBAL, MSGL_INFO, "miss, index = %d, symbol = %c, adv = (%d, %d)\n", index, symbol, advance->x, advance->y);
	
	error = FT_Load_Glyph(render_context.face, index, FT_LOAD_NO_BITMAP );
	if (error) {
		mp_msg(MSGT_GLOBAL, MSGL_WARN, "Error loading glyph\n");
		return error;
	}
	
#if (FREETYPE_MAJOR > 2) || \
    ((FREETYPE_MAJOR == 2) && (FREETYPE_MINOR >= 2)) || \
    ((FREETYPE_MAJOR == 2) && (FREETYPE_MINOR == 1) && (FREETYPE_PATCH >= 10))
// FreeType >= 2.1.10 required
	if (!(render_context.face->style_flags & FT_STYLE_FLAG_ITALIC) && 
			((render_context.italic == 1) || (render_context.italic > 55))) {
		FT_GlyphSlot_Oblique(render_context.face->glyph);
	}
#endif
	error = FT_Get_Glyph(render_context.face->glyph, &(info->glyph));
	if (error) {
		mp_msg(MSGT_GLOBAL, MSGL_WARN, "Error getting glyph\n");
		return error;
	}

	info->advance.x = info->glyph->advance.x >> 10;
	info->advance.y = info->glyph->advance.y >> 10;

	if (render_context.stroker) {
		info->outline_glyph = info->glyph;
		error = FT_Glyph_Stroke( &(info->outline_glyph), render_context.stroker, 0 ); // don't destroy original
		if (error) {
			mp_msg(MSGT_GLOBAL, MSGL_WARN, "FT_Glyph_Stroke error %d \n", error);
		}
	} else {
		info->outline_glyph = 0;
	}

	info->bm = info->bm_o = info->bm_s = 0;

	return 0;
}

/**
 * This function goes through text_info and calculates text parameters.
 * The following text_info fields are filled:
 *   n_lines
 *   height
 *   lines[].height
 *   lines[].asc
 *   lines[].desc
 */
static void measure_text()
{
	int cur_line = 0, max_asc = 0, max_desc = 0;
	int i;
	text_info.height = 0;
	for (i = 0; i < text_info.length + 1; ++i) {
		if ((i == text_info.length) || text_info.glyphs[i].linebreak) {
			text_info.lines[cur_line].asc = max_asc;
			text_info.lines[cur_line].desc = max_desc;
			text_info.height += max_asc + max_desc;
			cur_line ++;
			max_asc = max_desc = 0;
		}
		if (i < text_info.length) {
			glyph_info_t* cur = text_info.glyphs + i;
			if (cur->asc > max_asc)
				max_asc = cur->asc * render_context.scale_y;
			if (cur->desc > max_desc)
				max_desc = cur->desc * render_context.scale_y;
		}
	}
}

/**
 * \brief rearrange text between lines
 * \param max_text_width maximal text line width in pixels
 * The algo is similar to the one in libvo/sub.c:
 * 1. Place text, wrapping it when current line is full
 * 2. Try moving words from the end of a line to the beginning of the next one while it reduces
 * the difference in lengths between this two lines.
 * The result may not be optimal, but usually is good enough.
 */
static void wrap_lines_smart(int max_text_width)
{
	int i, j;
	glyph_info_t *cur, *s1, *e1, *s2, *s3, *w;
	int last_space;
	int break_type;
	int exit;
	int pen_shift_x;
	int pen_shift_y;
	int cur_line;

	last_space = -1;
	text_info.n_lines = 1;
	break_type = 0;
	s1 = text_info.glyphs; // current line start
	for (i = 0; i < text_info.length; ++i) {
		int break_at, s_offset, len;
		cur = text_info.glyphs + i;
		break_at = -1;
		s_offset = s1->bbox.xMin + s1->pos.x;
		len = (cur->bbox.xMax + cur->pos.x) - s_offset;

		if (cur->symbol == '\n') {
			break_type = 2;
			break_at = i;
			mp_msg(MSGT_GLOBAL, MSGL_DBG2, "forced line break at %d\n", break_at);
		}
		
		if (len >= max_text_width) {
			break_type = 1;
			break_at = last_space;
			if (break_at == -1)
				break_at = i - 1;
			if (break_at == -1)
				break_at = 0;
			mp_msg(MSGT_GLOBAL, MSGL_DBG2, "overfill at %d\n", i);
			mp_msg(MSGT_GLOBAL, MSGL_DBG2, "line break at %d\n", break_at);
		}

		if (break_at != -1) {
			// need to use one more line
			// marking break_at+1 as start of a new line
			int lead = break_at + 1; // the first symbol of the new line
			if (text_info.n_lines >= MAX_LINES) {
				// to many lines ! 
				// no more linebreaks
				for (j = lead; j < text_info.length; ++j)
					text_info.glyphs[j].linebreak = 0;
				break;
			}
			if (lead < text_info.length)
				text_info.glyphs[lead].linebreak = break_type;
			last_space = -1;
			s1 = text_info.glyphs + lead;
			s_offset = s1->bbox.xMin + s1->pos.x;
			text_info.n_lines ++;
		}
		
		if (cur->symbol == ' ')
			last_space = i;
	}
#define DIFF(x,y) (((x) < (y)) ? (y - x) : (x - y))
	exit = 0;
	while (!exit) {
		exit = 1;
		w = s3 = text_info.glyphs;
		s1 = s2 = 0;
		for (i = 0; i <= text_info.length; ++i) {
			cur = text_info.glyphs + i;
			if ((i == text_info.length) || cur->linebreak) {
				s1 = s2;
				s2 = s3;
				s3 = cur;
				if (s1 && (s2->linebreak == 1)) { // have at least 2 lines, and linebreak is 'soft'
					int l1, l2, l1_new, l2_new;

					w = s2;
					do { --w; } while ((w > s1) && (w->symbol == ' '));
					while ((w > s1) && (w->symbol != ' ')) { --w; }
					e1 = w;
					while ((e1 > s1) && (e1->symbol == ' ')) { --e1; }
					if (w->symbol == ' ') ++w;

					l1 = ((s2-1)->bbox.xMax + (s2-1)->pos.x) - (s1->bbox.xMin + s1->pos.x);
					l2 = ((s3-1)->bbox.xMax + (s3-1)->pos.x) - (s2->bbox.xMin + s2->pos.x);
					l1_new = (e1->bbox.xMax + e1->pos.x) - (s1->bbox.xMin + s1->pos.x);
					l2_new = ((s3-1)->bbox.xMax + (s3-1)->pos.x) - (w->bbox.xMin + w->pos.x);

					if (DIFF(l1_new, l2_new) < DIFF(l1, l2)) {
						w->linebreak = 1;
						s2->linebreak = 0;
						exit = 0;
					}
				}
			}
			if (i == text_info.length)
				break;
		}
		
	}
	assert(text_info.n_lines >= 1);
#undef DIFF
	
	measure_text();

	pen_shift_x = 0;
	pen_shift_y = 0;
	cur_line = 1;
	for (i = 0; i < text_info.length; ++i) {
		cur = text_info.glyphs + i;
		if (cur->linebreak) {
			int height = text_info.lines[cur_line - 1].desc + text_info.lines[cur_line].asc;
			cur_line ++;
			pen_shift_x = - cur->pos.x;
			pen_shift_y += (height >> 6) + global_settings->line_spacing;
			mp_msg(MSGT_GLOBAL, MSGL_DBG2, "shifting from %d to %d by (%d, %d)\n", i, text_info.length - 1, pen_shift_x, pen_shift_y);
		}
		cur->pos.x += pen_shift_x;
		cur->pos.y += pen_shift_y;
	}
}

/**
 * \brief determine karaoke effects
 * Karaoke effects cannot be calculated during parse stage (get_next_char()),
 * so they are done in a separate step.
 * Parse stage: when karaoke style override is found, its parameters are stored in the next glyph's 
 * (the first glyph of the karaoke word)'s effect_type and effect_timing.
 * This function:
 * 1. sets effect_type for all glyphs in the word (_karaoke_ word)
 * 2. sets effect_timing for all glyphs to x coordinate of the border line between the left and right karaoke parts
 * (left part is filled with PrimaryColour, right one - with SecondaryColour).
 */
static void process_karaoke_effects(void)
{
	glyph_info_t *cur, *cur2;
	glyph_info_t *s1, *e1; // start and end of the current word
	glyph_info_t *s2; // start of the next word
	int i;
	int timing; // current timing
	int tm_start, tm_end; // timings at start and end of the current word
	int tm_current;
	double dt;
	int x;
	int x_start, x_end;

	tm_current = frame_context.time - render_context.event->Start;
	timing = 0;
	s1 = s2 = 0;
	for (i = 0; i <= text_info.length; ++i) {
		cur = text_info.glyphs + i;
		if ((i == text_info.length) || (cur->effect_type != EF_NONE)) {
			s1 = s2;
			s2 = cur;
			if (s1) {
				e1 = s2 - 1;
				tm_start = timing + s1->effect_skip_timing;
				tm_end = tm_start + s1->effect_timing;
				timing = tm_end;
				x_start = s1->bbox.xMin + s1->pos.x;
				x_end = e1->bbox.xMax + e1->pos.x;

				dt = (tm_current - tm_start);
				if ((s1->effect_type == EF_KARAOKE) || (s1->effect_type == EF_KARAOKE_KO)) {
					if (dt > 0)
						x = x_end + 1;
					else
						x = x_start;
				} else if (s1->effect_type == EF_KARAOKE_KF) {
					dt /= (tm_end - tm_start);
					x = x_start + (x_end - x_start) * dt;
				} else {
					mp_msg(MSGT_GLOBAL, MSGL_ERR, "Unknown effect type (internal error)  \n");
					continue;
				}

				for (cur2 = s1; cur2 <= e1; ++cur2) {
					cur2->effect_type = s1->effect_type;
					cur2->effect_timing = x - cur2->pos.x;
				}
			}
		}
	}
}

static int get_face_ascender(FT_Face face)
{
	int v = face->size->metrics.ascender;
	int v2 = FT_MulFix(face->bbox.yMax, face->size->metrics.y_scale);
	if (v > v2 * 0.9)
		return v;
	else
		return v2;
}

static int get_face_descender(FT_Face face)
{
	int v = - face->size->metrics.descender;
	int v2 = - FT_MulFix(face->bbox.yMin, face->size->metrics.y_scale);
	if (v > v2 * 0.9)
		return v;
	else
		return v2;
}

/**
 * \brief Main ass rendering function, glues everything together
 * \param event event to render
 * Process event, appending resulting ass_image_t's to images_root.
 */
static int ass_render_event(ass_event_t* event, event_images_t* event_images)
{
	char* p;
	FT_UInt glyph_index; 
	FT_Bool use_kerning; 
	FT_UInt previous; 
	FT_UInt num_glyphs;
	FT_Vector pen;
	int error;
	unsigned code;
	FT_BBox bbox;
	int i, j;
	FT_Vector shift;
	int MarginL, MarginR, MarginV;
	int last_break;
	int alignment, halign, valign;
	int device_x = 0, device_y = 0;

	if (event->Style >= frame_context.track->n_styles) {
		mp_msg(MSGT_GLOBAL, MSGL_WARN, "No style found!\n");
		return 1;
	}
	if (!event->Text) {
		mp_msg(MSGT_GLOBAL, MSGL_WARN, "Empty event!\n");
		return 1;
	}

	init_render_context(event);

	text_info.length = 0;
	pen.x = 0;
	pen.y = 0;
	previous = 0;
	num_glyphs = 0;
	p = event->Text;
	// Event parsing.
	while (1) {
		// get next char, executing style override
		// this affects render_context
		code = get_next_char(&p);
		
		// face could have been changed in get_next_char
		if (!render_context.face) {
			free_render_context();
			return 1;
		}

		if (code == 0)
			break;

		use_kerning = FT_HAS_KERNING(render_context.face);

		if (text_info.length >= MAX_GLYPHS) {
			mp_msg(MSGT_GLOBAL, MSGL_WARN, "\nMAX_GLYPHS reached: event %d, start = %llu, duration = %llu\n Text = %s\n", 
					(int)(event - frame_context.track->events), event->Start, event->Duration, event->Text);
			break;
		}

		glyph_index = FT_Get_Char_Index( render_context.face, code);

		if ( use_kerning && previous && glyph_index ) {
			FT_Vector delta;
			FT_Get_Kerning( render_context.face, previous, glyph_index, FT_KERNING_DEFAULT, &delta );
			pen.x += delta.x;
			pen.y += delta.y;
		}

		shift.x = pen.x & 63;
		shift.y = pen.y & 63;

		if ((render_context.scale_x != 1.) || (render_context.scale_y != 1.) ||
				(frame_context.font_scale_x != 1.)) {
			FT_Matrix matrix;
			matrix.xx = (FT_Fixed)( render_context.scale_x * frame_context.font_scale_x * 0x10000L );
			matrix.xy = (FT_Fixed)( 0 * 0x10000L );
			matrix.yx = (FT_Fixed)( 0 * 0x10000L );
			matrix.yy = (FT_Fixed)( render_context.scale_y * 0x10000L );

			FT_Set_Transform( render_context.face, &matrix, &shift );
		} else {
			FT_Set_Transform(render_context.face, 0, &shift);
		}
		
		error = get_glyph(glyph_index, code, text_info.glyphs + text_info.length, &shift);

		if (error) {
			continue;
		}
		
		text_info.glyphs[text_info.length].pos.x = pen.x >> 6;
		text_info.glyphs[text_info.length].pos.y = pen.y >> 6;
		
		pen.x += text_info.glyphs[text_info.length].advance.x;
		pen.x += render_context.hspacing;
		pen.y += text_info.glyphs[text_info.length].advance.y;
		
		// if it's an outline glyph, we still need to fill the bbox
		if (text_info.glyphs[text_info.length].glyph) {
			FT_Glyph_Get_CBox( text_info.glyphs[text_info.length].glyph, FT_GLYPH_BBOX_PIXELS, &(text_info.glyphs[text_info.length].bbox) );
		}

		
		previous = glyph_index;
		
		text_info.glyphs[text_info.length].symbol = code;
		text_info.glyphs[text_info.length].linebreak = 0;
		for (i = 0; i < 4; ++i) {
			uint32_t clr = render_context.c[i];
			change_alpha(&clr, mult_alpha(_a(clr), render_context.fade), 1.);
			text_info.glyphs[text_info.length].c[i] = clr;
		}
		text_info.glyphs[text_info.length].effect_type = render_context.effect_type;
		text_info.glyphs[text_info.length].effect_timing = render_context.effect_timing;
		text_info.glyphs[text_info.length].effect_skip_timing = render_context.effect_skip_timing;
		text_info.glyphs[text_info.length].asc = get_face_ascender(render_context.face);
		text_info.glyphs[text_info.length].desc = get_face_descender(render_context.face);
		text_info.glyphs[text_info.length].be = render_context.be;
		text_info.glyphs[text_info.length].shadow = render_context.shadow;

		text_info.length++;

		render_context.effect_type = EF_NONE;
		render_context.effect_timing = 0;
		render_context.effect_skip_timing = 0;
	}
	
	if (text_info.length == 0) {
		// no valid symbols in the event; this can be smth like {comment}
		free_render_context();
		return 1;
	}
	
	// depends on glyph x coordinates being monotonous, so it should be done before line wrap
	process_karaoke_effects();
	
	// alignments
	alignment = render_context.alignment;
	if (!alignment)
		alignment = render_context.style->Alignment;
	halign = alignment & 3;
	valign = alignment & 12;

	MarginL = (event->MarginL) ? event->MarginL : render_context.style->MarginL; 
	MarginR = (event->MarginR) ? event->MarginR : render_context.style->MarginR; 
	MarginV = (event->MarginV) ? event->MarginV : render_context.style->MarginV;

	if (render_context.evt_type != EVENT_HSCROLL) {
		int max_text_width;

		// calculate max length of a line
		max_text_width = x2scr(frame_context.track->PlayResX - MarginR) - x2scr(MarginL);

		// rearrange text in several lines
		wrap_lines_smart(max_text_width);

		// align text
		last_break = -1;
		for (i = 1; i < text_info.length + 1; ++i) { // (text_info.length + 1) is the end of the last line
			if ((i == text_info.length) || text_info.glyphs[i].linebreak) {
				int width, shift;
				glyph_info_t* first_glyph = text_info.glyphs + last_break + 1;
				glyph_info_t* last_glyph = text_info.glyphs + i - 1;

				while ((last_glyph > first_glyph) && ((last_glyph->symbol == '\n') || (last_glyph->symbol == 0)))
					last_glyph --;

				width = last_glyph->pos.x + last_glyph->bbox.xMax - first_glyph->pos.x - first_glyph->bbox.xMin;
				shift = - first_glyph->bbox.xMin; // now text line starts exactly at 0 (left margin)
				if (halign == HALIGN_LEFT) { // left aligned, no action
				} else if (halign == HALIGN_RIGHT) { // right aligned
					shift = max_text_width - width;
				} else if (halign == HALIGN_CENTER) { // centered
					shift = (max_text_width - width) / 2;
				}
				for (j = last_break + 1; j < i; ++j) {
					text_info.glyphs[j].pos.x += shift;
				}
				last_break = i - 1;
			}
		}
	} else { // render_context.evt_type == EVENT_HSCROLL
		measure_text();
	}
	
	// determing text bounding box
	compute_string_bbox(&text_info, &bbox);
	bbox.yMin = - (text_info.lines[0].asc >> 6);
	bbox.yMax = (text_info.height - text_info.lines[0].asc) >> 6;
	
	// determine device coordinates for text
	
	// x coordinate for everything except positioned events
	if (render_context.evt_type == EVENT_NORMAL ||
	    render_context.evt_type == EVENT_VSCROLL) {
		device_x = x2scr(MarginL);
	} else if (render_context.evt_type == EVENT_HSCROLL) {
		if (render_context.scroll_direction == SCROLL_RL)
			device_x = x2scr(frame_context.track->PlayResX - render_context.scroll_shift);
		else if (render_context.scroll_direction == SCROLL_LR)
			device_x = x2scr(render_context.scroll_shift) - (bbox.xMax - bbox.xMin);
	}

	// y coordinate for everything except positioned events
	if (render_context.evt_type == EVENT_NORMAL ||
	    render_context.evt_type == EVENT_HSCROLL) {
		if (valign == VALIGN_TOP) { // toptitle
			device_y = y2scr_top(MarginV) + (text_info.lines[0].asc >> 6);
		} else if (valign == VALIGN_CENTER) { // midtitle
			int scr_y = y2scr(frame_context.track->PlayResY / 2);
			device_y = scr_y - (bbox.yMax - bbox.yMin) / 2;
		} else { // subtitle
			int scr_y;
			if (valign != VALIGN_SUB)
				mp_msg(MSGT_GLOBAL, MSGL_V, "Invalid valign, supposing 0 (subtitle)\n");
			scr_y = y2scr_sub(frame_context.track->PlayResY - MarginV);
			device_y = scr_y;
			device_y -= (text_info.height >> 6);
			device_y += (text_info.lines[0].asc >> 6);
		}
	} else if (render_context.evt_type == EVENT_VSCROLL) {
		if (render_context.scroll_direction == SCROLL_TB)
			device_y = y2scr(render_context.clip_y0 + render_context.scroll_shift) - (bbox.yMax - bbox.yMin);
		else if (render_context.scroll_direction == SCROLL_BT)
			device_y = y2scr(render_context.clip_y1 - render_context.scroll_shift);
	}

	// positioned events are totally different
	if (render_context.evt_type == EVENT_POSITIONED) {
		int align_shift_x = 0;
		int align_shift_y = 0;
		mp_msg(MSGT_GLOBAL, MSGL_DBG2, "positioned event at %d, %d\n", render_context.pos_x, render_context.pos_y);
		switch(halign) {
			case HALIGN_LEFT:
				align_shift_x = - bbox.xMin;
				break;
			case HALIGN_CENTER:
				align_shift_x = - (bbox.xMax + bbox.xMin) /2;
				break;
			case HALIGN_RIGHT:
				align_shift_x = - bbox.xMax;
				break;
		}
		switch(valign) {
			case VALIGN_TOP:
				align_shift_y = - bbox.yMin;
				break;
			case VALIGN_CENTER:
				align_shift_y = - (bbox.yMax + bbox.yMin) /2;
				break;
			case VALIGN_SUB:
				align_shift_y = - bbox.yMax;
				break;
		}
		device_x = x2scr(render_context.pos_x) + align_shift_x;
		device_y = y2scr(render_context.pos_y) + align_shift_y;
	}
	
	// fix clip coordinates (they depend on alignment)
	render_context.clip_x0 = x2scr(render_context.clip_x0);
	render_context.clip_x1 = x2scr(render_context.clip_x1);
	if (render_context.evt_type == EVENT_NORMAL ||
	    render_context.evt_type == EVENT_HSCROLL ||
	    render_context.evt_type == EVENT_VSCROLL) {
		if (valign == VALIGN_TOP) {
			render_context.clip_y0 = y2scr_top(render_context.clip_y0);
			render_context.clip_y1 = y2scr_top(render_context.clip_y1);
		} else if (valign == VALIGN_CENTER) {
			render_context.clip_y0 = y2scr(render_context.clip_y0);
			render_context.clip_y1 = y2scr(render_context.clip_y1);
		} else if (valign == VALIGN_SUB) {
			render_context.clip_y0 = y2scr_sub(render_context.clip_y0);
			render_context.clip_y1 = y2scr_sub(render_context.clip_y1);
		}
	} else if (render_context.evt_type == EVENT_POSITIONED) {
		render_context.clip_y0 = y2scr(render_context.clip_y0);
		render_context.clip_y1 = y2scr(render_context.clip_y1);
	}

	// rotate glyphs if needed
	if (render_context.rotation != 0.) {
		double angle = render_context.rotation;
		FT_Vector center;
		FT_Matrix matrix_rotate;
		
		matrix_rotate.xx = (FT_Fixed)( cos( angle ) * 0x10000L );
		matrix_rotate.xy = (FT_Fixed)( -sin( angle ) * 0x10000L );
		matrix_rotate.yx = (FT_Fixed)( sin( angle ) * 0x10000L );
		matrix_rotate.yy = (FT_Fixed)( cos( angle ) * 0x10000L );
		
		if (((render_context.org_x != 0) || (render_context.org_y != 0)) && (render_context.evt_type == EVENT_POSITIONED)) {
			center.x = render_context.org_x;
			center.y = render_context.org_y;
		} else {
			FT_BBox str_bbox;

			center.x = text_info.glyphs[0].pos.x + device_x;
			center.y = text_info.glyphs[0].pos.y + device_y;

			compute_string_bbox(&text_info, &str_bbox);
			center.x += (str_bbox.xMax - str_bbox.xMin) / 2;
			center.y += (str_bbox.yMax - str_bbox.yMin) / 2;
		}
//		mp_msg(MSGT_GLOBAL, MSGL_DBG2, "\ncenter: %d, %d\n", center.x, center.y);

		for (i = 0; i < text_info.length; ++i) {
			glyph_info_t* info = text_info.glyphs + i;

			// calculating shift vector
			// shift = (position - center)*M - (position - center)
			FT_Vector start;
			FT_Vector start_old;
//			mp_msg(MSGT_GLOBAL, MSGL_INFO, "start: (%d, %d) + (%d, %d) - (%d, %d) = (%d, %d)\n", info->pos.x, info->pos.y, device_x, device_y, center.x, center.y,
//					info->pos.x + device_x - center.x, info->pos.y + device_y - center.y);
			start.x = (info->pos.x + device_x - center.x) << 6;
			start.y = - (info->pos.y + device_y - center.y) << 6;
			start_old.x = start.x;
			start_old.y = start.y;
//			mp_msg(MSGT_GLOBAL, MSGL_INFO, "start: %d, %d\n", start.x / 64, start.y / 64);

			FT_Vector_Transform(&start, &matrix_rotate);
			
			start.x -= start_old.x;
			start.y -= start_old.y;

			info->pos.x += start.x >> 6;
			info->pos.y -= start.y >> 6;

//			mp_msg(MSGT_GLOBAL, MSGL_DBG2, "shift: %d, %d\n", start.x / 64, start.y / 64);
			if (info->glyph)
				FT_Glyph_Transform( info->glyph, &matrix_rotate, 0 );
			if (info->outline_glyph)
				FT_Glyph_Transform( info->outline_glyph, &matrix_rotate, 0 );
		}
	}

	event_images->top = device_y - (text_info.lines[0].asc >> 6);
	event_images->height = text_info.height >> 6;
	event_images->detect_collisions = render_context.detect_collisions;
	event_images->shift_direction = (valign == VALIGN_TOP) ? 1 : -1;
	event_images->event = event;
	event_images->imgs = render_text(&text_info, device_x, device_y);

	free_render_context();
	
	return 0;
}

void ass_configure(ass_instance_t* priv, const ass_settings_t* config)
{
	if (memcmp(&priv->settings, config, sizeof(ass_settings_t)) != 0) {
		mp_msg(MSGT_GLOBAL, MSGL_V, "ass_configure: %d x %d; margins: l: %d, r: %d, t: %d, b: %d  \n",
				config->frame_width, config->frame_height,
				config->left_margin, config->right_margin, config->top_margin, config->bottom_margin);

		priv->render_id = ++last_render_id;
		memcpy(&priv->settings, config, sizeof(ass_settings_t));
		ass_glyph_cache_reset();
	}
}

/**
 * \brief Start a new frame
 */
static int ass_start_frame(ass_instance_t *priv, ass_track_t* track, long long now)
{
	ass_image_t* img;

	ass_instance = priv;
	global_settings = &priv->settings;

	if (!priv->settings.frame_width && !priv->settings.frame_height)
		return 1; // library not initialized
	
	frame_context.ass_priv = priv;
	frame_context.width = global_settings->frame_width;
	frame_context.height = global_settings->frame_height;
	frame_context.orig_width = global_settings->frame_width - global_settings->left_margin - global_settings->right_margin;
	frame_context.orig_height = global_settings->frame_height - global_settings->top_margin - global_settings->bottom_margin;
	frame_context.track = track;
	frame_context.time = now;

	ass_lazy_track_init();
	
	frame_context.font_scale = global_settings->font_size_coeff * ass_internal_font_size_coeff *
	                           frame_context.orig_height / frame_context.track->PlayResY;
	frame_context.border_scale = ((double)frame_context.orig_height) / frame_context.track->PlayResY;

	if (frame_context.width * track->PlayResY == frame_context.height * track->PlayResX)
		frame_context.font_scale_x = 1.;
	else
		frame_context.font_scale_x = ((double)(frame_context.orig_width * track->PlayResY)) / (frame_context.orig_height * track->PlayResX);

	img = priv->images_root;
	while (img) {
		ass_image_t* next = img->next;
		free(img);
		img = next;
	}
	priv->images_root = 0;

	return 0;
}

static int cmp_event_layer(const void* p1, const void* p2)
{
	ass_event_t* e1 = ((event_images_t*)p1)->event;
	ass_event_t* e2 = ((event_images_t*)p2)->event;
	if (e1->Layer < e2->Layer)
		return -1;
	if (e1->Layer > e2->Layer)
		return 1;
	if (e1->Start < e2->Start)
		return -1;
	if (e1->Start > e2->Start)
		return 1;
	if (e1->ReadOrder < e2->ReadOrder)
		return -1;
	if (e1->ReadOrder > e2->ReadOrder)
		return 1;
	return 0;
}

#define MAX_EVENTS 100

static render_priv_t* get_render_priv(ass_event_t* event)
{
	if (!event->render_priv)
		event->render_priv = calloc(1, sizeof(render_priv_t));
	// FIXME: check render_id
	if (ass_instance->render_id != event->render_priv->render_id) {
		memset(event->render_priv, 0, sizeof(render_priv_t));
		event->render_priv->render_id = ass_instance->render_id;
	}
	return event->render_priv;
}

typedef struct segment_s {
	int a, b; // top and height
} segment_t;

static int overlap(segment_t* s1, segment_t* s2)
{
	if (s1->a >= s2->b || s2->a >= s1->b)
		return 0;
	return 1;
}

static int cmp_segment(const void* p1, const void* p2)
{
	return ((segment_t*)p1)->a - ((segment_t*)p1)->b;
}

static void shift_event(event_images_t* ei, int shift)
{
	ass_image_t* cur = ei->imgs;
	while (cur) {
		cur->dst_y += shift;
		// clip top and bottom
		if (cur->dst_y < 0) {
			int clip = - cur->dst_y;
			cur->h -= clip;
			cur->bitmap += clip * cur->stride;
			cur->dst_y = 0;
		}
		if (cur->dst_y + cur->h >= frame_context.height) {
			int clip = cur->dst_y + cur->h - frame_context.height;
			cur->h -= clip;
		}
		if (cur->h <= 0) {
			cur->h = 0;
			cur->dst_y = 0;
		}
		cur = cur->next;
	}
	ei->top += shift;
}

// dir: 1 - move down
//      -1 - move up
static int fit_segment(segment_t* s, segment_t* fixed, int* cnt, int dir)
{
	int i;
	int shift;

	if (*cnt == 0) {
		*cnt = 1;
		fixed[0].a = s->a;
		fixed[0].b = s->b;
		return 0;
	}

	if (dir == 1) { // move down
		if (s->b <= fixed[0].a) // all ok
			return 0;
		for (i = 0; i < *cnt; ++i) {
			shift = fixed[i].b - s->a;
			if (i == *cnt - 1 || fixed[i+1].a >= shift + s->b) { // here is a good place
				fixed[i].b += s->b - s->a;
				return shift;
			}
		}
	} else { // dir == -1, move up
		if (s->a >= fixed[*cnt-1].b) // all ok
			return 0;
		for (i = *cnt-1; i >= 0; --i) {
			shift = fixed[i].a - s->b;
			if (i == 0 || fixed[i-1].b <= shift + s->a) { // here is a good place
				fixed[i].a -= s->b - s->a;
				return shift;
			}
		}
	}
	assert(0); // unreachable
}

static void fix_collisions(event_images_t* imgs, int cnt)
{
	segment_t used[MAX_EVENTS];
	int cnt_used = 0;
	int i, j;

	// fill used[] with fixed events
	for (i = 0; i < cnt; ++i) {
		render_priv_t* priv;
		if (!imgs[i].detect_collisions) break;
		priv = get_render_priv(imgs[i].event);
		if (priv->height > 0) { // it's a fixed event
			segment_t s;
			s.a = priv->top;
			s.b = priv->top + priv->height;
			if (priv->height != imgs[i].height) { // no, it's not
				mp_msg(MSGT_GLOBAL, MSGL_WARN, "Achtung! Event height has changed!  \n");
				priv->top = 0;
				priv->height = 0;
			}
			for (j = 0; j < cnt_used; ++j)
				if (overlap(&s, used + j)) { // no, it's not
					priv->top = 0;
					priv->height = 0;
				}
			if (priv->height > 0) { // still a fixed event
				used[cnt_used].a = priv->top;
				used[cnt_used].b = priv->top + priv->height;
				cnt_used ++;
				shift_event(imgs + i, priv->top - imgs[i].top);
			}
		}
	}
	qsort(used, cnt_used, sizeof(segment_t), cmp_segment);

	// try to fit other events in free spaces
	for (i = 0; i < cnt; ++i) {
		render_priv_t* priv;
		if (!imgs[i].detect_collisions) break;
		priv = get_render_priv(imgs[i].event);
		if (priv->height == 0) { // not a fixed event
			int shift;
			segment_t s;
			s.a = imgs[i].top;
			s.b = imgs[i].top + imgs[i].height;
			shift = fit_segment(&s, used, &cnt_used, imgs[i].shift_direction);
			if (shift) shift_event(imgs + i, shift);
			// make it fixed
			priv->top = imgs[i].top;
			priv->height = imgs[i].height;
		}
		
	}
}

/**
 * \brief render a frame
 * \param priv library handle
 * \param track track
 * \param now current video timestamp (ms)
 */
ass_image_t* ass_render_frame(ass_instance_t *priv, ass_track_t* track, long long now)
{
	int i, cnt, rc;
	event_images_t eimg[MAX_EVENTS];
	event_images_t* last;
	ass_image_t** tail;
	
	// init frame
	rc = ass_start_frame(priv, track, now);
	if (rc != 0)
		return 0;

	// render events separately
	cnt = 0;
	for (i = 0; i < track->n_events; ++i) {
		ass_event_t* event = track->events + i;
		if ( (event->Start <= now) && (now < (event->Start + event->Duration)) ) {
			if (cnt < MAX_EVENTS) {
				rc = ass_render_event(event, eimg + cnt);
				if (!rc) ++cnt;
			} else {
				mp_msg(MSGT_GLOBAL, MSGL_WARN, "Too many simultaneous events  \n");
				break;
			}
		}
	}

	// sort by layer
	qsort(eimg, cnt, sizeof(event_images_t), cmp_event_layer);

	// call fix_collisions for each group of events with the same layer
	last = eimg;
	for (i = 1; i < cnt; ++i)
		if (last->event->Layer != eimg[i].event->Layer) {
			fix_collisions(last, eimg + i - last);
			last = eimg + i;
		}
	if (cnt > 0)
		fix_collisions(last, eimg + cnt - last);

	// concat lists
	tail = &ass_instance->images_root;
	for (i = 0; i < cnt; ++i) {
		ass_image_t* cur = eimg[i].imgs;
		while (cur) {
			*tail = cur;
			tail = &cur->next;
			cur = cur->next;
		}
	}
	
	return ass_instance->images_root;
}

