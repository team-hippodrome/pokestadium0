/* Stadium Zero fragment012_17ED00. */
/* C ported from the Stadium 1 decomp: src/fragments/battle_engine/battle_engine_3223B0.c. */

#include "fragments/battle_engine/battle_engine.h"
#include "math_util.h"

#include "m2c_macros.h"

void BattleAnim_SetupSurfHitSpark(Particle* arg0);
void BattleAnim_SetupBubbleBubbles(Particle* arg0, s16 arg1);
void BattleAnim_SetupBubbleBeamBubblesSlow(Particle* arg0);
void BattleAnim_SetupBubbleBeamBubblesFast(Particle* arg0);
void BattleAnim_SetupUnusedRotatingSparkVariant(Particle* arg0);
void BattleAnim_SetupUnusedAimedSparkVariant(Particle* arg0);
void BattleAnim_SetupWaterGunAndHydroPumpEmitterFade(Particle* arg0);
void BattleAnim_SetupHydroPumpBurstChild(Particle* arg0);
void BattleAnim_SetupHydroPumpMetadataBurstChild(Particle* arg0);
void BattleAnim_SetupHydroPumpBurstEmitter(Particle* arg0);
void BattleAnim_SetupWaterGunProjectileChild(Particle* arg0);
void BattleAnim_SetupWaterGunProjectileMetadata(Particle* arg0);
void BattleAnim_SetupWaterGunProjectile(Particle* arg0);
void BattleAnim_SetupIceBeamColdBreath(Particle* arg0);
void BattleAnim_SetupMegaKickAndPunchProjectile(Particle* arg0);
void BattleAnim_SetupInitialBeamEmanator(Particle* arg0);
void BattleAnim_SetupPulsingBeamEmanator(Particle* arg0);
void BattleAnim_SetupStrongBeamHitEffect(Particle* arg0);
void BattleAnim_SetupPsybeamHitSparkFlicker(Particle* arg0);
void BattleAnim_SetupStrongOutwardMovingLargeHitSpark(Particle* arg0);
void BattleAnim_SetupBlizzardHitUpwardColdAir(Particle* arg0);
void BattleAnim_SetupWaterGunHitEffect(Particle* arg0);
void BattleAnim_SetupTriAttackHitSpark(Particle* arg0);
void BattleAnim_SetupStrongOutwardMovingSmallHitSpark(Particle* arg0);
void BattleAnim_SetupUnusedIndexedFadeVariantA(Particle* arg0);
void BattleAnim_SetupUnusedIndexedFadeVariantB(Particle* arg0);
void BattleAnim_SetupWaterGunEmitterColoration(Particle* arg0);
void BattleAnim_SetupHydroPumpWaterGunProjectileHit(Particle* arg0);
void BattleAnim_StartMegaPunchEffect(void);
void BattleAnim_InitializeWaterGunUse(void);
void BattleAnim_InitializeHydroPumpUse(void);
void BattleAnim_InitializeTriAttackHit(void);

void BattleAnim_RunWaterGunAndHydroPumpEmitterFade(Particle* arg0);
void BattleAnim_RunHydroPumpBurstEmitter(Particle* arg0);
void BattleAnim_RunWaterGunProjectile(Particle* arg0);
void BattleAnim_RunMegaKickAndPunchProjectile(Particle* arg0);
void BattleAnim_CallbackEndEffect86Descriptor19ModePositionedAnimFade(Particle* arg0);

/**
 * @unverified Name from Stadium 1.
 */
void BattleAnim_SetupSurfHitSpark(Particle* arg0) {
    s16 sp26 = Particle_FieldAC_GetS16_0C038(arg0);
    s16 sp24 = Particle_FieldCF_GetS16_0C058(arg0);

    Particle_Field1C_SetScaled_0B938(arg0, (ParticleMath_RandomRange(0xA) * 0.01f) + 0.05f);
    Particle_Field7C_SetYScaled_0AF24(arg0, (ParticleMath_RandomRange(0x1E) * 0.1f) + 1.0f);
    Particle_Field9A_SetY_0A3D8(arg0, ParticleMath_RandomRange(0x10000));
    Particle_Field74_SetScaled_0AD8C(arg0, 5.0f);
    Particle_Field78_SetScaled_0ADA4(arg0, ParticleMath_RandomRange(0xF) + 5.0f);
    Particle_FieldAE_SetS16_0BF4C(arg0, ParticleMath_RandomRangeOffset(0x1000, 0x800));
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, sp24);
    Particle_FieldA6_SetS16_0BCA8(arg0, sp26);
    Particle_DisableRendering(arg0);
    Particle_AdvanceLifecycle(arg0);
}

M2C_UNK func_8213C938(s8 *);                      /* extern */
M2C_UNK func_8213CB3C(s8 *);                      /* extern */
s32 func_8213CB7C(s8 *);                          /* extern */
M2C_UNK func_8213CCEC(s8 *, M2C_UNK, M2C_UNK, M2C_UNK, s32, s32); /* extern */
M2C_UNK func_8213E488(s8 *);                      /* extern */
M2C_UNK func_8213F658(s8 *, f32, f32);        /* extern */
M2C_UNK func_82140064(s8 *, s32, s16);            /* extern */
M2C_UNK func_82140594(s8 *, M2C_UNK);             /* extern */
s32 func_82140690(s8 *);                          /* extern */
s32 func_821406B4(s8 *);                          /* extern */
M2C_UNK func_82149660(s8 *);                      /* extern */

/**
 * Handles the hit spark from being hit by Surf
 * @unverified Name and comment from Stadium 1, matched by code similarity.
 */
void BattleAnim_RunSurfHitSpark(s8 *arg0) {
    s16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_82149660(arg0);
        break;
    case 2:
        if (func_821406B4(arg0) != 0) {
            func_8213CB3C(arg0);
            func_82140594(arg0, 0xA);
        }
        break;
    case 3:
        if (func_82140690(arg0) != 0) {
            func_8213CCEC(arg0, 0, 3, 1, 1, 0);
        }
        break;
    case 4:
        func_8213C938(arg0);
        break;
    }
    if (func_8213CB7C(arg0) != 0) {
        func_8213E488(arg0);
        func_8213F658(arg0, M2C_FIELD(arg0, f32 *, 0x74), 0.5f);
        func_82140064(arg0, M2C_FIELD(arg0, s32 *, 0x70), M2C_FIELD(arg0, s16 *, 0xAA));
    }
}

/**
 * @unverified Name from Stadium 1.
 */
void BattleAnim_SetupBubbleBubbles(Particle* arg0, s16 arg1) {
    s16 sp2E = Particle_FieldAC_GetS16_0C038(arg0);

    Particle_FieldCA_SetU8_0BECC(arg0, 7);
    Particle_Field1C_SetScaled_0B938(arg0, 0.1f);
    Particle_Field94_AddVec_0A52C(arg0, ParticleMath_RandomSigned(0xC00), ParticleMath_RandomSigned(0x1000), 0);
    ParticleGfx_RecolorEnvRandomPalette(arg0);
    Particle_Field74_SetScaled_0AD8C(arg0, (ParticleMath_RandomRange(6) * 0.5f) + 4.0f);
    Particle_FieldA6_SetS16_0BCA8(arg0, sp2E * 2);
    Particle_DisableRendering(arg0);
    Particle_AdvanceLifecycle(arg0);
}

/**
 * Spawns Bubbles for Bubble
 * @unverified Name and comment from Stadium 1.
 */
void BattleAnim_RunBubbleBubbles(Particle* arg0) {
    s16 temp_a1 = Particle_FieldCF_GetS16_0C058(arg0);

    switch (arg0->unk_B2) {
        case 1:
            BattleAnim_SetupBubbleBubbles(arg0, temp_a1);
            break;

        case 2:
            if (Particle_FieldA6_DecrementToZeroStep1AndStepState_0BDD0(arg0) != 0) {
                Particle_FieldA6_SetS16_0BCA8(arg0, ParticleMath_RandomRange(0xA) + 0x19);
                Particle_EnableRendering(arg0);
            }
            break;

        case 3:
            Particle_Field1C_Approach_0B98C(arg0, 0.15f, 0.01f);
            Particle_AddVelocityFromRotationTemplate1(arg0);
            if ((Particle_FieldA6_DecrementToZeroStep1_0BDAC(arg0) != 0) && (Particle_PrimAlpha_Approach_0BC2C(arg0, 0x20, 0x20) != 0)) {
                Particle_AdvanceLifecycle(arg0);
            }
            break;

        case 4:
            Particle_DisableAndDetach(arg0);
            break;
    }
}

/**
 * @unverified Name from Stadium 1.
 */
void BattleAnim_SetupBubbleBeamBubblesSlow(Particle* arg0) {
    UNUSED s32 pad[3]; // FAKE: stack padding
    s16 sp22 = Particle_FieldAC_GetS16_0C038(arg0);

    Particle_FieldCF_GetS16_0C058(arg0);
    Particle_Field1C_SetScaled_0B938(arg0, 0.05f);
    Particle_SetRandomVelocityXYZ(arg0, 4, 2, 2);
    Particle_Field94_AddX_0A578(arg0, ParticleMath_RandomSignedOffset(0x200, 0xE00));
    Particle_Field9A_SetX_0A3C4(arg0, ParticleMath_RandomRange(0x1000) + 0x100);
    Particle_FieldB0_SetS16_0BFEC(arg0, -0x1800 - ParticleMath_RandomRange(0x1000));
    Particle_Field94_AddY_0A594(arg0, ParticleMath_RandomSigned(0x3000));
    Particle_Field74_SetScaled_0AD8C(arg0, (ParticleMath_RandomRange(0xF) * 0.1f) + 1.0f);
    ParticleGfx_RecolorEnvRandomPalette(arg0);
    Particle_FieldA6_SetS16_0BCA8(arg0, sp22 * 2);
    Particle_DisableRendering(arg0);
    Particle_AdvanceLifecycle(arg0);
}

s32 func_8213EFF8(Particle* arg0, s32 arg1, s32 arg2);
/**
 * @unverified Name from Stadium 1.
 */
void BattleAnim_ContinueBubbleBeamBubblesSlow(Particle* arg0) {
    if (arg0->unk_B8 == 1) {
        func_8213EFF8(arg0, arg0->unk_B0, arg0->unk_9A.x);
        Particle_AddVelocityFromRotationTemplate1(arg0);
    }
}

s32 func_82137D74(M2C_UNK);                         /* extern */
M2C_UNK func_8213C930(s8 *);                      /* extern */
M2C_UNK func_8213CB3C(s8 *);                      /* extern */
s32 func_8213CB7C(s8 *);                          /* extern */
M2C_UNK func_8213CCEC(s8 *, M2C_UNK, M2C_UNK, M2C_UNK, s32, s32); /* extern */
M2C_UNK func_8213D238(s8 *);                      /* extern */
M2C_UNK func_82140228(s8 *, M2C_UNK, M2C_UNK);    /* extern */
s32 func_82140690(s8 *);                          /* extern */
s32 func_821406B4(s8 *);                          /* extern */
M2C_UNK func_82149ADC(s8 *);                      /* extern */
M2C_UNK func_82149C20(s8 *);                      /* extern */

/**
 * handles the slower additional bubbles that appear when using bubble beam as opposed to bubble
 * @unverified Name and comment from Stadium 1, matched by code similarity.
 */
void BattleAnim_RunBubbleBeamBubblesSlow(s8 *arg0) {
    s16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_82149ADC(arg0);
        break;
    case 2:
        if (func_821406B4(arg0) != 0) {
            func_8213D238(arg0);
            func_8213CB3C(arg0);
            func_82140594(arg0, (s16) (func_82137D74(0xA) + 8));
        }
        break;
    case 3:
        func_82140228(arg0, 0x3E19999A, 0x3CA3D70A);
        if (func_82140690(arg0) != 0) {
            func_8213CCEC(arg0, 0, 3, 1, 1, 0);
        }
        break;
    case 4:
        func_8213C930(arg0);
        break;
    }
    if (func_8213CB7C(arg0) != 0) {
        func_82149C20(arg0);
    }
}

/**
 * @unverified Name from Stadium 1.
 */
void BattleAnim_SetupBubbleBeamBubblesFast(Particle* arg0) {
    s16 sp56 = Particle_FieldAC_GetS16_0C038(arg0);
    f32 var_fa0;
    UNUSED s32 pad[2]; // FAKE: stack padding
    Vec3f sp3C;
    Vec3f sp30;
    s16 sp2E;

    Particle_FieldCA_SetU8_0BECC(arg0, 7);
    Particle_Field1C_SetScaled_0B938(arg0, 0.1f);
    Particle_SetScaleSpeed(arg0, 0.2f);
    Particle_SetScaleTarget(arg0, 0.02f);
    BattleAnim_GetSecondaryOwnerAnchorPosition(&sp3C);
    BattleAnim_GetTertiaryOwnerBone9Position(&sp30);
    var_fa0 = sp30.x - sp3C.x;
    if (var_fa0 <= 0.0f) {
        var_fa0 = -var_fa0;
    }
    sp2E = -MathUtil_Atan2s(var_fa0, sp30.y - sp3C.y);
    Particle_Field94_AddVec_0A52C(arg0, sp2E + ParticleMath_RandomSigned(0x800), ParticleMath_RandomSigned(0x800), 0);
    Particle_SetRandomVelocityXYZ(arg0, 4, 2, 2);
    ParticleGfx_RecolorEnvRandomPalette(arg0);
    Particle_Field74_SetScaled_0AD8C(arg0, (ParticleMath_RandomRange(6) * 0.5f) + 5.0f);
    Particle_FieldA6_SetS16_0BCA8(arg0, sp56 * 2);
    Particle_DisableRendering(arg0);
    Particle_AdvanceLifecycle(arg0);
}

s32 func_82137D74(M2C_UNK);                         /* extern */
M2C_UNK func_8213C938(s8 *);                      /* extern */
M2C_UNK func_8213CB3C(s8 *);                      /* extern */
M2C_UNK func_8213CCEC(s8 *, M2C_UNK, M2C_UNK, M2C_UNK, s32, s32); /* extern */
M2C_UNK func_8213E528(s8 *);                      /* extern */
M2C_UNK func_821402B8(s8 *);                      /* extern */
s32 func_82140690(s8 *);                          /* extern */
s32 func_821406B4(s8 *);                          /* extern */
M2C_UNK func_82149D74(s8 *);                      /* extern */

/**
 * handles the faster additional bubbles that appear when using bubble beam as opposed to bubble
 * @unverified Name and comment from Stadium 1, matched by code similarity.
 */
void BattleAnim_RunBubbleBeamBubblesFast(s8 *arg0) {
    s16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_82149D74(arg0);
        return;
    case 2:
        if (func_821406B4(arg0) != 0) {
            func_82140594(arg0, (s16) (func_82137D74(0x14) + 0xF));
            func_8213CB3C(arg0);
            return;
        }
        return;
    case 3:
        func_821402B8(arg0);
        func_8213E528(arg0);
        if (func_82140690(arg0) != 0) {
            func_8213CCEC(arg0, 0, 3, 1, 1, 0);
            return;
        }
        break;
    case 4:
        func_8213C938(arg0);
        break;
    }
}

void BattleAnim_SetupUnusedRotatingSparkVariant(Particle* arg0) {
    UNUSED s32 pad[2]; // FAKE: stack padding
    f32 temp_fv0;
    Vec3f sp40;
    Vec3f sp34;
    s16 sp32;
    s16 sp30 = Particle_FieldAC_GetS16_0C038(arg0);
    s16 sp2E = Particle_FieldCE_GetS32_0C040(arg0);

    Particle_FieldCA_SetU8_0BECC(arg0, 7);
    Particle_Field1C_SetScaled_0B938(arg0, 0.1f);
    BattleAnim_GetSecondaryOwnerAnchorPosition(&sp40);
    BattleAnim_GetTertiaryOwnerBone9Position(&sp34);

    temp_fv0 = sp34.x - sp40.x;
    if (temp_fv0 <= 0.0f) {
        temp_fv0 = -temp_fv0;
    }

    sp32 = MathUtil_Atan2s(temp_fv0, sp34.y - sp40.y) * -1;
    Particle_Field94_AddY_0A594(arg0, ParticleMath_RandomSigned(0x400));

    switch (sp2E) {
        case 0:
            Particle_FieldAE_SetS16_0BF4C(arg0, sp32 + 0x800);
            Particle_FieldB0_SetS16_0BFEC(arg0, 0x1800);
            break;

        case 1:
            Particle_FieldAE_SetS16_0BF4C(arg0, sp32 - 0x1000);
            Particle_FieldB0_SetS16_0BFEC(arg0, 0x1000);
            break;

        case 2:
            Particle_FieldAE_SetS16_0BF4C(arg0, sp32 + 0xC00);
            Particle_FieldB0_SetS16_0BFEC(arg0, -0x1400);
            break;

        case 3:
            Particle_FieldAE_SetS16_0BF4C(arg0, sp32 - 0xA00);
            Particle_FieldB0_SetS16_0BFEC(arg0, -0x2000);
            break;
    }

    Particle_Field74_SetScaled_0AD8C(arg0, 5.25f);
    ParticleGfx_RecolorEnvRandomPalette(arg0);
    Particle_FieldA6_SetS16_0BCA8(arg0, sp30 * 2);
    Particle_DisableRendering(arg0);
    Particle_AdvanceLifecycle(arg0);
}

void BattleAnim_MotionUnusedRotatingSparkVariant(Particle* arg0) {
    switch (arg0->unk_B8) {
        case 1:
            if (Particle_TickPhaseTimer(arg0, 2) != 0) {
                Particle_AdvancePhase(arg0);
                Particle_Field94_AddX_0A578(arg0, arg0->unk_AE);
            }
            break;

        case 2:
            Particle_Field94_AddZ_0A5B0(arg0, arg0->unk_B0);
            break;
    }

    if (arg0->unk_B8 > 0) {
        Particle_AddVelocityFromRotationTemplate5(arg0);
    }
}

M2C_UNK func_8213C930(s8 *);                      /* extern */
M2C_UNK func_8213CB3C(s8 *);                      /* extern */
s32 func_8213CB7C(s8 *);                          /* extern */
M2C_UNK func_8213D238(s8 *);                      /* extern */
M2C_UNK func_82140594(s8 *, M2C_UNK);             /* extern */
s32 func_821406B4(s8 *);                          /* extern */
M2C_UNK func_82149FD8(s8 *);                      /* extern */
M2C_UNK func_8214A190(s8 *);                      /* extern */

void func_8214A220(s8 *arg0) {
    s16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_82149FD8(arg0);
        break;
    case 2:
        if (func_821406B4(arg0) != 0) {
            func_8213D238(arg0);
            func_8213CB3C(arg0);
            func_82140594(arg0, 0x1E);
        }
        break;
    case 3:
        func_821406B4(arg0);
        break;
    case 4:
        func_8213C930(arg0);
        break;
    }
    if (func_8213CB7C(arg0) != 0) {
        func_8214A190(arg0);
    }
}

void BattleAnim_SetupUnusedAimedSparkVariant(Particle* arg0) {
    s16 sp4E = Particle_FieldCE_GetS32_0C040(arg0);
    Vec3f sp40;
    Vec3f sp34;
    s16 temp_v1;

    Particle_FieldCA_SetU8_0BECC(arg0, 7);
    Particle_Field1C_SetScaled_0B938(arg0, 0.1f);
    Particle_SetScaleSpeed(arg0, 0.1f);
    BattleAnim_GetSecondaryOwnerAnchorPosition(&sp40);
    BattleAnim_GetTertiaryOwnerBone9Position(&sp34);

    temp_v1 = ParticleMath_AngleXBetweenPoints(sp40, sp34);

    switch (sp4E) {
        case 0:
            Particle_Field94_AddX_0A578(arg0, temp_v1 + 0x2000);
            Particle_Field94_AddY_0A594(arg0, -0x4000);
            break;

        case 1:
            Particle_Field94_AddX_0A578(arg0, temp_v1 + 0x6000);
            Particle_Field94_AddY_0A594(arg0, -0x4000);
            break;
    }

    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, Particle_FieldCF_GetS16_0C058(arg0));
    Particle_AdvanceLifecycle(arg0);
}

void BattleAnim_CallbackUnusedAimedSparkVariant(Particle* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            BattleAnim_SetupUnusedAimedSparkVariant(arg0);
            break;

        case 2:
            Particle_PrimAlpha_ApproachAndStepState_0BC5C(arg0, 0xFF, 4);
            break;

        case 3:
            Particle_TickDelayAndAdvanceLifecycle(arg0, 0x46);
            break;

        case 4:
            Particle_PrimAlpha_ApproachAndStepState_0BC5C(arg0, 0, 0x10);
            break;

        case 5:
            Particle_DisableAndDetach(arg0);
            break;
    }

    Particle_Field1C_Approach_0B98C(arg0, 50.0f, 0.2f);
    Particle_Field20_Approach_0BA84(arg0, 1.0f, 0.1f);
}

/**
 * @unverified Name from Stadium 1.
 */
void BattleAnim_SetupWaterGunAndHydroPumpEmitterFade(Particle* arg0) {
    switch (Particle_FieldCE_GetS32_0C040(arg0)) {
        case 0:
            Particle_Field1C_SetScaled_0B938(arg0, 0.5f);
            Particle_SetScaleSpeed(arg0, 1.2f);
            Particle_SetScaleTarget(arg0, 0.1f);
            break;

        case 1:
            Particle_Field1C_SetScaled_0B938(arg0, 0.3f);
            Particle_SetScaleSpeed(arg0, 0.8f);
            Particle_SetScaleTarget(arg0, 0.05f);
            break;
    }

    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, 0x26);
    Particle_AdvanceLifecycle(arg0);
}

/**
 * Handles the fading of the burst emitters for Water Gun and Hydro Pump
 * @unverified Name and comment from Stadium 1.
 */
void BattleAnim_RunWaterGunAndHydroPumpEmitterFade(Particle* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            BattleAnim_SetupWaterGunAndHydroPumpEmitterFade(arg0);
            break;

        case 2:
            Particle_Field1C_ApproachField24ByField20_0BA1C(arg0);
            func_8213CCEC(arg0, 0, 7, 1, 2, 0);
            Particle_PrimAlpha_Approach_0BC2C(arg0, 0x20, 8);
            break;

        case 3:
            Particle_MarkInactive(arg0);
            break;
    }
}

/**
 * @unverified Name from Stadium 1.
 */
void BattleAnim_SetupHydroPumpBurstChild(Particle* arg0) {
    UNUSED s32 pad; // FAKE: stack padding

    Particle_FieldAC_GetS16_0C038(arg0);
    Particle_Field1C_SetScaled_0B938(arg0, 0.5f);
    Particle_Field94_AddVec_0A52C(arg0, ParticleMath_RandomRange(0x10000), ParticleMath_RandomRange(0x10000), 0);
    Particle_Field74_SetScaled_0AD8C(arg0, 1.0f);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, 0x27);
    Particle_AdvanceLifecycle(arg0);
}

M2C_UNK func_8213C930(s8 *);                      /* extern */
M2C_UNK func_8213CA80(s8 *, M2C_UNK);             /* extern */
M2C_UNK func_8213D604(s8 *, M2C_UNK);             /* extern */
M2C_UNK func_8213E528(s8 *);                      /* extern */
M2C_UNK func_8213F658(s8 *, f32, f32);    /* extern */
M2C_UNK func_82140228(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_82140518(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_8214A634(s8 *);                      /* extern */

void func_8214A6B4(s8 *arg0) {
    s16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_8214A634(arg0);
        return;
    case 2:
        func_82140228(arg0, 0x3E99999A, 0x3D4CCCCD);
        func_82140518(arg0, 0x20, 0x10);
        func_8213F658(arg0, 0.5f, 0.05f);
        func_8213E528(arg0);
        func_8213D604(arg0, 0xBF800000);
        func_8213CA80(arg0, 0x10);
        return;
    case 3:
        func_8213C930(arg0);
        return;
    }
}

/**
 * @unverified Name from Stadium 1.
 */
void BattleAnim_SetupHydroPumpMetadataBurstChild(Particle* arg0) {
    s16 sp26 = Particle_FieldCE_GetS32_0C040(arg0);

    Particle_Field1C_SetScaled_0B938(arg0, 0.6f);

    if (sp26 == 1) {
        Particle_Field38_AddXZFromField94YOffset180_08F38(arg0, 6.0f);
    }

    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, 0x28);
    Particle_SetPrimAlpha(arg0, 0xC8);
    Particle_AdvanceLifecycle(arg0);
}

M2C_UNK func_8213C938(s8 *);                      /* extern */
M2C_UNK func_8213C9D0(s8 *);                      /* extern */
M2C_UNK func_82140228(s8 *, M2C_UNK, M2C_UNK);    /* extern */
s32 func_82140518(s8 *, M2C_UNK, M2C_UNK);        /* extern */
M2C_UNK func_8214A77C(s8 *);                      /* extern */

void func_8214A7F4(s8 *arg0) {
    s16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_8214A77C(arg0);
        break;
    case 2:
        if (func_82140518(arg0, 0x80, 0x20) != 0) {
            func_8213C9D0(arg0);
        }
        break;
    case 3:
        func_8213C938(arg0);
        break;
    }
    func_82140228(arg0, 0x3EB33333, 0x3D4CCCCD);
}

/**
 * @unverified Name from Stadium 1.
 */
void BattleAnim_SetupHydroPumpBurstEmitter(Particle* arg0) {
    Particle_Field1C_SetScaled_0B938(arg0, 0.7f);
    Particle_Field74_SetScaled_0AD8C(arg0, 12.0f);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, 0x28);
    Particle_SetPrimAlpha(arg0, 0xFF);
    Particle_AdvanceLifecycle(arg0);
}

/**
 * Emits metadata-controlled particles and child projectiles for Hydro Pump
 * @unverified Name and comment from Stadium 1.
 */
void BattleAnim_RunHydroPumpBurstEmitter(Particle* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            BattleAnim_SetupHydroPumpBurstEmitter(arg0);
            break;

        case 2:
            BattleAnim_EmitParticleBurstWithMetadata(arg0, BattleAnim_CallbackStartEffect58Descriptor08MetadataBurstChild, &gBattleAnimParticleDescriptors[8], 1, 0, 0);
            BattleAnim_EmitParticleBurstWithMetadata(arg0, BattleAnim_CallbackStartEffect58Descriptor08MetadataBurstChild, &gBattleAnimParticleDescriptors[8], 1, 0, 1);
            BattleAnim_EmitParticleBurst(arg0, BattleAnim_CallbackStartEffect58Descriptor0ABurstChild, &gBattleAnimParticleDescriptors[0xA], 4);
            Particle_TickDelayAndAdvanceLifecycle(arg0, 0x14);
            break;

        case 3:
            Particle_DisableAndDetach(arg0);
            break;
    }

    Particle_AddVelocityFromRotationTemplate1(arg0);
}

/**
 * @unverified Name from Stadium 1.
 */
void BattleAnim_SetupWaterGunProjectileChild(Particle* arg0) {
    UNUSED s32 pad; // FAKE: stack padding

    Particle_FieldAC_GetS16_0C038(arg0);
    Particle_Field1C_SetScaled_0B938(arg0, 0.2f);
    Particle_Field94_AddVec_0A52C(arg0, ParticleMath_RandomRange(0x10000), ParticleMath_RandomRange(0x10000), 0);
    Particle_Field74_SetScaled_0AD8C(arg0, 0.5f);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, 0x27);
    Particle_AdvanceLifecycle(arg0);
}

M2C_UNK func_8213C930(s8 *);                      /* extern */
M2C_UNK func_8213CA80(s8 *, M2C_UNK);             /* extern */
M2C_UNK func_8213D604(s8 *, M2C_UNK);             /* extern */
M2C_UNK func_8213E528(s8 *);                      /* extern */
M2C_UNK func_82140228(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_82140518(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_8214A9DC(s8 *);                      /* extern */

void func_8214AA60(s8 *arg0) {
    s16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_8214A9DC(arg0);
        return;
    case 2:
        func_82140228(arg0, 0x3DCCCCCD, 0x3CA3D70A);
        func_82140518(arg0, 0x20, 0xC);
        func_8213E528(arg0);
        func_8213D604(arg0, 0xBF000000);
        func_8213CA80(arg0, 0x10);
        return;
    case 3:
        func_8213C930(arg0);
        return;
    }
}

/**
 * @unverified Name from Stadium 1.
 */
void BattleAnim_SetupWaterGunProjectileMetadata(Particle* arg0) {
    s16 sp26 = Particle_FieldCE_GetS32_0C040(arg0);

    Particle_Field1C_SetScaled_0B938(arg0, 0.2f);

    switch (sp26) {
        case 1:
            Particle_Field38_AddXZFromField94YOffset180_08F38(arg0, 3.0f);
            break;

        case 2:
            Particle_Field38_AddXZFromField94YOffset180_08F38(arg0, 6.0f);
            break;
    }

    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, 0x28);
    Particle_SetPrimAlpha(arg0, 0xC8);
    Particle_AdvanceLifecycle(arg0);
}

M2C_UNK func_8213C938(s8 *);                      /* extern */
M2C_UNK func_8213C9D0(s8 *);                      /* extern */
M2C_UNK func_82140228(s8 *, M2C_UNK, M2C_UNK);    /* extern */
s32 func_82140518(s8 *, M2C_UNK, M2C_UNK);        /* extern */
M2C_UNK func_8214AB14(s8 *);                      /* extern */

void func_8214ABAC(s8 *arg0) {
    s16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_8214AB14(arg0);
        break;
    case 2:
        if (func_82140518(arg0, 0x80, 0x20) != 0) {
            func_8213C9D0(arg0);
        }
        break;
    case 3:
        func_8213C938(arg0);
        break;
    }
    func_82140228(arg0, 0x3DCCCCCD, 0x3CA3D70A);
}

/**
 * @unverified Name from Stadium 1.
 */
void BattleAnim_SetupWaterGunProjectile(Particle* arg0) {
    Particle_Field1C_SetScaled_0B938(arg0, 0.2f);
    Particle_Field74_SetScaled_0AD8C(arg0, 10.0f);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, 0x28);
    Particle_SetPrimAlpha(arg0, 0xFF);
    Particle_AdvanceLifecycle(arg0);
}

/**
 * Handles the parent projectile for Water gun
 * @unverified Name and comment from Stadium 1.
 */
void BattleAnim_RunWaterGunProjectile(Particle* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            BattleAnim_SetupWaterGunProjectile(arg0);
            break;

        case 2:
            BattleAnim_EmitParticleBurstWithMetadata(arg0, BattleAnim_CallbackStartEffect6Descriptor08MetadataBurstChild, &gBattleAnimParticleDescriptors[8], 1, 0, 0);
            BattleAnim_EmitParticleBurstWithMetadata(arg0, BattleAnim_CallbackStartEffect6Descriptor08MetadataBurstChild, &gBattleAnimParticleDescriptors[8], 1, 0, 1);
            BattleAnim_EmitParticleBurstWithMetadata(arg0, BattleAnim_CallbackStartEffect6Descriptor08MetadataBurstChild, &gBattleAnimParticleDescriptors[8], 1, 0, 2);
            BattleAnim_EmitParticleBurst(arg0, BattleAnim_CallbackStartEffect6Descriptor0ABurstChild, &gBattleAnimParticleDescriptors[0xA], 4);
            Particle_TickDelayAndAdvanceLifecycle(arg0, 0x20);
            break;

        case 3:
            Particle_DisableAndDetach(arg0);
            break;
    }
    Particle_AddVelocityFromRotationTemplate1(arg0);
}

/**
 * @unverified Name from Stadium 1.
 */
void BattleAnim_SetupIceBeamColdBreath(Particle* arg0) {
    UNUSED s32 pad[3]; // FAKE: stack padding
    s16 sp22 = Particle_FieldAC_GetS16_0C038(arg0);
    s16 sp20 = Particle_FieldCF_GetS16_0C058(arg0);

    Particle_Field1C_SetScaled_0B938(arg0, 0.25f);
    Particle_SetRandomVelocityXYZ(arg0, 4, 2, 2);
    Particle_Field94_AddX_0A578(arg0, ParticleMath_RandomSignedOffset(0x200, -0xE00));
    Particle_Field9A_SetX_0A3C4(arg0, ParticleMath_RandomRange(0x400) + 0x100);
    Particle_FieldB0_SetS16_0BFEC(arg0, ParticleMath_RandomRange(0x1000) + 0x1000);
    Particle_Field94_AddY_0A594(arg0, ParticleMath_RandomSigned(0x1800));
    Particle_Field74_SetScaled_0AD8C(arg0, (ParticleMath_RandomRange(0x28) * 0.1f) + 1.0f);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, sp20);
    Particle_SetPrimAlpha(arg0, 0xC8);
    Particle_FieldA6_SetS16_0BCA8(arg0, sp22 * 2);
    Particle_DisableRendering(arg0);
    Particle_AdvanceLifecycle(arg0);
}

/**
 * @unverified Name from Stadium 1.
 */
void BattleAnim_ContinueIceBeamColdBreath(Particle* arg0) {
    if (arg0->unk_B8 == 1) {
        Particle_ApproachRotationXTo(arg0, arg0->unk_B0, arg0->unk_9A.x);
        Particle_AddVelocityFromRotationTemplate1(arg0);
        Particle_Field38_AddYScaled_08E90(arg0, -0.2f);
    }
}

M2C_UNK func_8213C930(s8 *);                      /* extern */
M2C_UNK func_8213CB3C(s8 *);                      /* extern */
s32 func_8213CB7C(s8 *);                          /* extern */
M2C_UNK func_8213CCEC(s8 *, M2C_UNK, M2C_UNK, M2C_UNK, s32, s32); /* extern */
M2C_UNK func_8213D238(s8 *);                      /* extern */
M2C_UNK func_82140228(s8 *, M2C_UNK, M2C_UNK);    /* extern */
s32 func_821406B4(s8 *);                          /* extern */
M2C_UNK func_8214ADB8(s8 *);                      /* extern */
M2C_UNK func_8214AF08(s8 *);                      /* extern */

void func_8214AF58(s8 *arg0) {
    s16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_8214ADB8(arg0);
        break;
    case 2:
        if (func_821406B4(arg0) != 0) {
            func_8213D238(arg0);
            func_8213CB3C(arg0);
        }
        break;
    case 3:
        func_82140228(arg0, 0x3F333333, 0x3DCCCCCD);
        func_8213CCEC(arg0, 0, 7, 1, 2, 0);
        break;
    case 4:
        func_8213C930(arg0);
        break;
    }
    if (func_8213CB7C(arg0) != 0) {
        func_8214AF08(arg0);
    }
}

/**
 * @unverified Name from Stadium 1.
 */
void BattleAnim_SetupMegaKickAndPunchProjectile(Particle* arg0) {
    s16 sp26 = Particle_FieldAC_GetS16_0C038(arg0);

    Particle_Field1C_SetScaled_0B938(arg0, 0.75f - (sp26 * 0.1f));
    Particle_Field74_SetScaled_0AD8C(arg0, 10.0f);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, 0x28);
    Particle_SetPrimAlpha(arg0, (0xFF - (sp26 << 5)) & 0xFF);
    Particle_FieldA6_SetS16_0BCA8(arg0, sp26 + 1);
    Particle_DisableRendering(arg0);
    Particle_AdvanceLifecycle(arg0);
}

/**
 * handles projectile for Mega kick and mega punch
 * @unverified Name and comment from Stadium 1.
 */
void BattleAnim_RunMegaKickAndPunchProjectile(Particle* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            BattleAnim_SetupMegaKickAndPunchProjectile(arg0);
            break;

        case 2:
            if (Particle_FieldA6_DecrementToZeroStep1AndStepState_0BDD0(arg0) != 0) {
                Particle_EnableRendering(arg0);
            }
            break;

        case 3:
            Particle_TickDelayAndAdvanceLifecycle(arg0, 0xA);
            Particle_AddVelocityFromRotationTemplate1(arg0);
            break;

        case 4:
            Particle_DisableAndDetach(arg0);
            break;
    }
}

/**
 * @unverified Name from Stadium 1.
 */
void BattleAnim_SetupInitialBeamEmanator(Particle* arg0) {
    Particle_Field1C_SetScaled_0B938(arg0, 1.0f);
    Particle_SetScaleSpeed(arg0, 2.0f);
    Particle_SetScaleTarget(arg0, 0.75f);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, Particle_FieldCF_GetS16_0C058(arg0));
    Particle_AdvanceLifecycle(arg0);
}

/**
 * Runs the first emanator that shows up in Ice Beam, Psybeam, Aurora Beam, Hyper Beam, Solar Beam, and Tri Attack.
 * Most Beam mosts switch to the Pulsing emanator after a few frames
 * @unverified Name and comment from Stadium 1.
 */
void BattleAnim_RunInitialBeamEmanator(Particle* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            BattleAnim_SetupInitialBeamEmanator(arg0);
            break;

        case 2:
            func_8213CCEC(arg0, 0, 3, 1, 1, 0);
            Particle_Field1C_ApproachField24ByField20_0BA1C(arg0);
            break;

        case 3:
            Particle_DisableAndDetach(arg0);
            break;
    }
}

/**
 * @unverified Name from Stadium 1.
 */
void BattleAnim_SetupPulsingBeamEmanator(Particle* arg0) {
    Particle_Field1C_SetScaled_0B938(arg0, 0.4f);
    Particle_SetScaleSpeed(arg0, 0.7f);
    Particle_SetScaleTarget(arg0, 0.1f);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, Particle_FieldCF_GetS16_0C058(arg0));
    Particle_SetTextureFrame(arg0, 1);
    Particle_Field94_SetZ_0A2CC(arg0, ParticleMath_RandomRange(0x10000));
    Particle_AdvanceLifecycle(arg0);
}

M2C_UNK func_8213C938(s8 *);                      /* extern */
M2C_UNK func_821401F8(s8 *, M2C_UNK);             /* extern */
M2C_UNK func_82140210(s8 *, M2C_UNK);             /* extern */
s32 func_821402E4(s8 *);                          /* extern */
s32 func_82140690(s8 *);                          /* extern */
M2C_UNK func_8214B280(s8 *);                      /* extern */

/**
 * handles the pulsing beam emanator for Ice Beam, Psybeam, Aurora Beam, Hyper Beam, and Solar Beam
 * @unverified Name and comment from Stadium 1, matched by code similarity.
 */
void BattleAnim_RunPulsingBeamEmanator(s8 *arg0) {
    s16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_8214B280(arg0);
        break;
    case 2:
        if (func_821402E4(arg0) != 0) {
            func_821401F8(arg0, 0x3E4CCCCD);
        }
        break;
    case 3:
        func_821402E4(arg0);
        break;
    case 4:
        func_821401F8(arg0, 0x3F333333);
        func_82140210(arg0, 0x3DCCCCCD);
        M2C_FIELD(arg0, s16 *, 0xAE) = 2;
        break;
    }
    if (func_82140690(arg0) != 0) {
        func_8213C938(arg0);
    }
}

/**
 * @unverified Name from Stadium 1.
 */
void BattleAnim_SetupStrongBeamHitEffect(Particle* arg0) {
    Particle_Field1C_SetScaled_0B938(arg0, 2.0f);
    Particle_Field38_AddXZFromField94YOffset180_08F38(arg0, 10.0f);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, Particle_FieldCF_GetS16_0C058(arg0));
    Particle_SetPrimAlpha(arg0, 0xFF);
    Particle_SetTextureFrame(arg0, 1);
    Particle_Field94_SetZ_0A2CC(arg0, ParticleMath_RandomRange(0x10000));
    Particle_AdvanceLifecycle(arg0);
}

/**
 * Handles the hit effect from being hit by Ice beam, Hyper Beam, Solarbeam, or Sky attack
 * @unverified Name and comment from Stadium 1.
 */
void BattleAnim_RunStrongBeamHitEffect(Particle* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            BattleAnim_SetupStrongBeamHitEffect(arg0);
            break;

        case 2:
            Particle_Field1C_ApproachAndStepState_0B9D0(arg0, 5.0f, 1.0f);
            break;

        case 3:
            Particle_Field1C_ApproachAndStepState_0B9D0(arg0, 0.0f, 1.0f);
            Particle_PrimAlpha_Approach_0BC2C(arg0, 0x40, 0x20);
            break;

        case 4:
            Particle_DisableAndDetach(arg0);
            break;
    }
}

/**
 * @unverified Name from Stadium 1.
 */
void BattleAnim_SetupPsybeamHitSparkFlicker(Particle* arg0) {
    Particle_FieldCF_GetS16_0C058(arg0);
    Particle_Field1C_SetScaled_0B938(arg0, 2.0f);
    Particle_Field38_AddXZFromField94YOffset180_08F38(arg0, 10.0f);
    ParticleGfx_RecolorPrimFromPaletteSetB(arg0, ParticleMath_RandomRange(6));
    ParticleGfx_RecolorEnvFromPaletteSetB(arg0, ParticleMath_RandomRange(6));
    Particle_SetTextureFrame(arg0, 1);
    Particle_Field94_SetZ_0A2CC(arg0, ParticleMath_RandomRange(0x10000));
    Particle_AdvanceLifecycle(arg0);
}

/**
 * handles the hit spark when being hit by psybeam
 * @unverified Name and comment from Stadium 1.
 */
void BattleAnim_RunPsybeamHitSparkFlicker(Particle* arg0) {
    Particle_FieldCF_GetS16_0C058(arg0);

    switch (arg0->unk_B2) {
        case 1:
            BattleAnim_SetupPsybeamHitSparkFlicker(arg0);
            break;

        case 2:
            Particle_Field1C_ApproachAndStepState_0B9D0(arg0, 5.0f, 1.0f);
            break;

        case 3:
            Particle_Field1C_ApproachAndStepState_0B9D0(arg0, 0.0f, 1.0f);
            Particle_PrimAlpha_Approach_0BC2C(arg0, 0x40, 0x20);
            break;

        case 4:
            Particle_DisableAndDetach(arg0);
            break;
    }

    if (gParticleFrameMod16 == 0) {
        ParticleGfx_RecolorPrimFromPaletteSetB(arg0, ParticleMath_RandomRange(6));
        ParticleGfx_RecolorEnvFromPaletteSetB(arg0, ParticleMath_RandomRange(6));
    }
}

/**
 * @unverified Name from Stadium 1.
 */
void BattleAnim_SetupAuroraBeamHitSpark(Particle* arg0) {
    UNUSED s16 pad; // FAKE: stack padding
    s16 sp24;

    Particle_FieldCF_GetS16_0C058(arg0);
    sp24 = Particle_FieldAC_GetS16_0C038(arg0);
    Particle_Field1C_SetScaled_0B938(arg0, 2.0f);
    Particle_Field38_AddXZFromField94YOffset180_08F38(arg0, 10.0f);
    ParticleGfx_RecolorPrim(arg0, 0x8);
    ParticleGfx_RecolorEnvFromPaletteSetA(arg0, sp24 % 6);
    Particle_SetTextureFrame(arg0, 1);
    Particle_FieldA6_SetS16_0BCA8(arg0, sp24 * 2);
    Particle_Field94_AddZ_0A5B0(arg0, (sp24 << 0x10) / 10);
    Particle_Field9A_SetZ_0A3EC(arg0, ParticleMath_RandomSignedOffsetBySign(0x800, 0x400));
    Particle_DisableRendering(arg0);
    Particle_AdvanceLifecycle(arg0);
}

/**
 * Handles the hit spark when being hit by aurora beam
 * @unverified Name and comment from Stadium 1.
 */
void BattleAnim_RunAuroraBeamHitSpark(Particle* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            BattleAnim_SetupAuroraBeamHitSpark(arg0);
            break;

        case 2:
            if (Particle_FieldA6_DecrementToZeroStep1AndStepState_0BDD0(arg0) != 0) {
                Particle_EnableRendering(arg0);
            }
            break;

        case 3:
            Particle_Field1C_ApproachAndStepState_0B9D0(arg0, 4.0f, 1.0f);
            break;

        case 4:
            Particle_TickDelayAndAdvanceLifecycle(arg0, 8);
            break;

        case 5:
            Particle_Field1C_ApproachAndStepState_0B9D0(arg0, 0.0f, 1.0f);
            break;

        case 6:
            Particle_DisableAndDetach(arg0);
            break;
    }

    Particle_Field94_AddXFromField9A_0A4B4(arg0);
}

/**
 * @unverified Name from Stadium 1.
 */
void BattleAnim_SetupStrongOutwardMovingLargeHitSpark(Particle* arg0) {
    Particle_FieldAC_GetS16_0C038(arg0);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, Particle_FieldCF_GetS16_0C058(arg0));
    Particle_Field1C_SetScaled_0B938(arg0, 1.35f);
    Particle_Field38_AddXZFromField94Y_08ED0(arg0, 5.0f);
    Particle_Field74_SetScaled_0AD8C(arg0, 5.5f);
    Particle_Field94_AddVec_0A52C(arg0, ParticleMath_RandomRange(0x10000), ParticleMath_RandomRange(0x10000), 0);
    Particle_AdvanceLifecycle(arg0);
}

M2C_UNK func_8213C930(s8 *);                      /* extern */
s32 func_8213C9B0(s8 *);                          /* extern */
M2C_UNK func_8213CCEC(s8 *, M2C_UNK, M2C_UNK, M2C_UNK, s32, s32); /* extern */
M2C_UNK func_8213E528(s8 *);                      /* extern */
M2C_UNK func_8213F658(s8 *, f32, f32);    /* extern */
M2C_UNK func_82140518(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_8214B84C(s8 *);                      /* extern */

/**
 * Handles hit effect shared by Hydro Pump, Ice Beam, Hyper Beam, Solar Beam, Waterfall, and Sky Attack
 * @unverified Name and comment from Stadium 1, matched by code similarity.
 */
void BattleAnim_RunStrongOutwardMovingLargeHitSpark(s8 *arg0) {
    s16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_8214B84C(arg0);
        break;
    case 2:
        func_82140518(arg0, 0x20, 0x16);
        func_8213CCEC(arg0, 0, 7, 1, 2, 0);
        break;
    case 3:
        func_8213C930(arg0);
        break;
    }
    if (func_8213C9B0(arg0) != 0) {
        func_8213F658(arg0, 3.4f, 1.0f);
        func_8213E528(arg0);
    }
}

/**
 * @unverified Name from Stadium 1.
 */
void BattleAnim_SetupBlizzardHitUpwardColdAir(Particle* arg0) {
    Particle_FieldAC_GetS16_0C038(arg0);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, Particle_FieldCF_GetS16_0C058(arg0));
    Particle_Field1C_SetScaled_0B938(arg0, 1.0f);
    Particle_Field38_AddXZFromField94Y_08ED0(arg0, 5.0f);
    Particle_Field74_SetScaled_0AD8C(arg0, 4.0f);
    Particle_Field94_AddVec_0A52C(arg0, ParticleMath_RandomRange(0x10000), ParticleMath_RandomRange(0x10000), 0);
    Particle_AdvanceLifecycle(arg0);
}

M2C_UNK func_8213C930(s8 *);                      /* extern */
s32 func_8213C9B0(s8 *);                          /* extern */
M2C_UNK func_8213CCEC(s8 *, M2C_UNK, M2C_UNK, M2C_UNK, s32, s32); /* extern */
M2C_UNK func_8213E528(s8 *);                      /* extern */
M2C_UNK func_8213F658(s8 *, f32, f32);    /* extern */
M2C_UNK func_82140518(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_8214B9A8(s8 *);                      /* extern */

/**
 * Handles the cold air that emanates upward from pokemon hit by blizzard
 * @unverified Name and comment from Stadium 1, matched by code similarity.
 */
void BattleAnim_RunBlizzardHitUpwardColdAir(s8 *arg0) {
    s16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_8214B9A8(arg0);
        break;
    case 2:
        func_82140518(arg0, 0x20, 0x16);
        func_8213CCEC(arg0, 0, 7, 1, 2, 0);
        break;
    case 3:
        func_8213C930(arg0);
        break;
    }
    if (func_8213C9B0(arg0) != 0) {
        func_8213F658(arg0, 2.5f, 0.75f);
        func_8213E528(arg0);
    }
}

/**
 * @unverified Name from Stadium 1.
 */
void BattleAnim_SetupWaterGunHitEffect(Particle* arg0) {
    Particle_FieldAC_GetS16_0C038(arg0);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, Particle_FieldCF_GetS16_0C058(arg0));
    Particle_Field1C_SetScaled_0B938(arg0, 0.6f);
    Particle_Field38_AddXZFromField94Y_08ED0(arg0, 5.0f);
    Particle_Field74_SetScaled_0AD8C(arg0, 3.0f);
    Particle_Field94_AddVec_0A52C(arg0, ParticleMath_RandomRange(0x10000), ParticleMath_RandomRange(0x10000), 0);
    Particle_AdvanceLifecycle(arg0);
}

M2C_UNK func_8213C930(s8 *);                      /* extern */
s32 func_8213C9B0(s8 *);                          /* extern */
M2C_UNK func_8213CCEC(s8 *, M2C_UNK, M2C_UNK, M2C_UNK, s32, s32); /* extern */
M2C_UNK func_8213E528(s8 *);                      /* extern */
M2C_UNK func_8213F658(s8 *, f32, f32);    /* extern */
M2C_UNK func_82140518(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_8214BAFC(s8 *);                      /* extern */

/**
 * @unverified Name from Stadium 1, matched by code similarity.
 */
void BattleAnim_RunWaterGunHitEffect(s8 *arg0) {
    s16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_8214BAFC(arg0);
        break;
    case 2:
        func_82140518(arg0, 0x20, 0x16);
        func_8213CCEC(arg0, 0, 7, 1, 2, 0);
        break;
    case 3:
        func_8213C930(arg0);
        break;
    }
    if (func_8213C9B0(arg0) != 0) {
        func_8213F658(arg0, 1.5f, 0.4f);
        func_8213E528(arg0);
    }
}

/**
 * @unverified Name from Stadium 1.
 */
void BattleAnim_SetupWeakBeamHitEffect(Particle* arg0) {
    UNUSED s32 pad; // FAKE: stack padding

    switch (Particle_FieldCF_GetS16_0C058(arg0)) {
        case 0:
            ParticleGfx_RecolorPrim(arg0, 0x8);
            ParticleGfx_RecolorEnvFromPaletteSetA(arg0, ParticleMath_RandomRange(6));
            break;

        case 1:
            ParticleGfx_RecolorPrimFromPaletteSetB(arg0, ParticleMath_RandomRange(6));
            ParticleGfx_RecolorEnvFromPaletteSetB(arg0, ParticleMath_RandomRange(6));
            break;

        case 2:
            ParticleGfx_RecolorPrimEnvFromPaletteSetB(arg0, ParticleMath_RandomRange(6));
            break;
    }

    Particle_Field1C_SetScaled_0B938(arg0, 0.8f);
    Particle_Field38_AddXZFromField94Y_08ED0(arg0, 5.0f);
    Particle_Field74_SetScaled_0AD8C(arg0, 3.0f);
    Particle_Field94_AddVec_0A52C(arg0, ParticleMath_RandomRange(0x10000), ParticleMath_RandomRange(0x10000), 0);
    Particle_AdvanceLifecycle(arg0);
}

s16 func_8213C484();                                /* extern */
M2C_UNK func_8213C930(s8 *);                      /* extern */
s32 func_8213C9B0(s8 *);                          /* extern */
M2C_UNK func_8213CCEC(s8 *, M2C_UNK, M2C_UNK, M2C_UNK, s32, s32); /* extern */
M2C_UNK func_8213E528(s8 *);                      /* extern */
M2C_UNK func_8213F658(s8 *, f32, f32);    /* extern */
M2C_UNK func_82140518(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_821434FC(s8 *, s16);                 /* extern */
M2C_UNK func_82143530(s8 *, s16);                 /* extern */
M2C_UNK func_82143564(s8 *, s16);                 /* extern */
M2C_UNK func_821435E0(s8 *, s16);                 /* extern */
M2C_UNK func_8214BC58(s8 *);                      /* extern */
extern s32 D_8219A790;

/**
 * handles shared effect being hit by Psybeam, bubble beam, and aurora beam
 * @unverified Name and comment from Stadium 1, matched by code similarity.
 */
void BattleAnim_RunWeakBeamHitEffect(s8 *arg0) {
    s16 sp2E;
    s16 temp_v1;

    sp2E = func_8213C484();
    temp_v1 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v1) {                              /* switch 1; irregular */
    case 1:                                         /* switch 1 */
        func_8214BC58(arg0);
        break;
    case 2:                                         /* switch 1 */
        func_82140518(arg0, 0x20, 0x16);
        func_8213CCEC(arg0, 0, 7, 1, 2, 0);
        break;
    case 3:                                         /* switch 1 */
        func_8213C930(arg0);
        break;
    }
    if (func_8213C9B0(arg0) != 0) {
        func_8213F658(arg0, 1.5f, 0.5f);
        func_8213E528(arg0);
        switch (sp2E) {                             /* switch 2; irregular */
        case 0:                                     /* switch 2 */
            func_821434FC(arg0, func_82137D74(6));
            return;
        case 1:                                     /* switch 2 */
            if (D_8219A790 == 0) {
                func_82143530(arg0, func_82137D74(6));
                func_82143564(arg0, func_82137D74(6));
                return;
            }
            break;
        case 2:                                     /* switch 2 */
            func_821435E0(arg0, func_82137D74(6));
            break;
        }
    }
}

/**
 * @unverified Name from Stadium 1.
 */
void BattleAnim_SetupTriAttackHitSpark(Particle* arg0) {
    s16 sp2E;
    s16 sp2C;
    s16 sp2A;

    sp2E = Particle_FieldAC_GetS16_0C038(arg0);
    sp2C = Particle_FieldCF_GetS16_0C058(arg0);
    sp2A = Particle_FieldCE_GetS32_0C040(arg0);

    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, sp2C);
    Particle_Field1C_SetScaled_0B938(arg0, 0.6f);
    Particle_SetScaleSpeed(arg0, 1.2f);
    Particle_SetScaleTarget(arg0, 0.2f);

    switch (sp2A) {
        case 0:
            Particle_SetPosition(arg0, 0.0f, 10.0f, 0.0f);
            break;

        case 1:
            Particle_SetPosition(arg0, 0.0f, -5.0f, 10.0f);
            break;

        case 2:
            Particle_SetPosition(arg0, 0.0f, -5.0f, -10.0f);
            break;
    }

    Particle_Field38_AddXZFromField94Y_08ED0(arg0, 5.0f);
    Particle_Field74_SetScaled_0AD8C(arg0, 1.0f);
    Particle_Field94_AddVec_0A52C(arg0, ParticleMath_RandomRange(0x10000), ParticleMath_RandomRange(0x10000), 0);
    Particle_FieldA6_SetS16_0BCA8(arg0, sp2E);
    Particle_DisableRendering(arg0);
    Particle_AdvanceLifecycle(arg0);
}

M2C_UNK func_8213C464();                            /* extern */
M2C_UNK func_8213C930(s8 *);                      /* extern */
M2C_UNK func_8213CB3C(s8 *);                      /* extern */
M2C_UNK func_8213CCEC(s8 *, M2C_UNK, M2C_UNK, M2C_UNK, s32, s32); /* extern */
M2C_UNK func_8213E528(s8 *);                      /* extern */
M2C_UNK func_8213F658(s8 *, f32, f32);    /* extern */
M2C_UNK func_821402B8(s8 *);                      /* extern */
M2C_UNK func_82140518(s8 *, M2C_UNK, M2C_UNK);    /* extern */
s32 func_821406B4(s8 *);                          /* extern */
M2C_UNK func_8214BEE8(s8 *);                      /* extern */

/**
 * Handles the Tri Attack hit spark
 * @unverified Name and comment from Stadium 1, matched by code similarity.
 */
void BattleAnim_RunTriAttackHitSpark(s8 *arg0) {
    s16 temp_v1;

    func_8213C464();
    temp_v1 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v1) {                              /* irregular */
    case 1:
        func_8214BEE8(arg0);
        return;
    case 2:
        if (func_821406B4(arg0) != 0) {
            func_8213CB3C(arg0);
            return;
        }
        return;
    case 3:
        func_821402B8(arg0);
        func_82140518(arg0, 0x20, 0x16);
        func_8213CCEC(arg0, 0, 7, 1, 2, 0);
        func_8213F658(arg0, 1.5f, 0.1f);
        func_8213E528(arg0);
        return;
    case 4:
        func_8213C930(arg0);
        break;
    }
}

/**
 * Handles hit effect shared by Hydro Pump, Ice Beam, Hyper Beam, Solar Beam, Waterfall, and Sky Attack
 * @unverified Name and comment from Stadium 1.
 */
void BattleAnim_SetupStrongOutwardMovingSmallHitSpark(Particle* arg0) {
    s16 sp2E = Particle_FieldAC_GetS16_0C038(arg0);
    s16 sp2C = Particle_FieldCF_GetS16_0C058(arg0);

    Particle_SetRandomVelocityXYZ(arg0, 0, 0xF, 0x14);
    Particle_Field38_AddYScaled_08E90(arg0, 5.0f);
    Particle_Field1C_SetScaled_0B938(arg0, 0.2f);
    Particle_Field74_SetScaled_0AD8C(arg0, 2.5f);
    Particle_Field94_AddVec_0A52C(arg0, ParticleMath_RandomSigned(0x2000), ParticleMath_RandomSigned(0x2000), 0);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, sp2C);
    Particle_FieldA6_SetS16_0BCA8(arg0, sp2E * 4);
    Particle_DisableRendering(arg0);
    Particle_AdvanceLifecycle(arg0);
}

M2C_UNK func_8213C938(s8 *);                      /* extern */
M2C_UNK func_8213CB3C(s8 *);                      /* extern */
M2C_UNK func_8213CCEC(s8 *, M2C_UNK, M2C_UNK, M2C_UNK, s32, s32); /* extern */
M2C_UNK func_8213E528(s8 *);                      /* extern */
M2C_UNK func_82140228(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_82140518(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_82140594(s8 *, M2C_UNK);             /* extern */
s32 func_82140690(s8 *);                          /* extern */
M2C_UNK func_8214C134(s8 *);                      /* extern */

void func_8214C208(s8 *arg0) {
    s16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_8214C134(arg0);
        return;
    case 2:
        if (func_8213CA80(arg0, M2C_FIELD(arg0, s16 *, 0xA2)) != 0) {
            func_82140594(arg0, 2);
            func_8213CB3C(arg0);
            return;
        }
        return;
    case 3:
        func_8213CCEC(arg0, 0, 7, 1, 1, 0);
        func_82140228(arg0, 0x3F000000, 0x3DCCCCCD);
        func_8213E528(arg0);
        if (func_82140690(arg0) != 0) {
            func_82140518(arg0, 0, 0x20);
            return;
        }
        break;
    case 4:
        func_8213C938(arg0);
        break;
    }
}

void BattleAnim_SetupUnusedIndexedFadeVariantA(Particle* arg0) {
    s16 sp2E = Particle_FieldAC_GetS16_0C038(arg0);

    Particle_FieldCF_GetS16_0C058(arg0);
    Particle_SetRandomVelocityXYZ(arg0, 0xA, 0x14, 0x14);
    Particle_Field1C_SetScaled_0B938(arg0, 0.25f);
    Particle_Field74_SetScaled_0AD8C(arg0, 2.5f);
    Particle_Field94_AddVec_0A52C(arg0, ParticleMath_RandomSigned(0x2000), ParticleMath_RandomSigned(0x2000), 0);
    ParticleGfx_RecolorPrimRandomPalette(arg0);
    Particle_SetPrimAlpha(arg0, 0xC8);
    Particle_FieldA6_SetS16_0BCA8(arg0, sp2E * 4);
    Particle_DisableRendering(arg0);
    Particle_AdvanceLifecycle(arg0);
}

M2C_UNK func_8213C930(s8 *);                      /* extern */
M2C_UNK func_8213CB3C(s8 *);                      /* extern */
M2C_UNK func_8213CCEC(s8 *, M2C_UNK, M2C_UNK, M2C_UNK, s32, s32); /* extern */
M2C_UNK func_8213E528(s8 *);                      /* extern */
M2C_UNK func_82140228(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_82140518(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_82140594(s8 *, M2C_UNK);             /* extern */
s32 func_82140690(s8 *);                          /* extern */
M2C_UNK func_8214C300(s8 *);                      /* extern */

void func_8214C3C8(s8 *arg0) {
    s16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_8214C300(arg0);
        return;
    case 2:
        if (func_8213CA80(arg0, M2C_FIELD(arg0, s16 *, 0xA2)) != 0) {
            func_82140594(arg0, 2);
            func_8213CB3C(arg0);
            return;
        }
        return;
    case 3:
        func_8213CCEC(arg0, 0, 7, 1, 1, 0);
        func_82140228(arg0, 0x3ECCCCCD, 0x3DCCCCCD);
        func_8213E528(arg0);
        if (func_82140690(arg0) != 0) {
            func_82140518(arg0, 0, 0x20);
            return;
        }
        break;
    case 4:
        func_8213C930(arg0);
        break;
    }
}

void BattleAnim_SetupUnusedIndexedFadeVariantB(Particle* arg0) {
    s16 sp2E = Particle_FieldAC_GetS16_0C038(arg0);

    Particle_FieldCF_GetS16_0C058(arg0);
    Particle_SetRandomVelocityXYZ(arg0, 0xA, 0x14, 0x14);
    Particle_Field1C_SetScaled_0B938(arg0, 0.4f);
    Particle_Field74_SetScaled_0AD8C(arg0, 2.5f);
    Particle_Field94_AddVec_0A52C(arg0, ParticleMath_RandomSigned(0x2000), ParticleMath_RandomSigned(0x2000), 0);
    Particle_SetPrimColor(arg0, 0xFF, 0xFF, 0xFF);
    ParticleGfx_RecolorEnvRandomPalette(arg0);
    Particle_FieldA6_SetS16_0BCA8(arg0, sp2E * 4);
    Particle_DisableRendering(arg0);
    Particle_AdvanceLifecycle(arg0);
}

M2C_UNK func_8213C930(s8 *);                      /* extern */
M2C_UNK func_8213CB3C(s8 *);                      /* extern */
M2C_UNK func_8213CBFC(s8 *, M2C_UNK);             /* extern */
M2C_UNK func_8213CCEC(s8 *, M2C_UNK, M2C_UNK, M2C_UNK, s32, s32); /* extern */
M2C_UNK func_8213E528(s8 *);                      /* extern */
M2C_UNK func_82140228(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_8214C4C4(s8 *);                      /* extern */

void func_8214C598(s8 *arg0) {
    s16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_8214C4C4(arg0);
        return;
    case 2:
        if (func_8213CA80(arg0, M2C_FIELD(arg0, s16 *, 0xA2)) != 0) {
            func_8213CB3C(arg0);
            func_8213CBFC(arg0, 1);
            return;
        }
        return;
    case 3:
        func_82140228(arg0, 0x3F000000, 0x3CCCCCCD);
        func_8213CCEC(arg0, 2, 7, 1, 1, 0);
        func_8213E528(arg0);
        return;
    case 4:
        func_8213C930(arg0);
        break;
    }
}

/**
 * @unverified Name from Stadium 1.
 */
void BattleAnim_SetupBubbleBubbleBeamSharedEffect(Particle* arg0) {
    Vec3s sp28;
    UNUSED s16 pad; // FAKE: stack padding
    s16 sp24;

    Particle_FieldCF_GetS16_0C058(arg0);
    sp24 = Particle_FieldAC_GetS16_0C038(arg0);
    Particle_Field1C_SetScaled_0B938(arg0, 0.05f);
    Particle_SetRotationTargetXY(arg0, arg0->unk_94.x, arg0->unk_94.y + 0x8000);
    Particle_Field9A_SetXY_0A3A0(arg0, 0x800, 0x300);
    sp28.x = sp24 << 0xC;
    sp28.y = ParticleMath_RandomSignedOffsetBySign(0x3000, 0x1000);
    sp28.z = 0;
    Particle_Field94_AddVecFromVec3s_0A4F0(arg0, sp28);
    ParticleGfx_RecolorEnvRandomPalette(arg0);
    Particle_FieldA6_SetS16_0BCA8(arg0, ParticleMath_RandomRange(0x10) + 8);
    Particle_Field74_SetScaled_0AD8C(arg0, 4.0f);
    Particle_AdvanceLifecycle(arg0);
}

void BattleAnim_CallbackEndEffects34And53Descriptor45RotatingBounceFade(Particle* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            BattleAnim_SetupBubbleBubbleBeamSharedEffect(arg0);
            break;

        case 2:
            Particle_Field1C_Approach_0B98C(arg0, 0.15f, 0.01f);
            func_8213F658(arg0, 1.0f, 0.7f);
            Particle_ApproachRotationTargetY(arg0);
            if (Particle_FieldA6_DecrementToZeroStep1AndStepState_0BDD0(arg0) != 0) {
                Particle_FieldA6_SetS16_0BCA8(arg0, ParticleMath_RandomRangeOffset(0xC, 0x20));
                if (arg0->unk_94.y >= arg0->unk_A0.y) {
                    Particle_FieldA0_SetX_0A400(arg0, -0x4000);
                } else {
                    Particle_FieldA0_SetX_0A400(arg0, 0x4000);
                }
            }
            break;

        case 3:
            Particle_ApproachRotationTargetX(arg0);
            func_8213F658(arg0, 0.5f, 0.2f);
            Particle_FieldA6_DecrementToZeroStep1AndStepState_0BDD0(arg0);
            break;

        case 4:
            Particle_ApproachRotationTargetX(arg0);
            func_8213CCEC(arg0, 0, 3, 1, 1, 0);
            break;

        case 5:
            Particle_MarkInactive(arg0);
            break;
    }

    if (Particle_IsRunning(arg0) != 0) {
        Particle_AddVelocityFromRotationTemplate3(arg0);
    }
}

/**
 * @unverified Name from Stadium 1.
 */
void BattleAnim_SetupHydroPumpColorShiftFade(Particle* arg0) {
    Particle_Field1C_SetScaled_0B938(arg0, 0.2f);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, Particle_FieldCF_GetS16_0C058(arg0));
    Particle_SetPrimAlpha(arg0, 0xC8);
    Particle_FieldA6_SetS16_0BCA8(arg0, 0x18);
    arg0->unk_74 = 0.02f;
    Particle_AdvanceLifecycle(arg0);
}

M2C_UNK func_82137AB4(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_8213C930(s8 *);                      /* extern */
M2C_UNK func_82140228(s8 *, M2C_UNK, s32);        /* extern */
M2C_UNK func_82140380(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_821403B0(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_821403E0(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_8214047C(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_821404AC(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_821404DC(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_82140548(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_821406B4(s8 *);                      /* extern */
M2C_UNK func_8214C8E0(s8 *);                      /* extern */

/**
 * Handles the growth, color shift, and fade of a Hydro Pump particle
 * @unverified Name and comment from Stadium 1, matched by code similarity.
 */
void BattleAnim_RunHydroPumpColorShiftFade(s8 *arg0) {
    s16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_8214C8E0(arg0);
        return;
    case 2:
        func_82140228(arg0, 0x40000000, 0x3CA3D70A);
        func_821404DC(arg0, 0xC8, 2);
        func_821406B4(arg0);
        return;
    case 3:
        func_82137AB4(arg0 + 0x70, 0x3C03126F, 0x3A83126F);
        func_82140228(arg0, 0x40000000, M2C_FIELD(arg0, s32 *, 0x70));
        func_82140380(arg0, 0x78, 8);
        func_821403E0(arg0, 0x96, 8);
        func_821403B0(arg0, 0x96, 8);
        func_8214047C(arg0, 0x78, 8);
        func_821404AC(arg0, 0x96, 8);
        func_821404DC(arg0, 0x96, 8);
        func_82140548(arg0, 0, 0xC);
        return;
    case 4:
        func_8213C930(arg0);
        return;
    }
}

/**
 * @unverified Name from Stadium 1.
 */
void BattleAnim_SetupWaterGunEmitterColoration(Particle* arg0) {
    s16 sp26 = Particle_FieldCE_GetS32_0C040(arg0);

    Particle_Field1C_SetScaled_0B938(arg0, 0.05f);
    Particle_SetScaleSpeed(arg0, 0.3f);
    Particle_SetScaleTarget(arg0, 0.005f);

    switch (sp26) {
        case 0:
            Particle_Field94_SetY_0A2B8(arg0, 0);
            break;

        case 1:
            Particle_Field94_SetY_0A2B8(arg0, 0x5500);
            break;

        case 2:
            Particle_Field94_SetY_0A2B8(arg0, -0x5600);
            break;
    }

    Particle_AddVelocityFromDirVector(arg0, 10.0f);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, Particle_FieldCF_GetS16_0C058(arg0));
    Particle_SetPrimAlpha(arg0, 0xC8);
    Particle_FieldA6_SetS16_0BCA8(arg0, 0x18);
    Particle_AdvanceLifecycle(arg0);
}

M2C_UNK func_8213C930(s8 *);                      /* extern */
M2C_UNK func_821402B8(s8 *);                      /* extern */
M2C_UNK func_82140380(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_821403B0(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_821403E0(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_8214047C(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_821404AC(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_821404DC(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_82140548(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_821406B4(s8 *);                      /* extern */
M2C_UNK func_8214CA90(s8 *);                      /* extern */

/**
 * Handles the coloring of the burst emitter for Water gun
 * @unverified Name and comment from Stadium 1, matched by code similarity.
 */
void BattleAnim_RunWaterGunEmitterColoration(s8 *arg0) {
    s16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_8214CA90(arg0);
        break;
    case 2:
        func_821404DC(arg0, 0xC8, 2);
        func_821406B4(arg0);
        break;
    case 3:
        func_82140380(arg0, 0x78, 8);
        func_821403E0(arg0, 0x96, 8);
        func_821403B0(arg0, 0x96, 8);
        func_8214047C(arg0, 0x78, 8);
        func_821404AC(arg0, 0x96, 8);
        func_821404DC(arg0, 0x96, 8);
        func_82140548(arg0, 0, 0xC);
        break;
    case 4:
        func_8213C930(arg0);
        break;
    }
    func_821402B8(arg0);
}

/**
 * @unverified Name from Stadium 1.
 */
void BattleAnim_SetupHydroPumpWaterGunProjectileHit(Particle* arg0) {
    UNUSED s16 pad; // FAKE: stack padding
    s16 sp2C;

    Particle_FieldAC_GetS16_0C038(arg0);
    sp2C = Particle_FieldCF_GetS16_0C058(arg0);
    Particle_Field1C_SetScaled_0B938(arg0, 0.5f);
    Particle_Field94_AddVec_0A52C(arg0, ParticleMath_RandomRange(0x10000), ParticleMath_RandomRange(0x10000), 0);
    Particle_Field38_AddXZFromField94Y_08ED0(arg0, 5.0f);
    Particle_Field74_SetScaled_0AD8C(arg0, 1.0f);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, sp2C);
    Particle_AdvanceLifecycle(arg0);
}

M2C_UNK func_8213C930(s8 *);                      /* extern */
M2C_UNK func_8213CA80(s8 *, M2C_UNK);             /* extern */
M2C_UNK func_8213D604(s8 *, M2C_UNK);             /* extern */
M2C_UNK func_8213E528(s8 *);                      /* extern */
M2C_UNK func_82140228(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_82140518(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_8214CC90(s8 *);                      /* extern */

/**
 * Handles the projectile shared by being hit by water gun and hydro pump
 * @unverified Name and comment from Stadium 1, matched by code similarity.
 */
void BattleAnim_RunHydroPumpWaterGunProjectileHit(s8 *arg0) {
    s16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_8214CC90(arg0);
        break;
    case 2:
        func_82140228(arg0, 0x3E99999A, 0x3CA3D70A);
        func_82140518(arg0, 0x20, 0xC);
        func_8213E528(arg0);
        func_8213D604(arg0, 0xBF800000);
        func_8213CA80(arg0, 0x10);
        break;
    case 3:
        func_8213C930(arg0);
        break;
    }
    if (M2C_FIELD(arg0, f32 *, 0x2C) < 0.0f) {
        func_8213C930(arg0);
    }
}

/**
 * Starts the effect for Mega Punch
 * @unverified Name and comment from Stadium 1.
 */
void BattleAnim_StartMegaPunchEffect(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(4, BattleAnim_RunMegaKickAndPunchProjectile, &gBattleAnimParticleDescriptors[8], 0, 4, 0x11, gBattleAnimCurrentAnchor, 0, 0);
}

M2C_UNK func_8213B560(M2C_UNK, M2C_UNK *, M2C_UNK *, M2C_UNK, s32, s32, s32, s32, s32); /* extern */
extern M2C_UNK D_8218E5C8;
extern s16 D_8219A80A;
extern M2C_UNK func_8214B0FC;

void func_8214CE58(void) {
    func_8213B560(0, &func_8214B0FC, &D_8218E5C8, 0, 4, 0x11, (s32) D_8219A80A, 0, 0);
}

M2C_UNK func_8213B5D8(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK *, M2C_UNK *, s32, s32, s32, s32, s32, s32); /* extern */
extern M2C_UNK D_8218E7A8;
extern s16 D_8219A80A;
extern M2C_UNK func_821499D4;

void func_8214CEB0(void) {
    func_8213B5D8(0, 1, 0x3C, &func_821499D4, &D_8218E7A8, 0, 1, 0x11, (s32) D_8219A80A, 0, 0);
}

extern ParticleDescriptor D_8218E580[86];
extern M2C_UNK D_8218E728;
void InitParticleEffectGroup_Basic(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_RunDefaultHitSpark, &D_8218E728, 0, 1, 0x11, 9, 3, 5);
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_CallbackEndEffects34And53Descriptor45RotatingBounceFade, &D_8218E7A8, 0, 0x10, 0x11, 9, 0, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(8, BattleAnim_CallbackEndEffects34And53Descriptor45RotatingBounceFade, &D_8218E7A8, 0, 0x10, 0x11, 9, 0, 0);
}

/**
 * initializes water gun
 * @unverified Name and comment from Stadium 1.
 */
void BattleAnim_InitializeWaterGunUse(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(3, BattleAnim_RunWaterGunAndHydroPumpEmitterFade, &gBattleAnimParticleDescriptors[0xE], 0, 1, 0x11, gBattleAnimCurrentAnchor, 0, 1);
    BattleAnim_CreateEffectSlotForCurrentOwner(3, BattleAnim_RunWaterGunAndHydroPumpEmitterFade, &gBattleAnimParticleDescriptors[0x19], 0, 1, 0x11, gBattleAnimCurrentAnchor, 0, 1);
    BattleAnim_CreateEffectSlotForCurrentOwner(4, BattleAnim_RunWaterGunProjectile, &gDefaultParticleDescriptor, 0, 1, 0x11, gBattleAnimCurrentAnchor, 0, 0);
}

extern M2C_UNK D_8218E650;
extern M2C_UNK D_8218E7D8;
extern M2C_UNK D_8218E5D8;
void InitComplexParticleSequence(void) {
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0, 1, 0xF, BattleAnim_CallbackEndEffect2Descriptor19AnimatedAlphaFade, &D_8218E650, 0, 1, 0x10, gBattleAnimCurrentAnchor, 0x26, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(0xC, BattleAnim_CallbackEndEffect2Descriptor4BModeColorShiftFade, &D_8218E7D8, 0, 1, 0xA, 0, 0x4C, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(0xC, BattleAnim_CallbackEndEffect2Descriptor4BModeColorShiftFade, &D_8218E7D8, 0, 1, 0xA, 0, 0x4C, 1);
    BattleAnim_CreateEffectSlotForCurrentOwner(0xC, BattleAnim_CallbackEndEffect2Descriptor4BModeColorShiftFade, &D_8218E7D8, 0, 1, 0xA, 0, 0x4C, 2);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(4, 1, 0x10, BattleAnim_CallbackEndEffects2And27Descriptor0AFallingSparkFade, &D_8218E5D8, 0, 2, 0x11, gBattleAnimCurrentAnchor, 0x4C, 0);
}

/**
 * initializes hydro pump
 * @unverified Name and comment from Stadium 1.
 */
void BattleAnim_InitializeHydroPumpUse(void) {
    BattleAnim_SpawnGlobalTintColorFadeDetach(0, 0x40, 6);
    BattleAnim_CreateEffectSlotForCurrentOwner(3, BattleAnim_RunWaterGunAndHydroPumpEmitterFade, &gBattleAnimParticleDescriptors[0xE], 0, 1, 0x11, gBattleAnimCurrentAnchor, 0, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(3, BattleAnim_RunWaterGunAndHydroPumpEmitterFade, &gBattleAnimParticleDescriptors[0x19], 0, 1, 0x11, gBattleAnimCurrentAnchor, 0, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(4, BattleAnim_RunHydroPumpBurstEmitter, &gBattleAnimParticleDescriptors[8], 0, 1, 0x11, gBattleAnimCurrentAnchor, 0, 0);
}

M2C_UNK func_8213B560(M2C_UNK, M2C_UNK *, M2C_UNK *, M2C_UNK, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_8213B5D8(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK *, M2C_UNK *, s32, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_8213BD78(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, s32); /* extern */
extern M2C_UNK D_8218E5A8;
extern M2C_UNK D_8218E5D8;
extern M2C_UNK D_8218E650;
extern M2C_UNK D_8218E7D8;
extern s16 D_8219A80A;
extern M2C_UNK func_82145998;

/**
 * initializes hydro pump
 * @unverified Name and comment from Stadium 1, matched by code similarity.
 */
void BattleAnim_InitializeHydroPumpHit(void) {
    func_8213BD78(4, 8, 0x33, 0x10, 0xFF);
    func_8213B560(0, &func_82145998, &D_8218E5A8, 0, 1, 0x10, (s32) D_8219A80A, 0x33, 0);
    func_8213B5D8(0, 5, 3, &BattleAnim_RunStrongOutwardMovingLargeHitSpark, &D_8218E650, 0, 8, 0x10, (s32) D_8219A80A, 0x26, 0);
    func_8213B5D8(0xA, 1, 8, &func_8214C208, &D_8218E650, 0, 3, 0x11, (s32) D_8219A80A, 0x26, 0);
    func_8213B560(0xC, &BattleAnim_RunHydroPumpColorShiftFade, &D_8218E7D8, 0, 1, 0xA, 0, 0x4C, 0);
    func_8213B5D8(2, 1, 0x10, &BattleAnim_RunHydroPumpWaterGunProjectileHit, &D_8218E5D8, 0, 4, 0x11, (s32) D_8219A80A, 0x4C, 0);
}

M2C_UNK func_8213B560(M2C_UNK, M2C_UNK *, M2C_UNK *, M2C_UNK, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_8213B5D8(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK *, M2C_UNK *, s32, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_8213B644(M2C_UNK, M2C_UNK, M2C_UNK);   /* extern */
M2C_UNK func_8213B6AC(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, s32); /* extern */
extern M2C_UNK D_8218E7D0;
extern M2C_UNK D_8218E818;
extern s16 D_8219A80A;
extern M2C_UNK func_8214B1F8;

/**
 * initializes ice beam
 * @unverified Name and comment from Stadium 1, matched by code similarity.
 */
void BattleAnim_InitializeIceBeamUse(void) {
    func_8213B6AC(0, 0, 0x20, 8, 0xA0);
    func_8213B644(0, 8, 0x33);
    func_8213B560(0, &func_8214B1F8, &D_8218E818, 0, 1, 0x10, (s32) D_8219A80A, 0x40, 0);
    func_8213B560(6, &BattleAnim_RunPulsingBeamEmanator, &D_8218E818, 0x6E, 1, 0x10, (s32) D_8219A80A, 0x40, 1);
    func_8213B5D8(0, 3, 0x1E, &func_8214AF58, &D_8218E7D0, 0, 1, 0x11, (s32) D_8219A80A, 0x13, 0);
}

M2C_UNK func_8213B560(M2C_UNK, M2C_UNK *, M2C_UNK *, M2C_UNK, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_8213B644(M2C_UNK, M2C_UNK, M2C_UNK);   /* extern */
M2C_UNK func_8213B6AC(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, s32); /* extern */
extern M2C_UNK D_8218E818;
extern s16 D_8219A80A;
extern M2C_UNK func_8214B1F8;

void func_8214D5E4(void) {
    func_8213B6AC(0, 0, 0x20, 8, 0xA0);
    func_8213B644(0, 8, 6);
    func_8213B560(0, &func_8214B1F8, &D_8218E818, 0, 1, 0x10, (s32) D_8219A80A, 0xD, 0);
    func_8213B560(6, &BattleAnim_RunPulsingBeamEmanator, &D_8218E818, 0x46, 1, 0x10, (s32) D_8219A80A, 0xD, 1);
}

M2C_UNK func_8213B5D8(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK *, M2C_UNK *, s32, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_8213B644(M2C_UNK, M2C_UNK, M2C_UNK);   /* extern */
extern M2C_UNK D_8218E7A8;
extern s16 D_8219A80A;

void func_8214D6B4(void) {
    func_8213B644(0, 8, 6);
    func_8213B5D8(0, 1, 0x3C, &BattleAnim_RunBubbleBeamBubblesFast, &D_8218E7A8, 0, 4, 0x11, (s32) D_8219A80A, 0, 0);
    func_8213B5D8(0, 1, 0x3C, &BattleAnim_RunBubbleBeamBubblesSlow, &D_8218E7A8, 0, 1, 0x11, (s32) D_8219A80A, 0, 0);
}

M2C_UNK func_8213B560(M2C_UNK, M2C_UNK *, M2C_UNK *, M2C_UNK, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_8213B644(M2C_UNK, M2C_UNK, M2C_UNK);   /* extern */
M2C_UNK func_8213B6AC(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, s32); /* extern */
extern M2C_UNK D_8218E818;
extern s16 D_8219A80A;
extern M2C_UNK func_8214B1F8;

void func_8214D774(void) {
    func_8213B6AC(0, 0, 0x20, 8, 0xA0);
    func_8213B644(0, 8, 6);
    func_8213B560(0, &func_8214B1F8, &D_8218E818, 0, 1, 0x10, (s32) D_8219A80A, 0x41, 0);
    func_8213B560(6, &BattleAnim_RunPulsingBeamEmanator, &D_8218E818, 0x46, 1, 0x10, (s32) D_8219A80A, 0x41, 1);
}

M2C_UNK func_8213B560(M2C_UNK, M2C_UNK *, M2C_UNK *, M2C_UNK, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_8213B644(M2C_UNK, M2C_UNK, M2C_UNK);   /* extern */
M2C_UNK func_8213B6AC(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, s32); /* extern */
M2C_UNK func_8213BC00(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, s32); /* extern */
M2C_UNK func_8215B110();                            /* extern */
extern M2C_UNK D_8218E818;
extern s16 D_8219A80A;
extern M2C_UNK func_8214B1F8;

void func_8214D844(void) {
    func_8213B6AC(0, 0, 0x20, 8, 0xA0);
    func_8213BC00(0, 8, 0xFF, 0, 0x10);
    func_8213B644(0, 0x20, 0xE);
    func_8213B560(0, &func_8214B1F8, &D_8218E818, 0, 1, 0x10, (s32) D_8219A80A, 0x2C, 0);
    func_8215B110();
    func_8213B560(6, &BattleAnim_RunPulsingBeamEmanator, &D_8218E818, 0x46, 1, 0x10, (s32) D_8219A80A, 0x2C, 1);
}

M2C_UNK func_8213B560(M2C_UNK, M2C_UNK *, M2C_UNK *, M2C_UNK, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_8213B644(M2C_UNK, M2C_UNK, M2C_UNK);   /* extern */
M2C_UNK func_8213B6AC(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, s32); /* extern */
extern M2C_UNK D_8218E818;
extern s16 D_8219A80A;
extern M2C_UNK func_8214B1F8;

void func_8214D938(void) {
    func_8213B6AC(0, 0, 0x20, 8, 0xA0);
    func_8213B644(0, 8, 0x20);
    func_8213B560(0, &func_8214B1F8, &D_8218E818, 0, 1, 0x10, (s32) D_8219A80A, 0x17, 0);
    func_8213B560(6, &BattleAnim_RunPulsingBeamEmanator, &D_8218E818, 0x46, 1, 0x10, (s32) D_8219A80A, 0x17, 1);
}

M2C_UNK func_8213B560(M2C_UNK, M2C_UNK *, M2C_UNK *, M2C_UNK, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_8213B644(M2C_UNK, M2C_UNK, M2C_UNK);   /* extern */
M2C_UNK func_8213B6AC(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, s32); /* extern */
extern M2C_UNK D_8218E818;
extern s16 D_8219A80A;
extern M2C_UNK func_8214B1F8;

void func_8214DA08(void) {
    func_8213B6AC(0, 0, 0x20, 8, 0xA0);
    func_8213B644(0, 8, 0x20);
    func_8213B560(0, &func_8214B1F8, &D_8218E818, 0, 1, 0x10, (s32) D_8219A80A, 0x17, 0);
}

M2C_UNK func_8213B560(M2C_UNK, M2C_UNK *, M2C_UNK *, M2C_UNK, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_8213B5D8(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK *, M2C_UNK *, s32, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_8213BD78(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, s32); /* extern */
extern M2C_UNK D_8218E5A8;
extern M2C_UNK D_8218E650;
extern s16 D_8219A80A;
extern M2C_UNK func_82145998;

void func_8214DA90(void) {
    func_8213BD78(4, 8, 0x33, 0xC, 0xFF);
    func_8213B560(0, &func_82145998, &D_8218E5A8, 0, 1, 0x10, (s32) D_8219A80A, 0x33, 0);
    func_8213B5D8(0, 5, 3, &BattleAnim_RunStrongOutwardMovingLargeHitSpark, &D_8218E650, 0, 8, 0x10, (s32) D_8219A80A, 0x26, 0);
    func_8213B5D8(0xA, 1, 3, &func_8214C208, &D_8218E650, 0, 8, 0x11, (s32) D_8219A80A, 0x26, 0);
}

M2C_UNK func_8213B560(M2C_UNK, M2C_UNK *, M2C_UNK *, M2C_UNK, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_8213B5D8(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK *, M2C_UNK *, s32, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_8213B644(M2C_UNK, M2C_UNK, M2C_UNK);   /* extern */
M2C_UNK func_8213BE70(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, s32, s32); /* extern */
extern M2C_UNK D_8218E5A8;
extern M2C_UNK D_8218E650;
extern M2C_UNK D_8218E770;
extern M2C_UNK D_8218E798;
extern M2C_UNK D_8218E820;
extern s16 D_8219A80A;
extern M2C_UNK func_82145998;
extern M2C_UNK func_8214B468;
extern M2C_UNK func_82161288;
extern M2C_UNK func_821627C0;

/**
 * sets being hit by ice beam
 * @unverified Name and comment from Stadium 1, matched by code similarity.
 */
void BattleAnim_InitializeIceBeamHit(void) {
    func_8213BE70(0, 8, 0x33, 0x10, 0xDC, 0x20);
    func_8213B560(3, &func_82145998, &D_8218E5A8, 0, 1, 0x10, (s32) D_8219A80A, 0x33, 0);
    func_8213B5D8(0, 5, 3, &BattleAnim_RunStrongOutwardMovingLargeHitSpark, &D_8218E650, 0, 8, 0x10, (s32) D_8219A80A, 0x26, 0);
    func_8213B5D8(4, 4, 2, &func_8214B468, &D_8218E820, 0, 1, 0x10, (s32) D_8219A80A, 0x33, 0);
    func_8213B5D8(0xC, 1, 3, &func_8214C208, &D_8218E650, 0, 8, 0x11, (s32) D_8219A80A, 0x26, 0);
    func_8213B5D8(0xE, 4, 2, &func_82161288, &D_8218E770, 0, 6, 0x10, 0x64, 0, 0);
    func_8213B5D8(0, 2, 6, &func_821627C0, &D_8218E798, 0, 8, 0x11, 9, 0x18, 0xB);
    func_8213B644(0x30, 0x20, 8);
}

M2C_UNK func_8213B560(M2C_UNK, M2C_UNK *, M2C_UNK *, M2C_UNK, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_8213B5D8(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK *, M2C_UNK *, s32, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_8213B644(M2C_UNK, M2C_UNK, M2C_UNK);   /* extern */
M2C_UNK func_8213C060(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK); /* extern */
extern M2C_UNK D_8218E650;
extern M2C_UNK D_8218E660;
extern M2C_UNK D_8218E820;
extern s16 D_8219A80A;
extern M2C_UNK func_82145A58;
extern M2C_UNK func_8214B5A0;

/**
 * initializes being hit by psybeam
 * @unverified Name and comment from Stadium 1, matched by code similarity.
 */
void BattleAnim_InitializePsybeamHit(void) {
    func_8213C060(4, 0x32, 0x20, 0xA0);
    func_8213B5D8(4, 4, 3, &func_8214B5A0, &D_8218E820, 0, 1, 0x10, (s32) D_8219A80A, 0, 0);
    func_8213B560(3, &func_82145A58, &D_8218E660, 0, 1, 0x10, (s32) D_8219A80A, 0x21, 0);
    func_8213B5D8(3, 5, 3, &BattleAnim_RunWeakBeamHitEffect, &D_8218E650, 0, 8, 0x10, (s32) D_8219A80A, 1, 0);
    func_8213B644(0x30, 0x20, 8);
}

extern ParticleDescriptor D_8218E588[86];
void InitParticleEffectSet_WithCustomCallback(void) {
    BattleAnim_SpawnBeamBoomWaterfallHueChange(4, 0x8, 0x21, 0x10, 0xFF);
    BattleAnim_CreateEffectSlotForCurrentOwner(3, BattleAnim_RunExpandingHitSpark, &D_8218E5A8, 0, 1, 0x10, gBattleAnimCurrentAnchor, 0x33, 0);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(3, 5, 3, BattleAnim_CallbackSharedDescriptor19RecolorAnimatedFade, &D_8218E650, 0, 8, 0x10, gBattleAnimCurrentAnchor, 0, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_CallbackEndEffects34And53Descriptor45RotatingBounceFade, &D_8218E7A8, 0, 0x10, 0x11, 9, 0, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(8, BattleAnim_CallbackEndEffects34And53Descriptor45RotatingBounceFade, &D_8218E7A8, 0, 0x10, 0x11, 9, 0, 0);
    BattleAnim_SpawnGlobalTintColorFadeDetach(0x30, 0x20, 0x8);
}

M2C_UNK func_8213B560(M2C_UNK, M2C_UNK *, M2C_UNK *, M2C_UNK, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_8213B5D8(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK *, M2C_UNK *, s32, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_8213B644(M2C_UNK, M2C_UNK, M2C_UNK);   /* extern */
M2C_UNK func_8213C060(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK); /* extern */
extern M2C_UNK D_8218E650;
extern M2C_UNK D_8218E820;
extern s16 D_8219A80A;
extern M2C_UNK func_8214B77C;

/**
 * initialize being hit by aurora beam
 * @unverified Name and comment from Stadium 1, matched by code similarity.
 */
void BattleAnim_InitializeAuroraBeamHit(void) {
    func_8213C060(4, 0x32, 0x20, 0xA0);
    func_8213B560(4, &func_8214B77C, &D_8218E820, 0, 9, 0x10, (s32) D_8219A80A, 0, 0);
    func_8213B5D8(3, 5, 3, &BattleAnim_RunWeakBeamHitEffect, &D_8218E650, 0, 8, 0x10, (s32) D_8219A80A, 0, 0);
    func_8213B5D8(0xC, 1, 3, &func_8214C208, &D_8218E650, 0, 8, 0x11, (s32) D_8219A80A, 0x39, 0);
    func_8213B644(0x16, 0x20, 8);
}

extern ParticleDescriptor D_8218E588[86];
extern ParticleDescriptor D_8218E588[86];
void InitParticleEffectSet_WithComplex(void) {
    UNUSED s32 pad; // FAKE: stack padding

    BattleAnim_SpawnOwnerModelTintRampDetach(0, 0x17, 0xFF, 0, 8);
    BattleAnim_SpawnBeamBoomWaterfallHueChange(4, 0x17, 0x17, 0x10, 0xFF);
    BattleAnim_CreateEffectSlotForCurrentOwner(3, BattleAnim_RunExpandingHitSpark, &D_8218E5A8, 0, 1, 0x10, gBattleAnimCurrentAnchor, 0x17, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_RunStrongBeamHitEffect, &D_8218E728, 0, 1, 0x10, gBattleAnimCurrentAnchor, 0x2C, 0);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(4, 8, 1, BattleAnim_RunStrongBeamHitEffect, &D_8218E820, 0, 1, 0x10, gBattleAnimCurrentAnchor, 0x2C, 0);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(3, 5, 2, BattleAnim_CallbackSharedDescriptor19AnimatedFadeMotion, &D_8218E650, 0, 8, 0x10, gBattleAnimCurrentAnchor, 0xF, 0);
    BattleAnim_InitializeHyperBeamHitSequence();
}

extern ParticleDescriptor D_8218E588[86];
void BattleAnim_EndEffect71PaletteApproachWithExpandingScaleFades(void) {
    UNUSED s32 pad; // FAKE: stack padding

    BattleAnim_SpawnBeamBoomWaterfallHueChange(4, 0x8, 0x17, 0x10, 0xFF);
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_RunStrongBeamHitEffect, &D_8218E728, 0, 1, 0x10, gBattleAnimCurrentAnchor, 0x17, 0);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(4, 4, 1, BattleAnim_RunStrongBeamHitEffect, &D_8218E820, 0, 1, 0x10, gBattleAnimCurrentAnchor, 0x17, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(3, BattleAnim_RunExpandingHitSpark, &D_8218E5A8, 0, 1, 0x10, gBattleAnimCurrentAnchor, 0x18, 0);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(3, 5, 3, BattleAnim_CallbackSharedDescriptor19AnimatedFadeMotion, &D_8218E650, 0, 8, 0x10, gBattleAnimCurrentAnchor, 0x17, 0);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0xC, 1, 3, BattleAnim_CallbackSharedDescriptor19DelayedAnimatedGrowFade, &D_8218E650, 0, 8, 0x11, gBattleAnimCurrentAnchor, 0x17, 0);
    BattleAnim_SpawnGlobalTintColorFadeDetach(0x16, 0x20, 0x8);
}

/**
 * initializes being hit by tri attack
 * @unverified Name and comment from Stadium 1.
 */
void BattleAnim_InitializeTriAttackHit(void) {
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0, 2, 8, BattleAnim_CallbackEndEffect86Descriptor19ModePositionedAnimFade, &gBattleAnimParticleDescriptors[0x19], 0, 1, 0x11, gBattleAnimCurrentAnchor, 0x49, 0);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0, 2, 8, BattleAnim_CallbackEndEffect86Descriptor19ModePositionedAnimFade, &gBattleAnimParticleDescriptors[0x19], 0, 1, 0x11, gBattleAnimCurrentAnchor, 0x4A, 1);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0, 2, 8, BattleAnim_CallbackEndEffect86Descriptor19ModePositionedAnimFade, &gBattleAnimParticleDescriptors[0x19], 0, 1, 0x11, gBattleAnimCurrentAnchor, 0x4B, 2);
}
