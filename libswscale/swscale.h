/*
 * Copyright (C) 2001-2003 Michael Niedermayer <michaelni@gmx.at>
 *
 * This file is part of FFmpeg.
 *
 * FFmpeg is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * FFmpeg is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with FFmpeg; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#ifndef SWSCALE_SWSCALE_H
#define SWSCALE_SWSCALE_H

/**
 * @file libswscale/swscale.h
 * @brief
 *     external api for the swscale stuff
 */

#include "libavutil/avutil.h"

#define LIBSWSCALE_VERSION_MAJOR 0
#define LIBSWSCALE_VERSION_MINOR 6
#define LIBSWSCALE_VERSION_MICRO 1

#define LIBSWSCALE_VERSION_INT  AV_VERSION_INT(LIBSWSCALE_VERSION_MAJOR, \
                                               LIBSWSCALE_VERSION_MINOR, \
                                               LIBSWSCALE_VERSION_MICRO)
#define LIBSWSCALE_VERSION      AV_VERSION(LIBSWSCALE_VERSION_MAJOR, \
                                           LIBSWSCALE_VERSION_MINOR, \
                                           LIBSWSCALE_VERSION_MICRO)
#define LIBSWSCALE_BUILD        LIBSWSCALE_VERSION_INT

#define LIBSWSCALE_IDENT        "SwS" AV_STRINGIFY(LIBSWSCALE_VERSION)

/**
 * Returns the LIBSWSCALE_VERSION_INT constant.
 */
unsigned swscale_version(void);

/* values for the flags, the stuff on the command line is different */
#define SWS_FAST_BILINEAR     1
#define SWS_BILINEAR          2
#define SWS_BICUBIC           4
#define SWS_X                 8
#define SWS_POINT          0x10
#define SWS_AREA           0x20
#define SWS_BICUBLIN       0x40
#define SWS_GAUSS          0x80
#define SWS_SINC          0x100
#define SWS_LANCZOS       0x200
#define SWS_SPLINE        0x400

#define SWS_SRC_V_CHR_DROP_MASK     0x30000
#define SWS_SRC_V_CHR_DROP_SHIFT    16

#define SWS_PARAM_DEFAULT           123456

#define SWS_PRINT_INFO              0x1000

//the following 3 flags are not completely implemented
//internal chrominace subsampling info
#define SWS_FULL_CHR_H_INT    0x2000
//input subsampling info
#define SWS_FULL_CHR_H_INP    0x4000
#define SWS_DIRECT_BGR        0x8000
#define SWS_ACCURATE_RND      0x40000
#define SWS_BITEXACT          0x80000

#define SWS_CPU_CAPS_MMX      0x80000000
#define SWS_CPU_CAPS_MMX2     0x20000000
#define SWS_CPU_CAPS_3DNOW    0x40000000
#define SWS_CPU_CAPS_ALTIVEC  0x10000000
#define SWS_CPU_CAPS_BFIN     0x01000000

#define SWS_MAX_REDUCE_CUTOFF 0.002

#define SWS_CS_ITU709         1
#define SWS_CS_FCC            4
#define SWS_CS_ITU601         5
#define SWS_CS_ITU624         5
#define SWS_CS_SMPTE170M      5
#define SWS_CS_SMPTE240M      7
#define SWS_CS_DEFAULT        5



// when used for filters they must have an odd number of elements
// coeffs cannot be shared between vectors
typedef struct {
    double *coeff;              ///< pointer to the list of coefficients
    int length;                 ///< number of coefficients in the vector
} SwsVector;

// vectors can be shared
typedef struct {
    SwsVector *lumH;
    SwsVector *lumV;
    SwsVector *chrH;
    SwsVector *chrV;
} SwsFilter;

struct SwsContext;

void sws_freeContext(struct SwsContext *swsContext);

struct SwsContext *sws_getContext(int srcW, int srcH, enum PixelFormat srcFormat, int dstW, int dstH, enum PixelFormat dstFormat, int flags,
                                  SwsFilter *srcFilter, SwsFilter *dstFilter, double *param);
int sws_scale(struct SwsContext *context, uint8_t* src[], int srcStride[], int srcSliceY,
              int srcSliceH, uint8_t* dst[], int dstStride[]);
#if LIBSWSCALE_VERSION_MAJOR < 1
/**
 * @deprecated Use sws_scale() instead.
 */
int sws_scale_ordered(struct SwsContext *context, uint8_t* src[], int srcStride[], int srcSliceY,
                      int srcSliceH, uint8_t* dst[], int dstStride[]) attribute_deprecated;
#endif


int sws_setColorspaceDetails(struct SwsContext *c, const int inv_table[4], int srcRange, const int table[4], int dstRange, int brightness, int contrast, int saturation);
int sws_getColorspaceDetails(struct SwsContext *c, int **inv_table, int *srcRange, int **table, int *dstRange, int *brightness, int *contrast, int *saturation);

/**
 * Returns a normalized Gaussian curve used to filter stuff
 * quality=3 is high quality, lower is lower quality.
 */
SwsVector *sws_getGaussianVec(double variance, double quality);

/**
 * Allocates and returns a vector with \p length coefficients, all
 * with the same value \p c.
 */
SwsVector *sws_getConstVec(double c, int length);

/**
 * Allocates and returns a vector with just one coefficient, with
 * value 1.0.
 */
SwsVector *sws_getIdentityVec(void);

/**
 * Scales all the coefficients of \p a by the \p scalar value.
 */
void sws_scaleVec(SwsVector *a, double scalar);
void sws_normalizeVec(SwsVector *a, double height);
void sws_convVec(SwsVector *a, SwsVector *b);
void sws_addVec(SwsVector *a, SwsVector *b);
void sws_subVec(SwsVector *a, SwsVector *b);
void sws_shiftVec(SwsVector *a, int shift);

/**
 * Allocates and returns a clone of the vector \p a, that is a vector
 * with the same coefficients as \p a.
 */
SwsVector *sws_cloneVec(SwsVector *a);

void sws_printVec(SwsVector *a);
void sws_freeVec(SwsVector *a);

SwsFilter *sws_getDefaultFilter(float lumaGBlur, float chromaGBlur,
                                float lumaSharpen, float chromaSharpen,
                                float chromaHShift, float chromaVShift,
                                int verbose);
void sws_freeFilter(SwsFilter *filter);

/**
 * Checks if context is valid or reallocs a new one instead.
 * If context is NULL, just calls sws_getContext() to get a new one.
 * Otherwise, checks if the parameters are the ones already saved in context.
 * If that is the case, returns the current context.
 * Otherwise, frees context and gets a new one.
 *
 * Be warned that srcFilter, dstFilter are not checked, they are
 * asumed to remain valid.
 */
struct SwsContext *sws_getCachedContext(struct SwsContext *context,
                                        int srcW, int srcH, enum PixelFormat srcFormat,
                                        int dstW, int dstH, enum PixelFormat dstFormat, int flags,
                                        SwsFilter *srcFilter, SwsFilter *dstFilter, double *param);

#endif /* SWSCALE_SWSCALE_H */
