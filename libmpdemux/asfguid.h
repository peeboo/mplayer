/*
 * Copyright (C) 2001 Reimar Döffinger
 *
 * This file is part of MPlayer.
 *
 * MPlayer is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * MPlayer is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with MPlayer; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef MPLAYER_ASFGUID_H
#define MPLAYER_ASFGUID_H

#include <inttypes.h>
#include "libavutil/common.h"
#include "mpbswap.h"


#define	ASF_LOAD_GUID_PREFIX(guid)	AV_RL32(guid)

#define ASF_GUID_PREFIX_audio_stream	0xF8699E40
#define ASF_GUID_PREFIX_video_stream	0xBC19EFC0
#define ASF_GUID_PREFIX_audio_conceal_none 0x49f1a440
#define ASF_GUID_PREFIX_audio_conceal_interleave 0xbfc3cd50
#define ASF_GUID_PREFIX_header		0x75B22630
#define ASF_GUID_PREFIX_data_chunk	0x75b22636
#define ASF_GUID_PREFIX_index_chunk	0x33000890
#define ASF_GUID_PREFIX_stream_header	0xB7DC0791
#define ASF_GUID_PREFIX_header_2_0	0xD6E229D1
#define ASF_GUID_PREFIX_file_header	0x8CABDCA1
#define	ASF_GUID_PREFIX_content_desc	0x75b22633
#define	ASF_GUID_PREFIX_stream_group	0x7bf875ce
#define ASF_GUID_PREFIX_ext_audio_stream	0x31178C9D
#define ASF_GUID_PREFIX_ext_stream_embed_stream_header	0x3AFB65E2
#define ASF_GUID_PREFIX_dvr_ms_timing_rep_data	0xFD3CC02A
#define ASF_GUID_PREFIX_dvr_ms_vid_frame_rep_data	0xDD6432CC

/*
const char asf_audio_stream_guid[16] = {0x40, 0x9e, 0x69, 0xf8,
  0x4d, 0x5b, 0xcf, 0x11, 0xa8, 0xfd, 0x00, 0x80, 0x5f, 0x5c, 0x44, 0x2b};
const char asf_video_stream_guid[16] = {0xc0, 0xef, 0x19, 0xbc,
  0x4d, 0x5b, 0xcf, 0x11, 0xa8, 0xfd, 0x00, 0x80, 0x5f, 0x5c, 0x44, 0x2b};
*/
static const char asf_stream_header_guid[16] = {0x91, 0x07, 0xdc, 0xb7,
  0xb7, 0xa9, 0xcf, 0x11, 0x8e, 0xe6, 0x00, 0xc0, 0x0c, 0x20, 0x53, 0x65};
static const char asf_file_header_guid[16] = {0xa1, 0xdc, 0xab, 0x8c,
  0x47, 0xa9, 0xcf, 0x11, 0x8e, 0xe4, 0x00, 0xc0, 0x0c, 0x20, 0x53, 0x65};
static const char asf_content_desc_guid[16] = {0x33, 0x26, 0xb2, 0x75,
  0x8e, 0x66, 0xcf, 0x11, 0xa6, 0xd9, 0x00, 0xaa, 0x00, 0x62, 0xce, 0x6c};
static const char asf_stream_group_guid[16] = {0xce, 0x75, 0xf8, 0x7b,
  0x8d, 0x46, 0xd1, 0x11, 0x8d, 0x82, 0x00, 0x60, 0x97, 0xc9, 0xa2, 0xb2};
static const char asf_data_chunk_guid[16] = {0x36, 0x26, 0xb2, 0x75,
  0x8e, 0x66, 0xcf, 0x11, 0xa6, 0xd9, 0x00, 0xaa, 0x00, 0x62, 0xce, 0x6c};
static const char asf_ext_stream_embed_stream_header[16] = {0xe2, 0x65, 0xfb, 0x3a,
  0xef, 0x47, 0xf2, 0x40, 0xac, 0x2c, 0x70, 0xa9, 0x0d, 0x71, 0xd3, 0x43};
static const char asf_ext_stream_audio[16] = {0x9d, 0x8c, 0x17, 0x31,
  0xe1, 0x03, 0x28, 0x45, 0xb5, 0x82, 0x3d, 0xf9, 0xdb, 0x22, 0xf5, 0x03};
static const char asf_ext_stream_header[16] = {0xCB, 0xA5, 0xE6, 0x14,
  0x72, 0xC6, 0x32, 0x43, 0x83, 0x99, 0xA9, 0x69, 0x52, 0x06, 0x5B, 0x5A};
static const char asf_metadata_header[16] = {0xea, 0xcb, 0xf8, 0xc5,
  0xaf, 0x5b, 0x77, 0x48, 0x84, 0x67, 0xaa, 0x8c, 0x44, 0xfa, 0x4c, 0xca};
static const char asf_content_encryption[16] = {0xfb, 0xb3, 0x11, 0x22,
  0x23, 0xbd, 0xd2, 0x11, 0xb4, 0xb7, 0x00, 0xa0, 0xc9, 0x55, 0xfc, 0x6e};
static const char asf_dvr_ms_timing_rep_data[16] = {0x2a, 0xc0, 0x3c,0xfd,
  0xdb, 0x06, 0xfa, 0x4c, 0x80, 0x1c, 0x72, 0x12, 0xd3, 0x87, 0x45, 0xe4};
static const char asf_dvr_ms_vid_frame_rep_data[16] = {0xcc, 0x32, 0x64, 0xdd,
  0x29, 0xe2, 0xdb, 0x40, 0x80, 0xf6, 0xd2, 0x63, 0x28, 0xd2, 0x76, 0x1f};

static int find_asf_guid(char *buf, const char *guid, int cur_pos, int buf_len)
{
  int i;
  for (i = cur_pos; i < buf_len - 19; i++) {
    if (memcmp(&buf[i], guid, 16) == 0)
      return i + 16 + 8; // point after guid + length
  }
  return -1;
}

#endif /* MPLAYER_ASFGUID_H */
