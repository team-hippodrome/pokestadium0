/* Stadium Zero resident code. */
/* C ported from the Stadium 1 decomp: src/fragments/particle_math/particle_math_269820.c, src/gb_save.c. */

#include "gb_save.h"
#include "input.h"
#include "gb_data.h"
#include "pokemon_stats.h"
#include "save_data.h"
#include "game_state.h"
#include "audio_sfx.h"
#include "gfx_buffer.h"
#include "controller.h"
#include "memory.h"
#include "stage_loader.h"
extern u32 D_8007360C[];
extern u8 pad_D_80075944[];

#include "fragments/particle_math/particle_math.h"
#include "geo_render.h"
extern ParticleDescriptor gDefaultParticleDescriptor;

#include "m2c_macros.h"

void GbSave_BuildPortSummary(unk_func_8002D860* arg0, s32 arg1);
void Particle_SetVelocityXZFromRotationY(Particle* arg0);
s32 Ui_AdjustVerticalSelection(unk_func_8002DCB8_arg0* arg0, s32 arg1);
s32 Ui_HandleVerticalSelectionInput(s32 arg0);
s32 Ui_AdjustHorizontalSelection(unk_func_8002DD98_arg0* arg0, s32 arg1);
s32 Ui_HandleHorizontalSelectionInput(unk_func_8002DD98_arg0* arg0);
void Ui_AdjustSteppedScrollSelection(unk_func_8002DE78_arg0* arg0);
s32 Ui_HandleNumericSelectionInput(unk_func_8820E99C_030_030* arg0);
s32 Ui_AdjustSteppedRangeSelection(unk_func_8002E128_arg0* arg0);
s32 Ui_GetSelectionDirection(unk_func_8002EBD8_arg0* arg0);
Color_RGBA8 Color_InterpolateFromGray(Color_RGBA8 arg0, f32 arg1);

s32 Ui_AdjustNumericSelection(unk_func_8830867C_044_038_030* arg0, s32 arg1);
s32 Particle_Field50_SetXZFromField7C_09BB4(s32* arg0);
s32 Particle_Field7C_SetXZFromField74AngleY_0B278(void *arg0);

void func_8001AA9C(u8, u8, u8, u8);
void func_8001AB6C(void);
void func_8001A384(s32, s32);
void func_8001A944(s32, s32, s32);
void func_8001ABBC(void);
void Font_SetLineHeight(s32 arg0);
void func_8001ABE8(void);
void func_8001AAE4(u8, u8, u8, u8);
void func_8001AC3C(void);
extern s8 D_800734A8;
extern s8 D_800734B0;
extern s8 D_800734B8;
// FAKE: decomp slop. Raw pointer-offset casts stand in for struct fields.
/**
 * Sets the text color from the row flags: 0x18 selected, 0x1 alternate, otherwise
 * normal. Each is a pair of colors; without flag 0x2 the second one is used.
 * Seen in play (2026-11-13) (menu tour from the main menu): called on every menu screen past the
 * main menu (Pokédex, party, Lab list, sort and PC, registration), with flags 2 and 0; it
 * returned pointers into the color table at 0x800734A8.
 * @unverified Name and comment guessed from the code.
 */
void Font_SetColorForFlags(s32 arg0)
{
  s8 *new_var; // FAKE: permuter temp
  if (arg0 & 0x18)
  {
    new_var = &D_800734B8;
  }
  else
    if (arg0 & 1)
  {
    new_var = &D_800734B0;
    new_var = new_var; // FAKE: self-assignment
  }
  else
  {
    new_var = &D_800734A8;
  }
  if (!(arg0 & 2))
  {
    new_var += 4;
  }
  new_var = (s8 *) new_var;
  func_8001AA9C(*((u8 *) (new_var + 0)), *((u8 *) (new_var + 1)), *((u8 *) (new_var + 2)), *((u8 *) (((s8 *) new_var) + 3))); // FAKE: decomp slop, raw pointer casts stand in for struct fields
}

/*
 * func_80027F8C
 *
 * Picks one 4-byte entry and passes its four bytes to func_8001AA9C as four
 * byte-sized arguments.  The entry comes from one of three tables chosen by
 * the flags in arg0:
 *   - if any of bits 0x18 is set, from D_800734B8;
 *   - otherwise, if bit 0x01 is set, from D_800734C0;
 *   - otherwise from D_800734A8.
 * If bit 0x02 is clear the entry that follows (4 bytes further on) is used
 * instead.
 *
 * This is the same selection as Font_SetColorForFlags just above, except that bit
 * 0x01 selects D_800734C0 here and D_800734B0 there.  What the four bytes
 * mean is not established from the code (they look like color components).
 */
extern s8 D_800734C0;
void func_80027F8C(s32 arg0) {
    u8* entry;

    if (arg0 & 0x18) {
        entry = (u8*)&D_800734B8;
    } else if (arg0 & 1) {
        entry = (u8*)&D_800734C0;
    } else {
        entry = (u8*)&D_800734A8;
    }
    if (!(arg0 & 2)) {
        entry += 4;
    }
    func_8001AA9C(entry[0], entry[1], entry[2], entry[3]);
}

/**
 * Builds the display summary of a port's Game Boy save, or clears it when no
 * save is present.
 */
void GbSave_BuildPortSummary(unk_func_8002D860* arg0, s32 arg1) {
    if (GbSave_GetSaveState(arg1) != 0) {
        arg0->unk_00 = 1;
    } else {
        arg0->unk_00 = 0;
        arg0->unk_08 = GbSave_GetTrainerId(arg1);
        GbSave_GetPlayerName(arg1, &arg0[1]);
    }
    arg0->unk_04 = GbSave_GetPortGame(arg1);
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
void func_8001AA60(s32, s32, s32);
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
        Ui_FillRectRgba5551(0, y, 0x188, 0x36, D_800734C8[GbSave_GameToCategoryIndex(summary->game)]);
    } else {
        gSPDisplayList(gDisplayListHead++, D_80060270);
        Ui_FillRectRgba5551(0, y, 0x188, 0x36, D_800734D8);
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
    Ui_FillRectRgba5551(0, y + 54, 0x280, 2, D_800734DC);

    if (summary != NULL) {
        func_8001AB6C();
        func_8001A384(8, 0);
        func_8001AA9C(((u8*)&D_800734A8)[0], ((u8*)&D_800734A8)[1], ((u8*)&D_800734A8)[2], ((u8*)&D_800734A8)[3]);
        func_8001AA60(0x4A, (y + 32), arg3 + 0x31);
        func_8001AA60(0x5E, (y + 32), 0x50);
        func_8001A944(0x86, (y + 32), (s32)((summary->state == 0) ? summary->name : D_8007B8E0));
        func_8001ABBC();

        gSPDisplayList(gDisplayListHead++, D_80073450);
        gDPLoadTextureBlock(gDisplayListHead++, D_04010918, G_IM_FMT_IA, G_IM_SIZ_8b, 40, 10, 0, G_TX_NOMIRROR | G_TX_WRAP,
                            G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        gSPScisTextureRectangle(gDisplayListHead++, 255 << 2, (y + 41) << 2, 295 << 2, (y + 51) << 2, G_TX_RENDERTILE, 0,
                                0, 1 << 10, 1 << 10);
        if (summary->state == 0) {
            Ui_DrawNumberZeroPadded(0x12A, y + 39, summary->trainerId, 5);
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
    func_8001A944(0x254 - ((func_800566BC((s32)label) * 20) >> 1), (y + 32), (s32)label);
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
 * the colored tile panels grey.
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
void Ui_DrawTexturedFrame(s32 x, s32 y, s32 w, s32 h, u8* arg4) {
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
    load = D_800734F0[M2C_FIELD(arg4, s32*, 4)];
    load(8, 8, M2C_FIELD(arg4, u8**, 8), M2C_FIELD(arg4, s32*, 0));
    gSPTextureRectangle(gDisplayListHead++, x << 2, y << 2, (x2 - 8U) << 2, y8, G_TX_RENDERTILE, 0, 0, 0x400, 0x400);
    load(8, 8, M2C_FIELD(arg4, u8**, 0x14), M2C_FIELD(arg4, s32*, 0));
    gSPTextureRectangle(gDisplayListHead++, (x2 - 8) << 2, y << 2, x2 << 2, (y2 - 8U) << 2, G_TX_RENDERTILE, 0, 0, 0x400, 0x400);
    load(8, 8, M2C_FIELD(arg4, u8**, 0x10), M2C_FIELD(arg4, s32*, 0));
    gSPTextureRectangle(gDisplayListHead++, (x + 8) << 2, (y2 - 8) << 2, x2 << 2, y2 << 2, G_TX_RENDERTILE, (w * -0x20) + 0x200, 0, 0x400, 0x400);
    load(8, 8, M2C_FIELD(arg4, u8**, 0xC), M2C_FIELD(arg4, s32*, 0));
    gSPTextureRectangle(gDisplayListHead++, x << 2, y8, (x + 8) << 2, y2 << 2, G_TX_RENDERTILE, 0, (h * -0x20) + 0x200, 0x400, 0x400);
}

extern Gfx D_80073450[];
void Ui_DrawTexturedFrame(s32, s32, s32, s32, u8*);

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
void Ui_DrawTexturedDivider(s32 x, s32 y, s32 w, u8* arg3) {
    GbTexLoadFunc load;
    s32 pad[2]; // FAKE
    s32 x2;
    s32 y8;

    if (w < 0x10) {
        w = 0x10;
    }
    x2 = x + w;
    y8 = (y + 8) << 2;
    load = D_80073500[M2C_FIELD(arg3, s32*, 4)];
    gSPDisplayList(gDisplayListHead++, D_80073450);
    gDPSetCombineMode(gDisplayListHead++, G_CC_DECALRGBA, G_CC_DECALRGBA);
    load(8, 8, M2C_FIELD(arg3, u8**, 0x10), M2C_FIELD(arg3, s32*, 0));
    gSPTextureRectangle(gDisplayListHead++, x << 2, y << 2, (x2 - 8) << 2, y8, G_TX_RENDERTILE, 0, 0, 0x400, 0x400);
    load(8, 8, M2C_FIELD(arg3, u8**, 0x14), M2C_FIELD(arg3, s32*, 0));
    gSPTextureRectangle(gDisplayListHead++, (x2 - 8) << 2, y << 2, x2 << 2, y8, G_TX_RENDERTILE, 0, 0, 0x400, 0x400);
}

extern GbTexLoadFunc D_80073510[];

/**
 * Vertical counterpart of Ui_DrawTexturedDivider: draws a frame edge of height h (at least 16)
 * at (x, y) from the textures at arg3 + 8 and arg3 + 0xC, loaded through
 * D_80073510[arg3 + 4].
 */
void func_80029864(s32 x, s32 y, s32 h, u8* arg3) {
    GbTexLoadFunc load;
    s32 pad[2]; // FAKE
    s32 y2;
    s32 x8;

    if (h < 0x10) {
        h = 0x10;
    }
    y2 = y + h;
    x8 = (x + 8) << 2;
    load = D_80073510[M2C_FIELD(arg3, s32*, 4)];
    gSPDisplayList(gDisplayListHead++, D_80073450);
    gDPSetCombineMode(gDisplayListHead++, G_CC_DECALRGBA, G_CC_DECALRGBA);
    load(8, 8, M2C_FIELD(arg3, u8**, 8), M2C_FIELD(arg3, s32*, 0));
    gSPTextureRectangle(gDisplayListHead++, x << 2, y << 2, x8, (y2 - 8) << 2, G_TX_RENDERTILE, 0, 0, 0x400, 0x400);
    load(8, 8, M2C_FIELD(arg3, u8**, 0xC), M2C_FIELD(arg3, s32*, 0));
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
 * Seen in play (2026-11-12) in いちらん: drew the yellow row cursor at (0x52, 0x98), size 0x50 x
 * 0x14, for LabPCList_DrawRowCursor.
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

/*
 * func_8002A32C
 *
 * Forwards its four arguments unchanged to Ui_DrawTexturedFrameDecal and adds a fifth
 * argument: the address of the data at D_80073524 (typed as a byte array).
 * func_8002A354 calls Ui_DrawTexturedFrameDecal the same way with D_8007353C as the
 * fifth argument.  What this data is, and what Ui_DrawTexturedFrameDecal does with it,
 * has not been determined, so the names are left as addresses.
 */
extern u8 D_80073524[];
void Ui_DrawTexturedFrameDecal(s32, s32, s32, s32, u8*);
void func_8002A32C(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    Ui_DrawTexturedFrameDecal(arg0, arg1, arg2, arg3, D_80073524);
}

extern u8 D_8007353C[];
void Ui_DrawTexturedFrameDecal(s32, s32, s32, s32, u8*);
void func_8002A354(s32 arg0, s32 arg1, s32 arg2, s32 arg3, Color8002A354 arg4) {
    gSPDisplayList(gDisplayListHead++, D_80060270);
    func_80029028(arg0 + 1, arg1 + 1, arg2 - 2, arg3 - 2, arg4);
    Ui_DrawTexturedFrameDecal(arg0, arg1, arg2, arg3, D_8007353C);
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
    s32 curY;

    gSPDisplayList(gDisplayListHead++, D_80073408);
    stride = arg0->stride;
    max_rows = 0x1000 / (stride * 2);
    rows = arg0->height;
    pixels = arg0->pixels;
    curY = y;
    while (rows > 0) {
        if (max_rows < rows) {
            n = max_rows;
        } else {
            n = rows;
        }
        func_8001B884(x, curY, arg0->width, n, pixels, stride, 0x200000);
        stride = arg0->stride;
        rows -= n;
        curY += n;
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

// FAKE: decomp slop. Raw pointer-offset casts and the new_var alias stand in for struct fields.
/**
 * Sets a window's x, y, width and height and clears its state word (+0x10).
 * Seen in play (2026-11-13) (menu tour from the main menu): called on every menu screen past the
 * main menu, for example (54, 87, width 532).
 * @unverified Name and comment guessed from the code.
 */
void Window_SetRect(s8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4)
{
  s8 *new_var; // FAKE: permuter temp
  *((s32 *) (((s8 *) arg0) + 0)) = arg1;
  *((s32 *) (((s8 *) arg0) + 4)) = arg2;
  new_var = arg0;
  *((s32 *) (((s8 *) arg0) + 8)) = arg3;
  *((s32 *) (((s8 *) new_var) + 0xC)) = arg4;
  *((s32 *) (((s8 *) arg0) + 0x10)) = 0;
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

/*
 * Particle_Field7C_SetXZFromField74AngleY_0B278
 *
 * Advances a small step counter held in the object `arg0`: the counter is
 * the word at offset 0x24 and a second word at offset 0x28 receives a value
 * that depends on it.  Returns 1 or 0.
 *
 *   counter >= 11: word 0x28 = 4, return 1 (counter unchanged);
 *   counter >= 7:  word 0x28 = 3, counter + 1, return 1;
 *   counter <  4:  if counter == 0, func_8003F6AC(4, arg0) first (the
 *                  counter is re-read afterwards); then word 0x28 = 0,
 *                  counter + 1, return 1;
 *   counter 4, 5:  word 0x28 = 1, counter + 1, return 0;
 *   counter == 6:  word 0x28 = 2 (counter unchanged), return 0.
 *
 * What the counter measures is not established.
 */
M2C_UNK func_8003F6AC();

/** Sets a particle's x and z components from its angle about the y axis. */
s32 Particle_Field7C_SetXZFromField74AngleY_0B278(void *arg0) {
    s32 var_v1;
    s32 var_v0;

    var_v0 = M2C_FIELD(arg0, s32 *, 0x24);
    var_v1 = 1;
    if (var_v0 >= 0xB) {
        M2C_FIELD(arg0, s32 *, 0x28) = 4;
        return 1;
    }
    if (var_v0 >= 7) {
        M2C_FIELD(arg0, s32 *, 0x28) = 3;
        M2C_FIELD(arg0, s32 *, 0x24) = (s32) (var_v0 + 1);
    } else if (var_v0 < 4) {
        if (var_v0 == 0) {
            func_8003F6AC(4, arg0);
            var_v1 = 1;
            var_v0 = M2C_FIELD(arg0, s32 *, 0x24);
        }
        M2C_FIELD(arg0, s32 *, 0x28) = 0;
        M2C_FIELD(arg0, s32 *, 0x24) = (s32) (var_v0 + 1);
    } else {
        var_v1 = 0;
        if (var_v0 < 6) {
            M2C_FIELD(arg0, s32 *, 0x28) = 1;
            M2C_FIELD(arg0, s32 *, 0x24) = (s32) (var_v0 + 1);
        } else {
            M2C_FIELD(arg0, s32 *, 0x28) = 2;
        }
    }
    return var_v1;
}

extern u8 D_80073554[];
void func_8002C1B4(s32, s32, s32, s32);
void func_8002C5A4(); // no prototype: callers pass a fourth argument the definition ignores

/** Sets a particle's x and z components from another vector in the particle. */
s32 Particle_Field50_SetXZFromField7C_09BB4(s32* arg0) {
    UNUSED s32 pad1; // FAKE: unused locals that only pad the stack frame
    UNUSED s32 pad2; // FAKE
    UNUSED s32 pad3; // FAKE
    UNUSED s32 pad4; // FAKE
    s32 x;
    s32 y;
    s32 w;
    s32 h;
    s32 ret;
    s32 maxW;
    s32 maxH;
    s32 t;

    maxW = (arg0[2] < 0x10) ? 0x10 : arg0[2];
    maxH = (arg0[3] < 0x10) ? 0x10 : arg0[3];
    ret = 1;
    switch ((u32)arg0[10]) {
        case 4:
            return 1;
        case 3:
            x = arg0[0];
            y = arg0[1];
            t = 0xB - arg0[9];
            w = ((maxW - 0x10) * t) / 4 + 0x10;
            h = ((maxH - 0x10) * t) / 4 + 0x10;
            break;
        case 0:
            t = arg0[9] - 1;
            x = arg0[0];
            y = arg0[1];
            w = ((maxW - 0x10) * t) / 4 + 0x10;
            h = ((maxH - 0x10) * t) / 4 + 0x10;
            break;
        case 1:
        case 2:
            ret = 0;
            x = arg0[0];
            y = arg0[1];
            h = maxH;
            w = maxW;
            break;
    }
    if (ret == 0) {
        if (!(arg0[5] & 1)) {
            if ((arg0[5] & 2) && (arg0[5] & 4)) {
                Ui_FillRectPrimEnvColor(x, y, w, h, *(Color_RGBA8*)&arg0[6], *(Color_RGBA8*)&arg0[7]);
            } else if (((u8*)&arg0[6])[3] == 0xFF) {
                gSPDisplayList(gDisplayListHead++, D_80060270);
                func_80029028(x, y, w, h, *(Color8002A354*)&arg0[6]);
            } else {
                gSPDisplayList(gDisplayListHead++, D_80073480);
                Ui_FillRectPrimColor(x, y, w, h, *(Color_RGBA8*)&arg0[6]);
            }
        }
    }
    Ui_DrawTexturedFrameDecal(x, y, w, h, D_80073554);
    if (arg0[5] & 0x800) {
        func_8002C1B4(x, y - 0x16, arg0[8], arg0[5]);
    }
    if (arg0[5] & 0x1000) {
        func_8002C5A4(x, y - 0xA, 0x50, arg0[5]);
    }
    return ret;
}

/** Sets a particle's x and z velocity from its rotation about the y axis. */
void Particle_SetVelocityXZFromRotationY(Particle* arg0) {
    Particle_Field7C_SetXZFromField74AngleY_0B278(arg0);
    Particle_Field50_SetXZFromField7C_09BB4(arg0);
}

/**
 * Initializes a text-box style object at arg0: stores the constants 0x14,
 * 8, 6, 2 and 0 at offsets 0x24..0x34, runs Window_SetRect(arg0, arg1, arg2,
 * arg3, 0x18), then sets offset 0x14 to 1, offset 0x20 to the color arg4
 * (a 4-byte struct passed by value, stored with unaligned stores) and offset
 * 0x38 to the string pointer arg5. What the fields mean is not established.
 * Seen in play (2026-11-13) (menu tour from the main menu): called on every menu screen past the
 * main menu, for windows at (411, 189, 72) and (496, 189, 72).
 * @unverified Name guessed from the code; comment kept.
 */
void Window_InitLabeled(s8* arg0, s32 arg1, s32 arg2, s32 arg3, Color_RGBA8 arg4, char* arg5) {
    M2C_FIELD(arg0, s32*, 0x24) = 0x14;
    M2C_FIELD(arg0, s32*, 0x28) = 8;
    M2C_FIELD(arg0, s32*, 0x2C) = 6;
    M2C_FIELD(arg0, s32*, 0x30) = 2;
    M2C_FIELD(arg0, s32*, 0x34) = 0;
    Window_SetRect(arg0, arg1, arg2, arg3, 0x18);
    M2C_FIELD(arg0, s32*, 0x14) = 1;
    M2C_FIELD(arg0, Color_RGBA8*, 0x20) = arg4;
    M2C_FIELD(arg0, char**, 0x38) = arg5;
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
void Window_DrawLabeled(s8* arg0, s32 arg1) {
    func_8002A32C(M2C_FIELD(arg0, s32*, 0), M2C_FIELD(arg0, s32*, 4), M2C_FIELD(arg0, s32*, 8), M2C_FIELD(arg0, s32*, 0xC));
    if ((M2C_FIELD(arg0, s32*, 0x10) & 8) || (arg1 & 0x10)) {
        Ui_FillRectHighlighted(M2C_FIELD(arg0, s32*, 0) + 1, M2C_FIELD(arg0, s32*, 4) + 1, M2C_FIELD(arg0, s32*, 8) - 2, M2C_FIELD(arg0, s32*, 0xC) - 2, M2C_FIELD(arg0, Color_RGBA8*, 0x20));
    } else if (arg1 & 2) {
        Ui_DrawRoundedFrame(M2C_FIELD(arg0, s32*, 0), M2C_FIELD(arg0, s32*, 4), M2C_FIELD(arg0, s32*, 8), M2C_FIELD(arg0, s32*, 0xC), D_80073520);
    }
    func_8001AB6C();
    func_8001A384(M2C_FIELD(arg0, s32*, 0x28), M2C_FIELD(arg0, s32*, 0x34));
    Font_SetColorForFlags(M2C_FIELD(arg0, s32*, 0x10) | arg1);
    func_8001A944(M2C_FIELD(arg0, s32*, 0x2C) + M2C_FIELD(arg0, s32*, 0), M2C_FIELD(arg0, s32*, 0x30) + M2C_FIELD(arg0, s32*, 4), M2C_FIELD(arg0, s32*, 0x38));
    func_8001ABBC();
}

/*
 * func_8002B018
 *
 * Calls Window_SetRect(arg0, arg1, arg2, arg3, arg4), which fills the first
 * five words of the object (arg1, arg2, arg3, arg4, 0), then stores arg5 at
 * +0x24 and arg6 at +0x28.
 */
void func_8002B018(s8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    Window_SetRect(arg0, arg1, arg2, arg3, arg4);
    M2C_FIELD(arg0, s32 *, 0x28) = arg6;
    M2C_FIELD(arg0, s32 *, 0x24) = arg5;
}

void func_8002B054(s8* arg0, s32 arg1) {
    Color_RGBA8 color;
    Color_RGBA8* src;

    func_8002A32C(M2C_FIELD(arg0, s32*, 0), M2C_FIELD(arg0, s32*, 4), M2C_FIELD(arg0, s32*, 8), M2C_FIELD(arg0, s32*, 0xC));
    if ((M2C_FIELD(arg0, s32*, 0x10) & 8) || (arg1 & 0x10)) {
        Ui_FillRectHighlighted(M2C_FIELD(arg0, s32*, 0) + 1, M2C_FIELD(arg0, s32*, 4) + 1, M2C_FIELD(arg0, s32*, 8) - 2, M2C_FIELD(arg0, s32*, 0xC) - 2, M2C_FIELD(arg0, Color_RGBA8*, 0x20));
    } else if (arg1 & 2) {
        Ui_DrawRoundedFrame(M2C_FIELD(arg0, s32*, 0), M2C_FIELD(arg0, s32*, 4), M2C_FIELD(arg0, s32*, 8), M2C_FIELD(arg0, s32*, 0xC), D_80073520);
    }
    if (arg1 & 0x12) {
        src = (Color_RGBA8*)(arg0 + 0x18);
    } else {
        src = (Color_RGBA8*)(arg0 + 0x1C);
    }
    color = *src;
    gSPDisplayList(gDisplayListHead++, D_80073450);
    gDPSetCombineMode(gDisplayListHead++, G_CC_MODULATEIDECALA_PRIM, G_CC_MODULATEIDECALA_PRIM);
    gDPSetPrimColor(gDisplayListHead++, 0, 0, color.r, color.g, color.b, color.a);
    Gfx_DrawTextureIa16(M2C_FIELD(arg0, s32*, 0) + 3, M2C_FIELD(arg0, s32*, 4) + 3, M2C_FIELD(arg0, s32*, 8) - 6, M2C_FIELD(arg0, s32*, 0xC) - 6, M2C_FIELD(arg0, u8**, 0x28), M2C_FIELD(arg0, s32*, 0x24), 0);
}

/** Moves a vertical menu selection according to a d-pad direction. */
s32 Ui_AdjustVerticalSelection(unk_func_8002DCB8_arg0* arg0, s32 arg1) {
    s32 ret = 0;

    switch (arg1) {
        case 0x800:
            Audio_PlaySoundEffectById(SFX_MENU_SCROLL);
            if (arg0->unk_04 == 0) {
                arg0->unk_04 += arg0->unk_08;
            }
            arg0->unk_04--;
            ret = 1;
            break;

        case 0x400:
            Audio_PlaySoundEffectById(SFX_MENU_SCROLL);
            if (arg0->unk_04 >= (arg0->unk_08 - 1)) {
                arg0->unk_04 -= arg0->unk_08;
            }
            arg0->unk_04++;
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
s32 Ui_AdjustHorizontalSelection(unk_func_8002DD98_arg0* arg0, s32 arg1) {
    s32 ret = 0;

    switch (arg1) {
        case 0x200:
            Audio_PlaySoundEffectById(SFX_MENU_SCROLL);
            if (arg0->unk_04 == 0) {
                arg0->unk_04 += arg0->unk_08;
            }
            arg0->unk_04--;
            ret = 1;
            break;

        case 0x100:
            Audio_PlaySoundEffectById(SFX_MENU_SCROLL);
            if (arg0->unk_04 >= (arg0->unk_08 - 1)) {
                arg0->unk_04 -= arg0->unk_08;
            }
            arg0->unk_04++;
            ret = 1;
            break;
    }

    return ret;
}

/** Reads the repeated d-pad input and moves a horizontal menu selection. */
s32 Ui_HandleHorizontalSelectionInput(unk_func_8002DD98_arg0* arg0) {
    s32 sp1C = Input_GetRepeatedDPad() & 0xFFFF;

    Ui_AdjustHorizontalSelection(arg0, sp1C);
    return sp1C;
}

/** Scrolls a selection in steps according to the repeated d-pad input. */
void Ui_AdjustSteppedScrollSelection(unk_func_8002DE78_arg0* arg0) {
    s32 temp_v0 = Input_GetRepeatedDPad();
    s32 sp18 = arg0->unk_0C;

    if (gPlayer1Controller->buttonDown & 0x2000) {
        sp18 = ((arg0->unk_08 - arg0->unk_04) + 1) / 10;
    }

    switch (temp_v0) {
        case 0x800:
            Audio_PlaySoundEffectById(SFX_MENU_SCROLL);
            if (arg0->unk_00 - sp18 < arg0->unk_04) {
                arg0->unk_00 = arg0->unk_04;
            } else {
                arg0->unk_00 -= sp18;
            }
            break;

        case 0x400:
            Audio_PlaySoundEffectById(SFX_MENU_SCROLL);
            if (arg0->unk_08 < arg0->unk_00 + sp18) {
                arg0->unk_00 = arg0->unk_08;
            } else {
                arg0->unk_00 += sp18;
            }
            break;
    }
}

/** Changes a numeric selection according to a d-pad direction. */
s32 Ui_AdjustNumericSelection(unk_func_8830867C_044_038_030* arg0, s32 arg1) {
    s32 var_t1;
    s32 var_a2;
    s32 i;

    var_a2 = 1;

    for (i = arg0->unk_10; i > 0; i--) {
        var_a2 *= 10;
    }

    switch (arg1) {
        case 0x200:
            if (arg0->unk_10 + 1 < arg0->unk_0C) {
                arg0->unk_10 = arg0->unk_10 + 1;
            }
            Audio_PlaySoundEffectById(SFX_MENU_SCROLL);
            var_t1 = 1;
            break;

        case 0x100:
            if (arg0->unk_10 > 0) {
                arg0->unk_10--;
            }
            Audio_PlaySoundEffectById(SFX_MENU_SCROLL);
            var_t1 = 1;
            break;

        case 0x800:
            if (arg0->unk_00 == arg0->unk_08) {
                arg0->unk_00 = arg0->unk_00 - ((arg0->unk_00 / var_a2) * var_a2);
                if (arg0->unk_00 < arg0->unk_04) {
                    arg0->unk_00 = arg0->unk_04;
                }
            } else {
                arg0->unk_00 += var_a2;
                if (arg0->unk_08 < arg0->unk_00) {
                    arg0->unk_00 = arg0->unk_08;
                }
            }
            Audio_PlaySoundEffectById(SFX_MENU_SCROLL);
            var_t1 = 1;
            break;

        case 0x400:
            if (arg0->unk_00 == arg0->unk_04) {
                arg0->unk_00 = arg0->unk_08;
            } else {
                arg0->unk_00 -= var_a2;
                if (arg0->unk_00 < arg0->unk_04) {
                    arg0->unk_00 = arg0->unk_04;
                }
            }
            Audio_PlaySoundEffectById(SFX_MENU_SCROLL);
            var_t1 = 1;
            break;
    }
    return var_t1;
}

/** Reads the repeated d-pad input and changes a numeric selection. */
s32 Ui_HandleNumericSelectionInput(unk_func_8820E99C_030_030* arg0) {
    s32 sp1C = Input_GetRepeatedDPad() & 0xFFFF;

    Ui_AdjustNumericSelection(arg0, sp1C);
    return sp1C;
}

/**
 * Changes a selection over a stepped range according to the repeated d-pad
 * input.
 */
s32 Ui_AdjustSteppedRangeSelection(unk_func_8002E128_arg0* arg0) {
    s32 sp1C = Input_GetRepeatedDPad() & 0xFFFF;
    s32 sp18 = arg0->unk_0C;

    if (sp1C != 0) {
        Audio_PlaySoundEffectById(SFX_MENU_SCROLL);

        switch (sp1C) {
            case 0x200:
                sp18 *= 0xA;

            case 0x800:
                if (arg0->unk_00 >= arg0->unk_08) {
                    arg0->unk_00 = arg0->unk_04;
                } else if (arg0->unk_08 < (arg0->unk_00 + sp18)) {
                    arg0->unk_00 = arg0->unk_08;
                } else {
                    arg0->unk_00 = arg0->unk_00 + sp18;
                }
                break;

            case 0x100:
                sp18 *= 0xA;

            case 0x400:
                if (arg0->unk_04 >= arg0->unk_00) {
                    arg0->unk_00 = arg0->unk_08;
                } else if ((arg0->unk_00 - sp18) < arg0->unk_04) {
                    arg0->unk_00 = arg0->unk_04;
                } else {
                    arg0->unk_00 = arg0->unk_00 - sp18;
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
                        func_8001BCB4(arg0, arg1, 8, 0xC, D_80073584[temp_lo], 8, 0);
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
            func_8001BCB4(x + digits * 9, y, 8, 0xC, D_80073584[value % 10], 8, 0);
        }
        value /= 10;
        first = 0;
    }
}

extern Gfx D_80073450[];
extern u8 *D_80073584[];
/**
 * Draws `value` in `digits` digit images, with leading zeros.
 * Seen in play (2026-11-12) in いちらん: called with (0x2D, 0x9C, 1, 4) for the 0001 number of the
 * first row and (0x104, 0x9C, 12345, 5) for its ID 12345, both drawn with leading zeros as shown.
 */
void Ui_DrawNumberZeroPadded(s32 x, s32 y, s32 value, s32 digits) {

    gSPDisplayList(gDisplayListHead++, D_80073450);
    gDPSetCombineMode(gDisplayListHead++, G_CC_DECALRGBA, G_CC_DECALRGBA);
    while (digits > 0) {
        digits--;
        func_8001BCB4(x + digits * 9, y, 8, 0xC, D_80073584[value % 10], 8, 0);
        value /= 10;
    }
}

/** Returns the direction chosen by the d-pad bits in a menu state. */
s32 Ui_GetSelectionDirection(unk_func_8002EBD8_arg0* arg0) {
    s32 var_v1 = 0;

    if (arg0->unk_08 & 0x4000) {
        var_v1 = -1;
    } else if (arg0->unk_08 & 0x8000) {
        var_v1 = 1;
    }

    return var_v1;
}

/*
 * GbSave_GameToCategoryIndex  (owner func_8002BC44)
 *
 * Returns entry arg0 of a 12-word lookup table at D_80073644.  The retail
 * ROM holds { 0, 0, 1, 2, 0, 0, 0, 3, 0, 0, 0, 0 } there (checked against the
 * ROM bytes), the same table the Stadium 1 version of this function keeps as
 * a file-static array.  The table is referenced by its ROM address instead of
 * being defined here because this file's .data cannot be placed yet.
 * arg0 is not range-checked.
 */
extern s32 D_80073644[];
/** Maps a Game Boy game id to its category index. */
s32 GbSave_GameToCategoryIndex(s32 arg0) {
    return D_80073644[arg0];
}

extern Img8002A3F8 D_80073674;
extern Color_RGBA8 D_80073684[];
extern u8* D_80073694[];
extern u8 D_04008F20[];
void Gfx_DrawTextureIa8(s32 x1, s32 y1, s32 draw_width, s32 height, u8* texture, s32 load_width, s32 texture_spread_x_mode);

void func_8002BC58(s32 x, s32 y, s32 arg2, s32 game) {
    Img8002A3F8 img = D_80073674;
    Color_RGBA8* color = &D_80073684[GbSave_GameToCategoryIndex(game)];

    Ui_DrawImageInStrips(&img, x, y);
    gSPDisplayList(gDisplayListHead++, D_80073450);
    gDPSetCombineMode(gDisplayListHead++, G_CC_MODULATEIDECALA_PRIM, G_CC_MODULATEIDECALA_PRIM);
    gDPSetPrimColor(gDisplayListHead++, 0, 0, color->r, color->g, color->b, color->a);
    Gfx_DrawTextureIa8(x + 6, y + 0x10, 0x28, 0x22, D_04008F20, 0x28, 0);
    gDPSetPrimColor(gDisplayListHead++, 0, 0, ((u8*)&D_800734A8)[0], ((u8*)&D_800734A8)[1], ((u8*)&D_800734A8)[2], ((u8*)&D_800734A8)[3]);
    Gfx_DrawTextureIa8(x + 9, y + 0x17, 0x20, 0x14, D_80073694[arg2], 0x20, 0);
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

void func_8002C1B4(s32 x, s32 y, s32 str, s32 flags) {
    s32 width;
    s32 textX;

    width = (func_800566BC(str) >> 1) * 0x14;
    textX = x + 8;
    if (flags & 0x2000) {
        textX += 0x28;
        width += 0x28;
    }
    gSPDisplayList(gDisplayListHead++, D_80073450);
    gDPSetCombineMode(gDisplayListHead++, G_CC_DECALRGBA, G_CC_DECALRGBA);
    gDPLoadTextureBlock(gDisplayListHead++, D_04010E10, G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 28, 0, G_TX_CLAMP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    gSPTextureRectangle(gDisplayListHead++, x << 2, y << 2, (x + width + 8) << 2, (y + 0x1C) << 2, G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);
    gDPLoadTextureBlock(gDisplayListHead++, D_04010FD8, G_IM_FMT_RGBA, G_IM_SIZ_16b, 48, 28, 0, G_TX_CLAMP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    gSPTextureRectangle(gDisplayListHead++, (x + width + 8) << 2, y << 2, (x + width + 0x38) << 2, (y + 0x1C) << 2, G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);
    if (flags & 0x2000) {
        Ui_DrawImageInStrips(&D_800735F4, x + 8, y + 4);
    }
    func_8001AB6C();
    func_8001A384(8, 0);
    func_8001AA9C(((u8*)&D_800734A8)[0], ((u8*)&D_800734A8)[1], ((u8*)&D_800734A8)[2], ((u8*)&D_800734A8)[3]);
    func_8001A944(textX, y + 4, str);
    func_8001ABBC();
}

extern u8 D_0400E680[];
extern u8 D_0400E788[];

void func_8002C5A4(s32 x, s32 y, s32 w) {
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
        Ui_FillRectHighlighted(arg0 + 3, arg1 + 3, 0xE6, 0x16, D_800736A8);
    }

    Font_BeginTranslucentTextRendering();
    Font_SetColorForFlags(arg4);
    Font_SetActive(8, 0);
    Font_Printf(arg0 + 8, arg1 + 4, arg2);
    Font_EndTexturedTextRendering();
}

/*
 * SavePrompt_Init
 *
 * Initializes a record like Pokedex_InitEntryWindow does, with the first five words
 * set by Window_SetRect to (arg1, arg2, 0xF8, 0xAE, 0), the words at +0x20,
 * +0x24 and +0x28 cleared and +0x14 set to 0x1001.  It then sets up two
 * sub-objects: func_80027804 is called on the area at arg0 + 0x50 with
 * D_800736AC, 3 and 3, and Menu_Init on the object at arg0 + 0x2C with
 * that area, arg0 + 0x5C, the callback func_8002C998 and the constants 0xEC
 * and 0x1C.  Finally bit 0x10000 is set in the word at +0x4C.
 * What func_80027804 and Menu_Init do is not established yet, so the
 * roles of those arguments are not named.
 */
M2C_UNK func_80027804(s8 *, M2C_UNK *, M2C_UNK, M2C_UNK); /* extern */
M2C_UNK Menu_Init(s8 *, s8 *, s8 *, M2C_UNK *, s32, s32); /* extern */
extern M2C_UNK D_800736AC;
extern M2C_UNK func_8002C998;

/**
 * Sets up the save-before-leaving window (248x174) with its menu.
 * Seen in play (2026-11-12) in いちらん: B after using an item opened 「ないようが へんこうされています」 with
 * レポートしてやめる, レポートしないでやめる and キャンセル.
 */
void SavePrompt_Init(s8 *arg0, s32 arg1, s32 arg2) {
    s8 *sp2C;
    s8 *temp_a0;

    Window_SetRect(arg0, arg1, arg2, 0xF8, 0xAE);
    M2C_FIELD(arg0, s32 *, 0x24) = 0;
    M2C_FIELD(arg0, s32 *, 0x20) = 0;
    M2C_FIELD(arg0, s32 *, 0x28) = 0;
    M2C_FIELD(arg0, s32 *, 0x14) = 0x1001;
    temp_a0 = arg0 + 0x50;
    sp2C = temp_a0;
    func_80027804(temp_a0, &D_800736AC, 3, 3);
    Menu_Init(arg0 + 0x2C, sp2C, arg0 + 0x5C, &func_8002C998, 0xEC, 0x1C);
    M2C_FIELD(arg0, s32 *, 0x4C) = (s32) (M2C_FIELD(arg0, s32 *, 0x4C) | 0x10000);
}

s32 func_8002AE6C();
void Ui_DrawTexturedDivider(s32, s32, s32, u8*);
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
void SavePrompt_Draw(s32* arg0) {
    if (func_8002AE6C() != 0) {
        return;
    }
    Ui_DrawTexturedDivider(arg0[0], arg0[1] + 0x45, arg0[2], D_8007356C);
    Ui_FillRectPrimEnvColor(arg0[0] + 6, arg0[1] + 6, arg0[2] - 0xC, 0x40, D_800736B8, D_800736BC);
    gSPDisplayList(gDisplayListHead++, D_80060270);
    func_80029028(arg0[0] + 6, arg0[1] + 0x4C, arg0[2] - 0xC, 0x5C, D_800736C0);
    Menu_DrawItems((s8*)arg0 + 0x2C, arg0[0] + 6, arg0[1] + 0x50, 0xFFEF, 0);
    func_8001AB6C();
    func_8001AA9C(((u8*)&D_800734A8)[0], ((u8*)&D_800734A8)[1], ((u8*)&D_800734A8)[2], ((u8*)&D_800734A8)[3]);
    func_8001A384(8, 0);
    Font_SetLineHeight(0x1C);
    func_8001A944(arg0[0] + 0xE, arg0[1] + 0xA, (s32)D_8007B920);
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
void Save_DrawReportingWindow(s32* arg0) {
    s32 i = 2;
    u8* str = D_8007B940;
    BgStage_AdvanceFrame();
    while (i-- > 0) {
        BgStage_DrawFrame();
        Ui_FillRectPrimEnvColor(arg0[0] + 6, arg0[1] + 6, arg0[2] - 0xC, 0x40, D_800736C4, D_800736C8);
        func_8001AB6C();
        func_8001AA9C(0xFF, 0xFF, 0xFF, 0xFF);
        func_8001A384(0x10, 0);
        func_8001ABE8();
        func_8001AAE4(0xFF, 0xB2, 0xB2, 0xFF);
        func_8001A944(arg0[0] + 0x20, arg0[1] + 0x16, (s32)str);
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
s32 SavePrompt_Update(s8 *arg0) {
    s32 ret = 0;

    if ((M2C_FIELD(arg0, s32 *, 0x28) != 1) && (M2C_FIELD(arg0, s32 *, 0x28) != 2)) {
        return 0;
    }
    if (Menu_UpdateCursor(arg0 + 0x2C, arg0) == 0) {
        s32 res = func_8002BC14(D_800603C0);

        if (res == -1) {
            func_8003F6AC(3);
            ret = -1;
        } else if (res == 1) {
            switch (M2C_FIELD(arg0, s32 *, 0x34)) {
                case 0:
                    ret = 1;
                    func_8003F6AC(0x1D);
                    break;
                case 1:
                    ret = 2;
                    func_8003F6AC(0x21);
                    break;
                case 2:
                    ret = -1;
                    func_8003F6AC(3);
                    break;
            }
            if (arg0) { // FAKE: no-op test; changes register allocation to match
            }
        }
    }
    return ret;
}

extern u8 D_80073554[];
void Window_DrawFrame(s32* arg0);

/**
 * Draws the window frame, hiding it every other four frames while blinking is on. Returns 1 while hidden.
 * Not reached in play (2026-11-13): did not run in a tour of the main menu, Pokédex, party, Lab,
 * registration, Free Battle setup and a COM battle (opening, a switch, running, a Pound turn).
 * @unverified Name and comment guessed from the code.
 */
s32 Window_DrawBlinkingFrame(s32* arg0) {
    s32 t = arg0[8]++;

    t %= 8;
    if ((arg0[9] == 0) && (t >= 4)) {
        return 1;
    }
    Window_DrawFrame(arg0);
    Ui_DrawTexturedFrameDecal(arg0[0], arg0[1], arg0[2], arg0[3], D_80073554);
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
void TextBox_Init(s8 *arg0, s32 arg1, s32 arg2, s32 arg3, u32 arg4) {
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
    M2C_FIELD(arg0, s32 *, 0x30) = arg2;
    M2C_FIELD(arg0, s32 *, 0x34) = arg3;
    cw = D_800736D0[arg2].w;
    ch = D_800736D0[arg2].h;
    w = ch * 2 + len * cw;
    h = ch + (u32)(cw + ch) * arg3;
    Window_SetRect(arg0, (0x274 - w) / 2, (0x19C - h) / 2 + 0x38, w + 0xC, h + 0xC);
    M2C_FIELD(arg0, s32 *, 0x24) = 0;
    M2C_FIELD(arg0, s32 *, 0x20) = 0;
    M2C_FIELD(arg0, s32 *, 0x28) = 0;
    M2C_FIELD(arg0, s32 *, 0x14) = 6;
    M2C_FIELD(arg0, Rgba8002D188 *, 0x18) = *(Rgba8002D188 *)D_800736E8;
    M2C_FIELD(arg0, Rgba8002D188 *, 0x1C) = *(Rgba8002D188 *)D_800736EC;
    M2C_FIELD(arg0, s32 *, 0x2C) = arg1;
}

extern Rgba8002D188 D_800736F0[];
/**
 * Draws a text box and its text.
 * Seen in play (2026-11-13) drew the 「エントリーできる ポケモンが いません」 box on the Free Battle entry screen,
 * every frame while it was up.
 */
void TextBox_Draw(s32* arg0) {
    if (func_8002AE6C(arg0) != 0) {
        return;
    }
    func_8001AB6C();
    func_8001A384(D_800736D0[arg0[12]].unk8, 0);
    func_8001AA9C(D_800736F0[0].r, D_800736F0[0].g, D_800736F0[0].b, D_800736F0[0].a);
    Font_SetLineHeight(D_800736D0[arg0[12]].w + D_800736D0[arg0[12]].h);
    func_8001ABE8();
    func_8001AAE4(D_800736F0[1].r, D_800736F0[1].g, D_800736F0[1].b, D_800736F0[1].a);
    func_8001A944(arg0[0] + D_800736D0[arg0[12]].h + 6, arg0[1] + D_800736D0[arg0[12]].h + 6, arg0[11]);
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
 * Not reached in play (2026-11-13): did not run in a tour of the main menu, Pokédex, party, Lab,
 * registration, Free Battle setup and a COM battle (opening, a switch, running, a Pound turn).
 * @unverified Name and comment guessed from the code.
 */
void BlinkingTextBox_Init(s8 *arg0, s32 arg1, s32 arg2, s32 arg3, u32 arg4) {
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
    M2C_FIELD(arg0, s32 *, 0x2C) = arg2;
    M2C_FIELD(arg0, s32 *, 0x30) = arg3;
    cw = D_800736D0[arg2].w;
    ch = D_800736D0[arg2].h;
    w = ch * 2 + len * cw;
    h = ch + (u32)(cw + ch) * arg3;
    Window_SetRect(arg0, (0x274 - w) / 2, (0x19C - h) / 2 + 0x38, w + 0xC, h + 0xC);
    M2C_FIELD(arg0, s32 *, 0x20) = 0;
    M2C_FIELD(arg0, s32 *, 0x24) = 0;
    M2C_FIELD(arg0, s32 *, 0x14) = 6;
    M2C_FIELD(arg0, Rgba8002D188 *, 0x18) = *(Rgba8002D188 *)D_800736F8;
    M2C_FIELD(arg0, Rgba8002D188 *, 0x1C) = *(Rgba8002D188 *)D_800736FC;
    M2C_FIELD(arg0, s32 *, 0x28) = arg1;
}

extern Rgba8002D188 D_80073700[];
/**
 * Draws a blinking text box and its text.
 * Not reached in play (2026-11-13): did not run in a tour of the main menu, Pokédex, party, Lab,
 * registration, Free Battle setup and a COM battle (opening, a switch, running, a Pound turn).
 * @unverified Name and comment guessed from the code.
 */
void BlinkingTextBox_Draw(s32* arg0) {
    if (Window_DrawBlinkingFrame(arg0) != 0) {
        return;
    }
    func_8001AB6C();
    func_8001A384(D_800736D0[arg0[11]].unk8, 0);
    func_8001AA9C(D_80073700[0].r, D_80073700[0].g, D_80073700[0].b, D_80073700[0].a);
    Font_SetLineHeight(D_800736D0[arg0[11]].w + D_800736D0[arg0[11]].h);
    func_8001ABE8();
    func_8001AAE4(D_80073700[1].r, D_80073700[1].g, D_80073700[1].b, D_80073700[1].a);
    func_8001A944(arg0[0] + D_800736D0[arg0[11]].h + 6, arg0[1] + D_800736D0[arg0[11]].h + 6, arg0[10]);
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
 * Seen in play (2026-11-12) in いちらん page 2/3: フシギダネ's たいあたり (0x21) gave 0x20 and なきごえ (0x2D)
 * 0x2C; ヒトカゲ's ひっかく (0x0A) gave 9.
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

s32 func_8001FA8C(s32);

/**
 * Returns the display index of the species' type 1 (`arg1` 0) or type 2 (`arg1` 1); -1 for type 2 of a single-type species.
 * Seen in play (2026-11-12) in いちらん: it drives the タイプ1/タイプ2 columns. フシギダネ gave 0xB and 3 (くさ,
 * どく), ヒトカゲ 9 and -1, and ゼニガメ 0xA and -1. どく = 3 matches its 4th place in タイプであつめる.
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
    return func_8001FA8C(type);
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
    Ui_DrawTexturedFrameDecal(0x6E, 0x72, 0x1A4, 0x114, D_80073554);
    gSPDisplayList(gDisplayListHead++, D_80060270);
    func_80029028(0x74, 0x78, 0x198, 0x108, D_80073708);
    if (arg0 == 0) {
        func_8001AB6C();
        func_8001A384(0x10, 0);
        func_8001AA9C(0xFF, 0xFF, 0xFF, 0xFF);
        func_8001ABE8();
        func_8001AAE4(0xFF, 0xF1, 0x78, 0xFF);
        func_8001A944(0xEC, 0xA8, (s32)D_8007B950);
        func_8001AC3C();
        func_8001ABBC();
    } else if (arg0 == 2) {
        func_8001AB6C();
        func_8001A384(0x10, 0);
        func_8001AA9C(0xFF, 0xFF, 0xFF, 0xFF);
        func_8001ABE8();
        func_8001AAE4(0xFF, 0xF1, 0x78, 0xFF);
        func_8001A944(0xB0, 0xA8, (s32)D_8007B960);
        func_8001AC3C();
        func_8001ABBC();
    } else if (arg0 == 3) {
        func_8001AB6C();
        func_8001A384(0x10, 0);
        func_8001AA9C(0xFF, 0xFF, 0xFF, 0xFF);
        func_8001ABE8();
        func_8001AAE4(0xFF, 0xF1, 0x78, 0xFF);
        func_8001A944(0x80, 0x84, (s32)D_8007B97C);
        func_8001AC3C();
        func_8001ABBC();
    }
    if (arg0 != 0) {
        func_8001AB6C();
        func_8001A384(0x10, 0);
        func_8001AA9C(0xFF, 0xFF, 0xFF, 0xFF);
        func_8001ABE8();
        func_8001AAE4(0xFF, 0xF1, 0x78, 0xFF);
        func_8001A944(0x128, 0xF0, (s32)D_8007B9BC);
        func_8001AC3C();
        func_8001AA9C(((u8*)&D_800734A8)[0], ((u8*)&D_800734A8)[1], ((u8*)&D_800734A8)[2], ((u8*)&D_800734A8)[3]);
        Font_SetLineHeight(0x24);
        func_8001A944(0x80, 0xF0, (s32)D_8007B9D0);
        func_8001ABBC();
    }
    func_80006780();
}

/*
 * func_8002D7D4
 *
 * Polling loop on arg0.  First func_80006780 (BgStage_AdvanceFrame, per
 * symbol_addrs.txt) is called once.  Then, repeatedly:
 *
 *   - state starts at 2.  Save_DrawReportResultWindow(state) is called and
 *     GbSave_PollCartRemoval(arg0) (GbSave_PollCartRemoval, per symbol_addrs.txt) is
 *     polled; if the poll returns 1 or 3, state becomes 1 or 3 for the next
 *     round.  This repeats until the poll returns 2.
 *   - Save_DrawReportResultWindow(0) is called twice.
 *   - The whole sequence is repeated while func_8002207C(arg0)
 *     (GbSave_RebuildAndWriteSave) returns 0.
 *
 * What Save_DrawReportResultWindow does with its argument is not established, so the
 * values 1, 2 and 3 are not given names in the code.
 *
 * Context from the Stadium 1 decomp (not proof for this ROM): the same
 * loop exists there as LabUI_ShowSavingPrompt, where the polled function
 * GbSave_PollCartRemoval returns 0 when it has nothing to report yet, 1
 * while it waits for the cart to be put back, 2 once the pak is verified as
 * the same one, and 3 if a pak was reinitialised but is not the expected one; the loop
 * shows a saving-status message for the latest value.  Zero's loop differs in
 * detail (it never maps 2 to 0, and it calls Save_DrawReportResultWindow(0) twice after the
 * inner loop instead of sending two null messages inside it).
 */
M2C_UNK func_80006780();                            /* extern */
s32 GbSave_PollCartRemoval(s32);                             /* extern */
s32 func_8002207C(s32);                             /* extern */
void Save_DrawReportResultWindow(s32);

void func_8002D7D4(s32 arg0) {
    s32 state;
    s32 result;

    func_80006780();
    do {
        state = 2;
        do {
            Save_DrawReportResultWindow(state);
            result = GbSave_PollCartRemoval(arg0);
            if (result == 1) {
                state = 1;
            } else if (result == 3) {
                state = 3;
            }
        } while (result != 2);
        Save_DrawReportResultWindow(0);
        Save_DrawReportResultWindow(0);
    } while (func_8002207C(arg0) == 0);
}
