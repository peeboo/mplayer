
#ifndef __MYMPLAYERHANDLER
#define __MYMPLAYERHANDLER

extern int             mplSubRender;
extern int             mplMainRender;
extern int             mplGeneralTimer;
extern int             mplSkinChanged;

extern unsigned char * mplDrawBuffer;
extern unsigned char * mplMenuDrawBuffer;
extern int             mainVisible;

extern int             mplMainAutoPlay;

extern void mplInit( int argc,char* argv[], char *envp[] );
extern void mplMsgHandle( int msg,float param );

#endif
