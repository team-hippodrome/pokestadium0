/* Stadium Zero resident code. */

#include "global.h"
#include "m2c_macros.h"
#include "menu.h"

void ScrollList_AnimateScroll(ScrollMenu*);
void ScrollList_DrawScrollArrows(ScrollMenu*, s32, s32, s32, s32);
void ScrollList_DrawCursor(ScrollMenu*, s32, s32);

extern u8 D_80073520[];
M2C_UNK Ui_DrawRoundedFrame(s32, s32, s32, s32, Color_RGBA8);

void Menu_SetItems(Menu* arg0, ByteMatrix* arg1, u16* arg2);
extern Controller* D_800603C0;
M2C_UNK func_8000B2F4(Controller*);

/**
 * Initializes a menu: stores its layout arguments, sets the position through Menu_SetItems, the 0xC00 repeat delay and the controller.
 * Seen in play (2026-11-12) in いちらん: R, then A on the ポケモン header, set up the five-row sort menu
 * through this (アイウエオじゅんにならべる ... いちらんするポケモンをえらぶ).
 */
void Menu_Init(Menu* arg0, ByteMatrix* arg1, u16* arg2, MenuDrawItemFunc arg3, s32 arg4, s32 arg5) {
    arg0->cellWidth = arg4;
    arg0->cellHeight = arg5;
    arg0->drawItem = arg3;
    Menu_SetItems(arg0, arg1, arg2);
    arg0->unk_1C = 0xC00;
    arg0->options = 0;
    func_8000B2F4(arg0->controller = D_800603C0);
}

void Menu_ClearItemFlags(Menu* arg0);

/**
 * Points the menu at item table `arg1` with flags `arg2`, puts the cursor on the first item and clears the item flags.
 * Seen in play (2026-11-12) in いちらん: called from Menu_Init for the five-row sort menu.
 */
void Menu_SetItems(Menu* arg0, ByteMatrix* arg1, u16* arg2) {
    arg0->items = arg1;
    arg0->itemFlags = arg2;
    arg0->cursor = 0;
    Menu_ClearItemFlags(arg0);
}

/**
 * Clears the flags of every item.
 * Seen in play (2026-11-12) in いちらん: ran over 5 items for the sort menu and 15 for the タイプであつめる
 * type list (the 15 Gen 1 types).
 */
void Menu_ClearItemFlags(Menu* arg0) {
    s32 i;

    for (i = 0; i < arg0->items->capacity; i++) {
        arg0->itemFlags[i] = 0;
    }
}

/**
 * Draws the cursor rectangle (via Ui_DrawRoundedFrame) for a list menu with one cell per row:
 * x = arg1 + 2, y = cursor * cellHeight + arg2 + 2, size = (cellWidth - 4) x (cellHeight - 4),
 * color read from D_80073520. Compare ScrollList_DrawCursor and ScrollGrid_DrawCursor. The separate `y`
 * local only fixes the order in which the fields are loaded.
 * Seen in play (2026-11-12) in いちらん: drew the yellow cursor frame on the selected sort menu row.
 */
void Menu_DrawCursor(Menu* arg0, s32 arg1, s32 arg2) {
    s32 y;

    y = arg0->cursor * arg0->cellHeight + arg2 + 2;
    Ui_DrawRoundedFrame(arg1 + 2, y, arg0->cellWidth - 4, arg0->cellHeight - 4, *(Color_RGBA8*)D_80073520);
}

/**
 * Draws a menu's items from its definition, one row per item.
 * Seen in play (2026-11-12) in いちらん: drew the sort menu rows every frame while it was open.
 */
void Menu_DrawItems(Menu* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 i;
    s32 y = arg2;
    s32 count = arg0->items->count;
    u8** items = (u8**)arg0->items->rows;
    s32 flags;

    for (i = 0; i < count; i++) {
        flags = arg0->itemFlags[i];
        if (i == arg0->cursor) {
            flags |= 0x12;
        }
        arg0->drawItem(arg1, y, items[i], i, flags & arg3, arg4);
        y += arg0->cellHeight;
    }
    if (arg0->items->count > 0 && (arg3 & 2) && (arg0->options & 0x10000)) {
        Menu_DrawCursor(arg0, arg1, arg2);
    }
}

/**
 * Like Menu_DrawItems, for item tables that store `itemSize`-byte items inline instead of pointers.
 * Seen in play (2026-11-13) (menu tour from the main menu): called in the Lab list (いちらん) and the
 * Lab PC box screen.
 * @unverified Name and comment guessed from the code.
 */
void Menu_DrawInlineItems(Menu* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 i;
    s32 y = arg2;
    ByteMatrix* def = arg0->items;
    s32 count = def->count;
    u8* items = def->rows;
    s32 flags;

    for (i = 0; i < count; i++) {
        flags = arg0->itemFlags[i];
        if (i == arg0->cursor) {
            flags |= 0x12;
        }
        arg0->drawItem(arg1, y, items + def->rowSize * i, i, flags & arg3, arg4);
        y += arg0->cellHeight;
    }
    if (arg0->items->count > 0 && (arg3 & 2) && (arg0->options & 0x10000)) {
        Menu_DrawCursor(arg0, arg1, arg2);
    }
}

s32 func_8000B30C();
s32 func_8003F6AC();
/**
 * Moves a menu's cursor from controller input. Returns 0 when the menu has no items.
 * Seen in play (2026-11-12) in いちらん: D-Down moved the sort menu cursor one row per press. It also
 * stops on a disabled row (すべてのせんたくをやめる).
 */
s32 Menu_UpdateCursor(Menu* arg0) {
    s32 input;
    s32 old = arg0->cursor;

    if (arg0->items->count == 0) {
        return 0;
    }
    if (arg0) { // FAKE: no-op test; changes register allocation to match
    }
    input = (u16)func_8000B30C();
    switch (input) {
        case 0x800:
            if (arg0->cursor == 0) {
                arg0->cursor += arg0->items->count;
            }
            arg0->cursor--;
            break;
        case 0x400:
            if (arg0->cursor >= arg0->items->count - 1) {
                arg0->cursor -= arg0->items->count;
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
 * Seen in play (2026-11-13) ran while the cursor was in the せいとん (sort) screen's box list.
 */
s32 Menu_UpdateCursorSkipDisabled(Menu* arg0) {
    s32 input;
    s32 old = arg0->cursor;

    if (arg0->items->count == 0) {
        return 0;
    }
    if (arg0) {}  // karodo
    input = (u16)func_8000B30C();
    switch (input) {
        case 0x800:
            do {
                if (arg0->cursor == 0) {
                    arg0->cursor += arg0->items->count;
                }
                arg0->cursor--;
            } while (arg0->itemFlags[arg0->cursor] & 1);
            break;
        case 0x400:
            do {
                if (arg0->cursor == arg0->items->count - 1) {
                    arg0->cursor -= arg0->items->count;
                }
                arg0->cursor++;
            } while (arg0->itemFlags[arg0->cursor] & 1);
            break;
    }
    if (old != arg0->cursor) {
        func_8003F6AC(1);
    }
    return input;
}

/**
 * Moves the cursor forward past disabled items (flag 1).
 * Seen in play (2026-11-13) ran once when the Free Battle opponent picker (1P VS 2P, 3P, 4P, COM)
 * opened with only one controller: the cursor came up on COM, past the greyed-out 2P to 4P rows.
 */
s32 Menu_SkipDisabledForward(Menu* arg0) {
    s32 i;

    for (i = arg0->cursor; i < arg0->items->count && (arg0->itemFlags[i] & 1); i++) {
    }
    if (i < arg0->items->count) {
        arg0->cursor = i;
        return i;
    }
    for (i = arg0->cursor - 1; i >= 0 && (arg0->itemFlags[i] & 1); i--) {
    }
    if (i >= 0) {
        arg0->cursor = i;
        return i;
    }
    return -1;
}

void GridMenu_SetItems(GridMenu*, ByteMatrix*, u16*);
extern Controller* D_800603C0;
M2C_UNK func_8000B2F4(Controller*);

/**
 * Initializes a grid menu: stores the column count, cell size and item callback, points it at
 * item table `arg1` with flags `arg2` (GridMenu_SetItems), and stores the 0xC00 value and the
 * controller D_800603C0, which is also passed to func_8000B2F4.
 * Seen in play (2026-11-12) in せいとん: ran when ポケモンのせいり was opened from the せいとん menu.
 */
void GridMenu_Init(GridMenu* arg0, ByteMatrix* arg1, u16* arg2, MenuDrawItemFunc arg3, s32 arg4, s32 arg5, s32 arg6) {
    arg0->columns = arg4;
    arg0->cellWidth = arg5;
    arg0->cellHeight = arg6;
    arg0->drawItem = arg3;
    GridMenu_SetItems(arg0, arg1, arg2);
    arg0->unk_1C = 0xC00;
    arg0->options = 0;
    func_8000B2F4(arg0->controller = D_800603C0);
}

void GridMenu_ClearItemFlags(GridMenu* arg0);

/**
 * Points the grid menu at item table `arg1` with flags `arg2`, puts the cursor on the first item and clears the item flags.
 * Seen in play (2026-11-12) in せいとん: called from GridMenu_Init when ポケモンのせいり was opened.
 */
void GridMenu_SetItems(GridMenu* arg0, ByteMatrix* arg1, u16* arg2) {
    arg0->items = arg1;
    arg0->itemFlags = arg2;
    arg0->cursor = 0;
    GridMenu_ClearItemFlags(arg0);
}

/**
 * Clears the flags of every item.
 * Seen in play (2026-11-12) in せいとん: called from GridMenu_SetItems when ポケモンのせいり was opened.
 */
void GridMenu_ClearItemFlags(GridMenu* arg0) {
    s32 i;

    for (i = 0; i < arg0->items->capacity; i++) {
        arg0->itemFlags[i] = 0;
    }
}

/**
 * Draws the cursor rectangle (via Ui_DrawRoundedFrame) for a multi-column menu: the cursor cell is
 * at column cursor % columns, row cursor / columns, so x = column * colSpacing + arg_x + 2 and
 * y = row * rowSpacing + arg_y + 2; the size is (colSpacing - 4) x (rowSpacing - 4) and the
 * color is read from D_80073520. Compare ScrollGrid_DrawCursor. The `px`/`py` locals only fix the
 * evaluation order of the argument expressions.
 * Seen in play (2026-11-13) (tour of menus and a COM battle): ran in Free Battle setup.
 * @unverified Name guessed from the code; comment kept.
 */
void GridMenu_DrawCursor(GridMenu* menu, s32 x, s32 y) {
    s32 px;
    s32 py;

    px = (menu->cursor % menu->columns) * menu->cellWidth + x + 2;
    py = (menu->cursor / menu->columns) * menu->cellHeight + y + 2;
    Ui_DrawRoundedFrame(px, py, menu->cellWidth - 4, menu->cellHeight - 4, *(Color_RGBA8*)D_80073520);
}

/**
 * Draws every cell of the grid; items are pointers.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal or j,
 * no pointer word, no lui/addiu pair in any fragment), so play cannot reach it.
 * @unverified Name and comment guessed from the code.
 */
void GridMenu_DrawItems(GridMenu* menu, s32 x, s32 y, s32 mask, s32 arg4) {
    ByteMatrix* def = menu->items;
    s32 i;
    u8** items = (u8**)def->rows;
    u8* item;
    s32 f;

    for (i = 0; i < def->capacity; i++) {
        item = (i < def->count) ? items[i] : NULL;
        f = menu->itemFlags[i];
        if (i == menu->cursor) {
            f |= 0x12;
        }
        menu->drawItem((i % menu->columns) * menu->cellWidth + x, (i / menu->columns) * menu->cellHeight + y, item, i, f & mask, arg4);
    }
    if ((menu->items->count > 0) && (mask & 2) && (menu->options & 0x10000)) {
        GridMenu_DrawCursor(menu, x, y);
    }
}

void GridMenu_DrawCursor(GridMenu*, s32, s32);
/**
 * Draws every cell of the grid; items are stored inline.
 * Seen in play (2026-11-12): drew the main menu's 3 x 3 item grid (せいとん, いちらん, ずかん, バトル, てもち, GB,
 * OFF, とうろく) every frame.
 */
void GridMenu_DrawInlineItems(GridMenu* menu, s32 x, s32 y, s32 mask, s32 arg4) {
    ByteMatrix* def = menu->items;
    s32 i;
    u8* items = def->rows;
    u8* item;
    s32 f;

    for (i = 0; i < def->capacity; i++) {
        item = (i < def->count) ? items + def->rowSize * i : NULL;
        f = menu->itemFlags[i];
        if (i == menu->cursor) {
            f |= 0x12;
        }
        menu->drawItem(x + (i % menu->columns) * menu->cellWidth, y + (i / menu->columns) * menu->cellHeight, item, i, f & mask, arg4);
    }
    if ((menu->items->count > 0) && (mask & 2) && (menu->options & 0x10000)) {
        GridMenu_DrawCursor(menu, x, y);
    }
}

/**
 * Moves the grid cursor with the D-Pad, wrapping around rows and columns.
 * Seen in play (2026-11-13) ran while the せいとん (sort) screen's Pokémon move grid had the cursor.
 */
s32 GridMenu_UpdateCursor(GridMenu* arg0) {
    s32 input;
    s32 old = arg0->cursor;

    if (arg0->items->count == 0) {
        return 0;
    }
    if (arg0 && arg0) { // FAKE: no-op test; changes register allocation to match
    }
    input = (u16)func_8000B30C();
    switch (input) {
        case 0x800:
            arg0->cursor -= arg0->columns;
            if (arg0->cursor < 0) {
                arg0->cursor += ((arg0->items->count - 1) / arg0->columns + 1) * arg0->columns;
                if (arg0->cursor > arg0->items->count - 1) {
                    arg0->cursor = arg0->items->count - 1;
                }
            }
            break;
        case 0x400:
            arg0->cursor += arg0->columns;
            if ((arg0->items->count - 1) / arg0->columns < arg0->cursor / arg0->columns) {
                arg0->cursor = arg0->cursor % arg0->columns;
            } else if (arg0->cursor > arg0->items->count - 1) {
                arg0->cursor = arg0->items->count - 1;
            }
            break;
        case 0x200:
            if (arg0->cursor % arg0->columns == 0) {
                arg0->cursor += arg0->columns;
            }
            arg0->cursor--;
            if (arg0->cursor > arg0->items->count - 1) {
                arg0->cursor = arg0->items->count - 1;
            }
            break;
        case 0x100:
            if (arg0->cursor % arg0->columns + 1 == arg0->columns) {
                arg0->cursor -= arg0->columns;
            }
            arg0->cursor++;
            if (arg0->cursor >= arg0->items->count) {
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
s32 GridMenu_UpdateCursorSkipDisabled(GridMenu* menu) {
    s32 button;
    s32 prev = menu->cursor;
    s32 found = 0;
    s32 row_start;
    s32 i;
    s32 end;

    if (menu->items->count == 0) {
        return 0;
    }
    button = (u16)func_8000B30C();
    switch (button) {
        case 0x800:
            do {
                menu->cursor -= menu->columns;
                if (menu->cursor < 0) {
                    menu->cursor += ((menu->items->count - 1) / menu->columns + 1) * menu->columns;
                }
                row_start = menu->cursor - menu->cursor % menu->columns;
                for (i = menu->cursor; i >= row_start; i--) {
                    if (i <= menu->items->count - 1 && !(menu->itemFlags[i] & 1)) {
                        menu->cursor = i;
                        found = 1;
                        break;
                    }
                }
                if (!found) {
                    end = menu->columns + row_start - 1;
                    if (end >= menu->items->count - 1) {
                        end = menu->items->count - 1;
                    }
                    for (i = menu->cursor + 1; i <= end; i++) {
                        if (!(menu->itemFlags[i] & 1)) {
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
                if ((menu->items->count - 1) / menu->columns < menu->cursor / menu->columns) {
                    menu->cursor %= menu->columns;
                }
                row_start = menu->cursor - menu->cursor % menu->columns;
                for (i = menu->cursor; i >= row_start; i--) {
                    if (i <= menu->items->count - 1 && !(menu->itemFlags[i] & 1)) {
                        menu->cursor = i;
                        found = 1;
                        break;
                    }
                }
                if (!found) {
                    end = menu->columns + row_start - 1;
                    if (end >= menu->items->count - 1) {
                        end = menu->items->count - 1;
                    }
                    for (i = menu->cursor + 1; i <= end; i++) {
                        if (!(menu->itemFlags[i] & 1)) {
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
            } while (menu->cursor >= menu->items->count || (menu->itemFlags[menu->cursor] & 1));
            break;
        case 0x100:
            do {
                if (menu->cursor % menu->columns + 1 == menu->columns) {
                    menu->cursor -= menu->columns;
                }
                menu->cursor++;
            } while (menu->cursor >= menu->items->count || (menu->itemFlags[menu->cursor] & 1));
            break;
    }
    if (prev != menu->cursor) {
        func_8003F6AC(1);
        if (button) {} // karodo
    }
    return button;
}

void ScrollList_SetItems(ScrollMenu* arg0, ByteMatrix* arg1, u16* arg2);
extern Controller* D_800603C0;
/**
 * Initializes a scrolling list: stores its layout arguments, the position, the 0xC00 repeat delay, the controller and the scroll bar geometry.
 * Seen in play (2026-11-12) in いちらん: set up the scrolling type list of タイプであつめる (8 rows visible).
 */
void ScrollList_Init(ScrollMenu* arg0, ByteMatrix* arg1, u16* arg2, s32 arg3, MenuDrawItemFunc arg4, s32 arg5, s32 arg6) {
    arg0->visibleRows = arg3;
    arg0->cellWidth = arg5;
    arg0->cellHeight = arg6;
    arg0->drawItem = arg4;
    ScrollList_SetItems(arg0, arg1, arg2);
    arg0->unk_1C = 0xC00;
    arg0->options = 0x100000;
    arg0->controller = D_800603C0;
    arg0->inputDirection = arg0->scrollFlags = 0;
    arg0->scrollY = 0;
    arg0->cursorY = 0;
    arg0->cursorStep = (arg0->cellHeight * 4) / 10;
    arg0->pageStep = (arg0->cellHeight * arg0->visibleRows * 2) / 10;
    arg0->repeatTimer = 8;
}

void Menu_ClearItemFlags(Menu* arg0);

/**
 * Points the list at item table `arg1` with flags `arg2` and resets the cursor and scroll.
 * Seen in play (2026-11-12) in いちらん: called from ScrollList_Init with the 15-type item table.
 */
void ScrollList_SetItems(ScrollMenu* arg0, ByteMatrix* arg1, u16* arg2) {
    arg0->items = arg1;
    arg0->itemFlags = arg2;
    arg0->cursor = 0;
    arg0->cursorY = 0;
    arg0->scrollY = 0;
    arg0->pageTargetY = 0;
    arg0->repeatTimer = 0;
    Menu_ClearItemFlags((Menu*)arg0);
}

/**
 * Scrolls up when the cursor row is above the visible area.
 * Not reached in play (2026-11-13): did not run in a tour of the main menu, Pokédex, party, Lab,
 * registration, Free Battle setup and a COM battle (opening, a switch, running, a Pound turn).
 * @unverified Name and comment guessed from the code.
 */
void ScrollList_ScrollUpToCursor(ScrollMenu* arg0) {
    s32 temp_v0;

    temp_v0 = arg0->cursorY;
    if (temp_v0 < arg0->scrollY) {
        arg0->scrollY = temp_v0;
    }
}

/**
 * Scrolls down when the cursor row is below the visible area.
 * Seen in play (2026-11-12) in いちらん: paging the type list with D-Right moved the cursor below the
 * visible rows, and this scrolled down to it.
 */
void ScrollList_ScrollDownToCursor(ScrollMenu* arg0) {
    s32 temp_v0 = arg0->cursorY - arg0->cellHeight * arg0->visibleRows + 1;

    if (arg0->scrollY < temp_v0) {
        arg0->scrollY = temp_v0;
    }
}

// FAKE: permuter output (the karodo no-op tests and the 0xFFFFFFFF mask).
/**
 * Moves the drawn scroll position toward the target a step at a time.
 * Seen in play (2026-11-13) (menu tour from the main menu): called in the Pokédex, the Lab list,
 * sort and PC screens and registration, while a list was on screen.
 * @unverified Name and comment guessed from the code.
 */
void ScrollList_AnimateScroll(ScrollMenu *menu)
{
  s32 t1;
  s32 t3;
  s32 t2;
  s32 speed;
  s32 cur;
  if ((menu->scrollFlags) & 0x800)
  {
    if (!((menu->inputDirection) & 0x800))
    {
      speed = menu->cursorStep;
      t1 = menu->cursor * menu->cellHeight;
      cur = menu->cursorY;
      menu->cursorY = cur - (((cur - t1) < speed) ? (cur - t1) : (speed));
      if (1) {} // karodo
      if (1) {} // karodo
      if (1) {} // karodo
      ScrollList_ScrollUpToCursor(menu);
      if (t1 == (menu->cursorY))
      {
        menu->scrollFlags &= ~0x800;
      }
    }
  }
  else
    if ((menu->scrollFlags) & 0x400)
  {
    if (!((menu->inputDirection) & 0x400))
    {
      t2 = ((menu->cursor + 1) * menu->cellHeight) - 1;
      speed = menu->cursorStep;
      menu->cursorY += ((t2 - (menu->cursorY)) < speed) ? (t2 - (menu->cursorY)) : (speed);
      ScrollList_ScrollDownToCursor(menu);
      if (t2 == (menu->cursorY))
      {
        menu->scrollFlags &= ~0x400;
        menu->cursorY = menu->cursorY - menu->cellHeight + 1;
      }
    }
  }
  else
  {
    if ((menu->scrollFlags) & 0x200)
    {
      if (!((menu->inputDirection) & 0x200))
      {
        t1 = menu->scrollY;
        t3 = menu->pageTargetY;
        t1 = ((t1 - t3) < (menu->pageStep)) ? (t1 - t3) : (menu->pageStep);
        menu->scrollY -= t1;
        if (1) {} // karodo
        menu->cursorY -= t1;
        menu->cursor = (menu->cursorY) / menu->cellHeight;
        if ((t3 & 0xFFFFFFFFu) == menu->scrollY) // FAKE: no-op mask fixes bnel operand order
        {
          menu->scrollFlags &= ~0x200;
        }
      }
    }
    else
      if ((menu->scrollFlags) & 0x100)
    {
      if (!((menu->inputDirection) & 0x100))
      {
        t3 = menu->pageTargetY;
        t1 = ((t3 - menu->scrollY) < (menu->pageStep)) ? (t3 - menu->scrollY) : (menu->pageStep);
        menu->scrollY += t1;
        if (1) {} // karodo
        menu->cursorY += t1;
        menu->cursor = (menu->cursorY) / menu->cellHeight;
        if ((t3 & 0xFFFFFFFFu) == menu->scrollY) // FAKE: no-op mask fixes bnel operand order
        {
          menu->scrollFlags &= ~0x100;
        }
      }
    }
  }
  menu->inputDirection = 0;
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
 * Seen in play (2026-11-12) in いちらん: ran each frame for the main list and drew the up and down
 * arrows above and below it.
 */
void ScrollList_DrawScrollArrows(ScrollMenu* menu, s32 x, s32 topY, s32 bottomY, s32 width) {
    s32 height = menu->cellHeight * menu->visibleRows;
    s32 arrowX;
    s32 more;

    arrowX = menu->cellWidth / 2 + x - 9;
    gDPPipeSync(gDisplayListHead++);
    gDPSetCycleType(gDisplayListHead++, G_CYC_1CYCLE);
    gDPSetRenderMode(gDisplayListHead++, 0x0F0A4000, 0);
    gDPSetCombineMode(gDisplayListHead++, G_CC_DECALRGBA, G_CC_DECALRGBA);
    gDPSetTexturePersp(gDisplayListHead++, G_TP_NONE);
    gDPSetTextureFilter(gDisplayListHead++, G_TF_POINT);
    func_8001C22C(x, topY, width, 0x10, D_04003A50, 8, 0);
    func_8001C22C(x, bottomY, width, 0x10, D_04003A50, 8, 0);
    gSPDisplayList(gDisplayListHead++, D_80073408);
    func_8001B884(arrowX, topY, 0x12, 0x10, (menu->scrollY > 0) ? D_04003AD8 : D_040044F8, 0x14, 0x200000);
    func_8001B884(arrowX - 0x1C, topY, 0x14, 0x10, (menu->scrollY > 0) ? D_04003FE8 : D_04004A08, 0x14, 0x200000);
    more = menu->scrollY + height < menu->cellHeight * menu->items->count;
    func_8001B884(arrowX, bottomY, 0x12, 0x10, more ? D_04003D60 : D_04004780, 0x14, 0x200000);
    func_8001B884(arrowX + 0x1A, bottomY, 0x14, 0x10, more ? D_04004270 : D_04004C90, 0x14, 0x200000);
    gSPDisplayList(gDisplayListHead++, D_80073438);
}

/**
 * Draws the cursor rectangle (via Ui_DrawRoundedFrame) for a scrolling list menu. Same shape as
 * ScrollGrid_DrawCursor but with x = arg1 + 2 (no column calculation) and the rectangle size taken from
 * cellWidth/cellHeight minus 4: y = scrollTarget + arg2 - scroll + 2, and when flag 0x400 is
 * set, (cellHeight - 1) is subtracted from it. The color argument is read from D_80073520.
 * Matching note: the redundant (s32) cast on arg2 only fixes the operand order of the addu.
 * Seen in play (2026-11-12) in いちらん: drew the cursor frame on the selected row of the type list.
 */
void ScrollList_DrawCursor(ScrollMenu* arg0, s32 arg1, s32 arg2) {
    s32 sp2C;

    sp2C = (s32)arg2 + arg0->cursorY - arg0->scrollY + 2;
    if (arg0->scrollFlags & 0x400) {
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
 * Seen in play (2026-11-12) in いちらん: drew the main list's rows (フシギダネ, ヒトカゲ, ゼニガメ) every frame.
 */
void ScrollList_DrawItems(ScrollMenu* menu, s32 x, s32 y, s32 mask, s32 arg4) {
    s32 height = menu->cellHeight * menu->visibleRows;
    s32 i;
    s32 rowY;
    s32 end;
    s32 item;
    s32 f;
    s32* items = (s32*)menu->items->rows;

    gDPPipeSync(gDisplayListHead++);
    gDPSetScissor(gDisplayListHead++, G_SC_NON_INTERLACE, x, y, menu->cellWidth + x, y + height);
    ScrollList_AnimateScroll(menu);
    rowY = y - menu->scrollY % menu->cellHeight;
    i = menu->scrollY / menu->cellHeight;
    end = (menu->scrollY + height - 1) / menu->cellHeight + 1;
    for (; i < end; i++) {
        item = 0;
        f = 0;
        if (i < menu->items->count) {
            item = items[i];
            f = menu->itemFlags[i];
            if (i == menu->cursor) {
                f |= 0x12;
            }
        }
        menu->drawItem(x, rowY, (u8*)item, i, f & mask, arg4);
        rowY += menu->cellHeight;
    }
    gDPPipeSync(gDisplayListHead++);
    gDPSetScissor(gDisplayListHead++, G_SC_NON_INTERLACE, 0, 0, 640, 480);
    if (menu->options & 0x100000) {
        ScrollList_DrawScrollArrows(menu, x, y - 16, y + menu->cellHeight * menu->visibleRows, menu->cellWidth);
    }
    if ((menu->items->count > 0) && (mask & 2) && (menu->options & 0x10000)) {
        ScrollList_DrawCursor(menu, x, y);
    }
}

/**
 * Draws the visible rows inside a scissor box; items are stored inline.
 * Seen in play (2026-11-12) in せいとん > ポケモンのせいり: drew the left (てもち, x 0x34) and right (GBのボックス1,
 * x 0x180) Pokémon lists every frame.
 */
void ScrollList_DrawInlineItems(ScrollMenu* menu, s32 x, s32 y, s32 mask, s32 arg4) {
    ByteMatrix* def = menu->items;
    u8* items = def->rows;
    s32 height = menu->cellHeight * menu->visibleRows;
    s32 i;
    s32 rowY;
    s32 end;
    u8* item;
    s32 f;

    gDPPipeSync(gDisplayListHead++);
    gDPSetScissor(gDisplayListHead++, G_SC_NON_INTERLACE, x, y, menu->cellWidth + x, y + height);
    ScrollList_AnimateScroll(menu);
    rowY = y - menu->scrollY % menu->cellHeight;
    i = menu->scrollY / menu->cellHeight;
    end = (menu->scrollY + height - 1) / menu->cellHeight + 1;
    for (; i < end; i++) {
        item = NULL;
        f = 0;
        if (i < menu->items->count) {
            item = items + def->rowSize * i;
            f = menu->itemFlags[i];
            if (i == menu->cursor) {
                f |= 0x12;
            }
        }
        menu->drawItem(x, rowY, item, i, f & mask, arg4);
        rowY += menu->cellHeight;
    }
    gDPPipeSync(gDisplayListHead++);
    gDPSetScissor(gDisplayListHead++, G_SC_NON_INTERLACE, 0, 0, 640, 480);
    if (menu->options & 0x100000) {
        ScrollList_DrawScrollArrows(menu, x, y - 16, y + menu->cellHeight * menu->visibleRows, menu->cellWidth);
    }
    if ((menu->items->count > 0) && (mask & 2) && (menu->options & 0x10000)) {
        ScrollList_DrawCursor(menu, x, y);
    }
}

void func_8002F9D8(ScrollMenu* menu, s32 x, s32 y, s32 mask, s32 arg4) {
    ByteMatrix* def = menu->items;
    u8* items = def->rows;
    s32 pad[2]; // FAKE: stack padding
    s32 height = menu->cellHeight * menu->visibleRows;
    s32 i;
    s32 rowY;
    s32 end;
    u8* item;
    s32 f;

    gDPPipeSync(gDisplayListHead++);
    gDPSetScissor(gDisplayListHead++, G_SC_NON_INTERLACE, x, y, menu->cellWidth + x, y + height);
    ScrollList_AnimateScroll(menu);
    i = menu->scrollY / menu->cellHeight;
    rowY = y - menu->scrollY % menu->cellHeight + (menu->cursor - i) * menu->cellHeight;
    menu->drawItem(x, rowY, NULL, i, 0, arg4);
    rowY = y - menu->scrollY % menu->cellHeight;
    end = (menu->scrollY + height - 1) / menu->cellHeight;
    for (; i < end; i++) {
        item = NULL;
        f = 0;
        if (i < menu->items->count) {
            item = items + def->rowSize * i;
            f = menu->itemFlags[i];
            if (i == menu->cursor) {
                f |= 0x12;
            }
        }
        menu->drawItem(x, ((i >= menu->cursor) ? menu->cellHeight : 0) + rowY, item, i, f & mask, arg4);
        rowY += menu->cellHeight;
    }
    gDPPipeSync(gDisplayListHead++);
    gDPSetScissor(gDisplayListHead++, G_SC_NON_INTERLACE, 0, 0, 640, 480);
    if (menu->options & 0x100000) {
        menu->items->count++;
        ScrollList_DrawScrollArrows(menu, x, y - 16, y + menu->cellHeight * menu->visibleRows, menu->cellWidth);
        menu->items->count--;
    }
    if ((mask & 2) && (menu->options & 0x10000)) {
        ScrollList_DrawCursor(menu, x, y);
    }
}

/**
 * Moves a scrolling list's cursor and scroll position from controller input.
 * Seen in play (2026-11-12) in いちらん: while it ran, D-Down moved the row cursor from フシギダネ to
 * ヒトカゲ, then to ゼニガメ, where it stayed on the last row.
 */
u16 ScrollList_UpdateCursor(ScrollMenu* menu) {
    s32 prev_top;
    s32 prev;
    s32 room;
    s32 total;
    s32 page;
    s32 step;
    s32 delta;
    s32 end;

    prev = menu->cursor;
    prev_top = menu->pageTargetY;
    if (menu->items->count == 0) {
        return 0;
    }
    // Each pair of stores stays on one line: the assembler orders them differently when they are on separate lines.
    if (menu->controller->buttonPressed & 0x800) {
        menu->repeatTimer = 8; menu->inputDirection = 0x800;
    } else if (menu->controller->buttonPressed & 0x400) {
        menu->repeatTimer = 8; menu->inputDirection = 0x400;
    } else if (menu->controller->buttonPressed & 0x200) {
        menu->repeatTimer = 8; menu->inputDirection = 0x200;
    } else if (menu->controller->buttonPressed & 0x100) {
        menu->repeatTimer = 8; menu->inputDirection = 0x100;
    } else if (menu->repeatTimer > 0) {
        menu->repeatTimer--;
    } else {
        menu->inputDirection = menu->controller->buttonDown;
    }

    if ((menu->inputDirection & 0x800) && !(menu->scrollFlags & ~0x800)) {
        menu->scrollFlags |= 0x800;
        menu->cursorY -= (menu->cursorY < menu->cursorStep) ? menu->cursorY : menu->cursorStep;
        ScrollList_ScrollUpToCursor(menu);
        menu->cursor = menu->cursorY / menu->cellHeight;
        if (prev != menu->cursor) {
            func_8003F6AC(1);
        }
    } else if ((menu->inputDirection & 0x400) && !(menu->scrollFlags & ~0x400)) {
        if (menu->scrollFlags == 0) {
            menu->cursorY = menu->cursorY + menu->cellHeight - 1;
        }
        menu->scrollFlags |= 0x400;
        end = menu->cellHeight * menu->items->count;
        menu->cursorY += ((end - menu->cursorY - 1) < menu->cursorStep) ? (end - menu->cursorY - 1) : menu->cursorStep;
        ScrollList_ScrollDownToCursor(menu);
        menu->cursor = menu->cursorY / menu->cellHeight;
        if (prev != menu->cursor) {
            func_8003F6AC(1);
        }
    } else if ((menu->inputDirection & 0x200) && !(menu->scrollFlags & ~0x200)) {
        page = menu->cellHeight * menu->visibleRows;
        if (menu->scrollFlags == 0) {
            menu->pageTargetY = menu->scrollY;
        }
        menu->scrollFlags |= 0x200;
        if (menu->scrollY < menu->pageStep) {
            delta = menu->scrollY;
        } else {
            delta = menu->pageStep;
        }
        menu->scrollY -= delta;
        menu->cursorY -= delta;
        menu->cursor = menu->cursorY / menu->cellHeight;
        if (menu->scrollY < menu->pageTargetY) {
            menu->pageTargetY -= (page < menu->pageTargetY) ? page : menu->pageTargetY;
        }
        if (prev_top != menu->pageTargetY) {
            func_8003F6AC(1);
        }
    } else if ((menu->inputDirection & 0x100) && !(menu->scrollFlags & ~0x100)) {
        total = menu->cellHeight * menu->items->count;
        page = menu->cellHeight * menu->visibleRows;
        if (menu->scrollFlags == 0) {
            menu->pageTargetY = menu->scrollY;
        }
        menu->scrollFlags |= 0x100;
        room = total - menu->scrollY - page;
        if (room <= 0) {
            room = 0;
        }
        step = (room < menu->pageStep) ? room : menu->pageStep;
        menu->scrollY += step;
        menu->cursorY += step;
        menu->cursor = menu->cursorY / menu->cellHeight;
        if (menu->pageTargetY < menu->scrollY) {
            room = total - page - menu->pageTargetY;
            menu->pageTargetY += (page < room) ? page : room;
        }
        if (prev_top != menu->pageTargetY) {
            func_8003F6AC(1);
        }
    }
    return menu->scrollFlags;
}

u16 func_80030230(ScrollMenu* menu) {
    s32 prev_top;
    s32 prev;
    s32 room;
    s32 total;
    s32 page;
    s32 step;
    s32 delta;
    s32 end;

    prev = menu->cursor;
    prev_top = menu->pageTargetY;
    if (menu->items->count == 0) {
        return 0;
    }
    // Each pair of stores stays on one line: the assembler orders them differently when they are on separate lines.
    if (menu->controller->buttonPressed & 0x800) {
        menu->repeatTimer = 8; menu->inputDirection = 0x800;
    } else if (menu->controller->buttonPressed & 0x400) {
        menu->repeatTimer = 8; menu->inputDirection = 0x400;
    } else if (menu->controller->buttonPressed & 0x200) {
        menu->repeatTimer = 8; menu->inputDirection = 0x200;
    } else if (menu->controller->buttonPressed & 0x100) {
        menu->repeatTimer = 8; menu->inputDirection = 0x100;
    } else if (menu->repeatTimer > 0) {
        menu->repeatTimer--;
    } else {
        menu->inputDirection = menu->controller->buttonDown;
    }

    if ((menu->inputDirection & 0x800) && !(menu->scrollFlags & ~0x800)) {
        menu->scrollFlags |= 0x800;
        menu->cursorY -= (menu->cursorY < menu->cursorStep) ? menu->cursorY : menu->cursorStep;
        ScrollList_ScrollUpToCursor(menu);
        menu->cursor = menu->cursorY / menu->cellHeight;
        if (prev != menu->cursor) {
            func_8003F6AC(1);
        }
    } else if ((menu->inputDirection & 0x400) && !(menu->scrollFlags & ~0x400)) {
        if (menu->scrollFlags == 0) {
            menu->cursorY = menu->cursorY + menu->cellHeight - 1;
        }
        menu->scrollFlags |= 0x400;
        end = menu->cellHeight * (menu->items->count + 1);
        menu->cursorY += ((end - menu->cursorY - 1) < menu->cursorStep) ? (end - menu->cursorY - 1) : menu->cursorStep;
        ScrollList_ScrollDownToCursor(menu);
        menu->cursor = menu->cursorY / menu->cellHeight;
        if (prev != menu->cursor) {
            func_8003F6AC(1);
        }
    } else if ((menu->inputDirection & 0x200) && !(menu->scrollFlags & ~0x200)) {
        page = menu->cellHeight * menu->visibleRows;
        if (menu->scrollFlags == 0) {
            menu->pageTargetY = menu->scrollY;
        }
        menu->scrollFlags |= 0x200;
        if (menu->scrollY < menu->pageStep) {
            delta = menu->scrollY;
        } else {
            delta = menu->pageStep;
        }
        menu->scrollY -= delta;
        menu->cursorY -= delta;
        menu->cursor = menu->cursorY / menu->cellHeight;
        if (menu->scrollY < menu->pageTargetY) {
            menu->pageTargetY -= (page < menu->pageTargetY) ? page : menu->pageTargetY;
        }
        if (prev_top != menu->pageTargetY) {
            func_8003F6AC(1);
        }
    } else if ((menu->inputDirection & 0x100) && !(menu->scrollFlags & ~0x100)) {
        total = menu->cellHeight * menu->items->count;
        page = menu->cellHeight * menu->visibleRows;
        if (menu->scrollFlags == 0) {
            menu->pageTargetY = menu->scrollY;
        }
        menu->scrollFlags |= 0x100;
        room = total - menu->scrollY - page;
        if (room <= 0) {
            room = 0;
        }
        step = (room < menu->pageStep) ? room : menu->pageStep;
        menu->scrollY += step;
        menu->cursorY += step;
        menu->cursor = menu->cursorY / menu->cellHeight;
        if (menu->pageTargetY < menu->scrollY) {
            room = total - page - menu->pageTargetY;
            menu->pageTargetY += (page < room) ? page : room;
        }
        if (prev_top != menu->pageTargetY) {
            func_8003F6AC(1);
        }
    }
    return menu->scrollFlags;
}

/**
 * Puts the cursor on row `arg1` and scrolls up to it if needed.
 * Seen in play (2026-11-13) (tour of menus and a COM battle): ran in Free Battle setup.
 * @unverified Name and comment guessed from the code.
 */
void ScrollList_SetCursor(ScrollMenu* arg0, u32 arg1) {
    s32 v;

    arg0->repeatTimer = 0;
    arg0->cursor = arg1;
    arg0->cursorY = arg0->cellHeight * arg1;
    if (arg0->cursorY < arg0->scrollY) {
        arg0->scrollY = arg0->cursorY;
    } else {
        v = (arg0->cursorY + arg0->cellHeight) - (arg0->visibleRows * arg0->cellHeight);
        if (arg0->scrollY < v) {
            arg0->scrollY = v;
        }
    }
    arg0->pageTargetY = arg0->scrollY;
}

/**
 * Puts the cursor on row `arg1`, keeping its distance from the top of the visible area where possible.
 * Seen in play (2026-11-13) ran once when C-Right switched the Pokédex list from number order to
 * アイウエオ order; the list was re-sorted with the cursor kept on the top visible row.
 */
void ScrollList_SetCursorKeepOffset(ScrollMenu* arg0, s32 arg1) {
    s32 temp_a2;
    s32 temp_v0;
    s32 var_a1;
    s32 var_v0;
    s32 var_v1;

    arg0->repeatTimer = 0;
    arg0->cursor = arg1;
    temp_v0 = arg0->cursorY - arg0->scrollY;
    arg0->cursorY = arg0->cellHeight * arg1;

    temp_a2 = arg0->items->count - arg0->visibleRows;

    var_a1 = temp_a2 = (temp_a2 > 0) ? temp_a2 : 0;
    temp_a2 *= arg0->cellHeight;

    var_v0 = (arg0->cursorY - temp_v0 > 0) ? arg0->cursorY - temp_v0 : 0;

    var_v1 = (var_v0 < temp_a2) ? var_v0 : temp_a2;
    arg0->scrollY = var_v1;
    arg0->pageTargetY = var_v1;
}

/** Sets the selected cell of a paged grid widget, applying a page offset. */
void WidgetTree_SetPagedGridSelectionWithOffset(ScrollMenu* arg0, s32 arg1, s32 arg2) {
    s32 temp_a2;
    s32 temp_a2_2;
    s32 temp_lo;
    s32 temp_v1;
    s32 var_v0_2;
    ByteMatrix* temp_v0 = arg0->items;

    if (temp_v0->count != 0) {
        arg0->repeatTimer = 0;
        temp_v1 = temp_v0->count - 1;
        if (arg1 >= temp_v1) {
            arg1 = temp_v1;
        }
        arg0->cursor = arg1;
        arg0->cursorY = arg0->cellHeight * arg1;

        temp_a2 = temp_v0->count - arg0->visibleRows;
        temp_lo = arg0->cellHeight * ((temp_a2 > 0) ? temp_a2 : 0);

        temp_a2_2 = arg0->cursorY - arg2 * arg0->cellHeight;
        if (temp_a2_2 > 0) {
            var_v0_2 = temp_a2_2;
        } else {
            var_v0_2 = 0;
        }

        temp_v1 = (var_v0_2 < temp_lo) ? var_v0_2 : temp_lo;
        arg0->scrollY = temp_v1;
        arg0->pageTargetY = temp_v1;
    }
}

void ScrollGrid_SetItems(ScrollMenu* arg0, ByteMatrix* arg1, u16* arg2);
extern Controller* D_800603C0;
/**
 * Sets up a scrolling grid menu: draw callback, cell size, columns, rows and item table.
 * Seen in play (2026-11-13) ran once as the tournament entry screen built the レンタルポケモン grid (スピアー,
 * オニドリル, ピカチュウ ... at L30).
 */
void ScrollGrid_Init(ScrollMenu* arg0, ByteMatrix* arg1, u16* arg2, s32 arg3, s32 arg4, MenuDrawItemFunc arg5, s32 arg6, s32 arg7) {
    arg0->visibleRows = arg4;
    arg0->cellWidth = arg6;
    arg0->cellHeight = arg7;
    arg0->drawItem = arg5;
    ScrollGrid_SetItems(arg0, arg1, arg2);
    arg0->unk_1C = 0xC00;
    arg0->options = 0x100000;
    arg0->controller = D_800603C0;
    arg0->inputDirection = arg0->scrollFlags = 0;
    arg0->scrollY = 0;
    arg0->cursorY = 0;
    arg0->cursorStep = arg0->cellHeight * 4 / 10;
    arg0->pageStep = arg0->cellHeight * arg0->visibleRows * 2 / 10;
    arg0->repeatTimer = 8;
    arg0->cursorX = 0;
    arg0->columns = arg3;
    arg0->cursorStepX = arg0->cellWidth * 4 / 10;
}

void Menu_ClearItemFlags(Menu* arg0);

/**
 * Points the grid at item table `arg1` with flags `arg2` and resets the cursor.
 * Seen in play (2026-11-13) ran once as the tournament entry screen filled the レンタルポケモン grid.
 */
void ScrollGrid_SetItems(ScrollMenu* arg0, ByteMatrix* arg1, u16* arg2) {
    arg0->items = arg1;
    arg0->itemFlags = arg2;
    arg0->cursor = 0;
    Menu_ClearItemFlags((Menu*)arg0);
}

/**
 * Scrolls up when the cursor row is above the visible area.
 * Not reached in play (2026-11-13): did not run in a tour of the main menu, Pokédex, party, Lab,
 * registration, Free Battle setup and a COM battle (opening, a switch, running, a Pound turn).
 * @unverified Name and comment guessed from the code.
 */
void ScrollGrid_ScrollUpToCursor(ScrollMenu* arg0) {
    s32 temp_v0;

    temp_v0 = arg0->cursorY;
    if (temp_v0 < arg0->scrollY) {
        arg0->scrollY = temp_v0;
    }
}

/**
 * Scrolls down when the cursor row is below the visible area.
 * Not reached in play (2026-11-13): did not run in a tour of the main menu, Pokédex, party, Lab,
 * registration, Free Battle setup and a COM battle (opening, a switch, running, a Pound turn).
 * @unverified Name and comment guessed from the code.
 */
void ScrollGrid_ScrollDownToCursor(ScrollMenu* arg0) {
    s32 temp_v0 = arg0->cursorY - arg0->cellHeight * arg0->visibleRows + 1;

    if (arg0->scrollY < temp_v0) {
        arg0->scrollY = temp_v0;
    }
}

/**
 * Moves the drawn scroll position toward the target a step at a time.
 * Seen in play (2026-11-13) ran when the rental grid opened on the entry screen (Free Battle, L1-30
 * rules, six L30 rentals vs COM).
 * @unverified Name and comment guessed from the code.
 */
void ScrollGrid_AnimateScroll(ScrollMenu* menu) {
    s32 t1;
    s32 t3;
    s32 t2;
    s32 speed;

    if (menu->scrollFlags & 0x800) {
        if (!(menu->inputDirection & 0x800)) {
            speed = menu->cursorStep;
            t1 = (menu->cursor / menu->columns) * menu->cellHeight;

            menu->cursorY = menu->cursorY - (((menu->cursorY - t1) < speed) ? (menu->cursorY - t1) : speed);
            ScrollGrid_ScrollUpToCursor(menu);
            if (t1 == menu->cursorY) {
                menu->scrollFlags &= ~0x800;
            }
        }
    } else if (menu->scrollFlags & 0x400) {
        if (!(menu->inputDirection & 0x400)) {
            t2 = ((menu->cursor / menu->columns) + 1) * menu->cellHeight - 1;
            speed = menu->cursorStep;
            menu->cursorY += (((t2 - menu->cursorY) < speed) ? (t2 - menu->cursorY) : speed);
            ScrollGrid_ScrollDownToCursor(menu);
            if (t2 == menu->cursorY) {
                menu->scrollFlags &= ~0x400;
                menu->cursorY = menu->cursorY - menu->cellHeight + 1;
            }
        }
    } else if (menu->scrollFlags & 0x200) {
        if (!(menu->inputDirection & 0x200)) {
            t3 = (menu->cursor % menu->columns) * menu->cellWidth;

            menu->cursorX = menu->cursorX - (((menu->cursorX - t3) < menu->cursorStepX) ? (menu->cursorX - t3) : menu->cursorStepX);
            if (t3 == menu->cursorX) {
                menu->scrollFlags &= ~0x200;
            }
        }
    } else if (menu->scrollFlags & 0x100) {
        if (!(menu->inputDirection & 0x100)) {
            t3 = ((menu->cursor % menu->columns) + 1) * menu->cellWidth - 1;
            menu->cursorX += (((t3 - menu->cursorX) < menu->cursorStepX) ? (t3 - menu->cursorX) : menu->cursorStepX);
            if (t3 == menu->cursorX) {
                menu->scrollFlags &= ~0x100;
                menu->cursorX = menu->cursorX - menu->cellWidth + 1;
            }
        }
    }
    menu->inputDirection = 0;
}

/**
 * Draws the up and down arrows when there are rows above or below the visible area.
 * Seen in play (2026-11-13) ran while the tournament's レンタルポケモン grid had more rows below the
 * visible ones.
 */
void ScrollGrid_DrawScrollArrows(ScrollMenu* menu, s32 x, s32 y) {
    s32 height = menu->cellHeight * menu->visibleRows;
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
    tex = (menu->scrollY > 0) ? D_04003AD8 : D_040044F8;
    func_8001B884(arrowX, topY, 0x12, 0x10, tex, 0x14, 0x200000);
    more = menu->scrollY + height < ((menu->items->count + menu->columns - 1) / menu->columns) * menu->cellHeight;
    func_8001B884(arrowX, bottomY, 0x12, 0x10, more ? D_04003D60 : D_04004780, 0x14, 0x200000);
    gSPDisplayList(gDisplayListHead++, D_80073438);
}


/**
 * Draws a rectangle (via Ui_DrawRoundedFrame) for the cursor of a paged grid menu.
 * The column is cursor % columns, so x = column * cellWidth + arg1. y is
 * scrollTarget + arg2 - scroll + 2; when flag 0x400 is set, (cellHeight - 1)
 * is subtracted from it. The rectangle size is the cell size minus 4 in each
 * direction, and the color argument is read from D_80073520.
 * Seen in play (2026-11-13) drew the cursor box on the tournament's レンタルポケモン grid.
 */
void ScrollGrid_DrawCursor(ScrollMenu* arg0, s32 arg1, s32 arg2) {
    s32 sp2C;
    s32 sp28;

    sp2C = arg0->cursorY + arg2 - arg0->scrollY + 2;
    sp28 = (arg0->cursor % arg0->columns) * arg0->cellWidth + arg1;
    if (arg0->scrollFlags & 0x400) {
        sp2C = sp2C - arg0->cellHeight + 1;
    }
    Ui_DrawRoundedFrame(sp28, sp2C, arg0->cellWidth - 4, arg0->cellHeight - 4, *(Color_RGBA8*)D_80073520);
}

void ScrollGrid_DrawScrollArrows(ScrollMenu*, s32, s32);

/**
 * Grid version of ScrollList_DrawInlineItems: sets the scissor to the menu area (columns * cellWidth by
 * rows * cellHeight at x, y), calls ScrollGrid_AnimateScroll, then draws every visible cell i through
 * menu->draw(column x, row y, item, i, flags & mask, arg4). The cell's flags come from
 * menu->flags and get 0x12 for the cursor cell; cells past def->itemCount get no item and
 * flags 0. Afterwards the scissor is reset to the full screen, ScrollGrid_DrawScrollArrows draws when option
 * bit 0x100000 is set and ScrollGrid_DrawCursor (cursor box) draws when the list is non-empty, mask
 * bit 2 is set and option bit 0x10000 is set.
 * Seen in play (2026-11-13) drew the tournament's レンタルポケモン grid every frame.
 */
void ScrollGrid_DrawItems(ScrollMenu* menu, s32 x, s32 y, s32 mask, s32 arg4) {
    s32 width = menu->cellWidth * menu->columns;
    ByteMatrix* def = menu->items;
    u8* items = def->rows;
    s32 height = menu->cellHeight * menu->visibleRows;
    s32 i;
    s32 end;
    s32 baseY;
    u8* item;
    s32 f;

    gDPPipeSync(gDisplayListHead++);
    gDPSetScissorFrac(gDisplayListHead++, G_SC_NON_INTERLACE, x * 4.0f, y * 4.0f, (x + width) * 4.0f, (y + height) * 4.0f);
    ScrollGrid_AnimateScroll(menu);
    baseY = y - menu->scrollY;
    i = (menu->scrollY / menu->cellHeight) * menu->columns;
    end = ((menu->scrollY + height - 1) / menu->cellHeight + 1) * menu->columns;
    for (; i < end; i++) {
        item = NULL;
        f = 0;
        if (i < menu->items->count) {
            item = items + def->rowSize * i;
            f = menu->itemFlags[i];
            if (i == menu->cursor) {
                f |= 0x12;
            }
        }
        menu->drawItem((i % menu->columns) * menu->cellWidth + x, (i / menu->columns) * menu->cellHeight + baseY, item, i, f & mask, arg4);
    }
    gDPPipeSync(gDisplayListHead++);
    gDPSetScissor(gDisplayListHead++, G_SC_NON_INTERLACE, 0, 0, 640, 480);
    if (menu->options & 0x100000) {
        ScrollGrid_DrawScrollArrows(menu, x, y);
    }
    if ((menu->items->count > 0) && (mask & 2) && (menu->options & 0x10000)) {
        ScrollGrid_DrawCursor(menu, x, y);
    }
}

/**
 * Returns how many cells the current row has (the last row can be short).
 * Not reached in play (2026-11-13): did not run in a tour of the main menu, Pokédex, party, Lab,
 * registration, Free Battle setup and a COM battle (opening, a switch, running, a Pound turn).
 * @unverified Name and comment guessed from the code.
 */
s32 ScrollGrid_GetRowLength(ScrollMenu* menu) {
    s32 page_count = (menu->items->count + menu->columns - 1) / menu->columns;
    s32 page = menu->cursorY / menu->cellHeight;
    s32 next_page = page + 1;
    s32 remainder = menu->items->count % menu->columns;

    return ((page_count == next_page) && (remainder != 0)) ? remainder : menu->columns;
}

/**
 * Moves the scrolling grid's cursor with the D-Pad and scrolls to keep it visible.
 * Seen in play (2026-11-13) ran every frame while the cursor was in the tournament's レンタルポケモン grid.
 */
u16 ScrollGrid_UpdateCursor(ScrollMenu *menu)
{
  long new_var; // FAKE
  s32 prev = menu->cursor;
  s32 lim;
  s32 w;
  if (menu->items->count == 0)
  {
    return 0;
  }
  if (menu->controller->buttonPressed & 0x800)
  { menu->repeatTimer = 8; menu->inputDirection = 0x800; }
  else
    if (menu->controller->buttonPressed & 0x400)
  { menu->repeatTimer = 8; menu->inputDirection = 0x400; }
  else
    if (menu->controller->buttonPressed & 0x200)
  { menu->repeatTimer = 8; menu->inputDirection = 0x200; }
  else
    if (menu->controller->buttonPressed & 0x100)
  { menu->repeatTimer = 8; menu->inputDirection = 0x100; }
  else
    if (menu->repeatTimer > 0)
  {
    menu->repeatTimer--;
  }
  else
  {
 do { menu->inputDirection = menu->controller->buttonDown; } while (0); // FAKE
  }
  if ((menu->inputDirection & 0x800) && (!(menu->scrollFlags & (~0x800))))
  {
    menu->scrollFlags |= 0x800;
    menu->cursorY -= (menu->cursorY < menu->cursorStep) ? (menu->cursorY) : (menu->cursorStep);
    ScrollGrid_ScrollUpToCursor(menu);
    menu->cursor = ((menu->cursorY / menu->cellHeight) * menu->columns) + (menu->cursorX / menu->cellWidth);
  }
  else
    if ((menu->inputDirection & 0x400) && (!(menu->scrollFlags & (~0x400))))
  {
    if (menu->scrollFlags == 0)
    {
      menu->cursorY = (menu->cursorY + menu->cellHeight) - 1;
    }
    menu->scrollFlags |= 0x400;
    new_var = (((menu->items->count + menu->columns) - 1) / menu->columns) * menu->cellHeight;
    menu->cursorY += (((new_var - menu->cursorY) - 1) < menu->cursorStep) ? ((new_var - menu->cursorY) - 1) : (menu->cursorStep);
    ScrollGrid_ScrollDownToCursor(menu);
    lim = (ScrollGrid_GetRowLength((ScrollMenu *) menu) - 1) * menu->cellWidth;
    if (lim < menu->cursorX)
    {
      menu->cursorX = lim;
    }
    menu->cursor = ((menu->cursorY / menu->cellHeight) * menu->columns) + (menu->cursorX / menu->cellWidth);
  }
  else
    if ((menu->inputDirection & 0x200) && (!(menu->scrollFlags & (~0x200))))
  {
    menu->scrollFlags |= 0x200;
    if (menu->cursorX < menu->cursorStepX)
    {
      menu->cursorX += menu->cellWidth * ScrollGrid_GetRowLength((ScrollMenu *) menu);
    }
    menu->cursorX -= menu->cursorStepX;
    menu->cursor = ((menu->cursorY / menu->cellHeight) * menu->columns) + (menu->cursorX / menu->cellWidth);
  }
  else
    if ((menu->inputDirection & 0x100) && (!(menu->scrollFlags & (~0x100))))
  {
    if (menu->scrollFlags == 0)
    {
      menu->cursorX = (menu->cursorX + menu->cellWidth) - 1;
    }
    menu->scrollFlags |= 0x100;
    lim = ScrollGrid_GetRowLength((ScrollMenu *) menu);
    w = menu->cellWidth;
    lim = w * lim; if (w) {} // FAKE: found by the traced-allocator lever sweep; keeps w live so the sum takes a2
    if ((menu->cursorX + menu->cursorStepX) >= lim)
    {
      menu->cursorX -= lim;
    }
    menu->cursorX += menu->cursorStepX;
    menu->cursor = ((menu->cursorY / menu->cellHeight) * menu->columns) + (menu->cursorX / w);
  }
  if (prev != menu->cursor)
  {
    func_8003F6AC(1);
  }
  return menu->scrollFlags;
}

/**
 * Puts the cursor on cell `arg1` and scrolls to it.
 * Seen in play (2026-11-13) ran when a rental was picked from the tournament's レンタルポケモン grid and
 * the cursor came back to it.
 */
void ScrollGrid_SetCursor(ScrollMenu* arg0, s32 arg1) {
    s32 v;
    arg0->repeatTimer = 0;
    arg0->cursor = arg1;
    arg0->cursorY = (arg1 / arg0->columns) * arg0->cellHeight;
    arg0->cursorX = (arg1 % arg0->columns) * arg0->cellWidth;
    if (arg0->cursorY < arg0->scrollY) {
        arg0->scrollY = arg0->cursorY;
    } else {
        v = (arg0->cursorY + arg0->cellHeight) - arg0->visibleRows * arg0->cellHeight;
        if (arg0->scrollY < v) {
            arg0->scrollY = v;
        }
    }
    arg0->pageTargetY = arg0->scrollY;
}

void ScrollGrid_SetCursor();                 /* extern */

/**
 * Moves the cursor past disabled cells and scrolls to it.
 * Seen in play (2026-11-13) ran when the cursor came back to the tournament's レンタルポケモン grid after a
 * pick.
 */
void ScrollGrid_SyncCursor(ScrollMenu* arg0) {
    Menu_SkipDisabledForward((Menu*)arg0);
    ScrollGrid_SetCursor(arg0, arg0->cursor);
}
