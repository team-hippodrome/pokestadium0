/* Stadium Zero fragment012_17ED00. */
/* C ported from the Stadium 1 decomp: src/fragments/battle_engine/battle_engine_2F6930.c. */

#include "fragments/battle_engine/battle_engine.h"
#include "math_util.h"

void BattleAnim_CalculateDistanceAngles(Vec3f* arg0, Vec3f* arg1, f32* arg2, s16* arg3, s16* arg4);
Vec3f* BattleAnim_Vec3fSetZero(Vec3f* arg0);
Vec3f* BattleAnim_Vec3fOffsetByPolarXZ(Vec3f* arg0, Vec3f* arg1, f32 arg2, s16 arg3);
void BattleAnim_Vec3fSetPolarXZ(Vec3f* dest_vector, f32 magnitude, s16 theta);
Vec3f* BattleAnim_Vec3fCopy(Vec3f* dest, Vec3f* src);
Vec3s* BattleAnim_Vec3sCopy(Vec3s* arg0, Vec3s* arg1);
Vec3f* BattleAnim_Vec3fScaleComponents(Vec3f* arg0, f32 arg1, f32 arg2, f32 arg3);
s16 BattleAnim_Atan2sFromPoints(f32 arg0, f32 arg1, f32 arg2, f32 arg3);
f32 BattleAnim_Distance2D(f32 arg0, f32 arg1, f32 arg2, f32 arg3);
u16 BattleAnim_RandomRange(s32 range);
s32 BattleAnim_StepToS16(s16* dest, s16 finish, s16 rate);
void BattleAnim_ApproachF(f32* dest, f32 value, f32 speed);
void BattleAnim_ApproachS16(s16* dest, s16 value, s16 speed);
void BattleAnim_ApproachU16(u16* dest, u16 value, s16 speed);
void Battle_ComputeSplineWeightsVariantA(f32* arg0, f32 arg1);
void Battle_ComputeSplineWeightsVariantB(f32* arg0, f32 arg1);
void Battle_ComputeSplineWeightsVariantC(f32* arg0, f32 arg1);
void Battle_ComputeSplineWeightsVariantD(f32* arg0, f32 arg1);
void Battle_ComputeSplineWeightsVariantE(f32* arg0, f32 arg1);

/**
 * @src/math_util.c
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void BattleAnim_CalculateDistanceAngles(Vec3f* arg0, Vec3f* arg1, f32* arg2, s16* arg3, s16* arg4) {
    f32 sp2C = arg1->x - arg0->x;
    f32 sp28 = arg1->y - arg0->y;
    f32 sp24 = arg1->z - arg0->z;

    *arg2 = sqrtf(SQ(sp2C) + SQ(sp28) + SQ(sp24));
    *arg3 = MathUtil_Atan2s(sqrtf(SQ(sp2C) + SQ(sp24)), sp28);
    *arg4 = MathUtil_Atan2s(sp24, sp2C);
}

/**
 * Sets all three components of `dest` to 0.0f and returns `dest`.
 * Not reached in play (2026-11-13): no move in the 165-move battle sweep called it (each move used
 * once, from the command menu to the end of its turn).
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
Vec3f* BattleAnim_Vec3fSetZero(Vec3f* arg0) {
    arg0->x = 0.0f;
    arg0->y = 0.0f;
    arg0->z = 0.0f;
    return arg0;
}

/**
 * Sets `dest` to `origin` displaced by `radius` in the XZ plane at angle
 * `theta` (s16 angle units, measured from +Z toward +X: x += sin, z += cos).
 * The Y component is copied unchanged. Returns `dest`.
 * Not reached in play (2026-11-13): no move in the 165-move battle sweep called it (each move used
 * once, from the command menu to the end of its turn).
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
Vec3f* BattleAnim_Vec3fOffsetByPolarXZ(Vec3f* arg0, Vec3f* arg1, f32 arg2, s16 arg3) {
    arg0->x = (SINS(arg3) * arg2) + arg1->x;
    arg0->y = arg1->y;
    arg0->z = (COSS(arg3) * arg2) + arg1->z;
    return arg0;
}

/**
 * Writes the XZ components of `dest` from polar form: x = cos(theta) * magnitude,
 * z = sin(theta) * magnitude (theta measured from +X toward +Z, unlike
 * BattleAnim_Vec3fOffsetByPolarXZ, which measures from +Z toward +X). The Y
 * component is left untouched.
 * Seen in play (2026-11-13) in the 165-move sweep (Fly, Agility, Double Team, Waterfall): with
 * magnitude 1.706 and theta 0x4000 it set z to 1.706 and x to 0; y was untouched.
 */
void BattleAnim_Vec3fSetPolarXZ(Vec3f* dest_vector, f32 magnitude, s16 theta) {
    dest_vector->x = COSS(theta) * magnitude;
    dest_vector->z = SINS(theta) * magnitude;
}

/**
 * Copies all three components of `src` into `dest` and returns `dest`.
 * Seen in play (2026-11-12) in move animations: wrote three floats to dest (e.g. -91.2, 39.0) and
 * returned dest.
 */
Vec3f* BattleAnim_Vec3fCopy(Vec3f* dest, Vec3f* src) {
    dest->x = src->x;
    dest->y = src->y;
    dest->z = src->z;
    return dest;
}

/**
 * Copies all three components of the s16 vector `src` into `dest` and returns
 * `dest`. Callers use it to copy display object rotations.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
Vec3s* BattleAnim_Vec3sCopy(Vec3s* arg0, Vec3s* arg1) {
    arg0->x = arg1->x;
    arg0->y = arg1->y;
    arg0->z = arg1->z;
    return arg0;
}

/**
 * Multiplies `dest` in place by a separate factor per axis and returns `dest`.
 * Not reached in play (2026-11-13): no move in the 165-move battle sweep called it (each move used
 * once, from the command menu to the end of its turn).
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
Vec3f* BattleAnim_Vec3fScaleComponents(Vec3f* arg0, f32 arg1, f32 arg2, f32 arg3) {
    arg0->x = arg0->x * arg1;
    arg0->y = arg0->y * arg2;
    arg0->z = arg0->z * arg3;
    return arg0;
}

/**
 * @src/math_util.c
 * Not reached in play (2026-11-13): no move in the 165-move battle sweep called it (each move used
 * once, from the command menu to the end of its turn).
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
s16 BattleAnim_Atan2sFromPoints(f32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    return MathUtil_Atan2s(arg2 - arg0, arg3 - arg1);
}

/**
 * Returns the Euclidean distance between points `a` and `b`, passed by value.
 * @unverified Name was previously used only by callers of this address; the definition was still func_. Comment from Stadium 1.
 */
f32 BattleAnim_Vec3fDistance(Vec3f a, Vec3f b) {
    static f32 x2;
    static f32 y2;
    static f32 z2;
    x2 = SQ(b.x - a.x);
    y2 = SQ(b.y - a.y);
    z2 = SQ(b.z - a.z);
    return sqrtf(x2 + y2 + z2);
}

/**
 * Returns the distance between (x0, y0) and (x1, y1) in a 2D plane. The camera
 * code passes X and Z world coordinates. The squared deltas are kept in
 * function-local statics (.bss words) instead of stack temporaries.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
f32 BattleAnim_Distance2D(f32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    static f32 D_843900D0;
    static f32 D_843900D4;

    D_843900D0 = SQ(arg0 - arg2);
    D_843900D4 = SQ(arg1 - arg3);

    if (D_843900D0 + D_843900D4 == 0.0f) {
        return 0.0f;
    }

    return sqrtf(D_843900D0 + D_843900D4);
}

/**
 * @src/math_util.c
 * @src/fragments/battle_engine/battle_engine_battle_phases.c
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
u16 BattleAnim_RandomRange(s32 range) {
    f32 random_value = (u32)MathUtil_Random16();

    return (random_value / 65535.0) * range;
}

/**
 * Moves *dest toward `finish` by at most |rate| and returns 0 if *dest now
 * equals `finish`, otherwise 1. The difference is computed in s16, so for
 * angle values it takes the shorter way around the 16-bit circle.
 * Seen in play (2026-11-12) in the battle camera during Flamethrower: with finish 0xE38, the s16
 * at dest went 0 -> 0xC -> 0x2D -> 0x5F -> 0x9F, each step equal to that call's rate (0xC, 0x21,
 * 0x32, 0x40), and it returned 1 while short of the target.
 */
s32 BattleAnim_StepToS16(s16* dest, s16 finish, s16 rate) {
    s16 delta_to_finish = finish - *dest;

    if (rate < 0) {
        rate *= -1;
    }

    if (delta_to_finish > 0) {
        delta_to_finish -= rate;
        if (delta_to_finish >= 0) {
            *dest = finish - delta_to_finish;
        } else {
            *dest = finish;
        }
    } else {
        delta_to_finish += rate;
        if (delta_to_finish <= 0) {
            *dest = finish - delta_to_finish;
        } else {
            *dest = finish;
        }
    }

    if (finish == *dest) {
        return 0;
    }

    return 1;
}

/**
 * Exponential approach: moves *dest toward `value` by the fraction `speed` of
 * the remaining distance (speed 0.1f closes 10% per call). A result within
 * +/-0.001 of zero is snapped to exactly 0.0f, even when `value` is not 0.
 * Seen in play (2026-11-13) in the 165-move sweep: with *dest = 50, value 8 and speed 0.3 it set
 * *dest to 37.4.
 */
void BattleAnim_ApproachF(f32* dest, f32 value, f32 speed) {
    *dest = *dest + ((value - *dest) * speed);
    if ((*dest < 0.001) && (*dest > -0.001)) {
        *dest = 0.0f;
    }
}

/**
 * Integer variant of BattleAnim_ApproachF without the snap to zero. `speed` is
 * an s16 multiplier, so any value other than 0 or 1 overshoots `value`.
 * Not reached in play (2026-11-13): no move in the 165-move battle sweep called it (each move used
 * once, from the command menu to the end of its turn).
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void BattleAnim_ApproachS16(s16* dest, s16 value, s16 speed) {
    *dest = *dest + ((value - *dest) * speed);
}

/**
 * u16 version of BattleAnim_ApproachS16; the same overshoot caveat applies.
 * Not reached in play (2026-11-13): no move in the 165-move battle sweep called it (each move used
 * once, from the command menu to the end of its turn).
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void BattleAnim_ApproachU16(u16* dest, u16 value, s16 speed) {
    *dest = *dest + ((value - *dest) * speed);
}

void Battle_ComputeSplineWeightsVariantA(f32* arg0, f32 arg1) {
    static f32 D_843900D8;
    static f32 D_843900DC;
    static f32 D_843900E0;

    D_843900E0 = 1.0f - arg1;
    D_843900DC = SQ(arg1);
    D_843900D8 = D_843900DC * arg1;

    arg0[0] = (SQ(D_843900E0) * D_843900E0) / 6.0f;
    arg0[1] = ((0.5f * D_843900D8) - D_843900DC) + 0.6666667f;
    arg0[2] = (-0.5f * D_843900D8) + (0.5f * D_843900DC) + (0.5f * arg1) + 0.16666667f;
    arg0[3] = D_843900D8 / 6.0;
}

void Battle_ComputeSplineWeightsVariantB(f32* arg0, f32 arg1) {
    static f32 D_843900E4;
    static f32 D_843900E8;
    static f32 D_843900EC;

    D_843900EC = 1.0 - arg1;
    D_843900E8 = SQ(arg1);
    D_843900E4 = D_843900E8 * arg1;

    arg0[0] = SQ(D_843900EC) * D_843900EC;
    arg0[1] = (((21.0f * D_843900E4) / 12.0f) - (9.0f * D_843900E8 * 0.5f)) + (3.0f * arg1);
    arg0[2] = ((-11.0f * D_843900E4) / 12.0f) + (3.0f * D_843900E8 * 0.5f);
    arg0[3] = D_843900E4 / 6.0f;
}

void Battle_ComputeSplineWeightsVariantC(f32* arg0, f32 arg1) {
    static f32 D_843900F0;
    static f32 D_843900F4;
    static f32 D_843900F8;

    D_843900F8 = 1.0f - arg1;
    D_843900F4 = SQ(arg1);
    D_843900F0 = D_843900F4 * arg1;

    arg0[0] = SQ(D_843900F8) * D_843900F8 * 0.25f;
    arg0[1] = ((0.5833333f * D_843900F0) - (1.25f * D_843900F4)) + (arg1 * 0.25f) + 0.5833333f;
    arg0[2] = (-0.5f * D_843900F0) + (0.5f * D_843900F4) + (0.5f * arg1) + 0.16666667f;
    arg0[3] = D_843900F0 / 6.0f;
}

void Battle_ComputeSplineWeightsVariantD(f32* arg0, f32 arg1) {
    static f32 D_843900FC;
    static f32 D_84390100;
    static f32 D_84390104;
    static f32 D_84390108;

    D_84390100 = 1.0f - arg1;
    D_84390104 = SQ(D_84390100);
    D_84390108 = D_84390104 * D_84390100;
    D_843900FC = CB(arg1);

    arg0[0] = D_84390108 / 6.0f;
    arg0[1] = (-0.5f * D_84390108) + (0.5f * D_84390104) + (0.5f * D_84390100) + 0.16666667f;
    arg0[2] = (((7.0f * D_84390108) / 12.0f) - (5.0f * D_84390104 * 0.25f)) + (D_84390100 * 0.25f) + 0.5833333f;
    arg0[3] = D_843900FC * 0.25f;
}

void Battle_ComputeSplineWeightsVariantE(f32* arg0, f32 arg1) {
    static f32 D_8439010C;
    static f32 D_84390110;
    static f32 D_84390114;
    static f32 D_84390118;

    D_84390110 = 1.0f - arg1;
    D_84390114 = SQ(D_84390110);
    D_84390118 = D_84390114 * D_84390110;
    D_8439010C = CB(arg1);

    arg0[0] = D_84390118 / 6.0f;
    arg0[1] = ((-11.0f * D_84390118) / 12.0f) + (3.0f * D_84390114 * 0.5f);
    arg0[2] = (((21.0f * D_84390118) / 12.0f) - (9.0f * D_84390114 * 0.5f)) + (3.0f * D_84390110);
    arg0[3] = D_8439010C;
}
