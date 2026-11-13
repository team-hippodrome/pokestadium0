/* Stadium Zero fragment014_235D70. */
/* C ported from the Stadium 1 decomp: src/fragments/lab_pc/lab_pc_1B4EA0.c, src/fragments/lab_pc_icons/lab_pc_icons.c. */

#include "fragments/lab_pc_icons/lab_pc_icons.h"
#include "display_object_textures.h"
#include "poke_icon.h"
#include "graphics_textures.h"
#include "ui_graphics.h"
#include "gb_data.h"
#include "table_view.h"
#include "text_system.h"
#include "gb_save.h"
#include "jpeg_stream.h"
#include "audio_sfx.h"
#include "memmap.h"
#include "memory.h"
#include "stage_loader.h"
#include "util.h"
#include "fragments/widget_tree/widget_tree.h"
#include "fragments/pokemon_lab_support/pokemon_lab_support.h"
typedef struct unk_D_88605B00 {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
} unk_D_88605B00;

#include "fragments/lab_pc/lab_pc.h"
#include "graphics_textures.h"
#include "input.h"
#include "gb_data.h"
#include "pokemon_stats.h"
#include "save_data.h"
#include "game_state.h"
#include "table_view.h"
#include "text_system.h"
#include "gb_save.h"
#include "audio_sfx.h"
#include "hal_libc.h"
#include "memmap.h"
#include "memory.h"
#include "stage_loader.h"
typedef struct unk_D_88218060 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ Color_RGBA8* unk_04;
} unk_D_88218060;
typedef struct unk_D_88218070 {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ u8* unk_08;
    /* 0x0C */ s16 unk_0C;
    /* 0x10 */ Color_RGBA8* unk_10;
} unk_D_88218070;

#include "m2c_macros.h"

void func_8800075C(void);
void func_88000FE0(void);

extern Color_RGBA8 D_88001FD0;
void Ui_FillRectHighlighted(s32, s32, s32, s32, Color_RGBA8);
void Font_SetColorForFlags(s32);

/**
 * Draws one wide menu row label with the selection highlight.
 * Not reached in play (2026-11-13): did not run in a tour of the main menu, Pokédex, party, Lab,
 * registration, Free Battle setup and a COM battle (opening, a switch, running, a Pound turn).
 * @unverified Name and comment guessed from the code.
 */
void MainMenu_DrawMenuRow(s32 arg0, s32 arg1, char* arg2, s32 arg3, s32 arg4) {
    if (arg4 & 8) {
        Ui_FillRectHighlighted(arg0 + 3, arg1 + 3, 0x162, 0x1E, D_88001FD0);
    }
    Font_BeginTranslucentTextRendering();
    Font_SetColorForFlags(arg4);
    Font_SetActive(0x10, 0);
    Font_Printf(arg0 + 0xC, arg1 + 6, arg2);
    Font_EndTexturedTextRendering();
}

void Window_SetRect(s8* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
M2C_UNK func_80027804();
M2C_UNK Menu_Init();
extern s8 D_88001FD4[];
typedef struct Rgba880002D8 { u8 r, g, b, a; } Rgba880002D8;
extern u8 D_88001FE0[];
extern u8 D_88001FE4[];
/**
 * Sets up the prompt window (372x274) and its inner menu.
 * Not reached in play (2026-11-13): did not run in a tour of the main menu, Pokédex, party, Lab,
 * registration, Free Battle setup and a COM battle (opening, a switch, running, a Pound turn).
 * @unverified Name and comment guessed from the code.
 */
M2C_UNK MainMenu_InitPromptWindow(s32 arg0, s32 arg1, s32 arg2) {
    s8 *obj = (s8 *)arg0;
    s32 pad; // FAKE: stack padding

    Window_SetRect(obj, arg1, arg2, 0x174, 0x112);
    M2C_FIELD(obj, s32 *, 0x24) = 0;
    M2C_FIELD(obj, s32 *, 0x20) = 0;
    M2C_FIELD(obj, s32 *, 0x28) = 0;
    M2C_FIELD(obj, s32 *, 0x14) = 0x1001;
    Window_SetRect(obj + 0x2C, M2C_FIELD(obj, s32 *, 0) + 6, M2C_FIELD(obj, s32 *, 4) + 6, M2C_FIELD(obj, s32 *, 8) - 0xC, 0x88);
    M2C_FIELD(obj, s32 *, 0x40) = 6;
    M2C_FIELD(obj, Rgba880002D8 *, 0x44) = *(Rgba880002D8 *)D_88001FE0;
    M2C_FIELD(obj, Rgba880002D8 *, 0x48) = *(Rgba880002D8 *)D_88001FE4;
    func_80027804(obj + 0x70, D_88001FD4, 3, 3);
    Menu_Init(obj + 0x4C, obj + 0x70, obj + 0x7C, MainMenu_DrawMenuRow, 0x168, 0x24);
    M2C_FIELD(obj, s32 *, 0x6C) |= 0x10000;
}

s32 func_8002AE6C();
extern u8 D_800734A8[4];
extern u8 D_8007356C[];
extern Gfx D_80060270[];
extern Color_RGBA8 D_88001FE8;
extern char D_88002308[];
extern char D_88002328[];
void Ui_DrawTexturedDivider(s32, s32, s32, u8 *);
void func_80029028(s32, s32, s32, s32, Color_RGBA8);
void Window_DrawFrame(void*);
void Menu_DrawItems(s8 *, s32, s32, s32, s32);
/**
 * Draws トーナメントのつづきをする？ (Continue the tournament?).
 * Not reached in play (2026-11-13): did not run in a tour of the main menu, Pokédex, party, Lab,
 * registration, Free Battle setup and a COM battle (opening, a switch, running, a Pound turn).
 * @unverified Name and comment guessed from the code.
 */
void MainMenu_DrawContinueTournamentPrompt(s8* arg0) {
    if (func_8002AE6C() == 0) {
        Window_DrawFrame(arg0 + 0x2C);
        Ui_DrawTexturedDivider(M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, s32 *, 4) + 0x8D, M2C_FIELD(arg0, s32 *, 8), D_8007356C);
        gSPDisplayList(gDisplayListHead++, D_80060270);
        func_80029028(M2C_FIELD(arg0, s32 *, 0) + 6, M2C_FIELD(arg0, s32 *, 4) + 0x94, M2C_FIELD(arg0, s32 *, 8) - 0xC, 0x78, D_88001FE8);
        Font_BeginTranslucentTextRendering();
        Font_SetActive(0x10, 0);
        Gfx_SetEnvColor(0xFF, 0xFF, 0xFF, 0xFF);
        Font_EnableTwoCycleTexturing();
        Gfx_SetPrimColor(0xFF, 0x96, 0x96, 0xFF);
        Font_Printf(M2C_FIELD(arg0, s32 *, 0x2C) + 0xC, M2C_FIELD(arg0, s32 *, 0x30) + 0xC, D_88002308);
        Font_DisableTwoCycleTexturing();
        Font_SetActive(8, 0);
        Gfx_SetEnvColor(D_800734A8[0], D_800734A8[1], D_800734A8[2], D_800734A8[3]);
        Font_SetLineHeight(0x1C);
        Font_Printf(M2C_FIELD(arg0, s32 *, 0x2C) + 0x34, M2C_FIELD(arg0, s32 *, 0x30) + 0x30, D_88002328);
        Font_EndTexturedTextRendering();
        Menu_DrawItems(arg0 + 0x4C, M2C_FIELD(arg0, s32 *, 0) + 6, M2C_FIELD(arg0, s32 *, 4) + 0x9A, 0xFFEF, 0);
    }
}

s32 Menu_UpdateCursor(s8*);
s32 func_8002BC14(s32);
extern s32 D_800603C0;

/**
 * Moves the prompt cursor while the window is open. Returns the 1-based choice on confirm, otherwise 0.
 * Not reached in play (2026-11-13): did not run in a tour of the main menu, Pokédex, party, Lab,
 * registration, Free Battle setup and a COM battle (opening, a switch, running, a Pound turn).
 * @unverified Name and comment guessed from the code.
 */
s32 MainMenu_UpdatePromptCursor(s8* arg0) {
    s32 ret = 0;

    switch (M2C_FIELD(arg0, s32*, 0x28)) {
        case 1:
        case 2:
            break;
        default:
            return 0;
    }
    if (Menu_UpdateCursor(arg0 + 0x4C) == 0) {
        if (func_8002BC14(D_800603C0) == 1) {
            ret = M2C_FIELD(arg0, s32*, 0x54) + 1;
        }
    }
    return ret;
}

extern Gfx D_80073450[];
void func_8001B884(s32, s32, s32, s32, u8*, s32, s32);
/**
 * Draws an IA image at (x, y) in strips with primitive alpha `alpha`.
 * Seen in play (2026-11-12) on the main menu: it drew the 0x60 x 0x40 item pictures at x 0x59
 * (せいとん column) and 0x1C7 (いちらん column).
 */
void MainMenu_DrawImageWithAlpha(s32 x, s32 y, s32 w, s32 h, s32 stride, u8* pixels, s32 alpha) {
    s32 rows;
    s32 n;
    s32 max_rows;
    s32 curY;
    u8* pix;

    gSPDisplayList(gDisplayListHead++, D_80073450);
    gDPSetCombineLERP(gDisplayListHead++, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0);
    gDPSetPrimColor(gDisplayListHead++, 0, 0, 255, 255, 255, alpha);
    rows = h;
    pix = pixels;
    curY = y;
    if (rows > 0) {
        max_rows = 0x1000 / (stride * 2);
        do {
            if (max_rows < rows) {
                n = max_rows;
            } else {
                n = rows;
            }
            func_8001B884(x, curY, w, n, pix, stride, 0);
            rows -= n;
            curY += n;
            pix += n * stride * 2;
        } while (rows > 0);
    }
}

void func_8800075C(void) {
}

extern Gfx D_80073450[];
void Ui_DrawTexturedFrame(s32, s32, s32, s32, u8*);
/**
 * Appends a call of display list D_80073450, a gDPSetCombineMode(G_CC_MODULATEIA_PRIM,
 * G_CC_MODULATEIA_PRIM) and a white primitive color with alpha arg5 to the current display
 * list, then forwards its first five arguments unchanged to Ui_DrawTexturedFrame (compare
 * Ui_DrawTexturedFrameDecal, which does the same with a decal combiner and no primitive color).
 * Seen in play (2026-11-13) (tour of menus and a COM battle): ran in the main menu, the Pokédex,
 * the party screen, the Lab list, Lab sort, registration, the Lab PC and Free Battle setup.
 * @unverified Name guessed from the code; comment kept.
 */
void MainMenu_DrawTexturedFrameWithAlpha(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8* arg4, s32 arg5) {
    gSPDisplayList(gDisplayListHead++, D_80073450);
    gDPSetCombineMode(gDisplayListHead++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
    gDPSetPrimColor(gDisplayListHead++, 0, 0, 255, 255, 255, arg5);
    Ui_DrawTexturedFrame(arg0, arg1, arg2, arg3, arg4);
}

extern u8 D_88002034[][0x18];
typedef struct unk_88002034 { s32 x; s32 y; s32 w; s32 h; s32 stride; u8* pixels; } unk_88002034;
typedef struct unk_8800210C { s32 x; s32 y; s32 w; s32 h; } unk_8800210C;
extern Color_RGBA8 D_88002010[];
extern unk_8800210C D_8800210C[];
extern unk_8800210C D_8800219C[];
extern Gfx D_80073480[];
extern Color_RGBA8 D_80073520;
extern u8 D_80073554[];
void Ui_FillRectPrimColor(s32, s32, s32, s32, Color_RGBA8);
void Ui_DrawRoundedFrame(s32, s32, s32, s32, Color_RGBA8);
void func_8001AB6C(void);
void func_8001AA9C(u8, u8, u8, u8);
void func_8001A384(s32, s32);
void func_8001A944(s32, s32, s32);
void func_8001ABBC(void);

// D_88002034 is declared as raw bytes in this file; each 0x18 byte row is one unk_88002034.
#define ICON(i) (((unk_88002034*)D_88002034)[i])

/**
 * Draws one main menu item with its frame, fading it by `scale` (capped at 0.3 when disabled).
 * Seen in play: runs every frame for the main menu's item panels.
 */
void MainMenu_DrawItem(s32 a0, s32 a1, s32 a2, s32 mode, s32 flags, f32* scale) {
    Color_RGBA8 frame_color;
    Color_RGBA8 text_color;
    f32 fade;
    f32 value;
    s32 alpha;

    value = *scale;
    // the fade is capped at 0.3 when bit 0 is set
    if ((flags & 1) && (value > 0.3f)) {
        fade = 0.3f;
    } else {
        fade = value;
    }
    if (mode == 1) {
        return;
    }
    alpha = (s32)(fade * 255.0f);
    MainMenu_DrawImageWithAlpha(D_8800210C[mode].x + ICON(mode).x, D_8800210C[mode].y + ICON(mode).y, ICON(mode).w, ICON(mode).h,
                  ICON(mode).stride, ICON(mode).pixels, alpha);
    frame_color = D_88002010[mode];
    frame_color.a = alpha;
    if (D_8800219C[mode].h) {
        gSPDisplayList(gDisplayListHead++, D_80073480);
        Ui_FillRectPrimColor(D_8800210C[mode].x + 6, D_8800210C[mode].y + 6, D_8800210C[mode].w - 12, 4, frame_color);
        Ui_FillRectPrimColor(D_8800210C[mode].x + 6, D_8800210C[mode].y + 6, 4, D_8800219C[mode].y - 10, frame_color);
        Ui_FillRectPrimColor(D_8800210C[mode].x + D_8800210C[mode].w - 10, D_8800210C[mode].y + 6, 4, D_8800219C[mode].y - 10, frame_color);
        Ui_FillRectPrimColor(D_8800210C[mode].x + 6, D_8800210C[mode].y + D_8800219C[mode].y - 4, D_8800210C[mode].w - 12, 0x20, frame_color);
    } else {
        gSPDisplayList(gDisplayListHead++, D_80073480);
        Ui_FillRectPrimColor(D_8800210C[mode].x + 6, D_8800210C[mode].y + 6, D_8800210C[mode].w - 12, 8, frame_color);
        Ui_FillRectPrimColor(D_8800210C[mode].x + 6, D_8800210C[mode].y + D_8800210C[mode].h - 14, D_8800210C[mode].w - 12, 8, frame_color);
        Ui_FillRectPrimColor(D_8800210C[mode].x + 6, D_8800210C[mode].y + 14, 9, D_8800210C[mode].h - 28, frame_color);
        Ui_FillRectPrimColor(D_8800210C[mode].x + D_8800210C[mode].w - 15, D_8800210C[mode].y + 14, 9, D_8800210C[mode].h - 28, frame_color);
    }
    MainMenu_DrawTexturedFrameWithAlpha(D_8800210C[mode].x, D_8800210C[mode].y, D_8800210C[mode].w, D_8800210C[mode].h, D_80073554, alpha);
    if (D_8800219C[mode].h) {
        text_color = *(Color_RGBA8*)D_800734A8;
        text_color.a = alpha;
        func_8001AB6C();
        func_8001AA9C(text_color.r, text_color.g, text_color.b, text_color.a);
        func_8001A384(0x10, D_8800219C[mode].w);
        func_8001A944(D_8800210C[mode].x + D_8800219C[mode].x, D_8800210C[mode].y + D_8800219C[mode].y, D_8800219C[mode].h);
        func_8001ABBC();
    }
    if (flags & 2) {
        Ui_DrawRoundedFrame(D_8800210C[mode].x - 4, D_8800210C[mode].y - 4, D_8800210C[mode].w + 8, D_8800210C[mode].h + 8, D_80073520);
    }
}

void func_80027410(void*, void*, s32, s32, s32);
void GridMenu_Init(void*, void*, void*, void*, s32, s32, s32);
s32 func_800226BC(s32, s32, s32);
s32 func_80025BD8();
void MainMenu_DrawItem();
/**
 * Sets up the main menu item list and enables the items for mode `arg2`.
 * Seen in play (2026-11-13) ran once each time the main menu came back from another screen, before
 * its eight items were drawn.
 */
M2C_UNK MainMenu_InitItemList(u8* arg0, s32 arg1, s32 arg2) {
    M2C_FIELD(arg0, s32*, 4) = 0;
    func_80027410(arg0 + 0x1E0, arg0 + 0x30, 0x30, 9, 9);
    GridMenu_Init(arg0 + 8, arg0 + 0x1E0, arg0 + 0x1F0, MainMenu_DrawItem, 3, 0, 0);
    M2C_FIELD(arg0, s32*, 0x10) = arg1;
    M2C_FIELD(arg0, u16**, 0xC)[1] |= 1;
    switch (arg2) {
        case 4:
            M2C_FIELD(arg0, u16**, 0xC)[0] |= 1;
            M2C_FIELD(arg0, u16**, 0xC)[2] |= 1;
            M2C_FIELD(arg0, u16**, 0xC)[3] |= 1;
            M2C_FIELD(arg0, u16**, 0xC)[5] |= 1;
            M2C_FIELD(arg0, u16**, 0xC)[6] |= 1;
            M2C_FIELD(arg0, u16**, 0xC)[8] |= 1;
            break;
        case 3:
            M2C_FIELD(arg0, u16**, 0xC)[0] |= 1;
            M2C_FIELD(arg0, u16**, 0xC)[2] |= 1;
            M2C_FIELD(arg0, u16**, 0xC)[3] |= 1;
            M2C_FIELD(arg0, u16**, 0xC)[5] |= 1;
            M2C_FIELD(arg0, u16**, 0xC)[8] |= 1;
            break;
        case 2:
            M2C_FIELD(arg0, u16**, 0xC)[0] |= 1;
            M2C_FIELD(arg0, u16**, 0xC)[2] |= 1;
            M2C_FIELD(arg0, u16**, 0xC)[3] |= 1;
            break;
        case 1:
            M2C_FIELD(arg0, u16**, 0xC)[0] |= 1;
            M2C_FIELD(arg0, u16**, 0xC)[2] |= 1;
            break;
    }
    if ((arg2 == 1 || arg2 == 2) && func_800226BC(0x20, func_80025BD8(), 0) == 0) {
        M2C_FIELD(arg0, u16**, 0xC)[5] |= 1;
    }
}

/**
 * Advances the item list fade timer and its state (fade in, shown, fade out, done).
 * Seen in play (2026-11-13) ran every frame on the main menu while the cursor moved between items.
 */
s32 MainMenu_StepItemFade(s8 *arg0) {
    s32 temp_v0;
    s32 var_v1;

    temp_v0 = M2C_FIELD(arg0, s32 *, 4);
    var_v1 = 1;
    if (temp_v0 >= 0x17) {
        M2C_FIELD(arg0, s32 *, 0) = 4;
        return 1;
    }
    if (temp_v0 >= 0xD) {
        M2C_FIELD(arg0, s32 *, 0) = 3;
        M2C_FIELD(arg0, s32 *, 4) = (s32) (temp_v0 + 1);
    } else if (temp_v0 < 0xA) {
        M2C_FIELD(arg0, s32 *, 0) = 0;
        M2C_FIELD(arg0, s32 *, 4) = (s32) (temp_v0 + 1);
    } else {
        var_v1 = 0;
        if (temp_v0 < 0xC) {
            M2C_FIELD(arg0, s32 *, 0) = 1;
            M2C_FIELD(arg0, s32 *, 4) = (s32) (temp_v0 + 1);
        } else {
            M2C_FIELD(arg0, s32 *, 0) = 2;
        }
    }
    return var_v1;
}

extern u8 D_05018868[];
void GridMenu_DrawInlineItems(s8*, s32, s32, s32, f32*);

/**
 * Draws the main menu items with the current fade.
 * Seen in play: runs every frame while the main menu's item panels (ずかん, バトル, てもち, GB, とうろく, OFF)
 * are drawn.
 */
s32 MainMenu_DrawItemList(s8* arg0, s32 arg1) {
    f32 alpha;
    s32 ret = 1;
    s32 color = 0xFFED;
    s32 n;

    MainMenu_StepItemFade(arg0);
    switch (M2C_FIELD(arg0, u32*, 0)) {
        case 4:
            return 1;
        case 3:
            n = 0x17 - M2C_FIELD(arg0, s32*, 4);
            alpha = (f32)n / 10.0f;
            break;
        case 0:
            n = M2C_FIELD(arg0, s32*, 4) - 1;
            alpha = (f32)n / 10.0f;
            break;
        case 1:
        case 2:
            ret = 0;
            alpha = 1.0f;
            color = arg1 | 0xFFED;
            break;
    }
    GridMenu_DrawInlineItems(arg0 + 8, 0, 0, color, &alpha);
    MainMenu_DrawImageWithAlpha(0xE6, 0x56, 0xC8, 0x64, 0xC8, D_05018868, 255.0f * alpha);
    return ret;
}

void func_88000FE0(void) {
}

void Window_InitLabeled(s8* arg0, s32 arg1, s32 arg2, s32 arg3, Color_RGBA8 arg4, char* arg5);
M2C_UNK func_8000B2F4(s32);
extern u8 D_8800222C[];
extern char D_880023C0[];
extern char D_880023C8[];
/**
 * Sets up the message window (532x138) with its color and text.
 * Seen in play: A on バトル opens its window (「コンピュータや ともだちと たいせん する。 はいりますか？ はい いいえ」) and runs
 * this.
 */
void MainMenu_InitMessageWindow(s8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, Color_RGBA8 arg6, s32 arg7) {
    Window_SetRect(arg0, arg1, arg2, 0x214, 0x8A);
    M2C_FIELD(arg0, s32 *, 0x24) = 0;
    M2C_FIELD(arg0, s32 *, 0x20) = 0;
    M2C_FIELD(arg0, s32 *, 0x28) = 0;
    M2C_FIELD(arg0, s32 *, 0x14) = 0x800;
    M2C_FIELD(arg0, Color_RGBA8 *, 0x18) = arg6;
    M2C_FIELD(arg0, s32 *, 0x20) = arg3;
    M2C_FIELD(arg0, s32 *, 0x34) = arg4;
    M2C_FIELD(arg0, s32 *, 0x38) = arg5;
    Window_InitLabeled(arg0 + 0x3C, M2C_FIELD(arg0, s32 *, 0) + 0x165, M2C_FIELD(arg0, s32 *, 4) + 0x66, 0x48, *(Color_RGBA8 *)D_8800222C, D_880023C0);
    M2C_FIELD(arg0, s32 *, 0x68) = 0xA;
    M2C_FIELD(arg0, s32 *, 0x70) = 0xC;
    Window_InitLabeled(arg0 + 0x78, M2C_FIELD(arg0, s32 *, 0) + 0x1BA, M2C_FIELD(arg0, s32 *, 4) + 0x66, 0x48, *(Color_RGBA8 *)D_8800222C, D_880023C8);
    M2C_FIELD(arg0, s32 *, 0xBC) = 2;
    M2C_FIELD(arg0, s32 *, 0xB8) = 0;
    M2C_FIELD(arg0, s32 *, 0xB4) = D_800603C0;
    func_8000B2F4(D_800603C0);
    M2C_FIELD(arg0, Color_RGBA8 *, 0x2C) = arg6;
    M2C_FIELD(arg0, s32 *, 0xC0) = arg7;
}

s32 func_8002AE6C();
extern u8 D_800734A8[4];
extern u8 D_8007356C[];
void Ui_DrawTexturedDivider(s32, s32, s32, u8 *);
void Window_DrawLabeled(s8 *, s32);
void MainMenu_DrawImageWithAlpha(s32, s32, s32, s32, s32, u8*, s32);
/**
 * Draws the message window: divider and text.
 * Seen in play: draws the item window opened by A (「…はいりますか？ はい いいえ」).
 */
void MainMenu_DrawMessageWindow(s8 *arg0) {
    s32* p;

    if (func_8002AE6C() == 0) {
        Ui_DrawTexturedDivider(M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, s32 *, 4) + 0x59, M2C_FIELD(arg0, s32 *, 8), D_8007356C);
        Font_BeginTranslucentTextRendering();
        Gfx_SetEnvColor(D_800734A8[0], D_800734A8[1], D_800734A8[2], D_800734A8[3]);
        Font_SetActive(8, 0);
        Font_SetLineHeight(0x1C);
        Font_Printf(M2C_FIELD(arg0, s32 *, 0) + 0x8A, M2C_FIELD(arg0, s32 *, 4) + 0xA, M2C_FIELD(arg0, char **, 0x34));
        Font_Printf(M2C_FIELD(arg0, s32 *, 0) + 0xBC, M2C_FIELD(arg0, s32 *, 4) + 0x68, M2C_FIELD(arg0, char **, 0x38));
        Font_EndTexturedTextRendering();
        Window_DrawLabeled(arg0 + 0x3C, (M2C_FIELD(arg0, s32 *, 0xB8) == 0) ? 2 : 0);
        Window_DrawLabeled(arg0 + 0x78, (M2C_FIELD(arg0, s32 *, 0xB8) == 1) ? 2 : 0);
        p = M2C_FIELD(arg0, s32 **, 0xC0);
        MainMenu_DrawImageWithAlpha(M2C_FIELD(arg0, s32 *, 0) + 0xA, M2C_FIELD(arg0, s32 *, 4) + 0xA, p[2], p[3], p[4], (u8*)p[5], 0xFF);
    }
}

s32 func_8002B390(s8*);
s32 func_8002BC14(s32);
extern s32 D_800603C0;

/**
 * Handles input on the message window while it is open.
 * Seen in play: runs while that window is open; D-Right moves the cursor between はい and いいえ.
 */
s32 MainMenu_UpdateMessageWindow(s8* arg0) {
    s32 ret = 0;

    switch (M2C_FIELD(arg0, s32*, 0x28)) {
        case 1:
        case 2:
            break;
        default:
            return 0;
    }
    if (func_8002B390(arg0 + 0xB4) == 0) {
        ret = func_8002BC14(D_800603C0);
        if (ret == 1) {
            switch (M2C_FIELD(arg0, s32*, 0xB8)) {
                case 0:
                    ret = 1;
                    break;
                case 1:
                    ret = -1;
                    break;
            }
        }
    }
    return ret;
}

extern Color_RGBA8 D_88002230;
void Window_SetRect(s8* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

/**
 * Initialises the object arg0 (size and layout not established; same
 * family as FreeBattle_InitLevelSumWarning). Calls Window_SetRect(arg0, arg1, arg2, 0x224, 0x60),
 * clears the words at 0x20, 0x24 and 0x28, sets the word at 0x14 to 0x2800,
 * copies the 4-byte color D_88002230 to arg0 + 0x18, then stores arg3 at 0x20
 * (replacing the zero) and arg4 at 0x30.
 * Not reached in play (2026-11-13): did not run in a tour of the main menu, Pokédex, party, Lab,
 * registration, Free Battle setup and a COM battle (opening, a switch, running, a Pound turn).
 * @unverified Name guessed from the code; comment kept.
 */
void MainMenu_InitTextWindow(s8* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    Window_SetRect(arg0, arg1, arg2, 0x224, 0x60);
    M2C_FIELD(arg0, s32*, 0x24) = 0;
    M2C_FIELD(arg0, s32*, 0x20) = 0;
    M2C_FIELD(arg0, s32*, 0x28) = 0;
    M2C_FIELD(arg0, s32*, 0x14) = 0x2800;
    M2C_FIELD(arg0, Color_RGBA8*, 0x18) = D_88002230;
    M2C_FIELD(arg0, s32*, 0x20) = arg3;
    M2C_FIELD(arg0, s32*, 0x30) = arg4;
}

s32 func_8002AE6C();
extern u8 D_800734A8[4];
/**
 * Draws the text window's text.
 * Seen in play: runs while the main menu shows the 「GBのカートリッジがない」 warning window at the top.
 */
void MainMenu_DrawTextWindow(s8* arg0) {
    if (func_8002AE6C() == 0) {
        Font_BeginTranslucentTextRendering();
        Gfx_SetEnvColor(D_800734A8[0], D_800734A8[1], D_800734A8[2], D_800734A8[3]);
        Font_SetActive(8, 0);
        Font_SetLineHeight(0x1C);
        Font_Printf(M2C_FIELD(arg0, s32*, 0) + 0xA, M2C_FIELD(arg0, s32*, 4) + 0xA, M2C_FIELD(arg0, char**, 0x30));
        Font_EndTexturedTextRendering();
    }
}

M2C_UNK MainMenu_InitPromptWindow(s32, M2C_UNK, M2C_UNK);       /* extern */
M2C_UNK MainMenu_InitItemList(u8 *, s32, s32);            /* extern */
extern u8 D_800AF985;
extern M2C_UNK D_88002240;

/**
 * The caller MainMenu_LoadGbSaveSummary passes a fourth argument, &D_88002B20, which this function
 * never reads. It is declared so that call compiles; the empty `if (arg3)` only stops
 * the compiler from spilling the unused argument, which the ROM does not do.
 * Seen in play (2026-11-13) ran once each time the main menu came back from another screen, after
 * MainMenu_LoadGbSaveSummary.
 */
void MainMenu_InitScreen(u8 *arg0, s32 arg1, s32 arg2, s32 *arg3) {
    s32 temp_v0;

    if (arg3) {  // karodo
    }

    if (D_800AF985 & 1) {
        MainMenu_InitPromptWindow(arg0 + 0x32C, 0x82, 0x6E);
        M2C_FIELD(arg0, s32 *, 0) = 1;
    } else {
        M2C_FIELD(arg0, s32 *, 0) = 2;
    }
    M2C_FIELD(arg0, s32 *, 4) = 0;
    MainMenu_InitItemList(arg0 + 0x2C, arg2, arg1);
    M2C_FIELD(arg0, s32 *, 0xC) = arg1;
    if (arg1 > 0) {
        temp_v0 = arg1 * 4;
        MainMenu_InitTextWindow(arg0 + 0x2F8, 0x2E, 0x53, *((M2C_UNK*)((u8*)&D_88002230 + temp_v0)), *((M2C_UNK*)((u8*)&D_88002240 + temp_v0))); // FAKE: decomp slop, raw pointer casts stand in for struct fields
    }
}

void BgStage_DrawFrame(void);                            /* extern */
M2C_UNK Ui_DrawTintedScreenBackground(M2C_UNK, M2C_UNK, u8, u8, s32); /* extern */
void MainMenu_DrawContinueTournamentPrompt(s8 *);
M2C_UNK MainMenu_DrawItemList(s8 *, M2C_UNK);             /* extern */
void MainMenu_DrawMessageWindow(s8 *);
extern M2C_UNK D_88002254;

/**
 * Draws the main menu for its current state, including the continue-tournament prompt.
 * Seen in play: runs every frame on the メインメニュー screen.
 */
void MainMenu_DrawScreen(s8 *arg0) {
    s32 temp_v0;

    BgStage_DrawFrame();
    Ui_DrawTintedScreenBackground(0x38, 0x1E0, M2C_FIELD(&D_88002254, u8 *, 0), M2C_FIELD(&D_88002254, u8 *, 1), (s32) M2C_FIELD(&D_88002254, u8 *, 2));
    temp_v0 = M2C_FIELD(arg0, s32 *, 0);
    switch (temp_v0) {                              /* irregular */
    case 1:
        MainMenu_DrawItemList(arg0 + 0x2C, 0);
        MainMenu_DrawContinueTournamentPrompt(arg0 + 0x32C);
        return;
    case 2:
        MainMenu_DrawItemList(arg0 + 0x2C, 2);
        if (M2C_FIELD(arg0, s32 *, 0xC) > 0) {
            MainMenu_DrawTextWindow(arg0 + 0x2F8);
            return;
        }
        return;
    case 3:
        MainMenu_DrawItemList(arg0 + 0x2C, 2);
        MainMenu_DrawMessageWindow(arg0 + 0x234);
        break;
    }
}

extern s32 D_88002258[];
extern s32 D_8800227C[];
extern s32 D_880022A0[];
extern Color_RGBA8 D_88001FEC[];
extern u8 D_88002034[][0x18];
s32 GridMenu_UpdateCursorSkipDisabled(s8*);
void func_800245E0(s32, s32);
s32 MainMenu_LoadSelectedFragment(s32);
/**
 * Runs the main menu screen's state machine for one frame and returns the chosen item.
 * Seen in play (2026-11-13) ran every frame while the main menu was up and the cursor moved between
 * its items.
 */
s32 MainMenu_UpdateScreen(s8* arg0) {
    s32 ret = 0;
    s32 idx;
    s32 dir;

    switch (M2C_FIELD(arg0, s32*, 0)) {
        case 1:
            if (M2C_FIELD(arg0, s32*, 4) == 4 && M2C_FIELD(arg0, s32*, 0x2C) == 4) {
                ret = M2C_FIELD(arg0, s32*, 8);
            } else if (M2C_FIELD(arg0, s32*, 4) == 2 && M2C_FIELD(arg0, s32*, 0x354) == 4) {
                M2C_FIELD(arg0, s32*, 0) = M2C_FIELD(arg0, s32*, 4);
                M2C_FIELD(arg0, s32*, 4) = 0;
            } else {
                switch (MainMenu_UpdatePromptCursor(arg0 + 0x32C)) {
                    case 1:
                        func_8003F6AC(0x1E);
                        gSessionContext.sessionFlags |= 2;
                        M2C_FIELD(arg0, s32*, 8) = 0x8050;
                        M2C_FIELD(arg0, s32*, 0x350) = 7;
                        M2C_FIELD(arg0, s32*, 4) = 4;
                        M2C_FIELD(arg0, s32*, 0x30) = 0xD;
                        break;
                    case 2:
                        func_8003F6AC(3);
                        gSessionContext.sessionFlags &= ~1;
                        M2C_FIELD(arg0, s32*, 0x350) = 7;
                        M2C_FIELD(arg0, s32*, 4) = 2;
                        break;
                    case 3:
                        func_8003F6AC(0x1F);
                        func_800245E0(0x15, 0);
                        gSessionContext.sessionFlags &= ~1;
                        M2C_FIELD(arg0, s32*, 0x350) = 7;
                        M2C_FIELD(arg0, s32*, 4) = 2;
                        break;
                }
            }
            break;
        case 2:
            if (GridMenu_UpdateCursorSkipDisabled(arg0 + 0x34) == 0) {
                dir = func_8002BC14(D_800603C0);
                if (dir == -1) {
                    func_8003F6AC(8);
                } else if (dir == 1) {
                    func_8003F6AC(2);
                    M2C_FIELD(arg0, s32*, 0) = 3;
                    idx = M2C_FIELD(arg0, s32*, 0x3C);
                    MainMenu_InitMessageWindow(arg0 + 0x234, 0x36, 0x57, D_88002258[idx], D_8800227C[idx], D_880022A0[idx], D_88001FEC[idx], (s32)D_88002034[idx]);
                }
            }
            break;
        case 3:
            if (M2C_FIELD(arg0, s32*, 4) == 4 && M2C_FIELD(arg0, s32*, 0x2C) == 4) {
                ret = M2C_FIELD(arg0, s32*, 8);
            } else if (M2C_FIELD(arg0, s32*, 4) == 2 && M2C_FIELD(arg0, s32*, 0x25C) == 4) {
                M2C_FIELD(arg0, s32*, 0) = M2C_FIELD(arg0, s32*, 4);
                M2C_FIELD(arg0, s32*, 4) = 0;
            } else {
                dir = MainMenu_UpdateMessageWindow(arg0 + 0x234);
                if (dir == -1) {
                    func_8003F6AC(3);
                    M2C_FIELD(arg0, s32*, 0x258) = 7;
                    M2C_FIELD(arg0, s32*, 4) = 2;
                } else if (dir == 1) {
                    if (M2C_FIELD(arg0, s32*, 0x3C) == 7) {
                        func_8003F6AC(2);
                    } else {
                        func_8003F6AC(0x1C);
                    }
                    M2C_FIELD(arg0, s32*, 8) = MainMenu_LoadSelectedFragment(M2C_FIELD(arg0, s32*, 0x3C));
                    M2C_FIELD(arg0, s32*, 0x258) = 7;
                    M2C_FIELD(arg0, s32*, 4) = 4;
                    M2C_FIELD(arg0, s32*, 0x30) = 0xD;
                }
            }
            break;
    }
    return ret;
}

s32 func_80002D98(M2C_UNK);
M2C_UNK func_8000B2F4(s32);
u8 GbSave_GetSaveState(s32 arg0);
s32 GbSave_HasPokedex(s32);
s32 func_80022EDC(s32);
s32 func_80025BD8();
M2C_UNK func_80027FF8(M2C_UNK *, s32);
extern s32 D_800603C0;
extern s32 D_80073400;
extern s32 D_88002B00;
extern M2C_UNK D_88002B08;
extern s32 D_88002B20;

/**
 * Allocates the 0x3B0-byte object stored in D_88002B20 and starts it with
 * MainMenu_InitScreen. Steps:
 *  1. id = func_80025BD8(); D_88002B00 = id; if (D_88002B00 != -1) pass it with
 *     &D_88002B08 to func_80027FF8.
 *  2. Picks a mode from id: id == -1 -> 4; else GbSave_GetSaveState(id) != 0 -> 3;
 *     else GbSave_HasPokedex(id) == 0 -> 2; else func_80022EDC(id) == 0 -> 1; else 0.
 *  3. D_88002B20 = func_80002D98(0x3B0), then
 *     MainMenu_InitScreen(D_88002B20, mode, D_80073400 == 0 ? 4 : D_80073400 - 1, &D_88002B20)
 *     and finally func_8000B2F4(D_800603C0).
 * pad1/pad2 are unused locals that reproduce the retail 0x30-byte frame. What the id,
 * the modes and D_80073400 mean is not established.
 * Seen in play (2026-11-13) ran once each time the main menu came back from another screen; the
 * menu then showed the GB save summary bar (1P サトシ IDNo/12345).
 */
void MainMenu_LoadGbSaveSummary(void) {
    s32 pad1; // FAKE: stack padding
    s32 pad2; // FAKE: stack padding
    s32 sp24;
    s32 var_s0;

    var_s0 = 0;
    sp24 = func_80025BD8();
    D_88002B00 = sp24;
    if (D_88002B00 != -1) {
        func_80027FF8(&D_88002B08, D_88002B00);
    }
    if (sp24 == -1) {
        var_s0 = 4;
    } else if (GbSave_GetSaveState(sp24) != 0) {
        var_s0 = 3;
    } else if (GbSave_HasPokedex(sp24) == 0) {
        var_s0 = 2;
    } else if (func_80022EDC(sp24) == 0) {
        var_s0 = 1;
    }
    D_88002B20 = func_80002D98(0x3B0);
    MainMenu_InitScreen(D_88002B20, var_s0, (D_80073400 == 0) ? 4 : D_80073400 - 1, &D_88002B20);
    func_8000B2F4(D_800603C0);
}

/**
 * Returns `arg0` with its RGB scaled by `arg1` (alpha kept).
 * Seen in play (2026-11-13) ran as the main menu faded in (console reset, then N64 logo, opening,
 * title and main menu).
 * @unverified Name and comment guessed from the code.
 */
Color_RGBA8 MainMenu_ScaleColor(Color_RGBA8 arg0, f32 arg1) {
    Color_RGBA8 color;

    color.r = (s32)(arg0.r * arg1);
    color.g = (s32)(arg0.g * arg1);
    color.b = (s32)(arg0.b * arg1);
    color.a = arg0.a;
    return color;
}

M2C_UNK func_80005B98(M2C_UNK);
extern s32 D_880022C4;
/**
 * Draws the background, brightening it a little more each call.
 * Seen in play (2026-11-13) ran as the main menu faded in (console reset, then N64 logo, opening,
 * title and main menu).
 * @unverified Name and comment guessed from the code.
 */
s32 MainMenu_DrawFadeInBackground(s32 arg0) {
    Color_RGBA8 sp24;

    if (arg0 == 1) {
        /* Dead read of the counter; the retail code loads it here. */
        if (D_880022C4) {}  // karodo
        func_80005B98(1);
    }
    BgStage_DrawFrame();
    sp24 = MainMenu_ScaleColor(*(Color_RGBA8*)&D_88002254, D_880022C4 / 20.0);
    Ui_DrawTintedScreenBackground(0, 0x1E0, sp24.r, sp24.g, sp24.b);
    D_880022C4++;
    return 0;
}

void BgStage_DrawFrame(void);                            /* extern */
M2C_UNK Ui_DrawTintedScreenBackground(M2C_UNK, M2C_UNK, u8, u8, s32); /* extern */
extern M2C_UNK D_88002254;

/**
 * Draws the tinted main menu background.
 * Seen in play (2026-11-13) ran as the main menu faded in (console reset, then N64 logo, opening,
 * title and main menu).
 * @unverified Name and comment guessed from the code.
 */
s32 MainMenu_DrawBackground(s32 arg0) {
    BgStage_DrawFrame();
    Ui_DrawTintedScreenBackground(0, 0x1E0, M2C_FIELD(&D_88002254, u8 *, 0), M2C_FIELD(&D_88002254, u8 *, 1), (s32) M2C_FIELD(&D_88002254, u8 *, 2));
    return 0;
}

M2C_UNK GbSave_DrawSummaryBar(M2C_UNK, M2C_UNK *, M2C_UNK *, s32); /* extern */
extern M2C_UNK D_88002A8C;

/**
 * Draws the GB save summary bar sliding in from the top.
 * Seen in play (2026-11-13) ran as the main menu faded in (console reset, then N64 logo, opening,
 * title and main menu).
 * @unverified Name and comment guessed from the code.
 */
s32 MainMenu_DrawSummaryBarSlideIn(UNUSED s32 arg0) {
    static s32 D_880022C8;
    s32 sp1C;
    M2C_UNK *var_a1;

    sp1C = ((D_880022C8 * 0x38) / 6) - 0x38;
    BgStage_DrawFrame();
    if (D_88002B00 == -1) {
        var_a1 = NULL;
    } else {
        var_a1 = &D_88002B08;
    }
    GbSave_DrawSummaryBar(sp1C, var_a1, &D_88002A8C, D_88002B00);
    D_880022C8++;
    return 0;
}

void BgStage_DrawFrame(void);                            /* extern */
M2C_UNK GbSave_DrawSummaryBar(M2C_UNK, M2C_UNK *, M2C_UNK *, s32); /* extern */
extern M2C_UNK D_88002A9C;
extern s32 D_88002B00;
extern M2C_UNK D_88002B08;

/**
 * Draws the GB save summary bar.
 * Seen in play (2026-11-13) ran as the main menu faded in (console reset, then N64 logo, opening,
 * title and main menu).
 * @unverified Name and comment guessed from the code.
 */
s32 MainMenu_DrawSummaryBar(s32 arg0) {
    M2C_UNK *var_a1;

    BgStage_DrawFrame();
    if (D_88002B00 == -1) {
        var_a1 = NULL;
    } else {
        var_a1 = &D_88002B08;
    }
    GbSave_DrawSummaryBar(0, var_a1, &D_88002A9C, D_88002B00);
    return 0;
}

M2C_UNK func_80005B98(M2C_UNK);                     /* extern */
void BgStage_DrawFrame(void);                            /* extern */
M2C_UNK GbSave_DrawSummaryBar(M2C_UNK, M2C_UNK *, M2C_UNK *, s32); /* extern */
M2C_UNK Ui_DrawTintedScreenBackground(M2C_UNK, M2C_UNK, u8, u8, s32); /* extern */
extern M2C_UNK D_88002254;
extern M2C_UNK D_88002AAC;
extern s32 D_88002B00;
extern M2C_UNK D_88002B08;
extern s32 D_88002B20;

/**
 * Draws the GB save summary bar over the background.
 * Seen in play (2026-11-13) ran when the main menu came back with its top bar (1P サトシ IDNo/12345)
 * over the background.
 */
s32 MainMenu_DrawSummaryBarAndBackground(s32 arg0) {
    M2C_UNK *var_a1;

    if (arg0 == 1) {
        func_80005B98(0xF);
    }
    BgStage_DrawFrame();
    if (D_88002B00 == -1) {
        var_a1 = NULL;
    } else {
        var_a1 = &D_88002B08;
    }
    GbSave_DrawSummaryBar(0, var_a1, &D_88002AAC, D_88002B00);
    Ui_DrawTintedScreenBackground(0x38, 0x1E0, M2C_FIELD(&D_88002254, u8 *, 0), M2C_FIELD(&D_88002254, u8 *, 1), (s32) M2C_FIELD(&D_88002254, u8 *, 2));
    MainMenu_DrawItemList(D_88002B20 + 0x2C, 2);
    return 0;
}

void Cont_StartReadInputs(void);                            /* extern */
void Cont_ReadInputs(void);                            /* extern */
M2C_UNK func_8001B5F0();                            /* extern */
s32 MainMenu_UpdateScreen(s8*);
extern s32 D_88002B20;

/**
 * One frame: reads the controllers, draws the main menu and, when `arg0` is 0, updates it.
 * Seen in play: runs every frame on the メインメニュー screen (ずかん, バトル, てもち, GB, とうろく, OFF).
 */
s32 MainMenu_RunFrame(s32 arg0) {
    s32 sp1C;

    sp1C = 0;
    Cont_StartReadInputs();
    Cont_ReadInputs();
    func_8001B5F0();
    MainMenu_DrawScreen(D_88002B20);
    if (arg0 == 0) {
        sp1C = MainMenu_UpdateScreen(D_88002B20);
    }
    return sp1C;
}

M2C_UNK func_80002DC0(s32);                         /* extern */
extern s32 D_88002B20;

/**
 * Frees the main menu state.
 * Seen in play (2026-11-12): ran once as the main menu was left for いちらん.
 */
void MainMenu_Free(void) {
    func_80002DC0(D_88002B20);
}

extern s32 D_88002B20;

/**
 * Draws the main menu without updating it.
 * Seen in play (2026-11-13) ran while the GB player prompt (ゲームボーイのポケモン, はい/いいえ) was open over the
 * main menu.
 * @unverified Name and comment guessed from the code.
 */
s32 MainMenu_DrawFrame(s32 arg0) {
    MainMenu_DrawScreen(D_88002B20);
    return 0;
}

M2C_UNK func_8000256C(M2C_UNK);                     /* extern */
M2C_UNK func_80002620(M2C_UNK);                     /* extern */
M2C_UNK func_80003EB8(u32, M2C_UNK *, M2C_UNK *, M2C_UNK); /* extern */
M2C_UNK func_80005B98(M2C_UNK);                     /* extern */
M2C_UNK func_80006724();                            /* extern */
M2C_UNK func_8000675C();                            /* extern */
s32 func_80006828(M2C_UNK, M2C_UNK *);              /* extern */
M2C_UNK func_80006998(M2C_UNK);                     /* extern */
M2C_UNK func_8000A7B0(M2C_UNK);                     /* extern */
M2C_UNK func_8000A7FC(M2C_UNK);                     /* extern */
s32 Font_Init(s32 load_size, s32 side);            /* extern */
M2C_UNK func_8001A360();                            /* extern */
void MainMenu_LoadGbSaveSummary(void);                          /* extern */
extern M2C_UNK D_002E0BE0;
extern M2C_UNK D_002E2B90;
extern M2C_UNK D_00400F70;
extern M2C_UNK D_004076E0;
extern M2C_UNK D_004199E0;
extern M2C_UNK D_01000000;
extern M2C_UNK D_04000000;
extern M2C_UNK D_05000000;
extern s32 D_80073400;
s32 MainMenu_DrawFadeInBackground(s32 arg0);
s32 MainMenu_DrawSummaryBarSlideIn(s32 arg0);

/**
 * Entry point: pushes the 'COMP' pool state, loads the font and segments, and sets up the screen.
 * Seen in play (2026-11-13) ran once each time the main menu came back from the Pokédex, party or
 * list screen.
 */
s32 MainMenu_Init(s32 arg0) {
    s32 sp1C;
    s32 temp_v0;

    func_8000256C(0x434F4D50);
    Font_Init(0x18, 0);
    func_80003EB8((u32) ((s32) &D_01000000 & 0x0F000000) >> 0x18, &D_002E0BE0, &D_002E2B90, 0);
    func_80003EB8((u32) ((s32) &D_04000000 & 0x0F000000) >> 0x18, &D_00400F70, &D_004076E0, 0);
    func_80003EB8((u32) ((s32) &D_05000000 & 0x0F000000) >> 0x18, &D_004076E0, &D_004199E0, 0);
    MainMenu_LoadGbSaveSummary();
    func_8000675C();
    if (arg0 == 1) {
        D_80073400 = 4;
        func_80006828(0x14, &MainMenu_DrawFadeInBackground);
        func_80006828(2, &MainMenu_DrawBackground);
        func_80006828(6, &MainMenu_DrawSummaryBarSlideIn);
        func_80006828(2, &MainMenu_DrawSummaryBar);
    } else {
        func_80006828(0x11, &MainMenu_DrawSummaryBarAndBackground);
    }
    func_8000A7B0(9);
    temp_v0 = func_80006828(0, &MainMenu_RunFrame);
    sp1C = temp_v0;
    D_80073400 = M2C_FIELD(D_88002B20, s32 *, 0x3C) + 1;
    if (temp_v0 != 0x8040) {
        if (temp_v0 == 0x8050) {
            func_80006998(0xFFFF);
        } else {
            func_80006998(1);
        }
        func_80005B98(0xF);
        func_80006828(0x11, &MainMenu_DrawFrame);
        func_8000A7FC(0xF);
    } else {
        func_80006998(1);
    }
    func_80006724();
    MainMenu_Free();
    func_8001A360();
    func_80002620(0x434F4D50);
    return sp1C;
}

M2C_UNK func_80025BA0(s32, M2C_UNK *, M2C_UNK *, M2C_UNK, s32);
extern u16 D_800AF986;
extern M2C_UNK D_82000000;
extern M2C_UNK D_00166580;
extern M2C_UNK D_001720F0;

/**
 * Goes straight to the fragment at 0x82000000 when D_800AF986 bit 8 is set, otherwise starts the main menu.
 * Seen in play (2026-11-13) ran once each time a menu screen (Pokédex, party, list) was left with B
 * and the main menu came back.
 */
s32 MainMenu_Enter(s32 arg0, s32 arg1) {
    s32 ret;

    if (D_800AF986 & 0x100) {
        ret = 0x8040;
        func_80025BA0(((u32)((s32)&D_82000000 & 0x0FF00000) >> 0x14) - 0x10, &D_00166580, &D_001720F0, 0, 0);
    } else {
        ret = MainMenu_Init(arg0);
    }
    return ret;
}
