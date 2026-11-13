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
Strip400State sTrailState;
Strip400Node sTrailPoints[400];
extern s32 pad_D_84398F48[2];
extern s32 pad_D_84389178[2];

void LassoHit_Init(f32 arg0, f32 arg1, f32 arg2, f32 arg3, u8 arg4, u8 arg5, u8 arg6, u8 arg7, u8 arg8, u8 arg9);
f32 Strip400_GetTailFadeRatio(void);
void Radial20_RotateVertexOffset(f32 arg0, UNUSED Vec3f* arg1, Vec3f* arg2, f32 arg3, UNUSED f32 arg4, UNUSED f32 arg5,
                   UNUSED f32 arg6);

/**
 * Moves: Bind (hit), Constrict (hit), Disable (hit), String Shot (hit), Wrap (hit)
 * TODO: Human contributor add screenshot
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Bind, Constrict, String Shot and Wrap. Disable did not use it.
 */
void LassoHit_Init(f32 arg0, f32 arg1, f32 arg2, f32 arg3, u8 arg4, u8 arg5, u8 arg6, u8 arg7, u8 arg8, u8 arg9) {
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

/**
 * Moves: Bind (hit), Constrict (hit), Disable (hit), String Shot (hit), Wrap (hit)
 * TODO: Human contributor add screenshot
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Bind, Constrict, String Shot and Wrap. Disable did not use it.
 */
s32 LassoHit_Update(void) {
    s32 i;
    f32 spB8;
    f32 temp_fs0_2;
    f32 temp_fs4;
    f32 temp_fs5;
    f32 temp_ft0;
    f32 var_fs1;
    Strip400Node* var_s0;
    Strip400State* ptr = &sTrailState;
    f32 sp98;
    f32 sp94;
    f32 sp90;
    f32 tmp2;
    s32 tmp00;
    Vec3f sp7C;

    ptr->unk_00++;
    if (ptr->unk_06 < ptr->unk_00) {
        return -1;
    }

    if ((ptr->unk_06 - 0x28) < ptr->unk_00) {
        ptr->unk_00 = ptr->unk_06 - 0x34;
        ptr->unk_02++;
        if (ptr->unk_02 >= 0x15) {
            return -1;
        }
    } else if (ptr->unk_00 < 0x1E) {
        ptr->unk_2A += 10;
        if (ptr->unk_2A > 0xC8) {
            ptr->unk_2A = 0xC8;
        }
    }

    BattleAnim_GetCurrentOwnerBonePosition(&sp7C);
    sp98 = sp7C.x;
    sp94 = sp7C.y;
    sp90 = sp7C.z;

    ptr->unk_28 += 6;
    if (ptr->unk_28 > 0xC8) {
        ptr->unk_28 = 0xC8;
    }

    if (((ptr->unk_06 - 0x34) < ptr->unk_00) && (ptr->unk_00 < (ptr->unk_06 - 0x28))) {
        ptr->unk_24 -= 0.1;
        if (ptr->unk_24 < 0.25) {
            ptr->unk_24 = 0.25f;
        }
    }

    var_s0 = &sTrailPoints[0];

    for (i = 0; i < ptr->unk_28; i++) {
        tmp00 = ptr->unk_00;

        if ((ptr->unk_06 - 0x28) < tmp00) {
            var_s0->unk_0C -= 6.0;
            if (var_s0->unk_0C < ptr->unk_18) {
                var_s0->unk_0C = ptr->unk_18;
            }
            var_fs1 = __sinf((((ptr->unk_00 + i) % 200) * 251.327419281005859) / 200.0) * 0.1;
        } else if ((ptr->unk_06 - 0x2D) < tmp00) {
            var_fs1 = __sinf((((ptr->unk_00 + i) % 200) * 251.327419281005859) / 200.0) + 2.0;
            var_s0->unk_0C += var_fs1;
        } else if ((ptr->unk_06 - 0x34) < tmp00) {
            var_s0->unk_0C -= 8.0;
            if (var_s0->unk_0C < ptr->unk_18) {
                var_s0->unk_0C = ptr->unk_18;
            }
            var_fs1 = __sinf((((ptr->unk_00 + i) % 200) * 251.327419281005859) / 200.0) * 0.1;
        } else {
            var_fs1 = __sinf((((ptr->unk_00 + i) % 200) * 188.495564460754395) / 200.0);
            var_s0->unk_0C += var_fs1;
        }

        tmp2 = var_s0->unk_0C;

        temp_fs4 = (((tmp00 + i) % 200) * 69.1150403022766113) / 200.0;
        temp_fs5 = (((tmp00 + i) % 200) * 12.566370964050293) / 200.0;

        spB8 = (__sinf(temp_fs4) * tmp2) + sp98;
        temp_fs0_2 = (__sinf(temp_fs5) * (0.7 * tmp2)) + sp94;
        temp_ft0 = __cosf(temp_fs4) * tmp2 + sp90;

        var_s0->unk_08 = temp_ft0;
        var_s0->unk_04 = temp_fs0_2 + var_fs1;
        var_s0->unk_00 = spB8;
        var_s0++;

        var_s0->unk_00 = spB8;
        var_s0->unk_04 = (2.0 * __sinf(temp_fs5 * 3.0)) + temp_fs0_2 + var_fs1;
        var_s0->unk_08 = temp_ft0;
        var_s0++;
    }

    return 0;
}

extern Gfx D_82192AB0[];
/**
 * Not reached in play (2026-11-13): did not run in a tour of the main menu, Pokédex, party, Lab,
 * registration, Free Battle setup and a COM battle (opening, a switch, running, a Pound turn).
 * @unverified Name was previously used only by callers of this address; the definition was still func_.
 */
Gfx* Strip400_Draw(Gfx* arg0) {
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
/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Tri Attack.
 */
void TriAttackRadial_EmitVariantA(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, s16 arg6, u8 arg7, u8 arg8, u8 arg9,
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
/**
 * Not reached in play (2026-11-13): did not run in a tour of the main menu, Pokédex, party, Lab,
 * registration, Free Battle setup and a COM battle (opening, a switch, running, a Pound turn).
 * @unverified Name was previously used only by callers of this address; the definition was still func_.
 */
void Radial20_VariantC(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, s16 arg6, u8 arg7, u8 arg8, u8 arg9,
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

/**
 * Not reached in play (2026-11-13): did not run in a tour of the main menu, Pokédex, party, Lab,
 * registration, Free Battle setup and a COM battle (opening, a switch, running, a Pound turn).
 * @unverified Name was previously used only by callers of this address; the definition was still func_.
 */
void Radial20_UpdateNode(Radial20* arg0) {
    Radial20Node* var_v0;
    UNUSED s32 pad; // FAKE: stack padding
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

extern Gfx D_82192B00[];
extern u8 D_82192B50[];
extern u8 D_82192B54[];
extern u8 D_82192B58[];
extern f32 D_82192B5C[];
/**
 * Not reached in play (2026-11-13): did not run in a tour of the main menu, Pokédex, party, Lab,
 * registration, Free Battle setup and a COM battle (opening, a switch, running, a Pound turn).
 * @unverified Name was previously used only by callers of this address; the definition was still func_.
 */
Gfx* Radial20_Draw(Gfx* arg0) {
    s32 i;
    s32 x;
    s32 j;
    s32 y;
    Radial20* sp1B4;
    Radial20Node* var_s2;
    Vtx* vtx;
    Vec3f sp1A0;

    sp1B4 = D_821A3490;

    for (i = 0; i < 10; i++) {
        if (sp1B4->unk_000 == 1) {
            var_s2 = &sp1B4->unk_048[0];

            switch (sp1B4->unk_008) {
                case 0:
                case 3:
                case 8:
                    sp1B4->unk_01C = Gfx_AllocDisplayList(sizeof(Vtx) * 40);
                    vtx = sp1B4->unk_01C;

                    for (j = 0; j < 20; j++, vtx++) {
                        Radial20_RotateVertexOffset(var_s2->unk_0C, &var_s2->unk_1C, &sp1A0, var_s2->unk_08, 1.0f, 0.0f, 0.0f);

                        vtx->v.ob[0] = var_s2->unk_10.x + sp1A0.x;
                        vtx->v.ob[1] = var_s2->unk_10.y + sp1A0.y;
                        vtx->v.ob[2] = var_s2->unk_10.z + sp1A0.z;
                        vtx->v.cn[0] = sp1B4->unk_00A.r;
                        vtx->v.cn[1] = sp1B4->unk_00A.g;
                        vtx->v.cn[2] = sp1B4->unk_00A.b;
                        vtx->v.cn[3] = var_s2->unk_04;
                        vtx++;

                        if (var_s2->unk_00 <= 0.0) {
                            Radial20_RotateVertexOffset(var_s2->unk_0C + M_PI_F, &var_s2->unk_1C, &sp1A0, var_s2->unk_08, 1.0f, 0.0f,
                                                        0.0f);
                        }

                        vtx->v.ob[0] = var_s2->unk_10.x + sp1A0.x;
                        vtx->v.ob[1] = var_s2->unk_10.y + sp1A0.y;
                        vtx->v.ob[2] = var_s2->unk_10.z + sp1A0.z;
                        vtx->v.cn[0] = sp1B4->unk_00A.r;
                        vtx->v.cn[1] = sp1B4->unk_00A.g;
                        vtx->v.cn[2] = sp1B4->unk_00A.b;
                        vtx->v.cn[3] = var_s2->unk_04;
                        var_s2++;
                    }
                    break;

                case 1:
                    vtx = Gfx_AllocDisplayList(sizeof(Vtx) * 60);
                    sp1B4->unk_01C = vtx;

                    for (j = 0; j < 20; j++, vtx++) {
                        Radial20_RotateVertexOffset(var_s2->unk_0C, &var_s2->unk_1C, &sp1A0, var_s2->unk_08, 1.0f, 0.0f, 0.0f);

                        vtx->v.ob[0] = var_s2->unk_10.x + sp1A0.x;
                        vtx->v.ob[1] = var_s2->unk_10.y + sp1A0.y;
                        vtx->v.ob[2] = var_s2->unk_10.z + sp1A0.z;
                        vtx->v.cn[0] = 0xFF;
                        vtx->v.cn[1] = 0x40;
                        vtx->v.cn[2] = 0x40;
                        vtx->v.cn[3] = var_s2->unk_04;
                        vtx++;

                        if (var_s2->unk_00 <= 0.0) {
                            Radial20_RotateVertexOffset(var_s2->unk_0C + TWO_THIRDS_PI, &var_s2->unk_1C, &sp1A0, var_s2->unk_08,
                                                        1.0f, 0.0f, 0.0f);
                        }

                        vtx->v.ob[0] = var_s2->unk_10.x + sp1A0.x;
                        vtx->v.ob[1] = var_s2->unk_10.y + sp1A0.y;
                        vtx->v.ob[2] = var_s2->unk_10.z + sp1A0.z;
                        vtx->v.cn[0] = 0;
                        vtx->v.cn[1] = 0xA0;
                        vtx->v.cn[2] = 0xFF;
                        vtx->v.cn[3] = var_s2->unk_04;
                        vtx++;

                        if (var_s2->unk_00 <= 0.0) {
                            Radial20_RotateVertexOffset(var_s2->unk_0C + TWO_THIRDS_PI * 2, &var_s2->unk_1C, &sp1A0,
                                                        var_s2->unk_08, 1.0f, 0.0f, 0.0f);
                        }

                        vtx->v.ob[0] = var_s2->unk_10.x + sp1A0.x;
                        vtx->v.ob[1] = var_s2->unk_10.y + sp1A0.y;
                        vtx->v.ob[2] = var_s2->unk_10.z + sp1A0.z;
                        vtx->v.cn[0] = 0xFF;
                        vtx->v.cn[1] = 0xFF;
                        vtx->v.cn[2] = 0;
                        vtx->v.cn[3] = var_s2->unk_04;
                        var_s2++;
                    }
                    break;

                case 5:
                    vtx = Gfx_AllocDisplayList(sizeof(Vtx) * 60);
                    sp1B4->unk_01C = vtx;

                    for (j = 0; j < 20; j++, vtx++) {
                        Radial20_RotateVertexOffset(var_s2->unk_0C, &var_s2->unk_1C, &sp1A0, var_s2->unk_08, 1.0f, 0.0f, 0.0f);

                        vtx->v.ob[0] = var_s2->unk_10.x + sp1A0.x;
                        vtx->v.ob[1] = var_s2->unk_10.y + sp1A0.y;
                        vtx->v.ob[2] = var_s2->unk_10.z + sp1A0.z;
                        vtx->v.cn[0] = sp1B4->unk_00A.r;
                        vtx->v.cn[1] = sp1B4->unk_00A.g;
                        vtx->v.cn[2] = sp1B4->unk_00A.b;
                        vtx->v.cn[3] = var_s2->unk_04;
                        vtx++;

                        if (var_s2->unk_00 <= 0.0) {
                            Radial20_RotateVertexOffset(var_s2->unk_0C + TWO_THIRDS_PI, &var_s2->unk_1C, &sp1A0, var_s2->unk_08,
                                                        1.0f, 0.0f, 0.0f);
                        }

                        vtx->v.ob[0] = var_s2->unk_10.x + sp1A0.x;
                        vtx->v.ob[1] = var_s2->unk_10.y + sp1A0.y;
                        vtx->v.ob[2] = var_s2->unk_10.z + sp1A0.z;
                        vtx->v.cn[0] = sp1B4->unk_00A.r;
                        vtx->v.cn[1] = sp1B4->unk_00A.g;
                        vtx->v.cn[2] = sp1B4->unk_00A.b;
                        vtx->v.cn[3] = var_s2->unk_04;
                        vtx++;

                        if (var_s2->unk_00 <= 0.0) {
                            Radial20_RotateVertexOffset(var_s2->unk_0C + TWO_THIRDS_PI * 2, &var_s2->unk_1C, &sp1A0,
                                                        var_s2->unk_08, 1.0f, 0.0f, 0.0f);
                        }

                        vtx->v.ob[0] = var_s2->unk_10.x + sp1A0.x;
                        vtx->v.ob[1] = var_s2->unk_10.y + sp1A0.y;
                        vtx->v.ob[2] = var_s2->unk_10.z + sp1A0.z;
                        vtx->v.cn[0] = sp1B4->unk_00A.r;
                        vtx->v.cn[1] = sp1B4->unk_00A.g;
                        vtx->v.cn[2] = sp1B4->unk_00A.b;
                        vtx->v.cn[3] = var_s2->unk_04;
                        var_s2++;
                    }
                    break;

                case 6:
                case 7:
                    vtx = Gfx_AllocDisplayList(sizeof(Vtx) * 20 * 6);
                    sp1B4->unk_01C = vtx;

                    for (j = 0; j < 20; j++, var_s2++) {
                        for (x = 0; x < 6; x++) {
                            Radial20_RotateVertexOffset(var_s2->unk_0C + ((2.0 * x * M_PI_F) / 6.0), &var_s2->unk_1C, &sp1A0,
                                                        var_s2->unk_08, 1.0f, 0.0f, 0.0f);

                            vtx->v.ob[0] = var_s2->unk_10.x + sp1A0.x;
                            vtx->v.ob[1] = var_s2->unk_10.y + sp1A0.y;
                            vtx->v.ob[2] = var_s2->unk_10.z + sp1A0.z;
                            vtx->v.cn[0] = sp1B4->unk_00A.r;
                            vtx->v.cn[1] = sp1B4->unk_00A.g;
                            vtx->v.cn[2] = sp1B4->unk_00A.b;
                            vtx->v.cn[3] = 0x64;
                            vtx++;
                        }
                    }
                    break;

                case 9:
                    vtx = Gfx_AllocDisplayList(sizeof(Vtx) * 20 * 3 * 3);
                    sp1B4->unk_01C = vtx;

                    for (j = 0; j < 20; j++, var_s2++) {
                        for (x = 0; x < 3; x++) {
                            for (y = 0; y < 3; y++) {
                                f32 x1, y1, z1;

                                Radial20_RotateVertexOffset(var_s2->unk_0C + ((TWO_PI_F * y) / 12.0f) + ((TWO_PI_F * x) / 3.0f),
                                                            &var_s2->unk_1C, &sp1A0, D_82192B5C[y] * var_s2->unk_08, 1.0f, 0.0f,
                                                            0.0f);

                                x1 = var_s2->unk_10.x + sp1A0.x;
                                y1 = var_s2->unk_10.y + sp1A0.y;
                                z1 = var_s2->unk_10.z + sp1A0.z;

                                vtx->v.ob[0] = x1;
                                vtx->v.ob[1] = y1;
                                vtx->v.ob[2] = z1;

                                if ((y == 0) && ((guRandom() % 100) == 0)) {
                                    AuxiliaryEffect_Spawn(sp1B4->unk_002, x1, y1, z1, 0xA, 0.75f);
                                }

                                vtx->v.cn[0] = ((D_82192B50[x] * (0xFF - var_s2->unk_04)) + (var_s2->unk_04 * 0xFF)) / 255;
                                vtx->v.cn[1] = ((D_82192B54[x] * (0xFF - var_s2->unk_04)) + (var_s2->unk_04 * 0xFF)) / 255;
                                vtx->v.cn[2] = ((D_82192B58[x] * (0xFF - var_s2->unk_04)) + (var_s2->unk_04 * 0xFF)) / 255;
                                vtx->v.cn[3] = var_s2->unk_04;
                                vtx++;
                            }
                        }
                    }
                    break;

                case 2:
                case 4:
                    vtx = Gfx_AllocDisplayList(sizeof(Vtx) * 20 * 15);
                    sp1B4->unk_01C = vtx;

                    for (j = 0; j < 20; j++, var_s2++) {
                        for (x = 0; x < 15; x++) {
                            if (var_s2->unk_00 <= 0.0) {
                                Radial20_RotateVertexOffset(var_s2->unk_0C + ((2.0 * x * M_PI_F) / 15.0), &var_s2->unk_1C,
                                                            &sp1A0, var_s2->unk_08, 1.0f, 0.0f, 0.0f);
                            }

                            vtx->v.ob[0] = var_s2->unk_10.x + sp1A0.x;
                            vtx->v.ob[1] = var_s2->unk_10.y + sp1A0.y;
                            vtx->v.ob[2] = var_s2->unk_10.z + sp1A0.z;
                            vtx->v.cn[0] = sp1B4->unk_00A.r;
                            vtx->v.cn[1] = sp1B4->unk_00A.g;
                            vtx->v.cn[2] = sp1B4->unk_00A.b;
                            vtx->v.cn[3] = var_s2->unk_04;
                            vtx++;
                        }
                    }
                    break;

                default:
                    break;
            }

            vtx = sp1B4->unk_01C;
            for (x = 0; x < 19; x++) {
                switch (sp1B4->unk_008) {
                    case 0:
                    case 3:
                    case 8:
                        gSPDisplayList(arg0++, D_82192B00);
                        gSPVertex(arg0++, vtx, 4, 0);
                        gSP2Triangles(arg0++, 0, 2, 1, 0, 2, 3, 1, 0);
                        vtx += 2;
                        break;

                    default:
                        gSPDisplayList(arg0++, D_82192B00);
                        gSPClearGeometryMode(arg0++, G_CULL_BOTH);
                        gSPSetGeometryMode(arg0++, G_CULL_FRONT);
                        gSPVertex(arg0++, vtx, 6, 0);
                        gSP2Triangles(arg0++, 0, 3, 1, 0, 3, 4, 1, 0);
                        gSP2Triangles(arg0++, 1, 4, 2, 0, 4, 5, 2, 0);
                        gSP2Triangles(arg0++, 2, 5, 0, 0, 5, 3, 0, 0);
                        vtx += 3;
                        break;

                    case 6:
                    case 7:
                        gSPDisplayList(arg0++, D_82192B00);
                        gSPClearGeometryMode(arg0++, G_CULL_BOTH);
                        gSPSetGeometryMode(arg0++, G_CULL_FRONT);
                        gSPVertex(arg0++, vtx, 12, 0);

                        for (j = 0; j < 5; j++) {
                            gSP2Triangles(arg0++, j + 0, j + 6, j + 1, 0, j + 1, j + 6, j + 7, 0);
                        }

                        gSP2Triangles(arg0++, 5, 11, 0, 0, 0, 11, 6, 0);
                        vtx += 6;
                        break;

                    case 2:
                    case 4:
                        gSPDisplayList(arg0++, D_82192B00);
                        gSPVertex(arg0++, vtx, 30, 0);

                        for (j = 0; j < 14; j++) {
                            gSP2Triangles(arg0++, j + 0, j + 15, j + 1, 0, j + 15, j + 16, j + 1, 0);
                        }

                        gSP2Triangles(arg0++, 14, 29, 0, 0, 29, 15, 0, 0);
                        vtx += 15;
                        break;

                    case 9:
                        gSPDisplayList(arg0++, D_82192B00);
                        gSPClearGeometryMode(arg0++, G_CULL_BOTH);
                        gSPSetGeometryMode(arg0++, G_CULL_FRONT);
                        gSPVertex(arg0++, vtx, 18, 0);

                        for (j = 0; j < 3; j++) {
                            u8 idx = j * 3;
                            gSP2Triangles(arg0++, idx + 0, idx + 9, idx + 1, 0, idx + 1, idx + 9, idx + 10, 0);
                            gSP2Triangles(arg0++, idx + 1, idx + 10, idx + 2, 0, idx + 2, idx + 10, idx + 11, 0);
                            gSP2Triangles(arg0++, idx + 2, idx + 11, idx + 0, 0, idx + 0, idx + 11, idx + 9, 0);
                        }

                        vtx += 9;
                        break;
                }
            }

            vtx = sp1B4->unk_01C;
            for (x = 0; x < 19; x++) {
                switch (sp1B4->unk_008) {
                    case 0:
                    case 2:
                    case 3:
                    case 4:
                        break;

                    default:
                        gSPDisplayList(arg0++, D_82192B00);
                        gSPClearGeometryMode(arg0++, G_CULL_BOTH);
                        gSPSetGeometryMode(arg0++, G_CULL_BACK);
                        gSPVertex(arg0++, vtx, 6, 0);
                        gSP2Triangles(arg0++, 0, 3, 1, 0, 3, 4, 1, 0);
                        gSP2Triangles(arg0++, 1, 4, 2, 0, 4, 5, 2, 0);
                        gSP2Triangles(arg0++, 2, 5, 0, 0, 5, 3, 0, 0);
                        vtx += 3;
                        break;

                    case 6:
                    case 7:
                        gSPDisplayList(arg0++, D_82192B00);
                        gSPClearGeometryMode(arg0++, G_CULL_BOTH);
                        gSPSetGeometryMode(arg0++, G_CULL_BACK);
                        gSPVertex(arg0++, vtx, 12, 0);

                        for (j = 0; j < 5; j++) {
                            gSP2Triangles(arg0++, j + 0, j + 6, j + 1, 0, j + 1, j + 6, j + 7, 0);
                        }

                        gSP2Triangles(arg0++, 5, 11, 0, 0, 0, 11, 6, 0);
                        vtx += 6;
                        break;

                    case 9:
                        gSPDisplayList(arg0++, D_82192B00);
                        gSPClearGeometryMode(arg0++, G_CULL_BOTH);
                        gSPSetGeometryMode(arg0++, G_CULL_BACK);
                        gSPVertex(arg0++, vtx, 18, 0);

                        for (j = 0; j < 3; j++) {
                            u8 idx = j * 3;
                            gSP2Triangles(arg0++, idx + 0, idx + 9, idx + 1, 0, idx + 1, idx + 9, idx + 10, 0);
                            gSP2Triangles(arg0++, idx + 1, idx + 10, idx + 2, 0, idx + 2, idx + 10, idx + 11, 0);
                            gSP2Triangles(arg0++, idx + 2, idx + 11, idx + 0, 0, idx + 0, idx + 11, idx + 9, 0);
                        }

                        vtx += 9;
                        break;
                }
            }

            vtx = sp1B4->unk_01C;
            switch (sp1B4->unk_008) {
                case 9:
                    gSPDisplayList(arg0++, D_82192B00);
                    gSPClearGeometryMode(arg0++, G_CULL_BOTH);
                    gSPVertex(arg0++, vtx, 9, 0);
                    gSP2Triangles(arg0++, 2, 1, 0, 0, 5, 4, 3, 0);
                    gSP1Triangle(arg0++, 8, 7, 6, 0);
                    break;
            }
            arg0 = AuxiliaryEffect_Draw(sp1B4->unk_002, arg0);
        }
        sp1B4++;
    }

    return arg0;
}
