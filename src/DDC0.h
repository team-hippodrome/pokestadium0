#ifndef _DDC0_H_
#define _DDC0_H_

#include "global.h"

void func_8000A798(void);
void func_80024044(void);
void func_80033750(void);
void func_800350E0(void);
void Audio_ResetCurrentMusic(void);
void Audio_PlayMusicIfChanged(s32 arg0);
void Audio_StopMusic(s32 arg0);
s32 Audio_WaitForIdle(s32 arg0);
void Audio_FadeOutForShutdown(void);
void Audio_Disable(void);
void Audio_Enable(void);
void Audio_StartThread(void);

#endif // _DDC0_H_
