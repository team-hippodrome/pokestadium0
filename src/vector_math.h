/* Declarations for src/vector_math.c. */
#ifndef VECTOR_MATH_H
#define VECTOR_MATH_H

#include "global.h"

typedef struct unk_D_83402EE0_070 {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ u8 unk_02;
    /* 0x03 */ u8 unk_03[11];
    /* 0x0E */ u8 unk_0E[11];
    /* 0x19 */ char unk19[0x1];
} unk_D_83402EE0_070; // size = 0x1A

typedef struct unk_D_83402EE0_00A {
    /* 0x00 */ u8 unk_00[7];
} unk_D_83402EE0_00A; // size = 0x7

typedef struct unk_D_83402EE0 {
    /* 0x00 */ f32 unk_00;
    /* 0x04 */ u8 unk_04;
    /* 0x05 */ u8 unk_05;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ u8 unk_08;
    /* 0x09 */ u8 unk_09;
    /* 0x0A */ unk_D_83402EE0_00A unk_0A[10];
    /* 0x50 */ Vec3f unk_50;
    /* 0x5C */ Vec3f unk_5C;
    /* 0x68 */ u32 unk_68;
    /* 0x6C */ u8 unk_6C;
    /* 0x6D */ char unk6D[3];
    /* 0x70 */ unk_D_83402EE0_070 unk_70;
} unk_D_83402EE0; // size = 0x8C

typedef struct unk_D_83403C60_050_00C {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
} unk_D_83403C60_050_00C; // size = 0xC

typedef struct unk_func_800314BC_temp_v4 {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s32 unk_04;
} unk_func_800314BC_temp_v4; // size = 0x8

typedef struct unk_D_83407B38_0B0 {
    /* 0x00 */ s32 unk_00;
    /* 0x00 */ s32 unk_08;
} unk_D_83407B38_0B0; // size >= 0xC

// vector_math.c
f32 Math_AbsF32(f32);
void Vec3f_CrossProductComponents(f32, f32, f32, f32, f32, f32, f32*, f32*, f32*);
void Vec3f_NormalizeComponents(f32*, f32*, f32*);
void Mtx_BuildTranslatedDirectionRotation(Mtx*, f32, f32, f32, f32, f32, f32);
void MtxF_ExtractScale(MtxF*, MtxF*);
void MtxF_GetScaleVector(MtxF* arg0, Vec3f* arg1);

#endif // VECTOR_MATH_H
