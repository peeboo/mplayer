/*
 * this code comes under GPL
 * This code was taken from http://www.mpg123.org
 * See ChangeLog of mpg123-0.59s-pre.1 for detail
 * Applied to mplayer by Nick Kurshev <nickols_k@mail.ru>
 *
 * Local ChangeLog:
 * - Partial loops unrolling and removing MOVW insn from loops
*/
#include "config.h"
#include "mangle.h"
#define real float /* ugly - but only way */

extern void (*dct64_MMX_func)(short*, short*, real*);
static unsigned long long attribute_used __attribute__((aligned(8))) null_one = 0x0000ffff0000ffffULL;
static unsigned long long attribute_used __attribute__((aligned(8))) one_null = 0xffff0000ffff0000ULL;
unsigned int __attribute__((aligned(16))) costab_mmx[] =
{
	1056974725,
	1057056395,
	1057223771,
	1057485416,
	1057855544,
	1058356026,
	1059019886,
	1059897405,
	1061067246,
	1062657950,
	1064892987,
	1066774581,
	1069414683,
	1073984175,
	1079645762,
	1092815430,
	1057005197,
	1057342072,
	1058087743,
	1059427869,
	1061799040,
	1065862217,
	1071413542,
	1084439708,
	1057128951,
	1058664893,
	1063675095,
	1076102863,
	1057655764,
	1067924853,
	1060439283,
};

/**
  This array of magic numbers were calculated by the pure function
  make_decode_tables_MMX(32768), which had been implemented in (deleted since
  r23383) tabinit_MMX.c.
  */
static short __attribute__((aligned(8))) mp3lib_decwins[] =
{
	     0,	     7,	    54,	   114,	   510,	  1288,	  1644,	  9372,
	 18760,	 -9373,	  1644,	 -1289,	   510,	  -115,	    54,	    -8,
	     0,	     7,	    54,	   114,	   510,	  1288,	  1644,	  9372,
	 18760,	 -9373,	  1644,	 -1289,	   510,	  -115,	    54,	    -8,
	     0,	     7,	    55,	   129,	   500,	  1379,	  1490,	  9834,
	 18748,	 -8910,	  1784,	 -1197,	   516,	  -101,	    52,	    -7,
	     0,	     7,	    55,	   129,	   500,	  1379,	  1490,	  9834,
	 18748,	 -8910,	  1784,	 -1197,	   516,	  -101,	    52,	    -7,
	     0,	     8,	    56,	   145,	   488,	  1469,	  1322,	 10294,
	 18714,	 -8448,	  1910,	 -1107,	   520,	   -87,	    51,	    -6,
	     0,	     8,	    56,	   145,	   488,	  1469,	  1322,	 10294,
	 18714,	 -8448,	  1910,	 -1107,	   520,	   -87,	    51,	    -6,
	     0,	     9,	    57,	   161,	   474,	  1559,	  1141,	 10751,
	 18658,	 -7987,	  2023,	 -1016,	   522,	   -74,	    49,	    -6,
	     0,	     9,	    57,	   161,	   474,	  1559,	  1141,	 10751,
	 18658,	 -7987,	  2023,	 -1016,	   522,	   -74,	    49,	    -6,
	     0,	    10,	    57,	   177,	   456,	  1647,	   944,	 11205,
	 18579,	 -7528,	  2123,	  -927,	   522,	   -61,	    48,	    -5,
	     0,	    10,	    57,	   177,	   456,	  1647,	   944,	 11205,
	 18579,	 -7528,	  2123,	  -927,	   522,	   -61,	    48,	    -5,
	     0,	    11,	    57,	   194,	   435,	  1733,	   734,	 11654,
	 18477,	 -7073,	  2210,	  -838,	   519,	   -50,	    46,	    -5,
	     0,	    11,	    57,	   194,	   435,	  1733,	   734,	 11654,
	 18477,	 -7073,	  2210,	  -838,	   519,	   -50,	    46,	    -5,
	     0,	    12,	    57,	   212,	   411,	  1817,	   510,	 12097,
	 18354,	 -6621,	  2285,	  -751,	   515,	   -39,	    44,	    -4,
	     0,	    12,	    57,	   212,	   411,	  1817,	   510,	 12097,
	 18354,	 -6621,	  2285,	  -751,	   515,	   -39,	    44,	    -4,
	     0,	    13,	    57,	   229,	   384,	  1899,	   271,	 12534,
	 18209,	 -6174,	  2348,	  -666,	   508,	   -28,	    43,	    -4,
	     0,	    13,	    57,	   229,	   384,	  1899,	   271,	 12534,
	 18209,	 -6174,	  2348,	  -666,	   508,	   -28,	    43,	    -4,
	     0,	    14,	    56,	   247,	   354,	  1977,	    18,	 12963,
	 18043,	 -5733,	  2398,	  -583,	   501,	   -18,	    41,	    -4,
	     0,	    14,	    56,	   247,	   354,	  1977,	    18,	 12963,
	 18043,	 -5733,	  2398,	  -583,	   501,	   -18,	    41,	    -4,
	     0,	    15,	    56,	   266,	   320,	  2052,	  -249,	 13383,
	 17855,	 -5298,	  2438,	  -502,	   491,	    -9,	    39,	    -3,
	     0,	    15,	    56,	   266,	   320,	  2052,	  -249,	 13383,
	 17855,	 -5298,	  2438,	  -502,	   491,	    -9,	    39,	    -3,
	     0,	    17,	    54,	   284,	   283,	  2122,	  -530,	 13794,
	 17648,	 -4870,	  2466,	  -423,	   480,	    -1,	    37,	    -3,
	     0,	    17,	    54,	   284,	   283,	  2122,	  -530,	 13794,
	 17648,	 -4870,	  2466,	  -423,	   480,	    -1,	    37,	    -3,
	     0,	    18,	    52,	   302,	   243,	  2188,	  -825,	 14194,
	 17420,	 -4450,	  2484,	  -347,	   468,	     7,	    35,	    -3,
	     0,	    18,	    52,	   302,	   243,	  2188,	  -825,	 14194,
	 17420,	 -4450,	  2484,	  -347,	   468,	     7,	    35,	    -3,
	     0,	    19,	    50,	   320,	   199,	  2249,	 -1133,	 14583,
	 17173,	 -4039,	  2492,	  -274,	   455,	    14,	    33,	    -2,
	     0,	    19,	    50,	   320,	   199,	  2249,	 -1133,	 14583,
	 17173,	 -4039,	  2492,	  -274,	   455,	    14,	    33,	    -2,
	    -1,	    21,	    48,	   339,	   152,	  2304,	 -1454,	 14959,
	 16908,	 -3637,	  2490,	  -204,	   440,	    20,	    32,	    -2,
	    -1,	    21,	    48,	   339,	   152,	  2304,	 -1454,	 14959,
	 16908,	 -3637,	  2490,	  -204,	   440,	    20,	    32,	    -2,
	    -1,	    22,	    45,	   357,	   101,	  2354,	 -1788,	 15322,
	 16624,	 -3245,	  2479,	  -137,	   425,	    26,	    30,	    -2,
	    -1,	    22,	    45,	   357,	   101,	  2354,	 -1788,	 15322,
	 16624,	 -3245,	  2479,	  -137,	   425,	    26,	    30,	    -2,
	    -1,	    24,	    41,	   374,	    47,	  2396,	 -2135,	 15671,
	 16323,	 -2864,	  2460,	   -72,	   409,	    31,	    28,	    -2,
	    -1,	    24,	    41,	   374,	    47,	  2396,	 -2135,	 15671,
	 16323,	 -2864,	  2460,	   -72,	   409,	    31,	    28,	    -2,
	    -1,	    26,	    37,	   391,	   -11,	  2431,	 -2493,	 16004,
	 16005,	 -2494,	  2432,	   -12,	   392,	    36,	    26,	    -2,
	    -1,	    26,	    37,	   391,	   -11,	  2431,	 -2493,	 16004,
	 16005,	 -2494,	  2432,	   -12,	   392,	    36,	    26,	    -2,
	    -2,	   -28,	    31,	  -409,	   -72,	 -2460,	 -2864,	-16323,
	 15671,	  2135,	  2396,	   -47,	   374,	   -41,	    24,	     1,
	    -2,	   -28,	    31,	  -409,	   -72,	 -2460,	 -2864,	-16323,
	 15671,	  2135,	  2396,	   -47,	   374,	   -41,	    24,	     1,
	    -2,	   -30,	    26,	  -425,	  -137,	 -2479,	 -3245,	-16624,
	 15322,	  1788,	  2354,	  -101,	   357,	   -45,	    22,	     1,
	    -2,	   -30,	    26,	  -425,	  -137,	 -2479,	 -3245,	-16624,
	 15322,	  1788,	  2354,	  -101,	   357,	   -45,	    22,	     1,
	    -2,	   -32,	    20,	  -440,	  -204,	 -2490,	 -3637,	-16908,
	 14959,	  1454,	  2304,	  -152,	   339,	   -48,	    21,	     1,
	    -2,	   -32,	    20,	  -440,	  -204,	 -2490,	 -3637,	-16908,
	 14959,	  1454,	  2304,	  -152,	   339,	   -48,	    21,	     1,
	    -2,	   -33,	    14,	  -455,	  -274,	 -2492,	 -4039,	-17173,
	 14583,	  1133,	  2249,	  -199,	   320,	   -50,	    19,	     0,
	    -2,	   -33,	    14,	  -455,	  -274,	 -2492,	 -4039,	-17173,
	 14583,	  1133,	  2249,	  -199,	   320,	   -50,	    19,	     0,
	    -3,	   -35,	     7,	  -468,	  -347,	 -2484,	 -4450,	-17420,
	 14194,	   825,	  2188,	  -243,	   302,	   -52,	    18,	     0,
	    -3,	   -35,	     7,	  -468,	  -347,	 -2484,	 -4450,	-17420,
	 14194,	   825,	  2188,	  -243,	   302,	   -52,	    18,	     0,
	    -3,	   -37,	    -1,	  -480,	  -423,	 -2466,	 -4870,	-17648,
	 13794,	   530,	  2122,	  -283,	   284,	   -54,	    17,	     0,
	    -3,	   -37,	    -1,	  -480,	  -423,	 -2466,	 -4870,	-17648,
	 13794,	   530,	  2122,	  -283,	   284,	   -54,	    17,	     0,
	    -3,	   -39,	    -9,	  -491,	  -502,	 -2438,	 -5298,	-17855,
	 13383,	   249,	  2052,	  -320,	   266,	   -56,	    15,	     0,
	    -3,	   -39,	    -9,	  -491,	  -502,	 -2438,	 -5298,	-17855,
	 13383,	   249,	  2052,	  -320,	   266,	   -56,	    15,	     0,
	    -4,	   -41,	   -18,	  -501,	  -583,	 -2398,	 -5733,	-18043,
	 12963,	   -18,	  1977,	  -354,	   247,	   -56,	    14,	     0,
	    -4,	   -41,	   -18,	  -501,	  -583,	 -2398,	 -5733,	-18043,
	 12963,	   -18,	  1977,	  -354,	   247,	   -56,	    14,	     0,
	    -4,	   -43,	   -28,	  -508,	  -666,	 -2348,	 -6174,	-18209,
	 12534,	  -271,	  1899,	  -384,	   229,	   -57,	    13,	     0,
	    -4,	   -43,	   -28,	  -508,	  -666,	 -2348,	 -6174,	-18209,
	 12534,	  -271,	  1899,	  -384,	   229,	   -57,	    13,	     0,
	    -4,	   -44,	   -39,	  -515,	  -751,	 -2285,	 -6621,	-18354,
	 12097,	  -510,	  1817,	  -411,	   212,	   -57,	    12,	     0,
	    -4,	   -44,	   -39,	  -515,	  -751,	 -2285,	 -6621,	-18354,
	 12097,	  -510,	  1817,	  -411,	   212,	   -57,	    12,	     0,
	    -5,	   -46,	   -50,	  -519,	  -838,	 -2210,	 -7073,	-18477,
	 11654,	  -734,	  1733,	  -435,	   194,	   -57,	    11,	     0,
	    -5,	   -46,	   -50,	  -519,	  -838,	 -2210,	 -7073,	-18477,
	 11654,	  -734,	  1733,	  -435,	   194,	   -57,	    11,	     0,
	    -5,	   -48,	   -61,	  -522,	  -927,	 -2123,	 -7528,	-18579,
	 11205,	  -944,	  1647,	  -456,	   177,	   -57,	    10,	     0,
	    -5,	   -48,	   -61,	  -522,	  -927,	 -2123,	 -7528,	-18579,
	 11205,	  -944,	  1647,	  -456,	   177,	   -57,	    10,	     0,
	    -6,	   -49,	   -74,	  -522,	 -1016,	 -2023,	 -7987,	-18658,
	 10751,	 -1141,	  1559,	  -474,	   161,	   -57,	     9,	     0,
	    -6,	   -49,	   -74,	  -522,	 -1016,	 -2023,	 -7987,	-18658,
	 10751,	 -1141,	  1559,	  -474,	   161,	   -57,	     9,	     0,
	    -6,	   -51,	   -87,	  -520,	 -1107,	 -1910,	 -8448,	-18714,
	 10294,	 -1322,	  1469,	  -488,	   145,	   -56,	     8,	     0,
	    -6,	   -51,	   -87,	  -520,	 -1107,	 -1910,	 -8448,	-18714,
	 10294,	 -1322,	  1469,	  -488,	   145,	   -56,	     8,	     0,
	    -7,	   -52,	  -101,	  -516,	 -1197,	 -1784,	 -8910,	-18748,
	  9834,	 -1490,	  1379,	  -500,	   129,	   -55,	     7,	     0,
	    -7,	   -52,	  -101,	  -516,	 -1197,	 -1784,	 -8910,	-18748,
	  9834,	 -1490,	  1379,	  -500,	   129,	   -55,	     7,	     0,
};

int synth_1to1_MMX(real *bandPtr, int channel, short *samples)
{
    static short buffs[2][2][0x110] __attribute__((aligned(8)));
    static int bo = 1;
    short *b0, (*buf)[0x110], *a, *b;
    short* window;
    int bo1, i = 8;

    if (channel == 0) {
	bo = (bo - 1) & 0xf;
	buf = buffs[1];
    } else {
	samples++;
	buf = buffs[0];
    }

    if (bo & 1) {
	b0 = buf[1];
	bo1 = bo + 1;
       	a = buf[0] + bo;
	b = buf[1] + ((bo + 1) & 0xf);
    } else {
	b0 = buf[0];
	bo1 = bo;
	b = buf[0] + bo;
       	a = buf[1] + ((bo + 1) & 0xf);
    }

    dct64_MMX_func(a, b, bandPtr);
    window = mp3lib_decwins + 16 - bo1;
    //printf("DEBUG: channel %d, bo %d, off %d\n", channel, bo, 16 - bo1);
__asm __volatile(
ASMALIGN(4)
".L03:\n\t"
        "movq  (%1),%%mm0\n\t"
        "movq  64(%1),%%mm4\n\t"
        "pmaddwd (%2),%%mm0\n\t"
        "pmaddwd 32(%2),%%mm4\n\t"
        "movq  8(%1),%%mm1\n\t"
        "movq  72(%1),%%mm5\n\t"
        "pmaddwd 8(%2),%%mm1\n\t"
        "pmaddwd 40(%2),%%mm5\n\t"
        "movq  16(%1),%%mm2\n\t"
        "movq  80(%1),%%mm6\n\t"
        "pmaddwd 16(%2),%%mm2\n\t"
        "pmaddwd 48(%2),%%mm6\n\t"
        "movq  24(%1),%%mm3\n\t"
        "movq  88(%1),%%mm7\n\t"
        "pmaddwd 24(%2),%%mm3\n\t"
        "pmaddwd 56(%2),%%mm7\n\t"
        "paddd %%mm1,%%mm0\n\t"
        "paddd %%mm5,%%mm4\n\t"
        "paddd %%mm2,%%mm0\n\t"
        "paddd %%mm6,%%mm4\n\t"
        "paddd %%mm3,%%mm0\n\t"
        "paddd %%mm7,%%mm4\n\t"
        "movq  %%mm0,%%mm1\n\t"
        "movq  %%mm4,%%mm5\n\t"
        "psrlq $32,%%mm1\n\t"
        "psrlq $32,%%mm5\n\t"
        "paddd %%mm1,%%mm0\n\t"
        "paddd %%mm5,%%mm4\n\t"
        "psrad $13,%%mm0\n\t"
        "psrad $13,%%mm4\n\t"
        "packssdw %%mm0,%%mm0\n\t"
        "packssdw %%mm4,%%mm4\n\t"

	"movq	(%3), %%mm1\n\t"
	"punpckldq %%mm4, %%mm0\n\t"
	"pand   "MANGLE(one_null)", %%mm1\n\t"
	"pand   "MANGLE(null_one)", %%mm0\n\t"
	"por    %%mm0, %%mm1\n\t"
	"movq   %%mm1,(%3)\n\t"

        "add $64,%2\n\t"
        "add $128,%1\n\t"
        "add $8,%3\n\t"

	"decl %0\n\t"
        "jnz  .L03\n\t"

        "movq  (%1),%%mm0\n\t"
        "pmaddwd (%2),%%mm0\n\t"
        "movq  8(%1),%%mm1\n\t"
        "pmaddwd 8(%2),%%mm1\n\t"
        "movq  16(%1),%%mm2\n\t"
        "pmaddwd 16(%2),%%mm2\n\t"
        "movq  24(%1),%%mm3\n\t"
        "pmaddwd 24(%2),%%mm3\n\t"
        "paddd %%mm1,%%mm0\n\t"
        "paddd %%mm2,%%mm0\n\t"
        "paddd %%mm3,%%mm0\n\t"
        "movq  %%mm0,%%mm1\n\t"
        "psrlq $32,%%mm1\n\t"
        "paddd %%mm1,%%mm0\n\t"
        "psrad $13,%%mm0\n\t"
        "packssdw %%mm0,%%mm0\n\t"
        "movd %%mm0,%%eax\n\t"
	"movw %%ax, (%3)\n\t"
        "sub $32,%2\n\t"
        "add $64,%1\n\t"
        "add $4,%3\n\t"

        "movl $7,%0\n\t"
ASMALIGN(4)
".L04:\n\t"
        "movq  (%1),%%mm0\n\t"
        "movq  64(%1),%%mm4\n\t"
        "pmaddwd (%2),%%mm0\n\t"
        "pmaddwd -32(%2),%%mm4\n\t"
        "movq  8(%1),%%mm1\n\t"
        "movq  72(%1),%%mm5\n\t"
        "pmaddwd 8(%2),%%mm1\n\t"
        "pmaddwd -24(%2),%%mm5\n\t"
        "movq  16(%1),%%mm2\n\t"
        "movq  80(%1),%%mm6\n\t"
        "pmaddwd 16(%2),%%mm2\n\t"
        "pmaddwd -16(%2),%%mm6\n\t"
        "movq  24(%1),%%mm3\n\t"
        "movq  88(%1),%%mm7\n\t"
        "pmaddwd 24(%2),%%mm3\n\t"
        "pmaddwd -8(%2),%%mm7\n\t"
        "paddd %%mm1,%%mm0\n\t"
        "paddd %%mm5,%%mm4\n\t"
        "paddd %%mm2,%%mm0\n\t"
        "paddd %%mm6,%%mm4\n\t"
        "paddd %%mm3,%%mm0\n\t"
        "paddd %%mm7,%%mm4\n\t"
        "movq  %%mm0,%%mm1\n\t"
        "movq  %%mm4,%%mm5\n\t"
        "psrlq $32,%%mm1\n\t"
        "psrlq $32,%%mm5\n\t"
        "paddd %%mm0,%%mm1\n\t"
        "paddd %%mm4,%%mm5\n\t"
        "psrad $13,%%mm1\n\t"
        "psrad $13,%%mm5\n\t"
        "packssdw %%mm1,%%mm1\n\t"
        "packssdw %%mm5,%%mm5\n\t"
        "psubd %%mm0,%%mm0\n\t"
        "psubd %%mm4,%%mm4\n\t"
        "psubsw %%mm1,%%mm0\n\t"
        "psubsw %%mm5,%%mm4\n\t"

	"movq	(%3), %%mm1\n\t"
	"punpckldq %%mm4, %%mm0\n\t"
	"pand   "MANGLE(one_null)", %%mm1\n\t"
	"pand   "MANGLE(null_one)", %%mm0\n\t"
	"por    %%mm0, %%mm1\n\t"
	"movq   %%mm1,(%3)\n\t"

        "sub $64,%2\n\t"
        "add $128,%1\n\t"
        "add $8,%3\n\t"
        "decl %0\n\t"
	"jnz  .L04\n\t"

        "movq  (%1),%%mm0\n\t"
        "pmaddwd (%2),%%mm0\n\t"
        "movq  8(%1),%%mm1\n\t"
        "pmaddwd 8(%2),%%mm1\n\t"
        "movq  16(%1),%%mm2\n\t"
        "pmaddwd 16(%2),%%mm2\n\t"
        "movq  24(%1),%%mm3\n\t"
        "pmaddwd 24(%2),%%mm3\n\t"
        "paddd %%mm1,%%mm0\n\t"
        "paddd %%mm2,%%mm0\n\t"
        "paddd %%mm3,%%mm0\n\t"
        "movq  %%mm0,%%mm1\n\t"
        "psrlq $32,%%mm1\n\t"
        "paddd %%mm0,%%mm1\n\t"
        "psrad $13,%%mm1\n\t"
        "packssdw %%mm1,%%mm1\n\t"
        "psubd %%mm0,%%mm0\n\t"
        "psubsw %%mm1,%%mm0\n\t"
        "movd %%mm0,%%eax\n\t"
	"movw %%ax,(%3)\n\t"
	"emms\n\t"
	:"+r"(i), "+r"(window), "+r"(b0), "+r"(samples)
	:
	:"memory", "%eax");
    return 0;
}

