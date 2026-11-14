/* Stadium Zero fragment012_17ED00. */
/* C ported from the Stadium 1 decomp: src/fragments/battle_engine/battle_engine_356730.c. */

#include "battle.h"
#include "battle_hud.h"
#include "gfx_buffer.h"
extern DoubleTextureTrail D_821CD0E0[4];
extern Gfx D_821934E0[];
#define TRIANGLES(gfx)                                                                                        \
    {                                                                                                         \
        s32 j, k;                                                                                             \
        for (j = 0; j < 2; j++)                                                                               \
            for (k = 0; k < 4; k++)                                                                           \
                gSP2Triangles(gfx++, (j * 4) + k, (j * 4) + (k + 9), (j * 4) + (k + 1), 0, (j * 4) + (k + 9), \
                              (j * 4) + (k + 10), (j * 4) + (k + 1), 0);                                      \
    }

void DoubleTextureTrail_InitPool(void);
void DoubleTextureTrail_RotateVertexOffset(f32 arg0, Vec3f* arg1, f32 arg2);
void DoubleTextureTrail_Update(DoubleTextureTrail* arg0);
s32 DoubleTextureTrail_UpdateAll(void);
Gfx* DoubleTextureTrail_LoadTextures(Gfx* arg0, DoubleTextureTrail* arg1);
Gfx* DoubleTextureTrail_DrawAll(Gfx* arg0);

Gfx* WaterParticle_DrawPass(Gfx* arg0, DoubleTextureTrail* arg1, s16 arg2, s16 arg3);

/**
 * Clears the 4 double-texture trails and their segments.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (3 of the moves).
 * @unverified Name from Stadium 1.
 */
void DoubleTextureTrail_InitPool(void) {
    s32 i;
    s32 j;
    DoubleTextureTrail* var_v0 = &D_821CD0E0[0];
    DoubleTextureTrailSegment* var_a0;

    for (i = 0; i < 4; i++, var_v0++) {
        var_v0->active = 0;
        var_v0->frame = 0;
        var_v0->growFrames = 0;

        var_a0 = &var_v0->segments[0];
        for (j = 0; j < 10; j++, var_a0++) {
            var_a0->index = 0;
            var_a0->alpha = 0;
            var_a0->radius = 1.0f;
            var_a0->angle = 0.0f;
            var_a0->position.x = 0.0f;
            var_a0->position.y = 0.0f;
            var_a0->position.z = 0.0f;
            var_a0->velocity.x = 0.0f;
            var_a0->velocity.y = 0.0f;
            var_a0->velocity.z = 0.0f;
        }
    }
}

/**
 * Starts a free double-texture trail with the given positions, motion, segment counts,
 * two scrolling textures and colors.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (3 of the moves).
 * @unverified Name from Stadium 1.
 */
void DoubleTextureTrail_Spawn(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9,
                   f32 argA, s16 argB, s32 argC, s32 argD, s16 argE, s16 argF, s16 arg10, s16 arg11, s16 arg12,
                   s16 arg13, s16 arg14, s16 arg15, CombinerCycleArgs* arg16, CombinerCycleArgs* arg17, u8 arg18,
                   u8 arg19, u8 arg1A, u8 arg1B, u8 arg1C, u8 arg1D, u8 arg1E, u8 arg1F, u8 arg20, u8 arg21, u8 arg22,
                   u8 arg23, u8 arg24) {
    DoubleTextureTrail* var_v0;
    DoubleTextureTrailSegment* var_a0;
    s32 i;
    s32 j;
    Vec3f sp3C;
    Vec3f sp30;

    sp3C.x = arg0;
    sp3C.y = arg1;
    sp3C.z = arg2;

    sp30.x = arg3;
    sp30.y = arg4;
    sp30.z = arg5;

    var_v0 = &D_821CD0E0[0];
    for (i = 0; i < 4; i++, var_v0++) {
        if (var_v0->active == 0) {
            var_v0->active = 1;
            var_v0->frame = 0;
            var_v0->growFrames = argB;
            var_v0->maxRadius = argA;
            var_v0->radiusStep = arg7;
            var_v0->speed = arg8;
            var_v0->angleStep = arg6;
            var_v0->textureA = argC;
            var_v0->textureB = argD;

            var_v0->scrollA.s = 0;
            var_v0->scrollA.t = 0;
            var_v0->scrollB.s = 0;
            var_v0->scrollB.t = 0;

            var_v0->scrollA.sStep = argE;
            var_v0->scrollA.tStep = argF;
            var_v0->scrollB.sStep = arg12;
            var_v0->scrollB.tStep = arg13;

            var_v0->scrollA.shiftS = arg10;
            var_v0->scrollA.shiftT = arg11;
            var_v0->scrollB.shiftS = arg14;
            var_v0->scrollB.shiftT = arg15;

            var_v0->combineCycle0 = *arg16;
            var_v0->combineCycle1 = *arg17;

            var_v0->primColor.color.r = arg18;
            var_v0->primColor.color.g = arg19;
            var_v0->primColor.color.b = arg1A;
            var_v0->primColor.color.a = arg1B;

            var_v0->primColor.lodFrac = arg1C;

            var_v0->envColor.color.r = arg1D;
            var_v0->envColor.color.g = arg1E;
            var_v0->envColor.color.b = arg1F;
            var_v0->envColor.color.a = arg20;

            var_v0->lineColor.r = arg21;
            var_v0->lineColor.g = arg22;
            var_v0->lineColor.b = arg23;
            var_v0->lineColor.a = arg24;

            var_v0->primAlphaScale = 1.0f;
            var_v0->envAlphaScale = 1.0f;
            var_v0->fadeStartFrame = 0x46;

            var_a0 = &var_v0->segments[0];
            for (j = 0; j < 10; j++, var_a0++) {
                var_a0->index = j;
                var_a0->alpha = 0xFF;
                var_a0->radius = arg9;
                var_a0->angle = 0.0f;
                var_a0->position = sp3C;
                var_a0->velocity.x = sp30.x * arg8;
                var_a0->velocity.y = sp30.y * arg8;
                var_a0->velocity.z = sp30.z * arg8;
            }
            break;
        }
    }
}

/**
 * Writes the point arg2 units along Z rotated by arg0 radians about X to arg1.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (3 of the moves).
 * @unverified Name from Stadium 1.
 */
void DoubleTextureTrail_RotateVertexOffset(f32 arg0, Vec3f* arg1, f32 arg2) {
    UNUSED MtxF sp70;
    MtxF sp30;
    UNUSED s32 pad; // FAKE: stack padding

    guRotateF(sp30.mf, (360.0f * arg0) / 6.2831855f, 1.0f, 0.0f, 0.0f);
    guMtxXFMF(sp30.mf, 0.0f, 0.0f, arg2, &arg1->x, &arg1->y, &arg1->z);
}

/**
 * Advances one trail: moves its head and updates each segment's position and fade.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (3 of the moves).
 * @unverified Name from Stadium 1.
 */
void DoubleTextureTrail_Update(DoubleTextureTrail* arg0) {
    DoubleTextureTrailSegment* var_v0;
    UNUSED s32 pad; // FAKE: stack padding
    s32 i;
    Vec3f sp58;
    Vec3f sp4C;
    f32 temp_fa0;
    f32 temp_fa1;
    f32 var_fv0;
    f32 var_fv1;

    BattleAnim_GetSecondaryOwnerAnchorPosition(&sp58);
    BattleAnim_GetTertiaryOwnerBone9Position(&sp4C);
    if (sp4C.y > 200.0f) {
        sp4C.y = 200.0f;
    }

    var_v0 = &arg0->segments[0];
    for (i = 0; i < 10; i++, var_v0++) {
        if (arg0->frame < arg0->growFrames) {
            temp_fa1 = ((f32)arg0->frame * i) / 9.0f;
            var_fv0 = arg0->growFrames - 1;
            var_fv1 = temp_fa1 / var_fv0;
            temp_fa0 = 1.0f - var_fv1;
        } else {
            temp_fa1 = i;

            var_fv1 = temp_fa1 / 9.0f;
            temp_fa0 = 1.0f - var_fv1;
        }

        var_v0->position.x = (sp58.x * temp_fa0) + (sp4C.x * var_fv1);
        var_v0->position.y = (sp58.y * temp_fa0) + (sp4C.y * var_fv1);
        var_v0->position.z = (sp58.z * temp_fa0) + (sp4C.z * var_fv1);

        var_v0->angle += arg0->angleStep;

        if (i == 0) {
            var_v0->radius = 1.0f;
        } else if (i == 9) {
            if (arg0->frame < 5) {
                var_v0->radius = 1.0f;
            } else {
                var_v0->radius += 0.5f;
                if (arg0->maxRadius * 1.0f < var_v0->radius) {
                    var_v0->radius = arg0->maxRadius * 1.0f;
                }
            }
        } else if (i == 1) {
            var_v0->radius += arg0->radiusStep;
            if (arg0->maxRadius * 0.5f < var_v0->radius) {
                var_v0->radius = arg0->maxRadius * 0.5f;
            }
        } else if (i == 2) {
            var_v0->radius += arg0->radiusStep;
            if (arg0->maxRadius * 0.75f < var_v0->radius) {
                var_v0->radius = arg0->maxRadius * 0.75f;
            }
        } else {
            var_v0->radius += arg0->radiusStep;
            if (arg0->maxRadius * 1.0f < var_v0->radius) {
                var_v0->radius = arg0->maxRadius * 1.0f;
            }
        }
    }
}

/**
 * Advances every active trail and counts its frames. Returns 0.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (3 of the moves).
 * @unverified Name from Stadium 1.
 */
s32 DoubleTextureTrail_UpdateAll(void) {
    s32 i;
    DoubleTextureTrail* var_s0 = &D_821CD0E0[0];

    for (i = 0; i < 4; i++, var_s0++) {
        if (var_s0->active == 1) {
            var_s0->frame += 1;
            DoubleTextureTrail_Update(var_s0);
        }
    }

    return 0;
}

/**
 * Seen in play (2026-11-13) (unattended Free Battle in which every Pokémon knows only Metronome, 70
 * turns): ran.
 * @unverified Name was previously used only by callers of this address; the definition was still func_.
 */
Gfx* WaterParticle_DrawPass(Gfx* arg0, DoubleTextureTrail* arg1, s16 arg2, s16 arg3) {
    s32 i;
    s32 j;
    Vtx* sp44;
    UNUSED s32 k;
    PrimLodColor* temp_v0;
    PrimLodColor* temp_v1;
    u8 a1;
    u8 a2;
    s16 tmp;

    temp_v1 = &arg1->primColor;
    temp_v0 = &arg1->envColor;

    if (arg3 == 0) {
        if (arg1->fadeStartFrame < arg1->frame) {
            tmp = arg1->frame - arg1->fadeStartFrame;

            arg1->primAlphaScale = 1.0f - tmp * 0.1f;
            arg1->envAlphaScale = 1.0f - tmp * 0.1f;

            if (tmp * 0.1f > 1.0f) {
                arg1->primAlphaScale = 0.0f;
            }

            if (arg1->envAlphaScale < 0.0f) {
                arg1->envAlphaScale = 0.0f;
            }
        }
    }

    a1 = temp_v1->color.a * arg1->primAlphaScale;
    a2 = temp_v0->color.a * arg1->envAlphaScale;

    gDPSetPrimColor(arg0++, 0, temp_v1->lodFrac, temp_v1->color.r, temp_v1->color.g, temp_v1->color.b, a1);
    gDPSetEnvColor(arg0++, temp_v0->color.r, temp_v0->color.g, temp_v0->color.b, a2);

    sp44 = arg1->vtx;
    for (i = 0; i < 9; i++) {
        gSPVertex(arg0++, sp44, 18, 0);
        for (j = 0; j < 8; j++) {
            gSP2Triangles(arg0++, j, j + 9, j + 1, 0, j + 9, j + 10, j + 1, 0);
        }
        sp44 += 9;
    }

    return arg0;
}

/**
 * Adds the loads for a trail's two scrolling 32x32 I4 textures to the display list.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (3 of the moves).
 * @unverified Name from Stadium 1.
 */
Gfx* DoubleTextureTrail_LoadTextures(Gfx* arg0, DoubleTextureTrail* arg1) {
    TextureScroll* ptr;

    ptr = &arg1->scrollA;
    gDPLoadTextureTile_4b(arg0++, sBattleAnimAssetPointers[arg1->textureA], G_IM_FMT_I, 32, 0, 0, 0, 31, 31, 0,
                          G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, 5, 5, ptr->shiftS, ptr->shiftT);
    gDPSetTileSize(arg0++, G_TX_RENDERTILE, ptr->s, ptr->t, (ptr->s + 31) << 2, (ptr->t + 31) << 2);

    ptr = &arg1->scrollB;
    gDPLoadMultiTile_4b(arg0++, sBattleAnimAssetPointers[arg1->textureB], 0x0100, 1, G_IM_FMT_I, 32, 0, 0, 0, 31, 31, 0,
                        G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, 5, 5, ptr->shiftS, ptr->shiftT);
    gDPSetTileSize(arg0++, 1, ptr->s, ptr->t, (ptr->s + 31) << 2, (ptr->t + 31) << 2);

    return arg0;
}

/**
 * Adds the display lists that draw every active trail as textured strips and returns the
 * new end of the list.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (3 of the moves).
 * @unverified Name from Stadium 1.
 */
Gfx* DoubleTextureTrail_DrawAll(Gfx* arg0) {
    s32 i;
    s32 j;
    s32 k;
    DoubleTextureTrail* var_fp;
    DoubleTextureTrailSegment* var_s2;
    Vec3f sp100;
    Vec3f spF4;
    Vec3f spE8;
    Vec3f spDC;
    CameraNode* spD8;
    UNUSED s32 pad[3]; // FAKE: stack padding
    Vtx* var_s0;

    spD8 = BattleAnim_GetCameraContext();
    var_fp = &D_821CD0E0[0];

    for (i = 0; i < 4; i++, var_fp++) {
        if (var_fp->active == 1) {
            if (ModelPhase_IsIdle() == 0) {
                var_fp->scrollA.s += var_fp->scrollA.sStep;
                var_fp->scrollA.t += var_fp->scrollA.tStep;
                var_fp->scrollB.s += var_fp->scrollB.sStep;
                var_fp->scrollB.t += var_fp->scrollB.tStep;
            }

            var_s2 = &var_fp->segments[0];

            var_fp->vtx = Gfx_AllocDisplayList(sizeof(Vtx) * 90);

            var_s0 = var_fp->vtx;
            for (j = 0; j < 10; j++, var_s2++) {
                for (k = 0; k < 9; k++) {
                    DoubleTextureTrail_RotateVertexOffset(var_s2->angle + ((2.0f * (k % 8) * 3.1415927f) / 8), &sp100, var_s2->radius);
                    var_s0->v.ob[0] = var_s2->position.x + sp100.x;
                    var_s0->v.ob[1] = var_s2->position.y + sp100.y;
                    var_s0->v.ob[2] = var_s2->position.z + sp100.z;

                    var_s0->v.tc[0] = (k * 0x400) / 8;
                    var_s0->v.tc[1] = (j * 0x400) / 10;

                    var_s0->v.cn[0] = 0;
                    var_s0->v.cn[1] = 0;
                    var_s0->v.cn[2] = 0;
                    var_s0->v.cn[3] = 0;

                    var_s0++;
                }
            }

            if ((var_fp->lineColor.r | var_fp->lineColor.g | var_fp->lineColor.b | var_fp->lineColor.a) != 0) {
                spE8 = var_fp->segments[9].position;
                spF4 = var_fp->segments[0].position;
                spDC.x = spD8->view.eyePosition.x;
                spDC.y = spD8->view.eyePosition.y;
                spDC.z = spD8->view.eyePosition.z;
                arg0 = Gfx_DrawThickLine(arg0, &spF4, &spE8, &spDC, 20.0f, var_fp->lineColor.r, var_fp->lineColor.g,
                                     var_fp->lineColor.b, var_fp->lineColor.a * var_fp->primAlphaScale);
            }

            gSPDisplayList(arg0++, D_821934E0);

            Gfx_SetCombineMode(
                arg0++, var_fp->combineCycle0.colorA, var_fp->combineCycle0.colorB, var_fp->combineCycle0.colorC, var_fp->combineCycle0.colorD,
                var_fp->combineCycle0.alphaA, var_fp->combineCycle0.alphaB, var_fp->combineCycle0.alphaC, var_fp->combineCycle0.alphaD,
                var_fp->combineCycle1.colorA, var_fp->combineCycle1.colorB, var_fp->combineCycle1.colorC, var_fp->combineCycle1.colorD,
                var_fp->combineCycle1.alphaA, var_fp->combineCycle1.alphaB, var_fp->combineCycle1.alphaC, var_fp->combineCycle1.alphaD);

            arg0 = DoubleTextureTrail_LoadTextures(arg0, var_fp);

            gDPSetPrimColor(arg0++, 0, var_fp->primColor.lodFrac, var_fp->primColor.color.r, var_fp->primColor.color.g,
                            var_fp->primColor.color.b, var_fp->primColor.color.a);
            gDPSetEnvColor(arg0++, var_fp->envColor.color.r, var_fp->envColor.color.g, var_fp->envColor.color.b,
                           var_fp->envColor.color.a);
            gSPClearGeometryMode(arg0++, G_CULL_BOTH);
            gSPSetGeometryMode(arg0++, G_CULL_FRONT);
            gDPPipeSync(arg0++);

            arg0 = WaterParticle_DrawPass(arg0, var_fp, i, 0);

            gSPClearGeometryMode(arg0++, G_CULL_BOTH);
            gSPSetGeometryMode(arg0++, G_CULL_BACK);
            gDPPipeSync(arg0++);

            arg0 = WaterParticle_DrawPass(arg0, var_fp, i, 1);
        }
    }

    return arg0;
}
