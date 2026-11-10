/* Stadium Zero fragment012_17ED00. */
/* C ported from the Stadium 1 decomp: src/fragments/battle_engine/battle_engine_31C660.c. */

#include "fragments/battle_engine/battle_engine.h"
#include "model_renderer.h"

#include "m2c_macros.h"

void BattleAnim_SetupOwnerModelTintPaletteFade(Particle* arg0);
void BattleAnim_SetupParticleRecolorTransparent(Particle* arg0);
void BattleAnim_SetupDescriptor25AlphaFadeInHoldOut(Particle* arg0);
void BattleAnim_SetupDescriptor25AlphaFadeInHold(Particle* arg0);
void BattleAnim_SetupDescriptor25PaletteFadeOut(Particle* arg0);
void BattleAnim_SetupDescriptor25PaletteFadeIn(Particle* arg0);

void BattleAnim_SetupOwnerModelTintPaletteFade(Particle* arg0) {
    ParticleGfx_RecolorPrim(arg0, Particle_FieldCF_GetS16_0C058(arg0));
    Particle_FieldAE_SetS16_0BF4C(arg0, 0);
    Particle_AdvanceLifecycle(arg0);
}

M2C_UNK func_80019B28(s32, u8, u8, u8, s32);        /* extern */
M2C_UNK func_8213C930(s8 *);                      /* extern */
s32 func_8213C9B0(s8 *);                          /* extern */
M2C_UNK func_8213C9D0(s8 *);                      /* extern */
s32 func_8214083C(s8 *, s16, u8);                 /* extern */
s32 func_821436A0(s8 *, u8, u8);                  /* extern */
M2C_UNK func_82144130(s8 *);                      /* extern */

void func_82144170(s8 *arg0) {
    s16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_82144130(arg0);
        break;
    case 2:
        if (func_8214083C(arg0, M2C_FIELD(arg0, s16 *, 0xA2), M2C_FIELD(arg0, u8 *, 0xCA)) != 0) {
            func_8213C9D0(arg0);
        }
        break;
    case 3:
        if (func_821436A0(arg0, M2C_FIELD(arg0, u8 *, 0xC9), M2C_FIELD(arg0, u8 *, 0xA7)) != 0) {
            func_8213C9D0(arg0);
        }
        break;
    case 4:
        func_8213C930(arg0);
        break;
    }
    if (func_8213C9B0(arg0) != 0) {
        func_80019B28(M2C_FIELD(arg0, s32 *, 0x10), M2C_FIELD(arg0, u8 *, 0xBA), M2C_FIELD(arg0, u8 *, 0xBB), M2C_FIELD(arg0, u8 *, 0xBC), (s32) M2C_FIELD(arg0, s16 *, 0xAA));
    }
}

void BattleAnim_SetupOwnerModelTintRandomPaletteCycle(Particle* arg0) {
    ParticleGfx_RecolorPrim(arg0, gParticlePaletteSetA[ParticleMath_RandomRange(6)]);
    Particle_FieldCF_SetU8_0BEEC(arg0, gParticlePaletteSetA[ParticleMath_RandomRange(6)]);
    Particle_SetPrimAlpha(arg0, arg0->unk_CD);

    if (arg0->unk_AA == 0) {
        arg0->unk_AA = 1;
    }

    Particle_FieldA6_SetS16_0BCA8(arg0, 0xFF / arg0->unk_AA);
    Particle_AdvanceLifecycle(arg0);
}

void BattleAnim_CallbackOwnerModelTintRandomPaletteCycle(Particle* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            BattleAnim_SetupOwnerModelTintRandomPaletteCycle(arg0);
            break;

        case 2:
            ParticleGfx_ApproachPrimPalette(arg0, arg0->unk_CF, arg0->unk_AA);
            if (Particle_FieldA6_DecrementToZeroStep1_0BDAC(arg0) != 0) {
                Particle_FieldA6_SetS16_0BCA8(arg0, 0xFF / arg0->unk_AA);
                Particle_FieldCF_SetU8_0BEEC(arg0, gParticlePaletteSetA[ParticleMath_RandomRange(6)]);
            }
            Model_SetMaterialColor(&arg0->unk_10->displayObject, arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->prim_a);
            break;
    }
}

void BattleAnim_SetupOwnerModelTintPaletteRotateFadeDetach(Particle* arg0) {
    ParticleGfx_RecolorPrim(arg0, gParticlePaletteSetA[0]);
    Particle_FieldAE_SetS16_0BF4C(arg0, 1);
    Particle_FieldCF_SetU8_0BEEC(arg0, gParticlePaletteSetA[1]);
    Particle_SetPrimAlpha(arg0, arg0->unk_CD);

    if (arg0->unk_AA == 0) {
        arg0->unk_AA = 1;
    }

    Particle_FieldA8_SetS16_0BE14(arg0, 0xFF / arg0->unk_AA);
    Particle_AdvanceLifecycle(arg0);
}

void BattleAnim_CallbackOwnerModelTintPaletteRotateFadeDetach(Particle* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            BattleAnim_SetupOwnerModelTintPaletteRotateFadeDetach(arg0);
            break;

        case 2:
            Particle_FieldA6_DecrementToZeroStep1AndStepState_0BDD0(arg0);
            if (Particle_FieldA8_DecrementToZeroStep1_0BE6C(arg0) != 0) {
                Particle_FieldA8_SetS16_0BE14(arg0, 0xFF / arg0->unk_AA);
                arg0->unk_AE = (arg0->unk_AE + 1) % 6;
                Particle_FieldCF_SetU8_0BEEC(arg0, gParticlePaletteSetA[arg0->unk_AE]);
            }
            ParticleGfx_ApproachPrimPalette(arg0, arg0->unk_CF, arg0->unk_AA);
            Model_SetMaterialColor(&arg0->unk_10->displayObject, arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->prim_a);
            break;

        case 3:
            if (Particle_PrimAlpha_Approach_0BC2C(arg0, 0, 8) != 0) {
                Particle_AdvanceLifecycle(arg0);
            }
            Model_SetMaterialColor(&arg0->unk_10->displayObject, arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->prim_a);
            break;

        case 4:
            Particle_DisableAndDetach(arg0);
            break;
    }
}

void BattleAnim_SetupOwnerModelAlphaFade(Particle* arg0) {
    arg0->prim_a = arg0->unk_A6;
    Particle_AdvanceLifecycle(arg0);
}

M2C_UNK func_80019B6C(s32, u8);                     /* extern */
M2C_UNK func_8213C930(s8 *);                      /* extern */
s32 func_8213C9B0(s8 *);                          /* extern */
M2C_UNK func_8213C9D0(s8 *);                      /* extern */
s32 func_82140518(s8 *, u8, u8);                  /* extern */
M2C_UNK func_82144644(s8 *);                      /* extern */

void func_82144668(s8 *arg0) {
    s16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_82144644(arg0);
        break;
    case 2:
        if (func_82140518(arg0, M2C_FIELD(arg0, u8 *, 0xC9), M2C_FIELD(arg0, u8 *, 0xA7)) != 0) {
            func_8213C9D0(arg0);
        }
        break;
    case 3:
        func_8213C930(arg0);
        break;
    }
    if (func_8213C9B0(arg0) != 0) {
        func_80019B6C(M2C_FIELD(arg0, s32 *, 0x10), M2C_FIELD(arg0, u8 *, 0xC0));
    }
}

void BattleAnim_SetupParticleRecolorTransparent(Particle* arg0) {
    ParticleGfx_RecolorPrim(arg0, Particle_FieldCF_GetS16_0C058(arg0));
    Particle_SetPrimAlpha(arg0, 0);
    Particle_AdvanceLifecycle(arg0);
}

M2C_UNK func_80019B28(s32, u8, u8, u8, s32);        /* extern */
M2C_UNK func_8213C938(s8 *);                      /* extern */
M2C_UNK func_82144710(s8 *);                      /* extern */

void func_82144750(s8 *arg0) {
    s16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_82144710(arg0);
        break;
    case 2:
        func_82140518(arg0, 0x80, 4);
        break;
    case 3:
        if (func_82140518(arg0, 0, 8) != 0) {
            func_8213C938(arg0);
        }
        break;
    }
    func_80019B28(M2C_FIELD(arg0, s32 *, 0x10), M2C_FIELD(arg0, u8 *, 0xBA), M2C_FIELD(arg0, u8 *, 0xBB), M2C_FIELD(arg0, u8 *, 0xBC), (s32) M2C_FIELD(arg0, u8 *, 0xC0));
}

void BattleAnim_SetupDescriptor25AlphaFadeInHoldOut(Particle* arg0) {
    ParticleGfx_RecolorPrim(arg0, Particle_FieldCF_GetS16_0C058(arg0));
    Particle_SetPrimAlpha(arg0, 0);
    Particle_AdvanceLifecycle(arg0);
}

void BattleAnim_CallbackDescriptor25AlphaFadeInHoldOut(Particle* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            BattleAnim_SetupDescriptor25AlphaFadeInHoldOut(arg0);
            break;

        case 2:
            Particle_PrimAlpha_ApproachAndStepState_0BC5C(arg0, arg0->unk_CD, arg0->unk_AA);
            break;

        case 3:
            Particle_FieldA6_DecrementToZeroStep1AndStepState_0BDD0(arg0);
            break;

        case 4:
            if (Particle_PrimAlpha_Approach_0BC2C(arg0, 0, arg0->unk_AA) != 0) {
                Particle_MarkInactive(arg0);
            }
            break;
    }
}

s32 func_8213C484();                                /* extern */
M2C_UNK func_8213C9D0(s8 *);                      /* extern */
M2C_UNK func_8214050C(s8 *, u8);                  /* extern */
M2C_UNK func_82143408(s8 *, s32);                 /* extern */
// FAKE: decomp slop. Raw pointer-offset casts stand in for struct fields.
void func_821448D4(s8 *arg0)
{
  func_82143408(arg0, func_8213C484() & 0xFFFF);
  if (arg0)
  {
  }
  func_8214050C(arg0, *((u8 *) (((s8 *) arg0) + 0xC9)));
  func_8213C9D0(arg0);
}

void BattleAnim_CallbackDescriptor25AlphaHoldFadeOut(Particle* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            BattleAnim_SetupDescriptor25AlphaHoldFadeOut(arg0);
            break;

        case 2:
            Particle_FieldA6_DecrementToZeroStep1AndStepState_0BDD0(arg0);
            break;

        case 3:
            if (Particle_PrimAlpha_Approach_0BC2C(arg0, 0, arg0->unk_AA) != 0) {
                Particle_MarkInactive(arg0);
            }
            break;
    }
}

void BattleAnim_SetupDescriptor25AlphaFadeInHold(Particle* arg0) {
    ParticleGfx_RecolorPrim(arg0, Particle_FieldCF_GetS16_0C058(arg0));
    Particle_SetPrimAlpha(arg0, 0);
    Particle_AdvanceLifecycle(arg0);
}

void BattleAnim_CallbackDescriptor25AlphaFadeInHold(Particle* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            BattleAnim_SetupDescriptor25AlphaFadeInHold(arg0);
            break;

        case 2:
            Particle_PrimAlpha_ApproachAndStepState_0BC5C(arg0, arg0->unk_CD, arg0->unk_AA);
            break;

        case 3:
            if (Particle_FieldA6_DecrementToZeroStep1_0BDAC(arg0) != 0) {
                Particle_MarkInactive(arg0);
            }
            break;
    }
}

void func_82144A54(Particle* arg0) {
    ParticleGfx_RecolorPrim(arg0, Particle_FieldCF_GetS16_0C058(arg0));
    Particle_SetPrimAlpha(arg0, arg0->unk_CD);
    Particle_AdvanceLifecycle(arg0);
}

M2C_UNK func_8213C938(s8 *);                      /* extern */
s32 func_82140690();                                /* extern */

void func_82144A9C(s8 *arg0) {
    s16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_82144A54((Particle*)arg0);
        return;
    case 2:
        if (func_82140690() != 0) {
            func_8213C938(arg0);
        }
        return;
    }
}

void BattleAnim_SetupDescriptor25PaletteFadeOut(Particle* arg0) {
    ParticleGfx_RecolorPrim(arg0, Particle_FieldCF_GetS16_0C058(arg0));
    Particle_SetPrimAlpha(arg0, 0xFF);
    Particle_AdvanceLifecycle(arg0);
}

void BattleAnim_CallbackDescriptor25PaletteFadeOut(Particle* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            BattleAnim_SetupDescriptor25PaletteFadeOut(arg0);
            break;

        case 2:
            Particle_FieldA6_DecrementToZeroStep1AndStepState_0BDD0(arg0);
            break;

        case 3:
            ParticleGfx_ApproachPrimPalette(arg0, arg0->unk_CD, arg0->unk_AA);
            if (Particle_PrimAlpha_Approach_0BC2C(arg0, 0, arg0->unk_AA) != 0) {
                Particle_MarkInactive(arg0);
            }
            break;
    }
}

void BattleAnim_SetupDescriptor25PaletteFadeIn(Particle* arg0) {
    ParticleGfx_RecolorPrim(arg0, Particle_FieldCF_GetS16_0C058(arg0));
    Particle_SetPrimAlpha(arg0, 0);
    Particle_AdvanceLifecycle(arg0);
}

void BattleAnim_CallbackDescriptor25PaletteFadeIn(Particle* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            BattleAnim_SetupDescriptor25PaletteFadeIn(arg0);
            break;

        case 2:
            ParticleGfx_ApproachPrimPalette(arg0, arg0->unk_CD, arg0->unk_AA);
            Particle_PrimAlpha_ApproachAndStepState_0BC5C(arg0, 0xFF, arg0->unk_AA);
            break;

        case 3:
            if (Particle_FieldA6_DecrementToZeroStep1_0BDAC(arg0) != 0) {
                Particle_MarkInactive(arg0);
            }
            break;
    }
}
