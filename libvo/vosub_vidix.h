/*
 *  vosub_vidix.h
 *
 *	Copyright (C) Nick Kurshev <nickols_k@mail.ru> - 2002
 *
 *  You can redistribute this file under terms and conditions
 *  of GNU General Public licence v2.
 *
 * This file contains vosub_vidix interface to any mplayer's VO driver
 */

#ifndef __VOSUB_VIDIX_INCLUDED
#define __VOSUB_VIDIX_INCLUDED

		    /* drvname can be NULL */
int	 vidix_preinit(
const char *drvname,void *server);
int      vidix_init(unsigned src_width,unsigned src_height,
		    unsigned dest_x,unsigned dest_y,unsigned dst_width,
		    unsigned dst_height,unsigned format,unsigned dest_bpp,
		    unsigned vid_w,unsigned vid_h);
void	 vidix_start(void);
void	 vidix_stop(void);
void     vidix_term( void );
uint32_t vidix_query_fourcc(unsigned fourcc);

uint32_t vidix_draw_slice(uint8_t *image[], int stride[], int w,int h,int x,int y);
uint32_t vidix_draw_frame(uint8_t *src[]);
void     vidix_flip_page(void);
void     vidix_draw_osd(void);

#endif
