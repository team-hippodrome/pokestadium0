/* Stadium Zero fragment012_17ED00. */
/* C ported from the Stadium 1 decomp: src/fragments/battle_engine/battle_engine_31AA30.c, src/fragments/battle_engine/battle_engine_32B680.c, src/fragments/battle_engine/battle_engine_move_animation.c. */

#include "fragments/battle_engine/battle_engine.h"
#include "model_animation.h"
#include "geo_render.h"
#include "gfx_buffer.h"
#include "matrix.h"
#include "math_util.h"

#include "fragments/battle_engine/battle_engine.h"

#include "fragments/battle_engine/battle_engine.h"
#include "model_animation.h"
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
#include "matrix.h"
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

#include "m2c_macros.h"
extern Vtx D_84385C80[];
extern Vtx D_82191480[];
extern Vtx D_82191080[];

extern Gfx D_821903D0[];
extern Vtx D_82190E50[];

void ParticleEffect_Noop(UNUSED s32 arg0, UNUSED s32 arg1);
void BattleAnim_DrawFlameHit(Particle* arg0, CameraNode* arg1);
void BattleAnim_DrawFlameUse(Particle* arg0, CameraNode* arg1);
void func_82142678(UNUSED ActivePokemon* active_pokemon, UNUSED s32 unused);

void BattleAnim_DrawAsset76Ia8FrameWithAsset77I4Overlay(Particle* arg0, CameraNode* arg1);

void ParticleEffect_Noop(UNUSED s32 arg0, UNUSED s32 arg1) {
}

void BattleAnim_DrawAsset76Ia8FrameWithAsset77I4Overlay(Particle* arg0, CameraNode* arg1) {
    ParticleGfx_LoadTextureIa8(sBattleAnimAssetPointers[0x76] + (arg0->textureFrame << 0xB), 0x20, 0x40);
    ParticleGfx_LoadTextureI4MultiBlockWrapSTWithShift(sBattleAnimAssetPointers[0x77], 0x40, 0x40, 2, 1);
    ParticleGfx_SetAnimatedAuxTileSize(0, 0xA, 0x40, 0x40);
    ParticleGfx_SetPrimEnvLodTextureCombine(0x80, arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->prim_a, arg0->env_r, arg0->env_g, arg0->env_b);
    ParticleGfx_DrawModelQuad(arg1, arg0->worldPosition, arg0->scale, D_82191080);
}

/**
 * Draw the flames when being *hit* by Flamethrower or dragon rage
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Flamethrower, Dragon Rage.
 */
void BattleAnim_DrawFlameHit(Particle* arg0, CameraNode* arg1) {
    gSPDisplayList(gDisplayListHead++, D_821904C8);

    BattleAnim_DrawAsset76Ia8FrameWithAsset77I4Overlay(arg0, arg1);
}

/**
 * Draw the flames when using Flamethrower, Dragon Rage, Fire Spin, Rage, Bide, Self-Destruct, Fire Blast, Sky Attack,
 * or Explosion
 * Seen in play (2026-11-13) (unattended Free Battle in which every Pokémon knows only Metronome, 70
 * turns): ran.
 * @unverified Name and comment from Stadium 1.
 */
void BattleAnim_DrawFlameUse(Particle* arg0, CameraNode* arg1) {
    gSPDisplayList(gDisplayListHead++, D_82190548);

    BattleAnim_DrawAsset76Ia8FrameWithAsset77I4Overlay(arg0, arg1);
}

/**
 * Seen in play (2026-11-13) in the 165-move sweep (each move used once by the 1P Pokémon): it ran
 * only for Sing, Sleep Powder, Hypnosis, Lovely Kiss and Spore.
 */
void BattleAnim_DrawSleepMoveAnimatedI4(Particle* arg0, CameraNode* arg1) {
    ParticleGfx_PushBillboardMatrix(arg1, arg0->worldPosition, arg0->scale);

    gSPDisplayList(gDisplayListHead++, D_82190548);

    ParticleGfx_LoadTextureI4WrapSTNoMirror(sBattleAnimAssetPointers[0x1F], 0x20, 0x40);
    ParticleGfx_SetAnimatedTileSize(0, 8, 0x20, 0x40);
    ParticleGfx_SetPrimEnvColorShadeCombine(0xFF, 0xFF, 0xFF, arg0->prim_a, 0xFF, 0xFF, 0xFF, 0xFF);

    gDPSetRenderMode(gDisplayListHead++, G_RM_PASS, G_RM_AA_ZB_XLU_SURF2);
    gSPDisplayList(gDisplayListHead++, sBattleAnimAssetPointers[0x20]);
}

/**
 * Raws the rocks that spawn out of the tunnel when pokemon other than diglett and dugtrio use dig
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Dig.
 */
s32 BattleAnim_DrawDigRocks(Particle* arg0, UNUSED CameraNode* arg1) {
    ParticleGfx_PushTransformMatrix(arg0->worldPosition, arg0->rotation, arg0->scale);

    gSPDisplayList(gDisplayListHead++, gDL_ItemIcon);

    ParticleGfx_LoadTextureRgba16(sBattleAnimAssetPointers[0xBC], 0x20, 0x20);

    gSPDisplayList(gDisplayListHead++, sBattleAnimAssetPointers[0xBD]);
}

extern Vtx D_82191880[];

void BattleAnim_DrawAssets27And28LayeredI4QuadVariantA(Particle* arg0, UNUSED CameraNode* arg1) {
    ParticleGfx_Push2DTransform(arg0->worldPosition.x, arg0->worldPosition.y, arg0->rotation.z, arg0->scale);

    gSPDisplayList(gDisplayListHead++, D_821904C8);

    ParticleGfx_SetPrimEnvLodCombine(0x80, arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->prim_a, arg0->env_r, arg0->env_g, arg0->env_b);
    ParticleGfx_LoadTextureI4WrapSTNoMirror(sBattleAnimAssetPointers[0x27], 0x40, 0x40);
    ParticleGfx_SetAnimatedTileSize(2, -2, 0x40, 0x40);
    ParticleGfx_LoadTextureI4MultiBlockWrapST(sBattleAnimAssetPointers[0x28], 0x40, 0x40);
    ParticleGfx_SetAnimatedAuxTileSize(0, -1, 0x40, 0x40);
    ParticleGfx_DrawQuadVertices(D_82191880);
}

extern Vtx D_821918C0[];

void BattleAnim_DrawAssets27And28LayeredI4QuadVariantB(Particle* arg0, UNUSED CameraNode* arg1) {
    ParticleGfx_Push2DTransform(arg0->worldPosition.x, arg0->worldPosition.y, arg0->rotation.z, arg0->scale);

    gSPDisplayList(gDisplayListHead++, D_821904C8);

    ParticleGfx_SetPrimEnvLodCombine(0x80, arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->prim_a, arg0->env_r, arg0->env_g, arg0->env_b);
    ParticleGfx_LoadTextureI4WrapSTNoMirror(sBattleAnimAssetPointers[0x27], 0x40, 0x40);
    ParticleGfx_SetAnimatedTileSize(1, -3, 0x40, 0x40);
    ParticleGfx_LoadTextureI4MultiBlockWrapST(sBattleAnimAssetPointers[0x28], 0x40, 0x40);
    ParticleGfx_SetAnimatedAuxTileSize(-2, -2, 0x40, 0x40);
    ParticleGfx_DrawQuadVertices(D_821918C0);
}

/**
 * Draw the lightest mist for mist/smoke moves (Mist, Smokescreen, Haze, Smog, Poison Gas)
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Haze, Mist, Poison Gas, Smog and Smokescreen.
 */
void BattleAnim_DrawMistLightest(Particle* arg0, UNUSED CameraNode* arg1) {
    ParticleGfx_Push2DTransform(arg0->worldPosition.x, arg0->worldPosition.y, arg0->rotation.z, arg0->scale);

    gSPDisplayList(gDisplayListHead++, D_821904C8);

    ParticleGfx_SetPrimEnvLodCombine(0x80, arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->prim_a, arg0->env_r, arg0->env_g, arg0->env_b);
    ParticleGfx_LoadTextureMultiBlock4(sBattleAnimAssetPointers[0x29], 0, 0, 4, 0x20, 0x20, 1, 1, 5, 5, 2, 0);
    ParticleGfx_SetAnimatedTileSize(1, 1, 0x20, 0x20);
    ParticleGfx_LoadTextureMultiBlock4(sBattleAnimAssetPointers[0x29], 0x100, 1, 4, 0x20, 0x20, 1, 1, 5, 5, 1, 0xF);
    ParticleGfx_SetAnimatedAuxTileSize(-1, 1, 0x20, 0x20);
    ParticleGfx_DrawQuadVertices(gFullscreenQuadVtx);
}

void BattleAnim_DrawAsset87AnimatedI4Quad(Particle* arg0, UNUSED CameraNode* arg1) {
    ParticleGfx_Push2DTransform(arg0->worldPosition.x, arg0->worldPosition.y, arg0->rotation.z, arg0->scale);

    gSPDisplayList(gDisplayListHead++, D_821904C8);

    ParticleGfx_SetPrimEnvColorCombine(arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->env_r, arg0->env_g, arg0->env_b, arg0->prim_a);
    ParticleGfx_LoadTextureI4WrapSTNoMirror(sBattleAnimAssetPointers[0x87], 0x20, 0x20);
    ParticleGfx_SetAnimatedTileSize(0, 2, 0x20, 0x20);
    ParticleGfx_DrawQuadVertices(gFullscreenQuadVtx);
}

void func_82141F6C(Particle* arg0, u8* arg1) {
    ParticleGfx_Push2DTransformYScaled(arg0->worldPosition.x, arg0->worldPosition.y, arg0->rotation.z, arg0->scale);

    gSPDisplayList(gDisplayListHead++, D_821904C8);

    ParticleGfx_SetPrimEnvColorCombine(arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->env_r, arg0->env_g, arg0->env_b, arg0->prim_a);
    ParticleGfx_DrawI4TextureAtlas(sBattleAnimAssetPointers[0x19], D_82191480, 0x40, 0x40, 0x40, 0x40);
}

void func_82142048(Particle* arg0, u8* arg1) {
    ParticleGfx_Push2DTransformYScaled(arg0->worldPosition.x, arg0->worldPosition.y, arg0->rotation.z, arg0->scale);

    gSPDisplayList(gDisplayListHead++, D_821904C8);

    ParticleGfx_SetPrimEnvColorCombine(arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->env_r, arg0->env_g, arg0->env_b, arg0->prim_a);
    ParticleGfx_DrawI4TextureAtlas(sBattleAnimAssetPointers[0x5E], D_82191480, 0x40, 0x40, 0x40, 0x40);
}

extern Vtx D_8140E018[];
extern Vtx D_84385CC0[];
extern Vtx D_84385D00[];
void BattleAnim_DrawAsset1AFrameI4Quad(Particle* arg0, UNUSED CameraNode* arg1) {
    gSPDisplayList(gDisplayListHead++, D_82190548);
    gSPClearGeometryMode(gDisplayListHead++, G_CULL_BACK);

    ParticleGfx_LoadTextureI4Alias(sBattleAnimAssetPointers[0x1A] + (arg0->textureFrame << 9), 0x20, 0x20);
    ParticleGfx_SetPrimEnvColorCombine(arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->env_r, arg0->env_g, arg0->env_b, arg0->prim_a);
    ParticleGfx_DrawTransformedQuad(arg0->worldPosition, arg0->rotation, arg0->scale, D_82190E50);

    gSPSetGeometryMode(gDisplayListHead++, G_CULL_BACK);
}

void BattleAnim_DrawAsset1CRgba16Quad(Particle* arg0, UNUSED CameraNode* arg1) {
    gSPDisplayList(gDisplayListHead++, D_821903D0);
    gSPClearGeometryMode(gDisplayListHead++, G_CULL_BACK);

    ParticleGfx_LoadTextureRgba16(sBattleAnimAssetPointers[0x1C], 0x20, 0x20);
    ParticleGfx_DrawTransformedQuad(arg0->worldPosition, arg0->rotation, arg0->scale, D_82190E50);

    gSPSetGeometryMode(gDisplayListHead++, G_CULL_BACK);
}

/**
 * Particle callback of the Petal Dance animation. Player sweep (all 165 moves used in battle):
 * only Petal Dance reached this function.
 */
void BattleAnim_PetalDanceParticleDraw(Particle* arg0, UNUSED CameraNode* arg1) {
    gSPDisplayList(gDisplayListHead++, D_821903D0);
    gSPClearGeometryMode(gDisplayListHead++, G_CULL_BACK);

    ParticleGfx_LoadTextureRgba16(sBattleAnimAssetPointers[0x1E], 0x20, 0x20);
    ParticleGfx_DrawTransformedQuad(arg0->worldPosition, arg0->rotation, arg0->scale, D_82190E50);

    gSPSetGeometryMode(gDisplayListHead++, G_CULL_BACK);
}

/**
 * Particle callback of the Wing Attack animation. Player sweep (all 165 moves used in battle):
 * only Wing Attack reached this function.
 */
void BattleAnim_WingAttackParticleDraw(Particle* arg0, UNUSED CameraNode* arg1) {
    gSPDisplayList(gDisplayListHead++, D_821903D0);
    gSPClearGeometryMode(gDisplayListHead++, G_CULL_BACK);

    ParticleGfx_LoadTextureRgba16(sBattleAnimAssetPointers[0xC3], 0x20, 0x20);
    ParticleGfx_DrawTransformedQuad(arg0->worldPosition, arg0->rotation, arg0->scale, D_82190E50);

    gSPSetGeometryMode(gDisplayListHead++, G_CULL_BACK);
}

extern Vtx D_82190E50[];
void BattleAnim_DrawAsset1DRotatedI4Quad(Particle* arg0, UNUSED CameraNode* arg1) {
    Vec3s sp40;

    gSPDisplayList(gDisplayListHead++, D_821904C8);
    gSPClearGeometryMode(gDisplayListHead++, G_CULL_BACK);

    ParticleGfx_LoadTextureI4Alias(sBattleAnimAssetPointers[0x1D], 0x20, 0x20);
    ParticleGfx_SetPrimEnvColorCombine(arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->env_r, arg0->env_g, arg0->env_b, arg0->prim_a);
    sp40.x = arg0->rotation.x + 0x4000;
    sp40.y = arg0->rotation.y + 0x4000;
    sp40.z = arg0->rotation.z;
    ParticleGfx_DrawTransformedQuad(arg0->worldPosition, sp40, arg0->scale, D_82190E50);

    gSPSetGeometryMode(gDisplayListHead++, G_CULL_BACK);
}

/**
 * Empty function. Not referenced in C.
 */
void func_82142678(UNUSED ActivePokemon* active_pokemon, UNUSED s32 unused) {
}

extern Vtx D_82191100[];

void BattleAnim_DrawAsset13FrameI4YScaledQuadA(Particle* arg0, UNUSED CameraNode* arg1) {
    gSPDisplayList(gDisplayListHead++, D_82190548);

    ParticleGfx_LoadTextureI4Alias(sBattleAnimAssetPointers[0x13] + (gParticleFrameMod8 * 0x600), 0x20, 0x60);
    ParticleGfx_SetPrimEnvColorCombine(arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->env_r, arg0->env_g, arg0->env_b, arg0->prim_a);

    gSPClearGeometryMode(gDisplayListHead++, G_CULL_BACK);

    ParticleGfx_DrawTransformedQuadYScaled(arg0->worldPosition, arg0->rotation, arg0->scale, D_82191100);

    gSPSetGeometryMode(gDisplayListHead++, G_CULL_BACK);
}

extern Vtx D_82191140[];

void BattleAnim_DrawAsset13FrameI4YScaledQuadB(Particle* arg0, UNUSED CameraNode* arg1) {
    gSPDisplayList(gDisplayListHead++, D_82190548);
    gSPClearGeometryMode(gDisplayListHead++, G_CULL_BACK);

    ParticleGfx_LoadTextureI4Alias(sBattleAnimAssetPointers[0x13] + (gParticleFrameMod8 * 0x600), 0x20, 0x60);
    ParticleGfx_SetPrimEnvColorCombine(arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->env_r, arg0->env_g, arg0->env_b, arg0->prim_a);
    ParticleGfx_DrawTransformedQuadYScaled(arg0->worldPosition, arg0->rotation, arg0->scale, D_82191140);

    gSPSetGeometryMode(gDisplayListHead++, G_CULL_BACK);
}

extern Vtx D_82191180[];
void func_821428F8(Particle* arg0, UNUSED CameraNode* arg1) {
    gSPDisplayList(gDisplayListHead++, D_82190548);
    gSPClearGeometryMode(gDisplayListHead++, G_CULL_BACK);

    ParticleGfx_LoadTextureI4Alias(sBattleAnimAssetPointers[0x13] + (gParticleFrameMod8 * 0x600), 0x20, 0x60);
    ParticleGfx_SetPrimEnvColorCombine(arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->env_r, arg0->env_g, arg0->env_b, arg0->prim_a);
    ParticleGfx_DrawTransformedQuadYScaled(arg0->worldPosition, arg0->rotation, arg0->scale, D_82191180);

    gSPSetGeometryMode(gDisplayListHead++, G_CULL_BACK);
}

extern Vtx D_82191100[];

void BattleAnim_DrawAsset13FrameI4ModelQuadA(Particle* arg0, CameraNode* arg1) {
    gSPDisplayList(gDisplayListHead++, D_82190548);
    gSPClearGeometryMode(gDisplayListHead++, G_CULL_BACK);

    ParticleGfx_LoadTextureI4Alias(sBattleAnimAssetPointers[0x13] + (gParticleFrameMod8 * 0x600), 0x20, 0x60);
    ParticleGfx_SetPrimEnvColorCombine(arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->env_r, arg0->env_g, arg0->env_b, arg0->prim_a);
    ParticleGfx_DrawModelQuadRotatedYScaled(arg1, arg0->worldPosition, arg0->scale, D_82191100, arg0->rotation.z);

    gSPSetGeometryMode(gDisplayListHead++, G_CULL_BACK);
}

extern Vtx D_82191140[];

void func_82142B60(Particle* arg0, CameraNode* arg1) {
    gSPDisplayList(gDisplayListHead++, D_82190548);
    gSPClearGeometryMode(gDisplayListHead++, G_CULL_BACK);

    ParticleGfx_LoadTextureI4Alias(sBattleAnimAssetPointers[0x13] + (gParticleFrameMod8 * 0x600), 0x20, 0x60);
    ParticleGfx_SetPrimEnvColorCombine(arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->env_r, arg0->env_g, arg0->env_b, arg0->prim_a);
    ParticleGfx_DrawModelQuadRotatedYScaled(arg1, arg0->worldPosition, arg0->scale, D_82191140, arg0->rotation.z);

    gSPSetGeometryMode(gDisplayListHead++, G_CULL_BACK);
}

extern Vtx D_82191180[];

/**
 * Particle callback of the Thundershock animation. Player sweep (all 165 moves used in battle):
 * only Thundershock reached this function.
 */
void BattleAnim_ThunderShockParticleDraw(Particle* arg0, CameraNode* arg1) {
    gSPDisplayList(gDisplayListHead++, D_82190548);
    gSPClearGeometryMode(gDisplayListHead++, G_CULL_BACK);

    ParticleGfx_LoadTextureI4Alias(sBattleAnimAssetPointers[0x13] + (gParticleFrameMod8 * 0x600), 0x20, 0x60);
    ParticleGfx_SetPrimEnvColorCombine(arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->env_r, arg0->env_g, arg0->env_b, arg0->prim_a);
    ParticleGfx_DrawModelQuadRotatedYScaled(arg1, arg0->worldPosition, arg0->scale, D_82191180, arg0->rotation.z);

    gSPSetGeometryMode(gDisplayListHead++, G_CULL_BACK);
}

void BattleAnim_DrawAsset1BI4TriangleA(Particle* arg0, UNUSED CameraNode* arg1) {
    gSPDisplayList(gDisplayListHead++, D_821904C8);
    gSPClearGeometryMode(gDisplayListHead++, G_CULL_BACK);

    ParticleGfx_LoadTextureI4Alias(sBattleAnimAssetPointers[0x1B], 0x10, 0x100);
    ParticleGfx_SetPrimEnvColorCombine(0xFF, 0xFF, 0xFF, arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->prim_a);
    ParticleGfx_DrawTransformedTriangle(arg0->worldPosition, arg0->rotation, arg0->scale, gVtx_UI_TriangleSmall);

    gSPSetGeometryMode(gDisplayListHead++, G_CULL_BACK);
}

extern Vtx D_82190D60[];
void func_82142EDC(Particle* arg0, UNUSED CameraNode* arg1) {
    gSPDisplayList(gDisplayListHead++, D_821904C8);
    gSPClearGeometryMode(gDisplayListHead++, G_CULL_BACK);

    ParticleGfx_LoadTextureI4Alias(sBattleAnimAssetPointers[0x1B], 0x10, 0x100);
    ParticleGfx_SetPrimEnvColorCombine(0xFF, 0xFF, 0xFF, arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->prim_a);
    ParticleGfx_DrawTransformedTriangle(arg0->worldPosition, arg0->rotation, arg0->scale, D_82190D60);

    gSPSetGeometryMode(gDisplayListHead++, G_CULL_BACK);
}

void BattleAnim_DrawAsset13FrameDiv2I4Quad(Particle* arg0, UNUSED CameraNode* arg1) {
    gSPDisplayList(gDisplayListHead++, D_821904C8);
    gSPClearGeometryMode(gDisplayListHead++, G_CULL_BACK);

    ParticleGfx_LoadTextureI4Alias(sBattleAnimAssetPointers[0x13] + ((gParticleFrameDiv2 & 7) * 0x600), 0x20, 0x60);
    ParticleGfx_SetPrimEnvColorCombine(0xFF, 0xFF, 0xFF, 0, 0x64, 0xC8, 0xFF);
    ParticleGfx_DrawTransformedQuad(arg0->worldPosition, arg0->rotation, arg0->scale, gVtx_UI_ComplexQuad);

    gSPSetGeometryMode(gDisplayListHead++, G_CULL_BACK);
}

void BattleAnim_DrawAsset18FrameI4ModelQuad(Particle* arg0, CameraNode* arg1) {
    gSPDisplayList(gDisplayListHead++, D_82190548);

    ParticleGfx_LoadTextureI4Alias(sBattleAnimAssetPointers[0x18] + (arg0->textureFrame << 9), 0x20, 0x20);
    ParticleGfx_SetPrimEnvColorCombine(arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->env_r, arg0->env_g, arg0->env_b, arg0->prim_a);
    ParticleGfx_DrawModelQuadRotated(arg1, arg0->worldPosition, arg0->scale, D_82190E50, arg0->rotation.z);
}

void BattleAnim_DrawAssetA9I4XYScaledQuad(Particle* arg0, UNUSED CameraNode* arg1) {
    gSPDisplayList(gDisplayListHead++, D_82190548);
    gSPClearGeometryMode(gDisplayListHead++, G_CULL_BACK);

    ParticleGfx_LoadTextureI4Alias(sBattleAnimAssetPointers[0xA9], 0x20, 0x20);
    ParticleGfx_SetPrimEnvColorCombine(arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->env_r, arg0->env_g, arg0->env_b, arg0->prim_a);
    ParticleGfx_DrawTransformedQuadXYScaled(arg0->worldPosition, arg0->rotation, arg0->scale, arg0->scaleTarget, gVtx_UI_RectVertical);

    gSPSetGeometryMode(gDisplayListHead++, G_CULL_BACK);
}

M2C_UNK func_8216D640(u8, u8, u8, u8);              /* extern */

void func_82143344(s8 *arg0, M2C_UNK arg1) {
    func_8216D640(M2C_FIELD(arg0, u8 *, 0xBA), M2C_FIELD(arg0, u8 *, 0xBB), M2C_FIELD(arg0, u8 *, 0xBC), M2C_FIELD(arg0, u8 *, 0xC0));
}
