/* Stadium Zero fragment012_17ED00. */
/* C ported from the Stadium 1 decomp: src/fragments/particle_math/particle_math_261F90.c. */

#include "fragments/particle_math/particle_math.h"
#include "math.h"
#include "matrix.h"
#include "math_util.h"
extern ParticleMatrixPool* gParticleMatrixPool;
extern s32 gParticleMatrixPoolIndex;
extern s32 gParticleMatrixPoolIndex;
extern ParticleRenderContext gParticleRenderContext;
extern ParticleCameraState* gParticleCameraState;
extern u32 gParticleFrameCounter;
extern s32 gParticleFrameMod64;
extern s32 gParticleFrameMod32;
extern s32 gParticleFrameMod16;
extern s32 gParticleFrameMod8;
extern s32 gParticleFrameMod4;
extern u32 gParticleFrameMod3;
extern s32 gParticleFrameMod2;
extern u32 gParticleFrameDiv64;
extern u32 gParticleFrameDiv32;
extern u32 gParticleFrameDiv16;
extern u32 gParticleFrameDiv8;
extern u32 gParticleFrameDiv4;
extern u32 gParticleFrameDiv3;
extern u32 gParticleFrameDiv2;
extern s32 gParticleFrameDiv64Parity;
extern s32 gParticleFrameDiv32Parity;
extern s32 gParticleFrameDiv16Parity;
extern s32 gParticleFrameDiv8Parity;
extern s32 gParticleFrameDiv4Parity;
extern s32 gParticleFrameDiv3Parity;
extern s32 gParticleFrameDiv2Parity;
extern s32 gParticleRandomOffset;
extern s32 pad_D_8140E714[2];
extern Particle* gParticlePool;
extern BattleAnimEffectSlot* gBattleAnimEffectSlots;
extern ParticleEmitter* gMiniFxEmitters;
extern s32 gParticlePoolIndex;
extern s32 gBattleAnimEffectSlotIndex;
extern s32 gMiniFxEmitterIndex;

#include "m2c_macros.h"

void ParticleMath_BitwiseOr(s32* arg0, s32 arg1);
void ParticleMath_BitwiseAndNot(s32* arg0, s32 arg1);
void ParticleMath_BitwiseXor(s32* arg0, s32 arg1);
s32 ParticleMath_HasBits(s32* arg0, s32 arg1);
s32 ParticleMath_LacksBits(s32* arg0, s32 arg1);
s32 ParticleMath_ApproachFloatUp(f32* arg0, f32 arg1, f32 arg2);
s32 ParticleMath_ApproachFloatDown(f32* arg0, f32 arg1, f32 arg2);
s32 ParticleMath_ApproachS32Up(s32* arg0, s32 arg1, s32 arg2);
s32 ParticleMath_ApproachS32Down(s32* arg0, s32 arg1, s32 arg2);
s32 ParticleMath_ApproachS16Up(s16* arg0, s16 arg1, s16 arg2);
s32 ParticleMath_ApproachU16Up(u16* arg0, u16 arg1, u16 arg2);
s32 ParticleMath_ApproachS16Down(s16* arg0, s16 arg1, s16 arg2);
s32 ParticleMath_ApproachU16Down(u16* arg0, s32 arg1, s32 arg2);
s32 ParticleMath_ApproachFloatUpByPointer(f32* arg0, f32 arg1, f32* arg2);
s32 ParticleMath_ApproachFloatDownByPointer(f32* arg0, f32 arg1, f32* arg2);
s32 ParticleMath_ApproachS32UpByPointer(s32* arg0, s32 arg1, s32* arg2);
s32 ParticleMath_ApproachS32DownByPointer(s32* arg0, s32 arg1, s32* arg2);
s32 ParticleMath_ApproachS16UpByPointer(s16* arg0, s16 arg1, s16* arg2);
s32 ParticleMath_ApproachS16DownByPointer(s16* arg0, s16 arg1, s16* arg2);
s32 ParticleMath_ApproachAngle(s16* arg0, s16 arg1, s16 arg2);
s32 ParticleMath_ApproachS32(s32* arg0, s32 arg1, s32 arg2);
s32 ParticleMath_ApproachFloat(f32* arg0, f32 arg1, f32 arg2);
void ParticleMath_BounceFloat(f32* arg0, f32 arg1, f32 arg2, f32* arg3);
void ParticleMath_BounceS16(s16* arg0, s16 arg1, s16 arg2, s16* arg3);
void ParticleMath_CopyVec3f(Vec3f* arg0, Vec3f* arg1);
void ParticleMath_CopyVec3s(Vec3s* arg0, Vec3s* arg1);
void ParticleMath_AddVec3f(Vec3f* arg0, Vec3f* arg1);
void ParticleMath_AddVec3s(Vec3s* arg0, Vec3s* arg1);
s32 ParticleMath_IsWithinRadius2D(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4);
s32 ParticleMath_RandomRangeOffset(s32 arg0, s32 arg1);
s32 ParticleMath_RandomSigned(s32 arg0);
s32 ParticleMath_RandomSignedOffset(s32 arg0, s32 arg1);
s32 ParticleMath_RandomSignedOffsetBySign(s32 arg0, s32 arg1);
void ParticleMath_NoopStub(UNUSED s32 arg0);
s16 ParticleMath_Atan2YZ(Vec3f arg0);
s16 ParticleMath_Atan2ZX(Vec3f arg0);
s16 ParticleMath_Atan2XY(Vec3f arg0);
void ParticleMath_Vec3ToAngles(Vec3s* arg0, Vec3f arg1);
f32 ParticleMath_Rotate2DX(f32 arg0, f32 arg1, s16 arg2);
f32 ParticleMath_Rotate2DY(f32 arg0, f32 arg1, s16 arg2);
Vec3f* ParticleMath_RotateVec3fY(Vec3f* arg0, Vec3f arg1, Vec3s arg2);
Vec3f* ParticleMath_MakeXZVectorFromAngle(Vec3f* arg0, f32 arg1, s16 arg2);
Vec3f* ParticleMath_RotateVec3fXY(Vec3f* arg0, Vec3f arg1, Vec3s arg4);
f32 ParticleMath_Distance3D(Vec3f arg0, Vec3f arg1);
Vec3f* ParticleMath_NormalizedDirection(Vec3f* arg0, Vec3f arg1, Vec3f arg2);
s32 ParticleMath_DistanceScaled(Vec3f arg0, Vec3f arg1, f32 arg2);
s32 ParticleMath_ScaleDirectionToLength(Vec3f* arg0, Vec3f arg1, Vec3f arg2, f32 arg3);
Vec3f* ParticleMath_RandomDirection(Vec3f* arg0, f32 arg1);
Vec3f* ParticleMath_ScaleVec3f(Vec3f* arg0, f32 arg1);
s16 ParticleMath_AngleXBetweenPoints(Vec3f arg0, Vec3f arg1);
s16 ParticleMath_AngleYBetweenPoints(Vec3f arg0, Vec3f arg1);
s16 ParticleMath_AngleZBetweenPoints(Vec3f arg0, Vec3f arg1);
s16 ParticleMath_ApproachAngleCoarse(s16 arg0, s16 arg1);
void ParticleGfx_NoopStub1(void);
void ParticleGfx_PushMatrix(MtxF* arg0);
void ParticleGfx_Build2DTransformMatrix(MtxF* arg0, s16 arg1, s16 arg2, s16 arg3, f32 arg4);
void ParticleGfx_Build2DTransformMatrixYScaled(MtxF* arg0, s16 arg1, s16 arg2, s16 arg3, f32 arg4);
void ParticleGfx_Push2DTransform(s16 arg0, s16 arg1, s16 arg2, f32 arg3);
void ParticleGfx_Push2DTransformYScaled(s16 arg0, s16 arg1, s16 arg2, f32 arg3);
void ParticleGfx_BuildTransformMatrix(MtxF* arg0, Vec3f arg1, Vec3s arg2, f32 arg3);
void ParticleGfx_BuildTransformMatrixYScaled(MtxF* arg0, Vec3f arg1, Vec3s arg2, f32 arg3);
void ParticleGfx_BuildTransformMatrixXYScaled(MtxF* arg0, Vec3f arg1, Vec3s arg2, f32 arg3, f32 arg4);
void ParticleGfx_BuildBillboardMatrix(MtxF* arg0, MtxF* arg1, Vec3f arg2, f32 arg3);
void ParticleGfx_BuildBillboardMatrixYScaled(MtxF* arg0, MtxF* arg1, Vec3f arg2, f32 arg3);
void ParticleGfx_BuildBillboardRotatedMatrix(MtxF* arg0, MtxF* arg1, Vec3f arg2, f32 arg3, s16 arg4);
void ParticleGfx_BuildBillboardRotatedMatrixYScaled(MtxF* arg0, MtxF* arg1, Vec3f arg2, f32 arg3, s16 arg4);
void ParticleGfx_BuildDirectionMatrix(MtxF* arg0, Vec3f arg1, Vec3f arg2, s16 arg3, f32 arg4);
void ParticleGfx_PushTransformMatrix(Vec3f arg0, Vec3s arg1, f32 arg2);
void ParticleGfx_PushTransformMatrixYScaled(Vec3f arg0, Vec3s arg1, f32 arg2);
void ParticleGfx_PushTransformMatrixXYScaled(Vec3f arg0, Vec3s arg1, f32 arg2, f32 arg3);
void ParticleGfx_PushBillboardMatrix(CameraNode* arg0, Vec3f arg1, f32 arg4);
void ParticleGfx_PushBillboardRotatedMatrix(CameraNode* arg0, Vec3f arg1, f32 arg4, s16 arg5);
void ParticleGfx_PushBillboardMatrixYScaled(CameraNode* arg0, Vec3f arg1, f32 arg4);
void ParticleGfx_PushBillboardRotatedMatrixYScaled(CameraNode* arg0, Vec3f arg1, f32 arg4, s16 arg5);
void ParticleGfx_PushTransformMatrixWithHalfTurnXY(Vec3f arg0, Vec3s arg3, f32 arg5);
void ParticleGfx_PushDirectionMatrix(Vec3f arg0, Vec3f arg3, f32 arg6);

u32 ParticleMath_RandomRange(u32 arg0);

/**
 * Set every bit selected by mask.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal or j,
 * no pointer word, no lui/addiu pair in any fragment), so play cannot reach it.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void ParticleMath_BitwiseOr(s32* arg0, s32 arg1) {
    *arg0 |= arg1;
}

/**
 * Clear every bit selected by mask.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void ParticleMath_BitwiseAndNot(s32* arg0, s32 arg1) {
    *arg0 &= ~arg1;
}

/**
 * Toggle every bit selected by mask.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void ParticleMath_BitwiseXor(s32* arg0, s32 arg1) {
    *arg0 ^= arg1;
}

/**
 * Return whether any bit selected by mask is set.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
s32 ParticleMath_HasBits(s32* arg0, s32 arg1) {
    s32 var_v1 = 0;

    if (*arg0 & arg1) {
        var_v1 = 1;
    }
    return var_v1;
}

/**
 * Return whether all bits selected by mask are clear.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
s32 ParticleMath_LacksBits(s32* arg0, s32 arg1) {
    s32 var_v1 = 0;

    if (!(*arg0 & arg1)) {
        var_v1 = 1;
    }
    return var_v1;
}

/**
 * Increase value toward target by step; return 1 only when this call reaches or crosses the target.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
s32 ParticleMath_ApproachFloatUp(f32* arg0, f32 arg1, f32 arg2) {
    s32 var_v1 = 0;

    if (*arg0 < arg1) {
        *arg0 += arg2;
        if (arg1 <= *arg0) {
            *arg0 = arg1;
            var_v1 = 1;
        }
    }
    return var_v1;
}

/**
 * Decrease value toward target by step; return 1 only when this call reaches or crosses the target.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
s32 ParticleMath_ApproachFloatDown(f32* arg0, f32 arg1, f32 arg2) {
    s32 var_v1 = 0;

    if (arg1 < *arg0) {
        *arg0 -= arg2;
        if (*arg0 <= arg1) {
            *arg0 = arg1;
            var_v1 = 1;
        }
    }
    return var_v1;
}

/**
 * Increase value toward target by step; return 1 only when this call reaches or crosses the target.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
s32 ParticleMath_ApproachS32Up(s32* arg0, s32 arg1, s32 arg2) {
    s32 var_v1 = 0;

    if (*arg0 < arg1) {
        *arg0 += arg2;
        if (*arg0 >= arg1) {
            *arg0 = arg1;
            var_v1 = 1;
        }
    }
    return var_v1;
}

/**
 * Decrease value toward target by step; return 1 only when this call reaches or crosses the target.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
s32 ParticleMath_ApproachS32Down(s32* arg0, s32 arg1, s32 arg2) {
    s32 var_v1 = 0;

    if (arg1 < *arg0) {
        *arg0 -= arg2;
        if (arg1 >= *arg0) {
            *arg0 = arg1;
            var_v1 = 1;
        }
    }
    return var_v1;
}

/**
 * Increase value toward target by step; return 1 only when this call reaches or crosses the target.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
s32 ParticleMath_ApproachS16Up(s16* arg0, s16 arg1, s16 arg2) {
    s32 var_v1 = 0;

    if (*arg0 < arg1) {
        *arg0 += arg2;
        if (*arg0 >= arg1) {
            *arg0 = arg1;
            var_v1 = 1;
        }
    }
    return var_v1;
}

/**
 * Increase value toward target by step; return 1 only when this call reaches or crosses the target.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
s32 ParticleMath_ApproachU16Up(u16* arg0, u16 arg1, u16 arg2) {
    s32 var_v1 = 0;

    if (*arg0 < arg1) {
        *arg0 += arg2;
        if (*arg0 >= arg1) {
            *arg0 = arg1;
            var_v1 = 1;
        }
    }
    return var_v1;
}

/**
 * Decrease value toward target by step; return 1 only when this call reaches or crosses the target.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
s32 ParticleMath_ApproachS16Down(s16* arg0, s16 arg1, s16 arg2) {
    s32 var_v1 = 0;

    if (arg1 < *arg0) {
        *arg0 -= arg2;
        if (arg1 >= *arg0) {
            *arg0 = arg1;
            var_v1 = 1;
        }
    }
    return var_v1;
}

/**
 * Decrease value toward target by step; return 1 only when this call reaches or crosses the target.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
s32 ParticleMath_ApproachU16Down(u16* arg0, s32 arg1, s32 arg2) {
    s32 var_v1 = 0;
    s32 temp_v0 = *arg0;

    if (arg1 < temp_v0) {
        temp_v0 -= arg2;
        if (arg1 >= temp_v0) {
            temp_v0 = arg1;
            var_v1 = 1;
        }
        *arg0 = temp_v0;
    }
    return var_v1;
}

/**
 * Increase value toward target by the pointed-to step; return 1 only when this call reaches or crosses the target.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
s32 ParticleMath_ApproachFloatUpByPointer(f32* arg0, f32 arg1, f32* arg2) {
    s32 var_v1 = 0;

    if (*arg0 < arg1) {
        *arg0 += *arg2;
        if (arg1 <= *arg0) {
            *arg0 = arg1;
            var_v1 = 1;
        }
    }
    return var_v1;
}

/**
 * Decrease value toward target by the pointed-to step; return 1 only when this call reaches or crosses the target.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
s32 ParticleMath_ApproachFloatDownByPointer(f32* arg0, f32 arg1, f32* arg2) {
    s32 var_v1 = 0;

    if (arg1 < *arg0) {
        *arg0 -= *arg2;
        if (*arg0 <= arg1) {
            *arg0 = arg1;
            var_v1 = 1;
        }
    }
    return var_v1;
}

/**
 * Increase value toward target by the pointed-to step; return 1 only when this call reaches or crosses the target.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
s32 ParticleMath_ApproachS32UpByPointer(s32* arg0, s32 arg1, s32* arg2) {
    s32 var_v1 = 0;

    if (*arg0 < arg1) {
        *arg0 += *arg2;
        if (*arg0 >= arg1) {
            *arg0 = arg1;
            var_v1 = 1;
        }
    }
    return var_v1;
}

/**
 * Decrease value toward target by the pointed-to step; return 1 only when this call reaches or crosses the target.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
s32 ParticleMath_ApproachS32DownByPointer(s32* arg0, s32 arg1, s32* arg2) {
    s32 var_v1 = 0;

    if (arg1 < *arg0) {
        *arg0 -= *arg2;
        if (arg1 >= *arg0) {
            *arg0 = arg1;
            var_v1 = 1;
        }
    }
    return var_v1;
}

/**
 * Increase value toward target by the pointed-to step; return 1 only when this call reaches or crosses the target.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
s32 ParticleMath_ApproachS16UpByPointer(s16* arg0, s16 arg1, s16* arg2) {
    s32 var_v1 = 0;

    if (*arg0 < arg1) {
        *arg0 += *arg2;
        if (*arg0 >= arg1) {
            *arg0 = arg1;
            var_v1 = 1;
        }
    }
    return var_v1;
}

/**
 * Decrease value toward target by the pointed-to step; return 1 only when this call reaches or crosses the target.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
s32 ParticleMath_ApproachS16DownByPointer(s16* arg0, s16 arg1, s16* arg2) {
    s32 var_v1 = 0;

    if (arg1 < *arg0) {
        *arg0 -= *arg2;
        if (arg1 >= *arg0) {
            *arg0 = arg1;
            var_v1 = 1;
        }
    }
    return var_v1;
}

/**
 * Steps the byte *arg0 toward arg1 by |arg2|; returns 1 once it gets there.
 */
s32 func_8213775C(s8* arg0, s8 arg1, s8 arg2) {
    s8 temp_v0 = *arg0;
    s32 var_v1 = 0;

    if (temp_v0 < arg1) {
        if (arg2 >= 0) {
            *arg0 = temp_v0 + arg2;
        } else {
            *arg0 = temp_v0 - arg2;
        }

        if (*arg0 >= arg1) {
            *arg0 = arg1;
            var_v1 = 1;
        }
    } else if (arg1 < temp_v0) {
        if (arg2 >= 0) {
            *arg0 = temp_v0 - arg2;
        } else {
            *arg0 = temp_v0 + arg2;
        }

        if (arg1 >= *arg0) {
            *arg0 = arg1;
            var_v1 = 1;
        }
    } else {
        var_v1 = 1;
    }

    return var_v1;
}

/**
 * Move value toward target, clamp overshoot, and return 1 at the target.
 * Seen in play (2026-11-13) in the 165-move sweep (Vice Grip, Guillotine): with target 0 and step
 * 0x20 it took a particle color byte from 0xFF to 0xDF and returned 0.
 */
s32 ParticleMath_ApproachU8(u8* arg0, u8 arg1, u8 arg2) {
    s32 var_v1 = 0;
    s16 var_a3 = *arg0;
    s16 target = arg1;

    if (var_a3 < target) {
        var_a3 += arg2;
        if (var_a3 >= target) {
            var_a3 = target;
            var_v1 = 1;
        }
    } else if (target < var_a3) {
        var_a3 -= arg2;
        if (target >= var_a3) {
            var_a3 = target;
            var_v1 = 1;
        }
    } else {
        var_v1 = 1;
    }

    *arg0 = var_a3;
    return var_v1;
}

/**
 * Steps the halfword *arg0 toward arg1 by |arg2|; returns 1 once it gets there.
 */
s32 func_82137898(s16* arg0, s16 arg1, s16 arg2) {
    s16 temp_v0 = *arg0;
    s32 var_v1 = 0;

    if (temp_v0 < arg1) {
        if (arg2 >= 0) {
            *arg0 = temp_v0 + arg2;
        } else {
            *arg0 = temp_v0 - arg2;
        }

        if (*arg0 >= arg1) {
            *arg0 = arg1;
            var_v1 = 1;
        }
    } else if (arg1 < temp_v0) {
        if (arg2 >= 0) {
            *arg0 = temp_v0 - arg2;
        } else {
            *arg0 = temp_v0 + arg2;
        }

        if (arg1 >= *arg0) {
            *arg0 = arg1;
            var_v1 = 1;
        }
    } else {
        var_v1 = 1;
    }

    return var_v1;
}

/**
 * Approach a wrapping 16-bit angle along the selected short arc; return 1 when the target is reached.
 * Seen in play (2026-11-13) in the 165-move sweep (Thunderbolt): with target 0x4000 and step 0x800
 * it moved the angle from 0x0Fxx to 0x17xx and returned 0.
 */
s32 ParticleMath_ApproachAngle(s16* arg0, s16 arg1, s16 arg2) {
    s32 a0 = *(u16*)arg0;
    s32 var_v1 = 0;
    s32 var_a1 = (u16)arg1;

    if ((u16)arg1 == a0) {
        var_a1 = (u16)arg1;
        var_v1 = 1;
    } else {
        var_a1 = (u16)arg1 - a0;
        if (var_a1 < -0x8000) {
            var_a1 = arg2 + a0;
            if (((u16)arg1 - var_a1) <= -65536) {
                var_a1 = (u16)arg1;
                var_v1 = 1;
            }
        } else if (var_a1 < 0) {
            var_a1 = a0 - arg2;
            if (((u16)arg1 - var_a1) >= 0) {
                var_a1 = (u16)arg1;
                var_v1 = 1;
            }
        } else if (var_a1 < 0x8000) {
            var_a1 = arg2 + a0;
            if (((u16)arg1 - var_a1) <= 0) {
                var_a1 = (u16)arg1;
                var_v1 = 1;
            }
        } else {
            var_a1 = a0 - arg2;
            if (((u16)arg1 - var_a1) >= 0x10000) {
                var_a1 = (u16)arg1;
                var_v1 = 1;
            }
        }
    }

    *arg0 = var_a1;
    return var_v1;
}

/**
 * Move value toward target, clamp overshoot, and return 1 at the target.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
s32 ParticleMath_ApproachS32(s32* arg0, s32 arg1, s32 arg2) {
    s32 temp_v0 = *arg0;
    s32 var_v1 = 0;

    if (temp_v0 < arg1) {
        if (arg2 >= 0) {
            *arg0 = temp_v0 + arg2;
        } else {
            *arg0 = temp_v0 - arg2;
        }

        if (*arg0 >= arg1) {
            *arg0 = arg1;
            var_v1 = 1;
        }
    } else if (arg1 < temp_v0) {
        if (arg2 >= 0) {
            *arg0 = temp_v0 - arg2;
        } else {
            *arg0 = temp_v0 + arg2;
        }

        if (arg1 >= *arg0) {
            *arg0 = arg1;
            var_v1 = 1;
        }
    } else {
        var_v1 = 1;
    }

    return var_v1;
}

/**
 * Move value toward target, clamp overshoot, and return 1 at the target.
 * Seen in play (2026-11-13) in the 165-move sweep (Thunder Punch): it moved a particle float toward
 * its target and returned 0 before arriving.
 */
s32 ParticleMath_ApproachFloat(f32* arg0, f32 arg1, f32 arg2) {
    s32 var_v1 = 0;

    if (*arg0 < arg1) {
        if (arg2 >= 0.0f) {
            *arg0 += arg2;
        } else {
            *arg0 -= arg2;
        }

        if (arg1 <= *arg0) {
            *arg0 = arg1;
            var_v1 = 1;
        }
    } else if (arg1 < *arg0) {
        if (arg2 >= 0.0f) {
            *arg0 -= arg2;
        } else {
            *arg0 += arg2;
        }

        if (*arg0 <= arg1) {
            *arg0 = arg1;
            var_v1 = 1;
        }
    } else {
        var_v1 = 1;
    }

    return var_v1;
}

/**
 * Advance by the signed step, clamp at the approached endpoint, and reverse the step there.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void ParticleMath_BounceFloat(f32* arg0, f32 arg1, f32 arg2, f32* arg3) {
    *arg0 += *arg3;

    if (*arg3 >= 0.0f) {
        if (arg2 <= *arg0) {
            *arg0 = arg2;
            *arg3 = -*arg3;
        }
    } else if (*arg0 <= arg1) {
        *arg0 = arg1;
        *arg3 = -*arg3;
    }
}

/**
 * Advance by the signed step, clamp at the approached endpoint, and reverse the step there.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void ParticleMath_BounceS16(s16* arg0, s16 arg1, s16 arg2, s16* arg3) {
    *arg0 += *arg3;
    if (*arg3 >= 0) {
        if (*arg0 >= arg2) {
            *arg0 = arg2;
            *arg3 = -*arg3;
        }
    } else if (arg1 >= *arg0) {
        *arg0 = arg1;
        *arg3 = -*arg3;
    }
}

/**
 * Copy all three vector components to the destination.
 * Seen in play (2026-11-13) in the 165-move sweep (Swords Dance): it filled a zeroed vector at a0
 * with (15.84, 52.8, 12.32).
 */
void ParticleMath_CopyVec3f(Vec3f* arg0, Vec3f* arg1) {
    arg0->x = arg1->x;
    arg0->y = arg1->y;
    arg0->z = arg1->z;
}

/**
 * Copy all three vector components to the destination.
 * Seen in play (2026-11-13) in the 165-move sweep (Swords Dance): it filled a zeroed Vec3s at a0.
 */
void ParticleMath_CopyVec3s(Vec3s* arg0, Vec3s* arg1) {
    arg0->x = arg1->x;
    arg0->y = arg1->y;
    arg0->z = arg1->z;
}

/**
 * Add all three source components to the destination in place.
 * Seen in play (2026-11-13) in the 165-move sweep (Leer, Mist): it added the vector at a1 into the
 * one at a0.
 */
void ParticleMath_AddVec3f(Vec3f* arg0, Vec3f* arg1) {
    arg0->x += arg1->x;
    arg0->y += arg1->y;
    arg0->z += arg1->z;
}

/**
 * Add all three source components to the destination in place.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void ParticleMath_AddVec3s(Vec3s* arg0, Vec3s* arg1) {
    arg0->x += arg1->x;
    arg0->y += arg1->y;
    arg0->z += arg1->z;
}

/**
 * Compare squared 2D distance with squared radius, including the boundary.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
s32 ParticleMath_IsWithinRadius2D(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4) {
    s32 var_v1 = 0;

    if ((SQ(arg2 - arg0) + SQ(arg3 - arg1)) <= SQ(arg4)) {
        var_v1 = 1;
    }
    return var_v1;
}

u32 func_80055640();                                /* extern */

u32 ParticleMath_RandomRange(u32 arg0) {
    u32 temp_v0;
    u32 var_v1;

    temp_v0 = func_80055640();
    if (arg0 == 0) {
        var_v1 = 0;
    } else {
        var_v1 = (u32) (temp_v0 / 10U) % arg0;
    }
    return var_v1;
}

/**
 * Add offset to a random value in [0, range) for a positive range.
 * Seen in play (2026-11-13) in the 165-move sweep (Vice Grip): range 12, offset 5 returned 6.
 */
s32 ParticleMath_RandomRangeOffset(s32 arg0, s32 arg1) {
    return ParticleMath_RandomRange(arg0) + arg1;
}

/**
 * Return a random integer in [-range, range) for a positive range.
 * Seen in play (2026-11-13) in the 165-move sweep (Vice Grip): range 3 returned -1.
 */
s32 ParticleMath_RandomSigned(s32 arg0) {
    return ParticleMath_RandomRange(arg0 * 2) - arg0;
}

/**
 * Add offset to the signed random result.
 * Seen in play (2026-11-13) in the 165-move sweep (Horn Attack): range 0x2000, offset 0x8000
 * returned 0x7DD7.
 */
s32 ParticleMath_RandomSignedOffset(s32 arg0, s32 arg1) {
    return ParticleMath_RandomSigned(arg0) + arg1;
}

/**
 * Move a signed random result farther from zero by offset; zero takes the positive branch.
 * Seen in play (2026-11-13) in the 165-move sweep (Horn Attack): range 0x800, offset 0x400 returned
 * 0x75B (a positive draw of 0x35B pushed out by 0x400).
 */
s32 ParticleMath_RandomSignedOffsetBySign(s32 arg0, s32 arg1) {
    s32 temp_v0 = ParticleMath_RandomSigned(arg0);

    if (temp_v0 >= 0) {
        temp_v0 += arg1;
    } else {
        temp_v0 -= arg1;
    }
    return temp_v0;
}

/**
 * Empty callback retained at its original entry point.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void ParticleMath_NoopStub(UNUSED s32 arg0) {
}

/**
 * Return MathUtil_Atan2s for the vector's Y and Z components, in that argument order.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
s16 ParticleMath_Atan2YZ(Vec3f arg0) {
    return MathUtil_Atan2s(arg0.y, arg0.z);
}

/**
 * Return MathUtil_Atan2s for the vector's Z and X components, in that argument order.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
s16 ParticleMath_Atan2ZX(Vec3f arg0) {
    return MathUtil_Atan2s(arg0.z, arg0.x);
}

/**
 * Return MathUtil_Atan2s for the vector's X and Y components, in that argument order.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
s16 ParticleMath_Atan2XY(Vec3f arg0) {
    return MathUtil_Atan2s(arg0.x, arg0.y);
}

/**
 * Write the YZ, ZX, and XY atan2 results to the three destination components.
 * No caller in play (2026-11-13): nothing that runs reaches it, not even through callbacks, data
 * tables or fragment headers.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void ParticleMath_Vec3ToAngles(Vec3s* arg0, Vec3f arg1) {
    arg0->x = MathUtil_Atan2s(arg1.y, arg1.z);
    arg0->y = MathUtil_Atan2s(arg1.z, arg1.x);
    arg0->z = MathUtil_Atan2s(arg1.x, arg1.y);
}

/**
 * Return x*cos(angle) - y*sin(angle), the rotated 2D X component.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
f32 ParticleMath_Rotate2DX(f32 arg0, f32 arg1, s16 arg2) {
    return (COSS(arg2) * arg0) - (SINS(arg2) * arg1);
}

/**
 * Return x*sin(angle) + y*cos(angle), the rotated 2D Y component.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
f32 ParticleMath_Rotate2DY(f32 arg0, f32 arg1, s16 arg2) {
    return (SINS(arg2) * arg0) + (COSS(arg2) * arg1);
}

/**
 * Rotate the supplied vector around the Y axis and return the destination.
 * Seen in play (2026-11-13) in the 165-move sweep (Confusion, Confuse Ray, Amnesia): it turned
 * (-10, 5, 10) into (10, 5, 10) and (-10, 5, -10) for quarter turns either way; y was kept.
 */
Vec3f* ParticleMath_RotateVec3fY(Vec3f* arg0, Vec3f arg1, Vec3s arg2) {
    f32 temp_fv0 = SINS(arg2.y);
    f32 temp_fv1 = COSS(arg2.y);

    arg0->x = (arg1.x * temp_fv1) + (arg1.z * temp_fv0);
    arg0->y = arg1.y;
    arg0->z = (-arg1.x * temp_fv0) + (arg1.z * temp_fv1);

    return arg0;
}

/**
 * Build (length*sin(angle), 0, length*cos(angle)) and return the destination.
 * Seen in play (2026-11-13) in the 165-move sweep (Leer, Mist): length 110 at angle 0x4000 wrote
 * (110, 0, 0).
 */
Vec3f* ParticleMath_MakeXZVectorFromAngle(Vec3f* arg0, f32 arg1, s16 arg2) {
    f32 temp_fv0 = SINS(arg2);
    f32 temp_fv1 = COSS(arg2);

    arg0->x = arg1 * temp_fv0;
    arg0->y = 0.0f;
    arg0->z = arg1 * temp_fv1;

    return arg0;
}

/**
 * Apply the explicit X/Y-angle transform to a copied vector and return the destination.
 * No caller in play (2026-11-13): nothing that runs reaches it, not even through callbacks, data
 * tables or fragment headers.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
Vec3f* ParticleMath_RotateVec3fXY(Vec3f* arg0, Vec3f arg1, Vec3s arg4) {
    f32 x = arg1.x;
    f32 y = arg1.y;
    f32 z = arg1.z;
    f32 temp_fv0 = SINS(arg4.x);
    f32 temp_fv1 = COSS(arg4.x);
    f32 temp_ft4 = SINS(arg4.y);
    f32 temp_ft5 = COSS(arg4.y);

    arg0->x = (x * temp_ft5) + (z * temp_ft4);
    arg0->y = ((x * temp_fv0 * temp_ft4) + (y * temp_fv1)) - (z * temp_fv0 * temp_ft5);
    arg0->z = (-x * temp_fv1 * temp_ft4) + (y * temp_fv0) + (z * temp_fv1 * temp_ft5);

    return arg0;
}

/**
 * Return the Euclidean distance between two 3D points.
 * No caller in play (2026-11-13): it is only called from ParticleMath_DistanceScaled, which has no
 * caller in the ROM itself.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
f32 ParticleMath_Distance3D(Vec3f arg0, Vec3f arg1) {
    return sqrtf(SQ(arg1.x - arg0.x) + SQ(arg1.y - arg0.y) + SQ(arg1.z - arg0.z));
}

/**
 * Normalize end - start into the destination; zero-length behavior belongs to Vec3f_Normalize.
 * Seen in play (2026-11-13) in the 165-move sweep (Swords Dance): it wrote (-0.993, 0.116, 0.011),
 * length 1.0, at a0.
 */
Vec3f* ParticleMath_NormalizedDirection(Vec3f* arg0, Vec3f arg1, Vec3f arg2) {
    arg0->x = arg2.x - arg1.x;
    arg0->y = arg2.y - arg1.y;
    arg0->z = arg2.z - arg1.z;

    Vec3f_Normalize(arg0);

    return arg0;
}

s32 BattleAnim_GetCameraContext(void);

#ifdef NON_MATCHING
/* TODO: decompile func_82138244; signature not recovered. */
#else
void func_821381E4(Vec3f*, Vec3f, Vec3f);
s32 BattleAnim_GetCameraContext(void);
void func_82137F10();
/**
 * Writes to arg0 the point arg2 units from the camera eye along the view direction turned
 * by arg1.
 */
void func_82138244(Vec3f *arg0, s32 arg1, f32 arg2) {
    Vec3f dir;
    CameraNode *camera;

    camera = (CameraNode *)BattleAnim_GetCameraContext();
    func_821381E4(&dir, camera->view.eyePosition, camera->view.targetPosition);
    func_82137F10(arg1, dir);
    arg0->x = camera->view.eyePosition.x + arg2 * dir.x;
    arg0->y = camera->view.eyePosition.y + arg2 * dir.y;
    arg0->z = camera->view.eyePosition.z + arg2 * dir.z;
}
#endif

/* Place a point at the requested distance from the scene camera eye. */
void func_8213831C(Vec3f* out, f32 distance) {
    Vec3f direction;
    CameraNode* camera;
    camera = (CameraNode*)BattleAnim_GetCameraContext();
    ParticleMath_NormalizedDirection(&direction, camera->view.eyePosition, camera->view.targetPosition);
    out->x = camera->view.eyePosition.x + distance * direction.x;
    out->y = camera->view.eyePosition.y + distance * direction.y;
    out->z = camera->view.eyePosition.z + distance * direction.z;
}

/**
 * Divide the 3D distance by the divisor and convert the result to s32.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
s32 ParticleMath_DistanceScaled(Vec3f arg0, Vec3f arg1, f32 arg2) {
    return ParticleMath_Distance3D(arg0, arg1) / arg2;
}

/**
 * Scale end - start to length and return the original distance / length as s32; no zero guard.
 * No caller in play (2026-11-13): nothing that runs reaches it, not even through callbacks, data
 * tables or fragment headers.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
s32 ParticleMath_ScaleDirectionToLength(Vec3f* arg0, Vec3f arg1, Vec3f arg2, f32 arg3) {
    f32 temp_fv1;

    arg0->x = arg2.x - arg1.x;
    arg0->y = arg2.y - arg1.y;
    arg0->z = arg2.z - arg1.z;

    temp_fv1 = arg3 / sqrtf(SQ(arg0->x) + SQ(arg0->y) + SQ(arg0->z));

    arg0->x = arg0->x * temp_fv1;
    arg0->y = arg0->y * temp_fv1;
    arg0->z = arg0->z * temp_fv1;

    return 1.0f / temp_fv1;
}

/**
 * Rotate a +Z vector by independently sampled X/Y angles; this is not a uniform-sphere sampler.
 * No caller in play (2026-11-13): nothing that runs reaches it, not even through callbacks, data
 * tables or fragment headers.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
Vec3f* ParticleMath_RandomDirection(Vec3f* arg0, f32 arg1) {
    Vec3f sp2C;
    Vec3s sp24;

    sp2C.x = 0.0f;
    sp2C.y = 0.0f;
    sp2C.z = arg1;

    sp24.x = ParticleMath_RandomRange(0x10000);
    sp24.y = ParticleMath_RandomRange(0x10000);

    ParticleMath_RotateVec3fXY(arg0, sp2C, sp24);
    return arg0;
}

/**
 * Multiply all three components in place and return the vector.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
Vec3f* ParticleMath_ScaleVec3f(Vec3f* arg0, f32 arg1) {
    arg0->x *= arg1;
    arg0->y *= arg1;
    arg0->z *= arg1;

    return arg0;
}

void func_821381E4(Vec3f*, Vec3f, Vec3f);

/**
 * Takes the scene camera (BattleAnim_GetCameraContext returns a CameraNode*), asks
 * func_821381E4 for the direction from its eye to its target position (the
 * Vec3f arguments are passed by value, in $a1-$a3 and on the stack), and
 * passes the result's z and x components to MathUtil_Atan2s (the angle itself
 * is discarded).
 */
void func_821385C0(void) {
    UNUSED s32 pad; // FAKE: stack padding
    Vec3f sp30;
    CameraNode* camera;

    camera = (CameraNode*)BattleAnim_GetCameraContext();
    func_821381E4(&sp30, camera->view.eyePosition, camera->view.targetPosition);
    MathUtil_Atan2s(sp30.z, sp30.x);
}

/**
 * Return the YZ-component atan2 of end - start in that argument order.
 * No caller in play (2026-11-13): nothing that runs reaches it, not even through callbacks, data
 * tables or fragment headers.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
s16 ParticleMath_AngleXBetweenPoints(Vec3f arg0, Vec3f arg1) {
    return MathUtil_Atan2s(arg1.y - arg0.y, arg1.z - arg0.z);
}

/**
 * Return the ZX-component atan2 of end - start in that argument order.
 * Not reached in play (2026-11-13): did not run in a tour of the main menu, Pokédex, party, Lab,
 * registration, Free Battle setup and a COM battle (opening, a switch, running, a Pound turn).
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
s16 ParticleMath_AngleYBetweenPoints(Vec3f arg0, Vec3f arg1) {
    return MathUtil_Atan2s(arg1.z - arg0.z, arg1.x - arg0.x);
}

/**
 * Return the XY-component atan2 of end - start in that argument order.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
s16 ParticleMath_AngleZBetweenPoints(Vec3f arg0, Vec3f arg1) {
    return MathUtil_Atan2s(arg1.x - arg0.x, arg1.y - arg0.y);
}

/**
 * Select a fixed angular increment from the signed difference, or snap when the high bytes agree.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
s16 ParticleMath_ApproachAngleCoarse(s16 arg0, s16 arg1) {
    s16 temp_v0 = arg1 - arg0;

    if ((arg0 >> 8) != (arg1 >> 8)) {
        if (temp_v0 < 0x400) {
            arg0 += 0x80;
        } else if (temp_v0 < 0x800) {
            arg0 += 0x200;
        } else if (temp_v0 < 0x4000) {
            arg0 += 0x400;
        } else if (temp_v0 < 0x8000) {
            arg0 += 0x700;
        } else if (temp_v0 < 0xC000) {
            arg0 -= 0x700;
        } else if (temp_v0 < 0xF800) {
            arg0 -= 0x400;
        } else if (temp_v0 < 0xFC00) {
            arg0 -= 0x200;
        } else {
            arg0 -= 0x80;
        }
    } else {
        arg0 = arg1;
    }

    return arg0;
}

/**
 * Empty callback retained at its original entry point.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void ParticleGfx_NoopStub1(void) {
}

/**
 * Convert a float matrix into the next pool slot and load it as MODELVIEW; stop emitting when all 364 slots are used.
 * Seen in play (2026-11-13) in the 165-move sweep (Pound and most hit moves): it emitted G_MTX
 * DA380003 (load, no push, modelview) pointing at the next gParticleMatrixPool slot, which advanced
 * by 0x40 per call.
 */
void ParticleGfx_PushMatrix(MtxF* arg0) {
    if (gParticleMatrixPoolIndex < 0x16C) {
        MtxF_ToFixed(&gParticleMatrixPool->unk_0000[gParticleMatrixPoolIndex], arg0);

        gSPMatrix(gDisplayListHead++, (u32)&gParticleMatrixPool->unk_0000[gParticleMatrixPoolIndex] & 0x1FFFFFFF,
                  G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

        gParticleMatrixPoolIndex++;
    }
}

/**
 * Build a translated 2D rotation matrix and apply uniform scale.
 * Seen in play (2026-11-13) in the 165-move sweep (Mist, powders, Smokescreen, Haze, Smog): with
 * angle 0x8000 and scale 1 it wrote mf[0][0] = mf[1][1] = -1 and zeros off the rotation block.
 */
void ParticleGfx_Build2DTransformMatrix(MtxF* arg0, s16 arg1, s16 arg2, s16 arg3, f32 arg4) {
    f32 temp_fv0 = SINS(arg3) * arg4;
    f32 temp_fv1 = COSS(arg3) * arg4;

    arg0->mf[0][0] = temp_fv1;
    arg0->mf[0][1] = -temp_fv0;
    arg0->mf[0][2] = 0.0f;
    arg0->mf[0][3] = 0.0f;

    arg0->mf[1][0] = temp_fv0;
    arg0->mf[1][1] = temp_fv1;
    arg0->mf[1][2] = 0.0f;
    arg0->mf[1][3] = 0.0f;

    arg0->mf[2][0] = 0.0f;
    arg0->mf[2][1] = 0.0f;
    arg0->mf[2][2] = 1.0f;
    arg0->mf[2][3] = 0.0f;

    arg0->mf[3][0] = arg1;
    arg0->mf[3][1] = arg2;
    arg0->mf[3][2] = 0.0f;
    arg0->mf[3][3] = 1.0f;
}

/**
 * Build a translated 2D rotation matrix and scale only its Y basis.
 * Seen in play (2026-11-13) in the 165-move sweep (Scratch, Cut, Vine Whip): with the same angle
 * and scales 2, 3 and 4, only the second row grew with the scale (mf[1][0] -1.58, -2.36, -3.15);
 * the first row stayed the same.
 */
void ParticleGfx_Build2DTransformMatrixYScaled(MtxF* arg0, s16 arg1, s16 arg2, s16 arg3, f32 arg4) {
    f32 temp_fv0 = SINS(arg3);
    f32 temp_fv1 = COSS(arg3);

    arg0->mf[0][0] = temp_fv1;
    arg0->mf[0][1] = -temp_fv0;
    arg0->mf[0][2] = 0.0f;
    arg0->mf[0][3] = 0.0f;

    arg0->mf[1][0] = temp_fv0 * arg4;
    arg0->mf[1][1] = temp_fv1 * arg4;
    arg0->mf[1][2] = 0.0f;
    arg0->mf[1][3] = 0.0f;

    arg0->mf[2][0] = 0.0f;
    arg0->mf[2][1] = 0.0f;
    arg0->mf[2][2] = 1.0f;
    arg0->mf[2][3] = 0.0f;

    arg0->mf[3][0] = arg1;
    arg0->mf[3][1] = arg2;
    arg0->mf[3][2] = 0.0f;
    arg0->mf[3][3] = 1.0f;
}

/**
 * Build the 2D transform with an added half turn and load it through the matrix pool.
 * Seen in play (2026-11-13) in the 165-move sweep (Mist, powders, Haze, Smog): it built the 2D
 * matrix and emitted one G_MTX DA380003.
 */
void ParticleGfx_Push2DTransform(s16 arg0, s16 arg1, s16 arg2, f32 arg3) {
    MtxF sp20;

    ParticleGfx_Build2DTransformMatrix(&sp20, arg0, arg1, arg2 + 0x8000, arg3);
    ParticleGfx_PushMatrix(&sp20);
}

/**
 * Build the 2D transform with an added half turn and load it through the matrix pool.
 * Seen in play (2026-11-13) in the 165-move sweep (Scratch, Cut, Vine Whip): it built the Y-scaled
 * 2D matrix and emitted one G_MTX DA380003.
 */
void ParticleGfx_Push2DTransformYScaled(s16 arg0, s16 arg1, s16 arg2, f32 arg3) {
    MtxF sp20;

    ParticleGfx_Build2DTransformMatrixYScaled(&sp20, arg0, arg1, arg2 + 0x8000, arg3);
    ParticleGfx_PushMatrix(&sp20);
}

/**
 * Build a translated 3D rotation matrix and apply uniform scale.
 * Seen in play (2026-11-13) in the 165-move sweep (Scratch, Razor Wind, Cut, Slam and others): it
 * wrote the particle position (e.g. -170.4, 116.4, -11.85) into the translation row and the scale
 * 4.5 into the rotation block.
 */
void ParticleGfx_BuildTransformMatrix(MtxF* arg0, Vec3f arg1, Vec3s arg2, f32 arg3) {
    f32 temp_fa1;
    f32 temp_fs0;
    f32 temp_fs1;
    f32 temp_ft4;
    f32 temp_fv0;
    f32 temp_fv1;

    temp_ft4 = SINS(arg2.x);
    temp_fv0 = COSS(arg2.x);

    temp_fv1 = SINS(arg2.y);
    temp_fa1 = COSS(arg2.y);

    temp_fs0 = SINS(arg2.z);
    temp_fs1 = COSS(arg2.z);

    arg0->mf[0][0] = ((temp_fa1 * temp_fs1) + (temp_ft4 * temp_fv1 * temp_fs0)) * arg3;
    arg0->mf[0][1] = temp_fv0 * temp_fs0 * arg3;
    arg0->mf[0][2] = ((-temp_fv1 * temp_fs1) + (temp_ft4 * temp_fa1 * temp_fs0)) * arg3;
    arg0->mf[0][3] = 0.0f;

    arg0->mf[1][0] = ((-temp_fa1 * temp_fs0) + (temp_ft4 * temp_fv1 * temp_fs1)) * arg3;
    arg0->mf[1][1] = temp_fv0 * temp_fs1 * arg3;
    arg0->mf[1][2] = ((temp_fv1 * temp_fs0) + (temp_ft4 * temp_fa1 * temp_fs1)) * arg3;
    arg0->mf[1][3] = 0.0f;

    arg0->mf[2][0] = temp_fv0 * temp_fv1 * arg3;
    arg0->mf[2][1] = -temp_ft4 * arg3;
    arg0->mf[2][2] = temp_fv0 * temp_fa1 * arg3;
    arg0->mf[2][3] = 0.0f;

    arg0->mf[3][0] = arg1.x;
    arg0->mf[3][1] = arg1.y;
    arg0->mf[3][2] = arg1.z;
    arg0->mf[3][3] = 1.0f;
}

/**
 * Build a translated 3D rotation matrix and scale only its Y basis.
 * Seen in play (2026-11-13) in the 165-move sweep (Thunderpunch, Hyper Beam, Thundershock,
 * Thunderbolt, Thunder): it wrote a rotation-and-translation matrix from the particle position and
 * rotation.
 */
void ParticleGfx_BuildTransformMatrixYScaled(MtxF* arg0, Vec3f arg1, Vec3s arg2, f32 arg3) {
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_fs0;
    f32 temp_ft5;
    f32 temp_fv0;
    f32 temp_fv1;

    temp_fa1 = SINS(arg2.x);
    temp_fv0 = COSS(arg2.x);

    temp_fv1 = SINS(arg2.y);
    temp_fa0 = COSS(arg2.y);

    temp_ft5 = SINS(arg2.z);
    temp_fs0 = COSS(arg2.z);

    arg0->mf[0][0] = (temp_fa0 * temp_fs0) + (temp_fa1 * temp_fv1 * temp_ft5);
    arg0->mf[0][1] = temp_fv0 * temp_ft5;
    arg0->mf[0][2] = (-temp_fv1 * temp_fs0) + (temp_fa1 * temp_fa0 * temp_ft5);
    arg0->mf[0][3] = 0.0f;

    arg0->mf[1][0] = ((-temp_fa0 * temp_ft5) + (temp_fa1 * temp_fv1 * temp_fs0)) * arg3;
    arg0->mf[1][1] = temp_fv0 * temp_fs0 * arg3;
    arg0->mf[1][2] = ((temp_fv1 * temp_ft5) + (temp_fa1 * temp_fa0 * temp_fs0)) * arg3;
    arg0->mf[1][3] = 0.0f;

    arg0->mf[2][0] = temp_fv0 * temp_fv1;
    arg0->mf[2][1] = -temp_fa1;
    arg0->mf[2][2] = temp_fv0 * temp_fa0;
    arg0->mf[2][3] = 0.0f;

    arg0->mf[3][0] = arg1.x;
    arg0->mf[3][1] = arg1.y;
    arg0->mf[3][2] = arg1.z;
    arg0->mf[3][3] = 1.0f;
}

/**
 * Build a translated 3D rotation matrix and scale its X/Y bases separately.
 * Not reached in play (2026-11-13): no move in the 165-move battle sweep called it (each move used
 * once, from the command menu to the end of its turn).
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void ParticleGfx_BuildTransformMatrixXYScaled(MtxF* arg0, Vec3f arg1, Vec3s arg2, f32 arg3, f32 arg4) {
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_fs0;
    f32 temp_ft5;
    f32 temp_fv0;
    f32 temp_fv1;

    temp_fa1 = SINS(arg2.x);
    temp_fv0 = COSS(arg2.x);

    temp_fv1 = SINS(arg2.y);
    temp_fa0 = COSS(arg2.y);

    temp_ft5 = SINS(arg2.z);
    temp_fs0 = COSS(arg2.z);

    arg0->mf[0][0] = ((temp_fa0 * temp_fs0) + (temp_fa1 * temp_fv1 * temp_ft5)) * arg3;
    arg0->mf[0][1] = temp_fv0 * temp_ft5 * arg3;
    arg0->mf[0][2] = ((-temp_fv1 * temp_fs0) + (temp_fa1 * temp_fa0 * temp_ft5)) * arg3;
    arg0->mf[0][3] = 0.0f;

    arg0->mf[1][0] = ((-temp_fa0 * temp_ft5) + (temp_fa1 * temp_fv1 * temp_fs0)) * arg4;
    arg0->mf[1][1] = temp_fv0 * temp_fs0 * arg4;
    arg0->mf[1][2] = ((temp_fv1 * temp_ft5) + (temp_fa1 * temp_fa0 * temp_fs0)) * arg4;
    arg0->mf[1][3] = 0.0f;

    arg0->mf[2][0] = temp_fv0 * temp_fv1;
    arg0->mf[2][1] = -temp_fa1;
    arg0->mf[2][2] = temp_fv0 * temp_fa0;
    arg0->mf[2][3] = 0.0f;

    arg0->mf[3][0] = arg1.x;
    arg0->mf[3][1] = arg1.y;
    arg0->mf[3][2] = arg1.z;
    arg0->mf[3][3] = 1.0f;
}

/**
 * Build a translated billboard matrix by transposing the supplied view basis and applying uniform scale.
 * Seen in play (2026-11-13) in the 165-move sweep (Pound and most hit moves): it was called with
 * the battle camera's view matrix and wrote a new matrix from it, scaled by the particle scale.
 */
void ParticleGfx_BuildBillboardMatrix(MtxF* arg0, MtxF* arg1, Vec3f arg2, f32 arg3) {
    arg0->mf[0][0] = arg1->mf[0][0] * arg3;
    arg0->mf[0][1] = arg1->mf[1][0] * arg3;
    arg0->mf[0][2] = arg1->mf[2][0] * arg3;
    arg0->mf[0][3] = 0.0f;

    arg0->mf[1][0] = arg1->mf[0][1] * arg3;
    arg0->mf[1][1] = arg1->mf[1][1] * arg3;
    arg0->mf[1][2] = arg1->mf[2][1] * arg3;
    arg0->mf[1][3] = 0.0f;

    arg0->mf[2][0] = arg1->mf[0][2] * arg3;
    arg0->mf[2][1] = arg1->mf[1][2] * arg3;
    arg0->mf[2][2] = arg1->mf[2][2] * arg3;
    arg0->mf[2][3] = 0.0f;

    arg0->mf[3][0] = arg2.x;
    arg0->mf[3][1] = arg2.y;
    arg0->mf[3][2] = arg2.z;
    arg0->mf[3][3] = 1.0f;
}

/**
 * Build a translated billboard matrix by transposing the supplied view basis and scaling only the second basis vector.
 * No caller in play (2026-11-13): it is only called from ParticleGfx_PushBillboardMatrixYScaled,
 * which has no caller in the ROM itself.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void ParticleGfx_BuildBillboardMatrixYScaled(MtxF* arg0, MtxF* arg1, Vec3f arg2, f32 arg3) {
    arg0->mf[0][0] = arg1->mf[0][0];
    arg0->mf[0][1] = arg1->mf[1][0];
    arg0->mf[0][2] = arg1->mf[2][0];
    arg0->mf[0][3] = 0.0f;

    arg0->mf[1][0] = arg1->mf[0][1] * arg3;
    arg0->mf[1][1] = arg1->mf[1][1] * arg3;
    arg0->mf[1][2] = arg1->mf[2][1] * arg3;
    arg0->mf[1][3] = 0.0f;

    arg0->mf[2][0] = arg1->mf[0][2];
    arg0->mf[2][1] = arg1->mf[1][2];
    arg0->mf[2][2] = arg1->mf[2][2];
    arg0->mf[2][3] = 0.0f;

    arg0->mf[3][0] = arg2.x;
    arg0->mf[3][1] = arg2.y;
    arg0->mf[3][2] = arg2.z;
    arg0->mf[3][3] = 1.0f;
}

/**
 * Build a translated billboard matrix by rotating its first two basis vectors and applying uniform scale.
 * Seen in play (2026-11-13) in the 165-move sweep (Pay Day, Ice Punch, Ice Beam, Blizzard, Psybeam,
 * Aurora Beam): it was called with the battle camera's view matrix and wrote the camera-facing
 * matrix rotated by the extra angle, with the particle position as translation.
 */
void ParticleGfx_BuildBillboardRotatedMatrix(MtxF* arg0, MtxF* arg1, Vec3f arg2, f32 arg3, s16 arg4) {
    f32 temp_fv0 = SINS(arg4);
    f32 temp_fv1 = COSS(arg4);

    arg0->mf[0][0] = ((arg1->mf[0][0] * temp_fv1) + (arg1->mf[0][1] * temp_fv0)) * arg3;
    arg0->mf[0][1] = ((arg1->mf[1][0] * temp_fv1) + (arg1->mf[1][1] * temp_fv0)) * arg3;
    arg0->mf[0][2] = ((arg1->mf[2][0] * temp_fv1) + (arg1->mf[2][1] * temp_fv0)) * arg3;
    arg0->mf[0][3] = 0.0f;

    arg0->mf[1][0] = ((arg1->mf[0][0] * -temp_fv0) + (arg1->mf[0][1] * temp_fv1)) * arg3;
    arg0->mf[1][1] = ((arg1->mf[1][0] * -temp_fv0) + (arg1->mf[1][1] * temp_fv1)) * arg3;
    arg0->mf[1][2] = ((arg1->mf[2][0] * -temp_fv0) + (arg1->mf[2][1] * temp_fv1)) * arg3;
    arg0->mf[1][3] = 0.0f;

    arg0->mf[2][0] = arg1->mf[0][2] * arg3;
    arg0->mf[2][1] = arg1->mf[1][2] * arg3;
    arg0->mf[2][2] = arg1->mf[2][2] * arg3;
    arg0->mf[2][3] = 0.0f;

    arg0->mf[3][0] = arg2.x;
    arg0->mf[3][1] = arg2.y;
    arg0->mf[3][2] = arg2.z;
    arg0->mf[3][3] = 1.0f;
}

/**
 * Build a translated billboard matrix by rotating its first two basis vectors and scaling only the second basis vector.
 * Seen in play (2026-11-13) in the 165-move sweep (Hyper Beam, Thundershock, Thunderbolt, Thunder):
 * it was called with the battle camera's view matrix and wrote the rotated camera-facing matrix.
 */
void ParticleGfx_BuildBillboardRotatedMatrixYScaled(MtxF* arg0, MtxF* arg1, Vec3f arg2, f32 arg3, s16 arg4) {
    f32 temp_fv0 = SINS(arg4);
    f32 temp_fv1 = COSS(arg4);

    arg0->mf[0][0] = (arg1->mf[0][0] * temp_fv1) + (arg1->mf[0][1] * temp_fv0);
    arg0->mf[0][1] = (arg1->mf[1][0] * temp_fv1) + (arg1->mf[1][1] * temp_fv0);
    arg0->mf[0][2] = (arg1->mf[2][0] * temp_fv1) + (arg1->mf[2][1] * temp_fv0);
    arg0->mf[0][3] = 0.0f;

    arg0->mf[1][0] = ((arg1->mf[0][0] * -temp_fv0) + (arg1->mf[0][1] * temp_fv1)) * arg3;
    arg0->mf[1][1] = ((arg1->mf[1][0] * -temp_fv0) + (arg1->mf[1][1] * temp_fv1)) * arg3;
    arg0->mf[1][2] = ((arg1->mf[2][0] * -temp_fv0) + (arg1->mf[2][1] * temp_fv1)) * arg3;
    arg0->mf[1][3] = 0.0f;

    arg0->mf[2][0] = arg1->mf[0][2];
    arg0->mf[2][1] = arg1->mf[1][2];
    arg0->mf[2][2] = arg1->mf[2][2];
    arg0->mf[2][3] = 0.0f;

    arg0->mf[3][0] = arg2.x;
    arg0->mf[3][1] = arg2.y;
    arg0->mf[3][2] = arg2.z;
    arg0->mf[3][3] = 1.0f;
}

/**
 * Build a scaled basis from a normalized direction and cross products, with the supplied translation.
 * No caller in play (2026-11-13): it is only called from ParticleGfx_PushDirectionMatrix, which has
 * no caller in the ROM itself.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void ParticleGfx_BuildDirectionMatrix(MtxF* arg0, Vec3f arg1, Vec3f arg2, s16 arg3, f32 arg4) {
    Vec3f sp3C;
    Vec3f sp30;
    Vec3f sp24;

    Vec3f_SetComponentsDuplicate(&sp3C, SINS(arg3), 0.0f, COSS(arg3));
    Vec3f_Normalize(&arg1);
    Vec3f_CrossProduct(&sp30, &arg1, &sp3C);
    Vec3f_Normalize(&sp30);
    Vec3f_CrossProduct(&sp24, &sp30, &arg1);
    Vec3f_Normalize(&sp24);

    arg0->mf[0][0] = sp30.x * arg4;
    arg0->mf[0][1] = sp30.y * arg4;
    arg0->mf[0][2] = sp30.z * arg4;
    arg0->mf[3][0] = arg2.x;

    arg0->mf[1][0] = arg1.x * arg4;
    arg0->mf[1][1] = arg1.y * arg4;
    arg0->mf[1][2] = arg1.z * arg4;
    arg0->mf[3][1] = arg2.y;

    arg0->mf[2][0] = sp24.x * arg4;
    arg0->mf[2][1] = sp24.y * arg4;
    arg0->mf[2][2] = sp24.z * arg4;
    arg0->mf[3][2] = arg2.z;

    arg0->mf[0][3] = 0.0f;
    arg0->mf[1][3] = 0.0f;
    arg0->mf[2][3] = 0.0f;
    arg0->mf[3][3] = 1.0f;
}

/**
 * Build the corresponding transform and load it through the matrix pool.
 * Seen in play (2026-11-13) in the 165-move sweep (Scratch, Razor Wind, Cut and others): it built
 * the transform matrix and emitted one G_MTX DA380003.
 */
void ParticleGfx_PushTransformMatrix(Vec3f arg0, Vec3s arg1, f32 arg2) {
    MtxF sp28;

    ParticleGfx_BuildTransformMatrix(&sp28, arg0, arg1, arg2);
    ParticleGfx_PushMatrix(&sp28);
}

/**
 * Build the corresponding transform and load it through the matrix pool.
 * Seen in play (2026-11-13) in the 165-move sweep (Thunderpunch, Hyper Beam, Thunder): it built the
 * Y-scaled transform matrix and emitted one G_MTX DA380003.
 */
void ParticleGfx_PushTransformMatrixYScaled(Vec3f arg0, Vec3s arg1, f32 arg2) {
    MtxF sp28;

    ParticleGfx_BuildTransformMatrixYScaled(&sp28, arg0, arg1, arg2);
    ParticleGfx_PushMatrix(&sp28);
}

/**
 * Build the corresponding transform and load it through the matrix pool.
 * Not reached in play (2026-11-13): no move in the 165-move battle sweep called it (each move used
 * once, from the command menu to the end of its turn).
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void ParticleGfx_PushTransformMatrixXYScaled(Vec3f arg0, Vec3s arg1, f32 arg2, f32 arg3) {
    MtxF sp28;

    ParticleGfx_BuildTransformMatrixXYScaled(&sp28, arg0, arg1, arg2, arg3);
    ParticleGfx_PushMatrix(&sp28);
}

/**
 * Build the corresponding transform and load it through the matrix pool.
 * Seen in play (2026-11-13) in the 165-move sweep (Pound and most hit moves): called with the
 * battle camera, it emitted one G_MTX DA380003.
 */
void ParticleGfx_PushBillboardMatrix(CameraNode* arg0, Vec3f arg1, f32 arg4) {
    MtxF sp20;

    ParticleGfx_BuildBillboardMatrix(&sp20, &arg0->view.floatMatrix, arg1, arg4);
    ParticleGfx_PushMatrix(&sp20);
}

/**
 * Build the corresponding transform and load it through the matrix pool.
 * Seen in play (2026-11-13) in the 165-move sweep (Pay Day, Ice Punch, Ice Beam, Blizzard,
 * Psybeam): called with the battle camera, it emitted one G_MTX DA380003.
 */
void ParticleGfx_PushBillboardRotatedMatrix(CameraNode* arg0, Vec3f arg1, f32 arg4, s16 arg5) {
    MtxF sp28;

    ParticleGfx_BuildBillboardRotatedMatrix(&sp28, &arg0->view.floatMatrix, arg1, arg4, arg5);
    ParticleGfx_PushMatrix(&sp28);
}

/**
 * Build the corresponding transform and load it through the matrix pool.
 * No caller in play (2026-11-13): it is only called from ParticleGfx_DrawModelQuadYScaled, which
 * has no caller in the ROM itself.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void ParticleGfx_PushBillboardMatrixYScaled(CameraNode* arg0, Vec3f arg1, f32 arg4) {
    MtxF sp20;

    ParticleGfx_BuildBillboardMatrixYScaled(&sp20, &arg0->view.floatMatrix, arg1, arg4);
    ParticleGfx_PushMatrix(&sp20);
}

/**
 * Build the corresponding transform and load it through the matrix pool.
 * Seen in play (2026-11-13) in the 165-move sweep (Hyper Beam, Thundershock, Thunderbolt, Thunder):
 * called with the battle camera, it emitted one G_MTX DA380003.
 */
void ParticleGfx_PushBillboardRotatedMatrixYScaled(CameraNode* arg0, Vec3f arg1, f32 arg4, s16 arg5) {
    MtxF sp28;

    ParticleGfx_BuildBillboardRotatedMatrixYScaled(&sp28, &arg0->view.floatMatrix, arg1, arg4, arg5);
    ParticleGfx_PushMatrix(&sp28);
}

/**
 * Add half turns to rotation X/Y, build the transform, and load it through the matrix pool.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void ParticleGfx_PushTransformMatrixWithHalfTurnXY(Vec3f arg0, Vec3s arg3, f32 arg5) {
    MtxF sp30;
    Vec3s sp28;

    sp28.x = arg3.x + 0x8000;
    sp28.y = arg3.y + 0x8000;
    sp28.z = arg3.z;

    ParticleGfx_BuildTransformMatrix(&sp30, arg0, sp28, arg5);
    ParticleGfx_PushMatrix(&sp30);
}

/**
 * Build the corresponding transform and load it through the matrix pool.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void ParticleGfx_PushDirectionMatrix(Vec3f arg0, Vec3f arg3, f32 arg6) {
    MtxF sp30;

    ParticleGfx_BuildDirectionMatrix(&sp30, arg3, arg0, 0, arg6);
    ParticleGfx_PushMatrix(&sp30);
}
