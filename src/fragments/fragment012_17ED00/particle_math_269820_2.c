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
void Particle_Field50_SetXScaled_098E8(Particle* arg0, f32 arg1);
void Particle_Field50_SetYScaled_09900(Particle* arg0, f32 arg1);
void Particle_Field50_AddXScaled_099C0(Particle* arg0, f32 arg1);
void Particle_Field50_AddYScaled_099E0(Particle* arg0, f32 arg1);
void Particle_Field50_SubXScaled_09A78(Particle* arg0, f32 arg1);
void Particle_Field50_SubYScaled_09A98(Particle* arg0, f32 arg1);
s32 Particle_Field50_ApproachXToField5C_09AD8(Particle* arg0, f32 arg1);
s32 Particle_Field50_ApproachYToField5C_09B18(Particle* arg0, f32 arg1);
void Particle_Field50_AddXFromField7C_09C58(Particle* arg0);
void Particle_Field50_AddYFromField7C_09C6C(Particle* arg0);
void Particle_AddVelocityXYFromRotationZViaImpulse(Particle* arg0);
void Particle_AddVelocityFromRotationTemplate2(Particle* arg0);
void Particle_Field50_SetZScaled_09918(Particle* arg0, f32 arg1);
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
void Particle_Field1C_SetScaled_0B938(Particle* arg0, f32 arg1);
void Particle_SetScale(Particle* arg0, f32 arg1);
void Particle_SetScaleSpeed(Particle* arg0, f32 arg1);
void Particle_SetScaleTarget(Particle* arg0, f32 arg1);
s32 Particle_Field1C_Approach_0B98C(Particle* arg0, f32 arg1, f32 arg2);
s32 Particle_Field1C_ApproachAndStepState_0B9D0(Particle* arg0, f32 arg1, f32 arg2);
s32 Particle_Field1C_ApproachField24ByField20_0BA1C(Particle* arg0);
s32 Particle_Field1C_ApproachField24AndStepState_0BA48(Particle* arg0);
s32 Particle_Field20_Approach_0BA84(Particle* arg0, f32 arg1, f32 arg2);
s32 Particle_PrimAlpha_ApproachAndStepState_0BC5C(Particle* arg0, u8 arg1, u8 arg2);
s32 Particle_FieldA6_DecrementToZero_0BD08(Particle* arg0, s16 arg1);
s32 Particle_FieldA6_DecrementToZeroAndStepState_0BD34(Particle* arg0, s16 arg1);
s32 Particle_FieldA6_DecrementToStep1_0BD80(Particle* arg0, s16 arg1);
s32 Particle_FieldA6_DecrementToZeroStep1_0BDAC(Particle* arg0);
s32 Particle_FieldA6_DecrementToZeroStep1AndStepState_0BDD0(Particle* arg0);
s32 Particle_FieldA8_DecrementToZeroStep1_0BE6C(Particle* arg0);
s32 Particle_FieldA8_DecrementToZeroStep1AndStepState_0BE8C(Particle* arg0);
s32 Particle_FieldAE_ApproachAndStepState_0BF98(Particle* arg0, s16 arg1, s16 arg2);

void Particle_AdvanceLifecycle(Particle* arg0);
s32 Particle_TickDelayTimer(Particle* arg0, s16 arg1);
s32 Particle_AnimateFramesPingPong(Particle* arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5);
s32 Particle_AnimateFramesReverseFirstPingPong(Particle* arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5);
void Particle_Field38_SetVecFromVec3fScaled_08C20(Particle* arg0, Vec3f arg1);
void Particle_Field38_AddVecScaledFromVec3f_08D78(Particle* arg0, Vec3f arg1);
void Particle_Field50_AddVecFromField7C_09BDC(Particle* arg0);
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
void Particle_Field7C_SetXYFromField74AngleZ_0B23C(Particle* arg0);
void Particle_Field7C_SetVecFromField74AnglesXZ_0B330(Particle* arg0);
s32 Particle_PrimAlpha_Approach_0BC2C(Particle* arg0, u8 arg1, u8 arg2);
s32 Particle_FieldA6_DecrementTo_0BCC4(Particle* arg0, s16 arg1, s16 arg2);
s32 Particle_FieldA8_DecrementTo_0BE30(Particle* arg0, s16 arg1);
s32 Particle_FieldAE_Approach_0BF60(Particle* arg0, s16 arg1, s16 arg2);

s32 Particle_TickDelayAndAdvanceLifecycle(Particle* arg0, s16 arg1) {
    s32 sp1C = Particle_TickDelayTimer(arg0, arg1);

    if (sp1C != 0) {
        Particle_AdvanceLifecycle(arg0);
    }
    return sp1C;
}

void Particle_SetFlags(Particle* arg0, s32 arg1) {
    arg0->flags |= arg1;
}

void Particle_ClearFlags(Particle* arg0, s32 arg1) {
    arg0->flags &= ~arg1;
}

void Particle_ToggleFlags(Particle* arg0, s32 arg1) {
    arg0->flags ^= arg1;
}

s32 Particle_HasFlags(Particle* arg0, s32 arg1) {
    s32 var_v1 = 0;

    if (arg0->flags & arg1) {
        var_v1 = 1;
    }
    return var_v1;
}

s32 Particle_LacksFlags(Particle* arg0, s32 arg1) {
    s32 var_v1 = 0;

    if (!(arg0->flags & arg1)) {
        var_v1 = 1;
    }
    return var_v1;
}

void Particle_EnableRendering(Particle* arg0) {
    Particle_SetFlags(arg0, 4);
}

void Particle_DisableRendering(Particle* arg0) {
    Particle_ClearFlags(arg0, 4);
}

s32 Particle_IsRenderingEnabled(Particle* arg0) {
    return Particle_HasFlags(arg0, 4);
}

void Particle_EnableFlag40(Particle* arg0) {
    Particle_SetFlags(arg0, 0x40);
}

void Particle_DisableFlag40(Particle* arg0) {
    Particle_ClearFlags(arg0, 0x40);
}

void Particle_HasFlag40(Particle* arg0) {
    Particle_HasFlags(arg0, 0x40);
}

void func_8213CBFC(s8 *arg0, s16 arg1) {
    M2C_FIELD(arg0, s8 *, 0xC3) = (s8) arg1;
}

s32 func_8213CC10(Particle* arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5) {
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

s32 func_8213CC10(Particle*, s16, s16, s16, s16, s16);

s32 func_8213CCEC(Particle* arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5) {
    s32 sp24 = func_8213CC10(arg0, arg1, arg2, arg3, arg4, arg5);

    if (sp24 != 0) {
        Particle_ClearFlags(arg0, 1);
        Particle_AdvanceLifecycle(arg0);
    }

    return sp24;
}

s32 func_8213CD60(Particle* arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5) {
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

s32 func_8213CD60(Particle*, s16, s16, s16, s16, s16);

s32 func_8213CE3C(Particle* arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5) {
    s32 sp24 = func_8213CD60(arg0, arg1, arg2, arg3, arg4, arg5);

    if (sp24 != 0) {
        Particle_ClearFlags(arg0, 1);
        Particle_AdvanceLifecycle(arg0);
    }

    return sp24;
}

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

s32 Particle_AnimateFramesForwardAndAdvanceLifecycle(Particle* arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5) {
    s32 sp24 = Particle_AnimateFramesPingPong(arg0, arg1, arg2, arg3, arg4, arg5);

    if (sp24 != 0) {
        Particle_AdvanceLifecycle(arg0);
    }

    return sp24;
}

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

s32 Particle_AnimateFramesReverseAndAdvanceLifecycle(Particle* arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5) {
    s32 sp24 = Particle_AnimateFramesReverseFirstPingPong(arg0, arg1, arg2, arg3, arg4, arg5);

    if (sp24 != 0) {
        Particle_AdvanceLifecycle(arg0);
    }
    return sp24;
}

void Particle_BeginPhase(Particle* arg0) {
    arg0->phase = 1;
    Particle_ClearFlags(arg0, 2);
}

void Particle_ResetPhase(Particle* arg0) {
    arg0->phase = 0;
    Particle_ClearFlags(arg0, 2);
}

void func_8213D284(s8 *arg0) {
    M2C_FIELD(arg0, s16 *, 0xB4) = (s16) (M2C_FIELD(arg0, s16 *, 0xB4) + 1);
}

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
 * @unverified Name was previously used only by callers of this address; the definition was still func_. Comment from Stadium 1.
 */
void Particle_SetPosition(Particle* arg0, f32 arg1, f32 arg2, f32 arg3) {
    M2C_FIELD(arg0, f32*, 0x34) = arg1 * gParticleRenderContext.scale.y;
    M2C_FIELD(arg0, f32*, 0x34 + 4) = arg2 * gParticleRenderContext.scale.y;
    M2C_FIELD(arg0, f32*, 0x34 + 8) = arg3 * gParticleRenderContext.scale.y;
}

void Particle_Field38_SetVecFromVec3fScaled_08C20(Particle* arg0, Vec3f arg1) {
    arg0->positionOffset.x = arg1.x * gParticleRenderContext.scale.y;
    arg0->positionOffset.y = arg1.y * gParticleRenderContext.scale.y;
    arg0->positionOffset.z = arg1.z * gParticleRenderContext.scale.y;
}

void func_8213D484(s8 *arg0, f32 arg1, f32 arg2, f32 arg3) {
    M2C_FIELD(arg0, f32 *, 0x34) = arg1;
    M2C_FIELD(arg0, f32 *, 0x38) = arg2;
    M2C_FIELD(arg0, f32 *, 0x3C) = arg3;
}

extern f32 D_FLT_8219A824;

void func_8213D4A4(s8 *arg0, f32 arg1) {
    M2C_FIELD(arg0, f32 *, 0x34) = (f32) (arg1 * D_FLT_8219A824);
}

extern f32 D_FLT_8219A824;

void func_8213D4BC(s8 *arg0, f32 arg1) {
    M2C_FIELD(arg0, f32 *, 0x38) = (f32) (arg1 * D_FLT_8219A824);
}

extern f32 D_FLT_8219A824;

void func_8213D4D4(s8 *arg0, f32 arg1) {
    M2C_FIELD(arg0, f32 *, 0x3C) = (f32) (arg1 * D_FLT_8219A824);
}

void Particle_Field38_AddVecScaledFromVec3f_08D78(Particle* arg0, Vec3f arg1) {
    arg0->positionOffset.x += arg1.x * gParticleRenderContext.scale.y;
    arg0->positionOffset.y += arg1.y * gParticleRenderContext.scale.y;
    arg0->positionOffset.z += arg1.z * gParticleRenderContext.scale.y;
}

void Particle_Field38_AddVecFromVec3f_08DD8(Particle* arg0, Vec3f arg1) {
    arg0->positionOffset.x += arg1.x;
    arg0->positionOffset.y += arg1.y;
    arg0->positionOffset.z += arg1.z;
}

void Particle_Field38_AddVecScaled_08E18(Particle* arg0, f32 arg1, f32 arg2, f32 arg3) {
    arg0->positionOffset.x += arg1 * gParticleRenderContext.scale.y;
    arg0->positionOffset.y += arg2 * gParticleRenderContext.scale.y;
    arg0->positionOffset.z += arg3 * gParticleRenderContext.scale.y;
}

extern f32 D_FLT_8219A824;

void func_8213D5E4(s8 *arg0, f32 arg1) {
    M2C_FIELD(arg0, f32 *, 0x34) = (f32) (M2C_FIELD(arg0, f32 *, 0x34) + (arg1 * D_FLT_8219A824));
}

extern f32 D_FLT_8219A824;

void func_8213D604(s8 *arg0, f32 arg1) {
    M2C_FIELD(arg0, f32 *, 0x38) = (f32) (M2C_FIELD(arg0, f32 *, 0x38) + (arg1 * D_FLT_8219A824));
}

extern f32 D_FLT_8219A824;

void func_8213D624(s8 *arg0, f32 arg1) {
    M2C_FIELD(arg0, f32 *, 0x3C) = (f32) (M2C_FIELD(arg0, f32 *, 0x3C) + (arg1 * D_FLT_8219A824));
}

void Particle_Field38_AddXZFromField94Y_08ED0(Particle* arg0, f32 arg1) {
    arg0->positionOffset.x += arg1 * SINS(arg0->rotation.y) * gParticleRenderContext.scale.y;
    arg0->positionOffset.z += arg1 * COSS(arg0->rotation.y) * gParticleRenderContext.scale.y;
}

void Particle_Field38_AddXZFromField94YOffset180_08F38(Particle* arg0, f32 arg1) {
    arg0->positionOffset.x += arg1 * SINS(arg0->rotation.y + 0x8000) * gParticleRenderContext.scale.y;
    arg0->positionOffset.z += arg1 * COSS(arg0->rotation.y + 0x8000) * gParticleRenderContext.scale.y;
}

void Particle_Field38_AddXZFromField94YOffset90_08FAC(Particle* arg0, f32 arg1) {
    arg0->positionOffset.x += arg1 * SINS(arg0->rotation.y + 0x4000) * gParticleRenderContext.scale.y;
    arg0->positionOffset.z += arg1 * COSS(arg0->rotation.y + 0x4000) * gParticleRenderContext.scale.y;
}

void Particle_Field38_AddXZFromField94YOffsetMinus90_0901C(Particle* arg0, f32 arg1) {
    arg0->positionOffset.x += arg1 * SINS(arg0->rotation.y - 0x4000) * gParticleRenderContext.scale.y;
    arg0->positionOffset.z += arg1 * COSS(arg0->rotation.y - 0x4000) * gParticleRenderContext.scale.y;
}

void Particle_AddVelocityFromDirVector(Particle* arg0, f32 arg1) {
    Vec3f sp1C;

    Particle_ComputeVectorFromRotationY(arg0, arg1, &sp1C);
    arg0->positionOffset.x += sp1C.x * gParticleRenderContext.scale.y;
    arg0->positionOffset.y += sp1C.y * gParticleRenderContext.scale.y;
    arg0->positionOffset.z += sp1C.z * gParticleRenderContext.scale.y;
}

void Particle_SetPositionFromRotationTemplate1(Particle* arg0, f32 arg1) {
    Vec3f sp1C;

    Particle_ComputeVectorFromRotationXYZAlt(arg0, arg1, &sp1C);
    Particle_Field38_SetVecFromVec3fScaled_08C20(arg0, sp1C);
}

void Particle_SetPositionFromRotationTemplate2(Particle* arg0, f32 arg1) {
    Vec3f sp1C;

    Particle_ComputeVectorFromRotationYZVariant(arg0, arg1, &sp1C);
    Particle_Field38_SetVecFromVec3fScaled_08C20(arg0, sp1C);
}

void Particle_AddPositionFromRotationTemplate1(Particle* arg0, f32 arg1) {
    Vec3f sp1C;

    Particle_ComputeVectorFromRotationXYZAlt(arg0, arg1, &sp1C);
    Particle_Field38_AddVecScaledFromVec3f_08D78(arg0, sp1C);
}

void Particle_AddPositionFromRotationTemplate2(Particle* arg0, f32 arg1) {
    Vec3f sp1C;

    Particle_ComputeVectorFromRotationYZVariant(arg0, arg1, &sp1C);
    Particle_Field38_AddVecScaledFromVec3f_08D78(arg0, sp1C);
}

void Particle_AddPositionRotatedVectorByYaw(Particle* arg0, Vec3f arg1) {
    Vec3f sp24;

    ParticleMath_RotateVec3fY(&sp24, arg1, arg0->rotation);
    Particle_Field38_AddVecScaledFromVec3f_08D78(arg0, sp24);
}

s32 func_82137DF4(M2C_UNK);                         /* extern */
extern f32 D_FLT_8219A824;

void func_8213DA64(s8 *arg0, M2C_UNK arg1) {
    M2C_FIELD(arg0, f32 *, 0x34) = (f32) ((f32) func_82137DF4(arg1) * D_FLT_8219A824);
}

s32 func_82137DF4(M2C_UNK);                         /* extern */
extern f32 D_FLT_8219A824;

void func_8213DAA4(s8 *arg0, M2C_UNK arg1) {
    M2C_FIELD(arg0, f32 *, 0x38) = (f32) ((f32) func_82137DF4(arg1) * D_FLT_8219A824);
}

s32 func_82137DF4(M2C_UNK);                         /* extern */
extern f32 D_FLT_8219A824;

void func_8213DAE4(s8 *arg0, M2C_UNK arg1) {
    M2C_FIELD(arg0, f32 *, 0x3C) = (f32) ((f32) func_82137DF4(arg1) * D_FLT_8219A824);
}

s32 func_82137DF4(M2C_UNK);                         /* extern */
extern f32 D_FLT_8219A824;

void func_8213DB24(s8 *arg0, M2C_UNK arg1, s32 arg2) {
    M2C_FIELD(arg0, f32 *, 0x34) = (f32) (((f32) func_82137DF4(arg1) * D_FLT_8219A824) + (f32) arg2);
}

s32 func_82137DF4(M2C_UNK);                         /* extern */
extern f32 D_FLT_8219A824;

void func_8213DB78(s8 *arg0, M2C_UNK arg1, s32 arg2) {
    M2C_FIELD(arg0, f32 *, 0x38) = (f32) (((f32) func_82137DF4(arg1) * D_FLT_8219A824) + (f32) arg2);
}

s32 func_82137DF4(M2C_UNK);                         /* extern */
extern f32 D_FLT_8219A824;

void func_8213DBCC(s8 *arg0, M2C_UNK arg1, s32 arg2) {
    M2C_FIELD(arg0, f32 *, 0x3C) = (f32) (((f32) func_82137DF4(arg1) * D_FLT_8219A824) + (f32) arg2);
}

s32 func_82137DF4(M2C_UNK);                         /* extern */
extern f32 D_FLT_8219A824;

void func_8213DC20(s8 *arg0, M2C_UNK arg1, s32 arg2) {
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

void func_8213DCA8(s8 *arg0, M2C_UNK arg1, s32 arg2) {
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

void func_8213DD30(s8 *arg0, M2C_UNK arg1, s32 arg2) {
    f32 temp_f0;

    temp_f0 = (f32) func_82137DF4(arg1);
    if (temp_f0 >= 0.0f) {
        M2C_FIELD(arg0, f32 *, 0x3C) = (f32) (((f32) arg2 + temp_f0) * D_FLT_8219A824);
        return;
    }
    M2C_FIELD(arg0, f32 *, 0x3C) = (f32) ((temp_f0 - (f32) arg2) * D_FLT_8219A824);
}

void Particle_SetRandomVelocityXYZ(Particle* arg0, s32 arg1, s32 arg2, s32 arg3) {
    Vec3f sp18;

    sp18.x = ParticleMath_RandomSigned(arg1);
    sp18.y = ParticleMath_RandomSigned(arg2);
    sp18.z = ParticleMath_RandomSigned(arg3);

    arg0->positionOffset.x = sp18.x * gParticleRenderContext.scale.y;
    arg0->positionOffset.y = sp18.y * gParticleRenderContext.scale.y;
    arg0->positionOffset.z = sp18.z * gParticleRenderContext.scale.y;
}

void func_8213DE50(Particle* arg0, s32 arg1, s32 arg2, s32 arg3) {
    Vec3f sp1C;

    sp1C.x = ParticleMath_RandomRange(arg1);
    sp1C.y = ParticleMath_RandomRange(arg2);
    sp1C.z = ParticleMath_RandomRange(arg3);

    arg0->positionOffset.x = sp1C.x * gParticleRenderContext.scale.y;
    arg0->positionOffset.y = sp1C.y * gParticleRenderContext.scale.y;
    arg0->positionOffset.z = sp1C.z * gParticleRenderContext.scale.y;
}

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

void func_8213E0A4(s8 *arg0, f32 arg1, f32 arg2, f32 arg3) {
    M2C_FIELD(arg0, f32 *, 0x64) = arg1;
    M2C_FIELD(arg0, f32 *, 0x68) = arg2;
    M2C_FIELD(arg0, f32 *, 0x6C) = arg3;
}

/**
 * @unverified Name was previously used only by callers of this address; the definition was still func_.
 */
void Particle_SetVelocity(Particle* arg0, f32 arg1, f32 arg2, f32 arg3) {
    M2C_FIELD(arg0, f32*, 0x4C) = arg1 * gParticleRenderContext.scale.y;
    M2C_FIELD(arg0, f32*, 0x4C + 4) = arg2 * gParticleRenderContext.scale.y;
    M2C_FIELD(arg0, f32*, 0x4C + 8) = arg3 * gParticleRenderContext.scale.y;
}

extern f32 D_FLT_8219A824;

void func_8213E104(s8 *arg0, f32 arg1) {
    M2C_FIELD(arg0, f32 *, 0x4C) = (f32) (arg1 * D_FLT_8219A824);
}

void Particle_Field50_SetXScaled_098E8(Particle* arg0, f32 arg1) {
    arg0->motionOffset.y = arg1 * gParticleRenderContext.scale.y;
}

void Particle_Field50_SetYScaled_09900(Particle* arg0, f32 arg1) {
    arg0->motionOffset.z = arg1 * gParticleRenderContext.scale.y;
}

void Particle_SetVelocityRandomDirection(Particle* arg0, f32 arg1) {
    ParticleMath_RandomDirection(&arg0->motionOffset, arg1 * gParticleRenderContext.scale.y);
}

void func_8213E184(Particle* arg0, f32 arg1, f32 arg2, f32 arg3) {
    M2C_FIELD(arg0, f32*, 0x4C) += arg1 * gParticleRenderContext.scale.y;
    M2C_FIELD(arg0, f32*, 0x50) += arg2 * gParticleRenderContext.scale.y;
    M2C_FIELD(arg0, f32*, 0x54) += arg3 * gParticleRenderContext.scale.y;
}

extern f32 D_FLT_8219A824;

void func_8213E1DC(s8 *arg0, f32 arg1) {
    M2C_FIELD(arg0, f32 *, 0x4C) = (f32) (M2C_FIELD(arg0, f32 *, 0x4C) + (arg1 * D_FLT_8219A824));
}

void Particle_Field50_AddXScaled_099C0(Particle* arg0, f32 arg1) {
    arg0->motionOffset.y += arg1 * gParticleRenderContext.scale.y;
}

void Particle_Field50_AddYScaled_099E0(Particle* arg0, f32 arg1) {
    arg0->motionOffset.z += arg1 * gParticleRenderContext.scale.y;
}

void Particle_Field50_SubVecScaled_09A20(Particle* arg0, f32 arg1, f32 arg2, f32 arg3) {
    arg0->motionOffset.x -= arg1 * gParticleRenderContext.scale.y;
    arg0->motionOffset.y -= arg2 * gParticleRenderContext.scale.y;
    arg0->motionOffset.z -= arg3 * gParticleRenderContext.scale.y;
}

extern f32 D_FLT_8219A824;

void func_8213E294(s8 *arg0, f32 arg1) {
    M2C_FIELD(arg0, f32 *, 0x4C) = (f32) (M2C_FIELD(arg0, f32 *, 0x4C) - (arg1 * D_FLT_8219A824));
}

void Particle_Field50_SubXScaled_09A78(Particle* arg0, f32 arg1) {
    arg0->motionOffset.y -= arg1 * gParticleRenderContext.scale.y;
}

void Particle_Field50_SubYScaled_09A98(Particle* arg0, f32 arg1) {
    arg0->motionOffset.z -= arg1 * gParticleRenderContext.scale.y;
}

s32 func_8213E2F4(Particle* arg0, f32 arg1) {
    return ParticleMath_ApproachFloat(&arg0->motionOffset.x, arg1 * gParticleRenderContext.scale.y, arg0->motionTarget.x);
}

s32 Particle_Field50_ApproachXToField5C_09AD8(Particle* arg0, f32 arg1) {
    return ParticleMath_ApproachFloat(&arg0->motionOffset.y, arg1 * gParticleRenderContext.scale.y, arg0->motionTarget.y);
}

s32 Particle_Field50_ApproachYToField5C_09B18(Particle* arg0, f32 arg1) {
    return ParticleMath_ApproachFloat(&arg0->motionOffset.z, arg1 * gParticleRenderContext.scale.y, arg0->motionTarget.z);
}

void func_8213E3B4(s8 *arg0) {
    M2C_FIELD(arg0, f32 *, 0x4C) = (f32) M2C_FIELD(arg0, f32 *, 0x78);
    M2C_FIELD(arg0, f32 *, 0x50) = (f32) M2C_FIELD(arg0, f32 *, 0x7C);
    M2C_FIELD(arg0, f32 *, 0x54) = (f32) M2C_FIELD(arg0, f32 *, 0x80);
}

void func_8213E3D0(s8 *arg0) {
    M2C_FIELD(arg0, f32 *, 0x4C) = (f32) M2C_FIELD(arg0, f32 *, 0x78);
    M2C_FIELD(arg0, f32 *, 0x54) = (f32) M2C_FIELD(arg0, f32 *, 0x80);
}

void func_8213E3E4(s8 *arg0) {
    M2C_FIELD(arg0, f32 *, 0x4C) = (f32) M2C_FIELD(arg0, f32 *, 0x78);
    M2C_FIELD(arg0, f32 *, 0x50) = (f32) M2C_FIELD(arg0, f32 *, 0x7C);
}

M2C_UNK func_8213E3F8(s32 arg0) {
    ((Particle*)arg0)->motionOffset.x += ((Particle*)arg0)->motionStep.x;
    ((Particle*)arg0)->motionOffset.y += ((Particle*)arg0)->motionStep.y;
    ((Particle*)arg0)->motionOffset.z += ((Particle*)arg0)->motionStep.z;
}

/**
 * @unverified Name was previously used only by callers of this address; the definition was still func_.
 */
void Particle_Field50_AddXZFromField7C_09C10(Particle* arg0) {
    M2C_FIELD(arg0, f32*, 0x4C) += M2C_FIELD(arg0, f32*, 0x78);
    M2C_FIELD(arg0, f32*, 0x54) += M2C_FIELD(arg0, f32*, 0x80);
}

/**
 * @unverified Name was previously used only by callers of this address; the definition was still func_.
 */
void Particle_Field50_AddVecFromField7C_09BDC(Particle* arg0) {
    arg0->motionOffset.x += arg0->motionStep.x;
    arg0->motionOffset.y += arg0->motionStep.y;
}

void func_8213E474(s8 *arg0)
{
  *((f32 *) (((s8 *) arg0) + 0x4C)) = (f32) ((*((f32 *) (((s8 *) arg0) + 0x78))) + (*((f32 *) (((s8 *) arg0) + 0x4C)))); // FAKE: decomp slop, raw pointer casts stand in for struct fields
}

void Particle_Field50_AddXFromField7C_09C58(Particle* arg0) {
    arg0->motionOffset.y += arg0->motionStep.y;
}

void Particle_Field50_AddYFromField7C_09C6C(Particle* arg0) {
    arg0->motionOffset.z += arg0->motionStep.z;
}

void Particle_AddVelocityXYFromRotationZViaImpulse(Particle* arg0) {
    Particle_Field7C_SetXYFromField74AngleZ_0B23C(arg0);
    Particle_Field50_AddXYFromField7C_09C34(arg0);
}

M2C_UNK func_8213FB14();                            /* extern */

void func_8213E4D8(s32 arg0) {
    func_8213FB14();
    Particle_Field50_AddXZFromField7C_09C10(arg0);
}

void Particle_AddVelocityFromRotationTemplate2(Particle* arg0) {
    Particle_Field7C_SetVecFromField74AnglesXZ_0B330(arg0);
    Particle_Field50_AddVecFromField7C_09BDC(arg0);
}

M2C_UNK func_8213E3F8(s32);                         /* extern */
M2C_UNK func_8213FB50();                            /* extern */

void func_8213E528(s32 arg0) {
    func_8213FB50();
    func_8213E3F8(arg0);
}

M2C_UNK func_8213E3F8(s32);                         /* extern */

void Particle_MotionStep_SetVecFromField74AnglesXZ(Particle* arg0);

void func_8213E550(s32 arg0) {
    Particle_MotionStep_SetVecFromField74AnglesXZ((Particle*)arg0);
    func_8213E3F8(arg0);
}

M2C_UNK func_8213E3F8(s32);                         /* extern */
M2C_UNK func_8213FC48();                            /* extern */

void func_8213E578(s32 arg0) {
    func_8213FC48();
    func_8213E3F8(arg0);
}

M2C_UNK func_8213E3F8(s32);                         /* extern */
M2C_UNK func_8213FCC8();                            /* extern */

void func_8213E5A0(s32 arg0) {
    func_8213FCC8();
    func_8213E3F8(arg0);
}

M2C_UNK func_8213E3F8(s32);                         /* extern */
M2C_UNK func_8213FE04();                            /* extern */

void func_8213E5C8(s32 arg0) {
    func_8213FE04();
    func_8213E3F8(arg0);
}

M2C_UNK func_8213E3F8(s32);                         /* extern */
M2C_UNK func_8213FD3C();                            /* extern */

void func_8213E5F0(s32 arg0) {
    func_8213FD3C();
    func_8213E3F8(arg0);
}

M2C_UNK func_8213E3F8(s32);                         /* extern */
M2C_UNK func_8213FED4();                            /* extern */

void func_8213E618(s32 arg0) {
    func_8213FED4();
    func_8213E3F8(arg0);
}

M2C_UNK func_8213E3F8(s32);                         /* extern */
M2C_UNK func_8213FED4();                            /* extern */

void func_8213E640(s32 arg0) {
    func_8213FED4();
    func_8213E3F8(arg0);
}

void Particle_AddVelocityXZFromRotationY(Particle* arg0) {
    arg0->motionStep.x = arg0->stepMagnitude * SINS(arg0->rotation.y);
    arg0->motionStep.z = arg0->stepMagnitude * COSS(arg0->rotation.y);

    Particle_Field50_AddXZFromField7C_09C10(arg0);
}

void Particle_AddVelocityXZFromRotationYPlusHalfTurn(Particle* arg0) {
    arg0->motionStep.x = arg0->stepMagnitude * SINS(arg0->rotation.y + 0x8000);
    arg0->motionStep.z = arg0->stepMagnitude * COSS(arg0->rotation.y + 0x8000);

    Particle_Field50_AddXZFromField7C_09C10(arg0);
}

void Particle_AddVelocityXZFromRotationYPlusHalfTurnFromArgument(Particle* arg0, f32 arg1) {
    arg0->motionStep.x = SINS(arg0->rotation.y + 0x8000) * arg1;
    arg0->motionStep.z = COSS(arg0->rotation.y + 0x8000) * arg1;

    Particle_Field50_AddXZFromField7C_09C10(arg0);
}

M2C_UNK func_8213E488();                            /* extern */

void func_8213E77C(s8 *arg0) {
    M2C_FIELD(arg0, f32 *, 0x7C) = (f32) M2C_FIELD(arg0, f32 *, 0x70);
    func_8213E488();
}

s32 Particle_Field50_AddNegField74Y_CheckField2CYNonPositive_09F84(Particle* arg0) {
    s32 sp1C = 0;

    arg0->motionStep.y = -arg0->stepMagnitude;
    func_8213E488(arg0);

    if (arg0->worldPosition.y <= 0.0f) {
        sp1C = 1;
    }
    return sp1C;
}


s32 Particle_Field74_AdvanceAndAddNegY_CheckField2CYNonPositive_09FD8(Particle* arg0) {
    s32 sp1C = 0;

    arg0->stepMagnitude += arg0->magnitudeStep;
    arg0->motionStep.y = -arg0->stepMagnitude;

    func_8213E488(arg0);

    if (arg0->worldPosition.y <= 0.0f) {
        sp1C = 1;
    }
    return sp1C;
}

void Particle_SetVelocityTarget(Particle* arg0, f32 arg1, f32 arg2, f32 arg3) {
    arg0->motionTarget.x = arg1 * gParticleRenderContext.scale.y;
    arg0->motionTarget.y = arg2 * gParticleRenderContext.scale.y;
    arg0->motionTarget.z = arg3 * gParticleRenderContext.scale.y;
}

void Particle_Field50_SetZScaled_09918(Particle* arg0, f32 arg1) {
    arg0->motionTarget.x = arg1 * gParticleRenderContext.scale.y;
}

extern f32 D_FLT_8219A824;

void func_8213E8B0(s8 *arg0, f32 arg1) {
    M2C_FIELD(arg0, f32 *, 0x5C) = (f32) (arg1 * D_FLT_8219A824);
}

extern f32 D_FLT_8219A824;

void func_8213E8C8(s8 *arg0, f32 arg1) {
    M2C_FIELD(arg0, f32 *, 0x60) = (f32) (arg1 * D_FLT_8219A824);
}

s32 Particle_Field5C_ApproachY_0A0C4(Particle* arg0, f32 arg1, f32 arg2) {
    return ParticleMath_ApproachFloat(&arg0->motionTarget.y, arg1 * gParticleRenderContext.scale.y, arg2 * gParticleRenderContext.scale.y);
}

f32 ParticleMath_ScaleApproachStep(f32 arg0) {
    return arg0 * 0.4f;
}

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

void Particle_Field9A_SetVecFromVec3s_0A37C(Particle* arg0, Vec3s arg1) {
    M2C_FIELD(arg0, s16*, 0x90) = arg1.x;
    M2C_FIELD(arg0, s16*, 0x92) = arg1.y;
    M2C_FIELD(arg0, s16*, 0x94) = arg1.z;
}

void func_8213EA8C(s8 *arg0, s16 arg1, s16 arg2, s16 arg3) {
    M2C_FIELD(arg0, s16 *, 0x90) = arg1;
    M2C_FIELD(arg0, s16 *, 0x92) = arg2;
    M2C_FIELD(arg0, s16 *, 0x94) = arg3;
}

void func_8213EAC0(s8 *arg0, s16 arg1) {
    M2C_FIELD(arg0, s16 *, 0x90) = arg1;
}

void func_8213EAD4(s8 *arg0, s16 arg1) {
    M2C_FIELD(arg0, s16 *, 0x92) = arg1;
}

void func_8213EAE8(s8 *arg0, s16 arg1) {
    M2C_FIELD(arg0, s16 *, 0x94) = arg1;
}

void func_8213EAFC(s8 *arg0) {
    M2C_FIELD(arg0, s16 *, 0x90) = (s16) (M2C_FIELD(arg0, s16 *, 0x90) + 0x8000);
    M2C_FIELD(arg0, s16 *, 0x92) = (s16) (M2C_FIELD(arg0, s16 *, 0x92) + 0x8000);
    M2C_FIELD(arg0, s16 *, 0x94) = (s16) (M2C_FIELD(arg0, s16 *, 0x94) + 0x8000);
}

void func_8213EB28(s8 *arg0) {
    M2C_FIELD(arg0, s16 *, 0x90) = (s16) (M2C_FIELD(arg0, s16 *, 0x90) + 0x8000);
}

void func_8213EB3C(s8 *arg0) {
    M2C_FIELD(arg0, s16 *, 0x92) = (s16) (M2C_FIELD(arg0, s16 *, 0x92) + 0x8000);
}

void func_8213EB50(s8 *arg0) {
    M2C_FIELD(arg0, s16 *, 0x94) = (s16) (M2C_FIELD(arg0, s16 *, 0x94) + 0x8000);
}

void func_8213EB64(s8 *arg0, s16 arg1, s16 arg2, s16 arg3) {
    M2C_FIELD(arg0, s16 *, 0x96) = arg1;
    M2C_FIELD(arg0, s16 *, 0x98) = arg2;
    M2C_FIELD(arg0, s16 *, 0x9A) = arg3;
}

void func_8213EB98(Particle* arg0, Vec3s arg1) {
    arg0->rotationStep.x = arg1.x;
    arg0->rotationStep.y = arg1.y;
    arg0->rotationStep.z = arg1.z;
}

void func_8213EBBC(s8 *arg0, s16 arg1, s16 arg2) {
    M2C_FIELD(arg0, s16 *, 0x96) = arg1;
    M2C_FIELD(arg0, s16 *, 0x98) = arg2;
}

void func_8213EBE0(s8 *arg0, s16 arg1) {
    M2C_FIELD(arg0, s16 *, 0x96) = arg1;
}

void func_8213EBF4(s8 *arg0, s16 arg1) {
    M2C_FIELD(arg0, s16 *, 0x98) = arg1;
}

void func_8213EC08(s8 *arg0, s16 arg1) {
    M2C_FIELD(arg0, s16 *, 0x9A) = arg1;
}

void func_8213EC1C(s8 *arg0, s16 arg1) {
    M2C_FIELD(arg0, s16 *, 0x9C) = arg1;
}

void func_8213EC30(s8 *arg0, s16 arg1) {
    M2C_FIELD(arg0, s16 *, 0x9E) = arg1;
}

void Particle_SetRotationTargetXY(Particle* arg0, s16 arg1, s16 arg2) {
    Particle_FieldA0_SetX_0A400(arg0, arg1);
    Particle_FieldA0_SetY_0A414(arg0, arg2);
}

void func_8213EC80(s8 *arg0) {
    M2C_FIELD(arg0, s16 *, 0x9C) = (s16) M2C_FIELD(arg0, s16 *, 0x90);
    M2C_FIELD(arg0, s16 *, 0x9E) = (s16) M2C_FIELD(arg0, s16 *, 0x92);
    M2C_FIELD(arg0, s16 *, 0xA0) = (s16) M2C_FIELD(arg0, s16 *, 0x94);
}

void func_8213EC9C(Particle* arg0) {
    arg0->rotation.x += arg0->rotationStep.x;
    arg0->rotation.y += arg0->rotationStep.y;
    arg0->rotation.z += arg0->rotationStep.z;
}

void func_8213ECD0(s8 *arg0)
{
  s16 *new_var; // FAKE: permuter temp
  *((s16 *) (((0, (s8 *) arg0)) + 0x90)) = (s16) ((*(new_var = (s16 *) (((s8 *) arg0) + 0x96))) + (*((s16 *) (((s8 *) arg0) + 0x90)))); // FAKE: decomp slop, raw pointer casts stand in for struct fields
}

void func_8213ECE4(s8 *arg0)
{
  *((s16 *) (((s8 *) arg0) + 0x92)) = (s16) ((*((s16 *) (((s8 *) arg0) + 0x98))) + (*((s16 *) (((s8 *) arg0) + 0x92)))); // FAKE: decomp slop, raw pointer casts stand in for struct fields
 if (0) { }  // karodo
}

void Particle_Field94_AddXFromField9A_0A4B4(Particle* arg0) {
    arg0->rotation.z += arg0->rotationStep.z;
}

void Particle_Field94_AddVecFromVec3s_0A4F0(Particle* arg0, Vec3s arg1) {
    arg0->rotation.x += arg1.x;
    arg0->rotation.y += arg1.y;
    arg0->rotation.z += arg1.z;
}

void func_8213ED48(s8 *arg0, s16 arg1, s16 arg2, s16 arg3) {
    M2C_FIELD(arg0, s16 *, 0x90) = (s16) (M2C_FIELD(arg0, s16 *, 0x90) + arg1);
    M2C_FIELD(arg0, s16 *, 0x92) = (s16) (M2C_FIELD(arg0, s16 *, 0x92) + arg2);
    M2C_FIELD(arg0, s16 *, 0x94) = (s16) (M2C_FIELD(arg0, s16 *, 0x94) + arg3);
}

void func_8213ED94(s8 *arg0, s16 arg1) {
    M2C_FIELD(arg0, s16 *, 0x90) = (s16) (M2C_FIELD(arg0, s16 *, 0x90) + arg1);
}

void func_8213EDB0(s8 *arg0, s16 arg1) {
    M2C_FIELD(arg0, s16 *, 0x92) = (s16) (M2C_FIELD(arg0, s16 *, 0x92) + arg1);
}

void func_8213EDCC(s8 *arg0, s16 arg1) {
    M2C_FIELD(arg0, s16 *, 0x94) = (s16) (M2C_FIELD(arg0, s16 *, 0x94) + arg1);
}

void func_8213EDE8(s8 *arg0, s16 arg1, s16 arg2) {
    M2C_FIELD(arg0, s16 *, 0x9C) = (s16) (M2C_FIELD(arg0, s16 *, 0x9C) + arg1);
    M2C_FIELD(arg0, s16 *, 0x9E) = (s16) (M2C_FIELD(arg0, s16 *, 0x9E) + arg2);
}

void Particle_Field94_SubVecFromVec3s_0A600(Particle* arg0, Vec3s arg1) {
    arg0->rotation.x -= arg1.x;
    arg0->rotation.y -= arg1.y;
    arg0->rotation.z -= arg1.z;
}

void func_8213EE58(s8 *arg0, s16 arg1) {
    M2C_FIELD(arg0, s16 *, 0x90) = (s16) (M2C_FIELD(arg0, s16 *, 0x90) - arg1);
}

void func_8213EE74(s8 *arg0, s16 arg1) {
    M2C_FIELD(arg0, s16 *, 0x92) = (s16) (M2C_FIELD(arg0, s16 *, 0x92) - arg1);
}

void Particle_Field94_SubX_0A63C(Particle* arg0, s16 arg1) {
    arg0->rotation.z -= arg1;
}

M2C_UNK func_82137940(s8 *, s16, s16, s8 *);    /* extern */

void func_8213EEAC(s8 *arg0) {
    func_82137940(arg0 + 0x90, M2C_FIELD(arg0, s16 *, 0x9C), M2C_FIELD(arg0, s16 *, 0x96), arg0);
}

M2C_UNK func_82137940(s8 *, s16, s16, s8 *);    /* extern */

void func_8213EED8(s8 *arg0) {
    func_82137940(arg0 + 0x92, M2C_FIELD(arg0, s16 *, 0x9E), M2C_FIELD(arg0, s16 *, 0x98), arg0);
}

M2C_UNK func_82137940(s8 *, s16, s16, s8 *);    /* extern */

void func_8213EF04(s8 *arg0) {
    func_82137940(arg0 + 0x94, M2C_FIELD(arg0, s16 *, 0xA0), M2C_FIELD(arg0, s16 *, 0x9A), arg0);
}

void Particle_ApproachRotationTargetXY(Particle* arg0) {
    Particle_ApproachRotationTargetX(arg0);
    Particle_ApproachRotationTargetY(arg0);
}

void Particle_ApproachRotationTargetXYZ(Particle* arg0) {
    Particle_ApproachRotationTargetX(arg0);
    Particle_ApproachRotationTargetY(arg0);
    Particle_ApproachRotationTargetZ(arg0);
}

void Particle_ApproachRotationXTo(Particle* arg0, s16 arg1, s16 arg2) {
    ParticleMath_ApproachAngle(&arg0->rotation.x, arg1, arg2);
}

void func_8213EFC0(Particle* arg0, s16 arg1, s16 arg2) {
    ParticleMath_ApproachAngle(&arg0->rotation.y, arg1, arg2);
}

s32 func_8213EFF8(Particle* arg0, s32 arg1, s32 arg2) {
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

s32 func_8213F02C(Particle* arg0, s32 arg1, s32 arg2) {
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

void Particle_AddRotationRandomSignedXY(Particle* arg0, s32 arg1, s32 arg2) {
    Particle_Field94_AddX_0A578(arg0, ParticleMath_RandomSigned(arg1));
    Particle_Field94_AddY_0A594(arg0, ParticleMath_RandomSigned(arg2));
}

void Particle_AddRotationRandomSignedXYWithXHalfTurn(Particle* arg0, s32 arg1, s32 arg2) {
    Particle_Field94_AddX_0A578(arg0, ParticleMath_RandomSignedOffset(arg1, 0x8000));
    Particle_Field94_AddY_0A594(arg0, ParticleMath_RandomSigned(arg2));
}

void Particle_AddRotationRandomSignedY(Particle* arg0, s32 arg1) {
    Particle_Field94_AddY_0A594(arg0, ParticleMath_RandomSigned(arg1));
}

void Particle_AddRotationRandomSignedYWithHalfTurn(Particle* arg0, s32 arg1) {
    Particle_Field94_AddY_0A594(arg0, ParticleMath_RandomSignedOffset(arg1, 0x8000));
}

void Particle_AddRotationRandomSignedXWithFixedYQuarterTurn(Particle* arg0) {
    Particle_Field94_AddX_0A578(arg0, ParticleMath_RandomSigned(0x10000));
    Particle_Field94_AddY_0A594(arg0, 0x4000);
}

extern struct ActivePokemon* D_8219A818;

s16 BattleAnim_GetParticleAngleYToTertiaryOwner(Particle* arg0) {
    Vec3f sp24;
    s16 ret;

    BattleAnim_GetOwnerDefaultAnchorPosition(D_8219A818, &sp24);
    ret = ParticleMath_AngleYBetweenPoints(arg0->origin, sp24) + arg0->rotation.y;
    return ret;
}

void Particle_ComputeVectorFromRotationY(Particle* arg0, f32 arg1, Vec3f* arg2) {
    arg2->x = SINS(arg0->rotation.y) * arg1;
    arg2->y = 0.0f;
    arg2->z = COSS(arg0->rotation.y) * arg1;
}

void Particle_ComputeVectorFromRotationXY(Particle* arg0, f32 arg1, Vec3f* arg2) {
    arg2->x = arg1 * COSS(arg0->rotation.x) * SINS(arg0->rotation.y);
    arg2->y = -arg1 * SINS(arg0->rotation.x);
    arg2->z = arg1 * COSS(arg0->rotation.x) * COSS(arg0->rotation.y);
}

void Particle_ComputeVectorFromRotationXZ(Particle* arg0, f32 arg1, Vec3f* arg2) {
    arg2->x = arg1 * SINS(arg0->rotation.x) * SINS(arg0->rotation.z);
    arg2->y = -arg1 * SINS(arg0->rotation.x) * COSS(arg0->rotation.z);
    arg2->z = arg1 * COSS(arg0->rotation.x);
}

void Particle_ComputeVectorFromRotationXYZAlt(Particle* arg0, f32 arg1, Vec3f* arg2) {
    arg2->x = arg1 * (SINS(arg0->rotation.x) * COSS(arg0->rotation.y) * SINS(arg0->rotation.z) +
                      COSS(arg0->rotation.x) * SINS(arg0->rotation.y));
    arg2->y = -arg1 * SINS(arg0->rotation.x) * COSS(arg0->rotation.z);
    arg2->z = arg1 * (COSS(arg0->rotation.x) * COSS(arg0->rotation.y) -
                      SINS(arg0->rotation.x) * SINS(arg0->rotation.y) * SINS(arg0->rotation.z));
}

void Particle_ComputeVectorFromRotationYZVariant(Particle* arg0, f32 arg1, Vec3f* arg2) {
    arg2->x = arg1 * (SINS(arg0->rotation.y) * COSS(arg0->rotation.z) +
                      SINS(arg0->rotation.x) * COSS(arg0->rotation.y) * SINS(arg0->rotation.z));
    arg2->y = arg1 * (SINS(arg0->rotation.y) * SINS(arg0->rotation.z) -
                      SINS(arg0->rotation.x) * COSS(arg0->rotation.y) * COSS(arg0->rotation.z));
    arg2->z = arg1 * (COSS(arg0->rotation.x) * COSS(arg0->rotation.y));
}

extern f32 D_FLT_8219A824;

void func_8213F628(s8 *arg0, f32 arg1) {
    M2C_FIELD(arg0, f32 *, 0x70) = (f32) (arg1 * D_FLT_8219A824);
}

extern f32 D_FLT_8219A824;

void func_8213F640(s8 *arg0, f32 arg1) {
    M2C_FIELD(arg0, f32 *, 0x74) = (f32) (arg1 * D_FLT_8219A824);
}

s32 func_8213F658(Particle* arg0, f32 arg1, f32 arg2) {
    return ParticleMath_ApproachFloat(&arg0->stepMagnitude, arg1 * gParticleRenderContext.scale.y, arg2 * gParticleRenderContext.scale.y);
}

/**
 * Approach stepMagnitude, magnitudeStep using the stored or supplied target and step.
 * @unverified Name and comment from Stadium 1, matched by code similarity.
 */
s32 Particle_StepMagnitude_ApproachUsingMagnitudeStep(Particle* arg0, f32 arg1) {
    return ParticleMath_ApproachFloat(&arg0->stepMagnitude, arg1 * gParticleRenderContext.scale.y, arg0->magnitudeStep);
}

s32 Particle_Field74_Approach_0ADBC(Particle* arg0, f32 arg1, f32 arg2) {
    return ParticleMath_ApproachFloat(&arg0->magnitudeStep, arg1 * gParticleRenderContext.scale.y, arg2 * gParticleRenderContext.scale.y);
}

void func_8213F720(Particle* arg0, Vec3f arg1) {
    M2C_FIELD(arg0, f32*, 0x78) = arg1.x * gParticleRenderContext.scale.y;
    M2C_FIELD(arg0, f32*, 0x7C) = arg1.y * gParticleRenderContext.scale.y;
    M2C_FIELD(arg0, f32*, 0x80) = arg1.z * gParticleRenderContext.scale.y;
}

/**
 * @unverified Name was previously used only by callers of this address; the definition was still func_.
 */
void Particle_SetVelocityImpulse(Particle* arg0, f32 arg1, f32 arg2, f32 arg3) {
    M2C_FIELD(arg0, f32*, 0x78) = arg1 * gParticleRenderContext.scale.y;
    M2C_FIELD(arg0, f32*, 0x78 + 4) = arg2 * gParticleRenderContext.scale.y;
    M2C_FIELD(arg0, f32*, 0x78 + 8) = arg3 * gParticleRenderContext.scale.y;
}

extern f32 D_FLT_8219A824;

void func_8213F7A8(s8 *arg0, f32 arg1) {
    M2C_FIELD(arg0, f32 *, 0x78) = (f32) (arg1 * D_FLT_8219A824);
}

extern f32 D_FLT_8219A824;

void func_8213F7C0(s8 *arg0, f32 arg1) {
    M2C_FIELD(arg0, f32 *, 0x7C) = (f32) (arg1 * D_FLT_8219A824);
}

extern f32 D_FLT_8219A824;

void func_8213F7D8(s8 *arg0, f32 arg1) {
    M2C_FIELD(arg0, f32 *, 0x80) = (f32) (arg1 * D_FLT_8219A824);
}

s32 func_8213F7F0(Particle* arg0, f32 arg1, f32 arg2) {
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

void func_8213F9E8(s8 *arg0, f32 arg1) {
    M2C_FIELD(arg0, f32 *, 0x78) = (f32) (M2C_FIELD(arg0, f32 *, 0x78) * arg1);
    M2C_FIELD(arg0, f32 *, 0x7C) = (f32) (M2C_FIELD(arg0, f32 *, 0x7C) * arg1);
    M2C_FIELD(arg0, f32 *, 0x80) = (f32) (M2C_FIELD(arg0, f32 *, 0x80) * arg1);
}

/**
 * @unverified Name was previously used only by callers of this address; the definition was still func_.
 */
s32 Particle_Field7C_ApproachY_0B180(Particle* arg0, f32 arg1, f32 arg2) {
    return ParticleMath_ApproachFloat(&arg0->motionStep.y, arg1 * gParticleRenderContext.scale.y, arg2 * gParticleRenderContext.scale.y);
}

void Particle_Field7C_SetXFromField74AngleY_0B1EC(Particle* arg0) {
    M2C_FIELD(arg0, f32*, 0x7C) = COSS(M2C_FIELD(arg0, u16*, 0x90)) * arg0->stepMagnitude;
}

void func_8213FA88(Particle* arg0) {
    M2C_FIELD(arg0, f32*, 0x78) = arg0->stepMagnitude * SINS(M2C_FIELD(arg0, u16*, 0x92));
}

void Particle_Field7C_SetYFromField74AngleX_0B1C4(Particle* arg0) {
    M2C_FIELD(arg0, f32*, 0x80) = COSS(M2C_FIELD(arg0, u16*, 0x92)) * arg0->stepMagnitude;
}

/**
 * @unverified Name was previously used only by callers of this address; the definition was still func_.
 */
void Particle_Field7C_SetVecFromField74AnglesXZ_0B330(Particle* arg0) {
    M2C_FIELD(arg0, f32*, 0x78) = arg0->stepMagnitude * COSS(M2C_FIELD(arg0, u16*, 0x94));
    M2C_FIELD(arg0, f32*, 0x7C) = arg0->stepMagnitude * SINS(M2C_FIELD(arg0, u16*, 0x94));
}

void Particle_Field7C_SetXYFromField74AngleZ_0B23C(Particle* arg0) {
    M2C_FIELD(arg0, f32*, 0x78) = SINS(M2C_FIELD(arg0, u16*, 0x92)) * arg0->stepMagnitude;
    M2C_FIELD(arg0, f32*, 0x80) = COSS(M2C_FIELD(arg0, u16*, 0x92)) * arg0->stepMagnitude;
}

void Particle_Field7C_SetVecFromField74AnglesXY_0B2B4(Particle* arg0) {
    arg0->motionStep.x = arg0->stepMagnitude * COSS(arg0->rotation.x) * SINS(arg0->rotation.y);
    arg0->motionStep.y = -arg0->stepMagnitude * SINS(arg0->rotation.x);
    arg0->motionStep.z = arg0->stepMagnitude * COSS(arg0->rotation.x) * COSS(arg0->rotation.y);
}

/**
 * Evaluate the explicit trigonometric component formula and store/add the resulting motion term.
 * @unverified Name and comment from Stadium 1, matched by code similarity.
 */
void Particle_MotionStep_SetVecFromField74AnglesXZ(Particle* arg0) {
    arg0->motionStep.x = arg0->stepMagnitude * SINS(arg0->rotation.x) * SINS(arg0->rotation.z);
    arg0->motionStep.y = -arg0->stepMagnitude * SINS(arg0->rotation.x) * COSS(arg0->rotation.z);
    arg0->motionStep.z = arg0->stepMagnitude * COSS(arg0->rotation.x);
}

void Particle_Field7C_SetVecFromField74AnglesXYAlt_0B3AC(Particle* arg0) {
    arg0->motionStep.x = arg0->stepMagnitude * SINS(arg0->rotation.y);
    arg0->motionStep.y = -arg0->stepMagnitude * SINS(arg0->rotation.x) * COSS(arg0->rotation.y);
    arg0->motionStep.z = arg0->stepMagnitude * COSS(arg0->rotation.x) * COSS(arg0->rotation.y);
}

void Particle_Field7C_SetVecFromField74AnglesYZ_0B42C(Particle* arg0) {
    arg0->motionStep.x = arg0->stepMagnitude * SINS(arg0->rotation.y) * COSS(arg0->rotation.z);
    arg0->motionStep.y = arg0->stepMagnitude * SINS(arg0->rotation.y) * SINS(arg0->rotation.z);
    arg0->motionStep.z = COSS(arg0->rotation.y);
}

void Particle_Field7C_SetVecFromField74AnglesXYZ_0B4A0(Particle* arg0) {
    arg0->motionStep.x = arg0->stepMagnitude * (COSS(arg0->rotation.x) * SINS(arg0->rotation.y) * COSS(arg0->rotation.z) +
                                     SINS(arg0->rotation.x) * SINS(arg0->rotation.z));
    arg0->motionStep.y = -arg0->stepMagnitude * (COSS(arg0->rotation.x) * SINS(arg0->rotation.y) * SINS(arg0->rotation.z) -
                                      SINS(arg0->rotation.x) * COSS(arg0->rotation.z));
    arg0->motionStep.z = arg0->stepMagnitude * (COSS(arg0->rotation.x) * COSS(arg0->rotation.y));
}

void Particle_Field7C_SetVecFromField74AnglesXYZAlt_0B568(Particle* arg0) {
    arg0->motionStep.x = arg0->stepMagnitude * (SINS(arg0->rotation.x) * COSS(arg0->rotation.y) * SINS(arg0->rotation.z) +
                                     COSS(arg0->rotation.x) * SINS(arg0->rotation.y));
    arg0->motionStep.y = -arg0->stepMagnitude * SINS(arg0->rotation.x) * COSS(arg0->rotation.z);

    arg0->motionStep.z = arg0->stepMagnitude * (-SINS(arg0->rotation.x) * SINS(arg0->rotation.y) * SINS(arg0->rotation.z) +
                                     COSS(arg0->rotation.x) * COSS(arg0->rotation.y));
}

void Particle_Field7C_SetVecFromField74AnglesYZAlt_0B638(Particle* arg0) {
    arg0->motionStep.x = arg0->stepMagnitude * SINS(arg0->rotation.y) * COSS(arg0->rotation.z);
    arg0->motionStep.y = arg0->stepMagnitude * (COSS(arg0->rotation.x) * SINS(arg0->rotation.y) * SINS(arg0->rotation.z) -
                                     SINS(arg0->rotation.x) * COSS(arg0->rotation.y));
    arg0->motionStep.z = arg0->stepMagnitude * (SINS(arg0->rotation.x) * SINS(arg0->rotation.y) * SINS(arg0->rotation.z) +
                                     COSS(arg0->rotation.x) * COSS(arg0->rotation.y));
}

void Particle_Field7C_SetVecFromField74AnglesYZVariant_0B700(Particle* arg0) {
    arg0->motionStep.x = arg0->stepMagnitude * (SINS(arg0->rotation.y) * COSS(arg0->rotation.z) +
                                     SINS(arg0->rotation.x) * COSS(arg0->rotation.y) * SINS(arg0->rotation.z));
    arg0->motionStep.y = arg0->stepMagnitude * (SINS(arg0->rotation.y) * SINS(arg0->rotation.z) -
                                     SINS(arg0->rotation.x) * COSS(arg0->rotation.y) * COSS(arg0->rotation.z));
    arg0->motionStep.z = arg0->stepMagnitude * (COSS(arg0->rotation.x) * COSS(arg0->rotation.y));
}

void Particle_UpdateRotatingVelocityXZ(Particle* arg0, f32 arg1, s16 arg2) {
    f32 tmp1 = arg0->motionOffset.x;
    f32 tmp2 = arg0->motionOffset.z;

    arg0->rotationStep.y += arg2;

    arg0->motionOffset.x = arg1 * gParticleRenderContext.scale.y * SINS(arg0->rotationStep.y);
    arg0->motionOffset.z = arg1 * gParticleRenderContext.scale.y * COSS(arg0->rotationStep.y);

    arg0->motionStep.x = arg0->motionOffset.x - tmp1;
    arg0->motionStep.z = arg0->motionOffset.z - tmp2;
}

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
        func_8213E3F8(arg0);
    }

    return sp24;
}

void Particle_Field1C_SetScaled_0B938(Particle* arg0, f32 arg1) {
    arg0->scale = arg1 * gParticleRenderContext.scale.y;
}

void Particle_SetScale(Particle* arg0, f32 arg1) {
    arg0->scale = arg1;
}

void Particle_SetScaleSpeed(Particle* arg0, f32 arg1) {
    arg0->unk_20 = arg1 * gParticleRenderContext.scale.y;
}

void Particle_SetScaleTarget(Particle* arg0, f32 arg1) {
    arg0->unk_24 = arg1 * gParticleRenderContext.scale.y;
}

s32 Particle_Field1C_Approach_0B98C(Particle* arg0, f32 arg1, f32 arg2) {
    return ParticleMath_ApproachFloat(&arg0->scale, arg1 * gParticleRenderContext.scale.y, arg2 * gParticleRenderContext.scale.y);
}

s32 Particle_Field1C_ApproachAndStepState_0B9D0(Particle* arg0, f32 arg1, f32 arg2) {
    s32 sp1C = Particle_Field1C_Approach_0B98C(arg0, arg1, arg2);

    if (sp1C != 0) {
        Particle_AdvanceLifecycle(arg0);
    }
    return sp1C;
}

s32 Particle_Field1C_ApproachField24ByField20_0BA1C(Particle* arg0) {
    return ParticleMath_ApproachFloat(&arg0->scale, arg0->unk_20, arg0->unk_24);
}

s32 Particle_Field1C_ApproachField24AndStepState_0BA48(Particle* arg0) {
    s32 sp1C = Particle_Field1C_ApproachField24ByField20_0BA1C(arg0);

    if (sp1C != 0) {
        Particle_AdvanceLifecycle(arg0);
    }
    return sp1C;
}

s32 Particle_Field20_Approach_0BA84(Particle* arg0, f32 arg1, f32 arg2) {
    return ParticleMath_ApproachFloat(&arg0->unk_20, arg1 * gParticleRenderContext.scale.y, arg2 * gParticleRenderContext.scale.y);
}

void Particle_SetPrimColor(Particle* arg0, u8 arg1, u8 arg2, u8 arg3) {
    arg0->prim_r = arg1;
    arg0->prim_g = arg2;
    arg0->prim_b = arg3;
}

M2C_UNK func_82137804(s32, s32, s32);               /* extern */

void func_82140380(s32 arg0, s32 arg1, s32 arg2) {
    func_82137804(arg0 + 0xBA, arg1 & 0xFF, arg2 & 0xFF);
}

M2C_UNK func_82137804(s32, s32, s32);               /* extern */

void func_821403B0(s32 arg0, s32 arg1, s32 arg2) {
    func_82137804(arg0 + 0xBB, arg1 & 0xFF, arg2 & 0xFF);
}

M2C_UNK func_82137804(s32, s32, s32);               /* extern */

void func_821403E0(s32 arg0, s32 arg1, s32 arg2) {
    func_82137804(arg0 + 0xBC, arg1 & 0xFF, arg2 & 0xFF);
}

extern s16 D_8219A8B2;
extern s16 D_8219A8B4;
extern s16 D_8219A8B6;

void func_82140410(s8 *arg0) {
    D_8219A8B2 = (s16) M2C_FIELD(arg0, u8 *, 0xBA);
    D_8219A8B4 = (s16) M2C_FIELD(arg0, u8 *, 0xBB);
    D_8219A8B6 = (s16) M2C_FIELD(arg0, u8 *, 0xBC);
}

extern s16 D_8219A8B2;
extern s16 D_8219A8B4;
extern s16 D_8219A8B6;

/**
 * @unverified Name was previously used only by callers of this address; the definition was still func_.
 */
void BattleAnim_LoadGlobalTintToParticle(s8 *arg0) {
    M2C_FIELD(arg0, s8 *, 0xBA) = (s8) D_8219A8B2;
    M2C_FIELD(arg0, s8 *, 0xBB) = (s8) D_8219A8B4;
    M2C_FIELD(arg0, s8 *, 0xBC) = (s8) D_8219A8B6;
}

/**
 * Set envRed, envGreen, envBlue.
 * @unverified Name was previously used only by callers of this address; the definition was still func_. Comment from Stadium 1.
 */
void Particle_SetEnvColor(Particle* arg0, u8 arg1, u8 arg2, u8 arg3) {
    arg0->env_r = arg1;
    arg0->env_g = arg2;
    arg0->env_b = arg3;
}

M2C_UNK func_82137804(s32, s32, s32);               /* extern */

void func_8214047C(s32 arg0, s32 arg1, s32 arg2) {
    func_82137804(arg0 + 0xBD, arg1 & 0xFF, arg2 & 0xFF);
}

M2C_UNK func_82137804(s32, s32, s32);               /* extern */

void func_821404AC(s32 arg0, s32 arg1, s32 arg2) {
    func_82137804(arg0 + 0xBF, arg1 & 0xFF, arg2 & 0xFF);
}

M2C_UNK func_82137804(s32, s32, s32);               /* extern */

void func_821404DC(s32 arg0, s32 arg1, s32 arg2) {
    func_82137804(arg0 + 0xBE, arg1 & 0xFF, arg2 & 0xFF);
}

void func_8214050C(s8 *arg0, char arg1)
{
  s8 *new_var; // FAKE: permuter temp
  s8 *new_var2; // FAKE: permuter temp
  new_var2 = arg0;
  new_var = (s8 *) new_var2;
  *((s8 *) (new_var + 0xC0)) = arg1;
}

M2C_UNK func_82137804(s32, s32, s32);               /* extern */

void func_82140518(s32 arg0, s32 arg1, s32 arg2) {
    func_82137804(arg0 + 0xC0, arg1 & 0xFF, arg2 & 0xFF);
}

s32 Particle_PrimAlpha_ApproachAndStepState_0BC5C(Particle* arg0, u8 arg1, u8 arg2) {
    s32 sp1C = Particle_PrimAlpha_Approach_0BC2C(arg0, arg1, arg2);

    if (sp1C != 0) {
        Particle_AdvanceLifecycle(arg0);
    }
    return sp1C;
}

void func_82140594(s8 *arg0, s16 arg1) {
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

s32 Particle_FieldA6_DecrementToZero_0BD08(Particle* arg0, s16 arg1) {
    return Particle_FieldA6_DecrementTo_0BCC4(arg0, 0, arg1);
}

s32 Particle_FieldA6_DecrementToZeroAndStepState_0BD34(Particle* arg0, s16 arg1) {
    s32 sp1C = Particle_FieldA6_DecrementTo_0BCC4(arg0, 0, arg1);

    if (sp1C != 0) {
        Particle_AdvanceLifecycle(arg0);
    }
    return sp1C;
}

s32 Particle_FieldA6_DecrementToStep1_0BD80(Particle* arg0, s16 arg1) {
    return Particle_FieldA6_DecrementTo_0BCC4(arg0, arg1, 1);
}

s32 Particle_FieldA6_DecrementToZeroStep1_0BDAC(Particle* arg0) {
    return Particle_FieldA6_DecrementTo_0BCC4(arg0, 0, 1);
}

s32 Particle_FieldA6_DecrementToZeroStep1AndStepState_0BDD0(Particle* arg0) {
    s32 sp1C = Particle_FieldA6_DecrementTo_0BCC4(arg0, 0, 1);

    if (sp1C != 0) {
        Particle_AdvanceLifecycle(arg0);
    }
    return sp1C;
}

void func_821406F8(s8 *arg0, s16 arg1) {
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

s32 Particle_FieldA8_DecrementToZeroStep1_0BE6C(Particle* arg0) {
    return Particle_FieldA8_DecrementTo_0BE30(arg0, 0);
}

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

void func_821407B4(s8 *arg0, s16 arg1) {
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

void func_821407E0(s8 *arg0, unsigned short arg1)
{
  *((s8 *) (((s8 *) arg0) + 0xC8)) = arg1;
}

void func_821407EC(s8 *arg0, s16 arg1) {
    M2C_FIELD(arg0, s16 *, 0xA6) = arg1;
}

void func_82140800(s8 *arg0, s16 arg1) {
    M2C_FIELD(arg0, s8 *, 0xCA) = (s8) arg1;
}

void func_82140814(s8 *arg0, s16 arg1) {
    M2C_FIELD(arg0, s8 *, 0xC9) = (s8) arg1;
}

void func_82140828(s8 *arg0, s16 arg1) {
    M2C_FIELD(arg0, s16 *, 0xAA) = arg1;
}

M2C_UNK func_82137898(s32, s16, s16);               /* extern */

void func_8214083C(s32 arg0, s16 arg1, s16 arg2) {
    func_82137898(arg0 + 0xAA, arg1, arg2);
}

s32 Particle_FieldAE_ApproachAndStepState_0BF98(Particle* arg0, s16 arg1, s16 arg2) {
    s32 sp1C = Particle_FieldAE_Approach_0BF60(arg0, arg1, arg2);

    if (sp1C != 0) {
        Particle_AdvanceLifecycle(arg0);
    }
    return sp1C;
}

void func_821408C8(s8 *arg0, s16 arg1) {
    M2C_FIELD(arg0, s16 *, 0xAC) = arg1;
}

M2C_UNK func_82137898(s32, s16, s16);               /* extern */

void func_821408DC(s32 arg0, s16 arg1, s16 arg2) {
    func_82137898(arg0 + 0xAC, arg1, arg2);
}
