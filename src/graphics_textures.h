#ifndef _1CF30_H_
#define _1CF30_H_

#include "global.h"

extern FontContext* font_context;

void Gfx_DrawTexturedRect(s32 x1, s32 y1, s32 width, s32 height, s32 texture_step_x, s32 texture_step_y, s32 texture_step_x_mode);
void Gfx_DrawTextureRgba16(s32 x1, s32 y1, s32 draw_width, s32 height, u8* texture, s32 load_width, s32 texture_spread_x_mode);
void Gfx_DrawTextureRgba32(s32 x1, s32 y1, s32 draw_width, s32 height, u8* texture, s32 load_width, s32 texture_spread_x_mode);
void Gfx_DrawTextureIa8(s32 x1, s32 y1, s32 draw_width, s32 height, u8* texture, s32 load_width, s32 texture_spread_x_mode);
void Gfx_DrawTextureIa16(s32 x1, s32 y1, s32 draw_width, s32 height, u8* texture, s32 load_width, s32 texture_spread_x_mode);
void Gfx_DrawTextureI4(s32 x1, s32 y1, s32 draw_width, s32 height, u8* texture, s32 load_width, s32 texture_spread_x_mode);
void Gfx_DrawTextureI8(s32 x1, s32 y1, s32 draw_width, s32 height, u8* texture, s32 load_width, s32 texture_spread_x_mode);
void Gfx_DrawTextureI16(s32 x1, s32 y1, s32 draw_width, s32 height, u8* texture, s32 load_width, s32 texture_spread_x_mode);
void Gfx_DrawTextureRgba16Ia8(s32 x1, s32 y1, s32 draw_width, s32 height, u8* texture, u8* texture_multi, s32 load_width, s32 texture_x_spread_mode);

void Gfx_SetVertexAttributes(Vtx* vertex, s16 x, s16 y, s16 z, s16 texture_x, s16 texture_y, u8 r, u8 g, u8 b, u8 alpha) ;
void Gfx_SetViewportDimensions(Vp* viewport, s16 width, s16 height);
void Font_ResetContext(UNUSED s32 arg0, UNUSED s32 arg1);
s32 Font_GetSetIndexFromMask(s32 mask);
s32 Font_Init(s32 load_size, s32 side);
void Font_Free(void);
void Font_SetActive(s32 mask, s32 arg1);
char* String_CopyBytesAndAdvance(char* buffer, const char* data, u32 size);
void Font_Printf(s32 x, s32 y, const char* fmt, ...);
void Font_DrawCharAt(s32 arg0, s32 arg1, s32 arg2);
void Gfx_SetEnvColor(s32 r, s32 g, s32 b, s32 a);
void Gfx_SetPrimColor(s32 r, s32 g, s32 b, s32 a);
void Font_SetLineHeight(s32 arg0);
void Font_BeginTranslucentTextRendering(void);
void Font_EndTexturedTextRendering(void);
void Font_EnableTwoCycleTexturing(void);
void Font_DisableTwoCycleTexturing(void);

#endif // _1CF30_H_
