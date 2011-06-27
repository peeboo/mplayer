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

#include <stdlib.h>
#include <string.h>

#include "interface.h"
#include "app.h"
#include "skin/skin.h"
#include "ui/gmplayer.h"
#include "ui/widgets.h"
#include "wm/ws.h"
#include "wm/wsxdnd.h"

#include "access_mpcontext.h"
#include "config.h"
#include "help_mp.h"
#include "input/input.h"
#include "libaf/equalizer.h"
#include "libmpcodecs/dec_audio.h"
#include "libmpcodecs/dec_video.h"
#include "libmpcodecs/vd.h"
#include "libmpcodecs/vf.h"
#include "libvo/video_out.h"
#include "libvo/x11_common.h"
#include "mixer.h"
#include "mp_msg.h"
#include "mpcommon.h"
#include "mplayer.h"
#include "path.h"
#include "sub/font_load.h"
#include "sub/sub.h"

#ifdef CONFIG_DVDREAD
#include "stream/stream_dvd.h"
#endif

guiInterface_t guiInfo;

int guiWinID = -1;

char *skinName;
char *skinDirInHome;
char *skinMPlayerDir;

plItem *plCurrent    = NULL;
plItem *plList       = NULL;
plItem *plLastPlayed = NULL;

urlItem *URLList = NULL;

char *fsHistory[fsPersistant_MaxPos] = { NULL, NULL, NULL, NULL, NULL };

float gtkEquChannels[6][10];

static int initialized;

int gstrcmp(const char *a, const char *b)
{
    if (!a && !b)
        return 0;
    if (!a || !b)
        return -1;

    return strcmp(a, b);
}

static int gstrncmp(const char *a, const char *b, int size)
{
    if (!a && !b)
        return 0;
    if (!a || !b)
        return -1;

    return strncmp(a, b, size);
}

char *gstrdup(const char *str)
{
    if (!str)
        return NULL;

    return strdup(str);
}

char *gstrchr(char *str, int c)
{
    if (!str)
        return NULL;

    return strchr(str, c);
}

void gfree(void **p)
{
    free(*p);
    *p = NULL;
}

/**
 * \brief This actually creates a new list containing only one element...
 */
void gaddlist(char ***list, const char *entry)
{
    int i;

    if (*list) {
        for (i = 0; (*list)[i]; i++)
            free((*list)[i]);

        free(*list);
    }

    *list      = malloc(2 * sizeof(char **));
    (*list)[0] = gstrdup(entry);
    (*list)[1] = NULL;
}

/**
 * \brief This replaces a string starting with search by replace.
 * If not found, replace is appended.
 */
static void greplace(char ***list, const char *search, const char *replace)
{
    int i   = 0;
    int len = (search ? strlen(search) : 0);

    if (*list) {
        for (i = 0; (*list)[i]; i++) {
            if (search && (strncmp((*list)[i], search, len) == 0)) {
                free((*list)[i]);
                (*list)[i] = gstrdup(replace);
                return;
            }
        }

        *list = realloc(*list, (i + 2) * sizeof(char *));
    } else
        *list = malloc(2 * sizeof(char *));

    (*list)[i]     = gstrdup(replace);
    (*list)[i + 1] = NULL;
}

void guiInit(void)
{
    int i;

    mp_msg(MSGT_GPLAYER, MSGL_V, "GUI init.\n");

    memset(&guiInfo, 0, sizeof(guiInfo));
    guiInfo.Balance    = 50.0f;
    guiInfo.StreamType = -1;

    memset(&gtkEquChannels, 0, sizeof(gtkEquChannels));

#ifdef CONFIG_DXR3
    if (!gtkDXR3Device)
        gtkDXR3Device = strdup("/dev/em8300-0");
#endif

    if (stream_cache_size > 0) {
        gtkCacheOn   = 1;
        gtkCacheSize = stream_cache_size;
    } else if (stream_cache_size == 0)
        gtkCacheOn = 0;

    if (autosync && (autosync != gtkAutoSync)) {
        gtkAutoSyncOn = 1;
        gtkAutoSync   = autosync;
    }

#ifdef CONFIG_ASS
    gtkASS.enabled       = ass_enabled;
    gtkASS.use_margins   = ass_use_margins;
    gtkASS.top_margin    = ass_top_margin;
    gtkASS.bottom_margin = ass_bottom_margin;
#endif

    gtkInit();

    // initialize X
    wsXInit(mDisplay);

    // load skin

    skinDirInHome  = get_path("skins");
    skinMPlayerDir = MPLAYER_DATADIR "/skins";

    mp_dbg(MSGT_GPLAYER, MSGL_DBG2, "[interface] skin directory #1: %s\n", skinDirInHome);
    mp_dbg(MSGT_GPLAYER, MSGL_DBG2, "[interface] skin directory #2: %s\n", skinMPlayerDir);

    if (!skinName)
        skinName = strdup("default");

    i = skinRead(skinName);

    if (i == -1 && strcmp(skinName, "default") != 0) {
        mp_msg(MSGT_GPLAYER, MSGL_WARN, MSGTR_SKIN_SKINCFG_SelectedSkinNotFound, skinName);

        skinName = strdup("default");
        i = skinRead(skinName);
    }

    switch (i) {
    case -1:
        gmp_msg(MSGT_GPLAYER, MSGL_FATAL, MSGTR_SKIN_SKINCFG_SkinNotFound, skinName);
        guiExit(EXIT_ERROR);

    case -2:
        gmp_msg(MSGT_GPLAYER, MSGL_FATAL, MSGTR_SKIN_SKINCFG_SkinCfgError, skinName);
        guiExit(EXIT_ERROR);
    }

    // initialize windows

    mainDrawBuffer = malloc(guiApp.main.Bitmap.ImageSize);

    if (!mainDrawBuffer) {
        gmp_msg(MSGT_GPLAYER, MSGL_FATAL, MSGTR_NEMDB);
        guiExit(EXIT_ERROR);
    }

    if (gui_save_pos) {
        if (gui_main_pos_x != -3)
            guiApp.main.x = gui_main_pos_x;
        if (gui_main_pos_y != -3)
            guiApp.main.y = gui_main_pos_y;
        if (gui_sub_pos_x != -3)
            guiApp.sub.x = gui_sub_pos_x;
        if (gui_sub_pos_y != -3)
            guiApp.sub.y = gui_sub_pos_y;
    }

    if (WinID > 0) {
        guiApp.subWindow.Parent = WinID;
        guiApp.sub.x = 0;
        guiApp.sub.y = 0;
    }

    if (guiWinID >= 0)
        guiApp.mainWindow.Parent = guiWinID;

    wsCreateWindow(&guiApp.subWindow, guiApp.sub.x, guiApp.sub.y, guiApp.sub.width, guiApp.sub.height, wsNoBorder, wsShowMouseCursor | wsHandleMouseButton | wsHandleMouseMove, wsShowFrame | wsHideWindow, "MPlayer - Video");
    wsDestroyImage(&guiApp.subWindow);
    wsCreateImage(&guiApp.subWindow, guiApp.sub.Bitmap.Width, guiApp.sub.Bitmap.Height);
    wsXDNDMakeAwareness(&guiApp.subWindow);

    uiMenuInit();
    uiPlaybarInit();

// i=wsHideFrame|wsMaxSize|wsHideWindow;
// if ( guiApp.mainDecoration ) i=wsShowFrame|wsMaxSize|wsHideWindow;
    i = wsShowFrame | wsMaxSize | wsHideWindow;
    wsCreateWindow(&guiApp.mainWindow, guiApp.main.x, guiApp.main.y, guiApp.main.width, guiApp.main.height, wsNoBorder, wsShowMouseCursor | wsHandleMouseButton | wsHandleMouseMove, i, "MPlayer");
    wsSetShape(&guiApp.mainWindow, guiApp.main.Mask.Image);
    wsXDNDMakeAwareness(&guiApp.mainWindow);

    mp_dbg(MSGT_GPLAYER, MSGL_DBG2, "[interface] screen depth: %d\n", wsDepthOnScreen);
    mp_dbg(MSGT_GPLAYER, MSGL_DBG2, "[interface] mainWindow ID: 0x%x\n", (int)guiApp.mainWindow.WindowID);
    mp_dbg(MSGT_GPLAYER, MSGL_DBG2, "[interface] subWindow ID: 0x%x\n", (int)guiApp.subWindow.WindowID);

    guiApp.mainWindow.ReDraw       = (void *)uiMainDraw;
    guiApp.mainWindow.MouseHandler = uiMainMouseHandle;
    guiApp.mainWindow.KeyHandler   = uiMainKeyHandle;
    guiApp.mainWindow.DandDHandler = uiDandDHandler;

    guiApp.subWindow.ReDraw       = (void *)uiSubDraw;
    guiApp.subWindow.MouseHandler = uiSubMouseHandle;
    guiApp.subWindow.KeyHandler   = uiMainKeyHandle;
    guiApp.subWindow.DandDHandler = uiDandDHandler;

    wsSetBackgroundRGB(&guiApp.subWindow, guiApp.sub.R, guiApp.sub.G, guiApp.sub.B);
    wsClearWindow(guiApp.subWindow);

    if (guiApp.sub.Bitmap.Image)
        wsConvert(&guiApp.subWindow, guiApp.sub.Bitmap.Image);

    btnModify(evSetVolume, guiInfo.Volume);
    btnModify(evSetBalance, guiInfo.Balance);
    btnModify(evSetMoviePosition, guiInfo.Position);

    wsSetIcon(wsDisplay, guiApp.mainWindow.WindowID, &guiIcon);
    wsSetIcon(wsDisplay, guiApp.subWindow.WindowID, &guiIcon);

    if (!guiApp.mainDecoration)
        wsWindowDecoration(&guiApp.mainWindow, 0);

    wsVisibleWindow(&guiApp.mainWindow, wsShowWindow);

#if 0
    wsVisibleWindow(&guiApp.subWindow, wsShowWindow);
    {
        XEvent xev;

        do
            XNextEvent(wsDisplay, &xev);
        while (xev.type != MapNotify || xev.xmap.event != guiApp.subWindow.WindowID);

        guiApp.subWindow.Mapped = wsMapped;
    }

    if (!fullscreen)
        fullscreen = gtkLoadFullscreen;

    if (fullscreen) {
        uiFullScreen();
        btnModify(evFullScreen, btnPressed);
    }
#else
    if (!fullscreen)
        fullscreen = gtkLoadFullscreen;

    if (gtkShowVideoWindow) {
        wsVisibleWindow(&guiApp.subWindow, wsShowWindow);
        {
            XEvent xev;

            do
                XNextEvent(wsDisplay, &xev);
            while (xev.type != MapNotify || xev.xmap.event != guiApp.subWindow.WindowID);

            guiApp.subWindow.Mapped = wsMapped;
        }

        if (fullscreen) {
            uiFullScreen();
            btnModify(evFullScreen, btnPressed);
        }
    } else {
        if (fullscreen) {
            wsVisibleWindow(&guiApp.subWindow, wsShowWindow);
            {
                XEvent xev;

                do
                    XNextEvent(wsDisplay, &xev);
                while (xev.type != MapNotify || xev.xmap.event != guiApp.subWindow.WindowID);

                guiApp.subWindow.Mapped = wsMapped;
            }
            guiInfo.Playing = GUI_PAUSE; // because of !gtkShowVideoWindow...
            uiFullScreen();          // ...guiInfo.Playing is required
            wsVisibleWindow(&guiApp.subWindow, wsHideWindow);
            btnModify(evFullScreen, btnPressed);
        }
    }
#endif

    guiInfo.Playing = GUI_STOP;

    uiSubRender = 1;

    if (filename)
        uiSetFileName(NULL, filename, STREAMTYPE_FILE);

    if (plCurrent && !filename)
        uiSetFileName(plCurrent->path, plCurrent->name, STREAMTYPE_FILE);

    if (subdata)
        guiSetFilename(guiInfo.Subtitlename, subdata->filename);

    guiLoadFont();

    initialized = 1;
}

void guiDone(void)
{
    if (initialized) {
        uiMainRender = 0;

        if (gui_save_pos) {
            gui_main_pos_x = guiApp.mainWindow.X;
            gui_main_pos_y = guiApp.mainWindow.Y;
            gui_sub_pos_x  = guiApp.subWindow.X;
            gui_sub_pos_y  = guiApp.subWindow.Y;
        }

#ifdef CONFIG_ASS
        ass_enabled       = gtkASS.enabled;
        ass_use_margins   = gtkASS.use_margins;
        ass_top_margin    = gtkASS.top_margin;
        ass_bottom_margin = gtkASS.bottom_margin;
#endif

        cfg_write();
        wsXDone();
    }

    appFreeStruct();
    free(guiIcon.collection);

    if (gui_conf) {
        m_config_free(gui_conf);
        gui_conf = NULL;
    }

    mp_msg(MSGT_GPLAYER, MSGL_V, "GUI done.\n");
}

void guiExit(enum exit_reason how)
{
    exit_player_with_rc(how, how >= EXIT_ERROR);
}

void guiLoadFont(void)
{
#ifdef CONFIG_FREETYPE
    load_font_ft(vo_image_width, vo_image_height, &vo_font, font_name, osd_font_scale_factor);
#else
    if (vo_font) {
        int i;

        free(vo_font->name);
        free(vo_font->fpath);

        for (i = 0; i < 16; i++) {
            if (vo_font->pic_a[i]) {
                free(vo_font->pic_a[i]->bmp);
                free(vo_font->pic_a[i]->pal);
            }
        }

        for (i = 0; i < 16; i++) {
            if (vo_font->pic_b[i]) {
                free(vo_font->pic_b[i]->bmp);
                free(vo_font->pic_b[i]->pal);
            }
        }

        free(vo_font);
        vo_font = NULL;
    }

    if (font_name) {
        vo_font = read_font_desc(font_name, font_factor, 0);

        if (!vo_font)
            gmp_msg(MSGT_GPLAYER, MSGL_ERR, MSGTR_CantLoadFont, font_name);
    } else {
        font_name = gstrdup(get_path("font/font.desc"));
        vo_font   = read_font_desc(font_name, font_factor, 0);

        if (!vo_font) {
            gfree((void **)&font_name);
            font_name = gstrdup(MPLAYER_DATADIR "/font/font.desc");
            vo_font   = read_font_desc(font_name, font_factor, 0);
        }
    }
#endif
}

void guiLoadSubtitle(char *name)
{
    if (guiInfo.Playing == 0) {
        guiInfo.SubtitleChanged = 1; // what is this for? (mw)
        return;
    }

    if (subdata) {
        mp_msg(MSGT_GPLAYER, MSGL_INFO, MSGTR_DeletingSubtitles);

        sub_free(subdata);
        subdata = NULL;
        vo_sub  = NULL;

        if (vo_osd_list) {
            int len;
            mp_osd_obj_t *osd;

            osd = vo_osd_list;

            while (osd) {
                if (osd->type == OSDTYPE_SUBTITLE)
                    break;

                osd = osd->next;
            }

            if (osd && (osd->flags & OSDFLAG_VISIBLE)) {
                len = osd->stride * (osd->bbox.y2 - osd->bbox.y1);
                memset(osd->bitmap_buffer, 0, len);
                memset(osd->alpha_buffer, 0, len);
            }
        }
    }

    if (name) {
        mp_msg(MSGT_GPLAYER, MSGL_INFO, MSGTR_LoadingSubtitles, name);

        subdata = sub_read_file(name, guiInfo.FPS);

        if (!subdata)
            gmp_msg(MSGT_GPLAYER, MSGL_ERR, MSGTR_CantLoadSub, name);

        sub_name    = (malloc(2 * sizeof(char *))); // when mplayer will be restarted
        sub_name[0] = strdup(name);                 // sub_name[0] will be read
        sub_name[1] = NULL;
    }

    update_set_of_subtitles();
}

static void add_vf(char *str)
{
    void *p;

    if (vf_settings) {
        int i = 0;

        while (vf_settings[i].name) {
            if (!gstrcmp(vf_settings[i++].name, str)) {
                i = -1;
                break;
            }
        }

        if (i != -1) {
            p = realloc(vf_settings, (i + 2) * sizeof(m_obj_settings_t));

            if (!p)
                return;

            vf_settings = p;
            vf_settings[i].name     = strdup(str);
            vf_settings[i].attribs  = NULL;
            vf_settings[i + 1].name = NULL;
        }
    } else {
        vf_settings = malloc(2 * sizeof(m_obj_settings_t));
        vf_settings[0].name    = strdup(str);
        vf_settings[0].attribs = NULL;
        vf_settings[1].name    = NULL;
    }

    mp_msg(MSGT_GPLAYER, MSGL_INFO, MSGTR_AddingVideoFilter, str);
}

int guiGetEvent(int type, void *arg)
{
    mixer_t *mixer = NULL;

    stream_t *stream = arg;

#ifdef CONFIG_DVDREAD
    dvd_priv_t *dvdp = arg;
#endif

    if (guiInfo.mpcontext)
        mixer = mpctx_get_mixer(guiInfo.mpcontext);

    switch (type) {
    case guiXEvent:
        guiInfo.event_struct = arg;
        wsEvents(wsDisplay, arg);
        gtkEventHandling();
        break;

    case guiSetState:

        switch ((int)arg) {
        case GUI_STOP:
        case GUI_PLAY:
// if ( !gtkShowVideoWindow ) wsVisibleWindow( &guiApp.subWindow,wsHideWindow );
        case GUI_PAUSE:
            guiInfo.Playing = (int)arg;
            break;
        }

        uiState();
        break;

    case guiSetFileName:
        if (arg)
            guiSetFilename(guiInfo.Filename, arg);
        break;

    case guiSetAudioOnly:

        guiInfo.AudioOnly = (int)arg;

        if (guiInfo.AudioOnly) {
            guiInfo.MovieWindow = False;
            wsVisibleWindow(&guiApp.subWindow, wsHideWindow);
        } else
            wsVisibleWindow(&guiApp.subWindow, wsShowWindow);

        break;

    case guiSetContext:
        guiInfo.mpcontext = arg;
        break;

    case guiSetAfilter:
        guiInfo.afilter = arg;
        break;

    case guiSetVideoWindow:

        if (!guiApp.subWindow.isFullScreen) {
            wsResizeWindow(&guiApp.subWindow, vo_dwidth, vo_dheight);
            wsMoveWindow(&guiApp.subWindow, True, guiApp.sub.x, guiApp.sub.y);
        }

        guiInfo.MovieWidth  = vo_dwidth;
        guiInfo.MovieHeight = vo_dheight;

        if (guiWinID >= 0)
            wsMoveWindow(&guiApp.mainWindow, False, 0, vo_dheight);

        WinID = guiApp.subWindow.WindowID;
        break;

#ifdef CONFIG_DVDREAD
    case guiSetDVD:
        guiInfo.DVD.titles   = dvdp->vmg_file->tt_srpt->nr_of_srpts;
        guiInfo.DVD.chapters = dvdp->vmg_file->tt_srpt->title[dvd_title].nr_of_ptts;
        guiInfo.DVD.angles   = dvdp->vmg_file->tt_srpt->title[dvd_title].nr_of_angles;
        guiInfo.DVD.nr_of_audio_channels = dvdp->nr_of_channels;
        memcpy(guiInfo.DVD.audio_streams, dvdp->audio_streams, sizeof(dvdp->audio_streams));
        guiInfo.DVD.nr_of_subtitles = dvdp->nr_of_subtitles;
        memcpy(guiInfo.DVD.subtitles, dvdp->subtitles, sizeof(dvdp->subtitles));
        guiInfo.DVD.current_title   = dvd_title + 1;
        guiInfo.DVD.current_chapter = dvd_chapter + 1;
        guiInfo.DVD.current_angle   = dvd_angle + 1;
        guiInfo.Track = dvd_title + 1;
        break;
#endif

    case guiSetStream:

        guiInfo.StreamType = stream->type;

        switch (stream->type) {
#ifdef CONFIG_DVDREAD
        case STREAMTYPE_DVD:
            guiGetEvent(guiSetDVD, stream->priv);
            break;
#endif

#ifdef CONFIG_VCD
        case STREAMTYPE_VCD:
            guiInfo.VCDTracks = 0;
            stream_control(stream, STREAM_CTRL_GET_NUM_CHAPTERS, &guiInfo.VCDTracks);
            break;
#endif

        default:
            break;
        }

        break;

    case guiIEvent:

        mp_dbg(MSGT_GPLAYER, MSGL_DBG2, "[interface] guiIEvent: %d\n", (int)arg);

        switch ((int)arg) {
        case MP_CMD_QUIT:
            uiEventHandling(evExit, 0);
            break;

        case MP_CMD_VO_FULLSCREEN:
            uiEventHandling(evFullScreen, 0);
            break;
        }

        break;

    case guiReDraw:
        uiEventHandling(evRedraw, 0);
        break;

    case guiSetVolume:
        if (mixer) {
            float l, r;

            mixer_getvolume(mixer, &l, &r);
            guiInfo.Volume = (r > l ? r : l);

            if (r != l)
                guiInfo.Balance = ((r - l) + 100) * 0.5f;
            else
                guiInfo.Balance = 50.0f;

            btnModify(evSetVolume, guiInfo.Volume);
            btnModify(evSetBalance, guiInfo.Balance);
        }
        break;

    case guiSetValues:

        // video

        guiInfo.sh_video = arg;

        if (arg) {
            sh_video_t *sh = arg;
            guiInfo.FPS = sh->fps;
        }

        if (!guiInfo.MovieWindow)
            wsVisibleWindow(&guiApp.subWindow, wsHideWindow);

        if (guiInfo.StreamType == STREAMTYPE_STREAM)
            btnSet(evSetMoviePosition, btnDisabled);
        else
            btnSet(evSetMoviePosition, btnReleased);

        // audio

        if (mixer) {
            float l, r;

            mixer_getvolume(mixer, &l, &r);
            guiInfo.Volume = (r > l ? r : l);

            if (r != l)
                guiInfo.Balance = ((r - l) + 100) * 0.5f;
            else
                guiInfo.Balance = 50.0f;

            btnModify(evSetVolume, guiInfo.Volume);
            btnModify(evSetBalance, guiInfo.Balance);
        }

        if (gtkEnableAudioEqualizer) {
            equalizer_t eq;
            int i, j;

            for (i = 0; i < 6; i++) {
                for (j = 0; j < 10; j++) {
                    eq.channel = i;
                    eq.band    = j;
                    eq.gain    = gtkEquChannels[i][j];
                    gtkSet(gtkSetEqualizer, 0, &eq);
                }
            }
        }

        // subtitle

#ifdef CONFIG_DXR3
        if (video_driver_list && !gstrcmp(video_driver_list[0], "dxr3") && (((demuxer_t *)mpctx_get_demuxer(guiInfo.mpcontext))->file_format != DEMUXER_TYPE_MPEG_PS) && !gtkVfLAVC) {
            gtkMessageBox(GTK_MB_FATAL, MSGTR_NEEDLAVC);
            guiInfo.Playing = 0;
            return True;
        }
#endif

        break;

    case guiSetDefaults:

// if ( guiInfo.Playing == 1 && guiInfo.FilenameChanged )
        if (guiInfo.FilenameChanged) {
            audio_id  = -1;
            video_id  = -1;
            dvdsub_id = -1;
            vobsub_id = -1;
            stream_cache_size = -1;
            autosync  = 0;
            dvd_title = 0;
            force_fps = 0;
        }

        guiInfo.sh_video = NULL;
        wsPostRedisplay(&guiApp.subWindow);

        break;

    case guiPreparation:

        guiGetEvent(guiSetDefaults, NULL);

        switch (guiInfo.StreamType) {
        case STREAMTYPE_PLAYLIST:
            break;

#ifdef CONFIG_VCD
        case STREAMTYPE_VCD:
        {
            char tmp[512];

            sprintf(tmp, "vcd://%d", guiInfo.Track + 1);
            guiSetFilename(guiInfo.Filename, tmp);
        }
        break;
#endif

#ifdef CONFIG_DVDREAD
        case STREAMTYPE_DVD:
        {
            char tmp[512];

            sprintf(tmp, "dvd://%d", guiInfo.Title);
            guiSetFilename(guiInfo.Filename, tmp);
        }

            dvd_chapter = guiInfo.Chapter;
            dvd_angle   = guiInfo.Angle;

            break;
#endif
        }

// if ( guiInfo.StreamType != STREAMTYPE_PLAYLIST ) // Does not make problems anymore!
        {
            if (guiInfo.Filename)
                filename = gstrdup(guiInfo.Filename);
            else if (filename)
                guiSetFilename(guiInfo.Filename, filename);
        }

        // video opts

        if (!video_driver_list) {
            int i = 0;

            while (video_out_drivers[i++]) {
                if (video_out_drivers[i - 1]->control(VOCTRL_GUISUPPORT, NULL) == VO_TRUE) {
                    gaddlist(&video_driver_list, (char *)video_out_drivers[i - 1]->info->short_name);
                    break;
                }
            }
        }

        if (!video_driver_list && !video_driver_list[0]) {
            gmp_msg(MSGT_GPLAYER, MSGL_FATAL, MSGTR_IDFGCVD);
            guiExit(EXIT_ERROR);
        }

        {
            int i = 0;

            guiInfo.MovieWindow = True;

            while (video_out_drivers[i++]) {
                if (video_out_drivers[i - 1]->control(VOCTRL_GUISUPPORT, NULL) == VO_TRUE) {
                    if ((video_driver_list && !gstrcmp(video_driver_list[0], (char *)video_out_drivers[i - 1]->info->short_name)) && (video_out_drivers[i - 1]->control(VOCTRL_GUI_NOWINDOW, NULL) == VO_TRUE)) {
                        guiInfo.MovieWindow = False;
                        break;
                    }
                }
            }
        }

#ifdef CONFIG_DXR3
        if (video_driver_list && !gstrcmp(video_driver_list[0], "dxr3"))
            if (guiInfo.StreamType != STREAMTYPE_DVD && guiInfo.StreamType != STREAMTYPE_VCD)
                if (gtkVfLAVC)
                    add_vf("lavc");
#endif

        if (gtkVfPP)
            add_vf("pp");

        // audio opts

// if ( ao_plugin_cfg.plugin_list ) { free( ao_plugin_cfg.plugin_list ); ao_plugin_cfg.plugin_list=NULL; }
        if (gtkAONorm)
            greplace(&af_cfg.list, "volnorm", "volnorm");

        if (gtkEnableAudioEqualizer)
            greplace(&af_cfg.list, "equalizer", "equalizer");

        if (gtkAOExtraStereo) {
            char *name;

            name = malloc(12 + 20 + 1);
            snprintf(name, 12 + 20, "extrastereo=%f", gtkAOExtraStereoMul);
            name[12 + 20] = 0;
            greplace(&af_cfg.list, "extrastereo", name);
            free(name);
        }

#ifdef CONFIG_OSS_AUDIO
        if (audio_driver_list && !gstrncmp(audio_driver_list[0], "oss", 3)) {
            char *tmp;

            mixer_device  = gtkAOOSSMixer;
            mixer_channel = gtkAOOSSMixerChannel;

            if (gtkAOOSSDevice) {
                tmp = calloc(1, strlen(gtkAOOSSDevice) + 7);
                sprintf(tmp, "oss:%s", gtkAOOSSDevice);
            } else
                tmp = strdup("oss");

            gaddlist(&audio_driver_list, tmp);
            free(tmp);
        }
#endif

#ifdef CONFIG_ALSA
        if (audio_driver_list && !gstrncmp(audio_driver_list[0], "alsa", 4)) {
            char *tmp;

            mixer_device  = gtkAOALSAMixer;
            mixer_channel = gtkAOALSAMixerChannel;

            if (gtkAOALSADevice) {
                tmp = calloc(1, strlen(gtkAOALSADevice) + 14);
                sprintf(tmp, "alsa:device=%s", gtkAOALSADevice);
            } else
                tmp = strdup("alsa");

            gaddlist(&audio_driver_list, tmp);
            free(tmp);
        }
#endif

#ifdef CONFIG_SDL
        if (audio_driver_list && !gstrncmp(audio_driver_list[0], "sdl", 3)) {
            char *tmp;

            if (gtkAOSDLDriver) {
                tmp = calloc(1, strlen(gtkAOSDLDriver) + 10);
                sprintf(tmp, "sdl:%s", gtkAOSDLDriver);
            } else
                tmp = strdup("sdl");

            gaddlist(&audio_driver_list, tmp);
            free(tmp);
        }
#endif

#ifdef CONFIG_ESD
        if (audio_driver_list && !gstrncmp(audio_driver_list[0], "esd", 3)) {
            char *tmp;

            if (gtkAOESDDevice) {
                tmp = calloc(1, strlen(gtkAOESDDevice) + 10);
                sprintf(tmp, "esd:%s", gtkAOESDDevice);
            } else
                tmp = strdup("esd");

            gaddlist(&audio_driver_list, tmp);
            free(tmp);
        }
#endif

        // subtitle

// subdata->filename=gstrdup( guiInfo.Subtitlename );
        stream_dump_type = 0;

        if (gtkSubDumpMPSub)
            stream_dump_type = 4;

        if (gtkSubDumpSrt)
            stream_dump_type = 6;

        gtkSubDumpMPSub = gtkSubDumpSrt = 0;
        guiLoadFont();

        // misc

        if (gtkCacheOn)
            stream_cache_size = gtkCacheSize;

        if (gtkAutoSyncOn)
            autosync = gtkAutoSync;

        if (guiInfo.AudioFile)
            audio_stream = gstrdup(guiInfo.AudioFile);
        else if (guiInfo.FilenameChanged)
            gfree((void **)&audio_stream);

// audio_stream = NULL;

        guiInfo.DiskChanged     = 0;
        guiInfo.FilenameChanged = 0;
        guiInfo.NewPlay = 0;

#ifdef CONFIG_ASS
        ass_enabled       = gtkASS.enabled;
        ass_use_margins   = gtkASS.use_margins;
        ass_top_margin    = gtkASS.top_margin;
        ass_bottom_margin = gtkASS.bottom_margin;
#endif

        break;
    }

    return False;
}

void guiEventHandling(void)
{
    if (!guiInfo.Playing || !guiInfo.MovieWindow)
        wsHandleEvents();

    gtkEventHandling();
}

// ---
#if defined(MP_DEBUG) && 0
void list(void)
{
    plItem *next = plList;

    printf("--- list ---\n");

    while (next || next->next) {
        printf("item: %s/%s\n", next->path, next->name);

        if (next->next)
            next = next->next;
        else
            break;
    }

    printf("--- end of list ---\n");
}
#else
#define list();
#endif

void *gtkSet(int cmd, float fparam, void *vparam)
{
    equalizer_t *eq   = (equalizer_t *)vparam;
    plItem *item      = (plItem *)vparam;
    urlItem *url_item = (urlItem *)vparam;
    int is_added      = True;

    switch (cmd) {
    // handle playlist

    // add item to playlist
    case gtkAddPlItem:

        if (plList) {
            plItem *next = plList;

            while (next->next)
// {
// printf( "%s\n",next->name );
                next = next->next;
// }

            next->next = item;
            item->prev = next;
            item->next = NULL;
        } else {
            item->prev = item->next = NULL;
            plCurrent  = plList = item;
        }

        list();

        return NULL;

    // add item into playlist after current
    case gtkInsertPlItem:
        if (plCurrent) {
            plItem *curr = plCurrent;
            item->next = curr->next;

            if (item->next)
                item->next->prev = item;

            item->prev = curr;
            curr->next = item;
            plCurrent  = plCurrent->next;

            return plCurrent;
        } else
            return gtkSet(gtkAddPlItem, 0, (void *)item);
        return NULL;   // NOTE TO MYSELF: remove this

    // get next item from playlist
    case gtkGetNextPlItem:
        if (plCurrent && plCurrent->next) {
            plCurrent = plCurrent->next;
// if (!plCurrent && plList)
// {
// plItem *next = plList;
//
// while (next->next)
// {
// if (!next->next) break;
// next = next->next;
// }
//
// plCurrent = next;
// }
            return plCurrent;
        }

        return NULL;

    // get previous item from playlist
    case gtkGetPrevPlItem:
        if (plCurrent && plCurrent->prev) {
            plCurrent = plCurrent->prev;
// if ( !plCurrent && plList ) plCurrent=plList;
            return plCurrent;
        }

        return NULL;

    // set current item
    case gtkSetCurrPlItem:
        plCurrent = item;
        return plCurrent;

    // get current item
    case gtkGetCurrPlItem:
        return plCurrent;

    // delete current item
    case gtkDelCurrPlItem:
    {
        plItem *curr = plCurrent;

        if (!curr)
            return NULL;

        if (curr->prev)
            curr->prev->next = curr->next;
        if (curr->next)
            curr->next->prev = curr->prev;
        if (curr == plList)
            plList = curr->next;

        plCurrent = curr->next;

        // free it
        free(curr->path);
        free(curr->name);
        free(curr);
    }

        uiCurr();   // instead of using uiNext && uiPrev

        return plCurrent;

    // delete list
    case gtkDelPl:
    {
        plItem *curr = plList;
        plItem *next;

        if (!plList)
            return NULL;

        if (!curr->next) {
            free(curr->path);
            free(curr->name);
            free(curr);
        } else {
            while (curr->next) {
                next = curr->next;
                free(curr->path);
                free(curr->name);
                free(curr);
                curr = next;
            }
        }

        plList    = NULL;
        plCurrent = NULL;
    }

        return NULL;

    // handle url
    case gtkAddURLItem:
        if (URLList) {
            urlItem *next_url = URLList;
            is_added = False;

            while (next_url->next) {
                if (!gstrcmp(next_url->url, url_item->url)) {
                    is_added = True;
                    break;
                }

                next_url = next_url->next;
            }

            if (!is_added && gstrcmp(next_url->url, url_item->url))
                next_url->next = url_item;
        } else {
            url_item->next = NULL;
            URLList = url_item;
        }

        return NULL;

        // subtitle

#ifndef CONFIG_FREETYPE
    case gtkSetFontFactor:
        font_factor = fparam;
        guiLoadFont();
        return NULL;
#else
    case gtkSetFontOutLine:
        subtitle_font_thickness = (8.0f / 100.0f) * fparam;
        guiLoadFont();
        return NULL;

    case gtkSetFontBlur:
        subtitle_font_radius = (8.0f / 100.0f) * fparam;
        guiLoadFont();
        return NULL;

    case gtkSetFontTextScale:
        text_font_scale_factor = fparam;
        guiLoadFont();
        return NULL;

    case gtkSetFontOSDScale:
        osd_font_scale_factor = fparam;
        guiLoadFont();
        return NULL;

    case gtkSetFontEncoding:
        gfree((void **)&subtitle_font_encoding);
        subtitle_font_encoding = gstrdup((char *)vparam);
        guiLoadFont();
        return NULL;

    case gtkSetFontAutoScale:
        subtitle_autoscale = (int)fparam;
        guiLoadFont();
        return NULL;
#endif

#ifdef CONFIG_ICONV
    case gtkSetSubEncoding:
        gfree((void **)&sub_cp);
        sub_cp = gstrdup((char *)vparam);
        break;
#endif

    // misc

    case gtkClearStruct:

        if ((unsigned int)vparam & guiFilenames) {
            gfree((void **)&guiInfo.Filename);
            gfree((void **)&guiInfo.Subtitlename);
            gfree((void **)&guiInfo.AudioFile);
            gtkSet(gtkDelPl, 0, NULL);
        }

#ifdef CONFIG_DVDREAD
        if ((unsigned int)vparam & guiDVD)
            memset(&guiInfo.DVD, 0, sizeof(guiDVDStruct));
#endif

#ifdef CONFIG_VCD
        if ((unsigned int)vparam & guiVCD)
            guiInfo.VCDTracks = 0;
#endif

        return NULL;

    case gtkSetExtraStereo:
        gtkAOExtraStereoMul = fparam;
        if (guiInfo.afilter)
            af_control_any_rev(guiInfo.afilter, AF_CONTROL_ES_MUL | AF_CONTROL_SET, &gtkAOExtraStereoMul);
        return NULL;

    case gtkSetPanscan:
    {
        mp_cmd_t *mp_cmd;

        mp_cmd       = calloc(1, sizeof(*mp_cmd));
        mp_cmd->id   = MP_CMD_PANSCAN;
        mp_cmd->name = strdup("panscan");
        mp_cmd->args[0].v.f = fparam;
        mp_cmd->args[1].v.i = 1;
        mp_input_queue_cmd(mp_cmd);
    }

        return NULL;

    case gtkSetAutoq:
        auto_quality = (int)fparam;
        return NULL;

    // set equalizers

    case gtkSetContrast:
        if (guiInfo.sh_video)
            set_video_colors(guiInfo.sh_video, "contrast", (int)fparam);
        return NULL;

    case gtkSetBrightness:
        if (guiInfo.sh_video)
            set_video_colors(guiInfo.sh_video, "brightness", (int)fparam);
        return NULL;

    case gtkSetHue:
        if (guiInfo.sh_video)
            set_video_colors(guiInfo.sh_video, "hue", (int)fparam);
        return NULL;

    case gtkSetSaturation:
        if (guiInfo.sh_video)
            set_video_colors(guiInfo.sh_video, "saturation", (int)fparam);
        return NULL;

    case gtkSetEqualizer:
    {
        af_control_ext_t tmp;

        if (eq) {
            gtkEquChannels[eq->channel][eq->band] = eq->gain;
            tmp.ch  = eq->channel;
            tmp.arg = gtkEquChannels[eq->channel];

            if (guiInfo.afilter)
                af_control_any_rev(guiInfo.afilter, AF_CONTROL_EQUALIZER_GAIN | AF_CONTROL_SET, &tmp);
        } else {
            int i;

            memset(gtkEquChannels, 0, sizeof(gtkEquChannels));

            if (guiInfo.afilter) {
                for (i = 0; i < 6; i++) {
                    tmp.ch  = i;
                    tmp.arg = gtkEquChannels[i];
                    af_control_any_rev(guiInfo.afilter, AF_CONTROL_EQUALIZER_GAIN | AF_CONTROL_SET, &tmp);
                }
            }
        }

        return NULL;
    }
    }

    return NULL;
}

// This function adds/inserts one file into the gui playlist.
static int import_file_into_gui(char *temp, int insert)
{
    char *filename, *pathname;
    plItem *item;

    filename = strdup(mp_basename(temp));
    pathname = strdup(temp);

    if (strlen(pathname) - strlen(filename) > 0)
        pathname[strlen(pathname) - strlen(filename) - 1] = 0;                                            // we have some path, so remove / at end
    else
        pathname[strlen(pathname) - strlen(filename)] = 0;

    mp_dbg(MSGT_GPLAYER, MSGL_DBG2, "[interface] playtree, add: %s/%s\n", pathname, filename);

    item = calloc(1, sizeof(plItem));

    if (!item)
        return 0;

    item->name = filename;
    item->path = pathname;

    if (insert)
        gtkSet(gtkInsertPlItem, 0, (void *)item);            // inserts the item after current, and makes current=item
    else
        gtkSet(gtkAddPlItem, 0, (void *)item);

    return 1;
}

// This function imports the initial playtree (based on cmd-line files)
// into the gui playlist by either:
// - overwriting gui pl (enqueue=0)
// - appending it to gui pl (enqueue=1)
int import_initial_playtree_into_gui(play_tree_t *my_playtree, m_config_t *config, int enqueue)
{
    play_tree_iter_t *my_pt_iter = NULL;
    int result = 0;

    if (!enqueue)
        gtkSet(gtkDelPl, 0, 0);             // delete playlist before "appending"

    if ((my_pt_iter = pt_iter_create(&my_playtree, config))) {
        while ((filename = pt_iter_get_next_file(my_pt_iter)) != NULL)
            // add it to end of list
            if (import_file_into_gui(filename, 0))
                result = 1;
    }

    uiCurr();   // update filename
    uiGotoTheNext = 1;

    if (!enqueue)
        filename = guiInfo.Filename;             // Backward compatibility; if file is specified on commandline,
                                                 // gmplayer does directly start in Play-Mode.
    else
        filename = NULL;

    return result;
}

// This function imports and inserts an playtree, that is created "on the fly",
// for example by parsing some MOV-Reference-File; or by loading an playlist
// with "File Open".
// The file which contained the playlist is thereby replaced with it's contents.
int import_playtree_playlist_into_gui(play_tree_t *my_playtree, m_config_t *config)
{
    play_tree_iter_t *my_pt_iter = NULL;
    int result = 0;
    plItem *save;

    save = (plItem *)gtkSet(gtkGetCurrPlItem, 0, 0);    // save current item

    if ((my_pt_iter = pt_iter_create(&my_playtree, config))) {
        while ((filename = pt_iter_get_next_file(my_pt_iter)) != NULL)
            // insert it into the list and set plCurrent=new item
            if (import_file_into_gui(filename, 1))
                result = 1;

        pt_iter_destroy(&my_pt_iter);
    }

    if (save)
        gtkSet(gtkSetCurrPlItem, 0, (void *)save);
    else
        gtkSet(gtkSetCurrPlItem, 0, (void *)plList);     // go to head, if plList was empty before

    if (save && result)
        gtkSet(gtkDelCurrPlItem, 0, 0);

    uiCurr();   // update filename
    filename = NULL;

    return result;
}

// NOTE TO MYSELF: This function is nonsense.
//                 MPlayer should pass messages to the GUI
//                 which must decide then which message has
//                 to be shown (MSGL_FATAL, for example).
//                 But with this function it is at least
//                 possible to show GUI's very critical or
//                 abort messages.
void gmp_msg(int mod, int lev, const char *format, ...)
{
    char msg[512];
    va_list va;

    va_start(va, format);
    vsnprintf(msg, sizeof(msg), format, va);
    va_end(va);

    mp_msg(mod, lev, msg);

    if (mp_msg_test(mod, lev))
        gtkMessageBox(GTK_MB_FATAL, msg);
}
