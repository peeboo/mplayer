/*
   This file is based on:
   $XFree86: xc/programs/Xserver/hw/xfree86/etc/scanpci.c,v 3.34.2.17 1998/11/10 11:55:40 dawes Exp $
   Modified for readability by Nick Kurshev
*/
#include <windows.h>

/* Nothing to do for Win9x. For WinNT I have no solution */

static __inline__ int enable_os_io(void)
{
    return(0);
}

static __inline__ int disable_os_io(void)
{
    return(0);
}
