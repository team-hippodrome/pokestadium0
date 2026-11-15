/* Fixed-layout split; original translation-unit boundaries remain unconfirmed. */
#include "battle.h"
#include "vector_math.h"

/**
 * Init hook for Disable's use animation: clears the frame counter, resets the shared matrix and
 * the 20-slot radial pool, and emits the first radial burst (variant D).
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Disable.
 */
void BattleAnim_SetupDisableUseRadial(void) {
    D_8219CB16 = 0;
    BattleAnim_ResetSharedEffectMatrix();
    Radial20_ResetPool();
    BattleAnim_StartEffect98Radial20_EmitVariantD();
}

/**
 * Update hook for Disable's use animation: emits another radial burst every 7 frames for the first
 * 120 frames and returns -1 (done) at frame 181; otherwise returns whether the radial pool has
 * finished.
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Disable.
 */
s32 BattleAnim_RunDisableUseRadial(void) {
    D_8219CB16++;
    if (D_8219CB16 >= 181) {
        return -1;
    }

    if ((D_8219CB16 < 120) && ((D_8219CB16 % 7) == 0)) {
        BattleAnim_StartEffect98Radial20_EmitVariantD();
    }

    return Radial20_IsComplete();
}

/**
 * Draw hook for Disable's use animation: loads the shared effect matrix and draws the radial pool.
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Disable.
 */
void BattleAnim_DrawDisableUseRadial(void) {
    gSPMatrix(gDisplayListHead++, &D_8219CAC8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gDisplayListHead = Radial20_Draw(gDisplayListHead);
}

/**
 * Init hook for Razor Leaf's use animation: clears the frame counter, resets the shared matrix and
 * initializes the leaf trail pool.
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Razor Leaf.
 */
void BattleAnim_SetupRazorLeafUseTrail(void) {
    D_8219CB18 = 0;
    BattleAnim_ResetSharedEffectMatrix();
    RazorLeafTrail_Init();
}

/**
 * Update hook for Razor Leaf's use animation: every second frame starts a white leaf trail at a
 * random point around the secondary owner (scaled by its model size), moving sideways toward the
 * center, then advances the trails. Always returns 0.
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Razor Leaf.
 */
s32 BattleAnim_RunRazorLeafUseTrail(void) {
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
        RazorLeafTrail_Start(sp5C, sp58, sp54, var_fv0, 0.0f, 0.0f, 0xFF, 0xFF, 0xFF, 0x64, 0.3f, 1.0f, 4.0f, 0x1E); // #FFFFFF
    }
    RazorLeafTrail_IsComplete();
    return 0;
}

/**
 * Draw hook for Razor Leaf's use animation: loads the shared effect matrix and draws the leaf
 * trails.
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Razor Leaf.
 */
void BattleAnim_DrawRazorLeafUseTrail(void) {
    gSPMatrix(gDisplayListHead++, &D_8219CAC8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gDisplayListHead = RazorLeafTrail_Draw(gDisplayListHead);
}

/**
 * Init hook for Petal Dance's use animation: clears the frame counter, resets the shared matrix
 * and initializes the petal trail pool.
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Petal Dance.
 */
void BattleAnim_SetupPetalDanceUseTrail(void) {
    D_8219CB1A = 0;
    BattleAnim_ResetSharedEffectMatrix();
    PetalDanceTrail_Init();
}

/**
 * Update hook for Petal Dance's use animation: every second frame starts a white petal trail at a
 * random point around the secondary owner (scaled by its model size), moving sideways toward the
 * center, then advances the trails. Always returns 0.
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Petal Dance.
 */
s32 BattleAnim_RunPetalDanceUseTrail(void) {
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
        PetalDanceTrail_Start(sp5C, sp58, sp54, var_fv0, 0.0f, 0.0f, 0xFF, 0xFF, 0xFF, 0x64, 0.3f, 1.0f, 4.0f, 0x1E); // #FFFFFF
    }
    PetalDanceTrail_IsComplete();
    return 0;
}

/**
 * Draw hook for Petal Dance's use animation: loads the shared effect matrix and draws the petal
 * trails.
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Petal Dance.
 */
void BattleAnim_DrawPetalDanceUseTrail(void) {
    gSPMatrix(gDisplayListHead++, &D_8219CAC8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gDisplayListHead = PetalDanceTrail_Draw(gDisplayListHead);
}

/**
 * Init hook for the Hypnosis and Screech use animation: resets the shared matrix and starts the
 * wave grid with a duration of 1800 frames. The secondary owner's anchor is read but not used.
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Hypnosis, Screech.
 */
void BattleAnim_SetupHypnosisScreechUseTrail(void) {
    Vec3f sp1C;

    BattleAnim_ResetSharedEffectMatrix();
    BattleAnim_EffectSecondaryOwnerAnchorPosition(&sp1C);
    HypnosisScreechTrail_Init(1800);
}

/**
 * Update hook for the Hypnosis and Screech use animation: returns whether the wave grid has
 * finished.
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Hypnosis, Screech.
 */
s32 BattleAnim_RunHypnosisScreechUseTrail(void) {
    return HypnosisScreechTrail_IsComplete();
}

/**
 * Draw hook for the Hypnosis and Screech use animation: loads the shared effect matrix and draws
 * the wave grid.
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Hypnosis, Screech.
 */
void BattleAnim_DrawHypnosisScreechUseTrail(void) {
    gSPMatrix(gDisplayListHead++, &D_8219CAC8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gDisplayListHead = HypnosisScreechTrail_Draw(gDisplayListHead);
}

/**
 * Init hook for Sing's use animation: resets the shared matrix and starts the wave grid with a
 * duration of 1800 frames. The secondary owner's anchor is read but not used.
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Sing.
 */
void BattleAnim_SetupSingUseTrail(void) {
    Vec3f sp1C;

    BattleAnim_ResetSharedEffectMatrix();
    BattleAnim_EffectSecondaryOwnerAnchorPosition(&sp1C);
    SingTrail_InitPool(1800);
}

/**
 * Update hook for Sing's use animation: advances the wave grid and returns whether it has
 * finished.
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Sing.
 */
s32 BattleAnim_RunSingUseTrail(void) {
    return SingTrail_AdvanceTimer();
}

/**
 * Draw hook for Sing's use animation: loads the shared effect matrix and draws the wave grid.
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Sing.
 */
void BattleAnim_DrawSingUseTrail(void) {
    gSPMatrix(gDisplayListHead++, &D_8219CAC8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gDisplayListHead = SingTrail_BuildGfx(gDisplayListHead);
}

/**
 * Init hook for the Kinesis and Supersonic use animation: resets the shared matrix and starts the
 * 40-cell grid trail with a duration of 1800 frames. The secondary owner's anchor is read but not
 * used.
 * Moves: Kinesis (use), Supersonic (use)
 * TODO: Human contributor add screenshot
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Supersonic, Kinesis.
 */
void BattleAnim_SetupKinesisSupersonicUseTrail(void) {
    Vec3f sp1C;

    BattleAnim_ResetSharedEffectMatrix();
    BattleAnim_EffectSecondaryOwnerAnchorPosition(&sp1C);
    Trail40GridAlt_Init(1800);
}

/**
 * Update hook for the Kinesis and Supersonic use animation: returns whether the grid trail has
 * finished.
 * Moves: Kinesis (use), Supersonic (use)
 * TODO: Human contributor add screenshot
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Supersonic, Kinesis.
 */
s32 BattleAnim_RunKinesisSupersonicUseTrail(void) {
    return Trail40GridAlt_IsComplete();
}

/**
 * Draw hook for the Kinesis and Supersonic use animation: loads the shared effect matrix and draws
 * the grid trail.
 * Moves: Kinesis (use), Supersonic (use)
 * TODO: Human contributor add screenshot
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Supersonic, Kinesis.
 */
void BattleAnim_DrawKinesisSupersonicUseTrail(void) {
    gSPMatrix(gDisplayListHead++, &D_8219CAC8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gDisplayListHead = Trail40GridAlt_Draw(gDisplayListHead);
}

/**
 * Init hook for Sonic Boom's use animation: clears the frame counter, resets the shared matrix and
 * initializes the four-stream trail pool.
 * Moves: Sonic Boom (use)
 * TODO: Human contributor add screenshot
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Sonic Boom.
 */
void BattleAnim_SetupSonicBoomUseFourStream(void) {
    D_8219CAC0 = 0;
    BattleAnim_ResetSharedEffectMatrix();
    FourStreamTrail_Init();
}

/**
 * Update hook for Sonic Boom's use animation: on each of the first 4 frames starts a pale cyan
 * stream at the secondary owner's bone, fanned out at one of three angles and spinning in a random
 * direction. Returns -1 (done) at frame 50, otherwise whether the streams have finished (0 for the
 * first two frames).
 * Moves: Sonic Boom (use)
 * TODO: Human contributor add screenshot
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Sonic Boom.
 */
s32 BattleAnim_RunSonicBoomUseFourStream(void) {
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
    if (D_8219CAC0 >= 50) {
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
        FourStreamTrail_Start(sp64, sp60, sp5C, sp58, sp54, sp50, 0xC0, 0xFF, 0xFF, 0x80, (((guRandom() % 2) * 2) - 1) * D_DBL_82197940, // #C0FFFF
                              2.0f, 13.0f, 0x28);
    }

    if (D_8219CAC0 >= 2) {
        var_v1 = FourStreamTrail_IsComplete();
    } else {
        var_v1 = 0;
    }
    return var_v1;
}

/**
 * Draw hook for Sonic Boom's use animation: from frame 2 on, loads the shared effect matrix and
 * draws the streams.
 * Moves: Sonic Boom (use)
 * TODO: Human contributor add screenshot
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Sonic Boom.
 */
void BattleAnim_DrawSonicBoomUseFourStream(void) {
    if (D_8219CAC0 >= 2) {
        gSPMatrix(gDisplayListHead++, &D_8219CAC8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

        gDisplayListHead = FourStreamTrail_Draw(gDisplayListHead);
    }
}

/**
 * Init hook for Spike Cannon's use animation: clears the frame counter, resets the shared matrix
 * and initializes the four-stream trail pool.
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Spike Cannon.
 */
void BattleAnim_SetupSpikeCannonUseFourStream(void) {
    D_8219CAC2 = 0;
    BattleAnim_ResetSharedEffectMatrix();
    SpikeCannonFourStream_Init();
}

/**
 * Update hook for Spike Cannon's use animation: every 4 frames, 4 times, starts a pale cyan stream
 * from the attacker toward the target, bent to one of three angles. Returns whether the streams
 * have finished (0 for the first two frames).
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Spike Cannon.
 */
s32 BattleAnim_RunSpikeCannonUseFourStream(void) {
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
        SpikeCannonFourStream_Start(sp60, sp5C, sp58, sp54, sp50, 0.0f, 0xD0, 0xFF, 0xFF, 0x80, D_FLT_82197950, 2.0f, 4.0f, 0x28); // #D0FFFF
    }

    if (D_8219CAC2 >= 2) {
        var_v1 = SpikeCannonFourStream_IsComplete();
    } else {
        var_v1 = 0;
    }
    return var_v1;
}

/**
 * Draw hook for Spike Cannon's use animation: from frame 2 on, loads the shared effect matrix and
 * draws the streams.
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Spike Cannon.
 */
void BattleAnim_DrawSpikeCannonUseFourStream(void) {
    if (D_8219CAC2 >= 2) {
        gSPMatrix(gDisplayListHead++, &D_8219CAC8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

        gDisplayListHead = SpikeCannonFourStream_Draw(gDisplayListHead);
    }
}

/**
 * Init hook for the stinger moves (Poison Sting, Twineedle, Pin Missile, Spike Cannon): resets the
 * shared matrix, starts one pale cyan stream from the attacker toward the target, and spawns the
 * needle particle (kind 1) at the start point.
 * Moves: Pin Missile (use), Poison Sting (use), Twineedle (use)
 * TODO: Human contributor add screenshot
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Poison Sting, Twineedle, Pin Missile.
 */
void BattleAnim_StingerMoves_Init(void) {
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
    OwnerAnchoredFourStream_Start(sp58, sp54, sp50, sp4C, sp48, sp44, 0xC0, 0xFF, 0xFF, 0xA0, D_FLT_82197954, 2.0f, 4.0f, 0x28); // #C0FFFF
    sp5C.x = sp58;
    sp5C.y = sp54;
    sp5C.z = sp50;
    BattleAnim_SpawnSecondaryOwnerParticle(sp5C, 1);
}

/**
 * Update hook for the stinger moves: returns -1 (done) at frame 50, otherwise whether the stream
 * has finished.
 * Moves: Pin Missile (use), Poison Sting (use), Twineedle (use)
 * TODO: Human contributor add screenshot
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Poison Sting, Twineedle, Pin Missile.
 */
s32 BattleAnim_StingerMoves_Update(void) {
    D_8219CB08++;
    if (D_8219CB08 >= 50) {
        return -1;
    }

    return OwnerAnchoredFourStream_IsComplete();
}

/**
 * Draw hook for the stinger moves: loads the shared effect matrix and draws the stream.
 * Moves: Pin Missile (use), Poison Sting (use), Twineedle (use)
 * TODO: Human contributor add screenshot
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Poison Sting, Twineedle, Pin Missile.
 */
void BattleAnim_StingerMoves_Draw(void) {
    gSPMatrix(gDisplayListHead++, &D_8219CAC8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gDisplayListHead = OwnerAnchoredFourStream_Draw(gDisplayListHead);
}

/**
 * Emits Tri Attack's radial burst (variant A, 9 rays, white) from the attacker toward the target.
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Tri Attack.
 */
void BattleAnim_EmitTriAttackUseRadial(void) {
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
    TriAttackRadial_EmitVariantA(sp5C, sp58, sp54, sp50, sp4C, sp48, 9, 0xFF, 0xFF, 0xFF, 0xB4, D_FLT_82197958, 2.0f, 20.0f, 0x3C); // #FFFFFF
}

/**
 * Init hook for Tri Attack's use animation: clears the frame counter, resets the shared matrix and
 * the radial pool, and emits the burst.
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Tri Attack.
 */
void BattleAnim_SetupTriAttackUseRadial(void) {
    D_8219CB0A = 0;
    BattleAnim_ResetSharedEffectMatrix();
    Radial20_ResetPool();
    BattleAnim_EmitTriAttackUseRadial();
}

/**
 * Update hook for Tri Attack's use animation: returns -1 (done) at frame 181, otherwise whether
 * the radial pool has finished.
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Tri Attack.
 */
s32 BattleAnim_RunTriAttackUseRadial(void) {
    D_8219CB0A++;
    if (D_8219CB0A >= 181) {
        return -1;
    }
    return Radial20_IsComplete();
}

/**
 * Draw hook for Tri Attack's use animation: loads the shared effect matrix and draws the radial
 * pool.
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Tri Attack.
 */
void BattleAnim_DrawTriAttackUseRadial(void) {
    gSPMatrix(gDisplayListHead++, &D_8219CAC8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gDisplayListHead = Radial20_Draw(gDisplayListHead);
}

/**
 * Starts Aurora Beam's two double-texture beam trails from the attacker toward the target, each
 * with its own textures, scroll speeds, combiner and colors.
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Aurora Beam.
 */
void BattleAnim_SeedAuroraBeamUseDoubleTextureTrail(void) {
    static CombinerCycleArgs D_84387FC0 = { 2, 1, 0xE, 1, 2, 2, 3, 1 };
    static CombinerCycleArgs D_84387FE0 = { 3, 5, 0, 5, 3, 7, 0, 5 };
    static CombinerCycleArgs D_84388000 = { 2, 1, 0xE, 1, 2, 1, 3, 1 };
    static CombinerCycleArgs D_84388020 = { 3, 5, 0, 5, 0, 7, 5, 7 };

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

/**
 * Init hook for Aurora Beam's use animation: resets the shared matrix and the trail pool, then
 * starts the beams.
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Aurora Beam.
 */
void BattleAnim_SetupAuroraBeamUseDoubleTextureTrail(void) {
    BattleAnim_ResetSharedEffectMatrix();
    DoubleTextureTrail_InitPool();
    BattleAnim_SeedAuroraBeamUseDoubleTextureTrail();
}

/**
 * Update hook for Aurora Beam's use animation: advances the beam trails and returns whether they
 * have finished.
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Aurora Beam.
 */
s32 BattleAnim_RunAuroraBeamUseDoubleTextureTrail(void) {
    return DoubleTextureTrail_UpdateAll();
}

/**
 * Draw hook for Aurora Beam's use animation: loads the shared effect matrix and draws the beam
 * trails.
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Aurora Beam.
 */
void BattleAnim_DrawAuroraBeamUseDoubleTextureTrail(void) {
    gSPMatrix(gDisplayListHead++, &D_8219CAC8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gDisplayListHead = DoubleTextureTrail_DrawAll(gDisplayListHead);
}

/**
 * Starts one Ice Beam trail from the attacker toward the target, with the direction jittered at
 * random.
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Ice Beam.
 */
void BattleAnim_SeedIceBeamUseSixSlotTrail(void) {
    static CombinerCycleArgs D_84388040 = { 3, 5, 1, 5, 1, 7, 3, 7 };
    static CombinerCycleArgs D_84388060 = { 0x1F, 0x1F, 0x1F, 0, 7, 7, 7, 0 };

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

    HyperBeamIceBeamTrail_Spawn(0, spA4, spA0, sp9C, sp98, sp94, sp90, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0, 0x64, 0xFF, 0xFF, D_FLT_82197974, 2.0f,
                  20.0f, 0x3C, 0x95, 0x95, 0, 0xA, 0, 0xD, 0, 0, 0, 0, &D_84388040, &D_84388060);
}

/**
 * Init hook for Ice Beam's use animation: clears the frame counter, resets the shared matrix and
 * the six-slot trail pool, and starts the first trail.
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Ice Beam.
 */
void BattleAnim_SetupIceBeamUseSixSlotTrail(void) {
    D_8219CB0C = 0;
    BattleAnim_ResetSharedEffectMatrix();
    HyperBeamIceBeamTrail_ResetPool();
    BattleAnim_SeedIceBeamUseSixSlotTrail();
}

/**
 * Update hook for Ice Beam's use animation: starts another trail every 10 frames, advances them,
 * and returns whether they have finished.
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Ice Beam.
 */
s32 BattleAnim_RunIceBeamUseSixSlotTrail(void) {
    D_8219CB0C++;
    if ((D_8219CB0C % 10) == 0) {
        BattleAnim_SeedIceBeamUseSixSlotTrail();
    }
    return HyperBeamIceBeamTrail_UpdateAll();
}

/**
 * Draw hook for Ice Beam's use animation: loads the shared effect matrix and draws the trails.
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Ice Beam.
 */
void BattleAnim_DrawIceBeamUseSixSlotTrail(void) {
    gSPMatrix(gDisplayListHead++, &D_8219CAC8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gDisplayListHead = HyperBeamIceBeamTrail_DrawAll(gDisplayListHead);
}

/**
 * Starts Psybeam's two double-texture beam trails from the attacker toward the target, each with
 * its own textures, scroll speeds, combiner and colors.
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Psybeam.
 */
void BattleAnim_SeedPsybeamUseDoubleTextureTrail(void) {
    static CombinerCycleArgs D_84388080 = { 3, 5, 1, 5, 6, 7, 2, 3 };
    static CombinerCycleArgs D_843880A0 = { 0x1F, 0x1F, 0x1F, 0, 0, 7, 5, 7 };
    static CombinerCycleArgs D_843880C0 = { 3, 5, 2, 5, 1, 7, 3, 7 };
    static CombinerCycleArgs D_843880E0 = { 0x1F, 0x1F, 0x1F, 0, 0, 7, 5, 7 };

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

/**
 * Init hook for Psybeam's use animation: resets the shared matrix and the trail pool, then starts
 * the beams.
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Psybeam.
 */
void BattleAnim_SetupPsybeamUseDoubleTextureTrail(void) {
    BattleAnim_ResetSharedEffectMatrix();
    DoubleTextureTrail_InitPool();
    BattleAnim_SeedPsybeamUseDoubleTextureTrail();
}

/**
 * Update hook for Psybeam's use animation: advances the beam trails and returns whether they have
 * finished.
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Psybeam.
 */
s32 BattleAnim_RunPsybeamUseDoubleTextureTrail(void) {
    return DoubleTextureTrail_UpdateAll();
}

/**
 * Draw hook for Psybeam's use animation: loads the shared effect matrix and draws the beam trails.
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Psybeam.
 */
void BattleAnim_DrawPsybeamUseDoubleTextureTrail(void) {
    gSPMatrix(gDisplayListHead++, &D_8219CAC8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gDisplayListHead = DoubleTextureTrail_DrawAll(gDisplayListHead);
}

/**
 * Starts the two double-texture trails of start effect 77 from the owner toward the
 * target.
 * Not reached in play (2026-11-13): did not run in the 165-move battle sweep (each move used once,
 * from the command menu to the end of its turn) or in a tour of the menus and a COM battle.
 * @unverified Name from Stadium 1.
 */
void BattleAnim_StartEffect77DoubleTextureTrail_Seed(void) {
    static CombinerCycleArgs D_84388100 = { 2, 1, 0xE, 1, 2, 7, 1, 3 };
    static CombinerCycleArgs D_84388120 = { 3, 5, 0, 5, 0, 7, 5, 7 };
    static CombinerCycleArgs D_84388140 = { 2, 1, 0xE, 1, 2, 7, 1, 3 };
    static CombinerCycleArgs D_84388160 = { 3, 5, 0, 5, 0, 7, 5, 7 };

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

/**
 * Init hook for start effect 77: resets the shared matrix and the trail pool, then starts
 * the trails.
 * Not reached in play (2026-11-13): did not run in the 165-move battle sweep (each move used once,
 * from the command menu to the end of its turn) or in a tour of the menus and a COM battle.
 * @unverified Name from Stadium 1.
 */
void BattleAnim_StartEffect77DoubleTextureTrail_Init(void) {
    BattleAnim_ResetSharedEffectMatrix();
    DoubleTextureTrail_InitPool();
    BattleAnim_StartEffect77DoubleTextureTrail_Seed();
}

/**
 * Update hook for start effect 77: advances the trails.
 * Not reached in play (2026-11-13): did not run in the 165-move battle sweep (each move used once,
 * from the command menu to the end of its turn) or in a tour of the menus and a COM battle.
 * @unverified Name from Stadium 1.
 */
s32 BattleAnim_StartEffect77DoubleTextureTrail_Update(void) {
    return DoubleTextureTrail_UpdateAll();
}

/**
 * Draw hook for start effect 77: loads the shared matrix and draws the trails.
 * Not reached in play (2026-11-13): did not run in the 165-move battle sweep (each move used once,
 * from the command menu to the end of its turn) or in a tour of the menus and a COM battle.
 * @unverified Name from Stadium 1.
 */
void BattleAnim_StartEffect77DoubleTextureTrail_Draw(void) {
    gSPMatrix(gDisplayListHead++, &D_8219CAC8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gDisplayListHead = DoubleTextureTrail_DrawAll(gDisplayListHead);
}

/**
 * Starts Solar Beam's double-texture beam trail from the attacker toward the target.
 * Seen in play (2026-11-13) ran on SolarBeam's second turn, when the charged beam fired (the sweep
 * only saw the charging turn).
 * Seen in play (2026-11-14) (Metronome bench, one movie per move, 1P Onix vs Pinsir on Splash, exec
 * breakpoint): ran only for Solar Beam.
 * @unverified Name from Stadium 1.
 */
void BattleAnim_SeedSolarBeamUseDoubleTextureTrail(void) {
    static CombinerCycleArgs D_84388180 = { 2, 1, 0xE, 1, 2, 1, 3, 1 };
    static CombinerCycleArgs D_843881A0 = { 3, 5, 0, 5, 0, 7, 5, 7 };

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

/**
 * Init hook for Solar Beam's firing animation: resets the shared matrix and the trail pool, then
 * starts the beam.
 * Seen in play (2026-11-13) ran on SolarBeam's second turn, when the charged beam fired.
 * Seen in play (2026-11-14) (Metronome bench, one movie per move, 1P Onix vs Pinsir on Splash, exec
 * breakpoint): ran only for Solar Beam.
 * @unverified Name from Stadium 1.
 */
void BattleAnim_SetupSolarBeamUseDoubleTextureTrail(void) {
    BattleAnim_ResetSharedEffectMatrix();
    DoubleTextureTrail_InitPool();
    BattleAnim_SeedSolarBeamUseDoubleTextureTrail();
}

/**
 * Update hook for Solar Beam's firing animation: advances the beam trail and returns whether it
 * has finished.
 * Seen in play (2026-11-13) ran on SolarBeam's second turn, while the charged beam fired.
 * Seen in play (2026-11-14) (Metronome bench, one movie per move, 1P Onix vs Pinsir on Splash, exec
 * breakpoint): ran only for Solar Beam.
 * @unverified Name from Stadium 1.
 */
s32 BattleAnim_RunSolarBeamUseDoubleTextureTrail(void) {
    return DoubleTextureTrail_UpdateAll();
}

/**
 * Draw hook for Solar Beam's firing animation: loads the shared effect matrix and draws the beam
 * trail.
 * Seen in play (2026-11-13) ran on SolarBeam's second turn, while the charged beam fired.
 * Seen in play (2026-11-14) (Metronome bench, one movie per move, 1P Onix vs Pinsir on Splash, exec
 * breakpoint): ran only for Solar Beam.
 * @unverified Name from Stadium 1.
 */
void BattleAnim_DrawSolarBeamUseDoubleTextureTrail(void) {
    gSPMatrix(gDisplayListHead++, &D_8219CAC8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gDisplayListHead = DoubleTextureTrail_DrawAll(gDisplayListHead);
}

/**
 * Starts Hyper Beam's two double-texture beam trails from the attacker toward the target, each
 * with its own textures, scroll speeds, combiner and colors.
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Hyper Beam.
 */
void BattleAnim_SeedHyperBeamUseDoubleTextureTrail(void) {
    static CombinerCycleArgs D_843881C0 = {
        0x00000002, 0x00000001, 0x0000000E, 0x00000001, 0x00000007, 0x00000007, 0x00000007, 0x00000003,
    };
    static CombinerCycleArgs D_843881E0 = {
        0x00000003, 0x00000005, 0x00000000, 0x00000005, 0x00000007, 0x00000007, 0x00000007, 0x00000000,
    };
    static CombinerCycleArgs D_84388200 = {
        0x00000002, 0x00000001, 0x0000000E, 0x00000001, 0x00000002, 0x00000001, 0x00000003, 0x00000001,
    };
    static CombinerCycleArgs D_84388220 = {
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
