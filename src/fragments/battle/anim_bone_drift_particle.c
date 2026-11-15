/* Stadium Zero fragment012_17ED00. */

#include "global.h"
#include "battle.h"

void func_821401D4(Particle*, f32);
void func_8213E11C(Particle*, f32);
u32 ParticleMath_RandomRange(u32 arg0);
void Particle_SetRotationStepY(Particle*, s16);
void Particle_SetStepMagnitudeScaled(Particle*, f32);
void Particle_SetMotionStepYScaled(Particle*, f32);
void func_82143478(Particle*, s32);
void Particle_SetPrimAlpha(s8 *arg0, char arg1);
void Particle_SetParam0(Particle*, s32);
void func_8213C9D0(Particle*);

/**
 * Init step for a small particle that drifts to a bone: scale 0.16, a random Y spin, slow
 * step and rise speeds, palette 0x1A, full alpha and a 2-frame delay.
 * @unverified Name guessed from the code.
 */
void BattleAnim_InitBoneDriftEmber(Particle* particle) {
    func_821401D4(particle, 0.16f);
    func_8213E11C(particle, -3.2f);
    Particle_SetRotationStepY(particle, ParticleMath_RandomRange(0x10000));
    Particle_SetStepMagnitudeScaled(particle, 0.085f);
    Particle_SetMotionStepYScaled(particle, 0.44f);
    func_82143478(particle, 0x1A);
    Particle_SetPrimAlpha(particle, 0xFF);
    Particle_SetParam0(particle, 2);
    func_8213C9D0(particle);
}

extern Vec3f D_8219A898;

/**
 * Particle callback: init, then follows the owner's bone CD while shrinking and fading,
 * then detaches. Hidden while not running.
 * @unverified Name guessed from the code.
 */
void BattleAnim_CallbackBoneDriftEmber(Particle* particle) {
    switch (particle->lifecycle) {
        case 1:
            BattleAnim_InitBoneDriftEmber(particle);
            break;

        case 2:
            BattleAnim_GetOwnerBonePosition(particle->pokemon, particle->byteParam0, &D_8219A898);
            Particle_ApproachPosition(particle, D_8219A898);
            Particle_ApproachScale(particle, 0.2f, 0.053f);
            Particle_ApproachPrimAlphaThenAdvance(particle, 0x10, 0x1A);
            Particle_PrimG_Approach_0BB14(particle, 0, 0x40);
            if (Particle_DecrementParam0ToZero(particle) != 0) {
                Particle_PrimR_Approach_0BAE4(particle, 0, 8);
                Particle_EnvR_Approach_0BB90(particle, 0, 0xE);
            }
            break;

        case 3:
            Particle_DisableAndDetach(particle);
            break;
    }

    if (particle->lifecycle > 0) {
        Particle_MoveXZAlongRotationY(particle);
        Particle_ApplyMotionStepY(particle);
    }

    if (BattleScene_IsParticipantModelVisible(particle->pokemon)) {
        Particle_EnableRendering(particle);
    } else {
        Particle_DisableRendering(particle);
    }
}

extern void* D_82199DE0[];
extern void* D_8219A810;
extern s32 gNextGameState;
extern u8 D_8218E5A0[];
s32 func_82107CF0(void*);
void func_8213B5D8(s32, s32, s32, void (*)(Particle*), u8*, s32, s32, s32, s32, s32, s32);

/**
 * Spawns the BattleAnim_CallbackBoneDriftEmber effect for side arg0 when gNextGameState is 0x8080 and that
 * Pokemon's species is 6 (Charizard).
 * @unverified Name guessed from the code.
 */
void BattleAnim_SpawnCharizardBoneDriftEmbers(s32 side) {
    D_8219A810 = D_82199DE0[side];
    if (gNextGameState == 0x8080) {
        if (func_82107CF0(D_8219A810) == 6) {
            func_8213B5D8(0, 0, -1, BattleAnim_CallbackBoneDriftEmber, D_8218E5A0, 0, 1, 0x11, 0xA, 0, 0);
        }
    }
}
