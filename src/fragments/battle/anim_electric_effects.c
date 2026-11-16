#include "pokemon.h"
/* Stadium Zero fragment012_17ED00. */
/* C ported from the Stadium 1 decomp: src/fragments/battle_engine/battle_engine_3274D0.c. */

#include "battle.h"
#include "matrix.h"

#include "m2c_macros.h"

void BattleAnim_SetupStrongElectricSpark(Particle* arg0);
void BattleAnim_ApplyThunderThunderboltUseRadialOffset(Particle* arg0);
void BattleAnim_SetupThunderThunderboltUseEffect(Particle* arg0);
void BattleAnim_SetupDelayedRisingColumnFade(Particle* arg0);
void BattleAnim_SetupDelayedRisingColumnRandomScale(Particle* arg0);
void BattleAnim_SetupSharedDirectionalSprayFade(Particle* arg0);
void BattleAnim_SetupDirectionalSprayScaledFade(Particle* arg0);
void BattleAnim_SetupThunderShockOuterJolts(Particle* arg0);
void BattleAnim_SetupUnregisteredStraightDirStreamFade(Particle* arg0);
void BattleAnim_SetupEnd28Desc10UpwardBurstFade(Particle* arg0);
void BattleAnim_SetupEnd28Desc10WideScatterBurstFade(Particle* arg0);
void BattleAnim_InitializeThunderPunchUse(void);
void BattleAnim_InitializeHyperBeamHitSequence(void);

void BattleAnim_CallbackStart18And73Desc11ScatterRise(Particle* arg0);
void BattleAnim_RunDeterministicRotatingBoltOfLightning(Particle* arg0);
void BattleAnim_RunRandomRotatingBoltOfLightning(Particle* arg0);
void BattleAnim_CallbackSharedDirectionalSprayFade(Particle* arg0);
void BattleAnim_CallbackSharedDesc13DirSprayScaledFade(Particle* arg0);

/**
 * Inits a strong electric spark: scale 0.05, a random rotationX, rotationY and rotationZ, pushed
 * out up to 9 units along it, then rotated a quarter turn about X, recolored from its palette pair.
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Thunder Punch, Thunderbolt, Thunder.
 */
void BattleAnim_SetupStrongElectricSpark(Particle* arg0) {
    UNUSED s32 pad; // FAKE: stack padding
    Vec3s sp2C;

    Particle_SpawnIndex_GetS16_0C038(arg0);
    Particle_SetScaleScaled(arg0, 0.05f);
    sp2C.x = ParticleMath_RandomRange(0x8000) - 0x4000;
    sp2C.y = ParticleMath_RandomRange(0x10000);
    sp2C.z = ParticleMath_RandomRange(0x800) - 0x400;
    Particle_Rotation_AddVecFromVec3s_0A4F0(arg0, sp2C);
    Particle_AddPositionFromRotationTemplate1(arg0, ParticleMath_RandomRange(10));
    Particle_Rotation_AddX_0A578(arg0, 0x4000);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, Particle_GetByteParam1(arg0));
    Particle_AdvanceLifecycle(arg0);
}

void Particle_DisableAndDetach(Particle* arg0);                      /* extern */
M2C_UNK func_82140228(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_82140548(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_821406B4(s8 *);                      /* extern */
M2C_UNK func_8214E590(s8 *);                      /* extern */

/**
 * Particle lifecycle callback (start effects18 and73 descriptor11 scatter rise fade): steps the
 * particle by its lifecycle state.
 * Seen in play (2026-11-14) (Metronome bench, one movie per move, 1P Onix vs Pinsir on Splash, exec
 * breakpoint): ran only for Thunder, Thunderbolt, Thunder Punch.
 * @unverified Name guessed from the code.
 */
void BattleAnim_CallbackStart18And73Desc11ScatterRise(Particle* particle) {
    s16 temp_v0;

    temp_v0 = particle->lifecycle;
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_8214E590(particle);
        break;
    case 2:
        func_821406B4(particle);
        break;
    case 3:
        func_82140548(particle, 0, 0x40);
        break;
    case 4:
        Particle_DisableAndDetach(particle);
        break;
    }
    func_82140228(particle, 0x3F800000, 0x3D4CCCCD); // 1.0f, 0.05f
    Particle_MoveAlongRotationXYZAlt(particle);
}

/**
 * Raises the particle by a species-dependent height so the bolt reaches tall Pokémon (15 for
 * Charizard and Kangaskhan, 10 for several others, 0 by default).
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
 * Inits the Thunder or Thunderbolt use flash: scale 0.1, no speed, raised for the owner's species,
 * palette pair 0x17.
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Thunderbolt, Thunder.
 */
void BattleAnim_SetupThunderThunderboltUseEffect(Particle* arg0) {
    Particle_SetScaleScaled(arg0, 0.1f);
    Particle_StepMagnitude_SetScaled_0AD8C(arg0, 0.0f);
    BattleAnim_ApplyThunderThunderboltUseRadialOffset(arg0);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, 0x17);
    Particle_AdvanceLifecycle(arg0);
}

/**
 * Particle callback for the Thunder or Thunderbolt use flash: grows toward scale 4 until its timer
 * ends, then shrinks while fading out, then detaches.
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
            Particle_DecrementParam0ToZeroThenAdvance(arg0);
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

/**
 * Inits a lightning bolt of the rotating ring: 15 units up, scale 0.1, a random rotationX,
 * rotationY an eighth of a turn per spawn index, recolored from its palette pair, hidden at first.
 * Seen in play (2026-11-13) in the 165-move sweep (each move used once by the 1P Pokémon): it ran
 * only for Hyper Beam, ThunderShock, Thunderbolt and Thunder.
 */
void BattleAnim_SetupDelayedRisingColumnFade(Particle* arg0) {
    s16 sp2E = Particle_SpawnIndex_GetS16_0C038(arg0);
    Vec3s sp28;

    Particle_PositionOffset_SetYScaled_08CA0(arg0, 15.0f);
    Particle_SetScaleScaled(arg0, 0.1f);
    Particle_StepMagnitude_SetScaled_0AD8C(arg0, 0.0f);
    sp28.x = 0x4000 - ParticleMath_RandomRange(0x8000);
    sp28.y = sp2E << 0xD;
    sp28.z = 0;
    Particle_Rotation_AddVecFromVec3s_0A4F0(arg0, sp28);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, Particle_GetByteParam1(arg0));
    Particle_DisableRendering(arg0);
    Particle_AdvanceLifecycle(arg0);
}

/**
 * Particle callback for a bolt of the rotating ring: waits as many frames as its spawn index,
 * shows it, grows toward scale 3 until its timer ends, fades out, then detaches. Every frame it
 * turns and moves along its rotation.
 * Moves: Hyper Beam (hit), Thunder (use/hit), Thunder Shock (use/hit), Thunderbolt (use/hit)
 * TODO: Human contributor add screenshot
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Hyper Beam, Thunder Shock, Thunderbolt, Thunder.
 */
void BattleAnim_RunDeterministicRotatingBoltOfLightning(Particle* arg0) {
    switch (arg0->lifecycle) {
        case 1:
            BattleAnim_SetupDelayedRisingColumnFade(arg0);
            break;

        case 2:
            if (Particle_TickDelayAndAdvanceLifecycle(arg0, Particle_SpawnIndex_GetS16_0C038(arg0)) != 0) {
                Particle_EnableRendering(arg0);
            }
            break;

        case 3:
            Particle_ApproachScale(arg0, 3.0f, 0.1f);
            Particle_DecrementParam0ToZeroThenAdvance(arg0);
            break;

        case 4:
            Particle_ApproachPrimAlphaThenAdvance(arg0, 0, 0x40);
            break;

        case 5:
            Particle_DisableAndDetach(arg0);
            break;
    }

    Particle_Rotation_AddY_0A594(arg0, 0x400);
    Particle_AddVelocityFromRotationTemplate1(arg0);
}

/**
 * Inits a bolt of the random rotating ring: like the fixed ring but with a narrower random
 * rotationX and a random speed below 1.
 * Seen in play (2026-11-13) in the 165-move sweep (each move used once by the 1P Pokémon): it ran
 * only for Hyper Beam, ThunderShock, Thunderbolt and Thunder.
 */
void BattleAnim_SetupDelayedRisingColumnRandomScale(Particle* arg0) {
    s16 sp2E = Particle_SpawnIndex_GetS16_0C038(arg0);
    Vec3s sp28;

    Particle_PositionOffset_SetYScaled_08CA0(arg0, 15.0f);
    Particle_SetScaleScaled(arg0, 0.1f);
    Particle_StepMagnitude_SetScaled_0AD8C(arg0, MathUtil_Random_ZeroOne());
    sp28.x = 0x3000 - ParticleMath_RandomRange(0x6000);
    sp28.y = sp2E << 0xD;
    sp28.z = 0;
    Particle_Rotation_AddVecFromVec3s_0A4F0(arg0, sp28);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, Particle_GetByteParam1(arg0));
    Particle_DisableRendering(arg0);
    Particle_AdvanceLifecycle(arg0);
}

/**
 * Particle callback for a bolt of the random rotating ring: like the fixed ring but grows toward
 * scale 3.5.
 * Moves: Hyper Beam (hit), Thunder (use/hit), Thunder Shock (use/hit), Thunderbolt (use/hit)
 * TODO: Human contributor add screenshot
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Hyper Beam, Thunder Shock, Thunderbolt, Thunder.
 */
void BattleAnim_RunRandomRotatingBoltOfLightning(Particle* arg0) {
    switch (arg0->lifecycle) {
        case 1:
            BattleAnim_SetupDelayedRisingColumnRandomScale(arg0);
            break;

        case 2:
            if (Particle_TickDelayAndAdvanceLifecycle(arg0, Particle_SpawnIndex_GetS16_0C038(arg0)) != 0) {
                Particle_EnableRendering(arg0);
            }
            break;

        case 3:
            Particle_ApproachScale(arg0, 3.5f, 0.1f);
            Particle_DecrementParam0ToZeroThenAdvance(arg0);
            break;

        case 4:
            Particle_ApproachPrimAlphaThenAdvance(arg0, 0, 0x40);
            break;

        case 5:
            Particle_DisableAndDetach(arg0);
            break;
    }

    Particle_Rotation_AddY_0A594(arg0, 0x400);
    Particle_AddVelocityFromRotationTemplate1(arg0);
}

/**
 * Lifecycle init: half scale, no speed, pointed up with a random spread about Z, palette
 * color from the CF parameter.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (4 of the moves).
 * Seen in play (2026-11-14) (Metronome bench, one movie per move, 1P Onix vs Pinsir on Splash, exec
 * breakpoint): ran only for Hyper Beam, Thunder, Thunderbolt, Thundershock.
 * @unverified Name from Stadium 1.
 */
void BattleAnim_SetupSharedDirectionalSprayFade(Particle* arg0) {
    Vec3s sp28;

    Particle_SpawnIndex_GetS16_0C038(arg0);
    Particle_SetScaleScaled(arg0, 0.5f);
    Particle_StepMagnitude_SetScaled_0AD8C(arg0, 0.0f);
    sp28.x = -0x4000;
    sp28.y = 0;
    sp28.z = (ParticleMath_RandomRange(0x10) << 0xB) - 0x4000;
    Particle_Rotation_AddVecFromVec3s_0A4F0(arg0, sp28);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, Particle_GetByteParam1(arg0));
    Particle_AdvanceLifecycle(arg0);
}

void Particle_DisableAndDetach(Particle* arg0);                      /* extern */
M2C_UNK func_82140228(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_82140548(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_821406B4(s8 *);                      /* extern */
M2C_UNK func_8214EC88(s8 *);                      /* extern */

/**
 * Particle lifecycle callback (shared directional spray fade): steps the particle by its lifecycle
 * state.
 * Seen in play (2026-11-14) (Metronome bench, one movie per move, 1P Onix vs Pinsir on Splash, exec
 * breakpoint): ran only for Hyper Beam, Thunder, Thunderbolt, Thundershock.
 * @unverified Name guessed from the code.
 */
void BattleAnim_CallbackSharedDirectionalSprayFade(Particle* particle) {
    s16 temp_v0;

    temp_v0 = particle->lifecycle;
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_8214EC88(particle);
        break;
    case 2:
        func_82140228(particle, 0x40000000, 0x3E4CCCCD); // 2.0f, 0.2f
        func_821406B4(particle);
        break;
    case 3:
        func_82140548(particle, 0, 0x40);
        break;
    case 4:
        Particle_DisableAndDetach(particle);
        break;
    }
    Particle_MoveAlongRotationXYZAlt(particle);
}

/**
 * Inits a directional spray particle: grows from 0.5 toward a random 1 to 6, a random speed below
 * 4, pointed straight up with a random rotationZ in sixteenths of half a turn, recolored from its
 * palette pair.
 * Seen in play (2026-11-13) in the 165-move sweep (each move used once by the 1P Pokémon): it ran
 * only for Hyper Beam, ThunderShock, Thunderbolt and Thunder.
 */
void BattleAnim_SetupDirectionalSprayScaledFade(Particle* arg0) {
    UNUSED s32 pad; // FAKE: stack padding
    Vec3s sp2C;

    Particle_SpawnIndex_GetS16_0C038(arg0);
    Particle_SetScaleScaled(arg0, 0.5f);
    Particle_SetScaleTarget(arg0, (MathUtil_Random_ZeroOne() * 5.0f) + 1.0f);
    Particle_SetScaleStep(arg0, 0.2f);
    Particle_StepMagnitude_SetScaled_0AD8C(arg0, MathUtil_Random_ZeroOne() * 4.0f);
    sp2C.x = -0x4000;
    sp2C.y = 0;
    sp2C.z = (ParticleMath_RandomRange(0x10) << 0xB) - 0x4000;
    Particle_Rotation_AddVecFromVec3s_0A4F0(arg0, sp2C);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, Particle_GetByteParam1(arg0));
    Particle_AdvanceLifecycle(arg0);
}

void Particle_DisableAndDetach(Particle* arg0);                      /* extern */
M2C_UNK func_821402B8(s8 *);                      /* extern */
M2C_UNK func_82140548(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_821406B4(s8 *);                      /* extern */
M2C_UNK func_8214EDE0(s8 *);                      /* extern */

/**
 * Particle lifecycle callback (shared descriptor13 directional spray scaled fade): steps the
 * particle by its lifecycle state.
 * Seen in play (2026-11-14) (Metronome bench, one movie per move, 1P Onix vs Pinsir on Splash, exec
 * breakpoint): ran only for Hyper Beam, Thunder, Thunderbolt, Thundershock.
 * @unverified Name guessed from the code.
 */
void BattleAnim_CallbackSharedDesc13DirSprayScaledFade(Particle* particle) {
    s16 temp_v0;

    temp_v0 = particle->lifecycle;
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_8214EDE0(particle);
        break;
    case 2:
        func_821402B8(particle);
        func_821406B4(particle);
        break;
    case 3:
        func_82140548(particle, 0, 0x40);
        break;
    case 4:
        Particle_DisableAndDetach(particle);
        break;
    }
    Particle_MoveAlongRotationXYZAlt(particle);
}

/**
 * Inits a Thunder Shock outer jolt: grows from 0.1 to 1.4, no speed, pointed up with a random
 * rotationZ and pushed 150 units out along it, then given a constant Z spin, recolored from its
 * palette pair.
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Thunder Shock.
 */
void BattleAnim_SetupThunderShockOuterJolts(Particle* arg0) {
    UNUSED s32 pad; // FAKE: stack padding
    Vec3s sp2C;
    UNUSED s32 pad2[2]; // FAKE: stack padding

    Particle_SpawnIndex_GetS16_0C038(arg0);
    Particle_SetScaleScaled(arg0, 0.1f);
    Particle_SetScaleTarget(arg0, 1.4f);
    Particle_SetScaleStep(arg0, 0.1f);
    MathUtil_Random_ZeroOne();
    Particle_StepMagnitude_SetScaled_0AD8C(arg0, 0.0f);
    sp2C.x = -0x4000;
    sp2C.y = 0;
    sp2C.z = (ParticleMath_RandomRange(0x10) << 0xB) - 0x4000;
    Particle_Rotation_AddVecFromVec3s_0A4F0(arg0, sp2C);
    Particle_AddPositionFromRotationTemplate1(arg0, 150.0f);
    Particle_Rotation_AddZConstant_0A334(arg0);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, Particle_GetByteParam1(arg0));
    Particle_AdvanceLifecycle(arg0);
}

void Particle_DisableAndDetach(Particle* arg0);                      /* extern */
M2C_UNK func_821402B8(s8 *);                      /* extern */
M2C_UNK func_82140548(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_821406B4(s8 *);                      /* extern */
M2C_UNK func_8214EF84(s8 *);                      /* extern */

/**
 * Particle lifecycle callback (start effect59 end effect28 directional stream fade): steps the
 * particle by its lifecycle state.
 * Seen in play (2026-11-14) (Metronome bench, one movie per move, 1P Onix vs Pinsir on Splash, exec
 * breakpoint): ran only for Thundershock.
 * @unverified Name guessed from the code.
 */
void BattleAnim_CallbackStart59End28DirStreamFade(Particle* particle) {
    s16 temp_v0;

    temp_v0 = particle->lifecycle;
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_8214EF84(particle);
        break;
    case 2:
        func_821406B4(particle);
        break;
    case 3:
        func_82140548(particle, 0, 0x10);
        break;
    case 4:
        Particle_DisableAndDetach(particle);
        break;
    }
    func_821402B8(particle);
    Particle_MoveAlongRotationXYZAlt(particle);
}

/**
 * Lifecycle init: tiny and growing, pointed straight along the stream direction, palette
 * color from the CF parameter.
 * Not reached in play (2026-11-13): did not run in the 165-move battle sweep (each move used once,
 * from the command menu to the end of its turn) or in a tour of the menus and a COM battle.
 * @unverified Name from Stadium 1.
 */
void BattleAnim_SetupUnregisteredStraightDirStreamFade(Particle* arg0) {
    UNUSED s32 pad; // FAKE: stack padding
    Vec3s sp2C;
    UNUSED s32 pad2[2]; // FAKE: stack padding

    Particle_SpawnIndex_GetS16_0C038(arg0);
    Particle_SetScaleScaled(arg0, 0.1f);
    Particle_SetScaleTarget(arg0, 1.4f);
    Particle_SetScaleStep(arg0, 0.1f);
    MathUtil_Random_ZeroOne();
    Particle_StepMagnitude_SetScaled_0AD8C(arg0, 0.0f);
    sp2C.x = -0x4000;
    sp2C.y = 0;
    sp2C.z = 0;
    Particle_Rotation_AddVecFromVec3s_0A4F0(arg0, sp2C);
    Particle_AddPositionFromRotationTemplate1(arg0, 150.0f);
    Particle_Rotation_AddZConstant_0A334(arg0);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, Particle_GetByteParam1(arg0));
    Particle_AdvanceLifecycle(arg0);
}

void Particle_DisableAndDetach(Particle* arg0);                      /* extern */
M2C_UNK func_821402B8(s8 *);                      /* extern */
M2C_UNK func_82140548(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_821406B4(s8 *);                      /* extern */
M2C_UNK func_8214F110(s8 *);                      /* extern */

/**
 * Particle callback (no reference found) for
 * BattleAnim_SetupUnregisteredStraightDirStreamFade: steps, fades out by 16, then detaches.
 * @unverified Name guessed from the code.
 */
void BattleAnim_CallbackUnregisteredStraightStreamFade(Particle* particle) {
    s16 temp_v0;

    temp_v0 = particle->lifecycle;
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_8214F110(particle);
        break;
    case 2:
        func_821406B4(particle);
        break;
    case 3:
        func_82140548(particle, 0, 0x10);
        break;
    case 4:
        Particle_DisableAndDetach(particle);
        break;
    }
    func_821402B8(particle);
    Particle_MoveAlongRotationXYZAlt(particle);
}

/**
 * Lifecycle init for end effect 28: tiny and growing, offset and pointed upward, palette
 * color from the CF parameter.
 * Not reached in play (2026-11-13): did not run in the 165-move battle sweep (each move used once,
 * from the command menu to the end of its turn) or in a tour of the menus and a COM battle.
 * @unverified Name from Stadium 1.
 */
void BattleAnim_SetupEnd28Desc10UpwardBurstFade(Particle* arg0) {
    UNUSED s32 pad; // FAKE: stack padding
    Vec3f sp30;
    Vec3s sp28;

    Particle_SpawnIndex_GetS16_0C038(arg0);
    Particle_SetScaleScaled(arg0, 0.1f);
    Particle_SetScaleTarget(arg0, 2.0f);
    Particle_SetScaleStep(arg0, 0.1f);
    sp28.x = 0;
    sp28.y = 0;
    sp28.z = -0x8000;
    Particle_Rotation_AddVecFromVec3s_0A4F0(arg0, sp28);
    sp30.x = ParticleMath_RandomRange(100) + -50.0f;
    sp30.y = 200.0f;
    sp30.z = ParticleMath_RandomRange(100) + -50.0f;
    Particle_PositionOffset_AddVecScaled(arg0, sp30);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, Particle_GetByteParam1(arg0));
    Particle_AdvanceLifecycle(arg0);
}

void Particle_DisableAndDetach(Particle* arg0);                      /* extern */
M2C_UNK func_821402B8(s8 *);                      /* extern */
M2C_UNK func_82140548(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_821406B4(s8 *);                      /* extern */
M2C_UNK func_8214F28C(s8 *);                      /* extern */

/**
 * Particle callback for end effect 28: init, step, fade out by 64, detach.
 * @unverified Name guessed from the code.
 */
void BattleAnim_CallbackEndEffect28StreamA(Particle* particle) {
    s16 temp_v0;

    temp_v0 = particle->lifecycle;
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_8214F28C(particle);
        break;
    case 2:
        func_821406B4(particle);
        break;
    case 3:
        func_82140548(particle, 0, 0x40);
        break;
    case 4:
        Particle_DisableAndDetach(particle);
        break;
    }
    func_821402B8(particle);
    Particle_MoveAlongRotationXYZAlt(particle);
}

/**
 * Lifecycle init for end effect 28: tiny and growing, with a wide random spread, palette
 * color from the CF parameter.
 * Not reached in play (2026-11-13): did not run in the 165-move battle sweep (each move used once,
 * from the command menu to the end of its turn) or in a tour of the menus and a COM battle.
 * @unverified Name from Stadium 1.
 */
void BattleAnim_SetupEnd28Desc10WideScatterBurstFade(Particle* arg0) {
    UNUSED s32 pad[4]; // FAKE: stack padding
    Vec3s sp28;

    Particle_SpawnIndex_GetS16_0C038(arg0);
    Particle_SetScaleScaled(arg0, 0.1f);
    Particle_SetScaleTarget(arg0, 2.0f);
    Particle_SetScaleStep(arg0, 0.1f);
    sp28.x = -0x1000 - ParticleMath_RandomRange(0x6000);
    sp28.y = ParticleMath_RandomRange(0x10000);
    sp28.z = ParticleMath_RandomRange(0x800) - 0x400;
    Particle_Rotation_AddVecFromVec3s_0A4F0(arg0, sp28);
    Particle_AddPositionFromRotationTemplate1(arg0, 200.0f);
    Particle_Rotation_AddX_0A578(arg0, -0x4000);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, Particle_GetByteParam1(arg0));
    Particle_AdvanceLifecycle(arg0);
}

void Particle_DisableAndDetach(Particle* arg0);                      /* extern */
M2C_UNK func_821402B8(s8 *);                      /* extern */
M2C_UNK func_82140548(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_821406B4(s8 *);                      /* extern */
M2C_UNK func_8214F478(s8 *);                      /* extern */

/**
 * Second particle callback for end effect 28: init, step, fade out by 64, detach.
 * @unverified Name guessed from the code.
 */
void BattleAnim_CallbackEndEffect28StreamB(Particle* particle) {
    s16 temp_v0;

    temp_v0 = particle->lifecycle;
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_8214F478(particle);
        break;
    case 2:
        func_821406B4(particle);
        break;
    case 3:
        func_82140548(particle, 0, 0x40);
        break;
    case 4:
        Particle_DisableAndDetach(particle);
        break;
    }
    func_821402B8(particle);
    Particle_MoveAlongRotationXYZAlt(particle);
}

/**
 * initializes using thunderbolt or thunder
 * Effect start init 18 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used:
 * it ran for exactly Thunder, Thunderbolt.
 */
void BattleAnim_InitializeThunderThunderboltUse(void) {
    BattleAnim_SpawnCategory17MarkerSlot(100, 1);
    BattleAnim_SpawnGlobalTintColorFadeDetach(0, 0x20, 3);
    BattleAnim_CreateRepeatEffectSlotForCurrentOwner(0, 3, 8, BattleAnim_CallbackStart18And73Desc11ScatterRise, &gBattleAnimParticleDescriptors[0x11], 8, 4, 2, 0, 0x25, 0);
    BattleAnim_AddSpawnDelay(25);
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_RunThunderThunderboltUseEffect, &gBattleAnimParticleDescriptors[0x15], 0xE, 1, 2, 0, 0x25, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_RunThunderThunderboltUseEffect, &gBattleAnimParticleDescriptors[0x16], 0xE, 1, 2, 0, 0x25, 0);
    BattleAnim_SpawnDesc25AlphaHoldFadeOut(8, 2, 8, 0x8, 0xFF);
    BattleAnim_CreateRepeatEffectSlotForCurrentOwner(8, 4, 2, BattleAnim_RunDeterministicRotatingBoltOfLightning, &gBattleAnimParticleDescriptors[0xF], 0x14, 4, 7, 0, 0x25, 0);
    BattleAnim_CreateRepeatEffectSlotForCurrentOwner(8, 4, 2, BattleAnim_RunRandomRotatingBoltOfLightning, &gBattleAnimParticleDescriptors[0xF], 0x14, 4, 7, 0, 0x25, 0);
    BattleAnim_CreateRepeatEffectSlotForCurrentOwner(8, 4, 2, BattleAnim_CallbackSharedDesc13DirSprayScaledFade, &gBattleAnimParticleDescriptors[0x13], 0x14, 4, 7, 0, 0x25, 0);
    BattleAnim_CreateRepeatEffectSlotForCurrentOwner(8, 4, 2, BattleAnim_CallbackSharedDirectionalSprayFade, &gBattleAnimParticleDescriptors[0x13], 0x14, 4, 7, 0, 0x25, 0);
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
    func_8213B644(48, 0x20, 8);
    func_8213B5D8(0, 8, 5, &BattleAnim_CallbackSharedDirectionalSprayFade, &D_8218E618, 8, 3, 3, 0, 0x25, 0);
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
    func_8213B644(48, 0x20, 8);
    func_8213B5D8(0, 8, 5, &BattleAnim_CallbackSharedDirectionalSprayFade, &D_8218E618, 8, 3, 3, 0, 0x25, 0);
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
    BattleAnim_SpawnCategory17MarkerSlot(100, 1);
    BattleAnim_SpawnGlobalTintColorFadeDetach(0, 0x10, 3);
    BattleAnim_CreateRepeatEffectSlotForCurrentOwner(0, 8, 3, BattleAnim_CallbackStart59End28DirStreamFade, &gBattleAnimParticleDescriptors[0x14], 2, 1, 2, 0, 0x25, 0);
    BattleAnim_CreateRepeatEffectSlotForCurrentOwner(0, 5, 5, BattleAnim_CallbackStart59End28DirStreamFade, &gBattleAnimParticleDescriptors[0x13], 2, 1, 2, 0, 0x25, 0);
    BattleAnim_AddSpawnDelay(35);
    BattleAnim_SpawnDesc25AlphaHoldFadeOutFullAlpha(8, 4, 8, 0x8);
    BattleAnim_CreateRepeatEffectSlotForCurrentOwner(0, 4, 2, BattleAnim_CallbackSharedDesc13DirSprayScaledFade, &gBattleAnimParticleDescriptors[0x13], 0x14, 4, 2, 0, 0x25, 0);
    BattleAnim_CreateRepeatEffectSlotForCurrentOwner(0, 5, 2, BattleAnim_CallbackSharedDirectionalSprayFade, &gBattleAnimParticleDescriptors[0x13], 0x14, 4, 2, 0, 0x25, 0);
    BattleAnim_CreateRepeatEffectSlotForCurrentOwner(0, 6, 2, BattleAnim_RunDeterministicRotatingBoltOfLightning, &gBattleAnimParticleDescriptors[0xF], 0x14, 2, 1, 0, 0x25, 0);
    BattleAnim_CreateRepeatEffectSlotForCurrentOwner(0, 4, 2, BattleAnim_RunRandomRotatingBoltOfLightning, &gBattleAnimParticleDescriptors[0xF], 0x14, 2, 1, 0, 0x25, 0);
}

M2C_UNK func_8213B5D8(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK *, M2C_UNK *, s32, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_8213B644(M2C_UNK, M2C_UNK, M2C_UNK);   /* extern */
M2C_UNK func_8213B720(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK); /* extern */
extern M2C_UNK D_8218E608;
extern M2C_UNK D_8218E620;

/**
 * Starts a three-part effect: sets the tint and spawn timing, then queues
 * BattleAnim_CallbackEndEffect28StreamA, BattleAnim_CallbackEndEffect28StreamB and
 * BattleAnim_CallbackStart59End28DirStreamFade on the current owner.
 * @unverified Name guessed from the code.
 */
void BattleAnim_EndEffect28ThreePartStream(void) {
    func_8213B720(34, 4, 0x10, 8);
    func_8213B644(0, 0x20, 3);
    func_8213B644(48, 0x20, 8);
    func_8213B5D8(0, 10, 2, &BattleAnim_CallbackEndEffect28StreamA, &D_8218E608, 0xC, 1, 3, 0, 0x25, 0);
    func_8213B5D8(0, 5, 3, &BattleAnim_CallbackEndEffect28StreamB, &D_8218E608, 0xC, 2, 3, 0, 0x25, 0);
    func_8213B5D8(0, 8, 2, &BattleAnim_CallbackStart59End28DirStreamFade, &D_8218E620, 0xC, 3, 3, 0, 0x25, 0);
}

/**
 * initializes using thunder punch
 * Effect start init 73 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used:
 * it ran for exactly Thunder Punch.
 */
void BattleAnim_InitializeThunderPunchUse(void) {
    BattleAnim_CreateRepeatEffectSlotForCurrentOwner(0, 4, 5, BattleAnim_CallbackStart18And73Desc11ScatterRise, &gBattleAnimParticleDescriptors[0x11], 8, 4, 0x10, gBattleAnimCurrentAnchor, 0x25, 0);
    BattleAnim_CreateRepeatEffectSlotForCurrentOwner(0, 1, 36, BattleAnim_CallbackStart73Desc15ColorImpulseFade, &gBattleAnimParticleDescriptors[0x15], 0, 1, 0x11, gBattleAnimCurrentAnchor, 0, 0);
}

/**
 * initializes getting hit by hyper beam
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Hyper Beam.
 */
void BattleAnim_InitializeHyperBeamHitSequence(void) {
    BattleAnim_CreateRepeatEffectSlotForCurrentOwner(8, 4, 2, BattleAnim_CallbackSharedDesc13DirSprayScaledFade, &gBattleAnimParticleDescriptors[0x13], 0x14, 4, 7, 0, 0x2C, 0);
    BattleAnim_CreateRepeatEffectSlotForCurrentOwner(8, 4, 2, BattleAnim_CallbackSharedDirectionalSprayFade, &gBattleAnimParticleDescriptors[0x13], 0x14, 3, 7, 0, 0xF, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(8, BattleAnim_RunDeterministicRotatingBoltOfLightning, &gBattleAnimParticleDescriptors[0xF], 0x14, 1, 7, 0, 0x2C, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(8, BattleAnim_RunRandomRotatingBoltOfLightning, &gBattleAnimParticleDescriptors[0xF], 0x14, 1, 7, 0, 0xF, 0);
}
