/*
** FAAD2 - Freeware Advanced Audio (AAC) Decoder including SBR decoding
** Copyright (C) 2003 M. Bakker, Ahead Software AG, http://www.nero.com
**  
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.
** 
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
** 
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software 
** Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
**
** Any non-GPL usage of this software or parts of this software is strictly
** forbidden.
**
** Commercial non-GPL licensing of this software is possible.
** For more info contact Ahead Software through Mpeg4AAClicense@nero.com.
**
** Initially modified for use with MPlayer by Arpad Gere�ffy on 2003/08/30
** $Id: hcb_11.h,v 1.1 2003/08/30 22:30:28 arpi Exp $
** detailed CVS changelog at http://www.mplayerhq.hu/cgi-bin/cvsweb.cgi/main/
**/

/* 2-step huffman table HCB_11 */


/* 1st step: 5 bits
 *           2^5 = 32 entries
 *
 * Used to find offset into 2nd step table and number of extra bits to get
 */
static hcb hcb11_1[] = {
    /* 4 bits */
    { /* 00000 */ 0, 0 },
    { /*       */ 0, 0 },
    { /* 00010 */ 1, 0 },
    { /*       */ 1, 0 },

    /* 5 bits */
    { /* 00100 */ 2, 0 },
    { /* 00101 */ 3, 0 },
    { /* 00110 */ 4, 0 },
    { /* 00111 */ 5, 0 },
    { /* 01000 */ 6, 0 },
    { /* 01001 */ 7, 0 },

    /* 6 bits */
    { /* 01010 */ 8,  1 },
    { /* 01011 */ 10, 1 },
    { /* 01100 */ 12, 1 },

    /* 6/7 bits */
    { /* 01101 */ 14, 2 },

    /* 7 bits */
    { /* 01110 */ 18, 2 },
    { /* 01111 */ 22, 2 },
    { /* 10000 */ 26, 2 },

    /* 7/8 bits */
    { /* 10001 */ 30, 3 },

    /* 8 bits */
    { /* 10010 */ 38, 3 },
    { /* 10011 */ 46, 3 },
    { /* 10100 */ 54, 3 },
    { /* 10101 */ 62, 3 },
    { /* 10110 */ 70, 3 },
    { /* 10111 */ 78, 3 },

    /* 8/9 bits */
    { /* 11000 */ 86, 4 },

    /* 9 bits */
    { /* 11001 */ 102, 4 },
    { /* 11010 */ 118, 4 },
    { /* 11011 */ 134, 4 },

    /* 9/10 bits */
    { /* 11100 */ 150, 5 },

    /* 10 bits */
    { /* 11101 */ 182, 5 },
    { /* 11110 */ 214, 5 },

    /* 10/11/12 bits */
    { /* 11111 */ 246, 7 }
};

/* 2nd step table
 *
 * Gives size of codeword and actual data (x,y,v,w)
 */
static hcb_2_pair hcb11_2[] = {
    /* 4 */
    { 4,  0,  0 },
    { 4,  1,  1 },

    /* 5 */
    { 5, 16, 16 },
    { 5,  1,  0 },
    { 5,  0,  1 },
    { 5,  2,  1 },
    { 5,  1,  2 },
    { 5,  2,  2 },

    /* 6 */
    { 6,  1,  3 },
    { 6,  3,  1 },
    { 6,  3,  2 },
    { 6,  2,  0 },
    { 6,  2,  3 },
    { 6,  0,  2 },

    /* 6/7 */
    { 6,  3,  3 }, { 6,  3,  3 },
    { 7,  4,  1 },
    { 7,  1,  4 },

    /* 7 */
    { 7,  4,  2 },
    { 7,  2,  4 },
    { 7,  4,  3 },
    { 7,  3,  4 },
    { 7,  3,  0 },
    { 7,  0,  3 },
    { 7,  5,  1 },
    { 7,  5,  2 },
    { 7,  2,  5 },
    { 7,  4,  4 },
    { 7,  1,  5 },
    { 7,  5,  3 },

    /* 7/8 */
    { 7,  3,  5 }, { 7,  3,  5 },
    { 7,  5,  4 }, { 7,  5,  4 },
    { 8,  4,  5 },
    { 8,  6,  2 },
    { 8,  2,  6 },
    { 8,  6,  1 },

    /* 8 */
    { 8,  6,  3 },
    { 8,  3,  6 },
    { 8,  1,  6 },
    { 8,  4, 16 },
    { 8,  3, 16 },
    { 8, 16,  5 },
    { 8, 16,  3 },
    { 8, 16,  4 },
    { 8,  6,  4 },
    { 8, 16,  6 },
    { 8,  4,  0 },
    { 8,  4,  6 },
    { 8,  0,  4 },
    { 8,  2, 16 },
    { 8,  5,  5 },
    { 8,  5, 16 },
    { 8, 16,  7 },
    { 8, 16,  2 },
    { 8, 16,  8 },
    { 8,  2,  7 },
    { 8,  7,  2 },
    { 8,  3,  7 },
    { 8,  6,  5 },
    { 8,  5,  6 },
    { 8,  6, 16 },
    { 8, 16, 10 },
    { 8,  7,  3 },
    { 8,  7,  1 },
    { 8, 16,  9 },
    { 8,  7, 16 },
    { 8,  1, 16 },
    { 8,  1,  7 },
    { 8,  4,  7 },
    { 8, 16, 11 },
    { 8,  7,  4 },
    { 8, 16, 12 },
    { 8,  8, 16 },
    { 8, 16,  1 },
    { 8,  6,  6 },
    { 8,  9, 16 },
    { 8,  2,  8 },
    { 8,  5,  7 },
    { 8, 10, 16 },
    { 8, 16, 13 },
    { 8,  8,  3 },
    { 8,  8,  2 },
    { 8,  3,  8 },
    { 8,  5,  0 },

    /* 8/9 */
    { 8, 16, 14 }, { 8, 16, 14 },
    { 8, 11, 16 }, { 8, 11, 16 },
    { 8,  7,  5 }, { 8,  7,  5 },
    { 8,  4,  8 }, { 8,  4,  8 },
    { 8,  6,  7 }, { 8,  6,  7 },
    { 8,  7,  6 }, { 8,  7,  6 },
    { 8,  0,  5 }, { 8,  0,  5 },
    { 9,  8,  4 },
    { 9, 16, 15 },

    /* 9 */
    { 9, 12, 16 },
    { 9,  1,  8 },
    { 9,  8,  1 },
    { 9, 14, 16 },
    { 9,  5,  8 },
    { 9, 13, 16 },
    { 9,  3,  9 },
    { 9,  8,  5 },
    { 9,  7,  7 },
    { 9,  2,  9 },
    { 9,  8,  6 },
    { 9,  9,  2 },
    { 9,  9,  3 },
    { 9, 15, 16 },
    { 9,  4,  9 },
    { 9,  6,  8 },
    { 9,  6,  0 },
    { 9,  9,  4 },
    { 9,  5,  9 },
    { 9,  8,  7 },
    { 9,  7,  8 },
    { 9,  1,  9 },
    { 9, 10,  3 },
    { 9,  0,  6 },
    { 9, 10,  2 },
    { 9,  9,  1 },
    { 9,  9,  5 },
    { 9,  4, 10 },
    { 9,  2, 10 },
    { 9,  9,  6 },
    { 9,  3, 10 },
    { 9,  6,  9 },
    { 9, 10,  4 },
    { 9,  8,  8 },
    { 9, 10,  5 },
    { 9,  9,  7 },
    { 9, 11,  3 },
    { 9,  1, 10 },
    { 9,  7,  0 },
    { 9, 10,  6 },
    { 9,  7,  9 },
    { 9,  3, 11 },
    { 9,  5, 10 },
    { 9, 10,  1 },
    { 9,  4, 11 },
    { 9, 11,  2 },
    { 9, 13,  2 },
    { 9,  6, 10 },

    /* 9/10 */
    { 9, 13,  3 }, { 9, 13,  3 },
    { 9,  2, 11 }, { 9,  2, 11 },
    { 9, 16,  0 }, { 9, 16,  0 },
    { 9,  5, 11 }, { 9,  5, 11 },
    { 9, 11,  5 }, { 9, 11,  5 },
    { 10, 11,  4 },
    { 10,  9,  8 },
    { 10,  7, 10 },
    { 10,  8,  9 },
    { 10,  0, 16 },
    { 10,  4, 13 },
    { 10,  0,  7 },
    { 10,  3, 13 },
    { 10, 11,  6 },
    { 10, 13,  1 },
    { 10, 13,  4 },
    { 10, 12,  3 },
    { 10,  2, 13 },
    { 10, 13,  5 },
    { 10,  8, 10 },
    { 10,  6, 11 },
    { 10, 10,  8 },
    { 10, 10,  7 },
    { 10, 14,  2 },
    { 10, 12,  4 },
    { 10,  1, 11 },
    { 10,  4, 12 },

    /* 10 */
    { 10, 11,  1 },
    { 10,  3, 12 },
    { 10,  1, 13 },
    { 10, 12,  2 },
    { 10,  7, 11 },
    { 10,  3, 14 },
    { 10,  5, 12 },
    { 10,  5, 13 },
    { 10, 14,  4 },
    { 10,  4, 14 },
    { 10, 11,  7 },
    { 10, 14,  3 },
    { 10, 12,  5 },
    { 10, 13,  6 },
    { 10, 12,  6 },
    { 10,  8,  0 },
    { 10, 11,  8 },
    { 10,  2, 12 },
    { 10,  9,  9 },
    { 10, 14,  5 },
    { 10,  6, 13 },
    { 10, 10, 10 },
    { 10, 15,  2 },
    { 10,  8, 11 },
    { 10,  9, 10 },
    { 10, 14,  6 },
    { 10, 10,  9 },
    { 10,  5, 14 },
    { 10, 11,  9 },
    { 10, 14,  1 },
    { 10,  2, 14 },
    { 10,  6, 12 },
    { 10,  1, 12 },
    { 10, 13,  8 },
    { 10,  0,  8 },
    { 10, 13,  7 },
    { 10,  7, 12 },
    { 10, 12,  7 },
    { 10,  7, 13 },
    { 10, 15,  3 },
    { 10, 12,  1 },
    { 10,  6, 14 },
    { 10,  2, 15 },
    { 10, 15,  5 },
    { 10, 15,  4 },
    { 10,  1, 14 },
    { 10,  9, 11 },
    { 10,  4, 15 },
    { 10, 14,  7 },
    { 10,  8, 13 },
    { 10, 13,  9 },
    { 10,  8, 12 },
    { 10,  5, 15 },
    { 10,  3, 15 },
    { 10, 10, 11 },
    { 10, 11, 10 },
    { 10, 12,  8 },
    { 10, 15,  6 },
    { 10, 15,  7 },
    { 10,  8, 14 },
    { 10, 15,  1 },
    { 10,  7, 14 },
    { 10,  9,  0 },
    { 10,  0,  9 },

    /* 10/11/12 */
    { 10,  9, 13 }, { 10,  9, 13 }, { 10,  9, 13 }, { 10,  9, 13 },
    { 10,  9, 12 }, { 10,  9, 12 }, { 10,  9, 12 }, { 10,  9, 12 },
    { 10, 12,  9 }, { 10, 12,  9 }, { 10, 12,  9 }, { 10, 12,  9 },
    { 10, 14,  8 }, { 10, 14,  8 }, { 10, 14,  8 }, { 10, 14,  8 },
    { 10, 10, 13 }, { 10, 10, 13 }, { 10, 10, 13 }, { 10, 10, 13 },
    { 10, 14,  9 }, { 10, 14,  9 }, { 10, 14,  9 }, { 10, 14,  9 },
    { 10, 12, 10 }, { 10, 12, 10 }, { 10, 12, 10 }, { 10, 12, 10 },
    { 10,  6, 15 }, { 10,  6, 15 }, { 10,  6, 15 }, { 10,  6, 15 },
    { 10,  7, 15 }, { 10,  7, 15 }, { 10,  7, 15 }, { 10,  7, 15 },

    { 11,  9, 14 }, { 11,  9, 14 },
    { 11, 15,  8 }, { 11, 15,  8 },
    { 11, 11, 11 }, { 11, 11, 11 },
    { 11, 11, 14 }, { 11, 11, 14 },
    { 11,  1, 15 }, { 11,  1, 15 },
    { 11, 10, 12 }, { 11, 10, 12 },
    { 11, 10, 14 }, { 11, 10, 14 },
    { 11, 13, 11 }, { 11, 13, 11 },
    { 11, 13, 10 }, { 11, 13, 10 },
    { 11, 11, 13 }, { 11, 11, 13 },
    { 11, 11, 12 }, { 11, 11, 12 },
    { 11,  8, 15 }, { 11,  8, 15 },
    { 11, 14, 11 }, { 11, 14, 11 },
    { 11, 13, 12 }, { 11, 13, 12 },
    { 11, 12, 13 }, { 11, 12, 13 },
    { 11, 15,  9 }, { 11, 15,  9 },
    { 11, 14, 10 }, { 11, 14, 10 },
    { 11, 10,  0 }, { 11, 10,  0 },
    { 11, 12, 11 }, { 11, 12, 11 },
    { 11,  9, 15 }, { 11,  9, 15 },
    { 11,  0, 10 }, { 11,  0, 10 },
    { 11, 12, 12 }, { 11, 12, 12 },
    { 11, 11,  0 }, { 11, 11,  0 },
    { 11, 12, 14 }, { 11, 12, 14 },
    { 11, 10, 15 }, { 11, 10, 15 },
    { 11, 13, 13 }, { 11, 13, 13 },
    { 11,  0, 13 }, { 11,  0, 13 },
    { 11, 14, 12 }, { 11, 14, 12 },
    { 11, 15, 10 }, { 11, 15, 10 },
    { 11, 15, 11 }, { 11, 15, 11 },
    { 11, 11, 15 }, { 11, 11, 15 },
    { 11, 14, 13 }, { 11, 14, 13 },
    { 11, 13,  0 }, { 11, 13,  0 },
    { 11,  0, 11 }, { 11,  0, 11 },
    { 11, 13, 14 }, { 11, 13, 14 },
    { 11, 15, 12 }, { 11, 15, 12 },
    { 11, 15, 13 }, { 11, 15, 13 },
    { 11, 12, 15 }, { 11, 12, 15 },
    { 11, 14,  0 }, { 11, 14,  0 },
    { 11, 14, 14 }, { 11, 14, 14 },
    { 11, 13, 15 }, { 11, 13, 15 },
    { 11, 12,  0 }, { 11, 12,  0 },
    { 11, 14, 15 }, { 11, 14, 15 },
    { 12,  0, 14 },
    { 12,  0, 12 },
    { 12, 15, 14 },
    { 12, 15,  0 },
    { 12,  0, 15 },
    { 12, 15, 15 }
};
