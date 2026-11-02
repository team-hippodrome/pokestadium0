/* Stadium Zero fragment019_293410. */
/* C ported from the Stadium 1 decomp: src/fragments/lab_pc_icons/lab_pc_icons.c. */

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

#include "m2c_macros.h"

s32 LabPC_ComputeExpForLevel(s32 arg0, s32 arg1);

typedef struct Entry80066AA0 {
    /* 0x00 */ const char* str;
    /* 0x04 */ u8 r, g, b, a;
} Entry80066AA0;
extern Entry80066AA0 D_80066AA0[];
extern Entry80066AA0 D_80066AA8;
s32 func_8001FA30(u8);
void func_8A200020(s32 arg0, s32 arg1, BattleMon* arg2) {
    Entry80066AA0* e;

    if (arg2->hp == 0) {
        e = &D_80066AA8;
    } else {
        e = &D_80066AA0[func_8001FA30(arg2->statusCondition)];
    }
    Gfx_SetEnvColor(e->r, e->g, e->b, 0xFF);
    Font_Printf(arg0, arg1, e->str);
}

extern M2C_UNK D_800734A8;
extern char D_8A21D850[];
extern char D_8A21D854[];
extern char D_8A21D858[];
void func_80027F20(s32);
void func_8A200020(s32, s32, BattleMon*);
void func_8A20009C(s32 arg0, s32 arg1, BattleMon* arg2, s32 arg3) {
    BattleHud_DrawHpBarTexture(arg0 + 0x16D, arg1 + 9, 0x94, arg2->hp, arg2->unk_26);
    Font_BeginTranslucentTextRendering();
    func_80027F20(arg3);
    Font_SetActive(0x10, 0);
    Font_Printf(arg0 + 0x4C, arg1 + 0xD, arg2->unk_30);
    Gfx_SetEnvColor(((u8*)&D_800734A8)[0], ((u8*)&D_800734A8)[1], ((u8*)&D_800734A8)[2], ((u8*)&D_800734A8)[3]);
    Font_SetActive(4, 0);
    Font_Printf(arg0 + 0x13B, arg1 + 6, D_8A21D850);
    Font_SetActive(8, 0);
    Font_Printf(arg0 + 0x11B, arg1 + 0x19, D_8A21D854, arg2->unk_24);
    Font_Printf(arg0 + 0x175, arg1 + 0x19, D_8A21D858, arg2->hp, arg2->unk_26);
    func_8A200020(arg0 + 0xD4, arg1 + 0x19, arg2);
    Font_EndTexturedTextRendering();
}

extern s8* D_8A21DA50;
void UI_DrawTextureRgba16(s32 arg0, s32 arg1, s32 arg2) {
    gSPDisplayList(gDisplayListHead++, D_80060290);

    Gfx_DrawTextureRgba16(arg0, arg1, 0x28, 0x28, M2C_FIELD(M2C_FIELD(M2C_FIELD(D_8A21DA50, s8**, 8) + arg2 * 0x14, s8**, 0xC), u8**, 8), 0x28, 0x200000);

    gSPDisplayList(gDisplayListHead++, gUiRestoreTextureDL);
}

#ifdef NON_MATCHING
/* TODO: decompile func_8A200274; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment019_293410/func_8A200274.s")
#endif

/*
 * func_8A20034C
 *
 * Initialises a record like func_8A1009E0 does: func_8002A8C4 fills the first
 * five words with (arg1, arg2, 0x221, 0x168, 0), the words at +0x20, +0x24
 * and +0x28 are cleared and +0x14 is set to 0x1001.  It then calls
 * func_8002D880 on the sub-object at arg0 + 0x2C with arg3, the area at
 * arg0 + 0x50, the callback func_8A200274 and the constants 0x215 and 0x33.
 * What func_8002D880 does is not established yet, so the roles of those
 * arguments are not named.
 */
M2C_UNK func_8002D880(s8 *, s32, s8 *, M2C_UNK *, s32, s32); /* extern */
extern M2C_UNK func_8A200274;

void func_8A20034C(s8 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_8002A8C4(arg0, arg1, arg2, 0x221, 0x168);
    M2C_FIELD(arg0, s32 *, 0x24) = 0;
    M2C_FIELD(arg0, s32 *, 0x20) = 0;
    M2C_FIELD(arg0, s32 *, 0x28) = 0;
    M2C_FIELD(arg0, s32 *, 0x14) = 0x1001;
    func_8002D880(arg0 + 0x2C, arg3, arg0 + 0x50, &func_8A200274, 0x215, 0x33);
}

#ifdef NON_MATCHING
/* TODO: decompile func_8A2003C0; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment019_293410/func_8A2003C0.s")
#endif

extern Color_RGBA8 D_8A203304;
void func_8002A0AC(s32, s32, s32, s32, Color_RGBA8);
void func_80027F20(s32);

void func_8A200770(s32 arg0, s32 arg1, char* arg2, s32 arg3, s32 arg4) {
    if (arg4 & 0x10) {
        func_8002A0AC(arg0 + 3, arg1 + 3, 0xA2, 0x1E, D_8A203304);
    }
    Font_BeginTranslucentTextRendering();
    func_80027F20(arg4);
    Font_SetActive(0x10, 0);
    Font_Printf(arg0 + 0xC, arg1 + 6, arg2);
    Font_EndTexturedTextRendering();
}

#ifdef NON_MATCHING
/* TODO: decompile func_8A20080C; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment019_293410/func_8A20080C.s")
#endif

s32 func_8002AB84();                                /* extern */
M2C_UNK func_8002D9B8(s8 *, s32, s32, M2C_UNK, s32); /* extern */

void func_8A2008F4(s8 *arg0) {
    if (func_8002AB84() == 0) {
        func_8002D9B8(arg0 + 0x2C, M2C_FIELD(arg0, s32 *, 0) + 6, M2C_FIELD(arg0, s32 *, 4) + 0xC, 0xFEF, 0);
    }
}

extern s8 *D_800603C0;
M2C_UNK func_8003F6AC(M2C_UNK);
s32 func_8002DC04(s8*);
s32 func_8002BC14(s32);
/**
 * Menu-list input handler (same pattern as func_8200639C / func_8900408C). Does nothing and
 * returns 0 while func_8002DC04(arg0 + 0x2C) is non-zero. Otherwise reads the input result
 * from func_8002BC14(D_800603C0): -1 returns -1; 1 looks at the entry for the cursor index
 * stored at arg0 + 0x34 in the halfword table pointed to by arg0 + 0x30 -- if bit 0 of that
 * entry is clear it returns index + 1, if set it plays sound effect func_8003F6AC(8) and
 * returns 0; any other result returns 0. (What the table bit means -- likely "disabled"
 * -- is inferred from the sound call only.)
 */
s32 func_8A20093C(s8* arg0) {
    s32 sp1C = 0;
    s32 dir;
    s32 idx;

    if (func_8002DC04(arg0 + 0x2C) == 0) {
        dir = func_8002BC14((s32)D_800603C0);
        if (dir == -1) {
            sp1C = -1;
        } else if (dir == 1) {
            idx = M2C_FIELD(arg0, s32*, 0x34);
            if (!(M2C_FIELD(arg0, u16**, 0x30)[idx] & 1)) {
                sp1C = idx + 1;
            } else {
                func_8003F6AC(8);
            }
        }
    }
    return sp1C;
}

#ifdef NON_MATCHING
/* TODO: decompile func_8A2009CC; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment019_293410/func_8A2009CC.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_8A200B78; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment019_293410/func_8A200B78.s")
#endif

typedef struct Color82000BC4 {
    u8 r, g, b, a;
} Color82000BC4;
typedef struct Entry80066AD8 {
    const char* str;
    Color82000BC4 color;
} Entry80066AD8;
extern Entry80066AD8 D_80066AD8[];
s32 func_8002D498(s32, s32);
void func_8001AB6C(void);
void func_8001A384(s32, s32);
void func_8001ABBC(void);
void func_8001AA9C(u8, u8, u8, u8);
void func_8001A944(s32, s32, const char*, ...);

void func_8A200D44(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    Color82000BC4 c;
    s32 idx = func_8002D498(arg3, arg4);

    if (idx != -1) {
        c = D_80066AD8[idx].color;
        func_8001AB6C();
        func_8001A384(arg2, 0);
        func_8001AA9C(c.r, c.g, c.b, c.a);
        func_8001A944(arg0, arg1, D_80066AD8[idx].str);
        func_8001ABBC();
    }
}

#ifdef NON_MATCHING
/* TODO: decompile func_8A200DE0; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment019_293410/func_8A200DE0.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_8A2010C8; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment019_293410/func_8A2010C8.s")
#endif

#ifdef NON_MATCHING
// Matches the ROM, but uses rodata data that is not placed in this file yet.
extern Gfx D_80060270[];
void func_80029028(s32, s32, s32, s32, Color_RGBA8);
void func_8001ABE8(void);
void func_8001AAE4(s32, s32, s32, s32);
void func_8001AC3C(void);
void func_8A201394(s32 arg0, s32 arg1, BattleMon* arg2) {
    gSPDisplayList(gDisplayListHead++, D_80060270);
    func_80029028(arg0, arg1, 0x122, 0x4E, D_8A203304);
    func_8001AB6C();
    func_8001AA9C(0xFF, 0xFF, 0xFF, 0xFF);
    func_8001ABE8();
    func_8001A384(0x10, 0);
    func_8001AAE4(0x5A, 0x6B, 0xFF, 0xFF);
    func_8001A944(arg0 + 0x25, arg1 + 0x1E, *(char**)D_80064C44[arg2->unk_00.unk_00]);
    func_8001AC3C();
    func_8001A384(8, 0);
    func_8001AA9C(((Color_RGBA8*)&D_800734A8)->r, ((Color_RGBA8*)&D_800734A8)->g, ((Color_RGBA8*)&D_800734A8)->b, ((Color_RGBA8*)&D_800734A8)->a);
    func_8001A944(arg0 + 9, arg1 + 6, "No.%03d", arg2->unk_00.unk_00);
    func_8001A944(arg0 + 0xC9, arg1 + 0x21, "L%d", arg2->unk_24);
    func_8001A384(4, 0);
    func_8001A944(arg0 + 9, arg1 + 0x3C, "タイプ");
    func_8001A944(arg0 + 0x4F, arg1 + 0x3C, "1/");
    if (func_8002D498((s32)arg2, 1) != -1) {
        func_8001A944(arg0 + 0xB9, arg1 + 0x3C, "2/");
    }
    func_8A200D44(arg0 + 0x6F, arg1 + 0x3C, 4, (s32)arg2, 0);
    func_8A200D44(arg0 + 0xD9, arg1 + 0x3C, 4, (s32)arg2, 1);
    func_8001ABBC();
}
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment019_293410/func_8A201394.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_8A201598; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment019_293410/func_8A201598.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_8A2018E0; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment019_293410/func_8A2018E0.s")
#endif

u8* func_800196F8(s32);
void func_800069CC(void);
void func_8001B884(s32, s32, s32, s32, u8*, s32, s32);
extern s32 D_8A21DA4C;
void func_8A201C08(s32 arg0, s32 arg1, s32 arg2) {
    u8* tex;
    s32 i;
    s32 n;

    tex = func_800196F8(D_8A21DA4C);
    func_800069CC();
    gSPDisplayList(gDisplayListHead++, D_80060290);
    gDPSetAlphaCompare(gDisplayListHead++, G_AC_NONE);
    for (i = 0; i < 0xD2; i += n) {
        if ((0xD2 - i) < 8) {
            n = 0xD2 - i;
        } else {
            n = 8;
        }
        func_8001B884(arg0, arg1 + i, 0xF4, n, tex, 0x100, 0x200000);
        tex += n << 9;
    }
    gSPDisplayList(gDisplayListHead++, gUiRestoreTextureDL);
}

#ifdef NON_MATCHING
/* TODO: decompile func_8A201D3C; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment019_293410/func_8A201D3C.s")
#endif

M2C_UNK func_80019008(s32, s32, M2C_UNK);           /* extern */
M2C_UNK func_80029658(s32, s32, s32, M2C_UNK *);    /* extern */
M2C_UNK func_80029864(s32, s32, s32, M2C_UNK *);    /* extern */
s32 func_8002AB84();                                /* extern */
M2C_UNK func_8A2009CC(s32, s32, s32);               /* extern */
M2C_UNK func_8A200B78(s32, s32, s32);               /* extern */
M2C_UNK func_8A200DE0(s32, s32, s32);               /* extern */
M2C_UNK func_8A2010C8(s32, s32, s32, s32);          /* extern */
void func_8A201394();
M2C_UNK func_8A2018E0(s32, s32, s32, s32);          /* extern */
void func_8A201C08(s32, s32, s32);
extern s8 D_8007356C;
extern s32 D_8A21DA4C;
void func_8A201EAC(s8 *arg0, s32 arg1)
{
  s32 temp_v0;
  if (((*((s32 *) (((s8 *) arg0) + 0x28))) != 2) && (func_8002AB84() == 0))
  {
    if (arg1 == 0)
    {
      func_80029864((*((s32 *) (((s8 *) arg0) + 0))) + 0xF9, *((s32 *) (((s8 *) arg0) + 4)), *((s32 *) (((s8 *) arg0) + 0xC)), &D_8007356C);
      func_80029658(*((s32 *) (((s8 *) arg0) + 0)), (*((s32 *) (((s8 *) arg0) + 4))) + 0xD7, 0x100, &D_8007356C);
      func_80029658((*((s32 *) (((s8 *) arg0) + 0))) + 0xFA, (*((s32 *) (((s8 *) arg0) + 4))) + 0x95, 0x12E, &D_8007356C);
      func_8A2009CC((*((s32 *) (((s8 *) arg0) + 0))) + 6, (*((s32 *) (((s8 *) arg0) + 4))) + 0xDE, *((s32 *) (((s8 *) arg0) + 0x2C)));
      func_8A200B78((*((s32 *) (((s8 *) arg0) + 0))) + 0x100, (*((s32 *) (((s8 *) arg0) + 4))) + 6, *((s32 *) (((s8 *) arg0) + 0x2C)));
      func_8A200DE0((*((s32 *) (((s8 *) arg0) + 0))) + 0x100, (*((s32 *) (((s8 *) arg0) + 4))) + 0x9C, *((s32 *) (((s8 *) arg0) + 0x2C)));
    }
    else
    {
      func_80029658(*((s32 *) (((s8 *) arg0) + 0)), (*((s32 *) (((s8 *) arg0) + 4))) + 0xD7, *((s32 *) (((s8 *) arg0) + 8)), &D_8007356C);
      func_80029864((*((s32 *) (((s8 *) arg0) + 0))) + 0xF9, *((s32 *) (((s8 *) arg0) + 4)), 0xDE, &D_8007356C);
      func_8A201394((*((s32 *) (((s8 *) arg0) + 0))) + 0x100, (*((s32 *) (((s8 *) arg0) + 4))) + 6, *((s32 *) (((s8 *) arg0) + 0x2C)));
      func_8A2010C8((*((s32 *) (((s8 *) arg0) + 0))) + 6, (*((s32 *) (((s8 *) arg0) + 4))) + 0xDE, *((s32 *) (((s8 *) arg0) + 0x2C)), *((s32 *) (((s8 *) arg0) + 0x30)));
      func_8A2018E0((*((s32 *) (((s8 *) arg0) + 0))) + 0x100, (*((s32 *) (((s8 *) arg0) + 4))) + 0x54, *((s32 *) (((s8 *) arg0) + 0x2C)), *((s32 *) (((s8 *) arg0) + 0x30)));
    }
  }
  temp_v0 = *((s32 *) (((s8 *) arg0) + 0x28));
  if (((temp_v0 ^ 0) == 1) || (temp_v0 == 2))
  {
    if ((*((s32 *) (((s8 *) arg0) + 0x34))) == 0)
    {
      *((s32 *) (((s8 *) arg0) + 0x34)) = 1;
      func_80019008(D_8A21DA4C, *((s32 *) (((s8 *) arg0) + 0x2C)), 0x108D);
    }
    func_8A201C08(0x32, 0x5A, *((s32 *) (((s8 *) arg0) + 0x2C)));
  }
}

s32 func_80022B40();                                /* extern */
s32 func_8002D454(s32, s32, s8 *);                /* extern */
M2C_UNK func_8003F6AC(M2C_UNK);                     /* extern */
extern s8 *D_800603C0;

s32 func_8A202078(s8 *arg0) {
    s32 var_s0;
    u16 temp_v0;

    var_s0 = -1;
    if (func_80022B40() != 0) {
        temp_v0 = M2C_FIELD(D_800603C0, u16 *, 8);
        if (temp_v0 & 8) {
            var_s0 = 0;
        } else if (temp_v0 & 1) {
            var_s0 = 1;
        } else if (temp_v0 & 4) {
            var_s0 = 2;
        } else if (temp_v0 & 2) {
            var_s0 = 3;
        }
        if (var_s0 >= 0) {
            if (func_8002D454(M2C_FIELD(arg0, s32 *, 0x2C), var_s0, arg0) == -1) {
                func_8003F6AC(8);
            } else {
                func_8003F6AC(2);
                M2C_FIELD(arg0, s32 *, 0x30) = var_s0;
                if (M2C_FIELD(arg0, s32 *, 0x28) <= 0) {
                    M2C_FIELD(arg0, s32 *, 0x24) = (s32) M2C_FIELD(arg0, s32 *, 0x24);
                } else {
                    M2C_FIELD(arg0, s32 *, 0x24) = 4;
                }
            }
        }
    }
    return var_s0 >= 0;
}

M2C_UNK func_8002C064(M2C_UNK, M2C_UNK, u8, u8, s32); /* extern */
extern M2C_UNK D_8A203300;

void func_8A202160(void) {
    func_8002C064(0x38, 0x1E0, M2C_FIELD(&D_8A203300, u8 *, 0), M2C_FIELD(&D_8A203300, u8 *, 1), (s32) M2C_FIELD(&D_8A203300, u8 *, 2));
}

s32 LabPC_ComputeExpForLevel(s32 arg0, s32 arg1) {
    s32 sp4;

    switch (gBaseStats[arg0].unk_13) {
        case 0:
            sp4 = arg1 * arg1 * arg1;
            break;

        case 1:
            sp4 = (((arg1 * arg1 * arg1 * 3) / 4) + (arg1 * 0xA * arg1)) - 0x1E;
            break;

        case 2:
            sp4 = (((arg1 * arg1 * arg1 * 3) / 4) + (arg1 * 0x14 * arg1)) - 0x1E;
            break;

        case 3:
            sp4 = ((((arg1 * arg1 * arg1 * 6) / 5) - (arg1 * 0xF * arg1)) + (arg1 * 0x64)) - 0x8C;
            break;

        case 4:
            sp4 = (arg1 * arg1 * arg1 * 4) / 5;
            break;

        case 5:
            sp4 = (arg1 * arg1 * arg1 * 5) / 4;
            break;
    }
    return sp4;
}

s32 func_80020AFC(M2C_UNK, s32, M2C_UNK, M2C_UNK);  /* extern */
M2C_UNK func_80020C60(s32);                         /* extern */
s32 func_80020CE4(s32, s32, s32);                   /* extern */
extern s32 D_8A21DA40;

void func_8A202390(s8 *arg0) {
    s32 sp1C;
    s32 sp18;
    s32 temp_v0;

    sp1C = M2C_FIELD(arg0, s32 *, 0);
    temp_v0 = func_80020AFC(0x20, D_8A21DA40, 0, 0);
    sp18 = temp_v0;
    M2C_FIELD(arg0, s32 *, 8) = func_80020CE4(sp1C, M2C_FIELD(arg0, s32 *, 4), temp_v0);
    func_80020C60(sp18);
}

void func_80022118(s32);
void func_80020DF0(s32, s32, s32);
s32 func_8002207C(s32);
void func_8002D7D4(s32);
void func_80022188(s32);
M2C_UNK func_8A20261C(M2C_UNK *);

void func_8A2023F4(s32* arg0, s32 arg1) {
    s32* sp2C;
    s32 i;
    s32 temp_s3;

    sp2C = (s32*)arg0[0];
    func_80022118(D_8A21DA40);
    temp_s3 = func_80020AFC(0x20, D_8A21DA40, 0, 1);

    for (i = 0; i < arg0[2]; i++) {
        func_80020DF0(sp2C[i], 1, temp_s3);
    }

    func_80020C60(temp_s3);
    if (func_8002207C(D_8A21DA40) == 0) {
        func_8002D7D4(D_8A21DA40);
        func_8A20261C((M2C_UNK*)arg1);
    }
    func_80022188(D_8A21DA40);
}

#ifdef NON_MATCHING
/* TODO: decompile func_8A2024D0; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment019_293410/func_8A2024D0.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_8A20261C; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment019_293410/func_8A20261C.s")
#endif

void func_8A202904(s8 *arg0, s32 arg1, s32 arg2) {
    M2C_FIELD(M2C_FIELD(arg0, s8 **, 8), s32 *, 0x24) = 7;
    M2C_FIELD(arg0, s32 *, 4) = arg1;
    M2C_FIELD(arg0, s32 *, 0xC) = arg2;
}

#ifdef NON_MATCHING
/* TODO: decompile func_8A20291C; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment019_293410/func_8A20291C.s")
#endif

extern s32 D_8A21DE08;
extern M2C_UNK D_8A21DE10;
extern M2C_UNK D_8A21DA80;
s32 func_80025BD8();
M2C_UNK func_80027FF8(M2C_UNK *, s32);
M2C_UNK func_8A2024D0(M2C_UNK *);

/**
 * Stores the result of func_80025BD8() in D_8A21DA40 and copies it to D_8A21DE08. If it
 * is not -1, passes it with &D_8A21DE10 to func_80027FF8. Then calls
 * func_8A2024D0(&D_8A21DA80). The copy is re-read from D_8A21DE08 for the compare and
 * call, as the retail register allocation requires. The meaning of the value is not
 * established.
 */
void func_8A202EF4(void) {
    D_8A21DA40 = func_80025BD8();
    D_8A21DE08 = D_8A21DA40;
    if (D_8A21DE08 != -1) {
        func_80027FF8(&D_8A21DE10, D_8A21DE08);
    }
    func_8A2024D0(&D_8A21DA80);
}

#ifdef NON_MATCHING
/* TODO: decompile func_8A202F50; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment019_293410/func_8A202F50.s")
#endif

M2C_UNK func_8000B1FC();                            /* extern */
M2C_UNK func_8000B220();                            /* extern */
M2C_UNK func_800158C0();                            /* extern */
M2C_UNK func_8001B5F0();                            /* extern */
M2C_UNK func_8A20261C(M2C_UNK *);                   /* extern */
M2C_UNK func_8A20291C(M2C_UNK *);                   /* extern */
extern M2C_UNK D_8A21DA80;

void func_8A203070(s32 arg0) {
    func_8000B1FC();
    func_8000B220();
    func_8001B5F0();
    func_800158C0();
    func_8A20261C(&D_8A21DA80);
    func_8A20291C(&D_8A21DA80);
}

extern u8 D_81000000[];
extern u8 D_0015B1A0[];
extern u8 D_0015E220[];
extern u8 D_01000000[];
extern u8 D_002E0BE0[];
extern u8 D_002E2B90[];
extern u8 D_04000000[];
extern u8 D_00400F70[];
extern u8 D_004076E0[];
extern u8 D_88000000[];
extern u8 D_00235D70[];
extern u8 D_00238BD0[];
extern u8 D_003DCB60[];
extern u8 D_003F53C0[];
extern u8 D_8A203438[];
extern ModelLoadContext* D_8A21DA48;
extern s32 D_8A21DA4C;
extern s8* D_8A21DA50;
extern BinArchive* D_8A21DA54;
extern void* D_8A21DA58;
extern void* D_8A21DA60[4];
void func_8A202EF4(void);
s32 func_8A202F50(u8);
void func_8A203070(s32 arg0);
s32 func_8A2030C0(UNUSED s32 arg0, UNUSED s32 arg1, UNUSED s32 arg2) {
    s32 i;

    main_pool_push_state('VIEW');
    Font_Init(0x1C, 0);
    D_8A21DA54 = BinArchive_Open(D_003DCB60, D_003F53C0, 1, 1);
    D_8A21DA48 = (ModelLoadContext*)PokeIcon_AllocFramebuffers(1);
    D_8A21DA4C = (s32)PokeIcon_CreateModelPreview(D_8A21DA48, 0x100, 0xD2, 0, 0, 0xF4, 0xD2, D_8A203438);
    D_8A21DA50 = (s8*)PokeIcon_CreateRenderList(D_8A21DA48, 6, 0x28, 0x28);
    PokeIcon_OpenModelArchives();

    Fragment_Load(((((u32)D_81000000) & 0x0FF00000) >> 0x14) - 0x10, D_0015B1A0, D_0015E220);
    Asset_LoadToSegment(((u32)D_01000000 & 0x0F000000) >> 0x18, D_002E0BE0, D_002E2B90, 0);
    Asset_LoadToSegment(((u32)D_04000000 & 0x0F000000) >> 0x18, D_00400F70, D_004076E0, 0);

    D_8A21DA58 = main_pool_alloc(0x3000, 0);
    for (i = 0; i < 4; i++) {
        D_8A21DA60[i] = main_pool_alloc(0x14800, 0);
    }

    func_8A202EF4();
    StageLoader_UpdateSegments();
    BgStage_RunUntilCondition(8, func_8A202F50);
    BgStage_RunUntilCondition(0, (s32 (*)(u8))func_8A203070);
    BgStage_RunUntilCondition(8, func_8A202F50);
    StageLoader_WaitForRetrace();
    Font_Free();
    main_pool_pop_state('VIEW');
    Fragment_QueueCall(((((u32)D_88000000) & 0x0FF00000) >> 0x14) - 0x10, D_00235D70, D_00238BD0, 0, 0);
    return 0x8040;
}
