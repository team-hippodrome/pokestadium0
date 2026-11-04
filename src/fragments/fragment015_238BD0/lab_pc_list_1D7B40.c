/* Stadium Zero fragment015_238BD0. */
/* C ported from the Stadium 1 decomp: src/fragments/lab_pc_list/lab_pc_list_1D7B40.c. */

#include "fragments/lab_pc_list/lab_pc_list.h"
#include "graphics_textures.h"
#include "input.h"
#include "gb_data.h"
#include "game_state.h"
#include "table_view.h"
#include "text_system.h"
#include "gb_save.h"
#include "audio_sfx.h"
#include "hal_libc.h"
#include "memmap.h"
#include "memory.h"
#include "pokemon_stats.h"
extern u8 D_8910D7D0[];
typedef struct unk_func_88309614 {
    /* 0x00 */ char unk00[0x8];
    /* 0x08 */ s32 unk_08;
} unk_func_88309614;
typedef struct unk_func_88313894 {
    /* 0x00 */ char unk00[0xC];
    /* 0x0C */ unk_func_8830867C_02C_0CC_000_000* unk_0C;
    /* 0x10 */ char unk10[0xC];
    /* 0x1C */ s32 unk_1C;
    /* 0x20 */ unk_func_88313894_020 unk_20;
    /* 0x40 */ unk_func_88313894_020 unk_40;
} unk_func_88313894;

#include "fragments/particle_math/particle_math.h"
#include "m2c_macros.h"
void func_8002ED18(s8*, s32, s8*);

void func_89004708(void);
void func_89004710(void);

void func_89004680(s32 arg0, s32 arg1, s32 arg2, u8* arg3) {
    DeckHandle* sp1C = Deck_Open(arg0, arg1, arg2, 1);

    Deck_WriteEntries(M2C_FIELD(arg3, u8**, 0), M2C_FIELD(arg3, s32*, 8), sp1C);

    if ((arg0 == 0x10) || (arg0 == 0x11) || (arg0 == 0x12) || (arg0 == 0x13)) {
        Deck_CloseAndFlushBox(sp1C);
    } else {
        Deck_CloseAndFlush(sp1C);
    }
}

void func_89004708(void) {
}

void func_89004710(void) {
}

void func_89004718(s8* arg0, s8* arg1) {
    s32 i;

    for (i = 0; i < 13; i++) {
        if (M2C_FIELD(arg1 + i * 0x10, s32*, 8) == 0) {
            M2C_FIELD(arg0, u16**, 0x30)[i] |= 0x100;
        }
    }
}

void func_890047E4(s8 *arg0, s8 *arg1) {
    u16 *temp_v0;

    if (M2C_FIELD(arg1, s32 *, 8) == 1) {
        temp_v0 = M2C_FIELD(arg0, u16 **, 0x30);
        *temp_v0 |= 0x200;
    }
}

void func_8900480C(s8* arg0, s8* arg1) {
    s32 i;

    for (i = 0; i < 13; i++) {
        if (M2C_FIELD(arg1 + i * 0x10, s32*, 8) == M2C_FIELD(arg1 + i * 0x10, s32*, 4)) {
            M2C_FIELD(arg0, u16**, 0x30)[i] |= 0x400;
        }
    }
}

void func_890048EC(s8 *arg0, s32 arg1) {
    u16 *temp_v0;

    temp_v0 = M2C_FIELD(arg0, s32 *, 0x30) + (arg1 * 2);
    *temp_v0 |= 1;
}

typedef struct Rgba89004908 {
    /* 0x0 */ u8 r, g, b, a;
} Rgba89004908; // size = 0x4
void func_8002A0AC(s32, s32, s32, s32, Rgba89004908);
M2C_UNK func_8001AA9C(u8, u8, u8, u8);
extern Rgba89004908 D_8900A5BC;
extern Rgba89004908 D_8900A730[];
extern Rgba89004908 D_800734B0[];
extern M2C_UNK D_800734A8;
void func_89004908(s32 x, s32 y, char* str, UNUSED s32 index, s32 flags) {
    Rgba89004908 color;
    UNUSED s32 pad[4];

    if (flags & 0x10) {
        func_8002A0AC(x + 3, y + 3, 0xD2, 0x16, D_8900A5BC);
    }
    Font_BeginTranslucentTextRendering();
    if (flags & 1) {
        color = ((Rgba89004908*)&D_800734A8)[1];
        color.a = 0x4C;
    } else if (flags & 0x100) {
        color = D_8900A730[(flags & 2) ? 0 : 1];
    } else if (flags & 0x200) {
        color = D_8900A730[(flags & 2) ? 0 : 1];
    } else if (flags & 0x400) {
        color = D_800734B0[(flags & 2) ? 0 : 1];
    } else {
        color = ((Rgba89004908*)&D_800734A8)[(flags & 2) ? 0 : 1];
    }
    func_8001AA9C(color.r, color.g, color.b, color.a);
    Font_SetActive(8, 0);
    Font_Printf(x + 8, y + 4, str);
    Font_EndTexturedTextRendering();
}

#ifdef NON_MATCHING
/* TODO: decompile func_89004AD4; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment015_238BD0/func_89004AD4.s")
#endif

s32 func_8002AE6C();                                /* extern */
M2C_UNK func_8002D9B8(s8 *, s32, s32, M2C_UNK, s32); /* extern */

void func_89004B98(s8 *arg0) {
    if (func_8002AE6C() == 0) {
        func_8002D9B8(arg0 + 0x2C, M2C_FIELD(arg0, s32 *, 0) + 6, M2C_FIELD(arg0, s32 *, 4) + 0xA, 0xFFEF, 0);
    }
}

s32 func_8002DCE0(void*);
s32 func_8002BC14(s32);
M2C_UNK func_8003F6AC(M2C_UNK);
extern s32 D_800603C0;
s32 func_89004BE0(s32 arg0) {
    s32 sp1C = 0;
    s32 dir;

    if (func_8002DCE0((u8*)arg0 + 0x2C) == 0) {
        dir = func_8002BC14(D_800603C0);
        if (dir == -1) {
            func_8003F6AC(3);
            sp1C = -1;
        } else if (dir == 1) {
            sp1C = M2C_FIELD(arg0, s32*, 0x34) + 1;
        }
    }
    return sp1C;
}

#ifdef NON_MATCHING
/* TODO: decompile func_89004C54; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment015_238BD0/func_89004C54.s")
#endif

void func_89004E1C(s8* arg0, s32 arg1) {
    func_8002ED18(arg0, arg1, arg0 + 0x44);
}

void func_8002EC24(s8*, s32, s8*, s32, void*, s32, s32);
void func_89004C54();

void func_89004E3C(s8* arg0, s32 arg1, s32 arg2, s32 arg3) {
    M2C_FIELD(arg0, s32*, 0x80) = arg1;
    M2C_FIELD(arg0, s32*, 0x84) = arg2;
    func_8002EC24(arg0, arg3, arg0 + 0x44, 6, func_89004C54, 0xCC, 0x1C);
    M2C_FIELD(arg0, s32*, 0x20) |= 0x10000;
}

#ifdef NON_MATCHING
/* TODO: decompile func_89004EB0; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment015_238BD0/func_89004EB0.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_89004FE4; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment015_238BD0/func_89004FE4.s")
#endif

M2C_UNK func_8002B054(M2C_UNK, s32);                /* extern */

void func_89005068(s32 arg0, M2C_UNK arg1, M2C_UNK arg2, M2C_UNK arg3, s32 arg4) {
    func_8002B054(arg2, arg4);
}

#ifdef NON_MATCHING
/* TODO: decompile func_89005098; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment015_238BD0/func_89005098.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_890054D4; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment015_238BD0/func_890054D4.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_890056A4; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment015_238BD0/func_890056A4.s")
#endif

M2C_UNK func_8001A384(M2C_UNK, M2C_UNK);            /* extern */
M2C_UNK func_8001A944(s32, s32, s32);               /* extern */
M2C_UNK func_8001AA9C(u8, u8, u8, u8);              /* extern */
M2C_UNK func_8001AB2C(M2C_UNK);                     /* extern */
M2C_UNK func_8001AB6C();                            /* extern */
M2C_UNK func_8001ABBC();                            /* extern */
extern M2C_UNK D_800734A8;

void func_89005958(s32 arg0, s32 arg1, s32 arg2) {
    func_8001AB6C();
    func_8001A384(0x10, 0);
    func_8001AA9C(M2C_FIELD(&D_800734A8, u8 *, 0), M2C_FIELD(&D_800734A8, u8 *, 1), M2C_FIELD(&D_800734A8, u8 *, 2), M2C_FIELD(&D_800734A8, u8 *, 3));
    func_8001AB2C(0x2C);
    func_8001A944(arg0 + 0xC, arg1 + 0x14, arg2);
    func_8001ABBC();
}

#ifdef NON_MATCHING
/* TODO: decompile func_890059D0; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment015_238BD0/func_890059D0.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_89005AE0; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment015_238BD0/func_89005AE0.s")
#endif

void func_89000020(void* arg0, void* arg1);
void func_89000048(void*);

void func_89005E14(s8* arg0) {
    M2C_FIELD(arg0, s32**, 0x3AC)[M2C_FIELD(arg0, s32*, 0x248)] = 1;
    M2C_FIELD(arg0, s32**, 0x3AC)[M2C_FIELD(arg0, s32*, 0x1D0)] = M2C_FIELD(arg0, s32**, 0x3AC)[M2C_FIELD(arg0, s32*, 0x248)];
    func_89000020(arg0 + 0x31C, (void*)(M2C_FIELD(arg0, s32**, 0x294)[3] * M2C_FIELD(arg0, s32*, 0x29C) + M2C_FIELD(arg0, s32**, 0x294)[0]));
    func_89000048(arg0 + 0x294);
}

void func_80027654(s32* matrix, u8* out, s32 row);
void func_80027700(s32* matrix, u8* in, s32 row);

void func_89005EA4(s8* arg0) {
    u8 row[0x50];
    s32* matrix = M2C_FIELD(arg0, s32**, 0x294);

    func_80027654(matrix, row, M2C_FIELD(arg0, s32*, 0x29C));
    func_80027700(matrix, (u8*)(matrix[3] * M2C_FIELD(arg0, s32*, 0x3A4) + matrix[0]), M2C_FIELD(arg0, s32*, 0x29C));
    func_80027700(matrix, row, M2C_FIELD(arg0, s32*, 0x3A4));
    M2C_FIELD(arg0, s32**, 0x3AC)[M2C_FIELD(arg0, s32*, 0x28C)] = 1;
}


void func_89005F2C(s8* arg0) {
    u8 row[0x50];
    s32* matrix;

    func_80027654(M2C_FIELD(arg0, s32**, 0x31C), row, M2C_FIELD(arg0, s32*, 0x324));
    matrix = M2C_FIELD(arg0, s32**, 0x294);
    func_80027700(M2C_FIELD(arg0, s32**, 0x31C), (u8*)(matrix[3] * M2C_FIELD(arg0, s32*, 0x29C) + matrix[0]), M2C_FIELD(arg0, s32*, 0x324));
    func_80027700(M2C_FIELD(arg0, s32**, 0x294), row, M2C_FIELD(arg0, s32*, 0x29C));
    M2C_FIELD(arg0, s32**, 0x3AC)[M2C_FIELD(arg0, s32*, 0x290)] = 1;
    M2C_FIELD(arg0, s32**, 0x3AC)[M2C_FIELD(arg0, s32*, 0x28C)] = M2C_FIELD(arg0, s32**, 0x3AC)[M2C_FIELD(arg0, s32*, 0x290)];
}

void func_89000048(void*);

void func_89005FD8(s8* arg0) {
    func_89000048(arg0 + 0x294);
    M2C_FIELD(arg0, s32**, 0x3AC)[M2C_FIELD(arg0, s32*, 0x28C)] = 1;
    M2C_FIELD(arg0, s32*, 0) = (((M2C_FIELD(arg0, s32*, 0x28C) == 0) ? 1 : 0) == M2C_FIELD(M2C_FIELD(arg0, s8**, 0x294), s32*, 8)) ? 1 : 4;
}


void func_89006054(s8 *arg0) {
    s32 temp_v0;
    s8 *temp_a0;

    temp_v0 = M2C_FIELD(arg0, s32 *, 0x248);
    temp_a0 = arg0 + 0x31C;
    M2C_FIELD(temp_a0, s32 *, -0x8C) = temp_v0;
    func_89004E1C(temp_a0, M2C_FIELD(arg0, s32 *, 0x3A8) + (temp_v0 * 0x10));
    M2C_FIELD(arg0, s32 *, 0) = 4;
}

#ifdef NON_MATCHING
/* TODO: decompile func_8900609C; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment015_238BD0/func_8900609C.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_890067B0; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment015_238BD0/func_890067B0.s")
#endif

M2C_UNK func_80002620(M2C_UNK);                     /* extern */

void func_890069C0(s32 arg0) {
    func_80002620(0x4F545043);
}

void func_8002C064(s32, s32, s32, s32, s32);
void func_89005AE0(void*);
void func_8002CAD0(void*);
void func_89007678(void*);
extern Color_RGB8 D_8900A5B8;

void func_890069E8(s32* arg0) {
    BgStage_DrawFrame();
    func_8002C064(0x38, 0x1E0, D_8900A5B8.r, D_8900A5B8.g, D_8900A5B8.b);
    switch (*arg0) {
        case 1:
            func_89005AE0(arg0 + 4);
            break;
        case 2:
            func_89005AE0(arg0 + 4);
            func_8002CAD0((u8*)arg0 + 0x408);
            break;
        case 3:
            func_89005AE0(arg0 + 4);
            func_89007678((u8*)arg0 + 0x46C);
            break;
        case 4:
            func_89005AE0(arg0 + 4);
            func_89007678((u8*)arg0 + 0x46C);
            break;
    }
}

M2C_UNK func_80023268(s32, u8, M2C_UNK);            /* extern */
extern s32 D_89019108;

void func_89006AB4(s8 *arg0) {
    s32 var_s1;
    u8 *var_s0;

    var_s0 = M2C_FIELD(arg0, u8 **, 0);
    var_s1 = 0;
    if (M2C_FIELD(arg0, s32 *, 8) > 0) {
        do {
            func_80023268(D_89019108, *var_s0, 3);
            var_s1 += 1;
            var_s0 += 0x50;
        } while (var_s1 < M2C_FIELD(arg0, s32 *, 8));
    }
}

#ifdef NON_MATCHING
/* TODO: decompile func_89006B2C; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment015_238BD0/func_89006B2C.s")
#endif

s32 func_89006CDC(s8* arg0) {
    s32 i;

    for (i = 0; i < 13; i++) {
        if (((s32*)(arg0 + 0x785C))[i] != 0) {
            return 1;
        }
    }
    return 0;
}

#ifdef NON_MATCHING
/* TODO: decompile func_89006D60; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment015_238BD0/func_89006D60.s")
#endif
