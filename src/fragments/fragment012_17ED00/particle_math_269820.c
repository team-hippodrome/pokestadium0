/* Stadium Zero fragment012_17ED00. */
/* C ported from the Stadium 1 decomp: src/fragments/demo_scenes/demo_scenes_16A0E0.c, src/fragments/particle_math/particle_math_269820.c. */

#include "fragments/particle_math/particle_math.h"
#include "geo_render.h"
extern ParticleDescriptor gDefaultParticleDescriptor;

#include "fragments/demo_scenes/demo_scenes.h"
#include "geo_render.h"
#include "model_animation.h"
#include "geo_layout.h"
#include "display_object_textures.h"
#include "model_renderer.h"
#include "graphics_textures.h"
#include "input.h"
#include "text_system.h"
#include "jpeg_stream.h"
#include "audio_loop_point.h"
#include "gfx_buffer.h"
#include "gfx_rect.h"
#include "matrix.h"
#include "controller.h"
#include "memory.h"
#include "stage_loader.h"
#include "fragments/fragment012_17ED00/battle_engine_361050_2_types.h"
extern unk_D_86B10BE0 D_8219A82C;

#include "m2c_macros.h"

void Particle_SetFieldOffsetACIfNotSentinel(Particle* arg0, s16 arg1);
void Particle_SetFieldOffsetCFIfNotSentinel(Particle* arg0, u8 arg1);
void Particle_SetFieldOffsetA6IfNotSentinel(Particle* arg0, s16 arg1);
void Particle_SetFieldOffsetA8IfNotSentinel(Particle* arg0, s16 arg1);
void Particle_SetPrimAlphaIfNotSentinel(Particle* arg0, u8 arg1);
void Particle_SetFieldOffsetAAIfNotSentinel(Particle* arg0, s16 arg1);
s16 Particle_FieldAA_GetS16_0C068(Particle* arg0);
s16 Particle_GetUnkAA(Particle* arg0);
void FirstClearBonus_HideDialogBox(void);

void Particle_SetPrimAlpha(s8 *arg0, char arg1);
void Particle_FieldA6_SetS16_0BCA8(Particle* arg0, s16 arg1);
void Particle_FieldA8_SetS16_0BE14(Particle* arg0, s16 arg1);
void Particle_FieldAC_SetS16_0BED8(Particle* arg0, s16 arg1);
void Particle_FieldCF_SetU8_0BEEC(Particle* arg0, u8 arg1);

/**
 * Store the parameter only when it differs from the field-specific sentinel.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void Particle_SetFieldOffsetACIfNotSentinel(Particle* arg0, s16 arg1) {
    if ((u32)arg0 != -1) {
        Particle_FieldAC_SetS16_0BED8(arg0, arg1);
    }
}

/**
 * Store the parameter only when it differs from the field-specific sentinel.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void Particle_SetFieldOffsetCFIfNotSentinel(Particle* arg0, u8 arg1) {
    if ((u32)arg0 != -1) {
        Particle_FieldCF_SetU8_0BEEC(arg0, arg1);
    }
}

/**
 * Store the parameter only when it differs from the field-specific sentinel.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void Particle_SetFieldOffsetA6IfNotSentinel(Particle* arg0, s16 arg1) {
    if ((u32)arg0 != -1) {
        Particle_FieldA6_SetS16_0BCA8(arg0, arg1);
    }
}

/**
 * Store the parameter only when it differs from the field-specific sentinel.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void Particle_SetFieldOffsetA8IfNotSentinel(Particle* arg0, s16 arg1) {
    if ((u32)arg0 != -1) {
        Particle_FieldA8_SetS16_0BE14(arg0, arg1);
    }
}

/**
 * Store the parameter only when it differs from the field-specific sentinel.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void Particle_SetFieldOffsetCEIfNotSentinel(Particle* arg0, u8 arg1) {
    if ((u32)arg0 != -1) {
        arg0->unk_CE = arg1;
    }
}

void func_8213C3B8(s8 *arg0, unsigned char arg1)
{
  int new_var; // FAKE: permuter temp
  new_var = arg0 != ((s8 *) (-1));
  if (new_var)
  {
    *((s8 *) (((s8 *) arg0) + 0xC9)) = (s8) (arg1 & 0xFF);
  }
}

void func_8213C3D4(s8 *arg0, s16 arg1) {
    if (arg0 != (s8 *)-1) {
        M2C_FIELD(arg0, s16 *, 0xA6) = arg1;
    }
}

/**
 * Store the parameter only when it differs from the field-specific sentinel.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void Particle_SetPrimAlphaIfNotSentinel(Particle* arg0, u8 arg1) {
    if ((u32)arg0 != -1) {
        Particle_SetPrimAlpha(arg0, arg1);
    }
}

/**
 * Store the parameter only when it differs from the field-specific sentinel.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void Particle_SetFieldOffsetAAIfNotSentinel(Particle* arg0, s16 arg1) {
    if ((u32)arg0 != -1) {
        arg0->unk_AE = arg1;
    }
}

void func_8213C444(s8 *arg0, s16 arg1) {
    if (arg0 != (s8 *)-1) {
        M2C_FIELD(arg0, s16 *, 0xAC) = arg1;
    }
}

/**
 * Returns the particle's unk_CE.
 * Seen in play (2026-11-13) in the 165-move sweep (Pay Day, Vice Grip): it returned 7 and 2, the
 * byte at 0xCA each time.
 */
u8 Particle_GetUnkCE(s8 *arg0) {
    return M2C_FIELD(arg0, u8 *, 0xCA);
}

/**
 * Returns the particle's unk_CD.
 * @unverified Name and comment guessed from the code.
 */
u8 Particle_GetUnkCD(s8 *arg0) {
    return M2C_FIELD(arg0, u8 *, 0xC9);
}

/**
 * Return the particle's unk_AA field.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
s16 Particle_FieldAA_GetS16_0C068(Particle* arg0) {
    return arg0->unk_AE;
}

/**
 * Returns the particle's unk_AC.
 * @unverified Name and comment guessed from the code.
 */
s16 Particle_GetUnkAC(s8 *arg0) {
    return M2C_FIELD(arg0, s16 *, 0xA8);
}

// FAKE: decomp slop. Raw pointer-offset casts stand in for struct fields.
s16 func_8213C484(s8 *arg0)
{
  u8 new_var; // FAKE: permuter temp
  new_var = *((u8 *) (((s8 *) arg0) + 0xCB));
  return (s16) new_var;
}

/**
 * Returns the particle's unk_AA (offset 0xA6). Renamed from Particle_FieldA6_GetS16_0BCBC, which
 * used the Stadium 1 offset.
 * Return the particle's unk_A6 field.
 * Seen in play (2026-11-13) in the 165-move sweep (Guillotine): it returned 32, the halfword at
 * 0xA6.
 */
s16 Particle_GetUnkAA(Particle* arg0) {
    return arg0->unk_AA;
}

/**
 * Returns the particle's unk_A6.
 * @unverified Name and comment guessed from the code.
 */
s16 Particle_GetUnkA6(s8 *arg0) {
    return M2C_FIELD(arg0, s16 *, 0xA2);
}

/**
 * Returns the particle's unk_A8.
 * @unverified Name and comment guessed from the code.
 */
s16 Particle_GetUnkA8(s8 *arg0) {
    return M2C_FIELD(arg0, s16 *, 0xA4);
}

/**
 * @unverified Name was previously used only by callers of this address; the definition was still func_.
 */
void BattleAnim_SetEffectStateFlag(s32 arg0) {
    (*(s32 *)&D_8219A82C) = arg0;
}

void FirstClearBonus_HideDialogBox(void) {
    D_8219A82C.unk_00 = 0;
}

s32 func_8213C4C4(void) {
    return (*(s32 *)&D_8219A82C);
}
