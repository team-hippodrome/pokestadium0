/* Stadium Zero fragment012_17ED00. */
/* C ported from the Stadium 1 decomp: src/fragments/battle_engine/battle_engine_34E1A0.c. */

#include "fragments/battle_engine/battle_engine.h"
#include "math.h"
#include "gallery.h"
#include "gfx_buffer.h"
extern Trail40 sWaterSurface;
extern Gfx D_82192B98[];

void HypnosisScreechTrail_Init(s16 arg0);
void HypnosisScreechTrail_Start(s32 arg0, s32 arg1);
void HypnosisScreechTrailNode_FillVertex(Trail40Node* arg0, Vtx* arg1);
s32 HypnosisScreechTrail_IsComplete(void);
Gfx* HypnosisScreechTrail_Draw(Gfx* arg0);

void Trail40_Reset(void);

/**
 * @unverified Name from Stadium 1.
 */
void HypnosisScreechTrail_Init(s16 arg0) {
    s32 i;
    s32 j;
    s16 tmp1;
    s16 tmp2;
    s16 tmp3;
    Trail40Node* var_v0 = &sWaterSurface.unk_0014[0][0];

    sWaterSurface.unk_0000 = 0;
    sWaterSurface.unk_0002 = arg0;
    sWaterSurface.unk_0004 = 0;
    sWaterSurface.unk_0008 = 0.01f;

    for (i = 0; i < 16; i++) {
        for (j = 0; j < 16; j++) {
            tmp1 = i * 0x20;
            tmp3 = tmp1 * 0x10;
            tmp2 = j * 0x20;

            var_v0->unk_00 = (i * 9.0f) - 72.0f;
            var_v0->unk_04 = 1.0f;
            var_v0->unk_08 = (j * 7.0f) - 56.0f;

            var_v0->unk_18 = tmp1 * 0x10;
            var_v0->unk_1A = tmp2 * 0x10;

            var_v0++;
        }
    }
}

/**
 * @unverified Name from Stadium 1.
 */
void HypnosisScreechTrail_Start(s32 arg0, s32 arg1) {
    f32 sp84;
    f32 sp80;
    f32 sp7C;
    f32 sp78;
    f32 sp74;
    f32 sp70;
    f32 sp6C;
    f32 sp68;
    f32 sp64;
    f32 sp60;
    f32 sp5C;
    f32 sp58;
    f32 sp54;
    f32 sp50;
    f32 sp4C;
    UNUSED s32 pad; // FAKE: stack padding
    s16 sp46;

    sp6C = sWaterSurface.unk_0014[arg0][arg1].unk_00;
    sp68 = sWaterSurface.unk_0014[arg0][arg1].unk_04;
    sp64 = sWaterSurface.unk_0014[arg0][arg1].unk_08;
    sp84 = 0.0f;
    sp80 = 0.0f;
    sp7C = 0.0f;
    sp46 = 0;

    if ((arg0 > 0) && (arg1 >= 1)) {
        sp60 = sWaterSurface.unk_0014[arg0 - 1][arg1].unk_00 - sp6C;
        sp5C = sWaterSurface.unk_0014[arg0 - 1][arg1].unk_04 - sp68;
        sp58 = sWaterSurface.unk_0014[arg0 - 1][arg1].unk_08 - sp64;
        Vec3f_NormalizeComponents(&sp60, &sp5C, &sp58);
        sp54 = sWaterSurface.unk_0014[arg0][arg1 - 1].unk_00 - sp6C;
        sp50 = sWaterSurface.unk_0014[arg0][arg1 - 1].unk_04 - sp68;
        sp4C = sWaterSurface.unk_0014[arg0][arg1 - 1].unk_08 - sp64;
        Vec3f_NormalizeComponents(&sp54, &sp50, &sp4C);
        Vec3f_CrossProductComponents(sp60, sp5C, sp58, sp54, sp50, sp4C, &sp78, &sp74, &sp70);
        Vec3f_NormalizeComponents(&sp78, &sp74, &sp70);
        sp84 += sp78;
        sp80 += sp74;
        sp7C += sp70;
        sp46 = 1;
    }

    if ((0 < arg0) && (arg1 < 15)) {
        sp60 = sWaterSurface.unk_0014[arg0 - 1][arg1].unk_00 - sp6C;
        sp5C = sWaterSurface.unk_0014[arg0 - 1][arg1].unk_04 - sp68;
        sp58 = sWaterSurface.unk_0014[arg0 - 1][arg1].unk_08 - sp64;
        Vec3f_NormalizeComponents(&sp60, &sp5C, &sp58);
        sp54 = sWaterSurface.unk_0014[arg0][arg1 + 1].unk_00 - sp6C;
        sp50 = sWaterSurface.unk_0014[arg0][arg1 + 1].unk_04 - sp68;
        sp4C = sWaterSurface.unk_0014[arg0][arg1 + 1].unk_08 - sp64;
        Vec3f_NormalizeComponents(&sp54, &sp50, &sp4C);
        Vec3f_CrossProductComponents(sp60, sp5C, sp58, sp54, sp50, sp4C, &sp78, &sp74, &sp70);
        Vec3f_NormalizeComponents(&sp78, &sp74, &sp70);
        sp84 += sp78;
        sp80 += sp74;
        sp7C += sp70;
        sp46 += 1;
    }

    if ((arg0 < 15) && (arg1 >= 1)) {
        sp60 = sWaterSurface.unk_0014[arg0 + 1][arg1].unk_00 - sp6C;
        sp5C = sWaterSurface.unk_0014[arg0 + 1][arg1].unk_04 - sp68;
        sp58 = sWaterSurface.unk_0014[arg0 + 1][arg1].unk_08 - sp64;
        Vec3f_NormalizeComponents(&sp60, &sp5C, &sp58);
        sp54 = sWaterSurface.unk_0014[arg0][arg1 - 1].unk_00 - sp6C;
        sp50 = sWaterSurface.unk_0014[arg0][arg1 - 1].unk_04 - sp68;
        sp4C = sWaterSurface.unk_0014[arg0][arg1 - 1].unk_08 - sp64;
        Vec3f_NormalizeComponents(&sp54, &sp50, &sp4C);
        Vec3f_CrossProductComponents(sp60, sp5C, sp58, sp54, sp50, sp4C, &sp78, &sp74, &sp70);
        Vec3f_NormalizeComponents(&sp78, &sp74, &sp70);
        sp84 += sp78;
        sp80 += sp74;
        sp7C += sp70;
        sp46 += 1;
    }

    if ((arg0 < 15) && (arg1 < 15)) {
        sp60 = sWaterSurface.unk_0014[arg0 + 1][arg1].unk_00 - sp6C;
        sp5C = sWaterSurface.unk_0014[arg0 + 1][arg1].unk_04 - sp68;
        sp58 = sWaterSurface.unk_0014[arg0 + 1][arg1].unk_08 - sp64;
        Vec3f_NormalizeComponents(&sp60, &sp5C, &sp58);
        sp54 = sWaterSurface.unk_0014[arg0][arg1 + 1].unk_00 - sp6C;
        sp50 = sWaterSurface.unk_0014[arg0][arg1 + 1].unk_04 - sp68;
        sp4C = sWaterSurface.unk_0014[arg0][arg1 + 1].unk_08 - sp64;
        Vec3f_NormalizeComponents(&sp54, &sp50, &sp4C);
        Vec3f_CrossProductComponents(sp60, sp5C, sp58, sp54, sp50, sp4C, &sp78, &sp74, &sp70);
        Vec3f_NormalizeComponents(&sp78, &sp74, &sp70);
        sp84 -= sp78;
        sp80 -= sp74;
        sp7C -= sp70;
        sp46 += 1;
    }

    if (sp46 != 0) {
        if ((sp84 == 0.0) && (sp80 == 0.0) && (sp7C == 0.0)) {
            sp80 = 1.0f;
        } else {
            Vec3f_NormalizeComponents(&sp84, &sp80, &sp7C);
        }
        sWaterSurface.unk_0014[arg0][arg1].unk_0C = sp84;
        sWaterSurface.unk_0014[arg0][arg1].unk_10 = sp80;
        sWaterSurface.unk_0014[arg0][arg1].unk_14 = sp7C;
    }
}

/**
 * @unverified Name from Stadium 1.
 */
void HypnosisScreechTrailNode_FillVertex(Trail40Node* arg0, Vtx* arg1) {
    f32 r;
    f32 g;
    f32 b;

    arg1->v.ob[0] = arg0->unk_00;
    arg1->v.ob[1] = arg0->unk_04;
    arg1->v.ob[2] = arg0->unk_08;

    arg1->v.tc[0] = arg0->unk_18;
    arg1->v.tc[1] = arg0->unk_1A;

    r = arg0->unk_0C;
    g = arg0->unk_10;
    b = arg0->unk_14;

    arg1->v.cn[0] = (s32)(r * 120.0);
    arg1->v.cn[1] = (s32)(g * 120.0);
    arg1->v.cn[2] = (s32)(b * 120.0);
    arg1->v.cn[3] = sWaterSurface.unk_0004;
}

/**
 * @unverified Name from Stadium 1.
 */
s32 HypnosisScreechTrail_IsComplete(void) {
    Trail40Node* var_s1;
    s32 i;
    s32 j;
    f32 temp_fv1_2;
    f32 tmp;

    sWaterSurface.unk_0000 = sWaterSurface.unk_0000 + 1;
    if (sWaterSurface.unk_0002 < sWaterSurface.unk_0000) {
        return -1;
    }
    if (sWaterSurface.unk_0000 < 0x1E) {
        sWaterSurface.unk_0004 += 0xA;
        if (sWaterSurface.unk_0004 >= 0x81) {
            sWaterSurface.unk_0004 = 0x80;
        }
    } else if ((sWaterSurface.unk_0002 - 0x1E) < sWaterSurface.unk_0000) {
        sWaterSurface.unk_0004 -= 0xA;
        if (sWaterSurface.unk_0004 < 0) {
            sWaterSurface.unk_0004 = 0;
        }
    }

    if (sWaterSurface.unk_0008 < 1.0) {
        sWaterSurface.unk_0008 += 0.05;
    }

    var_s1 = &sWaterSurface.unk_0014[0][0];
    for (i = 0; i < 16; i++) {
        for (j = 0; j < 16; j++) {
            temp_fv1_2 = 1.0 - (sqrtf(SQ(var_s1->unk_00) + SQ(var_s1->unk_08)) / 101.8224f);
            tmp = __sinf((((f32)(sWaterSurface.unk_0000 % 20) / 20.0) + (3.0 * temp_fv1_2)) * 6.2831854820251465) *
                  ((f64)sWaterSurface.unk_0008 * temp_fv1_2);
            var_s1->unk_04 = tmp;
            var_s1++;
        }
    }

    for (i = 0; i < 16; i++) {
        for (j = 0; j < 16; j++) {
            HypnosisScreechTrail_Start(i, j);
        }
    }

    return 0;
}

s32 func_8000515C(s32);
s8* func_8213C80C(void);
void func_80031F14(f32*, f32*, f32*);
void func_800320A8(s32, f32, f32, f32, f32, f32, f32);
extern s32 D_821A6F60;
void func_821787C4(void) {
    s8* temp_v0;
    f32 tmp1;
    f32 tmp2;
    f32 tmp3;
    f32 tmp4;
    f32 tmp5;
    f32 tmp6;
    f32 sp68;
    f32 sp64;
    f32 sp60;
    f32 sp5C;

    D_821A6F60 = func_8000515C(0x40);
    temp_v0 = func_8213C80C();

    tmp4 = *(f32*)(temp_v0 + 0xB4);
    tmp5 = *(f32*)(temp_v0 + 0xB8);
    tmp6 = *(f32*)(temp_v0 + 0xBC);

    tmp1 = *(f32*)(temp_v0 + 0xA8);
    tmp2 = *(f32*)(temp_v0 + 0xAC);
    tmp3 = *(f32*)(temp_v0 + 0xB0);

    sp5C = *(f32*)(temp_v0 + 0x2C);
    sp68 = tmp4 - tmp1;
    sp64 = tmp5 - tmp2;
    sp60 = tmp6 - tmp3;

    func_80031F14(&sp68, &sp64, &sp60);

    tmp1 = (140.0f * sp68) / (sp5C / 30.0f) + tmp1;
    tmp2 = (140.0f * sp64) / (sp5C / 30.0f) + tmp2;
    tmp3 = (140.0f * sp60) / (sp5C / 30.0f) + tmp3;

    func_800320A8(D_821A6F60, tmp1, tmp2, tmp3, tmp4, tmp5, tmp6);
}

/**
 * @unverified Name from Stadium 1.
 */
Gfx* HypnosisScreechTrail_Draw(Gfx* arg0) {
    s32 i;
    s32 j;
    Trail40Node* var_s2;
    s32 var_s4;
    Vtx* vtx;
    s32 idx;

    var_s4 = 0;
    sWaterSurface.unk_000C = Gfx_AllocDisplayList(sizeof(Vtx) * 16 * 16);

    vtx = sWaterSurface.unk_000C;
    var_s2 = &sWaterSurface.unk_0014[0][0];
    for (i = 0; i < 16; i++) {
        for (j = 0; j < 16; j++) {
            HypnosisScreechTrailNode_FillVertex(var_s2, vtx);
            var_s2++;
            vtx++;
        }
    }

    Trail40_Reset();

    gDPLoadTextureBlock(arg0++, sBattleAnimAssetPointers[0xA8], G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0, G_TX_NOMIRROR | G_TX_WRAP,
                        G_TX_NOMIRROR | G_TX_WRAP, 5, 5, G_TX_NOLOD, G_TX_NOLOD);
    gSPDisplayList(arg0++, D_82192B98);
    gDPSetPrimColor(arg0++, 0, 0, 255, 255, 255, sWaterSurface.unk_0004);
    gSPMatrix(arg0++, sWaterSurface.unk_0010, G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW);

    vtx = sWaterSurface.unk_000C;
    for (i = 0; i < 15; i++) {
        for (j = 0; j < 15; j++) {
            idx = (i + 0) * 16 + j;

            gSPVertex(arg0++, &vtx[idx + 0], 1, 0);
            gSPVertex(arg0++, &vtx[idx + 1], 1, 1);
            gSPVertex(arg0++, &vtx[((i + 1) * 16 + j) + (0 * 16) + 0], 1, 2);
            gSPVertex(arg0++, &vtx[idx + (1 * 16) + 1], 1, 3);

            if (!(var_s4 & 1)) {
                gSP2Triangles(arg0++, 1, 2, 0, 0, 1, 3, 2, 0);
            } else {
                gSP2Triangles(arg0++, 3, 2, 0, 0, 1, 3, 0, 0);
            }

            var_s4++;
        }
    }

    gSPPopMatrix(arg0++, G_MTX_MODELVIEW);
    return arg0;
}
