/* ------------------------------------------------------------------------- */

/* 
 * vo_jpeg.c, JPEG Renderer for MPlayer
 *
 * 
 * Changelog
 * 
 * Original version: Copyright 2002 by Pontscho (pontscho@makacs.poliod.hu)
 * 2003-04-25   Spring cleanup -- Alex
 * 2004-08-04   Added multiple subdirectory support -- Ivo (ivop@euronet.nl)
 * 2004-09-01   Cosmetics update -- Ivo
 *
 */

/* ------------------------------------------------------------------------- */

/* Global Includes */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <jpeglib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

/* ------------------------------------------------------------------------- */

/* Local Includes */

#include "config.h"
#include "mp_msg.h"
#include "video_out.h"
#include "video_out_internal.h"
#include "mplayer.h"			/* for exit_player() */
#include "help_mp.h"

/* ------------------------------------------------------------------------- */

/* Defines */

/* Used for temporary buffers to store file- and pathnames */
#define BUFLENGTH 512

/* ------------------------------------------------------------------------- */

/* Info */

static vo_info_t info=
{
	"JPEG file",
	"jpeg",
	"Zoltan Ponekker (pontscho@makacs.poliod.hu)",
	""
};

LIBVO_EXTERN (jpeg)

/* ------------------------------------------------------------------------- */

/* Global Variables */

static int image_width;
static int image_height;

int jpeg_baseline = 1;
int jpeg_progressive_mode = 0;
int jpeg_optimize = 100;
int jpeg_smooth = 0;
int jpeg_quality = 75;
char *jpeg_outdir = ".";
char *jpeg_subdirs = NULL;
int jpeg_maxfiles = 1000;

static int framenum = 0;

/* ------------------------------------------------------------------------- */

static uint32_t config(uint32_t width, uint32_t height, uint32_t d_width,
                       uint32_t d_height, uint32_t fullscreen, char *title,
                       uint32_t format)
{
    char buf[BUFLENGTH];
    struct stat stat_p;

    /* Create outdir.
     * If it already exists, test if it's a writable directory */ 
    
    snprintf(buf, BUFLENGTH, "%s", jpeg_outdir);
 
    if ( mkdir(buf, 0755) < 0 ) {
        switch (errno) { /* use switch in case other errors need to be caught
                            and handled in the future */
            case EEXIST:
                if ( stat(buf, &stat_p ) < 0 ) {
                    mp_msg(MSGT_VO, MSGL_ERR, "%s: %s: %s\n", info.short_name,
                            MSGTR_VO_JPEG_GenericError, strerror(errno) );
                    mp_msg(MSGT_VO, MSGL_ERR, "%s: %s %s\n", info.short_name,
                            MSGTR_VO_JPEG_UnableToAccess,buf);
                    exit_player(MSGTR_Exit_error);
                }
                if ( !S_ISDIR(stat_p.st_mode) ) {
                    mp_msg(MSGT_VO, MSGL_ERR, "%s: %s %s\n", info.short_name,
                            buf, MSGTR_VO_JPEG_ExistsButNoDirectory);
                    exit_player(MSGTR_Exit_error);
                }
                if ( !(stat_p.st_mode & S_IWUSR) ) {
                    mp_msg(MSGT_VO, MSGL_ERR, "%s: %s\n", info.short_name,
                            MSGTR_VO_JPEG_DirExistsButNotWritable);
                    exit_player(MSGTR_Exit_error);
                }
                
                mp_msg(MSGT_VO, MSGL_INFO, "%s: %s\n", info.short_name,
                        MSGTR_VO_JPEG_DirExistsAndIsWritable);
                break;

            default:
                mp_msg(MSGT_VO, MSGL_ERR, "%s: %s: %s\n", info.short_name,
                        MSGTR_VO_JPEG_GenericError, strerror(errno) );
                mp_msg(MSGT_VO, MSGL_ERR, "%s: %s\n", info.short_name,
                        MSGTR_VO_JPEG_CantCreateDirectory);
                exit_player(MSGTR_Exit_error);
        } /* end switch */
    } else {  
        mp_msg(MSGT_VO, MSGL_INFO, "%s: %s\n", info.short_name,
                MSGTR_VO_JPEG_DirectoryCreateSuccess);
    } /* end if */

    image_height = height;
    image_width = width;
    
    return 0;
}

/* ------------------------------------------------------------------------- */

static uint32_t jpeg_write(uint8_t * name, uint8_t * buffer)
{
    FILE *outfile;
    struct jpeg_compress_struct cinfo;
    struct jpeg_error_mgr jerr;
    JSAMPROW row_pointer[1];
    int row_stride;

    if ( !buffer ) return 1; 
    if ( (outfile = fopen(name, "wb") ) == NULL ) {
        return 1;
    }
 
    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_compress(&cinfo);
    jpeg_stdio_dest(&cinfo, outfile);
    
    cinfo.image_width = image_width;
    cinfo.image_height = image_height;
    cinfo.input_components = 3;
    cinfo.in_color_space = JCS_RGB;
    
    jpeg_set_defaults(&cinfo);
    jpeg_set_quality(&cinfo,jpeg_quality, jpeg_baseline);
    cinfo.optimize_coding = jpeg_optimize;
    cinfo.smoothing_factor = jpeg_smooth;

    if ( jpeg_progressive_mode ) {
        jpeg_simple_progression(&cinfo);
    }
    
    jpeg_start_compress(&cinfo, TRUE);
    
    row_stride = image_width * 3;
    while (cinfo.next_scanline < cinfo.image_height) {
        row_pointer[0] = &buffer[cinfo.next_scanline * row_stride];
        (void)jpeg_write_scanlines(&cinfo, row_pointer,1);
    }

    jpeg_finish_compress(&cinfo);
    fclose(outfile);
    jpeg_destroy_compress(&cinfo);
    
    return 0;
}

/* ------------------------------------------------------------------------- */

static uint32_t draw_frame(uint8_t *src[])
{
    static uint32_t framecounter = 0, subdircounter = 0;
    char buf[BUFLENGTH];
    uint8_t *dst = src[0];
    static char subdirname[BUFLENGTH] = "";
    struct stat stat_p;

    /* Start writing to new subdirectory after a certain amount of frames */
    if ( framecounter == jpeg_maxfiles ) {
        framecounter = 0;
    }

    /* If framecounter is zero (or reset to zero), increment subdirectory
     * number and create the subdirectory.
     * If jpeg_subdirs is not set, do nothing and resort to old behaviour. */
    if ( !framecounter && jpeg_subdirs ) {
        snprintf(subdirname, BUFLENGTH, "%s%08d", jpeg_subdirs,
                                                            ++subdircounter);
        snprintf(buf, BUFLENGTH, "%s/%s", jpeg_outdir, subdirname);
        if ( mkdir(buf, 0755) < 0 ) {
            switch (errno) { /* use switch in case other errors need to be
                                caught and handled in the future */
                case EEXIST:
                    if ( stat(buf, &stat_p) < 0 ) {
                        mp_msg(MSGT_VO, MSGL_ERR, "%s: %s: %s\n",
                                info.short_name, MSGTR_VO_JPEG_GenericError,
                                strerror(errno) );
                        mp_msg(MSGT_VO, MSGL_ERR, "%s: %s %s\n",
                                info.short_name, MSGTR_VO_JPEG_UnableToAccess,
                                buf);
                        exit_player(MSGTR_Exit_error);
                    }
                    if ( !S_ISDIR(stat_p.st_mode) ) {
                        mp_msg(MSGT_VO, MSGL_ERR, "\n%s: %s %s\n",
                                info.short_name, buf,
                                MSGTR_VO_JPEG_ExistsButNoDirectory);
                        exit_player(MSGTR_Exit_error);
                    }
                    if ( !(stat_p.st_mode & S_IWUSR) ) {
                        mp_msg(MSGT_VO, MSGL_ERR, "\n%s: %s - %s\n",
                                info.short_name, buf,
                                MSGTR_VO_JPEG_DirExistsButNotWritable);
                        exit_player(MSGTR_Exit_error);
                    }
                    
                    mp_msg(MSGT_VO, MSGL_INFO, "\n%s: %s - %s\n",
                            info.short_name, buf,
                            MSGTR_VO_JPEG_DirExistsAndIsWritable);
                    break;
                    
                default:
                    mp_msg(MSGT_VO, MSGL_ERR, "%s: %s: %s\n", info.short_name,
                            MSGTR_VO_JPEG_GenericError, strerror(errno) );
                    mp_msg(MSGT_VO, MSGL_ERR, "\n%s: %s - %s.\n",
                            info.short_name, buf,
                            MSGTR_VO_JPEG_CantCreateDirectory);
                    exit_player(MSGTR_Exit_error);
                    break;
            }
        } /* switch */
    } /* if !framecounter && jpeg_subdirs */
    
    framenum++;

    /* snprintf the full pathname of the outputfile */
    snprintf(buf, BUFLENGTH, "%s/%s/%08d.jpg", jpeg_outdir, subdirname,
                                                                    framenum);
    
    framecounter++;
    
    return jpeg_write(buf, src[0]);
}

/* ------------------------------------------------------------------------- */

static void draw_osd(void)
{
}

/* ------------------------------------------------------------------------- */

static void flip_page (void)
{
}

/* ------------------------------------------------------------------------- */

static uint32_t draw_slice(uint8_t *src[], int stride[], int w, int h,
                           int x, int y)
{
    return 0;
}

/* ------------------------------------------------------------------------- */

static uint32_t query_format(uint32_t format)
{
    if (format == IMGFMT_RGB24) {
        return VFCAP_CSP_SUPPORTED|VFCAP_CSP_SUPPORTED_BY_HW;
    }
    
    return 0;
}

/* ------------------------------------------------------------------------- */

static void uninit(void)
{
}

/* ------------------------------------------------------------------------- */

static void check_events(void)
{
}

/* ------------------------------------------------------------------------- */

static uint32_t preinit(const char *arg)
{
    return 0;
}

/* ------------------------------------------------------------------------- */

static uint32_t control(uint32_t request, void *data, ...)
{
    switch (request) {
        case VOCTRL_QUERY_FORMAT:
            return query_format(*((uint32_t*)data));
    }
    return VO_NOTIMPL;
}

/* ------------------------------------------------------------------------- */

#undef BUFLENGTH

/* ------------------------------------------------------------------------- */

