#include <stdio.h>
#include <stdlib.h>

#include "afmt.h"
#include "audio_out.h"
#include "audio_out_internal.h"

static ao_info_t info = 
{
	"Null audio output",
	"null",
	"Tobias Diedrich",
	""
};

LIBAO_EXTERN(null)

struct	timeval last_tv;
int	buffer;

static int drain(){
 
    struct timeval now_tv;
    int temp, temp2;

    gettimeofday(&now_tv, 0);
    temp = now_tv.tv_sec - last_tv.tv_sec;
    temp *= ao_data.bps;
    
    temp2 = now_tv.tv_usec - last_tv.tv_usec;
    temp2 /= 1000;
    temp2 *= ao_data.bps;
    temp2 /= 1000;
    temp += temp2;

    buffer-=temp;
    if (buffer<0) buffer=0;

    last_tv = now_tv;
}

// to set/get/query special features/parameters
static int control(int cmd,int arg){
    return -1;
}

// open & setup audio device
// return: 1=success 0=fail
static int init(int rate,int channels,int format,int flags){

    ao_data.buffersize= 65536;
    ao_data.outburst=1024;
    ao_data.channels=channels;
    ao_data.samplerate=rate;
    ao_data.format=format;
    ao_data.bps=channels*rate;
    if (format != AFMT_U8 && format != AFMT_S8)
	ao_data.bps*=2; 
    buffer=0;
    gettimeofday(&last_tv, 0);

    return 1;
}

// close audio device
static void uninit(){

}

// stop playing and empty buffers (for seeking/pause)
static void reset(){
    buffer=0;
}

// stop playing, keep buffers (for pause)
static void audio_pause()
{
    // for now, just call reset();
    reset();
}

// resume playing, after audio_pause()
static void audio_resume()
{
}

// return: how many bytes can be played without blocking
static int get_space(){

    drain();
    return ao_data.buffersize - buffer;
}

// plays 'len' bytes of 'data'
// it should round it down to outburst*n
// return: number of bytes played
static int play(void* data,int len,int flags){

    int maxbursts = (ao_data.buffersize - buffer) / ao_data.outburst;
    int playbursts = len / ao_data.outburst;
    int bursts = playbursts > maxbursts ? maxbursts : playbursts;
    buffer += bursts * ao_data.outburst;
    return bursts * ao_data.outburst;
}

// return: delay in seconds between first and last sample in buffer
static float get_delay(){

    drain();
    return (float) buffer / (float) ao_data.bps;
}






