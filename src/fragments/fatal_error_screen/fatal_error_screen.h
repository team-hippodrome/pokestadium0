/* Declarations for src/fragments/fatal_error_screen/. */
#ifndef FATAL_ERROR_SCREEN_H
#define FATAL_ERROR_SCREEN_H

#include "global.h"

// fatal_error_screen.c
void TransferPakError_DrawBackgroundPattern(s32 arg0, s32 arg1, s32 arg2);
void FatalError_DrawIcon(s32 arg0, s32 arg1);
void FatalError_DrawMessagePanel(s32 arg0);
void FatalError_DrawPortDiagram(s32 arg0);
s32 TransferPakError_DrawFrame(u8 arg0);
void TransferPakError_Main(s32 arg0, s32 arg1);

#endif // FATAL_ERROR_SCREEN_H
