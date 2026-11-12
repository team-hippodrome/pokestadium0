/* Fixed-layout split; original translation-unit boundaries remain unconfirmed. */
#include "battle_engine_32B680_3.h"

void BattleAnim_InitModelAnimationSlot(Particle* arg0, s16 arg1) {
    Vec3f sp24;

    arg0->displayObject = BattleAnim_AllocOwnerDisplayContext(arg0);

    if (arg0->displayObject != NULL) {
        BattleAnim_InitModelWithAnim(arg0->displayObject, 0x21, 0x22);
        Particle_Field1C_SetScaled_0B938(arg0, 0.2f);
        BattleAnim_ApplyModelSpeciesOffset(arg0);
        Vec3f_SetComponentsDuplicate(&sp24, (arg1 * 5.0f * 2) + -10.0f, 5.0f, 10.0f);
        Particle_AddPositionRotatedVectorByYaw(arg0, sp24);

        switch (arg1) {
            case 0:
                Particle_Field94_SetZ_0A2CC(arg0, 0x1400);
                break;

            case 1:
                Particle_Field38_AddYScaled_08E90(arg0, 2.0f);
                Particle_Field94_SetZ_0A2CC(arg0, 0);
                break;

            case 2:
                Particle_Field94_SetZ_0A2CC(arg0, -0x1400);
                break;
        }

        Particle_AdvanceLifecycle(arg0);
    } else {
        Particle_DisableAndDetach(arg0);
    }
}

void BattleAnim_CallbackStartEffects12And129DelayedModelAnimWait(Particle* arg0) {
    s16 sp26 = Particle_FieldAC_GetS16_0C038(arg0);

    switch (arg0->unk_B2) {
        case 1:
            Particle_FieldA6_SetS16_0BCA8(arg0, sp26 * 8);
            Particle_AdvanceLifecycle(arg0);
            break;

        case 2:
            if (Particle_FieldA6_DecrementToZeroStep1_0BDAC(arg0) != 0) {
                BattleAnim_InitModelAnimationSlot(arg0, sp26);
            }
            break;

        case 3:
            if (ModelAnim_IsFinished(arg0->displayObject) != 0) {
                Particle_AdvanceLifecycle(arg0);
            }
            break;

        case 4:
            Particle_DisableAndDetach(arg0);
            break;
    }
}

/**
 * @unverified Name from Stadium 1.
 */
void BattleAnim_InitializeAmnesiaUse(void) {
    BattleAnim_SpawnCategory17MarkerSlot(0x55, 1);
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_CallbackStartEffects12And129DelayedModelAnimWait, &gDefaultParticleDescriptor, 0x1E, 3, 6, 0, 0, 0);
}

s32 func_82107CF0(s32);
void func_8213D720(s8*, f32);
void func_8213D790(s8*, f32);
void func_82154704(s8* arg0) {
    f32 var_f20 = 0.0f;

    switch (func_82107CF0(M2C_FIELD(arg0, s32*, 0x10))) {
        case 0xF:
            var_f20 = -10.0f;
            break;
        case 0x16:
            var_f20 = -10.0f;
            break;
        case 0x33:
            var_f20 = 10.0f;
            break;
        case 0x3B:
            var_f20 = 15.0f;
            func_8213D644(arg0, 5.0f);
            break;
        case 0x4C:
            var_f20 = -10.0f;
            break;
        case 0x5B:
            var_f20 = -8.0f;
            break;
        case 0x5E:
            var_f20 = -5.0f;
            func_8213D644(arg0, 5.0f);
            break;
        case 0x5F:
            func_8213D790(arg0, 15.0f);
            break;
        case 0x73:
            func_8213D790(arg0, 5.0f);
            var_f20 = -5.0f;
            break;
        case 0x79:
            var_f20 = -8.0f;
            break;
        case 0x7F:
            var_f20 = 15.0f;
            break;
        case 0x80:
            var_f20 = -10.0f;
            break;
        case 0x84:
            var_f20 = 10.0f;
            break;
        case 0x8E:
            var_f20 = -25.0f;
            func_8213D644(arg0, 20.0f);
            break;
        case 0x95:
            func_8213D720(arg0, 5.0f);
            func_8213D644(arg0, 5.0f);
            break;
    }
    func_8213D604(arg0, var_f20);
}

/**
 * Moves: Barrier (use), Light Screen (use), Reflect (use)
 * TODO: Human contributor add screenshot
 * @unverified Name and comment from Stadium 1, matched by code similarity.
 */
void BattleAnim_InitializeScreenMove(void) {
    s32 temp_v0;

    func_8213B560(0, &func_82152FB0, &D_8218E580, 0x1E, 1, 0xB, 0, 0x1E, 0);
    func_8213B464(0xF);
    temp_v0 = func_8213646C();
    switch (temp_v0) {                              /* irregular */
    case 0x70:
        func_8213B5D8(0, 0x10, 8, &func_821624FC, &D_8218E7A0, 0, 4, 0xB, 0, 0x18, 5);
        return;
    case 0x71:
        func_8213B644(0, 0x10, 0x1E);
        func_8213BC7C(0, 0, 8, 0, 0xFF, 0x30);
        func_8213B5D8(0, 0x10, 8, &func_821624FC, &D_8218E7A0, 0, 8, 0xB, 0, 0x17, 5);
        func_8213B6AC(0, 1, 0x20, 8, 0xFF);
        return;
    case 0x73:
        func_8213B644(0, 0x10, 0x1E);
        func_8213BC7C(0, 0, 8, 0, 0xFF, 0x30);
        func_8213B5D8(0, 0x10, 8, &func_821624FC, &D_8218E7A0, 0, 8, 0xB, 0, 0, 5);
        func_8213B6AC(0, 1, 0x20, 8, 0xFF);
        return;
    }
}

void BattleAnim_BuildReflectiveTextureDisplayList(Gfx* arg0, s32 arg1, u16 arg2) {
    BattleAnim_SetupReflectiveCamera();

    switch (BattleAnim_GetQueuedMoveId()) {
        case 0x70:
            gDPPipeSync(arg0++);
            gDPSetPrimColor(arg0++, 0, 0x80, 255, 255, 255, 255);
            gDPSetEnvColor(arg0++, 155, 255, 255, 255);
            break;

        case 0x71:
            gDPPipeSync(arg0++);
            gDPSetPrimColor(arg0++, 0, 0x80, 255, 255, 255, 255);
            gDPSetEnvColor(arg0++, 255, 255, 100, 255);
            break;

        case 0x73:
            gDPPipeSync(arg0++);
            gDPSetPrimColor(arg0++, 0, 0x80, 255, 255, 100, 255);
            gDPSetEnvColor(arg0++, 255, 100, 0, 255);
            break;
    }

    arg0 = BattleAnim_BuildAnimatedTileDisplayList(arg0, arg1, 0x20, 5, 0, 2, 0, 0, 0, 1, 0, 0);

    gSPEndDisplayList(arg0++);
}

void BattleAnim_AllocateReflectiveTextureDisplayList(s32 arg0, arg1_func_84344CE8* arg1) {
    if (arg0 == 2) {
        arg1->unk_18 = Gfx_AllocDisplayList(sizeof(Gfx) * 30);
        BattleAnim_BuildReflectiveTextureDisplayList(arg1->unk_18, arg1->unk_14, D_80060484);
    }
}

/**
 * @unverified Name was previously used only by callers of this address; the definition was still func_.
 */
void BattleAnim_ApplyEffect125ModelScaleOffset(Particle* arg0) {
    UNUSED s32 pad; // FAKE: stack padding
    f32 scale = 1.2f;

    switch (BattleAnim_GetOwnerSpecies(arg0->pokemon)) {
        case 0x3:
            scale = 1.5f;
            break;
        case 0x19:
            scale = 0.6f;
            break;
        case 0x22:
            scale = 1.5f;
            break;
        case 0x33:
            scale = 1.0f;
            break;
        case 0x41:
            scale = 0.9f;
            break;
        case 0x44:
            scale = 1.5f;
            break;
        case 0x7B:
            scale = 1.5f;
            break;
        case 0x82:
            scale = 0.8f;
            break;
        case 0x83:
            scale = 0.8f;
            break;
        case 0x84:
            scale = 0.8f;
            break;
        case 0x87:
            scale = 0.8f;
            break;
        case 0x8E:
            scale = 2.5f;
            break;
        case 0x8F:
            scale = 1.5f;
            break;
        case 0x90:
            scale = 1.5f;
            break;
        case 0x91:
            scale = 2.5f;
            break;
        case 0x92:
            scale = 1.5f;
            break;
    }
    Particle_Field38_AddYScaled_08E90(arg0, 0.0f);
    Particle_Field1C_SetScaled_0B938(arg0, scale);
}

void BattleAnim_InitEffect125Model(Particle* arg0, UNUSED s16 arg1) {
    arg0->displayObject = BattleAnim_AllocOwnerDisplayContext(arg0);
    if (arg0->displayObject != NULL) {
        BattleAnim_InitModelWithAnim(arg0->displayObject, 0x25, 0x26);
        Particle_Field94_AddY_0A594(arg0, -0x8000);
        BattleAnim_ApplyEffect125ModelScaleOffset(arg0);
        Particle_FieldA6_SetS16_0BCA8(arg0, 0x20);
        Particle_AdvanceLifecycle(arg0);
    } else {
        Particle_DisableAndDetach(arg0);
    }
}

void BattleAnim_CallbackStartEffect125ModelBurstEmitter(Particle* arg0) {
    s16 temp_a1 = Particle_FieldAC_GetS16_0C038(arg0);

    switch (arg0->unk_B2) {
        case 1:
            BattleAnim_InitEffect125Model(arg0, temp_a1);
            break;

        case 2:
            if (Particle_FieldA6_DecrementToZeroStep1_0BDAC(arg0) != 0) {
                BattleAnim_EmitParticleBurstWithMetadata(arg0, BattleAnim_RunSparkleHit, &gBattleAnimParticleDescriptors[0x42], 8, 0x18, 3);
                Particle_FieldA6_SetS16_0BCA8(arg0, 0x10);
            }
            break;

        case 3:
            Particle_Field1C_ApproachAndStepState_0B9D0(arg0, 0.0f, 0.05f);
            Particle_PrimAlpha_Approach_0BC2C(arg0, 0, 8);
            break;

        case 4:
            Particle_DisableAndDetach(arg0);
            break;
    }
}

void BattleAnim_BuildEffect125DisplayList(Gfx* arg0, u16 arg1) {
    DisplayObject* tmp = D_8006049C;

    gDPPipeSync(arg0++);

    gDPSetPrimColor(arg0++, 0, 0x80, 255, 255, 255, tmp->lodFraction);

    ParticleGfx_SetAnimatedTileSizeOnList(arg0++, 1, 1, 0x20, 0x20);
    ParticleGfx_SetAnimatedAuxTileSizeOnList(arg0++, 2, 2, 0x20, 0x20);

    gSPEndDisplayList(arg0++);
}

void BattleAnim_AllocateEffect125DisplayList(s32 arg0, arg1_func_84344CE8* arg1) {
    if (arg0 == 2) {
        arg1->unk_18 = Gfx_AllocDisplayList(sizeof(Gfx) * 10);
        BattleAnim_BuildEffect125DisplayList(arg1->unk_18, D_80060484);
    }
}

void func_82155084(void) {
    func_8213B560(0, &func_82154EA4, &D_8218E580, 0x1E, 1, 7, 0, 0, 0);
    func_8213B560(0x14, &func_82144750, &D_8218E580, 0x50, 1, 0, 0, 0x33, 0);
}

void BattleAnim_InitEffect65Overlay(Particle* arg0) {
    s16 sp26;
    u16 sp24;
    u16 sp22;

    sp26 = BattleAnim_GetQueuedMoveId();
    sp24 = 0x17;
    sp22 = 0x8;
    Particle_FieldCA_SetU8_0BECC(arg0, 7);
    Particle_Field1C_SetScaled_0B938(arg0, 1.0f);
    Particle_SetPosition(arg0, 160.0f, 120.0f, 0.0f);

    switch (sp26) {
        case 0x4E:
        case 0x93:
            break;

        case 0x4D:
            sp24 = 0x3B;
            sp22 = 0;
            break;

        case 0x4F:
            sp24 = 0x33;
            break;
    }

    ParticleGfx_RecolorPrim(arg0, sp24);
    ParticleGfx_RecolorEnv(arg0, sp22);
    Particle_SetPrimAlpha(arg0, 0);
    Particle_AdvanceLifecycle(arg0);
}

/**
 * Moves: Poison Powder (use), Sleep Powder (use), Spore (use), Stun Spore (use)
 * TODO: Human contributor add screenshot
 * @unverified Name and comment from Stadium 1.
 */
void BattleAnim_RunSporePowderMoveOverlay(Particle* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            BattleAnim_InitEffect65Overlay(arg0);
            break;

        case 2:
            Particle_PrimAlpha_ApproachAndStepState_0BC5C(arg0, 0xFF, 4);
            break;
    }
}

/**
 * @unverified Name was previously used only by callers of this address; the definition was still func_.
 */
void ParticleEffect_RegisterParticleNodes(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(8, BattleAnim_RunSporePowderMoveOverlay, &gBattleAnimParticleDescriptors[0x32], 0, 1, 0x18, 0, 0, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(8, BattleAnim_RunSporePowderMoveOverlay, &gBattleAnimParticleDescriptors[0x31], 0, 1, 0x18, 0, 0, 0);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0, 3, 0x14, BattleAnim_CallbackStartEffects28And53And65And76Descriptor47AnimatedScaleMotion, &gBattleAnimParticleDescriptors[0x46], 0, 1, 0x10, 0x64, 0, 0);
}

void BattleAnim_InitEffect28Overlay(Particle* arg0) {
    s16 sp26 = Particle_FieldCF_GetS16_0C058(arg0);

    Particle_FieldCA_SetU8_0BECC(arg0, 7);
    Particle_Field1C_SetScaled_0B938(arg0, 1.0f);
    Particle_SetPosition(arg0, 160.0f, 120.0f, 0.0f);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, sp26);
    Particle_SetPrimAlpha(arg0, 0);
    Particle_AdvanceLifecycle(arg0);
}

/**
 * Moves: Haze (use), Mist (use), Poison Gas (use), Smog (use), Smokescreen (use)
 * TODO: Human contributor add screenshot
 * @unverified Name and comment from Stadium 1.
 */
void BattleAnim_RunGasAttack(Particle* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            BattleAnim_InitEffect28Overlay(arg0);
            break;

        case 2:
            Particle_PrimAlpha_ApproachAndStepState_0BC5C(arg0, 0xB4, 8);
            break;
    }
}

void func_821553D0(void) {
    func_8213B560(8, &func_82155380, &D_8218E720, 0, 1, 0x18, 0, 0x1C, 0);
    func_8213B560(0, &func_82163D7C, &D_8218E7B8, 0, 0xF, 0x11, (s32) D_8219A80A, 0, 0);
}

void func_82155464(void) {
    func_8213B560(8, &func_82155380, &D_8218E720, 0, 1, 0x18, 0, 0x1E, 0);
    func_8213B560(0, &func_82163D7C, &D_8218E7B8, 0, 0xF, 0x11, (s32) D_8219A80A, 0, 0);
}

void func_821554F8(void) {
    func_8213B560(8, &func_82155380, &D_8218E720, 0, 1, 0x18, 0, 0x1D, 0);
    func_8213B560(0, &func_82163D7C, &D_8218E7B8, 0, 0xF, 0x11, (s32) D_8219A80A, 0, 0);
}

/**
 * @unverified Name from Stadium 1.
 */
void BattleAnim_SetupLeechSeedUseEffect1(Particle* arg0) {
    Particle_Field1C_SetScaled_0B938(arg0, 0.2f);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, 0xD);
    Particle_SetPrimAlpha(arg0, 0xFF);
    Particle_AdvanceLifecycle(arg0);
}

void func_821555D4(s8 *arg0) {
    s16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_8215558C(arg0);
        break;
    case 2:
        func_8213CCEC(arg0, 0, 7, 1, 2, 0);
        func_82140518(arg0, 0x20, 0x18);
        break;
    case 3:
        func_8213C938(arg0);
        break;
    }
    func_82140228(arg0, 0x3DCCCCCD, 0x3C23D70A);
}

/**
 * @unverified Name from Stadium 1.
 */
void BattleAnim_SetupLeechSeedUseEffect2(Particle* arg0) {
    s16 sp2E = Particle_FieldAC_GetS16_0C038(arg0);

    Particle_Field1C_SetScaled_0B938(arg0, 0.5f);
    Particle_Field74_SetScaled_0AD8C(arg0, 4.5f);
    Particle_Field94_AddVec_0A52C(arg0, ParticleMath_RandomSignedOffset(0x800, -0x3800), ParticleMath_RandomSigned(0x1400), 0);
    Particle_FieldA6_SetS16_0BCA8(arg0, sp2E * 2);
    Particle_DisableRendering(arg0);
    Particle_AdvanceLifecycle(arg0);
}

void BattleAnim_CallbackStartEffect8ModelBurstEmitter(Particle* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            BattleAnim_SetupLeechSeedUseEffect2(arg0);
            break;

        case 2:
            if (Particle_FieldA6_DecrementToZeroStep1AndStepState_0BDD0(arg0) != 0) {
                arg0->displayObject = BattleAnim_AllocOwnerDisplayContext(arg0);
                BattleAnim_InitModel(arg0->displayObject, 0x9F);
                Particle_EnableRendering(arg0);
                Particle_FieldA6_SetS16_0BCA8(arg0, ParticleMath_RandomRange(3));
            }
            break;

        case 3:
            if (Particle_FieldA6_DecrementToZeroStep1AndStepState_0BDD0(arg0) != 0) {
                BattleAnim_EmitParticleBurstWithMetadata(arg0, BattleAnim_RunSparkleHit, &D_8218E798, 1, 0x17, 4);
            }
            break;

        case 4:
            Particle_TickDelayAndAdvanceLifecycle(arg0, 0x1E);
            break;

        case 5:
            Particle_DisableAndDetach(arg0);
            break;
    }

    if (Particle_IsRenderingEnabled(arg0) != 0) {
        Particle_ApproachRotationXTo(arg0, 0x1800, 0x400);
        Particle_AddVelocityFromRotationTemplate1(arg0);
        Particle_Field94_AddZ_0A5B0(arg0, 0x2000);
        BattleAnim_EmitParticleBurst(arg0, func_821555D4, &D_8218E7D0, 1);
    }
}

void BattleAnim_InitEffect31Model(Particle* arg0) {
    arg0->displayObject = BattleAnim_AllocOwnerDisplayContext(arg0);
    if (arg0->displayObject != NULL) {
        BattleAnim_InitModelWithAnim(arg0->displayObject, 0x2B, 0x2C);
        Particle_Field1C_SetScaled_0B938(arg0, 0.25f);
        Particle_Field94_SetY_0A2B8(arg0, ParticleMath_RandomRange(0x10000));
        Particle_AdvanceLifecycle(arg0);
    } else {
        Particle_DisableAndDetach(arg0);
    }
}

void func_821558F4(s8 *arg0) {
    s16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_82140594(arg0, func_82137D74(0x18));
        func_8213C9D0(arg0);
        return;
    case 2:
        if (func_82140690(arg0) != 0) {
            func_82155878(arg0);
            func_8213B560(0, &func_821624FC, &D_8218E798, 0, 1, 0x10, (s32) M2C_FIELD(arg0, u8 *, 0xC9), 0x17, 4);
            return;
        }
        return;
    case 3:
        if (func_8001104C(M2C_FIELD(arg0, s32 *, 0x14)) != 0) {
            func_8213C9D0(arg0);
        }
        break;
    }
}

/**
 * @unverified Name from Stadium 1, matched by code similarity.
 */
void BattleAnim_InitializeLeechSeedUse(void) {
    func_8213B5D8(0, 4, 5, &func_82155724, &D_8218E580, 0, 2, 0x11, (s32) D_8219A80A, 0, 0);
    func_8213B5D8(0, 8, 3, &func_82164AD0, &D_8218E7D0, 0, 1, 0x11, (s32) D_8219A80A, 0x33, 6);
}

/**
 * @unverified Name from Stadium 1.
 */
void BattleAnim_InitializeLeechSeedHit(void) {
    s32 i;
    s32 var_s2 = 0;
    s32 tmp;
    s32 end = gBattleAnimCurrentOwner->displayObject.anchorCount;

    if (end != 0) {
        for (i = 0; i < end; i++) {
            tmp = gBattleAnimCurrentOwner->displayObject.anchors[i].id;
            BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_CallbackMove73EndEffect31SpawnDescriptor42, &gDefaultParticleDescriptor, 0, 1, 0x10, tmp, 0, 0);
            var_s2++;
            if (var_s2 >= 8) {
                break;
            }
        }
    }
}

/**
 * initializes being hit by Pay Day
 * @unverified Name and comment from Stadium 1.
 */
void BattleAnim_InitializePayDayHit(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_InitializeParticleModel, &gDefaultParticleDescriptor, 0, 1, 0xA, 0, 0x22, 0);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(4, 2, 4, BattleAnim_RunSparkleHit, &gBattleAnimParticleDescriptors[0x42], 0, 4, 9, 0, 0x17, 1);
}

void ParticleEffect_DrawSimple(Gfx* arg0, u8* arg1) {
    BattleAnim_SetupReflectiveCamera();
    arg0 = BattleAnim_BuildAnimatedTileDisplayList(arg0, arg1, 0x20, 5, 2, 0, 0, 0, 1, 0, 0, 0);
    gSPEndDisplayList(arg0++);
}

void ParticleEffect_CreateSimpleDL(s32 arg0, arg1_func_84344CE8* arg1) {
    if (arg0 == 2) {
        arg1->unk_18 = Gfx_AllocDisplayList(sizeof(Gfx) * 30);
        ParticleEffect_DrawSimple(arg1->unk_18, arg1->unk_14);
    }
}

/**
 * @unverified Name from Stadium 1.
 */
void BattleAnim_SetupBlizzardHitSpark(Particle* arg0) {
    arg0->displayObject = BattleAnim_AllocParticleDisplayContext(arg0);
    if (arg0->displayObject != NULL) {
        BattleAnim_InitModel(arg0->displayObject, 0x30);
        Particle_SetFlags(arg0, 0x200);
        Particle_SetScale(arg0, 5.3f);
        Particle_SetPrimAlpha(arg0, 0);
        Particle_AdvanceLifecycle(arg0);
    } else {
        Particle_DisableAndDetach(arg0);
    }
}

void func_82155D3C(s8 *arg0) {
    s16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_82155CC0(arg0);
        break;
    case 2:
        func_82140548(arg0, 0xFF, 0x20);
        break;
    }
    if (func_8213C9B0(arg0) != 0) {
        func_8213831C(arg0 + 0x4C, 0x45674000);
    }
}

/**
 * @unverified Name from Stadium 1.
 */
void BattleAnim_SetupBlizzard(Particle* arg0) {
    UNUSED s32 pad[2]; // FAKE: stack padding
    s16 sp26 = Particle_FieldAC_GetS16_0C038(arg0);
    UNUSED s16 pad2; // FAKE: stack padding
    s16 sp22;

    Particle_FieldCE_GetS32_0C040(arg0);
    sp22 = Particle_FieldCF_GetS16_0C058(arg0);
    Particle_FieldA6_SetS16_0BCA8(arg0, sp26 * 2);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, Particle_FieldCF_GetS16_0C058(arg0));
    Particle_Field1C_SetScaled_0B938(arg0, 1.2f);
    Particle_SetScaleSpeed(arg0, 1.0f);
    Particle_SetScaleTarget(arg0, 0.02f);
    Particle_SetRandomVelocityXYZ(arg0, 5, 0xF, 0xF);
    Particle_Field38_AddYScaled_08E90(arg0, 10.0f);
    Particle_Field74_SetScaled_0AD8C(arg0, (ParticleMath_RandomRange(0xA) * 0.5f) + 8.0f);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, sp22);
    Particle_SetPrimAlpha(arg0, 0xC8);
    Particle_FieldAE_SetS16_0BF4C(arg0, 4);
    Particle_DisableRendering(arg0);
    Particle_AdvanceLifecycle(arg0);
}

/**
 * @unverified Name from Stadium 1, matched by code similarity.
 */
void BattleAnim_RunBlizzard(s8 *arg0) {
    s16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_82155DB8(arg0);
        return;
    case 2:
        if (func_821406B4(arg0) != 0) {
            func_8213CB3C(arg0);
            func_82140594(arg0, 4);
            return;
        }
        return;
    case 3:
        func_821402B8(arg0);
        func_8213CCEC(arg0, 1, 7, 1, 2, 0);
        func_8213E6BC(arg0);
        func_82140518(arg0, 0x40, 8);
        return;
    case 4:
        func_8213C930(arg0);
        break;
    }
}

/**
 * initializes using blizzard
 * @unverified Name and comment from Stadium 1, matched by code similarity.
 */
void BattleAnim_InitializeBlizzardUse(void) {
    func_8213B644(0, 0x10, 0x33);
    func_8213B8EC(0, 0xFF, 0x10, 8, 0x96);
    func_8213B560(0, &func_82155D3C, &D_8218E580, 0x1E, 1, 0x14, 0, 0, 0);
}

/**
 * initializes being hit by blizzard
 * @unverified Name and comment from Stadium 1, matched by code similarity.
 */
void BattleAnim_InitializeBlizzardHit(void) {
    func_8213B5D8(0, 8, 3, &func_82152F44, &D_8218E580, 0, 1, 0xC, 0, 0x2A, 0);
    func_8213BE70(4, 8, 0x33, 8, 0xC8, 0x18);
    func_8213B458(4);
    func_8213B5D8(0, 4, 6, &BattleAnim_RunBlizzard, &D_8218E7D0, 0, 4, 0xB, 9, 0x13, 0);
    func_8213B5D8(0, 2, 0xC, &func_821626F4, &D_8218E7A0, 0, 4, 0xB, 9, 0x18, 0xB);
    func_8213B5D8(0, 5, 4, &BattleAnim_RunBlizzardHitUpwardColdAir, &D_8218E650, 0, 6, 0x10, (s32) D_8219A80A, 0x26, 0);
    func_8213B644(0x32, 0x20, 8);
}

void ParticleEffect_DrawNode(Gfx* arg0, s32 arg1, u16 arg2) {
    Particle* temp_v0 = BattleAnim_GetOwnerContextParticle(D_8006049C);

    gDPPipeSync(arg0++);
    gDPSetPrimColor(arg0++, 0, 0x80, 255, 255, 255, temp_v0->prim_a);

    arg0 = BattleAnim_BuildAnimatedTileDisplayListFromStruct(arg0, arg1, 0x40, 6, -4, 0xF, 0, 0, -0xF, 5, 0, 0);

    gSPEndDisplayList(arg0++);
}

void ParticleEffect_CreateNodeDL(s32 arg0, arg1_func_84344CE8* arg1) {
    if (arg0 == 2) {
        arg1->unk_18 = Gfx_AllocDisplayList(sizeof(Gfx) * 30);
        ParticleEffect_DrawNode(arg1->unk_18, arg1->unk_14, D_80060484);
    }
}

void ParticleEffect_DrawNodeVariant(Gfx* arg0, arg1_func_8434E21C* arg1, UNUSED u16 arg2) {
    arg0 = BattleAnim_BuildAnimatedTileDisplayListFromStruct(arg0, arg1, 0x40, 6, -4, 0xF, 0, 0, -5, 5, 0, 0);

    gSPEndDisplayList(arg0++);
}

void ParticleEffect_CreateNodeVariantDL(s32 arg0, arg1_func_84344CE8* arg1) {
    if (arg0 == 2) {
        arg1->unk_18 = Gfx_AllocDisplayList(sizeof(Gfx) * 30);
        ParticleEffect_DrawNodeVariant(arg1->unk_18, arg1->unk_14, D_80060484);
    }
}

void ParticleEffect_DrawSimpleOffsetTileNoCamera(Gfx* arg0, u8* arg1, UNUSED u16 arg2) {
    arg0 = BattleAnim_BuildAnimatedTileDisplayList(arg0, arg1, 0x20, 5, -8, -0x1E, 0, 0, -0xB, -0xA, 0, 0);

    gSPEndDisplayList(arg0++);
}

void ParticleEffect_CreateSimpleOffsetTileNoCameraDL(s32 arg0, arg1_func_84344CE8* arg1) {
    if (arg0 == 2) {
        arg1->unk_18 = Gfx_AllocDisplayList(sizeof(Gfx) * 30);
        ParticleEffect_DrawSimpleOffsetTileNoCamera(arg1->unk_18, arg1->unk_14, D_80060484);
    }
}

void BattleAnim_DefaultEndEffect_Draw(void) {
}

void BattleAnim_InitMove146Model(Particle* arg0) {
    s16 sp26 = Particle_FieldCF_GetS16_0C058(arg0);
    s16 sp24;

    arg0->displayObject = BattleAnim_AllocOwnerDisplayContext(arg0);

    if (arg0->displayObject != NULL) {
        BattleAnim_InitModelWithAnim(arg0->displayObject, 0x31, 0x32);
        Particle_Field1C_SetScaled_0B938(arg0, 0.25f);
        Particle_Field38_SetYScaled_08CA0(arg0, 5.0f);
        switch (sp26) {
            case 0:
                sp24 = 0;
                break;

            case 1:
                sp24 = 0x5555;
                break;

            case 2:
                sp24 = -0x5556;
                break;
        }

        Particle_Field94_AddY_0A594(arg0, sp24);
        Particle_AdvanceLifecycle(arg0);
    } else {
        Particle_DisableAndDetach(arg0);
    }
}

/**
 * @unverified Name from Stadium 1.
 */
void BattleAnim_RunDizzyPunchHitEffect(Particle* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            BattleAnim_InitMove146Model(arg0);
            break;

        case 2:
            if (ModelAnim_IsFinished(arg0->displayObject) != 0) {
                Particle_AdvanceLifecycle(arg0);
            }
            break;

        case 3:
            Particle_DisableAndDetach(arg0);
            break;
    }
}

/**
 * @unverified Name from Stadium 1.
 */
void BattleAnim_InitializeDizzyPunchHit(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_RunDizzyPunchHitEffect, &gDefaultParticleDescriptor, 0x1E, 1, 6, gBattleAnimCurrentAnchor, 0, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_RunDizzyPunchHitEffect, &gDefaultParticleDescriptor, 0x1E, 1, 6, gBattleAnimCurrentAnchor, 1, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_RunDizzyPunchHitEffect, &gDefaultParticleDescriptor, 0x1E, 1, 6, gBattleAnimCurrentAnchor, 2, 0);
}

void BattleAnim_InitEffect49Model(Particle* arg0) {
    s16 sp26 = Particle_FieldCF_GetS16_0C058(arg0);
    u16 sp24;

    switch (BattleAnim_GetQueuedMoveId()) {
        case 0x47:
            sp24 = 0x18;
            break;

        case 0x48:
            sp24 = 0x1F;
            break;

        case 0x8D:
            sp24 = 0x21;
            break;
    }

    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, sp24);

    arg0->displayObject = BattleAnim_AllocOwnerDisplayContext(arg0);
    if (arg0->displayObject != NULL) {
        BattleAnim_InitModel(arg0->displayObject, 0x33);
        if (sp26 == 0) {
            BattleAnim_BindModelAnim(arg0->displayObject, 0x34);
        } else {
            BattleAnim_BindModelAnimReversed(arg0->displayObject, 0x34);
        }
        Particle_Field1C_SetScaled_0B938(arg0, 1.0f);
        Particle_AdvanceLifecycle(arg0);
    } else {
        Particle_DisableAndDetach(arg0);
    }
}

/**
 * @unverified Name was previously used only by callers of this address; the definition was still func_.
 */
void BattleAnim_CallbackEndEffect49Model33Anim34WaitCleanup(Particle* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            func_82156654(arg0);
            break;

        case 2:
            if (func_82136E2C(arg0->displayObject) != 0) {
                Particle_AdvanceLifecycle(arg0);
            }
            break;

        case 3:
            Particle_DisableAndDetach(arg0);
            break;
    }
}

/**
 * @unverified Name was previously used only by callers of this address; the definition was still func_.
 */
void BattleAnim_CallbackEndEffect21ModelAnimWait(Particle* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            func_82156654(arg0);
            break;

        case 2:
            if (ModelAnim_IsFinished(arg0->displayObject) != 0) {
                Particle_AdvanceLifecycle(arg0);
            }
            break;

        case 3:
            Particle_DisableAndDetach(arg0);
            break;
    }
}

void BattleAnim_BuildEffect49DisplayList(Gfx* arg0, UNUSED s32 arg1, UNUSED u16 arg2) {
    Particle* temp_v0 = BattleAnim_GetOwnerContextParticle(D_8006049C);

    gDPPipeSync(arg0++);

    gDPSetPrimColor(arg0++, 0, 0, temp_v0->prim_r, temp_v0->prim_g, temp_v0->prim_b, temp_v0->prim_a);
    gDPSetEnvColor(arg0++, temp_v0->env_r, temp_v0->env_g, temp_v0->env_b, 0);

    gSPEndDisplayList(arg0++);
}

void BattleAnim_AllocateEffect49DisplayList(s32 arg0, arg1_func_84344CE8* arg1) {
    if (arg0 == 2) {
        arg1->unk_18 = Gfx_AllocDisplayList(sizeof(Gfx) * 30);
        BattleAnim_BuildEffect49DisplayList(arg1->unk_18, arg1->unk_14, D_80060484);
    }
}

void ParticleEffect_RegisterColorAnim(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_CallbackEndEffect49Model33Anim34WaitCleanup, &gDefaultParticleDescriptor, 0, 1, 2, gBattleAnimCurrentAnchor, 1, 0);
}

void ParticleEffect_RegisterModeSpecific(void) {
    switch (BattleAnim_GetQueuedMoveId()) {
        case 0x8D:
            BattleAnim_SpawnDrainFlameHueChange(0, 0xA, 0x3E, 2, 0xC8, 0x10);
            break;

        case 0x47:
            BattleAnim_SpawnDrainFlameHueChange(0, 0x35, 0x3E, 2, 0xC8, 0x10);
            break;

        case 0x48:
            BattleAnim_SpawnDrainFlameHueChange(0, 0x27, 0x3E, 2, 0xC8, 0x10);
            break;
    }

    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_CallbackEndEffect21ModelAnimWait, &gDefaultParticleDescriptor, 0, 1, 2, gBattleAnimCurrentAnchor, 0, 0);
}

/**
 * @unverified Name from Stadium 1.
 */
void BattleAnim_SetupFlyUpwardMovementEffect(Particle* arg0) {
    arg0->displayObject = BattleAnim_AllocOwnerDisplayContext(arg0);
    if (arg0->displayObject != NULL) {
        BattleAnim_InitModel(arg0->displayObject, 0x35);
        Particle_Field1C_SetScaled_0B938(arg0, 5.0f);
        Particle_Field38_AddYScaled_08E90(arg0, -100.0f);
        Particle_SetPrimAlpha(arg0, 0);
        Particle_AdvanceLifecycle(arg0);
    } else {
        Particle_DisableAndDetach(arg0);
    }
}

/**
 * Handles the lines that give the impression of upward movement on the first turn of using fly.
 * @unverified Name and comment from Stadium 1.
 */
void BattleAnim_RunFlyUpwardMovementEffect(Particle* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            BattleAnim_SetupFlyUpwardMovementEffect(arg0);
            break;

        case 2:
            Particle_PrimAlpha_ApproachAndStepState_0BC5C(arg0, 0x80, 0x10);
            break;

        case 3:
            Particle_FieldA6_DecrementToZeroStep1AndStepState_0BDD0(arg0);
            break;

        case 4:
            Particle_PrimAlpha_ApproachAndStepState_0BC5C(arg0, 0, 0x20);
            break;
    }
}

/**
 * initializes the first turn of using fly
 * @unverified Name and comment from Stadium 1, matched by code similarity.
 */
void BattleAnim_InitializeFlyUse(void) {
    func_8213B560(0, &func_82156B0C, &D_8218E580, 0xA, 1, 0xA, 0, 0, 0);
}

/**
 * @unverified Name from Stadium 1.
 */
void BattleAnim_InitializeTeleportUse(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_RunFlyUpwardMovementEffect, &gDefaultParticleDescriptor, 0x40, 1, 0xA, 0, 0, 0);
    BattleAnim_SpawnInvisibility(0, 0xFF, 0, 0x10);
    BattleAnim_SpawnInvisibility(0x2D, 0, 0xFF, 0x20);
}

void BattleAnim_BuildEffect63DisplayList(Gfx* arg0, s32 arg1, u16 arg2) {
    UNUSED s32 pad; // FAKE: stack padding
    Particle* sp28 = BattleAnim_GetOwnerContextParticle(D_8006049C);

    ParticleGfx_SetAnimatedTileSizeOnList(arg0++, 1, 0x28, 0x20, 0x20);
    ParticleGfx_SetAnimatedAuxTileSizeOnList(arg0++, -1, 0x1E, 0x20, 0x20);

    gDPPipeSync(arg0++);

    gDPSetPrimColor(arg0++, 0, 0x80, 255, 255, 255, sp28->prim_a);
    gDPSetEnvColor(arg0++, 255, 55, 100, 255);

    gSPEndDisplayList(arg0++);
}

void BattleAnim_AllocateEffect63DisplayList(s32 arg0, arg1_func_84344CE8* arg1) {
    if (arg0 == 2) {
        arg1->unk_18 = Gfx_AllocDisplayList(sizeof(Gfx) * 30);
        BattleAnim_BuildEffect63DisplayList(arg1->unk_18, arg1->unk_14, D_80060484);
    }
}

void BattleAnim_BuildEffect75DisplayList(Gfx* arg0, UNUSED s32 arg1, UNUSED u16 arg2) {
    Particle* temp_v0 = BattleAnim_GetOwnerContextParticle(D_8006049C);

    gDPPipeSync(arg0++);

    gDPSetPrimColor(arg0++, 0, 0x80, 255, 255, 255, temp_v0->prim_a);
    gDPSetEnvColor(arg0++, 255, 255, 100, 255);

    gSPEndDisplayList(arg0++);
}

void BattleAnim_AllocateEffect75DisplayList(s32 arg0, arg1_func_84344CE8* arg1) {
    if (arg0 == 2) {
        arg1->unk_18 = Gfx_AllocDisplayList(sizeof(Gfx) * 30);
        BattleAnim_BuildEffect75DisplayList(arg1->unk_18, arg1->unk_14, D_80060484);
    }
}

void BattleAnim_InitEffects63And75Model(Particle* arg0) {
    s16 sp26 = Particle_FieldCF_GetS16_0C058(arg0);

    arg0->displayObject = BattleAnim_AllocOwnerDisplayContext(arg0);
    if (arg0->displayObject != NULL) {
        if (sp26 == 0) {
            BattleAnim_InitModelWithAnim(arg0->displayObject, 0x36, 0x37);
            Particle_Field1C_SetScaled_0B938(arg0, 0.75f);
        } else {
            BattleAnim_InitModelWithAnim(arg0->displayObject, 0x61, 0x62);
            Particle_Field1C_SetScaled_0B938(arg0, 1.0f);
        }
        Particle_AdvanceLifecycle(arg0);
    } else {
        Particle_DisableAndDetach(arg0);
    }
}

/**
 * @unverified Name was previously used only by callers of this address; the definition was still func_.
 */
void BattleAnim_CallbackStartEffects63And75ModelAnimWait(Particle* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            func_82156E54(arg0);
            break;

        case 2:
            if (ModelAnim_IsFinished(arg0->displayObject) != 0) {
                Particle_AdvanceLifecycle(arg0);
            }
            break;

        case 3:
            Particle_DisableAndDetach(arg0);
            break;
    }
}

void BattleAnim_InitEffects10And50Model(Particle* arg0) {
    u16 sp26 = Particle_FieldCF_GetS16_0C058(arg0);

    arg0->displayObject = BattleAnim_AllocOwnerDisplayContext(arg0);
    if (arg0->displayObject != NULL) {
        BattleAnim_InitModelWithAnim(arg0->displayObject, 0x39, 0x3A);
        Particle_Field1C_SetScaled_0B938(arg0, 0.5f);

        switch (sp26) {
            case 0:
                break;

            case 1:
                Particle_Field38_AddVecScaled_08E18(arg0, -10.0f, 0.0f, 20.0f);
                break;

            case 2:
                Particle_Field38_AddVecScaled_08E18(arg0, 10.0f, 0.0f, -20.0f);
                break;

            case 3:
                Particle_Field38_AddVecScaled_08E18(arg0, 20.0f, 0.0f, -20.0f);
                break;

            case 4:
                Particle_Field38_AddVecScaled_08E18(arg0, -20.0f, 0.0f, 20.0f);
                break;

            case 5:
                Particle_Field38_AddVecScaled_08E18(arg0, 15.0f, 0.0f, -25.0f);
                break;

            case 6:
                Particle_Field38_AddVecScaled_08E18(arg0, 20.0f, 0.0f, 30.0f);
                break;

            case 7:
                Particle_Field38_AddVecScaled_08E18(arg0, 15.0f, 0.0f, -10.0f);
                break;

            case 8:
                Particle_Field1C_SetScaled_0B938(arg0, 1.5f);
                break;
        }
        Particle_SetPrimColor(arg0, 0xFF, 0xFF, 0xFF);
        Particle_AdvanceLifecycle(arg0);
    } else {
        Particle_DisableAndDetach(arg0);
    }
}

/**
 * Moves: Rock Slide (hit), Rock Throw (hit), Strength (hit)
 * TODO: Human contributor add screenshot
 * @unverified Name and comment from Stadium 1, matched by code similarity.
 */
void BattleAnim_RunFallingRock(s8 *arg0) {
    s16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_82156F70(arg0);
        return;
    case 2:
        func_8213CA80(arg0, 0xA);
        return;
    case 3:
        func_82140380(arg0, 0, 0x10);
        func_821403B0(arg0, 0, 0x20);
        if (func_8001104C(M2C_FIELD(arg0, s32 *, 0x14)) != 0) {
            func_8213C9D0(arg0);
            return;
        }
        return;
    case 4:
        func_8213C938(arg0);
        break;
    }
}

void BattleAnim_ApplyEffects63And75SpeciesScaleOffset(Particle* arg0) {
    f32 sp1C = 0.6f;
    f32 sp18 = 0.0f;

    switch (BattleAnim_GetOwnerSpecies(arg0->pokemon)) {
        case 0x3:
            sp1C = 1.0f;
            sp18 = 5.0f;
            break;

        case 0x22:
            sp1C = 1.0f;
            sp18 = 5.0f;
            break;

        case 0x4C:
            sp1C = 0.8f;
            sp18 = 5.0f;
            break;

        case 0x5E:
            sp1C = 0.8f;
            sp18 = 5.0f;
            break;

        case 0x80:
            sp1C = 0.8f;
            sp18 = 10.0f;
            break;

        case 0x82:
            sp18 = 20.0f;
            break;

        case 0x88:
            sp1C = 1.2f;
            sp18 = 10.0f;
            break;

        case 0x8E:
            sp1C = 1.2f;
            sp18 = 20.0f;
            break;

        case 0x91:
            sp1C = 1.2f;
            sp18 = 15.0f;
            break;

        case 0x95:
            sp18 = 10.0f;
            break;
    }

    Particle_Field1C_SetScaled_0B938(arg0, sp1C);
    Particle_Field38_AddXZFromField94YOffset180_08F38(arg0, sp18);
}

void BattleAnim_InitEffects63And75Model38(Particle* arg0) {
    arg0->displayObject = BattleAnim_AllocOwnerDisplayContext(arg0);
    if (arg0->displayObject != NULL) {
        BattleAnim_InitModel(arg0->displayObject, 0x38);
        BattleAnim_ApplyEffects63And75SpeciesScaleOffset(arg0);
        Particle_SetPrimAlpha(arg0, 0);
        Particle_AdvanceLifecycle(arg0);
    } else {
        Particle_DisableAndDetach(arg0);
    }
}

/**
 * @unverified Name was previously used only by callers of this address; the definition was still func_.
 */
void BattleAnim_CallbackStartEffects63And75Model38FadeIn(Particle* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            func_82157354(arg0);
            break;

        case 2:
            Particle_PrimAlpha_ApproachAndStepState_0BC5C(arg0, 0xFF, 4);
            break;
    }
}

void Gfx_DrawParticleAlpha(Gfx* arg0, s32 arg1, u16 arg2) {
    Particle* temp_v0 = BattleAnim_GetOwnerContextParticle(D_8006049C);

    gDPPipeSync(arg0++);

    gDPSetPrimColor(arg0++, 0, 0xC8, 255, 255, 255, temp_v0->prim_a);
    gDPSetEnvColor(arg0++, 255, 155, 0, 255);

    arg0 = BattleAnim_BuildAnimatedTileDisplayListFromStruct(arg0, arg1, 0x20, 5, 1, 0, 0, 0, -1, 0, 0, 0);

    gSPEndDisplayList(arg0++);
}

void Particle_CreateDisplayList_Alpha(s32 arg0, arg1_func_84344CE8* arg1) {
    if (arg0 == 2) {
        arg1->unk_18 = Gfx_AllocDisplayList(sizeof(Gfx) * 30);
        Gfx_DrawParticleAlpha(arg1->unk_18, arg1->unk_14, D_80060484);
    }
}

void Gfx_DrawParticleTexture4b(Gfx* arg0, u8* arg1, UNUSED u16 arg2) {
    Particle* temp_v0 = BattleAnim_GetOwnerContextParticle(D_8006049C);

    gDPPipeSync(arg0++);

    gDPSetPrimColor(arg0++, 0, 0, 255, 255, 255, temp_v0->prim_r);
    gDPSetEnvColor(arg0++, 255, 155, 0, 255);
    gDPSetCombineLERP(arg0++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED,
                      0, 0, 0, COMBINED);
    gDPSetTextureLUT(arg0++, G_TT_NONE);
    gSPTexture(arg0++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
    gDPLoadTextureBlock_4b(arg0++, arg1, G_IM_FMT_I, 32, 32, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                           G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

    gSPEndDisplayList(arg0++);
}

void Particle_CreateDisplayList_Texture4b(s32 arg0, arg1_func_84344CE8* arg1) {
    if (arg0 == 2) {
        arg1->unk_18 = Gfx_AllocDisplayList(sizeof(Gfx) * 30);
        Gfx_DrawParticleTexture4b(arg1->unk_18, arg1->unk_14, D_80060484);
    }
}

void Gfx_DrawParticleGreenPrim(Gfx* arg0, u8* arg1, UNUSED u16 arg2) {
    Particle* temp_v0 = BattleAnim_GetOwnerContextParticle(D_8006049C);

    gDPPipeSync(arg0++);

    gDPSetPrimColor(arg0++, 0, 0, 255, 255, 255, temp_v0->prim_g);
    gDPSetEnvColor(arg0++, 255, 255, 0, 255);
    gDPSetCombineLERP(arg0++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED,
                      0, 0, 0, COMBINED);
    gDPSetTextureLUT(arg0++, G_TT_NONE);
    gSPTexture(arg0++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
    gDPLoadTextureBlock_4b(arg0++, arg1, G_IM_FMT_I, 32, 32, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                           G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

    gSPEndDisplayList(arg0++);
}

void Particle_CreateDisplayList_GreenPrim(s32 arg0, arg1_func_84344CE8* arg1) {
    if (arg0 == 2) {
        arg1->unk_18 = Gfx_AllocDisplayList(sizeof(Gfx) * 30);
        Gfx_DrawParticleGreenPrim(arg1->unk_18, arg1->unk_14, D_80060484);
    }
}

void ParticleEffect_RegisterHandlers_Default(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_CallbackStartEffects63And75ModelAnimWait, &gDefaultParticleDescriptor, 0, 1, 0xA, 0, 0, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_CallbackStartEffects63And75Model38FadeIn, &gDefaultParticleDescriptor, 0, 1, 0xA, 0, 0, 0);
}

/**
 * @unverified Name from Stadium 1.
 */
void BattleAnim_InitializeRockSlideRockThrowHit(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_CallbackEndEffects10And50ModelAnimColorFade, &gDefaultParticleDescriptor, 0, 1, 0xA, 0, 1, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(2, BattleAnim_CallbackEndEffects10And50ModelAnimColorFade, &gDefaultParticleDescriptor, 0, 1, 0xA, 0, 2, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(5, BattleAnim_CallbackEndEffects10And50ModelAnimColorFade, &gDefaultParticleDescriptor, 0, 1, 0xA, 0, 3, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(8, BattleAnim_CallbackEndEffects10And50ModelAnimColorFade, &gDefaultParticleDescriptor, 0, 1, 0xA, 0, 0, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(9, BattleAnim_CallbackEndEffects10And50ModelAnimColorFade, &gDefaultParticleDescriptor, 0, 1, 0xA, 0, 5, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(0xA, BattleAnim_CallbackEndEffects10And50ModelAnimColorFade, &gDefaultParticleDescriptor, 0, 1, 0xA, 0, 6, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(0xD, BattleAnim_CallbackEndEffects10And50ModelAnimColorFade, &gDefaultParticleDescriptor, 0, 1, 0xA, 0, 7, 0);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0xA, 3, 2, BattleAnim_CallbackSharedDescriptors3EAnd3FAnimatedRiseFade, &gBattleAnimParticleDescriptors[0x3F], 0, 0x10, 0xA, 0, 0x11, 0);
}

/**
 * @unverified Name from Stadium 1.
 */
void BattleAnim_InitializeStrengthUse(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_CallbackStartEffects63And75ModelAnimWait, &gDefaultParticleDescriptor, 0, 1, 0xA, 0, 1, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_CallbackStartEffects63And75Model38FadeIn, &gDefaultParticleDescriptor, 0, 1, 0xA, 0, 0, 0);
}

/**
 * @unverified Name from Stadium 1.
 */
void BattleAnim_InitializeStrengthHit(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_CallbackEndEffects10And50ModelAnimColorFade, &gDefaultParticleDescriptor, 0, 1, 0xA, 0, 8, 0);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0xA, 3, 2, BattleAnim_CallbackSharedDescriptors3EAnd3FAnimatedRiseFade, &gBattleAnimParticleDescriptors[0x3E], 0, 0x10, 0xA, 0, 0x11, 0);
}

/**
 * @unverified Name from Stadium 1.
 */
void BattleAnim_InitializeEggBombUse(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_CallbackInitModelAnimWait, &gDefaultParticleDescriptor, 0, 1, 0xA, 0, 0x23, 0);
}

/**
 * @unverified Name from Stadium 1.
 */
void BattleAnim_InitializeSoftBoiledUse(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_CallbackInitModelAnimWait, &gDefaultParticleDescriptor, 0, 1, 0xA, 0, 0x24, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(8, BattleAnim_CallbackInitModelAnimWait, &gDefaultParticleDescriptor, 0, 1, 0xA, 1, 0x24, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(0x10, BattleAnim_CallbackInitModelAnimWait, &gDefaultParticleDescriptor, 0, 1, 0xA, 2, 0x24, 0);
    BattleAnim_SpawnOwnerModelTintPulseDetach(0x5F, 0, 0x8, 0, 0xFF, 8);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0x5F, 8, 0xC, BattleAnim_RunSparkleHit, &gBattleAnimParticleDescriptors[0x42], 0, 8, 9, 0, 0x17, 6);
}

/**
 * @unverified Name from Stadium 1.
 */
void BattleAnim_SetupStrongWinds(Particle* arg0) {
    arg0->displayObject = BattleAnim_AllocOwnerDisplayContext(arg0);
    if (arg0->displayObject != NULL) {
        BattleAnim_InitModel(arg0->displayObject, 0x60);
        Particle_FieldCA_SetU8_0BECC(arg0, 7);
        Particle_SetFlags(arg0, 0x200);
        Particle_SetScale(arg0, 3.3f);
        Particle_SetPrimAlpha(arg0, 0);
        Particle_AdvanceLifecycle(arg0);
    } else {
        Particle_DisableAndDetach(arg0);
    }
}

void func_82157E28(s8 *arg0) {
    s16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_82157DA0(arg0);
        break;
    case 2:
        func_82140518(arg0, 0x9B, 8);
        break;
    case 3:
        func_8213C930(arg0);
        break;
    }
    if (func_8213C9B0(arg0) != 0) {
        func_8213831C(arg0 + 0x4C, 0x43480000);
    }
}

void Gfx_DrawParticleCyanEnv(Gfx* arg0, arg1_func_8434E21C* arg1, UNUSED u16 arg2) {
    BattleAnim_GetOwnerContextParticle(D_8006049C);

    gDPPipeSync(arg0++);
    gDPSetEnvColor(arg0++, 155, 255, 255, 255);

    arg0 = BattleAnim_BuildAnimatedTileDisplayListFromStruct(arg0, arg1, 0x20, 5, 2, 1, 0xE, 0xF, 0, 4, 0xC, 5);

    gSPEndDisplayList(arg0++);
}

void Particle_CreateDisplayList_CyanEnv(s32 arg0, arg1_func_84344CE8* arg1) {
    if (arg0 == 2) {
        arg1->unk_18 = Gfx_AllocDisplayList(sizeof(Gfx) * 30);
        Gfx_DrawParticleCyanEnv(arg1->unk_18, arg1->unk_14, D_80060484);
    }
}

void Gfx_DrawParticleBluePrim(Gfx* arg0, arg1_func_8434E21C* arg1, UNUSED u16 arg2) {
    Particle* temp_v0 = BattleAnim_GetOwnerContextParticle(D_8006049C);

    gDPPipeSync(arg0++);
    gDPSetPrimColor(arg0++, 0, 0x80, 255, 255, 255, temp_v0->prim_a);
    gDPSetEnvColor(arg0++, 0, 255, 255, 255);

    arg0 = BattleAnim_BuildAnimatedTileDisplayListFromStruct(arg0, arg1, 0x20, 5, -3, -5, 0xD, 3, 0, -2, 0xF, 2);

    gSPEndDisplayList(arg0++);
}

void Particle_CreateDisplayList_BluePrim(s32 arg0, arg1_func_84344CE8* arg1) {
    if (arg0 == 2) {
        arg1->unk_18 = Gfx_AllocDisplayList(sizeof(Gfx) * 30);
        Gfx_DrawParticleBluePrim(arg1->unk_18, arg1->unk_14, D_80060484);
    }
}

/**
 * Full screen overlay for gust, razor wind, and whirlwind
 * @unverified Name and comment from Stadium 1.
 */
void BattleAnim_InitializeStrongWind(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_CallbackInitModelAnimWait, &gDefaultParticleDescriptor, 0, 1, 0xE, 0, 0x25, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_CallbackStartEffect10Model60AlphaFadeIn, &gDefaultParticleDescriptor, 0, 1, 0x14, 0, 0, 0);
}

/**
 * initializes charging razor wind
 * @unverified Name and comment from Stadium 1.
 */
void BattleAnim_InitializeRazorWindUse(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_CallbackInitModelAnimWait, &gDefaultParticleDescriptor, 0, 1, 0xE, 0, 0x25, 0);
}

/**
 * @unverified Name from Stadium 1.
 */
void BattleAnim_RunBoomUseEffect1(Particle* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            BattleAnim_SelectParticleModelFrames(arg0, 0);
            break;

        case 2:
            Particle_TickDelayAndAdvanceLifecycle(arg0, arg0->unk_A6);
            break;

        case 3:
            Particle_DisableAndDetach(arg0);
            break;
    }
}

/**
 * @unverified Name was previously used only by callers of this address; the definition was still func_.
 */
void BattleAnim_CallbackStartEffects50And82ScalePulse_InitParticle(Particle* arg0) {
    Particle_Field1C_SetScaled_0B938(arg0, 2.0f);
    Particle_Field38_AddXZFromField94YOffset180_08F38(arg0, 10.0f);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, Particle_FieldCF_GetS16_0C058(arg0));
    Particle_SetPrimAlpha(arg0, 0xFF);
    Particle_SetTextureFrame(arg0, 1);
    Particle_Field94_SetZ_0A2CC(arg0, ParticleMath_RandomRange(0x10000));
    Particle_AdvanceLifecycle(arg0);
}

/**
 * @unverified Name from Stadium 1.
 */
void BattleAnim_RunBoomUseEffect2(Particle* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            BattleAnim_CallbackStartEffects50And82ScalePulse_InitParticle(arg0);
            break;

        case 2:
            Particle_Field1C_ApproachAndStepState_0B9D0(arg0, 10.0f, 1.0f);
            break;

        case 3:
            Particle_Field1C_ApproachAndStepState_0B9D0(arg0, 0.0f, 1.0f);
            Particle_PrimAlpha_Approach_0BC2C(arg0, 0x40, 0x20);
            break;

        case 4:
            Particle_DisableAndDetach(arg0);
            break;
    }
}

/**
 * @unverified Name from Stadium 1.
 */
void BattleAnim_SetupBoomUseEffect3(Particle* arg0) {
    UNUSED s16 pad; // FAKE: stack padding
    s16 sp34;
    Vec3s sp2C;
    UNUSED s32 pad2[3]; // FAKE: stack padding

    Particle_FieldAC_GetS16_0C038(arg0);
    sp34 = Particle_FieldCF_GetS16_0C058(arg0);
    Particle_SetRandomVelocityXYZ(arg0, 5, 5, 5);
    Particle_Field1C_SetScaled_0B938(arg0, 1.5f);
    Particle_Field74_SetScaled_0AD8C(arg0, 1.5f);
    sp2C.x = ParticleMath_RandomRange(0x2000) - 0x1000;
    sp2C.y = ParticleMath_RandomRange(0x10000);
    sp2C.z = 0;
    Particle_Field94_AddVecFromVec3s_0A4F0(arg0, sp2C);
    Particle_AddRotationTargetXY(arg0, sp2C.x, sp2C.y);
    Particle_Field9A_SetXY_0A3A0(arg0, 0, 0);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, sp34);
    Particle_SetPrimAlpha(arg0, 0x80);
    Particle_FieldA6_SetS16_0BCA8(arg0, arg0->unk_AC * 2);
    Particle_DisableRendering(arg0);
    Particle_AdvanceLifecycle(arg0);
}

/**
 * @unverified Name from Stadium 1, matched by code similarity.
 */
void BattleAnim_RunBoomUseEffect3(s8 *arg0) {
    s16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_82158344(arg0);
        return;
    case 2:
        if (func_821406B4(arg0) != 0) {
            func_82140594(arg0, 0xA);
            func_8213CB3C(arg0);
            return;
        }
        return;
    case 3:
        func_8213CCEC(arg0, 0, 7, 1, 2, 0);
        func_82140228(arg0, 0x40200000, 0x3E800000);
        func_8213E528(arg0);
        func_8213D604(arg0, 0.5f);
        if (func_82140690(arg0) != 0) {
            func_82140518(arg0, 0x20, 0x10);
            func_821403B0(arg0, 0, 0x14);
            func_8214047C(arg0, 0, 0x14);
            return;
        }
        break;
    case 4:
        func_8213C930(arg0);
        break;
    }
}

/**
 * @unverified Name from Stadium 1.
 */
void BattleAnim_SetupBoomUseEffect4(Particle* arg0) {
    UNUSED s32 pad[2]; // FAKE: stack padding
    UNUSED s16 pad2; // FAKE: stack padding
    s16 sp24;

    Particle_FieldAC_GetS16_0C038(arg0);
    sp24 = Particle_FieldCF_GetS16_0C058(arg0);
    Particle_FieldCE_GetS32_0C040(arg0);
    Particle_Field1C_SetScaled_0B938(arg0, 1.0f);
    Particle_SetRandomVelocityXYZ(arg0, 0xF, 0xF, 0x14);
    Particle_Field74_SetScaled_0AD8C(arg0, (ParticleMath_RandomRange(0x32) * 0.02f) + 1.0f);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, sp24);
    Particle_SetPrimAlpha(arg0, 0x80);
    Particle_DisableRendering(arg0);
    Particle_AdvanceLifecycle(arg0);
}

/**
 * @unverified Name from Stadium 1, matched by code similarity.
 */
void BattleAnim_RunBoomUseEffect4(s8 *arg0) {
    s16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_8215856C(arg0);
        return;
    case 2:
        if (func_821406B4(arg0) != 0) {
            func_8213CB3C(arg0);
            func_82140594(arg0, 5);
            return;
        }
        return;
    case 3:
        func_8213CCEC(arg0, 0, 7, 1, 2, 0);
        func_8213E77C(arg0);
        if (func_82140690(arg0) != 0) {
            func_821403B0(arg0, 0, 0x14);
            func_8214047C(arg0, 0, 0x14);
            func_82140518(arg0, 0x20, 4);
            return;
        }
        break;
    case 4:
        func_8213C930(arg0);
        break;
    }
}

void Gfx_DrawParticleCustomColors(Gfx* arg0, arg1_func_8434E21C* arg1, UNUSED u16 arg2) {
    Particle* temp_v0 = BattleAnim_GetOwnerContextParticle(D_8006049C);

    gDPPipeSync(arg0++);

    gDPSetPrimColor(arg0++, 0, 0x78, temp_v0->prim_r, temp_v0->prim_g, temp_v0->prim_b, temp_v0->prim_a);
    gDPSetEnvColor(arg0++, temp_v0->env_r, temp_v0->env_g, temp_v0->env_b, temp_v0->unk_B0);
    gDPSetCombineLERP(arg0++, TEXEL1, TEXEL0, PRIM_LOD_FRAC, TEXEL0, TEXEL1, TEXEL0, PRIM_LOD_FRAC, TEXEL0, PRIMITIVE,
                      ENVIRONMENT, COMBINED, ENVIRONMENT, COMBINED, 0, PRIMITIVE, ENVIRONMENT);

    arg0 = BattleAnim_BuildAnimatedTileDisplayListFromStruct(arg0, arg1, 0x20, 5, 2, 0xA, 0xD, 0xF, -2, 5, 0xE, 0xF);

    gSPEndDisplayList(arg0++);
}

void Particle_CreateDisplayList_CustomColors(s32 arg0, arg1_func_84344CE8* arg1) {
    if (arg0 == 2) {
        arg1->unk_18 = Gfx_AllocDisplayList(sizeof(Gfx) * 30);
        Gfx_DrawParticleCustomColors(arg1->unk_18, arg1->unk_14, D_80060484);
    }
}

void func_821588C0(s8 *arg0) {
    s16 temp_v1;

    func_8213C464();
    temp_v1 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v1) {                              /* irregular */
    case 1:
        func_82152730(arg0, 2);
        func_821401D4(arg0, 0x3F000000);
        func_821408C8(arg0, 0x64);
        func_82143478(arg0, 0x17);
        func_82140594(arg0, 5);
        return;
    case 2:
        func_82140228(arg0, 0x40E00000, 0x3E800000);
        if (func_821406B4(arg0) != 0) {
            func_82140594(arg0, 5);
            return;
        }
        return;
    case 3:
        func_82140228(arg0, 0x40E00000, 0x3E800000);
        func_821437E0(arg0, 0x1A, 0x19);
        if (func_82140690(arg0) != 0) {
            func_821408DC(arg0, 0, 8);
            func_82140548(arg0, 0, 0x10);
            return;
        }
        break;
    case 4:
        func_8213C930(arg0);
        break;
    }
}

/**
 * @unverified Name from Stadium 1.
 */
void BattleAnim_RunBoomUseEffect6(Particle* arg0) {
    s16 sp26 = Particle_FieldCE_GetS32_0C040(arg0);

    switch (arg0->unk_B2) {
        case 1:
            BattleAnim_SelectParticleModelFrames(arg0, 2);
            Particle_Field1C_SetScaled_0B938(arg0, 0.5f);
            Particle_FieldB0_SetS16_0BFEC(arg0, 0x64);
            ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, 0x17);
            Particle_FieldA6_SetS16_0BCA8(arg0, 5);

            switch (sp26) {
                case 0:
                    Particle_Field38_SetXScaled_08C88(arg0, 15.0f);
                    Particle_Field38_SetYScaled_08CA0(arg0, 15.0f);
                    break;

                case 1:
                    Particle_Field38_SetXScaled_08C88(arg0, -15.0f);
                    Particle_Field38_SetZScaled_08CB8(arg0, 15.0f);
                    Particle_Field38_SetYScaled_08CA0(arg0, -10.0f);
                    break;

                case 2:
                    Particle_Field38_SetXScaled_08C88(arg0, -10.0f);
                    Particle_Field38_SetZScaled_08CB8(arg0, -15.0f);
                    break;
            }
            break;

        case 2:
            Particle_Field1C_Approach_0B98C(arg0, 5.0f, 0.15f);
            if (Particle_FieldA6_DecrementToZeroStep1AndStepState_0BDD0(arg0) != 0) {
                Particle_FieldA6_SetS16_0BCA8(arg0, 5);
            }
            break;

        case 3:
            Particle_Field1C_Approach_0B98C(arg0, 5.0f, 0.15f);
            ParticleGfx_ApproachPrimEnvPalettePair(arg0, 0x1A, 0x19);
            if (Particle_FieldA6_DecrementToZeroStep1_0BDAC(arg0) != 0) {
                Particle_FieldB0_Approach_0C000(arg0, 0, 8);
                Particle_PrimAlpha_ApproachAndStepState_0BC5C(arg0, 0, 0x10);
            }
            break;

        case 4:
            Particle_MarkInactive(arg0);
            break;
    }
}

/**
 * @unverified Name from Stadium 1, matched by code similarity.
 */
void BattleAnim_RunBoomHitEffect1(s8 *arg0) {
    s16 temp_v1;

    func_8213C464();
    temp_v1 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v1) {                              /* irregular */
    case 1:
        func_82152730(arg0, 2);
        func_821401D4(arg0, 0x3E800000);
        func_821408C8(arg0, 0x64);
        func_82143478(arg0, 0x17);
        func_82140594(arg0, 5);
        func_8213D644(arg0, 30.0f);
        return;
    case 2:
        func_82140228(arg0, 0x40A00000, 0x3E99999A);
        if (func_821406B4(arg0) != 0) {
            func_82140594(arg0, 5);
            return;
        }
        return;
    case 3:
        func_82140228(arg0, 0x40A00000, 0x3E99999A);
        func_821437E0(arg0, 0x1A, 0x19);
        if (func_82140690(arg0) != 0) {
            func_821408DC(arg0, 0, 8);
            func_82140548(arg0, 0, 0x10);
            return;
        }
        break;
    case 4:
        func_8213C930(arg0);
        break;
    }
}

/**
 * @unverified Name from Stadium 1.
 */
void BattleAnim_SetupBoomHitEffect2(Particle* arg0) {
    UNUSED s32 pad[2]; // FAKE: stack padding
    s16 sp26 = Particle_FieldAC_GetS16_0C038(arg0);

    Particle_FieldCE_GetS32_0C040(arg0);
    Particle_FieldCF_GetS16_0C058(arg0);
    Particle_FieldA6_SetS16_0BCA8(arg0, sp26 * 2);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, Particle_FieldCF_GetS16_0C058(arg0));
    Particle_Field1C_SetScaled_0B938(arg0, 1.2f);
    Particle_SetScaleSpeed(arg0, 1.0f);
    Particle_SetScaleTarget(arg0, 0.02f);
    Particle_SetRandomVelocityXYZ(arg0, 5, 0xF, 0xF);
    Particle_Field38_AddYScaled_08E90(arg0, 10.0f);
    Particle_Field74_SetScaled_0AD8C(arg0, (ParticleMath_RandomRange(0xA) * 0.5f) + 8.0f);
    ParticleGfx_RecolorPrim(arg0, 0x17);
    ParticleGfx_RecolorEnv(arg0, 0x17);
    Particle_SetPrimAlpha(arg0, 0xC8);
    Particle_FieldAE_SetS16_0BF4C(arg0, 4);
    Particle_DisableRendering(arg0);
    Particle_AdvanceLifecycle(arg0);
}

/**
 * @unverified Name from Stadium 1, matched by code similarity.
 */
void BattleAnim_RunBoomHitEffect2(s8 *arg0) {
    s16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_82158CE0(arg0);
        return;
    case 2:
        if (func_821406B4(arg0) != 0) {
            func_8213CB3C(arg0);
            func_82140594(arg0, 4);
            return;
        }
        return;
    case 3:
        func_821402B8(arg0);
        func_8213CCEC(arg0, 1, 7, 1, 2, 0);
        func_8213E6BC(arg0);
        func_821403B0(arg0, 0, 0x20);
        func_821404DC(arg0, 0, 0x20);
        if (func_82140690(arg0) != 0) {
            return;
        }
        break;
    case 4:
        func_8213C930(arg0);
        break;
    }
}

/**
 * @unverified Name from Stadium 1.
 */
void BattleAnim_SetupBoomHitEffect3(Particle* arg0) {
    UNUSED s32 pad[2]; // FAKE: stack padding
    s16 sp26 = Particle_FieldAC_GetS16_0C038(arg0);
    UNUSED s16 pad2; // FAKE: stack padding
    s16 sp22;

    Particle_FieldCE_GetS32_0C040(arg0);
    sp22 = Particle_FieldCF_GetS16_0C058(arg0);
    Particle_FieldA6_SetS16_0BCA8(arg0, sp26 * 2);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, Particle_FieldCF_GetS16_0C058(arg0));
    Particle_Field1C_SetScaled_0B938(arg0, 1.0f);
    Particle_SetScaleSpeed(arg0, 0.5f);
    Particle_SetScaleTarget(arg0, 0.01f);
    Particle_SetRandomVelocityXYZ(arg0, 0xA, 0, 0xF);
    Particle_Field38_AddXZFromField94Y_08ED0(arg0, 10.0f);
    Particle_Field38_AddYScaled_08E90(arg0, 5.0f);
    Particle_Field74_SetScaled_0AD8C(arg0, (ParticleMath_RandomRange(0xA) * 0.5f) + 8.0f);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, sp22);
    Particle_SetPrimAlpha(arg0, 0xB4);
    Particle_FieldAE_SetS16_0BF4C(arg0, 4);
    Particle_DisableRendering(arg0);
    Particle_AdvanceLifecycle(arg0);
}

/**
 * @unverified Name from Stadium 1, matched by code similarity.
 */
void BattleAnim_RunBoomHitEffect3(s8 *arg0) {
    s16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_82158F20(arg0);
        break;
    case 2:
        if (func_821406B4(arg0) != 0) {
            func_8213CB3C(arg0);
            func_82140594(arg0, 4);
        }
        break;
    case 3:
        func_82140548(arg0, 0x40, 0x10);
        if (func_82140690(arg0) != 0) {
            func_821437E0(arg0, 0x16, 0x20);
        }
        func_8213F658(arg0, 0x40800000, 0x3F000000);
        func_8213E6BC(arg0);
        break;
    case 4:
        func_8213C930(arg0);
        break;
    }
    if (func_8213CB7C(arg0) != 0) {
        func_821402B8(arg0);
        func_8213CC10(arg0, 0, 7, 1, 2, 0);
    }
}

/**
 * @unverified Name from Stadium 1, matched by code similarity.
 */
void BattleAnim_InitializeBoomUse(void) {
    BattleAnim_SpawnGlobalTintColorFadeDetach(0, 0x10, 6);
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_RunBoomUseEffect1, &gDefaultParticleDescriptor, 0x19, 1, 0xE, 0, 0x27, 0);
    BattleAnim_SpawnDescriptor25AlphaFadeInHold(0, 0, 4, 0x8, 0x80);
    BattleAnim_CreateEffectSlotForCurrentOwner(0x16, BattleAnim_RunBoomUseEffect2, &D_8218E580[0x54], 0, 1, 0xC, 0, 0x33, 0);
    BattleAnim_SpawnDescriptor25AlphaHoldFadeOut(0x1A, 3, 0x20, 0x8, 0xC8);
    BattleAnim_CreateEffectSlotForCurrentOwner(0x1B, BattleAnim_CallbackStartEffects50And82CenterModelScalePaletteFade, &gDefaultParticleDescriptor, 0, 1, 9, 0, 0x21, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(0x1E, BattleAnim_RunBoomUseEffect6, &gDefaultParticleDescriptor, 0, 1, 9, 0, 0x21, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(0x22, BattleAnim_RunBoomUseEffect6, &gDefaultParticleDescriptor, 0, 1, 9, 0, 0x21, 1);
    BattleAnim_CreateEffectSlotForCurrentOwner(0x26, BattleAnim_RunBoomUseEffect6, &gDefaultParticleDescriptor, 0, 1, 9, 0, 0x21, 2);
    BattleAnim_CreateEffectSlotForCurrentOwner(0x28, BattleAnim_CallbackStartEffects50And82Descriptor48AnimatedScaleFade, &D_8218E580[0x48], 0, 6, 0x10, 9, 0x1A, 0);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0x32, 2, 2, BattleAnim_CallbackStartEffects50And82Descriptor4AAnimatedVerticalFade, &D_8218E580[0x4A], 0, 1, 9, 0, 0x1A, 0);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0x33, 2, 2, BattleAnim_CallbackStartEffects50And82Descriptor4AAnimatedVerticalFade, &D_8218E580[0x4A], 0, 1, 9, 0, 0x1A, 0);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0x34, 2, 2, BattleAnim_CallbackStartEffects50And82Descriptor4AAnimatedVerticalFade, &D_8218E580[0x4A], 0, 1, 9, 0, 0x1A, 0);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0x36, 2, 2, BattleAnim_CallbackStartEffects50And82Descriptor4AAnimatedVerticalFade, &D_8218E580[0x4A], 0, 1, 9, 0, 0x1A, 0);
    BattleAnim_SpawnOwnerModelTintRampDetach(0x16, 0x8, 0, 0xFF, 0x40);
    BattleAnim_SpawnOwnerModelTintRampDetach(0x24, 0x8, 0xFF, 0xDC, 0xC);
    BattleAnim_SpawnOwnerModelTintPaletteApproachInactiveAlt(0x28, 0x8, 0x17, 0x10, 0xDC);
    BattleAnim_SpawnOwnerModelTintPaletteApproachInactiveAlt(0x38, 0x17, 0x11, 0x10, 0xDC);
    BattleAnim_SpawnOwnerModelTintPaletteApproachInactiveAlt(0x40, 0x11, 0xE, 0x10, 0xDC);
    BattleAnim_SpawnOwnerModelTintRampDetach(0x48, 0xE, 0xDC, 0xB4, 6);
}

/**
 * @unverified Name from Stadium 1, matched by code similarity.
 */
void BattleAnim_InitializeBoomHit(void) {
    BattleAnim_SpawnGlobalTintColorFadeDetach(0, 0xFF, 6);
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_CallbackEndEffects81And82ModelScalePaletteFade, &gDefaultParticleDescriptor, 0, 1, 0xB, 0, 0x21, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(4, BattleAnim_CallbackEndEffects81And82ModelScalePaletteFade, &gDefaultParticleDescriptor, 0, 1, 0xB, 0, 0x21, 0);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0xA, 8, 4, BattleAnim_CallbackInitModelAnimWait, &gDefaultParticleDescriptor, 0, 1, 0xC, 0, 0x8, 0);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0xC, 8, 5, BattleAnim_CallbackEndEffects81And82Descriptor46AnimatedFade, &D_8218E580[0x46], 0, 5, 0x10, 9, 0x48, 0);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0xC, 4, 0xA, BattleAnim_CallbackEndEffects81And82Descriptor4AAnimatedColorFade, &D_8218E580[0x4A], 0, 4, 0xB, 9, 0, 0);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0xC, 4, 0xA, BattleAnim_CallbackEndEffects81And82Descriptor4FAnimatedPaletteFade, &D_8218E580[0x4F], 0, 4, 0xE, 9, 0x1A, 0);
    BattleAnim_SpawnOwnerModelTintRampDetach(3, 0x8, 0, 0xFF, 0x40);
    BattleAnim_SpawnOwnerModelTintRampDetach(0xA, 0x8, 0xFF, 0xE6, 5);
    BattleAnim_SpawnOwnerModelTintPaletteApproachInactiveAlt(0x10, 0x8, 0x17, 0x10, 0xDC);
    BattleAnim_SpawnOwnerModelTintPaletteApproachInactiveAlt(0x18, 0x17, 0x9, 0x10, 0xD2);
    BattleAnim_SpawnOwnerModelTintPaletteApproachInactiveAlt(0x28, 0x9, 0xE, 0x10, 0xC8);
    BattleAnim_SpawnOwnerModelTintRampDetach(0x30, 0xE, 0xC8, 0xB4, 6);
}

void func_821597B8(UNUSED ActivePokemon* active_pokemon, UNUSED s32 unused) {
}

void BattleAnim_TransformNop(UNUSED ActivePokemon* owner, UNUSED ActivePokemon* animated_pokemon) {
}

/**
 * @unverified Name from Stadium 1.
 */
void BattleAnim_SetupBitingEffect(Particle* arg0) {
    s16 sp26 = Particle_FieldCF_GetS16_0C058(arg0);

    arg0->displayObject = BattleAnim_AllocParticleDisplayContext(arg0);
    if (arg0->displayObject != NULL) {
        if (sp26 == 0) {
            BattleAnim_InitModel(arg0->displayObject, 0x55);
        } else {
            BattleAnim_InitModel(arg0->displayObject, 0x63);
        }
        BattleAnim_BindModelAnim(arg0->displayObject, 0x56);
        Particle_SetFlags(arg0, 0x200);
        Particle_FieldCA_SetU8_0BECC(arg0, 7);
        Particle_SetScale(arg0, 1.0f);
        ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, 0x24);
        Particle_SetPrimAlpha(arg0, 0);
        Particle_AdvanceLifecycle(arg0);
    } else {
        Particle_DisableAndDetach(arg0);
    }
}

void func_82159898(s8 *arg0) {
    s16 sp26;
    s16 temp_v1;

    sp26 = func_8213C484();
    temp_v1 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v1) {                              /* irregular */
    case 1:
        func_821597D0(arg0);
        break;
    case 2:
        func_8213CA80(arg0, 0xE);
        func_821403B0(arg0, 0xFF, 7);
        func_821403E0(arg0, 0xFF, 0x13);
        func_821404DC(arg0, 0xFF, 0x13);
        func_82140518(arg0, 0xFF, 0x13);
        break;
    case 3:
        func_8213CA80(arg0, 0x10);
        func_821403E0(arg0, 0, 0x11);
        func_821404DC(arg0, 0, 0x11);
        func_82140518(arg0, 0, 0x11);
        break;
    case 4:
        if (func_8001104C(M2C_FIELD(arg0, s32 *, 0x14)) != 0) {
            func_8213C930(arg0);
        }
        break;
    }
    if (func_8213C9B0(arg0) != 0) {
        if (sp26 == 0) {
            func_8213831C(arg0 + 0x4C, 0x432A0000);
            return;
        }
        func_8213831C(arg0 + 0x4C, 0x430C0000);
    }
}

void Gfx_DrawParticleFromTempColors(Gfx* arg0, s32 arg1, u16 arg2) {
    Particle* temp_v0 = BattleAnim_GetOwnerContextParticle(D_8006049C);

    gDPPipeSync(arg0++);

    gDPSetPrimColor(arg0++, 0, 0, temp_v0->prim_r, temp_v0->prim_g, temp_v0->prim_b, temp_v0->prim_a);
    gDPSetEnvColor(arg0++, temp_v0->env_r, temp_v0->env_g, temp_v0->env_b, 0);

    arg0 = BattleAnim_BuildAnimatedTileDisplayListFromStruct(arg0, arg1, 0x20, 5, 0, 0, 0, 0, 0, 0, 0, 0);

    gSPEndDisplayList(arg0++);
}

void Particle_CreateDisplayList_TempColors(s32 arg0, arg1_func_84344CE8* arg1) {
    if (arg0 == 2) {
        arg1->unk_18 = Gfx_AllocDisplayList(sizeof(Gfx) * 30);
        Gfx_DrawParticleFromTempColors(arg1->unk_18, arg1->unk_14, D_80060484);
    }
}

/**
 * @unverified Name from Stadium 1.
 */
void BattleAnim_InitializeClampViceGripUse(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_CallbackStartEffects71And74And111SpecialModelColorCycle, &gDefaultParticleDescriptor, 0, 1, 0x14, 0, 0, 0);
}

/**
 * initializes using guillotine
 * @unverified Name and comment from Stadium 1.
 */
void BattleAnim_InitializeGuillotineUse(void) {
    BattleAnim_SpawnGlobalTintColorFadeDetach(0, 0x20, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_CallbackStartEffects71And74And111SpecialModelColorCycle, &gDefaultParticleDescriptor, 0, 1, 0x14, 0, 0, 0);
}

/**
 * Moves: Bite (use), Hyper Fang (use), Super Fang (use)
 * TODO: Human contributor add screenshot
 * @unverified Name and comment from Stadium 1.
 */
void BattleAnim_InitializeBitingMoveUse(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_CallbackStartEffects71And74And111SpecialModelColorCycle, &gDefaultParticleDescriptor, 0, 1, 0x14, 0, 1, 0);
}

/**
 * Moves: Bite (hit), Clamp (hit), Hyper Fang (hit), Super Fang (hit), Vice Grip (hit)
 * TODO: Human contributor add screenshot
 * @unverified Name and comment from Stadium 1.
 */
void BattleAnim_InitializeBitingMoveHit(void) {
    BattleAnim_InitializeBitingMoveEndEffect();
}

/**
 * initializes being hit by guillotine
 * @unverified Name and comment from Stadium 1, matched by code similarity.
 */
void BattleAnim_InitializeGuillotineHit(void) {
    func_8213BC00(0, 0xA, 0, 0xFF, 0x40);
    func_82166B34();
    func_8213BC00(0x30, 0xA, 0xFF, 0, 2);
}

void Gfx_DrawParticleDualTileDiagonal4(Gfx* arg0, u8* arg1, UNUSED u16 arg2) {
    BattleAnim_GetOwnerContextParticle(D_8006049C);
    arg0 = BattleAnim_BuildAnimatedTileDisplayList(arg0, arg1, 0x20, 5, -4, -4, 0xD, 6, 4, 4, 0xF, 1);

    gSPEndDisplayList(arg0++);
}

void Particle_CreateDisplayList_DualTileDiagonal4(s32 arg0, arg1_func_84344CE8* arg1) {
    if (arg0 == 2) {
        arg1->unk_18 = Gfx_AllocDisplayList(sizeof(Gfx) * 30);
        Gfx_DrawParticleDualTileDiagonal4(arg1->unk_18, arg1->unk_14, D_80060484);
    }
}

void Gfx_DrawParticleDualTileAntiDiagonal1(Gfx* arg0, u8* arg1, UNUSED u16 arg2) {
    BattleAnim_GetOwnerContextParticle(D_8006049C);
    arg0 = BattleAnim_BuildAnimatedTileDisplayList(arg0, arg1, 0x20, 5, 1, -1, 0xE, 0xE, -1, 1, 2, 2);

    gSPEndDisplayList(arg0++);
}

void Particle_CreateDisplayList_DualTileAntiDiagonal1(s32 arg0, arg1_func_84344CE8* arg1) {
    if (arg0 == 2) {
        arg1->unk_18 = Gfx_AllocDisplayList(sizeof(Gfx) * 30);
        Gfx_DrawParticleDualTileAntiDiagonal1(arg1->unk_18, arg1->unk_14, D_80060484);
    }
}

/**
 * initializes using swords dance
 * @unverified Name and comment from Stadium 1.
 */
void BattleAnim_InitializeSwordsDanceUse(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_CallbackInitModelAnimWait, &gDefaultParticleDescriptor, 0, 1, 2, 0, 0x28, 0);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(4, 8, 0xC, BattleAnim_RunSparkleHit, &gBattleAnimParticleDescriptors[0x42], 0, 8, 9, 0, 0x22, 6);
}

f32 BattleAnim_GetSpeciesScaleAdjust(Particle* arg0) {
    f32 sp1C = 1.0f;

    switch (BattleAnim_GetOwnerSpecies(arg0->pokemon)) {
        case 0x3B:
            sp1C = 1.45f;
            break;

        case 0x5F:
            Particle_Field38_AddXZFromField94YOffsetMinus90_0901C(arg0, 20.0f);
            sp1C = 0.9f;
            break;

        case 0x82:
            sp1C = 0.9f;
            break;
    }
    return sp1C;
}

void BattleAnim_CallbackStartEffect69ModelPhaseWait(Particle* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            BattleAnim_SelectParticleModelFrames(arg0, 0);
            break;

        case 2:
            break;

        case 3:
            Particle_DisableAndDetach(arg0);
            break;
    }
}

void func_82159FC8(void) {
    func_8213B560(0, &func_82159F70, &D_8218E580, 0, 1, 0xA, 0, 0x29, 0);
    func_8213B5D8(5, 2, 0xA, &BattleAnim_RunDigHitDust, &D_8218E7D0, 0, 2, 0xA, 0, 0x44, 9);
    func_8213B5D8(0xA, 5, 6, &BattleAnim_RunDigHitRocks, &D_8218E708, 0, 3, 0xA, 0, 0x44, 0xB);
}

/**
 * @unverified Name from Stadium 1.
 */
void BattleAnim_InitializeDigUse(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_InitializeParticleModel, &gDefaultParticleDescriptor, 0, 1, 0xA, 0, 0x16, 0);
}

/**
 * @unverified Name from Stadium 1, matched by code similarity.
 */
void BattleAnim_InitializeDigHit(void) {
    func_8213B560(0, &func_82152FB0, &D_8218E580, 0, 1, 0xA, 0, 0x1D, 0);
    func_8213B5D8(0, 3, 3, &func_82162C68, &D_8218E728, 0, 1, 0xE, 9, 0, 0xF);
    func_8213B5D8(4, 1, 4, &BattleAnim_RunDigHitDust, &D_8218E7D0, 0, 8, 0x1B, 0, 0x44, 0xA);
    func_8213B560(4, &BattleAnim_RunDigHitRocks, &D_8218E708, 0, 0xC, 0x1B, 0, 0x44, 0xB);
}

/**
 * @unverified Name from Stadium 1.
 */
void BattleAnim_InitializeKinesisUse(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_CallbackInitModelAnimWait, &gDefaultParticleDescriptor, 0, 1, 0xB, 0, 0, 0);
    BattleAnim_SpawnCategory19MarkerSlot(0x28, 1);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(4, 4, 3, BattleAnim_RunSparkleHit, &gBattleAnimParticleDescriptors[0x42], 0, 4, 0xB, 0, 0x17, 0xA);
}

/**
 * @unverified Name from Stadium 1, matched by code similarity.
 */
void BattleAnim_InitializeBoneClubUse(void) {
    func_8213B560(0, &func_82152F44, &D_8218E580, 0, 1, 4, 0, 1, 0);
    func_8213B720(0x1D, 2, 0x20, 0x12);
}

/**
 * @unverified Name from Stadium 1.
 */
void BattleAnim_InitializeBonemerangUse(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_CallbackInitModelAnimWait, &gDefaultParticleDescriptor, 0, 1, 0xB, gBattleAnimCurrentAnchor, 2, 0);
}

void BattleAnim_CallbackStartEffect17ModelAnimFinish_InitParticle(Particle* arg0) {
    Particle_FieldCD_GetU8_0C048(arg0);
    arg0->displayObject = BattleAnim_AllocOwnerDisplayContext(arg0);
    if (arg0->displayObject != NULL) {
        BattleAnim_InitModelWithAnim(arg0->displayObject, 0x71, 0x72);
        Particle_Field1C_SetScaled_0B938(arg0, 1.0f);
        Particle_FieldA6_SetS16_0BCA8(arg0, 0x1E);
        Particle_AdvanceLifecycle(arg0);
    } else {
        Particle_DisableAndDetach(arg0);
    }
}

void BattleAnim_CallbackStartEffect17ModelAnimFinish(Particle* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            BattleAnim_CallbackStartEffect17ModelAnimFinish_InitParticle(arg0);
            break;

        case 2:
            if (ModelAnim_IsFinished(arg0->displayObject) != 0) {
                Particle_MarkInactive(arg0);
            }
            break;
    }
}

/**
 * @unverified Name from Stadium 1.
 */
void BattleAnim_SetupSlimePuddle(Particle* arg0) {
    s16 sp26 = Particle_FieldCD_GetU8_0C048(arg0);

    arg0->displayObject = BattleAnim_AllocOwnerDisplayContext(arg0);
    if (arg0->displayObject != NULL) {
        switch (sp26) {
            case 0:
                Particle_SetPosition(arg0, 8.0f, 0.0f, -10.0f);
                break;

            case 1:
                Particle_SetPosition(arg0, -10.0f, 0.0f, 12.0f);
                break;

            case 2:
                Particle_SetPosition(arg0, 0.0f, 0.0f, -2.0f);
                break;

            case 3:
                Particle_SetPosition(arg0, 15.0f, 0.0f, 3.0f);
                break;
        }

        BattleAnim_InitModelWithAnim(arg0->displayObject, 0x6E, 0x6F);
        Particle_Field1C_SetScaled_0B938(arg0, 1.0f);
        Particle_FieldA6_SetS16_0BCA8(arg0, 0x1E);
        Particle_AdvanceLifecycle(arg0);
    } else {
        Particle_DisableAndDetach(arg0);
    }
}

/**
 * Moves: Acid (hit), Lick (hit), Sludge (hit), Toxic (hit)
 * TODO: Human contributor add screenshot
 * @unverified Name and comment from Stadium 1.
 */
void BattleAnim_RunSlimePuddle(Particle* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            BattleAnim_SetupSlimePuddle(arg0);
            break;

        case 2:
            Particle_FieldA6_DecrementToZeroStep1AndStepState_0BDD0(arg0);
            break;

        case 3:
            Particle_Field1C_ApproachAndStepState_0B9D0(arg0, 0.0f, 0.05f);
            Particle_PrimAlpha_ApproachAndStepState_0BC5C(arg0, 0, 0x10);
            break;

        case 4:
            Particle_DisableAndDetach(arg0);
            break;
    }
}

void Gfx_DrawParticlePaletteBased(Gfx* arg0, u8* arg1, UNUSED u16 arg2) {
    UNUSED s32 pad[2]; // FAKE: stack padding
    s16 sp2E = Particle_FieldCF_GetS16_0C058(BattleAnim_GetOwnerContextParticle(D_8006049C));
    u8 sp2D;
    u8 sp2C;
    u8 sp2B;
    u8 sp2A;
    u8 sp29;
    u8 sp28;

    gDPLoadTextureBlock(arg0++, arg1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0, G_TX_NOMIRROR | G_TX_WRAP,
                        G_TX_NOMIRROR | G_TX_WRAP, 5, 5, G_TX_NOLOD, G_TX_NOLOD);

    ParticleGfx_SetAnimatedTileSizeOnList(arg0++, 5, 0, 0x20, 0x20);

    switch (sp2E) {
        case 0:
            sp2D = 0x96;
            sp2C = 0x32;
            sp2B = 0x32;
            sp2A = 0;
            sp29 = 0;
            sp28 = 0;
            break;

        case 1:
            sp2D = 0x78;
            sp2C = 0x96;
            sp2B = 0;
            sp2A = 0x64;
            sp29 = 0x78;
            sp28 = 0;
            break;

        case 2:
            sp2D = 0x46;
            sp2C = 0;
            sp2B = 0x78;
            sp2A = 0x64;
            sp29 = 0;
            sp28 = 0x96;
            break;

        case 3:
            sp2D = 0x64;
            sp2C = 0x96;
            sp2B = 0x96;
            sp2A = 0x64;
            sp29 = 0x96;
            sp28 = 0x96;
            break;
    }

    gDPSetPrimColor(arg0++, 0, 0xFF, sp2D, sp2C, sp2B, 255);
    gDPSetEnvColor(arg0++, sp2A, sp29, sp28, 255);

    gSPEndDisplayList(arg0++);
}

void Gfx_ParticlePaletteCallback(s32 arg0, arg1_func_84344CE8* arg1) {
    if (arg0 == 2) {
        arg1->unk_18 = Gfx_AllocDisplayList(sizeof(Gfx) * 30);
        Gfx_DrawParticlePaletteBased(arg1->unk_18, arg1->unk_14, D_80060484);
    }
}

void Gfx_ParticlePaletteDL(Gfx* arg0, UNUSED arg1_func_8434E21C* arg1, UNUSED u16 arg2) {
    DisplayObject* sp24 = D_8006049C;
    s32 tmp = BattleAnim_GetOwnerContextParticle(D_8006049C);
    UNUSED u8 sp1F;
    UNUSED u8 sp1E;
    u8 sp1D;
    u8 sp1C;
    u8 sp1B;
    u8 sp1A;
    u8 sp19;
    u8 sp18;

    switch (Particle_FieldCF_GetS16_0C058(tmp)) {
        case 0:
            sp1D = 0xFF;
            sp1C = 0x96;
            sp1B = 0x32;
            sp1A = 0;
            sp19 = 0;
            sp18 = 0;
            break;

        case 1:
            sp1D = 0xFF;
            sp1C = 0xFF;
            sp1B = 0xFF;
            sp1A = 0x96;
            sp19 = 0xB4;
            sp18 = 0;
            break;

        case 2:
            sp1D = 0xFF;
            sp1C = 0xFF;
            sp1B = 0xFF;
            sp1A = 0x96;
            sp19 = 0;
            sp18 = 0xC8;
            break;

        case 3:
            sp1D = 0x64;
            sp1C = 0xFF;
            sp1B = 0xFF;
            sp1A = 0xC8;
            sp19 = 0xFF;
            sp18 = 0xFF;
            break;
    }

    gDPSetCombineLERP(arg0++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED,
                      0, 0, 0, COMBINED);
    gDPSetPrimColor(arg0++, 0, 0xFF, sp1D, sp1C, sp1B, sp24->lodFraction);
    gDPSetEnvColor(arg0++, sp1A, sp19, sp18, 255);

    gSPEndDisplayList(arg0++);
}

void Gfx_ParticlePaletteColorOnlyCallback(s32 arg0, arg1_func_84344CE8* arg1) {
    if (arg0 == 2) {
        arg1->unk_18 = Gfx_AllocDisplayList(sizeof(Gfx) * 30);
        Gfx_ParticlePaletteDL(arg1->unk_18, arg1->unk_14, D_80060484);
    }
}

/**
 * Moves: Acid (use/hit), Lick (hit), Sludge (use/hit), Toxic (use/hit)
 * TODO: Human contributor add screenshot
 * @unverified Name and comment from Stadium 1.
 */
s16 BattleAnim_GetSlimeVariantIndex(void) {
    s16 sp1E;

    switch (BattleAnim_GetQueuedMoveId()) {
        case 0x7C:
            sp1E = 0;
            break;

        case 0x33:
            sp1E = 1;
            break;

        case 0x5C:
            sp1E = 2;
            break;

        case 0x7A:
            sp1E = 3;
            break;
    }

    return sp1E;
}

s16 BattleAnim_GetMoveKeyedTintRampParam(void) {
    s16 sp1E;

    switch (BattleAnim_GetQueuedMoveId()) {
        case 0x7C:
            sp1E = 0x10;
            break;

        case 0x33:
            sp1E = 0x29;
            break;

        case 0x5C:
            sp1E = 0x3B;
            break;

        case 0x7A:
            sp1E = 0x36;
            break;
    }

    return sp1E;
}

s16 BattleAnim_GetMoveKeyedTrailVariantParam(void) {
    s16 sp1E;

    switch (BattleAnim_GetQueuedMoveId()) {
        case 0x7C:
            sp1E = 8;
            break;

        case 0x33:
            sp1E = 0x33;
            break;

        case 0x5C:
            sp1E = 0x33;
            break;

        case 0x7A:
            sp1E = 0x33;
            break;
    }

    return sp1E;
}

/**
 * Handles the slime using in Toxic, Sludge, and Acid
 * @unverified Name and comment from Stadium 1.
 */
void BattleAnim_InitializeSlimeMove(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_CallbackStartEffect17ModelAnimFinish, &gDefaultParticleDescriptor, 0, 1, 0x11, gBattleAnimCurrentAnchor, BattleAnim_GetSlimeVariantIndex(), 0);
}

void ParticleEffect_PaletteMultiBurst(void) {
    s16 sp4E;
    s16 sp44;
    s16 sp4A;

    sp4E = BattleAnim_GetSlimeVariantIndex();
    sp44 = BattleAnim_GetMoveKeyedTintRampParam();
    sp4A = BattleAnim_GetMoveKeyedTrailVariantParam();

    BattleAnim_SpawnOwnerModelTintRampDetach(4, sp44, 0, 0xFF, 0x10);
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_RunSlimePuddle, &gDefaultParticleDescriptor, 0, 1, 0xA, 0, sp4E, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(4, BattleAnim_RunSlimePuddle, &gDefaultParticleDescriptor, 0, 1, 0xA, 1, sp4E, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(8, BattleAnim_RunSlimePuddle, &gDefaultParticleDescriptor, 0, 1, 0xA, 2, sp4E, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(0xC, BattleAnim_RunSlimePuddle, &gDefaultParticleDescriptor, 0, 1, 0xA, 3, sp4E, 0);
    BattleAnim_SpawnOwnerModelTintRampDetach(0x28, sp44, 0xFF, 0, 0x10);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(6, 4, 0xA, BattleAnim_CallbackSharedAnimatedVerticalFade, &gBattleAnimParticleDescriptors[0x3D], 0, 1, 9, 0, sp4A, 0);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(7, 8, 5, BattleAnim_CallbackSharedAnimatedVerticalFade, &gBattleAnimParticleDescriptors[0x3D], 0, 1, 9, 0, sp4A, 0);
}

f32 func_8215AEA4(Particle* arg0) {
    f32 sp1C = 0.5f;

    switch (BattleAnim_GetOwnerSpecies(arg0->pokemon)) {
        case 0x5F:
            sp1C = 0.3f;
            break;

        case 0x82:
            sp1C = 0.25f;
            break;

        case 0x83:
            sp1C = 0.4f;
            break;
    }
    return sp1C;
}

void Gfx_ParticleTextureTileCallback(Gfx* arg0, arg1_func_8434E21C* arg1, UNUSED u16 arg2) {
    BattleAnim_GetOwnerContextParticle(D_8006049C);
    arg0 = BattleAnim_BuildAnimatedTileDisplayListFromStruct(arg0, arg1, 0x20, 5, 0, 0, 1, 1, 0, -3, 1, 1);

    gSPEndDisplayList(arg0++);
}

void Gfx_ParticleTextureTileAllocCallback(s32 arg0, arg1_func_84344CE8* arg1) {
    if (arg0 == 2) {
        arg1->unk_18 = Gfx_AllocDisplayList(sizeof(Gfx) * 30);
        Gfx_ParticleTextureTileCallback(arg1->unk_18, arg1->unk_14, D_80060484);
    }
}

void Gfx_ParticleRedPrimCallback(Gfx* arg0, UNUSED arg1_func_8434E21C* arg1, UNUSED u16 arg2) {
    Particle* temp_v0 = BattleAnim_GetOwnerContextParticle(D_8006049C);

    gDPPipeSync(arg0++);

    gDPSetPrimColor(arg0++, 0, 0, 255, 0, 0, temp_v0->prim_a);
    gSPEndDisplayList(arg0++);
}

void Gfx_ParticleRedPrimAllocCallback(s32 arg0, arg1_func_84344CE8* arg1) {
    if (arg0 == 2) {
        arg1->unk_18 = Gfx_AllocDisplayList(sizeof(Gfx) * 30);
        Gfx_ParticleRedPrimCallback(arg1->unk_18, arg1->unk_14, D_80060484);
    }
}

/**
 * @unverified Name from Stadium 1.
 */
void BattleAnim_InitializeGlareLeerUse(void) {
    BattleAnim_SpawnGlobalTintColorFadeDetach(0, 0x10, 6);
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_RunScaryEyes, &gDefaultParticleDescriptor, 0x64, 1, 0xB, 0, 3, 6);
}

/**
 * initializes using hyper beam
 * @unverified Name and comment from Stadium 1.
 */
void BattleAnim_InitializeHyperBeamUseSequence(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_CallbackInitModelAnimWait, &gDefaultParticleDescriptor, 0, 1, 0xA, 0, 0x26, 0);
}

/**
 * @unverified Name from Stadium 1.
 */
void BattleAnim_InitializeEarthquakeFissureUse(void) {
    UNUSED s16 pad; // FAKE: stack padding
    s16 sp34;

    switch (BattleAnim_GetQueuedMoveId()) {
        case 0x59:
            sp34 = 0xE;
            break;

        case 0x5A:
            sp34 = 0;
            break;
    }

    BattleAnim_SpawnGlobalTintColorFadeDetach(0, 0x10, sp34);
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_CallbackInitModelAnimWait, &gDefaultParticleDescriptor, 0, 1, 0xA, 0, 0x26, 0);
}

/**
 * @unverified Name from Stadium 1.
 */
void BattleAnim_InitializeEarthquakeFissureHit(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(6, BattleAnim_InitializeParticleModel, &gDefaultParticleDescriptor, 0, 1, 0xA, 0, 4, 2);
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_CallbackInitModelAnimWait, &gDefaultParticleDescriptor, 0, 1, 0xA, 0, 5, 0);
    BattleAnim_InitializeEarthquakeFissureHitSequence();
}

/**
 * @unverified Name from Stadium 1.
 */
void BattleAnim_InitializeEarthquakeHit(void) {
    BattleAnim_InitializeEarthquakeFissureHit();
}

/**
 * @unverified Name from Stadium 1, matched by code similarity.
 */
void BattleAnim_InitializeDefenseCurlUse(void) {
    func_8213BC00(4, 8, 0, 0xFF, 0x40);
    func_8213C1BC(8);
    func_8213B560(0xC, &func_82152FB0, &D_8218E580, 0, 1, 0xE, 0, 6, 0);
    func_82168504();
}

/**
 * @unverified Name from Stadium 1, matched by code similarity.
 */
void BattleAnim_InitializeSharpenUse(void) {
    func_8213BC00(6, 8, 0, 0xFF, 0x40);
    func_8213C1BC(0xA);
    func_8213B560(0xC, &func_82152FB0, &D_8218E580, 0, 1, 0xA, 0, 7, 0);
    func_82168504();
}

void Gfx_PokemonPortraitCallback(Gfx* arg0, u8 arg1, UNUSED u16 arg2) {
    u8* var_a3;
    s32 idx = arg1 * 0xB48;

    if (BattleScene_GetParticipantSideIndex(BattleAnim_GetOwnerContextParticle(D_8006049C)->pokemon) == 0) {
        var_a3 = sSide1PokemonThumbnailImage + idx;
    } else {
        var_a3 = sSide2PokemonThumbnailImage + idx;
    }

    gDPLoadTextureTile(arg0++, var_a3, G_IM_FMT_RGBA, G_IM_SIZ_16b, 76, 0, 0, 0, 75, 18, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                       G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

    gSPEndDisplayList(arg0++);
}

void Gfx_PokemonPortraitAllocCallback(s32 arg0, arg1_func_84344CE8* arg1) {
    if (arg0 == 2) {
        arg1->unk_18 = Gfx_AllocDisplayList(sizeof(Gfx) * 30);
        Gfx_PokemonPortraitCallback(arg1->unk_18, arg1->unk_14, D_80060484);
    }
}

/**
 * Moves: Double-Edge (use), Hi Jump Kick (use), Quick Attack (use), Skull Bash (use), Take Down (use)
 * TODO: Human contributor add screenshot
 * @unverified Name and comment from Stadium 1.
 */
void BattleAnim_InitializeSpeedLines(void) {
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0, 8, 6, BattleAnim_CallbackInitModelAnimWait, &gDefaultParticleDescriptor, 0, 1, 9, 0, 8, 0);
}

void func_8215B5B8(void) {
    func_8213B644(0, 0x20, 0xE);
    func_8215B558();
}

/**
 * @unverified Name from Stadium 1.
 */
void BattleAnim_InitializeWithdrawUse(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_InitializeParticleModel, &gDefaultParticleDescriptor, 0, 1, 0xE, 0, 9, 0);
}

void func_8215B63C(void) {
    if (func_8213C4D0(0x5E) == 0) {
        func_8213B560(0, &func_82152F44, &D_8218E580, 0, 1, 0x10, (s32) D_8219A80A, 0xA, 0);
    }
}

f32 func_8215B6A4(Particle* arg0) {
    f32 a = 0.0f;
    f32 b = 1.0f;

    switch (BattleAnim_GetOwnerSpecies(arg0->pokemon)) {
        case 0x5F:
            Particle_Field38_AddXZFromField94YOffsetMinus90_0901C(arg0, 15.0f);
            a = 10.0f;
            b = 0.5f;
            break;
        case 0x82:
            a = 10.0f;
            b = 0.4f;
            break;
        case 0x83:
            a = 10.0f;
            b = 0.4f;
            break;
    }
    Particle_Field38_AddYScaled_08E90(arg0, a);
    return b;
}

/**
 * @unverified Name from Stadium 1, matched by code similarity.
 */
void BattleAnim_InitializeLovelyKissUse(void) {
    func_8213B560(0, &func_82152F44, &D_8218E580, 0, 1, 0xB, 0, 0xB, 0);
    func_8213B644(0x2A, 0x10, 0x15);
}

/**
 * @unverified Name from Stadium 1, matched by code similarity.
 */
void BattleAnim_InitializeLovelyKissHit(void) {
    func_8213BC7C(0, 1, 0x16, 0xFF, 0, 8);
    func_8213B560(0, &func_82152F44, &D_8218E580, 0, 1, 9, 0, 0xC, 0);
}

void func_8215B83C(s8 *arg0) {
    s16 sp26;
    s32 temp_v0;

    sp26 = func_8213C46C();
    temp_v0 = func_82136AC0(arg0);
    M2C_FIELD(arg0, s32 *, 0x14) = temp_v0;
    if (temp_v0 != 0) {
        if ((sp26 == 0) || (sp26 == 1)) {
            func_82136D58(M2C_FIELD(arg0, s32 *, 0x14), 0x8C);
        } else if ((sp26 == 2) || (sp26 == 3)) {
            func_82136D58(M2C_FIELD(arg0, s32 *, 0x14), 0x8E);
        } else {
            func_82136D58(M2C_FIELD(arg0, s32 *, 0x14), 0x8D);
        }
        func_821401D4(arg0, 0x3F800000);
        func_8214050C(arg0, 0);
        func_8213C9D0(arg0);
        return;
    }
    func_8213C938(arg0);
}

/**
 * Used to make the overlays for mediate, night shade, and dream eater
 * @unverified Name and comment from Stadium 1.
 */
void BattleAnim_RunPsychedelicOverlay(Particle* arg0) {
    u32 temp_v0 = Particle_FieldCD_GetU8_0C048(arg0);

    switch (arg0->unk_B2) {
        case 1:
            BattleAnim_CallbackStartEffects95To97EndEffects62And63ModelFadeIn_InitParticle(arg0);
            break;

        case 2:
            if ((temp_v0 == 0) || ((s32)temp_v0 == 1)) {
                Particle_PrimAlpha_ApproachAndStepState_0BC5C(arg0, 0x80, 8);
            } else if (temp_v0 == 3) {
                Particle_PrimAlpha_ApproachAndStepState_0BC5C(arg0, 0xFF, 0xFF);
            } else {
                Particle_PrimAlpha_ApproachAndStepState_0BC5C(arg0, 0xFF, 4);
            }
            break;
    }
}

void Gfx_PaletteParticleDL(Gfx* arg0, u8* arg1, UNUSED u16 arg2) {
    u8* a1;
    Particle* spC8;
    u8 var_t0;
    s16 spC4;
    s16 spC2;
    s16 spC0;
    s16 spBE;
    s16 var_a1;
    s16 var_a2;
    s16 var_a3;
    s16 var_s1;
    UNUSED s16 pad2; // FAKE: stack padding
    s16 spB2;
    s16 spB0;
    s16 spAE;
    s16 spAC;
    u16 temp_v0_2;
    s16 var_t2;
    s16 var_t1;

    spC8 = BattleAnim_GetOwnerContextParticle(D_8006049C);
    temp_v0_2 = Particle_FieldCD_GetU8_0C048(spC8);
    var_s1 = 0x20;
    var_t1 = 5;
    var_t2 = 5;
    var_a3 = 0;
    var_a1 = 0;
    var_a2 = 0;
    var_t0 = spC8->prim_a;

    switch (temp_v0_2) {
        case 0:
            spC4 = -1;
            spC2 = -1;
            spC0 = 1;
            spBE = -1;
            spB2 = 0xF;
            spB0 = 0;
            spAE = 0xE;
            spAC = 0xF;
            break;

        case 1:
            spC4 = -1;
            spC2 = 1;
            spC0 = 1;
            spBE = 1;
            spB2 = 0xF;
            spB0 = 0;
            spAE = 0xE;
            spAC = 0xF;
            break;

        case 2:
            spC4 = -2;
            spC2 = 2;
            spC0 = 2;
            var_a3 = 0xFF;
            spBE = 3;
            spB2 = 0xC;
            spB0 = 1;
            spAE = 0xC;
            spAC = 0;
            break;

        case 3:
            spC4 = -2;
            spC2 = -2;
            spC0 = 2;
            var_a3 = 0xFF;
            spBE = -3;
            spB2 = 0xC;
            spB0 = 1;
            spAE = 0xC;
            spAC = 0;
            break;

        case 4:
            var_a2 = 0xFF;
            var_a1 = 0x9B;
            spC4 = 1;
            spC2 = 1;
            spC0 = -1;
            spBE = -1;
            spB2 = 0xC;
            spB0 = 1;
            spAE = 0xC;
            spAC = 0;

            break;

        case 5:
            spC0 = -0xA;
            spBE = -0xF;
            spC4 = 0;
            spC2 = 0;
            spB2 = 0xF;
            spB0 = 1;
            spAE = 0xF;
            spAC = 1;
            var_a2 = 0xFF;
            var_a1 = 0xFF;
            var_a3 = 0xFF;
            var_t0 = 0x32;
            break;

        case 6:
            spC4 = 2;
            spC2 = -1;
            spC0 = -2;
            spBE = -2;
            spB2 = 0xD;
            spB0 = 0xE;
            spAE = 0xC;
            spAC = 0xE;
            var_a2 = 0xFF;
            var_a1 = 0xFF;
            var_a3 = 0xFF;
            var_s1 = 0x40;
            var_t1 = 6;
            var_t2 = 6;
            break;

        case 7:
            spC4 = 1;
            spC2 = 1;
            spC0 = -1;
            spBE = -1;
            spB2 = 0xD;
            spB0 = 0xF;
            spAE = 0xF;
            spAC = 0xE;
            var_a2 = 0xFF;
            var_a3 = 0x80;
            break;

        case 8:
            spC4 = 1;
            spC2 = 1;
            spC0 = -1;
            spBE = -1;
            spB2 = 0xD;
            spB0 = 0xF;
            spAE = 0xF;
            spAC = 0xE;
            var_a1 = 0xFF;
            var_a3 = 0xFF;
            break;

        case 9:
            spC4 = 1;
            spC2 = 1;
            spC0 = -1;
            spBE = -1;
            spB2 = 0xD;
            spB0 = 0xF;
            spAE = 0xF;
            spAC = 0xE;
            var_a2 = 0x64;
            var_a1 = 0xFF;
            break;

        case 10:
            spC4 = -1;
            spC2 = -1;
            spC0 = 1;
            spBE = -1;
            spB2 = 0xD;
            spB0 = 0;
            spAE = 0xC;
            spAC = 0xF;
            var_a2 = 0xC8;
            var_a1 = 0x64;
            break;

        case 11:
            spC4 = -1;
            spC2 = -1;
            spC0 = 1;
            spBE = -1;
            spB2 = 0xD;
            spB0 = 0;
            spAE = 0xC;
            spAC = 0xF;
            var_a1 = 0xFF;
            var_a3 = 0xFF;
            break;

        case 12:
            spC4 = -1;
            spC2 = -1;
            spC0 = 1;
            spBE = -1;
            spB2 = 0xD;
            spB0 = 0;
            spAE = 0xC;
            spAC = 0xF;
            var_a2 = 0xC8;
            var_a1 = 0xFF;
            break;

        case 13:
            spC4 = -1;
            spC2 = -1;
            spC0 = 1;
            spBE = -1;
            spB2 = 0xD;
            spB0 = 0;
            spAE = 0xC;
            spAC = 0xF;
            var_a2 = 0xFF;
            break;
    }

    a1 = arg1;

    gDPPipeSync(arg0++);
    gDPSetPrimColor(arg0++, 0, 0x80, var_a2, var_a1, var_a3, var_t0);

    gDPLoadTextureTile_4b(arg0++, arg1, G_IM_FMT_I, var_s1, var_s1, 0, 0, var_s1 - 1, var_s1 - 1, 0,
                          G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, var_t2, var_t1, spB2, spB0);

    ParticleGfx_SetAnimatedTileSizeOnList(arg0++, spC4, spC2, var_s1, var_s1);

    gDPLoadMultiTile_4b(arg0++, a1, 0x0100, 1, G_IM_FMT_I, var_s1, var_s1, 0, 0, var_s1 - 1, var_s1 - 1, 0,
                        G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, var_t2, var_t1, spAE, spAC);

    ParticleGfx_SetAnimatedAuxTileSizeOnList(arg0++, spC0, spBE, var_s1, var_s1);

    gSPEndDisplayList(arg0++);
}

void Gfx_PaletteParticleDLCallback(s32 arg0, arg1_func_84344CE8* arg1) {
    if (arg0 == 2) {
        arg1->unk_18 = Gfx_AllocDisplayList(sizeof(Gfx) * 30);
        Gfx_PaletteParticleDL(arg1->unk_18, arg1->unk_14, D_80060484);
    }
}

/**
 * @unverified Name from Stadium 1, matched by code similarity.
 */
void BattleAnim_InitializeDreamEaterUse(void) {
    func_8213B560(0, &func_8215B904, &D_8218E580, 0, 1, 0xC, 0, 0, 0);
    func_8213B560(0, &func_82153040, &D_8218E580, 0, 1, 9, 0, 0xD, 0);
    func_8213B560(4, &func_82153040, &D_8218E580, 0, 1, 9, 1, 0xD, 0);
    func_8213B560(8, &func_82153040, &D_8218E580, 0, 1, 9, 2, 0xD, 0);
    func_8213B560(0xC, &func_82153040, &D_8218E580, 0, 1, 9, 0, 0xD, 0);
    func_8213B560(0x10, &func_82153040, &D_8218E580, 0, 1, 9, 1, 0xD, 0);
    func_8213B560(0x14, &func_82153040, &D_8218E580, 0, 1, 9, 2, 0xD, 0);
    func_8213B560(0x18, &func_82153040, &D_8218E580, 0, 1, 9, 0, 0xD, 0);
    func_8213B560(0x1C, &func_82153040, &D_8218E580, 0, 1, 9, 1, 0xD, 0);
    func_8213B560(0x20, &func_82153040, &D_8218E580, 0, 1, 9, 2, 0xD, 0);
    func_8213B644(0, 8, 0x33);
}

/**
 * @unverified Name from Stadium 1.
 */
void BattleAnim_InitializeDreamEaterHit(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_RunPsychedelicOverlay, &gDefaultParticleDescriptor, 0, 1, 0xC, 1, 0, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_CallbackInitModelAnimWait, &gDefaultParticleDescriptor, 0, 1, 9, 0, 0xD, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(4, BattleAnim_CallbackInitModelAnimWait, &gDefaultParticleDescriptor, 0, 1, 9, 1, 0xD, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(8, BattleAnim_CallbackInitModelAnimWait, &gDefaultParticleDescriptor, 0, 1, 9, 2, 0xD, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(0xC, BattleAnim_CallbackInitModelAnimWait, &gDefaultParticleDescriptor, 0, 1, 9, 0, 0xD, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(0x10, BattleAnim_CallbackInitModelAnimWait, &gDefaultParticleDescriptor, 0, 1, 9, 1, 0xD, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(0x14, BattleAnim_CallbackInitModelAnimWait, &gDefaultParticleDescriptor, 0, 1, 9, 2, 0xD, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(0x18, BattleAnim_CallbackInitModelAnimWait, &gDefaultParticleDescriptor, 0, 1, 9, 0, 0xD, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(0x1C, BattleAnim_CallbackInitModelAnimWait, &gDefaultParticleDescriptor, 0, 1, 9, 1, 0xD, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(0x20, BattleAnim_CallbackInitModelAnimWait, &gDefaultParticleDescriptor, 0, 1, 9, 2, 0xD, 0);
}

/**
 * Moves: Absorb (use), Leech Life (use), Mega Drain (use)
 * TODO: Human contributor add screenshot
 * @unverified Name and comment from Stadium 1.
 */
void BattleAnim_CreateDrainingMoveOverlay(void) {
    switch (BattleAnim_GetQueuedMoveId()) {
        case 0x8D:
            BattleAnim_SpawnGlobalTintColorFadeDetach(0, 0x10, 6);
            BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_RunFillScreenOverlay, &gDefaultParticleDescriptor, 0x80, 1, 0xC, 0xD, 0x1A, 0x20);
            break;

        case 0x47:
            BattleAnim_SpawnGlobalTintColorFadeDetach(0, 0x10, 0x37);
            BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_RunFillScreenOverlay, &gDefaultParticleDescriptor, 0x80, 1, 0xC, 0xB, 0x1A, 0x20);
            break;

        case 0x48:
            BattleAnim_SpawnGlobalTintColorFadeDetach(0, 0x10, 0x1F);
            BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_RunFillScreenOverlay, &gDefaultParticleDescriptor, 0x80, 1, 0xC, 0xC, 0x1A, 0x20);
            break;
    }
}

/**
 * @unverified Name from Stadium 1.
 */
void BattleAnim_InitializeMeditateUse(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_RunPsychedelicOverlay, &gDefaultParticleDescriptor, 0, 1, 0xC, 4, 0, 0);
}

/**
 * @unverified Name from Stadium 1, matched by code similarity.
 */
void BattleAnim_InitializeNightShadeUse(void) {
    func_8213B560(0, &func_8215B904, &D_8218E580, 0, 1, 0xC, 2, 0, 0);
    func_8213B644(0, 8, 0);
    func_8213B464(0x40);
    func_8213B720(0, 2, 0x10, 8);
}

/**
 * Moves: Night Shade (hit)
 * TODO: Human contributor add screenshot
 * @unverified Name and comment from Stadium 1, matched by code similarity.
 */
void BattleAnim_InitializeNightShadeHit(void) {
    func_8213B720(0, 2, 0x10, 8);
    func_8213BC00(4, 8, 0xFF, 0, 8);
    func_8213B560(0, &func_8215B904, &D_8218E580, 0, 1, 0xC, 3, 0, 0);
    func_8213B5D8(4, 4, 4, &func_82162C68, &D_8218E728, 0, 3, 9, 0, 0x18, 0xD);
}

/**
 * @unverified Name from Stadium 1.
 */
void BattleAnim_SetupConfuseRayUseSpotlight(Particle* arg0) {
    arg0->displayObject = BattleAnim_AllocOwnerDisplayContext(arg0);
    if (arg0->displayObject != NULL) {
        BattleAnim_InitModelWithAnim(arg0->displayObject, 0x42, 0xC2);
        Particle_Field1C_SetScaled_0B938(arg0, 1.0f);
        ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, 0x23);
        Particle_SetPrimAlpha(arg0, 0);
        Particle_FieldAE_SetS16_0BF4C(arg0, 0);
        Particle_AdvanceLifecycle(arg0);
    } else {
        Particle_DisableAndDetach(arg0);
    }
}

void func_8215C984(s8 *arg0) {
    s16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_8215C8FC(arg0);
        break;
    case 2:
        func_82140518(arg0, 0xFF, 8);
        func_8214083C(arg0, 0xC8, 6);
        break;
    }
    func_8213EAD4(arg0, (s16) (func_821385C0() + 0x8000));
}

/**
 * @unverified Name from Stadium 1.
 */
void BattleAnim_SetupConfuseRayHitSpotlight(Particle* arg0) {
    arg0->displayObject = BattleAnim_AllocOwnerDisplayContext(arg0);
    if (arg0->displayObject != NULL) {
        BattleAnim_InitModelWithAnim(arg0->displayObject, 0x42, 0xC2);
        BattleAnim_SetModelAnimFrame(arg0->displayObject, 0x28);
        Particle_Field1C_SetScaled_0B938(arg0, 1.0f);
        ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, 0x23);
        Particle_FieldAE_SetS16_0BF4C(arg0, 0xFF);
        Particle_AdvanceLifecycle(arg0);
    } else {
        Particle_DisableAndDetach(arg0);
    }
}

void func_8215CA9C(s8 *arg0) {
    if (M2C_FIELD(arg0, s16 *, 0xAE) == 1) {
        func_8215CA14();
    }
    func_8213EAD4(arg0, (s16) (func_821385C0() + 0x8000));
}

void Gfx_WaterAnimPrimEnvDL(Gfx* arg0, u8 arg1, UNUSED u16 arg2) {
    Particle* temp_v0 = BattleAnim_GetOwnerContextParticle(D_8006049C);

    switch (arg1) {
        case 0:
            gDPPipeSync(arg0++);
            gDPSetPrimColor(arg0++, 0, 0, temp_v0->prim_r, temp_v0->prim_g, temp_v0->prim_b, temp_v0->prim_a);
            break;

        case 1:
            gDPPipeSync(arg0++);
            gDPSetPrimColor(arg0++, 0, 0, temp_v0->prim_r, temp_v0->prim_g, temp_v0->prim_b, temp_v0->unk_AE);
            break;
    }

    gDPSetEnvColor(arg0++, temp_v0->env_r, temp_v0->env_g, temp_v0->env_b, 0);
    gDPSetCombineLERP(arg0++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED,
                      0, 0, 0, COMBINED);

    gSPEndDisplayList(arg0++);
}

void Gfx_WaterAnimPrimEnvDLCallback(s32 arg0, arg1_func_84344CE8* arg1) {
    if (arg0 == 2) {
        arg1->unk_18 = Gfx_AllocDisplayList(sizeof(Gfx) * 30);
        Gfx_WaterAnimPrimEnvDL(arg1->unk_18, arg1->unk_14, D_80060484);
    }
}

void ParticleEffect_WaterAnimBurst(void) {
    BattleAnim_SpawnGlobalTintColorFadeDetach(0, 8, 3);
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_CallbackStartEffects21And93ModelAlphaAnchorFollow, &gDefaultParticleDescriptor, 0, 1, 0xA, 0, 0, 0);
}

void func_8215CCF0(void) {
    func_8213B644(0x10, 0x10, 8);
}

/**
 * @unverified Name from Stadium 1, matched by code similarity.
 */
void BattleAnim_InitializeConfuseRayUse(void) {
    func_8213B560(0, &func_8215C984, &D_8218E580, 0, 1, 0xA, 0, 0, 0);
    func_8213B644(0, 0x20, 3);
    func_8213BC00(8, 8, 0, 0xFF, 0x40);
    func_8213B878(0xC, 5, 0x10, 8);
    func_8213B560(0xC, &func_82162C68, &D_8218E728, 0, 4, 9, 0, 0x18, 0xD);
    func_8213B464(0x21);
    func_8213B720(0, 0, 0x10, 8);
    func_8213BC00(0, 8, 0xFF, 0, 0x10);
}

/**
 * Moves: Confuse Ray (hit)
 * TODO: Human contributor add screenshot
 * @unverified Name and comment from Stadium 1, matched by code similarity.
 */
void BattleAnim_InitializeConfuseRayHit(void) {
    func_8213B560(0, &func_8215CA9C, &D_8218E580, 0, 1, 0xA, 0, 0, 0);
    func_8213B720(0, 0, 0x10, 8);
    func_8213B644(0, 0x20, 3);
    func_8213BC00(8, 8, 0, 0xFF, 0x40);
    func_8213B560(0xC, &func_82162C68, &D_8218E728, 0, 4, 9, 0, 0x18, 0xD);
    func_8213B464(0x21);
    func_8213BC00(0, 8, 0xFF, 0, 0x10);
}

void Gfx_WaterAnimDL(Gfx* arg0, u8* arg1, UNUSED u16 arg2) {
    Particle* temp_v0 = BattleAnim_GetOwnerContextParticle(D_8006049C);

    gDPPipeSync(arg0++);
    gDPSetPrimColor(arg0++, 0, 0x80, 255, 255, 255, temp_v0->prim_a);

    gDPLoadTextureTile_4b(arg0++, arg1, G_IM_FMT_I, 32, 0, 0, 0, 31, 31, 0, G_TX_NOMIRROR | G_TX_WRAP,
                          G_TX_NOMIRROR | G_TX_WRAP, 5, 5, 14, 15);

    ParticleGfx_SetPartiallyAnimatedTileSize(arg0++, -0xB, -8, 0x20, 0x20);

    gDPLoadMultiTile_4b(arg0++, arg1, 0x0100, 1, G_IM_FMT_I, 32, 0, 0, 0, 31, 31, 0, G_TX_NOMIRROR | G_TX_WRAP,
                        G_TX_NOMIRROR | G_TX_WRAP, 5, 5, 13, 15);

    ParticleGfx_SetPartiallyAnimatedAuxTileSize(arg0++, 0x35, -4, 0x20, 0x20);

    gSPEndDisplayList(arg0++);
}

void Gfx_WaterAnimDLCallback(s32 arg0, arg1_func_84344CE8* arg1) {
    if (arg0 == 2) {
        arg1->unk_18 = Gfx_AllocDisplayList(sizeof(Gfx) * 30);
        Gfx_WaterAnimDL(arg1->unk_18, arg1->unk_14, D_80060484);
    }
}

void ParticleEffect_BasicMultiBurst(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_RunFillScreenOverlay, &D_8218E580, 0xFF, 1, 0xC, 0, 0xE, 8);
    BattleAnim_AddSpawnDelay(4);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0, 4, 0x10, BattleAnim_CallbackSharedAnimatedVerticalFade, &D_8218E7D0, 0, 2, 0xE, 0, 0x33, 3);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0, 4, 0x10, BattleAnim_CallbackSharedAnimatedVerticalFade, &D_8218E650, 0, 2, 0xE, 0, 0xC, 3);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0, 4, 0x10, BattleAnim_CallbackSharedAnimatedVerticalFade, &D_8218E5F8, 0, 2, 0xE, 0, 0xC, 3);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0, 8, 5, BattleAnim_CallbackSharedAnimatedVerticalFade, &D_8218E5D8, 0, 2, 0xE, 0, 0xC, 4);
}

void func_8215D31C(void) {
    func_8213B560(0, &func_821530F4, &D_8218E580, 0xFF, 1, 0xC, 0, 0xF, 0x40);
    func_8214DA90();
    func_8213B464(0x10);
    func_8213B5D8(0, 4, 5, &func_82164AD0, &D_8218E5D8, 0, 1, 0xE, 0, 0xC, 4);
}

void ParticleEffect_BasicMultiBurstDelayedSprayOnly(void) {
    BattleAnim_AddSpawnDelay(0x41);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0, 4, 0x20, BattleAnim_CallbackSharedAnimatedVerticalFade, &D_8218E7D0, 0, 2, 7, 0, 0x33, 8);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0, 4, 0x20, BattleAnim_CallbackSharedAnimatedVerticalFade, &D_8218E650, 0, 2, 7, 0, 0xC, 8);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0, 4, 0x20, BattleAnim_CallbackSharedAnimatedVerticalFade, &D_8218E5F8, 0, 2, 7, 0, 0xC, 8);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0, 8, 0xA, BattleAnim_CallbackSharedAnimatedVerticalFade, &D_8218E5D8, 0, 2, 7, 0, 0xC, 4);
}

/**
 * Moves: Surf (hit)
 * TODO: Human contributor add screenshot
 * @unverified Name and comment from Stadium 1, matched by code similarity.
 */
void BattleAnim_InitializeSurfHit(void) {
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0, 4, 4, BattleAnim_CallbackEndEffect16MultiDescriptorAnimatedFallFade, &D_8218E7D0, 0, 3, 0xE, 0, 0x33, 0xC);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0, 4, 4, BattleAnim_CallbackEndEffect16MultiDescriptorAnimatedFallFade, &D_8218E650, 0, 3, 0xE, 0, 0xC, 0xC);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0, 4, 4, BattleAnim_CallbackEndEffect16MultiDescriptorAnimatedFallFade, &D_8218E5F8, 0, 3, 0xE, 0, 0xC, 0xC);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0, 4, 4, BattleAnim_CallbackEndEffect16MultiDescriptorAnimatedFallFade, &D_8218E5D8, 0, 3, 0xE, 0, 0xC, 4);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0, 2, 0xC, BattleAnim_CallbackEndEffect16Descriptor45DelayedRotatingMotion, &D_8218E7A8, 0, 4, 0x11, 7, 0x33, 0);
}

/**
 * @unverified Name from Stadium 1, matched by code similarity.
 */
void BattleAnim_InitializeCrabhammerUse(void) {
    func_8213B560(0, &func_82152F44, &D_8218E580, 0, 1, 0x13, (s32) D_8219A80A, 0x10, 0);
    func_8213B720(0x22, 0, 0x10, 8);
}

/**
 * @unverified Name from Stadium 1.
 */
void BattleAnim_SetupBarrageEffect(Particle* arg0) {
    Particle_Field1C_SetScaled_0B938(arg0, 0.2f);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, 0x33);
    Particle_SetPrimAlpha(arg0, 0xFF);
    Particle_AdvanceLifecycle(arg0);
}

void func_8215D76C(s8 *arg0) {
    s16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_8215D724(arg0);
        break;
    case 2:
        func_8213CCEC(arg0, 0, 7, 1, 2, 0);
        func_82140518(arg0, 0x20, 0x40);
        break;
    case 3:
        func_8213C938(arg0);
        break;
    }
    func_82140228(arg0, 0x3F000000, 0x3DCCCCCD);
}

/**
 * @unverified Name from Stadium 1.
 */
void BattleAnim_SetupBarrageUseEffect1(Particle* arg0) {
    Particle_FieldAC_GetS16_0C038(arg0);
    Particle_Field1C_SetScaled_0B938(arg0, 0.3f);
    Particle_Field94_AddVec_0A52C(arg0, -0x1000, 0, 0);
    Particle_FieldA0_SetY_0A414(arg0, BattleAnim_GetParticleAngleYToTertiaryOwner(arg0));
    Particle_Field9A_SetY_0A3D8(arg0, 0x80);
    Particle_DisableRendering(arg0);
    Particle_AdvanceLifecycle(arg0);
}

void BattleAnim_CallbackStartEffect101ModelBurstEmitter(Particle* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            BattleAnim_SetupBarrageUseEffect1(arg0);
            break;

        case 2:
            if (Particle_FieldA6_DecrementToZeroStep1AndStepState_0BDD0(arg0) != 0) {
                arg0->displayObject = BattleAnim_AllocOwnerDisplayContext(arg0);
                BattleAnim_InitModelWithAnim(arg0->displayObject, 0xA0, 0xA1);
                Particle_EnableRendering(arg0);
            }
            break;

        case 3:
            if (Particle_TickDelayAndAdvanceLifecycle(arg0, 0xA) != 0) {
                Particle_Field74_SetScaled_0AD8C(arg0, 8.0f);
                BattleAnim_EmitParticleBurst(arg0, BattleAnim_CallbackStartEffect101EndEffect65Descriptor4ABurstChild, &D_8218E7D0, 1);
                BattleAnim_EmitParticleBurstWithMetadata(arg0, BattleAnim_RunBarrageUseEffect2, &D_8218E770, 0xC, 0x33, 0);
            }
            break;

        case 4:
            BattleAnim_EmitParticleBurst(arg0, BattleAnim_CallbackStartEffect101EndEffect65Descriptor4ABurstChild, &D_8218E7D0, 1);
            Particle_ApproachRotationXTo(arg0, 0x1000, 0x200);
            Particle_ApproachRotationTargetY(arg0);
            Particle_TickDelayAndAdvanceLifecycle(arg0, 0xF);
            break;

        case 5:
            Particle_DisableAndDetach(arg0);
            break;
    }

    if (Particle_IsRenderingEnabled(arg0) != 0) {
        Particle_AddVelocityFromRotationTemplate1(arg0);
    }
}

/**
 * @unverified Name from Stadium 1.
 */
void BattleAnim_InitializeBarrageUse(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_CallbackStartEffect101ModelBurstEmitter, &gDefaultParticleDescriptor, 0, 1, 0x11, gBattleAnimCurrentAnchor, 0, 0);
}

/**
 * @unverified Name from Stadium 1.
 */
void BattleAnim_SetupBarrageHitEffect(Particle* arg0) {
    Particle_FieldAC_GetS16_0C038(arg0);
    Particle_Field1C_SetScaled_0B938(arg0, 0.4f);
    Particle_Field38_SetYScaled_08CA0(arg0, 15.0f);
    Particle_Field38_AddXZFromField94Y_08ED0(arg0, 50.0f);
    Particle_Field94_AddVec_0A52C(arg0, 0x800, -0x8000, 0);
    Particle_Field74_SetScaled_0AD8C(arg0, 8.0f);
    Particle_AdvanceLifecycle(arg0);
    arg0->displayObject = BattleAnim_AllocOwnerDisplayContext(arg0);
    BattleAnim_InitModel(arg0->displayObject, 0xA0);
}

void func_8215DAEC(s8 *arg0) {
    s16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_8215DA5C(arg0);
        break;
    case 2:
        func_82139E5C(arg0, &func_8215D76C, &D_8218E7D0, 1);
        func_8213EF88(arg0, 0x1000, 0x80);
        func_8213CA80(arg0, 7);
        break;
    case 3:
        func_8213C938(arg0);
        break;
    }
    if (func_8213CB7C(arg0) != 0) {
        func_8213E528(arg0);
    }
}

/**
 * @unverified Name from Stadium 1.
 */
void BattleAnim_InitializeBarrageHit(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_CallbackMove140EndEffect65EmitDescriptor4A, &gDefaultParticleDescriptor, 0, 1, 0x11, gBattleAnimCurrentAnchor, 0, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(5, BattleAnim_RunDefaultHitSpark, &gBattleAnimParticleDescriptors[0x34], 0, 1, 0x11, 9, 0, 6);
    BattleAnim_CreateEffectSlotForCurrentOwner(7, BattleAnim_RunPhysicalHitPurpleSmoke, &gBattleAnimParticleDescriptors[0x3D], 0, 8, 0x11, 9, 0, 0);
}

/**
 * @unverified Name from Stadium 1.
 */
void BattleAnim_SetupPsywaveEffect(Particle* arg0) {
    arg0->displayObject = BattleAnim_AllocOwnerDisplayContext(arg0);
    if (arg0->displayObject != NULL) {
        BattleAnim_InitModel(arg0->displayObject, 0xA2);
        Particle_Field1C_SetScaled_0B938(arg0, 1.0f);
        Particle_SetPrimAlpha(arg0, 0);
        Particle_AdvanceLifecycle(arg0);
    } else {
        Particle_DisableAndDetach(arg0);
    }
}

/**
 * @unverified Name from Stadium 1.
 */
void BattleAnim_RunPsywaveEffect(Particle* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            BattleAnim_SetupPsywaveEffect(arg0);
            break;

        case 2:
            Particle_PrimAlpha_ApproachAndStepState_0BC5C(arg0, 0x80, 8);
            break;
    }
}

void Gfx_SimpleNodeDL(Gfx* arg0, arg1_func_8434E21C* arg1, UNUSED u16 arg2) {
    UNUSED s32 pad; // FAKE: stack padding
    Particle* sp48 = BattleAnim_GetOwnerContextParticle(D_8006049C);
    UNUSED s16 pad2; // FAKE: stack padding
    s16 sp44;
    s16 sp42;

    switch (Particle_FieldCF_GetS16_0C058(sp48)) {
        case 0:
            sp44 = -5;
            sp42 = 3;
            break;

        case 1:
            sp44 = 5;
            sp42 = -3;
            break;
    }

    gDPPipeSync(arg0++);
    gDPSetPrimColor(arg0++, 0, 0x80, 55, 255, 255, sp48->prim_a);

    arg0 = BattleAnim_BuildAnimatedTileDisplayListFromStruct(arg0++, arg1, 0x20, 5, 1, sp44, 0xD, 0xC, -1, sp42, 0xB, 0xD);
    gSPEndDisplayList(arg0++);
}

void Gfx_SimpleNodeDLCallback(s32 arg0, arg1_func_84344CE8* arg1) {
    if (arg0 == 2) {
        arg1->unk_18 = Gfx_AllocDisplayList(sizeof(Gfx) * 30);
        Gfx_SimpleNodeDL(arg1->unk_18, arg1->unk_14, D_80060484);
    }
}

/**
 * @unverified Name from Stadium 1.
 */
void BattleAnim_InitializePsywaveUse(void) {
    BattleAnim_SpawnGlobalTintColorFadeDetach(0, 0x10, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_RunPsywaveEffect, &gDefaultParticleDescriptor, 0, 1, 9, 0, 0, 0);
}

/**
 * @unverified Name from Stadium 1, matched by code similarity.
 */
void BattleAnim_InitializePsywaveHit(void) {
    func_8213BC7C(0, 2, 8, 0xFF, 0, 0x10);
    func_8213B560(0, &func_8215DCE8, &D_8218E580, 0, 1, 9, 0, 1, 0);
    func_8213B5D8(4, 4, 4, &func_82162C68, &D_8218E728, 0, 3, 9, 0, 0x18, 0xD);
}

/**
 * @unverified Name from Stadium 1.
 */
void BattleAnim_RunConfusionPsychicHitEffect(Particle* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            BattleAnim_SelectParticleModelFrames(arg0, 2);
            break;

        case 2:
            Particle_PrimAlpha_ApproachAndStepState_0BC5C(arg0, arg0->unk_A6, Particle_FieldCE_GetS32_0C040(arg0));
            break;

        case 3:
            Particle_TickDelayAndAdvanceLifecycle(arg0, 0x20);
            break;

        case 4:
            Particle_PrimAlpha_ApproachAndStepState_0BC5C(arg0, 0, 0xA);
            break;

        case 5:
            Particle_DisableAndDetach(arg0);
            break;
    }
}

/**
 * @unverified Name from Stadium 1, matched by code similarity.
 */
void BattleAnim_InitializePsychicUse(void) {
    func_8213B644(0, 5, 0);
    func_8213B560(0, &func_821530F4, &D_8218E580, 0xFF, 1, 0xC, 8, 0x18, 5);
    func_8213BC7C(0x32, 1, 8, 0, 0xFF, 0x20);
    func_8213B6AC(0x32, 1, 0x20, 8, 0xFF);
}

/**
 * @unverified Name from Stadium 1, matched by code similarity.
 */
void BattleAnim_InitializeConfusionUse(void) {
    func_8213B644(0, 6, 0);
    func_8213B560(0, &func_821530F4, &D_8218E580, 0xFF, 1, 0xC, 7, 0x17, 6);
    func_8213B6AC(0x32, 1, 0x20, 8, 0xFF);
    func_8213BC7C(0x32, 1, 8, 0, 0xFF, 0x20);
}

void func_8215E1A8(void) {
    func_8213B644(0, 0x40, 0);
    func_8213B560(0, &func_8215DFB4, &D_8218E580, 0xFF, 1, 0xC, 8, 0x18, 0x20);
    func_8213B5D8(4, 4, 4, &func_82162C68, &D_8218E728, 0, 3, 9, 0, 0x18, 0xD);
    func_8213BC00(8, 8, 0, 0xFF, 0x40);
    func_8213B720(0, 0, 0x10, 8);
    func_8213B464(0x21);
    func_8213BC00(0, 8, 0xFF, 0, 4);
    func_8213B644(8, 4, 8);
}

void func_8215E2C4(void) {
    func_8213B644(0, 0x40, 0);
    func_8213B560(0, &func_8215DFB4, &D_8218E580, 0xFF, 1, 0xC, 7, 0x17, 0x20);
    func_8213B5D8(4, 4, 4, &func_82162C68, &D_8218E728, 0, 3, 9, 0, 0x18, 0xD);
    func_8213BC00(8, 8, 0, 0xFF, 0x40);
    func_8213B720(0, 0, 0x10, 8);
    func_8213B464(0x21);
    func_8213BC00(0, 8, 0xFF, 0, 4);
    func_8213B644(8, 4, 8);
}

/**
 * @unverified Name from Stadium 1, matched by code similarity.
 */
void BattleAnim_InitializeFocusEnergyUse(void) {
    BattleAnim_SpawnGlobalTintColorFadeDetach(0, 0x10, 6);
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_RunFillScreenOverlay, &gDefaultParticleDescriptor, 0x80, 1, 0xC, 0xA, 0x1A, 4);
    BattleAnim_SpawnOwnerModelTintPulseDetach(0, 1, 0xA, 0, 0xC8, 3);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0x3C, 4, 0xE, BattleAnim_CallbackSharedAnimatedVerticalFade, &gBattleAnimParticleDescriptors[0x3D], 0, 1, 0x11, 7, 0x33, 7);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0x3D, 8, 7, BattleAnim_CallbackSharedAnimatedVerticalFade, &gBattleAnimParticleDescriptors[0x3D], 0, 1, 0x11, 7, 0x33, 7);
}

/**
 * @unverified Name from Stadium 1.
 */
void BattleAnim_InitializeBideRageUseSequence(void) {
    BattleAnim_SpawnGlobalTintColorFadeDetach(0, 0x20, 6);
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_RunFillScreenOverlay, &gDefaultParticleDescriptor, 0x80, 1, 0xC, 0xA, 0x1A, 0x20);
}

/**
 * @unverified Name from Stadium 1, matched by code similarity.
 */
void BattleAnim_InitializeSkyAttackUse1(void) {
    func_82168844(0xE);
    func_8213B644(0, 2, 0xE);
    func_8213BC00(0, 0xA, 0, 0xC8, 4);
    func_8213BD78(0x32, 0xA, 0x17, 2, 0xC8);
    func_8213B560(0x40, &BattleAnim_RunOscillatingFlameUnderneathPokemon, &D_8218E7F8, 0, 0x20, 7, 0, 0, 0);
}

/**
 * @unverified Name from Stadium 1, matched by code similarity.
 */
void BattleAnim_InitializeSkyAttackUse2(void) {
    func_8213B644(0, 0x20, 6);
    func_8213BC00(0, 0x12, 0, 0x80, 0x10);
    func_8213C0D8(0, 0xFF, 0, 0x10);
    func_8213B560(0, &func_82152FE0, &D_8218E580, 0xFF, 1, 9, (s32) D_8219A80A, 0x12, 0x20);
    func_8213B5D8(0, 1, 0xC, &func_82164AD0, &D_8218E770, 0, 1, 9, 0, 0x16, 5);
}

/**
 * @unverified Name from Stadium 1.
 */
void BattleAnim_InitializeSkyAttackHit(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_CallbackInitModelAnimWait, &gDefaultParticleDescriptor, 0, 1, 9, 0, 0x13, 0);
    BattleAnim_SetSpawnDelay(4);
    BattleAnim_EndEffect71PaletteApproachWithExpandingScaleFades();
}

void ParticleEffect_DrawQuad(Gfx* arg0, arg1_func_8434E21C* arg1, UNUSED u16 arg2) {
    Particle* temp_v0;
    UNUSED s32 pad; // FAKE: stack padding
    s16 var_t2;
    s16 tmp;
    s16 sp82;
    s16 sp80;
    s16 sp7E;
    s16 sp7C;
    s16 sp7A;
    s16 sp78;
    s16 sp76;
    s16 sp74;
    s16 var_s1;
    s16 var_t1;
    UNUSED s16 pad2; // FAKE: stack padding
    s16 var_t5;

    temp_v0 = BattleAnim_GetOwnerContextParticle(D_8006049C);
    var_t1 = 0x96;
    var_t2 = 0xFF;
    var_s1 = 0x20;
    var_t5 = 5;
    tmp = arg1->unk_0A;

    switch (tmp) {
        case 1:
            sp82 = -5;
            sp80 = -0xF;
            sp7E = -0xA;
            sp7C = -0xA;
            sp7A = 0;
            sp78 = 1;
            sp76 = 0;
            sp74 = 1;
            break;

        case 2:
            sp82 = 5;
            sp80 = -0xF;
            sp7E = 0;
            sp7C = -0xA;
            sp7A = 0;
            sp78 = 0xF;
            sp76 = 0;
            sp74 = 0xF;
            break;

        case 3:
            sp82 = 5;
            sp80 = -0xF;
            sp7C = -0xA;
            sp7E = 0;
            sp7A = 1;
            sp78 = 1;
            sp76 = 1;
            sp74 = 1;
            break;

        case 4:
            sp82 = 5;
            sp80 = -0xF;
            sp7E = 0;
            sp7C = -0xA;
            sp7A = 0;
            sp78 = 0;
            sp76 = 0;
            sp74 = 0;
            break;

        case 5:
            sp82 = -5;
            sp80 = -0xA;
            sp7E = 0;
            sp7C = 0;
            sp7A = 1;
            sp78 = 0;
            sp76 = 0;
            sp74 = 0;
            var_t1 = 0x78;
            var_t2 = 0xC8;
            var_s1 = 0x40;
            var_t5 = 6;
            break;

        case 6:
            sp82 = 0;
            sp80 = -0xA;
            sp7E = 0;
            sp7C = 0;
            sp7A = 1;
            sp78 = 1;
            sp76 = 0;
            sp74 = 0;
            var_t1 = 0x78;
            var_t2 = 0xC8;
            var_s1 = 0x40;
            var_t5 = 6;
            break;
    }

    gDPPipeSync(arg0++);
    gDPSetPrimColor(arg0++, 0, var_t1, 255, var_t2, 0, temp_v0->prim_a);

    gDPLoadTextureTile_4b(arg0++, arg1->unk_00, G_IM_FMT_I, 32, 32, 0, 0, 31, 31, 0, G_TX_NOMIRROR | G_TX_WRAP,
                          G_TX_NOMIRROR | G_TX_WRAP, 5, 5, sp7A, sp78);

    ParticleGfx_SetAnimatedTileSizeOnList(arg0++, sp82, sp80, 0x20, 0x20);

    gDPLoadMultiTile_4b(arg0++, arg1->unk_04, 0x0100, 1, G_IM_FMT_I, var_s1, 0, 0, 0, var_s1 - 1, var_s1 - 1, 0,
                        G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, var_t5, var_t5, sp76, sp74);

    ParticleGfx_SetAnimatedAuxTileSizeOnList(arg0++, sp7E, sp7C, var_s1, var_s1);

    gSPEndDisplayList(arg0++);
}

void ParticleEffect_AllocateDisplayList(s32 arg0, arg1_func_84344CE8* arg1) {
    if (arg0 == 2) {
        arg1->unk_18 = Gfx_AllocDisplayList(sizeof(Gfx) * 30);
        ParticleEffect_DrawQuad(arg1->unk_18, arg1->unk_14, D_80060484);
    }
}

/**
 * @unverified Name from Stadium 1.
 */
void BattleAnim_InitializeThunderHitSequence(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_CallbackInitModelAnimWait, &gDefaultParticleDescriptor, 0, 1, 0xE, 5, 0x14, 0);
}

/**
 * @unverified Name from Stadium 1, matched by code similarity.
 */
void BattleAnim_InitializeSolarBeamUse2(void) {
    func_8213B560(0, &func_821530F4, &D_8218E580, 0xBE, 1, 9, 6, 0x15, 2);
    func_8213BC00(8, 8, 0, 0xFF, 4);
    BattleAnim_InitializeSolarBeamUseSequence();
}

void BattleAnim_CallbackEndEffect76DefaultDescriptorModelFade(Particle* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            BattleAnim_SelectParticleModelFrames(arg0, 0);
            Particle_FieldA6_SetS16_0BCA8(arg0, 2);
            break;

        case 2:
            Particle_PrimG_Approach_0BB14(arg0, 0, 0x20);

            if (Particle_FieldA6_DecrementToZeroStep1_0BDAC != NULL) {
                Particle_PrimAlpha_Approach_0BC2C(arg0, 0, 0x20);
            }

            if (ModelAnim_IsFinished(arg0->displayObject) != 0) {
                Particle_MarkInactive(arg0);
            }
            break;
    }
}

/**
 * Using to make a horizontal cylindrical hit spark for Skull Bash, Mega Punch, and Mega Kick
 * @unverified Name and comment from Stadium 1, matched by code similarity.
 */
void BattleAnim_InitializeLargePhysicalHitSpark(void) {
    func_8213BC00(4, 8, 0xFF, 0, 0x20);
    func_8213B560(4, &func_8215ED1C, &D_8218E580, 0, 1, 9, 0, 0x19, 0);
}

/**
 * initializes using drill peck
 * @unverified Name and comment from Stadium 1.
 */
void BattleAnim_InitializeDrillPeckUse(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_CallbackInitModelAnimWait, &gDefaultParticleDescriptor, 0, 1, 0x11, gBattleAnimCurrentAnchor, 0x1B, 1);
}

/**
 * initializes being hit by drill peck
 * @unverified Name and comment from Stadium 1.
 */
void BattleAnim_InitializeDrillPeckHit(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_CallbackInitModelAnimWait, &gDefaultParticleDescriptor, 0, 1, 0x11, gBattleAnimCurrentAnchor, 0x1C, 1);
}

/**
 * initializes getting using horn drill
 * @unverified Name and comment from Stadium 1.
 */
void BattleAnim_InitializeHornDrillUse(void) {
    BattleAnim_SpawnGlobalTintColorFadeDetach(0, 0x20, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_CallbackInitModelAnimWait, &gDefaultParticleDescriptor, 0, 1, 0x11, gBattleAnimCurrentAnchor, 0x1B, 1);
}

/**
 * initializes getting hit by horn drill
 * @unverified Name and comment from Stadium 1, matched by code similarity.
 */
void BattleAnim_InitializeHornDrillHit(void) {
    func_8213BC00(0, 0xA, 0, 0xFF, 0x40);
    func_8213B560(0, &func_82152F44, &D_8218E580, 0, 1, 0x11, (s32) D_8219A80A, 0x1C, 1);
    func_8213BC00(0x30, 0xA, 0xFF, 0, 2);
}

/**
 * Used to create the spear projectile for fury attack, peck, and horn attack
 * @unverified Name and comment from Stadium 1.
 */
void BattleAnim_RunWeakSpear(Particle* arg0) {
    s16 sp26 = Particle_FieldCE_GetS32_0C040(arg0);

    switch (arg0->unk_B2) {
        case 1:
            BattleAnim_SelectParticleModelFrames(arg0, 0);
            if (sp26 == 1) {
                Particle_Field1C_SetScaled_0B938(arg0, 1.5f);
                Particle_Field38_AddXZFromField94YOffset180_08F38(arg0, 40.0f);
            }
            break;

        case 2:
            ParticleGfx_ApproachPrimEnvPalettePair(arg0, 0x33, 0x40);
            Particle_PrimAlpha_ApproachAndStepState_0BC5C(arg0, 0xFF, 0x40);
            break;

        case 3:
            ParticleGfx_ApproachPrimEnvPalettePair(arg0, 0, 0x40);
            Particle_PrimAlpha_ApproachAndStepState_0BC5C(arg0, 0, 0x40);
            break;

        case 4:
            Particle_MarkInactive(arg0);
            break;
    }
}

/**
 * @unverified Name from Stadium 1, matched by code similarity.
 */
void BattleAnim_InitializeFuryAttackPeckUse(void) {
    func_8213B5D8(0, 2, 3, &func_8215EFF8, &D_8218E580, 0, 1, 0x11, 7, 0x20, 0);
}

/**
 * initializes using horn attack
 * @unverified Name and comment from Stadium 1, matched by code similarity.
 */
void BattleAnim_InitializeHornAttackUse(void) {
    func_8213B560(0, &func_8215EFF8, &D_8218E580, 0, 1, 0x11, 7, 0x20, 1);
}

void func_8215F1B0(s8 *arg0) {
    s16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_82152730(arg0, 0);
        return;
    case 2:
        func_821437E0(arg0, 0x33, 0x24);
        func_82140518(arg0, 0xFF, 0x1D);
        if (func_8001104C(M2C_FIELD(arg0, s32 *, 0x14)) != 0) {
            func_8213C930(arg0);
        }
        return;
    }
}

/**
 * Moves: Body Slam (hit), Fly (hit), Seismic Toss (hit), Stomp (hit)
 * TODO: Human contributor add screenshot
 * @unverified Name and comment from Stadium 1.
 */
void BattleAnim_InitializeVerticalLandingHitSpark(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_CallbackEndEffect79DefaultDescriptorPaletteFade, &gDefaultParticleDescriptor, 0, 1, 0xA, 0, 0x1F, 0);
}

void func_8215F290(void) {
    func_8213B644(0, 8, 0x20);
}

void BattleAnim_CallbackStartEffects127And128Descriptor39ScaleFade_InitParticle(Particle* arg0) {
    s16 sp26 = Particle_FieldAC_GetS16_0C038(arg0);
    s16 sp24 = Particle_FieldCF_GetS16_0C058(arg0);

    Particle_FieldCE_GetS32_0C040(arg0);

    switch (sp26) {
        case 0:
            Particle_SetPosition(arg0, 0.0f, 0.0f, 0.0f);
            break;

        case 1:
            Particle_SetPosition(arg0, 0.0f, 10.0f, 10.0f);
            break;

        case 2:
            Particle_SetPosition(arg0, 0.0f, 15.0f, -15.0f);
            break;
    }

    Particle_Field1C_SetScaled_0B938(arg0, 0.1f);
    Particle_SetScaleSpeed(arg0, 2.0f);
    Particle_SetScaleTarget(arg0, 0.0625f);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, sp24);
    Particle_SetPrimAlpha(arg0, 0xFF);
    Particle_FieldA6_SetS16_0BCA8(arg0, sp26 * 8);
    Particle_DisableRendering(arg0);
    Particle_AdvanceLifecycle(arg0);
}

void func_8215F3EC(s8 *arg0) {
    s16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_8215F2B8(arg0);
        return;
    case 2:
        if (func_821406B4(arg0) != 0) {
            func_8213CB3C(arg0);
            func_82140594(arg0, 0xA);
            return;
        }
        return;
    case 3:
        func_821402B8(arg0);
        if (func_82140690(arg0) != 0) {
            func_82140548(arg0, 0, 0x10);
            return;
        }
        break;
    case 4:
        func_8213C930(arg0);
        break;
    }
}

void BattleAnim_StartEffect127Descriptor39ScaleFade(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_CallbackStartEffects127And128Descriptor39ScaleFade, &gBattleAnimParticleDescriptors[0x39], 8, 3, 2, 0, 0x45, 0);
}

void BattleAnim_StartEffect128Descriptor39ScaleFade(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_CallbackStartEffects127And128Descriptor39ScaleFade, &gBattleAnimParticleDescriptors[0x39], 8, 3, 2, 0, 0x47, 0);
}

void ParticleEffect_CreateTypeX(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_CallbackStartEffects12And129DelayedModelAnimWait, &gDefaultParticleDescriptor, 0x1E, 3, 6, 0, 0, 0);
}

void ParticleEffect_CreateSmoke(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_RunDefaultHitSpark, &gBattleAnimParticleDescriptors[0x34], 0, 1, 0x11, 9, 0, 6);
}

void ParticleEffect_CreateSmokeHighPriority(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(0x10, BattleAnim_RunDefaultHitSpark, &gBattleAnimParticleDescriptors[0x34], 0, 1, 0x11, 9, 0, 6);
}

void BattleAnim_CallbackStartEffect132Descriptor39DelayedRiseFade_InitParticle(Particle* arg0) {
    s16 sp26 = Particle_FieldAC_GetS16_0C038(arg0);
    s16 sp24 = Particle_FieldCF_GetS16_0C058(arg0);

    Particle_FieldCE_GetS32_0C040(arg0);

    switch (sp26) {
        case 0:
            Particle_SetPosition(arg0, 0.0f, 0.0f, 0.0f);
            break;

        case 1:
            Particle_SetPosition(arg0, 0.0f, 10.0f, 10.0f);
            break;

        case 2:
            Particle_SetPosition(arg0, 0.0f, 15.0f, -15.0f);
            break;
    }

    Particle_Field1C_SetScaled_0B938(arg0, 0.01f);
    Particle_SetScaleSpeed(arg0, 0.5f);
    Particle_SetScaleTarget(arg0, 0.05f);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, sp24);
    Particle_SetPrimAlpha(arg0, 0xFF);
    Particle_FieldA6_SetS16_0BCA8(arg0, sp26 * 8);
    Particle_DisableRendering(arg0);
    Particle_AdvanceLifecycle(arg0);
}

void BattleAnim_CallbackStartEffect132Descriptor39DelayedRiseFade(Particle* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            BattleAnim_CallbackStartEffect132Descriptor39DelayedRiseFade_InitParticle(arg0);
            break;

        case 2:
            if (Particle_FieldA6_DecrementToZeroStep1AndStepState_0BDD0(arg0) != 0) {
                Particle_EnableRendering(arg0);
                Particle_FieldA6_SetS16_0BCA8(arg0, 0xA);
            }
            break;

        case 3:
            Particle_Field1C_ApproachField24ByField20_0BA1C(arg0);
            func_8213E1FC(arg0, 1.0f);
            if (Particle_FieldA6_DecrementToZeroStep1AndStepState_0BDD0(arg0) != 0) {
                Particle_FieldA6_SetS16_0BCA8(arg0, 0x10);
            }
            break;

        case 4:
            func_8213F658(arg0, 0x40800000, 0x3F000000);
            func_8213E1FC(arg0, arg0->unk_74);
            Particle_PrimAlpha_Approach_0BC2C(arg0, 0, 0x10);
            if (Particle_FieldA6_DecrementToZeroStep1AndStepState_0BDD0(arg0) != 0) {
                break;
            }
            break;

        case 5:
            Particle_MarkInactive(arg0);
            break;
    }
}

void ParticleEffect_CreateDual(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_CallbackStartEffect132Descriptor39DelayedRiseFade, &gBattleAnimParticleDescriptors[0x39], 8, 3, 2, 0, 0x46, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(0x10, BattleAnim_CallbackStartEffect132Descriptor39DelayedRiseFade, &gBattleAnimParticleDescriptors[0x39], 8, 3, 2, 0, 0x46, 0);
}
