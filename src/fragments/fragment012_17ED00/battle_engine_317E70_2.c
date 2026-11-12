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
void BattleAnim_SpawnStandardParticles(BattleAnimEffectSlot* arg0);
void BattleAnim_SpawnBatchedParticles(BattleAnimEffectSlot* arg0);
void BattleAnim_CleanupEffectsRetainingCategories47(void);
void BattleAnim_CleanupEffectsRetainingCategory4(void);
void BattleAnim_ClearEffectCallbacks(void);
void BattleAnim_SetEffectStateFlag(s32 arg0);
Particle* Particle_Alloc(void);
s32 Particle_CountActive(void);
s32 Particle_IsInactive(Particle* arg0);
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
 * @unverified Name was previously used only by callers of this address; the definition was still func_. Comment from Stadium 1.
 */
void Particle_ResetDefaults(Particle* arg0) {
    Particle_InitLifecycle(arg0);
    Particle_SetPosition(arg0, 0.0f, 0.0f, 0.0f);
    Particle_SetOrigin(arg0, 0.0f, 0.0f, 0.0f);
    Particle_SetVelocity(arg0, 0.0f, 0.0f, 0.0f);
    Particle_SetVelocityTarget(arg0, 0.0f, 0.0f, 0.0f);
    Particle_SetVelocityImpulse(arg0, 0.0f, 0.0f, 0.0f);
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

Particle* Particle_Alloc(void) {
    s32 i;
    s32 var_v0 = gParticlePoolIndex;
    Particle* var_a0 = &gParticlePool[var_v0];

    for (i = 0; i < 0x12C; i++) {
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

void func_82139BE8(s8 *arg0) {
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

void BattleAnim_FreeEffectSlot(BattleAnimEffectSlot* arg0) {
    arg0->unk_0E = 0;
    arg0->unk_15 = 0;
    arg0->unk_14 = 0;
    arg0->unk_0C = arg0->unk_0E;
}

Particle* Particle_New(void) {
    return Particle_Alloc();
}

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
void Trade_UpdateBoxSlotBob(ActivePokemon* arg0, Vec3f* arg1);
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
            Trade_UpdateBoxSlotBob(arg0->pokemon, &sp30);
            ParticleMath_MakeXZVectorFromAngle(&sp3C, sp30.x * 25.0f, sp28.y);
            ParticleMath_AddVec3f(&arg0->origin, &sp3C);
            break;

        case 12:
            BattleAnim_GetOwnerBonePosition(arg0->pokemon, 0x64, &arg0->origin);
            BattleScene_GetParticipantModelRotation(arg0->pokemon, &sp28);
            Trade_UpdateBoxSlotBob(arg0->pokemon, &sp30);
            ParticleMath_MakeXZVectorFromAngle(&sp3C, sp30.x * 25.0f, sp28.y + 0x8000);
            ParticleMath_AddVec3f(&arg0->origin, &sp3C);
            break;

        case 13:
            BattleAnim_GetOwnerBonePosition(arg0->pokemon, 0x64, &arg0->origin);
            Trade_UpdateBoxSlotBob(arg0->pokemon, &sp30);
            arg0->origin.y += sp30.y * 25.0f;
            break;

        case 14:
            BattleAnim_GetOwnerBonePosition(arg0->pokemon, 0x64, &arg0->origin);
            Trade_UpdateBoxSlotBob(arg0->pokemon, &sp30);
            arg0->origin.y -= sp30.y * 25.0f;
            if (arg0->origin.y <= 0.0f) {
                arg0->origin.y = 0.0f;
            }
            break;

        case 15:
            BattleAnim_GetOwnerBonePosition(arg0->pokemon, 0x64, &arg0->origin);
            BattleScene_GetParticipantModelRotation(arg0->pokemon, &sp28);
            Trade_UpdateBoxSlotBob(arg0->pokemon, &sp30);
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
            Trade_UpdateBoxSlotBob(arg0->pokemon, &sp30);
            ParticleMath_MakeXZVectorFromAngle(&sp3C, sp30.x * 25.0f, sp28.y);
            ParticleMath_AddVec3f(&arg0->origin, &sp3C);
            break;

        case 30:
            BattleScene_GetParticipantPokeBallPosition(arg0->pokemon, &arg0->origin);
            break;
    }
}

void Trade_UpdateBoxSlotBob(ActivePokemon* arg0, Vec3f* arg1);
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
            Trade_UpdateBoxSlotBob(arg0->pokemon, &sp30);
            ParticleMath_MakeXZVectorFromAngle(&sp3C, sp30.x * 25.0f, sp28.y);
            ParticleMath_AddVec3f(&arg0->origin, &sp3C);
            break;

        case 5:
            BattleAnim_GetOwnerBonePosition(arg0->pokemon, 0x64, &arg0->origin);
            BattleScene_GetParticipantModelRotation(arg0->pokemon, &sp28);
            Trade_UpdateBoxSlotBob(arg0->pokemon, &sp30);
            ParticleMath_MakeXZVectorFromAngle(&sp3C, sp30.x * 25.0f, sp28.y + 0x8000);
            ParticleMath_AddVec3f(&arg0->origin, &sp3C);
            break;

        case 6:
            BattleAnim_GetOwnerBonePosition(arg0->pokemon, 0x64, &arg0->origin);
            Trade_UpdateBoxSlotBob(arg0->pokemon, &sp30);
            arg0->origin.y += sp30.y * 25.0f;
            break;

        case 7:
            BattleAnim_GetOwnerBonePosition(arg0->pokemon, 0x64, &arg0->origin);
            Trade_UpdateBoxSlotBob(arg0->pokemon, &sp30);
            arg0->origin.y -= sp30.y * 25.0f;
            if (arg0->origin.y <= 0.0f) {
                arg0->origin.y = 0.0f;
            }
            break;

        case 8:
            BattleAnim_GetOwnerBonePosition(arg0->pokemon, 0x64, &arg0->origin);
            BattleScene_GetParticipantModelRotation(arg0->pokemon, &sp28);
            Trade_UpdateBoxSlotBob(arg0->pokemon, &sp30);
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
 * @unverified Name was previously used only by callers of this address; the definition was still func_.
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

void func_8213AB88(s8 *arg0) {
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

void func_8213AC3C(s8* arg0) {
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

void BattleAnim_SpawnSingleParticle(BattleAnimEffectSlot* arg0) {
    UNUSED s32 pad; // FAKE: stack padding
    ActivePokemon* sp18 = arg0->unk_08;

    BattleAnim_InitializeParticleFromEffect(Particle_New(), sp18, arg0, 0);
}

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
            BattleAnim_SetEffectStateFlag(arg0->unk_19);
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

s32 Particle_CountActive(void) {
    s32 i;
    s32 var_v1 = 0;
    Particle* ptr = gParticlePool;

    for (i = 0; i < 0x12C; i++, ptr++) {
        if (ptr->allocated != 0) {
            var_v1++;
        }
    }

    return var_v1;
}

s32 Particle_CountActiveAlias(void) {
    return Particle_CountActive();
}

void BattleAnim_ReleaseParticleModel(Particle* arg0) {
    if (arg0->displayObject != NULL) {
        if (Particle_HasFlags(arg0, 0x400) != 0) {
            BattleAnim_FreeParticleDisplayContext(arg0->displayObject);
        } else {
            BattleAnim_FreeOwnerDisplayContext(arg0->displayObject);
        }
    }
}

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
void BattleAnim_ClearEffectCallbacks(void) {
    s32 i;

    for (i = 0; i < 8; i++) {
        if (gBattleAnimEffectUpdateFuncs[i] != NULL) {
            gBattleAnimEffectUpdateFuncs[i] = NULL;
            gBattleAnimEffectDrawFuncs[i] = NULL;
        }
    }
}

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
 * @unverified Name was previously used only by callers of this address; the definition was still func_. Comment from Stadium 1.
 */
void Particle_UpdateFrameCounters(void) {
    D_8219A830 = 1;
}

void BattleAnim_EnableEffectSpawning(void) {
    D_8219A830 = 0;
}

void Particle_UpdateFrameCountersAlias(void) {
    Particle_UpdateFrameCounters();
}

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

void BattleAnim_StopParticlesForOwnerCategory(u8 arg0, ActivePokemon* arg1) {
    s32 i;
    Particle* var_s0 = gParticlePool;

    for (i = 0; i < 300; i++, var_s0++) {
        if ((var_s0->allocated != 0) && (var_s0->unk_CA == 4) && (var_s0->unk_CB == arg0) && (arg1 == var_s0->pokemon)) {
            Particle_AdvanceLifecycle(var_s0);
        }
    }
}

void BattleAnim_ResetSpawnDelay(void) {
    gBattleAnimSpawnDelay = 0;
}

void BattleAnim_SetSpawnDelay(s32 arg0) {
    gBattleAnimSpawnDelay = arg0;
}

void BattleAnim_AddSpawnDelay(s32 arg0) {
    gBattleAnimSpawnDelay += arg0;
}

void BattleAnim_ResetSpawnDelayAlias(void) {
    BattleAnim_ResetSpawnDelay();
}

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

BattleAnimEffectSlot* BattleAnim_CreateEffectSlotForCurrentOwner(s32 arg0, func_unk_D_8140E724 arg1, ParticleDescriptor* arg2, s16 arg3, s16 arg4, u8 arg5,
                              u8 arg6, u8 arg7, u8 arg8) {
    return BattleAnim_CreateEffectSlot(arg0, 0, 1, arg1, arg2, gBattleAnimCurrentOwner, arg3, arg4, arg5, arg6, arg7, arg8);
}

BattleAnimEffectSlot* BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(s32 arg0, s32 arg1, s8 arg2, func_unk_D_8140E724 arg3, ParticleDescriptor* arg4, s16 arg5,
                              s16 arg6, u8 arg7, u8 arg8, u8 arg9, u8 argA) {
    return BattleAnim_CreateEffectSlot(arg0, arg1, arg2, arg3, arg4, gBattleAnimCurrentOwner, arg5, arg6, arg7, arg8, arg9, argA);
}

BattleAnimEffectSlot* BattleAnim_SpawnGlobalTintColorFadeDetach(s32 arg0, s16 arg1, u8 arg2) {
    return BattleAnim_CreateEffectSlot(arg0, 0, 1, BattleAnim_CallbackGlobalTintColorFadeDetach, &gDefaultParticleDescriptor, NULL, 0, arg1, 0x16, 0, arg2, 0);
}

/**
 * @unverified Name from Stadium 1.
 */
BattleAnimEffectSlot* BattleAnim_SpawnWhiteHueChange(s32 arg0, s16 arg1, s16 arg2, u8 arg3, u8 arg4) {
    return BattleAnim_CreateEffectSlot(arg0, 0, 1, BattleAnim_RunWhiteHueChange, &gBattleAnimParticleDescriptors[37], NULL, arg1, arg2, 0x16, arg4, arg3, 0);
}

BattleAnimEffectSlot* BattleAnim_SpawnDescriptor25AlphaHoldFadeOutFullAlpha(s32 arg0, s16 arg1, s16 arg2, u8 arg3) {
    return BattleAnim_CreateEffectSlot(arg0, 0, 1, BattleAnim_RunFullScreenHueChange, &gBattleAnimParticleDescriptors[37], NULL, arg1, arg2, 0x16, 0xFF, arg3, 0);
}

BattleAnimEffectSlot* BattleAnim_SpawnDescriptor25AlphaHoldFadeOut(s32 arg0, s16 arg1, s16 arg2, u8 arg3, u8 arg4) {
    return BattleAnim_CreateEffectSlot(arg0, 0, 1, BattleAnim_RunFullScreenHueChange, &gBattleAnimParticleDescriptors[37], NULL, arg1, arg2, 0x16, arg4, arg3, 0);
}

BattleAnimEffectSlot* BattleAnim_SpawnDescriptor25AlphaHoldFadeOutRepeating(s32 arg0, s32 arg1, s8 arg2, s16 arg3, s16 arg4, u8 arg5, u8 arg6) {
    return BattleAnim_CreateEffectSlot(arg0, arg1, arg2, BattleAnim_RunFullScreenHueChange, &gBattleAnimParticleDescriptors[37], NULL, arg3, arg4, 0x16, arg6, arg5, 0);
}

BattleAnimEffectSlot* BattleAnim_SpawnDescriptor25AlphaFadeInHoldFullAlpha(s32 arg0, s16 arg1, s16 arg2, u8 arg3) {
    return BattleAnim_CreateEffectSlot(arg0, 0, 1, BattleAnim_RunPokemonAndFullScreenHueChange, &gBattleAnimParticleDescriptors[37], NULL, arg1, arg2, 0x16, 0xFF, arg3, 0);
}

BattleAnimEffectSlot* BattleAnim_SpawnDescriptor25AlphaFadeInHold(s32 arg0, s16 arg1, s16 arg2, u8 arg3, u8 arg4) {
    return BattleAnim_CreateEffectSlot(arg0, 0, 1, BattleAnim_RunPokemonAndFullScreenHueChange, &gBattleAnimParticleDescriptors[37], NULL, arg1, arg2, 0x16, arg4, arg3, 0);
}

BattleAnimEffectSlot* BattleAnim_SpawnDescriptor25AlphaFadeInHoldRepeating(s32 arg0, s32 arg1, s8 arg2, s16 arg3, s16 arg4, u8 arg5, u8 arg6) {
    return BattleAnim_CreateEffectSlot(arg0, arg1, arg2, BattleAnim_RunPokemonAndFullScreenHueChange, &gBattleAnimParticleDescriptors[37], NULL, arg3, arg4, 0x16, arg6, arg5, 0);
}

BattleAnimEffectSlot* BattleAnim_SpawnDescriptor25AlphaHoldDetachFullAlpha(s32 arg0, s16 arg1, u8 arg2) {
    return BattleAnim_CreateEffectSlot(arg0, 0, 1, BattleAnim_CallbackDescriptor25AlphaHoldDetach, &gBattleAnimParticleDescriptors[37], NULL, arg1, 0, 0x16, 0xFF, arg2, 0);
}

BattleAnimEffectSlot* BattleAnim_SpawnDescriptor25AlphaHoldDetach(s32 arg0, s16 arg1, u8 arg2, u8 arg3) {
    return BattleAnim_CreateEffectSlot(arg0, 0, 1, BattleAnim_CallbackDescriptor25AlphaHoldDetach, &gBattleAnimParticleDescriptors[37], NULL, arg1, 0, 0x16, arg3, arg2, 0);
}

BattleAnimEffectSlot* BattleAnim_SpawnDescriptor25AlphaHoldDetachRepeating(s32 arg0, s32 arg1, s8 arg2, s16 arg3, u8 arg4, u8 arg5) {
    return BattleAnim_CreateEffectSlot(arg0, arg1, arg2, BattleAnim_CallbackDescriptor25AlphaHoldDetach, &gBattleAnimParticleDescriptors[37], NULL, arg3, 0, 0x16, arg5, arg4, 0);
}

BattleAnimEffectSlot* BattleAnim_SpawnDescriptor25PaletteFadeOut(s32 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4) {
    return BattleAnim_CreateEffectSlot(arg0, 0, 1, BattleAnim_CallbackDescriptor25PaletteFadeOut, &gBattleAnimParticleDescriptors[37], NULL, arg1, arg2, 0x16, arg4, arg3, 0);
}

BattleAnimEffectSlot* BattleAnim_SpawnDescriptor25PaletteFadeIn(s32 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4) {
    return BattleAnim_CreateEffectSlot(arg0, 0, 1, BattleAnim_CallbackDescriptor25PaletteFadeIn, &gBattleAnimParticleDescriptors[37], NULL, arg1, arg2, 0x16, arg4, arg3, 0);
}

BattleAnimEffectSlot* BattleAnim_SpawnOwnerModelTintRampDetach(s32 arg0, u8 arg1, s16 arg2, s16 arg3, s16 arg4) {
    return BattleAnim_CreateEffectSlot(arg0, 0, 1, BattleAnim_CallbackOwnerModelTintRampDetach, &gDefaultParticleDescriptor, gBattleAnimCurrentOwner, arg2, arg4, 0x1A, arg3, arg1, 0);
}

BattleAnimEffectSlot* BattleAnim_SpawnOwnerModelTintPulseDetach(s32 arg0, s16 arg1, u8 arg2, s16 arg3, s16 arg4, s16 arg5) {
    return BattleAnim_CreateEffectSlot(arg0, 0, 1, BattleAnim_RunUserHueChange, &gDefaultParticleDescriptor, gBattleAnimCurrentOwner, arg1, arg5, 0x1A, arg4, arg2, arg3);
}

BattleAnimEffectSlot* BattleAnim_SpawnOwnerModelTintHoldFadeDetach(s32 arg0, s16 arg1, u8 arg2, s16 arg3, s16 arg4) {
    return BattleAnim_CreateEffectSlot(arg0, 0, 1, BattleAnim_CallbackOwnerModelTintHoldFadeDetach, &gDefaultParticleDescriptor, gBattleAnimCurrentOwner, arg1, arg4, 0x1A, 0, arg2, arg3);
}

/**
 * @unverified Name from Stadium 1.
 */
BattleAnimEffectSlot* BattleAnim_SpawnBeamBoomWaterfallHueChange(s32 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4) {
    return BattleAnim_CreateEffectSlot(arg0, 0, 1, BattleAnim_CallbackOwnerModelTintPaletteApproachInactive, &gDefaultParticleDescriptor, gBattleAnimCurrentOwner, arg4, arg3, 0x1A, arg2, arg1, 0);
}

BattleAnimEffectSlot* BattleAnim_SpawnOwnerModelTintPaletteApproachInactiveAlt(s32 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4) {
    return BattleAnim_CreateEffectSlot(arg0, 0, 1, BattleAnim_CallbackOwnerModelTintPaletteApproachInactive, &gDefaultParticleDescriptor, gBattleAnimCurrentOwner, arg4, arg3, 0x1A, arg2, arg1, 0);
}

/**
 * @unverified Name from Stadium 1.
 */
BattleAnimEffectSlot* BattleAnim_SpawnIceBeamBlizzardHitHueChange(s32 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5) {
    return BattleAnim_CreateEffectSlot(arg0, 0, 1, BattleAnim_RunIceBeamBlizzardHitHueChange, &gDefaultParticleDescriptor, gBattleAnimCurrentOwner, arg4, arg3, 0x1A, arg2, arg1, arg5);
}

BattleAnimEffectSlot* BattleAnim_SpawnOwnerModelTintPaletteCycleVariant(s32 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5) {
    return BattleAnim_CreateEffectSlot(arg0, 0, 1, BattleAnim_RunIceBeamBlizzardHitHueChange, &gDefaultParticleDescriptor, gBattleAnimCurrentOwner, arg4, arg3, 0x1A, arg2, arg1, arg5);
}

/**
 * @unverified Name from Stadium 1.
 */
BattleAnimEffectSlot* BattleAnim_SpawnDrainFlameHueChange(s32 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5) {
    return BattleAnim_CreateEffectSlot(arg0, 0, 1, BattleAnim_CallbackOwnerModelTintPaletteFade, &gDefaultParticleDescriptor, gBattleAnimCurrentOwner, arg4, arg3, 0x1A, arg2, arg1, arg5);
}

BattleAnimEffectSlot* BattleAnim_SpawnOwnerModelTintRandomPaletteCycle(s32 arg0, s16 arg1, u8 arg2) {
    return BattleAnim_CreateEffectSlot(arg0, 0, 1, BattleAnim_CallbackOwnerModelTintRandomPaletteCycle, &gDefaultParticleDescriptor, gBattleAnimCurrentOwner, 0, arg1, 0x1A, arg2, 0, 0);
}

/**
 * @unverified Name from Stadium 1.
 */
BattleAnimEffectSlot* BattleAnim_SpawnRainbowHueChange(s32 arg0, s16 arg1, s16 arg2, u8 arg3) {
    return BattleAnim_CreateEffectSlot(arg0, 0, 1, BattleAnim_RunRainbowHueChange, &gDefaultParticleDescriptor, gBattleAnimCurrentOwner, arg1, arg2, 0x1A, arg3, 0, 0);
}

/**
 * @unverified Name from Stadium 1.
 */
BattleAnimEffectSlot* BattleAnim_SpawnInvisibility(s32 arg0, s16 arg1, s16 arg2, s16 arg3) {
    return BattleAnim_CreateEffectSlot(arg0, 0, 1, BattleAnim_CallbackOwnerModelAlphaFade, &gDefaultParticleDescriptor, gBattleAnimCurrentOwner, arg1, arg3, 0x1A, arg2, 0, 0);
}

BattleAnimEffectSlot* BattleAnim_SpawnOwnerModelAlphaFadeFullPreset(s32 arg0) {
    return BattleAnim_CreateEffectSlot(arg0, 0, 1, BattleAnim_CallbackOwnerModelAlphaFade, &gDefaultParticleDescriptor, gBattleAnimCurrentOwner, 0xFF, 0xFF, 0x1A, 0xFF, 0, 0);
}

BattleAnimEffectSlot* BattleAnim_SpawnOwnerModelAlphaFadeZeroStartPreset(s32 arg0) {
    return BattleAnim_CreateEffectSlot(arg0, 0, 1, BattleAnim_CallbackOwnerModelAlphaFade, &gDefaultParticleDescriptor, gBattleAnimCurrentOwner, 0, 0xFF, 0x1A, 0, 0, 0);
}

BattleAnimEffectSlot* BattleAnim_SpawnCategory17MarkerSlot(s32 arg0, u8 arg1) {
    return BattleAnim_CreateEffectSlot(arg0, 0, 1, NULL, NULL, 0, 0, 0, 0x17, arg1, 0, 0);
}

BattleAnimEffectSlot* BattleAnim_SpawnCategory19MarkerSlot(s32 arg0, u8 arg1) {
    return BattleAnim_CreateEffectSlot(arg0, 0, 1, NULL, NULL, gBattleAnimCurrentOwner, 0, 0, 0x19, arg1, 0, 0);
}
