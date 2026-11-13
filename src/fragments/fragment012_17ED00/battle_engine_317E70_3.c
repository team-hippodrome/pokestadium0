/* Stadium Zero fragment012_17ED00. */
/* C ported from the Stadium 1 decomp: src/fragments/battle_engine/battle_engine_317E70.c, src/fragments/trade_machine/trade_machine_28ED00.c. */

#include "fragments/battle_engine/battle_engine.h"
#include "geo_render.h"
#include "model_renderer.h"
#include "matrix.h"
#include "fragments/particle_math/particle_math.h"
#include "memory.h"
#include "pokemon.h"

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
void BattleAnim_GetOwnerModelSizeScaled(unk_D_82F20A88* arg0);
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
void BattleScene_GetParticipantModelSizeScaled(unk_D_82F20A88* arg0);

/**
 * Returns 1 if the current animation owner's model shows species arg0.
 * @unverified Name from Stadium 1.
 */
s32 BattleAnim_IsCurrentOwnerSpecies(s32 arg0) {
    s32 sp1C = 0;

    if (BattleAnim_GetOwnerSpecies(gBattleAnimCurrentOwner) == arg0) {
        sp1C = 1;
    }
    return sp1C;
}

void BattleAnim_GetOwnerBonePosition(ActivePokemon* arg0, s16 arg1, Vec3f* arg2);
void BattleAnim_GetOwnerBonePosition(ActivePokemon* arg0, s16 arg1, Vec3f* arg2);
/**
 * Writes the position of anchor bone arg1 of the Pokémon's model to arg2, falling back to
 * bone 0x64 and then to the origin. Onix, Magneton and Kangaskhan use bone 9 instead of
 * bone 0x64 (Magneton also for bone 9).
 * @unverified Name from Stadium 1.
 */
void BattleAnim_GetOwnerBonePosition(ActivePokemon *arg0, s16 arg1, Vec3f *arg2) {
    s16 sp1E;

    sp1E = BattleAnim_GetOwnerSpecies(arg0);
    if ((GeoRender_FindAnchorPosition(&arg0->displayObject, arg1, arg2) == NULL) && ((arg0 == NULL) || (GeoRender_FindAnchorPosition(&arg0->displayObject, 0x64, arg2) == NULL))) {
        arg2->x = 0.0f;
        arg2->y = 0.0f;
        arg2->z = 0.0f;
    }
    if ((sp1E == ONIX) && (arg1 == 0x64)) {
        GeoRender_FindAnchorPosition(&arg0->displayObject, 9, arg2);
        return;
    }
    if ((sp1E == MAGNETON) && ((arg1 == 0x64) || (arg1 == 9))) {
        GeoRender_FindAnchorPosition(&arg0->displayObject, 9, arg2);
        return;
    }
    if ((sp1E == KANGASKHAN) && (arg1 == 0x64)) {
        GeoRender_FindAnchorPosition(&arg0->displayObject, 9, arg2);
    }
}

/**
 * Writes the position of bone 0x64 of the current animation owner.
 * @unverified Name from Stadium 1.
 */
void BattleAnim_GetCurrentOwnerBonePosition(Vec3f* arg0) {
    BattleAnim_GetOwnerBonePosition(gBattleAnimCurrentOwner, 0x64, arg0);
}

/**
 * Writes the position of bone 0x64 of the secondary animation owner.
 * @unverified Name from Stadium 1.
 */
void BattleAnim_GetSecondaryOwnerBonePosition(Vec3f* arg0) {
    BattleAnim_GetOwnerBonePosition(gBattleAnimSecondaryOwner, 0x64, arg0);
}

/**
 * Writes the position of bone 0x64 of the tertiary animation owner.
 * @unverified Name from Stadium 1.
 */
void BattleAnim_GetTertiaryOwnerBonePosition(Vec3f* arg0) {
    BattleAnim_GetOwnerBonePosition(gBattleAnimTertiaryOwner, 0x64, arg0);
}

/**
 * Writes the secondary owner's default anchor position, or the position of the current
 * anchor bone if a default anchor is set.
 * @unverified Name from Stadium 1.
 */
void BattleAnim_GetSecondaryOwnerAnchorPosition(Vec3f* arg0) {
    if (gBattleAnimDefaultAnchor == 0xFF) {
        BattleAnim_GetOwnerDefaultAnchorPosition(gBattleAnimSecondaryOwner, arg0);
    } else {
        BattleAnim_GetOwnerBonePosition(gBattleAnimSecondaryOwner, gBattleAnimCurrentAnchor, arg0);
    }
}

/**
 * Writes the position of bone 9 of the tertiary animation owner.
 * @unverified Name from Stadium 1.
 */
void BattleAnim_GetTertiaryOwnerBone9Position(Vec3f* arg0) {
    BattleAnim_GetOwnerBonePosition(gBattleAnimTertiaryOwner, 9, arg0);
}

void BattleAnim_GetOwnerModelSizeScaled(unk_D_82F20A88* arg0) {
    BattleScene_GetParticipantModelSizeScaled(arg0);
}

/**
 * Returns the base model scale of the Pokémon's species.
 * @unverified Name from Stadium 1.
 */
f32 BattleAnim_GetOwnerModelScale(ActivePokemon* arg0) {
    return BattleAnim_GetSpeciesBaseScale(arg0);
}

M2C_UNK ActivePokemon_GetSizeRatio();                            /* extern */

void func_8213C75C(void) {
    ActivePokemon_GetSizeRatio();
}

/**
 * Returns the base model scale of the secondary animation owner.
 * @unverified Name from Stadium 1.
 */
f32 BattleAnim_GetSecondaryOwnerModelScale(void) {
    return BattleAnim_GetOwnerModelScale(gBattleAnimSecondaryOwner);
}

/**
 * Looks up the secondary owner's species base scale and discards it.
 * @unverified Name from Stadium 1.
 */
void BattleAnim_GetSecondaryOwnerSpeciesBaseScale(void) {
    BattleAnim_GetOwnerSpeciesBaseScaleAlias(gBattleAnimSecondaryOwner);
}

/**
 * Returns the base model scale of the tertiary animation owner.
 * @unverified Name from Stadium 1.
 */
f32 BattleAnim_GetTertiaryOwnerModelScale(void) {
    return BattleAnim_GetOwnerModelScale(gBattleAnimTertiaryOwner);
}

/**
 * Looks up the tertiary owner's species base scale and discards it.
 * @unverified Name from Stadium 1.
 */
void BattleAnim_GetTertiaryOwnerSpeciesBaseScale(void) {
    BattleAnim_GetOwnerSpeciesBaseScaleAlias(gBattleAnimTertiaryOwner);
}

extern s32 D_8219A878;

/**
 * Returns D_8219A878.
 * @unverified Name from Stadium 1.
 */
s32 BattleAnim_GetCameraContext(void) {
    return D_8219A878;
}

/**
 * Allocates a stinger-move particle of kind arg1 at arg0, owned by the secondary owner,
 * with anchor kind 0x15. Returns -1 if the pool is full.
 * @unverified Name from Stadium 1.
 */
Particle* BattleAnim_SpawnSecondaryOwnerParticle(Vec3f arg0, u8 arg1) {
    Particle* sp1C = Particle_New();

    if ((u32)sp1C != -1) {
        ParticleMath_CopyVec3f(&sp1C->origin, &arg0);
        BattleAnim_InitStingerMoveParticle(sp1C, arg1);
        sp1C->pokemon = gBattleAnimSecondaryOwner;
        sp1C->displayObject = NULL;
        sp1C->unk_CD = 0xFF;
        sp1C->unk_CC = 0x15;
        sp1C->unk_CA = 0;
    }
    return sp1C;
}

/**
 * Sets a particle's origin, unless the particle pointer is -1 (allocation failed).
 * @unverified Name from Stadium 1.
 */
void BattleAnim_SetParticlePosition(Particle* arg0, Vec3f arg1) {
    if ((u32)arg0 != -1) {
        arg0->origin.x = arg1.x;
        arg0->origin.y = arg1.y;
        arg0->origin.z = arg1.z;
    }
}

/**
 * Calls Particle_MarkInactive.
 * @unverified Name from Stadium 1.
 */
void BattleAnim_MarkParticleInactive(Particle* arg0) {
    Particle_MarkInactive(arg0);
}

/**
 * Start lifecycle 1 with a no-op descriptor, null associations, phase zero, and rendering enabled.
 * Seen in play (2026-11-13) in the 165-move sweep: it set the new particle's descriptor to
 * gDefaultParticleDescriptor (0x801A3920) and cleared the owner and callback, with lifecycle 1.
 */
void Particle_InitLifecycle(Particle* arg0) {
    arg0->lifecycle = 1;
    arg0->descriptor = &gDefaultParticleDescriptor;
    arg0->updateCallback = NULL;
    arg0->pokemon = 0;
    arg0->displayObject = 0;
    arg0->phase = 0;
    Particle_SetFlags(arg0, 4);
}

/**
 * Sets the particle's lifecycle (s16 at 0xAE) to 0, so it is destroyed on its next update.
 * @unverified Name from Stadium 1.
 */
void Particle_MarkInactive(s8 *arg0) {
    M2C_FIELD(arg0, s16 *, 0xAE) = 0;
}

M2C_UNK func_8213D260();                            /* extern */

void Particle_DisableAndDetach(s8 *arg0) {
    M2C_FIELD(arg0, s16 *, 0xAE) = 0;
    M2C_FIELD(arg0, s32 *, 8) = 0;
    M2C_FIELD(arg0, s32 *, 0xC) = 0;
    func_8213D260();
}

/**
 * Releases the particle's model, clears its flags, detaches it and returns it to the pool.
 * @unverified Name from Stadium 1.
 */
void BattleAnim_DestroyParticle(Particle* arg0) {
    BattleAnim_ReleaseParticleModel(arg0);
    arg0->flags = 0;
    Particle_DisableAndDetach(arg0);
    Particle_Free(arg0);
}

/**
 * Returns 1 if the particle's lifecycle is 0.
 * @unverified Name from Stadium 1.
 */
s32 Particle_IsInactive(s8 *arg0) {
    s32 var_v1;

    var_v1 = 0;
    if (M2C_FIELD(arg0, s16 *, 0xAE) == 0) {
        var_v1 = 1;
    }
    return var_v1;
}

/**
 * Returns 1 if the particle's lifecycle is 2 or more (past its init step).
 * @unverified Name from Stadium 1.
 */
s32 Particle_IsRunning(s8 *arg0) {
    s32 var_v1;

    var_v1 = 0;
    if (M2C_FIELD(arg0, s16 *, 0xAE) >= 2) {
        var_v1 = 1;
    }
    return var_v1;
}

/**
 * Clear the frame-animation initialization bit and advance the lifecycle.
 * Seen in play (2026-11-13) in the 165-move sweep: it moved lifecycle (offset 0xAE) from 1 to 2.
 */
void Particle_AdvanceLifecycle(Particle* arg0) {
    Particle_ClearFlags(arg0, 1);
    arg0->lifecycle++;
}

/**
 * Initialize once under flag 0x80, decrement immediately, and finish at zero while clearing that flag.
 * Seen in play (2026-11-13) in the 165-move sweep: on its first call with 0x14 it set flag 0x80,
 * set delayTimer to 0x13 and returned 0; called with 0 it returned 1 at once.
 */
s32 Particle_TickDelayTimer(Particle* arg0, s16 arg1) {
    s32 sp1C = 0;

    if (Particle_LacksFlags(arg0, 0x80) != 0) {
        Particle_SetFlags(arg0, 0x80);
        arg0->delayTimer = arg1;
    }

    arg0->delayTimer--;
    if (arg0->delayTimer <= 0) {
        arg0->delayTimer = 0;
        Particle_ClearFlags(arg0, 0x80);
        sp1C = 1;
    }

    return sp1C;
}
