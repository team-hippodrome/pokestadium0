/* Fixed-layout split; original translation-unit boundaries remain unconfirmed. */

#include "global.h"
#include "lab_pokemon_list.h"
#include "m2c_macros.h"

extern u8 D_80073520[];
M2C_UNK Ui_DrawRoundedFrame(s32, s32, s32, s32, Color_RGBA8);

M2C_UNK func_89109E5C(s32, s32, s32, s32);
M2C_UNK func_89109FE0(s32);
M2C_UNK func_8910A03C(s32);

extern s32 D_8910A7F8[3];
void func_80027410(void*, void*, s32, s32, s32);
void func_89109990(void*, void*, void*, s32);

extern s32 D_800603C0;
void func_8000B2F4(s32);

void Window_SetRect(s8 *, s32, s32, s32, s32);
void func_80027804(s8*, s8*, s32, s32);
void func_89109B60(s8*);
M2C_UNK func_89109C6C(s32, s32);                    /* extern */
void func_80027D68(void*, s32);
void ScrollList_Init(s8*, s8*, s8*, s32, void*, s32, s32);
void LabPCList_DrawMonRow();
extern s32 D_8910D990[];
extern Color_RGBA8 D_8910A7F4;
extern u8 D_8910A844[];
extern u8 D_8910A848[];
extern u8 D_8910A804[];
extern u8 D_8910A84C[];

void func_891000BC(s32 arg0);
void func_89100294(LabPCListScreen* arg0);
s32 LabPCList_GetColumnCursorX(LabPCListScreen* arg0);
extern M2C_UNK D_800734A8;

extern Gfx D_80060270[];
extern Color_RGBA8 D_8910A85C[2][2];
extern Color_RGBA8 D_8910A860;
extern Color_RGBA8 D_8910A86C[2][2];
extern SpeciesInfo D_80064C5C[];
extern char D_8910DBCC[];
extern char D_8910DBD8[];
extern char D_8910DBDC[];
extern char D_8910DBE0[];
extern char D_8910DBE4[];
extern char D_8910DBE8[];
extern char D_8910DBEC[];
void func_80029028(s32, s32, s32, s32, Color_RGBA8);
void Ui_FillRectHighlighted(s32, s32, s32, s32, Color_RGBA8);
void Ui_DrawNumberZeroPadded(s32, s32, s32, s32);
void Font_SetColorForFlags(s32);
void func_89101238(s32, s32, s8*, s32, s32);

s32 Window_DrawAnimatedFrame(void);
void func_8002C5A4(s32, s32, s32);
void Window_DrawFrame(s8*);
void Ui_DrawTexturedDivider(s32, s32, s32, u8*);
void ScrollList_DrawScrollArrows(s8*, s32, s32, s32, s32);
void ScrollList_DrawItems(s8*, s32, s32, s32, s8*);
void LabPCList_DrawDetailColumns(s8*, s32, s32, s32);
void LabPCList_DrawPopupMenu(LabPopupMenu*, s32);
void LabPCList_DrawLevelInputWindow(LabLevelInputWindow*);
void TextBox_Draw(s8*);
extern u8 D_8007356C[];
extern Gfx D_80060270[];
extern Color_RGBA8 D_8910A88C;
void LabPCList_DrawRowCursor(s8*, s32, s32);
void LabPCList_DrawPageHint(LabPCListScreen*);
void func_89100688(s8*);
void LabPCList_DrawHeaderCursor(LabPCListScreen*);
/**
 * Draws the lab PC list screen: page hint, column headers and rows.
 * Seen in play (2026-11-12): the いちらん list with the page hint, column headers and rows.
 */
void LabPCList_DrawListScreen(LabPCListScreen* arg0) {
    s32 sel;
    s32 y;
    s32 flags[2]; // FAKE (only [0] is used; has to live on the stack)

    if (Window_DrawAnimatedFrame() != 0) {
        return;
    }
    func_8002C5A4(arg0->window.frame.x, arg0->window.frame.y - 0xA, 0x1F4);
    Window_DrawFrame((s8*)&arg0->headerFrame);
    Ui_DrawTexturedDivider(arg0->window.frame.x, arg0->window.frame.y + 0x23, arg0->window.frame.width, D_8007356C);
    LabPCList_DrawPageHint(arg0);
    ScrollList_DrawScrollArrows((s8*)&arg0->list, arg0->listFrame.x, arg0->listFrame.y - 0x10,
                  arg0->listFrame.y + arg0->listFrame.height, arg0->listFrame.width);
    y = arg0->listFrame.y + 0x16;
    if (arg0->focus == 0) {
        flags[0] = ((arg0->state != 0) ? 0x10 : 0) | 2;
    } else {
        flags[0] = 0;
    }
    ScrollList_DrawItems((s8*)&arg0->list, arg0->listFrame.x, y, flags[0] | 0xFFED, arg0);
    sel = (arg0->focus == 1) ? (((arg0->state != 0) ? 0x10 : 0) | 2) : 0;
    LabPCList_DrawDetailColumns(arg0, arg0->listFrame.x, arg0->listFrame.y, sel);
    gSPDisplayList(gDisplayListHead++, D_80060270);
    func_80029028(arg0->listFrame.x, arg0->listFrame.y + 0x14, arg0->listFrame.width, 2, D_8910A88C);
    func_80029028(arg0->listFrame.x + 0x76, arg0->listFrame.y, 2, arg0->listFrame.height, D_8910A88C);
    if (arg0->state == 0) {
        switch (arg0->focus) {
            case 0:
                LabPCList_DrawRowCursor((s8*)&arg0->list, arg0->listFrame.x, y);
                break;
            case 1:
                func_89100688(arg0);
                break;
            case 2:
                LabPCList_DrawHeaderCursor(arg0);
                break;
        }
    }
    switch (arg0->state) {
        case 0:
            break;
        case 1:
            func_89105E70(&arg0->sourceSelectWindow, 2);
            break;
        case 2:
        case 3:
            LabPCList_DrawPopupMenu(&arg0->popup, 2);
            break;
        case 4:
            LabPCList_DrawLevelInputWindow(&arg0->levelInputWindow);
            break;
        case 5:
            LabPCList_DrawTypeFilter(&arg0->typeFilterWindow);
            break;
        case 6:
            LabPCList_DrawMoveFilter(&arg0->moveFilterWindow);
            break;
        case 7:
            LabPCList_DrawPopupMenu(&arg0->popup, 2);
            break;
        case 8:
            LabPCList_DrawPopupMenu(&arg0->popup, 0x10);
            LabPCList_DrawPopupMenu(&arg0->subPopup, 2);
            break;
        case 9:
            LabPCList_DrawPopupMenu(&arg0->popup, 0x10);
            LabPCList_DrawPopupMenu(&arg0->subPopup, 0x10);
            LabPCList_DrawPopupMenu(&arg0->subPopup2, 2);
            break;
        case 10:
            LabPCList_DrawPopupMenu(&arg0->popup, 0x10);
            LabPCList_DrawPopupMenu(&arg0->subPopup, 0x10);
            LabPCList_DrawPopupMenu(&arg0->subPopup2, 2);
            break;
        case 11:
        case 12:
            TextBox_Draw((s8*)arg0->textBox);
            break;
    }
}

/**
 * Returns whether any of filter flags `arg1` is active.
 * Seen in play (2026-11-12) in いちらん: opening レベルをきめてあつめる called this with 1; it returned 0 with
 * no level filter, and 1 once 006から100 had been applied (かいじょ is then usable).
 */
s32 LabPCList_HasFilterFlag(LabPCListScreen* arg0, s32 arg1) {
    return (arg0->activeFilters & arg1) != 0;
}

/**
 * Turns on filter flags `arg1`.
 * Seen in play (2026-11-12) in いちらん: choosing どく in タイプであつめる and pressing あつめる called this with
 * 2, the flag word at +0x7C went 0 -> 2, and the list then showed only フシギダネ.
 */
void LabPCList_SetFilterFlag(LabPCListScreen* arg0, s32 arg1) {
    arg0->activeFilters = (s32) (arg0->activeFilters | arg1);
}

/**
 * Turns off filter flags `arg1`.
 * Seen in play (2026-11-12) in いちらん: pressing かいじょ in タイプであつめる called this with 2, the flag word
 * at +0x7C went 2 -> 0, and all three party Pokémon came back.
 */
void LabPCList_ClearFilterFlag(LabPCListScreen* arg0, M2C_UNK arg1) {
    arg0->activeFilters = (s32) (arg0->activeFilters & ~arg1);
}

/**
 * Turns off every filter flag.
 * Seen in play (2026-11-12) in いちらん: すべてのせんたくをやめる took the flag word from 0x20 to 0.
 */
void LabPCList_ClearFilterFlags(LabPCListScreen* arg0) {
    arg0->activeFilters = 0;
}

// FAKE: decomp slop. Raw pointer-offset casts stand in for struct fields.
/**
 * Toggles filter flags `arg1` and returns whether they are now on.
 * Seen in play (2026-11-12) in いちらん: バトルようのポケモンをあつめる called this with 0x20; the flag word went 0
 * -> 0x20 and it returned 0x20 (on). The menu entry then read バトルようのポケモンをかいじょする.
 */
s32 LabPCList_ToggleFilterFlag(s8 *arg0, s32 arg1)
{
  s32 temp_t7;
  s32 new_var; // FAKE: permuter temp
  new_var = arg1;
  temp_t7 = ((*((s32 *) (((s8 *) arg0) + 0x7C))) ^ new_var) & 0xFFFFFFFFFFFFFFFFu;
  *((s32 *) (((s8 *) arg0) + 0x7C)) = temp_t7;
  return temp_t7 & new_var;
}

extern s32 D_8910D990[];
void ScrollList_SetItems(ScrollList*, PointerList*, u16*);
void func_80027D94(void*, PointerList*, void*, void*);
void func_80027D68(void*, s32);
s32 func_891096F4();
s32 func_89109720();
s32 func_891097E4();
s32 func_89109884();
s32 func_89109898();
s32 func_89109960();
/**
 * Rebuilds the visible list from the source boxes using the active filter flags.
 * Seen in play (2026-11-12) in いちらん (party list: フシギダネ, ヒトカゲ, ゼニガメ): ran when OK was pressed on
 * 「どこのポケモンを いちらん するか」 with てもち chosen, and the list then showed the three party Pokémon.
 */
M2C_UNK LabPCList_ApplyFiltersAndSort(LabPCListScreen* arg0) {
    ScrollList_SetItems(&arg0->list, &arg0->rows, arg0->rowFlags);
    if (arg0->activeFilters != 0) {
        if (arg0->activeFilters & 1) {
            func_80027D94(arg0->list.items, &arg0->filteredRows, func_891096F4, &arg0->levelFilterMin);
            ScrollList_SetItems(&arg0->list, &arg0->filteredRows, arg0->rowFlags);
        }
        if (arg0->activeFilters & 2) {
            func_80027D94(arg0->list.items, &arg0->filteredRows, func_89109720, &arg0->typeFilterCount);
            ScrollList_SetItems(&arg0->list, &arg0->filteredRows, arg0->rowFlags);
        }
        if (arg0->activeFilters & 4) {
            func_80027D94(arg0->list.items, &arg0->filteredRows, func_891097E4, &arg0->moveFilterMoves);
            ScrollList_SetItems(&arg0->list, &arg0->filteredRows, arg0->rowFlags);
        }
        if (arg0->activeFilters & 8) {
            func_80027D94(arg0->list.items, &arg0->filteredRows, func_89109884, &arg0->unk_9E58);
            ScrollList_SetItems(&arg0->list, &arg0->filteredRows, arg0->rowFlags);
        }
        if (arg0->activeFilters & 0x10) {
            func_80027D94(arg0->list.items, &arg0->filteredRows, func_89109898, &arg0->sameTypeFilterCount);
            ScrollList_SetItems(&arg0->list, &arg0->filteredRows, arg0->rowFlags);
        }
        if (arg0->activeFilters & 0x20) {
            func_80027D94(arg0->list.items, &arg0->filteredRows, func_89109960, NULL);
            ScrollList_SetItems(&arg0->list, &arg0->filteredRows, arg0->rowFlags);
        }
    }
    func_80027D68(arg0->list.items, D_8910D990[arg0->sortKey]);
}

typedef struct Pair8910D910 { void* a; s32 b; } Pair8910D910;
extern Pair8910D910 D_8910D910[];
void LabPCList_InitPopupMenu(LabPopupMenu*, void*, s8*, s32, s32);
void LabPCList_PlacePopup(LabPopupMenu*);

void func_89101F90(LabPCListScreen* arg0) {
    s32 sel;

    sel = arg0->pageColumnStart[arg0->page] + arg0->headerCursor.cursor - 2;
    switch (sel) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
            arg0->state = 3;
            LabPCList_InitPopupMenu(&arg0->popup, D_8910D910[sel].a, (s8*)&arg0->popupItemFlags, D_8910D910[sel].b, 0);
            Window_SetRect((s8*)&arg0->popup.anchorX, LabPCList_GetColumnCursorX(arg0), arg0->listFrame.y, 0, 0x16);
            arg0->popup.limitX = arg0->listFrame.x + arg0->listFrame.width;
            arg0->popup.limitY = arg0->listFrame.y + arg0->listFrame.height;
            LabPCList_PlacePopup(&arg0->popup);
            arg0->popup.window.frame.color = D_8910A7F4;
            break;
        case 4:
        case 5:
            LabPCList_InitTypeFilter(&arg0->typeFilterWindow, 0x81, 0x94, &arg0->typeFilterCount);
            arg0->state = 5;
            break;
        case 6:
        case 7:
        case 8:
        case 9:
            LabPCList_InitMoveFilter(&arg0->moveFilterWindow, 0x81, 0x94, arg0->moveFilterMoves);
            arg0->state = 6;
            break;
    }
}

typedef struct Str891020F8 { char s[13]; } Str891020F8;
void func_8000A460(s8*, s8*);
u32 func_800566BC(s8*);
void LabPCList_InitPopupMenu(LabPopupMenu*, void*, s8*, s32, s32);
void LabPCList_PlacePopup(LabPopupMenu*);
void func_8910A21C(s8*, s8*, s8*, s32);
extern s8* D_8910A890[];
extern u8 D_8910A898[];
extern u8 D_8910DC50[];
extern s8 D_8910E2D0[];
extern s8 D_8910E312[];

/**
 * Builds the "<species>をあつめる / をかいじょする" (gather / ungather) prompt for the selected Pokemon.
 * Seen in play (2026-11-12) in いちらん (party list: フシギダネ, ヒトカゲ, ゼニガメ): A on フシギダネ built the popup's
 * first row, 「フシギダネをあつめる」.
 */
void LabPCList_FormatGatherPrompt(LabPCListScreen* arg0) {
    func_8000A460(D_8910E2D0, *(s8**)D_80064C44[M2C_FIELD(((PointerList*)arg0->list.items)->items[arg0->list.cursor], u8*, 8)]);
    func_8000A460(D_8910E2D0 + func_800566BC(D_8910E2D0), D_8910A890[(arg0->activeFilters & 8) ? 1 : 0]);
    *(Str891020F8*)D_8910E312 = *(Str891020F8*)D_8910DC50;
    func_8000A460(D_8910E2D0 + (func_800566BC(D_8910E312) + 0x42), D_8910A890[(arg0->activeFilters & 0x10) ? 1 : 0]);
    LabPCList_InitPopupMenu(&arg0->popup, D_8910A898, (s8*)arg0->popupItemFlags, 4, 0);
    Window_SetRect((s8*)&arg0->popup.anchorX, arg0->listFrame.x + 0x26,
                  arg0->listFrame.y + arg0->list.cursorY - arg0->list.scrollY + 0x16, 0, 0x14);
    arg0->popup.limitX = arg0->listFrame.x + arg0->listFrame.width;
    arg0->popup.limitY = arg0->listFrame.y + arg0->listFrame.height;
    LabPCList_PlacePopup(&arg0->popup);
    arg0->popup.window.frame.color = D_8910A7F4;
    arg0->state = 7;
    func_80027804((s8*)arg0 + 0xAFFC, (s8*)arg0 + 0xAD54, 0xAA, 0);
    func_8910A21C((s8*)arg0 + 0xAFFC, (s8*)arg0 + 0xA00C, (s8*)arg0->unk_9E64, 3);
    if (M2C_FIELD(arg0, s32*, 0xB004) == 0) {
        M2C_FIELD(arg0->popup.menu.itemFlags, u16*, 6) |= 1;
    }
}

typedef struct List89102344 {
    /* 0x00 */ u8** items;
    /* 0x04 */ char unk04[4];
    /* 0x08 */ s32 count;
} List89102344;


s32 func_8003F6AC();
s32 ScrollList_UpdateCursor(void*);
void ScrollList_SetCursor(void*, s32);
void LabPCList_FormatGatherPrompt(LabPCListScreen*);

/**
 * Handles list input while the cursor is on the Pokemon rows.
 * Seen in play (2026-11-12): moved the cursor over the rows.
 */
s32 LabPCList_UpdateListCursor(LabPCListScreen* arg0) {
    s32 ret;

    if ((arg0->list.cursorY == 0) && (*(u16*)(D_800603C0 + 6) & 0x800)) {
        func_8003F6AC(1);
        arg0->focus = 2;
        arg0->headerCursor.cursor = 1;
        ScrollList_SetCursor(&arg0->list, arg0->list.scrollY / arg0->list.cellHeight);
        return 1;
    }
    ret = ScrollList_UpdateCursor(&arg0->list.items) != 0;
    if ((ret == 0) && (*(u16*)(D_800603C0 + 8) & 0x8000)) {
        if ((arg0->list.items->count > 0) && (((List89102344*)arg0->list.items)->items[arg0->list.cursor][8] > 0) && (((List89102344*)arg0->list.items)->items[arg0->list.cursor][8] < 0x98)) {
            func_8003F6AC(2);
            LabPCList_FormatGatherPrompt((s8*)arg0);
            ret = 1;
        } else {
            func_8003F6AC(8);
        }
    }
    return ret;
}

void func_8000A460(s8 *, s8 *);
u32 func_800566BC(s8*);
void LabPCList_InitPopupMenu(LabPopupMenu*, void *, s8 *, s32, s32);
void LabPCList_PlacePopup(LabPopupMenu*);
void Window_SetRect(s8 *, s32, s32, s32, s32);
extern Color_RGBA8 D_8910A7F4;
extern s8 *D_8910A8A8[];
extern s8 D_8910A8B0[];
extern u8 D_8910A8C8[];
extern s8 D_8910E358[];
/**
 * Sets up the sort menu: by name, by number, gather battle Pokemon, clear selections, choose what to list.
 * Seen in play (2026-11-12) in いちらん: A on the ポケモン header opened the menu アイウエオじゅんにならべる,
 * ポケモンばんごうでならべる, バトルようのポケモンをあつめる, すべてのせんたくをやめる, いちらんするポケモンをえらぶ.
 */
void LabPCList_InitSortMenu(LabPCListScreen *arg0) {
    func_8000A460(D_8910E358, D_8910A8B0);
    func_8000A460(D_8910E358 + func_800566BC(D_8910E358), D_8910A8A8[(arg0->activeFilters & 0x20) ? 1 : 0]);
    LabPCList_InitPopupMenu(&arg0->popup, D_8910A8C8, (s8*)&arg0->popupItemFlags, 5, 0);
    Window_SetRect((s8*)&arg0->popup.anchorX, arg0->listFrame.x + 0x26, arg0->listFrame.y, 0, 0x16);
    arg0->popup.limitX = arg0->listFrame.x + arg0->listFrame.width;
    arg0->popup.limitY = arg0->listFrame.y + arg0->listFrame.height;
    LabPCList_PlacePopup(&arg0->popup);
    arg0->popup.window.frame.color = D_8910A7F4;
    if (arg0->activeFilters == 0) {
        M2C_FIELD(arg0->popup.menu.itemFlags, u16 *, 6) |= 1;
    }
}

s32 func_8002B390(s32*);

/**
 * Handles input while the cursor is on the header buttons.
 * Seen in play (2026-11-12) in いちらん: R moved the focus to the column headers, and D-Left/D-Right
 * moved the highlight between ニックネーム, ID, おや and ばしょ while this ran.
 */
s32 LabPCList_UpdateHeaderCursor(LabPCListScreen* arg0) {
    s32 ret = 0;
    s32 button;

    button = func_8002B390(&arg0->headerCursor.controller);
    if (button != 0) {
        if ((button == 0x400) && (arg0->headerCursor.cursor == 1)) {
            func_8003F6AC(1);
            arg0->focus = 0;
            arg0->list.repeatTimer = 8; arg0->list.inputDirection = 0x400; // FAKE: both stores must share one source line (IDO schedules by line)
            ret = 1;
        } else {
            arg0->focus = (arg0->headerCursor.cursor < 2) ? 2 : 1;
            ret = 1;
        }
    } else if (*(u16*)(D_800603C0 + 8) & 0x8000) {
        if (arg0->headerCursor.cursor == 0) {
            func_8003F6AC(3);
            ret = -1;
        } else if (arg0->headerCursor.cursor == 1) {
            func_8003F6AC(2);
            LabPCList_InitSortMenu((LabPCListScreen*)arg0);
            ret = 1;
            arg0->state = 2;
        } else {
            func_8003F6AC(2);
            func_89101F90((LabPCListScreen*)arg0);
            ret = 1;
        }
    }
    return ret;
}

/**
 * Browse state: list or header input, C-Left/C-Right change the detail page, L/R move the focus.
 * Seen in play (2026-11-12) in いちらん (party list: フシギダネ, ヒトカゲ, ゼニガメ): was running while browsing;
 * C-Right turned the detail page from ページおくり1/3 to 2/3 (the move columns).
 */
s32 LabPCList_UpdateBrowse(LabPCListScreen* arg0) {
    s32 done = FALSE;
    s32 result;
    u16 buttons;

    switch (arg0->focus) {
        case 0:
            result = LabPCList_UpdateListCursor((LabPCListScreen*)arg0);
            break;
        case 1:
        case 2:
            result = LabPCList_UpdateHeaderCursor((LabPCListScreen*)arg0);
            break;
    }
    if (result == -1) {
        done = TRUE;
    } else if (result == 0) {
        buttons = *(u16*)(D_800603C0 + 8);
        if (buttons & 0x4000) {
            func_8003F6AC(3);
            done = TRUE;
        } else if (buttons & 2) {
            func_8003F6AC(2);
            if (arg0->page == 0) {
                arg0->page += 3;
            }
            arg0->page--;
            func_89100294(arg0);
        } else if (buttons & 1) {
            func_8003F6AC(2);
            if (arg0->page >= 2) {
                arg0->page -= 3;
            }
            arg0->page++;
            func_89100294(arg0);
        } else if (buttons & 0x20) {
            if (arg0->focus != 0) {
                func_8003F6AC(2);
                arg0->focus = 0;
            }
        } else if ((buttons & 0x10) && (arg0->focus != 1)) {
            func_8003F6AC(2);
            arg0->focus = 1;
            arg0->headerCursor.cursor = 2;
        }
    }
    return done;
}

M2C_UNK LabPCList_ApplyFiltersAndSort();
M2C_UNK func_89109C6C(s32, s32);                    /* extern */
/**
 * Handles the window that chooses which boxes to list.
 * Seen in play (2026-11-12): ran the 「どこのポケモンを いちらん するか えらんでください。」 window (てもち / ゲームボーイのボックス /
 * 64カセットのボックス, OK).
 */
s32 LabPCList_UpdateSourceSelect(LabPCListScreen* arg0)
{
  s8 *new_var2; // FAKE: permuter temp
  s32 temp_v0;
  s8 *new_var; // FAKE: permuter temp
  temp_v0 = func_89106254(&arg0->sourceSelectWindow);
  new_var2 = (s8*)&arg0->rows;
  if (temp_v0 == (-1))
  {
    goto block_4;
  }
  if (temp_v0 == 1)
  {
    new_var = (s8*)&arg0->sourceMatrix;
    func_89109C6C(new_var2, new_var);
    LabPCList_ApplyFiltersAndSort(arg0);
    *((s32 *) (((s8 *) arg0) + 0x88)) = 0;
    block_4:
    *((s32 *) (((s8 *) arg0) + 0x88)) = 0;

  }
  return 0;
}

typedef struct Sub89102930 { char unk00[0x10]; s32 unk10; char unk14[0xC]; } Sub89102930; // 0x20
typedef struct Item89102930 { char unk00[4]; s32 unk04; char unk08[8]; Sub89102930* subs; char unk14[4]; s32 subCount; char unk1C[8]; } Item89102930; // 0x24
s32 func_89102930(arg0) s8* arg0; {
    s32 flags = 0;
    s32 i;
    s32 j;
    Item89102930* item = M2C_FIELD(arg0, Item89102930**, 0x420);

    for (i = 0; i < M2C_FIELD(arg0, s32*, 0x428); i++, item++) {
        Sub89102930* sub = item->subs;
        for (j = 0; j < item->subCount; j++, sub++) {
            if (sub->unk10 != 0) {
                if (item->unk04 == 0x20 || item->unk04 == 0x21) {
                    flags |= 1;
                } else {
                    flags |= 0x10;
                }
            }
        }
    }
    for (i = 0; i < 3; i++) {
        if (((LabPCListScreen*)arg0)->unk_9E68[i].unk00 != 0 && ((LabPCListScreen*)arg0)->unk_9E68[i].unk04 != 0) {
            if (i == 0 || i == 1) {
                flags |= 2;
            } else {
                flags |= 0x20;
            }
        }
    }
    return flags;
}

s32 func_8002207C(s32);                             /* extern */
M2C_UNK func_80022118(s32);                         /* extern */
M2C_UNK func_80022188(s32);                         /* extern */
M2C_UNK func_800230C4(s32);                         /* extern */
M2C_UNK func_800243B8();                            /* extern */
M2C_UNK func_8002D7D4(s32);                         /* extern */
void LabPCList_DrawListScreen(LabPCListScreen*);
s32 func_89102930();                                /* extern */
M2C_UNK func_89109D14(s32);                         /* extern */
extern s32 D_8910E37C;

/**
 * Writes the changed boxes back to the save.
 * Seen in play (2026-11-12) in いちらん: ran on レポートしてやめる (B after an item was used, 「ないようが
 * へんこうされています」), and the Game Boy save on the Transfer Pak then held the changed party and bag.
 */
void LabPCList_SaveChanges(s32 arg0) {
    s32 sp1C;
    s32 temp_v0;

    temp_v0 = func_89102930();
    sp1C = temp_v0;
    if (temp_v0 & 3) {
        func_80022118(D_8910E37C);
    }
    func_89109D14(arg0 + 0x420);
    func_891000BC(arg0);
    if (sp1C & 3) {
        if (sp1C & 1) {
            func_800230C4(D_8910E37C);
        }
        if (func_8002207C(D_8910E37C) == 0) {
            func_8002D7D4(D_8910E37C);
            LabPCList_DrawListScreen((s8*)arg0);
        }
        func_80022188(D_8910E37C);
    }
    if (sp1C & 0x30) {
        func_800243B8();
    }
}
