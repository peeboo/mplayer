# This code was taken from http://www.mpg123.org
# See ChangeLog of mpg123-0.59s-pre.1 for detail
# Applied to mplayer by Nick Kurshev <nickols_k@mail.ru>
# Partial 3dnowex-DSP! optimization by Nick Kurshev
#
# TODO: optimize scalar 3dnow! code
# Warning: Phases 7 & 8 are not tested
#

.text

	.align 16

.globl dct64_MMX_3dnowex
dct64_MMX_3dnowex:
	pushl %ebx
	pushl %esi
	pushl %edi
	subl $256,%esp
	movl 280(%esp),%eax

	leal 128(%esp),%edx
	movl 272(%esp),%esi
	movl 276(%esp),%edi
	movl $costab_mmx,%ebx
	orl %ecx,%ecx
	movl %esp,%ecx

/* Phase 1*/
	movq	(%eax), %mm0
	movq	8(%eax), %mm4
	movq	%mm0, %mm3
	movq	%mm4, %mm7
	movq	120(%eax), %mm1
	movq	112(%eax), %mm5
	pswapd	%mm1, %mm1
	pswapd	%mm5, %mm5
	pfadd	%mm1, %mm0
	pfadd	%mm5, %mm4
	movq	%mm0, (%edx)
	movq	%mm4, 8(%edx)
	pfsub	%mm1, %mm3
	pfsub	%mm5, %mm7
	pfmul	(%ebx), %mm3
	pfmul	8(%ebx), %mm7
	pswapd	%mm3, %mm3
	pswapd	%mm7, %mm7
	movq	%mm3, 120(%edx)
	movq	%mm7, 112(%edx)

	movq	16(%eax), %mm0
	movq	24(%eax), %mm4
	movq	%mm0, %mm3
	movq	%mm4, %mm7
	movq	104(%eax), %mm1
	movq	96(%eax), %mm5
	pswapd	%mm1, %mm1
	pswapd	%mm5, %mm5
	pfadd	%mm1, %mm0
	pfadd	%mm5, %mm4
	movq	%mm0, 16(%edx)
	movq	%mm4, 24(%edx)
	pfsub	%mm1, %mm3
	pfsub	%mm5, %mm7
	pfmul	16(%ebx), %mm3
	pfmul	24(%ebx), %mm7
	pswapd	%mm3, %mm3
	pswapd	%mm7, %mm7
	movq	%mm3, 104(%edx)
	movq	%mm7, 96(%edx)

	movq	32(%eax), %mm0
	movq	40(%eax), %mm4
	movq	%mm0, %mm3
	movq	%mm4, %mm7
	movq	88(%eax), %mm1
	movq	80(%eax), %mm5
	pswapd	%mm1, %mm1
	pswapd	%mm5, %mm5
	pfadd	%mm1, %mm0
	pfadd	%mm5, %mm4
	movq	%mm0, 32(%edx)
	movq	%mm4, 40(%edx)
	pfsub	%mm1, %mm3
	pfsub	%mm5, %mm7
	pfmul	32(%ebx), %mm3
	pfmul	40(%ebx), %mm7
	pswapd	%mm3, %mm3
	pswapd	%mm7, %mm7
	movq	%mm3, 88(%edx)
	movq	%mm7, 80(%edx)

	movq	48(%eax), %mm0
	movq	56(%eax), %mm4
	movq	%mm0, %mm3
	movq	%mm4, %mm7
	movq	72(%eax), %mm1
	movq	64(%eax), %mm5
	pswapd	%mm1, %mm1
	pswapd	%mm5, %mm5
	pfadd	%mm1, %mm0
	pfadd	%mm5, %mm4
	movq	%mm0, 48(%edx)
	movq	%mm4, 56(%edx)
	pfsub	%mm1, %mm3
	pfsub	%mm5, %mm7
	pfmul	48(%ebx), %mm3
	pfmul	56(%ebx), %mm7
	pswapd	%mm3, %mm3
	pswapd	%mm7, %mm7
	movq	%mm3, 72(%edx)
	movq	%mm7, 64(%edx)

/* Phase 2*/

	movq	(%edx), %mm0
	movq	8(%edx), %mm4
	movq	%mm0, %mm3
	movq	%mm4, %mm7
	movq	56(%edx), %mm1
	movq	48(%edx), %mm5
	pswapd	%mm1, %mm1
	pswapd	%mm5, %mm5
	pfadd	%mm1, %mm0
	pfadd	%mm5, %mm4
	movq	%mm0, (%ecx)
	movq	%mm4, 8(%ecx)
	pfsub	%mm1, %mm3
	pfsub	%mm5, %mm7
	pfmul	64(%ebx), %mm3
	pfmul	72(%ebx), %mm7
	pswapd	%mm3, %mm3
	pswapd	%mm7, %mm7
	movq	%mm3, 56(%ecx)
	movq	%mm7, 48(%ecx)
	
	movq	16(%edx), %mm0
	movq	24(%edx), %mm4
	movq	%mm0, %mm3
	movq	%mm4, %mm7
	movq	40(%edx), %mm1
	movq	32(%edx), %mm5
	pswapd	%mm1, %mm1
	pswapd	%mm5, %mm5
	pfadd	%mm1, %mm0
	pfadd	%mm5, %mm4
	movq	%mm0, 16(%ecx)
	movq	%mm4, 24(%ecx)
	pfsub	%mm1, %mm3
	pfsub	%mm5, %mm7
	pfmul	80(%ebx), %mm3
	pfmul	88(%ebx), %mm7
	pswapd	%mm3, %mm3
	pswapd	%mm7, %mm7
	movq	%mm3, 40(%ecx)
	movq	%mm7, 32(%ecx)

/* Phase 3*/

	movq	64(%edx), %mm0
	movq	72(%edx), %mm4
	movq	%mm0, %mm3
	movq	%mm4, %mm7
	movq	120(%edx), %mm1
	movq	112(%edx), %mm5
	pswapd	%mm1, %mm1
	pswapd	%mm5, %mm5
	pfadd	%mm1, %mm0
	pfadd	%mm5, %mm4
	movq	%mm0, 64(%ecx)
	movq	%mm4, 72(%ecx)
	pfsubr	%mm1, %mm3
	pfsubr	%mm5, %mm7
	pfmul	64(%ebx), %mm3
	pfmul	72(%ebx), %mm7
	pswapd	%mm3, %mm3
	pswapd	%mm7, %mm7
	movq	%mm3, 120(%ecx)
	movq	%mm7, 112(%ecx)

	movq	80(%edx), %mm0
	movq	88(%edx), %mm4
	movq	%mm0, %mm3
	movq	%mm4, %mm7
	movq	104(%edx), %mm1
	movq	96(%edx), %mm5
	pswapd	%mm1, %mm1
	pswapd	%mm5, %mm5
	pfadd	%mm1, %mm0
	pfadd	%mm5, %mm4
	movq	%mm0, 80(%ecx)
	movq	%mm4, 88(%ecx)
	pfsubr	%mm1, %mm3
	pfsubr	%mm5, %mm7
	pfmul	80(%ebx), %mm3
	pfmul	88(%ebx), %mm7
	pswapd	%mm3, %mm3
	pswapd	%mm7, %mm7
	movq	%mm3, 104(%ecx)
	movq	%mm7, 96(%ecx)
	
/* Phase 4*/

	movq	(%ecx), %mm0
	movq	8(%ecx), %mm4
	movq	%mm0, %mm3
	movq	%mm4, %mm7
	movq	24(%ecx), %mm1
	movq	16(%ecx), %mm5
	pswapd	%mm1, %mm1
	pswapd	%mm5, %mm5
	pfadd	%mm1, %mm0
	pfadd	%mm5, %mm4
	movq	%mm0, (%edx)
	movq	%mm4, 8(%edx)
	pfsub	%mm1, %mm3
	pfsub	%mm5, %mm7
	pfmul	96(%ebx), %mm3
	pfmul	104(%ebx), %mm7
	pswapd	%mm3, %mm3
	pswapd	%mm7, %mm7
	movq	%mm3, 24(%edx)
	movq	%mm7, 16(%edx)

	movq	32(%ecx), %mm0
	movq	40(%ecx), %mm4
	movq	%mm0, %mm3
	movq	%mm4, %mm7
	movq	56(%ecx), %mm1
	movq	48(%ecx), %mm5
	pswapd	%mm1, %mm1
	pswapd	%mm5, %mm5
	pfadd	%mm1, %mm0
	pfadd	%mm5, %mm4
	movq	%mm0, 32(%edx)
	movq	%mm4, 40(%edx)
	pfsubr	%mm1, %mm3
	pfsubr	%mm5, %mm7
	pfmul	96(%ebx), %mm3
	pfmul	104(%ebx), %mm7
	pswapd	%mm3, %mm3
	pswapd	%mm7, %mm7
	movq	%mm3, 56(%edx)
	movq	%mm7, 48(%edx)

	movq	64(%ecx), %mm0
	movq	72(%ecx), %mm4
	movq	%mm0, %mm3
	movq	%mm4, %mm7
	movq	88(%ecx), %mm1
	movq	80(%ecx), %mm5
	pswapd	%mm1, %mm1
	pswapd	%mm5, %mm5
	pfadd	%mm1, %mm0
	pfadd	%mm5, %mm4
	movq	%mm0, 64(%edx)
	movq	%mm4, 72(%edx)
	pfsub	%mm1, %mm3
	pfsub	%mm5, %mm7
	pfmul	96(%ebx), %mm3
	pfmul	104(%ebx), %mm7
	pswapd	%mm3, %mm3
	pswapd	%mm7, %mm7
	movq	%mm3, 88(%edx)
	movq	%mm7, 80(%edx)

	movq	96(%ecx), %mm0
	movq	104(%ecx), %mm4
	movq	%mm0, %mm3
	movq	%mm4, %mm7
	movq	120(%ecx), %mm1
	movq	112(%ecx), %mm5
	pswapd	%mm1, %mm1
	pswapd	%mm5, %mm5
	pfadd	%mm1, %mm0
	pfadd	%mm5, %mm4
	movq	%mm0, 96(%edx)
	movq	%mm4, 104(%edx)
	pfsubr	%mm1, %mm3
	pfsubr	%mm5, %mm7
	pfmul	96(%ebx), %mm3
	pfmul	104(%ebx), %mm7
	pswapd	%mm3, %mm3
	pswapd	%mm7, %mm7
	movq	%mm3, 120(%edx)
	movq	%mm7, 112(%edx)

/* Phase 5 */

	movq	(%edx), %mm0
	movq	16(%edx), %mm4
	movq	%mm0, %mm3
	movq	%mm4, %mm7
	movq	8(%edx), %mm1
	movq	24(%edx), %mm5
	pswapd	%mm1, %mm1
	pswapd	%mm5, %mm5
	pfadd	%mm1, %mm0
	pfadd	%mm5, %mm4
	movq	%mm0, (%ecx)
	movq	%mm4, 16(%ecx)
	pfsub	%mm1, %mm3
	pfsubr	%mm5, %mm7
	pfmul	112(%ebx), %mm3
	pfmul	112(%ebx), %mm7
	pswapd	%mm3, %mm3
	pswapd	%mm7, %mm7
	movq	%mm3, 8(%ecx)
	movq	%mm7, 24(%ecx)

	movq	32(%edx), %mm0
	movq	48(%edx), %mm4
	movq	%mm0, %mm3
	movq	%mm4, %mm7
	movq	40(%edx), %mm1
	movq	56(%edx), %mm5
	pswapd	%mm1, %mm1
	pswapd	%mm5, %mm5
	pfadd	%mm1, %mm0
	pfadd	%mm5, %mm4
	movq	%mm0, 32(%ecx)
	movq	%mm4, 48(%ecx)
	pfsub	%mm1, %mm3
	pfsubr	%mm5, %mm7
	pfmul	112(%ebx), %mm3
	pfmul	112(%ebx), %mm7
	pswapd	%mm3, %mm3
	pswapd	%mm7, %mm7
	movq	%mm3, 40(%ecx)
	movq	%mm7, 56(%ecx)

	movq	64(%edx), %mm0
	movq	80(%edx), %mm4
	movq	%mm0, %mm3
	movq	%mm4, %mm7
	movq	72(%edx), %mm1
	movq	88(%edx), %mm5
	pswapd	%mm1, %mm1
	pswapd	%mm5, %mm5
	pfadd	%mm1, %mm0
	pfadd	%mm5, %mm4
	movq	%mm0, 64(%ecx)
	movq	%mm4, 80(%ecx)
	pfsub	%mm1, %mm3
	pfsubr	%mm5, %mm7
	pfmul	112(%ebx), %mm3
	pfmul	112(%ebx), %mm7
	pswapd	%mm3, %mm3
	pswapd	%mm7, %mm7
	movq	%mm3, 72(%ecx)
	movq	%mm7, 88(%ecx)

	movq	96(%edx), %mm0
	movq	112(%edx), %mm4
	movq	%mm0, %mm3
	movq	%mm4, %mm7
	movq	104(%edx), %mm1
	movq	120(%edx), %mm5
	pswapd	%mm1, %mm1
	pswapd	%mm5, %mm5
	pfadd	%mm1, %mm0
	pfadd	%mm5, %mm4
	movq	%mm0, 96(%ecx)
	movq	%mm4, 112(%ecx)
	pfsub	%mm1, %mm3
	pfsubr	%mm5, %mm7
	pfmul	112(%ebx), %mm3
	pfmul	112(%ebx), %mm7
	pswapd	%mm3, %mm3
	pswapd	%mm7, %mm7
	movq	%mm3, 104(%ecx)
	movq	%mm7, 120(%ecx)
	
/* Phase 6. This is the end of easy road. */
/* Code below is coded in scalar mode. Should be optimized */

	movd   32(%ecx), %mm0
	pfadd  36(%ecx), %mm0
	movd   %mm0, 32(%edx)

	movd   32(%ecx), %mm0
	pfsub  36(%ecx), %mm0
	pfmul  120(%ebx),%mm0
	movd   %mm0, 36(%edx)

	movd   44(%ecx), %mm0
	pfsub  40(%ecx), %mm0
	pfmul  120(%ebx),%mm0

	movd   %mm0, 44(%edx)
	pfadd  40(%ecx), %mm0
	pfadd  44(%ecx), %mm0
	movd   %mm0, 40(%edx)

	movd   48(%ecx), %mm3
	pfsub  52(%ecx), %mm3
	pfmul 120(%ebx), %mm3

	movd   60(%ecx), %mm2
	pfsub  56(%ecx), %mm2
	pfmul 120(%ebx), %mm2
	movq	%mm2, %mm1

	pfadd  56(%ecx), %mm1
	pfadd  60(%ecx), %mm1
	movq	%mm1, %mm0

	pfadd  48(%ecx), %mm0
	pfadd  52(%ecx), %mm0
	movd   %mm0, 48(%edx)
	pfadd  %mm3, %mm1
	movd   %mm1, 56(%edx)
	movd   %mm2, 60(%edx)
	pfadd  %mm3, %mm2
	movd   %mm2, 52(%edx)

/*---*/
	movd   64(%ecx), %mm0
	pfadd  68(%ecx), %mm0
	movd   %mm0, 64(%edx)

	movd   64(%ecx), %mm0
	pfsub  68(%ecx), %mm0
	pfmul 120(%ebx), %mm0
	movd   %mm0, 68(%edx)

	movd   76(%ecx), %mm0
	pfsub  72(%ecx), %mm0
	pfmul 120(%ebx), %mm0
	movd   %mm0, 76(%edx)
	pfadd  72(%ecx), %mm0
	pfadd  76(%ecx), %mm0
	movd   %mm0, 72(%edx)

	movd   92(%ecx), %mm0
	pfsub  88(%ecx), %mm0
	pfmul 120(%ebx), %mm0
	movd   %mm0, 92(%edx)
	pfadd  92(%ecx), %mm0
	pfadd  88(%ecx), %mm0
	movq   %mm0, %mm1
	
	pfadd  80(%ecx), %mm0
	pfadd  84(%ecx), %mm0
	movd   %mm0, 80(%edx)

	movd   80(%ecx), %mm0
	pfsub  84(%ecx), %mm0
	pfmul 120(%ebx), %mm0
	pfadd  %mm0, %mm1
	pfadd  92(%edx), %mm0
	movd   %mm0, 84(%edx)
	movd   %mm1, 88(%edx)

	movd   96(%ecx), %mm0
	pfadd 100(%ecx), %mm0
	movd   %mm0, 96(%edx)

	movd   96(%ecx), %mm0
	pfsub 100(%ecx), %mm0
	pfmul 120(%ebx), %mm0
	movd  %mm0, 100(%edx)

	movd  108(%ecx), %mm0
	pfsub 104(%ecx), %mm0
	pfmul 120(%ebx), %mm0
	movd  %mm0, 108(%edx)
	pfadd 104(%ecx), %mm0
	pfadd 108(%ecx), %mm0
	movd  %mm0, 104(%edx)

	movd  124(%ecx), %mm0
	pfsub 120(%ecx), %mm0
	pfmul 120(%ebx), %mm0
	movd  %mm0, 124(%edx)
	pfadd 120(%ecx), %mm0
	pfadd 124(%ecx), %mm0
	movq  %mm0, %mm1

	pfadd 112(%ecx), %mm0
	pfadd 116(%ecx), %mm0
	movd  %mm0, 112(%edx)

	movd  112(%ecx), %mm0
	pfsub 116(%ecx), %mm0
	pfmul 120(%ebx), %mm0
	pfadd %mm0,%mm1
	pfadd 124(%edx), %mm0
	movd  %mm0, 116(%edx)
	movd  %mm1, 120(%edx)

	jnz .L01
	
/* Phase 7*/
/* Code below is coded in scalar mode. Should be optimized */

	movd      (%ecx), %mm0
	pfadd    4(%ecx), %mm0
	movd     %mm0, 1024(%esi)

	movd      (%ecx), %mm0
	pfsub    4(%ecx), %mm0
	pfmul  120(%ebx), %mm0
	movd      %mm0, (%esi)
	movd      %mm0, (%edi)

	movd   12(%ecx), %mm0
	pfsub   8(%ecx), %mm0
	pfmul 120(%ebx), %mm0
	movd    %mm0, 512(%edi)
	pfadd   12(%ecx), %mm0
	pfadd   8(%ecx), %mm0
	movd    %mm0, 512(%esi)

	movd   16(%ecx), %mm0
	pfsub  20(%ecx), %mm0
	pfmul 120(%ebx), %mm0
	movq	%mm0, %mm3

	movd   28(%ecx), %mm0
	pfsub  24(%ecx), %mm0
	pfmul 120(%ebx), %mm0
	movd    %mm0, 768(%edi)
	movq	%mm0, %mm2
	
	pfadd  24(%ecx), %mm0
	pfadd  28(%ecx), %mm0
	movq	%mm0, %mm1

	pfadd  16(%ecx), %mm0
	pfadd  20(%ecx), %mm0
	movd   %mm0, 768(%esi)
	pfadd  %mm3, %mm1
	movd   %mm1, 256(%esi)
	pfadd  %mm3, %mm2
	movd   %mm2, 256(%edi)
	
/* Phase 8*/

	movq   32(%edx), %mm0
	movq   48(%edx), %mm1
	pfadd  48(%edx), %mm0
	pfadd  40(%edx), %mm1
	movd   %mm0, 896(%esi)
	movd   %mm1, 640(%esi)
	psrlq  $32, %mm0
	psrlq  $32, %mm1
	movd   %mm0, 128(%edi)
	movd   %mm1, 384(%edi)

	movd   40(%edx), %mm0
	pfadd  56(%edx), %mm0
	movd   %mm0, 384(%esi)

	movd   56(%edx), %mm0
	pfadd  36(%edx), %mm0
	movd   %mm0, 128(%esi)

	movd   60(%edx), %mm0
	movd   %mm0, 896(%edi)
	pfadd  44(%edx), %mm0
	movd   %mm0, 640(%edi)

	movq   96(%edx), %mm0
	movq   112(%edx), %mm2
	movq   104(%edx), %mm4
	pfadd  112(%edx), %mm0
	pfadd  104(%edx), %mm2
	pfadd  120(%edx), %mm4
	movq   %mm0, %mm1
	movq   %mm2, %mm3
	movq   %mm4, %mm5
	pfadd  64(%edx), %mm0
	pfadd  80(%edx), %mm2
	pfadd  72(%edx), %mm4
	movd   %mm0, 960(%esi)
	movd   %mm2, 704(%esi)
	movd   %mm4, 448(%esi)
	psrlq  $32, %mm0
	psrlq  $32, %mm2
	psrlq  $32, %mm4
	movd   %mm0, 64(%edi)
	movd   %mm2, 320(%edi)
	movd   %mm4, 576(%edi)
	pfadd  80(%edx), %mm1
	pfadd  72(%edx), %mm3
	pfadd  88(%edx), %mm5
	movd   %mm1, 832(%esi)
	movd   %mm3, 576(%esi)
	movd   %mm5, 320(%esi)
	psrlq  $32, %mm1
	psrlq  $32, %mm3
	psrlq  $32, %mm5
	movd   %mm1, 192(%edi)
	movd   %mm3, 448(%edi)
	movd   %mm5, 704(%edi)

	movd   120(%edx), %mm0
	pfadd  100(%edx), %mm0
	movq   %mm0, %mm1
	pfadd  88(%edx), %mm0
	movd   %mm0, 192(%esi)
	pfadd  68(%edx), %mm1
	movd   %mm1, 64(%esi)

	movd  124(%edx), %mm0
	movd  %mm0, 960(%edi)
	pfadd  92(%edx), %mm0
	movd  %mm0, 832(%edi)

	jmp	.L_bye
.L01:	
/* Phase 9*/
	movd      (%ecx), %mm0
	pfadd    4(%ecx), %mm0
	pf2id    %mm0, %mm0
	movd	 %mm0, %eax
	movw     %ax, 512(%esi)

	movd      (%ecx), %mm0
	pfsub    4(%ecx), %mm0
	pfmul  120(%ebx), %mm0
	pf2id    %mm0, %mm0
	movd	 %mm0, %eax
	movw     %ax, (%esi)

	movd    12(%ecx), %mm0
	pfsub    8(%ecx), %mm0
	pfmul  120(%ebx), %mm0
	pf2id    %mm0, %mm7
	movd	 %mm7, %eax
	movw     %ax, 256(%edi)
	pfadd   12(%ecx), %mm0
	pfadd    8(%ecx), %mm0
	pf2id    %mm0, %mm0
	movd	 %mm0, %eax
	movw     %ax, 256(%esi)

	movd   16(%ecx), %mm0
	pfsub  20(%ecx), %mm0
	pfmul  120(%ebx), %mm0
	movq   %mm0, %mm3

	movd   28(%ecx), %mm0
	pfsub  24(%ecx), %mm0
	pfmul 120(%ebx), %mm0
	pf2id  %mm0, %mm7
	movd   %mm7, %eax
	movw   %ax, 384(%edi)
	movq   %mm0, %mm2
	
	pfadd  24(%ecx), %mm0
	pfadd  28(%ecx), %mm0
	movq   %mm0, %mm1
	pfadd  16(%ecx), %mm0
	pfadd  20(%ecx), %mm0
	pf2id  %mm0, %mm0
	movd   %mm0, %eax
	movw   %ax, 384(%esi)
	pfadd  %mm3, %mm1
	pf2id  %mm1, %mm1
	movd   %mm1, %eax
	movw   %ax, 128(%esi)
	pfadd  %mm3, %mm2
	pf2id  %mm2, %mm2
	movd   %mm2, %eax
	movw   %ax, 128(%edi)
	
	
/* Phase 10*/

	movq    32(%edx), %mm0
	movq    48(%edx), %mm1
	pfadd   48(%edx), %mm0
	pfadd   40(%edx), %mm1
	pf2id   %mm0, %mm0
	pf2id   %mm1, %mm1
	movd	%mm0, %eax
	movd	%mm1, %ecx
	movw    %ax, 448(%esi)
	movw    %cx, 320(%esi)
	psrlq   $32, %mm0
	psrlq   $32, %mm1
	movd	%mm0, %eax
	movd	%mm1, %ecx
	movw    %ax, 64(%edi)
	movw    %cx, 192(%edi)

	movd   40(%edx), %mm0
	pfadd  56(%edx), %mm0
	pf2id  %mm0, %mm0
	movd   %mm0, %eax
	movw   %ax, 192(%esi)

	movd   56(%edx), %mm0
	pfadd  36(%edx), %mm0
	pf2id  %mm0, %mm0
	movd   %mm0, %eax
	movw   %ax, 64(%esi)

	movd   60(%edx), %mm0
	pf2id  %mm0, %mm7
	movd   %mm7, %eax
	movw   %ax, 448(%edi)
	pfadd  44(%edx), %mm0
	pf2id  %mm0, %mm0
	movd   %mm0, %eax
	movw   %ax, 320(%edi)

	movq   96(%edx), %mm0
	movq  112(%edx), %mm2
	movq  104(%edx), %mm4
	pfadd 112(%edx), %mm0
	pfadd 104(%edx), %mm2
	pfadd 120(%edx), %mm4
	movq  %mm0, %mm1
	movq  %mm2, %mm3
	movq  %mm4, %mm5
	pfadd  64(%edx), %mm0
	pfadd  80(%edx), %mm2
	pfadd  72(%edx), %mm4
	pf2id  %mm0, %mm7
	pf2id  %mm2, %mm6
	pf2id  %mm4, %mm4
	movd   %mm7, %eax
	movd   %mm6, %ecx
	movd   %mm4, %ebx
	movw   %ax, 480(%esi)
	movw   %cx, 352(%esi)
	movw   %bx, 224(%esi)
	psrlq  $32, %mm7
	psrlq  $32, %mm6
	psrlq  $32, %mm4
	movd   %mm7, %eax
	movd   %mm6, %ecx
	movd   %mm4, %ebx
	movw   %ax, 32(%edi)
	movw   %cx, 160(%edi)
	movw   %bx, 288(%edi)
	pfadd  80(%edx), %mm1
	pfadd  72(%edx), %mm3
	pfadd  88(%edx), %mm5
	pf2id  %mm1, %mm1
	pf2id  %mm3, %mm3
	pf2id  %mm5, %mm5
	movd   %mm1, %eax
	movd   %mm3, %ecx
	movd   %mm5, %ebx
	movw   %ax, 416(%esi)
	movw   %cx, 288(%esi)
	movw   %bx, 160(%esi)
	psrlq  $32, %mm1
	psrlq  $32, %mm3
	psrlq  $32, %mm5
	movd   %mm1, %eax
	movd   %mm3, %ecx
	movd   %mm5, %ebx
	movw   %ax, 96(%edi)
	movw   %cx, 224(%edi)
	movw   %bx, 352(%edi)

	movd  120(%edx), %mm0
	pfadd 100(%edx), %mm0
	movq  %mm0, %mm1
	pfadd  88(%edx), %mm0
	pf2id  %mm0, %mm0
	movd   %mm0, %eax
	movw   %ax, 96(%esi)
	pfadd  68(%edx), %mm1
	pf2id  %mm1, %mm1
	movd   %mm1, %eax
	movw   %ax, 32(%esi)

	movq  124(%edx), %mm0
	pf2id  %mm0, %mm1
	movd   %mm1, %eax
	movw   %ax, 480(%edi)
	pfadd  92(%edx), %mm0
	pf2id  %mm0, %mm0
	movd   %mm0, %eax
	movw   %ax, 416(%edi)

	movsw

.L_bye:
	addl $256,%esp
	femms
	popl %edi
	popl %esi
	popl %ebx
	ret
	

