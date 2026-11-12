/* Stadium Zero fragment002_15E220. */

#include "global.h"
#include "m2c_macros.h"

s32 func_8000B2E8(void);
void func_8001AB6C(void);
void func_8001A384(s32, s32);
void func_8001AA60(s32, s32, s16);
void func_8001ABBC(void);
u32 func_800566BC(const char*);
extern s16 D_81200D20[];
extern s32 D_81200DA8;

void func_81200020(void) {
    s32 unused; // FAKE: stack padding
    s32 len;
    s32 x;
    s32 idx;
    s32 i;

    if (!(func_8000B2E8() & 1)) {
        len = func_800566BC((const char*)D_81200D20) >> 1;
        x = 16 - (D_81200DA8 % 16);
        idx = D_81200DA8 / 16;
        gDPSetScissor(gDisplayListHead++, G_SC_NON_INTERLACE, 16, 0, 304, 240);
        func_8001AB6C();
        func_8001A384(4, 0);
        for (i = 0; i < 19; i++) {
            func_8001AA60(x, 0xC0, D_81200D20[idx]);
            idx++;
            if (len - 1 < idx) {
                idx = 0;
            }
            x += 16;
        }
        func_8001ABBC();
        gDPSetScissor(gDisplayListHead++, G_SC_NON_INTERLACE, 0, 0, 320, 240);
        D_81200DA8++;
        if (D_81200DA8 >= len * 16) {
            D_81200DA8 = 0;
        }
    }
}

u32 osGetCount(void);
f32 MathUtil_Random_ZeroOne(void);
void func_80025758(s32, s32, s32);
extern u8 D_81200DAC[];

void func_81200190(void) {
    s32 temp_s0;
    s32 sp38;

    temp_s0 = osGetCount() & 0xFF;
    while (temp_s0-- > 0) {
        MathUtil_Random_ZeroOne();
    }

    temp_s0 = MathUtil_Random_ZeroOne() * 40.0f;
    do {
        sp38 = MathUtil_Random_ZeroOne() * 40.0f;
    } while (temp_s0 == sp38);

    func_80025758(3, D_81200DAC[temp_s0], D_81200DAC[sp38]);
}

extern char D_81200DE0[];
extern char D_81200DEC[];
extern char D_81200E18[];
extern char D_81200E24[];
extern char D_81200E50[];
extern char D_81200E70[];
extern char D_81200E9C[];
extern char D_81200EA8[];
extern char D_81200ED8[];
extern char D_81200EF0[];
extern char D_81200F10[];
extern char D_81200F1C[];
extern char D_81200F38[];
extern char D_81200F58[];
extern char D_81200F80[];
extern char D_81200F94[];
extern char D_81200FB8[];
extern char D_81200FDC[];
void func_8001AC7C(s32, s32, s32, s32, s32, s32, s32, s32);

void func_8120023C(s32 arg0) {
    s32 kind = (arg0 >> 8) & 0xFF;
    s32 pad[1]; // FAKE: stack padding

    if (kind != 0) {
        func_8001AC7C(0x1E, 0x5F, 0x104, 0x5F, 0, 0, 0, 0x96);
        Font_BeginTranslucentTextRendering();
        Font_SetActive(2, -2);
        switch (kind) {
            case 1:
                Font_Printf(0x32, 0x64, D_81200DE0, arg0 & 0xFF);
                Font_Printf(0x3C, 0x87, D_81200DEC);
                break;
            case 2:
                Font_Printf(0x32, 0x64, D_81200E18, arg0 & 0xFF);
                Font_Printf(0x3C, 0x7D, D_81200E24);
                Font_Printf(0x6E, 0x8C, D_81200E50);
                Font_Printf(0x41, 0xA5, D_81200E70);
                break;
            case 3:
                Font_Printf(0x32, 0x64, D_81200E9C, arg0 & 0xFF);
                Font_Printf(0x2D, 0x7D, D_81200EA8);
                Font_Printf(0x69, 0x96, D_81200ED8);
                Font_Printf(0x5A, 0xA5, D_81200EF0);
                break;
            case 4:
                Font_Printf(0x32, 0x64, D_81200F10, arg0 & 0xFF);
                Font_Printf(0x5F, 0x73, D_81200F1C);
                Font_Printf(0x50, 0x82, D_81200F38);
                Font_Printf(0x41, 0x9B, D_81200F58);
                Font_Printf(0x7D, 0xAA, D_81200F80);
                break;
            case 5:
                Font_Printf(0x46, 0x73, D_81200F94);
                Font_Printf(0x50, 0x82, D_81200FB8);
                Font_Printf(0x69, 0xA5, D_81200FDC);
                break;
        }
        Font_EndTexturedTextRendering();
    }
}

extern s32 D_81201010;
void func_8120047C(void) {
    u8* image = (u8*)D_81201010;
    s32 i;
    s32 j;

    gDPPipeSync(gDisplayListHead++);
    gDPSetCycleType(gDisplayListHead++, G_CYC_1CYCLE);
    gDPSetRenderMode(gDisplayListHead++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
    gDPSetTexturePersp(gDisplayListHead++, G_TP_NONE);
    gDPSetScissor(gDisplayListHead++, G_SC_NON_INTERLACE, 0, 0, 320, 240);
    gDPSetCombine(gDisplayListHead++, 0x17FE2F, 0x77FCF87C);
    gDPSetTextureConvert(gDisplayListHead++, G_TC_CONV);
    gDPSetConvert(gDisplayListHead++, G_CV_K0, G_CV_K1, G_CV_K2, G_CV_K3, G_CV_K4, G_CV_K5);
    gDPPipeSync(gDisplayListHead++);

    for (i = 0; i < 0xF0; i += 0x10) {
        for (j = 0; j < 0x140; j += 0x10) {
            gDPLoadTextureBlockYuv(gDisplayListHead++, image, G_IM_FMT_YUV, G_IM_SIZ_16b, 16, 16, 0,
                                G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK,
                                G_TX_NOLOD, G_TX_NOLOD);
            gSPTextureRectangle(gDisplayListHead++, j << 2, i << 2, (j + 0x10) << 2, (i + 0x10) << 2, G_TX_RENDERTILE,
                                0, 0, 0x0400, 0x0400);
            image += 0x200;
        }
    }

    gDPPipeSync(gDisplayListHead++);
    gDPSetTextureConvert(gDisplayListHead++, G_TC_FILT);
}

extern M2C_UNK D_02000000;
extern u8 D_020002C0[];
extern u8 D_02000580[];
extern u8 D_02000840[];
extern Gfx D_800602C8[];
extern Gfx D_80060398[];
extern s32 D_81201020;
void Gfx_DrawTextureIa16(s32 x1, s32 y1, s32 draw_width, s32 height, u8* texture, s32 load_width, s32 texture_spread_x_mode);

void func_812007B0(s16 x, s16 y) {
    s32 t = D_81201020 - 0x30;
    s32 alpha = 0;

    if (t >= 0) {
        if (t < 0x10) {
            alpha = t * 0x10;
        } else if (t < 0x23) {
            alpha = 0xFF;
        } else if (t < 0x32) {
            alpha = -t * 0x10 + 0x320;
        }
    }
    D_81201020++;
    if (D_81201020 >= 0x6D) {
        D_81201020 = 0x30;
    }
    gSPDisplayList(gDisplayListHead++, D_800602C8);
    gDPSetEnvColor(gDisplayListHead++, 0xFF, 0xFF, 0xFF, alpha);
    Gfx_DrawTextureIa16(x, y, 0x58, 4, (u8*)&D_02000000, 0x58, 0);
    Gfx_DrawTextureIa16(x, y + 4, 0x58, 4, D_020002C0, 0x58, 0);
    Gfx_DrawTextureIa16(x, y + 8, 0x58, 4, D_02000580, 0x58, 0);
    Gfx_DrawTextureIa16(x, y + 0xC, 0x58, 4, D_02000840, 0x58, 0);
    gSPDisplayList(gDisplayListHead++, D_80060398);
}

extern s32 D_81201018;
s32 func_81200970(s32 arg0)
{
  s32 var_v1_2;
  var_v1_2 = arg0 == 5;
  if (var_v1_2 == 0)
  {
    var_v1_2 = arg0 == 0;
    if (var_v1_2 == 0)
    {
      var_v1_2 = arg0 == 1;
      if (var_v1_2 == 0)
      {
        var_v1_2 = arg0 == 3;
      }
    }
  }
  var_v1_2 = var_v1_2 != 0;
  if (var_v1_2 != 0)
  {
    var_v1_2 = D_81201018 >= 0x10;
  }
  return var_v1_2;
}

s32 Audio_GetActivityScore(void);

s32 func_812009C4(s32 arg0) {
    s32 var_v1 = 0;

    if ((D_81201018 >= 0x259) && (Audio_GetActivityScore() == 0) && (func_81200970(arg0) != 0)) {
        var_v1 = 1;
    }
    return var_v1;
}

/*
 * func_81200A20
 *
 * Called by func_81200B80, which passes its address to func_800068DC
 * (what that does with it is not established, and neither is the meaning of
 * the screen).  Judging by its body it runs once per frame.  Returns 0, or a
 * result code: 0xF000, 0x8020 or 0x8010.
 *
 * Each call it runs the frame helpers (func_8000B1FC, func_8000B220) and
 * increments the frame counter D_81201018.  When `arg0` is 0 it reads the
 * input word func_8000D0DC(D_81201014); the upper halfword of that word is
 * the value tested and passed on below:
 *   - upper halfword == 0xA: Audio_FadeCategoriesAndStreams(0x10), result 0xF000;
 *   - otherwise, if bit 0x1000 or 0x8000 is set in the halfword at offset 8
 *     of the structure D_800603C0 points to (read here as controller
 *     buttons, not confirmed) and func_81200970(upper halfword) != 0:
 *     func_8003F6AC(0xF), result 0x8020;
 *   - otherwise, if the button test above failed and
 *     func_812009C4(upper halfword) != 0: func_81200190(), result 0x8010.
 * It then calls func_800069CC, func_8120047C and, when the low bit of
 * func_8000B2E8() is set, func_812007B0(0x74, 0xC0); then func_81200020
 * and func_8120023C(lower halfword of the input word).  A non-zero result
 * is reported with func_80006998 (0xFFFF for 0x8020, otherwise 1).
 *
 * Note for matching: the empty `if (!sp1C) {}` after func_8000B220 does
 * nothing at run time; decomp-permuter found that it changes the register
 * allocation to the ROM's.  It is not evidence of what the original source
 * looked like.
 */
void func_8000B1FC(void);
M2C_UNK func_8000B220();
s32 func_8000B2E8();
M2C_UNK func_800069CC();
M2C_UNK func_80006998(M2C_UNK);
s32 func_8000D0DC(s32);
M2C_UNK Audio_FadeCategoriesAndStreams(M2C_UNK);
M2C_UNK func_8003F6AC(M2C_UNK);
void func_81200020(void);
void func_8120023C(s32);
void func_812007B0(s16, s16);
extern void *D_800603C0;
extern s32 D_81201014;

s32 func_81200A20(s32 arg0) {
    s32 sp1C;
    s32 sp18;
    s32 temp_v0;

    sp1C = 0;
    sp18 = 0;
    func_8000B1FC();
    func_8000B220();
    if (!sp1C) {  // karodo
    }
    D_81201018 += 1;
    if (arg0 == 0) {
        temp_v0 = func_8000D0DC(D_81201014);
        sp18 = temp_v0;
        if (((temp_v0 >> 0x10) & 0xFFFF) == 0xA) {
            Audio_FadeCategoriesAndStreams(0x10);
            sp1C = 0xF000;
        } else if (M2C_FIELD(D_800603C0, u16 *, 8) & 0x9000) {
            if (func_81200970((sp18 >> 0x10) & 0xFFFF) != 0) {
                func_8003F6AC(0xF);
                sp1C = 0x8020;
            }
        } else if (func_812009C4((sp18 >> 0x10) & 0xFFFF) != 0) {
            func_81200190();
            sp1C = 0x8010;
        }
    }
    func_800069CC();
    func_8120047C();
    if (func_8000B2E8() & 1) {
        func_812007B0(0x74, 0xC0);
    }
    func_81200020();
    func_8120023C(sp18 & 0xFFFF);
    if (sp1C != 0) {
        if (sp1C == 0x8020) {
            func_80006998(0xFFFF);
        } else {
            func_80006998(1);
        }
    }
    return sp1C;
}

s32 func_800023C4(M2C_UNK, M2C_UNK);                /* extern */
M2C_UNK func_8000256C(M2C_UNK);                     /* extern */
M2C_UNK func_80002620(M2C_UNK);                     /* extern */
s32 func_80003EB8(u32, M2C_UNK *, M2C_UNK *, M2C_UNK); /* extern */
M2C_UNK func_80005040(M2C_UNK, M2C_UNK);            /* extern */
M2C_UNK func_800050AC();                            /* extern */
s32 func_8000645C(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, s32, s32); /* extern */
M2C_UNK func_80006680(s32);                         /* extern */
M2C_UNK func_800066C8();                            /* extern */
s32 func_800068DC(M2C_UNK *, M2C_UNK, M2C_UNK);     /* extern */
M2C_UNK func_8000A838(M2C_UNK);                     /* extern */
M2C_UNK func_8000D280();                            /* extern */
M2C_UNK func_8001A194(M2C_UNK, M2C_UNK);            /* extern */
M2C_UNK func_800407B0(M2C_UNK, M2C_UNK, M2C_UNK);   /* extern */
M2C_UNK Audio_LoadWaveTablesAndMusic(s32);                         /* extern */
M2C_UNK func_80044268();                            /* extern */
extern M2C_UNK D_002E0BE0;
extern M2C_UNK D_002E2B90;
extern M2C_UNK D_002EBCB0;
extern M2C_UNK D_002F0A50;
extern M2C_UNK D_01000000;
extern M2C_UNK D_02000000;
extern s32 D_81201010;
extern s32 D_81201014;
extern s32 D_81201018;
extern s32 D_8120101C;
extern s32 D_81201020;
s32 func_81200A20(s32);

s32 func_81200B80(s32 arg0, M2C_UNK arg1) {
    s32 sp24;
    s32 sp20;

    func_8000256C(0x5449544C);
    func_80005040(0x10000, 0);
    sp20 = func_8000645C(0, 1, 2, 0, 2, 1);
    func_8001A194(6, 0);
    func_80003EB8((u32) ((s32) &D_01000000 & 0x0F000000) >> 0x18, &D_002E0BE0, &D_002E2B90, 0);
    func_80003EB8((u32) ((s32) &D_02000000 & 0x0F000000) >> 0x18, &D_002EBCB0, &D_002F0A50, 0);
    D_81201014 = func_800023C4(0x4510, 0);
    D_8120101C = func_800023C4(0x100000, 0);
    D_81201010 = func_80003EB8(0U, &D_002E2B90, &D_002EBCB0, 0);
    D_81201018 = 0;
    D_81201020 = 0;
    Audio_LoadWaveTablesAndMusic(D_8120101C);
    func_80006680(sp20);
    sp24 = func_800068DC(&func_81200A20, 0x10, 0x10);
    func_800066C8();
    func_8000D280();
    func_8000A838(0);
    func_80044268();
    if (sp24 == 0x8080) {
        func_800407B0(0x3C, 0xA, 0);
    }
    func_800050AC();
    func_80002620(0x5449544C);
    return sp24;
}
