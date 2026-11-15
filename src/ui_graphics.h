/* Declarations for src/ui_graphics.c. */
#ifndef UI_GRAPHICS_H
#define UI_GRAPHICS_H

#include "global.h"

extern Gfx gUiTranslucentFillDL[];

extern Gfx D_80060290[];

extern Gfx gUiEnvTintTextureDL[];

extern Gfx gUiRestoreTextureDL[];

extern Gfx D_80060990[];

// ui_graphics.c
s32 Ui_DrawTexturedRect8x8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8* arg4);
void Ui_DrawBorderStyleA(s32 x1, s32 y1, s32 width, s32 height);
void Ui_DrawBorderStyleB(s32 x1, s32 y1, s32 width, s32 height);
void Ui_DrawBorderStyleC(s32 x1, s32 y1, s32 width, s32 height);
void Ui_FillInsetRectangleA(s32 x1, s32 y1, s32 width, s32 height, u16 color);
void Ui_FillInsetRectangleB(s32 x1, s32 y1, s32 width, s32 height, u16 color);
void Ui_DrawBorderedPanel(s32 x1, s32 y1, s32 width, s32 height, u16 color);
void Ui_DrawGradientPanel(s32 x1, s32 y1, s32 width, s32 height, Color_RGB8* top_color, Color_RGB8* bottom_color);
void Ui_DrawBorderedPanelStyleB(s32 x1, s32 y1, s32 width, s32 height, u16 color);
void Ui_DrawBorderedPanelNoFill(s32 x1, s32 y1, s32 width, s32 height);
void Ui_DrawTextureMarker(s32 x, s32 y);
void Ui_Draw20x20Icon(s32 arg0, s32 arg1, s32 arg2);
void BattleHud_DrawHpBarTexture(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void BattleHud_DrawGradientRect(s32 arg0, s32 arg1, s32 arg2, s32 arg3, Color_RGB8* arg4, Color_RGB8* arg5);
void Widget_DrawMeterBar(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

#endif // UI_GRAPHICS_H
