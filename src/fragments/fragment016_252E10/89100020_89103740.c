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

#ifdef NON_MATCHING
/* TODO: decompile func_89103858; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment016_252E10/func_89103858.s")
#endif

typedef struct List89103C54 {
    /* 0x00 */ Ref89103740** items;
} List89103C54;
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
void func_800307D4(List89103C54**, s32, s32);
void func_89109C6C(s8*, s8*);

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

#ifdef NON_MATCHING
/* TODO: decompile func_89103F04; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment016_252E10/func_89103F04.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_891041D8; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment016_252E10/func_891041D8.s")
#endif

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
s32 func_89103858(s8*);
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
            ret = func_89103858(arg0);
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

#ifdef NON_MATCHING
/* TODO: decompile func_8910452C; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment016_252E10/func_8910452C.s")
#endif

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
M2C_UNK func_8910452C(M2C_UNK *);                   /* extern */
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
