#include <stdio.h>
#include <stdlib.h>

#include "config.h"
#ifdef USE_DIRECTSHOW

#include "mp_msg.h"
#include "help_mp.h"

#include "vd_internal.h"

#include "loader/dshow/DS_VideoDecoder.h"

static vd_info_t info = {
	"DirectShow video codecs",
	"dshow",
	VFM_DSHOW,
	"A'rpi",
	"based on http://avifile.sf.net",
	"win32 codecs"
};

LIBVD_EXTERN(dshow)

// to set/get/query special features/parameters
static int control(sh_video_t *sh,int cmd,void* arg,...){
    switch(cmd){
    case VDCTRL_QUERY_MAX_PP_LEVEL:
	return 4;
    case VDCTRL_SET_PP_LEVEL:
	if(!sh->context) return CONTROL_ERROR;
	DS_VideoDecoder_SetValue(sh->context,"Quality",*((int*)arg));
	return CONTROL_OK;

// TODO: query/set video options (brightness contrast etc)
//        DS_VideoDecoder_SetValue(ds_vdec,item,value);
	
    }
    return CONTROL_UNKNOWN;
}

// init driver
static int init(sh_video_t *sh){
    unsigned int out_fmt;
    if(!(sh->context=DS_VideoDecoder_Open(sh->codec->dll,&sh->codec->guid, sh->bih, 0, 0))){
        mp_msg(MSGT_DECVIDEO,MSGL_ERR,MSGTR_MissingDLLcodec,sh->codec->dll);
        mp_msg(MSGT_DECVIDEO,MSGL_HINT,"Maybe you forget to upgrade your win32 codecs?? It's time to download the new\n");
        mp_msg(MSGT_DECVIDEO,MSGL_HINT,"package from:  ftp://mplayerhq.hu/MPlayer/releases/w32codec.zip  !\n");
	return 0;
    }
    mpcodecs_config_vo(sh,sh->disp_w,sh->disp_h,IMGFMT_YUY2);
    out_fmt=sh->codec->outfmt[sh->outfmtidx];
    switch(out_fmt){
    case IMGFMT_YUY2:
    case IMGFMT_UYVY:
	DS_VideoDecoder_SetDestFmt(sh->context,16,out_fmt);break; // packed YUV
    case IMGFMT_YV12:
    case IMGFMT_I420:
    case IMGFMT_IYUV:
	DS_VideoDecoder_SetDestFmt(sh->context,12,out_fmt);break; // planar YUV
    default:
	DS_VideoDecoder_SetDestFmt(sh->context,out_fmt&255,0);    // RGB/BGR
    }
    DS_VideoDecoder_StartInternal(sh->context);
    mp_msg(MSGT_DECVIDEO,MSGL_V,"INFO: Win32/DShow video codec init OK!\n");
    return 1;
}

// uninit driver
static void uninit(sh_video_t *sh){
    DS_VideoDecoder_Destroy(sh->context);
}

//mp_image_t* mpcodecs_get_image(sh_video_t *sh, int mp_imgtype, int mp_imgflag, int w, int h);

// decode a frame
static mp_image_t* decode(sh_video_t *sh,void* data,int len,int flags){
    mp_image_t* mpi;
    if(len<=0) return NULL; // skipped frame
    
    if(flags&3){
	// framedrop:
        DS_VideoDecoder_DecodeInternal(sh->context, data, len, 0, 0);
	return NULL;
    }
    
    mpi=mpcodecs_get_image(sh, MP_IMGTYPE_TEMP, 0 /*MP_IMGFLAG_ACCEPT_STRIDE*/, 
	sh->disp_w, sh->disp_h);
    
    if(!mpi){	// temporary!
	printf("couldn't allocate image for cinepak codec\n");
	return NULL;
    }

    DS_VideoDecoder_DecodeInternal(sh->context, data, len, 0, mpi->planes[0]);

    return mpi;
}

#endif
