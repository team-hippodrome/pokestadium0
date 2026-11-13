#include "pokemon.h"
/* Stadium Zero fragment012_17ED00. */
/* C ported from the Stadium 1 decomp: src/fragments/battle_engine/battle_engine_3274D0.c. */

#include "fragments/battle_engine/battle_engine.h"
#include "math_util.h"

#include "m2c_macros.h"

void BattleAnim_SetupStrongElectricSpark(Particle* arg0);
void BattleAnim_ApplyThunderThunderboltUseRadialOffset(Particle* arg0);
void BattleAnim_SetupThunderThunderboltUseEffect(Particle* arg0);
void BattleAnim_SetupSharedDescriptor0FDelayedRisingColumnFade(Particle* arg0);
void BattleAnim_SetupSharedDescriptor0FDelayedRisingColumnRandomScale(Particle* arg0);
void BattleAnim_SetupSharedDirectionalSprayFade(Particle* arg0);
void BattleAnim_SetupSharedDescriptor13DirectionalSprayScaledFade(Particle* arg0);
void BattleAnim_SetupThunderShockOuterJolts(Particle* arg0);
void BattleAnim_SetupUnregisteredStraightDirectionalStreamFade(Particle* arg0);
void BattleAnim_SetupEndEffect28Descriptor10UpwardBurstFade(Particle* arg0);
void BattleAnim_SetupEndEffect28Descriptor10WideScatterBurstFade(Particle* arg0);
void BattleAnim_InitializeThunderPunchUse(void);
void BattleAnim_InitializeHyperBeamHitSequence(void);

void BattleAnim_CallbackStartEffects18And73Descriptor11ScatterRiseFade(Particle* arg0);
void BattleAnim_RunDeterministicRotatingBoltOfLightning(Particle* arg0);
void BattleAnim_RunRandomRotatingBoltOfLightning(Particle* arg0);
void BattleAnim_CallbackSharedDirectionalSprayFade(Particle* arg0);
void BattleAnim_CallbackSharedDescriptor13DirectionalSprayScaledFade(Particle* arg0);

/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Thunder Punch, Thunderbolt, Thunder.
 */
void BattleAnim_SetupStrongElectricSpark(Particle* arg0) {
    UNUSED s32 pad; // FAKE: stack padding
    Vec3s sp2C;

    Particle_FieldAC_GetS16_0C038(arg0);
    Particle_SetScaleScaled(arg0, 0.05f);
    sp2C.x = ParticleMath_RandomRange(0x8000) - 0x4000;
    sp2C.y = ParticleMath_RandomRange(0x10000);
    sp2C.z = ParticleMath_RandomRange(0x800) - 0x400;
    Particle_Field94_AddVecFromVec3s_0A4F0(arg0, sp2C);
    Particle_AddPositionFromRotationTemplate1(arg0, ParticleMath_RandomRange(0xA));
    Particle_Field94_AddX_0A578(arg0, 0x4000);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, Particle_FieldCF_GetS16_0C058(arg0));
    Particle_AdvanceLifecycle(arg0);
}

void Particle_DisableAndDetach(s8 *arg0);                      /* extern */
M2C_UNK func_8213E5C8(s8 *);                      /* extern */
M2C_UNK func_82140228(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_82140548(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_821406B4(s8 *);                      /* extern */
M2C_UNK func_8214E590(s8 *);                      /* extern */

void func_8214E67C(s8 *arg0) {
    s16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_8214E590(arg0);
        break;
    case 2:
        func_821406B4(arg0);
        break;
    case 3:
        func_82140548(arg0, 0, 0x40);
        break;
    case 4:
        Particle_DisableAndDetach(arg0);
        break;
    }
    func_82140228(arg0, 0x3F800000, 0x3D4CCCCD);
    func_8213E5C8(arg0);
}

/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Thunderbolt, Thunder.
 */
void BattleAnim_ApplyThunderThunderboltUseRadialOffset(Particle* arg0) {
    f32 sp1C = 0.0f;

    switch (BattleAnim_GetOwnerSpecies(arg0->pokemon)) {
        case CHARIZARD:
            sp1C = 15.0f;
            break;

        case KANGASKHAN:
            sp1C = 15.0f;
            break;

        case JOLTEON:
            sp1C = 10.0f;
            break;

        case DRAGONITE:
            sp1C = 10.0f;
            break;

        case NIDOQUEEN:
            sp1C = 10.0f;
            break;

        case NIDOKING:
            sp1C = 10.0f;
            break;

        case CHANSEY:
            sp1C = 10.0f;
            break;
    }

    Particle_AddPositionOffsetAlongRotationYPlus180(arg0, sp1C);
    Particle_AddPositionOffsetAlongRotationYPlus90(arg0, 5.0f);
}

/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Thunderbolt, Thunder.
 */
void BattleAnim_SetupThunderThunderboltUseEffect(Particle* arg0) {
    Particle_SetScaleScaled(arg0, 0.1f);
    Particle_Field74_SetScaled_0AD8C(arg0, 0.0f);
    BattleAnim_ApplyThunderThunderboltUseRadialOffset(arg0);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, 0x17);
    Particle_AdvanceLifecycle(arg0);
}

/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Thunderbolt, Thunder.
 */
void BattleAnim_RunThunderThunderboltUseEffect(Particle* arg0) {
    switch (arg0->lifecycle) {
        case 1:
            BattleAnim_SetupThunderThunderboltUseEffect(arg0);
            break;

        case 2:
            Particle_ApproachScale(arg0, 4.0f, 0.5f);
            Particle_DecrementUnkA6ToZeroThenAdvance(arg0);
            break;

        case 3:
            Particle_ApproachScale(arg0, 0.1f, 0.5f);
            Particle_ApproachPrimAlphaThenAdvance(arg0, 0, 0x20);
            break;

        case 4:
            Particle_DisableAndDetach(arg0);
            break;
    }
}

void BattleAnim_SetupSharedDescriptor0FDelayedRisingColumnFade(Particle* arg0) {
    s16 sp2E = Particle_FieldAC_GetS16_0C038(arg0);
    Vec3s sp28;

    Particle_Field38_SetYScaled_08CA0(arg0, 15.0f);
    Particle_SetScaleScaled(arg0, 0.1f);
    Particle_Field74_SetScaled_0AD8C(arg0, 0.0f);
    sp28.x = 0x4000 - ParticleMath_RandomRange(0x8000);
    sp28.y = sp2E << 0xD;
    sp28.z = 0;
    Particle_Field94_AddVecFromVec3s_0A4F0(arg0, sp28);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, Particle_FieldCF_GetS16_0C058(arg0));
    Particle_DisableRendering(arg0);
    Particle_AdvanceLifecycle(arg0);
}

/**
 * Moves: Hyper Beam (hit), Thunder (use/hit), Thunder Shock (use/hit), Thunderbolt (use/hit)
 * TODO: Human contributor add screenshot
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Hyper Beam, Thunder Shock, Thunderbolt, Thunder.
 */
void BattleAnim_RunDeterministicRotatingBoltOfLightning(Particle* arg0) {
    switch (arg0->lifecycle) {
        case 1:
            BattleAnim_SetupSharedDescriptor0FDelayedRisingColumnFade(arg0);
            break;

        case 2:
            if (Particle_TickDelayAndAdvanceLifecycle(arg0, Particle_FieldAC_GetS16_0C038(arg0)) != 0) {
                Particle_EnableRendering(arg0);
            }
            break;

        case 3:
            Particle_ApproachScale(arg0, 3.0f, 0.1f);
            Particle_DecrementUnkA6ToZeroThenAdvance(arg0);
            break;

        case 4:
            Particle_ApproachPrimAlphaThenAdvance(arg0, 0, 0x40);
            break;

        case 5:
            Particle_DisableAndDetach(arg0);
            break;
    }

    Particle_Field94_AddY_0A594(arg0, 0x400);
    Particle_AddVelocityFromRotationTemplate1(arg0);
}

void BattleAnim_SetupSharedDescriptor0FDelayedRisingColumnRandomScale(Particle* arg0) {
    s16 sp2E = Particle_FieldAC_GetS16_0C038(arg0);
    Vec3s sp28;

    Particle_Field38_SetYScaled_08CA0(arg0, 15.0f);
    Particle_SetScaleScaled(arg0, 0.1f);
    Particle_Field74_SetScaled_0AD8C(arg0, MathUtil_Random_ZeroOne());
    sp28.x = 0x3000 - ParticleMath_RandomRange(0x6000);
    sp28.y = sp2E << 0xD;
    sp28.z = 0;
    Particle_Field94_AddVecFromVec3s_0A4F0(arg0, sp28);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, Particle_FieldCF_GetS16_0C058(arg0));
    Particle_DisableRendering(arg0);
    Particle_AdvanceLifecycle(arg0);
}

/**
 * Moves: Hyper Beam (hit), Thunder (use/hit), Thunder Shock (use/hit), Thunderbolt (use/hit)
 * TODO: Human contributor add screenshot
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Hyper Beam, Thunder Shock, Thunderbolt, Thunder.
 */
void BattleAnim_RunRandomRotatingBoltOfLightning(Particle* arg0) {
    switch (arg0->lifecycle) {
        case 1:
            BattleAnim_SetupSharedDescriptor0FDelayedRisingColumnRandomScale(arg0);
            break;

        case 2:
            if (Particle_TickDelayAndAdvanceLifecycle(arg0, Particle_FieldAC_GetS16_0C038(arg0)) != 0) {
                Particle_EnableRendering(arg0);
            }
            break;

        case 3:
            Particle_ApproachScale(arg0, 3.5f, 0.1f);
            Particle_DecrementUnkA6ToZeroThenAdvance(arg0);
            break;

        case 4:
            Particle_ApproachPrimAlphaThenAdvance(arg0, 0, 0x40);
            break;

        case 5:
            Particle_DisableAndDetach(arg0);
            break;
    }

    Particle_Field94_AddY_0A594(arg0, 0x400);
    Particle_AddVelocityFromRotationTemplate1(arg0);
}

void BattleAnim_SetupSharedDirectionalSprayFade(Particle* arg0) {
    Vec3s sp28;

    Particle_FieldAC_GetS16_0C038(arg0);
    Particle_SetScaleScaled(arg0, 0.5f);
    Particle_Field74_SetScaled_0AD8C(arg0, 0.0f);
    sp28.x = -0x4000;
    sp28.y = 0;
    sp28.z = (ParticleMath_RandomRange(0x10) << 0xB) - 0x4000;
    Particle_Field94_AddVecFromVec3s_0A4F0(arg0, sp28);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, Particle_FieldCF_GetS16_0C058(arg0));
    Particle_AdvanceLifecycle(arg0);
}

void Particle_DisableAndDetach(s8 *arg0);                      /* extern */
M2C_UNK func_8213E5C8(s8 *);                      /* extern */
M2C_UNK func_82140228(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_82140548(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_821406B4(s8 *);                      /* extern */
M2C_UNK func_8214EC88(s8 *);                      /* extern */

void func_8214ED30(s8 *arg0) {
    s16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_8214EC88(arg0);
        break;
    case 2:
        func_82140228(arg0, 0x40000000, 0x3E4CCCCD);
        func_821406B4(arg0);
        break;
    case 3:
        func_82140548(arg0, 0, 0x40);
        break;
    case 4:
        Particle_DisableAndDetach(arg0);
        break;
    }
    func_8213E5C8(arg0);
}

void BattleAnim_SetupSharedDescriptor13DirectionalSprayScaledFade(Particle* arg0) {
    UNUSED s32 pad; // FAKE: stack padding
    Vec3s sp2C;

    Particle_FieldAC_GetS16_0C038(arg0);
    Particle_SetScaleScaled(arg0, 0.5f);
    Particle_SetScaleTarget(arg0, (MathUtil_Random_ZeroOne() * 5.0f) + 1.0f);
    Particle_SetScaleStep(arg0, 0.2f);
    Particle_Field74_SetScaled_0AD8C(arg0, MathUtil_Random_ZeroOne() * 4.0f);
    sp2C.x = -0x4000;
    sp2C.y = 0;
    sp2C.z = (ParticleMath_RandomRange(0x10) << 0xB) - 0x4000;
    Particle_Field94_AddVecFromVec3s_0A4F0(arg0, sp2C);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, Particle_FieldCF_GetS16_0C058(arg0));
    Particle_AdvanceLifecycle(arg0);
}

void Particle_DisableAndDetach(s8 *arg0);                      /* extern */
M2C_UNK func_8213E5C8(s8 *);                      /* extern */
M2C_UNK func_821402B8(s8 *);                      /* extern */
M2C_UNK func_82140548(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_821406B4(s8 *);                      /* extern */
M2C_UNK func_8214EDE0(s8 *);                      /* extern */

void func_8214EEE0(s8 *arg0) {
    s16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_8214EDE0(arg0);
        break;
    case 2:
        func_821402B8(arg0);
        func_821406B4(arg0);
        break;
    case 3:
        func_82140548(arg0, 0, 0x40);
        break;
    case 4:
        Particle_DisableAndDetach(arg0);
        break;
    }
    func_8213E5C8(arg0);
}

/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Thunder Shock.
 */
void BattleAnim_SetupThunderShockOuterJolts(Particle* arg0) {
    UNUSED s32 pad; // FAKE: stack padding
    Vec3s sp2C;
    UNUSED s32 pad2[2]; // FAKE: stack padding

    Particle_FieldAC_GetS16_0C038(arg0);
    Particle_SetScaleScaled(arg0, 0.1f);
    Particle_SetScaleTarget(arg0, 1.4f);
    Particle_SetScaleStep(arg0, 0.1f);
    MathUtil_Random_ZeroOne();
    Particle_Field74_SetScaled_0AD8C(arg0, 0.0f);
    sp2C.x = -0x4000;
    sp2C.y = 0;
    sp2C.z = (ParticleMath_RandomRange(0x10) << 0xB) - 0x4000;
    Particle_Field94_AddVecFromVec3s_0A4F0(arg0, sp2C);
    Particle_AddPositionFromRotationTemplate1(arg0, 150.0f);
    Particle_Field94_AddZConstant_0A334(arg0);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, Particle_FieldCF_GetS16_0C058(arg0));
    Particle_AdvanceLifecycle(arg0);
}

void Particle_DisableAndDetach(s8 *arg0);                      /* extern */
M2C_UNK func_8213E5C8(s8 *);                      /* extern */
M2C_UNK func_821402B8(s8 *);                      /* extern */
M2C_UNK func_82140548(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_821406B4(s8 *);                      /* extern */
M2C_UNK func_8214EF84(s8 *);                      /* extern */

void func_8214F06C(s8 *arg0) {
    s16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_8214EF84(arg0);
        break;
    case 2:
        func_821406B4(arg0);
        break;
    case 3:
        func_82140548(arg0, 0, 0x10);
        break;
    case 4:
        Particle_DisableAndDetach(arg0);
        break;
    }
    func_821402B8(arg0);
    func_8213E5C8(arg0);
}

void BattleAnim_SetupUnregisteredStraightDirectionalStreamFade(Particle* arg0) {
    UNUSED s32 pad; // FAKE: stack padding
    Vec3s sp2C;
    UNUSED s32 pad2[2]; // FAKE: stack padding

    Particle_FieldAC_GetS16_0C038(arg0);
    Particle_SetScaleScaled(arg0, 0.1f);
    Particle_SetScaleTarget(arg0, 1.4f);
    Particle_SetScaleStep(arg0, 0.1f);
    MathUtil_Random_ZeroOne();
    Particle_Field74_SetScaled_0AD8C(arg0, 0.0f);
    sp2C.x = -0x4000;
    sp2C.y = 0;
    sp2C.z = 0;
    Particle_Field94_AddVecFromVec3s_0A4F0(arg0, sp2C);
    Particle_AddPositionFromRotationTemplate1(arg0, 150.0f);
    Particle_Field94_AddZConstant_0A334(arg0);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, Particle_FieldCF_GetS16_0C058(arg0));
    Particle_AdvanceLifecycle(arg0);
}

void Particle_DisableAndDetach(s8 *arg0);                      /* extern */
M2C_UNK func_8213E5C8(s8 *);                      /* extern */
M2C_UNK func_821402B8(s8 *);                      /* extern */
M2C_UNK func_82140548(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_821406B4(s8 *);                      /* extern */
M2C_UNK func_8214F110(s8 *);                      /* extern */

void func_8214F1E8(s8 *arg0) {
    s16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_8214F110(arg0);
        break;
    case 2:
        func_821406B4(arg0);
        break;
    case 3:
        func_82140548(arg0, 0, 0x10);
        break;
    case 4:
        Particle_DisableAndDetach(arg0);
        break;
    }
    func_821402B8(arg0);
    func_8213E5C8(arg0);
}

void BattleAnim_SetupEndEffect28Descriptor10UpwardBurstFade(Particle* arg0) {
    UNUSED s32 pad; // FAKE: stack padding
    Vec3f sp30;
    Vec3s sp28;

    Particle_FieldAC_GetS16_0C038(arg0);
    Particle_SetScaleScaled(arg0, 0.1f);
    Particle_SetScaleTarget(arg0, 2.0f);
    Particle_SetScaleStep(arg0, 0.1f);
    sp28.x = 0;
    sp28.y = 0;
    sp28.z = -0x8000;
    Particle_Field94_AddVecFromVec3s_0A4F0(arg0, sp28);
    sp30.x = ParticleMath_RandomRange(0x64) + -50.0f;
    sp30.y = 200.0f;
    sp30.z = ParticleMath_RandomRange(0x64) + -50.0f;
    Particle_Field38_AddVecScaledFromVec3f_08D78(arg0, sp30);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, Particle_FieldCF_GetS16_0C058(arg0));
    Particle_AdvanceLifecycle(arg0);
}

void Particle_DisableAndDetach(s8 *arg0);                      /* extern */
M2C_UNK func_8213E5C8(s8 *);                      /* extern */
M2C_UNK func_821402B8(s8 *);                      /* extern */
M2C_UNK func_82140548(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_821406B4(s8 *);                      /* extern */
M2C_UNK func_8214F28C(s8 *);                      /* extern */

void func_8214F3D4(s8 *arg0) {
    s16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_8214F28C(arg0);
        break;
    case 2:
        func_821406B4(arg0);
        break;
    case 3:
        func_82140548(arg0, 0, 0x40);
        break;
    case 4:
        Particle_DisableAndDetach(arg0);
        break;
    }
    func_821402B8(arg0);
    func_8213E5C8(arg0);
}

void BattleAnim_SetupEndEffect28Descriptor10WideScatterBurstFade(Particle* arg0) {
    UNUSED s32 pad[4]; // FAKE: stack padding
    Vec3s sp28;

    Particle_FieldAC_GetS16_0C038(arg0);
    Particle_SetScaleScaled(arg0, 0.1f);
    Particle_SetScaleTarget(arg0, 2.0f);
    Particle_SetScaleStep(arg0, 0.1f);
    sp28.x = -0x1000 - ParticleMath_RandomRange(0x6000);
    sp28.y = ParticleMath_RandomRange(0x10000);
    sp28.z = ParticleMath_RandomRange(0x800) - 0x400;
    Particle_Field94_AddVecFromVec3s_0A4F0(arg0, sp28);
    Particle_AddPositionFromRotationTemplate1(arg0, 200.0f);
    Particle_Field94_AddX_0A578(arg0, -0x4000);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, Particle_FieldCF_GetS16_0C058(arg0));
    Particle_AdvanceLifecycle(arg0);
}

void Particle_DisableAndDetach(s8 *arg0);                      /* extern */
M2C_UNK func_8213E5C8(s8 *);                      /* extern */
M2C_UNK func_821402B8(s8 *);                      /* extern */
M2C_UNK func_82140548(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_821406B4(s8 *);                      /* extern */
M2C_UNK func_8214F478(s8 *);                      /* extern */

void func_8214F55C(s8 *arg0) {
    s16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_8214F478(arg0);
        break;
    case 2:
        func_821406B4(arg0);
        break;
    case 3:
        func_82140548(arg0, 0, 0x40);
        break;
    case 4:
        Particle_DisableAndDetach(arg0);
        break;
    }
    func_821402B8(arg0);
    func_8213E5C8(arg0);
}

/**
 * initializes using thunderbolt or thunder
 * Effect start init 18 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used:
 * it ran for exactly Thunder, Thunderbolt.
 */
void BattleAnim_InitializeThunderThunderboltUse(void) {
    BattleAnim_SpawnCategory17MarkerSlot(0x64, 1);
    BattleAnim_SpawnGlobalTintColorFadeDetach(0, 0x20, 3);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0, 3, 8, BattleAnim_CallbackStartEffects18And73Descriptor11ScatterRiseFade, &gBattleAnimParticleDescriptors[0x11], 8, 4, 2, 0, 0x25, 0);
    BattleAnim_AddSpawnDelay(0x19);
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_RunThunderThunderboltUseEffect, &gBattleAnimParticleDescriptors[0x15], 0xE, 1, 2, 0, 0x25, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_RunThunderThunderboltUseEffect, &gBattleAnimParticleDescriptors[0x16], 0xE, 1, 2, 0, 0x25, 0);
    BattleAnim_SpawnDescriptor25AlphaHoldFadeOut(8, 2, 8, 0x8, 0xFF);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(8, 4, 2, BattleAnim_RunDeterministicRotatingBoltOfLightning, &gBattleAnimParticleDescriptors[0xF], 0x14, 4, 7, 0, 0x25, 0);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(8, 4, 2, BattleAnim_RunRandomRotatingBoltOfLightning, &gBattleAnimParticleDescriptors[0xF], 0x14, 4, 7, 0, 0x25, 0);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(8, 4, 2, BattleAnim_CallbackSharedDescriptor13DirectionalSprayScaledFade, &gBattleAnimParticleDescriptors[0x13], 0x14, 4, 7, 0, 0x25, 0);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(8, 4, 2, BattleAnim_CallbackSharedDirectionalSprayFade, &gBattleAnimParticleDescriptors[0x13], 0x14, 4, 7, 0, 0x25, 0);
}

M2C_UNK func_8213B5D8(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK *, M2C_UNK *, s32, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_8213B644(M2C_UNK, M2C_UNK, M2C_UNK);   /* extern */
M2C_UNK func_8213B794(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, s32); /* extern */
extern M2C_UNK D_8218E600;
extern M2C_UNK D_8218E618;
extern M2C_UNK func_8214E9F0;
extern M2C_UNK func_8214EBA4;

/**
 * initializes being hit by thunder shock or thunderbolt
 * Effect end init 8 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used: it
 * ran for exactly Thunder Shock, Thunderbolt.
 */
void BattleAnim_InitializeThunderShockThunderboltHit(void) {
    func_8213B794(0x2C, 4, 0x10, 8, 0xFF);
    func_8213B644(0x30, 0x20, 8);
    func_8213B5D8(0, 8, 5, &func_8214ED30, &D_8218E618, 8, 3, 3, 0, 0x25, 0);
    func_8213B5D8(0, 4, 2, &func_8214E9F0, &D_8218E600, 0x14, 4, 3, 0, 0x25, 0);
    func_8213B5D8(0, 4, 2, &func_8214EBA4, &D_8218E600, 0x14, 4, 3, 0, 0x25, 0);
}

M2C_UNK func_8213B5D8(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK *, M2C_UNK *, s32, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_8213B644(M2C_UNK, M2C_UNK, M2C_UNK);   /* extern */
M2C_UNK func_8213B794(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, s32); /* extern */
M2C_UNK func_8215EC44();                            /* extern */
extern M2C_UNK D_8218E600;
extern M2C_UNK D_8218E618;
extern M2C_UNK func_8214E9F0;
extern M2C_UNK func_8214EBA4;

/**
 * initializes getting hit by thunder
 * Effect end init 72 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used: it
 * ran for exactly Thunder.
 */
void BattleAnim_InitializeThunderHit(void) {
    func_8213B794(0, 4, 8, 8, 0xC8);
    func_8213B644(0x30, 0x20, 8);
    func_8213B5D8(0, 8, 5, &func_8214ED30, &D_8218E618, 8, 3, 3, 0, 0x25, 0);
    func_8213B5D8(0, 4, 2, &func_8214E9F0, &D_8218E600, 0x14, 4, 3, 0, 0x25, 0);
    func_8213B5D8(0, 4, 2, &func_8214EBA4, &D_8218E600, 0x14, 4, 3, 0, 0x25, 0);
    func_8215EC44();
}

/**
 * initializes using thunder shock
 * Effect start init 59 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used:
 * it ran for exactly Thunder Shock.
 */
void BattleAnim_InitializeThunderShockUse(void) {
    BattleAnim_SpawnCategory17MarkerSlot(0x64, 1);
    BattleAnim_SpawnGlobalTintColorFadeDetach(0, 0x10, 3);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0, 8, 3, BattleAnim_CallbackStartEffect59EndEffect28DirectionalStreamFade, &gBattleAnimParticleDescriptors[0x14], 2, 1, 2, 0, 0x25, 0);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0, 5, 5, BattleAnim_CallbackStartEffect59EndEffect28DirectionalStreamFade, &gBattleAnimParticleDescriptors[0x13], 2, 1, 2, 0, 0x25, 0);
    BattleAnim_AddSpawnDelay(0x23);
    BattleAnim_SpawnDescriptor25AlphaHoldFadeOutFullAlpha(8, 4, 8, 0x8);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0, 4, 2, BattleAnim_CallbackSharedDescriptor13DirectionalSprayScaledFade, &gBattleAnimParticleDescriptors[0x13], 0x14, 4, 2, 0, 0x25, 0);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0, 5, 2, BattleAnim_CallbackSharedDirectionalSprayFade, &gBattleAnimParticleDescriptors[0x13], 0x14, 4, 2, 0, 0x25, 0);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0, 6, 2, BattleAnim_RunDeterministicRotatingBoltOfLightning, &gBattleAnimParticleDescriptors[0xF], 0x14, 2, 1, 0, 0x25, 0);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0, 4, 2, BattleAnim_RunRandomRotatingBoltOfLightning, &gBattleAnimParticleDescriptors[0xF], 0x14, 2, 1, 0, 0x25, 0);
}

M2C_UNK func_8213B5D8(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK *, M2C_UNK *, s32, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_8213B644(M2C_UNK, M2C_UNK, M2C_UNK);   /* extern */
M2C_UNK func_8213B720(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK); /* extern */
extern M2C_UNK D_8218E608;
extern M2C_UNK D_8218E620;

void func_8214FCBC(void) {
    func_8213B720(0x22, 4, 0x10, 8);
    func_8213B644(0, 0x20, 3);
    func_8213B644(0x30, 0x20, 8);
    func_8213B5D8(0, 0xA, 2, &func_8214F3D4, &D_8218E608, 0xC, 1, 3, 0, 0x25, 0);
    func_8213B5D8(0, 5, 3, &func_8214F55C, &D_8218E608, 0xC, 2, 3, 0, 0x25, 0);
    func_8213B5D8(0, 8, 2, &func_8214F06C, &D_8218E620, 0xC, 3, 3, 0, 0x25, 0);
}

/**
 * initializes using thunder punch
 * Effect start init 73 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used:
 * it ran for exactly Thunder Punch.
 */
void BattleAnim_InitializeThunderPunchUse(void) {
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0, 4, 5, BattleAnim_CallbackStartEffects18And73Descriptor11ScatterRiseFade, &gBattleAnimParticleDescriptors[0x11], 8, 4, 0x10, gBattleAnimCurrentAnchor, 0x25, 0);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0, 1, 0x24, BattleAnim_CallbackStartEffect73Descriptor15AnimatedColorImpulseFade, &gBattleAnimParticleDescriptors[0x15], 0, 1, 0x11, gBattleAnimCurrentAnchor, 0, 0);
}

/**
 * initializes getting hit by hyper beam
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Hyper Beam.
 */
void BattleAnim_InitializeHyperBeamHitSequence(void) {
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(8, 4, 2, BattleAnim_CallbackSharedDescriptor13DirectionalSprayScaledFade, &gBattleAnimParticleDescriptors[0x13], 0x14, 4, 7, 0, 0x2C, 0);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(8, 4, 2, BattleAnim_CallbackSharedDirectionalSprayFade, &gBattleAnimParticleDescriptors[0x13], 0x14, 3, 7, 0, 0xF, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(8, BattleAnim_RunDeterministicRotatingBoltOfLightning, &gBattleAnimParticleDescriptors[0xF], 0x14, 1, 7, 0, 0x2C, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(8, BattleAnim_RunRandomRotatingBoltOfLightning, &gBattleAnimParticleDescriptors[0xF], 0x14, 1, 7, 0, 0xF, 0);
}
