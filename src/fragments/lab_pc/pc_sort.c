/* Stadium Zero fragment015_238BD0. */
/* C ported from the Stadium 1 decomp: src/fragments/lab_pc_list/lab_pc_list_1D7B40.c. */

#include "lab_pc.h"
#include "asset_archive.h"
#include "font.h"
#include "fragments/lab_pokemon_list/lab_pokemon_list.h"
#include "graphics_textures.h"
#include "memory_main.h"
#include "pokemon_stats.h"
extern u8 D_8910D7D0[];

#include "m2c_macros.h"
void ScrollList_SetItems(void*, s32, void*);

void func_89004708(void);
void func_89004710(void);

/**
 * Writes the list `arg3` to deck (`arg0`, `arg1`, `arg2`) and closes it, flushing box decks 0x10..0x13.
 * Seen in play (2026-11-12) in せいとん: during PcSort_SaveChanges it ran for deck 0x20 (the party)
 * and 0x21 (GB box 1), the two lists the move changed.
 */
void PcSort_WriteDeck(s32 arg0, s32 arg1, s32 arg2, ByteMatrix* arg3) {
    DeckHandle* sp1C = Deck_Open(arg0, arg1, arg2, 1);

    Deck_WriteEntries(arg3->rows, arg3->count, sp1C);

    if ((arg0 == 0x10) || (arg0 == 0x11) || (arg0 == 0x12) || (arg0 == 0x13)) {
        Deck_CloseAndFlushBox(sp1C);
    } else {
        Deck_CloseAndFlush(sp1C);
    }
}

void func_89004708(void) {
}

void func_89004710(void) {
}

/**
 * Sets the 0x100 flag on each of the 13 box rows whose box is empty.
 * Seen in play (2026-11-13) ran once when the せいとん (sort) screen opened its list of 13 target boxes
 * (てもち, GBのボックス1 to 12).
 */
void PcSort_DisableEmptyBoxes(PcSortMenuWindow* arg0, ByteMatrix* arg1) {
    s32 i;

    for (i = 0; i < 13; i++) {
        if (arg1[i].count == 0) {
            arg0->menu.itemFlags[i] |= 0x100;
        }
    }
}

/**
 * Sets the 0x200 flag on the first row when the list holds exactly one Pokemon.
 * Seen in play (2026-11-13) ran once when A on the Pokémon sort screen's source (てもち) opened the
 * party list of three (フシ, ヒト, カメ); with three Pokémon the first row stayed selectable.
 */
void PcSort_DisableIfSingleMon(PcSortMenuWindow* arg0, ByteMatrix* arg1) {
    u16 *temp_v0;

    if (arg1->count == 1) {
        temp_v0 = arg0->menu.itemFlags;
        *temp_v0 |= 0x200;
    }
}

/**
 * Sets the 0x400 flag on each of the 13 box rows whose box is full.
 * Seen in play (2026-11-13) ran once when the Pokémon sort screen opened its target box list (てもち,
 * GBのボックス1 to 12, 64のボックス); no box was full, and no row was greyed out.
 */
void PcSort_DisableFullBoxes(PcSortMenuWindow* arg0, ByteMatrix* arg1) {
    s32 i;

    for (i = 0; i < 13; i++) {
        if (arg1[i].count == arg1[i].capacity) {
            arg0->menu.itemFlags[i] |= 0x400;
        }
    }
}

/**
 * Sets the disabled flag (1) on menu row `arg1`.
 * Seen in play (2026-11-12): greyed out てもち, the source, in the 「どこへいどうする？」 list.
 */
void PcSort_DisableRow(PcSortMenuWindow* arg0, s32 arg1) {
    u16 *temp_v0;

    temp_v0 = &arg0->menu.itemFlags[arg1];
    *temp_v0 |= 1;
}

void Ui_FillRectHighlighted(s32, s32, s32, s32, Color_RGBA8);
M2C_UNK func_8001AA9C(u8, u8, u8, u8);
extern Color_RGBA8 D_8900A5BC;
extern Color_RGBA8 D_8900A730[];
extern Color_RGBA8 D_800734B0[];
extern u8 D_800734A8[];
/**
 * Draws one menu row label with the selection highlight (dimmed when disabled).
 * Seen in play (2026-11-12): rows てもち, GBのボックス1-8, 64のボックス1-4 (dimmed when disabled).
 */
void PcSort_DrawMenuRow(s32 x, s32 y, char* str, UNUSED s32 index, s32 flags) {
    Color_RGBA8 color;
    UNUSED s32 pad[4]; // FAKE: stack padding

    if (flags & 0x10) {
        Ui_FillRectHighlighted(x + 3, y + 3, 0xD2, 0x16, D_8900A5BC);
    }
    Font_BeginTranslucentTextRendering();
    if (flags & 1) {
        color = ((Color_RGBA8*)&D_800734A8)[1];
        color.a = 0x4C;
    } else if (flags & 0x100) {
        color = D_8900A730[(flags & 2) ? 0 : 1];
    } else if (flags & 0x200) {
        color = D_8900A730[(flags & 2) ? 0 : 1];
    } else if (flags & 0x400) {
        color = D_800734B0[(flags & 2) ? 0 : 1];
    } else {
        color = ((Color_RGBA8*)&D_800734A8)[(flags & 2) ? 0 : 1];
    }
    func_8001AA9C(color.r, color.g, color.b, color.a);
    Font_SetActive(8, 0);
    Font_Printf(x + 8, y + 4, str);
    Font_EndTexturedTextRendering();
}

void Window_SetRect(s8*, s32, s32, s32, s32);
void Menu_Init(s8*, s32, s32, s32, s32, s32);
M2C_UNK func_80027804();
/**
 * Sets up a menu window whose height fits `arg4` rows.
 * Seen in play (2026-11-12): opened the 13-row 「どこからいどうする？」 box list.
 */
void PcSort_InitMenuWindow(PcSortMenuWindow* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 pad[2]; // FAKE: stack padding

    Window_SetRect((s8*)&arg0->window, arg1, arg2, 0xBC, (arg4 * 0x1C) + 0x14);
    arg0->window.state = 0;
    arg0->window.title = NULL;
    arg0->window.animTimer = 0;
    arg0->window.frame.style = 0;
    arg0->window.frame.color = D_8900A5BC;
    func_80027804((s8*)&arg0->items, arg3, arg4, arg4);
    Menu_Init((s8*)&arg0->menu, (s32)&arg0->items, (s32)arg0->itemFlags, (s32)PcSort_DrawMenuRow, 0xB0, 0x1C);
    arg0->menu.cursor = arg5;
    arg0->menu.options |= 0x10000;
}

s32 func_8002AE6C();                                /* extern */
M2C_UNK Menu_DrawItems(s8 *, s32, s32, M2C_UNK, s32); /* extern */

/**
 * Draws the menu window's items.
 * Seen in play (2026-11-12): drew that box list.
 */
void PcSort_DrawMenu(PcSortMenuWindow* arg0) {
    if (func_8002AE6C() == 0) {
        Menu_DrawItems(&arg0->menu, arg0->window.frame.x + 6, arg0->window.frame.y + 0xA, 0xFFEF, 0);
    }
}

s32 Menu_UpdateCursorSkipDisabled(void*);
s32 func_8002BC14(s32);
M2C_UNK func_8003F6AC(M2C_UNK);
extern s32 D_800603C0;
/**
 * Moves the menu cursor. Returns -1 on cancel, the 1-based row on confirm, otherwise 0.
 * Seen in play (2026-11-12): picked GBのボックス1 as the destination.
 */
s32 PcSort_UpdateMenuCursor(PcSortMenuWindow* arg0) {
    s32 sp1C = 0;
    s32 dir;

    if (Menu_UpdateCursorSkipDisabled(&arg0->menu) == 0) {
        dir = func_8002BC14(D_800603C0);
        if (dir == -1) {
            func_8003F6AC(3);
            sp1C = -1;
        } else if (dir == 1) {
            sp1C = arg0->menu.cursor + 1;
        }
    }
    return sp1C;
}

extern Gfx D_80060270[];
extern Color_RGBA8 D_8900A73C;
extern Color_RGBA8 D_8900A744;
extern char D_890189B0[];
void func_80029028(s32, s32, s32, s32, Color_RGBA8);
void Font_SetColorForFlags(s32);
/**
 * Draws a Pokemon list row with its level (Ｌ%d).
 * Seen in play (2026-11-12): ハナ L5, ヒノコ L5, カメ L5.
 */
void PcSort_DrawMonRow(s32 arg0, s32 arg1, u8* arg2, s32 arg3, s32 arg4) {
    BattleMon* mon = (BattleMon*)arg2;
    gSPDisplayList(gDisplayListHead++, D_80060270);
    func_80029028(arg0, arg1 + 1, 0xCC, 0x1A, D_8900A73C);
    func_80029028(arg0, arg1, 0xCC, 1, D_8900A744);
    func_80029028(arg0, arg1 + 0x1B, 0xCC, 1, D_8900A744);
    if (arg4 & 0x18) {
        Ui_FillRectHighlighted(arg0 + 3, arg1 + 3, 0xC6, 0x16, D_8900A5BC);
    }
    if (mon != NULL) {
        Font_BeginTranslucentTextRendering();
        Font_SetActive(8, 0);
        if ((mon->species.id > 0) && (mon->species.id < 0x98) && (D_80064C44[mon->species.id][8] & 1)) {
            func_8001AA9C(0xFF, 0xC8, 0xA0, 0xFF);
        } else {
            Font_SetColorForFlags(arg4);
        }
        Font_Printf(arg0 + 0xA, arg1 + 4, (char*)mon->nickname);
        Font_SetActive(4, 0);
        Font_Printf(arg0 + 0x83, arg1 + 8, D_890189B0, mon->level);
        Font_EndTexturedTextRendering();
    }
}

/**
 * Points the Pokemon list at a new set of entries.
 * Seen in play (2026-11-12): switched the right-hand list to the picked box.
 */
void PcSort_SetMonList(PcSortMonList* arg0, s32 arg1) {
    ScrollList_SetItems(&arg0->list, arg1, arg0->itemFlags);
}

void ScrollList_Init(void*, s32, void*, s32, void*, s32, s32);
void PcSort_DrawMonRow(s32, s32, u8*, s32, s32);

/**
 * Sets up the scrolling Pokemon list at (`arg1`, `arg2`) with PcSort_DrawMonRow rows.
 * Seen in play (2026-11-12): set up the てもち and GBのボックス1 lists.
 */
void PcSort_InitMonList(PcSortMonList* arg0, s32 arg1, s32 arg2, s32 arg3) {
    arg0->x = arg1;
    arg0->y = arg2;
    ScrollList_Init(&arg0->list, arg3, arg0->itemFlags, 6, PcSort_DrawMonRow, 0xCC, 0x1C);
    arg0->list.options |= 0x10000;
}

void func_8002F9D8(void *, s32, s32, s32, s32);
void ScrollList_DrawInlineItems(void *, s32, s32, s32, s32);
void Ui_DrawNumberZeroPadded(s32, s32, s32, s32);
void func_8001BCB4(s32, s32, s32, s32, void *, s32, s32);
extern Gfx D_80073450[];
extern u8 D_04011AB8[];
/**
 * Draws the scrolling Pokemon list (paged when 0x200 is set) and its scroll bar.
 * Seen in play (2026-11-12): the two lists with 03/06 and 00/30.
 */
void PcSort_DrawMonList(PcSortMonList* arg0, s32 arg1) {
    if (arg1 & 0x200) {
        func_8002F9D8(&arg0->list, arg0->x, arg0->y + 0x10, arg1 | 0xFFED, 0);
    } else {
        ScrollList_DrawInlineItems(&arg0->list, arg0->x, arg0->y + 0x10, arg1 | 0xFFED, 0);
    }
    Ui_DrawNumberZeroPadded(arg0->x + 0x98, arg0->y + 0xBA, arg0->list.items->count, 2);
    Ui_DrawNumberZeroPadded(arg0->x + 0xB3, arg0->y + 0xBA, arg0->list.items->capacity, 2);
    gSPDisplayList(gDisplayListHead++, D_80073450);
    gDPSetCombineMode(gDisplayListHead++, G_CC_DECALRGBA, G_CC_DECALRGBA);
    func_8001BCB4(arg0->x + 0xAA, arg0->y + 0xBC, 8, 0xA, D_04011AB8, 8, 0);
}

s32 ScrollList_UpdateCursor(void*);
s32 func_80030230(void*);

/**
 * Navigate the selected menu mode, then report cancel or confirm input.
 * Seen in play (2026-11-12) in せいとん: handled the てもち list with the cursor on ハナ after the source
 * and destination were chosen.
 */
s32 PcSort_UpdateMonList(PcSortMonList* menu, u32 flags) {
    s32 result = 0;
    s32 moved;
    s32 action;

    if (flags & 0x200) {
        moved = func_80030230(menu);
    } else {
        moved = ScrollList_UpdateCursor(menu);
    }
    if (moved == 0) {
        action = func_8002BC14(D_800603C0);
        if (action == -1) {
            func_8003F6AC(3);
            result = -1;
        } else if (action == 1) {
            result = 1;
        }
    }
    return result;
}


void func_89005068(s32 arg0, M2C_UNK arg1, M2C_UNK arg2, M2C_UNK arg3, s32 arg4) {
    func_8002B054(arg2, arg4);
}

void GridMenu_Init(s8*, s8*, s8*, void*, s32, s32, s32);
void func_80027410(s8*, s8*, s32, s32, s32);
extern Color_RGBA8 D_8900A580[];
extern Color_RGBA8 D_8900A750;
extern Color_RGBA8 D_8900A754;
extern u8 D_8900BFC0[];
extern u8 D_8900DAD0[];
extern u8 D_8900E858[];
extern u8 D_8900F5E0[];
extern u8 D_89010368[];
extern u8 D_89011E78[];
extern char D_890189B8[];

/**
 * Sets up the ポケモンのせいり (organize Pokemon) window and its lists.
 * Seen in play (2026-11-12): opened ポケモンのせいり.
 */
void PcSort_InitOrganizeWindow(PcSortOrganizeWindow* arg0, s32 x, s32 y, ByteMatrix* arg3, s32* arg4) {

    Window_SetRect(&arg0->window, x, y, 0x234, 0x172);
    arg0->window.animTimer = 0;
    arg0->window.state = 0;
    arg0->window.frame.style = 0x801;
    arg0->window.title = D_890189B8;
    Window_SetRect(&arg0->footerFrame, arg0->window.frame.x + 6, arg0->window.frame.y + 0x100, arg0->window.frame.width - 0xC, 0x6C);
    arg0->footerFrame.style = 6;
    arg0->footerFrame.color = D_8900A750;
    arg0->footerFrame.color2 = D_8900A754;
    func_8002B018(&arg0->moveButton, x + 0xE1, y + 0x48, 0x36, 0x2A, 0x30, D_8900DAD0);
    arg0->moveButton.selectedColor = D_8900A580[2];
    arg0->moveButton.color = D_8900A580[3];
    arg0->moveButton.highlightColor = D_8900A5BC;
    func_8002B018(&arg0->backButton, x + 0x11D, y + 0x48, 0x36, 0x2A, 0x30, D_8900BFC0);
    arg0->backButton.selectedColor = D_8900A580[0];
    arg0->backButton.color = D_8900A580[1];
    arg0->backButton.highlightColor = D_8900A5BC;
    func_8002B018(&arg0->exchangeButton, x + 0xE1, y + 0x78, 0x36, 0x2A, 0x30, D_8900F5E0);
    arg0->exchangeButton.selectedColor = D_8900A580[6];
    arg0->exchangeButton.color = D_8900A580[7];
    arg0->exchangeButton.highlightColor = D_8900A5BC;
    func_8002B018(&arg0->reorderButton, x + 0x11D, y + 0x78, 0x36, 0x2A, 0x30, D_8900E858);
    arg0->reorderButton.selectedColor = D_8900A580[4];
    arg0->reorderButton.color = D_8900A580[5];
    arg0->reorderButton.highlightColor = D_8900A5BC;
    func_8002B018(&arg0->viewButton, x + 0xE1, y + 0xA8, 0x36, 0x2A, 0x30, D_89010368);
    arg0->viewButton.selectedColor = D_8900A580[8];
    arg0->viewButton.color = D_8900A580[9];
    arg0->viewButton.highlightColor = D_8900A5BC;
    func_8002B018(&arg0->releaseButton, x + 0x11D, y + 0xA8, 0x36, 0x2A, 0x30, D_89011E78);
    arg0->releaseButton.selectedColor = D_8900A580[12];
    arg0->releaseButton.color = D_8900A580[13];
    arg0->releaseButton.highlightColor = D_8900A5BC;
    func_80027410(&arg0->buttonTable, &arg0->moveButton, 0x2C, 6, 6);
    GridMenu_Init(&arg0->operationMenu, &arg0->buttonTable, &arg0->operationFlags, func_89005068, 2, 0, 0);
    arg0->rightBox = 1;
    arg0->leftBox = 0;
    PcSort_InitMonList(&arg0->leftList, arg0->window.frame.x + 0xE, arg0->window.frame.y + 0x2C, (s32)arg3);
    PcSort_InitMonList(&arg0->rightList, arg0->window.frame.x + 0x15A, arg0->window.frame.y + 0x2C, (s32)(arg3 + arg0->rightBox));
    arg0->boxTables = arg3;
    arg0->dirty = arg4;
    func_80027410(&arg0->partyView, arg3->rows, 0x50, arg3->capacity, 0);
    arg0->state = 1;
}

M2C_UNK func_8001A384(M2C_UNK, M2C_UNK);
M2C_UNK func_8001A944(s32, s32, s32);
M2C_UNK func_8001AB6C();
M2C_UNK func_8001ABBC();
void func_8001B884(s32, s32, s32, s32, void*, s32, s32);
void Font_SetColorForFlags(s32);
void Ui_FillRectPrimEnvColor(s32, s32, s32, s32, Color_RGBA8, Color_RGBA8);
s32 func_8002BC44(s32);
extern Gfx D_80073408[];
extern Gfx D_80073438[];
extern s32 D_8900A758[];
extern Color_RGBA8 D_8900A78C[2];
extern Color_RGBA8 D_8900A794[2];
extern void* D_89017A80[];
extern u8 D_89017A98[];
extern s32 D_89019114;

/**
 * Draws a box tab with its name, highlighted when selected.
 * Seen in play (2026-11-12): the てもち and GBのボックス1 tabs.
 */
void PcSort_DrawBoxTab(s32 arg0, s32 x, s32 y, s32 flags, u32 idx) {
    Color_RGBA8* col;

    if (flags & 2) {
        col = D_8900A78C;
    } else {
        col = D_8900A794;
    }
    Ui_FillRectPrimEnvColor(x, y, 0xCC, 0x1E, col[0], col[1]);
    if (idx != -1) {
        gSPDisplayList(gDisplayListHead++, D_80073408);
        switch (idx) {
            case 0:
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
                func_8001B884(x + 0x10, y + 2, 0x18, 0x1A, D_89017A80[func_8002BC44(D_89019114)], 0x18, 0x200000);
                break;
            case 9:
            case 10:
            case 11:
            case 12:
                func_8001B884(x + 2, y + 2, 0x28, 0x1A, D_89017A98, 0x30, 0x200000);
                break;
        }
        gSPDisplayList(gDisplayListHead++, D_80073438);
        func_8001AB6C();
        Font_SetColorForFlags(flags);
        func_8001A384(8, 0);
        func_8001A944(x + 0x2B, y + 5, D_8900A758[idx]);
        func_8001ABBC();
    }
}

typedef struct Slot890056A4 {
    s32 x;
    s32 y;
    s32 type;
    s32 iconX;
    void* tex;
} Slot890056A4;
s32 BattleMon_CountMoves(u8* arg0);
s32 BattleMon_GetMoveIndex(s32, s32);
void PcBox_DrawMoveName(s32, s32, s32, s32);
extern Slot890056A4 D_8900A79C[];
extern char D_89018AC4[];
extern char D_89018AD0[];
extern char D_89018ADC[];
extern char D_89018AE8[];
extern char D_89018AF4[];
extern char D_89018B00[];
extern char D_89018B08[];
extern char D_89018B0C[];
extern char D_89018B10[];
extern char D_89018B14[];
extern Gfx D_80060290[];
extern Gfx D_80060398[];

/**
 * Draws Attack, Defense, Speed, Special and HP:%3d (？？？？？ when unknown).
 * Seen in play (2026-11-12) in せいとん: drew ハナ's stats under the lists: こうげき 9, ぼうぎょ 9, すばやさ 9,
 * とくしゅ 11 and HP: 19.
 */
void PcSort_DrawMonStats(s32 x, s32 y, u8* mon) {
    s32 count;
    s32 i;
    char* name;

    count = BattleMon_CountMoves(mon);
    Font_BeginTranslucentTextRendering();
    func_8001AA9C(0xFF, 0xC8, 0xC8, 0xFF);
    Font_SetActive(4, 0);
    Font_Printf(x + 6, y + 0x56, D_89018AC4);
    Font_Printf(x + 0x91, y + 0x56, D_89018AD0);
    Font_Printf(x + 0x11C, y + 0x56, D_89018ADC);
    Font_Printf(x + 0x1A7, y + 0x56, D_89018AE8);
    func_8001AA9C(D_800734A8[0], D_800734A8[1], D_800734A8[2], D_800734A8[3]);
    Font_SetActive(8, 0);
    if ((mon[0] <= 0) || (mon[0] >= 0x98)) {
        name = D_89018AF4;
    } else {
        name = *(char**)D_80064C44[mon[0]];
    }
    Font_Printf(x + 8, y + 8, name);
    Font_Printf(x + 8, y + 0x24, D_89018B00, *(u16*)(mon + 0x26));
    Font_Printf(x + 0x46, y + 0x54, D_89018B08, *(u16*)(mon + 0x28));
    Font_Printf(x + 0xD1, y + 0x54, D_89018B0C, *(u16*)(mon + 0x2A));
    Font_Printf(x + 0x15C, y + 0x54, D_89018B10, *(u16*)(mon + 0x2C));
    Font_Printf(x + 0x1E7, y + 0x54, D_89018B14, *(u16*)(mon + 0x2E));
    for (i = 0; i < count; i++) {
        PcBox_DrawMoveName(D_8900A79C[i].x + x, D_8900A79C[i].y + y, BattleMon_GetMoveIndex((s32)mon, i), D_8900A79C[i].type);
    }
    Font_EndTexturedTextRendering();
    gSPDisplayList(gDisplayListHead++, D_80060290);
    for (i = 0; i < count; i++) {
        func_8001B884(D_8900A79C[i].iconX + x, D_8900A79C[i].y + y, 0x14, 0x14, D_8900A79C[i].tex, 0x14, 0x200000);
    }
    gSPDisplayList(gDisplayListHead++, D_80060398);
}

M2C_UNK func_8001A384(M2C_UNK, M2C_UNK);            /* extern */
M2C_UNK func_8001A944(s32, s32, s32);               /* extern */
M2C_UNK func_8001AA9C(u8, u8, u8, u8);              /* extern */
void Font_SetLineHeight(s32 arg0);                     /* extern */
M2C_UNK func_8001AB6C();                            /* extern */
M2C_UNK func_8001ABBC();                            /* extern */
extern u8 D_800734A8[];

/**
 * Draws `arg2` in the small font.
 * Seen in play (2026-11-12): the small 03/06 and 00/30 counts.
 */
void PcSort_DrawSmallText(s32 arg0, s32 arg1, s32 arg2) {
    func_8001AB6C();
    func_8001A384(0x10, 0);
    func_8001AA9C(D_800734A8[0], D_800734A8[1], D_800734A8[2], D_800734A8[3]);
    Font_SetLineHeight(0x2C);
    func_8001A944(arg0 + 0xC, arg1 + 0x14, arg2);
    func_8001ABBC();
}

extern s32 D_8900A7EC[];
extern s32 D_8900A804[];
extern s32 D_8900A81C[];
extern s32 D_8900A834[];
void LabItem_DrawTitleText(s32, s32, s32, s32);
void PcSort_DrawMonStats();

/**
 * Draws the help line for the organize window's current state.
 * Seen in play (2026-11-12): 「ポケモンをいどうする」, 「どこからいどうする？」 and 「どこへいどうする？」.
 */
void PcSort_DrawHelpText(s32* arg0) {
    s32 idx = arg0[0x170 / 4];
    s32** list;

    switch (arg0[0]) {
        case 1:
            LabItem_DrawTitleText(arg0[0x30 / 4] + 0x58, arg0[0x34 / 4] + 0x1A, D_8900A7EC[idx], D_8900A834[idx]);
            break;
        case 2:
            PcSort_DrawSmallText(arg0[0x30 / 4], arg0[0x34 / 4], D_8900A804[idx]);
            break;
        case 3:
            PcSort_DrawSmallText(arg0[0x30 / 4], arg0[0x34 / 4], D_8900A81C[idx]);
            break;
        case 4:
        case 6:
        case 7:
            if (arg0[0] == 7) {
                list = (s32**)&arg0[0x31C / 4];
            } else {
                list = (s32**)&arg0[0x294 / 4];
            }
            PcSort_DrawMonStats(arg0[0x30 / 4], arg0[0x34 / 4], ((s32*)list)[2] * 0x50 + *list[0]);
            break;
    }
}

void Window_DrawFrame(s8*);
void Ui_DrawTexturedDivider(s32, s32, s32, void*);
void Ui_DrawTexturedFrameDecal(s32, s32, s32, s32, void*);
void GridMenu_DrawInlineItems(s8*, s32, s32, s32, s32);
void TextBox_Draw(s8*);
extern u8 D_8007356C[];
extern u8 D_800735C4[];

/**
 * Draws the organize Pokemon window: frame, lists and help line.
 * Seen in play (2026-11-12): the ポケモンのせいり window.
 */
void PcSort_DrawOrganizeWindow(PcSortOrganizeWindow* arg0) {
    s32 pad[1]; // FAKE: stack padding
    s32 m1;
    s32 m2;
    s32 mode;

    if (func_8002AE6C(&arg0->window) == 0) {
        Window_DrawFrame(&arg0->footerFrame);
        gSPDisplayList(gDisplayListHead++, D_80060270);
        func_80029028(arg0->window.frame.x + 6, arg0->window.frame.y + 6, arg0->window.frame.width - 0xC, 8, D_8900A5BC);
        func_80029028(arg0->window.frame.x + 6, arg0->window.frame.y + 0xF4, arg0->window.frame.width - 0xC, 6, D_8900A5BC);
        func_80029028(arg0->window.frame.x + 6, arg0->window.frame.y + 0xE, 8, 0xE6, D_8900A5BC);
        func_80029028(arg0->window.frame.x + arg0->window.frame.width - 0xE, arg0->window.frame.y + 0xE, 8, 0xE6, D_8900A5BC);
        func_80029028(arg0->window.frame.x + 0xDA, arg0->window.frame.y + 0xE, 0x80, 0xE6, D_8900A5BC);
        Ui_DrawTexturedDivider(arg0->window.frame.x, arg0->footerFrame.y - 7, arg0->window.frame.width, D_8007356C);
        Ui_DrawTexturedFrameDecal(arg0->window.frame.x + 0xC, arg0->window.frame.y + 0xC, 0xD0, 0xEA, D_800735C4);
        Ui_DrawTexturedFrameDecal(arg0->window.frame.x + 0x158, arg0->window.frame.y + 0xC, 0xD0, 0xEA, D_800735C4);
        GridMenu_DrawInlineItems(&arg0->operationMenu, 0, 0, (arg0->state == 1) ? 2 : 0x10, 0);
        PcSort_DrawBoxTab((s32)arg0, arg0->window.frame.x + 0xE, arg0->window.frame.y + 0xE, 0, arg0->leftBox);
        PcSort_DrawBoxTab((s32)arg0, arg0->window.frame.x + 0x15A, arg0->window.frame.y + 0xE, 0, arg0->rightBox);
        m1 = 0xFDED;
        m2 = 0xFDED;
        mode = arg0->state;
        switch (mode) {
            case 4:
            case 6:
                m1 = 0xFDEF;
                break;
            case 5:
                m2 = 0xFFED;
            case 7:
                m1 = 0xFDFD;
                m2 |= 2;
                break;
        }
        PcSort_DrawMonList(&arg0->leftList, m1);
        PcSort_DrawMonList(&arg0->rightList, m2);
        if ((arg0->state == 2) || (arg0->state == 0xA)) {
            PcSort_DrawMenu(&arg0->sourceBoxWindow);
        }
        if ((arg0->state == 3) || (arg0->state == 0xB)) {
            PcSort_DrawMenu(&arg0->targetBoxWindow);
        }
        PcSort_DrawHelpText((s32*)arg0);
        if ((arg0->state == 0xA) || (arg0->state == 0xB) || (arg0->state == 0xC) || (arg0->state == 0xD)) {
            TextBox_Draw(&arg0->textBox);
        }
    }
}

void func_89000020(void* arg0, void* arg1);
void LabList_RemoveSelectedEntry(void*);

/**
 * Moves the selected Pokemon into the destination box and marks both boxes changed.
 * Seen in play (2026-11-12) in せいとん > ポケモンをいどうする: moving ハナ (フシギダネ) from てもち into GBのボックス1
 * changed the counts from 03/06 and 00/30 to 02/06 and 01/30.
 */
void PcSort_MoveSelectedMon(PcSortOrganizeWindow* arg0) {
    arg0->dirty[arg0->targetBoxWindow.menu.cursor] = 1;
    arg0->dirty[arg0->sourceBoxWindow.menu.cursor] = arg0->dirty[arg0->targetBoxWindow.menu.cursor];
    func_89000020(&arg0->rightList, (void*)(arg0->leftList.list.items->rows + arg0->leftList.list.items->rowSize * arg0->leftList.list.cursor));
    LabList_RemoveSelectedEntry(&arg0->leftList);
}

void func_80027654(ByteMatrix* matrix, u8* out, s32 row);
void func_80027700(ByteMatrix* matrix, u8* in, s32 row);

/**
 * Swaps two entries of the source list.
 * Not reached in play (2026-11-13): did not run in a tour of the main menu, Pokédex, party, Lab,
 * registration, Free Battle setup and a COM battle (opening, a switch, running, a Pound turn).
 * @unverified Name and comment guessed from the code.
 */
void PcSort_SwapWithinList(PcSortOrganizeWindow* arg0) {
    u8 row[0x50];
    ByteMatrix* matrix = arg0->leftList.list.items;

    func_80027654(matrix, row, arg0->leftList.list.cursor);
    func_80027700(matrix, matrix->rows + matrix->rowSize * arg0->swapIndex, arg0->leftList.list.cursor);
    func_80027700(matrix, row, arg0->swapIndex);
    arg0->dirty[arg0->leftBox] = 1;
}


/**
 * Swaps the selected entries of the source and destination lists.
 * Not reached in play (2026-11-13): did not run in a tour of the main menu, Pokédex, party, Lab,
 * registration, Free Battle setup and a COM battle (opening, a switch, running, a Pound turn).
 * @unverified Name and comment guessed from the code.
 */
void PcSort_SwapBetweenLists(PcSortOrganizeWindow* arg0) {
    u8 row[0x50];
    ByteMatrix* matrix;

    func_80027654(arg0->rightList.list.items, row, arg0->rightList.list.cursor);
    matrix = arg0->leftList.list.items;
    func_80027700(arg0->rightList.list.items, matrix->rows + matrix->rowSize * arg0->leftList.list.cursor, arg0->rightList.list.cursor);
    func_80027700(arg0->leftList.list.items, row, arg0->leftList.list.cursor);
    arg0->dirty[arg0->rightBox] = 1;
    arg0->dirty[arg0->leftBox] = arg0->dirty[arg0->rightBox];
}

void LabList_RemoveSelectedEntry(void*);

/**
 * Removes the selected Pokemon from its box and marks the box changed.
 * Seen in play (2026-11-13) released フシギダネ in せいとん > ポケモンをにがす: てもち went from 03/06 to 02/06.
 */
void PcSort_ReleaseSelectedMon(PcSortOrganizeWindow* arg0) {
    LabList_RemoveSelectedEntry(&arg0->leftList);
    arg0->dirty[arg0->leftBox] = 1;
    arg0->state = (((arg0->leftBox == 0) ? 1 : 0) == arg0->leftList.list.items->count) ? 1 : 4;
}


/**
 * Shows the selected box's Pokemon in the destination list.
 * Seen in play (2026-11-12) in せいとん: after GBのボックス2 was chosen under 「どこへいどうする？」, it ran and that
 * box appeared as the destination list (00/30).
 */
void PcSort_OpenBox(PcSortOrganizeWindow* arg0) {
    s32 temp_v0;
    PcSortMonList* temp_a0;

    temp_v0 = arg0->targetBoxWindow.menu.cursor;
    temp_a0 = &arg0->rightList;
    arg0->rightBox = temp_v0;
    PcSort_SetMonList(temp_a0, (s32)(arg0->boxTables + temp_v0));
    arg0->state = 4;
}

void TextBox_Init(s8*, s8*, s32, s32, s32);
s32 Ui_CheckConfirmPressed(s8*);
void Menu_ClearItemFlags(s8*);
void Menu_SkipDisabledForward(s8*);
s32 GridMenu_UpdateCursor(s8*);
extern s8* D_8900A84C[];
extern s8 D_89018D8C[];
extern s8 D_89018DA4[];


/**
 * Runs the organize Pokemon window's state machine (move, swap, release).
 * Seen in play (2026-11-12): ran the source and destination picks.
 */
s32 PcSort_UpdateOrganizeWindow(PcSortOrganizeWindow* arg0) {
    s32 ret;
    s32 res;
    s32 next;
    u16 flags;
    u8 species;
    BattleMon* mon;

    ret = 0;
    next = 0;
    switch (arg0->state) {
        case 1:
            if (GridMenu_UpdateCursor(&arg0->operationMenu) == 0) {
                res = func_8002BC14(D_800603C0);
                if (res == -1) {
                    func_8003F6AC(3);
                    ret = -1;
                } else if (res == 1) {
                    if (arg0->operationMenu.cursor == 1) {
                        func_8003F6AC(3);
                        ret = -1;
                    } else {
                        func_8003F6AC(2);
                        next = 2;
                        if ((arg0->operationMenu.cursor == 3) || (arg0->operationMenu.cursor == 4) || (arg0->operationMenu.cursor == 5)) {
                            PcSort_SetMonList(&arg0->rightList, (s32)(&arg0->partyView));
                            arg0->rightBox = -1;
                        }
                    }
                }
            }
            break;
        case 2:
            res = PcSort_UpdateMenuCursor(&arg0->sourceBoxWindow);
            if (res == -1) {
                arg0->state = 1;
            } else if (res > 0) {
                flags = arg0->sourceBoxWindow.menu.itemFlags[arg0->sourceBoxWindow.menu.cursor];
                if (flags & 0x100) {
                    arg0->state = 0xA;
                    TextBox_Init(&arg0->textBox, D_8900A84C[arg0->operationMenu.cursor], 0, 1, 0);
                    func_8003F6AC(8);
                } else if (flags & 0x200) {
                    func_8003F6AC(8);
                    arg0->state = 0xA;
                    TextBox_Init(&arg0->textBox, D_89018D8C, 0, 1, 0);
                } else {
                    func_8003F6AC(2);
                    arg0->leftBox = arg0->sourceBoxWindow.menu.cursor;
                    PcSort_SetMonList(&arg0->leftList, (s32)(arg0->boxTables + arg0->sourceBoxWindow.menu.cursor));
                    if ((arg0->operationMenu.cursor == 3) || (arg0->operationMenu.cursor == 4) || (arg0->operationMenu.cursor == 5)) {
                        arg0->state = 4;
                    } else {
                        next = 3;
                    }
                }
            }
            break;
        case 3:
            res = PcSort_UpdateMenuCursor(&arg0->targetBoxWindow);
            if (res == -1) {
                next = 2;
            } else if (res > 0) {
                flags = arg0->targetBoxWindow.menu.itemFlags[arg0->targetBoxWindow.menu.cursor];
                if (flags & 0x100) {
                    func_8003F6AC(8);
                    arg0->state = 0xB;
                    TextBox_Init(&arg0->textBox, D_8900A84C[arg0->operationMenu.cursor], 0, 1, 0);
                } else if (flags & 0x400) {
                    func_8003F6AC(8);
                    arg0->state = 0xB;
                    TextBox_Init(&arg0->textBox, D_89018DA4, 0, 1, 0);
                } else {
                    func_8003F6AC(2);
                    PcSort_OpenBox(arg0);
                }
            }
            break;
        case 4:
            res = PcSort_UpdateMonList(&arg0->leftList, 0);
            if (res == -1) {
                arg0->state = 1;
            } else if (res == 1) {
                if (arg0->operationMenu.cursor == 0) {
                    func_8003F6AC(2);
                    arg0->state = 5;
                } else if (arg0->operationMenu.cursor == 2) {
                    func_8003F6AC(2);
                    arg0->state = 7;
                } else if (arg0->operationMenu.cursor == 3) {
                    func_8003F6AC(2);
                    arg0->leftList.list.itemFlags[arg0->leftList.list.cursor] |= 8;
                    arg0->swapIndex = arg0->leftList.list.cursor;
                    arg0->state = 6;
                } else if (arg0->operationMenu.cursor == 4) {
                    mon = arg0->leftList.list.cursor + *(BattleMon**)arg0->leftList.list.items;
                    if ((mon->species.id <= 0) || (mon->species.id >= 0x98)) {
                        func_8003F6AC(8);
                    } else {
                        func_8003F6AC(2);
                        ret = 2;
                    }
                } else {
                    mon = arg0->leftList.list.cursor + *(BattleMon**)arg0->leftList.list.items;
                    species = mon->species.id;
                    if ((species <= 0) || (species >= 0x98)) {
                        func_8003F6AC(8);
                    } else {
                        func_8003F6AC(2);
                        ret = 3;
                    }
                }
            }
            break;
        case 5:
            res = PcSort_UpdateMonList(&arg0->rightList, 0x200);
            if (res == -1) {
                arg0->state = 4;
            } else if (res == 1) {
                func_8003F6AC(0x18);
                PcSort_MoveSelectedMon(arg0);
                if ((((arg0->leftBox == 0) ? 1 : 0) == arg0->leftList.list.items->count) ||
                    (arg0->rightList.list.items->count == arg0->rightList.list.items->capacity)) {
                    arg0->state = 1;
                } else {
                    arg0->state = 4;
                }
            }
            break;
        case 6:
            res = PcSort_UpdateMonList(&arg0->leftList, 0);
            if (res == -1) {
                Menu_ClearItemFlags(&arg0->leftList);
                arg0->state = 4;
            } else if (res == 1) {
                func_8003F6AC(0x18);
                PcSort_SwapWithinList(arg0);
                Menu_ClearItemFlags(&arg0->leftList);
                arg0->state = 4;
            }
            break;
        case 7:
            res = PcSort_UpdateMonList(&arg0->rightList, 0);
            if (res == -1) {
                arg0->state = 4;
            } else if (res == 1) {
                func_8003F6AC(0x18);
                PcSort_SwapBetweenLists(arg0);
                arg0->state = 4;
            }
            break;
        case 10:
            if (Ui_CheckConfirmPressed(&arg0->textBox) == 1) {
                arg0->state = 2;
            }
            break;
        case 11:
            if (Ui_CheckConfirmPressed(&arg0->textBox) == 1) {
                arg0->state = 3;
            }
            break;
        case 12:
            if (Ui_CheckConfirmPressed(&arg0->textBox) == 1) {
                arg0->state = 4;
            }
            break;
        case 13:
            if (Ui_CheckConfirmPressed(&arg0->textBox) == 1) {
                arg0->state = 7;
            }
            break;
    }
    if (next > 0) {
        switch (next) {
            case 2:
                PcSort_InitMenuWindow(&arg0->sourceBoxWindow, arg0->window.frame.x + 0x25, arg0->window.frame.y - 0x14,
                              (s32)D_8900A758, 0xD, arg0->leftBox);
                PcSort_DisableEmptyBoxes(&arg0->sourceBoxWindow, arg0->boxTables);
                if ((arg0->operationMenu.cursor == 0) || (arg0->operationMenu.cursor == 5)) {
                    PcSort_DisableIfSingleMon(&arg0->sourceBoxWindow, arg0->boxTables);
                }
                break;
            case 3:
                PcSort_InitMenuWindow(&arg0->targetBoxWindow, arg0->window.frame.x + 0x173, arg0->window.frame.y - 0x14,
                              (s32)D_8900A758, 0xD, arg0->rightBox);
                if (arg0->operationMenu.cursor == 0) {
                    PcSort_DisableFullBoxes(&arg0->targetBoxWindow, arg0->boxTables);
                } else if (arg0->operationMenu.cursor == 2) {
                    PcSort_DisableEmptyBoxes(&arg0->targetBoxWindow, arg0->boxTables);
                }
                PcSort_DisableRow(&arg0->targetBoxWindow, arg0->leftBox);
                arg0->targetBoxWindow.menu.cursor = 0;
                Menu_SkipDisabledForward(&arg0->targetBoxWindow.menu);
                break;
        }
        arg0->state = next;
    }
    return ret;
}

s8 *PokeIcon_AllocFramebuffers(s32 arg0);
void PokeIcon_OpenModelArchives(void);
s32 func_80018F2C(s8*, s32, s32, s32, s32, s32, s32, s32);
void func_80027410(s8*, s8*, s32, s32, s32);
void func_89000448(s32, s32, s32, ByteMatrix*);
void PcSort_InitOrganizeWindow(PcSortOrganizeWindow*, s32, s32, ByteMatrix*, s32*);
extern u8 D_81000000[];
extern u8 D_0015B1A0[];
extern u8 D_0015E220[];
extern s32 D_89019108;
/**
 * Pushes the 'OTPC' pool state, opens the icon archives, and reads the boxes.
 * Seen in play (2026-11-12): ポケモンを いどうする opened the screen.
 */
void PcSort_Init(PcSortScreen* arg0, s32 arg1) {
    s32 i;

    main_pool_push_state('OTPC');
    arg0->iconFramebuffers = PokeIcon_AllocFramebuffers(1);
    arg0->monRenderer = (u16*)func_80018F2C(arg0->iconFramebuffers, 0x80, 0x78, 0, 0, 0x78, 0x78, 0);
    PokeIcon_OpenModelArchives();
    Fragment_Load(((((u32)D_81000000) & 0x0FF00000) >> 0x14) - 0x10, D_0015B1A0, D_0015E220);
    arg0->mode = arg1;
    func_80027410(&arg0->partyTable, arg0->partyMons, 0x50, 6, 0);
    for (i = 0; i < 8; i++) {
        func_80027410(&arg0->gbBoxTables[i], arg0->gbBoxMons[i], 0x50, 0x1E, 0);
    }
    for (i = 0; i < 4; i++) {
        func_80027410(&arg0->stadiumBoxTables[i], arg0->stadiumBoxMons[i], 0x50, 0x1E, 0);
    }
    func_89000448(0x20, D_89019108, 0, &arg0->partyTable);
    for (i = 0; i < 8; i++) {
        func_89000448(0x21, D_89019108, i, &arg0->gbBoxTables[i]);
    }
    for (i = 0; i < 4; i++) {
        func_89000448(0x11, 0, i, &arg0->stadiumBoxTables[i]);
    }
    arg0->dirty[0] = 0;
    i = 1;
    do {
        arg0->dirty[i] = 0;
        i++;
    } while (i != 13);
    PcSort_InitOrganizeWindow(&arg0->organizeWindow, 0x26, 0x53, &arg0->partyTable, arg0->dirty);
    arg0->state = 1;
}

M2C_UNK func_80002620(M2C_UNK);                     /* extern */

/**
 * Pops the 'OTPC' pool state.
 * Seen in play (2026-11-12): B left it for the せいとん menu.
 */
void PcSort_Free(s32 arg0) {
    func_80002620(0x4F545043);
}

void Ui_DrawTintedScreenBackground(s32, s32, s32, s32, s32);
void PcSort_DrawOrganizeWindow();
void SavePrompt_Draw(void*);
extern Color_RGB8 D_8900A5B8;

/**
 * Draws the Pokemon sorting screen for its current state, including the status window.
 * Seen in play (2026-11-12): drew ポケモンのせいり.
 */
void PcSort_DrawScreen(PcSortScreen* arg0) {
    BgStage_DrawFrame();
    Ui_DrawTintedScreenBackground(0x38, 0x1E0, D_8900A5B8.r, D_8900A5B8.g, D_8900A5B8.b);
    switch (arg0->state) {
        case 1:
            PcSort_DrawOrganizeWindow(&arg0->organizeWindow);
            break;
        case 2:
            PcSort_DrawOrganizeWindow(&arg0->organizeWindow);
            SavePrompt_Draw(arg0->savePrompt);
            break;
        case 3:
            PcSort_DrawOrganizeWindow(&arg0->organizeWindow);
            PcBox_DrawMonStatusWindow(&arg0->statusWindow);
            break;
        case 4:
            PcSort_DrawOrganizeWindow(&arg0->organizeWindow);
            PcBox_DrawMonStatusWindow(&arg0->statusWindow);
            break;
    }
}

M2C_UNK func_80023268(s32, u8, M2C_UNK);            /* extern */
extern s32 D_89019108;

/**
 * Requests the icon of each species in list `arg0`.
 * Seen in play (2026-11-13) ran when leaving せいとん with レポートしてやめる after moving フシギダネ and ヒトカゲ into
 * GBのボックス1.
 * @unverified Name and comment guessed from the code.
 */
void PcSort_LoadMonIcons(ByteMatrix* arg0) {
    s32 var_s1;
    u8 *var_s0;

    var_s0 = arg0->rows;
    var_s1 = 0;
    if (arg0->count > 0) {
        do {
            func_80023268(D_89019108, *var_s0, 3);
            var_s1 += 1;
            var_s0 += 0x50;
        } while (var_s1 < arg0->count);
    }
}

void func_80022118(s32);
void func_800230C4(s32);
s32 func_8002207C(s32);
void func_80022188(s32);
void func_800243B8(void);
void func_8002D7D4(s32);
/**
 * Writes the changed boxes back to the save and flushes it.
 * Seen in play (2026-11-12) in せいとん: レポートしてやめる after the move ran this, which wrote decks 0x20
 * and 0x21, and the Game Boy .sav then had party count 2 and current-box count 1.
 */
void PcSort_SaveChanges(PcSortScreen* arg0) {
    s32 dirty = 0;
    s32 i;
    s32 saved = 0;

    if (arg0->dirty[0] != 0) {
        dirty = 1;
    }
    for (i = 0; i < 8; i++) {
        if (arg0->dirty[1 + i] != 0) {
            dirty = 1;
            break;
        }
    }
    if (dirty != 0) {
        func_80022118(D_89019108);
    }
    if (arg0->dirty[0] != 0) {
        PcSort_WriteDeck(0x20, D_89019108, 0, &arg0->partyTable);
        PcSort_LoadMonIcons(&arg0->partyTable);
    }
    for (i = 0; i < 8; i++) {
        if (arg0->dirty[1 + i] != 0) {
            PcSort_WriteDeck(0x21, D_89019108, i, &arg0->gbBoxTables[i]);
            PcSort_LoadMonIcons(&arg0->gbBoxTables[i]);
        }
    }
    for (i = 0; i < 4; i++) {
        if (arg0->dirty[9 + i] != 0) {
            PcSort_WriteDeck(0x11, D_89019108, i, &arg0->stadiumBoxTables[i]);
            saved = 1;
        }
    }
    if (dirty != 0) {
        func_800230C4(D_89019108);
        if (func_8002207C(D_89019108) == 0) {
            func_8002D7D4(D_89019108);
            PcSort_DrawScreen(arg0);
        }
        func_80022188(D_89019108);
    }
    if (saved != 0) {
        func_800243B8();
    }
}

/**
 * Returns 1 when any of the 13 boxes changed.
 * Seen in play (2026-11-12) in せいとん: returned 1 after that move, when leaving opened 「ないようが
 * へんこうされています」.
 */
s32 PcSort_HasUnsavedChanges(PcSortScreen* arg0) {
    s32 i;

    for (i = 0; i < 13; i++) {
        if (arg0->dirty[i] != 0) {
            return 1;
        }
    }
    return 0;
}

void SavePrompt_Init(s8* arg0, s32 arg1, s32 arg2);
void Save_DrawReportingWindow(s8* arg0);
s32 SavePrompt_Update(s8* arg0);
s32 Audio_PlayCommand(u32 arg0, s32 arg1, s32 arg2);
s32 PcSort_UpdateOrganizeWindow(PcSortOrganizeWindow* arg0);
extern u8 D_89018DBC[];

/**
 * Runs the Pokemon organizer's state machine for one frame.
 * Seen in play (2026-11-12): ran ポケモンのせいり.
 */
s32 PcSort_UpdateScreen(PcSortScreen* arg0) {
    s32 ret = 0;
    s8* sub;
    u8* mon;
    s32 res;

    switch (arg0->state) {
        case 1:
            res = PcSort_UpdateOrganizeWindow(&arg0->organizeWindow);
            if (res == -1) {
                if (PcSort_HasUnsavedChanges(arg0) != 0) {
                    arg0->state = 2;
                    SavePrompt_Init(arg0->savePrompt, 0xCA, 0xAD);
                } else {
                    ret = 1;
                }
            } else if (res == 2) {
                mon = arg0->organizeWindow.leftList.list.cursor * 0x50 + *(u8**)arg0->organizeWindow.leftList.list.items;
                arg0->state = 3;
                PcBox_InitConfirmWindow(&arg0->statusWindow, 0x69, 0x7D, (s32)mon, 0,
                              D_800603C0, arg0->monRenderer);
            } else if (res == 3) {
                mon = arg0->organizeWindow.leftList.list.cursor * 0x50 + *(u8**)arg0->organizeWindow.leftList.list.items;
                arg0->state = 4;
                PcBox_InitConfirmWindow(&arg0->statusWindow, 0x69, 0x7D, (s32)mon,
                              (s32)D_89018DBC, D_800603C0, arg0->monRenderer);
                arg0->statusWindow.choice.cursor = 1;
            }
            break;
        case 2:
            sub = arg0->savePrompt;
            res = SavePrompt_Update(sub);
            if (res == -1) {
                arg0->state = 1;
            } else if (res > 0) {
                ret = 1;
                arg0->organizeWindow.window.animTimer = 7;
                switch (res) {
                    case 2:
                        break;
                    case 1:
                        Save_DrawReportingWindow(sub);
                        PcSort_SaveChanges(arg0);
                        break;
                }
            }
            break;
        case 3:
            res = func_8002BC14(D_800603C0);
            if ((res == -1) || (res == 1)) {
                func_8003F6AC(3);
                arg0->state = 1;
            }
            break;
        case 4:
            res = PcBox_UpdateConfirmCursor(&arg0->statusWindow);
            if (res == -1) {
                func_8003F6AC(3);
                arg0->state = 1;
            } else if (res == 1) {
                Audio_PlayCommand(0x57, 0, 0);
                PcSort_ReleaseSelectedMon(&arg0->organizeWindow);
                arg0->state = 1;
            }
            break;
    }
    return ret;
}
