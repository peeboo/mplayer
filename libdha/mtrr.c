/*
    mtrr.c - Stuff for optimizing memory access
    Copyrights:
    2002	- Linux version by Nick Kurshev
    Licence: GPL
*/

#include "config.h"

#include <stdio.h>
#include <errno.h>
#include "libdha.h"
#include "AsmMacros.h"


#if defined( __i386__ )
int	mtrr_set_type(unsigned base,unsigned size,int type)
{
#ifdef linux
    FILE * mtrr_fd;
    char * stype;
    switch(type)
    {
	case MTRR_TYPE_UNCACHABLE: stype = "uncachable"; break;
	case MTRR_TYPE_WRCOMB:	   stype = "write-combining"; break;
	case MTRR_TYPE_WRTHROUGH:  stype = "write-through"; break;
	case MTRR_TYPE_WRPROT:	   stype = "write-protect"; break;
	case MTRR_TYPE_WRBACK:	   stype = "write-back"; break;
	default:		   return EINVAL;
    }
    mtrr_fd = fopen("/proc/mtrr","wt");
    if(mtrr_fd)
    {
	char sout[256];
	unsigned wr_len;
	sprintf(sout,"base=0x%08X size=0x%08X type=%s\n",base,size,stype);
	wr_len = fprintf(mtrr_fd,sout);
	/*printf("MTRR: %s\n",sout);*/
	fclose(mtrr_fd);
	return wr_len == strlen(sout) ? 0 : EPERM;
    }
    return ENOSYS;
#else
#warning Please port MTRR stuff!!!
    return ENOSYS
#endif
}
#else
int	mtrr_set_type(unsigned base,unsigned size,int type)
{
    return ENOSYS;
}
#endif