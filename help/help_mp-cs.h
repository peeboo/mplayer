// Translated by:  Jiri Svoboda, jiri.svoboda@seznam.cz
// Updated by:     Tomas Blaha,  tomas.blaha at kapsa.cz
//                 Jiri Heryan
// Synced to 18818
// ========================= MPlayer help ===========================

#ifdef HELP_MP_DEFINE_STATIC
static char help_text[]=
"Pou�it�:          mplayer [volby] [url|cesta/]jm�no_souboru\n"
"\n"
"Z�kladn� volby: (�pln� seznam najdete v manu�lov� str�nce)\n"
" -vo <rozhran�>   vybere v�stupn� video rozhran� (seznam: -vo help)\n"
" -ao <rozhran�>   vybere v�stupn� audio rozhran� (seznam: -ao help)\n"
#ifdef HAVE_VCD
" vcd://<�_stopy>  p�ehraje (S)VCD (Super Video CD) stopu (z nep�ipojen�ho\n"
"                  za��zen�)\n"
#endif
#ifdef USE_DVDREAD
" dvd://<�_tit>    p�ehraje DVD titul ze za��zen� (mechaniky), m�sto ze souboru\n"
" -alang/-slang    zvol� jazyk zvuku/titulk� na DVD (dvouznakov� k�d zem�)\n"
#endif
" -ss <pozice>     p�evine na zadanou pozici (sekundy nebo hh:mm:ss)\n"
" -nosound         p�ehr�v�n� beze zvuku\n"
" -fs              celoobrazovkov� p�ehr�v�n� (nebo -vm -zoom, viz manu�l)\n"
" -x <x> -y <y>    rozli�en� obrazu (pro pou�it� s -vm nebo -zoom)\n"
" -sub <soubor>    zvol� soubor s titulky (viz tak� -subfps, -subdelay)\n"
" -playlist <soubor> ur�� soubor s playlistem\n"
" -vid x -aid y    vybere video (x) a audio (y) proud pro p�ehr�n�\n"
" -fps x -srate y  zm�nit video (x fps) a audio (y Hz) frekvence\n"
" -pp <kvalita>    aktivovat postprocessing (podrobnosti v manu�lu)\n"
" -framedrop       povolit zahazov�n� sn�mk� (pro pomal� stroje)\n"
"\n"
"Z�kladn� kl�vesy: (�pln� seznam je v manu�lu, viz tak� input.conf)\n"
" <-  nebo  ->     p�ev�jen� vzad/vp�ed o 10 sekund\n"
" dol� �i nahoru   p�ev�jen� vzad/vp�ed o  1 minutu\n"
" pgdown �i pgup   p�ev�jen� vzad/vp�ed o 10 minut\n"
" < nebo >         posun na p�edchoz�/dal�� soubor v playlistu\n"
" p nebo mezern�k  pozastav� p�ehr�v�n� (pokra�uje po stisku jak�koliv kl�vesy)\n"
" q nebo ESC       konec p�ehr�v�n� a ukon�en� programu\n"
" + nebo -         uprav� zpo�d�n� zvuku v kroc�ch +/- 0,1 sekundy\n"
" o                cyklick� zm�na re�imu OSD: nic / pozice / pozice a �as\n"
" * nebo /         p�id� nebo ubere PCM hlasitost\n"
" x nebo z         uprav� zpo�d�n� titulk� v kroc�ch +/- 0,1 sekundy\n"
" r nebo t         uprav� polohu titulk� nahoru/dol�, viz tak� -vf expand\n"
"\n"
" * * * V MAN STR�NCE NAJDETE PODROBNOSTI, DAL�� VOLBY A KL�VESY * * *\n"
"\n";
#endif

// libmpcodecs/ad_dvdpcm.c:
#define MSGTR_SamplesWanted "Vzorky tohoto form�tu jsou pot�eba pro zlep�en� podpory. Kontaktujte pros�m\n v�vojov� t�m.\n"

// ========================= MPlayer messages ===========================

// mplayer.c:

#define MSGTR_Exiting "\nKon��m...\n"
#define MSGTR_ExitingHow "\nKon��m... (%s)\n"
#define MSGTR_Exit_quit "Konec"
#define MSGTR_Exit_eof "Konec souboru"
#define MSGTR_Exit_error "Kritick� chyba"
#define MSGTR_IntBySignal "\nMPlayer p�eru�en sign�lem %d v modulu %s.\n"
#define MSGTR_NoHomeDir "Nemohu nal�zt dom�c� adres��.\n"
#define MSGTR_GetpathProblem "Nastal probl�m s get_path(\"config\")\n"
#define MSGTR_CreatingCfgFile "Vytv���m konfigura�n� soubor: %s\n"
#define MSGTR_CopyCodecsConf "(Zkop�rujte/nalinkujte etc/codecs.conf ze zdrojov�ch k�d� MPlayeru do ~/.mplayer/codecs.conf)\n"
#define MSGTR_BuiltinCodecsConf "Pou��v�m zabudovan� v�choz� codecs.conf.\n"
#define MSGTR_CantLoadFont "Nemohu na��st font: %s\n"
#define MSGTR_CantLoadSub "Nemohu na��st titulky: %s\n"
#define MSGTR_DumpSelectedStreamMissing "dump: Kritick� chyba: Chyb� po�adovan� datov� proud!\n"
#define MSGTR_CantOpenDumpfile "Nelze otev��t soubor pro dump.\n"
#define MSGTR_CoreDumped "J�dro odhozeno ;)\n"
#define MSGTR_FPSnotspecified "�daj o FPS v hlavi�ce souboru je �patn� nebo chyb�, pou�ijte volbu -fps!\n"
#define MSGTR_TryForceAudioFmtStr "Pokou��m se vynutit rodinu audiokodeku %s...\n"
#define MSGTR_CantFindAudioCodec "Nemohu nal�zt kodek pro audio form�t 0x%X!\n"
#define MSGTR_RTFMCodecs "P�e�t�te si DOCS/HTML/en/codecs.html!\n"
#define MSGTR_TryForceVideoFmtStr "Pokou��m se vynutit rodinu videokodeku %s...\n"
#define MSGTR_CantFindVideoCodec "Nemohu nal�zt kodek pro vybran� -vo a video form�t 0x%X.\n"
#define MSGTR_CannotInitVO "Kritick� chyba: Nemohu inicializovat video rozhran�!\n"
#define MSGTR_CannotInitAO "Nepoda�ilo se otev��t/inicializovat audio za��zen� -> nebude zvuk.\n"
#define MSGTR_StartPlaying "Za��n�m p�ehr�vat...\n"

#define MSGTR_SystemTooSlow "\n\n"\
"         ***********************************************************\n"\
"         ****  V� syst�m je p��li� POMAL� pro toto p�ehr�v�n�! ****\n"\
"         ***********************************************************\n\n"\
"Mo�n� p���iny, probl�my a �e�en�:\n"\
"- Nej�ast�j��: �patn�/chybn� _zvukov�_ ovlada�!\n"\
"  - Zkuste -ao sdl nebo pou�ijte OSS emulaci z ALSA.\n"\
"  - Pohrajte si s r�zn�mi hodnotami -autosync, pro za��tek t�eba 30.\n"\
"- Pomal� obrazov� v�stup\n"\
"  - Zkuste jin� -vo ovlada� (seznam: -vo help) nebo zkuste -framedrop!\n"\
"- Pomal� CPU\n"\
"  - Nezkou�ejte p�ehr�t velk� DVD/DivX na pomal� CPU! Zkuste n�kter� lavdopts,\n"\
"    jako -vfm ffmpeg -lavdopts lowres=1:fast:skiploopfilter=all.\n"\
"- Po�kozen� soubor.\n"\
"  - Zkuste r�zn� kombinace voleb -nobps -ni -forceidx -mc 0.\n"\
"- P�ehr�v�te z pomal�ho m�dia (NFS/SMB, DVD, VCD, atd.)\n"\
"  - Zkuste -cache 8192.\n"\
"- Pou��v�te -cache pro neprokl�dan� AVI soubory?\n"\
"  - Zkuste -nocache.\n"\
"Tipy na vylad�n� a zrychlen� najdete v DOCS/HTML/en/devices.html.\n"\
"Pokud nic z toho nepom��e, p�e�t�te si DOCS/HTML/en/bugreports.html.\n\n"

#define MSGTR_NoGui "MPlayer byl p�elo�en BEZ podpory GUI.\n"
#define MSGTR_GuiNeedsX "GUI MPlayeru vy�aduje X11.\n"
#define MSGTR_Playing "\nP�ehr�v�m %s\n"
#define MSGTR_NoSound "Audio: ��dn� zvuk\n"
#define MSGTR_FPSforced "FPS vynuceno na hodnotu %5.3f  (vyn. �as: %5.3f)\n"
#define MSGTR_CompiledWithRuntimeDetection "P�elo�eno s detekc� CPU za b�hu."
#define MSGTR_CompiledWithCPUExtensions "P�elo�eno pro CPU x86 s roz���en�mi:"
#define MSGTR_AvailableVideoOutputDrivers "Dostupn� video rozhran�:\n"
#define MSGTR_AvailableAudioOutputDrivers "Dostupn� audio rozhran�:\n"
#define MSGTR_AvailableAudioCodecs "Dostupn� audio kodeky:\n"
#define MSGTR_AvailableVideoCodecs "Dostupn� video kodeky:\n"
#define MSGTR_AvailableAudioFm "Dostupn� (zakompilovan�) rodiny audio kodek�/ovlada��:\n"
#define MSGTR_AvailableVideoFm "Dostupn� (zakompilovan�) rodiny video kodek�/ovlada��:\n"
#define MSGTR_AvailableFsType "Dostupn� re�imy zm�ny hladiny p�i celoobrazovkov�m zobrazen�:\n"
#define MSGTR_UsingRTCTiming "Pro �asov�n� pou�ity linuxov� hardwarov� RTC (%ldHz).\n"
#define MSGTR_CannotReadVideoProperties "Video: Nelze p�e��st vlastnosti.\n"
#define MSGTR_NoStreamFound "Nenalezen ��dn� datov� proud.\n"
#define MSGTR_ErrorInitializingVODevice "Chyba p�i otev�r�n�/inicializaci vybran�ho video_out (-vo) za��zen�.\n"
#define MSGTR_ForcedVideoCodec "Vynucen video kodek: %s\n"
#define MSGTR_ForcedAudioCodec "Vynucen audio kodek: %s\n"
#define MSGTR_Video_NoVideo "Video: ��dn� video\n"
#define MSGTR_NotInitializeVOPorVO "\nKritick� chyba: Nemohu inicializovat video filtry (-vf) nebo video v�stup (-vo)!\n"
#define MSGTR_Paused "\n===== POZASTAVENO =====\r"
#define MSGTR_PlaylistLoadUnable "\nNemohu na��st playlist %s.\n"
#define MSGTR_Exit_SIGILL_RTCpuSel \
"- MPlayer havaroval kv�li 'Illegal Instruction'.\n"\
"  To m��e b�t chyba v k�du pro rozpozn�n� CPU za b�hu...\n"\
"  Pros�m, p�e�t�te si DOCS/HTML/en/bugreports.html.\n"
#define MSGTR_Exit_SIGILL \
"- MPlayer havaroval kv�li 'Illegal Instruction'.\n"\
"  To se obvykle st�v�, kdy� se ho pokus�te spustit na CPU odli�n�m, ne� pro kter�\n"\
"  byl p�elo�en/optimalizov�n.\n  Ov��te si to!\n"
#define MSGTR_Exit_SIGSEGV_SIGFPE \
"- MPlayer havaroval kv�li �patn�mu pou�it� CPU/FPU/RAM.\n"\
"  P�elo�te MPlayer s volbou --enable-debug , prove�te 'gdb' backtrace\n"\
"  a disassembly. Detaily najdete v DOCS/HTML/en/bugreports_what.html#bugreports_crash.\n"
#define MSGTR_Exit_SIGCRASH \
"- MPlayer havaroval. To by se nem�lo st�t.\n"\
"  M��e to b�t chyba v k�du MPlayeru _nebo_ ve va�ich ovlada��ch _nebo_ ve verzi\n"\
"  va�eho gcc. Pokud si mysl�te, �e je to chyba MPlayeru, p�e�t�te si, pros�m,\n"\
"  DOCS/HTML/en/bugreports.html a pokra�ujte podle tam uveden�ho n�vodu. My v�m nem��eme\n"\
"  pomoci, pokud tyto informace neuvedete p�i ohla�ov�n� mo�n� chyby.\n"
#define MSGTR_LoadingConfig "Na��t�m konfiguraci '%s'\n"
#define MSGTR_AddedSubtitleFile "SUB: P�id�n soubor s titulky (%d): %s\n"
#define MSGTR_RemovedSubtitleFile "SUB: Odebr�n soubor s titulky (%d): %s\n"
#define MSGTR_ErrorOpeningOutputFile "Chyba p�i otev�r�n� souboru [%s] pro z�pis!\n"
#define MSGTR_CommandLine "P��kazov� ��dek:"
#define MSGTR_RTCDeviceNotOpenable "Selhalo otev�en� %s: %s (by m�lo b�t �iteln� u�ivatelem.)\n"
#define MSGTR_LinuxRTCInitErrorIrqpSet "Chyba inicializace Linuxov�ch RTC v ioctl (rtc_irqp_set %lu): %s\n"
#define MSGTR_IncreaseRTCMaxUserFreq "Zkuste p�idat \"echo %lu > /proc/sys/dev/rtc/max-user-freq\" do startovac�ch\n skript� va�eho syst�mu.\n"
#define MSGTR_LinuxRTCInitErrorPieOn "Chyba inicializace Linuxov�ch RTC v ioctl (rtc_pie_on): %s\n"
#define MSGTR_UsingTimingType "Pou��v�m %s �asov�n�.\n"
#define MSGTR_NoIdleAndGui "Volbu -idle nelze pou��t pro GMPlayer.\n"
#define MSGTR_MenuInitialized "Menu inicializov�no: %s\n"
#define MSGTR_MenuInitFailed "Selhala inicializace menu.\n"
#define MSGTR_Getch2InitializedTwice "VAROV�N�: getch2_init vol�na dvakr�t!\n"
#define MSGTR_DumpstreamFdUnavailable "Nemohu ulo�it (dump) tento proud - ��dn� deskriptor souboru nen� dostupn�.\n"
#define MSGTR_FallingBackOnPlaylist "Ustupuji od pokusu o zpracov�n� playlistu %s...\n"
#define MSGTR_CantOpenLibmenuFilterWithThisRootMenu "Nemohu otev��t video filtr libmenu s ko�enov�m menu %s.\n"
#define MSGTR_AudioFilterChainPreinitError "Chyba p�i p�edinicializaci �et�zce audio filtr�!\n"
#define MSGTR_LinuxRTCReadError "Chyba p�i �ten� z Linuxov�ch RTC: %s\n"
#define MSGTR_SoftsleepUnderflow "Varov�n�! Podte�en� softsleep!\n"
#define MSGTR_DvdnavNullEvent "Nedefinovan� DVDNAV ud�lost?!\n"
#define MSGTR_DvdnavHighlightEventBroken "DVDNAV ud�lost: Vadn� zv�raz�ov�n� ud�lost�\n"
#define MSGTR_DvdnavEvent "DVDNAV ud�lost: %s\n"
#define MSGTR_DvdnavHighlightHide "DVDNAV ud�lost: Highlight Hide\n"
#define MSGTR_DvdnavStillFrame "######################################## DVDNAV ud�lost: Stoj�c� sn�mek: %d sek.\n"
#define MSGTR_DvdnavNavStop "DVDNAV ud�lost: Nav Stop\n"
#define MSGTR_DvdnavNavNOP "DVDNAV ud�lost: Nav NOP\n"
#define MSGTR_DvdnavNavSpuStreamChangeVerbose "DVDNAV ud�lost: Nav Zm�na SPU proudu: fyz: %d/%d/%d logick�: %d\n"
#define MSGTR_DvdnavNavSpuStreamChange "DVDNAV ud�lost: Nav Zm�na SPU proudu: fyz: %d logick�: %d\n"
#define MSGTR_DvdnavNavAudioStreamChange "DVDNAV ud�lost: Nav Zm�na audio proudu: fyz: %d logick�: %d\n"
#define MSGTR_DvdnavNavVTSChange "DVDNAV ud�lost: Nav Zm�na VTS\n"
#define MSGTR_DvdnavNavCellChange "DVDNAV ud�lost: Nav Cell Change\n"
#define MSGTR_DvdnavNavSpuClutChange "DVDNAV ud�lost: Nav Zm�na SPU CLUT\n"
#define MSGTR_DvdnavNavSeekDone "DVDNAV ud�lost: Nav P�ev�jen� Dokon�eno\n"
#define MSGTR_MenuCall "Vol�n� menu\n"

#define MSGTR_EdlOutOfMem "Nelze alokovat dostatek pam�ti pro vlo�en� EDL dat.\n"
#define MSGTR_EdlRecordsNo "Na��t�m %d EDL akc�.\n"
#define MSGTR_EdlQueueEmpty "Ve�ker� EDL akce ji� byly provedeny.\n"
#define MSGTR_EdlCantOpenForWrite "Nelze otev��t EDL soubor [%s] pro z�pis.\n"
#define MSGTR_EdlCantOpenForRead "Nelze otev��t EDL soubor [%s] pro �ten�.\n"
#define MSGTR_EdlNOsh_video "EDL nelze pou��t bez videa, vyp�n�m.\n"
#define MSGTR_EdlNOValidLine "Chybn� EDL na ��dku: %s\n"
#define MSGTR_EdlBadlyFormattedLine "�patn� form�tovan� EDL na ��dku [%d], zahazuji.\n"
#define MSGTR_EdlBadLineOverlap "Posledn� stop zna�ka byla [%f]; dal�� start je [%f].\n"\
"Vstupy mus� b�t v chronologick�m po�ad� a nesm� se p�ekr�vat. Zahazuji.\n"
#define MSGTR_EdlBadLineBadStop "�asov� zna�ka stop m� b�t za zna�kou start.\n"

// mplayer.c OSD

#define MSGTR_OSDenabled "zapnuto"
#define MSGTR_OSDdisabled "vypnuto"
#define MSGTR_OSDChannel "Kan�l: %s"
#define MSGTR_OSDSubDelay "Zpo�d�n� tit: %d ms"
#define MSGTR_OSDSpeed "Rychlost: x %6.2f"
#define MSGTR_OSDosd "OSD: %s"

// property values
#define MSGTR_Enabled "zapnuto"
#define MSGTR_EnabledEdl "zapnuto (EDL)"
#define MSGTR_Disabled "vypnuto"
#define MSGTR_HardFrameDrop "intenzivn�"
#define MSGTR_Unknown "nezn�m�"
#define MSGTR_Bottom "dol�"
#define MSGTR_Center "na st�ed"
#define MSGTR_Top "nahoru"

// osd bar names
#define MSGTR_Volume "Hlasitost"
#define MSGTR_Panscan "Panscan"
#define MSGTR_Gamma "Gama"
#define MSGTR_Brightness "Jas"
#define MSGTR_Contrast "Kontrast"
#define MSGTR_Saturation "Sytost"
#define MSGTR_Hue "Odst�n"

// property state
#define MSGTR_MuteStatus "Zti�en�: %s"
#define MSGTR_AVDelayStatus "A-V odchylka: %s"
#define MSGTR_OnTopStatus "Z�stat navrchu: %s"
#define MSGTR_RootwinStatus "Ko�enov� okno: %s"
#define MSGTR_BorderStatus "R�me�ek: %s"
#define MSGTR_FramedroppingStatus "Zahazov�n� sn�mk�: %s"
#define MSGTR_VSyncStatus "Vertik�ln� synchronizace: %s"
#define MSGTR_SubSelectStatus "Titulky: %s"
#define MSGTR_SubPosStatus "Um�st�n� titulk�: %s/100"
#define MSGTR_SubAlignStatus "Zarovn�n� titulk�: %s"
#define MSGTR_SubDelayStatus "Zpo�d�n� titulk�: %s"
#define MSGTR_SubVisibleStatus "Titulky: %s"
#define MSGTR_SubForcedOnlyStatus "Pouze vynucen� titulky: %s"
 
// mencoder.c:

#define MSGTR_UsingPass3ControlFile "��dic� soubor pro t��pr�chodov� re�im: %s\n"
#define MSGTR_MissingFilename "\nChyb� jm�no souboru.\n\n"
#define MSGTR_CannotOpenFile_Device "Nelze otev��t soubor/za��zen�.\n"
#define MSGTR_CannotOpenDemuxer "Nelze otev��t demuxer.\n"
#define MSGTR_NoAudioEncoderSelected "\nNebyl vybr�n audio enkod�r (-oac). N�jak� vyberte (viz -oac help) nebo pou�ijte -nosound.\n"
#define MSGTR_NoVideoEncoderSelected "\nNebyl vybr�n video enkod�r (-ovc). N�jak� vyberte (viz  -ovc help).\n"
#define MSGTR_CannotOpenOutputFile "Nelze otev��t v�stupn� soubor '%s'\n"
#define MSGTR_EncoderOpenFailed "Selhalo spu�t�n� enkod�ru\n"
#define MSGTR_MencoderWrongFormatAVI "\nVAROV�N�: FORM�T V�STUPN�HO SOUBORU JE _AVI_. Viz -of help.\n"
#define MSGTR_MencoderWrongFormatMPG "\nVAROV�N�: FORM�T V�STUPN�HO SOUBORU JE _MPEG_. Viz -of help.\n"
#define MSGTR_MissingOutputFilename "Nebyl nastaven v�stupn� soubor, prostudujte si volbu -o."
#define MSGTR_ForcingOutputFourcc "Vynucuji v�stupn� FourCC na %x [%.4s].\n"
#define MSGTR_ForcingOutputAudiofmtTag "Vynucuji zna�ku v�stupn�ho zvukov�ho form�tu 0x%x\n"
#define MSGTR_DuplicateFrames "\n%d opakuj�c�ch se sn�mk�!\n"
#define MSGTR_SkipFrame "\nP�eskakuji sn�mek!\n"
#define MSGTR_ResolutionDoesntMatch "\nNov� video soubor m� jin� rozli�en� nebo barevn� prostor ne� jeho p�edch�dce.\n"
#define MSGTR_FrameCopyFileMismatch "\nV�echny video soubory mus� m�t shodn� fps, rozli�en� a kodek pro -ovc copy.\n"
#define MSGTR_AudioCopyFileMismatch "\nV�echny soubory mus� pou��vat identick� audio kodek a form�t pro -oac copy.\n"
#define MSGTR_NoAudioFileMismatch "\nNelze kombinovat neozvu�en� video soubory s ozvu�en�mi. Zkuste -nosound.\n"
#define MSGTR_NoSpeedWithFrameCopy "VAROV�N�: volba -speed nem� zaru�enou spr�vnou funk�nost spolu s -oac copy!\n"\
"V�sledn� film m��e b�t vadn�!\n"
#define MSGTR_ErrorWritingFile "%s: chyba p�i z�pisu souboru.\n"
#define MSGTR_RecommendedVideoBitrate "Doporu�en� datov� tok videa pro CD %s: %d\n"
#define MSGTR_VideoStreamResult "\nVideo proud: %8.3f kbit/s  (%d B/s)  velikost: %"PRIu64" bajt�  %5.3f sekund  %d sn�mk�\n"
#define MSGTR_AudioStreamResult "\nAudio proud: %8.3f kbit/s  (%d B/s)  velikost: %"PRIu64" bajt�  %5.3f sekund\n"
#define MSGTR_OpenedStream "�sp�ch: form�t: %d  data: 0x%X - 0x%x\n"
#define MSGTR_VCodecFramecopy "videokodek: framecopy (%dx%d %dbpp fourcc=%x)\n"
#define MSGTR_ACodecFramecopy "audiokodek: framecopy (form�t=%x kan�l�=%d frekvence=%d bit�=%d B/s=%d vzorek-%d)\n"
#define MSGTR_CBRPCMAudioSelected "Vybr�n CBR PCM zvuk.\n"
#define MSGTR_MP3AudioSelected "Vybr�n MP3 zvuk.\n"
#define MSGTR_CannotAllocateBytes "Nelze alokovat %d bajt�.\n"
#define MSGTR_SettingAudioDelay "Nastavuji zpo�d�n� zvuku na %5.3fs.\n"
#define MSGTR_SettingVideoDelay "Nastavuji zpo�d�n� videa na %5.3fs.\n"
#define MSGTR_SettingAudioInputGain "Nastavuji p�edzes�len� zvukov�ho vstupu na %f.\n"
#define MSGTR_LamePresetEquals "\npreset=%s\n\n"
#define MSGTR_LimitingAudioPreload "Omezuji p�edna��t�n� zvuku na 0.4s.\n"
#define MSGTR_IncreasingAudioDensity "Zvy�uji hustotu audia na 4.\n"
#define MSGTR_ZeroingAudioPreloadAndMaxPtsCorrection "Vynucuji p�edna��t�n� zvuku na 0, max korekci pts  na 0.\n"
#define MSGTR_CBRAudioByterate "\n\nCBR zvuk: %d bajt�/s, %d bajt�/blok\n"
#define MSGTR_LameVersion "LAME ve verzi %s (%s)\n\n"
#define MSGTR_InvalidBitrateForLamePreset "Chyba: Specifikovan� datov� tok je mimo rozsah pro tento preset re�im.\n"\
"\n"\
"Pokud pou��v�te tento re�im, mus�te zadat hodnotu od \"8\" do \"320\".\n"\
"\n"\
"Dal�� informace viz: \"-lameopts preset=help\"\n"
#define MSGTR_InvalidLamePresetOptions "Chyba: Nezadali jste platn� profil a/nebo volby s preset re�imem.\n"\
"\n"\
"Dostupn� profily jsou:\n"\
"\n"\
"   <fast>        standard\n"\
"   <fast>        extreme\n"\
"                 insane\n"\
"   <cbr> (ABR Mode) - Implikuje re�im ABR. Pro jeho pou�it�,\n"\
"                      jednodu�e zadejte datov� tok. Nap��klad:\n"\
"                      \"preset=185\" aktivuje tento re�im\n"\
"                      a pou�ije pr�m�rn� datov� tok 185 kbps.\n"\
"\n"\
"    N�kolik p��klad�:\n"\
"\n"\
"    \"-lameopts fast:preset=standard  \"\n"\
" or \"-lameopts  cbr:preset=192       \"\n"\
" or \"-lameopts      preset=172       \"\n"\
" or \"-lameopts      preset=extreme   \"\n"\
"\n"\
"Dal�� informace viz: \"-lameopts preset=help\"\n"
#define MSGTR_LamePresetsLongInfo "\n"\
"Preset re�imy jsou navr�eny tak, aby poskytovaly co nejvy��� mo�nou kvalitu.\n"\
"\n"\
"V�t�ina z nich byla testov�na a vylad�na pomoc� zevrubn�ch zdvojen�ch slep�ch\n"\
"poslechov�ch test�, za ��elem dosa�en� a ov��en� t�to kvality.\n"\
"\n"\
"Nastaven� jsou neust�le aktualizov�na v souladu s nejnov�j��m v�vojem\n"\
"a m�la by poskytovat prakticky nejvy��� mo�nou kvalitu, jak� je v sou�asnosti \n"\
"s kodekem LAME dosa�iteln�.\n"\
"\n"\
"Aktivace preset re�im�:\n"\
"\n"\
"   Pro re�imy VBR (v�eobecn� nejvy��� kvalita):\n"\
"\n"\
"     \"preset=standard\" Tento re�im by m�l b�t jasnou volbou\n"\
"                             pro v�t�inu lid� a hudebn�ch ��nr� a m�\n"\
"                             ji� vysokou kvalitu.\n"\
"\n"\
"     \"preset=extreme\" Pokud m�te v�jime�n� dobr� sluch a odpov�daj�c�\n"\
"                             vybaven�, tento re�im obecn� poskytuje\n"\
"                             m�rn� vy��� kvalitu ne� re�im \"standard\".\n"\
"\n"\
"   Pro CBR 320kbps (nejvy��� mo�n� kvalita ze v�ech preset re�im�):\n"\
"\n"\
"     \"preset=insane\"  Tento re�im je pro v�t�inu lid� a situac�\n"\
"                             p�edimenzovan�, ale pokud vy�adujete\n"\
"                             absolutn� nejvy��� kvalitu bez ohledu na\n"\
"                             velikost souboru, je toto va�e volba.\n"\
"\n"\
"   Pro re�imy ABR (vysok� kvalita p�i dan�m datov�m toku, ale ne jako VBR):\n"\
"\n"\
"     \"preset=<kbps>\"  Pou�it�m tohoto re�imu obvykle dos�hnete dobr�\n"\
"                             kvality p�i dan�m datov�m toku. V z�vislosti\n"\
"                             na zadan�m toku tento preset odvod� optim�ln�\n"\
"                             nastaven� pro danou situaci.\n"\
"                             A�koli tento p��stup funguje, nen� ani zdaleka\n"\
"                             tak flexibiln� jako VBR, a obvykle nedosahuje\n"\
"                             stejn� �rovn� kvality jako VBR na vy���ch dato-\n"\
"                             v�ch toc�ch.\n"\
"\n"\
"Pro odpov�daj�c� profily jsou tak� dostupn� n�sleduj�c� volby:\n"\
"\n"\
"   <fast>        standard\n"\
"   <fast>        extreme\n"\
"                 insane\n"\
"   <cbr> (ABR re�im) - Implikuje re�im ABR. Pro jeho pou�it�,\n"\
"                      jednodu�e zadejte datov� tok. Nap��klad:\n"\
"                      \"preset=185\" aktivuje tento re�im\n"\
"                      a pou�ije pr�m�rn� datov� tok 185 kbps.\n"\
"\n"\
"   \"fast\" - V dan�m profilu aktivuje novou rychlou VBR kompresi.\n"\
"            Nev�hodou je obvykle m�rn� vy��� datov� tok ne� v norm�ln�m\n"\
"            re�imu a tak� m��e doj�t k m�rn�mu poklesu kvality.\n"\
"   Varov�n�:v sou�asn� verzi m��e nastaven� \"fast\" v�st k p��li�\n"\
"            vysok�mu datov�mu toku ve srovn�n� s norm�ln�m nastaven�m.\n"\
"\n"\
"   \"cbr\"  - Pokud pou�ijete re�im ABR (viz v��e) s v�znamn�m\n"\
"            datov�m tokem, nap�. 80, 96, 112, 128, 160, 192, 224, 256, 320,\n"\
"            m��ete pou��t volbu \"cbr\" k vynucen� k�dov�n� v re�imu CBR\n"\
"            (konstantn� tok) nam�sto standardn�ho ABR re�imu. ABR poskytuje\n"\
"            lep�� kvalitu, ale CBR m��e b�t u�ite�n� v situac�ch jako je\n"\
"            vys�l�n� MP3 proudu po internetu.\n"\
"\n"\
"    Nap��klad:\n"\
"\n"\
"      \"-lameopts fast:preset=standard  \"\n"\
" nebo \"-lameopts  cbr:preset=192       \"\n"\
" nebo \"-lameopts      preset=172       \"\n"\
" nebo \"-lameopts      preset=extreme   \"\n"\
"\n"\
"\n"\
"Pro ABR re�im je k dispozici n�kolik zkratek:\n"\
"phone => 16kbps/mono        phon+/lw/mw-eu/sw => 24kbps/mono\n"\
"mw-us => 40kbps/mono        voice => 56kbps/mono\n"\
"fm/radio/tape => 112kbps    hifi => 160kbps\n"\
"cd => 192kbps               studio => 256kbps"
#define MSGTR_LameCantInit \
"Nelze nastavit volby pro LAME, ov��te datov�_tok/vzorkovou_rychlost. N�kter�"\
"velmi n�zk� datov� toky (<32) vy�aduj� ni��� vzorkovou rychlost (nap�. -srate 8000).\n"\
"Pokud v�e sel�e, zkuste preset."
#define MSGTR_ConfigFileError "chyba konfigura�n�ho souboru"
#define MSGTR_ErrorParsingCommandLine "chyba p�i zpracov�v�n� p��kazov�ho ��dku"
#define MSGTR_VideoStreamRequired "Videoproud je povinn�!\n"
#define MSGTR_ForcingInputFPS "Vstupn� fps bude interpretov�no jako %5.2f\n"
#define MSGTR_RawvideoDoesNotSupportAudio "V�stupn� form�t souboru RAWVIDEO nepodporuje zvuk - vyp�n�m ho.\n"
#define MSGTR_DemuxerDoesntSupportNosound "Tento demuxer zat�m nepodporuje -nosound.\n"
#define MSGTR_MemAllocFailed "Alokace pam�ti selhala.\n"
#define MSGTR_NoMatchingFilter "Nemohu naj�t odpov�daj�c� filtr/ao form�t!\n"
#define MSGTR_MP3WaveFormatSizeNot30 "sizeof(MPEGLAYER3WAVEFORMAT)==%d!=30, mo�n� je vadn� p�eklada� C?\n"
#define MSGTR_NoLavcAudioCodecName "Audio LAVC, chyb� jm�no kodeku!\n"
#define MSGTR_LavcAudioCodecNotFound "Audio LAVC, nemohu naj�t enkod�r pro kodek %s.\n"
#define MSGTR_CouldntAllocateLavcContext "Audio LAVC, nemohu alokovat kontext!\n"
#define MSGTR_CouldntOpenCodec "Nelze otev��t kodek %s, br=%d.\n"
#define MSGTR_CantCopyAudioFormat "Audio form�t 0x%x je nekompatibiln� s '-oac copy', zkuste pros�m '-oac pcm',\n nebo pou�ijte '-fafmttag' pro jeho p�eps�n�.\n"

// cfg-mencoder.h:

#define MSGTR_MEncoderMP3LameHelp "\n\n"\
" vbr=<0-4>     metoda prom�nn�ho datov�ho toku\n"\
"                0: cbr  (konstantn� tok)\n"\
"                1: mt   (VBR algoritmus Mark Taylor)\n"\
"                2: rh   (VBR algoritmus Robert Hegemann - v�choz�)\n"\
"                3: abr  (pr�m�rn� tok)\n"\
"                4: mtrh (VBR alogoritmus Mark Taylor Robert Hegemann)\n"\
"\n"\
" abr           pr�m�rn� datov� tok\n"\
"\n"\
" cbr           konstantn� datov� tok\n"\
"               Vynut� tak� metodu CBR pro n�sledn� ABR preset re�imy\n"\
"\n"\
" br=<0-1024>   ur�en� datov�ho toku v kBit (pouze CBR a ABR)\n"\
"\n"\
" q=<0-9>       kvalita (0-nejvy���, 9-nejni���) (pouze pro VBR)\n"\
"\n"\
" aq=<0-9>      kvalita algoritmu (0-nejlep��/nejpomalej��, 9-nejhor��/nejrychlej��)\n"\
"\n"\
" ratio=<1-100> kompresn� pom�r\n"\
"\n"\
" vol=<0-10>    zes�len� zvuku\n"\
"\n"\
" mode=<0-3>    (v�choz�: auto)\n"\
"                0: stereo\n"\
"                1: joint-stereo\n"\
"                2: dualchannel\n"\
"                3: mono\n"\
"\n"\
" padding=<0-2>\n"\
"                0: ne\n"\
"                1: v�e\n"\
"                2: upravit\n"\
"\n"\
" fast          Zap�n� rychlej�� enk�dov�n� pro n�sledn� VBR preset re�imy,\n"\
"               poskytuje o n�co ni��� kvalitu a vy��� datov� tok.\n"\
"\n"\
" preset=<hodnota> P�ednastaven� profily poskytuj�c� maxim�ln� kvalitu.\n"\
"                  medium: enk�dov�n� metodou VBR, dobr� kvalita\n"\
"                   (datov� tok 150-180 kbps)\n"\
"                  standard: enk�dov�n� metodou VBR, vysok� kvalita\n"\
"                   (datov� tok 170-210 kbps)\n"\
"                  extreme: enk�dov�n� metodou VBR, velmi vysok� kvalita\n"\
"                   (datov� tok 200-240 kbps)\n"\
"                  insane: enk�dov�n� metodou CBR, nejvy��� preset kvalita\n"\
"                   (datov� tok 320 kbps)\n"\
"                  <8-320>: hodnota pr�m�rn�ho datov�ho toku pro metodu ABR.\n\n"

//codec-cfg.c:
#define MSGTR_DuplicateFourcc "zdvojen� FourCC"
#define MSGTR_TooManyFourccs "p��li� mnoho FourCC/form�t�..."
#define MSGTR_ParseError "chyba interpretace (parse)"
#define MSGTR_ParseErrorFIDNotNumber "chyba interpretace (ID form�tu, nikoli ��slo?)"
#define MSGTR_ParseErrorFIDAliasNotNumber "chyba interpretace (alias ID form�tu, nikoli ��slo?)"
#define MSGTR_DuplicateFID "zdvojen� ID form�tu"
#define MSGTR_TooManyOut "p��li� mnoho v�stupu..."
#define MSGTR_InvalidCodecName "\njm�no kodeku(%s) nen� platn�!\n"
#define MSGTR_CodecLacksFourcc "\nkodek(%s) nem� FourCC/form�t!\n"
#define MSGTR_CodecLacksDriver "\nkodek(%s) nem� driver!\n"
#define MSGTR_CodecNeedsDLL "\nkodek(%s) vy�aduje 'dll'!\n"
#define MSGTR_CodecNeedsOutfmt "\nkodek(%s) vy�aduje 'outfmt'!\n"
#define MSGTR_CantAllocateComment "Nelze alokovat pam� pro koment��. "
#define MSGTR_GetTokenMaxNotLessThanMAX_NR_TOKEN "get_token(): max >= MAX_MR_TOKEN!"
#define MSGTR_ReadingFile "Na��t�m %s: "
#define MSGTR_CantOpenFileError "Nelze otev��t '%s': %s\n"
#define MSGTR_CantGetMemoryForLine "Nem�m pam� pro 'line': %s\n"
#define MSGTR_CantReallocCodecsp "Nelze realokovat '*codecsp': %s\n"
#define MSGTR_CodecNameNotUnique "Jm�no kodeku '%s' nen� jedine�n�."
#define MSGTR_CantStrdupName "Nelze prov�st strdup -> 'name': %s\n"
#define MSGTR_CantStrdupInfo "Nelze prov�st strdup -> 'info': %s\n"
#define MSGTR_CantStrdupDriver "Nelze prov�st strdup -> 'driver': %s\n"
#define MSGTR_CantStrdupDLL "Nelze prov�st strdup -> 'dll': %s"
#define MSGTR_AudioVideoCodecTotals "%d audio & %d video kodek�\n"
#define MSGTR_CodecDefinitionIncorrect "Kodek nen� spr�vn� definov�n."
#define MSGTR_OutdatedCodecsConf "Tento codecs.conf je p��li� star� a nekompatibiln� s t�mto sestaven�m  MPlayeru!"

// divx4_vbr.c:
#define MSGTR_OutOfMemory "nedostatek pam�ti"
#define MSGTR_OverridingTooLowBitrate "Nastaven� datov� tok je p��li� mal� pro tento klip.\n"\
"Minim�ln� mo�n� datov� tok pro tento klip  je %.0f kbps. P�episuji\n"\
"u�ivatelem nastavenou hodnotu.\n"

// fifo.c
#define MSGTR_CannotMakePipe "Nelze vytvo�it ROURU!\n"

// m_config.c
#define MSGTR_SaveSlotTooOld "Nalezen� save slot z lvl %d je p��li� star�: %d !!!\n"
#define MSGTR_InvalidCfgfileOption "Volbu %s nelze pou��t v konfigura�n�m souboru\n"
#define MSGTR_InvalidCmdlineOption "Volbu %s nelze pou��t z p��kazov�ho ��dku\n"
#define MSGTR_InvalidSuboption "Chyba: volba '%s' nem� ��dnou podvolbu '%s'\n"
#define MSGTR_MissingSuboptionParameter "Chyba: podvolba '%s' volby '%s' mus� m�t parametr!\n"
#define MSGTR_MissingOptionParameter "Chyba: volba '%s' mus� m�t parametr!\n"
#define MSGTR_OptionListHeader "\n N�zev                Typ             Min        Max      Glob�l  CL    Konfig\n\n"
#define MSGTR_TotalOptions "\nCelkem: %d voleb\n"
#define MSGTR_ProfileInclusionTooDeep "VAROV�N�: P��li� hlubok� vno�ov�n� profil�.\n"
#define MSGTR_NoProfileDefined "��dn� profil nebyl definov�n.\n"
#define MSGTR_AvailableProfiles "Dostupn� profily:\n"
#define MSGTR_UnknownProfile "Nezn�m� profil '%s'.\n"
#define MSGTR_Profile "Profil %s: %s\n"

// m_property.c
#define MSGTR_PropertyListHeader "\n N�zev                Typ             Min        Max\n\n"
#define MSGTR_TotalProperties "\nCelkem: %d nastaven�\n"

// open.c, stream.c:
#define MSGTR_CdDevNotfound "CD-ROM za��zen� '%s' nebylo nalezeno.\n"
#define MSGTR_ErrTrackSelect "Chyba p�i v�b�ru VCD stopy."
#define MSGTR_ReadSTDIN "�tu ze std. vstupu...\n"
#define MSGTR_UnableOpenURL "Nelze otev��t URL: %s\n"
#define MSGTR_ConnToServer "P�ipojeno k serveru: %s\n"
#define MSGTR_FileNotFound "Soubor nenalezen: '%s'\n"

#define MSGTR_SMBInitError "Nelze inicializovat knihovnu libsmbclient: %d\n"
#define MSGTR_SMBFileNotFound "Nemohu otev��t soubor ze s�t�: '%s'\n"
#define MSGTR_SMBNotCompiled "MPlayer nebyl p�elo�en s podporou �ten� SMB.\n"

#define MSGTR_CantOpenDVD "Nelze otev��t DVD za��zen�: %s\n"
#define MSGTR_NoDVDSupport "MPlayer byl zkompilov�n bez podpory DVD, kon��m.\n"
#define MSGTR_DVDwait "Na��t�m strukturu disku, �ekejte pros�m...\n"
#define MSGTR_DVDnumTitles "Na tomto DVD je %d titul(�).\n"
#define MSGTR_DVDinvalidTitle "Neplatn� ��slo DVD titulu: %d\n"
#define MSGTR_DVDnumChapters "V tomto DVD titulu je %d kapitol.\n"
#define MSGTR_DVDinvalidChapter "Neplatn� ��slo DVD kapitoly: %d\n"
#define MSGTR_DVDinvalidChapterRange "Nespr�vn� nastaven� rozsah kapitol %s\n"
#define MSGTR_DVDinvalidLastChapter "Neplatn� ��slo posledn� DVD kapitoly: %d\n"
#define MSGTR_DVDnumAngles "Tento DVD titul m� %d �hl� pohledu.\n"
#define MSGTR_DVDinvalidAngle "Neplatn� ��slo DVD �hlu pohledu: %d\n"
#define MSGTR_DVDnoIFO "Nelze otev��t IFO soubor pro DVD titul %d.\n"
#define MSGTR_DVDnoVMG "Nelze otev��t VMG info!\n"
#define MSGTR_DVDnoVOBs "Nelze otev��t VOBy titulu (VTS_%02d_1.VOB).\n"
#define MSGTR_DVDnoMatchingAudio "DVD zvuk v po�adovan�m jazyce nebyl nalezen!\n"
#define MSGTR_DVDaudioChannel "Vybr�n DVD zvukov� kan�l: %d jazyk: %c%c\n"
#define MSGTR_DVDnoMatchingSubtitle "DVD titulky v po�adovan�m jazyce nebyly nalezeny!\n"
#define MSGTR_DVDsubtitleChannel "Vybr�n DVD titulkov� kan�l: %d jazyk: %c%c\n"
#define MSGTR_DVDopenOk "DVD �sp�n� otev�eno.\n"

// muxer.c, muxer_*.c:
#define MSGTR_TooManyStreams "P��li� mnoho datov�ch proud�!"
#define MSGTR_RawMuxerOnlyOneStream "Muxer surov�ho zvuku podporuje pouze jeden zvukov� proud!\n"
#define MSGTR_IgnoringVideoStream "Ignoruji video proud!\n"
#define MSGTR_UnknownStreamType "Varov�n�, nezn�m� typ datov�ho proudu: %d\n"
#define MSGTR_WarningLenIsntDivisible "Varov�n�, d�lka nen� n�sobkem velikosti vzorku!\n"
#define MSGTR_MuxbufMallocErr "Nelze alokovat pam� pro sn�mkovou vyrovn�vac� pam� muxeru!\n"
#define MSGTR_MuxbufReallocErr "Nelze realokovat pam� pro sn�mkovou vyrovn�vac� pam� muxeru!\n"
#define MSGTR_MuxbufSending "Sn�mkov� vyrovn�vac� pam� muxeru pos�l� %d sn�mk� do muxeru.\n"
#define MSGTR_WritingHeader "Zapisuji hlavi�ku...\n"
#define MSGTR_WritingTrailer "Zapisuji index...\n"
 
// demuxer.c, demux_*.c:
#define MSGTR_AudioStreamRedefined "VAROV�N�: Hlavi�ka audio proudu %d p�edefinov�na!\n"
#define MSGTR_VideoStreamRedefined "VAROV�N�: Hlavi�ka video proudu %d p�edefinov�na!\n"
#define MSGTR_TooManyAudioInBuffer "\nP��li� mnoho audio paket� ve vyrovn�vac� pam�ti: (%d v %d bajtech)\n"
#define MSGTR_TooManyVideoInBuffer "\nP��li� mnoho video paket� ve vyrovn�vac� pam�ti: (%d v %d bajtech)\n"
#define MSGTR_MaybeNI "Mo�n� p�ehr�v�te neprokl�dan� proud/soubor nebo kodek selhal?\n"\
		      "V AVI souborech zkuste vynutit neprokl�dan� re�im pomoc� volby -ni.\n"
#define MSGTR_SwitchToNi "\nDetekov�n �patn� prokl�dan� AVI soubor - p�ep�n�m do -ni re�imu...\n"
#define MSGTR_Detected_XXX_FileFormat "Detekov�n form�t souboru %s.\n"
#define MSGTR_DetectedAudiofile "Detekov�n zvukov� soubor.\n"
#define MSGTR_NotSystemStream "Toto nen� form�t MPEG System Stream... (mo�n� Transport Stream?)\n"
#define MSGTR_InvalidMPEGES "�patn� MPEG-ES proud??? Kontaktujte autora, mo�n� to je chyba :(\n"
#define MSGTR_FormatNotRecognized "======= Bohu�el, form�t tohoto souboru nebyl rozpozn�n/nen� podporov�n =======\n"\
                                  "==== Pokud je soubor AVI, ASF nebo MPEG proud, kontaktujte pros�m autora! ====\n"
#define MSGTR_MissingVideoStream "Nebyl nalezen video proud.\n"
#define MSGTR_MissingAudioStream "Nebyl nalezen audio proud -> bez zvuku.\n"
#define MSGTR_MissingVideoStreamBug "Chyb� video proud!? Kontaktujte autora, m��e to b�t chyba :(\n"

#define MSGTR_DoesntContainSelectedStream "demux: Soubor neobsahuje zvolen� audio nebo video proud.\n"

#define MSGTR_NI_Forced "Vynucen"
#define MSGTR_NI_Detected "Detekov�n"
#define MSGTR_NI_Message "%s NEPROKL�DAN� form�t AVI souboru.\n"

#define MSGTR_UsingNINI "Pou��v�m NEPROKL�DAN� vadn� form�tov�n� AVI souboru.\n"
#define MSGTR_CouldntDetFNo "Nelze ur�it po�et sn�mk� (pro absolutn� posun)\n"
#define MSGTR_CantSeekRawAVI "Nelze se posouvat v surov�ch (raw) AVI proudech! (Pot�ebuji index, zkuste pou��t volbu -idx.)\n"
#define MSGTR_CantSeekFile "Nemohu se posouvat v tomto souboru.\n"

#define MSGTR_MOVcomprhdr "MOV: Komprimovan� hlavi�ky vy�aduj� ZLIB!\n"
#define MSGTR_MOVvariableFourCC "MOV: VAROV�N�: Prom�nn� FourCC detekov�na!?\n"
#define MSGTR_MOVtooManyTrk "MOV: VAROV�N�: p��li� mnoho stop"
#define MSGTR_FoundAudioStream "==> Nalezen audio proud: %d\n"
#define MSGTR_FoundVideoStream "==> Nalezen video proud: %d\n"
#define MSGTR_DetectedTV "Detekov�na TV! ;-)\n"
#define MSGTR_ErrorOpeningOGGDemuxer "Nelze otev��t Ogg demuxer.\n"
#define MSGTR_ASFSearchingForAudioStream "ASF: Hled�m audio proud (id: %d).\n"
#define MSGTR_CannotOpenAudioStream "Nemohu otev��t audio proud: %s\n"
#define MSGTR_CannotOpenSubtitlesStream "Nemohu otev��t proud s titulky: %s\n"
#define MSGTR_OpeningAudioDemuxerFailed "Nepovedlo se otev��t audio demuxer: %s\n"
#define MSGTR_OpeningSubtitlesDemuxerFailed "Nepovedlo se otev��t demuxer pro titulky: %s\n"
#define MSGTR_TVInputNotSeekable "TV vstup neumo��uje posun! (\"Posun\" bude pravd�podobn� pou�it pro zm�nu kan�l� ;)\n"
#define MSGTR_DemuxerInfoAlreadyPresent "Informace o demuxeru %s je ji� p��tomna!\n"
#define MSGTR_ClipInfo "Informace o klipu:\n"

#define MSGTR_LeaveTelecineMode "\ndemux_mpg: detekov�no 30000/1001 fps NTSC, p�ep�n�m frekvenci sn�mk�.\n"
#define MSGTR_EnterTelecineMode "\ndemux_mpg: detekov�no 24000/1001 fps progresivn� NTSC, p�ep�n�m frekvenci sn�mk�.\n"

#define MSGTR_CacheFill "\rNapln�n� cache: %5.2f%% (%"PRId64" bajt�)   "
#define MSGTR_NoBindFound "Tla��tko '%s' nem� p�i�azenu ��dnou funkci."
#define MSGTR_FailedToOpen "Selhalo otev�en� %s.\n"

// dec_video.c & dec_audio.c:
#define MSGTR_CantOpenCodec "Nelze otev��t kodek.\n"
#define MSGTR_CantCloseCodec "Nelze uzav��t kodek.\n"

#define MSGTR_MissingDLLcodec "CHYBA: Nelze otev��t po�adovan� DirectShow kodek %s.\n"
#define MSGTR_ACMiniterror "Nemohu na��st/inicializovat Win32/ACM audio kodek (chyb� DLL soubor?).\n"
#define MSGTR_MissingLAVCcodec "Nemohu naj�t kodek '%s' v libavcodec...\n"

#define MSGTR_MpegNoSequHdr "MPEG: KRITICK� CHYBA: Konec souboru v pr�b�hu vyhled�v�n� hlavi�ky sekvence.\n"
#define MSGTR_CannotReadMpegSequHdr "KRITICK� CHYBA: Nelze p�e��st hlavi�ku sekvence.\n"
#define MSGTR_CannotReadMpegSequHdrEx "KRITICK� CHYBA: Nelze p�e��st roz���en� hlavi�ky sekvence.\n"
#define MSGTR_BadMpegSequHdr "MPEG: �patn� hlavi�ka sekvence.\n"
#define MSGTR_BadMpegSequHdrEx "MPEG: �patn� roz���en� hlavi�ky sekvence.\n"

#define MSGTR_ShMemAllocFail "Nelze alokovat sd�lenou pam�\n"
#define MSGTR_CantAllocAudioBuf "Nelze alokovat vyrovn�vac� pam� pro zvukov� v�stup\n"

#define MSGTR_UnknownAudio "Nezn�m�/chyb�j�c� audio form�t -> nebude zvuk.\n"

#define MSGTR_UsingExternalPP "[PP] Pou��v�m extern� filtr pro postprocessing, max q = %d.\n"
#define MSGTR_UsingCodecPP "[PP] Pou��v�m integrovan� postprocessing kodeku, max q = %d.\n"
#define MSGTR_VideoAttributeNotSupportedByVO_VD "Video atribut '%s' nen� podporov�n vybran�m vo & vd.\n"
#define MSGTR_VideoCodecFamilyNotAvailableStr "Po�adovan� rodina video kodeku [%s] (vfm=%s) nen� dostupn�.\nAktivujte ji p�i kompilaci.\n"
#define MSGTR_AudioCodecFamilyNotAvailableStr "Po�adovan� rodina audio kodeku [%s] (afm=%s) nen� dostupn�.\nAktivujte ji p�i kompilaci.\n"
#define MSGTR_OpeningVideoDecoder "Otev�r�m video dekod�r: [%s] %s\n"
#define MSGTR_SelectedVideoCodec "Vybr�n video kodek: [%s] vfm: %s (%s)\n"
#define MSGTR_OpeningAudioDecoder "Otev�r�m audio dekod�r: [%s] %s\n"
#define MSGTR_SelectedAudioCodec "Vybr�n audio kodek: [%s] afm: %s (%s)\n"
#define MSGTR_BuildingAudioFilterChain "Vytv���m zvukov� �et�zec filtr� pro %dHz/%dch/%s -> %dHz/%dch/%s...\n"
#define MSGTR_UninitVideoStr "Uninit video: %s\n"
#define MSGTR_UninitAudioStr "Uninit audio: %s\n"
#define MSGTR_VDecoderInitFailed "Video dekod�r - inicializace selhala :(\n"
#define MSGTR_ADecoderInitFailed "Audio dekod�r - inicializace selhala :(\n"
#define MSGTR_ADecoderPreinitFailed "Audio dekod�r - p�edinicializace selhala :(\n"
#define MSGTR_AllocatingBytesForInputBuffer "dec_audio: Alokuji %d byt� pro vstupn� vyrovn�vac� pam�\n"
#define MSGTR_AllocatingBytesForOutputBuffer "dec_audio: Alokuji %d + %d = %d byt� pro v�stupn� vyrovn�vac� pam�\n"

// LIRC:
#define MSGTR_SettingUpLIRC "Zap�n�m podporu LIRC...\n"
#define MSGTR_LIRCdisabled "Nebudete moci pou��vat d�lkov� ovlada�.\n"
#define MSGTR_LIRCopenfailed "Nepovedlo se zapnout podporu LIRC.\n"
#define MSGTR_LIRCcfgerr "Nepovedlo se p�e��st konfigura�n� soubor LIRC %s.\n"

// vf.c
#define MSGTR_CouldNotFindVideoFilter "Nemohu nal�zt video filtr '%s'\n"
#define MSGTR_CouldNotOpenVideoFilter "Nemohu otev��t video filtr '%s'\n"
#define MSGTR_OpeningVideoFilter "Otev�r�m video filtr: "
#define MSGTR_CannotFindColorspace "Ani p�i vlo�en� 'scale' nemohu nal�zt spole�n� barevn� prostor :(\n"

// vd.c
#define MSGTR_CodecDidNotSet "VDek: Kodek nenastavil sh->disp_w a sh->disp_h, pokou��m se to obej�t.\n"
#define MSGTR_VoConfigRequest "VDek: Po�adovan� konfigurace vo - %d x %d (preferovan� barevn� prostor: %s)\n"
#define MSGTR_CouldNotFindColorspace "Nemohu nal�zt spole�n� barevn� prostor - zkou��m to znovu s -vf scale...\n"
#define MSGTR_MovieAspectIsSet "Pom�r stran obrazu filmu je %.2f:1 - �k�luji na spr�vn� pom�r.\n"
#define MSGTR_MovieAspectUndefined "Pom�r stran obrazu filmu nen� definov�n - nem�n�m velikost.\n"

// vd_dshow.c, vd_dmo.c
#define MSGTR_DownloadCodecPackage "Pot�ebujete aktualizovat nebo nainstalovat bin�rn� kodeky.\nJd�te na http://www.mplayerhq.hu/dload.html\n"
#define MSGTR_DShowInitOK "INFO: Inicializace Win32/DShow videokodeku OK.\n"
#define MSGTR_DMOInitOK "INFO: Inicializace Win32/DMO videokodeku OK.\n"

// x11_common.c
#define MSGTR_EwmhFullscreenStateFailed "\nX11: Nemohu poslat ud�lost EWMH fullscreen!\n"
#define MSGTR_CouldNotFindXScreenSaver "xscreensaver_disable: Nelze nal�zt okno XScreenSaveru.\n"
#define MSGTR_SelectedVideoMode "XF86VM: Vybr�n videore�im %dx%d pro obraz velikosti %dx%d.\n"

#define MSGTR_InsertingAfVolume "[Mixer] Hardwarov� mix�r nen� k dispozici, vkl�d�m filtr pro hlasitost.\n"
#define MSGTR_NoVolume "[Mixer] ��zen� hlasitosti nen� dostupn�.\n"

// ====================== GUI messages/buttons ========================

#ifdef HAVE_NEW_GUI

// --- labels ---
#define MSGTR_About "O aplikaci"
#define MSGTR_FileSelect "Vybrat soubor..."
#define MSGTR_SubtitleSelect "Vybrat titulky..."
#define MSGTR_OtherSelect "Vybrat..."
#define MSGTR_AudioFileSelect "Vybrat extern� zvukov� kan�l..."
#define MSGTR_FontSelect "Vybrat font..."
// Pozn�mka: Pokud zm�n�te MSGTR_PlayList, ujist�te se pros�m, �e vyhovuje i pro  MSGTR_MENU_PlayList
#define MSGTR_PlayList "Playlist"
#define MSGTR_Equalizer "Ekvaliz�r"
#define MSGTR_ConfigureEqualizer "Konfigurace ekvaliz�ru"
#define MSGTR_SkinBrowser "Prohl��e� t�mat"
#define MSGTR_Network "S��ov� vys�l�n�..."
// Pozn�mka: Pokud zm�n�te MSGTR_Preferences, ujist�te se pros�m, �e vyhovuje i pro  MSGTR_MENU_Preferences
#define MSGTR_Preferences "Nastaven�" // P�edvolby?
#define MSGTR_AudioPreferences "Konfigurace ovlada�e zvuku"
#define MSGTR_NoMediaOpened "Nic nen� otev�eno."
#define MSGTR_VCDTrack "VCD stopa %d"
#define MSGTR_NoChapter "��dn� kapitola" //bez kapitoly?
#define MSGTR_Chapter "Kapitola %d"
#define MSGTR_NoFileLoaded "Nen� na�ten ��dn� soubor."

// --- buttons ---
#define MSGTR_Ok "OK"
#define MSGTR_Cancel "Zru�it"
#define MSGTR_Add "P�idat"
#define MSGTR_Remove "Odebrat"
#define MSGTR_Clear "Vynulovat"
#define MSGTR_Config "Konfigurace"
#define MSGTR_ConfigDriver "Konfigurovat ovlada�"
#define MSGTR_Browse "Prohl��et"

// --- error messages ---
#define MSGTR_NEMDB "Bohu�el nen� dostatek pam�ti pro vykreslovac� mezipam�."
#define MSGTR_NEMFMR "Bohu�el nen� dostatek pam�ti pro vykreslen� menu."
#define MSGTR_IDFGCVD "Bohu�el nebyl nalezen video ovlada� kompatibiln� s GUI."
#define MSGTR_NEEDLAVCFAME "Bohu�el nelze p�ehr�vat ne-MPEG s kartou DXR3/H+ bez p�eenk�dov�n�.\nPros�m, zapn�te lavc nebo fame v konfiguraci DXR3/H+."
#define MSGTR_UNKNOWNWINDOWTYPE "Nalezen nezn�m� typ okna ..."

// --- skin loader error messages
#define MSGTR_SKIN_ERRORMESSAGE "[t�mata] chyba v konfigura�n�m souboru t�mat na ��dce %d: %s"
#define MSGTR_SKIN_WARNING1 "[t�mata] varov�n� v konfigura�n�m souboru t�mat na ��dce %d:\nwidget nalezen ale p�ed n�m nebyla nalezena ��dn� \"section\" (%s)"
#define MSGTR_SKIN_WARNING2 "[t�mata] varov�n� v konfigura�n�m souboru t�mat na ��dce %d:\nwidget nalezen ale p�ed n�m nebyla nalezena ��dn� \"subsection\" (%s)"
#define MSGTR_SKIN_WARNING3 "[t�mata] varov�n� v konfigura�n�m souboru t�mat na ��dce %d:\nwidget (%s) nepodporuje tuto subsekci"
#define MSGTR_SKIN_SkinFileNotFound "[t�mata] soubor ( %s ) nenalezen.\n"
#define MSGTR_SKIN_SkinFileNotReadable "[t�mata] soubor ( %s ) nelze p�e��st.\n"
#define MSGTR_SKIN_BITMAP_16bit  "Bitmapy s hloubkou 16 bit� a m�n� nejsou podporov�ny (%s).\n"
#define MSGTR_SKIN_BITMAP_FileNotFound  "Soubor nenalezen (%s)\n"
#define MSGTR_SKIN_BITMAP_BMPReadError "chyba �ten� BMP (%s)\n"
#define MSGTR_SKIN_BITMAP_TGAReadError "chyba �ten� TGA (%s)\n"
#define MSGTR_SKIN_BITMAP_PNGReadError "chyba �ten� PNG (%s)\n"
#define MSGTR_SKIN_BITMAP_RLENotSupported "form�t TGA zapouzd�en� v RLE nen� podporov�n (%s)\n"
#define MSGTR_SKIN_BITMAP_UnknownFileType "nezn�m� typ souboru (%s)\n"
#define MSGTR_SKIN_BITMAP_ConversionError "chyba konverze z 24 do 32 bit� (%s)\n"
#define MSGTR_SKIN_BITMAP_UnknownMessage "nezn�m� zpr�va: %s\n"
#define MSGTR_SKIN_FONT_NotEnoughtMemory "nedostatek pam�ti\n"
#define MSGTR_SKIN_FONT_TooManyFontsDeclared "deklarov�no p��li� mnoho font�\n"
#define MSGTR_SKIN_FONT_FontFileNotFound "soubor fontu nebyl nalezen\n"
#define MSGTR_SKIN_FONT_FontImageNotFound "soubor obrazu fontu nebyl nalezen\n"
#define MSGTR_SKIN_FONT_NonExistentFontID "neexistuj�c� identifik�tor fontu (%s)\n"
#define MSGTR_SKIN_UnknownParameter "nezn�m� parametr (%s)\n"
#define MSGTR_SKIN_SKINCFG_SkinNotFound "T�ma nenalezeno (%s).\n"
#define MSGTR_SKIN_SKINCFG_SelectedSkinNotFound "Vybran� skin ( %s ) nenalezen, zkou��m 'v�choz�'...\n"
#define MSGTR_SKIN_SKINCFG_SkinCfgReadError "chyba p�i �ten� konfigura�n�ho souboru t�mat (%s)\n"
#define MSGTR_SKIN_LABEL "T�mata:"

// --- gtk menus
#define MSGTR_MENU_AboutMPlayer "O aplikaci MPlayer"
#define MSGTR_MENU_Open "Otev��t..."
#define MSGTR_MENU_PlayFile "P�ehr�t soubor..."
#define MSGTR_MENU_PlayVCD "P�ehr�t VCD..."
#define MSGTR_MENU_PlayDVD "P�ehr�t DVD..."
#define MSGTR_MENU_PlayURL "P�ehr�t z URL..."
#define MSGTR_MENU_LoadSubtitle "Na��st titulky..."
#define MSGTR_MENU_DropSubtitle "Zahodit titulky..."
#define MSGTR_MENU_LoadExternAudioFile "Na��st extern� soubor se zvukem..."
#define MSGTR_MENU_Playing "Ovl�d�n� p�ehr�v�n�"
#define MSGTR_MENU_Play "P�ehr�t"
#define MSGTR_MENU_Pause "Pozastavit"
#define MSGTR_MENU_Stop "Stop"
#define MSGTR_MENU_NextStream "Dal�� proud"
#define MSGTR_MENU_PrevStream "P�edchoz� proud"
#define MSGTR_MENU_Size "Velikost"
#define MSGTR_MENU_HalfSize   "Polovi�n� velikost"
#define MSGTR_MENU_NormalSize "Norm�ln� velikost"
#define MSGTR_MENU_DoubleSize "Dvojn�sobn� velikost"
#define MSGTR_MENU_FullScreen "Cel� obrazovka"
#define MSGTR_MENU_DVD "DVD"
#define MSGTR_MENU_VCD "VCD"
#define MSGTR_MENU_PlayDisc "P�ehr�t disk..."
#define MSGTR_MENU_ShowDVDMenu "Zobrazit DVD menu"
#define MSGTR_MENU_Titles "Tituly"
#define MSGTR_MENU_Title "Titul %2d"
#define MSGTR_MENU_None "(��dn�)"
#define MSGTR_MENU_Chapters "Kapitoly"
#define MSGTR_MENU_Chapter "Kapitola %2d"
#define MSGTR_MENU_AudioLanguages "Jazyk zvuku"
#define MSGTR_MENU_SubtitleLanguages "Jazyk titulk�"
#define MSGTR_MENU_PlayList MSGTR_PlayList
#define MSGTR_MENU_SkinBrowser "Prohl��e� t�mat"
#define MSGTR_MENU_Preferences MSGTR_Preferences
#define MSGTR_MENU_Exit "Konec..."
#define MSGTR_MENU_Mute "Ztlumit"
#define MSGTR_MENU_Original "P�vodn�"
#define MSGTR_MENU_AspectRatio "Pom�r stran"
#define MSGTR_MENU_AudioTrack "Audio stopa"
#define MSGTR_MENU_Track "Stopa %d"
#define MSGTR_MENU_VideoTrack "Video stopa"
#define MSGTR_MENU_Subtitles "Titulky"

// --- equalizer
// Pozn�mka: Pokud zm�n�te MSGTR_EQU_Audio, ujist�te se pros�m, �e vyhovuje i pro MSGTR_PREFERENCES_Audio
#define MSGTR_EQU_Audio "Zvuk"
// Pozn�mka: Pokud zm�n�te MSGTR_EQU_Video, ujist�te se pros�m, �e vyhovuje i pro MSGTR_PREFERENCES_Video
#define MSGTR_EQU_Video "Obraz"
#define MSGTR_EQU_Contrast "Kontrast: "
#define MSGTR_EQU_Brightness "Jas: "
#define MSGTR_EQU_Hue "Odst�n: "
#define MSGTR_EQU_Saturation "Sytost: "
#define MSGTR_EQU_Front_Left "Lev� p�edn�"
#define MSGTR_EQU_Front_Right "Prav� p�edn�"
#define MSGTR_EQU_Back_Left "Lev� zadn�"
#define MSGTR_EQU_Back_Right "Prav� zadn�"
#define MSGTR_EQU_Center "St�edov�"
#define MSGTR_EQU_Bass "Basov�"
#define MSGTR_EQU_All "V�e"
#define MSGTR_EQU_Channel1 "Kan�l 1:"
#define MSGTR_EQU_Channel2 "Kan�l 2:"
#define MSGTR_EQU_Channel3 "Kan�l 3:"
#define MSGTR_EQU_Channel4 "Kan�l 4:"
#define MSGTR_EQU_Channel5 "Kan�l 5:"
#define MSGTR_EQU_Channel6 "Kan�l 6:"

// --- playlist
#define MSGTR_PLAYLIST_Path "Cesta"
#define MSGTR_PLAYLIST_Selected "Vybran� soubory"
#define MSGTR_PLAYLIST_Files "Soubory"
#define MSGTR_PLAYLIST_DirectoryTree "Adres��e"

// --- preferences
#define MSGTR_PREFERENCES_Audio MSGTR_EQU_Audio
#define MSGTR_PREFERENCES_Video MSGTR_EQU_Video
#define MSGTR_PREFERENCES_SubtitleOSD "Titulky & OSD"
#define MSGTR_PREFERENCES_Codecs "Kodeky & demuxer"
// Pozn�mka: Pokud zm�n�te MSGTR_PREFERENCES_Misc, ujist�te se pros�m, �e vyhovuje i pro MSGTR_PREFERENCES_FRAME_Misc
#define MSGTR_PREFERENCES_Misc "Ostatn�"

#define MSGTR_PREFERENCES_None "Nic"
#define MSGTR_PREFERENCES_DriverDefault "v�choz� nastaven�"
#define MSGTR_PREFERENCES_AvailableDrivers "Dostupn� ovlada�e:"
#define MSGTR_PREFERENCES_DoNotPlaySound "Nep�ehr�vat zvuk"
#define MSGTR_PREFERENCES_NormalizeSound "Normalizovat zvuk"
#define MSGTR_PREFERENCES_EnableEqualizer "Aktivovat ekvaliz�r"
#define MSGTR_PREFERENCES_SoftwareMixer "Aktivovat softwarov� sm�ova�"
#define MSGTR_PREFERENCES_ExtraStereo "Aktivovat extra stereo"
#define MSGTR_PREFERENCES_Coefficient "Koeficient:"
#define MSGTR_PREFERENCES_AudioDelay "Zpo�d�n� zvuku"
#define MSGTR_PREFERENCES_DoubleBuffer "Aktivovat dvojitou vyrovn�vac� pam�"
#define MSGTR_PREFERENCES_DirectRender "Aktivovat direct rendering"
#define MSGTR_PREFERENCES_FrameDrop "Aktivovat zahazov�n� sn�mk�"
#define MSGTR_PREFERENCES_HFrameDrop "Aktivovat TVRD� zahazov�n� sn�mk� (nebezpe�n�)"
#define MSGTR_PREFERENCES_Flip "P�evr�tit obraz vzh�ru nohama"
#define MSGTR_PREFERENCES_Panscan "Panscan:"
#define MSGTR_PREFERENCES_OSDTimer "�as a ostatn� ukazatele"
#define MSGTR_PREFERENCES_OSDProgress "Pouze ukazatele pozice a nastaven�"
#define MSGTR_PREFERENCES_OSDTimerPercentageTotalTime "�as, procenta a celkov� �as"
#define MSGTR_PREFERENCES_Subtitle "Titulky:"
#define MSGTR_PREFERENCES_SUB_Delay "Zpo�d�n�: "
#define MSGTR_PREFERENCES_SUB_FPS "FPS:"
#define MSGTR_PREFERENCES_SUB_POS "Pozice: "
#define MSGTR_PREFERENCES_SUB_AutoLoad "Vypnout automatick� na�ten� titulk�"
#define MSGTR_PREFERENCES_SUB_Unicode "Titulky v UNICODE"
#define MSGTR_PREFERENCES_SUB_MPSUB "P�ev�st dan� titulky do vlastn�ho form�tu MPlayeru"
#define MSGTR_PREFERENCES_SUB_SRT "P�ev�st dan� titulky do �asov� orientovan�ho form�tu SubViewer (SRT)"
#define MSGTR_PREFERENCES_SUB_Overlap "Zapnout p�ekr�v�n� titulk�"
#define MSGTR_PREFERENCES_Font "Font:"
#define MSGTR_PREFERENCES_FontFactor "Zv�t�en� Fontu:"
#define MSGTR_PREFERENCES_PostProcess "Aktivovat postprocessing"
#define MSGTR_PREFERENCES_AutoQuality "Automatick� ��zen� kvality:"
#define MSGTR_PREFERENCES_NI "Pou��t parser pro neprokl�dan� AVI form�t"
#define MSGTR_PREFERENCES_IDX "Znovu sestavit tabulku index�, pokud je to t�eba"
#define MSGTR_PREFERENCES_VideoCodecFamily "Rodina video kodeku:"
#define MSGTR_PREFERENCES_AudioCodecFamily "Rodina audio kodeku:"
#define MSGTR_PREFERENCES_FRAME_OSD_Level "Typ OSD"
#define MSGTR_PREFERENCES_FRAME_Subtitle "Titulky"
#define MSGTR_PREFERENCES_FRAME_Font "Font"
#define MSGTR_PREFERENCES_FRAME_PostProcess "Postprocessing"
#define MSGTR_PREFERENCES_FRAME_CodecDemuxer "Kodek & demuxer"
#define MSGTR_PREFERENCES_FRAME_Cache "Vyrovn�vac� pam�"
#define MSGTR_PREFERENCES_FRAME_Misc MSGTR_PREFERENCES_Misc
#define MSGTR_PREFERENCES_Audio_Device "Za��zen�:"
#define MSGTR_PREFERENCES_Audio_Mixer "Mix�r:"
#define MSGTR_PREFERENCES_Audio_MixerChannel "Kan�l mix�ru:"
#define MSGTR_PREFERENCES_Message "Pozor, n�kter� nastaven� pot�ebuj� pro svou funkci restartovat p�ehr�v�n�!"
#define MSGTR_PREFERENCES_DXR3_VENC "Video enkod�r:"
#define MSGTR_PREFERENCES_DXR3_LAVC "Pou��t LAVC (FFmpeg)"
#define MSGTR_PREFERENCES_DXR3_FAME "Pou��t FAME"
#define MSGTR_PREFERENCES_FontEncoding1 "Unicode"
#define MSGTR_PREFERENCES_FontEncoding2 "Z�padoevropsk� jazyky (ISO-8859-1)"
#define MSGTR_PREFERENCES_FontEncoding3 "Z�padoevropsk� jazyky s Eurem (ISO-8859-15)"
#define MSGTR_PREFERENCES_FontEncoding4 "Slovansk�/st�edoevropsk� jazyky (ISO-8859-2)"
#define MSGTR_PREFERENCES_FontEncoding5 "Esperanto, gael�tina, malt�z�tina, ture�tina (ISO-8859-3)"
#define MSGTR_PREFERENCES_FontEncoding6 "Star� Baltsk� k�dov�n� (ISO-8859-4)"
#define MSGTR_PREFERENCES_FontEncoding7 "Cyrilice (ISO-8859-5)"
#define MSGTR_PREFERENCES_FontEncoding8 "Arab�tina (ISO-8859-6)"
#define MSGTR_PREFERENCES_FontEncoding9 "Modern� �e�tina (ISO-8859-7)"
#define MSGTR_PREFERENCES_FontEncoding10 "Ture�tina (ISO-8859-9)"
#define MSGTR_PREFERENCES_FontEncoding11 "Baltick� (ISO-8859-13)"
#define MSGTR_PREFERENCES_FontEncoding12 "Kelt�tina (ISO-8859-14)"
#define MSGTR_PREFERENCES_FontEncoding13 "Hebrej�tina (ISO-8859-8)"
#define MSGTR_PREFERENCES_FontEncoding14 "Ru�tina (KOI8-R)"
#define MSGTR_PREFERENCES_FontEncoding15 "Ukrajin�tina, b�loru�tina (KOI8-U/RU)"
#define MSGTR_PREFERENCES_FontEncoding16 "Jednoduch� ��n�tina (CP936)"
#define MSGTR_PREFERENCES_FontEncoding17 "Tradi�n� ��n�tina (BIG5)"
#define MSGTR_PREFERENCES_FontEncoding18 "Japon�tina (SHIFT-JIS)"
#define MSGTR_PREFERENCES_FontEncoding19 "Korej�tina (CP949)"
#define MSGTR_PREFERENCES_FontEncoding20 "Thaj�tina (CP874)"
#define MSGTR_PREFERENCES_FontEncoding21 "Cyrilick� Windows (CP1251)"
#define MSGTR_PREFERENCES_FontEncoding22 "Slovansk�/st�edoevropsk� Windows (CP1250)"
#define MSGTR_PREFERENCES_FontNoAutoScale "Bez automatick� velikosti"
#define MSGTR_PREFERENCES_FontPropWidth "Propor�n� dle ���ky obrazu"
#define MSGTR_PREFERENCES_FontPropHeight "Propor�n� dle v��ky obrazu"
#define MSGTR_PREFERENCES_FontPropDiagonal "Propor�n� dle �hlop���ky"
#define MSGTR_PREFERENCES_FontEncoding "K�dov�n�:"
#define MSGTR_PREFERENCES_FontBlur "Rozmaz�n�:"
#define MSGTR_PREFERENCES_FontOutLine "Obrys:"
#define MSGTR_PREFERENCES_FontTextScale "Velikost textu:"
#define MSGTR_PREFERENCES_FontOSDScale "Velikost OSD:"
#define MSGTR_PREFERENCES_Cache "Zapnout vyrovn�vac� pam�"
#define MSGTR_PREFERENCES_CacheSize "Velikost vyrovn�vac� pam�ti: "
#define MSGTR_PREFERENCES_LoadFullscreen "Spustit p�es celou obrazovku"
#define MSGTR_PREFERENCES_SaveWinPos "Ulo�it pozici okna"
#define MSGTR_PREFERENCES_XSCREENSAVER "Zastavit XScreenSaver"
#define MSGTR_PREFERENCES_PlayBar "Aktivovat playbar"
#define MSGTR_PREFERENCES_AutoSync "Zapnout automatickou synchronizaci"
#define MSGTR_PREFERENCES_AutoSyncValue "Automatick� synchronizace: "
#define MSGTR_PREFERENCES_CDROMDevice "Za��zen� CD-ROM:"
#define MSGTR_PREFERENCES_DVDDevice "Za��zen� DVD:"
#define MSGTR_PREFERENCES_FPS "Sn�mkov� rychlost (FPS):"
#define MSGTR_PREFERENCES_ShowVideoWindow "Zobrazovat video okno p�i ne�innosti"
#define MSGTR_PREFERENCES_ArtsBroken "Nov�j�� verze aRts jsou nekompatibiln� "\
           "s GTK 1.x a zhavaruj� GMPlayer!"

#define MSGTR_ABOUT_UHU "V�voj GUI je sponzorov�n firmou UHU Linux\n"
#define MSGTR_ABOUT_Contributors "P�isp�vatel� k�du a dokumentace\n"
#define MSGTR_ABOUT_Codecs_libs_contributions "Kodeky a knihovny t�et�ch stran\n"
#define MSGTR_ABOUT_Translations "P�eklady\n"
#define MSGTR_ABOUT_Skins "Skiny\n"

// --- messagebox
#define MSGTR_MSGBOX_LABEL_FatalError "Kritick� chyba!"
#define MSGTR_MSGBOX_LABEL_Error "Chyba!"
#define MSGTR_MSGBOX_LABEL_Warning "Varov�n�!"

// bitmap.c

#define MSGTR_NotEnoughMemoryC32To1 "[c32to1] nedostatek pam�ti pro obr�zek\n"
#define MSGTR_NotEnoughMemoryC1To32 "[c1to32] nedostatek pam�ti pro obr�zek\n"

// cfg.c

#define MSGTR_ConfigFileReadError "[cfg] chyba p�i �ten� konfigura�n�ho souboru...\n"
#define MSGTR_UnableToSaveOption "[cfg] Nelze ulo�it volbu '%s'.\n"

// interface.c

#define MSGTR_DeletingSubtitles "[GUI] Ma�u titulky.\n"
#define MSGTR_LoadingSubtitles "[GUI] Na��t�m titulky: %s\n"
#define MSGTR_AddingVideoFilter "[GUI] P�id�v�m video filtr: %s\n"
#define MSGTR_RemovingVideoFilter "[GUI] Odstra�uji video filtr: %s\n"

// mw.c

#define MSGTR_NotAFile "Toto nevypad� jako soubor: %s !\n"

// ws.c

#define MSGTR_WS_CouldNotOpenDisplay "[ws] Nelze otev��t display.\n"
#define MSGTR_WS_RemoteDisplay "[ws] Vzd�len� display, vyp�n�m XMITSHM.\n"
#define MSGTR_WS_NoXshm "[ws] Promi�te, ale v� syst�m nepodporuje roz���en� X shared memory.\n"
#define MSGTR_WS_NoXshape "[ws] Promi�te, ale v� syst�m nepodporuje roz���en� XShape.\n"
#define MSGTR_WS_ColorDepthTooLow "[ws] Promi�te, ale barevn� hloubka je p��li� mal�.\n"
#define MSGTR_WS_TooManyOpenWindows "[ws] P��li� mnoho otev�en�ch oken.\n"
#define MSGTR_WS_ShmError "[ws] chyba roz���en� shared memory\n"
#define MSGTR_WS_NotEnoughMemoryDrawBuffer "[ws] Promi�te, nedostatek pam�ti pro vykreslen� bufferu.\n"
#define MSGTR_WS_DpmsUnavailable "DPMS nen� k dispozici?\n"
#define MSGTR_WS_DpmsNotEnabled "Nelze zapnout DPMS.\n"

// wsxdnd.c

#define MSGTR_WS_NotAFile "Toto nevypad� jako soubor...\n"
#define MSGTR_WS_DDNothing "D&D: Nic se nevr�tilo!\n"

#endif

// ======================= VO Video Output drivers ========================

#define MSGTR_VOincompCodec "Vybran� video_out za��zen� je nekompatibiln� s t�mto kodekem.\n"\
                "Zkuste p�idat filtr scale, �ili -vf spp,scale nam�sto -vf spp.\n"
#define MSGTR_VO_GenericError "Tato chyba nastala"
#define MSGTR_VO_UnableToAccess "Nem�m p��stup k"
#define MSGTR_VO_ExistsButNoDirectory "ji� existuje, ale nen� to adres��."
#define MSGTR_VO_DirExistsButNotWritable "V�stupn� adres�� ji� existuje, ale nelze do n�j zapisovat."
#define MSGTR_VO_DirExistsAndIsWritable "V�stupn� adres�� ji� existuje a lze do n�j zapisovat."
#define MSGTR_VO_CantCreateDirectory "Nelze vytvo�it v�stupn� adres��."
#define MSGTR_VO_CantCreateFile "Nelze vytvo�it v�stupn� soubor."
#define MSGTR_VO_DirectoryCreateSuccess "�sp�n� vytvo�en v�stupn� adres��."
#define MSGTR_VO_ParsingSuboptions "Interpretuji podvolby."
#define MSGTR_VO_SuboptionsParsedOK "Podvolby interpretov�ny OK."
#define MSGTR_VO_ValueOutOfRange "hodnota mimo rozsah"
#define MSGTR_VO_NoValueSpecified "Nebyla zad�na hodnota."
#define MSGTR_VO_UnknownSuboptions "nezn�m�(�) podvolba(y)"

// vo_aa.c

#define MSGTR_VO_AA_HelpHeader "\n\nZde jsou podvolby aalib vo_aa:\n"
#define MSGTR_VO_AA_AdditionalOptions "Dodate�n� volby vo_aa zaji��uj�:\n" \
"  help        vyp��e tuto n�pov�du\n" \
"  osdcolor    nastav� barvu OSD\n  subcolor    nastav� barvu titulk�\n" \
"        parametry barev jsou:\n           0 : normal\n" \
"           1 : dim\n           2 : bold\n           3 : boldfont\n" \
"           4 : reverse\n           5 : special\n\n\n"

// vo_jpeg.c
#define MSGTR_VO_JPEG_ProgressiveJPEG "Zapnut progresivn� JPEG."
#define MSGTR_VO_JPEG_NoProgressiveJPEG "Vypnut progresivn� JPEG."
#define MSGTR_VO_JPEG_BaselineJPEG "Zapnut z�kladn� JPEG."
#define MSGTR_VO_JPEG_NoBaselineJPEG "Vypnut z�kladn� JPEG."

// vo_pnm.c
#define MSGTR_VO_PNM_ASCIIMode "Zapnut ASCII re�im."
#define MSGTR_VO_PNM_RawMode "Zapnut surov� (Raw) re�im."
#define MSGTR_VO_PNM_PPMType "Budou zapisov�ny PPM soubory."
#define MSGTR_VO_PNM_PGMType "Budou zapisov�ny PGM soubory."
#define MSGTR_VO_PNM_PGMYUVType "Budou zapisov�ny PGMYUV soubory."

// vo_yuv4mpeg.c
#define MSGTR_VO_YUV4MPEG_InterlacedHeightDivisibleBy4 "Prokl�dan� re�im obrazu vy�aduje v��ku obrazu d�litelnou 4."
#define MSGTR_VO_YUV4MPEG_InterlacedLineBufAllocFail "Nelze alokovat ��dkovou vyrovn�vac� pam� pro re�im prokl�dan�ho obrazu."
#define MSGTR_VO_YUV4MPEG_InterlacedInputNotRGB "Vstup nen� RGB, nelze odd�lit jasovou slo�ku podle pol�!"
#define MSGTR_VO_YUV4MPEG_WidthDivisibleBy2 "���ka obrazu mus� b�t d�liteln� 2."
#define MSGTR_VO_YUV4MPEG_NoMemRGBFrameBuf "Nen� dostatek pam�ti pro alokaci RGB framebufferu."
#define MSGTR_VO_YUV4MPEG_OutFileOpenError "Nelze z�skat pam� nebo ukazatel souboru pro z�pis \"%s\"!"
#define MSGTR_VO_YUV4MPEG_OutFileWriteError "Chyba p�i z�pisu obr�zku na v�stup!"
#define MSGTR_VO_YUV4MPEG_UnknownSubDev "Nezn�m� podza��zen�: %s"
#define MSGTR_VO_YUV4MPEG_InterlacedTFFMode "Pou��v�m prokl�dan� v�stupn� re�im, horn� pole nap�ed."
#define MSGTR_VO_YUV4MPEG_InterlacedBFFMode "Pou��v�m prokl�dan� v�stupn� re�im, doln� pole nap�ed."
#define MSGTR_VO_YUV4MPEG_ProgressiveMode "Pou��v�m (v�choz�) neprokl�dan� sn�mkov� re�im."

// sub.c
#define MSGTR_VO_SUB_Seekbar "Postup"
#define MSGTR_VO_SUB_Play "Play"
#define MSGTR_VO_SUB_Pause "Pauza"
#define MSGTR_VO_SUB_Stop "Stop"
#define MSGTR_VO_SUB_Rewind "Zp�t"
#define MSGTR_VO_SUB_Forward "Vp�ed"
#define MSGTR_VO_SUB_Clock "Hodiny"
#define MSGTR_VO_SUB_Contrast "Kontrast"
#define MSGTR_VO_SUB_Saturation "Sytost"
#define MSGTR_VO_SUB_Volume "Hlasitost"
#define MSGTR_VO_SUB_Brightness "Jas"
#define MSGTR_VO_SUB_Hue "Barevn� t�n"

// vo_xv.c
#define MSGTR_VO_XV_ImagedimTooHigh "Rozm�ry zdrojov�ho obrazu jsou p��li� velk�: %ux%u (maximum je %ux%u)\n"

// Old vo drivers that have been replaced

#define MSGTR_VO_PGM_HasBeenReplaced "V�stupn� videorozhran� pgm bylo nahrazeno -vo pnm:pgmyuv.\n"
#define MSGTR_VO_MD5_HasBeenReplaced "V�stupn� videorozhran� md5 bylo nahrazeno -vo md5sum.\n"

// ======================= AO Audio Output drivers ========================

// libao2 

// audio_out.c
#define MSGTR_AO_ALSA9_1x_Removed "audio_out: moduly alsa9 a alsa1x byly odstran�ny, m�sto nich pou�ijte -ao alsa.\n"

// ao_oss.c
#define MSGTR_AO_OSS_CantOpenMixer "[AO OSS] audio_setup: Nelze otev��t mix�n� za��zen� %s: %s\n"
#define MSGTR_AO_OSS_ChanNotFound "[AO OSS] audio_setup: Mixer zvukov� karty nem� kan�l '%s', pou��v�m v�choz�.\n"
#define MSGTR_AO_OSS_CantOpenDev "[AO OSS] audio_setup: Nelze otev��t zvukov� za��zen� %s: %s\n"
#define MSGTR_AO_OSS_CantMakeFd "[AO OSS] audio_setup: Nelze prov�st blokov�n� souborov�ho deskriptoru: %s\n"
#define MSGTR_AO_OSS_CantSet "[AO OSS] Zvukov� za��zen� %s nelze nastavit na v�stup %s, zkou��m %s...\n"
#define MSGTR_AO_OSS_CantSetChans "[AO OSS] audio_setup: Selhalo nastaven� v�stupn�ho zvukov�ho za��zen� na %d kan�l�.\n"
#define MSGTR_AO_OSS_CantUseGetospace "[AO OSS] audio_setup: Ovlada� nepodporuje SNDCTL_DSP_GETOSPACE :-(\n"
#define MSGTR_AO_OSS_CantUseSelect "[AO OSS]\n   ***  Ovlada� Va�� zvukov� karty NEPODPORUJE select()  ***\n P�ekompilujte MPlayer s #undef HAVE_AUDIO_SELECT v config.h !\n\n"
#define MSGTR_AO_OSS_CantReopen "[AO OSS]\nKritick� chyba: *** NELZE ZNOVUOTEV��T / RESTARTOVAT ZVUKOV� ZA��ZEN� *** %s\n"
#define MSGTR_AO_OSS_UnknownUnsupportedFormat "[AO OSS] Nezn�m�/nepodporovan� OSS form�t: %x.\n"

// ao_arts.c
#define MSGTR_AO_ARTS_CantInit "[AO ARTS] %s\n"
#define MSGTR_AO_ARTS_ServerConnect "[AO ARTS] P�ipojen ke zvukov�mu serveru.\n"
#define MSGTR_AO_ARTS_CantOpenStream "[AO ARTS] Nelze otev��t datov� proud.\n"
#define MSGTR_AO_ARTS_StreamOpen "[AO ARTS] Datov� proud otev�en.\n"
#define MSGTR_AO_ARTS_BufferSize "[AO ARTS] velikost vyrovn�vac� pam�ti: %d\n"

// ao_dxr2.c
#define MSGTR_AO_DXR2_SetVolFailed "[AO DXR2] Nastaven� hlasitosti na %d selhalo.\n"
#define MSGTR_AO_DXR2_UnsupSamplerate "[AO DXR2] %d Hz nen� podporov�no, zkuste p�evzorkovat.\n"

// ao_esd.c
#define MSGTR_AO_ESD_CantOpenSound "[AO ESD] esd_open_sound selhalo: %s\n"
#define MSGTR_AO_ESD_LatencyInfo "[AO ESD] latence: [server: %0.2fs, s��: %0.2fs] (upravuji %0.2fs)\n"
#define MSGTR_AO_ESD_CantOpenPBStream "[AO ESD] selhalo otev�en� datov�ho proudu ESD pro p�ehr�v�n�: %s\n"

// ao_mpegpes.c
#define MSGTR_AO_MPEGPES_CantSetMixer "[AO MPEGPES] selhalo nastaven� DVB zvukov�ho mixeru: %s.\n" 
#define MSGTR_AO_MPEGPES_UnsupSamplerate "[AO MPEGPES] %d Hz nen� podporov�no, zkuste p�evzorkovat.\n"

// ao_null.c
// This one desn't even  have any mp_msg nor printf's?? [CHECK]

// ao_pcm.c
#define MSGTR_AO_PCM_FileInfo "[AO PCM] Soubor: %s (%s)\nPCM: Vzorkov�n�: %iHz Kan�l(y): %s Form�t %s\n"
#define MSGTR_AO_PCM_HintInfo "[AO PCM] Info:  Nejrychlej�� extrakce dos�hnete s -vc null -vo null -ao pcm:fast\n[AO PCM] Info: Pro z�pis WAVE soubor� pou�ijte -ao pcm:waveheader (v�choz�).\n"
#define MSGTR_AO_PCM_CantOpenOutputFile "[AO PCM] Selhalo otev�en� %s pro z�pis!\n"

// ao_sdl.c
#define MSGTR_AO_SDL_INFO "[AO SDL] Vzorkov�n�: %iHz Kan�l(y): %s Form�t %s\n"
#define MSGTR_AO_SDL_DriverInfo "[AO SDL] pou��v�m zvukov� ovlada� %s.\n"
#define MSGTR_AO_SDL_UnsupportedAudioFmt "[AO SDL] Nepodporovan� form�t zvuku: 0x%x.\n"
#define MSGTR_AO_SDL_CantInit "[AO SDL] Inicializace SDL Audio selhala: %s\n"
#define MSGTR_AO_SDL_CantOpenAudio "[AO SDL] Nelze otev��t zvuk: %s\n"

// ao_sgi.c
#define MSGTR_AO_SGI_INFO "[AO SGI] ovl�d�n�.\n"
#define MSGTR_AO_SGI_InitInfo "[AO SGI] init: Vzorkov�n�: %iHz Kan�l(y): %s Form�t %s\n"
#define MSGTR_AO_SGI_InvalidDevice "[AO SGI] p�ehr�v�n�: neplatn� za��zen�.\n"
#define MSGTR_AO_SGI_CantSetParms_Samplerate "[AO SGI] init: selhalo setparams: %s\nNelze nastavit po�adovan� vzorkov�n�.\n"
#define MSGTR_AO_SGI_CantSetAlRate "[AO SGI] init: AL_RATE nebyl p�ijat dan�m zdrojem.\n"
#define MSGTR_AO_SGI_CantGetParms "[AO SGI] init: selhalo getparams: %s\n"
#define MSGTR_AO_SGI_SampleRateInfo "[AO SGI] init: vzorkov�n� je nyn� %lf (po�adovan� kmito�et je %lf)\n"
#define MSGTR_AO_SGI_InitConfigError "[AO SGI] init: %s\n"
#define MSGTR_AO_SGI_InitOpenAudioFailed "[AO SGI] init: Nelze otev��t zvukov� kan�l: %s\n"
#define MSGTR_AO_SGI_Uninit "[AO SGI] uninit: ...\n"
#define MSGTR_AO_SGI_Reset "[AO SGI] reset: ...\n"
#define MSGTR_AO_SGI_PauseInfo "[AO SGI] audio_pause: ...\n"
#define MSGTR_AO_SGI_ResumeInfo "[AO SGI] audio_resume: ...\n"

// ao_sun.c
#define MSGTR_AO_SUN_RtscSetinfoFailed "[AO SUN] rtsc: selhalo SETINFO.\n"
#define MSGTR_AO_SUN_RtscWriteFailed "[AO SUN] rtsc: z�pis selhal.\n"
#define MSGTR_AO_SUN_CantOpenAudioDev "[AO SUN] Nelze otev��t zvukov� za��zen� %s, %s  -> nebude zvuk.\n"
#define MSGTR_AO_SUN_UnsupSampleRate "[AO SUN] audio_setup: Va�e karta nepodporuje %d kan�lov�, %s, %d Hz vzorkov�n�.\n"
#define MSGTR_AO_SUN_CantUseSelect "[AO SUN]\n   ***  Ovlada� Va�� zvukov� karty NEPODPORUJE select()  ***\n P�ekompilujte MPlayer s #undef HAVE_AUDIO_SELECT v config.h !\n\n"
#define MSGTR_AO_SUN_CantReopenReset "[AO SUN]\nKritick� chyba: *** NELZE ZNOVUOTEV��T / RESTARTOVAT ZVUKOV� ZA��ZEN� (%s) ***\n"

// ao_alsa5.c
#define MSGTR_AO_ALSA5_InitInfo "[AO ALSA5] alsa-init: po�adovan� form�t: %d Hz, %d kan�l(�), %s\n"
#define MSGTR_AO_ALSA5_SoundCardNotFound "[AO ALSA5] alsa-init: ��dn� zvukov� karta nebyla nalezena.\n"
#define MSGTR_AO_ALSA5_InvalidFormatReq "[AO ALSA5] alsa-init: po�adov�n neplatn� form�t (%s) - v�stup odpojen.\n"
#define MSGTR_AO_ALSA5_PlayBackError "[AO ALSA5] alsa-init: chyba otev�en� p�ehr�v�n� zvuku: %s\n"
#define MSGTR_AO_ALSA5_PcmInfoError "[AO ALSA5] alsa-init: chyba v PCM info: %s\n"
#define MSGTR_AO_ALSA5_SoundcardsFound "[AO ALSA5] alsa-init: nalezeno %d zvukov�ch karet, pou��v�m: %s\n"
#define MSGTR_AO_ALSA5_PcmChanInfoError "[AO ALSA5] alsa-init: chyba info v PCM kan�lu: %s\n"
#define MSGTR_AO_ALSA5_CantSetParms "[AO ALSA5] alsa-init: chyba p�i nastavov�n� parametr�: %s\n"
#define MSGTR_AO_ALSA5_CantSetChan "[AO ALSA5] alsa-init: chyba p�i nastavov�n� kan�lu: %s\n"
#define MSGTR_AO_ALSA5_ChanPrepareError "[AO ALSA5] alsa-init: chyba p�i p��prav� kan�lu: %s\n"
#define MSGTR_AO_ALSA5_DrainError "[AO ALSA5] alsa-uninit: chyba playback drain: %s\n"
#define MSGTR_AO_ALSA5_FlushError "[AO ALSA5] alsa-uninit: chyba playback flush: %s\n" //to jsou n�zvy �e by jeden pad
#define MSGTR_AO_ALSA5_PcmCloseError "[AO ALSA5] alsa-uninit: chyba uzav�en� PCM: %s\n"
#define MSGTR_AO_ALSA5_ResetDrainError "[AO ALSA5] alsa-reset: chyba playback drain: %s\n"
#define MSGTR_AO_ALSA5_ResetFlushError "[AO ALSA5] alsa-reset: chyba playback flush: %s\n"
#define MSGTR_AO_ALSA5_ResetChanPrepareError "[AO ALSA5] alsa-reset: chyba p�i p��prav� kan�l�: %s\n"
#define MSGTR_AO_ALSA5_PauseDrainError "[AO ALSA5] alsa-pause: chyba playback drain: %s\n"
#define MSGTR_AO_ALSA5_PauseFlushError "[AO ALSA5] alsa-pause: chyba playback flush: %s\n"
#define MSGTR_AO_ALSA5_ResumePrepareError "[AO ALSA5] alsa-resume: chyba p�i p��prav� kan�l�: %s\n"
#define MSGTR_AO_ALSA5_Underrun "[AO ALSA5] alsa-play: podte�en� v alsa, restartuji proud.\n"
#define MSGTR_AO_ALSA5_PlaybackPrepareError "[AO ALSA5] alsa-play: chyba p��pravy p�ehr�v�n� zvuku: %s\n"
#define MSGTR_AO_ALSA5_WriteErrorAfterReset "[AO ALSA5] alsa-play: chyba p�i z�pisu po restartu: %s - vzd�v�m to.\n"
#define MSGTR_AO_ALSA5_OutPutError "[AO ALSA5] alsa-play: chyba v�stupu: %s\n"

// ao_plugin.c

#define MSGTR_AO_PLUGIN_InvalidPlugin "[AO PLUGIN] neplatn� z�suvn� modul: %s\n"

// ======================= AF Audio Filters ================================

// libaf 

// af_ladspa.c

#define MSGTR_AF_LADSPA_AvailableLabels "dostupn� n�zvy v"
#define MSGTR_AF_LADSPA_WarnNoInputs "VAROV�N�! Tento LADSPA plugin nem� audio vstupy.\n  Vstupn� audio sign�l bude ztracen."
#define MSGTR_AF_LADSPA_ErrMultiChannel "V�cekan�lov� (>2) pluginy nejsou podporov�ny (zat�m).\n  Pou��vejte pouze mono a stereo pluginy."
#define MSGTR_AF_LADSPA_ErrNoOutputs "Tento LADSPA plugin nem� audio v�stupy."
#define MSGTR_AF_LADSPA_ErrInOutDiff "Po�et audio vstup� LADSPA pluginu je odli�n� od po�tu audio v�stup�."
#define MSGTR_AF_LADSPA_ErrFailedToLoad "selhalo na�ten�"
#define MSGTR_AF_LADSPA_ErrNoDescriptor "Nelze nal�zt funkci ladspa_descriptor() v uveden� knihovn�."
#define MSGTR_AF_LADSPA_ErrLabelNotFound "Nelze nal�zt po�adovan� n�zev v knihovn� plugin�."
#define MSGTR_AF_LADSPA_ErrNoSuboptions "Nebyla zad�ny ��dn� podvolby."
#define MSGTR_AF_LADSPA_ErrNoLibFile "Nebyla zad�na ��dn� knihovna."
#define MSGTR_AF_LADSPA_ErrNoLabel "Nebyl zad�n n�zev ��dn�ho filtru."
#define MSGTR_AF_LADSPA_ErrNotEnoughControls "Na p��kazov�m ��dku bylo uvedeno m�lo voleb."
#define MSGTR_AF_LADSPA_ErrControlBelow "%s: Vstupn� voli� #%d je ni��� ne� minim�ln� hodnota %0.4f.\n"
#define MSGTR_AF_LADSPA_ErrControlAbove "%s: Vstupn� voli� #%d je vy��� ne� maxim�ln� hodnota %0.4f.\n"

// format.c

#define MSGTR_AF_FORMAT_UnknownFormat "nezn�m� form�t "

// ========================== INPUT =========================================

// joystick.c

#define MSGTR_INPUT_JOYSTICK_Opening "Otev�r�m za��zen� joysticku %s\n"
#define MSGTR_INPUT_JOYSTICK_CantOpen "Nelze otev��t za��zen� joysticku %s: %s\n"
#define MSGTR_INPUT_JOYSTICK_ErrReading "Chyba p�i �ten� za��zen� joysticku: %s\n"
#define MSGTR_INPUT_JOYSTICK_LoosingBytes "Joystick: Uvolnili jsme %d bajt� dat\n"
#define MSGTR_INPUT_JOYSTICK_WarnLostSync "Joystick: warning init event, ztratili jsme synchronizaci s ovlada�em.\n"
#define MSGTR_INPUT_JOYSTICK_WarnUnknownEvent "Joystick: varov�n�, nezn�m� typ ud�losti %d\n"

// input.c

#define MSGTR_INPUT_INPUT_ErrCantRegister2ManyCmdFds "P��li� mnoho souborov�ch deskriptor� p��kaz�, nelze registrovat\n deskriptor souboru %d.\n"
#define MSGTR_INPUT_INPUT_ErrCantRegister2ManyKeyFds "P��li� mnoho souborov�ch deskriptor� kl�vesnice, nelze registrovat\n deskriptor souboru %d.\n"
#define MSGTR_INPUT_INPUT_ErrArgMustBeInt "P��kaz %s: argument %d nen� typu integer.\n"
#define MSGTR_INPUT_INPUT_ErrArgMustBeFloat "P��kaz %s: argument %d nen� typu float.\n"
#define MSGTR_INPUT_INPUT_ErrUnterminatedArg "P��kaz %s: argument %d nen� ukon�en.\n"
#define MSGTR_INPUT_INPUT_ErrUnknownArg "Nezn�m� argument %d\n"
#define MSGTR_INPUT_INPUT_Err2FewArgs "P��kaz %s vy�aduje aspo� %d argument�, nalezli jsme jich v�ak pouze %d.\n"
#define MSGTR_INPUT_INPUT_ErrReadingCmdFd "Chyba p�i �ten� p��kazov�ho deskriptoru souboru %d: %s\n"
#define MSGTR_INPUT_INPUT_ErrCmdBufferFullDroppingContent "Vyrovn�vac� pam� deskriptoru souboru p��kaz� %d je pln�: zahazuji obsah.\n"
#define MSGTR_INPUT_INPUT_ErrInvalidCommandForKey "�patn� p��kaz pro p�i�azen� kl�vese %s"
#define MSGTR_INPUT_INPUT_ErrSelect "Chyba v�b�ru: %s\n"
#define MSGTR_INPUT_INPUT_ErrOnKeyInFd "Chyba v deskriptoru souboru kl�vesov�ho vstupu %d\n"
#define MSGTR_INPUT_INPUT_ErrDeadKeyOnFd "Vstup mrtv� kl�vesy z deskriptoru souboru %d\n"
#define MSGTR_INPUT_INPUT_Err2ManyKeyDowns "P��li� mnoho sou�asn� stisknut�ch kl�ves\n"
#define MSGTR_INPUT_INPUT_ErrOnCmdFd "Chyba na cmd fd %d\n"
#define MSGTR_INPUT_INPUT_ErrReadingInputConfig "Chyba p�i �ten� input konfigura�n�ho souboru %s: %s\n"
#define MSGTR_INPUT_INPUT_ErrUnknownKey "Nezn�m� kl�vesa '%s'\n"
#define MSGTR_INPUT_INPUT_ErrUnfinishedBinding "Nedokon�en� p�i�azen� %s\n"
#define MSGTR_INPUT_INPUT_ErrBuffer2SmallForKeyName "P��li� mal� vyrovn�vac� pam� pro tento n�zev kl�vesy: %s\n"
#define MSGTR_INPUT_INPUT_ErrNoCmdForKey "Nenalezen p��kaz pro tla��tko %s"
#define MSGTR_INPUT_INPUT_ErrBuffer2SmallForCmd "P��li� mal� vyrovn�vac� pam� pro p��kaz %s\n"
#define MSGTR_INPUT_INPUT_ErrWhyHere "Co tady d�l�me?\n"
#define MSGTR_INPUT_INPUT_ErrCantInitJoystick "Nelze inicializovat vstupn� joystick\n"
#define MSGTR_INPUT_INPUT_ErrCantStatFile "Nelze stat %s: %s\n"
#define MSGTR_INPUT_INPUT_ErrCantOpenFile "Nelze otev��t %s: %s\n"

// ========================== LIBMPDEMUX ===================================

// url.c

#define MSGTR_MPDEMUX_URL_StringAlreadyEscaped "Zd� se, �e je ji� �et�zec eskejpov�n v url_escape %c%c1%c2\n"

// ai_alsa1x.c

#define MSGTR_MPDEMUX_AIALSA1X_CannotSetSamplerate "Nelze nastavit vzorkovac� kmito�et.\n"
#define MSGTR_MPDEMUX_AIALSA1X_CannotSetBufferTime "Nelze nastavit �as vyrovn�vac� pam�ti.\n"
#define MSGTR_MPDEMUX_AIALSA1X_CannotSetPeriodTime "Nelze nastavit �as opakov�n�.\n"

// ai_alsa1x.c / ai_alsa.c

#define MSGTR_MPDEMUX_AIALSA_PcmBrokenConfig "Vadn� konfigurace pro toto PCM: ��dn� konfigurace nejsou k dispozici.\n"
#define MSGTR_MPDEMUX_AIALSA_UnavailableAccessType "Typ p��stupu nen� k dispozici.\n"
#define MSGTR_MPDEMUX_AIALSA_UnavailableSampleFmt "Form�t vzorku nen� k dispozici.\n"
#define MSGTR_MPDEMUX_AIALSA_UnavailableChanCount "Po�et kan�l� nen� k dispozici - vrac�m v�choz�: %d\n"
#define MSGTR_MPDEMUX_AIALSA_CannotInstallHWParams "Nelze nainstalovat hardwarov� parametry: %s"
#define MSGTR_MPDEMUX_AIALSA_PeriodEqualsBufferSize "Nelze pou��t opakov�n� odpov�daj�c� velikosti vyrovn�vac� pam�ti (%u == %lu)\n"
#define MSGTR_MPDEMUX_AIALSA_CannotInstallSWParams "Nelze nainstalovat softwarov� parametry:\n"
#define MSGTR_MPDEMUX_AIALSA_ErrorOpeningAudio "Chyba p�i otev�r�n� zvuku: %s\n"
#define MSGTR_MPDEMUX_AIALSA_AlsaStatusError "ALSA status error: %s"
#define MSGTR_MPDEMUX_AIALSA_AlsaXRUN "ALSA xrun!!! (minim�ln� %.3f ms dlouh�)\n"
#define MSGTR_MPDEMUX_AIALSA_AlsaStatus "ALSA Status:\n"
#define MSGTR_MPDEMUX_AIALSA_AlsaXRUNPrepareError "ALSA xrun: prepare error: %s"
#define MSGTR_MPDEMUX_AIALSA_AlsaReadWriteError "ALSA chyba �ten�/z�pisu"

// ai_oss.c

#define MSGTR_MPDEMUX_AIOSS_Unable2SetChanCount "Nelze nastavit po�et kan�l�: %d\n"
#define MSGTR_MPDEMUX_AIOSS_Unable2SetStereo "Nelze nastavit stereo: %d\n"
#define MSGTR_MPDEMUX_AIOSS_Unable2Open "Nelze otev��t '%s': %s\n"
#define MSGTR_MPDEMUX_AIOSS_UnsupportedFmt "nepodporovan� form�t\n"
#define MSGTR_MPDEMUX_AIOSS_Unable2SetAudioFmt "Nelze nastavit audio form�t."
#define MSGTR_MPDEMUX_AIOSS_Unable2SetSamplerate "Nelze nastavit vzorkovac� kmito�et: %d\n"
#define MSGTR_MPDEMUX_AIOSS_Unable2SetTrigger "Nelze nastavit spou��: %d\n"
#define MSGTR_MPDEMUX_AIOSS_Unable2GetBlockSize "Nelze zjistit velikost bloku!\n"
#define MSGTR_MPDEMUX_AIOSS_AudioBlockSizeZero "Velikost zvukov�ho bloku je nulov�, nastavuji ji na %d!\n"
#define MSGTR_MPDEMUX_AIOSS_AudioBlockSize2Low "Velikost zvukov�ho bloku je p��li� mal�, nastavuji ji na %d!\n"

// asfheader.c

#define MSGTR_MPDEMUX_ASFHDR_HeaderSizeOver1MB "FATAL: velikost hlavi�ky je v�t�� ne� 1 MB (%d)!\nKontaktujte pros�m tv�rce MPlayeru a nahrajte/po�lete jim tento soubor.\n"
#define MSGTR_MPDEMUX_ASFHDR_HeaderMallocFailed "Nemohu alokovat %d bajt� pro hlavi�ku.\n"
#define MSGTR_MPDEMUX_ASFHDR_EOFWhileReadingHeader "konec souboru p�i �ten� ASF hlavi�ky, po�kozen�/ne�pln� soubor?\n"
#define MSGTR_MPDEMUX_ASFHDR_DVRWantsLibavformat "DVR bude pravd�podobn� pracovat pouze s libavformat, v p��pad� probl�m� zkuste -demuxer 35\n"
#define MSGTR_MPDEMUX_ASFHDR_NoDataChunkAfterHeader "Po hlavi�ce nen�sleduje ��dn� datov� chunk!\n"
#define MSGTR_MPDEMUX_ASFHDR_AudioVideoHeaderNotFound "ASF: ani audio ani video hlavi�ky nebyly nalezeny - vadn� soubor?\n"
#define MSGTR_MPDEMUX_ASFHDR_InvalidLengthInASFHeader "Nespr�vn� d�lka v hlavi�ce ASF!\n"

// asf_mmst_streaming.c

#define MSGTR_MPDEMUX_MMST_WriteError "chyba z�pisu\n"
#define MSGTR_MPDEMUX_MMST_EOFAlert "\nV�straha! EOF\n"
#define MSGTR_MPDEMUX_MMST_PreHeaderReadFailed "�ten� pre-hlavi�ky selhalo\n"
#define MSGTR_MPDEMUX_MMST_InvalidHeaderSize "�patn� velikost hlavi�ky, vzd�v�m to.\n"
#define MSGTR_MPDEMUX_MMST_HeaderDataReadFailed "�ten� dat hlavi�ky selhalo.\n"
#define MSGTR_MPDEMUX_MMST_packet_lenReadFailed "Selhalo �ten� packet_len.\n"
#define MSGTR_MPDEMUX_MMST_InvalidRTSPPacketSize "�patn� velikost RTSP paketu, vzd�v�m to.\n"
#define MSGTR_MPDEMUX_MMST_CmdDataReadFailed "Selhalo �ten� p��kazov�ch dat.\n"
#define MSGTR_MPDEMUX_MMST_HeaderObject "hlavi�kov� objekt\n"
#define MSGTR_MPDEMUX_MMST_DataObject "datov� objekt\n"
#define MSGTR_MPDEMUX_MMST_FileObjectPacketLen "souborov� objekt, d�lka paketu = %d (%d)\n"
#define MSGTR_MPDEMUX_MMST_StreamObjectStreamID "proudov� objekt, ID datov�ho proudu: %d\n"
#define MSGTR_MPDEMUX_MMST_2ManyStreamID "P��li� mnoho ID, proud p�esko�en."
#define MSGTR_MPDEMUX_MMST_UnknownObject "nezn�m� objekt\n"
#define MSGTR_MPDEMUX_MMST_MediaDataReadFailed "�ten� media dat selhalo.\n"
#define MSGTR_MPDEMUX_MMST_MissingSignature "chyb� signatura\n"
#define MSGTR_MPDEMUX_MMST_PatentedTechnologyJoke "V�e hotovo. D�kujeme, �e jste si st�hli medi�ln� soubor obsahuj�c� propriet�rn� a patentovanou technologii.\n"
#define MSGTR_MPDEMUX_MMST_UnknownCmd "nezn�m� p��kaz %02x\n"
#define MSGTR_MPDEMUX_MMST_GetMediaPacketErr "chyba get_media_packet: %s\n"
#define MSGTR_MPDEMUX_MMST_Connected "P�ipojeno\n"

// asf_streaming.c

#define MSGTR_MPDEMUX_ASF_StreamChunkSize2Small "Ahhhh, velikost stream_chunck je p��li� mal�: %d\n"
#define MSGTR_MPDEMUX_ASF_SizeConfirmMismatch "size_confirm nesouhlas�!: %d %d\n"
#define MSGTR_MPDEMUX_ASF_WarnDropHeader "Varov�n�: zahozena hlavi�ka ????\n"
#define MSGTR_MPDEMUX_ASF_ErrorParsingChunkHeader "Chyba p�i parsov�n� hlavi�ky chunku\n"
#define MSGTR_MPDEMUX_ASF_NoHeaderAtFirstChunk "Hlavi�ka nedo�la jako prvn� chunk !!!!\n"
#define MSGTR_MPDEMUX_ASF_BufferMallocFailed "Chyba: nelze alokovat %d bajt� vyrovn�vac� pam�ti.\n"
#define MSGTR_MPDEMUX_ASF_ErrReadingNetworkStream "Chyba p�i �ten� proudu ze s�t�.\n"
#define MSGTR_MPDEMUX_ASF_ErrChunk2Small "Chyba: chunk je p��li� mal�.\n"
#define MSGTR_MPDEMUX_ASF_ErrSubChunkNumberInvalid "Chyba: po�et sub chunk� je nespr�vn�.\n"
#define MSGTR_MPDEMUX_ASF_Bandwidth2SmallCannotPlay "P��li� mal� p�enosov� rychlost, soubor nelze p�ehr�vat!\n"
#define MSGTR_MPDEMUX_ASF_Bandwidth2SmallDeselectedAudio "P��li� mal� p�enosov� rychlost, odvolan� audio proud.\n"
#define MSGTR_MPDEMUX_ASF_Bandwidth2SmallDeselectedVideo "P��li� mal� p�enosov� rychlost, odvolan� video proud.\n"
#define MSGTR_MPDEMUX_ASF_InvalidLenInHeader "Nespr�vn� d�lka v ASF hlavi�ce!\n"
#define MSGTR_MPDEMUX_ASF_ErrReadingChunkHeader "Chyba p�i �ten� hlavi�ky chunku.\n"
#define MSGTR_MPDEMUX_ASF_ErrChunkBiggerThanPacket "Chyba: chunk_size > packet_size\n"
#define MSGTR_MPDEMUX_ASF_ErrReadingChunk "Chyba p�i �ten� chunku.\n"
#define MSGTR_MPDEMUX_ASF_ASFRedirector "=====> ASF Redirector\n"
#define MSGTR_MPDEMUX_ASF_InvalidProxyURL "neplatn� proxy URL\n"
#define MSGTR_MPDEMUX_ASF_UnknownASFStreamType "nezn�m� typ ASF proudu\n"
#define MSGTR_MPDEMUX_ASF_Failed2ParseHTTPResponse "Selhalo parsov�n� HTTP odpov�di.\n"
#define MSGTR_MPDEMUX_ASF_ServerReturn "Server vr�til %d:%s\n"
#define MSGTR_MPDEMUX_ASF_ASFHTTPParseWarnCuttedPragma "ASF HTTP PARSE VAROV�N�: Pragma %s zkr�cena z %d bajt� na %d\n"
#define MSGTR_MPDEMUX_ASF_SocketWriteError "Chyba z�pisu soketu: %s\n"
#define MSGTR_MPDEMUX_ASF_HeaderParseFailed "Selhalo parsov�n� hlavi�ky\n"
#define MSGTR_MPDEMUX_ASF_NoStreamFound "Nenalezen datov� proud\n"
#define MSGTR_MPDEMUX_ASF_UnknownASFStreamingType "Nezn�m� typ ASF proudu\n"
#define MSGTR_MPDEMUX_ASF_InfoStreamASFURL "STREAM_ASF, URL: %s\n"
#define MSGTR_MPDEMUX_ASF_StreamingFailed "Selhalo, kon��m.\n"

// audio_in.c

#define MSGTR_MPDEMUX_AUDIOIN_ErrReadingAudio "\nChyba p�i �ten� audia: %s\n"
#define MSGTR_MPDEMUX_AUDIOIN_XRUNSomeFramesMayBeLeftOut "Zotaveno z cross-run, n�kter� sn�mky mohly b�t vynech�ny!\n"
#define MSGTR_MPDEMUX_AUDIOIN_ErrFatalCannotRecover "Kritick� chyba, nelze zotavit!\n"
#define MSGTR_MPDEMUX_AUDIOIN_NotEnoughSamples "\nNedostatek audio vzork�!\n"

// aviheader.c

#define MSGTR_MPDEMUX_AVIHDR_EmptyList "** pr�zdn� seznam?!\n"
#define MSGTR_MPDEMUX_AVIHDR_FoundMovieAt "Nalezen film na 0x%X - 0x%X\n"
#define MSGTR_MPDEMUX_AVIHDR_FoundBitmapInfoHeader "Nalezena 'bih', %u bajt� z %d\n"
#define MSGTR_MPDEMUX_AVIHDR_RegeneratingKeyfTableForMPG4V1 "Regeneruji tabulku kl��ov�ch sn�mk� pro MS mpg4v1 video.\n"
#define MSGTR_MPDEMUX_AVIHDR_RegeneratingKeyfTableForDIVX3 "Regeneruji tabulku kl��ov�ch sn�mk� pro DIVX3 video.\n"
#define MSGTR_MPDEMUX_AVIHDR_RegeneratingKeyfTableForMPEG4 "Regeneruji tabulku kl��ov�ch sn�mk� pro MPEG4 video.\n"
#define MSGTR_MPDEMUX_AVIHDR_FoundWaveFmt "Nalezen 'wf', %d bajt� z %d\n"
#define MSGTR_MPDEMUX_AVIHDR_FoundAVIV2Header "AVI: nalezena dmlh (size=%d) (total_frames=%d)\n"
#define MSGTR_MPDEMUX_AVIHDR_ReadingIndexBlockChunksForFrames "�tu INDEX blok, %d chunk� pro %d sn�mk� (fpos=%"PRId64").\n"
#define MSGTR_MPDEMUX_AVIHDR_AdditionalRIFFHdr "Dodate�n� RIFF hlavi�ka...\n"
#define MSGTR_MPDEMUX_AVIHDR_WarnNotExtendedAVIHdr "** Varov�n�: toto nen� roz���en� AVI hlavi�ka..\n"
#define MSGTR_MPDEMUX_AVIHDR_BrokenChunk "Vadn� chunk?  chunksize=%d  (id=%.4s)\n"
#define MSGTR_MPDEMUX_AVIHDR_BuildingODMLidx "AVI: ODML: Vytv���m ODML index (%d superindexchunk�).\n"
#define MSGTR_MPDEMUX_AVIHDR_BrokenODMLfile "AVI: ODML: Detekov�n vadn� (ne�pln�?) soubor. Pou�ije se tradi�n� index.\n"
#define MSGTR_MPDEMUX_AVIHDR_CantReadIdxFile "Nelze ��st indexov� soubor %s: %s\n"
#define MSGTR_MPDEMUX_AVIHDR_NotValidMPidxFile "%s nen� plan� indexov� soubor pro MPlayer.\n"
#define MSGTR_MPDEMUX_AVIHDR_FailedMallocForIdxFile "Nemohu alokovat pam� pro data indexu od %s.\n"
#define MSGTR_MPDEMUX_AVIHDR_PrematureEOF "p�ed�asn� konec indexov�ho souboru %s\n"
#define MSGTR_MPDEMUX_AVIHDR_IdxFileLoaded "Nahr�n indexov� soubor: %s\n"
#define MSGTR_MPDEMUX_AVIHDR_GeneratingIdx "Generuji index: %3lu %s     \r"
#define MSGTR_MPDEMUX_AVIHDR_IdxGeneratedForHowManyChunks "AVI: Vygenerov�na tabulka indexu pro %d chunk�!\n"
#define MSGTR_MPDEMUX_AVIHDR_Failed2WriteIdxFile "Nelze zapsat indexov� soubor %s: %s\n"
#define MSGTR_MPDEMUX_AVIHDR_IdxFileSaved "Ulo�en indexov� soubor: %s\n"

// cache2.c

#define MSGTR_MPDEMUX_CACHE2_NonCacheableStream "\rTento proud nelze ukl�dat do vyrovn�vac� pam�ti.\n"
#define MSGTR_MPDEMUX_CACHE2_ReadFileposDiffers "!!! read_filepos se li�� !!! Ohlaste tuto chybu...\n"

// cdda.c

#define MSGTR_MPDEMUX_CDDA_CantOpenCDDADevice "Nelze otev��t CDDA za��zen�.\n"
#define MSGTR_MPDEMUX_CDDA_CantOpenDisc "Nelze otev��t disk.\n"
#define MSGTR_MPDEMUX_CDDA_AudioCDFoundWithNTracks "Nalezeno audio CD s %ld stopami\n"

// cddb.c

#define MSGTR_MPDEMUX_CDDB_FailedToReadTOC "Selhalo �ten� TOC.\n"
#define MSGTR_MPDEMUX_CDDB_FailedToOpenDevice "Selhalo otev�en� za��zen� %s.\n"
#define MSGTR_MPDEMUX_CDDB_NotAValidURL "neplatn� URL\n"
#define MSGTR_MPDEMUX_CDDB_FailedToSendHTTPRequest "Selhalo odesl�n� HTTP po�adavku.\n"
#define MSGTR_MPDEMUX_CDDB_FailedToReadHTTPResponse "Selhalo �ten� HTTP odpov�di.\n"
#define MSGTR_MPDEMUX_CDDB_HTTPErrorNOTFOUND "Nen� k dispozici.\n"
#define MSGTR_MPDEMUX_CDDB_HTTPErrorUnknown "nezn�m� error k�d\n"
#define MSGTR_MPDEMUX_CDDB_NoCacheFound "Vyrovn�vac� pam� nenalezena.\n"
#define MSGTR_MPDEMUX_CDDB_NotAllXMCDFileHasBeenRead "Nebyl p�e�ten cel� xmcd soubor.\n"
#define MSGTR_MPDEMUX_CDDB_FailedToCreateDirectory "Selhalo vytvo�en� adres��e %s.\n"
#define MSGTR_MPDEMUX_CDDB_NotAllXMCDFileHasBeenWritten "Nebyl zaps�n cel� xmcd soubor.\n"
#define MSGTR_MPDEMUX_CDDB_InvalidXMCDDatabaseReturned "Vr�cen chybn� soubor xmcd datab�ze.\n"
#define MSGTR_MPDEMUX_CDDB_UnexpectedFIXME "neo�ek�van� UROB-SI-S�M\n"
#define MSGTR_MPDEMUX_CDDB_UnhandledCode "neo�et�en� k�d\n"
#define MSGTR_MPDEMUX_CDDB_UnableToFindEOL "Nelze nal�st konec ��dku.\n"
#define MSGTR_MPDEMUX_CDDB_ParseOKFoundAlbumTitle "Parsov�n� OK, nalezeno: %s\n"
#define MSGTR_MPDEMUX_CDDB_AlbumNotFound "Album nenalezeno.\n"
#define MSGTR_MPDEMUX_CDDB_ServerReturnsCommandSyntaxErr "Server vr�til: Syntaktick� chyba p��kazu\n"
#define MSGTR_MPDEMUX_CDDB_NoSitesInfoAvailable "Nejsou informace o sitech (serverech).\n"
#define MSGTR_MPDEMUX_CDDB_FailedToGetProtocolLevel "Selhalo z�sk�n� �rovn� protokolu.\n"
#define MSGTR_MPDEMUX_CDDB_NoCDInDrive "V mechanice nen� CD.\n"

// cue_read.c

#define MSGTR_MPDEMUX_CUEREAD_UnexpectedCuefileLine "[bincue] Neo�ek�van� ��dek v cue souboru: %s\n"
#define MSGTR_MPDEMUX_CUEREAD_BinFilenameTested "[bincue] otestov�n bin soubor: %s\n"
#define MSGTR_MPDEMUX_CUEREAD_CannotFindBinFile "[bincue] Nelze nal�zt bin soubor - vzd�v�m to.\n"
#define MSGTR_MPDEMUX_CUEREAD_UsingBinFile "[bincue] Pou��v�m bin soubor %s.\n"
#define MSGTR_MPDEMUX_CUEREAD_UnknownModeForBinfile "[bincue] nezn�m� re�im pro bin soubor. To by se nem�lo st�t. Kon��m.\n"
#define MSGTR_MPDEMUX_CUEREAD_CannotOpenCueFile "[bincue] Nelze otev��t %s\n"
#define MSGTR_MPDEMUX_CUEREAD_ErrReadingFromCueFile "[bincue] Chyba �ten� z  %s\n"
#define MSGTR_MPDEMUX_CUEREAD_ErrGettingBinFileSize "[bincue] Chyba z�sk�n� velikosti bin souboru.\n"
#define MSGTR_MPDEMUX_CUEREAD_InfoTrackFormat "stopa %02d:  format=%d  %02d:%02d:%02d\n"
#define MSGTR_MPDEMUX_CUEREAD_UnexpectedBinFileEOF "[bincue] neo�ek�van� konec bin souboru\n"
#define MSGTR_MPDEMUX_CUEREAD_CannotReadNBytesOfPayload "[bincue] Nelze p�e��st %d bajt� 'payloadu'.\n"
#define MSGTR_MPDEMUX_CUEREAD_CueStreamInfo_FilenameTrackTracksavail "CUE stream_open, soubor=%s, stopa=%d, dostupn� stopy: %d -> %d\n"

// network.c

#define MSGTR_MPDEMUX_NW_UnknownAF "Nezn�m� rodina adres %d\n"
#define MSGTR_MPDEMUX_NW_ResolvingHostForAF "Resolvuji %s pro %s...\n"
#define MSGTR_MPDEMUX_NW_CantResolv "Nelze resolvovat jm�no pro %s: %s\n"
#define MSGTR_MPDEMUX_NW_ConnectingToServer "P�ipojuji se k serveru %s[%s]: %d...\n"
#define MSGTR_MPDEMUX_NW_CantConnect2Server "Selhalo p�ipojen� k serveru pomoc� %s\n"
#define MSGTR_MPDEMUX_NW_SelectFailed "Select selhal.\n"
#define MSGTR_MPDEMUX_NW_ConnTimeout "spojen� vypr�elo\n"
#define MSGTR_MPDEMUX_NW_GetSockOptFailed "getsockopt selhal: %s\n"
#define MSGTR_MPDEMUX_NW_ConnectError "chyba spojen�: %s\n"
#define MSGTR_MPDEMUX_NW_InvalidProxySettingTryingWithout "�patn� nastaven� proxy... Zkou��m bez proxy.\n"
#define MSGTR_MPDEMUX_NW_CantResolvTryingWithoutProxy "Nelze resolvovat jm�no vzd�len�ho syst�mu pro AF_INET. Zkou��m bez proxy.\n"
#define MSGTR_MPDEMUX_NW_ErrSendingHTTPRequest "Chyba p�i odes�l�n� HTTP po�adavku: Nebyl odesl�n cel� po�adavek.\n"
#define MSGTR_MPDEMUX_NW_ReadFailed "Chyba p�i �ten�.\n"
#define MSGTR_MPDEMUX_NW_Read0CouldBeEOF "http_read_response p�e�etlo 0 (to je EOF).\n"
#define MSGTR_MPDEMUX_NW_AuthFailed "Autentifikace selhala. Pou�ijte volby -user a -passwd pro zad�n� sv�ho\n"\
"u�ivatelsk�ho_jm�na/hesla pro seznam URL, nebo URL v n�sleduj�c� form�:\n"\
"http://u�ivatelsk�_jm�no:heslo@jm�no_serveru/soubor\n"
#define MSGTR_MPDEMUX_NW_AuthRequiredFor "Pro %s je vy�adov�na autentifikace\n"
#define MSGTR_MPDEMUX_NW_AuthRequired "Vy�adov�na autentifikace.\n"
#define MSGTR_MPDEMUX_NW_NoPasswdProvidedTryingBlank "Nezad�no heslo, zkou��m pr�zdn� heslo.\n"
#define MSGTR_MPDEMUX_NW_ErrServerReturned "Server vr�til %d: %s\n"
#define MSGTR_MPDEMUX_NW_CacheSizeSetTo "Vyrovn�vac� pam� nastavena na %d KBajt�\n"

// ========================== LIBMPMENU ===================================

// common

#define MSGTR_LIBMENU_NoEntryFoundInTheMenuDefinition "[MENU] V definici menu nen� ��dn� polo�ka.\n"

// libmenu/menu.c
#define MSGTR_LIBMENU_SyntaxErrorAtLine "[MENU] syntaktick� chyba na ��dku: %d\n"
#define MSGTR_LIBMENU_MenuDefinitionsNeedANameAttrib "[MENU] V definici menu je pot�eba jmenn� atribut (��dek %d)\n"
#define MSGTR_LIBMENU_BadAttrib "[MENU] �patn� atribut %s=%s v menu '%s' na ��dku %d\n"
#define MSGTR_LIBMENU_UnknownMenuType "[MENU] nezn�m� typ menu '%s' na ��dce %d\n"
#define MSGTR_LIBMENU_CantOpenConfigFile "[MENU] Nemohu otev��t konfigura�n� soubor menu: %s\n"
#define MSGTR_LIBMENU_ConfigFileIsTooBig "[MENU] Konfigura�n� soubor je p��li� velk�. (> %d KB)\n"
#define MSGTR_LIBMENU_ConfigFileIsEmpty "[MENU] Konfigura�n� soubor je pr�zdn�.\n"
#define MSGTR_LIBMENU_MenuNotFound "[MENU] Menu %s nebylo nalezeno.\n"
#define MSGTR_LIBMENU_MenuInitFailed "[MENU] Menu '%s': Selhala inicializace.\n"
#define MSGTR_LIBMENU_UnsupportedOutformat "[MENU] Nepodporovan� v�stupn� form�t!\n"

// libmenu/menu_cmdlist.c
#define MSGTR_LIBMENU_ListMenuEntryDefinitionsNeedAName "[MENU] Polo�ky typu seznam vy�aduj� n�zev (��dek %d).\n"
#define MSGTR_LIBMENU_ListMenuNeedsAnArgument "[MENU] Polo�ka typu seznam vy�aduje argument.\n"

// libmenu/menu_console.c
#define MSGTR_LIBMENU_WaitPidError "[MENU] Chyba p�i �ek�n� na PID: %s.\n"
#define MSGTR_LIBMENU_SelectError "[MENU] Chyba v�b�ru.\n"
#define MSGTR_LIBMENU_ReadErrorOnChilds "[MENU] Chyba �ten� na popisova�i souboru potomka: %s.\n"
#define MSGTR_LIBMENU_ConsoleRun "[MENU] Spu�t�n� v konsoli: %s ...\n"
#define MSGTR_LIBMENU_AChildIsAlreadyRunning "[MENU] Potomek u� b��.\n"
#define MSGTR_LIBMENU_ForkFailed "[MENU] Forkov�n� selhalo!!!\n"
#define MSGTR_LIBMENU_WriteError "[MENU] chyba p�i z�pisu.\n"

// libmenu/menu_filesel.c
#define MSGTR_LIBMENU_OpendirError "[MENU] chyba p�i otev�r�n� adres��e: %s\n"
#define MSGTR_LIBMENU_ReallocError "[MENU] chyba p�i relokaci: %s\n"
#define MSGTR_LIBMENU_MallocError "[MENU] chyba p�i alokaci pam�ti: %s\n"
#define MSGTR_LIBMENU_ReaddirError "[MENU] chyba �ten� adres��e: %s\n"
#define MSGTR_LIBMENU_CantOpenDirectory "[MENU] Nelze otev��t adres�� %s.\n"

// libmenu/menu_param.c
#define MSGTR_LIBMENU_SubmenuDefinitionNeedAMenuAttribut "[MENU] P�i definici podmenu je pot�eba uv�st atribut 'menu'.\n"
#define MSGTR_LIBMENU_PrefMenuEntryDefinitionsNeed "[MENU] Preferen�n� polo�ka menu vy�aduje korektn� atribut 'property' (��dka %d).\n"
#define MSGTR_LIBMENU_PrefMenuNeedsAnArgument "[MENU] Preferen�n� menu vy�aduje argument.\n"

// libmenu/menu_pt.c
#define MSGTR_LIBMENU_CantfindTheTargetItem "[MENU] Nemohu nal�zt c�lovou polo�ku??\n"
#define MSGTR_LIBMENU_FailedToBuildCommand "[MENU] Selhalo sestaven� p��kazu: %s.\n"

// libmenu/menu_txt.c
#define MSGTR_LIBMENU_MenuTxtNeedATxtFileName "[MENU] Textov� menu vy�aduje n�zev souboru txt (parametrick� soubor).\n"
#define MSGTR_LIBMENU_MenuTxtCantOpen "[MENU] Nelze otev��t: %s.\n"
#define MSGTR_LIBMENU_WarningTooLongLineSplitting "[MENU] Pozor, ��dka je p��li� dlouh�. Rozd�luju ji.\n"
#define MSGTR_LIBMENU_ParsedLines "[MENU] Zpracov�no %d ��dk�.\n"

// libmenu/vf_menu.c
#define MSGTR_LIBMENU_UnknownMenuCommand "[MENU] Nezn�m� p��kaz: '%s'.\n"
#define MSGTR_LIBMENU_FailedToOpenMenu "[MENU] Nemohu otev��t menu: '%s'.\n"

// ========================== LIBMPCODECS ===================================

// libmpcodecs/ad_libdv.c
#define MSGTR_MPCODECS_AudioFramesizeDiffers "[AD_LIBDV] Varov�n�! Velikost r�mce zvuku se li��! p�e�teno=%d  hlavi�ka=%d.\n"

// libmpcodecs/vd_dmo.c vd_dshow.c vd_vfw.c
#define MSGTR_MPCODECS_CouldntAllocateImageForCinepakCodec "[VD_DMO] Nemohu alokovat obraz pro kodek cinepak.\n"

// libmpcodecs/vd_ffmpeg.c
#define MSGTR_MPCODECS_XVMCAcceleratedCodec "[VD_FFMPEG] XVMC akcelerovan� kodek.\n"
#define MSGTR_MPCODECS_ArithmeticMeanOfQP "[VD_FFMPEG] Aritmetick� pr�m�r QP: %2.4f, harmonick� pr�m�r QP: %2.4f\n"
#define MSGTR_MPCODECS_DRIFailure "[VD_FFMPEG] DRI selhalo.\n"
#define MSGTR_MPCODECS_CouldntAllocateImageForCodec "[VD_FFMPEG] Nemohu alokovat obraz pro kodek.\n"
#define MSGTR_MPCODECS_XVMCAcceleratedMPEG2 "[VD_FFMPEG] XVMC-akcelerovan� MPEG-2.\n"
#define MSGTR_MPCODECS_TryingPixfmt "[VD_FFMPEG] Zkou��m pixfmt=%d.\n"
#define MSGTR_MPCODECS_McGetBufferShouldWorkOnlyWithXVMC "[VD_FFMPEG] mc_get_buffer by m�lo fungovat jen s XVMC akcelerac�!"
#define MSGTR_MPCODECS_UnexpectedInitVoError "[VD_FFMPEG] Neo�ek�van� chyba init_vo.\n"
#define MSGTR_MPCODECS_UnrecoverableErrorRenderBuffersNotTaken "[VD_FFMPEG] Neodstraniteln� chyba, vykreslovac� buffery nepou�ity.\n"
#define MSGTR_MPCODECS_OnlyBuffersAllocatedByVoXvmcAllowed "[VD_FFMPEG] Povoleny jsou jen buffery alokovan� pomoc� vo_xvmc.\n"

// libmpcodecs/ve_lavc.c
#define MSGTR_MPCODECS_HighQualityEncodingSelected "[VE_LAVC] Vybr�no vysoce kvalitn� k�dov�n� (nebude prob�hat v re�ln�m �ase)!\n"
#define MSGTR_MPCODECS_UsingConstantQscale "[VE_LAVC] Pou��v�m konstantn� qscale = %f (VBR).\n"

// libmpcodecs/ve_raw.c
#define MSGTR_MPCODECS_OutputWithFourccNotSupported "[VE_RAW] Surov� v�stup s fourcc [%x] nen� podporov�n!\n"
#define MSGTR_MPCODECS_NoVfwCodecSpecified "[VE_RAW] Po�adovan� VfW kodek nebyl specifikov�n!\n"

// libmpcodecs/vf_crop.c
#define MSGTR_MPCODECS_CropBadPositionWidthHeight "[CROP] �patn� pozice/���ka/v��ka - o�ezov� oblast zasahuje mimo origin�l!\n"

// libmpcodecs/vf_cropdetect.c
#define MSGTR_MPCODECS_CropArea "[CROP] O�ezov� oblast: X: %d..%d  Y: %d..%d  (-vf crop=%d:%d:%d:%d).\n"

// libmpcodecs/vf_format.c, vf_palette.c, vf_noformat.c
#define MSGTR_MPCODECS_UnknownFormatName "[VF_FORMAT] Nezn�m� n�zev form�tu: '%s'.\n"

// libmpcodecs/vf_framestep.c vf_noformat.c vf_palette.c vf_tile.c
#define MSGTR_MPCODECS_ErrorParsingArgument "[VF_FRAMESTEP] Chyba p�i zpracov�n� argumentu.\n"

// libmpcodecs/ve_vfw.c
#define MSGTR_MPCODECS_CompressorType "Typ komprese: %.4lx\n"
#define MSGTR_MPCODECS_CompressorSubtype "Podtyp komprese: %.4lx\n"
#define MSGTR_MPCODECS_CompressorFlags "P��znaky kompresoru: %lu, verze %lu, verze ICM: %lu\n"
#define MSGTR_MPCODECS_Flags "P��znaky:"
#define MSGTR_MPCODECS_Quality " kvalita"

// libmpcodecs/vf_expand.c
#define MSGTR_MPCODECS_FullDRNotPossible "Pln� DR nen� mo�n�, zkou��m m�sto n�j SLICES!\n"
#define MSGTR_MPCODECS_WarnNextFilterDoesntSupportSlices  "Varov�n�! Dal�� filtr nepodporuje SLICES, o�ek�vejte sig11...\n"
#define MSGTR_MPCODECS_FunWhydowegetNULL "Pro� jsme dostali NULL??\n"

// libmpcodecs/vf_fame.c
#define MSGTR_MPCODECS_FatalCantOpenlibFAME "Fat�ln� chyba: Nelze otev��t libFAME!\n"

// libmpcodecs/vf_test.c, vf_yuy2.c, vf_yvu9.c
#define MSGTR_MPCODECS_WarnNextFilterDoesntSupport "%s nen� dal��m filtrem/vo podporov�n :(\n"



#define MSGTR_MPDEMUX_AUDIO_UnknownFormat "Audio demuxer: nezn�m� form�t %d.\n"
#define MSGTR_MPDEMUX_DEMUXERS_FillBufferError "fill_buffer chyba: �patn� demuxer: ani vd, ad nebo sd.\n"
#define MSGTR_MPDEMUX_NUV_NoVideoBlocksInFile "V souboru nejsou ��dn� bloky videa.\n"
#define MSGTR_MPDEMUX_XMMS_FoundPlugin "Nalezen plugin: %s (%s).\n"
#define MSGTR_MPDEMUX_XMMS_ClosingPlugin "Uzav�r�m plugin: %s.\n"

// mga_common.c

#define MSGTR_LIBVO_MGA_ErrorInConfigIoctl "[MGA] Chyba v mga_vid_config ioctl (�patn� verze mga_vid.o?)."
#define MSGTR_LIBVO_MGA_CouldNotGetLumaValuesFromTheKernelModule "[MGA] Nemohu z�skat hodnoty luma z jadern�ho modulu!\n"
#define MSGTR_LIBVO_MGA_CouldNotSetLumaValuesFromTheKernelModule "[MGA] Nemohu nastavit hodnoty luma v jadern�m modulu!\n"
#define MSGTR_LIBVO_MGA_ScreenWidthHeightUnknown "[MGA] Pom�r stran obrazovky nen� zn�m!\n"
#define MSGTR_LIBVO_MGA_InvalidOutputFormat "[MGA] Neplatn� form�t v�stupu %0X\n"
#define MSGTR_LIBVO_MGA_IncompatibleDriverVersion "[MGA] Verze va�eho mga_vid ovlada�e nen� kompatibiln� s touto verz� MPlayeru!\n"
#define MSGTR_LIBVO_MGA_UsingBuffers "[MGA] Pou��v�m %d bufer�.\n"
#define MSGTR_LIBVO_MGA_CouldntOpen "[MGA] Nemohu otev��t: %s\n"
#define MGSTR_LIBVO_MGA_ResolutionTooHigh "[MGA] Vstupn� rozli�en� minim�ln� v jednom rozm�ru v�t�� ne� 1023x1023. P�e�k�lujte pros�m softwarov�, nebo pou�ijte -lavdopts lowres=1\n"
 
// libvo/vesa_lvo.c
 
#define MSGTR_LIBVO_VESA_ThisBranchIsNoLongerSupported "[VESA_LVO] Tato v�tev nen� nad�le podporov�na.\n[VESA_LVO] Pou�ijte pros�m -vo vesa:vidix.\n"
#define MSGTR_LIBVO_VESA_CouldntOpen "[VESA_LVO] Nemohu otev��t: '%s'\n"
#define MSGTR_LIBVO_VESA_InvalidOutputFormat "[VESA_LVI] Neplatn� v�stupn� form�t: %s(%0X)\n"
#define MSGTR_LIBVO_VESA_IncompatibleDriverVersion "[VESA_LVO] Verze va�eho fb_vid ovlada�e nen� ko�mpatibiln� s touto verz� MPlayeru!\n"

// libvo/vo_3dfx.c

#define MSGTR_LIBVO_3DFX_Only16BppSupported "[VO_3DFX] Podporov�no je jen 16bpp!"
#define MSGTR_LIBVO_3DFX_VisualIdIs "[VO_3DFX] Visual ID je  %lx.\n"
#define MSGTR_LIBVO_3DFX_UnableToOpenDevice "[VO_3DFX] Nemohu otev��t /dev/3dfx.\n"
#define MSGTR_LIBVO_3DFX_Error "[VO_3DFX] Chyba: %d.\n"
#define MSGTR_LIBVO_3DFX_CouldntMapMemoryArea "[VO_3DFX] Nemohu namapovat oblasti pam�ti 3dfx: %p,%p,%d.\n"
#define MSGTR_LIBVO_3DFX_DisplayInitialized "[VO_3DFX] Inicialozov�no: %p.\n"
#define MSGTR_LIBVO_3DFX_UnknownSubdevice "[VO_3DFX] Nezn�m� podza��zen�: %s.\n"
#define MSGTR_LIBVO_DXR3_UnableToLoadNewSPUPalette "[VO_DXR3] Nemohu nahr�t novou SPU paletu!\n"
#define MSGTR_LIBVO_DXR3_UnableToSetPlaymode "[VO_DXR3] Nemohu nastavit re�im p�ehr�v�n�!\n"
#define MSGTR_LIBVO_DXR3_UnableToSetSubpictureMode "[VO_DXR3] Nemohu nastavit re�im titulk�!\n"
#define MSGTR_LIBVO_DXR3_UnableToGetTVNorm "[VO_DXR3] Nemohu zjistit televizn� normu!\n"
#define MSGTR_LIBVO_DXR3_AutoSelectedTVNormByFrameRate "[VO_DXR3] Automaticky nastaven� televizn� norma podle sn�mkov� rychlosti: "
#define MSGTR_LIBVO_DXR3_UnableToSetTVNorm "[VO_DXR3] Nemohu nastavit televizn� normu!\n"
#define MSGTR_LIBVO_DXR3_SettingUpForNTSC "[VO_DXR3] Nastavuji pro NTSC.\n"
#define MSGTR_LIBVO_DXR3_SettingUpForPALSECAM "[VO_DXR3] Nastavuji pro PAL/SECAM.\n"
#define MSGTR_LIBVO_DXR3_SettingAspectRatioTo43 "[VO_DXR3] Nastavuji pom�r stran 4:3.\n"
#define MSGTR_LIBVO_DXR3_SettingAspectRatioTo169 "[VO_DXR3] Nastavuji pom�r stran 16:9.\n"
#define MSGTR_LIBVO_DXR3_OutOfMemory "[VO_DXR3] do�la pam�\n"
#define MSGTR_LIBVO_DXR3_UnableToAllocateKeycolor "[VO_DXR3] Nemohu alokovat kl��ovac� barvu!\n"
#define MSGTR_LIBVO_DXR3_UnableToAllocateExactKeycolor "[VO_DXR3] Nemohu alokovat kl��ovac� barvu p�esn�, pou��v�m nejbli��� (0x%lx).\n"
#define MSGTR_LIBVO_DXR3_Uninitializing "[VO_DXR3] Deinicializuji.\n"
#define MSGTR_LIBVO_DXR3_FailedRestoringTVNorm "[VO_DXR3] Nepovedlo se nastavit p�vodn� televizn� normu!\n"
#define MSGTR_LIBVO_DXR3_EnablingPrebuffering "[VO_DXR3] Zap�n�m prebuffering.\n"
#define MSGTR_LIBVO_DXR3_UsingNewSyncEngine "[VO_DXR3] Pou��v�m nov� synchroniza�n� k�d.\n"
#define MSGTR_LIBVO_DXR3_UsingOverlay "[VO_DXR3] Pou��v�m overlay.\n"
#define MSGTR_LIBVO_DXR3_ErrorYouNeedToCompileMplayerWithX11 "[VO_DXR3] Chyba: Overlay vy�aduje kompilaci s nainstalovan�mi x11 knihovnami a hlavi�kami.\n"
#define MSGTR_LIBVO_DXR3_WillSetTVNormTo "[VO_DXR3] Nastav�m televizn� normu na: "
#define MSGTR_LIBVO_DXR3_AutoAdjustToMovieFrameRatePALPAL60 "p�ep�n�m na rychlost sn�mk� podle filmu (PAL/PAL-60)"
#define MSGTR_LIBVO_DXR3_AutoAdjustToMovieFrameRatePALNTSC "p�ep�n�m na rychlost sn�mk� podle filmu (PAL/NTSC)"
#define MSGTR_LIBVO_DXR3_UseCurrentNorm "Pou��t sou�asnou normu"
#define MSGTR_LIBVO_DXR3_UseUnknownNormSuppliedCurrentNorm "P�ed�na nezn�m� norma. Pou�iji sou�asnou."
#define MSGTR_LIBVO_DXR3_ErrorOpeningForWritingTrying "[VO_DXR3] Chyba p�i otev�r�n� %s pro z�pis, zkus�m /dev/em8300.\n"
#define MSGTR_LIBVO_DXR3_ErrorOpeningForWritingTryingMV "[VO_DXR3] Chyba p�i otev�r�n� %s pro z�pis, zkus�m /dev/em8300_mv.\n"
#define MSGTR_LIBVO_DXR3_ErrorOpeningForWritingAsWell "[VO_DXR3] Chyba p�i otev�r�n� /dev/em8300 pro z�pis!\nVzd�v�m to.\n"
#define MSGTR_LIBVO_DXR3_ErrorOpeningForWritingAsWellMV "[VO_DXR3] Chyba p�i otev�r�n� /dev/em8300_mv pro z�pis!\nVzd�v�m to.\n"
#define MSGTR_LIBVO_DXR3_Opened "[VO_DXR3] Otev�eno: %s.\n"
#define MSGTR_LIBVO_DXR3_ErrorOpeningForWritingTryingSP "[VO_DXR3] Chyba p�i otev�r�n� %s pro z�pis, zkou��m /dev/em8300_sp.\n"
#define MSGTR_LIBVO_DXR3_ErrorOpeningForWritingAsWellSP "[VO_DXR3] Chyba p�i otev�r�n� /dev/em8300_sp pro z�pis!\nVzd�v�m to.\n"
#define MSGTR_LIBVO_DXR3_UnableToOpenDisplayDuringHackSetup "[VO_DXR3] B�hem hacku na nastaven� overlaye se nepoda�ilo otev��t display!\n"
#define MSGTR_LIBVO_DXR3_UnableToInitX11 "[VO_DXR3] Nemohu inicializovat X11!\n"
#define MSGTR_LIBVO_DXR3_FailedSettingOverlayAttribute "[VO_DXR3] Nepoda�ilo se nastavit atribut overlaye.\n"
#define MSGTR_LIBVO_DXR3_FailedSettingOverlayScreen "[VO_DXR3] Nepoda�ilo se nastavit obrazovku pro overlay!\nKon��m.\n"
#define MSGTR_LIBVO_DXR3_FailedEnablingOverlay "[VO_DXR3] Nepoda�ilo se zapnout overlay!\nKon��m.\n"
#define MSGTR_LIBVO_DXR3_FailedSettingOverlayBcs "[VO_DXR3] Nemohu nastavit bcs overlaye!\n"
#define MSGTR_LIBVO_DXR3_FailedGettingOverlayYOffsetValues "[VO_DXR3] Nemohu z�skat posunut� Y overlaye!\nKon��m.\n"
#define MSGTR_LIBVO_DXR3_FailedGettingOverlayXOffsetValues "[VO_DXR3] Nemohu z�skat posunut� X overlaye!\nKon��m.\n"
#define MSGTR_LIBVO_DXR3_FailedGettingOverlayXScaleCorrection "[VO_DXR3] Nemohu z�skat korekci zv�t�en� X!\nKon��m.\n"
#define MSGTR_LIBVO_DXR3_YOffset "[VO_DXR3] Posunut� Y: %d.\n"
#define MSGTR_LIBVO_DXR3_XOffset "[VO_DXR3] Posunut� X: %d.\n"
#define MSGTR_LIBVO_DXR3_XCorrection "[VO_DXR3] Korekce X: %d.\n"
#define MSGTR_LIBVO_DXR3_FailedSetSignalMix "[VO_DXR3] Nepoda�ilo se nastavit sign�l mix!\n"

// libvo/vo_mga.c

#define MSGTR_LIBVO_MGA_AspectResized "[VO_MGA] aspect(): velikost zm�n�na na %dx%d.\n"
#define MSGTR_LIBVO_MGA_Uninit "[VO] deinicializace!\n"

// libvo/vo_null.c

#define MSGTR_LIBVO_NULL_UnknownSubdevice "[VO_NULL] Nezn�m� podza��zen�: %s.\n"

// libvo/vo_png.c

#define MSGTR_LIBVO_PNG_Warning1 "[VO_PNG] Upozorn�n�: �rove� komprimace nastavena na 0, komprimace vypnuta!\n"
#define MSGTR_LIBVO_PNG_Warning2 "[VO_PNG] Info: Pou�ijte -vo png:z=<n> k nastaven� �rovn� komprese v rozsahu 0 a� 9.\n"
#define MSGTR_LIBVO_PNG_Warning3 "[VO_PNG] Info: (0 = ��dn� komprese, 1 = nejrychlej��, nejni��� - 9 nejvy���, ale nejpomalej�� komprese)\n"
#define MSGTR_LIBVO_PNG_ErrorOpeningForWriting "\n[VO_PNG] Nemohu otev��t '%s' pro z�pis!\n"
#define MSGTR_LIBVO_PNG_ErrorInCreatePng "[VO_PNG] Chyba p�i create_png.\n"
#define MSGTR_LIBVO_SDL_CouldntGetAnyAcceptableSDLModeForOutput "[VO_SDL] Nemohu z�skat ��dn� akceptovateln� re�im SDL pro v�stup.\n"
#define MSGTR_LIBVO_SDL_SetVideoModeFailed "[VO_SDL] set_video_mode: SDL_SetVideoMode selhalo: %s.\n"
#define MSGTR_LIBVO_SDL_SetVideoModeFailedFull "[VO_SDL] Set_fullmode: SDL_SetVideoMode selhalo: %s.\n"
#define MSGTR_LIBVO_SDL_MappingI420ToIYUV "[VO_SDL] Mapuji I420 na IYUV.\n"
#define MSGTR_LIBVO_SDL_UnsupportedImageFormat "[VO_SDL] Nepodporovan� obrazov� form�t (0x%X).\n"
#define MSGTR_LIBVO_SDL_InfoPleaseUseVmOrZoom "[VO_SDL] Info: Pou�ijte -vm nebo -zoom k p�epnut� do nejvhodn�j��ho rozli�en�.\n"
#define MSGTR_LIBVO_SDL_FailedToSetVideoMode "[VO_SDL] Nepoda�ilo se nastavit graick� re�im: %s.\n"
#define MSGTR_LIBVO_SDL_CouldntCreateAYUVOverlay "[VO_SDL] Nemohu vytvo�it YUV overlay: %s.\n"
#define MSGTR_LIBVO_SDL_CouldntCreateARGBSurface "[VO_SDL] Nemohu vytvo�it RGB povrch: %s.\n"
#define MSGTR_LIBVO_SDL_UsingDepthColorspaceConversion "[VO_SDL] Pou��v�m konverzi hloubky/barevn�ho prostoru, co� zpomaluje (%ibpp -> %ibpp).\n"
#define MSGTR_LIBVO_SDL_UnsupportedImageFormatInDrawslice "[VO_SDL] Ve draw_slice se vyskytl nepodporovan� obrazov� form�t, kontaktujte v�voj��e MPlayeru!\n"
#define MSGTR_LIBVO_SDL_BlitFailed "[VO_SDL] Blit selhal: %s.\n"
#define MSGTR_LIBVO_SDL_InitializationFailed "[VO_SDL] Inicializace SDL selhala: %s.\n"
#define MSGTR_LIBVO_SDL_UsingDriver "[VO_SDL] Pou��v�m ovlada�: %s.\n"

// libvo/vobsub_vidix.c

#define MSGTR_LIBVO_SUB_VIDIX_CantStartPlayback "[VO_SUB_VIDIX] Nemohu spustit p�ehr�v�n�: %s\n"
#define MSGTR_LIBVO_SUB_VIDIX_CantStopPlayback "[VO_SUB_VIDIX] Nemohu zastavit p�ehr�v�n�: %s\n"
#define MSGTR_LIBVO_SUB_VIDIX_InterleavedUvForYuv410pNotSupported "[VO_SUB_VIDIX] Prokl�dan� UV pro YUV410P nen� podporov�no.\n"
#define MSGTR_LIBVO_SUB_VIDIX_DummyVidixdrawsliceWasCalled "[VO_SUB_VIDIX] Bylo zavol�no pr�zdn� vidix_draw_slice().\n"
#define MSGTR_LIBVO_SUB_VIDIX_DummyVidixdrawframeWasCalled "[VO_SUB_VIDIX] Bylo zavol�no pr�zdn� vidix_draw_frame().\n"
#define MSGTR_LIBVO_SUB_VIDIX_UnsupportedFourccForThisVidixDriver "[VO_SUB_VIDIX] Nepodporovan� FourCC pro tento VIDIX ovlada�: %x (%s).\n"
#define MSGTR_LIBVO_SUB_VIDIX_VideoServerHasUnsupportedResolution "[VO_SUB_VIDIX] Video server m� nepodporovan� rozli�en� (%dx%d), podporov�no je: %dx%d-%dx%d.\n"
#define MSGTR_LIBVO_SUB_VIDIX_VideoServerHasUnsupportedColorDepth "[VO_SUB_VIDIX] Video server m� vidixem nepodporovanou barevnou hloubku (%d).\n"
#define MSGTR_LIBVO_SUB_VIDIX_DriverCantUpscaleImage "[VO_SUB_VIDIX] Ovlada� VIDIX nem��e zv�t�it obraz (%d%d -> %d%d).\n"
#define MSGTR_LIBVO_SUB_VIDIX_DriverCantDownscaleImage "[VO_SUB_VIDIX] Ovlada� VIDIX nem��e zmen�it obraz (%d%d -> %d%d).\n"
#define MSGTR_LIBVO_SUB_VIDIX_CantConfigurePlayback "[VO_SUB_VIDIX] Nemohu nakonfigurovat p�ehr�v�n�: %s.\n"
#define MSGTR_LIBVO_SUB_VIDIX_YouHaveWrongVersionOfVidixLibrary "[VO_SUB_VIDIX] M�te �patnou verzi knihovny VIDIX.\n"
#define MSGTR_LIBVO_SUB_VIDIX_CouldntFindWorkingVidixDriver "[VO_SUB_VIDIX] Nemohu nal�zt funk�n� ovlada� VIDIX.\n"
#define MSGTR_LIBVO_SUB_VIDIX_CouldntGetCapability "[VO_SUB_VIDIX] Nemohu zjistit schopnosti: %s.\n"
#define MSGTR_LIBVO_SUB_VIDIX_Description "[VO_SUB_VIDIX] Popis: %s.\n"
#define MSGTR_LIBVO_SUB_VIDIX_Author "[VO_SUB_VIDIX] Autor: %s.\n"
#define MSGTR_LIBVO_SVGA_ForcedVidmodeNotAvailable "[VO_SVGA] Vynucen� vid_mode %d (%s) nen� k dispozici.\n"
#define MSGTR_LIBVO_SVGA_ForcedVidmodeTooSmall "[VO_SVGA] Vynucen� vid_mode %d (%s) je p��li� mal�.\n"
#define MSGTR_LIBVO_SVGA_Vidmode "[VO_SVGA] Vid_mode: %d, %dx%d %dbpp.\n"
#define MSGTR_LIBVO_SVGA_VgasetmodeFailed "[VO_SVGA] Vga_setmode(%d) selhal.\n"
#define MSGTR_LIBVO_SVGA_VideoModeIsLinearAndMemcpyCouldBeUsed "[VO_SVGA] Grafick� re�im je line�rn� a m��eme pou��t k p�enosu obrazu memcpy.\n"
#define MSGTR_LIBVO_SVGA_VideoModeHasHardwareAcceleration "[VO_SVGA] Grafick� re�im m� hardwarovou akceleraci a m��eme pou��t put_image.\n"
#define MSGTR_LIBVO_SVGA_IfItWorksForYouIWouldLikeToKnow "[VO_SVGA] Pokud v�m to funguje, dejte mi v�d�t. \n[VO_SVGA] (po�lete z�znam z `mplayer test.avi -v -v -v -v &> svga.log`). D�ky.\n"
#define MSGTR_LIBVO_SVGA_VideoModeHas "[VO_SVGA] Grafick� re�im m� %d str�nek.\n"
#define MSGTR_LIBVO_SVGA_CenteringImageStartAt "[VO_SVGA] Vyst�e�uji obraz. Za��n�m na (%d,%d)\n"
#define MSGTR_LIBVO_SVGA_UsingVidix "[VO_SVGA] Pou��v�m VIDIX. w=%i h=%i  mw=%i mh=%i\n"

// libvo/vo_syncfb.c

#define MSGTR_LIBVO_SYNCFB_CouldntOpen "[VO_SYNCFB] Nemohu otev��t /dev/syncfb nebo /dev/mga_vid.\n"
#define MSGTR_LIBVO_SYNCFB_UsingPaletteYuv420p3 "[VO_SYNCFB] Pou��v�m paletu YUV420P3.\n"
#define MSGTR_LIBVO_SYNCFB_UsingPaletteYuv420p2 "[VO_SYNCFB] Pou��v�m paletu YUV420P2.\n"
#define MSGTR_LIBVO_SYNCFB_UsingPaletteYuv420 "[VO_SYNCFB] Pou��v�m paletu YUV420.\n"
#define MSGTR_LIBVO_SYNCFB_NoSupportedPaletteFound "[VO_SYNCFB] Nenalezl jsem ��dnou podporovanou paletu.\n"
#define MSGTR_LIBVO_SYNCFB_BesSourcerSize "[VO_SYNCFB] BES sourcer velikost: %d x %d.\n"
#define MSGTR_LIBVO_SYNCFB_FramebufferMemory "[VO_SYNCFB] pam� framebufferu: %ld v %ld bufferech.\n"
#define MSGTR_LIBVO_SYNCFB_RequestingFirstBuffer "[VO_SYNCFB] Po�aduji prvn� buffer #%d.\n"
#define MSGTR_LIBVO_SYNCFB_GotFirstBuffer "[VO_SYNCFB] Z�skal jsem prvn� buffer #%d.\n"
#define MSGTR_LIBVO_SYNCFB_UnknownSubdevice "[VO_SYNCFB] nezn�m� podza��zen�: %s.\n"

// libvo/vo_tdfxfb.c

#define MSGTR_LIBVO_TDFXFB_CantOpen "[VO_TDFXFB] Nemohu otev��t %s: %s.\n"
#define MSGTR_LIBVO_TDFXFB_ProblemWithFbitgetFscreenInfo "[VO_TDFXFB] Probl�m s ioctl FBITGET_FSCREENINFO: %s.\n"
#define MSGTR_LIBVO_TDFXFB_ProblemWithFbitgetVscreenInfo "[VO_TDFXFB] Probl�m s ioctl FBITGET_VSCREENINFO: %s.\n"
#define MSGTR_LIBVO_TDFXFB_ThisDriverOnlySupports "[VO_TDFXFB] Ovlada� podporuje jen 3Dfx Banshee, Voodoo3 a Voodoo 5.\n"
#define MSGTR_LIBVO_TDFXFB_OutputIsNotSupported "[VO_TDFXFB] %d bpp v�stup nen� podporov�n.\n"
#define MSGTR_LIBVO_TDFXFB_CouldntMapMemoryAreas "[VO_TDFXFB] Nemohu namapovat pam�ov� bloky: %s.\n"
#define MSGTR_LIBVO_TDFXFB_BppOutputIsNotSupported "[VO_TDFXFB] %d bpp v�stup nen� podporov�n. (To by se nem�lo nikdy st�t.)\n"
#define MSGTR_LIBVO_TDFXFB_SomethingIsWrongWithControl "[VO_TDFXFB] Echt! N�co nen� v po��dku s control().\n"
#define MSGTR_LIBVO_TDFXFB_NotEnoughVideoMemoryToPlay "[VO_TDFXFB] Pro p�ehr�v�n� filmu nen� dostatek video pam�ti. Zkuste ni��� rozli�en�.\n"
#define MSGTR_LIBVO_TDFXFB_ScreenIs "[VO_TDFXFB] Obrazovka je %dx%d p�i %d bpp, vstup je %dx%d p�i %d bpp, norma je %dx%d.\n"
#define MSGTR_LIBVO_TDFXVID_Move "[VO_TDXVID] P�esun %d(%d) x %d => %d.\n"
#define MSGTR_LIBVO_TDFXVID_AGPMoveFailedToClearTheScreen "[VO_TDFXVID] AGP p�esunu se nepoda�ilo vy�istit obrazovku.\n"
#define MSGTR_LIBVO_TDFXVID_BlitFailed "[VO_TDFXVID] Blit selhal.\n"
#define MSGTR_LIBVO_TDFXVID_NonNativeOverlayFormatNeedConversion "[VO_TDFXVID] Ne-nativn� form�t overlaye pot�ebuje konverzi.\n"
#define MSGTR_LIBVO_TDFXVID_UnsupportedInputFormat "[VO_TDFXVID] Nepodporovan� vstupn� form�t 0x%x.\n"
#define MSGTR_LIBVO_TDFXVID_OverlaySetupFailed "[VO_TDFXVID] Npoda�ilo se nastavit overlay.\n"
#define MSGTR_LIBVO_TDFXVID_OverlayOnFailed "[VO_TDFXVID] Zapnut� overlaye selhalo.\n"
#define MSGTR_LIBVO_TDFXVID_OverlayReady "[VO_TDFXVID] Overlay p�ipraven: %d(%d) x %d @ %d => %d(%d) x %d @ %d.\n"
#define MSGTR_LIBVO_TDFXVID_TextureBlitReady "[VO_TDFXVID] P�ipraven blit textury: %d(%d) x %d @ %d => %d(%d) x %d @ %d.\n"
#define MSGTR_LIBVO_TDFXVID_OverlayOffFailed "[VO_TDFXVID] Vypnut� overlaye selhalo.\n"
#define MSGTR_LIBVO_TDFXVID_CantOpen "[VO_TDFXVID] Nemohu otev��t %s: %s.\n"
#define MSGTR_LIBVO_TDFXVID_CantGetCurrentCfg "[VO_TDFXVID] Nemohu z�skat sou�asnou konfiguraci: %s.\n"
#define MSGTR_LIBVO_TDFXVID_MemmapFailed "[VO_TDFXVID] Memmap selhako!!!\n"
#define MSGTR_LIBVO_TDFXVID_GetImageTodo "Get image bude dod�l�n.\n"
#define MSGTR_LIBVO_TDFXVID_AgpMoveFailed "[VO_TDFXVID] AGP p�esun selhal.\n"
#define MSGTR_LIBVO_TDFXVID_SetYuvFailed "[VO_TDFXVID] Nastaven� YUV selhalo.\n"
#define MSGTR_LIBVO_TDFXVID_AgpMoveFailedOnYPlane "[VO_TDFXVID] AGP p�esun selhal na slo�ce Y.\n"
#define MSGTR_LIBVO_TDFXVID_AgpMoveFailedOnUPlane "[VO_TDFXVID] AGP p�esun selhal na slo�ce U.\n"
#define MSGTR_LIBVO_TDFXVID_AgpMoveFailedOnVPlane "[VO_TDFXVID] AGP p�esun selhal na slo�ce V.\n"
#define MSGTR_LIBVO_TDFXVID_UnknownFormat "[VO_TDFXVID] Nezn�m� form�t: 0x%x.\n"

// libvo/vo_tga.c

#define MSGTR_LIBVO_TGA_UnknownSubdevice "[VO_TGA] Nezn�m� podza��zen�: %s.\n"

// libvo/vo_vesa.c

#define MSGTR_LIBVO_VESA_FatalErrorOccurred "[VO_VESA] Nastala z�va�n� chyba! Nemohu pokra�ovat.\n"
#define MSGTR_LIBVO_VESA_UnkownSubdevice "[VO_VESA] Nezn�m� podza��zen�: '%s'.\n"
#define MSGTR_LIBVO_VESA_YouHaveTooLittleVideoMemory "[VO_VESA] Pro tento re�im m�te m�lo videopam�ti:\n[VO_VESA] Po�adov�no: %08lX dostupn�: %08lX.\n"
#define MSGTR_LIBVO_VESA_YouHaveToSpecifyTheCapabilitiesOfTheMonitor "[VO_VESA] M�l(a) byste specifikovat mo�nosti monitoru. Nebudu m�nit obnovovac� frekvenci.\n"
#define MSGTR_LIBVO_VESA_UnableToFitTheMode "[VO_VESA] Po�adavky re�imu p�esahuj� schopnosti monitoru. Nebudu m�nit obnovovac� frekvenci.\n"
#define MSGTR_LIBVO_VESA_DetectedInternalFatalError "[VO_VESA] Byla zji�t�na z�va�n� chyba: init byl zavol�n p�ed preinit.\n"
#define MSGTR_LIBVO_VESA_SwitchFlipIsNotSupported "[VO_VESA] Volba -flip nen� podporov�na.\n"
#define MSGTR_LIBVO_VESA_PossibleReasonNoVbe2BiosFound "[VO_VESA] Mo�n� p���iny: Nenalezen VBE2 BIOS.\n"
#define MSGTR_LIBVO_VESA_FoundVesaVbeBiosVersion "[VO_VESA] Nalezen VESA VBE BIOS verze %x.%x revize: %x.\n"
#define MSGTR_LIBVO_VESA_VideoMemory "[VO_VESA] Video pam�: %u Kb.\n"
#define MSGTR_LIBVO_VESA_Capabilites "[VO_VESA] Schpnosti VESA: %s %s %s %s %s.\n"
#define MSGTR_LIBVO_VESA_BelowWillBePrintedOemInfo "[VO_VESA] !!! N��e najdete OEM informace !!!\n"
#define MSGTR_LIBVO_VESA_YouShouldSee5OemRelatedLines "[VO_VESA] N��e by m�lo b�t vyps�no p�t ��dk� OEM, jinak m�te rozbit� vm86.\n"
#define MSGTR_LIBVO_VESA_OemInfo "[VO_VESA] OEM informace: %s.\n"
#define MSGTR_LIBVO_VESA_OemRevision "[VO_VESA] OEM revize: %x.\n"
#define MSGTR_LIBVO_VESA_OemVendor "[VO_VESA] OEM v�robce: %s.\n"
#define MSGTR_LIBVO_VESA_OemProductName "[VO_VESA] OEM n�zev produktu: %s.\n"
#define MSGTR_LIBVO_VESA_OemProductRev "[VO_VESA] OEM revize produktu: %s.\n"
#define MSGTR_LIBVO_VESA_Hint "[VO_VESA] Tip: Aby fungoval TV-Out, m�l(a) byste zasunout televizn� konektor\n"\
"[VO_VESA] p�ed nabootov�n�m PC, proto�e VESA BIOS se inicializuje jen b�hem POST.\n"
#define MSGTR_LIBVO_VESA_UsingVesaMode "[VO_VESA] Pou��v�m VESA re�im (%u) = %x [%ux%u@%u]\n"
#define MSGTR_LIBVO_VESA_CantInitializeSwscaler "[VO_VESA] Nemohu inicializovat softwarov� �k�lov�n�.\n"
#define MSGTR_LIBVO_VESA_CantUseDga "[VO_VESA] Nemohu pou��t DGA. Vynucuji re�im p�ep�n�n� bank. :(\n"
#define MSGTR_LIBVO_VESA_UsingDga "[VO_VESA] Pou��v�m DGA (fyzick� zdroje: %08lXh, %08lXh)"
#define MSGTR_LIBVO_VESA_CantUseDoubleBuffering "[VO_VESA] Nemohu pou��t double buffering: nen� dostatek videopam�ti.\n"
#define MSGTR_LIBVO_VESA_CantFindNeitherDga "[VO_VESA] Nemohu naj�t ani DGA, ani relokovateln� r�mec okna.\n"
#define MSGTR_LIBVO_VESA_YouveForcedDga "[VO_VESA] Vynutil jste DGA. Kon��m.\n"
#define MSGTR_LIBVO_VESA_CantFindValidWindowAddress "[VO_VESA] Nemohu naj�t platnou adresu okna.\n"
#define MSGTR_LIBVO_VESA_UsingBankSwitchingMode "[VO_VESA] Pou��v�m �e�im p�ep�n�n� bank (fyzick� zdroje: %08lXh, %08lXh).\n"
#define MSGTR_LIBVO_VESA_CantAllocateTemporaryBuffer "[VO_VESA] Nemohu alokovat do�asn� buffer.\n"
#define MSGTR_LIBVO_VESA_SorryUnsupportedMode "[VO_VESA] Promi�te, tento re�im nen� podporov�n, zkuste -x 640 -zoom.\n"
#define MSGTR_LIBVO_VESA_OhYouReallyHavePictureOnTv "[VO_VESA] No, skute�n� m�te obraz na televizi!\n"
#define MSGTR_LIBVO_VESA_CantInitialozeLinuxVideoOverlay "[VO_VESA] Nemohu inicializovat Linux Video Overlay.\n"
#define MSGTR_LIBVO_VESA_UsingVideoOverlay "[VO_VESA] Pou��v�m video overlay: %s.\n"
#define MSGTR_LIBVO_VESA_CantInitializeVidixDriver "[VO_VESA] Nemohu inicializovat ovlada� VIDIX.\n"
#define MSGTR_LIBVO_VESA_UsingVidix "[VO_VESA] Pou��v�m VIDIX.\n"
#define MSGTR_LIBVO_VESA_CantFindModeFor "[VO_VESA] Nemohu naj�t re�im pro: %ux%u@%u.\n"
#define MSGTR_LIBVO_VESA_InitializationComplete "[VO_VESA] Inicializace VESA je dokon�ena.\n"
#define MSGTR_LIBVO_X11_DrawFrameCalled "[VO_X11] Zavol�no draw_frame()!!!\n"
#define MSGTR_LIBVO_XV_DrawFrameCalled "[VO_XV] Zavol�no draw_frame()!!!\n"
#define MSGTR_LIBVO_MGA_InvalidOutputFormat "mga: �patn� v�stupn� form�t %0X\n"
#define MSGTR_LIBVO_SDL_InitializationFailed "[VO_SDL] Nepoda�ilo se inicializovat SDL: %s.\n"