/* Stadium Zero fragment014_235D70. */
/* C ported from the Stadium 1 decomp: src/fragments/lab_pc/lab_pc_1B4EA0.c, src/fragments/lab_pc_icons/lab_pc_icons.c. */

#include "fragments/lab_pc_icons/lab_pc_icons.h"
#include "display_object_textures.h"
#include "poke_icon.h"
#include "graphics_textures.h"
#include "ui_graphics.h"
#include "gb_data.h"
#include "table_view.h"
#include "text_system.h"
#include "gb_save.h"
#include "jpeg_stream.h"
#include "audio_sfx.h"
#include "memmap.h"
#include "memory.h"
#include "stage_loader.h"
#include "util.h"
#include "fragments/widget_tree/widget_tree.h"
#include "fragments/pokemon_lab_support/pokemon_lab_support.h"
typedef struct unk_D_88605B00 {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
} unk_D_88605B00;

#include "fragments/lab_pc/lab_pc.h"
#include "graphics_textures.h"
#include "input.h"
#include "gb_data.h"
#include "pokemon_stats.h"
#include "save_data.h"
#include "game_state.h"
#include "table_view.h"
#include "text_system.h"
#include "gb_save.h"
#include "audio_sfx.h"
#include "hal_libc.h"
#include "memmap.h"
#include "memory.h"
#include "stage_loader.h"
typedef struct unk_D_88218060 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ Color_RGBA8* unk_04;
} unk_D_88218060;
typedef struct unk_D_88218070 {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ u8* unk_08;
    /* 0x0C */ s16 unk_0C;
    /* 0x10 */ Color_RGBA8* unk_10;
} unk_D_88218070;

#include "m2c_macros.h"

void func_8800075C(void);
void func_88000FE0(void);

#ifdef NON_MATCHING
/* TODO: decompile func_88000020; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment014_235D70/func_88000020.s")
#endif

extern Color_RGBA8 D_88001FD0;
void func_8002A0AC(s32, s32, s32, s32, Color_RGBA8);
void func_80027F20(s32);

void func_8800023C(s32 arg0, s32 arg1, char* arg2, s32 arg3, s32 arg4) {
    if (arg4 & 8) {
        func_8002A0AC(arg0 + 3, arg1 + 3, 0x162, 0x1E, D_88001FD0);
    }
    Font_BeginTranslucentTextRendering();
    func_80027F20(arg4);
    Font_SetActive(0x10, 0);
    Font_Printf(arg0 + 0xC, arg1 + 6, arg2);
    Font_EndTexturedTextRendering();
}

#ifdef NON_MATCHING
/* TODO: decompile func_880002D8; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment014_235D70/func_880002D8.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_880003D4; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment014_235D70/func_880003D4.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_88000564; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment014_235D70/func_88000564.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_880005E8; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment014_235D70/func_880005E8.s")
#endif

void func_8800075C(void) {
}

extern Gfx D_80073450[];
void func_800292A8(s32, s32, s32, s32, u8*);
/**
 * Appends a call of display list D_80073450, a gDPSetCombineMode(G_CC_MODULATEIA_PRIM,
 * G_CC_MODULATEIA_PRIM) and a white primitive colour with alpha arg5 to the current display
 * list, then forwards its first five arguments unchanged to func_800292A8 (compare
 * func_800295E8, which does the same with a decal combiner and no primitive colour).
 */
void func_88000764(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8* arg4, s32 arg5) {
    gSPDisplayList(gDisplayListHead++, D_80073450);
    gDPSetCombineMode(gDisplayListHead++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
    gDPSetPrimColor(gDisplayListHead++, 0, 0, 255, 255, 255, arg5);
    func_800292A8(arg0, arg1, arg2, arg3, arg4);
}

#ifdef NON_MATCHING
/* TODO: decompile func_880007FC; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment014_235D70/func_880007FC.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_88000C1C; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment014_235D70/func_88000C1C.s")
#endif

s32 func_88000E20(s8 *arg0) {
    s32 temp_v0;
    s32 var_v1;

    temp_v0 = M2C_FIELD(arg0, s32 *, 4);
    var_v1 = 1;
    if (temp_v0 >= 0x17) {
        M2C_FIELD(arg0, s32 *, 0) = 4;
        return 1;
    }
    if (temp_v0 >= 0xD) {
        M2C_FIELD(arg0, s32 *, 0) = 3;
        M2C_FIELD(arg0, s32 *, 4) = (s32) (temp_v0 + 1);
    } else if (temp_v0 < 0xA) {
        M2C_FIELD(arg0, s32 *, 0) = 0;
        M2C_FIELD(arg0, s32 *, 4) = (s32) (temp_v0 + 1);
    } else {
        var_v1 = 0;
        if (temp_v0 < 0xC) {
            M2C_FIELD(arg0, s32 *, 0) = 1;
            M2C_FIELD(arg0, s32 *, 4) = (s32) (temp_v0 + 1);
        } else {
            M2C_FIELD(arg0, s32 *, 0) = 2;
        }
    }
    return var_v1;
}

#ifdef NON_MATCHING
/* TODO: decompile func_88000EAC; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment014_235D70/func_88000EAC.s")
#endif

void func_88000FE0(void) {
}

#ifdef NON_MATCHING
/* TODO: decompile func_88000FE8; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment014_235D70/func_88000FE8.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_88001128; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment014_235D70/func_88001128.s")
#endif

s32 func_8002B390(s8*);
s32 func_8002BC14(s32);
extern s32 D_800603C0;

s32 func_8800125C(s8* arg0) {
    s32 ret = 0;

    switch (M2C_FIELD(arg0, s32*, 0x28)) {
        case 1:
        case 2:
            break;
        default:
            return 0;
    }
    if (func_8002B390(arg0 + 0xB4) == 0) {
        ret = func_8002BC14(D_800603C0);
        if (ret == 1) {
            switch (M2C_FIELD(arg0, s32*, 0xB8)) {
                case 0:
                    ret = 1;
                    break;
                case 1:
                    ret = -1;
                    break;
            }
        }
    }
    return ret;
}

extern Color_RGBA8 D_88002230;
void func_8002A8C4(s8* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

/**
 * Initialises the object arg0 (size and layout not established; same
 * family as func_82008524). Calls func_8002A8C4(arg0, arg1, arg2, 0x224, 0x60),
 * clears the words at 0x20, 0x24 and 0x28, sets the word at 0x14 to 0x2800,
 * copies the 4-byte colour D_88002230 to arg0 + 0x18, then stores arg3 at 0x20
 * (replacing the zero) and arg4 at 0x30.
 */
void func_880012FC(s8* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    func_8002A8C4(arg0, arg1, arg2, 0x224, 0x60);
    M2C_FIELD(arg0, s32*, 0x24) = 0;
    M2C_FIELD(arg0, s32*, 0x20) = 0;
    M2C_FIELD(arg0, s32*, 0x28) = 0;
    M2C_FIELD(arg0, s32*, 0x14) = 0x2800;
    M2C_FIELD(arg0, Color_RGBA8*, 0x18) = D_88002230;
    M2C_FIELD(arg0, s32*, 0x20) = arg3;
    M2C_FIELD(arg0, s32*, 0x30) = arg4;
}

s32 func_8002AE6C();
extern u8 D_800734A8[4];
void func_88001368(s8* arg0) {
    if (func_8002AE6C() == 0) {
        Font_BeginTranslucentTextRendering();
        Gfx_SetEnvColor(D_800734A8[0], D_800734A8[1], D_800734A8[2], D_800734A8[3]);
        Font_SetActive(8, 0);
        Font_SetLineHeight(0x1C);
        Font_Printf(M2C_FIELD(arg0, s32*, 0) + 0xA, M2C_FIELD(arg0, s32*, 4) + 0xA, M2C_FIELD(arg0, char**, 0x30));
        Font_EndTexturedTextRendering();
    }
}

M2C_UNK func_880002D8(s32, M2C_UNK, M2C_UNK);       /* extern */
M2C_UNK func_88000C1C(u8 *, s32, s32);            /* extern */
extern u8 D_800AF985;
extern M2C_UNK D_88002240;

/*
 * The caller func_8800187C passes a fourth argument, &D_88002B20, which this function
 * never reads. It is declared so that call compiles; the empty `if (arg3)` only stops
 * the compiler from spilling the unused argument, which the ROM does not do.
 */
void func_880013EC(u8 *arg0, s32 arg1, s32 arg2, s32 *arg3) {
    s32 temp_v0;

    if (arg3) {
    }

    if (D_800AF985 & 1) {
        func_880002D8(arg0 + 0x32C, 0x82, 0x6E);
        M2C_FIELD(arg0, s32 *, 0) = 1;
    } else {
        M2C_FIELD(arg0, s32 *, 0) = 2;
    }
    M2C_FIELD(arg0, s32 *, 4) = 0;
    func_88000C1C(arg0 + 0x2C, arg2, arg1);
    M2C_FIELD(arg0, s32 *, 0xC) = arg1;
    if (arg1 > 0) {
        temp_v0 = arg1 * 4;
        func_880012FC(arg0 + 0x2F8, 0x2E, 0x53, *((M2C_UNK*)((u8*)&D_88002230 + temp_v0)), *((M2C_UNK*)((u8*)&D_88002240 + temp_v0)));
    }
}

M2C_UNK func_800069CC();                            /* extern */
M2C_UNK func_8002C064(M2C_UNK, M2C_UNK, u8, u8, s32); /* extern */
M2C_UNK func_880003D4(s8 *);                      /* extern */
M2C_UNK func_88000EAC(s8 *, M2C_UNK);             /* extern */
M2C_UNK func_88001128(s8 *);                      /* extern */
extern M2C_UNK D_88002254;

void func_8800149C(s8 *arg0) {
    s32 temp_v0;

    func_800069CC();
    func_8002C064(0x38, 0x1E0, M2C_FIELD(&D_88002254, u8 *, 0), M2C_FIELD(&D_88002254, u8 *, 1), (s32) M2C_FIELD(&D_88002254, u8 *, 2));
    temp_v0 = M2C_FIELD(arg0, s32 *, 0);
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_88000EAC(arg0 + 0x2C, 0);
        func_880003D4(arg0 + 0x32C);
        return;
    case 2:
        func_88000EAC(arg0 + 0x2C, 2);
        if (M2C_FIELD(arg0, s32 *, 0xC) > 0) {
            func_88001368(arg0 + 0x2F8);
            return;
        }
        return;
    case 3:
        func_88000EAC(arg0 + 0x2C, 2);
        func_88001128(arg0 + 0x234);
        break;
    }
}

#ifdef NON_MATCHING
/* TODO: decompile func_88001564; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment014_235D70/func_88001564.s")
#endif

s32 func_80002D98(M2C_UNK);
M2C_UNK func_8000B2F4(s32);
s32 func_80022B4C(s32);
s32 func_80022F00(s32);
s32 func_80022EDC(s32);
s32 func_80025BD8();
M2C_UNK func_80027FF8(M2C_UNK *, s32);
extern s32 D_800603C0;
extern s32 D_80073400;
extern s32 D_88002B00;
extern M2C_UNK D_88002B08;
extern s32 D_88002B20;

/**
 * Allocates the 0x3B0-byte object stored in D_88002B20 and starts it with
 * func_880013EC. Steps:
 *  1. id = func_80025BD8(); D_88002B00 = id; if (D_88002B00 != -1) pass it with
 *     &D_88002B08 to func_80027FF8.
 *  2. Picks a mode from id: id == -1 -> 4; else func_80022B4C(id) != 0 -> 3;
 *     else func_80022F00(id) == 0 -> 2; else func_80022EDC(id) == 0 -> 1; else 0.
 *  3. D_88002B20 = func_80002D98(0x3B0), then
 *     func_880013EC(D_88002B20, mode, D_80073400 == 0 ? 4 : D_80073400 - 1, &D_88002B20)
 *     and finally func_8000B2F4(D_800603C0).
 * pad1/pad2 are unused locals that reproduce the retail 0x30-byte frame. What the id,
 * the modes and D_80073400 mean is not established.
 */
void func_8800187C(void) {
    s32 pad1;
    s32 pad2;
    s32 sp24;
    s32 var_s0;

    var_s0 = 0;
    sp24 = func_80025BD8();
    D_88002B00 = sp24;
    if (D_88002B00 != -1) {
        func_80027FF8(&D_88002B08, D_88002B00);
    }
    if (sp24 == -1) {
        var_s0 = 4;
    } else if (func_80022B4C(sp24) != 0) {
        var_s0 = 3;
    } else if (func_80022F00(sp24) == 0) {
        var_s0 = 2;
    } else if (func_80022EDC(sp24) == 0) {
        var_s0 = 1;
    }
    D_88002B20 = func_80002D98(0x3B0);
    func_880013EC(D_88002B20, var_s0, (D_80073400 == 0) ? 4 : D_80073400 - 1, &D_88002B20);
    func_8000B2F4(D_800603C0);
}

#ifdef NON_MATCHING
/* TODO: decompile func_8800196C; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment014_235D70/func_8800196C.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_88001A30; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment014_235D70/func_88001A30.s")
#endif

M2C_UNK func_800069CC();                            /* extern */
M2C_UNK func_8002C064(M2C_UNK, M2C_UNK, u8, u8, s32); /* extern */
extern M2C_UNK D_88002254;

s32 func_88001AE0(s32 arg0) {
    func_800069CC();
    func_8002C064(0, 0x1E0, M2C_FIELD(&D_88002254, u8 *, 0), M2C_FIELD(&D_88002254, u8 *, 1), (s32) M2C_FIELD(&D_88002254, u8 *, 2));
    return 0;
}

#ifdef NON_MATCHING
/* TODO: decompile func_88001B28; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment014_235D70/func_88001B28.s")
#endif

M2C_UNK func_800069CC();                            /* extern */
M2C_UNK func_80028060(M2C_UNK, M2C_UNK *, M2C_UNK *, s32); /* extern */
extern M2C_UNK D_88002A9C;
extern s32 D_88002B00;
extern M2C_UNK D_88002B08;

s32 func_88001BB4(s32 arg0) {
    M2C_UNK *var_a1;

    func_800069CC();
    if (D_88002B00 == -1) {
        var_a1 = NULL;
    } else {
        var_a1 = &D_88002B08;
    }
    func_80028060(0, var_a1, &D_88002A9C, D_88002B00);
    return 0;
}

M2C_UNK func_80005B98(M2C_UNK);                     /* extern */
M2C_UNK func_800069CC();                            /* extern */
M2C_UNK func_80028060(M2C_UNK, M2C_UNK *, M2C_UNK *, s32); /* extern */
M2C_UNK func_8002C064(M2C_UNK, M2C_UNK, u8, u8, s32); /* extern */
extern M2C_UNK D_88002254;
extern M2C_UNK D_88002AAC;
extern s32 D_88002B00;
extern M2C_UNK D_88002B08;
extern s32 D_88002B20;

s32 func_88001C08(s32 arg0) {
    M2C_UNK *var_a1;

    if (arg0 == 1) {
        func_80005B98(0xF);
    }
    func_800069CC();
    if (D_88002B00 == -1) {
        var_a1 = NULL;
    } else {
        var_a1 = &D_88002B08;
    }
    func_80028060(0, var_a1, &D_88002AAC, D_88002B00);
    func_8002C064(0x38, 0x1E0, M2C_FIELD(&D_88002254, u8 *, 0), M2C_FIELD(&D_88002254, u8 *, 1), (s32) M2C_FIELD(&D_88002254, u8 *, 2));
    func_88000EAC(D_88002B20 + 0x2C, 2);
    return 0;
}

M2C_UNK func_8000B1FC();                            /* extern */
M2C_UNK func_8000B220();                            /* extern */
M2C_UNK func_8001B5F0();                            /* extern */
s32 func_88001564(s32);                             /* extern */
extern s32 D_88002B20;

s32 func_88001CA4(s32 arg0) {
    s32 sp1C;

    sp1C = 0;
    func_8000B1FC();
    func_8000B220();
    func_8001B5F0();
    func_8800149C(D_88002B20);
    if (arg0 == 0) {
        sp1C = func_88001564(D_88002B20);
    }
    return sp1C;
}

M2C_UNK func_80002DC0(s32);                         /* extern */
extern s32 D_88002B20;

void func_88001D04(void) {
    func_80002DC0(D_88002B20);
}

extern s32 D_88002B20;

s32 func_88001D28(s32 arg0) {
    func_8800149C(D_88002B20);
    return 0;
}

M2C_UNK func_8000256C(M2C_UNK);                     /* extern */
M2C_UNK func_80002620(M2C_UNK);                     /* extern */
M2C_UNK func_80003EB8(u32, M2C_UNK *, M2C_UNK *, M2C_UNK); /* extern */
M2C_UNK func_80005B98(M2C_UNK);                     /* extern */
M2C_UNK func_80006724();                            /* extern */
M2C_UNK func_8000675C();                            /* extern */
s32 func_80006828(M2C_UNK, M2C_UNK *);              /* extern */
M2C_UNK func_80006998(M2C_UNK);                     /* extern */
M2C_UNK func_8000A7B0(M2C_UNK);                     /* extern */
M2C_UNK func_8000A7FC(M2C_UNK);                     /* extern */
M2C_UNK func_8001A194(M2C_UNK, M2C_UNK);            /* extern */
M2C_UNK func_8001A360();                            /* extern */
void func_8800187C(void);                          /* extern */
extern M2C_UNK D_002E0BE0;
extern M2C_UNK D_002E2B90;
extern M2C_UNK D_00400F70;
extern M2C_UNK D_004076E0;
extern M2C_UNK D_004199E0;
extern M2C_UNK D_01000000;
extern M2C_UNK D_04000000;
extern M2C_UNK D_05000000;
extern s32 D_80073400;
extern M2C_UNK func_88001A30;
extern M2C_UNK func_88001B28;

s32 func_88001D54(s32 arg0) {
    s32 sp1C;
    s32 temp_v0;

    func_8000256C(0x434F4D50);
    func_8001A194(0x18, 0);
    func_80003EB8((u32) ((s32) &D_01000000 & 0x0F000000) >> 0x18, &D_002E0BE0, &D_002E2B90, 0);
    func_80003EB8((u32) ((s32) &D_04000000 & 0x0F000000) >> 0x18, &D_00400F70, &D_004076E0, 0);
    func_80003EB8((u32) ((s32) &D_05000000 & 0x0F000000) >> 0x18, &D_004076E0, &D_004199E0, 0);
    func_8800187C();
    func_8000675C();
    if (arg0 == 1) {
        D_80073400 = 4;
        func_80006828(0x14, &func_88001A30);
        func_80006828(2, &func_88001AE0);
        func_80006828(6, &func_88001B28);
        func_80006828(2, &func_88001BB4);
    } else {
        func_80006828(0x11, &func_88001C08);
    }
    func_8000A7B0(9);
    temp_v0 = func_80006828(0, &func_88001CA4);
    sp1C = temp_v0;
    D_80073400 = M2C_FIELD(D_88002B20, s32 *, 0x3C) + 1;
    if (temp_v0 != 0x8040) {
        if (temp_v0 == 0x8050) {
            func_80006998(0xFFFF);
        } else {
            func_80006998(1);
        }
        func_80005B98(0xF);
        func_80006828(0x11, &func_88001D28);
        func_8000A7FC(0xF);
    } else {
        func_80006998(1);
    }
    func_80006724();
    func_88001D04();
    func_8001A360();
    func_80002620(0x434F4D50);
    return sp1C;
}

#ifdef NON_MATCHING
/* TODO: decompile func_88001F44; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment014_235D70/func_88001F44.s")
#endif
