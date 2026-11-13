/* Declarations for src/fragments/lab_menu/. */
#ifndef LAB_MENU_H
#define LAB_MENU_H

#include "global.h"
#include "m2c_macros.h"

// lab_menu.c
void LabMenu_DrawItem(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 LabMenu_Draw(s32 arg0);
void LabMenu_UpdateCursor(void);
void LabMenu_LoadSelectedFragment(void);
s32 LabMenu_RunFrame(s32 arg0);
s32 LabMenu_Init(s32 arg0, M2C_UNK arg1);

#endif // LAB_MENU_H
