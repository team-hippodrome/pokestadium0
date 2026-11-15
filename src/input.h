/* Declarations for src/input.c. */
#ifndef INPUT_H
#define INPUT_H

#include "global.h"
#include "m2c_macros.h"

// input.c
void Input_ResetRepeatState(void);
void func_8001B884(s32, s32, s32, s32, u8*, s32, s32);
void Gfx_DrawTextureRgba16(s32 x1, s32 y1, s32 draw_width, s32 height, u8* texture, s32 load_width, s32 texture_spread_x_mode);
void Gfx_DrawTextureRgba32(s32 x1, s32 y1, s32 draw_width, s32 height, u8* texture, s32 load_width, s32 texture_spread_x_mode);
void Gfx_DrawTextureIa8(s32 x1, s32 y1, s32 draw_width, s32 height, u8* texture, s32 load_width, s32 texture_spread_x_mode);
void Gfx_DrawTextureIa16(s32 x1, s32 y1, s32 draw_width, s32 height, u8* texture, s32 load_width, s32 texture_spread_x_mode);
void Gfx_DrawTextureI4(s32 x1, s32 y1, s32 draw_width, s32 height, u8* texture, s32 load_width, s32 texture_spread_x_mode);
void Gfx_DrawTextureI8(s32 x1, s32 y1, s32 draw_width, s32 height, u8* texture, s32 load_width, s32 texture_spread_x_mode);
void Gfx_DrawTextureI16(s32 x1, s32 y1, s32 draw_width, s32 height, u8* texture, s32 load_width, s32 texture_spread_x_mode);
void Gfx_DrawTextureRgba16Ia8(s32 x1, s32 y1, s32 draw_width, s32 height, u8* texture, u8* texture_multi, s32 load_width, s32 texture_x_spread_mode);

#endif // INPUT_H
