
#define VCODEC_DIVX4 1
#define ACODEC_VBRMP3 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

#include "mp_msg.h"
#include "help_mp.h"

#include "codec-cfg.h"

#include "stream.h"
#include "demuxer.h"
#include "stheader.h"

#include "aviwrite.h"

#include "libvo/video_out.h"

#include "dec_audio.h"
#include "dec_video.h"

#include <encore2.h>

#include "get_path.c"

//--------------------------

// cache2:
#ifdef USE_STREAM_CACHE
extern int cache_fill_status;
#else
#define cache_fill_status 0
#endif

// AVI demuxer params:
static float c_total=0;
int delay_corrected=1;

char *audio_codec=NULL; // override audio codec
char *video_codec=NULL; // override video codec
int audio_family=-1;     // override audio codec family 
int video_family=-1;     // override video codec family 

// audio stream skip/resync functions requires only for seeking.
// (they should be implemented in the audio codec layer)
//void skip_audio_frame(sh_audio_t *sh_audio){}
//void resync_audio_stream(sh_audio_t *sh_audio){}

int verbose=5; // must be global!

double video_time_usage=0;
double vout_time_usage=0;
static double audio_time_usage=0;
static int total_time_usage_start=0;
static int benchmark=0;

int force_fps=0;

#include "libmpeg2/mpeg2.h"
#include "libmpeg2/mpeg2_internal.h"

static unsigned char* vo_image=NULL;
static unsigned char* vo_image_ptr=NULL;
static int vo_w,vo_h;

static uint32_t draw_slice(uint8_t *src[], int stride[], int w,int h, int x0,int y0){
  int y;
//  printf("draw_slice %dx%d %d;%d\n",w,h,x,y);
  
  // copy Y:
  for(y=0;y<h;y++){
      unsigned char* s=src[0]+stride[0]*(y0+y)+x0;
      unsigned char* d=vo_image+vo_w*(y0+y)+x0;
      memcpy(d,s,w);
  }
  x0>>=1;y0>>=1;
  w>>=1;h>>=1;
  // copy U:
  for(y=0;y<h;y++){
      unsigned char* s=src[2]+stride[2]*(y0+y)+x0;
      unsigned char* d=vo_image+vo_w*vo_h+(vo_w>>1)*(y0+y)+x0;
      memcpy(d,s,w);
  }
  // copy V:
  for(y=0;y<h;y++){
      unsigned char* s=src[1]+stride[1]*(y0+y)+x0;
      unsigned char* d=vo_image+vo_w*vo_h+vo_w*vo_h/4+(vo_w>>1)*(y0+y)+x0;
      memcpy(d,s,w);
  }

}

static uint32_t draw_frame(uint8_t *src[]){
  // printf("This function shouldn't be called - report bug!\n");
  // later: add YUY2->YV12 conversion here!
  vo_image_ptr=src[0];
}

vo_functions_t video_out;

//---------------

static int eof=0;

static void exit_sighandler(int x){
    eof=1;
}

int main(int argc,char* argv[]){

stream_t* stream=NULL;
demuxer_t* demuxer=NULL;
demux_stream_t *d_audio=NULL;
demux_stream_t *d_video=NULL;
demux_stream_t *d_dvdsub=NULL;
sh_audio_t *sh_audio=NULL;
sh_video_t *sh_video=NULL;
int file_format=DEMUXER_TYPE_UNKNOWN;
int i;
unsigned int out_fmt;

aviwrite_t* muxer=NULL;
aviwrite_stream_t* mux_a=NULL;
aviwrite_stream_t* mux_v=NULL;
FILE* muxer_f=NULL;

ENC_PARAM enc_param;
ENC_FRAME enc_frame;
ENC_RESULT enc_result;
void* enc_handle=NULL;

float audio_preload=0.3;

//int out_buffer_size=0x200000;
//unsigned char* out_buffer=malloc(out_buffer_size);

  mp_msg_init(verbose+MSGL_STATUS);

  // check codec.conf
  if(!parse_codec_cfg("etc/codecs.conf")){
    mp_msg(MSGT_CPLAYER,MSGL_HINT,MSGTR_CopyCodecsConf);
    exit(0);  // From unknown reason a hangup occurs here :((((((
  }

  if(argc>1)
    stream=open_stream(argv[1],0,&file_format);
  else
//    stream=open_stream("/3d/abcug/Weird AL - Amish Paradise (MUSIC VIDEO).mpeg",0,&file_format);
    stream=open_stream("/3d/divx/405divx_sm_v2[1].avi",0,&file_format);
//    stream=open_stream("/dev/cdrom",2,&file_format); // VCD track 2

  if(!stream){
	printf("Cannot open file/device\n");
	exit(1);
  }

  printf("success: format: %d  data: 0x%X - 0x%X\n",file_format, (int)(stream->start_pos),(int)(stream->end_pos));

  stream_enable_cache(stream,2048*1024);

  demuxer=demux_open(stream,file_format,-1,-1,-1);
  if(!demuxer){
	printf("Cannot open demuxer\n");
	exit(1);
  }

d_audio=demuxer->audio;
d_video=demuxer->video;
d_dvdsub=demuxer->sub;
sh_audio=d_audio->sh;
sh_video=d_video->sh;

  if(!video_read_properties(sh_video)){
      printf("Couldn't read video properties\n");
      exit(1);
  }

  mp_msg(MSGT_CPLAYER,MSGL_INFO,"[V] filefmt:%d  fourcc:0x%X  size:%dx%d  fps:%5.2f  ftime:=%6.4f\n",
   demuxer->file_format,sh_video->format, sh_video->disp_w,sh_video->disp_h,
   sh_video->fps,sh_video->frametime
  );
  

sh_video->codec=NULL;
if(video_family!=-1) mp_msg(MSGT_CPLAYER,MSGL_INFO,MSGTR_TryForceVideoFmt,video_family);
while(1){
  sh_video->codec=find_codec(sh_video->format,
    sh_video->bih?((unsigned int*) &sh_video->bih->biCompression):NULL,sh_video->codec,0);
  if(!sh_video->codec){
    if(video_family!=-1) {
      sh_video->codec=NULL; /* re-search */
      mp_msg(MSGT_CPLAYER,MSGL_WARN,MSGTR_CantFindVfmtFallback);
      video_family=-1;
      continue;      
    }
    mp_msg(MSGT_CPLAYER,MSGL_ERR,MSGTR_CantFindVideoCodec,sh_video->format);
    mp_msg(MSGT_CPLAYER,MSGL_HINT, MSGTR_TryUpgradeCodecsConfOrRTFM,get_path("codecs.conf"));
    exit(1);
  }
  if(video_codec && strcmp(sh_video->codec->name,video_codec)) continue;
  else if(video_family!=-1 && sh_video->codec->driver!=video_family) continue;
  break;
}

mp_msg(MSGT_CPLAYER,MSGL_INFO,"%s video codec: [%s] drv:%d (%s)\n",video_codec?"Forcing":"Detected",sh_video->codec->name,sh_video->codec->driver,sh_video->codec->info);

for(i=0;i<CODECS_MAX_OUTFMT;i++){
    out_fmt=sh_video->codec->outfmt[i];
    if(out_fmt==0xFFFFFFFF) continue;
    if(out_fmt==IMGFMT_YV12) break;
    if(out_fmt==IMGFMT_I420) break;
    if(out_fmt==IMGFMT_IYUV) break;
    if(out_fmt==IMGFMT_YUY2) break;
}
if(i>=CODECS_MAX_OUTFMT){
    mp_msg(MSGT_CPLAYER,MSGL_FATAL,MSGTR_VOincompCodec);
    exit(1); // exit_player(MSGTR_Exit_error);
}
sh_video->outfmtidx=i;

if(out_fmt==IMGFMT_YV12 || out_fmt==IMGFMT_I420 || out_fmt==IMGFMT_IYUV){
    vo_w=sh_video->disp_w;
    vo_h=sh_video->disp_h;
    vo_image=malloc(vo_w*vo_h*3/2);
    vo_image_ptr=vo_image;
}

divx_quality=4;

if(!init_video(sh_video)){
     mp_msg(MSGT_CPLAYER,MSGL_FATAL,MSGTR_CouldntInitVideoCodec);
     exit(1);
}



if(sh_audio){
  // Go through the codec.conf and find the best codec...
  sh_audio->codec=NULL;
  if(audio_family!=-1) mp_msg(MSGT_CPLAYER,MSGL_INFO,MSGTR_TryForceAudioFmt,audio_family);
  while(1){
    sh_audio->codec=find_codec(sh_audio->format,NULL,sh_audio->codec,1);
    if(!sh_audio->codec){
      if(audio_family!=-1) {
        sh_audio->codec=NULL; /* re-search */
        mp_msg(MSGT_CPLAYER,MSGL_ERR,MSGTR_CantFindAfmtFallback);
        audio_family=-1;
        continue;      
      }
      mp_msg(MSGT_CPLAYER,MSGL_ERR,MSGTR_CantFindAudioCodec,sh_audio->format);
      mp_msg(MSGT_CPLAYER,MSGL_HINT, MSGTR_TryUpgradeCodecsConfOrRTFM,get_path("codecs.conf"));
      sh_audio=d_audio->sh=NULL;
      break;
    }
    if(audio_codec && strcmp(sh_audio->codec->name,audio_codec)) continue;
    else if(audio_family!=-1 && sh_audio->codec->driver!=audio_family) continue;
    mp_msg(MSGT_CPLAYER,MSGL_INFO,"%s audio codec: [%s] drv:%d (%s)\n",audio_codec?"Forcing":"Detected",sh_audio->codec->name,sh_audio->codec->driver,sh_audio->codec->info);
    break;
  }
}

if(sh_audio){
  mp_msg(MSGT_CPLAYER,MSGL_V,"Initializing audio codec...\n");
  if(!init_audio(sh_audio)){
    mp_msg(MSGT_CPLAYER,MSGL_ERR,MSGTR_CouldntInitAudioCodec);
    sh_audio=d_audio->sh=NULL;
  } else {
    mp_msg(MSGT_CPLAYER,MSGL_INFO,"AUDIO: srate=%d  chans=%d  bps=%d  sfmt=0x%X  ratio: %d->%d\n",sh_audio->samplerate,sh_audio->channels,sh_audio->samplesize,
        sh_audio->sample_format,sh_audio->i_bps,sh_audio->o_bps);
  }
}



// set up video encoder:
video_out.draw_slice=draw_slice;
video_out.draw_frame=draw_frame;

// set up output file:
muxer_f=fopen("test.avi","wb");
muxer=aviwrite_new_muxer();

// ============= VIDEO ===============

mux_v=aviwrite_new_stream(muxer,AVIWRITE_TYPE_VIDEO);

mux_v->buffer_size=0x200000;
mux_v->buffer=malloc(mux_v->buffer_size);

mux_v->source=sh_video;

mux_v->h.dwSampleSize=0; // VBR
mux_v->h.dwScale=10000;
mux_v->h.dwRate=mux_v->h.dwScale*sh_video->fps;

mux_v->codec=VCODEC_DIVX4; // 0=streamcopy

switch(mux_v->codec){
case 0:
    mux_v->bih=sh_video->bih;
    break;
case VCODEC_DIVX4:
    mux_v->bih=malloc(sizeof(BITMAPINFOHEADER));
    mux_v->bih->biSize=sizeof(BITMAPINFOHEADER);
    mux_v->bih->biWidth=sh_video->disp_w;
    mux_v->bih->biHeight=sh_video->disp_h;
    mux_v->bih->biPlanes=0;
    mux_v->bih->biBitCount=24;
    mux_v->bih->biCompression=mmioFOURCC('d','i','v','x');
    mux_v->bih->biSizeImage=mux_v->bih->biWidth*mux_v->bih->biHeight*(mux_v->bih->biBitCount/8);
    break;
}

// ============= AUDIO ===============
if(sh_audio){

mux_a=aviwrite_new_stream(muxer,AVIWRITE_TYPE_AUDIO);

mux_a->buffer_size=0x100000; //16384;
mux_a->buffer=malloc(mux_a->buffer_size);

mux_a->source=sh_audio;

//mux_a->codec=ACODEC_VBRMP3; // 0=streamcopy

switch(mux_a->codec){
case 0:
    mux_a->h.dwSampleSize=sh_audio->audio.dwSampleSize;
    mux_a->h.dwScale=sh_audio->audio.dwScale;
    mux_a->h.dwRate=sh_audio->audio.dwRate;
    mux_a->wf=sh_audio->wf;
    break;
case ACODEC_VBRMP3:
    mux_a->h.dwSampleSize=0; // VBR
    mux_a->h.dwScale=4608;
    mux_a->h.dwRate=sh_audio->samplerate;
    mux_a->wf=malloc(sizeof(WAVEFORMATEX));
    mux_a->wf->wFormatTag=0x55; // MP3
    mux_a->wf->nChannels=sh_audio->channels;
    mux_a->wf->nSamplesPerSec=sh_audio->samplerate;
    mux_a->wf->nAvgBytesPerSec=0;
    mux_a->wf->nBlockAlign=1;
    mux_a->wf->wBitsPerSample=16;
    mux_a->wf->cbSize=0; // FIXME for l3codeca.acm
    break;
}
}

aviwrite_write_header(muxer,muxer_f);

switch(mux_v->codec){
case 0:
    break;
case VCODEC_DIVX4:
    // init divx4linux:
    enc_param.x_dim=sh_video->disp_w;
    enc_param.y_dim=sh_video->disp_h;
    enc_param.framerate=sh_video->fps;
    enc_param.bitrate=1800000;
    enc_param.rc_period=0;
    enc_param.rc_reaction_period=0;
    enc_param.rc_reaction_ratio=0;
    enc_param.max_quantizer=0;
    enc_param.min_quantizer=0;
    enc_param.max_key_interval=0;
    enc_param.use_bidirect=0;
    enc_param.deinterlace=0;
    enc_param.quality=5; // the quality of compression ( 1 - fastest, 5 - best )
    enc_param.obmc=0;
    enc_param.handle=NULL;
    encore(NULL,ENC_OPT_INIT,&enc_param,NULL);
    enc_handle=enc_param.handle;
    break;
}

signal(SIGINT,exit_sighandler);  // Interrupt from keyboard
signal(SIGQUIT,exit_sighandler); // Quit from keyboard
signal(SIGTERM,exit_sighandler); // kill

while(!eof){

    float frame_time=0;
    int blit_frame=0;
    float a_pts=0;
    float v_pts=0;
    unsigned char* start=NULL;
    int in_size;

if(sh_audio){
    // get audio:
    if(mux_a->timer-audio_preload<mux_v->timer){
	// copy 0.5 sec of audio
	int len;
	if(mux_a->h.dwSampleSize){
	    // CBR
	    len=sh_audio->i_bps/2;
	    len/=mux_a->h.dwSampleSize;if(len<1) len=1;
	    len*=mux_a->h.dwSampleSize;
//	    printf("%d -> ",len);
	    len=demux_read_data(sh_audio->ds,mux_a->buffer,len);
//	    printf("%d  \n",len);
	} else {
	    // VBR
	    printf("not yet implemented!\n");
	}
	if(len>0) aviwrite_write_chunk(muxer,mux_a,muxer_f,len,0);
    }
}

    // get video frame!
    in_size=video_read_frame(sh_video,&frame_time,&start,force_fps);
    if(in_size<0){ eof=1; break; }

    sh_video->timer+=frame_time;

    if(pts_from_bps){
        unsigned int samples=(sh_audio->audio.dwSampleSize)?
          ((ds_tell(d_audio)-sh_audio->a_in_buffer_len)/sh_audio->audio.dwSampleSize) :
          (d_audio->pack_no); // <- used for VBR audio
        a_pts=samples*(float)sh_audio->audio.dwScale/(float)sh_audio->audio.dwRate;
      delay_corrected=1;
    } else {
      // PTS = (last timestamp) + (bytes after last timestamp)/(bytes per sec)
      a_pts=d_audio->pts;
      if(!delay_corrected) if(a_pts) delay_corrected=1;
      //printf("*** %5.3f ***\n",a_pts);
      a_pts+=(ds_tell_pts(d_audio)-sh_audio->a_in_buffer_len)/(float)sh_audio->i_bps;
    }
    v_pts=d_video->pts;

    mp_msg(MSGT_AVSYNC,MSGL_STATUS,"A:%6.1f V:%6.1f A-V:%7.3f ct:%7.3f  %3d/%3d  %2d%% %2d%% %4.1f%%  %d%%\r",
	  a_pts,v_pts,a_pts-v_pts,c_total,
          (int)sh_video->num_frames,(int)sh_video->num_frames_decoded,
          (sh_video->timer>0.5)?(int)(100.0*video_time_usage/(double)sh_video->timer):0,
          (sh_video->timer>0.5)?(int)(100.0*vout_time_usage/(double)sh_video->timer):0,
          (sh_video->timer>0.5)?(100.0*audio_time_usage/(double)sh_video->timer):0
	  ,cache_fill_status
        );
        fflush(stdout);

//    if(!blit_frame) continue;

switch(mux_v->codec){
case 0:
    mux_v->buffer=start;
    aviwrite_write_chunk(muxer,mux_v,muxer_f,in_size,(sh_video->ds->flags&1)?0x10:0);
    break;
case VCODEC_DIVX4:
    blit_frame=decode_video(&video_out,sh_video,start,in_size,0);
    if(!blit_frame){
	// empty.
	aviwrite_write_chunk(muxer,mux_v,muxer_f,0,0);
	break;
    }
    enc_frame.image=vo_image_ptr;
    enc_frame.bitstream=mux_v->buffer;
    enc_frame.length=mux_v->buffer_size;
    switch(out_fmt){
    case IMGFMT_YV12:	enc_frame.colorspace=ENC_CSP_YV12; break;
    case IMGFMT_IYUV:
    case IMGFMT_I420:	enc_frame.colorspace=ENC_CSP_I420; break;
    case IMGFMT_YUY2:	enc_frame.colorspace=ENC_CSP_YUY2; break;
    case IMGFMT_UYVY:	enc_frame.colorspace=ENC_CSP_UYVY; break;
    case IMGFMT_RGB24:
    case IMGFMT_BGR24:
    	enc_frame.colorspace=ENC_CSP_RGB24; break;
    }
    enc_frame.quant=0;
    enc_frame.intra=0;
    enc_frame.mvs=NULL;
//    printf("encoding...\n");
    encore(enc_handle,ENC_OPT_ENCODE,&enc_frame,&enc_result);
//    printf("  len=%d  key:%d  qualt:%d  \n",enc_frame.length,enc_result.is_key_frame,enc_result.quantizer);
    aviwrite_write_chunk(muxer,mux_v,muxer_f,enc_frame.length,enc_result.is_key_frame?0x10:0);
    break;
}


} // while(!eof)

aviwrite_write_index(muxer,muxer_f);
fseek(muxer_f,0,SEEK_SET);
aviwrite_write_header(muxer,muxer_f); // update header
fclose(muxer_f);

}
