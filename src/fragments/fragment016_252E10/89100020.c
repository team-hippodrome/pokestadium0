/* Stadium Zero fragment016_252E10. */

#include "global.h"
#include "game_state.h"
#include "jpeg_stream.h"
#include "memory.h"
#include "stage_loader.h"
#include "m2c_macros.h"

extern u8 D_80073520[];
M2C_UNK func_80029A64(s32, s32, s32, s32, Color_RGBA8);

M2C_UNK func_89109E5C(s32, s32, s32, s32);          /* extern */
M2C_UNK func_89109FE0(s32);                         /* extern */
void func_89100020(s32 arg0)
{
  s32 var_s0;
  s32 var_s1;
  s8 *var_s2;
  func_89109E5C(arg0 + 0x9E64, arg0 + 0x9EB8, arg0 + 0x9EE0, arg0 + 0x9F44);
  var_s2 = arg0 + 0x8000;
 do { var_s0 = arg0; var_s1 = 0; do { if ((*((s32 *) (((s8 *) var_s2) + 0x1E68))) != 0) { func_89109FE0(var_s0 + 0x9E64); } var_s1 += 0x1C; var_s0 += 0x1C; var_s2 += 0x1C; } while (var_s1 != 0x54); } while (0);
}

M2C_UNK func_8910A03C(s32);                         /* extern */

void func_891000BC(s32 arg0) {
    s32 var_s1;
    s32 var_s2;
    s8 *var_s0;

    var_s0 = arg0 + 0x8000;
    var_s1 = arg0;
    var_s2 = 0;
    do {
        if ((M2C_FIELD(var_s0, s32 *, 0x1E68) != 0) && (M2C_FIELD(var_s0, s32 *, 0x1E6C) != 0)) {
            func_8910A03C(var_s1 + 0x9E64);
        }
        var_s2 += 0x1C;
        var_s1 += 0x1C;
        var_s0 += 0x1C;
    } while (var_s2 != 0x54);
}

typedef struct Entry89100140 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ char unk_10[0x10];
    /* 0x20 */ s32 unk_20;
} Entry89100140; // size = 0x24

typedef struct Ctx89100140 {
    /* 0x000 */ char unk000[0x3B4];
    /* 0x3B4 */ Entry89100140 unk_3B4[3];
    /* 0x420 */ char unk_420[1];
} Ctx89100140;

extern s32 D_8910A7F8[3];
void func_80027410(void*, void*, s32, s32, s32);
void func_89109990(void*, void*, void*, s32);

void func_89100140(Ctx89100140* arg0) {
    s32 i;

    arg0->unk_3B4[0].unk_04 = 0x20;
    arg0->unk_3B4[0].unk_08 = func_80025BD8();
    arg0->unk_3B4[0].unk_0C = 0;
    arg0->unk_3B4[0].unk_20 = 6;
    func_80027410(arg0->unk_3B4[0].unk_10, (s8*)arg0 + 0x90, 0x20, 1, 0);
    func_89109990(&arg0->unk_3B4[0], (s8*)arg0 + 0x8200, (s8*)arg0 + 0x430, 6);
    arg0->unk_3B4[1].unk_04 = 0x21;
    arg0->unk_3B4[1].unk_08 = arg0->unk_3B4[0].unk_08;
    arg0->unk_3B4[1].unk_0C = 1;
    arg0->unk_3B4[1].unk_20 = 0x1E;
    func_80027410(arg0->unk_3B4[1].unk_10, (s8*)arg0 + 0xB0, 0x20, 8, 0);
    func_89109990(&arg0->unk_3B4[1], (s8*)arg0 + 0x8218, (s8*)arg0 + 0x640, 0x1E);
    arg0->unk_3B4[2].unk_04 = 0x11;
    arg0->unk_3B4[2].unk_08 = 0;
    arg0->unk_3B4[2].unk_0C = 2;
    arg0->unk_3B4[2].unk_20 = 0x1E;
    func_80027410(arg0->unk_3B4[2].unk_10, (s8*)arg0 + 0x1B0, 0x20, 4, 0);
    func_89109990(&arg0->unk_3B4[2], (s8*)arg0 + 0x85D8, (s8*)arg0 + 0x58C0, 0x1E);
    for (i = 0; i < 3; i++) {
        arg0->unk_3B4[i].unk_00 = D_8910A7F8[i];
    }
    func_80027410((s8*)arg0 + 0x420, arg0->unk_3B4, 0x24, 3, 3);
}

typedef struct Ctx89100294 {
    /* 0x0000 */ char unk0000[0x8C];
    /* 0x008C */ s32 unk8C;
    /* 0x0090 */ char unk0090[0xB15C - 0x90];
    /* 0xB15C */ s32 mode;
    /* 0xB160 */ char unkB160[0xB548 - 0xB160];
    /* 0xB548 */ s32* ranges;
    /* 0xB54C */ s32 unkB54C;
    /* 0xB550 */ s32 unkB550;
    /* 0xB554 */ s32 unkB554;
} Ctx89100294;
extern s32 D_800603C0;
void func_8000B2F4(s32);
void func_89100294(Ctx89100294* arg0) {
    s32 count;

    switch (arg0->mode) {
        case 0:
            count = arg0->ranges[arg0->mode + 1] - arg0->ranges[arg0->mode] - 1;
            break;
        case 1:
            count = 1;
            break;
        case 2:
            count = arg0->ranges[arg0->mode + 1] - arg0->ranges[arg0->mode];
            break;
    }
    if (arg0->unk8C == 2) {
        arg0->unkB550 = arg0->unkB550;  /* self-assignment is required to match (retail reloads and stores the field) */
    } else {
        arg0->unkB550 = 2;
    }
    arg0->unkB554 = count + 2;
    arg0->unkB54C = D_800603C0;
    func_8000B2F4(D_800603C0);
}

#ifdef NON_MATCHING
/* TODO: decompile func_89100380; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment016_252E10/func_89100380.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_891003A4; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment016_252E10/func_891003A4.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_891005CC; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment016_252E10/func_891005CC.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_89100688; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment016_252E10/func_89100688.s")
#endif

/**
 * Draws a highlight rectangle (via func_80029A64) for the screen object arg0, positioned from
 * the two words at arg0 + 0x2C / 0x30 (what they mean is not established). The word at
 * arg0 + 0xB550 selects the shape: 0 draws a 0x26 x 0x14 rectangle at the origin, 1 a
 * 0x50 x 0x14 rectangle offset 0x26 to the right; other values draw nothing. The colour is
 * read from D_80073520. (Compare func_8910179C.)
 */
void func_89100870(s8* arg0) {
    switch (M2C_FIELD(arg0, s32*, 0xB550)) {
        case 0:
            func_80029A64(M2C_FIELD(arg0, s32*, 0x2C), M2C_FIELD(arg0, s32*, 0x30), 0x26, 0x14, *(Color_RGBA8*)D_80073520);
            return;
        case 1:
            func_80029A64(M2C_FIELD(arg0, s32*, 0x2C) + 0x26, M2C_FIELD(arg0, s32*, 0x30), 0x50, 0x14, *(Color_RGBA8*)D_80073520);
            return;
    }
}

#ifdef NON_MATCHING
/* TODO: decompile func_89100914; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment016_252E10/func_89100914.s")
#endif

typedef struct Color82000BC4 {
    u8 r, g, b, a;
} Color82000BC4;
typedef struct Entry80066AD8 {
    const char* str;
    Color82000BC4 color;
} Entry80066AD8;
extern Entry80066AD8 D_80066AD8[];
s32 func_8002D498(u8*, s32);
M2C_UNK func_8001A384(M2C_UNK, M2C_UNK);
M2C_UNK func_8001A944(s32, s32, M2C_UNK *);
M2C_UNK func_8001AA9C(u8, u8, u8, u8);
M2C_UNK func_8001AB6C();
M2C_UNK func_8001ABBC();

void func_89100F1C(s32 arg0, s32 arg1, u8* arg2, s32 arg3) {
    Color82000BC4 c;
    s32 idx;

    if ((*arg2 > 0) && (*arg2 < 0x98) && ((idx = func_8002D498(arg2, arg3)) != -1)) {
        c = D_80066AD8[idx].color;
        func_8001AB6C();
        func_8001A384(4, 0);
        func_8001AA9C(c.r, c.g, c.b, c.a);
        func_8001A944(arg0, arg1, (M2C_UNK*)D_80066AD8[idx].str);
        func_8001ABBC();
    }
}

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
extern Entry89100FC4 D_8006A9D4[];
extern M2C_UNK D_800734A8;
extern char D_8910DBAC[];
s32 func_8002D454(s32, s32);
void func_89100FC4(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    const char* str;
    Color82000BC4 color;
    s32 idx;

    idx = func_8002D454(arg2, arg3);
    if (idx != -1) {
        if (idx == -2) {
            color = *(Color82000BC4*)&D_800734A8;
            str = D_8910DBAC;
        } else {
            color = D_80066AD8[D_8006A9D4[idx].type].color;
            str = D_8006A9D4[idx].name;
        }
        func_8001AB6C();
        func_8001A384(4, -1);
        func_8001AA9C(color.r, color.g, color.b, color.a);
        func_8001A944(arg0, arg1, (M2C_UNK*)str);
        func_8001ABBC();
    }
}

M2C_UNK func_8001A384(M2C_UNK, M2C_UNK);            /* extern */
M2C_UNK func_8001A944(s32, s32, M2C_UNK *);         /* extern */
M2C_UNK func_8001AA60(s32, s32, s32);               /* extern */
M2C_UNK func_8001AA9C(u8, u8, u8, u8);              /* extern */
M2C_UNK func_8001AB6C();                            /* extern */
M2C_UNK func_8001ABBC();                            /* extern */
extern M2C_UNK D_800734A8;
extern M2C_UNK D_8910DBB4;
extern M2C_UNK D_8910DBBC;
extern M2C_UNK D_8910DBC0;
extern M2C_UNK D_8910DBC4;

void func_891010AC(s32 arg0, s32 arg1, s8 ***arg2) {
    s32 temp_v0;

    func_8001AB6C();
    func_8001AA9C(M2C_FIELD(&D_800734A8, u8 *, 0), M2C_FIELD(&D_800734A8, u8 *, 1), M2C_FIELD(&D_800734A8, u8 *, 2), M2C_FIELD(&D_800734A8, u8 *, 3));
    temp_v0 = M2C_FIELD(**arg2, s32 *, 4);
    switch (temp_v0) {                              /* irregular */
    case 32:
        func_8001A384(4, 0);
        func_8001A944(arg0, arg1, &D_8910DBB4);
        break;
    case 33:
        func_8001A384(4, -1);
        func_8001AA60(arg0 + 0x22, arg1, M2C_FIELD(*arg2, s32 *, 4) + 0x31);
        func_8001AA9C(0xFFU, 0xC8U, 0xFFU, 0xFFU);
        func_8001A944(arg0 - 2, arg1, &D_8910DBBC);
        break;
    case 17:
        func_8001A384(4, -1);
        func_8001AA60(arg0 + 0x22, arg1, M2C_FIELD(*arg2, s32 *, 4) + 0x31);
        func_8001AA9C(0x96U, 0xDCU, 0xD2U, 0xFFU);
        func_8001A944(arg0 - 2, arg1, &D_8910DBC0);
        break;
    case 19:
        func_8001A384(4, 0);
        func_8001A944(arg0, arg1, &D_8910DBC4);
        break;
    }
    func_8001ABBC();
}

void LabPCList_DrawPlainText(s32 arg0, s32 arg1, s8* arg2, s32 arg3, s32 arg4) {
    Font_BeginTranslucentTextRendering();
    Gfx_SetEnvColor(((Color_RGBA8*)&D_800734A8)->r, ((Color_RGBA8*)&D_800734A8)->g, ((Color_RGBA8*)&D_800734A8)->b, ((Color_RGBA8*)&D_800734A8)->a);
    Font_SetActive(4, arg4);
    Font_Printf(arg0, arg1, arg2, arg3);
    Font_EndTexturedTextRendering();
}

#ifdef NON_MATCHING
/* TODO: decompile func_891012A8; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment016_252E10/func_891012A8.s")
#endif

/**
 * Fields of the scrolling list menu used by func_8910179C (same layout as GridMenu80031004
 * in src/2E480.c; offsets not listed are unknown/unused here).
 */
typedef struct ListMenu8910179C {
    /* 0x00 */ char unk00[0x10];
    /* 0x10 */ s32 cellHeight;
    /* 0x14 */ char unk14[0x16];
    /* 0x2A */ u16 flags;
    /* 0x2C */ s32 scroll;
    /* 0x30 */ char unk30[0x4];
    /* 0x34 */ s32 scrollTarget;
} ListMenu8910179C;

/**
 * Draws a fixed-size (0x50 x 0x14) cursor rectangle via func_80029A64 for a scrolling list
 * menu: x = arg1 + 0x26, y = scrollTarget + arg2 - scroll, minus (cellHeight - 1) when flag
 * 0x400 is set; colour read from D_80073520. Compare func_80031004 and func_8002F32C.
 */
void func_8910179C(ListMenu8910179C* arg0, s32 arg1, s32 arg2) {
    s32 y;

    y = arg0->scrollTarget + arg2 - arg0->scroll;
    if (arg0->flags & 0x400) {
        y = y - arg0->cellHeight + 1;
    }
    func_80029A64(arg1 + 0x26, y, 0x50, 0x14, *(Color_RGBA8*)D_80073520);
}

#ifdef NON_MATCHING
/* TODO: decompile func_89101818; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment016_252E10/func_89101818.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_891019E4; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment016_252E10/func_891019E4.s")
#endif

s32 func_89101D44(s8 *arg0, s32 arg1) {
    return (M2C_FIELD(arg0, s32 *, 0x7C) & arg1) != 0;
}

void func_89101D54(s8 *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0x7C) = (s32) (M2C_FIELD(arg0, s32 *, 0x7C) | arg1);
}

void func_89101D64(s8 *arg0, M2C_UNK arg1) {
    M2C_FIELD(arg0, s32 *, 0x7C) = (s32) (M2C_FIELD(arg0, s32 *, 0x7C) & ~arg1);
}

void func_89101D78(s8 *arg0) {
    M2C_FIELD(arg0, s32 *, 0x7C) = 0;
}

s32 func_89101D80(s8 *arg0, s32 arg1)
{
  s32 temp_t7;
  s32 new_var;
  new_var = arg1;
  temp_t7 = ((*((s32 *) (((s8 *) arg0) + 0x7C))) ^ new_var) & 0xFFFFFFFFFFFFFFFFu;
  *((s32 *) (((s8 *) arg0) + 0x7C)) = temp_t7;
  return temp_t7 & new_var;
}

#ifdef NON_MATCHING
/* TODO: decompile func_89101D94; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment016_252E10/func_89101D94.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_89101F90; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment016_252E10/func_89101F90.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_891020F8; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment016_252E10/func_891020F8.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_89102344; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment016_252E10/func_89102344.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_891024A4; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment016_252E10/func_891024A4.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_891025D8; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment016_252E10/func_891025D8.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_89102700; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment016_252E10/func_89102700.s")
#endif

M2C_UNK func_89101D94(s8 *);                      /* extern */
s32 func_89106254(s32);                             /* extern */
M2C_UNK func_89109C6C(s32, s32);                    /* extern */
s32 func_891028CC(s8 *arg0)
{
  s8 *new_var2;
  s32 temp_v0;
  s8 *new_var;
  temp_v0 = func_89106254(arg0 + 0x230);
  new_var2 = arg0 + 0x9648;
  if (temp_v0 == (-1))
  {
    goto block_4;
  }
  if (temp_v0 == 1)
  {
    new_var = arg0 + 0x420;
    func_89109C6C(new_var2, new_var);
    func_89101D94(arg0);
    *((s32 *) (((s8 *) arg0) + 0x88)) = 0;
    block_4:
    *((s32 *) (((s8 *) arg0) + 0x88)) = 0;

  }
  return 0;
}

typedef struct Sub89102930 { char unk00[0x10]; s32 unk10; char unk14[0xC]; } Sub89102930; // 0x20
typedef struct Item89102930 { char unk00[4]; s32 unk04; char unk08[8]; Sub89102930* subs; char unk14[4]; s32 subCount; char unk1C[8]; } Item89102930; // 0x24
typedef struct Slot89102930 { s32 unk00; s32 unk04; char unk08[0x14]; } Slot89102930; // 0x1C
typedef struct Ctx89102930 { char unk0000[0x9E68]; Slot89102930 slots[3]; } Ctx89102930;
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
        if (((Ctx89102930*)arg0)->slots[i].unk00 != 0 && ((Ctx89102930*)arg0)->slots[i].unk04 != 0) {
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
M2C_UNK func_891019E4(s32);                         /* extern */
s32 func_89102930();                                /* extern */
M2C_UNK func_89109D14(s32);                         /* extern */
extern s32 D_8910E37C;

void func_89102A04(s32 arg0) {
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
            func_891019E4(arg0);
        }
        func_80022188(D_8910E37C);
    }
    if (sp1C & 0x30) {
        func_800243B8();
    }
}

#ifdef NON_MATCHING
/* TODO: decompile func_89102AB8; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment016_252E10/func_89102AB8.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_89102C40; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment016_252E10/func_89102C40.s")
#endif

typedef struct Ctx89102EC8 {
    /* 0x0000 */ char unk0000[0x78];
    /* 0x0078 */ s32 unk78;
    /* 0x007C */ char unk007C[0xC];
    /* 0x0088 */ s32 unk88;
    /* 0x008C */ char unk008C[0x9828 - 0x8C];
    /* 0x9828 */ u8 unk9828;
    /* 0x9829 */ u8 unk9829;
    /* 0x982A */ char unk982A[2];
    /* 0x982C */ s32 unk982C;
    /* 0x9830 */ char unk9830[0x98D4 - 0x9830];
    /* 0x98D4 */ s32 unk98D4;
    /* 0x98D8 */ char unk98D8[0x10];
    /* 0x98E8 */ s32 unk98E8;
} Ctx89102EC8;
s32 func_89106C98(void*);
M2C_UNK func_89101D94(s8 *);
s32 func_89102EC8(s8 *arg)
{
  Ctx89102EC8 *arg0 = (Ctx89102EC8 *) arg;
  s32 ret;
  Ctx89102EC8 *new_var;
  ret = func_89106C98(arg0->unk9830);
  if (ret == (-1))
  {
    new_var = arg0;
    new_var->unk88 = 0;
  }
  else
    if (ret == 1)
  {
    if (arg0->unk98E8 >= arg0->unk98D4)
    {
      arg0->unk982C = 0;
      arg0->unk9828 = arg0->unk98D4;
      arg0->unk9829 = arg0->unk98E8;
      arg0->unk78 = 1;
    }
    else
    {
      arg0->unk982C = 1;
      arg0->unk9829 = arg0->unk98D4;
      arg0->unk9828 = arg0->unk98E8;
      arg0->unk78 = 2;
    }
    func_89101D54((s8 *) arg0, 1);
    func_89101D94((s8 *) arg0);
    arg0->unk88 = 0;
  }
  else
  {
 do { if (ret == 2) { arg0->unk9828 = 1; arg0->unk9829 = 100; arg0->unk982C = 0; func_89101D64((s8 *) arg0, 1); func_89101D94((s8 *) arg0); arg0->unk88 = 0; } } while (0);
  }
  return 0;
}

s32 func_89107614(s8*);
void func_89107850(s8*, s8*);
s32 func_89102FBC(s8* arg0) {
    s8* sp24 = arg0 + 0x9920;
    s32 ret = func_89107614(sp24);

    if (ret == -1) {
        M2C_FIELD(arg0, s32*, 0x88) = 0;
    } else if (ret == 1) {
        func_89107850(sp24, arg0 + 0x9918);
        if (M2C_FIELD(arg0, s32*, 0x9918) == 0) {
            func_89101D64(arg0, 2);
        } else {
            func_89101D54(arg0, 2);
        }
        func_89101D94(arg0);
        M2C_FIELD(arg0, s32*, 0x88) = 0;
    } else if (ret == 2) {
        M2C_FIELD(arg0, s32*, 0x9918) = 0;
        func_89101D64(arg0, 2);
        func_89101D94(arg0);
        M2C_FIELD(arg0, s32*, 0x88) = 0;
    }
    return 0;
}

s32 func_89107EC4(s8*);
void func_89108108(s8*, s8*);
s32 func_89103080(s8* arg0) {
    s8* sp24 = arg0 + 0x9B08;
    s32 ret = func_89107EC4(sp24);

    if (ret == -1) {
        M2C_FIELD(arg0, s32*, 0x88) = 0;
    } else if (ret == 1) {
        func_89108108(sp24, arg0 + 0x9B00);
        if (M2C_FIELD(arg0, s32*, 0x9B04) == 0) {
            func_89101D64(arg0, 4);
        } else {
            func_89101D54(arg0, 4);
        }
        func_89101D94(arg0);
        M2C_FIELD(arg0, s32*, 0x88) = 0;
    } else if (ret == 2) {
        M2C_FIELD(arg0, s32*, 0x9B04) = 0;
        func_89101D64(arg0, 4);
        func_89101D94(arg0);
        M2C_FIELD(arg0, s32*, 0x88) = 0;
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

#ifdef NON_MATCHING
/* TODO: decompile func_89103274; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment016_252E10/func_89103274.s")
#endif

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

#ifdef NON_MATCHING
/* TODO: decompile func_891033A0; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment016_252E10/func_891033A0.s")
#endif

void func_891035E4(u8* arg0) {
    s32 i;
    s32** ptr = M2C_FIELD(arg0, s32***, 0x14);

    for (i = 0; i < M2C_FIELD(arg0, s32*, 0x1C); i++) {
        (*ptr++)[1] = i;
    }
}

#ifdef NON_MATCHING
// Matches the ROM, but uses rodata data that is not placed in this file yet.
typedef struct Str7_89103620 { char s[7]; } Str7_89103620;
typedef struct Str9_89103620 { char s[9]; } Str9_89103620;
u32 func_800566BC(s8*);
void func_89103620(s8* arg0, s32 arg1, s32 arg2) {
    switch (arg1) {
        case 0:
            *(Str7_89103620*)arg0 = *(Str7_89103620*)"てもち";
            break;
        case 1:
            *(Str9_89103620*)arg0 = *(Str9_89103620*)"ＧＢ　０";
            arg0[func_800566BC(arg0) - 1] += arg2 + 1;
            break;
        case 2:
            *(Str9_89103620*)arg0 = *(Str9_89103620*)"６４　０";
            arg0[func_800566BC(arg0) - 1] += arg2 + 1;
            break;
    }
}
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment016_252E10/func_89103620.s")
#endif

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

#ifdef NON_MATCHING
/* TODO: decompile func_89103C54; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment016_252E10/func_89103C54.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_89103DAC; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment016_252E10/func_89103DAC.s")
#endif

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

s32 func_89102700(s8*);
s32 func_89102AB8(s8*);
s32 func_89102C40(s8*);
s32 func_89102EC8(s8*);
s32 func_891033A0(s8*);
s32 func_89103858(s8*);
s32 func_89103C54(s8*);
s32 func_89103DAC(s8*);
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

#ifdef NON_MATCHING
/* TODO: decompile func_891049E8; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment016_252E10/func_891049E8.s")
#endif

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
