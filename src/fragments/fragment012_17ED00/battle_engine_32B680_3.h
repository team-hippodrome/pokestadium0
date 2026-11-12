#ifndef ZERO_BATTLE_ENGINE_32B680_3_H
#define ZERO_BATTLE_ENGINE_32B680_3_H

/* Stadium Zero fragment012_17ED00. */
/* C ported from the Stadium 1 decomp: src/fragments/battle_engine/battle_engine_32B680.c, src/fragments/battle_engine/battle_engine_343BA0.c, src/fragments/battle_engine/battle_engine_move_animation.c, src/fragments/battle_engine/battle_engine_move_model_transforms.c. */

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

#include "model_animation_events.h"
#include "model_renderer.h"
#include "pokemon_stats.h"
#include "text_system.h"
#include "gb_save.h"
#include "audio_commands.h"
#include "jpeg_stream.h"
#include "audio_fade.h"
#include "audio_stored_fade.h"
#include "audio_loop_point.h"
#include "cry.h"
#include "memory.h"
#include "moves.h"
#include "pokemon.h"
#include "status.h"
extern PokemonBattleCues sSide1BattleCues;
extern PokemonBattleCues sSide2BattleCues;
extern SpeciesModelTransform sSide1PresentationTransform;
extern SpeciesModelTransform sSide2PresentationTransform;
extern ActivePokemon* sActivePokemon[2];
extern ActivePokemon* sSide1ActivePokemon;
extern ActivePokemon* sSide2ActivePokemon;
extern MovePresentationCue* sCurrentAnimation;
extern ModelDimensions sPokemonModelDimensions[2];
extern SwayLayoutConfig sDefaultSwayLayout;
extern BattleSceneStateTickSlot sBattleSceneStateTickSlots[7];
extern s32 sBattleSceneStateTickSlotIndex;
extern PokemonBattleCues* sSideBattleCues[];
extern SpeciesModelTransform* sSidePresentationTransform[];
extern TagTeamPartners* sPlayerTagTeam[];
extern u8 sPokemonWithAlternateSleepIdle[];
extern u8 sPokemonWithAlternateSleepHitReactions[];
extern u8 sPokemonWithNewHmInYellow[];
extern u8 sCharizardLearnsFlyInYellow[];
extern u8 sButterfreeLearnsFlashInYellow[];
extern u8 sVenonatLearnsFlashInYellow[];
extern u8 sVenomothLearnsFlashInYellow[];
extern u8 sDiglettLearnsCutInYellow[];
extern u8 sDugtrioLearnsCutInYellow[];
extern u8 sKabutopsLearnsCutInYellow[];
extern u8 sMewtwoLearnsNothingNewInYellow[];
extern u8 sMewLearnsNothingNewInYellow[];
extern u8* sPokemonYellowHmAdditions[];
extern u8 sAerodactyl;
extern u8 sFearow;
extern u8 sFarfetchD;
extern u8 sDoduoEvoLine[];
extern char** sBattleMessagesTable;
extern char** sPokemonNameTable;
extern char** sMoveNameTable;
extern char** sStatusConditionNameTable;
extern char** sBattleControllerDisconnectedMessage;
#define PARTNER_PIKACHU_CUE_BANK 152
#define DIGLETT_OB1 (DIGLETT - 1)
#define DUGTRIO_OB1 (DUGTRIO - 1)
#define ELECTRODE_OB1 (ELECTRODE - 1)
#define SQUIRTLE_OB1 (SQUIRTLE - 1)
#define WARTORTLE_OB1 (WARTORTLE - 1)
#define BLASTOISE_OB1 (BLASTOISE - 1)
#define CLOYSTER_OB1  (CLOYSTER - 1)

extern f32 sModelTransformConstants[];
#define NINETY_DEGREES 0x4000
extern s32 pad_D_8438466C;
extern s16 sChargeMoveCues[];
extern ThumbnailSettings sSideThumbnailSettings[2];
extern BattleSceneStateCallback sBattleSceneStateTickSentinel;
extern BattleSceneStateRow sBattleSceneStateRowTable[];

#include "m2c_macros.h"

void BattleAnim_SetupReflectiveCamera(void);
Gfx* BattleAnim_BuildAnimatedTileDisplayList(Gfx* arg0, u8* arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5, s16 arg6, s16 arg7, s16 arg8, s16 arg9,
                   s16 argA, s16 argB);
Gfx* BattleAnim_BuildAnimatedTileDisplayListFromStruct(Gfx* arg0, arg1_func_8434E21C* arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5, s16 arg6, s16 arg7,
                   s16 arg8, s16 arg9, s16 argA, s16 argB);
void ParticleEffect_AllocateGfxIfNeeded(s32 arg0, arg1_func_84344CE8* arg1);
void ParticleEffect_AllocateGfxAndDraw(s32 arg0, arg1_func_84344CE8* arg1);
void BattleAnim_InitializeThunderWaveUse(void);
void BattleAnim_SetupEffect1Descriptor2F(Particle* arg0);
void BattleAnim_InitModelAnimationSlot(Particle* arg0, s16 arg1);
void BattleAnim_InitializeAmnesiaUse(void);
void BattleAnim_BuildReflectiveTextureDisplayList(Gfx* arg0, s32 arg1, u16 arg2);
void BattleAnim_AllocateReflectiveTextureDisplayList(s32 arg0, arg1_func_84344CE8* arg1);
void BattleAnim_BuildEffect125DisplayList(Gfx* arg0, u16 arg1);
void BattleAnim_AllocateEffect125DisplayList(s32 arg0, arg1_func_84344CE8* arg1);
void BattleAnim_InitEffect28Overlay(Particle* arg0);
void BattleAnim_SetupLeechSeedUseEffect1(Particle* arg0);
void BattleAnim_SetupLeechSeedUseEffect2(Particle* arg0);
void BattleAnim_InitializeLeechSeedHit(void);
void BattleAnim_InitializePayDayHit(void);
void ParticleEffect_DrawSimple(Gfx* arg0, u8* arg1);
void ParticleEffect_CreateSimpleDL(s32 arg0, arg1_func_84344CE8* arg1);
void BattleAnim_SetupBlizzardHitSpark(Particle* arg0);
void BattleAnim_SetupBlizzard(Particle* arg0);
void ParticleEffect_CreateNodeDL(s32 arg0, arg1_func_84344CE8* arg1);
void ParticleEffect_DrawNodeVariant(Gfx* arg0, arg1_func_8434E21C* arg1, UNUSED u16 arg2);
void ParticleEffect_CreateNodeVariantDL(s32 arg0, arg1_func_84344CE8* arg1);
void ParticleEffect_DrawSimpleOffsetTileNoCamera(Gfx* arg0, u8* arg1, UNUSED u16 arg2);
void ParticleEffect_CreateSimpleOffsetTileNoCameraDL(s32 arg0, arg1_func_84344CE8* arg1);
void BattleAnim_DefaultEndEffect_Draw(void);
void BattleAnim_InitializeDizzyPunchHit(void);
void BattleAnim_InitEffect49Model(Particle* arg0);
void BattleAnim_AllocateEffect49DisplayList(s32 arg0, arg1_func_84344CE8* arg1);
void ParticleEffect_RegisterColorAnim(void);
void BattleAnim_SetupFlyUpwardMovementEffect(Particle* arg0);
void BattleAnim_InitializeTeleportUse(void);
void BattleAnim_AllocateEffect63DisplayList(s32 arg0, arg1_func_84344CE8* arg1);
void BattleAnim_AllocateEffect75DisplayList(s32 arg0, arg1_func_84344CE8* arg1);
void BattleAnim_InitEffects63And75Model(Particle* arg0);
void BattleAnim_InitEffects10And50Model(Particle* arg0);
void BattleAnim_ApplyEffects63And75SpeciesScaleOffset(Particle* arg0);
void BattleAnim_InitEffects63And75Model38(Particle* arg0);
void Particle_CreateDisplayList_Alpha(s32 arg0, arg1_func_84344CE8* arg1);
void Particle_CreateDisplayList_Texture4b(s32 arg0, arg1_func_84344CE8* arg1);
void Particle_CreateDisplayList_GreenPrim(s32 arg0, arg1_func_84344CE8* arg1);
void ParticleEffect_RegisterHandlers_Default(void);
void BattleAnim_InitializeRockSlideRockThrowHit(void);
void BattleAnim_InitializeStrengthUse(void);
void BattleAnim_InitializeStrengthHit(void);
void BattleAnim_InitializeEggBombUse(void);
void BattleAnim_SetupStrongWinds(Particle* arg0);
void Gfx_DrawParticleCyanEnv(Gfx* arg0, arg1_func_8434E21C* arg1, UNUSED u16 arg2);
void Particle_CreateDisplayList_CyanEnv(s32 arg0, arg1_func_84344CE8* arg1);
void Particle_CreateDisplayList_BluePrim(s32 arg0, arg1_func_84344CE8* arg1);
void BattleAnim_InitializeStrongWind(void);
void BattleAnim_InitializeRazorWindUse(void);
void BattleAnim_SetupBoomUseEffect4(Particle* arg0);
void Particle_CreateDisplayList_CustomColors(s32 arg0, arg1_func_84344CE8* arg1);
void BattleAnim_SetupBoomHitEffect3(Particle* arg0);
void func_821597B8(UNUSED ActivePokemon* active_pokemon, UNUSED s32 unused);
void BattleAnim_TransformNop(UNUSED ActivePokemon* owner, UNUSED ActivePokemon* animated_pokemon);
void BattleAnim_SetupBitingEffect(Particle* arg0);
void Particle_CreateDisplayList_TempColors(s32 arg0, arg1_func_84344CE8* arg1);
void BattleAnim_InitializeClampViceGripUse(void);
void BattleAnim_InitializeGuillotineUse(void);
void BattleAnim_InitializeBitingMoveUse(void);
void BattleAnim_InitializeBitingMoveHit(void);
void Gfx_DrawParticleDualTileDiagonal4(Gfx* arg0, u8* arg1, UNUSED u16 arg2);
void Particle_CreateDisplayList_DualTileDiagonal4(s32 arg0, arg1_func_84344CE8* arg1);
void Gfx_DrawParticleDualTileAntiDiagonal1(Gfx* arg0, u8* arg1, UNUSED u16 arg2);
void Particle_CreateDisplayList_DualTileAntiDiagonal1(s32 arg0, arg1_func_84344CE8* arg1);
void BattleAnim_InitializeSwordsDanceUse(void);
f32 BattleAnim_GetSpeciesScaleAdjust(Particle* arg0);
void BattleAnim_InitializeDigUse(void);
void BattleAnim_InitializeKinesisUse(void);
void BattleAnim_InitializeBonemerangUse(void);
void BattleAnim_CallbackStartEffect17ModelAnimFinish_InitParticle(Particle* arg0);
void BattleAnim_SetupSlimePuddle(Particle* arg0);
void Gfx_DrawParticlePaletteBased(Gfx* arg0, u8* arg1, UNUSED u16 arg2);
void Gfx_ParticlePaletteCallback(s32 arg0, arg1_func_84344CE8* arg1);
void Gfx_ParticlePaletteDL(Gfx* arg0, UNUSED arg1_func_8434E21C* arg1, UNUSED u16 arg2);
void Gfx_ParticlePaletteColorOnlyCallback(s32 arg0, arg1_func_84344CE8* arg1);
s16 BattleAnim_GetSlimeVariantIndex(void);
s16 BattleAnim_GetMoveKeyedTrailVariantParam(void);
void BattleAnim_InitializeSlimeMove(void);
void ParticleEffect_PaletteMultiBurst(void);
void Gfx_ParticleTextureTileCallback(Gfx* arg0, arg1_func_8434E21C* arg1, UNUSED u16 arg2);
void Gfx_ParticleTextureTileAllocCallback(s32 arg0, arg1_func_84344CE8* arg1);
void Gfx_ParticleRedPrimAllocCallback(s32 arg0, arg1_func_84344CE8* arg1);
void BattleAnim_InitializeGlareLeerUse(void);
void BattleAnim_InitializeHyperBeamUseSequence(void);
void BattleAnim_InitializeEarthquakeFissureHit(void);
void BattleAnim_InitializeEarthquakeHit(void);
void Gfx_PokemonPortraitCallback(Gfx* arg0, u8 arg1, UNUSED u16 arg2);
void Gfx_PokemonPortraitAllocCallback(s32 arg0, arg1_func_84344CE8* arg1);
void BattleAnim_InitializeSpeedLines(void);
void BattleAnim_InitializeWithdrawUse(void);
void Gfx_PaletteParticleDLCallback(s32 arg0, arg1_func_84344CE8* arg1);
void BattleAnim_InitializeDreamEaterHit(void);
void BattleAnim_InitializeMeditateUse(void);
void BattleAnim_SetupConfuseRayUseSpotlight(Particle* arg0);
void BattleAnim_SetupConfuseRayHitSpotlight(Particle* arg0);
void Gfx_WaterAnimPrimEnvDLCallback(s32 arg0, arg1_func_84344CE8* arg1);
void ParticleEffect_WaterAnimBurst(void);
void Gfx_WaterAnimDLCallback(s32 arg0, arg1_func_84344CE8* arg1);
void BattleAnim_SetupBarrageEffect(Particle* arg0);
void BattleAnim_SetupBarrageUseEffect1(Particle* arg0);
void BattleAnim_InitializeBarrageUse(void);
void BattleAnim_SetupBarrageHitEffect(Particle* arg0);
void BattleAnim_InitializeBarrageHit(void);
void BattleAnim_SetupPsywaveEffect(Particle* arg0);
void Gfx_SimpleNodeDLCallback(s32 arg0, arg1_func_84344CE8* arg1);
void BattleAnim_InitializePsywaveUse(void);
void BattleAnim_InitializeBideRageUseSequence(void);
void BattleAnim_InitializeSkyAttackHit(void);
void ParticleEffect_AllocateDisplayList(s32 arg0, arg1_func_84344CE8* arg1);
void BattleAnim_InitializeThunderHitSequence(void);
void BattleAnim_InitializeDrillPeckUse(void);
void BattleAnim_InitializeDrillPeckHit(void);
void BattleAnim_InitializeHornDrillUse(void);
void BattleAnim_InitializeVerticalLandingHitSpark(void);
void BattleAnim_CallbackStartEffects127And128Descriptor39ScaleFade_InitParticle(Particle* arg0);
void BattleAnim_StartEffect127Descriptor39ScaleFade(void);
void BattleAnim_StartEffect128Descriptor39ScaleFade(void);
void ParticleEffect_CreateTypeX(void);
void ParticleEffect_CreateSmoke(void);
void ParticleEffect_CreateSmokeHighPriority(void);
void BattleAnim_CallbackStartEffect132Descriptor39DelayedRiseFade_InitParticle(Particle* arg0);
void ParticleEffect_CreateDual(void);

void BattleAnim_CallbackInitModelAnimWait(Particle* arg0);
void BattleAnim_InitializeParticleModel(Particle* arg0);
void BattleAnim_RunScaryEyes(Particle* arg0);
void BattleAnim_RunFillScreenOverlay(Particle* arg0);
void Gfx_SetParticlePrimEnvColors(Gfx* arg0);
void Gfx_DrawParticleTextureWithParams(Gfx* arg0, arg1_func_8434E21C* arg1, UNUSED u16 arg2);
void BattleAnim_CallbackMove86StartDescriptor24(Particle* arg0);
void BattleAnim_ApplyEffect1SpeciesMotion(Particle* arg0);
void BattleAnim_ApplyModelSpeciesOffset(Particle* arg0);
void BattleAnim_CallbackStartEffects12And129DelayedModelAnimWait(Particle* arg0);
void BattleAnim_CallbackMove73EndEffect31SpawnDescriptor42(Particle* arg0);
void ParticleEffect_DrawNode(Gfx* arg0, s32 arg1, u16 arg2);
void BattleAnim_RunDizzyPunchHitEffect(Particle* arg0);
void BattleAnim_CallbackEndEffect49Model33Anim34WaitCleanup(Particle* arg0);
void BattleAnim_BuildEffect49DisplayList(Gfx* arg0, UNUSED s32 arg1, UNUSED u16 arg2);
void BattleAnim_CallbackStartEffect86ModelFadeCycle(Particle* arg0);
void BattleAnim_BuildEffect63DisplayList(Gfx* arg0, s32 arg1, u16 arg2);
void BattleAnim_BuildEffect75DisplayList(Gfx* arg0, UNUSED s32 arg1, UNUSED u16 arg2);
void BattleAnim_CallbackStartEffects63And75ModelAnimWait(Particle* arg0);
void BattleAnim_CallbackEndEffects10And50ModelAnimColorFade(Particle* arg0);
void BattleAnim_CallbackStartEffects63And75Model38FadeIn(Particle* arg0);
void Gfx_DrawParticleAlpha(Gfx* arg0, s32 arg1, u16 arg2);
void Gfx_DrawParticleTexture4b(Gfx* arg0, u8* arg1, UNUSED u16 arg2);
void Gfx_DrawParticleGreenPrim(Gfx* arg0, u8* arg1, UNUSED u16 arg2);
void BattleAnim_CallbackStartEffect10Model60AlphaFadeIn(Particle* arg0);
void Gfx_DrawParticleBluePrim(Gfx* arg0, arg1_func_8434E21C* arg1, UNUSED u16 arg2);
void Gfx_DrawParticleCustomColors(Gfx* arg0, arg1_func_8434E21C* arg1, UNUSED u16 arg2);
void BattleAnim_CallbackStartEffects71And74And111SpecialModelColorCycle(Particle* arg0);
void Gfx_DrawParticleFromTempColors(Gfx* arg0, s32 arg1, u16 arg2);
void BattleAnim_CallbackStartEffect17ModelAnimFinish(Particle* arg0);
void BattleAnim_RunSlimePuddle(Particle* arg0);
s16 BattleAnim_GetMoveKeyedTintRampParam(void);
void Gfx_ParticleRedPrimCallback(Gfx* arg0, UNUSED arg1_func_8434E21C* arg1, UNUSED u16 arg2);
void BattleAnim_RunPsychedelicOverlay(Particle* arg0);
void Gfx_PaletteParticleDL(Gfx* arg0, u8* arg1, UNUSED u16 arg2);
void BattleAnim_CallbackStartEffects21And93ModelAlphaAnchorFollow(Particle* arg0);
void Gfx_WaterAnimPrimEnvDL(Gfx* arg0, u8 arg1, UNUSED u16 arg2);
void Gfx_WaterAnimDL(Gfx* arg0, u8* arg1, UNUSED u16 arg2);
void BattleAnim_CallbackStartEffect101ModelBurstEmitter(Particle* arg0);
void BattleAnim_CallbackMove140EndEffect65EmitDescriptor4A(Particle* arg0);
void BattleAnim_RunPsywaveEffect(Particle* arg0);
void Gfx_SimpleNodeDL(Gfx* arg0, arg1_func_8434E21C* arg1, UNUSED u16 arg2);
void ParticleEffect_DrawQuad(Gfx* arg0, arg1_func_8434E21C* arg1, UNUSED u16 arg2);
void BattleAnim_CallbackEndEffect79DefaultDescriptorPaletteFade(Particle* arg0);
void BattleAnim_CallbackStartEffects127And128Descriptor39ScaleFade(Particle* arg0);
void BattleAnim_CallbackStartEffect132Descriptor39DelayedRiseFade(Particle* arg0);

void BattleAnim_RunDreamEaterUseEffect(Particle* arg0);

void BattleAnim_CallbackInitModelAnimMode2(Particle* arg0);

Gfx* BattleAnim_BuildAnimatedTileDisplayList(Gfx* arg0, u8* arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5, s16 arg6, s16 arg7, s16 arg8, s16 arg9,
                   s16 argA, s16 argB);

Gfx* BattleAnim_BuildAnimatedTileDisplayListFromStruct(Gfx* arg0, arg1_func_8434E21C* arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5, s16 arg6, s16 arg7,
                   s16 arg8, s16 arg9, s16 argA, s16 argB);

void BattleAnim_SetupMove86EndDescriptor24(Particle* arg0);

void BattleAnim_RunThunderWaveHitEffect(Particle* arg0);

void BattleAnim_SetupMove86StartDescriptor24(Particle* arg0);

M2C_UNK func_8213C938(s8 *);                      /* extern */
M2C_UNK func_8213E4D8(s8 *);                      /* extern */
M2C_UNK func_82140228(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_82140548(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_821406B4(s8 *);                      /* extern */
M2C_UNK func_82153D00(s8 *);                      /* extern */

void func_82153E28(s8 *arg0);

M2C_UNK func_8213B5D8(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK *, M2C_UNK *, s32, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_8213B644(M2C_UNK, M2C_UNK, M2C_UNK);   /* extern */
extern M2C_UNK D_8218E6A8;
extern s16 D_8219A80A;
extern M2C_UNK func_82153C50;

void func_82153FD8(void);

extern const f32 D_FLT_82196EC8;
extern const f32 D_FLT_82196ECC;
void func_82154050(Particle* arg0);

void BattleAnim_CallbackStartEffect1Descriptor2FPhaseFadeOut(Particle* arg0);

M2C_UNK func_8213B560(M2C_UNK, M2C_UNK *, M2C_UNK *, M2C_UNK, s32, s32, s32, s32, s32); /* extern */
extern M2C_UNK D_8218E700;
extern M2C_UNK func_82154248;

void func_821542BC(void);

void func_82154310(Particle* arg0);

s32 func_8213646C();                                /* extern */
M2C_UNK func_8213B464(M2C_UNK);                     /* extern */
M2C_UNK func_8213B560(M2C_UNK, M2C_UNK *, M2C_UNK *, M2C_UNK, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_8213B5D8(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK *, M2C_UNK *, s32, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_8213B644(M2C_UNK, M2C_UNK, M2C_UNK);   /* extern */
M2C_UNK func_8213B6AC(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, s32); /* extern */
M2C_UNK func_8213BC7C(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, s32, s32); /* extern */
extern ParticleDescriptor D_8218E580[];
extern M2C_UNK D_8218E7A0;
extern M2C_UNK func_82152FB0;
extern M2C_UNK func_821624FC;

void BattleAnim_InitializeScreenMove(void);

void func_82154C9C(Particle* arg0);

void BattleAnim_InitEffect125Model(Particle* arg0, UNUSED s16 arg1);

void BattleAnim_CallbackStartEffect125ModelBurstEmitter(Particle* arg0);

M2C_UNK func_8213B560(M2C_UNK, M2C_UNK *, M2C_UNK *, M2C_UNK, s32, s32, s32, s32, s32); /* extern */
extern M2C_UNK func_82144750;
extern M2C_UNK func_82154EA4;

void func_82155084(void);

void BattleAnim_InitEffect65Overlay(Particle* arg0);

void BattleAnim_RunSporePowderMoveOverlay(Particle* arg0);

/*
 * func_82155238
 *
 * Starts the three particle effect slots of effect 65 for the current
 * battle-animation owner: two one-shot slots (type 8) that fade in using
 * BattleAnim_RunSporePowderMoveOverlay with particle
 * descriptors 0x32 and 0x31, and one repeating slot (0, 3, 0x14) driven by
 * the animated-scale-motion callback with descriptor 0x46.
 *
 * Same three calls as ParticleEffect_RegisterParticleNodes in the Stadium 1
 * decomp.  The third descriptor is index 0x47 there; here the retail
 * address (D_8218E7B8) is index 0x46 of gBattleAnimParticleDescriptors
 * (8-byte stride from 0x8218E588), so the table differs by one entry.
 */
void func_82155238(void);

void BattleAnim_RunGasAttack(Particle* arg0);

M2C_UNK func_8213B560(M2C_UNK, M2C_UNK *, M2C_UNK *, M2C_UNK, s32, s32, s32, s32, s32); /* extern */
extern M2C_UNK D_8218E720;
extern M2C_UNK D_8218E7B8;
extern M2C_UNK func_82155380;
extern M2C_UNK func_82163D7C;

void func_821553D0(void);

M2C_UNK func_8213B560(M2C_UNK, M2C_UNK *, M2C_UNK *, M2C_UNK, s32, s32, s32, s32, s32); /* extern */

void func_82155464(void);

M2C_UNK func_8213B560(M2C_UNK, M2C_UNK *, M2C_UNK *, M2C_UNK, s32, s32, s32, s32, s32); /* extern */

void func_821554F8(void);

M2C_UNK func_8213C938(s8 *);                      /* extern */
M2C_UNK func_8213CCEC(s8 *, M2C_UNK, M2C_UNK, M2C_UNK, s32, s32); /* extern */
M2C_UNK func_82140228(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_82140518(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_8215558C(s8 *);                      /* extern */

void func_821555D4(s8 *arg0);

extern M2C_UNK D_8218E798;
extern M2C_UNK D_8218E7D0;
void BattleAnim_CallbackStartEffect8ModelBurstEmitter(Particle* arg0);

void BattleAnim_InitEffect31Model(Particle* arg0);

s32 func_8001104C(s32);                             /* extern */
s16 func_82137D74(M2C_UNK);                         /* extern */
M2C_UNK func_8213B560(M2C_UNK, M2C_UNK *, M2C_UNK *, M2C_UNK, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_8213C9D0(s8 *);                      /* extern */
M2C_UNK func_82140594(s8 *, s16);                 /* extern */
s32 func_82140690(s8 *);                          /* extern */
M2C_UNK func_82155878(s8 *);                      /* extern */

void func_821558F4(s8 *arg0);

M2C_UNK func_8213B5D8(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK *, M2C_UNK *, s32, s32, s32, s32, s32, s32); /* extern */
extern M2C_UNK func_82155724;
extern M2C_UNK func_82164AD0;

void BattleAnim_InitializeLeechSeedUse(void);

M2C_UNK func_8213831C(s8 *, M2C_UNK);             /* extern */
s32 func_8213C9B0(s8 *);                          /* extern */
M2C_UNK func_82140548(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_82155CC0(s8 *);                      /* extern */

void func_82155D3C(s8 *arg0);

M2C_UNK func_8213C930(s8 *);                      /* extern */
M2C_UNK func_8213CB3C(s8 *);                      /* extern */
M2C_UNK func_8213CCEC(s8 *, M2C_UNK, M2C_UNK, M2C_UNK, s32, s32); /* extern */
M2C_UNK func_8213E6BC(s8 *);                      /* extern */
M2C_UNK func_821402B8(s8 *);                      /* extern */
M2C_UNK func_82140518(s8 *, M2C_UNK, M2C_UNK);    /* extern */
s32 func_821406B4(s8 *);                          /* extern */
M2C_UNK func_82155DB8(s8 *);                      /* extern */

void BattleAnim_RunBlizzard(s8 *arg0);

M2C_UNK func_8213B560(M2C_UNK, M2C_UNK *, M2C_UNK *, M2C_UNK, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_8213B644(M2C_UNK, M2C_UNK, M2C_UNK);   /* extern */
M2C_UNK func_8213B8EC(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, s32); /* extern */

void BattleAnim_InitializeBlizzardUse(void);

M2C_UNK func_8213B458(M2C_UNK);                     /* extern */
M2C_UNK func_8213B5D8(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK *, M2C_UNK *, s32, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_8213B644(M2C_UNK, M2C_UNK, M2C_UNK);   /* extern */
M2C_UNK func_8213BE70(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, s32, s32); /* extern */
extern M2C_UNK D_8218E650;
extern M2C_UNK BattleAnim_RunBlizzardHitUpwardColdAir;
extern M2C_UNK func_82152F44;
extern M2C_UNK func_821626F4;

void BattleAnim_InitializeBlizzardHit(void);

void BattleAnim_InitMove146Model(Particle* arg0);

void func_82156654(Particle* arg0);
s32 func_82136E2C(DisplayObject* arg0);
void func_8215673C(Particle* arg0);

void func_821567BC(Particle* arg0);

void ParticleEffect_RegisterModeSpecific(void);

void BattleAnim_RunFlyUpwardMovementEffect(Particle* arg0);

M2C_UNK func_8213B560(M2C_UNK, M2C_UNK *, M2C_UNK *, M2C_UNK, s32, s32, s32, s32, s32); /* extern */
extern M2C_UNK func_82156B0C;

void BattleAnim_InitializeFlyUse(void);

void func_82156E54(Particle* arg0);
void func_82156EF0(Particle* arg0);

s32 func_8001104C(s32);                             /* extern */
M2C_UNK func_8213C938(s8 *);                      /* extern */
M2C_UNK func_8213C9D0(s8 *);                      /* extern */
M2C_UNK func_8213CA80(s8 *, M2C_UNK);             /* extern */
M2C_UNK func_82140380(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_821403B0(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_82156F70(s8 *);                      /* extern */

void BattleAnim_RunFallingRock(s8 *arg0);

void func_82157354(Particle* arg0);
void func_821573BC(Particle* arg0);

void BattleAnim_InitializeSoftBoiledUse(void);

M2C_UNK func_8213831C(s8 *, M2C_UNK);             /* extern */
M2C_UNK func_8213C930(s8 *);                      /* extern */
s32 func_8213C9B0(s8 *);                          /* extern */
M2C_UNK func_82140518(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_82157DA0(s8 *);                      /* extern */

void func_82157E28(s8 *arg0);

void BattleAnim_RunBoomUseEffect1(Particle* arg0);

void func_82158224(Particle* arg0);

void BattleAnim_RunBoomUseEffect2(Particle* arg0);

void BattleAnim_SetupBoomUseEffect3(Particle* arg0);

M2C_UNK func_8213C930(s8 *);                      /* extern */
M2C_UNK func_8213CB3C(s8 *);                      /* extern */
M2C_UNK func_8213CCEC(s8 *, M2C_UNK, M2C_UNK, M2C_UNK, s32, s32); /* extern */
void func_8213D604(s8*, f32);
M2C_UNK func_8213E528(s8 *);                      /* extern */
M2C_UNK func_82140228(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_821403B0(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_8214047C(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_82140518(s8 *, M2C_UNK, M2C_UNK);    /* extern */
s32 func_82140690(s8 *);                          /* extern */
s32 func_821406B4(s8 *);                          /* extern */
M2C_UNK func_82158344(s8 *);                      /* extern */

void BattleAnim_RunBoomUseEffect3(s8 *arg0);

M2C_UNK func_8213C930(s8 *);                      /* extern */
M2C_UNK func_8213CB3C(s8 *);                      /* extern */
M2C_UNK func_8213CCEC(s8 *, M2C_UNK, M2C_UNK, M2C_UNK, s32, s32); /* extern */
M2C_UNK func_8213E77C(s8 *);                      /* extern */
M2C_UNK func_821403B0(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_8214047C(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_82140518(s8 *, M2C_UNK, M2C_UNK);    /* extern */
s32 func_82140690(s8 *);                          /* extern */
s32 func_821406B4(s8 *);                          /* extern */
M2C_UNK func_8215856C(s8 *);                      /* extern */

void BattleAnim_RunBoomUseEffect4(s8 *arg0);

M2C_UNK func_8213C464();                            /* extern */
M2C_UNK func_8213C930(s8 *);                      /* extern */
M2C_UNK func_821401D4(s8 *, M2C_UNK);             /* extern */
M2C_UNK func_82140228(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_82140548(s8 *, M2C_UNK, M2C_UNK);    /* extern */
s32 func_82140690(s8 *);                          /* extern */
s32 func_821406B4(s8 *);                          /* extern */
M2C_UNK func_821408C8(s8 *, M2C_UNK);             /* extern */
M2C_UNK func_821408DC(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_82143478(s8 *, M2C_UNK);             /* extern */
M2C_UNK func_821437E0(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_82152730(s8 *, M2C_UNK);             /* extern */

void func_821588C0(s8 *arg0);

void BattleAnim_RunBoomUseEffect6(Particle* arg0);

M2C_UNK func_8213C464();                            /* extern */
M2C_UNK func_8213C930(s8 *);                      /* extern */
void func_8213D644(s8*, f32);
M2C_UNK func_821401D4(s8 *, M2C_UNK);             /* extern */
M2C_UNK func_82140228(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_82140548(s8 *, M2C_UNK, M2C_UNK);    /* extern */
s32 func_82140690(s8 *);                          /* extern */
s32 func_821406B4(s8 *);                          /* extern */
M2C_UNK func_821408C8(s8 *, M2C_UNK);             /* extern */
M2C_UNK func_821408DC(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_82143478(s8 *, M2C_UNK);             /* extern */
M2C_UNK func_821437E0(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_82152730(s8 *, M2C_UNK);             /* extern */

void BattleAnim_RunBoomHitEffect1(s8 *arg0);

void BattleAnim_SetupBoomHitEffect2(Particle* arg0);

M2C_UNK func_8213C930(s8 *);                      /* extern */
M2C_UNK func_8213CB3C(s8 *);                      /* extern */
M2C_UNK func_8213CCEC(s8 *, M2C_UNK, M2C_UNK, M2C_UNK, s32, s32); /* extern */
M2C_UNK func_8213E6BC(s8 *);                      /* extern */
M2C_UNK func_821402B8(s8 *);                      /* extern */
M2C_UNK func_821403B0(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_821404DC(s8 *, M2C_UNK, M2C_UNK);    /* extern */
s32 func_82140690(s8 *);                          /* extern */
s32 func_821406B4(s8 *);                          /* extern */
M2C_UNK func_82158CE0(s8 *);                      /* extern */

void BattleAnim_RunBoomHitEffect2(s8 *arg0);

M2C_UNK func_8213C930(s8 *);                      /* extern */
M2C_UNK func_8213CB3C(s8 *);                      /* extern */
s32 func_8213CB7C(s8 *);                          /* extern */
M2C_UNK func_8213CC10(s8 *, M2C_UNK, M2C_UNK, M2C_UNK, s32, s32); /* extern */
M2C_UNK func_8213E6BC(s8 *);                      /* extern */
M2C_UNK func_8213F658(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_821402B8(s8 *);                      /* extern */
M2C_UNK func_82140548(s8 *, M2C_UNK, M2C_UNK);    /* extern */
s32 func_82140690(s8 *);                          /* extern */
s32 func_821406B4(s8 *);                          /* extern */
M2C_UNK func_821437E0(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_82158F20(s8 *);                      /* extern */

void BattleAnim_RunBoomHitEffect3(s8 *arg0);

extern ParticleDescriptor D_8218E580[86];
void BattleAnim_InitializeBoomUse(void);

void BattleAnim_InitializeBoomHit(void);

/**
 * Empty function. Not referenced in C.
 */

s32 func_8001104C(s32);                             /* extern */
M2C_UNK func_8213831C(s8 *, M2C_UNK);             /* extern */
s16 func_8213C484();                                /* extern */
M2C_UNK func_8213C930(s8 *);                      /* extern */
s32 func_8213C9B0(s8 *);                          /* extern */
M2C_UNK func_8213CA80(s8 *, M2C_UNK);             /* extern */
M2C_UNK func_821403B0(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_821403E0(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_821404DC(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_82140518(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_821597D0(s8 *);                      /* extern */

void func_82159898(s8 *arg0);

M2C_UNK func_8213BC00(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, s32); /* extern */
M2C_UNK func_82166B34();                            /* extern */

void BattleAnim_InitializeGuillotineHit(void);

void BattleAnim_CallbackStartEffect69ModelPhaseWait(Particle* arg0);

M2C_UNK func_8213B560(M2C_UNK, M2C_UNK *, M2C_UNK *, M2C_UNK, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_8213B5D8(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK *, M2C_UNK *, s32, s32, s32, s32, s32, s32); /* extern */
extern M2C_UNK D_8218E708;
extern M2C_UNK func_82159F70;
extern M2C_UNK BattleAnim_RunDigHitDust;
extern M2C_UNK BattleAnim_RunDigHitRocks;

void func_82159FC8(void);

M2C_UNK func_8213B560(M2C_UNK, M2C_UNK *, M2C_UNK *, M2C_UNK, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_8213B5D8(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK *, M2C_UNK *, s32, s32, s32, s32, s32, s32); /* extern */
extern M2C_UNK D_8218E728;
extern M2C_UNK func_82162C68;

void BattleAnim_InitializeDigHit(void);

M2C_UNK func_8213B560(M2C_UNK, M2C_UNK *, M2C_UNK *, M2C_UNK, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_8213B720(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK); /* extern */

void BattleAnim_InitializeBoneClubUse(void);

f32 func_8215AEA4(Particle* arg0);

void BattleAnim_InitializeEarthquakeFissureUse(void);

M2C_UNK func_8213B560(M2C_UNK, M2C_UNK *, M2C_UNK *, M2C_UNK, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_8213BC00(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, s32); /* extern */
M2C_UNK func_8213C1BC(M2C_UNK);                     /* extern */
M2C_UNK func_82168504();                            /* extern */

void BattleAnim_InitializeDefenseCurlUse(void);

M2C_UNK func_8213B560(M2C_UNK, M2C_UNK *, M2C_UNK *, M2C_UNK, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_8213BC00(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, s32); /* extern */
M2C_UNK func_8213C1BC(M2C_UNK);                     /* extern */
M2C_UNK func_82168504();                            /* extern */

void BattleAnim_InitializeSharpenUse(void);

M2C_UNK func_8213B644(M2C_UNK, M2C_UNK, M2C_UNK);   /* extern */
M2C_UNK func_8215B558();                            /* extern */

void func_8215B5B8(void);

M2C_UNK func_8213B560(M2C_UNK, M2C_UNK *, M2C_UNK *, M2C_UNK, s32, s32, s32, s32, s32); /* extern */
s32 func_8213C4D0(M2C_UNK);                         /* extern */

void func_8215B63C(void);

f32 func_8215B6A4(Particle* arg0);

M2C_UNK func_8213B560(M2C_UNK, M2C_UNK *, M2C_UNK *, M2C_UNK, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_8213B644(M2C_UNK, M2C_UNK, M2C_UNK);   /* extern */

void BattleAnim_InitializeLovelyKissUse(void);

M2C_UNK func_8213B560(M2C_UNK, M2C_UNK *, M2C_UNK *, M2C_UNK, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_8213BC7C(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, s32, s32); /* extern */

void BattleAnim_InitializeLovelyKissHit(void);

s32 func_82136AC0(s8 *);                          /* extern */
M2C_UNK func_82136D58(s32, M2C_UNK);                /* extern */
s16 func_8213C46C();                                /* extern */
M2C_UNK func_8213C938(s8 *);                      /* extern */
M2C_UNK func_8213C9D0(s8 *);                      /* extern */
M2C_UNK func_821401D4(s8 *, M2C_UNK);             /* extern */
M2C_UNK func_8214050C(s8 *, M2C_UNK);             /* extern */

void func_8215B83C(s8 *arg0);

M2C_UNK func_8213B560(M2C_UNK, M2C_UNK *, M2C_UNK *, M2C_UNK, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_8213B644(M2C_UNK, M2C_UNK, M2C_UNK);   /* extern */
extern M2C_UNK func_82153040;
extern M2C_UNK func_8215B904;

void BattleAnim_InitializeDreamEaterUse(void);

void BattleAnim_CreateDrainingMoveOverlay(void);

M2C_UNK func_8213B464(M2C_UNK);                     /* extern */
M2C_UNK func_8213B560(M2C_UNK, M2C_UNK *, M2C_UNK *, M2C_UNK, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_8213B644(M2C_UNK, M2C_UNK, M2C_UNK);   /* extern */
M2C_UNK func_8213B720(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK); /* extern */

void BattleAnim_InitializeNightShadeUse(void);

M2C_UNK func_8213B560(M2C_UNK, M2C_UNK *, M2C_UNK *, M2C_UNK, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_8213B5D8(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK *, M2C_UNK *, s32, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_8213B720(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK); /* extern */
M2C_UNK func_8213BC00(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, s32); /* extern */

void BattleAnim_InitializeNightShadeHit(void);

s32 func_821385C0();                                /* extern */
M2C_UNK func_8213EAD4(s8 *, s16);                 /* extern */
M2C_UNK func_82140518(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_8214083C(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_8215C8FC(s8 *);                      /* extern */

void func_8215C984(s8 *arg0);

s32 func_821385C0();                                /* extern */
M2C_UNK func_8213EAD4(s8 *, s16);                 /* extern */
M2C_UNK func_8215CA14();                            /* extern */

void func_8215CA9C(s8 *arg0);

M2C_UNK func_8213B644(M2C_UNK, M2C_UNK, M2C_UNK);   /* extern */

void func_8215CCF0(void);

M2C_UNK func_8213B464(M2C_UNK);                     /* extern */
M2C_UNK func_8213B560(M2C_UNK, M2C_UNK *, M2C_UNK *, M2C_UNK, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_8213B644(M2C_UNK, M2C_UNK, M2C_UNK);   /* extern */
M2C_UNK func_8213B720(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK); /* extern */
M2C_UNK func_8213B878(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK); /* extern */
M2C_UNK func_8213BC00(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, s32); /* extern */

void BattleAnim_InitializeConfuseRayUse(void);

M2C_UNK func_8213B464(M2C_UNK);                     /* extern */
M2C_UNK func_8213B560(M2C_UNK, M2C_UNK *, M2C_UNK *, M2C_UNK, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_8213B644(M2C_UNK, M2C_UNK, M2C_UNK);   /* extern */
M2C_UNK func_8213B720(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK); /* extern */
M2C_UNK func_8213BC00(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, s32); /* extern */

void BattleAnim_InitializeConfuseRayHit(void);

extern M2C_UNK D_8218E5F8;
extern M2C_UNK D_8218E5D8;
void ParticleEffect_BasicMultiBurst(void);

M2C_UNK func_8213B464(M2C_UNK);                     /* extern */
M2C_UNK func_8213B560(M2C_UNK, M2C_UNK *, M2C_UNK *, M2C_UNK, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_8213B5D8(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK *, M2C_UNK *, s32, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_8214DA90();                            /* extern */
extern M2C_UNK func_821530F4;

void func_8215D31C(void);

void ParticleEffect_BasicMultiBurstDelayedSprayOnly(void);

extern M2C_UNK D_8218E7A8;
void BattleAnim_InitializeSurfHit(void);

M2C_UNK func_8213B560(M2C_UNK, M2C_UNK *, M2C_UNK *, M2C_UNK, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_8213B720(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK); /* extern */

void BattleAnim_InitializeCrabhammerUse(void);

M2C_UNK func_8213C938(s8 *);                      /* extern */
M2C_UNK func_8213CCEC(s8 *, M2C_UNK, M2C_UNK, M2C_UNK, s32, s32); /* extern */
M2C_UNK func_82140228(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_82140518(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_8215D724(s8 *);                      /* extern */

void func_8215D76C(s8 *arg0);

extern M2C_UNK D_8218E770;

M2C_UNK func_82139E5C(s8 *, M2C_UNK *, M2C_UNK *, M2C_UNK); /* extern */
M2C_UNK func_8213C938(s8 *);                      /* extern */
M2C_UNK func_8213CA80(s8 *, M2C_UNK);             /* extern */
s32 func_8213CB7C(s8 *);                          /* extern */
M2C_UNK func_8213E528(s8 *);                      /* extern */
M2C_UNK func_8213EF88(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_8215DA5C(s8 *);                      /* extern */

void func_8215DAEC(s8 *arg0);

M2C_UNK func_8213B560(M2C_UNK, M2C_UNK *, M2C_UNK *, M2C_UNK, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_8213B5D8(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK *, M2C_UNK *, s32, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_8213BC7C(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, s32, s32); /* extern */
extern M2C_UNK func_8215DCE8;

void BattleAnim_InitializePsywaveHit(void);

void BattleAnim_RunConfusionPsychicHitEffect(Particle* arg0);

M2C_UNK func_8213B560(M2C_UNK, M2C_UNK *, M2C_UNK *, M2C_UNK, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_8213B644(M2C_UNK, M2C_UNK, M2C_UNK);   /* extern */
M2C_UNK func_8213B6AC(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, s32); /* extern */
M2C_UNK func_8213BC7C(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, s32, s32); /* extern */

void BattleAnim_InitializePsychicUse(void);

M2C_UNK func_8213B560(M2C_UNK, M2C_UNK *, M2C_UNK *, M2C_UNK, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_8213B644(M2C_UNK, M2C_UNK, M2C_UNK);   /* extern */
M2C_UNK func_8213B6AC(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, s32); /* extern */
M2C_UNK func_8213BC7C(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, s32, s32); /* extern */

void BattleAnim_InitializeConfusionUse(void);

M2C_UNK func_8213B464(M2C_UNK);                     /* extern */
M2C_UNK func_8213B560(M2C_UNK, M2C_UNK *, M2C_UNK *, M2C_UNK, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_8213B5D8(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK *, M2C_UNK *, s32, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_8213B644(M2C_UNK, M2C_UNK, M2C_UNK);   /* extern */
M2C_UNK func_8213B720(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK); /* extern */
M2C_UNK func_8213BC00(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, s32); /* extern */
extern M2C_UNK func_8215DFB4;

void func_8215E1A8(void);

M2C_UNK func_8213B464(M2C_UNK);                     /* extern */
M2C_UNK func_8213B560(M2C_UNK, M2C_UNK *, M2C_UNK *, M2C_UNK, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_8213B5D8(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK *, M2C_UNK *, s32, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_8213B644(M2C_UNK, M2C_UNK, M2C_UNK);   /* extern */
M2C_UNK func_8213B720(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK); /* extern */
M2C_UNK func_8213BC00(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, s32); /* extern */

void func_8215E2C4(void);

void BattleAnim_InitializeFocusEnergyUse(void);

M2C_UNK func_8213B560(M2C_UNK, M2C_UNK *, M2C_UNK *, M2C_UNK, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_8213B644(M2C_UNK, M2C_UNK, M2C_UNK);   /* extern */
M2C_UNK func_8213BC00(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, s32); /* extern */
M2C_UNK func_8213BD78(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, s32); /* extern */
M2C_UNK func_82168844(M2C_UNK);                     /* extern */
extern M2C_UNK D_8218E7F8;
extern M2C_UNK BattleAnim_RunOscillatingFlameUnderneathPokemon;

void BattleAnim_InitializeSkyAttackUse1(void);

M2C_UNK func_8213B560(M2C_UNK, M2C_UNK *, M2C_UNK *, M2C_UNK, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_8213B5D8(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK *, M2C_UNK *, s32, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_8213B644(M2C_UNK, M2C_UNK, M2C_UNK);   /* extern */
M2C_UNK func_8213BC00(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, s32); /* extern */
M2C_UNK func_8213C0D8(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK); /* extern */
extern M2C_UNK func_82152FE0;

void BattleAnim_InitializeSkyAttackUse2(void);

M2C_UNK func_8213B560(M2C_UNK, M2C_UNK *, M2C_UNK *, M2C_UNK, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_8213BC00(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, s32); /* extern */
M2C_UNK BattleAnim_InitializeSolarBeamUseSequence();                            /* extern */

void BattleAnim_InitializeSolarBeamUse2(void);

void BattleAnim_CallbackEndEffect76DefaultDescriptorModelFade(Particle* arg0);

M2C_UNK func_8213B560(M2C_UNK, M2C_UNK *, M2C_UNK *, M2C_UNK, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_8213BC00(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, s32); /* extern */
extern M2C_UNK func_8215ED1C;

void BattleAnim_InitializeLargePhysicalHitSpark(void);

M2C_UNK func_8213B560(M2C_UNK, M2C_UNK *, M2C_UNK *, M2C_UNK, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_8213BC00(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, s32); /* extern */

void BattleAnim_InitializeHornDrillHit(void);

void BattleAnim_RunWeakSpear(Particle* arg0);

M2C_UNK func_8213B5D8(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK *, M2C_UNK *, s32, s32, s32, s32, s32, s32); /* extern */
extern M2C_UNK func_8215EFF8;

void BattleAnim_InitializeFuryAttackPeckUse(void);

M2C_UNK func_8213B560(M2C_UNK, M2C_UNK *, M2C_UNK *, M2C_UNK, s32, s32, s32, s32, s32); /* extern */

void BattleAnim_InitializeHornAttackUse(void);

s32 func_8001104C(s32);                             /* extern */
M2C_UNK func_8213C930(s8 *);                      /* extern */
M2C_UNK func_82140518(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_821437E0(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_82152730(s8 *, M2C_UNK);             /* extern */

void func_8215F1B0(s8 *arg0);

M2C_UNK func_8213B644(M2C_UNK, M2C_UNK, M2C_UNK);   /* extern */

void func_8215F290(void);

M2C_UNK func_8213C930(s8 *);                      /* extern */
M2C_UNK func_8213CB3C(s8 *);                      /* extern */
M2C_UNK func_821402B8(s8 *);                      /* extern */
M2C_UNK func_82140548(s8 *, M2C_UNK, M2C_UNK);    /* extern */
s32 func_82140690(s8 *);                          /* extern */
s32 func_821406B4(s8 *);                          /* extern */
M2C_UNK func_8215F2B8(s8 *);                      /* extern */

void func_8215F3EC(s8 *arg0);

void func_8213E1FC(Particle* arg0, f32 arg1);

#endif
