/* Stadium Zero fragment012_17ED00. */
/* C ported from the Stadium 1 decomp: src/fragments/battle_engine/battle_engine_3540B0.c. */

#include "fragments/battle_engine/battle_engine.h"
#include "gfx_buffer.h"
#include "m2c_macros.h"

extern OwnerLinkedFourStream D_821B5E30[4];
void OwnerAnchoredFourStream_Update(f32 arg0, Vec3f* arg1, f32 arg2);
void OwnerAnchoredFourStream_UpdateNodeChain(OwnerAnchoredFourStream* arg0);

typedef struct OwnerLinkedFourStreamZero {
    /* 0x000 */ s16 unk_000;
    /* 0x002 */ s16 unk_002;
    /* 0x004 */ s16 unk_004;
    /* 0x006 */ char unk006[0x16];
    /* 0x01C */ OwnerLinkedFourStreamNode unk_01C[15];
} OwnerLinkedFourStreamZero; // size = 0x418

extern OwnerLinkedFourStreamZero D_821B6F00[4];

/**
 * Seen in play (2026-11-13) (unattended Free Battle in which every Pokémon knows only Metronome, 70
 * turns): ran.
 * @unverified Name was previously used only by callers of this address; the definition was still func_.
 */
void OwnerAnchoredFourStream_Init(void) {
    s32 i;
    s32 j;
    OwnerLinkedFourStreamZero* var_a2 = &D_821B6F00[0];
    OwnerLinkedFourStreamNode* var_v0;

    for (i = 0; i < 4; i++, var_a2++) {
        var_a2->unk_000 = 0;
        var_a2->unk_002 = 0;
        var_a2->unk_004 = 0;

        var_v0 = &var_a2->unk_01C[0];
        for (j = 0; j < 15; j++, var_v0++) {
            var_v0->unk_00 = 0;
            var_v0->unk_04 = 1.0f;
            var_v0->unk_08 = 0.0f;
            var_v0->unk_0C.z = var_v0->unk_0C.y = var_v0->unk_0C.x = 0.0f;
            var_v0->unk_18.z = var_v0->unk_18.y = var_v0->unk_18.x = 0.0f;
        }
    }
}

typedef struct OwnerAnchoredFourStreamZero {
    /* 0x000 */ s16 unk_000;
    /* 0x002 */ s16 unk_002;
    /* 0x004 */ s16 unk_004;
    /* 0x006 */ s16 unk_006;
    /* 0x008 */ Color_RGB8 unk_008;
    /* 0x00C */ f32 unk_00C;
    /* 0x010 */ f32 unk_010;
    /* 0x014 */ Vtx* unk_014;
    /* 0x018 */ Particle* unk_018;
    /* 0x01C */ OwnerAnchoredFourStreamNode unk_01C[15];
} OwnerAnchoredFourStreamZero; // size = 0x418

/**
 * Seen in play (2026-11-13) (unattended Free Battle in which every Pokémon knows only Metronome, 70
 * turns): ran.
 * @unverified Name was previously used only by callers of this address; the definition was still func_.
 */
void OwnerAnchoredFourStream_Start(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, u8 arg6, u8 arg7, u8 arg8, u8 arg9,
                   f32 argA, f32 argB, f32 argC, s16 argD) {
    s32 i;
    s32 j;
    OwnerAnchoredFourStreamZero* var_v1;
    OwnerAnchoredFourStreamNode* var_s0;
    Vec3f sp64;
    Vec3f sp58;

    sp64.x = arg0;
    sp64.y = arg1;
    sp64.z = arg2;
    sp58.x = arg3;
    sp58.y = arg4;
    sp58.z = arg5;

    var_v1 = (OwnerAnchoredFourStreamZero*)&D_821B6F00[0];
    for (i = 0; i < 4; i++, var_v1++) {
        if (var_v1->unk_000 == 0) {
            var_v1->unk_000 = 1;
            var_v1->unk_002 = 0;
            var_v1->unk_004 = argD;
            var_v1->unk_008.r = arg6;
            var_v1->unk_008.g = arg7;
            var_v1->unk_008.b = arg8;
            var_v1->unk_00C = argC;
            var_v1->unk_010 = argA;

            var_v1->unk_018 = BattleAnim_SpawnSecondaryOwnerParticle(sp64, 2);
            if (arg3 < 0.0) {
                var_v1->unk_006 = -1;
            } else {
                var_v1->unk_006 = 1;
            }

            var_s0 = &var_v1->unk_01C[0];
            for (j = 0; j < 15; j++, var_s0++) {
                var_s0->unk_00 = (arg9 * (0xE - j)) / 15;
                var_s0->unk_04 = argB;
                var_s0->unk_08 = (RAND(120) * 6.2831855f) / 120.0;
                var_s0->unk_0C = sp64;
                var_s0->unk_18 = sp58;
            }
            break;
        }
    }
}

/**
 * Rotates the point (0, 0, arg2) about the X axis by arg0 radians and writes it to arg1.
 * @unverified Name from Stadium 1.
 */
void OwnerAnchoredFourStream_Update(f32 arg0, Vec3f* arg1, f32 arg2) {
    UNUSED MtxF sp70;
    MtxF sp30;
    UNUSED s32 pad; // FAKE: stack padding

    guRotateF(sp30.mf, (arg0 * 360.0) / 6.2831854820251465, 1.0f, 0.0f, 0.0f);
    guMtxXFMF(sp30.mf, 0.0f, 0.0f, arg2, &arg1->x, &arg1->y, &arg1->z);
}

/**
 * Steps a stream's 15-node chain: the head node moves by its velocity, bending sideways by
 * 0.4 a frame up to 20, and grows its width by 2 up to the stream's maximum; each other node
 * takes the previous frame's values of the node before it.
 * @unverified Name from Stadium 1.
 */
void OwnerAnchoredFourStream_UpdateNodeChain(OwnerAnchoredFourStream* arg0) {
    s32 i;
    OwnerAnchoredFourStreamNode* var_s0 = &arg0->unk_01C[0];

    for (i = 0; i < 15; i++, var_s0++) {
        if (i == 0) {
            var_s0->unk_24 = var_s0->unk_04;
            var_s0->unk_28 = var_s0->unk_08;

            var_s0->unk_2C = var_s0->unk_0C;
            var_s0->unk_38 = var_s0->unk_18;

            var_s0->unk_0C.x += var_s0->unk_18.x;
            var_s0->unk_0C.y += var_s0->unk_18.y;
            var_s0->unk_0C.z += var_s0->unk_18.z;

            var_s0->unk_08 += arg0->unk_010;
            if (arg0->unk_006 > 0) {
                var_s0->unk_18.x += 0.4;
                if (var_s0->unk_18.x > 20.0) {
                    var_s0->unk_18.x = 20.0f;
                }
            } else {
                var_s0->unk_18.x -= 0.4;
                if (var_s0->unk_18.x < -20.0) {
                    var_s0->unk_18.x = -20.0f;
                }
            }

            BattleAnim_SetParticlePosition(arg0->unk_018, var_s0->unk_0C);

            var_s0->unk_04 += 2.0;
            if (arg0->unk_00C < var_s0->unk_04) {
                var_s0->unk_04 = arg0->unk_00C;
            }
        } else {
            var_s0->unk_24 = var_s0->unk_04;
            var_s0->unk_28 = var_s0->unk_08;

            var_s0->unk_2C = var_s0->unk_0C;
            var_s0->unk_38 = var_s0->unk_18;

            var_s0->unk_0C = var_s0[-1].unk_2C;
            var_s0->unk_08 = var_s0[-1].unk_28;
            var_s0->unk_18 = var_s0[-1].unk_38;
            var_s0->unk_04 = var_s0[-1].unk_24;
        }
    }
}

/**
 * M2C_UNK func_8217E0C0(M2C_UNK *);                   /* extern
 * Seen in play (2026-11-13) (unattended Free Battle in which every Pokémon knows only Metronome, 70
 * turns): ran.
 * @unverified Name was previously used only by callers of this address; the definition was still func_.
 */
s32 OwnerAnchoredFourStream_IsComplete(void)
{
  s8 *new_var; // FAKE: permuter temp
  s32 var_s1;
  new_var = (s8*)D_821B6F00;
  var_s1 = 0;
  do
  {
    new_var = (s8 *) ((0, new_var)); // FAKE: comma expression
    if ((*((s16 *) (new_var + 0))) == 1)
    {
      new_var = new_var; // FAKE: self-assignment
      *((s16 *) (new_var + 2)) = (s16) ((*((s16 *) (new_var + 2))) + 1);
      if ((*((s16 *) (new_var + 4))) < (*((s16 *) (new_var + 2))))
      {
        *((s16 *) (new_var + 0)) = 0;
      }
      else
      {
        func_8217E0C0(new_var);
      }
    }
    var_s1 += 1;
    new_var += 0x418;
  }
  while (var_s1 != 4);
  return 0;
}

extern Gfx D_82193270[];
/**
 * Seen in play (2026-11-13) (unattended Free Battle in which every Pokémon knows only Metronome, 70
 * turns): ran.
 * @unverified Name was previously used only by callers of this address; the definition was still func_.
 */
Gfx* OwnerAnchoredFourStream_Draw(Gfx* arg0) {
    s32 i;
    s32 j;
    s32 k;
    OwnerAnchoredFourStreamNode* temp_s0;
    OwnerAnchoredFourStreamZero* var_s5;
    Vtx* var_s0;
    Vec3f sp154;
    UNUSED s32 pad[15]; // FAKE: stack padding
    Mtx* temp_v0;
    Mtx sp100;
    Mtx spC0;
    s16 var_s3;

    var_s5 = (OwnerAnchoredFourStreamZero*)&D_821B6F00[0];
    for (i = 0; i < 4; i++, var_s5++) {
        if (var_s5->unk_000 == 1) {
            temp_s0 = &var_s5->unk_01C[0];
            if (temp_s0->unk_0C.y > 0.0f) {
                temp_v0 = Gfx_AllocDisplayList(sizeof(Mtx) * 1);
                guTranslate(temp_v0, temp_s0->unk_0C.x, temp_s0->unk_0C.y, temp_s0->unk_0C.z);
                guRotateRPY(&sp100, (temp_s0->unk_08 * -360.0f * var_s5->unk_006) / 6.2831854820251465,
                            0x5A - (var_s5->unk_006 * 0x5A), 0.0f);
                guMtxCatL(&sp100, temp_v0, temp_v0);
                guScale(&spC0, 0.16f, 0.16f, 0.16f);
                guMtxCatL(&spC0, temp_v0, temp_v0);

                gSPMatrix(arg0++, temp_v0, G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW);
                gSPDisplayList(arg0++, D_821941F0);
                gSPPopMatrix(arg0++, G_MTX_MODELVIEW);
            }

            var_s5->unk_014 = Gfx_AllocDisplayList(sizeof(Vtx) * 30);

            var_s0 = var_s5->unk_014;
            for (j = 0; j < 15; j++) {
                OwnerAnchoredFourStream_Update(temp_s0->unk_08, &sp154, temp_s0->unk_04);

                var_s3 = temp_s0->unk_0C.y + sp154.y;
                if (var_s3 < 0) {
                    var_s3 = 0;
                }

                var_s0->v.ob[0] = temp_s0->unk_0C.x + sp154.x;
                var_s0->v.ob[1] = var_s3;
                var_s0->v.ob[2] = temp_s0->unk_0C.z + sp154.z;
                var_s0->v.cn[0] = var_s5->unk_008.r;
                var_s0->v.cn[1] = var_s5->unk_008.g;
                var_s0->v.cn[2] = var_s5->unk_008.b;
                var_s0->v.cn[3] = temp_s0->unk_00;
                var_s0++;

                OwnerAnchoredFourStream_Update(temp_s0->unk_08 + 3.1415927f, &sp154, temp_s0->unk_04);

                var_s3 = temp_s0->unk_0C.y + sp154.y;
                if (var_s3 < 0) {
                    var_s3 = 0;
                }

                var_s0->v.ob[0] = temp_s0->unk_0C.x + sp154.x;
                var_s0->v.ob[1] = var_s3;
                var_s0->v.ob[2] = temp_s0->unk_0C.z + sp154.z;
                var_s0->v.cn[0] = var_s5->unk_008.r;
                var_s0->v.cn[1] = var_s5->unk_008.g;
                var_s0->v.cn[2] = var_s5->unk_008.b;
                var_s0->v.cn[3] = temp_s0->unk_00;
                var_s0++;

                temp_s0++;
            }

            var_s0 = var_s5->unk_014;

            gSPDisplayList(arg0++, D_82193270);

            for (k = 0; k < 14; k++) {
                gSPVertex(arg0++, var_s0, 4, 0);
                gSP2Triangles(arg0++, 0, 2, 1, 0, 2, 3, 1, 0);
                var_s0 += 2;
            }
        }
    }

    return arg0;
}
