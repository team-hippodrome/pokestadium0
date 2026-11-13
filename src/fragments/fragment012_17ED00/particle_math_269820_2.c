/* Stadium Zero fragment012_17ED00. */
/* C ported from the Stadium 1 decomp: src/fragments/particle_math/particle_math_269820.c. */

#include "fragments/particle_math/particle_math.h"
#include "geo_render.h"
extern ParticleDescriptor gDefaultParticleDescriptor;

#include "m2c_macros.h"

s32 Particle_TickDelayAndAdvanceLifecycle(Particle* arg0, s16 arg1);
void Particle_SetFlags(Particle* arg0, s32 arg1);
void Particle_ClearFlags(Particle* arg0, s32 arg1);
void Particle_ToggleFlags(Particle* arg0, s32 arg1);
s32 Particle_HasFlags(Particle* arg0, s32 arg1);
s32 Particle_LacksFlags(Particle* arg0, s32 arg1);
void Particle_EnableRendering(Particle* arg0);
void Particle_DisableRendering(Particle* arg0);
s32 Particle_IsRenderingEnabled(Particle* arg0);
void Particle_EnableFlag40(Particle* arg0);
void Particle_DisableFlag40(Particle* arg0);
void Particle_HasFlag40(Particle* arg0);
s32 Particle_AnimateFramesForwardAndAdvanceLifecycle(Particle* arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5);
s32 Particle_AnimateFramesReverseAndAdvanceLifecycle(Particle* arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5);
void Particle_SetPositionFromRotationTemplate1(Particle* arg0, f32 arg1);
void Particle_SetPositionFromRotationTemplate2(Particle* arg0, f32 arg1);
void Particle_AddPositionFromRotationTemplate1(Particle* arg0, f32 arg1);
void Particle_AddPositionFromRotationTemplate2(Particle* arg0, f32 arg1);
void Particle_SetMotionOffsetYScaled(Particle* arg0, f32 arg1);
void Particle_SetMotionOffsetZScaled(Particle* arg0, f32 arg1);
void Particle_AddMotionOffsetYScaled(Particle* arg0, f32 arg1);
void Particle_AddMotionOffsetZScaled(Particle* arg0, f32 arg1);
void Particle_SubMotionOffsetYScaled(Particle* arg0, f32 arg1);
void Particle_SubMotionOffsetZScaled(Particle* arg0, f32 arg1);
s32 Particle_ApproachMotionOffsetY(Particle* arg0, f32 arg1);
s32 Particle_ApproachMotionOffsetZ(Particle* arg0, f32 arg1);
void Particle_ApplyMotionStepY(Particle* arg0);
void Particle_ApplyMotionStepZ(Particle* arg0);
void Particle_AddVelocityXZFromRotationYViaHelpers(Particle* arg0);
void Particle_AddVelocityFromRotationTemplate2(Particle* arg0);
void Particle_SetMotionTargetXScaled(Particle* arg0, f32 arg1);
f32 ParticleMath_ScaleApproachStep(f32 arg0);
void Particle_SetRotationTargetXY(Particle* arg0, s16 arg1, s16 arg2);
void Particle_Field94_AddXFromField9A_0A4B4(Particle* arg0);
void Particle_Field94_SubX_0A63C(Particle* arg0, s16 arg1);
void Particle_ApproachRotationTargetXY(Particle* arg0);
void Particle_ApproachRotationTargetXYZ(Particle* arg0);
s32 Particle_Field94_DecrementXTo_0A7DC(Particle* arg0, s32 arg1, s32 arg2);
void Particle_AddRotationRandomSignedXY(Particle* arg0, s32 arg1, s32 arg2);
void Particle_AddRotationRandomSignedXYWithXHalfTurn(Particle* arg0, s32 arg1, s32 arg2);
void Particle_AddRotationRandomSignedY(Particle* arg0, s32 arg1);
void Particle_AddRotationRandomSignedYWithHalfTurn(Particle* arg0, s32 arg1);
void Particle_AddRotationRandomSignedXWithFixedYQuarterTurn(Particle* arg0);
s32 Particle_Field74_Approach_0ADBC(Particle* arg0, f32 arg1, f32 arg2);
s32 Particle_Field7C_IncrementXUntilAtLeast_0AF54(Particle* arg0, f32 arg1, f32 arg2);
s32 Particle_Field7C_IncrementYUntilAtLeast_0AFA8(Particle* arg0, f32 arg1, f32 arg2);
s32 Particle_Field7C_DecrementXUntilAtMost_0B050(Particle* arg0, f32 arg1, f32 arg2);
s32 Particle_Field7C_DecrementYUntilAtMost_0B0A4(Particle* arg0, f32 arg1, f32 arg2);
void Particle_SetScaleScaled(Particle* arg0, f32 arg1);
void Particle_SetScale(Particle* arg0, f32 arg1);
void Particle_SetScaleTarget(Particle* arg0, f32 arg1);
void Particle_SetScaleStep(Particle* arg0, f32 arg1);
s32 Particle_ApproachScale(Particle* arg0, f32 arg1, f32 arg2);
s32 Particle_ApproachScaleThenAdvance(Particle* arg0, f32 arg1, f32 arg2);
s32 Particle_ApproachScaleTarget(Particle* arg0);
s32 Particle_ApproachScaleTargetThenAdvance(Particle* arg0);
s32 Particle_StepScaleTarget(Particle* arg0, f32 arg1, f32 arg2);
s32 Particle_ApproachPrimAlphaThenAdvance(Particle* arg0, u8 arg1, u8 arg2);
s32 Particle_FieldA6_DecrementToZero_0BD08(Particle* arg0, s16 arg1);
s32 Particle_FieldA6_DecrementToZeroAndStepState_0BD34(Particle* arg0, s16 arg1);
s32 Particle_FieldA6_DecrementToStep1_0BD80(Particle* arg0, s16 arg1);
s32 Particle_DecrementUnkA6ToZero(Particle* arg0);
s32 Particle_DecrementUnkA6ToZeroThenAdvance(Particle* arg0);
s32 Particle_DecrementUnkA8ToZero(Particle* arg0);
s32 Particle_FieldA8_DecrementToZeroStep1AndStepState_0BE8C(Particle* arg0);
s32 Particle_ApproachUnkAEThenAdvance(Particle* arg0, s16 arg1, s16 arg2);

void Particle_AdvanceLifecycle(Particle* arg0);
s32 Particle_TickDelayTimer(Particle* arg0, s16 arg1);
s32 Particle_AnimateFramesPingPong(Particle* arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5);
s32 Particle_AnimateFramesReverseFirstPingPong(Particle* arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5);
void Particle_Field38_SetVecFromVec3fScaled_08C20(Particle* arg0, Vec3f arg1);
void Particle_Field38_AddVecScaledFromVec3f_08D78(Particle* arg0, Vec3f arg1);
void Particle_ApplyMotionStepXY(Particle* arg0);
void Particle_Field50_AddXYFromField7C_09C34(Particle* arg0);
void Particle_FieldA0_SetX_0A400(Particle* arg0, s16 arg1);
void Particle_FieldA0_SetY_0A414(Particle* arg0, s16 arg1);
void Particle_Field94_AddX_0A578(Particle* arg0, s16 arg1);
void Particle_Field94_AddY_0A594(Particle* arg0, s16 arg1);
void Particle_ApproachRotationTargetX(Particle* arg0);
void Particle_ApproachRotationTargetY(Particle* arg0);
void Particle_ApproachRotationTargetZ(Particle* arg0);
void Particle_ComputeVectorFromRotationXYZAlt(Particle* arg0, f32 arg1, Vec3f* arg2);
void Particle_ComputeVectorFromRotationYZVariant(Particle* arg0, f32 arg1, Vec3f* arg2);
void Particle_SetMotionStepXZFromRotationY(Particle* arg0);
void Particle_SetMotionStepFromRotationXZ(Particle* arg0);
s32 Particle_PrimAlpha_Approach_0BC2C(Particle* arg0, u8 arg1, u8 arg2);
s32 Particle_FieldA6_DecrementTo_0BCC4(Particle* arg0, s16 arg1, s16 arg2);
s32 Particle_FieldA8_DecrementTo_0BE30(Particle* arg0, s16 arg1);
s32 Particle_FieldAE_Approach_0BF60(Particle* arg0, s16 arg1, s16 arg2);

/**
 * Tick the delay timer and advance lifecycle when it expires.
 * Seen in play (2026-11-12) in move animations (30-move sweep): it changed lifecycle (0xAE) of
 * the live particle, e.g. 0x2 -> 0x3.
 */
s32 Particle_TickDelayAndAdvanceLifecycle(Particle* arg0, s16 arg1) {
    s32 sp1C = Particle_TickDelayTimer(arg0, arg1);

    if (sp1C != 0) {
        Particle_AdvanceLifecycle(arg0);
    }
    return sp1C;
}

/**
 * Set the selected particle flag bits.
 * Seen in play (2026-11-12) in move animations (30-move sweep): it changed flags (0x18) of the
 * live particle, e.g. 0x0 -> 0x4.
 */
void Particle_SetFlags(Particle* arg0, s32 arg1) {
    arg0->flags |= arg1;
}

/**
 * Clear the selected particle flag bits.
 * Seen in play (2026-11-12) in move animations (30-move sweep): it changed flags (0x18) of the
 * live particle, e.g. 0x4 -> 0x0.
 */
void Particle_ClearFlags(Particle* arg0, s32 arg1) {
    arg0->flags &= ~arg1;
}

/**
 * Toggle the selected particle flag bits.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void Particle_ToggleFlags(Particle* arg0, s32 arg1) {
    arg0->flags ^= arg1;
}

/**
 * Return whether any selected flag bit is set.
 * Seen in play (2026-11-13) in the 165-move sweep: with flags 0x4 it returned 0 for mask 0x108 and
 * 1 for mask 0x4.
 */
s32 Particle_HasFlags(Particle* arg0, s32 arg1) {
    s32 var_v1 = 0;

    if (arg0->flags & arg1) {
        var_v1 = 1;
    }
    return var_v1;
}

/**
 * Return whether all selected flag bits are clear.
 * Seen in play (2026-11-13) in the 165-move sweep: with flags 0x4 it returned 1 for masks 0x800 and
 * 0x200.
 */
s32 Particle_LacksFlags(Particle* arg0, s32 arg1) {
    s32 var_v1 = 0;

    if (!(arg0->flags & arg1)) {
        var_v1 = 1;
    }
    return var_v1;
}

/**
 * Set flag 4, which gates drawing in both particle render passes.
 * Seen in play (2026-11-12): with this function stubbed to return at once, Flamethrower's flames
 * never appeared (same frame, same savestate), while the battle went on normally. In the move
 * sweep it set flag 4.
 */
void Particle_EnableRendering(Particle* arg0) {
    Particle_SetFlags(arg0, 4);
}

/**
 * Clear flag 4 to suppress drawing without freeing the particle.
 * Seen in play (2026-11-12) in move animations: cleared flag 4, the flag Particle_EnableRendering
 * sets and which the flames need in order to be drawn.
 */
void Particle_DisableRendering(Particle* arg0) {
    Particle_ClearFlags(arg0, 4);
}

/**
 * Test flag 4, the per-particle drawing gate.
 * Seen in play (2026-11-12) in move animations: tests flag 4, the render flag confirmed by
 * stubbing Particle_EnableRendering.
 */
s32 Particle_IsRenderingEnabled(Particle* arg0) {
    return Particle_HasFlags(arg0, 4);
}

/**
 * Set flag 0x40; its effect-specific interpretation is unresolved.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void Particle_EnableFlag40(Particle* arg0) {
    Particle_SetFlags(arg0, 0x40);
}

/**
 * Clear flag 0x40 without changing the other flags.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void Particle_DisableFlag40(Particle* arg0) {
    Particle_ClearFlags(arg0, 0x40);
}

/**
 * Evaluate flag 0x40 and discard the result; the original void interface returns no test value.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void Particle_HasFlag40(Particle* arg0) {
    Particle_HasFlags(arg0, 0x40);
}

/**
 * Sets the particle's textureFrame to arg1.
 * Seen in play (2026-11-13) (tour of menus and a COM battle): ran in the battle opening, a switch
 * in battle and a Pound turn.
 * @unverified Name and comment guessed from the code.
 */
void Particle_SetTextureFrame(Particle* arg0, s16 arg1) {
    M2C_FIELD(arg0, s8 *, 0xC3) = (s8) arg1;
}

/**
 * Steps textureFrame from `arg1` up to `arg2` by `arg3` every `arg4` frames, restarting `arg5` times. Returns 1 when the last loop ends on `arg2`. Flag 1 marks it as started.
 */
s32 Particle_AnimateFramesForwardLooped(Particle* arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5) {
    s32 sp1C = 0;

    if (Particle_LacksFlags(arg0, 1) != 0) {
        arg0->frameTimer = arg4;
        arg0->textureFrame = arg1;
        arg0->loopsRemaining = arg5;
        Particle_SetFlags(arg0, 1);
    } else {
        arg0->frameTimer--;
        if (arg0->frameTimer <= 0) {
            arg0->frameTimer = arg4;

            arg0->textureFrame += arg3;
            if (arg2 < arg0->textureFrame) {
                if (arg0->loopsRemaining > 0) {
                    arg0->loopsRemaining--;
                }

                if (arg0->loopsRemaining == 0) {
                    arg0->textureFrame = arg2;
                    sp1C = 1;
                } else {
                    arg0->textureFrame = arg1;
                }
            }
        }
    }
    return sp1C;
}

s32 Particle_AnimateFramesForwardLooped(Particle*, s16, s16, s16, s16, s16);

/**
 * Particle_AnimateFramesForwardLooped, then clears flag 1 and advances the lifecycle when it finishes.
 */
s32 Particle_AnimateFramesForwardLoopedThenAdvance(Particle* arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5) {
    s32 sp24 = Particle_AnimateFramesForwardLooped(arg0, arg1, arg2, arg3, arg4, arg5);

    if (sp24 != 0) {
        Particle_ClearFlags(arg0, 1);
        Particle_AdvanceLifecycle(arg0);
    }

    return sp24;
}

/**
 * Like Particle_AnimateFramesForwardLooped, but steps textureFrame down from `arg1` to `arg2`.
 * No caller in play (2026-11-13): it is only called from
 * Particle_AnimateFramesReverseLoopedThenAdvance, which has no caller in the ROM itself.
 * @unverified Name and comment guessed from the code.
 */
s32 Particle_AnimateFramesReverseLooped(Particle* arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5) {
    s32 sp1C = 0;

    if (Particle_LacksFlags(arg0, 1) != 0) {
        arg0->frameTimer = arg4;
        arg0->textureFrame = arg1;
        arg0->loopsRemaining = arg5;
        Particle_SetFlags(arg0, 1);
    } else {
        arg0->frameTimer--;
        if (arg0->frameTimer <= 0) {
            arg0->frameTimer = arg4;

            arg0->textureFrame -= arg3;
            if (arg0->textureFrame < arg2) {
                if (arg0->loopsRemaining > 0) {
                    arg0->loopsRemaining--;
                }

                if (arg0->loopsRemaining == 0) {
                    arg0->textureFrame = arg2;
                    sp1C = 1;
                } else {
                    arg0->textureFrame = arg1;
                }
            }
        }
    }

    return sp1C;
}

s32 Particle_AnimateFramesReverseLooped(Particle*, s16, s16, s16, s16, s16);

/**
 * Particle_AnimateFramesReverseLooped, then clears flag 1 and advances the lifecycle when it finishes.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name and comment guessed from the code.
 */
s32 Particle_AnimateFramesReverseLoopedThenAdvance(Particle* arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5) {
    s32 sp24 = Particle_AnimateFramesReverseLooped(arg0, arg1, arg2, arg3, arg4, arg5);

    if (sp24 != 0) {
        Particle_ClearFlags(arg0, 1);
        Particle_AdvanceLifecycle(arg0);
    }

    return sp24;
}

/**
 * Run ping-pong texture-frame animation with a frame timer and loop counter; return 1 on completion.
 * No caller in play (2026-11-13): it is only called from
 * Particle_AnimateFramesForwardAndAdvanceLifecycle, which has no caller in the ROM itself.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
s32 Particle_AnimateFramesPingPong(Particle* arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5) {
    s32 sp24 = 0;

    if (Particle_LacksFlags(arg0, 1) != 0) {
        arg0->frameTimer = arg4;
        arg0->textureFrame = arg1;
        arg0->loopsRemaining = arg5;
        Particle_SetFlags(arg0, 1);
        Particle_ClearFlags(arg0, 0x10);
    } else {
        arg0->frameTimer--;
        if (arg0->frameTimer <= 0) {
            arg0->frameTimer = arg4;

            if (Particle_LacksFlags(arg0, 0x10) != 0) {
                arg0->textureFrame += arg3;
                if (arg0->textureFrame >= arg2) {
                    arg0->textureFrame = arg2;
                    Particle_SetFlags(arg0, 0x10);
                }
            } else {
                arg0->textureFrame -= arg3;
                if (arg1 >= arg0->textureFrame) {
                    arg0->textureFrame = arg1;
                    if (arg0->loopsRemaining > 0) {
                        arg0->loopsRemaining--;
                    }

                    if (arg0->loopsRemaining == 0) {
                        Particle_ClearFlags(arg0, 0x20);
                        Particle_ClearFlags(arg0, 1);
                        sp24 = 1;
                    } else {
                        Particle_ClearFlags(arg0, 0x10);
                        Particle_SetFlags(arg0, 0x20);
                    }
                }
            }
        }
    }

    return sp24;
}

/**
 * Run the corresponding frame animation and advance lifecycle when it reports completion.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
s32 Particle_AnimateFramesForwardAndAdvanceLifecycle(Particle* arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5) {
    s32 sp24 = Particle_AnimateFramesPingPong(arg0, arg1, arg2, arg3, arg4, arg5);

    if (sp24 != 0) {
        Particle_AdvanceLifecycle(arg0);
    }

    return sp24;
}

/**
 * Run reverse-first ping-pong texture-frame animation with a frame timer and loop counter; return 1 on completion.
 * No caller in play (2026-11-13): it is only called from
 * Particle_AnimateFramesReverseAndAdvanceLifecycle, which has no caller in the ROM itself.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
s32 Particle_AnimateFramesReverseFirstPingPong(Particle* arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5) {
    s32 sp24 = 0;

    if (Particle_LacksFlags(arg0, 1) != 0) {
        arg0->frameTimer = arg4;
        arg0->textureFrame = arg1;
        arg0->loopsRemaining = arg5;
        Particle_SetFlags(arg0, 1);
        Particle_ClearFlags(arg0, 0x10);
    } else {
        arg0->frameTimer--;
        if (arg0->frameTimer <= 0) {
            arg0->frameTimer = arg4;
            if (Particle_LacksFlags(arg0, 0x10) != 0) {
                arg0->textureFrame -= arg3;
                if (arg2 >= arg0->textureFrame) {
                    arg0->textureFrame = arg2;
                    Particle_SetFlags(arg0, 0x10);
                }
            } else {
                arg0->textureFrame += arg3;
                if (arg0->textureFrame >= arg1) {
                    arg0->textureFrame = arg1;
                    if (arg0->loopsRemaining > 0) {
                        arg0->loopsRemaining--;
                    }

                    if (arg0->loopsRemaining == 0) {
                        Particle_ClearFlags(arg0, 1);
                        sp24 = 1;
                    } else {
                        Particle_ClearFlags(arg0, 0x10);
                    }
                }
            }
        }
    }
    return sp24;
}

/**
 * Run the corresponding frame animation and advance lifecycle when it reports completion.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
s32 Particle_AnimateFramesReverseAndAdvanceLifecycle(Particle* arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5) {
    s32 sp24 = Particle_AnimateFramesReverseFirstPingPong(arg0, arg1, arg2, arg3, arg4, arg5);

    if (sp24 != 0) {
        Particle_AdvanceLifecycle(arg0);
    }
    return sp24;
}

/**
 * Set phase to one and clear the phase-timer initialization bit.
 * Seen in play (2026-11-12) in move animations (30-move sweep): it changed phase (0xB4) of the
 * live particle, e.g. 0x0 -> 0x1.
 */
void Particle_BeginPhase(Particle* arg0) {
    arg0->phase = 1;
    Particle_ClearFlags(arg0, 2);
}

/**
 * Set phase to zero and clear the phase-timer initialization bit.
 * Seen in play (2026-11-13) (tour of menus and a COM battle): ran in the battle opening, a switch
 * in battle and a Pound turn.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void Particle_ResetPhase(Particle* arg0) {
    arg0->phase = 0;
    Particle_ClearFlags(arg0, 2);
}

/**
 * Increments the particle's phase.
 * Seen in play (2026-11-12) in move animations (30-move sweep): it changed phase (0xB4) of the
 * live particle, e.g. 0x1 -> 0x2.
 */
void Particle_IncrementPhase(s8 *arg0) {
    M2C_FIELD(arg0, s16 *, 0xB4) = (s16) (M2C_FIELD(arg0, s16 *, 0xB4) + 1);
}

/**
 * Initialize under flag 2, decrement immediately, and finish only after the timer becomes negative.
 * Seen in play (2026-11-12) in move animations (30-move sweep): it changed phaseTimer (0xB6) of
 * the live particle, e.g. 0x0 -> 0x1.
 */
s32 Particle_TickPhaseTimer(Particle* arg0, s16 arg1) {
    s32 sp1C = 0;

    if (Particle_LacksFlags(arg0, 2) != 0) {
        Particle_SetFlags(arg0, 2);
        arg0->phaseTimer = arg1;
    }

    arg0->phaseTimer--;
    if (arg0->phaseTimer < 0) {
        Particle_ClearFlags(arg0, 2);
        sp1C = 1;
    }
    return sp1C;
}

/**
 * Sum origin and both offset terms; copy the resulting transform and alpha to an associated DisplayObject.
 * Seen in play (2026-11-12) in move animations (30-move sweep): it changed worldPosition
 * (0x28-0x30) of the live particle, e.g. -23.555 -> 160.
 */
void Particle_UpdateWorldTransform(Particle* arg0) {
    arg0->worldPosition.x = arg0->origin.x + arg0->positionOffset.x + arg0->motionOffset.x;
    arg0->worldPosition.y = arg0->origin.y + arg0->positionOffset.y + arg0->motionOffset.y;
    arg0->worldPosition.z = arg0->origin.z + arg0->positionOffset.z + arg0->motionOffset.z;

    if (arg0->displayObject != NULL) {
        arg0->displayObject->position.x = arg0->worldPosition.x;
        arg0->displayObject->position.y = arg0->worldPosition.y;
        arg0->displayObject->position.z = arg0->worldPosition.z;

        arg0->displayObject->scale.x = arg0->scale;
        arg0->displayObject->scale.y = arg0->scale;
        arg0->displayObject->scale.z = arg0->scale;

        if (Particle_LacksFlags(arg0, 0x200) != 0) {
            arg0->displayObject->rotation.x = arg0->rotation.x;
            arg0->displayObject->rotation.y = arg0->rotation.y;
            arg0->displayObject->rotation.z = arg0->rotation.z;
        }
        arg0->displayObject->lodFraction = arg0->prim_a;
    }
}

/**
 * Set the base position offset after multiplying each input by the render context's Y scale.
 * Seen in play (2026-11-13) in the 165-move sweep: with (0, 0, 0) it set positionOffset.y (0x38)
 * from -19.36 to 0.
 */
void Particle_SetPosition(Particle* arg0, f32 arg1, f32 arg2, f32 arg3) {
    M2C_FIELD(arg0, f32*, 0x34) = arg1 * gParticleRenderContext.scale.y;
    M2C_FIELD(arg0, f32*, 0x34 + 4) = arg2 * gParticleRenderContext.scale.y;
    M2C_FIELD(arg0, f32*, 0x34 + 8) = arg3 * gParticleRenderContext.scale.y;
}

/**
 * Sets the particle's position offset to arg1 times the global particle scale.
 * @unverified Name guessed from the code.
 */
void Particle_Field38_SetVecFromVec3fScaled_08C20(Particle* arg0, Vec3f arg1) {
    arg0->positionOffset.x = arg1.x * gParticleRenderContext.scale.y;
    arg0->positionOffset.y = arg1.y * gParticleRenderContext.scale.y;
    arg0->positionOffset.z = arg1.z * gParticleRenderContext.scale.y;
}

/**
 * Sets positionOffset (unscaled).
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name and comment guessed from the code.
 */
void Particle_SetPositionOffset(s8 *arg0, f32 arg1, f32 arg2, f32 arg3) {
    M2C_FIELD(arg0, f32 *, 0x34) = arg1;
    M2C_FIELD(arg0, f32 *, 0x38) = arg2;
    M2C_FIELD(arg0, f32 *, 0x3C) = arg3;
}

extern f32 D_FLT_8219A824;

/**
 * Sets the particle's positionOffset.x to arg1 times the particle scale D_FLT_8219A824.
 * Seen in play (2026-11-12) in move animations (30-move sweep): it changed positionOffset.x
 * (0x34) of the live particle, e.g. 0 -> 23.4.
 */
void Particle_SetPosOffsetXScaled(s8 *arg0, f32 arg1) {
    M2C_FIELD(arg0, f32 *, 0x34) = (f32) (arg1 * D_FLT_8219A824);
}

extern f32 D_FLT_8219A824;

/**
 * Sets the particle's positionOffset.y to arg1 times the particle scale D_FLT_8219A824.
 * Seen in play (2026-11-12) in move animations (30-move sweep): it changed positionOffset.y
 * (0x38) of the live particle, e.g. 0 -> -17.6.
 */
void Particle_SetPosOffsetYScaled(s8 *arg0, f32 arg1) {
    M2C_FIELD(arg0, f32 *, 0x38) = (f32) (arg1 * D_FLT_8219A824);
}

extern f32 D_FLT_8219A824;

/**
 * Sets the particle's positionOffset.z to arg1 times the particle scale D_FLT_8219A824.
 * Seen in play (2026-11-12) in move animations (30-move sweep): it changed positionOffset.z
 * (0x3C) of the live particle, e.g. 0 -> 23.4.
 */
void Particle_SetPosOffsetZScaled(s8 *arg0, f32 arg1) {
    M2C_FIELD(arg0, f32 *, 0x3C) = (f32) (arg1 * D_FLT_8219A824);
}

/**
 * Adds arg1 times the global particle scale to the particle's position offset.
 * @unverified Name guessed from the code.
 */
void Particle_Field38_AddVecScaledFromVec3f_08D78(Particle* arg0, Vec3f arg1) {
    arg0->positionOffset.x += arg1.x * gParticleRenderContext.scale.y;
    arg0->positionOffset.y += arg1.y * gParticleRenderContext.scale.y;
    arg0->positionOffset.z += arg1.z * gParticleRenderContext.scale.y;
}

/**
 * Adds arg1 to the particle's position offset, unscaled.
 * @unverified Name guessed from the code.
 */
void Particle_Field38_AddVecFromVec3f_08DD8(Particle* arg0, Vec3f arg1) {
    arg0->positionOffset.x += arg1.x;
    arg0->positionOffset.y += arg1.y;
    arg0->positionOffset.z += arg1.z;
}

/**
 * Adds (arg1, arg2, arg3) times the global particle scale to the particle's position
 * offset.
 * @unverified Name guessed from the code.
 */
void Particle_Field38_AddVecScaled_08E18(Particle* arg0, f32 arg1, f32 arg2, f32 arg3) {
    arg0->positionOffset.x += arg1 * gParticleRenderContext.scale.y;
    arg0->positionOffset.y += arg2 * gParticleRenderContext.scale.y;
    arg0->positionOffset.z += arg3 * gParticleRenderContext.scale.y;
}

extern f32 D_FLT_8219A824;

/**
 * Adds arg1 times the particle scale D_FLT_8219A824 to the particle's positionOffset.x.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name and comment guessed from the code.
 */
void Particle_AddPosOffsetXScaled(s8 *arg0, f32 arg1) {
    M2C_FIELD(arg0, f32 *, 0x34) = (f32) (M2C_FIELD(arg0, f32 *, 0x34) + (arg1 * D_FLT_8219A824));
}

extern f32 D_FLT_8219A824;

/**
 * Adds arg1 times the particle scale D_FLT_8219A824 to the particle's positionOffset.y.
 * Seen in play (2026-11-12) in move animations (30-move sweep): it changed positionOffset.y
 * (0x38) of the live particle, e.g. 10.56 -> 28.16.
 */
void Particle_AddPosOffsetYScaled(s8 *arg0, f32 arg1) {
    M2C_FIELD(arg0, f32 *, 0x38) = (f32) (M2C_FIELD(arg0, f32 *, 0x38) + (arg1 * D_FLT_8219A824));
}

extern f32 D_FLT_8219A824;

/**
 * Adds arg1 times the particle scale D_FLT_8219A824 to the particle's positionOffset.z.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name and comment guessed from the code.
 */
void Particle_AddPosOffsetZScaled(s8 *arg0, f32 arg1) {
    M2C_FIELD(arg0, f32 *, 0x3C) = (f32) (M2C_FIELD(arg0, f32 *, 0x3C) + (arg1 * D_FLT_8219A824));
}

/**
 * Moves the position offset arg1 units (scaled) along the particle's Y rotation in the XZ
 * plane.
 * @unverified Name guessed from the code.
 */
void Particle_AddPositionOffsetAlongRotationY(Particle* arg0, f32 arg1) {
    arg0->positionOffset.x += arg1 * SINS(arg0->rotation.y) * gParticleRenderContext.scale.y;
    arg0->positionOffset.z += arg1 * COSS(arg0->rotation.y) * gParticleRenderContext.scale.y;
}

/**
 * Add to positionOffset.x, positionOffset.z with render-context Y scaling.
 * Seen in play (2026-11-13) in the 165-move sweep (Thrash, Sonic Boom): it changed positionOffset.x
 * and .z (0x34, 0x3C) and left .y alone.
 */
void Particle_AddPositionOffsetAlongRotationYPlus180(Particle* arg0, f32 arg1) {
    arg0->positionOffset.x += arg1 * SINS(arg0->rotation.y + 0x8000) * gParticleRenderContext.scale.y;
    arg0->positionOffset.z += arg1 * COSS(arg0->rotation.y + 0x8000) * gParticleRenderContext.scale.y;
}

/**
 * Moves the position offset arg1 units (scaled) in the XZ plane, a quarter turn from the
 * particle's Y rotation.
 * @unverified Name guessed from the code.
 */
void Particle_AddPositionOffsetAlongRotationYPlus90(Particle* arg0, f32 arg1) {
    arg0->positionOffset.x += arg1 * SINS(arg0->rotation.y + 0x4000) * gParticleRenderContext.scale.y;
    arg0->positionOffset.z += arg1 * COSS(arg0->rotation.y + 0x4000) * gParticleRenderContext.scale.y;
}

/**
 * Add to positionOffset.x, positionOffset.z with render-context Y scaling.
 * Seen in play (2026-11-13) in the 165-move sweep (Dig, Barrier, Light Screen, Reflect): with
 * rotation.y = 0x4000 (so rotation.y - 0x4000 = 0), arg1 = 20 added 72 (20 times the 3.6 render
 * scale) to positionOffset.z and nothing to x; arg1 = 15 added 54.
 */
void Particle_AddPositionOffsetAlongRotationYMinus90(Particle* arg0, f32 arg1) {
    arg0->positionOffset.x += arg1 * SINS(arg0->rotation.y - 0x4000) * gParticleRenderContext.scale.y;
    arg0->positionOffset.z += arg1 * COSS(arg0->rotation.y - 0x4000) * gParticleRenderContext.scale.y;
}

/**
 * Adds the vector of length arg1 along the particle's Y rotation, times the global
 * particle scale, to the position offset.
 * @unverified Name guessed from the code.
 */
void Particle_AddVelocityFromDirVector(Particle* arg0, f32 arg1) {
    Vec3f sp1C;

    Particle_ComputeVectorFromRotationY(arg0, arg1, &sp1C);
    arg0->positionOffset.x += sp1C.x * gParticleRenderContext.scale.y;
    arg0->positionOffset.y += sp1C.y * gParticleRenderContext.scale.y;
    arg0->positionOffset.z += sp1C.z * gParticleRenderContext.scale.y;
}

/**
 * Set the base position offset using Particle_ComputeVectorFromRotationXYZAlt and context scaling.
 * Seen in play (2026-11-12) in move animations (30-move sweep): it changed positionOffset
 * (0x34-0x3C) of the live particle, e.g. 0 -> 4.142.
 */
void Particle_SetPositionFromRotationTemplate1(Particle* arg0, f32 arg1) {
    Vec3f sp1C;

    Particle_ComputeVectorFromRotationXYZAlt(arg0, arg1, &sp1C);
    Particle_Field38_SetVecFromVec3fScaled_08C20(arg0, sp1C);
}

/**
 * Set the base position offset using Particle_ComputeVectorFromRotationYZVariant and context scaling.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void Particle_SetPositionFromRotationTemplate2(Particle* arg0, f32 arg1) {
    Vec3f sp1C;

    Particle_ComputeVectorFromRotationYZVariant(arg0, arg1, &sp1C);
    Particle_Field38_SetVecFromVec3fScaled_08C20(arg0, sp1C);
}

/**
 * Add Particle_ComputeVectorFromRotationXYZAlt's result to the base position offset with context scaling.
 * Seen in play (2026-11-12) in move animations (30-move sweep): it changed positionOffset
 * (0x34-0x3C) of the live particle, e.g. 0 -> -0.74.
 */
void Particle_AddPositionFromRotationTemplate1(Particle* arg0, f32 arg1) {
    Vec3f sp1C;

    Particle_ComputeVectorFromRotationXYZAlt(arg0, arg1, &sp1C);
    Particle_Field38_AddVecScaledFromVec3f_08D78(arg0, sp1C);
}

/**
 * Add Particle_ComputeVectorFromRotationYZVariant's result to the base position offset with context scaling.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void Particle_AddPositionFromRotationTemplate2(Particle* arg0, f32 arg1) {
    Vec3f sp1C;

    Particle_ComputeVectorFromRotationYZVariant(arg0, arg1, &sp1C);
    Particle_Field38_AddVecScaledFromVec3f_08D78(arg0, sp1C);
}

/**
 * Rotates arg1 by the particle's rotation about Y and adds it, scaled, to the position
 * offset.
 * @unverified Name guessed from the code.
 */
void Particle_AddPositionRotatedVectorByYaw(Particle* arg0, Vec3f arg1) {
    Vec3f sp24;

    ParticleMath_RotateVec3fY(&sp24, arg1, arg0->rotation);
    Particle_Field38_AddVecScaledFromVec3f_08D78(arg0, sp24);
}

s32 func_82137DF4(M2C_UNK);                         /* extern */
extern f32 D_FLT_8219A824;

/**
 * Sets the particle's positionOffset.x to a random value from func_82137DF4(arg1) times the particle scale D_FLT_8219A824.
 * Seen in play (2026-11-12) in move animations (30-move sweep): it changed positionOffset.x
 * (0x34) of the live particle, e.g. 0 -> 47.52.
 */
void Particle_SetPosOffsetXRandomScaled(s8 *arg0, M2C_UNK arg1) {
    M2C_FIELD(arg0, f32 *, 0x34) = (f32) ((f32) func_82137DF4(arg1) * D_FLT_8219A824);
}

s32 func_82137DF4(M2C_UNK);                         /* extern */
extern f32 D_FLT_8219A824;

/**
 * Sets the particle's positionOffset.y to a random value from func_82137DF4(arg1) times the particle scale D_FLT_8219A824.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name and comment guessed from the code.
 */
void Particle_SetPosOffsetYRandomScaled(s8 *arg0, M2C_UNK arg1) {
    M2C_FIELD(arg0, f32 *, 0x38) = (f32) ((f32) func_82137DF4(arg1) * D_FLT_8219A824);
}

s32 func_82137DF4(M2C_UNK);                         /* extern */
extern f32 D_FLT_8219A824;

/**
 * Sets the particle's positionOffset.z to a random value from func_82137DF4(arg1) times the particle scale D_FLT_8219A824.
 * Seen in play (2026-11-12) in move animations (30-move sweep): it changed positionOffset.z
 * (0x3C) of the live particle, e.g. 0 -> 44.
 */
void Particle_SetPosOffsetZRandomScaled(s8 *arg0, M2C_UNK arg1) {
    M2C_FIELD(arg0, f32 *, 0x3C) = (f32) ((f32) func_82137DF4(arg1) * D_FLT_8219A824);
}

s32 func_82137DF4(M2C_UNK);                         /* extern */
extern f32 D_FLT_8219A824;

/**
 * Sets the particle's positionOffset.x to a random value from func_82137DF4(arg1) times the particle scale D_FLT_8219A824, plus arg2.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name and comment guessed from the code.
 */
void Particle_SetPosOffsetXRandomScaledPlus(s8 *arg0, M2C_UNK arg1, s32 arg2) {
    M2C_FIELD(arg0, f32 *, 0x34) = (f32) (((f32) func_82137DF4(arg1) * D_FLT_8219A824) + (f32) arg2);
}

s32 func_82137DF4(M2C_UNK);                         /* extern */
extern f32 D_FLT_8219A824;

/**
 * Sets the particle's positionOffset.y to a random value from func_82137DF4(arg1) times the particle scale D_FLT_8219A824, plus arg2.
 * Seen in play (2026-11-12) in move animations (30-move sweep): it changed positionOffset.y
 * (0x38) of the live particle, e.g. 0 -> 1.2.
 */
void Particle_SetPosOffsetYRandomScaledPlus(s8 *arg0, M2C_UNK arg1, s32 arg2) {
    M2C_FIELD(arg0, f32 *, 0x38) = (f32) (((f32) func_82137DF4(arg1) * D_FLT_8219A824) + (f32) arg2);
}

s32 func_82137DF4(M2C_UNK);                         /* extern */
extern f32 D_FLT_8219A824;

/**
 * Sets the particle's positionOffset.z to a random value from func_82137DF4(arg1) times the particle scale D_FLT_8219A824, plus arg2.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name and comment guessed from the code.
 */
void Particle_SetPosOffsetZRandomScaledPlus(s8 *arg0, M2C_UNK arg1, s32 arg2) {
    M2C_FIELD(arg0, f32 *, 0x3C) = (f32) (((f32) func_82137DF4(arg1) * D_FLT_8219A824) + (f32) arg2);
}

s32 func_82137DF4(M2C_UNK);                         /* extern */
extern f32 D_FLT_8219A824;

/**
 * Sets positionOffset.x to the random value from func_82137DF4 pushed `arg2` units away from zero, times D_FLT_8219A824.
 * Seen in play (2026-11-12) in move animations (30-move sweep): it changed positionOffset.x
 * (0x34) of the live particle, e.g. 0 -> 44.
 */
void Particle_SetRandomPositionOffsetXWithGap(s8 *arg0, M2C_UNK arg1, s32 arg2) {
    f32 temp_f0;

    temp_f0 = (f32) func_82137DF4(arg1);
    if (temp_f0 >= 0.0f) {
        M2C_FIELD(arg0, f32 *, 0x34) = (f32) (((f32) arg2 + temp_f0) * D_FLT_8219A824);
        return;
    }
    M2C_FIELD(arg0, f32 *, 0x34) = (f32) ((temp_f0 - (f32) arg2) * D_FLT_8219A824);
}

s32 func_82137DF4(M2C_UNK);                         /* extern */
extern f32 D_FLT_8219A824;

/**
 * Y version of Particle_SetRandomPositionOffsetXWithGap.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name and comment guessed from the code.
 */
void Particle_SetRandomPositionOffsetYWithGap(s8 *arg0, M2C_UNK arg1, s32 arg2) {
    f32 temp_f0;

    temp_f0 = (f32) func_82137DF4(arg1);
    if (temp_f0 >= 0.0f) {
        M2C_FIELD(arg0, f32 *, 0x38) = (f32) (((f32) arg2 + temp_f0) * D_FLT_8219A824);
        return;
    }
    M2C_FIELD(arg0, f32 *, 0x38) = (f32) ((temp_f0 - (f32) arg2) * D_FLT_8219A824);
}

s32 func_82137DF4(M2C_UNK);                         /* extern */
extern f32 D_FLT_8219A824;

/**
 * Z version of Particle_SetRandomPositionOffsetXWithGap.
 * Seen in play (2026-11-12) in move animations (30-move sweep): it changed positionOffset.z
 * (0x3C) of the live particle, e.g. 0 -> -51.04.
 */
void Particle_SetRandomPositionOffsetZWithGap(s8 *arg0, M2C_UNK arg1, s32 arg2) {
    f32 temp_f0;

    temp_f0 = (f32) func_82137DF4(arg1);
    if (temp_f0 >= 0.0f) {
        M2C_FIELD(arg0, f32 *, 0x3C) = (f32) (((f32) arg2 + temp_f0) * D_FLT_8219A824);
        return;
    }
    M2C_FIELD(arg0, f32 *, 0x3C) = (f32) ((temp_f0 - (f32) arg2) * D_FLT_8219A824);
}

/**
 * Sets the position offset to a random vector with components in +-arg1, +-arg2 and
 * +-arg3, times the global particle scale.
 * @unverified Name guessed from the code.
 */
void Particle_SetRandomVelocityXYZ(Particle* arg0, s32 arg1, s32 arg2, s32 arg3) {
    Vec3f sp18;

    sp18.x = ParticleMath_RandomSigned(arg1);
    sp18.y = ParticleMath_RandomSigned(arg2);
    sp18.z = ParticleMath_RandomSigned(arg3);

    arg0->positionOffset.x = sp18.x * gParticleRenderContext.scale.y;
    arg0->positionOffset.y = sp18.y * gParticleRenderContext.scale.y;
    arg0->positionOffset.z = sp18.z * gParticleRenderContext.scale.y;
}

/**
 * Sets positionOffset to random values in +-`arg1`/`arg2`/`arg3`, times the render scale.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name and comment guessed from the code.
 */
void Particle_SetRandomPositionOffsetXYZ(Particle* arg0, s32 arg1, s32 arg2, s32 arg3) {
    Vec3f sp1C;

    sp1C.x = ParticleMath_RandomRange(arg1);
    sp1C.y = ParticleMath_RandomRange(arg2);
    sp1C.z = ParticleMath_RandomRange(arg3);

    arg0->positionOffset.x = sp1C.x * gParticleRenderContext.scale.y;
    arg0->positionOffset.y = sp1C.y * gParticleRenderContext.scale.y;
    arg0->positionOffset.z = sp1C.z * gParticleRenderContext.scale.y;
}

/**
 * Sets the position offset to a random XY vector (+-arg1, +-arg2) rotated by the
 * particle's Y rotation, times the global particle scale.
 * @unverified Name guessed from the code.
 */
void Particle_SetRandomRotatedVelocityXY(Particle* arg0, s32 arg1, s32 arg2) {
    Vec3f sp2C;
    Vec3f sp20;

    sp2C.x = ParticleMath_RandomSigned(arg1);
    sp2C.y = ParticleMath_RandomSigned(arg2);
    sp2C.z = 0.0f;

    ParticleMath_RotateVec3fY(&sp20, sp2C, arg0->rotation);

    arg0->positionOffset.x = sp20.x * gParticleRenderContext.scale.y;
    arg0->positionOffset.y = sp20.y * gParticleRenderContext.scale.y;
    arg0->positionOffset.z = sp20.z * gParticleRenderContext.scale.y;
}

/**
 * Add independent signed random components to the base position offset with render-context scaling.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name and comment from Stadium 1, matched by code similarity.
 */
void Particle_AddRandomPositionOffsetXYZ(Particle* arg0, s32 arg1, s32 arg2, s32 arg3) {
    Vec3f sp24;

    sp24.x = ParticleMath_RandomSigned(arg1);
    sp24.y = ParticleMath_RandomSigned(arg2);
    sp24.z = ParticleMath_RandomSigned(arg3);

    arg0->positionOffset.x += sp24.x * gParticleRenderContext.scale.y;
    arg0->positionOffset.y += sp24.y * gParticleRenderContext.scale.y;
    arg0->positionOffset.z += sp24.z * gParticleRenderContext.scale.y;
}

/**
 * Sets origin (unscaled).
 */
void Particle_SetOrigin(Particle* arg0, f32 arg1, f32 arg2, f32 arg3) {
    arg0->origin.x = arg1;
    arg0->origin.y = arg2;
    arg0->origin.z = arg3;
}

/**
 * Sets motionOffset (0x4C, the displacement Particle_ApplyMotionStep accumulates) to the scaled (x, y, z). Was
 * Particle_SetVelocity: in play (2026-11-12, move animations) Particle_ApplyMotionStep added motionStep (0x78)
 * into this field each frame, so this is a position offset, not a velocity.
 */
void Particle_SetMotionOffset(Particle* arg0, f32 arg1, f32 arg2, f32 arg3) {
    M2C_FIELD(arg0, f32*, 0x4C) = arg1 * gParticleRenderContext.scale.y;
    M2C_FIELD(arg0, f32*, 0x4C + 4) = arg2 * gParticleRenderContext.scale.y;
    M2C_FIELD(arg0, f32*, 0x4C + 8) = arg3 * gParticleRenderContext.scale.y;
}

extern f32 D_FLT_8219A824;

/**
 * Sets the particle's motionOffset.x to arg1 times the particle scale D_FLT_8219A824.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name and comment guessed from the code.
 */
void Particle_SetMotionOffsetXScaled(s8 *arg0, f32 arg1) {
    M2C_FIELD(arg0, f32 *, 0x4C) = (f32) (arg1 * D_FLT_8219A824);
}

/**
 * Seen in play (2026-11-13) in the move sweep (Solar Beam): with arg1 = 76.0 it set motionOffset.y
 * (0x50) to 273.6, arg1 times the 3.6 render scale; x and z were untouched.
 */
void Particle_SetMotionOffsetYScaled(Particle* arg0, f32 arg1) {
    arg0->motionOffset.y = arg1 * gParticleRenderContext.scale.y;
}

/**
 * Sets motionOffset.z to arg1 times the global particle scale.
 * @unverified Name guessed from the code.
 */
void Particle_SetMotionOffsetZScaled(Particle* arg0, f32 arg1) {
    arg0->motionOffset.z = arg1 * gParticleRenderContext.scale.y;
}

/**
 * Sets motionOffset to a random direction of length arg1 times the global particle
 * scale.
 * @unverified Name guessed from the code.
 */
void Particle_SetVelocityRandomDirection(Particle* arg0, f32 arg1) {
    ParticleMath_RandomDirection(&arg0->motionOffset, arg1 * gParticleRenderContext.scale.y);
}

/**
 * Adds the vector, times the render scale, to motionOffset.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name and comment guessed from the code.
 */
void Particle_AddMotionOffsetScaled(Particle* arg0, f32 arg1, f32 arg2, f32 arg3) {
    M2C_FIELD(arg0, f32*, 0x4C) += arg1 * gParticleRenderContext.scale.y;
    M2C_FIELD(arg0, f32*, 0x50) += arg2 * gParticleRenderContext.scale.y;
    M2C_FIELD(arg0, f32*, 0x54) += arg3 * gParticleRenderContext.scale.y;
}

extern f32 D_FLT_8219A824;

/**
 * Adds arg1 times the particle scale D_FLT_8219A824 to the particle's motionOffset.x.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name and comment guessed from the code.
 */
void Particle_AddMotionOffsetXScaled(s8 *arg0, f32 arg1) {
    M2C_FIELD(arg0, f32 *, 0x4C) = (f32) (M2C_FIELD(arg0, f32 *, 0x4C) + (arg1 * D_FLT_8219A824));
}

/**
 * Adds arg1 times the global particle scale to motionOffset.y.
 * @unverified Name guessed from the code.
 */
void Particle_AddMotionOffsetYScaled(Particle* arg0, f32 arg1) {
    arg0->motionOffset.y += arg1 * gParticleRenderContext.scale.y;
}

/**
 * Adds arg1 times the global particle scale to motionOffset.z.
 * @unverified Name guessed from the code.
 */
void Particle_AddMotionOffsetZScaled(Particle* arg0, f32 arg1) {
    arg0->motionOffset.z += arg1 * gParticleRenderContext.scale.y;
}

/**
 * Subtracts (arg1, arg2, arg3) times the global particle scale from motionOffset.
 * @unverified Name guessed from the code.
 */
void Particle_SubMotionOffsetScaled(Particle* arg0, f32 arg1, f32 arg2, f32 arg3) {
    arg0->motionOffset.x -= arg1 * gParticleRenderContext.scale.y;
    arg0->motionOffset.y -= arg2 * gParticleRenderContext.scale.y;
    arg0->motionOffset.z -= arg3 * gParticleRenderContext.scale.y;
}

extern f32 D_FLT_8219A824;

/**
 * Subtracts arg1 times the particle scale D_FLT_8219A824 from the particle's motionOffset.x.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name and comment guessed from the code.
 */
void Particle_SubMotionOffsetXScaled(s8 *arg0, f32 arg1) {
    M2C_FIELD(arg0, f32 *, 0x4C) = (f32) (M2C_FIELD(arg0, f32 *, 0x4C) - (arg1 * D_FLT_8219A824));
}

/**
 * Subtracts arg1 times the global particle scale from motionOffset.y.
 * @unverified Name guessed from the code.
 */
void Particle_SubMotionOffsetYScaled(Particle* arg0, f32 arg1) {
    arg0->motionOffset.y -= arg1 * gParticleRenderContext.scale.y;
}

/**
 * Subtracts arg1 times the global particle scale from motionOffset.z.
 * @unverified Name guessed from the code.
 */
void Particle_SubMotionOffsetZScaled(Particle* arg0, f32 arg1) {
    arg0->motionOffset.z -= arg1 * gParticleRenderContext.scale.y;
}

/**
 * Moves motionOffset.x toward `arg1` (times the render scale) with ParticleMath_ApproachFloat.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name and comment guessed from the code.
 */
s32 Particle_ApproachMotionOffsetX(Particle* arg0, f32 arg1) {
    return ParticleMath_ApproachFloat(&arg0->motionOffset.x, arg1 * gParticleRenderContext.scale.y, arg0->motionTarget.x);
}

/**
 * Seen in play (2026-11-13) in the move sweep (Solar Beam): with arg1 = 0 it moved motionOffset.y
 * (0x50) from 273.6 to 266.4 and then 259.2, steps of motionTarget.y (7.2).
 */
s32 Particle_ApproachMotionOffsetY(Particle* arg0, f32 arg1) {
    return ParticleMath_ApproachFloat(&arg0->motionOffset.y, arg1 * gParticleRenderContext.scale.y, arg0->motionTarget.y);
}

/**
 * Steps motionOffset.z toward arg1 (scaled) by motionTarget.z. Returns nonzero once it
 * arrives.
 * @unverified Name guessed from the code.
 */
s32 Particle_ApproachMotionOffsetZ(Particle* arg0, f32 arg1) {
    return ParticleMath_ApproachFloat(&arg0->motionOffset.z, arg1 * gParticleRenderContext.scale.y, arg0->motionTarget.z);
}

/**
 * Sets motionOffset to motionStep.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name and comment guessed from the code.
 */
void Particle_CopyMotionStepToOffset(s8 *arg0) {
    M2C_FIELD(arg0, f32 *, 0x4C) = (f32) M2C_FIELD(arg0, f32 *, 0x78);
    M2C_FIELD(arg0, f32 *, 0x50) = (f32) M2C_FIELD(arg0, f32 *, 0x7C);
    M2C_FIELD(arg0, f32 *, 0x54) = (f32) M2C_FIELD(arg0, f32 *, 0x80);
}

/**
 * Sets motionOffset.x and .z to motionStep.
 */
void Particle_CopyMotionStepToOffsetXZ(s8 *arg0) {
    M2C_FIELD(arg0, f32 *, 0x4C) = (f32) M2C_FIELD(arg0, f32 *, 0x78);
    M2C_FIELD(arg0, f32 *, 0x54) = (f32) M2C_FIELD(arg0, f32 *, 0x80);
}

/**
 * Sets motionOffset.x and .y to motionStep.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name and comment guessed from the code.
 */
void Particle_CopyMotionStepToOffsetXY(s8 *arg0) {
    M2C_FIELD(arg0, f32 *, 0x4C) = (f32) M2C_FIELD(arg0, f32 *, 0x78);
    M2C_FIELD(arg0, f32 *, 0x50) = (f32) M2C_FIELD(arg0, f32 *, 0x7C);
}

/**
 * Adds motionStep to motionOffset.
 * Seen in play (2026-11-12) in move animations (30-move sweep): it changed motionOffset
 * (0x4C-0x54) of the live particle, e.g. 0 -> 3.55.
 */
M2C_UNK Particle_ApplyMotionStep(s32 arg0) {
    ((Particle*)arg0)->motionOffset.x += ((Particle*)arg0)->motionStep.x;
    ((Particle*)arg0)->motionOffset.y += ((Particle*)arg0)->motionStep.y;
    ((Particle*)arg0)->motionOffset.z += ((Particle*)arg0)->motionStep.z;
}

/**
 * Seen in play (2026-11-13) in the 165-move sweep (Mega Kick, Thunder Punch): it added motionStep.x
 * and .z (0x78, 0x80) to motionOffset.x and .z (0x4C, 0x54); y was untouched.
 */
void Particle_ApplyMotionStepXZ(Particle* arg0) {
    M2C_FIELD(arg0, f32*, 0x4C) += M2C_FIELD(arg0, f32*, 0x78);
    M2C_FIELD(arg0, f32*, 0x54) += M2C_FIELD(arg0, f32*, 0x80);
}

/**
 * Adds motionStep.x and .y to motionOffset.x and .y.
 * No caller in play (2026-11-13): nothing that runs reaches it, not even through callbacks, data
 * tables or fragment headers.
 * @unverified Named from the code; not reached in the sweep.
 */
void Particle_ApplyMotionStepXY(Particle* arg0) {
    arg0->motionOffset.x += arg0->motionStep.x;
    arg0->motionOffset.y += arg0->motionStep.y;
}

void func_8213E474(s8 *arg0)
{
  *((f32 *) (((s8 *) arg0) + 0x4C)) = (f32) ((*((f32 *) (((s8 *) arg0) + 0x78))) + (*((f32 *) (((s8 *) arg0) + 0x4C)))); // FAKE: decomp slop, raw pointer casts stand in for struct fields
}

/**
 * Adds motionStep.y to motionOffset.y.
 * @unverified Name guessed from the code.
 */
void Particle_ApplyMotionStepY(Particle* arg0) {
    arg0->motionOffset.y += arg0->motionStep.y;
}

/**
 * Adds motionStep.z to motionOffset.z.
 * @unverified Name guessed from the code.
 */
void Particle_ApplyMotionStepZ(Particle* arg0) {
    arg0->motionOffset.z += arg0->motionStep.z;
}

/**
 * Sets motionStep.x and .z from stepMagnitude along rotation.y, then adds them to motionOffset.x
 * and .z. Same result as Particle_AddVelocityXZFromRotationY, built from the two helpers. Renamed
 * from Particle_AddVelocityXYFromRotationZViaImpulse: it reads rotation.y and writes x and z.
 * Evaluate the explicit trigonometric component formula and store/add the resulting motion term.
 * Seen in play (2026-11-13) in the 165-move sweep (Petal Dance): it changed motionOffset.x and .z
 * (0x4C, 0x54) only.
 */
void Particle_AddVelocityXZFromRotationYViaHelpers(Particle* arg0) {
    Particle_SetMotionStepXZFromRotationY(arg0);
    Particle_Field50_AddXYFromField7C_09C34(arg0);
}

M2C_UNK func_8213FB14();                            /* extern */

void func_8213E4D8(s32 arg0) {
    func_8213FB14();
    Particle_ApplyMotionStepXZ(arg0);
}

/**
 * Recomputes motionStep from the step magnitude and rotation angles, then adds it to
 * motionOffset.
 * @unverified Name guessed from the code.
 */
void Particle_AddVelocityFromRotationTemplate2(Particle* arg0) {
    Particle_SetMotionStepFromRotationXZ(arg0);
    Particle_ApplyMotionStepXY(arg0);
}

M2C_UNK Particle_ApplyMotionStep(s32);                         /* extern */
M2C_UNK func_8213FB50();                            /* extern */

void Particle_AddVelocityFromRotationTemplate1(s32 arg0) {
    func_8213FB50();
    Particle_ApplyMotionStep(arg0);
}

M2C_UNK Particle_ApplyMotionStep(s32);                         /* extern */

void Particle_MotionStep_SetVecFromField74AnglesXZ(Particle* arg0);

void func_8213E550(s32 arg0) {
    Particle_MotionStep_SetVecFromField74AnglesXZ((Particle*)arg0);
    Particle_ApplyMotionStep(arg0);
}

M2C_UNK Particle_ApplyMotionStep(s32);                         /* extern */
M2C_UNK func_8213FC48();                            /* extern */

void func_8213E578(s32 arg0) {
    func_8213FC48();
    Particle_ApplyMotionStep(arg0);
}

M2C_UNK Particle_ApplyMotionStep(s32);                         /* extern */
M2C_UNK func_8213FCC8();                            /* extern */

void func_8213E5A0(s32 arg0) {
    func_8213FCC8();
    Particle_ApplyMotionStep(arg0);
}

M2C_UNK Particle_ApplyMotionStep(s32);                         /* extern */
M2C_UNK func_8213FE04();                            /* extern */

void func_8213E5C8(s32 arg0) {
    func_8213FE04();
    Particle_ApplyMotionStep(arg0);
}

M2C_UNK Particle_ApplyMotionStep(s32);                         /* extern */
M2C_UNK func_8213FD3C();                            /* extern */

void func_8213E5F0(s32 arg0) {
    func_8213FD3C();
    Particle_ApplyMotionStep(arg0);
}

M2C_UNK Particle_ApplyMotionStep(s32);                         /* extern */
M2C_UNK func_8213FED4();                            /* extern */

void func_8213E618(s32 arg0) {
    func_8213FED4();
    Particle_ApplyMotionStep(arg0);
}

M2C_UNK Particle_ApplyMotionStep(s32);                         /* extern */
M2C_UNK func_8213FED4();                            /* extern */

void func_8213E640(s32 arg0) {
    func_8213FED4();
    Particle_ApplyMotionStep(arg0);
}

/**
 * Sets motionStep.x and motionStep.z to the step magnitude along the particle's Y
 * rotation, then adds them to motionOffset.
 * @unverified Name guessed from the code.
 */
void Particle_AddVelocityXZFromRotationY(Particle* arg0) {
    arg0->motionStep.x = arg0->stepMagnitude * SINS(arg0->rotation.y);
    arg0->motionStep.z = arg0->stepMagnitude * COSS(arg0->rotation.y);

    Particle_ApplyMotionStepXZ(arg0);
}

/**
 * Evaluate the explicit trigonometric component formula and store/add the resulting motion term.
 * Seen in play (2026-11-13) in the 165-move sweep (Thunder Punch, Scratch): it set motionStep.x
 * (0x78) and added it to motionOffset.x (0x4C).
 */
void Particle_AddVelocityXZFromRotationYPlusHalfTurn(Particle* arg0) {
    arg0->motionStep.x = arg0->stepMagnitude * SINS(arg0->rotation.y + 0x8000);
    arg0->motionStep.z = arg0->stepMagnitude * COSS(arg0->rotation.y + 0x8000);

    Particle_ApplyMotionStepXZ(arg0);
}

/**
 * Evaluate the explicit trigonometric component formula and store/add the resulting motion term.
 * Seen in play (2026-11-13) in the 165-move sweep (Surf): with arg1 = 10 it set motionStep.x to 10
 * (z 0) and added it to motionOffset.x, i.e. the step pointed along rotation.y + 0x8000.
 */
void Particle_StepBackwardAlongRotationY(Particle* arg0, f32 arg1) {
    arg0->motionStep.x = SINS(arg0->rotation.y + 0x8000) * arg1;
    arg0->motionStep.z = COSS(arg0->rotation.y + 0x8000) * arg1;

    Particle_ApplyMotionStepXZ(arg0);
}

M2C_UNK func_8213E488();                            /* extern */

void func_8213E77C(s8 *arg0) {
    M2C_FIELD(arg0, f32 *, 0x7C) = (f32) M2C_FIELD(arg0, f32 *, 0x70);
    func_8213E488();
}

/**
 * Sets motionStep.y to -stepMagnitude, adds it to motionOffset.y and returns 1 once worldPosition.y
 * is at or below 0.
 * Apply the downward motion term and return whether the stored world-position Y is nonpositive.
 * Seen in play (2026-11-13) in the 165-move sweep (Vice Grip): it wrote motionStep.y (0x7C) and
 * changed motionOffset.y (0x50), returning 0 while the particle was above the floor.
 */
s32 Particle_FallAtStepMagnitude(Particle* arg0) {
    s32 sp1C = 0;

    arg0->motionStep.y = -arg0->stepMagnitude;
    func_8213E488(arg0);

    if (arg0->worldPosition.y <= 0.0f) {
        sp1C = 1;
    }
    return sp1C;
}


/**
 * Adds magnitudeStep to stepMagnitude, then falls like Particle_FallAtStepMagnitude; returns 1 once
 * worldPosition.y is at or below 0.
 * Apply the downward motion term and return whether the stored world-position Y is nonpositive.
 * Seen in play (2026-11-13) in the 165-move sweep (Vice Grip): it wrote motionStep.y (0x7C) and
 * returned 0 while the particle was above the floor.
 */
s32 Particle_AccelerateFall(Particle* arg0) {
    s32 sp1C = 0;

    arg0->stepMagnitude += arg0->magnitudeStep;
    arg0->motionStep.y = -arg0->stepMagnitude;

    func_8213E488(arg0);

    if (arg0->worldPosition.y <= 0.0f) {
        sp1C = 1;
    }
    return sp1C;
}

/**
 * Sets motionTarget to (arg1, arg2, arg3) times the global particle scale.
 * @unverified Name guessed from the code.
 */
void Particle_SetVelocityTarget(Particle* arg0, f32 arg1, f32 arg2, f32 arg3) {
    arg0->motionTarget.x = arg1 * gParticleRenderContext.scale.y;
    arg0->motionTarget.y = arg2 * gParticleRenderContext.scale.y;
    arg0->motionTarget.z = arg3 * gParticleRenderContext.scale.y;
}

/**
 * Sets motionTarget.x to arg1 times the global particle scale.
 * @unverified Name guessed from the code.
 */
void Particle_SetMotionTargetXScaled(Particle* arg0, f32 arg1) {
    arg0->motionTarget.x = arg1 * gParticleRenderContext.scale.y;
}

extern f32 D_FLT_8219A824;

/**
 * Sets the particle's motionTarget.y to arg1 times the particle scale D_FLT_8219A824.
 * Seen in play (2026-11-13) in the 165-move sweep (Petal Dance): with arg1 = 2.0 it wrote 7.2 (2.0
 * × scale 3.6) to motionTarget.y (0x5C).
 */
void Particle_SetMotionTargetYScaled(s8 *arg0, f32 arg1) {
    M2C_FIELD(arg0, f32 *, 0x5C) = (f32) (arg1 * D_FLT_8219A824);
}

extern f32 D_FLT_8219A824;

/**
 * Sets the particle's motionTarget.z to arg1 times the particle scale D_FLT_8219A824.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name and comment guessed from the code.
 */
void Particle_SetMotionTargetZScaled(s8 *arg0, f32 arg1) {
    M2C_FIELD(arg0, f32 *, 0x60) = (f32) (arg1 * D_FLT_8219A824);
}

/**
 * Steps motionTarget.y toward arg1 by arg2, both scaled. Returns nonzero once it arrives.
 * @unverified Name guessed from the code.
 */
s32 Particle_Field5C_ApproachY_0A0C4(Particle* arg0, f32 arg1, f32 arg2) {
    return ParticleMath_ApproachFloat(&arg0->motionTarget.y, arg1 * gParticleRenderContext.scale.y, arg2 * gParticleRenderContext.scale.y);
}

/**
 * Return 40 percent of the supplied difference for proportional position approach.
 * No caller in play (2026-11-13): nothing that runs reaches it, not even through callbacks, data
 * tables or fragment headers.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
f32 ParticleMath_ScaleApproachStep(f32 arg0) {
    return arg0 * 0.4f;
}

/**
 * Approach each base position-offset component by 40 percent of its difference when outside a +/-0.01 tolerance.
 * No caller in play (2026-11-13): nothing that runs reaches it, not even through callbacks, data
 * tables or fragment headers.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void Particle_ApproachPosition(Particle* arg0, Vec3f arg1) {
    f32 sp24;
    f32 sp20;
    f32 temp_fa0;

    temp_fa0 = arg1.x - arg0->positionOffset.x;
    sp20 = arg1.y - arg0->positionOffset.y;
    sp24 = arg1.z - arg0->positionOffset.z;

    if (!(temp_fa0 <= 0.01f) || !(temp_fa0 >= -0.01f)) {
        ParticleMath_ApproachFloat(&arg0->positionOffset.x, arg1.x, ParticleMath_ScaleApproachStep(temp_fa0));
    }

    if (!(sp20 <= 0.01f) || !(sp20 >= -0.01f)) {
        ParticleMath_ApproachFloat(&arg0->positionOffset.y, arg1.y, ParticleMath_ScaleApproachStep(sp20));
    }

    if (!(sp24 <= 0.01f) || !(sp24 >= -0.01f)) {
        ParticleMath_ApproachFloat(&arg0->positionOffset.z, arg1.z, ParticleMath_ScaleApproachStep(sp24));
    }
}

/**
 * Writes arg1 into the three s16 fields at offset 0x90 of the particle.
 * @unverified Name guessed from the code.
 */
void Particle_Field9A_SetVecFromVec3s_0A37C(Particle* arg0, Vec3s arg1) {
    M2C_FIELD(arg0, s16*, 0x90) = arg1.x;
    M2C_FIELD(arg0, s16*, 0x92) = arg1.y;
    M2C_FIELD(arg0, s16*, 0x94) = arg1.z;
}

/**
 * Sets rotation.
 */
void Particle_SetRotation(Particle* arg0, s16 arg1, s16 arg2, s16 arg3) {
    arg0->rotation.x = arg1;
    arg0->rotation.y = arg2;
    arg0->rotation.z = arg3;
}

/**
 * Sets the particle's rotation.x to arg1.
 * Seen in play (2026-11-12) in move animations (30-move sweep): it changed rotation.x (0x90) of
 * the live particle, e.g. 0x0 -> 0x76ef.
 */
void Particle_SetRotationX(s8 *arg0, s16 arg1) {
    M2C_FIELD(arg0, s16 *, 0x90) = arg1;
}

/**
 * Sets the particle's rotation.y to arg1.
 * Seen in play (2026-11-12) in move animations (30-move sweep): it changed rotation.y (0x92) of
 * the live particle, e.g. 0xc000 -> 0x1a98.
 */
void Particle_SetRotationY(s8 *arg0, s16 arg1) {
    M2C_FIELD(arg0, s16 *, 0x92) = arg1;
}

/**
 * Sets the particle's rotation.z to arg1.
 * Seen in play (2026-11-12) in move animations (30-move sweep): it changed rotation.z (0x94) of
 * the live particle, e.g. 0x0 -> 0xd4a3.
 */
void Particle_SetRotationZ(s8 *arg0, s16 arg1) {
    M2C_FIELD(arg0, s16 *, 0x94) = arg1;
}

/**
 * Adds a half turn (0x8000) to each rotation axis.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name and comment guessed from the code.
 */
void Particle_AddHalfTurnToRotation(s8 *arg0) {
    M2C_FIELD(arg0, s16 *, 0x90) = (s16) (M2C_FIELD(arg0, s16 *, 0x90) + 0x8000);
    M2C_FIELD(arg0, s16 *, 0x92) = (s16) (M2C_FIELD(arg0, s16 *, 0x92) + 0x8000);
    M2C_FIELD(arg0, s16 *, 0x94) = (s16) (M2C_FIELD(arg0, s16 *, 0x94) + 0x8000);
}

/**
 * Turns the particle's rotation.x by half a circle (+0x8000).
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name and comment guessed from the code.
 */
void Particle_FlipRotationX(s8 *arg0) {
    M2C_FIELD(arg0, s16 *, 0x90) = (s16) (M2C_FIELD(arg0, s16 *, 0x90) + 0x8000);
}

/**
 * Turns the particle's rotation.y by half a circle (+0x8000).
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name and comment guessed from the code.
 */
void Particle_FlipRotationY(s8 *arg0) {
    M2C_FIELD(arg0, s16 *, 0x92) = (s16) (M2C_FIELD(arg0, s16 *, 0x92) + 0x8000);
}

/**
 * Turns the particle's rotation.z by half a circle (+0x8000).
 * Seen in play (2026-11-13) in the 165-move sweep (Pin Missile): rotation.z (0x94) went from 0x18xx
 * to 0x98xx, a turn of 0x8000.
 */
void Particle_FlipRotationZ(s8 *arg0) {
    M2C_FIELD(arg0, s16 *, 0x94) = (s16) (M2C_FIELD(arg0, s16 *, 0x94) + 0x8000);
}

/**
 * Sets rotationStep.
 * Seen in play (2026-11-13) (tour of menus and a COM battle): ran in the battle opening, a switch
 * in battle and a Pound turn.
 * @unverified Name and comment guessed from the code.
 */
void Particle_SetRotationStep(s8 *arg0, s16 arg1, s16 arg2, s16 arg3) {
    M2C_FIELD(arg0, s16 *, 0x96) = arg1;
    M2C_FIELD(arg0, s16 *, 0x98) = arg2;
    M2C_FIELD(arg0, s16 *, 0x9A) = arg3;
}

/**
 * Sets rotationStep from a Vec3s passed by value.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name and comment guessed from the code.
 */
void Particle_SetRotationStepVec(Particle* arg0, Vec3s arg1) {
    arg0->rotationStep.x = arg1.x;
    arg0->rotationStep.y = arg1.y;
    arg0->rotationStep.z = arg1.z;
}

/**
 * Sets rotationStep.x and .y.
 * Seen in play (2026-11-13) in the 165-move sweep (Fire Punch, Ember, Bubblebeam, Selfdestruct, Egg
 * Bomb): with (0x800, 0x300) it set rotationStep.x (0x96) to 0x800 and rotationStep.y (0x98) to
 * 0x300; z was untouched.
 */
void Particle_SetRotationStepXY(s8 *arg0, s16 arg1, s16 arg2) {
    M2C_FIELD(arg0, s16 *, 0x96) = arg1;
    M2C_FIELD(arg0, s16 *, 0x98) = arg2;
}

/**
 * Sets the particle's rotationStep.x to arg1.
 * Seen in play (2026-11-12) in move animations (30-move sweep): it changed rotationStep.x (0x96)
 * of the live particle, e.g. 0x0 -> 0x1000.
 */
void Particle_SetRotationStepX(s8 *arg0, s16 arg1) {
    M2C_FIELD(arg0, s16 *, 0x96) = arg1;
}

/**
 * Sets the particle's rotationStep.y to arg1.
 * Seen in play (2026-11-12) in move animations (30-move sweep): it changed rotationStep.y (0x98)
 * of the live particle, e.g. 0x0 -> 0x44ac.
 */
void Particle_SetRotationStepY(s8 *arg0, s16 arg1) {
    M2C_FIELD(arg0, s16 *, 0x98) = arg1;
}

/**
 * Sets the particle's rotationStep.z to arg1.
 * Seen in play (2026-11-12) in move animations (30-move sweep): it changed rotationStep.z (0x9A)
 * of the live particle, e.g. 0x0 -> 0x995.
 */
void Particle_SetRotationStepZ(s8 *arg0, s16 arg1) {
    M2C_FIELD(arg0, s16 *, 0x9A) = arg1;
}

/**
 * Sets the particle's rotationTarget.x to arg1.
 * Seen in play (2026-11-12) in move animations (30-move sweep): it changed rotationTarget.x
 * (0x9C) of the live particle, e.g. 0x0 -> 0xc000.
 */
void Particle_SetRotationTargetX(s8 *arg0, s16 arg1) {
    M2C_FIELD(arg0, s16 *, 0x9C) = arg1;
}

/**
 * Sets the particle's rotationTarget.y to arg1.
 * Seen in play (2026-11-12) in move animations (30-move sweep): it changed rotationTarget.y
 * (0x9E) of the live particle, e.g. 0x0 -> 0x4000.
 */
void Particle_SetRotationTargetY(s8 *arg0, s16 arg1) {
    M2C_FIELD(arg0, s16 *, 0x9E) = arg1;
}

/**
 * Set the X/Y rotation targets, leaving Z unchanged.
 * Seen in play (2026-11-12) in move animations (30-move sweep): it changed rotationTarget
 * (0x9C/0x9E) of the live particle, e.g. 0x0 -> 0x4000.
 */
void Particle_SetRotationTargetXY(Particle* arg0, s16 arg1, s16 arg2) {
    Particle_FieldA0_SetX_0A400(arg0, arg1);
    Particle_FieldA0_SetY_0A414(arg0, arg2);
}

/**
 * Copies rotation into rotationTarget.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name and comment guessed from the code.
 */
void Particle_SetRotationTargetToRotation(s8 *arg0) {
    M2C_FIELD(arg0, s16 *, 0x9C) = (s16) M2C_FIELD(arg0, s16 *, 0x90);
    M2C_FIELD(arg0, s16 *, 0x9E) = (s16) M2C_FIELD(arg0, s16 *, 0x92);
    M2C_FIELD(arg0, s16 *, 0xA0) = (s16) M2C_FIELD(arg0, s16 *, 0x94);
}

/**
 * Adds rotationStep to rotation.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name and comment guessed from the code.
 */
void Particle_ApplyRotationStep(Particle* arg0) {
    arg0->rotation.x += arg0->rotationStep.x;
    arg0->rotation.y += arg0->rotationStep.y;
    arg0->rotation.z += arg0->rotationStep.z;
}

/**
 * Adds rotationStep.x to rotation.x.
 * Seen in play (2026-11-12) in move animations (30-move sweep): it changed rotation.x (0x90) of
 * the live particle, e.g. 0xb01c -> 0xae15.
 */
void Particle_ApplyRotationStepX(s8 *arg0)
{
  s16 *new_var; // FAKE: permuter temp
  *((s16 *) (((0, (s8 *) arg0)) + 0x90)) = (s16) ((*(new_var = (s16 *) (((s8 *) arg0) + 0x96))) + (*((s16 *) (((s8 *) arg0) + 0x90)))); // FAKE: decomp slop, raw pointer casts stand in for struct fields
}

/**
 * Adds rotationStep.y to rotation.y.
 */
void Particle_ApplyRotationStepY(s8 *arg0)
{
  *((s16 *) (((s8 *) arg0) + 0x92)) = (s16) ((*((s16 *) (((s8 *) arg0) + 0x98))) + (*((s16 *) (((s8 *) arg0) + 0x92)))); // FAKE: decomp slop, raw pointer casts stand in for struct fields
 if (0) { }  // karodo
}

/**
 * Adds rotationStep.z to rotation.z.
 * @unverified Name guessed from the code.
 */
void Particle_Field94_AddXFromField9A_0A4B4(Particle* arg0) {
    arg0->rotation.z += arg0->rotationStep.z;
}

/**
 * Adds arg1 to the particle's rotation.
 * @unverified Name guessed from the code.
 */
void Particle_Field94_AddVecFromVec3s_0A4F0(Particle* arg0, Vec3s arg1) {
    arg0->rotation.x += arg1.x;
    arg0->rotation.y += arg1.y;
    arg0->rotation.z += arg1.z;
}

/**
 * Adds the three angles to rotation.
 */
void Particle_AddRotationXYZ(s8 *arg0, s16 arg1, s16 arg2, s16 arg3) {
    M2C_FIELD(arg0, s16 *, 0x90) = (s16) (M2C_FIELD(arg0, s16 *, 0x90) + arg1);
    M2C_FIELD(arg0, s16 *, 0x92) = (s16) (M2C_FIELD(arg0, s16 *, 0x92) + arg2);
    M2C_FIELD(arg0, s16 *, 0x94) = (s16) (M2C_FIELD(arg0, s16 *, 0x94) + arg3);
}

/**
 * Adds arg1 to the particle's rotation.x.
 * Seen in play (2026-11-12) in move animations (30-move sweep): it changed rotation.x (0x90) of
 * the live particle, e.g. 0x0 -> 0x1160.
 */
void Particle_AddRotationX(s8 *arg0, s16 arg1) {
    M2C_FIELD(arg0, s16 *, 0x90) = (s16) (M2C_FIELD(arg0, s16 *, 0x90) + arg1);
}

/**
 * Adds arg1 to the particle's rotation.y.
 * Seen in play (2026-11-12) in move animations (30-move sweep): it changed rotation.y (0x92) of
 * the live particle, e.g. 0x4000 -> 0x3f46.
 */
void Particle_AddRotationY(s8 *arg0, s16 arg1) {
    M2C_FIELD(arg0, s16 *, 0x92) = (s16) (M2C_FIELD(arg0, s16 *, 0x92) + arg1);
}

/**
 * Adds arg1 to the particle's rotation.z.
 * Seen in play (2026-11-12) in move animations (30-move sweep): it changed rotation.z (0x94) of
 * the live particle, e.g. 0x0 -> 0x2000.
 */
void Particle_AddRotationZ(s8 *arg0, s16 arg1) {
    M2C_FIELD(arg0, s16 *, 0x94) = (s16) (M2C_FIELD(arg0, s16 *, 0x94) + arg1);
}

void func_8213EDE8(s8 *arg0, s16 arg1, s16 arg2) {
    M2C_FIELD(arg0, s16 *, 0x9C) = (s16) (M2C_FIELD(arg0, s16 *, 0x9C) + arg1);
    M2C_FIELD(arg0, s16 *, 0x9E) = (s16) (M2C_FIELD(arg0, s16 *, 0x9E) + arg2);
}

/**
 * Subtracts arg1 from the particle's rotation.
 * @unverified Name guessed from the code.
 */
void Particle_Field94_SubVecFromVec3s_0A600(Particle* arg0, Vec3s arg1) {
    arg0->rotation.x -= arg1.x;
    arg0->rotation.y -= arg1.y;
    arg0->rotation.z -= arg1.z;
}

/**
 * Subtracts arg1 from the particle's rotation.x.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name and comment guessed from the code.
 */
void Particle_SubRotationX(s8 *arg0, s16 arg1) {
    M2C_FIELD(arg0, s16 *, 0x90) = (s16) (M2C_FIELD(arg0, s16 *, 0x90) - arg1);
}

/**
 * Subtracts arg1 from the particle's rotation.y.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name and comment guessed from the code.
 */
void Particle_SubRotationY(s8 *arg0, s16 arg1) {
    M2C_FIELD(arg0, s16 *, 0x92) = (s16) (M2C_FIELD(arg0, s16 *, 0x92) - arg1);
}

/**
 * Subtracts arg1 from rotation.z.
 * @unverified Name guessed from the code.
 */
void Particle_Field94_SubX_0A63C(Particle* arg0, s16 arg1) {
    arg0->rotation.z -= arg1;
}

M2C_UNK func_82137940(s8 *, s16, s16, s8 *);    /* extern */

/**
 * Steps the particle's rotation.x toward a target (helper of the approach family).
 * Seen in play (2026-11-12) in move animations (30-move sweep): it changed rotation.x (0x90) of
 * the live particle, e.g. 0xe02 -> 0xfe02.
 */
void Particle_ApproachRotationX(s8 *arg0) {
    func_82137940(arg0 + 0x90, M2C_FIELD(arg0, s16 *, 0x9C), M2C_FIELD(arg0, s16 *, 0x96), arg0);
}

M2C_UNK func_82137940(s8 *, s16, s16, s8 *);    /* extern */

/**
 * Steps the particle's rotation.y toward a target (helper of the approach family).
 * Seen in play (2026-11-12) in move animations (30-move sweep): it changed rotation.y (0x92) of
 * the live particle, e.g. 0xec64 -> 0xef64.
 */
void Particle_ApproachRotationY(s8 *arg0) {
    func_82137940(arg0 + 0x92, M2C_FIELD(arg0, s16 *, 0x9E), M2C_FIELD(arg0, s16 *, 0x98), arg0);
}

M2C_UNK func_82137940(s8 *, s16, s16, s8 *);    /* extern */

/**
 * Steps the particle's rotation.z toward a target (helper of the approach family).
 * No caller in play (2026-11-13): it is only called from Particle_ApproachRotationTargetXYZ, which
 * has no caller in the ROM itself.
 * @unverified Name and comment guessed from the code.
 */
void Particle_ApproachRotationZ(s8 *arg0) {
    func_82137940(arg0 + 0x94, M2C_FIELD(arg0, s16 *, 0xA0), M2C_FIELD(arg0, s16 *, 0x9A), arg0);
}

/**
 * Approach the selected rotation components using the stored or supplied target and step.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void Particle_ApproachRotationTargetXY(Particle* arg0) {
    Particle_ApproachRotationTargetX(arg0);
    Particle_ApproachRotationTargetY(arg0);
}

/**
 * Approach the selected rotation components using the stored or supplied target and step.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void Particle_ApproachRotationTargetXYZ(Particle* arg0) {
    Particle_ApproachRotationTargetX(arg0);
    Particle_ApproachRotationTargetY(arg0);
    Particle_ApproachRotationTargetZ(arg0);
}

/**
 * Approach rotation.x using the stored or supplied target and step.
 * Seen in play (2026-11-12) in move animations (30-move sweep): it changed rotation.x (0x90) of
 * the live particle, e.g. 0xd45 -> 0x1545.
 */
void Particle_ApproachRotationXTo(Particle* arg0, s16 arg1, s16 arg2) {
    ParticleMath_ApproachAngle(&arg0->rotation.x, arg1, arg2);
}

/**
 * Moves rotation.y toward `arg1` by `arg2` with ParticleMath_ApproachAngle.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name and comment guessed from the code.
 */
void Particle_ApproachRotationYAngle(Particle* arg0, s16 arg1, s16 arg2) {
    ParticleMath_ApproachAngle(&arg0->rotation.y, arg1, arg2);
}

/**
 * Lowers rotation.x by `arg2` toward `arg1`. Returns 1 when it reaches `arg1`.
 */
s32 Particle_DecreaseRotationXTo(Particle* arg0, s32 arg1, s32 arg2) {
    s32 var_v1 = 0;
    s32 var_v0 = arg0->rotation.x;

    if (arg1 < var_v0) {
        var_v0 -= arg2;
        if (arg1 >= var_v0) {
            var_v0 = arg1;
            var_v1 = 1;
        }
        arg0->rotation.x = var_v0;
    }

    return var_v1;
}

/**
 * Lowers rotation.y by `arg2` toward `arg1`. Returns 1 when it reaches `arg1`.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name and comment guessed from the code.
 */
s32 Particle_DecreaseRotationYTo(Particle* arg0, s32 arg1, s32 arg2) {
    s32 var_v1 = 0;
    s32 var_v0 = M2C_FIELD(arg0, s16*, 0x92);

    if (arg1 < var_v0) {
        var_v0 -= arg2;
        if (arg1 >= var_v0) {
            var_v0 = arg1;
            var_v1 = 1;
        }
        M2C_FIELD(arg0, s16*, 0x92) = var_v0;
    }

    return var_v1;
}

/**
 * Lowers rotation.z by arg2 until it reaches arg1. Returns 1 on the frame it gets there.
 * @unverified Name guessed from the code.
 */
s32 Particle_Field94_DecrementXTo_0A7DC(Particle* arg0, s32 arg1, s32 arg2) {
    s32 var_v1 = 0;
    s32 var_v0 = arg0->rotation.z;

    if (arg1 < var_v0) {
        var_v0 -= arg2;
        if (arg1 >= var_v0) {
            var_v0 = arg1;
            var_v1 = 1;
        }
        arg0->rotation.z = var_v0;
    }

    return var_v1;
}

/**
 * Add the indicated random binary-angle offsets, including any fixed half/quarter turn.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void Particle_AddRotationRandomSignedXY(Particle* arg0, s32 arg1, s32 arg2) {
    Particle_Field94_AddX_0A578(arg0, ParticleMath_RandomSigned(arg1));
    Particle_Field94_AddY_0A594(arg0, ParticleMath_RandomSigned(arg2));
}

/**
 * Add the indicated random binary-angle offsets, including any fixed half/quarter turn.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void Particle_AddRotationRandomSignedXYWithXHalfTurn(Particle* arg0, s32 arg1, s32 arg2) {
    Particle_Field94_AddX_0A578(arg0, ParticleMath_RandomSignedOffset(arg1, 0x8000));
    Particle_Field94_AddY_0A594(arg0, ParticleMath_RandomSigned(arg2));
}

/**
 * Add the indicated random binary-angle offsets, including any fixed half/quarter turn.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void Particle_AddRotationRandomSignedY(Particle* arg0, s32 arg1) {
    Particle_Field94_AddY_0A594(arg0, ParticleMath_RandomSigned(arg1));
}

/**
 * Add the indicated random binary-angle offsets, including any fixed half/quarter turn.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void Particle_AddRotationRandomSignedYWithHalfTurn(Particle* arg0, s32 arg1) {
    Particle_Field94_AddY_0A594(arg0, ParticleMath_RandomSignedOffset(arg1, 0x8000));
}

/**
 * Add the indicated random binary-angle offsets, including any fixed half/quarter turn.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void Particle_AddRotationRandomSignedXWithFixedYQuarterTurn(Particle* arg0) {
    Particle_Field94_AddX_0A578(arg0, ParticleMath_RandomSigned(0x10000));
    Particle_Field94_AddY_0A594(arg0, 0x4000);
}

extern struct ActivePokemon* D_8219A818;

/**
 * Returns the Y angle from the particle's origin to the default anchor of the Pokémon in
 * D_8219A818, plus the particle's own Y rotation.
 * @unverified Name from Stadium 1.
 */
s16 BattleAnim_GetParticleAngleYToTertiaryOwner(Particle* arg0) {
    Vec3f sp24;
    s16 ret;

    BattleAnim_GetOwnerDefaultAnchorPosition(D_8219A818, &sp24);
    ret = ParticleMath_AngleYBetweenPoints(arg0->origin, sp24) + arg0->rotation.y;
    return ret;
}

/**
 * Write a direction vector using the indicated rotation components and the supplied magnitude.
 * Seen in play (2026-11-13) (unattended Free Battle in which every Pokémon knows only Metronome, 70
 * turns): ran.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void Particle_ComputeVectorFromRotationY(Particle* arg0, f32 arg1, Vec3f* arg2) {
    arg2->x = SINS(arg0->rotation.y) * arg1;
    arg2->y = 0.0f;
    arg2->z = COSS(arg0->rotation.y) * arg1;
}

/**
 * Write a direction vector using the indicated rotation components and the supplied magnitude.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void Particle_ComputeVectorFromRotationXY(Particle* arg0, f32 arg1, Vec3f* arg2) {
    arg2->x = arg1 * COSS(arg0->rotation.x) * SINS(arg0->rotation.y);
    arg2->y = -arg1 * SINS(arg0->rotation.x);
    arg2->z = arg1 * COSS(arg0->rotation.x) * COSS(arg0->rotation.y);
}

/**
 * Write a direction vector using the indicated rotation components and the supplied magnitude.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void Particle_ComputeVectorFromRotationXZ(Particle* arg0, f32 arg1, Vec3f* arg2) {
    arg2->x = arg1 * SINS(arg0->rotation.x) * SINS(arg0->rotation.z);
    arg2->y = -arg1 * SINS(arg0->rotation.x) * COSS(arg0->rotation.z);
    arg2->z = arg1 * COSS(arg0->rotation.x);
}

/**
 * Write a direction vector using the indicated rotation components and the supplied magnitude.
 * Seen in play (2026-11-13) (tour of menus and a COM battle): ran in the battle opening and a
 * switch in battle.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void Particle_ComputeVectorFromRotationXYZAlt(Particle* arg0, f32 arg1, Vec3f* arg2) {
    arg2->x = arg1 * (SINS(arg0->rotation.x) * COSS(arg0->rotation.y) * SINS(arg0->rotation.z) +
                      COSS(arg0->rotation.x) * SINS(arg0->rotation.y));
    arg2->y = -arg1 * SINS(arg0->rotation.x) * COSS(arg0->rotation.z);
    arg2->z = arg1 * (COSS(arg0->rotation.x) * COSS(arg0->rotation.y) -
                      SINS(arg0->rotation.x) * SINS(arg0->rotation.y) * SINS(arg0->rotation.z));
}

/**
 * Write a direction vector using the indicated rotation components and the supplied magnitude.
 * No caller in play (2026-11-13): it is only called from Particle_AddPositionFromRotationTemplate2
 * and Particle_SetPositionFromRotationTemplate2, which have no caller in the ROM themselves.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void Particle_ComputeVectorFromRotationYZVariant(Particle* arg0, f32 arg1, Vec3f* arg2) {
    arg2->x = arg1 * (SINS(arg0->rotation.y) * COSS(arg0->rotation.z) +
                      SINS(arg0->rotation.x) * COSS(arg0->rotation.y) * SINS(arg0->rotation.z));
    arg2->y = arg1 * (SINS(arg0->rotation.y) * SINS(arg0->rotation.z) -
                      SINS(arg0->rotation.x) * COSS(arg0->rotation.y) * COSS(arg0->rotation.z));
    arg2->z = arg1 * (COSS(arg0->rotation.x) * COSS(arg0->rotation.y));
}

extern f32 D_FLT_8219A824;

/**
 * Sets the particle's stepMagnitude to arg1 times the particle scale D_FLT_8219A824.
 * Seen in play (2026-11-13) in the 165-move sweep: arg1 = 0.4 set stepMagnitude (0x70) to 0.704,
 * arg1 times the particle scale D_FLT_8219A824 (1.76).
 */
void Particle_SetStepMagnitudeScaled(s8 *arg0, f32 arg1) {
    M2C_FIELD(arg0, f32 *, 0x70) = (f32) (arg1 * D_FLT_8219A824);
}

extern f32 D_FLT_8219A824;

/**
 * Sets the particle's magnitudeStep to arg1 times the particle scale D_FLT_8219A824.
 * Seen in play (2026-11-13) (tour of menus and a COM battle): ran in the battle opening, a switch
 * in battle and a Pound turn.
 * @unverified Name and comment guessed from the code.
 */
void Particle_SetMagnitudeStepScaled(s8 *arg0, f32 arg1) {
    M2C_FIELD(arg0, f32 *, 0x74) = (f32) (arg1 * D_FLT_8219A824);
}

/**
 * Moves stepMagnitude toward `arg1` (times the render scale) with ParticleMath_ApproachFloat.
 * Seen in play (2026-11-12) in move animations (30-move sweep): it changed stepMagnitude (0x70)
 * of the live particle, e.g. 7.04 -> 5.72.
 */
s32 Particle_ApproachStepMagnitude(Particle* arg0, f32 arg1, f32 arg2) {
    return ParticleMath_ApproachFloat(&arg0->stepMagnitude, arg1 * gParticleRenderContext.scale.y, arg2 * gParticleRenderContext.scale.y);
}

/**
 * Approach stepMagnitude, magnitudeStep using the stored or supplied target and step.
 * Seen in play (2026-11-13) in the 165-move sweep (Petal Dance): it changed stepMagnitude (0x70)
 * only.
 */
s32 Particle_StepMagnitude_ApproachUsingMagnitudeStep(Particle* arg0, f32 arg1) {
    return ParticleMath_ApproachFloat(&arg0->stepMagnitude, arg1 * gParticleRenderContext.scale.y, arg0->magnitudeStep);
}

/**
 * Steps magnitudeStep toward arg1 by arg2, both scaled. Returns nonzero once it arrives.
 * @unverified Name guessed from the code.
 */
s32 Particle_Field74_Approach_0ADBC(Particle* arg0, f32 arg1, f32 arg2) {
    return ParticleMath_ApproachFloat(&arg0->magnitudeStep, arg1 * gParticleRenderContext.scale.y, arg2 * gParticleRenderContext.scale.y);
}

/**
 * Sets motionStep to the vector times the render scale.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name and comment guessed from the code.
 */
void Particle_SetMotionStepScaled(Particle* arg0, Vec3f arg1) {
    M2C_FIELD(arg0, f32*, 0x78) = arg1.x * gParticleRenderContext.scale.y;
    M2C_FIELD(arg0, f32*, 0x7C) = arg1.y * gParticleRenderContext.scale.y;
    M2C_FIELD(arg0, f32*, 0x80) = arg1.z * gParticleRenderContext.scale.y;
}

/**
 * Sets motionStep (0x78), the per-frame velocity that Particle_ApplyMotionStep adds to motionOffset, to the
 * scaled (x, y, z). Was Particle_SetVelocityImpulse. Seen in play (2026-11-12) in move animations: wrote 0x78-0x80.
 */
void Particle_SetMotionStep(Particle* arg0, f32 arg1, f32 arg2, f32 arg3) {
    M2C_FIELD(arg0, f32*, 0x78) = arg1 * gParticleRenderContext.scale.y;
    M2C_FIELD(arg0, f32*, 0x78 + 4) = arg2 * gParticleRenderContext.scale.y;
    M2C_FIELD(arg0, f32*, 0x78 + 8) = arg3 * gParticleRenderContext.scale.y;
}

extern f32 D_FLT_8219A824;

/**
 * Sets the particle's motionStep.x to arg1 times the particle scale D_FLT_8219A824.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name and comment guessed from the code.
 */
void Particle_SetMotionStepXScaled(s8 *arg0, f32 arg1) {
    M2C_FIELD(arg0, f32 *, 0x78) = (f32) (arg1 * D_FLT_8219A824);
}

extern f32 D_FLT_8219A824;

/**
 * Sets the particle's motionStep.y to arg1 times the particle scale D_FLT_8219A824.
 * Seen in play (2026-11-12) in move animations (30-move sweep): it changed motionStep.y (0x7C) of
 * the live particle, e.g. 0 -> 2.112.
 */
void Particle_SetMotionStepYScaled(s8 *arg0, f32 arg1) {
    M2C_FIELD(arg0, f32 *, 0x7C) = (f32) (arg1 * D_FLT_8219A824);
}

extern f32 D_FLT_8219A824;

/**
 * Sets the particle's motionStep.z to arg1 times the particle scale D_FLT_8219A824.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name and comment guessed from the code.
 */
void Particle_SetMotionStepZScaled(s8 *arg0, f32 arg1) {
    M2C_FIELD(arg0, f32 *, 0x80) = (f32) (arg1 * D_FLT_8219A824);
}

/**
 * Raises motionStep.x by `arg2` up to `arg1` (both times the render scale). Returns 1 at the cap.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name and comment guessed from the code.
 */
s32 Particle_IncreaseMotionStepXTo(Particle* arg0, f32 arg1, f32 arg2) {
    f32 temp_fv0;
    s32 var_v1 = 0;

    arg0->motionStep.x += arg2 * gParticleRenderContext.scale.y;

    temp_fv0 = arg1 * gParticleRenderContext.scale.y;
    if (temp_fv0 <= arg0->motionStep.x) {
        arg0->motionStep.x = temp_fv0;
        var_v1 = 1;
    }
    return var_v1;
}

/**
 * Raises motionStep.y by arg2 (scaled) and clamps it at arg1 (scaled). Returns 1 once
 * clamped.
 * @unverified Name guessed from the code.
 */
s32 Particle_Field7C_IncrementXUntilAtLeast_0AF54(Particle* arg0, f32 arg1, f32 arg2) {
    f32 temp_fv0;
    s32 var_v1 = 0;

    arg0->motionStep.y += arg2 * gParticleRenderContext.scale.y;

    temp_fv0 = arg1 * gParticleRenderContext.scale.y;
    if (temp_fv0 <= arg0->motionStep.y) {
        arg0->motionStep.y = temp_fv0;
        var_v1 = 1;
    }
    return var_v1;
}

/**
 * Raises motionStep.z by arg2 (scaled) and clamps it at arg1 (scaled). Returns 1 once
 * clamped.
 * @unverified Name guessed from the code.
 */
s32 Particle_Field7C_IncrementYUntilAtLeast_0AFA8(Particle* arg0, f32 arg1, f32 arg2) {
    f32 temp_fv0;
    s32 var_v1 = 0;

    arg0->motionStep.z += arg2 * gParticleRenderContext.scale.y;

    temp_fv0 = arg1 * gParticleRenderContext.scale.y;
    if (temp_fv0 <= arg0->motionStep.z) {
        arg0->motionStep.z = temp_fv0;
        var_v1 = 1;
    }
    return var_v1;
}

/**
 * Decrease the selected field toward its threshold and return the completion result.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name and comment from Stadium 1, matched by code similarity.
 */
s32 Particle_MotionStep_DecrementYUntilAtMost(Particle* arg0, f32 arg1, f32 arg2) {
    s32 var_v1 = 0;
    f32 temp_fv0;

    arg0->motionStep.x -= arg2 * gParticleRenderContext.scale.y;

    temp_fv0 = arg1 * gParticleRenderContext.scale.y;
    if (arg0->motionStep.x <= temp_fv0) {
        arg0->motionStep.x = temp_fv0;
        var_v1 = 1;
    }
    return var_v1;
}

/**
 * Lowers motionStep.y by arg2 (scaled) and clamps it at arg1 (scaled). Returns 1 once
 * clamped.
 * @unverified Name guessed from the code.
 */
s32 Particle_Field7C_DecrementXUntilAtMost_0B050(Particle* arg0, f32 arg1, f32 arg2) {
    f32 temp_fv0;
    s32 var_v1 = 0;

    arg0->motionStep.y -= arg2 * gParticleRenderContext.scale.y;

    temp_fv0 = arg1 * gParticleRenderContext.scale.y;
    if (arg0->motionStep.y <= temp_fv0) {
        arg0->motionStep.y = temp_fv0;
        var_v1 = 1;
    }
    return var_v1;
}

/**
 * Lowers motionStep.z by arg2 (scaled) and clamps it at arg1 (scaled). Returns 1 once
 * clamped.
 * @unverified Name guessed from the code.
 */
s32 Particle_Field7C_DecrementYUntilAtMost_0B0A4(Particle* arg0, f32 arg1, f32 arg2) {
    s32 var_v1 = 0;
    f32 temp_fv0;

    arg0->motionStep.z -= arg2 * gParticleRenderContext.scale.y;

    temp_fv0 = arg1 * gParticleRenderContext.scale.y;
    if (arg0->motionStep.z <= temp_fv0) {
        arg0->motionStep.z = temp_fv0;
        var_v1 = 1;
    }
    return var_v1;
}

/**
 * Multiplies motionStep by `arg1`.
 * No caller in play (2026-11-13): nothing that runs reaches it, not even through callbacks, data
 * tables or fragment headers.
 * @unverified Name and comment guessed from the code.
 */
void Particle_ScaleMotionStep(s8 *arg0, f32 arg1) {
    M2C_FIELD(arg0, f32 *, 0x78) = (f32) (M2C_FIELD(arg0, f32 *, 0x78) * arg1);
    M2C_FIELD(arg0, f32 *, 0x7C) = (f32) (M2C_FIELD(arg0, f32 *, 0x7C) * arg1);
    M2C_FIELD(arg0, f32 *, 0x80) = (f32) (M2C_FIELD(arg0, f32 *, 0x80) * arg1);
}

/**
 * Steps motionStep.y toward arg1 by arg2 (both scaled by the render context); returns 1 on arrival.
 * Seen in play (2026-11-13) in the 165-move sweep (Razor Wind): it changed motionStep.y (0x7C)
 * only.
 */
s32 Particle_ApproachMotionStepY(Particle* arg0, f32 arg1, f32 arg2) {
    return ParticleMath_ApproachFloat(&arg0->motionStep.y, arg1 * gParticleRenderContext.scale.y, arg2 * gParticleRenderContext.scale.y);
}

/**
 * Sets the f32 at offset 0x7C to the step magnitude times the cosine of the angle at
 * offset 0x90.
 * @unverified Name guessed from the code.
 */
void Particle_Field7C_SetXFromField74AngleY_0B1EC(Particle* arg0) {
    M2C_FIELD(arg0, f32*, 0x7C) = COSS(M2C_FIELD(arg0, u16*, 0x90)) * arg0->stepMagnitude;
}

void func_8213FA88(Particle* arg0) {
    M2C_FIELD(arg0, f32*, 0x78) = arg0->stepMagnitude * SINS(M2C_FIELD(arg0, u16*, 0x92));
}

/**
 * Sets the f32 at offset 0x80 to the step magnitude times the cosine of the angle at
 * offset 0x92.
 * @unverified Name guessed from the code.
 */
void Particle_Field7C_SetYFromField74AngleX_0B1C4(Particle* arg0) {
    M2C_FIELD(arg0, f32*, 0x80) = COSS(M2C_FIELD(arg0, u16*, 0x92)) * arg0->stepMagnitude;
}

/**
 * No caller in play (2026-11-13): nothing that runs reaches it, not even through callbacks, data
 * tables or fragment headers.
 * @unverified Name was previously used only by callers of this address; the definition was still func_.
 */
void Particle_SetMotionStepFromRotationXZ(Particle* arg0) {
    M2C_FIELD(arg0, f32*, 0x78) = arg0->stepMagnitude * COSS(M2C_FIELD(arg0, u16*, 0x94));
    M2C_FIELD(arg0, f32*, 0x7C) = arg0->stepMagnitude * SINS(M2C_FIELD(arg0, u16*, 0x94));
}

/**
 * Sets the f32s at offsets 0x78 and 0x80 to the step magnitude times the sine and cosine
 * of the angle at offset 0x92.
 * @unverified Name guessed from the code.
 */
void Particle_SetMotionStepXZFromRotationY(Particle* arg0) {
    M2C_FIELD(arg0, f32*, 0x78) = SINS(M2C_FIELD(arg0, u16*, 0x92)) * arg0->stepMagnitude;
    M2C_FIELD(arg0, f32*, 0x80) = COSS(M2C_FIELD(arg0, u16*, 0x92)) * arg0->stepMagnitude;
}

void Particle_SetMotionStepFromRotationXY(Particle* arg0) {
    arg0->motionStep.x = arg0->stepMagnitude * COSS(arg0->rotation.x) * SINS(arg0->rotation.y);
    arg0->motionStep.y = -arg0->stepMagnitude * SINS(arg0->rotation.x);
    arg0->motionStep.z = arg0->stepMagnitude * COSS(arg0->rotation.x) * COSS(arg0->rotation.y);
}

/**
 * Evaluate the explicit trigonometric component formula and store/add the resulting motion term.
 * No caller in play (2026-11-13): nothing that runs reaches it, not even through callbacks, data
 * tables or fragment headers.
 * @unverified Name and comment from Stadium 1, matched by code similarity.
 */
void Particle_MotionStep_SetVecFromField74AnglesXZ(Particle* arg0) {
    arg0->motionStep.x = arg0->stepMagnitude * SINS(arg0->rotation.x) * SINS(arg0->rotation.z);
    arg0->motionStep.y = -arg0->stepMagnitude * SINS(arg0->rotation.x) * COSS(arg0->rotation.z);
    arg0->motionStep.z = arg0->stepMagnitude * COSS(arg0->rotation.x);
}

void Particle_SetMotionStepFromRotationXYAlt(Particle* arg0) {
    arg0->motionStep.x = arg0->stepMagnitude * SINS(arg0->rotation.y);
    arg0->motionStep.y = -arg0->stepMagnitude * SINS(arg0->rotation.x) * COSS(arg0->rotation.y);
    arg0->motionStep.z = arg0->stepMagnitude * COSS(arg0->rotation.x) * COSS(arg0->rotation.y);
}

/**
 * Not reached in play: no move in the 165-move sweep called it, and nothing in the source calls it
 * directly.
 */
void Particle_SetMotionStepFromRotationYZ(Particle* arg0) {
    arg0->motionStep.x = arg0->stepMagnitude * SINS(arg0->rotation.y) * COSS(arg0->rotation.z);
    arg0->motionStep.y = arg0->stepMagnitude * SINS(arg0->rotation.y) * SINS(arg0->rotation.z);
    //!bug The z step is not scaled by stepMagnitude, unlike x and y and every sibling.
    arg0->motionStep.z = COSS(arg0->rotation.y);
}

void Particle_SetMotionStepFromRotationXYZ(Particle* arg0) {
    arg0->motionStep.x = arg0->stepMagnitude * (COSS(arg0->rotation.x) * SINS(arg0->rotation.y) * COSS(arg0->rotation.z) +
                                     SINS(arg0->rotation.x) * SINS(arg0->rotation.z));
    arg0->motionStep.y = -arg0->stepMagnitude * (COSS(arg0->rotation.x) * SINS(arg0->rotation.y) * SINS(arg0->rotation.z) -
                                      SINS(arg0->rotation.x) * COSS(arg0->rotation.z));
    arg0->motionStep.z = arg0->stepMagnitude * (COSS(arg0->rotation.x) * COSS(arg0->rotation.y));
}

void Particle_SetMotionStepFromRotationXYZAlt(Particle* arg0) {
    arg0->motionStep.x = arg0->stepMagnitude * (SINS(arg0->rotation.x) * COSS(arg0->rotation.y) * SINS(arg0->rotation.z) +
                                     COSS(arg0->rotation.x) * SINS(arg0->rotation.y));
    arg0->motionStep.y = -arg0->stepMagnitude * SINS(arg0->rotation.x) * COSS(arg0->rotation.z);

    arg0->motionStep.z = arg0->stepMagnitude * (-SINS(arg0->rotation.x) * SINS(arg0->rotation.y) * SINS(arg0->rotation.z) +
                                     COSS(arg0->rotation.x) * COSS(arg0->rotation.y));
}

void Particle_SetMotionStepFromRotationYZAlt(Particle* arg0) {
    arg0->motionStep.x = arg0->stepMagnitude * SINS(arg0->rotation.y) * COSS(arg0->rotation.z);
    arg0->motionStep.y = arg0->stepMagnitude * (COSS(arg0->rotation.x) * SINS(arg0->rotation.y) * SINS(arg0->rotation.z) -
                                     SINS(arg0->rotation.x) * COSS(arg0->rotation.y));
    arg0->motionStep.z = arg0->stepMagnitude * (SINS(arg0->rotation.x) * SINS(arg0->rotation.y) * SINS(arg0->rotation.z) +
                                     COSS(arg0->rotation.x) * COSS(arg0->rotation.y));
}

/**
 * Evaluate the explicit trigonometric component formula and store/add the resulting motion term.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void Particle_SetMotionStepFromRotationYZVariant(Particle* arg0) {
    arg0->motionStep.x = arg0->stepMagnitude * (SINS(arg0->rotation.y) * COSS(arg0->rotation.z) +
                                     SINS(arg0->rotation.x) * COSS(arg0->rotation.y) * SINS(arg0->rotation.z));
    arg0->motionStep.y = arg0->stepMagnitude * (SINS(arg0->rotation.y) * SINS(arg0->rotation.z) -
                                     SINS(arg0->rotation.x) * COSS(arg0->rotation.y) * COSS(arg0->rotation.z));
    arg0->motionStep.z = arg0->stepMagnitude * (COSS(arg0->rotation.x) * COSS(arg0->rotation.y));
}

/**
 * Advances rotationStep.y by arg2 and puts motionOffset on a circle of radius arg1
 * (scaled) at that angle. motionStep.x and motionStep.z become the change from last frame.
 * @unverified Name guessed from the code.
 */
void Particle_UpdateRotatingVelocityXZ(Particle* arg0, f32 arg1, s16 arg2) {
    f32 tmp1 = arg0->motionOffset.x;
    f32 tmp2 = arg0->motionOffset.z;

    arg0->rotationStep.y += arg2;

    arg0->motionOffset.x = arg1 * gParticleRenderContext.scale.y * SINS(arg0->rotationStep.y);
    arg0->motionOffset.z = arg1 * gParticleRenderContext.scale.y * COSS(arg0->rotationStep.y);

    arg0->motionStep.x = arg0->motionOffset.x - tmp1;
    arg0->motionStep.z = arg0->motionOffset.z - tmp2;
}

/**
 * Ballistic arc over arg5 frames. On the first call, clears motionOffset and sets the
 * step magnitude (arg3), upward speed (arg1) and heading (arg4). Each frame after, lowers
 * the upward speed by the gravity arg2 and applies the motion step. Returns 1 when the time
 * is up.
 * @unverified Name guessed from the code.
 */
s32 Particle_Field50_AdvanceField7CWithTimer_0B854(Particle* arg0, f32 arg1, f32 arg2, f32 arg3, s16 arg4, s16 arg5) {
    s32 sp24 = 0;

    if (Particle_LacksFlags(arg0, 2) != 0) {
        Particle_SetFlags(arg0, 2);
        arg0->motionOffset.x = arg0->motionOffset.y = arg0->motionOffset.z = 0.0f;
        arg0->stepMagnitude = arg3 * gParticleRenderContext.scale.y;
        arg0->motionStep.y = arg1 * gParticleRenderContext.scale.y;
        arg0->rotation.y = arg4;
        func_8213FB14(arg0);
        arg0->phaseTimer = arg5;
    }

    arg0->phaseTimer--;
    if (arg0->phaseTimer < 0) {
        sp24 = 1;
    } else {
        arg0->motionStep.y -= arg2 * gParticleRenderContext.scale.y;
        Particle_ApplyMotionStep(arg0);
    }

    return sp24;
}

/**
 * Sets scale to arg1 times the render-context scale.
 * Seen in play (2026-11-13) in the 165-move sweep (Pay Day): arg1 = 1.5 set scale to 2.64.
 */
void Particle_SetScaleScaled(Particle* arg0, f32 arg1) {
    arg0->scale = arg1 * gParticleRenderContext.scale.y;
}

/**
 * Set particle scale directly, without render-context scaling.
 * Seen in play (2026-11-12) in move animations (30-move sweep): it changed scale (0x1C) of the
 * live particle, e.g. 1 -> 5.3.
 */
void Particle_SetScale(Particle* arg0, f32 arg1) {
    arg0->scale = arg1;
}

/**
 * Sets scaleTarget (0x20) to arg1 times the render-context scale. Was Particle_SetScaleSpeed,
 * swapped with Particle_SetScaleStep: Particle_ApproachScaleTarget moves scale toward this field.
 * Seen in play (2026-11-13) in the 165-move sweep (Vice Grip): arg1 = 0.1 wrote 0.36 to 0x20, and
 * Particle_ApproachScaleTarget then moved scale toward 0.36.
 */
void Particle_SetScaleTarget(Particle* arg0, f32 arg1) {
    arg0->scaleTarget = arg1 * gParticleRenderContext.scale.y;
}

/**
 * Sets scaleStep (0x24) to arg1 times the render-context scale. Was Particle_SetScaleTarget,
 * swapped with Particle_SetScaleTarget.
 * Seen in play (2026-11-13) in the 165-move sweep (Vice Grip): arg1 = 0.03 wrote 0.108 to 0x24, and
 * Particle_ApproachScaleTarget then grew scale by 0.108 per call.
 */
void Particle_SetScaleStep(Particle* arg0, f32 arg1) {
    arg0->scaleStep = arg1 * gParticleRenderContext.scale.y;
}

/**
 * Steps scale toward arg1 by arg2 (both times the render-context scale); returns 1 on arrival.
 * Seen in play (2026-11-13) in the 165-move sweep (Fire Punch): scale grew 0.18 to 0.216 to 0.252
 * on successive calls.
 */
s32 Particle_ApproachScale(Particle* arg0, f32 arg1, f32 arg2) {
    return ParticleMath_ApproachFloat(&arg0->scale, arg1 * gParticleRenderContext.scale.y, arg2 * gParticleRenderContext.scale.y);
}

/**
 * Particle_ApproachScale, then advances the lifecycle on arrival.
 * Seen in play (2026-11-13) in the 165-move sweep (Ice Beam): scale shrank 1.76 to 1.672 to 1.584.
 */
s32 Particle_ApproachScaleThenAdvance(Particle* arg0, f32 arg1, f32 arg2) {
    s32 sp1C = Particle_ApproachScale(arg0, arg1, arg2);

    if (sp1C != 0) {
        Particle_AdvanceLifecycle(arg0);
    }
    return sp1C;
}

/**
 * Steps scale toward scaleTarget by scaleStep; returns 1 on arrival.
 * Seen in play (2026-11-13) in the 165-move sweep (Vice Grip): with scaleTarget 0.36 and scaleStep
 * 0.108, scale went from 0 to 0.108.
 */
s32 Particle_ApproachScaleTarget(Particle* arg0) {
    return ParticleMath_ApproachFloat(&arg0->scale, arg0->scaleTarget, arg0->scaleStep);
}

/**
 * Particle_ApproachScaleTarget, then advances the lifecycle on arrival.
 * Seen in play (2026-11-13) in the 165-move sweep (Vice Grip): with scaleTarget 0.36 and scaleStep
 * 0.108, scale went from 0 to 0.108 and it returned 0.
 */
s32 Particle_ApproachScaleTargetThenAdvance(Particle* arg0) {
    s32 sp1C = Particle_ApproachScaleTarget(arg0);

    if (sp1C != 0) {
        Particle_AdvanceLifecycle(arg0);
    }
    return sp1C;
}

/**
 * Steps scaleTarget itself toward arg1 by arg2 (both times the render-context scale); returns 1 on
 * arrival.
 * No caller in play (2026-11-13): nothing that runs reaches it, not even through callbacks, data
 * tables or fragment headers.
 * @unverified Name from the code; not reached in the move sweep.
 */
s32 Particle_StepScaleTarget(Particle* arg0, f32 arg1, f32 arg2) {
    return ParticleMath_ApproachFloat(&arg0->scaleTarget, arg1 * gParticleRenderContext.scale.y, arg2 * gParticleRenderContext.scale.y);
}

/**
 * Set primRed, primGreen, primBlue.
 * Seen in play (2026-11-13) in the 165-move sweep: with (FF, FF, FF) it set prim_r (0xBA) from 0xC8
 * to 0xFF, with prim_g and prim_b already 0xFF.
 */
void Particle_SetPrimColor(Particle* arg0, u8 arg1, u8 arg2, u8 arg3) {
    arg0->prim_r = arg1;
    arg0->prim_g = arg2;
    arg0->prim_b = arg3;
}

M2C_UNK func_82137804(s32, s32, s32);               /* extern */

/**
 * Steps the particle's primRed toward a target (helper of the approach family).
 * Seen in play (2026-11-12) in move animations (30-move sweep): it changed prim_r (0xBA) of the
 * live particle, e.g. 0xffff -> 0xf7ff.
 */
void Particle_ApproachPrimRed(s32 arg0, s32 arg1, s32 arg2) {
    func_82137804(arg0 + 0xBA, arg1 & 0xFF, arg2 & 0xFF);
}

M2C_UNK func_82137804(s32, s32, s32);               /* extern */

/**
 * Steps the particle's primGreen toward a target (helper of the approach family).
 * Seen in play (2026-11-12) in move animations (30-move sweep): it changed prim_g (0xBB) of the
 * live particle, e.g. 0xf7ff -> 0xf7f7.
 */
void Particle_ApproachPrimGreen(s32 arg0, s32 arg1, s32 arg2) {
    func_82137804(arg0 + 0xBB, arg1 & 0xFF, arg2 & 0xFF);
}

M2C_UNK func_82137804(s32, s32, s32);               /* extern */

/**
 * Steps the particle's primBlue toward a target (helper of the approach family).
 * Seen in play (2026-11-12) in move animations (30-move sweep): it changed prim_b (0xBC) of the
 * live particle, e.g. 0xffffffff -> 0xf7ffffff.
 */
void Particle_ApproachPrimBlue(s32 arg0, s32 arg1, s32 arg2) {
    func_82137804(arg0 + 0xBC, arg1 & 0xFF, arg2 & 0xFF);
}

extern s16 D_8219A8B2;
extern s16 D_8219A8B4;
extern s16 D_8219A8B6;

/**
 * Copies prim_r/g/b into the temporary color D_8219A8B2..D_8219A8B6.
 * Seen in play (2026-11-13) (tour of menus and a COM battle): ran in the battle opening and a
 * switch in battle.
 * @unverified Name and comment guessed from the code.
 */
void Particle_StorePrimColorInTemp(s8 *arg0) {
    D_8219A8B2 = (s16) M2C_FIELD(arg0, u8 *, 0xBA);
    D_8219A8B4 = (s16) M2C_FIELD(arg0, u8 *, 0xBB);
    D_8219A8B6 = (s16) M2C_FIELD(arg0, u8 *, 0xBC);
}

extern s16 D_8219A8B2;
extern s16 D_8219A8B4;
extern s16 D_8219A8B6;

/**
 * Seen in play (2026-11-13) (tour of menus and a COM battle): ran in the battle opening and a
 * switch in battle.
 * @unverified Name was previously used only by callers of this address; the definition was still func_.
 */
void BattleAnim_LoadGlobalTintToParticle(s8 *arg0) {
    M2C_FIELD(arg0, s8 *, 0xBA) = (s8) D_8219A8B2;
    M2C_FIELD(arg0, s8 *, 0xBB) = (s8) D_8219A8B4;
    M2C_FIELD(arg0, s8 *, 0xBC) = (s8) D_8219A8B6;
}

/**
 * Set envRed, envGreen, envBlue.
 * Seen in play (2026-11-12) in move animations (30-move sweep): it changed env_r/g/b (0xBD-0xBF)
 * of the live particle, e.g. 0xffffff64 -> 0xffffffff.
 */
void Particle_SetEnvColor(Particle* arg0, u8 arg1, u8 arg2, u8 arg3) {
    arg0->env_r = arg1;
    arg0->env_g = arg2;
    arg0->env_b = arg3;
}

M2C_UNK func_82137804(s32, s32, s32);               /* extern */

/**
 * Steps the particle's envRed toward a target (helper of the approach family).
 * Seen in play (2026-11-12) in move animations (30-move sweep): it changed env_r (0xBD) of the
 * live particle, e.g. 0xff0000 -> 0xdf0000.
 */
void Particle_ApproachEnvRed(s32 arg0, s32 arg1, s32 arg2) {
    func_82137804(arg0 + 0xBD, arg1 & 0xFF, arg2 & 0xFF);
}

M2C_UNK func_82137804(s32, s32, s32);               /* extern */

/**
 * Steps the particle's envBlue toward a target (helper of the approach family).
 * Seen in play (2026-11-12) in move animations (30-move sweep): it changed env_b (0xBF) of the
 * live particle, e.g. 0xf7c0cfff -> 0xf7c0cff7.
 */
void Particle_ApproachEnvBlue(s32 arg0, s32 arg1, s32 arg2) {
    func_82137804(arg0 + 0xBF, arg1 & 0xFF, arg2 & 0xFF);
}

M2C_UNK func_82137804(s32, s32, s32);               /* extern */

/**
 * Steps the particle's envGreen toward a target (helper of the approach family).
 * Seen in play (2026-11-12) in move animations (30-move sweep): it changed env_g (0xBE) of the
 * live particle, e.g. 0xe7ffff00 -> 0xe7ffe700.
 */
void Particle_ApproachEnvGreen(s32 arg0, s32 arg1, s32 arg2) {
    func_82137804(arg0 + 0xBE, arg1 & 0xFF, arg2 & 0xFF);
}

void Particle_SetPrimAlpha(s8 *arg0, char arg1)
{
  s8 *new_var; // FAKE: permuter temp
  s8 *new_var2; // FAKE: permuter temp
  new_var2 = arg0;
  new_var = (s8 *) new_var2;
  *((s8 *) (new_var + 0xC0)) = arg1;
}

M2C_UNK func_82137804(s32, s32, s32);               /* extern */

/**
 * Steps the particle's primAlpha toward a target (helper of the approach family).
 * Seen in play (2026-11-12) in move animations (30-move sweep): it changed prim_a (0xC0) of the
 * live particle, e.g. 0xc8000000 -> 0xc4000000.
 */
void Particle_ApproachPrimAlpha(s32 arg0, s32 arg1, s32 arg2) {
    func_82137804(arg0 + 0xC0, arg1 & 0xFF, arg2 & 0xFF);
}

/**
 * Steps prim alpha toward arg1 by arg2 and advances the lifecycle when it arrives.
 * Run the field-approach helper and advance lifecycle when it reports completion.
 * Seen in play (2026-11-13) in the 165-move sweep (Pay Day): with target 0 and step 0x40 it lowered
 * prim alpha (0xC0) from 0xFF to 0xBF.
 */
s32 Particle_ApproachPrimAlphaThenAdvance(Particle* arg0, u8 arg1, u8 arg2) {
    s32 sp1C = Particle_PrimAlpha_Approach_0BC2C(arg0, arg1, arg2);

    if (sp1C != 0) {
        Particle_AdvanceLifecycle(arg0);
    }
    return sp1C;
}

/**
 * Sets the particle's unk_A6 to arg1.
 * Seen in play (2026-11-13) (tour of menus and a COM battle): ran in the battle opening, a switch
 * in battle and a Pound turn.
 * @unverified Name and comment guessed from the code.
 */
void Particle_SetUnkA6(s8 *arg0, s16 arg1) {
    M2C_FIELD(arg0, s16 *, 0xA2) = arg1;
}

s32 func_821405A8(s8 *arg0, s16 arg1, s16 arg2) {
    s32 var_v1;

    M2C_FIELD(arg0, s16 *, 0xA2) = (s16) (M2C_FIELD(arg0, s16 *, 0xA2) - arg2);
    var_v1 = 0;
    if (arg1 >= M2C_FIELD(arg0, s16 *, 0xA2)) {
        M2C_FIELD(arg0, s16 *, 0xA2) = arg1;
        var_v1 = 1;
    }
    return var_v1;
}

/**
 * Decrease the selected field toward its threshold and return the completion result.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
s32 Particle_FieldA6_DecrementToZero_0BD08(Particle* arg0, s16 arg1) {
    return Particle_FieldA6_DecrementTo_0BCC4(arg0, 0, arg1);
}

/**
 * Run the countdown helper and advance lifecycle when it reports completion.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
s32 Particle_FieldA6_DecrementToZeroAndStepState_0BD34(Particle* arg0, s16 arg1) {
    s32 sp1C = Particle_FieldA6_DecrementTo_0BCC4(arg0, 0, arg1);

    if (sp1C != 0) {
        Particle_AdvanceLifecycle(arg0);
    }
    return sp1C;
}

/**
 * Decrease the selected field toward its threshold and return the completion result.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
s32 Particle_FieldA6_DecrementToStep1_0BD80(Particle* arg0, s16 arg1) {
    return Particle_FieldA6_DecrementTo_0BCC4(arg0, arg1, 1);
}

/**
 * Counts unk_A6 (offset 0xA2) down by 1 toward 0; returns 1 when it gets there.
 * Decrease the selected field toward its threshold and return the completion result.
 * Seen in play (2026-11-13) in the 165-move sweep (Cut): unk_A6 at 0xA2 went from 7 to 6.
 */
s32 Particle_DecrementUnkA6ToZero(Particle* arg0) {
    return Particle_FieldA6_DecrementTo_0BCC4(arg0, 0, 1);
}

/**
 * Counts unk_A6 (offset 0xA2) down by 1 toward 0 and advances the lifecycle when it gets there.
 * Run the countdown helper and advance lifecycle when it reports completion.
 * Seen in play (2026-11-13) in the 165-move sweep (Mega Kick, Vice Grip): unk_A6 at 0xA2 went from
 * 0x32 to 0x31.
 */
s32 Particle_DecrementUnkA6ToZeroThenAdvance(Particle* arg0) {
    s32 sp1C = Particle_FieldA6_DecrementTo_0BCC4(arg0, 0, 1);

    if (sp1C != 0) {
        Particle_AdvanceLifecycle(arg0);
    }
    return sp1C;
}

/**
 * Sets the particle's unk_A8 to arg1.
 * Seen in play (2026-11-13) (tour of menus and a COM battle): ran in the battle opening, a switch
 * in battle and a Pound turn.
 * @unverified Name and comment guessed from the code.
 */
void Particle_SetUnkA8(s8 *arg0, s16 arg1) {
    M2C_FIELD(arg0, s16 *, 0xA4) = arg1;
}

s32 func_8214070C(s8 *arg0, s16 arg1) {
    s32 var_v1;

    M2C_FIELD(arg0, s16 *, 0xA4) = (s16) (M2C_FIELD(arg0, s16 *, 0xA4) - 1);
    var_v1 = 0;
    if (arg1 >= M2C_FIELD(arg0, s16 *, 0xA4)) {
        M2C_FIELD(arg0, s16 *, 0xA4) = arg1;
        var_v1 = 1;
    }
    return var_v1;
}

/**
 * Counts unk_A8 (offset 0xA4) down by 1 toward 0; returns 1 when it gets there.
 * Decrease the selected field toward its threshold and return the completion result.
 * Seen in play (2026-11-13) in the 165-move sweep (Ember): unk_A8 at 0xA4 went from 7 to 6.
 */
s32 Particle_DecrementUnkA8ToZero(Particle* arg0) {
    return Particle_FieldA8_DecrementTo_0BE30(arg0, 0);
}

/**
 * Run the countdown helper and advance lifecycle when it reports completion.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
s32 Particle_FieldA8_DecrementToZeroStep1AndStepState_0BE8C(Particle* arg0) {
    s32 sp1C = Particle_FieldA8_DecrementTo_0BE30(arg0, 0);

    if (sp1C != 0) {
        Particle_AdvanceLifecycle(arg0);
    }
    return sp1C;
}

void func_821407A8(s8 *arg0, int arg1)
{
  int *new_var; // FAKE: permuter temp
  new_var = &arg1;
  *((s8 *) (((s8 *) arg0) + 0xC6)) = *new_var;
}

/**
 * Sets the particle's unk_AC to arg1.
 * Seen in play (2026-11-13) in the 165-move sweep: arg1 = 0 cleared unk_AC (offset 0xA8) from 0x16.
 */
void Particle_SetUnkAC(s8 *arg0, s16 arg1) {
    M2C_FIELD(arg0, s16 *, 0xA8) = arg1;
}

void func_821407C8(s8 *arg0, unsigned char arg1)
{
  s8 *new_var; // FAKE: permuter temp
  new_var = (s8 *) (((s8 *) arg0) + 0xCB);
  *new_var = arg1;
}

void func_821407D4(s8 *arg0, unsigned char arg1)
{
  s8 *new_var; // FAKE: permuter temp
  new_var = ((s8 *) arg0) + 0xCB;
  *((s8 *) new_var) = arg1;
}

/**
 * Sets the particle's unk_CC to arg1.
 * Seen in play (2026-11-13) in the 165-move sweep (Selfdestruct): arg1 = 9 set the byte at 0xC8
 * (unk_CC) from 2 to 9.
 */
void Particle_SetUnkCC(s8 *arg0, unsigned short arg1)
{
  *((s8 *) (((s8 *) arg0) + 0xC8)) = arg1;
}

/**
 * Sets the particle's unk_AA to arg1.
 * Seen in play (2026-11-13) in the 165-move sweep (Thunder Punch, Scratch): arg1 = 0 cleared unk_AA
 * (offset 0xA6) from 1.
 */
void Particle_SetUnkAA(s8 *arg0, s16 arg1) {
    M2C_FIELD(arg0, s16 *, 0xA6) = arg1;
}

/**
 * Sets the particle's unk_CE to arg1.
 * Seen in play (2026-11-13) (tour of menus and a COM battle): ran in the battle opening, a switch
 * in battle and a Pound turn.
 * @unverified Name and comment guessed from the code.
 */
void Particle_SetUnkCE(s8 *arg0, s16 arg1) {
    M2C_FIELD(arg0, s8 *, 0xCA) = (s8) arg1;
}

/**
 * Sets the particle's unk_CD to arg1.
 * Seen in play (2026-11-13) (tour of menus and a COM battle): ran in the battle opening, a switch
 * in battle and a Pound turn.
 * @unverified Name and comment guessed from the code.
 */
void Particle_SetUnkCD(s8 *arg0, s16 arg1) {
    M2C_FIELD(arg0, s8 *, 0xC9) = (s8) arg1;
}

/**
 * Sets the particle's unk_AE to arg1.
 * Seen in play (2026-11-13) in the 165-move sweep (Pay Day, Double Kick): arg1 = 0xE1 was written
 * to unk_AE, which sits at offset 0xAA.
 */
void Particle_SetUnkAE(s8 *arg0, s16 arg1) {
    M2C_FIELD(arg0, s16 *, 0xAA) = arg1;
}

M2C_UNK func_82137898(s32, s16, s16);               /* extern */

/**
 * Steps the particle's unk_AE toward a target (helper of the approach family).
 * Seen in play (2026-11-13) in the 165-move sweep (Pay Day): with target 0 and step 0x40, unk_AE
 * (offset 0xAA) went from 0xE1 to 0xA1.
 */
void Particle_ApproachUnkAE(s32 arg0, s16 arg1, s16 arg2) {
    func_82137898(arg0 + 0xAA, arg1, arg2);
}

/**
 * Run the field-approach helper and advance lifecycle when it reports completion.
 * Seen in play (2026-11-13) in the 165-move sweep (Ice Beam, Blizzard): with target 0xDC and step
 * 0x20 it moved unk_AE (offset 0xAA) from 0 to 0x20 and returned 0, so the lifecycle did not
 * advance yet.
 */
s32 Particle_ApproachUnkAEThenAdvance(Particle* arg0, s16 arg1, s16 arg2) {
    s32 sp1C = Particle_FieldAE_Approach_0BF60(arg0, arg1, arg2);

    if (sp1C != 0) {
        Particle_AdvanceLifecycle(arg0);
    }
    return sp1C;
}

/**
 * Sets the particle's unk_B0 to arg1.
 * Seen in play (2026-11-13) in the 165-move sweep (Bite): arg1 = 2 was written to unk_B0, which
 * sits at offset 0xAC.
 */
void Particle_SetUnkB0(s8 *arg0, s16 arg1) {
    M2C_FIELD(arg0, s16 *, 0xAC) = arg1;
}

M2C_UNK func_82137898(s32, s16, s16);               /* extern */

/**
 * Steps the particle's unk_B0 toward a target (helper of the approach family).
 * Seen in play (2026-11-13) in the 165-move sweep (Selfdestruct): with target 0 and step 8, unk_B0
 * (offset 0xAC) went from 0x64 to 0x5C.
 */
void Particle_ApproachUnkB0(s32 arg0, s16 arg1, s16 arg2) {
    func_82137898(arg0 + 0xAC, arg1, arg2);
}
