/* Stadium Zero fragment012_17ED00. */
/* C ported from the Stadium 1 decomp: src/fragments/battle_engine/battle_engine_31A7E0.c. */

#include "fragments/battle_engine/battle_engine.h"

#include "m2c_macros.h"

void BattleAnim_InitStingerTrailColor(Particle* arg0);
void BattleAnim_InitStingerTrailColorDuplicate(Particle* arg0);
void BattleAnim_InitStingerMoveParticle(Particle* arg0, u8 arg1);

void BattleAnim_UpdateSecondaryOwnerParticleBlueFadeGrow(Particle* arg0);
void BattleAnim_UpdateSecondaryOwnerParticleBlueGrow(Particle* arg0);

/**
 * @unverified Name from Stadium 1.
 */
void BattleAnim_InitStingerTrailColor(Particle* arg0) {
    Particle_Field1C_SetScaled_0B938(arg0, 0.1f);
    Particle_SetPrimColor(arg0, 0xFF, 0xFF, 0xFF);
    Particle_SetEnvColor(arg0, 0x64, 0xC8, 0xFF);
    Particle_SetPrimAlpha(arg0, 0xFF);
    Particle_AdvanceLifecycle(arg0);
}

M2C_UNK func_8213C930(s8 *);                      /* extern */
s32 func_8213C9B0(s8 *);                          /* extern */
M2C_UNK func_8213CCEC(s8 *, M2C_UNK, M2C_UNK, M2C_UNK, s32, s32); /* extern */
M2C_UNK func_82140228(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_82140518(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_82140920(s8 *);                      /* extern */

void func_8214098C(s8 *arg0) {
    s16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_82140920(arg0);
        break;
    case 2:
        func_8213CCEC(arg0, 0, 7, 1, 2, 0);
        func_82140518(arg0, 0x20, 8);
        break;
    case 3:
        func_8213C930(arg0);
        break;
    }
    if (func_8213C9B0(arg0) != 0) {
        func_82140228(arg0, 0x3F000000, 0x3D4CCCCD);
    }
}

/**
 * @unverified Name from Stadium 1.
 */
void BattleAnim_InitStingerTrailColorDuplicate(Particle* arg0) {
    Particle_Field1C_SetScaled_0B938(arg0, 0.1f);
    Particle_SetPrimColor(arg0, 0xFF, 0xFF, 0xFF);
    Particle_SetEnvColor(arg0, 0x64, 0xC8, 0xFF);
    Particle_SetPrimAlpha(arg0, 0xFF);
    Particle_AdvanceLifecycle(arg0);
}

s32 func_8213C9B0(s8 *);                          /* extern */
M2C_UNK func_82140228(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_82140A48();                            /* extern */

void func_82140AB4(s8 *arg0) {
    if (M2C_FIELD(arg0, s16 *, 0xAE) == 1) {
        func_82140A48();
    }
    if (func_8213C9B0(arg0) != 0) {
        func_82140228(arg0, 0x3F4CCCCD, 0x3DA3D70A);
    }
}

/**
 * @unverified Name from Stadium 1.
 */
void BattleAnim_InitStingerMoveParticle(Particle* arg0, u8 arg1) {
    switch (arg1) {
        case 1:
            arg0->unk_08 = BattleAnim_UpdateSecondaryOwnerParticleBlueFadeGrow;
            arg0->unk_0C = &gBattleAnimParticleDescriptors[25];
            break;

        case 2:
            arg0->unk_08 = BattleAnim_UpdateSecondaryOwnerParticleBlueGrow;
            arg0->unk_0C = &gBattleAnimParticleDescriptors[22];
            break;
    }
}
