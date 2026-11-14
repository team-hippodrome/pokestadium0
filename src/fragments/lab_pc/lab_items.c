/* Stadium Zero fragment015_238BD0. */
/* C ported from the Stadium 1 decomp: src/fragments/lab_pc/lab_pc_1B4EA0.c, src/fragments/lab_pc_list/lab_pc_list_1CEA00.c. */

#include "lab_pc.h"
#include "font.h"
#include "graphics_textures.h"
#include "hal_libc.h"
#include "input.h"
#include "lab_item.h"
#include "pokemon_stats.h"
#include "save_data.h"

// Declared here instead of in a header: the callers of these disagree on their types.
s32 Ui_GetSelectionDirection(Controller* arg0);
extern s32 pad_D_8831A4DC[8];
typedef struct unk_D_88317298 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
} unk_D_88317298;
typedef struct unk_D_883172F4 {
    /* 0x00 */ u16* unk_00;
    /* 0x04 */ s32 unk_04;
} unk_D_883172F4;

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
void ScrollList_SetItems(s8*, s32, s8*);

void LabItem_Unused(void);
s32 LabItem_ComputeRemainingCapacity(s32 arg0, ByteMatrix* arg1);
s32 LabItem_ComputeMaxTransferQuantity(s32 arg0, ByteMatrix* arg1);
s32 LabItem_FindOrAllocateGamePakBoxSlot(LabItemSaveSlot* arg0, s32 arg1, char* arg2);
void LabItem_LoadGamePakBoxSlots(LabItemSaveSlot* arg0);
void LabItem_ReadDeckEntries(s32 arg0, s32 arg1, s32 arg2, ByteMatrix* arg3);

/**
 * Inserts `row` into the list's table at the list's cursor (the third word of the
 * ScrollList, typed here as LabMonEntryList.count), shifting later rows down.
 * Seen in play (2026-11-14) in せいとん: moving a Pokémon or a quantityless item put it at the row the
 * cursor picked in the destination list (ホ went to the top of てもち).
 */
void LabList_InsertRowAtCursor(LabMonEntryList* list, s32 (*row)(s32, s32)) {
    func_800274E0(list->items, row, list->count);
}

void func_800275E4(s32, s32);
void ScrollList_SetCursorKeepOffset(s32*, s32);

/**
 * LabList_RemoveSelectedEntry
 *
 * Removes one row from the grid referenced by the cursor arg0 and fixes up
 * the cursor.  arg0->items is the table and arg0->cursor the current index.
 *
 *   1. func_800275E4(grid, index) is called.  This is ByteMatrix_RemoveRow
 *      (name from symbol_addrs.txt; its code was read and agrees): it
 *      removes row `index` from a byte matrix whose row count is the word at
 *      offset 8 and whose row size is the word at offset 0xC, decrements
 *      the count, and returns 1 if the index was out of range.  The return
 *      value is not used here.
 *   2. If the index is now at or past the (already decremented) count, i.e.
 *      the removed row was the last one, it is decremented.
 *   3. ScrollList_SetCursorKeepOffset(arg0, index) is called
 *      (WidgetTree_SetScrollableGridIndexPreserveScroll in symbol_addrs.txt).
 *
 * symbol_addrs.txt names this function LabList_RemoveSelectedEntry,
 * a Stadium 1 name.  The Stadium 1 function of that name is NOT the same
 * code: it removes from a pointer list and, when the index is past the end
 * and positive, sets the index to count - 1.  Zero's version operates on a
 * byte matrix and the retail code simply subtracts 1 from the index, so the
 * name is a rough match at best.
 * Seen in play (2026-11-13) removed the list row when フシギダネ was released (せいとん > ポケモンをにがす) and when
 * a Pokémon moved out of てもち into GBのボックス1, so it serves the Pokémon lists as well as the item
 * list.
 */
void LabList_RemoveSelectedEntry(ScrollList* list) {
    func_800275E4((s32)list->items, list->cursor);
    if (list->cursor >= list->items->count) {
        list->cursor -= 1;
    }
    ScrollList_SetCursorKeepOffset((s32*)list, list->cursor);
}

void func_800275E4(s32, s32);
int func_800274E0();
void ScrollList_SetCursorKeepOffset(s32*, s32);

/**
 * Adds `quantity` of `itemId` to the item list at its cursor. Rows that already hold
 * the item are removed first (their counts are added in, and the cursor moves up past
 * each one removed), then the total is inserted as stacks of at most 99.
 * Seen in play (2026-11-14) in どうぐをいどうする: moving 2 of キズぐすり ×03 into サトシのパソコン put a
 * キズぐすり ×02 row at the picked position.
 */
void LabItem_InsertItemStacks(s32* list, s32 itemId, s32 quantity) {
    s32 i;
    s32 var_s3;
    s32 var_v0;
    s32* temp_s4;
    u8 sp3C[2];
    u8* var_s2;
    u8* temp_v1;

    temp_s4 = (s32*)list[0];
    temp_v1 = (u8*)temp_s4[0];
    i = 0;

    if (temp_s4[2] > 0) {
        var_s2 = temp_v1;
        do {
            if (itemId == var_s2[0]) {
                quantity += var_s2[1];
                func_800275E4(list[0], i);
                if (i < list[2]) {
                    list[2]--;
                }
            } else {
                i++;
                var_s2 += 2;
            }
        } while (i < temp_s4[2]);
    }

    sp3C[0] = itemId;
    var_s3 = list[2];

    while (quantity > 0) {
        if (quantity < 0x63) {
            var_v0 = quantity;
        } else {
            var_v0 = 0x63;
        }
        quantity -= var_v0;
        sp3C[1] = var_v0;
        func_800274E0(temp_s4, sp3C, var_s3++);
    }

    ScrollList_SetCursorKeepOffset(list, list[2]);
}

/**
 * Takes `arg1` from the selected item's count, removing the entry when nothing is left.
 * Seen in play (2026-11-13) in せいとん > どうぐをいどうする, moving all five ほのおのいし to サトシのパソコン removed the bag
 * row (006/020 to 005/020, PC 000/050 to 001/050).
 */
void LabItem_DecreaseSelectedCount(ScrollList* list, s32 count) {
    u8* temp_v1 = &list->items->rows[list->items->rowSize * list->cursor];

    if (count >= temp_v1[1]) {
        LabList_RemoveSelectedEntry(list);
        return;
    }
    temp_v1[1] -= count;
}

/**
 * Empty and never called: no jal, j or address word for it in any built fragment or the
 * resident code (scanned 2026-11-14).
 */
void LabItem_Unused(void) {
}

/**
 * Returns how many more of `itemId` a full table can take: 99 minus the count of
 * every row that already holds it, summed.
 * Seen in play (2026-11-14): with the bag poked to 20/20 rows and ふしぎなアメ ×95 in row 0, picking
 * ふしぎなアメ ×05 in サトシのパソコン to move into the bag returned 4, and the count
 * selector's limit was 4.
 */
s32 LabItem_ComputeRemainingCapacity(s32 itemId, ByteMatrix* table) {
    s32 i;
    s32 var_v1 = 0;
    u8* var_v0 = table->rows;

    for (i = 0; i < table->count; i++, var_v0 += 2) {
        if (itemId == var_v0[0]) {
            var_v1 = (var_v1 - var_v0[1]) + 0x63;
        }
    }

    return var_v1;
}

/** Returns the largest quantity of an item that can be transferred. */
s32 LabItem_ComputeMaxTransferQuantity(s32 itemId, ByteMatrix* table) {
    s32 var_v1;

    if (LabItem_IsQuantitylessItemForOperation(itemId) != 0) {
        if (table->count < table->capacity) {
            var_v1 = 1;
        } else {
            var_v1 = 0;
        }
    } else if (table->count < table->capacity) {
        var_v1 = 0x63;
    } else {
        var_v1 = LabItem_ComputeRemainingCapacity(itemId, table);
    }
    return var_v1;
}

/** Finds the item box slot for a Game Pak box, allocating one if needed. */
s32 LabItem_FindOrAllocateGamePakBoxSlot(LabItemSaveSlot* slots, s32 trainerId, char* trainerName) {
    s32 i;

    for (i = 0; i < 4; i++) {
        if ((slots[i].present != 0) && (trainerId == slots[i].trainerId) && (HAL_Strcmp(slots[i].trainerName, trainerName) == 0)) {
            return i;
        }
    }

    for (i = 0; i < 4; i++) {
        if (slots[i].present == 0) {
            return i;
        }
    }

    return -1;
}

/** Loads the item box slots for the Game Pak boxes. */
void LabItem_LoadGamePakBoxSlots(LabItemSaveSlot* slots) {
    s32 i;

    for (i = 0; i < 4; i++) {
        slots[i].present = Deck_IsSaveEntryPresent(0x12, i);
        if (slots[i].present != 0) {
            slots[i].trainerId = Deck_GetSaveEntryTrainerId(0x12, i) & 0xFFFF;
            Deck_GetSaveEntryName(0x12, i, slots[i].trainerName);
        }
    }
}

/** Reads item entries from a deck. */
void LabItem_ReadDeckEntries(s32 deckType, s32 port, s32 index, ByteMatrix* table) {
    DeckHandle* sp1C = Deck_Open(deckType, port, index, 0);

    table->count = Deck_ReadEntries(table->rows, table->capacity, sp1C);
    Deck_CloseAndFlush(sp1C);
}

/** Writes item entries back to a deck. */
void LabItem_WriteDeckBack(s32 deckType, s32 port, s32 index, ByteMatrix* table, s32 unused, char* trainerName, s32 trainerId) {
    DeckHandle* sp2C;

    if (trainerId != -1) {
        if (1) {}  // karodo
        sp2C = Deck_OpenAndSetName(deckType, port, index, unused, trainerName, trainerId);
    } else {
        sp2C = Deck_Open(deckType, port, index, 1);
    }

    Deck_WriteEntries(table->rows, table->count, sp2C);

    if ((deckType == 0x10) || (deckType == 0x11) || (deckType == 0x12) || (deckType == 0x13)) {
        Deck_CloseAndFlushBox(sp2C);
    } else {
        Deck_CloseAndFlush(sp2C);
    }
}

M2C_UNK Ui_DrawTintedScreenBackground(M2C_UNK, M2C_UNK, u8, u8, s32); /* extern */
extern Color_RGBA8 D_8900A5B8;

/**
 * Draws the tinted terminal screen background.
 * Seen in play (2026-11-12): the せいとん background.
 */
void LabItem_DrawBackground(void) {
    Ui_DrawTintedScreenBackground(0x38, 0x1E0, D_8900A5B8.r, D_8900A5B8.g, (s32)D_8900A5B8.b);
}

void Window_SetRect(s8*, s32, s32, s32, s32);
void Window_InitLabeled(s8*, s32, s32, s32, Color_RGBA8, char*);
void func_8000B2F4(s32);
extern Color_RGBA8 D_8900A5C0;
extern char D_89018460[];
extern char D_89018468[];
extern s32 D_800603C0;
/**
 * Sets up a はい/いいえ question window with a title and text; the caller sets the cursor.
 * Seen in play (2026-11-14): 「ちゅうい！ ６４カセットに あきが ありません どれかけしますか？」 when the
 * 64 cassette had no free save, and 「このデータをすてますか？」.
 */
void LabItem_InitConfirmWindow(LabItemConfirmWindow* win, s32 x, s32 y, char *title, s32 text) {
    Window_SetRect(win, x, y, 0x10C, 0x92);
    win->window.animTimer = 0;
    win->window.state = 0;
    win->window.frame.style = 0x2801;
    win->window.title = title;
    Window_InitLabeled(&win->yesButton, win->window.frame.x + 0x2E, win->window.frame.y + 0x6E, 0x48, D_8900A5C0, D_89018460);
    win->yesButton.labelX = 0xA;
    win->yesButton.unk_34 = 0xC;
    Window_InitLabeled(&win->noButton, win->window.frame.x + 0x96, win->window.frame.y + 0x6E, 0x48, D_8900A5C0, D_89018468);
    win->choice.count = 2;
    win->choice.cursor = 0;
    win->choice.controller = (Controller*)D_800603C0;
    func_8000B2F4(D_800603C0);
    win->text = text;
}

s32 func_8002AE6C();                                /* extern */
M2C_UNK func_8001A384(M2C_UNK, M2C_UNK);            /* extern */
M2C_UNK func_8001A944(s32, s32, ...);
M2C_UNK func_8001AA9C(u8, u8, u8, u8);              /* extern */
void Font_SetLineHeight(s32 arg0);                     /* extern */
M2C_UNK func_8001AB6C();                            /* extern */
M2C_UNK func_8001ABBC();                            /* extern */
void Ui_DrawTexturedDivider(s32, s32, s32, void*);
void Ui_FillRectPrimEnvColor(s32, s32, s32, s32, Color_RGBA8, Color_RGBA8);
void func_80029028(s32, s32, s32, s32, Color_RGBA8);
void Window_DrawLabeled(s8*, s32);
extern u8 D_8007356C[];
extern u8 D_800734A8[];
extern Gfx D_80060270[];
extern Color_RGBA8 D_8900A5C4;
extern Color_RGBA8 D_8900A5C8;
extern Color_RGBA8 D_8900A5CC;

/**
 * Draws a はい/いいえ question window.
 * Seen in play (2026-11-14): drew both ちゅうい！ questions above.
 */
void LabItem_DrawConfirmWindow(LabItemConfirmWindow* win) {
    if (func_8002AE6C() == 0) {
        Ui_DrawTexturedDivider(win->window.frame.x, win->window.frame.y + 0x61, win->window.frame.width, D_8007356C);
        Ui_FillRectPrimEnvColor(win->window.frame.x + 6, win->window.frame.y + 6, win->window.frame.width - 0xC, 0x5C, D_8900A5C4, D_8900A5C8);
        gSPDisplayList(gDisplayListHead++, D_80060270);
        func_80029028(win->window.frame.x + 6, win->window.frame.y + 0x68, win->window.frame.width - 0xC, 0x24, D_8900A5CC);
        func_8001AB6C();
        if (!win) { // FAKE: empty test only changes register allocation; needed to match
        }
        func_8001AA9C(D_800734A8[0], D_800734A8[1], D_800734A8[2], D_800734A8[3]);
        func_8001A384(8, 0);
        Font_SetLineHeight(0x1C);
        func_8001A944(win->window.frame.x + 0xE, win->window.frame.y + 0xA, win->text);
        func_8001ABBC();
        Window_DrawLabeled(&win->yesButton, (win->choice.cursor == 0) ? 2 : 0);
        Window_DrawLabeled(&win->noButton, (win->choice.cursor == 1) ? 2 : 0);
    }
}

s32 func_8002B390(s8*);
s32 func_8002BC14(s32);
extern s32 D_800603C0;

/**
 * Moves the はい/いいえ cursor. Returns 1 on はい, -1 on いいえ or B, otherwise 0.
 * Seen in play (2026-11-14): D-Left and A on はい went on to データをけす; いいえ is the default.
 */
s32 LabItem_UpdateConfirmWindow(LabItemConfirmWindow* win) {
    s32 ret = 0;

    switch (win->window.state) {
        case 1:
        case 2:
            break;
        default:
            return 0;
    }
    if (func_8002B390(&win->choice) == 0) {
        ret = func_8002BC14(D_800603C0);
        if (ret == 1) {
            switch (win->choice.cursor) {
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

extern Color_RGBA8 D_8900A5BC;

/**
 * Sets up the item count selector (84x52).
 * Seen in play (2026-11-13) in せいとん > どうぐをいどうする, the ×count selector opened when ほのおのいし ×05 was
 * picked to move from てもちのどうぐ to サトシのパソコン.
 */
void LabItem_InitCountSelector(LabItemCountSelector* sel, s32 x, s32 y, s32 max, s32 limit) {
    Window_SetRect(&sel->window, x, y, 0x54, 0x34);
    sel->window.animTimer = 0;
    sel->window.title = 0;
    sel->window.state = 0;
    sel->window.frame.style = 0;
    *(Color_RGBA8*)&sel->window.frame.color = D_8900A5BC; // copied as an aligned word
    sel->count.digitCount = 2;
    sel->count.value = 1;
    sel->count.min = 1;
    sel->count.max = max;
    sel->count.digit = 0;
    func_8000B2F4(D_800603C0);
    sel->limit = limit;
    sel->state = 0;
}

void func_8001B884(s32, s32, s32, s32, u8*, s32, s32);
void func_8001AA60(s32, s32, s32);
void Font_SetColorForFlags(s32);
void Ui_DrawRoundedFrame(s32, s32, s32, s32, Color_RGBA8);
void TextBox_Draw(TextBox*);
extern Gfx D_80073408[];
extern Gfx D_80073438[];
extern Color_RGBA8 D_80073520;
extern u8 D_04002130[];
extern u8 D_04002238[];
extern u8 D_04002340[];
extern u8 D_04002448[];
extern char D_89018470[];

/**
 * Draws the count selector with its ×count and the up/down arrows.
 * Seen in play (2026-11-13) in せいとん > どうぐをいどうする, drew the ×count selector (×01, ×02 ... ×05) for
 * ほのおのいし.
 */
void LabItem_DrawCountSelector(LabItemCountSelector* sel) {
    UNUSED s32 pad[1]; // FAKE: stack padding
    s32 x;
    s32 v;

    if (func_8002AE6C(&sel->window) == 0) {
        x = sel->window.frame.x - sel->count.digit * 0x16 + 0x36;
        gSPDisplayList(gDisplayListHead++, D_80073408);
        if (((u16*)D_800603C0)[3] & 0x800) {
            v = (s32)D_04002340;
        } else {
            v = (s32)D_04002130;
        }
        func_8001B884(x + 3, sel->window.frame.y + 6, 0xE, 8, (u8*)v, 0x10, 0x200000);
        if (((u16*)D_800603C0)[3] & 0x400) {
            v = (s32)D_04002448;
        } else {
            v = (s32)D_04002238;
        }
        func_8001B884(x + 3, sel->window.frame.y + 0x26, 0xE, 8, (u8*)v, 0x10, 0x200000);
        gSPDisplayList(gDisplayListHead++, D_80073438);
        Ui_DrawRoundedFrame(x - 3, sel->window.frame.y + 0xD, 0x1A, 0x1A, D_80073520);
        Font_BeginTranslucentTextRendering();
        Font_SetActive(8, 0);
        Gfx_SetEnvColor(D_800734A8[0], D_800734A8[1], D_800734A8[2],
                      D_800734A8[3]);
        func_8001A944(sel->window.frame.x + 0xA, sel->window.frame.y + 0x10, D_89018470);
        if (sel->count.digit == 1) {
            v = 2;
        } else {
            v = 0;
        }
        Font_SetColorForFlags(v);
        func_8001AA60(sel->window.frame.x + 0x20, sel->window.frame.y + 0x10, sel->count.value / 10 + '0');
        if (sel->count.digit == 0) {
            v = 2;
        } else {
            v = 0;
        }
        Font_SetColorForFlags(v);
        func_8001AA60(sel->window.frame.x + 0x36, sel->window.frame.y + 0x10, sel->count.value % 10 + '0');
        Font_EndTexturedTextRendering();
        if (sel->state == 1) {
            TextBox_Draw(&sel->textBox);
        }
    }
}

s32 func_8002B638(s8 *);                          /* extern */
s32 func_8002BC14(s32);                             /* extern */
void TextBox_Init(TextBox*, char*, s32, s32, s32);
s32 Ui_CheckConfirmPressed(TextBox*);
M2C_UNK func_8003F6AC(M2C_UNK);                     /* extern */
extern s32 D_800603C0;
extern M2C_UNK D_89018474;

/**
 * Handles the count selector input; shows どうぐがいっぱいです (the items are full) when needed.
 * Seen in play (2026-11-13) in せいとん > どうぐをいどうする, the D-pad changed the ほのおのいし count and A moved
 * that many to サトシのパソコン.
 */
s32 LabItem_UpdateCountSelector(LabItemCountSelector* sel) {
    s32 sp2C;
    s32 temp_v0;
    s32 temp_v0_2;

    sp2C = 0;
    temp_v0 = sel->state;
    switch (temp_v0) {                              /* irregular */
    case 0:
        if (func_8002B638(&sel->count) == 0) {
            temp_v0_2 = func_8002BC14(D_800603C0);
            if (temp_v0_2 == -1) {
                func_8003F6AC(3);
                sp2C = -1;
            } else if (temp_v0_2 == 1) {
                if (sel->limit < sel->count.value) {
                    func_8003F6AC(8);
                    TextBox_Init(&sel->textBox, &D_89018474, 0, 1, 0);
                    sel->state = 1;
                } else {
                    func_8003F6AC(2);
                    sp2C = 1;
                }
            }
        }
        break;
    case 1:
        if (Ui_CheckConfirmPressed(&sel->textBox) == 1) {
            sel->state = 0;
            sel->count.value = (s32) sel->limit;
        }
        break;
    }
    return sp2C;
}

/**
 * Sets flag 0x100 on each of the three list rows (てもちの どうぐ, %sのパソコン,
 * 64の カセット) whose item table is empty; picking such a row shows a warning text box.
 * Seen in play (2026-11-14): ran as the source window of どうぐをいどうする opened.
 */
void LabItem_DisableEmptyLists(LabItemMenuWindow* win, ByteMatrix* tables) {
    s32 var_v0;
    u16* temp_a1;
    ByteMatrix* var_v1;
    u16** new_var; // FAKE: permuter temp

    var_v0 = 0;
    new_var = &win->menu.itemFlags;
    var_v1 = tables;
    do {
        if (var_v1->count == 0) {
            temp_a1 = *new_var + var_v0;
            *temp_a1 |= 0x100;
        }
        var_v0 += 1;
        var_v1 += 1;
    } while (var_v0 != 3);
}

/**
 * Sets the disabled flag (1) on menu row `arg1`.
 * Seen in play (2026-11-13) ran when the てもちのどうぐ / サトシのパソコン / 64のカセット list menu opened in せいとん >
 * どうぐをいどうする; the list already chosen as the source was greyed out as a destination.
 */
void LabItem_DisableRow(LabItemMenuWindow* win, s32 row) {
    u16 *temp_v0;

    temp_v0 = &win->menu.itemFlags[row];
    *temp_v0 |= 1;
}

/*
 * LabItem_DrawMenuRow: draws one line of text `str` at (x, y) in the Lab PC list style.
 *
 * `flags` bit 0x10 first draws a 0xD2 x 0x16 highlight (Ui_FillRectHighlighted, color
 * D_8900A5BC) at (x + 3, y + 3).  The text color is then picked:
 *   - flags & 1: D_800734A8[1] with alpha forced to 0x4C;
 *   - else flags & 0x100: D_8900A5D4[(flags & 2) ? 0 : 1];
 *   - otherwise: D_800734A8[(flags & 2) ? 0 : 1];
 * and the string is printed at (x + 8, y + 4) with font set 8 in translucent text
 * mode.  `index` is unused.  (A shorter sibling of PcSort_DrawMenuRow, which has two more
 * color tables.)
 */
void Ui_FillRectHighlighted(s32, s32, s32, s32, Color_RGBA8);
M2C_UNK func_8001AA9C(u8, u8, u8, u8);
extern Color_RGBA8 D_8900A5D4[];
extern u8 D_800734A8[];
/**
 * Draws one menu row label with the selection highlight (dimmed when disabled).
 * Seen in play (2026-11-13) drew the rows of the item sort screen's source window (てもちの どうぐ, サトシの
 * パソコン, 64の カセット).
 */
void LabItem_DrawMenuRow(s32 x, s32 y, char* str, UNUSED s32 index, s32 flags) {
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
        color = D_8900A5D4[(flags & 2) ? 0 : 1];
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
 * Seen in play (2026-11-13) in せいとん > どうぐを いどうする, A opened the three-row source window (てもちの どうぐ,
 * サトシの パソコン, 64の カセット) and this ran once as it appeared.
 */
void LabItem_InitMenuWindow(LabItemMenuWindow* win, s32 x, s32 y, s32 names, s32 count, s32 cursor) {
    s32 pad[2]; // FAKE: stack padding

    Window_SetRect((s8*)&win->window, x, y, 0xE4, (count * 0x1C) + 0x14);
    win->window.state = 0;
    win->window.title = NULL;
    win->window.animTimer = 0;
    win->window.frame.style = 0;
    *(Color_RGBA8*)&win->window.frame.color = D_8900A5BC;
    func_80027804((s8*)&win->items, names, count, count);
    Menu_Init((s8*)&win->menu, (s32)&win->items, (s32)win->itemFlags, (s32)LabItem_DrawMenuRow, 0xD8, 0x1C);
    win->menu.cursor = cursor;
    win->menu.options |= 0x10000;
}

s32 func_8002AE6C();                                /* extern */
M2C_UNK Menu_DrawItems(s8 *, s32, s32, M2C_UNK, s32); /* extern */

/**
 * Draws the menu window's items.
 * Seen in play (2026-11-13) drew the three-row source window (てもちの どうぐ, サトシの パソコン, 64の カセット) on the
 * item sort screen.
 */
void LabItem_DrawMenu(LabItemMenuWindow* win) {
    if (func_8002AE6C() == 0) {
        Menu_DrawItems((s8*)&win->menu, win->window.frame.x + 6, win->window.frame.y + 0xA, 0xFFEF, 0);
    }
}

s32 Menu_UpdateCursorSkipDisabled(void*);
/**
 * Moves the menu cursor. Returns -1 on cancel, the 1-based row on confirm, otherwise 0.
 * Seen in play (2026-11-13) ran every frame while the item sort screen's source window (てもちの どうぐ,
 * サトシの パソコン, 64の カセット) had the cursor.
 */
s32 LabItem_UpdateMenuCursor(LabItemMenuWindow* win) {
    s32 sp1C = 0;
    s32 dir;

    if (Menu_UpdateCursorSkipDisabled(&win->menu) == 0) {
        dir = func_8002BC14(D_800603C0);
        if (dir == -1) {
            func_8003F6AC(3);
            sp1C = -1;
        } else if (dir == 1) {
            sp1C = win->menu.cursor + 1;
        }
    }
    return sp1C;
}

extern Gfx D_80060270[];
extern Color_RGBA8 D_8900A5E0;
extern Color_RGBA8 D_8900A5E8;
extern Color_RGBA8 D_8900A5EC[];
extern char D_8901848C[];
char* func_8001FDC8(u8, char*);
s32 func_80031C24(u8);
s32 func_80031CC8(u8);
void Font_SetColorForFlags(s32);
/**
 * Draws one item row: the item name, and ×count unless the item has no quantity.
 * Seen in play (2026-11-14): キズぐすり ×03, モンスターボール ×05, わざマシン０１ ×01.
 */
void LabItem_DrawItemCountRow(s32 x, s32 y, u8* row, s32 index, s32 flags) {
    char buf[0x30];

    gSPDisplayList(gDisplayListHead++, D_80060270);
    func_80029028(x, y + 1, 0xEC, 0x1A, *(Color_RGBA8*)&D_8900A5E0);
    func_80029028(x, y, 0xEC, 1, *(Color_RGBA8*)&D_8900A5E8);
    func_80029028(x, y + 0x1B, 0xEC, 1, *(Color_RGBA8*)&D_8900A5E8);
    if (flags & 0x18) {
        Ui_FillRectHighlighted(x + 3, y + 3, 0xE6, 0x16, D_8900A5BC);
    }
    if (row != NULL) {
        func_8001AB6C();
        func_8001A384(8, 0);
        if (func_80031C24(row[0]) != 0) {
            Color_RGBA8 color;

            color = D_8900A5EC[(flags & 2) ? 0 : 1];
            func_8001AA9C(color.r, color.g, color.b, color.a);
        } else {
            Font_SetColorForFlags(flags);
        }
        func_8001A944(x + 8, y + 4, func_8001FDC8(row[0], buf));
        if (func_80031CC8(row[0]) == 0) {
            func_8001A384(4, 0);
            func_8001A944(x + 0xB4, y + 8, D_8901848C, row[1]);
        }
        func_8001ABBC();
    }
}

/**
 * Points the item list at another item table.
 * Seen in play (2026-11-14): switched the left list to the picked source and the right list to the picked
 * destination (サトシのパソコン, 64の カセット).
 */
void LabItem_SetItemList(LabItemList* list, s32 table) {
    ScrollList_SetItems((s8*)&list->list, table, (s8*)list->itemFlags);
}

void ScrollList_Init(s8*, s32, s8*, s32, void*, s32, s32);
void LabItem_DrawItemCountRow();

/**
 * Sets up the scrolling item list at (`arg1`, `arg2`) with LabItem_DrawItemCountRow rows.
 * Seen in play (2026-11-12): set up the てもちの どうぐ and サトシのパソコン lists.
 */
void LabItem_InitItemList(LabItemList* list, s32 x, s32 y, s32 table) {
    list->x = x;
    list->y = y;
    ScrollList_Init((s8*)&list->list, table, (s8*)list->itemFlags, 8, LabItem_DrawItemCountRow, 0xEC, 0x1C);
    list->list.options |= 0x10000;
}

void func_8002F9D8(void *, s32, s32, s32, s32);
void ScrollList_DrawInlineItems(void *, s32, s32, s32, s32);
void Ui_DrawNumberZeroPadded(s32, s32, s32, s32);
void func_8001BCB4(s32, s32, s32, s32, void *, s32, s32);
extern Gfx D_80073450[];
extern u8 D_04011AB8[];
/**
 * Draws the scrolling item list and its scroll bar.
 * Seen in play (2026-11-12): those lists with 000/020 and 000/050.
 */
void LabItem_DrawItemList(LabItemList* list, s32 flags) {
    if (flags & 0x200) {
        func_8002F9D8(&list->list, list->x, list->y + 0x10, flags | 0xFFED, 0);
    } else {
        ScrollList_DrawInlineItems(&list->list, list->x, list->y + 0x10, flags | 0xFFED, 0);
    }
    Ui_DrawNumberZeroPadded(list->x + 0xA8, list->y + 0xF2, list->list.items->count, 3);
    Ui_DrawNumberZeroPadded(list->x + 0xCE, list->y + 0xF2, list->list.items->capacity, 3);
    gSPDisplayList(gDisplayListHead++, D_80073450);
    gDPSetCombineMode(gDisplayListHead++, G_CC_DECALRGBA, G_CC_DECALRGBA);
    func_8001BCB4(list->x + 0xC4, list->y + 0xF4, 8, 0xA, D_04011AB8, 8, 0);
}

s32 ScrollList_UpdateCursor(void*);
s32 func_80030230(void*);

/**
 * Moves the item list cursor (paged when `flags` has 0x200, which also allows the empty row
 * past the end as an insert position). Returns -1 on cancel, 1 on confirm, otherwise 0.
 * Seen in play (2026-11-14) picking items and destination rows in どうぐをいどうする.
 */
s32 LabItem_UpdateItemList(void* menu, u32 flags) {
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

void func_80027410(s8*, s8*, s32, s32, s32);
s32 func_800564D4(char*, const char*, ...);
extern Color_RGBA8 D_8900A600;
extern Color_RGBA8 D_8900A604;
extern u8 D_8900A580[];
extern u8 D_8900BFC0[];
extern u8 D_8900DAD0[];
extern u8 D_8900E858[];
extern u8 D_8900F5E0[];
extern char D_890184BC[];
extern char D_890190F0[];
extern char D_890184CC[];
extern s32 D_8901911C;
extern char* D_8900A5F4[];
/**
 * Sets up the どうぐのせいり (organize items) window for %sのパソコン (%s's PC).
 * Seen in play (2026-11-12): opened どうぐのせいり with サトシのパソコン.
 */
void LabItem_InitOrganizeWindow(LabItemOrganizeWindow* win, s32 x, s32 y, ByteMatrix* tables, s32* dirty, s32* gamePakSlot) {
    Window_SetRect(&win->window, x, y, 0x234, 0x174);
    win->window.animTimer = 0;
    win->window.state = 0;
    win->window.frame.style = 0x801;
    win->window.title = D_890184BC;
    Window_SetRect(&win->footerFrame, win->window.frame.x + 6, win->window.frame.y + 0x136, win->window.frame.width - 0xC, 0x38);
    win->footerFrame.style = 6;
    win->footerFrame.color = D_8900A600;
    win->footerFrame.color2 = D_8900A604;
    func_8002B018(&win->backButton, x + 0xFF, y + 0x3A, 0x36, 0x2A, 0x30, (s32)D_8900BFC0);
    win->backButton.selectedColor = ((Color_RGBA8*)D_8900A580)[0];
    win->backButton.color = ((Color_RGBA8*)D_8900A580)[1];
    win->backButton.highlightColor = D_8900A5BC;
    func_8002B018(&win->moveButton, x + 0xFF, y + 0x74, 0x36, 0x2A, 0x30, (s32)D_8900DAD0);
    win->moveButton.selectedColor = ((Color_RGBA8*)D_8900A580)[2];
    win->moveButton.color = ((Color_RGBA8*)D_8900A580)[3];
    win->moveButton.highlightColor = D_8900A5BC;
    func_8002B018(&win->reorderButton, x + 0xFF, y + 0xAE, 0x36, 0x2A, 0x30, (s32)D_8900E858);
    win->reorderButton.selectedColor = ((Color_RGBA8*)D_8900A580)[4];
    win->reorderButton.color = ((Color_RGBA8*)D_8900A580)[5];
    win->reorderButton.highlightColor = D_8900A5BC;
    func_8002B018(&win->exchangeButton, x + 0xFF, y + 0xE8, 0x36, 0x2A, 0x30, (s32)D_8900F5E0);
    win->exchangeButton.selectedColor = ((Color_RGBA8*)D_8900A580)[6];
    win->exchangeButton.color = ((Color_RGBA8*)D_8900A580)[7];
    win->exchangeButton.highlightColor = D_8900A5BC;
    win->rightBox = 1;
    win->leftBox = 0;
    func_800564D4(D_890190F0, D_890184CC, &D_8901911C);
    win->boxNames = D_8900A5F4;
    win->boxCount = 3;
    win->operationCursor.count = 4;
    win->operationCursor.cursor = 0;
    win->operationCursor.controller = D_800603C0;
    func_8000B2F4(D_800603C0);
    win->state = 1;
    win->tables = tables;
    win->dirty = dirty;
    win->gamePakSlot = gamePakSlot;
    LabItem_InitItemList(&win->leftList, win->window.frame.x + 0xC, win->window.frame.y + 0x2A, (s32)&tables[win->leftBox]);
    LabItem_InitItemList(&win->rightList, win->window.frame.x + 0x13C, win->window.frame.y + 0x2A, (s32)&tables[win->rightBox]);
    func_80027410((s8*)&win->reorderView, (s8*)win->tables->rows, 2, win->tables->capacity, 0);
}


extern PrimEnvColor D_8900A608;
extern PrimEnvColor D_8900A610;
extern u8* D_89017A80[];
extern u8 D_89017A98[];
extern s32 D_89019114;
extern Gfx D_80073408[];
extern Gfx D_80073438[];
void Gfx_DrawTextureRgba16(s32, s32, s32, s32, u8*, s32, s32);
void Font_SetColorForFlags(s32);
s32 func_8002BC44(s32);

/**
 * Draws the tab above an item list: the list's icon and name from `win->boxNames`
 * (てもちの どうぐ, %sのパソコン, 64の カセット), or a blank tab for -1 (the reorder view).
 * Seen in play (2026-11-14): drew the てもちの どうぐ and サトシのパソコン tabs, and 64の カセット after it was picked.
 */
void LabItem_DrawListTab(LabItemOrganizeWindow* win, s32 x, s32 y, s32 flags, s32 icon) {
    PrimEnvColor* colors;

    if (flags & 2) {
        colors = &D_8900A608;
    } else {
        colors = &D_8900A610;
    }
    Ui_FillRectPrimEnvColor(x, y, 0xEC, 0x1E, colors->prim, colors->env);
    if (icon != -1) {
        gSPDisplayList(gDisplayListHead++, D_80073408);
        switch (icon) {
            case 0:
            case 1:
                Gfx_DrawTextureRgba16(x + 5, y + 2, 0x18, 0x1A, D_89017A80[func_8002BC44(D_89019114)], 0x18, 0x200000);
                break;
            case 2:
                Gfx_DrawTextureRgba16(x + 5, y + 2, 0x2E, 0x1A, D_89017A98, 0x30, 0x200000);
                break;
        }
        gSPDisplayList(gDisplayListHead++, D_80073438);
        func_8001AB6C();
        Font_SetColorForFlags(flags);
        func_8001A384(8, 0);
        func_8001A944(x + 0x21, y + 4, win->boxNames[icon]);
        func_8001ABBC();
    }
}

M2C_UNK func_8001A384(M2C_UNK, M2C_UNK);            /* extern */
M2C_UNK func_8001A944(s32, s32, ...);
M2C_UNK func_8001AA9C(u8, u8, u8, u8);              /* extern */
M2C_UNK func_8001AAE4(u8, u8, u8, u8);              /* extern */
M2C_UNK func_8001AB6C();                            /* extern */
M2C_UNK func_8001ABBC();                            /* extern */
M2C_UNK func_8001ABE8();                            /* extern */
M2C_UNK func_8001AC3C();                            /* extern */
u32 func_800566BC(s32);                             /* extern */

/**
 * Draws title text with the two-color (prim/env) font style from `arg3`.
 * Seen in play (2026-11-12): the ポケモンのせいり / どうぐのせいり titles.
 */
void LabItem_DrawTitleText(s32 x, s32 y, s32 text, PrimEnvColor* colors) {
    func_8001AB6C();
    func_8001A384(0x20, 0);
    func_8001AA9C(colors->prim.r, colors->prim.g, colors->prim.b, colors->prim.a);
    func_8001ABE8();
    func_8001AAE4(colors->env.r, colors->env.g, colors->env.b, colors->env.a);
    func_8001A944(((u32) (0x178 - ((func_800566BC(text) >> 1) << 5)) >> 1) + x, y + 0xC, text);
    func_8001AC3C();
    func_8001ABBC();
}

extern u8 D_800734A8[];

/**
 * Draws `arg2` centered in the 376-pixel help area.
 * Seen in play (2026-11-13) ran when the item sort screen's help line changed to 「どこから いどうする?」,
 * which sits centered in the bottom help area.
 */
void LabItem_DrawCenteredText(s32 x, s32 y, char* text) {
    Font_BeginTranslucentTextRendering();
    Font_SetActive(0x10, 0);
    Gfx_SetEnvColor(D_800734A8[0], D_800734A8[1], D_800734A8[2], D_800734A8[3]);
    Font_Printf(((0x178 - (strlen(text) / 2) * 0x18) / 2) + x, y + 0x10, text);
    Font_EndTexturedTextRendering();
}

M2C_UNK func_8001A384(M2C_UNK, M2C_UNK);            /* extern */
M2C_UNK func_8001A944(s32, s32, ...);
M2C_UNK func_8001AA9C(u8, u8, u8, u8);              /* extern */
void Font_SetLineHeight(s32 arg0);                     /* extern */
M2C_UNK func_8001AB6C();                            /* extern */
M2C_UNK func_8001ABBC();                            /* extern */
extern u8 D_800734A8[];

/**
 * Draws `text` in the small font in the help area.
 * Seen in play (2026-11-14): the item descriptions (「たたかいで うしなった HPを 20かいふく する。」).
 */
void LabItem_DrawSmallText(s32 x, s32 y, s32 text) {
    func_8001AB6C();
    func_8001A384(8, 0);
    func_8001AA9C(D_800734A8[0], D_800734A8[1], D_800734A8[2], D_800734A8[3]);
    Font_SetLineHeight(0x1C);
    func_8001A944(x + 8, y + 4, text);
    func_8001ABBC();
}

extern s32 D_8900A650[];
extern char* D_8900A660[];
extern char* D_8900A66C[];
extern PrimEnvColor* D_8900A678[];
s32 func_80031BC0(u8, char *);
/**
 * Draws the help line for the organize window's current state.
 * Seen in play (2026-11-12): 「どうぐをいどうする」.
 */
void LabItem_DrawHelpText(LabItemOrganizeWindow* win) {
    char sp2C[0x54];
    ScrollList* list;

    switch (win->state) {
        case 1:
            LabItem_DrawTitleText(win->footerFrame.x + 0x58, win->footerFrame.y, D_8900A650[win->operationCursor.cursor], D_8900A678[win->operationCursor.cursor]);
            break;
        case 2:
            LabItem_DrawCenteredText(win->footerFrame.x + 0x58, win->footerFrame.y, D_8900A660[win->operationCursor.cursor]);
            break;
        case 3:
            LabItem_DrawCenteredText(win->footerFrame.x + 0x58, win->footerFrame.y, D_8900A66C[win->operationCursor.cursor]);
            break;
        case 4:
        case 6:
        case 7:
            if (win->state == 6) {
                list = &win->rightList.list;
            } else {
                list = &win->leftList.list;
            }
            LabItem_DrawSmallText(win->footerFrame.x + 0x58, win->footerFrame.y, func_80031BC0(list->items->rows[list->cursor * 2], sp2C));
            break;
    }
}

void Ui_DrawTexturedFrameDecal(s32, s32, s32, s32, u8*);
extern u8 D_800735C4[];
void Window_DrawFrame(void*);
void LabItem_DrawItemList(LabItemList* arg0, s32 arg1);
/**
 * Draws the organize items window: frame, lists and help line.
 * Seen in play (2026-11-12): the どうぐのせいり window.
 */
void LabItem_DrawOrganizeWindow(LabItemOrganizeWindow* win) {
    s32 v;
    s32 flags;

    if (func_8002AE6C(&win->window) == 0) {
        Window_DrawFrame(&win->footerFrame);
        gSPDisplayList(gDisplayListHead++, D_80060270);
        func_80029028(win->window.frame.x + 6, win->window.frame.y + 6, win->window.frame.width - 0xC, 6, D_8900A5BC);
        func_80029028(win->window.frame.x + 6, win->window.frame.y + 0x12A, win->window.frame.width - 0xC, 6, D_8900A5BC);
        func_80029028(win->window.frame.x + 6, win->window.frame.y + 0xC, 6, 0x11E, D_8900A5BC);
        func_80029028(win->window.frame.x + win->window.frame.width - 0xC, win->window.frame.y + 0xC, 6, 0x11E, D_8900A5BC);
        func_80029028(win->window.frame.x + 0xF8, win->window.frame.y + 0xC, 0x44, 0x11E, D_8900A5BC);
        Ui_DrawTexturedDivider(win->window.frame.x, win->window.frame.y + 0x12F, win->window.frame.width, D_8007356C);
        Ui_DrawTexturedFrameDecal(win->window.frame.x + 0xA, win->window.frame.y + 0xA, 0xF0, 0x122, D_800735C4);
        Ui_DrawTexturedFrameDecal(win->window.frame.x + 0x13A, win->window.frame.y + 0xA, 0xF0, 0x122, D_800735C4);
        v = (win->state == 1) ? 2 : 0x10;
        func_8002B054(&win->backButton, (win->operationCursor.cursor == 3) ? v : 0);
        func_8002B054(&win->moveButton, (win->operationCursor.cursor == 0) ? v : 0);
        func_8002B054(&win->reorderButton, (win->operationCursor.cursor == 1) ? v : 0);
        func_8002B054(&win->exchangeButton, (win->operationCursor.cursor == 2) ? v : 0);
        LabItem_DrawListTab(win, win->window.frame.x + 0xC, win->window.frame.y + 0xC, 0, win->leftBox);
        LabItem_DrawListTab(win, win->window.frame.x + 0x13C, win->window.frame.y + 0xC, 0, win->rightBox);
        LabItem_DrawItemList(&win->leftList, ((win->state == 4) || (win->state == 7)) ? 2 : ((win->state == 5) || (win->state == 6)) ? 0x10 : 0);
        flags = ((win->state == 5) || (win->state == 6)) ? 2 : 0;
        flags |= (win->state == 5) ? 0x200 : 0;
        LabItem_DrawItemList(&win->rightList, flags);
        if ((win->state == 2) || (win->state == 9)) {
            LabItem_DrawMenu(&win->sourceBoxWindow);
        }
        if ((win->state == 3) || (win->state == 0xA)) {
            LabItem_DrawMenu(&win->targetBoxWindow);
        }
        LabItem_DrawHelpText(win);
        if ((win->state == 9) || (win->state == 0xA) || (win->state == 0xB) || (win->state == 0xC)) {
            TextBox_Draw(&win->textBox);
        }
        if (win->state == 8) {
            LabItem_DrawCountSelector(&win->countSelector);
        }
    }
}

/**
 * Moves the selected item from the left list to the right one and marks both lists
 * changed. A quantityless item moves as its row; anything else moves the count from the
 * count selector (LabItem_InsertItemStacks, then LabItem_DecreaseSelectedCount).
 * Seen in play (2026-11-14): moving 2 of キズぐすり ×03 left ×01 in てもち and added ×02 to サトシのパソコン.
 */
void LabItem_MoveSelectedItem(LabItemOrganizeWindow* win) {
    u8* item;

    item = win->leftList.list.items->rows + win->leftList.list.cursor * 2;
    win->dirty[win->targetBoxWindow.menu.cursor] = 1;
    win->dirty[win->sourceBoxWindow.menu.cursor] = win->dirty[win->targetBoxWindow.menu.cursor];
    if (LabItem_IsQuantitylessItemForOperation(item[0]) != 0) {
        LabList_InsertRowAtCursor((LabMonEntryList*)&win->rightList, (void*)(win->leftList.list.items->rows + win->leftList.list.items->rowSize * win->leftList.list.cursor));
        LabList_RemoveSelectedEntry(&win->leftList.list);
    } else {
        LabItem_InsertItemStacks((s32*)&win->rightList, item[0], win->countSelector.count.value);
        LabItem_DecreaseSelectedCount((ScrollList*)&win->leftList, win->countSelector.count.value);
    }
}

void func_80027654(ByteMatrix* matrix, u8* out, s32 row);
void func_80027700(ByteMatrix* matrix, u8* in, s32 row);

/**
 * Swaps the selected rows of the left and right item lists and marks both changed.
 * Seen in play (2026-11-14) in どうぐをいれかえる: キズぐすり ×01 (てもち) and モンスターボール ×05
 * (サトシのパソコン) traded places.
 */
void LabItem_SwapBetweenLists(LabItemOrganizeWindow* win) {
    u8 row[4];
    ByteMatrix* matrix;

    func_80027654(win->rightList.list.items, row, win->rightList.list.cursor);
    matrix = win->leftList.list.items;
    func_80027700(win->rightList.list.items, matrix->rows + matrix->rowSize * win->leftList.list.cursor, win->rightList.list.cursor);
    func_80027700(win->leftList.list.items, row, win->leftList.list.cursor);
    win->dirty[win->rightBox] = 1;
    win->dirty[win->leftBox] = win->dirty[win->rightBox];
}

void func_80027654(ByteMatrix* matrix, u8* out, s32 row);
void func_80027700(ByteMatrix* matrix, u8* in, s32 row);

/**
 * Swaps the row picked first (swapIndex) with the selected row of the same list and marks it
 * changed. Seen in play (2026-11-14) in どうぐをならべかえる: キズぐすり and モンスターボール traded rows in てもち.
 */
void LabItem_SwapWithinList(LabItemOrganizeWindow* win) {
    u8 row[4];
    ByteMatrix* matrix = win->leftList.list.items;

    func_80027654(matrix, row, win->leftList.list.cursor);
    func_80027700(matrix, matrix->rows + matrix->rowSize * win->swapIndex, win->leftList.list.cursor);
    func_80027700(matrix, row, win->swapIndex);
    win->dirty[win->leftBox] = 1;
}


/**
 * Shows the destination list picked in 「どこへいどうする？」 on the right and moves on to
 * picking the item (state 4). Seen in play (2026-11-14): opened サトシのパソコン and 64の カセット as the destination.
 * Also called after a 64 save slot is freed, to open 64の カセット.
 */
void LabItem_OpenTargetList(LabItemOrganizeWindow* win) {
    s32 temp_v0;
    LabItemList* temp_a0;

    temp_v0 = win->targetBoxWindow.menu.cursor;
    temp_a0 = &win->rightList;
    win->rightBox = temp_v0;
    LabItem_SetItemList(temp_a0, (s32)&win->tables[temp_v0]);
    win->state = 4;
}

s32 func_8002B2B0(void *);
s32 Menu_SkipDisabledForward(Menu*);
extern s32 D_8900A688[];
extern s32 D_8900A694;
extern s8 D_89018648[];

typedef struct Pair89002318 { u8 unk0; u8 unk1; } Pair89002318;
typedef struct Ent89002318 { char unk0[0x10]; } Ent89002318;

/**
 * Runs the organize items window's state machine (move, toss, deposit, withdraw).
 * Seen in play (2026-11-12): ran どうぐのせいり.
 */
s32 LabItem_UpdateOrganizeWindow(LabItemOrganizeWindow* win) {
    s32 ret = 0;
    s32 idx;
    s32 next = 0;
    u8* ptr;
    s32 v;
    u8* ptr2;

    switch (win->state) {
        case 1:
            if (func_8002B2B0(&win->operationCursor) != 0) {
                break;
            }
            v = func_8002BC14(D_800603C0);
            if (v == -1) {
                func_8003F6AC(3);
                ret = -1;
                break;
            }
            if (v != 1) {
                break;
            }
            if (win->operationCursor.cursor == 3) {
                func_8003F6AC(3);
                ret = -1;
                break;
            }
            func_8003F6AC(2);
            next = 2;
            if (win->operationCursor.cursor != 1) {
                break;
            }
            LabItem_SetItemList(&win->rightList, &win->reorderView);
            win->rightBox = -1;
            break;

        case 2:
            v = LabItem_UpdateMenuCursor(&win->sourceBoxWindow);
            if (v == -1) {
                win->state = 1;
                break;
            }
            if (v <= 0) {
                break;
            }
            if (win->sourceBoxWindow.menu.itemFlags[win->sourceBoxWindow.menu.cursor] & 0x100) {
                win->state = 9;
                TextBox_Init(&win->textBox, (void*)D_8900A688[win->operationCursor.cursor], 0, 1, 0);
                func_8003F6AC(8);
                break;
            }
            func_8003F6AC(2);
            idx = win->sourceBoxWindow.menu.cursor;
            win->leftBox = idx;
            LabItem_SetItemList(&win->leftList, (s32)&win->tables[idx]);
            if (win->operationCursor.cursor == 1) {
                win->state = 4;
                break;
            }
            next = 3;
            break;

        case 3:
            v = LabItem_UpdateMenuCursor(&win->targetBoxWindow);
            if (v == -1) {
                next = 2;
                break;
            }
            if (v <= 0) {
                break;
            }
            if (win->targetBoxWindow.menu.itemFlags[win->targetBoxWindow.menu.cursor] & 0x100) {
                func_8003F6AC(8);
                win->state = 10;
                TextBox_Init(&win->textBox, (void*)D_8900A688[win->operationCursor.cursor], 0, 1, 0);
                break;
            }
            func_8003F6AC(2);
            if (win->targetBoxWindow.menu.cursor == 2) {
                if (*win->gamePakSlot == -1) {
                    ret = 1;
                    break;
                }
            }
            LabItem_OpenTargetList(win);
            break;

        case 4:
            v = LabItem_UpdateItemList(&win->leftList, 0);
            if (v == -1) {
                win->state = 1;
                break;
            }
            if (v != 1) {
                break;
            }
            ptr = win->leftList.list.items->rows + win->leftList.list.cursor * 2;
            if (win->operationCursor.cursor == 0) {
                if (func_80031C24(*ptr) != 0 && win->rightBox == 2) {
                    func_8003F6AC(8);
                    TextBox_Init(&win->textBox, (void*)D_8900A694, 1, 2, 0xC);
                    win->state = 11;
                    break;
                }
                v = LabItem_ComputeMaxTransferQuantity(*ptr, win->rightList.list.items);
                if (v == 0) {
                    func_8003F6AC(8);
                    win->state = 11;
                    TextBox_Init(&win->textBox, D_89018648, 0, 1, 0);
                    break;
                }
                func_8003F6AC(2);
                if (func_80031CC8(*ptr) == 0) {
                    LabItem_InitCountSelector(&win->countSelector, win->leftList.x + 0x98,
                                  win->leftList.y + win->leftList.list.cursorY - win->leftList.list.scrollY + 0x2C,
                                  ptr[1], v);
                    win->state = 8;
                } else {
                    win->state = 5;
                }
                break;
            }
            if (win->operationCursor.cursor == 2) {
                if (func_80031C24(*ptr) != 0 && win->rightBox == 2) {
                    func_8003F6AC(8);
                    TextBox_Init(&win->textBox, (void*)D_8900A694, 1, 2, 0xC);
                    win->state = 11;
                    break;
                }
                func_8003F6AC(2);
                win->state = 6;
                break;
            }
            func_8003F6AC(2);
            win->leftList.list.itemFlags[win->leftList.list.cursor] |= 8;
            win->swapIndex = win->leftList.list.cursor;
            win->state = 7;
            break;

        case 8:
            v = LabItem_UpdateCountSelector(&win->countSelector);
            if (v == -1) {
                win->state = 4;
                break;
            }
            if (v == 1) {
                win->state = 5;
            }
            break;

        case 5:
            v = LabItem_UpdateItemList(&win->rightList, 0x200);
            if (v == -1) {
                win->state = 4;
                break;
            }
            if (v != 1) {
                break;
            }
            func_8003F6AC(0x18);
            LabItem_MoveSelectedItem(win);
            if (win->leftList.list.items->count == 0) {
                win->state = 1;
                break;
            }
            win->state = 4;
            break;

        case 7:
            v = LabItem_UpdateItemList(&win->leftList, 0);
            if (v == -1) {
                Menu_ClearItemFlags((Menu*)&win->leftList.list);
                win->state = 4;
                break;
            }
            if (v != 1) {
                break;
            }
            func_8003F6AC(0x18);
            LabItem_SwapWithinList(win);
            Menu_ClearItemFlags((Menu*)&win->leftList.list);
            win->state = 4;
            break;

        case 6:
            v = LabItem_UpdateItemList(&win->rightList, 0);
            if (v == -1) {
                win->state = 4;
                break;
            }
            if (v != 1) {
                break;
            }
            ptr2 = win->rightList.list.items->rows + win->rightList.list.cursor * 2;
            if (func_80031C24(*ptr2) != 0 &&
                win->leftBox == 2) {
                func_8003F6AC(8);
                TextBox_Init(&win->textBox, (void*)D_8900A694, 1, 2, 0xC);
                win->state = 12;
                break;
            }
            func_8003F6AC(0x18);
            LabItem_SwapBetweenLists(win);
            win->state = 4;
            break;

        case 9:
            if (Ui_CheckConfirmPressed(&win->textBox) == 1) {
                win->state = 2;
            }
            break;
        case 10:
            if (Ui_CheckConfirmPressed(&win->textBox) == 1) {
                win->state = 3;
            }
            break;
        case 11:
            if (Ui_CheckConfirmPressed(&win->textBox) == 1) {
                win->state = 4;
            }
            break;
        case 12:
            if (Ui_CheckConfirmPressed(&win->textBox) == 1) {
                win->state = 6;
            }
            break;
    }

    if (next > 0) {
        switch (next) {
            case 2:
                LabItem_InitMenuWindow(&win->sourceBoxWindow, win->window.frame.x + 0x1F, win->window.frame.y + 0x29, (s32)win->boxNames,
                              win->boxCount, win->leftBox);
                LabItem_DisableEmptyLists(&win->sourceBoxWindow, win->tables);
                break;
            case 3:
                LabItem_InitMenuWindow(&win->targetBoxWindow, win->window.frame.x + 0x14F, win->window.frame.y + 0x29, (s32)win->boxNames,
                              win->boxCount, win->rightBox);
                if (win->operationCursor.cursor == 2) {
                    LabItem_DisableEmptyLists(&win->targetBoxWindow, win->tables);
                }
                LabItem_DisableRow(&win->targetBoxWindow, win->leftBox);
                win->targetBoxWindow.menu.cursor = 0;
                Menu_SkipDisabledForward(&win->targetBoxWindow.menu);
                break;
        }
        win->state = next;
    }
    return ret;
}

extern Color_RGBA8 D_8900A698;
extern u8 D_8900A69C[];
extern char D_89018660[];
extern char D_8901866C[];
void Ui_DrawImageInStrips(void*, s32, s32);
void Font_SetColorForFlags(s32);
/**
 * Draws one row of the データをけす list: cassette icon, なまえ/%s and ID No/%05d.
 * Seen in play (2026-11-14): the four rows タケシ 01000 ... エリカ 04000 (poked in RAM).
 */
void LabItem_DrawTrainerInfo(s32 x, s32 y, LabItemSaveSlot* slot, s32 index, s32 flags) {
    gSPDisplayList(gDisplayListHead++, D_80060270);
    func_80029028(x, y + 1, 0x13C, 0x3C, *(Color_RGBA8*)&D_8900A5BC);
    func_80029028(x, y, 0x13C, 1, D_8900A698);
    func_80029028(x, y + 0x3D, 0x13C, 1, D_8900A698);
    if (flags & 0x10) {
        Ui_FillRectHighlighted(x + 3, y + 3, 0x136, 0x38, D_8900A5BC);
    }
    Ui_DrawImageInStrips(D_8900A69C, x + 0xB, y + 0xB);
    Font_BeginTranslucentTextRendering();
    Font_SetColorForFlags(flags);
    Font_SetActive(0x10, 0);
    Font_Printf(x + 0x53, y + 6, D_89018660, slot->trainerName);
    Font_SetActive(8, 0);
    Font_Printf(x + 0x58, y + 0x24, D_8901866C, slot->trainerId);
    Font_EndTexturedTextRendering();
}

extern Color_RGBA8 D_8900A6AC;
extern Color_RGBA8 D_8900A6B0;
extern char D_89018678[];
void LabItem_DrawTrainerInfo();
void Window_SetRect(s8*, s32, s32, s32, s32);
void Menu_Init(s8*, s32, s32, s32, s32, s32);
void func_80027410(s8*, s8*, s32, s32, s32);
/**
 * Sets up the データをけす window over the four 64 item saves, with
 * 「セーブは４つぶんだけです けすデータをえらんでください」.
 * Seen in play (2026-11-14): opened after はい on 「６４カセットに あきが ありません」.
 */
void LabItem_InitDeleteDataWindow(LabItemDeleteDataWindow* win, s32 x, s32 y, LabItemSaveSlot* slots) {
    s32 pad[2]; // FAKE: stack padding
    Window_SetRect((s8*)&win->window, x, y, 0x148, 0x14A);
    win->window.animTimer = 0;
    win->window.state = 0;
    win->window.frame.style = 0x801;
    win->window.title = D_89018678;
    Window_SetRect((s8*)&win->footerFrame, win->window.frame.x + 6, win->window.frame.y + 0x104, win->window.frame.width - 0xC, 0x40);
    win->footerFrame.style = 6;
    win->footerFrame.color = D_8900A6AC;
    win->footerFrame.color2 = D_8900A6B0;
    func_80027410((s8*)&win->slotTable, (s8*)slots, 0x14, 4, 4);
    Menu_Init((s8*)&win->menu, (s32)&win->slotTable, (s32)win->itemFlags, (s32)LabItem_DrawTrainerInfo, 0x13C, 0x3E);
    win->menu.options |= 0x10000;
}

void Ui_DrawTexturedDivider(s32, s32, s32, void*);
void Window_DrawFrame(void*);
void Menu_DrawInlineItems(void*, s32, s32, s32, s32);
extern u8 D_8007356C[];
extern u8 D_89018688[];
/**
 * Draws the データをけす window. Seen in play (2026-11-14).
 */
void LabItem_DrawDeleteDataWindow(LabItemDeleteDataWindow* win, s32 flags) {
    if (func_8002AE6C() == 0) {
        Ui_DrawTexturedDivider(win->window.frame.x, win->footerFrame.y - 7, win->window.frame.width, D_8007356C);
        Window_DrawFrame(&win->footerFrame);
        Menu_DrawInlineItems(&win->menu, win->window.frame.x + 6, win->window.frame.y + 6, 0xFFEF, 0);
        func_8001AB6C();
        func_8001A384(8, 0);
        if (!win) { // FAKE: empty test only changes register allocation; needed to match
        }
        func_8001AA9C(D_800734A8[0], D_800734A8[1], D_800734A8[2], D_800734A8[3]);
        Font_SetLineHeight(0x1C);
        func_8001A944(win->footerFrame.x + 8, win->footerFrame.y + 8, D_89018688);
        func_8001ABBC();
    }
}

s32 Menu_UpdateCursor(void*);

/**
 * Moves the データをけす cursor. Returns -1 on cancel, 1 on confirm, otherwise 0.
 * Seen in play (2026-11-14): D-Down moved from タケシ to カスミ, A opened カスミ's save.
 */
s32 LabItem_UpdateDeleteDataCursor(LabItemDeleteDataWindow* win) {
    s32 sp1C = 0;
    s32 dir;

    if (Menu_UpdateCursor(&win->menu) == 0) {
        dir = Ui_GetSelectionDirection(gPlayer1Controller);
        if (dir == -1) {
            Audio_PlaySoundEffectById(3);
            sp1C = -1;
        } else if (dir == 1) {
            Audio_PlaySoundEffectById(2);
            sp1C = 1;
        }
    }
    return sp1C;
}

extern u8 D_8900A580[];
extern u8 D_8900A584[];
extern u8 D_8900A5A0[];
extern u8 D_8900A5A4[];
extern u8 D_8900A5A8[];
extern u8 D_8900A5AC[];
extern Color_RGBA8 D_8900A6B4;
extern Color_RGBA8 D_8900A6B8;
extern u8 D_8900BFC0[];
extern u8 D_89010368[];
extern u8 D_890110F0[];

/**
 * Sets up the window for one 64 item save picked in データをけす: the owner's なまえ and
 * ID No, its item list, and three buttons (メニューへもどる, このデータをすてる,
 * どうぐをかくにんする).
 * Seen in play (2026-11-14): with all four 64 item saves poked in RAM to other trainers (タケシ 01000 ... エリカ
 * 04000), picking カスミ opened it with her (empty) item list, 000/100.
 */
void LabItem_InitSaveDataWindow(LabItemSaveDataWindow* win, s32 x, s32 y, LabItemSaveSlot* slot, ByteMatrix* items) {
    Window_SetRect(&win->window, x, y, 0x184, 0x180);
    win->window.animTimer = 0;
    win->window.title = NULL;
    win->window.state = 0;
    win->window.frame.style = 0x1001;
    Window_SetRect(&win->footerFrame, win->window.frame.x + 6, win->window.frame.y + 0x142,
                  win->window.frame.width - 0xC, 0x38);
    win->footerFrame.style = 6;
    win->footerFrame.color = D_8900A6B4;
    win->footerFrame.color2 = D_8900A6B8;
    func_8002B018(&win->backButton, x + 0x2B, y + 0x47, 0x36, 0x2A, 0x30, (s32)D_8900BFC0);
    win->backButton.selectedColor = *(Color_RGBA8*)D_8900A580;
    win->backButton.color = *(Color_RGBA8*)D_8900A584;
    win->backButton.highlightColor = D_8900A5BC;
    func_8002B018(&win->discardButton, x + 0x2B, y + 0x9F, 0x36, 0x2A, 0x30, (s32)D_890110F0);
    win->discardButton.selectedColor = *(Color_RGBA8*)D_8900A5A8;
    win->discardButton.color = *(Color_RGBA8*)D_8900A5AC;
    win->discardButton.highlightColor = D_8900A5BC;
    func_8002B018(&win->viewItemsButton, x + 0x2B, y + 0xF7, 0x36, 0x2A, 0x30, (s32)D_89010368);
    win->viewItemsButton.selectedColor = *(Color_RGBA8*)D_8900A5A0;
    win->viewItemsButton.color = *(Color_RGBA8*)D_8900A5A4;
    win->viewItemsButton.highlightColor = D_8900A5BC;
    win->operationCursor.count = 3;
    win->operationCursor.cursor = 0;
    win->operationCursor.controller = D_800603C0;
    func_8000B2F4(D_800603C0);
    LabItem_InitItemList(&win->itemList, win->window.frame.x + 0x88, win->window.frame.y + 0x36, (s32)items);
    win->slot = slot;
    win->state = 1;
}

extern PrimEnvColor D_8900A6BC;
extern PrimEnvColor D_8900A6C4;
extern Gfx D_80073408[];
extern Gfx D_80073438[];
extern u8 D_89017A98[];
extern char D_890186C0[];
extern char D_890186CC[];
void Ui_FillRectPrimEnvColor(s32, s32, s32, s32, Color_RGBA8, Color_RGBA8);
void Font_SetColorForFlags(s32);
/**
 * Draws the save owner's なまえ/%s and ID No/%05d with the cassette icon.
 * Seen in play (2026-11-14): なまえ／カスミ, ID No／02000.
 */
void LabItem_DrawSaveDataOwner(s32 x, s32 y, LabItemSaveSlot* slot, s32 flags) {
    PrimEnvColor* color;

    if (flags & 2) {
        color = &D_8900A6BC;
    } else {
        color = &D_8900A6C4;
    }
    Ui_FillRectPrimEnvColor(x, y, 0xEC, 0x2A, color->prim, color->env);
    gSPDisplayList(gDisplayListHead++, D_80073408);
    Gfx_DrawTextureRgba16(x + 6, y + 8, 0x2E, 0x1A, D_89017A98, 0x30, 0x200000);
    gSPDisplayList(gDisplayListHead++, D_80073438);
    Font_BeginTranslucentTextRendering();
    Font_SetColorForFlags(flags);
    Font_SetActive(8, 0);
    Font_Printf(x + 0x34, y + 2, D_890186C0, slot->trainerName);
    Font_SetActive(4, 0);
    Font_Printf(x + 0x38, y + 0x18, D_890186CC, slot->trainerId);
    Font_EndTexturedTextRendering();
}

extern s32 D_8900A6CC[];
extern PrimEnvColor* D_8900A6D8[];
/**
 * Draws the save data window's help line: the selected button's caption, or the
 * selected item's description while the item list has the cursor.
 * Seen in play (2026-11-14): 「このデータをすてる」 and 「どうぐをかくにんする」.
 */
void LabItem_DrawSaveDataHelpText(LabItemSaveDataWindow* win) {
    char sp2C[0x54];
    ScrollList* list;

    switch (win->state) {
        case 1:
            LabItem_DrawTitleText(win->footerFrame.x, win->footerFrame.y, D_8900A6CC[win->operationCursor.cursor], D_8900A6D8[win->operationCursor.cursor]);
            break;
        case 2:
            list = &win->itemList.list;
            LabItem_DrawSmallText(win->footerFrame.x, win->footerFrame.y, func_80031BC0(list->items->rows[list->cursor * 2], sp2C));
            break;
    }
}

void Ui_DrawTexturedFrameDecal(s32, s32, s32, s32, u8*);
extern u8 D_800735C4[];
void Window_DrawFrame(void*);
/**
 * Draws the save data window: frame, buttons, owner, item list and help line.
 * Seen in play (2026-11-14): drew カスミ's save.
 */
void LabItem_DrawSaveDataWindow(LabItemSaveDataWindow* win) {
    s32 v;

    if (func_8002AE6C(&win->window) == 0) {
        Window_DrawFrame(&win->footerFrame);
        Ui_DrawTexturedDivider(win->window.frame.x, win->footerFrame.y - 7, win->window.frame.width, D_8007356C);
        gSPDisplayList(gDisplayListHead++, D_80060270);
        func_80029028(win->window.frame.x + 6, win->window.frame.y + 6, 0x82, 0x136, *(Color_RGBA8*)&D_8900A5BC);
        func_80029028(win->window.frame.x + 0x88, win->window.frame.y + 6, 0xEC, 6, *(Color_RGBA8*)&D_8900A5BC);
        func_80029028(win->window.frame.x + 0x88, win->window.frame.y + 0x136, 0xEC, 6, *(Color_RGBA8*)&D_8900A5BC);
        func_80029028(win->window.frame.x + 0x174, win->window.frame.y + 6, 0xA, 0x136, *(Color_RGBA8*)&D_8900A5BC);
        Ui_DrawTexturedFrameDecal(win->window.frame.x + 0x86, win->window.frame.y + 0xA, 0xF0, 0x12E, D_800735C4);
        v = (win->state == 1) ? 2 : 0x10;
        func_8002B054(&win->backButton, (win->operationCursor.cursor == 2) ? v : 0);
        func_8002B054(&win->discardButton, (win->operationCursor.cursor == 0) ? v : 0);
        func_8002B054(&win->viewItemsButton, (win->operationCursor.cursor == 1) ? v : 0);
        LabItem_DrawSaveDataOwner(win->window.frame.x + 0x88, win->window.frame.y + 0xC, win->slot, 0);
        LabItem_DrawItemList(&win->itemList, (win->state == 2) ? 2 : 0);
        LabItem_DrawSaveDataHelpText(win);
    }
}

s32 func_8002B2B0(void *);
s32 LabItem_UpdateItemList(void *, u32);
/**
 * Runs the save data window. Returns 1 for このデータをすてる, -1 for B or
 * メニューへもどる, otherwise 0; どうぐをかくにんする scrolls the item list until B.
 * Seen in play (2026-11-14): このデータをすてる led to 「このデータをすてますか？」.
 */
s32 LabItem_UpdateSaveDataWindow(LabItemSaveDataWindow* win) {
    s32 ret = 0;

    switch (win->state) {
        case 1:
            if (func_8002B2B0(&win->operationCursor) == 0) {
                s32 r = func_8002BC14(D_800603C0);
                if (r == -1) {
                        func_8003F6AC(3);
                        ret = -1;
                } else if (r == 1) {
                        switch (win->operationCursor.cursor) {
                            case 1:
                                func_8003F6AC(2);
                                win->state = 2;
                                break;
                            case 0:
                                func_8003F6AC(2);
                                ret = 1;
                                break;
                            case 2:
                                func_8003F6AC(3);
                                ret = -1;
                                break;
                        }
                }
            }
            break;
        case 2:
            if (LabItem_UpdateItemList(&win->itemList, 0) == -1) {
                win->state = 1;
            }
            break;
    }
    return ret;
}

extern s32 D_89019108;
extern s32 D_89019118;
extern s32 D_8901911C;

/**
 * Sets up どうぐのせいり: builds the bag (20), PC (50) and 64 cassette (100) item tables,
 * reads the bag (deck 0x23) and the PC items (0x22), finds this trainer's 64 item save
 * (deck 0x12, four slots keyed by trainer ID and name) and reads it if present, clears the
 * dirty flags and opens the organize window.
 * Seen in play (2026-11-14): どうぐを いどうする opened the screen with 003/020, 002/050 and 000/100.
 */
void LabItem_Init(LabItemScreen* screen) {
    s32 i;

    func_80027410((s8*)&screen->itemTables[0], (s8*)screen->bagItemRows, 2, 0x14, 0);
    func_80027410((s8*)&screen->itemTables[1], (s8*)screen->pcItemRows, 2, 0x32, 0);
    func_80027410((s8*)&screen->itemTables[2], (s8*)screen->gamePakItemRows, 2, 0x64, 0);
    LabItem_ReadDeckEntries(0x23, D_89019108, 0, &screen->itemTables[0]);
    LabItem_ReadDeckEntries(0x22, D_89019108, 0, &screen->itemTables[1]);
    LabItem_LoadGamePakBoxSlots(screen->saveSlots);
    screen->gamePakSlot = LabItem_FindOrAllocateGamePakBoxSlot(screen->saveSlots, D_89019118, (char*)&D_8901911C);
    if ((screen->gamePakSlot != -1) && (screen->saveSlots[screen->gamePakSlot].present != 0)) {
        LabItem_ReadDeckEntries(0x12, 0, screen->gamePakSlot, &screen->itemTables[2]);
    }
    i = 0;
    do {
        screen->dirty[i] = 0;
        i++;
    } while (i != 3);
    LabItem_InitOrganizeWindow(&screen->organizeWindow, 0x26, 0x51, screen->itemTables, screen->dirty, &screen->gamePakSlot);
    screen->state = 1;
}
