/* Stadium Zero resident code. */

#include "global.h"
#include "m2c_macros.h"

/**
 * Paged grid menu fields used by ScrollGrid_DrawCursor, Menu_DrawCursor,
 * ScrollList_DrawCursor and the other grid/list menu helpers. Offsets other than the ones
 * named here are unknown/unused by this function.
 */
typedef struct GridMenu80031004 {
    /* 0x00 */ char unk00[0x8];
    /* 0x08 */ s32 cursor;
    /* 0x0C */ s32 cellWidth;
    /* 0x10 */ s32 cellHeight;
    /* 0x14 */ char unk14[0x16];
    /* 0x2A */ u16 flags;
    /* 0x2C */ s32 scroll;
    /* 0x30 */ char unk30[0x4];
    /* 0x34 */ s32 scrollTarget;
    /* 0x38 */ char unk38[0x10];
    /* 0x48 */ s32 columns;
} GridMenu80031004;

typedef struct MenuDef8002E230 {
    /* 0x00 */ u8* items;
    /* 0x04 */ s32 count;
    /* 0x08 */ s32 itemCount;
    /* 0x0C */ s32 itemSize;
} MenuDef8002E230;
typedef void (*MenuDrawFunc8002E230)(s32, s32, u8*, s32, s32, s32);
typedef struct Menu8002E230 {
    /* 0x00 */ MenuDef8002E230* def;
    /* 0x04 */ u16* flags;
    /* 0x08 */ s32 cursor;
    /* 0x0C */ s32 colSpacing;
    /* 0x10 */ s32 rowSpacing;
    /* 0x14 */ MenuDrawFunc8002E230 draw;
    /* 0x18 */ char unk18[0x8];
    /* 0x20 */ s32 options;
    /* 0x24 */ s32 columns;
} Menu8002E230;

typedef struct ScrollMenu8002F6C4 {
    /* 0x00 */ MenuDef8002E230* def;
    /* 0x04 */ u16* flags;
    /* 0x08 */ s32 cursor;
    /* 0x0C */ s32 width;
    /* 0x10 */ s32 rowSpacing;
    /* 0x14 */ MenuDrawFunc8002E230 draw;
    /* 0x18 */ char unk18[0x8];
    /* 0x20 */ s32 options;
    /* 0x24 */ s32 rows;
    /* 0x28 */ s32 unk28;
    /* 0x2C */ s32 scroll;
} ScrollMenu8002F6C4;

typedef struct GridMenu800310D8 {
    /* 0x00 */ MenuDef8002E230* def;
    /* 0x04 */ u16* flags;
    /* 0x08 */ s32 cursor;
    /* 0x0C */ s32 cellWidth;
    /* 0x10 */ s32 cellHeight;
    /* 0x14 */ MenuDrawFunc8002E230 draw;
    /* 0x18 */ char unk18[0x8];
    /* 0x20 */ s32 options;
    /* 0x24 */ s32 rows;
    /* 0x28 */ char unk28[0x4];
    /* 0x2C */ s32 scroll;
    /* 0x30 */ char unk30[0x18];
    /* 0x48 */ s32 columns;
} GridMenu800310D8;
void ScrollList_AnimateScroll(ScrollMenu8002F6C4*);
void ScrollList_DrawScrollArrows(ScrollMenu8002F6C4*, s32, s32, s32, s32);
void ScrollList_DrawCursor(GridMenu80031004*, s32, s32);

extern u8 D_80073520[];
M2C_UNK Ui_DrawRoundedFrame(s32, s32, s32, s32, Color_RGBA8);

void Menu_SetItems(s8* arg0, s32 arg1, s32 arg2);
extern s32 D_800603C0;
M2C_UNK func_8000B2F4(s32);

/**
 * Initializes a menu: stores its layout arguments, sets the position through Menu_SetItems, the 0xC00 repeat delay and the controller.
 * @unverified Name and comment guessed from the code.
 */
void Menu_Init(s8* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    M2C_FIELD(arg0, s32*, 0xC) = arg4;
    M2C_FIELD(arg0, s32*, 0x10) = arg5;
    M2C_FIELD(arg0, s32*, 0x14) = arg3;
    Menu_SetItems(arg0, arg1, arg2);
    M2C_FIELD(arg0, s32*, 0x1C) = 0xC00;
    M2C_FIELD(arg0, s32*, 0x20) = 0;
    func_8000B2F4(M2C_FIELD(arg0, s32*, 0x18) = D_800603C0);
}

void Menu_ClearItemFlags(u8* arg0);

/**
 * Points the menu at item table `arg1` with flags `arg2`, puts the cursor on the first item and clears the item flags.
 * @unverified Name and comment guessed from the code.
 */
void Menu_SetItems(s8 *arg0, s32 arg1, s32 arg2) {
    M2C_FIELD(arg0, s32 *, 0) = arg1;
    M2C_FIELD(arg0, s32 *, 4) = arg2;
    M2C_FIELD(arg0, s32 *, 8) = 0;
    Menu_ClearItemFlags((u8*)arg0);
}

/**
 * Clears the flags of every item.
 * @unverified Name and comment guessed from the code.
 */
void Menu_ClearItemFlags(u8* arg0) {
    s32 i;

    for (i = 0; i < M2C_FIELD(M2C_FIELD(arg0, u8**, 0), s32*, 4); i++) {
        M2C_FIELD(arg0, s16**, 4)[i] = 0;
    }
}

/**
 * Draws the cursor rectangle (via Ui_DrawRoundedFrame) for a list menu with one cell per row:
 * x = arg1 + 2, y = cursor * cellHeight + arg2 + 2, size = (cellWidth - 4) x (cellHeight - 4),
 * colour read from D_80073520. Compare ScrollList_DrawCursor and ScrollGrid_DrawCursor. The separate `y`
 * local only fixes the order in which the fields are loaded.
 * @unverified Name guessed from the code; comment kept.
 */
void Menu_DrawCursor(GridMenu80031004* arg0, s32 arg1, s32 arg2) {
    s32 y;

    y = arg0->cursor * arg0->cellHeight + arg2 + 2;
    Ui_DrawRoundedFrame(arg1 + 2, y, arg0->cellWidth - 4, arg0->cellHeight - 4, *(Color_RGBA8*)D_80073520);
}

/**
 * Draws a menu's items from its definition, one row per item.
 * @unverified Name and comment guessed from the code.
 */
void Menu_DrawItems(Menu8002E230* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 i;
    s32 y = arg2;
    s32 count = arg0->def->itemCount;
    u8** items = (u8**)arg0->def->items;
    s32 flags;

    for (i = 0; i < count; i++) {
        flags = arg0->flags[i];
        if (i == arg0->cursor) {
            flags |= 0x12;
        }
        arg0->draw(arg1, y, items[i], i, flags & arg3, arg4);
        y += arg0->rowSpacing;
    }
    if (arg0->def->itemCount > 0 && (arg3 & 2) && (arg0->options & 0x10000)) {
        Menu_DrawCursor((GridMenu80031004*)arg0, arg1, arg2);
    }
}

/**
 * Like Menu_DrawItems, for item tables that store `itemSize`-byte items inline instead of pointers.
 * @unverified Name and comment guessed from the code.
 */
void Menu_DrawInlineItems(Menu8002E230* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 i;
    s32 y = arg2;
    MenuDef8002E230* def = arg0->def;
    s32 count = def->itemCount;
    u8* items = def->items;
    s32 flags;

    for (i = 0; i < count; i++) {
        flags = arg0->flags[i];
        if (i == arg0->cursor) {
            flags |= 0x12;
        }
        arg0->draw(arg1, y, items + def->itemSize * i, i, flags & arg3, arg4);
        y += arg0->rowSpacing;
    }
    if (arg0->def->itemCount > 0 && (arg3 & 2) && (arg0->options & 0x10000)) {
        Menu_DrawCursor((GridMenu80031004*)arg0, arg1, arg2);
    }
}

s32 func_8000B30C();
s32 func_8003F6AC();
/**
 * Moves a menu's cursor from controller input. Returns 0 when the menu has no items.
 * @unverified Name and comment guessed from the code.
 */
s32 Menu_UpdateCursor(Menu8002E230* arg0) {
    s32 input;
    s32 old = arg0->cursor;

    if (arg0->def->itemCount == 0) {
        return 0;
    }
    if (arg0) { // FAKE: no-op test; changes register allocation to match
    }
    input = (u16)func_8000B30C();
    switch (input) {
        case 0x800:
            if (arg0->cursor == 0) {
                arg0->cursor += arg0->def->itemCount;
            }
            arg0->cursor--;
            break;
        case 0x400:
            if (arg0->cursor >= arg0->def->itemCount - 1) {
                arg0->cursor -= arg0->def->itemCount;
            }
            arg0->cursor++;
            break;
    }
    if (old != arg0->cursor) {
        func_8003F6AC(1);
    }
    return input;
}

/**
 * Moves the cursor up or down with wraparound, skipping disabled items (flag 1).
 * @unverified Name and comment guessed from the code.
 */
s32 Menu_UpdateCursorSkipDisabled(Menu8002E230* arg0) {
    s32 input;
    s32 old = arg0->cursor;

    if (arg0->def->itemCount == 0) {
        return 0;
    }
    if (arg0) {}  // karodo
    input = (u16)func_8000B30C();
    switch (input) {
        case 0x800:
            do {
                if (arg0->cursor == 0) {
                    arg0->cursor += arg0->def->itemCount;
                }
                arg0->cursor--;
            } while (arg0->flags[arg0->cursor] & 1);
            break;
        case 0x400:
            do {
                if (arg0->cursor == arg0->def->itemCount - 1) {
                    arg0->cursor -= arg0->def->itemCount;
                }
                arg0->cursor++;
            } while (arg0->flags[arg0->cursor] & 1);
            break;
    }
    if (old != arg0->cursor) {
        func_8003F6AC(1);
    }
    return input;
}

/**
 * Moves the cursor forward past disabled items (flag 1).
 * @unverified Name and comment guessed from the code.
 */
s32 Menu_SkipDisabledForward(Menu8002E230* arg0) {
    s32 i;

    for (i = arg0->cursor; i < arg0->def->itemCount && (arg0->flags[i] & 1); i++) {
    }
    if (i < arg0->def->itemCount) {
        arg0->cursor = i;
        return i;
    }
    for (i = arg0->cursor - 1; i >= 0 && (arg0->flags[i] & 1); i--) {
    }
    if (i >= 0) {
        arg0->cursor = i;
        return i;
    }
    return -1;
}

void GridMenu_SetItems(s8*, s32, s32);
extern s32 D_800603C0;
M2C_UNK func_8000B2F4(s32);

/**
 * Initialises a menu object at arg0: stores arg4, arg5, arg6 and arg3 at
 * offsets 0x24, 0x0C, 0x10 and 0x14, calls GridMenu_SetItems(arg0, arg1, arg2),
 * sets offset 0x1C to 0xC00 and offset 0x20 to 0, then stores D_800603C0 at
 * offset 0x18 and passes it to func_8000B2F4. What the fields mean is not
 * established.
 * @unverified Name guessed from the code; comment kept.
 */
void GridMenu_Init(s8* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    M2C_FIELD(arg0, s32*, 0x24) = arg4;
    M2C_FIELD(arg0, s32*, 0xC) = arg5;
    M2C_FIELD(arg0, s32*, 0x10) = arg6;
    M2C_FIELD(arg0, s32*, 0x14) = arg3;
    GridMenu_SetItems(arg0, arg1, arg2);
    M2C_FIELD(arg0, s32*, 0x1C) = 0xC00;
    M2C_FIELD(arg0, s32*, 0x20) = 0;
    func_8000B2F4(M2C_FIELD(arg0, s32*, 0x18) = D_800603C0);
}

void GridMenu_ClearItemFlags(u8* arg0);

/**
 * Points the grid menu at item table `arg1` with flags `arg2`, puts the cursor on the first item and clears the item flags.
 * @unverified Name and comment guessed from the code.
 */
void GridMenu_SetItems(s8 *arg0, s32 arg1, s32 arg2) {
    M2C_FIELD(arg0, s32 *, 0) = arg1;
    M2C_FIELD(arg0, s32 *, 4) = arg2;
    M2C_FIELD(arg0, s32 *, 8) = 0;
    GridMenu_ClearItemFlags((u8*)arg0);
}

/**
 * Clears the flags of every item.
 * @unverified Name and comment guessed from the code.
 */
void GridMenu_ClearItemFlags(u8* arg0) {
    s32 i;

    for (i = 0; i < M2C_FIELD(M2C_FIELD(arg0, u8**, 0), s32*, 4); i++) {
        M2C_FIELD(arg0, s16**, 4)[i] = 0;
    }
}

/**
 * Draws the cursor rectangle (via Ui_DrawRoundedFrame) for a multi-column menu: the cursor cell is
 * at column cursor % columns, row cursor / columns, so x = column * colSpacing + arg_x + 2 and
 * y = row * rowSpacing + arg_y + 2; the size is (colSpacing - 4) x (rowSpacing - 4) and the
 * colour is read from D_80073520. Compare ScrollGrid_DrawCursor. The `px`/`py` locals only fix the
 * evaluation order of the argument expressions.
 * @unverified Name guessed from the code; comment kept.
 */
void GridMenu_DrawCursor(Menu8002E230* menu, s32 x, s32 y) {
    s32 px;
    s32 py;

    px = (menu->cursor % menu->columns) * menu->colSpacing + x + 2;
    py = (menu->cursor / menu->columns) * menu->rowSpacing + y + 2;
    Ui_DrawRoundedFrame(px, py, menu->colSpacing - 4, menu->rowSpacing - 4, *(Color_RGBA8*)D_80073520);
}

/**
 * Draws every cell of the grid; items are pointers.
 * @unverified Name and comment guessed from the code.
 */
void GridMenu_DrawItems(Menu8002E230* menu, s32 x, s32 y, s32 mask, s32 arg4) {
    MenuDef8002E230* def = menu->def;
    s32 i;
    u8** items = (u8**)def->items;
    u8* item;
    s32 f;

    for (i = 0; i < def->count; i++) {
        item = (i < def->itemCount) ? items[i] : NULL;
        f = menu->flags[i];
        if (i == menu->cursor) {
            f |= 0x12;
        }
        menu->draw((i % menu->columns) * menu->colSpacing + x, (i / menu->columns) * menu->rowSpacing + y, item, i, f & mask, arg4);
    }
    if ((menu->def->itemCount > 0) && (mask & 2) && (menu->options & 0x10000)) {
        GridMenu_DrawCursor(menu, x, y);
    }
}

void GridMenu_DrawCursor(Menu8002E230*, s32, s32);
/**
 * Draws every cell of the grid; items are stored inline.
 * @unverified Name and comment guessed from the code.
 */
void GridMenu_DrawInlineItems(Menu8002E230* menu, s32 x, s32 y, s32 mask, s32 arg4) {
    MenuDef8002E230* def = menu->def;
    s32 i;
    u8* items = def->items;
    u8* item;
    s32 f;

    for (i = 0; i < def->count; i++) {
        item = (i < def->itemCount) ? items + def->itemSize * i : NULL;
        f = menu->flags[i];
        if (i == menu->cursor) {
            f |= 0x12;
        }
        menu->draw(x + (i % menu->columns) * menu->colSpacing, y + (i / menu->columns) * menu->rowSpacing, item, i, f & mask, arg4);
    }
    if ((menu->def->itemCount > 0) && (mask & 2) && (menu->options & 0x10000)) {
        GridMenu_DrawCursor(menu, x, y);
    }
}

/**
 * Moves the grid cursor with the D-Pad, wrapping around rows and columns.
 * @unverified Name and comment guessed from the code.
 */
s32 GridMenu_UpdateCursor(Menu8002E230* arg0) {
    s32 input;
    s32 old = arg0->cursor;

    if (arg0->def->itemCount == 0) {
        return 0;
    }
    if (arg0 && arg0) { // FAKE: no-op test; changes register allocation to match
    }
    input = (u16)func_8000B30C();
    switch (input) {
        case 0x800:
            arg0->cursor -= arg0->columns;
            if (arg0->cursor < 0) {
                arg0->cursor += ((arg0->def->itemCount - 1) / arg0->columns + 1) * arg0->columns;
                if (arg0->cursor > arg0->def->itemCount - 1) {
                    arg0->cursor = arg0->def->itemCount - 1;
                }
            }
            break;
        case 0x400:
            arg0->cursor += arg0->columns;
            if ((arg0->def->itemCount - 1) / arg0->columns < arg0->cursor / arg0->columns) {
                arg0->cursor = arg0->cursor % arg0->columns;
            } else if (arg0->cursor > arg0->def->itemCount - 1) {
                arg0->cursor = arg0->def->itemCount - 1;
            }
            break;
        case 0x200:
            if (arg0->cursor % arg0->columns == 0) {
                arg0->cursor += arg0->columns;
            }
            arg0->cursor--;
            if (arg0->cursor > arg0->def->itemCount - 1) {
                arg0->cursor = arg0->def->itemCount - 1;
            }
            break;
        case 0x100:
            if (arg0->cursor % arg0->columns + 1 == arg0->columns) {
                arg0->cursor -= arg0->columns;
            }
            arg0->cursor++;
            if (arg0->cursor >= arg0->def->itemCount) {
                arg0->cursor -= arg0->cursor % arg0->columns;
            }
            break;
    }
    if (old != arg0->cursor) {
        func_8003F6AC(1);
    }
    return input;
}

/**
 * Moves the grid cursor with the D-Pad, skipping disabled cells (flag 1).
 * Seen in play (2026-11-12): on the main menu with no GB cartridge (only バトル and OFF enabled),
 * D-Down moved the cursor from バトル to OFF, D-Left left it on OFF (G B, to its left, is disabled),
 * and D-Up moved it back to バトル.
 */
s32 GridMenu_UpdateCursorSkipDisabled(Menu8002E230* menu) {
    s32 button;
    s32 prev = menu->cursor;
    s32 found = 0;
    s32 row_start;
    s32 i;
    s32 end;

    if (menu->def->itemCount == 0) {
        return 0;
    }
    button = (u16)func_8000B30C();
    switch (button) {
        case 0x800:
            do {
                menu->cursor -= menu->columns;
                if (menu->cursor < 0) {
                    menu->cursor += ((menu->def->itemCount - 1) / menu->columns + 1) * menu->columns;
                }
                row_start = menu->cursor - menu->cursor % menu->columns;
                for (i = menu->cursor; i >= row_start; i--) {
                    if (i <= menu->def->itemCount - 1 && !(menu->flags[i] & 1)) {
                        menu->cursor = i;
                        found = 1;
                        break;
                    }
                }
                if (!found) {
                    end = menu->columns + row_start - 1;
                    if (end >= menu->def->itemCount - 1) {
                        end = menu->def->itemCount - 1;
                    }
                    for (i = menu->cursor + 1; i <= end; i++) {
                        if (!(menu->flags[i] & 1)) {
                            menu->cursor = i;
                            found = 1;
                            break;
                        }
                    }
                }
            } while (!found);
            break;
        case 0x400:
            do {
                menu->cursor += menu->columns;
                if ((menu->def->itemCount - 1) / menu->columns < menu->cursor / menu->columns) {
                    menu->cursor %= menu->columns;
                }
                row_start = menu->cursor - menu->cursor % menu->columns;
                for (i = menu->cursor; i >= row_start; i--) {
                    if (i <= menu->def->itemCount - 1 && !(menu->flags[i] & 1)) {
                        menu->cursor = i;
                        found = 1;
                        break;
                    }
                }
                if (!found) {
                    end = menu->columns + row_start - 1;
                    if (end >= menu->def->itemCount - 1) {
                        end = menu->def->itemCount - 1;
                    }
                    for (i = menu->cursor + 1; i <= end; i++) {
                        if (!(menu->flags[i] & 1)) {
                            menu->cursor = i;
                            found = 1;
                            break;
                        }
                    }
                }
            } while (!found);
            break;
        case 0x200:
            do {
                if (menu->cursor % menu->columns == 0) {
                    menu->cursor += menu->columns;
                }
                menu->cursor--;
            } while (menu->cursor >= menu->def->itemCount || (menu->flags[menu->cursor] & 1));
            break;
        case 0x100:
            do {
                if (menu->cursor % menu->columns + 1 == menu->columns) {
                    menu->cursor -= menu->columns;
                }
                menu->cursor++;
            } while (menu->cursor >= menu->def->itemCount || (menu->flags[menu->cursor] & 1));
            break;
    }
    if (prev != menu->cursor) {
        func_8003F6AC(1);
        if (button) {} // karodo
    }
    return button;
}

void ScrollList_SetItems(s8* arg0, s32 arg1, s32 arg2);
extern s32 D_800603C0;
/**
 * Initializes a scrolling list: stores its layout arguments, the position, the 0xC00 repeat delay, the controller and the scroll bar geometry.
 * @unverified Name and comment guessed from the code.
 */
void ScrollList_Init(s8* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    M2C_FIELD(arg0, s32*, 0x24) = arg3;
    M2C_FIELD(arg0, s32*, 0x0C) = arg5;
    M2C_FIELD(arg0, s32*, 0x10) = arg6;
    M2C_FIELD(arg0, s32*, 0x14) = arg4;
    ScrollList_SetItems(arg0, arg1, arg2);
    M2C_FIELD(arg0, s32*, 0x1C) = 0xC00;
    M2C_FIELD(arg0, s32*, 0x20) = 0x100000;
    M2C_FIELD(arg0, s32*, 0x18) = D_800603C0;
    M2C_FIELD(arg0, u16*, 0x28) = M2C_FIELD(arg0, u16*, 0x2A) = 0;
    M2C_FIELD(arg0, s32*, 0x2C) = 0;
    M2C_FIELD(arg0, s32*, 0x34) = 0;
    M2C_FIELD(arg0, s32*, 0x38) = (M2C_FIELD(arg0, s32*, 0x10) * 4) / 10;
    M2C_FIELD(arg0, s32*, 0x3C) = (M2C_FIELD(arg0, s32*, 0x24) * M2C_FIELD(arg0, s32*, 0x10) * 2) / 10;
    M2C_FIELD(arg0, s32*, 0x40) = 8;
}

void Menu_ClearItemFlags(u8* arg0);

/**
 * Points the list at item table `arg1` with flags `arg2` and resets the cursor and scroll.
 * @unverified Name and comment guessed from the code.
 */
void ScrollList_SetItems(s8 *arg0, s32 arg1, s32 arg2) {
    M2C_FIELD(arg0, s32 *, 0) = arg1;
    M2C_FIELD(arg0, s32 *, 4) = arg2;
    M2C_FIELD(arg0, s32 *, 8) = 0;
    M2C_FIELD(arg0, s32 *, 0x34) = 0;
    M2C_FIELD(arg0, s32 *, 0x2C) = 0;
    M2C_FIELD(arg0, s32 *, 0x30) = 0;
    M2C_FIELD(arg0, s32 *, 0x40) = 0;
    Menu_ClearItemFlags((u8*)arg0);
}

/**
 * Scrolls up when the cursor row is above the visible area.
 * @unverified Name and comment guessed from the code.
 */
void ScrollList_ScrollUpToCursor(s8 *arg0) {
    s32 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s32 *, 0x34);
    if (temp_v0 < M2C_FIELD(arg0, s32 *, 0x2C)) {
        M2C_FIELD(arg0, s32 *, 0x2C) = temp_v0;
    }
}

// FAKE: decomp slop. Raw pointer-offset casts stand in for struct fields.
/**
 * Scrolls down when the cursor row is below the visible area.
 * @unverified Name and comment guessed from the code.
 */
void ScrollList_ScrollDownToCursor(s8 *arg0)
{
  s32 *new_var3; // FAKE: permuter temp
  s32 *new_var2; // FAKE: permuter temp
  int temp_v0;
  s8 *new_var; // FAKE: permuter temp
  s32 *new_var4; // FAKE: permuter temp
  new_var = (s8 *) arg0;
  new_var4 = (s32 *) (new_var + 0x34);
  new_var3 = &(*new_var4);
  temp_v0 = ((*(new_var2 = new_var3)) - ((*((s32 *) (((s8 *) arg0) + 0x24))) * (*((s32 *) (((s8 *) arg0) + 0x10))))) + 1; // FAKE: decomp slop, raw pointer casts stand in for struct fields
  if ((*((s32 *) (((s8 *) arg0) + 0x2C))) < temp_v0)
  {
    *((s32 *) (new_var + 0x2C)) = temp_v0;
  }
}

// FAKE: permuter output. Raw offset casts stand in for menu fields 0x28-0x3C.
/**
 * Moves the drawn scroll position toward the target a step at a time.
 * @unverified Name and comment guessed from the code.
 */
void ScrollList_AnimateScroll(ScrollMenu8002F6C4 *menu)
{
  s32 t1;
  s32 t3;
  s32 t2;
  s32 *new_var; // FAKE
  s32 speed;
  s32 cur;
  if ((*((u16 *) (((s8 *) menu) + 0x2A))) & 0x800)
  {
    if (!((*((u16 *) (((s8 *) menu) + 0x28))) & 0x800))
    {
      speed = *((s32 *) (((s8 *) menu) + 0x38));
      t1 = menu->cursor * menu->rowSpacing;
      cur = *((s32 *) (((s8 *) menu) + 0x34));
      *((s32 *) (((s8 *) menu) + 0x34)) = cur - (((cur - t1) < speed) ? (cur - t1) : (speed));
      if (1) {} // karodo
      if (1) {} // karodo
      if (1) {} // karodo
      ScrollList_ScrollUpToCursor((s8 *) menu);
      if (t1 == (*((s32 *) (((s8 *) menu) + 0x34))))
      {
        *((u16 *) (((s8 *) menu) + 0x2A)) &= ~0x800;
      }
    }
  }
  else
    if ((*((u16 *) (((s8 *) menu) + 0x2A))) & 0x400)
  {
    if (!((*((u16 *) (((s8 *) menu) + 0x28))) & 0x400))
    {
      t2 = ((menu->cursor + 1) * menu->rowSpacing) - 1;
      speed = *((s32 *) (((s8 *) menu) + 0x38));
      *((s32 *) (((s8 *) menu) + 0x34)) += ((t2 - (*((s32 *) (((s8 *) menu) + 0x34)))) < speed) ? (t2 - (*((s32 *) (((s8 *) menu) + 0x34)))) : (speed); // FAKE: decomp slop, raw pointer casts stand in for struct fields
      ScrollList_ScrollDownToCursor((s8 *) menu);
      if (t2 == (*((s32 *) (((s8 *) menu) + 0x34))))
      {
        *((u16 *) (((s8 *) menu) + 0x2A)) &= ~0x400;
        new_var = (s32 *) (((s8 *) menu) + 0x34);
        *new_var = ((*((s32 *) (((s8 *) menu) + 0x34))) - menu->rowSpacing) + 1;
      }
    }
  }
  else
  {
    if ((*((u16 *) (((s8 *) menu) + 0x2A))) & 0x200)
    {
      if (!((*((u16 *) (((s8 *) menu) + 0x28))) & 0x200))
      {
        t1 = menu->scroll;
        t3 = *((s32 *) (((s8 *) menu) + 0x30));
        t1 = ((t1 - t3) < (*((s32 *) (((s8 *) menu) + 0x3C)))) ? (t1 - t3) : (*((s32 *) (((s8 *) menu) + 0x3C))); // FAKE: decomp slop, raw pointer casts stand in for struct fields
        menu->scroll -= t1;
        if (1) {} // karodo
        *((s32 *) (((s8 *) menu) + 0x34)) -= t1;
        menu->cursor = (*((s32 *) (((s8 *) menu) + 0x34))) / menu->rowSpacing;
        if ((t3 & 0xFFFFFFFFu) == menu->scroll) // FAKE: no-op mask fixes bnel operand order
        {
          *((u16 *) (((s8 *) menu) + 0x2A)) &= ~0x200;
        }
      }
    }
    else
      if ((*((u16 *) (((s8 *) menu) + 0x2A))) & 0x100)
    {
      if (!((*((u16 *) (((s8 *) menu) + 0x28))) & 0x100))
      {
        t3 = *((s32 *) (((s8 *) menu) + 0x30));
        t1 = ((t3 - menu->scroll) < (*((s32 *) (((s8 *) menu) + 0x3C)))) ? (t3 - menu->scroll) : (*((s32 *) (((s8 *) menu) + 0x3C))); // FAKE: decomp slop, raw pointer casts stand in for struct fields
        menu->scroll += t1;
        if (1) {} // karodo
        *((s32 *) (((s8 *) menu) + 0x34)) += t1;
        menu->cursor = (*((s32 *) (((s8 *) menu) + 0x34))) / menu->rowSpacing;
        if ((t3 & 0xFFFFFFFFu) == menu->scroll) // FAKE: no-op mask fixes bnel operand order
        {
          *((u16 *) (((s8 *) menu) + 0x2A)) &= ~0x100;
        }
      }
    }
  }
  *((u16 *) (((s8 *) menu) + 0x28)) = 0;
}

extern u8 D_04003A50[];
extern u8 D_04003AD8[];
extern u8 D_040044F8[];
extern u8 D_04003FE8[];
extern u8 D_04004A08[];
extern u8 D_04003D60[];
extern u8 D_04004780[];
extern u8 D_04004270[];
extern u8 D_04004C90[];
extern Gfx D_80073408[];
extern Gfx D_80073438[];
void func_8001C22C(s32, s32, s32, s32, u8*, s32, s32);
void func_8001B884(s32, s32, s32, s32, u8*, s32, s32);
/**
 * Draws the up and down arrows when there are rows above or below the visible area.
 * @unverified Name and comment guessed from the code.
 */
void ScrollList_DrawScrollArrows(ScrollMenu8002F6C4* menu, s32 x, s32 topY, s32 bottomY, s32 width) {
    s32 height = menu->rowSpacing * menu->rows;
    s32 arrowX;
    s32 more;

    arrowX = menu->width / 2 + x - 9;
    gDPPipeSync(gDisplayListHead++);
    gDPSetCycleType(gDisplayListHead++, G_CYC_1CYCLE);
    gDPSetRenderMode(gDisplayListHead++, 0x0F0A4000, 0);
    gDPSetCombineMode(gDisplayListHead++, G_CC_DECALRGBA, G_CC_DECALRGBA);
    gDPSetTexturePersp(gDisplayListHead++, G_TP_NONE);
    gDPSetTextureFilter(gDisplayListHead++, G_TF_POINT);
    func_8001C22C(x, topY, width, 0x10, D_04003A50, 8, 0);
    func_8001C22C(x, bottomY, width, 0x10, D_04003A50, 8, 0);
    gSPDisplayList(gDisplayListHead++, D_80073408);
    func_8001B884(arrowX, topY, 0x12, 0x10, (menu->scroll > 0) ? D_04003AD8 : D_040044F8, 0x14, 0x200000);
    func_8001B884(arrowX - 0x1C, topY, 0x14, 0x10, (menu->scroll > 0) ? D_04003FE8 : D_04004A08, 0x14, 0x200000);
    more = menu->scroll + height < menu->rowSpacing * menu->def->itemCount;
    func_8001B884(arrowX, bottomY, 0x12, 0x10, more ? D_04003D60 : D_04004780, 0x14, 0x200000);
    func_8001B884(arrowX + 0x1A, bottomY, 0x14, 0x10, more ? D_04004270 : D_04004C90, 0x14, 0x200000);
    gSPDisplayList(gDisplayListHead++, D_80073438);
}

/**
 * Draws the cursor rectangle (via Ui_DrawRoundedFrame) for a scrolling list menu. Same shape as
 * ScrollGrid_DrawCursor but with x = arg1 + 2 (no column calculation) and the rectangle size taken from
 * cellWidth/cellHeight minus 4: y = scrollTarget + arg2 - scroll + 2, and when flag 0x400 is
 * set, (cellHeight - 1) is subtracted from it. The colour argument is read from D_80073520.
 * Matching note: the redundant (s32) cast on arg2 only fixes the operand order of the addu.
 * @unverified Name guessed from the code; comment kept.
 */
void ScrollList_DrawCursor(GridMenu80031004* arg0, s32 arg1, s32 arg2) {
    s32 sp2C;

    sp2C = (s32)arg2 + arg0->scrollTarget - arg0->scroll + 2;
    if (arg0->flags & 0x400) {
        sp2C = sp2C - arg0->cellHeight + 1;
    }
    Ui_DrawRoundedFrame(arg1 + 2, sp2C, arg0->cellWidth - 4, arg0->cellHeight - 4, *(Color_RGBA8*)D_80073520);
}

/**
 * Draws a scrolling list menu whose entries are an array of words (def->items[i], passed to the
 * draw callback by value as the entry argument) rather than fixed-size records -- compare
 * ScrollList_DrawInlineItems, which indexes records by def->itemSize. Sets the scissor rectangle to the
 * menu area (x, y, width x rows * rowSpacing), calls ScrollList_AnimateScroll, then draws every visible
 * row i (from scroll / rowSpacing) through menu->draw(x, rowY, entry, i, flags & mask, arg4),
 * where the flags halfword for row i comes from menu->flags and is OR'd with 0x12 for the
 * cursor row; rows at or past def->itemCount get entry 0 and flags 0. Afterwards the scissor
 * is restored to the full 640x480 screen, ScrollList_DrawScrollArrows draws when option bit 0x100000 is set
 * and ScrollList_DrawCursor (cursor box) draws when mask bit 2, option bit 0x10000 and a non-empty
 * list agree.
 * @unverified Name guessed from the code; comment kept.
 */
void ScrollList_DrawItems(ScrollMenu8002F6C4* menu, s32 x, s32 y, s32 mask, s32 arg4) {
    s32 height = menu->rowSpacing * menu->rows;
    s32 i;
    s32 rowY;
    s32 end;
    s32 item;
    s32 f;
    s32* items = (s32*)menu->def->items;

    gDPPipeSync(gDisplayListHead++);
    gDPSetScissor(gDisplayListHead++, G_SC_NON_INTERLACE, x, y, menu->width + x, y + height);
    ScrollList_AnimateScroll(menu);
    rowY = y - menu->scroll % menu->rowSpacing;
    i = menu->scroll / menu->rowSpacing;
    end = (menu->scroll + height - 1) / menu->rowSpacing + 1;
    for (; i < end; i++) {
        item = 0;
        f = 0;
        if (i < menu->def->itemCount) {
            item = items[i];
            f = menu->flags[i];
            if (i == menu->cursor) {
                f |= 0x12;
            }
        }
        menu->draw(x, rowY, (u8*)item, i, f & mask, arg4);
        rowY += menu->rowSpacing;
    }
    gDPPipeSync(gDisplayListHead++);
    gDPSetScissor(gDisplayListHead++, G_SC_NON_INTERLACE, 0, 0, 640, 480);
    if (menu->options & 0x100000) {
        ScrollList_DrawScrollArrows(menu, x, y - 16, y + menu->rowSpacing * menu->rows, menu->width);
    }
    if ((menu->def->itemCount > 0) && (mask & 2) && (menu->options & 0x10000)) {
        ScrollList_DrawCursor((GridMenu80031004*)menu, x, y);
    }
}

/**
 * Draws the visible rows inside a scissor box; items are stored inline.
 * @unverified Name and comment guessed from the code.
 */
void ScrollList_DrawInlineItems(ScrollMenu8002F6C4* menu, s32 x, s32 y, s32 mask, s32 arg4) {
    MenuDef8002E230* def = menu->def;
    u8* items = def->items;
    s32 height = menu->rowSpacing * menu->rows;
    s32 i;
    s32 rowY;
    s32 end;
    u8* item;
    s32 f;

    gDPPipeSync(gDisplayListHead++);
    gDPSetScissor(gDisplayListHead++, G_SC_NON_INTERLACE, x, y, menu->width + x, y + height);
    ScrollList_AnimateScroll(menu);
    rowY = y - menu->scroll % menu->rowSpacing;
    i = menu->scroll / menu->rowSpacing;
    end = (menu->scroll + height - 1) / menu->rowSpacing + 1;
    for (; i < end; i++) {
        item = NULL;
        f = 0;
        if (i < menu->def->itemCount) {
            item = items + def->itemSize * i;
            f = menu->flags[i];
            if (i == menu->cursor) {
                f |= 0x12;
            }
        }
        menu->draw(x, rowY, item, i, f & mask, arg4);
        rowY += menu->rowSpacing;
    }
    gDPPipeSync(gDisplayListHead++);
    gDPSetScissor(gDisplayListHead++, G_SC_NON_INTERLACE, 0, 0, 640, 480);
    if (menu->options & 0x100000) {
        ScrollList_DrawScrollArrows(menu, x, y - 16, y + menu->rowSpacing * menu->rows, menu->width);
    }
    if ((menu->def->itemCount > 0) && (mask & 2) && (menu->options & 0x10000)) {
        ScrollList_DrawCursor(menu, x, y);
    }
}

void func_8002F9D8(ScrollMenu8002F6C4* menu, s32 x, s32 y, s32 mask, s32 arg4) {
    MenuDef8002E230* def = menu->def;
    u8* items = def->items;
    s32 pad[2]; // FAKE: stack padding
    s32 height = menu->rowSpacing * menu->rows;
    s32 i;
    s32 rowY;
    s32 end;
    u8* item;
    s32 f;

    gDPPipeSync(gDisplayListHead++);
    gDPSetScissor(gDisplayListHead++, G_SC_NON_INTERLACE, x, y, menu->width + x, y + height);
    ScrollList_AnimateScroll(menu);
    i = menu->scroll / menu->rowSpacing;
    rowY = y - menu->scroll % menu->rowSpacing + (menu->cursor - i) * menu->rowSpacing;
    menu->draw(x, rowY, NULL, i, 0, arg4);
    rowY = y - menu->scroll % menu->rowSpacing;
    end = (menu->scroll + height - 1) / menu->rowSpacing;
    for (; i < end; i++) {
        item = NULL;
        f = 0;
        if (i < menu->def->itemCount) {
            item = items + def->itemSize * i;
            f = menu->flags[i];
            if (i == menu->cursor) {
                f |= 0x12;
            }
        }
        menu->draw(x, ((i >= menu->cursor) ? menu->rowSpacing : 0) + rowY, item, i, f & mask, arg4);
        rowY += menu->rowSpacing;
    }
    gDPPipeSync(gDisplayListHead++);
    gDPSetScissor(gDisplayListHead++, G_SC_NON_INTERLACE, 0, 0, 640, 480);
    if (menu->options & 0x100000) {
        menu->def->itemCount++;
        ScrollList_DrawScrollArrows(menu, x, y - 16, y + menu->rowSpacing * menu->rows, menu->width);
        menu->def->itemCount--;
    }
    if ((mask & 2) && (menu->options & 0x10000)) {
        ScrollList_DrawCursor(menu, x, y);
    }
}

typedef struct ScrollList8002FD8C {
    /* 0x00 */ MenuDef8002E230* def;
    /* 0x04 */ u16* itemFlags;
    /* 0x08 */ s32 cursor;
    /* 0x0C */ s32 width;
    /* 0x10 */ s32 rowSpacing;
    /* 0x14 */ char unk14[0x4];
    /* 0x18 */ u16* input;
    /* 0x1C */ char unk1C[0x8];
    /* 0x24 */ s32 rows;
    /* 0x28 */ u16 buttons;
    /* 0x2A */ u16 flags;
    /* 0x2C */ s32 scroll;
    /* 0x30 */ s32 top;
    /* 0x34 */ s32 scrollTarget;
    /* 0x38 */ s32 scrollSpeed;
    /* 0x3C */ s32 pageSpeed;
    /* 0x40 */ s32 repeatTimer;
} ScrollList8002FD8C;

/**
 * Moves a scrolling list's cursor and scroll position from controller input.
 * Seen in play (2026-11-12) in いちらん: while it ran, D-Down moved the row cursor from フシギダネ to
 * ヒトカゲ, then to ゼニガメ, where it stayed on the last row.
 */
u16 ScrollList_UpdateCursor(ScrollList8002FD8C* menu) {
    s32 prev_top;
    s32 prev;
    s32 room;
    s32 total;
    s32 page;
    s32 step;
    s32 delta;
    s32 end;

    prev = menu->cursor;
    prev_top = menu->top;
    if (menu->def->itemCount == 0) {
        return 0;
    }
    // Each pair of stores stays on one line: the assembler orders them differently when they are on separate lines.
    if (menu->input[4] & 0x800) {
        menu->repeatTimer = 8; menu->buttons = 0x800;
    } else if (menu->input[4] & 0x400) {
        menu->repeatTimer = 8; menu->buttons = 0x400;
    } else if (menu->input[4] & 0x200) {
        menu->repeatTimer = 8; menu->buttons = 0x200;
    } else if (menu->input[4] & 0x100) {
        menu->repeatTimer = 8; menu->buttons = 0x100;
    } else if (menu->repeatTimer > 0) {
        menu->repeatTimer--;
    } else {
        menu->buttons = menu->input[3];
    }

    if ((menu->buttons & 0x800) && !(menu->flags & ~0x800)) {
        menu->flags |= 0x800;
        menu->scrollTarget -= (menu->scrollTarget < menu->scrollSpeed) ? menu->scrollTarget : menu->scrollSpeed;
        ScrollList_ScrollUpToCursor((s8*)menu);
        menu->cursor = menu->scrollTarget / menu->rowSpacing;
        if (prev != menu->cursor) {
            func_8003F6AC(1);
        }
    } else if ((menu->buttons & 0x400) && !(menu->flags & ~0x400)) {
        if (menu->flags == 0) {
            menu->scrollTarget = menu->scrollTarget + menu->rowSpacing - 1;
        }
        menu->flags |= 0x400;
        end = menu->rowSpacing * menu->def->itemCount;
        menu->scrollTarget += ((end - menu->scrollTarget - 1) < menu->scrollSpeed) ? (end - menu->scrollTarget - 1) : menu->scrollSpeed;
        ScrollList_ScrollDownToCursor((s8*)menu);
        menu->cursor = menu->scrollTarget / menu->rowSpacing;
        if (prev != menu->cursor) {
            func_8003F6AC(1);
        }
    } else if ((menu->buttons & 0x200) && !(menu->flags & ~0x200)) {
        page = menu->rowSpacing * menu->rows;
        if (menu->flags == 0) {
            menu->top = menu->scroll;
        }
        menu->flags |= 0x200;
        if (menu->scroll < menu->pageSpeed) {
            delta = menu->scroll;
        } else {
            delta = menu->pageSpeed;
        }
        menu->scroll -= delta;
        menu->scrollTarget -= delta;
        menu->cursor = menu->scrollTarget / menu->rowSpacing;
        if (menu->scroll < menu->top) {
            menu->top -= (page < menu->top) ? page : menu->top;
        }
        if (prev_top != menu->top) {
            func_8003F6AC(1);
        }
    } else if ((menu->buttons & 0x100) && !(menu->flags & ~0x100)) {
        total = menu->rowSpacing * menu->def->itemCount;
        page = menu->rowSpacing * menu->rows;
        if (menu->flags == 0) {
            menu->top = menu->scroll;
        }
        menu->flags |= 0x100;
        room = total - menu->scroll - page;
        if (room <= 0) {
            room = 0;
        }
        step = (room < menu->pageSpeed) ? room : menu->pageSpeed;
        menu->scroll += step;
        menu->scrollTarget += step;
        menu->cursor = menu->scrollTarget / menu->rowSpacing;
        if (menu->top < menu->scroll) {
            room = total - page - menu->top;
            menu->top += (page < room) ? page : room;
        }
        if (prev_top != menu->top) {
            func_8003F6AC(1);
        }
    }
    return menu->flags;
}

u16 func_80030230(ScrollList8002FD8C* menu) {
    s32 prev_top;
    s32 prev;
    s32 room;
    s32 total;
    s32 page;
    s32 step;
    s32 delta;
    s32 end;

    prev = menu->cursor;
    prev_top = menu->top;
    if (menu->def->itemCount == 0) {
        return 0;
    }
    // Each pair of stores stays on one line: the assembler orders them differently when they are on separate lines.
    if (menu->input[4] & 0x800) {
        menu->repeatTimer = 8; menu->buttons = 0x800;
    } else if (menu->input[4] & 0x400) {
        menu->repeatTimer = 8; menu->buttons = 0x400;
    } else if (menu->input[4] & 0x200) {
        menu->repeatTimer = 8; menu->buttons = 0x200;
    } else if (menu->input[4] & 0x100) {
        menu->repeatTimer = 8; menu->buttons = 0x100;
    } else if (menu->repeatTimer > 0) {
        menu->repeatTimer--;
    } else {
        menu->buttons = menu->input[3];
    }

    if ((menu->buttons & 0x800) && !(menu->flags & ~0x800)) {
        menu->flags |= 0x800;
        menu->scrollTarget -= (menu->scrollTarget < menu->scrollSpeed) ? menu->scrollTarget : menu->scrollSpeed;
        ScrollList_ScrollUpToCursor((s8*)menu);
        menu->cursor = menu->scrollTarget / menu->rowSpacing;
        if (prev != menu->cursor) {
            func_8003F6AC(1);
        }
    } else if ((menu->buttons & 0x400) && !(menu->flags & ~0x400)) {
        if (menu->flags == 0) {
            menu->scrollTarget = menu->scrollTarget + menu->rowSpacing - 1;
        }
        menu->flags |= 0x400;
        end = menu->rowSpacing * (menu->def->itemCount + 1);
        menu->scrollTarget += ((end - menu->scrollTarget - 1) < menu->scrollSpeed) ? (end - menu->scrollTarget - 1) : menu->scrollSpeed;
        ScrollList_ScrollDownToCursor((s8*)menu);
        menu->cursor = menu->scrollTarget / menu->rowSpacing;
        if (prev != menu->cursor) {
            func_8003F6AC(1);
        }
    } else if ((menu->buttons & 0x200) && !(menu->flags & ~0x200)) {
        page = menu->rowSpacing * menu->rows;
        if (menu->flags == 0) {
            menu->top = menu->scroll;
        }
        menu->flags |= 0x200;
        if (menu->scroll < menu->pageSpeed) {
            delta = menu->scroll;
        } else {
            delta = menu->pageSpeed;
        }
        menu->scroll -= delta;
        menu->scrollTarget -= delta;
        menu->cursor = menu->scrollTarget / menu->rowSpacing;
        if (menu->scroll < menu->top) {
            menu->top -= (page < menu->top) ? page : menu->top;
        }
        if (prev_top != menu->top) {
            func_8003F6AC(1);
        }
    } else if ((menu->buttons & 0x100) && !(menu->flags & ~0x100)) {
        total = menu->rowSpacing * menu->def->itemCount;
        page = menu->rowSpacing * menu->rows;
        if (menu->flags == 0) {
            menu->top = menu->scroll;
        }
        menu->flags |= 0x100;
        room = total - menu->scroll - page;
        if (room <= 0) {
            room = 0;
        }
        step = (room < menu->pageSpeed) ? room : menu->pageSpeed;
        menu->scroll += step;
        menu->scrollTarget += step;
        menu->cursor = menu->scrollTarget / menu->rowSpacing;
        if (menu->top < menu->scroll) {
            room = total - page - menu->top;
            menu->top += (page < room) ? page : room;
        }
        if (prev_top != menu->top) {
            func_8003F6AC(1);
        }
    }
    return menu->flags;
}

/**
 * Puts the cursor on row `arg1` and scrolls up to it if needed.
 * @unverified Name and comment guessed from the code.
 */
void ScrollList_SetCursor(s32* arg0, u32 arg1) {
    s32 v;

    arg0[16] = 0;
    arg0[2] = arg1;
    arg0[13] = arg0[4] * arg1;
    if (arg0[13] < arg0[11]) {
        arg0[11] = arg0[13];
    } else {
        v = (arg0[13] + arg0[4]) - (arg0[4] * arg0[9]);
        if (arg0[11] < v) {
            arg0[11] = v;
        }
    }
    arg0[12] = arg0[11];
}

/**
 * Puts the cursor on row `arg1`, keeping its distance from the top of the visible area where possible.
 * @unverified Name and comment guessed from the code.
 */
void ScrollList_SetCursorKeepOffset(s32* arg0, s32 arg1) {
    s32 temp_a2;
    s32 temp_v0;
    s32 var_a1;
    s32 var_v0;
    s32 var_v1;

    arg0[16] = 0;
    arg0[2] = arg1;
    temp_v0 = arg0[13] - arg0[11];
    arg0[13] = arg0[4] * arg1;

    temp_a2 = ((s32*)arg0[0])[2] - arg0[9];

    var_a1 = temp_a2 = (temp_a2 > 0) ? temp_a2 : 0;
    temp_a2 *= arg0[4];

    var_v0 = (arg0[13] - temp_v0 > 0) ? arg0[13] - temp_v0 : 0;

    var_v1 = (var_v0 < temp_a2) ? var_v0 : temp_a2;
    arg0[11] = var_v1;
    arg0[12] = var_v1;
}

void WidgetTree_SetPagedGridSelectionWithOffset(s8* arg0, s32 arg1, s32 arg2) {
    s32 temp_a2;
    s32 temp_a2_2;
    s32 temp_lo;
    s32 temp_v1;
    s32 var_v0_2;
    s8* temp_v0 = M2C_FIELD(arg0, s8**, 0);

    if (M2C_FIELD(temp_v0, s32*, 8) != 0) {
        M2C_FIELD(arg0, s32*, 0x40) = 0;
        temp_v1 = M2C_FIELD(temp_v0, s32*, 8) - 1;
        if (arg1 >= temp_v1) {
            arg1 = temp_v1;
        }
        M2C_FIELD(arg0, s32*, 8) = arg1;
        M2C_FIELD(arg0, s32*, 0x34) = M2C_FIELD(arg0, s32*, 0x10) * arg1;

        temp_a2 = M2C_FIELD(temp_v0, s32*, 8) - M2C_FIELD(arg0, s32*, 0x24);
        temp_lo = M2C_FIELD(arg0, s32*, 0x10) * ((temp_a2 > 0) ? temp_a2 : 0);

        temp_a2_2 = -(arg2 * M2C_FIELD(arg0, s32*, 0x10)) + M2C_FIELD(arg0, s32*, 0x34);
        if (temp_a2_2 > 0) {
            var_v0_2 = temp_a2_2;
        } else {
            var_v0_2 = 0;
        }

        temp_v1 = (var_v0_2 < temp_lo) ? var_v0_2 : temp_lo;
        M2C_FIELD(arg0, s32*, 0x2C) = temp_v1;
        M2C_FIELD(arg0, s32*, 0x30) = temp_v1;
    }
}

void ScrollGrid_SetItems(s8* arg0, s32 arg1, s32 arg2);
extern s32 D_800603C0;
/**
 * Sets up a scrolling grid menu: draw callback, cell size, columns, rows and item table.
 * @unverified Name and comment guessed from the code.
 */
void ScrollGrid_Init(s8* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7) {
    M2C_FIELD(arg0, s32*, 0x24) = arg4;
    M2C_FIELD(arg0, s32*, 0xC) = arg6;
    M2C_FIELD(arg0, s32*, 0x10) = arg7;
    M2C_FIELD(arg0, s32*, 0x14) = arg5;
    ScrollGrid_SetItems(arg0, arg1, arg2);
    M2C_FIELD(arg0, s32*, 0x1C) = 0xC00;
    M2C_FIELD(arg0, s32*, 0x20) = 0x100000;
    M2C_FIELD(arg0, s32*, 0x18) = D_800603C0;
    M2C_FIELD(arg0, s16*, 0x28) = M2C_FIELD(arg0, u16*, 0x2A) = 0;
    M2C_FIELD(arg0, s32*, 0x2C) = 0;
    M2C_FIELD(arg0, s32*, 0x34) = 0;
    M2C_FIELD(arg0, s32*, 0x38) = M2C_FIELD(arg0, s32*, 0x10) * 4 / 10;
    M2C_FIELD(arg0, s32*, 0x3C) = M2C_FIELD(arg0, s32*, 0x24) * M2C_FIELD(arg0, s32*, 0x10) * 2 / 10;
    M2C_FIELD(arg0, s32*, 0x40) = 8;
    M2C_FIELD(arg0, s32*, 0x44) = 0;
    M2C_FIELD(arg0, s32*, 0x48) = arg3;
    M2C_FIELD(arg0, s32*, 0x4C) = M2C_FIELD(arg0, s32*, 0xC) * 4 / 10;
}

void Menu_ClearItemFlags(u8* arg0);

/**
 * Points the grid at item table `arg1` with flags `arg2` and resets the cursor.
 * @unverified Name and comment guessed from the code.
 */
void ScrollGrid_SetItems(s8 *arg0, s32 arg1, s32 arg2) {
    M2C_FIELD(arg0, s32 *, 0) = arg1;
    M2C_FIELD(arg0, s32 *, 4) = arg2;
    M2C_FIELD(arg0, s32 *, 8) = 0;
    Menu_ClearItemFlags((u8*)arg0);
}

/**
 * Scrolls up when the cursor row is above the visible area.
 * @unverified Name and comment guessed from the code.
 */
void ScrollGrid_ScrollUpToCursor(s8 *arg0) {
    s32 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s32 *, 0x34);
    if (temp_v0 < M2C_FIELD(arg0, s32 *, 0x2C)) {
        M2C_FIELD(arg0, s32 *, 0x2C) = temp_v0;
    }
}

// FAKE: decomp slop. Raw pointer-offset casts stand in for struct fields.
/**
 * Scrolls down when the cursor row is below the visible area.
 * @unverified Name and comment guessed from the code.
 */
void ScrollGrid_ScrollDownToCursor(s8 *arg0)
{
  s32 temp_v0;
  s8 *new_var; // FAKE: permuter temp
  temp_v0 = ((*((s32 *) (((s8 *) arg0) + 0x34))) - ((*((s32 *) (((s8 *) arg0) + 0x24))) * (*((s32 *) (((s8 *) arg0) + 0x10))))) + 1; // FAKE: decomp slop, raw pointer casts stand in for struct fields
  new_var = ((s8 *) arg0) + 0x2C;
  if ((*((s32 *) (((s8 *) arg0) + 0x2C))) < temp_v0)
  {
    *((s32 *) new_var) = temp_v0;
  }
}

/**
 * Moves the drawn scroll position toward the target a step at a time.
 * @unverified Name and comment guessed from the code.
 */
void ScrollGrid_AnimateScroll(GridMenu80031004* menu) {
    s32 t1;
    s32 t3;
    s32 t2;
    s32 speed;

    if (menu->flags & 0x800) {
        if (!(M2C_FIELD(menu, u16*, 0x28) & 0x800)) {
            speed = M2C_FIELD(menu, s32*, 0x38);
            t1 = (menu->cursor / menu->columns) * menu->cellHeight;

            menu->scrollTarget = menu->scrollTarget - (((menu->scrollTarget - t1) < speed) ? (menu->scrollTarget - t1) : speed);
            ScrollGrid_ScrollUpToCursor((s8*)menu);
            if (t1 == menu->scrollTarget) {
                menu->flags &= ~0x800;
            }
        }
    } else if (menu->flags & 0x400) {
        if (!(M2C_FIELD(menu, u16*, 0x28) & 0x400)) {
            t2 = ((menu->cursor / menu->columns) + 1) * menu->cellHeight - 1;
            speed = M2C_FIELD(menu, s32*, 0x38);
            menu->scrollTarget += (((t2 - menu->scrollTarget) < speed) ? (t2 - menu->scrollTarget) : speed);
            ScrollGrid_ScrollDownToCursor((s8*)menu);
            if (t2 == menu->scrollTarget) {
                menu->flags &= ~0x400;
                menu->scrollTarget = menu->scrollTarget - menu->cellHeight + 1;
            }
        }
    } else if (menu->flags & 0x200) {
        if (!(M2C_FIELD(menu, u16*, 0x28) & 0x200)) {
            t3 = (menu->cursor % menu->columns) * menu->cellWidth;

            M2C_FIELD(menu, s32*, 0x44) = M2C_FIELD(menu, s32*, 0x44) - (((M2C_FIELD(menu, s32*, 0x44) - t3) < M2C_FIELD(menu, s32*, 0x4C)) ? (M2C_FIELD(menu, s32*, 0x44) - t3) : M2C_FIELD(menu, s32*, 0x4C));
            if (t3 == M2C_FIELD(menu, s32*, 0x44)) {
                menu->flags &= ~0x200;
            }
        }
    } else if (menu->flags & 0x100) {
        if (!(M2C_FIELD(menu, u16*, 0x28) & 0x100)) {
            t3 = ((menu->cursor % menu->columns) + 1) * menu->cellWidth - 1;
            M2C_FIELD(menu, s32*, 0x44) = (((t3 - M2C_FIELD(menu, s32*, 0x44)) < M2C_FIELD(menu, s32*, 0x4C)) ? (t3 - M2C_FIELD(menu, s32*, 0x44)) : M2C_FIELD(menu, s32*, 0x4C)) + M2C_FIELD(menu, s32*, 0x44);
            if (t3 == M2C_FIELD(menu, s32*, 0x44)) {
                menu->flags &= ~0x100;
                M2C_FIELD(menu, s32*, 0x44) = M2C_FIELD(menu, s32*, 0x44) - menu->cellWidth + 1;
            }
        }
    }
    M2C_FIELD(menu, u16*, 0x28) = 0;
}

/**
 * Draws the up and down arrows when there are rows above or below the visible area.
 * @unverified Name and comment guessed from the code.
 */
void ScrollGrid_DrawScrollArrows(GridMenu800310D8* menu, s32 x, s32 y) {
    s32 height = menu->cellHeight * menu->rows;
    s32 arrowX;
    s32 topY;
    s32 bottomY;
    s32 more;
    s32 width = menu->cellWidth * menu->columns;
    u8* tex;

    arrowX = (menu->cellWidth * menu->columns) / 2 + x - 9;
    topY = y - 0x10;
    bottomY = y + height;
    gDPPipeSync(gDisplayListHead++);
    gDPSetCycleType(gDisplayListHead++, G_CYC_1CYCLE);
    gDPSetRenderMode(gDisplayListHead++, 0x0F0A4000, 0);
    gDPSetCombineMode(gDisplayListHead++, G_CC_DECALRGBA, G_CC_DECALRGBA);
    gDPSetTexturePersp(gDisplayListHead++, G_TP_NONE);
    gDPSetTextureFilter(gDisplayListHead++, G_TF_POINT);
    func_8001C22C(x, topY, width, 0x10, D_04003A50, 8, 0);
    func_8001C22C(x, bottomY, width, 0x10, D_04003A50, 8, 0);
    gSPDisplayList(gDisplayListHead++, D_80073408);
    tex = (menu->scroll > 0) ? D_04003AD8 : D_040044F8;
    func_8001B884(arrowX, topY, 0x12, 0x10, tex, 0x14, 0x200000);
    more = menu->scroll + height < ((menu->def->itemCount + menu->columns - 1) / menu->columns) * menu->cellHeight;
    func_8001B884(arrowX, bottomY, 0x12, 0x10, more ? D_04003D60 : D_04004780, 0x14, 0x200000);
    gSPDisplayList(gDisplayListHead++, D_80073438);
}


/**
 * Draws a rectangle (via Ui_DrawRoundedFrame) for the cursor of a paged grid menu.
 * The column is cursor % columns, so x = column * cellWidth + arg1. y is
 * scrollTarget + arg2 - scroll + 2; when flag 0x400 is set, (cellHeight - 1)
 * is subtracted from it. The rectangle size is the cell size minus 4 in each
 * direction, and the colour argument is read from D_80073520.
 * @unverified Name guessed from the code; comment kept.
 */
void ScrollGrid_DrawCursor(GridMenu80031004* arg0, s32 arg1, s32 arg2) {
    s32 sp2C;
    s32 sp28;

    sp2C = arg0->scrollTarget + arg2 - arg0->scroll + 2;
    sp28 = (arg0->cursor % arg0->columns) * arg0->cellWidth + arg1;
    if (arg0->flags & 0x400) {
        sp2C = sp2C - arg0->cellHeight + 1;
    }
    Ui_DrawRoundedFrame(sp28, sp2C, arg0->cellWidth - 4, arg0->cellHeight - 4, *(Color_RGBA8*)D_80073520);
}

void ScrollGrid_DrawScrollArrows(GridMenu800310D8*, s32, s32);

/**
 * Grid version of ScrollList_DrawInlineItems: sets the scissor to the menu area (columns * cellWidth by
 * rows * cellHeight at x, y), calls ScrollGrid_AnimateScroll, then draws every visible cell i through
 * menu->draw(column x, row y, item, i, flags & mask, arg4). The cell's flags come from
 * menu->flags and get 0x12 for the cursor cell; cells past def->itemCount get no item and
 * flags 0. Afterwards the scissor is reset to the full screen, ScrollGrid_DrawScrollArrows draws when option
 * bit 0x100000 is set and ScrollGrid_DrawCursor (cursor box) draws when the list is non-empty, mask
 * bit 2 is set and option bit 0x10000 is set.
 * @unverified Name guessed from the code; comment kept.
 */
void ScrollGrid_DrawItems(GridMenu800310D8* menu, s32 x, s32 y, s32 mask, s32 arg4) {
    s32 width = menu->cellWidth * menu->columns;
    MenuDef8002E230* def = menu->def;
    u8* items = def->items;
    s32 height = menu->cellHeight * menu->rows;
    s32 i;
    s32 end;
    s32 baseY;
    u8* item;
    s32 f;

    gDPPipeSync(gDisplayListHead++);
    gDPSetScissorFrac(gDisplayListHead++, G_SC_NON_INTERLACE, x * 4.0f, y * 4.0f, (x + width) * 4.0f, (y + height) * 4.0f);
    ScrollGrid_AnimateScroll((GridMenu80031004*)menu);
    baseY = y - menu->scroll;
    i = (menu->scroll / menu->cellHeight) * menu->columns;
    end = ((menu->scroll + height - 1) / menu->cellHeight + 1) * menu->columns;
    for (; i < end; i++) {
        item = NULL;
        f = 0;
        if (i < menu->def->itemCount) {
            item = items + def->itemSize * i;
            f = menu->flags[i];
            if (i == menu->cursor) {
                f |= 0x12;
            }
        }
        menu->draw((i % menu->columns) * menu->cellWidth + x, (i / menu->columns) * menu->cellHeight + baseY, item, i, f & mask, arg4);
    }
    gDPPipeSync(gDisplayListHead++);
    gDPSetScissor(gDisplayListHead++, G_SC_NON_INTERLACE, 0, 0, 640, 480);
    if (menu->options & 0x100000) {
        ScrollGrid_DrawScrollArrows(menu, x, y);
    }
    if ((menu->def->itemCount > 0) && (mask & 2) && (menu->options & 0x10000)) {
        ScrollGrid_DrawCursor((GridMenu80031004*)menu, x, y);
    }
}

/**
 * Returns how many cells the current row has (the last row can be short).
 * @unverified Name and comment guessed from the code.
 */
s32 ScrollGrid_GetRowLength(GridMenu80031004* menu) {
    s32 page_count = (M2C_FIELD(menu, MenuDef8002E230**, 0x0)->itemCount + menu->columns - 1) / menu->columns;
    s32 page = menu->scrollTarget / menu->cellHeight;
    s32 next_page = page + 1;
    s32 remainder = M2C_FIELD(menu, MenuDef8002E230**, 0x0)->itemCount % menu->columns;

    return ((page_count == next_page) && (remainder != 0)) ? remainder : menu->columns;
}

typedef struct GridMenu8003152C {
    /* 0x00 */ MenuDef8002E230* def;
    /* 0x04 */ char unk04[0x4];
    /* 0x08 */ s32 cursor;
    /* 0x0C */ s32 cellWidth;
    /* 0x10 */ s32 cellHeight;
    /* 0x14 */ char unk14[0x4];
    /* 0x18 */ u16* input;
    /* 0x1C */ char unk1C[0xC];
    /* 0x28 */ u16 buttons;
    /* 0x2A */ u16 flags;
    /* 0x2C */ s32 scroll;
    /* 0x30 */ char unk30[0x4];
    /* 0x34 */ s32 scrollTarget;
    /* 0x38 */ s32 scrollSpeed;
    /* 0x3C */ char unk3C[0x4];
    /* 0x40 */ s32 repeatTimer;
    /* 0x44 */ s32 scrollX;
    /* 0x48 */ s32 columns;
    /* 0x4C */ s32 scrollSpeedX;
} GridMenu8003152C;

/**
 * Moves the scrolling grid's cursor with the D-Pad and scrolls to keep it visible.
 * @unverified Name and comment guessed from the code.
 */
u16 ScrollGrid_UpdateCursor(GridMenu8003152C *menu)
{
  long new_var; // FAKE
  s32 prev = menu->cursor;
  s32 lim;
  s32 w;
  if (menu->def->itemCount == 0)
  {
    return 0;
  }
  if (menu->input[4] & 0x800)
  { menu->repeatTimer = 8; menu->buttons = 0x800; }
  else
    if (menu->input[4] & 0x400)
  { menu->repeatTimer = 8; menu->buttons = 0x400; }
  else
    if (menu->input[4] & 0x200)
  { menu->repeatTimer = 8; menu->buttons = 0x200; }
  else
    if (menu->input[4] & 0x100)
  { menu->repeatTimer = 8; menu->buttons = 0x100; }
  else
    if (menu->repeatTimer > 0)
  {
    menu->repeatTimer--;
  }
  else
  {
 do { menu->buttons = menu->input[3]; } while (0); // FAKE
  }
  if ((menu->buttons & 0x800) && (!(menu->flags & (~0x800))))
  {
    menu->flags |= 0x800;
    menu->scrollTarget -= (menu->scrollTarget < menu->scrollSpeed) ? (menu->scrollTarget) : (menu->scrollSpeed);
    ScrollGrid_ScrollUpToCursor((s8 *) menu);
    menu->cursor = ((menu->scrollTarget / menu->cellHeight) * menu->columns) + (menu->scrollX / menu->cellWidth);
  }
  else
    if ((menu->buttons & 0x400) && (!(menu->flags & (~0x400))))
  {
    if (menu->flags == 0)
    {
      menu->scrollTarget = (menu->scrollTarget + menu->cellHeight) - 1;
    }
    menu->flags |= 0x400;
    new_var = (((menu->def->itemCount + menu->columns) - 1) / menu->columns) * menu->cellHeight;
    menu->scrollTarget += (((new_var - menu->scrollTarget) - 1) < menu->scrollSpeed) ? ((new_var - menu->scrollTarget) - 1) : (menu->scrollSpeed);
    ScrollGrid_ScrollDownToCursor((s8 *) menu);
    lim = (ScrollGrid_GetRowLength((GridMenu80031004 *) menu) - 1) * menu->cellWidth;
    if (lim < menu->scrollX)
    {
      menu->scrollX = lim;
    }
    menu->cursor = ((menu->scrollTarget / menu->cellHeight) * menu->columns) + (menu->scrollX / menu->cellWidth);
  }
  else
    if ((menu->buttons & 0x200) && (!(menu->flags & (~0x200))))
  {
    menu->flags |= 0x200;
    if (menu->scrollX < menu->scrollSpeedX)
    {
      menu->scrollX += menu->cellWidth * ScrollGrid_GetRowLength((GridMenu80031004 *) menu);
    }
    menu->scrollX -= menu->scrollSpeedX;
    menu->cursor = ((menu->scrollTarget / menu->cellHeight) * menu->columns) + (menu->scrollX / menu->cellWidth);
  }
  else
    if ((menu->buttons & 0x100) && (!(menu->flags & (~0x100))))
  {
    if (menu->flags == 0)
    {
      menu->scrollX = (menu->scrollX + menu->cellWidth) - 1;
    }
    menu->flags |= 0x100;
    lim = ScrollGrid_GetRowLength((GridMenu80031004 *) menu);
    w = menu->cellWidth;
    lim = w * lim; if (w) {} // FAKE: found by the traced-allocator lever sweep; keeps w live so the sum takes a2
    if ((menu->scrollX + menu->scrollSpeedX) >= lim)
    {
      menu->scrollX -= lim;
    }
    menu->scrollX += menu->scrollSpeedX;
    menu->cursor = ((menu->scrollTarget / menu->cellHeight) * menu->columns) + (menu->scrollX / w);
  }
  if (prev != menu->cursor)
  {
    func_8003F6AC(1);
  }
  return menu->flags;
}

typedef struct GridMenu80031AB0 {
    /* 0x00 */ char unk00[0x8];
    /* 0x08 */ s32 cursor;
    /* 0x0C */ u32 cellWidth;
    /* 0x10 */ u32 cellHeight;
    /* 0x14 */ char unk14[0x10];
    /* 0x24 */ u32 rows;
    /* 0x28 */ char unk28[4];
    /* 0x2C */ s32 scroll;
    /* 0x30 */ s32 scrollTarget;
    /* 0x34 */ s32 cursorY;
    /* 0x38 */ char unk38[0x8];
    /* 0x40 */ s32 unk40;
    /* 0x44 */ s32 cursorX;
    /* 0x48 */ s32 columns;
} GridMenu80031AB0;
/**
 * Puts the cursor on cell `arg1` and scrolls to it.
 * @unverified Name and comment guessed from the code.
 */
void ScrollGrid_SetCursor(GridMenu80031AB0* arg0, s32 arg1) {
    s32 v;
    arg0->unk40 = 0;
    arg0->cursor = arg1;
    arg0->cursorY = (arg1 / arg0->columns) * arg0->cellHeight;
    arg0->cursorX = (arg1 % arg0->columns) * arg0->cellWidth;
    if (arg0->cursorY < arg0->scroll) {
        arg0->scroll = arg0->cursorY;
    } else {
        v = (arg0->cursorY + arg0->cellHeight) - arg0->rows * arg0->cellHeight;
        if (arg0->scroll < v) {
            arg0->scroll = v;
        }
    }
    arg0->scrollTarget = arg0->scroll;
}

void ScrollGrid_SetCursor();                 /* extern */

/**
 * Moves the cursor past disabled cells and scrolls to it.
 * @unverified Name and comment guessed from the code.
 */
void ScrollGrid_SyncCursor(s8 *arg0) {
    Menu_SkipDisabledForward((Menu8002E230*)arg0);
    ScrollGrid_SetCursor(arg0, M2C_FIELD(arg0, s32 *, 8));
}
