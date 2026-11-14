/* Declarations for the cup_clear fragment (src/fragments/cup_clear/): the cup-cleared trophy scene. */
#ifndef FRAGMENT_CUP_CLEAR_H
#define FRAGMENT_CUP_CLEAR_H

#include "global.h"

// libultra/libc/xldtob.c
void func_8005B388(void);

// cup_clear.c
s32 CupClear_SelectTrophyCallback(s32 context, GeoSwitchCaseNode* node);
void CupClear_PollInput(void);
void func_8180006C(UNUSED CameraNode* arg0);
s32 CupClear_DrawFrame(s32 arg0);
void CupClear_DrawBannerPanel(s16 x, s16 y, s16 width, s16 height);
void CupClear_ShowBannerText(s32 frames, s32 blink);
void CupClear_PullBackCamera(void);
void CupClear_OpenBannerPanel(void);
void func_8180050C(void);
void CupClear_PlaySequence(void);
void CupClear_InitScene(void);
s32 CupClear_Main(s32 arg0, s32 cup);

#endif // FRAGMENT_CUP_CLEAR_H
