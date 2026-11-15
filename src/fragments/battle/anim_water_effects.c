/* Stadium Zero fragment012_17ED00. */
/* C ported from the Stadium 1 decomp: src/fragments/battle_engine/battle_engine_3223B0.c. */

#include "battle.h"
#include "matrix.h"

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
 * Inits a Surf spray droplet: random scale 0.05 to 0.14, a random rise of 1 to 4, a random spin
 * speed, speed 5 plus a random 5 to 19 extra, a random wobble timer, recolored from its palette
 * pair, hidden for a start delay equal to its spawn index.
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Surf.
 */
void BattleAnim_SetupSurfHitSpark(Particle* arg0) {
    s16 sp26 = Particle_SpawnIndex_GetS16_0C038(arg0);
    s16 sp24 = Particle_GetByteParam1(arg0);

    Particle_SetScaleScaled(arg0, (ParticleMath_RandomRange(10) * 0.01f) + 0.05f);
    Particle_MotionStep_SetYScaled_0AF24(arg0, (ParticleMath_RandomRange(30) * 0.1f) + 1.0f);
    Particle_RotationStep_SetY_0A3D8(arg0, ParticleMath_RandomRange(0x10000));
    Particle_StepMagnitude_SetScaled_0AD8C(arg0, 5.0f);
    Particle_MagnitudeStep_SetScaled_0ADA4(arg0, ParticleMath_RandomRange(0xF) + 5.0f);
    Particle_ScratchA_SetS16_0BF4C(arg0, ParticleMath_RandomRangeOffset(0x1000, 0x800));
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, sp24);
    Particle_Param0_SetS16_0BCA8(arg0, sp26);
    Particle_DisableRendering(arg0);
    Particle_AdvanceLifecycle(arg0);
}

void Particle_DisableAndDetach(Particle* arg0);                      /* extern */
M2C_UNK func_8213CB3C(s8 *);                      /* extern */
s32 func_8213CB7C(s8 *);                          /* extern */
M2C_UNK Particle_AnimateFramesForwardLoopedThenAdvance(s8 *, M2C_UNK, M2C_UNK, M2C_UNK, s32, s32); /* extern */
M2C_UNK func_8213E488(s8 *);                      /* extern */
M2C_UNK Particle_ApproachStepMagnitude(s8 *, f32, f32);        /* extern */
M2C_UNK func_82140064(s8 *, s32, s16);            /* extern */
M2C_UNK Particle_SetParam0(s8 *, M2C_UNK);             /* extern */
s32 func_82140690(s8 *);                          /* extern */
s32 func_821406B4(s8 *);                          /* extern */
M2C_UNK func_82149660(s8 *);                      /* extern */

/**
 * Handles the hit spark from being hit by Surf
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Surf.
 */
void BattleAnim_RunSurfHitSpark(Particle* arg0) {
    s16 temp_v0;

    temp_v0 = arg0->lifecycle;
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_82149660(arg0);
        break;
    case 2:
        if (func_821406B4(arg0) != 0) {
            func_8213CB3C(arg0);
            Particle_SetParam0(arg0, 0xA);
        }
        break;
    case 3:
        if (func_82140690(arg0) != 0) {
            Particle_AnimateFramesForwardLoopedThenAdvance(arg0, 0, 3, 1, 1, 0);
        }
        break;
    case 4:
        Particle_DisableAndDetach(arg0);
        break;
    }
    if (func_8213CB7C(arg0) != 0) {
        func_8213E488(arg0);
        Particle_ApproachStepMagnitude(arg0, arg0->magnitudeStep, 0.5f);
        func_82140064(arg0, M2C_FIELD(arg0, s32 *, 0x70), arg0->scratchA);
    }
}

/**
 * Inits a Bubble bubble: effect list 7, scale 0.1, a random rotationX and rotationY, a random env
 * color, speed 4 to 6.5, hidden for a start delay of twice its spawn index. arg1 is unused.
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Bubble.
 */
void BattleAnim_SetupBubbleBubbles(Particle* arg0, s16 arg1) {
    s16 sp2E = Particle_SpawnIndex_GetS16_0C038(arg0);

    Particle_SetEffectList(arg0, 7);
    Particle_SetScaleScaled(arg0, 0.1f);
    Particle_Rotation_AddVec_0A52C(arg0, ParticleMath_RandomSigned(0xC00), ParticleMath_RandomSigned(0x1000), 0);
    ParticleGfx_RecolorEnvRandomPalette(arg0);
    Particle_StepMagnitude_SetScaled_0AD8C(arg0, (ParticleMath_RandomRange(6) * 0.5f) + 4.0f);
    Particle_Param0_SetS16_0BCA8(arg0, sp2E * 2);
    Particle_DisableRendering(arg0);
    Particle_AdvanceLifecycle(arg0);
}

/**
 * Spawns Bubbles for Bubble
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Bubble.
 */
void BattleAnim_RunBubbleBubbles(Particle* arg0) {
    s16 temp_a1 = Particle_GetByteParam1(arg0);

    switch (arg0->lifecycle) {
        case 1:
            BattleAnim_SetupBubbleBubbles(arg0, temp_a1);
            break;

        case 2:
            if (Particle_DecrementParam0ToZeroThenAdvance(arg0) != 0) {
                Particle_Param0_SetS16_0BCA8(arg0, ParticleMath_RandomRange(0xA) + 0x19);
                Particle_EnableRendering(arg0);
            }
            break;

        case 3:
            Particle_ApproachScale(arg0, 0.15f, 0.01f);
            Particle_AddVelocityFromRotationTemplate1(arg0);
            if ((Particle_DecrementParam0ToZero(arg0) != 0) && (Particle_PrimAlpha_Approach_0BC2C(arg0, 0x20, 0x20) != 0)) {
                Particle_AdvanceLifecycle(arg0);
            }
            break;

        case 4:
            Particle_DisableAndDetach(arg0);
            break;
    }
}

/**
 * Inits a slow Bubble Beam bubble: scale 0.05, random velocity, a random upward rotationX that
 * later curls down at a random rate, a random rotationY, speed 1 to 2.4, a random env color, hidden
 * for a start delay of twice its spawn index.
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Bubble Beam.
 */
void BattleAnim_SetupBubbleBeamBubblesSlow(Particle* arg0) {
    UNUSED s32 pad[3]; // FAKE: stack padding
    s16 sp22 = Particle_SpawnIndex_GetS16_0C038(arg0);

    Particle_GetByteParam1(arg0);
    Particle_SetScaleScaled(arg0, 0.05f);
    Particle_SetRandomVelocityXYZ(arg0, 4, 2, 2);
    Particle_Rotation_AddX_0A578(arg0, ParticleMath_RandomSignedOffset(0x200, 0xE00));
    Particle_RotationStep_SetX_0A3C4(arg0, ParticleMath_RandomRange(0x1000) + 0x100);
    Particle_ScratchB_SetS16_0BFEC(arg0, -0x1800 - ParticleMath_RandomRange(0x1000));
    Particle_Rotation_AddY_0A594(arg0, ParticleMath_RandomSigned(0x3000));
    Particle_StepMagnitude_SetScaled_0AD8C(arg0, (ParticleMath_RandomRange(0xF) * 0.1f) + 1.0f);
    ParticleGfx_RecolorEnvRandomPalette(arg0);
    Particle_Param0_SetS16_0BCA8(arg0, sp22 * 2);
    Particle_DisableRendering(arg0);
    Particle_AdvanceLifecycle(arg0);
}

s32 Particle_DecreaseRotationXTo(Particle* arg0, s32 arg1, s32 arg2);
/**
 * Phase step for a slow Bubble Beam bubble: curls its rotationX toward its stored target and moves
 * along its rotation.
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Bubble Beam.
 */
void BattleAnim_ContinueBubbleBeamBubblesSlow(Particle* arg0) {
    if (arg0->phase == 1) {
        Particle_DecreaseRotationXTo(arg0, arg0->scratchB, arg0->rotationStep.x);
        Particle_AddVelocityFromRotationTemplate1(arg0);
    }
}

u32 ParticleMath_RandomRange(u32 arg0);                         /* extern */
void Particle_MarkInactive(Particle* arg0);                      /* extern */
M2C_UNK func_8213CB3C(s8 *);                      /* extern */
s32 func_8213CB7C(s8 *);                          /* extern */
M2C_UNK Particle_AnimateFramesForwardLoopedThenAdvance(s8 *, M2C_UNK, M2C_UNK, M2C_UNK, s32, s32); /* extern */
M2C_UNK func_8213D238(s8 *);                      /* extern */
M2C_UNK func_82140228(s8 *, M2C_UNK, M2C_UNK);    /* extern */
s32 func_82140690(s8 *);                          /* extern */
s32 func_821406B4(s8 *);                          /* extern */
M2C_UNK func_82149ADC(s8 *);                      /* extern */
M2C_UNK func_82149C20(s8 *);                      /* extern */

/**
 * handles the slower additional bubbles that appear when using bubble beam as opposed to bubble
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Bubble Beam.
 */
void BattleAnim_RunBubbleBeamBubblesSlow(Particle* arg0) {
    s16 temp_v0;

    temp_v0 = arg0->lifecycle;
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_82149ADC(arg0);
        break;
    case 2:
        if (func_821406B4(arg0) != 0) {
            func_8213D238(arg0);
            func_8213CB3C(arg0);
            Particle_SetParam0(arg0, (s16) (ParticleMath_RandomRange(0xA) + 8));
        }
        break;
    case 3:
        func_82140228(arg0, 0x3E19999A, 0x3CA3D70A); // 0.15f, 0.02f
        if (func_82140690(arg0) != 0) {
            Particle_AnimateFramesForwardLoopedThenAdvance(arg0, 0, 3, 1, 1, 0);
        }
        break;
    case 4:
        Particle_MarkInactive(arg0);
        break;
    }
    if (func_8213CB7C(arg0) != 0) {
        func_82149C20(arg0);
    }
}

/**
 * Inits a fast Bubble Beam bubble: effect list 7, growing from 0.1 to 0.2, aimed from the
 * attacker's anchor at the target's bone 9 with a little random spread, random velocity, a random
 * env color, speed 5 to 7.5, hidden for a start delay of twice its spawn index.
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Bubble Beam.
 */
void BattleAnim_SetupBubbleBeamBubblesFast(Particle* arg0) {
    s16 sp56 = Particle_SpawnIndex_GetS16_0C038(arg0);
    f32 var_fa0;
    UNUSED s32 pad[2]; // FAKE: stack padding
    Vec3f sp3C;
    Vec3f sp30;
    s16 sp2E;

    Particle_SetEffectList(arg0, 7);
    Particle_SetScaleScaled(arg0, 0.1f);
    Particle_SetScaleTarget(arg0, 0.2f);
    Particle_SetScaleStep(arg0, 0.02f);
    BattleAnim_GetSecondaryOwnerAnchorPosition(&sp3C);
    BattleAnim_GetTertiaryOwnerBone9Position(&sp30);
    var_fa0 = sp30.x - sp3C.x;
    if (var_fa0 <= 0.0f) {
        var_fa0 = -var_fa0;
    }
    sp2E = -MathUtil_Atan2s(var_fa0, sp30.y - sp3C.y);
    Particle_Rotation_AddVec_0A52C(arg0, sp2E + ParticleMath_RandomSigned(0x800), ParticleMath_RandomSigned(0x800), 0);
    Particle_SetRandomVelocityXYZ(arg0, 4, 2, 2);
    ParticleGfx_RecolorEnvRandomPalette(arg0);
    Particle_StepMagnitude_SetScaled_0AD8C(arg0, (ParticleMath_RandomRange(6) * 0.5f) + 5.0f);
    Particle_Param0_SetS16_0BCA8(arg0, sp56 * 2);
    Particle_DisableRendering(arg0);
    Particle_AdvanceLifecycle(arg0);
}

u32 ParticleMath_RandomRange(u32 arg0);                         /* extern */
void Particle_DisableAndDetach(Particle* arg0);                      /* extern */
M2C_UNK func_8213CB3C(s8 *);                      /* extern */
M2C_UNK Particle_AnimateFramesForwardLoopedThenAdvance(s8 *, M2C_UNK, M2C_UNK, M2C_UNK, s32, s32); /* extern */
void Particle_AddVelocityFromRotationTemplate1(s32 arg0);                      /* extern */
M2C_UNK func_821402B8(s8 *);                      /* extern */
s32 func_82140690(s8 *);                          /* extern */
s32 func_821406B4(s8 *);                          /* extern */
M2C_UNK func_82149D74(s8 *);                      /* extern */

/**
 * handles the faster additional bubbles that appear when using bubble beam as opposed to bubble
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Bubble Beam.
 */
void BattleAnim_RunBubbleBeamBubblesFast(Particle* arg0) {
    s16 temp_v0;

    temp_v0 = arg0->lifecycle;
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_82149D74(arg0);
        return;
    case 2:
        if (func_821406B4(arg0) != 0) {
            Particle_SetParam0(arg0, (s16) (ParticleMath_RandomRange(0x14) + 0xF));
            func_8213CB3C(arg0);
            return;
        }
        return;
    case 3:
        func_821402B8(arg0);
        Particle_AddVelocityFromRotationTemplate1(arg0);
        if (func_82140690(arg0) != 0) {
            Particle_AnimateFramesForwardLoopedThenAdvance(arg0, 0, 3, 1, 1, 0);
            return;
        }
        break;
    case 4:
        Particle_DisableAndDetach(arg0);
        break;
    }
}

/**
 * Lifecycle init for a rotating spark: tiny, aimed from the owner toward the target with
 * a mode-dependent spread (CE parameter), delayed 2 frames per burst index.
 * Not reached in play (2026-11-13): did not run in the 165-move battle sweep (each move used once,
 * from the command menu to the end of its turn) or in a tour of the menus and a COM battle.
 * @unverified Name from Stadium 1.
 */
void BattleAnim_SetupUnusedRotatingSparkVariant(Particle* arg0) {
    UNUSED s32 pad[2]; // FAKE: stack padding
    f32 temp_fv0;
    Vec3f sp40;
    Vec3f sp34;
    s16 sp32;
    s16 sp30 = Particle_SpawnIndex_GetS16_0C038(arg0);
    s16 sp2E = Particle_FieldCE_GetS32_0C040(arg0);

    Particle_SetEffectList(arg0, 7);
    Particle_SetScaleScaled(arg0, 0.1f);
    BattleAnim_GetSecondaryOwnerAnchorPosition(&sp40);
    BattleAnim_GetTertiaryOwnerBone9Position(&sp34);

    temp_fv0 = sp34.x - sp40.x;
    if (temp_fv0 <= 0.0f) {
        temp_fv0 = -temp_fv0;
    }

    sp32 = MathUtil_Atan2s(temp_fv0, sp34.y - sp40.y) * -1;
    Particle_Rotation_AddY_0A594(arg0, ParticleMath_RandomSigned(0x400));

    switch (sp2E) {
        case 0:
            Particle_ScratchA_SetS16_0BF4C(arg0, sp32 + 0x800);
            Particle_ScratchB_SetS16_0BFEC(arg0, 0x1800);
            break;

        case 1:
            Particle_ScratchA_SetS16_0BF4C(arg0, sp32 - 0x1000);
            Particle_ScratchB_SetS16_0BFEC(arg0, 0x1000);
            break;

        case 2:
            Particle_ScratchA_SetS16_0BF4C(arg0, sp32 + 0xC00);
            Particle_ScratchB_SetS16_0BFEC(arg0, -0x1400);
            break;

        case 3:
            Particle_ScratchA_SetS16_0BF4C(arg0, sp32 - 0xA00);
            Particle_ScratchB_SetS16_0BFEC(arg0, -0x2000);
            break;
    }

    Particle_StepMagnitude_SetScaled_0AD8C(arg0, 5.25f);
    ParticleGfx_RecolorEnvRandomPalette(arg0);
    Particle_Param0_SetS16_0BCA8(arg0, sp30 * 2);
    Particle_DisableRendering(arg0);
    Particle_AdvanceLifecycle(arg0);
}

/**
 * Motion steps for the rotating spark: after 2 frames turns it about X by unk_AE, then
 * keeps turning it about Z by unk_B0 while it moves.
 * Not reached in play (2026-11-13): did not run in the 165-move battle sweep (each move used once,
 * from the command menu to the end of its turn) or in a tour of the menus and a COM battle.
 * @unverified Name from Stadium 1.
 */
void BattleAnim_MotionUnusedRotatingSparkVariant(Particle* arg0) {
    switch (arg0->phase) {
        case 1:
            if (Particle_TickPhaseTimer(arg0, 2) != 0) {
                Particle_AdvancePhase(arg0);
                Particle_Rotation_AddX_0A578(arg0, arg0->scratchA);
            }
            break;

        case 2:
            Particle_Rotation_AddZ_0A5B0(arg0, arg0->scratchB);
            break;
    }

    if (arg0->phase > 0) {
        Particle_MoveAlongRotationXYZAlt(arg0);
    }
}

void Particle_MarkInactive(Particle* arg0);                      /* extern */
M2C_UNK func_8213CB3C(s8 *);                      /* extern */
s32 func_8213CB7C(s8 *);                          /* extern */
M2C_UNK func_8213D238(s8 *);                      /* extern */
M2C_UNK Particle_SetParam0(s8 *, M2C_UNK);             /* extern */
s32 func_821406B4(s8 *);                          /* extern */
M2C_UNK func_82149FD8(s8 *);                      /* extern */
M2C_UNK func_8214A190(s8 *);                      /* extern */

/**
 * Particle callback (no reference found): runs BattleAnim_SetupUnusedRotatingSparkVariant on
 * lifecycle 1, then steps it until its spawn step is done.
 * @unverified Name guessed from the code.
 */
void BattleAnim_CallbackUnusedRotatingSpark(Particle* particle) {
    s16 temp_v0;

    temp_v0 = particle->lifecycle;
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_82149FD8(particle);
        break;
    case 2:
        if (func_821406B4(particle) != 0) {
            func_8213D238(particle);
            func_8213CB3C(particle);
            Particle_SetParam0(particle, 0x1E);
        }
        break;
    case 3:
        func_821406B4(particle);
        break;
    case 4:
        Particle_MarkInactive(particle);
        break;
    }
    if (func_8213CB7C(particle) != 0) {
        func_8214A190(particle);
    }
}

/**
 * Lifecycle init for an aimed spark: tiny, pointed from the secondary owner's anchor at
 * the tertiary owner's bone 9, palette color from the CF parameter.
 * Not reached in play (2026-11-13): did not run in the 165-move battle sweep (each move used once,
 * from the command menu to the end of its turn) or in a tour of the menus and a COM battle.
 * @unverified Name from Stadium 1.
 */
void BattleAnim_SetupUnusedAimedSparkVariant(Particle* arg0) {
    s16 sp4E = Particle_FieldCE_GetS32_0C040(arg0);
    Vec3f sp40;
    Vec3f sp34;
    s16 temp_v1;

    Particle_SetEffectList(arg0, 7);
    Particle_SetScaleScaled(arg0, 0.1f);
    Particle_SetScaleTarget(arg0, 0.1f);
    BattleAnim_GetSecondaryOwnerAnchorPosition(&sp40);
    BattleAnim_GetTertiaryOwnerBone9Position(&sp34);

    temp_v1 = ParticleMath_AngleXBetweenPoints(sp40, sp34);

    switch (sp4E) {
        case 0:
            Particle_Rotation_AddX_0A578(arg0, temp_v1 + 0x2000);
            Particle_Rotation_AddY_0A594(arg0, -0x4000);
            break;

        case 1:
            Particle_Rotation_AddX_0A578(arg0, temp_v1 + 0x6000);
            Particle_Rotation_AddY_0A594(arg0, -0x4000);
            break;
    }

    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, Particle_GetByteParam1(arg0));
    Particle_AdvanceLifecycle(arg0);
}

/**
 * Particle callback for the aimed spark: fades it in, holds, then fades it out, while
 * growing it toward 50 times its size.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal or j,
 * no pointer word, no lui/addiu pair in any fragment), so play cannot reach it.
 * @unverified Name from Stadium 1.
 */
void BattleAnim_CallbackUnusedAimedSparkVariant(Particle* arg0) {
    switch (arg0->lifecycle) {
        case 1:
            BattleAnim_SetupUnusedAimedSparkVariant(arg0);
            break;

        case 2:
            Particle_ApproachPrimAlphaThenAdvance(arg0, 0xFF, 4);
            break;

        case 3:
            Particle_TickDelayAndAdvanceLifecycle(arg0, 70);
            break;

        case 4:
            Particle_ApproachPrimAlphaThenAdvance(arg0, 0, 0x10);
            break;

        case 5:
            Particle_DisableAndDetach(arg0);
            break;
    }

    Particle_ApproachScale(arg0, 50.0f, 0.2f);
    Particle_StepScaleTarget(arg0, 1.0f, 0.1f);
}

/**
 * Inits the Water Gun or Hydro Pump muzzle splash: variant 0 grows from 0.5 to 1.2, variant 1 from
 * 0.3 to 0.8. Palette pair 0x26.
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Water Gun, Hydro Pump.
 */
void BattleAnim_SetupWaterGunAndHydroPumpEmitterFade(Particle* arg0) {
    switch (Particle_FieldCE_GetS32_0C040(arg0)) {
        case 0:
            Particle_SetScaleScaled(arg0, 0.5f);
            Particle_SetScaleTarget(arg0, 1.2f);
            Particle_SetScaleStep(arg0, 0.1f);
            break;

        case 1:
            Particle_SetScaleScaled(arg0, 0.3f);
            Particle_SetScaleTarget(arg0, 0.8f);
            Particle_SetScaleStep(arg0, 0.05f);
            break;
    }

    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, 0x26);
    Particle_AdvanceLifecycle(arg0);
}

/**
 * Handles the fading of the burst emitters for Water Gun and Hydro Pump
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Water Gun, Hydro Pump.
 */
void BattleAnim_RunWaterGunAndHydroPumpEmitterFade(Particle* arg0) {
    switch (arg0->lifecycle) {
        case 1:
            BattleAnim_SetupWaterGunAndHydroPumpEmitterFade(arg0);
            break;

        case 2:
            Particle_ApproachScaleTarget(arg0);
            Particle_AnimateFramesForwardLoopedThenAdvance(arg0, 0, 7, 1, 2, 0);
            Particle_PrimAlpha_Approach_0BC2C(arg0, 0x20, 8);
            break;

        case 3:
            Particle_MarkInactive(arg0);
            break;
    }
}

/**
 * Inits a Hydro Pump spray child: scale 0.5, a random direction, speed 1, palette pair 0x27.
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Hydro Pump.
 */
void BattleAnim_SetupHydroPumpBurstChild(Particle* arg0) {
    UNUSED s32 pad; // FAKE: stack padding

    Particle_SpawnIndex_GetS16_0C038(arg0);
    Particle_SetScaleScaled(arg0, 0.5f);
    Particle_Rotation_AddVec_0A52C(arg0, ParticleMath_RandomRange(0x10000), ParticleMath_RandomRange(0x10000), 0);
    Particle_StepMagnitude_SetScaled_0AD8C(arg0, 1.0f);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, 0x27);
    Particle_AdvanceLifecycle(arg0);
}

void Particle_MarkInactive(Particle* arg0);                      /* extern */
M2C_UNK func_8213CA80(s8 *, M2C_UNK);             /* extern */
M2C_UNK Particle_AddPosOffsetYScaled(s8 *, M2C_UNK);             /* extern */
void Particle_AddVelocityFromRotationTemplate1(s32 arg0);                      /* extern */
M2C_UNK Particle_ApproachStepMagnitude(s8 *, f32, f32);    /* extern */
M2C_UNK func_82140228(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK Particle_ApproachPrimAlpha(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_8214A634(s8 *);                      /* extern */

/**
 * Particle lifecycle callback (start effect58 descriptor0 aburst child): steps the particle by its
 * lifecycle state.
 * Seen in play (2026-11-14) (Metronome bench, one movie per move, 1P Onix vs Pinsir on Splash, exec
 * breakpoint): ran only for Hydro Pump.
 * @unverified Name guessed from the code.
 */
void BattleAnim_CallbackStart58Desc0ABurstChild(Particle* particle) {
    s16 temp_v0;

    temp_v0 = particle->lifecycle;
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_8214A634(particle);
        return;
    case 2:
        func_82140228(particle, 0x3E99999A, 0x3D4CCCCD); // 0.3f, 0.05f
        Particle_ApproachPrimAlpha(particle, 0x20, 0x10);
        Particle_ApproachStepMagnitude(particle, 0.5f, 0.05f);
        Particle_AddVelocityFromRotationTemplate1(particle);
        Particle_AddPosOffsetYScaled(particle, 0xBF800000); // -1.0f
        func_8213CA80(particle, 0x10);
        return;
    case 3:
        Particle_MarkInactive(particle);
        return;
    }
}

/**
 * Inits a Hydro Pump trail blob: scale 0.6, set 6 units back for variant 1, palette pair 0x28,
 * alpha 0xC8.
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Hydro Pump.
 */
void BattleAnim_SetupHydroPumpMetadataBurstChild(Particle* arg0) {
    s16 sp26 = Particle_FieldCE_GetS32_0C040(arg0);

    Particle_SetScaleScaled(arg0, 0.6f);

    if (sp26 == 1) {
        Particle_AddPositionOffsetAlongRotationYPlus180(arg0, 6.0f);
    }

    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, 0x28);
    Particle_SetPrimAlpha(arg0, 0xC8);
    Particle_AdvanceLifecycle(arg0);
}

void Particle_DisableAndDetach(Particle* arg0);                      /* extern */
M2C_UNK func_8213C9D0(s8 *);                      /* extern */
M2C_UNK func_82140228(s8 *, M2C_UNK, M2C_UNK);    /* extern */
s32 Particle_ApproachPrimAlpha(s8 *, M2C_UNK, M2C_UNK);        /* extern */
M2C_UNK func_8214A77C(s8 *);                      /* extern */

/**
 * Particle lifecycle callback (start effect58 descriptor08 metadata burst child): steps the
 * particle by its lifecycle state.
 * Seen in play (2026-11-14) (Metronome bench, one movie per move, 1P Onix vs Pinsir on Splash, exec
 * breakpoint): ran only for Hydro Pump.
 * @unverified Name guessed from the code.
 */
void BattleAnim_CallbackStart58Desc08MetadataBurstChild(Particle* particle) {
    s16 temp_v0;

    temp_v0 = particle->lifecycle;
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_8214A77C(particle);
        break;
    case 2:
        if (Particle_ApproachPrimAlpha(particle, 0x80, 0x20) != 0) {
            func_8213C9D0(particle);
        }
        break;
    case 3:
        Particle_DisableAndDetach(particle);
        break;
    }
    func_82140228(particle, 0x3EB33333, 0x3D4CCCCD); // 0.35f, 0.05f
}

/**
 * Inits the Hydro Pump water ball that emits the spray: scale 0.7, speed 12, palette pair 0x28,
 * full alpha.
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Hydro Pump.
 */
void BattleAnim_SetupHydroPumpBurstEmitter(Particle* arg0) {
    Particle_SetScaleScaled(arg0, 0.7f);
    Particle_StepMagnitude_SetScaled_0AD8C(arg0, 12.0f);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, 0x28);
    Particle_SetPrimAlpha(arg0, 0xFF);
    Particle_AdvanceLifecycle(arg0);
}

/**
 * Emits metadata-controlled particles and child projectiles for Hydro Pump
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Hydro Pump.
 */
void BattleAnim_RunHydroPumpBurstEmitter(Particle* arg0) {
    switch (arg0->lifecycle) {
        case 1:
            BattleAnim_SetupHydroPumpBurstEmitter(arg0);
            break;

        case 2:
            BattleAnim_EmitParticleBurstWithMetadata(arg0, BattleAnim_CallbackStart58Desc08MetadataBurstChild, &gBattleAnimParticleDescriptors[8], 1, 0, 0);
            BattleAnim_EmitParticleBurstWithMetadata(arg0, BattleAnim_CallbackStart58Desc08MetadataBurstChild, &gBattleAnimParticleDescriptors[8], 1, 0, 1);
            BattleAnim_EmitParticleBurst(arg0, BattleAnim_CallbackStart58Desc0ABurstChild, &gBattleAnimParticleDescriptors[0xA], 4);
            Particle_TickDelayAndAdvanceLifecycle(arg0, 20);
            break;

        case 3:
            Particle_DisableAndDetach(arg0);
            break;
    }

    Particle_AddVelocityFromRotationTemplate1(arg0);
}

/**
 * Inits a Water Gun spray child: scale 0.2, a random direction, speed 0.5, palette pair 0x27.
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Water Gun.
 */
void BattleAnim_SetupWaterGunProjectileChild(Particle* arg0) {
    UNUSED s32 pad; // FAKE: stack padding

    Particle_SpawnIndex_GetS16_0C038(arg0);
    Particle_SetScaleScaled(arg0, 0.2f);
    Particle_Rotation_AddVec_0A52C(arg0, ParticleMath_RandomRange(0x10000), ParticleMath_RandomRange(0x10000), 0);
    Particle_StepMagnitude_SetScaled_0AD8C(arg0, 0.5f);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, 0x27);
    Particle_AdvanceLifecycle(arg0);
}

void Particle_MarkInactive(Particle* arg0);                      /* extern */
M2C_UNK func_8213CA80(s8 *, M2C_UNK);             /* extern */
M2C_UNK Particle_AddPosOffsetYScaled(s8 *, M2C_UNK);             /* extern */
void Particle_AddVelocityFromRotationTemplate1(s32 arg0);                      /* extern */
M2C_UNK func_82140228(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK Particle_ApproachPrimAlpha(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_8214A9DC(s8 *);                      /* extern */

/**
 * Particle lifecycle callback (start effect6 descriptor0 aburst child): steps the particle by its
 * lifecycle state.
 * Seen in play (2026-11-14) (Metronome bench, one movie per move, 1P Onix vs Pinsir on Splash, exec
 * breakpoint): ran only for Water Gun.
 * @unverified Name guessed from the code.
 */
void BattleAnim_CallbackStart6Desc0ABurstChild(Particle* particle) {
    s16 temp_v0;

    temp_v0 = particle->lifecycle;
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_8214A9DC(particle);
        return;
    case 2:
        func_82140228(particle, 0x3DCCCCCD, 0x3CA3D70A); // 0.1f, 0.02f
        Particle_ApproachPrimAlpha(particle, 0x20, 0xC);
        Particle_AddVelocityFromRotationTemplate1(particle);
        Particle_AddPosOffsetYScaled(particle, 0xBF000000); // -0.5f
        func_8213CA80(particle, 0x10);
        return;
    case 3:
        Particle_MarkInactive(particle);
        return;
    }
}

/**
 * Inits a Water Gun trail blob: scale 0.2, set 3 (variant 1) or 6 (variant 2) units back, palette
 * pair 0x28, alpha 0xC8.
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Water Gun.
 */
void BattleAnim_SetupWaterGunProjectileMetadata(Particle* arg0) {
    s16 sp26 = Particle_FieldCE_GetS32_0C040(arg0);

    Particle_SetScaleScaled(arg0, 0.2f);

    switch (sp26) {
        case 1:
            Particle_AddPositionOffsetAlongRotationYPlus180(arg0, 3.0f);
            break;

        case 2:
            Particle_AddPositionOffsetAlongRotationYPlus180(arg0, 6.0f);
            break;
    }

    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, 0x28);
    Particle_SetPrimAlpha(arg0, 0xC8);
    Particle_AdvanceLifecycle(arg0);
}

void Particle_DisableAndDetach(Particle* arg0);                      /* extern */
M2C_UNK func_8213C9D0(s8 *);                      /* extern */
M2C_UNK func_82140228(s8 *, M2C_UNK, M2C_UNK);    /* extern */
s32 Particle_ApproachPrimAlpha(s8 *, M2C_UNK, M2C_UNK);        /* extern */
M2C_UNK func_8214AB14(s8 *);                      /* extern */

/**
 * Particle lifecycle callback (start effect6 descriptor08 metadata burst child): steps the particle
 * by its lifecycle state.
 * Seen in play (2026-11-14) (Metronome bench, one movie per move, 1P Onix vs Pinsir on Splash, exec
 * breakpoint): ran only for Water Gun.
 * @unverified Name guessed from the code.
 */
void BattleAnim_CallbackStart6Desc08MetadataBurstChild(Particle* particle) {
    s16 temp_v0;

    temp_v0 = particle->lifecycle;
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_8214AB14(particle);
        break;
    case 2:
        if (Particle_ApproachPrimAlpha(particle, 0x80, 0x20) != 0) {
            func_8213C9D0(particle);
        }
        break;
    case 3:
        Particle_DisableAndDetach(particle);
        break;
    }
    func_82140228(particle, 0x3DCCCCCD, 0x3CA3D70A); // 0.1f, 0.02f
}

/**
 * Inits the Water Gun water ball: scale 0.2, speed 10, palette pair 0x28, full alpha.
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Water Gun.
 */
void BattleAnim_SetupWaterGunProjectile(Particle* arg0) {
    Particle_SetScaleScaled(arg0, 0.2f);
    Particle_StepMagnitude_SetScaled_0AD8C(arg0, 10.0f);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, 0x28);
    Particle_SetPrimAlpha(arg0, 0xFF);
    Particle_AdvanceLifecycle(arg0);
}

/**
 * Handles the parent projectile for Water gun
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Water Gun.
 */
void BattleAnim_RunWaterGunProjectile(Particle* arg0) {
    switch (arg0->lifecycle) {
        case 1:
            BattleAnim_SetupWaterGunProjectile(arg0);
            break;

        case 2:
            BattleAnim_EmitParticleBurstWithMetadata(arg0, BattleAnim_CallbackStart6Desc08MetadataBurstChild, &gBattleAnimParticleDescriptors[8], 1, 0, 0);
            BattleAnim_EmitParticleBurstWithMetadata(arg0, BattleAnim_CallbackStart6Desc08MetadataBurstChild, &gBattleAnimParticleDescriptors[8], 1, 0, 1);
            BattleAnim_EmitParticleBurstWithMetadata(arg0, BattleAnim_CallbackStart6Desc08MetadataBurstChild, &gBattleAnimParticleDescriptors[8], 1, 0, 2);
            BattleAnim_EmitParticleBurst(arg0, BattleAnim_CallbackStart6Desc0ABurstChild, &gBattleAnimParticleDescriptors[0xA], 4);
            Particle_TickDelayAndAdvanceLifecycle(arg0, 0x20);
            break;

        case 3:
            Particle_DisableAndDetach(arg0);
            break;
    }
    Particle_AddVelocityFromRotationTemplate1(arg0);
}

/**
 * Inits an Ice Beam cold-breath puff: scale 0.25, random velocity, a random downward rotationX that
 * later turns up at a random rate, a random rotationY, speed 1 to 5, recolored from its palette
 * pair, alpha 0xC8, hidden for a start delay of twice its spawn index.
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Ice Beam.
 */
void BattleAnim_SetupIceBeamColdBreath(Particle* arg0) {
    UNUSED s32 pad[3]; // FAKE: stack padding
    s16 sp22 = Particle_SpawnIndex_GetS16_0C038(arg0);
    s16 sp20 = Particle_GetByteParam1(arg0);

    Particle_SetScaleScaled(arg0, 0.25f);
    Particle_SetRandomVelocityXYZ(arg0, 4, 2, 2);
    Particle_Rotation_AddX_0A578(arg0, ParticleMath_RandomSignedOffset(0x200, -0xE00));
    Particle_RotationStep_SetX_0A3C4(arg0, ParticleMath_RandomRange(0x400) + 0x100);
    Particle_ScratchB_SetS16_0BFEC(arg0, ParticleMath_RandomRange(0x1000) + 0x1000);
    Particle_Rotation_AddY_0A594(arg0, ParticleMath_RandomSigned(0x1800));
    Particle_StepMagnitude_SetScaled_0AD8C(arg0, (ParticleMath_RandomRange(40) * 0.1f) + 1.0f);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, sp20);
    Particle_SetPrimAlpha(arg0, 0xC8);
    Particle_Param0_SetS16_0BCA8(arg0, sp22 * 2);
    Particle_DisableRendering(arg0);
    Particle_AdvanceLifecycle(arg0);
}

/**
 * Phase step for an Ice Beam cold-breath puff: turns its rotationX toward its stored target, moves
 * along its rotation and sinks 0.2 per frame.
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Ice Beam.
 */
void BattleAnim_ContinueIceBeamColdBreath(Particle* arg0) {
    if (arg0->phase == 1) {
        Particle_ApproachRotationXTo(arg0, arg0->scratchB, arg0->rotationStep.x);
        Particle_AddVelocityFromRotationTemplate1(arg0);
        Particle_PositionOffset_AddYScaled_08E90(arg0, -0.2f);
    }
}

void Particle_MarkInactive(Particle* arg0);                      /* extern */
M2C_UNK func_8213CB3C(s8 *);                      /* extern */
s32 func_8213CB7C(s8 *);                          /* extern */
M2C_UNK Particle_AnimateFramesForwardLoopedThenAdvance(s8 *, M2C_UNK, M2C_UNK, M2C_UNK, s32, s32); /* extern */
M2C_UNK func_8213D238(s8 *);                      /* extern */
M2C_UNK func_82140228(s8 *, M2C_UNK, M2C_UNK);    /* extern */
s32 func_821406B4(s8 *);                          /* extern */
M2C_UNK func_8214ADB8(s8 *);                      /* extern */
M2C_UNK func_8214AF08(s8 *);                      /* extern */

/**
 * Particle callback of the Ice Beam animation. Player sweep (all 165 moves used in battle): only
 * Ice Beam reached this function.
 */
void BattleAnim_IceBeamParticleUpdateA(Particle* arg0) {
    s16 temp_v0;

    temp_v0 = arg0->lifecycle;
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
        func_82140228(arg0, 0x3F333333, 0x3DCCCCCD); // 0.7f, 0.1f
        Particle_AnimateFramesForwardLoopedThenAdvance(arg0, 0, 7, 1, 2, 0);
        break;
    case 4:
        Particle_MarkInactive(arg0);
        break;
    }
    if (func_8213CB7C(arg0) != 0) {
        func_8214AF08(arg0);
    }
}

/**
 * Inits a Mega Punch or Mega Kick afterimage: each later spawn is smaller (0.75 minus 0.1 per
 * index) and fainter (alpha 0xFF minus 32 per index), speed 10, palette pair 0x28, hidden for a
 * start delay of its spawn index plus 1.
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Mega Punch, Mega Kick.
 */
void BattleAnim_SetupMegaKickAndPunchProjectile(Particle* arg0) {
    s16 sp26 = Particle_SpawnIndex_GetS16_0C038(arg0);

    Particle_SetScaleScaled(arg0, 0.75f - (sp26 * 0.1f));
    Particle_StepMagnitude_SetScaled_0AD8C(arg0, 10.0f);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, 0x28);
    Particle_SetPrimAlpha(arg0, (0xFF - (sp26 << 5)) & 0xFF);
    Particle_Param0_SetS16_0BCA8(arg0, sp26 + 1);
    Particle_DisableRendering(arg0);
    Particle_AdvanceLifecycle(arg0);
}

/**
 * handles projectile for Mega kick and mega punch
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Mega Punch, Mega Kick.
 */
void BattleAnim_RunMegaKickAndPunchProjectile(Particle* arg0) {
    switch (arg0->lifecycle) {
        case 1:
            BattleAnim_SetupMegaKickAndPunchProjectile(arg0);
            break;

        case 2:
            if (Particle_DecrementParam0ToZeroThenAdvance(arg0) != 0) {
                Particle_EnableRendering(arg0);
            }
            break;

        case 3:
            Particle_TickDelayAndAdvanceLifecycle(arg0, 10);
            Particle_AddVelocityFromRotationTemplate1(arg0);
            break;

        case 4:
            Particle_DisableAndDetach(arg0);
            break;
    }
}

/**
 * Inits a beam's starting glow: grows from 1.0 to 2.0 in steps of 0.75, recolored from its palette
 * pair.
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Ice Beam, Psybeam, Aurora Beam, Hyper Beam, Tri Attack.
 */
void BattleAnim_SetupInitialBeamEmanator(Particle* arg0) {
    Particle_SetScaleScaled(arg0, 1.0f);
    Particle_SetScaleTarget(arg0, 2.0f);
    Particle_SetScaleStep(arg0, 0.75f);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, Particle_GetByteParam1(arg0));
    Particle_AdvanceLifecycle(arg0);
}

/**
 * Runs the first emanator that shows up in Ice Beam, Psybeam, Aurora Beam, Hyper Beam, Solar Beam,
 * and Tri Attack. Most Beam mosts switch to the Pulsing emanator after a few frames
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Ice Beam, Psybeam, Aurora Beam, Hyper Beam, Tri Attack.
 */
void BattleAnim_RunInitialBeamEmanator(Particle* arg0) {
    switch (arg0->lifecycle) {
        case 1:
            BattleAnim_SetupInitialBeamEmanator(arg0);
            break;

        case 2:
            Particle_AnimateFramesForwardLoopedThenAdvance(arg0, 0, 3, 1, 1, 0);
            Particle_ApproachScaleTarget(arg0);
            break;

        case 3:
            Particle_DisableAndDetach(arg0);
            break;
    }
}

/**
 * Inits a beam's pulsing glow: grows from 0.4 to 0.7, recolored from its palette pair, texture
 * frame 1, a random Z rotation.
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Ice Beam, Psybeam, Aurora Beam, Hyper Beam.
 */
void BattleAnim_SetupPulsingBeamEmanator(Particle* arg0) {
    Particle_SetScaleScaled(arg0, 0.4f);
    Particle_SetScaleTarget(arg0, 0.7f);
    Particle_SetScaleStep(arg0, 0.1f);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, Particle_GetByteParam1(arg0));
    Particle_SetTextureFrame(arg0, 1);
    Particle_Rotation_SetZ_0A2CC(arg0, ParticleMath_RandomRange(0x10000));
    Particle_AdvanceLifecycle(arg0);
}

void Particle_DisableAndDetach(Particle* arg0);                      /* extern */
M2C_UNK func_821401F8(s8 *, M2C_UNK);             /* extern */
M2C_UNK func_82140210(s8 *, M2C_UNK);             /* extern */
s32 func_821402E4(s8 *);                          /* extern */
s32 func_82140690(s8 *);                          /* extern */
M2C_UNK func_8214B280(s8 *);                      /* extern */

/**
 * handles the pulsing beam emanator for Ice Beam, Psybeam, Aurora Beam, Hyper Beam, and Solar Beam
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Ice Beam, Psybeam, Aurora Beam, Hyper Beam.
 */
void BattleAnim_RunPulsingBeamEmanator(Particle* arg0) {
    s16 temp_v0;

    temp_v0 = arg0->lifecycle;
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_8214B280(arg0);
        break;
    case 2:
        if (func_821402E4(arg0) != 0) {
            func_821401F8(arg0, 0x3E4CCCCD); // 0.2f
        }
        break;
    case 3:
        func_821402E4(arg0);
        break;
    case 4:
        func_821401F8(arg0, 0x3F333333); // 0.7f
        func_82140210(arg0, 0x3DCCCCCD); // 0.1f
        arg0->lifecycle = 2;
        break;
    }
    if (func_82140690(arg0) != 0) {
        Particle_DisableAndDetach(arg0);
    }
}

/**
 * Inits a strong beam hit flash: scale 2.0, 10 units back, recolored from its palette pair, full
 * alpha, texture frame 1, a random Z rotation.
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Ice Beam, Hyper Beam.
 */
void BattleAnim_SetupStrongBeamHitEffect(Particle* arg0) {
    Particle_SetScaleScaled(arg0, 2.0f);
    Particle_AddPositionOffsetAlongRotationYPlus180(arg0, 10.0f);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, Particle_GetByteParam1(arg0));
    Particle_SetPrimAlpha(arg0, 0xFF);
    Particle_SetTextureFrame(arg0, 1);
    Particle_Rotation_SetZ_0A2CC(arg0, ParticleMath_RandomRange(0x10000));
    Particle_AdvanceLifecycle(arg0);
}

/**
 * Handles the hit effect from being hit by Ice beam, Hyper Beam, Solarbeam, or Sky attack
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Ice Beam, Hyper Beam.
 */
void BattleAnim_RunStrongBeamHitEffect(Particle* arg0) {
    switch (arg0->lifecycle) {
        case 1:
            BattleAnim_SetupStrongBeamHitEffect(arg0);
            break;

        case 2:
            Particle_ApproachScaleThenAdvance(arg0, 5.0f, 1.0f);
            break;

        case 3:
            Particle_ApproachScaleThenAdvance(arg0, 0.0f, 1.0f);
            Particle_PrimAlpha_Approach_0BC2C(arg0, 0x40, 0x20);
            break;

        case 4:
            Particle_DisableAndDetach(arg0);
            break;
    }
}

/**
 * Inits a Psybeam hit flash: scale 2.0, 10 units back, random prim and env colors from palette set
 * B, texture frame 1, a random Z rotation.
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Psybeam.
 */
void BattleAnim_SetupPsybeamHitSparkFlicker(Particle* arg0) {
    Particle_GetByteParam1(arg0);
    Particle_SetScaleScaled(arg0, 2.0f);
    Particle_AddPositionOffsetAlongRotationYPlus180(arg0, 10.0f);
    ParticleGfx_RecolorPrimFromPaletteSetB(arg0, ParticleMath_RandomRange(6));
    ParticleGfx_RecolorEnvFromPaletteSetB(arg0, ParticleMath_RandomRange(6));
    Particle_SetTextureFrame(arg0, 1);
    Particle_Rotation_SetZ_0A2CC(arg0, ParticleMath_RandomRange(0x10000));
    Particle_AdvanceLifecycle(arg0);
}

/**
 * handles the hit spark when being hit by psybeam
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Psybeam.
 */
void BattleAnim_RunPsybeamHitSparkFlicker(Particle* arg0) {
    Particle_GetByteParam1(arg0);

    switch (arg0->lifecycle) {
        case 1:
            BattleAnim_SetupPsybeamHitSparkFlicker(arg0);
            break;

        case 2:
            Particle_ApproachScaleThenAdvance(arg0, 5.0f, 1.0f);
            break;

        case 3:
            Particle_ApproachScaleThenAdvance(arg0, 0.0f, 1.0f);
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
 * Inits an Aurora Beam hit flash: scale 2.0, 10 units back, prim palette 8 and an env color from
 * palette set A cycling with spawn index, texture frame 1, rotated a tenth of a turn per spawn
 * index and spinning at a random rate, hidden for a start delay of twice its spawn index.
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Aurora Beam.
 */
void BattleAnim_SetupAuroraBeamHitSpark(Particle* arg0) {
    UNUSED s16 pad; // FAKE: stack padding
    s16 sp24;

    Particle_GetByteParam1(arg0);
    sp24 = Particle_SpawnIndex_GetS16_0C038(arg0);
    Particle_SetScaleScaled(arg0, 2.0f);
    Particle_AddPositionOffsetAlongRotationYPlus180(arg0, 10.0f);
    ParticleGfx_RecolorPrim(arg0, 0x8);
    ParticleGfx_RecolorEnvFromPaletteSetA(arg0, sp24 % 6);
    Particle_SetTextureFrame(arg0, 1);
    Particle_Param0_SetS16_0BCA8(arg0, sp24 * 2);
    Particle_Rotation_AddZ_0A5B0(arg0, (sp24 << 0x10) / 10);
    Particle_RotationStep_SetZ_0A3EC(arg0, ParticleMath_RandomSignedOffsetBySign(0x800, 0x400));
    Particle_DisableRendering(arg0);
    Particle_AdvanceLifecycle(arg0);
}

/**
 * Handles the hit spark when being hit by aurora beam
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Aurora Beam.
 */
void BattleAnim_RunAuroraBeamHitSpark(Particle* arg0) {
    switch (arg0->lifecycle) {
        case 1:
            BattleAnim_SetupAuroraBeamHitSpark(arg0);
            break;

        case 2:
            if (Particle_DecrementParam0ToZeroThenAdvance(arg0) != 0) {
                Particle_EnableRendering(arg0);
            }
            break;

        case 3:
            Particle_ApproachScaleThenAdvance(arg0, 4.0f, 1.0f);
            break;

        case 4:
            Particle_TickDelayAndAdvanceLifecycle(arg0, 8);
            break;

        case 5:
            Particle_ApproachScaleThenAdvance(arg0, 0.0f, 1.0f);
            break;

        case 6:
            Particle_DisableAndDetach(arg0);
            break;
    }

    Particle_Rotation_AddXFromRotationStep_0A4B4(arg0);
}

/**
 * Inits a large outward hit spark: recolored from its palette pair, scale 1.35, 5 units forward,
 * speed 5.5, a random direction.
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Hydro Pump, Hyper Beam, Ice Beam and Waterfall.
 */
void BattleAnim_SetupStrongOutwardMovingLargeHitSpark(Particle* arg0) {
    Particle_SpawnIndex_GetS16_0C038(arg0);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, Particle_GetByteParam1(arg0));
    Particle_SetScaleScaled(arg0, 1.35f);
    Particle_AddPositionOffsetAlongRotationY(arg0, 5.0f);
    Particle_StepMagnitude_SetScaled_0AD8C(arg0, 5.5f);
    Particle_Rotation_AddVec_0A52C(arg0, ParticleMath_RandomRange(0x10000), ParticleMath_RandomRange(0x10000), 0);
    Particle_AdvanceLifecycle(arg0);
}

void Particle_MarkInactive(Particle* arg0);                      /* extern */
s32 Particle_IsRunning(Particle* arg0);                          /* extern */
M2C_UNK Particle_AnimateFramesForwardLoopedThenAdvance(s8 *, M2C_UNK, M2C_UNK, M2C_UNK, s32, s32); /* extern */
void Particle_AddVelocityFromRotationTemplate1(s32 arg0);                      /* extern */
M2C_UNK Particle_ApproachStepMagnitude(s8 *, f32, f32);    /* extern */
M2C_UNK Particle_ApproachPrimAlpha(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_8214B84C(s8 *);                      /* extern */

/**
 * Handles hit effect shared by Hydro Pump, Ice Beam, Hyper Beam, Solar Beam, Waterfall, and Sky
 * Attack
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Hydro Pump, Hyper Beam, Ice Beam and Waterfall (the sweep used only the charge turn of
 * Solar Beam and Sky Attack).
 */
void BattleAnim_RunStrongOutwardMovingLargeHitSpark(Particle* arg0) {
    s16 temp_v0;

    temp_v0 = arg0->lifecycle;
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_8214B84C(arg0);
        break;
    case 2:
        Particle_ApproachPrimAlpha(arg0, 0x20, 0x16);
        Particle_AnimateFramesForwardLoopedThenAdvance(arg0, 0, 7, 1, 2, 0);
        break;
    case 3:
        Particle_MarkInactive(arg0);
        break;
    }
    if (Particle_IsRunning(arg0) != 0) {
        Particle_ApproachStepMagnitude(arg0, 3.4f, 1.0f);
        Particle_AddVelocityFromRotationTemplate1(arg0);
    }
}

/**
 * Inits a Blizzard hit cold-air puff: recolored from its palette pair, scale 1.0, 5 units forward,
 * speed 4, a random direction.
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Blizzard.
 */
void BattleAnim_SetupBlizzardHitUpwardColdAir(Particle* arg0) {
    Particle_SpawnIndex_GetS16_0C038(arg0);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, Particle_GetByteParam1(arg0));
    Particle_SetScaleScaled(arg0, 1.0f);
    Particle_AddPositionOffsetAlongRotationY(arg0, 5.0f);
    Particle_StepMagnitude_SetScaled_0AD8C(arg0, 4.0f);
    Particle_Rotation_AddVec_0A52C(arg0, ParticleMath_RandomRange(0x10000), ParticleMath_RandomRange(0x10000), 0);
    Particle_AdvanceLifecycle(arg0);
}

void Particle_MarkInactive(Particle* arg0);                      /* extern */
s32 Particle_IsRunning(Particle* arg0);                          /* extern */
M2C_UNK Particle_AnimateFramesForwardLoopedThenAdvance(s8 *, M2C_UNK, M2C_UNK, M2C_UNK, s32, s32); /* extern */
void Particle_AddVelocityFromRotationTemplate1(s32 arg0);                      /* extern */
M2C_UNK Particle_ApproachStepMagnitude(s8 *, f32, f32);    /* extern */
M2C_UNK Particle_ApproachPrimAlpha(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_8214B9A8(s8 *);                      /* extern */

/**
 * Handles the cold air that emanates upward from pokemon hit by blizzard
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Blizzard.
 */
void BattleAnim_RunBlizzardHitUpwardColdAir(Particle* arg0) {
    s16 temp_v0;

    temp_v0 = arg0->lifecycle;
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_8214B9A8(arg0);
        break;
    case 2:
        Particle_ApproachPrimAlpha(arg0, 0x20, 0x16);
        Particle_AnimateFramesForwardLoopedThenAdvance(arg0, 0, 7, 1, 2, 0);
        break;
    case 3:
        Particle_MarkInactive(arg0);
        break;
    }
    if (Particle_IsRunning(arg0) != 0) {
        Particle_ApproachStepMagnitude(arg0, 2.5f, 0.75f);
        Particle_AddVelocityFromRotationTemplate1(arg0);
    }
}

/**
 * Inits a Water Gun hit splash: recolored from its palette pair, scale 0.6, 5 units forward, speed
 * 3, a random direction.
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Water Gun.
 */
void BattleAnim_SetupWaterGunHitEffect(Particle* arg0) {
    Particle_SpawnIndex_GetS16_0C038(arg0);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, Particle_GetByteParam1(arg0));
    Particle_SetScaleScaled(arg0, 0.6f);
    Particle_AddPositionOffsetAlongRotationY(arg0, 5.0f);
    Particle_StepMagnitude_SetScaled_0AD8C(arg0, 3.0f);
    Particle_Rotation_AddVec_0A52C(arg0, ParticleMath_RandomRange(0x10000), ParticleMath_RandomRange(0x10000), 0);
    Particle_AdvanceLifecycle(arg0);
}

void Particle_MarkInactive(Particle* arg0);                      /* extern */
s32 Particle_IsRunning(Particle* arg0);                          /* extern */
M2C_UNK Particle_AnimateFramesForwardLoopedThenAdvance(s8 *, M2C_UNK, M2C_UNK, M2C_UNK, s32, s32); /* extern */
void Particle_AddVelocityFromRotationTemplate1(s32 arg0);                      /* extern */
M2C_UNK Particle_ApproachStepMagnitude(s8 *, f32, f32);    /* extern */
M2C_UNK Particle_ApproachPrimAlpha(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_8214BAFC(s8 *);                      /* extern */

/**
 * Particle callback for a Water Gun hit splash: fades toward alpha 0x20 while playing frames 0 to
 * 7 once, then is marked inactive. While running it slows toward speed 1.5 and moves along its
 * rotation.
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Water Gun.
 */
void BattleAnim_RunWaterGunHitEffect(Particle* arg0) {
    s16 temp_v0;

    temp_v0 = arg0->lifecycle;
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_8214BAFC(arg0);
        break;
    case 2:
        Particle_ApproachPrimAlpha(arg0, 0x20, 0x16);
        Particle_AnimateFramesForwardLoopedThenAdvance(arg0, 0, 7, 1, 2, 0);
        break;
    case 3:
        Particle_MarkInactive(arg0);
        break;
    }
    if (Particle_IsRunning(arg0) != 0) {
        Particle_ApproachStepMagnitude(arg0, 1.5f, 0.4f);
        Particle_AddVelocityFromRotationTemplate1(arg0);
    }
}

/**
 * Inits a weak beam hit spark: random colors by variant (0: prim palette 8 and an env from set A;
 * 1: prim and env from set B; 2: a pair from set B), scale 0.8, 5 units forward, speed 3, a random
 * direction.
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Psybeam, Bubble Beam, Aurora Beam.
 */
void BattleAnim_SetupWeakBeamHitEffect(Particle* arg0) {
    UNUSED s32 pad; // FAKE: stack padding

    switch (Particle_GetByteParam1(arg0)) {
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

    Particle_SetScaleScaled(arg0, 0.8f);
    Particle_AddPositionOffsetAlongRotationY(arg0, 5.0f);
    Particle_StepMagnitude_SetScaled_0AD8C(arg0, 3.0f);
    Particle_Rotation_AddVec_0A52C(arg0, ParticleMath_RandomRange(0x10000), ParticleMath_RandomRange(0x10000), 0);
    Particle_AdvanceLifecycle(arg0);
}

s16 Particle_GetByteParam1();                                /* extern */
void Particle_MarkInactive(Particle* arg0);                      /* extern */
s32 Particle_IsRunning(Particle* arg0);                          /* extern */
M2C_UNK Particle_AnimateFramesForwardLoopedThenAdvance(s8 *, M2C_UNK, M2C_UNK, M2C_UNK, s32, s32); /* extern */
void Particle_AddVelocityFromRotationTemplate1(s32 arg0);                      /* extern */
M2C_UNK Particle_ApproachStepMagnitude(s8 *, f32, f32);    /* extern */
M2C_UNK Particle_ApproachPrimAlpha(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_821434FC(s8 *, s16);                 /* extern */
M2C_UNK func_82143530(s8 *, s16);                 /* extern */
M2C_UNK func_82143564(s8 *, s16);                 /* extern */
M2C_UNK func_821435E0(s8 *, s16);                 /* extern */
M2C_UNK func_8214BC58(s8 *);                      /* extern */
extern s32 D_8219A790;

/**
 * handles shared effect being hit by Psybeam, bubble beam, and aurora beam
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Psybeam, Bubble Beam, Aurora Beam.
 */
void BattleAnim_RunWeakBeamHitEffect(Particle* arg0) {
    s16 sp2E;
    s16 temp_v1;

    sp2E = Particle_GetByteParam1();
    temp_v1 = arg0->lifecycle;
    switch (temp_v1) {                              /* switch 1; irregular */
    case 1:                                         /* switch 1 */
        func_8214BC58(arg0);
        break;
    case 2:                                         /* switch 1 */
        Particle_ApproachPrimAlpha(arg0, 0x20, 0x16);
        Particle_AnimateFramesForwardLoopedThenAdvance(arg0, 0, 7, 1, 2, 0);
        break;
    case 3:                                         /* switch 1 */
        Particle_MarkInactive(arg0);
        break;
    }
    if (Particle_IsRunning(arg0) != 0) {
        Particle_ApproachStepMagnitude(arg0, 1.5f, 0.5f);
        Particle_AddVelocityFromRotationTemplate1(arg0);
        switch (sp2E) {                             /* switch 2; irregular */
        case 0:                                     /* switch 2 */
            func_821434FC(arg0, ParticleMath_RandomRange(6));
            return;
        case 1:                                     /* switch 2 */
            if (D_8219A790 == 0) {
                func_82143530(arg0, ParticleMath_RandomRange(6));
                func_82143564(arg0, ParticleMath_RandomRange(6));
                return;
            }
            break;
        case 2:                                     /* switch 2 */
            func_821435E0(arg0, ParticleMath_RandomRange(6));
            break;
        }
    }
}

/**
 * Inits a Tri Attack hit spark: recolored from its palette pair, growing from 0.6 to 1.2, placed
 * at one corner of a triangle (by variant), 5 units forward, speed 1, a random direction, hidden
 * for a start delay equal to its spawn index.
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Tri Attack.
 */
void BattleAnim_SetupTriAttackHitSpark(Particle* arg0) {
    s16 sp2E;
    s16 sp2C;
    s16 sp2A;

    sp2E = Particle_SpawnIndex_GetS16_0C038(arg0);
    sp2C = Particle_GetByteParam1(arg0);
    sp2A = Particle_FieldCE_GetS32_0C040(arg0);

    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, sp2C);
    Particle_SetScaleScaled(arg0, 0.6f);
    Particle_SetScaleTarget(arg0, 1.2f);
    Particle_SetScaleStep(arg0, 0.2f);

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

    Particle_AddPositionOffsetAlongRotationY(arg0, 5.0f);
    Particle_StepMagnitude_SetScaled_0AD8C(arg0, 1.0f);
    Particle_Rotation_AddVec_0A52C(arg0, ParticleMath_RandomRange(0x10000), ParticleMath_RandomRange(0x10000), 0);
    Particle_Param0_SetS16_0BCA8(arg0, sp2E);
    Particle_DisableRendering(arg0);
    Particle_AdvanceLifecycle(arg0);
}

M2C_UNK Particle_GetByteParam2();                            /* extern */
void Particle_MarkInactive(Particle* arg0);                      /* extern */
M2C_UNK func_8213CB3C(s8 *);                      /* extern */
M2C_UNK Particle_AnimateFramesForwardLoopedThenAdvance(s8 *, M2C_UNK, M2C_UNK, M2C_UNK, s32, s32); /* extern */
void Particle_AddVelocityFromRotationTemplate1(s32 arg0);                      /* extern */
M2C_UNK Particle_ApproachStepMagnitude(s8 *, f32, f32);    /* extern */
M2C_UNK func_821402B8(s8 *);                      /* extern */
M2C_UNK Particle_ApproachPrimAlpha(s8 *, M2C_UNK, M2C_UNK);    /* extern */
s32 func_821406B4(s8 *);                          /* extern */
M2C_UNK func_8214BEE8(s8 *);                      /* extern */

/**
 * Handles the Tri Attack hit spark
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Tri Attack.
 */
void BattleAnim_RunTriAttackHitSpark(Particle* arg0) {
    s16 temp_v1;

    Particle_GetByteParam2();
    temp_v1 = arg0->lifecycle;
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
        Particle_ApproachPrimAlpha(arg0, 0x20, 0x16);
        Particle_AnimateFramesForwardLoopedThenAdvance(arg0, 0, 7, 1, 2, 0);
        Particle_ApproachStepMagnitude(arg0, 1.5f, 0.1f);
        Particle_AddVelocityFromRotationTemplate1(arg0);
        return;
    case 4:
        Particle_MarkInactive(arg0);
        break;
    }
}

/**
 * Handles hit effect shared by Hydro Pump, Ice Beam, Hyper Beam, Solar Beam, Waterfall, and Sky
 * Attack
 * Seen in play (2026-11-13) (unattended Free Battle in which every Pokémon knows only Metronome, 40
 * turns): ran.
 * Seen in play (2026-11-14) (Metronome bench, one movie per move, 1P Onix vs Pinsir on Splash, exec
 * breakpoint): ran only for Aurora Beam, Hydro Pump, Ice Beam, Sky Attack, Solar Beam, Waterfall.
 * @unverified Name and comment from Stadium 1.
 */
void BattleAnim_SetupStrongOutwardMovingSmallHitSpark(Particle* arg0) {
    s16 sp2E = Particle_SpawnIndex_GetS16_0C038(arg0);
    s16 sp2C = Particle_GetByteParam1(arg0);

    Particle_SetRandomVelocityXYZ(arg0, 0, 15, 20);
    Particle_PositionOffset_AddYScaled_08E90(arg0, 5.0f);
    Particle_SetScaleScaled(arg0, 0.2f);
    Particle_StepMagnitude_SetScaled_0AD8C(arg0, 2.5f);
    Particle_Rotation_AddVec_0A52C(arg0, ParticleMath_RandomSigned(0x2000), ParticleMath_RandomSigned(0x2000), 0);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, sp2C);
    Particle_Param0_SetS16_0BCA8(arg0, sp2E * 4);
    Particle_DisableRendering(arg0);
    Particle_AdvanceLifecycle(arg0);
}

void Particle_DisableAndDetach(Particle* arg0);                      /* extern */
M2C_UNK func_8213CB3C(s8 *);                      /* extern */
M2C_UNK Particle_AnimateFramesForwardLoopedThenAdvance(s8 *, M2C_UNK, M2C_UNK, M2C_UNK, s32, s32); /* extern */
void Particle_AddVelocityFromRotationTemplate1(s32 arg0);                      /* extern */
M2C_UNK func_82140228(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK Particle_ApproachPrimAlpha(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK Particle_SetParam0(s8 *, M2C_UNK);             /* extern */
s32 func_82140690(s8 *);                          /* extern */
M2C_UNK func_8214C134(s8 *);                      /* extern */

/**
 * Particle lifecycle callback (shared descriptor19 delayed animated grow fade): steps the particle
 * by its lifecycle state.
 * Seen in play (2026-11-14) (Metronome bench, one movie per move, 1P Onix vs Pinsir on Splash, exec
 * breakpoint): ran only for Aurora Beam, Hydro Pump, Ice Beam, Sky Attack, Solar Beam, Waterfall.
 * @unverified Name guessed from the code.
 */
void BattleAnim_CallbackSharedDesc19DelayedAnimGrowFade(Particle* particle) {
    s16 temp_v0;

    temp_v0 = particle->lifecycle;
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_8214C134(particle);
        return;
    case 2:
        if (func_8213CA80(particle, particle->param0) != 0) {
            Particle_SetParam0(particle, 2);
            func_8213CB3C(particle);
            return;
        }
        return;
    case 3:
        Particle_AnimateFramesForwardLoopedThenAdvance(particle, 0, 7, 1, 1, 0);
        func_82140228(particle, 0x3F000000, 0x3DCCCCCD); // 0.5f, 0.1f
        Particle_AddVelocityFromRotationTemplate1(particle);
        if (func_82140690(particle) != 0) {
            Particle_ApproachPrimAlpha(particle, 0, 0x20);
            return;
        }
        break;
    case 4:
        Particle_DisableAndDetach(particle);
        break;
    }
}

/**
 * Lifecycle init: random offset, quarter scale, random tilt, random palette color at
 * alpha 200, delayed 4 frames per burst index.
 * Not reached in play (2026-11-13): did not run in the 165-move battle sweep (each move used once,
 * from the command menu to the end of its turn) or in a tour of the menus and a COM battle.
 * @unverified Name from Stadium 1.
 */
void BattleAnim_SetupUnusedIndexedFadeVariantA(Particle* arg0) {
    s16 sp2E = Particle_SpawnIndex_GetS16_0C038(arg0);

    Particle_GetByteParam1(arg0);
    Particle_SetRandomVelocityXYZ(arg0, 10, 20, 20);
    Particle_SetScaleScaled(arg0, 0.25f);
    Particle_StepMagnitude_SetScaled_0AD8C(arg0, 2.5f);
    Particle_Rotation_AddVec_0A52C(arg0, ParticleMath_RandomSigned(0x2000), ParticleMath_RandomSigned(0x2000), 0);
    ParticleGfx_RecolorPrimRandomPalette(arg0);
    Particle_SetPrimAlpha(arg0, 0xC8);
    Particle_Param0_SetS16_0BCA8(arg0, sp2E * 4);
    Particle_DisableRendering(arg0);
    Particle_AdvanceLifecycle(arg0);
}

void Particle_MarkInactive(Particle* arg0);                      /* extern */
M2C_UNK func_8213CB3C(s8 *);                      /* extern */
M2C_UNK Particle_AnimateFramesForwardLoopedThenAdvance(s8 *, M2C_UNK, M2C_UNK, M2C_UNK, s32, s32); /* extern */
void Particle_AddVelocityFromRotationTemplate1(s32 arg0);                      /* extern */
M2C_UNK func_82140228(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK Particle_ApproachPrimAlpha(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK Particle_SetParam0(s8 *, M2C_UNK);             /* extern */
s32 func_82140690(s8 *);                          /* extern */
M2C_UNK func_8214C300(s8 *);                      /* extern */

/**
 * Particle callback (no reference found) for BattleAnim_SetupUnusedIndexedFadeVariantA: waits
 * param0 frames, then fades.
 * @unverified Name guessed from the code.
 */
void BattleAnim_CallbackUnusedIndexedFadeA(Particle* particle) {
    s16 temp_v0;

    temp_v0 = particle->lifecycle;
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_8214C300(particle);
        return;
    case 2:
        if (func_8213CA80(particle, particle->param0) != 0) {
            Particle_SetParam0(particle, 2);
            func_8213CB3C(particle);
            return;
        }
        return;
    case 3:
        Particle_AnimateFramesForwardLoopedThenAdvance(particle, 0, 7, 1, 1, 0);
        func_82140228(particle, 0x3ECCCCCD, 0x3DCCCCCD); // 0.4f, 0.1f
        Particle_AddVelocityFromRotationTemplate1(particle);
        if (func_82140690(particle) != 0) {
            Particle_ApproachPrimAlpha(particle, 0, 0x20);
            return;
        }
        break;
    case 4:
        Particle_MarkInactive(particle);
        break;
    }
}

/**
 * Like BattleAnim_SetupUnusedIndexedFadeVariantA but larger, white with a random
 * environment color.
 * Not reached in play (2026-11-13): did not run in the 165-move battle sweep (each move used once,
 * from the command menu to the end of its turn) or in a tour of the menus and a COM battle.
 * @unverified Name from Stadium 1.
 */
void BattleAnim_SetupUnusedIndexedFadeVariantB(Particle* arg0) {
    s16 sp2E = Particle_SpawnIndex_GetS16_0C038(arg0);

    Particle_GetByteParam1(arg0);
    Particle_SetRandomVelocityXYZ(arg0, 10, 20, 20);
    Particle_SetScaleScaled(arg0, 0.4f);
    Particle_StepMagnitude_SetScaled_0AD8C(arg0, 2.5f);
    Particle_Rotation_AddVec_0A52C(arg0, ParticleMath_RandomSigned(0x2000), ParticleMath_RandomSigned(0x2000), 0);
    Particle_SetPrimColor(arg0, 0xFF, 0xFF, 0xFF); // #FFFFFF
    ParticleGfx_RecolorEnvRandomPalette(arg0);
    Particle_Param0_SetS16_0BCA8(arg0, sp2E * 4);
    Particle_DisableRendering(arg0);
    Particle_AdvanceLifecycle(arg0);
}

void Particle_MarkInactive(Particle* arg0);                      /* extern */
M2C_UNK func_8213CB3C(s8 *);                      /* extern */
M2C_UNK Particle_AnimateFramesForwardLoopedThenAdvance(s8 *, M2C_UNK, M2C_UNK, M2C_UNK, s32, s32); /* extern */
void Particle_AddVelocityFromRotationTemplate1(s32 arg0);                      /* extern */
M2C_UNK func_82140228(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_8214C4C4(s8 *);                      /* extern */

/**
 * Particle callback (no reference found) for BattleAnim_SetupUnusedIndexedFadeVariantB: waits
 * param0 frames, switches to texture frame 1, then fades.
 * @unverified Name guessed from the code.
 */
void BattleAnim_CallbackUnusedIndexedFadeB(Particle* particle) {
    s16 temp_v0;

    temp_v0 = particle->lifecycle;
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_8214C4C4(particle);
        return;
    case 2:
        if (func_8213CA80(particle, particle->param0) != 0) {
            func_8213CB3C(particle);
            Particle_SetTextureFrame(particle, 1);
            return;
        }
        return;
    case 3:
        func_82140228(particle, 0x3F000000, 0x3CCCCCCD); // 0.5f, 0.025f
        Particle_AnimateFramesForwardLoopedThenAdvance(particle, 2, 7, 1, 1, 0);
        Particle_AddVelocityFromRotationTemplate1(particle);
        return;
    case 4:
        Particle_MarkInactive(particle);
        break;
    }
}

/**
 * Inits a Bubble or Bubble Beam bubble around the target: scale 0.05, turning back around toward
 * the attacker, rotated about X by spawn index (a sixteenth of a turn apart) with a random
 * rotationY, a random env color, an 8 to 23 frame timer, speed 4.
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Bubble Beam, Bubble.
 */
void BattleAnim_SetupBubbleBubbleBeamSharedEffect(Particle* arg0) {
    Vec3s sp28;
    UNUSED s16 pad; // FAKE: stack padding
    s16 sp24;

    Particle_GetByteParam1(arg0);
    sp24 = Particle_SpawnIndex_GetS16_0C038(arg0);
    Particle_SetScaleScaled(arg0, 0.05f);
    Particle_SetRotationTargetXY(arg0, arg0->rotation.x, arg0->rotation.y + 0x8000);
    Particle_RotationStep_SetXY_0A3A0(arg0, 0x800, 0x300);
    sp28.x = sp24 << 0xC;
    sp28.y = ParticleMath_RandomSignedOffsetBySign(0x3000, 0x1000);
    sp28.z = 0;
    Particle_Rotation_AddVecFromVec3s_0A4F0(arg0, sp28);
    ParticleGfx_RecolorEnvRandomPalette(arg0);
    Particle_Param0_SetS16_0BCA8(arg0, ParticleMath_RandomRange(0x10) + 8);
    Particle_StepMagnitude_SetScaled_0AD8C(arg0, 4.0f);
    Particle_AdvanceLifecycle(arg0);
}

/**
 * Particle callback for end effects 34 and 53 (the Bubble/BubbleBeam hit): bubbles grow,
 * slow and turn toward their target, then bounce and fade.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (2 of the moves).
 * Seen in play (2026-11-14) (Metronome bench, one movie per move, 1P Onix vs Pinsir on Splash, exec
 * breakpoint): ran only for Bubble, BubbleBeam.
 * @unverified Name guessed from the code.
 */
void BattleAnim_CallbackEnd34And53Desc45SpinBounceFade(Particle* arg0) {
    switch (arg0->lifecycle) {
        case 1:
            BattleAnim_SetupBubbleBubbleBeamSharedEffect(arg0);
            break;

        case 2:
            Particle_ApproachScale(arg0, 0.15f, 0.01f);
            Particle_ApproachStepMagnitude(arg0, 1.0f, 0.7f);
            Particle_ApproachRotationTargetY(arg0);
            if (Particle_DecrementParam0ToZeroThenAdvance(arg0) != 0) {
                Particle_Param0_SetS16_0BCA8(arg0, ParticleMath_RandomRangeOffset(12, 32));
                if (arg0->rotation.y >= arg0->rotationTarget.y) {
                    Particle_RotationTarget_SetX_0A400(arg0, -0x4000);
                } else {
                    Particle_RotationTarget_SetX_0A400(arg0, 0x4000);
                }
            }
            break;

        case 3:
            Particle_ApproachRotationTargetX(arg0);
            Particle_ApproachStepMagnitude(arg0, 0.5f, 0.2f);
            Particle_DecrementParam0ToZeroThenAdvance(arg0);
            break;

        case 4:
            Particle_ApproachRotationTargetX(arg0);
            Particle_AnimateFramesForwardLoopedThenAdvance(arg0, 0, 3, 1, 1, 0);
            break;

        case 5:
            Particle_MarkInactive(arg0);
            break;
    }

    if (Particle_IsRunning(arg0) != 0) {
        Particle_MoveAlongRotationXYAlt(arg0);
    }
}

/**
 * Inits a Hydro Pump splash: scale 0.2, recolored from its palette pair, alpha 0xC8, a 24-frame
 * timer, speed 0.02.
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Hydro Pump.
 */
void BattleAnim_SetupHydroPumpColorShiftFade(Particle* arg0) {
    Particle_SetScaleScaled(arg0, 0.2f);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, Particle_GetByteParam1(arg0));
    Particle_SetPrimAlpha(arg0, 0xC8);
    Particle_Param0_SetS16_0BCA8(arg0, 24);
    arg0->stepMagnitude = 0.02f;
    Particle_AdvanceLifecycle(arg0);
}

M2C_UNK func_82137AB4(s8 *, M2C_UNK, M2C_UNK);    /* extern */
void Particle_MarkInactive(Particle* arg0);                      /* extern */
M2C_UNK func_82140228(s8 *, M2C_UNK, s32);        /* extern */
M2C_UNK Particle_ApproachPrimRed(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK Particle_ApproachPrimGreen(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK Particle_ApproachPrimBlue(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK Particle_ApproachEnvRed(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK Particle_ApproachEnvBlue(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK Particle_ApproachEnvGreen(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_82140548(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_821406B4(s8 *);                      /* extern */
M2C_UNK func_8214C8E0(s8 *);                      /* extern */

/**
 * Handles the growth, color shift, and fade of a Hydro Pump particle
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Hydro Pump.
 */
void BattleAnim_RunHydroPumpColorShiftFade(s8 *arg0) {
    s16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_8214C8E0(arg0);
        return;
    case 2:
        func_82140228(arg0, 0x40000000, 0x3CA3D70A); // 2.0f, 0.02f
        Particle_ApproachEnvGreen(arg0, 0xC8, 2);
        func_821406B4(arg0);
        return;
    case 3:
        func_82137AB4(arg0 + 0x70, 0x3C03126F, 0x3A83126F); // 0.008f, 0.001f
        func_82140228(arg0, 0x40000000, M2C_FIELD(arg0, s32 *, 0x70)); // 2.0f
        Particle_ApproachPrimRed(arg0, 0x78, 8);
        Particle_ApproachPrimBlue(arg0, 0x96, 8);
        Particle_ApproachPrimGreen(arg0, 0x96, 8);
        Particle_ApproachEnvRed(arg0, 0x78, 8);
        Particle_ApproachEnvBlue(arg0, 0x96, 8);
        Particle_ApproachEnvGreen(arg0, 0x96, 8);
        func_82140548(arg0, 0, 0xC);
        return;
    case 4:
        Particle_MarkInactive(arg0);
        return;
    }
}

/**
 * Inits a Water Gun splash: growing from 0.05 to 0.3, turned to one of three rotationY values about
 * a third of a turn apart (by variant), pushed 10 units along it, recolored from its palette pair,
 * alpha 0xC8, a 24-frame timer.
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Water Gun.
 */
void BattleAnim_SetupWaterGunEmitterColoration(Particle* arg0) {
    s16 sp26 = Particle_FieldCE_GetS32_0C040(arg0);

    Particle_SetScaleScaled(arg0, 0.05f);
    Particle_SetScaleTarget(arg0, 0.3f);
    Particle_SetScaleStep(arg0, 0.005f);

    switch (sp26) {
        case 0:
            Particle_Rotation_SetY_0A2B8(arg0, 0);
            break;

        case 1:
            Particle_Rotation_SetY_0A2B8(arg0, 0x5500);
            break;

        case 2:
            Particle_Rotation_SetY_0A2B8(arg0, -0x5600);
            break;
    }

    Particle_AddVelocityFromDirVector(arg0, 10.0f);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, Particle_GetByteParam1(arg0));
    Particle_SetPrimAlpha(arg0, 0xC8);
    Particle_Param0_SetS16_0BCA8(arg0, 24);
    Particle_AdvanceLifecycle(arg0);
}

void Particle_MarkInactive(Particle* arg0);                      /* extern */
M2C_UNK func_821402B8(s8 *);                      /* extern */
M2C_UNK Particle_ApproachPrimRed(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK Particle_ApproachPrimGreen(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK Particle_ApproachPrimBlue(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK Particle_ApproachEnvRed(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK Particle_ApproachEnvBlue(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK Particle_ApproachEnvGreen(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_82140548(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_821406B4(s8 *);                      /* extern */
M2C_UNK func_8214CA90(s8 *);                      /* extern */

/**
 * Handles the coloring of the burst emitter for Water gun
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Water Gun.
 */
void BattleAnim_RunWaterGunEmitterColoration(Particle* arg0) {
    s16 temp_v0;

    temp_v0 = arg0->lifecycle;
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_8214CA90(arg0);
        break;
    case 2:
        Particle_ApproachEnvGreen(arg0, 0xC8, 2);
        func_821406B4(arg0);
        break;
    case 3:
        Particle_ApproachPrimRed(arg0, 0x78, 8);
        Particle_ApproachPrimBlue(arg0, 0x96, 8);
        Particle_ApproachPrimGreen(arg0, 0x96, 8);
        Particle_ApproachEnvRed(arg0, 0x78, 8);
        Particle_ApproachEnvBlue(arg0, 0x96, 8);
        Particle_ApproachEnvGreen(arg0, 0x96, 8);
        func_82140548(arg0, 0, 0xC);
        break;
    case 4:
        Particle_MarkInactive(arg0);
        break;
    }
    func_821402B8(arg0);
}

/**
 * Inits a Hydro Pump or Water Gun hit droplet: scale 0.5, a random direction, 5 units forward,
 * speed 1, recolored from its palette pair.
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Water Gun, Hydro Pump.
 */
void BattleAnim_SetupHydroPumpWaterGunProjectileHit(Particle* arg0) {
    UNUSED s16 pad; // FAKE: stack padding
    s16 sp2C;

    Particle_SpawnIndex_GetS16_0C038(arg0);
    sp2C = Particle_GetByteParam1(arg0);
    Particle_SetScaleScaled(arg0, 0.5f);
    Particle_Rotation_AddVec_0A52C(arg0, ParticleMath_RandomRange(0x10000), ParticleMath_RandomRange(0x10000), 0);
    Particle_AddPositionOffsetAlongRotationY(arg0, 5.0f);
    Particle_StepMagnitude_SetScaled_0AD8C(arg0, 1.0f);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, sp2C);
    Particle_AdvanceLifecycle(arg0);
}

void Particle_MarkInactive(Particle* arg0);                      /* extern */
M2C_UNK func_8213CA80(s8 *, M2C_UNK);             /* extern */
M2C_UNK Particle_AddPosOffsetYScaled(s8 *, M2C_UNK);             /* extern */
void Particle_AddVelocityFromRotationTemplate1(s32 arg0);                      /* extern */
M2C_UNK func_82140228(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK Particle_ApproachPrimAlpha(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_8214CC90(s8 *);                      /* extern */

/**
 * Handles the projectile shared by being hit by water gun and hydro pump
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Water Gun, Hydro Pump.
 */
void BattleAnim_RunHydroPumpWaterGunProjectileHit(Particle* arg0) {
    s16 temp_v0;

    temp_v0 = arg0->lifecycle;
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_8214CC90(arg0);
        break;
    case 2:
        func_82140228(arg0, 0x3E99999A, 0x3CA3D70A); // 0.3f, 0.02f
        Particle_ApproachPrimAlpha(arg0, 0x20, 0xC);
        Particle_AddVelocityFromRotationTemplate1(arg0);
        Particle_AddPosOffsetYScaled(arg0, 0xBF800000); // -1.0f
        func_8213CA80(arg0, 0x10);
        break;
    case 3:
        Particle_MarkInactive(arg0);
        break;
    }
    if (arg0->worldPosition.y < 0.0f) {
        Particle_MarkInactive(arg0);
    }
}

/**
 * Starts the effect for Mega Punch
 * Effect start init 15 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used:
 * it ran for exactly Mega Punch.
 */
void BattleAnim_StartMegaPunchEffect(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(4, BattleAnim_RunMegaKickAndPunchProjectile, &gBattleAnimParticleDescriptors[8], 0, 4, 0x11, gBattleAnimCurrentAnchor, 0, 0);
}

M2C_UNK func_8213B560(M2C_UNK, M2C_UNK *, M2C_UNK *, M2C_UNK, s32, s32, s32, s32, s32); /* extern */
extern M2C_UNK D_8218E5C8;
extern s16 D_8219A80A;
extern M2C_UNK func_8214B0FC;

/**
 * Effect init that spawns the Mega Kick animation. Player sweep (all 165 moves used in battle):
 * only Mega Kick reached this function.
 * Effect start init 2 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used:
 * it ran for exactly Mega Kick.
 */
void BattleAnim_InitializeMegaKickUse(void) {
    func_8213B560(0, &func_8214B0FC, &D_8218E5C8, 0, 4, 0x11, (s32) D_8219A80A, 0, 0);
}

M2C_UNK func_8213B5D8(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK *, M2C_UNK *, s32, s32, s32, s32, s32, s32); /* extern */
extern M2C_UNK D_8218E7A8;
extern s16 D_8219A80A;
extern M2C_UNK func_821499D4;

/**
 * Effect init that spawns the Bubble animation. Player sweep (all 165 moves used in battle): only
 * Bubble reached this function.
 * Effect start init 48 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used:
 * it ran for exactly Bubble.
 */
void BattleAnim_InitializeBubbleUse(void) {
    func_8213B5D8(0, 1, 60, &func_821499D4, &D_8218E7A8, 0, 1, 0x11, (s32) D_8219A80A, 0, 0);
}

extern ParticleDescriptor D_8218E580[86];
extern M2C_UNK D_8218E728;
/**
 * Effect init for the end (impact) of the Bubble animation.
 * Effect end init 34 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used: it
 * ran for exactly Bubble.
 */
void BattleAnim_InitializeBubbleHit(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_RunDefaultHitSpark, &D_8218E728, 0, 1, 0x11, 9, 3, 5);
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_CallbackEnd34And53Desc45SpinBounceFade, &D_8218E7A8, 0, 0x10, 0x11, 9, 0, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(8, BattleAnim_CallbackEnd34And53Desc45SpinBounceFade, &D_8218E7A8, 0, 0x10, 0x11, 9, 0, 0);
}

/**
 * initializes water gun
 * Effect start init 6 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used:
 * it ran for exactly Water Gun.
 */
void BattleAnim_InitializeWaterGunUse(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(3, BattleAnim_RunWaterGunAndHydroPumpEmitterFade, &gBattleAnimParticleDescriptors[0xE], 0, 1, 0x11, gBattleAnimCurrentAnchor, 0, 1);
    BattleAnim_CreateEffectSlotForCurrentOwner(3, BattleAnim_RunWaterGunAndHydroPumpEmitterFade, &gBattleAnimParticleDescriptors[0x19], 0, 1, 0x11, gBattleAnimCurrentAnchor, 0, 1);
    BattleAnim_CreateEffectSlotForCurrentOwner(4, BattleAnim_RunWaterGunProjectile, &gDefaultParticleDescriptor, 0, 1, 0x11, gBattleAnimCurrentAnchor, 0, 0);
}

extern M2C_UNK D_8218E650;
extern M2C_UNK D_8218E7D8;
extern M2C_UNK D_8218E5D8;
/**
 * Effect init for the end (impact) of the Water Gun animation.
 * Effect end init 2 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used: it
 * ran for exactly Water Gun.
 */
void BattleAnim_InitializeWaterGunHit(void) {
    BattleAnim_CreateRepeatEffectSlotForCurrentOwner(0, 1, 0xF, BattleAnim_CallbackEndEffect2Descriptor19AnimatedAlphaFade, &D_8218E650, 0, 1, 0x10, gBattleAnimCurrentAnchor, 0x26, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(12, BattleAnim_CallbackEndEffect2Descriptor4BModeColorShiftFade, &D_8218E7D8, 0, 1, 0xA, 0, 0x4C, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(12, BattleAnim_CallbackEndEffect2Descriptor4BModeColorShiftFade, &D_8218E7D8, 0, 1, 0xA, 0, 0x4C, 1);
    BattleAnim_CreateEffectSlotForCurrentOwner(12, BattleAnim_CallbackEndEffect2Descriptor4BModeColorShiftFade, &D_8218E7D8, 0, 1, 0xA, 0, 0x4C, 2);
    BattleAnim_CreateRepeatEffectSlotForCurrentOwner(4, 1, 0x10, BattleAnim_CallbackEndEffects2And27Descriptor0AFallingSparkFade, &D_8218E5D8, 0, 2, 0x11, gBattleAnimCurrentAnchor, 0x4C, 0);
}

/**
 * initializes hydro pump
 * Effect start init 58 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used:
 * it ran for exactly Hydro Pump.
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
 * Effect end init 27 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used: it
 * ran for exactly Hydro Pump.
 */
void BattleAnim_InitializeHydroPumpHit(void) {
    func_8213BD78(4, 8, 0x33, 0x10, 0xFF);
    func_8213B560(0, &func_82145998, &D_8218E5A8, 0, 1, 0x10, (s32) D_8219A80A, 0x33, 0);
    func_8213B5D8(0, 5, 3, &BattleAnim_RunStrongOutwardMovingLargeHitSpark, &D_8218E650, 0, 8, 0x10, (s32) D_8219A80A, 0x26, 0);
    func_8213B5D8(10, 1, 8, &BattleAnim_CallbackSharedDesc19DelayedAnimGrowFade, &D_8218E650, 0, 3, 0x11, (s32) D_8219A80A, 0x26, 0);
    func_8213B560(12, &BattleAnim_RunHydroPumpColorShiftFade, &D_8218E7D8, 0, 1, 0xA, 0, 0x4C, 0);
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
 * Effect start init 47 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used:
 * it ran for exactly Ice Beam.
 */
void BattleAnim_InitializeIceBeamUse(void) {
    func_8213B6AC(0, 0, 0x20, 8, 0xA0);
    func_8213B644(0, 8, 0x33);
    func_8213B560(0, &func_8214B1F8, &D_8218E818, 0, 1, 0x10, (s32) D_8219A80A, 0x40, 0);
    func_8213B560(6, &BattleAnim_RunPulsingBeamEmanator, &D_8218E818, 0x6E, 1, 0x10, (s32) D_8219A80A, 0x40, 1);
    func_8213B5D8(0, 3, 30, &BattleAnim_IceBeamParticleUpdateA, &D_8218E7D0, 0, 1, 0x11, (s32) D_8219A80A, 0x13, 0);
}

M2C_UNK func_8213B560(M2C_UNK, M2C_UNK *, M2C_UNK *, M2C_UNK, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_8213B644(M2C_UNK, M2C_UNK, M2C_UNK);   /* extern */
M2C_UNK func_8213B6AC(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, s32); /* extern */
extern M2C_UNK D_8218E818;
extern s16 D_8219A80A;
extern M2C_UNK func_8214B1F8;

/**
 * Effect init that spawns the Psybeam animation. Player sweep (all 165 moves used in battle):
 * only Psybeam reached this function.
 * Effect start init 4 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used:
 * it ran for exactly Psybeam.
 */
void BattleAnim_InitializePsybeamUse(void) {
    func_8213B6AC(0, 0, 0x20, 8, 0xA0);
    func_8213B644(0, 8, 6);
    func_8213B560(0, &func_8214B1F8, &D_8218E818, 0, 1, 0x10, (s32) D_8219A80A, 0xD, 0);
    func_8213B560(6, &BattleAnim_RunPulsingBeamEmanator, &D_8218E818, 0x46, 1, 0x10, (s32) D_8219A80A, 0xD, 1);
}

M2C_UNK func_8213B5D8(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK *, M2C_UNK *, s32, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_8213B644(M2C_UNK, M2C_UNK, M2C_UNK);   /* extern */
extern M2C_UNK D_8218E7A8;
extern s16 D_8219A80A;

/**
 * Effect init that spawns the Bubblebeam animation. Player sweep (all 165 moves used in battle):
 * only Bubblebeam reached this function.
 * Effect start init 77, start init 120 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all
 * 165 moves used: it ran for exactly Bubble Beam.
 */
void BattleAnim_InitializeBubbleBeamUse(void) {
    func_8213B644(0, 8, 6);
    func_8213B5D8(0, 1, 60, &BattleAnim_RunBubbleBeamBubblesFast, &D_8218E7A8, 0, 4, 0x11, (s32) D_8219A80A, 0, 0);
    func_8213B5D8(0, 1, 60, &BattleAnim_RunBubbleBeamBubblesSlow, &D_8218E7A8, 0, 1, 0x11, (s32) D_8219A80A, 0, 0);
}

M2C_UNK func_8213B560(M2C_UNK, M2C_UNK *, M2C_UNK *, M2C_UNK, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_8213B644(M2C_UNK, M2C_UNK, M2C_UNK);   /* extern */
M2C_UNK func_8213B6AC(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, s32); /* extern */
extern M2C_UNK D_8218E818;
extern s16 D_8219A80A;
extern M2C_UNK func_8214B1F8;

/**
 * Effect init that spawns the Aurora Beam animation. Player sweep (all 165 moves used in battle):
 * only Aurora Beam reached this function.
 * Effect start init 26 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used:
 * it ran for exactly Aurora Beam.
 */
void BattleAnim_InitializeAuroraBeamUse(void) {
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

/**
 * Effect init that spawns the Hyper Beam animation. Player sweep (all 165 moves used in battle):
 * only Hyper Beam reached this function.
 * Effect start init 39 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used:
 * it ran for exactly Hyper Beam.
 */
void BattleAnim_InitializeHyperBeamUse(void) {
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

/**
 * Starts a beam effect: sets the spawn and tint timing, then queues func_8214B1F8 at once and
 * the pulsing beam emanator after 6 frames (lifetime 70).
 * Seen in play (2026-11-14) (Metronome bench, one movie per move, 1P Onix vs Pinsir on Splash, exec
 * breakpoint): ran only for Solar Beam.
 * @unverified Name guessed from the code.
 */
void BattleAnim_StartEffect70PulsingBeam(void) {
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

/**
 * Effect init that spawns the Tri Attack animation. Player sweep (all 165 moves used in battle):
 * only Tri Attack reached this function.
 * Effect start init 78 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used:
 * it ran for exactly Tri Attack.
 */
void BattleAnim_InitializeTriAttackUse(void) {
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

/**
 * Effect init that spawns the Waterfall animation. Player sweep (all 165 moves used in battle):
 * only Waterfall reached this function.
 */
void BattleAnim_InitializeWaterfallUseB(void) {
    func_8213BD78(4, 8, 0x33, 0xC, 0xFF);
    func_8213B560(0, &func_82145998, &D_8218E5A8, 0, 1, 0x10, (s32) D_8219A80A, 0x33, 0);
    func_8213B5D8(0, 5, 3, &BattleAnim_RunStrongOutwardMovingLargeHitSpark, &D_8218E650, 0, 8, 0x10, (s32) D_8219A80A, 0x26, 0);
    func_8213B5D8(10, 1, 3, &BattleAnim_CallbackSharedDesc19DelayedAnimGrowFade, &D_8218E650, 0, 8, 0x11, (s32) D_8219A80A, 0x26, 0);
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
extern M2C_UNK BattleAnim_IceBeamParticleUpdateB;

/**
 * sets being hit by ice beam
 * Effect end init 67 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used: it
 * ran for exactly Ice Beam.
 */
void BattleAnim_InitializeIceBeamHit(void) {
    func_8213BE70(0, 8, 0x33, 0x10, 0xDC, 0x20);
    func_8213B560(3, &func_82145998, &D_8218E5A8, 0, 1, 0x10, (s32) D_8219A80A, 0x33, 0);
    func_8213B5D8(0, 5, 3, &BattleAnim_RunStrongOutwardMovingLargeHitSpark, &D_8218E650, 0, 8, 0x10, (s32) D_8219A80A, 0x26, 0);
    func_8213B5D8(4, 4, 2, &func_8214B468, &D_8218E820, 0, 1, 0x10, (s32) D_8219A80A, 0x33, 0);
    func_8213B5D8(12, 1, 3, &BattleAnim_CallbackSharedDesc19DelayedAnimGrowFade, &D_8218E650, 0, 8, 0x11, (s32) D_8219A80A, 0x26, 0);
    func_8213B5D8(14, 4, 2, &BattleAnim_CallbackEnd67Desc3DAnimatedGravityFade, &D_8218E770, 0, 6, 0x10, 0x64, 0, 0);
    func_8213B5D8(0, 2, 6, &BattleAnim_IceBeamParticleUpdateB, &D_8218E798, 0, 8, 0x11, 9, 0x18, 0xB);
    func_8213B644(48, 0x20, 8);
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
 * Effect end init 68 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used: it
 * ran for exactly Psybeam.
 */
void BattleAnim_InitializePsybeamHit(void) {
    func_8213C060(4, 0x32, 0x20, 0xA0);
    func_8213B5D8(4, 4, 3, &func_8214B5A0, &D_8218E820, 0, 1, 0x10, (s32) D_8219A80A, 0, 0);
    func_8213B560(3, &func_82145A58, &D_8218E660, 0, 1, 0x10, (s32) D_8219A80A, 0x21, 0);
    func_8213B5D8(3, 5, 3, &BattleAnim_RunWeakBeamHitEffect, &D_8218E650, 0, 8, 0x10, (s32) D_8219A80A, 1, 0);
    func_8213B644(48, 0x20, 8);
}

extern ParticleDescriptor D_8218E588[86];
/**
 * Effect init for the end (impact) of the Bubble Beam animation.
 * Effect end init 53 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used: it
 * ran for exactly Bubble Beam.
 */
void BattleAnim_InitializeBubbleBeamHit(void) {
    BattleAnim_SpawnBeamBoomWaterfallHueChange(4, 0x8, 0x21, 0x10, 0xFF);
    BattleAnim_CreateEffectSlotForCurrentOwner(3, BattleAnim_RunExpandingHitSpark, &D_8218E5A8, 0, 1, 0x10, gBattleAnimCurrentAnchor, 0x33, 0);
    BattleAnim_CreateRepeatEffectSlotForCurrentOwner(3, 5, 3, BattleAnim_CallbackSharedDescriptor19RecolorAnimatedFade, &D_8218E650, 0, 8, 0x10, gBattleAnimCurrentAnchor, 0, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_CallbackEnd34And53Desc45SpinBounceFade, &D_8218E7A8, 0, 0x10, 0x11, 9, 0, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(8, BattleAnim_CallbackEnd34And53Desc45SpinBounceFade, &D_8218E7A8, 0, 0x10, 0x11, 9, 0, 0);
    BattleAnim_SpawnGlobalTintColorFadeDetach(48, 0x20, 0x8);
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
 * Effect end init 69 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used: it
 * ran for exactly Aurora Beam.
 */
void BattleAnim_InitializeAuroraBeamHit(void) {
    func_8213C060(4, 0x32, 0x20, 0xA0);
    func_8213B560(4, &func_8214B77C, &D_8218E820, 0, 9, 0x10, (s32) D_8219A80A, 0, 0);
    func_8213B5D8(3, 5, 3, &BattleAnim_RunWeakBeamHitEffect, &D_8218E650, 0, 8, 0x10, (s32) D_8219A80A, 0, 0);
    func_8213B5D8(12, 1, 3, &BattleAnim_CallbackSharedDesc19DelayedAnimGrowFade, &D_8218E650, 0, 8, 0x11, (s32) D_8219A80A, 0x39, 0);
    func_8213B644(22, 0x20, 8);
}

extern ParticleDescriptor D_8218E588[86];
extern ParticleDescriptor D_8218E588[86];
/**
 * Effect init for the end (impact) of the Hyper Beam animation.
 * Effect end init 70 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used: it
 * ran for exactly Hyper Beam.
 */
void BattleAnim_InitializeHyperBeamHit(void) {
    UNUSED s32 pad; // FAKE: stack padding

    BattleAnim_SpawnOwnerTintRampDetach(0, 0x17, 0xFF, 0, 8);
    BattleAnim_SpawnBeamBoomWaterfallHueChange(4, 0x17, 0x17, 0x10, 0xFF);
    BattleAnim_CreateEffectSlotForCurrentOwner(3, BattleAnim_RunExpandingHitSpark, &D_8218E5A8, 0, 1, 0x10, gBattleAnimCurrentAnchor, 0x17, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_RunStrongBeamHitEffect, &D_8218E728, 0, 1, 0x10, gBattleAnimCurrentAnchor, 0x2C, 0);
    BattleAnim_CreateRepeatEffectSlotForCurrentOwner(4, 8, 1, BattleAnim_RunStrongBeamHitEffect, &D_8218E820, 0, 1, 0x10, gBattleAnimCurrentAnchor, 0x2C, 0);
    BattleAnim_CreateRepeatEffectSlotForCurrentOwner(3, 5, 2, BattleAnim_CallbackSharedDescriptor19AnimatedFadeMotion, &D_8218E650, 0, 8, 0x10, gBattleAnimCurrentAnchor, 0xF, 0);
    BattleAnim_InitializeHyperBeamHitSequence();
}

extern ParticleDescriptor D_8218E588[86];
/**
 * Starts end effect 71: a hue change, strong beam hits, an expanding hit spark, waves of
 * fading particles, and a global tint fade at frame 22.
 * Not reached in play (2026-11-13): did not run in the 165-move battle sweep (each move used once,
 * from the command menu to the end of its turn) or in a tour of the menus and a COM battle.
 * Seen in play (2026-11-14) (Metronome bench, one movie per move, 1P Onix vs Pinsir on Splash, exec
 * breakpoint): ran only for Sky Attack, Solar Beam.
 * @unverified Name guessed from the code.
 */
void BattleAnim_End71PaletteApproachExpandingScaleFades(void) {
    UNUSED s32 pad; // FAKE: stack padding

    BattleAnim_SpawnBeamBoomWaterfallHueChange(4, 0x8, 0x17, 0x10, 0xFF);
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_RunStrongBeamHitEffect, &D_8218E728, 0, 1, 0x10, gBattleAnimCurrentAnchor, 0x17, 0);
    BattleAnim_CreateRepeatEffectSlotForCurrentOwner(4, 4, 1, BattleAnim_RunStrongBeamHitEffect, &D_8218E820, 0, 1, 0x10, gBattleAnimCurrentAnchor, 0x17, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(3, BattleAnim_RunExpandingHitSpark, &D_8218E5A8, 0, 1, 0x10, gBattleAnimCurrentAnchor, 0x18, 0);
    BattleAnim_CreateRepeatEffectSlotForCurrentOwner(3, 5, 3, BattleAnim_CallbackSharedDescriptor19AnimatedFadeMotion, &D_8218E650, 0, 8, 0x10, gBattleAnimCurrentAnchor, 0x17, 0);
    BattleAnim_CreateRepeatEffectSlotForCurrentOwner(12, 1, 3, BattleAnim_CallbackSharedDesc19DelayedAnimGrowFade, &D_8218E650, 0, 8, 0x11, gBattleAnimCurrentAnchor, 0x17, 0);
    BattleAnim_SpawnGlobalTintColorFadeDetach(22, 0x20, 0x8);
}

/**
 * initializes being hit by tri attack
 * Effect end init 86 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used: it
 * ran for exactly Tri Attack.
 */
void BattleAnim_InitializeTriAttackHit(void) {
    BattleAnim_CreateRepeatEffectSlotForCurrentOwner(0, 2, 8, BattleAnim_CallbackEndEffect86Descriptor19ModePositionedAnimFade, &gBattleAnimParticleDescriptors[0x19], 0, 1, 0x11, gBattleAnimCurrentAnchor, 0x49, 0);
    BattleAnim_CreateRepeatEffectSlotForCurrentOwner(0, 2, 8, BattleAnim_CallbackEndEffect86Descriptor19ModePositionedAnimFade, &gBattleAnimParticleDescriptors[0x19], 0, 1, 0x11, gBattleAnimCurrentAnchor, 0x4A, 1);
    BattleAnim_CreateRepeatEffectSlotForCurrentOwner(0, 2, 8, BattleAnim_CallbackEndEffect86Descriptor19ModePositionedAnimFade, &gBattleAnimParticleDescriptors[0x19], 0, 1, 0x11, gBattleAnimCurrentAnchor, 0x4B, 2);
}
