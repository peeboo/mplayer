/*
 * vo_dxr3.c - DXR3/H+ video out
 *
 * Copyright (C) 2002 David Holm <dholm@iname.com>
 *
 */

/* ChangeLog added 2002-01-10
 * 2002-12-24: (Hohoho)
 *  Added patch from Thomas Jarosch <tomj@simonv.com> which adds support
 *   for setting the TV norm by movie framerate.
 *
 * 2002-11-03:
 *  Cleaned up syncing code and renamed setup variables so
 *   they can be accessed from the GUI.
 *
 * 2002-11-02:
 *  Added native overlay support, activate with :overlay
 *   you have to run dxr3view to modify settings (or manually
 *   edit the files in ~/.overlay.
 *
 * 2002-10-29:
 *  Added new sync-engine, activate with :sync option.
 *  Greatly improved commandline parser.
 *  Replaced :noprebuf with :prebuf and made noprebuf the default.
 *
 * 2002-10-28:
 *  Fixed multicard bug on athlons
 *
 * 2002-07-18:
 *  Disabled spuenc support, this is still not stable enough =(
 *
 * 2002-07-05:
 *  Removed lavc and fame encoder to be compatible with new libvo style.
 *  Added graphic equalizer support.
 *
 * 2002-04-15:
 *  The spuenc code isn't 100% stable yet, therefore I'm disabling
 *  it due to the upcoming stable release.
 *
 * 2002-04-03:
 *  Carl George added spuenc support
 *
 * 2002-03-26:
 *  XorA added an option parser and support for selecting encoder
 *  codec. We thank him again.
 *
 * 2002-03-25:
 *  A couple of bugfixes by XorA
 *
 * 2002-03-23:
 *  Thanks to Marcel Hild <hild@b4mad.net> the jitter-bug experienced
 *  with some videos have been fixed, many thanks goes to him.
 *
 * 2002-03-16:
 *  Fixed problems with fame, it gives a better picture than avcodec,
 *  but is slightly slower. Most notably the wobbling effect is gone
 *  with fame.
 *
 * 2002-03-13:
 *  Preliminary fame support added (it breaks after seeking, why?)
 *
 * 2002-02-18:
 *  Fixed sync problems when pausing video (while using prebuffering)
 *
 * 2002-02-16:
 *  Fixed bug which would case invalid output when using :noprebuf
 *  Removed equalization code, it caused problems on slow systems
 *
 * 2002-02-13:
 *  Using the swscaler instead of the old hand coded shit. (Checkout man mplayer and search for sws ;).
 *  Using aspect function to setup a proper mpeg1, no more hassling with odd resolutions or GOP-sizes,
 *  this would only create jitter on some vids!
 *  The swscaler sometimes exits with sig8 on mpegs, I don't know why yet (just use -vc mpegpes in this
 *  case, and report to me if you have any avi's etc which does this...)
 *
 * 2002-02-09:
 *  Thanks to the new control() method I have finally been able to enable the em8300 prebuffering.
 *  This should speed up playback on all systems, the vout cpu usage should rocket since I will be hogging
 *  the pci bus. Not to worry though, since frames are prebuffered it should be able to take a few blows
 *  if you start doing other stuff simultaneously.
 *
 * 2002-02-03:
 *  Removal of libmp1e, libavcodec has finally become faster (and it's code is helluva lot cleaner)
 *
 * 2002-02-02:
 *  Cleaned out some old code which might have slowed down writes
 *
 * 2002-01-17:
 *  Testrelease of new sync engine (using previously undocumented feature of em8300).
 *
 * 2002-01-15:
 *  Preliminary subpic support with -vc mpegpes and dvd's
 *  Device interfaces tries the new naming scheme by default (even though most users probably still use the old one)
 *
 * 2002-01-10:
 *  I rehauled the entire codebase. I have now changed to
 *  Kernighan & Ritchie codingstyle, please mail me if you 
 *  find any inconcistencies.
 */
 
#include <linux/em8300.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/select.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#include "config.h"
#ifdef HAVE_MALLOC_H
#include <malloc.h>
#endif
#include "fastmemcpy.h"

#include "video_out.h"
#include "video_out_internal.h"
#include "aspect.h"
#include "spuenc.h"
#include "sub.h"
#ifdef HAVE_NEW_GUI
#include "../Gui/interface.h"
#endif
#ifdef HAVE_X11
#include "x11_common.h"
#endif

#define SPU_SUPPORT

static vo_info_t info = 
{
	"DXR3/H+ video out",
	"dxr3",
	"David Holm <dholm@iname.com>",
	""
};
LIBVO_EXTERN (dxr3)

/* Resolutions and positions */
static int v_width, v_height;
static int s_width, s_height;
static int osd_w, osd_h;
static int fullscreen = 0;
static int img_format = 0;

/* Configuration values
 * Don't declare these static, they 
 * should be accessible from the gui.
 */
int dxr3_prebuf = 0;
int dxr3_newsync = 0;
int dxr3_overlay = 0;
int dxr3_device_num = 0;
int dxr3_norm = 0;

/* File descriptors */
static int fd_control = -1;
static int fd_video = -1;
static int fd_spu = -1;
static char fdv_name[80];
static char fds_name[80];

#ifdef SPU_SUPPORT
/* on screen display/subpics */
static char *osdpicbuf = NULL;
static int osdpicbuf_w;
static int osdpicbuf_h;
static int disposd = 0;
static encodedata *spued;
static encodedata *spubuf;
#endif


/* Static variable used in ioctl's */
static int ioval = 0;
static int prev_pts = 0;
static int pts_offset = 0;


/* Begin overlay.h */
/*
  Simple analog overlay API for DXR3/H+ linux driver.

  Henrik Johansson
*/


/* Pattern drawing callback used by the calibration functions.
   The function is expected to:
     Clear the entire screen.
     Fill the screen with color bgcol (0xRRGGBB)
     Draw a rectangle at (xpos,ypos) of size (width,height) in fgcol (0xRRGGBB)
*/

typedef int (*pattern_drawer_cb)(int fgcol, int bgcol,
			     int xpos, int ypos, int width, int height, void *arg);

struct coeff {
    float k,m;
};

typedef struct {
    int dev;

    int xres, yres,depth;
    int xoffset,yoffset,xcorr;
    int jitter;
    int stability;
    int keycolor;
    struct coeff colcal_upper[3];
    struct coeff colcal_lower[3];
    float color_interval;

    pattern_drawer_cb draw_pattern;
    void *dp_arg;
} overlay_t;


static overlay_t *overlay_init(int dev);
static int overlay_release(overlay_t *);

static int overlay_read_state(overlay_t *o, char *path);
static int overlay_write_state(overlay_t *o, char *path);

static int overlay_set_screen(overlay_t *o, int xres, int yres, int depth);
static int overlay_set_mode(overlay_t *o, int mode);
static int overlay_set_attribute(overlay_t *o, int attribute, int val);
static int overlay_set_keycolor(overlay_t *o, int color);
static int overlay_set_window(overlay_t *o, int xpos,int ypos,int width,int height);
static int overlay_set_bcs(overlay_t *o, int brightness, int contrast, int saturation);

static int overlay_autocalibrate(overlay_t *o, pattern_drawer_cb pd, void *arg);
static void overlay_update_params(overlay_t *o);
static int overlay_signalmode(overlay_t *o, int mode);
/* End overlay.h */


#ifdef HAVE_X11
#define KEY_COLOR 0x80a040
static XWindowAttributes xwin_attribs;
static overlay_t *overlay_data;
#endif


/* Functions for working with the em8300's internal clock */
/* End of internal clock functions */

static uint32_t control(uint32_t request, void *data, ...)
{
	switch (request) {
	case VOCTRL_GUISUPPORT:
		return VO_TRUE;
	case VOCTRL_GUI_NOWINDOW:
		if (dxr3_overlay) {
			return VO_FALSE;
		}
		return VO_TRUE;
	case VOCTRL_SET_SPU_PALETTE:
		if (ioctl(fd_spu, EM8300_IOCTL_SPU_SETPALETTE, data) < 0) {
			printf("VO: [dxr3] Unable to load new SPU palette!\n");
			return VO_ERROR;
		}
		return VO_TRUE;
#ifdef HAVE_X11
	case VOCTRL_FULLSCREEN:
		if (dxr3_overlay) {
			vo_x11_fullscreen();
			if (fullscreen) {
				overlay_signalmode(overlay_data, EM8300_OVERLAY_SIGNAL_WITH_VGA);
				fullscreen = 0;
			} else {
				overlay_signalmode(overlay_data, EM8300_OVERLAY_SIGNAL_ONLY);
				fullscreen = 1;
			}
			return VO_TRUE;
		}
		return VO_FALSE;
#endif
	case VOCTRL_RESUME:
		if (dxr3_newsync) {
			ioctl(fd_control, EM8300_IOCTL_SCR_GET, &ioval);
			pts_offset = vo_pts - (ioval << 1);
			if (pts_offset < 0) {
				pts_offset = 0;
			}
		}
		
		if (dxr3_prebuf) {
			ioval = EM8300_PLAYMODE_PLAY;
			if (ioctl(fd_control, EM8300_IOCTL_SET_PLAYMODE, &ioval) < 0) {
				printf("VO: [dxr3] Unable to set playmode!\n");
			}
		}
		return VO_TRUE;
	case VOCTRL_PAUSE:
		if (dxr3_prebuf) {
			ioval = EM8300_PLAYMODE_PAUSED;
			if (ioctl(fd_control, EM8300_IOCTL_SET_PLAYMODE, &ioval) < 0) {
				printf("VO: [dxr3] Unable to set playmode!\n");
			}
		}
		return VO_TRUE;
	case VOCTRL_RESET:
		if (dxr3_prebuf) {
			close(fd_video);
			fd_video = open(fdv_name, O_WRONLY);
			close(fd_spu);
			fd_spu = open(fds_name, O_WRONLY);
			fsync(fd_video);
			fsync(fd_spu);
		}
		return VO_TRUE;
	case VOCTRL_QUERY_FORMAT:
	    {
		uint32_t flag = 0;

		if (*((uint32_t*)data) != IMGFMT_MPEGPES)
		    return 0;

		flag = VFCAP_CSP_SUPPORTED | VFCAP_CSP_SUPPORTED_BY_HW | VFCAP_SPU;
		if (dxr3_prebuf)
		    flag |= VFCAP_TIMER;
		return flag;
	    }
	case VOCTRL_SET_EQUALIZER:
	    {
		va_list ap;
		int value;
		em8300_bcs_t bcs;
		
		va_start(ap, data);
		value = va_arg(ap, int);
		va_end(ap);

		if (ioctl(fd_control, EM8300_IOCTL_GETBCS, &bcs) < 0)
		    return VO_FALSE;
		if (!strcasecmp(data, "brightness"))
		    bcs.brightness = (value+100)*5;
		else if (!strcasecmp(data, "contrast"))
		    bcs.contrast = (value+100)*5;
		else if (!strcasecmp(data, "saturation"))
		    bcs.saturation = (value+100)*5;
		else return VO_FALSE;
        
		if (ioctl(fd_control, EM8300_IOCTL_SETBCS, &bcs) < 0)
		    return VO_FALSE;
		return VO_TRUE;
	    }
	case VOCTRL_GET_EQUALIZER:
	    {
		va_list ap;
		int *value;
		em8300_bcs_t bcs;
		
		va_start(ap, data);
		value = va_arg(ap, int*);
		va_end(ap);

		if (ioctl(fd_control, EM8300_IOCTL_GETBCS, &bcs) < 0)
		    return VO_FALSE;
		
		if (!strcasecmp(data, "brightness"))
		    *value = (bcs.brightness/5)-100;
		else if (!strcasecmp(data, "contrast"))
		    *value = (bcs.contrast/5)-100;
		else if (!strcasecmp(data, "saturation"))
		    *value = (bcs.saturation/5)-100;
		else return VO_FALSE;
        
		return VO_TRUE;
	    }
	}
	return VO_NOTIMPL;
}

void calculate_cvals(unsigned long mask, int *shift, int *prec)
{
	/* Calculate shift and precision */
	(*shift) = 0;
	(*prec) = 0;
	
	while (!(mask & 0x1)) {
		(*shift)++;
		mask >>= 1;
	}
	
	while (mask & 0x1) {
		(*prec)++;
		mask >>= 1;
	}
}

static uint32_t config(uint32_t width, uint32_t height, uint32_t d_width, uint32_t d_height, uint32_t fullscreen, char *title, uint32_t format)
{
	int tmp1, tmp2, size;
	em8300_register_t reg;
	extern float monitor_aspect;

	/* Softzoom turned on, downscale */
	/* This activates the subpicture processor, you can safely disable this and still send */
	/* broken subpics to the em8300, if it's enabled and you send broken subpics you will end */
	/* up in a lockup */
	ioval = EM8300_SPUMODE_ON;
	if (ioctl(fd_control, EM8300_IOCTL_SET_SPUMODE, &ioval) < 0) {
		printf("VO: [dxr3] Unable to set subpicture mode!\n");
		uninit();
		return -1;
	}

	/* Set the playmode to play (just in case another app has set it to something else) */
	ioval = EM8300_PLAYMODE_PLAY;
	if (ioctl(fd_control, EM8300_IOCTL_SET_PLAYMODE, &ioval) < 0) {
		printf("VO: [dxr3] Unable to set playmode!\n");
	}
	
	/* Start em8300 prebuffering and sync engine */
#ifdef MVCOMMAND_SYNC
	reg.microcode_register = 1;
	reg.reg = 0;
	reg.val = MVCOMMAND_SYNC;
	ioctl(fd_control, EM8300_IOCTL_WRITEREG, &reg);
#endif

#ifdef EM8300_IOCTL_FLUSH	
	/* Clean buffer by syncing it */
	ioval = EM8300_SUBDEVICE_VIDEO;
	ioctl(fd_control, EM8300_IOCTL_FLUSH, &ioval);
	ioval = EM8300_SUBDEVICE_AUDIO;
	ioctl(fd_control, EM8300_IOCTL_FLUSH, &ioval);
#endif

	/* Sync the video device to make sure the buffers are empty
	 * and set the playback speed to normal. Also reset the
	 * em8300 internal clock.
	 */
	fsync(fd_video);
	ioval = 0x900;
	ioctl(fd_control, EM8300_IOCTL_SCR_SETSPEED, &ioval);

	/* Store some variables statically that we need later in another scope */
	img_format = format;
	v_width = width;
	v_height = height;

	/* Set monitor_aspect to avoid jitter */
	monitor_aspect = (float) width / (float) height;
	
	/* adjust TV norm */
#ifdef EM8300_IOCTL_SET_VIDEOMODE
	if (dxr3_norm != 0) {
	    if (dxr3_norm == 5) {
			ioval = EM8300_VIDEOMODE_NTSC;
	    } else if (dxr3_norm == 4) {
			ioval = EM8300_VIDEOMODE_PAL60;
	    } else if (dxr3_norm == 3) {
			ioval = EM8300_VIDEOMODE_PAL;
	    } else if (dxr3_norm == 2) {
			if (vo_fps > 28) {
			    ioval = EM8300_VIDEOMODE_PAL60;
			} else {
			    ioval = EM8300_VIDEOMODE_PAL;
			}
			
			printf("VO: [dxr3] Auto-selected TV norm by frame rate: ");
			ioval == EM8300_VIDEOMODE_PAL60 ? printf("PAL-60") : printf("PAL");
			printf("\n"); 
		} else if (dxr3_norm == 1) {
			if (vo_fps > 28) {
			    ioval = EM8300_VIDEOMODE_NTSC;
			} else {
			    ioval = EM8300_VIDEOMODE_PAL;
			}

			printf("VO: [dxr3] Auto-selected TV norm by frame rate: ");
			ioval == EM8300_VIDEOMODE_NTSC ? printf("NTSC") : printf("PAL");
			printf("\n"); 
	    }
	
	    if (ioctl(fd_control, EM8300_IOCTL_SET_VIDEOMODE, &ioval) < 0) {
			printf("VO: [dxr3] Unable to set TV norm!\n");
	    }
	}
#endif
	
	
	/* libavcodec requires a width and height that is x|16 */
	aspect_save_orig(width, height);
	aspect_save_prescale(d_width, d_height);
#ifdef EM8300_IOCTL_GET_VIDEOMODE
	ioctl(fd_control, EM8300_IOCTL_GET_VIDEOMODE, &ioval);
	if (ioval == EM8300_VIDEOMODE_NTSC) {
		printf("VO: [dxr3] Setting up for NTSC.\n");
		aspect_save_screenres(352, 240);
	} else {
		printf("VO: [dxr3] Setting up for PAL/SECAM.\n");
		aspect_save_screenres(352, 288);
	}
#endif
	aspect(&s_width, &s_height, A_ZOOM);
	s_width -= s_width % 16;
	s_height -= s_height % 16;
	
	/* Try to figure out whether to use widescreen output or not */
	/* Anamorphic widescreen modes makes this a pain in the ass */
	tmp1 = abs(d_height - ((d_width / 4) * 3));
	tmp2 = abs(d_height - (int) (d_width / 2.35));
	if (tmp1 < tmp2) {
		ioval = EM8300_ASPECTRATIO_4_3;
		printf("VO: [dxr3] Setting aspect ratio to 4:3\n");
	} else {
		ioval = EM8300_ASPECTRATIO_16_9;
		printf("VO: [dxr3] Setting aspect ratio to 16:9\n");
	}
	ioctl(fd_control, EM8300_IOCTL_SET_ASPECTRATIO, &ioval);

#ifdef SPU_SUPPORT
#ifdef HAVE_FREETYPE
	s_width*=1.5;
#else
	s_width*=2;
	s_height*=2;
#endif

	osdpicbuf = calloc( 1,s_width * s_height);
	if (osdpicbuf == NULL) {
		printf("vo_dxr3: out of mem\n");
		return -1;
	}
	spued = (encodedata *) malloc(sizeof(encodedata));
	if (spued == NULL) {
	        free( osdpicbuf );
		printf("vo_dxr3:out of mem\n");
		return -1;
	}
	spubuf = (encodedata *) malloc(sizeof(encodedata));
	if (spubuf == NULL) {
	        free( osdpicbuf );
		free( spued );
		printf("vo_dxr3:out of mem\n");
		return -1;
	}
	osd_w = s_width;
	osd_h = s_height;
	osdpicbuf_w = s_width;
	osdpicbuf_h = s_height;
	
	spubuf->count=0;
	pixbuf_encode_rle( 0,0,osdpicbuf_w,osdpicbuf_h - 1,osdpicbuf,osdpicbuf_w,spubuf );

#endif

#ifdef HAVE_X11
	if (dxr3_overlay) {
		XVisualInfo vinfo;
		XSetWindowAttributes xswa;
		XSizeHints hint;
		unsigned long xswamask;
		Colormap cmap;
		XColor key_color;
		Window junkwindow;
		Screen *scr;
		int depth, red_shift, red_prec, green_shift, green_prec, blue_shift, blue_prec, acq_color;
		em8300_overlay_screen_t ovlscr;
		em8300_attribute_t ovlattr;

		vo_dx = (vo_screenwidth - d_width) / 2;
		vo_dy = (vo_screenheight - d_height) / 2;
		vo_dwidth = d_width;
		vo_dheight = d_height;
#ifdef HAVE_NEW_GUI
		if (use_gui) {
			guiGetEvent(guiSetShVideo, 0);
			XSetWindowBackground(mDisplay, vo_window, KEY_COLOR);
			XClearWindow(mDisplay, vo_window);
			XGetWindowAttributes(mDisplay, DefaultRootWindow(mDisplay), &xwin_attribs);
			depth = xwin_attribs.depth;
			if (depth != 15 && depth != 16 && depth != 24 && depth != 32) {
				depth = 24;
			}
			XMatchVisualInfo(mDisplay, mScreen, depth, TrueColor, &vinfo);
		} else
#endif
		{
			XGetWindowAttributes(mDisplay, DefaultRootWindow(mDisplay), &xwin_attribs);
			depth = xwin_attribs.depth;
			if (depth != 15 && depth != 16 && depth != 24 && depth != 32) {
				depth = 24;
			}
			XMatchVisualInfo(mDisplay, mScreen, depth, TrueColor, &vinfo);
			xswa.background_pixel = KEY_COLOR;
			xswa.border_pixel = 0;
			xswamask = CWBackPixel | CWBorderPixel;
			hint.y = vo_dy;
			hint.x = vo_dx;
			hint.base_width = hint.width = vo_dwidth;
			hint.base_height = hint.height = vo_dheight;
			hint.flags = PPosition | PSize;
			vo_window = XCreateWindow(mDisplay, mRootWin, hint.x, hint.y, hint.width, hint.height, 0, depth, CopyFromParent, vinfo.visual, xswamask, &xswa);
			vo_x11_classhint(mDisplay, vo_window, "Viewing Window");
			vo_hidecursor(mDisplay, vo_window);
			vo_x11_selectinput_witherr(mDisplay, vo_window, StructureNotifyMask | KeyPressMask | PropertyChangeMask);
			XSetStandardProperties(mDisplay, vo_window, "DXR3 Overlay", "DXR3 Overlay", None, NULL, 0, &hint);
			XSetWMNormalHints(mDisplay, vo_window, &hint);
			XMapWindow(mDisplay, vo_window);
			XFlush(mDisplay);
			XSync(mDisplay, False);
		}
		
		/* Start setting up overlay */
		XGetWindowAttributes(mDisplay, mRootWin, &xwin_attribs);
		overlay_set_screen(overlay_data, xwin_attribs.width, xwin_attribs.height, xwin_attribs.depth);
		overlay_read_state(overlay_data, NULL);

		/* Allocate keycolor */
		cmap = vo_x11_create_colormap(&vinfo);
		calculate_cvals(vinfo.red_mask, &red_shift, &red_prec);
		calculate_cvals(vinfo.green_mask, &green_shift, &green_prec);
		calculate_cvals(vinfo.blue_mask, &blue_shift, &blue_prec);
		
		key_color.red = ((KEY_COLOR >> 16) & 0xff) * 256;
		key_color.green = ((KEY_COLOR >> 8) & 0xff) * 256;
		key_color.blue = (KEY_COLOR & 0xff) * 256;
		key_color.pixel = (((key_color.red >> (16 - red_prec)) << red_shift) +
				   ((key_color.green >> (16 - green_prec)) << green_shift) +
				   ((key_color.blue >> (16 - blue_prec)) << blue_shift));
		key_color.flags = DoRed | DoGreen | DoBlue;
		if (!XAllocColor(mDisplay, cmap, &key_color)) {
			printf("VO: [dxr3] Unable to allocate keycolor!\n");
			return -1;
		}
		
		acq_color = ((key_color.red / 256) << 16) | ((key_color.green / 256) << 8) | key_color.blue;
		if (key_color.pixel != KEY_COLOR) {
			printf("VO: [dxr3] Unable to allocate exact keycolor, using closest match (%0x)\n", key_color.pixel);	
		}
		
		/* Set keycolor and activate overlay */
		XSetWindowBackground(mDisplay, vo_window, key_color.pixel);
		XClearWindow(mDisplay, vo_window);
		overlay_set_keycolor(overlay_data, key_color.pixel);
		overlay_set_mode(overlay_data, EM8300_OVERLAY_MODE_OVERLAY);
		overlay_set_mode(overlay_data, EM8300_OVERLAY_MODE_RECTANGLE);
	}
#endif

	return 0;
}

static void draw_alpha(int x, int y, int w, int h, unsigned char* src, unsigned char *srca, int srcstride)
{
#ifdef SPU_SUPPORT
	unsigned char *buf = &osdpicbuf[(y * osdpicbuf_w) + x];
	int by = 0;
	register int lx, ly;
	register int stride = 0;
	
	for (ly = 0; ly < h - 1; ly++) 
	 {
	  for(lx = 0; lx < w; lx++ )
	   if ( ( srca[stride + lx] )&&( src[stride + lx] >= 128 ) ) buf[by + lx] = 3;
	  by+=osdpicbuf_w;
	  stride+=srcstride;
	}
	pixbuf_encode_rle(x, y, osdpicbuf_w, osdpicbuf_h - 1, osdpicbuf, osdpicbuf_w, spued);
#endif
}

extern int vo_osd_changed_flag;
extern mp_osd_obj_t* vo_osd_list;

static void draw_osd(void)
{
#ifdef SPU_SUPPORT
 static int cleared = 0;
        int changed = 0;

	if ((disposd % 15) == 0) 
	{
		{
		 mp_osd_obj_t* obj = vo_osd_list;
		 vo_update_osd( osd_w,osd_h );
		 while( obj )
		  {
		   if ( obj->flags & OSDFLAG_VISIBLE ) { changed=1; break; }
		   obj=obj->next;
		  }
		}
		if ( changed )
		 {
		  vo_draw_text(osd_w, osd_h, draw_alpha);
		  memset(osdpicbuf, 0, s_width * s_height);
		  cleared=0;
		 }
		  else
		   {
		    if ( !cleared )
		     {
		      spued->count=spubuf->count;
		      memcpy( spued->data,spubuf->data,DATASIZE );
		      cleared=1;
		     }
		   }


		/* could stand some check here to see if the subpic hasn't changed
		 * as if it hasn't and we re-send it it will "blink" as the last one
		 * is turned off, and the new one (same one) is turned on
		 */
/*		Subpics are not stable yet =(
		expect lockups if you enable */
#if 1
		write(fd_spu, spued->data, spued->count);
#endif
	}
	disposd++;
#endif
}


static uint32_t draw_frame(uint8_t * src[])
{
	vo_mpegpes_t *p = (vo_mpegpes_t *) src[0];

#ifdef SPU_SUPPORT
	if (p->id == 0x20) {
		write(fd_spu, p->data, p->size);
	} else
#endif
		write(fd_video, p->data, p->size);
	return 0;
}

static void flip_page(void)
{
#ifdef HAVE_X11
	if (dxr3_overlay) {
		int event = vo_x11_check_events(mDisplay);
		if (event & VO_EVENT_RESIZE) {
			Window junkwindow;
			XGetWindowAttributes(mDisplay, vo_window, &xwin_attribs);
			XTranslateCoordinates(mDisplay, vo_window, mRootWin, -xwin_attribs.border_width, -xwin_attribs.border_width, &xwin_attribs.x, &xwin_attribs.y, &junkwindow);
			overlay_set_window(overlay_data, xwin_attribs.x, xwin_attribs.y, xwin_attribs.width, xwin_attribs.height);
		}
		if (event & VO_EVENT_EXPOSE) {
			Window junkwindow;
			XSetWindowBackground(mDisplay, vo_window, KEY_COLOR);
			XClearWindow(mDisplay, vo_window);
			XGetWindowAttributes(mDisplay, vo_window, &xwin_attribs);
			XTranslateCoordinates(mDisplay, vo_window, mRootWin, -xwin_attribs.border_width, -xwin_attribs.border_width, &xwin_attribs.x, &xwin_attribs.y, &junkwindow);
			overlay_set_window(overlay_data, xwin_attribs.x, xwin_attribs.y, xwin_attribs.width, xwin_attribs.height);
		}
	}
#endif

	if (dxr3_newsync) {
		ioctl(fd_control, EM8300_IOCTL_SCR_GET, &ioval);
		ioval <<= 1;
		if (vo_pts == 0) {
			ioval = 0;
			ioctl(fd_control, EM8300_IOCTL_SCR_SET, &ioval);
			pts_offset = 0;
		} else if ((vo_pts - pts_offset) < (ioval - 7200) || (vo_pts - pts_offset) > (ioval + 7200)) {
			ioval = (vo_pts + pts_offset) >> 1;
	    		ioctl(fd_control, EM8300_IOCTL_SCR_SET, &ioval);
			ioctl(fd_control, EM8300_IOCTL_SCR_GET, &ioval);
			pts_offset = vo_pts - (ioval << 1);
			if (pts_offset < 0) {
				pts_offset = 0;
			}
		}
		ioval = vo_pts + pts_offset;
		ioctl(fd_video, EM8300_IOCTL_SPU_SETPTS, &ioval);
		ioctl(fd_video, EM8300_IOCTL_VIDEO_SETPTS, &ioval);
		prev_pts = vo_pts;
	} else if (dxr3_prebuf) {
		ioctl(fd_spu, EM8300_IOCTL_SPU_SETPTS, &vo_pts);
		ioctl(fd_video, EM8300_IOCTL_VIDEO_SETPTS, &vo_pts);
	}
}

static uint32_t draw_slice(uint8_t *srcimg[], int stride[], int w, int h, int x0, int y0)
{
	return -1;
}

static void uninit(void)
{
	printf("VO: [dxr3] Uninitializing\n");
#ifdef HAVE_X11
	if (dxr3_overlay) {
		overlay_set_mode(overlay_data, EM8300_OVERLAY_MODE_OFF);
		overlay_release(overlay_data);
		
#ifdef HAVE_NEW_GUI
		if (!use_gui) {
#endif
			vo_x11_uninit();

#ifdef HAVE_NEW_GUI
		}
#endif
	}
#endif
	if (fd_video) {
		close(fd_video);
	}
	if (fd_spu) {
		close(fd_spu);
	}
	if (fd_control) {
		close(fd_control);
	}
#ifdef SPU_SUPPORT
	if(osdpicbuf) {
		free(osdpicbuf);
	}
	if(spued) {
		free(spued);
	}
#endif
}

static void check_events(void)
{
}

static uint32_t preinit(const char *arg)
{
	char devname[80];
	int fdflags = O_WRONLY;

	/* Parse commandline */
	while (arg) {
		if (!strncmp("prebuf", arg, 6) && !dxr3_prebuf) {
			printf("VO: [dxr3] Enabling prebuffering.\n");
			dxr3_prebuf = 1;
			fdflags |= O_NONBLOCK;
		} else if (!strncmp("sync", arg, 4) && !dxr3_newsync) {
			printf("VO: [dxr3] Using new sync engine.\n");
			dxr3_newsync = 1;
		} else if (!strncmp("overlay", arg, 7) && !dxr3_overlay) {
#ifdef HAVE_X11
			printf("VO: [dxr3] Using overlay.\n");
			dxr3_overlay = 1;
#else
			printf("VO: [dxr3] Error: You need to compile mplayer with x11 libraries and headers installed to use overlay.\n");
#endif
		} else if (!strncmp("norm=", arg, 5)) {
			arg += 5;
			// dxr3_norm is 0 (-> don't change norm) by default
			// but maybe someone changes this in the future

			printf("VO: [dxr3] Will set TV norm to: ");
			
			if (*arg == '5') {
			    dxr3_norm = 5;
			    printf("NTSC");
			} else if (*arg == '4') {
			    dxr3_norm = 4;
			    printf("PAL-60");
			} else if (*arg == '3') {
			    dxr3_norm = 3;
			    printf("PAL");
			} else if (*arg == '2') {
			    dxr3_norm = 2;
			    printf("Auto-adjust to movie frame rate (PAL/PAL60)");
			} else if (*arg == '1') {
			    dxr3_norm = 1;
			    printf("Auto-adjust to movie frame rate (PAL/NTSC)");
			} else if (*arg == '0') {
			    dxr3_norm = 0;
			    printf("Use current norm");
			} else {
			    dxr3_norm = 0;
			    printf("Unknown norm supplied. Use current norm");
			}
			
			printf("\n");
		} else if (arg[0] == '0' || arg[0] == '1' || arg[0] == '2' || arg[0] == '3') {
			dxr3_device_num = arg[0];
		}
		
		arg = strchr(arg, ':');
		if (arg) {
			arg++;
		}
	}
	

	/* Open the control interface */
	sprintf(devname, "/dev/em8300-%d", dxr3_device_num);
	fd_control = open(devname, fdflags);
	if (fd_control < 1) {
		/* Fall back to old naming scheme */
		printf("VO: [dxr3] Error opening %s for writing, trying /dev/em8300 instead\n", devname);
		sprintf(devname, "/dev/em8300");
		fd_control = open(devname, fdflags);
		if (fd_control < 1) {
			printf("VO: [dxr3] Error opening /dev/em8300 for writing as well!\nBailing\n");
			return -1;
		}
	} else {
		printf("VO: [dxr3] Opened %s\n", devname);
	}

	/* Open the video interface */
	sprintf(devname, "/dev/em8300_mv-%d", dxr3_device_num);
	fd_video = open(devname, fdflags);
	if (fd_video < 0) {
		/* Fall back to old naming scheme */
		printf("VO: [dxr3] Error opening %s for writing, trying /dev/em8300_mv instead\n", devname);
		sprintf(devname, "/dev/em8300_mv");
		fd_video = open(devname, fdflags);
		if (fd_video < 0) {
			printf("VO: [dxr3] Error opening /dev/em8300_mv for writing as well!\nBailing\n");
			uninit();
			return -1;
		}
	} else {
		printf("VO: [dxr3] Opened %s\n", devname);
	}
	strcpy(fdv_name, devname);
	
	/* Open the subpicture interface */
	fdflags |= O_NONBLOCK;
	sprintf(devname, "/dev/em8300_sp-%d", dxr3_device_num);
	fd_spu = open(devname, fdflags);
	if (fd_spu < 0) {
		/* Fall back to old naming scheme */
		printf("VO: [dxr3] Error opening %s for writing, trying /dev/em8300_sp instead\n", devname);
		sprintf(devname, "/dev/em8300_sp");
		fd_spu = open(devname, fdflags);
		if (fd_spu < 0) {
			printf("VO: [dxr3] Error opening /dev/em8300_sp for writing as well!\nBailing\n");
			uninit();
			return -1;
		}
	} else {
		printf("VO: [dxr3] Opened %s\n", devname);
	}
	strcpy(fds_name, devname);
	
#ifdef HAVE_X11
	if (dxr3_overlay) {
	
		/* Fucked up hack needed to enable overlay.
		 * Will be removed as soon as I figure out
		 * how to make it work like it should
		 */
		Display *dpy;
		overlay_t *ov;
		XWindowAttributes attribs;
		
		dpy = XOpenDisplay(NULL);
	    	if (!dpy) {
			printf("VO: [dxr3] Unable to open display during overlay hack setup!\n");
			return -1;
		}
		XGetWindowAttributes(dpy, RootWindow(dpy, DefaultScreen(dpy)), &attribs);
		ov = overlay_init(fd_control);
		overlay_set_screen(ov, attribs.width, attribs.height, PlanesOfScreen(ScreenOfDisplay(dpy, 0)));
		overlay_read_state(ov, NULL);
		overlay_set_keycolor(ov, KEY_COLOR);
		overlay_set_mode(ov, EM8300_OVERLAY_MODE_OVERLAY);
		overlay_set_mode(ov, EM8300_OVERLAY_MODE_RECTANGLE);
		overlay_release(ov);
		XCloseDisplay(dpy);
		/* End of fucked up hack */
		
		/* Initialize overlay and X11 */
		overlay_data = overlay_init(fd_control);
#ifdef HAVE_NEW_GUI
		if (!use_gui) {
#endif
			if (!vo_init()) {
				printf("VO: [dxr3] Unable to init x11!\n");
				return -1;
			}
#ifdef HAVE_NEW_GUI
		}
#endif
	}
#endif

	if (dxr3_newsync) {
		ioctl(fd_control, EM8300_IOCTL_SCR_GET, &ioval);
		pts_offset = vo_pts - (ioval << 1);
		if (pts_offset < 0) {
			pts_offset = 0;
		}
	}

	return 0;
}

/* Begin overlay.c */
static int update_parameters(overlay_t *o)
{
    overlay_set_attribute(o, EM9010_ATTRIBUTE_XOFFSET, o->xoffset);
    overlay_set_attribute(o, EM9010_ATTRIBUTE_YOFFSET, o->yoffset);
    overlay_set_attribute(o, EM9010_ATTRIBUTE_XCORR, o->xcorr);
    overlay_set_attribute(o, EM9010_ATTRIBUTE_STABILITY, o->stability);
    overlay_set_attribute(o, EM9010_ATTRIBUTE_JITTER, o->jitter);
    return 0;
}

static int overlay_set_attribute(overlay_t *o, int attribute, int value)
{
    em8300_attribute_t attr;
    
    attr.attribute = attribute;
    attr.value = value;
    if (ioctl(o->dev, EM8300_IOCTL_OVERLAY_SET_ATTRIBUTE, &attr)==-1)
        {
	     perror("Failed set attribute");
	     return -1;
        }

    return 0;
}

static overlay_t *overlay_init(int dev)
{
    overlay_t *o;

    o = (overlay_t *) malloc(sizeof(overlay_t));

    if(!o)
	return NULL;

    memset(o,sizeof(overlay_t),0);

    o->dev = dev;
    o->xres = 1280; o->yres=1024; o->xcorr=1000;
    o->color_interval=10;

    return o;
}

static int overlay_release(overlay_t *o)
{
    if(o)
	free(o);

    return 0;
}
#define TYPE_INT 1
#define TYPE_XINT 2
#define TYPE_COEFF 3
#define TYPE_FLOAT 4

struct lut_entry {
    char *name;
    int type;
    void *ptr;
};

static struct lut_entry *new_lookuptable(overlay_t *o)
{
    struct lut_entry m[] = {
	{"xoffset", TYPE_INT, &o->xoffset},
	{"yoffset", TYPE_INT, &o->yoffset},
	{"xcorr", TYPE_INT, &o->xcorr},
	{"jitter", TYPE_INT, &o->jitter},
	{"stability", TYPE_INT, &o->stability},
	{"keycolor", TYPE_XINT, &o->keycolor},
	{"colcal_upper", TYPE_COEFF, &o->colcal_upper[0]},
	{"colcal_lower", TYPE_COEFF, &o->colcal_lower[0]},
	{"color_interval", TYPE_FLOAT, &o->color_interval},
	{0,0,0}
    },*p;

    p = malloc(sizeof(m));
    memcpy(p,m,sizeof(m));
    return p;
}

static int lookup_parameter(overlay_t *o, struct lut_entry *lut, char *name, void **ptr, int *type) {
    int i;

    for(i=0; lut[i].name; i++) {
	if(!strcmp(name,lut[i].name)) {
	    *ptr = lut[i].ptr;
	    *type = lut[i].type;
	    return 1;
	}
    }
    return 0;
}

static int overlay_read_state(overlay_t *o, char *p)
{
    char *a,*tok;
    char path[128],fname[128],tmp[128],line[256];
    FILE *fp;
    struct lut_entry *lut;
    void *ptr;
    int type;
    int j;
	
    if(!p) {
	strcpy(fname,getenv("HOME"));
	strcat(fname,"/.overlay");	    
    } else
	strcpy(fname,p);
    
    sprintf(tmp,"/res_%dx%dx%d",o->xres,o->yres,o->depth);
    strcat(fname,tmp);

    if(!(fp=fopen(fname,"r")))
	return -1;

    lut = new_lookuptable(o);
    
    while(!feof(fp)) {
	if(!fgets(line,256,fp))
	    break;
	tok=strtok(line," ");
	if(lookup_parameter(o,lut,tok,&ptr,&type)) {
	    tok=strtok(NULL," ");
	    switch(type) {
	    case TYPE_INT:
		sscanf(tok,"%d",(int *)ptr);
		break;
	    case TYPE_XINT:
		sscanf(tok,"%x",(int *)ptr);
		break;
	    case TYPE_FLOAT:
		sscanf(tok,"%f",(float *)ptr);
		break;
	    case TYPE_COEFF:
		for(j=0;j<3;j++) {
		    sscanf(tok,"%f",&((struct coeff *)ptr)[j].k);
		    tok=strtok(NULL," ");
		    sscanf(tok,"%f",&((struct coeff *)ptr)[j].m);
		    tok=strtok(NULL," ");
		}
		break;	    
	    }
	    
	}	
    }

    update_parameters(o);
    
    free(lut);
    fclose(fp);
    return 0;
}

static void overlay_update_params(overlay_t *o) {
    update_parameters(o);
}

static int overlay_write_state(overlay_t *o, char *p)	
{
    char *a;
    char path[128],fname[128],tmp[128];
    FILE *fp;
    char line[256],*tok;
    struct lut_entry *lut;
    int i,j;
	
    if(!p) {
	strcpy(fname,getenv("HOME"));
	strcat(fname,"/.overlay");	    
    } else
	strcpy(fname,p);

    if(access(fname, W_OK|X_OK|R_OK)) {
	if(mkdir(fname,0766))
	    return -1;
    }	
    
    sprintf(tmp,"/res_%dx%dx%d",o->xres,o->yres,o->depth);
    strcat(fname,tmp);
    
    if(!(fp=fopen(fname,"w")))
	return -1;
    
    lut = new_lookuptable(o);

    for(i=0; lut[i].name; i++) {	
	fprintf(fp,"%s ",lut[i].name);
	switch(lut[i].type) {
	case TYPE_INT:
	    fprintf(fp,"%d\n",*(int *)lut[i].ptr);
	    break;
	case TYPE_XINT:
	    fprintf(fp,"%06x\n",*(int *)lut[i].ptr);
	    break;
	case TYPE_FLOAT:
	    fprintf(fp,"%f\n",*(float *)lut[i].ptr);
	    break;
	case TYPE_COEFF:
	    for(j=0;j<3;j++) 
		fprintf(fp,"%f %f ",((struct coeff *)lut[i].ptr)[j].k,
			((struct coeff *)lut[i].ptr)[j].m);
	    fprintf(fp,"\n");
	    break;	    
	}
    }

    fclose(fp);
    return 0;
}

static int overlay_set_screen(overlay_t *o, int xres, int yres, int depth)
{
   em8300_overlay_screen_t scr;

   o->xres = xres;
   o->yres = yres;
   o->depth = depth;

   scr.xsize = xres;
   scr.ysize = yres;
   
   if (ioctl(o->dev, EM8300_IOCTL_OVERLAY_SETSCREEN, &scr)==-1)
        {
            perror("Failed set screen...exiting");
            return -1;
	}
   return 0;
}

static int overlay_set_mode(overlay_t *o, int mode)
{
    if (ioctl(o->dev, EM8300_IOCTL_OVERLAY_SETMODE, &mode)==-1) {
	perror("Failed enabling overlay..exiting");
	return -1;
    }
    return 0;
}

static int overlay_set_window(overlay_t *o, int xpos,int ypos,int width,int height)
{
    em8300_overlay_window_t win;
    win.xpos = xpos;
    win.ypos = ypos;
    win.width = width;
    win.height = height;

    if (ioctl(o->dev, EM8300_IOCTL_OVERLAY_SETWINDOW, &win)==-1)
        {
            perror("Failed resizing window");
            return -1;
        }
    return 0;
}

static int overlay_set_bcs(overlay_t *o, int brightness, int contrast, int saturation)
{
    em8300_bcs_t bcs;
    bcs.brightness = brightness;
    bcs.contrast = contrast;
    bcs.saturation = saturation;

    if (ioctl(o->dev, EM8300_IOCTL_GETBCS, &bcs)==-1)
        {
            perror("Failed setting bcs");
            return -1;
        }
    return 0;
}

static int col_interp(float x, struct coeff c)
{
    float y;
    y = x*c.k + c.m;
    if(y > 255)
	y = 255;
    if(y < 0)
	y = 0;
    return rint(y);
}

static int overlay_set_keycolor(overlay_t *o, int color) {
    int r = (color & 0xff0000) >> 16;
    int g = (color & 0x00ff00) >> 8;
    int b = (color & 0x0000ff);
    float ru,gu,bu;
    float rl,gl,bl;
    int upper,lower;

    ru = r+o->color_interval;
    gu = g+o->color_interval;
    bu = b+o->color_interval;

    rl = r-o->color_interval;
    gl = g-o->color_interval;
    bl = b-o->color_interval;
    
    upper = (col_interp(ru, o->colcal_upper[0]) << 16) |
	    (col_interp(gu, o->colcal_upper[1]) << 8) |
	    (col_interp(bu, o->colcal_upper[2]));

    lower = (col_interp(rl, o->colcal_lower[0]) << 16) |
	    (col_interp(gl, o->colcal_lower[1]) << 8) |
	    (col_interp(bl, o->colcal_lower[2]));

    //printf("0x%06x 0x%06x\n",upper,lower);
    overlay_set_attribute(o,EM9010_ATTRIBUTE_KEYCOLOR_UPPER,upper);
    overlay_set_attribute(o,EM9010_ATTRIBUTE_KEYCOLOR_LOWER,lower);
    return 0;
}

static void least_sq_fit(int *x, int *y, int n, float *k, float *m)
{
    float sx=0,sy=0,sxx=0,sxy=0;
    float delta,b;
    int i;

    for(i=0; i < n; i++) {
	sx=sx+x[i];
	sy=sy+y[i];
	sxx=sxx+x[i]*x[i];
	sxy=sxy+x[i]*y[i];
    }

    delta=sxx*n-sx*sx;

    *m=(sxx*sy-sx*sxy)/delta;
    *k=(sxy*n-sx*sy)/delta;
}

static int overlay_autocalibrate(overlay_t *o, pattern_drawer_cb pd, void *arg)
{
    em8300_overlay_calibrate_t cal;
    em8300_overlay_window_t win;
    int x[256],r[256],g[256],b[256],n;
    float k,m;

    int i;

    o->draw_pattern=pd;
    o->dp_arg = arg;

    overlay_set_mode(o, EM8300_OVERLAY_MODE_OVERLAY);
    overlay_set_screen(o, o->xres, o->yres, o->depth);

    /* Calibrate Y-offset */

    o->draw_pattern(0x0000ff, 0, 0, 0, 355, 1, o->dp_arg);

    cal.cal_mode = EM8300_OVERLAY_CALMODE_YOFFSET;
    if (ioctl(o->dev, EM8300_IOCTL_OVERLAY_CALIBRATE, &cal))
        {
	    perror("Failed getting Yoffset values...exiting");
	    return -1;
        }
    o->yoffset = cal.result;
    printf("Yoffset: %d\n",cal.result);

    /* Calibrate X-offset */

    o->draw_pattern(0x0000ff, 0, 0, 0, 2, 288, o->dp_arg);

    cal.cal_mode = EM8300_OVERLAY_CALMODE_XOFFSET;
    if (ioctl(o->dev, EM8300_IOCTL_OVERLAY_CALIBRATE, &cal))
	{
 	    perror("Failed getting Xoffset values...exiting");
 	    return -1;
	}
    o->xoffset = cal.result;
    printf("Xoffset: %d\n",cal.result);

    /* Calibrate X scale correction */

    o->draw_pattern(0x0000ff, 0, 355, 0, 2, 288, o->dp_arg);

    cal.cal_mode = EM8300_OVERLAY_CALMODE_XCORRECTION;
    if (ioctl(o->dev, EM8300_IOCTL_OVERLAY_CALIBRATE, &cal))
	{
 	    perror("Failed getting Xoffset values...exiting");
 	    return -1;
	}
    printf("Xcorrection: %d\n",cal.result);
    o->xcorr = cal.result;

    win.xpos = 10;
    win.ypos = 10;
    win.width = o->xres-20;
    win.height = o->yres-20;
    if (ioctl(o->dev, EM8300_IOCTL_OVERLAY_SETWINDOW, &win)==-1) {
	perror("Failed resizing window");
	exit(1);
    }

    /* Calibrate key color upper limit */

    for(i=128,n=0; i <= 0xff; i+=4) {
	o->draw_pattern(i | (i << 8) | (i << 16), 0,
			(o->xres-200)/2,0,200,o->yres,o->dp_arg);

	cal.arg = i;
	cal.arg2 = 1;
	cal.cal_mode = EM8300_OVERLAY_CALMODE_COLOR;

	if (ioctl(o->dev, EM8300_IOCTL_OVERLAY_CALIBRATE, &cal))
	    {
		return -1 ;
	    }

	x[n] = i;
	r[n] = (cal.result>>16)&0xff;
	g[n] = (cal.result>>8)&0xff;
	b[n] = (cal.result)&0xff;
	n++;
    }

    least_sq_fit(x,r,n,&o->colcal_upper[0].k,&o->colcal_upper[0].m);
    least_sq_fit(x,g,n,&o->colcal_upper[1].k,&o->colcal_upper[1].m);
    least_sq_fit(x,b,n,&o->colcal_upper[2].k,&o->colcal_upper[2].m);

    /* Calibrate key color lower limit */

    for(i=128,n=0; i <= 0xff; i+=4) {
	o->draw_pattern(i | (i << 8) | (i << 16), 0xffffff,
			(o->xres-200)/2,0,200,o->yres, o->dp_arg);

	cal.arg = i;
	cal.arg2 = 2;
	cal.cal_mode = EM8300_OVERLAY_CALMODE_COLOR;

	if (ioctl(o->dev, EM8300_IOCTL_OVERLAY_CALIBRATE, &cal))
	    {
		return -1 ;
	    }
	x[n] = i;
	r[n] = (cal.result>>16)&0xff;
	g[n] = (cal.result>>8)&0xff;
	b[n] = (cal.result)&0xff;
	n++;
    }

    least_sq_fit(x,r,n,&o->colcal_lower[0].k,&o->colcal_lower[0].m);
    least_sq_fit(x,g,n,&o->colcal_lower[1].k,&o->colcal_lower[1].m);
    least_sq_fit(x,b,n,&o->colcal_lower[2].k,&o->colcal_lower[2].m);

    overlay_set_mode(o, EM8300_OVERLAY_MODE_OFF);

    return 0;
}


static int overlay_signalmode(overlay_t *o, int mode) {
	if(ioctl(o->dev, EM8300_IOCTL_OVERLAY_SIGNALMODE, &mode) ==-1) {
	    perror("Failed set signal mix");
	    return -1;
	}
	return 0;
}
/* End overlay.c */
