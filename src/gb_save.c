/* Stadium Zero resident code. */
/* C ported from the Stadium 1 decomp: src/fragments/particle_math/particle_math_269820.c, src/gb_save.c. */

#include "gb_save.h"
#include "input.h"
#include "gb_data.h"
#include "pokemon_stats.h"
#include "save_data.h"
#include "game_state.h"
#include "audio_sfx.h"
#include "gfx_buffer.h"
#include "controller.h"
#include "memory.h"
#include "stage_loader.h"
extern u32 D_8007360C[];
extern u8 pad_D_80075944[];

#include "fragments/particle_math/particle_math.h"
#include "geo_render.h"
extern ParticleDescriptor gDefaultParticleDescriptor;

#include "m2c_macros.h"

void GbSave_BuildPortSummary(unk_func_8002D860* arg0, s32 arg1);
void Particle_SetVelocityXZFromRotationY(Particle* arg0);
s32 Ui_AdjustVerticalSelection(unk_func_8002DCB8_arg0* arg0, s32 arg1);
s32 Ui_HandleVerticalSelectionInput(s32 arg0);
s32 Ui_AdjustHorizontalSelection(unk_func_8002DD98_arg0* arg0, s32 arg1);
s32 Ui_HandleHorizontalSelectionInput(unk_func_8002DD98_arg0* arg0);
void Ui_AdjustSteppedScrollSelection(unk_func_8002DE78_arg0* arg0);
s32 Ui_HandleNumericSelectionInput(unk_func_8820E99C_030_030* arg0);
s32 Ui_AdjustSteppedRangeSelection(unk_func_8002E128_arg0* arg0);
s32 Ui_GetSelectionDirection(unk_func_8002EBD8_arg0* arg0);
Color_RGBA8 Color_InterpolateFromGray(Color_RGBA8 arg0, f32 arg1);

s32 Ui_AdjustNumericSelection(unk_func_8830867C_044_038_030* arg0, s32 arg1);
void Particle_Field50_SetXZFromField7C_09BB4(Particle* arg0);
void Particle_Field7C_SetXZFromField74AngleY_0B278(Particle* arg0);

M2C_UNK func_8001AA9C(u8, u8, u8, u8);              /* extern */
extern s8 D_800734A8;
extern s8 D_800734B0;
extern s8 D_800734B8;
void func_80027F20(s32 arg0)
{
  s8 *new_var;
  if (arg0 & 0x18)
  {
    new_var = &D_800734B8;
  }
  else
    if (arg0 & 1)
  {
    new_var = &D_800734B0;
    new_var = new_var;
  }
  else
  {
    new_var = &D_800734A8;
  }
  if (!(arg0 & 2))
  {
    new_var += 4;
  }
  new_var = (s8 *) new_var;
  func_8001AA9C(*((u8 *) (new_var + 0)), *((u8 *) (new_var + 1)), *((u8 *) (new_var + 2)), *((u8 *) (((s8 *) new_var) + 3)));
}

/*
 * func_80027F8C
 *
 * Picks one 4-byte entry and passes its four bytes to func_8001AA9C as four
 * byte-sized arguments.  The entry comes from one of three tables chosen by
 * the flags in arg0:
 *   - if any of bits 0x18 is set, from D_800734B8;
 *   - otherwise, if bit 0x01 is set, from D_800734C0;
 *   - otherwise from D_800734A8.
 * If bit 0x02 is clear the entry that follows (4 bytes further on) is used
 * instead.
 *
 * This is the same selection as func_80027F20 just above, except that bit
 * 0x01 selects D_800734C0 here and D_800734B0 there.  What the four bytes
 * mean is not established from the code (they look like colour components).
 */
extern s8 D_800734C0;
void func_80027F8C(s32 arg0) {
    u8* entry;

    if (arg0 & 0x18) {
        entry = (u8*)&D_800734B8;
    } else if (arg0 & 1) {
        entry = (u8*)&D_800734C0;
    } else {
        entry = (u8*)&D_800734A8;
    }
    if (!(arg0 & 2)) {
        entry += 4;
    }
    func_8001AA9C(entry[0], entry[1], entry[2], entry[3]);
}

void GbSave_BuildPortSummary(unk_func_8002D860* arg0, s32 arg1) {
    if (GbSave_GetSaveState(arg1) != 0) {
        arg0->unk_00 = 1;
    } else {
        arg0->unk_00 = 0;
        arg0->unk_08 = GbSave_GetTrainerId(arg1);
        GbSave_GetPlayerName(arg1, &arg0[1]);
    }
    arg0->unk_04 = GbSave_GetPortGame(arg1);
}

#ifdef NON_MATCHING
/* TODO: decompile func_80028060; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_80028060.s")
#endif

void func_80028C80(s32 width, s32 height, void* texture, s32 fmt) {
    gDPLoadTextureBlock(gDisplayListHead++, texture, fmt, G_IM_SIZ_8b, width, height, 0, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
}

void func_80028E5C(s32 width, s32 height, void* texture, s32 fmt) {
    gDPLoadTextureBlock(gDisplayListHead++, texture, fmt, G_IM_SIZ_16b, width, height, 0, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
}

void Trade_DrawSolidFillRect(s32 arg0, s32 arg1, s32 arg2, s32 arg3, Color_RGB8 arg4) {
    s32 color = RGBA5551(arg4.r, arg4.g, arg4.b, 1);

    gDPPipeSync(gDisplayListHead++);
    gDPSetFillColor(gDisplayListHead++, (color << 0x10) | color);
    gDPFillRectangle(gDisplayListHead++, arg0, arg1, (arg0 + arg2) - 1, (arg1 + arg3) - 1);
}

#ifdef NON_MATCHING
/* TODO: decompile func_800290F0; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_800290F0.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_800291F8; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_800291F8.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_800292A8; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_800292A8.s")
#endif

extern Gfx D_80073450[];
void func_800292A8(s32, s32, s32, s32, u8*);

/**
 * Appends a call of display list D_80073450 and a gDPSetCombineMode(
 * G_CC_DECALRGBA, G_CC_DECALRGBA) to the current display list, then forwards
 * all five arguments unchanged to func_800292A8.
 */
void func_800295E8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8* arg4) {
    gSPDisplayList(gDisplayListHead++, D_80073450);
    gDPSetCombineMode(gDisplayListHead++, G_CC_DECALRGBA, G_CC_DECALRGBA);
    func_800292A8(arg0, arg1, arg2, arg3, arg4);
}

#ifdef NON_MATCHING
/* TODO: decompile func_80029658; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_80029658.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_80029864; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_80029864.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_80029A64; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_80029A64.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_8002A0AC; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_8002A0AC.s")
#endif

/*
 * func_8002A32C
 *
 * Forwards its four arguments unchanged to func_800295E8 and adds a fifth
 * argument: the address of the data at D_80073524 (typed as a byte array).
 * func_8002A354 calls func_800295E8 the same way with D_8007353C as the
 * fifth argument.  What this data is, and what func_800295E8 does with it,
 * has not been determined, so the names are left as addresses.
 */
extern u8 D_80073524[];
void func_800295E8(s32, s32, s32, s32, u8*);
void func_8002A32C(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_800295E8(arg0, arg1, arg2, arg3, D_80073524);
}

typedef struct Color8002A354 {
    u8 c[4];
} Color8002A354;
extern Gfx D_80060270[];
extern u8 D_8007353C[];
void func_80029028(s32, s32, s32, s32, Color8002A354);
void func_800295E8(s32, s32, s32, s32, u8*);
void func_8002A354(s32 arg0, s32 arg1, s32 arg2, s32 arg3, Color8002A354 arg4) {
    gSPDisplayList(gDisplayListHead++, D_80060270);
    func_80029028(arg0 + 1, arg1 + 1, arg2 - 2, arg3 - 2, arg4);
    func_800295E8(arg0, arg1, arg2, arg3, D_8007353C);
}

#ifdef NON_MATCHING
/* TODO: decompile func_8002A3F8; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_8002A3F8.s")
#endif

extern u8 D_04000008[];
void func_8002A550(s32 x, s32 y, s32 w, s32 h, Color_RGBA8 prim, Color_RGBA8 env) {
    gDPPipeSync(gDisplayListHead++);
    gDPSetCycleType(gDisplayListHead++, G_CYC_1CYCLE);
    if (prim.a == 255) {
        gDPSetRenderMode(gDisplayListHead++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
    } else {
        gDPSetRenderMode(gDisplayListHead++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    }
    gDPSetCombineLERP(gDisplayListHead++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, PRIMITIVE, PRIMITIVE,
                      ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, PRIMITIVE);
    gDPSetTexturePersp(gDisplayListHead++, G_TP_NONE);
    gDPSetTextureFilter(gDisplayListHead++, G_TF_BILERP);
    gDPSetPrimColor(gDisplayListHead++, 0, 0, prim.r, prim.g, prim.b, prim.a);
    gDPSetEnvColor(gDisplayListHead++, env.r, env.g, env.b, env.a);
    gDPLoadTextureBlock(gDisplayListHead++, D_04000008, G_IM_FMT_I, G_IM_SIZ_8b, 64, 64, 0, G_TX_NOMIRROR | G_TX_WRAP,
                        G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    gSPTextureRectangle(gDisplayListHead++, x << 2, y << 2, (x + w) << 2, (y + h) << 2, G_TX_RENDERTILE, 0, 0,
                        (64 << 10) / w, (64 << 10) / h);
}

void func_8002A8C4(s8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4)
{
  s8 *new_var;
  *((s32 *) (((s8 *) arg0) + 0)) = arg1;
  *((s32 *) (((s8 *) arg0) + 4)) = arg2;
  new_var = arg0;
  *((s32 *) (((s8 *) arg0) + 8)) = arg3;
  *((s32 *) (((s8 *) new_var) + 0xC)) = arg4;
  *((s32 *) (((s8 *) arg0) + 0x10)) = 0;
}

#ifdef NON_MATCHING
/* TODO: decompile func_8002A8E0; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_8002A8E0.s")
#endif

/*
 * func_8002AAC4
 *
 * Advances a small step counter held in the object `arg0`: the counter is
 * the word at offset 0x24 and a second word at offset 0x28 receives a value
 * that depends on it.  Returns 1 or 0.
 *
 *   counter >= 11: word 0x28 = 4, return 1 (counter unchanged);
 *   counter >= 7:  word 0x28 = 3, counter + 1, return 1;
 *   counter <  4:  if counter == 0, func_8003F6AC(4, arg0) first (the
 *                  counter is re-read afterwards); then word 0x28 = 0,
 *                  counter + 1, return 1;
 *   counter 4, 5:  word 0x28 = 1, counter + 1, return 0;
 *   counter == 6:  word 0x28 = 2 (counter unchanged), return 0.
 *
 * What the counter measures is not established.
 */
M2C_UNK func_8003F6AC(M2C_UNK, void *);

s32 func_8002AAC4(void *arg0) {
    s32 var_v1;
    s32 var_v0;

    var_v0 = M2C_FIELD(arg0, s32 *, 0x24);
    var_v1 = 1;
    if (var_v0 >= 0xB) {
        M2C_FIELD(arg0, s32 *, 0x28) = 4;
        return 1;
    }
    if (var_v0 >= 7) {
        M2C_FIELD(arg0, s32 *, 0x28) = 3;
        M2C_FIELD(arg0, s32 *, 0x24) = (s32) (var_v0 + 1);
    } else if (var_v0 < 4) {
        if (var_v0 == 0) {
            func_8003F6AC(4, arg0);
            var_v1 = 1;
            var_v0 = M2C_FIELD(arg0, s32 *, 0x24);
        }
        M2C_FIELD(arg0, s32 *, 0x28) = 0;
        M2C_FIELD(arg0, s32 *, 0x24) = (s32) (var_v0 + 1);
    } else {
        var_v1 = 0;
        if (var_v0 < 6) {
            M2C_FIELD(arg0, s32 *, 0x28) = 1;
            M2C_FIELD(arg0, s32 *, 0x24) = (s32) (var_v0 + 1);
        } else {
            M2C_FIELD(arg0, s32 *, 0x28) = 2;
        }
    }
    return var_v1;
}

#ifdef NON_MATCHING
/* TODO: decompile func_8002AB84; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_8002AB84.s")
#endif

void Particle_SetVelocityXZFromRotationY(Particle* arg0) {
    Particle_Field7C_SetXZFromField74AngleY_0B278(arg0);
    Particle_Field50_SetXZFromField7C_09BB4(arg0);
}

/**
 * Initialises a text-box style object at arg0: stores the constants 0x14,
 * 8, 6, 2 and 0 at offsets 0x24..0x34, runs func_8002A8C4(arg0, arg1, arg2,
 * arg3, 0x18), then sets offset 0x14 to 1, offset 0x20 to the colour arg4
 * (a 4-byte struct passed by value, stored with unaligned stores) and offset
 * 0x38 to the string pointer arg5. What the fields mean is not established.
 */
void func_8002AE94(s8* arg0, s32 arg1, s32 arg2, s32 arg3, Color_RGBA8 arg4, char* arg5) {
    M2C_FIELD(arg0, s32*, 0x24) = 0x14;
    M2C_FIELD(arg0, s32*, 0x28) = 8;
    M2C_FIELD(arg0, s32*, 0x2C) = 6;
    M2C_FIELD(arg0, s32*, 0x30) = 2;
    M2C_FIELD(arg0, s32*, 0x34) = 0;
    func_8002A8C4(arg0, arg1, arg2, arg3, 0x18);
    M2C_FIELD(arg0, s32*, 0x14) = 1;
    M2C_FIELD(arg0, Color_RGBA8*, 0x20) = arg4;
    M2C_FIELD(arg0, char**, 0x38) = arg5;
}

#ifdef NON_MATCHING
/* TODO: decompile func_8002AF04; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_8002AF04.s")
#endif

/*
 * func_8002B018
 *
 * Calls func_8002A8C4(arg0, arg1, arg2, arg3, arg4), which fills the first
 * five words of the object (arg1, arg2, arg3, arg4, 0), then stores arg5 at
 * +0x24 and arg6 at +0x28.
 */
void func_8002B018(s8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    func_8002A8C4(arg0, arg1, arg2, arg3, arg4);
    M2C_FIELD(arg0, s32 *, 0x28) = arg6;
    M2C_FIELD(arg0, s32 *, 0x24) = arg5;
}

#ifdef NON_MATCHING
/* TODO: decompile func_8002B054; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_8002B054.s")
#endif

s32 Ui_AdjustVerticalSelection(unk_func_8002DCB8_arg0* arg0, s32 arg1) {
    s32 ret = 0;

    switch (arg1) {
        case 0x800:
            Audio_PlaySoundEffectById(SFX_MENU_SCROLL);
            if (arg0->unk_04 == 0) {
                arg0->unk_04 += arg0->unk_08;
            }
            arg0->unk_04--;
            ret = 1;
            break;

        case 0x400:
            Audio_PlaySoundEffectById(SFX_MENU_SCROLL);
            if (arg0->unk_04 >= (arg0->unk_08 - 1)) {
                arg0->unk_04 -= arg0->unk_08;
            }
            arg0->unk_04++;
            ret = 1;
            break;
    }

    return ret;
}

s32 Ui_HandleVerticalSelectionInput(s32 arg0) {
    s32 sp1C = Input_GetRepeatedDPad() & 0xFFFF;

    Ui_AdjustVerticalSelection(arg0, sp1C);
    return sp1C;
}

s32 Ui_AdjustHorizontalSelection(unk_func_8002DD98_arg0* arg0, s32 arg1) {
    s32 ret = 0;

    switch (arg1) {
        case 0x200:
            Audio_PlaySoundEffectById(SFX_MENU_SCROLL);
            if (arg0->unk_04 == 0) {
                arg0->unk_04 += arg0->unk_08;
            }
            arg0->unk_04--;
            ret = 1;
            break;

        case 0x100:
            Audio_PlaySoundEffectById(SFX_MENU_SCROLL);
            if (arg0->unk_04 >= (arg0->unk_08 - 1)) {
                arg0->unk_04 -= arg0->unk_08;
            }
            arg0->unk_04++;
            ret = 1;
            break;
    }

    return ret;
}

s32 Ui_HandleHorizontalSelectionInput(unk_func_8002DD98_arg0* arg0) {
    s32 sp1C = Input_GetRepeatedDPad() & 0xFFFF;

    Ui_AdjustHorizontalSelection(arg0, sp1C);
    return sp1C;
}

void Ui_AdjustSteppedScrollSelection(unk_func_8002DE78_arg0* arg0) {
    s32 temp_v0 = Input_GetRepeatedDPad();
    s32 sp18 = arg0->unk_0C;

    if (gPlayer1Controller->buttonDown & 0x2000) {
        sp18 = ((arg0->unk_08 - arg0->unk_04) + 1) / 10;
    }

    switch (temp_v0) {
        case 0x800:
            Audio_PlaySoundEffectById(SFX_MENU_SCROLL);
            if (arg0->unk_00 - sp18 < arg0->unk_04) {
                arg0->unk_00 = arg0->unk_04;
            } else {
                arg0->unk_00 -= sp18;
            }
            break;

        case 0x400:
            Audio_PlaySoundEffectById(SFX_MENU_SCROLL);
            if (arg0->unk_08 < arg0->unk_00 + sp18) {
                arg0->unk_00 = arg0->unk_08;
            } else {
                arg0->unk_00 += sp18;
            }
            break;
    }
}

s32 Ui_AdjustNumericSelection(unk_func_8830867C_044_038_030* arg0, s32 arg1) {
    s32 var_t1;
    s32 var_a2;
    s32 i;

    var_a2 = 1;

    for (i = arg0->unk_10; i > 0; i--) {
        var_a2 *= 10;
    }

    switch (arg1) {
        case 0x200:
            if (arg0->unk_10 + 1 < arg0->unk_0C) {
                arg0->unk_10 = arg0->unk_10 + 1;
            }
            Audio_PlaySoundEffectById(SFX_MENU_SCROLL);
            var_t1 = 1;
            break;

        case 0x100:
            if (arg0->unk_10 > 0) {
                arg0->unk_10--;
            }
            Audio_PlaySoundEffectById(SFX_MENU_SCROLL);
            var_t1 = 1;
            break;

        case 0x800:
            if (arg0->unk_00 == arg0->unk_08) {
                arg0->unk_00 = arg0->unk_00 - ((arg0->unk_00 / var_a2) * var_a2);
                if (arg0->unk_00 < arg0->unk_04) {
                    arg0->unk_00 = arg0->unk_04;
                }
            } else {
                arg0->unk_00 += var_a2;
                if (arg0->unk_08 < arg0->unk_00) {
                    arg0->unk_00 = arg0->unk_08;
                }
            }
            Audio_PlaySoundEffectById(SFX_MENU_SCROLL);
            var_t1 = 1;
            break;

        case 0x400:
            if (arg0->unk_00 == arg0->unk_04) {
                arg0->unk_00 = arg0->unk_08;
            } else {
                arg0->unk_00 -= var_a2;
                if (arg0->unk_00 < arg0->unk_04) {
                    arg0->unk_00 = arg0->unk_04;
                }
            }
            Audio_PlaySoundEffectById(SFX_MENU_SCROLL);
            var_t1 = 1;
            break;
    }
    return var_t1;
}

s32 Ui_HandleNumericSelectionInput(unk_func_8820E99C_030_030* arg0) {
    s32 sp1C = Input_GetRepeatedDPad() & 0xFFFF;

    Ui_AdjustNumericSelection(arg0, sp1C);
    return sp1C;
}

s32 Ui_AdjustSteppedRangeSelection(unk_func_8002E128_arg0* arg0) {
    s32 sp1C = Input_GetRepeatedDPad() & 0xFFFF;
    s32 sp18 = arg0->unk_0C;

    if (sp1C != 0) {
        Audio_PlaySoundEffectById(SFX_MENU_SCROLL);

        switch (sp1C) {
            case 0x200:
                sp18 *= 0xA;

            case 0x800:
                if (arg0->unk_00 >= arg0->unk_08) {
                    arg0->unk_00 = arg0->unk_04;
                } else if (arg0->unk_08 < (arg0->unk_00 + sp18)) {
                    arg0->unk_00 = arg0->unk_08;
                } else {
                    arg0->unk_00 = arg0->unk_00 + sp18;
                }
                break;

            case 0x100:
                sp18 *= 0xA;

            case 0x400:
                if (arg0->unk_04 >= arg0->unk_00) {
                    arg0->unk_00 = arg0->unk_08;
                } else if ((arg0->unk_00 - sp18) < arg0->unk_04) {
                    arg0->unk_00 = arg0->unk_04;
                } else {
                    arg0->unk_00 = arg0->unk_00 - sp18;
                }
                break;
        }
    }

    return sp1C;
}

#ifdef NON_MATCHING
/* TODO: decompile func_8002B788; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_8002B788.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_8002B940; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_8002B940.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_8002BAB8; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_8002BAB8.s")
#endif

s32 Ui_GetSelectionDirection(unk_func_8002EBD8_arg0* arg0) {
    s32 var_v1 = 0;

    if (arg0->unk_08 & 0x4000) {
        var_v1 = -1;
    } else if (arg0->unk_08 & 0x8000) {
        var_v1 = 1;
    }

    return var_v1;
}

/*
 * GbSave_GameToCategoryIndex  (owner func_8002BC44)
 *
 * Returns entry arg0 of a 12-word lookup table at D_80073644.  The retail
 * ROM holds { 0, 0, 1, 2, 0, 0, 0, 3, 0, 0, 0, 0 } there (checked against the
 * ROM bytes), the same table the Stadium 1 version of this function keeps as
 * a file-static array.  The table is referenced by its ROM address instead of
 * being defined here because this file's .data cannot be placed yet.
 * arg0 is not range-checked.
 */
extern s32 D_80073644[];
s32 GbSave_GameToCategoryIndex(s32 arg0) {
    return D_80073644[arg0];
}

#ifdef NON_MATCHING
/* TODO: decompile func_8002BC58; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_8002BC58.s")
#endif

extern u8 D_04009FB0[];
void func_8002BE24(s32 start, s32 end) {
    s32 row;
    s32 n;

    while (start < end) {
        row = start % 128;
        n = (128 - row > 32) ? 32 : 128 - row;
        if (n >= end - start) {
            n = end - start;
        }
        gDPLoadTextureBlock(gDisplayListHead++, D_04009FB0 + row * 128, G_IM_FMT_I, G_IM_SIZ_8b, 128, n, 0, G_TX_WRAP, G_TX_WRAP, 7, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        gSPTextureRectangle(gDisplayListHead++, 0, start << 2, 640 << 2, (start + n) << 2, G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);
        start += n;
    }
}

#ifdef NON_MATCHING
/* TODO: decompile func_8002C064; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_8002C064.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_8002C1B4; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_8002C1B4.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_8002C5A4; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_8002C5A4.s")
#endif

Color_RGBA8 Color_InterpolateFromGray(Color_RGBA8 arg0, f32 arg1) {
    static Color_RGBA8 D_80075940 = { 0xC8, 0xC8, 0xC8, 0xFF };

    Color_RGBA8 sp4;

    sp4.r = (s32)((arg0.r - D_80075940.r) * arg1) + D_80075940.r;
    sp4.g = (s32)((arg0.g - D_80075940.g) * arg1) + D_80075940.g;
    sp4.b = (s32)((arg0.b - D_80075940.b) * arg1) + D_80075940.b;
    sp4.a = arg0.a;

    return sp4;
}

extern Color_RGBA8 D_800736A8;
void func_8002A0AC(s32, s32, s32, s32, Color_RGBA8);

void BattleInfoWidget_DrawLabel(s32 arg0, s32 arg1, char* arg2, s32 arg3, s32 arg4) {
    if (arg4 & 0x18) {
        func_8002A0AC(arg0 + 3, arg1 + 3, 0xE6, 0x16, D_800736A8);
    }

    Font_BeginTranslucentTextRendering();
    func_80027F20(arg4);
    Font_SetActive(8, 0);
    Font_Printf(arg0 + 8, arg1 + 4, arg2);
    Font_EndTexturedTextRendering();
}

/*
 * func_8002CA34
 *
 * Initialises a record like func_8A1009E0 does, with the first five words
 * set by func_8002A8C4 to (arg1, arg2, 0xF8, 0xAE, 0), the words at +0x20,
 * +0x24 and +0x28 cleared and +0x14 set to 0x1001.  It then sets up two
 * sub-objects: func_80027804 is called on the area at arg0 + 0x50 with
 * D_800736AC, 3 and 3, and func_8002D880 on the object at arg0 + 0x2C with
 * that area, arg0 + 0x5C, the callback func_8002C998 and the constants 0xEC
 * and 0x1C.  Finally bit 0x10000 is set in the word at +0x4C.
 * What func_80027804 and func_8002D880 do is not established yet, so the
 * roles of those arguments are not named.
 */
M2C_UNK func_80027804(s8 *, M2C_UNK *, M2C_UNK, M2C_UNK); /* extern */
M2C_UNK func_8002D880(s8 *, s8 *, s8 *, M2C_UNK *, s32, s32); /* extern */
extern M2C_UNK D_800736AC;
extern M2C_UNK func_8002C998;

void func_8002CA34(s8 *arg0, s32 arg1, s32 arg2) {
    s8 *sp2C;
    s8 *temp_a0;

    func_8002A8C4(arg0, arg1, arg2, 0xF8, 0xAE);
    M2C_FIELD(arg0, s32 *, 0x24) = 0;
    M2C_FIELD(arg0, s32 *, 0x20) = 0;
    M2C_FIELD(arg0, s32 *, 0x28) = 0;
    M2C_FIELD(arg0, s32 *, 0x14) = 0x1001;
    temp_a0 = arg0 + 0x50;
    sp2C = temp_a0;
    func_80027804(temp_a0, &D_800736AC, 3, 3);
    func_8002D880(arg0 + 0x2C, sp2C, arg0 + 0x5C, &func_8002C998, 0xEC, 0x1C);
    M2C_FIELD(arg0, s32 *, 0x4C) = (s32) (M2C_FIELD(arg0, s32 *, 0x4C) | 0x10000);
}

#ifdef NON_MATCHING
/* TODO: decompile func_8002CAD0; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_8002CAD0.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_8002CC44; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_8002CC44.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_8002CD7C; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_8002CD7C.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_8002CE5C; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_8002CE5C.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_8002CEEC; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_8002CEEC.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_8002D024; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_8002D024.s")
#endif

s32 func_8002D138(UNUSED s32 arg0) {
    s32 ret = 0;

    if (gPlayer1Controller->buttonPressed & (BTN_A | BTN_B)) {
        ret = 1;
        Audio_PlaySoundEffectById(SFX_MENU_CONFIRM);
    }
    return ret;
}

#ifdef NON_MATCHING
/* TODO: decompile func_8002D188; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_8002D188.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_8002D2BC; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_8002D2BC.s")
#endif

s32 func_8002D3D0(u8* arg0) {
    s32 i;

    for (i = 0; i < 4; i++) {
        if (arg0[i + 9] == 0) {
            return i;
        }
    }
    return 4;
}

/*
 * func_8002D430
 *
 * Reads the byte at offset 9 of the record at (arg0 + arg1) and turns it
 * into a zero-based index:
 *    byte 0         -> -1
 *    byte 1..165    -> byte - 1      (0..164)
 *    byte >= 166    -> -2
 * i.e. the byte is a 1-based id with 165 valid values.  What the id
 * identifies has not been determined.
 */
s32 func_8002D430(s32 arg0, s32 arg1) {
    u8* p = (u8*)(arg0 + arg1);
    s32 id = p[9];
    s32 r;

    if (id >= 166) {
        r = -2;
    } else {
        r = id - 1;
    }
    return r;
}

s32 func_8002D3D0(u8*);
s32 func_8002D430(s32, s32);                        /* extern */

s32 func_8002D454(s32 arg0, s32 arg1) {
    if (arg1 >= func_8002D3D0((u8*)arg0)) {
        return -1;
    }
    return func_8002D430(arg0, arg1);
}

s32 func_8001FA8C(s32);

s32 func_8002D498(BattleMon* arg0, s32 arg1) {
    s32 idx = arg0->unk_00.unk_00 - 1;
    s32 type;

    if (arg1 == 1) {
        if (gSpeciesData[idx].type1 == gSpeciesData[idx].type2) {
            return -1;
        }
        type = gSpeciesData[idx].type2;
    } else {
        type = gSpeciesData[idx].type1;
    }
    return func_8001FA8C(type);
}

#ifdef NON_MATCHING
/* TODO: decompile func_8002D520; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_8002D520.s")
#endif

/*
 * func_8002D7D4
 *
 * Polling loop on arg0.  First func_80006780 (BgStage_AdvanceFrame, per
 * symbol_addrs.txt) is called once.  Then, repeatedly:
 *
 *   - state starts at 2.  func_8002D520(state) is called and
 *     func_80021B30(arg0) (GbSave_PollCartRemoval, per symbol_addrs.txt) is
 *     polled; if the poll returns 1 or 3, state becomes 1 or 3 for the next
 *     round.  This repeats until the poll returns 2.
 *   - func_8002D520(0) is called twice.
 *   - The whole sequence is repeated while func_8002207C(arg0)
 *     (GbSave_RebuildAndWriteSave) returns 0.
 *
 * What func_8002D520 does with its argument is not established, so the
 * values 1, 2 and 3 are not given names in the code.
 *
 * Context from the Stadium 1 decomp (not proof for this ROM): the same
 * loop exists there as LabUI_ShowSavingPrompt, where the polled function
 * GbSave_PollCartRemoval returns 0 when it has nothing to report yet, 1
 * while it waits for the cart to be put back, 2 once the pak is verified as
 * the same one, and 3 if a pak was reinitialised but is not the expected one; the loop
 * shows a saving-status message for the latest value.  Zero's loop differs in
 * detail (it never maps 2 to 0, and it calls func_8002D520(0) twice after the
 * inner loop instead of sending two null messages inside it).
 */
M2C_UNK func_80006780();                            /* extern */
s32 func_80021B30(s32);                             /* extern */
s32 func_8002207C(s32);                             /* extern */
M2C_UNK func_8002D520(M2C_UNK);                     /* extern */

void func_8002D7D4(s32 arg0) {
    s32 state;
    s32 result;

    func_80006780();
    do {
        state = 2;
        do {
            func_8002D520(state);
            result = func_80021B30(arg0);
            if (result == 1) {
                state = 1;
            } else if (result == 3) {
                state = 3;
            }
        } while (result != 2);
        func_8002D520(0);
        func_8002D520(0);
    } while (func_8002207C(arg0) == 0);
}
