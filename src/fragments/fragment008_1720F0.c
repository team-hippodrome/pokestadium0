/* Stadium Zero fragment008_1720F0. */

#include "global.h"
#include "m2c_macros.h"
#include "graphics_textures.h"

s32 func_800246A8(M2C_UNK, s32);                    /* extern */

s32 func_88100020(void) {
    s32 var_s0;

    var_s0 = 0;
loop_1:
    if (func_800246A8(0x10, var_s0) == 0) {
        return var_s0;
    }
    var_s0 += 1;
    if (var_s0 == 0x10) {
        return -1;
    }
    goto loop_1;
}

typedef struct Entry88100078 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ u8 unk_04[0x50];
} Entry88100078; // size = 0x54
s32 func_80020AFC(s32, s32, s32, s32);
s32 func_80020CE4(void*, s32, s32);
M2C_UNK func_80020C60(s32);
void func_88100078(s32 arg0, s32 arg1, s32 arg2, s32* arg3) {
    Entry88100078* entry = (Entry88100078*)arg3[0];
    s32 handle = func_80020AFC(arg0, arg1, arg2, 0);
    s32 i;

    for (i = 0; i < 6; i++, entry++) {
        if (func_80020CE4(entry->unk_04, 1, handle) == 0) {
            break;
        }
        entry->unk_00 = 0;
    }
    func_80020C60(handle);
    arg3[2] = i;
}

s32 func_80020B94(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, s8 *, s32); /* extern */
M2C_UNK func_80020C60(s32);                         /* extern */
s32 func_80020DF0(s32, M2C_UNK, s32);               /* extern */
// FAKE: decomp slop. Raw pointer-offset casts stand in for struct fields.
void func_88100100(s8 *arg0, M2C_UNK arg1)
{
  s32 temp_s3;
  s32 var_s0;
  s32 var_s1;
  var_s1 = *((s32 *) (((s8 *) arg0) + 0x18));
  if ((!arg0) && (!arg0))
  {
  }
  temp_s3 = func_80020B94(0x10, 0, arg1, 0, arg0 + 8, *((s32 *) (((s8 *) arg0) + 4)));
  var_s0 = 0;
  if ((*((s32 *) (((s8 *) arg0) + 0x20))) > 0)
  {
    loop_1:
    if (func_80020DF0(var_s1 + 4, 1, temp_s3) != 0)
    {
      var_s0 += 1;
      var_s1 += 0x54;
      if (var_s0 < (*((s32 *) (((s8 *) arg0) + 0x20))))
      {
        goto loop_1;
      }
    }

  }
  func_80020C60(temp_s3);
}

/*
 * func_881001A8
 *
 * arg0 points to a record whose first word is a pointer to an array of
 * pointers, with two counts at offsets 4 and 8. For each index i below the
 * count at offset 8, calls func_88100100(entries[i], i). Then, for the
 * remaining indices i up to the count at offset 4, calls
 * func_800245E0(0x10, i) when func_800246A8(0x10, i) is non-zero.
 *
 * What the record fields and the 0x10 argument mean is not established.
 * The separate `base` local reproduces the ROM's register copy (the array
 * pointer is loaded before the first count is tested).
 */
s32 func_800245E0(M2C_UNK, s32);
void func_881001A8(void *arg0) {
    s32 i;
    s8 **p;
    s8 **base;

    base = M2C_FIELD(arg0, s8 ***, 0);
    i = 0;
    if (M2C_FIELD(arg0, s32 *, 8) > 0) {
        p = base;
        do {
            func_88100100(*p, i);
            i++;
            p++;
        } while (i < M2C_FIELD(arg0, s32 *, 8));
    }
    for (; i < M2C_FIELD(arg0, s32 *, 4); i++) {
        if (func_800246A8(0x10, i) != 0) {
            func_800245E0(0x10, i);
        }
    }
}

s32 func_80024ADC(s32, s32);
void func_80027410(s8*, s8*, s32, s32, s32);
s32 func_800246C8(s32, s32);
void func_8002479C(s32, s32, u8*);
void func_8810024C(s8* arg0) {
    u8* p = M2C_FIELD(arg0, u8**, 0);
    s32 i;

    for (i = 0; i < 0x10; i++) {
        if (func_800246A8(0x10, i) == 0) {
            continue;
        }
        if (func_80024ADC(0x10, i) == 0) {
            continue;
        }
        p[0] = 0;
        p[1] = 0x10;
        p[2] = 0;
        p[3] = i;
        func_80027410((s8*)p + 0x18, (s8*)p + 0x28, 0x54, 6, 0);
        func_88100078(p[1], p[2], p[3], (s32*)(p + 0x18));
        M2C_FIELD(p, s32*, 4) = func_800246C8(p[1], p[3]);
        func_8002479C(p[1], p[3], p + 8);
        p += 0x220;
    }
    M2C_FIELD(arg0, s32*, 8) = (p - M2C_FIELD(arg0, u8**, 0)) / 0x220;
}

s32 func_80021894(s32);
s32 func_80022C70(s32);
void func_80022D84(s32, u8*);
void func_88100348(s8* arg0) {
    u8* p = M2C_FIELD(arg0, u8**, 0);
    s32 i;

    for (i = 0; i < 4; i++) {
        if (func_80021894(i) == 0) {
            continue;
        }
        p[0] = 0;
        p[1] = 0x20;
        p[2] = i;
        p[3] = 0;
        func_80027410((s8*)p + 0x18, (s8*)p + 0x28, 0x54, 6, 0);
        func_88100078(p[1], p[2], p[3], (s32*)(p + 0x18));
        M2C_FIELD(p, s32*, 4) = func_80022C70(p[2]);
        func_80022D84(p[2], p + 8);
        p += 0x220;
    }
    M2C_FIELD(arg0, s32*, 8) = (p - M2C_FIELD(arg0, u8**, 0)) / 0x220;
}

extern Color_RGBA8 D_88102D74;
void func_8002A0AC(s32, s32, s32, s32, Color_RGBA8);
void func_80027F20(s32);

void func_88100428(s32 arg0, s32 arg1, char* arg2, s32 arg3, s32 arg4, s32* arg5) {
    s32 temp_v0 = *arg5;

    if (arg4 & 0x10) {
        func_8002A0AC(arg0 + 3, arg1 + 3, temp_v0 - 6, 0x1A, D_88102D74);
    }
    Font_BeginTranslucentTextRendering();
    func_80027F20(arg4);
    Font_SetActive(0x10, 0);
    Font_Printf(arg0 + 8, arg1 + 4, arg2);
    Font_EndTexturedTextRendering();
}

void func_8002A8C4(s8* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
s32 func_800226BC(s32, s32, s32);
void func_80027804(s8*, s8*, s32, s32);
M2C_UNK func_8002D880(s8 *, s8 *, s8 *, M2C_UNK *, s32, s32);
extern s32 D_88103078;

void func_881004CC(s8* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, M2C_UNK* arg5, s32 arg6, M2C_UNK* arg7, s32 arg8, M2C_UNK* arg9) {
    s32 sp2C;

    func_8002A8C4(arg0, arg1, arg2, arg3, arg4);
    M2C_FIELD(arg0, s32 *, 0x28) = 0;
    M2C_FIELD(arg0, s32 *, 0x24) = 0;
    M2C_FIELD(arg0, s32 *, 0x14) = 0x801;
    M2C_FIELD(arg0, s32 *, 0x20) = (s32)arg9;
    func_80027804(arg0 + 0x50, (s8*)arg5, arg6, arg6);
    func_8002D880(arg0 + 0x2C, arg0 + 0x50, arg0 + 0x5C, (M2C_UNK*)func_88100428, arg3 - 0xC, 0x20);
    M2C_FIELD(arg0, s32 *, 0x4C) = (s32) (M2C_FIELD(arg0, s32 *, 0x4C) | 0x10000);
    M2C_FIELD(arg0, s32 *, 0x7C) = (s32)arg7;
    M2C_FIELD(arg0, s32 *, 0x80) = arg8;
    sp2C = func_88100020();
    if ((func_800226BC(0x20, D_88103078, 0) == 0) || (sp2C == -1)) {
        M2C_FIELD(M2C_FIELD(arg0, s8 **, 0x30), u16 *, 0) |= 1;
    }
    if (sp2C == 0) {
        M2C_FIELD(M2C_FIELD(arg0, s8 **, 0x30), u16 *, 2) |= 1;
        M2C_FIELD(M2C_FIELD(arg0, s8 **, 0x30), u16 *, 4) |= 1;
    }
}

typedef struct Color88100D9C {
    u8 c[4];
} Color88100D9C;
s32 func_8002AE6C();
void func_80029658(s32, s32, s32, void*);
void func_80029028(s32, s32, s32, s32, Color88100D9C);
void func_8002A550(s32, s32, s32, s32, Color88100D9C, Color88100D9C);
void func_8002D9B8(s8*, s32, s32, s32, s32);
extern u8 D_8007356C[];
extern u8 D_800734A8[4];
extern Gfx D_80060270[];
extern Color88100D9C D_88102D9C;
extern Color88100D9C D_88102DA0;
void func_881005E4(s8* arg0, s32 arg1) {
    UNUSED s32 pad;
    s32 sp38;
    s32 h;

    if (func_8002AE6C() == 0) {
        h = (M2C_FIELD(M2C_FIELD(arg0, s8**, 0x2C), s32*, 8) << 5) + 8;
        func_80029658(M2C_FIELD(arg0, s32*, 0), M2C_FIELD(arg0, s32*, 4) + h + 5, M2C_FIELD(arg0, s32*, 8), D_8007356C);
        gSPDisplayList(gDisplayListHead++, D_80060270);
        func_80029028(M2C_FIELD(arg0, s32*, 0) + 6, M2C_FIELD(arg0, s32*, 4) + 6, M2C_FIELD(arg0, s32*, 8) - 0xC, h, *(Color88100D9C*)&D_88102D74);
        func_8002A550(M2C_FIELD(arg0, s32*, 0) + 6, M2C_FIELD(arg0, s32*, 4) + h + 0xC, M2C_FIELD(arg0, s32*, 8) - 0xC, M2C_FIELD(arg0, s32*, 0x80) * 0x1C, D_88102D9C, D_88102DA0);
        sp38 = M2C_FIELD(arg0, s32*, 8) - 0xC;
        func_8002D9B8(arg0 + 0x2C, M2C_FIELD(arg0, s32*, 0) + 6, M2C_FIELD(arg0, s32*, 4) + 0xA, arg1 | 0xFFED, (s32)&sp38);
        Font_BeginTranslucentTextRendering();
        Gfx_SetEnvColor(D_800734A8[0], D_800734A8[1], D_800734A8[2], D_800734A8[3]);
        Font_SetActive(8, 0);
        Font_SetLineHeight(0x1C);
        Font_Printf(M2C_FIELD(arg0, s32*, 0) + 0xE, M2C_FIELD(arg0, s32*, 4) + h + 0x10, (*(char***)(arg0 + 0x7C))[M2C_FIELD(arg0, s32*, 0x34)]);
        Font_EndTexturedTextRendering();
    }
}

s32 func_8002DC04(s8*);
M2C_UNK func_8002BC14(s32);
M2C_UNK func_8003F6AC(M2C_UNK);
extern s32 D_800603C0;

/**
 * Menu-list input handler (same pattern as func_8A20093C and func_8200639C). Returns 0
 * immediately unless the word at arg0 + 0x28 is 1 or 2. Then, while func_8002DC04(arg0 + 0x2C)
 * is zero, reads the input result from func_8002BC14(D_800603C0): -1 plays sound
 * func_8003F6AC(3) and returns -1; 1 checks the halfword table at arg0 + 0x30 indexed by the
 * cursor word at arg0 + 0x34 -- if bit 0 of the entry is clear it plays sound 2 and returns
 * cursor + 1, otherwise it plays sound 8 and returns 0. Every other case returns 0.
 * (The meaning of the table bit is inferred from the sound choice only.)
 */
s32 func_881007AC(void* arg0) {
    s32 ret = 0;
    s32 dir;

    switch (M2C_FIELD(arg0, s32*, 0x28)) {
        case 1:
        case 2:
            break;
        default:
            return 0;
    }
    if (func_8002DC04((s8*)arg0 + 0x2C) == 0) {
        dir = func_8002BC14(D_800603C0);
        if (dir == -1) {
            func_8003F6AC(3);
            ret = -1;
        } else if (dir == 1) {
            if (!(M2C_FIELD(arg0, u16**, 0x30)[M2C_FIELD(arg0, s32*, 0x34)] & 1)) {
                func_8003F6AC(2);
                ret = M2C_FIELD(arg0, s32*, 0x34) + 1;
            } else {
                func_8003F6AC(8);
            }
        }
    }
    return ret;
}

void func_8002A8C4(s8* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
extern s32 D_800603C0;
typedef struct Win88100898 {
    s32 x; s32 y; s32 w; s32 h; s32 unk10; s32 unk14; s32 unk18; s32 unk1C;
    s32 unk20; s32 unk24; s32 unk28;
    char unk2C[0x2C];
    s32 unk58; s32 unk5C; s32 unk60; s32 unk64;
    char unk68[0x3C];
    s32 unkA4; s32 unkA8; s32 unkAC; s32 unkB0;
} Win88100898;
extern Color_RGBA8 D_88102DA4;
extern char D_88102F14[];
extern char D_88102F1C[];
void func_8002AE94(s8*, s32, s32, s32, Color_RGBA8, char*);
M2C_UNK func_8000B2F4(s32);
void func_88100898(s8* arg, s32 arg1, s32 arg2, s32 arg3) {
    Win88100898* arg0 = (Win88100898*)arg;
    func_8002A8C4(arg, arg1, arg2, 0x174, 0x66);
    arg0->unk24 = 0;
    arg0->unk20 = 0;
    arg0->unk28 = 0;
    arg0->unk14 = 0x1001;
    func_8002AE94((s8*)arg0->unk2C, arg0->x + 0x62, arg0->y + 0x42, 0x48, D_88102DA4, D_88102F14);
    arg0->unk58 = 0xA;
    arg0->unk60 = 0xC;
    func_8002AE94((s8*)arg0->unk68, arg0->x + 0xCA, arg0->y + 0x42, 0x48, D_88102DA4, D_88102F1C);
    arg0->unkAC = 2;
    arg0->unkA8 = 0;
    arg0->unkA4 = D_800603C0;
    func_8000B2F4(D_800603C0);
    arg0->unkB0 = arg3;
}

extern Gfx D_80060270[];
void func_80029028(s32, s32, s32, s32, Color88100D9C);

s32 func_8002AE6C();
extern u8 D_800734A8[4];
extern u8 D_8007356C[];
extern Color88100D9C D_88102DA8;
extern Color88100D9C D_88102DAC;
void func_80029658(s32, s32, s32, void*);
void func_8002A550(s32, s32, s32, s32, Color88100D9C, Color88100D9C);
void func_8002AF04(s8*, s32);

void func_881009A0(s8* arg0) {
    if (func_8002AE6C() == 0) {
        func_80029658(M2C_FIELD(arg0, s32*, 0), M2C_FIELD(arg0, s32*, 4) + 0x35, M2C_FIELD(arg0, s32*, 8), D_8007356C);
        func_8002A550(M2C_FIELD(arg0, s32*, 0) + 6, M2C_FIELD(arg0, s32*, 4) + 6, M2C_FIELD(arg0, s32*, 8) - 0xC, 0x30, D_88102DA8, D_88102DAC);
        gSPDisplayList(gDisplayListHead++, D_80060270);
        func_80029028(M2C_FIELD(arg0, s32*, 0) + 6, M2C_FIELD(arg0, s32*, 4) + 0x3C, M2C_FIELD(arg0, s32*, 8) - 0xC, 0x24, *(Color88100D9C*)&D_88102D74);
        Font_BeginTranslucentTextRendering();
        Gfx_SetEnvColor(D_800734A8[0], D_800734A8[1], D_800734A8[2], D_800734A8[3]);
        Font_SetActive(0x10, 0);
        Font_Printf(M2C_FIELD(arg0, s32*, 0) + 0x12, M2C_FIELD(arg0, s32*, 4) + 0x12, M2C_FIELD(arg0, char**, 0xB0));
        Font_EndTexturedTextRendering();
        func_8002AF04(arg0 + 0x2C, (M2C_FIELD(arg0, s32*, 0xA8) == 0) ? 2 : 0);
        func_8002AF04(arg0 + 0x68, (M2C_FIELD(arg0, s32*, 0xA8) == 1) ? 2 : 0);
    }
}

s32 func_8002B390(void*);
M2C_UNK func_8002BC14(s32);
extern s32 D_800603C0;
s32 func_88100B2C(s32 arg0) {
    s32 sp1C = 0;

    if (func_8002B390((u8*)arg0 + 0xA4) == 0) {
        sp1C = func_8002BC14(D_800603C0);
        if (sp1C == 1) {
            switch (M2C_FIELD(arg0, s32*, 0xA8)) {
                case 0:
                    sp1C = 1;
                    break;
                case 1:
                    sp1C = -1;
                    break;
            }
        }
    }
    return sp1C;
}

typedef struct Rgba88100BA4 {
    u8 r, g, b, a;
} Rgba88100BA4;

extern u8 D_88102DB0[];
extern u8 D_88102DB4[];
void func_8002A8C4(s8* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

void func_88100BA4(void* arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_8002A8C4((s8*)arg0, arg1, arg2, 0x170, 0x68);
    M2C_FIELD(arg0, s32*, 0x24) = 0;
    M2C_FIELD(arg0, s32*, 0x20) = 0;
    M2C_FIELD(arg0, s32*, 0x28) = 0;
    M2C_FIELD(arg0, s32*, 0x14) = 0x1006;
    M2C_FIELD(arg0, Rgba88100BA4*, 0x18) = *(Rgba88100BA4*)D_88102DB0;
    M2C_FIELD(arg0, Rgba88100BA4*, 0x1C) = *(Rgba88100BA4*)D_88102DB4;
    M2C_FIELD(arg0, s32*, 0x2C) = arg3;
}

s32 func_8002AE6C();
extern u8 D_800734A8[4];
void Gallery_AlbumDrawStatusText(s8* arg0) {
    u8* c;

    if (func_8002AE6C() == 0) {
        Font_BeginTranslucentTextRendering();
        c = D_800734A8;
        Gfx_SetEnvColor(c[0], c[1], c[2], c[3]);
        Font_SetActive(8, 0);
        Font_SetLineHeight(0x1C);
        Font_Printf(M2C_FIELD(arg0, s32*, 0) + 0xE, M2C_FIELD(arg0, s32*, 4) + 0xE, M2C_FIELD(arg0, char**, 0x2C));
        Font_EndTexturedTextRendering();
    }
}

M2C_UNK func_8002BC14(s32);                         /* extern */
extern s32 D_800603C0;

s32 func_88100CA8(s32 arg0) {
    return func_8002BC14(D_800603C0);
}


/**
 * Appends a call of display list D_80060270 to the current display list and
 * then calls func_80029028(arg0, arg1, 0x88, 0x64, arg2). arg0 and arg1 are
 * passed straight through (the retail code never touches $a0/$a1); arg2 is a
 * 4-byte colour passed by value.
 */
void func_88100CD0(s32 arg0, s32 arg1, Color88100D9C arg2) {
    gSPDisplayList(gDisplayListHead++, D_80060270);
    func_80029028(arg0, arg1, 0x88, 0x64, arg2);
}

/**
 * Appends a call of display list D_80060270 to the current display list and
 * then calls func_80029028(arg0 + 0x88, arg1, 0x18C, 0x64, arg2). arg1 is
 * passed straight through (the retail code never touches $a1); arg2 is a
 * 4-byte colour passed by value.
 */
void func_88100D30(s32 arg0, s32 arg1, Color88100D9C arg2) {
    gSPDisplayList(gDisplayListHead++, D_80060270);
    func_80029028(arg0 + 0x88, arg1, 0x18C, 0x64, arg2);
}

void func_88100D9C(s32 arg0, s32 arg1, Color88100D9C arg2) {
    gSPDisplayList(gDisplayListHead++, D_80060270);
    func_80029028(arg0, arg1, 0x214, 1, arg2);
    func_80029028(arg0, arg1 + 0x63, 0x214, 1, arg2);
}

extern Color88100D9C D_88102D7C;
extern u8 D_88102DB8[];
extern char D_88102F24[];
extern char D_88102F2C[];
extern Gfx D_80073450[];
extern u8 D_04010918[];
void func_8001BCB4(s32, s32, s32, s32, void*, s32, s32);
s32 func_80022BAC(u8);
void func_8002BC58(s32, s32, u8, s32);
void func_8002A3F8(u8*, s32, s32);
void func_8002BAB8(s32, s32, s32, s32);
void func_88100E34(s32 arg0, s32 arg1, s32 arg2, u8* arg3) {
    UNUSED s32 pad[3];

    gSPDisplayList(gDisplayListHead++, D_80060270);
    func_80029028(arg0, arg1, 0x88, 0x64, D_88102D7C);
    if (arg3[0] == 0) {
        if (arg3[1] == 0x20) {
            func_8002BC58(arg0 + 5, arg1 + 4, arg3[2], func_80022BAC(arg3[2]));
        } else if (arg3[1] == 0x10) {
            func_8002A3F8(D_88102DB8, arg0 + 4, arg1 + 4);
            Font_BeginTranslucentTextRendering();
            func_80027F20(arg2);
            Font_SetActive(8, 0);
            Font_Printf(arg0 + 0x1B, arg1 + 0x1A, D_88102F24, arg3[3] + 1);
            Font_EndTexturedTextRendering();
        }
    }
    Font_BeginTranslucentTextRendering();
    Gfx_SetEnvColor(0xFF, 0xC8, 0xC8, 0xFF);
    Font_SetActive(4, -1);
    Font_Printf(arg0 + 4, arg1 + 0x41, D_88102F2C);
    func_80027F20(arg2);
    Font_SetActive(4, 0);
    Font_Printf(arg0 + 0x38, arg1 + 0x41, (char*)(arg3 + 8));
    Font_EndTexturedTextRendering();
    if (M2C_FIELD(arg3, s32*, 4) != 0) {
        gSPDisplayList(gDisplayListHead++, D_80073450);
        gDPSetCombineMode(gDisplayListHead++, G_CC_DECALRGBA, G_CC_DECALRGBA);
        func_8001BCB4(arg0 + 0x25, arg1 + 0x56, 0x28, 0xA, D_04010918, 0x28, 0);
        func_8002BAB8(arg0 + 0x51, arg1 + 0x54, M2C_FIELD(arg3, s32*, 4), 5);
    }
}

extern Color88100D9C D_88102D78[2];
void func_8810105C(s32 x, s32 y, s32 height) {
    gSPDisplayList(gDisplayListHead++, D_80060270);
    func_80029028(x, y, 0x88, height, D_88102D78[1]);
    gSPDisplayList(gDisplayListHead++, D_80060270);
    func_80029028(x + 0x88, y, 0x18C, height, D_88102D78[0]);
}

#ifdef NON_MATCHING
/* TODO: decompile func_8810112C; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment008_1720F0/func_8810112C.s")
#endif

extern s32 D_88103074;
extern Gfx D_80073408[];
extern Gfx D_80073438[];
s32 func_80018DEC(s8*, s32);
void func_8001B884(s32, s32, s32, s32, u8*, s32, s32);
void func_8810137C(s32 arg0, s32 arg1) {
    gSPDisplayList(gDisplayListHead++, D_80060270);
    func_80029028(arg0, arg1, 0x84, 0x32, D_88102D78[0]);
    gSPDisplayList(gDisplayListHead++, D_80073408);
    func_8001B884(arg0 + 0x56, arg1 + 6, 0x28, 0x28, (u8*)func_80018DEC((s8*)D_88103074, 0x18), 0x28, 0x200000);
    gSPDisplayList(gDisplayListHead++, D_80073438);
}

extern Gfx D_80073450[];
extern u8 D_04011A60[];
void func_8001BCB4(s32, s32, s32, s32, void*, s32, s32);
void func_8002B940(s32, s32, s32, s32);
void func_88101478(s32 x, s32 y, u8* entry, s32 frame, s32 color, s32* anim) {
    s32 idx;

    gSPDisplayList(gDisplayListHead++, D_80060270);
    func_80029028(x, y, 0x84, 0x32, D_88102D78[0]);
    if (entry != NULL) {
        Font_BeginTranslucentTextRendering();
        func_80027F20(color);
        Font_SetActive(4, 0);
        Font_Printf(x + 4, y + 4, entry + 0x30);
        Font_EndTexturedTextRendering();
        gSPDisplayList(gDisplayListHead++, D_80073450);
        func_8001BCB4(x + 0x2C, y + 0x19, 8, 0xA, D_04011A60, 8, 0);
        func_8002B940(x + 0x38, y + 0x17, entry[0x24], 3);
        idx = frame % anim[2] + anim[1];
        gSPDisplayList(gDisplayListHead++, D_80073408);
        func_8001B884(x + 0x56, y + 6, 0x28, 0x28, (u8*)func_80018DEC((s8*)D_88103074, idx), 0x28, 0x200000);
        gSPDisplayList(gDisplayListHead++, D_80073438);
    }
}

void func_8810165C(s8 *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0) = 0;
    M2C_FIELD(arg0, s32 *, 4) = arg1;
    M2C_FIELD(arg0, s32 *, 8) = 0xF;
}

void func_88101670(s8 *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 4) = arg1;
    M2C_FIELD(arg0, s32 *, 8) = 0xF;
    M2C_FIELD(arg0, s32 *, 0) = (s32) (arg1 * 0xF);
}

// FAKE: decomp slop. Raw pointer-offset casts stand in for struct fields.
s32 func_88101690(s8 *arg0)
{
 if (0) { }  // karodo
  return (*((s32 *) (((s8 *) arg0) + 0))) >= ((*((s32 *) (((s8 *) arg0) + 4))) * (*((s32 *) (((s8 *) arg0) + 8))));
}

s32 func_881016B0(s32 *arg0) {
    return *arg0 == 0;
}

s32 func_881016BC(s8* arg0) {
    if (M2C_FIELD(arg0, s32*, 0) < M2C_FIELD(arg0, s32*, 4) * M2C_FIELD(arg0, s32*, 8)) {
        M2C_FIELD(arg0, s32*, 0) += 1;
    }
    return func_88101690(arg0);
}

s32 Audio_QueueSoundAvoidingRecent(s32* arg0) {
    if (*arg0 > 0) {
        *arg0 -= 1;
    }
    return func_881016B0(arg0);
}

s32 func_88101734(s32 *arg0) {
    return *arg0;
}

typedef struct IconCache8810173C {
    /* 0x00 */ s32* slots;
    /* 0x04 */ s32 base;
    /* 0x08 */ s32 count;
    /* 0x0C */ s32 start;
} IconCache8810173C; // size = 0x10
extern Color88100D9C D_88102D80;
extern s32 D_88103098[];
void func_8810112C(s32, s32, u8*, s32, s32, IconCache8810173C*);
void func_8810173C(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    u8* box = (u8*)arg2;
    s32 pad[2]; // FAKE
    IconCache8810173C cache;
    s32 pad2; // FAKE
    s32 i;
    u8* entry;
    s32 color;

    if (box != NULL) {
        func_88100E34(arg0, arg1, arg4, box);
        cache.slots = D_88103098;
        cache.base = 0;
        cache.count = 0x18;
        cache.start = arg3 * 6;
        entry = M2C_FIELD(box, u8**, 0x18);
        for (i = 0; i < M2C_FIELD(box, s32*, 0x20); i++, entry += 0x54) {
            color = 0;
            if (arg4 & 2) {
                color = 0x10000;
            }
            func_8810112C(arg0 + 0x88 + (i % 3) * 0x84, (i / 3) * 0x32 + arg1, entry + 4, arg3 * 6 + i, color, &cache);
        }
        for (; i < 6; i++) {
            color = 0;
            if (arg4 & 2) {
                color = 0x10000;
            }
            func_8810112C(arg0 + 0x88 + (i % 3) * 0x84, (i / 3) * 0x32 + arg1, NULL, arg3 * 6 + i, color, &cache);
        }
    } else {
        func_88100CD0(arg0, arg1, D_88102D7C);
        func_88100D30(arg0, arg1, D_88102D78[0]);
    }
    func_88100D9C(arg0, arg1, D_88102D80);
}

void func_88101A38(s32 arg0, s32 arg1, s8* arg2, s32 arg3, s32 arg4) {
    s32 pad[2]; // FAKE
    IconCache8810173C cache;
    s32 i;
    s32 n;
    u8* entry;

    entry = M2C_FIELD(arg2, u8**, 0x18);
    func_88100E34(arg0, arg1, 0, (u8*)arg2);
    cache.slots = D_88103098;
    cache.base = 0;
    cache.count = 0x18;
    cache.start = arg3 * 6;
    if (arg4 == 0) {
        n = 0;
    } else if (arg4 == 1) {
        n = M2C_FIELD(arg2, s32*, 0x20);
    } else {
        n = (arg4 - 2) / 15;
        if (n >= M2C_FIELD(arg2, s32*, 0x20)) {
            n = M2C_FIELD(arg2, s32*, 0x20);
        }
    }
    for (i = 0; i < n; i++, entry += 0x54) {
        func_88101478(arg0 + 0x88 + (i % 3) * 0x84, (i / 3) * 0x32 + arg1, entry + 4, arg3 * 6 + i, 0, (s32*)&cache);
    }
    for (; i < M2C_FIELD(arg2, s32*, 0x20); i++) {
        func_8810137C(arg0 + 0x88 + (i % 3) * 0x84, (i / 3) * 0x32 + arg1);
    }
    for (; i < 6; i++) {
        func_8810112C(arg0 + 0x88 + (i % 3) * 0x84, (i / 3) * 0x32 + arg1, NULL, i, 0, NULL);
    }
    func_88100D9C(arg0, arg1, D_88102D80);
}

/*
 * func_88101D7C
 *
 * Stores -1 into arg2 consecutive words of the s32 array arg0, starting at
 * index arg1 (indices arg1 .. arg1 + arg2 - 1). Does nothing when
 * arg1 + arg2 <= arg1, i.e. when arg2 is not positive. The compare is signed.
 * What the -1 entries mean is not established from this function.
 */
void func_88101D7C(s32* arg0, s32 arg1, s32 arg2) {
    s32 end;

    end = arg1 + arg2;
    for (; arg1 < end; arg1++) {
        arg0[arg1] = -1;
    }
}

void func_88101DB4(s8 *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0xBC) = arg1;
    switch (arg1) {                                 /* irregular */
    case 0:
        M2C_FIELD(arg0, s32 *, 4) = 0;
        return;
    case 1:
        M2C_FIELD(arg0, s32 *, 4) = 1;
        return;
    case 2:
        M2C_FIELD(arg0, s32 *, 4) = 2;
        return;
    }
}

extern M2C_UNK D_88102D84;
extern s32 D_88103098[];
void func_8810173C(s32, s32, s32, s32, s32, s32);
M2C_UNK func_8002EC24();
void func_88101DF8(s8 *arg0, s32 arg1, s32 arg2, s8 *arg3, s32 arg4) {
    func_8002A8C4(arg0 + 8, arg1, arg2, 0x220, 0x158);
    M2C_FIELD(arg0, s32 *, 0x2C) = 0;
    M2C_FIELD(arg0, s32 *, 0x28) = 0;
    M2C_FIELD(arg0, s32 *, 0x30) = 0;
    M2C_FIELD(arg0, s32 *, 0x1C) = 0x801;
    func_88101DB4(arg0, arg4);
    M2C_FIELD(arg0, s32 *, 0x28) = ((s32 *)&D_88102D84)[M2C_FIELD(arg0, s32 *, 0xBC)];
    M2C_FIELD(arg0, s8 **, 0xB8) = arg3;
    func_8002EC24(arg0 + 0x54, arg3, arg0 + 0x98, 3, func_8810173C, 0x214, 0x64);
    M2C_FIELD(arg0, s32 *, 0x74) |= 0x10000;
    M2C_FIELD(arg0, s32 *, 0) = 0;
    func_88101D7C(D_88103098, 0, 0x18);
}

typedef struct {
    /* 0x00 */ char unk00[0x8];
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ char unk10[0x44];
    /* 0x54 */ s32** tables;
    /* 0x58 */ char unk58[0x4];
    /* 0x5C */ s32 index;
} IndexedDrawer;

void func_8810173C(s32, s32, s32, s32, s32, s32);

/*
 * func_88101EC8
 *
 * Calls func_8810173C with the fields at +0x08 and +0x0C each increased by 6,
 * the entry at the current index (+0x5C) in the first table of arg0->tables,
 * that index, and two zero arguments.
 */
void func_88101EC8(IndexedDrawer* arg0) {
    s32 index = arg0->index;
    s32* entry = &(*arg0->tables)[index];

    func_8810173C(arg0->unk_08 + 6, arg0->unk_0C + 6, *entry, index, 0, 0);
}

void func_800189C0(s32, s32);
void func_800069CC(void);
void func_8002F3C4(s8*, s32, s32, s32, s32);
void func_88101A38(s32, s32, s8*, s32, s32);
void func_88100C24(s8*);
void func_88101F1C(s8* arg0) {
    func_800189C0(D_88103074, 0);
    func_800069CC();
    if (func_8002AE6C(arg0 + 8) == 0) {
        switch (M2C_FIELD(arg0, u32*, 4)) {
            case 0:
            case 1:
            case 2:
                func_8002F3C4(arg0 + 0x54, M2C_FIELD(arg0, s32*, 8) + 6, M2C_FIELD(arg0, s32*, 0xC) + 0x16, 0xFFFF, 0);
                break;
            case 3:
                func_88101EC8((IndexedDrawer*)arg0);
                func_8810105C(M2C_FIELD(arg0, s32*, 8) + 6, M2C_FIELD(arg0, s32*, 0xC) + 0x6A, 0x84);
                func_88101A38(M2C_FIELD(arg0, s32*, 8) + 6, M2C_FIELD(arg0, s32*, 0xC) + 0xEE, arg0 + 0xC0,
                              M2C_FIELD(arg0, s32*, 0x5C), 0);
                func_881009A0(arg0 + 0x310);
                break;
            case 4:
                func_88101EC8((IndexedDrawer*)arg0);
                func_8810105C(M2C_FIELD(arg0, s32*, 8) + 6, M2C_FIELD(arg0, s32*, 0xC) + 0x6A, 0x84);
                func_88101A38(M2C_FIELD(arg0, s32*, 8) + 6, M2C_FIELD(arg0, s32*, 0xC) + 0xEE, arg0 + 0xC0,
                              M2C_FIELD(arg0, s32*, 0x5C), func_88101734((s32*)(arg0 + 0x3C4)) + 0x10);
                break;
            case 5:
                func_88101EC8((IndexedDrawer*)arg0);
                func_8810105C(M2C_FIELD(arg0, s32*, 8) + 6, M2C_FIELD(arg0, s32*, 0xC) + 0x6A, 0x84);
                func_88101A38(M2C_FIELD(arg0, s32*, 8) + 6, M2C_FIELD(arg0, s32*, 0xC) + 0xEE, arg0 + 0xC0,
                              M2C_FIELD(arg0, s32*, 0x5C), 1);
                func_88100C24(arg0 + 0x2E0);
                break;
            case 6:
                func_88101A38(M2C_FIELD(arg0, s32*, 8) + 6, M2C_FIELD(arg0, s32*, 0xC) + 6, arg0 + 0xC0,
                              M2C_FIELD(arg0, s32*, 0x5C), 1);
                func_8810105C(M2C_FIELD(arg0, s32*, 8) + 6, M2C_FIELD(arg0, s32*, 0xC) + 0x6A, 0xE8);
                func_881009A0(arg0 + 0x310);
                break;
            case 7:
                func_88101A38(M2C_FIELD(arg0, s32*, 8) + 6, M2C_FIELD(arg0, s32*, 0xC) + 6, arg0 + 0xC0,
                              M2C_FIELD(arg0, s32*, 0x5C), func_88101734((s32*)(arg0 + 0x3C4)) + 2);
                func_8810105C(M2C_FIELD(arg0, s32*, 8) + 6, M2C_FIELD(arg0, s32*, 0xC) + 0x6A, 0xE8);
                break;
            case 8:
                func_88101A38(M2C_FIELD(arg0, s32*, 8) + 6, M2C_FIELD(arg0, s32*, 0xC) + 6, arg0 + 0xC0,
                              M2C_FIELD(arg0, s32*, 0x5C), 0);
                func_8810105C(M2C_FIELD(arg0, s32*, 8) + 6, M2C_FIELD(arg0, s32*, 0xC) + 0x6A, 0xE8);
                func_88100C24(arg0 + 0x2E0);
                break;
        }
    }
}

typedef struct Rec88102184 {
    s32 w[0x220 / 4];
} Rec88102184;
extern char D_88102F34[];
extern char D_88102F54[];
extern char D_88102F6C[];
extern char D_88102FC8[];
s32 func_8002FD8C(s8*);
void func_8003FE58(s32, s32, s32);
void func_80027868(s32, s32);

s32 func_88102184(s8* arg0) {
    s32 ret = 0;
    s32 res;
    Rec88102184* src;

    switch (M2C_FIELD(arg0, u32*, 4)) {
        case 0:
            if (func_8002FD8C(arg0 + 0x54) == 0) {
                res = func_8002BC14(D_800603C0);
                if (res == -1) {
                    func_8003F6AC(3);
                    ret = -1;
                } else if (res == 1) {
                    func_8003F6AC(2);
                    M2C_FIELD(arg0, u32*, 4) = 3;
                    func_88100898(arg0 + 0x310, M2C_FIELD(arg0, s32*, 8) + 0x56, M2C_FIELD(arg0, s32*, 0xC) + 0x79, (s32)D_88102F34);
                    *(Rec88102184*)(arg0 + 0xC0) = *(*M2C_FIELD(arg0, Rec88102184****, 0x54))[M2C_FIELD(arg0, s32*, 0x5C)];
                    M2C_FIELD(arg0, s8*, 0xC1) = 0x10;
                    M2C_FIELD(arg0, s8*, 0xC3) = func_88100020();
                }
            }
            break;
        case 1:
            if ((func_8002FD8C(arg0 + 0x54) == 0) && (func_8002BC14(D_800603C0) == -1)) {
                func_8003F6AC(3);
                ret = -1;
            }
            break;
        case 2:
            if (func_8002FD8C(arg0 + 0x54) == 0) {
                res = func_8002BC14(D_800603C0);
                if (res == -1) {
                    func_8003F6AC(3);
                    ret = -1;
                    func_881001A8(M2C_FIELD(arg0, void**, 0xB8));
                } else if (res == 1) {
                    func_8003F6AC(2);
                    *(Rec88102184*)(arg0 + 0xC0) = *(*M2C_FIELD(arg0, Rec88102184****, 0x54))[M2C_FIELD(arg0, s32*, 0x5C)];
                    func_88100898(arg0 + 0x310, M2C_FIELD(arg0, s32*, 8) + 0x56, M2C_FIELD(arg0, s32*, 0xC) + 0x79, (s32)D_88102F54);
                    M2C_FIELD(arg0, s32*, 0x3B8) = 1;
                    M2C_FIELD(arg0, u32*, 4) = 6;
                }
            }
            break;
        case 3:
            res = func_88100B2C((s32)(arg0 + 0x310));
            if (res == -1) {
                func_8003F6AC(3);
                M2C_FIELD(arg0, u32*, 4) = 0;
            } else if (res == 1) {
                func_8003F6AC(2);
                func_88100100((*M2C_FIELD(arg0, s8****, 0x54))[M2C_FIELD(arg0, s32*, 0x5C)], func_88100020());
                func_8810165C(arg0 + 0x3C4, M2C_FIELD(arg0, s32*, 0xE0));
                M2C_FIELD(arg0, u32*, 4) = 4;
            }
            break;
        case 4:
            if (M2C_FIELD(arg0, s32*, 0x3C4) % 15 == 0) {
                func_8003FE58(0x90, 1, 0);
            }
            if (func_881016BC(arg0 + 0x3C4) != 0) {
                func_8003F6AC(0x1E);
                func_88100BA4(arg0 + 0x2E0, M2C_FIELD(arg0, s32*, 8) + 0x58, M2C_FIELD(arg0, s32*, 0xC) + 0x78, (s32)D_88102F6C);
                M2C_FIELD(arg0, u32*, 4) = 5;
            }
            break;
        case 5:
            res = func_88100CA8((s32)(arg0 + 0x2E0));
            if ((res == -1) || (res == 1)) {
                func_8003F6AC(2);
                ret = -1;
            }
            break;
        case 6:
            res = func_88100B2C((s32)(arg0 + 0x310));
            if (res == -1) {
                func_8003F6AC(3);
                M2C_FIELD(arg0, u32*, 4) = 2;
            } else if (res == 1) {
                func_8003F6AC(2);
                func_88101670(arg0 + 0x3C4, M2C_FIELD(arg0, s32*, 0xE0));
                M2C_FIELD(arg0, u32*, 4) = 7;
            }
            break;
        case 7:
            if (M2C_FIELD(arg0, s32*, 0x3C4) % 15 == 0) {
                func_8003FE58(0x90, 1, 0);
            }
            if (Audio_QueueSoundAvoidingRecent((s32*)(arg0 + 0x3C4)) != 0) {
                func_8003F6AC(0x1F);
                func_80027868(M2C_FIELD(arg0, s32*, 0xB8), M2C_FIELD(arg0, s32*, 0x5C));
                func_881001A8(M2C_FIELD(arg0, void**, 0xB8));
                func_88100BA4(arg0 + 0x2E0, M2C_FIELD(arg0, s32*, 8) + 0x58, M2C_FIELD(arg0, s32*, 0xC) + 0x78, (s32)D_88102FC8);
                M2C_FIELD(arg0, u32*, 4) = 8;
            }
            break;
        case 8:
            res = func_88100CA8((s32)(arg0 + 0x2E0));
            if ((res == -1) || (res == 1)) {
                func_8003F6AC(2);
                ret = -1;
            }
            break;
    }
    return ret;
}

/*
 * func_881025C8
 *
 * Builds a table of pointers into a block of equally sized records.
 * arg1 holds the address of the first record at +0x00 and the record count
 * at +0x08.  arg0 holds the address of the pointer table at +0x00; entry i
 * is set to (first record + i * 0x220), so each record is 0x220 bytes.
 * The count is then copied to arg0 + 0x08.  What the records are is not
 * known from the code alone.
 *
 * func_820008C8 is the same routine with a record size of 0x214.
 */
void func_881025C8(s32* arg0, s32* arg1) {
    s32 value = arg1[0];
    s32* out = (s32*)arg0[0];
    s32 i = 0;

    if (arg1[2] > 0) {
        do {
            *out = value;
            i += 1;
            value += 0x220;
            out += 1;
        } while (i < arg1[2]);
    }
    arg0[2] = arg1[2];
}

void func_80027410(s8*, s8*, s32, s32, s32);
void func_80027804(s8*, s8*, s32, s32);
void func_8810024C(s8*);
void func_88101DF8(s8*, s32, s32, s8*, s32);
void func_881025C8(s32* arg0, s32* arg1);

void func_88102600(s32* arg0) {
    func_80027410((s8*)arg0 + 0x2698, (s8*)arg0 + 0x458, 0x220, 0x10, 0);
    func_8810024C((s8*)arg0 + 0x2698);
    func_80027804((s8*)arg0 + 0x26A8, (s8*)arg0 + 0x2658, 0x10, 0);
    func_881025C8((s32*)((s8*)arg0 + 0x26A8), (s32*)((s8*)arg0 + 0x2698));
    func_88101DF8((s8*)arg0 + 0x88, 0x30, 0x5C, (s8*)arg0 + 0x26A8, 1);
}

void func_80027410(s8*, s8*, s32, s32, s32);
void func_80027804(s8*, s8*, s32, s32);
void func_8810024C(s8*);
void func_88101DF8(s8*, s32, s32, s8*, s32);
void func_881025C8(s32* arg0, s32* arg1);

void func_88102688(s32* arg0) {
    func_80027410((s8*)arg0 + 0x2698, (s8*)arg0 + 0x458, 0x220, 0x10, 0);
    func_8810024C((s8*)arg0 + 0x2698);
    func_80027804((s8*)arg0 + 0x26A8, (s8*)arg0 + 0x2658, 0x10, 0);
    func_881025C8((s32*)((s8*)arg0 + 0x26A8), (s32*)((s8*)arg0 + 0x2698));
    func_88101DF8((s8*)arg0 + 0x88, 0x30, 0x5C, (s8*)arg0 + 0x26A8, 2);
}

void func_80027410(s8*, s8*, s32, s32, s32);
void func_80027804(s8*, s8*, s32, s32);
void func_88100348(s8*);
void func_88101DF8(s8*, s32, s32, s8*, s32);

void func_88102710(s32* arg0) {
    func_80027410((s8*)arg0 + 0x2698, (s8*)arg0 + 0x458, 0x220, 4, 0);
    func_88100348((s8*)arg0 + 0x2698);
    func_80027804((s8*)arg0 + 0x26A8, (s8*)arg0 + 0x2658, 4, 0);
    func_881025C8((s32*)((s8*)arg0 + 0x26A8), (s32*)((s8*)arg0 + 0x2698));
    func_88101DF8((s8*)arg0 + 0x88, 0x30, 0x5C, (s8*)arg0 + 0x26A8, 0);
}

s32 func_80025BD8();
M2C_UNK func_80027FF8(M2C_UNK *, s32);
void func_881004CC(s8*, s32, s32, s32, s32, M2C_UNK*, s32, M2C_UNK*, s32, M2C_UNK*);
extern M2C_UNK D_88102D84;
extern M2C_UNK D_88102D90;
extern M2C_UNK D_88103000;
extern s32 D_88103078;
extern M2C_UNK D_88103080;

/**
 * Stores the result of func_80025BD8() in D_88103078. If it is not -1, passes it with
 * &D_88103080 to func_80027FF8 (the value is re-read from D_88103078 after the store,
 * as the retail register allocation requires). Then restarts the sub-object at
 * arg0 + 4 with func_881004CC(arg0 + 4, 0x40, 0x74, 0x1AC, 0xCE, &D_88102D84, 3,
 * &D_88102D90, 3, &D_88103000) and sets the state word *arg0 to 0.
 * arg0 is declared s32 to agree with the existing func_88102794(s32) prototype; it is
 * used as a byte-addressed pointer. What the object and the value mean is not established.
 */
void func_88102794(s32 arg0) {
    D_88103078 = func_80025BD8();
    if (D_88103078 != -1) {
        func_80027FF8(&D_88103080, D_88103078);
    }
    func_881004CC((s8 *)arg0 + 4, 0x40, 0x74, 0x1AC, 0xCE, &D_88102D84, 3, &D_88102D90, 3, &D_88103000);
    *(s32 *)arg0 = 0;
}

void func_800069CC(void);
void func_8002C064(s32, s32, s32, s32, s32);
extern u8 D_88102D70[];
void func_881005E4(s8*, s32);
void func_88101F1C(s8*);
M2C_UNK func_88102834(s32 a) {
    s32* arg0 = (s32*)a;
    func_800069CC();
    func_8002C064(0x38, 0x1E0, D_88102D70[0], D_88102D70[1], D_88102D70[2]);
    switch (arg0[0]) {
        case 0:
            func_881005E4(arg0 + 1, 2);
            break;
        case 1:
            func_88101F1C((s8*)(arg0 + 0x22));
            break;
    }
}

/*
 * func_881028B8
 *
 * One step of a two-state routine on the object at address `arg0` (passed
 * as an integer); the first word of the object is the state.  Returns 1 when
 * finished, otherwise 0.
 *
 *   state 0: r = func_881007AC(arg0 + 4)
 *            r == -1: return 1
 *            r == 1:  func_88102710(arg0), state = 1
 *            r == 2:  func_88102600(arg0), state = 1
 *            r == 3:  func_88102688(arg0), state = 1
 *   state 1: if func_88102184(arg0 + 0x88) == -1, restart the sub-object
 *            with func_881004CC(arg0 + 4, 0x40, 0x74, 0x1AC, 0xCE,
 *            &D_88102D84, 3, &D_88102D90, 3, &D_8810300C) and set state 0.
 *
 * Offsets are byte offsets: `arg0 + 4` is the address four bytes in (the
 * m2c draft treated arg0 as an s32 pointer, which scales by four and does
 * not match).  What the states and helpers do is not established; the
 * helpers are still assembly.
 */
void func_881004CC(s8*, s32, s32, s32, s32, M2C_UNK*, s32, M2C_UNK*, s32, M2C_UNK*);
s32 func_881007AC(void *);
s32 func_88102184(s8*);
void func_88102600(s32 *);
void func_88102688(s32 *);
void func_88102710(s32 *);
extern M2C_UNK D_88102D84;
extern M2C_UNK D_88102D90;
extern M2C_UNK D_8810300C;

s32 func_881028B8(s32 arg0) {
    s32 sp3C;
    s32 temp_v0;
    s32 temp_v0_2;

    sp3C = 0;
    temp_v0 = *(s32 *)arg0;
    switch (temp_v0) {
    case 0:
        temp_v0_2 = func_881007AC((s8 *)arg0 + 4);
        if (temp_v0_2 == -1) {
            sp3C = 1;
        } else if (temp_v0_2 == 1) {
            func_88102710((s32 *)arg0);
            *(s32 *)arg0 = 1;
        } else if (temp_v0_2 == 2) {
            func_88102600((s32 *)arg0);
            *(s32 *)arg0 = 1;
        } else if (temp_v0_2 == 3) {
            func_88102688((s32 *)arg0);
            *(s32 *)arg0 = 1;
        }
        break;
    case 1:
        if (func_88102184((s8 *)arg0 + 0x88) == -1) {
            func_881004CC((s8 *)arg0 + 4, 0x40, 0x74, 0x1AC, 0xCE, &D_88102D84, 3, &D_88102D90, 3, &D_8810300C);
            *(s32 *)arg0 = 0;
        }
        break;
    }
    return sp3C;
}

s32 func_80002D98(s32);
void func_80018234(s32, s32, s32, s32);
void func_88102794(s32);
extern s32 D_88103074;
extern s32 D_881030F8;

/*
 * func_881029E0
 *
 * Setup step for this fragment: calls func_80002D98(0x26B4) (the symbol file
 * names that address Util_Malloc), keeps the result in D_881030F8, passes it
 * to func_88102794, then calls func_80018234(D_88103074, 0x18, 0x84, 0xF800).
 * What the 0x26B4-byte block holds and what func_88102794 does with it are
 * not established here (D_881030F8 is later passed to func_88102834 and
 * func_881028B8 by func_88102B58).
 * Matching note: the call result is stored straight into D_881030F8 and the
 * global is read back for the next call; going through a local gives a
 * different store sequence.
 */
void func_881029E0(void) {
    D_881030F8 = func_80002D98(0x26B4);
    func_88102794(D_881030F8);
    func_80018234(D_88103074, 0x18, 0x84, 0xF800);
}

typedef struct Col88102A2C { u8 r, g, b, a; } Col88102A2C;
extern s32 D_88102DCC;
extern s32 D_88102DD0;
/* Second name for D_88102DCC; see func_8A202F50 in lab_pc_icons.c. */
extern s32 D_88102DCC_2;
extern M2C_UNK D_88103018;
void func_800189C0(s32, s32);
M2C_UNK func_80028060(M2C_UNK, M2C_UNK *, M2C_UNK *, s32);
void func_8002C8D8(Col88102A2C*, Col88102A2C, f32);
s32 func_88102A2C(s32 arg0) {
    Col88102A2C sp2C;
    M2C_UNK *var_a1;
    s32 n;

    n = D_88102DCC;
    if (n >= 8) {
        D_88102DD0 = 1;
    }
    if (D_88102DD0 != 0) {
        n--;
        D_88102DCC_2 = n;
    }
    func_800189C0(D_88103074, 0);
    func_800069CC();
    if (D_88103078 == -1) {
        var_a1 = NULL;
    } else {
        var_a1 = &D_88103080;
    }
    func_80028060(0, var_a1, &D_88103018, D_88103078);
    n = D_88102DCC;
    func_8002C8D8(&sp2C, *(Col88102A2C*)D_88102D70, n / (f64)8.0f);
    func_8002C064(0x38, 0x1E0, sp2C.r, sp2C.g, sp2C.b);
    if (D_88102DD0 == 0) {
        n = D_88102DCC;
        n++;
        D_88102DCC = n;
    }
    return 0;
}

M2C_UNK func_8000B1FC();                            /* extern */
M2C_UNK func_8000B220();                            /* extern */
M2C_UNK func_88102834(s32);                         /* extern */
s32 func_881028B8(s32);
extern s32 D_881030F8;

void func_88102B58(s32 arg0) {
    func_8000B1FC();
    func_8000B220();
    func_88102834(D_881030F8);
    func_881028B8(D_881030F8);
}

M2C_UNK func_80002DC0(s32);                         /* extern */
extern s32 D_881030F8;

void func_88102B98(void) {
    func_80002DC0(D_881030F8);
}

M2C_UNK func_8000256C(M2C_UNK);
M2C_UNK func_80002620(M2C_UNK);
M2C_UNK func_80003EB8(u32, M2C_UNK *, M2C_UNK *, M2C_UNK);
M2C_UNK func_800040B4(s32, M2C_UNK *, M2C_UNK *);
M2C_UNK func_80006724();
M2C_UNK func_8000675C();
M2C_UNK func_80006828(M2C_UNK, void*);
s32 func_80017860(M2C_UNK);
M2C_UNK func_80017934();
s32 func_80017FDC(s32, M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK func_8001A194(M2C_UNK, M2C_UNK);
M2C_UNK func_80025BA0(s32, M2C_UNK *, M2C_UNK *, M2C_UNK, s32);
extern M2C_UNK D_0015B1A0;
extern M2C_UNK D_0015E220;
extern M2C_UNK D_00235D70;
extern M2C_UNK D_00238BD0;
extern M2C_UNK D_002E0BE0;
extern M2C_UNK D_002E2B90;
extern M2C_UNK D_00400F70;
extern M2C_UNK D_004076E0;
extern M2C_UNK D_004199E0;
extern M2C_UNK D_0042C4A0;
extern M2C_UNK D_01000000;
extern M2C_UNK D_04000000;
extern M2C_UNK D_05000000;
extern M2C_UNK D_81000000;
extern M2C_UNK D_88000000;
extern s32 D_88103070;
extern s32 D_88103074;
s32 func_88102BBC(s32 arg0, s32 arg1) {
    func_8000256C(0x52454753);
    func_8001A194(0x3C, 0);
    D_88103070 = func_80017860(1);
    D_88103074 = func_80017FDC(D_88103070, 0x19, 0x28, 0x28);
    func_80017934();
    func_800040B4(((u32)((s32)&D_81000000 & 0x0FF00000) >> 0x14) - 0x10, &D_0015B1A0, &D_0015E220);
    func_80003EB8((u32)((s32)&D_01000000 & 0x0F000000) >> 0x18, &D_002E0BE0, &D_002E2B90, 0);
    func_80003EB8((u32)((s32)&D_04000000 & 0x0F000000) >> 0x18, &D_00400F70, &D_004076E0, 0);
    func_80003EB8((u32)((s32)&D_05000000 & 0x0F000000) >> 0x18, &D_004199E0, &D_0042C4A0, 0);
    func_881029E0();
    func_8000675C();
    func_80006828(8, func_88102A2C);
    func_80006828(0, func_88102B58);
    func_80006828(8, func_88102A2C);
    func_80006724();
    func_88102B98();
    func_80002620(0x52454753);
    func_80025BA0(((u32)((s32)&D_88000000 & 0x0FF00000) >> 0x14) - 0x10, &D_00235D70, &D_00238BD0, 0, 0);
    return 0x8040;
}
