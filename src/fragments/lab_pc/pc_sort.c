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

void PcSort_Unused1(void);
void PcSort_Unused2(void);

/**
 * Writes the list `table` to deck (`deck_type`, `port`, `index`) and closes it, flushing box decks 0x10..0x13.
 * Seen in play (2026-11-12) in せいとん: during PcSort_SaveChanges it ran for deck 0x20 (the party)
 * and 0x21 (GB box 1), the two lists the move changed.
 */
void PcSort_WriteDeck(s32 deck_type, s32 port, s32 index, ByteMatrix* table) {
    DeckHandle* sp1C = Deck_Open(deck_type, port, index, 1);

    Deck_WriteEntries(table->rows, table->count, sp1C);

    if ((deck_type == 0x10) || (deck_type == 0x11) || (deck_type == 0x12) || (deck_type == 0x13)) {
        Deck_CloseAndFlushBox(sp1C);
    } else {
        Deck_CloseAndFlush(sp1C);
    }
}

/**
 * Empty and never called: no jal, j or address word for it in any built fragment or the
 * resident code (scanned 2026-11-14).
 */
void PcSort_Unused1(void) {
}

/**
 * Empty and never called: no jal, j or address word for it in any built fragment or the
 * resident code (scanned 2026-11-14).
 */
void PcSort_Unused2(void) {
}

/**
 * Sets the 0x100 flag on each of the 13 box rows whose box is empty.
 * Seen in play (2026-11-13) ran once when the せいとん (sort) screen opened its list of 13 target boxes
 * (てもち, GBのボックス1-8 and 64のボックス1-4).
 */
void PcSort_DisableEmptyBoxes(PcSortMenuWindow* win, ByteMatrix* tables) {
    s32 i;

    for (i = 0; i < 13; i++) {
        if (tables[i].count == 0) {
            win->menu.itemFlags[i] |= 0x100;
        }
    }
}

/**
 * Sets the 0x200 flag on the first row when the list holds exactly one Pokemon.
 * Seen in play (2026-11-13) ran once when A on the Pokémon sort screen's source (てもち) opened the
 * party list of three (フシ, ヒト, カメ); with three Pokémon the first row stayed selectable.
 */
void PcSort_DisableIfSingleMon(PcSortMenuWindow* win, ByteMatrix* tables) {
    u16 *temp_v0;

    if (tables->count == 1) {
        temp_v0 = win->menu.itemFlags;
        *temp_v0 |= 0x200;
    }
}

/**
 * Sets the 0x400 flag on each of the 13 box rows whose box is full.
 * Seen in play (2026-11-13) ran once when the Pokémon sort screen opened its target box list (てもち,
 * GBのボックス1-8, 64のボックス1-4); no box was full, and no row was grayed out.
 */
void PcSort_DisableFullBoxes(PcSortMenuWindow* win, ByteMatrix* tables) {
    s32 i;

    for (i = 0; i < 13; i++) {
        if (tables[i].count == tables[i].capacity) {
            win->menu.itemFlags[i] |= 0x400;
        }
    }
}

/**
 * Sets the disabled flag (1) on menu row `row`.
 * Seen in play (2026-11-12): grayed out てもち, the source, in the 「どこへいどうする？」 list.
 */
void PcSort_DisableRow(PcSortMenuWindow* win, s32 row) {
    u16 *temp_v0;

    temp_v0 = &win->menu.itemFlags[row];
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
        Ui_FillRectHighlighted(x + 3, y + 3, 210, 22, D_8900A5BC);
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
 * Sets up a menu window whose height fits `count` rows.
 * Seen in play (2026-11-12): opened the 13-row 「どこからいどうする？」 box list.
 */
void PcSort_InitMenuWindow(PcSortMenuWindow* win, s32 x, s32 y, s32 names, s32 count, s32 cursor) {
    s32 pad[2]; // FAKE: stack padding

    Window_SetRect((s8*)&win->window, x, y, 188, (count * 28) + 20);
    win->window.state = 0;
    win->window.title = NULL;
    win->window.animTimer = 0;
    win->window.frame.style = 0;
    win->window.frame.color = D_8900A5BC;
    func_80027804((s8*)&win->items, names, count, count);
    Menu_Init((s8*)&win->menu, (s32)&win->items, (s32)win->itemFlags, (s32)PcSort_DrawMenuRow, 176, 28);
    win->menu.cursor = cursor;
    win->menu.options |= 0x10000;
}

s32 func_8002AE6C();                                /* extern */
M2C_UNK Menu_DrawItems(s8 *, s32, s32, M2C_UNK, s32); /* extern */

/**
 * Draws the menu window's items.
 * Seen in play (2026-11-12): drew that box list.
 */
void PcSort_DrawMenu(PcSortMenuWindow* win) {
    if (func_8002AE6C() == 0) {
        Menu_DrawItems(&win->menu, win->window.frame.x + 6, win->window.frame.y + 10, 0xFFEF, 0);
    }
}

s32 Menu_UpdateCursorSkipDisabled(void*);
s32 func_8002BC14(s32);
M2C_UNK Audio_PlaySystemSound(M2C_UNK);
extern s32 D_800603C0;
/**
 * Moves the menu cursor. Returns -1 on cancel, the 1-based row on confirm, otherwise 0.
 * Seen in play (2026-11-12): picked GBのボックス1 as the destination.
 */
s32 PcSort_UpdateMenuCursor(PcSortMenuWindow* win) {
    s32 sp1C = 0;
    s32 dir;

    if (Menu_UpdateCursorSkipDisabled(&win->menu) == 0) {
        dir = func_8002BC14(D_800603C0);
        if (dir == -1) {
            Audio_PlaySystemSound(3);
            sp1C = -1;
        } else if (dir == 1) {
            sp1C = win->menu.cursor + 1;
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
void PcSort_DrawMonRow(s32 x, s32 y, u8* row, s32 index, s32 flags) {
    BattleMon* mon = (BattleMon*)row;
    gSPDisplayList(gDisplayListHead++, D_80060270);
    func_80029028(x, y + 1, 204, 26, D_8900A73C);
    func_80029028(x, y, 204, 1, D_8900A744);
    func_80029028(x, y + 27, 204, 1, D_8900A744);
    if (flags & 0x18) {
        Ui_FillRectHighlighted(x + 3, y + 3, 198, 22, D_8900A5BC);
    }
    if (mon != NULL) {
        Font_BeginTranslucentTextRendering();
        Font_SetActive(8, 0);
        if ((mon->species.id > 0) && (mon->species.id < 152) && (D_80064C44[mon->species.id][8] & 1)) {
            func_8001AA9C(0xFF, 0xC8, 0xA0, 0xFF); // #FFC8A0FF
        } else {
            Font_SetColorForFlags(flags);
        }
        Font_Printf(x + 10, y + 4, (char*)mon->nickname);
        Font_SetActive(4, 0);
        Font_Printf(x + 131, y + 8, D_890189B0, mon->level);
        Font_EndTexturedTextRendering();
    }
}

/**
 * Points the Pokemon list at a new set of entries.
 * Seen in play (2026-11-12): switched the right-hand list to the picked box.
 */
void PcSort_SetMonList(PcSortMonList* list, s32 table) {
    ScrollList_SetItems(&list->list, table, list->itemFlags);
}

void ScrollList_Init(void*, s32, void*, s32, void*, s32, s32);
void PcSort_DrawMonRow(s32, s32, u8*, s32, s32);

/**
 * Sets up the scrolling Pokemon list at (`x`, `y`) with PcSort_DrawMonRow rows.
 * Seen in play (2026-11-12): set up the てもち and GBのボックス1 lists.
 */
void PcSort_InitMonList(PcSortMonList* list, s32 x, s32 y, s32 table) {
    list->x = x;
    list->y = y;
    ScrollList_Init(&list->list, table, list->itemFlags, 6, PcSort_DrawMonRow, 204, 28);
    list->list.options |= 0x10000;
}

void ScrollList_DrawSmoothScroll(void *, s32, s32, s32, s32);
void ScrollList_DrawInlineItems(void *, s32, s32, s32, s32);
void Ui_DrawNumberZeroPadded(s32, s32, s32, s32);
void func_8001BCB4(s32, s32, s32, s32, void *, s32, s32);
extern Gfx D_80073450[];
extern u8 D_04011AB8[];
/**
 * Draws the scrolling Pokemon list (paged when 0x200 is set) and its scroll bar.
 * Seen in play (2026-11-12): the two lists with 03/06 and 00/30.
 */
void PcSort_DrawMonList(PcSortMonList* list, s32 flags) {
    if (flags & 0x200) {
        ScrollList_DrawSmoothScroll(&list->list, list->x, list->y + 0x10, flags | 0xFFED, 0);
    } else {
        ScrollList_DrawInlineItems(&list->list, list->x, list->y + 0x10, flags | 0xFFED, 0);
    }
    Ui_DrawNumberZeroPadded(list->x + 152, list->y + 186, list->list.items->count, 2);
    Ui_DrawNumberZeroPadded(list->x + 179, list->y + 186, list->list.items->capacity, 2);
    gSPDisplayList(gDisplayListHead++, D_80073450);
    gDPSetCombineMode(gDisplayListHead++, G_CC_DECALRGBA, G_CC_DECALRGBA);
    func_8001BCB4(list->x + 170, list->y + 188, 8, 10, D_04011AB8, 8, 0);
}

s32 ScrollList_UpdateCursor(void*);
s32 ScrollList_UpdateSmoothScroll(void*);

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
        moved = ScrollList_UpdateSmoothScroll(menu);
    } else {
        moved = ScrollList_UpdateCursor(menu);
    }
    if (moved == 0) {
        action = func_8002BC14(D_800603C0);
        if (action == -1) {
            Audio_PlaySystemSound(3);
            result = -1;
        } else if (action == 1) {
            result = 1;
        }
    }
    return result;
}


/**
 * Grid menu callback that draws one of the six operation buttons of ポケモンのせいり.
 * Seen in play (2026-11-14): drew the いどうする, メニューへもどる, いれかえる, ならべかえる, みる and にがす buttons.
 */
void PcSort_DrawOperationButton(s32 x, M2C_UNK y, M2C_UNK button, M2C_UNK index, s32 flags) {
    ImageButton_Draw(button, flags);
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
void PcSort_InitOrganizeWindow(PcSortOrganizeWindow* win, s32 x, s32 y, ByteMatrix* tables, s32* dirty) {

    Window_SetRect(&win->window, x, y, 564, 370);
    win->window.animTimer = 0;
    win->window.state = 0;
    win->window.frame.style = 0x801;
    win->window.title = D_890189B8;
    Window_SetRect(&win->footerFrame, win->window.frame.x + 6, win->window.frame.y + 0x100, win->window.frame.width - 12, 108);
    win->footerFrame.style = 6;
    win->footerFrame.color = D_8900A750;
    win->footerFrame.color2 = D_8900A754;
    ImageButton_Init(&win->moveButton, x + 225, y + 72, 54, 42, 0x30, D_8900DAD0);
    win->moveButton.selectedColor = D_8900A580[2];
    win->moveButton.color = D_8900A580[3];
    win->moveButton.highlightColor = D_8900A5BC;
    ImageButton_Init(&win->backButton, x + 285, y + 72, 54, 42, 0x30, D_8900BFC0);
    win->backButton.selectedColor = D_8900A580[0];
    win->backButton.color = D_8900A580[1];
    win->backButton.highlightColor = D_8900A5BC;
    ImageButton_Init(&win->exchangeButton, x + 225, y + 120, 54, 42, 0x30, D_8900F5E0);
    win->exchangeButton.selectedColor = D_8900A580[6];
    win->exchangeButton.color = D_8900A580[7];
    win->exchangeButton.highlightColor = D_8900A5BC;
    ImageButton_Init(&win->reorderButton, x + 285, y + 120, 54, 42, 0x30, D_8900E858);
    win->reorderButton.selectedColor = D_8900A580[4];
    win->reorderButton.color = D_8900A580[5];
    win->reorderButton.highlightColor = D_8900A5BC;
    ImageButton_Init(&win->viewButton, x + 225, y + 168, 54, 42, 0x30, D_89010368);
    win->viewButton.selectedColor = D_8900A580[8];
    win->viewButton.color = D_8900A580[9];
    win->viewButton.highlightColor = D_8900A5BC;
    ImageButton_Init(&win->releaseButton, x + 285, y + 168, 54, 42, 0x30, D_89011E78);
    win->releaseButton.selectedColor = D_8900A580[12];
    win->releaseButton.color = D_8900A580[13];
    win->releaseButton.highlightColor = D_8900A5BC;
    func_80027410(&win->buttonTable, &win->moveButton, 0x2C, 6, 6);
    GridMenu_Init(&win->operationMenu, &win->buttonTable, &win->operationFlags, PcSort_DrawOperationButton, 2, 0, 0);
    win->rightBox = 1;
    win->leftBox = 0;
    PcSort_InitMonList(&win->leftList, win->window.frame.x + 14, win->window.frame.y + 44, (s32)tables);
    PcSort_InitMonList(&win->rightList, win->window.frame.x + 346, win->window.frame.y + 44, (s32)(tables + win->rightBox));
    win->boxTables = tables;
    win->dirty = dirty;
    func_80027410(&win->partyView, tables->rows, 0x50, tables->capacity, 0);
    win->state = 1;
}

M2C_UNK func_8001A384(M2C_UNK, M2C_UNK);
void Font_Printf(s32 x, s32 y, const char* fmt, ...);
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
void PcSort_DrawBoxTab(s32 win, s32 x, s32 y, s32 flags, u32 idx) {
    Color_RGBA8* col;

    if (flags & 2) {
        col = D_8900A78C;
    } else {
        col = D_8900A794;
    }
    Ui_FillRectPrimEnvColor(x, y, 204, 30, col[0], col[1]);
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
                func_8001B884(x + 0x10, y + 2, 24, 26, D_89017A80[func_8002BC44(D_89019114)], 0x18, 0x200000);
                break;
            case 9:
            case 10:
            case 11:
            case 12:
                func_8001B884(x + 2, y + 2, 40, 26, D_89017A98, 0x30, 0x200000);
                break;
        }
        gSPDisplayList(gDisplayListHead++, D_80073438);
        func_8001AB6C();
        Font_SetColorForFlags(flags);
        func_8001A384(8, 0);
        Font_Printf(x + 43, y + 5, D_8900A758[idx]);
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
    func_8001AA9C(0xFF, 0xC8, 0xC8, 0xFF); // #FFC8C8FF
    Font_SetActive(4, 0);
    Font_Printf(x + 6, y + 86, D_89018AC4);
    Font_Printf(x + 145, y + 86, D_89018AD0);
    Font_Printf(x + 284, y + 86, D_89018ADC);
    Font_Printf(x + 423, y + 86, D_89018AE8);
    func_8001AA9C(D_800734A8[0], D_800734A8[1], D_800734A8[2], D_800734A8[3]);
    Font_SetActive(8, 0);
    if ((mon[0] <= 0) || (mon[0] >= 152)) {
        name = D_89018AF4;
    } else {
        name = *(char**)D_80064C44[mon[0]];
    }
    Font_Printf(x + 8, y + 8, name);
    Font_Printf(x + 8, y + 36, D_89018B00, *(u16*)(mon + 0x26));
    Font_Printf(x + 70, y + 84, D_89018B08, *(u16*)(mon + 0x28));
    Font_Printf(x + 209, y + 84, D_89018B0C, *(u16*)(mon + 0x2A));
    Font_Printf(x + 348, y + 84, D_89018B10, *(u16*)(mon + 0x2C));
    Font_Printf(x + 487, y + 84, D_89018B14, *(u16*)(mon + 0x2E));
    for (i = 0; i < count; i++) {
        PcBox_DrawMoveName(D_8900A79C[i].x + x, D_8900A79C[i].y + y, BattleMon_GetMoveIndex((s32)mon, i), D_8900A79C[i].type);
    }
    Font_EndTexturedTextRendering();
    gSPDisplayList(gDisplayListHead++, D_80060290);
    for (i = 0; i < count; i++) {
        func_8001B884(D_8900A79C[i].iconX + x, D_8900A79C[i].y + y, 20, 20, D_8900A79C[i].tex, 0x14, 0x200000);
    }
    gSPDisplayList(gDisplayListHead++, D_80060398);
}

M2C_UNK func_8001A384(M2C_UNK, M2C_UNK);            /* extern */
void Font_Printf(s32 x, s32 y, const char* fmt, ...);
M2C_UNK func_8001AA9C(u8, u8, u8, u8);              /* extern */
void Font_SetLineHeight(s32 arg0);                     /* extern */
M2C_UNK func_8001AB6C();                            /* extern */
M2C_UNK func_8001ABBC();                            /* extern */
extern u8 D_800734A8[];

/**
 * Draws `text` in the small font.
 * Seen in play (2026-11-12): the small 03/06 and 00/30 counts.
 */
void PcSort_DrawSmallText(s32 x, s32 y, s32 text) {
    func_8001AB6C();
    func_8001A384(0x10, 0);
    func_8001AA9C(D_800734A8[0], D_800734A8[1], D_800734A8[2], D_800734A8[3]);
    Font_SetLineHeight(44);
    Font_Printf(x + 12, y + 20, text);
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
void PcSort_DrawHelpText(s32* win) {
    s32 idx = win[0x170 / 4];
    s32** list;

    switch (win[0]) {
        case 1:
            LabItem_DrawTitleText(win[48 / 4] + 88, win[52 / 4] + 26, D_8900A7EC[idx], D_8900A834[idx]);
            break;
        case 2:
            PcSort_DrawSmallText(win[48 / 4], win[52 / 4], D_8900A804[idx]);
            break;
        case 3:
            PcSort_DrawSmallText(win[48 / 4], win[52 / 4], D_8900A81C[idx]);
            break;
        case 4:
        case 6:
        case 7:
            if (win[0] == 7) {
                list = (s32**)&win[0x31C / 4];
            } else {
                list = (s32**)&win[0x294 / 4];
            }
            PcSort_DrawMonStats(win[48 / 4], win[52 / 4], ((s32*)list)[2] * 0x50 + *list[0]);
            break;
    }
}

void Window_DrawFrame(s8*);
void Ui_DrawTexturedDivider(s32, s32, s32, void*);
void Ui_DrawTexturedFrameDecal(s32, s32, s32, s32, void*);
void GridMenu_DrawInlineItems(s8*, s32, s32, s32, s32);
void TextBox_Draw(TextBox*);
extern u8 D_8007356C[];
extern u8 D_800735C4[];

/**
 * Draws the organize Pokemon window: frame, lists and help line.
 * Seen in play (2026-11-12): the ポケモンのせいり window.
 */
void PcSort_DrawOrganizeWindow(PcSortOrganizeWindow* win) {
    s32 pad[1]; // FAKE: stack padding
    s32 m1;
    s32 m2;
    s32 mode;

    if (func_8002AE6C(&win->window) == 0) {
        Window_DrawFrame(&win->footerFrame);
        gSPDisplayList(gDisplayListHead++, D_80060270);
        func_80029028(win->window.frame.x + 6, win->window.frame.y + 6, win->window.frame.width - 12, 8, D_8900A5BC);
        func_80029028(win->window.frame.x + 6, win->window.frame.y + 244, win->window.frame.width - 12, 6, D_8900A5BC);
        func_80029028(win->window.frame.x + 6, win->window.frame.y + 14, 8, 230, D_8900A5BC);
        func_80029028(win->window.frame.x + win->window.frame.width - 14, win->window.frame.y + 14, 8, 230, D_8900A5BC);
        func_80029028(win->window.frame.x + 218, win->window.frame.y + 14, 0x80, 230, D_8900A5BC);
        Ui_DrawTexturedDivider(win->window.frame.x, win->footerFrame.y - 7, win->window.frame.width, D_8007356C);
        Ui_DrawTexturedFrameDecal(win->window.frame.x + 12, win->window.frame.y + 12, 208, 234, D_800735C4);
        Ui_DrawTexturedFrameDecal(win->window.frame.x + 344, win->window.frame.y + 12, 208, 234, D_800735C4);
        GridMenu_DrawInlineItems(&win->operationMenu, 0, 0, (win->state == 1) ? 2 : 0x10, 0);
        PcSort_DrawBoxTab((s32)win, win->window.frame.x + 14, win->window.frame.y + 14, 0, win->leftBox);
        PcSort_DrawBoxTab((s32)win, win->window.frame.x + 346, win->window.frame.y + 14, 0, win->rightBox);
        m1 = 0xFDED;
        m2 = 0xFDED;
        mode = win->state;
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
        PcSort_DrawMonList(&win->leftList, m1);
        PcSort_DrawMonList(&win->rightList, m2);
        if ((win->state == 2) || (win->state == 10)) {
            PcSort_DrawMenu(&win->sourceBoxWindow);
        }
        if ((win->state == 3) || (win->state == 11)) {
            PcSort_DrawMenu(&win->targetBoxWindow);
        }
        PcSort_DrawHelpText((s32*)win);
        if ((win->state == 10) || (win->state == 11) || (win->state == 12) || (win->state == 13)) {
            TextBox_Draw(&win->textBox);
        }
    }
}

void LabList_InsertRowAtCursor(void* arg0, void* arg1);

/**
 * Moves the selected Pokemon into the destination box and marks both boxes changed.
 * Seen in play (2026-11-12) in せいとん > ポケモンをいどうする: moving ハナ (フシギダネ) from てもち into GBのボックス1
 * changed the counts from 03/06 and 00/30 to 02/06 and 01/30.
 */
void PcSort_MoveSelectedMon(PcSortOrganizeWindow* win) {
    win->dirty[win->targetBoxWindow.menu.cursor] = 1;
    win->dirty[win->sourceBoxWindow.menu.cursor] = win->dirty[win->targetBoxWindow.menu.cursor];
    LabList_InsertRowAtCursor(&win->rightList, (void*)(win->leftList.list.items->rows + win->leftList.list.items->rowSize * win->leftList.list.cursor));
    LabList_RemoveSelectedEntry(&win->leftList.list);
}

void func_80027654(ByteMatrix* matrix, u8* out, s32 row);
void func_80027700(ByteMatrix* matrix, u8* in, s32 row);

/**
 * Swaps the Pokémon picked first (swapIndex) with the selected one in the same list and
 * marks it changed. Seen in play (2026-11-14) in ポケモンをならべかえる: ハナ and カメ traded rows in てもち.
 */
void PcSort_SwapWithinList(PcSortOrganizeWindow* win) {
    u8 row[0x50];
    ByteMatrix* matrix = win->leftList.list.items;

    func_80027654(matrix, row, win->leftList.list.cursor);
    func_80027700(matrix, matrix->rows + matrix->rowSize * win->swapIndex, win->leftList.list.cursor);
    func_80027700(matrix, row, win->swapIndex);
    win->dirty[win->leftBox] = 1;
}


/**
 * Swaps the selected Pokémon of the left and right lists and marks both changed.
 * Seen in play (2026-11-14) in ポケモンをいれかえる: ハナ (てもち) and ハヒ (GBのボックス1) traded places.
 */
void PcSort_SwapBetweenLists(PcSortOrganizeWindow* win) {
    u8 row[0x50];
    ByteMatrix* matrix;

    func_80027654(win->rightList.list.items, row, win->rightList.list.cursor);
    matrix = win->leftList.list.items;
    func_80027700(win->rightList.list.items, matrix->rows + matrix->rowSize * win->leftList.list.cursor, win->rightList.list.cursor);
    func_80027700(win->leftList.list.items, row, win->leftList.list.cursor);
    win->dirty[win->rightBox] = 1;
    win->dirty[win->leftBox] = win->dirty[win->rightBox];
}


/**
 * Removes the selected Pokemon from its box and marks the box changed.
 * Seen in play (2026-11-13) released フシギダネ in せいとん > ポケモンをにがす: てもち went from 03/06 to 02/06.
 */
void PcSort_ReleaseSelectedMon(PcSortOrganizeWindow* win) {
    LabList_RemoveSelectedEntry(&win->leftList.list);
    win->dirty[win->leftBox] = 1;
    win->state = (((win->leftBox == 0) ? 1 : 0) == win->leftList.list.items->count) ? 1 : 4;
}


/**
 * Shows the selected box's Pokemon in the destination list.
 * Seen in play (2026-11-12) in せいとん: after GBのボックス2 was chosen under 「どこへいどうする？」, it ran and that
 * box appeared as the destination list (00/30).
 */
void PcSort_OpenBox(PcSortOrganizeWindow* win) {
    s32 temp_v0;
    PcSortMonList* temp_a0;

    temp_v0 = win->targetBoxWindow.menu.cursor;
    temp_a0 = &win->rightList;
    win->rightBox = temp_v0;
    PcSort_SetMonList(temp_a0, (s32)(win->boxTables + temp_v0));
    win->state = 4;
}

void TextBox_Init(TextBox*, char*, s32, s32, s32);
s32 Ui_CheckConfirmPressed(TextBox*);
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
s32 PcSort_UpdateOrganizeWindow(PcSortOrganizeWindow* win) {
    s32 ret;
    s32 res;
    s32 next;
    u16 flags;
    u8 species;
    BattleMon* mon;

    ret = 0;
    next = 0;
    switch (win->state) {
        case 1:
            if (GridMenu_UpdateCursor(&win->operationMenu) == 0) {
                res = func_8002BC14(D_800603C0);
                if (res == -1) {
                    Audio_PlaySystemSound(3);
                    ret = -1;
                } else if (res == 1) {
                    if (win->operationMenu.cursor == 1) {
                        Audio_PlaySystemSound(3);
                        ret = -1;
                    } else {
                        Audio_PlaySystemSound(2);
                        next = 2;
                        if ((win->operationMenu.cursor == 3) || (win->operationMenu.cursor == 4) || (win->operationMenu.cursor == 5)) {
                            PcSort_SetMonList(&win->rightList, (s32)(&win->partyView));
                            win->rightBox = -1;
                        }
                    }
                }
            }
            break;
        case 2:
            res = PcSort_UpdateMenuCursor(&win->sourceBoxWindow);
            if (res == -1) {
                win->state = 1;
            } else if (res > 0) {
                flags = win->sourceBoxWindow.menu.itemFlags[win->sourceBoxWindow.menu.cursor];
                if (flags & 0x100) {
                    win->state = 10;
                    TextBox_Init(&win->textBox, D_8900A84C[win->operationMenu.cursor], 0, 1, 0);
                    Audio_PlaySystemSound(8);
                } else if (flags & 0x200) {
                    Audio_PlaySystemSound(8);
                    win->state = 10;
                    TextBox_Init(&win->textBox, D_89018D8C, 0, 1, 0);
                } else {
                    Audio_PlaySystemSound(2);
                    win->leftBox = win->sourceBoxWindow.menu.cursor;
                    PcSort_SetMonList(&win->leftList, (s32)(win->boxTables + win->sourceBoxWindow.menu.cursor));
                    if ((win->operationMenu.cursor == 3) || (win->operationMenu.cursor == 4) || (win->operationMenu.cursor == 5)) {
                        win->state = 4;
                    } else {
                        next = 3;
                    }
                }
            }
            break;
        case 3:
            res = PcSort_UpdateMenuCursor(&win->targetBoxWindow);
            if (res == -1) {
                next = 2;
            } else if (res > 0) {
                flags = win->targetBoxWindow.menu.itemFlags[win->targetBoxWindow.menu.cursor];
                if (flags & 0x100) {
                    Audio_PlaySystemSound(8);
                    win->state = 11;
                    TextBox_Init(&win->textBox, D_8900A84C[win->operationMenu.cursor], 0, 1, 0);
                } else if (flags & 0x400) {
                    Audio_PlaySystemSound(8);
                    win->state = 11;
                    TextBox_Init(&win->textBox, D_89018DA4, 0, 1, 0);
                } else {
                    Audio_PlaySystemSound(2);
                    PcSort_OpenBox(win);
                }
            }
            break;
        case 4:
            res = PcSort_UpdateMonList(&win->leftList, 0);
            if (res == -1) {
                win->state = 1;
            } else if (res == 1) {
                if (win->operationMenu.cursor == 0) {
                    Audio_PlaySystemSound(2);
                    win->state = 5;
                } else if (win->operationMenu.cursor == 2) {
                    Audio_PlaySystemSound(2);
                    win->state = 7;
                } else if (win->operationMenu.cursor == 3) {
                    Audio_PlaySystemSound(2);
                    win->leftList.list.itemFlags[win->leftList.list.cursor] |= 8;
                    win->swapIndex = win->leftList.list.cursor;
                    win->state = 6;
                } else if (win->operationMenu.cursor == 4) {
                    mon = win->leftList.list.cursor + *(BattleMon**)win->leftList.list.items;
                    if ((mon->species.id <= 0) || (mon->species.id >= 152)) {
                        Audio_PlaySystemSound(8);
                    } else {
                        Audio_PlaySystemSound(2);
                        ret = 2;
                    }
                } else {
                    mon = win->leftList.list.cursor + *(BattleMon**)win->leftList.list.items;
                    species = mon->species.id;
                    if ((species <= 0) || (species >= 152)) {
                        Audio_PlaySystemSound(8);
                    } else {
                        Audio_PlaySystemSound(2);
                        ret = 3;
                    }
                }
            }
            break;
        case 5:
            res = PcSort_UpdateMonList(&win->rightList, 0x200);
            if (res == -1) {
                win->state = 4;
            } else if (res == 1) {
                Audio_PlaySystemSound(24);
                PcSort_MoveSelectedMon(win);
                if ((((win->leftBox == 0) ? 1 : 0) == win->leftList.list.items->count) ||
                    (win->rightList.list.items->count == win->rightList.list.items->capacity)) {
                    win->state = 1;
                } else {
                    win->state = 4;
                }
            }
            break;
        case 6:
            res = PcSort_UpdateMonList(&win->leftList, 0);
            if (res == -1) {
                Menu_ClearItemFlags(&win->leftList);
                win->state = 4;
            } else if (res == 1) {
                Audio_PlaySystemSound(24);
                PcSort_SwapWithinList(win);
                Menu_ClearItemFlags(&win->leftList);
                win->state = 4;
            }
            break;
        case 7:
            res = PcSort_UpdateMonList(&win->rightList, 0);
            if (res == -1) {
                win->state = 4;
            } else if (res == 1) {
                Audio_PlaySystemSound(24);
                PcSort_SwapBetweenLists(win);
                win->state = 4;
            }
            break;
        case 10:
            if (Ui_CheckConfirmPressed(&win->textBox) == 1) {
                win->state = 2;
            }
            break;
        case 11:
            if (Ui_CheckConfirmPressed(&win->textBox) == 1) {
                win->state = 3;
            }
            break;
        case 12:
            if (Ui_CheckConfirmPressed(&win->textBox) == 1) {
                win->state = 4;
            }
            break;
        case 13:
            if (Ui_CheckConfirmPressed(&win->textBox) == 1) {
                win->state = 7;
            }
            break;
    }
    if (next > 0) {
        switch (next) {
            case 2:
                PcSort_InitMenuWindow(&win->sourceBoxWindow, win->window.frame.x + 37, win->window.frame.y - 20,
                              (s32)D_8900A758, 0xD, win->leftBox);
                PcSort_DisableEmptyBoxes(&win->sourceBoxWindow, win->boxTables);
                if ((win->operationMenu.cursor == 0) || (win->operationMenu.cursor == 5)) {
                    PcSort_DisableIfSingleMon(&win->sourceBoxWindow, win->boxTables);
                }
                break;
            case 3:
                PcSort_InitMenuWindow(&win->targetBoxWindow, win->window.frame.x + 371, win->window.frame.y - 20,
                              (s32)D_8900A758, 0xD, win->rightBox);
                if (win->operationMenu.cursor == 0) {
                    PcSort_DisableFullBoxes(&win->targetBoxWindow, win->boxTables);
                } else if (win->operationMenu.cursor == 2) {
                    PcSort_DisableEmptyBoxes(&win->targetBoxWindow, win->boxTables);
                }
                PcSort_DisableRow(&win->targetBoxWindow, win->leftBox);
                win->targetBoxWindow.menu.cursor = 0;
                Menu_SkipDisabledForward(&win->targetBoxWindow.menu);
                break;
        }
        win->state = next;
    }
    return ret;
}

s8 *PokeIcon_AllocFramebuffers(s32 arg0);
void PokeIcon_OpenModelArchives(void);
s32 func_80018F2C(s8*, s32, s32, s32, s32, s32, s32, s32);
void func_80027410(s8*, s8*, s32, s32, s32);
void LabItem_ReadDeckEntries(s32, s32, s32, ByteMatrix*);
void PcSort_InitOrganizeWindow(PcSortOrganizeWindow*, s32, s32, ByteMatrix*, s32*);
extern u8 D_81000000[];
extern u8 D_0015B1A0[];
extern u8 D_0015E220[];
extern s32 D_89019108;
/**
 * Pushes the 'OTPC' pool state, opens the icon archives, and reads the boxes.
 * Seen in play (2026-11-12): ポケモンを いどうする opened the screen.
 */
void PcSort_Init(PcSortScreen* screen, s32 title) {
    s32 i;

    MainPool_PushState('OTPC');
    screen->iconFramebuffers = PokeIcon_AllocFramebuffers(1);
    screen->monRenderer = (u16*)func_80018F2C(screen->iconFramebuffers, 0x80, 0x78, 0, 0, 0x78, 0x78, 0);
    PokeIcon_OpenModelArchives();
    Fragment_Load(((((u32)D_81000000) & 0x0FF00000) >> 0x14) - 0x10, D_0015B1A0, D_0015E220);
    screen->title = title;
    func_80027410(&screen->partyTable, screen->partyMons, 0x50, 6, 0);
    for (i = 0; i < 8; i++) {
        func_80027410(&screen->gbBoxTables[i], screen->gbBoxMons[i], 0x50, 30, 0);
    }
    for (i = 0; i < 4; i++) {
        func_80027410(&screen->stadiumBoxTables[i], screen->stadiumBoxMons[i], 0x50, 30, 0);
    }
    LabItem_ReadDeckEntries(0x20, D_89019108, 0, &screen->partyTable);
    for (i = 0; i < 8; i++) {
        LabItem_ReadDeckEntries(0x21, D_89019108, i, &screen->gbBoxTables[i]);
    }
    for (i = 0; i < 4; i++) {
        LabItem_ReadDeckEntries(0x11, 0, i, &screen->stadiumBoxTables[i]);
    }
    screen->dirty[0] = 0;
    i = 1;
    do {
        screen->dirty[i] = 0;
        i++;
    } while (i != 13);
    PcSort_InitOrganizeWindow(&screen->organizeWindow, 38, 83, &screen->partyTable, screen->dirty);
    screen->state = 1;
}

M2C_UNK func_80002620(M2C_UNK);                     /* extern */

/**
 * Pops the 'OTPC' pool state.
 * Seen in play (2026-11-12): B left it for the せいとん menu.
 */
void PcSort_Free(s32 unused) {
    func_80002620(0x4F545043);
}

void Ui_DrawTintedScreenBackground(s32, s32, s32, s32, s32);
void PcSort_DrawOrganizeWindow();
void SavePrompt_Draw(SavePrompt*);
extern Color_RGB8 D_8900A5B8;

/**
 * Draws the Pokemon sorting screen for its current state, including the status window.
 * Seen in play (2026-11-12): drew ポケモンのせいり.
 */
void PcSort_DrawScreen(PcSortScreen* screen) {
    BgStage_DrawFrame();
    Ui_DrawTintedScreenBackground(56, 480, D_8900A5B8.r, D_8900A5B8.g, D_8900A5B8.b);
    switch (screen->state) {
        case 1:
            PcSort_DrawOrganizeWindow(&screen->organizeWindow);
            break;
        case 2:
            PcSort_DrawOrganizeWindow(&screen->organizeWindow);
            SavePrompt_Draw(&screen->savePrompt);
            break;
        case 3:
            PcSort_DrawOrganizeWindow(&screen->organizeWindow);
            PcBox_DrawMonStatusWindow(&screen->statusWindow);
            break;
        case 4:
            PcSort_DrawOrganizeWindow(&screen->organizeWindow);
            PcBox_DrawMonStatusWindow(&screen->statusWindow);
            break;
    }
}

extern s32 D_89019108;

/**
 * Marks every species in a GB Pokémon list as seen, owned and held in the cartridge's Pokédex
 * (GbSave_SetSeenOwnedBits with 3) after the list is written back.
 * Seen in play (2026-11-14): after moving ホ (ポッポ, #16) into てもち, its seen, owned and held bits were cleared
 * in RAM; レポートしてやめる set all three again.
 */
void PcSort_MarkListInPokedex(ByteMatrix* table) {
    s32 var_s1;
    u8 *var_s0;

    var_s0 = table->rows;
    var_s1 = 0;
    if (table->count > 0) {
        do {
            GbSave_SetSeenOwnedBits(D_89019108, *var_s0, 3);
            var_s1 += 1;
            var_s0 += 0x50;
        } while (var_s1 < table->count);
    }
}

void func_80022118(s32);
void func_800230C4(s32);
s32 func_8002207C(s32);
void func_80022188(s32);
void Save_CommitPokemonRecords(void);
void GbSave_RunReportErrorLoop(s32);
/**
 * Writes the changed boxes back to the save and flushes it.
 * Seen in play (2026-11-12) in せいとん: レポートしてやめる after the move ran this, which wrote decks 0x20
 * and 0x21, and the Game Boy .sav then had party count 2 and current-box count 1.
 */
void PcSort_SaveChanges(PcSortScreen* screen) {
    s32 dirty = 0;
    s32 i;
    s32 saved = 0;

    if (screen->dirty[0] != 0) {
        dirty = 1;
    }
    for (i = 0; i < 8; i++) {
        if (screen->dirty[1 + i] != 0) {
            dirty = 1;
            break;
        }
    }
    if (dirty != 0) {
        func_80022118(D_89019108);
    }
    if (screen->dirty[0] != 0) {
        PcSort_WriteDeck(0x20, D_89019108, 0, &screen->partyTable);
        PcSort_MarkListInPokedex(&screen->partyTable);
    }
    for (i = 0; i < 8; i++) {
        if (screen->dirty[1 + i] != 0) {
            PcSort_WriteDeck(0x21, D_89019108, i, &screen->gbBoxTables[i]);
            PcSort_MarkListInPokedex(&screen->gbBoxTables[i]);
        }
    }
    for (i = 0; i < 4; i++) {
        if (screen->dirty[9 + i] != 0) {
            PcSort_WriteDeck(0x11, D_89019108, i, &screen->stadiumBoxTables[i]);
            saved = 1;
        }
    }
    if (dirty != 0) {
        func_800230C4(D_89019108);
        if (func_8002207C(D_89019108) == 0) {
            GbSave_RunReportErrorLoop(D_89019108);
            PcSort_DrawScreen(screen);
        }
        func_80022188(D_89019108);
    }
    if (saved != 0) {
        Save_CommitPokemonRecords();
    }
}

/**
 * Returns 1 when any of the 13 boxes changed.
 * Seen in play (2026-11-12) in せいとん: returned 1 after that move, when leaving opened 「ないようが
 * へんこうされています」.
 */
s32 PcSort_HasUnsavedChanges(PcSortScreen* screen) {
    s32 i;

    for (i = 0; i < 13; i++) {
        if (screen->dirty[i] != 0) {
            return 1;
        }
    }
    return 0;
}

void SavePrompt_Init(SavePrompt*, s32, s32);
void Save_DrawReportingWindow(SavePrompt*);
s32 SavePrompt_Update(SavePrompt*);
s32 Audio_PlayCommand(u32 arg0, s32 arg1, s32 arg2);
s32 PcSort_UpdateOrganizeWindow(PcSortOrganizeWindow* arg0);
extern u8 D_89018DBC[];

/**
 * Runs the Pokemon organizer's state machine for one frame.
 * Seen in play (2026-11-12): ran ポケモンのせいり.
 */
s32 PcSort_UpdateScreen(PcSortScreen* screen) {
    s32 ret = 0;
    SavePrompt* sub;
    u8* mon;
    s32 res;

    switch (screen->state) {
        case 1:
            res = PcSort_UpdateOrganizeWindow(&screen->organizeWindow);
            if (res == -1) {
                if (PcSort_HasUnsavedChanges(screen) != 0) {
                    screen->state = 2;
                    SavePrompt_Init(&screen->savePrompt, 202, 173);
                } else {
                    ret = 1;
                }
            } else if (res == 2) {
                mon = screen->organizeWindow.leftList.list.cursor * 0x50 + *(u8**)screen->organizeWindow.leftList.list.items;
                screen->state = 3;
                PcBox_InitMonStatusWindow(&screen->statusWindow, 105, 125, (s32)mon, 0,
                              D_800603C0, screen->monRenderer);
            } else if (res == 3) {
                mon = screen->organizeWindow.leftList.list.cursor * 0x50 + *(u8**)screen->organizeWindow.leftList.list.items;
                screen->state = 4;
                PcBox_InitMonStatusWindow(&screen->statusWindow, 105, 125, (s32)mon,
                              (s32)D_89018DBC, D_800603C0, screen->monRenderer);
                screen->statusWindow.choice.cursor = 1;
            }
            break;
        case 2:
            sub = &screen->savePrompt;
            res = SavePrompt_Update(sub);
            if (res == -1) {
                screen->state = 1;
            } else if (res > 0) {
                ret = 1;
                screen->organizeWindow.window.animTimer = 7;
                switch (res) {
                    case 2:
                        break;
                    case 1:
                        Save_DrawReportingWindow(sub);
                        PcSort_SaveChanges(screen);
                        break;
                }
            }
            break;
        case 3:
            res = func_8002BC14(D_800603C0);
            if ((res == -1) || (res == 1)) {
                Audio_PlaySystemSound(3);
                screen->state = 1;
            }
            break;
        case 4:
            res = PcBox_UpdateConfirmCursor(&screen->statusWindow);
            if (res == -1) {
                Audio_PlaySystemSound(3);
                screen->state = 1;
            } else if (res == 1) {
                Audio_PlayCommand(0x57, 0, 0);
                PcSort_ReleaseSelectedMon(&screen->organizeWindow);
                screen->state = 1;
            }
            break;
    }
    return ret;
}
