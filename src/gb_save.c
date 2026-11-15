/* Stadium Zero resident code. */
/* C ported from the Stadium 1 decomp: src/fragments/particle_math/particle_math_269820.c, src/gb_save.c. */

#include "gb_save.h"
#include "menu.h"
#include "pokemon_stats.h"

// Declared here instead of in a header: the callers of these disagree on their types.
s32 Window_DrawAnimatedFrame(Window* arg0);
s32 Ui_GetSelectionDirection(Controller* arg0);
s32 Ui_HandleHorizontalSelectionInput(UiSelection* arg0);
extern u32 D_8007360C[];
extern u8 pad_D_80075944[];

extern ParticleDescriptor gDefaultParticleDescriptor;

#include "m2c_macros.h"

void GbSave_BuildPortSummary(GbSavePortSummary* arg0, s32 arg1);
void Window_UpdateAndDrawFrame(Window* window);
s32 Ui_AdjustVerticalSelection(UiSelection* arg0, s32 arg1);
s32 Ui_HandleVerticalSelectionInput(s32 arg0);
s32 Ui_AdjustHorizontalSelection(UiSelection* arg0, s32 arg1);
s32 Ui_HandleHorizontalSelectionInput(UiSelection* arg0);
void Ui_AdjustSteppedScrollSelection(UiRangeValue* arg0);
s32 Ui_HandleNumericSelectionInput(UiNumberInput* arg0);
s32 Ui_AdjustSteppedRangeSelection(UiRangeValue* arg0);
s32 Ui_GetSelectionDirection(Controller* arg0);
Color_RGBA8 Color_InterpolateFromGray(Color_RGBA8 arg0, f32 arg1);

s32 Ui_AdjustNumericSelection(UiNumberInput* arg0, s32 arg1);
s32 Window_DrawAnimatedFrame(Window* arg0);
s32 Window_UpdateAnimation(Window* arg0);

void func_8001AA9C(u8, u8, u8, u8);
void func_8001AB6C(void);
void func_8001A384(s32, s32);
void Font_Printf(s32 x, s32 y, const char* fmt, ...);
void func_8001ABBC(void);
void Font_SetLineHeight(s32 arg0);
void func_8001ABE8(void);
void func_8001AAE4(u8, u8, u8, u8);
void func_8001AC3C(void);
extern Color_RGBA8 D_800734A8[2];
extern Color_RGBA8 D_800734B0[2];
extern Color_RGBA8 D_800734B8[2];
/**
 * Sets the text color from the row flags: 0x18 selected, 0x1 alternate, otherwise
 * normal. Each is a pair of colors; without flag 0x2 the second one is used.
 * Seen in play (2026-11-13) (menu tour from the main menu): called on every menu screen past the
 * main menu (Pokédex, party, Lab list, sort and PC, registration), with flags 2 and 0; it
 * returned pointers into the color table at 0x800734A8.
 * @unverified Name and comment guessed from the code.
 */
void Font_SetColorForFlags(s32 arg0) {
    Color_RGBA8* color;

    if (arg0 & 0x18) {
        color = D_800734B8;
    } else if (arg0 & 1) {
        color = D_800734B0;
    } else {
        color = D_800734A8;
    }
    if (!(arg0 & 2)) {
        color++;
    }
    func_8001AA9C(color->r, color->g, color->b, color->a);
}

extern s8 D_800734C0;
/**
 * Sets the text (environment) color for a menu item from its `flags`: disabled (0x18), highlighted
 * (1) or normal, each in a bright and a dim variant (bit 1). Same as Font_SetColorForFlags except that
 * flag 1 picks D_800734C0 here and D_800734B0 there.
 * @unverified Name read from the code; Free Battle setup uses it for its cup rows.
 */
void Ui_SetTextColorForFlags(s32 flags) {
    u8* entry;

    if (flags & 0x18) {
        entry = (u8*)&D_800734B8;
    } else if (flags & 1) {
        entry = (u8*)&D_800734C0;
    } else {
        entry = (u8*)&D_800734A8;
    }
    if (!(flags & 2)) {
        entry += 4;
    }
    func_8001AA9C(entry[0], entry[1], entry[2], entry[3]);
}

/**
 * Builds the display summary of a port's Game Boy save, or clears it when no
 * save is present.
 */
void GbSave_BuildPortSummary(GbSavePortSummary* arg0, s32 arg1) {
    if (GbSave_GetSaveState(arg1) != 0) {
        arg0->isUnavailable = 1;
    } else {
        arg0->isUnavailable = 0;
        arg0->trainerId = GbSave_GetTrainerId(arg1);
        GbSave_GetPlayerName(arg1, &arg0[1]);
    }
    arg0->gameType = GbSave_GetPortGame(arg1);
}

typedef struct GbSaveSummary {
    /* 0x00 */ s32 state;
    /* 0x04 */ s32 game;
    /* 0x08 */ s32 trainerId;
    /* 0x0C */ char name[1];
} GbSaveSummary;

extern Gfx D_80060270[];
extern Gfx D_80073408[];
extern Gfx D_80073438[];
extern Gfx D_80073450[];
extern Color_RGBA8 D_800734C8[];
extern Color_RGBA8 D_800734D8;
extern Color_RGBA8 D_800734DC;
extern u8* D_800734E0[];
extern char D_8007B8E0[];
extern u8 D_0400DFB8[];
extern u8 D_0400EB90[];
extern u8 D_0400FB80[];
extern u8 D_04010918[];
void Ui_FillRectRgba5551(s32 arg0, s32 arg1, s32 arg2, s32 arg3, Color_RGBA8 arg4);
s32 GbSave_GameToCategoryIndex(s32 arg0);
void Font_DrawCharAt(s32 x, s32 y, s32 chr);
void Ui_DrawNumberZeroPadded(s32 x, s32 y, s32 value, s32 digits);
u32 func_800566BC(s32);

/**
 * Draws a save summary bar at `y`, colored by the summary's game, with `label`.
 * Seen in play (2026-11-13) ran on the Pokédex, party and list screens, which all show the 1P サトシ
 * IDNo/12345 bar at the top.
 */
void GbSave_DrawSummaryBar(s32 y, GbSaveSummary* summary, char* label, s32 arg3) {
    if (summary != NULL) {
        gSPDisplayList(gDisplayListHead++, D_80060270);
        Ui_FillRectRgba5551(0, y, 392, 54, D_800734C8[GbSave_GameToCategoryIndex(summary->game)]);
    } else {
        gSPDisplayList(gDisplayListHead++, D_80060270);
        Ui_FillRectRgba5551(0, y, 392, 54, D_800734D8);
    }

    gDPPipeSync(gDisplayListHead++);
    gDPSetCycleType(gDisplayListHead++, G_CYC_1CYCLE);
    gDPSetTexturePersp(gDisplayListHead++, G_TP_NONE);
    gDPSetTextureFilter(gDisplayListHead++, G_TF_POINT);
    gDPSetCombineMode(gDisplayListHead++, G_CC_DECALRGBA, G_CC_DECALRGBA);
    gDPSetRenderMode(gDisplayListHead++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
    gDPLoadTextureBlock(gDisplayListHead++, D_0400DFB8, G_IM_FMT_IA, G_IM_SIZ_8b, 32, 54, 0, G_TX_NOMIRROR | G_TX_WRAP,
                        G_TX_NOMIRROR | G_TX_WRAP, 5, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    gSPScisTextureRectangle(gDisplayListHead++, 391 << 2, y << 2, 640 << 2, (y + 54) << 2, G_TX_RENDERTILE, 0, 0, 1 << 10,
                            1 << 10);

    gDPPipeSync(gDisplayListHead++);
    gDPSetRenderMode(gDisplayListHead++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    gDPLoadTextureBlock(gDisplayListHead++, D_0400EB90, G_IM_FMT_IA, G_IM_SIZ_8b, 80, 51, 0, G_TX_NOMIRROR | G_TX_WRAP,
                        G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    gSPScisTextureRectangle(gDisplayListHead++, 315 << 2, y << 2, 391 << 2, (y + 51) << 2, G_TX_RENDERTILE, 0, 0, 1 << 10,
                            1 << 10);
    gDPLoadTextureBlock(gDisplayListHead++, D_0400FB80, G_IM_FMT_IA, G_IM_SIZ_8b, 80, 3, 0, G_TX_NOMIRROR | G_TX_WRAP,
                        G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    gSPScisTextureRectangle(gDisplayListHead++, 315 << 2, (y + 51) << 2, 391 << 2, (y + 54) << 2, G_TX_RENDERTILE, 0, 0,
                            1 << 10, 1 << 10);
    gSPDisplayList(gDisplayListHead++, D_80060270);
    Ui_FillRectRgba5551(0, y + 54, 640, 2, D_800734DC);

    if (summary != NULL) {
        func_8001AB6C();
        func_8001A384(8, 0);
        func_8001AA9C(((u8*)&D_800734A8)[0], ((u8*)&D_800734A8)[1], ((u8*)&D_800734A8)[2], ((u8*)&D_800734A8)[3]);
        Font_DrawCharAt(74, (y + 32), arg3 + 0x31); // '1' + player
        Font_DrawCharAt(94, (y + 32), 0x50); // 'P'
        Font_Printf(134, (y + 32), (s32)((summary->state == 0) ? summary->name : D_8007B8E0));
        func_8001ABBC();

        gSPDisplayList(gDisplayListHead++, D_80073450);
        gDPLoadTextureBlock(gDisplayListHead++, D_04010918, G_IM_FMT_IA, G_IM_SIZ_8b, 40, 10, 0, G_TX_NOMIRROR | G_TX_WRAP,
                            G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        gSPScisTextureRectangle(gDisplayListHead++, 255 << 2, (y + 41) << 2, 295 << 2, (y + 51) << 2, G_TX_RENDERTILE, 0,
                                0, 1 << 10, 1 << 10);
        if (summary->state == 0) {
            Ui_DrawNumberZeroPadded(298, y + 39, summary->trainerId, 5);
        }
        gSPDisplayList(gDisplayListHead++, D_80073408);
        gDPLoadTextureBlock(gDisplayListHead++, D_800734E0[GbSave_GameToCategoryIndex(summary->game)], G_IM_FMT_RGBA,
                            G_IM_SIZ_16b, 20, 20, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK,
                            G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        gSPScisTextureRectangle(gDisplayListHead++, 54 << 2, (y + 32) << 2, 73 << 2, (y + 51) << 2, G_TX_RENDERTILE, 0, 0,
                                4 << 10, 1 << 10);
        gSPDisplayList(gDisplayListHead++, D_80073438);
    }

    func_8001AB6C();
    func_8001A384(8, 0);
    func_8001AA9C(((u8*)&D_800734A8)[0], ((u8*)&D_800734A8)[1], ((u8*)&D_800734A8)[2], ((u8*)&D_800734A8)[3]);
    Font_Printf(596 - ((func_800566BC((s32)label) * 20) >> 1), (y + 32), (s32)label);
    func_8001ABBC();
}

/**
 * Loads an 8-bit texture block of `width` x `height` in format `fmt`.
 * Seen in play (2026-11-13) (menu tour from the main menu): called on the main menu and every menu
 * screen after it, loading 8x8 textures 0x04010C60 and 0x04010D38.
 * @unverified Name and comment guessed from the code.
 */
void Gfx_LoadTextureBlock8b(s32 width, s32 height, void* texture, s32 fmt) {
    gDPLoadTextureBlock(gDisplayListHead++, texture, fmt, G_IM_SIZ_8b, width, height, 0, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
}

/**
 * Loads a 16-bit texture block of `width` x `height` in format `fmt`.
 * Not reached in play (2026-11-13): did not run in a tour of the main menu, Pokédex, party, Lab,
 * registration, Free Battle setup and a COM battle (opening, a switch, running, a Pound turn).
 * @unverified Name and comment guessed from the code.
 */
void Gfx_LoadTextureBlock16b(s32 width, s32 height, void* texture, s32 fmt) {
    gDPLoadTextureBlock(gDisplayListHead++, texture, fmt, G_IM_SIZ_16b, width, height, 0, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
}

/** Draws a solid-colored rectangle. */
void Trade_DrawSolidFillRect(s32 arg0, s32 arg1, s32 arg2, s32 arg3, Color_RGB8 arg4) {
    s32 color = RGBA5551(arg4.r, arg4.g, arg4.b, 1);

    gDPPipeSync(gDisplayListHead++);
    gDPSetFillColor(gDisplayListHead++, (color << 0x10) | color);
    gDPFillRectangle(gDisplayListHead++, arg0, arg1, (arg0 + arg2) - 1, (arg1 + arg3) - 1);
}

/**
 * Fills a rectangle (x, y, w, h) with an RGBA5551 fill color made from arg4.
 * Seen in play (2026-11-13) (menu tour from the main menu): called on every menu screen past the
 * main menu, as (0, 0, 392, 54) for the header strip and (0, 54, 640, 2) for the line under it.
 * @unverified Name and comment guessed from the code.
 */
void Ui_FillRectRgba5551(s32 arg0, s32 arg1, s32 arg2, s32 arg3, Color_RGBA8 arg4) {
    s32 color = RGBA5551(arg4.r, arg4.g, arg4.b, 1);

    gDPPipeSync(gDisplayListHead++);
    gDPSetFillColor(gDisplayListHead++, (color << 0x10) | color);
    gDPScisFillRectangle(gDisplayListHead++, arg0, arg1, (arg0 + arg2) - 1, (arg1 + arg3) - 1);
}

/**
 * Fills a rectangle (x, y, w, h) using a primitive color.
 * Seen in play (2026-11-13) (menu tour from the main menu): called on the main menu and every menu
 * screen after it, as (451, 84, 104, 4) and (451, 84, 4, 68). Stubbing it on the main menu turned
 * the colored tile panels gray.
 * @unverified Name and comment guessed from the code.
 */
void Ui_FillRectPrimColor(s32 arg0, s32 arg1, s32 arg2, s32 arg3, Color_RGBA8 color) {
    gDPPipeSync(gDisplayListHead++);
    gDPSetPrimColor(gDisplayListHead++, 0, 0, color.r, color.g, color.b, color.a);
    gDPFillRectangle(gDisplayListHead++, arg0, arg1, arg0 + arg2, arg1 + arg3);
}

typedef void (*GbTexLoadFunc4)(s32, s32, u8*, s32);
extern GbTexLoadFunc4 D_800734F0[];
/**
 * Draws a hollow frame from four 8x8 edge textures (top, right, bottom, left).
 * w and h are clamped to at least 16.
 *
 * The two `8U` subtractions are deliberate: the target computes (x2 - 8) and (y2 - 8)
 * afresh in the following rectangle instead of reusing them, which IDO only does when
 * the two occurrences differ in signedness.
 * Seen in play (2026-11-13) (menu tour from the main menu): called on the main menu and every menu
 * screen after it, as (445, 78, 116, 112) and (79, 202, 116, 112).
 * @unverified Name guessed from the code; comment kept.
 */
void Ui_DrawTexturedFrame(s32 x, s32 y, s32 w, s32 h, FrameTextures* arg4) {
    GbTexLoadFunc4 load;
    s32 x2;
    s32 y2;
    s32 y8;

    if (w < 0x10) {
        w = 0x10;
    }
    if (h < 0x10) {
        h = 0x10;
    }
    x2 = x + w;
    y2 = y + h;
    y8 = (y + 8) << 2;
    load = D_800734F0[arg4->format];
    load(8, 8, arg4->top, arg4->loadArg);
    gSPTextureRectangle(gDisplayListHead++, x << 2, y << 2, (x2 - 8U) << 2, y8, G_TX_RENDERTILE, 0, 0, 0x400, 0x400); // FAKE: 8U
    load(8, 8, arg4->right, arg4->loadArg);
    gSPTextureRectangle(gDisplayListHead++, (x2 - 8) << 2, y << 2, x2 << 2, (y2 - 8U) << 2, G_TX_RENDERTILE, 0, 0, 0x400, 0x400); // FAKE: 8U
    load(8, 8, arg4->bottom, arg4->loadArg);
    gSPTextureRectangle(gDisplayListHead++, (x + 8) << 2, (y2 - 8) << 2, x2 << 2, y2 << 2, G_TX_RENDERTILE, (w * -0x20) + 0x200, 0, 0x400, 0x400);
    load(8, 8, arg4->left, arg4->loadArg);
    gSPTextureRectangle(gDisplayListHead++, x << 2, y8, (x + 8) << 2, y2 << 2, G_TX_RENDERTILE, 0, (h * -0x20) + 0x200, 0x400, 0x400);
}

extern Gfx D_80073450[];
void Ui_DrawTexturedFrame(s32, s32, s32, s32, FrameTextures*);

/**
 * Appends a call of display list D_80073450 and a gDPSetCombineMode(
 * G_CC_DECALRGBA, G_CC_DECALRGBA) to the current display list, then forwards
 * all five arguments unchanged to Ui_DrawTexturedFrame.
 * Seen in play (2026-11-13) (menu tour from the main menu): called on every menu screen past the
 * main menu, at (54, 87).
 * @unverified Name guessed from the code; comment kept.
 */
void Ui_DrawTexturedFrameDecal(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8* arg4) {
    gSPDisplayList(gDisplayListHead++, D_80073450);
    gDPSetCombineMode(gDisplayListHead++, G_CC_DECALRGBA, G_CC_DECALRGBA);
    Ui_DrawTexturedFrame(arg0, arg1, arg2, arg3, arg4);
}

typedef void (*GbTexLoadFunc)(s32, s32, u8*, s32);
extern GbTexLoadFunc D_80073500[];
extern Gfx D_80073450[];

/**
 * Draws a horizontal frame edge of width w (at least 16) at (x, y): an 8x8 texture
 * stretched over all but the last 8 pixels, then an 8x8 end cap. The two textures come
 * from arg3 + 0x10 and arg3 + 0x14, and are loaded through D_80073500[arg3 + 4].
 * Seen in play (2026-11-13) (menu tour from the main menu): called on every menu screen past the
 * main menu, as (54, 176, width 532).
 * @unverified Name guessed from the code; comment kept.
 */
void Ui_DrawTexturedDivider(s32 x, s32 y, s32 w, FrameTextures* arg3) {
    GbTexLoadFunc load;
    s32 pad[2]; // FAKE
    s32 x2;
    s32 y8;

    if (w < 0x10) {
        w = 0x10;
    }
    x2 = x + w;
    y8 = (y + 8) << 2;
    load = D_80073500[arg3->format];
    gSPDisplayList(gDisplayListHead++, D_80073450);
    gDPSetCombineMode(gDisplayListHead++, G_CC_DECALRGBA, G_CC_DECALRGBA);
    load(8, 8, arg3->bottom, arg3->loadArg);
    gSPTextureRectangle(gDisplayListHead++, x << 2, y << 2, (x2 - 8) << 2, y8, G_TX_RENDERTILE, 0, 0, 0x400, 0x400);
    load(8, 8, arg3->right, arg3->loadArg);
    gSPTextureRectangle(gDisplayListHead++, (x2 - 8) << 2, y << 2, x2 << 2, y8, G_TX_RENDERTILE, 0, 0, 0x400, 0x400);
}

extern GbTexLoadFunc D_80073510[];

/**
 * Draws the 8x8 top-left and bottom-left corner tiles of a frame at (x, y) with height `h`
 * (at least 16), using the loader that matches the frame textures' format.
 * @unverified Name read from the code.
 */
void Ui_DrawFrameLeftCorners(s32 x, s32 y, s32 h, FrameTextures* frame) {
    GbTexLoadFunc load;
    s32 pad[2]; // FAKE
    s32 y2;
    s32 x8;

    if (h < 0x10) {
        h = 0x10;
    }
    y2 = y + h;
    x8 = (x + 8) << 2;
    load = D_80073510[frame->format];
    gSPDisplayList(gDisplayListHead++, D_80073450);
    gDPSetCombineMode(gDisplayListHead++, G_CC_DECALRGBA, G_CC_DECALRGBA);
    load(8, 8, frame->top, frame->loadArg);
    gSPTextureRectangle(gDisplayListHead++, x << 2, y << 2, x8, (y2 - 8) << 2, G_TX_RENDERTILE, 0, 0, 0x400, 0x400);
    load(8, 8, frame->left, frame->loadArg);
    gSPTextureRectangle(gDisplayListHead++, x << 2, (y2 - 8) << 2, x8, y2 << 2, G_TX_RENDERTILE, 0, 0, 0x400, 0x400);
}

extern u8 D_04009E98[];
extern u8 D_04009EE0[];
extern u8 D_04009F28[];
extern u8 D_04009F70[];
/**
 * Draws a hollow frame in a flat color from the four 8x8 edge textures at
 * D_04009E98 (top), D_04009F70 (right), D_04009F28 (bottom) and D_04009EE0 (left).
 * w and h are clamped to at least 16.
 *
 * y8 is taken before the clamps and x2/y2 after them: that keeps the first basic
 * block at the size the target has. The right and bottom edges are written out as
 * x + w and y + h where the target evaluates them again.
 * Seen in play (2026-11-12) in いちらん: drew the yellow row cursor at (82, 152), size 80 x
 * 20, for LabPCList_DrawRowCursor.
 */
void Ui_DrawRoundedFrame(s32 x, s32 y, s32 w, s32 h, Color_RGBA8 color) {
    s32 x2;
    s32 y2;
    s32 y8;

    y8 = (y + 8) << 2;
    if (w < 0x10) {
        w = 0x10;
    }
    if (h < 0x10) {
        h = 0x10;
    }
    x2 = x + w;
    y2 = y + h;
    gSPDisplayList(gDisplayListHead++, D_80073450);
    gDPSetCombineLERP(gDisplayListHead++, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, TEXEL0);
    gDPSetPrimColor(gDisplayListHead++, 0, 0, color.r, color.g, color.b, color.a);
    gDPLoadTextureBlock(gDisplayListHead++, D_04009E98, G_IM_FMT_IA, G_IM_SIZ_8b, 8, 8, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    gSPTextureRectangle(gDisplayListHead++, x << 2, y << 2, (x + w - 8) << 2, y8, G_TX_RENDERTILE, 0, 0, 0x400, 0x400);
    gDPLoadTextureBlock(gDisplayListHead++, D_04009F70, G_IM_FMT_IA, G_IM_SIZ_8b, 8, 8, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    gSPTextureRectangle(gDisplayListHead++, (x2 - 8U) << 2, y << 2, x2 << 2, (y + h - 8) << 2, G_TX_RENDERTILE, 0, 0, 0x400, 0x400); // FAKE: 8U keeps x2 - 8 apart from the one above
    gDPLoadTextureBlock(gDisplayListHead++, D_04009F28, G_IM_FMT_IA, G_IM_SIZ_8b, 8, 8, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    gSPTextureRectangle(gDisplayListHead++, (x + 8) << 2, (y + h - 8U) << 2, x2 << 2, y2 << 2, G_TX_RENDERTILE, (w * -0x20) + 0x200, 0, 0x400, 0x400); // FAKE: 8U, as above
    gDPLoadTextureBlock(gDisplayListHead++, D_04009EE0, G_IM_FMT_IA, G_IM_SIZ_8b, 8, 8, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    gSPTextureRectangle(gDisplayListHead++, x << 2, y8, (x + 8) << 2, y2 << 2, G_TX_RENDERTILE, 0, (h * -0x20) + 0x200, 0x400, 0x400);
}

typedef struct Color8002A354 {
    u8 c[4];
} Color8002A354;
extern Gfx D_80060270[];
void func_80029028(s32, s32, s32, s32, Color8002A354);
/**
 * Fills a rectangle with `color` brightened by 1.4 (alpha kept), used for the selected-row highlight.
 * Seen in play (2026-11-13) (menu tour from the main menu): called on the party, Pokédex, Lab list,
 * sort and PC screens, for the selected row (for example (56, 137, 527, 45) on the party screen).
 * @unverified Name and comment guessed from the code.
 */
void Ui_FillRectHighlighted(s32 arg0, s32 arg1, s32 arg2, s32 arg3, Color_RGBA8 color) {
    Color_RGBA8 light;

    light.r = color.r * 1.4;
    light.g = color.g * 1.4;
    light.b = color.b * 1.4;
    light.a = color.a;
    gSPDisplayList(gDisplayListHead++, D_80060270);
    func_80029028(arg0, arg1, arg2, arg3, *(Color8002A354*)&light);
}

extern u8 D_80073524[];
void Ui_DrawTexturedFrameDecal(s32, s32, s32, s32, u8*);
/**
 * Draws the textured border of a label box at (x, y), size (w, h), with the frame textures D_80073524.
 * Seen in play (2026-11-14): Window_DrawLabeled draws the main menu's small label boxes with it.
 */
void Ui_DrawLabelFrame(s32 x, s32 y, s32 w, s32 h) {
    Ui_DrawTexturedFrameDecal(x, y, w, h, D_80073524);
}

extern u8 D_8007353C[];
void Ui_DrawTexturedFrameDecal(s32, s32, s32, s32, u8*);
/**
 * Fills a box at (x, y), size (w, h) with `color` and draws its textured border.
 * @unverified Name read from the code; the Lab PC terminal uses it.
 */
void Ui_DrawFilledFrame(s32 x, s32 y, s32 w, s32 h, Color8002A354 color) {
    gSPDisplayList(gDisplayListHead++, D_80060270);
    func_80029028(x + 1, y + 1, w - 2, h - 2, color);
    Ui_DrawTexturedFrameDecal(x, y, w, h, D_8007353C);
}

typedef struct Img8002A3F8 {
    /* 0x00 */ s32 stride;
    /* 0x04 */ s32 height;
    /* 0x08 */ s32 width;
    /* 0x0C */ u8 *pixels;
} Img8002A3F8;
extern Gfx D_80073408[];
extern Gfx D_80073438[];
void func_8001B884(s32, s32, s32, s32, u8*, s32, s32);
/**
 * Draws an RGBA16 image at (x, y) in horizontal strips that fit the 4 KB texture memory.
 * Seen in play (2026-11-13) (menu tour from the main menu): called in the Lab list, the Pokédex and
 * registration (image 0x800828D0 at (59, 118) in registration).
 * @unverified Name and comment guessed from the code.
 */
void Ui_DrawImageInStrips(Img8002A3F8 *arg0, s32 x, s32 y) {
    s32 stride;
    s32 rows;
    s32 max_rows;
    u8 *pixels;
    s32 n;
    s32 cur_y;

    gSPDisplayList(gDisplayListHead++, D_80073408);
    stride = arg0->stride;
    max_rows = 0x1000 / (stride * 2);
    rows = arg0->height;
    pixels = arg0->pixels;
    cur_y = y;
    while (rows > 0) {
        if (max_rows < rows) {
            n = max_rows;
        } else {
            n = rows;
        }
        func_8001B884(x, cur_y, arg0->width, n, pixels, stride, 0x200000);
        stride = arg0->stride;
        rows -= n;
        cur_y += n;
        pixels += n * stride * 2;
    }
    gSPDisplayList(gDisplayListHead++, D_80073438);
}

extern u8 D_04000008[];
/**
 * Fills a rectangle with the primitive and environment colors; opaque when prim alpha is 255, translucent otherwise.
 * Seen in play (2026-11-13) (menu tour from the main menu): called on every menu screen past the
 * main menu, for the info panel (for example (342, 114, 248, 104) in the Pokédex).
 * @unverified Name and comment guessed from the code.
 */
void Ui_FillRectPrimEnvColor(s32 x, s32 y, s32 w, s32 h, Color_RGBA8 prim, Color_RGBA8 env) {
    gDPPipeSync(gDisplayListHead++);
    gDPSetCycleType(gDisplayListHead++, G_CYC_1CYCLE);
    if (prim.a == 255) {
        gDPSetRenderMode(gDisplayListHead++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
    } else {
        gDPSetRenderMode(gDisplayListHead++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    }
    gDPSetCombineLERP(gDisplayListHead++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, PRIMITIVE, PRIMITIVE,
                      ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, PRIMITIVE);
    gDPSetTexturePersp(gDisplayListHead++, G_TP_NONE);
    gDPSetTextureFilter(gDisplayListHead++, G_TF_BILERP);
    gDPSetPrimColor(gDisplayListHead++, 0, 0, prim.r, prim.g, prim.b, prim.a);
    gDPSetEnvColor(gDisplayListHead++, env.r, env.g, env.b, env.a);
    gDPLoadTextureBlock(gDisplayListHead++, D_04000008, G_IM_FMT_I, G_IM_SIZ_8b, 64, 64, 0, G_TX_NOMIRROR | G_TX_WRAP,
                        G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    gSPTextureRectangle(gDisplayListHead++, x << 2, y << 2, (x + w) << 2, (y + h) << 2, G_TX_RENDERTILE, 0, 0,
                        (64 << 10) / w, (64 << 10) / h);
}

/**
 * Sets a window's x, y, width and height and clears its state word (+0x10).
 * Seen in play (2026-11-13) (menu tour from the main menu): called on every menu screen past the
 * main menu, for example (54, 87, width 532).
 * @unverified Name and comment guessed from the code.
 */
void Window_SetRect(s32* arg0, s32 x, s32 y, s32 w, s32 h) {
    arg0[0] = x;
    arg0[1] = y;
    arg0[2] = w;
    arg0[3] = h;
    arg0[4] = 0;
}

extern Gfx D_80073480[];
extern u8 D_800735C4[];
extern u8 D_800735DC[];

/**
 * Draws a window's frame and fill from its rect, flags and color; width and height are at least 16.
 * Seen in play (2026-11-13) (menu tour from the main menu): called in the Lab list, sort and PC
 * screens.
 * @unverified Name and comment guessed from the code.
 */
void Window_DrawFrame(s32* arg0) {
    UNUSED s32 pad1; // FAKE: unused locals that only pad the stack frame
    UNUSED s32 pad2; // FAKE
    UNUSED s32 pad3; // FAKE
    UNUSED s32 pad4; // FAKE
    s32 x;
    s32 y;
    s32 w;
    s32 h;
    s32 x2;
    s32 y2;
    s32 w2;
    s32 h2;
    Color_RGBA8* color = (Color_RGBA8*)&arg0[6];

    w = (arg0[2] < 0x10) ? 0x10 : arg0[2];
    h = (arg0[3] < 0x10) ? 0x10 : arg0[3];
    x = arg0[0];
    y = arg0[1];
    if (!(arg0[5] & 1)) {
        if (arg0[5] & 0x18) {
            x2 = x + 2;
            w2 = w - 4;
            y2 = y + 2;
            h2 = h - 4;
        } else {
            x2 = x;
            y2 = y;
            w2 = w;
            h2 = h;
        }
        if ((arg0[5] & 2) && (arg0[5] & 4)) {
            Ui_FillRectPrimEnvColor(x, y, w, h, *(Color_RGBA8*)&arg0[6], *(Color_RGBA8*)&arg0[7]);
        } else {
            if (color->a == 0xFF) {
                gSPDisplayList(gDisplayListHead++, D_80060270);
                func_80029028(x2, y2, w2, h2, *(Color8002A354*)color);
            } else {
                gSPDisplayList(gDisplayListHead++, D_80073480);
                Ui_FillRectPrimColor(x2, y2, w2, h2, *color);
            }
        }
    }
    if (arg0[5] & 8) {
        Ui_DrawTexturedFrameDecal(x, y, w, h, D_800735DC);
    } else if (arg0[5] & 0x10) {
        Ui_DrawTexturedFrameDecal(x, y, w, h, D_800735C4);
    }
}

M2C_UNK Audio_PlaySystemSound();

/**
 * Steps the open/close animation of a window: animTimer 0-3 opening (state 0, plays sound 4 at 0), 4-5 state 1,
 * 6 open (state 2, holds); a close starts at 7 (state 3) and ends at 11 (state 4, closed).
 * Returns 1 unless the window is (nearly) open, so callers draw what is under it.
 * @unverified Read from the code; the timer values match the Window.animTimer play note.
 */
s32 Window_UpdateAnimation(Window* arg0) {
    s32 var_v1;
    s32 var_v0;

    var_v0 = arg0->animTimer;
    var_v1 = 1;
    if (var_v0 >= 11) {
        arg0->state = 4;
        return 1;
    }
    if (var_v0 >= 7) {
        arg0->state = 3;
        arg0->animTimer = (s32) (var_v0 + 1);
    } else if (var_v0 < 4) {
        if (var_v0 == 0) {
            Audio_PlaySystemSound(4, arg0);
            var_v1 = 1;
            var_v0 = arg0->animTimer;
        }
        arg0->state = 0;
        arg0->animTimer = (s32) (var_v0 + 1);
    } else {
        var_v1 = 0;
        if (var_v0 < 6) {
            arg0->state = 1;
            arg0->animTimer = (s32) (var_v0 + 1);
        } else {
            arg0->state = 2;
        }
    }
    return var_v1;
}

extern u8 D_80073554[];
void Window_DrawTitleTab(s32, s32, s32, s32);
void Window_DrawHeaderStripe(); // no prototype: callers pass a fourth argument the definition ignores

/**
 * Draws a window's frame, scaled from 16x16 up to its size while it opens (state 0) and back down
 * while it closes (state 3), with the fill, title tab (style 0x800) and 0x1000 decoration.
 * Returns 0 once the window is open (states 1 and 2), so callers draw the contents only then.
 * @unverified Read from the code.
 */
s32 Window_DrawAnimatedFrame(Window* arg0) {
    UNUSED s32 pad1; // FAKE: unused locals that only pad the stack frame
    UNUSED s32 pad2; // FAKE
    UNUSED s32 pad3; // FAKE
    UNUSED s32 pad4; // FAKE
    s32 x;
    s32 y;
    s32 w;
    s32 h;
    s32 ret;
    s32 max_w;
    s32 max_h;
    s32 t;

    max_w = (arg0->frame.width < 0x10) ? 0x10 : arg0->frame.width;
    max_h = (arg0->frame.height < 0x10) ? 0x10 : arg0->frame.height;
    ret = 1;
    switch ((u32)arg0->state) {
        case 4:
            return 1;
        case 3:
            x = arg0->frame.x;
            y = arg0->frame.y;
            t = 11 - arg0->animTimer;
            w = ((max_w - 0x10) * t) / 4 + 0x10;
            h = ((max_h - 0x10) * t) / 4 + 0x10;
            break;
        case 0:
            t = arg0->animTimer - 1;
            x = arg0->frame.x;
            y = arg0->frame.y;
            w = ((max_w - 0x10) * t) / 4 + 0x10;
            h = ((max_h - 0x10) * t) / 4 + 0x10;
            break;
        case 1:
        case 2:
            ret = 0;
            x = arg0->frame.x;
            y = arg0->frame.y;
            h = max_h;
            w = max_w;
            break;
    }
    if (ret == 0) {
        if (!(arg0->frame.style & 1)) {
            if ((arg0->frame.style & 2) && (arg0->frame.style & 4)) {
                Ui_FillRectPrimEnvColor(x, y, w, h, arg0->frame.color, arg0->frame.color2);
            } else if (arg0->frame.color.a == 0xFF) {
                gSPDisplayList(gDisplayListHead++, D_80060270);
                func_80029028(x, y, w, h, *(Color8002A354*)&arg0->frame.color);
            } else {
                gSPDisplayList(gDisplayListHead++, D_80073480);
                Ui_FillRectPrimColor(x, y, w, h, arg0->frame.color);
            }
        }
    }
    Ui_DrawTexturedFrameDecal(x, y, w, h, D_80073554);
    if (arg0->frame.style & 0x800) {
        Window_DrawTitleTab(x, y - 22, (s32)arg0->title, arg0->frame.style);
    }
    if (arg0->frame.style & 0x1000) {
        Window_DrawHeaderStripe(x, y - 10, 80, arg0->frame.style);
    }
    return ret;
}

/**
 * Advances a window's open/close animation and draws its frame and background for this frame.
 * Verified in play (2026-11-14): with the function stubbed at the main menu's バトル prompt, the
 * prompt's frame and background vanished and only its text stayed; restoring it brought them back.
 * Every main menu message window calls it each frame through MainMenu_DrawMessageWindow.
 */
void Window_UpdateAndDrawFrame(Window* window) {
    Window_UpdateAnimation(window);
    Window_DrawAnimatedFrame(window);
}

/**
 * Sets up a labeled button: rect (arg1, arg2), width arg3 and height 24, style 1, color `arg4` and label
 * `arg5`, drawn in font size 8 at offset (6, 2) inside the box. The meaning of unk_24 (set to 0x14) is
 * not known.
 * Seen in play (2026-11-13) (menu tour from the main menu): called on every menu screen past the
 * main menu, for windows at (411, 189, 72) and (496, 189, 72).
 * @unverified Name guessed from the code; comment kept.
 */
void Window_InitLabeled(LabeledButton* arg0, s32 arg1, s32 arg2, s32 arg3, Color_RGBA8 arg4, char* arg5) {
    arg0->unk_24 = 0x14;
    arg0->fontSize = 8;
    arg0->labelX = 6;
    arg0->labelY = 2;
    arg0->unk_34 = 0;
    Window_SetRect((s8*)arg0, arg1, arg2, arg3, 24);
    arg0->style = 1;
    arg0->color = arg4;
    arg0->label = arg5;
}

extern Color_RGBA8 D_80073520;
void Ui_FillRectHighlighted(s32, s32, s32, s32, Color_RGBA8);
void Ui_DrawRoundedFrame(s32, s32, s32, s32, Color_RGBA8);
/**
 * Draws a labeled window: frame, highlight or rounded border from the flags, then its label in the flag color.
 * Seen in play (2026-11-13) (menu tour from the main menu): called on every menu screen past the
 * main menu, for the windows set up by Window_InitLabeled.
 * @unverified Name and comment guessed from the code.
 */
void Window_DrawLabeled(LabeledButton* arg0, s32 arg1) {
    Ui_DrawLabelFrame(arg0->x, arg0->y, arg0->width, arg0->height);
    if ((arg0->flags & 8) || (arg1 & 0x10)) {
        Ui_FillRectHighlighted(arg0->x + 1, arg0->y + 1, arg0->width - 2, arg0->height - 2, arg0->color);
    } else if (arg1 & 2) {
        Ui_DrawRoundedFrame(arg0->x, arg0->y, arg0->width, arg0->height, D_80073520);
    }
    func_8001AB6C();
    func_8001A384(arg0->fontSize, arg0->unk_34);
    Font_SetColorForFlags(arg0->flags | arg1);
    Font_Printf(arg0->x + arg0->labelX, arg0->y + arg0->labelY, arg0->label);
    func_8001ABBC();
}

/**
 * Sets an image button's rectangle and its IA16 image and image width.
 * Seen in play (2026-11-14): せいとん's organize window sets up its two image buttons with it.
 */
void ImageButton_Init(ImageButton* button, s32 x, s32 y, s32 w, s32 h, s32 image_width, s32 image) {
    Window_SetRect((s8*)button, x, y, w, h);
    button->image = (u8*)image;
    button->imageWidth = image_width;
}

/**
 * Draws an image button: border, a highlighted fill when it is pressed (flag 8 or `flags` 0x10) or a
 * rounded frame when selected (`flags` 2), then its image tinted with the selected or normal color.
 * Seen in play (2026-11-14): draws the せいとん organize window's buttons.
 */
void ImageButton_Draw(ImageButton* button, s32 flags) {
    Color_RGBA8 color;
    Color_RGBA8* src;

    Ui_DrawLabelFrame(button->x, button->y, button->width, button->height);
    if ((button->flags & 8) || (flags & 0x10)) {
        Ui_FillRectHighlighted(button->x + 1, button->y + 1, button->width - 2, button->height - 2, button->highlightColor);
    } else if (flags & 2) {
        Ui_DrawRoundedFrame(button->x, button->y, button->width, button->height, D_80073520);
    }
    if (flags & 0x12) {
        src = &button->selectedColor;
    } else {
        src = &button->color;
    }
    color = *src;
    gSPDisplayList(gDisplayListHead++, D_80073450);
    gDPSetCombineMode(gDisplayListHead++, G_CC_MODULATEIDECALA_PRIM, G_CC_MODULATEIDECALA_PRIM);
    gDPSetPrimColor(gDisplayListHead++, 0, 0, color.r, color.g, color.b, color.a);
    Gfx_DrawTextureIa16(button->x + 3, button->y + 3, button->width - 6, button->height - 6, button->image, button->imageWidth, 0);
}

/** Moves a vertical menu selection according to a d-pad direction. */
s32 Ui_AdjustVerticalSelection(UiSelection* arg0, s32 arg1) {
    s32 ret = 0;

    switch (arg1) {
        case 0x800:
            Audio_PlaySoundEffectById(SFX_MENU_SCROLL);
            if (arg0->index == 0) {
                arg0->index += arg0->count;
            }
            arg0->index--;
            ret = 1;
            break;

        case 0x400:
            Audio_PlaySoundEffectById(SFX_MENU_SCROLL);
            if (arg0->index >= (arg0->count - 1)) {
                arg0->index -= arg0->count;
            }
            arg0->index++;
            ret = 1;
            break;
    }

    return ret;
}

/** Reads the repeated d-pad input and moves a vertical menu selection. */
s32 Ui_HandleVerticalSelectionInput(s32 arg0) {
    s32 sp1C = Input_GetRepeatedDPad() & 0xFFFF;

    Ui_AdjustVerticalSelection(arg0, sp1C);
    return sp1C;
}

/** Moves a horizontal menu selection according to a d-pad direction. */
s32 Ui_AdjustHorizontalSelection(UiSelection* arg0, s32 arg1) {
    s32 ret = 0;

    switch (arg1) {
        case 0x200:
            Audio_PlaySoundEffectById(SFX_MENU_SCROLL);
            if (arg0->index == 0) {
                arg0->index += arg0->count;
            }
            arg0->index--;
            ret = 1;
            break;

        case 0x100:
            Audio_PlaySoundEffectById(SFX_MENU_SCROLL);
            if (arg0->index >= (arg0->count - 1)) {
                arg0->index -= arg0->count;
            }
            arg0->index++;
            ret = 1;
            break;
    }

    return ret;
}

/** Reads the repeated d-pad input and moves a horizontal menu selection. */
s32 Ui_HandleHorizontalSelectionInput(UiSelection* arg0) {
    s32 sp1C = Input_GetRepeatedDPad() & 0xFFFF;

    Ui_AdjustHorizontalSelection(arg0, sp1C);
    return sp1C;
}

/** Scrolls a selection in steps according to the repeated d-pad input. */
void Ui_AdjustSteppedScrollSelection(UiRangeValue* arg0) {
    s32 temp_v0 = Input_GetRepeatedDPad();
    s32 sp18 = arg0->step;

    if (gPlayer1Controller->buttonDown & 0x2000) {
        sp18 = ((arg0->max - arg0->min) + 1) / 10;
    }

    switch (temp_v0) {
        case 0x800:
            Audio_PlaySoundEffectById(SFX_MENU_SCROLL);
            if (arg0->value - sp18 < arg0->min) {
                arg0->value = arg0->min;
            } else {
                arg0->value -= sp18;
            }
            break;

        case 0x400:
            Audio_PlaySoundEffectById(SFX_MENU_SCROLL);
            if (arg0->max < arg0->value + sp18) {
                arg0->value = arg0->max;
            } else {
                arg0->value += sp18;
            }
            break;
    }
}

/** Changes a numeric selection according to a d-pad direction. */
s32 Ui_AdjustNumericSelection(UiNumberInput* arg0, s32 arg1) {
    s32 var_t1;
    s32 var_a2;
    s32 i;

    var_a2 = 1;

    for (i = arg0->cursorDigit; i > 0; i--) {
        var_a2 *= 10;
    }

    switch (arg1) {
        case 0x200:
            if (arg0->cursorDigit + 1 < arg0->digitCount) {
                arg0->cursorDigit = arg0->cursorDigit + 1;
            }
            Audio_PlaySoundEffectById(SFX_MENU_SCROLL);
            var_t1 = 1;
            break;

        case 0x100:
            if (arg0->cursorDigit > 0) {
                arg0->cursorDigit--;
            }
            Audio_PlaySoundEffectById(SFX_MENU_SCROLL);
            var_t1 = 1;
            break;

        case 0x800:
            if (arg0->value == arg0->max) {
                arg0->value = arg0->value - ((arg0->value / var_a2) * var_a2);
                if (arg0->value < arg0->min) {
                    arg0->value = arg0->min;
                }
            } else {
                arg0->value += var_a2;
                if (arg0->max < arg0->value) {
                    arg0->value = arg0->max;
                }
            }
            Audio_PlaySoundEffectById(SFX_MENU_SCROLL);
            var_t1 = 1;
            break;

        case 0x400:
            if (arg0->value == arg0->min) {
                arg0->value = arg0->max;
            } else {
                arg0->value -= var_a2;
                if (arg0->value < arg0->min) {
                    arg0->value = arg0->min;
                }
            }
            Audio_PlaySoundEffectById(SFX_MENU_SCROLL);
            var_t1 = 1;
            break;
    }
    return var_t1;
}

/** Reads the repeated d-pad input and changes a numeric selection. */
s32 Ui_HandleNumericSelectionInput(UiNumberInput* arg0) {
    s32 sp1C = Input_GetRepeatedDPad() & 0xFFFF;

    Ui_AdjustNumericSelection(arg0, sp1C);
    return sp1C;
}

/**
 * Changes a selection over a stepped range according to the repeated d-pad
 * input.
 */
s32 Ui_AdjustSteppedRangeSelection(UiRangeValue* arg0) {
    s32 sp1C = Input_GetRepeatedDPad() & 0xFFFF;
    s32 sp18 = arg0->step;

    if (sp1C != 0) {
        Audio_PlaySoundEffectById(SFX_MENU_SCROLL);

        switch (sp1C) {
            case 0x200:
                sp18 *= 10;

            case 0x800:
                if (arg0->value >= arg0->max) {
                    arg0->value = arg0->min;
                } else if (arg0->max < (arg0->value + sp18)) {
                    arg0->value = arg0->max;
                } else {
                    arg0->value = arg0->value + sp18;
                }
                break;

            case 0x100:
                sp18 *= 10;

            case 0x400:
                if (arg0->min >= arg0->value) {
                    arg0->value = arg0->max;
                } else if ((arg0->value - sp18) < arg0->min) {
                    arg0->value = arg0->min;
                } else {
                    arg0->value = arg0->value - sp18;
                }
                break;
        }
    }

    return sp1C;
}

extern Gfx D_80073450[];
extern u8 *D_80073584[];
/**
 * Draws `arg2` (up to nine digits) at (arg0, arg1) in 8x12 digit images, 9 pixels apart, without
 * leading zeros.
 * Seen in play (2026-11-13) the Free Battle entry screen called it after each L icon, and the rows
 * showed the levels without padding (L10, L20, L25). The Lab PC list calls it the same way. Was
 * Trade_DrawDigitStrip, a Stadium 1 Trade name for a general number drawer.
 */
void Ui_DrawNumberUnpadded(s32 arg0, s32 arg1, s32 arg2) {
    s32 i;
    s32 var_s0;
    s32 var_s4;
    s32 temp_lo;

    var_s0 = 100000000;
    var_s4 = 0;
    gSPDisplayList(gDisplayListHead++, D_80073450);
    gDPSetCombineMode(gDisplayListHead++, G_CC_DECALRGBA, G_CC_DECALRGBA);

    for (i = 9; i != 0;) {
        temp_lo = arg2 / var_s0;
        i--;
        if ((temp_lo != 0) || (var_s4 != 0) || (i == 0)) {
                        func_8001BCB4(arg0, arg1, 8, 12, D_80073584[temp_lo], 8, 0);
            arg0 += 9;
            var_s4 = 1;
        }
        arg2 %= var_s0;
        var_s0 /= 10;
    }
}

extern Gfx D_80073450[];
extern u8 *D_80073584[];
/**
 * Draws `value` right-aligned in `digits` digit images, without leading zeros.
 * Seen in play (2026-11-13) (menu tour from the main menu): called in registration as (246, 137,
 * value 10, 3 digits) and in the Lab PC box screen as (206, 151, value 0, 2 digits) and (233, 151,
 * value 30, 2 digits).
 * @unverified Name and comment guessed from the code.
 */
void Ui_DrawNumber(s32 x, s32 y, s32 value, s32 digits) {
    s32 first;

    gSPDisplayList(gDisplayListHead++, D_80073450);
    gDPSetCombineMode(gDisplayListHead++, G_CC_DECALRGBA, G_CC_DECALRGBA);
    first = 1;
    while (digits > 0) {
        digits--;
        if (value > 0 || first) {
            func_8001BCB4(x + digits * 9, y, 8, 12, D_80073584[value % 10], 8, 0);
        }
        value /= 10;
        first = 0;
    }
}

extern Gfx D_80073450[];
extern u8 *D_80073584[];
/**
 * Draws `value` in `digits` digit images, with leading zeros.
 * Seen in play (2026-11-12) in いちらん: called with (45, 156, 1, 4) for the 0001 number of the
 * first row and (260, 156, 12345, 5) for its ID 12345, both drawn with leading zeros as shown.
 */
void Ui_DrawNumberZeroPadded(s32 x, s32 y, s32 value, s32 digits) {

    gSPDisplayList(gDisplayListHead++, D_80073450);
    gDPSetCombineMode(gDisplayListHead++, G_CC_DECALRGBA, G_CC_DECALRGBA);
    while (digits > 0) {
        digits--;
        func_8001BCB4(x + digits * 9, y, 8, 12, D_80073584[value % 10], 8, 0);
        value /= 10;
    }
}

/** Returns -1 when B was pressed, 1 when A was pressed, else 0. */
s32 Ui_GetSelectionDirection(Controller* arg0) {
    s32 var_v1 = 0;

    if (arg0->buttonPressed & BTN_B) {
        var_v1 = -1;
    } else if (arg0->buttonPressed & BTN_A) {
        var_v1 = 1;
    }

    return var_v1;
}

extern s32 D_80073644[];
/**
 * Maps a Game Boy game id to its category index through the 12-word table D_80073644, which holds
 * { 0, 0, 1, 2, 0, 0, 0, 3, 0, 0, 0, 0 } in the retail ROM (Stadium 1 keeps it as a file-static
 * array; here it stays extern because this file's .data cannot be placed yet). `arg0` is not
 * range-checked.
 */
s32 GbSave_GameToCategoryIndex(s32 arg0) {
    return D_80073644[arg0];
}

extern Img8002A3F8 D_80073674;
extern Color_RGBA8 D_80073684[];
extern u8* D_80073694[];
extern u8 D_04008F20[];
void Gfx_DrawTextureIa8(s32 x1, s32 y1, s32 draw_width, s32 height, u8* texture, s32 load_width, s32 texture_spread_x_mode);

/**
 * Draws a Game Boy cartridge icon at (x, y), tinted with the color of the cartridge's `game`
 * (GbSave_GameToCategoryIndex), with label image `label` on it.
 * Seen in play (2026-11-14): the registration screen's trainer panel draws the Green cartridge with it.
 */
void GbSave_DrawCartridgeIcon(s32 x, s32 y, s32 label, s32 game) {
    Img8002A3F8 img = D_80073674;
    Color_RGBA8* color = &D_80073684[GbSave_GameToCategoryIndex(game)];

    Ui_DrawImageInStrips(&img, x, y);
    gSPDisplayList(gDisplayListHead++, D_80073450);
    gDPSetCombineMode(gDisplayListHead++, G_CC_MODULATEIDECALA_PRIM, G_CC_MODULATEIDECALA_PRIM);
    gDPSetPrimColor(gDisplayListHead++, 0, 0, color->r, color->g, color->b, color->a);
    Gfx_DrawTextureIa8(x + 6, y + 16, 40, 34, D_04008F20, 40, 0);
    gDPSetPrimColor(gDisplayListHead++, 0, 0, ((u8*)&D_800734A8)[0], ((u8*)&D_800734A8)[1], ((u8*)&D_800734A8)[2], ((u8*)&D_800734A8)[3]);
    Gfx_DrawTextureIa8(x + 9, y + 23, 0x20, 20, D_80073694[label], 0x20, 0);
}

extern u8 D_04009FB0[];
/**
 * Tiles the 128-pixel I8 background texture across the 640-wide screen from row `start` to `end`.
 * Seen in play (2026-11-13) (menu tour from the main menu): called on the main menu and every menu
 * screen after it, called from Ui_DrawTintedScreenBackground with rows 56 to 480.
 * @unverified Name and comment guessed from the code.
 */
void Ui_DrawScreenBackgroundRows(s32 start, s32 end) {
    s32 row;
    s32 n;

    while (start < end) {
        row = start % 128;
        n = (128 - row > 32) ? 32 : 128 - row;
        if (n >= end - start) {
            n = end - start;
        }
        gDPLoadTextureBlock(gDisplayListHead++, D_04009FB0 + row * 128, G_IM_FMT_I, G_IM_SIZ_8b, 128, n, 0, G_TX_WRAP, G_TX_WRAP, 7, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        gSPTextureRectangle(gDisplayListHead++, 0, start << 2, 640 << 2, (start + n) << 2, G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);
        start += n;
    }
}

/**
 * Draws the screen background rows `start`..`end` tinted with the environment color (r, g, b).
 * Seen in play (2026-11-13) (menu tour from the main menu): called on the main menu and every menu
 * screen after it, for rows 56 to 480 with the tint (200, 200, ...).
 * @unverified Name and comment guessed from the code.
 */
void Ui_DrawTintedScreenBackground(s32 start, s32 end, s32 r, s32 g, s32 b) {
    gDPPipeSync(gDisplayListHead++);
    gDPSetCycleType(gDisplayListHead++, G_CYC_1CYCLE);
    gDPSetRenderMode(gDisplayListHead++, 0x0F0A4000, 0);
    gDPSetTexturePersp(gDisplayListHead++, G_TP_NONE);
    gDPSetTextureFilter(gDisplayListHead++, G_TF_POINT);
    gDPSetCombineLERP(gDisplayListHead++, TEXEL0, 0, ENVIRONMENT, 0, 0, 0, 0, TEXEL0, TEXEL0, 0, ENVIRONMENT, 0, 0, 0, 0, TEXEL0);
    gDPSetEnvColor(gDisplayListHead++, r, g, b, 0xFF);
    Ui_DrawScreenBackgroundRows(start, end);
    gDPPipeSync(gDisplayListHead++);
    gDPSetTexturePersp(gDisplayListHead++, G_TP_PERSP);
}

extern u8 D_04010E10[];
extern u8 D_04010FD8[];
extern Img8002A3F8 D_800735F4;
u32 func_800566BC(s32);

/**
 * Draws a window's title tab above it at (x, y): a stretched tab sized to the title `str`, its end
 * cap, an optional icon (style 0x2000) and the title text.
 * Verified in play (2026-11-14): stubbed at the main menu's バトル prompt, the バトル tab above the
 * prompt vanished.
 */
void Window_DrawTitleTab(s32 x, s32 y, s32 str, s32 flags) {
    s32 width;
    s32 text_x;

    width = (func_800566BC(str) >> 1) * 20;
    text_x = x + 8;
    if (flags & 0x2000) {
        text_x += 40;
        width += 40;
    }
    gSPDisplayList(gDisplayListHead++, D_80073450);
    gDPSetCombineMode(gDisplayListHead++, G_CC_DECALRGBA, G_CC_DECALRGBA);
    gDPLoadTextureBlock(gDisplayListHead++, D_04010E10, G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 28, 0, G_TX_CLAMP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    gSPTextureRectangle(gDisplayListHead++, x << 2, y << 2, (x + width + 8) << 2, (y + 28) << 2, G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);
    gDPLoadTextureBlock(gDisplayListHead++, D_04010FD8, G_IM_FMT_RGBA, G_IM_SIZ_16b, 48, 28, 0, G_TX_CLAMP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    gSPTextureRectangle(gDisplayListHead++, (x + width + 8) << 2, y << 2, (x + width + 56) << 2, (y + 28) << 2, G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);
    if (flags & 0x2000) {
        Ui_DrawImageInStrips(&D_800735F4, x + 8, y + 4);
    }
    func_8001AB6C();
    func_8001A384(8, 0);
    func_8001AA9C(((u8*)&D_800734A8)[0], ((u8*)&D_800734A8)[1], ((u8*)&D_800734A8)[2], ((u8*)&D_800734A8)[3]);
    Font_Printf(text_x, y + 4, str);
    func_8001ABBC();
}

extern u8 D_0400E680[];
extern u8 D_0400E788[];

/**
 * Draws the decorative stripe (style 0x1000) above a window: a `w`-wide bar and a 32-pixel end cap at
 * (x, y). Callers pass the window style as a fourth argument it ignores.
 * Seen in play (2026-11-14): runs for the Pokédex, party, registration and list windows (style 0x1000).
 */
void Window_DrawHeaderStripe(s32 x, s32 y, s32 w) {
    gSPDisplayList(gDisplayListHead++, D_80073450);
    gDPSetCombineMode(gDisplayListHead++, G_CC_DECALRGBA, G_CC_DECALRGBA);
    gDPLoadTextureBlock(gDisplayListHead++, D_0400E680, G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 16, 0, G_TX_CLAMP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    gSPTextureRectangle(gDisplayListHead++, x << 2, y << 2, (x + w) << 2, (y + 16) << 2, G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);
    gDPLoadTextureBlock(gDisplayListHead++, D_0400E788, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 16, 0, G_TX_CLAMP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    gSPTextureRectangle(gDisplayListHead++, (x + w) << 2, y << 2, (x + w + 32) << 2, (y + 16) << 2, G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);
}

/** Interpolates a color between gray and the given color. */
Color_RGBA8 Color_InterpolateFromGray(Color_RGBA8 arg0, f32 arg1) {
    static Color_RGBA8 D_80075940 = { 0xC8, 0xC8, 0xC8, 0xFF }; // #C8C8C8FF

    Color_RGBA8 sp4;

    sp4.r = (s32)((arg0.r - D_80075940.r) * arg1) + D_80075940.r;
    sp4.g = (s32)((arg0.g - D_80075940.g) * arg1) + D_80075940.g;
    sp4.b = (s32)((arg0.b - D_80075940.b) * arg1) + D_80075940.b;
    sp4.a = arg0.a;

    return sp4;
}

extern Color_RGBA8 D_800736A8;
void Ui_FillRectHighlighted(s32, s32, s32, s32, Color_RGBA8);

/** Draws a label in a battle info widget. */
void BattleInfoWidget_DrawLabel(s32 arg0, s32 arg1, char* arg2, s32 arg3, s32 arg4) {
    if (arg4 & 0x18) {
        Ui_FillRectHighlighted(arg0 + 3, arg1 + 3, 230, 22, D_800736A8);
    }

    Font_BeginTranslucentTextRendering();
    Font_SetColorForFlags(arg4);
    Font_SetActive(8, 0);
    Font_Printf(arg0 + 8, arg1 + 4, arg2);
    Font_EndTexturedTextRendering();
}

M2C_UNK func_80027804(s8 *, M2C_UNK *, M2C_UNK, M2C_UNK); /* extern */
M2C_UNK Menu_Init(s8 *, s8 *, s8 *, M2C_UNK *, s32, s32); /* extern */
extern M2C_UNK D_800736AC;
extern M2C_UNK func_8002C998;

/**
 * Sets up the save-before-leaving window (248x174, style 0x1001) at (arg1, arg2) with its three-item menu
 * (items D_800736AC, callback func_8002C998, 236 wide, 28-pixel rows).
 * Seen in play (2026-11-12) in いちらん: B after using an item opened 「ないようが へんこうされています」 with
 * レポートしてやめる, レポートしないでやめる and キャンセル.
 */
void SavePrompt_Init(SavePrompt* arg0, s32 arg1, s32 arg2) {
    s8 *sp2C;
    s8 *temp_a0;

    Window_SetRect((s8*)arg0, arg1, arg2, 248, 174);
    arg0->window.animTimer = 0;
    arg0->window.title = NULL;
    arg0->window.state = 0;
    arg0->window.frame.style = 0x1001;
    temp_a0 = (s8*)&arg0->items;
    sp2C = temp_a0;
    func_80027804(temp_a0, &D_800736AC, 3, 3);
    Menu_Init((s8*)&arg0->menu, sp2C, (s8*)arg0->itemFlags, &func_8002C998, 236, 28);
    arg0->menu.options |= 0x10000;
}

s32 func_8002AE6C();
void Ui_DrawTexturedDivider(s32, s32, s32, FrameTextures*);
void Menu_DrawItems(s8*, s32, s32, s32, s32);
extern u8 D_8007356C[];
extern Color_RGBA8 D_800736B8;
extern Color_RGBA8 D_800736BC;
extern Color8002A354 D_800736C0;
extern u8 D_8007B920[];

/**
 * Draws the save-before-leaving window.
 * Seen in play (2026-11-12) in いちらん: drew that window every frame while it was open.
 */
void SavePrompt_Draw(SavePrompt* arg0) {
    if (func_8002AE6C() != 0) {
        return;
    }
    Ui_DrawTexturedDivider(arg0->window.frame.x, arg0->window.frame.y + 69, arg0->window.frame.width, D_8007356C);
    Ui_FillRectPrimEnvColor(arg0->window.frame.x + 6, arg0->window.frame.y + 6, arg0->window.frame.width - 12, 0x40, D_800736B8, D_800736BC);
    gSPDisplayList(gDisplayListHead++, D_80060270);
    func_80029028(arg0->window.frame.x + 6, arg0->window.frame.y + 76, arg0->window.frame.width - 12, 92, D_800736C0);
    Menu_DrawItems((s8*)&arg0->menu, arg0->window.frame.x + 6, arg0->window.frame.y + 80, 0xFFEF, 0);
    func_8001AB6C();
    func_8001AA9C(((u8*)&D_800734A8)[0], ((u8*)&D_800734A8)[1], ((u8*)&D_800734A8)[2], ((u8*)&D_800734A8)[3]);
    func_8001A384(8, 0);
    Font_SetLineHeight(28);
    Font_Printf(arg0->window.frame.x + 14, arg0->window.frame.y + 10, (s32)D_8007B920);
    func_8001ABBC();
}

extern Color_RGBA8 D_800736C4;
extern Color_RGBA8 D_800736C8;
extern u8 D_8007B940[];
/**
 * Draws the レポートちゅう (Saving...) window for two frames.
 * Seen in play (2026-11-12) in いちらん: after レポートしてやめる it drew 「レポートちゅう」 over the prompt, just
 * before LabPCList_SaveChanges ran.
 */
void Save_DrawReportingWindow(SavePrompt* arg0) {
    s32 i = 2;
    u8* str = D_8007B940;
    BgStage_AdvanceFrame();
    while (i-- > 0) {
        BgStage_DrawFrame();
        Ui_FillRectPrimEnvColor(arg0->window.frame.x + 6, arg0->window.frame.y + 6, arg0->window.frame.width - 12, 0x40, D_800736C4, D_800736C8);
        func_8001AB6C();
        func_8001AA9C(0xFF, 0xFF, 0xFF, 0xFF); // #FFFFFF
        func_8001A384(0x10, 0);
        func_8001ABE8();
        func_8001AAE4(0xFF, 0xB2, 0xB2, 0xFF); // #FFB2B2
        Font_Printf(arg0->window.frame.x + 0x20, arg0->window.frame.y + 22, (s32)str);
        func_8001AC3C();
        func_8001ABBC();
        BgStage_AdvanceFrame();
    }
    BgStage_DrawFrame();
}

s32 func_8002BC14(s32);
s32 Menu_UpdateCursor(void *, void *);
extern s32 D_800603C0;

/**
 * Handles the save-before-leaving window. Returns -1 on cancel, 1 to save, 2 to leave without saving.
 * Seen in play (2026-11-12) in いちらん: returned 1 for レポートしてやめる, 2 for レポートしないでやめる, and -1 for
 * キャンセル or B.
 */
s32 SavePrompt_Update(SavePrompt* arg0) {
    s32 ret = 0;

    if ((arg0->window.state != 1) && (arg0->window.state != 2)) {
        return 0;
    }
    if (Menu_UpdateCursor(&arg0->menu, arg0) == 0) {
        s32 res = func_8002BC14(D_800603C0);

        if (res == -1) {
            Audio_PlaySystemSound(3);
            ret = -1;
        } else if (res == 1) {
            switch (arg0->menu.cursor) {
                case 0:
                    ret = 1;
                    Audio_PlaySystemSound(29);
                    break;
                case 1:
                    ret = 2;
                    Audio_PlaySystemSound(33);
                    break;
                case 2:
                    ret = -1;
                    Audio_PlaySystemSound(3);
                    break;
            }
            if (arg0) { // karodo
            }
        }
    }
    return ret;
}

extern u8 D_80073554[];
void Window_DrawFrame(s32* arg0);

/**
 * Draws the window frame, hiding it every other four frames while blinking is on. Returns 1 while hidden.
 * Seen in play (2026-11-13) ran when the COM entry was confirmed (このデータでエントリーします, はい), just before
 * the stadium and VS intro (Free Battle, L1-30 rules, six L30 rentals vs COM); also in an ordinary
 * Free Battle.
 * @unverified Name and comment guessed from the code.
 */
s32 Window_DrawBlinkingFrame(BlinkingTextBox* arg0) {
    s32 t = arg0->blinkTimer++;

    t %= 8;
    if ((arg0->noBlink == 0) && (t >= 4)) {
        return 1;
    }
    Window_DrawFrame(&arg0->frame);
    Ui_DrawTexturedFrameDecal(arg0->frame.x, arg0->frame.y, arg0->frame.width, arg0->frame.height, D_80073554);
    return 0;
}

typedef struct Ent8002D188 { s32 w; s32 h; s32 unk8; } Ent8002D188;
typedef struct Rgba8002D188 { u8 r, g, b, a; } Rgba8002D188;
extern Ent8002D188 D_800736D0[];
u32 func_800566BC(s32);
extern u8 D_800736E8[];
extern u8 D_800736EC[];
/**
 * Sets up a text box sized to string `arg1`.
 * Seen in play (2026-11-13) ran once when A was pressed on a Free Battle entry row whose Pokémon
 * were all ineligible; a text box sized to 「エントリーできる ポケモンが いません」 then appeared.
 */
void TextBox_Init(TextBox* arg0, s32 arg1, s32 arg2, s32 arg3, u32 arg4) {
    u32 len;
    s32 w;
    s32 h;
    s32 cw;
    s32 ch;

    if (arg4 == 0) {
        len = func_800566BC(arg1) >> 1;
    } else {
        len = arg4;
    }
    arg0->fontStyle = arg2;
    arg0->lineCount = arg3;
    cw = D_800736D0[arg2].w;
    ch = D_800736D0[arg2].h;
    w = ch * 2 + len * cw;
    h = ch + (u32)(cw + ch) * arg3;
    Window_SetRect((s8*)arg0, (628 - w) / 2, (412 - h) / 2 + 56, w + 12, h + 12);
    arg0->window.animTimer = 0;
    arg0->window.title = NULL;
    arg0->window.state = 0;
    arg0->window.frame.style = 6;
    arg0->window.frame.color = *(Color_RGBA8*)D_800736E8;
    arg0->window.frame.color2 = *(Color_RGBA8*)D_800736EC;
    arg0->text = (char*)arg1;
}

extern Rgba8002D188 D_800736F0[];
/**
 * Draws a text box and its text.
 * Seen in play (2026-11-13) drew the 「エントリーできる ポケモンが いません」 box on the Free Battle entry screen,
 * every frame while it was up.
 */
void TextBox_Draw(TextBox* arg0) {
    if (func_8002AE6C(arg0) != 0) {
        return;
    }
    func_8001AB6C();
    func_8001A384(D_800736D0[arg0->fontStyle].unk8, 0);
    func_8001AA9C(D_800736F0[0].r, D_800736F0[0].g, D_800736F0[0].b, D_800736F0[0].a);
    Font_SetLineHeight(D_800736D0[arg0->fontStyle].w + D_800736D0[arg0->fontStyle].h);
    func_8001ABE8();
    func_8001AAE4(D_800736F0[1].r, D_800736F0[1].g, D_800736F0[1].b, D_800736F0[1].a);
    Font_Printf(arg0->window.frame.x + D_800736D0[arg0->fontStyle].h + 6, arg0->window.frame.y + D_800736D0[arg0->fontStyle].h + 6, (s32)arg0->text);
    func_8001AC3C();
    func_8001ABBC();
}

/**
 * Returns 1 and plays the confirm sound if player 1 pressed A or B this frame.
 * Seen in play (2026-11-13) (menu tour from the main menu): called in the Lab PC item and box
 * screens while a prompt was open; it returned 0 on frames without A or B.
 * @unverified Name and comment guessed from the code.
 */
s32 Ui_CheckConfirmPressed(UNUSED s32 arg0) {
    s32 ret = 0;

    if (gPlayer1Controller->buttonPressed & (BTN_A | BTN_B)) {
        ret = 1;
        Audio_PlaySoundEffectById(SFX_MENU_CONFIRM);
    }
    return ret;
}

extern u8 D_800736F8[];
extern u8 D_800736FC[];
u32 func_800566BC(s32);
/**
 * Sets up a blinking text box sized to string `arg1`.
 * Seen in play (2026-11-13) ran when the COM entry was confirmed (このデータでエントリーします, はい), just before
 * the stadium and VS intro (Free Battle, L1-30 rules, six L30 rentals vs COM); also in an ordinary
 * Free Battle.
 * @unverified Name and comment guessed from the code.
 */
void BlinkingTextBox_Init(BlinkingTextBox* arg0, s32 arg1, s32 arg2, s32 arg3, u32 arg4) {
    u32 len;
    s32 w;
    s32 h;
    s32 cw;
    s32 ch;

    if (arg4 == 0) {
        len = func_800566BC(arg1) >> 1;
    } else {
        len = arg4;
    }
    arg0->fontStyle = arg2;
    arg0->lineCount = arg3;
    cw = D_800736D0[arg2].w;
    ch = D_800736D0[arg2].h;
    w = ch * 2 + len * cw;
    h = ch + (u32)(cw + ch) * arg3;
    Window_SetRect((s8*)arg0, (628 - w) / 2, (412 - h) / 2 + 56, w + 12, h + 12);
    arg0->blinkTimer = 0;
    arg0->noBlink = 0;
    arg0->frame.style = 6;
    *(Rgba8002D188*)&arg0->frame.color = *(Rgba8002D188 *)D_800736F8;
    *(Rgba8002D188*)&arg0->frame.color2 = *(Rgba8002D188 *)D_800736FC;
    arg0->text = (char*)arg1;
}

extern Rgba8002D188 D_80073700[];
/**
 * Draws a blinking text box and its text.
 * Seen in play (2026-11-13) ran when the COM entry was confirmed (このデータでエントリーします, はい), just before
 * the stadium and VS intro (Free Battle, L1-30 rules, six L30 rentals vs COM); also in an ordinary
 * Free Battle.
 * @unverified Name and comment guessed from the code.
 */
void BlinkingTextBox_Draw(BlinkingTextBox* arg0) {
    if (Window_DrawBlinkingFrame(arg0) != 0) {
        return;
    }
    func_8001AB6C();
    func_8001A384(D_800736D0[arg0->fontStyle].unk8, 0);
    func_8001AA9C(D_80073700[0].r, D_80073700[0].g, D_80073700[0].b, D_80073700[0].a);
    Font_SetLineHeight(D_800736D0[arg0->fontStyle].w + D_800736D0[arg0->fontStyle].h);
    func_8001ABE8();
    func_8001AAE4(D_80073700[1].r, D_80073700[1].g, D_80073700[1].b, D_80073700[1].a);
    Font_Printf(arg0->frame.x + D_800736D0[arg0->fontStyle].h + 6, arg0->frame.y + D_800736D0[arg0->fontStyle].h + 6, arg0->text);
    func_8001AC3C();
    func_8001ABBC();
}

/**
 * Returns the number of moves a Pokemon knows (the count of nonzero move
 * slots).
 */
s32 BattleMon_CountMoves(u8* arg0) {
    s32 i;

    for (i = 0; i < 4; i++) {
        if (arg0[i + 9] == 0) {
            return i;
        }
    }
    return 4;
}

/**
 * Returns the zero-based move id in move slot `arg1` of BattleMon `arg0` (moves start at 0x09):
 * -1 for an empty slot, -2 for an id past the 165 Gen 1 moves.
 * Seen in play (2026-11-12) in いちらん page 2/3: フシギダネ's たいあたり (33) gave 32 and なきごえ (45)
 * 44; ヒトカゲ's ひっかく (10) gave 9.
 */
s32 BattleMon_GetMoveIndex(s32 arg0, s32 arg1) {
    u8* p = (u8*)(arg0 + arg1);
    s32 id = p[9];
    s32 r;

    if (id >= 166) {
        r = -2;
    } else {
        r = id - 1;
    }
    return r;
}

s32 BattleMon_CountMoves(u8* arg0);
s32 BattleMon_GetMoveIndex(s32, s32);                        /* extern */

/**
 * Returns -1 for a slot past the filled moves, otherwise BattleMon_GetMoveIndex.
 * Seen in play (2026-11-12) in いちらん page 2/3: slots 0-1 returned the move index and the empty
 * slots 2-3 returned -1.
 */
s32 BattleMon_GetMoveIndexChecked(s32 arg0, s32 arg1) {
    if (arg1 >= BattleMon_CountMoves((u8*)arg0)) {
        return -1;
    }
    return BattleMon_GetMoveIndex(arg0, arg1);
}

s32 Type_ToTableIndex(s32);

/**
 * Returns the display index of the species' type 1 (`arg1` 0) or type 2 (`arg1` 1); -1 for type 2 of a single-type species.
 * Seen in play (2026-11-12) in いちらん: it drives the タイプ1/タイプ2 columns. フシギダネ gave 11 and 3 (くさ,
 * どく), ヒトカゲ 9 and -1, and ゼニガメ 10 and -1. どく = 3 matches its 4th place in タイプであつめる.
 */
s32 Pokemon_GetTypeIndex(BattleMon* arg0, s32 arg1) {
    s32 idx = arg0->species.id - 1;
    s32 type;

    if (arg1 == 1) {
        if (gSpeciesData[idx].type1 == gSpeciesData[idx].type2) {
            return -1;
        }
        type = gSpeciesData[idx].type2;
    } else {
        type = gSpeciesData[idx].type1;
    }
    return Type_ToTableIndex(type);
}

s32 func_80006780();
void BgStage_DrawFrame(void);
extern u8 D_80073554[];
extern Color8002A354 D_80073708;
extern u8 D_8007B950[];
extern u8 D_8007B960[];
extern u8 D_8007B97C[];
extern u8 D_8007B9BC[];
extern u8 D_8007B9D0[];

/**
 * Draws the save result window: レポートちゅう (Saving...) or, on failure, レポートできませんでした (Could not save) with "don't turn the power off".
 * Not reached in play (2026-11-13): did not run in a tour of the main menu, Pokédex, party, Lab,
 * registration, Free Battle setup and a COM battle (opening, a switch, running, a Pound turn).
 * @unverified Name and comment guessed from the code.
 */
void Save_DrawReportResultWindow(s32 arg0) {
    BgStage_DrawFrame();
    Ui_DrawTexturedFrameDecal(110, 114, 420, 276, D_80073554);
    gSPDisplayList(gDisplayListHead++, D_80060270);
    func_80029028(116, 120, 408, 264, D_80073708);
    if (arg0 == 0) {
        func_8001AB6C();
        func_8001A384(0x10, 0);
        func_8001AA9C(0xFF, 0xFF, 0xFF, 0xFF); // #FFFFFF
        func_8001ABE8();
        func_8001AAE4(0xFF, 0xF1, 0x78, 0xFF); // #FFF178
        Font_Printf(236, 168, (s32)D_8007B950);
        func_8001AC3C();
        func_8001ABBC();
    } else if (arg0 == 2) {
        func_8001AB6C();
        func_8001A384(0x10, 0);
        func_8001AA9C(0xFF, 0xFF, 0xFF, 0xFF); // #FFFFFF
        func_8001ABE8();
        func_8001AAE4(0xFF, 0xF1, 0x78, 0xFF); // #FFF178
        Font_Printf(176, 168, (s32)D_8007B960);
        func_8001AC3C();
        func_8001ABBC();
    } else if (arg0 == 3) {
        func_8001AB6C();
        func_8001A384(0x10, 0);
        func_8001AA9C(0xFF, 0xFF, 0xFF, 0xFF); // #FFFFFF
        func_8001ABE8();
        func_8001AAE4(0xFF, 0xF1, 0x78, 0xFF); // #FFF178
        Font_Printf(0x80, 132, (s32)D_8007B97C);
        func_8001AC3C();
        func_8001ABBC();
    }
    if (arg0 != 0) {
        func_8001AB6C();
        func_8001A384(0x10, 0);
        func_8001AA9C(0xFF, 0xFF, 0xFF, 0xFF); // #FFFFFF
        func_8001ABE8();
        func_8001AAE4(0xFF, 0xF1, 0x78, 0xFF); // #FFF178
        Font_Printf(296, 240, (s32)D_8007B9BC);
        func_8001AC3C();
        func_8001AA9C(((u8*)&D_800734A8)[0], ((u8*)&D_800734A8)[1], ((u8*)&D_800734A8)[2], ((u8*)&D_800734A8)[3]);
        Font_SetLineHeight(36);
        Font_Printf(0x80, 240, (s32)D_8007B9D0);
        func_8001ABBC();
    }
    func_80006780();
}

M2C_UNK func_80006780();                            /* extern */
s32 GbSave_PollCartRemoval(s32);                             /* extern */
s32 func_8002207C(s32);                             /* extern */
void Save_DrawReportResultWindow(s32);

/**
 * Shows the report (save) error window until the cartridge has been taken out and put back, and
 * repeats until the save to port `port` succeeds (func_8002207C, GbSave_RebuildAndWriteSave). The
 * window state starts at 2 and follows GbSave_PollCartRemoval's result 1 or 3 until it returns 2. In
 * Stadium 1 the same loop (LabUI_ShowSavingPrompt) reads the poll as 0 nothing yet, 1 waiting for the
 * cart, 2 same pak verified and 3 a different pak reinitialized.
 * @unverified Name read from the code; the Lab PC calls it when writing to the GB cartridge fails.
 */
void GbSave_RunReportErrorLoop(s32 port) {
    s32 state;
    s32 result;

    func_80006780();
    do {
        state = 2;
        do {
            Save_DrawReportResultWindow(state);
            result = GbSave_PollCartRemoval(port);
            if (result == 1) {
                state = 1;
            } else if (result == 3) {
                state = 3;
            }
        } while (result != 2);
        Save_DrawReportResultWindow(0);
        Save_DrawReportResultWindow(0);
    } while (func_8002207C(port) == 0);
}
