/* Stadium Zero fragment012_17ED00. */
/* C ported from the Stadium 1 decomp: src/fragments/battle_engine/battle_engine_34A420.c. */

#include "fragments/battle_engine/battle_engine.h"
#include "gallery.h"
#include "gfx_buffer.h"
#include "math_util.h"
#include "math.h"
typedef struct Strip400State {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ f32 unk_10;
    /* 0x14 */ f32 unk_14;
    /* 0x18 */ f32 unk_18;
    /* 0x1C */ f32 unk_1C;
    /* 0x20 */ f32 unk_20;
    /* 0x24 */ f32 unk_24;
    /* 0x28 */ s16 unk_28;
    /* 0x2A */ s16 unk_2A;
    /* 0x2C */ Vtx* unk_2C;
    /* 0x30 */ Color_RGB8 unk_30;
    /* 0x33 */ Color_RGB8 unk_33;
} Strip400State;
typedef struct Strip400Node {
    /* 0x00 */ f32 unk_00;
    /* 0x04 */ f32 unk_04;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ f32 unk_0C;
} Strip400Node;
extern Strip400State sTrailState;
extern Strip400Node sTrailPoints[400];
extern s32 pad_D_84398F48[2];
extern s32 pad_D_84389178[2];

void Radial20_Init(f32 arg0, f32 arg1, f32 arg2, f32 arg3, u8 arg4, u8 arg5, u8 arg6, u8 arg7, u8 arg8, u8 arg9);
f32 Strip400_GetTailFadeRatio(void);
void Radial20_RotateVertexOffset(f32 arg0, UNUSED Vec3f* arg1, Vec3f* arg2, f32 arg3, UNUSED f32 arg4, UNUSED f32 arg5,
                   UNUSED f32 arg6);

void Radial20_Init(f32 arg0, f32 arg1, f32 arg2, f32 arg3, u8 arg4, u8 arg5, u8 arg6, u8 arg7, u8 arg8, u8 arg9) {
    Strip400State* ptr1 = &sTrailState;
    Strip400Node* ptr2;
    s32 i;

    ptr1->unk_00 = 0;
    ptr1->unk_02 = 0;
    ptr1->unk_04 = 0;
    ptr1->unk_06 = 0x46;
    ptr1->unk_08 = arg0;
    ptr1->unk_0C = arg1;
    ptr1->unk_10 = arg2;
    ptr1->unk_14 = arg3 * 40.0;
    ptr1->unk_18 = arg3 * 20.0;
    ptr1->unk_1C = 0.0f;
    ptr1->unk_20 = arg3;
    ptr1->unk_24 = 1.0f;
    ptr1->unk_28 = 0;
    ptr1->unk_2A = 0;
    ptr1->unk_30.r = arg4;
    ptr1->unk_30.g = arg5;
    ptr1->unk_30.b = arg6;
    ptr1->unk_33.r = arg7;
    ptr1->unk_33.g = arg8;
    ptr1->unk_33.b = arg9;

    ptr2 = &sTrailPoints[0];
    for (i = 0; i < 400; i++, ptr2++) {
        ptr2->unk_00 = arg0;
        ptr2->unk_04 = arg1;
        ptr2->unk_08 = arg2;
        ptr2->unk_0C = ptr1->unk_14;
    }
}

f32 Strip400_GetTailFadeRatio(void) {
    Strip400State* ptr = &sTrailState;
    f32 tmp;
    s32 tmp2 = ptr->unk_00;

    if (tmp2 < (ptr->unk_06 - 0x34)) {
        return 1.0f;
    }

    if (ptr->unk_18 == 0.0f) {
        return 1.0f;
    }

    tmp = (sTrailPoints[ptr->unk_06 * 0].unk_0C * 2.0f) / (ptr->unk_14 + ptr->unk_18);
    return tmp;
}

#ifdef NON_MATCHING
/* TODO: decompile func_821742F0; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_821742F0.s")
#endif

extern Gfx D_82192AB0[];
Gfx* func_821748CC(Gfx* arg0) {
    Vtx* vtx;
    s32 i;
    Strip400Node* var_a0;
    Strip400State* ptr = &sTrailState;

    if (ptr->unk_28 < 2) {
        return arg0;
    }
    ptr->unk_2C = Gfx_AllocDisplayList(ptr->unk_28 * 2 * sizeof(Vtx));
    vtx = ptr->unk_2C;
    var_a0 = &sTrailPoints[0];

    for (i = 0; i < ptr->unk_28; i++) {
        vtx->v.ob[0] = var_a0->unk_00;
        if (var_a0->unk_04 > 0.0) {
            vtx->v.ob[1] = var_a0->unk_04;
        } else {
            vtx->v.ob[1] = 0;
        }
        vtx->v.ob[2] = var_a0->unk_08;
        vtx->v.cn[0] = ptr->unk_30.r;
        vtx->v.cn[1] = ptr->unk_30.g;
        vtx->v.cn[2] = ptr->unk_30.b;
        vtx->v.cn[3] = ptr->unk_2A;

        vtx++;
        var_a0++;

        vtx->v.ob[0] = var_a0->unk_00;
        if (var_a0->unk_04 > 0.0) {
            vtx->v.ob[1] = var_a0->unk_04;
        } else {
            vtx->v.ob[1] = 0;
        }
        vtx->v.ob[2] = var_a0->unk_08;
        vtx->v.cn[0] = ptr->unk_33.r;
        vtx->v.cn[1] = ptr->unk_33.g;
        vtx->v.cn[2] = ptr->unk_33.b;
        vtx->v.cn[3] = (u8)ptr->unk_2A / 2;

        vtx++;
        var_a0++;
    }

    gSPDisplayList(arg0++, D_82192AB0);

    vtx = ptr->unk_2C;
    for (i = 0; i < ptr->unk_28 - 1; i++) {
        gSPVertex(arg0++, vtx, 4, 0);
        gSP2Triangles(arg0++, 0, 2, 1, 0, 2, 3, 1, 0);
        vtx += 2;
    }

    return arg0;
}

extern Radial20 D_821A3490[10];
void Radial20_ResetPool(void) {
    s16 temp_v0;
    s32 i;
    s32 j;
    Radial20* var_a2;
    Radial20Node* var_v1;

    temp_v0 = AuxiliaryEffect_Alloc();
    var_a2 = &D_821A3490[0];

    for (i = 0; i < 10; i++) {
        var_a2->unk_000 = 0;
        var_a2->unk_004 = 0;
        var_a2->unk_006 = 0;

        var_v1 = &var_a2->unk_048[0];
        for (j = 0; j < 20; j++, var_v1++) {
            var_v1->unk_00 = 0.0f;
            var_v1->unk_04 = 0;
            var_v1->unk_08 = 1.0f;
            var_v1->unk_0C = 0.0f;
            var_v1->unk_10.x = 0.0f;
            var_v1->unk_10.y = 0.0f;
            var_v1->unk_10.z = 0.0f;
            var_v1->unk_1C.x = 0.0f;
            var_v1->unk_1C.y = 0.0f;
            var_v1->unk_1C.z = 0.0f;
        }

        var_a2->unk_002 = temp_v0;
        var_a2++;
    }
}

extern Radial20 D_84398F50[10];
extern Radial20 D_821A3490[10];
void func_82174C30(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, s16 arg6, u8 arg7, u8 arg8, u8 arg9,
                   u8 argA, f32 argB, f32 argC, f32 argD, s16 argE) {
    Radial20* var_v0;
    Radial20Node* var_a1_2;
    s32 i;
    s32 j;
    Vec3f sp14;
    Vec3f sp8;

    sp14.x = arg0;
    sp14.y = arg1;
    sp14.z = arg2;
    sp8.x = arg3;
    sp8.y = arg4;
    sp8.z = arg5;

    var_v0 = &D_821A3490[0];

    for (i = 0; i < 10; i++, var_v0++) {
        if (var_v0->unk_000 == 0) {
            var_v0->unk_000 = 1;
            var_v0->unk_004 = 0;
            var_v0->unk_006 = argE;
            var_v0->unk_008 = arg6;
            var_v0->unk_00A.r = arg7;
            var_v0->unk_00A.g = arg8;
            var_v0->unk_00A.b = arg9;
            var_v0->unk_014 = argD;
            var_v0->unk_018 = argB;

            // clang-format off
            for (j = 0; j < 3; j++) { var_v0->unk_038[j] = 0; }
            // clang-format on

            var_a1_2 = &var_v0->unk_048[0];
            for (j = 0; j < 20; j++) {
                var_a1_2->unk_00 = j;
                if (j == 0) {
                    var_a1_2->unk_04 = 0xFF;
                } else {
                    var_a1_2->unk_04 = (argA * (0x13 - j)) / 20;
                }
                var_a1_2->unk_08 = argC;
                var_a1_2->unk_0C = 0.0f;
                var_a1_2->unk_10 = sp14;
                var_a1_2->unk_1C = sp8;
                var_a1_2++;
            }
            break;
        }
    }
}

extern Radial20 D_821A3490[10];
void Radial20_VariantB(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, s16 arg6, u8 arg7, u8 arg8, u8 arg9,
                   u8 argA, f32 argB, f32 argC, f32 argD, s16 argE) {
    Radial20* var_v0;
    Radial20Node* var_v1_2;
    s32 i;
    s32 j;
    Vec3f spC;
    Vec3f sp0;

    spC.x = arg0;
    spC.y = arg1;
    spC.z = arg2;
    sp0.x = arg3;
    sp0.y = arg4;
    sp0.z = arg5;

    var_v0 = &D_821A3490[0];

    for (i = 0; i < 10; i++, var_v0++) {
        if (var_v0->unk_000 == 0) {
            var_v0->unk_000 = 1;
            var_v0->unk_004 = 0;
            var_v0->unk_006 = argE;
            var_v0->unk_008 = arg6;
            var_v0->unk_00A.r = arg7;
            var_v0->unk_00A.g = arg8;
            var_v0->unk_00A.b = arg9;
            var_v0->unk_014 = argD;
            var_v0->unk_018 = argB;

            var_v1_2 = &var_v0->unk_048[0];
            for (j = 0; j < 20; j++, var_v1_2++) {
                var_v1_2->unk_00 = j;
                var_v1_2->unk_04 = argA;
                var_v1_2->unk_08 = argC;
                var_v1_2->unk_0C = 0.0f;
                var_v1_2->unk_10 = spC;
                var_v1_2->unk_1C = sp0;
            }
            break;
        }
    }
}

extern Radial20 D_821A3490[10];
void func_82175068(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, s16 arg6, u8 arg7, u8 arg8, u8 arg9,
                   u8 argA, f32 argB, f32 argC, f32 argD, s16 argE) {
    Radial20* var_v0;
    Radial20Node* var_s0;
    s32 i;
    s32 j;
    Vec3f spBC;
    Vec3f spB0;
    s32 spA4;
    s32 temp_fp;
    s32 temp_s2;
    s32 temp_s3;
    s32 temp_s4;
    s32 temp_s7;
    s32 tmp;

    spBC.x = arg0;
    spBC.y = arg1;
    spBC.z = arg2;
    spB0.x = arg3;
    spB0.y = arg4;
    spB0.z = arg5;

    var_v0 = &D_821A3490[0];

    for (i = 0; i < 10; i++, var_v0++) {
        if (var_v0->unk_000 == 0) {
            var_s0 = &var_v0->unk_048[0];

            var_v0->unk_000 = 1;
            var_v0->unk_004 = 0;
            var_v0->unk_006 = argE;
            var_v0->unk_008 = arg6;
            var_v0->unk_00A.r = arg7;
            var_v0->unk_00A.g = arg8;
            var_v0->unk_00A.b = arg9;
            var_v0->unk_014 = argD;
            var_v0->unk_018 = argB;

            temp_s7 = (guRandom() % 20) + 2;
            temp_fp = (guRandom() % 10) + 4;
            spA4 = (guRandom() % 20) + 2;
            temp_s4 = (guRandom() % 10) + 4;

            for (j = 0, temp_s2 = spA4, temp_s3 = temp_s7; j < 20; j++) {
                var_s0->unk_00 = j;
                var_s0->unk_04 = argA;
                var_s0->unk_08 = argC;
                var_s0->unk_0C = 0.0f;
                var_s0->unk_10 = spBC;
                var_s0->unk_1C = spB0;

                var_s0->unk_1C.y += 2.0 * __sinf(((temp_s3 % temp_fp) * TWO_PI) / temp_fp) *
                                    __sinf(((temp_s2 % (temp_s4 + 0x14)) * TWO_PI) / (temp_s4 + 0x14));
                var_s0->unk_1C.z += 0.5 * __sinf(((temp_s2 % temp_s4) * TWO_PI) / temp_s4);
                tmp = j * 0.5;
                var_s0->unk_10.x += var_s0->unk_1C.x * ((j * 0.5) - tmp);

                temp_s2++;
                temp_s3++;
                var_s0++;
            }
            break;
        }
    }
}

extern Radial20 D_821A3490[10];
void func_82175440(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, s16 arg6, u8 arg7, u8 arg8, u8 arg9,
                   u8 argA, f32 argB, f32 argC, f32 argD, s16 argE) {
    Radial20* var_v0;
    Radial20Node* var_s0;
    s32 i;
    s32 j;
    Vec3f spBC;
    Vec3f spB0;
    s32 spA4;
    s32 temp_fp;
    s32 temp_s2;
    s32 temp_s3;
    s32 temp_s4;
    s32 temp_s7;
    s32 tmp;

    spBC.x = arg0;
    spBC.y = arg1;
    spBC.z = arg2;
    spB0.x = arg3;
    spB0.y = arg4;
    spB0.z = arg5;

    var_v0 = &D_821A3490[0];

    for (i = 0; i < 10; i++, var_v0++) {
        if (var_v0->unk_000 == 0) {
            var_s0 = &var_v0->unk_048[0];

            var_v0->unk_000 = 1;
            var_v0->unk_004 = 0;
            var_v0->unk_006 = argE;
            var_v0->unk_008 = arg6;
            var_v0->unk_00A.r = arg7;
            var_v0->unk_00A.g = arg8;
            var_v0->unk_00A.b = arg9;
            var_v0->unk_014 = argD;
            var_v0->unk_018 = argB;

            temp_s7 = (guRandom() % 20) + 2;
            temp_fp = (guRandom() % 10) + 4;
            spA4 = (guRandom() % 20) + 2;
            temp_s4 = (guRandom() % 10) + 4;

            for (j = 0, temp_s2 = spA4, temp_s3 = temp_s7; j < 20; j++) {
                var_s0->unk_00 = j;
                var_s0->unk_04 = argA;
                var_s0->unk_08 = argC;
                var_s0->unk_0C = 0.0f;
                var_s0->unk_10 = spBC;
                var_s0->unk_1C = spB0;

                var_s0->unk_1C.z += 2.5 * __sinf(((temp_s3 % temp_fp) * TWO_PI) / temp_fp) *
                                    __sinf(((temp_s2 % (temp_s4 + 0x14)) * TWO_PI) / (temp_s4 + 0x14));
                var_s0->unk_1C.y += 0.5 * __sinf(((temp_s2 % temp_s4) * TWO_PI) / temp_s4);
                tmp = j * 0.5;
                var_s0->unk_10.x += var_s0->unk_1C.x * ((j * 0.5) - tmp);

                temp_s2++;
                temp_s3++;
                var_s0++;
            }
            break;
        }
    }
}

extern Radial20 D_821A3490[10];
void Radial20_VariantE(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, s16 arg6, u8 arg7, u8 arg8, u8 arg9,
                   u8 argA, f32 argB, f32 argC, f32 argD, s16 argE) {
    Radial20* var_v0;
    Radial20Node* var_s0;
    s32 i;
    s32 j;
    Vec3f spBC;
    Vec3f spB0;
    s32 temp_fp;
    s32 temp_s5;
    s32 temp_s6;
    s32 temp_s7;

    spBC.x = arg0;
    spBC.y = arg1;
    spBC.z = arg2;
    spB0.x = arg3;
    spB0.y = arg4;
    spB0.z = arg5;

    var_v0 = &D_821A3490[0];

    for (i = 0; i < 10; i++, var_v0++) {
        if (var_v0->unk_000 == 0) {
            var_s0 = &var_v0->unk_048[0];

            var_v0->unk_000 = 1;
            var_v0->unk_004 = 0;
            var_v0->unk_006 = argE;
            var_v0->unk_008 = arg6;
            var_v0->unk_00A.r = arg7;
            var_v0->unk_00A.g = arg8;
            var_v0->unk_00A.b = arg9;
            var_v0->unk_014 = argD;
            var_v0->unk_018 = argB;

            temp_s5 = RAND(20) + 2;
            temp_s7 = RAND(10) + 4;
            temp_s6 = RAND(20) + 2;
            temp_fp = RAND(10) + 4;

            for (j = 0; j < 20; j++) {
                var_s0->unk_00 = j;
                var_s0->unk_04 = argA;
                var_s0->unk_08 = argC;
                var_s0->unk_0C = 0.0f;
                var_s0->unk_10 = spBC;

                var_s0->unk_10.y += 5.0 * __sinf((((temp_s5 + j) % temp_s7) * TWO_PI) / temp_s7) *
                                    __sinf((((temp_s6 + j) % (temp_fp + 20)) * TWO_PI) / (temp_fp + 20));
                var_s0->unk_10.z += 5.0 * __cosf((((temp_s5 + j) % temp_s7) * TWO_PI) / temp_s7) *
                                    __cosf((((temp_s6 + j) % (temp_fp + 20)) * TWO_PI) / (temp_fp + 20));
                var_s0->unk_1C = spB0;

                var_s0->unk_10.x += var_s0->unk_1C.x * ((j * 0.5) - (s32)(j * 0.5));

                var_s0++;
            }
            break;
        }
    }
}

void Radial20_RotateVertexOffset(f32 arg0, UNUSED Vec3f* arg1, Vec3f* arg2, f32 arg3, UNUSED f32 arg4, UNUSED f32 arg5,
                   UNUSED f32 arg6) {
    UNUSED MtxF pad;
    MtxF sp30;
    UNUSED s32 pad2[2];

    guRotateF(sp30.mf, (arg0 * 360.0) / TWO_PI, 1.0f, 0.0f, 0.0f);
    guMtxXFMF(sp30.mf, 0.0f, 0.0f, arg3, &arg2->x, &arg2->y, &arg2->z);
}

void func_82175C74(Radial20* arg0) {
    Radial20Node* var_v0;
    UNUSED s32 pad;
    s32 i;
    Vec3f sp28;

    BattleAnim_GetSecondaryOwnerAnchorPosition(&sp28);

    switch (arg0->unk_008) {
        case 0:
            var_v0 = &arg0->unk_048[0];
            for (i = 0; i < 20; i++, var_v0++) {
                if (var_v0->unk_00 > 0.0) {
                    var_v0->unk_00 -= 1.0;
                } else {
                    var_v0->unk_10.x += var_v0->unk_1C.x;
                    var_v0->unk_10.y += var_v0->unk_1C.y;
                    var_v0->unk_10.z += var_v0->unk_1C.z;
                    var_v0->unk_0C += arg0->unk_018;

                    var_v0->unk_08 += 1.0;
                    if (arg0->unk_014 < var_v0->unk_08) {
                        var_v0->unk_08 = arg0->unk_014;
                    }
                }
            }
            break;

        case 3:
        case 8:
            var_v0 = &arg0->unk_048[0];
            for (i = 0; i < 20; i++, var_v0++) {
                if (var_v0->unk_00 > 0.0) {
                    var_v0->unk_10 = sp28;
                    var_v0->unk_00 -= 1.0;
                } else {
                    var_v0->unk_10.x += var_v0->unk_1C.x;
                    var_v0->unk_10.y += var_v0->unk_1C.y;
                    var_v0->unk_10.z += var_v0->unk_1C.z;

                    var_v0->unk_0C += arg0->unk_018;

                    if (var_v0->unk_1C.x > 1.0) {
                        var_v0->unk_1C.x -= 0.1;
                    }

                    if (var_v0->unk_1C.x < -1.0) {
                        var_v0->unk_1C.x += 0.1;
                    }

                    var_v0->unk_1C.y -= 0.2;
                    if (var_v0->unk_1C.y < -1.0) {
                        var_v0->unk_1C.y = -1.0f;
                    }

                    if (var_v0->unk_10.y < 0.0) {
                        var_v0->unk_10.y = 0.0f;
                    }
                }
            }
            break;

        default:
            var_v0 = &arg0->unk_048[0];
            for (i = 0; i < 20; i++, var_v0++) {
                if (var_v0->unk_00 > 0.0) {
                    var_v0->unk_10 = sp28;
                    var_v0->unk_00 -= 1.0;
                } else {
                    var_v0->unk_10.x += var_v0->unk_1C.x;
                    var_v0->unk_10.y = sp28.y;
                    var_v0->unk_10.z = sp28.z;

                    var_v0->unk_0C += arg0->unk_018;
                    var_v0->unk_08 += 1.0;

                    if (arg0->unk_014 < var_v0->unk_08) {
                        var_v0->unk_08 = arg0->unk_014;
                    }
                }
            }
            break;

        case 6:
            var_v0 = &arg0->unk_048[0];
            for (i = 0; i < 20; i++, var_v0++) {
                if (var_v0->unk_00 > 0.0) {
                    var_v0->unk_10 = sp28;
                    var_v0->unk_00 -= 1.0;
                } else {
                    var_v0->unk_10.x += var_v0->unk_1C.x;
                    var_v0->unk_10.y += var_v0->unk_1C.y;
                    var_v0->unk_10.z += var_v0->unk_1C.z;

                    var_v0->unk_0C += arg0->unk_018;
                    var_v0->unk_08 += 1.0;

                    if (arg0->unk_014 < var_v0->unk_08) {
                        var_v0->unk_08 = arg0->unk_014;
                    }
                }
            }
            break;

        case 7:
        case 9:
            var_v0 = &arg0->unk_048[0];
            for (i = 0; i < 20; i++, var_v0++) {
                if (var_v0->unk_00 > 0.0) {
                    var_v0->unk_00 -= 1.0;
                } else {
                    var_v0->unk_10.x += var_v0->unk_1C.x;
                    var_v0->unk_10.y += var_v0->unk_1C.y;
                    var_v0->unk_10.z += var_v0->unk_1C.z;

                    var_v0->unk_0C += arg0->unk_018;
                    var_v0->unk_08 += 1.0;

                    if (arg0->unk_014 < var_v0->unk_08) {
                        var_v0->unk_08 = arg0->unk_014;
                    }
                }
            }
            break;

        case 2:
        case 4:
            var_v0 = &arg0->unk_048[0];
            for (i = 0; i < 20; i++, var_v0++) {
                if (var_v0->unk_00 > 0.0) {
                    var_v0->unk_00 -= 1.0;
                } else {
                    var_v0->unk_10.x += var_v0->unk_1C.x;
                    var_v0->unk_10.y += var_v0->unk_1C.y;
                    var_v0->unk_10.z += var_v0->unk_1C.z;

                    var_v0->unk_0C += arg0->unk_018;
                    var_v0->unk_08 += 1.0;

                    if (arg0->unk_014 < var_v0->unk_08) {
                        var_v0->unk_08 = arg0->unk_014;
                    }
                }
            }
            break;
    }
}

extern Radial20 D_821A3490[10];
s32 Radial20_IsComplete(void) {
    s32 i;
    s32 var_s2 = 0;
    Radial20* var_s0 = D_821A3490;

    for (i = 0; i < 10; i++, var_s0++) {
        if (var_s0->unk_000 == 1) {
            var_s0->unk_004++;
            if (var_s0->unk_006 < var_s0->unk_004) {
                var_s0->unk_000 = 0;
                if (var_s0->unk_008 == 9) {}  // karodo
            } else {
                Radial20_UpdateNode(var_s0);
                var_s2++;
            }
            AuxiliaryEffect_Update(var_s0->unk_002);
        }
    }

    if (var_s2 > 0) {
        return 0;
    }
    return -1;
}

#ifdef NON_MATCHING
/* TODO: decompile func_821765B4; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_821765B4.s")
#endif
