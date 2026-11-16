/* Stadium Zero fragment012_17ED00. */
/* C ported from the Stadium 1 decomp: src/fragments/battle_engine/battle_engine_3438B0.c. */

#include "battle.h"
#include "gfx_buffer.h"

#include "m2c_macros.h"

void BattleAnim_DrawFullScreenColorOverlay(u8 arg0, u8 arg1, u8 arg2, u8 arg3);

/**
 * Fills the whole screen with the color (arg0, arg1, arg2) at alpha arg3.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (29 of the moves).
 * @unverified Name from Stadium 1.
 */
void BattleAnim_DrawFullScreenColorOverlay(u8 arg0, u8 arg1, u8 arg2, u8 arg3) {
    gSPDisplayList(gDisplayListHead++, gDL_BeginColorFill);

    ParticleGfx_SetPrimColor(arg0, arg1, arg2, arg3);

    gSPTextureRectangle(gDisplayListHead++, 0, 0, 0x04FC, 0x03BC, G_TX_RENDERTILE, 0, 0, 0x1000, 0x0400);
    gSPDisplayList(gDisplayListHead++, gDL_EndColorFill);
}

void BattleAnim_RenderEffectsFrameNop(void);
void BattleAnim_DrawWorldParticleChainsThunk(s32, M2C_UNK);
void BattleAnim_DrawScreenParticlesThunk(s32, M2C_UNK);
extern Gfx D_82190100[];
extern Gfx D_821900B0[];
extern s32 D_8219A7CC;
extern s16 D_8219A8C0;
extern s16 D_8219A8BE;
extern s16 D_8219A8BC;
extern s16 D_8219A8BA;
extern s16 D_8219A8D0;
extern s16 D_8219A8CE;
extern s16 D_8219A8CC;
extern s16 D_8219A8CA;
extern s16 D_8219A8C8;
extern s16 D_8219A8C6;
extern s16 D_8219A8C4;
extern s16 D_8219A8C2;
extern s16 D_8219A8D8;
extern s16 D_8219A8D6;
/**
 * Draws the frame's battle effects: runs the effect draw callbacks, allocates the particle
 * matrix pool, sets the prim, fog, env and blend colors and the stage tint, draws the 3D
 * effects, then sets a 320x240 orthographic projection and draws the 2D overlays.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (165 of the moves).
 * @unverified Name from Stadium 1.
 */
void BattleAnim_RenderEffectsFrame(CameraNode* arg0) {
    BattleAnim_DrawEffectCallbacks(arg0);
    gParticleMatrixPool = Gfx_AllocDisplayList(sizeof(ParticleMatrixPool));
    gParticleMatrixPoolIndex = 0;
    D_8219A7CC += 1;

    gSPDisplayList(gDisplayListHead++, D_82190100);

    BattleAnim_RenderEffectsFrameNop();
    ParticleGfx_SetPrimColor(D_8219A8BA, D_8219A8BC, D_8219A8BE, D_8219A8C0);
    ParticleGfx_SetFogColor(D_8219A8CA, D_8219A8CC, D_8219A8CE, D_8219A8D0);
    ParticleGfx_SetEnvColor(D_8219A8C2, D_8219A8C4, D_8219A8C6, D_8219A8C8);
    ParticleGfx_SetBlendColor(gBlendColorR, gBlendColorG, D_8219A8D6, D_8219A8D8);
    Battle_SetStageTintColor(gSavedPrimColorR, gSavedPrimColorG, gSavedPrimColorB);
    BattleAnim_DrawWorldParticleChainsThunk(0, (M2C_UNK)arg0);
    guOrtho(&gParticleMatrixPool->orthoMatrix, 0.0f, 320.0f, 240.0f, 0.0f, -2.0f, 2.0f, 1.0f);

    gSPMatrix(gDisplayListHead++, (u32)&gParticleMatrixPool->orthoMatrix & 0x1FFFFFFF,
              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    gSPDisplayList(gDisplayListHead++, gDL_BeginUIOverlay);

    ParticleGfx_PipeSync();
    BattleAnim_DrawScreenParticlesThunk(0, (M2C_UNK)arg0);

    gSPDisplayList(gDisplayListHead++, D_821900B0);
}

M2C_UNK BattleAnim_DrawScreenParticles(M2C_UNK);                     /* extern */

/**
 * Forwards arg1 to BattleAnim_DrawScreenParticles.
 * @unverified Name guessed from the code.
 */
void BattleAnim_DrawScreenParticlesThunk(s32 unused, M2C_UNK camera) {
    BattleAnim_DrawScreenParticles(camera);
}

M2C_UNK BattleAnim_DrawWorldParticleChains(M2C_UNK);                     /* extern */

/**
 * Forwards arg1 to BattleAnim_DrawWorldParticleChains.
 * @unverified Name guessed from the code.
 */
void BattleAnim_DrawWorldParticleChainsThunk(s32 unused, M2C_UNK camera) {
    BattleAnim_DrawWorldParticleChains(camera);
}
