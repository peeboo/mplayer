
#include "events.h"

evName evNames[] =
 {
  { evNone,              "evNone"              },
  { evPlay,              "evPlay"              },
  { evStop,              "evStop"              },
  { evPause,             "evPause"             },
  { evPrev,              "evPrev"              },
  { evNext,              "evNext"              },
  { evLoad,              "evLoad"              },
  { evEqualeaser,        "evEqualeaser"        },
  { evPlayList,          "evPlaylist"          },
  { evExit,              "evExit"              },
  { evIconify,           "evIconify"           },
  { evIncBalance,        "evIncBalance"        },
  { evDecBalance,        "evDecBalance"        },
  { evFullScreen,        "evFullScreen"        },
  { evFName,             "evFName"             },
  { evMovieTime,         "evMovieTime"         },
  { evAbout,             "evAbout"             },
  { evLoadPlay,          "evLoadPlay"          },
  { evPreferences,       "evPreferences"       },
  { evSkinBrowser,       "evSkinBrowser"       },
  { evBackward10sec,     "evBackward10sec"     },
  { evForward10sec,      "evForward10sec"      },
  { evBackward1min,      "evBackward1min"      },
  { evForward1min,       "evForward1min"       },
  { evBackward10min,     "evBackward10min"     },
  { evForward10min,      "evForward10min"      },
  { evIncVolume,         "evIncVolume"         },
  { evDecVolume,         "evDecVolume"         },
  { evMute,              "evMute"              },
  { evIncAudioBufDelay,  "evIncAudioBufDelay"  },
  { evDecAudioBufDelay,  "evDecAudioBufDelay"  },
  { evPlaySwitchToPause, "evPlaySwitchToPause" },
  { evPauseSwitchToPlay, "evPauseSwitchToPlay" },
  { evNormalSize,        "evNormalSize"        },
  { evDoubleSize,        "evDoubleSize"        },
  { evSetMoviePosition,  "evSetMoviePosition"  },
  { evSetVolume,         "evSetVolume"         },
  { evSetBalance,        "evSetBalance"        },
  { evHelp,		 "evHelp"	       },	
  { evLoadSubtitle,      "evLoadSubtitle"      },
  { evPlayDVD,		 "evPlayDVD"	       }
 };

int evBoxs = sizeof( evNames ) / sizeof( evName );
