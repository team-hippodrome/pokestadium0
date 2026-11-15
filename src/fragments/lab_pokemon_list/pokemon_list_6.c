/* Fixed-layout split; original translation-unit boundaries remain unconfirmed. */
#include "global.h"
#include "lab_pokemon_list.h"
#include "m2c_macros.h"

typedef struct Color82000BC4 {
    u8 r, g, b, a;
} Color82000BC4;
typedef struct Entry80066AD8 {
    const char* str;
    Color82000BC4 color;
} Entry80066AD8;

typedef struct Label89100FC4 {
    Color82000BC4 color;
    const char* str;
} Label89100FC4;

extern u8 D_80073520[];
M2C_UNK Ui_DrawRoundedFrame(s32, s32, s32, s32, Color_RGBA8);
extern s32 D_8910A7F8[3];
void func_80027410(void*, void*, s32, s32, s32);
void LabPCList_InitSourceBoxes(void*, void*, void*, s32);
extern s32 D_800603C0;
void func_8000B2F4(s32);
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
s32 LabPCList_GetColumnCursorX();
extern Entry80066AD8 D_80066AD8[];
s32 Pokemon_GetTypeIndex(u8*, s32);
M2C_UNK func_8001A384(M2C_UNK, M2C_UNK);
void Font_Printf(s32 x, s32 y, const char* fmt, ...);
M2C_UNK func_8001AA9C(u8, u8, u8, u8);
M2C_UNK func_8001AB6C();
M2C_UNK func_8001ABBC();
extern Entry89100FC4 D_8006A9D4[];
extern M2C_UNK D_800734A8;
extern char D_8910DBAC[];
s32 BattleMon_GetMoveIndexChecked(s32, s32);
extern M2C_UNK D_800734A8;
extern M2C_UNK D_8910DBB4;
extern M2C_UNK D_8910DBBC;
extern M2C_UNK D_8910DBC0;
extern M2C_UNK D_8910DBC4;
extern u8 D_04006170[];
extern u8 D_04006CE0[];
extern Gfx D_80060290[];
extern Gfx D_80060398[];
extern u8 D_8910C370[];
extern u8 D_8910C978[];
extern char D_8910DBF0[];
extern char D_8910DC04[];
void Gfx_DrawTextureRgba16(s32, s32, s32, s32, u8*, s32, s32);
extern s32 D_8910D990[];
void ScrollList_SetItems(s32*, void*, void*);
void func_80027D94(s32, void*, void*, void*);
void func_80027D68(s32, s32);
int LabPCList_FilterByLevelRange();
s32 LabPCList_FilterByAnyType();
s32 LabPCList_FilterByAnyMove();
s32 LabPCList_FilterBySpeciesId();
s32 LabPCList_FilterByExactTypePair();
s32 LabPCList_FilterByBattleEligible();
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
s32 Audio_PlaySystemSound();
s32 ScrollList_UpdateCursor(void*);
void ScrollList_SetCursor(void*, s32);
void LabPCList_FormatGatherPrompt(LabPCListScreen*);
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
s32 LabPCList_UpdateHeaderCursor(void*);
M2C_UNK LabPCList_ApplyFiltersAndSort();
extern s32 D_8910E37C;
s32 LabPCList_UpdatePopupMenu(LabPopupMenu*);
void func_80027D68(s32, s32);
M2C_UNK LabPCList_ApplyFiltersAndSort();
extern s32 D_8910D9D0;
extern s32 D_8910D9D4;

void LabPCList_InitLevelInputWindow(LabLevelInputWindow*, s32, s32, Color_RGBA8, s32, s32, s32);
s32 LabPCList_HasFilterFlag(LabPCListScreen*, s32);

/**
 * Handles the column sort popup: the first row sorts high to low (or by text), the second low to high, the third opens the level range input.
 * Seen in play (2026-11-14) in いちらん: sorted every stat column both ways and opened レベルのにゅうりょく.
 */
s32 LabPCList_UpdateColumnMenu(LabPCListScreen* screen) {
    UNUSED s32 pad; // FAKE: stack padding
    u32 sel;
    s32 a;
    s32 b;

    sel = screen->headerCursor.cursor + screen->pageColumnStart[screen->page] - 2;
    LabPCList_UpdatePopupMenu(&screen->popup);
    if (((u16*)D_800603C0)[4] & 0x4000) {
        Audio_PlaySystemSound(3);
        screen->state = 0;
    } else if (((u16*)D_800603C0)[4] & 0x8000) {
        Audio_PlaySystemSound(2);
        switch (screen->popup.menu.cursor) {
            case 0:
                switch (sel) {
                    case 0:
                        screen->sortKey = 0xF;
                        break;
                    case 1:
                        screen->sortKey = 0xD;
                        break;
                    case 2:
                        screen->sortKey = 0xE;
                        break;
                    case 3:
                        screen->sortKey = 0;
                        break;
                    case 10:
                        screen->sortKey = 2;
                        break;
                    case 11:
                        screen->sortKey = 4;
                        break;
                    case 12:
                        screen->sortKey = 6;
                        break;
                    case 13:
                        screen->sortKey = 8;
                        break;
                    case 14:
                        screen->sortKey = 0xA;
                        break;
                    case 15:
                        screen->sortKey = 0xC;
                        break;
                }
                func_80027D68(M2C_FIELD(screen, s32*, 0xB160), D_8910D990[screen->sortKey]);
                screen->state = 0;
                break;
            case 1:
                switch (sel) {
                    case 10:
                        screen->sortKey = 1;
                        break;
                    case 11:
                        screen->sortKey = 3;
                        break;
                    case 12:
                        screen->sortKey = 5;
                        break;
                    case 13:
                        screen->sortKey = 7;
                        break;
                    case 14:
                        screen->sortKey = 9;
                        break;
                    case 15:
                        screen->sortKey = 0xB;
                        break;
                }
                func_80027D68(M2C_FIELD(screen, s32*, 0xB160), D_8910D990[screen->sortKey]);
                screen->state = 0;
                break;
            case 2:
                if (screen->unk_982C != 0) {
                    a = screen->levelFilterMax;
                    b = screen->levelFilterMin;
                } else {
                    a = screen->levelFilterMin;
                    b = screen->levelFilterMax;
                }
                screen->state = 4;
                LabPCList_InitLevelInputWindow(&screen->levelInputWindow, 0x110, 0xF5, D_8910A7F4, a, b, LabPCList_HasFilterFlag(screen, 1));
                break;
        }
    }
    return 0;
}

/**
 * Runs the レベルのにゅうりょく (level input) window and applies the level range filter.
 * Seen in play (2026-11-12) in いちらん: あつめる with 006から100 stored 6 and 100 at +0x9828/+0x9829, set
 * flag 1, and the Lv 5 party disappeared; かいじょ reset the range to 1-100 and cleared flag 1.
 */
s32 LabPCList_UpdateLevelInput(void*);
M2C_UNK LabPCList_ApplyFiltersAndSort();
s32 LabPCList_RunLevelFilter(s8 *screenArg)
{
  LabPCListScreen *screen = (LabPCListScreen *) screenArg;
  s32 ret;
  ret = func_89106C98(&screen->levelInputWindow);
  if (ret == (-1))
  {
    screen->state = 0;
  }
  else
    if (ret == 1)
  {
    if (screen->levelInputWindow.maxLevel.value >= screen->levelInputWindow.minLevel.value)
    {
      screen->unk_982C = 0;
      screen->levelFilterMin = screen->levelInputWindow.minLevel.value;
      screen->levelFilterMax = screen->levelInputWindow.maxLevel.value;
      screen->sortKey = 1;
    }
    else
    {
      screen->unk_982C = 1;
      screen->levelFilterMax = screen->levelInputWindow.minLevel.value;
      screen->levelFilterMin = screen->levelInputWindow.maxLevel.value;
      screen->sortKey = 2;
    }
    LabPCList_SetFilterFlag((s8 *) screen, 1);
    LabPCList_ApplyFiltersAndSort((s8 *) screen);
    screen->state = 0;
  }
  else
  {
    if (ret == 2)
    {
      screen->levelFilterMin = 1; screen->levelFilterMax = 100; // IDO: both stores must share one source line
      screen->unk_982C = 0;
      LabPCList_ClearFilterFlag((s8 *) screen, 1);
      LabPCList_ApplyFiltersAndSort((s8 *) screen);
      screen->state = 0;
    }
  }
  return 0;
}

/**
 * Runs the type filter window and turns filter flag 2 on or off.
 * Seen in play (2026-11-12) in いちらん: ran while the タイプであつめる window was open.
 */
s32 LabPCList_RunTypeFilter(LabPCListScreen* screen) {
    LabTypeFilterWindow* sp24 = &screen->typeFilterWindow;
    s32 ret = LabPCList_UpdateTypeFilter(sp24);

    if (ret == -1) {
        screen->state = 0;
    } else if (ret == 1) {
        LabPCList_CommitTypeFilter(sp24, &screen->typeFilterCount);
        if (screen->typeFilterCount == 0) {
            LabPCList_ClearFilterFlag(screen, 2);
        } else {
            LabPCList_SetFilterFlag(screen, 2);
        }
        LabPCList_ApplyFiltersAndSort(screen);
        screen->state = 0;
    } else if (ret == 2) {
        screen->typeFilterCount = 0;
        LabPCList_ClearFilterFlag(screen, 2);
        LabPCList_ApplyFiltersAndSort(screen);
        screen->state = 0;
    }
    return 0;
}

/**
 * Runs the move filter window and turns filter flag 4 on or off.
 * Seen in play (2026-11-12) in いちらん: あつめる with ひっかく set filter flag 4 and left only ヒトカゲ (ひっさつまえば
 * left the list empty); かいじょ cleared flag 4 and all three party Pokémon returned.
 */
s32 LabPCList_RunMoveFilter(LabPCListScreen* screen) {
    LabMoveFilterWindow* sp24 = &screen->moveFilterWindow;
    s32 ret = LabPCList_UpdateMoveFilter(sp24);

    if (ret == -1) {
        screen->state = 0;
    } else if (ret == 1) {
        LabPCList_CommitMoveFilter(sp24, screen->moveFilterMoves);
        if (screen->moveFilterCount == 0) {
            LabPCList_ClearFilterFlag(screen, 4);
        } else {
            LabPCList_SetFilterFlag(screen, 4);
        }
        LabPCList_ApplyFiltersAndSort(screen);
        screen->state = 0;
    } else if (ret == 2) {
        screen->moveFilterCount = 0;
        LabPCList_ClearFilterFlag(screen, 4);
        LabPCList_ApplyFiltersAndSort(screen);
        screen->state = 0;
    }
    return 0;
}

/** One 0x20-byte list item; only the fields tested here are named. */
typedef struct Item89103144 {
    /* 0x00 */ char unk00[0x8];
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ char unk0C[0x10];
    /* 0x1C */ s32 unk_1C;
} Item89103144; // size = 0x20

/** List owning the items. */
typedef struct List89103144 {
    /* 0x00 */ char unk00[0x10];
    /* 0x10 */ Item89103144* items;
    /* 0x14 */ char unk14[0x4];
    /* 0x18 */ s32 count;
    /* 0x1C */ char unk1C[0x4];
    /* 0x20 */ s32 limit;
} List89103144;

/** Per-item flag array holder. */
typedef struct Flags89103144 {
    /* 0x00 */ char unk00[0x4];
    /* 0x04 */ u16* flags;
} Flags89103144;

/**
 * Greys out the boxes of a source that are not listed, full, or the Pokémon's own box.
 * Seen in play (2026-11-14) in いちらん: ran when いどうする > ゲームボーイのボックス / 64カセットのボックス opened the box list.
 */
void LabPCList_DisableUnavailableBoxes(Flags89103144* menu, Item89103144** entry, List89103144* source) {
    s32 i;
    Item89103144* item;

    item = source->items;
    i = 0;
    if (source->count > 0) {
        do {
            if ((item->unk_08 == 0) || (item->unk_1C >= source->limit) || (item == *entry)) {
                menu->flags[i] |= 1;
            }
            i++;
            item++;
        } while (i < source->count);
    }
}

/**
 * Greys out each destination source with no box that could take the Pokémon.
 * Seen in play (2026-11-14) in いちらん: ran when いどうする opened 「どこへ？」.
 */
void LabPCList_DisableUnavailableSources(s8* menu, s8** movingEntry, s8* sources) {
    s32 i;
    s32 j;
    s8* box;
    s8* entry;

    for (box = M2C_FIELD(sources, s8**, 0), i = 0; i < M2C_FIELD(sources, s32*, 8); i++, box += 0x24) {
        for (entry = M2C_FIELD(box, s8**, 0x10), j = 0; j < M2C_FIELD(box, s32*, 0x18); j++, entry += 0x20) {
            if ((M2C_FIELD(entry, s32*, 8) != 0) && (M2C_FIELD(entry, s32*, 0x1C) < M2C_FIELD(box, s32*, 0x20)) &&
                (entry != *movingEntry)) {
                break;
            }
        }
        if (j >= M2C_FIELD(box, s32*, 0x18)) {
            M2C_FIELD(menu, u16**, 4)[i] |= 1;
        }
    }
}

extern u8 D_8910A8DC[];
extern s32 D_8910DD34[];
/**
 * Opens the 「どこへ？」 (where to?) menu: てもちのポケモン, ゲームボーイのボックス, 64カセットのボックス.
 * Seen in play (2026-11-14) in いちらん: いどうする on フシギダネ opened it.
 */
void LabPCList_OpenDestinationMenu(LabPCListScreen* screen, s8** entry) {
    LabPCList_InitPopupMenu(&screen->subPopup, D_8910A8DC, (s8*)&screen->popupItemFlags[1], 3, (s32)D_8910DD34);
    Window_SetRect((s8*)&screen->subPopup.anchorX, screen->popup.window.frame.x + 0xE, screen->popup.window.frame.y + 0x38, 0x6C, 0x1C);
    screen->subPopup.window.frame.style |= 0x1000000;
    screen->subPopup.limitX = screen->listFrame.x + screen->listFrame.width;
    screen->subPopup.limitY = screen->listFrame.y + screen->listFrame.height;
    LabPCList_PlacePopup(&screen->subPopup);
    screen->subPopup.window.frame.color = D_8910A7F4;
    LabPCList_DisableUnavailableSources((s8*)&screen->subPopup.menu, entry, (s8*)&screen->sourceMatrix);
}

/**
 * Returns whether the Pokémon is the only one left in the party, which cannot be moved.
 * Seen in play (2026-11-14) in いちらん: with the party count poked to 1 at this check, いどうする showed 「さいごのポケモンです」.
 */
s32 LabPCList_IsLastPartyMon(s8 **entry) {
    s32 var_v1;
    s8 *temp_v0;

    temp_v0 = *entry;
    var_v1 = M2C_FIELD(M2C_FIELD(temp_v0, s8 **, 0), s32 *, 4) == 0x20;
    if (var_v1 != 0) {
        var_v1 = M2C_FIELD(temp_v0, s32 *, 0x1C) == 1;
    }
    return var_v1;
}

void TextBox_Init(s8* arg0, s32 arg1, s32 arg2, s32 arg3, u32 arg4);
extern Info891033A0 D_80065D00[];
extern s8 D_8910DD40[];
extern s8 D_8910DD58[];

/**
 * Handles the menu opened on a selected Pokemon.
 * Seen in play (2026-11-12) in いちらん (party list: フシギダネ, ヒトカゲ, ゼニガメ): was handling the popup
 * opened with A on フシギダネ.
 */
s32 LabPCList_UpdateMonMenu(LabPCListScreen* screen) {
    s32 ret = 0;
    s8* entry;

    LabPCList_UpdatePopupMenu(&screen->popup);
    if (((u16*)D_800603C0)[4] & 0x4000) {
        Audio_PlaySystemSound(3);
        screen->state = 0;
    } else if (((u16*)D_800603C0)[4] & 0x8000) {
        entry = ((PointerList*)screen->list.items)->items[screen->list.cursor];
        switch (screen->popup.menu.cursor) {
            case 0:
                Audio_PlaySystemSound(2);
                if (LabPCList_ToggleFilterFlag(screen, 8) != 0) {
                    screen->unk_9E58 = M2C_FIELD(entry, u8*, 8);
                }
                LabPCList_ApplyFiltersAndSort(screen);
                screen->state = 0;
                break;
            case 1:
                Audio_PlaySystemSound(2);
                if (LabPCList_ToggleFilterFlag(screen, 0x10) != 0) {
                    s32 id;

                    id = M2C_FIELD(entry, u8*, 8) - 1;
                    screen->sameTypeFilterCount = 1;
                    screen->sameTypeFilterTypes[0] = D_80065D00[id].unk06;
                    if (D_80065D00[id].unk06 != D_80065D00[id].unk07) {
                        screen->sameTypeFilterTypes[1] = D_80065D00[id].unk07;
                        screen->sameTypeFilterCount++;
                    }
                }
                LabPCList_ApplyFiltersAndSort(screen);
                screen->state = 0;
                break;
            case 2:
                if (LabPCList_IsLastPartyMon((s8**)entry) != 0) {
                    Audio_PlaySystemSound(8);
                    TextBox_Init((s8*)screen->textBox, (s32)D_8910DD40, 0, 1, 0);
                    screen->state = 0xB;
                } else {
                    Audio_PlaySystemSound(2);
                    LabPCList_OpenDestinationMenu(screen, (s8**)entry);
                    screen->state = 8;
                }
                break;
            case 3:
                if (!(screen->popup.menu.itemFlags[screen->popup.menu.cursor] & 1)) {
                    Audio_PlaySystemSound(2);
                    screen->state = 0;
                    ret = 2;
                } else {
                    Audio_PlaySystemSound(8);
                    TextBox_Init((s8*)screen->textBox, (s32)D_8910DD58, 0, 1, 0);
                    screen->state = 0xC;
                }
                break;
        }
    }
    return ret;
}

/**
 * Renumbers the slot index (entry[1]) of every Pokemon left in a box after one is taken out. Seen
 * in play (2026-11-12) in いちらん: after フシギダネ left the party, the two remaining entries went from
 * slots 1, 2 to 0, 1.
 */
void LabPCList_ReindexBoxSlots(u8* box) {
    s32 i;
    s32** ptr = M2C_FIELD(box, s32***, 0x14);

    for (i = 0; i < M2C_FIELD(box, s32*, 0x1C); i++) {
        (*ptr++)[1] = i;
    }
}
