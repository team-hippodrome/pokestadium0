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
void func_89109990(void*, void*, void*, s32);
extern s32 D_800603C0;
void func_8000B2F4(s32);
void Window_SetRect(s8 *, s32, s32, s32, s32);
void func_80027804(s8*, s8*, s32, s32);
void func_89109B60(s8*);
void func_80027D68(s32, s32);
void ScrollList_Init(s8*, s8*, s8*, s32, void*, s32, s32);
void LabPCList_DrawMonRow();
void func_89105C54(s8*, s32, s32, s8*, Color_RGBA8);
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
M2C_UNK func_8001A944(s32, s32, M2C_UNK *, ...);
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
s32 func_891096F4();
s32 func_89109720();
s32 func_891097E4();
s32 func_89109884();
s32 func_89109898();
s32 func_89109960();
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
s32 func_8003F6AC();
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
void func_89105C54(s8*, s32, s32, s8*, Color_RGBA8);
M2C_UNK LabPCList_ApplyFiltersAndSort();
extern s32 D_8910D9D0;
extern s32 D_8910D9D4;

void LabPCList_InitLevelInputWindow(LabLevelInputWindow*, s32, s32, Color_RGBA8, s32, s32, s32);
s32 LabPCList_HasFilterFlag(LabPCListScreen*, s32);

s32 func_89102C40(LabPCListScreen* arg0) {
    UNUSED s32 pad; // FAKE: stack padding
    u32 sel;
    s32 a;
    s32 b;

    sel = arg0->headerCursor.cursor + arg0->pageColumnStart[arg0->page] - 2;
    LabPCList_UpdatePopupMenu(&arg0->popup);
    if (((u16*)D_800603C0)[4] & 0x4000) {
        func_8003F6AC(3);
        arg0->state = 0;
    } else if (((u16*)D_800603C0)[4] & 0x8000) {
        func_8003F6AC(2);
        switch (arg0->popup.menu.cursor) {
            case 0:
                switch (sel) {
                    case 0:
                        arg0->sortKey = 0xF;
                        break;
                    case 1:
                        arg0->sortKey = 0xD;
                        break;
                    case 2:
                        arg0->sortKey = 0xE;
                        break;
                    case 3:
                        arg0->sortKey = 0;
                        break;
                    case 10:
                        arg0->sortKey = 2;
                        break;
                    case 11:
                        arg0->sortKey = 4;
                        break;
                    case 12:
                        arg0->sortKey = 6;
                        break;
                    case 13:
                        arg0->sortKey = 8;
                        break;
                    case 14:
                        arg0->sortKey = 0xA;
                        break;
                    case 15:
                        arg0->sortKey = 0xC;
                        break;
                }
                func_80027D68(M2C_FIELD(arg0, s32*, 0xB160), D_8910D990[arg0->sortKey]);
                arg0->state = 0;
                break;
            case 1:
                switch (sel) {
                    case 10:
                        arg0->sortKey = 1;
                        break;
                    case 11:
                        arg0->sortKey = 3;
                        break;
                    case 12:
                        arg0->sortKey = 5;
                        break;
                    case 13:
                        arg0->sortKey = 7;
                        break;
                    case 14:
                        arg0->sortKey = 9;
                        break;
                    case 15:
                        arg0->sortKey = 0xB;
                        break;
                }
                func_80027D68(M2C_FIELD(arg0, s32*, 0xB160), D_8910D990[arg0->sortKey]);
                arg0->state = 0;
                break;
            case 2:
                if (arg0->unk_982C != 0) {
                    a = arg0->levelFilterMax;
                    b = arg0->levelFilterMin;
                } else {
                    a = arg0->levelFilterMin;
                    b = arg0->levelFilterMax;
                }
                arg0->state = 4;
                LabPCList_InitLevelInputWindow(&arg0->levelInputWindow, 0x110, 0xF5, D_8910A7F4, a, b, LabPCList_HasFilterFlag(arg0, 1));
                break;
        }
    }
    return 0;
}

s32 LabPCList_UpdateLevelInput(void*);
M2C_UNK LabPCList_ApplyFiltersAndSort();
/**
 * Runs the レベルのにゅうりょく (level input) window and applies the level range filter.
 * Seen in play (2026-11-12) in いちらん: あつめる with 006から100 stored 6 and 100 at +0x9828/+0x9829, set
 * flag 1, and the Lv 5 party disappeared; かいじょ reset the range to 1-100 and cleared flag 1.
 */
s32 LabPCList_RunLevelFilter(s8 *arg)
{
  LabPCListScreen *arg0 = (LabPCListScreen *) arg;
  s32 ret;
  LabPCListScreen *new_var; // FAKE: permuter temp
  ret = LabPCList_UpdateLevelInput(&arg0->levelInputWindow);
  if (ret == (-1))
  {
    new_var = arg0;
    new_var->state = 0;
  }
  else
    if (ret == 1)
  {
    if (arg0->levelInputWindow.maxLevel.value >= arg0->levelInputWindow.minLevel.value)
    {
      arg0->unk_982C = 0;
      arg0->levelFilterMin = arg0->levelInputWindow.minLevel.value;
      arg0->levelFilterMax = arg0->levelInputWindow.maxLevel.value;
      arg0->sortKey = 1;
    }
    else
    {
      arg0->unk_982C = 1;
      arg0->levelFilterMax = arg0->levelInputWindow.minLevel.value;
      arg0->levelFilterMin = arg0->levelInputWindow.maxLevel.value;
      arg0->sortKey = 2;
    }
    LabPCList_SetFilterFlag((s8 *) arg0, 1);
    LabPCList_ApplyFiltersAndSort((s8 *) arg0);
    arg0->state = 0;
  }
  else
  {
 do { if (ret == 2) { arg0->levelFilterMin = 1; arg0->levelFilterMax = 100; arg0->unk_982C = 0; LabPCList_ClearFilterFlag((s8 *) arg0, 1); LabPCList_ApplyFiltersAndSort((s8 *) arg0); arg0->state = 0; } } while (0);  // FAKE
  }
  return 0;
}

s32 LabPCList_UpdateTypeFilter(s8*);
void LabPCList_CommitTypeFilter(s8*, s8*);
/**
 * Runs the type filter window and turns filter flag 2 on or off.
 * Seen in play (2026-11-12) in いちらん: ran while the タイプであつめる window was open.
 */
s32 LabPCList_RunTypeFilter(LabPCListScreen* arg0) {
    s8* sp24 = (s8*)arg0->typeFilterWindow;
    s32 ret = LabPCList_UpdateTypeFilter(sp24);

    if (ret == -1) {
        arg0->state = 0;
    } else if (ret == 1) {
        LabPCList_CommitTypeFilter(sp24, (s8*)&arg0->unk_9918);
        if (arg0->unk_9918 == 0) {
            LabPCList_ClearFilterFlag(arg0, 2);
        } else {
            LabPCList_SetFilterFlag(arg0, 2);
        }
        LabPCList_ApplyFiltersAndSort(arg0);
        arg0->state = 0;
    } else if (ret == 2) {
        arg0->unk_9918 = 0;
        LabPCList_ClearFilterFlag(arg0, 2);
        LabPCList_ApplyFiltersAndSort(arg0);
        arg0->state = 0;
    }
    return 0;
}

s32 LabPCList_UpdateMoveFilter(s8*);
void LabPCList_CommitMoveFilter(s8*, s8*);
/**
 * Runs the move filter window and turns filter flag 4 on or off.
 * Seen in play (2026-11-12) in いちらん: あつめる with ひっかく set filter flag 4 and left only ヒトカゲ (ひっさつまえば
 * left the list empty); かいじょ cleared flag 4 and all three party Pokémon returned.
 */
s32 LabPCList_RunMoveFilter(LabPCListScreen* arg0) {
    s8* sp24 = (s8*)arg0->moveFilterWindow;
    s32 ret = LabPCList_UpdateMoveFilter(sp24);

    if (ret == -1) {
        arg0->state = 0;
    } else if (ret == 1) {
        LabPCList_CommitMoveFilter(sp24, (s8*)&arg0->unk_9B00);
        if (arg0->unk_9B04 == 0) {
            LabPCList_ClearFilterFlag(arg0, 4);
        } else {
            LabPCList_SetFilterFlag(arg0, 4);
        }
        LabPCList_ApplyFiltersAndSort(arg0);
        arg0->state = 0;
    } else if (ret == 2) {
        arg0->unk_9B04 = 0;
        LabPCList_ClearFilterFlag(arg0, 4);
        LabPCList_ApplyFiltersAndSort(arg0);
        arg0->state = 0;
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
 * For every item of arg2 whose unk_08 is zero, whose unk_1C is at
 * least arg2->limit, or that is the item *arg1, sets bit 0 of the matching
 * entry in arg0->flags.
 */
void func_89103144(Flags89103144* arg0, Item89103144** arg1, List89103144* arg2) {
    s32 i;
    Item89103144* item;

    item = arg2->items;
    i = 0;
    if (arg2->count > 0) {
        do {
            if ((item->unk_08 == 0) || (item->unk_1C >= arg2->limit) || (item == *arg1)) {
                arg0->flags[i] |= 1;
            }
            i++;
            item++;
        } while (i < arg2->count);
    }
}

void func_891031B8(s8* arg0, s8** arg1, s8* arg2) {
    s32 i;
    s32 j;
    s8* box;
    s8* entry;

    for (box = M2C_FIELD(arg2, s8**, 0), i = 0; i < M2C_FIELD(arg2, s32*, 8); i++, box += 0x24) {
        for (entry = M2C_FIELD(box, s8**, 0x10), j = 0; j < M2C_FIELD(box, s32*, 0x18); j++, entry += 0x20) {
            if ((M2C_FIELD(entry, s32*, 8) != 0) && (M2C_FIELD(entry, s32*, 0x1C) < M2C_FIELD(box, s32*, 0x20)) &&
                (entry != *arg1)) {
                break;
            }
        }
        if (j >= M2C_FIELD(box, s32*, 0x18)) {
            M2C_FIELD(arg0, u16**, 4)[i] |= 1;
        }
    }
}

extern u8 D_8910A8DC[];
extern s32 D_8910DD34[];
void func_89103274(LabPCListScreen* arg0, s8** arg1) {
    LabPCList_InitPopupMenu(&arg0->subPopup, D_8910A8DC, (s8*)&arg0->popupItemFlags[1], 3, (s32)D_8910DD34);
    Window_SetRect((s8*)&arg0->subPopup.anchorX, arg0->popup.window.frame.x + 0xE, arg0->popup.window.frame.y + 0x38, 0x6C, 0x1C);
    arg0->subPopup.window.frame.style |= 0x1000000;
    arg0->subPopup.limitX = arg0->listFrame.x + arg0->listFrame.width;
    arg0->subPopup.limitY = arg0->listFrame.y + arg0->listFrame.height;
    LabPCList_PlacePopup(&arg0->subPopup);
    arg0->subPopup.window.frame.color = D_8910A7F4;
    func_891031B8((s8*)&arg0->subPopup.menu, arg1, (s8*)&arg0->sourceMatrix);
}

s32 func_89103370(s8 **arg0) {
    s32 var_v1;
    s8 *temp_v0;

    temp_v0 = *arg0;
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
s32 LabPCList_UpdateMonMenu(LabPCListScreen* arg0) {
    s32 ret = 0;
    s8* entry;

    LabPCList_UpdatePopupMenu(&arg0->popup);
    if (((u16*)D_800603C0)[4] & 0x4000) {
        func_8003F6AC(3);
        arg0->state = 0;
    } else if (((u16*)D_800603C0)[4] & 0x8000) {
        entry = ((PointerList*)arg0->list.items)->items[arg0->list.cursor];
        switch (arg0->popup.menu.cursor) {
            case 0:
                func_8003F6AC(2);
                if (LabPCList_ToggleFilterFlag(arg0, 8) != 0) {
                    arg0->unk_9E58 = M2C_FIELD(entry, u8*, 8);
                }
                LabPCList_ApplyFiltersAndSort(arg0);
                arg0->state = 0;
                break;
            case 1:
                func_8003F6AC(2);
                if (LabPCList_ToggleFilterFlag(arg0, 0x10) != 0) {
                    s32 id;

                    id = M2C_FIELD(entry, u8*, 8) - 1;
                    arg0->unk_9E5C = 1;
                    M2C_FIELD(arg0, u8*, 0x9E60) = D_80065D00[id].unk06;
                    if (D_80065D00[id].unk06 != D_80065D00[id].unk07) {
                        M2C_FIELD(arg0, u8*, 0x9E61) = D_80065D00[id].unk07;
                        arg0->unk_9E5C++;
                    }
                }
                LabPCList_ApplyFiltersAndSort(arg0);
                arg0->state = 0;
                break;
            case 2:
                if (func_89103370((s8**)entry) != 0) {
                    func_8003F6AC(8);
                    TextBox_Init((s8*)arg0->textBox, (s32)D_8910DD40, 0, 1, 0);
                    arg0->state = 0xB;
                } else {
                    func_8003F6AC(2);
                    func_89103274(arg0, (s8**)entry);
                    arg0->state = 8;
                }
                break;
            case 3:
                if (!(arg0->popup.menu.itemFlags[arg0->popup.menu.cursor] & 1)) {
                    func_8003F6AC(2);
                    arg0->state = 0;
                    ret = 2;
                } else {
                    func_8003F6AC(8);
                    TextBox_Init((s8*)arg0->textBox, (s32)D_8910DD58, 0, 1, 0);
                    arg0->state = 0xC;
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
void LabPCList_ReindexBoxSlots(u8* arg0) {
    s32 i;
    s32** ptr = M2C_FIELD(arg0, s32***, 0x14);

    for (i = 0; i < M2C_FIELD(arg0, s32*, 0x1C); i++) {
        (*ptr++)[1] = i;
    }
}
