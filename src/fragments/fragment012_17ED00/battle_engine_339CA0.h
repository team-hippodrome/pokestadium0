#ifndef ZERO_BATTLE_ENGINE_339CA0_H
#define ZERO_BATTLE_ENGINE_339CA0_H

/* Stadium Zero fragment012_17ED00. */
/* C ported from the Stadium 1 decomp: src/fragments/battle_engine/battle_engine_339CA0.c, src/fragments/battle_engine/battle_engine_343BA0.c. */

#include "fragments/battle_engine/battle_engine.h"
#include "model_animation.h"
#include "geo_render.h"
#include "gfx_buffer.h"
#include "matrix.h"
#include "math_util.h"

#include "gallery.h"
#include "math.h"
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

void BattleAnim_SetupSlashingMoveUse(Particle* arg0);
void BattleAnim_SetupRazorWindHitEffect(Particle* arg0);
void BattleAnim_SetupPetalDanceRazorLeafHitEffect(Particle* arg0);
void BattleAnim_CallbackEndEffects39And41And45And46And83Descriptor3DMetadataBurstChild_InitParticle(Particle* arg0);
void BattleAnim_SetupSandAttackHitEffect(Particle* arg0);
void BattleAnim_CallbackSharedDescriptors3EAnd3FAnimatedRiseFade_InitParticle(Particle* arg0);
void BattleAnim_SetupIceBeamIcePunchEffect(Particle* arg0);
void BattleAnim_CallbackOrphanDescriptor34ColorFadeDetach_InitParticle(Particle* arg0);
void BattleAnim_SetupGroundedCircularHitSpark(Particle* arg0);
void BattleAnim_SetupUnusedGlitterVariant(Particle* arg0);
void BattleAnim_SetupPointyMoveHitSparkChild(Particle* arg0);
void BattleAnim_SetupPhysicalHitPurpleSmoke(Particle* arg0);
void BattleAnim_SetupSwiftHitEffect2(Particle* arg0);
void BattleAnim_SetupBlizzardHitEffect(Particle* arg0);
void BattleAnim_SetupThunderPunchHitEffect(Particle* arg0);
void BattleAnim_SetupDefaultHitSpark(Particle* arg0);
void BattleAnim_SetupStrongPurpleHitSmoke(Particle* arg0);
void BattleAnim_SetupPointyMoveHitSpark(Particle* arg0);
void BattleAnim_SetupFirePunchUseEffect1(Particle* arg0);
void BattleAnim_SetupFirePunchUseEffect2(Particle* arg0);
void BattleAnim_SetupThunderPunchUseEffect(Particle* arg0);
void BattleAnim_RecolorParticleByQueuedMoveId(Particle* arg0);
void BattleAnim_CallbackStartEffects28And53And65And76Descriptor47AnimatedScaleMotion_InitParticle(Particle* arg0);
void BattleAnim_SetupAcidArmorUseEffect2(Particle* arg0);
void BattleAnim_ApplySpeciesKeyedSpawnOffset(Particle* arg0);
void BattleAnim_SetupBarrageUseEffect2(Particle* arg0);
void BattleAnim_CallbackDescriptor50BurstChild_InitParticle(Particle* arg0);
void BattleAnim_EndEffect16_NoOpInit(void);
void BattleAnim_SetupSolarBeamUseEffect(Particle* arg0);
void BattleAnim_SetupQiChargeChild(Particle* arg0);
void BattleAnim_RunStrongContactMoveHitSpark(void);
void BattleAnim_InitializeUniqueSharedHitSpark(void);
void BattleAnim_InitializeLowKickHit(void);
void BattleAnim_InitializeDefaultLimbForMove(void);
void BattleAnim_InitializeSpecialLimbForMove(void);
void BattleAnim_InitializePointyMoveHitSparks(void);
void BattleAnim_InitializePoisonStingTwineedleHit(void);
void BattleAnim_InitializeFuryAttackGustHit(void);
void BattleAnim_OrphanDescriptor34Emitter(void);
void BattleAnim_InitializeSubmissionUse(void);
void BattleAnim_InitializeStompHit(void);
void BattleAnim_InitializeGroundedCircularHitSpark(void);
void BattleAnim_InitializeSubmissionHit(void);
void BattleAnim_InitializeBitingMoveEndEffect(void);
void BattleAnim_InitializeSwiftHit(void);
void BattleAnim_StartEffect137Descriptor3FRisingFade(void);
void BattleAnim_InitializeRazorWindHit(void);
void BattleAnim_InitializePetalDanceHitSequence(void);
void BattleAnim_InitializeDoubleEdgeTakeDownUse(void);
void BattleAnim_InitializeBodySlamUse(void);
void BattleAnim_InitializeDefenseCurlSharpenUseSequence(void);
void BattleAnim_InitializeQiCharge(s32 arg0);
void BattleAnim_InitializeRecoverUse(void);

void BattleAnim_RunRazorWindHitEffect(Particle* arg0);
void BattleAnim_RunPetalDanceRazorLeafHitEffect(Particle* arg0);
void BattleAnim_CallbackSharedDescriptors3EAnd3FAnimatedRiseFade(Particle* arg0);
void BattleAnim_CallbackOrphanDescriptor34ColorFadeDetach(Particle* arg0);
void BattleAnim_RunGroundedCircularHitSpark(Particle* arg0);
void BattleAnim_RunPhysicalHitPurpleSmoke(Particle* arg0);
void BattleAnim_CallbackEndEffect52Descriptor42BurstChild(Particle* arg0);
void BattleAnim_RunSwiftHitEffect2(Particle* arg0);
void BattleAnim_RunSparkleHit(Particle* arg0);
void BattleAnim_RunDefaultHitSpark(Particle* arg0);
void BattleAnim_RunStrongPurpleHitSmoke(Particle* arg0);
s32 BattleAnim_RunPointyMoveHitSpark(Particle* arg0);
void BattleAnim_CallbackSharedAnimatedVerticalFade(Particle* arg0);
void BattleAnim_CallbackStartEffects29And60And104And110DefaultDescriptorBurstEmitter(Particle* arg0);

M2C_UNK func_8213C930(s8 *);                      /* extern */
M2C_UNK func_8213CCEC(s8 *, M2C_UNK, M2C_UNK, M2C_UNK, s32, s32); /* extern */
M2C_UNK func_82140228(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_82140548(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_8215F930(s8 *);                      /* extern */

void func_8215FAA4(s8 *arg0);

void func_8216008C(Particle* arg0);

s16 Particle_GetUnkCE();                                /* extern */
M2C_UNK func_8213C938(s8 *);                      /* extern */
M2C_UNK func_8213CA80(s8 *, M2C_UNK);             /* extern */
M2C_UNK func_82140228(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK Particle_ApproachPrimGreen(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK Particle_ApproachPrimBlue(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK Particle_ApproachEnvBlue(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK Particle_ApproachEnvGreen(s8 *, M2C_UNK, M2C_UNK);    /* extern */

void BattleAnim_RunSlashingMoveFullScreenFlash(s8 *arg0);

void Particle_SetPosition(Particle* arg0, f32 arg1, f32 arg2, f32 arg3);

void func_821601C0(Particle* arg0);

s16 Particle_GetUnkCE();                                /* extern */
M2C_UNK func_8213C930(s8 *);                      /* extern */
M2C_UNK func_8213CA80(s8 *, M2C_UNK);             /* extern */
M2C_UNK func_82140228(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK Particle_ApproachPrimGreen(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK Particle_ApproachPrimBlue(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK Particle_ApproachEnvBlue(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK Particle_ApproachEnvGreen(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK Particle_ApproachPrimAlpha(s8 *, M2C_UNK, M2C_UNK);    /* extern */

void BattleAnim_RunSlashMoveWhiteFlashOverlay(s8 *arg0);

void BattleAnim_CallbackSharedOwnerKeyedAnimGrowFade_InitParticle(Particle* arg0);

M2C_UNK func_8213C938(s8 *);                      /* extern */
M2C_UNK func_8213CA80(s8 *, M2C_UNK);             /* extern */
M2C_UNK func_8213CC10(s8 *, M2C_UNK, M2C_UNK, M2C_UNK, s32, s32); /* extern */
M2C_UNK func_82140228(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_82140548(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_8216031C(s8 *);                      /* extern */

void func_821603C8(s8 *arg0);

M2C_UNK func_8213C930(s8 *);                      /* extern */
M2C_UNK func_8213CB3C(s8 *);                      /* extern */
M2C_UNK func_8213CCEC(s8 *, M2C_UNK, M2C_UNK, M2C_UNK, s32, s32); /* extern */
M2C_UNK func_8213E6BC(s8 *);                      /* extern */
M2C_UNK Particle_ApproachPrimAlpha(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_82160494(s8 *);                      /* extern */

void func_82160528(s8 *arg0);

f32 func_8000F150();                                /* extern */
s16 Particle_GetUnkAC();                                /* extern */
u16 func_8213C484(s8 *);                          /* extern */
s32 func_8213C494(s8 *);                          /* extern */
M2C_UNK func_8213C9D0(s8 *);                      /* extern */
M2C_UNK Particle_AddRotationY(s8 *, s16);                 /* extern */
M2C_UNK Particle_SetStepMagnitudeScaled(s8 *, f32);                 /* extern */
M2C_UNK func_821401D4(s8 *, M2C_UNK);             /* extern */
M2C_UNK func_8214050C(s8 *, M2C_UNK);             /* extern */
M2C_UNK func_82143478(s8 *, u16);                 /* extern */

void func_821605F8(s8 *arg0);

M2C_UNK func_8213C930(s8 *);                      /* extern */
M2C_UNK func_8213CCEC(s8 *, M2C_UNK, M2C_UNK, M2C_UNK, s32, s32); /* extern */
M2C_UNK func_8213E1FC(s8 *, s32);                 /* extern */
M2C_UNK func_8213E4D8(s8 *);                      /* extern */
M2C_UNK func_8213F658(s8 *, f32, f32);    /* extern */
M2C_UNK func_82140228(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_82140548(s8 *, M2C_UNK, M2C_UNK);    /* extern */

void BattleAnim_RunSmallSand(s8 *arg0);

f32 func_8000F150();                                /* extern */
s16 Particle_GetUnkAC();                                /* extern */
u16 func_8213C484(s8 *);                          /* extern */
s32 func_8213C494(s8 *);                          /* extern */
M2C_UNK func_8213C9D0(s8 *);                      /* extern */
M2C_UNK Particle_AddRotationY(s8 *, s16);                 /* extern */
M2C_UNK Particle_SetStepMagnitudeScaled(s8 *, f32);                 /* extern */
M2C_UNK func_821401D4(s8 *, M2C_UNK);             /* extern */
M2C_UNK func_8214050C(s8 *, M2C_UNK);             /* extern */
M2C_UNK func_82143478(s8 *, u16);                 /* extern */

void func_821607E8(s8 *arg0);

M2C_UNK func_8213C930(s8 *);                      /* extern */
M2C_UNK func_8213C9D0(s8 *);                      /* extern */
M2C_UNK func_8213CCEC(s8 *, M2C_UNK, M2C_UNK, M2C_UNK, s32, s32); /* extern */
M2C_UNK func_8213E1FC(s8 *, s32);                 /* extern */
M2C_UNK func_8213E4D8(s8 *);                      /* extern */
M2C_UNK func_8213F658(s8 *, f32, f32);    /* extern */
M2C_UNK func_82140228(s8 *, M2C_UNK, M2C_UNK);    /* extern */
s32 Particle_ApproachPrimAlpha(s8 *, M2C_UNK, M2C_UNK);        /* extern */

void BattleAnim_RunLargeSand(s8 *arg0);

void BattleAnim_SetupSandAttackUseEffect(Particle* arg0);

M2C_UNK func_8213C930(s8 *);                      /* extern */
M2C_UNK func_8213CCEC(s8 *, M2C_UNK, M2C_UNK, M2C_UNK, s32, s32); /* extern */
M2C_UNK func_8213E1FC(s8 *, s32);                 /* extern */
M2C_UNK func_8213E4D8(s8 *);                      /* extern */
M2C_UNK func_82140228(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK Particle_ApproachPrimAlpha(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_821609F0(s8 *);                      /* extern */

void func_82160AF0(s8 *arg0);

f32 func_8000F150();                                /* extern */
s16 Particle_GetUnkAC();                                /* extern */
s32 func_8213C494(s8 *);                          /* extern */
M2C_UNK func_8213C9D0(s8 *);                      /* extern */
M2C_UNK func_8213DDB8(s8 *, M2C_UNK, M2C_UNK, M2C_UNK); /* extern */
M2C_UNK Particle_AddRotationY(s8 *, s16);                 /* extern */
M2C_UNK Particle_SetStepMagnitudeScaled(s8 *, f32);                 /* extern */
M2C_UNK func_821401D4(s8 *, M2C_UNK);             /* extern */
M2C_UNK func_8214050C(s8 *, M2C_UNK);             /* extern */

void func_82160BB8(s8 *arg0);

M2C_UNK func_8213C930(s8 *);                      /* extern */
M2C_UNK func_8213C9D0(s8 *);                      /* extern */
M2C_UNK func_8213CCEC(s8 *, M2C_UNK, M2C_UNK, M2C_UNK, s32, s32); /* extern */
M2C_UNK func_8213E1FC(s8 *, s32);                 /* extern */
M2C_UNK func_8213E4D8(s8 *);                      /* extern */
M2C_UNK func_8213F658(s8 *, f32, f32);    /* extern */
M2C_UNK func_82140228(s8 *, M2C_UNK, M2C_UNK);    /* extern */
s32 Particle_ApproachPrimAlpha(s8 *, M2C_UNK, M2C_UNK);        /* extern */

void func_82160CCC(s8 *arg0);

M2C_UNK func_8213C930(s8 *);                      /* extern */
M2C_UNK func_8213C9D0(s8 *);                      /* extern */
M2C_UNK func_8213CB3C(s8 *);                      /* extern */
M2C_UNK func_8213CC10(s8 *, M2C_UNK, M2C_UNK, M2C_UNK, s32, s32); /* extern */
s32 func_8213E7A0(s8 *);                          /* extern */
M2C_UNK func_82140228(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK Particle_ApproachPrimAlpha(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_82160DC4(s8 *);                      /* extern */

void BattleAnim_RunSandAttackHitEffect(s8 *arg0);

/*
 * BattleAnim_CallbackSharedDescriptors3EAnd3FAnimatedRiseFade
 *
 * Per-frame callback of the "animated rise and fade" particle used by
 * descriptors 0x3E and 0x3F.  It switches on the particle's lifecycle state
 * (the halfword at offset 0xAE; the donor calls it `lifecycle`):
 *   1  initialise (the _InitParticle function, func_82160FA0)
 *   2  animate frames 0..7 forward, ease the scale (field at 0x1C) toward 0.8
 *      by 0.1, ease the second float (func_8213F658) toward 1.0 by 1.0, and
 *      once the countdown at offset 0xA6 has reached zero move the Y motion
 *      step toward 0.5 by 0.4 and add it to the offset
 *   3  add the Y motion step to the offset and fade the primitive alpha to 0
 *      by 0x20
 *   4  mark the particle inactive
 * Afterwards, if the particle is still running, it is pushed along its
 * facing direction.
 *
 * Same structure as BattleAnim_CallbackSharedDescriptors3EAnd3FAnimatedRiseFade
 * in the Stadium 1 decomp (the donor spells the callees differently, and
 * Zero's address 0x8213F658 has no name in the symbol table).  The first
 * float argument of that call is written as the double 1.0, as in the donor:
 * with 1.0f twice the compiler reuses one register and emits three extra
 * instructions.
 */
void BattleAnim_CallbackSharedDescriptors3EAnd3FAnimatedRiseFade(Particle* arg0);

M2C_UNK func_8213C930(s8 *);                      /* extern */
M2C_UNK func_8213CB3C(s8 *);                      /* extern */
M2C_UNK func_8213CCEC(s8 *, M2C_UNK, M2C_UNK, M2C_UNK, s32, s32); /* extern */
M2C_UNK func_8213E7A0(s8 *);                      /* extern */
M2C_UNK Particle_ApproachPrimAlpha(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_82161190(s8 *);                      /* extern */

void func_82161288(s8 *arg0);

M2C_UNK func_8213C938(s8 *);                      /* extern */
s32 func_8213CA04(s8 *, M2C_UNK);                 /* extern */
M2C_UNK func_8213CB3C(s8 *);                      /* extern */
M2C_UNK func_8213CCEC(s8 *, M2C_UNK, M2C_UNK, M2C_UNK, s32, s32); /* extern */
M2C_UNK func_8213E6BC(s8 *);                      /* extern */
M2C_UNK Particle_ApproachPrimRed(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK Particle_ApproachEnvRed(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK Particle_ApproachEnvBlue(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK Particle_ApproachEnvGreen(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK Particle_ApproachPrimAlpha(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_82161358(s8 *);                      /* extern */

void func_8216140C(s8 *arg0);

M2C_UNK func_8213C930(s8 *);                      /* extern */
s32 func_8213C9B0(s8 *);                          /* extern */
M2C_UNK func_8213C9D0(s8 *);                      /* extern */
M2C_UNK func_8213E528(s8 *);                      /* extern */
M2C_UNK func_8213F658(s8 *, f32, f32);    /* extern */
s32 Particle_ApproachPrimAlpha(s8 *, M2C_UNK, M2C_UNK);        /* extern */
s32 func_82140690(s8 *);                          /* extern */
M2C_UNK func_821615F8(s8 *);                      /* extern */

void func_821616BC(s8 *arg0);

M2C_UNK func_8213C930(s8 *);                      /* extern */
s32 func_8213C9B0(s8 *);                          /* extern */
M2C_UNK func_8213C9D0(s8 *);                      /* extern */
M2C_UNK func_8213E528(s8 *);                      /* extern */
M2C_UNK func_8213F658(s8 *, f32, f32);    /* extern */
M2C_UNK func_82140228(s8 *, M2C_UNK, M2C_UNK);    /* extern */
s32 Particle_ApproachPrimAlpha(s8 *, M2C_UNK, M2C_UNK);        /* extern */
s32 func_82140690(s8 *);                          /* extern */
M2C_UNK func_8216177C(s8 *);                      /* extern */

void BattleAnim_RunPointyMoveHitSparkChild(s8 *arg0);

void BattleAnim_CallbackEndEffect52Descriptor42BurstChild_InitParticle(Particle* arg0);

M2C_UNK func_8213E3F8(s8 *);

void BattleAnim_SetupSharedScalePulseFallSetup(Particle* arg0);

void BattleAnim_RunBlizzardHitEffect(Particle* arg0);

void func_821627C0(Particle* arg0);

void BattleAnim_RunThunderPunchHitEffect(Particle* arg0);

void BattleAnim_RunFirePunchUseEffect1(Particle* arg0);

M2C_UNK func_8213C930(s8 *);                      /* extern */
M2C_UNK func_8213CB3C(s8 *);                      /* extern */
M2C_UNK func_8213CCEC(s8 *, M2C_UNK, M2C_UNK, M2C_UNK, s32, s32); /* extern */
M2C_UNK func_8213E4D8(s8 *);                      /* extern */
M2C_UNK func_8213F658(s8 *, f32, f32);    /* extern */
M2C_UNK func_82140228(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK Particle_ApproachPrimGreen(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK Particle_ApproachPrimBlue(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK Particle_ApproachEnvGreen(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK Particle_ApproachPrimAlpha(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_821635E4(s8 *);                      /* extern */

void func_8216374C(s8 *arg0);

M2C_UNK func_8213C930(s8 *);                      /* extern */
M2C_UNK func_8213CB3C(s8 *);                      /* extern */
M2C_UNK func_8213CCEC(s8 *, M2C_UNK, M2C_UNK, M2C_UNK, s32, s32); /* extern */
M2C_UNK func_8213E4D8(s8 *);                      /* extern */
M2C_UNK func_8213F658(s8 *, f32, f32);    /* extern */
M2C_UNK func_82140228(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK Particle_ApproachPrimGreen(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK Particle_ApproachPrimBlue(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK Particle_ApproachEnvGreen(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK Particle_ApproachPrimAlpha(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_82163884(s8 *);                      /* extern */

void func_821639EC(s8 *arg0);

M2C_UNK func_8213C930(s8 *);                      /* extern */
M2C_UNK func_8213CB3C(s8 *);                      /* extern */
M2C_UNK func_8213CCEC(s8 *, M2C_UNK, M2C_UNK, M2C_UNK, s32, s32); /* extern */
M2C_UNK func_8213E528(s8 *);                      /* extern */
M2C_UNK func_82140228(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK Particle_ApproachPrimAlpha(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_82163C28(s8 *);                      /* extern */

void func_82163D7C(s8 *arg0);

/*
 * func_82163E60
 *
 * Particle initialiser: sets the particle's scale to 0.2, recolours its
 * primitive/environment colours from its descriptor's palette pair, sets
 * the primitive alpha to 0xC8, stores 0x18 with Particle_FieldA6_SetS16_0BCA8,
 * sets the float at offset 0x70 (the donor calls it stepMagnitude; the
 * value, 0.02 in the donor, is the rodata float D_FLT_82197730 here) and
 * advances the particle's lifecycle.
 *
 * Same sequence as
 * BattleAnim_SetupHydroPumpColorShiftFade
 * in the Stadium 1 decomp.  The 0xC8 alpha is passed as -0x38 in the retail
 * code (the same byte).
 */
extern f32 D_FLT_82197730;

void func_82163E60(Particle* arg0);

M2C_UNK func_82137AB4(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_8213C930(s8 *);                      /* extern */
M2C_UNK func_82140228(s8 *, M2C_UNK, s32);        /* extern */
M2C_UNK Particle_ApproachEnvGreen(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_82140548(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_821406B4(s8 *);                      /* extern */

void func_82163ED0(s8 *arg0);

extern const f32 D_FLT_82197734;

void BattleAnim_RunAcidArmorUseEffect2(Particle* arg0);

void BattleAnim_InitSharedVerticalFadeParticle(Particle* arg0);
/*
 * BattleAnim_InitSharedVerticalFadeParticle  (src/fragments/fragment012_17ED00/battle_engine_339CA0.c)  -- 589 words
 *
 * Init callback for a battle-animation particle of the shared "vertical fade"
 * effect: it reads three values stored on the particle, then, per variant
 * (switch on sp2C), sets its scale, a random position offset, step size, alpha and
 * a couple of misc fields.  Cases 9-11 additionally build a random rotation
 * vector (sp30) and apply it to the particle.
 *
 * Origin: Stadium 1 BattleAnim_InitSharedVerticalFadeParticle.  Where Zero
 * differs, this code follows the retail ROM; the one structural difference
 * I found is case 8 (see the comment there).  The names
 * used for the helper calls are the ones already in this repo's symbol list,
 * so they look different from Stadium 1's names (for example
 * Particle_Field1C_SetScaled_0B938 is Stadium 1's Particle_Scale_SetScaled).
 *
 * Verified: compiles with IDO 7.1 -O2 -mips2 (repo flags and headers) to the same words as the retail ROM, relocations compared by address.
 * Constants: the float literals this function reads (0.0, 0.02, 0.04, 0.05,
 * 0.07, 0.15, 0.2, 0.3) and the 13-entry jump table of its switch were
 * compared with the bytes in the retail ROM and are identical.  The function
 * is kept behind NON_MATCHING only because those literals live in this
 * file's .rodata, which is not placed yet (see the note above the function).
 */

/* Initialises one particle of the shared "vertical fade" battle effect. */

M2C_UNK func_8213C930(s8 *);                      /* extern */
M2C_UNK func_8213CB3C(s8 *);                      /* extern */
M2C_UNK func_8213CCEC(s8 *, M2C_UNK, M2C_UNK, M2C_UNK, s32, s32); /* extern */
M2C_UNK func_8213E77C(s8 *);                      /* extern */
s32 func_821406B4(s8 *);                          /* extern */

void func_82164AD0(s8 *arg0);

M2C_UNK func_8213C930(s8 *);                      /* extern */
M2C_UNK func_8213CB3C(s8 *);                      /* extern */
M2C_UNK func_8213CC10(s8 *, M2C_UNK, M2C_UNK, M2C_UNK, s32, s32); /* extern */
M2C_UNK func_8213D238(s8 *);                      /* extern */
M2C_UNK Particle_IncrementPhase(s8 *);                      /* extern */
s32 func_8213D294(s8 *, M2C_UNK);                 /* extern */
M2C_UNK func_8213E71C(s8 *, M2C_UNK);             /* extern */
M2C_UNK func_8213E7F4(s8 *);                      /* extern */
M2C_UNK Particle_SetMagnitudeStepScaled(s8 *, M2C_UNK);             /* extern */
M2C_UNK func_8213F6DC(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK Particle_ApproachPrimAlpha(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK Particle_SetUnkA6(s8 *, M2C_UNK);             /* extern */
s32 func_821406B4(s8 *);                          /* extern */
M2C_UNK func_82164B9C(s8 *);                      /* extern */

void BattleAnim_RunSplashOfWater(s8 *arg0);

M2C_UNK func_8213C930(s8 *);                      /* extern */
s32 func_8213C9B0(s8 *);                          /* extern */
M2C_UNK func_8213CB3C(s8 *);                      /* extern */
M2C_UNK func_8213CCEC(s8 *, M2C_UNK, M2C_UNK, M2C_UNK, s32, s32); /* extern */
M2C_UNK func_8213E3F8(s8 *);                      /* extern */
M2C_UNK func_8213F940(s8 *, M2C_UNK, M2C_UNK);    /* extern */
s32 func_821406B4(s8 *);                          /* extern */

void BattleAnim_RunDigHitDust(s8 *arg0);

M2C_UNK func_8213C930(s8 *);                      /* extern */
s32 func_8213C9B0(s8 *);                          /* extern */
M2C_UNK func_8213CB3C(s8 *);                      /* extern */
M2C_UNK func_8213E3F8(s8 *);                      /* extern */
M2C_UNK func_8213F940(s8 *, M2C_UNK, M2C_UNK);    /* extern */
s32 func_821406B4(s8 *);                          /* extern */

void BattleAnim_RunDigHitRocks(s8 *arg0);

void BattleAnim_RunBarrageUseEffect2(Particle* arg0);

M2C_UNK func_8213C930(s8 *);                      /* extern */
s32 func_8213C9B0(s8 *);                          /* extern */
M2C_UNK func_8213CCEC(s8 *, M2C_UNK, M2C_UNK, M2C_UNK, s32, s32); /* extern */
M2C_UNK func_8213E3F8(s8 *);                      /* extern */
M2C_UNK func_8213F940(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_821402B8(s8 *);                      /* extern */
M2C_UNK Particle_ApproachPrimAlpha(s8 *, M2C_UNK, M2C_UNK);    /* extern */
s32 func_82140690(s8 *);                          /* extern */
M2C_UNK func_82165100(s8 *);                      /* extern */

void func_82165224(s8 *arg0);

void BattleAnim_CallbackDescriptor50BurstEmitter_InitParticle(Particle* arg0);

extern ParticleDescriptor D_8218E580[86];
void BattleAnim_CallbackDescriptor50BurstEmitter(Particle* arg0);

M2C_UNK func_8213C930(s8 *);                      /* extern */
s32 func_8213C9B0(s8 *);                          /* extern */
M2C_UNK func_8213CCEC(s8 *, M2C_UNK, M2C_UNK, M2C_UNK, s32, s32); /* extern */
M2C_UNK func_8213E3F8(s8 *);                      /* extern */
M2C_UNK func_8213F940(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_821402B8(s8 *);                      /* extern */
M2C_UNK Particle_ApproachPrimAlpha(s8 *, M2C_UNK, M2C_UNK);    /* extern */
s32 func_82140690(s8 *);                          /* extern */

void func_8216547C(s8 *arg0);

void BattleAnim_RunSolarBeamUseEffect(Particle* arg0);

extern const f32 D_FLT_82197850;

s32 func_8213E334(Particle* arg0, f32 arg1);
void func_8213E4B0(Particle* arg0);
void BattleAnim_RunQiChargeChild(Particle* arg0);

void func_8213E11C(Particle* arg0, f32 arg1);
void BattleAnim_SetupQiCharge(Particle* arg0);

void func_82165854(Particle* arg0);
void BattleAnim_CallbackStartEffects29And60And104And110DefaultDescriptorBurstEmitter(Particle* arg0);

extern const f32 D_FLT_82197854;
void BattleAnim_CallbackDescriptor26BurstChild_InitParticle(Particle* arg0);

extern Vec3f D_8219A880;

void BattleAnim_CallbackDescriptor26BurstChild(Particle* arg0);

s16 Particle_GetUnkAC();                                /* extern */
M2C_UNK func_8213E14C(s32, M2C_UNK);                /* extern */
M2C_UNK func_82143408(s32, M2C_UNK);                /* extern */

void func_82165BC8(s32 arg0);

void BattleAnim_CallbackDescriptor26BurstEmitter(Particle* arg0);

extern const f32 D_FLT_8219786C;
void BattleAnim_SetupUnusedGrowingSparkVariant(Particle* arg0);

void BattleAnim_CallbackUnusedGrowingSparkVariant(Particle* arg0);

extern M2C_UNK D_8218E798;
extern M2C_UNK D_8218E7D0;
void ParticleEffect_TextureSetup(void);

void BattleAnim_InitializeIcePunchHit(void);

M2C_UNK func_8213B560(M2C_UNK, M2C_UNK *, M2C_UNK *, M2C_UNK, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_8213B5D8(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK *, M2C_UNK *, s32, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_8213B794(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, s32); /* extern */
M2C_UNK func_8213BC00(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, s32); /* extern */
extern M2C_UNK D_8218E610;
extern M2C_UNK D_8218E728;
extern M2C_UNK D_8218E788;
extern M2C_UNK func_8214E67C;
extern M2C_UNK func_82162938;
extern M2C_UNK func_82162C68;

void BattleAnim_InitializeThunderPunchHit(void);

M2C_UNK func_8213B644(M2C_UNK, M2C_UNK, M2C_UNK);   /* extern */

void func_82166B88(void);

M2C_UNK func_8213B5D8(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK *, M2C_UNK *, s32, s32, s32, s32, s32, s32); /* extern */
extern s16 D_8219A80A;

void func_82166DC4(void);

/*
 * BattleAnim_InitializeScratchSlashUse
 *
 * Starts the effect slots of one battle animation.  If func_82107CF0
 * (applied to the word at D_8219A814) returns 0x7B, the animation is
 * replaced by a single call to func_8216713C() (it takes no argument) and
 * nothing else happens.
 * Otherwise it creates three slots running func_8215FAA4 on descriptor
 * D_8218E6D0 (start delays 0, 4 and 0xA; the last argument 0, 1, 2 is the
 * only value that differs), one slot running BattleAnim_RunSlashingMoveFullScreenFlash on descriptor
 * D_8218E6C8 with start delay 0x1E, and then calls func_8213B720 with
 * (0x23, 0, 0x10, 0x12).
 *
 * What the arguments of func_8213B560 / func_8213B720 mean is not
 * established here (both are still unnamed); the values are copied from the
 * retail code.  The retail code keeps func_8215FAA4 in a stack local (sp+0x30)
 * that is reused by the three calls, hence the sp30 variable.
 */
s32 func_82107CF0(s32);
void func_8216713C(void);
M2C_UNK func_8213B720(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK);
extern M2C_UNK D_8218E6C8;
extern M2C_UNK D_8218E6D0;
extern s32 D_8219A814;

void BattleAnim_InitializeScratchSlashUse(void);

void func_82167274(void);
void ParticleEffect_DynamicCollisionSetup(void);

void BattleAnim_InitializeCutSlashScratchEffect(void);

M2C_UNK func_8213B560(M2C_UNK, M2C_UNK *, M2C_UNK *, M2C_UNK, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_8213B794(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, s32); /* extern */
extern M2C_UNK D_8218E6D8;
extern M2C_UNK D_8218E790;

void BattleAnim_InitializeVineWhipUse(void);

void BattleAnim_InitializeVineWhipHit(void);

M2C_UNK func_8213B560(M2C_UNK, M2C_UNK *, M2C_UNK *, M2C_UNK, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_8213B5D8(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK *, M2C_UNK *, s32, s32, s32, s32, s32, s32); /* extern */
extern M2C_UNK D_8218E7B0;
extern M2C_UNK func_82163540;

void func_821675EC(void);

M2C_UNK func_8213B644(M2C_UNK, M2C_UNK, M2C_UNK);   /* extern */

void func_821676E4(void);

void BattleAnim_InitializeRazorLeafHit(void);

M2C_UNK func_8213B644(M2C_UNK, M2C_UNK, M2C_UNK);   /* extern */

void func_821677AC(void);

s32 func_8213646C();                                /* extern */
M2C_UNK func_8213B560(M2C_UNK, M2C_UNK *, M2C_UNK *, M2C_UNK, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_8213BC7C(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, s32, s32); /* extern */
extern M2C_UNK D_8218E7B8;

void BattleAnim_InitializePowderSporeGasMoveHit(void);

M2C_UNK func_8213B5D8(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK *, M2C_UNK *, s32, s32, s32, s32, s32, s32); /* extern */
extern M2C_UNK D_8218E7C8;

void func_82167A8C(void);

void BattleAnim_InitializeSandAttackHit(void);

M2C_UNK func_8213B464(M2C_UNK);                     /* extern */
M2C_UNK func_8213B560(M2C_UNK, M2C_UNK *, M2C_UNK *, M2C_UNK, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_8213B5D8(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK *, M2C_UNK *, s32, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_8213BC00(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, s32); /* extern */
M2C_UNK func_8213C0D8(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK); /* extern */
extern M2C_UNK D_8218E770;
extern M2C_UNK D_8218E7D8;
extern M2C_UNK func_821640A0;

void BattleAnim_InitializeAcidArmorUse(void);

M2C_UNK func_8213B464(M2C_UNK);                     /* extern */
M2C_UNK func_8213B560(M2C_UNK, M2C_UNK *, M2C_UNK *, M2C_UNK, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_8213B644(M2C_UNK, M2C_UNK, M2C_UNK);   /* extern */
M2C_UNK func_8213B720(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK); /* extern */
M2C_UNK func_8213B878(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK); /* extern */
M2C_UNK func_8213BC00(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, s32); /* extern */

void BattleAnim_InitializeFlashUse(void);

M2C_UNK func_8213B464(M2C_UNK);                     /* extern */
M2C_UNK func_8213B644(M2C_UNK, M2C_UNK, M2C_UNK);   /* extern */
M2C_UNK func_8213B720(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK); /* extern */
M2C_UNK func_8213BC00(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, s32); /* extern */

void BattleAnim_InitializeFlashHit(void);

M2C_UNK func_8213B560(M2C_UNK, M2C_UNK *, M2C_UNK *, M2C_UNK, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_8213B5D8(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK *, M2C_UNK *, s32, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_8213BC7C(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, s32, s32); /* extern */
M2C_UNK func_8215E510();                            /* extern */
extern M2C_UNK D_8218E7F8;
extern M2C_UNK BattleAnim_RunOscillatingFlameUnderneathPokemon;
void BattleAnim_InitializeBideRageUse(void);

void BattleAnim_InitializeStruggleThrashUse(void);

void BattleAnim_InitializeEarthquakeFissureHitSequence(void);

void func_82168364(void);

void BattleAnim_InitializeSubstituteTransformUse(void);

M2C_UNK func_8213B644(M2C_UNK, M2C_UNK, M2C_UNK);   /* extern */
M2C_UNK func_82168844(M2C_UNK);                     /* extern */

void BattleAnim_InitializeMimicConversionUse(void);

M2C_UNK func_8213B560(M2C_UNK, M2C_UNK *, M2C_UNK *, M2C_UNK, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_8213B644(M2C_UNK, M2C_UNK, M2C_UNK);   /* extern */
M2C_UNK func_82168844(M2C_UNK);                     /* extern */
extern M2C_UNK D_8218E768;
extern M2C_UNK func_821655C0;

void BattleAnim_InitializeSolarBeamUseSequence(void);

M2C_UNK func_8213BC7C(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, s32, s32); /* extern */

void func_82168ACC(void);

M2C_UNK func_8213B5D8(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK *, M2C_UNK *, s32, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_8213BC00(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, s32); /* extern */
extern M2C_UNK func_821624FC;

void BattleAnim_InitializeHardenUse(void);

#endif
