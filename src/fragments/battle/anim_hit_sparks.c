/* Fixed-layout split; original translation-unit boundaries remain unconfirmed. */
#include "battle.h"

// Declared here instead of in a header: the callers of these disagree on their types.
M2C_UNK func_8213B5D8(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK *, M2C_UNK *, s32, s32, s32, s32, s32, s32);
extern M2C_UNK BattleAnim_RunOscillatingFlameUnderneathPokemon;
extern M2C_UNK D_8218E7B8;
s32 func_82107CF0(s32);
void BattleAnim_PowderCloudScaleMotion(Particle* arg0);
void BattleAnim_CallbackSharedAnimatedVerticalFade(Particle* arg0);

/**
 * Particle callback for the growing spark: waits its delay, shows for 12 frames, fades out
 * and detaches. While visible it grows toward its scale target and fades env green and blue.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal or j,
 * no pointer word, no lui/addiu pair in any fragment), so play cannot reach it.
 * @unverified Name from Stadium 1.
 */
void BattleAnim_CallbackUnusedGrowingSparkVariant(Particle* arg0) {
    switch (arg0->lifecycle) {
        case 1:
            BattleAnim_SetupUnusedGrowingSparkVariant(arg0);
            break;

        case 2:
            if (Particle_DecrementParam0ToZeroThenAdvance(arg0) != 0) {
                Particle_EnableRendering(arg0);
            }
            break;

        case 3:
            Particle_TickDelayAndAdvanceLifecycle(arg0, 12);
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
 * Effect script for a strong contact hit: one default hit spark (descriptor 0x34, variant 7), then
 * after 2 frames 8 smoke puffs (descriptor 0x3D).
 * Moves: Bone Club (hit), Dizzy Punch (hit), Double Slap (hit), Drill Peck (hit), Headbutt (hit),
 * Pay Day (hit) TODO: Human contributor add screenshot Effect end init 14
 * (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used: it ran for exactly Bone
 * Club, Dizzy Punch, Double Slap, Drill Peck, Headbutt, Pay Day.
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
 * Effect script for Low Kick's hit: one default hit spark, then 8 smoke puffs after 2 frames.
 * Effect end init 36 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used: it
 * ran for exactly Low Kick.
 */
void BattleAnim_InitializeLowKickHit(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_RunDefaultHitSpark, &gBattleAnimParticleDescriptors[0x34], 0, 1, 0x11, 9, 0, 8);
    BattleAnim_CreateEffectSlotForCurrentOwner(2, BattleAnim_RunPhysicalHitPurpleSmoke, &gBattleAnimParticleDescriptors[0x3D], 0, 8, 0x11, 9, 2, 0);
}

/**
 * Effect script for a default contact hit: one default hit spark (descriptor 0x34, variant 9),
 * then after 2 frames 8 smoke puffs.
 * Moves: Bide (hit), Bonemerang (hit), Counter (hit), Hi Jump Kick (hit), Jump Kick (hit), Karate
 * Chop (hit), Pound (hit), Quick Attack (hit), Rage (hit), Rolling Kick (hit), Struggle (hit),
 * Tackle (hit), Take Down (hit) TODO: Human contributor add screenshot Effect end init 44
 * (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used: it ran for exactly
 * Bonemerang, Hi Jump Kick, Jump Kick, Karate Chop, Pound, Quick Attack, Rage, Rolling Kick,
 * Struggle, Tackle, Take Down.
 */
void BattleAnim_InitializeDefaultLimbForMove(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_RunDefaultHitSpark, &gBattleAnimParticleDescriptors[0x34], 0, 1, 0x11, 9, 0, 6);
    BattleAnim_CreateEffectSlotForCurrentOwner(2, BattleAnim_RunPhysicalHitPurpleSmoke, &gBattleAnimParticleDescriptors[0x3D], 0, 8, 0x11, 9, 0, 0);
}

/**
 * Effect script for a special contact hit: like the default limb hit but with a different spark
 * color, then 8 smoke puffs after 2 frames.
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
 * Effect script for a pointy-move hit: one pointy-move hit spark (descriptor 0x34), which emits
 * its own spark children.
 * Moves: Horn Attack (hit), Horn Drill (hit), Peck (hit), Pin Missile (hit), Spike Cannon (hit)
 * TODO: Human contributor add screenshot
 * Effect end init 37 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used: it
 * ran for exactly Horn Attack, Peck, Pin Missile, Spike Cannon.
 */
void BattleAnim_InitializePointyMoveHitSparks(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_RunPointyMoveHitSpark, &gBattleAnimParticleDescriptors[0x34], 0, 1, 0x11, 9, 3, 0);
}

/**
 * Effect script for the Poison Sting and Twineedle hit: one pointy-move hit spark (variant 4).
 * Effect end init 38 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used: it
 * ran for exactly Poison Sting, Twineedle.
 */
void BattleAnim_InitializePoisonStingTwineedleHit(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_RunPointyMoveHitSpark, &gBattleAnimParticleDescriptors[0x34], 0, 1, 0x11, 9, 4, 0);
}

/**
 * Effect script for the Fury Attack and Gust hit: 7 default hit sparks.
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

    BattleAnim_CreateRepeatEffectSlotForCurrentOwner(0, 8, 6, BattleAnim_RunSparkleHit, &D_8218E798, 0, 8, 0x11, temp_s1, 0x18, 2);
    BattleAnim_CreateRepeatEffectSlotForCurrentOwner(1, 8, 6, BattleAnim_RunSparkleHit, &D_8218E798, 0, 8, 0x11, temp_s1, 0x18, 2);
    BattleAnim_CreateRepeatEffectSlotForCurrentOwner(2, 8, 6, BattleAnim_RunSparkleHit, &D_8218E798, 0, 8, 0x11, temp_s1, 0x18, 2);
    BattleAnim_CreateRepeatEffectSlotForCurrentOwner(4, 8, 6, BattleAnim_RunSparkleHit, &D_8218E798, 0, 8, 0x11, temp_s1, 0x18, 2);
    BattleAnim_CreateRepeatEffectSlotForCurrentOwner(0, 6, 12, BattleAnim_CallbackEnd67Desc3DAnimatedGravityFade, &D_8218E7D0, 0, 2, 0x11, temp_s1, 1, 0);
    BattleAnim_CreateRepeatEffectSlotForCurrentOwner(1, 6, 10, BattleAnim_CallbackEnd67Desc3DAnimatedGravityFade, &D_8218E7D0, 0, 2, 0x11, temp_s1, 1, 0);
}

/**
 * Effect script for Ice Punch's hit: a hit spark, two bursts of 8 falling ice bits at frames 2 and
 * 3, sparkles at frames 4, 8 and 12, and an owner tint ramp.
 * Effect end init 42 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used: it
 * ran for exactly Ice Punch.
 */
void BattleAnim_InitializeIcePunchHit(void) {
    UNUSED s32 pad; // FAKE: stack padding

    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_RunDefaultHitSpark, &gBattleAnimParticleDescriptors[0x34], 0, 1, 0x11, 9, 3, 5);
    BattleAnim_CreateEffectSlotForCurrentOwner(2, BattleAnim_CallbackEnd67Desc3DAnimatedGravityFade, &gBattleAnimParticleDescriptors[0x3D], 0, 8, 0x10, 0x64, 0, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(3, BattleAnim_CallbackEnd67Desc3DAnimatedGravityFade, &gBattleAnimParticleDescriptors[0x3D], 0, 8, 0x10, 0x64, 0, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(4, BattleAnim_RunSparkleHit, &gBattleAnimParticleDescriptors[0x42], 0, 8, 9, 0, 0x18, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(8, BattleAnim_RunSparkleHit, &gBattleAnimParticleDescriptors[0x42], 0, 4, 9, 0, 0x18, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(12, BattleAnim_RunSparkleHit, &gBattleAnimParticleDescriptors[0x42], 0, 4, 9, 0, 0x18, 0);
    BattleAnim_SpawnOwnerTintRampDetach(0, 0x33, 0xE0, 0, 0x20);
}

/**
 * Effect script for Thunder Punch's hit: a hit spark, the Thunder Punch sparks at frame 4, rising
 * scatter particles, a full-screen flash and an owner tint ramp.
 * Effect end init 43 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used: it
 * ran for exactly Thunder Punch.
 */
void BattleAnim_InitializeThunderPunchHit(void) {
    func_8213B560(0, &func_82162C68, &D_8218E728, 0, 1, 0x11, 9, 3, 5);
    func_8213B560(4, &func_82162938, &D_8218E788, 0, 1, 0x10, 0x64, 0, 0);
    func_8213B5D8(0, 4, 5, &BattleAnim_CallbackStart18And73Desc11ScatterRise, &D_8218E610, 8, 4, 2, 0, 0, 0);
    func_8213B794(0, 0, 0x40, 8, 0xC8);
    func_8213BC00(0, 0x17, 0xE1, 0, 0x40);
}

/**
 * Queues one descriptor 0x34 color-fade particle on the current owner at once. No caller
 * was found.
 * @unverified Name from Stadium 1.
 */
void BattleAnim_OrphanDescriptor34Emitter(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_CallbackOrphanDesc34ColorFadeDetach, &gBattleAnimParticleDescriptors[0x34], 0, 5, 0x11, gBattleAnimCurrentAnchor, 0, 0);
}

/**
 * Effect script for Submission's use: rising particles 3 at a time every 2 frames, at frame 0 and
 * again at frame 40.
 * Effect start init 108 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used:
 * it ran for exactly Submission.
 */
void BattleAnim_InitializeSubmissionUse(void) {
    BattleAnim_CreateRepeatEffectSlotForCurrentOwner(0, 3, 2, BattleAnim_HeavyHitAnimatedRiseFade, &gBattleAnimParticleDescriptors[0x3F], 0, 0x10, 0xA, 0, 0x11, 0);
    BattleAnim_CreateRepeatEffectSlotForCurrentOwner(40, 3, 2, BattleAnim_HeavyHitAnimatedRiseFade, &gBattleAnimParticleDescriptors[0x3F], 0, 0x10, 0xA, 0, 0x11, 0);
}

/**
 * Effect script for Stomp's hit: a heavy-hit spark, a ground ring spark, and rising particles 3 at
 * a time every 2 frames from frame 4.
 * Effect end init 39 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used: it
 * ran for exactly Stomp.
 */
void BattleAnim_InitializeStompHit(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_RunHeavyHitSparksAndSmoke, &gBattleAnimParticleDescriptors[0x34], 0, 1, 0x11, 9, 0, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_RunGroundedCircularHitSpark, &gBattleAnimParticleDescriptors[0x36], 0, 1, 0xA, 0, 0, 0);
    BattleAnim_CreateRepeatEffectSlotForCurrentOwner(4, 3, 2, BattleAnim_HeavyHitAnimatedRiseFade, &gBattleAnimParticleDescriptors[0x3F], 0, 0x10, 0xA, 0, 0x11, 0);
}

/**
 * Effect script for a grounded hit: 5 heavy-hit sparks, a ground ring spark after 8 frames, and
 * rising particles 3 at a time every 2 frames from frame 12.
 * Moves: Body Slam (hit), Crabhammer (hit), Double-Edge (hit), Fly (hit), Seismic Toss (hit), Slam
 * (hit), Thrash (hit) TODO: Human contributor add screenshot Effect end init 45
 * (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used: it ran for exactly Body
 * Slam, Crabhammer, Double Edge, Seismic Toss, Slam, Thrash.
 */
void BattleAnim_InitializeGroundedCircularHitSpark(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_RunHeavyHitSparksAndSmoke, &gBattleAnimParticleDescriptors[0x34], 0, 5, 0x11, 0x64, 9, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(8, BattleAnim_RunGroundedCircularHitSpark, &gBattleAnimParticleDescriptors[0x36], 0, 1, 0xA, 0, 0, 0);
    BattleAnim_CreateRepeatEffectSlotForCurrentOwner(12, 3, 2, BattleAnim_HeavyHitAnimatedRiseFade, &gBattleAnimParticleDescriptors[0x3F], 0, 0x10, 0xA, 0, 0x11, 0);
}

/**
 * Effect script for Submission's hit: 5 heavy-hit sparks, a ground ring spark at frame 8, and
 * rising particles 3 at a time every 2 frames from frame 12.
 * Effect end init 46 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used: it
 * ran for exactly Submission.
 */
void BattleAnim_InitializeSubmissionHit(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_RunHeavyHitSparksAndSmoke, &gBattleAnimParticleDescriptors[0x34], 0, 5, 0xA, 0, 0xA, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(8, BattleAnim_RunGroundedCircularHitSpark, &gBattleAnimParticleDescriptors[0x36], 0, 1, 0xA, 0, 0, 0);
    BattleAnim_CreateRepeatEffectSlotForCurrentOwner(12, 3, 2, BattleAnim_HeavyHitAnimatedRiseFade, &gBattleAnimParticleDescriptors[0x3F], 0, 0x10, 0xA, 0, 0x11, 0);
}

/**
 * Effect script for the biting moves' hit: 7 heavy-hit sparks (descriptor 0x34).
 * Moves: Bite (hit), Clamp (hit), Guillotine (hit), Hyper Fang (hit), Super Fang (hit), Vice Grip
 * (hit) TODO: Human contributor add screenshot
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
 * Effect script for Swift's hit: four star bursts at frames 0, 3, 5 and 8, and sparkles at frames
 * 12, 18 and 32.
 * Effect end init 52 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used: it
 * ran for exactly Swift.
 */
void BattleAnim_InitializeSwiftHit(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(12, BattleAnim_RunSparkleHit, &gBattleAnimParticleDescriptors[0x42], 0, 8, 9, 0, 0x17, 1);
    BattleAnim_CreateEffectSlotForCurrentOwner(18, BattleAnim_RunSparkleHit, &gBattleAnimParticleDescriptors[0x42], 0, 0xA, 9, 0, 0x17, 1);
    BattleAnim_CreateEffectSlotForCurrentOwner(0x20, BattleAnim_RunSparkleHit, &gBattleAnimParticleDescriptors[0x42], 0, 5, 9, 0, 0x17, 1);
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_RunSwiftHitEffect2, &gDefaultParticleDescriptor, 0, 2, 9, 0, 0, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(3, BattleAnim_RunSwiftHitEffect2, &gDefaultParticleDescriptor, 0, 2, 9, 0, 0, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(5, BattleAnim_RunSwiftHitEffect2, &gDefaultParticleDescriptor, 0, 2, 9, 0, 0, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(8, BattleAnim_RunSwiftHitEffect2, &gDefaultParticleDescriptor, 0, 2, 9, 0, 0, 0);
}

/**
 * Starts effect 137: queues two descriptor 0x3F rising, fading particles on the current
 * owner, three frames apart.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (2 of the moves).
 * @unverified Name from Stadium 1.
 */
void BattleAnim_StartEffect137Descriptor3FRisingFade(void) {
    BattleAnim_CreateRepeatEffectSlotForCurrentOwner(0, 3, 2, BattleAnim_HeavyHitAnimatedRiseFade, &gBattleAnimParticleDescriptors[0x3F], 0, 0x10, 0xA, 0, 0x11, 0);
}

/**
 * Queues the small and large sand particles on the current owner.
 * @unverified Name guessed from the code.
 */
void BattleAnim_StartEffect136Sand(void) {
    func_8213B5D8(0, 3, 2, &BattleAnim_RunSmallSand, &D_8218E7D0, 0, 6, 0x11, (s32) D_8219A80A, 0x11, 0);
    func_8213B5D8(0, 4, 2, &BattleAnim_RunLargeSand, &D_8218E7D0, 0, 4, 0x11, (s32) D_8219A80A, 0x11, 0);
}

/**
 * Effect script for the Scratch and Slash use: a Scyther runs the Cut animation instead; otherwise
 * three slash streaks at frames 0, 4 and 10, the slash flash at frame 30 and a full-screen flash
 * at frame 35.
 * Effect start init 13 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used:
 * it ran for exactly Fury Swipes, Scratch, Slash.
 */
void BattleAnim_InitializeScratchSlashUse(void) {
    void (*sp30)(s8*);

    if (func_82107CF0(D_8219A814) == SCYTHER) {
        BattleAnim_InitializeCutUse();
        return;
    }
    sp30 = BattleAnim_CallbackSharedDescriptor29ScaleAnimFade;
    func_8213B560(0, (M2C_UNK*)sp30, &D_8218E6D0, 0, 3, 0x10, (s32) D_8219A80A, 0xB, 0);
    func_8213B560(4, (M2C_UNK*)sp30, &D_8218E6D0, 0, 3, 0x10, (s32) D_8219A80A, 0xB, 1);
    func_8213B560(10, (M2C_UNK*)sp30, &D_8218E6D0, 0, 3, 0x10, (s32) D_8219A80A, 0xB, 2);
    func_8213B560(30, &BattleAnim_RunSlashingMoveFullScreenFlash, &D_8218E6C8, 0, 1, 0x18, 0, 0xF, 0);
    func_8213B720(35, 0, 0x10, 0x12);
}

/**
 * Effect init for the end (impact) of the Fury Swipes and Scratch and Slash animation.
 * Effect end init 5 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used: it
 * ran for exactly Fury Swipes, Scratch, Slash.
 */
void BattleAnim_InitializeScratchSlashHit(void) {
    UNUSED s32 pad; // FAKE: stack padding

    if (BattleAnim_GetOwnerSpecies(gBattleAnimSecondaryOwner) == SCYTHER) {
        BattleAnim_InitializeCutCrabhammerHit();
        return;
    }

    BattleAnim_SpawnDesc25AlphaHoldFadeOut(0, 2, 0x10, 0x12, 0xFF);
    BattleAnim_CreateEffectSlotForCurrentOwner(3, BattleAnim_SlashGrowFade, &gBattleAnimParticleDescriptors[0x2A], 0, 1, 0x10, gBattleAnimCurrentAnchor, 0x10, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(3, BattleAnim_SlashGrowFade, &gBattleAnimParticleDescriptors[0x2A], 0, 1, 0x10, gBattleAnimCurrentAnchor, 0x10, 1);
    BattleAnim_CreateEffectSlotForCurrentOwner(3, BattleAnim_SlashGrowFade, &gBattleAnimParticleDescriptors[0x2A], 0, 1, 0x10, gBattleAnimCurrentAnchor, 0x10, 2);
    BattleAnim_CreateEffectSlotForCurrentOwner(3, BattleAnim_CallbackSharedOwnerKeyedGrowColorAlphaFade, &gBattleAnimParticleDescriptors[0x28], 0, 1, 0x18, 0, 0xF, 0);
}

/**
 * Effect script for Cut: three slash streaks at frames 0, 4 and 10, a colored grow-fade at frame
 * 30, and a full-screen flash at frame 35.
 * Moves: Cut (use), Scratch (use), Slash (use)
 * TODO: Human contributor add screenshot
 * Seen in play (2026-11-12): in the per-move sweep it ran only for Cut, not for Slash or Scratch,
 * so the old name BattleAnim_InitializeCutSlashScratchEffect was too broad.
 */
void BattleAnim_InitializeCutEffect(void) {
    UNUSED s32 pad; // FAKE: stack padding

    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_CallbackSharedDescriptor29ScaleAnimFade, &gBattleAnimParticleDescriptors[0x29], 0, 1, 0x10, gBattleAnimCurrentAnchor, 0xB, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(4, BattleAnim_CallbackSharedDescriptor29ScaleAnimFade, &gBattleAnimParticleDescriptors[0x29], 0, 1, 0x10, gBattleAnimCurrentAnchor, 0xB, 1);
    BattleAnim_CreateEffectSlotForCurrentOwner(10, BattleAnim_CallbackSharedDescriptor29ScaleAnimFade, &gBattleAnimParticleDescriptors[0x29], 0, 1, 0x10, gBattleAnimCurrentAnchor, 0xB, 2);
    BattleAnim_CreateEffectSlotForCurrentOwner(30, BattleAnim_CallbackSharedOwnerKeyedGrowColorFade, &gBattleAnimParticleDescriptors[0x41], 0, 1, 0x18, 0, 0xF, 0);
    BattleAnim_SpawnDesc25AlphaHoldFadeOutFullAlpha(35, 0, 0x10, 0x12);
}

/**
 * Effect init for the end (impact) of the Crabhammer and Cut animation.
 * Effect end init 30 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used: it
 * ran for exactly Crabhammer, Cut.
 */
void BattleAnim_InitializeCutCrabhammerHit(void) {
    func_8213B794(0, 2, 0x10, 0x12, 0xFF);
    func_8213B560(3, &BattleAnim_SlashGrowFade, &D_8218E6D8, 0, 1, 0x10, (s32) D_8219A80A, 0x10, 2);
    func_8213B560(3, &BattleAnim_RunSlashMoveWhiteFlashOverlay, &D_8218E790, 0, 1, 0x18, 0, 0xF, 0);
}

/**
 * Effect script for Vine Whip's use: three whip streaks at frames 0, 4 and 10, a grow-fade at
 * frame 30 and a full-screen flash at frame 35.
 * Effect start init 117 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used:
 * it ran for exactly Vine Whip.
 */
void BattleAnim_InitializeVineWhipUse(void) {
    UNUSED s32 pad; // FAKE: stack padding

    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_CallbackSharedDescriptor29ScaleAnimFade, &gBattleAnimParticleDescriptors[0x29], 0, 1, 0x10, gBattleAnimCurrentAnchor, 0xD, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(4, BattleAnim_CallbackSharedDescriptor29ScaleAnimFade, &gBattleAnimParticleDescriptors[0x29], 0, 1, 0x10, gBattleAnimCurrentAnchor, 0xD, 1);
    BattleAnim_CreateEffectSlotForCurrentOwner(10, BattleAnim_CallbackSharedDescriptor29ScaleAnimFade, &gBattleAnimParticleDescriptors[0x29], 0, 1, 0x10, gBattleAnimCurrentAnchor, 0xD, 2);
    BattleAnim_CreateEffectSlotForCurrentOwner(30, BattleAnim_CallbackSharedOwnerKeyedGrowColorFade, &gBattleAnimParticleDescriptors[0x41], 0, 1, 0x18, 0, 0xD, 1);
    BattleAnim_SpawnDesc25AlphaHoldFadeOutFullAlpha(35, 0, 0x10, 0x27);
}

/**
 * Effect script for Vine Whip's hit: a full-screen flash, a slash grow-fade and a colored fade at
 * frame 3, and three streams of slowly falling leaves.
 * Effect end init 85 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used: it
 * ran for exactly Vine Whip.
 */
void BattleAnim_InitializeVineWhipHit(void) {
    UNUSED s32 pad; // FAKE: stack padding

    BattleAnim_SpawnDesc25AlphaHoldFadeOut(0, 2, 0x10, 0x27, 0xFF);
    BattleAnim_CreateEffectSlotForCurrentOwner(3, BattleAnim_SlashGrowFade, &gBattleAnimParticleDescriptors[0x2A], 0, 1, 0x10, gBattleAnimCurrentAnchor, 0xD, 2);
    BattleAnim_CreateEffectSlotForCurrentOwner(3, BattleAnim_CallbackSharedOwnerKeyedGrowColorAlphaFade, &gBattleAnimParticleDescriptors[0x41], 0, 1, 0x18, 0, 0xD, 1);
    BattleAnim_CreateRepeatEffectSlotForCurrentOwner(0, 1, 5, BattleAnim_RunSlowFallingHitEffect, &gBattleAnimParticleDescriptors[0x2B], 0, 2, 0xE, 0, 0, 0);
    BattleAnim_CreateRepeatEffectSlotForCurrentOwner(0, 1, 5, BattleAnim_RunSlowFallingHitEffect, &gBattleAnimParticleDescriptors[0x2B], 0, 2, 0xE, 0, 0, 0);
    BattleAnim_CreateRepeatEffectSlotForCurrentOwner(0, 2, 0xF, BattleAnim_RunSlowFallingHitEffect, &gBattleAnimParticleDescriptors[0x2B], 0, 1, 0xE, 0, 0, 0);
}

/**
 * Effect init that spawns the Fire Punch animation. Player sweep (all 165 moves used in battle):
 * only Fire Punch reached this function.
 * Effect start init 56 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used:
 * it ran for exactly Fire Punch.
 */
void BattleAnim_InitializeFirePunchUse(void) {
    func_8213B5D8(0, 1, 36, &BattleAnim_FirePunchParticleUpdate, &D_8218E7B0, 0, 1, 0x11, (s32) D_8219A80A, 0, 0);
    func_8213B560(0, &func_82163540, &D_8218E788, 0, 1, 0x10, (s32) D_8219A80A, 0, 0);
}

/**
 * Effect script for Razor Wind's hit: 6 Razor Wind hit particles (descriptor 0x29).
 * Seen in play (2026-11-13) (Free Battle, 1P Onix's Razor Wind with its accuracy raised so it
 * lands): called through the effect table on the second (attacking) turn, and
 * Pinsir dropped from 75 to 68 HP. In the earlier sweep the second turn missed and this did not
 * run.
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
 * Effect script for Razor Leaf's hit: 8 leaves at frame 0, 10 more at frame 16, and a global tint
 * fade at frame 70.
 * Effect end init 4 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used: it
 * ran for exactly Razor Leaf.
 */
void BattleAnim_InitializeRazorLeafHit(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_RunPetalDanceRazorLeafHitEffect, &gBattleAnimParticleDescriptors[0x29], 0, 8, 0x10, 9, 0, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(0x10, BattleAnim_RunPetalDanceRazorLeafHitEffect, &gBattleAnimParticleDescriptors[0x29], 0, 0xA, 0x10, 9, 0, 0);
    BattleAnim_SpawnGlobalTintColorFadeDetach(70, 4, 0x8);
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
 * Effect script for Petal Dance's hit: adds 16 frames of spawn delay, then four bursts of 8 petals
 * at frames 0, 16, 32 and 48.
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Petal Dance.
 */
void BattleAnim_InitializePetalDanceHitSequence(void) {
    BattleAnim_AddSpawnDelay(0x10);
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_RunPetalDanceRazorLeafHitEffect, &gBattleAnimParticleDescriptors[0x29], 0, 8, 0x10, 9, 1, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(0x10, BattleAnim_RunPetalDanceRazorLeafHitEffect, &gBattleAnimParticleDescriptors[0x29], 0, 8, 0x10, 9, 1, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(0x20, BattleAnim_RunPetalDanceRazorLeafHitEffect, &gBattleAnimParticleDescriptors[0x29], 0, 8, 0x10, 9, 1, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(48, BattleAnim_RunPetalDanceRazorLeafHitEffect, &gBattleAnimParticleDescriptors[0x29], 0, 8, 0x10, 9, 1, 0);
}

/**
 * Effect script for the powder, spore and gas moves' hit: a user hue pulse colored by move (Poison
 * Powder, Smog and Poison Gas share one color, Stun Spore and Spore another, Sleep Powder its
 * own), then 7 powder cloud particles.
 * Moves: Poison Gas (hit), Poison Powder (hit), Sleep Powder (hit), Smog (hit), Spore (hit), Stun
 * Spore (hit) TODO: Human contributor add screenshot Effect end init 18
 * (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used: it ran for exactly
 * Poison Gas, Poison Powder, Sleep Powder, Smog, Spore, Stun Spore.
 */
void BattleAnim_InitializePowderSporeGasMoveHit(void) {
    s32 temp_v0;

    temp_v0 = func_8213646C();
    switch (temp_v0) {                              /* irregular */
    case POISONPOWDER:
        func_8213BC7C(0, 0x64, 0x3B, 0, 0xA0, 4);
        break;
    case STUN_SPORE:
        func_8213BC7C(0, 0x64, 0x17, 0, 0xA0, 4);
        break;
    case SLEEP_POWDER:
        func_8213BC7C(0, 0x64, 0x2D, 0, 0xA0, 4);
        break;
    case SPORE:
        func_8213BC7C(0, 0x64, 0x17, 0, 0xA0, 4);
        break;
    case SMOG:
        func_8213BC7C(0, 0x64, 0x3B, 0, 0xA0, 4);
        break;
    case POISON_GAS:
        func_8213BC7C(0, 0x64, 0x3B, 0, 0xA0, 4);
        break;
    }
    func_8213B560(0, &BattleAnim_PowderCloudScaleMotion, &D_8218E7B8, 0, 7, 0x10, 0x64, 1, 0);
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
 * Effect script for Sand-Attack's hit: two bursts of 5 rising sand grains at frames 0 and 3, and 7
 * sand cloud particles.
 * Effect end init 55 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used: it
 * ran for exactly Sand Attack.
 */
void BattleAnim_InitializeSandAttackHit(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_CallbackEndEffect55Descriptor49RiseGravityFade, &D_8218E580[0x49], 0, 5, 0x10, 0x64, 0, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(3, BattleAnim_CallbackEndEffect55Descriptor49RiseGravityFade, &D_8218E580[0x49], 0, 5, 0x10, 0x64, 0, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_PowderCloudScaleMotion, &D_8218E580[0x47], 0, 7, 0x10, 0x64, 1, 0);
}

/**
 * Effect script for Acid Armor's use: the owner fades out and back in at frame 36, an owner tint
 * ramp, 6 frames of spawn delay, the Acid Armor particle, and 8 bubbles every 4 frames.
 * Effect start init 81 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used:
 * it ran for exactly Acid Armor.
 */
void BattleAnim_InitializeAcidArmorUse(void) {
    func_8213C0D8(0, 0xFF, 0x30, 6);
    func_8213C0D8(36, 0, 0, 0xFF);
    func_8213BC00(0, 0x21, 0, 0xFF, 8);
    func_8213B464(6);
    func_8213B560(2, &BattleAnim_AcidArmorParticleUpdateA, &D_8218E7D8, 0, 1, 0xA, 0, 0x2F, 0);
    func_8213B5D8(0, 8, 4, &func_821640A0, &D_8218E770, 0, 3, 9, 0, 0x30, 0);
}

/**
 * Effect script for Flash's use: a global tint fade, owner tint ramps, a fade-in overlay at frame
 * 12, hit sparks at frame 12, then 33 more frames of spawn delay before a full-screen flash, a
 * second tint fade and a last tint ramp.
 * Moves: Flash (use)
 * TODO: Human contributor add screenshot
 * Effect start init 16 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used:
 * it ran for exactly Flash.
 */
void BattleAnim_InitializeFlashUse(void) {
    func_8213B644(0, 0x20, 6);
    func_8213BC00(8, 8, 0, 0xFF, 0x40);
    func_8213B878(12, 5, 0x10, 8);
    func_8213B560(12, &func_82162C68, &D_8218E728, 0, 4, 9, 0, 0x18, 0xD);
    func_8213B464(33);
    func_8213B720(0, 0, 0x10, 8);
    func_8213B644(0, 0x10, 8);
    func_8213BC00(0, 8, 0xFF, 0, 0x10);
}

/**
 * Effect script for Flash's hit: a global tint fade, an owner tint ramp at frame 8, a full-screen
 * flash, then 33 frames of spawn delay before a second tint fade and a last tint ramp.
 * Effect end init 57 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used: it
 * ran for exactly Flash.
 */
void BattleAnim_InitializeFlashHit(void) {
    func_8213B644(0, 0x20, 6);
    func_8213BC00(8, 8, 0, 0xFF, 0x40);
    func_8213B720(0, 0, 0x10, 8);
    func_8213B464(33);
    func_8213B644(0, 0x10, 8);
    func_8213BC00(0, 8, 0xFF, 0, 0x10);
}

/**
 * Effect script for the Bide and Rage use: a user hue pulse, rising particles (14 every 4 frames,
 * 7 every 8 frames), 32 flames under the Pokémon, and the shared Bide/Rage overlay.
 * Effect start init 85 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used:
 * it ran for exactly Rage.
 */
void BattleAnim_InitializeBideRageUse(void) {
    M2C_UNK *sp38;

    func_8213BC7C(0, 1, 0xA, 0, 0xC8, 0x10);
    sp38 = &BattleAnim_CallbackSharedAnimatedVerticalFade;
    func_8213B5D8(6, 4, 14, &BattleAnim_CallbackSharedAnimatedVerticalFade, &D_8218E770, 0, 1, 0x11, 7, 0x1A, 0);
    func_8213B5D8(7, 8, 7, &BattleAnim_CallbackSharedAnimatedVerticalFade, &D_8218E770, 0, 1, 0x11, 7, 0x1A, 0);
    func_8213B560(0, &BattleAnim_RunOscillatingFlameUnderneathPokemon, &D_8218E7F8, 0, 0x20, 7, 0, 0, 0);
    func_8215E510();
}

/**
 * Effect script for the Struggle and Thrash use: a user hue pulse, rising particles 3 at a time
 * every 2 frames from frame 4, and two more streams of rising particles.
 * Effect start init 114 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used:
 * it ran for exactly Struggle, Thrash.
 */
void BattleAnim_InitializeStruggleThrashUse(void) {
    BattleAnim_SpawnOwnerTintPulseDetach(0, 1, 0xA, 0, 0xC8, 4);
    BattleAnim_CreateRepeatEffectSlotForCurrentOwner(4, 3, 2, BattleAnim_HeavyHitAnimatedRiseFade, &gBattleAnimParticleDescriptors[0x3F], 0, 0x10, 0xA, 0, 0x11, 0);
    BattleAnim_CreateRepeatEffectSlotForCurrentOwner(6, 4, 14, BattleAnim_CallbackSharedAnimatedVerticalFade, &gBattleAnimParticleDescriptors[0x3D], 0, 1, 0x11, 7, 0x33, 7);
    BattleAnim_CreateRepeatEffectSlotForCurrentOwner(7, 8, 7, BattleAnim_CallbackSharedAnimatedVerticalFade, &gBattleAnimParticleDescriptors[0x3D], 0, 1, 0x11, 7, 0x33, 7);
}

/**
 * Effect script for the Double-Edge and Take Down use: a global tint fade, the speed lines, and
 * rising particles 3 at a time every 2 frames from frame 8.
 * Effect start init 115 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used:
 * it ran for exactly Double Edge, Take Down.
 */
void BattleAnim_InitializeDoubleEdgeTakeDownUse(void) {
    BattleAnim_SpawnGlobalTintColorFadeDetach(0, 0x20, 6);
    BattleAnim_InitializeSpeedLines();
    BattleAnim_CreateRepeatEffectSlotForCurrentOwner(8, 3, 2, BattleAnim_HeavyHitAnimatedRiseFade, &gBattleAnimParticleDescriptors[0x3F], 0, 0x10, 0xA, 0, 0x11, 0);
}

/**
 * Effect script for Body Slam's use: rising particles 3 at a time every 2 frames from frame 4.
 * Effect start init 116 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used:
 * it ran for exactly Body Slam.
 */
void BattleAnim_InitializeBodySlamUse(void) {
    BattleAnim_CreateRepeatEffectSlotForCurrentOwner(4, 3, 2, BattleAnim_HeavyHitAnimatedRiseFade, &gBattleAnimParticleDescriptors[0x3F], 0, 0x10, 0xA, 0, 0x11, 0);
}

/**
 * Effect script for the Earthquake and Fissure hit: four bursts of 8 rising dust particles on
 * frames 4 to 7, then 5 hit sparks at frames 8 and 16.
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

/**
 * Queues four vertical-fade particles (frames 4-7) and two default hit sparks (frames 8 and
 * 16) on the current owner.
 * @unverified Name guessed from the code.
 */
void BattleAnim_SpawnVerticalFadesAndHitSparks(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(4, BattleAnim_CallbackSharedAnimatedVerticalFade, &D_8218E580[0x4A], 0, 8, 0xA, 0, 0x33, 1);
    BattleAnim_CreateEffectSlotForCurrentOwner(5, BattleAnim_CallbackSharedAnimatedVerticalFade, &D_8218E580[0x4A], 0, 8, 0xA, 0, 0x33, 1);
    BattleAnim_CreateEffectSlotForCurrentOwner(6, BattleAnim_CallbackSharedAnimatedVerticalFade, &D_8218E580[0x4A], 0, 8, 0xA, 0, 0x33, 1);
    BattleAnim_CreateEffectSlotForCurrentOwner(7, BattleAnim_CallbackSharedAnimatedVerticalFade, &D_8218E580[0x4A], 0, 8, 0xA, 0, 0x33, 1);
    BattleAnim_CreateEffectSlotForCurrentOwner(8, BattleAnim_RunDefaultHitSpark, &D_8218E580[0x51], 0, 5, 0x11, 9, 0x17, 0xE);
    BattleAnim_CreateEffectSlotForCurrentOwner(0x10, BattleAnim_RunDefaultHitSpark, &D_8218E580[0x51], 0, 5, 0x11, 9, 0x17, 0xE);
}

/**
 * Effect script for the Defense Curl and Sharpen use: several bursts of rising particles
 * (descriptor 0x3D) at frames 0, 4 and 8.
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
 * Effect script for the Substitute and Transform use: owner tint ramps at frames 4 and 9 and six
 * bursts of 8 rising particles over frames 0 to 8.
 * Effect start init 89 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used:
 * it ran for exactly Substitute, Transform.
 */
void BattleAnim_InitializeSubstituteTransformUse(void) {
    BattleAnim_SpawnOwnerTintRampDetach(4, 0x8, 0, 0xFF, 0x40);
    BattleAnim_SpawnOwnerTintRampDetach(9, 0x8, 0xFF, 0, 0x40);
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_CallbackSharedAnimatedVerticalFade, &gBattleAnimParticleDescriptors[0x3D], 0, 8, 0xE, 0, 0x33, 2);
    BattleAnim_CreateEffectSlotForCurrentOwner(1, BattleAnim_CallbackSharedAnimatedVerticalFade, &gBattleAnimParticleDescriptors[0x3D], 0, 8, 0xE, 0, 0x33, 2);
    BattleAnim_CreateEffectSlotForCurrentOwner(2, BattleAnim_CallbackSharedAnimatedVerticalFade, &gBattleAnimParticleDescriptors[0x3D], 0, 8, 0xE, 0, 0x33, 2);
    BattleAnim_CreateEffectSlotForCurrentOwner(4, BattleAnim_CallbackSharedAnimatedVerticalFade, &gBattleAnimParticleDescriptors[0x3D], 0, 8, 0xE, 0, 0x33, 2);
    BattleAnim_CreateEffectSlotForCurrentOwner(4, BattleAnim_CallbackSharedAnimatedVerticalFade, &gBattleAnimParticleDescriptors[0x3D], 0, 8, 0xE, 0, 0x33, 2);
    BattleAnim_CreateEffectSlotForCurrentOwner(8, BattleAnim_CallbackSharedAnimatedVerticalFade, &gBattleAnimParticleDescriptors[0x3D], 0, 8, 0xE, 0, 0x33, 2);
}

/**
 * Effect script for the gathering-energy charge: seven groups of burst emitters at frames 0, 8,
 * 16, 24, 32, 48 and 60 (4 emitters in each of the first two, 8 in the rest), with arg0 as their
 * palette parameter.
 * Moves: Conversion (use), Mimic (use), Recover (use), Sky Attack (use), Solar Beam (use)
 * TODO: Human contributor add screenshot
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Solar Beam, Mimic, Metronome, Sky Attack, Conversion.
 */
void BattleAnim_InitializeQiCharge(s32 arg0) {
    BattleAnim_CreateRepeatEffectSlotForCurrentOwner(0, 1, 4, BattleAnim_SolarbeamMimicBurstEmitter, &gDefaultParticleDescriptor, 0, 1, 2, 0, arg0, 0);
    BattleAnim_CreateRepeatEffectSlotForCurrentOwner(8, 1, 4, BattleAnim_SolarbeamMimicBurstEmitter, &gDefaultParticleDescriptor, 0, 1, 2, 0, arg0, 0);
    BattleAnim_CreateRepeatEffectSlotForCurrentOwner(0x10, 1, 8, BattleAnim_SolarbeamMimicBurstEmitter, &gDefaultParticleDescriptor, 0, 1, 2, 0, arg0, 0);
    BattleAnim_CreateRepeatEffectSlotForCurrentOwner(24, 1, 8, BattleAnim_SolarbeamMimicBurstEmitter, &gDefaultParticleDescriptor, 0, 1, 2, 0, arg0, 0);
    BattleAnim_CreateRepeatEffectSlotForCurrentOwner(0x20, 1, 8, BattleAnim_SolarbeamMimicBurstEmitter, &gDefaultParticleDescriptor, 0, 1, 2, 0, arg0, 0);
    BattleAnim_CreateRepeatEffectSlotForCurrentOwner(48, 1, 8, BattleAnim_SolarbeamMimicBurstEmitter, &gDefaultParticleDescriptor, 0, 1, 2, 0, arg0, 0);
    BattleAnim_CreateRepeatEffectSlotForCurrentOwner(60, 1, 8, BattleAnim_SolarbeamMimicBurstEmitter, &gDefaultParticleDescriptor, 0, 1, 2, 0, arg0, 0);
}

/**
 * Effect script for the Mimic and Conversion use: a global tint fade, the energy charge in color
 * 0x0E, and a second tint fade at frame 100.
 * Moves: Conversion (use), Mimic (use)
 * TODO: Human contributor add screenshot
 * Effect start init 29, start init 60 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all
 * 165 moves used: it ran for exactly Conversion, Mimic.
 */
void BattleAnim_InitializeMimicConversionUse(void) {
    func_8213B644(0, 8, 6);
    func_82168844(0xE);
    func_8213B644(100, 0x20, 8);
}

/**
 * Effect script for Solar Beam's charge: a global tint fade, the energy charge in color 0x17, the
 * Solar Beam glow at frame 10, and a second tint fade at frame 100.
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Solar Beam.
 */
void BattleAnim_InitializeSolarBeamUseSequence(void) {
    func_8213B644(0, 8, 6);
    func_82168844(0x17);
    func_8213B560(10, &func_821655C0, &D_8218E768, 0x1A, 1, 5, 0, 0x33, 0);
    func_8213B644(100, 0x20, 8);
}

/**
 * Effect init that spawns the Growth animation. Player sweep (all 165 moves used in battle): only
 * Growth reached this function.
 * Effect start init 109 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used:
 * it ran for exactly Growth.
 */
void BattleAnim_InitializeGrowthUse(void) {
    func_8213BC7C(10, 1, 8, 0, 0xFF, 0x20);
}

/**
 * Effect script for Recover's use: a global tint fade, the energy charge in color 0x0C, a rainbow
 * hue change at frame 4, and 5 sparkles every 8 frames from frame 4.
 * Seen in play (2026-11-13) ran when 1P used Recover with its HP set to 5 (at full HP the move
 * fails and the sweep never saw the animation).
 * @unverified Name from Stadium 1.
 */
void BattleAnim_InitializeRecoverUse(void) {
    BattleAnim_SpawnGlobalTintColorFadeDetach(0, 8, 6);
    BattleAnim_InitializeQiCharge(0xC);
    BattleAnim_SpawnRainbowHueChange(4, 0x32, 0x20, 0xA0);
    BattleAnim_CreateRepeatEffectSlotForCurrentOwner(4, 8, 5, BattleAnim_RunSparkleHit, &gBattleAnimParticleDescriptors[0x42], 0, 8, 9, 0, 0xC, 9);
}

/**
 * Effect script for Harden's use: an owner tint ramp and 2 particle bursts every 2 frames from
 * frame 4.
 * Effect start init 30 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used:
 * it ran for exactly Harden.
 */
void BattleAnim_InitializeHardenUse(void) {
    func_8213BC00(0, 8, 0xFF, 0, 0x20);
    func_8213B5D8(4, 2, 2, &func_821624FC, &D_8218E798, 0, 8, 9, 0, 0x17, 1);
}
