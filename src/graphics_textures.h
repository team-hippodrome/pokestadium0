/* Declarations for src/graphics_textures.c. */
#ifndef GRAPHICS_TEXTURES_H
#define GRAPHICS_TEXTURES_H

#include "global.h"

extern FontContext* font_context;

// graphics_textures.c
void Gfx_DrawTexturedRect(s32 x1, s32 y1, s32 width, s32 height, s32 texture_step_x, s32 texture_step_y, s32 texture_step_x_mode);
void Gfx_SetVertexAttributes(Vtx* vertex, s16 x, s16 y, s16 z, s16 texture_x, s16 texture_y, u8 r, u8 g, u8 b, u8 alpha) ;
void Gfx_SetViewportDimensions(Vp* viewport, s16 width, s16 height);

// functions defined in assembly
void Font_Printf(s32 x, s32 y, const char* fmt, ...);
void Font_DrawCharAt(s32 arg0, s32 arg1, s32 arg2);

#endif // GRAPHICS_TEXTURES_H
