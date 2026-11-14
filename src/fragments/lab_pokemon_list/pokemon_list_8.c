/* Fixed-layout split; original translation-unit boundaries remain unconfirmed. */
#include "global.h"
#include "lab_pokemon_list.h"
#include "asset_archive.h"
#include "memory_main.h"
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
s32 LabPCList_UpdateLevelInput(void*);
M2C_UNK LabPCList_ApplyFiltersAndSort();
extern u8 D_8910A8DC[];
extern s32 D_8910DD34[];
void TextBox_Init(s8* arg0, s32 arg1, s32 arg2, s32 arg3, u32 arg4);
extern Info891033A0 D_80065D00[];
extern s8 D_8910DD40[];
extern s8 D_8910DD58[];
u32 func_800566BC(s8*);

typedef struct Head89103740 { char unk00[0xC]; s32 unkC; } Head89103740;
typedef struct Sub89103740 { Head89103740* head; s32 unk04; char unk08[8]; s32 unk10; char unk14[8]; s32 count; } Sub89103740; // 0x20
typedef struct Item89103740 { char unk00[0x10]; Sub89103740* subs; char unk14[0x10]; } Item89103740; // 0x24
typedef struct Ref89103740 { Sub89103740* sub; s32 unk04; } Ref89103740;
typedef struct Msg89103740 { void* unk00; s32 unk04; void* unk08; void* unk0C; } Msg89103740;
extern char D_8910DD94[];
extern char D_8910E398[];
extern char D_8910E3A8[];
void func_80027868(s8*, s32);
void func_80027814(s8*, Ref89103740*, s32);
/**
 * Moves the selected Pokemon to source `sourceIndex`, box `box`, and shows the いどう (moved) message.
 * Seen in play (2026-11-12) in いちらん: ran with kind 1 (GB) or 2 (64 cartridge) and box 0, showed
 * the いどう message and left two Pokémon in the party.
 */
void LabPCList_MoveMonTo(LabPCListScreen* screen, Ref89103740* entry, s32 sourceIndex, s32 box, Msg89103740* msg) {
    Item89103740* items = M2C_FIELD(screen, Item89103740**, 0x420);
    Sub89103740* sub = &items[sourceIndex].subs[box];
    Sub89103740* old = entry->sub;
    msg->unk00 = D_8910DD94;
    msg->unk04 = 1;
    LabPCList_FormatLocationName(D_8910E398, entry->sub->head->unkC, entry->sub->unk04);
    msg->unk08 = D_8910E398;
    LabPCList_FormatLocationName(D_8910E3A8, sourceIndex, box);
    msg->unk0C = D_8910E3A8;
    func_80027868(old->unk14, entry->unk04);
    LabPCList_ReindexBoxSlots((u8*)old);
    entry->sub = sub;
    entry->unk04 = sub->count;
    func_80027814(sub->unk14, entry, sub->count);
    old->unk10 = 1;
    sub->unk10 = 1;
    screen->hasChanges = 1;
}

typedef struct List89103C54 {
    /* 0x00 */ Ref89103740** items;
} List89103C54;
void func_800307D4(List89103C54**, s32, s32);


extern u8 D_8910A8E8[];
void LabPCList_DisableUnavailableBoxes(s8*, Ref89103740*, s32);
/**
 * Handles the どこへ？ (where to?) menu: party, GB box, Stadium box, or a box list.
 * Seen in play (2026-11-12) in いちらん (party list: フシギダネ, ヒトカゲ, ゼニガメ): いどうする opened 「どこへ？」 with
 * てもちのポケモン, ゲームボーイのボックス and 64カセットのボックス while this ran.
 */
s32 LabPCList_UpdateDestinationMenu(LabPCListScreen* screen) {
    s32 ret = 0;
    s32 cursor;
    s32 top;

    LabPCList_UpdatePopupMenu(&screen->subPopup.window.frame.x);
    if (*(u16*)(D_800603C0 + 8) & 0x4000) {
        Audio_PlaySystemSound(3);
        screen->state = 7;
    } else if (*(u16*)(D_800603C0 + 8) & 0x8000) {
        if (!(screen->subPopup.menu.itemFlags[screen->subPopup.menu.cursor] & 1)) {
            switch (screen->subPopup.menu.cursor) {
                case 0:
                    Audio_PlaySystemSound(0x18);
                    cursor = screen->list.cursor;
                    top = screen->list.cursor - screen->list.scrollY / screen->list.cellHeight;
                    LabPCList_MoveMonTo((LabPCListScreen*)screen, ((List89103C54*)screen->list.items)->items[screen->list.cursor], 0, 0, screen->msg);
                    LabPCList_FlattenEntries(&screen->rows, (unk_func_8830867C_02C_144*)&screen->sourceMatrix.rows);
                    LabPCList_ApplyFiltersAndSort(screen);
                    func_800307D4(&screen->list.items, cursor, top);
                    screen->state = 0;
                    ret = 3;
                    break;
                case 3:
                    Audio_PlaySystemSound(0x18);
                    cursor = screen->list.cursor;
                    top = screen->list.cursor - screen->list.scrollY / screen->list.cellHeight;
                    LabPCList_MoveMonTo((LabPCListScreen*)screen, ((List89103C54*)screen->list.items)->items[screen->list.cursor], 3, 0, screen->msg);
                    LabPCList_FlattenEntries(&screen->rows, (unk_func_8830867C_02C_144*)&screen->sourceMatrix.rows);
                    LabPCList_ApplyFiltersAndSort(screen);
                    func_800307D4(&screen->list.items, cursor, top);
                    screen->state = 0;
                    ret = 3;
                    break;
                case 1:
                    Audio_PlaySystemSound(2);
                    LabPCList_InitPopupMenu(&screen->subPopup2, D_8910A8E8, (s8*)&screen->popupItemFlags[2], 8, 0);
                    Window_SetRect((s8*)&screen->subPopup2.anchorX, screen->subPopup.window.frame.x + 0xE, screen->subPopup.window.frame.y + 0x1C, 0xE4, 0x1C);
                    screen->subPopup2.window.frame.style |= 0x01000000;
                    screen->subPopup2.limitX = screen->listFrame.x + screen->listFrame.width;
                    screen->subPopup2.limitY = screen->listFrame.y + screen->listFrame.height;
                    LabPCList_PlacePopup(&screen->subPopup2);
                    screen->subPopup2.window.frame.color = D_8910A7F4;
                    LabPCList_DisableUnavailableBoxes((s8*)&screen->subPopup2.menu, ((List89103C54*)screen->list.items)->items[screen->list.cursor], screen->sourceMatrix.rows + 0x24);
                    screen->state = 9;
                    break;
                case 2:
                    Audio_PlaySystemSound(2);
                    LabPCList_InitPopupMenu(&screen->subPopup2, D_8910A8E8, (s8*)&screen->popupItemFlags[2], 4, 0);
                    Window_SetRect((s8*)&screen->subPopup2.anchorX, screen->subPopup.window.frame.x + 0xE, screen->subPopup.window.frame.y + 0x38, 0xE4, 0x1C);
                    screen->subPopup2.window.frame.style |= 0x01000000;
                    screen->subPopup2.limitX = screen->listFrame.x + screen->listFrame.width;
                    screen->subPopup2.limitY = screen->listFrame.y + screen->listFrame.height;
                    LabPCList_PlacePopup(&screen->subPopup2);
                    screen->subPopup2.window.frame.color = D_8910A7F4;
                    LabPCList_DisableUnavailableBoxes((s8*)&screen->subPopup2.menu, ((List89103C54*)screen->list.items)->items[screen->list.cursor], screen->sourceMatrix.rows + 0x48);
                    screen->state = 0xA;
                    break;
            }
        } else {
            Audio_PlaySystemSound(8);
        }
    }
    return ret;
}


/**
 * Moves the Pokemon to the chosen Game Boy box.
 * Seen in play (2026-11-12) in いちらん: いどうする > ゲームボーイのボックス showed ボックス1-8; ボックス1 moved フシギダネ out of
 * the party (「いどう てもち -> GB 1」).
 */
s32 LabPCList_UpdateGbBoxMenu(LabPCListScreen* screen) {
    s32 ret = 0;
    s32 cursor;
    s32 top;

    LabPCList_UpdatePopupMenu(&screen->subPopup2);
    if (*(u16*)(D_800603C0 + 8) & 0x4000) {
        Audio_PlaySystemSound(3);
        screen->state = 8;
    } else if (*(u16*)(D_800603C0 + 8) & 0x8000) {
        if (!(screen->subPopup2.menu.itemFlags[screen->subPopup2.menu.cursor] & 1)) {
            cursor = screen->list.cursor;
            top = screen->list.cursor - screen->list.scrollY / screen->list.cellHeight;
            Audio_PlaySystemSound(0x18);
            LabPCList_MoveMonTo((LabPCListScreen*)screen, ((List89103C54*)screen->list.items)->items[screen->list.cursor], 1, screen->subPopup2.menu.cursor, screen->msg);
            LabPCList_FlattenEntries(&screen->rows, (unk_func_8830867C_02C_144*)&screen->sourceMatrix);
            LabPCList_ApplyFiltersAndSort(screen);
            func_800307D4(&screen->list.items, cursor, top);
            screen->state = 0;
            ret = 3;
        } else {
            Audio_PlaySystemSound(8);
        }
    }
    return ret;
}

/**
 * Moves the Pokemon to the chosen Stadium (64 cartridge) box.
 * Seen in play (2026-11-12) in いちらん: いどうする > 64カセットのボックス showed ボックス1-4; ボックス1 moved フシギダネ out of
 * the party (「いどう てもち -> 64 1」).
 */
s32 LabPCList_UpdateStadiumBoxMenu(LabPCListScreen* screen) {
    s32 ret = 0;
    s32 cursor;
    s32 top;

    LabPCList_UpdatePopupMenu(&screen->subPopup2);
    if (*(u16*)(D_800603C0 + 8) & 0x4000) {
        Audio_PlaySystemSound(3);
        screen->state = 8;
    } else if (*(u16*)(D_800603C0 + 8) & 0x8000) {
        if (!(screen->subPopup2.menu.itemFlags[screen->subPopup2.menu.cursor] & 1)) {
            cursor = screen->list.cursor;
            top = screen->list.cursor - screen->list.scrollY / screen->list.cellHeight;
            Audio_PlaySystemSound(0x18);
            LabPCList_MoveMonTo((LabPCListScreen*)screen, ((List89103C54*)screen->list.items)->items[screen->list.cursor], 2, screen->subPopup2.menu.cursor, screen->msg);
            LabPCList_FlattenEntries(&screen->rows, (unk_func_8830867C_02C_144*)&screen->sourceMatrix);
            LabPCList_ApplyFiltersAndSort(screen);
            func_800307D4(&screen->list.items, cursor, top);
            screen->state = 0;
            ret = 3;
        } else {
            Audio_PlaySystemSound(8);
        }
    }
    return ret;
}

typedef struct Msg89103F04 {
    /* 0x00 */ void* text;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ s32 oldValue;
    /* 0x0C */ s32 newValue;
} Msg89103F04;
extern char D_8910DDFC[];
extern char D_8910DE04[];
extern char D_8910DE10[];
extern char D_8910DE1C[];
extern char D_8910DE28[];
extern char D_8910DE34[];
u16 func_80020234(s32, u8, s32, u8, s32);
s32 func_8002057C(u8, u16);
void func_800203FC(BattleMon*);
void LabPCList_ConsumeUsedItem();
/**
 * Uses a vitamin (HP Up, Protein, Iron, Carbos, Calcium; 0x23-0x27) or a Rare Candy (0x28) on the
 * Pokemon and fills in the old and new values for the result message.
 * Seen in play (2026-11-12) in いちらん: マックスアップ (HP Up) on フシギダネ showed HP 19 -> 20, and
 * ふしぎなアメ showed レベル 5 -> 6 with the stats recomputed. After レポートしてやめる the Game Boy save
 * had HP stat exp +0xA00, max HP 20 and one HP Up fewer.
 */
void LabPCList_ApplyVitaminItem(u8** entry, u8** item, Msg89103F04* msg) {
    BattleMon* mon;
    u16 old_max_hp;

    msg->unk04 = 0;
    mon = (BattleMon*)((u8*)entry + 8);
    switch (**item) {
        case 0x23:
            msg->text = D_8910DDFC;
            msg->oldValue = mon->maxHp;
            mon->statExp[0] += 0xA00;
            if (mon->statExp[0] > 0x6400) {
                mon->statExp[0] = 0x6400;
            }
            mon->maxHp = func_80020234(1, mon->species.id, mon->statExp[0], mon->level, mon->dvs);
            msg->newValue = mon->maxHp;
            break;
        case 0x24:
            msg->text = D_8910DE04;
            msg->oldValue = mon->attack;
            mon->statExp[1] += 0xA00;
            if (mon->statExp[1] > 0x6400) {
                mon->statExp[1] = 0x6400;
            }
            mon->attack = func_80020234(2, mon->species.id, mon->statExp[1], mon->level, mon->dvs);
            msg->newValue = mon->attack;
            break;
        case 0x25:
            msg->text = D_8910DE10;
            msg->oldValue = mon->defense;
            mon->statExp[2] += 0xA00;
            if (mon->statExp[2] > 0x6400) {
                mon->statExp[2] = 0x6400;
            }
            mon->defense = func_80020234(3, mon->species.id, mon->statExp[2], mon->level, mon->dvs);
            msg->newValue = mon->defense;
            break;
        case 0x26:
            msg->text = D_8910DE1C;
            msg->oldValue = mon->speed;
            mon->statExp[3] += 0xA00;
            if (mon->statExp[3] > 0x6400) {
                mon->statExp[3] = 0x6400;
            }
            mon->speed = func_80020234(4, mon->species.id, mon->statExp[3], mon->level, mon->dvs);
            msg->newValue = mon->speed;
            break;
        case 0x27:
            msg->text = D_8910DE28;
            msg->oldValue = mon->special;
            mon->statExp[4] += 0xA00;
            if (mon->statExp[4] > 0x6400) {
                mon->statExp[4] = 0x6400;
            }
            mon->special = func_80020234(5, mon->species.id, mon->statExp[4], mon->level, mon->dvs);
            msg->newValue = mon->special;
            break;
        case 0x28:
            msg->text = D_8910DE34;
            msg->oldValue = mon->level;
            old_max_hp = mon->maxHp;
            mon->exp = func_8002057C(mon->species.id, mon->level + 1);
            func_800203FC(mon);
            mon->hp += mon->maxHp - old_max_hp;
            msg->newValue = mon->level;
            break;
    }
    LabPCList_ConsumeUsedItem(item);
    *(s32*)(entry[0] + 0x10) = 1;
}

typedef struct Entry891041D8 {
    /* 0x0 */ char* name;
    /* 0x4 */ char unk04[0x8];
} Entry891041D8; // size = 0xC
typedef struct Msg891041D8 {
    /* 0x00 */ s8* text;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ s32 oldPp;
    /* 0x0C */ s32 newPp;
} Msg891041D8;
extern Entry891041D8 D_8006A9CC[];
typedef struct Str891041D8 {
    char c[7];
} Str891041D8;
extern char D_8910DE3C[];
extern s8 D_8910E3B8[];

/**
 * Uses a PP Up on move slot `slot` of the Pokemon and writes the result message.
 * Seen in play (2026-11-12) in いちらん: ポイントアップ on フシギダネ, move slot 0, showed 「たいあたりのPP」 35 -> 42.
 */
void LabPCList_ApplyPpUpItem(u8** entry, s32 item, s32 slot, Msg891041D8* msg) {
    u8* ptr;
    s32 base_pp;
    s32 step;
    s8* end;

    func_8000A460(D_8910E3B8, D_8006A9CC[*(u8*)((u32)entry + slot + 0x11)].name); // FAKE: integer cast keeps entry + slot from being reused
    ptr = (u8*)entry + slot + 8;
    end = D_8910E3B8 + func_800566BC(D_8910E3B8);
    *(Str891041D8*)end = *(Str891041D8*)D_8910DE3C;
    if (1) {} // karodo
    msg->text = D_8910E3B8;
    msg->unk04 = 0;
    base_pp = gMoveData[ptr[9] - 1].pp;
    step = base_pp / 5;
    if (step >= 7) {
        step = 7;
    }
    msg->oldPp = (ptr[0x20] >> 6) * step + base_pp;
    msg->newPp = msg->oldPp + step;
    ptr[0x20] += step + 0x40;
    LabPCList_ConsumeUsedItem(item, ptr, base_pp, msg);
    *(s32*)(entry[0] + 0x10) = 1;
}

u8 Move_GetIdFromTableIndex(s32 arg0);

/**
 * Teaches the TM or HM move of `item` in move slot `slot` (item ids from 0xC9 are TMs, below are HMs).
 * Seen in play (2026-11-12) in いちらん: わざマシン06 on フシギダネ ran this with slot 2, and どくどく (Toxic) then
 * appeared as わざ3.
 */
void LabPCList_TeachTmHmMove(u8** entry, u8** item, s32 slot) {
    u8* ptr;
    s32 var_a0;

    if (*item[0] >= 0xC9) {
        var_a0 = *item[0] - 0xC9;
    } else {
        var_a0 = *item[0] - 0x92;
    }

    ptr = (u8*)entry + slot + 8;
    ptr[9] = Move_GetIdFromTableIndex(var_a0);
    ptr[0x20] = gMoveData[ptr[9] - 1].pp;

    if (*item[0] >= 0xC9) {
        LabPCList_ConsumeUsedItem(item);
    }
    *(s32*)(entry[0] + 0x10) = 1;
}

s32 LabPCList_UpdateBrowse();
s32 LabPCList_UpdateSortMenu(LabPCListScreen*);
s32 LabPCList_UpdateColumnMenu(LabPCListScreen*);
s32 LabPCList_RunLevelFilter(s8*);
s32 LabPCList_UpdateMonMenu(LabPCListScreen*);
s32 LabPCList_UpdateGbBoxMenu();
s32 LabPCList_UpdateStadiumBoxMenu();
s32 Ui_CheckConfirmPressed(void*);
/**
 * Runs the list window's state machine (browse, sort menu, filters, moves).
 * Seen in play (2026-11-12): ran the list window.
 */
s32 LabPCList_UpdateList(LabPCListScreen* screen) {
    s32 ret = 0;

    if (screen->window.state == 0) {
        return 0;
    }
    switch (screen->state) {
        case 0:
            ret = LabPCList_UpdateBrowse(screen);
            break;
        case 1:
            ret = LabPCList_UpdateSourceSelect(screen);
            break;
        case 2:
            ret = LabPCList_UpdateSortMenu(screen);
            break;
        case 3:
            ret = LabPCList_UpdateColumnMenu(screen);
            break;
        case 4:
            ret = LabPCList_RunLevelFilter(screen);
            break;
        case 5:
            ret = LabPCList_RunTypeFilter(screen);
            break;
        case 6:
            ret = LabPCList_RunMoveFilter(screen);
            break;
        case 7:
            ret = LabPCList_UpdateMonMenu(screen);
            break;
        case 8:
            ret = LabPCList_UpdateDestinationMenu(screen);
            break;
        case 9:
            ret = LabPCList_UpdateGbBoxMenu(screen);
            break;
        case 10:
            ret = LabPCList_UpdateStadiumBoxMenu(screen);
            break;
        case 11:
        case 12:
            if (Ui_CheckConfirmPressed((s8*)screen->textBox) == 1) {
                screen->state = 0;
            }
            break;
    }
    return ret;
}

/**
 * Sets the state to the list and sets up the list screen, which gets the item result message.
 * Seen in play (2026-11-12) in いちらん (party list: フシギダネ, ヒトカゲ, ゼニガメ): ran on entry, right before
 * LabPCList_InitListWindow.
 */
void LabPCList_InitScreen(LabPCList* lab) {
    lab->state = 0;
    LabPCList_InitListWindow(&lab->listScreen, 0x26, 0x48, (s32)&lab->message);
}

void SavePrompt_Init(SavePrompt*, s32, s32);
void Save_DrawReportingWindow(SavePrompt*);
s32 SavePrompt_Update(SavePrompt*);
void LabPCList_SaveChanges(LabPCListScreen*);
void LabPCList_InitItemWindow(LabItemWindow*, s32, s32, s8*, s8*, s32);
s32 LabPCList_UpdateItemWindow(LabItemWindow*);
void LabPCList_InitMessageWindow(LabMessageWindow*, s32, s32, LabItemResult*);
s32 LabPCList_UpdateMessageWindow(LabMessageWindow*);
void LabPCList_UpdateItemUsability(s8*, s32);
/**
 * Per-frame update of the いちらん screen: runs the list, the save prompt, the item window or the
 * message window by state. Returns 1 when the caller should leave this screen.
 * Seen in play (2026-11-12): ran the いちらん screen.
 */
s32 LabPCList_UpdateScreen(LabPCList* lab) {
    s32 ret = 0;
    s32 r;
    s8* sub;

    switch (lab->state) {
        case 0:
            sub = (s8*)&lab->listScreen;
            r = LabPCList_UpdateList(sub);
            if (r == 1) {
                if (lab->listScreen.hasChanges != 0) {
                    SavePrompt_Init(&lab->savePrompt, 0xCA, 0xAD);
                    lab->state = 1;
                } else {
                    ret = 1;
                }
            } else if (r == 2) {
                LabPCList_UpdateItemUsability((s8*)&lab->listScreen + 0xAFFC, ((s32*)lab->listScreen.list.items->rows)[lab->listScreen.list.cursor] + 8);
                LabPCList_InitItemWindow(&lab->itemWindow, ((LabPCListScreen*)sub)->window.frame.x + 0xAB, ((LabPCListScreen*)sub)->window.frame.y + 0xD, sub + 0xAFFC,
                              sub + 0xB008, ((s32**)((LabPCListScreen*)sub)->list.items->rows)[((LabPCListScreen*)sub)->list.cursor]);
                lab->state = 2;
            } else if (r == 3) {
                LabPCList_InitMessageWindow(&lab->messageWindow, 0xB6, 0xEA, &lab->message);
                lab->state = 3;
            }
            break;
        case 1:
            sub = (s8*)&lab->savePrompt;
            r = SavePrompt_Update((SavePrompt*)sub);
            if (r == -1) {
                lab->state = 0;
            } else if (r > 0) {
                switch (r) {
                    case 1:
                        Save_DrawReportingWindow((SavePrompt*)sub);
                        LabPCList_SaveChanges(&lab->listScreen);
                        ret = 1;
                        break;
                    case 2:
                        ret = 1;
                        break;
                }
            }
            break;
        case 2:
            r = LabPCList_UpdateItemWindow(&lab->itemWindow);
            if (r == -1) {
                lab->state = 0;
            } else {
                s32 off = 0xB55C; // FAKE: stops IDO reusing lab + 0x8000 for the store below.

                if (r > 0) {
                    s32 a1 = ((s32*)lab->itemWindow.list.items->rows)[lab->itemWindow.list.cursor];
                    s32 a0 = ((s32*)lab->listScreen.list.items->rows)[lab->listScreen.list.cursor];

                    switch (r) {
                        case 1:
                            LabPCList_ApplyVitaminItem((u8**)a0, (u8**)a1, (Msg89103F04*)&lab->message);
                            break;
                        case 2:
                            LabPCList_ApplyPpUpItem((u8**)a0, a1, lab->itemWindow.moveSelect.menu.cursor, (Msg891041D8*)&lab->message);
                            break;
                        case 3:
                            LabPCList_TeachTmHmMove((u8**)a0, (u8**)a1, lab->itemWindow.moveSelect.menu.cursor);
                            break;
                    }
                    *(s32*)((s8*)lab + off) = 1;
                    if (r == 3) {
                        lab->state = 0;
                    } else {
                        LabPCList_InitMessageWindow(&lab->messageWindow, 0xB6, 0xEA, &lab->message);
                        lab->state = 3;
                    }
                }
            }
            break;
        case 3:
            if (LabPCList_UpdateMessageWindow(&lab->messageWindow) == 1) {
                lab->state = 0;
            }
            break;
    }
    return ret;
}

M2C_UNK Ui_DrawTintedScreenBackground(M2C_UNK, M2C_UNK, u8, u8, s32); /* extern */
extern M2C_UNK D_8910A7F0;

/**
 * Draws the tinted terminal screen background.
 * Seen in play (2026-11-12): the いちらん background.
 */
void LabPCList_DrawBackground(void) {
    Ui_DrawTintedScreenBackground(0x38, 0x1E0, M2C_FIELD(&D_8910A7F0, u8 *, 0), M2C_FIELD(&D_8910A7F0, u8 *, 1), (s32) M2C_FIELD(&D_8910A7F0, u8 *, 2));
}

void BgStage_DrawFrame(void);
s32 Window_UpdateAnimation(Window* arg0);
void SavePrompt_Draw(SavePrompt*);
void LabPCList_DrawItemWindow(LabItemWindow*);
void LabPCList_DrawMessageWindow(LabMessageWindow*);

/**
 * Draws the lab PC list for its current state.
 * Seen in play (2026-11-12): drew the いちらん screen.
 */
M2C_UNK LabPCList_DrawScreen(LabPCList* lab) {
    BgStage_DrawFrame();
    switch (lab->state) {
        case 0:
            if (Window_UpdateAnimation(&lab->listScreen) != 0) {
                LabPCList_DrawBackground();
            }
            LabPCList_DrawListScreen(&lab->listScreen);
            break;
        case 1:
            if (Window_UpdateAnimation(&lab->listScreen) != 0) {
                LabPCList_DrawBackground();
            }
            LabPCList_DrawListScreen(&lab->listScreen);
            SavePrompt_Draw(&lab->savePrompt);
            break;
        case 2:
            if (Window_UpdateAnimation(&lab->listScreen) != 0) {
                LabPCList_DrawBackground();
            }
            if (Window_UpdateAnimation(&lab->itemWindow) != 0) {
                LabPCList_DrawListScreen(&lab->listScreen);
            }
            LabPCList_DrawItemWindow(&lab->itemWindow);
            break;
        case 3:
            if (Window_UpdateAnimation(&lab->listScreen) != 0) {
                LabPCList_DrawBackground();
            }
            LabPCList_DrawListScreen(&lab->listScreen);
            LabPCList_DrawMessageWindow(&lab->messageWindow);
            break;
    }
}

void func_80027FF8(void*, s32);
extern M2C_UNK D_8910E380;
extern LabPCList D_8910E3D0;

/**
 * Seen in play (2026-11-12): runs once when いちらん opens; it reads the active controller port and
 * calls LabPCList_InitScreen. The old name BattlePrep_UpdateSingleBattleIntroFrame was a Stadium
 * 1 name for the same address.
 */
void LabPCList_Setup(void) {
    D_8910E37C = func_80025BD8();
    if (D_8910E37C != -1) {
        func_80027FF8(&D_8910E380, D_8910E37C);
    }
    LabPCList_InitScreen(&D_8910E3D0);
}

typedef struct Col891049E8 { u8 r, g, b, a; } Col891049E8;
extern s32 D_8910A908;
extern s32 D_8910A90C;
/*
 * Second name for D_8910A908. The fade-out store in this function family
 * (also FreeBattle_UpdateFade, LabTerminal_UpdateFade, LabPCList_UpdateFade, Pokedex_DrawFadeFrame) does not
 * share the counter's address with the load before it, which only happens
 * when the two accesses name different symbols.
 */
extern s32 D_8910A908_2;
extern M2C_UNK D_8910DE44;
M2C_UNK GbSave_DrawSummaryBar(M2C_UNK, M2C_UNK *, M2C_UNK *, s32);
void func_8002C8D8(Col891049E8*, Col891049E8, f32);
/**
 * Steps the screen fade; returns once eight frames have passed.
 * Seen in play (2026-11-13) ran on the frames the いちらん (list) screen faded in from the main menu.
 */
s32 LabPCList_UpdateFade(UNUSED s32 unused) {
    Col891049E8 sp2C;
    M2C_UNK *var_a1;
    s32 n;

    n = D_8910A908;
    if (n >= 8) {
        D_8910A90C = 1;
    }
    if (D_8910A90C != 0) {
        n--;
        D_8910A908_2 = n;
    }
    BgStage_DrawFrame();
    if (D_8910E37C == -1) {
        var_a1 = NULL;
    } else {
        var_a1 = &D_8910E380;
    }
    GbSave_DrawSummaryBar(0, var_a1, &D_8910DE44, D_8910E37C);
    n = D_8910A908;
    func_8002C8D8(&sp2C, *(Col891049E8*)&D_8910A7F0, n / (f64)8.0f);
    Ui_DrawTintedScreenBackground(0x38, 0x1E0, sp2C.r, sp2C.g, sp2C.b);
    if (D_8910A90C == 0) {
        n = D_8910A908;
        n++;
        D_8910A908 = n;
    }
    return 0;
}

void Cont_StartReadInputs(void);                            /* extern */
void Cont_ReadInputs(void);                            /* extern */
extern LabPCList D_8910E3D0;

/**
 * One frame of the Pokemon list screen.
 * Seen in play (2026-11-12): ran every frame of いちらん.
 */
void LabPCList_RunFrame(UNUSED s32 unused) {
    Cont_StartReadInputs();
    Cont_ReadInputs();
    LabPCList_DrawScreen(&D_8910E3D0);
    LabPCList_UpdateScreen(&D_8910E3D0);
}

extern u8 D_01000000[];
extern u8 D_002E0BE0[];
extern u8 D_002E2B90[];
extern u8 D_04000000[];
extern u8 D_00400F70[];
extern u8 D_004076E0[];
extern u8 D_88000000[];
extern u8 D_00235D70[];
extern u8 D_00238BD0[];
s32 LabPCList_UpdateFade(s32);

/**
 * LabPCList_Init
 *
 * Fragment entry point.  It has the same steps as LabTerminal_Init (and the Pokedex
 * entry function Pokedex_Main), differing only in the functions it calls in
 * steps 4 and 5.  Neither argument is used.  The steps are:
 *
 *   1. main_pool_push_state('TERM') saves the main pool state under that tag;
 *      the matching main_pool_pop_state('TERM') is near the end.
 *   2. Font_Init(0x3C, 0) is called (Font_Init in symbol_addrs.txt).
 *   3. Two assets are loaded with Asset_LoadToSegment: the ROM range
 *      D_002E0BE0..D_002E2B90 into segment 1 and D_00400F70..D_004076E0 into
 *      segment 4.  The segment number is bits 24-27 of the address of
 *      D_01000000 / D_04000000.
 *   4. LabPCList_Setup() and StageLoader_UpdateSegments() are called.
 *   5. BgStage_RunUntilCondition is run three times, with timer values 8, 0
 *      and 8: the first and third with callback LabPCList_UpdateFade, the second
 *      with LabPCList_RunFrame: fade in, run the list until it exits, fade out.
 *   6. StageLoader_WaitForRetrace() and main_pool_pop_state('TERM').
 *   7. Fragment_QueueCall queues a call to the fragment whose id comes from
 *      the address D_88000000 (bits 20-27, minus 0x10), with the ROM range
 *      D_00235D70..D_00238BD0.
 *
 * Returns 0x8040.
 * Seen in play (2026-11-12) in いちらん (party list: フシギダネ, ヒトカゲ, ゼニガメ): ran when いちらん was entered
 * from the main menu, before LabPCList_InitScreen.
 */
s32 LabPCList_Init(UNUSED s32 unused0, UNUSED s32 unused1) {
    main_pool_push_state('TERM');
    Font_Init(0x3C, 0);
    Asset_LoadToSegment(((u32)D_01000000 & 0x0F000000) >> 0x18, D_002E0BE0, D_002E2B90, 0);
    Asset_LoadToSegment(((u32)D_04000000 & 0x0F000000) >> 0x18, D_00400F70, D_004076E0, 0);
    LabPCList_Setup();
    StageLoader_UpdateSegments();
    BgStage_RunUntilCondition(8, LabPCList_UpdateFade);
    BgStage_RunUntilCondition(0, LabPCList_RunFrame);
    BgStage_RunUntilCondition(8, LabPCList_UpdateFade);
    StageLoader_WaitForRetrace();
    main_pool_pop_state('TERM');
    Fragment_QueueCall(((((u32)D_88000000) & 0x0FF00000) >> 0x14) - 0x10, D_00235D70, D_00238BD0, 0, 0);
    return 0x8040;
}
