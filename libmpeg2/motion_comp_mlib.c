/*
 * motion_comp_mlib.c
 * Copyright (C) 2000-2001 H�kan Hjort <d95hjort@dtek.chalmers.se>
 *
 * This file is part of mpeg2dec, a free MPEG-2 video stream decoder.
 *
 * mpeg2dec is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * mpeg2dec is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "config.h"

#ifdef LIBMPEG2_MLIB

#include <inttypes.h>
#include <mlib_types.h>
#include <mlib_status.h>
#include <mlib_sys.h>
#include <mlib_video.h>

#include "mpeg2_internal.h"

static void MC_put_16_mlib (uint8_t * dest, uint8_t * ref,
			    int stride, int height)
{
    if (height == 16) 
	mlib_VideoCopyRef_U8_U8_16x16 (dest, ref, stride);
    else
	mlib_VideoCopyRef_U8_U8_16x8 (dest, ref, stride);
}

static void MC_put_x16_mlib (uint8_t * dest, uint8_t * ref,
			     int stride, int height)
{
    if (height == 16)
	mlib_VideoInterpX_U8_U8_16x16 (dest, ref, stride, stride);
    else
	mlib_VideoInterpX_U8_U8_16x8 (dest, ref, stride, stride);
}

static void MC_put_y16_mlib (uint8_t * dest, uint8_t * ref,
			     int stride, int height)
{
    if (height == 16)
	mlib_VideoInterpY_U8_U8_16x16 (dest, ref, stride, stride);
    else
	mlib_VideoInterpY_U8_U8_16x8 (dest, ref, stride, stride);
}

static void MC_put_xy16_mlib (uint8_t * dest, uint8_t * ref,
			      int stride, int height)
{
    if (height == 16)
	mlib_VideoInterpXY_U8_U8_16x16 (dest, ref, stride, stride);
    else
	mlib_VideoInterpXY_U8_U8_16x8 (dest, ref, stride, stride);
}

static void MC_put_8_mlib (uint8_t * dest, uint8_t * ref,
			   int stride, int height)
{
    if (height == 8)
	mlib_VideoCopyRef_U8_U8_8x8 (dest, ref, stride);
    else
	mlib_VideoCopyRef_U8_U8_8x4 (dest, ref, stride);
}

static void MC_put_x8_mlib (uint8_t * dest, uint8_t * ref,
			    int stride, int height)
{
    if (height == 8)
	mlib_VideoInterpX_U8_U8_8x8 (dest, ref, stride, stride);
    else
	mlib_VideoInterpX_U8_U8_8x4 (dest, ref, stride, stride);
}

static void MC_put_y8_mlib (uint8_t * dest, uint8_t * ref,
			    int stride, int height)
{
    if (height == 8)
	mlib_VideoInterpY_U8_U8_8x8 (dest, ref, stride, stride);
    else
	mlib_VideoInterpY_U8_U8_8x4 (dest, ref, stride, stride);
}

static void MC_put_xy8_mlib (uint8_t * dest, uint8_t * ref,
			     int stride, int height)
{
    if (height == 8) 
	mlib_VideoInterpXY_U8_U8_8x8 (dest, ref, stride, stride);
    else
	mlib_VideoInterpXY_U8_U8_8x4 (dest, ref, stride, stride);
}

static void MC_avg_16_mlib (uint8_t * dest, uint8_t * ref,
			    int stride, int height)
{
    if (height == 16)
	mlib_VideoCopyRefAve_U8_U8_16x16 (dest, ref, stride);
    else
	mlib_VideoCopyRefAve_U8_U8_16x8 (dest, ref, stride);
}

static void MC_avg_x16_mlib (uint8_t * dest, uint8_t * ref,
			     int stride, int height)
{
    if (height == 16)
	mlib_VideoInterpAveX_U8_U8_16x16 (dest, ref, stride, stride);
    else
	mlib_VideoInterpAveX_U8_U8_16x8 (dest, ref, stride, stride);
}

static void MC_avg_y16_mlib (uint8_t * dest, uint8_t * ref,
			     int stride, int height)
{
    if (height == 16)
	mlib_VideoInterpAveY_U8_U8_16x16 (dest, ref, stride, stride);
    else
	mlib_VideoInterpAveY_U8_U8_16x8 (dest, ref, stride, stride);
}

static void MC_avg_xy16_mlib (uint8_t * dest, uint8_t * ref,
			      int stride, int height)
{
    if (height == 16)
	mlib_VideoInterpAveXY_U8_U8_16x16 (dest, ref, stride, stride);
    else
	mlib_VideoInterpAveXY_U8_U8_16x8 (dest, ref, stride, stride);
}

static void MC_avg_8_mlib (uint8_t * dest, uint8_t * ref,
			   int stride, int height)
{
    if (height == 8)
	mlib_VideoCopyRefAve_U8_U8_8x8 (dest, ref, stride);
    else
	mlib_VideoCopyRefAve_U8_U8_8x4 (dest, ref, stride);
}

static void MC_avg_x8_mlib (uint8_t * dest, uint8_t * ref,
			    int stride, int height)
{
    if (height == 8)
	mlib_VideoInterpAveX_U8_U8_8x8 (dest, ref, stride, stride);
    else
	mlib_VideoInterpAveX_U8_U8_8x4 (dest, ref, stride, stride);
}

static void MC_avg_y8_mlib (uint8_t * dest, uint8_t * ref,
			    int stride, int height)
{
    if (height == 8)
	mlib_VideoInterpAveY_U8_U8_8x8 (dest, ref, stride, stride);
    else
	mlib_VideoInterpAveY_U8_U8_8x4 (dest, ref, stride, stride);
}

static void MC_avg_xy8_mlib (uint8_t * dest, uint8_t * ref,
			     int stride, int height)
{
    if (height == 8)
	mlib_VideoInterpAveXY_U8_U8_8x8 (dest, ref, stride, stride);
    else
	mlib_VideoInterpAveXY_U8_U8_8x4 (dest, ref, stride, stride);
}

MOTION_COMP_EXTERN (mlib)

#endif
