/* Fixed-layout split; original translation-unit boundaries remain unconfirmed. */

#include "global.h"
#include "lab_pokemon_list.h"
#include "m2c_macros.h"

extern u8 D_80073520[];
M2C_UNK Ui_DrawRoundedFrame(s32, s32, s32, s32, Color_RGBA8);

M2C_UNK LabPCList_InitDeckCategories(s32, s32, s32, s32);

extern s32 D_8910A7F8[3];
void func_80027410(void*, void*, s32, s32, s32);
void LabPCList_InitSourceBoxes(void*, void*, void*, s32);

extern s32 D_800603C0;
void func_8000B2F4(s32);

void Window_SetRect(s8 *, s32, s32, s32, s32);
void func_80027804(s8*, s8*, s32, s32);
void LabPCList_LoadAllBoxes(s8*);
void func_80027D68(void*, s32);
void ScrollList_Init(s8*, s8*, s8*, s32, void*, s32, s32);
void LabPCList_DrawMonRow();
extern s32 D_8910D990[];
extern Color_RGBA8 D_8910A7F4;
extern u8 D_8910A844[];
extern u8 D_8910A848[];
extern u8 D_8910A804[];
extern u8 D_8910A84C[];

void LabPCList_SaveDirtyItemDecks(s32 screen);
void LabPCList_ResetHeaderCursor(LabPCListScreen* screen);
s32 LabPCList_GetColumnCursorX(LabPCListScreen* screen);
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
void LabPCList_DrawPlainText(s32, s32, s8*, s32, s32);

s32 Window_DrawAnimatedFrame(void);
void Window_DrawHeaderStripe(s32, s32, s32);
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
void LabPCList_DrawColumnCursor(s8*);
void LabPCList_DrawHeaderCursor(LabPCListScreen*);
/**
 * Draws the lab PC list screen: page hint, column headers and rows.
 * Seen in play (2026-11-12): the いちらん list with the page hint, column headers and rows.
 */
void LabPCList_DrawListScreen(LabPCListScreen* screen) {
    s32 sel;
    s32 y;
    s32 flags[2]; // FAKE (only [0] is used; has to live on the stack)

    if (Window_DrawAnimatedFrame() != 0) {
        return;
    }
    Window_DrawHeaderStripe(screen->window.frame.x, screen->window.frame.y - 0xA, 0x1F4);
    Window_DrawFrame((s8*)&screen->headerFrame);
    Ui_DrawTexturedDivider(screen->window.frame.x, screen->window.frame.y + 0x23, screen->window.frame.width, D_8007356C);
    LabPCList_DrawPageHint(screen);
    ScrollList_DrawScrollArrows((s8*)&screen->list, screen->listFrame.x, screen->listFrame.y - 0x10,
                  screen->listFrame.y + screen->listFrame.height, screen->listFrame.width);
    y = screen->listFrame.y + 0x16;
    if (screen->focus == 0) {
        flags[0] = ((screen->state != 0) ? 0x10 : 0) | 2;
    } else {
        flags[0] = 0;
    }
    ScrollList_DrawItems((s8*)&screen->list, screen->listFrame.x, y, flags[0] | 0xFFED, screen);
    sel = (screen->focus == 1) ? (((screen->state != 0) ? 0x10 : 0) | 2) : 0;
    LabPCList_DrawDetailColumns(screen, screen->listFrame.x, screen->listFrame.y, sel);
    gSPDisplayList(gDisplayListHead++, D_80060270);
    func_80029028(screen->listFrame.x, screen->listFrame.y + 0x14, screen->listFrame.width, 2, D_8910A88C);
    func_80029028(screen->listFrame.x + 0x76, screen->listFrame.y, 2, screen->listFrame.height, D_8910A88C);
    if (screen->state == 0) {
        switch (screen->focus) {
            case 0:
                LabPCList_DrawRowCursor((s8*)&screen->list, screen->listFrame.x, y);
                break;
            case 1:
                LabPCList_DrawColumnCursor(screen);
                break;
            case 2:
                LabPCList_DrawHeaderCursor(screen);
                break;
        }
    }
    switch (screen->state) {
        case 0:
            break;
        case 1:
            LabSourceSelect_Draw(&screen->sourceSelectWindow, 2);
            break;
        case 2:
        case 3:
            LabPCList_DrawPopupMenu(&screen->popup, 2);
            break;
        case 4:
            LabPCList_DrawLevelInputWindow(&screen->levelInputWindow);
            break;
        case 5:
            LabPCList_DrawTypeFilter(&screen->typeFilterWindow);
            break;
        case 6:
            LabPCList_DrawMoveFilter(&screen->moveFilterWindow);
            break;
        case 7:
            LabPCList_DrawPopupMenu(&screen->popup, 2);
            break;
        case 8:
            LabPCList_DrawPopupMenu(&screen->popup, 0x10);
            LabPCList_DrawPopupMenu(&screen->subPopup, 2);
            break;
        case 9:
            LabPCList_DrawPopupMenu(&screen->popup, 0x10);
            LabPCList_DrawPopupMenu(&screen->subPopup, 0x10);
            LabPCList_DrawPopupMenu(&screen->subPopup2, 2);
            break;
        case 10:
            LabPCList_DrawPopupMenu(&screen->popup, 0x10);
            LabPCList_DrawPopupMenu(&screen->subPopup, 0x10);
            LabPCList_DrawPopupMenu(&screen->subPopup2, 2);
            break;
        case 11:
        case 12:
            TextBox_Draw((s8*)screen->textBox);
            break;
    }
}

/**
 * Returns whether any of filter flags `flag` is active.
 * Seen in play (2026-11-12) in いちらん: opening レベルをきめてあつめる called this with 1; it returned 0 with
 * no level filter, and 1 once 006から100 had been applied (かいじょ is then usable).
 */
s32 LabPCList_HasFilterFlag(LabPCListScreen* screen, s32 flag) {
    return (screen->activeFilters & flag) != 0;
}

/**
 * Turns on filter flags `flag`.
 * Seen in play (2026-11-12) in いちらん: choosing どく in タイプであつめる and pressing あつめる called this with
 * 2, the flag word at +0x7C went 0 -> 2, and the list then showed only フシギダネ.
 */
void LabPCList_SetFilterFlag(LabPCListScreen* screen, s32 flag) {
    screen->activeFilters = (s32) (screen->activeFilters | flag);
}

/**
 * Turns off filter flags `flag`.
 * Seen in play (2026-11-12) in いちらん: pressing かいじょ in タイプであつめる called this with 2, the flag word
 * at +0x7C went 2 -> 0, and all three party Pokémon came back.
 */
void LabPCList_ClearFilterFlag(LabPCListScreen* screen, M2C_UNK flag) {
    screen->activeFilters = (s32) (screen->activeFilters & ~flag);
}

/**
 * Turns off every filter flag.
 * Seen in play (2026-11-12) in いちらん: すべてのせんたくをやめる took the flag word from 0x20 to 0.
 */
void LabPCList_ClearFilterFlags(LabPCListScreen* screen) {
    screen->activeFilters = 0;
}

// FAKE: decomp slop. Raw pointer-offset casts stand in for struct fields.
/**
 * Toggles filter flags `flag` and returns whether they are now on.
 * Seen in play (2026-11-12) in いちらん: バトルようのポケモンをあつめる called this with 0x20; the flag word went 0
 * -> 0x20 and it returned 0x20 (on). The menu entry then read バトルようのポケモンをかいじょする.
 */
s32 LabPCList_ToggleFilterFlag(s8 *screen, s32 flag)
{
  s32 temp_t7;
  s32 new_var; // FAKE: permuter temp
  new_var = flag;
  temp_t7 = ((*((s32 *) (((s8 *) screen) + 0x7C))) ^ new_var) & 0xFFFFFFFFFFFFFFFFu;
  *((s32 *) (((s8 *) screen) + 0x7C)) = temp_t7;
  return temp_t7 & new_var;
}

extern s32 D_8910D990[];
void ScrollList_SetItems(ScrollList*, PointerList*, u16*);
void func_80027D94(void*, PointerList*, void*, void*);
void func_80027D68(void*, s32);
int LabPCList_FilterByLevelRange();
s32 LabPCList_FilterByAnyType();
s32 LabPCList_FilterByAnyMove();
s32 LabPCList_FilterBySpeciesId();
s32 LabPCList_FilterByExactTypePair();
s32 LabPCList_FilterByBattleEligible();
/**
 * Rebuilds the visible list from the source boxes using the active filter flags.
 * Seen in play (2026-11-12) in いちらん (party list: フシギダネ, ヒトカゲ, ゼニガメ): ran when OK was pressed on
 * 「どこのポケモンを いちらん するか」 with てもち chosen, and the list then showed the three party Pokémon.
 */
M2C_UNK LabPCList_ApplyFiltersAndSort(LabPCListScreen* screen) {
    ScrollList_SetItems(&screen->list, &screen->rows, screen->rowFlags);
    if (screen->activeFilters != 0) {
        if (screen->activeFilters & 1) {
            func_80027D94(screen->list.items, &screen->filteredRows, LabPCList_FilterByLevelRange, &screen->levelFilterMin);
            ScrollList_SetItems(&screen->list, &screen->filteredRows, screen->rowFlags);
        }
        if (screen->activeFilters & 2) {
            func_80027D94(screen->list.items, &screen->filteredRows, LabPCList_FilterByAnyType, &screen->typeFilterCount);
            ScrollList_SetItems(&screen->list, &screen->filteredRows, screen->rowFlags);
        }
        if (screen->activeFilters & 4) {
            func_80027D94(screen->list.items, &screen->filteredRows, LabPCList_FilterByAnyMove, &screen->moveFilterMoves);
            ScrollList_SetItems(&screen->list, &screen->filteredRows, screen->rowFlags);
        }
        if (screen->activeFilters & 8) {
            func_80027D94(screen->list.items, &screen->filteredRows, LabPCList_FilterBySpeciesId, &screen->unk_9E58);
            ScrollList_SetItems(&screen->list, &screen->filteredRows, screen->rowFlags);
        }
        if (screen->activeFilters & 0x10) {
            func_80027D94(screen->list.items, &screen->filteredRows, LabPCList_FilterByExactTypePair, &screen->sameTypeFilterCount);
            ScrollList_SetItems(&screen->list, &screen->filteredRows, screen->rowFlags);
        }
        if (screen->activeFilters & 0x20) {
            func_80027D94(screen->list.items, &screen->filteredRows, LabPCList_FilterByBattleEligible, NULL);
            ScrollList_SetItems(&screen->list, &screen->filteredRows, screen->rowFlags);
        }
    }
    func_80027D68(screen->list.items, D_8910D990[screen->sortKey]);
}

typedef struct Pair8910D910 { void* a; s32 b; } Pair8910D910;
extern Pair8910D910 D_8910D910[];
void LabPCList_InitPopupMenu(LabPopupMenu*, void*, s8*, s32, s32);
void LabPCList_PlacePopup(LabPopupMenu*);

/**
 * Opens what A does on the selected column header: a sort popup for the text and stat columns, the type filter for タイプ1/タイプ2, the move filter for わざ1-4.
 * Seen in play (2026-11-14) in いちらん: A on ニックネーム opened アイウエオじゅんにならべる, on タイプ1 タイプであつめる, on わざ わざであつめる, on レベル たかいじゅん/ひくいじゅん/レベルをきめてあつめる.
 */
void LabPCList_OpenColumnMenu(LabPCListScreen* screen) {
    s32 sel;

    sel = screen->pageColumnStart[screen->page] + screen->headerCursor.cursor - 2;
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
            screen->state = 3;
            LabPCList_InitPopupMenu(&screen->popup, D_8910D910[sel].a, (s8*)&screen->popupItemFlags, D_8910D910[sel].b, 0);
            Window_SetRect((s8*)&screen->popup.anchorX, LabPCList_GetColumnCursorX(screen), screen->listFrame.y, 0, 0x16);
            screen->popup.limitX = screen->listFrame.x + screen->listFrame.width;
            screen->popup.limitY = screen->listFrame.y + screen->listFrame.height;
            LabPCList_PlacePopup(&screen->popup);
            screen->popup.window.frame.color = D_8910A7F4;
            break;
        case 4:
        case 5:
            LabPCList_InitTypeFilter(&screen->typeFilterWindow, 0x81, 0x94, &screen->typeFilterCount);
            screen->state = 5;
            break;
        case 6:
        case 7:
        case 8:
        case 9:
            LabPCList_InitMoveFilter(&screen->moveFilterWindow, 0x81, 0x94, screen->moveFilterMoves);
            screen->state = 6;
            break;
    }
}

typedef struct Str891020F8 { char s[13]; } Str891020F8;
void func_8000A460(s8*, s8*);
u32 func_800566BC(s8*);
void LabPCList_InitPopupMenu(LabPopupMenu*, void*, s8*, s32, s32);
void LabPCList_PlacePopup(LabPopupMenu*);
void LabPCList_BuildUsableItemList(s8*, s8*, s8*, s32);
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
void LabPCList_FormatGatherPrompt(LabPCListScreen* screen) {
    func_8000A460(D_8910E2D0, *(s8**)D_80064C44[M2C_FIELD(((PointerList*)screen->list.items)->items[screen->list.cursor], u8*, 8)]);
    func_8000A460(D_8910E2D0 + func_800566BC(D_8910E2D0), D_8910A890[(screen->activeFilters & 8) ? 1 : 0]);
    *(Str891020F8*)D_8910E312 = *(Str891020F8*)D_8910DC50;
    func_8000A460(D_8910E2D0 + (func_800566BC(D_8910E312) + 0x42), D_8910A890[(screen->activeFilters & 0x10) ? 1 : 0]);
    LabPCList_InitPopupMenu(&screen->popup, D_8910A898, (s8*)screen->popupItemFlags, 4, 0);
    Window_SetRect((s8*)&screen->popup.anchorX, screen->listFrame.x + 0x26,
                  screen->listFrame.y + screen->list.cursorY - screen->list.scrollY + 0x16, 0, 0x14);
    screen->popup.limitX = screen->listFrame.x + screen->listFrame.width;
    screen->popup.limitY = screen->listFrame.y + screen->listFrame.height;
    LabPCList_PlacePopup(&screen->popup);
    screen->popup.window.frame.color = D_8910A7F4;
    screen->state = 7;
    func_80027804((s8*)screen + 0xAFFC, (s8*)screen + 0xAD54, 0xAA, 0);
    LabPCList_BuildUsableItemList((s8*)screen + 0xAFFC, (s8*)screen + 0xA00C, (s8*)screen->unk_9E64, 3);
    if (M2C_FIELD(screen, s32*, 0xB004) == 0) {
        M2C_FIELD(screen->popup.menu.itemFlags, u16*, 6) |= 1;
    }
}

typedef struct List89102344 {
    /* 0x00 */ u8** items;
    /* 0x04 */ char unk04[4];
    /* 0x08 */ s32 count;
} List89102344;


s32 Audio_PlaySystemSound();
s32 ScrollList_UpdateCursor(void*);
void ScrollList_SetCursor(void*, s32);
void LabPCList_FormatGatherPrompt(LabPCListScreen*);

/**
 * Handles list input while the cursor is on the Pokemon rows.
 * Seen in play (2026-11-12): moved the cursor over the rows.
 */
s32 LabPCList_UpdateListCursor(LabPCListScreen* screen) {
    s32 ret;

    if ((screen->list.cursorY == 0) && (*(u16*)(D_800603C0 + 6) & 0x800)) {
        Audio_PlaySystemSound(1);
        screen->focus = 2;
        screen->headerCursor.cursor = 1;
        ScrollList_SetCursor(&screen->list, screen->list.scrollY / screen->list.cellHeight);
        return 1;
    }
    ret = ScrollList_UpdateCursor(&screen->list.items) != 0;
    if ((ret == 0) && (*(u16*)(D_800603C0 + 8) & 0x8000)) {
        if ((screen->list.items->count > 0) && (((List89102344*)screen->list.items)->items[screen->list.cursor][8] > 0) && (((List89102344*)screen->list.items)->items[screen->list.cursor][8] < 0x98)) {
            Audio_PlaySystemSound(2);
            LabPCList_FormatGatherPrompt((s8*)screen);
            ret = 1;
        } else {
            Audio_PlaySystemSound(8);
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
void LabPCList_InitSortMenu(LabPCListScreen *screen) {
    func_8000A460(D_8910E358, D_8910A8B0);
    func_8000A460(D_8910E358 + func_800566BC(D_8910E358), D_8910A8A8[(screen->activeFilters & 0x20) ? 1 : 0]);
    LabPCList_InitPopupMenu(&screen->popup, D_8910A8C8, (s8*)&screen->popupItemFlags, 5, 0);
    Window_SetRect((s8*)&screen->popup.anchorX, screen->listFrame.x + 0x26, screen->listFrame.y, 0, 0x16);
    screen->popup.limitX = screen->listFrame.x + screen->listFrame.width;
    screen->popup.limitY = screen->listFrame.y + screen->listFrame.height;
    LabPCList_PlacePopup(&screen->popup);
    screen->popup.window.frame.color = D_8910A7F4;
    if (screen->activeFilters == 0) {
        M2C_FIELD(screen->popup.menu.itemFlags, u16 *, 6) |= 1;
    }
}

s32 func_8002B390(s32*);

/**
 * Handles input while the cursor is on the header buttons.
 * Seen in play (2026-11-12) in いちらん: R moved the focus to the column headers, and D-Left/D-Right
 * moved the highlight between ニックネーム, ID, おや and ばしょ while this ran.
 */
s32 LabPCList_UpdateHeaderCursor(LabPCListScreen* screen) {
    s32 ret = 0;
    s32 button;

    button = func_8002B390(&screen->headerCursor.controller);
    if (button != 0) {
        if ((button == 0x400) && (screen->headerCursor.cursor == 1)) {
            Audio_PlaySystemSound(1);
            screen->focus = 0;
            screen->list.repeatTimer = 8; screen->list.inputDirection = 0x400; // FAKE: both stores must share one source line (IDO schedules by line)
            ret = 1;
        } else {
            screen->focus = (screen->headerCursor.cursor < 2) ? 2 : 1;
            ret = 1;
        }
    } else if (*(u16*)(D_800603C0 + 8) & 0x8000) {
        if (screen->headerCursor.cursor == 0) {
            Audio_PlaySystemSound(3);
            ret = -1;
        } else if (screen->headerCursor.cursor == 1) {
            Audio_PlaySystemSound(2);
            LabPCList_InitSortMenu((LabPCListScreen*)screen);
            ret = 1;
            screen->state = 2;
        } else {
            Audio_PlaySystemSound(2);
            LabPCList_OpenColumnMenu((LabPCListScreen*)screen);
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
s32 LabPCList_UpdateBrowse(LabPCListScreen* screen) {
    s32 done = FALSE;
    s32 result;
    u16 buttons;

    switch (screen->focus) {
        case 0:
            result = LabPCList_UpdateListCursor((LabPCListScreen*)screen);
            break;
        case 1:
        case 2:
            result = LabPCList_UpdateHeaderCursor((LabPCListScreen*)screen);
            break;
    }
    if (result == -1) {
        done = TRUE;
    } else if (result == 0) {
        buttons = *(u16*)(D_800603C0 + 8);
        if (buttons & 0x4000) {
            Audio_PlaySystemSound(3);
            done = TRUE;
        } else if (buttons & 2) {
            Audio_PlaySystemSound(2);
            if (screen->page == 0) {
                screen->page += 3;
            }
            screen->page--;
            LabPCList_ResetHeaderCursor(screen);
        } else if (buttons & 1) {
            Audio_PlaySystemSound(2);
            if (screen->page >= 2) {
                screen->page -= 3;
            }
            screen->page++;
            LabPCList_ResetHeaderCursor(screen);
        } else if (buttons & 0x20) {
            if (screen->focus != 0) {
                Audio_PlaySystemSound(2);
                screen->focus = 0;
            }
        } else if ((buttons & 0x10) && (screen->focus != 1)) {
            Audio_PlaySystemSound(2);
            screen->focus = 1;
            screen->headerCursor.cursor = 2;
        }
    }
    return done;
}

M2C_UNK LabPCList_ApplyFiltersAndSort();
/**
 * Handles the window that chooses which boxes to list.
 * Seen in play (2026-11-12): ran the 「どこのポケモンを いちらん するか えらんでください。」 window (てもち / ゲームボーイのボックス /
 * 64カセットのボックス, OK).
 */
s32 LabPCList_UpdateSourceSelect(LabPCListScreen* screen)
{
  s8 *new_var2; // FAKE: permuter temp
  s32 temp_v0;
  s8 *new_var; // FAKE: permuter temp
  temp_v0 = LabSourceSelect_Update(&screen->sourceSelectWindow);
  new_var2 = (s8*)&screen->rows;
  if (temp_v0 == (-1))
  {
    goto block_4;
  }
  if (temp_v0 == 1)
  {
    new_var = (s8*)&screen->sourceMatrix;
    LabPCList_FlattenEntries((PointerList*)new_var2, (unk_func_8830867C_02C_144*)new_var);
    LabPCList_ApplyFiltersAndSort(screen);
    *((s32 *) (((s8 *) screen) + 0x88)) = 0;
    block_4:
    *((s32 *) (((s8 *) screen) + 0x88)) = 0;

  }
  return 0;
}

typedef struct Sub89102930 { char unk00[0x10]; s32 unk10; char unk14[0xC]; } Sub89102930; // 0x20
typedef struct Item89102930 { char unk00[4]; s32 unk04; char unk08[8]; Sub89102930* subs; char unk14[4]; s32 subCount; char unk1C[8]; } Item89102930; // 0x24
/**
 * Returns which saves need writing: 1 a Game Boy box or the party changed, 2 a Game Boy item deck, 0x10 a 64 cartridge box, 0x20 the 64 item deck.
 * Seen in play (2026-11-14) in いちらん: ran on レポートしてやめる after a TM and a move; the Game Boy save was written.
 */
s32 LabPCList_GetChangedSaveFlags(screen) s8* screen; {
    s32 flags = 0;
    s32 i;
    s32 j;
    Item89102930* item = M2C_FIELD(screen, Item89102930**, 0x420);

    for (i = 0; i < M2C_FIELD(screen, s32*, 0x428); i++, item++) {
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
        if (((LabPCListScreen*)screen)->unk_9E68[i].unk00 != 0 && ((LabPCListScreen*)screen)->unk_9E68[i].unk04 != 0) {
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
M2C_UNK Save_CommitPokemonRecords();                            /* extern */
M2C_UNK GbSave_RunReportErrorLoop(s32);                         /* extern */
void LabPCList_DrawListScreen(LabPCListScreen*);
s32 LabPCList_GetChangedSaveFlags();                                /* extern */
M2C_UNK LabPCList_SaveDirtyBoxes(s32);                         /* extern */
extern s32 D_8910E37C;

/**
 * Writes the changed boxes back to the save.
 * Seen in play (2026-11-12) in いちらん: ran on レポートしてやめる (B after an item was used, 「ないようが
 * へんこうされています」), and the Game Boy save on the Transfer Pak then held the changed party and bag.
 */
void LabPCList_SaveChanges(s32 screen) {
    s32 sp1C;
    s32 temp_v0;

    temp_v0 = LabPCList_GetChangedSaveFlags();
    sp1C = temp_v0;
    if (temp_v0 & 3) {
        func_80022118(D_8910E37C);
    }
    LabPCList_SaveDirtyBoxes(screen + 0x420);
    LabPCList_SaveDirtyItemDecks(screen);
    if (sp1C & 3) {
        if (sp1C & 1) {
            func_800230C4(D_8910E37C);
        }
        if (func_8002207C(D_8910E37C) == 0) {
            GbSave_RunReportErrorLoop(D_8910E37C);
            LabPCList_DrawListScreen((s8*)screen);
        }
        func_80022188(D_8910E37C);
    }
    if (sp1C & 0x30) {
        Save_CommitPokemonRecords();
    }
}
