// Translated by:  Anders Rune Jensen <anders@gnulinux.dk>
// Sync'ed with help_mp-en.h 1.93.

// ========================= MPlayer help ===========================

#ifdef HELP_MP_DEFINE_STATIC
static char* banner_text=
"\n\n"
"MPlayer " VERSION "(C) 2000-2003 Arpad Gereoffy (se dokumentationen!)\n"
"\n";

static char help_text[]=
"Benyt:   mplayer [indstillinger] [URL|sti/]filnavn\n"
"\n"
"Basale indstillinger (se manualen for en komplet liste):\n"
" -vo <drv[:enhed]> v�lg videodriver og -enhed (se '-vo help' for en komplet liste)\n"
" -ao <drv[:enhed]> v�lg lyddriver og -enhed (se '-ao help' for en komplet liste)\n"
#ifdef HAVE_VCD
" -vcd <trackno>  afspil et VCD (Video CD) spor fra et drev i stedet for en fil\n"
#endif
#ifdef HAVE_LIBCSS
" -dvdauth <dev>  specificer DVD enhed til godkendelse (krypterede diske)\n"
#endif
#ifdef USE_DVDREAD
" -dvd <titleno>  afspiller DVD titel fra et drev i stedet for en fil\n"
" -alang/-slang   v�lg DVD lyd/undertekst sprog (vha. landekode p� 2 tegn)\n"
#endif
" -ss <timepos>   s�ger til en given position (sekunder eller hh:mm:ss)\n"
" -nosound        afspiller uden lyd\n"
" -fs -vm -zoom   type afspilning i fuldsk�rm (alm. fuldsk�rm, video mode, software skalering)\n"
" -x <x> -y <y>   skaler billede til <x> * <y> opl�sning [hvis -vo driveren underst�tter dette!]\n"
" -sub <file>     specificer undertekst-fil (se ogs� -subfps, -subdelay)\n"
" -playlist <file> specificer afspilningsliste\n"
" -vid x -aid y   afspil film (x) og lyd (y)\n"
" -fps x -srate y �ndre filmens (x fps) og lydens (y Hz)\n"
" -pp <quality>   sl� efterprocesseringsfilter til (bedre billedkvalitet) (se manualen for flere detaljer)\n"
" -framedrop      sl� billede-skip til (kan hj�lpe langsomme maskiner)\n"
"\n"
"Taster: (se manualen for en komplet liste, check ogs� input.conf)\n"
" <-  or  ->      s�ger 10 sekunder frem eller tilbage\n"
" up or down      s�ger 1 minut frem eller tilbage \n"
" pgup or pgdown  s�ger 10 minutter frem eller tilbage\n"
" < or >          s�ger frem eller tilbage i afspilningslisten\n"
" p or SPACE      pause filmen (starter igen ved tryk p� en vilk�rlig tast)\n"
" q or ESC        stop afspilning og afslut program\n"
" + or -          juster lydforsinkelse med +/- 0.1 sekundt\n"
" o               v�lger OSD type:  ingen / s�gebar / s�gebar+tid\n"
" * or /          for�g eller formindsk volumen (tryk 'm' for at v�lge master/pcm)\n"
" z or x          juster undertekstforsinkelse med +/- 0.1 sekund\n"
"\n"
" * * * SE MANUALEN FOR FLERE DETALJER, YDERLIGERE (AVANCEREDE) MULIGHEDER OG TASTER ! * * *\n"
"\n";
#endif

// ========================= MPlayer messages ===========================

// mplayer.c: 

#define MSGTR_Exiting "\n Afslutter... (%s)\n"
#define MSGTR_Exit_quit "Afslut"
#define MSGTR_Exit_eof "Slut p� filen"
#define MSGTR_Exit_error "Fatal fejl"
#define MSGTR_IntBySignal "\nMPlayer afbrudt af signal %d i modul: %s \n"
#define MSGTR_NoHomeDir "Kan ikke finde hjemmekatalog\n"
#define MSGTR_GetpathProblem "get_path(\"config\") problem\n"
#define MSGTR_CreatingCfgFile "Genererer konfigurationsfil: %s\n"
#define MSGTR_InvalidVOdriver "Ugyldig videodriver: %s\nBrug '-vo help' for at f� en komplet liste over gyldige videodrivere.\n"
#define MSGTR_InvalidAOdriver "Ugyldig lyddriver: %s\nBrug '-ao help' for at f� en komplet liste over gyldige lyddrivere.\n"
#define MSGTR_CopyCodecsConf "(kopier/link etc/codecs.conf (fra MPlayer kilde katalog) til ~/.mplayer/codecs.conf)\n"
#define MSGTR_BuiltinCodecsConf "Benytter indbyggede standardv�rdier for codecs.conf\n"
#define MSGTR_CantLoadFont "Kan ikke indl�se skrifttypen:  %s\n"
#define MSGTR_CantLoadSub "Kan ikke indl�se undertekstfilen: %s\n"
#define MSGTR_ErrorDVDkey "Fejl under afvikling af DVDN�GLE.\n"
#define MSGTR_CmdlineDVDkey "DVD kommandolinjen�gle er gemt til dekryptering.\n"
#define MSGTR_DVDauthOk "DVD auth sekvens synes af v�re OK.\n"
#define MSGTR_DumpSelectedStreamMissing "dump: FATAL: kan ikke finde den valge fil eller adresse!\n"
#define MSGTR_CantOpenDumpfile "Kan ikke �bne dump filen!!!\n"
#define MSGTR_CoreDumped "kernen dumpede :)\n"
#define MSGTR_FPSnotspecified "FPS ikke specificeret (eller ugyldig) i headeren! Brug -fps !\n"
#define MSGTR_TryForceAudioFmtStr "Pr�ver at tvinge et lyd-codec driverfamilie %s ...\n"
#define MSGTR_CantFindAfmtFallback "Kan ikke finde lyd codec for driver familien, falder tilbage p� en anden driver.\n"
#define MSGTR_CantFindAudioCodec "Kan ikke finde codec til lydformatet 0x%X !\n"
#define MSGTR_TryUpgradeCodecsConfOrRTFM "*** Pr�v at opgradere %s fra etc/codecs.conf\n*** Hvis dette ikke hj�lper, s� l�s filen DOCS/codecs.html!\n"
#define MSGTR_CouldntInitAudioCodec "Kunne ikke initialisere lydcodec! -> ingen lyd\n"
#define MSGTR_TryForceVideoFmtStr "Pr�ver at tvinge en videocodec driver familie %s ...\n"
#define MSGTR_CantFindVideoCodec "Kan ikke finde videocodec til formatet 0x%X !\n"
#define MSGTR_VOincompCodec "Desv�rre, den valgte video-driverenhed er ikke kompatibel med dette codec.\n"
#define MSGTR_CannotInitVO "FATAL: Kan ikke initialisere videodriveren!\n"
#define MSGTR_CannotInitAO "Kunne ikke �bne/initialisere lydkortet -> INGEN LYD\n"
#define MSGTR_StartPlaying "Starter afspilning ...\n"

#define MSGTR_SystemTooSlow "\n\n"\
"       ***********************************************************\n"\
"       **** Dit system er for langsomt til at afspille dette! ****\n"\
"       ***********************************************************\n"\
"!!! Evt. fejlkilder, problemer eller muligheder: \n"\
"- Den mest almindelige: �delagt eller d�rlig _lydkort_ driver. Mulighed: pr�v -ao sdl eller brug\n"\
"  ALSA 0.5 eller oss emulation af ALSA 0.9. l�s DOCS/sound.html for flere tips!\n"\
"  Du kan ogs� ekperimentere med -autosync 30 eller andre v�rdier.\n"\
"- Langsom video output. Pr�v en anden -vo driver (for liste: -vo help) eller pr�v\n"\
"  med -framedrop !  L�s DOCS/video.html for video tuning/speedup tips.\n"\
"- Langsom CPU. Pr�v ikke at afspille en stor dvd/divx p� en langsom CPU! Pr�v -hardframedrop\n"\
"- �delagt fil. Pr�v kombinationer af f�lgende: -nobps  -ni  -mc 0  -forceidx\n"\
"- For afspilning fra langsomt medie (nfs/smb, dvd, vcd osv.) pr�v -cache 8192\n"\
"- Bruger du -cache til at afspille en non-interleaved AVI fil? Pr�v i stedet -nocache.\n"\
"Hvis intet af dette hjalp, l�s da DOCS/bugreports.html !\n\n"

#define MSGTR_NoGui "MPlayer blev kompileret UDEN grafisk gr�nseflade!\n"
#define MSGTR_GuiNeedsX "MPlayer grafisk gr�nseflade kr�ver X11!\n"
#define MSGTR_Playing "Afspiller %s\n"
#define MSGTR_NoSound "Lyd: ingen lyd!!!\n"
#define MSGTR_FPSforced "FPS tvunget til %5.3f  (ftime: %5.3f)\n"
#define MSGTR_CompiledWithRuntimeDetection "Kompileret med dynamisk CPU valg - advarsel, dette er ikke optimalt! For at f� den bedre ydelse rekompiler MPlayer fra kildekode med --disable-runtime-cpudetection\n"
#define MSGTR_CompiledWithCPUExtensions "Kompileret til x86 CPU med udvidelse:"
#define MSGTR_AvailableVideoOutputPlugins "Tilg�ngelige videoudvidelser:\n"
#define MSGTR_AvailableVideoOutputDrivers "Tilg�ngelige videodrivere:\n"
#define MSGTR_AvailableAudioOutputDrivers "Tilg�ngelige lyddrivere:\n"
#define MSGTR_AvailableAudioCodecs "Tilg�ngelige lydcodecs:\n"
#define MSGTR_AvailableVideoCodecs "Tilg�ngelige videocodecs:\n"
#define MSGTR_AvailableAudioFm "\nTilg�ngelige (pr�kompilerede) lyd-codec familier/drivere:\n"
#define MSGTR_AvailableVideoFm "\nTilg�ngelige (pr�kompilerede) video-codec familier/drivere:\n"
#define MSGTR_AvailableFsType "Tilg�ngelige fuldsk�rms modes:\n"
#define MSGTR_UsingRTCTiming "Benytter Linux's hardware RTC timing (%ldHz)\n"
#define MSGTR_CannotReadVideoProperties "Video: kan ikke l�se egenskaber\n"
#define MSGTR_NoStreamFound "Ingen stream fundet\n"
#define MSGTR_InitializingAudioCodec "Initialiserer lydcodec...\n"
#define MSGTR_ErrorInitializingVODevice "Fejl under initialisering/�bning af den valgte video (-vo) enhed!\n"
#define MSGTR_ForcedVideoCodec "Tvunget videocodec: %s\n"
#define MSGTR_ForcedAudioCodec "Tvunget lydcodec: %s\n"
#define MSGTR_AODescription_AOAuthor "AO: Beskrivelse: %s\nAO: forfatter: %s\n"
#define MSGTR_AOComment "AO: Kommentar: %s\n"
#define MSGTR_Video_NoVideo "Video: ingen video!!!\n"
#define MSGTR_NotInitializeVOPorVO "\nFATAL: Kunne ikke initialisere video filtre (-vop) eller video udgang (-vo) !\n"
#define MSGTR_Paused "\n------ PAUSE -------\r"
#define MSGTR_PlaylistLoadUnable "\nKunne ikke indl�se afspilningslisten %s\n"
#define MSGTR_Exit_SIGILL_RTCpuSel \
"- MPlayer fejlede ved en 'ulovlig instruktion'.\n"\
"  Det kan v�re en fejl i den nye k�rselstids cpu-detekteringskode...\n"\
"  L�s venligst DOCS/bugreports.html.\n"
#define MSGTR_Exit_SIGILL \
"- MPlayer fejlede ved en 'ulovlig instruktion'.\n"\
" Dette sker oftest kun hvis du k�rer p� en cpu forskellig fra den\n"\
" mplayer var kompileret til.\n Unders�g venligst dette!\n"
#define MSGTR_Exit_SIGSEGV_SIGFPE \
"- MPlayer fejlede pga. ulovlig brug af CPU/FPU/RAM.\n"\
"  Rekompiler MPlayer med --enable-debug og lav en 'gdb' backtrace og\n"\
"  disassemling. For detaljer l�s venligst DOCS/bugreports.html#crash.b.\n"
#define MSGTR_Exit_SIGCRASH \
"- MPlayer fejlede. Dette skulle ikke ske.\n"\
"  Det kan v�re en fejl i MPlayer koden _eller_ i andre drivere _ eller_ i \n"\
"  den version af gcc du k�rer. Hvis du tror det er en fejl i MPlayer l�s da \n"\
"  venligst DOCS/bugreports.html og f�lg instruktionerne der. Vi kan ikke \n"
"  og vil ikke hj�lpe medmindre du f�lger instruktionerne n�r du rapporterer en mulig fejl.\n"

// mencoder.c:

#define MSGTR_MEncoderCopyright "(C) 2000-2003 Arpad Gereoffy ((se dokumentationen!)\n"
#define MSGTR_UsingPass3ControllFile "Benytter 3. pass kontrolfilen: %s\n"
#define MSGTR_MissingFilename "\nManglende filnavn!\n\n"
#define MSGTR_CannotOpenFile_Device "Kan ikke �bne fil/enhed\n"
#define MSGTR_ErrorDVDAuth "Fejl i DVD auth...\n"
#define MSGTR_CannotOpenDemuxer "Kan ikke �bne demuxer\n"
#define MSGTR_NoAudioEncoderSelected "\nIngen lydenkoder (-oac) valgt! V�lg en eller brug -nosound. Brug -oac for hj�lp !\n"
#define MSGTR_NoVideoEncoderSelected "\nIngen videoenkoder (-ovc) valgt! V�lg en eller brug, brug -ovc for hj�lp !\n"
#define MSGTR_InitializingAudioCodec "Initialiserer lydcodec...\n"
#define MSGTR_CannotOpenOutputFile "Kan ikke skrive til filen '%s'\n"
#define MSGTR_EncoderOpenFailed "Kunne ikke �bne enkoderen\n"
#define MSGTR_ForcingOutputFourcc "Tvinger udgang fourcc til %x [%.4s]\n"
#define MSGTR_WritingAVIHeader "Skriver AVI header...\n"
#define MSGTR_DuplicateFrames "\nduplikerer %d bille(r)!!!    \n"
#define MSGTR_SkipFrame "\nskip billede!!!    \n"
#define MSGTR_ErrorWritingFile "%s: fejl under skrivning af fil.\n"
#define MSGTR_WritingAVIIndex "\nSkriver AVI index...\n"
#define MSGTR_FixupAVIHeader "Fixup AVI header...\n"
#define MSGTR_RecommendedVideoBitrate "Anbefalet video bitrate for %s CD: %d\n"
#define MSGTR_VideoStreamResult "\nVideo stream: %8.3f kbit/s  (%d bps)  st�rrelse: %d bytes  %5.3f sek.  %d billeder\n"
#define MSGTR_AudioStreamResult "\nAudio stream: %8.3f kbit/s  (%d bps)  st�rrelse: %d bytes  %5.3f sek.\n"

// cfg-mencoder.h:

#define MSGTR_MEncoderMP3LameHelp "\n\n"\
" vbr=<0-4>     variabel bitrate metode\n"\
"                0: cbr\n"\
"                1: mt\n"\
"                2: rh(default)\n"\
"                3: abr\n"\
"                4: mtrh\n"\
"\n"\
" abr           middel bitrate\n"\
"\n"\
" cbr           konstant bitrate\n"\
"               Tvinger ogs� CBR mode enkoding p� efterf�lgende ABR pr�set modes\n"\
"\n"\
" br=<0-1024>   specificerer bitrate i kBit (kun CBR og ABR)\n"\
"\n"\
" q=<0-9>       kvalitet (0-h�jest, 9-lavest) (kun til VBR)\n"\
"\n"\
" aq=<0-9>      algoritmisk kvalitet (0-bedst/langsomst, 9-v�rst/hurtigst)\n"\
"\n"\
" ratio=<1-100> kompressionsrate\n"\
"\n"\
" vol=<0-10>    s�t lyd input forst�rkning\n"\
"\n"\
" mode=<0-3>    (standard: auto)\n"\
"                0: stereo\n"\
"                1: joint-stereo\n"\
"                2: flere kanals\n"\
"                3: mono\n"\
"\n"\
" padding=<0-2>\n"\
"                0: nej\n"\
"                1: alle\n"\
"                2: justeret\n"\
"\n"\
" fast          skift til hurtigere enkodning af efterf�lgende VBR pr�set modes,\n"\
"               svagt lavere kvalitet og h�jere bitrate.\n"\
"\n"\
" preset=<value> tilbyder de bedste kvalitets indstillinger.\n"\
"                 medium: VBR  enkodning,  god  kvalitet\n"\
"                 (150-180 kbps bitrate interval)\n"\
"                 standard:  VBR enkodning, h�j kvalitet\n"\
"                 (170-210 kbps bitrate interval)\n"\
"                 extreme: VBR enkodning, meget h�j kvalitet\n"\
"                 (200-240 kbps bitrate interval)\n"\
"                 insane:  CBR  enkodning, h�jeste pr�sets kvalitet\n"\
"                 (320 kbps bitrate)\n"\
"                 <8-320>: ABR enkodning ved middel kbps bitrate.\n\n"

// open.c, stream.c:
#define MSGTR_CdDevNotfound "CD-ROM Drev '%s' ikke fundet!\n"
#define MSGTR_ErrTrackSelect "Fejl i valg af VCD nummer!"
#define MSGTR_ReadSTDIN "L�ser fra stdin...\n"
#define MSGTR_UnableOpenURL "Ikke mulig at f� kontakt til adressen: %s\n"
#define MSGTR_ConnToServer "Koblet op til serveren: %s\n"
#define MSGTR_FileNotFound "Filen blev ikke fundet: '%s'\n"
#define MSGTR_SMBInitError "Kan ikke initialisere libsmbclient bibliotek: %d\n"
#define MSGTR_SMBFileNotFound "Kunne ikke �bne: '%s'\n"
#define MSGTR_SMBNotCompiled "MPlayer var ikke kompileret med SMB l�se-underst�ttelse\n"
#define MSGTR_CantOpenDVD "Kunne ikke �bne DVD drev: %s\n"
#define MSGTR_DVDwait "L�ser disken struktur, vent venligst...\n"
#define MSGTR_DVDnumTitles "Der er %d titler p� denne DVD.\n"
#define MSGTR_DVDinvalidTitle "Forkert DVD titel nummer: %d\n"
#define MSGTR_DVDnumChapters "Der er %d kapitler p� denne DVD titel.\n"
#define MSGTR_DVDinvalidChapter "Forkert DVD katalog nummmer: %d\n"
#define MSGTR_DVDnumAngles "Der er %d vinkler i denne DVD titel.\n"
#define MSGTR_DVDinvalidAngle "Forkert DVD vinkelnummer: %d\n"
#define MSGTR_DVDnoIFO "Kan ikke finde IFO filen for DVD titlen %d.\n"
#define MSGTR_DVDnoVOBs "Kan ikke �bne titlen VOBS (VTS_%02d_1.VOB).\n"
#define MSGTR_DVDopenOk "DVD korrekt �bnet!\n"

// demuxer.c, demux_*.c:
#define MSGTR_AudioStreamRedefined "Advarsel! Lyd-filens header %d er blevet omdefineret!\n"
#define MSGTR_VideoStreamRedefined "Advarsel! Video-filens header %d er blevet omdefineret!\n"
#define MSGTR_TooManyAudioInBuffer "\nDEMUXER: For mange (%d i %d bytes) lydpakker i bufferen!\n"
#define MSGTR_TooManyVideoInBuffer "\nDEMUXER: For mange (%d i %d bytes) videopakker i bufferen!\n"
#define MSGTR_MaybeNI "(m�ske afspiller du en 'non-interleaved' stream/fil ellers fejlede codec'et)\n"
#define MSGTR_SwitchToNi "\nDetekteret defekt .AVI - skifter til -ni!\n"
#define MSGTR_Detected_XXX_FileFormat "Detekterede %s filformat!\n"
#define MSGTR_DetectedAudiofile "Detekterede lydfil!\n"
#define MSGTR_NotSystemStream "Ikke MPEG System Stream format... (m�ske Transport Stream?)\n"
#define MSGTR_InvalidMPEGES "Ugyldig MPEG-ES stream??? Rapporter venligst dette, det kunne v�re en fejl i programmet :(\n"
#define MSGTR_FormatNotRecognized \
"============= Desv�rre, dette fil-format er ikke detekteret eller underst�ttet ===============\n"\
"=== Hvis denne fil er en AVI, ASF or MPEG stream, s� rapporter venligst dette, det kunne v�re en fejl i programmet :(===\n"
#define MSGTR_MissingVideoStream "Ingen videostream fundet!\n"
#define MSGTR_MissingAudioStream "Ingen lydstream fundet...  ->ingen lyd\n"
#define MSGTR_MissingVideoStreamBug "Manglende videostream!? Rapporter venligst dette, det kunne v�re en fejl i programmet :(\n"

#define MSGTR_DoesntContainSelectedStream "demux: filen indeholder ikke den valgte lyd- eller video-stream\n"

#define MSGTR_NI_Forced "Tvunget"
#define MSGTR_NI_Detected "Detekteret"
#define MSGTR_NI_Message "%s NON-INTERLEAVED AVI fil-format!\n"

#define MSGTR_UsingNINI "Bruger NON-INTERLEAVED (-ni), �delagt AVI fil-format!\n"
#define MSGTR_CouldntDetFNo "Kunne ikke finde antallet af billeder (for en absolutte s�gning)  \n"
#define MSGTR_CantSeekRawAVI "Kan ikke s�ge i r� .AVI stream! (manglende index, pr�v med -idx!)  \n"
#define MSGTR_CantSeekFile "Kan ikke s�ge i denne fil!  \n"
#define MSGTR_EncryptedVOB "Krypteret VOB fil (ikke kompileret med libcss support)! L�s filen DOCS/cd-dvd.html\n"
#define MSGTR_EncryptedVOBauth "Krypteret stream men autoriseringen blev ikke p�begyndt af dig!!\n"

#define MSGTR_MOVcomprhdr "MOV: Komprimeret header (endnu) ikke underst�ttet!\n"
#define MSGTR_MOVvariableFourCC "MOV: Advarsel! variablen FOURCC detekteret!?\n"
#define MSGTR_MOVtooManyTrk "MOV: Advarsel! For mange numre!"
#define MSGTR_FoundAudioStream "==> Fandt lydstream: %d\n"
#define MSGTR_FoundVideoStream "==> Fandt videostream: %d\n"
#define MSGTR_DetectedTV "Detekteret TV! ;-)\n"
#define MSGTR_ErrorOpeningOGGDemuxer "Ikke i stand til at �bne ogg demuxer\n"
#define MSGTR_ASFSearchingForAudioStream "ASF: S�ger efter lydstream (id:%d)\n"
#define MSGTR_CannotOpenAudioStream "Kan ikke �bne lydstream: %s\n"
#define MSGTR_CannotOpenSubtitlesStream "Kan ikke �bne undertekststream: %s\n"
#define MSGTR_OpeningAudioDemuxerFailed "Kan ikke �bne lyddemuxer: %s\n"
#define MSGTR_OpeningSubtitlesDemuxerFailed "Kunne ikke �bne undertekstdemuxer: %s\n"
#define MSGTR_TVInputNotSeekable "TV input er ikke s�gebart! (kan v�re du skulle skifte kanal ;))\n"
#define MSGTR_DemuxerInfoAlreadyPresent "Demuxer info %s allerede tilstede\n!"
#define MSGTR_ClipInfo "Klip info: \n"
#define MSGTR_LeaveTelecineMode "\ndemux_mpg: Progressiv f�lge detekteret, forbliver i 3:2 TELECINE mode\n"
#define MSGTR_EnterTelecineMode "\ndemux_mpg: 3:2 TELECINE detekteret, benytter inverse telecine fx. FPS �ndret til %5.3f!  \n"

// dec_video.c & dec_audio.c:
#define MSGTR_CantOpenCodec "kunne ikke �bne codec\n"
#define MSGTR_CantCloseCodec "kunne ikke afslutte codec\n"

#define MSGTR_MissingDLLcodec "FEJL: Kunne ikke �bne DirectShow codec: %s\n"
#define MSGTR_ACMiniterror "Kunne ikke loade/initialisere Win32/ACM LYD codec (manglende DLL fil?)\n"
#define MSGTR_MissingLAVCcodec "Kunne ikke finde codec '%s' i libavcodec...\n"

#define MSGTR_MpegNoSequHdr "MPEG: FATAL: EOF under s�gning efter sekvensheader\n"
#define MSGTR_CannotReadMpegSequHdr "FATAL: Kunne ikke l�se sekvensheader!\n"
#define MSGTR_CannotReadMpegSequHdrEx "FATAL: Kunne ikke l�se sekvensheaderudvidelse!\n"
#define MSGTR_BadMpegSequHdr "MPEG: Ugyldig sekvensheader!\n"
#define MSGTR_BadMpegSequHdrEx "MPEG: Ugyldig sekvensheaderudvidelse!\n"

#define MSGTR_ShMemAllocFail "Kunne ikke allokere delt ram\n"
#define MSGTR_CantAllocAudioBuf "Kunne ikke allokere lyd buffer\n"

#define MSGTR_UnknownAudio "Ukendt/manglende lyd format, sl�r over til ingen lyd\n"

#define MSGTR_UsingExternalPP "[PP] Benytter ekstern efterprocesseringsfilter, max q = %d\n"
#define MSGTR_UsingCodecPP "[PP] Benytter codec's efterprocessering, max q = %d\n"
#define MSGTR_VideoAttributeNotSupportedByVO_VD "Video egenskab '%s' ikke underst�ttet af den valgte vo & vd! \n"
#define MSGTR_VideoCodecFamilyNotAvailableStr "Anmodede videocodec familie [%s] (vfm=%s) ikke tilg�ngelig (aktiver f�r kompilering!)\n"
#define MSGTR_AudioCodecFamilyNotAvailableStr "Anmodede lydcodec familie [%s] (afm=%s) ikke tilg�ngelig (aktiver f�r kompilering!)\n"
#define MSGTR_OpeningVideoDecoder "�bner videodekoder: [%s] %s\n"
#define MSGTR_OpeningAudioDecoder "�bner audiodekoder: [%s] %s\n"
#define MSGTR_UninitVideoStr "deinit video: %s  \n"
#define MSGTR_UninitAudioStr "deinit audio: %s  \n"
#define MSGTR_VDecoderInitFailed "Videodekoder init fejlede :(\n"
#define MSGTR_ADecoderInitFailed "Lyddekoder init fejlede :(\n"
#define MSGTR_ADecoderPreinitFailed "Lyddekoder pr�init fejlede :(\n"
#define MSGTR_AllocatingBytesForInputBuffer "dec_audio: Allokerer %d bytes til input buffer\n"
#define MSGTR_AllocatingBytesForOutputBuffer "dec_audio: Allokerer %d + %d = %d bytes til output buffer\n"

// LIRC:
#define MSGTR_SettingUpLIRC "S�tter LIRC underst�ttelse op...\n"
#define MSGTR_LIRCdisabled "Du vil ikke v�re i stand til at bruge din fjernbetjening\n"
#define MSGTR_LIRCopenfailed "Ingen lirc underst�ttelse fundet!\n"
#define MSGTR_LIRCcfgerr "Kunne ikke l�se LIRC konfigurationsfil %s !\n"

// vf.c
#define MSGTR_CouldNotFindVideoFilter "Kunne ikke finde videofilter '%s'\n"
#define MSGTR_CouldNotOpenVideoFilter "Kunne ikke �bne videofilter '%s'\n"
#define MSGTR_OpeningVideoFilter "�bner videofilter: "
#define MSGTR_CannotFindColorspace "Kunne ikke finde f�lles colorspace, selv med 'scale' :(\n"

// vd.c
#define MSGTR_CodecDidNotSet "VDek: codec satte ikke sh->disp_w og sh->disp_h, pr�ver en anden l�sning!\n"
#define MSGTR_VoConfigRequest "VDek: vo konfig. anmodning - %d x %d (foretrukket csp: %s)\n"
#define MSGTR_CouldNotFindColorspace "Kunne ikke finde colorspace som matcher - pr�ver med -vop scale...\n"
#define MSGTR_MovieAspectIsSet "Film-Aspect er %.2f:1 - pr�skalerer for at rette film-aspect.\n"
#define MSGTR_MovieAspectUndefined "Film-Aspect er ikke defineret - ingen pr�skalering benyttet.\n"

// ====================== GUI messages/buttons ========================

#ifdef HAVE_NEW_GUI

// --- labels ---
#define MSGTR_About "Om"
#define MSGTR_FileSelect "V�lg fil ..."
#define MSGTR_SubtitleSelect "V�lg undertekst-fil ..."
#define MSGTR_OtherSelect "V�lg..."
#define MSGTR_AudioFileSelect "V�lg ekstern lydkanal ..."
#define MSGTR_FontSelect "V�lg font ..."
#define MSGTR_PlayList "PlayList"
#define MSGTR_Equalizer "Equalizer"
#define MSGTR_SkinBrowser "V�lg tema"
#define MSGTR_Network "Netv�rksstreaming ..."
#define MSGTR_Preferences "Indstillinger"
#define MSGTR_OSSPreferences "OSS driver konfiguration"
#define MSGTR_SDLPreferences "SDL driver konfiguration"
#define MSGTR_NoMediaOpened "medie ikke �bnet"
#define MSGTR_VCDTrack "VCD nummer %d"
#define MSGTR_NoChapter "ingen kapitel"
#define MSGTR_Chapter "kapitel %d"
#define MSGTR_NoFileLoaded "ingen fil indl�st"

// --- buttons ---
#define MSGTR_Ok "Ok"
#define MSGTR_Cancel "Annuller"
#define MSGTR_Add "Tilf�j"
#define MSGTR_Remove "Fjern"
#define MSGTR_Clear "Nulstil"
#define MSGTR_Config "Konfig"
#define MSGTR_ConfigDriver "Konfigurer driver"
#define MSGTR_Browse "Gennemse"

// --- error messages ---
#define MSGTR_NEMDB "Desv�rre, ikke nok ram til at vise bufferen."
#define MSGTR_NEMFMR "Desv�rre, ikke nok ram til at vise menuen."
#define MSGTR_IDFGCVD "Desv�rre, kunne ikke finde gui kompabitel video driver."
#define MSGTR_NEEDLAVCFAME "For at afspille ikke-mpeg filer med dit DXR3/H+ skal du kode filmen igen.\nVenligst aktiver lavc eller fame i DXR3/H+ configboxen."

// --- skin loader error messages
#define MSGTR_SKIN_ERRORMESSAGE "[tema] fejl i konfigurationsfilen til temaet p� linje %d: %s" 
#define MSGTR_SKIN_WARNING1 "[tema] advarsel i konfigurationsfilen til temaet p� linje %d: widget fundet men f�r \"section\" ikke fundet ( %s )"
#define MSGTR_SKIN_WARNING2 "[tema] advarsel i konfigurationsfilen til temaet p� linje %d: widget fundet men f�r \"subsection\" ikke fundet (%s)"
#define MSGTR_SKIN_WARNING3 "[tema] advarsel i konfigurationsfilen til temaet p� linje %d: denne undersektion er ikke underst�ttet af dette widget (%s)"
#define MSGTR_SKIN_BITMAP_16bit  "16 bits eller mindre ikke underst�ttet ( %s ).\n"
#define MSGTR_SKIN_BITMAP_FileNotFound  "filen ikke fundet ( %s )\n"
#define MSGTR_SKIN_BITMAP_BMPReadError "bmp l�se fejl ( %s )\n"
#define MSGTR_SKIN_BITMAP_TGAReadError "tga l�se fejl ( %s )\n"
#define MSGTR_SKIN_BITMAP_PNGReadError "png l�se fejl ( %s )\n"
#define MSGTR_SKIN_BITMAP_RLENotSupported "RLE pakket tga ikke supporteret ( %s )\n"
#define MSGTR_SKIN_BITMAP_UnknownFileType "ukendt filtype ( %s )\n"
#define MSGTR_SKIN_BITMAP_ConvertError "Fejl i 24 bit to 32 bit convertering ( %s )\n"
#define MSGTR_SKIN_BITMAP_UnknownMessage "ukendt besked: %s\n"
#define MSGTR_SKIN_FONT_NotEnoughtMemory "ikke nok ram\n"
#define MSGTR_SKIN_FONT_TooManyFontsDeclared "for mange skrifttyper specificeret\n"
#define MSGTR_SKIN_FONT_FontFileNotFound "skriftypefilen ikke fundet\n"
#define MSGTR_SKIN_FONT_FontImageNotFound "skrifttypebilled ikke fundet\n"
#define MSGTR_SKIN_FONT_NonExistentFontID "ikke eksisterende font ( %s )\n"
#define MSGTR_SKIN_UnknownParameter "ukendt parameter ( %s )\n"
#define MSGTR_SKINBROWSER_NotEnoughMemory "[temabrowser] ikke nok ram.\n"
#define MSGTR_SKIN_SKINCFG_SkinNotFound "Tema blev ikke fundet ( %s ).\n"
#define MSGTR_SKIN_SKINCFG_SkinCfgReadError "Tema config-fil l�se fejl ( %s ).\n"
#define MSGTR_SKIN_LABEL "Temaer:"

// --- gtk menus
#define MSGTR_MENU_AboutMPlayer "Om MPlayer"
#define MSGTR_MENU_Open "�ben ..."
#define MSGTR_MENU_PlayFile "Afspil fil ..."
#define MSGTR_MENU_PlayVCD "Afspil VCD ..."
#define MSGTR_MENU_PlayDVD "Afspil DVD ..."
#define MSGTR_MENU_PlayURL "Afspil URL ..."
#define MSGTR_MENU_LoadSubtitle "Indl�s undertekst ..."
#define MSGTR_MENU_DropSubtitle "Drop undertekst ..."
#define MSGTR_MENU_LoadExternAudioFile "Indl�s extern lyd fil ..."
#define MSGTR_MENU_Playing "Afspilning"
#define MSGTR_MENU_Play "Afspil"
#define MSGTR_MENU_Pause "Pause"
#define MSGTR_MENU_Stop "Stop"
#define MSGTR_MENU_NextStream "N�ste stream"
#define MSGTR_MENU_PrevStream "Forrige stream"
#define MSGTR_MENU_Size "St�rrelse"
#define MSGTR_MENU_NormalSize "Normal st�rrelse"
#define MSGTR_MENU_DoubleSize "Double st�rrelse"
#define MSGTR_MENU_FullScreen "Fuld sk�rm"
#define MSGTR_MENU_DVD "DVD"
#define MSGTR_MENU_VCD "VCD"
#define MSGTR_MENU_PlayDisc "Afspil disk ..."
#define MSGTR_MENU_ShowDVDMenu "Vis DVD menu"
#define MSGTR_MENU_Titles "Titler"
#define MSGTR_MENU_Title "Titel %2d"
#define MSGTR_MENU_None "(ingen)"
#define MSGTR_MENU_Chapters "Kapitler"
#define MSGTR_MENU_Chapter "Kapitel %2d"
#define MSGTR_MENU_AudioLanguages "Lyd sprog"
#define MSGTR_MENU_SubtitleLanguages "Undertekst sprog"
#define MSGTR_MENU_PlayList "Afspilningslisten"
#define MSGTR_MENU_SkinBrowser "V�lg udseende"
#define MSGTR_MENU_Preferences "Indstillinger"
#define MSGTR_MENU_Exit "Forlad ..."
#define MSGTR_MENU_Mute "Mute"
#define MSGTR_MENU_Original "Original"
#define MSGTR_MENU_AspectRatio "St�rrelsesforhold"
#define MSGTR_MENU_AudioTrack "Lydspor"
#define MSGTR_MENU_Track "Spor %d"
#define MSGTR_MENU_VideoTrack "Videospor"

// --- equalizer
#define MSGTR_EQU_Audio "Lyd"
#define MSGTR_EQU_Video "Video"
#define MSGTR_EQU_Contrast "Kontrast: "
#define MSGTR_EQU_Brightness "Lysstyrke: "
#define MSGTR_EQU_Hue "Hue: "
#define MSGTR_EQU_Saturation "Saturation: "
#define MSGTR_EQU_Front_Left "Venstre Front"
#define MSGTR_EQU_Front_Right "H�jre Front"
#define MSGTR_EQU_Back_Left "Venstre Bagh�jtaler"
#define MSGTR_EQU_Back_Right "H�jre Bagh�jtaler"
#define MSGTR_EQU_Center "Center"
#define MSGTR_EQU_Bass "Bass"
#define MSGTR_EQU_All "Alle"
#define MSGTR_EQU_Channel1 "Kanal 1:"
#define MSGTR_EQU_Channel2 "Kanal 2:"
#define MSGTR_EQU_Channel3 "Kanal 3:"
#define MSGTR_EQU_Channel4 "Kanal 4:"
#define MSGTR_EQU_Channel5 "Kanal 5:"
#define MSGTR_EQU_Channel6 "Kanal 6:"

// --- playlist
#define MSGTR_PLAYLIST_Path "Sti"
#define MSGTR_PLAYLIST_Selected "Valgte filer"
#define MSGTR_PLAYLIST_Files "Filer"
#define MSGTR_PLAYLIST_DirectoryTree "Katalog tr�"

// --- preferences
#define MSGTR_PREFERENCES_Audio "Lyd"
#define MSGTR_PREFERENCES_Video "Video"
#define MSGTR_PREFERENCES_SubtitleOSD "undertekster og OSD"
#define MSGTR_PREFERENCES_Codecs "Codecs & demuxer"
#define MSGTR_PREFERENCES_Misc "Misc"

#define MSGTR_PREFERENCES_None "Ingen"
#define MSGTR_PREFERENCES_AvailableDrivers "Tilg�ngelige drivere:"
#define MSGTR_PREFERENCES_DoNotPlaySound "Afspil ikke lyd"
#define MSGTR_PREFERENCES_NormalizeSound "Normaliser lydstyrke"
#define MSGTR_PREFERENCES_EnEqualizer "Anvend equalizer"
#define MSGTR_PREFERENCES_ExtraStereo "Anvend extra stereo"
#define MSGTR_PREFERENCES_Coefficient "Koefficient:"
#define MSGTR_PREFERENCES_AudioDelay "Lydforsinkelse"
#define MSGTR_PREFERENCES_Audio "Lyd"
#define MSGTR_PREFERENCES_DoubleBuffer "Anvend double buffering"
#define MSGTR_PREFERENCES_DirectRender "Anvend 'direct rendering'"
#define MSGTR_PREFERENCES_FrameDrop "Anvend billed-skip"
#define MSGTR_PREFERENCES_HFrameDrop "Anvend meget billed-skip ( farlig )"
#define MSGTR_PREFERENCES_Flip "Flip billede"
#define MSGTR_PREFERENCES_Panscan "Panscan: "
#define MSGTR_PREFERENCES_Video "Video"
#define MSGTR_PREFERENCES_OSDTimer "Statuslinje og indikator"
#define MSGTR_PREFERENCES_OSDProgress "Kun statuslinje"
#define MSGTR_PREFERENCES_OSDTimerPercentageTotalTime "Timer, procent og total tid"
#define MSGTR_PREFERENCES_Subtitle "Undertekst:"
#define MSGTR_PREFERENCES_SUB_Delay "Forsinkelse: "
#define MSGTR_PREFERENCES_SUB_FPS "FPS:"
#define MSGTR_PREFERENCES_SUB_POS "Position: "
#define MSGTR_PREFERENCES_SUB_AutoLoad "Deaktiver automatisk undertekster"
#define MSGTR_PREFERENCES_SUB_Unicode "Unicode undertekst"
#define MSGTR_PREFERENCES_SUB_MPSUB "Konverter en given undertekst til MPlayer's undertekst format"
#define MSGTR_PREFERENCES_SUB_SRT "Konverter den angivne undertekst til et tidsbaseret SubViewer (SRT) format"
#define MSGTR_PREFERENCES_SUB_Overlap "sl� (til/fra) undertekst overlapning"
#define MSGTR_PREFERENCES_Font "Font:"
#define MSGTR_PREFERENCES_FontFactor "Font factor:"
#define MSGTR_PREFERENCES_PostProcess "Anvend efterprocesseringsfilter"
#define MSGTR_PREFERENCES_AutoQuality "Auto kvalitet: "
#define MSGTR_PREFERENCES_NI "Benyt non-interleaved AVI parser"
#define MSGTR_PREFERENCES_IDX "Genopbyg index tabel, hvis n�dvendig"
#define MSGTR_PREFERENCES_VideoCodecFamily "Video codec familie:"
#define MSGTR_PREFERENCES_AudioCodecFamily "Lydcodec familie:"
#define MSGTR_PREFERENCES_FRAME_OSD_Level "OSD level"
#define MSGTR_PREFERENCES_FRAME_Subtitle "Undertekst"
#define MSGTR_PREFERENCES_FRAME_Font "Skriftype"
#define MSGTR_PREFERENCES_FRAME_PostProcess "Efterprocesseringsfilter"
#define MSGTR_PREFERENCES_FRAME_CodecDemuxer "Codec & demuxer"
#define MSGTR_PREFERENCES_FRAME_Cache "Cache"
#define MSGTR_PREFERENCES_FRAME_Misc "Misc"
#define MSGTR_PREFERENCES_OSS_Device "Enhed:"
#define MSGTR_PREFERENCES_OSS_Mixer "Mixer:"
#define MSGTR_PREFERENCES_SDL_Driver "Driver:"
#define MSGTR_PREFERENCES_Message "Husk, nogle funktioner kr�ver at MPlayer bliver genstartet for at de virker."
#define MSGTR_PREFERENCES_DXR3_VENC "Video enkoder:"
#define MSGTR_PREFERENCES_DXR3_LAVC "Brug LAVC (ffmpeg)"
#define MSGTR_PREFERENCES_DXR3_FAME "Brug FAME"
#define MSGTR_PREFERENCES_FontEncoding1 "Unicode"
#define MSGTR_PREFERENCES_FontEncoding2 "Vesteurop�riske sprog (ISO-8859-1)"
#define MSGTR_PREFERENCES_FontEncoding3 "Vesteurop�riske sprog med euro (ISO-8859-15)"
#define MSGTR_PREFERENCES_FontEncoding4 "�st-/Centraleurop�riske sprog (ISO-8859-2)"
#define MSGTR_PREFERENCES_FontEncoding5 "Esperanto, Galician, Maltisk, Tyrkisk (ISO-8859-3)"
#define MSGTR_PREFERENCES_FontEncoding6 "Gammel Baltisk tegns�t (ISO-8859-4)"
#define MSGTR_PREFERENCES_FontEncoding7 "Cyrillisk (ISO-8859-5)"
#define MSGTR_PREFERENCES_FontEncoding8 "Arabisk (ISO-8859-6)"
#define MSGTR_PREFERENCES_FontEncoding9 "Moderne Gr�sk (ISO-8859-7)"
#define MSGTR_PREFERENCES_FontEncoding10 "Tyrkisk (ISO-8859-9)"
#define MSGTR_PREFERENCES_FontEncoding11 "Baltisk (ISO-8859-13)"
#define MSGTR_PREFERENCES_FontEncoding12 "Keltisk (ISO-8859-14)"
#define MSGTR_PREFERENCES_FontEncoding13 "Hebr�isk tegns�t (ISO-8859-8)"
#define MSGTR_PREFERENCES_FontEncoding14 "Russisk (KOI8-R)"
#define MSGTR_PREFERENCES_FontEncoding15 "Ukrainsk, Belarusian (KOI8-U/RU)"
#define MSGTR_PREFERENCES_FontEncoding16 "Simplificeret kinesisk tegns�t (CP936)"
#define MSGTR_PREFERENCES_FontEncoding17 "Traditionel kinesisk tegns�t (BIG5)"
#define MSGTR_PREFERENCES_FontEncoding18 "Japansk tegns�t (SHIFT-JIS)"
#define MSGTR_PREFERENCES_FontEncoding19 "Koreansk tegns�t (CP949)"
#define MSGTR_PREFERENCES_FontEncoding20 "Thai tegns�t (CP874)"
#define MSGTR_PREFERENCES_FontEncoding21 "Cyrillic Windows (CP1251)"
#define MSGTR_PREFERENCES_FontNoAutoScale "Ingen autoskalering"
#define MSGTR_PREFERENCES_FontPropWidth "Proportional med film bredde"
#define MSGTR_PREFERENCES_FontPropHeight "Proportional med film h�jde"
#define MSGTR_PREFERENCES_FontPropDiagonal "Proportional med film diagonalt"
#define MSGTR_PREFERENCES_FontEncoding "Enkodning:"
#define MSGTR_PREFERENCES_FontBlur "Uskarp:"
#define MSGTR_PREFERENCES_FontOutLine "Outline:"
#define MSGTR_PREFERENCES_FontTextScale "Text skalering:"
#define MSGTR_PREFERENCES_FontOSDScale "OSD skalering:"
#define MSGTR_PREFERENCES_Cache "Cache p�/af"
#define MSGTR_PREFERENCES_LoadFullscreen "Start i fullsk�rm"
#define MSGTR_PREFERENCES_CacheSize "Cache st�rrelse: "
#define MSGTR_PREFERENCES_SaveWinPos "Gem vinduets position"
#define MSGTR_PREFERENCES_XSCREENSAVER "Stop XScreenSaver"
#define MSGTR_PREFERENCES_PlayBar "Anvend afspilningsbar"
#define MSGTR_PREFERENCES_AutoSync "AutoSynk. p�/af"
#define MSGTR_PREFERENCES_AutoSyncValue "Autosynk.: "
#define MSGTR_PREFERENCES_CDROMDevice "CD-ROM enhed:"
#define MSGTR_PREFERENCES_DVDDevice "DVD enhed:"
#define MSGTR_PREFERENCES_FPS "Film FPS:"
#define MSGTR_PREFERENCES_ShowVideoWindow "Vis video vindue n�r inaktiv"

#define MSGTR_ABOUT_UHU "GUI udvikling sponsereret af UHU Linux\n"
#define MSGTR_ABOUT_CoreTeam "   MPlayer kernen:\n"
#define MSGTR_ABOUT_AdditionalCoders "   Yderligere kodere:\n"
#define MSGTR_ABOUT_MainTesters "   Hovedtestere:\n"

// --- messagebox
#define MSGTR_MSGBOX_LABEL_FatalError "fatal fejl ..."
#define MSGTR_MSGBOX_LABEL_Error "fejl ..."
#define MSGTR_MSGBOX_LABEL_Warning "advarsel ..." 

#endif
