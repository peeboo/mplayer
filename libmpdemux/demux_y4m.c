//  Y4M file parser by Rik Snel (using yuv4mpeg*.[ch] from
//  mjpeg.sourceforge.net) (derived from demux_viv.c)
//  older YUV4MPEG (used by xawtv) support by Alex Beregszaszi

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h> /* strtok */

#include "config.h"
#include "mp_msg.h"
#include "help_mp.h"
#include "yuv4mpeg.h"

//#include "stream.h"
#include "demuxer.h"
#include "stheader.h"
#include "bswap.h"

typedef struct {
    int framenum; 
    y4m_stream_info_t* si;
    int is_older;
} y4m_priv_t;

int y4m_check_file(demuxer_t* demuxer){
    int orig_pos = stream_tell(demuxer->stream);
    char buf[10];
    y4m_priv_t* priv;
    
    mp_msg(MSGT_DEMUX, MSGL_V, "Checking for YUV4MPEG2\n");
    
    stream_read(demuxer->stream, buf, 9);
    buf[9] = 0;
    
    if (strncmp("YUV4MPEG2", buf, 9) && strncmp("YUV4MPEG ", buf, 9)) {
	    mp_msg(MSGT_DEMUX, MSGL_DBG2, "Failed: YUV4MPEG2\n");
	    return 0;
    }

    demuxer->priv = malloc(sizeof(y4m_priv_t));
    priv = demuxer->priv;

    priv->is_older = 0;

    if (!strncmp("YUV4MPEG ", buf, 9))
    {
	mp_msg(MSGT_DEMUX, MSGL_V, "Found older YUV4MPEG format (used by xawtv)\n");
	priv->is_older = 1;
    }

    mp_msg(MSGT_DEMUX,MSGL_DBG2,"Success: YUV4MPEG2\n");

    stream_seek(demuxer->stream, orig_pos);

    return 1;
}


// return value:
//     0 = EOF or no stream found
//     1 = successfully read a packet
int demux_y4m_fill_buffer(demuxer_t *demux) {
  demux_stream_t *ds=demux->video;
  demux_packet_t *dp;
  y4m_priv_t *priv=demux->priv;
  y4m_frame_info_t fi;
  unsigned char *buf[3];
  int err, size;

  demux->filepos=stream_tell(demux->stream);

  size = ((sh_video_t*)ds->sh)->disp_w*((sh_video_t*)ds->sh)->disp_h;

  dp = new_demux_packet(3*size/2);

  /* swap U and V components */
  buf[0] = dp->buffer;
  buf[1] = dp->buffer + 5*size/4;
  buf[2] = dp->buffer + size;

  if (priv->is_older)
  {
    stream_skip(demux->stream, 6); /* FRAME\n */
    stream_read(demux->stream, buf[0], size);
    stream_read(demux->stream, buf[1], size/4);
    stream_read(demux->stream, buf[2], size/4);
  }
  else
  {
    if ((err=y4m_read_frame(demux->stream, priv->si, &fi, buf)) != Y4M_OK) {
      mp_msg(MSGT_DEMUX, MSGL_V, "error reading frame %s\n", y4m_strerr(err));
      return 0;
    }
  }

  /* This seems to be the right way to calculate the presentation time stamp */
  dp->pts=(float)priv->framenum/((sh_video_t*)ds->sh)->fps;
  priv->framenum++;
  dp->pos=demux->filepos;
  dp->flags=0;
  ds_add_packet(ds, dp);

  return 1;
}

void demux_open_y4m(demuxer_t* demuxer){
    y4m_priv_t* priv = demuxer->priv;
    y4m_ratio_t framerate;
    sh_video_t* sh=new_sh_video(demuxer,0);
    int err;

    priv->framenum = 0;
    priv->si = malloc(sizeof(y4m_stream_info_t));

    if (priv->is_older)
    {
	char buf[4];
	int frame_rate_code;

	priv->framenum = 1;
	stream_skip(demuxer->stream, 8); /* YUV4MPEG */
	stream_skip(demuxer->stream, 1); /* space */
	stream_read(demuxer->stream, (char *)&buf[0], 3);
	buf[3] = 0;
	sh->disp_w = atoi(buf);
	stream_skip(demuxer->stream, 1); /* space */
	stream_read(demuxer->stream, (char *)&buf[0], 3);
	buf[3] = 0;
	sh->disp_h = atoi(buf);
	stream_skip(demuxer->stream, 1); /* space */
	stream_read(demuxer->stream, (char *)&buf[0], 1);
	buf[1] = 0;
	frame_rate_code = atoi(buf);
	stream_skip(demuxer->stream, 1); /* new-line */
	
	if (!sh->fps)
	{
	    /* values from xawtv */
	    switch(frame_rate_code)
	    {
		case 1:
		    sh->fps = 23.976f;
		    break;
		case 2:
		    sh->fps = 24.0f;
		    break;
		case 3:
		    sh->fps = 25.0f;
		    break;
		case 4:
		    sh->fps = 29.97f;
		    break;
		case 5:
		    sh->fps = 30.0f;
		    break;
		case 6:
		    sh->fps = 50.0f;
		    break;
		case 7:
		    sh->fps = 59.94f;
		    break;
		case 8:
		    sh->fps = 60.0f;
		    break;
		default:
		    sh->fps = 25.0f;
	    }
	}
	sh->frametime = 1.0f/sh->fps;
    }
    else
    {
	y4m_init_stream_info(priv->si);
	if ((err=y4m_read_stream_header(demuxer->stream, priv->si)) != Y4M_OK) 
	    mp_msg(MSGT_DEMUXER, MSGL_FATAL, "error parsing YUV4MPEG header: %s\n", y4m_strerr(err));
	
	if(!sh->fps) {
    	    framerate = y4m_si_get_framerate(priv->si);
    	    if (framerate.d != 0)
        	sh->fps=(float)framerate.n/(float)framerate.d;
    	    else
        	sh->fps=15.0f;
	}
	sh->frametime=1.0f/sh->fps;

	sh->disp_w = y4m_si_get_width(priv->si);
	sh->disp_h = y4m_si_get_height(priv->si);
    }

    sh->format = mmioFOURCC('Y', 'V', '1', '2');

    sh->bih=malloc(sizeof(BITMAPINFOHEADER));
    memset(sh->bih,0,sizeof(BITMAPINFOHEADER));
    sh->bih->biSize=40;
    sh->bih->biWidth = sh->disp_w;
    sh->bih->biHeight = sh->disp_h;
    sh->bih->biPlanes=3;
    sh->bih->biBitCount=12;
    sh->bih->biCompression=sh->format;
    sh->bih->biSizeImage=sh->bih->biWidth*sh->bih->biHeight*3/2; /* YV12 */

    demuxer->video->sh=sh;
    sh->ds=demuxer->video;
    demuxer->video->id=0;
		
    /* disable seeking, lazy */
    demuxer->seekable = 0;

    printf("YUV4MPEG2 Video stream %d size: display: %dx%d, codec: %ux%u\n",
            demuxer->video->id, sh->disp_w, sh->disp_h, sh->bih->biWidth,
            sh->bih->biHeight);
}

void demux_close_y4m(demuxer_t *demuxer)
{
    y4m_priv_t* priv;
    
    if (!priv->is_older)
	y4m_fini_stream_info(((y4m_priv_t*)demuxer->priv)->si);
    free(((y4m_priv_t*)demuxer->priv)->si);
    free(demuxer->priv);
    return;
}
