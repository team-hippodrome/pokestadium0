#ifndef _FRAGMENT48_H_
#define _FRAGMENT48_H_

#include "global.h"

void func_82183DC4(void);
void func_82183E1C(void);
void func_821853EC(void);
void GalleryDebugger_LoadDeckEntries(void);
void GalleryDebugger_SaveDeckEntries(void);
void GalleryDebugger_DrawMenu(void);
void GalleryDebugger_DrawFrame(void);
s32 GalleryDebugger_HandleMenuInput(void);
s32 GalleryDebugger_UpdateFadeState(void);
void GalleryDebugger_PollInput(void);
void GalleryDebugger_MenuLoop(void);
s32 GalleryDebugger_Main(s32 arg0, s32 arg1);

#endif // _FRAGMENT48_H_
