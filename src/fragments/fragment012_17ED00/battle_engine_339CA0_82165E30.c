/* Fixed-layout split; original translation-unit boundaries remain unconfirmed. */
#include "battle_engine_339CA0.h"

void BattleAnim_CallbackUnusedGrowingSparkVariant(Particle* arg0) {
    switch (arg0->lifecycle) {
        case 1:
            BattleAnim_SetupUnusedGrowingSparkVariant(arg0);
            break;

        case 2:
            if (Particle_DecrementUnkA6ToZeroThenAdvance(arg0) != 0) {
                Particle_EnableRendering(arg0);
            }
            break;

        case 3:
            Particle_TickDelayAndAdvanceLifecycle(arg0, 0xC);
            break;

        case 4:
            Particle_ApproachPrimAlphaThenAdvance(arg0, 0x20, 0x20);
            break;

        case 5:
            Particle_DisableAndDetach(arg0);
            break;
    }

    if (Particle_IsRenderingEnabled(arg0) != 0) {
        Particle_ApproachScaleTarget(arg0);
        Particle_EnvG_Approach_0BBF0(arg0, 0, 0x10);
        Particle_EnvB_Approach_0BBC0(arg0, 0, 8);
    }
}


/**
 * Moves: Bone Club (hit), Dizzy Punch (hit), Double Slap (hit), Drill Peck (hit), Headbutt (hit), Pay Day
 * (hit)
 * TODO: Human contributor add screenshot
 * Effect end init 14 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used: it
 * ran for exactly Bone Club, Dizzy Punch, Double Slap, Drill Peck, Headbutt, Pay Day.
 */
void BattleAnim_RunStrongContactMoveHitSpark(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_RunDefaultHitSpark, &gBattleAnimParticleDescriptors[0x34], 0, 1, 0x11, 7, 0, 7);
    BattleAnim_CreateEffectSlotForCurrentOwner(2, BattleAnim_RunPhysicalHitPurpleSmoke, &gBattleAnimParticleDescriptors[0x3D], 0, 8, 0x11, 7, 1, 0);
}

/**
 * Used by Comet Punch, Wing Attack, Double Kick, Sonic Boom, Night Shade
 * Effect end init 35 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used: it
 * ran for exactly Comet Punch, Double Kick, Night Shade, Sonic Boom, Wing Attack.
 */
void BattleAnim_InitializeUniqueSharedHitSpark(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_RunDefaultHitSpark, &gBattleAnimParticleDescriptors[0x34], 0, 1, 0x11, 7, 0, 6);
    BattleAnim_CreateEffectSlotForCurrentOwner(2, BattleAnim_RunPhysicalHitPurpleSmoke, &gBattleAnimParticleDescriptors[0x3D], 0, 8, 0x11, 7, 1, 0);
}

/**
 * Effect end init 36 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used: it
 * ran for exactly Low Kick.
 */
void BattleAnim_InitializeLowKickHit(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_RunDefaultHitSpark, &gBattleAnimParticleDescriptors[0x34], 0, 1, 0x11, 9, 0, 8);
    BattleAnim_CreateEffectSlotForCurrentOwner(2, BattleAnim_RunPhysicalHitPurpleSmoke, &gBattleAnimParticleDescriptors[0x3D], 0, 8, 0x11, 9, 2, 0);
}

/**
 * Moves: Bide (hit), Bonemerang (hit), Counter (hit), Hi Jump Kick (hit), Jump Kick (hit), Karate Chop (hit),
 * Pound (hit), Quick Attack (hit), Rage (hit), Rolling Kick (hit), Struggle (hit), Tackle (hit), Take Down
 * (hit)
 * TODO: Human contributor add screenshot
 * Effect end init 44 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used: it
 * ran for exactly Bonemerang, Hi Jump Kick, Jump Kick, Karate Chop, Pound, Quick Attack, Rage,
 * Rolling Kick, Struggle, Tackle, Take Down.
 */
void BattleAnim_InitializeDefaultLimbForMove(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_RunDefaultHitSpark, &gBattleAnimParticleDescriptors[0x34], 0, 1, 0x11, 9, 0, 6);
    BattleAnim_CreateEffectSlotForCurrentOwner(2, BattleAnim_RunPhysicalHitPurpleSmoke, &gBattleAnimParticleDescriptors[0x3D], 0, 8, 0x11, 9, 0, 0);
}

/**
 * Moves: Mega Kick (hit), Mega Punch (hit), Skull Bash (hit)
 * TODO: Human contributor add screenshot
 * Effect end init 80 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used: it
 * ran for exactly Mega Kick, Mega Punch.
 */
void BattleAnim_InitializeSpecialLimbForMove(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_RunDefaultHitSpark, &gBattleAnimParticleDescriptors[0x34], 0, 1, 0x11, 9, 0, 0x10);
    BattleAnim_CreateEffectSlotForCurrentOwner(2, BattleAnim_RunPhysicalHitPurpleSmoke, &gBattleAnimParticleDescriptors[0x3D], 0, 8, 0x11, 9, 0, 0);
}

/**
 * Moves: Horn Attack (hit), Horn Drill (hit), Peck (hit), Pin Missile (hit), Spike Cannon (hit)
 * TODO: Human contributor add screenshot
 * Effect end init 37 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used: it
 * ran for exactly Horn Attack, Peck, Pin Missile, Spike Cannon.
 */
void BattleAnim_InitializePointyMoveHitSparks(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_RunPointyMoveHitSpark, &gBattleAnimParticleDescriptors[0x34], 0, 1, 0x11, 9, 3, 0);
}

/**
 * Effect end init 38 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used: it
 * ran for exactly Poison Sting, Twineedle.
 */
void BattleAnim_InitializePoisonStingTwineedleHit(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_RunPointyMoveHitSpark, &gBattleAnimParticleDescriptors[0x34], 0, 1, 0x11, 9, 4, 0);
}

/**
 * Effect end init 47 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used: it
 * ran for exactly Fury Attack, Gust.
 */
void BattleAnim_InitializeFuryAttackGustHit(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_RunDefaultHitSpark, &gBattleAnimParticleDescriptors[0x34], 0, 7, 0x11, 9, 1, 0xC);
}

/**
 * Effect init for the start of the Ice Punch animation.
 * Effect start init 41 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used:
 * it ran for exactly Ice Punch.
 */
void BattleAnim_InitializeIcePunchUse(void) {
    s32 temp_s1 = gBattleAnimCurrentAnchor & 0xFF;

    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0, 8, 6, BattleAnim_RunSparkleHit, &D_8218E798, 0, 8, 0x11, temp_s1, 0x18, 2);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(1, 8, 6, BattleAnim_RunSparkleHit, &D_8218E798, 0, 8, 0x11, temp_s1, 0x18, 2);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(2, 8, 6, BattleAnim_RunSparkleHit, &D_8218E798, 0, 8, 0x11, temp_s1, 0x18, 2);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(4, 8, 6, BattleAnim_RunSparkleHit, &D_8218E798, 0, 8, 0x11, temp_s1, 0x18, 2);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0, 6, 0xC, BattleAnim_CallbackEndEffect67Descriptor3DAnimatedGravityFade, &D_8218E7D0, 0, 2, 0x11, temp_s1, 1, 0);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(1, 6, 0xA, BattleAnim_CallbackEndEffect67Descriptor3DAnimatedGravityFade, &D_8218E7D0, 0, 2, 0x11, temp_s1, 1, 0);
}

/**
 * Effect end init 42 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used: it
 * ran for exactly Ice Punch.
 */
void BattleAnim_InitializeIcePunchHit(void) {
    UNUSED s32 pad; // FAKE: stack padding

    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_RunDefaultHitSpark, &gBattleAnimParticleDescriptors[0x34], 0, 1, 0x11, 9, 3, 5);
    BattleAnim_CreateEffectSlotForCurrentOwner(2, BattleAnim_CallbackEndEffect67Descriptor3DAnimatedGravityFade, &gBattleAnimParticleDescriptors[0x3D], 0, 8, 0x10, 0x64, 0, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(3, BattleAnim_CallbackEndEffect67Descriptor3DAnimatedGravityFade, &gBattleAnimParticleDescriptors[0x3D], 0, 8, 0x10, 0x64, 0, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(4, BattleAnim_RunSparkleHit, &gBattleAnimParticleDescriptors[0x42], 0, 8, 9, 0, 0x18, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(8, BattleAnim_RunSparkleHit, &gBattleAnimParticleDescriptors[0x42], 0, 4, 9, 0, 0x18, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(0xC, BattleAnim_RunSparkleHit, &gBattleAnimParticleDescriptors[0x42], 0, 4, 9, 0, 0x18, 0);
    BattleAnim_SpawnOwnerModelTintRampDetach(0, 0x33, 0xE0, 0, 0x20);
}

/**
 * Effect end init 43 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used: it
 * ran for exactly Thunder Punch.
 */
void BattleAnim_InitializeThunderPunchHit(void) {
    func_8213B560(0, &func_82162C68, &D_8218E728, 0, 1, 0x11, 9, 3, 5);
    func_8213B560(4, &func_82162938, &D_8218E788, 0, 1, 0x10, 0x64, 0, 0);
    func_8213B5D8(0, 4, 5, &func_8214E67C, &D_8218E610, 8, 4, 2, 0, 0, 0);
    func_8213B794(0, 0, 0x40, 8, 0xC8);
    func_8213BC00(0, 0x17, 0xE1, 0, 0x40);
}

void BattleAnim_OrphanDescriptor34Emitter(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_CallbackOrphanDescriptor34ColorFadeDetach, &gBattleAnimParticleDescriptors[0x34], 0, 5, 0x11, gBattleAnimCurrentAnchor, 0, 0);
}

/**
 * Effect start init 108 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used:
 * it ran for exactly Submission.
 */
void BattleAnim_InitializeSubmissionUse(void) {
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0, 3, 2, BattleAnim_HeavyHitAnimatedRiseFade, &gBattleAnimParticleDescriptors[0x3F], 0, 0x10, 0xA, 0, 0x11, 0);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0x28, 3, 2, BattleAnim_HeavyHitAnimatedRiseFade, &gBattleAnimParticleDescriptors[0x3F], 0, 0x10, 0xA, 0, 0x11, 0);
}

/**
 * Effect end init 39 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used: it
 * ran for exactly Stomp.
 */
void BattleAnim_InitializeStompHit(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_RunHeavyHitSparksAndSmoke, &gBattleAnimParticleDescriptors[0x34], 0, 1, 0x11, 9, 0, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_RunGroundedCircularHitSpark, &gBattleAnimParticleDescriptors[0x36], 0, 1, 0xA, 0, 0, 0);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(4, 3, 2, BattleAnim_HeavyHitAnimatedRiseFade, &gBattleAnimParticleDescriptors[0x3F], 0, 0x10, 0xA, 0, 0x11, 0);
}

/**
 * Moves: Body Slam (hit), Crabhammer (hit), Double-Edge (hit), Fly (hit), Seismic Toss (hit), Slam (hit),
 * Thrash (hit)
 * TODO: Human contributor add screenshot
 * Effect end init 45 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used: it
 * ran for exactly Body Slam, Crabhammer, Double Edge, Seismic Toss, Slam, Thrash.
 */
void BattleAnim_InitializeGroundedCircularHitSpark(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_RunHeavyHitSparksAndSmoke, &gBattleAnimParticleDescriptors[0x34], 0, 5, 0x11, 0x64, 9, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(8, BattleAnim_RunGroundedCircularHitSpark, &gBattleAnimParticleDescriptors[0x36], 0, 1, 0xA, 0, 0, 0);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0xC, 3, 2, BattleAnim_HeavyHitAnimatedRiseFade, &gBattleAnimParticleDescriptors[0x3F], 0, 0x10, 0xA, 0, 0x11, 0);
}

/**
 * Effect end init 46 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used: it
 * ran for exactly Submission.
 */
void BattleAnim_InitializeSubmissionHit(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_RunHeavyHitSparksAndSmoke, &gBattleAnimParticleDescriptors[0x34], 0, 5, 0xA, 0, 0xA, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(8, BattleAnim_RunGroundedCircularHitSpark, &gBattleAnimParticleDescriptors[0x36], 0, 1, 0xA, 0, 0, 0);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0xC, 3, 2, BattleAnim_HeavyHitAnimatedRiseFade, &gBattleAnimParticleDescriptors[0x3F], 0, 0x10, 0xA, 0, 0x11, 0);
}

/**
 * Moves: Bite (hit), Clamp (hit), Guillotine (hit), Hyper Fang (hit), Super Fang (hit), Vice Grip (hit)
 * TODO: Human contributor add screenshot
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Vise Grip, Bite, Clamp, Hyper Fang, Super Fang.
 */
void BattleAnim_InitializeBitingMoveEndEffect(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_RunHeavyHitSparksAndSmoke, &gBattleAnimParticleDescriptors[0x34], 0, 7, 0xA, 0, 0xB, 0);
}

/**
 * Effect init that spawns the Metronome and Swift animation. Player sweep (all 165 moves used in
 * battle): only Metronome and Swift reached this function.
 * Effect start init 7 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used:
 * it ran for exactly Swift.
 */
void BattleAnim_InitializeSwiftUse(void) {
    func_8213B644(0, 8, 0x20);
}

/**
 * Effect end init 52 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used: it
 * ran for exactly Swift.
 */
void BattleAnim_InitializeSwiftHit(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(0xC, BattleAnim_RunSparkleHit, &gBattleAnimParticleDescriptors[0x42], 0, 8, 9, 0, 0x17, 1);
    BattleAnim_CreateEffectSlotForCurrentOwner(0x12, BattleAnim_RunSparkleHit, &gBattleAnimParticleDescriptors[0x42], 0, 0xA, 9, 0, 0x17, 1);
    BattleAnim_CreateEffectSlotForCurrentOwner(0x20, BattleAnim_RunSparkleHit, &gBattleAnimParticleDescriptors[0x42], 0, 5, 9, 0, 0x17, 1);
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_RunSwiftHitEffect2, &gDefaultParticleDescriptor, 0, 2, 9, 0, 0, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(3, BattleAnim_RunSwiftHitEffect2, &gDefaultParticleDescriptor, 0, 2, 9, 0, 0, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(5, BattleAnim_RunSwiftHitEffect2, &gDefaultParticleDescriptor, 0, 2, 9, 0, 0, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(8, BattleAnim_RunSwiftHitEffect2, &gDefaultParticleDescriptor, 0, 2, 9, 0, 0, 0);
}

void BattleAnim_StartEffect137Descriptor3FRisingFade(void) {
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0, 3, 2, BattleAnim_HeavyHitAnimatedRiseFade, &gBattleAnimParticleDescriptors[0x3F], 0, 0x10, 0xA, 0, 0x11, 0);
}

void func_82166DC4(void) {
    func_8213B5D8(0, 3, 2, &BattleAnim_RunSmallSand, &D_8218E7D0, 0, 6, 0x11, (s32) D_8219A80A, 0x11, 0);
    func_8213B5D8(0, 4, 2, &BattleAnim_RunLargeSand, &D_8218E7D0, 0, 4, 0x11, (s32) D_8219A80A, 0x11, 0);
}

/**
 * Effect start init 13 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used:
 * it ran for exactly Fury Swipes, Scratch, Slash.
 */
void BattleAnim_InitializeScratchSlashUse(void) {
    void (*sp30)(s8*);

    if (func_82107CF0(D_8219A814) == 0x7B) {
        BattleAnim_InitializeCutUse();
        return;
    }
    sp30 = func_8215FAA4;
    func_8213B560(0, (M2C_UNK*)sp30, &D_8218E6D0, 0, 3, 0x10, (s32) D_8219A80A, 0xB, 0);
    func_8213B560(4, (M2C_UNK*)sp30, &D_8218E6D0, 0, 3, 0x10, (s32) D_8219A80A, 0xB, 1);
    func_8213B560(0xA, (M2C_UNK*)sp30, &D_8218E6D0, 0, 3, 0x10, (s32) D_8219A80A, 0xB, 2);
    func_8213B560(0x1E, &BattleAnim_RunSlashingMoveFullScreenFlash, &D_8218E6C8, 0, 1, 0x18, 0, 0xF, 0);
    func_8213B720(0x23, 0, 0x10, 0x12);
}

/**
 * Effect init for the end (impact) of the Fury Swipes and Scratch and Slash animation.
 * Effect end init 5 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used: it
 * ran for exactly Fury Swipes, Scratch, Slash.
 */
void BattleAnim_InitializeScratchSlashHit(void) {
    UNUSED s32 pad; // FAKE: stack padding

    if (BattleAnim_GetOwnerSpecies(gBattleAnimSecondaryOwner) == 0x7B) {
        BattleAnim_InitializeCutCrabhammerHit();
        return;
    }

    BattleAnim_SpawnDescriptor25AlphaHoldFadeOut(0, 2, 0x10, 0x12, 0xFF);
    BattleAnim_CreateEffectSlotForCurrentOwner(3, BattleAnim_SlashGrowFade, &gBattleAnimParticleDescriptors[0x2A], 0, 1, 0x10, gBattleAnimCurrentAnchor, 0x10, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(3, BattleAnim_SlashGrowFade, &gBattleAnimParticleDescriptors[0x2A], 0, 1, 0x10, gBattleAnimCurrentAnchor, 0x10, 1);
    BattleAnim_CreateEffectSlotForCurrentOwner(3, BattleAnim_SlashGrowFade, &gBattleAnimParticleDescriptors[0x2A], 0, 1, 0x10, gBattleAnimCurrentAnchor, 0x10, 2);
    BattleAnim_CreateEffectSlotForCurrentOwner(3, BattleAnim_CallbackSharedOwnerKeyedGrowColorAlphaFade, &gBattleAnimParticleDescriptors[0x28], 0, 1, 0x18, 0, 0xF, 0);
}

/**
 * Moves: Cut (use), Scratch (use), Slash (use)
 * TODO: Human contributor add screenshot
 * Seen in play (2026-11-12): in the per-move sweep it ran only for Cut, not for Slash or Scratch,
 * so the old name BattleAnim_InitializeCutSlashScratchEffect was too broad.
 */
void BattleAnim_InitializeCutEffect(void) {
    UNUSED s32 pad; // FAKE: stack padding

    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_CallbackSharedDescriptor29ScaleAnimFade, &gBattleAnimParticleDescriptors[0x29], 0, 1, 0x10, gBattleAnimCurrentAnchor, 0xB, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(4, BattleAnim_CallbackSharedDescriptor29ScaleAnimFade, &gBattleAnimParticleDescriptors[0x29], 0, 1, 0x10, gBattleAnimCurrentAnchor, 0xB, 1);
    BattleAnim_CreateEffectSlotForCurrentOwner(0xA, BattleAnim_CallbackSharedDescriptor29ScaleAnimFade, &gBattleAnimParticleDescriptors[0x29], 0, 1, 0x10, gBattleAnimCurrentAnchor, 0xB, 2);
    BattleAnim_CreateEffectSlotForCurrentOwner(0x1E, BattleAnim_CallbackSharedOwnerKeyedGrowColorFade, &gBattleAnimParticleDescriptors[0x41], 0, 1, 0x18, 0, 0xF, 0);
    BattleAnim_SpawnDescriptor25AlphaHoldFadeOutFullAlpha(0x23, 0, 0x10, 0x12);
}

/**
 * Effect init for the end (impact) of the Crabhammer and Cut animation.
 * Effect end init 30 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used: it
 * ran for exactly Crabhammer, Cut.
 */
void BattleAnim_InitializeCutCrabhammerHit(void) {
    func_8213B794(0, 2, 0x10, 0x12, 0xFF);
    func_8213B560(3, &func_821603C8, &D_8218E6D8, 0, 1, 0x10, (s32) D_8219A80A, 0x10, 2);
    func_8213B560(3, &BattleAnim_RunSlashMoveWhiteFlashOverlay, &D_8218E790, 0, 1, 0x18, 0, 0xF, 0);
}

/**
 * Effect start init 117 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used:
 * it ran for exactly Vine Whip.
 */
void BattleAnim_InitializeVineWhipUse(void) {
    UNUSED s32 pad; // FAKE: stack padding

    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_CallbackSharedDescriptor29ScaleAnimFade, &gBattleAnimParticleDescriptors[0x29], 0, 1, 0x10, gBattleAnimCurrentAnchor, 0xD, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(4, BattleAnim_CallbackSharedDescriptor29ScaleAnimFade, &gBattleAnimParticleDescriptors[0x29], 0, 1, 0x10, gBattleAnimCurrentAnchor, 0xD, 1);
    BattleAnim_CreateEffectSlotForCurrentOwner(0xA, BattleAnim_CallbackSharedDescriptor29ScaleAnimFade, &gBattleAnimParticleDescriptors[0x29], 0, 1, 0x10, gBattleAnimCurrentAnchor, 0xD, 2);
    BattleAnim_CreateEffectSlotForCurrentOwner(0x1E, BattleAnim_CallbackSharedOwnerKeyedGrowColorFade, &gBattleAnimParticleDescriptors[0x41], 0, 1, 0x18, 0, 0xD, 1);
    BattleAnim_SpawnDescriptor25AlphaHoldFadeOutFullAlpha(0x23, 0, 0x10, 0x27);
}

/**
 * Effect end init 85 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used: it
 * ran for exactly Vine Whip.
 */
void BattleAnim_InitializeVineWhipHit(void) {
    UNUSED s32 pad; // FAKE: stack padding

    BattleAnim_SpawnDescriptor25AlphaHoldFadeOut(0, 2, 0x10, 0x27, 0xFF);
    BattleAnim_CreateEffectSlotForCurrentOwner(3, BattleAnim_SlashGrowFade, &gBattleAnimParticleDescriptors[0x2A], 0, 1, 0x10, gBattleAnimCurrentAnchor, 0xD, 2);
    BattleAnim_CreateEffectSlotForCurrentOwner(3, BattleAnim_CallbackSharedOwnerKeyedGrowColorAlphaFade, &gBattleAnimParticleDescriptors[0x41], 0, 1, 0x18, 0, 0xD, 1);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0, 1, 5, BattleAnim_RunSlowFallingHitEffect, &gBattleAnimParticleDescriptors[0x2B], 0, 2, 0xE, 0, 0, 0);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0, 1, 5, BattleAnim_RunSlowFallingHitEffect, &gBattleAnimParticleDescriptors[0x2B], 0, 2, 0xE, 0, 0, 0);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0, 2, 0xF, BattleAnim_RunSlowFallingHitEffect, &gBattleAnimParticleDescriptors[0x2B], 0, 1, 0xE, 0, 0, 0);
}

/**
 * Effect init that spawns the Fire Punch animation. Player sweep (all 165 moves used in battle):
 * only Fire Punch reached this function.
 * Effect start init 56 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used:
 * it ran for exactly Fire Punch.
 */
void BattleAnim_InitializeFirePunchUse(void) {
    func_8213B5D8(0, 1, 0x24, &BattleAnim_FirePunchParticleUpdate, &D_8218E7B0, 0, 1, 0x11, (s32) D_8219A80A, 0, 0);
    func_8213B560(0, &func_82163540, &D_8218E788, 0, 1, 0x10, (s32) D_8219A80A, 0, 0);
}

/**
 * Not reached in play (2026-11-13): no move in the 165-move battle sweep called it (each move used
 * once, from the command menu to the end of its turn).
 * @unverified Name from Stadium 1.
 */
void BattleAnim_InitializeRazorWindHit(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_RunRazorWindHitEffect, &gBattleAnimParticleDescriptors[0x29], 0, 6, 0x10, 0x64, 0, 0);
}

/**
 * Effect init that spawns the Razor Leaf animation. Player sweep (all 165 moves used in battle):
 * only Razor Leaf reached this function.
 * Effect start init 11 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used:
 * it ran for exactly Razor Leaf.
 */
void BattleAnim_InitializeRazorLeafUse(void) {
    func_8213B644(0, 8, 0x26);
}

/**
 * Effect end init 4 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used: it
 * ran for exactly Razor Leaf.
 */
void BattleAnim_InitializeRazorLeafHit(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_RunPetalDanceRazorLeafHitEffect, &gBattleAnimParticleDescriptors[0x29], 0, 8, 0x10, 9, 0, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(0x10, BattleAnim_RunPetalDanceRazorLeafHitEffect, &gBattleAnimParticleDescriptors[0x29], 0, 0xA, 0x10, 9, 0, 0);
    BattleAnim_SpawnGlobalTintColorFadeDetach(0x46, 4, 0x8);
}

/**
 * Effect init that spawns the Petal Dance animation. Player sweep (all 165 moves used in battle):
 * only Petal Dance reached this function.
 * Effect start init 57 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used:
 * it ran for exactly Petal Dance.
 */
void BattleAnim_InitializePetalDanceUse(void) {
    func_8213B644(0, 8, 0x15);
}

/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Petal Dance.
 */
void BattleAnim_InitializePetalDanceHitSequence(void) {
    BattleAnim_AddSpawnDelay(0x10);
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_RunPetalDanceRazorLeafHitEffect, &gBattleAnimParticleDescriptors[0x29], 0, 8, 0x10, 9, 1, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(0x10, BattleAnim_RunPetalDanceRazorLeafHitEffect, &gBattleAnimParticleDescriptors[0x29], 0, 8, 0x10, 9, 1, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(0x20, BattleAnim_RunPetalDanceRazorLeafHitEffect, &gBattleAnimParticleDescriptors[0x29], 0, 8, 0x10, 9, 1, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(0x30, BattleAnim_RunPetalDanceRazorLeafHitEffect, &gBattleAnimParticleDescriptors[0x29], 0, 8, 0x10, 9, 1, 0);
}

/**
 * Moves: Poison Gas (hit), Poison Powder (hit), Sleep Powder (hit), Smog (hit), Spore (hit), Stun Spore (hit)
 * TODO: Human contributor add screenshot
 * Effect end init 18 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used: it
 * ran for exactly Poison Gas, Poison Powder, Sleep Powder, Smog, Spore, Stun Spore.
 */
void BattleAnim_InitializePowderSporeGasMoveHit(void) {
    s32 temp_v0;

    temp_v0 = func_8213646C();
    switch (temp_v0) {                              /* irregular */
    case 0x4D:
        func_8213BC7C(0, 0x64, 0x3B, 0, 0xA0, 4);
        break;
    case 0x4E:
        func_8213BC7C(0, 0x64, 0x17, 0, 0xA0, 4);
        break;
    case 0x4F:
        func_8213BC7C(0, 0x64, 0x2D, 0, 0xA0, 4);
        break;
    case 0x93:
        func_8213BC7C(0, 0x64, 0x17, 0, 0xA0, 4);
        break;
    case 0x7B:
        func_8213BC7C(0, 0x64, 0x3B, 0, 0xA0, 4);
        break;
    case 0x8B:
        func_8213BC7C(0, 0x64, 0x3B, 0, 0xA0, 4);
        break;
    }
    func_8213B560(0, &func_82163D7C, &D_8218E7B8, 0, 7, 0x10, 0x64, 1, 0);
}

/**
 * Effect init that spawns the Sand Attack animation. Player sweep (all 165 moves used in battle):
 * only Sand Attack reached this function.
 * Effect start init 31 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used:
 * it ran for exactly Sand Attack.
 */
void BattleAnim_InitializeSandAttackUse(void) {
    func_8213B5D8(0, 2, 3, &BattleAnim_SandAttackParticleUpdate, &D_8218E7C8, 0, 8, 0x11, (s32) D_8219A80A, 0, 0);
    func_8213B5D8(0, 3, 2, &BattleAnim_RunSmallSand, &D_8218E7B8, 0, 6, 0x11, (s32) D_8219A80A, 0x31, 0);
    func_8213B5D8(0, 4, 2, &BattleAnim_RunLargeSand, &D_8218E7B8, 0, 4, 0x11, (s32) D_8219A80A, 0x31, 0);
}

/**
 * Effect end init 55 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used: it
 * ran for exactly Sand Attack.
 */
void BattleAnim_InitializeSandAttackHit(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_CallbackEndEffect55Descriptor49RiseGravityFade, &D_8218E580[0x49], 0, 5, 0x10, 0x64, 0, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(3, BattleAnim_CallbackEndEffect55Descriptor49RiseGravityFade, &D_8218E580[0x49], 0, 5, 0x10, 0x64, 0, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_PowderCloudScaleMotion, &D_8218E580[0x47], 0, 7, 0x10, 0x64, 1, 0);
}

/**
 * Effect start init 81 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used:
 * it ran for exactly Acid Armor.
 */
void BattleAnim_InitializeAcidArmorUse(void) {
    func_8213C0D8(0, 0xFF, 0x30, 6);
    func_8213C0D8(0x24, 0, 0, 0xFF);
    func_8213BC00(0, 0x21, 0, 0xFF, 8);
    func_8213B464(6);
    func_8213B560(2, &BattleAnim_AcidArmorParticleUpdateA, &D_8218E7D8, 0, 1, 0xA, 0, 0x2F, 0);
    func_8213B5D8(0, 8, 4, &func_821640A0, &D_8218E770, 0, 3, 9, 0, 0x30, 0);
}

/**
 * Moves: Flash (use)
 * TODO: Human contributor add screenshot
 * Effect start init 16 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used:
 * it ran for exactly Flash.
 */
void BattleAnim_InitializeFlashUse(void) {
    func_8213B644(0, 0x20, 6);
    func_8213BC00(8, 8, 0, 0xFF, 0x40);
    func_8213B878(0xC, 5, 0x10, 8);
    func_8213B560(0xC, &func_82162C68, &D_8218E728, 0, 4, 9, 0, 0x18, 0xD);
    func_8213B464(0x21);
    func_8213B720(0, 0, 0x10, 8);
    func_8213B644(0, 0x10, 8);
    func_8213BC00(0, 8, 0xFF, 0, 0x10);
}

/**
 * Effect end init 57 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used: it
 * ran for exactly Flash.
 */
void BattleAnim_InitializeFlashHit(void) {
    func_8213B644(0, 0x20, 6);
    func_8213BC00(8, 8, 0, 0xFF, 0x40);
    func_8213B720(0, 0, 0x10, 8);
    func_8213B464(0x21);
    func_8213B644(0, 0x10, 8);
    func_8213BC00(0, 8, 0xFF, 0, 0x10);
}

/**
 * Effect start init 85 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used:
 * it ran for exactly Rage.
 */
void BattleAnim_InitializeBideRageUse(void) {
    M2C_UNK *sp38;

    func_8213BC7C(0, 1, 0xA, 0, 0xC8, 0x10);
    sp38 = &func_82164AD0;
    func_8213B5D8(6, 4, 0xE, &func_82164AD0, &D_8218E770, 0, 1, 0x11, 7, 0x1A, 0);
    func_8213B5D8(7, 8, 7, &func_82164AD0, &D_8218E770, 0, 1, 0x11, 7, 0x1A, 0);
    func_8213B560(0, &BattleAnim_RunOscillatingFlameUnderneathPokemon, &D_8218E7F8, 0, 0x20, 7, 0, 0, 0);
    func_8215E510();
}

/**
 * Effect start init 114 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used:
 * it ran for exactly Struggle, Thrash.
 */
void BattleAnim_InitializeStruggleThrashUse(void) {
    BattleAnim_SpawnOwnerModelTintPulseDetach(0, 1, 0xA, 0, 0xC8, 4);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(4, 3, 2, BattleAnim_HeavyHitAnimatedRiseFade, &gBattleAnimParticleDescriptors[0x3F], 0, 0x10, 0xA, 0, 0x11, 0);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(6, 4, 0xE, BattleAnim_CallbackSharedAnimatedVerticalFade, &gBattleAnimParticleDescriptors[0x3D], 0, 1, 0x11, 7, 0x33, 7);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(7, 8, 7, BattleAnim_CallbackSharedAnimatedVerticalFade, &gBattleAnimParticleDescriptors[0x3D], 0, 1, 0x11, 7, 0x33, 7);
}

/**
 * Effect start init 115 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used:
 * it ran for exactly Double Edge, Take Down.
 */
void BattleAnim_InitializeDoubleEdgeTakeDownUse(void) {
    BattleAnim_SpawnGlobalTintColorFadeDetach(0, 0x20, 6);
    BattleAnim_InitializeSpeedLines();
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(8, 3, 2, BattleAnim_HeavyHitAnimatedRiseFade, &gBattleAnimParticleDescriptors[0x3F], 0, 0x10, 0xA, 0, 0x11, 0);
}

/**
 * Effect start init 116 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used:
 * it ran for exactly Body Slam.
 */
void BattleAnim_InitializeBodySlamUse(void) {
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(4, 3, 2, BattleAnim_HeavyHitAnimatedRiseFade, &gBattleAnimParticleDescriptors[0x3F], 0, 0x10, 0xA, 0, 0x11, 0);
}

/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Earthquake.
 */
void BattleAnim_InitializeEarthquakeFissureHitSequence(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(4, BattleAnim_CallbackSharedAnimatedVerticalFade, &D_8218E580[0x4A], 0, 8, 0xA, 0, 0x33, 1);
    BattleAnim_CreateEffectSlotForCurrentOwner(5, BattleAnim_CallbackSharedAnimatedVerticalFade, &D_8218E580[0x4A], 0, 8, 0xA, 0, 0x33, 1);
    BattleAnim_CreateEffectSlotForCurrentOwner(6, BattleAnim_CallbackSharedAnimatedVerticalFade, &D_8218E580[0x4A], 0, 8, 0xA, 0, 0x33, 1);
    BattleAnim_CreateEffectSlotForCurrentOwner(7, BattleAnim_CallbackSharedAnimatedVerticalFade, &D_8218E580[0x4A], 0, 8, 0xA, 0, 0x33, 1);
    BattleAnim_CreateEffectSlotForCurrentOwner(8, BattleAnim_RunDefaultHitSpark, &D_8218E580[0x51], 0, 5, 0x11, 9, 0x17, 0xE);
    BattleAnim_CreateEffectSlotForCurrentOwner(0x10, BattleAnim_RunDefaultHitSpark, &D_8218E580[0x51], 0, 5, 0x11, 9, 0x17, 0xE);
}

void func_82168364(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(4, BattleAnim_CallbackSharedAnimatedVerticalFade, &D_8218E580[0x4A], 0, 8, 0xA, 0, 0x33, 1);
    BattleAnim_CreateEffectSlotForCurrentOwner(5, BattleAnim_CallbackSharedAnimatedVerticalFade, &D_8218E580[0x4A], 0, 8, 0xA, 0, 0x33, 1);
    BattleAnim_CreateEffectSlotForCurrentOwner(6, BattleAnim_CallbackSharedAnimatedVerticalFade, &D_8218E580[0x4A], 0, 8, 0xA, 0, 0x33, 1);
    BattleAnim_CreateEffectSlotForCurrentOwner(7, BattleAnim_CallbackSharedAnimatedVerticalFade, &D_8218E580[0x4A], 0, 8, 0xA, 0, 0x33, 1);
    BattleAnim_CreateEffectSlotForCurrentOwner(8, BattleAnim_RunDefaultHitSpark, &D_8218E580[0x51], 0, 5, 0x11, 9, 0x17, 0xE);
    BattleAnim_CreateEffectSlotForCurrentOwner(0x10, BattleAnim_RunDefaultHitSpark, &D_8218E580[0x51], 0, 5, 0x11, 9, 0x17, 0xE);
}

/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Defense Curl, Sharpen.
 */
void BattleAnim_InitializeDefenseCurlSharpenUseSequence(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_CallbackSharedAnimatedVerticalFade, &gBattleAnimParticleDescriptors[0x3D], 0, 8, 0xE, 0, 0x33, 2);
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_CallbackSharedAnimatedVerticalFade, &gBattleAnimParticleDescriptors[0x3D], 0, 2, 0xE, 0, 0x33, 2);
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_CallbackSharedAnimatedVerticalFade, &gBattleAnimParticleDescriptors[0x3D], 0, 2, 0xE, 0, 0x33, 2);
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_CallbackSharedAnimatedVerticalFade, &gBattleAnimParticleDescriptors[0x3D], 0, 2, 0xE, 0, 0x33, 2);
    BattleAnim_CreateEffectSlotForCurrentOwner(4, BattleAnim_CallbackSharedAnimatedVerticalFade, &gBattleAnimParticleDescriptors[0x3D], 0, 8, 0xE, 0, 0x33, 2);
    BattleAnim_CreateEffectSlotForCurrentOwner(8, BattleAnim_CallbackSharedAnimatedVerticalFade, &gBattleAnimParticleDescriptors[0x3D], 0, 8, 0xE, 0, 0x33, 2);
}

/**
 * Effect start init 89 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used:
 * it ran for exactly Substitute, Transform.
 */
void BattleAnim_InitializeSubstituteTransformUse(void) {
    BattleAnim_SpawnOwnerModelTintRampDetach(4, 0x8, 0, 0xFF, 0x40);
    BattleAnim_SpawnOwnerModelTintRampDetach(9, 0x8, 0xFF, 0, 0x40);
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_CallbackSharedAnimatedVerticalFade, &gBattleAnimParticleDescriptors[0x3D], 0, 8, 0xE, 0, 0x33, 2);
    BattleAnim_CreateEffectSlotForCurrentOwner(1, BattleAnim_CallbackSharedAnimatedVerticalFade, &gBattleAnimParticleDescriptors[0x3D], 0, 8, 0xE, 0, 0x33, 2);
    BattleAnim_CreateEffectSlotForCurrentOwner(2, BattleAnim_CallbackSharedAnimatedVerticalFade, &gBattleAnimParticleDescriptors[0x3D], 0, 8, 0xE, 0, 0x33, 2);
    BattleAnim_CreateEffectSlotForCurrentOwner(4, BattleAnim_CallbackSharedAnimatedVerticalFade, &gBattleAnimParticleDescriptors[0x3D], 0, 8, 0xE, 0, 0x33, 2);
    BattleAnim_CreateEffectSlotForCurrentOwner(4, BattleAnim_CallbackSharedAnimatedVerticalFade, &gBattleAnimParticleDescriptors[0x3D], 0, 8, 0xE, 0, 0x33, 2);
    BattleAnim_CreateEffectSlotForCurrentOwner(8, BattleAnim_CallbackSharedAnimatedVerticalFade, &gBattleAnimParticleDescriptors[0x3D], 0, 8, 0xE, 0, 0x33, 2);
}

/**
 * Moves: Conversion (use), Mimic (use), Recover (use), Sky Attack (use), Solar Beam (use)
 * TODO: Human contributor add screenshot
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Solar Beam, Mimic, Metronome, Sky Attack, Conversion.
 */
void BattleAnim_InitializeQiCharge(s32 arg0) {
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0, 1, 4, BattleAnim_SolarbeamMimicBurstEmitter, &gDefaultParticleDescriptor, 0, 1, 2, 0, arg0, 0);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(8, 1, 4, BattleAnim_SolarbeamMimicBurstEmitter, &gDefaultParticleDescriptor, 0, 1, 2, 0, arg0, 0);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0x10, 1, 8, BattleAnim_SolarbeamMimicBurstEmitter, &gDefaultParticleDescriptor, 0, 1, 2, 0, arg0, 0);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0x18, 1, 8, BattleAnim_SolarbeamMimicBurstEmitter, &gDefaultParticleDescriptor, 0, 1, 2, 0, arg0, 0);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0x20, 1, 8, BattleAnim_SolarbeamMimicBurstEmitter, &gDefaultParticleDescriptor, 0, 1, 2, 0, arg0, 0);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0x30, 1, 8, BattleAnim_SolarbeamMimicBurstEmitter, &gDefaultParticleDescriptor, 0, 1, 2, 0, arg0, 0);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0x3C, 1, 8, BattleAnim_SolarbeamMimicBurstEmitter, &gDefaultParticleDescriptor, 0, 1, 2, 0, arg0, 0);
}

/**
 * Moves: Conversion (use), Mimic (use)
 * TODO: Human contributor add screenshot
 * Effect start init 29, start init 60 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all
 * 165 moves used: it ran for exactly Conversion, Mimic.
 */
void BattleAnim_InitializeMimicConversionUse(void) {
    func_8213B644(0, 8, 6);
    func_82168844(0xE);
    func_8213B644(0x64, 0x20, 8);
}

/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Solar Beam.
 */
void BattleAnim_InitializeSolarBeamUseSequence(void) {
    func_8213B644(0, 8, 6);
    func_82168844(0x17);
    func_8213B560(0xA, &func_821655C0, &D_8218E768, 0x1A, 1, 5, 0, 0x33, 0);
    func_8213B644(0x64, 0x20, 8);
}

/**
 * Effect init that spawns the Growth animation. Player sweep (all 165 moves used in battle): only
 * Growth reached this function.
 * Effect start init 109 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used:
 * it ran for exactly Growth.
 */
void BattleAnim_InitializeGrowthUse(void) {
    func_8213BC7C(0xA, 1, 8, 0, 0xFF, 0x20);
}

/**
 * Seen in play (2026-11-13) ran when 1P used Recover with its HP set to 5 (at full HP the move
 * fails and the sweep never saw the animation).
 * @unverified Name from Stadium 1.
 */
void BattleAnim_InitializeRecoverUse(void) {
    BattleAnim_SpawnGlobalTintColorFadeDetach(0, 8, 6);
    BattleAnim_InitializeQiCharge(0xC);
    BattleAnim_SpawnRainbowHueChange(4, 0x32, 0x20, 0xA0);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(4, 8, 5, BattleAnim_RunSparkleHit, &gBattleAnimParticleDescriptors[0x42], 0, 8, 9, 0, 0xC, 9);
}

/**
 * Effect start init 30 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used:
 * it ran for exactly Harden.
 */
void BattleAnim_InitializeHardenUse(void) {
    func_8213BC00(0, 8, 0xFF, 0, 0x20);
    func_8213B5D8(4, 2, 2, &func_821624FC, &D_8218E798, 0, 8, 9, 0, 0x17, 1);
}
