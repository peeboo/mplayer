// Basic types:

typedef char *                          Ptr;
typedef Ptr *                           Handle;
typedef long                            Size;
typedef unsigned char                   Boolean;
typedef unsigned char                   Str31[32];
typedef long                            Fixed;

typedef long OSErr;
typedef int OSType;

typedef long ComponentResult;
typedef unsigned char                   UInt8;
typedef signed char                     SInt8;
typedef unsigned short                  UInt16;
typedef signed short                    SInt16;
typedef unsigned long                   UInt32;
typedef signed long                     SInt32;

#define FOUR_CHAR_CODE(x)       ((unsigned long)(x)) /* otherwise compiler will complain about values with high bit set */

// codec private shit:
typedef void *GlobalsPtr;
typedef void **Globals;

//==================== COMPONENTS ===========================

struct __attribute__((__packed__)) ComponentParameters {
    UInt8                           flags;                      /* call modifiers: sync/async, deferred, immed, etc */
    UInt8                           paramSize;                  /* size in bytes of actual parameters passed to this call */
    short                           what;                       /* routine selector, negative for Component management calls */
    long                            params[1];                  /* actual parameters for the indicated routine */
};
typedef struct ComponentParameters      ComponentParameters;


struct __attribute__((__packed__)) ComponentDescription {
    OSType                          componentType;              /* A unique 4-byte code indentifying the command set */
    OSType                          componentSubType;           /* Particular flavor of this instance */
    OSType                          componentManufacturer;      /* Vendor indentification */
    unsigned long                   componentFlags;             /* 8 each for Component,Type,SubType,Manuf/revision */
    unsigned long                   componentFlagsMask;         /* Mask for specifying which flags to consider in search, zero during registration */
};
typedef struct ComponentDescription     ComponentDescription;


struct __attribute__((__packed__)) ResourceSpec {
    OSType                          resType;                    /* 4-byte code    */
    short                           resID;                      /*         */
};
typedef struct ResourceSpec             ResourceSpec;


struct __attribute__((__packed__)) ComponentResource {
    ComponentDescription            cd;                         /* Registration parameters */
    ResourceSpec                    component;                  /* resource where Component code is found */
    ResourceSpec                    componentName;              /* name string resource */
    ResourceSpec                    componentInfo;              /* info string resource */
    ResourceSpec                    componentIcon;              /* icon resource */
};
typedef struct ComponentResource        ComponentResource;
typedef ComponentResource *             ComponentResourcePtr;
typedef ComponentResourcePtr *          ComponentResourceHandle;


struct __attribute__((__packed__)) ComponentRecord {
    long                            data[1];
};
typedef struct ComponentRecord          ComponentRecord;
typedef ComponentRecord *               Component;


struct __attribute__((__packed__)) ComponentInstanceRecord {
    long                            data[1];
};
typedef struct ComponentInstanceRecord  ComponentInstanceRecord;

typedef ComponentInstanceRecord *       ComponentInstance;

// ========================= QUICKDRAW =========================

struct __attribute__((__packed__)) Rect {
    short                           top;
    short                           left;
    short                           bottom;
    short                           right;
};
typedef struct Rect                     Rect;
typedef Rect *                          RectPtr;

struct __attribute__((__packed__)) RGBColor {
    unsigned short                  red;                        /*magnitude of red component*/
    unsigned short                  green;                      /*magnitude of green component*/
    unsigned short                  blue;                       /*magnitude of blue component*/
};
typedef struct RGBColor                 RGBColor;
typedef RGBColor *                      RGBColorPtr;
typedef RGBColorPtr *                   RGBColorHdl;

struct __attribute__((__packed__)) ColorSpec {
    short                           value;                      /*index or other value*/
    RGBColor                        rgb;                        /*true color*/
};
typedef struct ColorSpec                ColorSpec;
typedef ColorSpec *                     ColorSpecPtr;
typedef ColorSpec                       CSpecArray[1];

struct __attribute__((__packed__)) ColorTable {
    long                            ctSeed;                     /*unique identifier for table*/
    short                           ctFlags;                    /*high bit: 0 = PixMap; 1 = device*/
    short                           ctSize;                     /*number of entries in CTTable*/
    CSpecArray                      ctTable;                    /*array [0..0] of ColorSpec*/
};
typedef struct ColorTable               ColorTable;
typedef ColorTable *                    CTabPtr;
typedef CTabPtr *                       CTabHandle;

struct __attribute__((__packed__)) MatrixRecord {
    Fixed                           matrix[3][3];
};
typedef struct MatrixRecord             MatrixRecord;
typedef MatrixRecord *                  MatrixRecordPtr;

typedef long                            ImageSequence;
typedef OSType                          CodecType;
typedef unsigned short                  CodecFlags;
typedef unsigned long                   CodecQ;

struct __attribute__((__packed__)) ImageDescription {
    long                            idSize;                     /* total size of ImageDescription including extra data ( CLUTs and other per sequence data ) */
    CodecType                       cType;                      /* what kind of codec compressed this data */
    long                            resvd1;                     /* reserved for Apple use */
    short                           resvd2;                     /* reserved for Apple use */
    short                           dataRefIndex;               /* set to zero  */
    short                           version;                    /* which version is this data */
    short                           revisionLevel;              /* what version of that codec did this */
    long                            vendor;                     /* whose  codec compressed this data */
    CodecQ                          temporalQuality;            /* what was the temporal quality factor  */
    CodecQ                          spatialQuality;             /* what was the spatial quality factor */
    short                           width;                      /* how many pixels wide is this data */
    short                           height;                     /* how many pixels high is this data */
    Fixed                           hRes;                       /* horizontal resolution */
    Fixed                           vRes;                       /* vertical resolution */
    long                            dataSize;                   /* if known, the size of data for this image descriptor */
    short                           frameCount;                 /* number of frames this description applies to */
    Str31                           name;                       /* name of codec ( in case not installed )  */
    short                           depth;                      /* what depth is this data (1-32) or ( 33-40 grayscale ) */
    short                           clutID;                     /* clut id or if 0 clut follows  or -1 if no clut */
};
typedef struct ImageDescription         ImageDescription;
typedef ImageDescription *              ImageDescriptionPtr;
typedef ImageDescriptionPtr *           ImageDescriptionHandle;

/* values for PixMap.pixelFormat*/
enum {
    k16LE555PixelFormat         = FOUR_CHAR_CODE('L555'),       /* 16 bit LE rgb 555 (PC)*/
    k16LE5551PixelFormat        = FOUR_CHAR_CODE('5551'),       /* 16 bit LE rgb 5551*/
    k16BE565PixelFormat         = FOUR_CHAR_CODE('B565'),       /* 16 bit BE rgb 565*/
    k16LE565PixelFormat         = FOUR_CHAR_CODE('L565'),       /* 16 bit LE rgb 565*/
    k24BGRPixelFormat           = FOUR_CHAR_CODE('24BG'),       /* 24 bit bgr */
    k32BGRAPixelFormat          = FOUR_CHAR_CODE('BGRA'),       /* 32 bit bgra    (Matrox)*/
    k32ABGRPixelFormat          = FOUR_CHAR_CODE('ABGR'),       /* 32 bit abgr    */
    k32RGBAPixelFormat          = FOUR_CHAR_CODE('RGBA'),       /* 32 bit rgba    */
    kYUVSPixelFormat            = FOUR_CHAR_CODE('yuvs'),       /* YUV 4:2:2 byte ordering 16-unsigned = 'YUY2'*/
    kYUVUPixelFormat            = FOUR_CHAR_CODE('yuvu'),       /* YUV 4:2:2 byte ordering 16-signed*/
    kYVU9PixelFormat            = FOUR_CHAR_CODE('YVU9'),       /* YVU9 Planar    9*/
    kYUV411PixelFormat          = FOUR_CHAR_CODE('Y411'),       /* YUV 4:1:1 Interleaved  16*/
    kYVYU422PixelFormat         = FOUR_CHAR_CODE('YVYU'),       /* YVYU 4:2:2 byte ordering   16*/
    kUYVY422PixelFormat         = FOUR_CHAR_CODE('UYVY'),       /* UYVY 4:2:2 byte ordering   16*/
    kYUV211PixelFormat          = FOUR_CHAR_CODE('Y211'),       /* YUV 2:1:1 Packed   8*/
    k2vuyPixelFormat            = FOUR_CHAR_CODE('2vuy')        /* UYVY 4:2:2 byte ordering   16*/
};

struct __attribute__((__packed__)) PixMapExtension {
    long                            extSize;                    /*size of struct, duh!*/
    unsigned long                   pmBits;                     /*pixmap attributes bitfield*/
    void *                          pmGD;                       /*this is a GDHandle*/
    long                            pmSeed;
    Fixed                           gammaLevel;                 /*pixmap gammalevel*/
    Fixed                           requestedGammaLevel;
    unsigned long                   reserved2;
    long                            longRowBytes;               /*used when rowBytes > 16382*/
    unsigned long                   signature;
    Handle                          baseAddrHandle;
};
typedef struct PixMapExtension          PixMapExtension;

typedef PixMapExtension *               PixMapExtPtr;
typedef PixMapExtPtr *                  PixMapExtHandle;


struct __attribute__((__packed__)) PixMap {
    Ptr                             baseAddr;                   /*pointer to pixels*/
    short                           rowBytes;                   /*offset to next line*/
    Rect                            bounds;                     /*encloses bitmap*/
    short                           pmVersion;                  /*pixMap version number*/
    short                           packType;                   /*defines packing format*/
    long                            packSize;                   /*length of pixel data*/
    Fixed                           hRes;                       /*horiz. resolution (ppi)*/
    Fixed                           vRes;                       /*vert. resolution (ppi)*/
    short                           pixelType;                  /*defines pixel type*/
    short                           pixelSize;                  /*# bits in pixel*/
    short                           cmpCount;                   /*# components in pixel*/
    short                           cmpSize;                    /*# bits per component*/
    OSType                          pixelFormat;                /*fourCharCode representation*/
    CTabHandle                      pmTable;                    /*color map for this pixMap*/
    PixMapExtHandle                 pmExt;                      /*Handle to pixMap extension*/
};
typedef struct PixMap                   PixMap;
typedef PixMap *                        PixMapPtr;
typedef PixMapPtr *                     PixMapHandle;


struct __attribute__((__packed__)) BitMap {
    Ptr                             baseAddr;
    short                           rowBytes;
    Rect                            bounds;
};
typedef struct BitMap                   BitMap;
typedef BitMap *                        BitMapPtr;
typedef BitMapPtr *                     BitMapHandle;
typedef struct OpaqueRgnHandle*         RgnHandle;

struct Pattern {
    UInt8                           pat[8];
};
typedef struct Pattern                  Pattern;
typedef unsigned char                   Style;
typedef Style                           StyleField;
struct __attribute__((__packed__)) Point {
    short                           v;
    short                           h;
};
typedef struct Point                    Point;
struct __attribute__((__packed__)) GrafPort {
    short                           device;
    BitMap                          portBits;
    Rect                            portRect;
    RgnHandle                       visRgn;
    RgnHandle                       clipRgn;
    Pattern                         bkPat;
    Pattern                         fillPat;
    Point                           pnLoc;
    Point                           pnSize;
    short                           pnMode;
    Pattern                         pnPat;
    short                           pnVis;
    short                           txFont;
    StyleField                      txFace;                     /*StyleField occupies 16-bits, but only first 8-bits are used*/
    UInt8                           txFlags;                    /* QuickTime uses second 8 bits of StyleField for txFlags */
    short                           txMode;
    short                           txSize;
    Fixed                           spExtra;
    long                            fgColor;
    long                            bkColor;
    short                           colrBit;
    short                           patStretch;
    Handle                          picSave;
    Handle                          rgnSave;
    Handle                          polySave;
    /*QDProcsPtr*/void*                      grafProcs;
};
typedef struct GrafPort                 GrafPort;
typedef GrafPort *GWorldPtr;
typedef GWorldPtr *GWorldHandle;
#define anyCodec                ((CodecComponent)0)
enum {
                                                                /* transfer modes */
    srcCopy                     = 0,                            /*the 16 transfer modes*/
    srcOr                       = 1,
    srcXor                      = 2,
    srcBic                      = 3,
    notSrcCopy                  = 4,
    notSrcOr                    = 5,
    notSrcXor                   = 6,
    notSrcBic                   = 7,
    patCopy                     = 8,
    patOr                       = 9,
    patXor                      = 10,
    patBic                      = 11,
    notPatCopy                  = 12,
    notPatOr                    = 13,
    notPatXor                   = 14,
    notPatBic                   = 15,                           /* Special Text Transfer Mode */
    grayishTextOr               = 49,
    hilitetransfermode          = 50,
    hilite                      = 50,                           /* Arithmetic transfer modes */
    blend                       = 32,
    addPin                      = 33,
    addOver                     = 34,
    subPin                      = 35,
    addMax                      = 37,
    adMax                       = 37,
    subOver                     = 38,
    adMin                       = 39,
    ditherCopy                  = 64,                           /* Transparent mode constant */
    transparent                 = 36
};

typedef unsigned long                   GWorldFlags;



// ============================== CODECS ===========================

typedef Component                       CompressorComponent;
typedef Component                       DecompressorComponent;
typedef Component                       CodecComponent;

enum {
    codecLosslessQuality        = 0x00000400,
    codecMaxQuality             = 0x000003FF,
    codecMinQuality             = 0x00000000,
    codecLowQuality             = 0x00000100,
    codecNormalQuality          = 0x00000200,
    codecHighQuality            = 0x00000300
};



// callbacks:
typedef void* ImageCodecDrawBandCompleteUPP;
typedef long long ICMProgressProcRecord;
typedef long long ICMCompletionProcRecord;
typedef long long ICMDataProcRecord;
typedef void* ICMFrameTimePtr;
typedef void* CDSequenceDataSourcePtr;
typedef void* ICMFrameTimeInfoPtr;

// graphics port
typedef struct OpaqueGrafPtr*           GrafPtr;
typedef GrafPtr                         CGrafPtr;


/*  codec capabilities flags    */
enum {
    codecCanScale               = 1L << 0,
	// 1
    codecCanMask                = 1L << 1,
	// 2
    codecCanMatte               = 1L << 2,
	// 4
    codecCanTransform           = 1L << 3,
	// 8
    codecCanTransferMode        = 1L << 4,
	// 10
    codecCanCopyPrev            = 1L << 5,
	// 20
    codecCanSpool               = 1L << 6,
	// 40
    codecCanClipVertical        = 1L << 7,
	// 80
    codecCanClipRectangular     = 1L << 8,
	// 100
    codecCanRemapColor          = 1L << 9,
	// 200
    codecCanFastDither          = 1L << 10,
	// 400
    codecCanSrcExtract          = 1L << 11,
	// 800
    codecCanCopyPrevComp        = 1L << 12,
	// 1000
    codecCanAsync               = 1L << 13,
	// 2000
    codecCanMakeMask            = 1L << 14,
	// 4000
    codecCanShift               = 1L << 15,
	// 8000
    codecCanAsyncWhen           = 1L << 16,
	// 10000
    codecCanShieldCursor        = 1L << 17,
	// 20000
    codecCanManagePrevBuffer    = 1L << 18,
	// 40000
    codecHasVolatileBuffer      = 1L << 19,     // 80000                /* codec requires redraw after window movement */
    codecWantsRegionMask        = 1L << 20,
	// 100000
    codecImageBufferIsOnScreen  = 1L << 21,     // 200000                /* old def of codec using overlay surface, = ( codecIsDirectToScreenOnly | codecUsesOverlaySurface | codecImageBufferIsOverlaySurface | codecSrcMustBeImageBuffer ) */
    codecWantsDestinationPixels = 1L << 22,
     // 400000
    codecWantsSpecialScaling    = 1L << 23,
     // 800000
    codecHandlesInputs          = 1L << 24,
	// 1000000
    codecCanDoIndirectSurface   = 1L << 25,                     /* codec can handle indirect surface (GDI) */
    codecIsSequenceSensitive    = 1L << 26,
    codecRequiresOffscreen      = 1L << 27,
    codecRequiresMaskBits       = 1L << 28,
    codecCanRemapResolution     = 1L << 29,
    codecIsDirectToScreenOnly   = 1L << 30,                     /* codec can only decompress data to the screen */
    codecCanLockSurface         = 1L << 31                      /* codec can lock destination surface, icm doesn't lock for you */
};

/*  codec capabilities flags2   */
enum {
    codecUsesOverlaySurface     = 1L << 0,                      /* codec uses overlay surface */
    codecImageBufferIsOverlaySurface = 1L << 1,                 /* codec image buffer is overlay surface, the bits in the buffer are on the screen */
    codecSrcMustBeImageBuffer   = 1L << 2,                      /* codec can only source data from an image buffer */
    codecImageBufferIsInAGPMemory = 1L << 4,                    /* codec image buffer is in AGP space, byte writes are OK */
    codecImageBufferIsInPCIMemory = 1L << 5                     /* codec image buffer is across a PCI bus; byte writes are bad */
};

/*  codec condition flags   */
// FFD =  13 = 8+4+1
enum {
    codecConditionFirstBand     = 1L << 0,
	// 1
    codecConditionLastBand      = 1L << 1,
	// 2
    codecConditionFirstFrame    = 1L << 2,
	// 4
    codecConditionNewDepth      = 1L << 3,
	// 8
    codecConditionNewTransform  = 1L << 4,
	// 10
    codecConditionNewSrcRect    = 1L << 5,
	// 20
    codecConditionNewMask       = 1L << 6,
	// 40
    codecConditionNewMatte      = 1L << 7,
	// 80
    codecConditionNewTransferMode = 1L << 8,
	// 100
    codecConditionNewClut       = 1L << 9,
	// 200
    codecConditionNewAccuracy   = 1L << 10,
	// 400
    codecConditionNewDestination = 1L << 11,
	// 800
    codecConditionFirstScreen   = 1L << 12,
	// 1000
    codecConditionDoCursor      = 1L << 13,
	// 2000
    codecConditionCatchUpDiff   = 1L << 14,
	// 4000
    codecConditionMaskMayBeChanged = 1L << 15,
	// 8000
    codecConditionToBuffer      = 1L << 16,
	// 10000
    codecConditionCodecChangedMask = 1L << 31
	// 20000
};



struct __attribute__((__packed__)) CodecCapabilities {
    long                            flags;
    short                           wantedPixelSize;
    short                           extendWidth;
    short                           extendHeight;
    short                           bandMin;
    short                           bandInc;
    short                           pad;
    unsigned long                   time;
    long                            flags2;                     /* field new in QuickTime 4.0 */
};
typedef struct CodecCapabilities        CodecCapabilities;

struct __attribute__((__packed__)) CodecDecompressParams {
    ImageSequence                   sequenceID;                 /* predecompress,banddecompress */
    ImageDescriptionHandle          imageDescription;           /* predecompress,banddecompress */
    Ptr                             data;
    long                            bufferSize;

    long                            frameNumber;
    long                            startLine;
    long                            stopLine;
    long                            conditionFlags;

    CodecFlags                      callerFlags;
 // short
    CodecCapabilities *             capabilities;               /* predecompress,banddecompress */
    ICMProgressProcRecord           progressProcRecord;
    ICMCompletionProcRecord         completionProcRecord;

    ICMDataProcRecord               dataProcRecord;
    CGrafPtr                        port;                       /* predecompress,banddecompress */
    PixMap                          dstPixMap;                  /* predecompress,banddecompress */
    BitMapPtr                       maskBits;
    PixMapPtr                       mattePixMap;
    Rect                            srcRect;                    /* predecompress,banddecompress */
    MatrixRecord *                  matrix;                     /* predecompress,banddecompress */
    CodecQ                          accuracy;                   /* predecompress,banddecompress */
    short                           transferMode;               /* predecompress,banddecompress */
    ICMFrameTimePtr                 frameTime;                  /* banddecompress */
    long                            reserved[1];

                                                                /* The following fields only exist for QuickTime 2.0 and greater */
    SInt8                           matrixFlags;                /* high bit set if 2x resize */
    SInt8                           matrixType;
    Rect                            dstRect;                    /* only valid for simple transforms */

                                                                /* The following fields only exist for QuickTime 2.1 and greater */
    UInt16                          majorSourceChangeSeed;
    UInt16                          minorSourceChangeSeed;
    CDSequenceDataSourcePtr         sourceData;

    RgnHandle                       maskRegion;

                                                                /* The following fields only exist for QuickTime 2.5 and greater */
    OSType **                       wantedDestinationPixelTypes; /* Handle to 0-terminated list of OSTypes */

    long                            screenFloodMethod;
    long                            screenFloodValue;
    short                           preferredOffscreenPixelSize;

                                                                /* The following fields only exist for QuickTime 3.0 and greater */
    ICMFrameTimeInfoPtr             syncFrameTime;              /* banddecompress */
    Boolean                         needUpdateOnTimeChange;     /* banddecompress */
    Boolean                         enableBlackLining;
    Boolean                         needUpdateOnSourceChange;   /* band decompress */
    Boolean                         pad;

    long                            unused;

    CGrafPtr                        finalDestinationPort;

    long                            requestedBufferWidth;       /* must set codecWantsSpecialScaling to indicate this field is valid*/
    long                            requestedBufferHeight;      /* must set codecWantsSpecialScaling to indicate this field is valid*/

                                                                /* The following fields only exist for QuickTime 4.0 and greater */
    Rect                            displayableAreaOfRequestedBuffer; /* set in predecompress*/
    Boolean                         requestedSingleField;
    Boolean                         needUpdateOnNextIdle;
    Boolean                         pad2[2];
    Fixed                           bufferGammaLevel;

                                                                /* The following fields only exist for QuickTime 5.0 and greater */
    UInt32                          taskWeight;                 /* preferred weight for MP tasks implementing this operation*/
    OSType                          taskName;                   /* preferred name (type) for MP tasks implementing this operation*/
};
typedef struct CodecDecompressParams    CodecDecompressParams;



struct __attribute__((__packed__)) ImageSubCodecDecompressCapabilities {
    long                            recordSize;                 /* sizeof(ImageSubCodecDecompressCapabilities)*/
    long                            decompressRecordSize;       /* size of your codec's decompress record*/
    Boolean                         canAsync;                   /* default true*/
    UInt8                           pad0;

                                                                /* The following fields only exist for QuickTime 4.0 and greater */
    UInt16                          suggestedQueueSize;
    Boolean                         canProvideTrigger;

                                                                /* The following fields only exist for QuickTime 5.0 and greater */
    Boolean                         subCodecFlushesScreen;      /* only used on Mac OS X*/
    Boolean                         subCodecCallsDrawBandComplete;
    UInt8                           pad2[1];

                                                                /* The following fields only exist for QuickTime 5.1 and greater */
    Boolean                         isChildCodec;               /* set by base codec before calling Initialize*/
    UInt8                           pad3[3];
};
typedef struct ImageSubCodecDecompressCapabilities ImageSubCodecDecompressCapabilities;


struct __attribute__((__packed__)) ImageSubCodecDecompressRecord {
    Ptr                             baseAddr;
    long                            rowBytes;
    Ptr                             codecData;
    ICMProgressProcRecord           progressProcRecord;
    ICMDataProcRecord               dataProcRecord;
    void *                          userDecompressRecord;       /* pointer to codec-specific per-band data*/
    UInt8                           frameType;
    Boolean                         inhibitMP;                  /* set this in BeginBand to tell the base decompressor not to call DrawBand from an MP task for this frame.  (Only has any effect for MP-capable subcodecs.  New in QuickTime 5.0.)*/
    UInt8                           pad[2];
    long                            priv[2];

                                                                /* The following fields only exist for QuickTime 5.0 and greater */
    ImageCodecDrawBandCompleteUPP   drawBandCompleteUPP;        /* only used if subcodec set subCodecCallsDrawBandComplete; if drawBandCompleteUPP is non-nil, codec must call it when a frame is finished, but may return from DrawBand before the frame is finished. */
    void *                          drawBandCompleteRefCon;     /* Note: do not call drawBandCompleteUPP directly from a hardware interrupt; instead, use DTInstall to run a function at deferred task time, and call drawBandCompleteUPP from that. */
};
typedef struct ImageSubCodecDecompressRecord ImageSubCodecDecompressRecord;


/* These are the bits that are set in the Component flags, and also in the codecInfo struct. */
enum {
    codecInfoDoes1              = (1L << 0),                    /* codec can work with 1-bit pixels */
    codecInfoDoes2              = (1L << 1),                    /* codec can work with 2-bit pixels */
    codecInfoDoes4              = (1L << 2),                    /* codec can work with 4-bit pixels */
    codecInfoDoes8              = (1L << 3),                    /* codec can work with 8-bit pixels */
    codecInfoDoes16             = (1L << 4),                    /* codec can work with 16-bit pixels */
    codecInfoDoes32             = (1L << 5),                    /* codec can work with 32-bit pixels */
    codecInfoDoesDither         = (1L << 6),                    /* codec can do ditherMode */
    codecInfoDoesStretch        = (1L << 7),                    /* codec can stretch to arbitrary sizes */
    codecInfoDoesShrink         = (1L << 8),                    /* codec can shrink to arbitrary sizes */
    codecInfoDoesMask           = (1L << 9),                    /* codec can mask to clipping regions */
    codecInfoDoesTemporal       = (1L << 10),                   /* codec can handle temporal redundancy */
    codecInfoDoesDouble         = (1L << 11),                   /* codec can stretch to double size exactly */
    codecInfoDoesQuad           = (1L << 12),                   /* codec can stretch to quadruple size exactly */
    codecInfoDoesHalf           = (1L << 13),                   /* codec can shrink to half size */
    codecInfoDoesQuarter        = (1L << 14),                   /* codec can shrink to quarter size */
    codecInfoDoesRotate         = (1L << 15),                   /* codec can rotate on decompress */
    codecInfoDoesHorizFlip      = (1L << 16),                   /* codec can flip horizontally on decompress */
    codecInfoDoesVertFlip       = (1L << 17),                   /* codec can flip vertically on decompress */
    codecInfoHasEffectParameterList = (1L << 18),               /* codec implements get effects parameter list call, once was codecInfoDoesSkew */
    codecInfoDoesBlend          = (1L << 19),                   /* codec can blend on decompress */
    codecInfoDoesWarp           = (1L << 20),                   /* codec can warp arbitrarily on decompress */
    codecInfoDoesRecompress     = (1L << 21),                   /* codec can recompress image without accumulating errors */
    codecInfoDoesSpool          = (1L << 22),                   /* codec can spool image data */
    codecInfoDoesRateConstrain  = (1L << 23)                    /* codec can data rate constrain */
};


enum {
    codecInfoDepth1             = (1L << 0),                    /* compressed data at 1 bpp depth available */
    codecInfoDepth2             = (1L << 1),                    /* compressed data at 2 bpp depth available */
    codecInfoDepth4             = (1L << 2),                    /* compressed data at 4 bpp depth available */
    codecInfoDepth8             = (1L << 3),                    /* compressed data at 8 bpp depth available */
    codecInfoDepth16            = (1L << 4),                    /* compressed data at 16 bpp depth available */
    codecInfoDepth32            = (1L << 5),                    /* compressed data at 32 bpp depth available */
    codecInfoDepth24            = (1L << 6),                    /* compressed data at 24 bpp depth available */
    codecInfoDepth33            = (1L << 7),                    /* compressed data at 1 bpp monochrome depth  available */
    codecInfoDepth34            = (1L << 8),                    /* compressed data at 2 bpp grayscale depth available */
    codecInfoDepth36            = (1L << 9),                    /* compressed data at 4 bpp grayscale depth available */
    codecInfoDepth40            = (1L << 10),                   /* compressed data at 8 bpp grayscale depth available */
    codecInfoStoresClut         = (1L << 11),                   /* compressed data can have custom cluts */
    codecInfoDoesLossless       = (1L << 12),                   /* compressed data can be stored in lossless format */
    codecInfoSequenceSensitive  = (1L << 13)                    /* compressed data is sensitive to out of sequence decoding */
};

struct __attribute__((__packed__)) CodecInfo {
    Str31                           typeName;                   /* name of the codec type i.e.: 'Apple Image Compression' */
    short                           version;                    /* version of the codec data that this codec knows about */
    short                           revisionLevel;              /* revision level of this codec i.e: 0x00010001 (1.0.1) */
    long                            vendor;                     /* Maker of this codec i.e: 'appl' */
    long                            decompressFlags;            /* codecInfo flags for decompression capabilities */
    long                            compressFlags;              /* codecInfo flags for compression capabilities */
    long                            formatFlags;                /* codecInfo flags for compression format details */
    UInt8                           compressionAccuracy;        /* measure (1-255) of accuracy of this codec for compress (0 if unknown) */
    UInt8                           decompressionAccuracy;      /* measure (1-255) of accuracy of this codec for decompress (0 if unknown) */
    unsigned short                  compressionSpeed;           /* ( millisecs for compressing 320x240 on base mac II) (0 if unknown)  */
    unsigned short                  decompressionSpeed;         /* ( millisecs for decompressing 320x240 on mac II)(0 if unknown)  */
    UInt8                           compressionLevel;           /* measure (1-255) of compression level of this codec (0 if unknown)  */
    UInt8                           resvd;                      /* pad */
    short                           minimumHeight;              /* minimum height of image (block size) */
    short                           minimumWidth;               /* minimum width of image (block size) */
    short                           decompressPipelineLatency;  /* in milliseconds ( for asynchronous codecs ) */
    short                           compressPipelineLatency;    /* in milliseconds ( for asynchronous codecs ) */
    long                            privateData;
};
typedef struct CodecInfo                CodecInfo;

static inline void dump_ImageDescription(void* xxx){
    ImageDescription* id=(ImageDescription*)xxx;
    unsigned char* x;
    int i;

    for(i=0;i<id->idSize;i++){
	printf(" %02X",((unsigned char*)id)[i]);
	if((i%16)==15) printf("\n");
    }
    printf("\n");


    printf("=============== ImageDescription at %p ==================\n",xxx);
    printf("idSize=0x%X  fourcc=0x%08X\n",id->idSize,id->cType);
    printf("ver=%d rev=%d vendor=0x%08X\n",id->version,id->revisionLevel,id->vendor);
    printf("tempQ=%d spatQ=%d  dim: %d x %d  dpi: %d x %d  depth: %d\n",
	id->temporalQuality,id->spatialQuality,
	id->width, id->height,
	id->hRes, id->vRes,
	id->depth);
    printf("dataSize=%d frameCount=%d clutID=%d\n",id->dataSize, id->frameCount, id->clutID);
    printf("name='%.*s'\n",((char*)(&id->name))[0],((char*)(&id->name))+1);
    x=((char*)(&id->clutID))+2;
    if(id->idSize>sizeof(ImageDescription)){
	printf("%02X %02X %02X %02X | %02X %02X %02X %02X | %02X %02X %02X %02X | %02X %02X %02X %02X\n",
	x[0],x[1],x[2],x[3],x[4],x[5],x[6],x[7],x[8],x[9],x[10],x[11],x[12],x[13],x[14],x[15]);
    }
    printf("=========================================================\n");
}

static inline void dump_Rect(char* title,Rect *r){
    printf("%s: %d;%d - %d;%d\n",title,
        (int)r->top,(int)r->left,(int)r->bottom,(int)r->right);
}

static inline void dump_MatrixRecord(char* title, MatrixRecord *m){
    printf("%s: [%d %d %d][%d %d %d][%d %d %d]\n",title,
	m->matrix[0][0],m->matrix[0][1],m->matrix[0][2],
	m->matrix[1][0],m->matrix[1][1],m->matrix[1][2],
	m->matrix[2][0],m->matrix[2][1],m->matrix[2][2]);
}

static inline void dump_PixMap(void* xxx){
    PixMap *p=xxx;
    printf("=============== PixMap at %p ==================\n",xxx);
    printf("base=%p  stride=%d\n",p->baseAddr, p->rowBytes);
    dump_Rect("bounds",&p->bounds);
    printf("pmVersion=0x%X packType=0x%X\n packSize=0x%X\n",
	p->pmVersion,p->packType, p->packSize);
    printf("hRes=0x%X vRes=0x%X pixelType=0x%X pixelSize=0x%X\n",
	p->hRes,p->vRes,p->pixelType,p->pixelSize);
    printf("cmpCount=0x%X cmpSize=0x%X pixelFormat=0x%X\n",
	p->cmpCount,p->cmpSize,p->pixelFormat);
    printf("pmTable=%p pmExt=%p\n",p->pmTable,p->pmExt);
    printf("=========================================================\n");
}

static inline void dump_CodecCapabilities(void* xxx){
    CodecCapabilities* cc=xxx;
    if(!xxx) return;
    printf("=============== CodecCapabilities at %p =================\n",xxx);
    printf("flags=0x%X  flags2=0x%X\n",cc->flags,cc->flags2);
    printf("wantedPixelSize=%d extendWidth=%d extendHeight=%d band=%d+%d\n",
	cc->wantedPixelSize,cc->extendWidth,cc->extendHeight,
	cc->bandMin,cc->bandInc);
    printf("pad=0x%X  time=0x%X\n",cc->pad,cc->time);
    printf("=========================================================\n");
}

static inline void dump_CodecDecompressParams(void* xxx){
    CodecDecompressParams* cd=xxx;
    ImageDescription **idh;
    int i;
    if(!xxx) return;
    printf("=============== CodecDecompressParams at %p ==================\n",xxx);
    printf("sequenceID=%d\n",cd->sequenceID);
    idh=cd->imageDescription;
    if(idh && idh[0]) dump_ImageDescription(idh[0]);
    
    for(i=0;i<sizeof(CodecDecompressParams);i++){
	printf(" %02X",((unsigned char*)cd)[i]);
	if((i%16)==15) printf("\n");
    }
    printf("\n");
    
    printf("data=%p  size=%d\n",cd->data,cd->bufferSize);
    printf("frameno=%d  lines: %d .. %d   condflags=0x%X  callerflags=0x%X\n",
	cd->frameNumber, cd->startLine, cd->stopLine, cd->conditionFlags,cd->callerFlags);
//    printf("maskBits=%p mattePixMap=%p\n",
//	cd->maskBits,cd->mattePixMap);
//    dump_PixMap(&cd->dstPixMap);
//    if(cd->mattePixMap) dump_PixMap(cd->mattePixMap);
//    dump_MatrixRecord("matrix",cd->matrix);
    printf("accuracy=%d  transferMode=%d  matrixFlags=0x%X matrixType=%d\n",
	(int)cd->accuracy, (int)cd->transferMode, (int)cd->matrixFlags, (int)cd->matrixType);
    printf("srcrect: %d;%d - %d;%d\n",cd->srcRect.top,cd->srcRect.left,cd->srcRect.bottom,cd->srcRect.right);
    printf("dstrect: %d;%d - %d;%d\n",cd->dstRect.top,cd->dstRect.left,cd->dstRect.bottom,cd->dstRect.right);
    printf("wantedDestinationPixelTypes=%p\n",cd->wantedDestinationPixelTypes);
    printf("screenFloodMethod=%d value=%d  preferredOffscreenPixelSize=%d\n",
	cd->screenFloodMethod, cd->screenFloodValue, cd->preferredOffscreenPixelSize);
    printf("callbacks: progress=%p compl=%p data=%p ftime=%p srcdata=%p sync=%p\n",
     cd->progressProcRecord, cd->completionProcRecord,
     cd->dataProcRecord, cd->frameTime, cd->sourceData, cd->syncFrameTime);
//    printf("\n");

    printf("=========================================================\n");


}

