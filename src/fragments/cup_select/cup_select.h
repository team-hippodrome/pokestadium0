/* Declarations for the cup_select fragment (src/fragments/cup_select/). */
#ifndef FRAGMENT_CUP_SELECT_H
#define FRAGMENT_CUP_SELECT_H

#include "global.h"

// libultra/libc/xldtob.c
void func_8005B388(void);

// cup_select.c
void AreaSelect_PollInput(void);
void func_8180050C(void);
void BattleScene_CameraPresetNop(UNUSED CameraNode* arg0);

// functions defined in assembly
s32 Stage_ShowIntro(void);

#endif // FRAGMENT_CUP_SELECT_H
