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
// FAKE: decomp slop. Raw pointer-offset casts stand in for struct fields.
void func_89100020(s32 arg0)
{
  s32 var_s0;
  s32 var_s1;
  s8 *var_s2;
  func_89109E5C(arg0 + 0x9E64, arg0 + 0x9EB8, arg0 + 0x9EE0, arg0 + 0x9F44);
  var_s2 = arg0 + 0x8000;
 do { var_s0 = arg0; var_s1 = 0; do { if ((*((s32 *) (((s8 *) var_s2) + 0x1E68))) != 0) { func_89109FE0(var_s0 + 0x9E64); } var_s1 += 0x1C; var_s0 += 0x1C; var_s2 += 0x1C; } while (var_s1 != 0x54); } while (0);  // FAKE
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
        arg0->unkB550 = arg0->unkB550; // FAKE: self-assignment is required to match (retail reloads and stores the field)
    } else {
        arg0->unkB550 = 2;
    }
    arg0->unkB554 = count + 2;
    arg0->unkB54C = D_800603C0;
    func_8000B2F4(D_800603C0);
}

typedef struct LabPCInitialStateFields {
    u8 pad0000[0x9828];
    u8 unk_9828;
    u8 unk_9829;
    u8 pad982A[2];
    s32 unk_982C;
    u8 pad9830[0xE8];
    s32 unk_9918;
    u8 pad991C[0x1E8];
    s32 unk_9B04;
} LabPCInitialStateFields;

void func_89100380(LabPCInitialStateFields* state) {
    /* IDO schedules these byte stores together when they share a source line. */
    state->unk_9828 = 1; state->unk_9829 = 100;
    state->unk_982C = 0;
    state->unk_9918 = 0;
    state->unk_9B04 = 0;
}

typedef struct Rgba891024A4 { u8 r, g, b, a; } Rgba891024A4;
void func_8002A8C4(s8 *, s32, s32, s32, s32);
void func_80027804(s8*, s8*, s32, s32);
void func_89109B60(s8*);
M2C_UNK func_89109C6C(s32, s32);                    /* extern */
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
typedef struct Big891003A4 {
    /* 0x0000 */ char unk0000[0xB15C];
    /* 0xB15C */ s32 unkB15C;
    /* 0xB160 */ char unkB160[0x20];
    /* 0xB180 */ s32 unkB180;
    /* 0xB184 */ char unkB184[0x3C4];
    /* 0xB548 */ u8* unkB548;
    /* 0xB54C */ char unkB54C[0xC];
    /* 0xB558 */ s32 unkB558;
    /* 0xB55C */ char unkB55C[0x38];
    /* 0xB594 */ s32 unkB594;
} Big891003A4;
void func_891003A4(s8* arg0, s32 arg1, s32 arg2, s32 arg3) {
    UNUSED s32 pad[1];

    func_89100140((Ctx89100140*)arg0);
    func_8002A8C4(arg0, arg1, arg2, 0x234, 0x17E);
    M2C_FIELD(arg0, s32*, 0x24) = 0;
    M2C_FIELD(arg0, s32*, 0x20) = 0;
    M2C_FIELD(arg0, s32*, 0x28) = 0;
    M2C_FIELD(arg0, s32*, 0x14) = 1;
    func_8002A8C4(arg0 + 0x4C, arg1 + 6, arg2 + 6, 0x228, 0x1E);
    M2C_FIELD(arg0, s32*, 0x60) = 6;
    M2C_FIELD(arg0, Rgba891024A4*, 0x64) = *(Rgba891024A4*)D_8910A844;
    M2C_FIELD(arg0, Rgba891024A4*, 0x68) = *(Rgba891024A4*)D_8910A848;
    func_8002A8C4(arg0 + 0x2C, arg1 + 6, arg2 + 0x3A, 0x228, 0x12E);
    M2C_FIELD(arg0, s32*, 0x40) = 1;
    func_80027804(arg0 + 0x9648, arg0 + 0x87B8, 0x1D2, 0);
    func_80027804(arg0 + 0x6C, arg0 + 0x8F00, 0x1D2, 0);
    func_89109B60(arg0 + 0x420);
    M2C_FIELD(arg0, s32*, 0x7C) = 0;
    M2C_FIELD(arg0, u8**, 0x84) = D_8910A804;
    func_89109C6C((s32)(arg0 + 0x9648), (s32)(arg0 + 0x420));
    M2C_FIELD(arg0, s32*, 0x78) = 0;
    func_80027D68((s32)(arg0 + 0x9648), D_8910D990[0]);
    M2C_FIELD(arg0, s32*, 0x8C) = 0;
    func_89100020((s32)arg0);
    M2C_FIELD(arg0, s32*, 0x80) = 0;
    ((Big891003A4*)arg0)->unkB15C = 0;
    func_8002EC24(arg0 + 0xB160, arg0 + 0x9648, arg0 + 0xB1A4, 0xE, func_891012A8, 0x228, 0x14);
    ((Big891003A4*)arg0)->unkB180 &= ~0x100000;
    ((Big891003A4*)arg0)->unkB548 = D_8910A84C;
    func_89100294((Ctx89100294*)arg0);
    ((Big891003A4*)arg0)->unkB558 = 0;
    ((Big891003A4*)arg0)->unkB594 = arg3;
    func_89100380((LabPCInitialStateFields*)arg0);
    M2C_FIELD(arg0, s32*, 0x88) = 1;
    func_89105C54(arg0 + 0x230, 0x78, 0x67, arg0 + 0x420, D_8910A7F4);
}

typedef struct Ctx89100688 {
    /* 0x0000 */ char unk0000[0x2C];
    /* 0x002C */ s32 x;
    /* 0x0030 */ s32 y;
    /* 0x0034 */ char unk0034[0x84 - 0x34];
    /* 0x0084 */ s32* widths;
    /* 0x0088 */ char unk0088[0xB15C - 0x88];
    /* 0xB15C */ s32 mode;
    /* 0xB160 */ char unkB160[0xB548 - 0xB160];
    /* 0xB548 */ s32* ranges;
    /* 0xB54C */ s32 unkB54C;
    /* 0xB550 */ s32 cursor;
} Ctx89100688;

s32 func_891005CC(Ctx89100688* arg0) {
    s32 i;
    s32 x = 0;
    s32 end;

    for (i = arg0->ranges[arg0->mode], end = arg0->ranges[arg0->mode] + arg0->cursor - 2; i < end; i++) {
        x += arg0->widths[i];
    }
    return arg0->x + x + 0x78;
}

void func_89100688(Ctx89100688* arg0) {
    s32 end;
    s32* r;
    s32 i;
    s32 w;

    switch (arg0->mode) {
        case 0:
            end = arg0->ranges[arg0->mode] + arg0->cursor - 2;
            i = end;
            if (i == 4) {
                w = arg0->widths[i] + arg0->widths[i + 1];
            } else {
                w = arg0->widths[i];
            }
            func_80029A64(func_891005CC(arg0), arg0->y, w, 0x14, *(Color_RGBA8*)D_80073520);
            break;
        case 1:
            w = 0;
            r = &arg0->ranges[arg0->mode];
            i = r[0] + arg0->cursor - 2;
            end = r[1] - r[0] + i;
            for (; i < end; i++) {
                w += arg0->widths[i];
            }
            func_80029A64(func_891005CC(arg0), arg0->y, w, 0x14, *(Color_RGBA8*)D_80073520);
            break;
        case 2:
            func_80029A64(func_891005CC(arg0), arg0->y, arg0->widths[arg0->ranges[arg0->mode] + arg0->cursor - 2], 0x14, *(Color_RGBA8*)D_80073520);
            break;
    }
}

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
M2C_UNK func_8001A944(s32, s32, M2C_UNK *, ...);
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
M2C_UNK func_8001A944(s32, s32, M2C_UNK *, ...);         /* extern */
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

extern u8 D_04006170[];
extern u8 D_04006CE0[];
extern Gfx D_80060290[];
extern Gfx D_80060398[];

extern u8 D_8910C370[];
extern u8 D_8910C978[];
extern char D_8910DBF0[];
extern char D_8910DC04[];
void Gfx_DrawTextureRgba16(s32, s32, s32, s32, u8*, s32, s32);

void func_89101818(s8* arg0) {
    func_8001AB6C();
    func_8001AA9C(M2C_FIELD(&D_800734A8, u8*, 0), M2C_FIELD(&D_800734A8, u8*, 1), M2C_FIELD(&D_800734A8, u8*, 2), M2C_FIELD(&D_800734A8, u8*, 3));
    func_8001A384(8, 0);
    func_8001A944(M2C_FIELD(arg0, s32*, 0x4C) + 0x22, M2C_FIELD(arg0, s32*, 0x50) + 5, (M2C_UNK*)D_8910DBF0);
    func_8001A944(M2C_FIELD(arg0, s32*, 0x4C) + 0x152, M2C_FIELD(arg0, s32*, 0x50) + 5, (M2C_UNK*)D_8910DC04,
                  M2C_FIELD(arg0, s32*, 0xB15C) + 1);
    func_8001ABBC();
    gSPDisplayList(gDisplayListHead++, D_80060290);
    Gfx_DrawTextureRgba16(M2C_FIELD(arg0, s32*, 0x4C) + 4, M2C_FIELD(arg0, s32*, 0x50) + 3, 0x1A, 0x18, D_8910C370, 0x20, 0x200000);
    Gfx_DrawTextureRgba16(M2C_FIELD(arg0, s32*, 0x4C) + 0xDA, M2C_FIELD(arg0, s32*, 0x50) + 3, 0x1A, 0x18, D_8910C978, 0x20, 0x200000);
    Gfx_DrawTextureRgba16(M2C_FIELD(arg0, s32*, 0x4C) + 0x134, M2C_FIELD(arg0, s32*, 0x50) + 2, 0x1A, 0x1A, D_04006170, 0x1C, 0x200000);
    Gfx_DrawTextureRgba16(M2C_FIELD(arg0, s32*, 0x4C) + 0x20A, M2C_FIELD(arg0, s32*, 0x50) + 2, 0x1A, 0x1A, D_04006CE0, 0x1C, 0x200000);
    gSPDisplayList(gDisplayListHead++, D_80060398);
}

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

// FAKE: decomp slop. Raw pointer-offset casts stand in for struct fields.
s32 func_89101D80(s8 *arg0, s32 arg1)
{
  s32 temp_t7;
  s32 new_var;
  new_var = arg1;
  temp_t7 = ((*((s32 *) (((s8 *) arg0) + 0x7C))) ^ new_var) & 0xFFFFFFFFFFFFFFFFu;
  *((s32 *) (((s8 *) arg0) + 0x7C)) = temp_t7;
  return temp_t7 & new_var;
}

typedef struct Ctx89101D94 {
    /* 0x0000 */ char unk0000[0x6C];
    /* 0x006C */ char unk6C[0xC];
    /* 0x0078 */ s32 unk78;
    /* 0x007C */ s32 unk7C;
    /* 0x0080 */ char unk0080[0x9648 - 0x80];
    /* 0x9648 */ char unk9648[0x9828 - 0x9648];
    /* 0x9828 */ char unk9828[0x9918 - 0x9828];
    /* 0x9918 */ char unk9918[0x9B00 - 0x9918];
    /* 0x9B00 */ char unk9B00[0x9E58 - 0x9B00];
    /* 0x9E58 */ char unk9E58[4];
    /* 0x9E5C */ char unk9E5C[0xB160 - 0x9E5C];
    /* 0xB160 */ s32 unkB160;
    /* 0xB164 */ char unkB164[0xB1A4 - 0xB164];
    /* 0xB1A4 */ char unkB1A4[4];
} Ctx89101D94;
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
M2C_UNK func_89101D94(Ctx89101D94* arg0) {
    func_8002ED18(&arg0->unkB160, arg0->unk9648, arg0->unkB1A4);
    if (arg0->unk7C != 0) {
        if (arg0->unk7C & 1) {
            func_80027D94(arg0->unkB160, arg0->unk6C, func_891096F4, arg0->unk9828);
            func_8002ED18(&arg0->unkB160, arg0->unk6C, arg0->unkB1A4);
        }
        if (arg0->unk7C & 2) {
            func_80027D94(arg0->unkB160, arg0->unk6C, func_89109720, arg0->unk9918);
            func_8002ED18(&arg0->unkB160, arg0->unk6C, arg0->unkB1A4);
        }
        if (arg0->unk7C & 4) {
            func_80027D94(arg0->unkB160, arg0->unk6C, func_891097E4, arg0->unk9B00);
            func_8002ED18(&arg0->unkB160, arg0->unk6C, arg0->unkB1A4);
        }
        if (arg0->unk7C & 8) {
            func_80027D94(arg0->unkB160, arg0->unk6C, func_89109884, arg0->unk9E58);
            func_8002ED18(&arg0->unkB160, arg0->unk6C, arg0->unkB1A4);
        }
        if (arg0->unk7C & 0x10) {
            func_80027D94(arg0->unkB160, arg0->unk6C, func_89109898, arg0->unk9E5C);
            func_8002ED18(&arg0->unkB160, arg0->unk6C, arg0->unkB1A4);
        }
        if (arg0->unk7C & 0x20) {
            func_80027D94(arg0->unkB160, arg0->unk6C, func_89109960, NULL);
            func_8002ED18(&arg0->unkB160, arg0->unk6C, arg0->unkB1A4);
        }
    }
    func_80027D68(arg0->unkB160, D_8910D990[arg0->unk78]);
}

typedef struct Pair8910D910 { void* a; s32 b; } Pair8910D910;
extern Pair8910D910 D_8910D910[];
void func_89106424(s8*, void*, s8*, s32, s32);
void func_89106570(s8*);
void func_891071A4(s8*, s32, s32, s8*);
void func_89107A60(s8*, s32, s32, s8*);
typedef struct Ctx89101F90 {
    /* 0x0000 */ char unk0000[0x2C];
    /* 0x002C */ s32 x;
    /* 0x0030 */ s32 y;
    /* 0x0034 */ s32 dx;
    /* 0x0038 */ s32 dy;
    /* 0x003C */ char unk003C[0x88 - 0x3C];
    /* 0x0088 */ s32 state;
    /* 0x008C */ char unk008C[0x9654 - 0x8C];
    /* 0x9654 */ s8 unk9654[0x966C - 0x9654];
    /* 0x966C */ Rgba891024A4 color;
    /* 0x9670 */ char unk9670[0x9680 - 0x9670];
    /* 0x9680 */ s8 unk9680[0x96C8 - 0x9680];
    /* 0x96C8 */ s32 posX;
    /* 0x96CC */ s32 posY;
    /* 0x96D0 */ char unk96D0[0x97C8 - 0x96D0];
    /* 0x97C8 */ s8 unk97C8[0x9918 - 0x97C8];
    /* 0x9918 */ s8 unk9918[0x9920 - 0x9918];
    /* 0x9920 */ s8 unk9920[0x9B00 - 0x9920];
    /* 0x9B00 */ s8 unk9B00[0x9B08 - 0x9B00];
    /* 0x9B08 */ s8 unk9B08[0xB15C - 0x9B08];
    /* 0xB15C */ s32 mode;
    /* 0xB160 */ char unkB160[0xB548 - 0xB160];
    /* 0xB548 */ s32* ranges;
    /* 0xB54C */ char unkB54C[4];
    /* 0xB550 */ s32 base;
} Ctx89101F90;

void func_89101F90(Ctx89101F90* arg0) {
    s32 sel;

    sel = arg0->ranges[arg0->mode] + arg0->base - 2;
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
            func_89106424(arg0->unk9654, D_8910D910[sel].a, arg0->unk97C8, D_8910D910[sel].b, 0);
            func_8002A8C4(arg0->unk9680, func_891005CC(arg0), arg0->y, 0, 0x16);
            arg0->posX = arg0->x + arg0->dx;
            arg0->posY = arg0->y + arg0->dy;
            func_89106570(arg0->unk9654);
            arg0->color = D_8910A7F4;
            break;
        case 4:
        case 5:
            func_891071A4(arg0->unk9920, 0x81, 0x94, arg0->unk9918);
            arg0->state = 5;
            break;
        case 6:
        case 7:
        case 8:
        case 9:
            func_89107A60(arg0->unk9B08, 0x81, 0x94, arg0->unk9B00);
            arg0->state = 6;
            break;
    }
}

typedef struct Str891020F8 { char s[13]; } Str891020F8;
typedef struct Big891020F8 {
    /* 0x0000 */ char unk0000[0x96C8];
    /* 0x96C8 */ s32 right;
    /* 0x96CC */ s32 bottom;
} Big891020F8;
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

void func_891020F8(s8* arg0) {
    func_8000A460(D_8910E2D0, *(s8**)D_80064C44[M2C_FIELD(M2C_FIELD(arg0, s8****, 0xB160)[0][M2C_FIELD(arg0, s32*, 0xB168)], u8*, 8)]);
    func_8000A460(D_8910E2D0 + func_800566BC(D_8910E2D0), D_8910A890[(M2C_FIELD(arg0, s32*, 0x7C) & 8) ? 1 : 0]);
    *(Str891020F8*)D_8910E312 = *(Str891020F8*)D_8910DC50;
    func_8000A460(D_8910E2D0 + (func_800566BC(D_8910E312) + 0x42), D_8910A890[(M2C_FIELD(arg0, s32*, 0x7C) & 0x10) ? 1 : 0]);
    func_89106424(arg0 + 0x9654, D_8910A898, arg0 + 0x97C8, 4, 0);
    func_8002A8C4(arg0 + 0x9680, M2C_FIELD(arg0, s32*, 0x2C) + 0x26,
                  M2C_FIELD(arg0, s32*, 0x30) + M2C_FIELD(arg0, s32*, 0xB194) - M2C_FIELD(arg0, s32*, 0xB18C) + 0x16, 0, 0x14);
    ((Big891020F8*)arg0)->right = M2C_FIELD(arg0, s32*, 0x34) + M2C_FIELD(arg0, s32*, 0x2C);
    ((Big891020F8*)arg0)->bottom = M2C_FIELD(arg0, s32*, 0x38) + M2C_FIELD(arg0, s32*, 0x30);
    func_89106570(arg0 + 0x9654);
    M2C_FIELD(arg0, Rgba891024A4*, 0x966C) = D_8910A7F4;
    M2C_FIELD(arg0, s32*, 0x88) = 7;
    func_80027804(arg0 + 0xAFFC, arg0 + 0xAD54, 0xAA, 0);
    func_8910A21C(arg0 + 0xAFFC, arg0 + 0xA00C, arg0 + 0x9E64, 3);
    if (M2C_FIELD(arg0, s32*, 0xB004) == 0) {
        M2C_FIELD(M2C_FIELD(arg0, s8**, 0x9698), u16*, 6) |= 1;
    }
}

typedef struct List89102344 {
    /* 0x00 */ u8** items;
    /* 0x04 */ char unk04[4];
    /* 0x08 */ s32 count;
} List89102344;

typedef struct Ctx89102344 {
    /* 0x0000 */ char unk0000[0x8C];
    /* 0x008C */ s32 unk8C;
    /* 0x0090 */ char unk0090[0xB160 - 0x90];
    /* 0xB160 */ List89102344* list;
    /* 0xB164 */ char unkB164[4];
    /* 0xB168 */ s32 cursor;
    /* 0xB16C */ char unkB16C[4];
    /* 0xB170 */ s32 unkB170;
    /* 0xB174 */ char unkB174[0xB18C - 0xB174];
    /* 0xB18C */ s32 unkB18C;
    /* 0xB190 */ char unkB190[4];
    /* 0xB194 */ s32 unkB194;
    /* 0xB198 */ char unkB198[0xB550 - 0xB198];
    /* 0xB550 */ s32 unkB550;
} Ctx89102344;

s32 func_8003F6AC();
s32 func_8002FD8C(void*);
void func_800306E0(void*, s32);
void func_891020F8(s8*);

s32 func_89102344(Ctx89102344* arg0) {
    s32 ret;

    if ((arg0->unkB194 == 0) && (*(u16*)(D_800603C0 + 6) & 0x800)) {
        func_8003F6AC(1);
        arg0->unk8C = 2;
        arg0->unkB550 = 1;
        func_800306E0(&arg0->list, arg0->unkB18C / arg0->unkB170);
        return 1;
    }
    ret = func_8002FD8C(&arg0->list) != 0;
    if ((ret == 0) && (*(u16*)(D_800603C0 + 8) & 0x8000)) {
        if ((arg0->list->count > 0) && (arg0->list->items[arg0->cursor][8] > 0) && (arg0->list->items[arg0->cursor][8] < 0x98)) {
            func_8003F6AC(2);
            func_891020F8((s8*)arg0);
            ret = 1;
        } else {
            func_8003F6AC(8);
        }
    }
    return ret;
}

typedef struct Screen891024A4 {
    /* 0x0000 */ char unk0[0x2C];
    /* 0x002C */ s32 x;
    /* 0x0030 */ s32 y;
    /* 0x0034 */ s32 w;
    /* 0x0038 */ s32 h;
    /* 0x003C */ char unk3C[0x40];
    /* 0x007C */ s32 mode;
    /* 0x0080 */ char unk80[0x9654 - 0x80];
    /* 0x9654 */ s8 menu[0x18];
    /* 0x966C */ Rgba891024A4 color;
    /* 0x9670 */ char unk9670[0x10];
    /* 0x9680 */ s8 box[0x18];
    /* 0x9698 */ s8 *boxItems;
    /* 0x969C */ char unk969C[0x2C];
    /* 0x96C8 */ s32 right;
    /* 0x96CC */ s32 bottom;
    /* 0x96D0 */ char unk96D0[0xF8];
    /* 0x97C8 */ s8 items[1];
} Screen891024A4;
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
void func_891024A4(Screen891024A4 *arg0) {
    func_8000A460(D_8910E358, D_8910A8B0);
    func_8000A460(D_8910E358 + func_800566BC(D_8910E358), D_8910A8A8[(arg0->mode & 0x20) ? 1 : 0]);
    func_89106424(arg0->menu, D_8910A8C8, arg0->items, 5, 0);
    func_8002A8C4(arg0->box, arg0->x + 0x26, arg0->y, 0, 0x16);
    arg0->right = arg0->x + arg0->w;
    arg0->bottom = arg0->y + arg0->h;
    func_89106570(arg0->menu);
    arg0->color = D_8910A7F4;
    if (arg0->mode == 0) {
        M2C_FIELD(arg0->boxItems, u16 *, 6) |= 1;
    }
}

typedef struct Ctx891025D8 {
    /* 0x0000 */ char unk0000[0x88];
    /* 0x0088 */ s32 unk88;
    /* 0x008C */ s32 unk8C;
    /* 0x0090 */ char unk0090[0xB188 - 0x90];
    /* 0xB188 */ s16 unkB188;
    /* 0xB18A */ char unkB18A[0xB1A0 - 0xB18A];
    /* 0xB1A0 */ s32 unkB1A0;
    /* 0xB1A4 */ char unkB1A4[0xB54C - 0xB1A4];
    /* 0xB54C */ s32 unkB54C;
    /* 0xB550 */ s32 unkB550;
} Ctx891025D8;
s32 func_8002B390(s32*);

s32 func_891025D8(Ctx891025D8* arg0) {
    s32 ret = 0;
    s32 button;

    button = func_8002B390(&arg0->unkB54C);
    if (button != 0) {
        if ((button == 0x400) && (arg0->unkB550 == 1)) {
            func_8003F6AC(1);
            arg0->unk8C = 0;
            arg0->unkB1A0 = 8; arg0->unkB188 = 0x400; // FAKE: both stores must share one source line (IDO schedules by line)
            ret = 1;
        } else {
            arg0->unk8C = (arg0->unkB550 < 2) ? 2 : 1;
            ret = 1;
        }
    } else if (*(u16*)(D_800603C0 + 8) & 0x8000) {
        if (arg0->unkB550 == 0) {
            func_8003F6AC(3);
            ret = -1;
        } else if (arg0->unkB550 == 1) {
            func_8003F6AC(2);
            func_891024A4((Screen891024A4*)arg0);
            ret = 1;
            arg0->unk88 = 2;
        } else {
            func_8003F6AC(2);
            func_89101F90((Ctx89101F90*)arg0);
            ret = 1;
        }
    }
    return ret;
}


s32 func_89102700(Ctx89100294* arg0) {
    s32 done = FALSE;
    s32 result;
    u16 buttons;

    switch (arg0->unk8C) {
        case 0:
            result = func_89102344((Ctx89102344*)arg0);
            break;
        case 1:
        case 2:
            result = func_891025D8((Ctx891025D8*)arg0);
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
            if (arg0->mode == 0) {
                arg0->mode += 3;
            }
            arg0->mode--;
            func_89100294(arg0);
        } else if (buttons & 1) {
            func_8003F6AC(2);
            if (arg0->mode >= 2) {
                arg0->mode -= 3;
            }
            arg0->mode++;
            func_89100294(arg0);
        } else if (buttons & 0x20) {
            if (arg0->unk8C != 0) {
                func_8003F6AC(2);
                arg0->unk8C = 0;
            }
        } else if ((buttons & 0x10) && (arg0->unk8C != 1)) {
            func_8003F6AC(2);
            arg0->unk8C = 1;
            arg0->unkB550 = 2;
        }
    }
    return done;
}

M2C_UNK func_89101D94();
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
