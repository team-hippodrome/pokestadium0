/* Stadium Zero fragment012_17ED00. */
/* C ported from the Stadium 1 decomp: src/fragments/battle_engine/battle_engine_317E70.c, src/fragments/trade_machine/trade_machine_28ED00.c. */

#include "fragments/battle_engine/battle_engine.h"
#include "geo_render.h"
#include "model_renderer.h"
#include "matrix.h"
#include "fragments/particle_math/particle_math.h"
#include "memory.h"

#include "fragments/trade_machine/trade_machine.h"
#include "geo_render.h"
#include "model_renderer.h"
#include "graphics_textures.h"
#include "ui_graphics.h"
#include "game_state.h"
#include "text_system.h"
#include "audio_sfx.h"
#include "matrix.h"
#include "geo_layout.h"
#include "math_util.h"
#include "memmap.h"
#include "memory.h"
s32 Trade_DrawBox3DModel(s32 arg0, GraphNode* arg1);

#include "m2c_macros.h"

s32 BattleAnim_IsCurrentOwnerSpecies(s32 arg0);
void BattleAnim_GetCurrentOwnerBonePosition(Vec3f* arg0);
void BattleAnim_GetSecondaryOwnerBonePosition(Vec3f* arg0);
void BattleAnim_GetTertiaryOwnerBonePosition(Vec3f* arg0);
void BattleAnim_GetSecondaryOwnerAnchorPosition(Vec3f* arg0);
void BattleAnim_GetTertiaryOwnerBone9Position(Vec3f* arg0);
void Trade_UpdateBoxSlotBobIdle(unk_D_82F20A88* arg0);
f32 BattleAnim_GetOwnerModelScale(ActivePokemon* arg0);
f32 BattleAnim_GetSecondaryOwnerModelScale(void);
void BattleAnim_GetSecondaryOwnerSpeciesBaseScale(void);
f32 BattleAnim_GetTertiaryOwnerModelScale(void);
void BattleAnim_GetTertiaryOwnerSpeciesBaseScale(void);
void BattleAnim_MarkParticleInactive(Particle* arg0);
void BattleAnim_DestroyParticle(Particle* arg0);

void BattleAnim_ReleaseParticleModel(Particle* arg0);
void BattleAnim_GetOwnerBonePosition(ActivePokemon* arg0, s16 arg1, Vec3f* arg2);
f32 BattleAnim_GetSpeciesBaseScale(ActivePokemon* arg0);
void BattleAnim_GetOwnerSpeciesBaseScaleAlias(ActivePokemon* arg0);
void Trade_UpdateBoxSlotBob(unk_D_82F20A88* arg0);

s32 BattleAnim_IsCurrentOwnerSpecies(s32 arg0) {
    s32 sp1C = 0;

    if (BattleAnim_GetOwnerSpecies(gBattleAnimCurrentOwner) == arg0) {
        sp1C = 1;
    }
    return sp1C;
}

void BattleAnim_GetOwnerBonePosition(ActivePokemon* arg0, s16 arg1, Vec3f* arg2);
void BattleAnim_GetOwnerBonePosition(ActivePokemon* arg0, s16 arg1, Vec3f* arg2);
void BattleAnim_GetOwnerBonePosition(ActivePokemon *arg0, s16 arg1, Vec3f *arg2) {
    s16 sp1E;

    sp1E = BattleAnim_GetOwnerSpecies(arg0);
    if ((GeoRender_FindAnchorPosition(&arg0->displayObject, arg1, arg2) == NULL) && ((arg0 == NULL) || (GeoRender_FindAnchorPosition(&arg0->displayObject, 0x64, arg2) == NULL))) {
        arg2->x = 0.0f;
        arg2->y = 0.0f;
        arg2->z = 0.0f;
    }
    if ((sp1E == 0x5F) && (arg1 == 0x64)) {
        GeoRender_FindAnchorPosition(&arg0->displayObject, 9, arg2);
        return;
    }
    if ((sp1E == 0x52) && ((arg1 == 0x64) || (arg1 == 9))) {
        GeoRender_FindAnchorPosition(&arg0->displayObject, 9, arg2);
        return;
    }
    if ((sp1E == 0x73) && (arg1 == 0x64)) {
        GeoRender_FindAnchorPosition(&arg0->displayObject, 9, arg2);
    }
}

void BattleAnim_GetCurrentOwnerBonePosition(Vec3f* arg0) {
    BattleAnim_GetOwnerBonePosition(gBattleAnimCurrentOwner, 0x64, arg0);
}

void BattleAnim_GetSecondaryOwnerBonePosition(Vec3f* arg0) {
    BattleAnim_GetOwnerBonePosition(gBattleAnimSecondaryOwner, 0x64, arg0);
}

void BattleAnim_GetTertiaryOwnerBonePosition(Vec3f* arg0) {
    BattleAnim_GetOwnerBonePosition(gBattleAnimTertiaryOwner, 0x64, arg0);
}

void BattleAnim_GetSecondaryOwnerAnchorPosition(Vec3f* arg0) {
    if (gBattleAnimDefaultAnchor == 0xFF) {
        BattleAnim_GetOwnerDefaultAnchorPosition(gBattleAnimSecondaryOwner, arg0);
    } else {
        BattleAnim_GetOwnerBonePosition(gBattleAnimSecondaryOwner, gBattleAnimCurrentAnchor, arg0);
    }
}

void BattleAnim_GetTertiaryOwnerBone9Position(Vec3f* arg0) {
    BattleAnim_GetOwnerBonePosition(gBattleAnimTertiaryOwner, 9, arg0);
}

void Trade_UpdateBoxSlotBobIdle(unk_D_82F20A88* arg0) {
    Trade_UpdateBoxSlotBob(arg0);
}

f32 BattleAnim_GetOwnerModelScale(ActivePokemon* arg0) {
    return BattleAnim_GetSpeciesBaseScale(arg0);
}

M2C_UNK func_82107BC4();                            /* extern */

void func_8213C75C(void) {
    func_82107BC4();
}

f32 BattleAnim_GetSecondaryOwnerModelScale(void) {
    return BattleAnim_GetOwnerModelScale(gBattleAnimSecondaryOwner);
}

void BattleAnim_GetSecondaryOwnerSpeciesBaseScale(void) {
    BattleAnim_GetOwnerSpeciesBaseScaleAlias(gBattleAnimSecondaryOwner);
}

f32 BattleAnim_GetTertiaryOwnerModelScale(void) {
    return BattleAnim_GetOwnerModelScale(gBattleAnimTertiaryOwner);
}

void BattleAnim_GetTertiaryOwnerSpeciesBaseScale(void) {
    BattleAnim_GetOwnerSpeciesBaseScaleAlias(gBattleAnimTertiaryOwner);
}

extern s32 D_8219A878;

s32 func_8213C80C(void) {
    return D_8219A878;
}

Particle* BattleAnim_SpawnSecondaryOwnerParticle(Vec3f arg0, u8 arg1) {
    Particle* sp1C = Particle_New();

    if ((u32)sp1C != -1) {
        ParticleMath_CopyVec3f(&sp1C->unk_68, &arg0);
        BattleAnim_InitStingerMoveParticle(sp1C, arg1);
        sp1C->unk_10 = gBattleAnimSecondaryOwner;
        sp1C->unk_14 = NULL;
        sp1C->unk_CD = 0xFF;
        sp1C->unk_CC = 0x15;
        sp1C->unk_CA = 0;
    }
    return sp1C;
}

void BattleAnim_SetParticlePosition(Particle* arg0, Vec3f arg1) {
    if ((u32)arg0 != -1) {
        arg0->unk_68.x = arg1.x;
        arg0->unk_68.y = arg1.y;
        arg0->unk_68.z = arg1.z;
    }
}

void BattleAnim_MarkParticleInactive(Particle* arg0) {
    Particle_MarkInactive(arg0);
}

void Particle_InitLifecycle(Particle* arg0) {
    arg0->unk_B2 = 1;
    arg0->unk_0C = &gDefaultParticleDescriptor;
    arg0->unk_08 = NULL;
    arg0->unk_10 = 0;
    arg0->unk_14 = 0;
    arg0->unk_B8 = 0;
    Particle_SetFlags(arg0, 4);
}

void func_8213C930(s8 *arg0) {
    M2C_FIELD(arg0, s16 *, 0xAE) = 0;
}

M2C_UNK func_8213D260();                            /* extern */

void func_8213C938(s8 *arg0) {
    M2C_FIELD(arg0, s16 *, 0xAE) = 0;
    M2C_FIELD(arg0, s32 *, 8) = 0;
    M2C_FIELD(arg0, s32 *, 0xC) = 0;
    func_8213D260();
}

void BattleAnim_DestroyParticle(Particle* arg0) {
    BattleAnim_ReleaseParticleModel(arg0);
    arg0->unk_18 = 0;
    Particle_DisableAndDetach(arg0);
    Particle_Free(arg0);
}

s32 func_8213C994(s8 *arg0) {
    s32 var_v1;

    var_v1 = 0;
    if (M2C_FIELD(arg0, s16 *, 0xAE) == 0) {
        var_v1 = 1;
    }
    return var_v1;
}

s32 func_8213C9B0(s8 *arg0) {
    s32 var_v1;

    var_v1 = 0;
    if (M2C_FIELD(arg0, s16 *, 0xAE) >= 2) {
        var_v1 = 1;
    }
    return var_v1;
}

void Particle_AdvanceLifecycle(Particle* arg0) {
    Particle_ClearFlags(arg0, 1);
    arg0->unk_B2++;
}

s32 Particle_TickDelayTimer(Particle* arg0, s16 arg1) {
    s32 sp1C = 0;

    if (Particle_LacksFlags(arg0, 0x80) != 0) {
        Particle_SetFlags(arg0, 0x80);
        arg0->unk_BC = arg1;
    }

    arg0->unk_BC--;
    if (arg0->unk_BC <= 0) {
        arg0->unk_BC = 0;
        Particle_ClearFlags(arg0, 0x80);
        sp1C = 1;
    }

    return sp1C;
}
