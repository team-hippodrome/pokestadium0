/* Declarations for src/matrix.c. */
#ifndef MATRIX_H
#define MATRIX_H

#include "global.h"
#include "moves.h"
#include "pokemon.h"
#include "m2c_macros.h"
#include "math.h"
#include "stdarg.h"

extern Mtx gIdentityMtx;

extern Vec3f D_80060450;

extern Vec3s D_8006045C;

extern Vec3f D_80060464;

extern f32 gSineTable[];

extern f32 gCosineTable[0x1000];

extern s16 gArctanTable[0x401];

// matrix.c
Color_RGBA8* Color_SetRGB(Color_RGBA8* dest, u8 r, u8 g, u8 b);
Color_RGBA8* Color_SetRGBA(Color_RGBA8* dest, u8 r, u8 g, u8 b, u8 alpha);
Vec3f* Vec3f_SetComponents(Vec3f* dest, f32 x, f32 y, f32 z);
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
f32 func_8000F23C(f32, f32, f32, f32);
f32 func_8000F150();                                /* extern */
Vec3f* Vec3f_SetComponentsDuplicate(Vec3f* dest, f32 x, f32 y, f32 z);
M2C_UNK func_8000D700(s32, M2C_UNK, s16, M2C_UNK);  /* extern */
M2C_UNK func_8000D520(s32, s8 *);                 /* extern */
unk_D_800A7440* GfxRect_SetBounds(unk_D_800A7440* arg0, s16 x1, s16 y1, s16 x2, s16 y2);
u16 MathUtil_Atan2Lookup(f32 y, f32 x);
s16 MathUtil_Atan2s(f32 y, f32 x);
s32 MathUtil_Random16(void);
f32 MathUtil_Random_ZeroOne(void);

#endif // MATRIX_H
