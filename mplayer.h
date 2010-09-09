/*
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

#ifndef MPLAYER_MPLAYER_H
#define MPLAYER_MPLAYER_H

extern char* current_module;

extern char ** audio_fm_list;
extern char ** video_fm_list;
extern char ** video_driver_list;
extern char ** audio_driver_list;
extern float  audio_delay;

extern int osd_level;
extern unsigned int osd_visible;

extern char * filename;

extern int use_menu;
extern int autosync;
extern double start_pts;
extern int frame_dropping;

/* for the GUI */
extern int auto_quality;
extern int stream_dump_type;

void update_set_of_subtitles(void);

#endif /* MPLAYER_MPLAYER_H */
