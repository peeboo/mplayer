// $Revision$
// MASTER FILE. Use this file as base for translations.
// Translated files should be sent to the mplayer-DOCS mailing list or
// to the help messages maintainer, see DOCS/tech/MAINTAINERS.
// The header of the translated file should contain credits and contact
// information. Before major releases we will notify all translators to update
// their files. Please do not simply translate and forget this, outdated
// translations quickly become worthless. To help us spot outdated files put a
// note like "sync'ed with help_mp-en.h XXX" in the header of the translation.
// Do NOT translate the above lines, just follow the instructions.

// ========================= MPlayer help ===========================

#ifdef HELP_MP_DEFINE_STATIC
static char help_text[]=
"Usage:   mplayer [options] [url|path/]filename\n"
"\n"
"Basic options: (complete list in the man page)\n"
" -vo <drv[:dev]>  select video output driver & device ('-vo help' for a list)\n"
" -ao <drv[:dev]>  select audio output driver & device ('-ao help' for a list)\n"
#ifdef HAVE_VCD
" vcd://<trackno>   play (S)VCD (Super Video CD) track (raw device, no mount)\n"
#endif
#ifdef USE_DVDREAD
" dvd://<titleno>   play DVD title from device instead of plain file\n"
" -alang/-slang    select DVD audio/subtitle language (by 2-char country code)\n"
#endif
" -ss <timepos>    seek to given (seconds or hh:mm:ss) position\n"
" -nosound         do not play sound\n"
" -fs              fullscreen playback (or -vm, -zoom, details in the man page)\n"
" -x <x> -y <y>    set display resolution (for use with -vm or -zoom)\n"
" -sub <file>      specify subtitle file to use (also see -subfps, -subdelay)\n"
" -playlist <file> specify playlist file\n"
" -vid x -aid y    select video (x) and audio (y) stream to play\n"
" -fps x -srate y  change video (x fps) and audio (y Hz) rate\n"
" -pp <quality>    enable postprocessing filter (details in the man page)\n"
" -framedrop       enable frame dropping (for slow machines)\n"
"\n"
"Basic keys: (complete list in the man page, also check input.conf)\n"
" <-  or  ->       seek backward/forward 10 seconds\n"
" up or down       seek backward/forward  1 minute\n"
" pgup or pgdown   seek backward/forward 10 minutes\n"
" < or >           step backward/forward in playlist\n"
" p or SPACE       pause movie (press any key to continue)\n"
" q or ESC         stop playing and quit program\n"
" + or -           adjust audio delay by +/- 0.1 second\n"
" o                cycle OSD mode:  none / seekbar / seekbar + timer\n"
" * or /           increase or decrease PCM volume\n"
" z or x           adjust subtitle delay by +/- 0.1 second\n"
" r or t           adjust subtitle position up/down, also see -vf expand\n"
"\n"
" * * * SEE THE MAN PAGE FOR DETAILS, FURTHER (ADVANCED) OPTIONS AND KEYS * * *\n"
"\n";
#endif

// ========================= MPlayer messages ===========================

// mplayer.c:

#define MSGTR_Exiting "\nExiting...\n"
#define MSGTR_ExitingHow "\nExiting... (%s)\n"
#define MSGTR_Exit_quit "Quit"
#define MSGTR_Exit_eof "End of file"
#define MSGTR_Exit_error "Fatal error"
#define MSGTR_IntBySignal "\nMPlayer interrupted by signal %d in module: %s\n"
#define MSGTR_NoHomeDir "Cannot find HOME directory.\n"
#define MSGTR_GetpathProblem "get_path(\"config\") problem\n"
#define MSGTR_CreatingCfgFile "Creating config file: %s\n"
#define MSGTR_InvalidVOdriver "Invalid video output driver name: %s\nUse '-vo help' to get a list of available video drivers.\n"
#define MSGTR_InvalidAOdriver "Invalid audio output driver name: %s\nUse '-ao help' to get a list of available audio drivers.\n"
#define MSGTR_CopyCodecsConf "(Copy/link etc/codecs.conf from the MPlayer sources to ~/.mplayer/codecs.conf)\n"
#define MSGTR_BuiltinCodecsConf "Using built-in default codecs.conf.\n"
#define MSGTR_CantLoadFont "Cannot load font: %s\n"
#define MSGTR_CantLoadSub "Cannot load subtitles: %s\n"
#define MSGTR_ErrorDVDkey "Error processing DVD key.\n"
#define MSGTR_CmdlineDVDkey "The requested DVD key is used for descrambling.\n"
#define MSGTR_DVDauthOk "DVD authentication sequence seems to be OK.\n"
#define MSGTR_DumpSelectedStreamMissing "dump: FATAL: Selected stream missing!\n"
#define MSGTR_CantOpenDumpfile "Cannot open dump file.\n"
#define MSGTR_CoreDumped "Core dumped ;)\n"
#define MSGTR_FPSnotspecified "FPS not specified in the header or invalid, use the -fps option.\n"
#define MSGTR_TryForceAudioFmtStr "Trying to force audio codec driver family %s...\n"
#define MSGTR_CantFindAfmtFallback "Cannot find audio codec for forced driver family, falling back to other drivers.\n"
#define MSGTR_CantFindAudioCodec "Cannot find codec for audio format 0x%X.\n"
#define MSGTR_RTFMCodecs "Read DOCS/HTML/en/codecs.html!\n"
#define MSGTR_CouldntInitAudioCodec "Could not initialize audio codec -> no sound.\n"
#define MSGTR_TryForceVideoFmtStr "Trying to force video codec driver family %s...\n"
#define MSGTR_CantFindVideoCodec "Cannot find codec matching selected -vo and video format 0x%X.\n"
#define MSGTR_CannotInitVO "FATAL: Cannot initialize video driver.\n"
#define MSGTR_CannotInitAO "Could not open/initialize audio device -> no sound.\n"
#define MSGTR_StartPlaying "Starting playback...\n"

#define MSGTR_SystemTooSlow "\n\n"\
"           ************************************************\n"\
"           **** Your system is too SLOW to play this!  ****\n"\
"           ************************************************\n\n"\
"Possible reasons, problems, workarounds:\n"\
"- Most common: broken/buggy _audio_ driver\n"\
"  - Try -ao sdl or use ALSA 0.5 or the OSS emulation of ALSA 0.9.\n"\
"  - Experiment with different values for -autosync, 30 is a good start.\n"\
"- Slow video output\n"\
"  - Try a different -vo driver (-vo help for a list) or try -framedrop!\n"\
"- Slow CPU\n"\
"  - Don't try to play a big DVD/DivX on a slow CPU! Try -hardframedrop.\n"\
"- Broken file\n"\
"  - Try various combinations of -nobps -ni -forceidx -mc 0.\n"\
"- Slow media (NFS/SMB mounts, DVD, VCD etc)\n"\
"  - Try -cache 8192.\n"\
"- Are you using -cache to play a non-interleaved AVI file?\n"\
"  - Try -nocache.\n"\
"Read DOCS/HTML/en/devices.html for tuning/speedup tips.\n"\
"If none of this helps you, read DOCS/HTML/en/bugreports.html.\n\n"

#define MSGTR_NoGui "MPlayer was compiled WITHOUT GUI support.\n"
#define MSGTR_GuiNeedsX "MPlayer GUI requires X11.\n"
#define MSGTR_Playing "Playing %s.\n"
#define MSGTR_NoSound "Audio: no sound\n"
#define MSGTR_FPSforced "FPS forced to be %5.3f  (ftime: %5.3f).\n"
#define MSGTR_CompiledWithRuntimeDetection "Compiled with runtime CPU detection - WARNING - this is not optimal!\nTo get best performance, recompile MPlayer with --disable-runtime-cpudetection.\n"
#define MSGTR_CompiledWithCPUExtensions "Compiled for x86 CPU with extensions:"
#define MSGTR_AvailableVideoOutputPlugins "Available video output plugins:\n"
#define MSGTR_AvailableVideoOutputDrivers "Available video output drivers:\n"
#define MSGTR_AvailableAudioOutputDrivers "Available audio output drivers:\n"
#define MSGTR_AvailableAudioCodecs "Available audio codecs:\n"
#define MSGTR_AvailableVideoCodecs "Available video codecs:\n"
#define MSGTR_AvailableAudioFm "\nAvailable (compiled-in) audio codec families/drivers:\n"
#define MSGTR_AvailableVideoFm "\nAvailable (compiled-in) video codec families/drivers:\n"
#define MSGTR_AvailableFsType "Available fullscreen layer change modes:\n"
#define MSGTR_UsingRTCTiming "Using Linux hardware RTC timing (%ldHz).\n"
#define MSGTR_CannotReadVideoProperties "Video: Cannot read properties.\n"
#define MSGTR_NoStreamFound "No stream found.\n"
#define MSGTR_InitializingAudioCodec "Initializing audio codec...\n"
#define MSGTR_ErrorInitializingVODevice "Error opening/initializing the selected video_out (-vo) device.\n"
#define MSGTR_ForcedVideoCodec "Forced video codec: %s\n"
#define MSGTR_ForcedAudioCodec "Forced audio codec: %s\n"
#define MSGTR_AODescription_AOAuthor "AO: Description: %s\nAO: Author: %s\n"
#define MSGTR_AOComment "AO: Comment: %s\n"
#define MSGTR_Video_NoVideo "Video: no video\n"
#define MSGTR_NotInitializeVOPorVO "\nFATAL: Could not initialize video filters (-vf) or video output (-vo).\n"
#define MSGTR_Paused "\n  =====  PAUSE  =====\r" // no more than 23 characters (status line for audio files)
#define MSGTR_PlaylistLoadUnable "\nUnable to load playlist %s.\n"
#define MSGTR_Exit_SIGILL_RTCpuSel \
"- MPlayer crashed by an 'Illegal Instruction'.\n"\
"  It may be a bug in our new runtime CPU-detection code...\n"\
"  Please read DOCS/HTML/en/bugreports.html.\n"
#define MSGTR_Exit_SIGILL \
"- MPlayer crashed by an 'Illegal Instruction'.\n"\
"  It usually happens when you run it on a CPU different than the one it was\n"\
"  compiled/optimized for.\n"\
"  Verify this!\n"
#define MSGTR_Exit_SIGSEGV_SIGFPE \
"- MPlayer crashed by bad usage of CPU/FPU/RAM.\n"\
"  Recompile MPlayer with --enable-debug and make a 'gdb' backtrace and\n"\
"  disassembly. Details in DOCS/HTML/en/bugreports_what.html#bugreports_crash.\n"
#define MSGTR_Exit_SIGCRASH \
"- MPlayer crashed. This shouldn't happen.\n"\
"  It can be a bug in the MPlayer code _or_ in your drivers _or_ in your\n"\
"  gcc version. If you think it's MPlayer's fault, please read\n"\
"  DOCS/HTML/en/bugreports.html and follow the instructions there. We can't and\n"\
"  won't help unless you provide this information when reporting a possible bug.\n"

#define MSGTR_EdlCantUseBothModes "Can't use -edl and -edlout at the same time.\n"
#define MSGTR_EdlOutOfMem "Can't allocate enough memory to hold EDL data.\n"
#define MSGTR_EdlRecordsNo "Read %d EDL actions.\n"
#define MSGTR_EdlQueueEmpty "There are no EDL actions to take care of.\n"
#define MSGTR_EdlCantOpenForWrite "Error opening file [%s] for writing.\n"
#define MSGTR_EdlCantOpenForRead "Can't open EDL file [%s] for reading.\n"
#define MSGTR_EdlNOsh_video "Cannot use EDL without video, disabling.\n"
#define MSGTR_EdlNOValidLine "Invalid EDL line: %s\n"
#define MSGTR_EdlBadlyFormattedLine "Badly formatted EDL line [%d] Discarding.\n"
#define MSGTR_EdlBadLineOverlap "Last stop position was [%f]; next start is "\
"[%f]. Entries must be in chronological order, cannot overlap. Discarding.\n"
#define MSGTR_EdlBadLineBadStop "Stop time has to be after start time.\n"

// mencoder.c:

#define MSGTR_UsingPass3ControllFile "Using pass3 control file: %s\n"
#define MSGTR_MissingFilename "\nFilename missing.\n\n"
#define MSGTR_CannotOpenFile_Device "Cannot open file/device.\n"
#define MSGTR_ErrorDVDAuth "Error in DVD authentication.\n"
#define MSGTR_CannotOpenDemuxer "Cannot open demuxer.\n"
#define MSGTR_NoAudioEncoderSelected "\nNo audio encoder (-oac) selected. Select one (see -oac help) or use -nosound.\n"
#define MSGTR_NoVideoEncoderSelected "\nNo video encoder (-ovc) selected. Select one (see -ovc help).\n"
#define MSGTR_InitializingAudioCodec "Initializing audio codec...\n"
#define MSGTR_CannotOpenOutputFile "Cannot open output file '%s'.\n"
#define MSGTR_EncoderOpenFailed "Failed to open the encoder.\n"
#define MSGTR_ForcingOutputFourcc "Forcing output fourcc to %x [%.4s]\n"
#define MSGTR_WritingAVIHeader "Writing AVI header...\n"
#define MSGTR_DuplicateFrames "\n%d duplicate frame(s)!\n"
#define MSGTR_SkipFrame "\nSkipping frame!\n"
#define MSGTR_ErrorWritingFile "%s: Error writing file.\n"
#define MSGTR_WritingAVIIndex "\nWriting AVI index...\n"
#define MSGTR_FixupAVIHeader "Fixing AVI header...\n"
#define MSGTR_RecommendedVideoBitrate "Recommended video bitrate for %s CD: %d\n"
#define MSGTR_VideoStreamResult "\nVideo stream: %8.3f kbit/s  (%d bps)  size: %d bytes  %5.3f secs  %d frames\n"
#define MSGTR_AudioStreamResult "\nAudio stream: %8.3f kbit/s  (%d bps)  size: %d bytes  %5.3f secs\n"
#define MSGTR_OpenedStream "success: format: %d  data: 0x%X - 0x%x\n"
#define MSGTR_VCodecFramecopy "videocodec: framecopy (%dx%d %dbpp fourcc=%x)\n"
#define MSGTR_ACodecFramecopy "audiocodec: framecopy (format=%x chans=%d rate=%ld bits=%d bps=%ld sample-%ld)\n"
#define MSGTR_CBRPCMAudioSelected "CBR PCM audio selected\n"
#define MSGTR_MP3AudioSelected "MP3 audio selected\n"
#define MSGTR_CannotAllocateBytes "Couldn't allocate %d bytes\n"
#define MSGTR_SettingAudioDelay "Setting AUDIO DELAY to %5.3f\n"
#define MSGTR_SettingAudioInputGain "Setting audio input gain to %f\n"
#define MSGTR_LamePresetEquals "\npreset=%s\n\n"
#define MSGTR_LimitingAudioPreload "Limiting audio preload to 0.4s\n"
#define MSGTR_IncreasingAudioDensity "Increasing audio density to 4\n"
#define MSGTR_ZeroingAudioPreloadAndMaxPtsCorrection "Forcing audio preload to 0, max pts correction to 0\n"
#define MSGTR_CBRAudioByterate "\n\nCBR audio: %ld bytes/sec, %d bytes/block\n"
#define MSGTR_LameVersion "LAME version %s (%s)\n\n"
#define MSGTR_InvalidBitrateForLamePreset "Error: The bitrate specified is out of the valid range for this preset\n"\
"\n"\
"When using this mode you must enter a value between \"8\" and \"320\"\n"\
"\n"\
"For further information try: \"-lameopts preset=help\"\n"
#define MSGTR_InvalidLamePresetOptions "Error: You did not enter a valid profile and/or options with preset\n"\
"\n"\
"Available profiles are:\n"\
"\n"\
"   <fast>        standard\n"\
"   <fast>        extreme\n"\
"                 insane\n"\
"   <cbr> (ABR Mode) - The ABR Mode is implied. To use it,\n"\
"                      simply specify a bitrate. For example:\n"\
"                      \"preset=185\" activates this\n"\
"                      preset and uses 185 as an average kbps.\n"\
"\n"\
"    Some examples:\n"\
"\n"\
"    \"-lameopts fast:preset=standard  \"\n"\
" or \"-lameopts  cbr:preset=192       \"\n"\
" or \"-lameopts      preset=172       \"\n"\
" or \"-lameopts      preset=extreme   \"\n"\
"\n"\
"For further information try: \"-lameopts preset=help\"\n"
#define MSGTR_LamePresetsLongInfo "\n"\
"The preset switches are designed to provide the highest possible quality.\n"\
"\n"\
"They have for the most part been subject to and tuned via rigorous double blind\n"\
"listening tests to verify and achieve this objective.\n"\
"\n"\
"These are continually updated to coincide with the latest developments that\n"\
"occur and as a result should provide you with nearly the best quality\n"\
"currently possible from LAME.\n"\
"\n"\
"To activate these presets:\n"\
"\n"\
"   For VBR modes (generally highest quality):\n"\
"\n"\
"     \"preset=standard\" This preset should generally be transparent\n"\
"                             to most people on most music and is already\n"\
"                             quite high in quality.\n"\
"\n"\
"     \"preset=extreme\" If you have extremely good hearing and similar\n"\
"                             equipment, this preset will generally provide\n"\
"                             slightly higher quality than the \"standard\"\n"\
"                             mode.\n"\
"\n"\
"   For CBR 320kbps (highest quality possible from the preset switches):\n"\
"\n"\
"     \"preset=insane\"  This preset will usually be overkill for most\n"\
"                             people and most situations, but if you must\n"\
"                             have the absolute highest quality with no\n"\
"                             regard to filesize, this is the way to go.\n"\
"\n"\
"   For ABR modes (high quality per given bitrate but not as high as VBR):\n"\
"\n"\
"     \"preset=<kbps>\"  Using this preset will usually give you good\n"\
"                             quality at a specified bitrate. Depending on the\n"\
"                             bitrate entered, this preset will determine the\n"\
"                             optimal settings for that particular situation.\n"\
"                             While this approach works, it is not nearly as\n"\
"                             flexible as VBR, and usually will not attain the\n"\
"                             same level of quality as VBR at higher bitrates.\n"\
"\n"\
"The following options are also available for the corresponding profiles:\n"\
"\n"\
"   <fast>        standard\n"\
"   <fast>        extreme\n"\
"                 insane\n"\
"   <cbr> (ABR Mode) - The ABR Mode is implied. To use it,\n"\
"                      simply specify a bitrate. For example:\n"\
"                      \"preset=185\" activates this\n"\
"                      preset and uses 185 as an average kbps.\n"\
"\n"\
"   \"fast\" - Enables the new fast VBR for a particular profile. The\n"\
"            disadvantage to the speed switch is that often times the\n"\
"            bitrate will be slightly higher than with the normal mode\n"\
"            and quality may be slightly lower also.\n"\
"   Warning: with the current version fast presets might result in too\n"\
"            high bitrate compared to regular presets.\n"\
"\n"\
"   \"cbr\"  - If you use the ABR mode (read above) with a significant\n"\
"            bitrate such as 80, 96, 112, 128, 160, 192, 224, 256, 320,\n"\
"            you can use the \"cbr\" option to force CBR mode encoding\n"\
"            instead of the standard abr mode. ABR does provide higher\n"\
"            quality but CBR may be useful in situations such as when\n"\
"            streaming an mp3 over the internet may be important.\n"\
"\n"\
"    For example:\n"\
"\n"\
"    \"-lameopts fast:preset=standard  \"\n"\
" or \"-lameopts  cbr:preset=192       \"\n"\
" or \"-lameopts      preset=172       \"\n"\
" or \"-lameopts      preset=extreme   \"\n"\
"\n"\
"\n"\
"A few aliases are available for ABR mode:\n"\
"phone => 16kbps/mono        phon+/lw/mw-eu/sw => 24kbps/mono\n"\
"mw-us => 40kbps/mono        voice => 56kbps/mono\n"\
"fm/radio/tape => 112kbps    hifi => 160kbps\n"\
"cd => 192kbps               studio => 256kbps"
#define MSGTR_ConfigfileError "configfile error"
#define MSGTR_ErrorParsingCommandLine "error parsing cmdline"
#define MSGTR_VideoStreamRequired "Video stream is mandatory!\n"
#define MSGTR_ForcingInputFPS "input fps will be interpreted as %5.2f instead\n"
#define MSGTR_RawvideoDoesNotSupportAudio "Output file format RAWVIDEO does not support audio - disabling audio\n"
#define MSGTR_DemuxerDoesntSupportNosound "This demuxer doesn't support -nosound yet.\n"
#define MSGTR_MemAllocFailed "memory allocation failed"
#define MSGTR_NoMatchingFilter "Couldn't find matching filter/ao format!\n"
#define MSGTR_MP3WaveFormatSizeNot30 "sizeof(MPEGLAYER3WAVEFORMAT)==%d!=30, maybe broken C compiler?\n"
#define MSGTR_NoLavcAudioCodecName "Audio LAVC, Missing codec name!\n"
#define MSGTR_LavcAudioCodecNotFound "Audio LAVC, couldn't find encoder for codec %s\n"
#define MSGTR_CouldntAllocateLavcContext "Audio LAVC, couldn't allocate context!\n"
#define MSGTR_CouldntOpenCodec "Couldn't open codec %s, br=%d\n"
#define MSGTR_FramesizeBufsizeTag "FRAME_SIZE: %d, BUFFER_SIZE: %d, TAG: 0x%x\n"

// cfg-mencoder.h:

#define MSGTR_MEncoderMP3LameHelp "\n\n"\
" vbr=<0-4>     variable bitrate method\n"\
"                0: cbr\n"\
"                1: mt\n"\
"                2: rh(default)\n"\
"                3: abr\n"\
"                4: mtrh\n"\
"\n"\
" abr           average bitrate\n"\
"\n"\
" cbr           constant bitrate\n"\
"               Also forces CBR mode encoding on subsequent ABR presets modes.\n"\
"\n"\
" br=<0-1024>   specify bitrate in kBit (CBR and ABR only)\n"\
"\n"\
" q=<0-9>       quality (0-highest, 9-lowest) (only for VBR)\n"\
"\n"\
" aq=<0-9>      algorithmic quality (0-best/slowest, 9-worst/fastest)\n"\
"\n"\
" ratio=<1-100> compression ratio\n"\
"\n"\
" vol=<0-10>    set audio input gain\n"\
"\n"\
" mode=<0-3>    (default: auto)\n"\
"                0: stereo\n"\
"                1: joint-stereo\n"\
"                2: dualchannel\n"\
"                3: mono\n"\
"\n"\
" padding=<0-2>\n"\
"                0: no\n"\
"                1: all\n"\
"                2: adjust\n"\
"\n"\
" fast          Switch on faster encoding on subsequent VBR presets modes,\n"\
"               slightly lower quality and higher bitrates.\n"\
"\n"\
" preset=<value> Provide the highest possible quality settings.\n"\
"                 medium: VBR  encoding,  good  quality\n"\
"                 (150-180 kbps bitrate range)\n"\
"                 standard:  VBR encoding, high quality\n"\
"                 (170-210 kbps bitrate range)\n"\
"                 extreme: VBR encoding, very high quality\n"\
"                 (200-240 kbps bitrate range)\n"\
"                 insane:  CBR  encoding, highest preset quality\n"\
"                 (320 kbps bitrate)\n"\
"                 <8-320>: ABR encoding at average given kbps bitrate.\n\n"

// open.c, stream.c:
#define MSGTR_CdDevNotfound "CD-ROM Device '%s' not found.\n"
#define MSGTR_ErrTrackSelect "Error selecting VCD track."
#define MSGTR_ReadSTDIN "Reading from stdin...\n"
#define MSGTR_UnableOpenURL "Unable to open URL: %s\n"
#define MSGTR_ConnToServer "Connected to server: %s\n"
#define MSGTR_FileNotFound "File not found: '%s'\n"

#define MSGTR_SMBInitError "Cannot init the libsmbclient library: %d\n"
#define MSGTR_SMBFileNotFound "Could not open from LAN: '%s'\n"
#define MSGTR_SMBNotCompiled "MPlayer was not compiled with SMB reading support.\n"

#define MSGTR_CantOpenDVD "Couldn't open DVD device: %s\n"
#define MSGTR_DVDwait "Reading disc structure, please wait...\n"
#define MSGTR_DVDnumTitles "There are %d titles on this DVD.\n"
#define MSGTR_DVDinvalidTitle "Invalid DVD title number: %d\n"
#define MSGTR_DVDnumChapters "There are %d chapters in this DVD title.\n"
#define MSGTR_DVDinvalidChapter "Invalid DVD chapter number: %d\n"
#define MSGTR_DVDnumAngles "There are %d angles in this DVD title.\n"
#define MSGTR_DVDinvalidAngle "Invalid DVD angle number: %d\n"
#define MSGTR_DVDnoIFO "Cannot open the IFO file for DVD title %d.\n"
#define MSGTR_DVDnoVOBs "Cannot open title VOBS (VTS_%02d_1.VOB).\n"
#define MSGTR_DVDopenOk "DVD successfully opened.\n"

// demuxer.c, demux_*.c:
#define MSGTR_AudioStreamRedefined "WARNING: Audio stream header %d redefined.\n"
#define MSGTR_VideoStreamRedefined "WARNING: Video stream header %d redefined.\n"
#define MSGTR_TooManyAudioInBuffer "\nToo many audio packets in the buffer: (%d in %d bytes).\n"
#define MSGTR_TooManyVideoInBuffer "\nToo many video packets in the buffer: (%d in %d bytes).\n"
#define MSGTR_MaybeNI "Maybe you are playing a non-interleaved stream/file or the codec failed?\n" \
		      "For AVI files, try to force non-interleaved mode with the -ni option.\n"
#define MSGTR_SwitchToNi "\nBadly interleaved AVI file detected - switching to -ni mode...\n"
#define MSGTR_Detected_XXX_FileFormat "%s file format detected.\n"
#define MSGTR_DetectedAudiofile "Audio file detected.\n"
#define MSGTR_NotSystemStream "Not MPEG System Stream format... (maybe Transport Stream?)\n"
#define MSGTR_InvalidMPEGES "Invalid MPEG-ES stream??? Contact the author, it may be a bug :(\n"
#define MSGTR_FormatNotRecognized "============ Sorry, this file format is not recognized/supported =============\n"\
				  "=== If this file is an AVI, ASF or MPEG stream, please contact the author! ===\n"
#define MSGTR_MissingVideoStream "No video stream found.\n"
#define MSGTR_MissingAudioStream "No audio stream found -> no sound.\n"
#define MSGTR_MissingVideoStreamBug "Missing video stream!? Contact the author, it may be a bug :(\n"

#define MSGTR_DoesntContainSelectedStream "demux: File doesn't contain the selected audio or video stream.\n"

#define MSGTR_NI_Forced "Forced"
#define MSGTR_NI_Detected "Detected"
#define MSGTR_NI_Message "%s NON-INTERLEAVED AVI file format.\n"

#define MSGTR_UsingNINI "Using NON-INTERLEAVED broken AVI file format.\n"
#define MSGTR_CouldntDetFNo "Could not determine number of frames (for absolute seek).\n"
#define MSGTR_CantSeekRawAVI "Cannot seek in raw AVI streams. (Index required, try with the -idx switch.)\n"
#define MSGTR_CantSeekFile "Cannot seek in this file.\n"

#define MSGTR_EncryptedVOB "Encrypted VOB file! Read DOCS/HTML/en/dvd.html.\n"

#define MSGTR_MOVcomprhdr "MOV: Compressed headers support requires ZLIB!\n"
#define MSGTR_MOVvariableFourCC "MOV: WARNING: Variable FOURCC detected!?\n"
#define MSGTR_MOVtooManyTrk "MOV: WARNING: too many tracks"
#define MSGTR_FoundAudioStream "==> Found audio stream: %d\n"
#define MSGTR_FoundVideoStream "==> Found video stream: %d\n"
#define MSGTR_DetectedTV "TV detected! ;-)\n"
#define MSGTR_ErrorOpeningOGGDemuxer "Unable to open the ogg demuxer.\n"
#define MSGTR_ASFSearchingForAudioStream "ASF: Searching for audio stream (id:%d).\n"
#define MSGTR_CannotOpenAudioStream "Cannot open audio stream: %s\n"
#define MSGTR_CannotOpenSubtitlesStream "Cannot open subtitle stream: %s\n"
#define MSGTR_OpeningAudioDemuxerFailed "Failed to open audio demuxer: %s\n"
#define MSGTR_OpeningSubtitlesDemuxerFailed "Failed to open subtitle demuxer: %s\n"
#define MSGTR_TVInputNotSeekable "TV input is not seekable! (Seeking will probably be for changing channels ;)\n"
#define MSGTR_DemuxerInfoAlreadyPresent "Demuxer info %s already present!\n"
#define MSGTR_ClipInfo "Clip info:\n"

#define MSGTR_LeaveTelecineMode "\ndemux_mpg: 30fps NTSC content detected, switching framerate.\n"
#define MSGTR_EnterTelecineMode "\ndemux_mpg: 24fps progressive NTSC content detected, switching framerate.\n"

// dec_video.c & dec_audio.c:
#define MSGTR_CantOpenCodec "Could not open codec.\n"
#define MSGTR_CantCloseCodec "Could not close codec.\n"

#define MSGTR_MissingDLLcodec "ERROR: Could not open required DirectShow codec %s.\n"
#define MSGTR_ACMiniterror "Could not load/initialize Win32/ACM AUDIO codec (missing DLL file?).\n"
#define MSGTR_MissingLAVCcodec "Cannot find codec '%s' in libavcodec...\n"

#define MSGTR_MpegNoSequHdr "MPEG: FATAL: EOF while searching for sequence header.\n"
#define MSGTR_CannotReadMpegSequHdr "FATAL: Cannot read sequence header.\n"
#define MSGTR_CannotReadMpegSequHdrEx "FATAL: Cannot read sequence header extension.\n"
#define MSGTR_BadMpegSequHdr "MPEG: bad sequence header\n"
#define MSGTR_BadMpegSequHdrEx "MPEG: bad sequence header extension\n"

#define MSGTR_ShMemAllocFail "Cannot allocate shared memory.\n"
#define MSGTR_CantAllocAudioBuf "Cannot allocate audio out buffer.\n"

#define MSGTR_UnknownAudio "Unknown/missing audio format -> no sound\n"

#define MSGTR_UsingExternalPP "[PP] Using external postprocessing filter, max q = %d.\n"
#define MSGTR_UsingCodecPP "[PP] Using codec's postprocessing, max q = %d.\n"
#define MSGTR_VideoAttributeNotSupportedByVO_VD "Video attribute '%s' is not supported by selected vo & vd.\n"
#define MSGTR_VideoCodecFamilyNotAvailableStr "Requested video codec family [%s] (vfm=%s) not available.\nEnable it at compilation.\n"
#define MSGTR_AudioCodecFamilyNotAvailableStr "Requested audio codec family [%s] (afm=%s) not available.\nEnable it at compilation.\n"
#define MSGTR_OpeningVideoDecoder "Opening video decoder: [%s] %s\n"
#define MSGTR_OpeningAudioDecoder "Opening audio decoder: [%s] %s\n"
#define MSGTR_UninitVideoStr "uninit video: %s\n"
#define MSGTR_UninitAudioStr "uninit audio: %s\n"
#define MSGTR_VDecoderInitFailed "VDecoder init failed :(\n"
#define MSGTR_ADecoderInitFailed "ADecoder init failed :(\n"
#define MSGTR_ADecoderPreinitFailed "ADecoder preinit failed :(\n"
#define MSGTR_AllocatingBytesForInputBuffer "dec_audio: Allocating %d bytes for input buffer.\n"
#define MSGTR_AllocatingBytesForOutputBuffer "dec_audio: Allocating %d + %d = %d bytes for output buffer.\n"

// LIRC:
#define MSGTR_SettingUpLIRC "Setting up LIRC support...\n"
#define MSGTR_LIRCdisabled "You will not be able to use your remote control.\n"
#define MSGTR_LIRCopenfailed "Failed to open LIRC support.\n"
#define MSGTR_LIRCcfgerr "Failed to read LIRC config file %s.\n"

// vf.c
#define MSGTR_CouldNotFindVideoFilter "Couldn't find video filter '%s'.\n"
#define MSGTR_CouldNotOpenVideoFilter "Couldn't open video filter '%s'.\n"
#define MSGTR_OpeningVideoFilter "Opening video filter: "
#define MSGTR_CannotFindColorspace "Cannot find matching colorspace, even by inserting 'scale' :(\n"

// vd.c
#define MSGTR_CodecDidNotSet "VDec: Codec did not set sh->disp_w and sh->disp_h, trying workaround.\n"
#define MSGTR_VoConfigRequest "VDec: vo config request - %d x %d (preferred csp: %s)\n"
#define MSGTR_CouldNotFindColorspace "Could not find matching colorspace - retrying with -vf scale...\n"
#define MSGTR_MovieAspectIsSet "Movie-Aspect is %.2f:1 - prescaling to correct movie aspect.\n"
#define MSGTR_MovieAspectUndefined "Movie-Aspect is undefined - no prescaling applied.\n"

// vd_dshow.c, vd_dmo.c
#define MSGTR_DownloadCodecPackage "You need to upgrade/install the binary codecs package.\nGo to http://mplayerhq.hu/homepage/dload.html\n"
#define MSGTR_DShowInitOK "INFO: Win32/DShow video codec init OK.\n"
#define MSGTR_DMOInitOK "INFO: Win32/DMO video codec init OK.\n"

// x11_common.c
#define MSGTR_EwmhFullscreenStateFailed "\nX11: Couldn't send EWMH fullscreen Event!\n"

#define MSGTR_InsertingAfVolume "[Mixer] No hardware mixing, inserting volume filter.\n"
#define MSGTR_NoVolume "[Mixer] No volume control available.\n"

// ====================== GUI messages/buttons ========================

#ifdef HAVE_NEW_GUI

// --- labels ---
#define MSGTR_About "About"
#define MSGTR_FileSelect "Select file..."
#define MSGTR_SubtitleSelect "Select subtitle..."
#define MSGTR_OtherSelect "Select..."
#define MSGTR_AudioFileSelect "Select external audio channel..."
#define MSGTR_FontSelect "Select font..."
#define MSGTR_PlayList "Playlist"
#define MSGTR_Equalizer "Equalizer"
#define MSGTR_SkinBrowser "Skin Browser"
#define MSGTR_Network "Network streaming..."
#define MSGTR_Preferences "Preferences"
#define MSGTR_AudioPreferences "Audio driver configuration"
#define MSGTR_NoMediaOpened "No media opened."
#define MSGTR_VCDTrack "VCD track %d"
#define MSGTR_NoChapter "No chapter"
#define MSGTR_Chapter "Chapter %d"
#define MSGTR_NoFileLoaded "No file loaded."

// --- buttons ---
#define MSGTR_Ok "OK"
#define MSGTR_Cancel "Cancel"
#define MSGTR_Add "Add"
#define MSGTR_Remove "Remove"
#define MSGTR_Clear "Clear"
#define MSGTR_Config "Config"
#define MSGTR_ConfigDriver "Configure driver"
#define MSGTR_Browse "Browse"

// --- error messages ---
#define MSGTR_NEMDB "Sorry, not enough memory for draw buffer."
#define MSGTR_NEMFMR "Sorry, not enough memory for menu rendering."
#define MSGTR_IDFGCVD "Sorry, I did not find a GUI compatible video output driver."
#define MSGTR_NEEDLAVCFAME "Sorry, you cannot play non-MPEG files with your DXR3/H+ device without reencoding.\nPlease enable lavc or fame in the DXR3/H+ configbox."

// --- skin loader error messages
#define MSGTR_SKIN_ERRORMESSAGE "[skin] error in skin config file on line %d: %s"
#define MSGTR_SKIN_WARNING1 "[skin] warning in config file line %d:\nwidget (%s) found but no \"section\" found before"
#define MSGTR_SKIN_WARNING2 "[skin] warning in config file line %d:\nwidget (%s) found but no \"subsection\" found before"
#define MSGTR_SKIN_WARNING3 "[skin] warning in config file line %d:\nthis subsection is not supported by widget (%s)"
#define MSGTR_SKIN_BITMAP_16bit  "16 bits or less depth bitmap not supported (%s).\n"
#define MSGTR_SKIN_BITMAP_FileNotFound  "file not found (%s)\n"
#define MSGTR_SKIN_BITMAP_BMPReadError "BMP read error (%s)\n"
#define MSGTR_SKIN_BITMAP_TGAReadError "TGA read error (%s)\n"
#define MSGTR_SKIN_BITMAP_PNGReadError "PNG read error (%s)\n"
#define MSGTR_SKIN_BITMAP_RLENotSupported "RLE packed TGA not supported (%s)\n"
#define MSGTR_SKIN_BITMAP_UnknownFileType "unknown file type (%s)\n"
#define MSGTR_SKIN_BITMAP_ConvertError "24 bit to 32 bit convert error (%s)\n"
#define MSGTR_SKIN_BITMAP_UnknownMessage "unknown message: %s\n"
#define MSGTR_SKIN_FONT_NotEnoughtMemory "not enough memory\n"
#define MSGTR_SKIN_FONT_TooManyFontsDeclared "Too many fonts declared.\n"
#define MSGTR_SKIN_FONT_FontFileNotFound "Font file not found.\n"
#define MSGTR_SKIN_FONT_FontImageNotFound "Font image file not found.\n"
#define MSGTR_SKIN_FONT_NonExistentFontID "non-existent font identifier (%s)\n"
#define MSGTR_SKIN_UnknownParameter "unknown parameter (%s)\n"
#define MSGTR_SKINBROWSER_NotEnoughMemory "[skinbrowser] not enough memory\n"
#define MSGTR_SKIN_SKINCFG_SkinNotFound "Skin not found (%s).\n"
#define MSGTR_SKIN_SKINCFG_SkinCfgReadError "skin configfile read error (%s)\n"
#define MSGTR_SKIN_LABEL "Skins:"

// --- gtk menus
#define MSGTR_MENU_AboutMPlayer "About MPlayer"
#define MSGTR_MENU_Open "Open..."
#define MSGTR_MENU_PlayFile "Play file..."
#define MSGTR_MENU_PlayVCD "Play VCD..."
#define MSGTR_MENU_PlayDVD "Play DVD..."
#define MSGTR_MENU_PlayURL "Play URL..."
#define MSGTR_MENU_LoadSubtitle "Load subtitle..."
#define MSGTR_MENU_DropSubtitle "Drop subtitle..."
#define MSGTR_MENU_LoadExternAudioFile "Load external audio file..."
#define MSGTR_MENU_Playing "Playing"
#define MSGTR_MENU_Play "Play"
#define MSGTR_MENU_Pause "Pause"
#define MSGTR_MENU_Stop "Stop"
#define MSGTR_MENU_NextStream "Next stream"
#define MSGTR_MENU_PrevStream "Prev stream"
#define MSGTR_MENU_Size "Size"
#define MSGTR_MENU_NormalSize "Normal size"
#define MSGTR_MENU_DoubleSize "Double size"
#define MSGTR_MENU_FullScreen "Fullscreen"
#define MSGTR_MENU_DVD "DVD"
#define MSGTR_MENU_VCD "VCD"
#define MSGTR_MENU_PlayDisc "Open disc..."
#define MSGTR_MENU_ShowDVDMenu "Show DVD menu"
#define MSGTR_MENU_Titles "Titles"
#define MSGTR_MENU_Title "Title %2d"
#define MSGTR_MENU_None "(none)"
#define MSGTR_MENU_Chapters "Chapters"
#define MSGTR_MENU_Chapter "Chapter %2d"
#define MSGTR_MENU_AudioLanguages "Audio languages"
#define MSGTR_MENU_SubtitleLanguages "Subtitle languages"
#define MSGTR_MENU_PlayList "Playlist"
#define MSGTR_MENU_SkinBrowser "Skin browser"
#define MSGTR_MENU_Preferences "Preferences"
#define MSGTR_MENU_Exit "Exit..."
#define MSGTR_MENU_Mute "Mute"
#define MSGTR_MENU_Original "Original"
#define MSGTR_MENU_AspectRatio "Aspect ratio"
#define MSGTR_MENU_AudioTrack "Audio track"
#define MSGTR_MENU_Track "Track %d"
#define MSGTR_MENU_VideoTrack "Video track"

// --- equalizer
#define MSGTR_EQU_Audio "Audio"
#define MSGTR_EQU_Video "Video"
#define MSGTR_EQU_Contrast "Contrast: "
#define MSGTR_EQU_Brightness "Brightness: "
#define MSGTR_EQU_Hue "Hue: "
#define MSGTR_EQU_Saturation "Saturation: "
#define MSGTR_EQU_Front_Left "Front Left"
#define MSGTR_EQU_Front_Right "Front Right"
#define MSGTR_EQU_Back_Left "Rear Left"
#define MSGTR_EQU_Back_Right "Rear Right"
#define MSGTR_EQU_Center "Center"
#define MSGTR_EQU_Bass "Bass"
#define MSGTR_EQU_All "All"
#define MSGTR_EQU_Channel1 "Channel 1:"
#define MSGTR_EQU_Channel2 "Channel 2:"
#define MSGTR_EQU_Channel3 "Channel 3:"
#define MSGTR_EQU_Channel4 "Channel 4:"
#define MSGTR_EQU_Channel5 "Channel 5:"
#define MSGTR_EQU_Channel6 "Channel 6:"

// --- playlist
#define MSGTR_PLAYLIST_Path "Path"
#define MSGTR_PLAYLIST_Selected "Selected files"
#define MSGTR_PLAYLIST_Files "Files"
#define MSGTR_PLAYLIST_DirectoryTree "Directory tree"

// --- preferences
#define MSGTR_PREFERENCES_Audio "Audio"
#define MSGTR_PREFERENCES_Video "Video"
#define MSGTR_PREFERENCES_SubtitleOSD "Subtitle & OSD"
#define MSGTR_PREFERENCES_Codecs "Codecs & demuxer"
#define MSGTR_PREFERENCES_Misc "Misc"

#define MSGTR_PREFERENCES_None "None"
#define MSGTR_PREFERENCES_DriverDefault "driver default"
#define MSGTR_PREFERENCES_AvailableDrivers "Available drivers:"
#define MSGTR_PREFERENCES_DoNotPlaySound "Do not play sound"
#define MSGTR_PREFERENCES_NormalizeSound "Normalize sound"
#define MSGTR_PREFERENCES_EnEqualizer "Enable equalizer"
#define MSGTR_PREFERENCES_ExtraStereo "Enable extra stereo"
#define MSGTR_PREFERENCES_Coefficient "Coefficient:"
#define MSGTR_PREFERENCES_AudioDelay "Audio delay"
#define MSGTR_PREFERENCES_DoubleBuffer "Enable double buffering"
#define MSGTR_PREFERENCES_DirectRender "Enable direct rendering"
#define MSGTR_PREFERENCES_FrameDrop "Enable frame dropping"
#define MSGTR_PREFERENCES_HFrameDrop "Enable HARD frame dropping (dangerous)"
#define MSGTR_PREFERENCES_Flip "Flip image upside down"
#define MSGTR_PREFERENCES_Panscan "Panscan: "
#define MSGTR_PREFERENCES_OSDTimer "Timer and indicators"
#define MSGTR_PREFERENCES_OSDProgress "Progressbars only"
#define MSGTR_PREFERENCES_OSDTimerPercentageTotalTime "Timer, percentage and total time"
#define MSGTR_PREFERENCES_Subtitle "Subtitle:"
#define MSGTR_PREFERENCES_SUB_Delay "Delay: "
#define MSGTR_PREFERENCES_SUB_FPS "FPS:"
#define MSGTR_PREFERENCES_SUB_POS "Position: "
#define MSGTR_PREFERENCES_SUB_AutoLoad "Disable subtitle autoloading"
#define MSGTR_PREFERENCES_SUB_Unicode "Unicode subtitle"
#define MSGTR_PREFERENCES_SUB_MPSUB "Convert the given subtitle to MPlayer's subtitle format"
#define MSGTR_PREFERENCES_SUB_SRT "Convert the given subtitle to the time based SubViewer (SRT) format"
#define MSGTR_PREFERENCES_SUB_Overlap "Toggle subtitle overlapping"
#define MSGTR_PREFERENCES_Font "Font:"
#define MSGTR_PREFERENCES_FontFactor "Font factor:"
#define MSGTR_PREFERENCES_PostProcess "Enable postprocessing"
#define MSGTR_PREFERENCES_AutoQuality "Auto quality: "
#define MSGTR_PREFERENCES_NI "Use non-interleaved AVI parser"
#define MSGTR_PREFERENCES_IDX "Rebuild index table, if needed"
#define MSGTR_PREFERENCES_VideoCodecFamily "Video codec family:"
#define MSGTR_PREFERENCES_AudioCodecFamily "Audio codec family:"
#define MSGTR_PREFERENCES_FRAME_OSD_Level "OSD level"
#define MSGTR_PREFERENCES_FRAME_Subtitle "Subtitle"
#define MSGTR_PREFERENCES_FRAME_Font "Font"
#define MSGTR_PREFERENCES_FRAME_PostProcess "Postprocessing"
#define MSGTR_PREFERENCES_FRAME_CodecDemuxer "Codec & demuxer"
#define MSGTR_PREFERENCES_FRAME_Cache "Cache"
#define MSGTR_PREFERENCES_FRAME_Misc "Misc"
#define MSGTR_PREFERENCES_Audio_Device "Device:"
#define MSGTR_PREFERENCES_Audio_Mixer "Mixer:"
#define MSGTR_PREFERENCES_Audio_MixerChannel "Mixer channel:"
#define MSGTR_PREFERENCES_Message "Please remember that you need to restart playback for some options to take effect!"
#define MSGTR_PREFERENCES_DXR3_VENC "Video encoder:"
#define MSGTR_PREFERENCES_DXR3_LAVC "Use LAVC (FFmpeg)"
#define MSGTR_PREFERENCES_DXR3_FAME "Use FAME"
#define MSGTR_PREFERENCES_FontEncoding1 "Unicode"
#define MSGTR_PREFERENCES_FontEncoding2 "Western European Languages (ISO-8859-1)"
#define MSGTR_PREFERENCES_FontEncoding3 "Western European Languages with Euro (ISO-8859-15)"
#define MSGTR_PREFERENCES_FontEncoding4 "Slavic/Central European Languages (ISO-8859-2)"
#define MSGTR_PREFERENCES_FontEncoding5 "Esperanto, Galician, Maltese, Turkish (ISO-8859-3)"
#define MSGTR_PREFERENCES_FontEncoding6 "Old Baltic charset (ISO-8859-4)"
#define MSGTR_PREFERENCES_FontEncoding7 "Cyrillic (ISO-8859-5)"
#define MSGTR_PREFERENCES_FontEncoding8 "Arabic (ISO-8859-6)"
#define MSGTR_PREFERENCES_FontEncoding9 "Modern Greek (ISO-8859-7)"
#define MSGTR_PREFERENCES_FontEncoding10 "Turkish (ISO-8859-9)"
#define MSGTR_PREFERENCES_FontEncoding11 "Baltic (ISO-8859-13)"
#define MSGTR_PREFERENCES_FontEncoding12 "Celtic (ISO-8859-14)"
#define MSGTR_PREFERENCES_FontEncoding13 "Hebrew charsets (ISO-8859-8)"
#define MSGTR_PREFERENCES_FontEncoding14 "Russian (KOI8-R)"
#define MSGTR_PREFERENCES_FontEncoding15 "Ukrainian, Belarusian (KOI8-U/RU)"
#define MSGTR_PREFERENCES_FontEncoding16 "Simplified Chinese charset (CP936)"
#define MSGTR_PREFERENCES_FontEncoding17 "Traditional Chinese charset (BIG5)"
#define MSGTR_PREFERENCES_FontEncoding18 "Japanese charsets (SHIFT-JIS)"
#define MSGTR_PREFERENCES_FontEncoding19 "Korean charset (CP949)"
#define MSGTR_PREFERENCES_FontEncoding20 "Thai charset (CP874)"
#define MSGTR_PREFERENCES_FontEncoding21 "Cyrillic Windows (CP1251)"
#define MSGTR_PREFERENCES_FontEncoding22 "Slavic/Central European Windows (CP1250)"
#define MSGTR_PREFERENCES_FontNoAutoScale "No autoscale"
#define MSGTR_PREFERENCES_FontPropWidth "Proportional to movie width"
#define MSGTR_PREFERENCES_FontPropHeight "Proportional to movie height"
#define MSGTR_PREFERENCES_FontPropDiagonal "Proportional to movie diagonal"
#define MSGTR_PREFERENCES_FontEncoding "Encoding:"
#define MSGTR_PREFERENCES_FontBlur "Blur:"
#define MSGTR_PREFERENCES_FontOutLine "Outline:"
#define MSGTR_PREFERENCES_FontTextScale "Text scale:"
#define MSGTR_PREFERENCES_FontOSDScale "OSD scale:"
#define MSGTR_PREFERENCES_Cache "Cache on/off"
#define MSGTR_PREFERENCES_CacheSize "Cache size: "
#define MSGTR_PREFERENCES_LoadFullscreen "Start in fullscreen"
#define MSGTR_PREFERENCES_SaveWinPos "Save window position"
#define MSGTR_PREFERENCES_XSCREENSAVER "Stop XScreenSaver"
#define MSGTR_PREFERENCES_PlayBar "Enable playbar"
#define MSGTR_PREFERENCES_AutoSync "AutoSync on/off"
#define MSGTR_PREFERENCES_AutoSyncValue "Autosync: "
#define MSGTR_PREFERENCES_CDROMDevice "CD-ROM device:"
#define MSGTR_PREFERENCES_DVDDevice "DVD device:"
#define MSGTR_PREFERENCES_FPS "Movie FPS:"
#define MSGTR_PREFERENCES_ShowVideoWindow "Show video window when inactive"

#define MSGTR_ABOUT_UHU "GUI development sponsored by UHU Linux\n"
#define MSGTR_ABOUT_CoreTeam "   MPlayer core team:\n"
#define MSGTR_ABOUT_AdditionalCoders "   Additional coders:\n"
#define MSGTR_ABOUT_MainTesters "   Main testers:\n"

// --- messagebox
#define MSGTR_MSGBOX_LABEL_FatalError "Fatal error!"
#define MSGTR_MSGBOX_LABEL_Error "Error!"
#define MSGTR_MSGBOX_LABEL_Warning "Warning!"

#endif

// ======================= VO Video Output drivers ========================

#define MSGTR_VOincompCodec "The selected video_out device is incompatible with this codec.\n"
#define MSGTR_VO_GenericError "This error has occurred"
#define MSGTR_VO_UnableToAccess "Unable to access"
#define MSGTR_VO_ExistsButNoDirectory "already exists, but is not a directory."
#define MSGTR_VO_DirExistsButNotWritable "Output directory already exists, but is not writable."
#define MSGTR_VO_DirExistsAndIsWritable "Output directory already exists and is writable."
#define MSGTR_VO_CantCreateDirectory "Unable to create output directory."
#define MSGTR_VO_CantCreateFile "Unable to create output file."
#define MSGTR_VO_DirectoryCreateSuccess "Output directory successfully created."
#define MSGTR_VO_ParsingSuboptions "Parsing suboptions."
#define MSGTR_VO_SuboptionsParsedOK "Suboptions parsed OK."
#define MSGTR_VO_ValueOutOfRange "Value out of range"
#define MSGTR_VO_NoValueSpecified "No value specified."
#define MSGTR_VO_UnknownSuboptions "Unknown suboption(s)"

// vo_jpeg.c
#define MSGTR_VO_JPEG_ProgressiveJPEG "Progressive JPEG enabled."
#define MSGTR_VO_JPEG_NoProgressiveJPEG "Progressive JPEG disabled."
#define MSGTR_VO_JPEG_BaselineJPEG "Baseline JPEG enabled."
#define MSGTR_VO_JPEG_NoBaselineJPEG "Baseline JPEG disabled."

