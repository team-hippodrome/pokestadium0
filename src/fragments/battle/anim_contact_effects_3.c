/* Fixed-layout split; original translation-unit boundaries remain unconfirmed. */
#include "battle.h"

// Declared here instead of in a header: the callers of these disagree on their types.
M2C_UNK Particle_AnimateFramesForwardLoopedThenAdvance(s8 *, M2C_UNK, M2C_UNK, M2C_UNK, s32, s32);
M2C_UNK Particle_ApplyMotionStep(s8 *);
M2C_UNK Particle_SetUnkA6(s8 *, M2C_UNK);
M2C_UNK func_8213C9D0(s8 *);
M2C_UNK func_821401D4(s8 *, M2C_UNK);
M2C_UNK func_82143408(s32, M2C_UNK);

/**
 * No caller in play (2026-11-13): nothing that runs reaches it, not even through callbacks, data
 * tables or fragment headers.
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


/**
 * Init step: scale 0.5, position offset 100, a delay of spawn index + 1 frames, prim
 * palette 8 and env palette 0x33.
 */
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

/**
 * Particle callback: after its delay, plays frames 0-15 and then emits a burst of five
 * descriptor 0x26 child particles, then detaches.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal or j,
 * no pointer word, no lui/addiu pair in any fragment), so play cannot reach it.
 * @unverified Name from Stadium 1.
 */
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

/**
 * Init step for the growing spark: scales size, scale target and step by the spawn index
 * (arg AC), raises it by 10, sets frame 15, colors and full alpha, and delays the start by
 * eight frames per index.
 * Not reached in play (2026-11-13): did not run in the 165-move battle sweep (each move used once,
 * from the command menu to the end of its turn) or in a tour of the menus and a COM battle.
 * @unverified Name from Stadium 1.
 */
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
