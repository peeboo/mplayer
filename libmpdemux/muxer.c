
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <unistd.h>

#include "config.h"
#include "../version.h"

#include "wine/mmreg.h"
#include "wine/avifmt.h"
#include "wine/vfw.h"

#include "muxer.h"

muxer_t* muxer_new_muxer(int type){
    muxer_t* muxer=malloc(sizeof(muxer_t));
    memset(muxer,0,sizeof(muxer_t));
    switch (type) {
      case MUXER_TYPE_MPEG:
	muxer_init_muxer_mpeg(muxer);
	break;
      case MUXER_TYPE_AVI:
      default:
	muxer_init_muxer_avi(muxer);
    }
    return muxer;
}
