/* Stadium Zero fragment012_17ED00. */
/* C ported from the Stadium 1 decomp: src/fragments/battle_engine/battle_engine_34E1A0.c. */

#include "battle.h"
#include "gfx_buffer.h"
#include "vector_math.h"
#include "math.h"
extern Trail40 sWaterSurface;
extern Gfx D_82192B98[];

void HypnosisScreechTrail_Init(s16 arg0);
void HypnosisScreechTrail_Start(s32 arg0, s32 arg1);
void HypnosisScreechTrailNode_FillVertex(Trail40Node* arg0, Vtx* arg1);
s32 HypnosisScreechTrail_IsComplete(void);
Gfx* HypnosisScreechTrail_Draw(Gfx* arg0);

void Trail40_Reset(void);

/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Hypnosis, Screech.
 */
void HypnosisScreechTrail_Init(s16 arg0) {
    s32 i;
    s32 j;
    s16 tmp1;
    s16 tmp2;
    s16 tmp3;
    Trail40Node* var_v0 = &sWaterSurface.grid[0][0];

    sWaterSurface.frame = 0;
    sWaterSurface.duration = arg0;
    sWaterSurface.alpha = 0;
    sWaterSurface.waveAmplitude = 0.01f;

    for (i = 0; i < 16; i++) {
        for (j = 0; j < 16; j++) {
            tmp1 = i * 0x20;
            tmp3 = tmp1 * 0x10;
            tmp2 = j * 0x20;

            var_v0->position.x = (i * 9.0f) - 72.0f;
            var_v0->position.y = 1.0f;
            var_v0->position.z = (j * 7.0f) - 56.0f;

            var_v0->texS = tmp1 * 0x10;
            var_v0->texT = tmp2 * 0x10;

            var_v0++;
        }
    }
}

/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Hypnosis, Screech.
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

    sp6C = sWaterSurface.grid[arg0][arg1].position.x;
    sp68 = sWaterSurface.grid[arg0][arg1].position.y;
    sp64 = sWaterSurface.grid[arg0][arg1].position.z;
    sp84 = 0.0f;
    sp80 = 0.0f;
    sp7C = 0.0f;
    sp46 = 0;

    if ((arg0 > 0) && (arg1 >= 1)) {
        sp60 = sWaterSurface.grid[arg0 - 1][arg1].position.x - sp6C;
        sp5C = sWaterSurface.grid[arg0 - 1][arg1].position.y - sp68;
        sp58 = sWaterSurface.grid[arg0 - 1][arg1].position.z - sp64;
        Vec3f_NormalizeComponents(&sp60, &sp5C, &sp58);
        sp54 = sWaterSurface.grid[arg0][arg1 - 1].position.x - sp6C;
        sp50 = sWaterSurface.grid[arg0][arg1 - 1].position.y - sp68;
        sp4C = sWaterSurface.grid[arg0][arg1 - 1].position.z - sp64;
        Vec3f_NormalizeComponents(&sp54, &sp50, &sp4C);
        Vec3f_CrossProductComponents(sp60, sp5C, sp58, sp54, sp50, sp4C, &sp78, &sp74, &sp70);
        Vec3f_NormalizeComponents(&sp78, &sp74, &sp70);
        sp84 += sp78;
        sp80 += sp74;
        sp7C += sp70;
        sp46 = 1;
    }

    if ((0 < arg0) && (arg1 < 15)) {
        sp60 = sWaterSurface.grid[arg0 - 1][arg1].position.x - sp6C;
        sp5C = sWaterSurface.grid[arg0 - 1][arg1].position.y - sp68;
        sp58 = sWaterSurface.grid[arg0 - 1][arg1].position.z - sp64;
        Vec3f_NormalizeComponents(&sp60, &sp5C, &sp58);
        sp54 = sWaterSurface.grid[arg0][arg1 + 1].position.x - sp6C;
        sp50 = sWaterSurface.grid[arg0][arg1 + 1].position.y - sp68;
        sp4C = sWaterSurface.grid[arg0][arg1 + 1].position.z - sp64;
        Vec3f_NormalizeComponents(&sp54, &sp50, &sp4C);
        Vec3f_CrossProductComponents(sp60, sp5C, sp58, sp54, sp50, sp4C, &sp78, &sp74, &sp70);
        Vec3f_NormalizeComponents(&sp78, &sp74, &sp70);
        sp84 += sp78;
        sp80 += sp74;
        sp7C += sp70;
        sp46 += 1;
    }

    if ((arg0 < 15) && (arg1 >= 1)) {
        sp60 = sWaterSurface.grid[arg0 + 1][arg1].position.x - sp6C;
        sp5C = sWaterSurface.grid[arg0 + 1][arg1].position.y - sp68;
        sp58 = sWaterSurface.grid[arg0 + 1][arg1].position.z - sp64;
        Vec3f_NormalizeComponents(&sp60, &sp5C, &sp58);
        sp54 = sWaterSurface.grid[arg0][arg1 - 1].position.x - sp6C;
        sp50 = sWaterSurface.grid[arg0][arg1 - 1].position.y - sp68;
        sp4C = sWaterSurface.grid[arg0][arg1 - 1].position.z - sp64;
        Vec3f_NormalizeComponents(&sp54, &sp50, &sp4C);
        Vec3f_CrossProductComponents(sp60, sp5C, sp58, sp54, sp50, sp4C, &sp78, &sp74, &sp70);
        Vec3f_NormalizeComponents(&sp78, &sp74, &sp70);
        sp84 += sp78;
        sp80 += sp74;
        sp7C += sp70;
        sp46 += 1;
    }

    if ((arg0 < 15) && (arg1 < 15)) {
        sp60 = sWaterSurface.grid[arg0 + 1][arg1].position.x - sp6C;
        sp5C = sWaterSurface.grid[arg0 + 1][arg1].position.y - sp68;
        sp58 = sWaterSurface.grid[arg0 + 1][arg1].position.z - sp64;
        Vec3f_NormalizeComponents(&sp60, &sp5C, &sp58);
        sp54 = sWaterSurface.grid[arg0][arg1 + 1].position.x - sp6C;
        sp50 = sWaterSurface.grid[arg0][arg1 + 1].position.y - sp68;
        sp4C = sWaterSurface.grid[arg0][arg1 + 1].position.z - sp64;
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
        sWaterSurface.grid[arg0][arg1].normal.x = sp84;
        sWaterSurface.grid[arg0][arg1].normal.y = sp80;
        sWaterSurface.grid[arg0][arg1].normal.z = sp7C;
    }
}

/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Hypnosis, Screech.
 */
void HypnosisScreechTrailNode_FillVertex(Trail40Node* arg0, Vtx* arg1) {
    f32 r;
    f32 g;
    f32 b;

    arg1->v.ob[0] = arg0->position.x;
    arg1->v.ob[1] = arg0->position.y;
    arg1->v.ob[2] = arg0->position.z;

    arg1->v.tc[0] = arg0->texS;
    arg1->v.tc[1] = arg0->texT;

    r = arg0->normal.x;
    g = arg0->normal.y;
    b = arg0->normal.z;

    arg1->v.cn[0] = (s32)(r * 120.0);
    arg1->v.cn[1] = (s32)(g * 120.0);
    arg1->v.cn[2] = (s32)(b * 120.0);
    arg1->v.cn[3] = sWaterSurface.alpha;
}

/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Hypnosis, Screech.
 */
s32 HypnosisScreechTrail_IsComplete(void) {
    Trail40Node* var_s1;
    s32 i;
    s32 j;
    f32 temp_fv1_2;
    f32 tmp;

    sWaterSurface.frame = sWaterSurface.frame + 1;
    if (sWaterSurface.duration < sWaterSurface.frame) {
        return -1;
    }
    if (sWaterSurface.frame < 0x1E) {
        sWaterSurface.alpha += 0xA;
        if (sWaterSurface.alpha >= 0x81) {
            sWaterSurface.alpha = 0x80;
        }
    } else if ((sWaterSurface.duration - 0x1E) < sWaterSurface.frame) {
        sWaterSurface.alpha -= 0xA;
        if (sWaterSurface.alpha < 0) {
            sWaterSurface.alpha = 0;
        }
    }

    if (sWaterSurface.waveAmplitude < 1.0) {
        sWaterSurface.waveAmplitude += 0.05;
    }

    var_s1 = &sWaterSurface.grid[0][0];
    for (i = 0; i < 16; i++) {
        for (j = 0; j < 16; j++) {
            temp_fv1_2 = 1.0 - (sqrtf(SQ(var_s1->position.x) + SQ(var_s1->position.z)) / 101.8224f);
            tmp = __sinf((((f32)(sWaterSurface.frame % 20) / 20.0) + (3.0 * temp_fv1_2)) * 6.2831854820251465) *
                  ((f64)sWaterSurface.waveAmplitude * temp_fv1_2);
            var_s1->position.y = tmp;
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
s32 BattleAnim_GetCameraContext(void);
void func_80031F14(f32*, f32*, f32*);
void func_800320A8(s32, f32, f32, f32, f32, f32, f32);
extern s32 D_821A6F60;
/**
 * Seen in play (2026-11-13) (unattended Free Battle in which every Pokémon knows only Metronome, 40
 * turns): ran.
 * @unverified Name was previously used only by callers of this address; the definition was still func_.
 */
void Trail40_Reset(void) {
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
    temp_v0 = BattleAnim_GetCameraContext();

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
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Hypnosis, Screech.
 */
Gfx* HypnosisScreechTrail_Draw(Gfx* arg0) {
    s32 i;
    s32 j;
    Trail40Node* var_s2;
    s32 var_s4;
    Vtx* vtx;
    s32 idx;

    var_s4 = 0;
    sWaterSurface.vtx = Gfx_AllocDisplayList(sizeof(Vtx) * 16 * 16);

    vtx = sWaterSurface.vtx;
    var_s2 = &sWaterSurface.grid[0][0];
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
    gDPSetPrimColor(arg0++, 0, 0, 255, 255, 255, sWaterSurface.alpha);
    gSPMatrix(arg0++, sWaterSurface.mtx, G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW);

    vtx = sWaterSurface.vtx;
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
