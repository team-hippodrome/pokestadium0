/* Stadium Zero fragment012_17ED00. */
/* C ported from the Stadium 1 decomp: src/fragments/battle_engine/battle_engine_3591E0.c, src/fragments/ekans_game/ekans_game.c. */

#include "battle.h"
#include "fragments/cartridge_check/cartridge_check.h"
#include "gfx_buffer.h"
#include "vector_math.h"
extern AuxiliaryEffect D_821CEEA0[2];
extern Gfx D_82193E18[];

#include "global.h"

void AuxiliaryEffect_Init(void);
s16 AuxiliaryEffect_Alloc(void);
void AuxiliaryEffect_Spawn(s16 arg0, f32 arg1, f32 arg2, f32 arg3, s16 arg4, f32 arg5);
void AuxiliaryEffect_Update(s16 arg0);
Gfx* AuxiliaryEffect_DrawOne(Gfx* arg0, AuxiliaryEffectNode* arg1, MtxF* arg2);
Gfx* AuxiliaryEffect_Draw(s16 arg0, Gfx* arg1);
void func_821832F4(void);
void func_821832FC(void);
s32 AuxEffect_GetId(s32 arg0);

/**
 * Marks both auxiliary effect pools free.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (164 of the moves).
 * @unverified Name from Stadium 1.
 */
void AuxiliaryEffect_Init(void) {
    s32 i;

    for (i = 0; i < 2; i++) {
        D_821CEEA0[i].unk_000 = 0;
    }
}

/**
 * Claims a free auxiliary effect pool (of 2), clears its 20 nodes and returns its index,
 * or -1 if both are in use.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (20 of the moves).
 * @unverified Name from Stadium 1.
 */
s16 AuxiliaryEffect_Alloc(void) {
    AuxiliaryEffect* var_a0;
    AuxiliaryEffectNode* var_v1;
    s32 i;
    s32 j;

    for (i = 0, var_a0 = &D_821CEEA0[0]; i < 2; i++, var_a0++) {
        if (var_a0->unk_000 == 0) {
            var_v1 = &var_a0->unk_004[0];
            for (j = 0; j < 20; j++, var_v1++) {
                var_v1->unk_00 = 0;
                var_v1->unk_04 = 0;
                var_v1->unk_08 = 1.0f;
                var_v1->unk_0C.x = 0.0f;
                var_v1->unk_0C.y = 0.0f;
                var_v1->unk_0C.z = 0.0f;
            }
            var_a0->unk_000 = 1;
            return i;
        }
    }
    return -1;
}

/**
 * Starts a node in auxiliary effect pool arg0 at (arg1, arg2, arg3) with parameters arg4
 * and arg5, if the pool is active and a node is free.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (16 of the moves).
 * @unverified Name from Stadium 1.
 */
void AuxiliaryEffect_Spawn(s16 arg0, f32 arg1, f32 arg2, f32 arg3, s16 arg4, f32 arg5) {
    s32 i;
    AuxiliaryEffect* temp_v0 = &D_821CEEA0[arg0];
    AuxiliaryEffectNode* var_v1;

    if (temp_v0->unk_000 != 0) {
        var_v1 = &temp_v0->unk_004[0];
        for (i = 0; i < 20; i++, var_v1++) {
            if (var_v1->unk_00 == 0) {
                var_v1->unk_00 = 1;
                var_v1->unk_04 = 0;
                var_v1->unk_06 = arg4;
                var_v1->unk_08 = arg5;
                var_v1->unk_0C.x = arg1;
                var_v1->unk_0C.y = arg2;
                var_v1->unk_0C.z = arg3;
                return;
            }
        }
    }
}

/**
 * Advances every running node in auxiliary effect pool arg0.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (20 of the moves).
 * @unverified Name from Stadium 1.
 */
void AuxiliaryEffect_Update(s16 arg0) {
    AuxiliaryEffect* temp_v0 = &D_821CEEA0[arg0];
    AuxiliaryEffectNode* var_v1;
    s32 i;

    if (temp_v0->unk_000 != 0) {
        var_v1 = &temp_v0->unk_004[0];
        for (i = 0; i < 20; i++, var_v1++) {
            if (var_v1->unk_00 == 1) {
                var_v1->unk_04++;
                if (var_v1->unk_06 < var_v1->unk_04) {
                    var_v1->unk_00 = 0;
                }
                var_v1->unk_0C.y -= 0.75f;
            }
        }
    }
}

/**
 * Adds the display list for one auxiliary effect node, transformed by arg2, and returns
 * the new end of the list.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (16 of the moves).
 * @unverified Name from Stadium 1.
 */
Gfx* AuxiliaryEffect_DrawOne(Gfx* arg0, AuxiliaryEffectNode* arg1, MtxF* arg2) {
    f32 spCC;
    f32 spC8;
    f32 spC4;
    f32 spC0;
    Mtx* spBC;
    Mtx sp78;
    Mtx sp38;

    spCC = arg1->unk_0C.x;
    spC8 = arg1->unk_0C.y;
    spC4 = arg1->unk_0C.z;
    spC0 = arg1->unk_08;
    spC0 *= __sinf((arg1->unk_04 * 3.1415927f) / 10.0f);

    guScale(&sp38, spC0, spC0, spC0);
    guTranslate(&sp78, spCC, spC8, spC4);
    spBC = Gfx_AllocDisplayList(sizeof(Mtx) * 1);
    guMtxCatL(&sp38, &sp78, spBC);
    guMtxCatL(arg2, spBC, spBC);

    gSPMatrix(arg0++, spBC, G_MTX_PUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gDPSetPrimColor(arg0++, 0, 0, 255, 255, 255, 200); // #FFFFFFC8
    gSPDisplayList(arg0++, D_82193E18);
    gSPPopMatrix(arg0++, G_MTX_MODELVIEW);

    return arg0;
}

/**
 * Adds the display lists for every running node in auxiliary effect pool arg0 and returns
 * the new end of the list.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (28 of the moves).
 * @unverified Name from Stadium 1.
 */
Gfx* AuxiliaryEffect_Draw(s16 arg0, Gfx* arg1) {
    UNUSED s32 pad; // FAKE: stack padding
    AuxiliaryEffect* temp_s3 = &D_821CEEA0[arg0];
    AuxiliaryEffectNode* var_s0;
    s32 i;
    MtxF sp78;
    MtxF sp38;

    if (temp_s3->unk_000 == 0) {
        return arg1;
    }

    MtxF_ExtractScale(sp78.mf, &D_80060488->view.floatMatrix);
    guMtxF2L(sp78.mf, sp38.mf);

    var_s0 = &temp_s3->unk_004;
    for (i = 0; i < 20; i++, var_s0++) {
        if (var_s0->unk_00 == 1) {
            arg1 = AuxiliaryEffect_DrawOne(arg1, var_s0, &sp38);
        }
    }

    return arg1;
}

/**
 * Empty.
 */
void func_821832F4(void) {
}

/**
 * Empty.
 */
void func_821832FC(void) {
}

/**
 * Returns its argument.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal or j,
 * no pointer word, no lui/addiu pair in any fragment), so play cannot reach it.
 * @unverified Name from Stadium 1.
 */
s32 AuxEffect_GetId(s32 arg0) {
    return arg0;
}
