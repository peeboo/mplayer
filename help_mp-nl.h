// Translated by:  Panagiotis Issaris <takis@lumumba.luc.ac.be>

#ifdef HELP_MP_DEFINE_STATIC
static char* banner_text=
"\n\n"
"MPlayer " VERSION "(C) 2000-2002 Arpad Gereoffy (zie DOCS!)\n"
"\n";

static char help_text[]=
#ifdef HAVE_NEW_GUI
"Gebruik:   mplayer [-gui] [opties] [pad/]bestandsnaam\n"
#else
"Gebruik:   mplayer [opties] [pad/]bestandsnaam\n"
#endif
"\n"
"Opties:\n"
" -vo <drv[:dev]>  selecteer video uitvoer driver & device (zie '-vo help' voor lijst)\n"
" -ao <drv[:dev]>  selecteer audio uitvoer driver & device (zie '-ao help' voor lijst)\n"
#ifdef HAVE_VCD
" -vcd <trackno>   speel VCD (Video CD) track van device in plaats van standaard bestand\n"
#endif
#ifdef HAVE_LIBCSS
" -dvdauth <dev>   specificeer DVD device voor authenticatie (voor geencrypteerde schijven)\n"
#endif
#ifdef USE_DVDREAD
" -dvd <titelnr>   speel DVD titel/track van device in plaats van gewoon bestand\n"
" -alang/-slang    selecteer DVD audio/ondertitelingstaal (door middel van 2-karakter landcode)\n"
#endif
" -ss <timepos>    ga naar opgegeven (seconden of hh:mm:ss) positie\n"
" -nosound         speel het geluid niet af\n"
" -fs -vm -zoom    volledig scherm afspeel opties (fullscr,vidmode chg,softw.scale)\n"
" -x <x> -y <y>    herschaal beeld naar <x> * <y> resolutie [als -vo driver het ondersteunt!]\n"
" -sub <bestand>   specificeer het te gebruiken ondertitel bestand (zie ook -subfps, -subdelay)\n"
" -playlist <file> specificeer het te gebruiken playlist bestand\n"
" -vid x -aid y    opties om te spelen video (x) en audio (y) stream te selecteren\n"
" -fps x -srate y  opties om video (x fps) en audio (y Hz) tempo te veranderen\n"
" -pp <kwaliteit>  activeer postprocessing filter (Zie manpage/docs voor meer informatie)\n"
" -framedrop       activeer frame-dropping (voor trage machines)\n"
"\n"
"Toetsen: (Zie manpage voor de volledige lijst, kijk ook naar input.conf)\n"
" <-  of  ->       ga 10 seconden achterwaarts/voorwaarts\n"
" omhoog of omlaag ga 1 minuut achterwaarts/voorwaarts\n"
" PGUP of PGDOWN   ga 10 minuten achterwaarts/voorwaarts\n"
" < or >           ga naar vorige/volgende item in playlist\n"
" p of SPACE       pauzeer film (druk eender welke toets om verder te gaan)\n"
" q of ESC         stop afspelen en sluit programma af\n"
" + of -           pas audio vertraging aan met +/- 0.1 seconde\n"
" o                doorloop OSD modes: geen / enkel zoekbalk / zoekbalk en tijd\n"
" * of /           verhoog of verlaag volume (druk 'm' om master/pcm te selecteren)\n"
" z of x           pas ondertiteling vertraging aan met +/- 0.1 seconde\n"
" r or t           verticale positionering van de ondertiteling, zie ook -vop expand !\n"
"\n"
" * * * ZIE MANPAGE VOOR DETAILS, OVERIGE (GEAVANCEERDE) OPTIES EN TOETSEN ! * * *\n"
"\n";
#endif

// ========================= MPlayer messages ===========================

// mplayer.c: 

#define MSGTR_Exiting "\nBezig met afsluiten... (%s)\n"
#define MSGTR_Exit_frames "Gevraagde aantal frames afgespeeld"
#define MSGTR_Exit_quit "Stop"
#define MSGTR_Exit_eof "Einde van bestand"
#define MSGTR_Exit_error "Fatale fout"
#define MSGTR_IntBySignal "\nMPlayer onderbroken door signal %d in module: %s \n"
#define MSGTR_NoHomeDir "Kan HOME dir niet vinden\n"
#define MSGTR_GetpathProblem "get_path(\"config\") probleem\n"
#define MSGTR_CreatingCfgFile "Bezig met het cre�ren van config bestand: %s\n"
#define MSGTR_InvalidVOdriver "Foutieve video uitvoer driver naam: %s\nGebruik '-vo help' om een lijst met beschikbare video drivers te verkrijgen.\n"
#define MSGTR_InvalidAOdriver "Foutieve audio uitvoer driver naam: %s\nGebruik '-ao help' om een lijst met beschikbare audio drivers te verkrijgen.\n"
#define MSGTR_CopyCodecsConf "(copy/ln etc/codecs.conf (van MPlayer source tree) naar ~/.mplayer/codecs.conf)\n"
#define MSGTR_CantLoadFont "Kan font niet laden: %s\n"
#define MSGTR_CantLoadSub "Kan ondertitels niet lezen: %s\n"
#define MSGTR_ErrorDVDkey "Fout bij het verwerken van DVD KEY.\n"
#define MSGTR_CmdlineDVDkey "DVD command line aangevraagde sleutel is opgeslaan voor descrambling.\n"
#define MSGTR_DVDauthOk "DVD auth sequence lijkt OK te zijn.\n"
#define MSGTR_DumpSelectedSteramMissing "dump: FATAL: geselecteerde stream ontbreekt!\n"
#define MSGTR_CantOpenDumpfile "Kan dump bestand niet openen!!!\n"
#define MSGTR_CoreDumped "Debuginformatie weggeschreven naar bestand core\n"
#define MSGTR_FPSnotspecified "FPS niet gespecificeerd (of foutief) in de header! Gebruik de optie -fps!\n"
#define MSGTR_NoVideoStream "Sorry, geen video stream... het is nog niet afspeelbaar\n"
#define MSGTR_TryForceAudioFmt "Probeer audio codec driver familie %d te forceren...\n"
#define MSGTR_CantFindAfmtFallback "Kan audio codec voor geforceerde driver familie niet vinden, val terug op andere drivers.\n"
#define MSGTR_CantFindAudioCodec "Kan codec voor audio format 0x%X niet vinden!\n"
#define MSGTR_TryUpgradeCodecsConfOrRTFM "*** Probeer %s te upgraden van etc/codecs.conf\n*** Als het nog steeds niet OK is, lees dan DOCS/codecs.html!\n"
#define MSGTR_CouldntInitAudioCodec "Kon audio codec niet initialiseren! -> nosound\n"
#define MSGTR_TryForceVideoFmt "Probeer video codec driver familie %d te forceren...\n"
#define MSGTR_CantFindVfmtFallback "Kan video codec voor geforceerde driver familie niet vinden, val terug op andere drivers.\n"
#define MSGTR_CantFindVideoCodec "Kan codec voor video format 0x%X niet vinden!\n"
#define MSGTR_VOincompCodec "Sorry, geselecteerde video_out device is incompatibel met deze codec.\n"
#define MSGTR_CouldntInitVideoCodec "FATAL: Kon video codec niet initialiseren :(\n"
#define MSGTR_EncodeFileExists "Bestand bestaat reeds: %s (overschrijf uw favoriete AVI niet!)\n"
#define MSGTR_CantCreateEncodeFile "Kan bestand voor encoding niet cre�ren\n"
#define MSGTR_CannotInitVO "FATAL: Kan video driver niet initialiseren!\n"
#define MSGTR_CannotInitAO "Kon audio device niet open/init -> NOSOUND\n"
#define MSGTR_StartPlaying "Start afspelen...\n"

#define MSGTR_SystemTooSlow "\n\n"\
"         ************************************************\n"\
"         ** Je system is te TRAAG om dit af te spelen! **\n"\
"         ************************************************\n"\
"!!! Mogelijke oorzaken, problemen, oplossingen: \n"\
"- Meestal: kapotte/buggy _audio_ driver. Oplossing: Probeer -ao sdl of gebruik\n"\
"  ALSA 0.5 of oss emulatie of ALSA 0.9. Lees DOCS/sound.html voor more tips!\n"\
"- Trage video output. Probeer andere -vo driver (voor lijst: -vo help) of probeer\n"\
"  met -framedrop !  Lees DOCS/video.html voor video tuning/speedup tips.\n"\
"- Trage CPU. Probeer geen grote DVD/DivX af te spelen op een trage CPU! Probeer -hardframedrop\n"\
"- Kapot bestand. Probeer verschillende combinaties van: -nobps  -ni  -mc 0  -forceidx\n"\
"- Gebruik je -cache om een niet-interleaved bestand af te spelen? Probeer met -nocache\n"\
"Als geen van deze oorzaken van toepassingen zijn, lees dan DOCS/bugreports.html !\n\n"

#define MSGTR_NoGui "MPlayer werd gecompileerd ZONDER GUI ondersteuning!\n"
#define MSGTR_GuiNeedsX "MPlayer GUI heeft X11 nodig!\n"
#define MSGTR_Playing "Bezig met het afspelen van %s\n"
#define MSGTR_NoSound "Audio: geen geluid!!!\n"
#define MSGTR_FPSforced "FPS geforceerd om %5.3f te zijn (ftime: %5.3f)\n"
#define MSGTR_CompiledWithRuntimeDetection "Gecompileerd met RUNTIME CPU detectie - waarschuwing, dit is niet optimaal! Om de best mogelijke performantie te krijgen, hercompileer je mplayer met --disable-runtime-cpudetection\n"
#define MSGTR_CompiledWithCPUExtensions "Gecompileerd voor x86 CPU met de volgende uitbreidingen:"
#define MSGTR_AvailableVideoOutputPlugins "Beschikbare video output plugins:\n"
#define MSGTR_AvailableVideoOutputDrivers "Beschikbare video output drivers:\n"
#define MSGTR_AvailableAudioOutputDrivers "Beschikbare audio output drivers:\n"
#define MSGTR_AvailableAudioCodecs "Beschikbare audio codecs:\n"
#define MSGTR_AvailableVideoCodecs "Beschikbare video codecs:\n"
#define MSGTR_UsingRTCTiming "Er wordt gebruik gemaakt van Linux's hardware RTC timing (%ldHz)\n"
#define MSGTR_CannotReadVideoPropertiers "Video: kan eigenschappen niet lezen\n"
#define MSGTR_NoStreamFound "Geen stream gevonden\n"
#define MSGTR_InitializingAudioCodec "Bezig met het initializeren van de audio codec...\n"
#define MSGTR_ErrorInitializingVODevice "Fout bij het openen/initialiseren van het gekozen video_out (-vo) apparaat!\n"
#define MSGTR_ForcedVideoCodec "Forced video codec: %s\n"
#define MSGTR_AODescription_AOAuthor "AO: Beschrijving: %s\nAO: Auteur: %s\n"
#define MSGTR_AOComment "AO: Commentaar: %s\n"
#define MSGTR_Video_NoVideo "Video: geen video!!!\n"
#define MSGTR_NotInitializeVOPorVO "\nFATAAL: Kon de video filters (-vop) of de video uitvoer (-vo) niet initialiseren!\n"
#define MSGTR_Paused "\n------ GEPAUZEERD -------\r"
#define MSGTR_PlaylistLoadUnable "\nKon de playlist %s niet laden\n"

// mencoder.c:

#define MSGTR_MEncoderCopyright "(C) 2000-2002 Arpad Gereoffy (zie DOCS!)\n"
#define MSGTR_UsingPass3ControllFile "Pass3 control bestand gebruikend: %s\n"
#define MSGTR_MissingFilename "\nOntbrekende bestandsnaam!\n\n"
#define MSGTR_CannotOpenFile_Device "Kan bestand/aparaat niet openen\n"
#define MSGTR_ErrorDVDAuth "Fout in DVD auth...\n"
#define MSGTR_CannotOpenDemuxer "Kan demuxer niet openen\n"
#define MSGTR_NoAudioEncoderSelected "\nGeen audio encoder (-oac) geselecteerd! Kies er een of gebruik -nosound. Probeer -oac help !\n"
#define MSGTR_NoVideoEncoderSelected "\nGeen video encoder (-ovc) geselecteerd! Kies er een. Probeer -ovc help !\n"
#define MSGTR_InitializingAudioCodec "Bezig met het initializeren van de audio codec...\n"
#define MSGTR_CannotOpenOutputFile "Kan het uitvoer bestand '%s' niet openen\n"
#define MSGTR_EncoderOpenFailed "Het openen van de encoder is mislukt\n"
#define MSGTR_ForcingOutputFourcc "Forcing output fourcc to %x [%.4s]\n"
#define MSGTR_WritingAVIHeader "Bezig met het schrijven van de AVI header...\n"
#define MSGTR_DuplicateFrames "\nduplicate %d frame(s)!!!    \n"
#define MSGTR_SkipFrame "\nskip frame!!!    \n"
#define MSGTR_ErrorWritingFile "%s: fout bij het schrijven van het bestand.\n"
#define MSGTR_WritingAVIIndex "\nBezig met het schrijven van de AVI index...\n"
#define MSGTR_FixupAVIHeader "Bezig met het herstellen van de AVI header...\n"
#define MSGTR_RecommendedVideoBitrate "Aangeraden video bitrate voor %s CD: %d\n"
#define MSGTR_VideoStreamResult "\nVideo stream: %8.3f kbit/s  (%d bps)  grootte: %d bytes  %5.3f secs  %d frames\n"
#define MSGTR_AudioStreamResult "\nAudio stream: %8.3f kbit/s  (%d bps)  grootte: %d bytes  %5.3f secs\n"

// open.c, stream.c: 
#define MSGTR_CdDevNotfound "CD-ROM Device '%s' niet gevonden!\n"
#define MSGTR_ErrTrackSelect "Fout bij het selecteren van VCD track!"
#define MSGTR_ReadSTDIN "Lezen van stdin...\n"
#define MSGTR_UnableOpenURL "Onmogelijk om URL te openen: %s\n"
#define MSGTR_ConnToServer "Verbonden met server: %s\n"
#define MSGTR_FileNotFound "Bestand niet gevonden: '%s'\n"

#define MSGTR_CantOpenDVD "Kon DVD device niet openen: %s\n"
#define MSGTR_DVDwait "Bezig met het lezen van de schijf structuur, gelieve te wachten...\n"
#define MSGTR_DVDnumTitles "Er zijn %d titels op deze DVD.\n"
#define MSGTR_DVDinvalidTitle "Foutieve DVD titelnummer: %d\n"
#define MSGTR_DVDnumChapters "Er zijn %d hoofdstukken in deze DVD titel.\n"
#define MSGTR_DVDinvalidChapter "Foutief DVD hoofdstuknummer: %d\n"
#define MSGTR_DVDnumAngles "Er zijn %d gezichtspunten in deze DVD titel.\n"
#define MSGTR_DVDinvalidAngle "Foutief DVD gezichtspuntnummer: %d\n"
#define MSGTR_DVDnoIFO "Kan het IFO bestand voor DVD titel %d niet openen.\n"
#define MSGTR_DVDnoVOBs "Kan titel VOBS niet openen (VTS_%02d_1.VOB).\n"
#define MSGTR_DVDopenOk "DVD openen geslaagd!\n"

// demuxer.c, demux_*.c:
#define MSGTR_AudioStreamRedefined "Waarschuwing! Audio stream header %d geherdefinieerd!\n"
#define MSGTR_VideoStreamRedefined "Waarschuwing! Video stream header %d geherdefinieerd!\n"
#define MSGTR_TooManyAudioInBuffer "\nDEMUXER: Te veel (%d in %d bytes) audio packets in de buffer!\n"
#define MSGTR_TooManyVideoInBuffer "\nDEMUXER: Te veel (%d in %d bytes) video packets in de buffer!\n"
#define MSGTR_MaybeNI "(misschien speel je een non-interleaved stream/bestand of werkte de codec niet)\n" \
		      "Voor .AVI bestanden probeer je best non-interleaved mode met de optie -ni\n"
#define MSGTR_SwitchToNi "\nSlecht geinterleaved .AVI bestand gedetecteerd - schakel om naar -ni mode!\n"
#define MSGTR_DetectedFILMfile "FILM bestandsformaat gedetecteerd!\n"
#define MSGTR_DetectedFLIfile "FLI bestandsformaat gedetecteerd!\n"
#define MSGTR_DetectedROQfile "RoQ bestandsformaat gedetecteerd!\n"
#define MSGTR_DetectedREALfile "REAL bestandsformaat gedetecteerd!\n"
#define MSGTR_DetectedAVIfile "AVI bestandsformaat gedetecteerd!\n"
#define MSGTR_DetectedASFfile "ASF bestandsformaat gedetecteerd!\n"
#define MSGTR_DetectedMPEGPESfile "MPEG-PES bestandsformaat gedetecteerd!\n"
#define MSGTR_DetectedMPEGPSfile "MPEG-PS bestandsformaat gedetecteerd!\n"
#define MSGTR_DetectedMPEGESfile "MPEG-ES bestandsformaat gedetecteerd!\n"
#define MSGTR_DetectedQTMOVfile "QuickTime/MOV bestandsformaat gedetecteerd!\n"
#define MSGTR_DetectedYUV4MPEG2file "YUV4MPEG2 bestandsformaat gedetecteerd!\n"
#define MSGTR_DetectedNuppelVideofile "NuppelVideo bestandsformaat gedetecteerd!\n"
#define MSGTR_DetectedVIVOfile "VIVO bestandsformaat gedetecteerd!\n"
#define MSGTR_DetectedBMPfile "BMP bestandsformaat gedetecteerd!\n"
#define MSGTR_DetectedOGGfile "OGG bestandsformaat gedetecteerd!\n"
#define MSGTR_DetectedRAWDVfile "RAWDV bestandsformaat gedetecteerd!\n"
#define MSGTR_DetectedAudiofile "Audio bestandsformaat gedetecteerd!\n"
#define MSGTR_NotSystemStream "Geen MPEG System Stream formaat... (misschien Transport Stream?)\n"
#define MSGTR_MissingMpegVideo "Ontbrekende MPEG video stream!? Contacteer de auteur, het zou een bug kunnen zijn :(\n"
#define MSGTR_InvalidMPEGES "Invalid MPEG-ES stream??? Contacteer de auteur, het zou een bug kunnen zijn :(\n"
#define MSGTR_FormatNotRecognized "============= Sorry, dit bestandsformaat niet herkend/ondersteund ===============\n"\
				  "=== Als dit een AVI bestand, ASF bestand of MPEG stream is, contacteer dan aub de auteur! ===\n"
#define MSGTR_MissingVideoStream "Geen video stream gevonden!\n"
#define MSGTR_MissingAudioStream "Geen audio stream gevonden...  ->nosound\n"
#define MSGTR_MissingVideoStreamBug "Ontbrekende video stream!? Contacteer de auteur, het zou een bug kunnen zijn :(\n"

#define MSGTR_DoesntContainSelectedStream "demux: bestand bevat de geselecteerde audio- of videostream niet\n"

#define MSGTR_NI_Forced "Geforceerd"
#define MSGTR_NI_Detected "Gedetecteerd"
#define MSGTR_NI_Message "%s NON-INTERLEAVED AVI bestandsformaat!\n"

#define MSGTR_UsingNINI "NON-INTERLEAVED Broken AVI bestandsformaat wordt gebruikt!\n"
#define MSGTR_CouldntDetFNo "Kon het aantal frames niet bepalen (voor absolute verplaatsing)  \n"
#define MSGTR_CantSeekRawAVI "Kan niet in raw .AVI streams verplaatsen! (index nodig, probeer met de -idx optie!)  \n"
#define MSGTR_CantSeekFile "Kan niet verplaatsen in dit bestand!  \n"

#define MSGTR_EncryptedVOB "Geencrypteerd VOB bestand (niet gecompileerd met libcss ondersteuning)! Lees DOCS/cd-dvd.html bestand\n"
#define MSGTR_EncryptedVOBauth "Geencrypteerde stream maar authenticatie was niet aangevraagd door u!!\n"

#define MSGTR_MOVcomprhdr "MOV: Gecomprimeerde headers (nog) niet ondersteund!\n"
#define MSGTR_MOVvariableFourCC "MOV: Waarschuwing! variabele FOURCC gedetecteerd!?\n"
#define MSGTR_MOVtooManyTrk "MOV: Waarschuwing! te veel tracks!"
#define MSGTR_MOVnotyetsupp "\n****** Quicktime MOV formaat nog niet ondersteund!!!!!!! *******\n"
#define MSGTR_FoundAudioStream "==> Audio stream gevonden: %d\n"
#define MSGTR_FoundVideoStream "==> Video stream gevonden: %d\n"
#define MSGTR_DetectedTV "TV gedetecteerd! ;-)\n"
#define MSGTR_ErrorOpeningOGGDemuxer "Kan de Ogg demuxer niet openen\n"
#define MSGTR_ASFSearchingForAudioStream "ASF: Bezig met zoeken naar audio stream (id:%d)\n"
#define MSGTR_CannotOpenAudioStream "Kan audio stream niet openen: %s\n"
#define MSGTR_CannotOpenSubtitlesStream "Kan ondertitelingstream niet openen: %s\n"
#define MSGTR_OpeningAudioDemuxerFailed "Kan audio demuxer niet openen: %s\n"
#define MSGTR_OpeningSubtitlesDemuxerFailed "Openen van de ondertiteling demuxer is mislukt: %s\n"
#define MSGTR_TVInputNotSeekable "TV invoer is niet doorzoekbaar! (Waarschijnlijk zal zoeken de kanalen veranderen ;)\n"
#define MSGTR_DemuxerInfoAlreadyPresent "Demuxer info %s reeds aanwezig\n!"
#define MSGTR_ClipInfo "Clip info: \n"

// dec_video.c & dec_audio.c:
#define MSGTR_CantOpenCodec "kon codec niet openen\n"
#define MSGTR_CantCloseCodec "kon codec niet sluiten\n"

#define MSGTR_MissingDLLcodec "FOUT: Kon de nodige DirectShow codec niet openen: %s\n"
#define MSGTR_ACMiniterror "Kon Win32/ACM AUDIO codec niet laden/initialiseren (ontbrekend DLL bestand?)\n"
#define MSGTR_MissingLAVCcodec "Kan codec codec '%s' niet vinden in libavcodec...\n"

#define MSGTR_NoDShowSupport "MPlayer werd gecompileerd ZONDER directshow ondersteuning!\n"
#define MSGTR_NoWfvSupport "Ondersteuning voor win32 codecs uitgeschakeld, of niet beschikbaar op niet-x86 platformen!\n"
#define MSGTR_NoDivx4Support "MPlayer werd gecompileerd ZONDER DivX4Linux (libdivxdecore.so) ondersteuning!\n"
#define MSGTR_NoLAVCsupport "MPlayer werd gecompileerd ZONDER ffmpeg/libavcodec ondersteuning!\n"
#define MSGTR_NoACMSupport "Win32/ACM audio codec uitgeschakeld, of niet beschikbaar op niet-x86 CPU -> forceer nosound :(\n"
#define MSGTR_NoDShowAudio "Gecompileerd zonder DirectShow ondersteuning -> forceer nosound :(\n"
#define MSGTR_NoOggVorbis "OggVorbis audio codec uigeschakeld -> forceer nosound :(\n"
#define MSGTR_NoXAnimSupport "MPlayer werd gecompileerd ZONDER XAnim ondersteuning!\n"

#define MSGTR_MpegPPhint "WAARSCHUWING! Je vroeg beeld postprocessing aan voor een MPEG 1/2 video,\n" \
			 "         maar compileerde MPlayer zonder MPEG 1/2 postprocessing ondersteuning!\n" \
			 "         #define MPEG12_POSTPROC in config.h, en hercompileer libmpeg2!\n"
#define MSGTR_MpegNoSequHdr "MPEG: FATAAL: EOF tijdens het zoeken naar sequence header\n"
#define MSGTR_CannotReadMpegSequHdr "FATAAL: Kan sequence header niet lezen!\n"
#define MSGTR_CannotReadMpegSequHdrEx "FATAAL: Kan sequence header extension niet lezen!\n"
#define MSGTR_BadMpegSequHdr "MPEG: Foutieve sequence header!\n"
#define MSGTR_BadMpegSequHdrEx "MPEG: Foutieve sequence header extension!\n"

#define MSGTR_ShMemAllocFail "Kan gedeeld geheugen niet alloceren\n"
#define MSGTR_CantAllocAudioBuf "Kan audio uitvoer buffer niet alloceren\n"
#define MSGTR_NoMemForDecodedImage "niet genoeg geheugen voor buffer voor gedecodeerd beeld (%ld bytes)\n"

#define MSGTR_AC3notvalid "AC3 stream ongeldig.\n"
#define MSGTR_AC3only48k "Alleen 48000 Hz streams ondersteund.\n"
#define MSGTR_UnknownAudio "Onbekend/ontbrekend audio formaat, gebruik -nosound\n"

#define MSGTR_UsingExternalPP "[PP] Gebruik makend van externe postprocessing filter, max q = %d\n"
#define MSGTR_UsingCodecPP "[PP] Gebruik makend van de codec's interne postprocessing, max q = %d\n"
#define MSGTR_VideoAttributeNotSupportedByVO_VD "Video attribuut '%s' wordt niet ondersteund door de gekozen vo & vd! \n"
#define MSGTR_VideoCodecFamilyNotAvailable "Aangevraagde video codec familie [%s] (vfm=%d) niet beschikbaar (activeer het bij het compileren!)\n"
#define MSGTR_AudioCodecFamilyNotAvailable "Aangevraagde audio codec familie [%s] (afm=%d) niet beschikbaar (activeer het bij het compileren!)\n"
#define MSGTR_OpeningVideoDecoder "Bezig met het openen van de video decoder: [%s] %s\n"
#define MSGTR_OpeningAudioDecoder "Bezig met het openen van de audio decoder: [%s] %s\n"
#define MSGTR_UninitVideo "Deinitialisatie video: %d  \n"
#define MSGTR_UninitAudio "Deinitialisatie audio: %d  \n"
#define MSGTR_VDecoderInitFailed "VDecoder initialisatie mislukt :(\n"
#define MSGTR_ADecoderInitFailed "ADecoder initialisatie mislukt :(\n"
#define MSGTR_ADecoderPreinitFailed "ADecoder preinitialisatie mislukt :(\n"
#define MSGTR_AllocatingBytesForInputBuffer "dec_audio: Bezig met het toekennen van %d bytes voor de invoer buffer\n"
#define MSGTR_AllocatingBytesForOutputBuffer "dec_audio: Bezig met het toekennen van %d + %d = %d bytes voor uitvoer buffer\n"

// LIRC:
#define MSGTR_SettingUpLIRC "Bezig met configuratie van lirc ondersteuning...\n"
#define MSGTR_LIRCdisabled "Je zal je afstandsbediening niet kunnen gebruiken\n"
#define MSGTR_LIRCopenfailed "Openen van lirc ondersteuning mislukt!\n"
#define MSGTR_LIRCsocketerr "Er is iets mis met de lirc socket: %s\n"
#define MSGTR_LIRCcfgerr "Lezen van LIRC config bestand mislukt %s !\n"

// vf.c
#define MSGTR_CouldNotFindVideoFilter "Kon video filter '%s' niet vinden\n"
#define MSGTR_CouldNotOpenVideoFilter "Kon video filter '%s' niet openen\n"
#define MSGTR_OpeningVideoFilter "Bezig met het openen van video filter: "
#define MSGTR_CannotFindColorspace "Kan geen gemeenschappelijke colorspace vinden, zelfs bij gebruik van 'scale' :(\n"

// vd.c
#define MSGTR_CodecDidNotSet "VDec: codec stelde sh->disp_w en sh->disp_h niet in, ik probeer het probleem te omzeilen!\n"
#define MSGTR_VoConfigRequest "VDec: vo config aanvraag - %d x %d (csp voorkeur: %s)\n"
#define MSGTR_CouldNotFindColorspace "Kon geen matching colorspace vinden - ik probeer opnieuw met -vop scale...\n"
#define MSGTR_MovieAspectIsSet "Movie-Aspect is %.2f:1 - prescaling to correct movie aspect.\n"
#define MSGTR_MovieAspectUndefined "Movie-Aspect is niet gedefinieerd - geen voorscalering toegepast.\n"
	
// ====================== GUI messages/buttons ========================

#ifdef HAVE_NEW_GUI

// --- labels ---
#define MSGTR_About "Info over"
#define MSGTR_FileSelect "Selecteer bestand ..."
#define MSGTR_SubtitleSelect "Selecteer ondertiteling ..."
#define MSGTR_OtherSelect "Selecteer ..."
#define MSGTR_AudioFileSelect "Selecteer extern audio kanaal ..."
#define MSGTR_FontSelect "Selecteer lettertype ..."
#define MSGTR_MessageBox "MessageBox"
#define MSGTR_PlayList "AfspeelLijst"
#define MSGTR_Equalizer "Equalizer"
#define MSGTR_SkinBrowser "Skin Browser"
#define MSGTR_Network "Network streaming ..."
#define MSGTR_Preferences "Voorkeuren"
#define MSGTR_OSSPreferences "OSS driver configuratie"

// --- buttons ---
#define MSGTR_Ok "Ok"
#define MSGTR_Cancel "Annuleer"
#define MSGTR_Add "Toevoegen"
#define MSGTR_Remove "Verwijderen"
#define MSGTR_Clear "Wis"
#define MSGTR_Config "Configureer"
#define MSGTR_ConfigDriver "Configureer driver"
#define MSGTR_Browse "Browse"

// --- error messages ---
#define MSGTR_NEMDB "Sorry, niet genoeg geheugen voor tekenbuffer."
#define MSGTR_NEMFMR "Sorry, niet genoeg geheugen voor menu rendering."
#define MSGTR_NEMFMM "Sorry, niet genoeg geheugen voor hoofdvenster shape mask."
#define MSGTR_IDFGCVD "Sorry, kon geen GUI compatibele video uitvoer driver vinden."
#define MSGTR_NEEDLAVCFAME "Sorry, je kan geen niet-MPEG bestanden met je DXR3/H+ apparaat aspelen zonder het bestand te herencoderen.\nActiveer lavc of fame in het DXR3/H+ configuratiescherm."

// --- skin loader error messages
#define MSGTR_SKIN_ERRORMESSAGE "[skin] fout skin config bestand op regel %d: %s" 
#define MSGTR_SKIN_WARNING1 "[skin] waarschuwing in skin config bestand op regel %d: widget gevonden maar voordien \"section\" niet gevonden ( %s )"
#define MSGTR_SKIN_WARNING2 "[skin] waarschuwing in skin config bestand op regel %d: widget gevonden maar voordien \"subsection\" niet gevonden (%s)"
#define MSGTR_SKIN_BITMAP_16bit  "16 bits of minder kleurendiepte bitmap niet ondersteund ( %s ).\n"
#define MSGTR_SKIN_BITMAP_FileNotFound  "bestand niet gevonden ( %s )\n"
#define MSGTR_SKIN_BITMAP_BMPReadError "bmp lees fout ( %s )\n"
#define MSGTR_SKIN_BITMAP_TGAReadError "tga lees fout ( %s )\n"
#define MSGTR_SKIN_BITMAP_PNGReadError "png lees fout ( %s )\n"
#define MSGTR_SKIN_BITMAP_RLENotSupported "RLE packed tga niet ondersteund ( %s )\n"
#define MSGTR_SKIN_BITMAP_UnknownFileType "onbekend bestandstype ( %s )\n"
#define MSGTR_SKIN_BITMAP_ConvertError "24 bit naar 32 bit converteerfout ( %s )\n"
#define MSGTR_SKIN_BITMAP_UnknownMessage "onbekende boodschap: %s\n"
#define MSGTR_SKIN_FONT_NotEnoughtMemory "onvoldoende geheugen\n"
#define MSGTR_SKIN_FONT_TooManyFontsDeclared "te veel fonts gedeclareerd\n"
#define MSGTR_SKIN_FONT_FontFileNotFound "font bestand niet gevonden\n"
#define MSGTR_SKIN_FONT_FontImageNotFound "font image bestand niet gevonden\n"
#define MSGTR_SKIN_FONT_NonExistentFontID "onbestaande font identifier ( %s )\n"
#define MSGTR_SKIN_UnknownParameter "onbekende parameter ( %s )\n"
#define MSGTR_SKINBROWSER_NotEnoughMemory "[skinbrowser] onvoldoende geheugen.\n"
#define MSGTR_SKIN_SKINCFG_SkinNotFound "Skin niet gevonden ( %s ).\n"
#define MSGTR_SKIN_SKINCFG_SkinCfgReadError "Leesfout in skin-configuratiebestand ( %s ).\n"
#define MSGTR_SKIN_LABEL "Skins:"

// --- gtk menus
#define MSGTR_MENU_AboutMPlayer "Over MPlayer"
#define MSGTR_MENU_Open "Open ..."
#define MSGTR_MENU_PlayFile "Speel bestand ..."
#define MSGTR_MENU_PlayVCD "Speel VCD ..."
#define MSGTR_MENU_PlayDVD "Speel DVD ..."
#define MSGTR_MENU_PlayURL "Speel URL ..."
#define MSGTR_MENU_LoadSubtitle "Laad ondertitels ..."
#define MSGTR_MENU_LoadExternAudioFile "Laad extern audio bestand ..."
#define MSGTR_MENU_Playing "Afspelen"
#define MSGTR_MENU_Play "Speel"
#define MSGTR_MENU_Pause "Pauzeer"
#define MSGTR_MENU_Stop "Stop"
#define MSGTR_MENU_NextStream "Volgende stream"
#define MSGTR_MENU_PrevStream "Vorige stream"
#define MSGTR_MENU_Size "Grootte"
#define MSGTR_MENU_NormalSize "Normale grootte"
#define MSGTR_MENU_DoubleSize "Dubbele grootte"
#define MSGTR_MENU_FullScreen "Volledig scherm"
#define MSGTR_MENU_DVD "DVD"
#define MSGTR_MENU_VCD "VCD"
#define MSGTR_MENU_PlayDisc "Speel disc ..."
#define MSGTR_MENU_ShowDVDMenu "Toon DVD menu"
#define MSGTR_MENU_Titles "Titels"
#define MSGTR_MENU_Title "Titel %2d"
#define MSGTR_MENU_None "(geen)"
#define MSGTR_MENU_Chapters "Hoofdstukken"
#define MSGTR_MENU_Chapter "Hoofdstuk %2d"
#define MSGTR_MENU_AudioLanguages "Audio talen"
#define MSGTR_MENU_SubtitleLanguages "Ondertiteling talen"
#define MSGTR_MENU_PlayList "Playlist"
#define MSGTR_MENU_SkinBrowser "Skin browser"
#define MSGTR_MENU_Preferences "Voorkeuren"
#define MSGTR_MENU_Exit "Afsluiten ..."

// --- equalizer
#define MSGTR_EQU_Audio "Audio"
#define MSGTR_EQU_Video "Video"
#define MSGTR_EQU_Contrast "Contrast: "
#define MSGTR_EQU_Brightness "Helderheid: "
#define MSGTR_EQU_Hue "Hue: "
#define MSGTR_EQU_Saturation "Saturatie: "
#define MSGTR_EQU_Front_Left "Links vooraan"
#define MSGTR_EQU_Front_Right "Rechts vooraan"
#define MSGTR_EQU_Back_Left "Links achter"
#define MSGTR_EQU_Back_Right "Rechts achter"
#define MSGTR_EQU_Center "Centrum"
#define MSGTR_EQU_Bass "Bass"
#define MSGTR_EQU_All "Allemaal"

// --- playlist
#define MSGTR_PLAYLIST_Path "Pad"
#define MSGTR_PLAYLIST_Selected "Geselecteerde bestanden"
#define MSGTR_PLAYLIST_Files "Bestanden"
#define MSGTR_PLAYLIST_DirectoryTree "Directory tree"

// --- preferences
#define MSGTR_PREFERENCES_None "Geen"
#define MSGTR_PREFERENCES_AvailableDrivers "Beschikbare drivers:"
#define MSGTR_PREFERENCES_DoNotPlaySound "Speel geen geluid af"
#define MSGTR_PREFERENCES_NormalizeSound "Normalizeer het geluid"
#define MSGTR_PREFERENCES_EnEqualizer "Gebruik equalizer"
#define MSGTR_PREFERENCES_ExtraStereo "Gebruik extra stereo"
#define MSGTR_PREFERENCES_Coefficient "Coefficient:"
#define MSGTR_PREFERENCES_AudioDelay "Audio vertraging"
#define MSGTR_PREFERENCES_Audio "Audio"
#define MSGTR_PREFERENCES_VideoEqu "Gebruik video equalizer"
#define MSGTR_PREFERENCES_DoubleBuffer "Gebruik dubbele buffering"
#define MSGTR_PREFERENCES_DirectRender "Gebruik directe rendering"
#define MSGTR_PREFERENCES_FrameDrop "Gebruik frame dropping"
#define MSGTR_PREFERENCES_HFrameDrop "Gebruik HARD frame drop( gevaarlijk )"
#define MSGTR_PREFERENCES_Flip "Keer het beeld ondersteboven"
#define MSGTR_PREFERENCES_Panscan "Panscan: "
#define MSGTR_PREFERENCES_Video "Video"
#define MSGTR_PREFERENCES_OSDTimer "Timer en indicatoren"
#define MSGTR_PREFERENCES_OSDProgress "Enkel voortgangsbalk"
#define MSGTR_PREFERENCES_Subtitle "Ondertiteling:"
#define MSGTR_PREFERENCES_SUB_Delay "Vertraging: "
#define MSGTR_PREFERENCES_SUB_FPS "FPS:"
#define MSGTR_PREFERENCES_SUB_POS "Positie: "
#define MSGTR_PREFERENCES_SUB_AutoLoad "Geen automatisch laden van ondertiteling"
#define MSGTR_PREFERENCES_SUB_Unicode "Unicode ondertiteling"
#define MSGTR_PREFERENCES_SUB_MPSUB "Converteer de gegeven ondertiteling naar MPlayer's ondertitelingsformaat"
#define MSGTR_PREFERENCES_SUB_SRT "Converteer de gegeven ondertiteling naar het tijdsgebaseerde SubViewer( SRT ) formaat"
#define MSGTR_PREFERENCES_Font "Lettertype:"
#define MSGTR_PREFERENCES_FontFactor "Lettertype factor:"
#define MSGTR_PREFERENCES_PostProcess "Gebruik postprocess"
#define MSGTR_PREFERENCES_AutoQuality "Auto kwaliteit: "
#define MSGTR_PREFERENCES_NI "Gebruik non-interleaved AVI parser"
#define MSGTR_PREFERENCES_IDX "Reconstrueer de index tabel als dat nodig is"
#define MSGTR_PREFERENCES_VideoCodecFamily "Video codec familie:"
#define MSGTR_PREFERENCES_FRAME_OSD_Level "OSD level"
#define MSGTR_PREFERENCES_FRAME_Subtitle "Ondertiteling"
#define MSGTR_PREFERENCES_FRAME_Font "Lettertype"
#define MSGTR_PREFERENCES_FRAME_PostProcess "Postprocess"
#define MSGTR_PREFERENCES_FRAME_CodecDemuxer "Codec & demuxer"
#define MSGTR_PREFERENCES_OSS_Device "Apparaat:"
#define MSGTR_PREFERENCES_OSS_Mixer "Mixer:"
#define MSGTR_PREFERENCES_Message "Denk eraan, dat sommige functies het afspelen herstarten."
#define MSGTR_PREFERENCES_DXR3_VENC "Video encoder:"
#define MSGTR_PREFERENCES_DXR3_LAVC "Gebruik LAVC (ffmpeg)"
#define MSGTR_PREFERENCES_DXR3_FAME "Gebruik FAME"

// --- messagebox
#define MSGTR_MSGBOX_LABEL_FatalError "fatale fout ..."
#define MSGTR_MSGBOX_LABEL_Error "fout ..."
#define MSGTR_MSGBOX_LABEL_Warning "waarschuwing ..." 

#endif
