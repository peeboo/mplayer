#include "dmo_guids.h"
int DMO_DEBUG = 0;

const GUID IID_IMediaBuffer = { 0x59eff8b9, 0x938c, 0x4a26,
{ 0x82, 0xf2, 0x95, 0xcb, 0x84, 0xcd, 0xc8, 0x37}};
const GUID IID_IMediaObject = { 0xd8ad0f58, 0x5494, 0x4102,
{ 0x97, 0xc5, 0xec, 0x79, 0x8e, 0x59, 0xbc, 0xf4}};
const GUID IID_IEnumDMO = { 0x2c3cd98a, 0x2bfa, 0x4a53,
{ 0x9c, 0x27, 0x52, 0x49, 0xba, 0x64, 0xba, 0x0f}};
const GUID IID_IMediaObjectInPlace = { 0x651b9ad0, 0x0fc7, 0x4aa9,
{ 0x95, 0x38, 0xd8, 0x99, 0x31, 0x01, 0x07, 0x41}};
const GUID IID_IDMOQualityControl = { 0x65abea96, 0xcf36, 0x453f,
{ 0xaf, 0x8a, 0x70, 0x5e, 0x98, 0xf1, 0x62, 0x60}};
const GUID IID_IDMOVideoOutputOptimizations = { 0xbe8f4f4e, 0x5b16, 0x4d29,
{ 0xb3, 0x50, 0x7f, 0x6b, 0x5d, 0x92, 0x98, 0xac}};


const GUID DMOCATEGORY_AUDIO_DECODER = { 0x57f2db8b, 0xe6bb, 0x4513,
{ 0x9d, 0x43, 0xdc, 0xd2, 0xa6, 0x59, 0x31, 0x25}};
const GUID DMOCATEGORY_AUDIO_ENCODER = { 0x33d9a761, 0x90c8, 0x11d0,
{ 0xbd, 0x43, 0x00, 0xa0, 0xc9, 0x11, 0xce, 0x86}};
const GUID DMOCATEGORY_VIDEO_DECODER = { 0x4a69b442, 0x28be, 0x4991,
{ 0x96, 0x9c, 0xb5, 0x00, 0xad, 0xf5, 0xd8, 0xa8}};
const GUID DMOCATEGORY_VIDEO_ENCODER = { 0x33d9a760, 0x90c8, 0x11d0,
{ 0xbd, 0x43, 0x00, 0xa0, 0xc9, 0x11, 0xce, 0x86}};
const GUID DMOCATEGORY_AUDIO_EFFECT = { 0xf3602b3f, 0x0592, 0x48df,
{ 0xa4, 0xcd, 0x67, 0x47, 0x21, 0xe7, 0xeb, 0xeb}};
const GUID DMOCATEGORY_VIDEO_EFFECT = { 0xd990ee14, 0x776c, 0x4723,
{ 0xbe, 0x46, 0x3d, 0xa2, 0xf5, 0x6f, 0x10,0xb9}};
const GUID DMOCATEGORY_AUDIO_CAPTURE_EFFECT = { 0xf665aaba, 0x3e09, 0x4920,
{ 0xaa, 0x5f, 0x21, 0x98, 0x11, 0x14, 0x8f, 0x09}};


const GUID DMOCATEGORY_ACOUSTIC_ECHO_CANCEL = { 0xBF963D80L, 0xC559, 0x11D0,
{ 0x8A, 0x2B, 0x00, 0xA0, 0xC9, 0x25, 0x5A, 0xC1}};

const GUID DMOCATEGORY_AUDIO_NOISE_SUPPRESS = { 0xe07f903f, 0x62fd, 0x4e60,
{ 0x8c, 0xdd, 0xde, 0xa7, 0x23, 0x66, 0x65, 0xb5}};

const GUID DMOCATEGORY_AGC = { 0xe88c9ba0l, 0xc557, 0x11d0,
{ 0x8a, 0x2b, 0x00, 0xa0, 0xc9, 0x25, 0x5a, 0xc1}};
