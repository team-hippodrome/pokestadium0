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
typedef struct Info891033A0 { u8 unk00[6]; u8 unk06; u8 unk07; u8 unk08[0xF]; } Info891033A0;

extern u8 D_80073520[];
M2C_UNK func_80029A64(s32, s32, s32, s32, Color_RGBA8);
extern s32 D_8910A7F8[3];
void func_80027410(void*, void*, s32, s32, s32);
void func_89109990(void*, void*, void*, s32);
extern s32 D_800603C0;
void func_8000B2F4(s32);
void func_8002A8C4(s8 *, s32, s32, s32, s32);
void func_80027804(s8*, s8*, s32, s32);
void func_89109B60(s8*);
void func_80027D68(s32, s32);
void func_8002EC24(s8*, s8*, s8*, s32, void*, s32, s32);
void func_891012A8();
void func_89105C54(s8*, s32, s32, s8*, Rgba891024A4);
extern s32 D_8910D990[];
extern Rgba891024A4 D_8910A7F4;
extern u8 D_8910A844[];
extern u8 D_8910A848[];
extern u8 D_8910A804[];
extern u8 D_8910A84C[];
s32 func_891005CC();
extern Entry80066AD8 D_80066AD8[];
s32 func_8002D498(u8*, s32);
M2C_UNK func_8001A384(M2C_UNK, M2C_UNK);
M2C_UNK func_8001A944(s32, s32, M2C_UNK *, ...);
M2C_UNK func_8001AA9C(u8, u8, u8, u8);
M2C_UNK func_8001AB6C();
M2C_UNK func_8001ABBC();
extern Entry89100FC4 D_8006A9D4[];
extern M2C_UNK D_800734A8;
extern char D_8910DBAC[];
s32 func_8002D454(s32, s32);
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
void func_8002ED18(s32*, void*, void*);
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
void func_89106424(s8*, void*, s8*, s32, s32);
void func_89106570(s8*);
void func_8910A21C(s8*, s8*, s8*, s32);
extern s8* D_8910A890[];
extern u8 D_8910A898[];
extern u8 D_8910DC50[];
extern s8 D_8910E2D0[];
extern s8 D_8910E312[];
s32 func_8003F6AC();
s32 func_8002FD8C(void*);
void func_800306E0(void*, s32);
void func_891020F8(s8*);
void func_8000A460(s8 *, s8 *);
u32 func_800566BC(s8*);
void func_89106424(s8 *, void *, s8 *, s32, s32);
void func_89106570(s8 *);
void func_8002A8C4(s8 *, s32, s32, s32, s32);
extern Rgba891024A4 D_8910A7F4;
extern s8 *D_8910A8A8[];
extern s8 D_8910A8B0[];
extern u8 D_8910A8C8[];
extern s8 D_8910E358[];
s32 func_891025D8(void*);
M2C_UNK func_89101D94();
extern s32 D_8910E37C;
s32 func_891066C0(s8*);
void func_80027D68(s32, s32);
void func_89105C54(s8*, s32, s32, s8*, Rgba891024A4);
M2C_UNK func_89101D94();
extern s32 D_8910D9D0;
extern s32 D_8910D9D4;
s32 func_89106C98(void*);
M2C_UNK func_89101D94();
s32 func_89107614(s8*);
void func_89107850(s8*, s8*);
s32 func_89107EC4(s8*);
void func_89108108(s8*, s8*);
extern u8 D_8910A8DC[];
extern s32 D_8910DD34[];
void func_8002CEEC(s8* arg0, s32 arg1, s32 arg2, s32 arg3, u32 arg4);
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
void func_89103740(Ctx89103740* arg0, Ref89103740* arg1, s32 arg2, s32 arg3, Msg89103740* arg4) {
    Item89103740* items = M2C_FIELD(arg0, Item89103740**, 0x420);
    Sub89103740* sub = &items[arg2].subs[arg3];
    Sub89103740* old = arg1->sub;
    arg4->unk00 = D_8910DD94;
    arg4->unk04 = 1;
    func_89103620(D_8910E398, arg1->sub->head->unkC, arg1->sub->unk04);
    arg4->unk08 = D_8910E398;
    func_89103620(D_8910E3A8, arg2, arg3);
    arg4->unk0C = D_8910E3A8;
    func_80027868(old->unk14, arg1->unk04);
    func_891035E4((u8*)old);
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
s32 func_89103858(Ctx89103858* arg0) {
    s32 ret = 0;
    s32 cursor;
    s32 top;

    func_891066C0((s8*)&arg0->x);
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
                    func_89103740((Ctx89103740*)arg0, arg0->list->items[arg0->cursor], 0, 0, arg0->msg);
                    func_89109C6C(arg0->unk9648, (s8*)&arg0->unk420);
                    func_89101D94(arg0);
                    func_800307D4(&arg0->list, cursor, top);
                    arg0->unk88 = 0;
                    ret = 3;
                    break;
                case 3:
                    func_8003F6AC(0x18);
                    cursor = arg0->cursor;
                    top = arg0->cursor - arg0->unkB18C / arg0->unkB170;
                    func_89103740((Ctx89103740*)arg0, arg0->list->items[arg0->cursor], 3, 0, arg0->msg);
                    func_89109C6C(arg0->unk9648, (s8*)&arg0->unk420);
                    func_89101D94(arg0);
                    func_800307D4(&arg0->list, cursor, top);
                    arg0->unk88 = 0;
                    ret = 3;
                    break;
                case 1:
                    func_8003F6AC(2);
                    func_89106424(arg0->unk974C, D_8910A8E8, arg0->unk9808, 8, 0);
                    func_8002A8C4(arg0->unk9778, arg0->x + 0xE, arg0->y + 0x1C, 0xE4, 0x1C);
                    arg0->unk9760 |= 0x01000000;
                    arg0->unk97C0 = arg0->unk2C + arg0->unk34;
                    arg0->unk97C4 = arg0->unk30 + arg0->unk38;
                    func_89106570(arg0->unk974C);
                    arg0->unk9764 = D_8910A7F4;
                    func_89103144(arg0->unk978C, arg0->list->items[arg0->cursor], arg0->unk420 + 0x24);
                    arg0->unk88 = 9;
                    break;
                case 2:
                    func_8003F6AC(2);
                    func_89106424(arg0->unk974C, D_8910A8E8, arg0->unk9808, 4, 0);
                    func_8002A8C4(arg0->unk9778, arg0->x + 0xE, arg0->y + 0x38, 0xE4, 0x1C);
                    arg0->unk9760 |= 0x01000000;
                    arg0->unk97C0 = arg0->unk2C + arg0->unk34;
                    arg0->unk97C4 = arg0->unk30 + arg0->unk38;
                    func_89106570(arg0->unk974C);
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

s32 func_89103C54(Ctx89103C54* arg0) {
    s32 ret = 0;
    s32 cursor;
    s32 top;

    func_891066C0(arg0->unk974C);
    if (*(u16*)(D_800603C0 + 8) & 0x4000) {
        func_8003F6AC(3);
        arg0->unk88 = 8;
    } else if (*(u16*)(D_800603C0 + 8) & 0x8000) {
        if (!(arg0->flags[arg0->index] & 1)) {
            cursor = arg0->cursor;
            top = arg0->cursor - arg0->unkB18C / arg0->unkB170;
            func_8003F6AC(0x18);
            func_89103740((Ctx89103740*)arg0, arg0->list->items[arg0->cursor], 1, arg0->index, arg0->msg);
            func_89109C6C(arg0->unk9648, arg0->unk0420);
            func_89101D94(arg0);
            func_800307D4(&arg0->list, cursor, top);
            arg0->unk88 = 0;
            ret = 3;
        } else {
            func_8003F6AC(8);
        }
    }
    return ret;
}

s32 func_89103DAC(Ctx89103C54* arg0) {
    s32 ret = 0;
    s32 cursor;
    s32 top;

    func_891066C0(arg0->unk974C);
    if (*(u16*)(D_800603C0 + 8) & 0x4000) {
        func_8003F6AC(3);
        arg0->unk88 = 8;
    } else if (*(u16*)(D_800603C0 + 8) & 0x8000) {
        if (!(arg0->flags[arg0->index] & 1)) {
            cursor = arg0->cursor;
            top = arg0->cursor - arg0->unkB18C / arg0->unkB170;
            func_8003F6AC(0x18);
            func_89103740((Ctx89103740*)arg0, arg0->list->items[arg0->cursor], 2, arg0->index, arg0->msg);
            func_89109C6C(arg0->unk9648, arg0->unk0420);
            func_89101D94(arg0);
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
 * @unverified Name from Stadium 1, matched by code similarity.
 */
void LabPCList_ApplyVitaminItem(u8** arg0, u8** arg1, Msg89103F04* arg2) {
    BattleMon* mon;
    u16 oldMaxHp;

    arg2->unk04 = 0;
    mon = (BattleMon*)((u8*)arg0 + 8);
    switch (**arg1) {
        case 0x23:
            arg2->text = D_8910DDFC;
            arg2->oldValue = mon->unk_26;
            mon->unk_14 += 0xA00;
            if (mon->unk_14 > 0x6400) {
                mon->unk_14 = 0x6400;
            }
            mon->unk_26 = func_80020234(1, mon->unk_00.unk_00, mon->unk_14, mon->unk_24, mon->unk_1E);
            arg2->newValue = mon->unk_26;
            break;
        case 0x24:
            arg2->text = D_8910DE04;
            arg2->oldValue = mon->unk_28;
            mon->unk_16 += 0xA00;
            if (mon->unk_16 > 0x6400) {
                mon->unk_16 = 0x6400;
            }
            mon->unk_28 = func_80020234(2, mon->unk_00.unk_00, mon->unk_16, mon->unk_24, mon->unk_1E);
            arg2->newValue = mon->unk_28;
            break;
        case 0x25:
            arg2->text = D_8910DE10;
            arg2->oldValue = mon->unk_2A;
            mon->unk_18 += 0xA00;
            if (mon->unk_18 > 0x6400) {
                mon->unk_18 = 0x6400;
            }
            mon->unk_2A = func_80020234(3, mon->unk_00.unk_00, mon->unk_18, mon->unk_24, mon->unk_1E);
            arg2->newValue = mon->unk_2A;
            break;
        case 0x26:
            arg2->text = D_8910DE1C;
            arg2->oldValue = mon->unk_2C;
            mon->unk_1A += 0xA00;
            if (mon->unk_1A > 0x6400) {
                mon->unk_1A = 0x6400;
            }
            mon->unk_2C = func_80020234(4, mon->unk_00.unk_00, mon->unk_1A, mon->unk_24, mon->unk_1E);
            arg2->newValue = mon->unk_2C;
            break;
        case 0x27:
            arg2->text = D_8910DE28;
            arg2->oldValue = mon->unk_2E;
            mon->unk_1C += 0xA00;
            if (mon->unk_1C > 0x6400) {
                mon->unk_1C = 0x6400;
            }
            mon->unk_2E = func_80020234(5, mon->unk_00.unk_00, mon->unk_1C, mon->unk_24, mon->unk_1E);
            arg2->newValue = mon->unk_2E;
            break;
        case 0x28:
            arg2->text = D_8910DE34;
            arg2->oldValue = mon->unk_24;
            oldMaxHp = mon->unk_26;
            mon->unk_10 = func_8002057C(mon->unk_00.unk_00, mon->unk_24 + 1);
            func_800203FC(mon);
            mon->hp += mon->unk_26 - oldMaxHp;
            arg2->newValue = mon->unk_24;
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

void func_891041D8(u8** arg0, s32 arg1, s32 arg2, Msg891041D8* arg3) {
    u8* ptr;
    s32 basePp;
    s32 step;
    s8* end;

    func_8000A460(D_8910E3B8, D_8006A9CC[*(u8*)((u32)arg0 + arg2 + 0x11)].name); // FAKE: integer cast keeps arg0 + arg2 from being reused
    ptr = (u8*)arg0 + arg2 + 8;
    end = D_8910E3B8 + func_800566BC(D_8910E3B8);
    *(Str891041D8*)end = *(Str891041D8*)D_8910DE3C;
    if (1) {} // karodo
    arg3->text = D_8910E3B8;
    arg3->unk04 = 0;
    basePp = gMoveData[ptr[9] - 1].unk_05;
    step = basePp / 5;
    if (step >= 7) {
        step = 7;
    }
    arg3->oldPp = (ptr[0x20] >> 6) * step + basePp;
    arg3->newPp = arg3->oldPp + step;
    ptr[0x20] += step + 0x40;
    func_8910A764(arg1, ptr, basePp, arg3);
    *(s32*)(arg0[0] + 0x10) = 1;
}

u8 Move_GetIdFromTableIndex(s32 arg0);
void LabPCList_ConsumeUsedTmItem(u8** arg0);

void func_89104314(u8** arg0, u8** arg1, s32 arg2) {
    u8* ptr;
    s32 var_a0;

    if (*arg1[0] >= 0xC9) {
        var_a0 = *arg1[0] - 0xC9;
    } else {
        var_a0 = *arg1[0] - 0x92;
    }

    ptr = (u8*)arg0 + arg2 + 8;
    ptr[9] = Move_GetIdFromTableIndex(var_a0);
    ptr[0x20] = gMoveData[ptr[9] - 1].unk_05;

    if (*arg1[0] >= 0xC9) {
        LabPCList_ConsumeUsedTmItem(arg1);
    }
    *(s32*)(arg0[0] + 0x10) = 1;
}

s32 func_89102700();
s32 func_89102AB8(s8*);
s32 func_89102C40(s8*);
s32 func_89102EC8(s8*);
s32 func_891033A0(s8*);
s32 func_89103C54();
s32 func_89103DAC();
s32 func_8002D138(void*);
s32 func_891043BC(s8* arg0) {
    s32 ret = 0;

    if (M2C_FIELD(arg0, s32*, 0x28) == 0) {
        return 0;
    }
    switch (M2C_FIELD(arg0, u32*, 0x88)) {
        case 0:
            ret = func_89102700(arg0);
            break;
        case 1:
            ret = func_891028CC(arg0);
            break;
        case 2:
            ret = func_89102AB8(arg0);
            break;
        case 3:
            ret = func_89102C40(arg0);
            break;
        case 4:
            ret = func_89102EC8(arg0);
            break;
        case 5:
            ret = func_89102FBC(arg0);
            break;
        case 6:
            ret = func_89103080(arg0);
            break;
        case 7:
            ret = func_891033A0(arg0);
            break;
        case 8:
            ret = func_89103858((Ctx89103858*)arg0);
            break;
        case 9:
            ret = func_89103C54(arg0);
            break;
        case 10:
            ret = func_89103DAC(arg0);
            break;
        case 11:
        case 12:
            if (func_8002D138(arg0 + 0xB55C) == 1) {
                M2C_FIELD(arg0, u32*, 0x88) = 0;
            }
            break;
    }
    return ret;
}

/**
 * Clears the first word of arg0 and initialises the sub-objects at offsets 4
 * and 0xB7E4 with func_891003A4(arg0 + 4, 0x26, 0x48, arg0 + 0xB7E4). What the
 * object is is not established.
 */
void func_891044F0(void* arg0) {
    M2C_FIELD(arg0, s32*, 0) = 0;
    func_891003A4((s8*)arg0 + 4, 0x26, 0x48, (s8*)arg0 + 0xB7E4);
}

void func_8002CA34(s8*, s32, s32);
void func_8002CC44(s8*);
s32 func_8002CD7C(s8*);
void func_89102A04(s8*);
void func_891084B4(s8*, s32, s32, s8*, s8*, s32);
s32 func_891089BC(s8*);
void func_89108F14(s8*, s32, s32, s8*);
s32 func_89109174(s8*);
void func_8910A4C8(s8*, s32);
/*
 * Per-frame update for a four-state object at arg0 (state word at offset 0).
 * Returns 1 when the caller should leave this screen. The sub-objects at
 * 4, 0xB59C, 0xB600 and 0xB7B4 are driven by the func_891043BC,
 * func_8002CD7C, func_891089BC and func_89109174 updates.
 */
s32 func_8910452C(s8* arg0) {
    s32 ret = 0;
    s32 r;
    s8* sub;

    switch (M2C_FIELD(arg0, s32*, 0)) {
        case 0:
            sub = arg0 + 4;
            r = func_891043BC(sub);
            if (r == 1) {
                if (M2C_FIELD(arg0, s32*, 0xB55C) != 0) {
                    func_8002CA34(arg0 + 0xB59C, 0xCA, 0xAD);
                    M2C_FIELD(arg0, s32*, 0) = 1;
                } else {
                    ret = 1;
                }
            } else if (r == 2) {
                func_8910A4C8(arg0 + 0xB000, (*M2C_FIELD(arg0, s32***, 0xB164))[M2C_FIELD(arg0, s32*, 0xB16C)] + 8);
                func_891084B4(arg0 + 0xB600, M2C_FIELD(sub, s32*, 0) + 0xAB, M2C_FIELD(sub, s32*, 4) + 0xD, sub + 0xAFFC,
                              sub + 0xB008, (*M2C_FIELD(sub, s32***, 0xB160))[M2C_FIELD(sub, s32*, 0xB168)]);
                M2C_FIELD(arg0, s32*, 0) = 2;
            } else if (r == 3) {
                func_89108F14(arg0 + 0xB7B4, 0xB6, 0xEA, arg0 + 0xB7E4);
                M2C_FIELD(arg0, s32*, 0) = 3;
            }
            break;
        case 1:
            sub = arg0 + 0xB59C;
            r = func_8002CD7C(sub);
            if (r == -1) {
                M2C_FIELD(arg0, s32*, 0) = 0;
            } else if (r > 0) {
                switch (r) {
                    case 1:
                        func_8002CC44(sub);
                        func_89102A04(arg0 + 4);
                        ret = 1;
                        break;
                    case 2:
                        ret = 1;
                        break;
                }
            }
            break;
        case 2:
            r = func_891089BC(arg0 + 0xB600);
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
                            func_891041D8((u8**)a0, a1, M2C_FIELD(arg0, s32*, 0xB744), (Msg891041D8*)(arg0 + 0xB7E4));
                            break;
                        case 3:
                            func_89104314((u8**)a0, (u8**)a1, M2C_FIELD(arg0, s32*, 0xB744));
                            break;
                    }
                    M2C_FIELD(arg0, s32*, off) = 1;
                    if (r == 3) {
                        M2C_FIELD(arg0, s32*, 0) = 0;
                    } else {
                        func_89108F14(arg0 + 0xB7B4, 0xB6, 0xEA, arg0 + 0xB7E4);
                        M2C_FIELD(arg0, s32*, 0) = 3;
                    }
                }
            }
            break;
        case 3:
            if (func_89109174(arg0 + 0xB7B4) == 1) {
                M2C_FIELD(arg0, s32*, 0) = 0;
            }
            break;
    }
    return ret;
}

M2C_UNK func_8002C064(M2C_UNK, M2C_UNK, u8, u8, s32); /* extern */
extern M2C_UNK D_8910A7F0;

void func_89104818(void) {
    func_8002C064(0x38, 0x1E0, M2C_FIELD(&D_8910A7F0, u8 *, 0), M2C_FIELD(&D_8910A7F0, u8 *, 1), (s32) M2C_FIELD(&D_8910A7F0, u8 *, 2));
}

void func_800069CC(void);
s32 func_8002AAC4(void*);
void func_8002CAD0(void*);
void func_89108650(void*);
void func_89108F94(void*);

M2C_UNK func_89104854(M2C_UNK* arg0) {
    func_800069CC();
    switch (*arg0) {
        case 0:
            if (func_8002AAC4(arg0 + 1) != 0) {
                func_89104818();
            }
            func_891019E4(arg0 + 1);
            break;
        case 1:
            if (func_8002AAC4(arg0 + 1) != 0) {
                func_89104818();
            }
            func_891019E4(arg0 + 1);
            func_8002CAD0((s8*)arg0 + 0xB59C);
            break;
        case 2:
            if (func_8002AAC4(arg0 + 1) != 0) {
                func_89104818();
            }
            if (func_8002AAC4((s8*)arg0 + 0xB600) != 0) {
                func_891019E4(arg0 + 1);
            }
            func_89108650((s8*)arg0 + 0xB600);
            break;
        case 3:
            if (func_8002AAC4(arg0 + 1) != 0) {
                func_89104818();
            }
            func_891019E4(arg0 + 1);
            func_89108F94((s8*)arg0 + 0xB7B4);
            break;
    }
}

void func_80027FF8(void*, s32);
void func_891044F0(void*);
extern M2C_UNK D_8910E380;
extern M2C_UNK D_8910E3D0;

void func_89104998(void) {
    D_8910E37C = func_80025BD8();
    if (D_8910E37C != -1) {
        func_80027FF8(&D_8910E380, D_8910E37C);
    }
    func_891044F0(&D_8910E3D0);
}

typedef struct Col891049E8 { u8 r, g, b, a; } Col891049E8;
extern s32 D_8910A908;
extern s32 D_8910A90C;
/*
 * Second name for D_8910A908. The fade-out store in this function family
 * (also func_8200579C, func_8900429C, func_891049E8, func_8A101B30) does not
 * share the counter's address with the load before it, which only happens
 * when the two accesses name different symbols.
 */
extern s32 D_8910A908_2;
extern M2C_UNK D_8910DE44;
M2C_UNK func_80028060(M2C_UNK, M2C_UNK *, M2C_UNK *, s32);
void func_8002C8D8(Col891049E8*, Col891049E8, f32);
s32 func_891049E8(s32 arg0) {
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
    func_800069CC();
    if (D_8910E37C == -1) {
        var_a1 = NULL;
    } else {
        var_a1 = &D_8910E380;
    }
    func_80028060(0, var_a1, &D_8910DE44, D_8910E37C);
    n = D_8910A908;
    func_8002C8D8(&sp2C, *(Col891049E8*)&D_8910A7F0, n / (f64)8.0f);
    func_8002C064(0x38, 0x1E0, sp2C.r, sp2C.g, sp2C.b);
    if (D_8910A90C == 0) {
        n = D_8910A908;
        n++;
        D_8910A908 = n;
    }
    return 0;
}

M2C_UNK func_8000B1FC();                            /* extern */
M2C_UNK func_8000B220();                            /* extern */
s32 func_8910452C(s8*);
M2C_UNK func_89104854(M2C_UNK *);                   /* extern */
extern M2C_UNK D_8910E3D0;

void func_89104B08(s32 arg0) {
    func_8000B1FC();
    func_8000B220();
    func_89104854(&D_8910E3D0);
    func_8910452C(&D_8910E3D0);
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
s32 func_891049E8(s32);

/*
 * func_89104B48
 *
 * Fragment entry point.  It has the same steps as func_89004560 (and the Pokedex
 * entry function func_8A101ED4), differing only in the functions it calls in
 * steps 4 and 5.  Neither argument is used.  The steps are:
 *
 *   1. main_pool_push_state('TERM') saves the main pool state under that tag;
 *      the matching main_pool_pop_state('TERM') is near the end.
 *   2. func_8001A194(0x3C, 0) is called (Font_Init in symbol_addrs.txt).
 *   3. Two assets are loaded with Asset_LoadToSegment: the ROM range
 *      D_002E0BE0..D_002E2B90 into segment 1 and D_00400F70..D_004076E0 into
 *      segment 4.  The segment number is bits 24-27 of the address of
 *      D_01000000 / D_04000000.
 *   4. func_89104998() and StageLoader_UpdateSegments() are called.
 *   5. BgStage_RunUntilCondition is run three times, with timer values 8, 0
 *      and 8: the first and third with callback func_891049E8, the second
 *      with func_89104B08.  What those callbacks do is not established
 *      (func_891049E8 is still assembly).
 *   6. StageLoader_WaitForRetrace() and main_pool_pop_state('TERM').
 *   7. Fragment_QueueCall queues a call to the fragment whose id comes from
 *      the address D_88000000 (bits 20-27, minus 0x10), with the ROM range
 *      D_00235D70..D_00238BD0.
 *
 * Returns 0x8040.
 */
s32 func_89104B48(s32 arg0, s32 arg1) {
    main_pool_push_state('TERM');
    func_8001A194(0x3C, 0);
    Asset_LoadToSegment(((u32)D_01000000 & 0x0F000000) >> 0x18, D_002E0BE0, D_002E2B90, 0);
    Asset_LoadToSegment(((u32)D_04000000 & 0x0F000000) >> 0x18, D_00400F70, D_004076E0, 0);
    func_89104998();
    StageLoader_UpdateSegments();
    BgStage_RunUntilCondition(8, func_891049E8);
    BgStage_RunUntilCondition(0, func_89104B08);
    BgStage_RunUntilCondition(8, func_891049E8);
    StageLoader_WaitForRetrace();
    main_pool_pop_state('TERM');
    Fragment_QueueCall(((((u32)D_88000000) & 0x0FF00000) >> 0x14) - 0x10, D_00235D70, D_00238BD0, 0, 0);
    return 0x8040;
}
