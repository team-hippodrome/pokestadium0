#include "pokemon.h"
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

void func_82154704(s8*);
void BattleAnim_SelectParticleModelFrames(Particle* arg0, s32 arg1) {
    f32 sp2C = 1.0f;
    s16 sp2A;
    s16 sp28;
    s16 sp26;
    s16 sp24 = Particle_FieldCD_GetU8_0C048(arg0);

    switch (Particle_FieldCF_GetS16_0C058(arg0)) {
        case 30:
            sp2A = 0x23;
            sp28 = 0x24;
            Particle_Field38_AddYScaled_08E90(arg0, 10.0f);
            func_82154704(arg0);
            break;

        case 0:
            sp2A = 0x66;
            sp28 = 0x67;
            sp2C = 0.5f;
            break;

        case 1:
            sp2A = 0x68;
            sp28 = 0x69;
            sp2C = 0.5f;
            break;

        case 2:
            sp2A = 0x6A;
            sp28 = 0x6B;
            sp2C = 0.5f;
            break;

        case 3:
            sp2A = 0x73;
            sp28 = 0x74;
            sp2C = func_8215AEA4(arg0);
            Particle_SetPrimAlpha(arg0, 0);
            Particle_Field38_SetYScaled_08CA0(arg0, 5.0f);
            break;

        case 4:
            sp2A = 0x78;
            sp28 = 0x79;
            Particle_SetPrimColor(arg0, 0x50, 0x46, 0x3C);
            Particle_SetEnvColor(arg0, 0xFF, 0, 0);
            break;

        case 5:
            sp2A = 0x7B;
            sp28 = 0x7C;
            break;

        case 6:
            sp2A = 0x7D;
            sp28 = 0x7E;
            break;

        case 7:
            sp2A = 0x7F;
            sp28 = 0x80;
            break;

        case 8:
            sp2A = 0x81;
            sp28 = 0x82;
            sp2C = 5.0f;
            ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, 0x17);
            Particle_SetPrimAlpha(arg0, 0x64);
            break;

        case 42:
            sp2A = 0x81;
            sp28 = 0x82;
            Particle_AddPositionOffsetAlongRotationYPlus180(arg0, 300.0f);
            sp2C = 5.0f;
            ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, 0xC);
            Particle_SetPrimAlpha(arg0, 0x64);
            break;

        case 9:
            sp2A = 0x83;
            sp28 = 0x84;
            Particle_SetFlags(arg0, 0x800);
            Particle_Field38_AddYScaled_08E90(arg0, 5.0f);
            break;

        case 10:
            sp2A = 0x85;
            sp28 = 0x86;
            sp2C = 0.5f;
            break;

        case 11:
            sp2A = 0x88;
            sp28 = 0x89;
            sp2C = func_8215B6A4(arg0);
            break;

        case 12:
            sp2A = 0x8A;
            sp28 = 0x8B;
            break;

        case 13:
            sp2A = 0x9A;
            sp28 = 0x9B;
            sp2C = 1.5f;

            switch (sp24) {
                case 1:
                    Particle_Field94_AddY_0A594(arg0, 0x6000);
                    break;

                case 2:
                    Particle_Field94_AddY_0A594(arg0, -0x4000);
                    break;
            }
            break;

        case 14:
            sp2A = 0x9C;
            sp2C = 1.5f;
            Particle_SetPrimAlpha(arg0, 0);
            break;

        case 15:
            sp2A = 0x9C;
            sp2C = 1.5f;
            Particle_SetPrimAlpha(arg0, 0);
            break;

        case 16:
            sp2A = 0x9D;
            sp28 = 0x9E;

            switch (BattleAnim_GetOwnerSpecies(arg0->pokemon)) {
                case ONIX:
                    Particle_AddPositionOffsetAlongRotationYPlus180(arg0, 15.0f);
                    Particle_Field38_SetYScaled_08CA0(arg0, 15.0f);
                    break;

                case GYARADOS:
                    Particle_AddPositionOffsetAlongRotationYPlus180(arg0, 15.0f);
                    break;
            }
            break;

        case 17:
            sp2A = 0xA3;
            sp28 = 0xA5;
            break;

        case 18:
            sp2A = 0xA3;
            sp28 = 0xA4;
            sp2C = 1.5f;
            break;

        case 19:
            sp2A = 0xA3;
            sp28 = 0xBB;
            sp2C = 1.5f;
            break;

        case 20:
            sp2A = 0xAA;
            sp28 = 0xAB;
            sp2C = 1.5f;
            break;

        case 21:
            sp2A = 0xAD;
            Particle_FieldAE_SetS16_0BF4C(arg0, 0xBE);
            Particle_SetPrimAlpha(arg0, 0);
            break;

        case 22:
            sp2A = 0x5C;
            sp28 = 0x5D;
            break;

        case 23:
            sp2A = 0xAE;
            Particle_SetPrimAlpha(arg0, 0);
            break;

        case 24:
            sp2A = 0xAE;
            Particle_SetPrimAlpha(arg0, 0);
            break;

        case 25:
            sp2A = 0xAF;
            sp28 = 0xB0;
            Particle_SetPrimColor(arg0, 0xFF, 0xFF, 0);
            Particle_SetEnvColor(arg0, 0xFF, 0, 0);
            Particle_Field38_SetYScaled_08CA0(arg0, 10.0f);
            break;

        case 26:
            sp2A = 0xB6;
            Particle_SetPrimAlpha(arg0, 0);
            break;

        case 27:
            sp2A = 0xB3;
            sp28 = 0xB4;
            Particle_SetPrimAlpha(arg0, 0x64);
            Particle_SetPrimColor(arg0, 0xFF, 0xFF, 0);
            Particle_SetEnvColor(arg0, 0xFF, 0, 0);
            sp2C = 0.8f;
            break;

        case 28:
            sp2A = 0xB3;
            sp28 = 0xB5;
            Particle_SetPrimAlpha(arg0, 0x64);
            Particle_SetPrimColor(arg0, 0xFF, 0xFF, 0);
            Particle_SetEnvColor(arg0, 0xFF, 0, 0);
            sp2C = 0.8f;
            break;

        case 29:
            sp2A = 0xBE;
            sp28 = 0xBF;
            break;

        case 31:
            sp2A = 0xC0;
            sp28 = 0xC1;
            ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, 0x17);
            Particle_SetPrimAlpha(arg0, 0x32);
            sp2C = 1.2f;
            break;

        case 32:
            sp2A = 0xB1;
            sp28 = 0xB2;
            ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, 0);
            Particle_SetPrimAlpha(arg0, 0);
            break;

        case 33:
            sp2A = 0xB7;
            break;

        case 34:
            sp2A = 0x2E;
            sp28 = 0x2F;
            Particle_Field94_AddY_0A594(arg0, -0x4000);
            sp2C = 0.5f;
            break;

        case 35:
            sp2A = 0x3B;
            sp28 = 0x3C;
            break;

        case 36:
            sp2A = 0x3D;
            sp28 = 0x3E;

            switch (sp24) {
                case 0:
                    sp26 = 0x6000;
                    break;

                case 1:
                    sp26 = 0x4000;
                    break;

                case 2:
                    sp26 = 0x2000;
                    break;
            }
            Particle_Field94_AddY_0A594(arg0, sp26);
            break;

        case 37:
            sp2A = 0x40;
            sp28 = 0x41;
            break;

        case 38:
            sp2A = 0x4B;
            sp28 = 0x4C;
            break;

        case 39:
            sp2A = 0x4D;
            sp28 = 0x4E;
            Particle_SetPrimColor(arg0, 0xFF, 0xFF, 0xFF);
            Particle_SetEnvColor(arg0, 0x37, 0xFF, 0xFF);
            break;

        case 40:
            sp2A = 0x57;
            sp28 = 0x58;
            break;

        case 41:
            sp2A = 0x5A;
            sp28 = 0x5B;
            sp2C = BattleAnim_GetSpeciesScaleAdjust(arg0);
            break;
    }

    arg0->displayObject = BattleAnim_AllocOwnerDisplayContext(arg0);
    if (arg0->displayObject != NULL) {
        switch (arg1) {
            case 0:
                BattleAnim_InitModelWithAnim(arg0->displayObject, sp2A, sp28);
                break;

            case 1:
                BattleAnim_InitModel(arg0->displayObject, sp2A);
                BattleAnim_BindModelAnimReversed(arg0->displayObject, sp28);
                break;

            case 2:
                BattleAnim_InitModel(arg0->displayObject, sp2A);
                break;
        }
        Particle_SetScaleScaled(arg0, sp2C);
        Particle_AdvanceLifecycle(arg0);
    } else {
        Particle_DisableAndDetach(arg0);
    }
}


void BattleAnim_CallbackInitModelAnimWait(Particle* arg0) {
    switch (arg0->lifecycle) {
        case 1:
            BattleAnim_SelectParticleModelFrames(arg0, 0);
            break;

        case 2:
            if (ModelAnim_IsFinished(arg0->displayObject) != 0) {
                Particle_MarkInactive(arg0);
            }
            break;
    }
}

/**
 * Moves: Barrier (use), Defense Curl (use), Dig (use/hit), Earthquake (hit), Fissure (hit), Light Screen
 * (use), Pay Day (hit), Reflect (use), Sharpen (use), Withdraw (use)
 * TODO: Human contributor add screenshot
 * Seen in play (2026-11-13) (unattended Free Battle in which every Pokémon knows only Metronome, 40
 * turns): ran.
 * @unverified Name and comment from Stadium 1.
 */
void BattleAnim_InitializeParticleModel(Particle* arg0) {
    if (arg0->lifecycle == 1) {
        BattleAnim_SelectParticleModelFrames(arg0, 0);
    }
}

/**
 * Used for the Eyes in Leer and Glare.
 * It is reused for additional flair in Sky Attack (hands an X shape on the bird)
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Leer, Glare.
 */
void BattleAnim_RunScaryEyes(Particle* arg0) {
    switch (arg0->lifecycle) {
        case 1:
            BattleAnim_SelectParticleModelFrames(arg0, 0);
            break;

        case 2:
            Particle_ApproachPrimAlphaThenAdvance(arg0, arg0->unk_A6, Particle_FieldCE_GetS32_0C040(arg0));
            break;
    }
}

/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Dream Eater.
 */
void BattleAnim_RunDreamEaterUseEffect(Particle* arg0) {
    switch (arg0->lifecycle) {
        case 1:
            BattleAnim_SelectParticleModelFrames(arg0, 1);
            break;

        case 2:
            if (BattleAnim_IsModelAnimComplete(arg0->displayObject) != 0) {
                Particle_AdvanceLifecycle(arg0);
            }
            break;

        case 3:
            Particle_DisableAndDetach(arg0);
            break;
    }
}

void BattleAnim_CallbackInitModelAnimMode2(Particle* arg0) {
    if (arg0->lifecycle == 1) {
        BattleAnim_SelectParticleModelFrames(arg0, 2);
    }
}

/**
 * Moves: Absorb (use), Bide (use), Confusion (use), Focus Energy (use), Leech Life (use), Mega Drain (use),
 * Psychic (use), Rage (use), Solar Beam (use), Waterfall (use/hit)
 * TODO: Human contributor add screenshot
 * Seen in play (2026-11-13) (unattended Free Battle in which every Pokémon knows only Metronome, 40
 * turns): ran.
 * @unverified Name and comment from Stadium 1.
 */
void BattleAnim_RunFillScreenOverlay(Particle* arg0) {
    switch (arg0->lifecycle) {
        case 1:
            BattleAnim_SelectParticleModelFrames(arg0, 2);
            break;

        case 2:
            Particle_ApproachPrimAlphaThenAdvance(arg0, arg0->unk_A6, Particle_FieldCE_GetS32_0C040(arg0));
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
    Particle_SetScaleScaled(arg0, 3.0f);
    Particle_Field38_AddYScaled_08E90(arg0, 10.0f);
    Particle_AddPositionOffsetAlongRotationY(arg0, 15.0f);
    Particle_Field74_SetScaled_0AD8C(arg0, -5.0f);
    ParticleGfx_RecolorPrim(arg0, 8);
    ParticleGfx_RecolorEnv(arg0, 0x17);
    Particle_AdvanceLifecycle(arg0);
}

/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Thunder Wave.
 */
void BattleAnim_RunThunderWaveHitEffect(Particle* arg0) {
    switch (arg0->lifecycle) {
        case 1:
            BattleAnim_SetupMove86EndDescriptor24(arg0);
            break;

        case 2:
            Particle_DecrementUnkA6ToZeroThenAdvance(arg0);
            break;

        case 3:
            Particle_ApproachPrimAlphaThenAdvance(arg0, 0, 0x40);
            break;

        case 4:
            Particle_DisableAndDetach(arg0);
            break;
    }

    Particle_ApproachScale(arg0, 0.0f, 0.1f);
    Particle_AddVelocityXZFromRotationYViaImpulse(arg0);
}

void BattleAnim_SetupMove86StartDescriptor24(Particle* arg0) {
    Vec3f sp34;
    UNUSED s32 pad[2]; // FAKE: stack padding
    s16 sp2A = Particle_FieldCD_GetU8_0C048(arg0);

    Particle_SetScaleScaled(arg0, 0.05f);

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
        Particle_DisableAndDetach(arg0);
        break;
    }
    func_82140228(arg0, 0x41200000, 0x3D4CCCCD);
    func_8213E4D8(arg0);
}

/**
 * Effect start init 38 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used:
 * it ran for exactly Thunder Wave.
 */
void BattleAnim_InitializeThunderWaveUse(void) {
    BattleAnim_SpawnCategory17MarkerSlot(0x55, 1);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0, 8, 0xC, BattleAnim_CallbackMove86StartDescriptor24, &gBattleAnimParticleDescriptors[0x24], 0xA, 1, 4, 0, 0, 0);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0, 8, 0xC, BattleAnim_CallbackMove86StartDescriptor24, &gBattleAnimParticleDescriptors[0x24], 0xA, 1, 4, 1, 0, 0);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0, 8, 0xC, BattleAnim_CallbackMove86StartDescriptor24, &gBattleAnimParticleDescriptors[0x24], 0xA, 1, 4, 2, 0, 0);
}

/**
 * Effect init for the end (impact) of the Thunder Wave animation.
 * Effect end init 17 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used: it
 * ran for exactly Thunder Wave.
 */
void BattleAnim_InitializeThunderWaveHit(void) {
    func_8213B644(0x30, 0x20, 8);
    func_8213B5D8(0, 0xC, 0xA, &func_82153C50, &D_8218E6A8, 0x14, 1, 4, (s32) D_8219A80A, 0, 0);
}


/**
 * Seen in play (2026-11-13) (unattended Free Battle in which every Pokémon knows only Metronome, 40
 * turns): ran.
 * @unverified Name was previously used only by callers of this address; the definition was still func_.
 */
void BattleAnim_ApplyEffect1SpeciesMotion(Particle* arg0) {
    f32 offset = 0.0f;
    f32 scale = 0.12f;

    switch (BattleAnim_GetOwnerSpecies(arg0->pokemon)) {
        case BEEDRILL:
            offset = 5.0f;
            break;
        case FEAROW:
            offset = 3.0f;
            break;
        case NIDOQUEEN:
            offset = 5.0f;
            break;
        case NIDOKING:
            offset = 3.0f;
            break;
        case PRIMEAPE:
            offset = 10.0f;
            break;
        case ALAKAZAM:
            offset = 8.0f;
            break;
        case GOLEM:
            offset = 2.0f;
            break;
        case CLOYSTER:
            offset = 5.0f;
            break;
        case GENGAR:
            offset = 5.0f;
            break;
        case HYPNO:
            offset = 5.0f;
            break;
        case KANGASKHAN:
            offset = 12.0f;
            break;
        case PINSIR:
            offset = 3.0f;
            break;
        case TAUROS:
            offset = 3.0f;
            break;
        case GYARADOS:
            scale = D_FLT_82196EC8;
            Particle_Field38_AddYScaled_08E90(arg0, 5.0f);
            break;
        case LAPRAS:
            scale = D_FLT_82196ECC;
            offset = 5.0f;
            break;
        case VAPOREON:
            offset = 3.0f;
            break;
        case FLAREON:
            offset = 3.0f;
            break;
        case AERODACTYL:
            offset = 10.0f;
            break;
        case ZAPDOS:
            offset = 3.0f;
            break;
    }
    Particle_AddPositionOffsetAlongRotationY(arg0, offset + 5.0f);
    Particle_SetScaleScaled(arg0, scale);
}


/**
 * Seen in play (2026-11-13) in the 165-move sweep (each move used once by the 1P Pokémon): it ran
 * only for Sing, Sleep Powder, Hypnosis, Lovely Kiss and Spore.
 */
void BattleAnim_SetupSleepMovePhaseFadeOut(Particle* arg0) {
    BattleAnim_ApplyEffect1SpeciesMotion(arg0);
    Particle_AdvanceLifecycle(arg0);
}

/**
 * Seen in play (2026-11-13) in the 165-move sweep (each move used once by the 1P Pokémon): it ran
 * only for Sing, Sleep Powder, Hypnosis, Lovely Kiss and Spore.
 */
void BattleAnim_SleepMovePhaseFadeOut(Particle* arg0) {
    switch (arg0->lifecycle) {
        case 1:
            BattleAnim_SetupSleepMovePhaseFadeOut(arg0);
            break;

        case 3:
            Particle_ApproachPrimAlphaThenAdvance(arg0, 0, 0x20);
            break;

        case 4:
            Particle_DisableAndDetach(arg0);

        case 2:
            break;
    }
}

/**
 * Effect start init 1 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used:
 * it ran for exactly Hypnosis, Lovely Kiss, Sing, Sleep Powder, Spore.
 */
void func_821542BC(void) {
    func_8213B560(0, &func_82154248, &D_8218E700, 0, 1, 0x10, 7, 0, 0);
}
