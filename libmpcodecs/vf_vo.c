#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../config.h"
#include "../mp_msg.h"

#include "../mp_image.h"
#include "vf.h"

#include "../libvo/video_out.h"

//===========================================================================//

#define video_out ((vo_functions_t*)(vf->priv))

static int config(struct vf_instance_s* vf,
        int width, int height, int d_width, int d_height,
	unsigned int flags, unsigned int outfmt){
    if(video_out->config(width,height,d_width,d_height,flags,"MPlayer",outfmt,NULL))
	return 0;
    return 1;
}

static int control(struct vf_instance_s* vf,
        int request, void* data){
    // return video_out->control(request,data);
    return -3;
}

static int query_format(struct vf_instance_s* vf, unsigned int fmt){
    return video_out->control(VOCTRL_QUERY_FORMAT,&fmt);
}

static void get_image(struct vf_instance_s* vf,
        mp_image_t *mpi){
    if(vo_directrendering) 
	video_out->control(VOCTRL_GET_IMAGE,mpi);
}

static void put_image(struct vf_instance_s* vf,
        mp_image_t *mpi){
  // first check, maybe the vo/vf plugin implements draw_image using mpi:
  if(video_out->control(VOCTRL_DRAW_IMAGE,mpi)==VO_TRUE) return; // done.
  // nope, fallback to old draw_frame/draw_slice:
  if(!(mpi->flags&(MP_IMGFLAG_DIRECT|MP_IMGFLAG_DRAW_CALLBACK))){
    // blit frame:
    if(mpi->flags&MP_IMGFLAG_PLANAR)
        video_out->draw_slice(mpi->planes,mpi->stride,mpi->w,mpi->h,mpi->x,mpi->y);
    else
        video_out->draw_frame(mpi->planes);
  }
}

static void draw_slice(struct vf_instance_s* vf,
        unsigned char* src, int* stride, int w,int h, int x, int y){
    video_out->draw_slice(src,stride,w,h,x,y);
}

static void uninit(struct vf_instance_s* vf){
//    video_out->uninit();
}

//===========================================================================//

static int open(vf_instance_t *vf, char* args){
    vf->config=config;
    vf->control=control;
    vf->query_format=query_format;
    vf->get_image=get_image;
    vf->put_image=put_image;
    vf->draw_slice=draw_slice;
    vf->uninit=uninit;
    vf->priv=(void*)args; // video_out
    if(!video_out) return 0; // no vo ?
//    if(video_out->preinit(args)) return 0; // preinit failed
    return 1;
}

vf_info_t vf_info_vo = {
    "libvo wrapper",
    "vo",
    "A'rpi",
    "for internal use",
    open
};

//===========================================================================//
