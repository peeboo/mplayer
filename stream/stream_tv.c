/*
 *  Copyright (C) 2006 Benjamin Zores
 *   Stream layer for TV Input, based on previous work from Albeu
 *
 *   This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software Foundation,
 *  Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#include "config.h"

#include <stdlib.h>
#include <string.h>

#include "stream.h"
#include "demuxer.h"

static int
tv_stream_open (stream_t *stream, int mode, void *opts, int *file_format)
{
  extern char* tv_param_channel;
  
  stream->type = STREAMTYPE_TV;
  *file_format =  DEMUXER_TYPE_TV;
  if (strlen (stream->url) > 5 && stream->url[5] != '\0')
    tv_param_channel = strdup (stream->url + 5);
  
  return STREAM_OK;
}

stream_info_t stream_info_tv = {
  "TV Input",
  "tv",
  "Benjamin Zores, Albeu",
  "",
  tv_stream_open, 			
  { "tv", NULL },
  NULL,
  1
};
