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

void func_8900020C(void);
s32 LabItem_ComputeRemainingCapacity(s32 arg0, ByteMatrix* arg1);
s32 LabItem_ComputeMaxTransferQuantity(s32 arg0, ByteMatrix* arg1);
s32 LabItem_FindOrAllocateGamePakBoxSlot(LabItemSaveSlot* arg0, s32 arg1, char* arg2);
void LabItem_LoadGamePakBoxSlots(LabItemSaveSlot* arg0);
void LabItem_ReadDeckEntries(s32 arg0, s32 arg1, s32 arg2, ByteMatrix* arg3);

void func_89000020(LabMonEntryList* arg0, s32 (*arg1)(s32, s32)) {
    func_800274E0(arg0->items, arg1, arg0->count);
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
 * symbol_addrs.txt names this function WidgetTree_RemoveScrollableGridEntry,
 * a Stadium 1 name.  The Stadium 1 function of that name is NOT the same
 * code: it removes from a pointer list and, when the index is past the end
 * and positive, sets the index to count - 1.  Zero's version operates on a
 * byte matrix and the retail code simply subtracts 1 from the index, so the
 * name is a rough match at best.
 * Seen in play (2026-11-13) removed the list row when フシギダネ was released (せいとん > ポケモンをにがす) and when
 * a Pokémon moved out of てもち into GBのボックス1, so it serves the Pokémon lists as well as the item
 * list.
 */
void LabList_RemoveSelectedEntry(ScrollList* arg0) {
    func_800275E4((s32)arg0->items, arg0->cursor);
    if (arg0->cursor >= arg0->items->count) {
        arg0->cursor -= 1;
    }
    ScrollList_SetCursorKeepOffset((s32*)arg0, arg0->cursor);
}

void func_800275E4(s32, s32);
int func_800274E0();
void ScrollList_SetCursorKeepOffset(s32*, s32);

void func_890000A4(s32* arg0, s32 arg1, s32 arg2) {
    s32 i;
    s32 var_s3;
    s32 var_v0;
    s32* temp_s4;
    u8 sp3C[2];
    u8* var_s2;
    u8* temp_v1;

    temp_s4 = (s32*)arg0[0];
    temp_v1 = (u8*)temp_s4[0];
    i = 0;

    if (temp_s4[2] > 0) {
        var_s2 = temp_v1;
        do {
            if (arg1 == var_s2[0]) {
                arg2 += var_s2[1];
                func_800275E4(arg0[0], i);
                if (i < arg0[2]) {
                    arg0[2]--;
                }
            } else {
                i++;
                var_s2 += 2;
            }
        } while (i < temp_s4[2]);
    }

    sp3C[0] = arg1;
    var_s3 = arg0[2];

    while (arg2 > 0) {
        if (arg2 < 0x63) {
            var_v0 = arg2;
        } else {
            var_v0 = 0x63;
        }
        arg2 -= var_v0;
        sp3C[1] = var_v0;
        func_800274E0(temp_s4, sp3C, var_s3++);
    }

    ScrollList_SetCursorKeepOffset(arg0, arg0[2]);
}

/**
 * Takes `arg1` from the selected item's count, removing the entry when nothing is left.
 * Seen in play (2026-11-13) in せいとん > どうぐをいどうする, moving all five ほのおのいし to サトシのパソコン removed the bag
 * row (006/020 to 005/020, PC 000/050 to 001/050).
 */
void LabItem_DecreaseSelectedCount(ScrollList* arg0, s32 arg1) {
    u8* temp_v1 = &arg0->items->rows[arg0->items->rowSize * arg0->cursor];

    if (arg1 >= temp_v1[1]) {
        LabList_RemoveSelectedEntry(arg0);
        return;
    }
    temp_v1[1] -= arg1;
}

void func_8900020C(void) {
}

/** Returns how many more items a box can hold. */
s32 LabItem_ComputeRemainingCapacity(s32 arg0, ByteMatrix* arg1) {
    s32 i;
    s32 var_v1 = 0;
    u8* var_v0 = arg1->rows;

    for (i = 0; i < arg1->count; i++, var_v0 += 2) {
        if (arg0 == var_v0[0]) {
            var_v1 = (var_v1 - var_v0[1]) + 0x63;
        }
    }

    return var_v1;
}

/** Returns the largest quantity of an item that can be transferred. */
s32 LabItem_ComputeMaxTransferQuantity(s32 arg0, ByteMatrix* arg1) {
    s32 var_v1;

    if (LabItem_IsQuantitylessItemForOperation(arg0) != 0) {
        if (arg1->count < arg1->capacity) {
            var_v1 = 1;
        } else {
            var_v1 = 0;
        }
    } else if (arg1->count < arg1->capacity) {
        var_v1 = 0x63;
    } else {
        var_v1 = LabItem_ComputeRemainingCapacity(arg0, arg1);
    }
    return var_v1;
}

/** Finds the item box slot for a Game Pak box, allocating one if needed. */
s32 LabItem_FindOrAllocateGamePakBoxSlot(LabItemSaveSlot* arg0, s32 arg1, char* arg2) {
    s32 i;

    for (i = 0; i < 4; i++) {
        if ((arg0[i].present != 0) && (arg1 == arg0[i].trainerId) && (HAL_Strcmp(arg0[i].trainerName, arg2) == 0)) {
            return i;
        }
    }

    for (i = 0; i < 4; i++) {
        if (arg0[i].present == 0) {
            return i;
        }
    }

    return -1;
}

/** Loads the item box slots for the Game Pak boxes. */
void LabItem_LoadGamePakBoxSlots(LabItemSaveSlot* arg0) {
    s32 i;

    for (i = 0; i < 4; i++) {
        arg0[i].present = Deck_IsSaveEntryPresent(0x12, i);
        if (arg0[i].present != 0) {
            arg0[i].trainerId = Deck_GetSaveEntryTrainerId(0x12, i) & 0xFFFF;
            Deck_GetSaveEntryName(0x12, i, arg0[i].trainerName);
        }
    }
}

/** Reads item entries from a deck. */
void LabItem_ReadDeckEntries(s32 arg0, s32 arg1, s32 arg2, ByteMatrix* arg3) {
    DeckHandle* sp1C = Deck_Open(arg0, arg1, arg2, 0);

    arg3->count = Deck_ReadEntries(arg3->rows, arg3->capacity, sp1C);
    Deck_CloseAndFlush(sp1C);
}

/** Writes item entries back to a deck. */
void LabItem_WriteDeckBack(s32 arg0, s32 arg1, s32 arg2, ByteMatrix* arg3, s32 arg4, char* arg5, s32 arg6) {
    DeckHandle* sp2C;

    if (arg6 != -1) {
        if (1) {}  // karodo
        sp2C = Deck_OpenAndSetName(arg0, arg1, arg2, arg4, arg5, arg6);
    } else {
        sp2C = Deck_Open(arg0, arg1, arg2, 1);
    }

    Deck_WriteEntries(arg3->rows, arg3->count, sp2C);

    if ((arg0 == 0x10) || (arg0 == 0x11) || (arg0 == 0x12) || (arg0 == 0x13)) {
        Deck_CloseAndFlushBox(sp2C);
    } else {
        Deck_CloseAndFlush(sp2C);
    }
}

M2C_UNK Ui_DrawTintedScreenBackground(M2C_UNK, M2C_UNK, u8, u8, s32); /* extern */
extern M2C_UNK D_8900A5B8;

/**
 * Draws the tinted terminal screen background.
 * Seen in play (2026-11-12): the せいとん background.
 */
void LabItem_DrawBackground(void) {
    Ui_DrawTintedScreenBackground(0x38, 0x1E0, M2C_FIELD(&D_8900A5B8, u8 *, 0), M2C_FIELD(&D_8900A5B8, u8 *, 1), (s32) M2C_FIELD(&D_8900A5B8, u8 *, 2));
}

void Window_SetRect(s8*, s32, s32, s32, s32);
void Window_InitLabeled(s8*, s32, s32, s32, Color_RGBA8, char*);
void func_8000B2F4(s32);
extern Color_RGBA8 D_8900A5C0;
extern char D_89018460[];
extern char D_89018468[];
extern s32 D_800603C0;
/**
 * Sets up the confirm window (268x146) with message `arg3` and labeled Yes/No buttons.
 * Not reached in play (2026-11-13): did not run in a tour of the main menu, Pokédex, party, Lab,
 * registration, Free Battle setup and a COM battle (opening, a switch, running, a Pound turn).
 * @unverified Name and comment guessed from the code.
 */
void LabItem_InitConfirmWindow(LabItemConfirmWindow* arg0, s32 arg1, s32 arg2, char *arg3, s32 arg4) {
    Window_SetRect(arg0, arg1, arg2, 0x10C, 0x92);
    arg0->window.animTimer = 0;
    arg0->window.state = 0;
    arg0->window.frame.style = 0x2801;
    arg0->window.title = arg3;
    Window_InitLabeled(&arg0->yesButton, arg0->window.frame.x + 0x2E, arg0->window.frame.y + 0x6E, 0x48, D_8900A5C0, D_89018460);
    arg0->yesButton.labelX = 0xA;
    arg0->yesButton.unk_34 = 0xC;
    Window_InitLabeled(&arg0->noButton, arg0->window.frame.x + 0x96, arg0->window.frame.y + 0x6E, 0x48, D_8900A5C0, D_89018468);
    arg0->choice.count = 2;
    arg0->choice.cursor = 0;
    arg0->choice.controller = (Controller*)D_800603C0;
    func_8000B2F4(D_800603C0);
    arg0->text = arg4;
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
 * Draws the confirm window: divider, message and buttons.
 * Not reached in play (2026-11-13): did not run in a tour of the main menu, Pokédex, party, Lab,
 * registration, Free Battle setup and a COM battle (opening, a switch, running, a Pound turn).
 * @unverified Name and comment guessed from the code.
 */
void LabItem_DrawConfirmWindow(LabItemConfirmWindow* arg0) {
    if (func_8002AE6C() == 0) {
        Ui_DrawTexturedDivider(arg0->window.frame.x, arg0->window.frame.y + 0x61, arg0->window.frame.width, D_8007356C);
        Ui_FillRectPrimEnvColor(arg0->window.frame.x + 6, arg0->window.frame.y + 6, arg0->window.frame.width - 0xC, 0x5C, D_8900A5C4, D_8900A5C8);
        gSPDisplayList(gDisplayListHead++, D_80060270);
        func_80029028(arg0->window.frame.x + 6, arg0->window.frame.y + 0x68, arg0->window.frame.width - 0xC, 0x24, D_8900A5CC);
        func_8001AB6C();
        if (!arg0) { // FAKE: empty test only changes register allocation; needed to match
        }
        func_8001AA9C(D_800734A8[0], D_800734A8[1], D_800734A8[2], D_800734A8[3]);
        func_8001A384(8, 0);
        Font_SetLineHeight(0x1C);
        func_8001A944(arg0->window.frame.x + 0xE, arg0->window.frame.y + 0xA, arg0->text);
        func_8001ABBC();
        Window_DrawLabeled(&arg0->yesButton, (arg0->choice.cursor == 0) ? 2 : 0);
        Window_DrawLabeled(&arg0->noButton, (arg0->choice.cursor == 1) ? 2 : 0);
    }
}

s32 func_8002B390(s8*);
s32 func_8002BC14(s32);
extern s32 D_800603C0;

/**
 * Handles input on the confirm window while it is open.
 * Not reached in play (2026-11-13): did not run in a tour of the main menu, Pokédex, party, Lab,
 * registration, Free Battle setup and a COM battle (opening, a switch, running, a Pound turn).
 * @unverified Name and comment guessed from the code.
 */
s32 LabItem_UpdateConfirmWindow(LabItemConfirmWindow* arg0) {
    s32 ret = 0;

    switch (arg0->window.state) {
        case 1:
        case 2:
            break;
        default:
            return 0;
    }
    if (func_8002B390(&arg0->choice) == 0) {
        ret = func_8002BC14(D_800603C0);
        if (ret == 1) {
            switch (arg0->choice.cursor) {
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
void LabItem_InitCountSelector(LabItemCountSelector* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    Window_SetRect(&arg0->window, arg1, arg2, 0x54, 0x34);
    arg0->window.animTimer = 0;
    arg0->window.title = 0;
    arg0->window.state = 0;
    arg0->window.frame.style = 0;
    *(Color_RGBA8*)&arg0->window.frame.color = D_8900A5BC; // copied as an aligned word
    arg0->count.digitCount = 2;
    arg0->count.value = 1;
    arg0->count.min = 1;
    arg0->count.max = arg3;
    arg0->count.digit = 0;
    func_8000B2F4(D_800603C0);
    arg0->limit = arg4;
    arg0->state = 0;
}

void func_8001B884(s32, s32, s32, s32, u8*, s32, s32);
void func_8001AA60(s32, s32, s32);
void Font_SetColorForFlags(s32);
void Ui_DrawRoundedFrame(s32, s32, s32, s32, Color_RGBA8);
void TextBox_Draw(s8*);
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
void LabItem_DrawCountSelector(LabItemCountSelector* arg0) {
    UNUSED s32 pad[1]; // FAKE: stack padding
    s32 x;
    s32 v;

    if (func_8002AE6C(&arg0->window) == 0) {
        x = arg0->window.frame.x - arg0->count.digit * 0x16 + 0x36;
        gSPDisplayList(gDisplayListHead++, D_80073408);
        if (((u16*)D_800603C0)[3] & 0x800) {
            v = (s32)D_04002340;
        } else {
            v = (s32)D_04002130;
        }
        func_8001B884(x + 3, arg0->window.frame.y + 6, 0xE, 8, (u8*)v, 0x10, 0x200000);
        if (((u16*)D_800603C0)[3] & 0x400) {
            v = (s32)D_04002448;
        } else {
            v = (s32)D_04002238;
        }
        func_8001B884(x + 3, arg0->window.frame.y + 0x26, 0xE, 8, (u8*)v, 0x10, 0x200000);
        gSPDisplayList(gDisplayListHead++, D_80073438);
        Ui_DrawRoundedFrame(x - 3, arg0->window.frame.y + 0xD, 0x1A, 0x1A, D_80073520);
        Font_BeginTranslucentTextRendering();
        Font_SetActive(8, 0);
        Gfx_SetEnvColor(D_800734A8[0], D_800734A8[1], D_800734A8[2],
                      D_800734A8[3]);
        func_8001A944(arg0->window.frame.x + 0xA, arg0->window.frame.y + 0x10, D_89018470);
        if (arg0->count.digit == 1) {
            v = 2;
        } else {
            v = 0;
        }
        Font_SetColorForFlags(v);
        func_8001AA60(arg0->window.frame.x + 0x20, arg0->window.frame.y + 0x10, arg0->count.value / 10 + '0');
        if (arg0->count.digit == 0) {
            v = 2;
        } else {
            v = 0;
        }
        Font_SetColorForFlags(v);
        func_8001AA60(arg0->window.frame.x + 0x36, arg0->window.frame.y + 0x10, arg0->count.value % 10 + '0');
        Font_EndTexturedTextRendering();
        if (arg0->state == 1) {
            TextBox_Draw(arg0->textBox);
        }
    }
}

s32 func_8002B638(s8 *);                          /* extern */
s32 func_8002BC14(s32);                             /* extern */
M2C_UNK TextBox_Init(s8 *, M2C_UNK *, M2C_UNK, M2C_UNK, s32); /* extern */
s32 Ui_CheckConfirmPressed(s8 *);                          /* extern */
M2C_UNK func_8003F6AC(M2C_UNK);                     /* extern */
extern s32 D_800603C0;
extern M2C_UNK D_89018474;

/**
 * Handles the count selector input; shows どうぐがいっぱいです (the items are full) when needed.
 * Seen in play (2026-11-13) in せいとん > どうぐをいどうする, the D-pad changed the ほのおのいし count and A moved
 * that many to サトシのパソコン.
 */
s32 LabItem_UpdateCountSelector(LabItemCountSelector* arg0) {
    s32 sp2C;
    s32 temp_v0;
    s32 temp_v0_2;

    sp2C = 0;
    temp_v0 = arg0->state;
    switch (temp_v0) {                              /* irregular */
    case 0:
        if (func_8002B638(&arg0->count) == 0) {
            temp_v0_2 = func_8002BC14(D_800603C0);
            if (temp_v0_2 == -1) {
                func_8003F6AC(3);
                sp2C = -1;
            } else if (temp_v0_2 == 1) {
                if (arg0->limit < arg0->count.value) {
                    func_8003F6AC(8);
                    TextBox_Init(arg0->textBox, &D_89018474, 0, 1, 0);
                    arg0->state = 1;
                } else {
                    func_8003F6AC(2);
                    sp2C = 1;
                }
            }
        }
        break;
    case 1:
        if (Ui_CheckConfirmPressed(arg0->textBox) == 1) {
            arg0->state = 0;
            arg0->count.value = (s32) arg0->limit;
        }
        break;
    }
    return sp2C;
}

/**
 * Sets flag 0x100 (empty) on the rows of the box picker whose item table has no rows.
 */
void func_89000CF0(LabItemMenuWindow* arg0, ByteMatrix* arg1) {
    s32 var_v0;
    u16* temp_a1;
    ByteMatrix* var_v1;
    u16** new_var; // FAKE: permuter temp

    var_v0 = 0;
    new_var = &arg0->menu.itemFlags;
    var_v1 = arg1;
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
void LabItem_DisableRow(LabItemMenuWindow* arg0, s32 arg1) {
    u16 *temp_v0;

    temp_v0 = &arg0->menu.itemFlags[arg1];
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
void LabItem_InitMenuWindow(LabItemMenuWindow* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 pad[2]; // FAKE: stack padding

    Window_SetRect((s8*)&arg0->window, arg1, arg2, 0xE4, (arg4 * 0x1C) + 0x14);
    arg0->window.state = 0;
    arg0->window.title = NULL;
    arg0->window.animTimer = 0;
    arg0->window.frame.style = 0;
    *(Color_RGBA8*)&arg0->window.frame.color = D_8900A5BC;
    func_80027804((s8*)&arg0->items, arg3, arg4, arg4);
    Menu_Init((s8*)&arg0->menu, (s32)&arg0->items, (s32)arg0->itemFlags, (s32)LabItem_DrawMenuRow, 0xD8, 0x1C);
    arg0->menu.cursor = arg5;
    arg0->menu.options |= 0x10000;
}

s32 func_8002AE6C();                                /* extern */
M2C_UNK Menu_DrawItems(s8 *, s32, s32, M2C_UNK, s32); /* extern */

/**
 * Draws the menu window's items.
 * Seen in play (2026-11-13) drew the three-row source window (てもちの どうぐ, サトシの パソコン, 64の カセット) on the
 * item sort screen.
 */
void LabItem_DrawMenu(LabItemMenuWindow* arg0) {
    if (func_8002AE6C() == 0) {
        Menu_DrawItems((s8*)&arg0->menu, arg0->window.frame.x + 6, arg0->window.frame.y + 0xA, 0xFFEF, 0);
    }
}

s32 Menu_UpdateCursorSkipDisabled(void*);
/**
 * Moves the menu cursor. Returns -1 on cancel, the 1-based row on confirm, otherwise 0.
 * Seen in play (2026-11-13) ran every frame while the item sort screen's source window (てもちの どうぐ,
 * サトシの パソコン, 64の カセット) had the cursor.
 */
s32 LabItem_UpdateMenuCursor(LabItemMenuWindow* arg0) {
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
extern Color_RGBA8 D_8900A5E0;
extern Color_RGBA8 D_8900A5E8;
extern Color_RGBA8 D_8900A5EC[];
extern char D_8901848C[];
char* func_8001FDC8(u8, char*);
s32 func_80031C24(u8);
s32 func_80031CC8(u8);
void Font_SetColorForFlags(s32);
/**
 * Draws an item row with its ×%02d count.
 * Seen in play (2026-11-13) (tour of menus and a COM battle): ran in the Lab PC.
 * @unverified Name and comment guessed from the code; ran in play on empty item lists only.
 */
void LabItem_DrawItemCountRow(s32 arg0, s32 arg1, u8* arg2, s32 arg3, s32 arg4) {
    char buf[0x30];

    gSPDisplayList(gDisplayListHead++, D_80060270);
    func_80029028(arg0, arg1 + 1, 0xEC, 0x1A, *(Color_RGBA8*)&D_8900A5E0);
    func_80029028(arg0, arg1, 0xEC, 1, *(Color_RGBA8*)&D_8900A5E8);
    func_80029028(arg0, arg1 + 0x1B, 0xEC, 1, *(Color_RGBA8*)&D_8900A5E8);
    if (arg4 & 0x18) {
        Ui_FillRectHighlighted(arg0 + 3, arg1 + 3, 0xE6, 0x16, D_8900A5BC);
    }
    if (arg2 != NULL) {
        func_8001AB6C();
        func_8001A384(8, 0);
        if (func_80031C24(arg2[0]) != 0) {
            Color_RGBA8 color;

            color = D_8900A5EC[(arg4 & 2) ? 0 : 1];
            func_8001AA9C(color.r, color.g, color.b, color.a);
        } else {
            Font_SetColorForFlags(arg4);
        }
        func_8001A944(arg0 + 8, arg1 + 4, func_8001FDC8(arg2[0], buf));
        if (func_80031CC8(arg2[0]) == 0) {
            func_8001A384(4, 0);
            func_8001A944(arg0 + 0xB4, arg1 + 8, D_8901848C, arg2[1]);
        }
        func_8001ABBC();
    }
}

void func_89001230(LabItemList* arg0, s32 arg1) {
    ScrollList_SetItems((s8*)&arg0->list, arg1, (s8*)arg0->itemFlags);
}

void ScrollList_Init(s8*, s32, s8*, s32, void*, s32, s32);
void LabItem_DrawItemCountRow();

/**
 * Sets up the scrolling item list at (`arg1`, `arg2`) with LabItem_DrawItemCountRow rows.
 * Seen in play (2026-11-12): set up the てもちの どうぐ and サトシのパソコン lists.
 */
void LabItem_InitItemList(LabItemList* arg0, s32 arg1, s32 arg2, s32 arg3) {
    arg0->x = arg1;
    arg0->y = arg2;
    ScrollList_Init((s8*)&arg0->list, arg3, (s8*)arg0->itemFlags, 8, LabItem_DrawItemCountRow, 0xEC, 0x1C);
    arg0->list.options |= 0x10000;
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
void LabItem_DrawItemList(LabItemList* arg0, s32 arg1) {
    if (arg1 & 0x200) {
        func_8002F9D8(&arg0->list, arg0->x, arg0->y + 0x10, arg1 | 0xFFED, 0);
    } else {
        ScrollList_DrawInlineItems(&arg0->list, arg0->x, arg0->y + 0x10, arg1 | 0xFFED, 0);
    }
    Ui_DrawNumberZeroPadded(arg0->x + 0xA8, arg0->y + 0xF2, arg0->list.items->count, 3);
    Ui_DrawNumberZeroPadded(arg0->x + 0xCE, arg0->y + 0xF2, arg0->list.items->capacity, 3);
    gSPDisplayList(gDisplayListHead++, D_80073450);
    gDPSetCombineMode(gDisplayListHead++, G_CC_DECALRGBA, G_CC_DECALRGBA);
    func_8001BCB4(arg0->x + 0xC4, arg0->y + 0xF4, 8, 0xA, D_04011AB8, 8, 0);
}

s32 ScrollList_UpdateCursor(void*);
s32 func_80030230(void*);

/**
 * Navigate the selected menu mode, then report cancel or confirm input.
 * Seen in play (2026-11-13) ran while picking an item and a list in せいとん > どうぐをいどうする and in its
 * swap command (どこのどうぐをいれかえる？).
 * @unverified Name guessed from the code; comment kept.
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

void func_8002B018(s8* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
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
void LabItem_InitOrganizeWindow(LabItemOrganizeWindow* arg0, s32 x, s32 y, ByteMatrix* arg3, s32* arg4, s32* arg5) {
    Window_SetRect(&arg0->window, x, y, 0x234, 0x174);
    arg0->window.animTimer = 0;
    arg0->window.state = 0;
    arg0->window.frame.style = 0x801;
    arg0->window.title = D_890184BC;
    Window_SetRect(&arg0->footerFrame, arg0->window.frame.x + 6, arg0->window.frame.y + 0x136, arg0->window.frame.width - 0xC, 0x38);
    arg0->footerFrame.style = 6;
    arg0->footerFrame.color = D_8900A600;
    arg0->footerFrame.color2 = D_8900A604;
    func_8002B018(&arg0->backButton, x + 0xFF, y + 0x3A, 0x36, 0x2A, 0x30, (s32)D_8900BFC0);
    arg0->backButton.selectedColor = ((Color_RGBA8*)D_8900A580)[0];
    arg0->backButton.color = ((Color_RGBA8*)D_8900A580)[1];
    arg0->backButton.highlightColor = D_8900A5BC;
    func_8002B018(&arg0->moveButton, x + 0xFF, y + 0x74, 0x36, 0x2A, 0x30, (s32)D_8900DAD0);
    arg0->moveButton.selectedColor = ((Color_RGBA8*)D_8900A580)[2];
    arg0->moveButton.color = ((Color_RGBA8*)D_8900A580)[3];
    arg0->moveButton.highlightColor = D_8900A5BC;
    func_8002B018(&arg0->reorderButton, x + 0xFF, y + 0xAE, 0x36, 0x2A, 0x30, (s32)D_8900E858);
    arg0->reorderButton.selectedColor = ((Color_RGBA8*)D_8900A580)[4];
    arg0->reorderButton.color = ((Color_RGBA8*)D_8900A580)[5];
    arg0->reorderButton.highlightColor = D_8900A5BC;
    func_8002B018(&arg0->exchangeButton, x + 0xFF, y + 0xE8, 0x36, 0x2A, 0x30, (s32)D_8900F5E0);
    arg0->exchangeButton.selectedColor = ((Color_RGBA8*)D_8900A580)[6];
    arg0->exchangeButton.color = ((Color_RGBA8*)D_8900A580)[7];
    arg0->exchangeButton.highlightColor = D_8900A5BC;
    arg0->rightBox = 1;
    arg0->leftBox = 0;
    func_800564D4(D_890190F0, D_890184CC, &D_8901911C);
    arg0->boxNames = D_8900A5F4;
    arg0->boxCount = 3;
    arg0->operationCursor.count = 4;
    arg0->operationCursor.cursor = 0;
    arg0->operationCursor.controller = D_800603C0;
    func_8000B2F4(D_800603C0);
    arg0->state = 1;
    arg0->tables = arg3;
    arg0->dirty = arg4;
    arg0->gamePakSlot = arg5;
    LabItem_InitItemList(&arg0->leftList, arg0->window.frame.x + 0xC, arg0->window.frame.y + 0x2A, (s32)&arg3[arg0->leftBox]);
    LabItem_InitItemList(&arg0->rightList, arg0->window.frame.x + 0x13C, arg0->window.frame.y + 0x2A, (s32)&arg3[arg0->rightBox]);
    func_80027410((s8*)&arg0->reorderView, (s8*)arg0->tables->rows, 2, arg0->tables->capacity, 0);
}


extern ColorPair890017FC D_8900A608;
extern ColorPair890017FC D_8900A610;
extern u8* D_89017A80[];
extern u8 D_89017A98[];
extern s32 D_89019114;
extern Gfx D_80073408[];
extern Gfx D_80073438[];
void Gfx_DrawTextureRgba16(s32, s32, s32, s32, u8*, s32, s32);
void Font_SetColorForFlags(s32);
s32 func_8002BC44(s32);

void func_890017FC(LabItemOrganizeWindow* arg0, s32 x, s32 y, s32 flags, s32 icon) {
    ColorPair890017FC* colors;

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
        func_8001A944(x + 0x21, y + 4, arg0->boxNames[icon]);
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
void LabItem_DrawTitleText(s32 arg0, s32 arg1, s32 arg2, s8 *arg3) {
    func_8001AB6C();
    func_8001A384(0x20, 0);
    func_8001AA9C(M2C_FIELD(arg3, u8 *, 0), M2C_FIELD(arg3, u8 *, 1), M2C_FIELD(arg3, u8 *, 2), M2C_FIELD(arg3, u8 *, 3));
    func_8001ABE8();
    func_8001AAE4(M2C_FIELD(arg3, u8 *, 4), M2C_FIELD(arg3, u8 *, 5), M2C_FIELD(arg3, u8 *, 6), M2C_FIELD(arg3, u8 *, 7));
    func_8001A944(((u32) (0x178 - ((func_800566BC(arg2) >> 1) << 5)) >> 1) + arg0, arg1 + 0xC, arg2);
    func_8001AC3C();
    func_8001ABBC();
}

extern u8 D_800734A8[];

/**
 * Draws `arg2` centered in the 376-pixel help area.
 * Seen in play (2026-11-13) ran when the item sort screen's help line changed to 「どこから いどうする?」,
 * which sits centered in the bottom help area.
 */
void LabItem_DrawCenteredText(s32 arg0, s32 arg1, char* arg2) {
    Font_BeginTranslucentTextRendering();
    Font_SetActive(0x10, 0);
    Gfx_SetEnvColor(D_800734A8[0], D_800734A8[1], D_800734A8[2], D_800734A8[3]);
    Font_Printf(((0x178 - (strlen(arg2) / 2) * 0x18) / 2) + arg0, arg1 + 0x10, arg2);
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
 * Draws `arg2` in the small font.
 * Seen in play (2026-11-13) ran while picking an item and a list in せいとん > どうぐをいどうする and in its
 * swap command (どこのどうぐをいれかえる？).
 * @unverified Name and comment guessed from the code.
 */
void LabItem_DrawSmallText(s32 arg0, s32 arg1, s32 arg2) {
    func_8001AB6C();
    func_8001A384(8, 0);
    func_8001AA9C(D_800734A8[0], D_800734A8[1], D_800734A8[2], D_800734A8[3]);
    Font_SetLineHeight(0x1C);
    func_8001A944(arg0 + 8, arg1 + 4, arg2);
    func_8001ABBC();
}

typedef struct List89001B88 {
    /* 0x00 */ u8** data;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 index;
} List89001B88;
extern s32 D_8900A650[];
extern char* D_8900A660[];
extern char* D_8900A66C[];
extern s8* D_8900A678[];
s32 func_80031BC0(u8, char *);
/**
 * Draws the help line for the organize window's current state.
 * Seen in play (2026-11-12): 「どうぐをいどうする」.
 */
void LabItem_DrawHelpText(LabItemOrganizeWindow* arg0) {
    char sp2C[0x54];
    ScrollList* list;

    switch (arg0->state) {
        case 1:
            LabItem_DrawTitleText(arg0->footerFrame.x + 0x58, arg0->footerFrame.y, D_8900A650[arg0->operationCursor.cursor], D_8900A678[arg0->operationCursor.cursor]);
            break;
        case 2:
            LabItem_DrawCenteredText(arg0->footerFrame.x + 0x58, arg0->footerFrame.y, D_8900A660[arg0->operationCursor.cursor]);
            break;
        case 3:
            LabItem_DrawCenteredText(arg0->footerFrame.x + 0x58, arg0->footerFrame.y, D_8900A66C[arg0->operationCursor.cursor]);
            break;
        case 4:
        case 6:
        case 7:
            if (arg0->state == 6) {
                list = &arg0->rightList.list;
            } else {
                list = &arg0->leftList.list;
            }
            LabItem_DrawSmallText(arg0->footerFrame.x + 0x58, arg0->footerFrame.y, func_80031BC0(list->items->rows[list->cursor * 2], sp2C));
            break;
    }
}

void Ui_DrawTexturedFrameDecal(s32, s32, s32, s32, u8*);
extern u8 D_800735C4[];
void func_8002B054(s8*, s32);
void Window_DrawFrame(void*);
void LabItem_DrawItemList(LabItemList* arg0, s32 arg1);
/**
 * Draws the organize items window: frame, lists and help line.
 * Seen in play (2026-11-12): the どうぐのせいり window.
 */
void LabItem_DrawOrganizeWindow(LabItemOrganizeWindow* arg0) {
    s32 v;
    s32 flags;

    if (func_8002AE6C(&arg0->window) == 0) {
        Window_DrawFrame(&arg0->footerFrame);
        gSPDisplayList(gDisplayListHead++, D_80060270);
        func_80029028(arg0->window.frame.x + 6, arg0->window.frame.y + 6, arg0->window.frame.width - 0xC, 6, D_8900A5BC);
        func_80029028(arg0->window.frame.x + 6, arg0->window.frame.y + 0x12A, arg0->window.frame.width - 0xC, 6, D_8900A5BC);
        func_80029028(arg0->window.frame.x + 6, arg0->window.frame.y + 0xC, 6, 0x11E, D_8900A5BC);
        func_80029028(arg0->window.frame.x + arg0->window.frame.width - 0xC, arg0->window.frame.y + 0xC, 6, 0x11E, D_8900A5BC);
        func_80029028(arg0->window.frame.x + 0xF8, arg0->window.frame.y + 0xC, 0x44, 0x11E, D_8900A5BC);
        Ui_DrawTexturedDivider(arg0->window.frame.x, arg0->window.frame.y + 0x12F, arg0->window.frame.width, D_8007356C);
        Ui_DrawTexturedFrameDecal(arg0->window.frame.x + 0xA, arg0->window.frame.y + 0xA, 0xF0, 0x122, D_800735C4);
        Ui_DrawTexturedFrameDecal(arg0->window.frame.x + 0x13A, arg0->window.frame.y + 0xA, 0xF0, 0x122, D_800735C4);
        v = (arg0->state == 1) ? 2 : 0x10;
        func_8002B054(&arg0->backButton, (arg0->operationCursor.cursor == 3) ? v : 0);
        func_8002B054(&arg0->moveButton, (arg0->operationCursor.cursor == 0) ? v : 0);
        func_8002B054(&arg0->reorderButton, (arg0->operationCursor.cursor == 1) ? v : 0);
        func_8002B054(&arg0->exchangeButton, (arg0->operationCursor.cursor == 2) ? v : 0);
        func_890017FC(arg0, arg0->window.frame.x + 0xC, arg0->window.frame.y + 0xC, 0, arg0->leftBox);
        func_890017FC(arg0, arg0->window.frame.x + 0x13C, arg0->window.frame.y + 0xC, 0, arg0->rightBox);
        LabItem_DrawItemList(&arg0->leftList, ((arg0->state == 4) || (arg0->state == 7)) ? 2 : ((arg0->state == 5) || (arg0->state == 6)) ? 0x10 : 0);
        flags = ((arg0->state == 5) || (arg0->state == 6)) ? 2 : 0;
        flags |= (arg0->state == 5) ? 0x200 : 0;
        LabItem_DrawItemList(&arg0->rightList, flags);
        if ((arg0->state == 2) || (arg0->state == 9)) {
            LabItem_DrawMenu(&arg0->sourceBoxWindow);
        }
        if ((arg0->state == 3) || (arg0->state == 0xA)) {
            LabItem_DrawMenu(&arg0->targetBoxWindow);
        }
        LabItem_DrawHelpText(arg0);
        if ((arg0->state == 9) || (arg0->state == 0xA) || (arg0->state == 0xB) || (arg0->state == 0xC)) {
            TextBox_Draw(arg0->textBox);
        }
        if (arg0->state == 8) {
            LabItem_DrawCountSelector(&arg0->countSelector);
        }
    }
}

void func_890020C0(LabItemOrganizeWindow* arg0) {
    u8* item;

    item = arg0->leftList.list.items->rows + arg0->leftList.list.cursor * 2;
    arg0->dirty[arg0->targetBoxWindow.menu.cursor] = 1;
    arg0->dirty[arg0->sourceBoxWindow.menu.cursor] = arg0->dirty[arg0->targetBoxWindow.menu.cursor];
    if (LabItem_IsQuantitylessItemForOperation(item[0]) != 0) {
        func_89000020((LabMonEntryList*)&arg0->rightList, (void*)(arg0->leftList.list.items->rows + arg0->leftList.list.items->rowSize * arg0->leftList.list.cursor));
        LabList_RemoveSelectedEntry(&arg0->leftList.list);
    } else {
        func_890000A4((s32*)&arg0->rightList, item[0], arg0->countSelector.count.value);
        LabItem_SubtractSelectedItemQuantity((unk_func_8820BE14_02C_038*)&arg0->leftList, arg0->countSelector.count.value);
    }
}

void func_80027654(ByteMatrix* matrix, u8* out, s32 row);
void func_80027700(ByteMatrix* matrix, u8* in, s32 row);

void func_8900219C(LabItemOrganizeWindow* arg0) {
    u8 row[4];
    ByteMatrix* matrix;

    func_80027654(arg0->rightList.list.items, row, arg0->rightList.list.cursor);
    matrix = arg0->leftList.list.items;
    func_80027700(arg0->rightList.list.items, matrix->rows + matrix->rowSize * arg0->leftList.list.cursor, arg0->rightList.list.cursor);
    func_80027700(arg0->leftList.list.items, row, arg0->leftList.list.cursor);
    arg0->dirty[arg0->rightBox] = 1;
    arg0->dirty[arg0->leftBox] = arg0->dirty[arg0->rightBox];
}

void func_80027654(ByteMatrix* matrix, u8* out, s32 row);
void func_80027700(ByteMatrix* matrix, u8* in, s32 row);

void func_89002248(LabItemOrganizeWindow* arg0) {
    u8 row[4];
    ByteMatrix* matrix = arg0->leftList.list.items;

    func_80027654(matrix, row, arg0->leftList.list.cursor);
    func_80027700(matrix, matrix->rows + matrix->rowSize * arg0->swapIndex, arg0->leftList.list.cursor);
    func_80027700(matrix, row, arg0->swapIndex);
    arg0->dirty[arg0->leftBox] = 1;
}


void func_890022D0(LabItemOrganizeWindow* arg0) {
    s32 temp_v0;
    LabItemList* temp_a0;

    temp_v0 = arg0->targetBoxWindow.menu.cursor;
    temp_a0 = &arg0->rightList;
    arg0->rightBox = temp_v0;
    func_89001230(temp_a0, (s32)&arg0->tables[temp_v0]);
    arg0->state = 4;
}

s32 func_8002B2B0(void *);
s32 func_89000258(u8, s32);
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
s32 LabItem_UpdateOrganizeWindow(LabItemOrganizeWindow* arg0) {
    s32 ret = 0;
    s32 idx;
    s32 next = 0;
    u8* ptr;
    s32 v;
    u8* ptr2;

    switch (arg0->state) {
        case 1:
            if (func_8002B2B0(&arg0->operationCursor) != 0) {
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
            if (arg0->operationCursor.cursor == 3) {
                func_8003F6AC(3);
                ret = -1;
                break;
            }
            func_8003F6AC(2);
            next = 2;
            if (arg0->operationCursor.cursor != 1) {
                break;
            }
            func_89001230(&arg0->rightList, &arg0->reorderView);
            arg0->rightBox = -1;
            break;

        case 2:
            v = LabItem_UpdateMenuCursor(&arg0->sourceBoxWindow);
            if (v == -1) {
                arg0->state = 1;
                break;
            }
            if (v <= 0) {
                break;
            }
            if (arg0->sourceBoxWindow.menu.itemFlags[arg0->sourceBoxWindow.menu.cursor] & 0x100) {
                arg0->state = 9;
                TextBox_Init(arg0->textBox, (void*)D_8900A688[arg0->operationCursor.cursor], 0, 1, 0);
                func_8003F6AC(8);
                break;
            }
            func_8003F6AC(2);
            idx = arg0->sourceBoxWindow.menu.cursor;
            arg0->leftBox = idx;
            func_89001230(&arg0->leftList, (s32)&arg0->tables[idx]);
            if (arg0->operationCursor.cursor == 1) {
                arg0->state = 4;
                break;
            }
            next = 3;
            break;

        case 3:
            v = LabItem_UpdateMenuCursor(&arg0->targetBoxWindow);
            if (v == -1) {
                next = 2;
                break;
            }
            if (v <= 0) {
                break;
            }
            if (arg0->targetBoxWindow.menu.itemFlags[arg0->targetBoxWindow.menu.cursor] & 0x100) {
                func_8003F6AC(8);
                arg0->state = 10;
                TextBox_Init(arg0->textBox, (void*)D_8900A688[arg0->operationCursor.cursor], 0, 1, 0);
                break;
            }
            func_8003F6AC(2);
            if (arg0->targetBoxWindow.menu.cursor == 2) {
                if (*arg0->gamePakSlot == -1) {
                    ret = 1;
                    break;
                }
            }
            func_890022D0(arg0);
            break;

        case 4:
            v = LabItem_UpdateItemList(&arg0->leftList, 0);
            if (v == -1) {
                arg0->state = 1;
                break;
            }
            if (v != 1) {
                break;
            }
            ptr = arg0->leftList.list.items->rows + arg0->leftList.list.cursor * 2;
            if (arg0->operationCursor.cursor == 0) {
                if (func_80031C24(*ptr) != 0 && arg0->rightBox == 2) {
                    func_8003F6AC(8);
                    TextBox_Init(arg0->textBox, (void*)D_8900A694, 1, 2, 0xC);
                    arg0->state = 11;
                    break;
                }
                v = func_89000258(*ptr, arg0->rightList.list.items);
                if (v == 0) {
                    func_8003F6AC(8);
                    arg0->state = 11;
                    TextBox_Init(arg0->textBox, D_89018648, 0, 1, 0);
                    break;
                }
                func_8003F6AC(2);
                if (func_80031CC8(*ptr) == 0) {
                    LabItem_InitCountSelector(&arg0->countSelector, arg0->leftList.x + 0x98,
                                  arg0->leftList.y + arg0->leftList.list.cursorY - arg0->leftList.list.scrollY + 0x2C,
                                  ptr[1], v);
                    arg0->state = 8;
                } else {
                    arg0->state = 5;
                }
                break;
            }
            if (arg0->operationCursor.cursor == 2) {
                if (func_80031C24(*ptr) != 0 && arg0->rightBox == 2) {
                    func_8003F6AC(8);
                    TextBox_Init(arg0->textBox, (void*)D_8900A694, 1, 2, 0xC);
                    arg0->state = 11;
                    break;
                }
                func_8003F6AC(2);
                arg0->state = 6;
                break;
            }
            func_8003F6AC(2);
            arg0->leftList.list.itemFlags[arg0->leftList.list.cursor] |= 8;
            arg0->swapIndex = arg0->leftList.list.cursor;
            arg0->state = 7;
            break;

        case 8:
            v = LabItem_UpdateCountSelector(&arg0->countSelector);
            if (v == -1) {
                arg0->state = 4;
                break;
            }
            if (v == 1) {
                arg0->state = 5;
            }
            break;

        case 5:
            v = LabItem_UpdateItemList(&arg0->rightList, 0x200);
            if (v == -1) {
                arg0->state = 4;
                break;
            }
            if (v != 1) {
                break;
            }
            func_8003F6AC(0x18);
            func_890020C0(arg0);
            if (arg0->leftList.list.items->count == 0) {
                arg0->state = 1;
                break;
            }
            arg0->state = 4;
            break;

        case 7:
            v = LabItem_UpdateItemList(&arg0->leftList, 0);
            if (v == -1) {
                Menu_ClearItemFlags((Menu*)&arg0->leftList.list);
                arg0->state = 4;
                break;
            }
            if (v != 1) {
                break;
            }
            func_8003F6AC(0x18);
            func_89002248(arg0);
            Menu_ClearItemFlags((Menu*)&arg0->leftList.list);
            arg0->state = 4;
            break;

        case 6:
            v = LabItem_UpdateItemList(&arg0->rightList, 0);
            if (v == -1) {
                arg0->state = 4;
                break;
            }
            if (v != 1) {
                break;
            }
            ptr2 = arg0->rightList.list.items->rows + arg0->rightList.list.cursor * 2;
            if (func_80031C24(*ptr2) != 0 &&
                arg0->leftBox == 2) {
                func_8003F6AC(8);
                TextBox_Init(arg0->textBox, (void*)D_8900A694, 1, 2, 0xC);
                arg0->state = 12;
                break;
            }
            func_8003F6AC(0x18);
            func_8900219C(arg0);
            arg0->state = 4;
            break;

        case 9:
            if (Ui_CheckConfirmPressed(arg0->textBox) == 1) {
                arg0->state = 2;
            }
            break;
        case 10:
            if (Ui_CheckConfirmPressed(arg0->textBox) == 1) {
                arg0->state = 3;
            }
            break;
        case 11:
            if (Ui_CheckConfirmPressed(arg0->textBox) == 1) {
                arg0->state = 4;
            }
            break;
        case 12:
            if (Ui_CheckConfirmPressed(arg0->textBox) == 1) {
                arg0->state = 6;
            }
            break;
    }

    if (next > 0) {
        switch (next) {
            case 2:
                LabItem_InitMenuWindow(&arg0->sourceBoxWindow, arg0->window.frame.x + 0x1F, arg0->window.frame.y + 0x29, (s32)arg0->boxNames,
                              arg0->boxCount, arg0->leftBox);
                func_89000CF0(&arg0->sourceBoxWindow, arg0->tables);
                break;
            case 3:
                LabItem_InitMenuWindow(&arg0->targetBoxWindow, arg0->window.frame.x + 0x14F, arg0->window.frame.y + 0x29, (s32)arg0->boxNames,
                              arg0->boxCount, arg0->rightBox);
                if (arg0->operationCursor.cursor == 2) {
                    func_89000CF0(&arg0->targetBoxWindow, arg0->tables);
                }
                LabItem_DisableRow(&arg0->targetBoxWindow, arg0->leftBox);
                arg0->targetBoxWindow.menu.cursor = 0;
                Menu_SkipDisabledForward(&arg0->targetBoxWindow.menu);
                break;
        }
        arg0->state = next;
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
 * Draws なまえ/%s (Name) and ID No/%05d.
 * Not reached in play (2026-11-13): did not run in a tour of the main menu, Pokédex, party, Lab,
 * registration, Free Battle setup and a COM battle (opening, a switch, running, a Pound turn).
 * @unverified Name and comment guessed from the code.
 */
void LabItem_DrawTrainerInfo(s32 arg0, s32 arg1, LabItemSaveSlot* arg2, s32 arg3, s32 arg4) {
    gSPDisplayList(gDisplayListHead++, D_80060270);
    func_80029028(arg0, arg1 + 1, 0x13C, 0x3C, *(Color_RGBA8*)&D_8900A5BC);
    func_80029028(arg0, arg1, 0x13C, 1, D_8900A698);
    func_80029028(arg0, arg1 + 0x3D, 0x13C, 1, D_8900A698);
    if (arg4 & 0x10) {
        Ui_FillRectHighlighted(arg0 + 3, arg1 + 3, 0x136, 0x38, D_8900A5BC);
    }
    Ui_DrawImageInStrips(D_8900A69C, arg0 + 0xB, arg1 + 0xB);
    Font_BeginTranslucentTextRendering();
    Font_SetColorForFlags(arg4);
    Font_SetActive(0x10, 0);
    Font_Printf(arg0 + 0x53, arg1 + 6, D_89018660, arg2->trainerName);
    Font_SetActive(8, 0);
    Font_Printf(arg0 + 0x58, arg1 + 0x24, D_8901866C, arg2->trainerId);
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
 * Sets up the データをけす (delete data) window.
 * Not reached in play (2026-11-13): did not run in a tour of the main menu, Pokédex, party, Lab,
 * registration, Free Battle setup and a COM battle (opening, a switch, running, a Pound turn).
 * @unverified Name and comment guessed from the code.
 */
void LabItem_InitDeleteDataWindow(LabItemDeleteDataWindow* arg0, s32 arg1, s32 arg2, LabItemSaveSlot* arg3) {
    s32 pad[2]; // FAKE: stack padding
    Window_SetRect((s8*)&arg0->window, arg1, arg2, 0x148, 0x14A);
    arg0->window.animTimer = 0;
    arg0->window.state = 0;
    arg0->window.frame.style = 0x801;
    arg0->window.title = D_89018678;
    Window_SetRect((s8*)&arg0->footerFrame, arg0->window.frame.x + 6, arg0->window.frame.y + 0x104, arg0->window.frame.width - 0xC, 0x40);
    arg0->footerFrame.style = 6;
    arg0->footerFrame.color = D_8900A6AC;
    arg0->footerFrame.color2 = D_8900A6B0;
    func_80027410((s8*)&arg0->slotTable, (s8*)arg3, 0x14, 4, 4);
    Menu_Init((s8*)&arg0->menu, (s32)&arg0->slotTable, (s32)arg0->itemFlags, (s32)LabItem_DrawTrainerInfo, 0x13C, 0x3E);
    arg0->menu.options |= 0x10000;
}

void Ui_DrawTexturedDivider(s32, s32, s32, void*);
void Window_DrawFrame(void*);
void Menu_DrawInlineItems(void*, s32, s32, s32, s32);
extern u8 D_8007356C[];
extern u8 D_89018688[];
/**
 * Draws the delete data window.
 * Not reached in play (2026-11-13): did not run in a tour of the main menu, Pokédex, party, Lab,
 * registration, Free Battle setup and a COM battle (opening, a switch, running, a Pound turn).
 * @unverified Name and comment guessed from the code.
 */
void LabItem_DrawDeleteDataWindow(LabItemDeleteDataWindow* arg0, s32 arg1) {
    if (func_8002AE6C() == 0) {
        Ui_DrawTexturedDivider(arg0->window.frame.x, arg0->footerFrame.y - 7, arg0->window.frame.width, D_8007356C);
        Window_DrawFrame(&arg0->footerFrame);
        Menu_DrawInlineItems(&arg0->menu, arg0->window.frame.x + 6, arg0->window.frame.y + 6, 0xFFEF, 0);
        func_8001AB6C();
        func_8001A384(8, 0);
        if (!arg0) { // FAKE: empty test only changes register allocation; needed to match
        }
        func_8001AA9C(D_800734A8[0], D_800734A8[1], D_800734A8[2], D_800734A8[3]);
        Font_SetLineHeight(0x1C);
        func_8001A944(arg0->footerFrame.x + 8, arg0->footerFrame.y + 8, D_89018688);
        func_8001ABBC();
    }
}

s32 Menu_UpdateCursor(void*);

/**
 * Moves the delete data cursor. Returns -1 on cancel, 1 on confirm.
 * Not reached in play (2026-11-13): did not run in a tour of the main menu, Pokédex, party, Lab,
 * registration, Free Battle setup and a COM battle (opening, a switch, running, a Pound turn).
 * @unverified Name and comment guessed from the code.
 */
s32 LabItem_UpdateDeleteDataCursor(LabItemDeleteDataWindow* arg0) {
    s32 sp1C = 0;
    s32 dir;

    if (Menu_UpdateCursor(&arg0->menu) == 0) {
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

void func_8002B018(s8* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
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

void func_89002E58(LabItemSaveDataWindow* arg0, s32 arg1, s32 arg2, LabItemSaveSlot* arg3, s32 arg4) {
    Window_SetRect(&arg0->window, arg1, arg2, 0x184, 0x180);
    arg0->window.animTimer = 0;
    arg0->window.title = NULL;
    arg0->window.state = 0;
    arg0->window.frame.style = 0x1001;
    Window_SetRect(&arg0->footerFrame, arg0->window.frame.x + 6, arg0->window.frame.y + 0x142,
                  arg0->window.frame.width - 0xC, 0x38);
    arg0->footerFrame.style = 6;
    arg0->footerFrame.color = D_8900A6B4;
    arg0->footerFrame.color2 = D_8900A6B8;
    func_8002B018(&arg0->backButton, arg1 + 0x2B, arg2 + 0x47, 0x36, 0x2A, 0x30, (s32)D_8900BFC0);
    arg0->backButton.selectedColor = *(Color_RGBA8*)D_8900A580;
    arg0->backButton.color = *(Color_RGBA8*)D_8900A584;
    arg0->backButton.highlightColor = D_8900A5BC;
    func_8002B018(&arg0->discardButton, arg1 + 0x2B, arg2 + 0x9F, 0x36, 0x2A, 0x30, (s32)D_890110F0);
    arg0->discardButton.selectedColor = *(Color_RGBA8*)D_8900A5A8;
    arg0->discardButton.color = *(Color_RGBA8*)D_8900A5AC;
    arg0->discardButton.highlightColor = D_8900A5BC;
    func_8002B018(&arg0->viewItemsButton, arg1 + 0x2B, arg2 + 0xF7, 0x36, 0x2A, 0x30, (s32)D_89010368);
    arg0->viewItemsButton.selectedColor = *(Color_RGBA8*)D_8900A5A0;
    arg0->viewItemsButton.color = *(Color_RGBA8*)D_8900A5A4;
    arg0->viewItemsButton.highlightColor = D_8900A5BC;
    arg0->operationCursor.count = 3;
    arg0->operationCursor.cursor = 0;
    arg0->operationCursor.controller = D_800603C0;
    func_8000B2F4(D_800603C0);
    LabItem_InitItemList(&arg0->itemList, arg0->window.frame.x + 0x88, arg0->window.frame.y + 0x36, arg4);
    arg0->slot = arg3;
    arg0->state = 1;
}

typedef Color_RGBA8 Rgba8900A6BC; // size = 0x4
typedef struct Color8900A6BC {
    /* 0x0 */ Rgba8900A6BC c[2];
} Color8900A6BC; // size = 0x8
extern Color8900A6BC D_8900A6BC;
extern Color8900A6BC D_8900A6C4;
extern Gfx D_80073408[];
extern Gfx D_80073438[];
extern u8 D_89017A98[];
extern char D_890186C0[];
extern char D_890186CC[];
void Ui_FillRectPrimEnvColor(s32, s32, s32, s32, Rgba8900A6BC, Rgba8900A6BC);
void Font_SetColorForFlags(s32);
void func_890030C8(s32 arg0, s32 arg1, LabItemSaveSlot* arg2, s32 arg3) {
    Color8900A6BC* color;

    if (arg3 & 2) {
        color = &D_8900A6BC;
    } else {
        color = &D_8900A6C4;
    }
    Ui_FillRectPrimEnvColor(arg0, arg1, 0xEC, 0x2A, color->c[0], color->c[1]);
    gSPDisplayList(gDisplayListHead++, D_80073408);
    Gfx_DrawTextureRgba16(arg0 + 6, arg1 + 8, 0x2E, 0x1A, D_89017A98, 0x30, 0x200000);
    gSPDisplayList(gDisplayListHead++, D_80073438);
    Font_BeginTranslucentTextRendering();
    Font_SetColorForFlags(arg3);
    Font_SetActive(8, 0);
    Font_Printf(arg0 + 0x34, arg1 + 2, D_890186C0, arg2->trainerName);
    Font_SetActive(4, 0);
    Font_Printf(arg0 + 0x38, arg1 + 0x18, D_890186CC, arg2->trainerId);
    Font_EndTexturedTextRendering();
}

extern s32 D_8900A6CC[];
extern s8 *D_8900A6D8[];
void func_8900323C(LabItemSaveDataWindow* arg0) {
    char sp2C[0x54];
    ScrollList* list;

    switch (arg0->state) {
        case 1:
            LabItem_DrawTitleText(arg0->footerFrame.x, arg0->footerFrame.y, D_8900A6CC[arg0->operationCursor.cursor], D_8900A6D8[arg0->operationCursor.cursor]);
            break;
        case 2:
            list = &arg0->itemList.list;
            LabItem_DrawSmallText(arg0->footerFrame.x, arg0->footerFrame.y, func_80031BC0(list->items->rows[list->cursor * 2], sp2C));
            break;
    }
}

void Ui_DrawTexturedFrameDecal(s32, s32, s32, s32, u8*);
extern u8 D_800735C4[];
void func_8002B054(s8*, s32);
void Window_DrawFrame(void*);
void func_890032E4(LabItemSaveDataWindow* arg0) {
    s32 v;

    if (func_8002AE6C(&arg0->window) == 0) {
        Window_DrawFrame(&arg0->footerFrame);
        Ui_DrawTexturedDivider(arg0->window.frame.x, arg0->footerFrame.y - 7, arg0->window.frame.width, D_8007356C);
        gSPDisplayList(gDisplayListHead++, D_80060270);
        func_80029028(arg0->window.frame.x + 6, arg0->window.frame.y + 6, 0x82, 0x136, *(Color_RGBA8*)&D_8900A5BC);
        func_80029028(arg0->window.frame.x + 0x88, arg0->window.frame.y + 6, 0xEC, 6, *(Color_RGBA8*)&D_8900A5BC);
        func_80029028(arg0->window.frame.x + 0x88, arg0->window.frame.y + 0x136, 0xEC, 6, *(Color_RGBA8*)&D_8900A5BC);
        func_80029028(arg0->window.frame.x + 0x174, arg0->window.frame.y + 6, 0xA, 0x136, *(Color_RGBA8*)&D_8900A5BC);
        Ui_DrawTexturedFrameDecal(arg0->window.frame.x + 0x86, arg0->window.frame.y + 0xA, 0xF0, 0x12E, D_800735C4);
        v = (arg0->state == 1) ? 2 : 0x10;
        func_8002B054(&arg0->backButton, (arg0->operationCursor.cursor == 2) ? v : 0);
        func_8002B054(&arg0->discardButton, (arg0->operationCursor.cursor == 0) ? v : 0);
        func_8002B054(&arg0->viewItemsButton, (arg0->operationCursor.cursor == 1) ? v : 0);
        func_890030C8(arg0->window.frame.x + 0x88, arg0->window.frame.y + 0xC, arg0->slot, 0);
        LabItem_DrawItemList(&arg0->itemList, (arg0->state == 2) ? 2 : 0);
        func_8900323C(arg0);
    }
}

s32 func_8002B2B0(void *);
s32 LabItem_UpdateItemList(void *, u32);
s32 func_8900352C(LabItemSaveDataWindow* arg0) {
    s32 ret = 0;

    switch (arg0->state) {
        case 1:
            if (func_8002B2B0(&arg0->operationCursor) == 0) {
                s32 r = func_8002BC14(D_800603C0);
                if (r == -1) {
                        func_8003F6AC(3);
                        ret = -1;
                } else if (r == 1) {
                        switch (arg0->operationCursor.cursor) {
                            case 1:
                                func_8003F6AC(2);
                                arg0->state = 2;
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
            if (LabItem_UpdateItemList(&arg0->itemList, 0) == -1) {
                arg0->state = 1;
            }
            break;
    }
    return ret;
}

extern s32 D_89019108;
extern s32 D_89019118;
extern s32 D_8901911C;

void func_89003650(LabItemScreen* arg0) {
    s32 i;

    func_80027410((s8*)&arg0->itemTables[0], (s8*)arg0->bagItemRows, 2, 0x14, 0);
    func_80027410((s8*)&arg0->itemTables[1], (s8*)arg0->pcItemRows, 2, 0x32, 0);
    func_80027410((s8*)&arg0->itemTables[2], (s8*)arg0->gamePakItemRows, 2, 0x64, 0);
    LabItem_ReadDeckEntries(0x23, D_89019108, 0, &arg0->itemTables[0]);
    LabItem_ReadDeckEntries(0x22, D_89019108, 0, &arg0->itemTables[1]);
    LabItem_LoadGamePakBoxSlots(arg0->saveSlots);
    arg0->gamePakSlot = LabItem_FindOrAllocateGamePakBoxSlot(arg0->saveSlots, D_89019118, (char*)&D_8901911C);
    if ((arg0->gamePakSlot != -1) && (arg0->saveSlots[arg0->gamePakSlot].present != 0)) {
        LabItem_ReadDeckEntries(0x12, 0, arg0->gamePakSlot, &arg0->itemTables[2]);
    }
    i = 0;
    do {
        arg0->dirty[i] = 0;
        i++;
    } while (i != 3);
    LabItem_InitOrganizeWindow(&arg0->organizeWindow, 0x26, 0x51, arg0->itemTables, arg0->dirty, &arg0->gamePakSlot);
    arg0->state = 1;
}
