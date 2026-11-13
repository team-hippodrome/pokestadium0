/* Declarations for src/audio_sound_state.c. */
#ifndef AUDIO_SOUND_STATE_H
#define AUDIO_SOUND_STATE_H

#include "global.h"

// libnumus/player.c
s32 Audio_GetActivityScore(void);

// audio_sound_state.c
s32 Audio_GetActiveVoiceCount(void);

#endif // AUDIO_SOUND_STATE_H
