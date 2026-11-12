/* Fixed-layout split; original translation-unit boundaries remain unconfirmed. */
#include "battle_engine_339CA0.h"

void BattleAnim_CallbackSharedDescriptor29ScaleAnimFade_InitParticle(Particle* arg0) {
    s16 sp26 = Particle_FieldAC_GetS16_0C038(arg0);
    s16 sp24 = Particle_FieldCF_GetS16_0C058(arg0);

    switch (Particle_FieldCE_GetS32_0C040(arg0)) {
        case 0:
            Particle_Field94_AddX_0A578(arg0, 0x4000);
            break;

        case 1:
            Particle_Field94_AddX_0A578(arg0, -0x3000);
            Particle_Field94_AddY_0A594(arg0, 0x4000);
            Particle_Field94_AddZ_0A5B0(arg0, 0x2000);
            break;

        case 2:
            Particle_Field94_AddX_0A578(arg0, 0x2000);
            Particle_Field94_AddY_0A594(arg0, 0x2000);
            Particle_Field94_AddZ_0A5B0(arg0, 0x2000);
            break;

        case 3:
            Particle_Field94_AddX_0A578(arg0, -0x8000);
            Particle_Field94_AddY_0A594(arg0, 0x2000);
            Particle_Field94_AddZ_0A5B0(arg0, 0x6000);
            break;

        case 4:
            Particle_Field94_AddX_0A578(arg0, -0x4000);
            Particle_Field94_AddY_0A594(arg0, 0x4000);
            Particle_Field94_AddZ_0A5B0(arg0, 0x4000);
            break;
    }

    Particle_Field38_AddYScaled_08E90(arg0, 10.0f);
    Particle_AddPositionFromRotationTemplate1(arg0, (sp26 - 1) * 10.0f);
    Particle_Field1C_SetScaled_0B938(arg0, 1.0f);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, sp24);
    Particle_AdvanceLifecycle(arg0);
}

void func_8215FAA4(s8 *arg0) {
    s16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_8215F930(arg0);
        break;
    case 2:
        func_8213CCEC(arg0, 0, 7, 1, 1, 0);
        break;
    case 3:
        func_82140548(arg0, 0, 0x40);
        break;
    case 4:
        func_8213C930(arg0);
        break;
    }
    func_82140228(arg0, 0x40600000, 0x3E800000);
}

void BattleAnim_CallbackEndEffect3Descriptor29DirectionalScaleFade_InitParticle(Particle* arg0) {
    s16 sp26 = Particle_FieldAC_GetS16_0C038(arg0);

    Particle_FieldCF_GetS16_0C058(arg0);

    switch (sp26) {
        case 0:
            Particle_Field94_AddX_0A578(arg0, 0x5800);
            Particle_Field94_AddY_0A594(arg0, 0x5800);
            Particle_Field94_AddZ_0A5B0(arg0, -0x6000);
            break;

        case 1:
            Particle_Field94_AddX_0A578(arg0, 0x6000);
            Particle_Field94_AddY_0A594(arg0, 0);
            Particle_Field94_AddZ_0A5B0(arg0, 0x5800);
            break;

        case 2:
            Particle_Field94_AddX_0A578(arg0, 0x2000);
            Particle_Field94_AddY_0A594(arg0, 0x2000);
            Particle_Field94_AddZ_0A5B0(arg0, 0x2000);
            break;

        case 3:
            Particle_Field94_AddX_0A578(arg0, 0x6000);
            break;

        case 4:
            Particle_Field94_AddX_0A578(arg0, 0);
            Particle_Field94_AddY_0A594(arg0, 0);
            Particle_Field94_AddZ_0A5B0(arg0, 0);
            break;

        case 5:
            Particle_Field94_AddX_0A578(arg0, 0x6000);
            Particle_Field94_AddY_0A594(arg0, 0x2800);
            Particle_Field94_AddZ_0A5B0(arg0, 0x5800);
            break;
    }

    Particle_Field38_AddYScaled_08E90(arg0, 10.0f);
    Particle_Field1C_SetScaled_0B938(arg0, 1.0f);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, 0xC);
    Particle_FieldA6_SetS16_0BCA8(arg0, sp26 * 3);
    Particle_DisableRendering(arg0);
    Particle_AdvanceLifecycle(arg0);
}

void BattleAnim_CallbackEndEffect3Descriptor29DirectionalScaleFade(Particle* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            BattleAnim_CallbackEndEffect3Descriptor29DirectionalScaleFade_InitParticle(arg0);
            break;

        case 2:
            if (Particle_FieldA6_DecrementToZeroStep1AndStepState_0BDD0(arg0) != 0) {
                Particle_EnableRendering(arg0);
            }
            break;

        case 3:
            func_8213CCEC(arg0, 0, 7, 1, 1, 0);
            Particle_Field1C_Approach_0B98C(arg0, 3.5f, 0.25f);
            break;

        case 4:
            Particle_PrimAlpha_ApproachAndStepState_0BC5C(arg0, 0, 0x40);
            Particle_Field1C_Approach_0B98C(arg0, 3.5f, 0.25f);
            break;

        case 5:
            Particle_MarkInactive(arg0);
            break;
    }
}

void BattleAnim_CallbackSharedDescriptor29DirectionalScatterFade_InitParticle(Particle* arg0) {
    s16 sp26 = Particle_FieldAC_GetS16_0C038(arg0);
    s16 sp24 = Particle_FieldCF_GetS16_0C058(arg0);

    switch (sp26) {
        case 0:
            Particle_Field94_AddX_0A578(arg0, 0x5800);
            Particle_Field94_AddY_0A594(arg0, 0x5800);
            Particle_Field94_AddZ_0A5B0(arg0, -0x6000);
            break;

        case 1:
            Particle_Field94_AddX_0A578(arg0, 0x6000);
            Particle_Field94_AddY_0A594(arg0, 0);
            Particle_Field94_AddZ_0A5B0(arg0, 0x5800);
            break;

        case 2:
            Particle_Field94_AddX_0A578(arg0, 0x2000);
            Particle_Field94_AddY_0A594(arg0, 0x2000);
            Particle_Field94_AddZ_0A5B0(arg0, 0x2000);
            break;

        case 3:
            Particle_Field94_AddX_0A578(arg0, 0x6000);
            break;

        case 4:
            Particle_Field94_AddX_0A578(arg0, 0);
            Particle_Field94_AddY_0A594(arg0, 0);
            Particle_Field94_AddZ_0A5B0(arg0, 0);
            break;

        case 5:
            Particle_Field94_AddX_0A578(arg0, 0x6000);
            Particle_Field94_AddY_0A594(arg0, 0x2800);
            Particle_Field94_AddZ_0A5B0(arg0, 0x5800);
            break;
    }

    switch (sp24) {
        case 0:
            Particle_SetRandomVelocityXSymmetric(arg0, 0xA, 3);
            Particle_SetRandomVelocityYOffset(arg0, 0xF, 0xA);
            Particle_SetRandomVelocityZSymmetric(arg0, 0xF, 3);
            ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, 0xD);
            break;

        case 1:
            Particle_SetRandomVelocityXSymmetric(arg0, 0xA, 5);
            Particle_SetRandomVelocityYOffset(arg0, 0x14, 5);
            Particle_SetRandomVelocityZSymmetric(arg0, 0xA, 5);
            ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, 0xE);
            break;
    }

    Particle_Field1C_SetScaled_0B938(arg0, 1.0f);
    Particle_FieldA6_SetS16_0BCA8(arg0, sp26 * 2);
    Particle_DisableRendering(arg0);
    Particle_AdvanceLifecycle(arg0);
}

void BattleAnim_CallbackSharedDescriptor29DirectionalScatterFade(Particle* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            BattleAnim_CallbackSharedDescriptor29DirectionalScatterFade_InitParticle(arg0);
            break;

        case 2:
            if (Particle_FieldA6_DecrementToZeroStep1AndStepState_0BDD0(arg0) != 0) {
                Particle_EnableRendering(arg0);
            }
            break;

        case 3:
            func_8213CCEC(arg0, 0, 7, 2, 1, 0);
            break;

        case 4:
            Particle_MarkInactive(arg0);
            break;
    }
}

void func_8216008C(Particle* arg0) {
    Particle_Field1C_SetScaled_0B938(arg0, 1.0f);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, Particle_FieldCF_GetS16_0C058(arg0));
    Particle_Field94_AddZ_0A5B0(arg0, 0x2500);
    Particle_AdvanceLifecycle(arg0);
}

void func_821600E0(s8 *arg0) {
    s16 sp26;
    s16 temp_v1;

    sp26 = func_8213C464();
    temp_v1 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v1) {                              /* irregular */
    case 1:
        func_8216008C(arg0);
        break;
    case 2:
        func_8213CA80(arg0, 0x14);
        break;
    case 3:
        func_8213C938(arg0);
        break;
    }
    func_82140228(arg0, 0x40C66666, 0x3F800000);
    if (sp26 == 0) {
        func_821403B0(arg0, 0, 0x18);
        func_821403E0(arg0, 0, 0x18);
        func_821404DC(arg0, 0, 0x18);
        func_821404AC(arg0, 0, 0x18);
    }
}

void func_821601C0(Particle* arg0) {
    Particle_Field1C_SetScaled_0B938(arg0, 1.0f);
    func_8213D3FC(arg0, 320.0f, 0.0f, 0.0f);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, Particle_FieldCF_GetS16_0C058(arg0));
    Particle_Field94_AddZ_0A5B0(arg0, -0x2800);
    Particle_AdvanceLifecycle(arg0);
}

void func_82160230(s8 *arg0) {
    s16 sp26;
    s16 temp_v1;

    sp26 = func_8213C464();
    temp_v1 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v1) {                              /* irregular */
    case 1:
        func_821601C0(arg0);
        break;
    case 2:
        func_8213CA80(arg0, 0x14);
        break;
    case 3:
        func_8213C930(arg0);
        break;
    }
    func_82140228(arg0, 0x40C00000, 0x3F800000);
    if (sp26 == 0) {
        func_821403B0(arg0, 0, 0x18);
        func_821403E0(arg0, 0, 0x18);
        func_821404DC(arg0, 0, 0x18);
        func_821404AC(arg0, 0, 0x18);
    }
    func_82140518(arg0, 0, 0x10);
}

void BattleAnim_CallbackSharedOwnerKeyedAnimGrowFade_InitParticle(Particle* arg0) {
    s16 sp26 = Particle_FieldCE_GetS32_0C040(arg0);
    s16 sp24 = Particle_FieldCF_GetS16_0C058(arg0);

    Particle_Field1C_SetScaled_0B938(arg0, 1.0f);
    Particle_Field94_AddX_0A578(arg0, 0x2000);
    Particle_Field94_AddY_0A594(arg0, 0x4000);

    switch (sp26) {
        case 0:
            Particle_Field38_AddYScaled_08E90(arg0, -10.0f);
            break;

        case 2:
            Particle_Field38_AddYScaled_08E90(arg0, 10.0f);
            break;
    }

    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, sp24);
    Particle_AdvanceLifecycle(arg0);
}

void func_821603C8(s8 *arg0) {
    s16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_8216031C(arg0);
        break;
    case 2:
        func_8213CA80(arg0, 8);
        break;
    case 3:
        func_82140548(arg0, 0, 0x20);
        break;
    case 4:
        func_8213C938(arg0);
        break;
    }
    func_8213CC10(arg0, 0, 7, 1, 2, 0);
    func_82140228(arg0, 0x40A00000, 0x3ECCCCCD);
}

void BattleAnim_CallbackEndEffects39And41And45And46And83Descriptor3DMetadataBurstChild_InitParticle(Particle* arg0) {
    s16 sp26 = Particle_FieldAC_GetS16_0C038(arg0);
    s16 sp24 = Particle_FieldCF_GetS16_0C058(arg0);

    Particle_Field1C_SetScaled_0B938(arg0, 1.0f);
    Particle_Field74_SetScaled_0AD8C(arg0, 0.4f);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, sp24);
    Particle_SetPrimAlpha(arg0, 0x64);
    Particle_FieldA6_SetS16_0BCA8(arg0, sp26 * 4);
    Particle_DisableRendering(arg0);
    Particle_AdvanceLifecycle(arg0);
}

void func_82160528(s8 *arg0) {
    s16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_82160494(arg0);
        return;
    case 2:
        if (func_8213CA80(arg0, M2C_FIELD(arg0, s16 *, 0xA2)) != 0) {
            func_8213CB3C(arg0);
            return;
        }
        return;
    case 3:
        func_8213CCEC(arg0, 0, 7, 1, 2, 0);
        func_82140518(arg0, 0x64, 6);
        func_8213E6BC(arg0);
        return;
    case 4:
        func_8213C930(arg0);
        break;
    }
}

void func_821605F8(s8 *arg0) {
    s16 sp26;
    u16 sp24;

    sp26 = func_8213C47C();
    sp24 = func_8213C484(arg0);
    func_821401D4(arg0, 0x3E800000);
    M2C_FIELD(arg0, f32 *, 0x5C) = (f32) ((func_8000F150() * 0.5f) + 0.25f);
    func_8213EDB0(arg0, (s16) (0x1800 - ((0x3000 / func_8213C494(arg0)) * sp26)));
    func_8213F628(arg0, (2.0f * func_8000F150()) + 3.0f);
    func_82143478(arg0, sp24);
    func_8214050C(arg0, 0xB4);
    func_8213C9D0(arg0);
}

void func_82160704(s8 *arg0) {
    s16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_821605F8(arg0);
        return;
    case 2:
        func_8213CCEC(arg0, 0, 7, 1, 2, 0);
        func_82140228(arg0, 0x3F400000, 0x3CCCCCCD);
        func_8213F658(arg0, 0.5f, 0.25f);
        func_8213E1FC(arg0, M2C_FIELD(arg0, s32 *, 0x5C));
        func_8213E4D8(arg0);
        return;
    case 3:
        func_82140548(arg0, 0, 0x20);
        return;
    case 4:
        func_8213C930(arg0);
        return;
    }
}

void func_821607E8(s8 *arg0) {
    s16 sp26;
    u16 sp24;

    sp26 = func_8213C47C();
    sp24 = func_8213C484(arg0);
    func_821401D4(arg0, 0x3F000000);
    M2C_FIELD(arg0, f32 *, 0x5C) = (f32) ((func_8000F150() * 0.5f) + 0.25f);
    func_8213EDB0(arg0, (s16) (0x1800 - ((0x3000 / func_8213C494(arg0)) * sp26)));
    func_8213F628(arg0, (func_8000F150() * 2.5f) + 3.0f);
    func_82143478(arg0, sp24);
    func_8214050C(arg0, 0xB4);
    func_8213C9D0(arg0);
}

void func_821608FC(s8 *arg0) {
    s16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_821607E8(arg0);
        break;
    case 2:
        func_8213CCEC(arg0, 0, 7, 1, 3, 0);
        func_82140228(arg0, 0x3F800000, 0x3D4CCCCD);
        func_8213F658(arg0, 0.5f, 0.25f);
        func_8213E1FC(arg0, M2C_FIELD(arg0, s32 *, 0x5C));
        break;
    case 3:
        if (func_82140518(arg0, 0, 0x20) != 0) {
            func_8213C9D0(arg0);
        }
        break;
    case 4:
        func_8213C930(arg0);
        break;
    }
    func_8213E4D8(arg0);
}

void BattleAnim_CallbackStartEffect31Descriptor49TieredRiseImpulseFade_InitParticle(Particle* arg0) {
    UNUSED s16 pad; // FAKE: stack padding
    s16 sp24 = Particle_FieldAC_GetS16_0C038(arg0);

    Particle_Field1C_SetScaled_0B938(arg0, 0.25f);
    arg0->unk_5C.y = (MathUtil_Random_ZeroOne() * 0.5f) + 0.4f;
    Particle_Field94_AddY_0A594(arg0, 0x800 - ((0x1000 / func_8213C494(arg0)) * sp24));
    Particle_Field74_SetScaled_0AD8C(arg0, (2.0f * MathUtil_Random_ZeroOne()) + 5.0f);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, 0x32);
    Particle_SetPrimAlpha(arg0, 0xFF);
    Particle_AdvanceLifecycle(arg0);
}

void func_82160AF0(s8 *arg0) {
    s16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_821609F0(arg0);
        return;
    case 2:
        func_8213CCEC(arg0, 0, 7, 1, 2, 0);
        func_82140518(arg0, 0x64, 9);
        func_82140228(arg0, 0x3ECCCCCD, 0x3CCCCCCD);
        func_8213E1FC(arg0, M2C_FIELD(arg0, s32 *, 0x5C));
        func_8213E4D8(arg0);
        return;
    case 3:
        func_8213C930(arg0);
        return;
    }
}

void func_82160BB8(s8 *arg0) {
    s16 sp26;

    sp26 = func_8213C47C();
    func_821401D4(arg0, 0x3ECCCCCD);
    func_8213DDB8(arg0, 0, 0, 0xA);
    M2C_FIELD(arg0, f32 *, 0x5C) = (f32) ((func_8000F150() * 0.5f) + 0.25f);
    func_8213EDB0(arg0, (s16) (0x2000 - ((0x4000 / func_8213C494(arg0)) * sp26)));
    func_8213F628(arg0, func_8000F150() + 1.0f);
    func_82143478(arg0, 0xA);
    func_8214050C(arg0, 0x64);
    func_8213C9D0(arg0);
}

void func_82160CCC(s8 *arg0) {
    s16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_82160BB8(arg0);
        return;
    case 2:
        func_8213CCEC(arg0, 0, 7, 1, 2, 0);
        func_82140228(arg0, 0x3F400000, 0x3CCCCCCD);
        func_8213F658(arg0, 0.5f, 0.2f);
        func_8213E1FC(arg0, M2C_FIELD(arg0, s32 *, 0x5C));
        func_8213E4D8(arg0);
        return;
    case 3:
        if (func_82140518(arg0, 0, 0x20) != 0) {
            func_8213C9D0(arg0);
            return;
        }
        return;
    case 4:
        func_8213C930(arg0);
        break;
    }
}

void BattleAnim_CallbackEndEffect55Descriptor49RiseGravityFade_InitParticle(Particle* arg0) {
    s16 sp26 = Particle_FieldAC_GetS16_0C038(arg0);

    Particle_Field1C_SetScaled_0B938(arg0, 0.3f);
    Particle_SetRandomVelocityXYZ(arg0, 0xA, 5, 0xA);
    Particle_Field38_AddYScaled_08E90(arg0, 15.0f);
    Particle_Field74_SetScaled_0AD8C(arg0, (ParticleMath_RandomRange(0xA) * 0.1f) + 1.5f);
    Particle_FieldA6_SetS16_0BCA8(arg0, sp26 * 2);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, 0x32);
    Particle_SetPrimAlpha(arg0, 0xFF);
    Particle_DisableRendering(arg0);
    Particle_AdvanceLifecycle(arg0);
}

void func_82160EAC(s8 *arg0) {
    s16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_82160DC4(arg0);
        return;
    case 2:
        if (func_8213CA80(arg0, M2C_FIELD(arg0, s16 *, 0xA2)) != 0) {
            func_8213CB3C(arg0);
            return;
        }
        return;
    case 3:
        func_82140228(arg0, 0x3F000000, 0x3CA3D70A);
        func_8213CC10(arg0, 0, 7, 1, 2, 0);
        func_82140518(arg0, 0x64, 6);
        if (func_8213E7A0(arg0) != 0) {
            func_8213C9D0(arg0);
            return;
        }
        break;
    case 4:
        func_8213C930(arg0);
        break;
    }
}

void BattleAnim_CallbackSharedDescriptors3EAnd3FAnimatedRiseFade_InitParticle(Particle* arg0) {
    s16 sp26 = Particle_FieldAC_GetS16_0C038(arg0);

    Particle_Field1C_SetScaled_0B938(arg0, 0.25f);
    Particle_Field94_AddY_0A594(arg0, sp26 << 0xC);
    Particle_Field74_SetScaled_0AD8C(arg0, (2.0f * MathUtil_Random_ZeroOne()) + 6.0f);
    Particle_Field7C_SetYScaled_0AF24(arg0, (MathUtil_Random_ZeroOne() * 3.0f) + 1.0f);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, 0xA);
    Particle_SetPrimAlpha(arg0, 0x64);
    Particle_FieldA6_SetS16_0BCA8(arg0, 7);
    Particle_AdvanceLifecycle(arg0);
}

void func_82161074(Particle* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            BattleAnim_CallbackSharedDescriptors3EAnd3FAnimatedRiseFade_InitParticle(arg0);
            break;

        case 2:
            func_8213CCEC((s8*)arg0, 0, 7, 1, 2, 0);
            Particle_Field1C_Approach_0B98C(arg0, 0.8f, 0.1f);
            func_8213F658((s8*)arg0, 1.0, 1.0f);
            if (Particle_FieldA6_DecrementToZeroStep1_0BDAC(arg0) != 0) {
                Particle_Field7C_ApproachY_0B180(arg0, 0.5f, 0.4f);
                Particle_Field50_AddXFromField7C_09C58(arg0);
            }
            break;

        case 3:
            Particle_Field50_AddXFromField7C_09C58(arg0);
            Particle_PrimAlpha_ApproachAndStepState_0BC5C(arg0, 0, 0x20);
            break;

        case 4:
            Particle_MarkInactive(arg0);
            break;
    }

    if (Particle_IsRunning(arg0) != 0) {
        Particle_AddVelocityXZFromRotationYViaImpulse(arg0);
    }
}

void BattleAnim_CallbackEndEffect67Descriptor3DAnimatedGravityFade_InitParticle(Particle* arg0) {
    s16 sp26 = Particle_FieldAC_GetS16_0C038(arg0);

    switch (Particle_FieldCF_GetS16_0C058(arg0)) {
        case 0:
            Particle_Field1C_SetScaled_0B938(arg0, 0.75f);
            Particle_SetRandomVelocityXYZ(arg0, 0xF, 0xF, 0xF);
            Particle_Field38_AddYScaled_08E90(arg0, 15.0f);
            Particle_Field74_SetScaled_0AD8C(arg0, 1.0f);
            break;

        case 1:
            Particle_Field1C_SetScaled_0B938(arg0, 0.5f);
            Particle_SetRandomVelocityXYZ(arg0, 3, 3, 3);
            Particle_Field74_SetScaled_0AD8C(arg0, 0.4f);
            break;
    }

    Particle_FieldA6_SetS16_0BCA8(arg0, sp26 * 4);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, 0x13);
    Particle_SetPrimAlpha(arg0, 0xC8);
    Particle_DisableRendering(arg0);
    Particle_AdvanceLifecycle(arg0);
}

void func_82161288(s8 *arg0) {
    s16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_82161190(arg0);
        return;
    case 2:
        if (func_8213CA80(arg0, M2C_FIELD(arg0, s16 *, 0xA2)) != 0) {
            func_8213CB3C(arg0);
            return;
        }
        return;
    case 3:
        func_8213CCEC(arg0, 0, 7, 1, 2, 0);
        func_82140518(arg0, 0x64, 6);
        func_8213E7A0(arg0);
        return;
    case 4:
        func_8213C930(arg0);
        break;
    }
}

void BattleAnim_CallbackOrphanDescriptor34ColorFadeDetach_InitParticle(Particle* arg0) {
    s16 sp26 = Particle_FieldAC_GetS16_0C038(arg0);

    Particle_SetRandomRotatedVelocityXY(arg0, 0xF, 0xF);
    Particle_Field1C_SetScaled_0B938(arg0, 1.0f);
    Particle_Field74_SetScaled_0AD8C(arg0, 0.2f);
    Particle_SetPrimColor(arg0, 0xFF, 0xFF, 0xFF);
    Particle_SetEnvColor(arg0, 0xFF, 0x64, 0);
    Particle_SetPrimAlpha(arg0, 0xFF);
    Particle_FieldA6_SetS16_0BCA8(arg0, sp26 * 4);
    Particle_DisableRendering(arg0);
    Particle_AdvanceLifecycle(arg0);
}

void func_8216140C(s8 *arg0) {
    s16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_82161358(arg0);
        return;
    case 2:
        if (func_8213CA80(arg0, M2C_FIELD(arg0, s16 *, 0xA2)) != 0) {
            func_8213CB3C(arg0);
            return;
        }
        return;
    case 3:
        func_8213CCEC(arg0, 0, 7, 1, 2, 0);
        func_82140380(arg0, 0x64, 9);
        func_8214047C(arg0, 0, 0x10);
        func_821404DC(arg0, 0x32, 3);
        func_821404AC(arg0, 0xFF, 0x10);
        if (func_8213CA04(arg0, 8) != 0) {
            func_82140518(arg0, 0, 0x20);
        }
        func_8213E6BC(arg0);
        return;
    case 4:
        func_8213C938(arg0);
        break;
    }
}

void BattleAnim_CallbackSharedDescriptor36ScaleAlphaFade_InitParticle(Particle* arg0) {
    Particle_Field1C_SetScaled_0B938(arg0, 0.1f);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, 0x14);
    Particle_SetPrimAlpha(arg0, 0xFF);
    Particle_AdvanceLifecycle(arg0);
}

void BattleAnim_CallbackSharedDescriptor36ScaleAlphaFade(Particle* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            BattleAnim_CallbackSharedDescriptor36ScaleAlphaFade_InitParticle(arg0);
            break;

        case 2:
            Particle_Field1C_Approach_0B98C(arg0, 0.75f, 0.08125f);
            Particle_PrimAlpha_ApproachAndStepState_0BC5C(arg0, 0, 0x20);
            break;

        case 3:
            Particle_DisableAndDetach(arg0);
            break;
    }
}

void BattleAnim_SetupUnusedGlitterVariant(Particle* arg0) {
    Vec3s sp28;

    Particle_FieldAC_GetS16_0C038(arg0);
    Particle_Field1C_SetScaled_0B938(arg0, 0.1f);
    sp28.x = MathUtil_Random16();
    sp28.y = MathUtil_Random16();
    sp28.z = 0;
    Particle_Field94_SetVecFromVec3s_0A24C(arg0, sp28);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, 0x15);
    Particle_SetPrimAlpha(arg0, 0xFF);
    Particle_FieldA6_SetS16_0BCA8(arg0, ParticleMath_RandomRange(5) + 8);
    Particle_Field74_SetScaled_0AD8C(arg0, 5.0f);
    Particle_AdvanceLifecycle(arg0);
}

void func_821616BC(s8 *arg0) {
    s16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_821615F8(arg0);
        break;
    case 2:
        func_8213F658(arg0, 2.0f, 0.5f);
        if ((func_82140690(arg0) != 0) && (func_82140518(arg0, 0, 0x40) != 0)) {
            func_8213C9D0(arg0);
        }
        break;
    case 3:
        func_8213C930(arg0);
        break;
    }
    if (func_8213C9B0(arg0) != 0) {
        func_8213E528(arg0);
    }
}

void BattleAnim_CallbackEndEffects37And38Descriptor38BurstChild_InitParticle(Particle* arg0) {
    Vec3s sp28;
    s16 sp26 = Particle_FieldCF_GetS16_0C058(arg0);

    Particle_FieldAC_GetS16_0C038(arg0);

    sp28.x = ParticleMath_RandomSigned(0x2000);
    sp28.y = ParticleMath_RandomSignedOffset(0x2000, 0x8000);
    sp28.z = 0;
    Particle_Field94_AddVecFromVec3s_0A4F0(arg0, sp28);

    switch (sp26) {
        case 0:
            Particle_Field1C_SetScaled_0B938(arg0, 0.2f);
            ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, 0x15);
            break;

        case 1:
            Particle_Field1C_SetScaled_0B938(arg0, 0.2f);
            ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, 0x1B);
            break;
    }

    Particle_SetPrimAlpha(arg0, 0xFF);
    Particle_FieldA6_SetS16_0BCA8(arg0, ParticleMath_RandomRange(5) + 8);
    Particle_Field74_SetScaled_0AD8C(arg0, 6.0f);
    Particle_AdvanceLifecycle(arg0);
}

void func_82161890(s8 *arg0) {
    s16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_8216177C(arg0);
        break;
    case 2:
        func_82140228(arg0, 0x3DCCCCCD, 0x3C23D70A);
        func_8213F658(arg0, 3.0f, 0.75f);
        if ((func_82140690(arg0) != 0) && (func_82140518(arg0, 0, 0x40) != 0)) {
            func_8213C9D0(arg0);
        }
        break;
    case 3:
        func_8213C930(arg0);
        break;
    }
    if (func_8213C9B0(arg0) != 0) {
        func_8213E528(arg0);
    }
}

void BattleAnim_CallbackSharedDescriptor3DAnimatedColorMotion_InitParticle(Particle* arg0) {
    Vec3s sp28;
    s16 sp26 = Particle_FieldCF_GetS16_0C058(arg0);

    Particle_FieldAC_GetS16_0C038(arg0);
    Particle_Field1C_SetScaled_0B938(arg0, 1.0f);

    switch (sp26) {
        case 0:
            ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, 8);
            Particle_SetPrimAlpha(arg0, 0x64);
            Particle_Field74_SetScaled_0AD8C(arg0, 5.0f);
            sp28.x = ParticleMath_RandomSigned(0x2000);
            sp28.y = ParticleMath_RandomSignedOffset(0x2000, 0x8000);
            sp28.z = 0;
            Particle_Field94_AddVecFromVec3s_0A4F0(arg0, sp28);
            break;

        case 1:
            ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, 8);
            Particle_SetPrimAlpha(arg0, 0x64);
            Particle_Field74_SetScaled_0AD8C(arg0, 5.0f);
            sp28.x = ParticleMath_RandomSigned(0x2000);
            sp28.y = ParticleMath_RandomSignedOffset(0x2000, 0x8000);
            sp28.z = 0;
            Particle_Field94_AddVecFromVec3s_0A4F0(arg0, sp28);
            break;

        case 2:
            ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, 8);
            Particle_SetPrimAlpha(arg0, 0x64);
            Particle_Field38_SetYScaled_08CA0(arg0, -10.0f);
            Particle_Field74_SetScaled_0AD8C(arg0, 5.0f);
            sp28.x = ParticleMath_RandomSigned(0x2000);
            sp28.y = ParticleMath_RandomSignedOffset(0x2000, 0x8000);
            sp28.z = 0;
            Particle_Field94_AddVecFromVec3s_0A4F0(arg0, sp28);
            break;

        case 3:
            ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, 9);
            Particle_SetPrimAlpha(arg0, 0x96);
            Particle_Field74_SetScaled_0AD8C(arg0, 3.0f);
            sp28.x = ParticleMath_RandomSigned(0x2000);
            sp28.y = ParticleMath_RandomSignedOffset(0x2000, 0x8000);
            sp28.z = 0;
            Particle_Field94_AddVecFromVec3s_0A4F0(arg0, sp28);
            break;

        case 4:
            ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, 5);
            Particle_SetPrimAlpha(arg0, 0x96);
            Particle_Field74_SetScaled_0AD8C(arg0, 4.0f);
            sp28.x = ParticleMath_RandomSigned(0x3000);
            sp28.y = ParticleMath_RandomSignedOffset(0x3000, 0x8000);
            sp28.z = 0;
            Particle_Field94_AddVecFromVec3s_0A4F0(arg0, sp28);
            break;
    }

    Particle_FieldA6_SetS16_0BCA8(arg0, ParticleMath_RandomRange(5) + 8);
    Particle_AdvanceLifecycle(arg0);
}

void BattleAnim_CallbackSharedDescriptor3DAnimatedColorMotion(Particle* arg0) {
    s16 sp2E = Particle_FieldCF_GetS16_0C058(arg0);

    switch (arg0->unk_B2) {
        case 1:
            BattleAnim_CallbackSharedDescriptor3DAnimatedColorMotion_InitParticle(arg0);
            break;
        case 2:
            func_8213CCEC(arg0, 0, 7, 1, 2, 0);

            switch (sp2E) {
                case 3:
                    Particle_PrimR_Approach_0BAE4(arg0, 0, 9);
                    func_8213F658(arg0, 1.0f, 0.75f);
                    Particle_PrimAlpha_Approach_0BC2C(arg0, 0x32, 6);
                    break;

                case 4:
                    func_8213F658(arg0, 1.0f, 0.75f);
                    Particle_Field38_AddYScaled_08E90(arg0, 0.5f);
                    Particle_PrimAlpha_Approach_0BC2C(arg0, 0x32, 6);
                    break;

                default:
                    Particle_PrimG_Approach_0BB14(arg0, 0x64, 6);
                    func_8213F658(arg0, 2.0f, 0.5f);
                    break;
            }
            break;

        case 3:
            Particle_MarkInactive(arg0);
            break;
    }

    if (Particle_IsRunning(arg0) != 0) {
        Particle_AddVelocityFromRotationTemplate1(arg0);
    }
}

void BattleAnim_CallbackEndEffect52Descriptor42BurstChild_InitParticle(Particle* arg0) {
    s16 sp2E = Particle_FieldAC_GetS16_0C038(arg0);
    Vec3s sp28;

    Particle_Field1C_SetScaled_0B938(arg0, 0.1f);
    sp28.x = ParticleMath_RandomRange(0x10000);
    sp28.y = ParticleMath_RandomRange(0x10000);
    sp28.z = 0;
    Particle_Field94_SetVecFromVec3s_0A24C(arg0, sp28);
    Particle_Field9A_SetZ_0A3EC(arg0, ParticleMath_RandomSignedOffsetBySign(0x400, 0x400));
    Particle_Field74_SetScaled_0AD8C(arg0, 8.0f);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, 0x17);
    Particle_FieldA6_SetS16_0BCA8(arg0, sp2E * 0);
    Particle_DisableRendering(arg0);
    Particle_AdvanceLifecycle(arg0);
}

void BattleAnim_CallbackEndEffect52Descriptor42BurstChild(Particle* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            BattleAnim_CallbackEndEffect52Descriptor42BurstChild_InitParticle(arg0);
            break;

        case 2:
            if (Particle_FieldA6_DecrementToZeroStep1AndStepState_0BDD0(arg0) != 0) {
                Particle_EnableRendering(arg0);
            }
            break;

        case 3:
            Particle_Field1C_ApproachAndStepState_0B9D0(arg0, 0.3f, 0.05f);
            func_8213F658(arg0, 3.0f, 1.0f);
            break;

        case 4:
            Particle_TickDelayAndAdvanceLifecycle(arg0, 2);
            break;

        case 5:
            Particle_Field1C_ApproachAndStepState_0B9D0(arg0, 0.05f, 0.05f);
            break;

        case 6:
            Particle_MarkInactive(arg0);
            break;
    }

    if (Particle_IsRenderingEnabled(arg0) != 0) {
        Particle_Field94_AddZFromField9A_0A4DC(arg0);
        Particle_Field7C_SetVecFromField74AnglesXY_0B2B4(arg0);
        func_8213E3F8(arg0);
    }
}

void BattleAnim_SetupEndEffect52DefaultBurstChild(Particle* arg0) {
    BattleAnim_EmitParticleBurst(arg0, BattleAnim_CallbackEndEffect52Descriptor42BurstChild, &gBattleAnimParticleDescriptors[0x42], 0xC);
    Particle_AdvanceLifecycle(arg0);
}

void BattleAnim_CallbackEndEffect52DefaultBurstEmitter(Particle* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            BattleAnim_SetupEndEffect52DefaultBurstChild(arg0);
            break;

        case 2:
            Particle_MarkInactive(arg0);
            break;
    }
}

void BattleAnim_SetupSharedScalePulseFallSetup(Particle* arg0) {
    s16 sp2E = Particle_FieldAC_GetS16_0C038(arg0);
    s16 sp2C = Particle_FieldCE_GetS32_0C040(arg0);
    s16 sp2A = Particle_FieldCF_GetS16_0C058(arg0);
    Vec3s sp24;

    sp24.x = ParticleMath_RandomRange(0x10000);
    sp24.y = ParticleMath_RandomRange(0x10000);
    sp24.z = 0;

    Particle_Field94_SetVecFromVec3s_0A24C(arg0, sp24);
    Particle_Field74_SetScaled_0AD8C(arg0, 0.0f);
    Particle_Field78_SetScaled_0ADA4(arg0, 0.0f);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, sp2A);
    Particle_Field1C_SetScaled_0B938(arg0, 0.0f);
    Particle_SetScaleSpeed(arg0, 0.3f);
    Particle_SetScaleTarget(arg0, 0.05f);
    Particle_FieldA6_SetS16_0BCA8(arg0, sp2E * 2);

    switch (sp2C) {
        case 0:
            Particle_AddPositionFromRotationTemplate1(arg0, ParticleMath_RandomRangeOffset(0x1E, 0xA));
            Particle_SetScaleSpeed(arg0, 0.2f);
            break;

        case 1:
            Particle_AddPositionFromRotationTemplate1(arg0, ParticleMath_RandomRangeOffset(0x28, 0xA));
            Particle_SetScaleSpeed(arg0, 0.3f);
            Particle_SetScaleTarget(arg0, 0.04f);
            break;

        case 2:
            Particle_SetScaleSpeed(arg0, 0.1f);
            Particle_SetScaleTarget(arg0, 0.03f);
            Particle_AddPositionFromRotationTemplate1(arg0, ParticleMath_RandomRangeOffset(0xC, 5));
            Particle_FieldA6_SetS16_0BCA8(arg0, sp2E * 1);  // FAKE
            break;

        case 3:
            Particle_Field74_SetScaled_0AD8C(arg0, 0.2f);
            Particle_Field1C_SetScaled_0B938(arg0, 0.1f);
            Particle_AddPositionFromRotationTemplate1(arg0, ParticleMath_RandomRangeOffset(0x14, 0x1E));
            Particle_FieldA6_SetS16_0BCA8(arg0, sp2E * 4);
            break;

        case 5:
            Particle_SetRandomVelocityXYZ(arg0, 0, 0xF, 0x19);
            Particle_Field38_AddYScaled_08E90(arg0, 15.0f);
            Particle_SetScaleSpeed(arg0, 0.15f);
            Particle_SetScaleTarget(arg0, 0.02f);
            Particle_Field74_SetScaled_0AD8C(arg0, 0.1f);
            break;

        case 6:
            Particle_AddPositionFromRotationTemplate1(arg0, ParticleMath_RandomRangeOffset(0x1E, 0x14));
            Particle_Field74_SetScaled_0AD8C(arg0, 0.3f);
            break;

        case 8:
            Particle_AddPositionFromRotationTemplate1(arg0, ParticleMath_RandomRangeOffset(8, 2));
            Particle_SetScaleSpeed(arg0, 0.1f);
            Particle_SetScaleTarget(arg0, 0.04f);
            Particle_Field74_SetScaled_0AD8C(arg0, 0.4f);
            Particle_FieldA6_SetS16_0BCA8(arg0, 0);
            break;

        case 7:
            Particle_AddPositionFromRotationTemplate1(arg0, ParticleMath_RandomRangeOffset(0xA, 2));
            Particle_SetScaleSpeed(arg0, 0.2f);
            Particle_SetScaleTarget(arg0, 0.025f);
            Particle_Field74_SetScaled_0AD8C(arg0, 1.0f);
            break;

        case 9:
            Particle_AddPositionFromRotationTemplate1(arg0, ParticleMath_RandomRangeOffset(0x1E, 0x14));
            Particle_SetScaleSpeed(arg0, 0.3f);
            Particle_SetScaleTarget(arg0, 0.025f);
            Particle_Field74_SetScaled_0AD8C(arg0, 0.0f);
            Particle_Field78_SetScaled_0ADA4(arg0, 0.02f);
            break;

        case 10:
            Particle_AddPositionFromRotationTemplate1(arg0, ParticleMath_RandomRangeOffset(0x19, 5));
            Particle_Field38_AddYScaled_08E90(arg0, 10.0f);
            Particle_SetScaleSpeed(arg0, 0.2f);
            break;

        case 11:
            Particle_AddPositionFromRotationTemplate1(arg0, ParticleMath_RandomRangeOffset(5, 5));
            Particle_Field74_SetScaled_0AD8C(arg0, ParticleMath_RandomRange(5) + 5.0f);
            break;
    }
    Particle_DisableRendering(arg0);
    Particle_AdvanceLifecycle(arg0);
}

void BattleAnim_CallbackSharedDescriptors42And44ScaleFall(Particle* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            BattleAnim_SetupSharedScalePulseFallSetup(arg0);
            break;

        case 2:
            if (Particle_FieldA6_DecrementToZeroStep1AndStepState_0BDD0(arg0) != 0) {
                Particle_EnableRendering(arg0);
            }
            break;

        case 3:
            if (Particle_Field1C_ApproachField24AndStepState_0BA48(arg0) != 0) {
                Particle_SetScaleSpeed(arg0, 0.0f);
            }
            break;

        case 4:
            Particle_Field1C_ApproachField24AndStepState_0BA48(arg0);
            break;

        case 5:
            Particle_MarkInactive(arg0);
            break;
    }

    if (Particle_IsRenderingEnabled(arg0) != 0) {
        Particle_Field74_AdvanceAndAddNegY_CheckField2CYNonPositive_09FD8(arg0);
        if (arg0->unk_2C.y < 0.0f) {
            Particle_MarkInactive(arg0);
        }
    }
}

void BattleAnim_CallbackEndEffect23Descriptor44ScalePulse_InitParticle(Particle* arg0) {
    s16 sp26 = Particle_FieldAC_GetS16_0C038(arg0);
    s16 sp24 = Particle_FieldCF_GetS16_0C058(arg0);

    Particle_Field1C_SetScaled_0B938(arg0, 0.0f);
    Particle_SetScaleSpeed(arg0, 0.3f);
    Particle_SetScaleTarget(arg0, 0.05f);
    Particle_SetRandomVelocityXYZ(arg0, 0xA, 0x14, 0x14);
    Particle_Field38_AddXZFromField94Y_08ED0(arg0, 15.0f);
    Particle_Field38_AddYScaled_08E90(arg0, 7.0f);
    Particle_Field74_SetScaled_0AD8C(arg0, ParticleMath_RandomRange(5) + 8.0f);
    Particle_FieldA6_SetS16_0BCA8(arg0, sp26 * 2);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, sp24);
    Particle_DisableRendering(arg0);
    Particle_AdvanceLifecycle(arg0);
}

void BattleAnim_CallbackEndEffect23Descriptor44ScalePulse(Particle* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            BattleAnim_CallbackEndEffect23Descriptor44ScalePulse_InitParticle(arg0);
            break;

        case 2:
            if (Particle_FieldA6_DecrementToZeroStep1AndStepState_0BDD0(arg0) != 0) {
                Particle_EnableRendering(arg0);
            }
            break;

        case 3:
            if (Particle_Field1C_ApproachField24AndStepState_0BA48(arg0) != 0) {
                Particle_SetScaleSpeed(arg0, 0.0f);
            }
            break;

        case 4:
            Particle_Field1C_ApproachField24AndStepState_0BA48(arg0);
            break;

        case 5:
            Particle_MarkInactive(arg0);
            break;
    }

    if (Particle_IsRenderingEnabled(arg0) != 0) {
        Particle_AddVelocityXZFromRotationYPlusHalfTurn(arg0);
    }
}

void func_821627C0(Particle* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            BattleAnim_SetupSharedScalePulseFallSetup(arg0);
            break;

        case 2:
            if (Particle_FieldA6_DecrementToZeroStep1AndStepState_0BDD0(arg0) != 0) {
                Particle_EnableRendering(arg0);
            }
            break;

        case 3:
            if (Particle_Field1C_ApproachField24AndStepState_0BA48(arg0) != 0) {
                Particle_SetScaleSpeed(arg0, 0.0f);
            }
            break;

        case 4:
            Particle_Field1C_ApproachField24AndStepState_0BA48(arg0);
            break;

        case 5:
            Particle_MarkInactive(arg0);
            break;
    }

    if (Particle_IsRenderingEnabled(arg0) != 0) {
        func_8213E528(arg0);
        if (arg0->unk_2C.y < 0.0f) {
            Particle_MarkInactive(arg0);
        }
    }
}

void BattleAnim_CallbackEndEffect43Descriptor40DelayedAnimFade_InitParticle(Particle* arg0) {
    s16 sp26 = Particle_FieldAC_GetS16_0C038(arg0);

    Particle_Field1C_SetScaled_0B938(arg0, 0.7f);
    Particle_Field38_SetYScaled_08CA0(arg0, 10.0f);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, 0x19);
    Particle_SetPrimAlpha(arg0, 0xFF);
    Particle_FieldA6_SetS16_0BCA8(arg0, sp26 * 4);
    Particle_DisableRendering(arg0);
    Particle_AdvanceLifecycle(arg0);
}

void BattleAnim_CallbackEndEffect43Descriptor40DelayedAnimFade(Particle* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            BattleAnim_CallbackEndEffect43Descriptor40DelayedAnimFade_InitParticle(arg0);
            break;

        case 2:
            if (Particle_TickDelayAndAdvanceLifecycle(arg0, arg0->unk_A6) != 0) {
                Particle_EnableRendering(arg0);
            }
            break;

        case 3:
            func_8213CCEC(arg0, 0, 5, 1, 1, 2);
            break;

        case 4:
            Particle_MarkInactive(arg0);
            break;
    }
}

void BattleAnim_CallbackSharedDescriptor34DelayedFrameMotion_InitParticle(Particle* arg0) {
    s16 sp26 = Particle_FieldAC_GetS16_0C038(arg0);
    s16 sp24 = Particle_FieldCE_GetS32_0C040(arg0);

    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, Particle_FieldCF_GetS16_0C058(arg0));

    switch (sp24) {
        case 1:
            Particle_Field74_SetScaled_0AD8C(arg0, 0.2f);
            Particle_Field1C_SetScaled_0B938(arg0, 1.0f);
            break;

        case 5:
            Particle_Field74_SetScaled_0AD8C(arg0, 0.2f);
            Particle_Field1C_SetScaled_0B938(arg0, 1.0f);
            break;

        case 6:
            Particle_Field74_SetScaled_0AD8C(arg0, 0.4f);
            Particle_Field1C_SetScaled_0B938(arg0, 1.5f);
            break;

        case 16:
            Particle_Field74_SetScaled_0AD8C(arg0, 0.4f);
            Particle_Field1C_SetScaled_0B938(arg0, 2.0f);
            break;

        case 7:
            Particle_Field74_SetScaled_0AD8C(arg0, 0.4f);
            Particle_Field1C_SetScaled_0B938(arg0, 1.5f);
            break;

        case 8:
            Particle_Field74_SetScaled_0AD8C(arg0, 0.4f);
            Particle_Field1C_SetScaled_0B938(arg0, 1.5f);
            Particle_Field38_AddYScaled_08E90(arg0, -10.0f);
            break;

        case 12:
            Particle_Field1C_SetScaled_0B938(arg0, 0.75f);
            Particle_Field74_SetScaled_0AD8C(arg0, 0.4f);
            Particle_SetRandomVelocityXYZ(arg0, 8, 0xA, 8);
            break;

        case 13:
            Particle_Field1C_SetScaled_0B938(arg0, 1.0f);
            Particle_Field74_SetScaled_0AD8C(arg0, 0.0f);
            Particle_SetRandomVelocityX(arg0, 0x1E);
            Particle_SetRandomVelocityYOffset(arg0, 0x14, 0xA);
            Particle_SetRandomVelocityZ(arg0, 0x1E);
            break;

        case 14:
            Particle_Field1C_SetScaled_0B938(arg0, 1.0f);
            Particle_Field74_SetScaled_0AD8C(arg0, 0.0f);
            Particle_SetRandomVelocityX(arg0, 0x14);
            Particle_SetRandomVelocityYOffset(arg0, 0x14, 0xA);
            Particle_SetRandomVelocityZ(arg0, 0xF);
            break;

        case 15:
            Particle_Field1C_SetScaled_0B938(arg0, 1.5f);
            Particle_Field74_SetScaled_0AD8C(arg0, 0.3f);
            Particle_SetRandomVelocityXYZ(arg0, 0xA, 0xA, 0xA);
            break;
    }

    Particle_SetPrimAlpha(arg0, 0xFF);
    Particle_FieldA6_SetS16_0BCA8(arg0, sp26 * 4);
    Particle_DisableRendering(arg0);
    Particle_AdvanceLifecycle(arg0);
}

void BattleAnim_CallbackSharedDescriptor34DelayedFrameMotion(Particle* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            BattleAnim_CallbackSharedDescriptor34DelayedFrameMotion_InitParticle(arg0);
            break;

        case 2:
            if (Particle_TickDelayAndAdvanceLifecycle(arg0, arg0->unk_A6) != 0) {
                Particle_EnableRendering(arg0);
            }
            break;

        case 3:
            func_8213CCEC(arg0, 0, 3, 1, 1, 0);
            Particle_AddVelocityXZFromRotationYPlusHalfTurn(arg0);
            break;

        case 4:
            Particle_MarkInactive(arg0);
            break;
    }
}

void BattleAnim_CallbackEndEffects39And41And45And46And83Descriptor34BurstEmitter_InitParticle(Particle* arg0) {
    s16 sp26 = Particle_FieldAC_GetS16_0C038(arg0);

    switch (Particle_FieldCF_GetS16_0C058(arg0)) {
        case 0:
            ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, 0);
            Particle_Field74_SetScaled_0AD8C(arg0, 0.2f);
            Particle_Field1C_SetScaled_0B938(arg0, 1.0f);
            Particle_FieldA6_SetS16_0BCA8(arg0, sp26 * 2);
            Particle_Field38_AddYScaled_08E90(arg0, 15.0f);
            break;

        case 1:
            ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, 0);
            Particle_Field74_SetScaled_0AD8C(arg0, 0.2f);
            Particle_Field1C_SetScaled_0B938(arg0, 1.0f);
            Particle_FieldA6_SetS16_0BCA8(arg0, sp26 * 2);
            break;

        case 2:
            ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, 0);
            Particle_Field74_SetScaled_0AD8C(arg0, 0.2f);
            Particle_Field1C_SetScaled_0B938(arg0, 1.0f);
            Particle_FieldA6_SetS16_0BCA8(arg0, sp26 * 2);
            Particle_Field38_AddYScaled_08E90(arg0, -10.0f);
            break;

        case 3:
            ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, 1);
            Particle_Field1C_SetScaled_0B938(arg0, 0.5f);
            Particle_Field74_SetScaled_0AD8C(arg0, 0.4f);
            Particle_FieldA6_SetS16_0BCA8(arg0, sp26 * 2);
            break;

        case 4:
            ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, 2);
            Particle_Field1C_SetScaled_0B938(arg0, 0.5f);
            Particle_Field74_SetScaled_0AD8C(arg0, 0.4f);
            Particle_FieldA6_SetS16_0BCA8(arg0, sp26 * 2);
            break;

        case 5:
            ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, 3);
            Particle_Field74_SetScaled_0AD8C(arg0, 0.2f);
            Particle_Field1C_SetScaled_0B938(arg0, 1.0f);
            Particle_FieldA6_SetS16_0BCA8(arg0, sp26 * 2);
            break;

        case 6:
            ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, 0);
            Particle_Field74_SetScaled_0AD8C(arg0, 0.4f);
            Particle_Field1C_SetScaled_0B938(arg0, 1.5f);
            Particle_FieldA6_SetS16_0BCA8(arg0, sp26 * 2);
            break;

        case 9:
            ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, 0);
            Particle_Field74_SetScaled_0AD8C(arg0, 0.2f);
            Particle_Field1C_SetScaled_0B938(arg0, 1.0f);
            Particle_SetRandomVelocityXYZ(arg0, 0xF, 0xF, 0xF);
            Particle_Field38_AddYScaled_08E90(arg0, 10.0f);
            Particle_FieldA6_SetS16_0BCA8(arg0, sp26 * 2);
            break;

        case 10:
            ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, 0);
            Particle_Field74_SetScaled_0AD8C(arg0, 0.2f);
            Particle_Field1C_SetScaled_0B938(arg0, 1.0f);
            Particle_SetRandomVelocityXYZ(arg0, 0x14, 0, 0x14);
            Particle_Field38_SetYScaled_08CA0(arg0, 0.0f);
            Particle_FieldA6_SetS16_0BCA8(arg0, sp26 * 2);
            break;

        case 11:
            ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, 0);
            Particle_Field74_SetScaled_0AD8C(arg0, 0.2f);
            Particle_Field1C_SetScaled_0B938(arg0, 1.0f);
            Particle_SetRandomVelocityXYZ(arg0, 0xA, 0, 0xA);
            Particle_Field38_SetYScaled_08CA0(arg0, 30.0f - (sp26 * 5.0f));
            Particle_FieldA6_SetS16_0BCA8(arg0, sp26 * 2);
            break;
    }

    Particle_SetPrimAlpha(arg0, 0xFF);
    Particle_DisableRendering(arg0);
    Particle_AdvanceLifecycle(arg0);
}

void BattleAnim_CallbackEndEffects39And41And45And46And83Descriptor34BurstEmitter(Particle* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            BattleAnim_CallbackEndEffects39And41And45And46And83Descriptor34BurstEmitter_InitParticle(arg0);
            break;

        case 2:
            if (Particle_TickDelayAndAdvanceLifecycle(arg0, arg0->unk_A6) != 0) {
                Particle_EnableRendering(arg0);
                Particle_FieldA6_SetS16_0BCA8(arg0, 2);
            }
            break;

        case 3:
            func_8213CCEC(arg0, 0, 3, 1, 1, 0);
            Particle_AddVelocityXZFromRotationYPlusHalfTurn(arg0);
            if ((Particle_FieldA6_DecrementToZeroStep1_0BDAC != 0) && (arg0->unk_B8 == 0)) {
                Particle_AdvancePhase(arg0);
            }
            break;

        case 4:
            Particle_MarkInactive(arg0);
            break;
    }

    if (arg0->unk_B8 == 1) {
        BattleAnim_EmitParticleBurstWithMetadata(arg0, BattleAnim_CallbackEndEffects39And41And45And46And83Descriptor3DMetadataBurstChild, &gBattleAnimParticleDescriptors[0x3D], 1, 8, 0);
        Particle_AdvancePhase(arg0);
    }
}

void BattleAnim_CallbackEndEffects37And38Descriptor34BurstEmitter_InitParticle(Particle* arg0) {
    s16 sp26 = Particle_FieldAC_GetS16_0C038(arg0);

    switch (Particle_FieldCF_GetS16_0C058(arg0)) {
        case 3:
            ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, 1);
            Particle_Field1C_SetScaled_0B938(arg0, 1.5f);
            Particle_Field74_SetScaled_0AD8C(arg0, 0.4f);
            Particle_FieldA6_SetS16_0BCA8(arg0, sp26 * 2);
            Particle_FieldCF_SetU8_0BEEC(arg0, 0);
            break;

        case 4:
            ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, 2);
            Particle_Field1C_SetScaled_0B938(arg0, 1.5f);
            Particle_Field74_SetScaled_0AD8C(arg0, 0.4f);
            Particle_FieldA6_SetS16_0BCA8(arg0, sp26 * 2);
            Particle_FieldCF_SetU8_0BEEC(arg0, 1);
            break;
    }

    Particle_SetPrimAlpha(arg0, 0xFF);
    Particle_DisableRendering(arg0);
    Particle_AdvanceLifecycle(arg0);
}

s32 BattleAnim_CallbackEndEffects37And38Descriptor34BurstEmitter(Particle* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            BattleAnim_CallbackEndEffects37And38Descriptor34BurstEmitter_InitParticle(arg0);
            break;

        case 2:
            if (Particle_TickDelayAndAdvanceLifecycle(arg0, arg0->unk_A6) != 0) {
                Particle_EnableRendering(arg0);
                Particle_FieldA6_SetS16_0BCA8(arg0, 2);
            }
            break;

        case 3:
            func_8213CCEC(arg0, 0, 3, 1, 1, 0);
            Particle_AddVelocityXZFromRotationYPlusHalfTurn(arg0);
            if ((Particle_FieldA6_DecrementToZeroStep1_0BDAC != NULL) && (arg0->unk_B8 == 0)) {
                Particle_AdvancePhase(arg0);
            }
            break;

        case 4:
            Particle_MarkInactive(arg0);
            break;
    }

    switch (arg0->unk_B8) {
        case 1:
            BattleAnim_EmitParticleBurst(arg0, BattleAnim_CallbackEndEffects37And38Descriptor38BurstChild, &gBattleAnimParticleDescriptors[0x38], 8);
            Particle_AdvancePhase(arg0);
            break;

        case 2:
            if (Particle_TickPhaseTimer(arg0, 1) != 0) {
                BattleAnim_EmitParticleBurst(arg0, BattleAnim_CallbackEndEffects37And38Descriptor38BurstChild, &gBattleAnimParticleDescriptors[0x38], 4);
                Particle_AdvancePhase(arg0);
            }
            break;

        case 3:
            if (Particle_TickPhaseTimer(arg0, 1) != 0) {
                BattleAnim_EmitParticleBurst(arg0, BattleAnim_CallbackEndEffects37And38Descriptor38BurstChild, &gBattleAnimParticleDescriptors[0x38], 4);
                Particle_AdvancePhase(arg0);
            }
            break;
    }
}

void BattleAnim_CallbackStartEffect56Descriptor40AnimScaleFade_InitParticle(Particle* arg0) {
    Particle_FieldAC_GetS16_0C038(arg0);
    Particle_Field1C_SetScaled_0B938(arg0, 0.05f);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, 7);
    Particle_SetPrimAlpha(arg0, 0xFF);
    Particle_FieldA6_SetS16_0BCA8(arg0, 0x32);
    Particle_AdvanceLifecycle(arg0);
}

void BattleAnim_CallbackStartEffect56Descriptor40AnimScaleFade(Particle* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            BattleAnim_CallbackStartEffect56Descriptor40AnimScaleFade_InitParticle(arg0);
            break;

        case 2:
            func_8213CC10(arg0, 0, 5, 1, 1, -1);
            Particle_Field1C_Approach_0B98C(arg0, 0.3f, 0.01f);
            Particle_FieldA6_DecrementToZeroStep1AndStepState_0BDD0(arg0);
            break;

        case 3:
            Particle_MarkInactive(arg0);
            break;
    }
}

void BattleAnim_CallbackStartEffect56Descriptor46AnimColorImpulseFade_InitParticle(Particle* arg0) {
    s16 sp2E;
    s16 sp2C;
    Vec3s sp24;

    sp2E = Particle_FieldAC_GetS16_0C038(arg0);
    sp2C = sp2E % 3;
    Particle_Field1C_SetScaled_0B938(arg0, 0.4f);
    Particle_Field74_SetScaled_0AD8C(arg0, 1.0f);

    sp24.x = MathUtil_Random16();
    sp24.y = MathUtil_Random16();
    sp24.z = 0;
    Particle_Field94_SetVecFromVec3s_0A24C(arg0, sp24);

    switch (sp2C) {
        case 0:
            Particle_SetPosition(arg0, 0.0f, -2.0f, 0.0f);
            break;

        case 1:
            Particle_SetPosition(arg0, 0.0f, 2.0f, 2.0f);
            break;

        case 2:
            Particle_SetPosition(arg0, 0.0f, 2.0f, -2.0f);
            break;
    }

    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, 0x17);
    Particle_FieldA6_SetS16_0BCA8(arg0, sp2E * 4);
    Particle_DisableRendering(arg0);
    Particle_AdvanceLifecycle(arg0);
}

void func_8216374C(s8 *arg0) {
    s16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_821635E4(arg0);
        return;
    case 2:
        if (func_8213CA80(arg0, M2C_FIELD(arg0, s16 *, 0xA2)) != 0) {
            func_8213CB3C(arg0);
            return;
        }
        return;
    case 3:
        func_8213CCEC(arg0, 0, 7, 1, 1, 0);
        func_8213F658(arg0, 0.2f, 0.25f);
        func_82140228(arg0, 0x3F000000, 0x3CA3D70A);
        func_821403E0(arg0, 0, 0x20);
        func_821404DC(arg0, 0, 0x20);
        if (M2C_FIELD(arg0, s8 *, 0xC3) >= 6) {
            func_821403B0(arg0, 0, 0x20);
            func_82140518(arg0, 0x64, 0x4E);
        }
        func_8213E4D8(arg0);
        return;
    case 4:
        func_8213C930(arg0);
        break;
    }
}

void BattleAnim_CallbackStartEffect73Descriptor15AnimatedColorImpulseFade_InitParticle(Particle* arg0) {
    s16 sp2E = Particle_FieldAC_GetS16_0C038(arg0);
    s16 sp2C = sp2E % 3;
    Vec3s sp24;

    Particle_Field1C_SetScaled_0B938(arg0, 0.4f);
    Particle_Field74_SetScaled_0AD8C(arg0, 1.0f);

    sp24.x = MathUtil_Random16();
    sp24.y = MathUtil_Random16();
    sp24.z = 0;
    Particle_Field94_SetVecFromVec3s_0A24C(arg0, sp24);

    switch (sp2C) {
        case 0:
            Particle_SetPosition(arg0, 0.0f, -2.0f, 0.0f);
            break;

        case 1:
            Particle_SetPosition(arg0, 0.0f, 2.0f, 2.0f);
            break;

        case 2:
            Particle_SetPosition(arg0, 0.0f, 2.0f, -2.0f);
            break;
    }

    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, 0x17);
    Particle_FieldA6_SetS16_0BCA8(arg0, sp2E * 4);
    Particle_DisableRendering(arg0);
    Particle_AdvanceLifecycle(arg0);
}

void func_821639EC(s8 *arg0) {
    s16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_82163884(arg0);
        return;
    case 2:
        if (func_8213CA80(arg0, M2C_FIELD(arg0, s16 *, 0xA2)) != 0) {
            func_8213CB3C(arg0);
            return;
        }
        return;
    case 3:
        func_8213CCEC(arg0, 0, 7, 1, 1, 0);
        func_8213F658(arg0, 0.2f, 0.25f);
        func_82140228(arg0, 0x3F000000, 0x3CA3D70A);
        func_821403E0(arg0, 0, 0x20);
        func_821404DC(arg0, 0, 0x20);
        if (M2C_FIELD(arg0, s8 *, 0xC3) >= 6) {
            func_821403B0(arg0, 0, 0x20);
            func_82140518(arg0, 0x64, 0x4E);
        }
        func_8213E4D8(arg0);
        return;
    case 4:
        func_8213C930(arg0);
        break;
    }
}

void BattleAnim_RecolorParticleByQueuedMoveId(Particle* arg0) {
    s16 sp1E;

    switch (BattleAnim_GetQueuedMoveId()) {
        case 0x4D:
            sp1E = 0x43;
            break;
        case 0x4E:
            sp1E = 5;
            break;
        case 0x4F:
            sp1E = 0xC;
            break;
        case 0x93:
            sp1E = 5;
            break;
        case 0x1C:
            sp1E = 0x31;
            break;
        case 0x6C:
            sp1E = 0x1C;
            break;
        case 0x7B:
            sp1E = 0x1E;
            break;
        case 0x36:
            sp1E = 0x1D;
            break;
        case 0x72:
            sp1E = 0x1E;
            break;
        case 0x8B:
            sp1E = 0x1E;
            break;
    }
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, sp1E);
}

void BattleAnim_CallbackStartEffects28And53And65And76Descriptor47AnimatedScaleMotion_InitParticle(Particle* arg0) {
    Vec3s sp28;
    s16 sp26 = Particle_FieldAC_GetS16_0C038(arg0);
    s16 sp24 = Particle_FieldCF_GetS16_0C058(arg0);

    Particle_Field1C_SetScaled_0B938(arg0, 1.0f);
    sp28.x = MathUtil_Random16();
    sp28.y = MathUtil_Random16();
    sp28.z = 0;
    Particle_Field94_SetVecFromVec3s_0A24C(arg0, sp28);

    switch (sp24) {
        case 0:
            Particle_SetRandomVelocityXYZ(arg0, 0xF, 0xF, 0xF);
            Particle_Field38_AddYScaled_08E90(arg0, 10.0f);
            Particle_Field74_SetScaled_0AD8C(arg0, 1.0f);
            Particle_FieldA6_SetS16_0BCA8(arg0, sp26 * 2);
            break;

        case 1:
            Particle_SetRandomVelocityXYZ(arg0, 0xA, 0xA, 0xA);
            Particle_Field38_AddYScaled_08E90(arg0, 10.0f);
            Particle_Field74_SetScaled_0AD8C(arg0, 0.0f);
            Particle_FieldA6_SetS16_0BCA8(arg0, sp26 * 2);
            break;
    }

    BattleAnim_RecolorParticleByQueuedMoveId(arg0);
    Particle_SetPrimAlpha(arg0, 0xC8);
    Particle_DisableRendering(arg0);
    Particle_AdvanceLifecycle(arg0);
}

void func_82163D7C(s8 *arg0) {
    s16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_82163C28(arg0);
        return;
    case 2:
        if (func_8213CA80(arg0, M2C_FIELD(arg0, s16 *, 0xA2)) != 0) {
            func_8213CB3C(arg0);
            return;
        }
        return;
    case 3:
        func_8213CCEC(arg0, 0, 7, 1, 2, 0);
        func_82140518(arg0, 0x64, 6);
        func_82140228(arg0, 0x40000000, 0x3D99999A);
        func_8213E528(arg0);
        return;
    case 4:
        func_8213C930(arg0);
        break;
    }
}

void func_82163E60(Particle* arg0) {
    Particle_Field1C_SetScaled_0B938(arg0, 0.2f);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, Particle_FieldCF_GetS16_0C058(arg0));
    Particle_SetPrimAlpha(arg0, 0xC8);
    Particle_FieldA6_SetS16_0BCA8(arg0, 0x18);
    arg0->unk_74 = D_FLT_82197730;
    Particle_AdvanceLifecycle(arg0);
}

void func_82163ED0(s8 *arg0) {
    s16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_82163E60(arg0);
        return;
    case 2:
        func_82140228(arg0, 0x40000000, 0x3CA3D70A);
        func_821404DC(arg0, 0xC8, 2);
        func_821406B4(arg0);
        return;
    case 3:
        func_82137AB4(arg0 + 0x70, 0x3C03126F, 0x3A83126F);
        func_82140228(arg0, 0x40000000, M2C_FIELD(arg0, s32 *, 0x70));
        func_821404DC(arg0, 0xC8, 2);
        func_82140548(arg0, 0, 0xC);
        return;
    case 4:
        func_8213C930(arg0);
        return;
    }
}

void BattleAnim_CallbackStartEffect81Descriptor3DRisingAnimFade_InitParticle(Particle* arg0) {
    s16 sp26 = Particle_FieldAC_GetS16_0C038(arg0);

    Particle_Field1C_SetScaled_0B938(arg0, 1.0f);
    Particle_SetRandomVelocityXYZ(arg0, 0xF, 0xF, 0xF);
    Particle_Field74_SetScaled_0AD8C(arg0, (ParticleMath_RandomRange(0x32) * D_FLT_82197734) + 0.5f);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, Particle_FieldCF_GetS16_0C058(arg0));
    Particle_SetPrimAlpha(arg0, 0x64);
    Particle_FieldA6_SetS16_0BCA8(arg0, sp26 * 4);
    Particle_DisableRendering(arg0);
    Particle_AdvanceLifecycle(arg0);
}
