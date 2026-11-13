/* Stadium Zero fragment018_262620. */
/* C ported from the Stadium 1 decomp: src/fragments/pokedex/pokedex_214920.c. */

#include "fragments/pokedex/pokedex.h"
#include "geo_render.h"
#include "display_object_textures.h"
#include "poke_icon.h"
#include "model_renderer.h"
#include "graphics_textures.h"
#include "input.h"
#include "gb_data.h"
#include "game_state.h"
#include "table_view.h"
#include "text_system.h"
#include "gb_save.h"
#include "3D140.h"
#include "jpeg_stream.h"
#include "audio_sfx.h"
#include "gfx_rect.h"
#include "controller.h"
#include "memmap.h"
#include "memory.h"
#include "stage_loader.h"
#include "pokemon_stats.h"
s32 Pokedex_DrawListScrollArrows(unk_func_888044BC_050*, s32, s32);
s32 Pokedex_HandleSpeciesListInput(unk_func_888044BC_038*, Controller*);
void Pokedex_DrawTrainerInfoCard(unk_func_888044BC_03C_02C*, s32, s32);
s32 Pokedex_DrawSortOrderLabel(unk_func_888044BC_040_030*, s32, s32);
s32 Pokedex_HandleEntryMenuInput(unk_func_888044BC_040*, Controller*);
s32 Pokedex_DrawDataPanel(unk_func_888044BC_044_02C*, s32, s32);
s32 Pokedex_DrawPreview(unk_func_888044BC_04C_02C*, s32, s32);
extern StageContext* D_8A12FF9C;
extern StageContext* D_8A12FFA0;
extern ModelLoadContext* D_8A12FFA4;
extern s32 D_8A12FFA8;
extern s32 D_8A12FFAC;
extern s32 D_8A12FFB0;
extern u8 pad_D_88826948[0x58];
extern u32 pad_D_888269A4;
extern u8 gPokedexAlphabeticalOrder[];

#include "m2c_macros.h"

void Pokedex_LoadIcon(u8* arg0, s32 arg1);
void Pokedex_ExitAreaMapScreen(void);
void Pokedex_RunEntryFlow(void);
s32 Pokedex_GetHighestSeenSpeciesIndex(void);
void Pokedex_InitFramebuffers(void);

s32 Pokedex_RunIndexScreen(void);
s32 Pokedex_ShowEntryMenu(void);
s32 Pokedex_ShowEntry(void);
s32 Pokedex_PlayCry(void);
s32 Pokedex_RedrawAreaMapTransition(u8 arg0);
s32 Pokedex_ShowAreaMapScreen(void);

extern Gfx D_80060290[];
extern Gfx D_80060398[];
extern u8 D_04002BA8[];
extern u8 D_04002ED0[];
void func_8001B884(s32, s32, s32, s32, u8*, s32, s32);
/**
 * Draws the 20x20 caught icon (`arg2` set) or the seen icon at (x, y).
 * Seen in play (2026-11-12): the Poke Ball icon beside 001 フシギダネ, 004 ヒトカゲ and 007 ゼニガメ, the
 * three caught species of the save.
 */
void Pokedex_DrawCaughtIcon(s32 arg0, s32 arg1, s32 arg2) {
    gSPDisplayList(gDisplayListHead++, D_80060290);
    func_8001B884(arg0, arg1, 0x14, 0x14, arg2 ? D_04002BA8 : D_04002ED0, 0x14, 0x200000);
    gSPDisplayList(gDisplayListHead++, D_80060398);
}

s32 func_800209A4();

/**
 * Returns the dex index under the list cursor, mapping through the sort order when sorted by kana.
 * Seen in play (2026-11-12): データをみる opened the entry of the row under the cursor (No.001).
 */
s32 Pokedex_GetCursorDexIndex(s8 *arg0) {
    s32 var_v1;

    if (M2C_FIELD(arg0, s32 *, 0x1B0) != 0) {
        var_v1 = func_800209A4(M2C_FIELD(arg0, s32 *, 0x34) + 1, arg0) - 1;
    } else {
        var_v1 = M2C_FIELD(arg0, s32 *, 0x34);
    }
    return var_v1;
}

#include "fragments/fragment018_262620/pokedex_214920_types.h"
extern unk_D_80064C60 D_80064C60[];
extern Gfx D_80060270[];
extern Color_RGBA8 D_8A1057D4;
extern Color_RGBA8 D_8A1057D8;
extern char D_8A12FC30[];
void func_80029028(s32, s32, s32, s32, Color_RGBA8);
void Ui_FillRectHighlighted(s32, s32, s32, s32, Color_RGBA8);
void Font_SetColorForFlags(s32);
s32 func_800231C8(s32, s32);
void func_8001A944(s32, s32, const char*, ...);
/**
 * Draws one row of the index list (number, name, seen/caught icon), mapping the row through the kana sort when sorted.
 * Seen in play (2026-11-12): the ずかんもくじ rows: number, name for seen species, caught icon.
 */
void Pokedex_DrawListRow(s32 arg0, s32 arg1, char* arg2, s32 arg3, s32 arg4, s32* arg5) {
    s32 sorted;
    UNUSED s32 pad[2]; // FAKE: stack padding
    s32 idx;
    s32 progress;

    sorted = *arg5;
    if (sorted != 0) {
        idx = func_800209A4(arg3 + 1) - 1;
    } else {
        idx = arg3;
    }
    progress = func_800231C8(D_8A12FFB0, idx + 1);
    gSPDisplayList(gDisplayListHead++, D_80060270);
    func_80029028(arg0, arg1, 0x104, 1, D_8A1057D8);
    func_80029028(arg0, arg1 + 0x23, 0x104, 1, D_8A1057D8);
    func_80029028(arg0, arg1 + 1, 0x104, 0x22, D_8A1057D4);
    if (arg4 & 0x10) {
        Ui_FillRectHighlighted(arg0 + 3, arg1 + 3, 0xFE, 0x1E, D_8A1057D4);
    }
    if (progress == 2) {
        Pokedex_DrawCaughtIcon(arg0 + 0x58, arg1 + 8, 0);
    }
    if (progress == 3) {
        Pokedex_DrawCaughtIcon(arg0 + 0x58, arg1 + 8, 1);
    }
    func_8001AB6C();
    Font_SetColorForFlags(arg4);
    func_8001A384(8, 0);
    func_8001A944(arg0 + 0x10, arg1 + 8, D_8A12FC30, idx + 1);
    if (progress != 0) {
        func_8001A384(0x10, 0);
        func_8001A944(arg0 + 0x7C, arg1 + 6, D_80064C60[idx].unk_00);
    }
    func_8001ABBC();
}

/*
 * Pokedex_InitListWindow
 *
 * Initialises a record in the same way as Pokedex_InitEntryWindow, PartyScreen_InitList and
 * SavePrompt_Init: Window_SetRect fills the first five words with
 * (arg1, arg2, 0x110, 0x16E, 0), the words at +0x24 and +0x28 are cleared,
 * +0x14 is set to 0x801 and +0x20 to the address of D_8A12FC38.  It then
 * sets up two sub-objects:
 *
 *   - func_80027410 (TableView_Initialize in symbol_addrs.txt) is called on
 *     the area at arg0 + 0x70 with D_80064C5C, 0x1C, 0x97 and 0x97;
 *   - ScrollList_Init is called on the object at arg0 + 0x2C with that area,
 *     arg0 + 0x80, 8, the callback Pokedex_DrawListRow and the constants 0x104
 *     and 0x24.
 *
 * Finally the word at +0x1B0 is cleared and bit 0x10000 is set in the word at
 * +0x4C.  What func_80027410 and ScrollList_Init do is not established yet,
 * so the roles of those arguments are not named.
 */
M2C_UNK func_80027410(s8 *, M2C_UNK *, M2C_UNK, M2C_UNK, s32); /* extern */
M2C_UNK ScrollList_Init(s8 *, s8 *, s8 *, M2C_UNK, M2C_UNK *, s32, s32); /* extern */
extern M2C_UNK D_80064C5C;
extern M2C_UNK D_8A12FC38;

/**
 * Sets up the index list window (272x366) and its scrolling list.
 * Seen in play (2026-11-12): set up the ずかんもくじ list window.
 */
void Pokedex_InitListWindow(void* arg0, s32 arg1, s32 arg2) {
    Window_SetRect((s8 *)arg0, arg1, arg2, 0x110, 0x16E);
    M2C_FIELD(arg0, s32 *, 0x24) = 0;
    M2C_FIELD(arg0, s32 *, 0x28) = 0;
    M2C_FIELD(arg0, s32 *, 0x14) = 0x801;
    M2C_FIELD(arg0, M2C_UNK **, 0x20) = &D_8A12FC38;
    func_80027410((s8 *)arg0 + 0x70, &D_80064C5C, 0x1C, 0x97, 0x97);
    ScrollList_Init((s8 *)arg0 + 0x2C, (s8 *)arg0 + 0x70, (s8 *)arg0 + 0x80, 8, &Pokedex_DrawListRow, 0x104, 0x24);
    M2C_FIELD(arg0, s32 *, 0x1B0) = 0;
    M2C_FIELD(arg0, s32 *, 0x4C) = (s32) (M2C_FIELD(arg0, s32 *, 0x4C) | 0x10000);
}

s32 func_8002AE6C();
s32 Ui_DrawTexturedDivider(s32, s32, s32, void*);
void func_80029028(s32, s32, s32, s32, Color_RGBA8);
void ScrollList_DrawInlineItems(void*, s32, s32, s32, s32);
void func_8001B884(s32, s32, s32, s32, u8*, s32, s32);
extern u8 D_8007356C;
extern u8 D_800734A8[];
extern Gfx D_80060270[];
extern Gfx D_80060290[];
extern Gfx D_80060398[];
extern u8 D_04005890[];
extern Color_RGBA8 D_8A1057DC;
extern char D_8A12FC48[];
extern char D_8A12FC5C[];
/**
 * Draws アイウエオじゅん (kana order) and ばんごうじゅん (number order).
 * Seen in play (2026-11-12): the ばんごうじゅん bar under the list.
 */
void Pokedex_DrawSortOrderMenu(s8* arg0, u32 arg1) {
    char* str;

    if (func_8002AE6C() == 0) {
        Ui_DrawTexturedDivider(M2C_FIELD(arg0, s32*, 0), M2C_FIELD(arg0, s32*, 4) + 0x145, M2C_FIELD(arg0, s32*, 8), &D_8007356C);
        ScrollList_DrawInlineItems(arg0 + 0x2C, M2C_FIELD(arg0, s32*, 0) + 6, M2C_FIELD(arg0, s32*, 4) + 0x16, arg1 | 0xFFED, (s32)(arg0 + 0x1B0));
        gSPDisplayList(gDisplayListHead++, D_80060270);
        func_80029028(M2C_FIELD(arg0, s32*, 0) + 6, M2C_FIELD(arg0, s32*, 4) + 0x14C, M2C_FIELD(arg0, s32*, 8) - 0xC, 0x1C, D_8A1057DC);
        Font_BeginTranslucentTextRendering();
        Gfx_SetEnvColor(D_800734A8[0], D_800734A8[1], D_800734A8[2], D_800734A8[3]);
        Font_SetActive(8, 0);
        Font_Printf(M2C_FIELD(arg0, s32*, 0) + 0x24, M2C_FIELD(arg0, s32*, 4) + 0x150, M2C_FIELD(arg0, s32*, 0x1B0) ? D_8A12FC48 : D_8A12FC5C);
        Font_EndTexturedTextRendering();
        gSPDisplayList(gDisplayListHead++, D_80060290);
        func_8001B884(M2C_FIELD(arg0, s32*, 0) + 0xD8, M2C_FIELD(arg0, s32*, 4) + 0x150, 0x14, 0x14, D_04005890, 0x14, 0x200000);
        gSPDisplayList(gDisplayListHead++, D_80060398);
    }
}

extern s32 D_800603C0;
s32 ScrollList_UpdateCursor(unk_func_8820BE14_02C_038*);

/**
 * Navigate the list, toggle the view mode, or report cancel/confirm input.
 * Seen in play (2026-11-12): moved the list cursor from 001 to 002.
 */
s32 Pokedex_UpdateListCursor(u8* state) {
    s32 result;
    unk_func_8820BE14_02C_038* menu;
    s32 value;

    menu = (unk_func_8820BE14_02C_038*)(state + 0x2C);
    result = ScrollList_UpdateCursor(menu);
    if (result == 0) {
        value = *(u16*)(D_800603C0 + 8);
        if (value & 1) {
            Audio_PlaySoundEffectById(2);
            WidgetTree_SetScrollableGridIndexPreserveScroll(menu, 0);
            value = *(s32*)(state + 0x1B0);
            value = value == 0;
            *(s32*)(state + 0x1B0) = value;
        } else if (value & 0x4000) {
            result = -1;
        } else if (value & 0x8000) {
            result = 1;
        }
    }
    return result;
}

typedef struct Rgba8A100620 {
    u8 r, g, b, a;
} Rgba8A100620;

extern Rgba8A100620 D_8A1057E0;
extern Rgba8A100620 D_8A1057E4;

/**
 * Sets up the seen/caught/owned counts window (248x104).
 * Seen in play (2026-11-12): set up the counts window.
 */
void Pokedex_InitCountsWindow(void* arg0, s32 arg1, s32 arg2) {
    Window_SetRect((s8*)arg0, arg1, arg2, 0xF8, 0x68);
    M2C_FIELD(arg0, s32*, 0x24) = 0;
    M2C_FIELD(arg0, s32*, 0x20) = 0;
    M2C_FIELD(arg0, s32*, 0x28) = 0;
    M2C_FIELD(arg0, s32*, 0x14) = 0x1006;
    M2C_FIELD(arg0, Rgba8A100620*, 0x18) = D_8A1057E0;
    M2C_FIELD(arg0, Rgba8A100620*, 0x1C) = D_8A1057E4;
}

s32 func_8002AE6C();
s32 GbSave_CountSeenSpecies(s32);
s32 GbSave_CountOwnedSpecies(s32);
s32 GbSave_CountHeldSpecies(s32);
extern u8 D_800734A8[4];
extern char D_8A12FC6C[];
extern char D_8A12FC7C[];
extern char D_8A12FC8C[];
extern char D_8A12FC9C[];
extern char D_8A12FCA0[];
extern char D_8A12FCA4[];
/**
 * Draws みつけたかず (seen), つかまえたかず (caught) and もっているかず (owned).
 * Seen in play (2026-11-12): みつけたかず 3, つかまえたかず 3, もっているかず 3 for the three-starter save.
 */
void Pokedex_DrawCounts(void* arg0) {
    if (func_8002AE6C() == 0) {
        Font_BeginTranslucentTextRendering();
        Font_SetActive(8, 0);
        Gfx_SetEnvColor(0x9C, 0xCC, 0x98, 0xFF);
        Font_Printf(M2C_FIELD(arg0, s32*, 0) + 0xE, M2C_FIELD(arg0, s32*, 4) + 0xE, D_8A12FC6C);
        Gfx_SetEnvColor(0x98, 0xCC, 0xCC, 0xFF);
        Font_Printf(M2C_FIELD(arg0, s32*, 0) + 0xE, M2C_FIELD(arg0, s32*, 4) + 0x2A, D_8A12FC7C);
        Gfx_SetEnvColor(0xCC, 0x98, 0x98, 0xFF);
        Font_Printf(M2C_FIELD(arg0, s32*, 0) + 0xE, M2C_FIELD(arg0, s32*, 4) + 0x46, D_8A12FC8C);
        Gfx_SetEnvColor(D_800734A8[0], D_800734A8[1], D_800734A8[2], D_800734A8[3]);
        Font_Printf(M2C_FIELD(arg0, s32*, 0) + 0xAE, M2C_FIELD(arg0, s32*, 4) + 0xE, D_8A12FC9C, GbSave_CountSeenSpecies(D_8A12FFB0));
        Font_Printf(M2C_FIELD(arg0, s32*, 0) + 0xAE, M2C_FIELD(arg0, s32*, 4) + 0x2A, D_8A12FCA0, GbSave_CountOwnedSpecies(D_8A12FFB0));
        Font_Printf(M2C_FIELD(arg0, s32*, 0) + 0xAE, M2C_FIELD(arg0, s32*, 4) + 0x46, D_8A12FCA4, GbSave_CountHeldSpecies(D_8A12FFB0));
        Font_EndTexturedTextRendering();
    }
}

extern Color_RGBA8 D_8A1057D4;
void Ui_FillRectHighlighted(s32, s32, s32, s32, Color_RGBA8);
void Font_SetColorForFlags(s32);

/**
 * Draws one menu row label with the selection highlight.
 * Seen in play (2026-11-12): one row of データをみる / なきごえ / ぶんぷをみる / やめる.
 */
void Pokedex_DrawMenuRow(s32 arg0, s32 arg1, char* arg2, s32 arg3, s32 arg4) {
    if (arg4 & 0x10) {
        Ui_FillRectHighlighted(arg0 + 3, arg1 + 3, 0xA2, 0x1E, D_8A1057D4);
    }
    Font_BeginTranslucentTextRendering();
    Font_SetColorForFlags(arg4);
    Font_SetActive(0x10, 0);
    Font_Printf(arg0 + 0xC, arg1 + 6, arg2);
    Font_EndTexturedTextRendering();
}

extern M2C_UNK D_8A1057E8;
M2C_UNK func_80027804();
/**
 * Sets up the sort order menu window (180x168).
 * Seen in play (2026-11-12): set up when the index opened.
 */
void Pokedex_InitSortMenuWindow(void* arg0, s32 arg1, s32 arg2) {
    s32 pad; // FAKE: stack padding

    Window_SetRect((s8*)arg0, arg1, arg2, 0xB4, 0xA8);
    M2C_FIELD(arg0, s32*, 0x24) = 0;
    M2C_FIELD(arg0, s32*, 0x20) = 0;
    M2C_FIELD(arg0, s32*, 0x28) = 0;
    M2C_FIELD(arg0, s32*, 0x14) = 0x1000;
    M2C_FIELD(arg0, Color_RGBA8*, 0x18) = D_8A1057D4;
    func_80027804((s8 *)arg0 + 0x58, &D_8A1057E8, 4, 4);
    Menu_Init((s8 *)arg0 + 0x2C, (s8 *)arg0 + 0x58, (s8 *)arg0 + 0x50, &Pokedex_DrawMenuRow, 0xA8, 0x24);
    M2C_FIELD(arg0, s32 *, 0x4C) = (s32) (M2C_FIELD(arg0, s32 *, 0x4C) | 0x10000);
}

s32 func_8002AE6C();                                /* extern */
M2C_UNK Menu_DrawItems(s8 *, s32, s32, s32, s32);  /* extern */

/**
 * Draws the menu window's items.
 * Seen in play (2026-11-12): データをみる / なきごえ / ぶんぷをみる / やめる.
 */
void Pokedex_DrawMenu(s8 *arg0, s32 arg1) {
    if (func_8002AE6C() == 0) {
        Menu_DrawItems(arg0 + 0x2C, M2C_FIELD(arg0, s32 *, 0) + 6, M2C_FIELD(arg0, s32 *, 4) + 0xC, arg1 | 0xFFED, 0);
    }
}

s32 func_8002BC14(s32);                             /* extern */
s32 Menu_UpdateCursor(s32);                             /* extern */

/**
 * Moves the menu cursor; without a move returns the confirm/cancel result.
 * Seen in play (2026-11-12): moved over that menu and returned the pick.
 */
s32 Pokedex_UpdateMenuCursor(s32 arg0) {
    s32 temp_v0;
    s32 var_v1;

    temp_v0 = Menu_UpdateCursor(arg0 + 0x2C);
    var_v1 = temp_v0;
    if (temp_v0 == 0) {
        var_v1 = func_8002BC14(D_800603C0);
    }
    return var_v1;
}

/**
 * Pokedex_InitEntryWindow
 *
 * Initialises a record in the same way as PartyScreen_InitList and SavePrompt_Init:
 * Window_SetRect fills the first five words with (arg1, arg2, 0x228, 0x15C, 0)
 * (the last two constants look like a width and a height, not confirmed),
 * the words at +0x20, +0x24 and +0x28 are cleared, and +0x14 is set to
 * 0x1001.
 * Seen in play (2026-11-12): set up the データをみる page.
 */
void Pokedex_InitEntryWindow(s8 *arg0, s32 arg1, s32 arg2) {
    Window_SetRect(arg0, arg1, arg2, 0x228, 0x15C);
    M2C_FIELD(arg0, s32 *, 0x24) = 0;
    M2C_FIELD(arg0, s32 *, 0x20) = 0;
    M2C_FIELD(arg0, s32 *, 0x28) = 0;
    M2C_FIELD(arg0, s32 *, 0x14) = 0x1001;
}

void func_8001B884(s32, s32, s32, s32, u8*, s32, s32);
void func_8A100A24(s32 arg0, s32 arg1, s32 arg2, u8* arg3) {
    s32 i;

    gDPPipeSync(gDisplayListHead++);
    gDPSetCycleType(gDisplayListHead++, G_CYC_1CYCLE);
    gDPSetCombineLERP(gDisplayListHead++, 0, 0, 0, TEXEL0, TEXEL0, 0, ENVIRONMENT, 0, 0, 0, 0, TEXEL0, TEXEL0, 0, ENVIRONMENT, 0);
    gDPSetRenderMode(gDisplayListHead++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    gDPSetTexturePersp(gDisplayListHead++, G_TP_NONE);
    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, arg2);
    for (i = 0; i < 0xD0; i += 8) {
        func_8001B884(arg0, arg1, 0xF4, 8, arg3, 0x100, 0);
        arg1 += 8;
        arg3 += 0x1000;
    }
    func_8001B884(arg0, arg1, 0xF4, 2, arg3, 0x100, 0);
    gDPPipeSync(gDisplayListHead++);
    gDPSetTexturePersp(gDisplayListHead++, G_TP_PERSP);
    gDPSetAlphaCompare(gDisplayListHead++, G_AC_NONE);
}

extern char D_8A12FCDC[];
void func_8001A944(s32, s32, const char*, ...);
void func_8001AA60(s32, s32, s32);

/**
 * Prints the two decimal digits of arg2 at (arg0, arg1). The tens digit is
 * printed by func_8001A944(arg0, arg1, D_8A12FCDC, arg2 / 10), with D_8A12FCDC
 * passed in the format-string position; the units digit is drawn by
 * func_8001AA60(arg0 + 0x54, arg1, arg2 % 10 + '0').
 * What D_8A12FCDC contains and the exact roles of the two callees are not
 * established.
 * Seen in play (2026-11-12): たかさ 0.7m and おもさ 6.9kg for Bulbasaur.
 */
void Pokedex_DrawTenthsValue(s32 arg0, s32 arg1, s32 arg2) {
    func_8001A944(arg0, arg1, D_8A12FCDC, arg2 / 10);
    func_8001AA60(arg0 + 0x54, arg1, (arg2 % 10) + 0x30);
}

extern char D_8A12FCE4[];
extern char D_8A12FCF0[];
extern char D_8A12FCF8[];
extern char D_8A12FD00[];
extern char D_8A12FD04[];
extern char D_8A12FD0C[];
extern char D_8A12FD10[];
extern char D_8A12FD14[];
extern char D_8A12FD18[];
extern u8 D_800735C4[];
extern s32 D_8A12FFB8;
s32 func_800231C8(s32, s32);
void Ui_DrawTexturedFrameDecal(s32, s32, s32, s32, u8*);

/**
 * Draws an entry's category (%sポケモン), No., たかさ (height) and おもさ (weight, kg).
 * Seen in play (2026-11-12): No.001 フシギダネ, たねポケモン, たかさ 0.7m, おもさ 6.9kg.
 */
void Pokedex_DrawEntryInfo(s32 arg0, s32 arg1) {
    u8* entry = (u8*)&D_80064C5C + D_8A12FFB8 * 0x1C;

    gSPDisplayList(gDisplayListHead++, D_80060270);
    func_80029028(arg0, arg1, 0x122, 0xD2, D_8A1057D4);
    Ui_DrawTexturedFrameDecal(arg0 + 8, arg1 + 8, 0x112, 0x5A, D_800735C4);
    Font_BeginTranslucentTextRendering();
    Gfx_SetEnvColor(0xFF, 0xFF, 0xFF, 0xFF);
    Font_EnableTwoCycleTexturing();
    Font_SetActive(0x20, 0);
    Gfx_SetPrimColor(0x96, 0x96, 0xFF, 0xFF);
    Font_Printf(arg0 + 0x70, arg1 + 0x38, M2C_FIELD(entry, char**, 4));
    Font_SetActive(0x10, 0);
    Gfx_SetPrimColor(0x96, 0xFF, 0x96, 0xFF);
    Font_Printf(arg0 + 8, arg1 + 0x6A, D_8A12FCE4, M2C_FIELD(entry, s32*, 8));
    Gfx_SetPrimColor(0xFF, 0xFF, 0x96, 0xFF);
    Font_Printf(arg0 + 0xD, arg1 + 0x8E, D_8A12FCF0);
    Gfx_SetPrimColor(0xFF, 0x96, 0x96, 0xFF);
    Font_Printf(arg0 + 0xD, arg1 + 0xB2, D_8A12FCF8);
    Font_DisableTwoCycleTexturing();
    Gfx_SetEnvColor(D_800734A8[0], D_800734A8[1], D_800734A8[2], D_800734A8[3]);
    Font_Printf(arg0 + 0x12, arg1 + 0x12, D_8A12FD00);
    Font_Printf(arg0 + 0x4E, arg1 + 0x12, D_8A12FD04, entry[0]);
    if (func_800231C8(D_8A12FFB0, entry[0]) >= 2) {
        Pokedex_DrawTenthsValue(arg0 + 0x79, arg1 + 0x8E, entry[0xD]);
        Pokedex_DrawTenthsValue(arg0 + 0x79, arg1 + 0xB2, M2C_FIELD(entry, s16*, 0xE));
    } else {
        Font_Printf(arg0 + 0x79, arg1 + 0x8E, D_8A12FD0C);
        Font_Printf(arg0 + 0x79, arg1 + 0xB2, D_8A12FD10);
    }
    Font_Printf(arg0 + 0xE1, arg1 + 0x8E, D_8A12FD14);
    Font_Printf(arg0 + 0xE1, arg1 + 0xB2, D_8A12FD18);
    Font_EndTexturedTextRendering();
}

typedef struct Rgba8A100F20 { u8 r, g, b, a; } Rgba8A100F20;
void Ui_FillRectPrimEnvColor(s32, s32, s32, s32, Rgba8A100F20, Rgba8A100F20);
void func_8001A944(s32, s32, const char*, ...);
s32 func_800231C8(s32, s32);
extern u8 D_8A1057F8[];
extern u8 D_8A1057FC[];
extern char D_8A12FD1C[];
extern s32 D_8A12FFB8;
/**
 * Draws the entry page name bar for the selected species (name shown once it is caught).
 * Seen in play (2026-11-12): the フシギダネ name bar on the entry page.
 */
void Pokedex_DrawEntryNameBar(s32 arg0, s32 arg1) {
    u8 *entry = (u8 *)&D_80064C5C + D_8A12FFB8 * 0x1C;

    Ui_FillRectPrimEnvColor(arg0, arg1, 0x21C, 0x78, *(Rgba8A100F20 *)D_8A1057F8, *(Rgba8A100F20 *)D_8A1057FC);
    func_8001AB6C();
    func_8001A384(0x10, 0);
    Font_SetLineHeight(0x24);
    if (func_800231C8(D_8A12FFB0, entry[0]) >= 2) {
        func_8001A944(arg0 + 0x2A, arg1 + 0xC, M2C_FIELD(entry, char **, 0x18));
    } else {
        func_8001A944(arg0 + 0x2A, arg1 + 0xC, D_8A12FD1C);
    }
    func_8001ABBC();
}

s32 Ui_DrawTexturedDivider(s32, s32, s32, void*);
s32 func_80029864(s32, s32, s32, void*);
s32 Ui_DrawImageInStrips(void*, s32, s32);
s32 Particle_Field50_SetXZFromField7C_09BB4();
void func_8A100A24(s32, s32, s32, u8*);
void Pokedex_DrawEntryInfo(s32, s32);
void Pokedex_DrawEntryNameBar(s32, s32);
extern u8 D_8007356C;
extern u8 D_8A11FC18;

/**
 * Pokedex_DrawEntryWindow
 *
 * Per-frame draw helper for the screen in this file, called by
 * Pokedex_DrawEntryScreen with D_8A130204, the value returned by func_800196F8, and
 * that function's second argument. `arg0` is a layout record: words at
 * offsets 0 and 4 act as an x/y origin that the draw calls below offset
 * (x + 0xF9, y + 0xD7 and so on), the word at offset 8 is passed to
 * Ui_DrawTexturedDivider, and the word at offset 0x28 is a mode value. When the mode
 * is not 2 and Particle_Field50_SetXZFromField7C_09BB4() returns 0, it runs Ui_DrawTexturedDivider,
 * func_80029864, Pokedex_DrawEntryInfo and Pokedex_DrawEntryNameBar at those offsets. When the
 * mode is 1 or 2 it also calls Ui_DrawImageInStrips on D_8A11FC18 with (0x32, 0x5A)
 * and then func_8A100A24(0x32, 0x5A, v, arg1), where v is 0xFF if arg2 >= 2
 * and 0x64 otherwise. What the individual calls draw is not established here;
 * the field meanings are inferred from the offsets only.
 * Seen in play (2026-11-12): the entry page with the dex text 「せなかの きゅうこんのような ふくろは...」.
 */
void Pokedex_DrawEntryWindow(void* arg0, s32 arg1, s32 arg2) {
    s32 temp_v0;

    if ((M2C_FIELD(arg0, s32*, 0x28) != 2) && (Particle_Field50_SetXZFromField7C_09BB4() == 0)) {
        Ui_DrawTexturedDivider(M2C_FIELD(arg0, s32*, 0), M2C_FIELD(arg0, s32*, 4) + 0xD7, M2C_FIELD(arg0, s32*, 8), &D_8007356C);
        func_80029864(M2C_FIELD(arg0, s32*, 0) + 0xF9, M2C_FIELD(arg0, s32*, 4), 0xDE, &D_8007356C);
        Pokedex_DrawEntryInfo(M2C_FIELD(arg0, s32*, 0) + 0x100, M2C_FIELD(arg0, s32*, 4) + 6);
        Pokedex_DrawEntryNameBar(M2C_FIELD(arg0, s32*, 0) + 6, M2C_FIELD(arg0, s32*, 4) + 0xDE);
    }
    temp_v0 = M2C_FIELD(arg0, s32*, 0x28);
    if ((temp_v0 == 1) || (temp_v0 == 2)) {
        Ui_DrawImageInStrips(&D_8A11FC18, 0x32, 0x5A);
        func_8A100A24(0x32, 0x5A, (arg2 >= 2) ? 0xFF : 0x64, arg1);
    }
}

M2C_UNK Ui_DrawTintedScreenBackground(M2C_UNK, M2C_UNK, u8, u8, s32); /* extern */
extern M2C_UNK D_8A1057D0;

/**
 * Draws the tinted Pokedex screen background.
 * Seen in play (2026-11-12): the ポケモンずかん screen background.
 */
void Pokedex_DrawBackground(void) {
    Ui_DrawTintedScreenBackground(0x38, 0x1E0, M2C_FIELD(&D_8A1057D0, u8 *, 0), M2C_FIELD(&D_8A1057D0, u8 *, 1), (s32) M2C_FIELD(&D_8A1057D0, u8 *, 2));
}

/*
 * Pokedex_InitIndexWindows
 *
 * Makes three calls on the object arg0 points to:
 *   Pokedex_InitListWindow(arg0, 0x36, 0x55)
 *   Pokedex_InitCountsWindow(arg0 + 0x1B4, 0x156, 0x72)
 *   Pokedex_InitSortMenuWindow(arg0 + 0x1E0, 0x186, 0x106)
 * The second and third calls address sub-objects at fixed offsets inside
 * arg0.  The constant pairs look like screen positions, but what the
 * callees do with them has not been established.
 */
void Pokedex_InitListWindow(void* arg0, s32 arg1, s32 arg2);
void Pokedex_InitCountsWindow(void* arg0, s32 arg1, s32 arg2);
void Pokedex_InitSortMenuWindow(void* arg0, s32 arg1, s32 arg2);

/**
 * Sets up the list, counts and sort menu windows of the index screen.
 * Seen in play (2026-11-12): set up the list, counts and menu windows when the index opened.
 */
void Pokedex_InitIndexWindows(void* arg0) {
    Pokedex_InitListWindow(arg0, 0x36, 0x55);
    Pokedex_InitCountsWindow((u8*)arg0 + 0x1B4, 0x156, 0x72);
    Pokedex_InitSortMenuWindow((u8*)arg0 + 0x1E0, 0x186, 0x106);
}

void BgStage_DrawFrame(void);                            /* extern */
M2C_UNK GbSave_DrawSummaryBar(M2C_UNK, M2C_UNK *, M2C_UNK *, s32); /* extern */
void Pokedex_DrawSortOrderMenu(s8*, u32);
void Pokedex_DrawCounts(void*);
extern M2C_UNK D_8A12FD2C;
extern M2C_UNK D_8A12FFC0;
extern M2C_UNK D_8A130174;
extern M2C_UNK D_8A1301A0;
extern s32 D_8A130230;
extern M2C_UNK D_8A130238;

/**
 * Draws the Pokedex index: sort order menu, seen/caught/owned counts and the list.
 * Seen in play (2026-11-13) drew the ずかんもくじ index: the list, the みつけたかず / つかまえたかず / もっているかず counts
 * (3/3/3), the ばんごうじゅん sort label and the データをみる / なきごえ / ぶんぷをみる / やめる menu.
 */
s32 Pokedex_DrawIndexScreen(s32 arg0) {
    M2C_UNK *var_a1;

    BgStage_DrawFrame();
    Pokedex_DrawBackground();
    if (D_8A130230 == -1) {
        var_a1 = NULL;
    } else {
        var_a1 = &D_8A130238;
    }
    GbSave_DrawSummaryBar(0, var_a1, &D_8A12FD2C, D_8A130230);
    Pokedex_DrawSortOrderMenu(&D_8A12FFC0, 0x10);
    Pokedex_DrawCounts(&D_8A130174);
    Pokedex_DrawMenu(&D_8A1301A0, 2);
    return 0;
}

M2C_UNK func_8003F6AC(M2C_UNK);
void Pokedex_DrawSortOrderMenu(s8*, u32);
void Cont_StartReadInputs(void);
void Cont_ReadInputs(void);
M2C_UNK func_8000B2F4(s32);
M2C_UNK func_800158C0();
void func_8001B5F0(void);
M2C_UNK func_80006780();
/**
 * Main loop of the Pokedex index screen.
 * Seen in play (2026-11-12): ran every frame of the ずかんもくじ screen.
 */
s32 Pokedex_RunIndexScreen(void) {
    s32 temp_s0;
    s32 var_s4;

    var_s4 = 1;
    func_8000B2F4(D_800603C0);
    do {
        Cont_StartReadInputs();
        Cont_ReadInputs();
        func_8001B5F0();
        if ((M2C_FIELD(&D_8A12FFC0, s32 *, 0x28) == 1) || (M2C_FIELD(&D_8A12FFC0, s32 *, 0x28) == 2U)) {
            temp_s0 = Pokedex_UpdateListCursor((u8*)&D_8A12FFC0);
            D_8A12FFB8 = Pokedex_GetCursorDexIndex((s8*)&D_8A12FFC0);
            if (temp_s0 == -1) {
                func_8003F6AC(3);
                M2C_FIELD(&D_8A12FFC0, s32 *, 0x24) = 7;
                M2C_FIELD(&D_8A12FFC0, s32 *, 0x1D8) = 7;
                M2C_FIELD(&D_8A12FFC0, s32 *, 0x204) = 7;
            } else if (temp_s0 == 1) {
                if (func_800231C8(D_8A12FFB0, D_8A12FFB8 + 1) == 0) {
                    func_8003F6AC(8);
                } else {
                    func_8003F6AC(2);
                    var_s4 = 2;
                    M2C_FIELD(&D_8A12FFC0, s32 *, 0x214) = 0;
                }
            }
        }
        func_800158C0();
        BgStage_DrawFrame();
        Pokedex_DrawBackground();
        Pokedex_DrawSortOrderMenu(&D_8A12FFC0, 2);
        Pokedex_DrawCounts(&D_8A130174);
        Pokedex_DrawMenu((s8*)&D_8A1301A0, 0);
        func_80006780();
        if (M2C_FIELD(&D_8A12FFC0, s32 *, 0x28) == 4) {
            var_s4 = 0;
        }
    } while (var_s4 == 1);
    return var_s4;
}

M2C_UNK func_8003F6AC(M2C_UNK);
M2C_UNK func_8003BD3C(s32);
extern s32 D_8A12FFB8;
extern u8 D_8A130204[];
s32 func_8A1013C0(s32 arg0, s32 *arg1) {
    s32 ret = 0;

    if (arg0 == 1) {
        if (M2C_FIELD(&D_8A12FFC0, u16 **, 0x210)[M2C_FIELD(&D_8A12FFC0, s32 *, 0x214)] & 1) {
            func_8003F6AC(8);
        } else {
            switch (M2C_FIELD(&D_8A12FFC0, s32 *, 0x214)) {
                case 0:
                    func_8003BD3C(D_8A12FFB8 + 1);
                    Pokedex_InitEntryWindow(D_8A130204, 0x2C, 0x54);
                    ret = 2;
                    *arg1 = 3;
                    break;
                case 1:
                    ret = 1;
                    *arg1 = 4;
                    break;
                case 2:
                    func_8003F6AC(2);
                    ret = 1;
                    *arg1 = 5;
                    break;
                case 3:
                    func_8003F6AC(3);
                    ret = 2;
                    *arg1 = 0;
                    break;
            }
        }
    } else if (arg0 == -1) {
        func_8003F6AC(3);
        ret = 1;
        *arg1 = 1;
    }
    return ret;
}

/*
 * Pokedex_ShowEntryMenu
 *
 * Frame loop of a screen in this file (the meaning of the screen is not
 * established).  Starts with func_8000B2F4(D_800603C0) and a result `var_s3`
 * of 2, then repeats until the result is no longer 2.  Each iteration:
 *
 *   - runs the frame helpers Cont_StartReadInputs, Cont_ReadInputs, func_8001B5F0;
 *   - while the state word at D_8A12FFC0 + 0x208 is 1 or 2, takes
 *     Pokedex_UpdateMenuCursor(&D_8A1301A0); if that is non-zero it is passed to
 *     func_8A1013C0(value, &sp50).  A return of 1 sets the result to the
 *     value func_8A1013C0 stored in sp50; a return of 2 sets the words at
 *     D_8A12FFC0 + 0x24, + 0x1D8 and + 0x204 to 7;
 *   - runs func_800158C0, BgStage_DrawFrame, Pokedex_DrawBackground, Pokedex_DrawSortOrderMenu
 *     (D_8A12FFC0, 0x10), Pokedex_DrawCounts(&D_8A130174), Pokedex_DrawMenu
 *     (&D_8A1301A0, 2) and func_80006780;
 *   - if the word at D_8A12FFC0 + 0x28 is 4, the result becomes sp50.
 *
 * Returns the result.  What the values mean is not established.
 *
 * Note for matching: the unused leading `pad` local moves sp50 down 4 bytes
 * to the ROM's stack offset (0x50); func_8001B5F0 must be declared void.
 */
void Cont_StartReadInputs(void);
void Cont_ReadInputs(void);
M2C_UNK func_8000B2F4(s32);
M2C_UNK func_800158C0();
void func_8001B5F0(void);
M2C_UNK func_80006780();
s32 func_8A1013C0(s32, s32 *);

/**
 * Seen in play (2026-11-12): A on a list row opened the データをみる menu.
 */
s32 Pokedex_ShowEntryMenu(void) {
    UNUSED s32 pad; // FAKE: stack padding
    s32 sp50;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 var_s3;

    var_s3 = 2;
    sp50 = 0;
    func_8000B2F4(D_800603C0);
    do {
        Cont_StartReadInputs();
        Cont_ReadInputs();
        func_8001B5F0();
        if ((M2C_FIELD(&D_8A12FFC0, s32 *, 0x208) == 1) || (M2C_FIELD(&D_8A12FFC0, s32 *, 0x208) == 2)) {
            temp_v0 = Pokedex_UpdateMenuCursor((s32) &D_8A1301A0);
            if (temp_v0 != 0) {
                temp_v0_2 = func_8A1013C0(temp_v0, &sp50);
                if (temp_v0_2 == 1) {
                    var_s3 = sp50;
                } else if (temp_v0_2 == 2) {
                    M2C_FIELD(&D_8A12FFC0, s32 *, 0x24) = 7;
                    M2C_FIELD(&D_8A12FFC0, s32 *, 0x1D8) = 7;
                    M2C_FIELD(&D_8A12FFC0, s32 *, 0x204) = 7;
                }
            }
        }
        func_800158C0();
        BgStage_DrawFrame();
        Pokedex_DrawBackground();
        Pokedex_DrawSortOrderMenu(&D_8A12FFC0, 0x10);
        Pokedex_DrawCounts(&D_8A130174);
        Pokedex_DrawMenu(&D_8A1301A0, 2);
        func_80006780();
        if (M2C_FIELD(&D_8A12FFC0, s32 *, 0x28) == 4) {
            var_s3 = sp50;
        }
    } while (var_s3 == 2);
    return var_s3;
}

extern s32 D_8A12FF98;
extern u8 D_8A130204[];
s32 func_800196F8(s32);
s32 Particle_Field7C_SetXZFromField74AngleY_0B278(void *arg0);
void Pokedex_DrawEntryWindow(void*, s32, s32);

/**
 * Draws one frame of the entry screen with the model preview.
 * Seen in play (2026-11-12): the entry page frame with the 3D model.
 */
s32 Pokedex_DrawEntryScreen(s32 arg0, s32 arg1) {
    UNUSED s32 pad[4]; // FAKE: stack padding
    s32 sp1C;

    GeoRender_AdvanceFrameCounter();
    sp1C = func_800196F8(D_8A12FF98);
    BgStage_DrawFrame();
    if (Particle_Field7C_SetXZFromField74AngleY_0B278(D_8A130204) != 0) {
        Pokedex_DrawBackground();
    }
    Pokedex_DrawEntryWindow(D_8A130204, sp1C, arg1);
    return 0;
}

/** Loads a Pokemon icon for the Pokedex. */
void Pokedex_LoadIcon(u8* arg0, s32 arg1) {
    unk_func_8001A024* sp1C;
    void* sp18;

    main_pool_push_state('ICON');
    sp1C = PokeIcon_CreateRenderList(D_8A12FFA4, 1, 0x50, 0x50);
    sp18 = PokeIcon_GetImage(sp1C, 0);
    func_80018234(sp1C, 0, arg1, 0x9530);
    PokeIcon_ProcessAllSlots(sp1C, 0);
    StageLoader_RunFrames(2);
    osInvalDCache(sp18, 0x3200);
    _bcopy(sp18, arg0, 0x3200);
    main_pool_pop_state('ICON');
}

extern u8 D_8A105818;

/**
 * Pokedex_CreateModelPreview
 *
 * Pushes the main-pool state with tag 0x50494354 ('PICT'), builds a model
 * preview with PokeIcon_CreateModelPreview(arg0, 0x100, 0xD2, 0, 0, 0xF4,
 * 0xD2, &D_8A105818), stores the result in D_8A12FF98, and passes it to
 * PokeIcon_SetPreviewSpecies together with arg1 and 0x108D. Only called by
 * Pokedex_ShowEntry, which passes D_8A12FFA4 and D_8A12FFB8 + 1; the meaning of
 * arg1 and of D_8A105818 is not established here.
 * Matching note: the call result is stored straight into D_8A12FF98 and
 * D_8A12FF98 is read back for the second call, which the compiler folds into
 * a register move; going through a local gives a different store sequence.
 * Seen in play (2026-11-12): the 3D Bulbasaur model on the entry page.
 */
void Pokedex_CreateModelPreview(s32 arg0, s32 arg1) {
    main_pool_push_state(0x50494354);
    D_8A12FF98 = (s32)PokeIcon_CreateModelPreview((ModelLoadContext*)arg0, 0x100, 0xD2, 0, 0, 0xF4, 0xD2, &D_8A105818);
    PokeIcon_SetPreviewSpecies((unk_func_8001B1FC*)D_8A12FF98, arg1, 0x108D);
}

M2C_UNK func_80002620(M2C_UNK);                     /* extern */
M2C_UNK func_800199E4(M2C_UNK *);                   /* extern */
extern M2C_UNK D_8A12FE30;

/**
 * Frees the model preview and pops the 'PICT' pool state.
 * Seen in play (2026-11-12): B on the entry page freed the model and returned to the list.
 */
void Pokedex_FreeModelPreview(void) {
    func_800199E4(&D_8A12FE30);
    func_80002620(0x50494354);
}

/*
 * Pokedex_ShowEntry
 *
 * Frame loop of a screen in this file (the meaning of the screen is not
 * established).  Calls Pokedex_CreateModelPreview(D_8A12FFA4, D_8A12FFB8 + 1) once, then
 * keeps the result of func_800231C8(D_8A12FFB0, D_8A12FFB8 + 1) and runs
 * one frame per iteration (Cont_StartReadInputs, Cont_ReadInputs, func_8001B5F0,
 * Pokedex_DrawEntryScreen(0, that result), func_80006780) until the state word at
 * D_8A12FFC0 + 0x26C becomes 4.
 *
 * While that state is 1 or 2 and bit 0xC000 is set in the halfword at
 * offset 8 of the structure D_800603C0 points to (read here as a controller
 * button field; not confirmed), and func_8003BECC() returns 0, the state
 * at D_8A12FFC0 + 0x268 is set to 7 and func_8003F6AC(3) is called.
 *
 * After the loop, Pokedex_FreeModelPreview() is called and the words at offsets 0x24,
 * 0x1D8 and 0x204 of D_8A12FFC0 are cleared.  Always returns 1.
 */
void Cont_StartReadInputs(void);
void Cont_ReadInputs(void);
void func_8001B5F0(void);
M2C_UNK func_80006780();
s32 func_8003BECC();
M2C_UNK func_8003F6AC(M2C_UNK);
void Pokedex_CreateModelPreview(s32, s32);
s32 func_800231C8(s32, s32);
extern s32 D_8A12FFB8;

/**
 * Seen in play (2026-11-12): データをみる showed the entry page.
 */
s32 Pokedex_ShowEntry(void) {
    s32 temp_s1;

    Pokedex_CreateModelPreview((s32)D_8A12FFA4, D_8A12FFB8 + 1);
    temp_s1 = func_800231C8(D_8A12FFB0, D_8A12FFB8 + 1);
    do {
        Cont_StartReadInputs();
        Cont_ReadInputs();
        func_8001B5F0();
        if (((M2C_FIELD(&D_8A12FFC0, s32 *, 0x26C) == 1) || (M2C_FIELD(&D_8A12FFC0, s32 *, 0x26C) == 2)) && (M2C_FIELD((void *)D_800603C0, u16 *, 8) & 0xC000) && (func_8003BECC() == 0)) {
            M2C_FIELD(&D_8A12FFC0, s32 *, 0x268) = 7;
            func_8003F6AC(3);
        }
        Pokedex_DrawEntryScreen(0, temp_s1);
        func_80006780();
    } while (M2C_FIELD(&D_8A12FFC0, s32 *, 0x26C) != 4);
    Pokedex_FreeModelPreview();
    M2C_FIELD(&D_8A12FFC0, s32 *, 0x24) = 0;
    M2C_FIELD(&D_8A12FFC0, s32 *, 0x1D8) = 0;
    M2C_FIELD(&D_8A12FFC0, s32 *, 0x204) = 0;
    return 1;
}

M2C_UNK func_80006780();                            /* extern */
void BgStage_DrawFrame(void);                            /* extern */
M2C_UNK func_8003BD3C(s32);                         /* extern */
s32 func_8003BECC();                                /* extern */
extern s32 D_8A12FFB8;
extern M2C_UNK D_8A1301A0;

/**
 * Seen in play (2026-11-12): なきごえ played the cry.
 */
s32 Pokedex_PlayCry(void) {
    func_8003BD3C(D_8A12FFB8 + 1);
    if (func_8003BECC() != 0) {
        do {
            BgStage_DrawFrame();
            Pokedex_DrawMenu(&D_8A1301A0, 0x10);
            func_80006780();
        } while (func_8003BECC() != 0);
    }
    return 2;
}

M2C_UNK func_80005B98(M2C_UNK);                     /* extern */
M2C_UNK func_8000661C(s32);                         /* extern */
M2C_UNK func_800067BC(M2C_UNK);                     /* extern */
M2C_UNK func_80006828(M2C_UNK, M2C_UNK *);          /* extern */
M2C_UNK func_8A1053E8(s32, s32, M2C_UNK, s32, s32); /* extern */
extern s32 D_8A12FFA8;
extern s32 D_8A12FFAC;
extern s32 D_8A12FFB8;
extern M2C_UNK Pokedex_DrawHabitatPage;

/**
 * Seen in play (2026-11-12): ぶんぷをみる opened the 3D Kanto map 「フシギダネのすみか」.
 */
void Pokedex_EnterAreaMapScreen(void) {
    func_80005B98(8);
    func_80006828(8, &Pokedex_DrawIndexScreen);
    func_800067BC(2);
    func_8000661C(D_8A12FFA0);
    func_800067BC(2);
    func_8A1053E8(D_8A12FFB8 + 1, D_8A12FFA8, 0x70800, D_8A12FFAC, 0x4B000);
    func_80005B98(8);
    func_80006828(0xA, &Pokedex_DrawHabitatPage);
}

/** Fades out and leaves the Pokedex area map screen. */
void Pokedex_ExitAreaMapScreen(void) {
    StageFade_Start(8);
    BgStage_RunUntilCondition(8, Pokedex_DrawAreaMapFrame);
    StageLoader_RunFrames(2);
    StageContext_SaveAndSwitch(D_8A12FF9C);
    Pokedex_ExitAreaMapPool();
    StageFade_Start(8);
    BgStage_RunUntilCondition(0xA, Pokedex_RedrawAreaMapTransition);
}

/** Runs the Pokedex area map screen. */
s32 Pokedex_ShowAreaMapScreen(void) {
    s32 var_s0 = 3;

    Pokedex_EnterAreaMapScreen();

    while (var_s0 == 3) {
        Cont_StartReadInputs();
        Cont_ReadInputs();
        Input_ResetRepeatState();
        Pokedex_DrawAreaMapFrame(0);
        if (Pokedex_CheckAreaMapExit() != 0) {
            var_s0 = 1;
        }
        BgStage_AdvanceFrame();
    }

    Audio_PlaySoundEffectById(SFX_MENU_BACK);
    Pokedex_ExitAreaMapScreen();
    return var_s0;
}

typedef struct Col8A101B30 { u8 r, g, b, a; } Col8A101B30;
extern s32 D_8A105800;
extern s32 D_8A105804;
/*
 * Second name for D_8A105800. The fade-out store in this function family
 * (also func_8200579C, func_8900429C, LabPCList_UpdateFade, func_8A101B30) does not
 * share the counter's address with the load before it, which only happens
 * when the two accesses name different symbols.
 */
extern s32 D_8A105800_2;
extern M2C_UNK D_8A12FD3C;
M2C_UNK GbSave_DrawSummaryBar(M2C_UNK, M2C_UNK *, M2C_UNK *, s32);
void func_8002C8D8(Col8A101B30*, Col8A101B30, f32);
s32 func_8A101B30(u8 arg0) {
    Col8A101B30 sp2C;
    M2C_UNK *var_a1;
    s32 n;

    n = D_8A105800;
    if (n >= 8) {
        D_8A105804 = 1;
    }
    if (D_8A105804 != 0) {
        n--;
        D_8A105800_2 = n;
    }
    BgStage_DrawFrame();
    if (D_8A130230 == -1) {
        var_a1 = NULL;
    } else {
        var_a1 = &D_8A130238;
    }
    GbSave_DrawSummaryBar(0, var_a1, &D_8A12FD3C, D_8A130230);
    n = D_8A105800;
    func_8002C8D8(&sp2C, *(Col8A101B30*)&D_8A1057D0, n / (f64)8.0f);
    Ui_DrawTintedScreenBackground(0x38, 0x1E0, sp2C.r, sp2C.g, sp2C.b);
    if (D_8A105804 == 0) {
        n = D_8A105800;
        n++;
        D_8A105800 = n;
    }
    return 0;
}

/** Runs the Pokedex entry flow. */
void Pokedex_RunEntryFlow(void) {
    s32 var_v0 = 1;

    while (var_v0 != 0) {
        switch (var_v0) {
            case 1:
                var_v0 = Pokedex_RunIndexScreen();
                break;

            case 2:
                var_v0 = Pokedex_ShowEntryMenu();
                break;

            case 3:
                var_v0 = Pokedex_ShowEntry();
                break;

            case 4:
                var_v0 = Pokedex_PlayCry();
                break;

            case 5:
                var_v0 = Pokedex_ShowAreaMapScreen();
                break;
        }
    }
}

/** Returns the highest species index that has been seen. */
s32 Pokedex_GetHighestSeenSpeciesIndex(void) {
    s32 i;

    for (i = 151; i > 0; i--) {
        if (GbSave_GetSpeciesProgressLevel(D_8A12FFB0, i) != 0) {
            break;
        }
    }

    return i;
}

/** Allocates and initializes the framebuffers for the Pokedex. */
void Pokedex_InitFramebuffers(void) {
    u32 sp34;
    u32 sp30;
    u32 sp2C;
    DepthBuffer* sp28;

    sp28 = main_pool_alloc(sizeof(DepthBuffer), 0);

    sp34 = D_8A12FF9C->renderTargets[0]->img_p;
    D_8A12FFA8 = D_8A12FF9C->renderTargets[0]->img_p + 0x25800;
    sp30 = D_8A12FF9C->renderTargets[1]->img_p;
    D_8A12FFAC = D_8A12FF9C->renderTargets[1]->img_p + 0x25800;
    sp2C = D_8A12FF9C->renderTargets[1]->img_p + 0x70800;

    D_8A12FFA0->renderTargets[0] = main_pool_alloc(sizeof(DepthBuffer), 0);
    D_8A12FFA0->renderTargets[1] = main_pool_alloc(sizeof(DepthBuffer), 0);

    GfxImage_Initialize(D_8A12FFA0->renderTargets[0], 0, 2, 0x140, 0xF0, sp34);
    GfxImage_Initialize(D_8A12FFA0->renderTargets[1], 0, 2, 0x140, 0xF0, sp30);
    GfxImage_Initialize(sp28, 0, 2, 0x140, 0xF0, sp2C);
    GfxImage_AttachDepthBuffer(D_8A12FFA0->renderTargets[0], sp28);
    GfxImage_AttachDepthBuffer(D_8A12FFA0->renderTargets[1], sp28);
}

void func_80027FF8(void*, s32);
void Pokedex_InitIndexWindows(void*);

/**
 * Loads the GB save summary and sets up the index windows.
 * Seen in play (2026-11-12): loaded the save summary and opened ずかんもくじ.
 */
void Pokedex_InitIndexScreen(void) {
    D_8A130230 = func_80025BD8();
    if (D_8A130230 != -1) {
        func_80027FF8(&D_8A130238, D_8A130230);
    }
    Pokedex_InitIndexWindows(&D_8A12FFC0);
}

extern u32 D_86806CD0[];
extern s32 D_8A12FFB4;
extern s32 D_8A12FFB8;
extern u8 D_81000000[];
extern u8 D_0015B1A0[];
extern u8 D_0015E220[];
extern u8 D_01000000[];
extern u8 D_002E0BE0[];
extern u8 D_002E2B90[];
extern u8 D_04000000[];
extern u8 D_00400F70[];
extern u8 D_004076E0[];
extern u8 D_88000000[];
extern u8 D_00235D70[];
extern u8 D_00238BD0[];
void Pokedex_InitIndexScreen(void);
s32 func_8A101B30(u8);

/**
 * Entry point of the Pokedex: reads the GB save, allocates the stage and framebuffers, and rebuilds the seen bitfield.
 * Seen in play (2026-11-13) ran when ずかん > ぶんぷをみる was opened for a second species in the same
 * visit, as the habitat map loaded.
 * @unverified Name and comment guessed from the code.
 */
s32 Pokedex_Init(s32 arg0, s32 arg1) {
    D_8A12FFB0 = GbSave_GetActivePort();
    D_8A12FFB4 = Pokedex_GetHighestSeenSpeciesIndex() - 1;
    D_8A12FFB8 = 0;

    main_pool_push_state('BOOK');

    D_8A12FF9C = StageContext_GetCurrent();
    D_8A12FFA0 = StageContext_Allocate(0, 1, 2, 1, 2, 0);
    Pokedex_InitFramebuffers();
    GbSave_RebuildHeldSpecies(D_8A12FFB0);
    Font_Init(0x3D, 0);
    D_8A12FFA4 = PokeIcon_AllocFramebuffers(1);
    PokeIcon_OpenModelArchives();

    Fragment_Load(((((u32)D_81000000) & 0x0FF00000) >> 0x14) - 0x10, D_0015B1A0, D_0015E220);
    Asset_LoadToSegment(((u32)D_01000000 & 0x0F000000) >> 0x18, D_002E0BE0, D_002E2B90, 0);
    Asset_LoadToSegment(((u32)D_04000000 & 0x0F000000) >> 0x18, D_00400F70, D_004076E0, 0);

    StageLoader_UpdateSegments();
    ModelRenderer_InitDisplayRoots();
    Pokedex_InitIndexScreen();
    BgStage_RunUntilCondition(8, func_8A101B30);
    Pokedex_RunEntryFlow();
    BgStage_RunUntilCondition(8, func_8A101B30);
    StageLoader_WaitForRetrace();
    Font_Free();

    main_pool_pop_state('BOOK');

    Fragment_QueueCall(((((u32)D_88000000) & 0x0FF00000) >> 0x14) - 0x10, D_00235D70, D_00238BD0, 0, 0);
    return 0x8040;
}
