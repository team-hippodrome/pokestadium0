/* Declarations for src/text_renderer.c. */
#ifndef TEXT_RENDERER_H
#define TEXT_RENDERER_H

#include "global.h"

// text_renderer.c
void TextRenderer_SetupGlyphState(void);
void TextRenderer_RestoreState(void);
void TextRenderer_DrawGlyphSmall(s16 arg0, s16 arg1, s16 arg2);
void TextRenderer_DrawGlyphLarge(s16 arg0, s16 arg1, s16 arg2);
void TextRenderer_DrawString(s16 arg0, s16 arg1, s8* arg2, s32 arg3);
void TextRenderer_FlushQueuedStrings(Gfx** arg0, s32 arg1);
void TextRenderer_ClearQueuedStrings(void);
char* TextRenderer_FormatCopy(char* buffer, const char* data, size_t size);
s32 HAL_Printf(s16 x, s16 y, const char* fmt, ...);
s32 TextRenderer_QueuePersistentString(s16 x, s16 y, const char* fmt, ...);

#endif // TEXT_RENDERER_H
