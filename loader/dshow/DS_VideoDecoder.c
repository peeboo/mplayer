/********************************************************

	DirectShow Video decoder implementation
	Copyright 2000 Eugene Kuznetsov  (divx@euro.ru)

*********************************************************/

#include "guids.h"
#include "interfaces.h"

#include "DS_VideoDecoder.h"
#include "../wine/winerror.h"

#ifndef NOAVIFILE_HEADERS
#define VFW_E_NOT_RUNNING               0x80040226
#include "fourcc.h"
#include "except.h"
#endif

#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>  // labs

// strcmp((const char*)info.dll,...)  is used instead of  (... == ...)
// so Arpi could use char* pointer in his simplified DS_VideoDecoder class

#define __MODULE__ "DirectShow_VideoDecoder"

#define false 0
#define true 1

int DS_VideoDecoder_GetCapabilities(DS_VideoDecoder *this)
{return this->m_Caps;}
	    
typedef struct _ct ct;

struct _ct {
		unsigned int bits;
		fourcc_t fcc;
		GUID *subtype;
		int cap;
	    };
            
static ct check[] = {
		{16, fccYUY2, &MEDIASUBTYPE_YUY2, CAP_YUY2},
		{12, fccIYUV, &MEDIASUBTYPE_IYUV, CAP_IYUV},
		{16, fccUYVY, &MEDIASUBTYPE_UYVY, CAP_UYVY},
		{12, fccYV12, &MEDIASUBTYPE_YV12, CAP_YV12},
		{16, fccYV12, &MEDIASUBTYPE_YV12, CAP_YV12},
		{16, fccYVYU, &MEDIASUBTYPE_YVYU, CAP_YVYU},
		//{12, fccI420, &MEDIASUBTYPE_I420, CAP_I420},
		{0},
	    };


DS_VideoDecoder * DS_VideoDecoder_Create(CodecInfo * info,  BITMAPINFOHEADER * format, int flip, int maxauto)
{
    DS_VideoDecoder *this;
    HRESULT result;
    ct* c;
                        
    this = malloc(sizeof(DS_VideoDecoder));
    memset( this, 0, sizeof(DS_VideoDecoder));
    
    this->m_sVhdr2 = 0;
    this->m_iLastQuality = -1;
    this->m_iMaxAuto = maxauto;

    //memset(&m_obh, 0, sizeof(m_obh));
    //m_obh.biSize = sizeof(m_obh);
    /*try*/
    {
        unsigned int bihs;
        
	bihs = (format->biSize < (int) sizeof(BITMAPINFOHEADER)) ?
	    sizeof(BITMAPINFOHEADER) : format->biSize;
        bihs = sizeof(VIDEOINFOHEADER) - sizeof(BITMAPINFOHEADER) + bihs;
     
        this->iv.m_bh = (BITMAPINFOHEADER*)malloc(bihs);
        memcpy(this->iv.m_bh, format, bihs);
        this->iv.m_State = STOP;
        //this->iv.m_pFrame = 0;
        this->iv.m_Mode = DIRECT;
        this->iv.m_iDecpos = 0;
        this->iv.m_iPlaypos = -1;
        this->iv.m_fQuality = 0.0f;
        this->iv.m_bCapable16b = true;
                
	this->m_sVhdr = (VIDEOINFOHEADER*)malloc(bihs);
	memset(this->m_sVhdr, 0, bihs);
	memcpy(&this->m_sVhdr->bmiHeader, this->iv.m_bh, this->iv.m_bh->biSize);
	this->m_sVhdr->rcSource.left = this->m_sVhdr->rcSource.top = 0;
	this->m_sVhdr->rcSource.right = this->m_sVhdr->bmiHeader.biWidth;
	this->m_sVhdr->rcSource.bottom = this->m_sVhdr->bmiHeader.biHeight;
	//this->m_sVhdr->rcSource.right = 0;
	//this->m_sVhdr->rcSource.bottom = 0;
	this->m_sVhdr->rcTarget = this->m_sVhdr->rcSource;

	this->m_sOurType.majortype = MEDIATYPE_Video;
	this->m_sOurType.subtype = MEDIATYPE_Video;
        this->m_sOurType.subtype.f1 = this->m_sVhdr->bmiHeader.biCompression;
	this->m_sOurType.formattype = FORMAT_VideoInfo;
        this->m_sOurType.bFixedSizeSamples = false;
	this->m_sOurType.bTemporalCompression = true;
	this->m_sOurType.pUnk = 0;
        this->m_sOurType.cbFormat = bihs;
        this->m_sOurType.pbFormat = (char*)this->m_sVhdr;

	this->m_sVhdr2 = (VIDEOINFOHEADER*)(malloc(sizeof(VIDEOINFOHEADER)+12));
	memcpy(this->m_sVhdr2, this->m_sVhdr, sizeof(VIDEOINFOHEADER));
        memset((char*)this->m_sVhdr2 + sizeof(VIDEOINFOHEADER), 0, 12);
	this->m_sVhdr2->bmiHeader.biCompression = 0;
	this->m_sVhdr2->bmiHeader.biBitCount = 24;

	memset(&this->m_sDestType, 0, sizeof(this->m_sDestType));
	this->m_sDestType.majortype = MEDIATYPE_Video;
	this->m_sDestType.subtype = MEDIASUBTYPE_RGB24;
	this->m_sDestType.formattype = FORMAT_VideoInfo;
	this->m_sDestType.bFixedSizeSamples = true;
	this->m_sDestType.bTemporalCompression = false;
	this->m_sDestType.lSampleSize = labs(this->m_sVhdr2->bmiHeader.biWidth*this->m_sVhdr2->bmiHeader.biHeight
				       * ((this->m_sVhdr2->bmiHeader.biBitCount + 7) / 8));
	this->m_sVhdr2->bmiHeader.biSizeImage = this->m_sDestType.lSampleSize;
	this->m_sDestType.pUnk = 0;
	this->m_sDestType.cbFormat = sizeof(VIDEOINFOHEADER);
	this->m_sDestType.pbFormat = (char*)this->m_sVhdr2;
        
        memset(&this->iv.m_obh, 0, sizeof(this->iv.m_obh));
	memcpy(&this->iv.m_obh, this->iv.m_bh, sizeof(this->iv.m_obh) < (unsigned) this->iv.m_bh->biSize
	       ? sizeof(this->iv.m_obh) : (unsigned) this->iv.m_bh->biSize);
	this->iv.m_obh.biBitCount=24;
        this->iv.m_obh.biSize = sizeof(BITMAPINFOHEADER);
        this->iv.m_obh.biCompression = 0;	//BI_RGB
        //this->iv.m_obh.biHeight = labs(this->iv.m_obh.biHeight);
        this->iv.m_obh.biSizeImage = labs(this->iv.m_obh.biWidth * this->iv.m_obh.biHeight)
                              * ((this->iv.m_obh.biBitCount + 7) / 8);


	this->m_pDS_Filter = DS_Filter_Create((const char*)info->dll, &info->guid, &this->m_sOurType, &this->m_sDestType);

	if (!flip)
	{
	    this->m_sVhdr2->bmiHeader.biHeight *= -1;
	    this->iv.m_obh.biHeight *= -1;
	    result = this->m_pDS_Filter->m_pOutputPin->vt->QueryAccept(this->m_pDS_Filter->m_pOutputPin, &this->m_sDestType);
	    if (result)
	    {
		printf("Decoder does not support upside-down frames\n");
		this->m_sVhdr2->bmiHeader.biHeight *= -1;
		this->iv.m_obh.biHeight *= -1;
	    }
	}

        memcpy( &this->iv.m_decoder, &this->iv.m_obh, sizeof(this->iv.m_obh) );

	switch (this->iv.m_bh->biCompression)
	{
	case fccDIV3:
	case fccDIV4:
	case fccDIV5:
	case fccDIV6:
	case fccMP42:
	case fccWMV2:
	    //YV12 seems to be broken for DivX :-) codec
//	case fccIV50:
	    //produces incorrect picture
	    //m_Caps = (CAPS) (m_Caps & ~CAP_YV12);
	    //m_Caps = CAP_UYVY;//CAP_YUY2; // | CAP_I420;
	    //m_Caps = CAP_I420;
	    this->m_Caps = (CAP_YUY2 | CAP_UYVY);
	    break;
	default:
              
	    this->m_Caps = CAP_NONE;

	    for (c = check; c->bits; c++)
	    {
		this->m_sVhdr2->bmiHeader.biBitCount = c->bits;
		this->m_sVhdr2->bmiHeader.biCompression = c->fcc;
		this->m_sDestType.subtype = *c->subtype;
		result = this->m_pDS_Filter->m_pOutputPin->vt->QueryAccept(this->m_pDS_Filter->m_pOutputPin, &this->m_sDestType);
		if (!result)
		    this->m_Caps = (this->m_Caps | c->cap);
	    }
	}

	if (this->m_Caps != CAP_NONE)
	    printf("Decoder is capable of YUV output ( flags 0x%x)\n", (int)this->m_Caps);

	this->m_sVhdr2->bmiHeader.biBitCount = 24;
	this->m_sVhdr2->bmiHeader.biCompression = 0;
	this->m_sDestType.subtype = MEDIASUBTYPE_RGB24;

	this->m_iMinBuffers = this->iv.VBUFSIZE;
	this->m_bIsDivX = (strcmp((const char*)info->dll, "divxcvki.ax") == 0
		     || strcmp((const char*)info->dll, "divx_c32.ax") == 0
		     || strcmp((const char*)info->dll, "wmvds32.ax") == 0
		     || strcmp((const char*)info->dll, "wmv8ds32.ax") == 0);
	this->m_bIsDivX4 = (strcmp((const char*)info->dll, "divxdec.ax") == 0);
	if (this->m_bIsDivX)
	    this->iv.VBUFSIZE += 7;
	else if (this->m_bIsDivX4)
	    this->iv.VBUFSIZE += 9;
    }
    /*catch (FatalError& error)
    {
        delete[] m_sVhdr;
	delete[] m_sVhdr2;
        delete m_pDS_Filter;
	throw;
    }*/
    return this;
}

void DS_VideoDecoder_Destroy(DS_VideoDecoder *this)
{
    DS_VideoDecoder_StopInternal(this);
    this->iv.m_State = STOP;
    free(this->m_sVhdr);
    free(this->m_sVhdr2);
    DS_Filter_Destroy(this->m_pDS_Filter);
}

void DS_VideoDecoder_StartInternal(DS_VideoDecoder *this)
{
    ALLOCATOR_PROPERTIES props, props1;
    Debug printf("DS_VideoDecoder_StartInternal\n");
    //cout << "DSSTART" << endl;
    DS_Filter_Start(this->m_pDS_Filter);
    
    props.cBuffers = 1;
    props.cbBuffer = this->m_sDestType.lSampleSize;

    //don't know how to do this correctly
    props.cbAlign = props.cbPrefix = 0;
    this->m_pDS_Filter->m_pAll->vt->SetProperties(this->m_pDS_Filter->m_pAll, &props, &props1);
    this->m_pDS_Filter->m_pAll->vt->Commit(this->m_pDS_Filter->m_pAll);
    
    //this->iv.m_State = START;
}

void DS_VideoDecoder_StopInternal(DS_VideoDecoder *this)
{
    DS_Filter_Stop(this->m_pDS_Filter);
    //??? why was this here ??? m_pOurOutput->SetFramePointer(0);
}

int DS_VideoDecoder_DecodeInternal(DS_VideoDecoder *this, const void* src, int size, int is_keyframe, CImage* pImage)
{
    IMediaSample* sample = 0;
    char* ptr;
    int result;
    
    Debug printf("DS_VideoDecoder_DecodeInternal(%p,%p,%d,%d,%p)\n",this,src,size,is_keyframe,pImage->ptr);
            
    this->m_pDS_Filter->m_pAll->vt->GetBuffer(this->m_pDS_Filter->m_pAll, &sample, 0, 0, 0);
    
    if (!sample)
    {
	Debug printf("ERROR: null sample\n");
	return -1;
    }
    
    //cout << "DECODE " << (void*) pImage << "   d: " << (void*) pImage->Data() << endl;
    if (pImage)
    {
	if (!(pImage->ptr))
	{
	    Debug printf("no m_outFrame??\n");
	}
	else
	    COutputPin_SetPointer2(this->m_pDS_Filter->m_pOurOutput,(char*)pImage->ptr);
    }


    sample->vt->GetPointer(sample, (BYTE **)&ptr);
    memcpy(ptr, src, size);
    sample->vt->SetActualDataLength(sample, size);
    sample->vt->SetSyncPoint(sample, is_keyframe);
    sample->vt->SetPreroll(sample, pImage ? 0 : 1);
    // sample->vt->SetMediaType(sample, &m_sOurType);

    // FIXME: - crashing with YV12 at this place decoder will crash
    //          while doing this call
    // %FS register was not setup for calling into win32 dll. Are all
    // crashes inside ...->Receive() fixed now?
    //
    // nope - but this is surely helpfull - I'll try some more experiments
    Setup_FS_Segment();
#if 0
    if (!this->m_pDS_Filter || !this->m_pDS_Filter->m_pImp
	|| !this->m_pDS_Filter->m_pImp->vt
	|| !this->m_pDS_Filter->m_pImp->vt->Receive)
	printf("DecodeInternal ERROR???\n");
#endif
    result = this->m_pDS_Filter->m_pImp->vt->Receive(this->m_pDS_Filter->m_pImp, sample);
    if (result)
    {
	Debug printf("DS_VideoDecoder::DecodeInternal() error putting data into input pin %x\n", result);
    }

    sample->vt->Release((IUnknown*)sample);

#if 0
    if (this->m_bIsDivX)
    {
	int q;
	IHidden* hidden=(IHidden*)((int)this->m_pDS_Filter->m_pFilter + 0xb8);
	// always check for actual value
	// this seems to be the only way to know the actual value
	hidden->vt->GetSmth2(hidden, &this->m_iLastQuality);
	if (this->m_iLastQuality > 9)
	    this->m_iLastQuality -= 10;

	if (this->m_iLastQuality < 0)
	    this->m_iLastQuality = 0;
	else if (this->m_iLastQuality > this->m_iMaxAuto)
	    this->m_iLastQuality = this->m_iMaxAuto;

	//cout << " Qual: " << this->m_iLastQuality << endl;
	this->iv.m_fQuality = this->m_iLastQuality / 4.0;
    }
    else if (this->m_bIsDivX4)
    {

        // maybe access methods directly to safe some cpu cycles...
        DS_VideoDecoder_GetValue(this, "Postprocessing", this->m_iLastQuality);
	if (this->m_iLastQuality < 0)
	    this->m_iLastQuality = 0;
	else if (this->m_iLastQuality > this->m_iMaxAuto)
	    this->m_iLastQuality = this->m_iMaxAuto;

	//cout << " Qual: " << m_iLastQuality << endl;
	this->iv.m_fQuality = this->m_iLastQuality / 6.0;
    }

    if (this->iv.m_Mode == -1 ) // ???BUFFERED_QUALITY_AUTO)
    {
	// adjust Quality - depends on how many cached frames we have
	int buffered = this->iv.m_iDecpos - this->iv.m_iPlaypos;

	if (this->m_bIsDivX || this->m_bIsDivX4)
	{
	    int to = buffered - this->m_iMinBuffers;
	    if (to < 0)
		to = 0;
	    if (to != this->m_iLastQuality)
	    {
		if (to > this->m_iMaxAuto)
		    to = this->m_iMaxAuto;
		if (this->m_iLastQuality != to)
		{
		    if (this->m_bIsDivX)
		    {
			IHidden* hidden=(IHidden*)((int)this->m_pDS_Filter->m_pFilter + 0xb8);
			hidden->vt->SetSmth(hidden, to, 0);
		    }
                    else
			DS_VideoDecoder_SetValue(this, "Postprocessing", to);
#ifndef QUIET
		    //printf("Switching quality %d -> %d  b:%d\n",m_iLastQuality, to, buffered);
#endif
		}
	    }
	}
    }
#endif

    return 0;
}

/*
 * bits == 0   - leave unchanged
 */
//int SetDestFmt(DS_VideoDecoder * this, int bits = 24, fourcc_t csp = 0);
int DS_VideoDecoder_SetDestFmt(DS_VideoDecoder *this, int bits, fourcc_t csp)
{
    HRESULT result;
    int should_test=1;
    int stoped = 0;   
    
    Debug printf("DS_VideoDecoder_SetDestFmt (%p, %d, %d)\n",this,bits,(int)csp);
        
       /* if (!CImage::Supported(csp, bits))
	return -1;
*/
    // BitmapInfo temp = m_obh;
    
    if (bits != 0)
    {
	int ok = true;

	switch (bits)
        {
	case 15:
	    this->m_sDestType.subtype = MEDIASUBTYPE_RGB555;
    	    break;
	case 16:
	    this->m_sDestType.subtype = MEDIASUBTYPE_RGB565;
	    break;
	case 24:
	    this->m_sDestType.subtype = MEDIASUBTYPE_RGB24;
	    break;
	case 32:
	    this->m_sDestType.subtype = MEDIASUBTYPE_RGB32;
	    break;
	default:
            ok = false;
	    break;
	}

        if (ok) {
	    this->iv.m_obh.biBitCount=bits;
            if( bits == 15 || bits == 16 ) {
	      this->iv.m_obh.biSize=sizeof(BITMAPINFOHEADER)+12;
	      this->iv.m_obh.biCompression=3;//BI_BITFIELDS
	      this->iv.m_obh.biSizeImage=abs((int)(2*this->iv.m_obh.biWidth*this->iv.m_obh.biHeight));
	    }
            
            if( bits == 16 ) {
	      this->iv.m_obh.colors[0]=0xF800;
	      this->iv.m_obh.colors[1]=0x07E0;
	      this->iv.m_obh.colors[2]=0x001F;
            } else if ( bits == 15 ) {
	      this->iv.m_obh.colors[0]=0x7C00;
	      this->iv.m_obh.colors[1]=0x03E0;
	      this->iv.m_obh.colors[2]=0x001F;
            } else {
	      this->iv.m_obh.biSize = sizeof(BITMAPINFOHEADER);
	      this->iv.m_obh.biCompression = 0;	//BI_RGB
	      //this->iv.m_obh.biHeight = labs(this->iv.m_obh.biHeight);
	      this->iv.m_obh.biSizeImage = labs(this->iv.m_obh.biWidth * this->iv.m_obh.biHeight)
                              * ((this->iv.m_obh.biBitCount + 7) / 8);
            }
        }
	//.biSizeImage=abs(temp.biWidth*temp.biHeight*((temp.biBitCount+7)/8));
    }

    if (csp != 0)
    {
        int ok = true;
	switch (csp)
	{
	case fccYUY2:
	    this->m_sDestType.subtype = MEDIASUBTYPE_YUY2;
	    break;
	case fccYV12:
	    this->m_sDestType.subtype = MEDIASUBTYPE_YV12;
	    break;
	case fccIYUV:
	    this->m_sDestType.subtype = MEDIASUBTYPE_IYUV;
	    break;
	case fccUYVY:
	    this->m_sDestType.subtype = MEDIASUBTYPE_UYVY;
	    break;
	case fccYVYU:
	    this->m_sDestType.subtype = MEDIASUBTYPE_YVYU;
	    break;
	default:
	    ok = false;
            break;
	}

        if (ok) {
          int bits=0;
	  switch(csp){
	  case fccYUV:
	    bits=24;break;
	  case fccYUY2:
	  case fccUYVY:
	  case fccYVYU:
	    bits=16;break;
	  case fccYV12:
	  case fccIYUV:
	  case fccI420:
	    bits=12;break;
	  }
	  if (csp != 0 && csp != 3 && this->iv.m_obh.biHeight > 0)
    	    this->iv.m_obh.biHeight *= -1; // YUV formats uses should have height < 0
	  this->iv.m_obh.biSize = sizeof(BITMAPINFOHEADER);
	  this->iv.m_obh.biCompression=csp;
	  this->iv.m_obh.biBitCount=bits;
	  this->iv.m_obh.biSizeImage=labs(this->iv.m_obh.biBitCount*
             this->iv.m_obh.biWidth*this->iv.m_obh.biHeight)>>3;
        }
    }
    this->m_sDestType.lSampleSize = this->iv.m_obh.biSizeImage;
    memcpy(&(this->m_sVhdr2->bmiHeader), &this->iv.m_obh, sizeof(this->iv.m_obh));
    this->m_sVhdr2->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    if (this->m_sVhdr2->bmiHeader.biCompression == 3)
        this->m_sDestType.cbFormat = sizeof(VIDEOINFOHEADER) + 12;
    else
        this->m_sDestType.cbFormat = sizeof(VIDEOINFOHEADER);


    switch(csp)
    {
    case fccYUY2:
	if(!(this->m_Caps & CAP_YUY2))
	    should_test=false;
	break;
    case fccYV12:
	if(!(this->m_Caps & CAP_YV12))
	    should_test=false;
	break;
    case fccIYUV:
	if(!(this->m_Caps & CAP_IYUV))
	    should_test=false;
	break;
    case fccUYVY:
	if(!(this->m_Caps & CAP_UYVY))
	    should_test=false;
	break;
    case fccYVYU:
	if(!(this->m_Caps & CAP_YVYU))
	    should_test=false;
	break;
    }
    if(should_test)
	result = this->m_pDS_Filter->m_pOutputPin->vt->QueryAccept(this->m_pDS_Filter->m_pOutputPin, &this->m_sDestType);
    else
	result = -1;

    if (result != 0)
    {
	if (csp)
	    printf("Warning: unsupported color space\n");
	else
	    printf("Warning: unsupported bit depth\n");

	this->m_sDestType.lSampleSize = this->iv.m_decoder.biSizeImage;
	memcpy(&(this->m_sVhdr2->bmiHeader), &this->iv.m_decoder, sizeof(this->iv.m_decoder));
	this->m_sVhdr2->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	if (this->m_sVhdr2->bmiHeader.biCompression == 3)
    	    this->m_sDestType.cbFormat = sizeof(VIDEOINFOHEADER) + 12;
	else
    	    this->m_sDestType.cbFormat = sizeof(VIDEOINFOHEADER);

	return -1;
    }

    memcpy( &this->iv.m_decoder, &this->iv.m_obh, sizeof(this->iv.m_obh));

//    m_obh=temp;
//    if(csp)
//	m_obh.biBitCount=BitmapInfo::BitCount(csp);
    this->iv.m_bh->biBitCount = bits;

    //DS_VideoDecoder_Restart(this);

    if (this->iv.m_State == START)
    {
	DS_VideoDecoder_StopInternal(this);
        this->iv.m_State = STOP;
        stoped = true;
    }

    this->m_pDS_Filter->m_pInputPin->vt->Disconnect(this->m_pDS_Filter->m_pInputPin);
    this->m_pDS_Filter->m_pOutputPin->vt->Disconnect(this->m_pDS_Filter->m_pOutputPin);
    COutputPin_SetNewFormat(this->m_pDS_Filter->m_pOurOutput,&this->m_sDestType);
    result = this->m_pDS_Filter->m_pInputPin->vt->ReceiveConnection(this->m_pDS_Filter->m_pInputPin,
							      this->m_pDS_Filter->m_pOurInput,
							      &this->m_sOurType);
    if (result)
    {
	printf("Error reconnecting input pin 0x%x\n", (int)result);
	return -1;
    }
    result = this->m_pDS_Filter->m_pOutputPin->vt->ReceiveConnection(this->m_pDS_Filter->m_pOutputPin,
							       (IPin *)this->m_pDS_Filter->m_pOurOutput,
							       &this->m_sDestType);
    if (result)
    {
	printf("Error reconnecting output pin 0x%x\n", (int)result);
	return -1;
    }

    if (stoped)
    {
	DS_VideoDecoder_StartInternal(this);
        this->iv.m_State = START; 
    }

    return 0;
}


int DS_VideoDecoder_SetDirection(DS_VideoDecoder *this, int d)
{
    this->iv.m_obh.biHeight = (d) ? this->iv.m_bh->biHeight : -this->iv.m_bh->biHeight;
    this->m_sVhdr2->bmiHeader.biHeight = this->iv.m_obh.biHeight;
    return 0;
}

HRESULT DS_VideoDecoder_GetValue(DS_VideoDecoder *this, const char* name, int* value)
{
/*
    if (m_bIsDivX4)
    {
	IDivxFilterInterface* pIDivx;
	if (m_pDS_Filter->m_pFilter->vt->QueryInterface((IUnknown*)m_pDS_Filter->m_pFilter, &IID_IDivxFilterInterface, (void**)&pIDivx))
	{
	    Debug printf("No such interface\n");
	    return -1;
	}
	if (strcmp(name, "Postprocessing") == 0)
	{
	    pIDivx->vt->get_PPLevel(pIDivx, &value);
	    value /= 10;
	}
	else if (strcmp(name, "Brightness") == 0)
	    pIDivx->vt->get_Brightness(pIDivx, &value);
	else if (strcmp(name, "Contrast") == 0)
	    pIDivx->vt->get_Contrast(pIDivx, &value);
	else if (strcmp(name, "Saturation") == 0)
	    pIDivx->vt->get_Saturation(pIDivx, &value);
	else if (strcmp(name, "MaxAuto") == 0)
	    value = m_iMaxAuto;
	pIDivx->vt->Release((IUnknown*)pIDivx);
	return 0;
    }
    else if (m_bIsDivX)
    {
	if (m_State != START)
	    return VFW_E_NOT_RUNNING;
// brightness 87
// contrast 74
// hue 23
// saturation 20
// post process mode 0
// get1 0x01
// get2 10
// get3=set2 86
// get4=set3 73
// get5=set4 19
// get6=set5 23
	IHidden* hidden=(IHidden*)((int)m_pDS_Filter->m_pFilter+0xb8);
	if (strcmp(name, "Quality") == 0)
	{
#warning NOT SURE
	    int r = hidden->vt->GetSmth2(hidden, &value);
	    if (value >= 10)
		value -= 10;
	    return 0;
	}
	if (strcmp(name, "Brightness") == 0)
	    return hidden->vt->GetSmth3(hidden, &value);
	if (strcmp(name, "Contrast") == 0)
	    return hidden->vt->GetSmth4(hidden, &value);
	if (strcmp(name, "Hue") == 0)
	    return hidden->vt->GetSmth6(hidden, &value);
	if (strcmp(name, "Saturation") == 0)
	    return hidden->vt->GetSmth5(hidden, &value);
	if (strcmp(name, "MaxAuto") == 0)
	{
	    value = m_iMaxAuto;
            return 0;
	}
    }
    else if (strcmp((const char*)record.dll, "ir50_32.dll") == 0)
    {
	IHidden2* hidden = 0;
	if (m_pDS_Filter->m_pFilter->vt->QueryInterface((IUnknown*)m_pDS_Filter->m_pFilter, &IID_Iv50Hidden, (void**)&hidden))
	{
	    Debug printf("No such interface\n");
	    return -1;
	}
#warning FIXME
	int recordpar[30];
	recordpar[0]=0x7c;
	recordpar[1]=fccIV50;
	recordpar[2]=0x10005;
	recordpar[3]=2;
	recordpar[4]=1;
	recordpar[5]=0x80000000;

	if (strcmp(name, "Brightness") == 0)
	    recordpar[5]|=0x20;
	else if (strcmp(name, "Saturation") == 0)
	    recordpar[5]|=0x40;
	else if (strcmp(name, "Contrast") == 0)
	    recordpar[5]|=0x80;
	if (!recordpar[5])
	{
	    hidden->vt->Release((IUnknown*)hidden);
	    return -1;
	}
	if (hidden->vt->DecodeSet(hidden, recordpar))
	    return -1;

	if (strcmp(name, "Brightness") == 0)
	    value = recordpar[18];
	else if (strcmp(name, "Saturation") == 0)
	    value = recordpar[19];
	else if (strcmp(name, "Contrast") == 0)
	    value = recordpar[20];

	hidden->vt->Release((IUnknown*)hidden);
    }
*/
    return 0;
}

HRESULT DS_VideoDecoder_SetValue(DS_VideoDecoder *this, const char* name, int value)
{
/*
    if (m_bIsDivX4)
    {
	IDivxFilterInterface* pIDivx;
	if (m_pDS_Filter->m_pFilter->vt->QueryInterface((IUnknown*)m_pDS_Filter->m_pFilter, &IID_IDivxFilterInterface, (void**)&pIDivx))
	{
	    Debug printf("No such interface\n");
	    return -1;
	}
	if (strcmp(name, "Postprocessing") == 0)
	    pIDivx->vt->put_PPLevel(pIDivx, value * 10);
	else if (strcmp(name, "Brightness") == 0)
	    pIDivx->vt->put_Brightness(pIDivx, value);
	else if (strcmp(name, "Contrast") == 0)
	    pIDivx->vt->put_Contrast(pIDivx, value);
	else if (strcmp(name, "Saturation") == 0)
	    pIDivx->vt->put_Saturation(pIDivx, value);
	else if (strcmp(name, "MaxAuto") == 0)
            m_iMaxAuto = value;
	pIDivx->vt->Release((IUnknown*)pIDivx);
	//printf("Set %s  %d\n", name, value);
	return 0;
    }
    else if (m_bIsDivX)
    {
	if (m_State != START)
	    return VFW_E_NOT_RUNNING;

	//cout << "set value " << name << "  " << value << endl;
// brightness 87
// contrast 74
// hue 23
// saturation 20
// post process mode 0
// get1 0x01
// get2 10
// get3=set2 86
// get4=set3 73
// get5=set4 19
	// get6=set5 23
    	IHidden* hidden = (IHidden*)((int)m_pDS_Filter->m_pFilter + 0xb8);
	if (strcmp(name, "Quality") == 0)
	{
            m_iLastQuality = value;
	    return hidden->vt->SetSmth(hidden, value, 0);
	}
	if (strcmp(name, "Brightness") == 0)
	    return hidden->vt->SetSmth2(hidden, value, 0);
	if (strcmp(name, "Contrast") == 0)
	    return hidden->vt->SetSmth3(hidden, value, 0);
	if (strcmp(name, "Saturation") == 0)
	    return hidden->vt->SetSmth4(hidden, value, 0);
	if (strcmp(name, "Hue") == 0)
	    return hidden->vt->SetSmth5(hidden, value, 0);
	if (strcmp(name, "MaxAuto") == 0)
	{
            m_iMaxAuto = value;
	    return 0;
	}
    }
    else if (strcmp((const char*)record.dll, "ir50_32.dll") == 0)
    {
	IHidden2* hidden = 0;
	if (m_pDS_Filter->m_pFilter->vt->QueryInterface((IUnknown*)m_pDS_Filter->m_pFilter, &IID_Iv50Hidden, (void**)&hidden))
	{
	    Debug printf("No such interface\n");
	    return -1;
	}
	int recordpar[30];
	recordpar[0]=0x7c;
	recordpar[1]=fccIV50;
	recordpar[2]=0x10005;
	recordpar[3]=2;
	recordpar[4]=1;
	recordpar[5]=0x80000000;
	if (strcmp(name, "Brightness") == 0)
	{
	    recordpar[5]|=0x20;
	    recordpar[18]=value;
	}
	else if (strcmp(name, "Saturation") == 0)
	{
	    recordpar[5]|=0x40;
	    recordpar[19]=value;
	}
	else if (strcmp(name, "Contrast") == 0)
	{
	    recordpar[5]|=0x80;
	    recordpar[20]=value;
	}
	if(!recordpar[5])
	{
	    hidden->vt->Release((IUnknown*)hidden);
    	    return -1;
	}
	HRESULT result = hidden->vt->DecodeSet(hidden, recordpar);
	hidden->vt->Release((IUnknown*)hidden);

	return result;
    }
*/
    return 0;
}
/*
vim: tabstop=8
*/
