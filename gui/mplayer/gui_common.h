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

#ifndef MPLAYER_GUI_GUI_COMMON_H
#define MPLAYER_GUI_GUI_COMMON_H

#include "gui/app.h"

#define DLABEL_DELAY 2500   // in milliseconds

void PutImage(txSample *bf, int x, int y, int max, int ofs);
void Render(wsTWindow *window, wItem *Items, int nrItems, char *db, int size);
void SimplePotmeterPutImage(txSample *bf, int x, int y, float frac);
char *Translate(char *str);

#endif /* MPLAYER_GUI_GUI_COMMON_H */
