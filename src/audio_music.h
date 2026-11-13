/* Declarations for src/audio_music.c. */
#ifndef AUDIO_MUSIC_H
#define AUDIO_MUSIC_H

#include "global.h"
#include "stdarg.h"
#include "moves.h"
#include "m2c_macros.h"

// audio_music.c
void Audio_ResetCurrentMusic(void);
void Audio_PlayMusicIfChanged(s32 arg0);
void Audio_StopMusic(s32 arg0);
s32 Audio_WaitForIdle(s32 arg0);
void Audio_FadeOutForShutdown(void);
void Audio_Disable(void);
void Audio_Enable(void);
M2C_UNK func_8000A7B0(M2C_UNK);                     /* extern */

// functions defined in assembly
void Audio_StartThread(void);

#endif // AUDIO_MUSIC_H
