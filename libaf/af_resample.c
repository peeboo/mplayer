/*=============================================================================
//	
//  This software has been released under the terms of the GNU General Public
//  license. See http://www.gnu.org/copyleft/gpl.html for details.
//
//  Copyright 2002 Anders Johansson ajh@atri.curtin.edu.au
//
//=============================================================================
*/

/* This audio filter changes the sample rate. */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <inttypes.h>

#include "af.h"
#include "dsp.h"

/* Below definition selects the length of each poly phase component.
   Valid definitions are L8 and L16, where the number denotes the
   length of the filter. This definition affects the computational
   complexity (see play()), the performance (see filter.h) and the
   memory usage. The filterlenght is choosen to 8 if the machine is
   slow and to 16 if the machine is fast and has MMX.  
*/

#if !defined(HAVE_MMX) // This machine is slow
#define L8 
#else
#define L16
#endif

#include "af_resample.h"

// Filtering types
#define RSMP_LIN   	(0<<0)	// Linear interpolation
#define RSMP_INT   	(1<<0)  // 16 bit integer 
#define RSMP_FLOAT	(2<<0)	// 32 bit floating point
#define RSMP_MASK	(3<<0)

// Defines for sloppy or exact resampling
#define FREQ_SLOPPY 	(0<<2)
#define FREQ_EXACT  	(1<<2)
#define FREQ_MASK	(1<<2)

// Accuracy for linear interpolation
#define STEPACCURACY 32

// local data
typedef struct af_resample_s
{
  void*  	w;	// Current filter weights
  void** 	xq; 	// Circular buffers
  uint32_t	xi; 	// Index for circular buffers
  uint32_t	wi;	// Index for w
  uint32_t	i; 	// Number of new samples to put in x queue 
  uint32_t  	dn;     // Down sampling factor
  uint32_t	up;	// Up sampling factor 
  uint64_t	step;	// Step size for linear interpolation
  uint64_t	pt;	// Pointer remainder for linear interpolation
  int		setup;	// Setup parameters cmdline or through postcreate
} af_resample_t;

// Euclids algorithm for calculating Greatest Common Divisor GCD(a,b)
static inline int gcd(register int a, register int b)
{
  register int r = min(a,b);
  a=max(a,b);
  b=r;

  r=a%b;
  while(r!=0){
    a=b;
    b=r;
    r=a%b;
  }
  return b;
}

// Fast linear interpolation resample with modest audio quality
static int linint(af_data_t* c,af_data_t* l, af_resample_t* s)
{
  uint32_t	len   = 0; 		// Number of input samples
  uint32_t	nch   = l->nch;   	// Words pre transfer
  uint64_t	step  = s->step; 
  int16_t*	in16  = ((int16_t*)c->audio);
  int16_t*	out16 = ((int16_t*)l->audio);
  int32_t*	in32  = ((int32_t*)c->audio);
  int32_t*	out32 = ((int32_t*)l->audio);
  uint64_t 	end   = ((((uint64_t)c->len)/2LL)<<STEPACCURACY);
  uint64_t	pt    = s->pt;
  uint16_t 	tmp;
  
  switch (nch){
  case 1:
    while(pt < end){
      out16[len++]=in16[pt>>STEPACCURACY];    	    
      pt+=step;
    }
    s->pt=pt & ((1LL<<STEPACCURACY)-1);
    break;		
  case 2:
    end/=2;
    while(pt < end){
      out32[len++]=in32[pt>>STEPACCURACY];    	    
      pt+=step;
    }
    len=(len<<1);
    s->pt=pt & ((1LL<<STEPACCURACY)-1);
    break;
  default:	
    end /=nch;
    while(pt < end){
      tmp=nch;
      do {	 
	tmp--;   
	out16[len+tmp]=in16[tmp+(pt>>STEPACCURACY)*nch];    	    
      } while (tmp);
      len+=nch;
      pt+=step;
    }	
    s->pt=pt & ((1LL<<STEPACCURACY)-1);
  }
  return len;
}

/* Determine resampling type and format */
static int set_types(struct af_instance_s* af, af_data_t* data)
{
  af_resample_t* s = af->setup;
  int rv = AF_OK;
  float rd = 0;

  // Make sure this filter isn't redundant 
  if((af->data->rate == data->rate) || (af->data->rate == 0))
    return AF_DETACH;
  /* If sloppy and small resampling difference (2%) */
  rd = abs((float)af->data->rate - (float)data->rate)/(float)data->rate;
  if((((s->setup & FREQ_MASK) == FREQ_SLOPPY) && (rd < 0.02) && 
      (data->format != (AF_FORMAT_FLOAT_NE))) || 
     ((s->setup & RSMP_MASK) == RSMP_LIN)){
    s->setup = (s->setup & ~RSMP_MASK) | RSMP_LIN;
    af->data->format = AF_FORMAT_S16_NE;
    af->data->bps    = 2;
    af_msg(AF_MSG_VERBOSE,"[resample] Using linear interpolation. \n");
  }
  else{
    /* If the input format is float or if float is explicitly selected
       use float, otherwise use int */
    if((data->format == (AF_FORMAT_FLOAT_NE)) || 
       ((s->setup & RSMP_MASK) == RSMP_FLOAT)){
      s->setup = (s->setup & ~RSMP_MASK) | RSMP_FLOAT;
      af->data->format = AF_FORMAT_FLOAT_NE;
      af->data->bps    = 4;
    }
    else{
      s->setup = (s->setup & ~RSMP_MASK) | RSMP_INT;
      af->data->format = AF_FORMAT_S16_NE;
      af->data->bps    = 2;
    }
    af_msg(AF_MSG_VERBOSE,"[resample] Using %s processing and %s frequecy"
	   " conversion.\n",
	   ((s->setup & RSMP_MASK) == RSMP_FLOAT)?"floating point":"integer",
	   ((s->setup & FREQ_MASK) == FREQ_SLOPPY)?"inexact":"exact");
  }

  if(af->data->format != data->format || af->data->bps != data->bps)
    rv = AF_FALSE;
  data->format = af->data->format;
  data->bps = af->data->bps;
  af->data->nch = data->nch;
  return rv;
}

// Initialization and runtime control
static int control(struct af_instance_s* af, int cmd, void* arg)
{
  switch(cmd){
  case AF_CONTROL_REINIT:{
    af_resample_t* s   = (af_resample_t*)af->setup; 
    af_data_t* 	   n   = (af_data_t*)arg; // New configureation
    int            i,d = 0;
    int 	   rv  = AF_OK;

    // Free space for circular bufers
    if(s->xq){
      for(i=1;i<af->data->nch;i++)
	if(s->xq[i])
	  free(s->xq[i]);
      free(s->xq);
    }

    if(AF_DETACH == (rv = set_types(af,n)))
      return AF_DETACH;
    
    // If linear interpolation 
    if((s->setup & RSMP_MASK) == RSMP_LIN){
      s->pt=0LL;
      s->step=((uint64_t)n->rate<<STEPACCURACY)/(uint64_t)af->data->rate+1LL;
      af_msg(AF_MSG_DEBUG0,"[resample] Linear interpolation step: 0x%016X.\n",
	     s->step);
      af->mul.n = af->data->rate;
      af->mul.d = n->rate;
      return rv;
    }

    // Calculate up and down sampling factors
    d=gcd(af->data->rate,n->rate);

    // If sloppy resampling is enabled limit the upsampling factor
    if(((s->setup & FREQ_MASK) == FREQ_SLOPPY) && (af->data->rate/d > 5000)){
      int up=af->data->rate/2;
      int dn=n->rate/2;
      int m=2;
      while(af->data->rate/(d*m) > 5000){
	d=gcd(up,dn); 
	up/=2; dn/=2; m*=2;
      }
      d*=m;
    }

    // Create space for circular bufers
    s->xq = malloc(n->nch*sizeof(void*));
    for(i=0;i<n->nch;i++)
      s->xq[i] = malloc(2*L*af->data->bps);
    s->xi = 0;

    // Check if the the design needs to be redone
    if(s->up != af->data->rate/d || s->dn != n->rate/d){
      float* w;
      float* wt;
      float fc;
      int j;
      s->up = af->data->rate/d;	
      s->dn = n->rate/d;
      
      // Calculate cuttof frequency for filter
      fc = 1/(float)(max(s->up,s->dn));
      // Allocate space for polyphase filter bank and protptype filter
      w = malloc(sizeof(float) * s->up *L);
      if(NULL != s->w)
	free(s->w);
      s->w = malloc(L*s->up*af->data->bps);

      // Design prototype filter type using Kaiser window with beta = 10
      if(NULL == w || NULL == s->w || 
	 -1 == design_fir(s->up*L, w, &fc, LP|KAISER , 10.0)){
	af_msg(AF_MSG_ERROR,"[resample] Unable to design prototype filter.\n");
	return AF_ERROR;
      }
      // Copy data from prototype to polyphase filter
      wt=w;
      for(j=0;j<L;j++){//Columns
	for(i=0;i<s->up;i++){//Rows
	  if((s->setup & RSMP_MASK) == RSMP_INT){
	    float t=(float)s->up*32767.0*(*wt);
	    ((int16_t*)s->w)[i*L+j] = (int16_t)((t>=0.0)?(t+0.5):(t-0.5));
	  }
	  else
	    ((float*)s->w)[i*L+j] = (float)s->up*(*wt);
	  wt++;
	}
      }
      free(w);
      af_msg(AF_MSG_VERBOSE,"[resample] New filter designed up: %i "
	     "down: %i\n", s->up, s->dn);
    }

    // Set multiplier and delay
    af->delay = (double)(1000*L/2)/((double)n->rate);
    af->mul.n = s->up;
    af->mul.d = s->dn;
    return rv;
  }
  case AF_CONTROL_COMMAND_LINE:{
    af_resample_t* s   = (af_resample_t*)af->setup; 
    int rate=0;
    int type=RSMP_INT;
    int sloppy=1;
    sscanf((char*)arg,"%i:%i:%i", &rate, &sloppy, &type);
    s->setup = (sloppy?FREQ_SLOPPY:FREQ_EXACT) | 
      (clamp(type,RSMP_LIN,RSMP_FLOAT));
    return af->control(af,AF_CONTROL_RESAMPLE_RATE | AF_CONTROL_SET, &rate);
  }
  case AF_CONTROL_POST_CREATE:	
    if((((af_cfg_t*)arg)->force & AF_INIT_FORMAT_MASK) == AF_INIT_FLOAT)
      ((af_resample_t*)af->setup)->setup = RSMP_FLOAT;
    return AF_OK;
  case AF_CONTROL_RESAMPLE_RATE | AF_CONTROL_SET: 
    // Reinit must be called after this function has been called
    
    // Sanity check
    if(((int*)arg)[0] < 8000 || ((int*)arg)[0] > 192000){
      af_msg(AF_MSG_ERROR,"[resample] The output sample frequency " 
	     "must be between 8kHz and 192kHz. Current value is %i \n",
	     ((int*)arg)[0]);
      return AF_ERROR;
    }

    af->data->rate=((int*)arg)[0]; 
    af_msg(AF_MSG_VERBOSE,"[resample] Changing sample rate "  
	   "to %iHz\n",af->data->rate);
    return AF_OK;
  }
  return AF_UNKNOWN;
}

// Deallocate memory 
static void uninit(struct af_instance_s* af)
{
  if(af->data)
    free(af->data);
}

// Filter data through filter
static af_data_t* play(struct af_instance_s* af, af_data_t* data)
{
  int 		 len = 0; 	 // Length of output data
  af_data_t*     c   = data;	 // Current working data
  af_data_t*     l   = af->data; // Local data
  af_resample_t* s   = (af_resample_t*)af->setup;

  if(AF_OK != RESIZE_LOCAL_BUFFER(af,data))
    return NULL;

  // Run resampling
  switch(s->setup & RSMP_MASK){
  case(RSMP_INT):
# define FORMAT_I 1
    if(s->up>s->dn){
#     define UP
#     include "af_resample.h"
#     undef UP 
    }
    else{
#     define DN
#     include "af_resample.h"
#     undef DN
    }
    break;
  case(RSMP_FLOAT):
# undef FORMAT_I
# define FORMAT_F 1
    if(s->up>s->dn){
#     define UP
#     include "af_resample.h"
#     undef UP 
    }
    else{
#     define DN
#     include "af_resample.h"
#     undef DN
    }
    break;
  case(RSMP_LIN):
    len = linint(c, l, s);
    break;
  }

  // Set output data
  c->audio = l->audio;
  c->len   = len*l->bps;
  c->rate  = l->rate;
  
  return c;
}

// Allocate memory and set function pointers
static int open(af_instance_t* af){
  af->control=control;
  af->uninit=uninit;
  af->play=play;
  af->mul.n=1;
  af->mul.d=1;
  af->data=calloc(1,sizeof(af_data_t));
  af->setup=calloc(1,sizeof(af_resample_t));
  if(af->data == NULL || af->setup == NULL)
    return AF_ERROR;
  ((af_resample_t*)af->setup)->setup = RSMP_INT | FREQ_SLOPPY;
  return AF_OK;
}

// Description of this plugin
af_info_t af_info_resample = {
  "Sample frequency conversion",
  "resample",
  "Anders",
  "",
  AF_FLAGS_REENTRANT,
  open
};

