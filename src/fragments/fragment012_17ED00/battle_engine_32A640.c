/* Stadium Zero fragment012_17ED00. */
/* C ported from the Stadium 1 decomp: src/fragments/battle_engine/battle_engine_32A640.c, src/fragments/battle_engine/battle_engine_343BA0.c. */

#include "fragments/battle_engine/battle_engine.h"

#include "fragments/battle_engine/battle_engine.h"
#include "gallery.h"
#include "gfx_buffer.h"
#include "math.h"
#include "math_util.h"
extern u8* sBattleAnimAssetPointers[256];
extern s16 sBattleAnimResourceList[0x10];
extern arg1_func_80019420* sBattleAnimResourceTablePointers[40];
extern s16 D_8219CAC0;
extern s16 D_8219CAC2;
extern Mtx D_8219CAC8;
extern s16 D_8219CB08;
extern s16 D_8219CB0A;
extern s16 D_8219CB0C;
extern s16 D_8219CB0E;
extern s16 D_8219CB10;
extern s16 D_8219CB12;
extern s16 D_8219CB14;
extern s16 D_8219CB16;
extern s16 D_8219CB18;
extern s16 D_8219CB1A;
extern const char D_821978C8[];

#include "m2c_macros.h"

void BattleAnim_UnusedResetAppearanceAndAdvance(Particle* arg0);
void BattleAnim_SetupOrphanDescriptor2BSpinFade(Particle* arg0);
void BattleAnim_SetupPetalDanceLingeringHitEffect(Particle* arg0);
void BattleAnim_DefaultStartEffect_Draw(void);
void BattleAnim_OrphanDescriptor2BAnd2EEmitterSequence(void);
void BattleAnim_InitializePetalDanceHit(void);
void BattleAnim_InitializeWingAttackHit(void);

void BattleAnim_CallbackOrphanDescriptor2BSpinFade(Particle* arg0);
void BattleAnim_CallbackOrphanDescriptor2EScatterFade(Particle* arg0);
void BattleAnim_RunPetalDanceLingeringHitEffect(Particle* arg0);
void BattleAnim_RunSlowFallingHitEffect(Particle* arg0);

/**
 * Lifecycle init: white and fully opaque.
 * @unverified Name from Stadium 1.
 */
void BattleAnim_UnusedResetAppearanceAndAdvance(Particle* arg0) {
    Particle_SetPrimColor(arg0, 0xFF, 0xFF, 0xFF);
    Particle_SetPrimAlpha(arg0, 0xFF);
    Particle_AdvanceLifecycle(arg0);
}

/**
 * Particle callback: resets the color, then fades the particle while moving it on a
 * circle of radius 32.
 * @unverified Name from Stadium 1.
 */
void BattleAnim_CallbackUnusedGenericFadeApproach(Particle* arg0) {
    switch (arg0->lifecycle) {
        case 0:
            break;

        case 1:
            BattleAnim_UnusedResetAppearanceAndAdvance(arg0);
            break;

        case 2:
            Particle_ApproachScale(arg0, 3.0f, 0.025f);
            Particle_TickDelayAndAdvanceLifecycle(arg0, 300);
            break;

        case 3:
            if (Particle_PrimAlpha_Approach_0BC2C(arg0, 0x20, 0x20) != 0) {
                Particle_AdvanceLifecycle(arg0);
            }
            break;

        case 4:
            Particle_DisableAndDetach(arg0);
            break;
    }

    Particle_UpdateRotatingVelocityXZ(arg0, 32.0f, 0x400);
}

/**
 * Lifecycle init: small, randomly rotated and spinning, fast, delayed 4 frames per burst
 * index.
 * @unverified Name from Stadium 1.
 */
void BattleAnim_SetupOrphanDescriptor2BSpinFade(Particle* arg0) {
    s16 sp26 = Particle_FieldAC_GetS16_0C038(arg0);

    Particle_SetScaleScaled(arg0, 0.2f);
    Particle_Field7C_SetYScaled_0AF24(arg0, 1.0f);
    Particle_Field94_SetX_0A2A4(arg0, ParticleMath_RandomRange(0x10000));
    Particle_Field94_SetZ_0A2CC(arg0, ParticleMath_RandomRange(0x10000));
    Particle_Field9A_SetY_0A3D8(arg0, ParticleMath_RandomRange(0x10000));
    Particle_Field74_SetScaled_0AD8C(arg0, 5.0f);
    Particle_FieldA6_SetS16_0BCA8(arg0, sp26 * 4);
    Particle_DisableRendering(arg0);
    Particle_AdvanceLifecycle(arg0);
}

void func_8213E1FC(Particle* arg0, f32 arg1);
s32 Particle_ApproachStepMagnitude(Particle* arg0, f32 arg1, f32 arg2);
/**
 * Particle callback: after the delay shows the particle, flies it out spinning, then
 * fades it.
 * @unverified Name from Stadium 1.
 */
void BattleAnim_CallbackOrphanDescriptor2BSpinFade(Particle* arg0) {
    switch (arg0->lifecycle) {
        case 1:
            BattleAnim_SetupOrphanDescriptor2BSpinFade(arg0);
            break;

        case 2:
            if (Particle_DecrementUnkA6ToZeroThenAdvance(arg0) != 0) {
                Particle_EnableRendering(arg0);
                Particle_BeginPhase(arg0);
            }
            break;

        case 3:
            if (Particle_TickDelayAndAdvanceLifecycle(arg0, 50) != 0) {
                Particle_AdvancePhase(arg0);
            }
            break;

        case 4:
            if (Particle_TickDelayAndAdvanceLifecycle(arg0, 20) != 0) {} // karodo
            break;

        case 5:
            Particle_DisableAndDetach(arg0);
            break;
    }

    switch (arg0->phase) {
        case 1:
            Particle_ApproachStepMagnitude(arg0, 50.0f, 0.5f);
            func_8213E1FC(arg0, 1.0f);
            Particle_UpdateRotatingVelocityXZ(arg0, arg0->stepMagnitude, 0x1000);
            Particle_Field94_AddX_0A578(arg0, 0x2000);
            Particle_Field94_AddZ_0A5B0(arg0, 0x3000);
            break;

        case 2:
            Particle_ApproachStepMagnitude(arg0, 0.0f, 1.0f);
            func_8213E1FC(arg0, -2.0f);
            Particle_UpdateRotatingVelocityXZ(arg0, arg0->stepMagnitude, 0x1000);
            Particle_Field94_AddX_0A578(arg0, 0x2000);
            Particle_Field94_AddZ_0A5B0(arg0, 0x3000);
            break;
    }
}

/**
 * Lifecycle init: half scale, fast, small random tilt, palette color 0x22, delayed 4
 * frames per burst index.
 * @unverified Name from Stadium 1.
 */
void BattleAnim_SetupOrphanDescriptor2EScatterFade(Particle* arg0) {
    s16 sp2E = Particle_FieldAC_GetS16_0C038(arg0);

    Particle_SetScaleScaled(arg0, 0.5f);
    Particle_Field74_SetScaled_0AD8C(arg0, 10.0f);
    Particle_Field94_AddVec_0A52C(arg0, ParticleMath_RandomSigned(0x1000), ParticleMath_RandomSigned(0x1000), 0);
    Particle_FieldA6_SetS16_0BCA8(arg0, sp2E * 4);
    ParticleGfx_RecolorPrim(arg0, 0x22);
    ParticleGfx_RecolorEnv(arg0, 0x22);
    Particle_DisableRendering(arg0);
    Particle_AdvanceLifecycle(arg0);
}

void Particle_DisableAndDetach(s8 *arg0);                      /* extern */
M2C_UNK func_8213CA80(s8 *, M2C_UNK);             /* extern */
M2C_UNK func_8213CB3C(s8 *);                      /* extern */
s32 func_8213CB7C(s8 *);                          /* extern */
void Particle_AddVelocityFromRotationTemplate1(s32 arg0);                      /* extern */
M2C_UNK Particle_AddRotationZ(s8 *, M2C_UNK);             /* extern */
s32 func_821406B4(s8 *);                          /* extern */
M2C_UNK func_821519AC(s8 *);                      /* extern */

void func_82151A5C(s8 *arg0) {
    s16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_821519AC(arg0);
        break;
    case 2:
        if (func_821406B4(arg0) != 0) {
            func_8213CB3C(arg0);
        }
        break;
    case 3:
        func_8213CA80(arg0, 0x46);
        break;
    case 4:
        Particle_DisableAndDetach(arg0);
        break;
    }
    if (func_8213CB7C(arg0) != 0) {
        Particle_AddVelocityFromRotationTemplate1(arg0);
        Particle_AddRotationZ(arg0, 0x2000);
    }
}

/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Petal Dance.
 */
void BattleAnim_SetupPetalDanceLingeringHitEffect(Particle* arg0) {
    s16 sp26 = Particle_FieldAC_GetS16_0C038(arg0);

    Particle_SetScaleScaled(arg0, 0.12f);
    Particle_Field7C_SetYScaled_0AF24(arg0, (ParticleMath_RandomRange(0x14) * 0.02f) + 0.25f);
    Particle_Field94_SetX_0A2A4(arg0, ParticleMath_RandomRange(0x10000));
    Particle_Field94_SetZ_0A2CC(arg0, ParticleMath_RandomRange(0x10000));
    Particle_Field74_SetScaled_0AD8C(arg0, 5.0f);
    Particle_FieldAE_SetS16_0BF4C(arg0, ParticleMath_RandomRange(0x800) + 0xC00);
    Particle_Field9A_SetX_0A3C4(arg0, ParticleMath_RandomSignedOffsetBySign(0x800, 0x300));
    Particle_FieldB0_SetS16_0BFEC(arg0, ParticleMath_RandomSignedOffsetBySign(0x800, 0x300));
    Particle_Field9A_SetY_0A3D8(arg0, ParticleMath_RandomRange(0x10000));
    Particle_Field9A_SetZ_0A3EC(arg0, ParticleMath_RandomSignedOffsetBySign(0x800, 0x300));
    Particle_Field38_AddYScaled_08E90(arg0, ParticleMath_RandomRange(0x1E));
    Particle_FieldA6_SetS16_0BCA8(arg0, sp26 * 2);
    Particle_DisableRendering(arg0);
    Particle_AdvanceLifecycle(arg0);
}

void func_8213E1FC(Particle* arg0, f32 arg1);
s32 Particle_ApproachStepMagnitude(Particle* arg0, f32 arg1, f32 arg2);
void Particle_ApplyRotationStepX(Particle* arg0);
/**
 * Handles the floating pedals that linger when being hit by pedal dance
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Petal Dance.
 */
void BattleAnim_RunPetalDanceLingeringHitEffect(Particle* arg0) {
    switch (arg0->lifecycle) {
        case 1:
            BattleAnim_SetupPetalDanceLingeringHitEffect(arg0);
            break;

        case 2:
            if (Particle_DecrementUnkA6ToZeroThenAdvance(arg0) != 0) {
                Particle_EnableRendering(arg0);
                Particle_BeginPhase(arg0);
                Particle_FieldA6_SetS16_0BCA8(arg0, ParticleMath_RandomRange(0xA) + 0x1E);
            }
            break;

        case 3:
            if (Particle_DecrementUnkA6ToZeroThenAdvance(arg0) != 0) {
                Particle_FieldA6_SetS16_0BCA8(arg0, 8);
                Particle_AdvancePhase(arg0);
            }
            break;

        case 4:
            if (Particle_DecrementUnkA6ToZeroThenAdvance(arg0) != 0) {
                Particle_Field9A_SetX_0A3C4(arg0, ParticleMath_RandomSignedOffsetBySign(0x1000, 0x600));
                Particle_FieldB0_SetS16_0BFEC(arg0, ParticleMath_RandomSignedOffsetBySign(0x400, 0x400));
                Particle_Field9A_SetZ_0A3EC(arg0, ParticleMath_RandomSignedOffsetBySign(0x1000, 0x600));
                arg0->positionOffset.x += arg0->motionOffset.x;
                arg0->motionOffset.x = 0;
                arg0->positionOffset.z += arg0->motionOffset.z;
                arg0->motionOffset.z = 0;
                Particle_AdvancePhase(arg0);
                arg0->motionStep.y = -((ParticleMath_RandomRange(8) * 0.1f) + 0.5f);
            }
            break;

        case 5:
            Particle_TickDelayAndAdvanceLifecycle(arg0, 70);
            break;

        case 6:
            Particle_MarkInactive(arg0);
            break;
    }

    switch (arg0->phase) {
        case 1:
            Particle_ApproachStepMagnitude(arg0, 20.0f, 0.5f);
            func_8213E1FC(arg0, arg0->motionStep.y);
            Particle_UpdateRotatingVelocityXZ(arg0, arg0->stepMagnitude, arg0->unk_AE);
            break;

        case 2:
            Particle_FieldAE_Approach_0BF60(arg0, 0, 0x200);
            func_8213E1FC(arg0, arg0->motionStep.y);
            Particle_UpdateRotatingVelocityXZ(arg0, arg0->stepMagnitude, arg0->unk_AE);
            break;

        case 3:
            func_8213E1FC(arg0, arg0->motionStep.y);
            Particle_UpdateRotatingVelocityXZ(arg0, 5.0f, 0x400);
            break;
    }

    if (Particle_IsRenderingEnabled(arg0) != 0) {
        Particle_ApplyRotationStepX(arg0);
        Particle_Field94_AddY_0A594(arg0, arg0->unk_B0);
        Particle_Field94_AddXFromField9A_0A4B4(arg0);
        if (arg0->worldPosition.y < 0.0f) {
            Particle_MarkInactive(arg0);
        }
    }
}

/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Vine Whip and Wing Attack.
 */
void BattleAnim_SetupSlowFallingHitEffect(Particle* arg0) {
    s16 sp26 = Particle_FieldAC_GetS16_0C038(arg0);
    s16 sp24 = Particle_FieldCE_GetS32_0C040(arg0);

    Particle_Field7C_SetYScaled_0AF24(arg0, 0.5f);

    switch (sp24) {
        case 0:
            Particle_SetScaleScaled(arg0, 0.12f);
            arg0->motionTarget.y = -((ParticleMath_RandomRange(0xA) * 0.1f) + 0.5f);
            Particle_Field38_AddYScaled_08E90(arg0, ParticleMath_RandomRange(0x28) + 0x1E);
            Particle_SetRandomVelocityXSymmetric(arg0, 0x1E, 0);
            Particle_SetRandomVelocityZSymmetric(arg0, 0x1E, 0);
            break;

        case 1:
            Particle_SetScaleScaled(arg0, 0.2f);
            arg0->motionTarget.y = -((ParticleMath_RandomRange(4) * 0.1f) + 0.2f);
            Particle_Field38_AddYScaled_08E90(arg0, ParticleMath_RandomSigned(0x14) + 0x1E);
            Particle_SetRandomVelocityXSymmetric(arg0, 0xF, 5);
            Particle_SetRandomVelocityZSymmetric(arg0, 0x14, 5);
            break;
    }

    Particle_Field94_SetX_0A2A4(arg0, ParticleMath_RandomRange(0x10000));
    Particle_Field94_SetZ_0A2CC(arg0, ParticleMath_RandomRange(0x10000));
    Particle_Field74_SetScaled_0AD8C(arg0, ParticleMath_RandomRange(0x14) + 15.0f);
    Particle_FieldAE_SetS16_0BF4C(arg0, ParticleMath_RandomRange(0x300) + 0x400);
    Particle_Field9A_SetY_0A3D8(arg0, ParticleMath_RandomRange(0x10000));
    Particle_Field9A_SetX_0A3C4(arg0, ParticleMath_RandomSignedOffsetBySign(0x800, 0x400));
    Particle_Field9A_SetZ_0A3EC(arg0, ParticleMath_RandomSignedOffsetBySign(0x800, 0x400));
    Particle_FieldA6_SetS16_0BCA8(arg0, sp26 * 2);
    Particle_DisableRendering(arg0);
    Particle_AdvanceLifecycle(arg0);
}

void func_8213E1FC(Particle* arg0, f32 arg1);
void Particle_ApplyRotationStepX(Particle* arg0);
/**
 * Handles the leaves that spawn when being hit by vine whip and the feathers that spawn when being hit by wing attack
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Vine Whip and Wing Attack.
 */
void BattleAnim_RunSlowFallingHitEffect(Particle* arg0) {
    s16 sp26 = Particle_FieldCE_GetS32_0C040(arg0);

    switch (arg0->lifecycle) {
        case 1:
            BattleAnim_SetupSlowFallingHitEffect(arg0);
            break;

        case 2:
            if (Particle_DecrementUnkA6ToZeroThenAdvance(arg0) != 0) {
                Particle_EnableRendering(arg0);
                Particle_BeginPhase(arg0);
                switch (sp26) {
                    case 0:
                        Particle_FieldA6_SetS16_0BCA8(arg0, ParticleMath_RandomRange(0x1E) + 0x32);
                        break;

                    case 1:
                        Particle_FieldA6_SetS16_0BCA8(arg0, ParticleMath_RandomRange(0x1E) + 0x64);
                        break;
                }
            }
            break;

        case 3:
            Particle_DecrementUnkA6ToZeroThenAdvance(arg0);
            break;

        case 4:
            Particle_MarkInactive(arg0);
            break;
    }

    if (arg0->phase == 1) {
        func_8213E1FC(arg0, arg0->motionTarget.y);
        Particle_UpdateRotatingVelocityXZ(arg0, 5.0f, 0x400);
    }

    if (Particle_IsRenderingEnabled(arg0) != 0) {
        Particle_ApplyRotationStepX(arg0);
        Particle_Field94_AddYFromField9A_0A4C8(arg0);
        Particle_Field94_AddXFromField9A_0A4B4(arg0);
        if (arg0->worldPosition.y < 0.0f) {
            Particle_MarkInactive(arg0);
        }
    }
}

/**
 * Draw hook for start effects that draw nothing.
 * @unverified Name from Stadium 1.
 */
void BattleAnim_DefaultStartEffect_Draw(void) {
}

/**
 * Effect sequence: sets effect state flag 1 after 128 frames, spawns four waves of
 * spinning particles, then 58 frames later four scatter bursts.
 * @unverified Name from Stadium 1.
 */
void BattleAnim_OrphanDescriptor2BAnd2EEmitterSequence(void) {
    BattleAnim_SpawnCategory17MarkerSlot(0x80, 1);
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_CallbackOrphanDescriptor2BSpinFade, &gBattleAnimParticleDescriptors[0x2B], 0, 0x10, 0xA, 0, 0, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(2, BattleAnim_CallbackOrphanDescriptor2BSpinFade, &gBattleAnimParticleDescriptors[0x2B], 0, 0x10, 0xA, 0, 0, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(4, BattleAnim_CallbackOrphanDescriptor2BSpinFade, &gBattleAnimParticleDescriptors[0x2B], 0, 0x10, 0xA, 0, 0, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(8, BattleAnim_CallbackOrphanDescriptor2BSpinFade, &gBattleAnimParticleDescriptors[0x2B], 0, 8, 0xA, 0, 0, 0);
    BattleAnim_AddSpawnDelay(58);
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_CallbackOrphanDescriptor2EScatterFade, &gBattleAnimParticleDescriptors[0x2E], 0, 0x10, 2, 0, 0, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_CallbackOrphanDescriptor2EScatterFade, &gBattleAnimParticleDescriptors[0x2E], 0, 0x10, 2, 0, 0, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_CallbackOrphanDescriptor2EScatterFade, &gBattleAnimParticleDescriptors[0x2E], 0, 0x10, 2, 0, 0, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_CallbackOrphanDescriptor2EScatterFade, &gBattleAnimParticleDescriptors[0x2E], 0, 0x10, 2, 0, 0, 0);
}

/**
 * initializes being hit by pedal dance
 * Effect end init 26 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used: it
 * ran for exactly Petal Dance.
 */
void BattleAnim_InitializePetalDanceHit(void) {
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0, 2, 0x14, BattleAnim_RunPetalDanceLingeringHitEffect, &gBattleAnimParticleDescriptors[0x2C], 0, 4, 0xE, 0, 0, 0);
    BattleAnim_InitializePetalDanceHitSequence();
}

/**
 * initializes being hit by wing attack
 * Effect end init 87 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used: it
 * ran for exactly Wing Attack.
 */
void BattleAnim_InitializeWingAttackHit(void) {
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0, 2, 5, BattleAnim_RunSlowFallingHitEffect, &gBattleAnimParticleDescriptors[0x2D], 0, 1, 0xE, 0, 0, 1);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0, 4, 5, BattleAnim_RunSlowFallingHitEffect, &gBattleAnimParticleDescriptors[0x2D], 0, 1, 0xE, 0, 0, 1);
}
