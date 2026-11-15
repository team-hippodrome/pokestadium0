/* Stadium Zero fragment012_17ED00. */
/* C ported from the Stadium 1 decomp: src/fragments/battle_engine/battle_engine_31D9F0.c, src/fragments/battle_engine/battle_engine_343BA0.c. */

#include "fragments/battle_engine/battle_engine.h"
#include "model_renderer.h"

#include "fragments/battle_engine/battle_engine.h"
#include "gallery.h"
#include "gfx_buffer.h"
#include "math.h"
#include "math_util.h"
extern u8* sBattleAnimAssetPointers[256];
extern s16 sBattleAnimResourceList[0x10];
extern arg1_func_80019420* sBattleAnimResourceTablePointers[40];
extern s16 D_8219CAC0;
extern s16 D_8219CAC2;
extern Mtx D_8219CAC8;
extern s16 D_8219CB08;
extern s16 D_8219CB0A;
extern s16 D_8219CB0C;
extern s16 D_8219CB0E;
extern s16 D_8219CB10;
extern s16 D_8219CB12;
extern s16 D_8219CB14;
extern s16 D_8219CB16;
extern s16 D_8219CB18;
extern s16 D_8219CB1A;
extern const char D_821978C8[];

#include "m2c_macros.h"
extern ParticleDescriptor D_8218E580[];

M2C_UNK Particle_AnimateFramesForwardLooped(s8 *, M2C_UNK, M2C_UNK, M2C_UNK, s32, s32);

void BattleAnim_SetupFireBreathFlameFading(Particle* arg0, s16 arg1);
void BattleAnim_SetupUnusedDescriptor4FColorCycleScaleFadeVariant(Particle* arg0);
void BattleAnim_SetupFireBreathFlameGeometry(Particle* arg0);
void BattleAnim_SetupFireBreathFlameColoration(Particle* arg0, s16 arg1);
void BattleAnim_SetupExpandingHitSpark(Particle* arg0);
void BattleAnim_SetupOscillatingFlameUnderneathPokemon(Particle* arg0);
void BattleAnim_SetupFireSpinFlame(Particle* arg0);
void BattleAnim_SetupUnusedVariant2(Particle* arg0);
void BattleAnim_SetupEmberProjectileAfterimages(Particle* arg0);
void BattleAnim_SetupEmberProjectile(Particle* arg0);
void BattleAnim_SetupEmberBurstEmitter(Particle* arg0);
void BattleAnim_SetupEmberUseEffect(Particle* arg0);
void BattleAnim_GetExplosionParticleColor(Particle* arg0, u8 arg1);
void func_82146674(void);
void BattleAnim_FirePunchEmberEggBombColorChange(Particle* arg0);
void BattleAnim_SetupBackgroundBombExplosion(Particle* arg0);
void BattleAnim_SetupBoomSmallExplosion(Particle* arg0);
void BattleAnim_SetupEggBombHitEffect(Particle* arg0);
void BattleAnim_SetupSecondaryBombExplosion(Particle* arg0);
void BattleAnim_SetupEmberHitFireball(Particle* arg0);
void BattleAnim_SetupEmberHitSmoke(Particle* arg0);
void BattleAnim_SetupFirePunchLingeringHitSpark(Particle* arg0);
void BattleAnim_SetupAfterImpactSmoke(Particle* arg0);
void BattleAnim_SetupFirePunchHitEffect(Particle* arg0);
void BattleAnim_SetupFlamethrowerHitRotation(Particle* arg0, s16 arg1, s16 arg2);
void BattleAnim_RunFlamethrowerHitRotationWeak(Particle* arg0);
void BattleAnim_RunFlamethrowerHitRotationStrong(Particle* arg0);
void BattleAnim_SetupFireBlastHitFrontFlames(Particle* arg0);
void BattleAnim_SetupDaimonji(Particle* arg0);
void BattleAnim_SetupDaimonjiColoration(Particle* arg0);
void func_821491CC(void);
void BattleAnim_DefaultStartEffect_Init(void);
void BattleAnim_DefaultEndEffect_Init(void);

void BattleAnim_RunFlamethrowerHitRotation(Particle* arg0, s32 arg1);

/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Flamethrower, Dragon Rage, Fire Spin, Fire Blast.
 */
void BattleAnim_SetupFireBreathFlameFading(Particle* arg0, s16 arg1) {
    UNUSED s32 pad[3]; // FAKE: stack padding
    s16 sp22 = Particle_FieldAC_GetS16_0C038(arg0);

    Particle_SetScaleScaled(arg0, 0.25f);
    Particle_Field94_AddX_0A578(arg0, ParticleMath_RandomSignedOffset(0x400, 0xE00));
    Particle_Field94_AddY_0A594(arg0, ParticleMath_RandomSigned(0x400));
    Particle_Field74_SetScaled_0AD8C(arg0, 2.5f);

    switch (arg1) {
        case 0:
            ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, 0x17);
            break;

        case 1:
            ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, 0x18);
            break;
    }

    Particle_FieldA6_SetS16_0BCA8(arg0, sp22 * 2);
    Particle_DisableRendering(arg0);
    Particle_AdvanceLifecycle(arg0);
}

s32 Particle_DecreaseRotationXTo(Particle* arg0, s32 arg1, s32 arg2);
/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Flamethrower, Dragon Rage, Fire Spin, Fire Blast.
 */
void BattleAnim_ContinueFireBreathFlameFading(Particle* arg0) {
    switch (arg0->phase) {
        case 1:
            if (Particle_TickPhaseTimer(arg0, 2) != 0) {
                Particle_AdvancePhase(arg0);
            }
            break;

        case 2:
            Particle_DecreaseRotationXTo(arg0, -0x400, 0x200);
            if (Particle_TickPhaseTimer(arg0, 0x10) != 0) {
                Particle_AdvancePhase(arg0);
            }
            break;
    }

    if (arg0->phase > 0) {
        Particle_AddVelocityFromRotationTemplate1(arg0);
    }
}

/**
 * Handles the fading of flames when using Fire Blast, Fire Spin, Flamethrower, or Dragon Rage
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Flamethrower, Dragon Rage, Fire Spin, Fire Blast.
 */
void BattleAnim_RunFireBreathFlameFading(Particle* arg0) {
    s16 sp2E = Particle_FieldCF_GetS16_0C058(arg0);

    switch (arg0->lifecycle) {
        case 1:
            BattleAnim_SetupFireBreathFlameFading(arg0, sp2E);
            break;

        case 2:
            if (Particle_DecrementUnkA6ToZeroThenAdvance(arg0) != 0) {
                Particle_BeginPhase(arg0);
                Particle_EnableRendering(arg0);
                Particle_FieldA6_SetS16_0BCA8(arg0, 11);
            }
            break;

        case 3:
            Particle_ApproachScale(arg0, 0.75f, 0.03f);

            switch (sp2E) {
                case 0:
                    Particle_PrimB_Approach_0BB44(arg0, 0, 0x18);
                    Particle_EnvG_Approach_0BBF0(arg0, 0, 0x18);
                    break;

                case 1:
                    Particle_PrimR_Approach_0BAE4(arg0, 0, 0x18);
                    Particle_EnvG_Approach_0BBF0(arg0, 0x78, 0xC);
                    break;
            }

            if (Particle_DecrementUnkA6ToZeroThenAdvance(arg0) != 0) {
                Particle_FieldA6_SetS16_0BCA8(arg0, 12);
            }
            break;

        case 4:
            Particle_ApproachScale(arg0, 0.75f, 0.02f);
            switch (sp2E) {
                case 0:
                    Particle_PrimG_Approach_0BB14(arg0, 0, 0x10);
                    Particle_EnvR_Approach_0BB90(arg0, 0, 0x10);
                    break;

                case 1:
                    Particle_PrimG_Approach_0BB14(arg0, 0x78, 0xC);
                    Particle_EnvG_Approach_0BBF0(arg0, 0, 0xA);
                    break;
            }

            if ((Particle_DecrementUnkA6ToZero(arg0) != 0) && (Particle_PrimAlpha_Approach_0BC2C(arg0, 0, 0x18) != 0)) {
                Particle_AdvanceLifecycle(arg0);
            }
            break;

        case 5:
            Particle_MarkInactive(arg0);
            break;
    }

    if (Particle_IsRenderingEnabled(arg0) != 0) {
        Particle_AnimateFramesForwardLooped(arg0, 0, 7, 1, 2, -1);
        BattleAnim_ContinueFireBreathFlameFading(arg0);
    }
}

/**
 * Lifecycle init: quarter scale, small random turn about Y, palette color 0x17, delayed 2
 * frames per burst index.
 * Not reached in play (2026-11-13): did not run in the 165-move battle sweep (each move used once,
 * from the command menu to the end of its turn) or in a tour of the menus and a COM battle.
 * @unverified Name from Stadium 1.
 */
void BattleAnim_SetupUnusedDescriptor4FColorCycleScaleFadeVariant(Particle* arg0) {
    UNUSED s32 pad[3]; // FAKE: stack padding
    s16 sp22 = Particle_FieldAC_GetS16_0C038(arg0);

    Particle_SetScaleScaled(arg0, 0.25f);
    Particle_Field94_AddY_0A594(arg0, ParticleMath_RandomSigned(0x400));
    Particle_Field74_SetScaled_0AD8C(arg0, D_8219C590[0]);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, 0x17);
    Particle_FieldA6_SetS16_0BCA8(arg0, sp22 * 2);
    Particle_DisableRendering(arg0);
    Particle_AdvanceLifecycle(arg0);
}

/**
 * Motion steps for the particle above: after 2 frames tilts it about Z, then keeps
 * curving it about X while it moves.
 * Not reached in play (2026-11-13): did not run in the 165-move battle sweep (each move used once,
 * from the command menu to the end of its turn) or in a tour of the menus and a COM battle.
 * @unverified Name from Stadium 1.
 */
void BattleAnim_MotionUnusedDescriptor4FColorCycleScaleFadeVariant(Particle* arg0) {
    switch (arg0->phase) {
        case 1:
            if (Particle_TickPhaseTimer(arg0, 2) != 0) {
                Particle_AdvancePhase(arg0);
                Particle_Field94_AddZ_0A5B0(arg0, 0x2900);
            }
            break;

        case 2:
            Particle_Field94_AddX_0A578(arg0, 0xC00);
            break;
    }

    if (arg0->phase > 0) {
        Particle_AddVelocityFromRotationTemplate7B(arg0);
    }
}

/**
 * Particle callback: after the delay shows the particle, loops its 8 texture frames and
 * runs the motion steps until it fades.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal or j,
 * no pointer word, no lui/addiu pair in any fragment), so play cannot reach it.
 * @unverified Name from Stadium 1.
 */
void BattleAnim_CallbackUnusedDescriptor4FColorCycleScaleFadeVariant(Particle* arg0) {
    switch (arg0->lifecycle) {
        case 1:
            BattleAnim_SetupUnusedDescriptor4FColorCycleScaleFadeVariant(arg0);
            break;

        case 2:
            if (Particle_DecrementUnkA6ToZeroThenAdvance(arg0) != 0) {
                Particle_BeginPhase(arg0);
                Particle_EnableRendering(arg0);
                Particle_FieldA6_SetS16_0BCA8(arg0, 11);
            }
            break;

        case 3:
            Particle_ApproachScale(arg0, 0.75f, 0.03f);
            Particle_PrimB_Approach_0BB44(arg0, 0, 0x18);
            Particle_EnvG_Approach_0BBF0(arg0, 0, 0x20);
            if (Particle_DecrementUnkA6ToZeroThenAdvance(arg0) != 0) {
                Particle_FieldA6_SetS16_0BCA8(arg0, 12);
            }
            break;

        case 4:
            Particle_ApproachScale(arg0, 0.75f, 0.02f);
            Particle_PrimG_Approach_0BB14(arg0, 0, 0x10);
            Particle_EnvR_Approach_0BB90(arg0, 0, 0x10);
            if ((Particle_DecrementUnkA6ToZero(arg0) != 0) && (Particle_PrimAlpha_Approach_0BC2C(arg0, 0, 0xC) != 0)) {
                Particle_AdvanceLifecycle(arg0);
            }
            break;

        case 5:
            Particle_MarkInactive(arg0);
            break;
    }

    if (Particle_IsRenderingEnabled(arg0) != 0) {
        Particle_AnimateFramesForwardLooped((s8*)arg0, 0, 7, 1, 2, -1);
        BattleAnim_MotionUnusedDescriptor4FColorCycleScaleFadeVariant(arg0);
    }
}

/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Flamethrower, Dragon Rage, Fire Spin, Fire Blast.
 */
void BattleAnim_SetupFireBreathFlameGeometry(Particle* arg0) {
    UNUSED s32 pad[3]; // FAKE: stack padding
    s16 sp22 = Particle_FieldAC_GetS16_0C038(arg0);
    s16 sp20 = Particle_FieldCF_GetS16_0C058(arg0);

    Particle_SetScaleScaled(arg0, 0.4f);
    Particle_Field94_AddX_0A578(arg0, ParticleMath_RandomSignedOffset(0x200, 0xE00));
    Particle_Field94_AddY_0A594(arg0, ParticleMath_RandomSigned(0x1800));
    Particle_Field74_SetScaled_0AD8C(arg0, 2.0f);

    switch (sp20) {
        case 0:
            ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, 0x1A);
            break;

        case 1:
            ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, 6);
            break;
    }

    Particle_SetPrimAlpha(arg0, 0xC8);
    Particle_FieldA6_SetS16_0BCA8(arg0, sp22 * 2);
    Particle_DisableRendering(arg0);
    Particle_AdvanceLifecycle(arg0);
}

s32 Particle_DecreaseRotationXTo(Particle* arg0, s32 arg1, s32 arg2);
/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Flamethrower, Dragon Rage, Fire Spin, Fire Blast.
 */
void BattleAnim_ContinueFireBreathFlameGeometry(Particle* arg0) {
    switch (arg0->phase) {
        case 1:
            if (Particle_TickPhaseTimer(arg0, 1) != 0) {
                Particle_AdvancePhase(arg0);
            }
            break;

        case 2:
            Particle_DecreaseRotationXTo(arg0, -0x1800, 0x800);
            if (Particle_TickPhaseTimer(arg0, 0x10) != 0) {
                Particle_AdvancePhase(arg0);
            }
            break;
    }

    if (arg0->phase > 0) {
        Particle_AddVelocityFromRotationTemplate1(arg0);
    }
}

void Particle_MarkInactive(s8 *arg0);                      /* extern */
M2C_UNK func_8213CB3C(s8 *);                      /* extern */
s32 func_8213CB7C(s8 *);                          /* extern */
M2C_UNK Particle_AnimateFramesForwardLoopedThenAdvance(s8 *, M2C_UNK, M2C_UNK, M2C_UNK, s32, s32); /* extern */
M2C_UNK func_8213D238(s8 *);                      /* extern */
M2C_UNK func_82140228(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK Particle_ApproachPrimAlpha(s8 *, M2C_UNK, M2C_UNK);    /* extern */
s32 func_821406B4(s8 *);                          /* extern */
M2C_UNK func_821452FC(s8 *);                      /* extern */
M2C_UNK func_821453F4(s8 *);                      /* extern */

void func_82145498(s8 *arg0) {
    s16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_821452FC(arg0);
        break;
    case 2:
        if (func_821406B4(arg0) != 0) {
            func_8213D238(arg0);
            func_8213CB3C(arg0);
        }
        break;
    case 3:
        Particle_AnimateFramesForwardLoopedThenAdvance(arg0, 0, 7, 1, 2, 0);
        Particle_ApproachPrimAlpha(arg0, 0x20, 4);
        func_82140228(arg0, 0x3F400000, 0x3D4CCCCD);
        break;
    case 4:
        Particle_MarkInactive(arg0);
        break;
    }
    if (func_8213CB7C(arg0) != 0) {
        func_821453F4(arg0);
    }
}

/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Flamethrower, Dragon Rage, Fire Spin, Fire Blast.
 */
void BattleAnim_SetupFireBreathFlameColoration(Particle* arg0, s16 arg1) {
    UNUSED s32 pad[3]; // FAKE: stack padding
    s16 sp22 = Particle_FieldAC_GetS16_0C038(arg0);

    Particle_SetScaleScaled(arg0, 0.2f);
    Particle_Field94_AddX_0A578(arg0, ParticleMath_RandomSignedOffset(0x200, 0xE00));
    Particle_Field94_AddY_0A594(arg0, ParticleMath_RandomSigned(0x2000));
    Particle_Field74_SetScaled_0AD8C(arg0, 2.0f);

    switch (arg1) {
        case 0:
            ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, 0x17);
            break;

        case 1:
            ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, 0x18);
            break;
    }

    Particle_FieldA6_SetS16_0BCA8(arg0, sp22 * 2);
    Particle_DisableRendering(arg0);
    Particle_AdvanceLifecycle(arg0);
}

/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Flamethrower, Dragon Rage, Fire Spin, Fire Blast.
 */
void BattleAnim_ContinueFireBreathFlameColoration(Particle* arg0) {
    switch (arg0->phase) {
        case 1:
            if (Particle_TickPhaseTimer(arg0, arg0->unk_AE) != 0) {
                Particle_AdvancePhase(arg0);
            }
            break;

        case 2:
            Particle_ApproachRotationXTo(arg0, 0x4000, 0x800);
            if (Particle_TickPhaseTimer(arg0, 0x10) != 0) {
                Particle_AdvancePhase(arg0);
            }
            break;
    }

    if (arg0->phase > 0) {
        Particle_AddVelocityFromRotationTemplate1(arg0);
    }
}

/**
 * Seen in play (2026-11-13) in the 165-move sweep (each move used once by the 1P Pokémon): it ran
 * only for Flamethrower, Dragon Rage, Fire Spin and Fire Blast.
 */
void BattleAnim_FlameRotatingFallColorCycle(Particle* arg0) {
    s16 temp_v0 = Particle_FieldCF_GetS16_0C058(arg0);

    switch (arg0->lifecycle) {
        case 1:
            BattleAnim_SetupFireBreathFlameColoration(arg0, temp_v0);
            break;

        case 2:
            if (Particle_DecrementUnkA6ToZeroThenAdvance(arg0) != 0) {
                Particle_BeginPhase(arg0);
                Particle_EnableRendering(arg0);
                Particle_FieldAE_SetS16_0BF4C(arg0, ParticleMath_RandomRange(3));
                Particle_FieldA6_SetS16_0BCA8(arg0, 8);
            }
            break;

        case 3:
            switch (temp_v0) {
                case 0:
                    Particle_PrimB_Approach_0BB44(arg0, 0, 0x20);
                    Particle_EnvG_Approach_0BBF0(arg0, 0, 0x20);
                    break;

                case 1:
                    Particle_PrimR_Approach_0BAE4(arg0, 0, 0x20);
                    Particle_EnvG_Approach_0BBF0(arg0, 0x78, 0x10);
                    break;
            }
            Particle_DecrementUnkA6ToZeroThenAdvance(arg0);
            break;

        case 4:
            switch (temp_v0) {
                case 0:
                    Particle_PrimG_Approach_0BB14(arg0, 0, 0x20);
                    Particle_EnvR_Approach_0BB90(arg0, 0, 0x20);
                    break;

                case 1:
                    Particle_PrimG_Approach_0BB14(arg0, 0x78, 0xC);
                    Particle_EnvG_Approach_0BBF0(arg0, 0, 0xA);
                    break;
            }

            if (Particle_PrimAlpha_Approach_0BC2C(arg0, 0, 0x18) != 0) {
                Particle_AdvanceLifecycle(arg0);
            }
            break;

        case 5:
            Particle_MarkInactive(arg0);
            break;
    }

    if (Particle_IsRenderingEnabled(arg0) != 0) {
        Particle_AnimateFramesForwardLooped((s8*)arg0, 0, 7, 1, 2, -1);
        Particle_ApproachScale(arg0, 0.02f, 0.015f);
        BattleAnim_ContinueFireBreathFlameColoration(arg0);
        if (arg0->worldPosition.y <= 0.0f) {
            Particle_MarkInactive(arg0);
        }
    }
}

/**
 * handles setting up the hit spark for Hydro Pump, Ice Beam, Bubble Beam, Hyper Beam, Solar Beam, Egg Bomb, Waterfall,
 * and Sky Attack Oddly, Psybeam calls this setup, but not the runner for the effect
 * Seen in play (2026-11-13) (unattended Free Battle in which every Pokémon knows only Metronome, 40
 * turns): ran.
 * @unverified Name and comment from Stadium 1.
 */
void BattleAnim_SetupExpandingHitSpark(Particle* arg0) {
    Particle_AddPositionOffsetAlongRotationYPlus180(arg0, 33.0f);
    Particle_SetScaleScaled(arg0, 0.67f);
    ParticleGfx_RecolorPrim(arg0, Particle_FieldCF_GetS16_0C058(arg0));
    Particle_SetPrimAlpha(arg0, 0xC8);
    Particle_AdvanceLifecycle(arg0);
}

/**
 * handles expanding hit spark for Hydro Pump, Ice Beam, Bubble Beam, Hyper Beam, Solar Beam, Egg Bomb, Waterfall, and
 * Sky Attack
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Bubblebeam, Egg Bomb, Hydro Pump, Hyper Beam, Ice Beam and Waterfall (the sweep used only
 * the charge turn of Solar Beam and Sky Attack).
 */
void BattleAnim_RunExpandingHitSpark(Particle* arg0) {
    switch (arg0->lifecycle) {
        case 1:
            BattleAnim_SetupExpandingHitSpark(arg0);
            break;

        case 2:
            if (Particle_ApproachScale(arg0, 6.67f, 0.67f) != 0) {
                Particle_AdvanceLifecycle(arg0);
            }
            break;

        case 3:
            Particle_TickDelayAndAdvanceLifecycle(arg0, 0);
            break;

        case 4:
            if (Particle_PrimAlpha_Approach_0BC2C(arg0, 0x20, 8) != 0) {
                Particle_AdvanceLifecycle(arg0);
            }
            break;

        case 5:
            Particle_DisableAndDetach(arg0);
            break;
    }
}

/**
 * handles the hit spark when being hit by psybeam
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Psybeam.
 */
void BattleAnim_RunPsybeamHitSparkDrift(Particle* arg0) {
    switch (arg0->lifecycle) {
        case 1:
            BattleAnim_SetupExpandingHitSpark(arg0);
            break;

        case 2:
            if (Particle_ApproachScale(arg0, 8.0f, 1.0f) != 0) {
                Particle_AdvanceLifecycle(arg0);
            }
            break;

        case 3:
            Particle_TickDelayAndAdvanceLifecycle(arg0, 8);
            break;

        case 4:
            if (Particle_PrimAlpha_Approach_0BC2C(arg0, 0x20, 8) != 0) {
                Particle_AdvanceLifecycle(arg0);
            }
            break;

        case 5:
            Particle_DisableAndDetach(arg0);
            break;
    }

    Particle_Field94_AddZ_0A5B0(arg0, 0x1000);
}

/**
 * Particle callback: grows an expanding hit spark to 8 times its size, then fades it,
 * picking a random color every 4 frames.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal or j,
 * no pointer word, no lui/addiu pair in any fragment), so play cannot reach it.
 * @unverified Name from Stadium 1.
 */
void BattleAnim_CallbackUnusedGrowFadeVariant(Particle* arg0) {
    switch (arg0->lifecycle) {
        case 1:
            BattleAnim_SetupExpandingHitSpark(arg0);
            break;

        case 2:
            if (Particle_ApproachScale(arg0, 8.0f, 1.0f) != 0) {
                Particle_AdvanceLifecycle(arg0);
            }
            break;

        case 3:
            Particle_TickDelayAndAdvanceLifecycle(arg0, 8);
            break;

        case 4:
            if (Particle_PrimAlpha_Approach_0BC2C(arg0, 0x20, 8) != 0) {
                Particle_AdvanceLifecycle(arg0);
            }
            break;

        case 5:
            Particle_DisableAndDetach(arg0);
            break;
    }

    Particle_Field94_AddZ_0A5B0(arg0, 0x1000);

    if (gParticleFrameMod4 == 0) {
        ParticleGfx_RecolorPrimFromPaletteSetB(arg0, ParticleMath_RandomRange(6));
    }
}

/**
 * Seen in play (2026-11-13) (Free Battle, 1P Metronome pinned to Rage): ran 32 times during Rage's
 * use animation, the flames rising around Onix.
 */
void BattleAnim_SetupOscillatingFlameUnderneathPokemon(Particle* arg0) {
    s16 sp26 = Particle_FieldAC_GetS16_0C038(arg0);

    Particle_SetScaleScaled(arg0, 0.5f);
    Particle_Field7C_SetYScaled_0AF24(arg0, 2.0f);
    Particle_Field9A_SetY_0A3D8(arg0, ParticleMath_RandomRange(0x10000));
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, 0x1A);
    Particle_SetPrimAlpha(arg0, 0xFF);
    Particle_FieldA6_SetS16_0BCA8(arg0, sp26 * 4);
    Particle_DisableRendering(arg0);
    Particle_AdvanceLifecycle(arg0);
}

void Particle_DisableAndDetach(s8 *arg0);                      /* extern */
M2C_UNK func_8213C9D0(s8 *);                      /* extern */
M2C_UNK func_8213CB3C(s8 *);                      /* extern */
M2C_UNK Particle_AnimateFramesForwardLoopedThenAdvance(s8 *, M2C_UNK, M2C_UNK, M2C_UNK, s32, s32); /* extern */
M2C_UNK func_8213E1FC(s8 *, M2C_UNK);             /* extern */
M2C_UNK func_82140064(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_82140228(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK Particle_ApproachPrimGreen(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK Particle_ApproachEnvRed(s8 *, M2C_UNK, M2C_UNK);    /* extern */
s32 Particle_ApproachPrimAlpha(s8 *, M2C_UNK, M2C_UNK);        /* extern */
M2C_UNK Particle_SetUnkA6(s8 *, M2C_UNK);             /* extern */
s32 func_82140690(s8 *);                          /* extern */
s32 func_821406B4(s8 *);                          /* extern */
M2C_UNK func_82145C28(s8 *);                      /* extern */

/**
 * handles the flame that appears under a pokemon when:
 * - charging Sky Attack
 * - Using Rage or Bide
 * - Being hit by Fire Spin
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Fire Spin, Rage, Sky Attack and Metronome (through the move it called). Bide did not use
 * it.
 */
void BattleAnim_RunOscillatingFlameUnderneathPokemon(s8 *arg0) {
    s16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_82145C28(arg0);
        return;
    case 2:
        if (func_821406B4(arg0) != 0) {
            func_8213CB3C(arg0);
            Particle_SetUnkA6(arg0, 0x10);
            return;
        }
        return;
    case 3:
        Particle_AnimateFramesForwardLoopedThenAdvance(arg0, 0, 7, 1, 2, -1);
        func_82140228(arg0, 0x3F800000, 0x3DCCCCCD);
        func_8213E1FC(arg0, 0x40000000);
        func_82140064(arg0, 0x41200000, 0x800);
        Particle_ApproachPrimGreen(arg0, 0, 4);
        Particle_ApproachEnvRed(arg0, 0, 4);
        if ((func_82140690(arg0) != 0) && (Particle_ApproachPrimAlpha(arg0, 0, 0x18) != 0)) {
            func_8213C9D0(arg0);
            return;
        }
        break;
    case 4:
        Particle_DisableAndDetach(arg0);
        break;
    }
}

/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Fire Spin.
 */
void BattleAnim_SetupFireSpinFlame(Particle* arg0) {
    s16 sp26 = Particle_FieldAC_GetS16_0C038(arg0);

    Particle_SetScaleScaled(arg0, 0.5f);
    Particle_Field38_SetYScaled_08CA0(arg0, 10.0f);
    Particle_Field7C_SetYScaled_0AF24(arg0, 1.0f);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, 0x1A);
    Particle_SetPrimAlpha(arg0, 0xFF);
    Particle_DisableRendering(arg0);
    Particle_Field9A_SetY_0A3D8(arg0, (sp26 << 0x10) / 18);
    Particle_FieldA6_SetS16_0BCA8(arg0, sp26 * 3);
    Particle_AdvanceLifecycle(arg0);
}

M2C_UNK func_8213CB3C(s8 *);                      /* extern */
s32 func_8213CB7C(s8 *);                          /* extern */
M2C_UNK func_82140064(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_82140228(s8 *, M2C_UNK, M2C_UNK);    /* extern */
s32 func_821406B4(s8 *);                          /* extern */
M2C_UNK func_82145E04(s8 *);                      /* extern */

/**
 * Particle callback of the Fire Spin animation. Player sweep (all 165 moves used in battle): only
 * Fire Spin reached this function.
 */
void BattleAnim_FireSpinParticleUpdate(s8 *arg0) {
    s16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_82145E04(arg0);
        break;
    case 2:
        if (func_821406B4(arg0) != 0) {
            func_8213CB3C(arg0);
        }
        break;
    case 3:
        func_82140228(arg0, 0x3F800000, 0x3DCCCCCD);
        break;
    }
    if (func_8213CB7C(arg0) != 0) {
        func_82140064(arg0, 0x42480000, 0);
    }
}

/**
 * Lifecycle init: full scale, raised 10 units, palette color 0x1A, starting angle spread
 * over 18 steps by burst index.
 * Not reached in play (2026-11-13): did not run in the 165-move battle sweep (each move used once,
 * from the command menu to the end of its turn) or in a tour of the menus and a COM battle.
 * @unverified Name from Stadium 1.
 */
void BattleAnim_SetupUnusedVariant2(Particle* arg0) {
    s16 sp26 = Particle_FieldAC_GetS16_0C038(arg0);

    Particle_SetScaleScaled(arg0, 1.0f);
    Particle_Field38_SetYScaled_08CA0(arg0, 10.0f);
    Particle_Field7C_SetYScaled_0AF24(arg0, 1.0f);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, 0x1A);
    Particle_SetPrimAlpha(arg0, 0xFF);
    Particle_DisableRendering(arg0);
    Particle_Field9A_SetY_0A3D8(arg0, (sp26 << 0x10) / 18);
    Particle_FieldA6_SetS16_0BCA8(arg0, 0);
    Particle_AdvanceLifecycle(arg0);
}

/**
 * Particle callback: shows the particle and moves it on a circle of radius 50 until it
 * finishes.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal or j,
 * no pointer word, no lui/addiu pair in any fragment), so play cannot reach it.
 * @unverified Name from Stadium 1.
 */
void BattleAnim_CallbackUnusedVariant2(Particle* arg0) {
    switch (arg0->lifecycle) {
        case 3:
            break;

        case 1:
            BattleAnim_SetupUnusedVariant2(arg0);
            break;

        case 2:
            if (Particle_DecrementUnkA6ToZeroThenAdvance(arg0) != 0) {
                Particle_EnableRendering(arg0);
            }
            break;

        case 4:
            Particle_ApproachPrimAlphaThenAdvance(arg0, 0, 0x10);
            break;

        case 5:
            Particle_DisableAndDetach(arg0);
            break;
    }

    if (Particle_IsRenderingEnabled(arg0) != 0) {
        Particle_UpdateRotatingVelocityXZ(arg0, 50.0f, 0);
    }
}

/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Ember.
 */
void BattleAnim_SetupEmberProjectileAfterimages(Particle* arg0) {
    Particle_SetScaleScaled(arg0, 0.4f);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, 0x1A);
    Particle_SetPrimAlpha(arg0, 0xA0);
    Particle_AdvanceLifecycle(arg0);
}

void Particle_DisableAndDetach(s8 *arg0);                      /* extern */
M2C_UNK Particle_AnimateFramesForwardLoopedThenAdvance(s8 *, M2C_UNK, M2C_UNK, M2C_UNK, s32, s32); /* extern */
M2C_UNK func_82140228(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK Particle_ApproachPrimAlpha(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_821460C8(s8 *);                      /* extern */

/**
 * Particle callback of the Ember animation. Player sweep (all 165 moves used in battle): only
 * Ember reached this function.
 */
void BattleAnim_EmberParticleUpdateB(s8 *arg0) {
    s16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_821460C8(arg0);
        break;
    case 2:
        Particle_AnimateFramesForwardLoopedThenAdvance(arg0, 2, 7, 1, 2, 0);
        Particle_ApproachPrimAlpha(arg0, 0x20, 0x18);
        break;
    case 3:
        Particle_DisableAndDetach(arg0);
        break;
    }
    func_82140228(arg0, 0x3F19999A, 0x3D4CCCCD);
}

/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Ember.
 */
void BattleAnim_SetupEmberProjectile(Particle* arg0) {
    Particle_SetScaleScaled(arg0, 0.4f);
    Particle_Field74_SetScaled_0AD8C(arg0, 8.0f);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, 0x29);
    Particle_SetTextureFrame(arg0, 2);
    Particle_SetPrimAlpha(arg0, 0xFF);
    Particle_AdvanceLifecycle(arg0);
}

M2C_UNK func_82139E5C(s8 *, M2C_UNK *, M2C_UNK *, M2C_UNK); /* extern */
void Particle_DisableAndDetach(s8 *arg0);                      /* extern */
M2C_UNK func_8213CA80(s8 *, M2C_UNK);             /* extern */
s32 func_8213CB7C(s8 *);                          /* extern */
M2C_UNK Particle_AnimateFramesForwardLoopedThenAdvance(s8 *, M2C_UNK, M2C_UNK, M2C_UNK, s32, s32); /* extern */
void Particle_AddVelocityFromRotationTemplate1(s32 arg0);                      /* extern */
M2C_UNK func_821437E0(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_821461C4(s8 *);                      /* extern */
extern M2C_UNK D_8218E7D0;

/**
 * handles the projectile made when Ember is used
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Ember.
 */
void BattleAnim_RunEmberProjectile(s8 *arg0) {
    s16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_821461C4(arg0);
        break;
    case 2:
        Particle_AnimateFramesForwardLoopedThenAdvance(arg0, 3, 5, 1, 1, 0);
        break;
    case 3:
        func_8213CA80(arg0, 0xF);
        break;
    case 4:
        Particle_DisableAndDetach(arg0);
        break;
    }
    if (func_8213CB7C(arg0) != 0) {
        func_821437E0(arg0, 0x2A, 0x1C);
        Particle_AddVelocityFromRotationTemplate1(arg0);
        func_82139E5C(arg0, &BattleAnim_EmberParticleUpdateB, &D_8218E7D0, 1);
    }
}

/**
 * Handles the white "origin" of the burst for ember
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Ember.
 */
void BattleAnim_SetupEmberBurstEmitter(Particle* arg0) {
    Particle_FieldAC_GetS16_0C038(arg0);
    Particle_Field74_SetScaled_0AD8C(arg0, 0.2f);
    Particle_SetScaleScaled(arg0, 1.0f);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, 0x1D);
    Particle_SetPrimAlpha(arg0, 0xFF);
    Particle_AdvanceLifecycle(arg0);
}

void Particle_MarkInactive(s8 *arg0);                      /* extern */
M2C_UNK func_8213CA80(s8 *, M2C_UNK);             /* extern */
M2C_UNK Particle_AnimateFramesForwardLoopedThenAdvance(s8 *, M2C_UNK, M2C_UNK, M2C_UNK, s32, s32); /* extern */
M2C_UNK func_8213E6BC(s8 *);                      /* extern */
M2C_UNK func_82140228(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_821437E0(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_82146314(s8 *);                      /* extern */

/**
 * Particle callback of the Ember animation. Player sweep (all 165 moves used in battle): only
 * Ember reached this function.
 */
void BattleAnim_EmberParticleUpdateA(s8 *arg0) {
    s16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_82146314(arg0);
        return;
    case 2:
        func_8213CA80(arg0, 1);
        return;
    case 3:
        Particle_AnimateFramesForwardLoopedThenAdvance(arg0, 0, 3, 1, 2, 0);
        func_8213E6BC(arg0);
        func_821437E0(arg0, 0, 0x20);
        func_82140228(arg0, 0x3FC00000, 0x3DCCCCCD);
        return;
    case 4:
        Particle_MarkInactive(arg0);
        return;
    }
}

/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Ember.
 */
void BattleAnim_SetupEmberUseEffect(Particle* arg0) {
    Vec3s sp28;
    UNUSED s32 pad[1]; // FAKE: stack padding

    Particle_FieldCF_GetS16_0C058(arg0);
    Particle_FieldAC_GetS16_0C038(arg0);
    Particle_SetScaleScaled(arg0, 0.45f);
    sp28.x = ParticleMath_RandomSigned(0x2000);
    sp28.y = ParticleMath_RandomSignedOffset(0x3000, 0);
    sp28.z = 0;
    Particle_Field94_AddVecFromVec3s_0A4F0(arg0, sp28);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, 0x1D);
    Particle_SetPrimAlpha(arg0, 0x64);
    Particle_Field74_SetScaled_0AD8C(arg0, 2.5f);
    Particle_AdvanceLifecycle(arg0);
}

s32 Particle_ApproachStepMagnitude(Particle* arg0, f32 arg1, f32 arg2);
/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Ember.
 */
void BattleAnim_RunEmberUseEffect(Particle* arg0) {
    switch (arg0->lifecycle) {
        case 1:
            BattleAnim_SetupEmberUseEffect(arg0);
            break;

        case 2:
            Particle_AnimateFramesForwardLoopedThenAdvance(arg0, 0, 7, 1, 2, 0);
            Particle_ApproachStepMagnitude(arg0, 0.5, 0.5f);
            Particle_PrimAlpha_Approach_0BC2C(arg0, 0x20, 4);
            break;

        case 3:
            Particle_MarkInactive(arg0);
            break;
    }

    if (Particle_IsRunning(arg0) != 0) {
        Particle_ApproachScale(arg0, 0.75f, 0.1f);
        Particle_AddVelocityFromRotationTemplate1(arg0);
        ParticleGfx_ApproachPrimEnvPalettePair(arg0, 0x1A, 0x10);
    }
}

/**
 * Handles config for explosion effects when using Fire Punch, Ember, and Egg bomb
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Egg Bomb, Ember and Fire Punch, the three moves the comment names; Explosion and
 * Selfdestruct did not use it.
 */
void BattleAnim_GetExplosionParticleColor(Particle* arg0, u8 arg1) {
    u16 sp1E;

    Particle_FieldCF_SetU8Alt_0BEF8(arg0, arg1);

    switch (arg1) {
        case 0:
            sp1E = 0x1A;
            break;

        case 1:
            sp1E = 0x2A;
            break;

        case 2:
            sp1E = 0x24;
            break;

        case 3:
            sp1E = 0x2C;
            break;
    }

    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, sp1E);
}

/**
 * Empty.
 */
void func_82146674(void) {
}

/**
 * Moves: Egg Bomb (hit), Ember (hit), Fire Punch (hit)
 * TODO: Human contributor add screenshot
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Fire Punch, Ember, Egg Bomb.
 */
void BattleAnim_FirePunchEmberEggBombColorChange(Particle* arg0) {
    UNUSED u16 pad; // FAKE: stack padding
    u16 sp1C;
    u16 sp1A;

    switch (Particle_FieldCF_GetS16_0C058(arg0)) {
        case 0:
            sp1C = 0x2E;
            sp1A = 0x10;
            break;

        case 1:
            sp1C = 0x2D;
            sp1A = 0x10;
            break;

        case 2:
            sp1C = 0x2D;
            sp1A = 0x10;
            break;

        case 3:
            sp1C = 0x2B;
            sp1A = 0x10;
            break;
    }

    ParticleGfx_ApproachPrimEnvPalettePair(arg0, sp1C, sp1A);
}

/**
 * Seen in play (2026-11-12): in the per-move sweep it ran only for Egg Bomb (not for Explosion or
 * Selfdestruct).
 */
void BattleAnim_SetupBackgroundBombExplosion(Particle* arg0) {
    s16 sp26 = Particle_FieldAC_GetS16_0C038(arg0);
    s16 sp24 = Particle_FieldCF_GetS16_0C058(arg0);
    s16 sp22 = Particle_FieldCE_GetS32_0C040(arg0);

    switch (sp26) {
        case 0:
            Particle_SetPosition(arg0, 0.0f, -5.0f, 0.0f);
            break;

        case 1:
            Particle_SetPosition(arg0, 0.0f, 5.0f, 5.0f);
            break;

        case 2:
            Particle_SetPosition(arg0, 0.0f, 5.0f, -5.0f);
            break;
    }

    switch (sp22) {
        case 0:
            Particle_SetScaleScaled(arg0, 0.5f);
            Particle_SetScaleTarget(arg0, 1.0f);
            Particle_SetScaleStep(arg0, 0.1f);
            break;

        case 1:
            Particle_SetScaleScaled(arg0, 0.75f);
            Particle_SetScaleTarget(arg0, 1.5f);
            Particle_SetScaleStep(arg0, 0.15f);
            break;

        case 2:
            Particle_SetScaleScaled(arg0, 1.0f);
            Particle_SetScaleTarget(arg0, 2.0f);
            Particle_SetScaleStep(arg0, 0.2f);
            break;
    }

    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, sp24);
    Particle_SetTextureFrame(arg0, 1);
    Particle_SetPrimAlpha(arg0, 0xC8);
    Particle_FieldA6_SetS16_0BCA8(arg0, sp26 * 2);
    Particle_DisableRendering(arg0);
    Particle_AdvanceLifecycle(arg0);
}

/**
 * Handles the large background explosion when being hit by egg bomb
 * Seen in play (2026-11-12): in the per-move sweep it ran only for Egg Bomb (not for Explosion or
 * Selfdestruct).
 */
void BattleAnim_RunBackgroundBombExplosion(Particle* arg0) {
    switch (arg0->lifecycle) {
        case 1:
            BattleAnim_SetupBackgroundBombExplosion(arg0);
            break;

        case 2:
            if (Particle_DecrementUnkA6ToZeroThenAdvance(arg0) != 0) {
                Particle_EnableRendering(arg0);
            }
            break;

        case 3:
            Particle_ApproachScaleTarget(arg0);
            Particle_AnimateFramesForwardLoopedThenAdvance(arg0, 2, 7, 1, 1, 0);
            if (arg0->textureFrame >= 6) {
                Particle_PrimAlpha_Approach_0BC2C(arg0, 0x64, 0x4E);
            }
            break;

        case 4:
            Particle_MarkInactive(arg0);
            break;
    }
}

/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Explosion and Selfdestruct.
 */
void BattleAnim_SetupBoomSmallExplosion(Particle* arg0) {
    Vec3f sp2C;
    s16 sp2A;
    s16 sp28;

    sp2A = Particle_FieldAC_GetS16_0C038(arg0);
    sp28 = Particle_FieldCF_GetS16_0C058(arg0);
    sp2C.x = ParticleMath_RandomSigned(0xA);
    sp2C.y = ParticleMath_RandomSignedOffset(0xF, 0xA);
    sp2C.z = ParticleMath_RandomSigned(0xF);
    Particle_Field38_AddVecScaledFromVec3f_08D78(arg0, sp2C);
    Particle_Field74_SetScaled_0AD8C(arg0, (ParticleMath_RandomRange(5) * 0.25f) + 3.0f);
    Particle_SetScaleScaled(arg0, 0.75f);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, sp28);
    Particle_SetPrimAlpha(arg0, 0xFF);
    Particle_FieldA6_SetS16_0BCA8(arg0, sp2A * 2);
    Particle_DisableRendering(arg0);
    Particle_AdvanceLifecycle(arg0);
}

M2C_UNK Particle_GetUnkCE();                            /* extern */
void Particle_MarkInactive(s8 *arg0);                      /* extern */
M2C_UNK func_8213CB3C(s8 *);                      /* extern */
M2C_UNK Particle_AnimateFramesForwardLoopedThenAdvance(s8 *, M2C_UNK, M2C_UNK, M2C_UNK, s32, s32); /* extern */
M2C_UNK func_8213E6BC(s8 *);                      /* extern */
M2C_UNK func_821402B8(s8 *);                      /* extern */
M2C_UNK Particle_ApproachPrimAlpha(s8 *, M2C_UNK, M2C_UNK);    /* extern */
s32 func_821406B4(s8 *);                          /* extern */
M2C_UNK func_821469BC(s8 *);                      /* extern */

/**
 * Handles the smaller explosions being hit by Explosion and Self-destruct (Boom)
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Explosion and Selfdestruct.
 */
void BattleAnim_RunBoomSmallExplosion(s8 *arg0) {
    s16 temp_v1;

    Particle_GetUnkCE();
    temp_v1 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v1) {                              /* irregular */
    case 1:
        func_821469BC(arg0);
        return;
    case 2:
        if (func_821406B4(arg0) != 0) {
            func_8213CB3C(arg0);
            return;
        }
        return;
    case 3:
        func_8213E6BC(arg0);
        func_821402B8(arg0);
        Particle_AnimateFramesForwardLoopedThenAdvance(arg0, 1, 7, 1, 1, 0);
        if (M2C_FIELD(arg0, s8 *, 0xC3) >= 6) {
            Particle_ApproachPrimAlpha(arg0, 0x64, 0x4E);
        }
        if (M2C_FIELD(arg0, s8 *, 0xC3) >= 4) {
            return;
        }
        break;
    case 4:
        Particle_MarkInactive(arg0);
        break;
    }
}

/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Egg Bomb.
 */
void BattleAnim_SetupEggBombHitEffect(Particle* arg0) {
    Vec3s sp30;
    Vec3f sp24;
    s16 sp22;
    s16 sp20;

    sp22 = Particle_FieldAC_GetS16_0C038(arg0);
    sp20 = Particle_FieldCF_GetS16_0C058(arg0);
    sp24.x = ParticleMath_RandomSigned(0xA);
    sp24.y = ParticleMath_RandomSignedOffset(0xA, 5);
    sp24.z = ParticleMath_RandomSigned(0xA);
    Particle_Field38_AddVecScaledFromVec3f_08D78(arg0, sp24);
    Particle_SetScaleScaled(arg0, 1.0f);
    Particle_Field74_SetScaled_0AD8C(arg0, 0.5f);
    sp30.x = ParticleMath_RandomSigned(0x2000);
    sp30.y = ParticleMath_RandomSigned(0x2000);
    sp30.z = 0;
    Particle_Field94_AddVecFromVec3s_0A4F0(arg0, sp30);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, sp20);
    Particle_SetPrimAlpha(arg0, 0xC8);
    Particle_FieldA6_SetS16_0BCA8(arg0, sp22 * 2);
    Particle_SetTextureFrame(arg0, 2);
    Particle_DisableRendering(arg0);
    Particle_AdvanceLifecycle(arg0);
}

void Particle_DisableAndDetach(s8 *arg0);                      /* extern */
M2C_UNK func_8213CB3C(s8 *);                      /* extern */
M2C_UNK Particle_AnimateFramesForwardLoopedThenAdvance(s8 *, M2C_UNK, M2C_UNK, M2C_UNK, s32, s32); /* extern */
void Particle_AddVelocityFromRotationTemplate1(s32 arg0);                      /* extern */
M2C_UNK func_82140228(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK Particle_ApproachPrimAlpha(s8 *, M2C_UNK, M2C_UNK);    /* extern */
s32 func_821406B4(s8 *);                          /* extern */
M2C_UNK func_82146BEC(s8 *);                      /* extern */

void BattleAnim_CallbackEndEffect40Descriptor48SpreadScaleAlphaFade(s8 *arg0) {
    s16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_82146BEC(arg0);
        return;
    case 2:
        if (func_821406B4(arg0) != 0) {
            func_8213CB3C(arg0);
            return;
        }
        return;
    case 3:
        Particle_AnimateFramesForwardLoopedThenAdvance(arg0, 2, 7, 1, 1, 0);
        func_82140228(arg0, 0x3F99999A, 0x3D4CCCCD);
        Particle_ApproachPrimAlpha(arg0, 0x64, 0x10);
        Particle_AddVelocityFromRotationTemplate1(arg0);
        return;
    case 4:
        Particle_DisableAndDetach(arg0);
        break;
    }
}

/**
 * Seen in play (2026-11-12): in the per-move sweep it ran only for Egg Bomb (not for Explosion or
 * Selfdestruct).
 */
void BattleAnim_SetupSecondaryBombExplosion(Particle* arg0) {
    s16 sp36 = Particle_FieldAC_GetS16_0C038(arg0);
    Vec3s sp30;
    UNUSED s32 pad[3]; // FAKE: stack padding

    Particle_SetRandomVelocityXYZ(arg0, 5, 5, 5);
    Particle_SetScaleScaled(arg0, 0.5f);
    Particle_Field74_SetScaled_0AD8C(arg0, 1.0f);
    sp30.x = 0x2000 - ParticleMath_RandomRange(0x4000);
    sp30.y = 0x2000 - ParticleMath_RandomRange(0x4000);
    sp30.z = 0;
    Particle_Field94_AddVecFromVec3s_0A4F0(arg0, sp30);
    Particle_AddRotationTargetXY(arg0, sp30.x, sp30.y);
    Particle_Field9A_SetXY_0A3A0(arg0, 0, 0);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, 0x1A);
    Particle_SetPrimAlpha(arg0, 0xC8);
    Particle_FieldA6_SetS16_0BCA8(arg0, sp36 * 3);
    Particle_DisableRendering(arg0);
    Particle_AdvanceLifecycle(arg0);
}

void Particle_DisableAndDetach(s8 *arg0);                      /* extern */
M2C_UNK func_8213C9D0(s8 *);                      /* extern */
M2C_UNK func_8213CB3C(s8 *);                      /* extern */
M2C_UNK Particle_AddPosOffsetYScaled(s8 *, M2C_UNK);             /* extern */
void Particle_AddVelocityFromRotationTemplate1(s32 arg0);                      /* extern */
M2C_UNK func_82140228(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK Particle_ApproachPrimRed(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK Particle_ApproachPrimGreen(s8 *, M2C_UNK, M2C_UNK);    /* extern */
s32 Particle_ApproachPrimAlpha(s8 *, M2C_UNK, M2C_UNK);        /* extern */
M2C_UNK Particle_SetUnkA6(s8 *, M2C_UNK);             /* extern */
s32 func_82140690(s8 *);                          /* extern */
s32 func_821406B4(s8 *);                          /* extern */
M2C_UNK func_8214667C(s8 *);                      /* extern */
M2C_UNK func_82146E1C(s8 *);                      /* extern */

/**
 * Handles secondary explosion from being hit by egg bomb
 * Seen in play (2026-11-12): in the per-move sweep it ran only for Egg Bomb (not for Explosion or
 * Selfdestruct).
 */
void BattleAnim_RunSecondaryBombExplosion(s8 *arg0) {
    s16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_82146E1C(arg0);
        return;
    case 2:
        if (func_821406B4(arg0) != 0) {
            Particle_SetUnkA6(arg0, 0xA);
            func_8213CB3C(arg0);
            return;
        }
        return;
    case 3:
        func_82140228(arg0, 0x3F800000, 0x3DCCCCCD);
        Particle_ApproachPrimRed(arg0, 0, 0xC);
        Particle_ApproachPrimGreen(arg0, 0, 0x20);
        Particle_AddVelocityFromRotationTemplate1(arg0);
        Particle_AddPosOffsetYScaled(arg0, 0x3ECCCCCD);
        func_8214667C(arg0);
        if ((func_82140690(arg0) != 0) && (Particle_ApproachPrimAlpha(arg0, 0x20, 0x10) != 0)) {
            func_8213C9D0(arg0);
            return;
        }
        break;
    case 4:
        Particle_DisableAndDetach(arg0);
        break;
    }
}

/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Ember.
 */
void BattleAnim_SetupEmberHitFireball(Particle* arg0) {
    s16 sp36 = Particle_FieldAC_GetS16_0C038(arg0);
    Vec3s sp30;
    Vec3f sp24;

    sp24.x = ParticleMath_RandomSigned(0x19);
    sp24.y = ParticleMath_RandomSignedOffset(0xF, 5);
    sp24.z = ParticleMath_RandomSigned(0xA);
    Particle_Field38_AddVecScaledFromVec3f_08D78(arg0, sp24);
    Particle_SetScaleScaled(arg0, 0.15f);
    Particle_Field74_SetScaled_0AD8C(arg0, 0.5f);
    sp30.x = 0x2000 - ParticleMath_RandomRange(0x4000);
    sp30.y = 0x2000 - ParticleMath_RandomRange(0x4000);
    sp30.z = 0;
    Particle_Field94_AddVecFromVec3s_0A4F0(arg0, sp30);
    Particle_AddRotationTargetXY(arg0, sp30.x, sp30.y);
    Particle_Field9A_SetXY_0A3A0(arg0, 0, 0);
    BattleAnim_GetExplosionParticleColor(arg0, (sp36 % 4) & 0xFF);
    Particle_SetPrimAlpha(arg0, 0xC8);
    Particle_FieldA6_SetS16_0BCA8(arg0, sp36 * 1); // FAKE: no-op * 1
    Particle_SetTextureFrame(arg0, 2);
    Particle_DisableRendering(arg0);
    Particle_AdvanceLifecycle(arg0);
}

void Particle_DisableAndDetach(s8 *arg0);                      /* extern */
M2C_UNK func_8213CB3C(s8 *);                      /* extern */
M2C_UNK Particle_AnimateFramesForwardLoopedThenAdvance(s8 *, M2C_UNK, M2C_UNK, M2C_UNK, s32, s32); /* extern */
void Particle_AddVelocityFromRotationTemplate1(s32 arg0);                      /* extern */
M2C_UNK func_82140228(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK Particle_ApproachPrimAlpha(s8 *, M2C_UNK, M2C_UNK);    /* extern */
s32 func_821406B4(s8 *);                          /* extern */
M2C_UNK func_82147050(s8 *);                      /* extern */

void BattleAnim_CallbackEndEffect56Descriptor46RisingScaleAlphaFade(s8 *arg0) {
    s16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_82147050(arg0);
        return;
    case 2:
        if (func_821406B4(arg0) != 0) {
            func_8213CB3C(arg0);
            return;
        }
        return;
    case 3:
        Particle_AnimateFramesForwardLoopedThenAdvance(arg0, 2, 7, 1, 1, 0);
        func_82140228(arg0, 0x3EE66667, 0x3D99999A);
        Particle_ApproachPrimAlpha(arg0, 0x64, 0x10);
        Particle_AddVelocityFromRotationTemplate1(arg0);
        return;
    case 4:
        Particle_DisableAndDetach(arg0);
        break;
    }
}

/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Ember.
 */
void BattleAnim_SetupEmberHitSmoke(Particle* arg0) {
    s16 sp36 = Particle_FieldAC_GetS16_0C038(arg0);
    Vec3s sp30;
    UNUSED s32 pad[3]; // FAKE: stack padding

    Particle_SetRandomVelocityXYZ(arg0, 5, 0xA, 0xA);
    Particle_SetScaleScaled(arg0, 0.90000004f);
    Particle_Field74_SetScaled_0AD8C(arg0, 1.0f);
    sp30.x = ParticleMath_RandomSigned(0x2000);
    sp30.y = ParticleMath_RandomRange(0x10000);
    sp30.z = 0;
    Particle_Field94_AddVecFromVec3s_0A4F0(arg0, sp30);
    BattleAnim_GetExplosionParticleColor(arg0, (sp36 % 4) & 0xFF);
    Particle_SetPrimAlpha(arg0, 0xC8);
    Particle_FieldA6_SetS16_0BCA8(arg0, 0);
    Particle_SetTextureFrame(arg0, 2);
    Particle_DisableRendering(arg0);
    Particle_AdvanceLifecycle(arg0);
}

s32 Particle_ApproachStepMagnitude(Particle* arg0, f32 arg1, f32 arg2);
/**
 * Seen in play (2026-11-13) in the 165-move sweep (each move used once by the 1P Pokémon): it ran
 * only for Ember.
 */
void BattleAnim_EmberSpreadScaleAlphaRise(Particle* arg0) {
    switch (arg0->lifecycle) {
        case 1:
            BattleAnim_SetupEmberHitSmoke(arg0);
            break;

        case 2:
            if (Particle_DecrementUnkA6ToZeroThenAdvance(arg0) != 0) {
                Particle_FieldA6_SetS16_0BCA8(arg0, 5);
                Particle_EnableRendering(arg0);
            }
            break;

        case 3:
            Particle_AnimateFramesForwardLoopedThenAdvance(arg0, 0, 7, 1, 2, 0);
            Particle_ApproachScale(arg0, 1.05f, 0.075f);
            Particle_ApproachStepMagnitude(arg0, 0.5, 0.5f);
            Particle_AddVelocityFromRotationTemplate1(arg0);
            if (Particle_DecrementUnkA6ToZero(arg0) != 0) {
                func_8213E1FC(arg0, 0x3F000000);
                Particle_PrimAlpha_Approach_0BC2C(arg0, 0x64, 0x10);
            }
            break;

        case 4:
            Particle_MarkInactive(arg0);
            break;
    }
}

/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Fire Punch, Ember.
 */
void BattleAnim_SetupFirePunchLingeringHitSpark(Particle* arg0) {
    s16 sp36 = Particle_FieldAC_GetS16_0C038(arg0);
    Vec3s sp30;
    UNUSED s32 pad[3]; // FAKE: stack padding

    Particle_SetRandomVelocityXYZ(arg0, 5, 5, 5);
    Particle_SetScaleScaled(arg0, 0.75f);
    Particle_Field74_SetScaled_0AD8C(arg0, 1.0f);
    sp30.x = 0x2000 - ParticleMath_RandomRange(0x4000);
    sp30.y = ParticleMath_RandomRange(0x10000);
    sp30.z = 0;
    Particle_Field94_AddVecFromVec3s_0A4F0(arg0, sp30);
    Particle_AddRotationTargetXY(arg0, sp30.x, sp30.y);
    Particle_Field9A_SetXY_0A3A0(arg0, 0, 0);
    BattleAnim_GetExplosionParticleColor(arg0, (sp36 % 4) & 0xFF);
    Particle_SetPrimAlpha(arg0, 0xC8);
    Particle_FieldA6_SetS16_0BCA8(arg0, sp36 * 3);
    Particle_DisableRendering(arg0);
    Particle_AdvanceLifecycle(arg0);
}

void Particle_DisableAndDetach(s8 *arg0);                      /* extern */
M2C_UNK func_8213C9D0(s8 *);                      /* extern */
M2C_UNK func_8213CB3C(s8 *);                      /* extern */
M2C_UNK Particle_AddPosOffsetYScaled(s8 *, M2C_UNK);             /* extern */
void Particle_AddVelocityFromRotationTemplate1(s32 arg0);                      /* extern */
M2C_UNK func_82140228(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK Particle_ApproachPrimRed(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK Particle_ApproachPrimGreen(s8 *, M2C_UNK, M2C_UNK);    /* extern */
s32 Particle_ApproachPrimAlpha(s8 *, M2C_UNK, M2C_UNK);        /* extern */
M2C_UNK Particle_SetUnkA6(s8 *, M2C_UNK);             /* extern */
s32 func_82140690(s8 *);                          /* extern */
s32 func_821406B4(s8 *);                          /* extern */
M2C_UNK func_8214667C(s8 *);                      /* extern */
M2C_UNK func_821474CC(s8 *);                      /* extern */

/**
 * Creates the lingering hit spark when hit by fire punch or ember
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Fire Punch, Ember.
 */
void BattleAnim_RunFirePunchLingeringHitSpark(s8 *arg0) {
    s16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_821474CC(arg0);
        return;
    case 2:
        if (func_821406B4(arg0) != 0) {
            Particle_SetUnkA6(arg0, 0xA);
            func_8213CB3C(arg0);
            return;
        }
        return;
    case 3:
        Particle_ApproachPrimRed(arg0, 0, 0xC);
        Particle_ApproachPrimGreen(arg0, 0, 0x20);
        func_82140228(arg0, 0x3FC00000, 0x3E19999A);
        func_8214667C(arg0);
        Particle_AddVelocityFromRotationTemplate1(arg0);
        Particle_AddPosOffsetYScaled(arg0, 0x3ECCCCCD);
        if ((func_82140690(arg0) != 0) && (Particle_ApproachPrimAlpha(arg0, 0x20, 0x10) != 0)) {
            func_8213C9D0(arg0);
            return;
        }
        break;
    case 4:
        Particle_DisableAndDetach(arg0);
        break;
    }
}

/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Egg Bomb and Fire Punch.
 */
void BattleAnim_SetupAfterImpactSmoke(Particle* arg0) {
    s16 sp36;
    Vec3s sp30;
    Vec3f sp24;

    sp36 = Particle_FieldAC_GetS16_0C038(arg0);
    sp24.x = ParticleMath_RandomSigned(0x14);
    sp24.y = ParticleMath_RandomSignedOffset(0xF, 0xA);
    sp24.z = ParticleMath_RandomSigned(0xF);
    Particle_Field38_AddVecScaledFromVec3f_08D78(arg0, sp24);
    Particle_SetScaleScaled(arg0, 0.1f);
    sp30.x = ParticleMath_RandomRange(0x10000);
    sp30.y = ParticleMath_RandomRange(0x10000);
    sp30.z = 0;
    Particle_Field94_AddVecFromVec3s_0A4F0(arg0, sp30);
    Particle_AddRotationTargetXY(arg0, sp30.x, sp30.y);
    Particle_Field9A_SetXY_0A3A0(arg0, 0, 0);
    BattleAnim_GetExplosionParticleColor(arg0, (sp36 % 4) & 0xFF);
    Particle_SetPrimAlpha(arg0, 0xC8);
    Particle_FieldA6_SetS16_0BCA8(arg0, sp36 * 2);
    Particle_SetTextureFrame(arg0, 2);
    Particle_DisableRendering(arg0);
    Particle_AdvanceLifecycle(arg0);
}

void Particle_DisableAndDetach(s8 *arg0);                      /* extern */
M2C_UNK func_8213CB3C(s8 *);                      /* extern */
M2C_UNK Particle_AnimateFramesForwardLoopedThenAdvance(s8 *, M2C_UNK, M2C_UNK, M2C_UNK, s32, s32); /* extern */
M2C_UNK func_82140228(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK Particle_ApproachPrimAlpha(s8 *, M2C_UNK, M2C_UNK);    /* extern */
s32 func_821406B4(s8 *);                          /* extern */
M2C_UNK func_82147710(s8 *);                      /* extern */

/**
 * Handles the dissipating and spreading smoke from being hit by fire punch and egg bomb
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Egg Bomb and Fire Punch.
 */
void BattleAnim_RunAfterImpactSmoke(s8 *arg0) {
    s16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_82147710(arg0);
        return;
    case 2:
        if (func_821406B4(arg0) != 0) {
            func_8213CB3C(arg0);
            return;
        }
        return;
    case 3:
        Particle_AnimateFramesForwardLoopedThenAdvance(arg0, 2, 7, 1, 1, 0);
        func_82140228(arg0, 0x3E99999A, 0x3D4CCCCD);
        Particle_ApproachPrimAlpha(arg0, 0x64, 0x10);
        return;
    case 4:
        Particle_DisableAndDetach(arg0);
        break;
    }
}

/**
 * handles the small bursts of fire that appear when hit by fire punch
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Fire Punch.
 */
void BattleAnim_SetupFirePunchHitEffect(Particle* arg0) {
    s16 temp_s1 = Particle_FieldAC_GetS16_0C038(arg0);

    Particle_SetScaleScaled(arg0, 0.75f);

    switch (temp_s1) {
        case 0:
            Particle_SetPosition(arg0, 0.0f, -3.0f, 0.0f);
            break;

        case 1:
            Particle_SetPosition(arg0, 0.0f, 3.0f, 3.0f);
            break;

        case 2:
            Particle_SetPosition(arg0, 0.0f, 3.0f, -3.0f);
            break;
    }

    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, 0x17);
    Particle_SetPrimAlpha(arg0, 0xFF);
    Particle_FieldA6_SetS16_0BCA8(arg0, temp_s1 * 4);
    Particle_DisableRendering(arg0);
    Particle_AdvanceLifecycle(arg0);
}

void Particle_MarkInactive(s8 *arg0);                      /* extern */
M2C_UNK func_8213CB3C(s8 *);                      /* extern */
M2C_UNK Particle_AnimateFramesForwardLoopedThenAdvance(s8 *, M2C_UNK, M2C_UNK, M2C_UNK, s32, s32); /* extern */
M2C_UNK func_82140228(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK Particle_ApproachPrimGreen(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK Particle_ApproachPrimBlue(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK Particle_ApproachEnvGreen(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK Particle_ApproachPrimAlpha(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_8214795C(s8 *);                      /* extern */

/**
 * handles the small bursts of fire that appear when hit by fire punch
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Fire Punch.
 */
void BattleAnim_RunFirePunchHitEffect(s8 *arg0) {
    s16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_8214795C(arg0);
        return;
    case 2:
        if (func_8213CA80(arg0, M2C_FIELD(arg0, s16 *, 0xA2)) != 0) {
            func_8213CB3C(arg0);
            return;
        }
        return;
    case 3:
        Particle_AnimateFramesForwardLoopedThenAdvance(arg0, 0, 7, 1, 1, 0);
        func_82140228(arg0, 0x3F800000, 0x3CA3D70A);
        Particle_ApproachPrimBlue(arg0, 0, 0x20);
        Particle_ApproachEnvGreen(arg0, 0, 0x20);
        if (M2C_FIELD(arg0, s8 *, 0xC3) >= 6) {
            Particle_ApproachPrimGreen(arg0, 0, 0x20);
            Particle_ApproachPrimAlpha(arg0, 0x64, 0x4E);
            return;
        }
        break;
    case 4:
        Particle_MarkInactive(arg0);
        break;
    }
}

/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Flamethrower, Dragon Rage.
 */
void BattleAnim_SetupFlamethrowerHitRotation(Particle* arg0, s16 arg1, s16 arg2) {
    UNUSED s32 pad[2]; // FAKE: stack padding
    s16 sp26 = Particle_FieldAC_GetS16_0C038(arg0);

    Particle_Field38_SetYScaled_08CA0(arg0, -10.0f);
    Particle_AddPositionOffsetAlongRotationY(arg0, 50.0f);
    Particle_SetScaleScaled(arg0, 0.5f);
    Particle_Field74_SetScaled_0AD8C(arg0, 5.0f);

    switch (arg1) {
        case 0:
            Particle_Field94_AddX_0A578(arg0, ParticleMath_RandomSigned(0x800));
            Particle_Field94_AddY_0A594(arg0, ParticleMath_RandomSignedOffset(0x1000, 0x8000));
            break;

        case 1:
            Particle_Field94_AddX_0A578(arg0, ParticleMath_RandomSigned(0xA00));
            Particle_Field94_AddY_0A594(arg0, ParticleMath_RandomSignedOffsetBySign(0xD00, 0xF400) + 0x8000);
            break;
    }

    switch (arg2) {
        case 0:
            ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, 0x1A);
            break;

        case 1:
            ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, 6);
            break;
    }

    Particle_SetPrimAlpha(arg0, 0xC8);
    Particle_FieldA6_SetS16_0BCA8(arg0, sp26 * 4);
    Particle_DisableRendering(arg0);
    Particle_AdvanceLifecycle(arg0);
}

/**
 * Handles Positioning the flames from getting hit by flamethrower or dragon rage
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Flamethrower, Dragon Rage.
 */
void BattleAnim_RunFlamethrowerHitRotation(Particle* arg0, s32 arg1) {
    s16 temp_v0 = Particle_FieldCF_GetS16_0C058(arg0);

    switch (arg0->lifecycle) {
        case 1:
            BattleAnim_SetupFlamethrowerHitRotation(arg0, arg1, temp_v0);
            break;

        case 2:
            if (Particle_DecrementUnkA6ToZeroThenAdvance(arg0) != 0) {
                Particle_EnableRendering(arg0);
            }
            break;

        case 3:
            Particle_FieldA6_SetS16_0BCA8(arg0, 12);
            Particle_AdvanceLifecycle(arg0);
            break;

        case 4:
            switch (temp_v0) {
                case 0:
                    Particle_PrimG_Approach_0BB14(arg0, 0, 0x10);
                    Particle_EnvR_Approach_0BB90(arg0, 0, 0x10);
                    break;

                case 1:
                    Particle_PrimG_Approach_0BB14(arg0, 0, 0xA);
                    Particle_EnvG_Approach_0BBF0(arg0, 0, 5);
                    break;
            }

            if ((Particle_DecrementUnkA6ToZero(arg0) != 0) && (Particle_PrimAlpha_Approach_0BC2C(arg0, 0, 0x18) != 0)) {
                Particle_AdvanceLifecycle(arg0);
            }
            break;

        case 5:
            Particle_DisableAndDetach(arg0);
            break;
    }

    if (Particle_IsRenderingEnabled(arg0) != 0) {
        Particle_ApproachRotationXTo(arg0, -0xC00, 0x100);
        Particle_ApproachScale(arg0, 1.2f, 0.04f);
        Particle_AddVelocityFromRotationTemplate1(arg0);
        Particle_AnimateFramesForwardLooped(arg0, 0, 7, 1, 2, -1);
    }
}

/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Flamethrower, Dragon Rage.
 */
void BattleAnim_RunFlamethrowerHitRotationWeak(Particle* arg0) {
    BattleAnim_RunFlamethrowerHitRotation(arg0, 0);
}

/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Flamethrower, Dragon Rage.
 */
void BattleAnim_RunFlamethrowerHitRotationStrong(Particle* arg0) {
    BattleAnim_RunFlamethrowerHitRotation(arg0, 1);
}

/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Flamethrower, Dragon Rage, Fire Blast.
 */
void BattleAnim_SetupFireBlastHitFrontFlames(Particle* arg0) {
    s16 sp36 = Particle_FieldCF_GetS16_0C058(arg0);
    UNUSED s32 pad[3]; // FAKE: stack padding
    s16 sp26 = Particle_FieldAC_GetS16_0C038(arg0);

    Particle_SetScaleScaled(arg0, 0.4f);
    Particle_AddPositionOffsetAlongRotationY(arg0, 15.0f);
    Particle_Field94_AddX_0A578(arg0, ParticleMath_RandomSignedOffset(0x200, 0xE00));
    Particle_Field94_AddY_0A594(arg0, ParticleMath_RandomSignedOffset(0x3800, 0x8000));
    Particle_FieldA0_SetX_0A400(arg0, -0x4000);
    Particle_Field9A_SetX_0A3C4(arg0, 0x1000);
    Particle_Field74_SetScaled_0AD8C(arg0, 3.0f);

    switch (sp36) {
        case 0:
            ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, 0x1A);
            break;

        case 1:
            ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, 6);
            break;
    }

    Particle_SetPrimAlpha(arg0, 0xC8);
    Particle_FieldA6_SetS16_0BCA8(arg0, sp26 * 2);
    Particle_DisableRendering(arg0);
    Particle_AdvanceLifecycle(arg0);
}

/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Flamethrower, Dragon Rage, Fire Blast.
 */
void BattleAnim_ContinueFireBlastHitFrontFlames(Particle* arg0) {
    switch (arg0->phase) {
        case 1:
            if (Particle_TickPhaseTimer(arg0, 1) != 0) {
                Particle_AdvancePhase(arg0);
            }
            break;

        case 2:
            Particle_ApproachRotationTargetX(arg0);
            if (Particle_TickPhaseTimer(arg0, 0x10) != 0) {
                Particle_AdvancePhase(arg0);
            }
            break;
    }

    if (arg0->phase > 0) {
        Particle_AddVelocityFromRotationTemplate1(arg0);
    }
}

void Particle_MarkInactive(s8 *arg0);                      /* extern */
M2C_UNK func_8213CB3C(s8 *);                      /* extern */
s32 func_8213CB7C(s8 *);                          /* extern */
M2C_UNK Particle_AnimateFramesForwardLoopedThenAdvance(s8 *, M2C_UNK, M2C_UNK, M2C_UNK, s32, s32); /* extern */
M2C_UNK func_8213D238(s8 *);                      /* extern */
M2C_UNK func_82140228(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK Particle_ApproachPrimAlpha(s8 *, M2C_UNK, M2C_UNK);    /* extern */
s32 func_821406B4(s8 *);                          /* extern */
M2C_UNK func_82147ED0(s8 *);                      /* extern */
M2C_UNK func_82147FF0(s8 *);                      /* extern */

void func_82148090(s8 *arg0) {
    s16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_82147ED0(arg0);
        break;
    case 2:
        if (func_821406B4(arg0) != 0) {
            func_8213D238(arg0);
            func_8213CB3C(arg0);
        }
        break;
    case 3:
        Particle_AnimateFramesForwardLoopedThenAdvance(arg0, 0, 7, 1, 2, 0);
        Particle_ApproachPrimAlpha(arg0, 0x20, 4);
        func_82140228(arg0, 0x3F99999A, 0x3DCCCCCD);
        break;
    case 4:
        Particle_MarkInactive(arg0);
        break;
    }
    if (func_8213CB7C(arg0) != 0) {
        func_82147FF0(arg0);
    }
}

/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Fire Blast.
 */
void BattleAnim_SetupDaimonji(Particle* arg0) {
    UNUSED s32 pad[3]; // FAKE: stack padding
    s16 sp22 = Particle_FieldAC_GetS16_0C038(arg0);
    s16 sp20 = Particle_FieldCF_GetS16_0C058(arg0);

    Particle_SetScaleScaled(arg0, 0.6f);
    Particle_Field38_AddYScaled_08E90(arg0, 15.0f);
    Particle_AddPositionOffsetAlongRotationYPlus180(arg0, 20.0f);

    switch (sp20) {
        case 0:
            Particle_Field74_SetScaled_0AD8C(arg0, 1.5f);
            Particle_Field94_AddX_0A578(arg0, -0x4000);
            break;

        case 1:
            Particle_Field74_SetScaled_0AD8C(arg0, 2.0f);
            Particle_Field94_AddY_0A594(arg0, 0x4000);
            Particle_Field94_AddX_0A578(arg0, -0xE00);
            break;

        case 2:
            Particle_Field74_SetScaled_0AD8C(arg0, 2.0f);
            Particle_Field94_AddY_0A594(arg0, -0x4000);
            Particle_Field94_AddX_0A578(arg0, -0xE00);
            break;

        case 3:
            Particle_Field74_SetScaled_0AD8C(arg0, 2.5f);
            Particle_Field94_AddY_0A594(arg0, 0x4000);
            Particle_Field94_AddX_0A578(arg0, 0x2000);
            break;

        case 4:
            Particle_Field74_SetScaled_0AD8C(arg0, 2.5f);
            Particle_Field94_AddY_0A594(arg0, -0x4000);
            Particle_Field94_AddX_0A578(arg0, 0x2000);
            break;
    }

    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, 0x17);
    Particle_FieldA6_SetS16_0BCA8(arg0, sp22 * 2);
    Particle_DisableRendering(arg0);
    Particle_AdvanceLifecycle(arg0);
}

/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Fire Blast.
 */
void BattleAnim_ContinueDaimonji(Particle* arg0) {
    switch (arg0->phase) {
        case 1:
            if (Particle_TickPhaseTimer(arg0, 2) != 0) {
                Particle_AdvancePhase(arg0);
            }
            break;

        case 2:
            if (Particle_TickPhaseTimer(arg0, 0x10) != 0) {
                Particle_AdvancePhase(arg0);
            }
            break;
    }

    if (arg0->phase > 0) {
        Particle_AddVelocityFromRotationTemplate5(arg0);
    }
}

/**
 * used to create the Daimonji of Fire blast that spells out 大
 * https://en.wikipedia.org/wiki/Gozan_no_Okuribi
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Fire Blast.
 */
void BattleAnim_RunDaimonji(Particle* arg0) {
    switch (arg0->lifecycle) {
        case 1:
            BattleAnim_SetupDaimonji(arg0);
            break;

        case 2:
            if (Particle_DecrementUnkA6ToZeroThenAdvance(arg0) != 0) {
                Particle_BeginPhase(arg0);
                Particle_EnableRendering(arg0);
                Particle_FieldA6_SetS16_0BCA8(arg0, 11);
            }
            break;

        case 3:
            Particle_PrimB_Approach_0BB44(arg0, 0, 0x18);
            Particle_EnvG_Approach_0BBF0(arg0, 0, 0x18);
            if (Particle_DecrementUnkA6ToZeroThenAdvance(arg0) != 0) {
                Particle_FieldA6_SetS16_0BCA8(arg0, 12);
            }
            break;

        case 4:
            Particle_PrimG_Approach_0BB14(arg0, 0, 0x10);
            Particle_EnvR_Approach_0BB90(arg0, 0, 0x10);
            if ((Particle_DecrementUnkA6ToZero(arg0) != 0) && (Particle_PrimAlpha_Approach_0BC2C(arg0, 0, 0x40) != 0)) {
                Particle_AdvanceLifecycle(arg0);
            }
            break;

        case 5:
            Particle_MarkInactive(arg0);
            break;
    }

    if (Particle_IsRenderingEnabled(arg0) != 0) {
        Particle_ApproachScale(arg0, 0.8f, 0.025f);
        Particle_AnimateFramesForwardLooped(arg0, 0, 7, 1, 2, -1);
        BattleAnim_ContinueDaimonji(arg0);
    }
}

/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Fire Blast.
 */
void BattleAnim_SetupDaimonjiColoration(Particle* arg0) {
    UNUSED s32 pad[3]; // FAKE: stack padding
    s16 sp22 = Particle_FieldAC_GetS16_0C038(arg0);

    Particle_FieldCF_GetS16_0C058(arg0);
    Particle_SetScaleScaled(arg0, 0.7f);
    Particle_SetRandomVelocityX(arg0, 0xF);
    Particle_SetRandomVelocityYOffset(arg0, 0xF, 0xA);
    Particle_SetRandomVelocityZ(arg0, 0xF);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, 0x1A);
    Particle_SetPrimAlpha(arg0, 0xC8);
    Particle_FieldA6_SetS16_0BCA8(arg0, sp22 * 4);
    Particle_DisableRendering(arg0);
    Particle_AdvanceLifecycle(arg0);
}

void Particle_MarkInactive(s8 *arg0);                      /* extern */
M2C_UNK func_8213C9D0(s8 *);                      /* extern */
M2C_UNK func_8213CB3C(s8 *);                      /* extern */
s32 func_8213CB7C(s8 *);                          /* extern */
M2C_UNK func_8213D238(s8 *);                      /* extern */
M2C_UNK func_82140228(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK Particle_ApproachPrimGreen(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK Particle_ApproachEnvRed(s8 *, M2C_UNK, M2C_UNK);    /* extern */
s32 Particle_ApproachPrimAlpha(s8 *, M2C_UNK, M2C_UNK);        /* extern */
M2C_UNK Particle_SetUnkA6(s8 *, M2C_UNK);             /* extern */
s32 func_82140690(s8 *);                          /* extern */
s32 func_821406B4(s8 *);                          /* extern */
M2C_UNK func_8214851C(s8 *);                      /* extern */

/**
 * Colors the Daimonji created when being hit by fire blast
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Fire Blast.
 */
void BattleAnim_RunDaimonjiColoration(s8 *arg0) {
    s16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_8214851C(arg0);
        break;
    case 2:
        if (func_821406B4(arg0) != 0) {
            func_8213D238(arg0);
            func_8213CB3C(arg0);
            Particle_SetUnkA6(arg0, 8);
        }
        break;
    case 3:
        Particle_ApproachPrimGreen(arg0, 0, 0x10);
        Particle_ApproachEnvRed(arg0, 0, 0x10);
        if ((func_82140690(arg0) != 0) && (Particle_ApproachPrimAlpha(arg0, 0x20, 0x18) != 0)) {
            func_8213C9D0(arg0);
        }
        break;
    case 4:
        Particle_MarkInactive(arg0);
        break;
    }
    if (func_8213CB7C(arg0) != 0) {
        func_82140228(arg0, 0x3F800000, 0x3CCCCCCD);
        Particle_AnimateFramesForwardLooped(arg0, 0, 7, 1, 2, 0);
    }
}

M2C_UNK func_8213B560(M2C_UNK, M2C_UNK *, M2C_UNK *, M2C_UNK, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_8213B794(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, s32); /* extern */
extern M2C_UNK D_8218E728;
extern M2C_UNK D_8218E770;
extern M2C_UNK D_8218E7B0;
extern s16 D_8219A80A;
extern M2C_UNK func_82146504;

/**
 * Effect init that spawns the Ember animation. Player sweep (all 165 moves used in battle): only
 * Ember reached this function.
 * Effect start init 22 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used:
 * it ran for exactly Ember.
 */
void BattleAnim_InitializeEmberUse(void) {
    func_8213B794(0, 0, 0x40, 8, 0xC8);
    func_8213B560(1, &BattleAnim_EmberParticleUpdateA, &D_8218E728, 0, 1, 0x10, (s32) D_8219A80A, 0, 0);
    func_8213B560(2, &func_82146504, &D_8218E770, 0, 3, 0x11, (s32) D_8219A80A, 0, 0);
    func_8213B560(4, &BattleAnim_RunEmberProjectile, &D_8218E7B0, 0, 1, 0x11, (s32) D_8219A80A, 0, 0);
}

extern ParticleDescriptor D_8218E588[86];
extern ParticleDescriptor D_8218E7B8;
/**
 * Effect init for the end (impact) of the Ember animation.
 * Effect end init 56 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used: it
 * ran for exactly Ember.
 */
void BattleAnim_InitializeEmberHit(void) {
    BattleAnim_SpawnDescriptor25AlphaHoldFadeOut(2, 0, 0x40, 0x8, 0xC8);
    BattleAnim_SpawnOwnerModelTintRampDetach(0, 0xA, 0xFF, 0, 0x30);
    BattleAnim_CreateEffectSlotForCurrentOwner(4, BattleAnim_CallbackEndEffect56Descriptor46RisingScaleAlphaFade, &D_8218E7B0, 0, 6, 0x10, 9, 0, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(8, BattleAnim_CallbackEndEffect56Descriptor46RisingScaleAlphaFade, &D_8218E7B0, 0, 6, 0x10, 9, 0, 0);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0, 2, 2, BattleAnim_CallbackEndEffects54And56Descriptor3DRisingColorScaleFade, &D_8218E770, 0, 4, 0x10, 9, 0, 0);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0, 2, 2, BattleAnim_EmberSpreadScaleAlphaRise, &D_8218E7B8, 0, 4, 0x10, 9, 0, 0);
}

M2C_UNK func_8213B560(M2C_UNK, M2C_UNK *, M2C_UNK *, M2C_UNK, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_8213B5D8(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK *, M2C_UNK *, s32, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_8213B794(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, s32); /* extern */
M2C_UNK func_8213BC00(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, s32); /* extern */
extern M2C_UNK D_8218E770;
extern M2C_UNK D_8218E7B0;

/**
 * initialize being hit by fire punch
 * Effect end init 54 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used: it
 * ran for exactly Fire Punch.
 */
void BattleAnim_InitializeFirePunchHit(void) {
    func_8213B794(2, 0, 0x40, 8, 0xC8);
    func_8213BC00(2, 9, 0xC8, 0, 0x10);
    func_8213B560(0, &BattleAnim_RunFirePunchHitEffect, &D_8218E7B0, 0, 3, 0x10, 9, 0, 0);
    func_8213B560(0xA, &BattleAnim_RunAfterImpactSmoke, &D_8218E7B0, 0, 8, 0x11, 9, 0, 0);
    func_8213B5D8(0xC, 2, 2, &BattleAnim_RunFirePunchLingeringHitSpark, &D_8218E770, 0, 4, 0x11, 9, 0, 0);
}

M2C_UNK func_8213B5D8(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK *, M2C_UNK *, s32, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_8213B644(M2C_UNK, M2C_UNK, M2C_UNK);   /* extern */
M2C_UNK func_8213C220(M2C_UNK, M2C_UNK);            /* extern */
extern M2C_UNK D_8218E770;
extern M2C_UNK D_8218E7F8;
extern s16 D_8219A80A;
extern M2C_UNK func_82144E24;
extern M2C_UNK func_82145718;

/**
 * initializes smoke for flamethrower and fire blast
 * Effect start init 23 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used:
 * it ran for exactly Fire Blast, Flamethrower.
 */
void BattleAnim_InitializeFireBlastFlamethrowerUseSmoke(void) {
    func_8213C220(0x64, 1);
    func_8213B644(0, 8, 6);
    func_8213B5D8(0, 2, 0x3C, &func_82144E24, &D_8218E7F8, 0, 1, 0x11, (s32) D_8219A80A, 0, 0);
    func_8213B5D8(0, 4, 0x1E, &func_82145498, &D_8218E770, 0, 1, 0x11, (s32) D_8219A80A, 0, 0);
    func_8213B5D8(0, 4, 0x1E, &func_82145718, &D_8218E7F8, 0, 1, 0x11, (s32) D_8219A80A, 0, 0);
}

extern ParticleDescriptor D_8218E588[86];
extern M2C_UNK D_8218E7F0;
/**
 * Effect init for the end (impact) of the Flamethrower animation.
 * Effect end init 22 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used: it
 * ran for exactly Flamethrower.
 */
void BattleAnim_InitializeFlamethrowerHit(void) {
    BattleAnim_SpawnDrainFlameHueChange(0xA, 0x9, 0xE, 8, 0xC8, 0x10);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0, 2, 0x14, BattleAnim_RunFlamethrowerHitRotationWeak, &D_8218E7F0, 0, 1, 0x11, 9, 0, 0);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0, 2, 2, BattleAnim_RunFlamethrowerHitRotationStrong, &D_8218E7F0, 0, 0xC, 0x11, 9, 0, 0);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(14, 8, 5, BattleAnim_CallbackEndEffects15And22And59Descriptor3DRotatingAlphaScaleFade, &D_8218E770, 0, 2, 0x11, 9, 0, 0);
    BattleAnim_SpawnOwnerModelTintRampDetach(0x3C, 0xE, 0xC8, 0, 8);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(58, 2, 2, BattleAnim_CallbackSharedAnimatedVerticalFade, &D_8218E770, 0, 1, 9, 0, 0x33, 0);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(60, 2, 2, BattleAnim_CallbackSharedAnimatedVerticalFade, &D_8218E770, 0, 1, 9, 0, 0x33, 0);
}

M2C_UNK func_8213B5D8(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK *, M2C_UNK *, s32, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_8213B644(M2C_UNK, M2C_UNK, M2C_UNK);   /* extern */
extern M2C_UNK D_8218E770;
extern M2C_UNK D_8218E7F8;
extern s16 D_8219A80A;
extern M2C_UNK func_82144E24;
extern M2C_UNK func_82145718;

/**
 * Effect init that spawns the Dragon Rage animation. Player sweep (all 165 moves used in battle):
 * only Dragon Rage reached this function.
 * Effect start init 35 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used:
 * it ran for exactly Dragon Rage.
 */
void BattleAnim_InitializeDragonRageUse(void) {
    func_8213B644(0, 8, 6);
    func_8213B5D8(0, 2, 0x3C, &func_82144E24, &D_8218E7F8, 0, 1, 0x11, (s32) D_8219A80A, 1, 0);
    func_8213B5D8(0, 4, 0x1E, &func_82145498, &D_8218E770, 0, 1, 0x11, (s32) D_8219A80A, 1, 0);
    func_8213B5D8(0, 4, 0x1E, &func_82145718, &D_8218E7F8, 0, 1, 0x11, (s32) D_8219A80A, 1, 0);
}

extern ParticleDescriptor D_8218E588[86];
/**
 * Effect init for the end (impact) of the Dragon Rage animation.
 * Effect end init 15 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used: it
 * ran for exactly Dragon Rage.
 */
void BattleAnim_InitializeDragonRageHit(void) {
    BattleAnim_SpawnDrainFlameHueChange(0xA, 0x33, 0x2C, 8, 0xC8, 0x10);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0, 2, 0x14, BattleAnim_RunFlamethrowerHitRotationWeak, &D_8218E7F0, 0, 1, 0x11, 9, 1, 0);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0, 2, 2, BattleAnim_RunFlamethrowerHitRotationStrong, &D_8218E7F0, 0, 0xC, 0x11, 9, 1, 0);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(14, 8, 5, BattleAnim_CallbackEndEffects15And22And59Descriptor3DRotatingAlphaScaleFade, &D_8218E770, 0, 2, 0x11, 9, 1, 0);
    BattleAnim_SpawnOwnerModelTintRampDetach(0x3C, 0x2C, 0xC8, 0, 8);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(58, 2, 2, BattleAnim_CallbackSharedAnimatedVerticalFade, &D_8218E770, 0, 1, 9, 0, 0x18, 0);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(60, 2, 2, BattleAnim_CallbackSharedAnimatedVerticalFade, &D_8218E770, 0, 1, 9, 0, 0x18, 0);
}

M2C_UNK func_8213B5D8(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK *, M2C_UNK *, s32, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_8213B644(M2C_UNK, M2C_UNK, M2C_UNK);   /* extern */
extern M2C_UNK D_8218E770;
extern M2C_UNK D_8218E7F8;
extern s16 D_8219A80A;
extern M2C_UNK func_82144E24;
extern M2C_UNK func_82145718;

/**
 * Effect init that spawns the Fire Spin animation. Player sweep (all 165 moves used in battle):
 * only Fire Spin reached this function.
 * Effect start init 84 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used:
 * it ran for exactly Fire Spin.
 */
void BattleAnim_InitializeFireSpinUse(void) {
    func_8213B644(0, 8, 6);
    func_8213B5D8(0, 2, 0x50, &func_82144E24, &D_8218E7F8, 0, 1, 0x11, (s32) D_8219A80A, 0, 0);
    func_8213B5D8(0, 4, 0x28, &func_82145498, &D_8218E770, 0, 1, 0x11, (s32) D_8219A80A, 0, 0);
    func_8213B5D8(0, 4, 0x28, &func_82145718, &D_8218E7F8, 0, 1, 0x11, (s32) D_8219A80A, 0, 0);
}

M2C_UNK func_8213B560(M2C_UNK, M2C_UNK *, M2C_UNK *, M2C_UNK, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_8213BF70(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, s32, s32); /* extern */
extern M2C_UNK D_8218E598;
extern M2C_UNK D_8218E7F8;

/**
 * initialize flames that make up the ring that engulfs a pokemon being hit by fire spin
 * Effect end init 29 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used: it
 * ran for exactly Fire Spin.
 */
void BattleAnim_InitializeFireSpinHitFlames(void) {
    func_8213B560(0, &BattleAnim_FireSpinParticleUpdate, &D_8218E598, 0, 0x12, 0xE, 0, 0, 0);
    func_8213B560(8, &BattleAnim_RunOscillatingFlameUnderneathPokemon, &D_8218E7F8, 0, 0x20, 7, 0, 0, 0);
    func_8213BF70(8, 9, 0xE, 8, 0xC8, 0x10);
}

/**
 * Empty.
 */
void func_821491CC(void) {
}

/**
 * Init hook for start effects that need no setup.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal or j,
 * no pointer word, no lui/addiu pair in any fragment), so play cannot reach it.
 * @unverified Name from Stadium 1.
 */
void BattleAnim_DefaultStartEffect_Init(void) {
}

extern ParticleDescriptor D_8218E588[86];
extern M2C_UNK D_8218E5A8;
extern M2C_UNK D_8218E7C0;
/**
 * Effect init for the end (impact) of the Egg Bomb animation.
 * Effect end init 40 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used: it
 * ran for exactly Egg Bomb.
 */
void BattleAnim_InitializeEggBombHit(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_RunExpandingHitSpark, &D_8218E5A8, 0, 1, 0x10, 9, 0x12, 0);
    BattleAnim_SpawnDescriptor25AlphaHoldFadeOut(0, 0, 0x40, 0x8, 0xC8);
    BattleAnim_SpawnBeamBoomWaterfallHueChange(4, 0x8, 0x17, 0x20, 0xFF);
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_RunBackgroundBombExplosion, &D_8218E7B0, 0, 3, 0x10, 9, 0x17, 2);
    BattleAnim_CreateEffectSlotForCurrentOwner(6, BattleAnim_RunBackgroundBombExplosion, &D_8218E7B0, 0, 3, 0x10, 9, 0x2C, 1);
    BattleAnim_CreateEffectSlotForCurrentOwner(12, BattleAnim_RunBackgroundBombExplosion, &D_8218E7B0, 0, 3, 0x10, 9, 0x1A, 1);
    BattleAnim_CreateEffectSlotForCurrentOwner(18, BattleAnim_RunBackgroundBombExplosion, &D_8218E7B0, 0, 2, 0x10, 9, 0x1A, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(20, BattleAnim_CallbackEndEffect40Descriptor48SpreadScaleAlphaFade, &D_8218E7C0, 0, 3, 0x11, 9, 0x1A, 0);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(20, 2, 2, BattleAnim_CallbackEndEffect40Descriptor3DSpreadRisingColorFade, &D_8218E770, 0, 6, 0x11, 9, 0, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(24, BattleAnim_CallbackEndEffects40And54Descriptor46SpreadScaleFade, &D_8218E7B0, 0, 8, 0x11, 9, 0, 0);
}

/**
 * Init hook for end effects that need no setup.
 * Not reached in play (2026-11-13): did not run in the 165-move battle sweep (each move used once,
 * from the command menu to the end of its turn) or in a tour of the menus and a COM battle.
 * @unverified Name from Stadium 1.
 */
void BattleAnim_DefaultEndEffect_Init(void) {
}

/**
 * Effect init for the end (impact) of the Fire Blast animation.
 * Effect end init 59 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used: it
 * ran for exactly Fire Blast.
 */
void BattleAnim_InitializeFireBlastHit(void) {
    BattleAnim_SpawnGlobalTintColorFadeDetach(0, 0xFF, 0);
    BattleAnim_SpawnDrainFlameHueChange(0xA, 9, 0xE, 8, 0xC8, 0x10);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(4, 8, 0x14, BattleAnim_CallbackEndEffects15And22And59Descriptor3DRotatingAlphaScaleFade, &D_8218E580[0x3E], 0, 2, 0xE, 0, 0, 0);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(4, 8, 0x14, BattleAnim_CallbackEndEffect59Descriptor4FColorScaleFade, &D_8218E580[0x4F], 0, 2, 9, 0, 0, 0);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0, 6, 0x28, BattleAnim_RunDaimonji, &D_8218E580[0x4F], 0, 1, 9, 0, 0, 0);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0, 4, 0x3C, BattleAnim_RunDaimonji, &D_8218E580[0x4F], 0, 1, 9, 0, 1, 0);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0, 4, 0x3C, BattleAnim_RunDaimonji, &D_8218E580[0x4F], 0, 1, 9, 0, 2, 0);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0, 3, 0x50, BattleAnim_RunDaimonji, &D_8218E580[0x4F], 0, 1, 9, 0, 3, 0);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0, 3, 0x50, BattleAnim_RunDaimonji, &D_8218E580[0x4F], 0, 1, 9, 0, 4, 0);
}
