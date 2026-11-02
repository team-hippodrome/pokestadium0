/* Fixed-layout split; original translation-unit boundaries remain unconfirmed. */
#include "battle_engine_32B680_3.h"

void BattleAnim_SetupReflectiveCamera(void) {
    Mtx* sp3C = Gfx_AllocDisplayList(sizeof(Mtx) * 1);
    LookAt* sp38 = Gfx_AllocDisplayList(sizeof(LookAt) * 1);
    CameraNode* temp_v0 = BattleAnim_GetCameraContext();

    guLookAtReflect(sp3C, sp38, temp_v0->view.eyePosition.x, temp_v0->view.eyePosition.y, temp_v0->view.eyePosition.z,
                    temp_v0->view.targetPosition.x, temp_v0->view.targetPosition.y, temp_v0->view.targetPosition.z, temp_v0->view.upDirection.x,
                    temp_v0->view.upDirection.y, temp_v0->view.upDirection.z);
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_82152730.s")

void BattleAnim_CallbackInitModelAnimWait(Particle* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            BattleAnim_SelectParticleModelFrames(arg0, 0);
            break;

        case 2:
            if (ModelAnim_IsFinished(arg0->unk_14) != 0) {
                Particle_MarkInactive(arg0);
            }
            break;
    }
}

void BattleAnim_CallbackInitModelAnim(Particle* arg0) {
    if (arg0->unk_B2 == 1) {
        BattleAnim_SelectParticleModelFrames(arg0, 0);
    }
}

void BattleAnim_CallbackStartEffects83And103ModelAlphaFadeIn(Particle* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            BattleAnim_SelectParticleModelFrames(arg0, 0);
            break;

        case 2:
            Particle_PrimAlpha_ApproachAndStepState_0BC5C(arg0, arg0->unk_A6, Particle_FieldCE_GetS32_0C040(arg0));
            break;
    }
}

void BattleAnim_CallbackInitModelAnimWaitCleanup(Particle* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            BattleAnim_SelectParticleModelFrames(arg0, 1);
            break;

        case 2:
            if (BattleAnim_IsModelAnimComplete(arg0->unk_14) != 0) {
                Particle_AdvanceLifecycle(arg0);
            }
            break;

        case 3:
            Particle_DisableAndDetach(arg0);
            break;
    }
}

void BattleAnim_CallbackInitModelAnimMode2(Particle* arg0) {
    if (arg0->unk_B2 == 1) {
        BattleAnim_SelectParticleModelFrames(arg0, 2);
    }
}

void BattleAnim_CallbackInitModelAnimMode2Update(Particle* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            BattleAnim_SelectParticleModelFrames(arg0, 2);
            break;

        case 2:
            Particle_PrimAlpha_ApproachAndStepState_0BC5C(arg0, arg0->unk_A6, Particle_FieldCE_GetS32_0C040(arg0));
            break;
    }
}

Gfx* BattleAnim_BuildAnimatedTileDisplayList(Gfx* arg0, u8* arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5, s16 arg6, s16 arg7, s16 arg8, s16 arg9,
                   s16 argA, s16 argB) {
    gDPLoadTextureTile_4b(arg0++, arg1, G_IM_FMT_I, arg2, 0, 0, 0, arg2 - 1, arg2 - 1, 0, G_TX_NOMIRROR | G_TX_WRAP,
                          G_TX_NOMIRROR | G_TX_WRAP, arg3, arg3, arg6, arg7);

    ParticleGfx_SetAnimatedTileSizeOnList(arg0++, arg4, arg5, arg2, arg2);

    gDPLoadMultiTile_4b(arg0++, arg1, 0x0100, 1, G_IM_FMT_I, arg2, 0, 0, 0, arg2 - 1, arg2 - 1, 0,
                        G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, arg3, arg3, argA, argB);

    ParticleGfx_SetAnimatedAuxTileSizeOnList(arg0++, arg8, arg9, arg2, arg2);
    return arg0;
}

Gfx* BattleAnim_BuildAnimatedTileDisplayListFromStruct(Gfx* arg0, arg1_func_8434E21C* arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5, s16 arg6, s16 arg7,
                   s16 arg8, s16 arg9, s16 argA, s16 argB) {
    gDPLoadTextureTile_4b(arg0++, arg1->unk_00, G_IM_FMT_I, arg2, arg2, 0, 0, arg2 - 1, arg2 - 1, 0,
                          G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, arg3, arg3, arg6, arg7);

    ParticleGfx_SetAnimatedTileSizeOnList(arg0++, arg4, arg5, arg2, arg2);

    gDPLoadMultiTile_4b(arg0++, arg1->unk_04, 0x0100, 1, G_IM_FMT_I, arg2, arg2, 0, 0, arg2 - 1, arg2 - 1, 0,
                        G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, arg3, arg3, argA, argB);
    ParticleGfx_SetAnimatedAuxTileSizeOnList(arg0++, arg8, arg9, arg2, arg2);
    return arg0;
}

void Gfx_SetParticlePrimEnvColors(Gfx* arg0) {
    Particle* temp_v0 = BattleAnim_GetOwnerContextParticle(D_8006049C);

    gDPPipeSync(arg0++);

    gDPSetPrimColor(arg0++, 0, 0, temp_v0->prim_r, temp_v0->prim_g, temp_v0->prim_b, temp_v0->prim_a);
    gDPSetEnvColor(arg0++, temp_v0->env_r, temp_v0->env_g, temp_v0->env_b, 255);

    gSPEndDisplayList(arg0++);
}

void ParticleEffect_AllocateGfxIfNeeded(s32 arg0, arg1_func_84344CE8* arg1) {
    if (arg0 == 2) {
        arg1->unk_18 = Gfx_AllocDisplayList(sizeof(Gfx) * 30);
        Gfx_SetParticlePrimEnvColors(arg1->unk_18);
    }
}

void Gfx_DrawParticleTextureWithParams(Gfx* arg0, arg1_func_8434E21C* arg1, UNUSED u16 arg2) {
    s16 mask = 5;
    Particle* sp40;
    s16 var_a2;
    s16 sp3C;
    s16 sp3A;
    s16 sp38;
    s16 sp36;
    s16 w = 32;
    s16 h = 32;
    s16 sp30;
    s16 sp2E;
    s16 sp2C;
    s16 sp2A;
    s32 temp_v0_2;

    sp40 = BattleAnim_GetOwnerContextParticle(D_8006049C);
    temp_v0_2 = Particle_FieldCE_GetS32_0C040(sp40);
    var_a2 = 0x80;

    switch (temp_v0_2) {
        case 0:
            var_a2 = 0x96;
            sp3C = 2;
            sp3A = 0;
            sp38 = -2;
            sp36 = 0;
            sp30 = 0xC;
            sp2E = 0;
            sp2C = 0xF;
            sp2A = 0;
            break;

        case 1:
            var_a2 = 0xFF;
            sp3C = 0;
            sp3A = 0;
            sp38 = 0xF;
            sp36 = 0;
            sp30 = 0xF;
            sp2E = 0;
            sp2C = 0xE;
            sp2A = 0xD;
            break;

        case 2:
            var_a2 = 0xFF;
            sp3C = 0;
            sp3A = 0;
            sp38 = 1;
            sp36 = 0;
            sp30 = 1;
            sp2E = 1;
            sp2C = 7;
            sp2A = 1;
            break;
    }

    gDPPipeSync(arg0++);
    gDPSetPrimColor(arg0++, 0, var_a2, sp40->prim_r, sp40->prim_g, sp40->prim_b, sp40->prim_a);
    gDPSetEnvColor(arg0++, sp40->env_r, sp40->env_g, sp40->env_b, 255);

    gDPLoadTextureTile_4b(arg0++, arg1->unk_00, G_IM_FMT_I, w, h, 0, 0, w - 1, h - 1, 0, G_TX_NOMIRROR | G_TX_WRAP,
                          G_TX_NOMIRROR | G_TX_WRAP, mask, mask, sp30, sp2E);

    ParticleGfx_SetAnimatedTileSizeOnList(arg0++, sp3C, sp3A, w, h);

    gDPLoadMultiTile_4b(arg0++, arg1->unk_04, 0x0100, 1, G_IM_FMT_I, w, h, 0, 0, w - 1, h - 1, 0,
                        G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, mask, mask, sp2C, sp2A);

    ParticleGfx_SetAnimatedAuxTileSizeOnList(arg0++, sp38, sp36, w, h);

    gSPEndDisplayList(arg0++);
}

void ParticleEffect_AllocateGfxAndDraw(s32 arg0, arg1_func_84344CE8* arg1) {
    if (arg0 == 2) {
        arg1->unk_18 = Gfx_AllocDisplayList(sizeof(Gfx) * 30);
        Gfx_DrawParticleTextureWithParams(arg1->unk_18, arg1->unk_14, D_80060484);
    }
}

void BattleAnim_SetupMove86EndDescriptor24(Particle* arg0) {
    Particle_Field1C_SetScaled_0B938(arg0, 3.0f);
    Particle_Field38_AddYScaled_08E90(arg0, 10.0f);
    Particle_Field38_AddXZFromField94Y_08ED0(arg0, 15.0f);
    Particle_Field74_SetScaled_0AD8C(arg0, -5.0f);
    ParticleGfx_RecolorPrim(arg0, 8);
    ParticleGfx_RecolorEnv(arg0, 0x17);
    Particle_AdvanceLifecycle(arg0);
}

void BattleAnim_CallbackMove86EndDescriptor24(Particle* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            BattleAnim_SetupMove86EndDescriptor24(arg0);
            break;

        case 2:
            Particle_FieldA6_DecrementToZeroStep1AndStepState_0BDD0(arg0);
            break;

        case 3:
            Particle_PrimAlpha_ApproachAndStepState_0BC5C(arg0, 0, 0x40);
            break;

        case 4:
            Particle_DisableAndDetach(arg0);
            break;
    }

    Particle_Field1C_Approach_0B98C(arg0, 0.0f, 0.1f);
    Particle_AddVelocityXZFromRotationYViaImpulse(arg0);
}

void BattleAnim_SetupMove86StartDescriptor24(Particle* arg0) {
    Vec3f sp34;
    UNUSED s32 pad[2];
    s16 sp2A = Particle_FieldCD_GetU8_0C048(arg0);

    Particle_Field1C_SetScaled_0B938(arg0, 0.05f);

    switch (sp2A) {
        case 0:
            sp34.x = 0;
            sp34.y = -5.0f;
            sp34.z = 0.0f;
            break;

        case 1:
            sp34.x = 0;
            sp34.y = 5.0f;
            sp34.z = 10.0f;
            break;

        case 2:
            sp34.x = 0;
            sp34.y = 5.0f;
            sp34.z = -10.0f;
            break;
    }

    Particle_Field38_AddVecScaledFromVec3f_08D78(arg0, sp34);
    Particle_Field38_AddYScaled_08E90(arg0, 10.0f);
    Particle_Field74_SetScaled_0AD8C(arg0, 0.0f);
    ParticleGfx_RecolorPrim(arg0, 8);
    ParticleGfx_RecolorEnv(arg0, 0x17);
    Particle_AdvanceLifecycle(arg0);
}

void func_82153E28(s8 *arg0) {
    s16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_82153D00(arg0);
        break;
    case 2:
        func_821406B4(arg0);
        break;
    case 3:
        func_82140548(arg0, 0, 0x20);
        break;
    case 4:
        func_8213C938(arg0);
        break;
    }
    func_82140228(arg0, 0x41200000, 0x3D4CCCCD);
    func_8213E4D8(arg0);
}

void ParticleEffect_RegisterExplosion(void) {
    BattleAnim_SpawnCategory17MarkerSlot(0x55, 1);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0, 8, 0xC, BattleAnim_CallbackMove86StartDescriptor24, &gBattleAnimParticleDescriptors[0x24], 0xA, 1, 4, 0, 0, 0);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0, 8, 0xC, BattleAnim_CallbackMove86StartDescriptor24, &gBattleAnimParticleDescriptors[0x24], 0xA, 1, 4, 1, 0, 0);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0, 8, 0xC, BattleAnim_CallbackMove86StartDescriptor24, &gBattleAnimParticleDescriptors[0x24], 0xA, 1, 4, 2, 0, 0);
}

void func_82153FD8(void) {
    func_8213B644(0x30, 0x20, 8);
    func_8213B5D8(0, 0xC, 0xA, &func_82153C50, &D_8218E6A8, 0x14, 1, 4, (s32) D_8219A80A, 0, 0);
}


void func_82154050(Particle* arg0) {
    f32 offset = 0.0f;
    f32 scale = D_FLT_82196CB8;

    switch (BattleAnim_GetOwnerSpecies(arg0->unk_10)) {
        case 0xF:
            offset = 5.0f;
            break;
        case 0x16:
            offset = 3.0f;
            break;
        case 0x1F:
            offset = 5.0f;
            break;
        case 0x22:
            offset = 3.0f;
            break;
        case 0x39:
            offset = 10.0f;
            break;
        case 0x41:
            offset = 8.0f;
            break;
        case 0x4C:
            offset = 2.0f;
            break;
        case 0x5B:
            offset = 5.0f;
            break;
        case 0x5E:
            offset = 5.0f;
            break;
        case 0x61:
            offset = 5.0f;
            break;
        case 0x73:
            offset = 12.0f;
            break;
        case 0x7F:
            offset = 3.0f;
            break;
        case 0x80:
            offset = 3.0f;
            break;
        case 0x82:
            scale = D_FLT_82196EC8;
            Particle_Field38_AddYScaled_08E90(arg0, 5.0f);
            break;
        case 0x83:
            scale = D_FLT_82196ECC;
            offset = 5.0f;
            break;
        case 0x86:
            offset = 3.0f;
            break;
        case 0x88:
            offset = 3.0f;
            break;
        case 0x8E:
            offset = 10.0f;
            break;
        case 0x91:
            offset = 3.0f;
            break;
    }
    Particle_Field38_AddXZFromField94Y_08ED0(arg0, offset + 5.0f);
    Particle_Field1C_SetScaled_0B938(arg0, scale);
}


void BattleAnim_SetupEffect1Descriptor2F(Particle* arg0) {
    BattleAnim_ApplyEffect1SpeciesMotion(arg0);
    Particle_AdvanceLifecycle(arg0);
}

void BattleAnim_CallbackStartEffect1Descriptor2FPhaseFadeOut(Particle* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            BattleAnim_SetupEffect1Descriptor2F(arg0);
            break;

        case 3:
            Particle_PrimAlpha_ApproachAndStepState_0BC5C(arg0, 0, 0x20);
            break;

        case 4:
            Particle_DisableAndDetach(arg0);

        case 2:
            break;
    }
}

void func_821542BC(void) {
    func_8213B560(0, &func_82154248, &D_8218E700, 0, 1, 0x10, 7, 0, 0);
}
