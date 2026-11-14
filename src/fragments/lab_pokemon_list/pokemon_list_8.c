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
void func_89109990(void*, void*, void*, s32);
extern s32 D_800603C0;
void func_8000B2F4(s32);
void Window_SetRect(s8 *, s32, s32, s32, s32);
void func_80027804(s8*, s8*, s32, s32);
void func_89109B60(s8*);
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
M2C_UNK LabPCList_ApplyFiltersAndSort();
extern s32 D_8910D9D0;
extern s32 D_8910D9D4;
s32 LabPCList_UpdateLevelInput(void*);
M2C_UNK LabPCList_ApplyFiltersAndSort();
s32 LabPCList_UpdateTypeFilter(s8*);
void LabPCList_CommitTypeFilter(s8*, s8*);
s32 LabPCList_UpdateMoveFilter(s8*);
void LabPCList_CommitMoveFilter(s8*, s8*);
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
 * Moves the selected Pokemon to location kind `arg2`, box `arg3`, and shows the いどう (moved) message.
 * Seen in play (2026-11-12) in いちらん: ran with kind 1 (GB) or 2 (64 cartridge) and box 0, showed
 * the いどう message and left two Pokémon in the party.
 */
void LabPCList_MoveMonTo(LabPCListScreen* arg0, Ref89103740* arg1, s32 arg2, s32 arg3, Msg89103740* arg4) {
    Item89103740* items = M2C_FIELD(arg0, Item89103740**, 0x420);
    Sub89103740* sub = &items[arg2].subs[arg3];
    Sub89103740* old = arg1->sub;
    arg4->unk00 = D_8910DD94;
    arg4->unk04 = 1;
    LabPCList_FormatLocationName(D_8910E398, arg1->sub->head->unkC, arg1->sub->unk04);
    arg4->unk08 = D_8910E398;
    LabPCList_FormatLocationName(D_8910E3A8, arg2, arg3);
    arg4->unk0C = D_8910E3A8;
    func_80027868(old->unk14, arg1->unk04);
    LabPCList_ReindexBoxSlots((u8*)old);
    arg1->sub = sub;
    arg1->unk04 = sub->count;
    func_80027814(sub->unk14, arg1, sub->count);
    old->unk10 = 1;
    sub->unk10 = 1;
    arg0->hasChanges = 1;
}

typedef struct List89103C54 {
    /* 0x00 */ Ref89103740** items;
} List89103C54;
void func_800307D4(List89103C54**, s32, s32);
void func_89109C6C(s8*, s8*);


extern u8 D_8910A8E8[];
void func_89103144(s8*, Ref89103740*, s32);
/**
 * Handles the どこへ？ (where to?) menu: party, GB box, Stadium box, or a box list.
 * Seen in play (2026-11-12) in いちらん (party list: フシギダネ, ヒトカゲ, ゼニガメ): いどうする opened 「どこへ？」 with
 * てもちのポケモン, ゲームボーイのボックス and 64カセットのボックス while this ran.
 */
s32 LabPCList_UpdateDestinationMenu(LabPCListScreen* arg0) {
    s32 ret = 0;
    s32 cursor;
    s32 top;

    LabPCList_UpdatePopupMenu(&arg0->subPopup.window.frame.x);
    if (*(u16*)(D_800603C0 + 8) & 0x4000) {
        func_8003F6AC(3);
        arg0->state = 7;
    } else if (*(u16*)(D_800603C0 + 8) & 0x8000) {
        if (!(arg0->subPopup.menu.itemFlags[arg0->subPopup.menu.cursor] & 1)) {
            switch (arg0->subPopup.menu.cursor) {
                case 0:
                    func_8003F6AC(0x18);
                    cursor = arg0->list.cursor;
                    top = arg0->list.cursor - arg0->list.scrollY / arg0->list.cellHeight;
                    LabPCList_MoveMonTo((LabPCListScreen*)arg0, ((List89103C54*)arg0->list.items)->items[arg0->list.cursor], 0, 0, arg0->msg);
                    func_89109C6C((s8*)&arg0->rows, (s8*)&arg0->sourceMatrix.rows);
                    LabPCList_ApplyFiltersAndSort(arg0);
                    func_800307D4(&arg0->list.items, cursor, top);
                    arg0->state = 0;
                    ret = 3;
                    break;
                case 3:
                    func_8003F6AC(0x18);
                    cursor = arg0->list.cursor;
                    top = arg0->list.cursor - arg0->list.scrollY / arg0->list.cellHeight;
                    LabPCList_MoveMonTo((LabPCListScreen*)arg0, ((List89103C54*)arg0->list.items)->items[arg0->list.cursor], 3, 0, arg0->msg);
                    func_89109C6C((s8*)&arg0->rows, (s8*)&arg0->sourceMatrix.rows);
                    LabPCList_ApplyFiltersAndSort(arg0);
                    func_800307D4(&arg0->list.items, cursor, top);
                    arg0->state = 0;
                    ret = 3;
                    break;
                case 1:
                    func_8003F6AC(2);
                    LabPCList_InitPopupMenu(&arg0->subPopup2, D_8910A8E8, (s8*)&arg0->popupItemFlags[2], 8, 0);
                    Window_SetRect((s8*)&arg0->subPopup2.anchorX, arg0->subPopup.window.frame.x + 0xE, arg0->subPopup.window.frame.y + 0x1C, 0xE4, 0x1C);
                    arg0->subPopup2.window.frame.style |= 0x01000000;
                    arg0->subPopup2.limitX = arg0->listFrame.x + arg0->listFrame.width;
                    arg0->subPopup2.limitY = arg0->listFrame.y + arg0->listFrame.height;
                    LabPCList_PlacePopup(&arg0->subPopup2);
                    arg0->subPopup2.window.frame.color = D_8910A7F4;
                    func_89103144((s8*)&arg0->subPopup2.menu, ((List89103C54*)arg0->list.items)->items[arg0->list.cursor], arg0->sourceMatrix.rows + 0x24);
                    arg0->state = 9;
                    break;
                case 2:
                    func_8003F6AC(2);
                    LabPCList_InitPopupMenu(&arg0->subPopup2, D_8910A8E8, (s8*)&arg0->popupItemFlags[2], 4, 0);
                    Window_SetRect((s8*)&arg0->subPopup2.anchorX, arg0->subPopup.window.frame.x + 0xE, arg0->subPopup.window.frame.y + 0x38, 0xE4, 0x1C);
                    arg0->subPopup2.window.frame.style |= 0x01000000;
                    arg0->subPopup2.limitX = arg0->listFrame.x + arg0->listFrame.width;
                    arg0->subPopup2.limitY = arg0->listFrame.y + arg0->listFrame.height;
                    LabPCList_PlacePopup(&arg0->subPopup2);
                    arg0->subPopup2.window.frame.color = D_8910A7F4;
                    func_89103144((s8*)&arg0->subPopup2.menu, ((List89103C54*)arg0->list.items)->items[arg0->list.cursor], arg0->sourceMatrix.rows + 0x48);
                    arg0->state = 0xA;
                    break;
            }
        } else {
            func_8003F6AC(8);
        }
    }
    return ret;
}


/**
 * Moves the Pokemon to the chosen Game Boy box.
 * Seen in play (2026-11-12) in いちらん: いどうする > ゲームボーイのボックス showed ボックス1-8; ボックス1 moved フシギダネ out of
 * the party (「いどう てもち -> GB 1」).
 */
s32 LabPCList_UpdateGbBoxMenu(LabPCListScreen* arg0) {
    s32 ret = 0;
    s32 cursor;
    s32 top;

    LabPCList_UpdatePopupMenu(&arg0->subPopup2);
    if (*(u16*)(D_800603C0 + 8) & 0x4000) {
        func_8003F6AC(3);
        arg0->state = 8;
    } else if (*(u16*)(D_800603C0 + 8) & 0x8000) {
        if (!(arg0->subPopup2.menu.itemFlags[arg0->subPopup2.menu.cursor] & 1)) {
            cursor = arg0->list.cursor;
            top = arg0->list.cursor - arg0->list.scrollY / arg0->list.cellHeight;
            func_8003F6AC(0x18);
            LabPCList_MoveMonTo((LabPCListScreen*)arg0, ((List89103C54*)arg0->list.items)->items[arg0->list.cursor], 1, arg0->subPopup2.menu.cursor, arg0->msg);
            func_89109C6C((s8*)&arg0->rows, (s8*)&arg0->sourceMatrix);
            LabPCList_ApplyFiltersAndSort(arg0);
            func_800307D4(&arg0->list.items, cursor, top);
            arg0->state = 0;
            ret = 3;
        } else {
            func_8003F6AC(8);
        }
    }
    return ret;
}

/**
 * Moves the Pokemon to the chosen Stadium (64 cartridge) box.
 * Seen in play (2026-11-12) in いちらん: いどうする > 64カセットのボックス showed ボックス1-4; ボックス1 moved フシギダネ out of
 * the party (「いどう てもち -> 64 1」).
 */
s32 LabPCList_UpdateStadiumBoxMenu(LabPCListScreen* arg0) {
    s32 ret = 0;
    s32 cursor;
    s32 top;

    LabPCList_UpdatePopupMenu(&arg0->subPopup2);
    if (*(u16*)(D_800603C0 + 8) & 0x4000) {
        func_8003F6AC(3);
        arg0->state = 8;
    } else if (*(u16*)(D_800603C0 + 8) & 0x8000) {
        if (!(arg0->subPopup2.menu.itemFlags[arg0->subPopup2.menu.cursor] & 1)) {
            cursor = arg0->list.cursor;
            top = arg0->list.cursor - arg0->list.scrollY / arg0->list.cellHeight;
            func_8003F6AC(0x18);
            LabPCList_MoveMonTo((LabPCListScreen*)arg0, ((List89103C54*)arg0->list.items)->items[arg0->list.cursor], 2, arg0->subPopup2.menu.cursor, arg0->msg);
            func_89109C6C((s8*)&arg0->rows, (s8*)&arg0->sourceMatrix);
            LabPCList_ApplyFiltersAndSort(arg0);
            func_800307D4(&arg0->list.items, cursor, top);
            arg0->state = 0;
            ret = 3;
        } else {
            func_8003F6AC(8);
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
void func_8910A764();
/**
 * Uses a vitamin (HP Up, Protein, Iron, Carbos, Calcium; 0x23-0x27) or a Rare Candy (0x28) on the
 * Pokemon and fills in the old and new values for the result message.
 * Seen in play (2026-11-12) in いちらん: マックスアップ (HP Up) on フシギダネ showed HP 19 -> 20, and
 * ふしぎなアメ showed レベル 5 -> 6 with the stats recomputed. After レポートしてやめる the Game Boy save
 * had HP stat exp +0xA00, max HP 20 and one HP Up fewer.
 */
void LabPCList_ApplyVitaminItem(u8** arg0, u8** arg1, Msg89103F04* arg2) {
    BattleMon* mon;
    u16 old_max_hp;

    arg2->unk04 = 0;
    mon = (BattleMon*)((u8*)arg0 + 8);
    switch (**arg1) {
        case 0x23:
            arg2->text = D_8910DDFC;
            arg2->oldValue = mon->maxHp;
            mon->statExp[0] += 0xA00;
            if (mon->statExp[0] > 0x6400) {
                mon->statExp[0] = 0x6400;
            }
            mon->maxHp = func_80020234(1, mon->species.id, mon->statExp[0], mon->level, mon->dvs);
            arg2->newValue = mon->maxHp;
            break;
        case 0x24:
            arg2->text = D_8910DE04;
            arg2->oldValue = mon->attack;
            mon->statExp[1] += 0xA00;
            if (mon->statExp[1] > 0x6400) {
                mon->statExp[1] = 0x6400;
            }
            mon->attack = func_80020234(2, mon->species.id, mon->statExp[1], mon->level, mon->dvs);
            arg2->newValue = mon->attack;
            break;
        case 0x25:
            arg2->text = D_8910DE10;
            arg2->oldValue = mon->defense;
            mon->statExp[2] += 0xA00;
            if (mon->statExp[2] > 0x6400) {
                mon->statExp[2] = 0x6400;
            }
            mon->defense = func_80020234(3, mon->species.id, mon->statExp[2], mon->level, mon->dvs);
            arg2->newValue = mon->defense;
            break;
        case 0x26:
            arg2->text = D_8910DE1C;
            arg2->oldValue = mon->speed;
            mon->statExp[3] += 0xA00;
            if (mon->statExp[3] > 0x6400) {
                mon->statExp[3] = 0x6400;
            }
            mon->speed = func_80020234(4, mon->species.id, mon->statExp[3], mon->level, mon->dvs);
            arg2->newValue = mon->speed;
            break;
        case 0x27:
            arg2->text = D_8910DE28;
            arg2->oldValue = mon->special;
            mon->statExp[4] += 0xA00;
            if (mon->statExp[4] > 0x6400) {
                mon->statExp[4] = 0x6400;
            }
            mon->special = func_80020234(5, mon->species.id, mon->statExp[4], mon->level, mon->dvs);
            arg2->newValue = mon->special;
            break;
        case 0x28:
            arg2->text = D_8910DE34;
            arg2->oldValue = mon->level;
            old_max_hp = mon->maxHp;
            mon->exp = func_8002057C(mon->species.id, mon->level + 1);
            func_800203FC(mon);
            mon->hp += mon->maxHp - old_max_hp;
            arg2->newValue = mon->level;
            break;
    }
    func_8910A764(arg1);
    *(s32*)(arg0[0] + 0x10) = 1;
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
void func_8910A764(s32, u8*, s32, Msg891041D8*);

/**
 * Uses a PP Up on move `arg2` of the Pokemon and writes the result message.
 * Seen in play (2026-11-12) in いちらん: ポイントアップ on フシギダネ, move slot 0, showed 「たいあたりのPP」 35 -> 42.
 */
void LabPCList_ApplyPpUpItem(u8** arg0, s32 arg1, s32 arg2, Msg891041D8* arg3) {
    u8* ptr;
    s32 base_pp;
    s32 step;
    s8* end;

    func_8000A460(D_8910E3B8, D_8006A9CC[*(u8*)((u32)arg0 + arg2 + 0x11)].name); // FAKE: integer cast keeps arg0 + arg2 from being reused
    ptr = (u8*)arg0 + arg2 + 8;
    end = D_8910E3B8 + func_800566BC(D_8910E3B8);
    *(Str891041D8*)end = *(Str891041D8*)D_8910DE3C;
    if (1) {} // karodo
    arg3->text = D_8910E3B8;
    arg3->unk04 = 0;
    base_pp = gMoveData[ptr[9] - 1].pp;
    step = base_pp / 5;
    if (step >= 7) {
        step = 7;
    }
    arg3->oldPp = (ptr[0x20] >> 6) * step + base_pp;
    arg3->newPp = arg3->oldPp + step;
    ptr[0x20] += step + 0x40;
    func_8910A764(arg1, ptr, base_pp, arg3);
    *(s32*)(arg0[0] + 0x10) = 1;
}

u8 Move_GetIdFromTableIndex(s32 arg0);
void LabPCList_ConsumeUsedTmItem(u8** arg0);

/**
 * Teaches the TM or HM move `arg1` in move slot `arg2` (item ids from 0xC9 are TMs, below are HMs).
 * Seen in play (2026-11-12) in いちらん: わざマシン06 on フシギダネ ran this with slot 2, and どくどく (Toxic) then
 * appeared as わざ3.
 */
void LabPCList_TeachTmHmMove(u8** arg0, u8** arg1, s32 arg2) {
    u8* ptr;
    s32 var_a0;

    if (*arg1[0] >= 0xC9) {
        var_a0 = *arg1[0] - 0xC9;
    } else {
        var_a0 = *arg1[0] - 0x92;
    }

    ptr = (u8*)arg0 + arg2 + 8;
    ptr[9] = Move_GetIdFromTableIndex(var_a0);
    ptr[0x20] = gMoveData[ptr[9] - 1].pp;

    if (*arg1[0] >= 0xC9) {
        LabPCList_ConsumeUsedTmItem(arg1);
    }
    *(s32*)(arg0[0] + 0x10) = 1;
}

s32 LabPCList_UpdateBrowse();
s32 LabPCList_UpdateSortMenu(LabPCListScreen*);
s32 func_89102C40(LabPCListScreen*);
s32 LabPCList_RunLevelFilter(s8*);
s32 LabPCList_UpdateMonMenu(LabPCListScreen*);
s32 LabPCList_UpdateGbBoxMenu();
s32 LabPCList_UpdateStadiumBoxMenu();
s32 Ui_CheckConfirmPressed(void*);
/**
 * Runs the list window's state machine (browse, sort menu, filters, moves).
 * Seen in play (2026-11-12): ran the list window.
 */
s32 LabPCList_UpdateList(LabPCListScreen* arg0) {
    s32 ret = 0;

    if (arg0->window.state == 0) {
        return 0;
    }
    switch (arg0->state) {
        case 0:
            ret = LabPCList_UpdateBrowse(arg0);
            break;
        case 1:
            ret = LabPCList_UpdateSourceSelect(arg0);
            break;
        case 2:
            ret = LabPCList_UpdateSortMenu(arg0);
            break;
        case 3:
            ret = func_89102C40(arg0);
            break;
        case 4:
            ret = LabPCList_RunLevelFilter(arg0);
            break;
        case 5:
            ret = LabPCList_RunTypeFilter(arg0);
            break;
        case 6:
            ret = LabPCList_RunMoveFilter(arg0);
            break;
        case 7:
            ret = LabPCList_UpdateMonMenu(arg0);
            break;
        case 8:
            ret = LabPCList_UpdateDestinationMenu(arg0);
            break;
        case 9:
            ret = LabPCList_UpdateGbBoxMenu(arg0);
            break;
        case 10:
            ret = LabPCList_UpdateStadiumBoxMenu(arg0);
            break;
        case 11:
        case 12:
            if (Ui_CheckConfirmPressed((s8*)arg0->textBox) == 1) {
                arg0->state = 0;
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
void LabPCList_InitScreen(LabPCList* arg0) {
    arg0->state = 0;
    LabPCList_InitListWindow(&arg0->listScreen, 0x26, 0x48, (s32)&arg0->message);
}

void SavePrompt_Init(SavePrompt*, s32, s32);
void Save_DrawReportingWindow(SavePrompt*);
s32 SavePrompt_Update(SavePrompt*);
void LabPCList_SaveChanges(LabPCListScreen*);
void LabPCList_InitItemWindow(LabItemWindow*, s32, s32, s8*, s8*, s32);
s32 LabPCList_UpdateItemWindow(LabItemWindow*);
void LabPCList_InitMessageWindow(LabMessageWindow*, s32, s32, LabItemResult*);
s32 LabPCList_UpdateMessageWindow(LabMessageWindow*);
void func_8910A4C8(s8*, s32);
/**
 * Per-frame update of the いちらん screen: runs the list, the save prompt, the item window or the
 * message window by state. Returns 1 when the caller should leave this screen.
 * Seen in play (2026-11-12): ran the いちらん screen.
 */
s32 LabPCList_UpdateScreen(LabPCList* arg0) {
    s32 ret = 0;
    s32 r;
    s8* sub;

    switch (arg0->state) {
        case 0:
            sub = (s8*)&arg0->listScreen;
            r = LabPCList_UpdateList(sub);
            if (r == 1) {
                if (arg0->listScreen.hasChanges != 0) {
                    SavePrompt_Init(&arg0->savePrompt, 0xCA, 0xAD);
                    arg0->state = 1;
                } else {
                    ret = 1;
                }
            } else if (r == 2) {
                func_8910A4C8((s8*)&arg0->listScreen + 0xAFFC, ((s32*)arg0->listScreen.list.items->rows)[arg0->listScreen.list.cursor] + 8);
                LabPCList_InitItemWindow(&arg0->itemWindow, ((LabPCListScreen*)sub)->window.frame.x + 0xAB, ((LabPCListScreen*)sub)->window.frame.y + 0xD, sub + 0xAFFC,
                              sub + 0xB008, ((s32**)((LabPCListScreen*)sub)->list.items->rows)[((LabPCListScreen*)sub)->list.cursor]);
                arg0->state = 2;
            } else if (r == 3) {
                LabPCList_InitMessageWindow(&arg0->messageWindow, 0xB6, 0xEA, &arg0->message);
                arg0->state = 3;
            }
            break;
        case 1:
            sub = (s8*)&arg0->savePrompt;
            r = SavePrompt_Update((SavePrompt*)sub);
            if (r == -1) {
                arg0->state = 0;
            } else if (r > 0) {
                switch (r) {
                    case 1:
                        Save_DrawReportingWindow((SavePrompt*)sub);
                        LabPCList_SaveChanges(&arg0->listScreen);
                        ret = 1;
                        break;
                    case 2:
                        ret = 1;
                        break;
                }
            }
            break;
        case 2:
            r = LabPCList_UpdateItemWindow(&arg0->itemWindow);
            if (r == -1) {
                arg0->state = 0;
            } else {
                s32 off = 0xB55C; // FAKE: stops IDO reusing arg0 + 0x8000 for the store below.

                if (r > 0) {
                    s32 a1 = ((s32*)arg0->itemWindow.list.items->rows)[arg0->itemWindow.list.cursor];
                    s32 a0 = ((s32*)arg0->listScreen.list.items->rows)[arg0->listScreen.list.cursor];

                    switch (r) {
                        case 1:
                            LabPCList_ApplyVitaminItem((u8**)a0, (u8**)a1, (Msg89103F04*)&arg0->message);
                            break;
                        case 2:
                            LabPCList_ApplyPpUpItem((u8**)a0, a1, arg0->itemWindow.moveSelect.menu.cursor, (Msg891041D8*)&arg0->message);
                            break;
                        case 3:
                            LabPCList_TeachTmHmMove((u8**)a0, (u8**)a1, arg0->itemWindow.moveSelect.menu.cursor);
                            break;
                    }
                    *(s32*)((s8*)arg0 + off) = 1;
                    if (r == 3) {
                        arg0->state = 0;
                    } else {
                        LabPCList_InitMessageWindow(&arg0->messageWindow, 0xB6, 0xEA, &arg0->message);
                        arg0->state = 3;
                    }
                }
            }
            break;
        case 3:
            if (LabPCList_UpdateMessageWindow(&arg0->messageWindow) == 1) {
                arg0->state = 0;
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
s32 Particle_Field7C_SetXZFromField74AngleY_0B278(void *arg0);
void SavePrompt_Draw(SavePrompt*);
void PcSort_DrawUseItemPrompt(LabItemWindow*);
void LabPCList_DrawMessageWindow(LabMessageWindow*);

/**
 * Draws the lab PC list for its current state.
 * Seen in play (2026-11-12): drew the いちらん screen.
 */
M2C_UNK LabPCList_DrawScreen(LabPCList* arg0) {
    BgStage_DrawFrame();
    switch (arg0->state) {
        case 0:
            if (Particle_Field7C_SetXZFromField74AngleY_0B278(&arg0->listScreen) != 0) {
                LabPCList_DrawBackground();
            }
            LabPCList_DrawListScreen(&arg0->listScreen);
            break;
        case 1:
            if (Particle_Field7C_SetXZFromField74AngleY_0B278(&arg0->listScreen) != 0) {
                LabPCList_DrawBackground();
            }
            LabPCList_DrawListScreen(&arg0->listScreen);
            SavePrompt_Draw(&arg0->savePrompt);
            break;
        case 2:
            if (Particle_Field7C_SetXZFromField74AngleY_0B278(&arg0->listScreen) != 0) {
                LabPCList_DrawBackground();
            }
            if (Particle_Field7C_SetXZFromField74AngleY_0B278(&arg0->itemWindow) != 0) {
                LabPCList_DrawListScreen(&arg0->listScreen);
            }
            PcSort_DrawUseItemPrompt(&arg0->itemWindow);
            break;
        case 3:
            if (Particle_Field7C_SetXZFromField74AngleY_0B278(&arg0->listScreen) != 0) {
                LabPCList_DrawBackground();
            }
            LabPCList_DrawListScreen(&arg0->listScreen);
            LabPCList_DrawMessageWindow(&arg0->messageWindow);
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
 * (also func_8200579C, func_8900429C, LabPCList_UpdateFade, func_8A101B30) does not
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
s32 LabPCList_UpdateFade(s32 arg0) {
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
void LabPCList_RunFrame(s32 arg0) {
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
 * entry function Pokedex_Init), differing only in the functions it calls in
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
 *      with LabPCList_RunFrame.  What those callbacks do is not established
 *      (LabPCList_UpdateFade is still assembly).
 *   6. StageLoader_WaitForRetrace() and main_pool_pop_state('TERM').
 *   7. Fragment_QueueCall queues a call to the fragment whose id comes from
 *      the address D_88000000 (bits 20-27, minus 0x10), with the ROM range
 *      D_00235D70..D_00238BD0.
 *
 * Returns 0x8040.
 * Seen in play (2026-11-12) in いちらん (party list: フシギダネ, ヒトカゲ, ゼニガメ): ran when いちらん was entered
 * from the main menu, before LabPCList_InitScreen.
 */
s32 LabPCList_Init(s32 arg0, s32 arg1) {
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
