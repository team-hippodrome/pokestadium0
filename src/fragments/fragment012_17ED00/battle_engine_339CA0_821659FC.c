/* Fixed-layout split; original translation-unit boundaries remain unconfirmed. */
#include "battle_engine_339CA0.h"

/**
 * @unverified Name was previously used only by callers of this address; the definition was still func_.
 */
void BattleAnim_CallbackDescriptor26BurstChild(Particle* arg0) {
    switch (arg0->lifecycle) {
        case 1:
            BattleAnim_CallbackDescriptor26BurstChild_InitParticle(arg0);
            break;

        case 2:
            if (Particle_DecrementUnkA6ToZeroThenAdvance(arg0) != 0) {
                Particle_EnableRendering(arg0);
                ParticleMath_ScaleDirectionToLength(&arg0->motionStep, arg0->motionOffset, D_8219A880, arg0->stepMagnitude);
            }
            break;

        case 3:
            Particle_Field7C_ScaleVec_0B14C(arg0, 1.5f);
            if (Particle_TickDelayAndAdvanceLifecycle(arg0, 4) != 0) {
                Particle_Field74_SetScaled_0AD8C(arg0, 10.0f);
                Particle_FieldA6_SetS16_0BCA8(arg0, ParticleMath_ScaleDirectionToLength(&arg0->motionStep, arg0->motionOffset, D_8219A880, arg0->stepMagnitude));
            }
            break;

        case 4:
            Particle_ApproachScale(arg0, 0.1f, 0.02f);
            Particle_PrimR_Approach_0BAE4(arg0, 0xFF, 4);
            Particle_EnvR_Approach_0BB90(arg0, 0xFF, 8);
            Particle_EnvG_Approach_0BBF0(arg0, 0xFF, 8);
            Particle_DecrementUnkA6ToZeroThenAdvance(arg0);
            break;

        case 5:
            Particle_DisableAndDetach(arg0);
            break;
    }

    if (Particle_IsRenderingEnabled(arg0) != 0) {
        Particle_ApplyMotionStep(arg0);
    }
}


void func_82165BC8(s32 arg0) {
    s16 sp26;

    sp26 = Particle_GetUnkAC();
    func_821401D4(arg0, 0x3F000000);
    func_8213E14C(arg0, 0x42C80000);
    Particle_SetUnkA6(arg0, (s16) (sp26 + 1));
    func_82143408(arg0, 8);
    func_82143440(arg0, 0x33);
    func_8213CB5C(arg0);
    func_8213C9D0(arg0);
}

void BattleAnim_CallbackDescriptor26BurstEmitter(Particle* arg0) {
    switch (arg0->lifecycle) {
        case 1:
            BattleAnim_CallbackDescriptor26BurstEmitter_InitParticle(arg0);
            break;

        case 2:
            if (Particle_DecrementUnkA6ToZeroThenAdvance(arg0) != 0) {
                Particle_EnableRendering(arg0);
            }
            break;

        case 3:
            if (Particle_AnimateFramesForwardLoopedThenAdvance(arg0, 0, 0xF, 2, 1, 0) != 0) {
                BattleAnim_EmitParticleBurst(arg0, BattleAnim_CallbackDescriptor26BurstChild, &gBattleAnimParticleDescriptors[0x26], 5);
            }
            break;

        case 4:
            Particle_DisableAndDetach(arg0);
            break;
    }
}

void BattleAnim_SetupUnusedGrowingSparkVariant(Particle* arg0) {
    f32 sp24;
    s16 sp22 = Particle_FieldAC_GetS16_0C038(arg0);

    sp24 = (sp22 + 15.0f) / 20.0f;
    if (sp24 >= 1.0f) {
        sp24 = 1.0f;
    }

    Particle_SetScaleScaled(arg0, sp24);
    Particle_SetScaleTarget(arg0, 8.0f * sp24);
    Particle_SetScaleStep(arg0, D_FLT_8219786C * sp24);
    Particle_Field38_AddYScaled_08E90(arg0, 10.0f);
    Particle_SetTextureFrame(arg0, 0xF);
    ParticleGfx_RecolorPrim(arg0, 0x8);
    ParticleGfx_RecolorEnv(arg0, 0x33);
    Particle_SetPrimAlpha(arg0, 0xFF);
    Particle_FieldA6_SetS16_0BCA8(arg0, sp22 * 8);
    Particle_DisableRendering(arg0);
    Particle_AdvanceLifecycle(arg0);
}
