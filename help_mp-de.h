// Transated by: Johannes Feigl, johannes.feigl@mcse.at


// ========================= MPlayer help ===========================

#ifdef HELP_MP_DEFINE_STATIC
static char* banner_text=
"\n\n"
"MPlayer " VERSION "(C) 2000-2001 Arpad Gereoffy (siehe DOCS/AUTHORS)\n"
"\n";

static char help_text[]=
#ifdef HAVE_NEW_GUI
"Verwendung:   mplayer [-gui] [optionen] [verzeichnis/]dateiname\n"
#else
"Verwendung:   mplayer [optionen] [verzeichnis/]dateiname\n"
#endif
"\n"
"Optionen:\n"
" -vo <drv[:dev]> Videoausgabetreiber & -Ger�t (siehe '-vo help' f�r eine Liste)\n"
" -ao <drv[:dev]> Audioausgabetreiber & -Ger�t (siehe '-ao help' f�r eine Liste)\n"
" -vcd <tracknr>  Spiele VCD (Video CD) Titel anstelle eines Dateinames\n"
#ifdef HAVE_LIBCSS
" -dvdauth <dev>  Benutze DVD Ger�t f�r die Authentifizierung (f�r verschl. DVD's)\n"
#endif
#ifdef USE_DVDREAD
" -dvd <titlenr>  Spiele DVD Titel/Track von Ger�t anstelle eines Dateinames\n"
#endif
" -ss <timepos>   Starte abspielen ab Position (Sekunden oder hh:mm:ss)\n"
" -nosound        Spiele keinen Sound\n"
#ifdef USE_FAKE_MONO
" -stereo <mode>  Auswahl der MPEG1-Stereoausgabe (0:stereo 1:links 2:rechts)\n"
#endif
" -fs -vm -zoom   Vollbild Optionen (Vollbild, Videomode, Softwareskalierung)\n"
" -x <x> -y <y>   Skaliere Bild auf <x> * <y> [wenn vo-Treiber mitmacht]\n"
" -sub <file>     Benutze Untertitledatei (siehe auch -subfps, -subdelay)\n"
" -vid x -aid y   Spiele Videostream (x) und Audiostream (y)\n"
" -fps x -srate y Benutze Videoframerate (x fps) und Audiosamplingrate (y Hz)\n"
" -pp <quality>   Aktiviere Nachbearbeitungsfilter (0-4 bei DivX, 0-63 bei MPEG)\n"
" -nobps          Benutze alternative A-V sync Methode f�r AVI's (k�nnte helfen!)\n"
" -framedrop      Benutze frame-dropping (f�r langsame Rechner)\n"
"\n"
"Tasten:\n"
" <- oder ->      Springe zehn Sekunden vor/zur�ck\n"
" rauf / runter   Springe eine Minute vor/zur�ck\n"
" p oder LEER     PAUSE (beliebige Taste zum Fortsetzen)\n"
" q oder ESC      Abspielen stoppen und Programm beenden\n"
" + oder -        Audioverz�gerung um +/- 0.1 Sekunde ver�ndern\n"
" o               OSD Mode:  Aus / Suchleiste / Suchleiste + Zeit\n"
" * oder /        Lautst�rke verstellen ('m' f�r Auswahl Master/Wave)\n"
" z oder x        Untertitelverz�gerung um +/- 0.1 Sekunde ver�ndern\n"
"\n"
" * * * IN DER MANPAGE STEHEN WEITERE KEYS UND OPTIONEN ! * * *\n"
"\n";
#endif

// ========================= MPlayer Ausgaben ===========================

// mplayer.c: 

#define MSGTR_Exiting "\nBeende... (%s)\n"
#define MSGTR_Exit_frames "Angeforderte Anzahl an Frames gespielt"
#define MSGTR_Exit_quit "Ende"
#define MSGTR_Exit_eof "Ende der Datei"
#define MSGTR_Exit_error "Schwerer Fehler"
#define MSGTR_IntBySignal "\nMPlayer wurde durch Signal %d von Modul %s beendet\n"
#define MSGTR_NoHomeDir "Kann Homeverzeichnis nicht finden\n"
#define MSGTR_GetpathProblem "get_path(\"config\") Problem\n"
#define MSGTR_CreatingCfgFile "Erstelle Konfigurationsdatei: %s\n"
#define MSGTR_InvalidVOdriver "Ung�ltiger Videoausgabetreibername: %s\n'-vo help' zeigt eine Liste aller.\n"
#define MSGTR_InvalidAOdriver "Ung�ltiger Audioausgabetreibername: %s\n'-ao help' zeigt eine Liste aller.\n"
#define MSGTR_CopyCodecsConf "(kopiere/linke etc/codecs.conf nach ~/.mplayer/codecs.conf)\n"
#define MSGTR_CantLoadFont "Kann Schriftdatei %s nicht laden\n"
#define MSGTR_CantLoadSub "Kann Untertitel nicht laden: %s\n"
#define MSGTR_ErrorDVDkey "Fehler beim Bearbeiten des DVD-Schl�ssels..\n"
#define MSGTR_CmdlineDVDkey "Der DVD-Schl�ssel der Kommandozeile wurde f�r das Descrambeln gespeichert.\n"
#define MSGTR_DVDauthOk "DVD Authentifizierungssequenz scheint OK zu sein.\n"
#define MSGTR_DumpSelectedSteramMissing "dump: FATAL: Ausgew�hlter Stream fehlt!\n"
#define MSGTR_CantOpenDumpfile "Kann dump-Datei nicht �ffnen!!!\n"
#define MSGTR_CoreDumped "core dumped :)\n"
#define MSGTR_FPSnotspecified "FPS ist im Header nicht angegeben (oder ung�ltig)! Benutze -fps Option!\n"
#define MSGTR_NoVideoStream "Sorry, kein Videostream... ist unabspielbar\n"
#define MSGTR_TryForceAudioFmt "Erzwinge Audiocodecgruppe %d ...\n"
#define MSGTR_CantFindAfmtFallback "Kann keinen Audiocodec f�r gew�nschte Gruppe finden, verwende anderen.\n"
#define MSGTR_CantFindAudioCodec "Kann Codec f�r Audioformat 0x%X nicht finden!\n"
#define MSGTR_TryUpgradeCodecsConfOrRTFM "*** Versuche %s mit etc/codecs.conf zu erneuern\n*** Sollte es weiterhin nicht gehen, dann lese DOCS/CODECS!\n"
#define MSGTR_CouldntInitAudioCodec "Kann Audiocodec nicht finden! -> Kein Ton\n"
#define MSGTR_TryForceVideoFmt "Erzwinge Videocodecgruppe %d ...\n"
#define MSGTR_CantFindVfmtFallback "Kann keinen Videocodec f�r gew�nschte Gruppe finden, verwende anderen.\n"
#define MSGTR_CantFindVideoCodec "Kann Videocodec f�r Format 0x%X nicht finden!\n"
#define MSGTR_VOincompCodec "Sorry, der ausgew�hlte Videoausgabetreiber ist nicht kompatibel mit diesem Codec.\n"
#define MSGTR_CouldntInitVideoCodec "FATAL: Kann Videocodec nicht initialisieren :(\n"
#define MSGTR_EncodeFileExists "Datei existiert: %s (�berschreibe nicht deine sch�nsten AVI's!)\n"
#define MSGTR_CantCreateEncodeFile "Kann Datei zum Encoden nicht �ffnen\n"
#define MSGTR_CannotInitVO "FATAL: Kann Videoausgabetreiber nicht initialisieren!\n"
#define MSGTR_CannotInitAO "Kann Audiotreiber/Soundkarte nicht initialisieren -> Kein Ton\n"
#define MSGTR_StartPlaying "Starte Wiedergabe...\n"
#define MSGTR_SystemTooSlow "\n************************************************************************"\
			    "\n** Dein System ist zu langsam. Versuche die -framedrop Option oder RTFM! **"\
			    "\n************************************************************************\n"

#define MSGTR_NoGui "MPlayer wurde OHNE GUI-Unterst�tzung kompiliert!\n"
#define MSGTR_GuiNeedsX "MPlayer GUI erfordert X11!\n"
#define MSGTR_Playing "Spiele %s\n"
#define MSGTR_NoSound "Audio: kein Ton!!!\n"
#define MSGTR_FPSforced "FPS fixiert auf %5.3f  (ftime: %5.3f)\n"

// open.c, stream.c:
#define MSGTR_CdDevNotfound "CD-ROM Ger�t '%s' nicht gefunden!\n"
#define MSGTR_ErrTrackSelect "Fehler beim Ausw�hlen des VCD Tracks!"
#define MSGTR_ReadSTDIN "Lese von stdin...\n"
#define MSGTR_UnableOpenURL "Kann URL nicht �ffnen: %s\n"
#define MSGTR_ConnToServer "Verbunden mit Server: %s\n"
#define MSGTR_FileNotFound "Datei nicht gefunden: '%s'\n"

#define MSGTR_CantOpenDVD "Kann DVD Ger�t nicht �ffnen: %s\n"
#define MSGTR_DVDwait "Lese Disk-Struktur, bitte warten...\n"
#define MSGTR_DVDnumTitles "Es sind %d Titel auf dieser DVD.\n"
#define MSGTR_DVDinvalidTitle "Ung�ltige DVD Titelnummer: %d\n"
#define MSGTR_DVDnumChapters "Es sind %d Kapitel auf diesem DVD Titel.\n"
#define MSGTR_DVDinvalidChapter "Ung�ltige DVD Kapitelnummer: %d\n"
#define MSGTR_DVDnumAngles "Es sind %d Sequenzen auf diesem DVD Titel.\n"
#define MSGTR_DVDinvalidAngle "Ung�ltige DVD Sequenznummer: %d\n"
#define MSGTR_DVDnoIFO "Kann die IFO-Datei f�r den DVD-Titel nicht �ffnen %d.\n"
#define MSGTR_DVDnoVOBs "Kann Titel-VOBS (VTS_%02d_1.VOB) nicht �ffnen.\n"
#define MSGTR_DVDopenOk "DVD erfolgreich ge�ffnet!\n"

// demuxer.c, demux_*.c:
#define MSGTR_AudioStreamRedefined "Warnung! Audiostreamheader %d redefiniert!\n"
#define MSGTR_VideoStreamRedefined "Warnung! Videostreamheader %d redefiniert\n"
#define MSGTR_TooManyAudioInBuffer "\nDEMUXER: Zu viele (%d in %d bytes) Audiopakete im Puffer!\n"
#define MSGTR_TooManyVideoInBuffer "\nDEMUXER: Zu viele (%d in %d bytes) Videopakete im Puffer!\n"
#define MSGTR_MaybeNI "Vielleicht spielst du einen non-interleaved Stream/Datei oder der Codec funktioniert nicht.\n"
#define MSGTR_DetectedAVIfile "AVI Dateiformat erkannt!\n"
#define MSGTR_DetectedASFfile "ASF Dateiformat erkannt!\n"
#define MSGTR_DetectedMPEGPESfile "MPEG-PES Dateiformat erkannt!\n"
#define MSGTR_DetectedMPEGPSfile "MPEG-PS Dateiformat erkannt!\n"
#define MSGTR_DetectedMPEGESfile "MPEG-ES Dateiformat erkannt!\n"
#define MSGTR_DetectedQTMOVfile "QuickTime/MOV Dateiformat erkannt!\n"
#define MSGTR_MissingMpegVideo "Vermisse MPEG Videostream!? Kontaktiere den Author, das k�nnte ein Bug sein :(\n"
#define MSGTR_InvalidMPEGES "Ung�ltiger MPEG-ES Stream??? Kontaktiere den Author, das k�nnte ein Bug sein :(\n"
#define MSGTR_FormatNotRecognized "=========== Sorry, das Dateiformat/Codec wird nicht unterst�tzt ==============\n"\
				  "============== Sollte dies ein AVI, ASF oder MPEG Stream sein, ===============\n"\
				  "================== dann kontaktiere bitte den Author =========================\n"
#define MSGTR_MissingVideoStream "kann keinen Videostream finden!\n"
#define MSGTR_MissingAudioStream "kann keinen Audiostream finden...  -> kein Ton\n"
#define MSGTR_MissingVideoStreamBug "Vermisse Videostream!? Kontaktiere den Author, m�glicherweise ein Bug :(\n"

#define MSGTR_DoesntContainSelectedStream "Demux: Datei enth�lt den gew�hlen Audio- oder Videostream nicht\n"

#define MSGTR_NI_Forced "Erzwungen"
#define MSGTR_NI_Detected "Erkannt"
#define MSGTR_NI_Message "%s NON-INTERLEAVED AVI Dateiformat!\n"

#define MSGTR_UsingNINI "Verwende NON-INTERLEAVED defektes AVI Dateiformat!\n"
#define MSGTR_CouldntDetFNo "Konnte die Anzahl der Frames (f�r absulute Suche) nicht finden  \n"
#define MSGTR_CantSeekRawAVI "Kann kein RAW .AVI-Streams durchsuchen! (Index erforderlich, versuche es mit der -idx Option!)  \n"
#define MSGTR_CantSeekFile "Kann diese Datei nicht durchsuchen!  \n"

#define MSGTR_EncryptedVOB "Verschl�sselte VOB-Datei (wurde ohne libcss Unterst�tzung kompiliert)! Lese DOCS\n"
#define MSGTR_EncryptedVOBauth "Verschl�sselter Stream, jedoch wurde die Authentifizierung nicht von dir gefordert!!\n"

#define MSGTR_MOVcomprhdr "MOV: Komprimierte Header werden (zur Zeit) nicht unterst�tzt!\n"
#define MSGTR_MOVvariableFourCC "MOV: Warnung! Variable FOURCC erkannt!?\n"
#define MSGTR_MOVtooManyTrk "MOV: Warnung! Zu viele Tracks!"
#define MSGTR_MOVnotyetsupp "\n******** Quicktime MOV Format wird zu Zeit nicht unterst�tzt!!!!!!! *********\n"

// dec_video.c & dec_audio.c:
#define MSGTR_CantOpenCodec "kann Codec nicht �ffnen\n"
#define MSGTR_CantCloseCodec "kann Codec nicht schlie�en\n"

#define MSGTR_MissingDLLcodec "FEHLER: Kann erforderlichen DirectShow Codec nicht finden: %s\n"
#define MSGTR_ACMiniterror "Kann Win32/ACM AUDIO Codec nicht finden (fehlende DLL-Datei?)\n"
#define MSGTR_MissingLAVCcodec "Kann Codec '%s' von libavcodec nicht finden...\n"

#define MSGTR_NoDShowSupport "MPlayer wurde OHNE DirectShow Unterst�tzung kompiliert!\n"
#define MSGTR_NoWfvSupport "Unterst�tzung f�r Win32 Codecs ausgeschaltet oder nicht verf�gbar auf nicht-x86 Plattformen!\n"
#define MSGTR_NoDivx4Support "MPlayer wurde OHNE DivX4Linux (libdivxdecore.so) Unterst�tzung kompiliert!\n"
#define MSGTR_NoLAVCsupport "MPlayer wurde OHNE ffmpeg/libavcodecUnterst�tzung kompiliert!\n"
#define MSGTR_NoACMSupport "Win32/ACM Audiocodecs ausgeschaltet oder nicht verf�gbar auf nicht-x86 Plattformen -> erzwinge -nosound :(\n"
#define MSGTR_NoDShowAudio "MPlayer wurde ohne DirectShow Unterst�tzung kompiliert -> erzwinge -nosound :(\n"
#define MSGTR_NoOggVorbis "OggVorbis Audiocodec ausgeschaltet -> erzwinge -nosound :(\n"

#define MSGTR_MpegPPhint "WARNUNG! Du hast Bild-Postprocessing erbeten f�r ein MPEG 1/2 Video,\n" \
			 "         aber hast MPlayer ohne MPEG 1/2 Postprocessing-Support kompiliert!\n" \
			 "         #define MPEG12_POSTPROC in config.h und kompiliere libmpeg2 neu!\n"
#define MSGTR_MpegNoSequHdr "MPEG: FATAL: Ende der Datei w�hrend der Suche f�r Sequenzheader\n"
#define MSGTR_CannotReadMpegSequHdr "FATAL: Kann Sequenzheader nicht lesen!\n"
#define MSGTR_CannotReadMpegSequHdrEx "FATAL: Kann Sequenzheader-Erweiterung nicht lesen!\n"
#define MSGTR_BadMpegSequHdr "MPEG: Schlechte Sequenzheader!\n"
#define MSGTR_BadMpegSequHdrEx "MPEG: Schlechte Sequenzheader-Erweiterung!\n"

#define MSGTR_ShMemAllocFail "Kann keine gemeinsamen Speicher zuweisen\n"
#define MSGTR_CantAllocAudioBuf "Kann keinen Audioausgabe-Puffer zuweisen\n"
#define MSGTR_NoMemForDecodedImage "nicht genug Speicher f�r den Puffer der dekodierten Bilder (%ld Bytes)\n"

#define MSGTR_AC3notvalid "AC3 Stream ung�ltig.\n"
#define MSGTR_AC3only48k "Nur 48000 Hz Streams sind unterst�tzt.\n"
#define MSGTR_UnknownAudio "Unbekanntes/fehlendes Audioformat -> kein Ton\n"

// LIRC:
#define MSGTR_SettingUpLIRC "LIRC-Unterst�tzung wird eingerichtet...\n"
#define MSGTR_LIRCdisabled "Es wird nicht m�glich, deine Fernbedienung zu benutzen\n"
#define MSGTR_LIRCopenfailed "�ffnen der LIRC-Unterst�tzung fehlgeschlagen!\n"
#define MSGTR_LIRCsocketerr "Etwas ist falsch mit dem LIRC Socket: %s\n"
#define MSGTR_LIRCcfgerr "Lesen der LIRC Konfigurationsdatei %s fehlgeschlagen!\n"


// ====================== GUI messages/buttons ========================

#ifdef HAVE_NEW_GUI

// --- labels ---
#define MSGTR_About "�ber ..."
#define MSGTR_FileSelect "W�hle Datei ..."
#define MSGTR_MessageBox "Message-Box"
#define MSGTR_PlayList "Playliste"
#define MSGTR_SkinBrowser "Skin Browser"

// --- buttons ---
#define MSGTR_Ok "Ok"
#define MSGTR_Cancel "Abbrechen"
#define MSGTR_Add "Hinzuf�gen"
#define MSGTR_Remove "Entfernen"

// --- error messages ---
#define MSGTR_NEMDB "Sorry, nicht genug Speicher f�r den Zeichen-Puffer."
#define MSGTR_NEMFMR "Sorry, nicht genug Speicher f�r Men�-Rendering."
#define MSGTR_NEMFMM "Sorry, nicht genug Speicher f�r die Hauptfenster-Maske."

// --- skin loader error messages
#define MSGTR_SKIN_ERRORMESSAGE "[Skin] Fehler in Skin-Konfigurationsdatei in Zeile %d: %s" 
#define MSGTR_SKIN_WARNING1 "[Skin] Warnung in Skin-Konfigurationsdatei in Zeile %d: Widget gefunden, aber davor wurde \"section\" nicht gefunden ( %s )"
#define MSGTR_SKIN_WARNING2 "[Skin] Warnung in Skin-Konfigurationsdatei in Zeile %d: Widget gefunden, aber davor wurde \"subsection\" nicht gefunden (%s)"
#define MSGTR_SKIN_BITMAP_16bit  "Bitmaps mit 16 Bits oder wenige sind nicht unterst�tzt ( %s ).\n"
#define MSGTR_SKIN_BITMAP_FileNotFound  "Datei nicht gefunden ( %s )\n"
#define MSGTR_SKIN_BITMAP_BMPReadError "BMP Lesefehler ( %s )\n"
#define MSGTR_SKIN_BITMAP_TGAReadError "TGA Lesefehler ( %s )\n"
#define MSGTR_SKIN_BITMAP_PNGReadError "PNG Lesefehler ( %s )\n"
#define MSGTR_SKIN_BITMAP_RLENotSupported "RLE gepackte TGA sind nicht unterst�tzt ( %s )\n"
#define MSGTR_SKIN_BITMAP_UnknownFileType "unbekanntes Dateiformat ( %s )\n"
#define MSGTR_SKIN_BITMAP_ConvertError "Konvertierungsfehler von 24 Bit auf 32 Bit ( %s )\n"
#define MSGTR_SKIN_BITMAP_UnknownMessage "unbekannte Nachricht: %s\n"
#define MSGTR_SKIN_FONT_NotEnoughtMemory "nicht genug Speicher\n"
#define MSGTR_SKIN_FONT_TooManyFontsDeclared "zu viele Schriften eingestellt\n"
#define MSGTR_SKIN_FONT_FontFileNotFound "Schriftdatei nicht gefunden\n"
#define MSGTR_SKIN_FONT_FontImageNotFound "Schriftbilddatei nicht gefunden\n"
#define MSGTR_SKIN_FONT_NonExistentFontID "nicht existierende Schriftbezeichnung ( %s )\n"
#define MSGTR_SKIN_UnknownParameter "unbekannter Parameter ( %s )\n"
#define MSGTR_SKINBROWSER_NotEnoughMemory "[Skin Browser] nicht genug Speicher.\n"

#endif
