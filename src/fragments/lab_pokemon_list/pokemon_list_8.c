/* Fixed-layout split; original translation-unit boundaries remain unconfirmed. */
#include "global.h"
#include "game_state.h"
#include "jpeg_stream.h"
#include "memory.h"
#include "stage_loader.h"
#include "m2c_macros.h"

typedef struct Rgba891024A4 { u8 r, g, b, a; } Rgba891024A4;
typedef struct Color82000BC4 {
    u8 r, g, b, a;
} Color82000BC4;
typedef struct Entry80066AD8 {
    const char* str;
    Color82000BC4 color;
} Entry80066AD8;
typedef struct Entry89100FC4 {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 type;
    /* 0x04 */ const char* name;
    /* 0x08 */ s32 unk_08;
} Entry89100FC4; // size = 0xC
typedef struct Label89100FC4 {
    Color82000BC4 color;
    const char* str;
} Label89100FC4;
#include "fragments/lab_pokemon_list/89100020_89102C40_types.h"

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
void func_89105C54(s8*, s32, s32, s8*, Rgba891024A4);
extern s32 D_8910D990[];
extern Rgba891024A4 D_8910A7F4;
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
void LabPCList_InitPopupMenu(s8*, void*, s8*, s32, s32);
void LabPCList_PlacePopup(s8*);
void func_8910A21C(s8*, s8*, s8*, s32);
extern s8* D_8910A890[];
extern u8 D_8910A898[];
extern u8 D_8910DC50[];
extern s8 D_8910E2D0[];
extern s8 D_8910E312[];
s32 func_8003F6AC();
s32 ScrollList_UpdateCursor(void*);
void ScrollList_SetCursor(void*, s32);
void LabPCList_FormatGatherPrompt(s8*);
void func_8000A460(s8 *, s8 *);
u32 func_800566BC(s8*);
void LabPCList_InitPopupMenu(s8 *, void *, s8 *, s32, s32);
void LabPCList_PlacePopup(s8 *);
void Window_SetRect(s8 *, s32, s32, s32, s32);
extern Rgba891024A4 D_8910A7F4;
extern s8 *D_8910A8A8[];
extern s8 D_8910A8B0[];
extern u8 D_8910A8C8[];
extern s8 D_8910E358[];
s32 LabPCList_UpdateHeaderCursor(void*);
M2C_UNK LabPCList_ApplyFiltersAndSort();
extern s32 D_8910E37C;
s32 LabPCList_UpdatePopupMenu(s8*);
void func_80027D68(s32, s32);
void func_89105C54(s8*, s32, s32, s8*, Rgba891024A4);
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
typedef struct Ctx89103740 { char unk0000[0xB558]; s32 unkB558; } Ctx89103740;
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
void LabPCList_MoveMonTo(Ctx89103740* arg0, Ref89103740* arg1, s32 arg2, s32 arg3, Msg89103740* arg4) {
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
    arg0->unkB558 = 1;
}

typedef struct List89103C54 {
    /* 0x00 */ Ref89103740** items;
} List89103C54;
void func_800307D4(List89103C54**, s32, s32);
void func_89109C6C(s8*, s8*);

typedef struct Ctx89103858 {
    /* 0x0000 */ char unk0000[0x2C];
    /* 0x002C */ s32 unk2C;
    /* 0x0030 */ s32 unk30;
    /* 0x0034 */ s32 unk34;
    /* 0x0038 */ s32 unk38;
    /* 0x003C */ char unk003C[0x88 - 0x3C];
    /* 0x0088 */ s32 unk88;
    /* 0x008C */ char unk008C[0x420 - 0x8C];
    /* 0x0420 */ s32 unk420;
    /* 0x0424 */ char unk0424[0x9648 - 0x424];
    /* 0x9648 */ s8 unk9648[0x96D0 - 0x9648];
    /* 0x96D0 */ s32 x;
    /* 0x96D4 */ s32 y;
    /* 0x96D8 */ char unk96D8[0x9714 - 0x96D8];
    /* 0x9714 */ u16* flags;
    /* 0x9718 */ s32 index;
    /* 0x971C */ char unk971C[0x974C - 0x971C];
    /* 0x974C */ s8 unk974C[0x14];
    /* 0x9760 */ s32 unk9760;
    /* 0x9764 */ Rgba891024A4 unk9764;
    /* 0x9768 */ char unk9768[0x9778 - 0x9768];
    /* 0x9778 */ s8 unk9778[0x14];
    /* 0x978C */ s8 unk978C[0x34];
    /* 0x97C0 */ s32 unk97C0;
    /* 0x97C4 */ s32 unk97C4;
    /* 0x97C8 */ char unk97C8[0x9808 - 0x97C8];
    /* 0x9808 */ s8 unk9808[0xB160 - 0x9808];
    /* 0xB160 */ List89103C54* list;
    /* 0xB164 */ char unkB164[4];
    /* 0xB168 */ s32 cursor;
    /* 0xB16C */ char unkB16C[4];
    /* 0xB170 */ s32 unkB170;
    /* 0xB174 */ char unkB174[0xB18C - 0xB174];
    /* 0xB18C */ s32 unkB18C;
    /* 0xB190 */ char unkB190[0xB594 - 0xB190];
    /* 0xB594 */ Msg89103740* msg;
} Ctx89103858;

extern u8 D_8910A8E8[];
void func_89103144(s8*, Ref89103740*, s32);
/**
 * Handles the どこへ？ (where to?) menu: party, GB box, Stadium box, or a box list.
 * Seen in play (2026-11-12) in いちらん (party list: フシギダネ, ヒトカゲ, ゼニガメ): いどうする opened 「どこへ？」 with
 * てもちのポケモン, ゲームボーイのボックス and 64カセットのボックス while this ran.
 */
s32 LabPCList_UpdateDestinationMenu(Ctx89103858* arg0) {
    s32 ret = 0;
    s32 cursor;
    s32 top;

    LabPCList_UpdatePopupMenu((s8*)&arg0->x);
    if (*(u16*)(D_800603C0 + 8) & 0x4000) {
        func_8003F6AC(3);
        arg0->unk88 = 7;
    } else if (*(u16*)(D_800603C0 + 8) & 0x8000) {
        if (!(arg0->flags[arg0->index] & 1)) {
            switch (arg0->index) {
                case 0:
                    func_8003F6AC(0x18);
                    cursor = arg0->cursor;
                    top = arg0->cursor - arg0->unkB18C / arg0->unkB170;
                    LabPCList_MoveMonTo((Ctx89103740*)arg0, arg0->list->items[arg0->cursor], 0, 0, arg0->msg);
                    func_89109C6C(arg0->unk9648, (s8*)&arg0->unk420);
                    LabPCList_ApplyFiltersAndSort(arg0);
                    func_800307D4(&arg0->list, cursor, top);
                    arg0->unk88 = 0;
                    ret = 3;
                    break;
                case 3:
                    func_8003F6AC(0x18);
                    cursor = arg0->cursor;
                    top = arg0->cursor - arg0->unkB18C / arg0->unkB170;
                    LabPCList_MoveMonTo((Ctx89103740*)arg0, arg0->list->items[arg0->cursor], 3, 0, arg0->msg);
                    func_89109C6C(arg0->unk9648, (s8*)&arg0->unk420);
                    LabPCList_ApplyFiltersAndSort(arg0);
                    func_800307D4(&arg0->list, cursor, top);
                    arg0->unk88 = 0;
                    ret = 3;
                    break;
                case 1:
                    func_8003F6AC(2);
                    LabPCList_InitPopupMenu(arg0->unk974C, D_8910A8E8, arg0->unk9808, 8, 0);
                    Window_SetRect(arg0->unk9778, arg0->x + 0xE, arg0->y + 0x1C, 0xE4, 0x1C);
                    arg0->unk9760 |= 0x01000000;
                    arg0->unk97C0 = arg0->unk2C + arg0->unk34;
                    arg0->unk97C4 = arg0->unk30 + arg0->unk38;
                    LabPCList_PlacePopup(arg0->unk974C);
                    arg0->unk9764 = D_8910A7F4;
                    func_89103144(arg0->unk978C, arg0->list->items[arg0->cursor], arg0->unk420 + 0x24);
                    arg0->unk88 = 9;
                    break;
                case 2:
                    func_8003F6AC(2);
                    LabPCList_InitPopupMenu(arg0->unk974C, D_8910A8E8, arg0->unk9808, 4, 0);
                    Window_SetRect(arg0->unk9778, arg0->x + 0xE, arg0->y + 0x38, 0xE4, 0x1C);
                    arg0->unk9760 |= 0x01000000;
                    arg0->unk97C0 = arg0->unk2C + arg0->unk34;
                    arg0->unk97C4 = arg0->unk30 + arg0->unk38;
                    LabPCList_PlacePopup(arg0->unk974C);
                    arg0->unk9764 = D_8910A7F4;
                    func_89103144(arg0->unk978C, arg0->list->items[arg0->cursor], arg0->unk420 + 0x48);
                    arg0->unk88 = 0xA;
                    break;
            }
        } else {
            func_8003F6AC(8);
        }
    }
    return ret;
}

typedef struct Ctx89103C54 {
    /* 0x0000 */ char unk0000[0x88];
    /* 0x0088 */ s32 unk88;
    /* 0x008C */ char unk008C[0x420 - 0x8C];
    /* 0x0420 */ s8 unk0420[0x9648 - 0x420];
    /* 0x9648 */ s8 unk9648[0x974C - 0x9648];
    /* 0x974C */ s8 unk974C[0x9790 - 0x974C];
    /* 0x9790 */ u16* flags;
    /* 0x9794 */ s32 index;
    /* 0x9798 */ char unk9798[0xB160 - 0x9798];
    /* 0xB160 */ List89103C54* list;
    /* 0xB164 */ char unkB164[4];
    /* 0xB168 */ s32 cursor;
    /* 0xB16C */ char unkB16C[4];
    /* 0xB170 */ s32 unkB170;
    /* 0xB174 */ char unkB174[0xB18C - 0xB174];
    /* 0xB18C */ s32 unkB18C;
    /* 0xB190 */ char unkB190[0xB594 - 0xB190];
    /* 0xB594 */ Msg89103740* msg;
} Ctx89103C54;

/**
 * Moves the Pokemon to the chosen Game Boy box.
 * Seen in play (2026-11-12) in いちらん: いどうする > ゲームボーイのボックス showed ボックス1-8; ボックス1 moved フシギダネ out of
 * the party (「いどう てもち -> GB 1」).
 */
s32 LabPCList_UpdateGbBoxMenu(Ctx89103C54* arg0) {
    s32 ret = 0;
    s32 cursor;
    s32 top;

    LabPCList_UpdatePopupMenu(arg0->unk974C);
    if (*(u16*)(D_800603C0 + 8) & 0x4000) {
        func_8003F6AC(3);
        arg0->unk88 = 8;
    } else if (*(u16*)(D_800603C0 + 8) & 0x8000) {
        if (!(arg0->flags[arg0->index] & 1)) {
            cursor = arg0->cursor;
            top = arg0->cursor - arg0->unkB18C / arg0->unkB170;
            func_8003F6AC(0x18);
            LabPCList_MoveMonTo((Ctx89103740*)arg0, arg0->list->items[arg0->cursor], 1, arg0->index, arg0->msg);
            func_89109C6C(arg0->unk9648, arg0->unk0420);
            LabPCList_ApplyFiltersAndSort(arg0);
            func_800307D4(&arg0->list, cursor, top);
            arg0->unk88 = 0;
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
s32 LabPCList_UpdateStadiumBoxMenu(Ctx89103C54* arg0) {
    s32 ret = 0;
    s32 cursor;
    s32 top;

    LabPCList_UpdatePopupMenu(arg0->unk974C);
    if (*(u16*)(D_800603C0 + 8) & 0x4000) {
        func_8003F6AC(3);
        arg0->unk88 = 8;
    } else if (*(u16*)(D_800603C0 + 8) & 0x8000) {
        if (!(arg0->flags[arg0->index] & 1)) {
            cursor = arg0->cursor;
            top = arg0->cursor - arg0->unkB18C / arg0->unkB170;
            func_8003F6AC(0x18);
            LabPCList_MoveMonTo((Ctx89103740*)arg0, arg0->list->items[arg0->cursor], 2, arg0->index, arg0->msg);
            func_89109C6C(arg0->unk9648, arg0->unk0420);
            LabPCList_ApplyFiltersAndSort(arg0);
            func_800307D4(&arg0->list, cursor, top);
            arg0->unk88 = 0;
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
            mon->unk_14 += 0xA00;
            if (mon->unk_14 > 0x6400) {
                mon->unk_14 = 0x6400;
            }
            mon->maxHp = func_80020234(1, mon->species.id, mon->unk_14, mon->level, mon->unk_1E);
            arg2->newValue = mon->maxHp;
            break;
        case 0x24:
            arg2->text = D_8910DE04;
            arg2->oldValue = mon->attack;
            mon->unk_16 += 0xA00;
            if (mon->unk_16 > 0x6400) {
                mon->unk_16 = 0x6400;
            }
            mon->attack = func_80020234(2, mon->species.id, mon->unk_16, mon->level, mon->unk_1E);
            arg2->newValue = mon->attack;
            break;
        case 0x25:
            arg2->text = D_8910DE10;
            arg2->oldValue = mon->defense;
            mon->unk_18 += 0xA00;
            if (mon->unk_18 > 0x6400) {
                mon->unk_18 = 0x6400;
            }
            mon->defense = func_80020234(3, mon->species.id, mon->unk_18, mon->level, mon->unk_1E);
            arg2->newValue = mon->defense;
            break;
        case 0x26:
            arg2->text = D_8910DE1C;
            arg2->oldValue = mon->speed;
            mon->unk_1A += 0xA00;
            if (mon->unk_1A > 0x6400) {
                mon->unk_1A = 0x6400;
            }
            mon->speed = func_80020234(4, mon->species.id, mon->unk_1A, mon->level, mon->unk_1E);
            arg2->newValue = mon->speed;
            break;
        case 0x27:
            arg2->text = D_8910DE28;
            arg2->oldValue = mon->special;
            mon->unk_1C += 0xA00;
            if (mon->unk_1C > 0x6400) {
                mon->unk_1C = 0x6400;
            }
            mon->special = func_80020234(5, mon->species.id, mon->unk_1C, mon->level, mon->unk_1E);
            arg2->newValue = mon->special;
            break;
        case 0x28:
            arg2->text = D_8910DE34;
            arg2->oldValue = mon->level;
            old_max_hp = mon->maxHp;
            mon->unk_10 = func_8002057C(mon->species.id, mon->level + 1);
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
s32 LabPCList_UpdateSortMenu(s8*);
s32 func_89102C40(s8*);
s32 LabPCList_RunLevelFilter(s8*);
s32 LabPCList_UpdateMonMenu(s8*);
s32 LabPCList_UpdateGbBoxMenu();
s32 LabPCList_UpdateStadiumBoxMenu();
s32 Ui_CheckConfirmPressed(void*);
/**
 * Runs the list window's state machine (browse, sort menu, filters, moves).
 * Seen in play (2026-11-12): ran the list window.
 */
s32 LabPCList_UpdateList(s8* arg0) {
    s32 ret = 0;

    if (M2C_FIELD(arg0, s32*, 0x28) == 0) {
        return 0;
    }
    switch (M2C_FIELD(arg0, u32*, 0x88)) {
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
            ret = LabPCList_UpdateDestinationMenu((Ctx89103858*)arg0);
            break;
        case 9:
            ret = LabPCList_UpdateGbBoxMenu(arg0);
            break;
        case 10:
            ret = LabPCList_UpdateStadiumBoxMenu(arg0);
            break;
        case 11:
        case 12:
            if (Ui_CheckConfirmPressed(arg0 + 0xB55C) == 1) {
                M2C_FIELD(arg0, u32*, 0x88) = 0;
            }
            break;
    }
    return ret;
}

/**
 * Clears the first word of arg0 and initializes the sub-objects at offsets 4
 * and 0xB7E4 with LabPCList_InitListWindow(arg0 + 4, 0x26, 0x48, arg0 + 0xB7E4). What the
 * object is is not established.
 * Seen in play (2026-11-12) in いちらん (party list: フシギダネ, ヒトカゲ, ゼニガメ): ran on entry, right before
 * LabPCList_InitListWindow.
 */
void LabPCList_InitScreen(void* arg0) {
    M2C_FIELD(arg0, s32*, 0) = 0;
    LabPCList_InitListWindow((s8*)arg0 + 4, 0x26, 0x48, (s8*)arg0 + 0xB7E4);
}

void SavePrompt_Init(s8*, s32, s32);
void Save_DrawReportingWindow(s8*);
s32 SavePrompt_Update(s8*);
void LabPCList_SaveChanges(s8*);
void LabPCList_InitItemWindow(s8*, s32, s32, s8*, s8*, s32);
s32 LabPCList_UpdateItemWindow(s8*);
void LabPCList_InitMessageWindow(s8*, s32, s32, s8*);
s32 LabPCList_UpdateMessageWindow(s8*);
void func_8910A4C8(s8*, s32);
/**
 * Per-frame update for a four-state object at arg0 (state word at offset 0).
 * Returns 1 when the caller should leave this screen. The sub-objects at
 * 4, 0xB59C, 0xB600 and 0xB7B4 are driven by the LabPCList_UpdateList,
 * SavePrompt_Update, LabPCList_UpdateItemWindow and LabPCList_UpdateMessageWindow updates.
 * Seen in play (2026-11-12): ran the いちらん screen.
 */
s32 LabPCList_UpdateScreen(s8* arg0) {
    s32 ret = 0;
    s32 r;
    s8* sub;

    switch (M2C_FIELD(arg0, s32*, 0)) {
        case 0:
            sub = arg0 + 4;
            r = LabPCList_UpdateList(sub);
            if (r == 1) {
                if (M2C_FIELD(arg0, s32*, 0xB55C) != 0) {
                    SavePrompt_Init(arg0 + 0xB59C, 0xCA, 0xAD);
                    M2C_FIELD(arg0, s32*, 0) = 1;
                } else {
                    ret = 1;
                }
            } else if (r == 2) {
                func_8910A4C8(arg0 + 0xB000, (*M2C_FIELD(arg0, s32***, 0xB164))[M2C_FIELD(arg0, s32*, 0xB16C)] + 8);
                LabPCList_InitItemWindow(arg0 + 0xB600, M2C_FIELD(sub, s32*, 0) + 0xAB, M2C_FIELD(sub, s32*, 4) + 0xD, sub + 0xAFFC,
                              sub + 0xB008, (*M2C_FIELD(sub, s32***, 0xB160))[M2C_FIELD(sub, s32*, 0xB168)]);
                M2C_FIELD(arg0, s32*, 0) = 2;
            } else if (r == 3) {
                LabPCList_InitMessageWindow(arg0 + 0xB7B4, 0xB6, 0xEA, arg0 + 0xB7E4);
                M2C_FIELD(arg0, s32*, 0) = 3;
            }
            break;
        case 1:
            sub = arg0 + 0xB59C;
            r = SavePrompt_Update(sub);
            if (r == -1) {
                M2C_FIELD(arg0, s32*, 0) = 0;
            } else if (r > 0) {
                switch (r) {
                    case 1:
                        Save_DrawReportingWindow(sub);
                        LabPCList_SaveChanges(arg0 + 4);
                        ret = 1;
                        break;
                    case 2:
                        ret = 1;
                        break;
                }
            }
            break;
        case 2:
            r = LabPCList_UpdateItemWindow(arg0 + 0xB600);
            if (r == -1) {
                M2C_FIELD(arg0, s32*, 0) = 0;
            } else {
                s32 off = 0xB55C; // FAKE: stops IDO reusing arg0 + 0x8000 for the store below.

                if (r > 0) {
                    s32 a1 = (*M2C_FIELD(arg0, s32***, 0xB64C))[M2C_FIELD(arg0, s32*, 0xB654)];
                    s32 a0 = (*M2C_FIELD(arg0, s32***, 0xB164))[M2C_FIELD(arg0, s32*, 0xB16C)];

                    switch (r) {
                        case 1:
                            LabPCList_ApplyVitaminItem((u8**)a0, (u8**)a1, (Msg89103F04*)(arg0 + 0xB7E4));
                            break;
                        case 2:
                            LabPCList_ApplyPpUpItem((u8**)a0, a1, M2C_FIELD(arg0, s32*, 0xB744), (Msg891041D8*)(arg0 + 0xB7E4));
                            break;
                        case 3:
                            LabPCList_TeachTmHmMove((u8**)a0, (u8**)a1, M2C_FIELD(arg0, s32*, 0xB744));
                            break;
                    }
                    M2C_FIELD(arg0, s32*, off) = 1;
                    if (r == 3) {
                        M2C_FIELD(arg0, s32*, 0) = 0;
                    } else {
                        LabPCList_InitMessageWindow(arg0 + 0xB7B4, 0xB6, 0xEA, arg0 + 0xB7E4);
                        M2C_FIELD(arg0, s32*, 0) = 3;
                    }
                }
            }
            break;
        case 3:
            if (LabPCList_UpdateMessageWindow(arg0 + 0xB7B4) == 1) {
                M2C_FIELD(arg0, s32*, 0) = 0;
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
void SavePrompt_Draw(void*);
void PcSort_DrawUseItemPrompt(void*);
void LabPCList_DrawMessageWindow(void*);

/**
 * Draws the lab PC list for its current state.
 * Seen in play (2026-11-12): drew the いちらん screen.
 */
M2C_UNK LabPCList_DrawScreen(M2C_UNK* arg0) {
    BgStage_DrawFrame();
    switch (*arg0) {
        case 0:
            if (Particle_Field7C_SetXZFromField74AngleY_0B278(arg0 + 1) != 0) {
                LabPCList_DrawBackground();
            }
            LabPCList_DrawListScreen(arg0 + 1);
            break;
        case 1:
            if (Particle_Field7C_SetXZFromField74AngleY_0B278(arg0 + 1) != 0) {
                LabPCList_DrawBackground();
            }
            LabPCList_DrawListScreen(arg0 + 1);
            SavePrompt_Draw((s8*)arg0 + 0xB59C);
            break;
        case 2:
            if (Particle_Field7C_SetXZFromField74AngleY_0B278(arg0 + 1) != 0) {
                LabPCList_DrawBackground();
            }
            if (Particle_Field7C_SetXZFromField74AngleY_0B278((s8*)arg0 + 0xB600) != 0) {
                LabPCList_DrawListScreen(arg0 + 1);
            }
            PcSort_DrawUseItemPrompt((s8*)arg0 + 0xB600);
            break;
        case 3:
            if (Particle_Field7C_SetXZFromField74AngleY_0B278(arg0 + 1) != 0) {
                LabPCList_DrawBackground();
            }
            LabPCList_DrawListScreen(arg0 + 1);
            LabPCList_DrawMessageWindow((s8*)arg0 + 0xB7B4);
            break;
    }
}

void func_80027FF8(void*, s32);
void LabPCList_InitScreen(void*);
extern M2C_UNK D_8910E380;
extern M2C_UNK D_8910E3D0;

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
s32 LabPCList_UpdateScreen(s8*);
M2C_UNK LabPCList_DrawScreen(M2C_UNK *);                   /* extern */
extern M2C_UNK D_8910E3D0;

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
