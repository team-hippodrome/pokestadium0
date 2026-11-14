/* Declarations for src/fragments/fatal_error_screen/. */
#ifndef FATAL_ERROR_SCREEN_H
#define FATAL_ERROR_SCREEN_H

#include "global.h"

// fatal_error_screen.c
void FatalError_DrawBackground(s32 unused0, s32 unused1, s32 unused2);
void FatalError_DrawWarningIcon(s32 x, s32 y);
void FatalError_DrawMessagePanel(s32 messageId);
void FatalError_DrawPortDiagram(s32 port);
s32 FatalError_DrawFrame(u8 fadeMode);
void FatalError_Main(s32 port, s32 messageId);

#endif // FATAL_ERROR_SCREEN_H
