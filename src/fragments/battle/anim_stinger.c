/* Stadium Zero fragment012_17ED00. */
/* C ported from the Stadium 1 decomp: src/fragments/battle_engine/battle_engine_31A7E0.c. */

#include "battle.h"

#include "m2c_macros.h"

void BattleAnim_InitStingerTrailColor(Particle* arg0);
void BattleAnim_InitStingerTrailColorDuplicate(Particle* arg0);
void BattleAnim_InitStingerMoveParticle(Particle* arg0, u8 arg1);

void BattleAnim_UpdateNeedleBlueFadeGrow(Particle* arg0);
void BattleAnim_UpdateSecondaryOwnerParticleBlueGrow(Particle* arg0);

/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Pin Missile, Poison Sting, Spike Cannon and Twineedle.
 */
void BattleAnim_InitStingerTrailColor(Particle* arg0) {
    Particle_SetScaleScaled(arg0, 0.1f);
    Particle_SetPrimColor(arg0, 0xFF, 0xFF, 0xFF);
    Particle_SetEnvColor(arg0, 0x64, 0xC8, 0xFF);
    Particle_SetPrimAlpha(arg0, 0xFF);
    Particle_AdvanceLifecycle(arg0);
}

void Particle_MarkInactive(Particle* arg0);                      /* extern */
s32 Particle_IsRunning(Particle* arg0);                          /* extern */
M2C_UNK Particle_AnimateFramesForwardLoopedThenAdvance(s8 *, M2C_UNK, M2C_UNK, M2C_UNK, s32, s32); /* extern */
M2C_UNK func_82140228(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK Particle_ApproachPrimAlpha(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_82140920(s8 *);                      /* extern */

/**
 * Seen in play (2026-11-13) in the 165-move sweep (each move used once by the 1P Pokémon): it ran
 * only for Poison Sting, Twineedle, Pin Missile and Spike Cannon.
 */
void BattleAnim_UpdateNeedleBlueFadeGrow(Particle* arg0) {
    s16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_82140920(arg0);
        break;
    case 2:
        Particle_AnimateFramesForwardLoopedThenAdvance(arg0, 0, 7, 1, 2, 0);
        Particle_ApproachPrimAlpha(arg0, 0x20, 8);
        break;
    case 3:
        Particle_MarkInactive(arg0);
        break;
    }
    if (Particle_IsRunning(arg0) != 0) {
        func_82140228(arg0, 0x3F000000, 0x3D4CCCCD);
    }
}

/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Pin Missile, Poison Sting, Spike Cannon and Twineedle.
 */
void BattleAnim_InitStingerTrailColorDuplicate(Particle* arg0) {
    Particle_SetScaleScaled(arg0, 0.1f);
    Particle_SetPrimColor(arg0, 0xFF, 0xFF, 0xFF);
    Particle_SetEnvColor(arg0, 0x64, 0xC8, 0xFF);
    Particle_SetPrimAlpha(arg0, 0xFF);
    Particle_AdvanceLifecycle(arg0);
}

s32 Particle_IsRunning(Particle* arg0);                          /* extern */
M2C_UNK func_82140228(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_82140A48();                            /* extern */

void BattleAnim_UpdateSecondaryOwnerParticleBlueGrow(Particle* arg0) {
    if (M2C_FIELD(arg0, s16 *, 0xAE) == 1) {
        func_82140A48();
    }
    if (Particle_IsRunning(arg0) != 0) {
        func_82140228(arg0, 0x3F4CCCCD, 0x3DA3D70A);
    }
}

/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Poison Sting, Twineedle, Pin Missile, Spike Cannon.
 */
void BattleAnim_InitStingerMoveParticle(Particle* arg0, u8 arg1) {
    switch (arg1) {
        case 1:
            arg0->updateCallback = BattleAnim_UpdateNeedleBlueFadeGrow;
            arg0->descriptor = &gBattleAnimParticleDescriptors[25];
            break;

        case 2:
            arg0->updateCallback = BattleAnim_UpdateSecondaryOwnerParticleBlueGrow;
            arg0->descriptor = &gBattleAnimParticleDescriptors[22];
            break;
    }
}
