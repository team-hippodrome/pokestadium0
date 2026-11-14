/* Stadium Zero fragment012_17ED00. */
/* C ported from the Stadium 1 decomp: src/fragments/battle_engine/battle_engine_2FA4D0.c, src/ui_graphics.c. */

#include "battle.h"
#include "fragments/party_summary/party_summary.h"
#include "gfx_buffer.h"
#include "graphics_textures.h"
#include "input.h"
#include "matrix.h"
#include "ui_graphics.h"

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

void BattleHud_DrawTranslucentShadowRect(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void Ui_DrawGradientRectangle(s32 x1, s32 y1, s32 width, s32 height, Color_RGB8* top_color,
                              Color_RGB8* bottom_color);

/**
 * Draws up to seven digits (and '-') of the string arg0 at (arg1, arg2) with the small 8x6
 * digit textures, stopping at the first space or the end.
 */
void func_82116480(s8* arg0, s16 arg1, s16 arg2) {
    u8** temp_s4;
    u8* var_v1;
    s32 i;
    s8 c;

    temp_s4 = Memmap_GetSegmentVaddr(D_300B870);

    gSPDisplayList(gDisplayListHead++, gUiEnvTintTextureDL);

    for (i = 0; i < 7; i++) {
        c = arg0[i];
        if ((c == ' ') || (c == 0)) {
            return;
        }
        switch (c) {
            case ' ':
                var_v1 = NULL;
                break;
            case 0:
                var_v1 = NULL;
                break;
            case '-':
                var_v1 = temp_s4[10];
                break;
            default:
                var_v1 = temp_s4[c - '0'];
                break;
        }

        if (var_v1 != NULL) {
            Gfx_DrawTextureRgba16(arg1, arg2, 8, 6, var_v1, 8, 0);
        }

        arg1 += 8;
    }

    gSPDisplayList(gDisplayListHead++, gUiRestoreTextureDL);
}

/**
 * Draws a translucent black rectangle at (arg0, arg1) of size arg2 x arg3 with vertex alpha
 * arg4, using a screen-space orthographic projection. The HUD boxes use it as a drop shadow.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (165 of the moves).
 * @unverified Name from Stadium 1.
 */
void BattleHud_DrawTranslucentShadowRect(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    GfxImage* temp_s1;
    Vtx* temp_s2;
    Mtx* sp84;
    Vp* sp80;

    temp_s1 = GfxImage_GetCurrent();
    temp_s2 = Gfx_AllocDisplayList(sizeof(Vtx) * 4);
    sp84 = Gfx_AllocDisplayList(sizeof(Mtx) * 1);
    sp80 = Gfx_AllocDisplayList(sizeof(Vp) * 1);
    Gfx_SetViewportDimensions(sp80, temp_s1->width, temp_s1->height);

    gSPViewport(gDisplayListHead++, (u32)sp80 & 0x1FFFFFFF);

    guOrtho(sp84, 0.5f, temp_s1->width - 0.5f, temp_s1->height - 0.5f, 0.5f, -2.0f, 2.0f, 1.0f);

    Gfx_SetVertexAttributes(&temp_s2[0], arg0, arg1, -1, 0, 0, 0, 0, 0, arg4);
    Gfx_SetVertexAttributes(&temp_s2[1], arg0 + arg2, arg1, -1, 0, 0, 0, 0, 0, arg4);
    Gfx_SetVertexAttributes(&temp_s2[2], arg0, arg1 + arg3, -1, 0, 0, 0, 0, 0, arg4);
    Gfx_SetVertexAttributes(&temp_s2[3], arg0 + arg2, arg1 + arg3, -1, 0, 0, 0, 0, 0, arg4);

    gDPPipeSync(gDisplayListHead++);
    gDPSetCycleType(gDisplayListHead++, G_CYC_1CYCLE);
    gSPClearGeometryMode(gDisplayListHead++, G_ZBUFFER | G_LIGHTING);
    gDPSetCombineMode(gDisplayListHead++, G_CC_SHADE, G_CC_SHADE);
    gDPSetRenderMode(gDisplayListHead++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    gSPPerspNormalize(gDisplayListHead++, 0xFFFF);
    gSPMatrix(gDisplayListHead++, (u32)sp84 & 0x1FFFFFFF, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    gSPMatrix(gDisplayListHead++, (u32)&gIdentityMtx & 0x1FFFFFFF, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPVertex(gDisplayListHead++, (u32)temp_s2 & 0x1FFFFFFF, 4, 0);
    gSP2Triangles(gDisplayListHead++, 0, 2, 3, 0, 0, 3, 1, 0);
}

/**
 * Draws an opaque rectangle that fades vertically from top_color to bottom_color, in screen
 * space.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (165 of the moves).
 * @unverified Name from Stadium 1.
 */
void Ui_DrawGradientRectangle(s32 x1, s32 y1, s32 width, s32 height, Color_RGB8* top_color,
                              Color_RGB8* bottom_color) {
    Vtx* temp_s2;
    GfxImage* temp_s1;
    Mtx* sp7C;
    Vp* sp78;

    temp_s1 = GfxImage_GetCurrent();
    temp_s2 = Gfx_AllocDisplayList(sizeof(Vtx) * 4);
    sp7C = Gfx_AllocDisplayList(sizeof(Mtx) * 1);
    sp78 = Gfx_AllocDisplayList(sizeof(Vp) * 1);

    Gfx_SetViewportDimensions(sp78, temp_s1->width, temp_s1->height);

    gSPViewport(gDisplayListHead++, (u32)sp78 & 0x1FFFFFFF);

    guOrtho(sp7C, 0.5f, temp_s1->width - 0.5f, temp_s1->height - 0.5f, 0.5f, -2.0f, 2.0f, 1.0f);
    Gfx_SetVertexAttributes(&temp_s2[0], x1, y1, -1, 0, 0, top_color->r, top_color->g, top_color->b, 0xFF);
    Gfx_SetVertexAttributes(&temp_s2[1], x1 + width, y1, -1, 0, 0, top_color->r, top_color->g, top_color->b, 0xFF);
    Gfx_SetVertexAttributes(&temp_s2[2], x1, y1 + height, -1, 0, 0, bottom_color->r, bottom_color->g,
                            bottom_color->b, 0xFF);
    Gfx_SetVertexAttributes(&temp_s2[3], x1 + width, y1 + height, -1, 0, 0, bottom_color->r, bottom_color->g,
                            bottom_color->b, 0xFF);

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

void func_8211694C(s32 arg0, s32 arg1, s32 arg2, s32 arg3, Color_RGB8* arg4, Color_RGB8* arg5);
/**
 * Calls func_8211694C with the same arguments (a gradient rectangle draw).
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (165 of the moves).
 * @unverified Name from Stadium 1.
 */
void Battle_DrawGradientRectWrapper(s32 arg0, s32 arg1, s32 arg2, s32 arg3, Color_RGB8* arg4, Color_RGB8* arg5) {
    func_8211694C(arg0, arg1, arg2, arg3, arg4, arg5);
}
