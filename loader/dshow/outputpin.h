#ifndef DS_OUTPUTPIN_H
#define DS_OUTPUTPIN_H

/* "output pin" - the one that connects to output of filter. */

#include "allocator.h"

typedef struct _COutputPin COutputPin;

typedef struct _COutputMemPin COutputMemPin;
struct _COutputMemPin
{
    IMemInputPin_vt* vt;
    char** frame_pointer;
    long* frame_size_pointer;
    MemAllocator* pAllocator;
    COutputPin* parent;
};

struct _COutputPin
{
    IPin_vt* vt;
    COutputMemPin* mempin;
    int refcount;
    AM_MEDIA_TYPE type;
    IPin* remote;
    void ( *SetFramePointer )(COutputPin*, char** z);
    void ( *SetPointer2 )(COutputPin*, char* p);
    void ( *SetFrameSizePointer )(COutputPin*, long* z);
    void ( *SetNewFormat )(COutputPin*, const AM_MEDIA_TYPE* a);
};

COutputPin* COutputPinCreate(const AM_MEDIA_TYPE* vhdr);

#endif /* DS_OUTPUTPIN_H */
