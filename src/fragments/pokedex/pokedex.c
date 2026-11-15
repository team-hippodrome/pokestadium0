/* Stadium Zero fragment018_262620: ポケモンずかん (the Pokédex), main menu > ずかん. */
/* C ported from the Stadium 1 decomp: src/fragments/pokedex/pokedex_214920.c. */

#include "pokedex.h"
#include "display_object_textures.h"
#include "font.h"
#include "fragments/battle/battle.h"
#include "geo_render.h"
#include "graphics_textures.h"
#include "input.h"
#include "memory_main.h"
#include "model_renderer.h"
#include "pokemon_stats.h"
extern StageContext* sMenuStageContext;
extern StageContext* sAreaMapStageContext;
extern ModelLoadContext* sIconFramebuffers;
extern s32 sAreaMapPool;
extern s32 sAreaMapLoadBuffer;
extern s32 sGbPort;

#include "m2c_macros.h"

extern Gfx D_80060290[];
extern Gfx D_80060398[];
extern u8 D_04002BA8[];
extern u8 D_04002ED0[];
/**
 * Draws the 20x20 Poké Ball icon of an owned species at (x, y): the red ball (D_04002BA8) when `is_held`
 * (the species is in the cartridge's party or boxes, もっている), else the gray ball (D_04002ED0).
 * Seen in play (2026-11-14, crafted Green save): red ball beside 001 フシギダネ (in the party), gray balls
 * beside 004 ヒトカゲ, 007 ゼニガメ and 016 ポッポ (caught, not held); no icon for seen-only 010 キャタピー.
 */
void Pokedex_DrawOwnedIcon(s32 x, s32 y, s32 is_held) {
    gSPDisplayList(gDisplayListHead++, D_80060290);
    Gfx_DrawTextureRgba16(x, y, 20, 20, is_held ? D_04002BA8 : D_04002ED0, 0x14, 0x200000);
    gSPDisplayList(gDisplayListHead++, D_80060398);
}

s32 Species_GetKanaOrderEntry();

/**
 * Returns the 0-based dex index under the list cursor, mapping through the kana order (Species_GetKanaOrderEntry) when
 * the list is sorted アイウエオじゅん.
 * Seen in play (2026-11-12): データをみる opened the entry of the row under the cursor (No.001).
 */
s32 Pokedex_GetCursorDexIndex(PokedexListWindow* list_window) {
    s32 var_v1;

    if (list_window->sortByKana != 0) {
        var_v1 = Species_GetKanaOrderEntry(list_window->list.cursor + 1, list_window) - 1;
    } else {
        var_v1 = list_window->list.cursor;
    }
    return var_v1;
}

extern unk_D_80064C60 D_80064C60[];
extern Gfx D_80060270[];
extern Color_RGBA8 D_8A1057D4;
extern Color_RGBA8 D_8A1057D8;
extern char D_8A12FC30[];
void func_80029028(s32, s32, s32, s32, Color_RGBA8);
void Ui_FillRectHighlighted(s32, s32, s32, s32, Color_RGBA8);
void Font_SetColorForFlags(s32);
/**
 * ScrollList row callback of the ずかんもくじ list: draws row `row` at (x, y) as its number ("%03d"), and for a
 * seen species its name, plus the owned icon when caught (progress 2) or held (progress 3). `sort_by_kana`
 * points at the window's sortByKana; when set the row maps through the kana order.
 * Seen in play (2026-11-14): rows 001-008, and 023 アーボ, 024, 119, 133 イーブイ first after C-Right.
 */
void Pokedex_DrawListRow(s32 x, s32 y, char* item, s32 row, s32 flags, s32* sort_by_kana) {
    s32 sorted;
    UNUSED s32 pad[2]; // FAKE: stack padding
    s32 idx;
    s32 progress;

    sorted = *sort_by_kana;
    if (sorted != 0) {
        idx = Species_GetKanaOrderEntry(row + 1) - 1;
    } else {
        idx = row;
    }
    progress = GbSave_GetSpeciesProgressLevel(sGbPort, idx + 1);
    gSPDisplayList(gDisplayListHead++, D_80060270);
    func_80029028(x, y, 260, 1, D_8A1057D8);
    func_80029028(x, y + 35, 260, 1, D_8A1057D8);
    func_80029028(x, y + 1, 260, 34, D_8A1057D4);
    if (flags & 0x10) {
        Ui_FillRectHighlighted(x + 3, y + 3, 254, 30, D_8A1057D4);
    }
    if (progress == 2) {
        Pokedex_DrawOwnedIcon(x + 88, y + 8, 0);
    }
    if (progress == 3) {
        Pokedex_DrawOwnedIcon(x + 88, y + 8, 1);
    }
    Font_BeginTranslucentTextRendering();
    Font_SetColorForFlags(flags);
    Font_SetActive(8, 0);
    Font_Printf(x + 0x10, y + 8, D_8A12FC30, idx + 1);
    if (progress != 0) {
        Font_SetActive(0x10, 0);
        Font_Printf(x + 124, y + 6, D_80064C60[idx].unk_00);
    }
    Font_EndTexturedTextRendering();
}

M2C_UNK func_80027410(s8 *, M2C_UNK *, M2C_UNK, M2C_UNK, s32); /* extern */
M2C_UNK ScrollList_Init(s8 *, s8 *, s8 *, M2C_UNK, M2C_UNK *, s32, s32); /* extern */
extern M2C_UNK D_80064C5C;
extern M2C_UNK D_8A12FC38;

/**
 * Sets up the ずかんもくじ (index) list window, 272x366 at (x, y) and titled D_8A12FC38 (ずかんもくじ): a table
 * over the 151 0x1C-byte species entries of D_80064C5C and a scroll list of 8 visible rows drawn by
 * Pokedex_DrawListRow, starting in number order.
 * Seen in play (2026-11-14): called with (54, 85) as the Pokédex opened.
 */
void Pokedex_InitListWindow(PokedexListWindow* list_window, s32 x, s32 y) {
    Window_SetRect((s8 *)list_window, x, y, 272, 366);
    list_window->window.animTimer = 0;
    list_window->window.state = 0;
    list_window->window.frame.style = 0x801;
    list_window->window.title = (char*)&D_8A12FC38;
    func_80027410((s8*)&list_window->entries, &D_80064C5C, 0x1C, 0x97, 0x97);
    ScrollList_Init((s8*)&list_window->list, (s8*)&list_window->entries, (s8*)list_window->itemFlags, 8, &Pokedex_DrawListRow, 260, 36);
    list_window->sortByKana = 0;
    list_window->list.options |= 0x10000;
}

s32 func_8002AE6C();
s32 Ui_DrawTexturedDivider(s32, s32, s32, void*);
void func_80029028(s32, s32, s32, s32, Color_RGBA8);
void ScrollList_DrawInlineItems(void*, s32, s32, s32, s32);
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
 * Draws the ずかんもくじ list's rows (Pokedex_DrawListRow) and the sort bar under them: アイウエオじゅん
 * (kana order) or ばんごうじゅん (number order) with the C-Right button icon (D_04005890).
 * `flags` is ORed into the row flags (2 while the list has focus, 0x10 while the menu has it).
 * Seen in play (2026-11-14): the bar read ばんごうじゅん, and アイウエオじゅん after C-Right.
 */
void Pokedex_DrawListWindow(PokedexListWindow* list_window, u32 flags) {
    char* str;

    if (func_8002AE6C() == 0) {
        Ui_DrawTexturedDivider(list_window->window.frame.x, list_window->window.frame.y + 325, list_window->window.frame.width, &D_8007356C);
        ScrollList_DrawInlineItems(&list_window->list, list_window->window.frame.x + 6, list_window->window.frame.y + 22, flags | 0xFFED, (s32)&list_window->sortByKana);
        gSPDisplayList(gDisplayListHead++, D_80060270);
        func_80029028(list_window->window.frame.x + 6, list_window->window.frame.y + 332, list_window->window.frame.width - 12, 28, D_8A1057DC);
        Font_BeginTranslucentTextRendering();
        Gfx_SetEnvColor(D_800734A8[0], D_800734A8[1], D_800734A8[2], D_800734A8[3]);
        Font_SetActive(8, 0);
        Font_Printf(list_window->window.frame.x + 36, list_window->window.frame.y + 336, list_window->sortByKana ? D_8A12FC48 : D_8A12FC5C);
        Font_EndTexturedTextRendering();
        gSPDisplayList(gDisplayListHead++, D_80060290);
        Gfx_DrawTextureRgba16(list_window->window.frame.x + 216, list_window->window.frame.y + 336, 20, 20, D_04005890, 0x14, 0x200000);
        gSPDisplayList(gDisplayListHead++, D_80060398);
    }
}

extern s32 D_800603C0;
s32 ScrollList_UpdateCursor(unk_func_8820BE14_02C_038*);

/**
 * Moves the list cursor. Without a move, C-Right toggles the kana / number order, and B returns -1 and
 * A returns 1.
 * Seen in play (2026-11-14): D-Down moved the cursor, C-Right switched ばんごうじゅん to アイウエオじゅん
 * and back, A on a seen row opened the menu, A on unseen 009 only buzzed.
 */
s32 Pokedex_UpdateListCursor(PokedexListWindow* list_window) {
    s32 result;
    unk_func_8820BE14_02C_038* menu;
    s32 value;

    menu = (unk_func_8820BE14_02C_038*)&list_window->list;
    result = ScrollList_UpdateCursor(menu);
    if (result == 0) {
        value = *(u16*)(D_800603C0 + 8);
        if (value & 1) {
            Audio_PlaySoundEffectById(2);
            WidgetTree_SetScrollableGridIndexPreserveScroll(menu, 0);
            value = list_window->sortByKana;
            value = value == 0;
            list_window->sortByKana = value;
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
 * Sets up the counts window (みつけたかず / つかまえたかず / もっているかず), 248x104 at (x, y).
 * Seen in play (2026-11-14): called with (342, 114) as the Pokédex opened.
 */
void Pokedex_InitCountsWindow(Window* window, s32 x, s32 y) {
    Window_SetRect((s8*)window, x, y, 248, 104);
    window->animTimer = 0;
    window->title = 0;
    window->state = 0;
    window->frame.style = 0x1006;
    *(Rgba8A100620*)&window->frame.color = D_8A1057E0;
    *(Rgba8A100620*)&window->frame.color2 = D_8A1057E4;
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
 * Draws the counts window: みつけたかず (seen), つかまえたかず (caught) and もっているかず (held: in the
 * cartridge's party or boxes) from GbSave_CountSeenSpecies / CountOwnedSpecies / CountHeldSpecies.
 * Seen in play (2026-11-14): 20 / 5 / 1 for a save with 20 seen, 5 caught and Bulbasaur in the party.
 */
void Pokedex_DrawCounts(Window* window) {
    if (func_8002AE6C() == 0) {
        Font_BeginTranslucentTextRendering();
        Font_SetActive(8, 0);
        Gfx_SetEnvColor(0x9C, 0xCC, 0x98, 0xFF); // #9CCC98FF
        Font_Printf(window->frame.x + 14, window->frame.y + 14, D_8A12FC6C);
        Gfx_SetEnvColor(0x98, 0xCC, 0xCC, 0xFF); // #98CCCCFF
        Font_Printf(window->frame.x + 14, window->frame.y + 42, D_8A12FC7C);
        Gfx_SetEnvColor(0xCC, 0x98, 0x98, 0xFF); // #CC9898FF
        Font_Printf(window->frame.x + 14, window->frame.y + 70, D_8A12FC8C);
        Gfx_SetEnvColor(D_800734A8[0], D_800734A8[1], D_800734A8[2], D_800734A8[3]);
        Font_Printf(window->frame.x + 174, window->frame.y + 14, D_8A12FC9C, GbSave_CountSeenSpecies(sGbPort));
        Font_Printf(window->frame.x + 174, window->frame.y + 42, D_8A12FCA0, GbSave_CountOwnedSpecies(sGbPort));
        Font_Printf(window->frame.x + 174, window->frame.y + 70, D_8A12FCA4, GbSave_CountHeldSpecies(sGbPort));
        Font_EndTexturedTextRendering();
    }
}

extern Color_RGBA8 D_8A1057D4;
void Ui_FillRectHighlighted(s32, s32, s32, s32, Color_RGBA8);
void Font_SetColorForFlags(s32);

/**
 * Menu row callback of the action menu: draws `label` at (x, y), with the highlight when `flags` has 0x10.
 * Seen in play (2026-11-14): データをみる, なきごえ, ぶんぷをみる and やめる.
 */
void Pokedex_DrawActionMenuRow(s32 x, s32 y, char* label, s32 row, s32 flags) {
    if (flags & 0x10) {
        Ui_FillRectHighlighted(x + 3, y + 3, 162, 30, D_8A1057D4);
    }
    Font_BeginTranslucentTextRendering();
    Font_SetColorForFlags(flags);
    Font_SetActive(0x10, 0);
    Font_Printf(x + 12, y + 6, label);
    Font_EndTexturedTextRendering();
}

extern M2C_UNK D_8A1057E8;
M2C_UNK func_80027804();
/**
 * Sets up the action menu window, 180x168 at (x, y), with the 4 rows of D_8A1057E8 (データをみる "view data",
 * なきごえ "cry", ぶんぷをみる "view habitat", やめる "quit") drawn by Pokedex_DrawActionMenuRow.
 * Seen in play (2026-11-14): called with (390, 262) as the Pokédex opened.
 */
void Pokedex_InitActionMenuWindow(PokedexMenuWindow* menu_window, s32 x, s32 y) {
    s32 pad; // FAKE: stack padding

    Window_SetRect((s8*)menu_window, x, y, 180, 168);
    menu_window->window.animTimer = 0;
    menu_window->window.title = 0;
    menu_window->window.state = 0;
    menu_window->window.frame.style = 0x1000;
    menu_window->window.frame.color = D_8A1057D4;
    func_80027804((s8*)&menu_window->items, &D_8A1057E8, 4, 4);
    Menu_Init((s8*)&menu_window->menu, (s8*)&menu_window->items, (s8*)menu_window->itemFlags, &Pokedex_DrawActionMenuRow, 168, 36);
    menu_window->menu.options |= 0x10000;
}

s32 func_8002AE6C();                                /* extern */
M2C_UNK Menu_DrawItems(s8 *, s32, s32, s32, s32);  /* extern */

/**
 * Draws the action menu's rows; `flags` is ORed into the row flags (2 while it has focus).
 * Seen in play (2026-11-14): データをみる / なきごえ / ぶんぷをみる / やめる beside the list.
 */
void Pokedex_DrawActionMenu(PokedexMenuWindow* menu_window, s32 flags) {
    if (func_8002AE6C() == 0) {
        Menu_DrawItems((s8*)&menu_window->menu, menu_window->window.frame.x + 6, menu_window->window.frame.y + 12, flags | 0xFFED, 0);
    }
}

s32 func_8002BC14(s32);                             /* extern */
s32 Menu_UpdateCursor(s32);                             /* extern */

/**
 * Moves the action menu cursor; without a move returns Ui_GetSelectionDirection's result (1 for A, -1 for B).
 * Seen in play (2026-11-14): D-Down moved to なきごえ / ぶんぷをみる / やめる and A picked the row.
 */
s32 Pokedex_UpdateActionMenuCursor(PokedexMenuWindow* menu_window) {
    s32 temp_v0;
    s32 var_v1;

    temp_v0 = Menu_UpdateCursor(&menu_window->menu);
    var_v1 = temp_v0;
    if (temp_v0 == 0) {
        var_v1 = func_8002BC14(D_800603C0);
    }
    return var_v1;
}

/**
 * Sets up the データをみる (entry page) window, 552x348 at (x, y).
 * Seen in play (2026-11-14): called with (44, 84) when データをみる was picked.
 */
void Pokedex_InitEntryWindow(Window* window, s32 x, s32 y) {
    Window_SetRect((s8*)window, x, y, 552, 348);
    window->animTimer = 0;
    window->title = 0;
    window->state = 0;
    window->frame.style = 0x1001;
}

/**
 * Draws the rendered 3D model preview (a 244x210 RGBA16 image with a 256-pixel stride, `pixels`) at (x, y) in
 * 8-row strips, blended with `alpha`.
 * Seen in play (2026-11-14): the entry page's フシギダネ model at alpha 255 (caught); seen-only キャタピー
 * was drawn at alpha 100, see-through over the background.
 */
void Pokedex_DrawModelPreviewImage(s32 x, s32 y, s32 alpha, u8* pixels) {
    s32 i;

    gDPPipeSync(gDisplayListHead++);
    gDPSetCycleType(gDisplayListHead++, G_CYC_1CYCLE);
    gDPSetCombineLERP(gDisplayListHead++, 0, 0, 0, TEXEL0, TEXEL0, 0, ENVIRONMENT, 0, 0, 0, 0, TEXEL0, TEXEL0, 0, ENVIRONMENT, 0);
    gDPSetRenderMode(gDisplayListHead++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    gDPSetTexturePersp(gDisplayListHead++, G_TP_NONE);
    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, alpha); // #FFFFFF
    for (i = 0; i < 208; i += 8) {
        Gfx_DrawTextureRgba16(x, y, 244, 8, pixels, 0x100, 0);
        y += 8;
        pixels += 0x1000;
    }
    Gfx_DrawTextureRgba16(x, y, 244, 2, pixels, 0x100, 0);
    gDPPipeSync(gDisplayListHead++);
    gDPSetTexturePersp(gDisplayListHead++, G_TP_PERSP);
    gDPSetAlphaCompare(gDisplayListHead++, G_AC_NONE);
}

extern char D_8A12FCDC[];

/**
 * Prints `tenths` / 10 as "%3d." (D_8A12FCDC) at (x, y) and its last digit with Font_DrawCharAt 0x54 to the
 * right, giving the entry page's height and weight.
 * Seen in play (2026-11-14): たかさ 0.7m and おもさ 6.9kg for フシギダネ.
 */
void Pokedex_DrawTenthsValue(s32 x, s32 y, s32 tenths) {
    Font_Printf(x, y, D_8A12FCDC, tenths / 10);
    Font_DrawCharAt(x + 84, y, (tenths % 10) + 0x30);
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
extern s32 sSelectedDexIndex;
void Ui_DrawTexturedFrameDecal(s32, s32, s32, s32, u8*);

/**
 * Draws the right half of the データをみる page at (x, y) for sSelectedDexIndex: No.%03d, the name, the
 * %sポケモン category, and たかさ (height, m) / おもさ (weight, kg), which read ??? until the species is caught.
 * Seen in play (2026-11-14): No.001 フシギダネ たねポケモン 0.7m 6.9kg; seen-only No.010 キャタピー
 * いもむしポケモン with ??? m and ??? kg.
 */
void Pokedex_DrawEntryInfo(s32 x, s32 y) {
    SpeciesInfo* entry = (SpeciesInfo*)((u8*)&D_80064C5C + sSelectedDexIndex * 0x1C);

    gSPDisplayList(gDisplayListHead++, D_80060270);
    func_80029028(x, y, 290, 210, D_8A1057D4);
    Ui_DrawTexturedFrameDecal(x + 8, y + 8, 274, 90, D_800735C4);
    Font_BeginTranslucentTextRendering();
    Gfx_SetEnvColor(0xFF, 0xFF, 0xFF, 0xFF); // #FFFFFFFF
    Font_EnableTwoCycleTexturing();
    Font_SetActive(0x20, 0);
    Gfx_SetPrimColor(0x96, 0x96, 0xFF, 0xFF); // #9696FFFF
    Font_Printf(x + 112, y + 56, entry->name);
    Font_SetActive(0x10, 0);
    Gfx_SetPrimColor(0x96, 0xFF, 0x96, 0xFF); // #96FF96FF
    Font_Printf(x + 8, y + 106, D_8A12FCE4, entry->category);
    Gfx_SetPrimColor(0xFF, 0xFF, 0x96, 0xFF); // #FFFF96FF
    Font_Printf(x + 13, y + 142, D_8A12FCF0);
    Gfx_SetPrimColor(0xFF, 0x96, 0x96, 0xFF); // #FF9696FF
    Font_Printf(x + 13, y + 178, D_8A12FCF8);
    Font_DisableTwoCycleTexturing();
    Gfx_SetEnvColor(D_800734A8[0], D_800734A8[1], D_800734A8[2], D_800734A8[3]);
    Font_Printf(x + 18, y + 18, D_8A12FD00);
    Font_Printf(x + 78, y + 18, D_8A12FD04, entry->dexNumber);
    if (GbSave_GetSpeciesProgressLevel(sGbPort, entry->dexNumber) >= 2) {
        Pokedex_DrawTenthsValue(x + 121, y + 142, entry->heightTenths);
        Pokedex_DrawTenthsValue(x + 121, y + 178, entry->weightTenths);
    } else {
        Font_Printf(x + 121, y + 142, D_8A12FD0C);
        Font_Printf(x + 121, y + 178, D_8A12FD10);
    }
    Font_Printf(x + 225, y + 142, D_8A12FD14);
    Font_Printf(x + 225, y + 178, D_8A12FD18);
    Font_EndTexturedTextRendering();
}

typedef struct Rgba8A100F20 { u8 r, g, b, a; } Rgba8A100F20;
void Ui_FillRectPrimEnvColor(s32, s32, s32, s32, Rgba8A100F20, Rgba8A100F20);
extern u8 D_8A1057F8[];
extern u8 D_8A1057FC[];
extern char D_8A12FD1C[];
extern s32 sSelectedDexIndex;
/**
 * Draws the description box of the データをみる page at (x, y): the species' dex text once it is caught,
 * else ??? (D_8A12FD1C).
 * Seen in play (2026-11-14): フシギダネ's 「せなかの きゅうこんのような ふくろは...」; ??? for seen-only キャタピー.
 */
void Pokedex_DrawEntryDescription(s32 x, s32 y) {
    SpeciesInfo* entry = (SpeciesInfo*)((u8*)&D_80064C5C + sSelectedDexIndex * 0x1C);

    Ui_FillRectPrimEnvColor(x, y, 540, 120, *(Rgba8A100F20 *)D_8A1057F8, *(Rgba8A100F20 *)D_8A1057FC);
    Font_BeginTranslucentTextRendering();
    Font_SetActive(0x10, 0);
    Font_SetLineHeight(36);
    if (GbSave_GetSpeciesProgressLevel(sGbPort, entry->dexNumber) >= 2) {
        Font_Printf(x + 42, y + 12, entry->description);
    } else {
        Font_Printf(x + 42, y + 12, D_8A12FD1C);
    }
    Font_EndTexturedTextRendering();
}

s32 Ui_DrawTexturedDivider(s32, s32, s32, void*);
s32 Ui_DrawFrameLeftCorners(s32, s32, s32, void*);
s32 Ui_DrawImageInStrips(void*, s32, s32);
s32 Window_DrawAnimatedFrame();
extern u8 D_8007356C;
extern u8 D_8A11FC18;

/**
 * Draws the データをみる page window: its frame, Pokedex_DrawEntryInfo and Pokedex_DrawEntryDescription, and
 * while the window is open (state 1 or 2) the preview backdrop D_8A11FC18 with the model image `preview`
 * on top, opaque when `progress` (GbSave_GetSpeciesProgressLevel) is 2 or more (caught), else at alpha 100.
 * Seen in play (2026-11-14): フシギダネ's page, and キャタピー's see-through model when only seen.
 */
void Pokedex_DrawEntryWindow(Window* window, s32 preview, s32 progress) {
    s32 temp_v0;

    if ((window->state != 2) && (Window_DrawAnimatedFrame() == 0)) {
        Ui_DrawTexturedDivider(window->frame.x, window->frame.y + 215, window->frame.width, &D_8007356C);
        Ui_DrawFrameLeftCorners(window->frame.x + 249, window->frame.y, 222, &D_8007356C);
        Pokedex_DrawEntryInfo(window->frame.x + 0x100, window->frame.y + 6);
        Pokedex_DrawEntryDescription(window->frame.x + 6, window->frame.y + 222);
    }
    temp_v0 = window->state;
    if ((temp_v0 == 1) || (temp_v0 == 2)) {
        Ui_DrawImageInStrips(&D_8A11FC18, 50, 90);
        Pokedex_DrawModelPreviewImage(50, 90, (progress >= 2) ? 0xFF : 0x64, preview);
    }
}

M2C_UNK Ui_DrawTintedScreenBackground(M2C_UNK, M2C_UNK, u8, u8, s32); /* extern */
extern Color_RGBA8 D_8A1057D0;

/**
 * Draws the Pokédex's green-tinted screen background (rows 56-480, color D_8A1057D0).
 * Seen in play (2026-11-14): the background behind ずかんもくじ and the データをみる page.
 */
void Pokedex_DrawBackground(void) {
    Ui_DrawTintedScreenBackground(56, 480, D_8A1057D0.r, D_8A1057D0.g, (s32)D_8A1057D0.b);
}

void Pokedex_InitListWindow(PokedexListWindow* list_window, s32 x, s32 y);
void Pokedex_InitCountsWindow(Window* window, s32 x, s32 y);
void Pokedex_InitActionMenuWindow(PokedexMenuWindow* menu_window, s32 x, s32 y);

/**
 * Sets up the ずかんもくじ screen's windows: the list at (54, 85), the counts at (342, 114) and the action
 * menu at (390, 262).
 * Seen in play (2026-11-14): ran once as the Pokédex opened.
 */
void Pokedex_InitIndexWindows(PokedexIndexScreen* screen) {
    Pokedex_InitListWindow(&screen->listWindow, 54, 85);
    Pokedex_InitCountsWindow(&screen->countsWindow, 342, 114);
    Pokedex_InitActionMenuWindow(&screen->menuWindow, 390, 262);
}

void BgStage_DrawFrame(void);                            /* extern */
M2C_UNK GbSave_DrawSummaryBar(M2C_UNK, M2C_UNK *, M2C_UNK *, s32); /* extern */
void Pokedex_DrawListWindow(PokedexListWindow*, u32);
void Pokedex_DrawCounts(Window*);
extern M2C_UNK D_8A12FD2C;
extern PokedexIndexScreen sIndexScreen;
extern M2C_UNK sCountsWindow;
extern M2C_UNK sActionMenuWindow;
extern s32 sSummaryPort;
extern M2C_UNK sPortSummary;

/**
 * BgStage_RunUntilCondition callback that draws the ずかんもくじ screen without input: the GB save bar
 * (ポケモンずかん), the list with its sort bar, the counts and the action menu.
 * Seen in play (2026-11-14): drew the index while the area map faded in (Pokedex_EnterAreaMapScreen) and
 * after it closed (Pokedex_ExitAreaMapScreen).
 */
s32 Pokedex_DrawIndexScreen(UNUSED u8 unused) {
    M2C_UNK *var_a1;

    BgStage_DrawFrame();
    Pokedex_DrawBackground();
    if (sSummaryPort == -1) {
        var_a1 = NULL;
    } else {
        var_a1 = &sPortSummary;
    }
    GbSave_DrawSummaryBar(0, var_a1, &D_8A12FD2C, sSummaryPort);
    Pokedex_DrawListWindow(&sIndexScreen.listWindow, 0x10);
    Pokedex_DrawCounts(&sCountsWindow);
    Pokedex_DrawActionMenu(&sActionMenuWindow, 2);
    return 0;
}

void Pokedex_DrawListWindow(PokedexListWindow*, u32);
/* Audio_PlaySoundEffectById, called by address with an s32 argument: battle.h's u32 prototype changes the
 * codegen of these callers (the constant 2 stays in a saved register). */
s32 Audio_PlaySystemSound(s32);
void Cont_StartReadInputs(void);
void Cont_ReadInputs(void);
M2C_UNK func_8000B2F4(s32);
/**
 * Pokédex screen 1, the ずかんもくじ list: runs frames until A on a seen species (returns 2, the action
 * menu) or B closes the windows (returns 0, quit). A on an unseen row only plays sound 8.
 * Seen in play (2026-11-14): ran while browsing the list; A on 001 went to the menu, A on 009 buzzed.
 */
s32 Pokedex_RunIndexScreen(void) {
    s32 temp_s0;
    s32 var_s4;

    var_s4 = 1;
    func_8000B2F4(D_800603C0);
    do {
        Cont_StartReadInputs();
        Cont_ReadInputs();
        Input_ResetRepeatState();
        if ((sIndexScreen.listWindow.window.state == 1) || (sIndexScreen.listWindow.window.state == 2U)) {
            temp_s0 = Pokedex_UpdateListCursor(&sIndexScreen.listWindow);
            sSelectedDexIndex = Pokedex_GetCursorDexIndex(&sIndexScreen.listWindow);
            if (temp_s0 == -1) {
                Audio_PlaySystemSound(3);
                sIndexScreen.listWindow.window.animTimer = 7;
                sIndexScreen.countsWindow.animTimer = 7;
                sIndexScreen.menuWindow.window.animTimer = 7;
            } else if (temp_s0 == 1) {
                if (GbSave_GetSpeciesProgressLevel(sGbPort, sSelectedDexIndex + 1) == 0) {
                    Audio_PlaySystemSound(8);
                } else {
                    Audio_PlaySystemSound(2);
                    var_s4 = 2;
                    sIndexScreen.menuWindow.menu.cursor = 0;
                }
            }
        }
        GeoRender_AdvanceFrameCounter();
        BgStage_DrawFrame();
        Pokedex_DrawBackground();
        Pokedex_DrawListWindow(&sIndexScreen.listWindow, 2);
        Pokedex_DrawCounts(&sCountsWindow);
        Pokedex_DrawActionMenu((s8*)&sActionMenuWindow, 0);
        BgStage_AdvanceFrame();
        if (sIndexScreen.listWindow.window.state == 4) {
            var_s4 = 0;
        }
    } while (var_s4 == 1);
    return var_s4;
}

extern s32 sSelectedDexIndex;
extern u8 sEntryWindow[];
/**
 * Acts on the action menu's result `menu_result` (1 = A, -1 = B; other values do nothing) and stores the
 * next screen of Pokedex_RunScreenLoop in `next_screen`: データをみる plays the cry, opens the entry
 * window and gives 3; なきごえ gives 4; ぶんぷをみる gives 5; やめる gives 0 (quit); B gives 1 (back to the
 * list). Returns 1 to switch screens at once, 2 to close the windows first, 0 to stay. A disabled row
 * (itemFlags bit 0) only plays sound 8.
 * Seen in play (2026-11-14): D-Down came in as 0x400 and did nothing; A on やめる left to the main menu.
 */
s32 Pokedex_HandleActionMenuResult(s32 menu_result, s32 *next_screen) {
    s32 ret = 0;

    if (menu_result == 1) {
        if (sIndexScreen.menuWindow.menu.itemFlags[sIndexScreen.menuWindow.menu.cursor] & 1) {
            Audio_PlaySystemSound(8);
        } else {
            switch (sIndexScreen.menuWindow.menu.cursor) {
                case 0:
                    Cry_PlayFromPokedex(sSelectedDexIndex + 1);
                    Pokedex_InitEntryWindow(sEntryWindow, 44, 84);
                    ret = 2;
                    *next_screen = 3;
                    break;
                case 1:
                    ret = 1;
                    *next_screen = 4;
                    break;
                case 2:
                    Audio_PlaySystemSound(2);
                    ret = 1;
                    *next_screen = 5;
                    break;
                case 3:
                    Audio_PlaySystemSound(3);
                    ret = 2;
                    *next_screen = 0;
                    break;
            }
        }
    } else if (menu_result == -1) {
        Audio_PlaySystemSound(3);
        ret = 1;
        *next_screen = 1;
    }
    return ret;
}

/*
 * Note for matching: the unused leading `pad` local moves sp50 down 4 bytes
 * to the ROM's stack offset (0x50); Input_ResetRepeatState must be declared void.
 */
void Cont_StartReadInputs(void);
void Cont_ReadInputs(void);
M2C_UNK func_8000B2F4(s32);
s32 Pokedex_HandleActionMenuResult(s32 menu_result, s32* next_screen);

/**
 * Pokédex screen 2, the action menu (データをみる / なきごえ / ぶんぷをみる / やめる) beside the list: runs
 * frames until Pokedex_HandleActionMenuResult picks the next screen, and returns it.
 * Note for matching: the unused leading `pad` local moves sp50 down 4 bytes to the ROM's stack offset (0x50);
 * Input_ResetRepeatState must be declared void.
 * Seen in play (2026-11-14): A on 001 opened it; each row led to its screen.
 */
s32 Pokedex_RunActionMenu(void) {
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
        Input_ResetRepeatState();
        if ((sIndexScreen.menuWindow.window.state == 1) || (sIndexScreen.menuWindow.window.state == 2)) {
            temp_v0 = Pokedex_UpdateActionMenuCursor((s32) &sActionMenuWindow);
            if (temp_v0 != 0) {
                temp_v0_2 = Pokedex_HandleActionMenuResult(temp_v0, &sp50);
                if (temp_v0_2 == 1) {
                    var_s3 = sp50;
                } else if (temp_v0_2 == 2) {
                    sIndexScreen.listWindow.window.animTimer = 7;
                    sIndexScreen.countsWindow.animTimer = 7;
                    sIndexScreen.menuWindow.window.animTimer = 7;
                }
            }
        }
        GeoRender_AdvanceFrameCounter();
        BgStage_DrawFrame();
        Pokedex_DrawBackground();
        Pokedex_DrawListWindow(&sIndexScreen.listWindow, 0x10);
        Pokedex_DrawCounts(&sCountsWindow);
        Pokedex_DrawActionMenu(&sActionMenuWindow, 2);
        BgStage_AdvanceFrame();
        if (sIndexScreen.listWindow.window.state == 4) {
            var_s3 = sp50;
        }
    } while (var_s3 == 2);
    return var_s3;
}

extern s32 sModelPreview;
extern u8 sEntryWindow[];
s32 func_800196F8(s32);
s32 Window_UpdateAnimation(Window* arg0);
void Pokedex_DrawEntryWindow(Window*, s32, s32);

/**
 * Draws one frame of the データをみる page: renders the model preview (PokeIcon_RenderPreview) and draws the
 * entry window with it. `progress` is the species' GbSave_GetSpeciesProgressLevel.
 * Seen in play (2026-11-14): every frame of フシギダネ's and キャタピー's pages.
 */
s32 Pokedex_DrawEntryScreen(s32 unused, s32 progress) {
    UNUSED s32 pad[4]; // FAKE: stack padding
    s32 sp1C;

    GeoRender_AdvanceFrameCounter();
    sp1C = func_800196F8(sModelPreview);
    BgStage_DrawFrame();
    if (Window_UpdateAnimation(sEntryWindow) != 0) {
        Pokedex_DrawBackground();
    }
    Pokedex_DrawEntryWindow(sEntryWindow, sp1C, progress);
    return 0;
}

/**
 * Renders the 80x80 icon of `species` (dex number) and copies it (0x3200 bytes, RGBA16) to `dest`.
 * Seen in play (2026-11-14): ポッポ's icon for the area map pins, loaded by Pokedex_LoadAreaMap.
 */
void Pokedex_LoadIcon(u8* dest, s32 species) {
    PokeIconRenderer* sp1C;
    void* sp18;

    MainPool_PushState('ICON');
    sp1C = PokeIcon_CreateRenderList(sIconFramebuffers, 1, 0x50, 0x50);
    sp18 = PokeIcon_GetImage(sp1C, 0);
    PokeIcon_SetSpeciesSlot(sp1C, 0, species, 0x9530);
    PokeIcon_ProcessAllSlots(sp1C, 0);
    StageLoader_RunFrames(2);
    osInvalDCache(sp18, 0x3200);
    _bcopy(sp18, dest, 0x3200);
    MainPool_PopState('ICON');
}

extern u8 D_8A105818;

/**
 * Pushes the 'PICT' pool state and creates the 244x210 3D model preview of `species` (dex number) in
 * sModelPreview, using `framebuffers` (sIconFramebuffers).
 * Matching note: the call result is stored straight into sModelPreview and sModelPreview is read back for
 * the second call, which the compiler folds into a register move; going through a local gives a different
 * store sequence.
 * Seen in play (2026-11-14): species 1 for フシギダネ's page; the model turned in the preview box.
 */
void Pokedex_CreateModelPreview(s32 framebuffers, s32 species) {
    MainPool_PushState(0x50494354);
    sModelPreview = (s32)PokeIcon_CreateModelPreview((ModelLoadContext*)framebuffers, 0x100, 0xD2, 0, 0, 0xF4, 0xD2, &D_8A105818);
    PokeIcon_SetPreviewSpecies((PokeModelPreview*)sModelPreview, species, 0x108D);
}

M2C_UNK func_800199E4(M2C_UNK *);                   /* extern */
extern M2C_UNK D_8A12FE30;

/**
 * Frees the model preview and pops the 'PICT' pool state.
 * Seen in play (2026-11-14): ran when B closed フシギダネ's page.
 */
void Pokedex_FreeModelPreview(void) {
    func_800199E4(&D_8A12FE30);
    MainPool_PopState(0x50494354);
}

void Cont_StartReadInputs(void);
void Cont_ReadInputs(void);
void Pokedex_CreateModelPreview(s32 framebuffers, s32 species);
extern s32 sSelectedDexIndex;

/**
 * Pokédex screen 3, the データをみる page of sSelectedDexIndex: creates the model preview, runs frames until
 * A or B (once the cry has finished) closes the window, frees the preview, and returns 1 (the list).
 * Seen in play (2026-11-14): フシギダネ's and キャタピー's pages; B went back to the list.
 */
s32 Pokedex_ShowEntry(void) {
    s32 temp_s1;

    Pokedex_CreateModelPreview((s32)sIconFramebuffers, sSelectedDexIndex + 1);
    temp_s1 = GbSave_GetSpeciesProgressLevel(sGbPort, sSelectedDexIndex + 1);
    do {
        Cont_StartReadInputs();
        Cont_ReadInputs();
        Input_ResetRepeatState();
        if (((sIndexScreen.entryWindow.state == 1) || (sIndexScreen.entryWindow.state == 2)) && (((Controller*)D_800603C0)->buttonPressed & 0xC000) && (Cry_IsPlaying() == 0)) {
            sIndexScreen.entryWindow.animTimer = 7;
            Audio_PlaySystemSound(3);
        }
        Pokedex_DrawEntryScreen(0, temp_s1);
        BgStage_AdvanceFrame();
    } while (sIndexScreen.entryWindow.state != 4);
    Pokedex_FreeModelPreview();
    sIndexScreen.listWindow.window.animTimer = 0;
    sIndexScreen.countsWindow.animTimer = 0;
    sIndexScreen.menuWindow.window.animTimer = 0;
    return 1;
}

void BgStage_DrawFrame(void);                            /* extern */
extern s32 sSelectedDexIndex;
extern M2C_UNK sActionMenuWindow;

/**
 * Pokédex screen 4, なきごえ: plays the cry of sSelectedDexIndex, redraws the menu until it ends, and
 * returns 2 (the action menu).
 * Seen in play (2026-11-14): なきごえ on フシギダネ.
 */
s32 Pokedex_PlayCry(void) {
    Cry_PlayFromPokedex(sSelectedDexIndex + 1);
    if (Cry_IsPlaying() != 0) {
        do {
            BgStage_DrawFrame();
            Pokedex_DrawActionMenu(&sActionMenuWindow, 0x10);
            BgStage_AdvanceFrame();
        } while (Cry_IsPlaying() != 0);
    }
    return 2;
}

M2C_UNK Pokedex_LoadAreaMap(s32 species, s32 pool, M2C_UNK pool_size, s32 load_buffer, s32 load_buffer_size); /* extern */
extern s32 sAreaMapPool;
extern s32 sAreaMapLoadBuffer;
extern s32 sSelectedDexIndex;

/**
 * Fades from the ずかんもくじ screen into the area map: switches to sAreaMapStageContext, loads the map for
 * sSelectedDexIndex (Pokedex_LoadAreaMap) and fades in with Pokedex_DrawAreaMapScreen.
 * Seen in play (2026-11-14): ぶんぷをみる on 016 ポッポ faded into 「ポッポのすみか」 over the 3D Kanto map.
 */
void Pokedex_EnterAreaMapScreen(void) {
    StageFade_Start(8);
    BgStage_RunUntilCondition(8, &Pokedex_DrawIndexScreen);
    StageLoader_RunFrames(2);
    StageContext_SaveAndSwitch(sAreaMapStageContext);
    StageLoader_RunFrames(2);
    Pokedex_LoadAreaMap(sSelectedDexIndex + 1, sAreaMapPool, 0x70800, sAreaMapLoadBuffer, 0x4B000);
    StageFade_Start(8);
    BgStage_RunUntilCondition(0xA, &Pokedex_DrawAreaMapScreen);
}

/**
 * Fades out of the area map, switches back to sMenuStageContext, frees the map ('MAPV' pool state) and
 * fades the ずかんもくじ screen back in.
 * Seen in play (2026-11-14): B on the zoomed-out map went back to the list at 016 ポッポ.
 */
void Pokedex_ExitAreaMapScreen(void) {
    StageFade_Start(8);
    BgStage_RunUntilCondition(8, Pokedex_DrawAreaMapScreen);
    StageLoader_RunFrames(2);
    StageContext_SaveAndSwitch(sMenuStageContext);
    Pokedex_ExitAreaMapPool();
    StageFade_Start(8);
    BgStage_RunUntilCondition(0xA, Pokedex_DrawIndexScreen);
}

/**
 * Pokédex screen 5, ぶんぷをみる (the area map of sSelectedDexIndex): runs frames until
 * Pokedex_HandleAreaMapInput reports B on the zoomed-out map, then leaves and returns 1 (the list).
 * Seen in play (2026-11-14): ポッポ's map; A zoomed in, D-Up / D-Down changed the area, R showed the GB map.
 */
s32 Pokedex_ShowAreaMapScreen(void) {
    s32 var_s0 = 3;

    Pokedex_EnterAreaMapScreen();

    while (var_s0 == 3) {
        Cont_StartReadInputs();
        Cont_ReadInputs();
        Input_ResetRepeatState();
        Pokedex_DrawAreaMapScreen(0);
        if (Pokedex_HandleAreaMapInput() != 0) {
            var_s0 = 1;
        }
        BgStage_AdvanceFrame();
    }

    Audio_PlaySoundEffectById(SFX_MENU_BACK);
    Pokedex_ExitAreaMapScreen();
    return var_s0;
}

typedef struct Col8A101B30 { u8 r, g, b, a; } Col8A101B30;
extern s32 sFadeTimer;
extern s32 sFadingOut;
/*
 * Second name for sFadeTimer. The fade-out store in this function family
 * (also FreeBattle_UpdateFade, LabTerminal_UpdateFade, LabPCList_UpdateFade, Pokedex_DrawFadeFrame) does not
 * share the counter's address with the load before it, which only happens
 * when the two accesses name different symbols.
 */
extern s32 D_8A105800_2;
extern M2C_UNK D_8A12FD3C;
M2C_UNK GbSave_DrawSummaryBar(M2C_UNK, M2C_UNK *, M2C_UNK *, s32);
void func_8002C8D8(Col8A101B30*, Col8A101B30, f32);
/**
 * BgStage_RunUntilCondition callback that fades the Pokédex background from gray to its green tint over 8
 * frames (sFadeTimer counting up), and on the next run back to gray (counting down, sFadingOut), with the
 * GB save bar on top.
 * Seen in play (2026-11-14): ran as the Pokédex opened, before ずかんもくじ appeared.
 */
s32 Pokedex_DrawFadeFrame(UNUSED u8 unused) {
    Col8A101B30 sp2C;
    M2C_UNK *var_a1;
    s32 n;

    n = sFadeTimer;
    if (n >= 8) {
        sFadingOut = 1;
    }
    if (sFadingOut != 0) {
        n--;
        D_8A105800_2 = n;
    }
    BgStage_DrawFrame();
    if (sSummaryPort == -1) {
        var_a1 = NULL;
    } else {
        var_a1 = &sPortSummary;
    }
    GbSave_DrawSummaryBar(0, var_a1, &D_8A12FD3C, sSummaryPort);
    n = sFadeTimer;
    func_8002C8D8(&sp2C, *(Col8A101B30*)&D_8A1057D0, n / (f64)8.0f);
    Ui_DrawTintedScreenBackground(56, 480, sp2C.r, sp2C.g, sp2C.b);
    if (sFadingOut == 0) {
        n = sFadeTimer;
        n++;
        sFadeTimer = n;
    }
    return 0;
}

/**
 * Runs the Pokédex's screens until one returns 0 (quit): 1 the ずかんもくじ list, 2 the action menu, 3 the
 * データをみる page, 4 なきごえ, 5 the ぶんぷをみる area map.
 * Seen in play (2026-11-14): went through all five screens, and やめる left to the main menu.
 */
void Pokedex_RunScreenLoop(void) {
    s32 var_v0 = 1;

    while (var_v0 != 0) {
        switch (var_v0) {
            case 1:
                var_v0 = Pokedex_RunIndexScreen();
                break;

            case 2:
                var_v0 = Pokedex_RunActionMenu();
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

/**
 * Returns the highest dex number (1-151) the active GB save has seen, or 0 if none.
 * Seen in play (2026-11-14): ran as the Pokédex opened.
 */
s32 Pokedex_GetHighestSeenSpeciesIndex(void) {
    s32 i;

    for (i = 151; i > 0; i--) {
        if (GbSave_GetSpeciesProgressLevel(sGbPort, i) != 0) {
            break;
        }
    }

    return i;
}

/**
 * Points sAreaMapStageContext's two 320x240 render targets at the menu stage's framebuffers, with a shared
 * depth buffer behind the second, and carves sAreaMapPool and sAreaMapLoadBuffer out of the space after them.
 * Seen in play (2026-11-14): ran as the Pokédex opened; the area map later rendered into these.
 */
void Pokedex_InitFramebuffers(void) {
    u32 sp34;
    u32 sp30;
    u32 sp2C;
    GfxImage* sp28;

    sp28 = MainPool_Alloc(sizeof(GfxImage), 0);

    sp34 = sMenuStageContext->renderTargets[0]->img_p;
    sAreaMapPool = sMenuStageContext->renderTargets[0]->img_p + 0x25800;
    sp30 = sMenuStageContext->renderTargets[1]->img_p;
    sAreaMapLoadBuffer = sMenuStageContext->renderTargets[1]->img_p + 0x25800;
    sp2C = sMenuStageContext->renderTargets[1]->img_p + 0x70800;

    sAreaMapStageContext->renderTargets[0] = MainPool_Alloc(sizeof(GfxImage), 0);
    sAreaMapStageContext->renderTargets[1] = MainPool_Alloc(sizeof(GfxImage), 0);

    GfxImage_Initialize(sAreaMapStageContext->renderTargets[0], 0, 2, 320, 240, sp34);
    GfxImage_Initialize(sAreaMapStageContext->renderTargets[1], 0, 2, 320, 240, sp30);
    GfxImage_Initialize(sp28, 0, 2, 320, 240, sp2C);
    GfxImage_AttachDepthBuffer(sAreaMapStageContext->renderTargets[0], sp28);
    GfxImage_AttachDepthBuffer(sAreaMapStageContext->renderTargets[1], sp28);
}

void func_80027FF8(void*, s32);
void Pokedex_InitIndexWindows(PokedexIndexScreen*);

/**
 * Builds the GB save bar's summary for the active port and sets up the ずかんもくじ windows.
 * Seen in play (2026-11-14): ran as the Pokédex opened; the bar read 1P ヒシト IDNo/04660.
 */
void Pokedex_InitIndexScreen(void) {
    sSummaryPort = GbSave_GetActivePort();
    if (sSummaryPort != -1) {
        func_80027FF8(&sPortSummary, sSummaryPort);
    }
    Pokedex_InitIndexWindows(&sIndexScreen);
}

extern u32 D_86806CD0[];
extern s32 sHighestSeenIndex;
extern s32 sSelectedDexIndex;
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
s32 Pokedex_DrawFadeFrame(u8 unused);

/**
 * Entry point of the Pokédex fragment (main menu > ずかん): picks the active GB save, pushes the 'BOOK' pool
 * state, sets up the area map stage and framebuffers, rebuilds the held-species bits, loads the font and
 * graphics, fades in (Pokedex_DrawFadeFrame), runs the screens, fades out, and queues the main menu
 * fragment (0x88000000). Both arguments are unused.
 * Seen in play (2026-11-14): its first call, GbSave_GetActivePort, returned into it as ずかん was entered,
 * and やめる came back to the main menu.
 */
s32 Pokedex_Main(UNUSED s32 arg0, UNUSED s32 arg1) {
    sGbPort = GbSave_GetActivePort();
    sHighestSeenIndex = Pokedex_GetHighestSeenSpeciesIndex() - 1;
    sSelectedDexIndex = 0;

    MainPool_PushState('BOOK');

    sMenuStageContext = StageContext_GetCurrent();
    sAreaMapStageContext = StageContext_Allocate(0, 1, 2, 1, 2, 0);
    Pokedex_InitFramebuffers();
    GbSave_RebuildHeldSpecies(sGbPort);
    Font_Init(0x3D, 0);
    sIconFramebuffers = PokeIcon_AllocFramebuffers(1);
    PokeIcon_OpenModelArchives();

    Fragment_Load(((((u32)D_81000000) & 0x0FF00000) >> 0x14) - 0x10, D_0015B1A0, D_0015E220);
    Asset_LoadToSegment(((u32)D_01000000 & 0x0F000000) >> 0x18, D_002E0BE0, D_002E2B90, 0);
    Asset_LoadToSegment(((u32)D_04000000 & 0x0F000000) >> 0x18, D_00400F70, D_004076E0, 0);

    StageLoader_UpdateSegments();
    ModelRenderer_InitDisplayRoots();
    Pokedex_InitIndexScreen();
    BgStage_RunUntilCondition(8, Pokedex_DrawFadeFrame);
    Pokedex_RunScreenLoop();
    BgStage_RunUntilCondition(8, Pokedex_DrawFadeFrame);
    StageLoader_WaitForRetrace();
    Font_Free();

    MainPool_PopState('BOOK');

    Fragment_QueueCall(((((u32)D_88000000) & 0x0FF00000) >> 0x14) - 0x10, D_00235D70, D_00238BD0, 0, 0);
    return 0x8040;
}
