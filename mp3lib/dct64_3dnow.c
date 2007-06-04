/*
* This code was taken from http://www.mpg123.org
* See ChangeLog of mpg123-0.59s-pre.1 for detail
* Applied to mplayer by Nick Kurshev <nickols_k@mail.ru>
* Partial 3dnow! optimization by Nick Kurshev
*
* TODO: optimize scalar 3dnow! code
* Warning: Phases 7 & 8 are not tested
*/
#define real float /* ugly - but only way */

#include "config.h"
#include "mangle.h"

static unsigned long long int attribute_used __attribute__((aligned(8))) x_plus_minus_3dnow = 0x8000000000000000ULL;
static float attribute_used plus_1f = 1.0;

void dct64_MMX_3dnow(short *a,short *b,real *c)
{
  char tmp[256];
    __asm __volatile(
"	movl %2,%%eax\n\t"

"	leal 128+%3,%%edx\n\t"
"	movl %0,%%esi\n\t"
"	movl %1,%%edi\n\t"
"	movl $"MANGLE(costab_mmx)",%%ebx\n\t"
"	leal %3,%%ecx\n\t"

/* Phase 1*/
"	movq	(%%eax), %%mm0\n\t"
"	movq	8(%%eax), %%mm4\n\t"
"	movq	%%mm0, %%mm3\n\t"
"	movq	%%mm4, %%mm7\n\t"
"	movq	120(%%eax), %%mm1\n\t"
"	movq	112(%%eax), %%mm5\n\t"
/* n.b.: pswapd*/
"	movq	%%mm1, %%mm2\n\t"
"	movq	%%mm5, %%mm6\n\t"
"	psrlq	$32, %%mm1\n\t"
"	psrlq	$32, %%mm5\n\t"
"	punpckldq %%mm2, %%mm1\n\t"
"	punpckldq %%mm6, %%mm5\n\t"
/**/
"	pfadd	%%mm1, %%mm0\n\t"
"	pfadd	%%mm5, %%mm4\n\t"
"	movq	%%mm0, (%%edx)\n\t"
"	movq	%%mm4, 8(%%edx)\n\t"
"	pfsub	%%mm1, %%mm3\n\t"
"	pfsub	%%mm5, %%mm7\n\t"
"	pfmul	(%%ebx), %%mm3\n\t"
"	pfmul	8(%%ebx), %%mm7\n\t"
"	movd	%%mm3, 124(%%edx)\n\t"
"	movd	%%mm7, 116(%%edx)\n\t"
"	psrlq	$32, %%mm3\n\t"
"	psrlq	$32, %%mm7\n\t"
"	movd	%%mm3, 120(%%edx)\n\t"
"	movd	%%mm7, 112(%%edx)\n\t"

"	movq	16(%%eax), %%mm0\n\t"
"	movq	24(%%eax), %%mm4\n\t"
"	movq	%%mm0, %%mm3\n\t"
"	movq	%%mm4, %%mm7\n\t"
"	movq	104(%%eax), %%mm1\n\t"
"	movq	96(%%eax), %%mm5\n\t"
/* n.b.: pswapd*/
"	movq	%%mm1, %%mm2\n\t"
"	movq	%%mm5, %%mm6\n\t"
"	psrlq	$32, %%mm1\n\t"
"	psrlq	$32, %%mm5\n\t"
"	punpckldq %%mm2, %%mm1\n\t"
"	punpckldq %%mm6, %%mm5\n\t"
/**/
"	pfadd	%%mm1, %%mm0\n\t"
"	pfadd	%%mm5, %%mm4\n\t"
"	movq	%%mm0, 16(%%edx)\n\t"
"	movq	%%mm4, 24(%%edx)\n\t"
"	pfsub	%%mm1, %%mm3\n\t"
"	pfsub	%%mm5, %%mm7\n\t"
"	pfmul	16(%%ebx), %%mm3\n\t"
"	pfmul	24(%%ebx), %%mm7\n\t"
"	movd	%%mm3, 108(%%edx)\n\t"
"	movd	%%mm7, 100(%%edx)\n\t"
"	psrlq	$32, %%mm3\n\t"
"	psrlq	$32, %%mm7\n\t"
"	movd	%%mm3, 104(%%edx)\n\t"
"	movd	%%mm7, 96(%%edx)\n\t"

"	movq	32(%%eax), %%mm0\n\t"
"	movq	40(%%eax), %%mm4\n\t"
"	movq	%%mm0, %%mm3\n\t"
"	movq	%%mm4, %%mm7\n\t"
"	movq	88(%%eax), %%mm1\n\t"
"	movq	80(%%eax), %%mm5\n\t"
/* n.b.: pswapd*/
"	movq	%%mm1, %%mm2\n\t"
"	movq	%%mm5, %%mm6\n\t"
"	psrlq	$32, %%mm1\n\t"
"	psrlq	$32, %%mm5\n\t"
"	punpckldq %%mm2, %%mm1\n\t"
"	punpckldq %%mm6, %%mm5\n\t"
/**/
"	pfadd	%%mm1, %%mm0\n\t"
"	pfadd	%%mm5, %%mm4\n\t"
"	movq	%%mm0, 32(%%edx)\n\t"
"	movq	%%mm4, 40(%%edx)\n\t"
"	pfsub	%%mm1, %%mm3\n\t"
"	pfsub	%%mm5, %%mm7\n\t"
"	pfmul	32(%%ebx), %%mm3\n\t"
"	pfmul	40(%%ebx), %%mm7\n\t"
"	movd	%%mm3, 92(%%edx)\n\t"
"	movd	%%mm7, 84(%%edx)\n\t"
"	psrlq	$32, %%mm3\n\t"
"	psrlq	$32, %%mm7\n\t"
"	movd	%%mm3, 88(%%edx)\n\t"
"	movd	%%mm7, 80(%%edx)\n\t"

"	movq	48(%%eax), %%mm0\n\t"
"	movq	56(%%eax), %%mm4\n\t"
"	movq	%%mm0, %%mm3\n\t"
"	movq	%%mm4, %%mm7\n\t"
"	movq	72(%%eax), %%mm1\n\t"
"	movq	64(%%eax), %%mm5\n\t"
/* n.b.: pswapd*/
"	movq	%%mm1, %%mm2\n\t"
"	movq	%%mm5, %%mm6\n\t"
"	psrlq	$32, %%mm1\n\t"
"	psrlq	$32, %%mm5\n\t"
"	punpckldq %%mm2, %%mm1\n\t"
"	punpckldq %%mm6, %%mm5\n\t"
/**/
"	pfadd	%%mm1, %%mm0\n\t"
"	pfadd	%%mm5, %%mm4\n\t"
"	movq	%%mm0, 48(%%edx)\n\t"
"	movq	%%mm4, 56(%%edx)\n\t"
"	pfsub	%%mm1, %%mm3\n\t"
"	pfsub	%%mm5, %%mm7\n\t"
"	pfmul	48(%%ebx), %%mm3\n\t"
"	pfmul	56(%%ebx), %%mm7\n\t"
"	movd	%%mm3, 76(%%edx)\n\t"
"	movd	%%mm7, 68(%%edx)\n\t"
"	psrlq	$32, %%mm3\n\t"
"	psrlq	$32, %%mm7\n\t"
"	movd	%%mm3, 72(%%edx)\n\t"
"	movd	%%mm7, 64(%%edx)\n\t"

/* Phase 2*/

"	movq	(%%edx), %%mm0\n\t"
"	movq	8(%%edx), %%mm4\n\t"
"	movq	%%mm0, %%mm3\n\t"
"	movq	%%mm4, %%mm7\n\t"
"	movq	56(%%edx), %%mm1\n\t"
"	movq	48(%%edx), %%mm5\n\t"
/* n.b.: pswapd*/
"	movq	%%mm1, %%mm2\n\t"
"	movq	%%mm5, %%mm6\n\t"
"	psrlq	$32, %%mm1\n\t"
"	psrlq	$32, %%mm5\n\t"
"	punpckldq %%mm2, %%mm1\n\t"
"	punpckldq %%mm6, %%mm5\n\t"
/**/
"	pfadd	%%mm1, %%mm0\n\t"
"	pfadd	%%mm5, %%mm4\n\t"
"	movq	%%mm0, (%%ecx)\n\t"
"	movq	%%mm4, 8(%%ecx)\n\t"
"	pfsub	%%mm1, %%mm3\n\t"
"	pfsub	%%mm5, %%mm7\n\t"
"	pfmul	64(%%ebx), %%mm3\n\t"
"	pfmul	72(%%ebx), %%mm7\n\t"
"	movd	%%mm3, 60(%%ecx)\n\t"
"	movd	%%mm7, 52(%%ecx)\n\t"
"	psrlq	$32, %%mm3\n\t"
"	psrlq	$32, %%mm7\n\t"
"	movd	%%mm3, 56(%%ecx)\n\t"
"	movd	%%mm7, 48(%%ecx)\n\t"

"	movq	16(%%edx), %%mm0\n\t"
"	movq	24(%%edx), %%mm4\n\t"
"	movq	%%mm0, %%mm3\n\t"
"	movq	%%mm4, %%mm7\n\t"
"	movq	40(%%edx), %%mm1\n\t"
"	movq	32(%%edx), %%mm5\n\t"
/* n.b.: pswapd*/
"	movq	%%mm1, %%mm2\n\t"
"	movq	%%mm5, %%mm6\n\t"
"	psrlq	$32, %%mm1\n\t"
"	psrlq	$32, %%mm5\n\t"
"	punpckldq %%mm2, %%mm1\n\t"
"	punpckldq %%mm6, %%mm5\n\t"
/**/
"	pfadd	%%mm1, %%mm0\n\t"
"	pfadd	%%mm5, %%mm4\n\t"
"	movq	%%mm0, 16(%%ecx)\n\t"
"	movq	%%mm4, 24(%%ecx)\n\t"
"	pfsub	%%mm1, %%mm3\n\t"
"	pfsub	%%mm5, %%mm7\n\t"
"	pfmul	80(%%ebx), %%mm3\n\t"
"	pfmul	88(%%ebx), %%mm7\n\t"
"	movd	%%mm3, 44(%%ecx)\n\t"
"	movd	%%mm7, 36(%%ecx)\n\t"
"	psrlq	$32, %%mm3\n\t"
"	psrlq	$32, %%mm7\n\t"
"	movd	%%mm3, 40(%%ecx)\n\t"
"	movd	%%mm7, 32(%%ecx)\n\t"

/* Phase 3*/

"	movq	64(%%edx), %%mm0\n\t"
"	movq	72(%%edx), %%mm4\n\t"
"	movq	%%mm0, %%mm3\n\t"
"	movq	%%mm4, %%mm7\n\t"
"	movq	120(%%edx), %%mm1\n\t"
"	movq	112(%%edx), %%mm5\n\t"
/* n.b.: pswapd*/
"	movq	%%mm1, %%mm2\n\t"
"	movq	%%mm5, %%mm6\n\t"
"	psrlq	$32, %%mm1\n\t"
"	psrlq	$32, %%mm5\n\t"
"	punpckldq %%mm2, %%mm1\n\t"
"	punpckldq %%mm6, %%mm5\n\t"
/**/
"	pfadd	%%mm1, %%mm0\n\t"
"	pfadd	%%mm5, %%mm4\n\t"
"	movq	%%mm0, 64(%%ecx)\n\t"
"	movq	%%mm4, 72(%%ecx)\n\t"
"	pfsubr	%%mm1, %%mm3\n\t"
"	pfsubr	%%mm5, %%mm7\n\t"
"	pfmul	64(%%ebx), %%mm3\n\t"
"	pfmul	72(%%ebx), %%mm7\n\t"
"	movd	%%mm3, 124(%%ecx)\n\t"
"	movd	%%mm7, 116(%%ecx)\n\t"
"	psrlq	$32, %%mm3\n\t"
"	psrlq	$32, %%mm7\n\t"
"	movd	%%mm3, 120(%%ecx)\n\t"
"	movd	%%mm7, 112(%%ecx)\n\t"

"	movq	80(%%edx), %%mm0\n\t"
"	movq	88(%%edx), %%mm4\n\t"
"	movq	%%mm0, %%mm3\n\t"
"	movq	%%mm4, %%mm7\n\t"
"	movq	104(%%edx), %%mm1\n\t"
"	movq	96(%%edx), %%mm5\n\t"
/* n.b.: pswapd*/
"	movq	%%mm1, %%mm2\n\t"
"	movq	%%mm5, %%mm6\n\t"
"	psrlq	$32, %%mm1\n\t"
"	psrlq	$32, %%mm5\n\t"
"	punpckldq %%mm2, %%mm1\n\t"
"	punpckldq %%mm6, %%mm5\n\t"
/**/
"	pfadd	%%mm1, %%mm0\n\t"
"	pfadd	%%mm5, %%mm4\n\t"
"	movq	%%mm0, 80(%%ecx)\n\t"
"	movq	%%mm4, 88(%%ecx)\n\t"
"	pfsubr	%%mm1, %%mm3\n\t"
"	pfsubr	%%mm5, %%mm7\n\t"
"	pfmul	80(%%ebx), %%mm3\n\t"
"	pfmul	88(%%ebx), %%mm7\n\t"
"	movd	%%mm3, 108(%%ecx)\n\t"
"	movd	%%mm7, 100(%%ecx)\n\t"
"	psrlq	$32, %%mm3\n\t"
"	psrlq	$32, %%mm7\n\t"
"	movd	%%mm3, 104(%%ecx)\n\t"
"	movd	%%mm7, 96(%%ecx)\n\t"

/* Phase 4*/

"	movq	(%%ecx), %%mm0\n\t"
"	movq	8(%%ecx), %%mm4\n\t"
"	movq	%%mm0, %%mm3\n\t"
"	movq	%%mm4, %%mm7\n\t"
"	movq	24(%%ecx), %%mm1\n\t"
"	movq	16(%%ecx), %%mm5\n\t"
/* n.b.: pswapd*/
"	movq	%%mm1, %%mm2\n\t"
"	movq	%%mm5, %%mm6\n\t"
"	psrlq	$32, %%mm1\n\t"
"	psrlq	$32, %%mm5\n\t"
"	punpckldq %%mm2, %%mm1\n\t"
"	punpckldq %%mm6, %%mm5\n\t"
/**/
"	pfadd	%%mm1, %%mm0\n\t"
"	pfadd	%%mm5, %%mm4\n\t"
"	movq	%%mm0, (%%edx)\n\t"
"	movq	%%mm4, 8(%%edx)\n\t"
"	pfsub	%%mm1, %%mm3\n\t"
"	pfsub	%%mm5, %%mm7\n\t"
"	pfmul	96(%%ebx), %%mm3\n\t"
"	pfmul	104(%%ebx), %%mm7\n\t"
"	movd	%%mm3, 28(%%edx)\n\t"
"	movd	%%mm7, 20(%%edx)\n\t"
"	psrlq	$32, %%mm3\n\t"
"	psrlq	$32, %%mm7\n\t"
"	movd	%%mm3, 24(%%edx)\n\t"
"	movd	%%mm7, 16(%%edx)\n\t"

"	movq	32(%%ecx), %%mm0\n\t"
"	movq	40(%%ecx), %%mm4\n\t"
"	movq	%%mm0, %%mm3\n\t"
"	movq	%%mm4, %%mm7\n\t"
"	movq	56(%%ecx), %%mm1\n\t"
"	movq	48(%%ecx), %%mm5\n\t"
/* n.b.: pswapd*/
"	movq	%%mm1, %%mm2\n\t"
"	movq	%%mm5, %%mm6\n\t"
"	psrlq	$32, %%mm1\n\t"
"	psrlq	$32, %%mm5\n\t"
"	punpckldq %%mm2, %%mm1\n\t"
"	punpckldq %%mm6, %%mm5\n\t"
/**/
"	pfadd	%%mm1, %%mm0\n\t"
"	pfadd	%%mm5, %%mm4\n\t"
"	movq	%%mm0, 32(%%edx)\n\t"
"	movq	%%mm4, 40(%%edx)\n\t"
"	pfsubr	%%mm1, %%mm3\n\t"
"	pfsubr	%%mm5, %%mm7\n\t"
"	pfmul	96(%%ebx), %%mm3\n\t"
"	pfmul	104(%%ebx), %%mm7\n\t"
"	movd	%%mm3, 60(%%edx)\n\t"
"	movd	%%mm7, 52(%%edx)\n\t"
"	psrlq	$32, %%mm3\n\t"
"	psrlq	$32, %%mm7\n\t"
"	movd	%%mm3, 56(%%edx)\n\t"
"	movd	%%mm7, 48(%%edx)\n\t"

"	movq	64(%%ecx), %%mm0\n\t"
"	movq	72(%%ecx), %%mm4\n\t"
"	movq	%%mm0, %%mm3\n\t"
"	movq	%%mm4, %%mm7\n\t"
"	movq	88(%%ecx), %%mm1\n\t"
"	movq	80(%%ecx), %%mm5\n\t"
/* n.b.: pswapd*/
"	movq	%%mm1, %%mm2\n\t"
"	movq	%%mm5, %%mm6\n\t"
"	psrlq	$32, %%mm1\n\t"
"	psrlq	$32, %%mm5\n\t"
"	punpckldq %%mm2, %%mm1\n\t"
"	punpckldq %%mm6, %%mm5\n\t"
/**/
"	pfadd	%%mm1, %%mm0\n\t"
"	pfadd	%%mm5, %%mm4\n\t"
"	movq	%%mm0, 64(%%edx)\n\t"
"	movq	%%mm4, 72(%%edx)\n\t"
"	pfsub	%%mm1, %%mm3\n\t"
"	pfsub	%%mm5, %%mm7\n\t"
"	pfmul	96(%%ebx), %%mm3\n\t"
"	pfmul	104(%%ebx), %%mm7\n\t"
"	movd	%%mm3, 92(%%edx)\n\t"
"	movd	%%mm7, 84(%%edx)\n\t"
"	psrlq	$32, %%mm3\n\t"
"	psrlq	$32, %%mm7\n\t"
"	movd	%%mm3, 88(%%edx)\n\t"
"	movd	%%mm7, 80(%%edx)\n\t"

"	movq	96(%%ecx), %%mm0\n\t"
"	movq	104(%%ecx), %%mm4\n\t"
"	movq	%%mm0, %%mm3\n\t"
"	movq	%%mm4, %%mm7\n\t"
"	movq	120(%%ecx), %%mm1\n\t"
"	movq	112(%%ecx), %%mm5\n\t"
/* n.b.: pswapd*/
"	movq	%%mm1, %%mm2\n\t"
"	movq	%%mm5, %%mm6\n\t"
"	psrlq	$32, %%mm1\n\t"
"	psrlq	$32, %%mm5\n\t"
"	punpckldq %%mm2, %%mm1\n\t"
"	punpckldq %%mm6, %%mm5\n\t"
/**/
"	pfadd	%%mm1, %%mm0\n\t"
"	pfadd	%%mm5, %%mm4\n\t"
"	movq	%%mm0, 96(%%edx)\n\t"
"	movq	%%mm4, 104(%%edx)\n\t"
"	pfsubr	%%mm1, %%mm3\n\t"
"	pfsubr	%%mm5, %%mm7\n\t"
"	pfmul	96(%%ebx), %%mm3\n\t"
"	pfmul	104(%%ebx), %%mm7\n\t"
"	movd	%%mm3, 124(%%edx)\n\t"
"	movd	%%mm7, 116(%%edx)\n\t"
"	psrlq	$32, %%mm3\n\t"
"	psrlq	$32, %%mm7\n\t"
"	movd	%%mm3, 120(%%edx)\n\t"
"	movd	%%mm7, 112(%%edx)\n\t"

/* Phase 5 */

"	movq	(%%edx), %%mm0\n\t"
"	movq	16(%%edx), %%mm4\n\t"
"	movq	%%mm0, %%mm3\n\t"
"	movq	%%mm4, %%mm7\n\t"
"	movq	8(%%edx), %%mm1\n\t"
"	movq	24(%%edx), %%mm5\n\t"
/* n.b.: pswapd*/
"	movq	%%mm1, %%mm2\n\t"
"	movq	%%mm5, %%mm6\n\t"
"	psrlq	$32, %%mm1\n\t"
"	psrlq	$32, %%mm5\n\t"
"	punpckldq %%mm2, %%mm1\n\t"
"	punpckldq %%mm6, %%mm5\n\t"
/**/
"	pfadd	%%mm1, %%mm0\n\t"
"	pfadd	%%mm5, %%mm4\n\t"
"	movq	%%mm0, (%%ecx)\n\t"
"	movq	%%mm4, 16(%%ecx)\n\t"
"	pfsub	%%mm1, %%mm3\n\t"
"	pfsubr	%%mm5, %%mm7\n\t"
"	pfmul	112(%%ebx), %%mm3\n\t"
"	pfmul	112(%%ebx), %%mm7\n\t"
"	movd	%%mm3, 12(%%ecx)\n\t"
"	movd	%%mm7, 28(%%ecx)\n\t"
"	psrlq	$32, %%mm3\n\t"
"	psrlq	$32, %%mm7\n\t"
"	movd	%%mm3, 8(%%ecx)\n\t"
"	movd	%%mm7, 24(%%ecx)\n\t"

"	movq	32(%%edx), %%mm0\n\t"
"	movq	48(%%edx), %%mm4\n\t"
"	movq	%%mm0, %%mm3\n\t"
"	movq	%%mm4, %%mm7\n\t"
"	movq	40(%%edx), %%mm1\n\t"
"	movq	56(%%edx), %%mm5\n\t"
/* n.b.: pswapd*/
"	movq	%%mm1, %%mm2\n\t"
"	movq	%%mm5, %%mm6\n\t"
"	psrlq	$32, %%mm1\n\t"
"	psrlq	$32, %%mm5\n\t"
"	punpckldq %%mm2, %%mm1\n\t"
"	punpckldq %%mm6, %%mm5\n\t"
/**/
"	pfadd	%%mm1, %%mm0\n\t"
"	pfadd	%%mm5, %%mm4\n\t"
"	movq	%%mm0, 32(%%ecx)\n\t"
"	movq	%%mm4, 48(%%ecx)\n\t"
"	pfsub	%%mm1, %%mm3\n\t"
"	pfsubr	%%mm5, %%mm7\n\t"
"	pfmul	112(%%ebx), %%mm3\n\t"
"	pfmul	112(%%ebx), %%mm7\n\t"
"	movd	%%mm3, 44(%%ecx)\n\t"
"	movd	%%mm7, 60(%%ecx)\n\t"
"	psrlq	$32, %%mm3\n\t"
"	psrlq	$32, %%mm7\n\t"
"	movd	%%mm3, 40(%%ecx)\n\t"
"	movd	%%mm7, 56(%%ecx)\n\t"

"	movq	64(%%edx), %%mm0\n\t"
"	movq	80(%%edx), %%mm4\n\t"
"	movq	%%mm0, %%mm3\n\t"
"	movq	%%mm4, %%mm7\n\t"
"	movq	72(%%edx), %%mm1\n\t"
"	movq	88(%%edx), %%mm5\n\t"
/* n.b.: pswapd*/
"	movq	%%mm1, %%mm2\n\t"
"	movq	%%mm5, %%mm6\n\t"
"	psrlq	$32, %%mm1\n\t"
"	psrlq	$32, %%mm5\n\t"
"	punpckldq %%mm2, %%mm1\n\t"
"	punpckldq %%mm6, %%mm5\n\t"
/**/
"	pfadd	%%mm1, %%mm0\n\t"
"	pfadd	%%mm5, %%mm4\n\t"
"	movq	%%mm0, 64(%%ecx)\n\t"
"	movq	%%mm4, 80(%%ecx)\n\t"
"	pfsub	%%mm1, %%mm3\n\t"
"	pfsubr	%%mm5, %%mm7\n\t"
"	pfmul	112(%%ebx), %%mm3\n\t"
"	pfmul	112(%%ebx), %%mm7\n\t"
"	movd	%%mm3, 76(%%ecx)\n\t"
"	movd	%%mm7, 92(%%ecx)\n\t"
"	psrlq	$32, %%mm3\n\t"
"	psrlq	$32, %%mm7\n\t"
"	movd	%%mm3, 72(%%ecx)\n\t"
"	movd	%%mm7, 88(%%ecx)\n\t"

"	movq	96(%%edx), %%mm0\n\t"
"	movq	112(%%edx), %%mm4\n\t"
"	movq	%%mm0, %%mm3\n\t"
"	movq	%%mm4, %%mm7\n\t"
"	movq	104(%%edx), %%mm1\n\t"
"	movq	120(%%edx), %%mm5\n\t"
/* n.b.: pswapd*/
"	movq	%%mm1, %%mm2\n\t"
"	movq	%%mm5, %%mm6\n\t"
"	psrlq	$32, %%mm1\n\t"
"	psrlq	$32, %%mm5\n\t"
"	punpckldq %%mm2, %%mm1\n\t"
"	punpckldq %%mm6, %%mm5\n\t"
/**/
"	pfadd	%%mm1, %%mm0\n\t"
"	pfadd	%%mm5, %%mm4\n\t"
"	movq	%%mm0, 96(%%ecx)\n\t"
"	movq	%%mm4, 112(%%ecx)\n\t"
"	pfsub	%%mm1, %%mm3\n\t"
"	pfsubr	%%mm5, %%mm7\n\t"
"	pfmul	112(%%ebx), %%mm3\n\t"
"	pfmul	112(%%ebx), %%mm7\n\t"
"	movd	%%mm3, 108(%%ecx)\n\t"
"	movd	%%mm7, 124(%%ecx)\n\t"
"	psrlq	$32, %%mm3\n\t"
"	psrlq	$32, %%mm7\n\t"
"	movd	%%mm3, 104(%%ecx)\n\t"
"	movd	%%mm7, 120(%%ecx)\n\t"

/* Phase 6. This is the end of easy road. */
/* Code below is coded in scalar mode. Should be optimized */

"	movd	"MANGLE(plus_1f)", %%mm6\n\t"
"	punpckldq 120(%%ebx), %%mm6\n\t"      /* mm6 = 1.0 | 120(%%ebx)*/
"	movq	"MANGLE(x_plus_minus_3dnow)", %%mm7\n\t" /* mm7 = +1 | -1 */

"	movq	32(%%ecx), %%mm0\n\t"
"	movq	64(%%ecx), %%mm2\n\t"
"	movq	%%mm0, %%mm1\n\t"
"	movq	%%mm2, %%mm3\n\t"
"	pxor	%%mm7, %%mm1\n\t"
"	pxor	%%mm7, %%mm3\n\t"
"	pfacc	%%mm1, %%mm0\n\t"
"	pfacc	%%mm3, %%mm2\n\t"
"	pfmul	%%mm6, %%mm0\n\t"
"	pfmul	%%mm6, %%mm2\n\t"
"	movq	%%mm0, 32(%%edx)\n\t"
"	movq	%%mm2, 64(%%edx)\n\t"

"	movd	44(%%ecx), %%mm0\n\t"
"	movd	40(%%ecx), %%mm2\n\t"
"	movd	120(%%ebx), %%mm3\n\t"
"	punpckldq 76(%%ecx), %%mm0\n\t"
"	punpckldq 72(%%ecx), %%mm2\n\t"
"	punpckldq %%mm3, %%mm3\n\t"
"	movq	%%mm0, %%mm4\n\t"
"	movq	%%mm2, %%mm5\n\t"
"	pfsub	%%mm2, %%mm0\n\t"
"	pfmul	%%mm3, %%mm0\n\t"
"	movq	%%mm0, %%mm1\n\t"
"	pfadd	%%mm5, %%mm0\n\t"
"	pfadd	%%mm4, %%mm0\n\t"
"	movq	%%mm0, %%mm2\n\t"
"	punpckldq %%mm1, %%mm0\n\t"
"	punpckhdq %%mm1, %%mm2\n\t"
"	movq	%%mm0, 40(%%edx)\n\t"
"	movq	%%mm2, 72(%%edx)\n\t"

"	movd   48(%%ecx), %%mm3\n\t"
"	movd   60(%%ecx), %%mm2\n\t"
"	pfsub  52(%%ecx), %%mm3\n\t"
"	pfsub  56(%%ecx), %%mm2\n\t"
"	pfmul 120(%%ebx), %%mm3\n\t"
"	pfmul 120(%%ebx), %%mm2\n\t"
"	movq	%%mm2, %%mm1\n\t"

"	pfadd  56(%%ecx), %%mm1\n\t"
"	pfadd  60(%%ecx), %%mm1\n\t"
"	movq	%%mm1, %%mm0\n\t"

"	pfadd  48(%%ecx), %%mm0\n\t"
"	pfadd  52(%%ecx), %%mm0\n\t"
"	pfadd	%%mm3, %%mm1\n\t"
"	punpckldq %%mm2, %%mm1\n\t"
"	pfadd	%%mm3, %%mm2\n\t"
"	punpckldq %%mm2, %%mm0\n\t"
"	movq	%%mm1, 56(%%edx)\n\t"
"	movq	%%mm0, 48(%%edx)\n\t"

/*---*/

"	movd   92(%%ecx), %%mm1\n\t"
"	pfsub  88(%%ecx), %%mm1\n\t"
"	pfmul 120(%%ebx), %%mm1\n\t"
"	movd   %%mm1, 92(%%edx)\n\t"
"	pfadd  92(%%ecx), %%mm1\n\t"
"	pfadd  88(%%ecx), %%mm1\n\t"
"	movq   %%mm1, %%mm0\n\t"

"	pfadd  80(%%ecx), %%mm0\n\t"
"	pfadd  84(%%ecx), %%mm0\n\t"
"	movd   %%mm0, 80(%%edx)\n\t"

"	movd   80(%%ecx), %%mm0\n\t"
"	pfsub  84(%%ecx), %%mm0\n\t"
"	pfmul 120(%%ebx), %%mm0\n\t"
"	pfadd  %%mm0, %%mm1\n\t"
"	pfadd  92(%%edx), %%mm0\n\t"
"	punpckldq %%mm1, %%mm0\n\t"
"	movq   %%mm0, 84(%%edx)\n\t"

"	movq	96(%%ecx), %%mm0\n\t"
"	movq	%%mm0, %%mm1\n\t"
"	pxor	%%mm7, %%mm1\n\t"
"	pfacc	%%mm1, %%mm0\n\t"
"	pfmul	%%mm6, %%mm0\n\t"
"	movq	%%mm0, 96(%%edx)\n\t"

"	movd  108(%%ecx), %%mm0\n\t"
"	pfsub 104(%%ecx), %%mm0\n\t"
"	pfmul 120(%%ebx), %%mm0\n\t"
"	movd  %%mm0, 108(%%edx)\n\t"
"	pfadd 104(%%ecx), %%mm0\n\t"
"	pfadd 108(%%ecx), %%mm0\n\t"
"	movd  %%mm0, 104(%%edx)\n\t"

"	movd  124(%%ecx), %%mm1\n\t"
"	pfsub 120(%%ecx), %%mm1\n\t"
"	pfmul 120(%%ebx), %%mm1\n\t"
"	movd  %%mm1, 124(%%edx)\n\t"
"	pfadd 120(%%ecx), %%mm1\n\t"
"	pfadd 124(%%ecx), %%mm1\n\t"
"	movq  %%mm1, %%mm0\n\t"

"	pfadd 112(%%ecx), %%mm0\n\t"
"	pfadd 116(%%ecx), %%mm0\n\t"
"	movd  %%mm0, 112(%%edx)\n\t"

"	movd  112(%%ecx), %%mm0\n\t"
"	pfsub 116(%%ecx), %%mm0\n\t"
"	pfmul 120(%%ebx), %%mm0\n\t"
"	pfadd %%mm0,%%mm1\n\t"
"	pfadd 124(%%edx), %%mm0\n\t"
"	punpckldq %%mm1, %%mm0\n\t"
"	movq  %%mm0, 116(%%edx)\n\t"

// this code is broken, there is nothing modifying the z flag above.
#if 0
"	jnz .L01\n\t"

/* Phase 7*/
/* Code below is coded in scalar mode. Should be optimized */

"	movd      (%%ecx), %%mm0\n\t"
"	pfadd    4(%%ecx), %%mm0\n\t"
"	movd     %%mm0, 1024(%%esi)\n\t"

"	movd      (%%ecx), %%mm0\n\t"
"	pfsub    4(%%ecx), %%mm0\n\t"
"	pfmul  120(%%ebx), %%mm0\n\t"
"	movd      %%mm0, (%%esi)\n\t"
"	movd      %%mm0, (%%edi)\n\t"

"	movd   12(%%ecx), %%mm0\n\t"
"	pfsub   8(%%ecx), %%mm0\n\t"
"	pfmul 120(%%ebx), %%mm0\n\t"
"	movd    %%mm0, 512(%%edi)\n\t"
"	pfadd   12(%%ecx), %%mm0\n\t"
"	pfadd   8(%%ecx), %%mm0\n\t"
"	movd    %%mm0, 512(%%esi)\n\t"

"	movd   16(%%ecx), %%mm0\n\t"
"	pfsub  20(%%ecx), %%mm0\n\t"
"	pfmul 120(%%ebx), %%mm0\n\t"
"	movq	%%mm0, %%mm3\n\t"

"	movd   28(%%ecx), %%mm0\n\t"
"	pfsub  24(%%ecx), %%mm0\n\t"
"	pfmul 120(%%ebx), %%mm0\n\t"
"	movd    %%mm0, 768(%%edi)\n\t"
"	movq	%%mm0, %%mm2\n\t"

"	pfadd  24(%%ecx), %%mm0\n\t"
"	pfadd  28(%%ecx), %%mm0\n\t"
"	movq	%%mm0, %%mm1\n\t"

"	pfadd  16(%%ecx), %%mm0\n\t"
"	pfadd  20(%%ecx), %%mm0\n\t"
"	movd   %%mm0, 768(%%esi)\n\t"
"	pfadd  %%mm3, %%mm1\n\t"
"	movd   %%mm1, 256(%%esi)\n\t"
"	pfadd  %%mm3, %%mm2\n\t"
"	movd   %%mm2, 256(%%edi)\n\t"

/* Phase 8*/

"	movq   32(%%edx), %%mm0\n\t"
"	movq   48(%%edx), %%mm1\n\t"
"	pfadd  48(%%edx), %%mm0\n\t"
"	pfadd  40(%%edx), %%mm1\n\t"
"	movd   %%mm0, 896(%%esi)\n\t"
"	movd   %%mm1, 640(%%esi)\n\t"
"	psrlq  $32, %%mm0\n\t"
"	psrlq  $32, %%mm1\n\t"
"	movd   %%mm0, 128(%%edi)\n\t"
"	movd   %%mm1, 384(%%edi)\n\t"

"	movd   40(%%edx), %%mm0\n\t"
"	pfadd  56(%%edx), %%mm0\n\t"
"	movd   %%mm0, 384(%%esi)\n\t"

"	movd   56(%%edx), %%mm0\n\t"
"	pfadd  36(%%edx), %%mm0\n\t"
"	movd   %%mm0, 128(%%esi)\n\t"

"	movd   60(%%edx), %%mm0\n\t"
"	movd   %%mm0, 896(%%edi)\n\t"
"	pfadd  44(%%edx), %%mm0\n\t"
"	movd   %%mm0, 640(%%edi)\n\t"

"	movq   96(%%edx), %%mm0\n\t"
"	movq   112(%%edx), %%mm2\n\t"
"	movq   104(%%edx), %%mm4\n\t"
"	pfadd  112(%%edx), %%mm0\n\t"
"	pfadd  104(%%edx), %%mm2\n\t"
"	pfadd  120(%%edx), %%mm4\n\t"
"	movq   %%mm0, %%mm1\n\t"
"	movq   %%mm2, %%mm3\n\t"
"	movq   %%mm4, %%mm5\n\t"
"	pfadd  64(%%edx), %%mm0\n\t"
"	pfadd  80(%%edx), %%mm2\n\t"
"	pfadd  72(%%edx), %%mm4\n\t"
"	movd   %%mm0, 960(%%esi)\n\t"
"	movd   %%mm2, 704(%%esi)\n\t"
"	movd   %%mm4, 448(%%esi)\n\t"
"	psrlq  $32, %%mm0\n\t"
"	psrlq  $32, %%mm2\n\t"
"	psrlq  $32, %%mm4\n\t"
"	movd   %%mm0, 64(%%edi)\n\t"
"	movd   %%mm2, 320(%%edi)\n\t"
"	movd   %%mm4, 576(%%edi)\n\t"
"	pfadd  80(%%edx), %%mm1\n\t"
"	pfadd  72(%%edx), %%mm3\n\t"
"	pfadd  88(%%edx), %%mm5\n\t"
"	movd   %%mm1, 832(%%esi)\n\t"
"	movd   %%mm3, 576(%%esi)\n\t"
"	movd   %%mm5, 320(%%esi)\n\t"
"	psrlq  $32, %%mm1\n\t"
"	psrlq  $32, %%mm3\n\t"
"	psrlq  $32, %%mm5\n\t"
"	movd   %%mm1, 192(%%edi)\n\t"
"	movd   %%mm3, 448(%%edi)\n\t"
"	movd   %%mm5, 704(%%edi)\n\t"

"	movd   120(%%edx), %%mm0\n\t"
"	pfadd  100(%%edx), %%mm0\n\t"
"	movq   %%mm0, %%mm1\n\t"
"	pfadd  88(%%edx), %%mm0\n\t"
"	movd   %%mm0, 192(%%esi)\n\t"
"	pfadd  68(%%edx), %%mm1\n\t"
"	movd   %%mm1, 64(%%esi)\n\t"

"	movd  124(%%edx), %%mm0\n\t"
"	movd  %%mm0, 960(%%edi)\n\t"
"	pfadd  92(%%edx), %%mm0\n\t"
"	movd  %%mm0, 832(%%edi)\n\t"

"	jmp	.L_bye\n\t"
".L01:\n\t"
#endif
/* Phase 9*/

"	movq	(%%ecx), %%mm0\n\t"
"	movq	%%mm0, %%mm1\n\t"
"	pxor    %%mm7, %%mm1\n\t"
"	pfacc	%%mm1, %%mm0\n\t"
"	pfmul	%%mm6, %%mm0\n\t"
"	pf2id	%%mm0, %%mm0\n\t"
"	packssdw %%mm0, %%mm0\n\t"
"	movd	%%mm0, %%eax\n\t"
"	movw    %%ax, 512(%%esi)\n\t"
"	shrl	$16, %%eax\n\t"
"	movw    %%ax, (%%esi)\n\t"

"	movd    12(%%ecx), %%mm0\n\t"
"	pfsub    8(%%ecx), %%mm0\n\t"
"	pfmul  120(%%ebx), %%mm0\n\t"
"	pf2id    %%mm0, %%mm7\n\t"
"	packssdw %%mm7, %%mm7\n\t"
"	movd	 %%mm7, %%eax\n\t"
"	movw     %%ax, 256(%%edi)\n\t"
"	pfadd   12(%%ecx), %%mm0\n\t"
"	pfadd    8(%%ecx), %%mm0\n\t"
"	pf2id    %%mm0, %%mm0\n\t"
"	packssdw %%mm0, %%mm0\n\t"
"	movd	 %%mm0, %%eax\n\t"
"	movw     %%ax, 256(%%esi)\n\t"

"	movd   16(%%ecx), %%mm3\n\t"
"	pfsub  20(%%ecx), %%mm3\n\t"
"	pfmul  120(%%ebx), %%mm3\n\t"
"	movq   %%mm3, %%mm2\n\t"

"	movd   28(%%ecx), %%mm2\n\t"
"	pfsub  24(%%ecx), %%mm2\n\t"
"	pfmul 120(%%ebx), %%mm2\n\t"
"	movq   %%mm2, %%mm1\n\t"

"	pf2id  %%mm2, %%mm7\n\t"
"	packssdw %%mm7, %%mm7\n\t"
"	movd   %%mm7, %%eax\n\t"
"	movw   %%ax, 384(%%edi)\n\t"

"	pfadd  24(%%ecx), %%mm1\n\t"
"	pfadd  28(%%ecx), %%mm1\n\t"
"	movq   %%mm1, %%mm0\n\t"

"	pfadd  16(%%ecx), %%mm0\n\t"
"	pfadd  20(%%ecx), %%mm0\n\t"
"	pf2id  %%mm0, %%mm0\n\t"
"	packssdw %%mm0, %%mm0\n\t"
"	movd   %%mm0, %%eax\n\t"
"	movw   %%ax, 384(%%esi)\n\t"
"	pfadd  %%mm3, %%mm1\n\t"
"	pf2id  %%mm1, %%mm1\n\t"
"	packssdw %%mm1, %%mm1\n\t"
"	movd   %%mm1, %%eax\n\t"
"	movw   %%ax, 128(%%esi)\n\t"
"	pfadd  %%mm3, %%mm2\n\t"
"	pf2id  %%mm2, %%mm2\n\t"
"	packssdw %%mm2, %%mm2\n\t"
"	movd   %%mm2, %%eax\n\t"
"	movw   %%ax, 128(%%edi)\n\t"

/* Phase 10*/

"	movq    32(%%edx), %%mm0\n\t"
"	movq    48(%%edx), %%mm1\n\t"
"	pfadd   48(%%edx), %%mm0\n\t"
"	pfadd   40(%%edx), %%mm1\n\t"
"	pf2id   %%mm0, %%mm0\n\t"
"	pf2id   %%mm1, %%mm1\n\t"
"	packssdw %%mm0, %%mm0\n\t"
"	packssdw %%mm1, %%mm1\n\t"
"	movd	%%mm0, %%eax\n\t"
"	movd	%%mm1, %%ecx\n\t"
"	movw    %%ax, 448(%%esi)\n\t"
"	movw    %%cx, 320(%%esi)\n\t"
"	shrl	$16, %%eax\n\t"
"	shrl	$16, %%ecx\n\t"
"	movw    %%ax, 64(%%edi)\n\t"
"	movw    %%cx, 192(%%edi)\n\t"

"	movd   40(%%edx), %%mm3\n\t"
"	movd   56(%%edx), %%mm4\n\t"
"	movd   60(%%edx), %%mm0\n\t"
"	movd   44(%%edx), %%mm2\n\t"
"	movd  120(%%edx), %%mm5\n\t"
"	punpckldq %%mm4, %%mm3\n\t"
"	punpckldq 124(%%edx), %%mm0\n\t"
"	pfadd 100(%%edx), %%mm5\n\t"
"	punpckldq 36(%%edx), %%mm4\n\t"
"	punpckldq 92(%%edx), %%mm2\n\t"
"	movq  %%mm5, %%mm6\n\t"
"	pfadd  %%mm4, %%mm3\n\t"
"	pf2id  %%mm0, %%mm1\n\t"
"	pf2id  %%mm3, %%mm3\n\t"
"	packssdw %%mm1, %%mm1\n\t"
"	packssdw %%mm3, %%mm3\n\t"
"	pfadd  88(%%edx), %%mm5\n\t"
"	movd   %%mm1, %%eax\n\t"
"	movd   %%mm3, %%ecx\n\t"
"	movw   %%ax, 448(%%edi)\n\t"
"	movw   %%cx, 192(%%esi)\n\t"
"	pf2id  %%mm5, %%mm5\n\t"
"	packssdw %%mm5, %%mm5\n\t"
"	shrl   $16, %%eax\n\t"
"	shrl   $16, %%ecx\n\t"
"	movd   %%mm5, %%ebx\n\t"
"	movw   %%bx, 96(%%esi)\n\t"
"	movw   %%ax, 480(%%edi)\n\t"
"	movw   %%cx, 64(%%esi)\n\t"
"	pfadd  %%mm2, %%mm0\n\t"
"	pf2id  %%mm0, %%mm0\n\t"
"	packssdw %%mm0, %%mm0\n\t"
"	movd   %%mm0, %%eax\n\t"
"	pfadd  68(%%edx), %%mm6\n\t"
"	movw   %%ax, 320(%%edi)\n\t"
"	shr    $16, %%eax\n\t"
"	pf2id  %%mm6, %%mm6\n\t"
"	packssdw %%mm6, %%mm6\n\t"
"	movd   %%mm6, %%ebx\n\t"
"	movw   %%ax, 416(%%edi)\n\t"
"	movw   %%bx, 32(%%esi)\n\t"

"	movq   96(%%edx), %%mm0\n\t"
"	movq  112(%%edx), %%mm2\n\t"
"	movq  104(%%edx), %%mm4\n\t"
"	pfadd %%mm2, %%mm0\n\t"
"	pfadd %%mm4, %%mm2\n\t"
"	pfadd 120(%%edx), %%mm4\n\t"
"	movq  %%mm0, %%mm1\n\t"
"	movq  %%mm2, %%mm3\n\t"
"	movq  %%mm4, %%mm5\n\t"
"	pfadd  64(%%edx), %%mm0\n\t"
"	pfadd  80(%%edx), %%mm2\n\t"
"	pfadd  72(%%edx), %%mm4\n\t"
"	pf2id  %%mm0, %%mm0\n\t"
"	pf2id  %%mm2, %%mm2\n\t"
"	pf2id  %%mm4, %%mm4\n\t"
"	packssdw %%mm0, %%mm0\n\t"
"	packssdw %%mm2, %%mm2\n\t"
"	packssdw %%mm4, %%mm4\n\t"
"	movd   %%mm0, %%eax\n\t"
"	movd   %%mm2, %%ecx\n\t"
"	movd   %%mm4, %%ebx\n\t"
"	movw   %%ax, 480(%%esi)\n\t"
"	movw   %%cx, 352(%%esi)\n\t"
"	movw   %%bx, 224(%%esi)\n\t"
"	shrl   $16, %%eax\n\t"
"	shrl   $16, %%ecx\n\t"
"	shrl   $16, %%ebx\n\t"
"	movw   %%ax, 32(%%edi)\n\t"
"	movw   %%cx, 160(%%edi)\n\t"
"	movw   %%bx, 288(%%edi)\n\t"
"	pfadd  80(%%edx), %%mm1\n\t"
"	pfadd  72(%%edx), %%mm3\n\t"
"	pfadd  88(%%edx), %%mm5\n\t"
"	pf2id  %%mm1, %%mm1\n\t"
"	pf2id  %%mm3, %%mm3\n\t"
"	pf2id  %%mm5, %%mm5\n\t"
"	packssdw %%mm1, %%mm1\n\t"
"	packssdw %%mm3, %%mm3\n\t"
"	packssdw %%mm5, %%mm5\n\t"
"	movd   %%mm1, %%eax\n\t"
"	movd   %%mm3, %%ecx\n\t"
"	movd   %%mm5, %%ebx\n\t"
"	movw   %%ax, 416(%%esi)\n\t"
"	movw   %%cx, 288(%%esi)\n\t"
"	movw   %%bx, 160(%%esi)\n\t"
"	shrl   $16, %%eax\n\t"
"	shrl   $16, %%ecx\n\t"
"	shrl   $16, %%ebx\n\t"
"	movw   %%ax, 96(%%edi)\n\t"
"	movw   %%cx, 224(%%edi)\n\t"
"	movw   %%bx, 352(%%edi)\n\t"

"	movsw\n\t"

".L_bye:\n\t"
"	femms\n\t"
	:
	:"m"(a),"m"(b),"m"(c),"m"(tmp[0])
	:"memory","%eax","%ebx","%ecx","%edx","%esi","%edi");
}
