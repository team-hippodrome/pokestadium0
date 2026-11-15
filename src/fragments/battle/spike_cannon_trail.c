/* Stadium Zero fragment012_17ED00. */
/* C ported from the Stadium 1 decomp: src/fragments/battle_engine/battle_engine_353370.c. */

#include "battle.h"
#include "gfx_buffer.h"
#include "matrix.h"
extern OwnerLinkedFourStream D_821B5E30[4];
extern Gfx D_82193220[];

void SpikeCannonFourStream_Init(void);
/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Spike Cannon.
 */
void SpikeCannonFourStream_Start(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, u8 arg6, u8 arg7, u8 arg8, u8 arg9,
                   f32 argA, f32 argB, f32 argC, s16 argD);
void SpikeCannonFourStream_Update(f32 arg0, Vec3f* arg1, f32 arg2);
void SpikeCannonFourStream_UpdateNodeChain(OwnerLinkedFourStream* arg0);
s32 SpikeCannonFourStream_IsComplete(void);
Gfx* SpikeCannonFourStream_Draw(Gfx* arg0);

/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Spike Cannon.
 */
void SpikeCannonFourStream_Init(void) {
    s32 i;
    s32 j;
    OwnerLinkedFourStream* var_a2 = &D_821B5E30[0];
    FourStreamTrailNode* var_v0;

    for (i = 0; i < 4; i++, var_a2++) {
        var_a2->active = 0;
        var_a2->frame = 0;
        var_a2->duration = 0;

        var_v0 = &var_a2->nodes[0];
        for (j = 0; j < 15; j++, var_v0++) {
            var_v0->alpha = 0;
            var_v0->halfWidth = 1.0f;
            var_v0->angle = 0.0f;
            var_v0->position.z = var_v0->position.y = var_v0->position.x = 0.0f;
            var_v0->velocity.z = var_v0->velocity.y = var_v0->velocity.x = 0.0f;
        }
    }
}

/**
 * Starts a four-stream spike trail in the first free of 4 slots: from (arg0, arg1, arg2)
 * toward (arg3, arg4, arg5), colored (arg6, arg7, arg8), with a particle on the secondary
 * owner and 15 trail nodes whose alpha fades from arg9. The direction sign comes from arg3.
 * @unverified Name from Stadium 1.
 */
void SpikeCannonFourStream_Start(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, u8 arg6, u8 arg7, u8 arg8, u8 arg9,
                   f32 argA, f32 argB, f32 argC, s16 argD) {
    s32 i;
    s32 j;
    OwnerLinkedFourStream* var_v1;
    FourStreamTrailNode* var_s0;
    Vec3f sp64;
    Vec3f sp58;

    sp64.x = arg0;
    sp64.y = arg1;
    sp64.z = arg2;

    sp58.x = arg3;
    sp58.y = arg4;
    sp58.z = arg5;

    var_v1 = &D_821B5E30[0];
    for (i = 0; i < 4; i++, var_v1++) {
        if (var_v1->active == 0) {
            var_v1->active = 1;
            var_v1->frame = 0;
            var_v1->duration = argD;
            var_v1->color.r = arg6;
            var_v1->color.g = arg7;
            var_v1->color.b = arg8;
            var_v1->targetPos = sp64;
            var_v1->maxHalfWidth = argC;
            var_v1->angleStep = argA;
            var_v1->particle = BattleAnim_SpawnSecondaryOwnerParticle(sp64, 2);

            if (arg3 < 0.0) {
                var_v1->direction = -1;
            } else {
                var_v1->direction = 1;
            }

            var_s0 = &var_v1->nodes[0];
            for (j = 0; j < 15; j++, var_s0++) {
                var_s0->alpha = (arg9 * (0xE - j)) / 15;
                var_s0->halfWidth = argB;
                var_s0->angle = (RAND(120) * 6.2831855f) / 120.0;
                var_s0->position = sp64;
                var_s0->velocity = sp58;
            }
            break;
        }
    }
}

/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Spike Cannon.
 */
void SpikeCannonFourStream_Update(f32 arg0, Vec3f* arg1, f32 arg2) {
    UNUSED MtxF sp70;
    MtxF sp30;
    UNUSED s32 pad; // FAKE: stack padding

    guRotateF(sp30.mf, (arg0 * 360.0) / 6.2831854820251465, 1.0f, 0.0f, 0.0f);
    guMtxXFMF(sp30.mf, 0.0f, 0.0f, arg2, &arg1->x, &arg1->y, &arg1->z);
}

/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Spike Cannon.
 */
void SpikeCannonFourStream_UpdateNodeChain(OwnerLinkedFourStream* arg0) {
    FourStreamTrailNode* var_s0 = &arg0->nodes[0];
    s32 i;
    f32 var_ft4;

    for (i = 0; i < 15; i++, var_s0++) {
        if (i == 0) {
            var_s0->prevHalfWidth = var_s0->halfWidth;
            var_s0->prevAngle = var_s0->angle;
            var_s0->prevPosition = var_s0->position;
            var_s0->prevVelocity = var_s0->velocity;

            var_s0->position.x += var_s0->velocity.x;
            var_s0->position.y += var_s0->velocity.y;
            var_s0->position.z += var_s0->velocity.z;

            var_s0->angle += arg0->angleStep;
            if (arg0->direction > 0) {
                var_s0->velocity.x += 0.4;
                if (var_s0->velocity.x > 20.0) {
                    var_s0->velocity.x = 20.0f;
                }
            } else {
                var_s0->velocity.x -= 0.4;
                if (var_s0->velocity.x < -20.0) {
                    var_s0->velocity.x = -20.0f;
                }
            }

            if (arg0->frame < 0xA) {
                f32 tmp1 = (((0xA - arg0->frame) * 0.01) / 10.0);
                f32 tmp2 = ((arg0->frame * 0.07) / 10.0);

                var_s0->velocity.y += (arg0->targetPos.y - var_s0->position.y) * tmp1;
                var_ft4 = (arg0->targetPos.y - var_s0->position.y) * tmp2;
            } else {
                var_s0->velocity.y += ((arg0->targetPos.y - var_s0->position.y) * 0.01);
                var_ft4 = (arg0->targetPos.y - var_s0->position.y) * 0.07;
            }
            var_s0->position.y += var_ft4;
            arg0->heading = (MathUtil_Atan2s(var_s0->velocity.x, var_s0->velocity.y + var_ft4) * 360.0) / 65535.0;

            BattleAnim_SetParticlePosition(arg0->particle, var_s0->position);

            if (arg0->frame == 1) {
                BattleAnim_SpawnSecondaryOwnerParticle(var_s0->position, 1);
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
 * for Spike Cannon.
 */
s32 SpikeCannonFourStream_IsComplete(void) {
    s32 i;
    OwnerLinkedFourStream* var_s0 = &D_821B5E30[0];

    for (i = 0; i < 4; i++, var_s0++) {
        if (var_s0->active == 1) {
            var_s0->frame += 1;
            if (var_s0->duration < var_s0->frame) {
                var_s0->active = 0;
                BattleAnim_MarkParticleInactive(var_s0->particle);
            } else {
                SpikeCannonFourStream_UpdateNodeChain(var_s0);
            }
        }
    }
    return 0;
}

/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Spike Cannon.
 */
Gfx* SpikeCannonFourStream_Draw(Gfx* arg0) {
    s32 i;
    s32 j;
    s32 k;
    OwnerLinkedFourStream* var_s5;
    FourStreamTrailNode* temp_s0;
    Mtx* temp_v0;
    Vec3f sp154;
    UNUSED s32 pad[14]; // FAKE: stack padding
    s16 var_s3;
    Vtx* var_s0;
    Mtx spD0;
    Mtx sp90;
    UNUSED s32 pad2; // FAKE: stack padding

    var_s5 = &D_821B5E30[0];
    for (i = 0; i < 4; i++, var_s5++) {
        if (var_s5->active == 1) {
            temp_s0 = &var_s5->nodes[0];
            if (temp_s0->position.y > 0.0f) {
                temp_v0 = Gfx_AllocDisplayList(sizeof(Mtx) * 1);
                guTranslate(temp_v0, temp_s0->position.x, temp_s0->position.y, temp_s0->position.z);
                guRotateRPY(&spD0, (temp_s0->angle * -360.0f * var_s5->direction) / 6.2831854820251465, 0.0f,
                            var_s5->heading);
                guMtxCatL(&spD0, temp_v0, temp_v0);
                guScale(&sp90, 0.09f, 0.09f, 0.09f);
                guMtxCatL(&sp90, temp_v0, temp_v0);

                gSPMatrix(arg0++, temp_v0, G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW);
                gSPDisplayList(arg0++, D_821941F0);
                gSPPopMatrix(arg0++, G_MTX_MODELVIEW);
            }

            var_s5->vtx = Gfx_AllocDisplayList(sizeof(Vtx) * 30);
            var_s0 = var_s5->vtx;

            for (j = 0; j < 15; j++) {
                SpikeCannonFourStream_Update(temp_s0->angle, &sp154, temp_s0->halfWidth);

                var_s3 = temp_s0->position.y + sp154.y;
                if (var_s3 < 0) {
                    var_s3 = 0;
                }

                var_s0->v.ob[0] = temp_s0->position.x + sp154.x;
                var_s0->v.ob[1] = var_s3;
                var_s0->v.ob[2] = temp_s0->position.z + sp154.z;
                var_s0->v.cn[0] = var_s5->color.r;
                var_s0->v.cn[1] = var_s5->color.g;
                var_s0->v.cn[2] = var_s5->color.b;
                var_s0->v.cn[3] = temp_s0->alpha;
                var_s0++;

                SpikeCannonFourStream_Update(temp_s0->angle + 3.1415927f, &sp154, temp_s0->halfWidth);

                var_s3 = temp_s0->position.y + sp154.y;
                if (var_s3 < 0) {
                    var_s3 = 0;
                }

                var_s0->v.ob[0] = temp_s0->position.x + sp154.x;
                var_s0->v.ob[1] = var_s3;
                var_s0->v.ob[2] = temp_s0->position.z + sp154.z;
                var_s0->v.cn[0] = var_s5->color.r;
                var_s0->v.cn[1] = var_s5->color.g;
                var_s0->v.cn[2] = var_s5->color.b;
                var_s0->v.cn[3] = temp_s0->alpha;
                var_s0++;

                temp_s0++;
            }

            var_s0 = var_s5->vtx;

            gSPDisplayList(arg0++, D_82193220);

            for (k = 0; k < 14; k++) {
                gSPVertex(arg0++, var_s0, 4, 0);
                gSP2Triangles(arg0++, 0, 2, 1, 0, 2, 3, 1, 0);
                var_s0 += 2;
            }
        }
    }

    return arg0;
}
