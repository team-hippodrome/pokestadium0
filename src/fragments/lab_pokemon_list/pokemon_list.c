/* Stadium Zero fragment016_252E10. */

#include "global.h"
#include "lab_pokemon_list.h"
#include "m2c_macros.h"

extern u8 D_80073520[];
M2C_UNK Ui_DrawRoundedFrame(s32, s32, s32, s32, Color_RGBA8);

M2C_UNK LabPCList_InitDeckCategories(s32, s32, s32, s32);          /* extern */
/**
 * Sets up the three item decks (Game Boy bag, Game Boy PC, 64 cartridge) and reads each one that exists.
 * Seen in play (2026-11-14) in いちらん: ran on entry; the どうぐをつかう window later listed the bag's items (マックスアップ ×5 ...).
 */
void LabPCList_LoadItemDecks(s8* screen) {
    s32 i;

    LabPCList_InitDeckCategories(screen + 0x9E64, screen + 0x9EB8, screen + 0x9EE0, screen + 0x9F44);
    for (i = 0; i < 3; i++) {
        if (M2C_FIELD(screen + i * 0x1C, s32*, 0x9E68) != 0) {
            LabPCList_ReadDeckCategory((unk_func_8830867C_02C_154*)(screen + i * 0x1C + 0x9E64));
        }
    }
}


/**
 * Writes back every item deck that exists and was changed.
 * Seen in play (2026-11-14) in いちらん: ran from LabPCList_SaveChanges on レポートしてやめる after a TM was used.
 */
void LabPCList_SaveDirtyItemDecks(s32 screen) {
    s32 var_s1;
    s32 var_s2;
    s8 *var_s0;

    var_s0 = screen + 0x8000;
    var_s1 = screen;
    var_s2 = 0;
    do {
        if ((M2C_FIELD(var_s0, s32 *, 0x1E68) != 0) && (M2C_FIELD(var_s0, s32 *, 0x1E6C) != 0)) {
            LabPCList_WriteDeckCategory((unk_func_8830867C_02C_154*)(var_s1 + 0x9E64));
        }
        var_s2 += 0x1C;
        var_s1 += 0x1C;
        var_s0 += 0x1C;
    } while (var_s2 != 0x54);
}

extern s32 D_8910A7F8[3];
void func_80027410(void*, void*, s32, s32, s32);
void LabPCList_InitSourceBoxes(void*, void*, void*, s32);

/**
 * Sets up the three sources of the list: てもち (6 slots), the 8 Game Boy boxes and the 4 64 cartridge boxes (30 slots each).
 * Seen in play (2026-11-14) in いちらん: ran on entry; 「どこのポケモンを いちらん するか」 then offered てもち, ゲームボーイのボックス (ボックス1-8) and 64カセットのボックス (ボックス1-4).
 */
void LabPCList_InitSources(LabPCListScreen* screen) {
    s32 i;

    screen->sources[0].unk_04 = 0x20;
    screen->sources[0].unk_08 = func_80025BD8();
    screen->sources[0].unk_0C = 0;
    screen->sources[0].unk_20 = 6;
    func_80027410(&screen->sources[0].boxes, (s8*)screen + 0x90, 0x20, 1, 0);
    LabPCList_InitSourceBoxes(&screen->sources[0], (s8*)screen + 0x8200, (s8*)screen + 0x430, 6);
    screen->sources[1].unk_04 = 0x21;
    screen->sources[1].unk_08 = screen->sources[0].unk_08;
    screen->sources[1].unk_0C = 1;
    screen->sources[1].unk_20 = 0x1E;
    func_80027410(&screen->sources[1].boxes, (s8*)screen + 0xB0, 0x20, 8, 0);
    LabPCList_InitSourceBoxes(&screen->sources[1], (s8*)screen + 0x8218, (s8*)screen + 0x640, 0x1E);
    screen->sources[2].unk_04 = 0x11;
    screen->sources[2].unk_08 = 0;
    screen->sources[2].unk_0C = 2;
    screen->sources[2].unk_20 = 0x1E;
    func_80027410(&screen->sources[2].boxes, (s8*)screen + 0x1B0, 0x20, 4, 0);
    LabPCList_InitSourceBoxes(&screen->sources[2], (s8*)screen + 0x85D8, (s8*)screen + 0x58C0, 0x1E);
    for (i = 0; i < 3; i++) {
        screen->sources[i].unk_00 = D_8910A7F8[i];
    }
    func_80027410((s8*)screen + 0x420, screen->sources, 0x24, 3, 3);
}

extern s32 D_800603C0;
void func_8000B2F4(s32);
/**
 * Sets the header cursor's range for the current detail page (1/3: six columns, 2/3: the move block, 3/3: six stat columns).
 * Seen in play (2026-11-14) in いちらん: ran on entry and on every C-Left/C-Right page turn (ページおくり1/3 -> 2/3 -> 3/3).
 */
void LabPCList_ResetHeaderCursor(LabPCListScreen* screen) {
    s32 count;

    switch (screen->page) {
        case 0:
            count = screen->pageColumnStart[screen->page + 1] - screen->pageColumnStart[screen->page] - 1;
            break;
        case 1:
            count = 1;
            break;
        case 2:
            count = screen->pageColumnStart[screen->page + 1] - screen->pageColumnStart[screen->page];
            break;
    }
    if (screen->focus == 2) {
        screen->headerCursor.cursor = screen->headerCursor.cursor; // FAKE: self-assignment is required to match (retail reloads and stores the field)
    } else {
        screen->headerCursor.cursor = 2;
    }
    screen->headerCursor.count = count + 2;
    screen->headerCursor.controller = D_800603C0;
    func_8000B2F4(D_800603C0);
}

/**
 * Resets the list filters: level range 1..100, and no type or move filter.
 * Seen in play (2026-11-12) in いちらん: すべてのせんたくをやめる ran this, then LabPCList_ClearFilterFlags, and
 * the full party list came back.
 */
void LabPCList_ResetFilterState(LabPCListScreen* state) {
    /* IDO schedules these byte stores together when they share a source line. */
    state->levelFilterMin = 1; state->levelFilterMax = 100;
    state->unk_982C = 0;
    state->typeFilterCount = 0;
    state->moveFilterCount = 0;
}

void Window_SetRect(s8 *, s32, s32, s32, s32);
void func_80027804(s8*, s8*, s32, s32);
void LabPCList_LoadAllBoxes(s8*);
void func_80027D68(s32, s32);
void ScrollList_Init(s8*, s8*, s8*, s32, void*, s32, s32);
void LabPCList_DrawMonRow();
extern s32 D_8910D990[];
extern Color_RGBA8 D_8910A7F4;
extern u8 D_8910A844[];
extern u8 D_8910A848[];
extern u8 D_8910A804[];
extern u8 D_8910A84C[];

/**
 * Sets up the Pokemon list window (564x382) and its widgets.
 * Seen in play (2026-11-12) in いちらん (party list: フシギダネ, ヒトカゲ, ゼニガメ): ran on entry as the list
 * window appeared.
 */
void LabPCList_InitListWindow(LabPCListScreen* screen, s32 x, s32 y, s32 msg_box) {
    UNUSED s32 pad[1]; // FAKE: stack padding

    LabPCList_InitSources(screen);
    Window_SetRect(screen, x, y, 564, 382);
    screen->window.animTimer = 0;
    M2C_FIELD(screen, s32*, 0x20) = 0;
    screen->window.state = 0;
    screen->window.frame.style = 1;
    Window_SetRect((s8*)&screen->headerFrame, x + 6, y + 6, 552, 30);
    screen->headerFrame.style = 6;
    screen->headerFrame.color = *(Color_RGBA8*)D_8910A844;
    screen->headerFrame.color2 = *(Color_RGBA8*)D_8910A848;
    Window_SetRect((s8*)&screen->listFrame, x + 6, y + 58, 552, 302);
    screen->listFrame.style = 1;
    func_80027804((s8*)&screen->rows, (s8*)screen->rowBuffer, 0x1D2, 0);
    func_80027804((s8*)&screen->filteredRows, (s8*)screen->filteredRowBuffer, 0x1D2, 0);
    LabPCList_LoadAllBoxes((s8*)&screen->sourceMatrix);
    screen->activeFilters = 0;
    screen->columnWidths = D_8910A804;
    LabPCList_FlattenEntries(&screen->rows, (unk_func_8830867C_02C_144*)&screen->sourceMatrix);
    screen->sortKey = 0;
    func_80027D68((s32)((s8*)&screen->rows), D_8910D990[0]);
    screen->focus = 0;
    LabPCList_LoadItemDecks(screen);
    screen->unk_0080 = 0;
    screen->page = 0;
    ScrollList_Init((s8*)&screen->list, (s8*)&screen->rows, (s8*)screen->rowFlags, 14, LabPCList_DrawMonRow, 552, 20);
    screen->list.options &= ~0x100000;
    screen->pageColumnStart = D_8910A84C;
    LabPCList_ResetHeaderCursor(screen);
    screen->hasChanges = 0;
    screen->msg = msg_box;
    LabPCList_ResetFilterState(screen);
    screen->state = 1;
    LabSourceSelect_Init(&screen->sourceSelectWindow, 120, 103, (s8*)&screen->sourceMatrix, D_8910A7F4);
}

/**
 * Returns the x position of the header cursor for the current detail page.
 * Seen in play (2026-11-14) in いちらん: placed the header frame and the column popups under ニックネーム, ID, おや, ばしょ and the stat columns.
 */
s32 LabPCList_GetColumnCursorX(LabPCListScreen* screen) {
    s32 i;
    s32 x = 0;
    s32 end;

    for (i = screen->pageColumnStart[screen->page], end = screen->pageColumnStart[screen->page] + screen->headerCursor.cursor - 2; i < end; i++) {
        x += screen->columnWidths[i];
    }
    return screen->listFrame.x + x + 0x78;
}

/**
 * Draws the yellow frame around the selected column header; on page 1 the two type columns share one frame.
 * Seen in play (2026-11-14) in いちらん: framed ニックネーム, ID, おや, ばしょ and タイプ1/タイプ2 while R and D-Right moved the header cursor.
 */
void LabPCList_DrawColumnCursor(LabPCListScreen* screen) {
    s32 end;
    s32* r;
    s32 i;
    s32 w;

    switch (screen->page) {
        case 0:
            end = screen->pageColumnStart[screen->page] + screen->headerCursor.cursor - 2;
            i = end;
            if (i == 4) {
                w = screen->columnWidths[i] + screen->columnWidths[i + 1];
            } else {
                w = screen->columnWidths[i];
            }
            Ui_DrawRoundedFrame(LabPCList_GetColumnCursorX(screen), screen->listFrame.y, w, 20, *(Color_RGBA8*)D_80073520);
            break;
        case 1:
            w = 0;
            r = &screen->pageColumnStart[screen->page];
            i = r[0] + screen->headerCursor.cursor - 2;
            end = r[1] - r[0] + i;
            for (; i < end; i++) {
                w += screen->columnWidths[i];
            }
            Ui_DrawRoundedFrame(LabPCList_GetColumnCursorX(screen), screen->listFrame.y, w, 20, *(Color_RGBA8*)D_80073520);
            break;
        case 2:
            Ui_DrawRoundedFrame(LabPCList_GetColumnCursorX(screen), screen->listFrame.y, screen->columnWidths[screen->pageColumnStart[screen->page] + screen->headerCursor.cursor - 2], 20, *(Color_RGBA8*)D_80073520);
            break;
    }
}

/**
 * Draws the frame of header cursor positions 0 (the 0x26-wide icon that leaves the list) and 1 (the
 * 0x50-wide ポケモン header that opens the sort menu); the column headers use LabPCList_DrawColumnCursor.
 * Seen in play (2026-11-14) in いちらん: D-Up from the first row framed the ポケモン header (cursor 1), whose A opens the sort menu.
 */
void LabPCList_DrawHeaderCursor(LabPCListScreen* screen) {
    switch (screen->headerCursor.cursor) {
        case 0:
            Ui_DrawRoundedFrame(screen->listFrame.x, screen->listFrame.y, 38, 20, *(Color_RGBA8*)D_80073520);
            return;
        case 1:
            Ui_DrawRoundedFrame(screen->listFrame.x + 38, screen->listFrame.y, 80, 20, *(Color_RGBA8*)D_80073520);
            return;
    }
}
