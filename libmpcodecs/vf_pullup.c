#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../config.h"
#include "../mp_msg.h"
#include "../cpudetect.h"

#include "img_format.h"
#include "mp_image.h"
#include "vf.h"

#include "../libvo/fastmemcpy.h"

#include "pullup.h"

struct vf_priv_s {
	struct pullup_context *ctx;
	int init;
	int fakecount;
};

static inline void *my_memcpy_pic(void * dst, void * src, int bytesPerLine, int height, int dstStride, int srcStride)
{
	int i;
	void *retval=dst;

	for(i=0; i<height; i++)
	{
		memcpy(dst, src, bytesPerLine);
		src+= srcStride;
		dst+= dstStride;
	}

	return retval;
}

static void init_pullup(struct vf_instance_s* vf, mp_image_t *mpi)
{
	struct pullup_context *c = vf->priv->ctx;

	if (mpi->flags & MP_IMGFLAG_PLANAR) {
		c->format = PULLUP_FMT_Y;
		c->nplanes = 3;
		pullup_preinit_context(c);
		c->bpp[0] = c->bpp[1] = c->bpp[2] = 8;
		c->w[0] = mpi->w;
		c->h[0] = mpi->h;
		c->w[1] = c->w[2] = mpi->chroma_width;
		c->h[1] = c->h[2] = mpi->chroma_height;
		c->stride[0] = mpi->width;
		c->stride[1] = c->stride[2] = mpi->chroma_width;
		c->background[1] = c->background[2] = 128;
	}

	c->junk_left = c->junk_right = 1;
	c->junk_top = c->junk_bottom = 4;

	if (gCpuCaps.hasMMX) c->cpu |= PULLUP_CPU_MMX;
	if (gCpuCaps.hasMMX2) c->cpu |= PULLUP_CPU_MMX2;
	if (gCpuCaps.has3DNow) c->cpu |= PULLUP_CPU_3DNOW;
	if (gCpuCaps.has3DNowExt) c->cpu |= PULLUP_CPU_3DNOWEXT;
	if (gCpuCaps.hasSSE) c->cpu |= PULLUP_CPU_SSE;
	if (gCpuCaps.hasSSE2) c->cpu |= PULLUP_CPU_SSE2;
	
	pullup_init_context(c);

	vf->priv->init = 1;
}


static void get_image(struct vf_instance_s* vf, mp_image_t *mpi)
{
	struct pullup_context *c = vf->priv->ctx;
	struct pullup_buffer *b;
	
	if (mpi->type == MP_IMGTYPE_STATIC) return;

	if (!vf->priv->init) init_pullup(vf, mpi);

	b = pullup_get_buffer(c, 2);
	if (!b) return; /* shouldn't happen... */

	mpi->priv = b;
	
	mpi->planes[0] = b->planes[0];
	mpi->planes[1] = b->planes[1];
	mpi->planes[2] = b->planes[2];
	mpi->stride[0] = c->stride[0];
	mpi->stride[1] = c->stride[1];
	mpi->stride[2] = c->stride[2];

	mpi->flags |= MP_IMGFLAG_DIRECT;
	mpi->flags &= ~MP_IMGFLAG_DRAW_CALLBACK;
	
	//mpi->width = mpi->stride[0];
}

static int put_image(struct vf_instance_s* vf, mp_image_t *mpi)
{
	struct pullup_context *c = vf->priv->ctx;
	struct pullup_buffer *b;
	struct pullup_frame *f;
	mp_image_t *dmpi;
	int ret;
	int p;
	
	if (!vf->priv->init) init_pullup(vf, mpi);
	
	if (mpi->flags & MP_IMGFLAG_DIRECT) {
		b = mpi->priv;
		mpi->priv = 0;
	} else {
		b = pullup_get_buffer(c, 2);
		if (!b) {
			mp_msg(MSGT_VFILTER,MSGL_ERR,"Could not get buffer from pullup!\n");
			f = pullup_get_frame(c);
			pullup_release_frame(f);
			return 0;
		}
		memcpy_pic(b->planes[0], mpi->planes[0], mpi->w, mpi->h,
			c->stride[0], mpi->stride[0]);
		if (mpi->flags & MP_IMGFLAG_PLANAR) {
			memcpy_pic(b->planes[1], mpi->planes[1],
				mpi->chroma_width, mpi->chroma_height,
				c->stride[1], mpi->stride[1]);
			memcpy_pic(b->planes[2], mpi->planes[2],
				mpi->chroma_width, mpi->chroma_height,
				c->stride[2], mpi->stride[2]);
		}
	}

	p = mpi->fields & MP_IMGFIELD_TOP_FIRST ? 0 :
		(mpi->fields & MP_IMGFIELD_ORDERED ? 1 : 0);
	//printf("p=%d\n", p);
	pullup_submit_field(c, b, p);
	pullup_submit_field(c, b, p^1);
	if (mpi->fields & MP_IMGFIELD_REPEAT_FIRST)
		pullup_submit_field(c, b, p);

	pullup_release_buffer(b, 2);

	f = pullup_get_frame(c);

	/* Fake yes for first few frames (buffer depth) to keep from
	 * breaking A/V sync with G1's bad architecture... */
	if (!f) return vf->priv->fakecount ? (--vf->priv->fakecount,1) : 0;

	if (f->length < 2) {
		pullup_release_frame(f);
		f = pullup_get_frame(c);
		if (!f) return 0;
		if (f->length < 2) {
			pullup_release_frame(f);
			return 0;
		}
	}

	/* If the frame isn't already exportable... */
	if (!f->buffer) {
		/* FIXME: DR disabled for now */
		if (0) {
			dmpi = vf_get_image(vf->next, mpi->imgfmt,
				MP_IMGTYPE_TEMP, MP_IMGFLAG_ACCEPT_STRIDE,
				mpi->width, mpi->height);
			/* FIXME: draw into DR buffer */
			return vf_next_put_image(vf, dmpi);
		}
		pullup_pack_frame(c, f);
	}
	dmpi = vf_get_image(vf->next, mpi->imgfmt,
		MP_IMGTYPE_EXPORT, MP_IMGFLAG_ACCEPT_STRIDE,
		mpi->width, mpi->height);

	dmpi->planes[0] = f->buffer->planes[0];
	dmpi->planes[1] = f->buffer->planes[1];
	dmpi->planes[2] = f->buffer->planes[2];
		
	dmpi->stride[0] = c->stride[0];
	dmpi->stride[1] = c->stride[1];
	dmpi->stride[2] = c->stride[2];
	
	ret = vf_next_put_image(vf, dmpi);
	pullup_release_frame(f);
	return ret;
}

static int query_format(struct vf_instance_s* vf, unsigned int fmt)
{
	/* FIXME - support more formats */
	switch (fmt) {
	case IMGFMT_YV12:
	case IMGFMT_IYUV:
	case IMGFMT_I420:
		return vf_next_query_format(vf, fmt);
	}
	return 0;
}

static int config(struct vf_instance_s* vf,
        int width, int height, int d_width, int d_height,
	unsigned int flags, unsigned int outfmt)
{
	if (height&3) return 0;
	return vf_next_config(vf, width, height, d_width, d_height, flags, outfmt);
}

static void uninit(struct vf_instance_s* vf)
{
	pullup_free_context(vf->priv->ctx);
	free(vf->priv);
}

static int open(vf_instance_t *vf, char* args)
{
	struct vf_priv_s *p;
	vf->get_image = get_image;
	vf->put_image = put_image;
	vf->config = config;
	vf->query_format = query_format;
	vf->uninit = uninit;
	vf->default_reqs = VFCAP_ACCEPT_STRIDE;
	vf->priv = p = calloc(1, sizeof(struct vf_priv_s));
	p->ctx = pullup_alloc_context();
	p->fakecount = 2;
	return 1;
}

vf_info_t vf_info_pullup = {
    "pullup (from field sequence to frames)",
    "pullup",
    "Rich Felker",
    "",
    open,
    NULL
};


