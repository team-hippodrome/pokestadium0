/* Fixed-layout split; original translation-unit boundaries remain unconfirmed. */
#include "battle_engine_343BA0_8.h"

void BattleAnim_StartEffect98Radial20_Init(void) {
    D_8219CB16 = 0;
    BattleAnim_ResetSharedEffectMatrix();
    Radial20_ResetPool();
    BattleAnim_StartEffect98Radial20_EmitVariantD();
}

s32 BattleAnim_StartEffect98Radial20_Update(void) {
    D_8219CB16++;
    if (D_8219CB16 >= 0xB5) {
        return -1;
    }

    if ((D_8219CB16 < 0x78) && ((D_8219CB16 % 7) == 0)) {
        BattleAnim_StartEffect98Radial20_EmitVariantD();
    }

    return Radial20_IsComplete();
}

void BattleAnim_StartEffect98Radial20_Draw(void) {
    gSPMatrix(gDisplayListHead++, &D_8219CAC8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gDisplayListHead = Radial20_Draw(gDisplayListHead);
}

void BattleAnim_StartEffect11Trail50Alt_Init(void) {
    D_8219CB18 = 0;
    BattleAnim_ResetSharedEffectMatrix();
    Trail50EffectAlt_Init();
}

s32 BattleAnim_StartEffect11Trail50Alt_Update(void) {
    UNUSED s32 pad[1]; // FAKE: stack padding
    Vec3f sp60;
    f32 sp5C;
    f32 sp58;
    f32 sp54;
    UNUSED s32 pad2[2]; // FAKE: stack padding
    f32 var_fv0;
    f32 sp44;

    D_8219CB18++;
    if (!(D_8219CB18 & 1)) {
        sp44 = BattleAnim_EffectSecondaryOwnerModelScale();
        BattleAnim_EffectSecondaryOwnerAnchorPosition(&sp60);
        sp5C = (((guRandom() % 50) - 0x19) * sp44) + sp60.x;
        sp58 = (((guRandom() % 60) - 0x1E) * sp44) + sp60.y;
        sp54 = (((guRandom() % 50) - 0x19) * sp44) + sp60.z;
        var_fv0 = 10.0f;
        if (sp5C > 0.0) {
            var_fv0 = -var_fv0;
        }
        Trail50EffectAlt_Start(sp5C, sp58, sp54, var_fv0, 0.0f, 0.0f, 0xFF, 0xFF, 0xFF, 0x64, 0.3f, 1.0f, 4.0f, 0x1E);
    }
    Trail50EffectAlt_IsComplete();
    return 0;
}

void BattleAnim_StartEffect11Trail50Alt_Draw(void) {
    gSPMatrix(gDisplayListHead++, &D_8219CAC8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gDisplayListHead = Trail50EffectAlt_Draw(gDisplayListHead);
}

void BattleAnim_StartEffect57Trail50_Init(void) {
    D_8219CB1A = 0;
    BattleAnim_ResetSharedEffectMatrix();
    Trail50Effect_Init();
}

s32 BattleAnim_StartEffect57Trail50_Update(void) {
    UNUSED s32 pad[1]; // FAKE: stack padding
    Vec3f sp60;
    f32 sp5C;
    f32 sp58;
    f32 sp54;
    UNUSED s32 pad2[2]; // FAKE: stack padding
    f32 var_fv0;
    f32 sp44;

    D_8219CB1A++;
    if (!(D_8219CB1A & 1)) {
        sp44 = BattleAnim_EffectSecondaryOwnerModelScale();
        BattleAnim_EffectSecondaryOwnerAnchorPosition(&sp60);
        sp5C = (((guRandom() % 50) - 0x19) * sp44) + sp60.x;
        sp58 = (((guRandom() % 60) - 0x1E) * sp44) + sp60.y;
        sp54 = (((guRandom() % 50) - 0x19) * sp44) + sp60.z;
        var_fv0 = 10.0f;
        if (sp5C > 0.0) {
            var_fv0 = -var_fv0;
        }
        Trail50Effect_Start(sp5C, sp58, sp54, var_fv0, 0.0f, 0.0f, 0xFF, 0xFF, 0xFF, 0x64, 0.3f, 1.0f, 4.0f, 0x1E);
    }
    Trail50Effect_IsComplete();
    return 0;
}

void BattleAnim_StartEffect57Trail50_Draw(void) {
    gSPMatrix(gDisplayListHead++, &D_8219CAC8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gDisplayListHead = Trail50Effect_Draw(gDisplayListHead);
}

void BattleAnim_StartEffect42Trail40_Init(void) {
    Vec3f sp1C;

    BattleAnim_ResetSharedEffectMatrix();
    BattleAnim_EffectSecondaryOwnerAnchorPosition(&sp1C);
    Trail40_Init(0x708);
}

s32 BattleAnim_StartEffect42Trail40_Update(void) {
    return Trail40_IsComplete();
}

void BattleAnim_StartEffect42Trail40_Draw(void) {
    gSPMatrix(gDisplayListHead++, &D_8219CAC8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gDisplayListHead = Trail40_Draw(gDisplayListHead);
}

void BattleAnim_StartEffect43Trail40Variant_Init(void) {
    Vec3f sp1C;

    BattleAnim_ResetSharedEffectMatrix();
    BattleAnim_EffectSecondaryOwnerAnchorPosition(&sp1C);
    Trail40Variant_InitPool(0x708);
}

s32 BattleAnim_StartEffect43Trail40Variant_Update(void) {
    return Trail40Variant_AdvanceTimer();
}

void BattleAnim_StartEffect43Trail40Variant_Draw(void) {
    gSPMatrix(gDisplayListHead++, &D_8219CAC8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gDisplayListHead = Trail40Variant_BuildGfx(gDisplayListHead);
}

void BattleAnim_StartEffect44Trail40GridAlt_Init(void) {
    Vec3f sp1C;

    BattleAnim_ResetSharedEffectMatrix();
    BattleAnim_EffectSecondaryOwnerAnchorPosition(&sp1C);
    Trail40GridAlt_Init(0x708);
}

s32 BattleAnim_StartEffect44Trail40GridAlt_Update(void) {
    return Trail40GridAlt_IsComplete();
}

void BattleAnim_StartEffect44Trail40GridAlt_Draw(void) {
    gSPMatrix(gDisplayListHead++, &D_8219CAC8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gDisplayListHead = Trail40GridAlt_Draw(gDisplayListHead);
}

void BattleAnim_StartEffect45FourStreamTrail_Init(void) {
    D_8219CAC0 = 0;
    BattleAnim_ResetSharedEffectMatrix();
    FourStreamTrail_Init();
}

s32 func_8216F3A0(void) {
    s32 var_v1;
    Vec3f sp68;
    f32 sp64;
    f32 sp60;
    f32 sp5C;
    f32 sp58;
    f32 sp54;
    f32 sp50;
    f32 sp4C;

    D_8219CAC0++;
    if (D_8219CAC0 >= 0x32) {
        return -1;
    }

    if (D_8219CAC0 < 4) {
        BattleAnim_EffectSecondaryOwnerBonePosition(&sp68);
        sp64 = sp68.x;
        sp60 = sp68.y;
        sp5C = sp68.z;
        sp58 = 1.0f;
        sp4C = (((D_8219CAC0 % 3) * D_FLT_82197934) / 3.0) + D_DBL_82197938;
        sp54 = (f64)__sinf(sp4C);
        sp50 = (f64)__cosf(sp4C);
        Vec3f_NormalizeComponents(&sp58, &sp54, &sp50);
        sp54 *= 20.0;
        sp50 *= 20.0;
        sp58 = 10.0f;
        if (sp64 < 0.0) {
            sp58 = -sp58;
        }
        FourStreamTrail_Start(sp64, sp60, sp5C, sp58, sp54, sp50, 0xC0, 0xFF, 0xFF, 0x80, (((guRandom() % 2) * 2) - 1) * D_DBL_82197940,
                              2.0f, 13.0f, 0x28);
    }

    if (D_8219CAC0 >= 2) {
        var_v1 = FourStreamTrail_IsComplete();
    } else {
        var_v1 = 0;
    }
    return var_v1;
}

void BattleAnim_StartEffect45FourStreamTrail_Draw(void) {
    if (D_8219CAC0 >= 2) {
        gSPMatrix(gDisplayListHead++, &D_8219CAC8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

        gDisplayListHead = FourStreamTrail_Draw(gDisplayListHead);
    }
}

void BattleAnim_StartEffect62OwnerLinkedFourStream_Init(void) {
    D_8219CAC2 = 0;
    BattleAnim_ResetSharedEffectMatrix();
    OwnerLinkedFourStream_Init();
}

s32 BattleAnim_StartEffect62OwnerLinkedFourStream_Update(void) {
    s32 var_v1;
    f32 sp60;
    f32 sp5C;
    f32 sp58;
    f32 sp54;
    f32 sp50;
    f32 sp4C;
    f32 sp48;

    D_8219CAC2++;
    if (((D_8219CAC2 >> 2) < 4) && !(D_8219CAC2 & 3)) {
        BattleAnim_CalcVectorAtToDm(&sp60, &sp5C, &sp58, &sp54, &sp50, &sp4C);
        sp48 = ((2 - (((D_8219CAC2 >> 2) + 2) % 3)) * D_FLT_82197948) + D_FLT_8219794C;
        sp54 *= 7.0f * __cosf(sp48);
        sp50 = __sinf(sp48) * 10.0f;
        sp4C = 0.0f;
        OwnerLinkedFourStream_Start(sp60, sp5C, sp58, sp54, sp50, 0.0f, 0xD0, 0xFF, 0xFF, 0x80, D_FLT_82197950, 2.0f, 4.0f, 0x28);
    }

    if (D_8219CAC2 >= 2) {
        var_v1 = OwnerLinkedFourStream_IsComplete();
    } else {
        var_v1 = 0;
    }
    return var_v1;
}

void BattleAnim_StartEffect62OwnerLinkedFourStream_Draw(void) {
    if (D_8219CAC2 >= 2) {
        gSPMatrix(gDisplayListHead++, &D_8219CAC8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

        gDisplayListHead = OwnerLinkedFourStream_Draw(gDisplayListHead);
    }
}

void BattleAnim_StartEffect67OwnerAnchoredFourStream_Init(void) {
    Vec3f sp5C;
    f32 sp58;
    f32 sp54;
    f32 sp50;
    f32 sp4C;
    f32 sp48;
    f32 sp44;

    D_8219CB08 = 0;
    BattleAnim_ResetSharedEffectMatrix();
    OwnerAnchoredFourStream_Init();
    BattleAnim_CalcVectorAtToDm(&sp58, &sp54, &sp50, &sp4C, &sp48, &sp44);
    sp4C *= 5.0;
    sp48 *= 5.0;
    sp44 *= 5.0;
    OwnerAnchoredFourStream_Start(sp58, sp54, sp50, sp4C, sp48, sp44, 0xC0, 0xFF, 0xFF, 0xA0, D_FLT_82197954, 2.0f, 4.0f, 0x28);
    sp5C.x = sp58;
    sp5C.y = sp54;
    sp5C.z = sp50;
    BattleAnim_SpawnSecondaryOwnerParticle(sp5C, 1);
}

s32 BattleAnim_StartEffect67OwnerAnchoredFourStream_Update(void) {
    D_8219CB08++;
    if (D_8219CB08 >= 0x32) {
        return -1;
    }

    return OwnerAnchoredFourStream_IsComplete();
}

void BattleAnim_StartEffect67OwnerAnchoredFourStream_Draw(void) {
    gSPMatrix(gDisplayListHead++, &D_8219CAC8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gDisplayListHead = OwnerAnchoredFourStream_Draw(gDisplayListHead);
}

void BattleAnim_StartEffect78Radial20_EmitVariantA(void) {
    f32 sp5C;
    f32 sp58;
    f32 sp54;
    f32 sp50;
    f32 sp4C;
    f32 sp48;

    BattleAnim_CalcVectorAtToDm(&sp5C, &sp58, &sp54, &sp50, &sp4C, &sp48);
    sp50 *= 6.0f;
    sp4C *= 6.0f;
    sp48 *= 6.0f;
    Radial20_VariantA(sp5C, sp58, sp54, sp50, sp4C, sp48, 9, 0xFF, 0xFF, 0xFF, 0xB4, D_FLT_82197958, 2.0f, 20.0f, 0x3C);
}

void BattleAnim_StartEffect78Radial20_Init(void) {
    D_8219CB0A = 0;
    BattleAnim_ResetSharedEffectMatrix();
    Radial20_ResetPool();
    BattleAnim_StartEffect78Radial20_EmitVariantA();
}

s32 BattleAnim_StartEffect78Radial20_Update(void) {
    D_8219CB0A++;
    if (D_8219CB0A >= 0xB5) {
        return -1;
    }
    return Radial20_IsComplete();
}

void BattleAnim_StartEffect78Radial20_Draw(void) {
    gSPMatrix(gDisplayListHead++, &D_8219CAC8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gDisplayListHead = Radial20_Draw(gDisplayListHead);
}

void BattleAnim_StartEffect26DoubleTextureTrail_Seed(void) {
    static unk_D_843C2C00_024 D_84387FC0 = { 2, 1, 0xE, 1, 2, 2, 3, 1 };
    static unk_D_843C2C00_024 D_84387FE0 = { 3, 5, 0, 5, 3, 7, 0, 5 };
    static unk_D_843C2C00_024 D_84388000 = { 2, 1, 0xE, 1, 2, 1, 3, 1 };
    static unk_D_843C2C00_024 D_84388020 = { 3, 5, 0, 5, 0, 7, 5, 7 };

    f32 spB4;
    f32 spB0;
    f32 spAC;
    f32 spA8;
    f32 spA4;
    f32 spA0;

    BattleAnim_CalcVectorAtToDm(&spB4, &spB0, &spAC, &spA8, &spA4, &spA0);
    spA8 *= 10.0f;
    spA4 *= 10.0f;
    spA0 *= 10.0f;
    DoubleTextureTrail_Spawn(spB4, spB0, spAC, spA8, spA4, spA0, 0.0f, 5.0f, D_FLT_8219795C, 2.0f, 10.0f, 0x14, 0x8F, 0x8F, 6, 0xA, 0xF, 0xE,
                  -3, 5, 0, 0xF, &D_84387FC0, &D_84387FE0, 0xFF, 0xFF, 0, 0x96, 0x64, 0xFF, 0, 0xC8, 0x32, 0xFF, 0x96,
                  0xFF, 0x78);
    DoubleTextureTrail_Spawn(spB4, spB0, spAC, spA8, spA4, spA0, 0.0f, 5.0f, D_FLT_82197960, 3.0f, 15.0f, 0x14, 0x8F, 0x90, 2, 6, 0, 0xF, -4,
                  2, 0, 0, &D_84388000, &D_84388020, 0, 0xFF, 0x64, 0x96, 0x64, 0x64, 0, 0xFF, 0xC8, 0, 0, 0, 0);
}

void BattleAnim_StartEffect26DoubleTextureTrail_Init(void) {
    BattleAnim_ResetSharedEffectMatrix();
    DoubleTextureTrail_InitPool();
    BattleAnim_StartEffect26DoubleTextureTrail_Seed();
}

s32 BattleAnim_StartEffect26DoubleTextureTrail_Update(void) {
    return DoubleTextureTrail_UpdateAll();
}

void BattleAnim_StartEffect26DoubleTextureTrail_Draw(void) {
    gSPMatrix(gDisplayListHead++, &D_8219CAC8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gDisplayListHead = DoubleTextureTrail_DrawAll(gDisplayListHead);
}

void BattleAnim_StartEffect47SixSlotTrail_Seed(void) {
    static unk_D_843C2C00_024 D_84388040 = { 3, 5, 1, 5, 1, 7, 3, 7 };
    static unk_D_843C2C00_024 D_84388060 = { 0x1F, 0x1F, 0x1F, 0, 7, 7, 7, 0 };

    f32 spA4;
    f32 spA0;
    f32 sp9C;
    f32 sp98;
    f32 sp94;
    f32 sp90;

    BattleAnim_CalcVectorAtToDm(&spA4, &spA0, &sp9C, &sp98, &sp94, &sp90);
    sp94 += D_FLT_82197968 * __cosf((RAND(10) * D_FLT_82197964) / 10.0f);
    sp90 += D_FLT_82197970 * __cosf((RAND(10) * D_FLT_8219796C) / 10.0f);

    sp98 *= 12.0f;
    sp94 *= 12.0f;
    sp90 *= 12.0f;

    BattleAnim_SixSlotTrail_Spawn(0, spA4, spA0, sp9C, sp98, sp94, sp90, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0, 0x64, 0xFF, 0xFF, D_FLT_82197974, 2.0f,
                  20.0f, 0x3C, 0x95, 0x95, 0, 0xA, 0, 0xD, 0, 0, 0, 0, &D_84388040, &D_84388060);
}

void BattleAnim_StartEffect47SixSlotTrail_Init(void) {
    D_8219CB0C = 0;
    BattleAnim_ResetSharedEffectMatrix();
    BattleAnim_SixSlotTrail_ResetPool();
    BattleAnim_StartEffect47SixSlotTrail_Seed();
}

s32 BattleAnim_StartEffect47SixSlotTrail_Update(void) {
    D_8219CB0C++;
    if ((D_8219CB0C % 10) == 0) {
        BattleAnim_StartEffect47SixSlotTrail_Seed();
    }
    return BattleAnim_SixSlotTrail_UpdateAll();
}

void BattleAnim_StartEffect47SixSlotTrail_Draw(void) {
    gSPMatrix(gDisplayListHead++, &D_8219CAC8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gDisplayListHead = BattleAnim_SixSlotTrail_DrawAll(gDisplayListHead);
}

void BattleAnim_StartEffect4DoubleTextureTrail_Seed(void) {
    static unk_D_843C2C00_024 D_84388080 = { 3, 5, 1, 5, 6, 7, 2, 3 };
    static unk_D_843C2C00_024 D_843880A0 = { 0x1F, 0x1F, 0x1F, 0, 0, 7, 5, 7 };
    static unk_D_843C2C00_024 D_843880C0 = { 3, 5, 2, 5, 1, 7, 3, 7 };
    static unk_D_843C2C00_024 D_843880E0 = { 0x1F, 0x1F, 0x1F, 0, 0, 7, 5, 7 };

    f32 spB4;
    f32 spB0;
    f32 spAC;
    f32 spA8;
    f32 spA4;
    f32 spA0;

    BattleAnim_CalcVectorAtToDm(&spB4, &spB0, &spAC, &spA8, &spA4, &spA0);
    spA8 *= 10.0f;
    spA4 *= 10.0f;
    spA0 *= 10.0f;
    DoubleTextureTrail_Spawn(spB4, spB0, spAC, spA8, spA4, spA0, 0.0f, 5.0f, D_FLT_82197978, 2.0f, 10.0f, 0x14, 0x93, 0x93, 5, 0xA, 0xF, 0xF,
                  -5, 5, 0xF, 0xF, &D_84388080, &D_843880A0, 0xC8, 0xC8, 0, 0x64, 0, 0, 0xC8, 0, 0xFF, 0, 0xFF, 0,
                  0x5A);
    DoubleTextureTrail_Spawn(spB4, spB0, spAC, spA8, spA4, spA0, 0.0f, 5.0f, D_FLT_8219797C, 3.0f, 15.0f, 0x14, 0x91, 0x91, -2, 0xA, 0xF,
                  0xF, 5, 0xF, 0xF, 0xF, &D_843880C0, &D_843880E0, 0xFF, 0x32, 0x64, 0xC8, 0, 0x64, 0x32, 0xFF, 0xFF, 0,
                  0, 0, 0);
}

void BattleAnim_StartEffect4DoubleTextureTrail_Init(void) {
    BattleAnim_ResetSharedEffectMatrix();
    DoubleTextureTrail_InitPool();
    BattleAnim_StartEffect4DoubleTextureTrail_Seed();
}

s32 BattleAnim_StartEffect4DoubleTextureTrail_Update(void) {
    return DoubleTextureTrail_UpdateAll();
}

void BattleAnim_StartEffect4DoubleTextureTrail_Draw(void) {
    gSPMatrix(gDisplayListHead++, &D_8219CAC8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gDisplayListHead = DoubleTextureTrail_DrawAll(gDisplayListHead);
}

void BattleAnim_StartEffect77DoubleTextureTrail_Seed(void) {
    static unk_D_843C2C00_024 D_84388100 = { 2, 1, 0xE, 1, 2, 7, 1, 3 };
    static unk_D_843C2C00_024 D_84388120 = { 3, 5, 0, 5, 0, 7, 5, 7 };
    static unk_D_843C2C00_024 D_84388140 = { 2, 1, 0xE, 1, 2, 7, 1, 3 };
    static unk_D_843C2C00_024 D_84388160 = { 3, 5, 0, 5, 0, 7, 5, 7 };

    f32 spB4;
    f32 spB0;
    f32 spAC;
    f32 spA8;
    f32 spA4;
    f32 spA0;

    BattleAnim_CalcVectorAtToDm(&spB4, &spB0, &spAC, &spA8, &spA4, &spA0);
    spA8 *= 10.0f;
    spA4 *= 10.0f;
    spA0 *= 10.0f;
    DoubleTextureTrail_Spawn(spB4, spB0, spAC, spA8, spA4, spA0, 0.0f, 5.0f, D_FLT_82197980, 2.0f, 10.0f, 0x14, 0x97, 0x98, -5, 0x14, 0xF,
                  0xD, -5, 0x14, 0, 0xE, &D_84388100, &D_84388120, 0xFF, 0xFF, 0xFF, 0x32, 0x64, 0x64, 0, 0xFF, 0xFF,
                  0xC8, 0xFF, 0xFF, 0x96);
    DoubleTextureTrail_Spawn(spB4, spB0, spAC, spA8, spA4, spA0, 0.0f, 5.0f, D_FLT_82197984, 3.0f, 15.0f, 0x14, 0x97, 0x98, 5, 0xF, 0xF, 0xE,
                  0, 0xF, 0xF, 0xF, &D_84388140, &D_84388160, 0xFF, 0xFF, 0xFF, 0x32, 0x64, 0x64, 0x64, 0xFF, 0xFF, 0,
                  0, 0, 0);
}

void BattleAnim_StartEffect77DoubleTextureTrail_Init(void) {
    BattleAnim_ResetSharedEffectMatrix();
    DoubleTextureTrail_InitPool();
    BattleAnim_StartEffect77DoubleTextureTrail_Seed();
}

s32 BattleAnim_StartEffect77DoubleTextureTrail_Update(void) {
    return DoubleTextureTrail_UpdateAll();
}

void BattleAnim_StartEffect77DoubleTextureTrail_Draw(void) {
    gSPMatrix(gDisplayListHead++, &D_8219CAC8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gDisplayListHead = DoubleTextureTrail_DrawAll(gDisplayListHead);
}

void BattleAnim_StartEffect70DoubleTextureTrail_Seed(void) {
    static unk_D_843C2C00_024 D_84388180 = { 2, 1, 0xE, 1, 2, 1, 3, 1 };
    static unk_D_843C2C00_024 D_843881A0 = { 3, 5, 0, 5, 0, 7, 5, 7 };

    f32 spB4;
    f32 spB0;
    f32 spAC;
    f32 spA8;
    f32 spA4;
    f32 spA0;

    BattleAnim_CalcVectorAtToDm(&spB4, &spB0, &spAC, &spA8, &spA4, &spA0);
    spA8 *= 10.0f;
    spA4 *= 10.0f;
    spA0 *= 10.0f;
    DoubleTextureTrail_Spawn(spB4, spB0, spAC, spA8, spA4, spA0, 0.0f, 5.0f, D_FLT_82197988, 3.0f, 15.0f, 0x14, 0x97, 0x94, 0, 0x14, 0xE,
                  0xF, 0, 0x14, 0xF, 0xE, &D_84388180, &D_843881A0, 0xFF, 0xFF, 0xFF, 0x96, 0x96, 0xFF, 0xFF, 0, 0xFF,
                  0xFF, 0xFF, 0, 0x96);
}

void BattleAnim_StartEffect70DoubleTextureTrail_Init(void) {
    BattleAnim_ResetSharedEffectMatrix();
    DoubleTextureTrail_InitPool();
    BattleAnim_StartEffect70DoubleTextureTrail_Seed();
}

s32 BattleAnim_StartEffect70DoubleTextureTrail_Update(void) {
    return DoubleTextureTrail_UpdateAll();
}

void BattleAnim_StartEffect70DoubleTextureTrail_Draw(void) {
    gSPMatrix(gDisplayListHead++, &D_8219CAC8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gDisplayListHead = DoubleTextureTrail_DrawAll(gDisplayListHead);
}

void BattleAnim_StartEffect39DoubleTextureTrail_Seed(void) {
    static unk_D_843C2C00_024 D_843881C0 = {
        0x00000002, 0x00000001, 0x0000000E, 0x00000001, 0x00000007, 0x00000007, 0x00000007, 0x00000003,
    };
    static unk_D_843C2C00_024 D_843881E0 = {
        0x00000003, 0x00000005, 0x00000000, 0x00000005, 0x00000007, 0x00000007, 0x00000007, 0x00000000,
    };
    static unk_D_843C2C00_024 D_84388200 = {
        0x00000002, 0x00000001, 0x0000000E, 0x00000001, 0x00000002, 0x00000001, 0x00000003, 0x00000001,
    };
    static unk_D_843C2C00_024 D_84388220 = {
        0x00000003, 0x00000005, 0x00000000, 0x00000005, 0x00000000, 0x00000007, 0x00000005, 0x00000007,
    };

    f32 spB4;
    f32 spB0;
    f32 spAC;
    f32 spA8;
    f32 spA4;
    f32 spA0;

    BattleAnim_CalcVectorAtToDm(&spB4, &spB0, &spAC, &spA8, &spA4, &spA0);
    spA8 *= 12.0f;
    spA4 *= 12.0f;
    spA0 *= 12.0f;
    DoubleTextureTrail_Spawn(spB4, spB0, spAC, spA8, spA4, spA0, 0.0f, 5.0f, D_FLT_8219798C, 2.0f, 10.0f, 0x14, 0x91, 0x92, 5, 0x1E, 0, 0xD,
                  -5, 0x1E, 0xF, 0xD, &D_843881C0, &D_843881E0, 0xFF, 0xFF, 0, 0xFF, 0x96, 0x32, 0, 0, 0xFF, 0xFF, 0xC8,
                  0x64, 0xC8);
    DoubleTextureTrail_Spawn(spB4, spB0, spAC, spA8, spA4, spA0, 0.0f, 5.0f, D_FLT_82197990, 3.0f, 15.0f, 0x14, 0x97, 0x96, 6, 0x14, 0xE,
                  0xF, -3, 0xA, 0, 0xF, &D_84388200, &D_84388220, 0xFF, 0xFF, 0x64, 0x96, 0xFF, 0xFF, 0x64, 0, 0xC8, 0,
                  0, 0, 0);
}
