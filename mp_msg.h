
extern int verbose; // defined in mplayer.c

// verbosity elevel:

// stuff from level MSGL_FATAL-MSGL_HINT should be translated.

#define MSGL_FATAL 0  // will exit/abort
#define MSGL_ERR 1    // continues
#define MSGL_WARN 2   // only warning
#define MSGL_HINT 3   // short help message
#define MSGL_INFO 4   // -quiet
#define MSGL_STATUS 5 // v=0
#define MSGL_V 6      // v=1
#define MSGL_DBG2 7   // v=2
#define MSGL_DBG3 8   // v=3
#define MSGL_DBG4 9   // v=4

// code/module:

#define MSGT_GLOBAL 0        // common player stuff errors
#define MSGT_CPLAYER 1       // console player (mplayer.c)
#define MSGT_GPLAYER 2       // gui player

#define MSGT_VO 3	       // libvo
#define MSGT_AO 4	       // libao

#define MSGT_DEMUXER 5    // demuxer.c (general stuff)
#define MSGT_DS 6         // demux stream (add/read packet etc)
#define MSGT_DEMUX 7      // fileformat-specific stuff (demux_*.c)
#define MSGT_HEADER 8     // fileformat-specific header (*header.c)

#define MSGT_AVSYNC 9     // mplayer.c timer stuff
#define MSGT_AUTOQ 10     // mplayer.c auto-quality stuff

#define MSGT_CFGPARSER 11 // cfgparser.c

#define MSGT_DECAUDIO 12  // av decoder
#define MSGT_DECVIDEO 13

#define MSGT_SEEK 14	// seeking code
#define MSGT_WIN32 15	// win32 dll stuff
#define MSGT_OPEN 16	// open.c (stream opening)
#define MSGT_DVD 17	// open.c (DVD init/read/seek)

#define MSGT_PARSEES 18	// parse_es.c (mpeg stream parser)
#define MSGT_LIRC 19	// lirc_mp.c

#define MSGT_STREAM 20  // stream.c

#define MSGT_MAX 64

void mp_msg_init(int verbose);
void mp_msg_c( int x, const char *format, ... );


#ifdef __GNUC__
#define mp_msg(mod,lev, args... ) mp_msg_c((mod<<8)|lev, ## args )

#ifdef MP_DEBUG
#define mp_dbg(mod,lev, args... ) mp_msg_c((mod<<8)|lev, ## args )
#else
// these messages are only usefull for developers, disable them
#define mp_dbg(mod,lev, args... ) 
#endif
#else // not GNU C
#define mp_msg(mod,lev, ... ) mp_msg_c((mod<<8)|lev, __VA_ARGS__)

#ifdef MP_DEBUG
#define mp_dbg(mod,lev, ... ) mp_msg_c((mod<<8)|lev, __VA_ARGS__)
#else
// these messages are only usefull for developers, disable them
#define mp_dbg(mod,lev, ... ) 
#endif
#endif
