#include "pokemon.h"
/* Fixed-layout split; original translation-unit boundaries remain unconfirmed. */
#include "battle.h"

// Declared here instead of in a header: the callers of these disagree on their types.
M2C_UNK Particle_AnimateFramesForwardLooped(s8 *, M2C_UNK, M2C_UNK, M2C_UNK, s32, s32);
M2C_UNK Particle_AnimateFramesForwardLoopedThenAdvance(s8 *, M2C_UNK, M2C_UNK, M2C_UNK, s32, s32);
M2C_UNK Particle_ApplyMotionStep(s8 *);
M2C_UNK Particle_ApproachPrimAlpha(s8 *, M2C_UNK, M2C_UNK);
M2C_UNK Particle_IncrementPhase(s8 *);
M2C_UNK Particle_SetMagnitudeStepScaled(s8 *, M2C_UNK);
M2C_UNK Particle_SetParam0(s8 *, M2C_UNK);
M2C_UNK func_8213E77C(s8 *);
s32 func_82140690(s8 *);
void BattleAnim_RunDigHitDust(Particle* arg0);
void BattleAnim_RunDigHitRocks(Particle* arg0);
void func_82164AD0(Particle* arg0);

/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Acid Armor.
 */
void BattleAnim_RunAcidArmorUseEffect2(Particle* arg0) {
    switch (arg0->lifecycle) {
        case 1:
            BattleAnim_SetupAcidArmorUseEffect2(arg0);
            break;

        case 2:
            if (Particle_DecrementParam0ToZeroThenAdvance(arg0) != 0) {
                Particle_Param0_SetS16_0BCA8(arg0, ParticleMath_RandomRange(4) + 4);
                Particle_EnableRendering(arg0);
            }
            break;

        case 3:
            Particle_DecrementParam0ToZeroThenAdvance(arg0);
            Particle_AddVelocityYFromFieldOffset74(arg0);
            break;

        case 4:
            Particle_AnimateFramesForwardLoopedThenAdvance(arg0, 0, 7, 1, 2, 0);
            Particle_PrimAlpha_Approach_0BC2C(arg0, 0x40, 4);
            Particle_AddVelocityYFromFieldOffset74(arg0);
            break;

        case 5:
            Particle_MarkInactive(arg0);
            break;
    }
}


/**
 * Seen in play (2026-11-13) (unattended Free Battle in which every Pokémon knows only Metronome, 40
 * turns): ran.
 * @unverified Name was previously used only by callers of this address; the definition was still func_.
 */
void BattleAnim_InitSharedVerticalFadeParticle(Particle* arg0) {
    Vec3s sp30;  /* scratch rotation vector used by the later cases */
    /* values the effect descriptor stored on the particle */
    s16 sp2E = Particle_SpawnIndex_GetS16_0C038(arg0);
    u16 sp2C = Particle_FieldCE_GetS32_0C040(arg0);

    /* common setup shared by every variant */
    Particle_ScratchB_SetS16_0BFEC(arg0, 2);
    Particle_Param0_SetS16_0BCA8(arg0, sp2E * 2);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, Particle_FieldCF_GetS16_0C058(arg0));

    /* sp2C selects which variant of the effect this particle belongs to (0..12) */
    switch (sp2C) {
        case 0:
            Particle_SetScaleScaled(arg0, 1.0f);
            Particle_SetRandomVelocityXYZ(arg0, 0xA, 0xA, 0xA);
            Particle_StepMagnitude_SetScaled_0AD8C(arg0, (ParticleMath_RandomRange(0x32) * 0.02f) + 0.5f);
            Particle_SetPrimAlpha(arg0, 0x64);
            Particle_ScratchA_SetS16_0BF4C(arg0, 4);
            break;

        case 1:
            Particle_SetScaleScaled(arg0, 1.0f);
            Particle_SetRandomVelocityXYZ(arg0, 0xA, 0xF, 0x3C);
            Particle_StepMagnitude_SetScaled_0AD8C(arg0, (ParticleMath_RandomRange(0x32) * 0.04f) + 1.0f);
            Particle_SetPrimAlpha(arg0, 0x64);
            Particle_ScratchA_SetS16_0BF4C(arg0, 4);
            break;

        case 2:
            Particle_SetScaleScaled(arg0, 1.5f);
            Particle_SetRandomVelocityXYZ(arg0, 0xF, 0x14, 0x19);
            Particle_StepMagnitude_SetScaled_0AD8C(arg0, (ParticleMath_RandomRange(0x32) * 0.07f) + 4.0f);
            Particle_SetPrimAlpha(arg0, 0xA0);
            Particle_Param0_SetS16_0BCA8(arg0, sp2E);
            Particle_ScratchA_SetS16_0BF4C(arg0, 0xA);
            break;

        case 3:
            Particle_SetScaleScaled(arg0, 1.0f);
            Particle_SetRandomVelocityXYZ(arg0, 0xA, 0, 0x19);
            Particle_AddPositionOffsetAlongRotationY(arg0, 10.0f);
            Particle_PositionOffset_AddYScaled_08E90(arg0, 5.0f);
            Particle_StepMagnitude_SetScaled_0AD8C(arg0, (ParticleMath_RandomRange(0xA) * 0.05f) + 0.2f);
            Particle_SetPrimAlpha(arg0, 0xFF);
            Particle_ScratchA_SetS16_0BF4C(arg0, 2);
            Particle_ScratchB_SetS16_0BFEC(arg0, 2);
            break;

        case 8:
            /* Stadium 1 calls a separate helper here that also adjusts the offset
               for particular species.  The Zero code has only that helper's
               default path (no species adjustment) written out inline: the
               random offset, the XZ offset of 10.0 and the Y offset of 5.0. */
            Particle_SetScaleScaled(arg0, 1.2f);
            Particle_SetRandomVelocityXYZ(arg0, 0xA, 0, 0x23);
            Particle_AddPositionOffsetAlongRotationY(arg0, 10.0f);
            Particle_PositionOffset_AddYScaled_08E90(arg0, 5.0f);
            Particle_StepMagnitude_SetScaled_0AD8C(arg0, (ParticleMath_RandomRange(0xA) * 0.05f) + 0.2f);
            Particle_SetPrimAlpha(arg0, 0xFF);
            Particle_ScratchA_SetS16_0BF4C(arg0, 2);
            Particle_ScratchB_SetS16_0BFEC(arg0, 2);
            Particle_Param0_SetS16_0BCA8(arg0, sp2E);
            break;

        case 12:
            Particle_SetScaleScaled(arg0, 1.2f);
            Particle_SetRandomVelocityXYZ(arg0, 0xA, 0, 0x28);
            Particle_AddPositionOffsetAlongRotationY(arg0, 10.0f);
            Particle_PositionOffset_AddYScaled_08E90(arg0, 5.0f);
            Particle_StepMagnitude_SetScaled_0AD8C(arg0, (ParticleMath_RandomRange(0xA) * 0.05f) + 0.2f);
            Particle_SetPrimAlpha(arg0, 0xFF);
            Particle_ScratchA_SetS16_0BF4C(arg0, 2);
            Particle_ScratchB_SetS16_0BFEC(arg0, 2);
            Particle_Param0_SetS16_0BCA8(arg0, sp2E);
            break;

        case 4:
            Particle_SetScaleScaled(arg0, 0.5f);
            Particle_SetRandomVelocityXYZ(arg0, 0xA, 0, 0x14);
            Particle_StepMagnitude_SetScaled_0AD8C(arg0, (ParticleMath_RandomRange(0xA) * 0.05f) + 0.5f);
            Particle_SetPrimAlpha(arg0, 0xFF);
            Particle_ScratchA_SetS16_0BF4C(arg0, 2);
            Particle_ScratchB_SetS16_0BFEC(arg0, 2);
            break;

        case 5:
            Particle_SetScaleScaled(arg0, 1.0f);
            Particle_SetRandomVelocityXYZ(arg0, 0xF, 0xF, 0xF);
            Particle_StepMagnitude_SetScaled_0AD8C(arg0, (ParticleMath_RandomRange(0x32) * 0.02f) + 1.0f);
            Particle_SetPrimAlpha(arg0, 0x80);
            Particle_ScratchA_SetS16_0BF4C(arg0, 4);
            break;

        case 6:
            Particle_SetScaleScaled(arg0, 0.5f);
            Particle_SetRandomVelocityXYZ(arg0, 5, 5, 5);
            Particle_StepMagnitude_SetScaled_0AD8C(arg0, 0.5f);
            Particle_SetPrimAlpha(arg0, 0xC8);
            Particle_ScratchA_SetS16_0BF4C(arg0, 4);
            break;

        case 7:
            Particle_SetScaleScaled(arg0, 0.5f);
            Particle_SetRandomVelocityXYZ(arg0, 0xA, 0, 5);
            Particle_PositionOffset_AddYScaled_08E90(arg0, 10.0f);
            Particle_StepMagnitude_SetScaled_0AD8C(arg0, (ParticleMath_RandomRange(0x14) * 0.02f) + 0.5f);
            Particle_SetPrimAlpha(arg0, 0xC8);
            Particle_ScratchA_SetS16_0BF4C(arg0, 4);
            break;

        case 9:
            Particle_SetScaleScaled(arg0, 1.0f);
            Particle_SetRandomVelocityXYZ(arg0, 0xA, 0, 0xA);
            sp30.x = ParticleMath_RandomSigned(0x1800) - 0x4000;
            sp30.y = ParticleMath_RandomRange(0x10000);
            sp30.z = 0;
            Particle_Rotation_AddVecFromVec3s_0A4F0(arg0, sp30);
            Particle_StepMagnitude_SetScaled_0AD8C(arg0, (ParticleMath_RandomRange(0x14) * 0.15f) + 3.0f);
            Particle_SetMotionStepFromRotationXY(arg0);
            Particle_Param0_SetS16_0BCA8(arg0, sp2E);
            Particle_ScratchA_SetS16_0BF4C(arg0, 0xA);
            break;

        case 10:
            Particle_SetScaleScaled(arg0, 0.8f);
            Particle_SetRandomVelocityXYZ(arg0, 0xF, 0, 0xF);
            sp30.x = ParticleMath_RandomSigned(0x1000) - 0x4000;
            sp30.y = ParticleMath_RandomRange(0x10000);
            sp30.z = 0;
            Particle_Rotation_AddVecFromVec3s_0A4F0(arg0, sp30);
            Particle_StepMagnitude_SetScaled_0AD8C(arg0, (ParticleMath_RandomRange(0x14) * 0.15f) + 4.0f);
            Particle_SetMotionStepFromRotationXY(arg0);
            Particle_Param0_SetS16_0BCA8(arg0, 0);
            Particle_ScratchA_SetS16_0BF4C(arg0, 0xA);
            break;

        case 11:
            Particle_SetScaleScaled(arg0, 0.05f);
            Particle_SetRandomVelocityXYZ(arg0, 0xA, 0, 0xA);
            sp30.x = ParticleMath_RandomSigned(0x1000) - 0x4000;
            sp30.y = ParticleMath_RandomRange(0x10000);
            sp30.z = 0;
            Particle_Rotation_AddVecFromVec3s_0A4F0(arg0, sp30);
            Particle_StepMagnitude_SetScaled_0AD8C(arg0, (ParticleMath_RandomRange(0x14) * 0.3f) + 6.0f);
            Particle_SetMotionStepFromRotationXY(arg0);
            Particle_SetPrimAlpha(arg0, 0xFF);
            Particle_Param0_SetS16_0BCA8(arg0, sp2E);
            Particle_ScratchA_SetS16_0BF4C(arg0, 0xA);
            break;
    }

    /* the particle starts hidden and its lifecycle is advanced once */
    Particle_DisableRendering(arg0);
    Particle_AdvanceLifecycle(arg0);
}


/**
 * Particle callback: shared vertical-fade init, wait for the spawn step, the later stages,
 * then inactive.
 */
void func_82164AD0(Particle* arg0) {
    s16 temp_v0;

    temp_v0 = arg0->lifecycle;
    switch (temp_v0) {                              /* irregular */
    case 1:
        BattleAnim_InitSharedVerticalFadeParticle(arg0);
        return;
    case 2:
        if (func_821406B4(arg0) != 0) {
            func_8213CB3C(arg0);
            return;
        }
        return;
    case 3:
        Particle_AnimateFramesForwardLoopedThenAdvance(arg0, 0, 7, 1, (s32) arg0->scratchB, 0);
        Particle_ApproachPrimAlpha(arg0, 0x40, M2C_FIELD(arg0, u8 *, 0xAB));
        func_8213E77C(arg0);
        return;
    case 4:
        Particle_MarkInactive(arg0);
        break;
    }
}


/**
 * Moves a particle to the owner's mouth or front: 50 units forward and 30 up by default,
 * with per-species distances.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (1 of the moves).
 * @unverified Name from Stadium 1.
 */
void BattleAnim_ApplySpeciesKeyedSpawnOffset(Particle* arg0) {
    f32 sp1C = 50.0f;
    f32 sp18 = 30.0f;

    switch (BattleAnim_GetOwnerSpecies(arg0->pokemon)) {
        case VENUSAUR:
            sp1C = 40.0f;
            break;

        case ONIX:
            sp1C = 25.0f;
            break;

        case EXEGGUTOR:
            sp1C = 35.0f;
            break;

        case CHANSEY:
            sp18 = 35.0f;
            break;

        case KANGASKHAN:
            sp1C = 40.0f;
            break;

        case GYARADOS:
            sp1C = 20.0f;
            break;

        case LAPRAS:
            sp1C = 30.0f;
            break;
    }

    Particle_AddPositionOffsetAlongRotationY(arg0, sp1C);
    Particle_PositionOffset_AddYScaled_08E90(arg0, sp18);
    Particle_MagnitudeStep_SetScaled_0ADA4(arg0, 0.4f);
}


/**
 * Moves: Surf (hit)
 * TODO: Human contributor add screenshot
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Surf.
 */
void BattleAnim_RunSplashOfWater(Particle* arg0) {
    s16 temp_v0;
    s16 temp_v0_2;

    temp_v0 = arg0->lifecycle;
    switch (temp_v0) {                              /* switch 1; irregular */
    case 1:                                         /* switch 1 */
        BattleAnim_InitSharedVerticalFadeParticle(arg0);
        func_82164B9C(arg0);
        break;
    case 2:                                         /* switch 1 */
        if (func_821406B4(arg0) != 0) {
            func_8213CB3C(arg0);
            func_8213D238(arg0);
            Particle_SetParam0(arg0, 0x14);
        }
        break;
    case 3:                                         /* switch 1 */
        Particle_AnimateFramesForwardLooped(arg0, 0, 7, 1, 2, 0);
        Particle_ApproachPrimAlpha(arg0, 0x40, 2);
        func_8213E7F4(arg0);
        func_8213E71C(arg0, 0x41200000);
        func_821406B4(arg0);
        break;
    case 4:                                         /* switch 1 */
        Particle_MarkInactive(arg0);
        break;
    }
    temp_v0_2 = arg0->phase;
    switch (temp_v0_2) {                            /* switch 2; irregular */
    case 1:                                         /* switch 2 */
        func_8213F6DC(arg0, 0x3F800000, 0x3DCCCCCD);
        if (func_8213D294(arg0, 4) != 0) {
            Particle_IncrementPhase(arg0);
            Particle_SetMagnitudeStepScaled(arg0, 0x3E4CCCCD);
            return;
        }
        return;
    case 2:                                         /* switch 2 */
        func_8213F6DC(arg0, 0xBF000000, 0x3E4CCCCD);
        break;
    }
}

/**
 * Moves: Dig (hit)
 * TODO: Human contributor add screenshot
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Dig.
 */
void BattleAnim_RunDigHitDust(Particle* arg0) {
    s16 temp_v0;

    temp_v0 = arg0->lifecycle;
    switch (temp_v0) {                              /* irregular */
    case 1:
        BattleAnim_InitSharedVerticalFadeParticle(arg0);
        break;
    case 2:
        if (func_821406B4(arg0) != 0) {
            func_8213CB3C(arg0);
        }
        break;
    case 3:
        Particle_AnimateFramesForwardLoopedThenAdvance(arg0, 0, 7, 1, (s32) arg0->scratchB, 0);
        Particle_ApproachPrimAlpha(arg0, 0x40, M2C_FIELD(arg0, u8 *, 0xAB));
        break;
    case 4:
        Particle_MarkInactive(arg0);
        break;
    }
    if (Particle_IsRunning(arg0) != 0) {
        func_8213F940(arg0, 0xC0000000, 0x3E99999A);
        Particle_ApplyMotionStep(arg0);
    }
}

/**
 * Moves: Dig (hit)
 * TODO: Human contributor add screenshot
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Dig.
 */
void BattleAnim_RunDigHitRocks(Particle* arg0) {
    s16 temp_v0;

    temp_v0 = arg0->lifecycle;
    switch (temp_v0) {                              /* irregular */
    case 1:
        BattleAnim_InitSharedVerticalFadeParticle(arg0);
        break;
    case 2:
        if (func_821406B4(arg0) != 0) {
            func_8213CB3C(arg0);
        }
        break;
    case 3:
        if (arg0->worldPosition.y < 0.0f) {
            Particle_MarkInactive(arg0);
        }
        break;
    }
    if (Particle_IsRunning(arg0) != 0) {
        func_8213F940(arg0, 0xC1200000, 0x3F4CCCCD);
        Particle_ApplyMotionStep(arg0);
    }
}

/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Barrage.
 */
void BattleAnim_SetupBarrageUseEffect2(Particle* arg0) {
    UNUSED s32 pad; // FAKE: stack padding

    Particle_SpawnIndex_GetS16_0C038(arg0);
    Particle_FieldCD_GetU8_0C048(arg0);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, Particle_FieldCF_GetS16_0C058(arg0));
    Particle_SetScaleScaled(arg0, 0.5f);
    Particle_Rotation_AddVec_0A52C(arg0, ParticleMath_RandomRange(0x10000), ParticleMath_RandomRange(0x10000), 0);
    Particle_StepMagnitude_SetScaled_0AD8C(arg0, 0.75f);
    Particle_SetPrimAlpha(arg0, 0xFF);
    Particle_AdvanceLifecycle(arg0);
}

/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Barrage.
 */
void BattleAnim_RunBarrageUseEffect2(Particle* arg0) {
    switch (arg0->lifecycle) {
        case 1:
            BattleAnim_SetupBarrageUseEffect2(arg0);
            break;

        case 2:
            Particle_AnimateFramesForwardLoopedThenAdvance(arg0, 0, 7, 1, 2, 0);
            Particle_PrimAlpha_Approach_0BC2C(arg0, 0x80, 8);
            Particle_AddVelocityFromRotationTemplate1(arg0);
            break;

        case 3:
            Particle_MarkInactive(arg0);
            break;
    }
}

/**
 * Lifecycle init for a burst child: random direction around straight back, random speed,
 * palette color from the CF parameter.
 * Not reached in play (2026-11-13): did not run in the 165-move battle sweep (each move used once,
 * from the command menu to the end of its turn) or in a tour of the menus and a COM battle.
 * @unverified Name from Stadium 1.
 */
void BattleAnim_CallbackDescriptor50BurstChild_InitParticle(Particle* arg0) {
    Vec3s sp28;
    s16 sp26 = Particle_FieldCF_GetS16_0C058(arg0);

    Particle_SpawnIndex_GetS16_0C038(arg0);
    sp28.x = ParticleMath_RandomSignedOffset(0x1000, -0x2000);
    sp28.y = ParticleMath_RandomSignedOffset(0x1000, 0x8000);
    sp28.z = 0;
    Particle_Rotation_AddVecFromVec3s_0A4F0(arg0, sp28);
    Particle_SetScaleScaled(arg0, 0.05f);
    Particle_SetScaleTarget(arg0, 0.25f);
    Particle_SetScaleStep(arg0, 0.02f);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, sp26);
    Particle_Param0_SetS16_0BCA8(arg0, 8);
    Particle_StepMagnitude_SetScaled_0AD8C(arg0, (ParticleMath_RandomRange(8) * 0.25f) + 2.0f);
    Particle_SetMotionStepFromRotationXY(arg0);
    Particle_AdvanceLifecycle(arg0);
}

/**
 * Particle callback: init, loops frames 1-7 until the spawn step is done, then fades; falls
 * with speed -1.5 by 0.1 while running.
 */
void func_82165224(Particle* arg0) {
    s16 temp_v0;

    temp_v0 = arg0->lifecycle;
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_82165100(arg0);
        break;
    case 2:
        Particle_AnimateFramesForwardLoopedThenAdvance(arg0, 1, 7, 1, 2, 0);
        if (func_82140690(arg0) != 0) {
            Particle_ApproachPrimAlpha(arg0, 0x64, 0x10);
        }
        break;
    case 3:
        Particle_MarkInactive(arg0);
        break;
    }
    if (Particle_IsRunning(arg0) != 0) {
        func_821402B8(arg0);
        func_8213F940(arg0, 0xBFC00000, 0x3DCCCCCD);
        Particle_ApplyMotionStep(arg0);
    }
}

/**
 * Lifecycle init for a burst emitter: one of several fixed positions by its A6 parameter,
 * with a 6-frame timer.
 * Not reached in play (2026-11-13): did not run in the 165-move battle sweep (each move used once,
 * from the command menu to the end of its turn) or in a tour of the menus and a COM battle.
 * @unverified Name from Stadium 1.
 */
void BattleAnim_CallbackDescriptor50BurstEmitter_InitParticle(Particle* arg0) {
    switch (arg0->param0) {
        case 0:
            Particle_SetPosition(arg0, 0.0f, -5.0f, -10.0f);
            break;

        case 1:
            Particle_SetPosition(arg0, 0.0f, 8.0f, 8.0f);
            break;

        case 2:
            Particle_SetPosition(arg0, 0.0f, 3.0f, 0.0f);
            break;

        case 3:
            Particle_SetPosition(arg0, 0.0f, -3.0f, 5.0f);
            break;
    }

    Particle_Param0_SetS16_0BCA8(arg0, 6);
    Particle_AdvanceLifecycle(arg0);
}

/**
 * Particle callback for a burst emitter: emits its burst children, then goes inactive.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal or j,
 * no pointer word, no lui/addiu pair in any fragment), so play cannot reach it.
 * @unverified Name from Stadium 1.
 */
void BattleAnim_CallbackDescriptor50BurstEmitter(Particle* arg0) {
    switch (arg0->lifecycle) {
        case 1:
            BattleAnim_CallbackDescriptor50BurstEmitter_InitParticle(arg0);
            break;

        case 2:
            BattleAnim_EmitParticleBurst(arg0, BattleAnim_CallbackDescriptor50BurstChild, &D_8218E580[0x50], 1);
            Particle_DecrementParam0ToZeroThenAdvance(arg0);
            break;

        case 3:
            Particle_MarkInactive(arg0);
            break;
    }
}

/**
 * Init hook for end effect 16: does nothing.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal or j,
 * no pointer word, no lui/addiu pair in any fragment), so play cannot reach it.
 * @unverified Name from Stadium 1.
 */
void BattleAnim_EndEffect16_NoOpInit(void) {
}

/**
 * Like func_82165224 with the shared vertical-fade init and a fall step of 0.2.
 */
void func_8216547C(Particle* arg0) {
    s16 temp_v0;

    temp_v0 = arg0->lifecycle;
    switch (temp_v0) {                              /* irregular */
    case 1:
        BattleAnim_InitSharedVerticalFadeParticle(arg0);
        break;
    case 2:
        Particle_AnimateFramesForwardLoopedThenAdvance(arg0, 1, 7, 1, 2, 0);
        if (func_82140690(arg0) != 0) {
            Particle_ApproachPrimAlpha(arg0, 0x64, 0x10);
        }
        break;
    case 3:
        Particle_MarkInactive(arg0);
        break;
    }
    if (Particle_IsRunning(arg0) != 0) {
        func_821402B8(arg0);
        func_8213F940(arg0, 0xBFC00000, 0x3E4CCCCD);
        Particle_ApplyMotionStep(arg0);
    }
}

/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Solar Beam.
 */
void BattleAnim_SetupSolarBeamUseEffect(Particle* arg0) {
    s16 sp26 = Particle_FieldCF_GetS16_0C058(arg0);

    Particle_SetScaleScaled(arg0, 0.2f);
    Particle_PositionOffset_AddYScaled_08E90(arg0, 5.0f);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, sp26);
    Particle_SetPrimAlpha(arg0, 0x40);
    Particle_AdvanceLifecycle(arg0);
}

/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Solar Beam.
 */
void BattleAnim_RunSolarBeamUseEffect(Particle* arg0) {
    switch (arg0->lifecycle) {
        case 1:
            BattleAnim_SetupSolarBeamUseEffect(arg0);
            break;

        case 2:
            Particle_ApproachScale(arg0, 8.0f, 0.1f);
            Particle_PrimAlpha_Approach_0BC2C(arg0, 0xFF, 4);
            break;

        case 3:
            Particle_DisableAndDetach(arg0);
            break;
    }
}

/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Solar Beam, Mimic, Metronome, Sky Attack, Conversion.
 */
void BattleAnim_SetupQiChargeChild(Particle* arg0) {
    s16 sp26 = Particle_SpawnIndex_GetS16_0C038(arg0);
    s16 sp24 = Particle_FieldCF_GetS16_0C058(arg0);

    Particle_StepMagnitude_SetScaled_0AD8C(arg0, 100.0f);
    Particle_MagnitudeStep_SetScaled_0ADA4(arg0, 3.0f);
    Particle_MotionTarget_SetYScaled_0A094(arg0, 2.0f);
    Particle_RotationStep_SetY_0A3D8(arg0, 0x400);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, sp24);
    Particle_SetScaleScaled(arg0, 0.5f - (sp26 * D_FLT_82197850));
    Particle_SetPrimAlpha(arg0, (0xFF - (sp26 * 0x10)) & 0xFF);
    Particle_Param0_SetS16_0BCA8(arg0, sp26 + 1);
    Particle_DisableRendering(arg0);
    Particle_AdvanceLifecycle(arg0);
}

/**
 * Moves: Conversion (use), Mimic (use), Recover (use), Sky Attack (use), Solar Beam (use)
 * TODO: Human contributor add screenshot
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Solar Beam, Mimic, Metronome, Sky Attack, Conversion.
 */
void BattleAnim_RunQiChargeChild(Particle* arg0) {
    switch (arg0->lifecycle) {
        case 1:
            BattleAnim_SetupQiChargeChild(arg0);
            break;

        case 2:
            if (Particle_DecrementParam0ToZeroThenAdvance(arg0) != 0) {
                Particle_EnableRendering(arg0);
                Particle_Param0_SetS16_0BCA8(arg0, 24);
            }
            break;

        case 3:
            if ((Particle_DecrementParam0ToZero(arg0) != 0) && (Particle_ApproachScale(arg0, 0.0f, 0.05f) != 0)) {
                Particle_AdvanceLifecycle(arg0);
            }
            break;

        case 4:
            Particle_DisableAndDetach(arg0);
            break;
    }

    if (Particle_IsRenderingEnabled(arg0) != 0) {
        Particle_StepMagnitude_ApproachUsingMagnitudeStep(arg0, 0.0f);
        Particle_Rotation_AddYFromRotationStep_0A4C8(arg0);
        func_8213E4B0(arg0);
        func_8213E334(arg0, 0.0f);
        Particle_EnvB_Approach_0BBC0(arg0, 0xFF, 4);
        Particle_EnvG_Approach_0BBF0(arg0, 0xFF, 4);
    }
}

/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Solar Beam, Mimic, Metronome, Sky Attack, Conversion.
 */
void BattleAnim_SetupQiCharge(Particle* arg0) {
    Particle_SpawnIndex_GetS16_0C038(arg0);
    Particle_Rotation_SetY_0A2B8(arg0, ParticleMath_RandomRange(0x10000));
    func_8213E11C(arg0, ParticleMath_RandomSignedOffsetBySign(0x28, 0x28));
    BattleAnim_EmitParticleBurst(arg0, BattleAnim_RunQiChargeChild, &D_8218E580[0x44], 5);
    Particle_AdvanceLifecycle(arg0);
}

/**
 * Seen in play (2026-11-13) in the 165-move sweep (each move used once by the 1P Pokémon): it ran
 * only for SolarBeam, Mimic, Sky Attack and Conversion.
 * @unverified Name was previously used only by callers of this address; the definition was still func_.
 */
void BattleAnim_SolarbeamMimicBurstEmitter(Particle* arg0) {
    switch (arg0->lifecycle) {
        case 1:
            func_82165854(arg0);
            break;

        case 2:
            Particle_DisableAndDetach(arg0);
            break;
    }
}

/**
 * Lifecycle init for a burst child: light cyan, scale growing with burst index, texture
 * frame 15.
 * Not reached in play (2026-11-13): did not run in the 165-move battle sweep (each move used once,
 * from the command menu to the end of its turn) or in a tour of the menus and a COM battle.
 * @unverified Name from Stadium 1.
 */
void BattleAnim_CallbackDescriptor26BurstChild_InitParticle(Particle* arg0) {
    s16 sp26 = Particle_SpawnIndex_GetS16_0C038(arg0);

    Particle_SetPrimColor(arg0, 0xDC, 0xFF, 0xFF);
    ParticleGfx_RecolorEnv(arg0, 0x33);
    arg0->scale = (sp26 * D_FLT_82197854) + 0.5f;
    Particle_StepMagnitude_SetScaled_0AD8C(arg0, 2.0f);
    Particle_SetPrimAlpha(arg0, (0xFF - (sp26 << 5)) & 0xFF);
    Particle_Param0_SetS16_0BCA8(arg0, sp26 + 1);
    Particle_SetTextureFrame(arg0, 0xF);
    Particle_DisableRendering(arg0);
    Particle_AdvanceLifecycle(arg0);
}
