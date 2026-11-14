/* Stadium Zero fragment012_17ED00. */
/* C ported from the Stadium 1 decomp: src/fragments/battle_engine/battle_engine_355A00.c. */

#include "battle.h"
#include "gfx_buffer.h"
extern Trail50Effect D_821C2820[50];
extern Gfx D_821933D0[];
extern Gfx D_82193460[];

void RazorLeafTrail_Init(void);
/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Razor Leaf.
 */
void RazorLeafTrail_Start(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, u8 arg6, u8 arg7, u8 arg8, u8 arg9,
                   f32 argA, f32 argB, f32 argC, s16 argD);
void RazorLeafTrail_Update(f32 arg0, Vec3f* arg1, f32 arg2);
void RazorLeafTrail_AdvanceNodes(Trail50Effect* arg0);
s32 RazorLeafTrail_IsComplete(void);
Gfx* RazorLeafTrail_Draw(Gfx* arg0);

/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Razor Leaf.
 */
void RazorLeafTrail_Init(void) {
    Trail50Effect* var_v0 = &D_821C2820[0];
    Trail50EffectNode* var_a0;
    s32 i;
    s32 j;

    for (i = 0; i < 50; i++, var_v0++) {
        var_v0->active = 0;
        var_v0->frame = 0;
        var_v0->duration = 0;

        var_a0 = &var_v0->nodes[0];

        for (j = 0; j < 10; j++, var_a0++) {
            var_a0->alpha = 0;
            var_a0->halfWidth = 1.0f;
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
 * Starts a leaf trail in the first free of 50 slots: from 80 times half the secondary owner's
 * model scale above (arg0, arg1, arg2) toward (arg3, arg4, arg5), colored (arg6, arg7, arg8),
 * falling slowly, with lifetime argD. Same setup as PetalDanceTrail_Start with its own pool.
 * @unverified Name from Stadium 1.
 */
void RazorLeafTrail_Start(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, u8 arg6, u8 arg7, u8 arg8, u8 arg9,
                   f32 argA, f32 argB, f32 argC, s16 argD) {
    Trail50Effect* var_v1;
    Trail50EffectNode* var_s0;
    s32 i;
    s32 j;
    Vec3f sp7C;
    Vec3f sp70;
    Vec3f sp64;
    f32 temp_fv1;

    temp_fv1 = BattleAnim_GetSecondaryOwnerModelScale() * 0.5f;

    sp7C.x = arg0;
    sp7C.y = (80.0f * temp_fv1) + arg1;
    sp7C.z = arg2;

    sp70.x = arg3;
    sp70.y = arg4;
    sp70.z = arg5;

    sp64.x = 0.0f;
    sp64.y = temp_fv1 * -2.0;
    sp64.z = 0.0f;

    var_v1 = &D_821C2820[0];

    for (i = 0; i < 50; i++, var_v1++) {
        if (var_v1->active == 0) {
            var_v1->active = 1;
            var_v1->phase = 0;
            var_v1->frame = 0;
            var_v1->duration = argD;
            var_v1->color.r = arg6;
            var_v1->color.g = arg7;
            var_v1->color.b = arg8;
            var_v1->startPos = sp7C;
            var_v1->maxHalfWidth = argC;
            var_v1->angleStep = argA;
            var_v1->scale = temp_fv1;

            if (arg0 > 0.0) {
                var_v1->direction = -1;
            } else {
                var_v1->direction = 1;
            }

            var_s0 = var_v1->nodes;
            for (j = 0; j < 10; j++, var_s0++) {
                var_s0->alpha = (arg9 * (9 - j)) / 10;
                var_s0->halfWidth = argB;
                var_s0->angle = (RAND(120) * 6.2831855f) / 120.0;
                var_s0->position = sp7C;
                var_s0->velocity = sp70;
                var_s0->swirlVelocity = sp64;
            }
            break;
        }
    }
}

/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Razor Leaf.
 */
void RazorLeafTrail_Update(f32 arg0, Vec3f* arg1, f32 arg2) {
    MtxF sp30;
    f32 temp_fv0 = (arg0 * 360.0) / 6.2831854820251465;

    guRotateRPYF(sp30.mf, 90.0f, temp_fv0, temp_fv0);
    guMtxXFMF(sp30.mf, 0.0f, 0.0f, arg2, &arg1->x, &arg1->y, &arg1->z);
}

/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Razor Leaf.
 */
void RazorLeafTrail_AdvanceNodes(Trail50Effect* arg0) {
    s32 i;
    f32 temp_fs3 = arg0->scale;
    Trail50EffectNode* var_s0 = &arg0->nodes[0];

    for (i = 0; i < 10; i++, var_s0++) {
        if (i == 0) {
            var_s0->prevHalfWidth = var_s0->halfWidth;
            var_s0->prevAngle = var_s0->angle;
            var_s0->prevPosition = var_s0->position;
            var_s0->prevVelocity = var_s0->velocity;

            switch (arg0->phase) {
                case 0:
                    var_s0->position.x += var_s0->swirlVelocity.x;
                    var_s0->position.y += var_s0->swirlVelocity.y;
                    var_s0->position.z += var_s0->swirlVelocity.z;
                    var_s0->angle += arg0->angleStep;
                    var_s0->swirlVelocity.x += __sinf(var_s0->angle) * temp_fs3;
                    var_s0->swirlVelocity.z += __cosf(var_s0->angle) * temp_fs3;
                    if (arg0->frame >= 0x15) {
                        arg0->phase = 1;
                        arg0->frame = 0;
                    }
                    break;

                case 1:
                    var_s0->position.x += var_s0->velocity.x;
                    var_s0->position.y += var_s0->velocity.y;
                    var_s0->position.z += var_s0->velocity.z;
                    var_s0->angle += arg0->angleStep;
                    if (arg0->direction > 0) {
                        var_s0->velocity.x += 2.0;
                        if (var_s0->velocity.x > 20.0) {
                            var_s0->velocity.x = 20.0f;
                        }
                    } else {
                        var_s0->velocity.x -= 2.0;
                        if (var_s0->velocity.x < -20.0) {
                            var_s0->velocity.x = -20.0f;
                        }
                    }
                    break;
            }

            var_s0->halfWidth += 2.0;
            if (arg0->maxHalfWidth < var_s0->halfWidth) {
                var_s0->halfWidth = arg0->maxHalfWidth;
            }
        } else {
            var_s0->prevHalfWidth = var_s0->halfWidth;
            var_s0->prevAngle = var_s0->angle;

            var_s0->prevPosition = var_s0->position;
            var_s0->prevVelocity = var_s0->velocity;

            var_s0->position = var_s0[-1].prevPosition;
            var_s0->angle = var_s0[-1].prevAngle;
            var_s0->velocity = var_s0[-1].prevVelocity;
            var_s0->halfWidth = var_s0[-1].prevHalfWidth;
        }
    }
}

/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Razor Leaf.
 */
s32 RazorLeafTrail_IsComplete(void) {
    s32 i;
    Trail50Effect* var_s0 = &D_821C2820[0];

    for (i = 0; i < 50; i++, var_s0++) {
        if (var_s0->active == 1) {
            var_s0->frame++;
            if ((var_s0->phase == 1) && (var_s0->duration < var_s0->frame)) {
                var_s0->active = 0;
            } else {
                RazorLeafTrail_AdvanceNodes(var_s0);
            }
        }
    }
    return 0;
}

/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Razor Leaf.
 */
Gfx* RazorLeafTrail_Draw(Gfx* arg0) {
    s32 i;
    s32 j;
    s32 k;
    Trail50EffectNode* temp_s0;
    Trail50Effect* var_s5;
    Vtx* var_s0;
    Vec3f sp184;
    UNUSED s32 pad[15]; // FAKE: stack padding
    Mtx* temp_v0;
    Mtx sp100;
    Mtx spC0;
    f32 temp_fs1;
    s16 var_s3;
    f32 tmp;

    gDPLoadTextureBlock(arg0++, sBattleAnimAssetPointers[0x1C], G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0, G_TX_NOMIRROR | G_TX_WRAP,
                        G_TX_NOMIRROR | G_TX_WRAP, 5, 5, G_TX_NOLOD, G_TX_NOLOD);

    var_s5 = &D_821C2820[0];
    for (i = 0; i < 50; i++, var_s5++) {
        if (var_s5->active == 1) {
            temp_s0 = &var_s5->nodes[0];
            tmp = var_s5->scale;
            if (temp_s0->position.y > 0.0f) {
                temp_fs1 = (temp_s0->angle * 360.0f) / 6.2831854820251465;
                temp_v0 = Gfx_AllocDisplayList(sizeof(Mtx) * 1);
                guTranslate(temp_v0, temp_s0->position.x, temp_s0->position.y, temp_s0->position.z);
                guRotateRPY(&sp100, 90.0f, temp_fs1, temp_fs1);
                guMtxCatL(&sp100, temp_v0, temp_v0);
                guScale(&spC0, tmp, tmp, tmp);
                guMtxCatL(&spC0, temp_v0, temp_v0);

                gSPMatrix(arg0++, temp_v0, G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW);
                gSPDisplayList(arg0++, D_82193460);
                gSPPopMatrix(arg0++, G_MTX_MODELVIEW);
            }

            var_s5->vtx = Gfx_AllocDisplayList(0x140);

            var_s0 = var_s5->vtx;
            for (j = 0; j < 10; j++) {
                RazorLeafTrail_Update(temp_s0->angle, &sp184, temp_s0->halfWidth * tmp);

                var_s3 = temp_s0->position.y + sp184.y;
                if (var_s3 < 0) {
                    var_s3 = 0;
                }

                var_s0->v.ob[0] = temp_s0->position.x + sp184.x;
                var_s0->v.ob[1] = var_s3;
                var_s0->v.ob[2] = temp_s0->position.z + sp184.z;
                var_s0->v.cn[0] = var_s5->color.r;
                var_s0->v.cn[1] = var_s5->color.g;
                var_s0->v.cn[2] = var_s5->color.b;
                var_s0->v.cn[3] = temp_s0->alpha;
                var_s0++;

                RazorLeafTrail_Update(temp_s0->angle + 3.1415927f, &sp184, temp_s0->halfWidth * tmp);

                var_s3 = temp_s0->position.y + sp184.y;
                if (var_s3 < 0) {
                    var_s3 = 0;
                }

                var_s0->v.ob[0] = temp_s0->position.x + sp184.x;
                var_s0->v.ob[1] = var_s3;
                var_s0->v.ob[2] = temp_s0->position.z + sp184.z;
                var_s0->v.cn[0] = var_s5->color.r;
                var_s0->v.cn[1] = var_s5->color.g;
                var_s0->v.cn[2] = var_s5->color.b;
                var_s0->v.cn[3] = temp_s0->alpha;
                var_s0++;

                temp_s0++;
            }

            var_s0 = var_s5->vtx;

            gSPDisplayList(arg0++, D_821933D0);

            for (k = 0; k < 9; k++) {
                gSPVertex(arg0++, var_s0, 4, 0);
                gSP2Triangles(arg0++, 0, 2, 1, 0, 2, 3, 1, 0);
                var_s0 += 2;
            }
        }
    }

    return arg0;
}
