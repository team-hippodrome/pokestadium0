/* Stadium Zero fragment012_17ED00. */
/* C ported from the Stadium 1 decomp: src/fragments/battle_engine/battle_engine_317E70.c, src/fragments/particle_math/particle_math_269820.c, src/fragments/particle_math/particle_math_26E540.c. */

#include "fragments/battle_engine/battle_engine.h"
#include "geo_render.h"
#include "model_renderer.h"
#include "matrix.h"
#include "fragments/particle_math/particle_math.h"
#include "memory.h"

#include "fragments/particle_math/particle_math.h"
#include "geo_render.h"
extern ParticleDescriptor gDefaultParticleDescriptor;

#include "fragments/particle_math/particle_math.h"

#include "m2c_macros.h"

void BattleAnim_FreeEffectSlot(BattleAnimEffectSlot* arg0);
Particle* Particle_New(void);
Particle* Particle_AllocChain(u8 arg0);
void BattleAnim_EmitParticleBurst(Particle* arg0, ParticleUpdateCallback arg1, ParticleDescriptor* arg2, s16 arg3);
void BattleAnim_UpdateOrDestroyParticle(Particle* arg0);
void BattleAnim_SpawnSingleParticle(BattleAnimEffectSlot* arg0);
void BattleAnim_DispatchParticleEmission(BattleAnimEffectSlot* arg0);
void BattleAnim_TickEffectSlots(void);
s32 Particle_CountActiveAlias(void);
void BattleAnim_ReleaseParticleModel(Particle* arg0);
s32 BattleAnim_IsEffectSpawningEnabled(void);
void BattleAnim_EnableEffectSpawning(void);
void Particle_UpdateFrameCountersAlias(void);
void BattleAnim_CleanupEffects(s32 cleanup_mode);
void BattleAnim_ResetSpawnDelay(void);
void BattleAnim_SetSpawnDelay(s32 arg0);
void BattleAnim_AddSpawnDelay(s32 arg0);
void BattleAnim_ResetSpawnDelayAlias(void);
BattleAnimEffectSlot* BattleAnim_CreateEffectSlot(s32 arg0, s32 arg1, s8 arg2, func_unk_D_8140E724 arg3, ParticleDescriptor* arg4,
                              ActivePokemon* arg5, s16 arg6, s16 arg7, u8 arg8, u8 arg9, u8 argA, u8 argB);
BattleAnimEffectSlot* BattleAnim_CreateEffectSlotForCurrentOwner(s32 arg0, func_unk_D_8140E724 arg1, ParticleDescriptor* arg2, s16 arg3, s16 arg4, u8 arg5,
                              u8 arg6, u8 arg7, u8 arg8);
BattleAnimEffectSlot* BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(s32 arg0, s32 arg1, s8 arg2, func_unk_D_8140E724 arg3, ParticleDescriptor* arg4, s16 arg5,
                              s16 arg6, u8 arg7, u8 arg8, u8 arg9, u8 argA);
BattleAnimEffectSlot* BattleAnim_SpawnGlobalTintColorFadeDetach(s32 arg0, s16 arg1, u8 arg2);
BattleAnimEffectSlot* BattleAnim_SpawnWhiteHueChange(s32 arg0, s16 arg1, s16 arg2, u8 arg3, u8 arg4);
BattleAnimEffectSlot* BattleAnim_SpawnDescriptor25AlphaHoldFadeOutFullAlpha(s32 arg0, s16 arg1, s16 arg2, u8 arg3);
BattleAnimEffectSlot* BattleAnim_SpawnDescriptor25AlphaHoldFadeOut(s32 arg0, s16 arg1, s16 arg2, u8 arg3, u8 arg4);
BattleAnimEffectSlot* BattleAnim_SpawnDescriptor25AlphaHoldFadeOutRepeating(s32 arg0, s32 arg1, s8 arg2, s16 arg3, s16 arg4, u8 arg5, u8 arg6);
BattleAnimEffectSlot* BattleAnim_SpawnDescriptor25AlphaFadeInHoldFullAlpha(s32 arg0, s16 arg1, s16 arg2, u8 arg3);
BattleAnimEffectSlot* BattleAnim_SpawnDescriptor25AlphaFadeInHold(s32 arg0, s16 arg1, s16 arg2, u8 arg3, u8 arg4);
BattleAnimEffectSlot* BattleAnim_SpawnDescriptor25AlphaFadeInHoldRepeating(s32 arg0, s32 arg1, s8 arg2, s16 arg3, s16 arg4, u8 arg5, u8 arg6);
BattleAnimEffectSlot* BattleAnim_SpawnDescriptor25AlphaHoldDetachFullAlpha(s32 arg0, s16 arg1, u8 arg2);
BattleAnimEffectSlot* BattleAnim_SpawnDescriptor25AlphaHoldDetach(s32 arg0, s16 arg1, u8 arg2, u8 arg3);
BattleAnimEffectSlot* BattleAnim_SpawnDescriptor25AlphaHoldDetachRepeating(s32 arg0, s32 arg1, s8 arg2, s16 arg3, u8 arg4, u8 arg5);
BattleAnimEffectSlot* BattleAnim_SpawnDescriptor25PaletteFadeOut(s32 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4);
BattleAnimEffectSlot* BattleAnim_SpawnDescriptor25PaletteFadeIn(s32 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4);
BattleAnimEffectSlot* BattleAnim_SpawnOwnerModelTintRampDetach(s32 arg0, u8 arg1, s16 arg2, s16 arg3, s16 arg4);
BattleAnimEffectSlot* BattleAnim_SpawnOwnerModelTintPulseDetach(s32 arg0, s16 arg1, u8 arg2, s16 arg3, s16 arg4, s16 arg5);
BattleAnimEffectSlot* BattleAnim_SpawnOwnerModelTintHoldFadeDetach(s32 arg0, s16 arg1, u8 arg2, s16 arg3, s16 arg4);
BattleAnimEffectSlot* BattleAnim_SpawnBeamBoomWaterfallHueChange(s32 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4);
BattleAnimEffectSlot* BattleAnim_SpawnOwnerModelTintPaletteApproachInactiveAlt(s32 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4);
BattleAnimEffectSlot* BattleAnim_SpawnIceBeamBlizzardHitHueChange(s32 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5);
BattleAnimEffectSlot* BattleAnim_SpawnOwnerModelTintPaletteCycleVariant(s32 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5);
BattleAnimEffectSlot* BattleAnim_SpawnDrainFlameHueChange(s32 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5);
BattleAnimEffectSlot* BattleAnim_SpawnOwnerModelTintRandomPaletteCycle(s32 arg0, s16 arg1, u8 arg2);
BattleAnimEffectSlot* BattleAnim_SpawnRainbowHueChange(s32 arg0, s16 arg1, s16 arg2, u8 arg3);
BattleAnimEffectSlot* BattleAnim_SpawnInvisibility(s32 arg0, s16 arg1, s16 arg2, s16 arg3);
BattleAnimEffectSlot* BattleAnim_SpawnOwnerModelAlphaFadeFullPreset(s32 arg0);
BattleAnimEffectSlot* BattleAnim_SpawnOwnerModelAlphaFadeZeroStartPreset(s32 arg0);
BattleAnimEffectSlot* BattleAnim_SpawnCategory17MarkerSlot(s32 arg0, u8 arg1);
BattleAnimEffectSlot* BattleAnim_SpawnCategory19MarkerSlot(s32 arg0, u8 arg1);

BattleAnimEffectSlot* BattleAnim_AllocEffectSlot(void);
void BattleAnim_CloneParticleState(Particle* arg0, Particle* arg1, ParticleUpdateCallback arg2, ParticleDescriptor* arg3,
                   s32 arg4);
Particle* BattleAnim_CreateProceduralParticle(s16 arg0, s16 arg1, s32 arg2, f32 arg3);
void BattleAnim_DestroyParticle(Particle* arg0);
void BattleAnim_InitializeParticleFromEffect(Particle* arg0, ActivePokemon* arg1, BattleAnimEffectSlot* arg2, s16 arg3);
void BattleAnim_SpawnStandardParticles(s8 *arg0);
void BattleAnim_SpawnBatchedParticles(s8* arg0);
void BattleAnim_CleanupEffectsRetainingCategories47(void);
void BattleAnim_CleanupEffectsRetainingCategory4(void);
void BattleAnim_ClearEffectCallbacks(void);
void BattleAnim_SetEffectState(s32 arg0);
Particle* Particle_Alloc(void);
s32 Particle_CountActive(void);
s32 Particle_IsInactive(s8 *arg0);
s32 Particle_HasFlags(Particle* arg0, s32 arg1);
void Particle_UpdateWorldTransform(Particle* arg0);
void Particle_UpdateFrameCounters(void);

s32 func_800023C4(M2C_UNK, M2C_UNK);                /* extern */
M2C_UNK func_8004FD20(s32, M2C_UNK);                /* extern */
extern s32 D_8219CA50;
extern s32 D_8219CA54;
extern s32 D_8219CA58;
extern s32 D_8219CA5C;

/**
 * Seen in play (2026-11-13) ran during the opening of a COM Free Battle, before the first command
 * menu.
 * @unverified Name was previously used only by callers of this address; the definition was still func_.
 */
void BattleAnim_InitParticleSystem(void) {
    D_8219CA54 = func_800023C4(0x20D0, 0);
    D_8219CA50 = func_800023C4(0xF3C0, 0);
    func_8004FD20(D_8219CA54, 0x20D0);
    func_8004FD20(D_8219CA50, 0xF3C0);
    D_8219CA5C = 0;
    D_8219CA58 = 0;
}

/**
 * Initialize lifecycle, motion parameters, rotation, timers, and white colors without clearing the entire allocation.
 * Seen in play (2026-11-12) during Flamethrower: ran on each newly allocated slot before
 * Particle_Alloc returned it.
 */
void Particle_ResetDefaults(Particle* arg0) {
    Particle_InitLifecycle(arg0);
    Particle_SetPosition(arg0, 0.0f, 0.0f, 0.0f);
    Particle_SetOrigin(arg0, 0.0f, 0.0f, 0.0f);
    Particle_SetMotionOffset(arg0, 0.0f, 0.0f, 0.0f);
    Particle_SetVelocityTarget(arg0, 0.0f, 0.0f, 0.0f);
    Particle_SetMotionStep(arg0, 0.0f, 0.0f, 0.0f);
    Particle_Field74_SetScaled_0AD8C(arg0, 0.0f);
    Particle_Field78_SetScaled_0ADA4(arg0, 0.0f);
    Particle_SetRotation(arg0, 0, 0, 0);
    Particle_SetRotationSpeed(arg0, 0, 0, 0);
    Particle_SetTextureFrame(arg0, 0);
    Particle_FieldA6_SetS16_0BCA8(arg0, 0);
    Particle_FieldA8_SetS16_0BE14(arg0, 0);
    Particle_FieldCD_SetS16_0BF38(arg0, 0);
    Particle_FieldCE_SetS16_0BF24(arg0, 0);
    Particle_FieldAA_SetS16_0BF10(arg0, 0);
    Particle_FieldAC_SetS16_0BED8(arg0, 0);
    Particle_FieldCF_SetU8_0BEEC(arg0, 0);
    Particle_SetPrimColor(arg0, 0xFF, 0xFF, 0xFF);
    Particle_SetEnvColor(arg0, 0xFF, 0xFF, 0xFF);
    Particle_SetPrimAlpha(arg0, 0xFF);

    arg0->scale = 1.0f;
}

/**
 * Search the 300-slot pool from the rolling index, initialize a free slot, or return (Particle*)-1.
 * Seen in play (2026-11-12) during Flamethrower: successive calls returned consecutive pool slots
 * 0x802993A0, 0x80299470 and 0x80299540, 0xD0 apart (the Particle size). Each one went through
 * Particle_ResetDefaults first.
 */
Particle* Particle_Alloc(void) {
    s32 i;
    s32 var_v0 = gParticlePoolIndex;
    Particle* var_a0 = &gParticlePool[var_v0];

    for (i = 0; i < 300; i++) {
        if (var_a0->allocated == 0) {
            break;
        }

        var_v0++;
        if (var_v0 >= 0x12C) {
            var_v0 = 0;
            var_a0 = &gParticlePool[0];
        } else {
            var_a0++;
        }
    }

    if (i >= 0x12C) {
        var_a0 = (Particle*)-1;
    } else {
        var_a0->allocated = 1;

        Particle_ResetDefaults(var_a0);

        gParticlePoolIndex = var_v0 + 1;
        if (gParticlePoolIndex >= 0x12C) {
            gParticlePoolIndex = 0;
        }
    }

    return var_a0;
}

/**
 * Finds a free slot in the 300-entry effect slot ring, starting at
 * gBattleAnimEffectSlotIndex and wrapping around, and marks it in use. Returns -1 when all
 * slots are taken.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (157 of the moves).
 * @unverified Name from Stadium 1.
 */
BattleAnimEffectSlot* BattleAnim_AllocEffectSlot(void) {
    s32 i;
    s32 var_v0 = gBattleAnimEffectSlotIndex;
    BattleAnimEffectSlot* var_v1 = &gBattleAnimEffectSlots[var_v0];

    for (i = 0; i < 300; i++) {
        if (var_v1->unk_15 == 0) {
            break;
        }

        var_v0++;

        if (var_v0 >= 300) {
            var_v0 = 0;
            var_v1 = &gBattleAnimEffectSlots[0];
        } else {
            var_v1++;
        }
    }

    if (i >= 300) {
        var_v1 = -1;
    } else {
        var_v1->unk_15 = -0x1;

        gBattleAnimEffectSlotIndex = var_v0 + 1;
        if (gBattleAnimEffectSlotIndex >= 300) {
            gBattleAnimEffectSlotIndex = 0;
        }
    }

    return var_v1;
}

/**
 * Unlinks a particle from its doubly linked list (next at 0x0, previous at 0x4) and
 * clears its allocated flag.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (157 of the moves).
 * @unverified Name from Stadium 1.
 */
void Particle_Free(s8 *arg0) {
    s8 **temp_v0;
    s8 *temp_v0_2;

    temp_v0 = M2C_FIELD(arg0, s8 ***, 4);
    if (temp_v0 != NULL) {
        *temp_v0 = M2C_FIELD(arg0, s8 **, 0);
    }
    temp_v0_2 = M2C_FIELD(arg0, s8 **, 0);
    if (temp_v0_2 != NULL) {
        M2C_FIELD(temp_v0_2, s8 ***, 4) = (s8 **) M2C_FIELD(arg0, s8 ***, 4);
    }
    M2C_FIELD(arg0, s8 ***, 4) = NULL;
    M2C_FIELD(arg0, s8 **, 0) = NULL;
    M2C_FIELD(arg0, s8 *, 0xCC) = 0;
}

/**
 * Marks an effect slot free and clears its delay, repeat interval and repeat count.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (157 of the moves).
 * @unverified Name from Stadium 1.
 */
void BattleAnim_FreeEffectSlot(BattleAnimEffectSlot* arg0) {
    arg0->unk_0E = 0;
    arg0->unk_15 = 0;
    arg0->unk_14 = 0;
    arg0->unk_0C = arg0->unk_0E;
}

/**
 * Allocate one particle using the shared pool allocator.
 * Seen in play (2026-11-12) during Flamethrower: returned the slot from Particle_Alloc
 * (0x802993A0, 0x80299470, 0x80299540).
 */
Particle* Particle_New(void) {
    return Particle_Alloc();
}

/**
 * Allocate a linked chain, returning its first particle even if a later allocation fails.
 * Not reached in play (2026-11-13): no move in the 165-move battle sweep called it (each move used
 * once, from the command menu to the end of its turn).
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
Particle* Particle_AllocChain(u8 arg0) {
    s32 i;
    Particle* sp28;
    Particle* temp_v0;
    Particle* var_s0;

    sp28 = Particle_Alloc();

    if ((u32)sp28 != -1) {
        var_s0 = sp28;
        arg0--;

        for (i = 0; i < arg0; i++) {
            temp_v0 = Particle_Alloc();
            if ((u32)temp_v0 == -1) {
                break;
            }
            var_s0->next = temp_v0;
            temp_v0->prev = var_s0;
            var_s0 = temp_v0;
        }
    }

    return sp28;
}

/**
 * Walks a chain of particles and gives each the same origin, rotation, update callback
 * and descriptor, with no owner Pokémon or display object.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal or j,
 * no pointer word, no lui/addiu pair in any fragment), so play cannot reach it.
 * @unverified Name from Stadium 1.
 */
void BattleAnim_InitializeParticleChain(Particle* arg0, Vec3f arg1, Vec3s arg2, s32 arg3, s32 arg4) {
    while (arg0 != NULL) {
        ParticleMath_CopyVec3f(&arg0->origin, &arg1);
        ParticleMath_CopyVec3s(&arg0->rotation, &arg2);
        arg0->updateCallback = arg3;
        arg0->descriptor = arg4;
        arg0->pokemon = 0;
        arg0->displayObject = 0;
        arg0->unk_CD = 0xFF;

        arg0 = arg0->next;
    }
}

/**
 * Initializes new particle arg0 as burst child arg4 of particle arg1: copies the owner,
 * parameters, motion and transform state, and gives it update callback arg2 and
 * descriptor arg3. A child of a list-4 particle goes to list 0.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (34 of the moves).
 * @unverified Name from Stadium 1.
 */
void BattleAnim_CloneParticleState(Particle* arg0, Particle* arg1, ParticleUpdateCallback arg2, ParticleDescriptor* arg3,
                   s32 arg4) {
    arg0->updateCallback = arg2;
    arg0->descriptor = arg3;
    arg0->pokemon = arg1->pokemon;
    arg0->unk_CF = arg1->unk_CF;
    arg0->unk_CA = arg1->unk_CA;
    arg0->unk_CC = 0x1C;
    arg0->unk_CD = 0xFF;
    arg0->unk_CE = arg1->unk_CE;
    arg0->unk_CB = arg1->unk_CB;
    arg0->stepMagnitude = arg1->stepMagnitude;

    Particle_FieldAC_SetS16_0BED8(arg0, arg4);

    ParticleMath_CopyVec3f(&arg0->positionOffset, &arg1->positionOffset);
    ParticleMath_CopyVec3f(&arg0->motionOffset, &arg1->motionOffset);
    ParticleMath_CopyVec3f(&arg0->origin, &arg1->origin);
    ParticleMath_CopyVec3f(&arg0->motionStep, &arg1->motionStep);
    ParticleMath_CopyVec3s(&arg0->rotation, &arg1->rotation);
    ParticleMath_CopyVec3s(&arg0->rotationStep, &arg1->rotationStep);

    if (arg1->unk_CA == 4) {
        arg0->unk_CA = 0;
    }
}

/**
 * Spawns arg3 copies of particle arg0 that use update callback arg1 and descriptor arg2,
 * stopping early if the pool runs out. Each copy gets its index in the burst.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (16 of the moves).
 * @unverified Name from Stadium 1.
 */
void BattleAnim_EmitParticleBurst(Particle* arg0, ParticleUpdateCallback arg1, ParticleDescriptor* arg2, s16 arg3) {
    s16 i;
    Particle* temp_v0;

    for (i = 0; i < arg3; i++) {
        temp_v0 = Particle_New();
        if ((u32)temp_v0 == -1) {
            break;
        }
        BattleAnim_CloneParticleState(temp_v0, arg0, arg1, arg2, i);
    }
}

/**
 * Like BattleAnim_EmitParticleBurst, but also sets each child's CF parameter to arg4 and
 * CE parameter to arg5.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (24 of the moves).
 * @unverified Name from Stadium 1.
 */
void BattleAnim_EmitParticleBurstWithMetadata(Particle* arg0, ParticleUpdateCallback arg1, ParticleDescriptor* arg2, s16 arg3, s16 arg4,
                   s16 arg5) {
    s16 i;
    Particle* temp_v0;

    for (i = 0; i < arg3; i++) {
        temp_v0 = Particle_New();
        if ((u32)temp_v0 == -1) {
            break;
        }
        BattleAnim_CloneParticleState(temp_v0, arg0, arg1, arg2, i);
        temp_v0->unk_CE = arg5;
        temp_v0->unk_CF = arg4;
    }
}

/**
 * Allocates a screen-space particle at (arg0, arg1) with all three rotation angles set to
 * arg2 and scale arg3. Returns -1 if the pool is full.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (100 of the moves).
 * @unverified Name from Stadium 1.
 */
Particle* BattleAnim_CreateProceduralParticle(s16 arg0, s16 arg1, s32 arg2, f32 arg3) {
    Particle* temp_v0 = Particle_New();

    if ((u32)temp_v0 != -1) {
        Vec3f_SetComponentsDuplicate(&temp_v0->positionOffset, arg0, arg1, 0.0f);
        Particle_UpdateWorldTransform(temp_v0);
        Vec3s_SetComponents(&temp_v0->rotation, arg2, arg2, arg2);
        temp_v0->scale = arg3;
        Particle_SetFlags(temp_v0, 0x108);
    }
    return temp_v0;
}

void func_80015908(ActivePokemon*, s32, Vec3f*);
void BattleScene_GetParticipantModelSizeScaled(ActivePokemon* arg0, Vec3f* arg1);
/**
 * Sets the particle's origin once at spawn from its anchor mode (unk_CC): the owner's model
 * position, its default anchor, bone 100 (optionally on the ground, or pushed forward or
 * backward along its facing by its size), or its Poke Ball position.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (146 of the moves).
 * @unverified Name from Stadium 1.
 */
void BattleAnim_InitializeParticleAnchor(Particle* arg0) {
    Vec3f sp3C;
    Vec3f sp30;
    Vec3s sp28;

    switch (arg0->unk_CC) {
        case 0:
            BattleScene_GetParticipantModelPosition(arg0->pokemon, &arg0->origin);
            break;

        case 1:
            BattleAnim_GetOwnerDefaultAnchorPosition(arg0->pokemon, &arg0->origin);
            break;

        case 27:
            BattleAnim_GetOwnerDefaultAnchorPosition(arg0->pokemon, &arg0->origin);
            arg0->origin.y = 0.0f;
            break;

        case 9:
            BattleAnim_GetOwnerBonePosition(arg0->pokemon, 0x64, &arg0->origin);
            break;

        case 10:
            BattleAnim_GetOwnerBonePosition(arg0->pokemon, 0x64, &arg0->origin);
            arg0->origin.y = 0.0f;
            break;

        case 11:
            BattleAnim_GetOwnerBonePosition(arg0->pokemon, 0x64, &arg0->origin);
            BattleScene_GetParticipantModelRotation(arg0->pokemon, &sp28);
            BattleScene_GetParticipantModelSizeScaled(arg0->pokemon, &sp30);
            ParticleMath_MakeXZVectorFromAngle(&sp3C, sp30.x * 25.0f, sp28.y);
            ParticleMath_AddVec3f(&arg0->origin, &sp3C);
            break;

        case 12:
            BattleAnim_GetOwnerBonePosition(arg0->pokemon, 0x64, &arg0->origin);
            BattleScene_GetParticipantModelRotation(arg0->pokemon, &sp28);
            BattleScene_GetParticipantModelSizeScaled(arg0->pokemon, &sp30);
            ParticleMath_MakeXZVectorFromAngle(&sp3C, sp30.x * 25.0f, sp28.y + 0x8000);
            ParticleMath_AddVec3f(&arg0->origin, &sp3C);
            break;

        case 13:
            BattleAnim_GetOwnerBonePosition(arg0->pokemon, 0x64, &arg0->origin);
            BattleScene_GetParticipantModelSizeScaled(arg0->pokemon, &sp30);
            arg0->origin.y += sp30.y * 25.0f;
            break;

        case 14:
            BattleAnim_GetOwnerBonePosition(arg0->pokemon, 0x64, &arg0->origin);
            BattleScene_GetParticipantModelSizeScaled(arg0->pokemon, &sp30);
            arg0->origin.y -= sp30.y * 25.0f;
            if (arg0->origin.y <= 0.0f) {
                arg0->origin.y = 0.0f;
            }
            break;

        case 15:
            BattleAnim_GetOwnerBonePosition(arg0->pokemon, 0x64, &arg0->origin);
            BattleScene_GetParticipantModelRotation(arg0->pokemon, &sp28);
            BattleScene_GetParticipantModelSizeScaled(arg0->pokemon, &sp30);
            ParticleMath_MakeXZVectorFromAngle(&sp3C, sp30.x * 25.0f, sp28.y);
            ParticleMath_AddVec3f(&arg0->origin, &sp3C);
            arg0->origin.y = 0.0f;
            break;

        case 17:
            BattleAnim_GetOwnerBonePosition(arg0->pokemon, arg0->unk_CD, &arg0->origin);
            func_80015908(arg0->pokemon, arg0->unk_CD, &arg0->origin);
            break;

        case 19:
            func_80015908(arg0->pokemon, arg0->unk_CD, &arg0->origin);
            BattleScene_GetParticipantModelRotation(arg0->pokemon, &sp28);
            BattleScene_GetParticipantModelSizeScaled(arg0->pokemon, &sp30);
            ParticleMath_MakeXZVectorFromAngle(&sp3C, sp30.x * 25.0f, sp28.y);
            ParticleMath_AddVec3f(&arg0->origin, &sp3C);
            break;

        case 30:
            BattleScene_GetParticipantPokeBallPosition(arg0->pokemon, &arg0->origin);
            break;
    }
}

void BattleScene_GetParticipantModelSizeScaled(ActivePokemon* arg0, Vec3f* arg1);
/**
 * Re-reads the particle's origin each frame for the anchor modes that follow the owner:
 * bone 100, optionally on the ground, pushed along the owner's facing, or raised by its
 * model height; the last mode follows the Poke Ball.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (157 of the moves).
 * @unverified Name from Stadium 1.
 */
void BattleAnim_UpdateParticleAnchor(Particle* arg0) {
    Vec3f sp3C;
    Vec3f sp30;
    Vec3s sp28;

    switch (arg0->unk_CC) {
        case 2:
            BattleAnim_GetOwnerBonePosition(arg0->pokemon, 0x64, &arg0->origin);
            break;

        case 3:
            BattleAnim_GetOwnerBonePosition(arg0->pokemon, 0x64, &arg0->origin);
            arg0->origin.y = 0.0f;
            break;

        case 4:
            BattleAnim_GetOwnerBonePosition(arg0->pokemon, 0x64, &arg0->origin);
            BattleScene_GetParticipantModelRotation(arg0->pokemon, &sp28);
            BattleScene_GetParticipantModelSizeScaled(arg0->pokemon, &sp30);
            ParticleMath_MakeXZVectorFromAngle(&sp3C, sp30.x * 25.0f, sp28.y);
            ParticleMath_AddVec3f(&arg0->origin, &sp3C);
            break;

        case 5:
            BattleAnim_GetOwnerBonePosition(arg0->pokemon, 0x64, &arg0->origin);
            BattleScene_GetParticipantModelRotation(arg0->pokemon, &sp28);
            BattleScene_GetParticipantModelSizeScaled(arg0->pokemon, &sp30);
            ParticleMath_MakeXZVectorFromAngle(&sp3C, sp30.x * 25.0f, sp28.y + 0x8000);
            ParticleMath_AddVec3f(&arg0->origin, &sp3C);
            break;

        case 6:
            BattleAnim_GetOwnerBonePosition(arg0->pokemon, 0x64, &arg0->origin);
            BattleScene_GetParticipantModelSizeScaled(arg0->pokemon, &sp30);
            arg0->origin.y += sp30.y * 25.0f;
            break;

        case 7:
            BattleAnim_GetOwnerBonePosition(arg0->pokemon, 0x64, &arg0->origin);
            BattleScene_GetParticipantModelSizeScaled(arg0->pokemon, &sp30);
            arg0->origin.y -= sp30.y * 25.0f;
            if (arg0->origin.y <= 0.0f) {
                arg0->origin.y = 0.0f;
            }
            break;

        case 8:
            BattleAnim_GetOwnerBonePosition(arg0->pokemon, 0x64, &arg0->origin);
            BattleScene_GetParticipantModelRotation(arg0->pokemon, &sp28);
            BattleScene_GetParticipantModelSizeScaled(arg0->pokemon, &sp30);
            ParticleMath_MakeXZVectorFromAngle(&sp3C, sp30.x * 25.0f, sp28.y);
            ParticleMath_AddVec3f(&arg0->origin, &sp3C);
            arg0->origin.y = 0.0f;
            break;

        case 16:
            BattleAnim_GetOwnerBonePosition(arg0->pokemon, arg0->unk_CD, &arg0->origin);
            break;

        case 18:
            BattleAnim_GetOwnerBonePosition(arg0->pokemon, arg0->unk_CD, &arg0->origin);
            break;

        case 29:
            BattleScene_GetParticipantPokeBallPosition(arg0->pokemon, &arg0->origin);
            break;
    }
}

/**
 * Destroys the particle if it went inactive, otherwise updates its world transform.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (157 of the moves).
 * @unverified Name from Stadium 1.
 */
void BattleAnim_UpdateOrDestroyParticle(Particle* arg0) {
    if (Particle_IsInactive(arg0) != 0) {
        BattleAnim_DestroyParticle(arg0);
    } else {
        Particle_UpdateWorldTransform(arg0);
    }
}

void func_8213A68C(void) {
    s32 i;
    Particle* var_s0 = gParticlePool;

    for (i = 0; i < 300; i++, var_s0++) {
        if (var_s0->allocated != 0) {
            BattleAnim_UpdateParticleAnchor(var_s0);
            if ((var_s0->pokemon == NULL) || (Particle_HasFlags(var_s0, 0x108) != 0)) {
                gParticleRenderContext.scale.x = 1.0f;
                gParticleRenderContext.scale.y = 1.0f;
                gParticleRenderContext.scale.z = 1.0f;
            } else if (Particle_LacksFlags(var_s0, 0x800) != 0) {
                gParticleRenderContext.scale.x = BattleAnim_GetSpeciesBaseScale(var_s0->pokemon);
                gParticleRenderContext.scale.y = BattleAnim_GetSpeciesBaseScale(var_s0->pokemon);
                gParticleRenderContext.scale.z = BattleAnim_GetSpeciesBaseScale(var_s0->pokemon);
            }
            var_s0->updateCallback(var_s0);
            BattleAnim_UpdateOrDestroyParticle(var_s0);
        }
    }
}

void func_8213A904(s8 *);
M2C_UNK func_8213A9C4(s8 *, s32);                 /* extern */
s32 func_8213CAFC(s8 *, M2C_UNK);                 /* extern */
s32 func_8213CB1C(s8 *, M2C_UNK);                 /* extern */

void func_8213A784(s32 arg0) {
    s32 var_s3;
    s8 *var_s0;
    s8 *var_s2;

    var_s2 = D_8219CA50;
    var_s3 = 0;
    do {
        if ((M2C_FIELD(var_s2, s8 *, 0xCC) != 0) && (M2C_FIELD(var_s2, s32 *, 4) == 0) && (func_8213CB1C(var_s2, 8) != 0)) {
            func_8213A904(var_s2);
            var_s0 = var_s2;
            if (var_s2 != NULL) {
                do {
                    if ((func_8213CAFC(var_s0, 4) != 0) && (M2C_FIELD(var_s0, s16 *, 0xAE) >= 2)) {
                        func_8213A9C4(var_s0, arg0);
                    }
                    var_s0 = M2C_FIELD(var_s0, s8 **, 0);
                } while (var_s0 != NULL);
            }
        }
        var_s3 += 1;
        var_s2 += 0xD0;
    } while (var_s3 != 0x12C);
}

void func_8213A904(s8 *);
M2C_UNK func_8213A9C4(s8 *, s32);                 /* extern */
s32 func_8213CAFC(s8 *, M2C_UNK);                 /* extern */

void func_8213A858(s32 arg0) {
    s32 var_s1;
    s8 *var_s0;

    var_s0 = D_8219CA50;
    var_s1 = 0;
    do {
        if ((M2C_FIELD(var_s0, s8 *, 0xCC) != 0) && (func_8213CAFC(var_s0, 8) != 0)) {
            func_8213A904(var_s0);
            if ((func_8213CAFC(var_s0, 4) != 0) && (M2C_FIELD(var_s0, s16 *, 0xAE) >= 2)) {
                func_8213A9C4(var_s0, arg0);
            }
        }
        var_s1 += 1;
        var_s0 += 0xD0;
    } while (var_s1 != 0x12C);
}

typedef void (*Fn8213A904)(s8*, s32);
void func_8213A904(s8* arg0) {
    s8* desc = M2C_FIELD(arg0, s8**, 0xC);
    s8* sp = M2C_FIELD(desc, s8**, 4);

    if (M2C_FIELD(desc, s16*, 0) == 1) {
        switch (M2C_FIELD(sp, s16*, 2)) {
            case 0:
                gSPDisplayList(gDisplayListHead++, D_82190548);
                break;
            case 1:
                gSPDisplayList(gDisplayListHead++, D_821904C8);
                break;
        }
        if (M2C_FIELD(sp, s16*, 0) != 2) {
            M2C_FIELD(sp, Fn8213A904*, 4)(arg0, *M2C_FIELD(sp, s32**, 0xC));
        }
    }
}

typedef void (*ParticleDrawFn2)(Particle*, s32);
typedef void (*ParticleDrawFnCam)(Particle*, CameraNode*);
/**
 * For kind 1, optionally run per-particle setup then draw; kind 3 calls the direct render callback.
 * Seen in play (2026-11-12) during Flamethrower: ran each frame for the three newly allocated
 * particles.
 */
void Particle_DispatchDraw(Particle* arg0, CameraNode* arg1) {
    s8* desc = (s8*)arg0->descriptor;
    s8* sp18 = M2C_FIELD(desc, s8**, 4);

    switch (M2C_FIELD(desc, s16*, 0)) {
        case 1:
            if (M2C_FIELD(sp18, s16*, 0) == 2) {
                M2C_FIELD(sp18, ParticleDrawFn2*, 4)(arg0, M2C_FIELD(M2C_FIELD(sp18, s8**, 0xC), s32*, 0));
                M2C_FIELD(sp18, ParticleDrawFnCam*, 8)(arg0, arg1);
            } else {
                M2C_FIELD(sp18, ParticleDrawFnCam*, 8)(arg0, arg1);
            }
            break;

        case 3:
            M2C_FIELD(desc, ParticleDrawFnCam*, 4)(arg0, arg1);
            break;
    }
}

/**
 * Seen in play (2026-11-13) in the 165-move sweep (Pound and most hit moves): it filled each new
 * particle from its effect slot: the update callback (e.g. 0x80168350), the descriptor pointer, the
 * owner (1P 0x8028FB20 or COM 0x802905C0) and the origin position.
 */
void BattleAnim_InitializeParticleFromEffect(Particle* arg0, ActivePokemon* arg1, BattleAnimEffectSlot* arg2, s16 arg3) {
    if ((u32)arg0 == -1) {
        return;
    }

    if (1) {}  // karodo
    if (1) {}  // karodo
    if (1) {}  // karodo
    if (1) {}  // karodo
    if (1) {}  // karodo

    while (arg0 != NULL) {
        arg0->pokemon = arg1;
        arg0->unk_AC = arg3++;
        arg0->updateCallback = arg2->unk_00;
        arg0->descriptor = arg2->unk_04;
        arg0->unk_CD = arg2->unk_19;
        arg0->unk_CE = arg2->unk_1A;
        arg0->unk_AA = arg2->unk_12;
        arg0->unk_CF = arg2->unk_1B;
        arg0->unk_CA = arg2->unk_17;
        arg0->unk_CC = arg2->unk_16;
        arg0->unk_CB = arg2->unk_18;

        if (arg1 != NULL) {
            BattleAnim_InitializeParticleAnchor(arg0);
            BattleScene_GetParticipantModelRotation(arg0->pokemon, &arg0->rotation);
        }

        if ((arg2->unk_16 & 0xFFFFu) == 0x12) {
            arg0->unk_A6 = arg2->unk_10 * arg3;
        } else {
            arg0->unk_A6 = arg2->unk_10;
        }

        arg0 = arg0->next;
    }
}

s32 func_82139C38();                                /* extern */
s32 func_82139C58(s32);                             /* extern */
void BattleAnim_InitializeParticleFromEffect(Particle* arg0, ActivePokemon* arg1, BattleAnimEffectSlot* arg2, s16 arg3);

/**
 * Emits an effect slot's particles: one particle per count (slot field 0x12) from the
 * plain pool, or the whole count at once from the chained pool when the descriptor asks
 * for it.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (145 of the moves).
 * @unverified Name from Stadium 1.
 */
void BattleAnim_SpawnStandardParticles(s8 *arg0) {
    s16 temp_s2;
    s16 var_s0;
    s32 temp_s3;

    temp_s3 = M2C_FIELD(arg0, s32 *, 8);
    temp_s2 = M2C_FIELD(arg0, s16 *, 0x12);
    if (M2C_FIELD(M2C_FIELD(arg0, s8 **, 4), s16 *, 2) == 0) {
        var_s0 = 0;
        if (temp_s2 > 0) {
            do {
                BattleAnim_InitializeParticleFromEffect((Particle*)func_82139C38(), (ActivePokemon*)temp_s3, (BattleAnimEffectSlot*)arg0, var_s0);
                var_s0 += 1;
            } while (var_s0 < temp_s2);
        }
    } else {
        BattleAnim_InitializeParticleFromEffect((Particle*)func_82139C58(temp_s2 & 0xFF), (ActivePokemon*)temp_s3, (BattleAnimEffectSlot*)arg0, 0);
    }
}

/**
 * Like BattleAnim_SpawnStandardParticles, but spawns field 0x10 divided by field 0x12
 * particles and sets field 0x10 to the batch size before each one.
 * Not reached in play (2026-11-13): did not run in the 165-move battle sweep (each move used once,
 * from the command menu to the end of its turn) or in a tour of the menus and a COM battle.
 * @unverified Name from Stadium 1.
 */
void BattleAnim_SpawnBatchedParticles(s8* arg0) {
    s16 step;
    s16 count;
    s16 i;
    s32 temp_s4;
    s32 temp_v0;

    temp_s4 = M2C_FIELD(arg0, s32 *, 8);
    step = M2C_FIELD(arg0, s16 *, 0x12);
    count = M2C_FIELD(arg0, s16 *, 0x10) / step;
    if (M2C_FIELD(M2C_FIELD(arg0, s8 **, 4), s16 *, 2) == 0) {
        for (i = 0; i < count; i++) {
            temp_v0 = func_82139C38();
            M2C_FIELD(arg0, s16 *, 0x10) = step;
            BattleAnim_InitializeParticleFromEffect((Particle*)temp_v0, (ActivePokemon*)temp_s4, (BattleAnimEffectSlot*)arg0, i);
        }
    } else {
        temp_v0 = func_82139C58(count & 0xFF);
        M2C_FIELD(arg0, s16 *, 0x10) = step;
        BattleAnim_InitializeParticleFromEffect((Particle*)temp_v0, (ActivePokemon*)temp_s4, (BattleAnimEffectSlot*)arg0, 0);
    }
}

/**
 * Emits one particle for an effect slot, owned by the slot's Pokémon.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (57 of the moves).
 * @unverified Name from Stadium 1.
 */
void BattleAnim_SpawnSingleParticle(BattleAnimEffectSlot* arg0) {
    UNUSED s32 pad; // FAKE: stack padding
    ActivePokemon* sp18 = arg0->unk_08;

    BattleAnim_InitializeParticleFromEffect(Particle_New(), sp18, arg0, 0);
}

/**
 * Runs an effect slot that is due: by its kind (unk_16) it spawns batched particles, a
 * screen-centered or screen-origin procedural particle, sets an effect state flag,
 * queues effect list 9, spawns a single particle, or spawns standard particles.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (157 of the moves).
 * @unverified Name from Stadium 1.
 */
void BattleAnim_DispatchParticleEmission(BattleAnimEffectSlot* arg0) {
    switch (arg0->unk_16) {
        case 18:
            BattleAnim_SpawnBatchedParticles(arg0);
            break;

        case 22:
            BattleAnim_InitializeParticleFromEffect(BattleAnim_CreateProceduralParticle(0xA0, 0x78, 0, 1.0f), 0, arg0, 0);
            break;

        case 24:
            BattleAnim_InitializeParticleFromEffect(BattleAnim_CreateProceduralParticle(0, 0, 0, 1.0f), 0, arg0, 0);
            break;

        case 23:
            BattleAnim_SetEffectState(arg0->unk_19);
            break;

        case 25:
            BattleAnim_QueueEffectList9(arg0->unk_19);
            break;

        case 26:
            BattleAnim_SpawnSingleParticle(arg0);
            break;

        default:
            BattleAnim_SpawnStandardParticles(arg0);
            break;
    }
}

/**
 * Per-frame tick of all 300 effect slots: counts down each slot's delay, runs it when
 * due, and frees it after its last repeat (a repeat count of 127 repeats forever).
 * Otherwise reloads the delay from the repeat interval.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (165 of the moves).
 * @unverified Name from Stadium 1.
 */
void BattleAnim_TickEffectSlots(void) {
    s32 i;
    BattleAnimEffectSlot* var_s0 = gBattleAnimEffectSlots;

    for (i = 0; i < 300; i++, var_s0++) {
        if (var_s0->unk_15 != 0) {
            var_s0->unk_0E--;
            if (var_s0->unk_0E <= 0) {
                if (var_s0->unk_14 >= 0) {
                    BattleAnim_DispatchParticleEmission(var_s0);
                    if (var_s0->unk_14 != 0x7F) {
                        var_s0->unk_14--;
                    }

                    if (var_s0->unk_14 <= 0) {
                        BattleAnim_FreeEffectSlot(var_s0);
                    } else {
                        var_s0->unk_0E = var_s0->unk_0C;
                    }
                } else if (var_s0->unk_14 == -1) {
                    var_s0->unk_0E = var_s0->unk_0C;
                    BattleAnim_DispatchParticleEmission(var_s0);
                }
            }
        }
    }
}

/**
 * Count allocated pool slots, regardless of their lifecycle or rendering flags.
 * No caller in play (2026-11-13): it is only called from Particle_CountActiveAlias, which has no
 * caller in the ROM itself.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
s32 Particle_CountActive(void) {
    s32 i;
    s32 var_v1 = 0;
    Particle* ptr = gParticlePool;

    for (i = 0; i < 300; i++, ptr++) {
        if (ptr->allocated != 0) {
            var_v1++;
        }
    }

    return var_v1;
}

/**
 * Return the allocated-slot count through the shared counter.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
s32 Particle_CountActiveAlias(void) {
    return Particle_CountActive();
}

/**
 * Frees a particle's display object, through the particle display pool when flag 0x400
 * is set or the owner display pool otherwise.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (157 of the moves).
 * @unverified Name from Stadium 1.
 */
void BattleAnim_ReleaseParticleModel(Particle* arg0) {
    if (arg0->displayObject != NULL) {
        if (Particle_HasFlags(arg0, 0x400) != 0) {
            BattleAnim_FreeParticleDisplayContext(arg0->displayObject);
        } else {
            BattleAnim_FreeOwnerDisplayContext(arg0->displayObject);
        }
    }
}

/**
 * Clears the spawn delay, frees every effect slot and destroys every particle except
 * those in effect lists 4 and 7.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (136 of the moves).
 * @unverified Name from Stadium 1.
 */
void BattleAnim_CleanupEffectsRetainingCategories47(void) {
    s32 i;
    BattleAnimEffectSlot* var_s0 = gBattleAnimEffectSlots;
    Particle* var_s2 = gParticlePool;

    BattleAnim_ResetSpawnDelay();

    for (i = 0; i < 300; i++, var_s0++) {
        if (var_s0->unk_15 != 0) {
            if ((var_s0->unk_17 != 4) && (var_s0->unk_17 != 7)) {
                BattleAnim_FreeEffectSlot(var_s0);
            }
        }
    }

    for (i = 0; i < 300; i++, var_s2++) {
        if (var_s2->allocated != 0) {
            if ((var_s2->unk_CA != 4) && (var_s2->unk_CA != 7)) {
                BattleAnim_DestroyParticle(var_s2);
            }
        }
    }
}

/**
 * Frees every effect slot and destroys every particle outside effect list 4, then resets
 * the saved primitive color to white.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (164 of the moves).
 * @unverified Name from Stadium 1.
 */
void BattleAnim_CleanupEffectsRetainingCategory4(void) {
    s32 i;
    BattleAnimEffectSlot* var_s0 = gBattleAnimEffectSlots;
    Particle* var_s2 = gParticlePool;

    for (i = 0; i < 300; i++, var_s0++) {
        if ((var_s0->unk_15 != 0) && (var_s0->unk_17 != 4)) {
            BattleAnim_FreeEffectSlot(var_s0);
        }
    }

    for (i = 0; i < 300; i++, var_s2++) {
        if ((var_s2->allocated != 0) && (var_s2->unk_CA != 4)) {
            BattleAnim_DestroyParticle(var_s2);
        }
    }

    Model_SetMaterialColor(&sActivePokemon[0]->displayObject, 0xFF, 0xFF, 0xFF, 0);
    Model_SetMaterialColor(&sActivePokemon[1]->displayObject, 0xFF, 0xFF, 0xFF, 0);
    Model_SetMaterialAlpha(&sActivePokemon[0]->displayObject, 0xFF);
    Model_SetMaterialAlpha(&sActivePokemon[1]->displayObject, 0xFF);

    gSavedPrimColorB = 0xFF;
    gSavedPrimColorG = gSavedPrimColorB;
    gSavedPrimColorR = gSavedPrimColorG;
}

extern s32 D_84390340;
/**
 * Clears the 8 registered effect update and draw callbacks.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (164 of the moves).
 * @unverified Name from Stadium 1.
 */
void BattleAnim_ClearEffectCallbacks(void) {
    s32 i;

    for (i = 0; i < 8; i++) {
        if (gBattleAnimEffectUpdateFuncs[i] != NULL) {
            gBattleAnimEffectUpdateFuncs[i] = NULL;
            gBattleAnimEffectDrawFuncs[i] = NULL;
        }
    }
}

/**
 * Returns 1 if D_8219A830 is 0.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (136 of the moves).
 * @unverified Name from Stadium 1.
 */
s32 BattleAnim_IsEffectSpawningEnabled(void) {
    s32 var_v1 = 0;

    if (D_8219A830 == 0) {
        var_v1 = 1;
    }
    return var_v1;
}

extern s32 D_8219A830;

/**
 * Advance the particle clock and derive its remainder, quotient, and quotient-parity counters.
 * Seen in play (2026-11-13) (unattended Free Battle in which every Pokémon knows only Metronome, 40
 * turns): ran.
 * @unverified Name was previously used only by callers of this address; the definition was still func_. Comment from Stadium 1.
 */
void Particle_UpdateFrameCounters(void) {
    D_8219A830 = 1;
}

/**
 * Clears D_8219A830.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (164 of the moves).
 * @unverified Name from Stadium 1.
 */
void BattleAnim_EnableEffectSpawning(void) {
    D_8219A830 = 0;
}

/**
 * Advance the particle clock through the shared frame-counter updater.
 * Seen in play (2026-11-13) (unattended Free Battle in which every Pokémon knows only Metronome, 40
 * turns): ran.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void Particle_UpdateFrameCountersAlias(void) {
    Particle_UpdateFrameCounters();
}

/**
 * Tears down battle animation effects. Mode 1 keeps effect lists 4 and 7 (and keeps the
 * callbacks while spawning is disabled). Mode 2 keeps only list 4, clears the callbacks
 * and reinitializes the auxiliary effects.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (164 of the moves).
 * @unverified Name from Stadium 1.
 */
void BattleAnim_CleanupEffects(s32 cleanup_mode) {
    BattleAnim_ResetSpawnDelay();
    switch (cleanup_mode) {
        case 1:
            BattleAnim_CleanupEffectsRetainingCategories47();
            if (BattleAnim_IsEffectSpawningEnabled() != 0) {
                BattleAnim_ClearEffectCallbacks();
            }
            break;

        case 2:
            BattleAnim_CleanupEffectsRetainingCategory4();
            BattleAnim_ClearEffectCallbacks();
            BattleAnim_EnableEffectSpawning();
            BattleAnim_ReinitAuxiliaryEffects();
            break;
    }
}

/**
 * Advances the lifecycle of every list-4 particle of owner arg1 whose sub-kind (unk_CB)
 * is arg0, which tells looping effects to finish.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (2 of the moves).
 * @unverified Name from Stadium 1.
 */
void BattleAnim_StopParticlesForOwnerCategory(u8 arg0, ActivePokemon* arg1) {
    s32 i;
    Particle* var_s0 = gParticlePool;

    for (i = 0; i < 300; i++, var_s0++) {
        if ((var_s0->allocated != 0) && (var_s0->unk_CA == 4) && (var_s0->unk_CB == arg0) && (arg1 == var_s0->pokemon)) {
            Particle_AdvanceLifecycle(var_s0);
        }
    }
}

/**
 * Sets the delay added to newly created effect slots to 0.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (164 of the moves).
 * @unverified Name from Stadium 1.
 */
void BattleAnim_ResetSpawnDelay(void) {
    gBattleAnimSpawnDelay = 0;
}

/**
 * Sets the delay, in frames, added to newly created effect slots.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (1 of the moves).
 * @unverified Name from Stadium 1.
 */
void BattleAnim_SetSpawnDelay(s32 arg0) {
    gBattleAnimSpawnDelay = arg0;
}

/**
 * Adds arg0 frames to the delay given to newly created effect slots.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (16 of the moves).
 * @unverified Name from Stadium 1.
 */
void BattleAnim_AddSpawnDelay(s32 arg0) {
    gBattleAnimSpawnDelay += arg0;
}

/**
 * Calls BattleAnim_ResetSpawnDelay.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (159 of the moves).
 * @unverified Name from Stadium 1.
 */
void BattleAnim_ResetSpawnDelayAlias(void) {
    BattleAnim_ResetSpawnDelay();
}

/**
 * Queues an effect slot: it runs after arg0 frames (plus the current spawn delay), repeats
 * arg2 times every arg1 frames, and spawns particles with callback arg3 and descriptor arg4
 * for owner arg5. arg8 is the emission kind and arg6, arg7, arg9 to argB its parameters.
 * The slot remembers the current effect list and resource list. Returns -1 if no slot is
 * free.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (157 of the moves).
 * @unverified Name from Stadium 1.
 */
BattleAnimEffectSlot* BattleAnim_CreateEffectSlot(s32 arg0, s32 arg1, s8 arg2, func_unk_D_8140E724 arg3, ParticleDescriptor* arg4,
                              ActivePokemon* arg5, s16 arg6, s16 arg7, u8 arg8, u8 arg9, u8 argA, u8 argB) {
    BattleAnimEffectSlot* sp1C = BattleAnim_AllocEffectSlot();

    if ((u32)sp1C != -1) {
        sp1C->unk_0E = arg0 + gBattleAnimSpawnDelay;
        sp1C->unk_0C = arg1;
        sp1C->unk_14 = arg2;
        sp1C->unk_00 = arg3;
        sp1C->unk_04 = arg4;
        sp1C->unk_08 = arg5;
        sp1C->unk_16 = arg8;
        sp1C->unk_10 = arg6;
        sp1C->unk_12 = arg7;
        sp1C->unk_19 = arg9;
        sp1C->unk_1A = argB;
        sp1C->unk_1B = argA;
        sp1C->unk_17 = BattleAnim_GetCurrentEffectList();
        sp1C->unk_18 = BattleAnim_GetQueuedResourceListId();
    }
    return sp1C;
}

/**
 * BattleAnim_CreateEffectSlot for the current animation owner, run once.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (136 of the moves).
 * @unverified Name from Stadium 1.
 */
BattleAnimEffectSlot* BattleAnim_CreateEffectSlotForCurrentOwner(s32 arg0, func_unk_D_8140E724 arg1, ParticleDescriptor* arg2, s16 arg3, s16 arg4, u8 arg5,
                              u8 arg6, u8 arg7, u8 arg8) {
    return BattleAnim_CreateEffectSlot(arg0, 0, 1, arg1, arg2, gBattleAnimCurrentOwner, arg3, arg4, arg5, arg6, arg7, arg8);
}

/**
 * BattleAnim_CreateEffectSlot for the current animation owner, with a repeat interval and
 * count.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (81 of the moves).
 * @unverified Name from Stadium 1.
 */
BattleAnimEffectSlot* BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(s32 arg0, s32 arg1, s8 arg2, func_unk_D_8140E724 arg3, ParticleDescriptor* arg4, s16 arg5,
                              s16 arg6, u8 arg7, u8 arg8, u8 arg9, u8 argA) {
    return BattleAnim_CreateEffectSlot(arg0, arg1, arg2, arg3, arg4, gBattleAnimCurrentOwner, arg5, arg6, arg7, arg8, arg9, argA);
}

/**
 * Queues a global tint color fade, after arg0 frames, using fade parameter arg1 and
 * color arg2.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (83 of the moves).
 * @unverified Name from Stadium 1.
 */
BattleAnimEffectSlot* BattleAnim_SpawnGlobalTintColorFadeDetach(s32 arg0, s16 arg1, u8 arg2) {
    return BattleAnim_CreateEffectSlot(arg0, 0, 1, BattleAnim_CallbackGlobalTintColorFadeDetach, &gDefaultParticleDescriptor, NULL, 0, arg1, 0x16, 0, arg2, 0);
}

/**
 * Seen in play (2026-11-13) (unattended Free Battle in which every Pokémon knows only Metronome, 70
 * turns): ran.
 * @unverified Name from Stadium 1.
 */
BattleAnimEffectSlot* BattleAnim_SpawnWhiteHueChange(s32 arg0, s16 arg1, s16 arg2, u8 arg3, u8 arg4) {
    return BattleAnim_CreateEffectSlot(arg0, 0, 1, BattleAnim_RunWhiteHueChange, &gBattleAnimParticleDescriptors[37], NULL, arg1, arg2, 0x16, arg4, arg3, 0);
}

/**
 * Queues a full-screen color overlay (descriptor 37) after arg0 frames that starts at
 * full alpha, holds, then fades out.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (13 of the moves).
 * @unverified Name from Stadium 1.
 */
BattleAnimEffectSlot* BattleAnim_SpawnDescriptor25AlphaHoldFadeOutFullAlpha(s32 arg0, s16 arg1, s16 arg2, u8 arg3) {
    return BattleAnim_CreateEffectSlot(arg0, 0, 1, BattleAnim_RunFullScreenHueChange, &gBattleAnimParticleDescriptors[37], NULL, arg1, arg2, 0x16, 0xFF, arg3, 0);
}

/**
 * Queues a full-screen color overlay (descriptor 37) after arg0 frames that starts at
 * alpha arg4, holds, then fades out.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (15 of the moves).
 * @unverified Name from Stadium 1.
 */
BattleAnimEffectSlot* BattleAnim_SpawnDescriptor25AlphaHoldFadeOut(s32 arg0, s16 arg1, s16 arg2, u8 arg3, u8 arg4) {
    return BattleAnim_CreateEffectSlot(arg0, 0, 1, BattleAnim_RunFullScreenHueChange, &gBattleAnimParticleDescriptors[37], NULL, arg1, arg2, 0x16, arg4, arg3, 0);
}

/**
 * Repeating version of BattleAnim_SpawnDescriptor25AlphaHoldFadeOut: runs arg2 times,
 * arg1 frames apart.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal or j,
 * no pointer word, no lui/addiu pair in any fragment), so play cannot reach it.
 * @unverified Name from Stadium 1.
 */
BattleAnimEffectSlot* BattleAnim_SpawnDescriptor25AlphaHoldFadeOutRepeating(s32 arg0, s32 arg1, s8 arg2, s16 arg3, s16 arg4, u8 arg5, u8 arg6) {
    return BattleAnim_CreateEffectSlot(arg0, arg1, arg2, BattleAnim_RunFullScreenHueChange, &gBattleAnimParticleDescriptors[37], NULL, arg3, arg4, 0x16, arg6, arg5, 0);
}

/**
 * Queues an overlay over the screen and the Pokémon (descriptor 37) after arg0 frames
 * that fades in to full alpha and holds.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (2 of the moves).
 * @unverified Name from Stadium 1.
 */
BattleAnimEffectSlot* BattleAnim_SpawnDescriptor25AlphaFadeInHoldFullAlpha(s32 arg0, s16 arg1, s16 arg2, u8 arg3) {
    return BattleAnim_CreateEffectSlot(arg0, 0, 1, BattleAnim_RunPokemonAndFullScreenHueChange, &gBattleAnimParticleDescriptors[37], NULL, arg1, arg2, 0x16, 0xFF, arg3, 0);
}

/**
 * Queues an overlay over the screen and the Pokémon (descriptor 37) after arg0 frames
 * that fades in to alpha arg4 and holds.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (3 of the moves).
 * @unverified Name from Stadium 1.
 */
BattleAnimEffectSlot* BattleAnim_SpawnDescriptor25AlphaFadeInHold(s32 arg0, s16 arg1, s16 arg2, u8 arg3, u8 arg4) {
    return BattleAnim_CreateEffectSlot(arg0, 0, 1, BattleAnim_RunPokemonAndFullScreenHueChange, &gBattleAnimParticleDescriptors[37], NULL, arg1, arg2, 0x16, arg4, arg3, 0);
}

/**
 * Repeating version of BattleAnim_SpawnDescriptor25AlphaFadeInHold: runs arg2 times,
 * arg1 frames apart.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal or j,
 * no pointer word, no lui/addiu pair in any fragment), so play cannot reach it.
 * @unverified Name from Stadium 1.
 */
BattleAnimEffectSlot* BattleAnim_SpawnDescriptor25AlphaFadeInHoldRepeating(s32 arg0, s32 arg1, s8 arg2, s16 arg3, s16 arg4, u8 arg5, u8 arg6) {
    return BattleAnim_CreateEffectSlot(arg0, arg1, arg2, BattleAnim_RunPokemonAndFullScreenHueChange, &gBattleAnimParticleDescriptors[37], NULL, arg3, arg4, 0x16, arg6, arg5, 0);
}

/**
 * Queues a full-alpha overlay (descriptor 37) after arg0 frames that holds for a time and
 * then detaches without fading.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal or j,
 * no pointer word, no lui/addiu pair in any fragment), so play cannot reach it.
 * @unverified Name from Stadium 1.
 */
BattleAnimEffectSlot* BattleAnim_SpawnDescriptor25AlphaHoldDetachFullAlpha(s32 arg0, s16 arg1, u8 arg2) {
    return BattleAnim_CreateEffectSlot(arg0, 0, 1, BattleAnim_CallbackDescriptor25AlphaHoldDetach, &gBattleAnimParticleDescriptors[37], NULL, arg1, 0, 0x16, 0xFF, arg2, 0);
}

/**
 * Queues an overlay (descriptor 37) after arg0 frames that holds at a given alpha and
 * then detaches without fading.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal or j,
 * no pointer word, no lui/addiu pair in any fragment), so play cannot reach it.
 * @unverified Name from Stadium 1.
 */
BattleAnimEffectSlot* BattleAnim_SpawnDescriptor25AlphaHoldDetach(s32 arg0, s16 arg1, u8 arg2, u8 arg3) {
    return BattleAnim_CreateEffectSlot(arg0, 0, 1, BattleAnim_CallbackDescriptor25AlphaHoldDetach, &gBattleAnimParticleDescriptors[37], NULL, arg1, 0, 0x16, arg3, arg2, 0);
}

/**
 * Repeating version of BattleAnim_SpawnDescriptor25AlphaHoldDetach: runs arg2 times, arg1
 * frames apart.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal or j,
 * no pointer word, no lui/addiu pair in any fragment), so play cannot reach it.
 * @unverified Name from Stadium 1.
 */
BattleAnimEffectSlot* BattleAnim_SpawnDescriptor25AlphaHoldDetachRepeating(s32 arg0, s32 arg1, s8 arg2, s16 arg3, u8 arg4, u8 arg5) {
    return BattleAnim_CreateEffectSlot(arg0, arg1, arg2, BattleAnim_CallbackDescriptor25AlphaHoldDetach, &gBattleAnimParticleDescriptors[37], NULL, arg3, 0, 0x16, arg5, arg4, 0);
}

/**
 * Queues a palette-colored overlay (descriptor 37) after arg0 frames that fades out.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal or j,
 * no pointer word, no lui/addiu pair in any fragment), so play cannot reach it.
 * @unverified Name from Stadium 1.
 */
BattleAnimEffectSlot* BattleAnim_SpawnDescriptor25PaletteFadeOut(s32 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4) {
    return BattleAnim_CreateEffectSlot(arg0, 0, 1, BattleAnim_CallbackDescriptor25PaletteFadeOut, &gBattleAnimParticleDescriptors[37], NULL, arg1, arg2, 0x16, arg4, arg3, 0);
}

/**
 * Queues a palette-colored overlay (descriptor 37) after arg0 frames that fades in.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal or j,
 * no pointer word, no lui/addiu pair in any fragment), so play cannot reach it.
 * @unverified Name from Stadium 1.
 */
BattleAnimEffectSlot* BattleAnim_SpawnDescriptor25PaletteFadeIn(s32 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4) {
    return BattleAnim_CreateEffectSlot(arg0, 0, 1, BattleAnim_CallbackDescriptor25PaletteFadeIn, &gBattleAnimParticleDescriptors[37], NULL, arg1, arg2, 0x16, arg4, arg3, 0);
}

/**
 * Queues a tint ramp on the current owner's model after arg0 frames.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (28 of the moves).
 * @unverified Name from Stadium 1.
 */
BattleAnimEffectSlot* BattleAnim_SpawnOwnerModelTintRampDetach(s32 arg0, u8 arg1, s16 arg2, s16 arg3, s16 arg4) {
    return BattleAnim_CreateEffectSlot(arg0, 0, 1, BattleAnim_CallbackOwnerModelTintRampDetach, &gDefaultParticleDescriptor, gBattleAnimCurrentOwner, arg2, arg4, 0x1A, arg3, arg1, 0);
}

/**
 * Queues a pulsing tint (the user hue change) on the current owner's model after arg0
 * frames.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (17 of the moves).
 * @unverified Name from Stadium 1.
 */
BattleAnimEffectSlot* BattleAnim_SpawnOwnerModelTintPulseDetach(s32 arg0, s16 arg1, u8 arg2, s16 arg3, s16 arg4, s16 arg5) {
    return BattleAnim_CreateEffectSlot(arg0, 0, 1, BattleAnim_RunUserHueChange, &gDefaultParticleDescriptor, gBattleAnimCurrentOwner, arg1, arg5, 0x1A, arg4, arg2, arg3);
}

/**
 * Queues a tint on the current owner's model after arg0 frames that holds and then fades.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal or j,
 * no pointer word, no lui/addiu pair in any fragment), so play cannot reach it.
 * @unverified Name from Stadium 1.
 */
BattleAnimEffectSlot* BattleAnim_SpawnOwnerModelTintHoldFadeDetach(s32 arg0, s16 arg1, u8 arg2, s16 arg3, s16 arg4) {
    return BattleAnim_CreateEffectSlot(arg0, 0, 1, BattleAnim_CallbackOwnerModelTintHoldFadeDetach, &gDefaultParticleDescriptor, gBattleAnimCurrentOwner, arg1, arg4, 0x1A, 0, arg2, arg3);
}

/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Hydro Pump, Bubble Beam, Hyper Beam, Metronome, Egg Bomb, Waterfall, Sky Attack.
 */
BattleAnimEffectSlot* BattleAnim_SpawnBeamBoomWaterfallHueChange(s32 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4) {
    return BattleAnim_CreateEffectSlot(arg0, 0, 1, BattleAnim_CallbackOwnerModelTintPaletteApproachInactive, &gDefaultParticleDescriptor, gBattleAnimCurrentOwner, arg4, arg3, 0x1A, arg2, arg1, 0);
}

/**
 * Queues a tint on the current owner's model after arg0 frames that approaches a palette
 * color and then stops.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (2 of the moves).
 * @unverified Name from Stadium 1.
 */
BattleAnimEffectSlot* BattleAnim_SpawnOwnerModelTintPaletteApproachInactiveAlt(s32 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4) {
    return BattleAnim_CreateEffectSlot(arg0, 0, 1, BattleAnim_CallbackOwnerModelTintPaletteApproachInactive, &gDefaultParticleDescriptor, gBattleAnimCurrentOwner, arg4, arg3, 0x1A, arg2, arg1, 0);
}

/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Ice Beam, Blizzard.
 */
BattleAnimEffectSlot* BattleAnim_SpawnIceBeamBlizzardHitHueChange(s32 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5) {
    return BattleAnim_CreateEffectSlot(arg0, 0, 1, BattleAnim_RunIceBeamBlizzardHitHueChange, &gDefaultParticleDescriptor, gBattleAnimCurrentOwner, arg4, arg3, 0x1A, arg2, arg1, arg5);
}

/**
 * Queues the Ice Beam/Blizzard hit hue change on the current owner's model after arg0
 * frames.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal or j,
 * no pointer word, no lui/addiu pair in any fragment), so play cannot reach it.
 * @unverified Name from Stadium 1.
 */
BattleAnimEffectSlot* BattleAnim_SpawnOwnerModelTintPaletteCycleVariant(s32 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5) {
    return BattleAnim_CreateEffectSlot(arg0, 0, 1, BattleAnim_RunIceBeamBlizzardHitHueChange, &gDefaultParticleDescriptor, gBattleAnimCurrentOwner, arg4, arg3, 0x1A, arg2, arg1, arg5);
}

/**
 * Seen in play (2026-11-13) (unattended Free Battle in which every Pokémon knows only Metronome, 40
 * turns): ran.
 * @unverified Name from Stadium 1.
 */
BattleAnimEffectSlot* BattleAnim_SpawnDrainFlameHueChange(s32 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5) {
    return BattleAnim_CreateEffectSlot(arg0, 0, 1, BattleAnim_CallbackOwnerModelTintPaletteFade, &gDefaultParticleDescriptor, gBattleAnimCurrentOwner, arg4, arg3, 0x1A, arg2, arg1, arg5);
}

/**
 * Queues a tint on the current owner's model after arg0 frames that cycles through random
 * palette colors.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal or j,
 * no pointer word, no lui/addiu pair in any fragment), so play cannot reach it.
 * @unverified Name from Stadium 1.
 */
BattleAnimEffectSlot* BattleAnim_SpawnOwnerModelTintRandomPaletteCycle(s32 arg0, s16 arg1, u8 arg2) {
    return BattleAnim_CreateEffectSlot(arg0, 0, 1, BattleAnim_CallbackOwnerModelTintRandomPaletteCycle, &gDefaultParticleDescriptor, gBattleAnimCurrentOwner, 0, arg1, 0x1A, arg2, 0, 0);
}

/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Psybeam, Aurora Beam.
 */
BattleAnimEffectSlot* BattleAnim_SpawnRainbowHueChange(s32 arg0, s16 arg1, s16 arg2, u8 arg3) {
    return BattleAnim_CreateEffectSlot(arg0, 0, 1, BattleAnim_RunRainbowHueChange, &gDefaultParticleDescriptor, gBattleAnimCurrentOwner, arg1, arg2, 0x1A, arg3, 0, 0);
}

/**
 * Seen in play (2026-11-13) (tour of menus and a COM battle): ran in the battle opening and a
 * switch in battle.
 * @unverified Name from Stadium 1.
 */
BattleAnimEffectSlot* BattleAnim_SpawnInvisibility(s32 arg0, s16 arg1, s16 arg2, s16 arg3) {
    return BattleAnim_CreateEffectSlot(arg0, 0, 1, BattleAnim_CallbackOwnerModelAlphaFade, &gDefaultParticleDescriptor, gBattleAnimCurrentOwner, arg1, arg3, 0x1A, arg2, 0, 0);
}

/**
 * Queues an alpha fade of the current owner's model after arg0 frames, starting from
 * full alpha.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal or j,
 * no pointer word, no lui/addiu pair in any fragment), so play cannot reach it.
 * @unverified Name from Stadium 1.
 */
BattleAnimEffectSlot* BattleAnim_SpawnOwnerModelAlphaFadeFullPreset(s32 arg0) {
    return BattleAnim_CreateEffectSlot(arg0, 0, 1, BattleAnim_CallbackOwnerModelAlphaFade, &gDefaultParticleDescriptor, gBattleAnimCurrentOwner, 0xFF, 0xFF, 0x1A, 0xFF, 0, 0);
}

/**
 * Queues an alpha fade of the current owner's model after arg0 frames, starting from
 * zero alpha.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (2 of the moves).
 * @unverified Name from Stadium 1.
 */
BattleAnimEffectSlot* BattleAnim_SpawnOwnerModelAlphaFadeZeroStartPreset(s32 arg0) {
    return BattleAnim_CreateEffectSlot(arg0, 0, 1, BattleAnim_CallbackOwnerModelAlphaFade, &gDefaultParticleDescriptor, gBattleAnimCurrentOwner, 0, 0xFF, 0x1A, 0, 0, 0);
}

/**
 * Queues a kind-23 effect slot after arg0 frames, which sets effect state flag arg1 when
 * it runs.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (25 of the moves).
 * @unverified Name from Stadium 1.
 */
BattleAnimEffectSlot* BattleAnim_SpawnCategory17MarkerSlot(s32 arg0, u8 arg1) {
    return BattleAnim_CreateEffectSlot(arg0, 0, 1, NULL, NULL, 0, 0, 0, 0x17, arg1, 0, 0);
}

/**
 * Queues a kind-25 effect slot for the current owner after arg0 frames, which queues
 * effect list 9 with value arg1 when it runs.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (1 of the moves).
 * @unverified Name from Stadium 1.
 */
BattleAnimEffectSlot* BattleAnim_SpawnCategory19MarkerSlot(s32 arg0, u8 arg1) {
    return BattleAnim_CreateEffectSlot(arg0, 0, 1, NULL, NULL, gBattleAnimCurrentOwner, 0, 0, 0x19, arg1, 0, 0);
}
