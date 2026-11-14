/* Stadium Zero resident code. */
/* C ported from the Stadium 1 decomp: src/gfx_rect.c, src/math_util.c, src/matrix.c. */

#include "matrix.h"
#include "game_state.h"
#include "gfx_rect.h"
extern Mtx gIdentityMtx;
extern Vec3f D_80060450;
extern Vec3s D_8006045C;
extern Vec3f D_80060464;
#define GET_HIGH_S16_OF_32(var) (((s16*)&(var))[0])
#define GET_LOW_S16_OF_32(var) (((s16*)&(var))[1])

#include "global.h"
extern GfxImage* D_8005F670;

#include "global.h"
// gSineTable, gCosineTable and gArctanTable (include/trig_tables.inc.c) match the
// ROM at 0x8006DBB0; they stay in the resident data region until it is split.

Color_RGBA8* Color_SetRGB(Color_RGBA8* dest, u8 r, u8 g, u8 b);
Color_RGBA8* Color_SetRGBA(Color_RGBA8* dest, u8 r, u8 g, u8 b, u8 alpha);
Vec3f* Vec3f_SetComponents(Vec3f* dest, f32 x, f32 y, f32 z);
unk_D_800A7440* GfxRect_SetBounds(unk_D_800A7440* arg0, s16 x1, s16 y1, s16 x2, s16 y2);
Vec3f* Vec3f_SetComponentsDuplicate(Vec3f* dest, f32 x, f32 y, f32 z);
Vec3f* Vec3f_AddInPlace(Vec3f* dest, Vec3f* summand);
Vec3f* Vec3f_Add(Vec3f* dest, Vec3f* a, Vec3f* b);
Vec3f* Vec3f_SubtractInPlace(Vec3f* dest, Vec3f* subtrahend);
Vec3f* Vec3f_Subtract(Vec3f* out, Vec3f* a, Vec3f* subtrahend);
Vec3f* Vec3f_FromVec3s(Vec3f* float_vector, Vec3s* int_vector);
Vec3f* Vec3f_TriangleNormal(Vec3f* dest, Vec3f* a, Vec3f* b, Vec3f* c);
Vec3f* Vec3f_CrossProduct(Vec3f* dest, Vec3f* a, Vec3f* b);
Vec3f* Vec3f_Normalize(Vec3f* vector);
Vec3s* Vec3s_SetComponents(Vec3s* dest, s16 a, s16 b, s16 c);
Vec3s* Vec3s_AddInPlace(Vec3s* dest, Vec3s* summand);
Vec3s* Vec3s_Add(Vec3s* dest, Vec3s* a, Vec3s* b);
Vec3s* Vec3s_SubtractInPlace(Vec3s* dest, Vec3s* subtrahend);
Vec3s* Vec3s_Subtract(Vec3s* dest, Vec3s* a, Vec3s* subtrahend);
Vec3s* Vec3s_FromVec3f(Vec3s* dest, Vec3f* float_vector);
void MtxF_Copy(MtxF* dest, MtxF* src);
void MtxF_Identity(MtxF* dest);
void MtxF_SetTranslation(MtxF* identity, Vec3f* translate);
void MtxF_SetLookAt(MtxF* mtx, Vec3f* from, Vec3f* to, u16 roll);
void MtxF_SetRotationTranslation(MtxF* out, Vec3s* translate, Vec3s* rotate);
void MtxF_SetRotationTranslationF(MtxF* out, Vec3f* translate, Vec3s* rotate);
void MtxF_SetRotationAndTransformTranslation(MtxF* out, Vec3f* translate, Vec3s* rotate);
void MtxF_SetRotationScaleTranslation(MtxF* dest, Vec3f* translate, Vec3s* rotate, Vec3f* scale);
void MtxF_SetRotationAndScaledTranslation(MtxF* dest, Vec3f* translate, Vec3s* rotate, Vec3f* scale);
void MtxF_SetOrthonormalBasis(MtxF* dest, Vec3f* up_direction, Vec3f* pos, s16 yaw);
void MtxF_Multiply(MtxF* dest, MtxF* A, MtxF* B);
void MtxF_ScaleRows(MtxF* dest, MtxF* matrix, Vec3f* scale);
void MtxF_GetScale(MtxF* matrix, Vec3f* dest);
void MtxF_TransformVec3s(MtxF* matrix, Vec3s* dest);
void MtxF_ToFixed(MtxF* dest, MtxF* src);
void Vec3f_CalculateDistanceAngles(Vec3f* to, Vec3f* from, f32* euclidean, s16* angle_x, s16* angle_y);
void Camera_ComputeEyeFromAngles(Vec3f* from, Vec3f* to, f32 dist, s16 rotation_x, s16 rotation_y);
u16 MathUtil_Atan2Lookup(f32 y, f32 x);
s16 MathUtil_Atan2s(f32 y, f32 x);
s32 MathUtil_Random16(void);
f32 MathUtil_Random_ZeroOne(void);
s16 Math_StepToS(s16 current, s16 target, s16 delta);
s32 Math_StepToS32(s32 current, s32 target, s32 increase, s32 decrease);
f32 Math_StepToF(f32 current, f32 target, f32 increase, f32 decrease);
s16 PackedBits_ReadSigned(s16* packed, s32 offset, s32 length);
void Color_RGBToHSV(f32 r, f32 g, f32 b, Vec3f* dest);
void Color_RGBA8ToHSV(Color_RGBA8_u32 color, Vec3f* dest);
void Color_RGB5551ToHSV(u16 color, Vec3f* dest);
f32 Color_HSVInterpolate(f32 hue, f32 low, f32 high);
void Color_HSVToRGB(f32* arg0, f32* arg1, f32* arg2, Vec3f* arg3);
u16 Color_HSVToRGB5551(Vec3f* arg0);
Color_RGBA8_u32* Color_HSVToRGBA8(Color_RGBA8_u32* arg0, Vec3f* arg1, s32 arg2);
u16 Color_AdjustRGB5551(u16 arg0, arg1_func_80010CA8 arg1);
u32 Color_AdjustRGBA8(u32 arg0, arg1_func_80010CA8 arg1);

/**
 * Sets the red, green and blue channels of a color; alpha is left unchanged.
 * Returns dest.
 */
Color_RGBA8* Color_SetRGB(Color_RGBA8* dest, u8 r, u8 g, u8 b) {
    dest->r = r;
    dest->g = g;
    dest->b = b;

    return dest;
}

/** Sets all four channels of a color. Returns dest. */
Color_RGBA8* Color_SetRGBA(Color_RGBA8* dest, u8 r, u8 g, u8 b, u8 alpha) {
    dest->r = r;
    dest->g = g;
    dest->b = b;
    dest->a = alpha;

    return dest;
}

/** Sets the x, y and z components of a float vector. Returns dest. */
Vec3f* Vec3f_SetComponents(Vec3f* dest, f32 x, f32 y, f32 z) {
    dest->x = x;
    dest->y = y;
    dest->z = z;

    return dest;
}

/**
 * Stores a rectangle's corners, ordering the coordinates when x2 is less than
 * x1. Returns the rectangle.
 */
unk_D_800A7440* GfxRect_SetBounds(unk_D_800A7440* arg0, s16 x1, s16 y1, s16 x2, s16 y2) {
    if (x2 >= x1) {
        arg0->x1 = x1;
        arg0->y1 = x2;
    } else {
        arg0->x1 = x2;
        arg0->y1 = x1;
    }

    if (y2 >= y1) {
        arg0->x2 = y2;
        arg0->y2 = y1;
    } else {
        arg0->y2 = y2;
        arg0->x2 = y1;
    }

    return arg0;
}

/**
 * Duplicate of Vec3f_SetComponents; the two are separate functions in the ROM.
 * Returns dest.
 */
Vec3f* Vec3f_SetComponentsDuplicate(Vec3f* dest, f32 x, f32 y, f32 z) {
    dest->x = x;
    dest->y = y;
    dest->z = z;

    return dest;
}

/** Adds summand to dest component-wise. Returns dest. */
Vec3f* Vec3f_AddInPlace(Vec3f* dest, Vec3f* summand) {
    dest->x += summand->x;
    dest->y += summand->y;
    dest->z += summand->z;

    return dest;
}

/** Stores a + b in dest. Returns dest. */
Vec3f* Vec3f_Add(Vec3f* dest, Vec3f* a, Vec3f* b) {
    dest->x = a->x + b->x;
    dest->y = a->y + b->y;
    dest->z = a->z + b->z;

    return dest;
}

/** Subtracts subtrahend from dest component-wise. Returns dest. */
Vec3f* Vec3f_SubtractInPlace(Vec3f* dest, Vec3f* subtrahend) {
    dest->x -= subtrahend->x;
    dest->y -= subtrahend->y;
    dest->z -= subtrahend->z;

    return dest;
}

/** Stores a - subtrahend in out. Returns out. */
Vec3f* Vec3f_Subtract(Vec3f* out, Vec3f* a, Vec3f* subtrahend) {
    out->x = a->x - subtrahend->x;
    out->y = a->y - subtrahend->y;
    out->z = a->z - subtrahend->z;

    return out;
}

/** Converts a short vector to a float vector. Returns float_vector. */
Vec3f* Vec3f_FromVec3s(Vec3f* float_vector, Vec3s* int_vector) {
    float_vector->x = int_vector->x;
    float_vector->y = int_vector->y;
    float_vector->z = int_vector->z;

    return float_vector;
}

/** Stores the unnormalized normal of triangle (a, b, c) in dest. Returns dest. */
Vec3f* Vec3f_TriangleNormal(Vec3f* dest, Vec3f* a, Vec3f* b, Vec3f* c) {
    dest->x = ((b->y - a->y) * (c->z - b->z)) - ((c->y - b->y) * (b->z - a->z));
    dest->y = ((b->z - a->z) * (c->x - b->x)) - ((c->z - b->z) * (b->x - a->x));
    dest->z = ((b->x - a->x) * (c->y - b->y)) - ((c->x - b->x) * (b->y - a->y));

    return dest;
}

/** Stores the cross product a x b in dest. Returns dest. */
Vec3f* Vec3f_CrossProduct(Vec3f* dest, Vec3f* a, Vec3f* b) {
    dest->x = (a->y * b->z) - (b->y * a->z);
    dest->y = (a->z * b->x) - (b->z * a->x);
    dest->z = (a->x * b->y) - (b->x * a->y);

    return dest;
}

/** Scales a vector to unit length in place. Returns the vector. */
Vec3f* Vec3f_Normalize(Vec3f* vector) {
    f32 temp_fv1_2 = 1.0f / sqrtf(SQ(vector->x) + SQ(vector->y) + SQ(vector->z));

    vector->x *= temp_fv1_2;
    vector->y *= temp_fv1_2;
    vector->z *= temp_fv1_2;

    return vector;
}

/** Sets the x, y and z components of a short vector. Returns dest. */
Vec3s* Vec3s_SetComponents(Vec3s* dest, s16 a, s16 b, s16 c) {
    dest->x = a;
    dest->y = b;
    dest->z = c;

    return dest;
}

/** Adds summand to dest component-wise. Returns dest. */
Vec3s* Vec3s_AddInPlace(Vec3s* dest, Vec3s* summand) {
    dest->x += summand->x;
    dest->y += summand->y;
    dest->z += summand->z;

    return dest;
}

/** Stores a + b in dest. Returns dest. */
Vec3s* Vec3s_Add(Vec3s* dest, Vec3s* a, Vec3s* b) {
    dest->x = a->x + b->x;
    dest->y = a->y + b->y;
    dest->z = a->z + b->z;

    return dest;
}

/** Subtracts subtrahend from dest component-wise. Returns dest. */
Vec3s* Vec3s_SubtractInPlace(Vec3s* dest, Vec3s* subtrahend) {
    dest->x -= subtrahend->x;
    dest->y -= subtrahend->y;
    dest->z -= subtrahend->z;

    return dest;
}

/** Stores a - subtrahend in dest. Returns dest. */
Vec3s* Vec3s_Subtract(Vec3s* dest, Vec3s* a, Vec3s* subtrahend) {
    dest->x = a->x - subtrahend->x;
    dest->y = a->y - subtrahend->y;
    dest->z = a->z - subtrahend->z;

    return dest;
}

/** Converts a float vector to a short vector with rounding. Returns dest. */
Vec3s* Vec3s_FromVec3f(Vec3s* dest, Vec3f* float_vector) {
    dest->x = ROUND_MAX(float_vector->x);
    dest->y = ROUND_MAX(float_vector->y);
    dest->z = ROUND_MAX(float_vector->z);

    return dest;
}

/**
 * Copies a float matrix; does nothing when source and destination are the
 * same.
 */
void MtxF_Copy(MtxF* dest, MtxF* src) {
    if (dest != src) {
        s32 i;
        u32* d = (u32*)dest;
        u32* s = (u32*)src;

        for (i = 0; i < 16; i++) {
            *d++ = *s++;
        }
    }
}

/** Sets a float matrix to the identity matrix. */
void MtxF_Identity(MtxF* dest) {
    s32 i;
    f32* j;
    // These loops must be one line to match on -O2
    // clang-format off
    
    // initialize everything except the first and last cells to 0
    for (j = (f32*)dest + 1, i = 0; i < 14; j++, i++) { *j = 0.0f; }

    // initialize the diagonal cells to 1
    for (j = (f32*)dest, i = 0; i < 4; j += 5, i++) { *j = 1.0f; }
    // clang-format on
}

/** Sets a float matrix to a pure translation. */
void MtxF_SetTranslation(MtxF* identity, Vec3f* translate) {
    MtxF_Identity(identity);

    identity->mf[3][0] = translate->x;
    identity->mf[3][1] = translate->y;
    identity->mf[3][2] = translate->z;
}

/**
 * Builds a look-at view matrix from an eye point, a target point and a roll
 * angle.
 */
void MtxF_SetLookAt(MtxF* mtx, Vec3f* from, Vec3f* to, u16 roll) {
    f32 inv_length;
    f32 dx;
    f32 dz;
    f32 x_col_y;
    f32 y_col_y;
    f32 z_col_y;
    f32 x_col_z;
    f32 y_col_z;
    f32 z_col_z;
    f32 x_col_x;
    f32 y_col_x;
    f32 z_col_x;

    dx = to->x - from->x;
    dz = to->z - from->z;

    inv_length = -1.0 / sqrtf(dx * dx + dz * dz);
    dx *= inv_length;
    dz *= inv_length;

    y_col_y = COSS(roll);
    x_col_y = SINS(roll) * dz;
    z_col_y = -SINS(roll) * dx;

    x_col_z = to->x - from->x;
    y_col_z = to->y - from->y;
    z_col_z = to->z - from->z;

    inv_length = -1.0 / sqrtf(x_col_z * x_col_z + y_col_z * y_col_z + z_col_z * z_col_z);
    x_col_z *= inv_length;
    y_col_z *= inv_length;
    z_col_z *= inv_length;

    x_col_x = y_col_y * z_col_z - z_col_y * y_col_z;
    y_col_x = z_col_y * x_col_z - x_col_y * z_col_z;
    z_col_x = x_col_y * y_col_z - y_col_y * x_col_z;

    inv_length = 1.0 / sqrtf(x_col_x * x_col_x + y_col_x * y_col_x + z_col_x * z_col_x);

    x_col_x *= inv_length;
    y_col_x *= inv_length;
    z_col_x *= inv_length;

    x_col_y = y_col_z * z_col_x - z_col_z * y_col_x;
    y_col_y = z_col_z * x_col_x - x_col_z * z_col_x;
    z_col_y = x_col_z * y_col_x - y_col_z * x_col_x;

    inv_length = 1.0 / sqrtf(x_col_y * x_col_y + y_col_y * y_col_y + z_col_y * z_col_y);
    x_col_y *= inv_length;
    y_col_y *= inv_length;
    z_col_y *= inv_length;

    mtx->mf[0][0] = x_col_x;
    mtx->mf[1][0] = y_col_x;
    mtx->mf[2][0] = z_col_x;
    mtx->mf[3][0] = -(from->x * x_col_x + from->y * y_col_x + from->z * z_col_x);

    mtx->mf[0][1] = x_col_y;
    mtx->mf[1][1] = y_col_y;
    mtx->mf[2][1] = z_col_y;
    mtx->mf[3][1] = -(from->x * x_col_y + from->y * y_col_y + from->z * z_col_y);

    mtx->mf[0][2] = x_col_z;
    mtx->mf[1][2] = y_col_z;
    mtx->mf[2][2] = z_col_z;
    mtx->mf[3][2] = -(from->x * x_col_z + from->y * y_col_z + from->z * z_col_z);

    mtx->mf[0][3] = 0.0f;
    mtx->mf[1][3] = 0.0f;
    mtx->mf[2][3] = 0.0f;
    mtx->mf[3][3] = 1.0f;
}

/**
 * Builds a rotation matrix from Euler angles and applies a short-vector
 * translation.
 */
void MtxF_SetRotationTranslation(MtxF* out, Vec3s* translate, Vec3s* rotate) {
    f32 sx = SINS(rotate->x);
    f32 cx = COSS(rotate->x);

    f32 sy = SINS(rotate->y);
    f32 cy = COSS(rotate->y);

    f32 sz = SINS(rotate->z);
    f32 cz = COSS(rotate->z);

    out->mf[0][0] = cy * cz + (sx * sy) * sz;
    out->mf[0][1] = -cy * sz + (sx * sy) * cz;
    out->mf[0][2] = cx * sy;
    out->mf[0][3] = translate->x;

    out->mf[1][0] = cx * sz;
    out->mf[1][1] = cx * cz;
    out->mf[1][2] = -sx;
    out->mf[1][3] = translate->y;

    out->mf[2][0] = -sy * cz + (sx * cy) * sz;
    out->mf[2][1] = sy * sz + (sx * cy) * cz;
    out->mf[2][2] = cx * cy;
    out->mf[2][3] = translate->z;

    out->mf[3][0] = 0.0f;
    out->mf[3][1] = 0.0f;
    out->mf[3][2] = 0.0f;
    out->mf[3][3] = 1.0f;
}

/**
 * Builds a rotation matrix from Euler angles and applies a float-vector
 * translation.
 */
void MtxF_SetRotationTranslationF(MtxF* out, Vec3f* translate, Vec3s* rotate) {
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_ft4;
    f32 temp_ft5;
    f32 temp_fv0;
    f32 temp_fv1;
    f32 sp0;

    temp_fv0 = SINS(rotate->x);
    temp_fv1 = COSS(rotate->x);

    temp_fa0 = SINS(rotate->y);
    temp_fa1 = COSS(rotate->y);

    temp_ft4 = SINS(rotate->z);
    temp_ft5 = COSS(rotate->z);

    sp0 = temp_fv0 * temp_fa0;
    out->mf[0][0] = (temp_fa1 * temp_ft5) + (sp0 * temp_ft4);
    out->mf[1][0] = (-temp_fa1 * temp_ft4) + (sp0 * temp_ft5);
    out->mf[2][0] = temp_fv1 * temp_fa0;
    out->mf[3][0] = translate->x;

    out->mf[0][1] = temp_fv1 * temp_ft4;
    out->mf[1][1] = temp_fv1 * temp_ft5;
    out->mf[2][1] = -temp_fv0;
    out->mf[3][1] = translate->y;

    sp0 = temp_fv0 * temp_fa1;
    out->mf[0][2] = (-temp_fa0 * temp_ft5) + (sp0 * temp_ft4);
    out->mf[1][2] = (temp_fa0 * temp_ft4) + (sp0 * temp_ft5);
    out->mf[2][2] = temp_fv1 * temp_fa1;
    out->mf[3][2] = translate->z;

    out->mf[0][3] = 0.0f;
    out->mf[1][3] = 0.0f;
    out->mf[2][3] = 0.0f;
    out->mf[3][3] = 1.0f;
}

/**
 * Builds a rotation matrix from Euler angles, with the translation transformed
 * by that rotation.
 */
void MtxF_SetRotationAndTransformTranslation(MtxF* out, Vec3f* translate, Vec3s* rotate) {
    f32 sx = SINS(rotate->x);
    f32 cx = COSS(rotate->x);
    f32 sy = SINS(rotate->y);
    f32 cy = COSS(rotate->y);
    f32 sz = SINS(rotate->z);
    f32 cz = COSS(rotate->z);

    out->mf[0][0] = (cy * cz) + ((sx * sy) * sz);
    out->mf[0][1] = (-cy * sz) + ((sx * sy) * cz);
    out->mf[0][2] = cx * sy;

    out->mf[1][0] = cx * sz;
    out->mf[1][1] = cx * cz;
    out->mf[1][2] = -sx;

    out->mf[2][0] = (-sy * cz) + ((sx * cy) * sz);
    out->mf[2][1] = (sy * sz) + ((sx * cy) * cz);
    out->mf[2][2] = cx * cy;

    out->mf[3][0] = (out->mf[0][0] * translate->x) + (out->mf[1][0] * translate->y) + (out->mf[2][0] * translate->z);
    out->mf[3][1] = (out->mf[0][1] * translate->x) + (out->mf[1][1] * translate->y) + (out->mf[2][1] * translate->z);
    out->mf[3][2] = (out->mf[0][2] * translate->x) + (out->mf[1][2] * translate->y) + (out->mf[2][2] * translate->z);

    out->mf[0][3] = out->mf[1][3] = out->mf[2][3] = 0.0f;
    out->mf[3][3] = 1.0f;
}

/**
 * Builds a rotation matrix from Euler angles with per-axis scale and a
 * translation.
 */
void MtxF_SetRotationScaleTranslation(MtxF* dest, Vec3f* translate, Vec3s* rotate, Vec3f* scale) {
    f32 sx = SINS(rotate->x);
    f32 cx = COSS(rotate->x);

    f32 sy = SINS(rotate->y);
    f32 cy = COSS(rotate->y);

    f32 sz = SINS(rotate->z);
    f32 cz = COSS(rotate->z);

    dest->mf[0][0] = (cy * cz) * scale->x;
    dest->mf[0][1] = (cy * sz) * scale->x;
    dest->mf[0][2] = (-sy) * scale->x;
    dest->mf[0][3] = 0.0f;

    dest->mf[1][0] = (sx * sy * cz - cx * sz) * scale->y;
    dest->mf[1][1] = (sx * sy * sz + cx * cz) * scale->y;
    dest->mf[1][2] = (sx * cy) * scale->y;
    dest->mf[1][3] = 0.0f;

    dest->mf[2][0] = (cx * sy * cz + sx * sz) * scale->z;
    dest->mf[2][1] = (cx * sy * sz - sx * cz) * scale->z;
    dest->mf[2][2] = (cx * cy) * scale->z;
    dest->mf[2][3] = 0.0f;

    dest->mf[3][0] = translate->x;
    dest->mf[3][1] = translate->y;
    dest->mf[3][2] = translate->z;
    dest->mf[3][3] = 1.0f;
}

/** Builds a rotation and scale matrix whose translation is also scaled. */
void MtxF_SetRotationAndScaledTranslation(MtxF* dest, Vec3f* translate, Vec3s* rotate, Vec3f* scale) {
    f32 sx = SINS(rotate->x);
    f32 cx = COSS(rotate->x);

    f32 sy = SINS(rotate->y);
    f32 cy = COSS(rotate->y);

    f32 sz = SINS(rotate->z);
    f32 cz = COSS(rotate->z);

    dest->mf[0][0] = cy * cz;
    dest->mf[0][1] = cy * sz;
    dest->mf[0][2] = -sy;
    dest->mf[0][3] = 0.0f;

    dest->mf[1][0] = sx * sy * cz - cx * sz;
    dest->mf[1][1] = sx * sy * sz + cx * cz;
    dest->mf[1][2] = sx * cy;
    dest->mf[1][3] = 0.0f;

    dest->mf[2][0] = cx * sy * cz + sx * sz;
    dest->mf[2][1] = cx * sy * sz - sx * cz;
    dest->mf[2][2] = cx * cy;
    dest->mf[2][3] = 0.0f;

    dest->mf[3][0] = translate->x * scale->x;
    dest->mf[3][1] = translate->y * scale->y;
    dest->mf[3][2] = translate->z * scale->z;
    dest->mf[3][3] = 1.0f;
}

void MtxF_SetBillboard(MtxF* dest, MtxF* basis, MtxF* transform, Vec3f* local_position) {
    f32 x_norm;
    f32 y_norm;
    f32 z_norm;

    x_norm = sqrtf(SQ(transform->mf[0][0]) + SQ(transform->mf[0][1]) + SQ(transform->mf[0][2]));
    y_norm = sqrtf(SQ(transform->mf[1][0]) + SQ(transform->mf[1][1]) + SQ(transform->mf[1][2]));
    z_norm = sqrtf(SQ(transform->mf[2][0]) + SQ(transform->mf[2][1]) + SQ(transform->mf[2][2]));

    dest->mf[0][0] = basis->mf[0][0] * x_norm;
    dest->mf[0][1] = basis->mf[1][0] * x_norm;
    dest->mf[0][2] = basis->mf[2][0] * x_norm;
    dest->mf[0][3] = 0.0f;

    dest->mf[1][0] = basis->mf[0][1] * y_norm;
    dest->mf[1][1] = basis->mf[1][1] * y_norm;
    dest->mf[1][2] = basis->mf[2][1] * y_norm;
    dest->mf[1][3] = 0.0f;

    dest->mf[2][0] = basis->mf[0][2] * z_norm;
    dest->mf[2][1] = basis->mf[1][2] * z_norm;
    dest->mf[2][2] = basis->mf[2][2] * z_norm;
    dest->mf[2][3] = 0.0f;

    dest->mf[3][0] =
        ((transform->mf[0][0] * local_position->x) + (transform->mf[1][0] * local_position->y) + (transform->mf[2][0] * local_position->z)) + transform->mf[3][0];
    dest->mf[3][1] =
        ((transform->mf[0][1] * local_position->x) + (transform->mf[1][1] * local_position->y) + (transform->mf[2][1] * local_position->z)) + transform->mf[3][1];
    dest->mf[3][2] =
        ((transform->mf[0][2] * local_position->x) + (transform->mf[1][2] * local_position->y) + (transform->mf[2][2] * local_position->z)) + transform->mf[3][2];
    dest->mf[3][3] = 1.0f;
}

/**
 * Builds a matrix from an up direction, a position and a heading angle about
 * the up direction.
 */
void MtxF_SetOrthonormalBasis(MtxF* dest, Vec3f* up_direction, Vec3f* pos, s16 yaw) {
    Vec3f lateral_direction;
    Vec3f left_direction;
    Vec3f forward_direction;

    Vec3f_SetComponentsDuplicate(&lateral_direction, SINS(yaw), 0, COSS(yaw));
    Vec3f_Normalize(up_direction);

    Vec3f_CrossProduct(&left_direction, up_direction, &lateral_direction);
    Vec3f_Normalize(&left_direction);

    Vec3f_CrossProduct(&forward_direction, &left_direction, up_direction);
    Vec3f_Normalize(&forward_direction);

    dest->mf[0][0] = left_direction.x;
    dest->mf[0][1] = left_direction.y;
    dest->mf[0][2] = left_direction.z;
    dest->mf[3][0] = pos->x;

    dest->mf[1][0] = up_direction->x;
    dest->mf[1][1] = up_direction->y;
    dest->mf[1][2] = up_direction->z;
    dest->mf[3][1] = pos->y;

    dest->mf[2][0] = forward_direction.x;
    dest->mf[2][1] = forward_direction.y;
    dest->mf[2][2] = forward_direction.z;
    dest->mf[3][2] = pos->z;

    dest->mf[0][3] = 0.0f;
    dest->mf[1][3] = 0.0f;
    dest->mf[2][3] = 0.0f;
    dest->mf[3][3] = 1.0f;
}

/** Stores the matrix product A * B in dest. */
void MtxF_Multiply(MtxF* dest, MtxF* A, MtxF* B) {
    f32 entry0;
    f32 entry1;
    f32 entry2;

    entry0 = A->mf[0][0];
    entry1 = A->mf[0][1];
    entry2 = A->mf[0][2];

    dest->mf[0][0] = (entry0 * B->mf[0][0]) + (entry1 * B->mf[1][0]) + (entry2 * B->mf[2][0]);
    dest->mf[0][1] = (entry0 * B->mf[0][1]) + (entry1 * B->mf[1][1]) + (entry2 * B->mf[2][1]);
    dest->mf[0][2] = (entry0 * B->mf[0][2]) + (entry1 * B->mf[1][2]) + (entry2 * B->mf[2][2]);

    entry0 = A->mf[1][0];
    entry1 = A->mf[1][1];
    entry2 = A->mf[1][2];

    dest->mf[1][0] = (entry0 * B->mf[0][0]) + (entry1 * B->mf[1][0]) + (entry2 * B->mf[2][0]);
    dest->mf[1][1] = (entry0 * B->mf[0][1]) + (entry1 * B->mf[1][1]) + (entry2 * B->mf[2][1]);
    dest->mf[1][2] = (entry0 * B->mf[0][2]) + (entry1 * B->mf[1][2]) + (entry2 * B->mf[2][2]);

    entry0 = A->mf[2][0];
    entry1 = A->mf[2][1];
    entry2 = A->mf[2][2];

    dest->mf[2][0] = (entry0 * B->mf[0][0]) + (entry1 * B->mf[1][0]) + (entry2 * B->mf[2][0]);
    dest->mf[2][1] = (entry0 * B->mf[0][1]) + (entry1 * B->mf[1][1]) + (entry2 * B->mf[2][1]);
    dest->mf[2][2] = (entry0 * B->mf[0][2]) + (entry1 * B->mf[1][2]) + (entry2 * B->mf[2][2]);

    entry0 = A->mf[3][0];
    entry1 = A->mf[3][1];
    entry2 = A->mf[3][2];

    dest->mf[3][0] = (entry0 * B->mf[0][0]) + (entry1 * B->mf[1][0]) + (entry2 * B->mf[2][0]) + B->mf[3][0];
    dest->mf[3][1] = (entry0 * B->mf[0][1]) + (entry1 * B->mf[1][1]) + (entry2 * B->mf[2][1]) + B->mf[3][1];
    dest->mf[3][2] = (entry0 * B->mf[0][2]) + (entry1 * B->mf[1][2]) + (entry2 * B->mf[2][2]) + B->mf[3][2];

    dest->mf[0][3] = dest->mf[1][3] = dest->mf[2][3] = 0.0f;
    dest->mf[3][3] = 1.0f;
}

/** Scales the rows of a matrix by the x, y and z components of a vector. */
void MtxF_ScaleRows(MtxF* dest, MtxF* matrix, Vec3f* scale) {
    s32 i;

    for (i = 0; i < 4; i++) {
        dest->mf[0][i] = matrix->mf[0][i] * scale->x;
        dest->mf[1][i] = matrix->mf[1][i] * scale->y;
        dest->mf[2][i] = matrix->mf[2][i] * scale->z;
        dest->mf[3][i] = matrix->mf[3][i];
    }
}

/** Extracts the per-axis scale from the row lengths of a matrix. */
void MtxF_GetScale(MtxF* matrix, Vec3f* dest) {
    dest->x = sqrtf(SQ(matrix->mf[0][0]) + SQ(matrix->mf[0][1]) + SQ(matrix->mf[0][2]));
    dest->y = sqrtf(SQ(matrix->mf[1][0]) + SQ(matrix->mf[1][1]) + SQ(matrix->mf[1][2]));
    dest->z = sqrtf(SQ(matrix->mf[2][0]) + SQ(matrix->mf[2][1]) + SQ(matrix->mf[2][2]));
}

/** Transforms a short vector by a matrix in place. */
void MtxF_TransformVec3s(MtxF* matrix, Vec3s* dest) {
    f32 entry0 = dest->x;
    f32 entry1 = dest->y;
    f32 entry2 = dest->z;

    dest->x = ((entry0 * matrix->mf[0][0]) + (entry1 * matrix->mf[1][0]) + (entry2 * matrix->mf[2][0])) + matrix->mf[3][0];
    dest->y = ((entry0 * matrix->mf[0][1]) + (entry1 * matrix->mf[1][1]) + (entry2 * matrix->mf[2][1])) + matrix->mf[3][1];
    dest->z = ((entry0 * matrix->mf[0][2]) + (entry1 * matrix->mf[1][2]) + (entry2 * matrix->mf[2][2])) + matrix->mf[3][2];
}

/**
 * Converts a float matrix to the RSP fixed-point format (integer parts first,
 * then fractions).
 */
void MtxF_ToFixed(MtxF* dest, MtxF* src) {
    s32 asFixedPoint;
    s32 i;
    s16* a3 = (s16*)dest;      // all integer parts stored in first 16 bytes
    s16* t0 = (s16*)dest + 16; // all fraction parts stored in last 16 bytes
    f32* t1 = (f32*)src;

    for (i = 0; i < 16; i++) {
        asFixedPoint = *t1++ * (1 << 16);         //! float-to-integer conversion responsible for PU crashes
        *a3++ = GET_HIGH_S16_OF_32(asFixedPoint); // integer part
        *t0++ = GET_LOW_S16_OF_32(asFixedPoint);  // fraction part
    }
}

void MtxF_SetBillboard(MtxF* dest, MtxF* basis, MtxF* transform, Vec3f* local_position);
void func_8000ED9C(MtxF* dest, Vec3f* local_position, Vec3s* rotate, Vec3f* scale, MtxF* basis, MtxF* transform) {
    MtxF sp58;
    MtxF sp18;

    MtxF_SetBillboard(&sp58, basis, transform, local_position);
    MtxF_SetRotationTranslationF(&sp18, &D_80060450, rotate);
    MtxF_Multiply(&sp18, &sp18, &sp58);
    MtxF_ScaleRows(dest, &sp18, scale);
}

/**
 * Computes the distance between two points and the two angles that point from
 * one to the other.
 */
void Vec3f_CalculateDistanceAngles(Vec3f* to, Vec3f* from, f32* euclidean, s16* angle_x, s16* angle_y) {
    f32 x_dist = from->x - to->x;
    f32 y_dist = from->y - to->y;
    f32 z_dist = from->z - to->z;

    *euclidean = sqrtf(SQ(x_dist) + SQ(y_dist) + SQ(z_dist));
    *angle_x = MathUtil_Atan2s(sqrtf(SQ(x_dist) + SQ(z_dist)), y_dist);
    *angle_y = MathUtil_Atan2s(z_dist, x_dist);
}

/** Computes a point at a given distance from a center using two angles. */
void Camera_ComputeEyeFromAngles(Vec3f* from, Vec3f* to, f32 dist, s16 rotation_x, s16 rotation_y) {
    to->x = from->x + (dist * COSS(rotation_x) * SINS(rotation_y));
    to->y = from->y + (dist * SINS(rotation_x));
    to->z = from->z + (dist * COSS(rotation_x) * COSS(rotation_y));
}

/**
 * Helper function for atan2s. Does a look up of the arctangent of y/x assuming
 * the resulting angle is in range [0, 0x2000] (1/8 of a circle).
 */
u16 MathUtil_Atan2Lookup(f32 y, f32 x) {
    u16 ret;

    if (x == 0) {
        ret = gArctanTable[0];
    } else {
        ret = gArctanTable[(s32)(y / x * 1024 + 0.5f)];
    }
    return ret;
}

/**
 * Compute the angle from (0, 0) to (x, y) as a s16. Given that terrain is in
 * the xz-plane, this is commonly called with (z, x) to get a yaw angle.
 */
s16 MathUtil_Atan2s(f32 y, f32 x) {
    u16 ret;

    if (x >= 0) {
        if (y >= 0) {
            if (y >= x) {
                ret = MathUtil_Atan2Lookup(x, y);
            } else {
                ret = 0x4000 - MathUtil_Atan2Lookup(y, x);
            }
        } else {
            y = -y;
            if (y < x) {
                ret = 0x4000 + MathUtil_Atan2Lookup(y, x);
            } else {
                ret = 0x8000 - MathUtil_Atan2Lookup(x, y);
            }
        }
    } else {
        x = -x;
        if (y < 0) {
            y = -y;
            if (y >= x) {
                ret = 0x8000 + MathUtil_Atan2Lookup(x, y);
            } else {
                ret = 0xC000 - MathUtil_Atan2Lookup(y, x);
            }
        } else {
            if (y < x) {
                ret = 0xC000 + MathUtil_Atan2Lookup(y, x);
            } else {
                ret = -MathUtil_Atan2Lookup(x, y);
            }
        }
    }
    return ret;
}

/**
 * Gets a random 16-bit value determined by the guRandom call.
 */
s32 MathUtil_Random16(void) {
    return guRandom() & 0xFFFF; // would prototype this as u16, but doesnt match with other calls.
}

/**
 * Gets a random float between 0.0 to 1.0.
 */
f32 MathUtil_Random_ZeroOne(void) {
    return MathUtil_Random16() / 65536.0f;
}

/** Moves a short toward a target by at most delta and stops on the target. */
s16 Math_StepToS(s16 current, s16 target, s16 delta) {
    s16 temp_v0 = target - current;

    if (temp_v0 < 0) {
        temp_v0 += delta;
        if (temp_v0 > 0) {
            temp_v0 = 0;
        }
    } else {
        temp_v0 -= delta;
        if (temp_v0 < 0) {
            temp_v0 = 0;
        }
    }

    return target - temp_v0;
}

/**
 * Moves an integer toward a target by separate increase and decrease steps and
 * stops on the target.
 */
s32 Math_StepToS32(s32 current, s32 target, s32 increase, s32 decrease) {
    //! If target is close to the max or min s32, then it's possible to overflow
    // past it without stopping.

    if (current < target) {
        current += increase;
        if (current > target) {
            current = target;
        }
    } else {
        current -= decrease;
        if (current < target) {
            current = target;
        }
    }
    return current;
}

/**
 * Moves a float toward a target by separate increase and decrease steps and
 * stops on the target.
 */
f32 Math_StepToF(f32 current, f32 target, f32 increase, f32 decrease) {
    if (current < target) {
        current += increase;
        if (current > target) {
            current = target;
        }
    } else {
        current -= decrease;
        if (current < target) {
            current = target;
        }
    }
    return current;
}

/** Reads a signed bit field of the given length from a packed array of shorts. */
s16 PackedBits_ReadSigned(s16* packed, s32 offset, s32 length) {
    Vec2s_s32 spC;
    s16* temp_a3 = &packed[(offset * length) / 16];
    s16* p_spC = &spC.x;

    p_spC[0] = temp_a3[0];
    p_spC[1] = temp_a3[1];

    spC.xy <<= ((offset * length) % 16);
    spC.xy >>= -length;
    return spC.y;
}

/** Converts RGB channels in the range 0 to 1 to hue, saturation and value. */
void Color_RGBToHSV(f32 r, f32 g, f32 b, Vec3f* dest) {
    f32 temp_ft4;
    f32 var_ft5;
    f32 var_fv0;
    f32 var_fv1;
    s32 var_v0;

    var_v0 = 0x47;
    if (g <= r) {
        var_fv0 = r;
        var_v0 = 0x52;
    } else {
        var_fv0 = g;
    }

    if (var_fv0 < b) {
        var_fv0 = b;
        var_v0 = 0x42;
    }

    if (r <= g) {
        var_fv1 = r;
    } else {
        var_fv1 = g;
    }

    if (b < var_fv1) {
        var_fv1 = b;
    }

    temp_ft4 = var_fv0 + var_fv1;
    dest->z = temp_ft4 - 1.0f;
    if (var_fv0 == var_fv1) {
        dest->y = 0.0f;
        dest->x = 0.0f;
        return;
    }

    if (dest->z <= 0.0f) {
        var_ft5 = var_fv0 - var_fv1;
        dest->y = var_ft5 / temp_ft4;
    } else {
        var_ft5 = var_fv0 - var_fv1;
        dest->y = var_ft5 / (2.0 - temp_ft4);
    }

    if (var_v0 == 0x52) {
        dest->x = (g - b) / var_ft5;
    } else if (var_v0 == 0x47) {
        dest->x = ((b - r) / var_ft5) + 2.0;
    } else {
        dest->x = ((r - g) / var_ft5) + 4.0;
    }

    dest->x *= 60.0f;
    if (dest->x < 0.0f) {
        dest->x += 360.0f;
    }
}

/** Converts an 8-bit RGBA color to HSV. */
void Color_RGBA8ToHSV(Color_RGBA8_u32 color, Vec3f* dest) {
    Color_RGBToHSV((s32)color.r / 255.0f, (s32)color.g / 255.0f, (s32)color.b / 255.0f, dest);
}

/** Converts an RGBA5551 color to HSV. */
void Color_RGB5551ToHSV(u16 color, Vec3f* dest) {
    Color_RGBToHSV(((color & 0xF800) >> 0xB) / 31.0f, ((color & 0x7C0) >> 6) / 31.0f, ((color & 0x3E) >> 1) / 31.0f, dest);
}

/**
 * Helper for HSV to RGB conversion: interpolates one channel for a given hue
 * sector.
 */
f32 Color_HSVInterpolate(f32 hue, f32 low, f32 high) {
    f32 channel;

    if (hue < 0.0f) {
        hue += 360.0f;
    } else {
        while (hue >= 360.0f) {
            hue -= 360.0f;
        }
    }

    if (hue < 60.0f) {
        channel = (((high - low) * hue) / 60.0f) + low;
    } else if ((hue >= 60.0f) && (hue < 180.0f)) {
        channel = high;
    } else if ((hue >= 180.0f) && (hue < 240.0f)) {
        channel = low + (((high - low) * (240.0 - hue)) / 60.0);
    } else {
        channel = low;
    }

    return channel;
}

/** Converts hue, saturation and value to RGB channels in the range 0 to 1. */
void Color_HSVToRGB(f32* arg0, f32* arg1, f32* arg2, Vec3f* arg3) {
    f32 sp24;
    f32 sp20;
    f32 temp_ft4;

    if (arg3->z < -1.0f) {
        arg3->z = -1.0f;
    } else if (arg3->z > 1.0f) {
        arg3->z = 1.0f;
    }

    if (arg3->y < 0.0f) {
        arg3->y = 0.0f;
    } else {
        sp24 = 1.0f;
        if (arg3->y > 1.0f) {
            arg3->y = 1.0f;
        }
    }

    if (arg3->x < 0.0f) {
        arg3->x += 360.0f;
    } else {
        while (arg3->x >= 360.0f) {
            arg3->x -= 360.0f;
        }
    }

    if (arg3->z <= 0.0f) {
        temp_ft4 = arg3->z + 1.0f;
        sp24 = temp_ft4 * 0.5f * (1.0f - arg3->y);
        sp20 = temp_ft4 - sp24;
    } else {
        temp_ft4 = arg3->z + 1.0f;
        sp20 = (temp_ft4 * 0.5 * (1.0f - arg3->y)) + arg3->y;
        sp24 = temp_ft4 - sp20;
    }

    *arg0 = Color_HSVInterpolate(arg3->x + 120.0f, sp24, sp20);
    *arg1 = Color_HSVInterpolate(arg3->x, sp24, sp20);
    *arg2 = Color_HSVInterpolate(arg3->x - 120.0f, sp24, sp20);
}

/** Converts an HSV color to RGBA5551. */
u16 Color_HSVToRGB5551(Vec3f* arg0) {
    f32 sp2C;
    f32 sp28;
    f32 sp24;
    s32 var_a0;
    s32 var_a1;
    s32 var_v1;

    Color_HSVToRGB(&sp2C, &sp28, &sp24, arg0);

    var_a1 = (sp2C * 31.0f) + 0.5f;
    if (var_a1 >= 0x20) {
        var_a1 = 0x1F;
    }

    var_v1 = (sp28 * 31.0f) + 0.5f;
    if (var_v1 >= 0x20) {
        var_v1 = 0x1F;
    }

    var_a0 = (sp24 * 31.0f) + 0.5f;
    if (var_a0 >= 0x20) {
        var_a0 = 0x1F;
    }

    return (var_a1 << 0xB) | (var_v1 << 6) | (var_a0 * 2) | 1;
}

/** Converts an HSV color to 8-bit RGBA, using the given alpha. */
Color_RGBA8_u32* Color_HSVToRGBA8(Color_RGBA8_u32* arg0, Vec3f* arg1, s32 arg2) {
    f32 sp34;
    f32 sp30;
    f32 sp2C;
    s32 var_a0;
    s32 var_a1;
    s32 var_v1;
    Color_RGBA8_u32 sp1C;

    Color_HSVToRGB(&sp34, &sp30, &sp2C, arg1);

    var_a1 = (sp34 * 255.0f) + 0.5f;
    if (var_a1 >= 0x100) {
        var_a1 = 0xFF;
    }

    var_v1 = (sp30 * 255.0f) + 0.5f;
    if (var_v1 >= 0x100) {
        var_v1 = 0xFF;
    }

    var_a0 = (sp2C * 255.0f) + 0.5f;
    if (var_a0 >= 0x100) {
        var_a0 = 0xFF;
    }

    sp1C.r = var_a1;
    sp1C.g = var_v1;
    sp1C.b = var_a0;
    sp1C.a = arg2;

    *arg0 = sp1C;

    return arg0;
}

/** Adjusts an RGBA5551 color in HSV space. */
u16 Color_AdjustRGB5551(u16 arg0, arg1_func_80010CA8 arg1) {
    Vec3f sp24;
    s32 a;
    s32 b;

    if (arg0 & 1) {
        Color_RGB5551ToHSV(arg0, &sp24);

        if (arg1.hueShift != 0) {
            sp24.x += (arg1.hueShift * 0.015625f);
        }

        if (arg1.saturationShift != 0) {
            if (arg1.saturationShift > 0) {
                sp24.y += ((1.0f - sp24.y) * arg1.saturationShift * 0.125f);
            } else {
                sp24.y += (sp24.y * arg1.saturationShift * 0.125f);
            }
        }

        if (arg1.valueShift != 0) {
            a = (((sp24.z + 1.0f) * 0.5f * 255.0f));
            if (arg1.valueShift > 0) {
                b = arg1.valueShift + 7;
            } else {
                b = arg1.valueShift + 8;
            }

            sp24.z = (2.0f * (D_8006BBB0[b][a] / 65535.0f)) - 1.0f;
        }

        arg0 = Color_HSVToRGB5551(&sp24);
    }
    return arg0;
}

/** Adjusts an 8-bit RGBA color in HSV space. */
u32 Color_AdjustRGBA8(u32 arg0, arg1_func_80010CA8 arg1) {
    Vec3f sp2C;
    Color_RGBA8_u32 arg;
    s32 a;
    s32 b;

    arg.rgba = arg0;

    if (arg.a > 0) {
        Color_RGBA8ToHSV(arg, &sp2C);

        if (arg1.hueShift != 0) {
            sp2C.x += (arg1.hueShift * 0.015625f);
        }

        if (arg1.saturationShift != 0) {
            if (arg1.saturationShift > 0) {
                sp2C.y += ((1.0f - sp2C.y) * arg1.saturationShift * 0.125f);
            } else {
                sp2C.y += (sp2C.y * arg1.saturationShift * 0.125f);
            }
        }

        if (arg1.valueShift != 0) {
            a = (((sp2C.z + 1.0f) * 0.5f * 255.0f));

            if (arg1.valueShift > 0) {
                b = arg1.valueShift + 7;
            } else {
                b = arg1.valueShift + 8;
            }

            sp2C.z = (2.0f * (D_8006BBB0[b][a] / 65535.0f)) - 1.0f;
        }

        Color_HSVToRGBA8(&arg, &sp2C, arg.a);
    }

    return arg.rgba;
}
