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
** $Id: hcb_3.h,v 1.1 2003/08/30 22:30:28 arpi Exp $
** detailed CVS changelog at http://www.mplayerhq.hu/cgi-bin/cvsweb.cgi/main/
**/

/* Binary search huffman table HCB_3 */


static hcb_bin_quad hcb3[] = {
    { /*  0 */ 0, {  1,  2, 0, 0 } },
    { /*  1 */ 1, {  0,  0, 0, 0 } }, /* 0 */
    { /*  2 */ 0, {  1,  2, 0, 0 } },
    { /*  3 */ 0, {  2,  3, 0, 0 } },
    { /*  4 */ 0, {  3,  4, 0, 0 } },
    { /*  5 */ 0, {  4,  5, 0, 0 } },
    { /*  6 */ 0, {  5,  6, 0, 0 } },
    { /*  7 */ 0, {  6,  7, 0, 0 } },
    { /*  8 */ 0, {  7,  8, 0, 0 } },
    { /*  9 */ 1, {  1,  0, 0, 0 } }, /* 1000 */
    { /* 10 */ 1, {  0,  0, 0, 1 } }, /* 1001 */
    { /* 11 */ 1, {  0,  1, 0, 0 } }, /* 1010 */
    { /* 12 */ 1, {  0,  0, 1, 0 } }, /* 1011 */
    { /* 13 */ 0, {  4,  5, 0, 0 } },
    { /* 14 */ 0, {  5,  6, 0, 0 } },
    { /* 15 */ 0, {  6,  7, 0, 0 } },
    { /* 16 */ 0, {  7,  8, 0, 0 } },
    { /* 17 */ 1, {  1,  1, 0, 0 } },
    { /* 18 */ 1, {  0,  0, 1, 1 } },
    { /* 19 */ 0, {  6,  7, 0, 0 } },
    { /* 20 */ 0, {  7,  8, 0, 0 } },
    { /* 21 */ 0, {  8,  9, 0, 0 } },
    { /* 22 */ 0, {  9, 10, 0, 0 } },
    { /* 23 */ 0, { 10, 11, 0, 0 } },
    { /* 24 */ 0, { 11, 12, 0, 0 } },
    { /* 25 */ 1, {  0,  1, 1, 0 } }, /* 110100 */
    { /* 26 */ 1, {  0,  1, 0, 1 } }, /* 110101 */
    { /* 27 */ 1, {  1,  0, 1, 0 } }, /* 110110 */
    { /* 28 */ 1, {  0,  1, 1, 1 } }, /* 110111 */
    { /* 29 */ 1, {  1,  0, 0, 1 } }, /* 111000 */
    { /* 30 */ 1, {  1,  1, 1, 0 } }, /* 111001 */
    { /* 31 */ 0, {  6,  7, 0, 0 } },
    { /* 32 */ 0, {  7,  8, 0, 0 } },
    { /* 33 */ 0, {  8,  9, 0, 0 } },
    { /* 34 */ 0, {  9, 10, 0, 0 } },
    { /* 35 */ 0, { 10, 11, 0, 0 } },
    { /* 36 */ 0, { 11, 12, 0, 0 } },
    { /* 37 */ 1, {  1,  1, 1, 1 } }, /* 1110100 */
    { /* 38 */ 1, {  1,  0, 1, 1 } }, /* 1110101 */
    { /* 39 */ 1, {  1,  1, 0, 1 } }, /* 1110110 */
    { /* 40 */ 0, {  9, 10, 0, 0 } },
    { /* 41 */ 0, { 10, 11, 0, 0 } },
    { /* 42 */ 0, { 11, 12, 0, 0 } },
    { /* 43 */ 0, { 12, 13, 0, 0 } },
    { /* 44 */ 0, { 13, 14, 0, 0 } },
    { /* 45 */ 0, { 14, 15, 0, 0 } },
    { /* 46 */ 0, { 15, 16, 0, 0 } },
    { /* 47 */ 0, { 16, 17, 0, 0 } },
    { /* 48 */ 0, { 17, 18, 0, 0 } },
    { /* 49 */ 1, {  2,  0, 0, 0 } }, /* 11101110 */
    { /* 50 */ 1, {  0,  0, 0, 2 } }, /* 11101111 */
    { /* 51 */ 1, {  0,  0, 1, 2 } }, /* 11110000 */
    { /* 52 */ 1, {  2,  1, 0, 0 } }, /* 11110001 */
    { /* 53 */ 1, {  1,  2, 1, 0 } }, /* 11110010 */
    { /* 54 */ 0, { 13, 14, 0, 0 } },
    { /* 55 */ 0, { 14, 15, 0, 0 } },
    { /* 56 */ 0, { 15, 16, 0, 0 } },
    { /* 57 */ 0, { 16, 17, 0, 0 } },
    { /* 58 */ 0, { 17, 18, 0, 0 } },
    { /* 59 */ 0, { 18, 19, 0, 0 } },
    { /* 60 */ 0, { 19, 20, 0, 0 } },
    { /* 61 */ 0, { 20, 21, 0, 0 } },
    { /* 62 */ 0, { 21, 22, 0, 0 } },
    { /* 63 */ 0, { 22, 23, 0, 0 } },
    { /* 64 */ 0, { 23, 24, 0, 0 } },
    { /* 65 */ 0, { 24, 25, 0, 0 } },
    { /* 66 */ 0, { 25, 26, 0, 0 } },
    { /* 67 */ 1, {  0,  0, 2, 1 } },
    { /* 68 */ 1, {  0,  1, 2, 1 } },
    { /* 69 */ 1, {  1,  2, 0, 0 } },
    { /* 70 */ 1, {  0,  1, 1, 2 } },
    { /* 71 */ 1, {  2,  1, 1, 0 } },
    { /* 72 */ 1, {  0,  0, 2, 0 } },
    { /* 73 */ 1, {  0,  2, 1, 0 } },
    { /* 74 */ 1, {  0,  1, 2, 0 } },
    { /* 75 */ 1, {  0,  2, 0, 0 } },
    { /* 76 */ 1, {  0,  1, 0, 2 } },
    { /* 77 */ 1, {  2,  0, 1, 0 } },
    { /* 78 */ 1, {  1,  2, 1, 1 } },
    { /* 79 */ 1, {  0,  2, 1, 1 } },
    { /* 80 */ 1, {  1,  1, 2, 0 } },
    { /* 81 */ 1, {  1,  1, 2, 1 } },
    { /* 82 */ 0, { 11, 12, 0, 0 } },
    { /* 83 */ 0, { 12, 13, 0, 0 } },
    { /* 84 */ 0, { 13, 14, 0, 0 } },
    { /* 85 */ 0, { 14, 15, 0, 0 } },
    { /* 86 */ 0, { 15, 16, 0, 0 } },
    { /* 87 */ 0, { 16, 17, 0, 0 } },
    { /* 88 */ 0, { 17, 18, 0, 0 } },
    { /* 89 */ 0, { 18, 19, 0, 0 } },
    { /* 90 */ 0, { 19, 20, 0, 0 } },
    { /* 91 */ 0, { 20, 21, 0, 0 } },
    { /* 92 */ 0, { 21, 22, 0, 0 } },
    { /* 93 */ 1, {  1,  2,  0,  1 } }, /* 1111101010 */
    { /* 94 */ 1, {  1,  0,  2,  0 } }, /* 1111101011 */
    { /* 95 */ 1, {  1,  0,  2,  1 } }, /* 1111101100 */
    { /* 96 */ 1, {  0,  2,  0,  1 } }, /* 1111101101 */
    { /* 97 */ 1, {  2,  1,  1,  1 } }, /* 1111101110 */
    { /* 98 */ 1, {  1,  1,  1,  2 } }, /* 1111101111 */
    { /* 99 */ 1, {  2,  1,  0,  1 } }, /* 1111110000 */
    { /* 00 */ 1, {  1,  0,  1,  2 } }, /* 1111110001 */
    { /* 01 */ 1, {  0,  0,  2,  2 } }, /* 1111110010 */
    { /* 02 */ 1, {  0,  1,  2,  2 } }, /* 1111110011 */
    { /* 03 */ 1, {  2,  2,  1,  0 } }, /* 1111110100 */
    { /* 04 */ 1, {  1,  2,  2,  0 } }, /* 1111110101 */
    { /* 05 */ 1, {  1,  0,  0,  2 } }, /* 1111110110 */
    { /* 06 */ 1, {  2,  0,  0,  1 } }, /* 1111110111 */
    { /* 07 */ 1, {  0,  2,  2,  1 } }, /* 1111111000 */
    { /* 08 */ 0, {  7,  8, 0, 0 } },
    { /* 09 */ 0, {  8,  9, 0, 0 } },
    { /* 10 */ 0, {  9, 10, 0, 0 } },
    { /* 11 */ 0, { 10, 11, 0, 0 } },
    { /* 12 */ 0, { 11, 12, 0, 0 } },
    { /* 13 */ 0, { 12, 13, 0, 0 } },
    { /* 14 */ 0, { 13, 14, 0, 0 } },
    { /* 15 */ 1, {  2,  2,  0,  0 } }, /* 11111110010 */
    { /* 16 */ 1, {  1,  2,  2,  1 } }, /* 11111110011 */
    { /* 17 */ 1, {  1,  1,  0,  2 } }, /* 11111110100 */
    { /* 18 */ 1, {  2,  0,  1,  1 } }, /* 11111110101 */
    { /* 19 */ 1, {  1,  1,  2,  2 } }, /* 11111110110 */
    { /* 20 */ 1, {  2,  2,  1,  1 } }, /* 11111110111 */
    { /* 21 */ 1, {  0,  2,  2,  0 } }, /* 11111111000 */
    { /* 22 */ 1, {  0,  2,  1,  2 } }, /* 11111111001 */
    { /* 23 */ 0, {  6,  7, 0, 0 } },
    { /* 24 */ 0, {  7,  8, 0, 0 } },
    { /* 25 */ 0, {  8,  9, 0, 0 } },
    { /* 26 */ 0, {  9, 10, 0, 0 } },
    { /* 27 */ 0, { 10, 11, 0, 0 } },
    { /* 28 */ 0, { 11, 12, 0, 0 } },
    { /* 29 */ 1, {  1,  0,  2,  2 } }, /* 111111110100 */
    { /* 30 */ 1, {  2,  2,  0,  1 } }, /* 111111110101 */
    { /* 31 */ 1, {  2,  1,  2,  0 } }, /* 111111110110 */
    { /* 32 */ 1, {  2,  2,  2,  0 } }, /* 111111110111 */
    { /* 33 */ 1, {  0,  2,  2,  2 } }, /* 111111111000 */
    { /* 34 */ 1, {  2,  2,  2,  1 } }, /* 111111111001 */
    { /* 35 */ 1, {  2,  1,  2,  1 } }, /* 111111111010 */
    { /* 36 */ 1, {  1,  2,  1,  2 } }, /* 111111111011 */
    { /* 37 */ 1, {  1,  2,  2,  2 } }, /* 111111111100 */
    { /* 38 */ 0, {  3,  4, 0, 0 } },
    { /* 39 */ 0, {  4,  5, 0, 0 } },
    { /* 40 */ 0, {  5,  6, 0, 0 } },
    { /* 41 */ 1, {  0,  2,  0,  2 } }, /* 1111111111010 */
    { /* 42 */ 1, {  2,  0,  2,  0 } }, /* 1111111111011 */
    { /* 43 */ 1, {  1,  2,  0,  2 } }, /* 1111111111100 */
    { /* 44 */ 0, {  3, 4, 0, 0 } },
    { /* 45 */ 0, {  4, 5, 0, 0 } },
    { /* 46 */ 0, {  5, 6, 0, 0 } },
    { /* 47 */ 1, {  2,  0,  2,  1 } }, /* 11111111111010 */
    { /* 48 */ 1, {  2,  1,  1,  2 } }, /* 11111111111011 */
    { /* 49 */ 1, {  2,  1,  0,  2 } }, /* 11111111111100 */
    { /* 50 */ 0, { 3, 4, 0, 0 } },
    { /* 51 */ 0, { 4, 5, 0, 0 } },
    { /* 52 */ 0, { 5, 6, 0, 0 } },
    { /* 53 */ 1, {  2,  2,  2,  2 } }, /* 111111111111010 */
    { /* 54 */ 1, {  2,  2,  1,  2 } }, /* 111111111111011 */
    { /* 55 */ 1, {  2,  1,  2,  2 } }, /* 111111111111100 */
    { /* 56 */ 1, {  2,  0,  1,  2 } }, /* 111111111111101 */
    { /* 57 */ 1, {  2,  0,  0,  2 } }, /* 111111111111110 */
    { /* 58 */ 0, { 1, 2, 0, 0 } },
    { /* 59 */ 1, {  2,  2,  0,  2 } }, /* 1111111111111110 */
    { /* 60 */ 1, {  2,  0,  2,  2 } }  /* 1111111111111111 */
};
