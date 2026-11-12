#ifndef ZERO_BATTLE_ENGINE_MOVE_MODEL_TRANSFORMS_H
#define ZERO_BATTLE_ENGINE_MOVE_MODEL_TRANSFORMS_H

/* Stadium Zero fragment012_17ED00. */
/* C ported from the Stadium 1 decomp: src/fragments/battle_engine/battle_engine_31AA30.c, src/fragments/battle_engine/battle_engine_move_model_transforms.c. */

#include "fragments/battle_engine/battle_engine.h"
#include "model_animation.h"
#include "model_renderer.h"
#include "matrix.h"
#include "pokemon.h"
extern f32 sModelTransformConstants[];
#define NINETY_DEGREES 0x4000
extern s32 pad_D_8438466C;
extern s16 sChargeMoveCues[];
extern ThumbnailSettings sSideThumbnailSettings[2];
extern BattleSceneStateCallback sBattleSceneStateTickSentinel;
extern BattleSceneStateRow sBattleSceneStateRowTable[];

#include "m2c_macros.h"

void BattleScene_ShowSecondaryModelsStaggeredFrame(ActivePokemon* active_pokemon);
void BattleScene_UpdateSecondaryModelTrailPosition(ActivePokemon* pokemon, s16 new_position);
void BattleScene_ResetParticipantModelFlags(ActivePokemon* active_pokemon);
void BattleAnim_WaterfallEnd(UNUSED ActivePokemon* owner, UNUSED ActivePokemon* animated_pokemon);
s32 BattleAnim_ApproachAngleAndCheckThreshold(ActivePokemon* pokemon, s16 phase, s16 camera_offset_scale);
void BattleAnim_WithdrawContinue(ActivePokemon* owner, UNUSED ActivePokemon* animated_pokemon);
void BattleAnim_DrawParticleNoop(UNUSED Particle* arg0, UNUSED CameraNode* arg1);

extern const f32 D_FLT_82194900;
void BattleAnim_InitSwayOffset(ActivePokemon* pokemon, f32 y, s16 theta);

extern const f32 D_FLT_82194904;
extern const f32 D_FLT_82194908;
void BattleAnim_UpdateTransform(ActivePokemon* owner, ActivePokemon* animated_pokemon, f32 height, f32 delta_y, s32 delta_theta);

extern const f32 D_FLT_8219490C;
extern const f32 D_FLT_82194910;
void BattleAnim_UpdateSwayPhysicsToTarget(UNUSED ActivePokemon* owner, ActivePokemon* animated_object, f32 target, f32 delta, s32 theta0, s32 theta1);

void BattleScene_HideParticipantSecondaryModels(ActivePokemon* active_pokemon);

/*
 * BattleScene_ShowSecondaryModelsAtMainTransform
 *
 * Resets the three trailing afterimage models of a Pokemon so that they show
 * at the main model's transform: for afterimages 0..2 it clears the field at
 * +0x16C of the entry and the byte at +0x185 (lodFraction), sets bit 0 of the
 * node flags, stores a per-afterimage value in the halfword at +0x16A (0, 0xE38
 * and 0xF1C8 for the three), and copies the main display object's position
 * (+0x24), rotation (+0x1E) and scale (+0x30) into the afterimage.
 *
 * The local six-byte array is placed at D_821891A8. The orbit
 * helpers use a separate data region recovered for this split.
 *
 * Same code as BattleScene_ShowSecondaryModelsAtMainTransform in the Stadium
 * 1 decomp, except that Zero loops over three afterimages where the donor
 * loops over two.
 */
void BattleScene_ShowSecondaryModelsAtMainTransform(ActivePokemon* pokemon);

void BattleScene_UpdateSecondaryModelOrbit(ActivePokemon* pokemon);

void BattleScene_ShowSecondaryModelsAtMainPose(ActivePokemon* active_pokemon);

extern Vec3f D_821891CC;
s32 func_82109824(ActivePokemon* arg0);

void BattleAnim_PokeBallThrowStart(UNUSED ActivePokemon* owner, ActivePokemon* animated_pokemon);

void BattleAnim_PokeBallThrowContinue(ActivePokemon* owner, ActivePokemon* animated_pokemon);

void BattleAnim_PokeBallThrow(s32 arg0, s8 *arg1);

void BattleAnim_PokeBallLandStart(UNUSED ActivePokemon* owner, ActivePokemon* animated_pokemon);

void BattleAnim_PokeBallLandContinue(ActivePokemon* owner, ActivePokemon* animated_pokemon);

M2C_UNK func_82109E60();                         /* extern */
M2C_UNK func_82109EF8(s32, s8 *);                 /* extern */

void BattleAnim_PokeBallLand(s32 arg0, s8 *arg1);

void BattleAnim_FlyStart(UNUSED ActivePokemon* owner, ActivePokemon* animated_pokemon);

extern f32 D_FLT_82189354[][4];

void BattleAnim_FlyContinue(ActivePokemon* owner, ActivePokemon* animated_pokemon);

M2C_UNK func_82109FFC(s32);                         /* extern */
M2C_UNK func_8210A084(s32, s8 *);                 /* extern */

void BattleAnim_Fly(s32 arg0, s8 *arg1);

void BattleAnim_WaterfallStart(UNUSED ActivePokemon* owner, ActivePokemon* animated_pokemon);

void BattleAnim_WaterfallContinue(ActivePokemon* owner, ActivePokemon* animated_pokemon);

void BattleAnim_Waterfall(ActivePokemon* owner, ActivePokemon* animated_pokemon);

void func_8210A2F4(UNUSED ActivePokemon* owner, ActivePokemon* animated_pokemon);

void func_8210A374(ActivePokemon* owner, ActivePokemon* animated_pokemon);

void func_8210A3DC(s32 arg0, s8 *arg1);

M2C_UNK func_821099CC(s8 *);                      /* extern */

void BattleAnim_SubmissionStart(s32 arg0, s8 *arg1);

s16 func_8000F1FC(s16, M2C_UNK, M2C_UNK, M2C_UNK);  /* extern */
M2C_UNK func_82109AF4(s8 *, s16);                 /* extern */
s32 func_8210A430(s32, s16, s16);                   /* extern */

void BattleAnim_SubmissionContinue(s32 arg0, s8 *arg1);

extern const f64 D_DBL_82194920;
void BattleAnim_SubmissionEnd(ActivePokemon* owner, ActivePokemon* animated_pokemon);

void func_8210A584(UNUSED ActivePokemon* owner, UNUSED ActivePokemon* animated_pokemon);
void BattleAnim_Submission(ActivePokemon* owner, ActivePokemon* animated_pokemon);

M2C_UNK func_821099CC(s8 *);                      /* extern */

void BattleAnim_DigStart(s32 arg0, s8 *arg1);

s16 func_8000F1FC(s16, M2C_UNK, M2C_UNK, M2C_UNK);  /* extern */
M2C_UNK func_82109AF4(s8 *, s16);                 /* extern */
s32 func_8210A430(s32, s16, s16);                   /* extern */

void BattleAnim_DigContinue(s32 arg0, s8 *arg1);

void func_8210A7D8(s32 arg0, s8* arg1);
void BattleAnim_Dig(ActivePokemon* owner, ActivePokemon* animated_pokemon);

M2C_UNK func_8000D700(s32, M2C_UNK, s16, M2C_UNK);  /* extern */
M2C_UNK func_82107790(s8 *);                      /* extern */
M2C_UNK func_821099CC(s8 *);                      /* extern */

void BattleAnim_AgilityStart(s32 arg0, s8 *arg1);

void BattleAnim_AgilityContinue(ActivePokemon* owner, ActivePokemon* animated_pokemon);

void BattleAnim_AgilityEnd(ActivePokemon* owner, ActivePokemon* animated_pokemon);

void func_8210A9B4(ActivePokemon* owner, ActivePokemon* animated_pokemon);
void func_8210AAA4(UNUSED ActivePokemon* owner, UNUSED ActivePokemon* animated_pokemon);
void BattleAnim_Agility(ActivePokemon* owner, ActivePokemon* animated_pokemon);

M2C_UNK func_8000D700(s32, M2C_UNK, s16, M2C_UNK);  /* extern */
M2C_UNK func_82107790(s8 *);                      /* extern */
void BattleScene_ShowSecondaryModelsAtMainTransform(ActivePokemon*);

void BattleAnim_DoubleTeamStart(s32 arg0, s8 *arg1);

void BattleAnim_DoubleTeamContinue(UNUSED ActivePokemon* owner, ActivePokemon* animated_pokemon);

void BattleAnim_DoubleTeam(ActivePokemon* owner, ActivePokemon* animated_pokemon);

void BattleAnim_ResetOwnerFacingAndExitStatusIdle(ActivePokemon* arg0);

M2C_UNK func_8000D700(s32, M2C_UNK, s16, M2C_UNK);  /* extern */
M2C_UNK func_82107790(s8 *);                      /* extern */

void BattleAnim_SeismicTossStart(s32 arg0, s8 *arg1);

void BattleAnim_SeismicTossContinue(UNUSED ActivePokemon* owner, ActivePokemon* animated_pokemon);

void func_8210AE34(ActivePokemon* owner, ActivePokemon* animated_pokemon);
void BattleAnim_SeismicToss(ActivePokemon* owner, ActivePokemon* animated_pokemon);

M2C_UNK func_82109764(s8 *);                      /* extern */
M2C_UNK func_82109C88(s8 *);                      /* extern */

void BattleAnim_MinimizeStart(s8 *arg0, s8 *arg1);

M2C_UNK func_8210942C(s32);                         /* extern */
s32 func_82109824(ActivePokemon*);
M2C_UNK func_8210C1A8(s32, M2C_UNK, M2C_UNK);       /* extern */

void BattleAnim_MinimizeContinue(s32 arg0, s32 arg1);

void BattleAnim_Minimize(ActivePokemon* owner, ActivePokemon* animated_pokemon);

void BattleAnim_WithdrawStart(s32 arg0, s8 *arg1);

void func_8210B164(ActivePokemon* owner, ActivePokemon* animated_pokemon);
void BattleAnim_Withdraw(ActivePokemon* owner, ActivePokemon* animated_pokemon);

void BattleAnim_MeditateStart(UNUSED ActivePokemon* owner, ActivePokemon* animated_pokemon);

void BattleAnim_MeditateContinue(ActivePokemon* owner, ActivePokemon* animated_pokemon);

void BattleAnim_MeditateEnd(ActivePokemon* owner, ActivePokemon* animated_pokemon);

void func_8210B2C4(ActivePokemon* owner, ActivePokemon* animated_pokemon);
void func_8210B3F0(UNUSED ActivePokemon* owner, UNUSED ActivePokemon* animated_pokemon);
void func_8210B280(UNUSED ActivePokemon* owner, ActivePokemon* animated_pokemon);
void BattleAnim_Meditate(ActivePokemon* owner, ActivePokemon* animated_pokemon);

void BattleAnim_SquishHitReactionStart(ActivePokemon* owner, ActivePokemon* animated_pokemon);

void BattleAnim_SquishHitReactionContinue(ActivePokemon* owner, ActivePokemon* animated_pokemon);

M2C_UNK func_8210B58C(s32);                         /* extern */
M2C_UNK func_8210B5C8(s32, s8 *);                 /* extern */

void BattleAnim_SquishHitReaction(s32 arg0, s8 *arg1);

void BattleAnim_LassoMoveHitReactionStart(ActivePokemon* owner, ActivePokemon* animated_pokemon);

void BattleAnim_LassoMoveHitReactionContinue(ActivePokemon* owner, ActivePokemon* animated_pokemon);

M2C_UNK func_8210B824(s32, s8 *);                 /* extern */

void BattleAnim_LassoMoveHitReaction(s32 arg0, s8 *arg1);

void BattleAnim_SurfStart(s32 arg0, s8 *arg1);

void BattleAnim_SurfContinue(ActivePokemon* owner, ActivePokemon* animated_pokemon);
void BattleAnim_Surf(ActivePokemon* owner, ActivePokemon* animated_pokemon);

void BattleAnim_PlayTransformInducingAnimation(s32 side_index);

#endif
