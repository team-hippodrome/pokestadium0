/* Stadium Zero resident code. */
/* C ported from the Stadium 1 decomp: src/fragments/battle_engine/battle_engine_2FA4D0.c, src/ui_graphics.c. */

#include "ui_graphics.h"
#include "graphics_textures.h"
#include "text_system.h"
#include "gfx_buffer.h"
#include "gfx_rect.h"
#include "hal_libc.h"
#include "stage_loader.h"
extern u8 D_10025D0[];
extern u8 D_1002650[];
extern u8 D_10026D0[];
extern u8 D_1002750[];
extern u8 D_10027D0[];
extern u8 D_1002850[];
extern u8 D_10028D0[];
extern u8 D_1002950[];
extern u8 D_10029D0[];
extern u8 D_1002A50[];
extern u8 D_1002AD0[];
extern u8 D_1002B50[];
extern u8 D_1002BD0[];
extern u8 D_1002C50[];
extern u8 D_1002CD0[];
extern u8 D_1002D50[];
extern u8 D_1002DD0[];
extern u8 D_1002E50[];
extern u8 D_1002ED0[];
extern u8 D_1002F50[];
extern u8 D_1002FD0[];
extern u8 D_1003050[];
extern u8 D_10030D0[];
extern u8 D_1003150[];
extern u8 D_10031D0[];
extern u8 D_1003750[];
extern u8 D_1003890[];
extern u8 D_1003930[];
extern u8 D_10039F0[];
extern u8 D_1003AB0[];
extern u8 D_1003B70[];
extern u8 D_1003C30[];
extern u8 D_1003CF0[];
extern u8 D_1003DB0[];
extern u8 D_1003E50[];
extern u8 D_1003EA0[];
extern u8 D_1003EC8[];
extern u8 D_1003EF0[];
extern u8 D_2004000[];
extern u8 D_2004320[];
extern Gfx gUiTranslucentFillDL[];
extern Gfx D_80060270[];
extern Gfx D_80060290[];
extern Gfx gUiEnvTintTextureDL[];
extern Gfx gUiRestoreTextureDL[];
extern Gfx D_80060990[];

#include "fragments/battle_engine/battle_engine.h"
#include "graphics_textures.h"
#include "ui_graphics.h"
#include "status_icons.h"
#include "game_state.h"
#include "text_system.h"
#include "3D140.h"
#include "gfx_buffer.h"
#include "gfx_rect.h"
#include "matrix.h"
#include "controller.h"
#include "memmap.h"
#include "memory.h"

void Ui_DrawBorderStyleA(s32 x1, s32 y1, s32 width, s32 height);
void Ui_DrawBorderStyleB(s32 x1, s32 y1, s32 width, s32 height);
void Ui_DrawBorderStyleC(s32 x1, s32 y1, s32 width, s32 height);
void Ui_FillInsetRectangleA(s32 x1, s32 y1, s32 width, s32 height, u16 color);
void Ui_FillInsetRectangleB(s32 x1, s32 y1, s32 width, s32 height, u16 color);
void BattleHud_DrawGradientRect(s32 arg0, s32 arg1, s32 arg2, s32 arg3, Color_RGB8* arg4, Color_RGB8* arg5);
void Ui_DrawBorderedPanel(s32 x1, s32 y1, s32 width, s32 height, u16 color);
void Ui_DrawBorderedPanelStyleB(s32 x1, s32 y1, s32 width, s32 height, u16 color);
void Ui_DrawBorderedPanelNoFill(s32 x1, s32 y1, s32 width, s32 height);
void Ui_Draw20x20Icon(s32 arg0, s32 arg1, s32 arg2);

s32 Ui_DrawTexturedRect8x8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8* arg4);

/** Draws a rectangle tiled with an 8x8 texture. */
s32 Ui_DrawTexturedRect8x8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8* arg4) {
    UNUSED s32 pad[4]; // FAKE: stack padding
    s32 sp2C;
    s32 sp28;

    if (arg2 < 9) {
        sp2C = 0x400;
    } else {
        sp2C = 0;
    }

    // clang-format off
    if (arg3 < 9) { sp28 = 0x400; } else { sp28 = 0; }
    // clang-format on

    gDPLoadTextureBlock(gDisplayListHead++, arg4, G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 8, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

    Gfx_DrawTexturedRect(arg0, arg1, (arg0 + arg2) - 1, (arg1 + arg3) - 1, sp2C, sp28, 0);
}

/** Draws a border in style A from 8x8 corner and edge textures. */
void Ui_DrawBorderStyleA(s32 x1, s32 y1, s32 width, s32 height) {
    Ui_DrawTexturedRect8x8(x1, y1, 8, 8, D_10027D0);
    Ui_DrawTexturedRect8x8(x1, (y1 + height) - 8, 8, 8, D_1002850);
    Ui_DrawTexturedRect8x8((x1 + width) - 8, (y1 + height) - 8, 8, 8, D_10028D0);
    Ui_DrawTexturedRect8x8((x1 + width) - 8, y1, 8, 8, D_1002950);

    if (width > 16) {
        Ui_DrawTexturedRect8x8(x1 + 8, y1, width - 0x10, 8, D_10025D0);
        Ui_DrawTexturedRect8x8(x1 + 8, (y1 + height) - 8, width - 0x10, 8, D_1002650);
    }

    if (height > 16) {
        Ui_DrawTexturedRect8x8(x1, y1 + 8, 8, height - 0x10, D_10026D0);
        Ui_DrawTexturedRect8x8((x1 + width) - 8, y1 + 8, 8, height - 0x10, D_1002750);
    }
}

/** Draws a border in style B from 8x8 corner and edge textures. */
void Ui_DrawBorderStyleB(s32 x1, s32 y1, s32 width, s32 height) {
    Ui_DrawTexturedRect8x8(x1, y1, 8, 8, D_1002BD0);
    Ui_DrawTexturedRect8x8(x1, (y1 + height) - 8, 8, 8, D_1002C50);
    Ui_DrawTexturedRect8x8((x1 + width) - 8, (y1 + height) - 8, 8, 8, D_1002CD0);
    Ui_DrawTexturedRect8x8((x1 + width) - 8, y1, 8, 8, D_1002D50);

    if (width > 16) {
        Ui_DrawTexturedRect8x8(x1 + 8, y1, width - 0x10, 8, D_10029D0);
        Ui_DrawTexturedRect8x8(x1 + 8, (y1 + height) - 8, width - 0x10, 8, D_1002A50);
    }

    if (height > 16) {
        Ui_DrawTexturedRect8x8(x1, y1 + 8, 8, height - 0x10, D_1002AD0);
        Ui_DrawTexturedRect8x8((x1 + width) - 8, y1 + 8, 8, height - 0x10, D_1002B50);
    }
}

/** Draws a border in style C from 8x8 corner and edge textures. */
void Ui_DrawBorderStyleC(s32 x1, s32 y1, s32 width, s32 height) {
    Ui_DrawTexturedRect8x8(x1, y1, 8, 8, D_1002FD0);
    Ui_DrawTexturedRect8x8(x1, (y1 + height) - 8, 8, 8, D_1003050);
    Ui_DrawTexturedRect8x8((x1 + width) - 8, (y1 + height) - 8, 8, 8, D_10030D0);
    Ui_DrawTexturedRect8x8((x1 + width) - 8, y1, 8, 8, D_1003150);

    if (width > 16) {
        Ui_DrawTexturedRect8x8(x1 + 8, y1, width - 0x10, 8, D_1002DD0);
        Ui_DrawTexturedRect8x8(x1 + 8, (y1 + height) - 8, width - 0x10, 8, D_1002E50);
    }

    if (height > 16) {
        Ui_DrawTexturedRect8x8(x1, y1 + 8, 8, height - 0x10, D_1002ED0);
        Ui_DrawTexturedRect8x8((x1 + width) - 8, y1 + 8, 8, height - 0x10, D_1002F50);
    }
}

/** Fills an inset rectangle in style A with a color. */
void Ui_FillInsetRectangleA(s32 x1, s32 y1, s32 width, s32 height, u16 color) {
    gSPDisplayList(gDisplayListHead++, D_80060270);
    gDPSetFillColor(gDisplayListHead++, (color << 0x10) | color);

    if (StageContext_IsHighResolution() != 0) {
        gDPFillRectangle(gDisplayListHead++, x1 + 7, y1 + 7, (x1 + width) - 8, (y1 + height) - 8);
    } else {
        gDPFillRectangle(gDisplayListHead++, x1 + 3, y1 + 3, (x1 + width) - 4, (y1 + height) - 4);
    }
}

/** Fills an inset rectangle in style B with a color. */
void Ui_FillInsetRectangleB(s32 x1, s32 y1, s32 width, s32 height, u16 color) {
    gSPDisplayList(gDisplayListHead++, D_80060270);
    gDPSetFillColor(gDisplayListHead++, (color << 0x10) | color);

    if (StageContext_IsHighResolution() != 0) {
        gDPFillRectangle(gDisplayListHead++, x1 + 5, y1 + 5, (x1 + width) - 6, (y1 + height) - 6);
    } else {
        gDPFillRectangle(gDisplayListHead++, x1 + 3, y1 + 3, (x1 + width) - 4, (y1 + height) - 4);
    }
}

/** Draws a rectangle shaded from one color to another. */
void BattleHud_DrawGradientRect(s32 arg0, s32 arg1, s32 arg2, s32 arg3, Color_RGB8* arg4, Color_RGB8* arg5) {
    Vtx* temp_s2;
    DepthBuffer* temp_s1;
    Mtx* sp7C;
    Vp* sp78;

    temp_s1 = GfxImage_GetCurrent();
    temp_s2 = Gfx_AllocDisplayList(sizeof(Vtx) * 4);
    sp7C = Gfx_AllocDisplayList(sizeof(Mtx) * 1);
    sp78 = Gfx_AllocDisplayList(sizeof(Vp) * 1);
    Gfx_SetViewportDimensions(sp78, temp_s1->width, temp_s1->height);

    gSPViewport(gDisplayListHead++, (u32)sp78 & 0x1FFFFFFF);

    guOrtho(sp7C, 0.5f, temp_s1->width - 0.5f, temp_s1->height - 0.5f, 0.5f, -2.0f, 2.0f, 1.0f);
    Gfx_SetVertexAttributes(&temp_s2[0], arg0, arg1, -1, 0, 0, arg4->r, arg4->g, arg4->b, 0xFF);
    Gfx_SetVertexAttributes(&temp_s2[1], arg0 + arg2, arg1, -1, 0, 0, arg4->r, arg4->g, arg4->b, 0xFF);
    Gfx_SetVertexAttributes(&temp_s2[2], arg0, arg1 + arg3, -1, 0, 0, arg5->r, arg5->g, arg5->b, 0xFF);
    Gfx_SetVertexAttributes(&temp_s2[3], arg0 + arg2, arg1 + arg3, -1, 0, 0, arg5->r, arg5->g, arg5->b, 0xFF);

    gDPPipeSync(gDisplayListHead++);
    gDPSetCycleType(gDisplayListHead++, G_CYC_1CYCLE);
    gSPClearGeometryMode(gDisplayListHead++, G_ZBUFFER | G_LIGHTING);
    gDPSetCombineMode(gDisplayListHead++, G_CC_SHADE, G_CC_SHADE);
    gDPSetRenderMode(gDisplayListHead++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
    gSPPerspNormalize(gDisplayListHead++, 0xFFFF);
    gSPMatrix(gDisplayListHead++, (u32)sp7C & 0x1FFFFFFF, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    gSPMatrix(gDisplayListHead++, (u32)&gIdentityMtx & 0x1FFFFFFF, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPVertex(gDisplayListHead++, (u32)temp_s2 & 0x1FFFFFFF, 4, 0);
    gSP2Triangles(gDisplayListHead++, 0, 2, 3, 0, 0, 3, 1, 0);
}

/** Draws a bordered panel filled with a color. */
void Ui_DrawBorderedPanel(s32 x1, s32 y1, s32 width, s32 height, u16 color) {
    gSPDisplayList(gDisplayListHead++, gUiEnvTintTextureDL);

    if (StageContext_IsHighResolution() != 0) {
        Ui_DrawBorderStyleA(x1, y1, width, height);
    } else {
        Ui_DrawBorderStyleC(x1, y1, width, height);
    }

    if ((width >= 0xF) && (height >= 0xF)) {
        Ui_FillInsetRectangleA(x1, y1, width, height, color);
    }

    gSPDisplayList(gDisplayListHead++, gUiRestoreTextureDL);
}

/** Draws a bordered panel shaded from a top color to a bottom color. */
void Ui_DrawGradientPanel(s32 x1, s32 y1, s32 width, s32 height, Color_RGB8* top_color, Color_RGB8* bottom_color) {
    if ((width >= 0xF) && (height >= 0xF)) {
        if (StageContext_IsHighResolution() != 0) {
            func_8001DBB0(x1 + 6, y1 + 6, width - 0xC, height - 0xC, top_color, bottom_color);
        } else {
            func_8001DBB0(x1 + 2, y1 + 2, width - 4, height - 4, top_color, bottom_color);
        }
    }

    gSPDisplayList(gDisplayListHead++, gUiEnvTintTextureDL);

    if (StageContext_IsHighResolution() != 0) {
        Ui_DrawBorderStyleA(x1, y1, width, height);
    } else {
        Ui_DrawBorderStyleC(x1, y1, width, height);
    }

    gSPDisplayList(gDisplayListHead++, gUiRestoreTextureDL);
}

/** Draws a bordered panel in style B filled with a color. */
void Ui_DrawBorderedPanelStyleB(s32 x1, s32 y1, s32 width, s32 height, u16 color) {
    gSPDisplayList(gDisplayListHead++, gUiEnvTintTextureDL);

    if (StageContext_IsHighResolution() != 0) {
        Ui_DrawBorderStyleB(x1, y1, width, height);
    } else {
        Ui_DrawBorderStyleC(x1, y1, width, height);
    }

    if ((width >= 0xF) && (height >= 0xF)) {
        Ui_FillInsetRectangleB(x1, y1, width, height, color);
    }

    gSPDisplayList(gDisplayListHead++, gUiRestoreTextureDL);
}

extern Gfx D_800602C8[];
extern Gfx D_80060398[];
/**
 * Draws a 282x130 YUV image at (x + 6, y + 6) as 16x16 tiles (the last column and row
 * are cut to 10 and 2 pixels), then draws border style A around it.
 */
void func_8001E24C(s32 x, s32 y, u8* image) {
    s32 j;
    s32 i;
    s32 w;
    s32 h;
    s32 left;
    s32 top;
    s32 right;
    s32 bottom;

    gDPPipeSync(gDisplayListHead++);
    gDPSetCycleType(gDisplayListHead++, G_CYC_1CYCLE);
    gDPSetRenderMode(gDisplayListHead++, 0x0F0A4000, 0);
    gDPSetTexturePersp(gDisplayListHead++, G_TP_NONE);
    gDPSetCombine(gDisplayListHead++, 0x17FE2F, 0x77FCF87C);
    gDPSetTextureConvert(gDisplayListHead++, G_TC_CONV);
    gDPSetConvert(gDisplayListHead++, G_CV_K0, G_CV_K1, G_CV_K2, G_CV_K3, G_CV_K4, G_CV_K5);
    gDPPipeSync(gDisplayListHead++);

    for (i = 0; i < 0x90; i += 0x10) {
            h = 0x82 - i;
            if (h > 0x10) {
                h = 0x10;
            }
        for (j = 0; j < 0x120; j += 0x10) {
            w = 0x11A - j;
            if (w > 0x10) {
                w = 0x10;
            }
            left = (x + j + 6) << 2;
            top = (y + i + 6) << 2;
            right = (x + j + w + 6) << 2;
            bottom = (y + i + h + 6) << 2;
            gDPLoadTextureBlockYuv(gDisplayListHead++, image, G_IM_FMT_YUV, G_IM_SIZ_16b, 16, 16, 0,
                                G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK,
                                G_TX_NOLOD, G_TX_NOLOD);
            gSPTextureRectangle(gDisplayListHead++, left, top, right, bottom, G_TX_RENDERTILE, 0, 0, 0x0400, 0x0400);
            image += 0x200;
        }
    }

    gDPSetTextureConvert(gDisplayListHead++, G_TC_FILT);
    gSPDisplayList(gDisplayListHead++, D_800602C8);
    Ui_DrawBorderStyleA(x, y, 0x126, 0x8E);
    gSPDisplayList(gDisplayListHead++, D_80060398);
}

/** Draws a bordered panel without a fill. */
void Ui_DrawBorderedPanelNoFill(s32 x1, s32 y1, s32 width, s32 height) {
    gSPDisplayList(gDisplayListHead++, gUiEnvTintTextureDL);

    if (StageContext_IsHighResolution() != 0) {
        Ui_DrawBorderStyleA(x1, y1, width, height);
    } else {
        Ui_DrawBorderStyleC(x1, y1, width, height);
    }

    gSPDisplayList(gDisplayListHead++, gUiRestoreTextureDL);
}

extern Gfx D_80060308[];
extern u8 D_10031C0[];
extern u8 D_1003740[];
extern u8 D_1003880[];

/** Draws a small texture marker at a position. */
void Ui_DrawTextureMarker(s32 x, s32 y) {
    if (StageContext_IsHighResolution() != 0) {
        gSPDisplayList(gDisplayListHead++, D_80060290);
        Gfx_DrawTextureRgba16(x, y, 0x20, 0x16, D_10031C0, 0x20, 0x200000);
    } else {
        gSPDisplayList(gDisplayListHead++, D_80060308);
        Gfx_DrawTextureRgba16Ia8(x, y, 0xC, 0xA, D_1003740, D_1003880, 0x10, 0x100000);
    }

    gSPDisplayList(gDisplayListHead++, gUiRestoreTextureDL);
}

/** Draws a 20x20 icon at a position. */
void Ui_Draw20x20Icon(s32 arg0, s32 arg1, s32 arg2) {
    u8* var_t4;

    if (arg2 != 0) {
        var_t4 = D_2004320;
    } else {
        var_t4 = D_2004000;
    }

    gSPDisplayList(gDisplayListHead++, D_80060290);
    gDPLoadTextureBlock(gDisplayListHead++, var_t4, G_IM_FMT_RGBA, G_IM_SIZ_16b, 20, 20, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    gSPTextureRectangle(gDisplayListHead++, arg0 << 2, arg1 << 2, (arg0 + 0x13) << 2, (arg1 + 0x13) << 2,
                        G_TX_RENDERTILE, 0, 0, 0x1000, 0x0400);
    gSPDisplayList(gDisplayListHead++, gUiRestoreTextureDL);
}

extern u8 D_01003920[];
void func_8001E9A0(s32 arg0, s32 arg1) {
    s32 i;

    gSPDisplayList(gDisplayListHead++, D_80060290);
    gDPSetAlphaCompare(gDisplayListHead++, G_AC_NONE);

    for (i = 0; i < 22; i += 2) {
        gDPLoadTextureBlock(gDisplayListHead++, D_01003920 + i * 0x108, G_IM_FMT_RGBA, G_IM_SIZ_16b, 132, 2, 0,
                            G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK,
                            G_TX_NOLOD, G_TX_NOLOD);
        gSPTextureRectangle(gDisplayListHead++, arg0 << 2, (arg1 + i) << 2, (arg0 + 0x83) << 2,
                            (arg1 + 1 + i) << 2, G_TX_RENDERTILE, 0, 0, 0x1000, 0x0400);
    }

    gSPDisplayList(gDisplayListHead++, gUiRestoreTextureDL);
}

/*
 * BattleHud_DrawHpBarTexture  (src/ui_graphics.c)  -- 465 words
 *
 * Draws a horizontal bar built from 8x12-texel pieces at screen
 * position (arg0, arg1).
 *   arg2 = total bar width in pixels (the usable part is arg2 - 4),
 *   arg3 = current value, arg4 = maximum value.
 * `temp_lo` is the empty part's width and `sp1C` the filled part's width.
 * The fill texture depends on the ratio arg3/arg4:
 *   below 10/48 -> texture 0x01006B90, below 27/48 -> 0x01006AD0,
 *   otherwise   -> 0x01006A10  (color names unknown; check in game).
 * Pieces drawn: a left piece, a right piece, the filled part, the empty part.
 *
 * Origin: Stadium 1 BattleHud_DrawHpBarTexture (so the bar is probably an
 * HP-style gauge, inferred from that name only).  Zero compares with
 * `arg3 < (arg4 * 0xA) / 48` where Stadium 1 wrote `arg3 * 0x30 < arg4 * 0xA`.
 *
 * Verified: compiles with IDO 7.1 -O2 -mips2 (repo flags and headers) to the same words as the retail ROM, relocations compared by address.
 */
extern Gfx D_80060290[];            /* display list that sets up texture-rectangle drawing */
extern Gfx gUiRestoreTextureDL[];
/* segment-1 texture addresses; rename once the textures are identified */
extern u8 D_01006B90[];
extern u8 D_01006AD0[];
extern u8 D_01006A10[];
extern u8 D_010067D0[];
extern u8 D_01006890[];
extern u8 D_01006950[];

/** Draws the textured fill of an HP bar. */
void BattleHud_DrawHpBarTexture(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    u8* spDC;                 /* chosen fill texture */
    s32 spD8 = arg2 - 4;      /* usable width of the bar */
    /* empty part width = (max - current) / max * usable width */
    s32 temp_lo = ((arg4 - arg3) * (arg2 - 4)) / arg4;
    s32 sp1C =  /* filled part width, written as (arg2 - empty) - 4 to match retail */
        (arg2 - temp_lo) - 4;

    /* choose the fill texture from the fill ratio */
    if (arg3 < ((arg4 * 0xA) / 48)) {
        spDC = D_01006B90;
    } else if (arg3 < ((arg4 * 0x1B) / 48)) {
        spDC = D_01006AD0;
    } else {
        spDC = D_01006A10;
    }

    gSPDisplayList(gDisplayListHead++, D_80060290);

    /* left piece (1 pixel wide, 11 tall) */

    gDPLoadTextureBlock(gDisplayListHead++, D_010067D0, G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 12, 0,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                        G_TX_NOLOD);
    gSPTextureRectangle(gDisplayListHead++, arg0 << 2, arg1 << 2, (arg0 + 1) << 2, (arg1 + 0xB) << 2, G_TX_RENDERTILE,
                        0, 0, 0x1000, 0x0400);

    /* right piece, placed after the usable width */
    gDPLoadTextureBlock(gDisplayListHead++, D_01006890, G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 12, 0,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                        G_TX_NOLOD);
    gSPTextureRectangle(gDisplayListHead++, ((arg0 + spD8) + 2) << 2, arg1 << 2, ((arg0 + spD8) + 3) << 2,
                        (arg1 + 0xB) << 2, G_TX_RENDERTILE, 0, 0, 0x1000, 0x0400);

    /* filled part */
    if (sp1C > 0) {
        gDPLoadTextureBlock(gDisplayListHead++, spDC, G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 12, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                            G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        gSPTextureRectangle(gDisplayListHead++, (arg0 + 2) << 2, arg1 << 2, (arg0 + sp1C + 1) << 2, (arg1 + 0xB) << 2,
                            G_TX_RENDERTILE, 0, 0, 0, 0x0400);
    }

    /* empty part */
    if (temp_lo > 0) {
        gDPLoadTextureBlock(gDisplayListHead++, D_01006950, G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 12, 0,
                            G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK,
                            G_TX_NOLOD, G_TX_NOLOD);
        gSPTextureRectangle(gDisplayListHead++, ((arg0 + sp1C) + 2) << 2, arg1 << 2, ((arg0 + sp1C) + temp_lo + 1) << 2,
                            (arg1 + 0xB) << 2, G_TX_RENDERTILE, 0, 0, 0, 0x0400);
    }

    /* restore the previous render state */
    gSPDisplayList(gDisplayListHead++, gUiRestoreTextureDL);
}

/*
 * Widget_DrawMeterBar  (src/ui_graphics.c)  -- 451 words
 *
 * Draws a meter bar, 0x41 pixels wide and 5 tall, at screen position
 * (arg0, arg1) using 16-bit RGBA textures.
 *   arg2 = current value, arg3 = maximum value.
 * The bar is 48 pixels long: `temp_lo` pixels are drawn as the "empty" part and
 * `sp14` pixels as the "filled" part (sp14 = 48 - empty).  The fill color
 * depends on how full the bar is:
 *   below 10/48 of max -> texture 0x01006D90 (low),
 *   below 27/48 of max -> texture 0x01006D68 (medium),
 *   otherwise          -> texture 0x01006D40 (high).
 * (The color names are a guess from the thresholds - check them in game.)
 *
 * Origin: this is the Stadium 1 function Widget_DrawMeterBar (so the bar is
 * probably a HP-style gauge, but that is inferred from the name only).  Stadium 1 used a
 * single symbol for the first two colors; Zero has three distinct textures.
 *
 * Verified: compiles with IDO 7.1 -O2 -mips2 (repo flags and headers) to the same words as the retail ROM, relocations compared by address.
 */
extern Gfx gUiEnvTintTextureDL[];
extern Gfx gUiRestoreTextureDL[];
/* segment-1 texture addresses; rename once the textures are identified */
extern u8 D_01006D90[];
extern u8 D_01006D68[];
extern u8 D_01006D40[];
extern u8 D_01006C50[];
extern u8 D_01006CF0[];
extern u8 D_01006D18[];

/**
 * @unverified Name was previously used only by callers of this address; the definition was still func_.
 */
void Widget_DrawMeterBar(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    u8* spCC;  /* chosen fill texture */
    /* length of the empty part in pixels (0..48); arg3 is the maximum */
    s32 temp_lo = ((arg3 - arg2) * 0x30) / arg3;
    s32 sp14 = 0x30 - temp_lo;  /* length of the filled part, 0..48 pixels */

    /* pick the fill color from the fill ratio (integer math, as in retail) */
    if (arg2 < ((arg3 * 0xA) / 48)) {
        spCC = D_01006D90;
    } else if (arg2 < ((arg3 * 0x1B) / 48)) {
        spCC = D_01006D68;
    } else {
        spCC = D_01006D40;
    }

    /* set up the texture-rectangle render state */
    gSPDisplayList(gDisplayListHead++, gUiEnvTintTextureDL);

    /* 1) a 16x5-texel piece at the left, x .. x+0x10 */

    gDPLoadTextureBlock(gDisplayListHead++, D_01006C50, G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 5, 0,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                        G_TX_NOLOD);
    gSPTextureRectangle(gDisplayListHead++, arg0 << 2, arg1 << 2, (arg0 + 0x10) << 2, (arg1 + 5) << 2, G_TX_RENDERTILE,
                        0, 0, 0x0400, 0x0400);

    /* 2) a 4x5-texel piece drawn 1 pixel wide at x+0x40, just past the 48-pixel bar area x+0x10 .. x+0x40 */
    gDPLoadTextureBlock(gDisplayListHead++, D_01006CF0, G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 5, 0,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                        G_TX_NOLOD);
    gSPTextureRectangle(gDisplayListHead++, (arg0 + 0x40) << 2, arg1 << 2, (arg0 + 0x41) << 2, (arg1 + 5) << 2,
                        G_TX_RENDERTILE, 0, 0, 0x0400, 0x0400);

    /* 3) filled part of the bar, starting at x + 0x10 */
    if (sp14 > 0) {
        gDPLoadTextureBlock(gDisplayListHead++, spCC, G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 5, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                            G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        gSPTextureRectangle(gDisplayListHead++, (arg0 + 0x10) << 2, arg1 << 2, (arg0 + sp14 + 0x10) << 2,
                            (arg1 + 5) << 2, G_TX_RENDERTILE, 0, 0, 0, 0x0400);
    }

    /* 4) empty part of the bar, right after the filled part */
    if (temp_lo > 0) {
        gDPLoadTextureBlock(gDisplayListHead++, D_01006D18, G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 5, 0,
                            G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK,
                            G_TX_NOLOD, G_TX_NOLOD);
        gSPTextureRectangle(gDisplayListHead++, ((arg0 + sp14) + 0x10) << 2, arg1 << 2,
                            ((arg0 + sp14) + temp_lo + 0x10) << 2, (arg1 + 5) << 2, G_TX_RENDERTILE, 0, 0, 0, 0x0400);
    }

    /* put the render state back */
    gSPDisplayList(gDisplayListHead++, gUiRestoreTextureDL);
}
