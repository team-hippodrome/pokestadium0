/* Declarations for src/font.c. */
#ifndef FONT_H
#define FONT_H

#include "global.h"
#include "stdarg.h"
#include "moves.h"
#include "m2c_macros.h"

// font.c
void Font_SetLineHeight(s32 arg0);                     /* extern */
void Font_ResetContext(UNUSED s32 arg0, UNUSED s32 arg1);
s32 Font_GetSetIndexFromMask(s32 mask);
s32 Font_Init(s32 load_size, s32 side);
void Font_Free(void);
void Font_SetActive(s32 mask, s32 arg1);
char* String_CopyBytesAndAdvance(char* buffer, const char* data, u32 size);
void Gfx_SetEnvColor(s32 r, s32 g, s32 b, s32 a);
void Gfx_SetPrimColor(s32 r, s32 g, s32 b, s32 a);
void Font_BeginTranslucentTextRendering(void);
void Font_EndTexturedTextRendering(void);
void Font_EnableTwoCycleTexturing(void);
void Font_DisableTwoCycleTexturing(void);

#endif // FONT_H
