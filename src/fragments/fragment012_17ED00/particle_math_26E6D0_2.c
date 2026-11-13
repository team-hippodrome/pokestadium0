/* Stadium Zero fragment012_17ED00. */
/* C ported from the Stadium 1 decomp: src/fragments/particle_math/particle_math_26E6D0.c. */

#include "fragments/particle_math/particle_math.h"
extern u8 gParticlePalette[][3];
extern u8 gParticlePaletteSetA[];
extern u8 gParticlePaletteSetB[];
extern u8 gParticleRandomPaletteIndices[];
extern u8 gParticlePalettePairs[][2];

#include "m2c_macros.h"
extern Vtx D_82191440[];
extern Vtx D_82190D90[];
extern Vtx D_821917C0[];
extern Vtx D_82191040[];
extern Vtx D_82191080[];
extern Vtx D_82191000[];

void ParticleGfx_LoadTextureCallbackI4FrameDiv2Mod8_64x64(UNUSED Particle* arg0, u8* texture);
void ParticleGfx_LoadTextureCallbackI4WrapST_64x64(UNUSED Particle* arg0, u8* texture);
void ParticleGfx_LoadTextureCallbackIa8WrapST_64x64(UNUSED Particle* arg0, u8* texture);

/**
 * Load a texture frame selected by the shared particle clock using ParticleGfx_LoadTextureI4Alias.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void ParticleGfx_LoadTextureCallbackI4FrameDiv2Mod8_64x64(UNUSED Particle* arg0, u8* texture) {
    ParticleGfx_LoadTextureI4Alias(&texture[(gParticleFrameDiv2 & 7) * (64 * 64 / 2)], 64, 64);
}

M2C_UNK func_8216BFE8(s32, M2C_UNK, M2C_UNK);       /* extern */

void func_82140EAC(s8 *arg0, s32 arg1) {
    func_8216BFE8((M2C_FIELD(arg0, s8 *, 0xC3) << 0xB) + arg1, 0x40, 0x40);
}

/**
 * Load the supplied texture using ParticleGfx_LoadTextureI4WrapST.
 * Seen in play (2026-11-13) in the 165-move sweep (Razor Wind, Whirlwind, Slam and others): it
 * emitted an I texture load (FD900000) with mirror+wrap and mask 6 on S and T (G_SETTILE 07058160),
 * i.e. 64x64.
 */
void ParticleGfx_LoadTextureCallbackI4WrapST_64x64(UNUSED Particle* arg0, u8* texture) {
    ParticleGfx_LoadTextureI4WrapST(texture, 64, 64);
}

/**
 * Load the supplied texture using ParticleGfx_LoadTextureIa8WrapST.
 * Seen in play (2026-11-13) in the 165-move sweep (Water Gun, Hydro Pump): it emitted an IA texture
 * load (FD700000) with mirror+wrap and mask 6 on S and T (G_SETTILE 07058160), i.e. 64x64.
 */
void ParticleGfx_LoadTextureCallbackIa8WrapST_64x64(UNUSED Particle* arg0, u8* texture) {
    ParticleGfx_LoadTextureIa8WrapST(texture, 64, 64);
}

extern Vtx D_82190E50[];

/**
 * Draw the particle using its world position, scale, color/angle parameters, and the selected vertex template.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void ParticleGfx_DrawBillboardPrim(Particle* arg0, CameraNode* arg1) {
    ParticleGfx_SetPrimColorTextureCombine(arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->prim_a);
    ParticleGfx_DrawModelQuad(arg1, arg0->worldPosition, arg0->scale, D_82190E50);
}

/**
 * Draw the particle using its world position, scale, color/angle parameters, and the selected vertex template.
 * Seen in play (2026-11-13) in the 165-move sweep (Water Gun, Hydro Pump, Surf, Waterfall): it
 * emitted the particle's prim color (FFFFFFFF), env color (64C8FF) and the prim/env combiner, then
 * a camera-facing quad.
 */
void ParticleGfx_DrawBillboardPrimEnv(Particle* arg0, CameraNode* arg1) {
    ParticleGfx_SetPrimEnvColorCombine(arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->env_r, arg0->env_g, arg0->env_b, arg0->prim_a);
    ParticleGfx_DrawModelQuad(arg1, arg0->worldPosition, arg0->scale, D_82190D90);
}

/**
 * Disable back-face culling, draw the transformed primitive, then restore culling; the s32 function has no return
 * statement.
 * Seen in play (2026-11-13) in the 165-move sweep (Scratch, Cut, Vine Whip): it emitted
 * G_GEOMETRYMODE D9FFFBFF 00000000 (clear G_CULL_BACK), the particle's prim and env colors and the
 * transformed quad, then turned culling back on. Was ParticleGfx_DrawBillboardDoubleSided, but the
 * quad uses the particle's own rotation, not the camera.
 */
s32 ParticleGfx_DrawDoubleSidedPrimEnvTransformedQuad(Particle* arg0, UNUSED CameraNode* arg1) {
    gSPClearGeometryMode(gDisplayListHead++, G_CULL_BACK);

    ParticleGfx_SetPrimEnvColorCombine(arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->env_r, arg0->env_g, arg0->env_b, arg0->prim_a);
    ParticleGfx_DrawTransformedQuad(arg0->worldPosition, arg0->rotation, arg0->scale, D_82190D90);

    gSPSetGeometryMode(gDisplayListHead++, G_CULL_BACK);
}

void func_82141128(Particle* arg0, CameraNode* arg1) {
    ParticleGfx_SetPrimEnvColorCombine(arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->env_r, arg0->env_g, arg0->env_b, arg0->prim_a);
    ParticleGfx_DrawModelQuad(arg1, arg0->worldPosition, arg0->scale, D_82190E50);
}

extern Vtx D_82190FC0[];

/**
 * Draw the particle using its world position, scale, color/angle parameters, and the selected vertex template.
 * Seen in play (2026-11-13) in the 165-move sweep (Psybeam): it emitted G_SETPRIMCOLOR with the
 * particle alpha (FFFFFFC8), the texture-alpha combiner FC4097FF FFFFFE38 and a G_MTX for the
 * rotated camera-facing quad.
 */
void ParticleGfx_DrawBillboardTextureAlphaRotatedQuad(Particle* arg0, CameraNode* arg1) {
    ParticleGfx_SetTextureAlphaCombine(arg0->prim_a);
    ParticleGfx_DrawModelQuadRotated(arg1, arg0->worldPosition, arg0->scale, D_82190FC0, arg0->rotation.z);
}

extern Vtx D_82190E90[];

/**
 * Draw the particle using its world position, scale, color/angle parameters, and the selected vertex template.
 * @unverified Name was previously used only by callers of this address; the definition was still func_. Comment from Stadium 1.
 */
void ParticleGfx_DrawBillboardDefaultQuad(Particle* arg0, CameraNode* arg1) {
    ParticleGfx_DrawModelQuad(arg1, arg0->worldPosition, arg0->scale, D_82190E90);
}

void func_8216936C(u8 prim_r, u8 prim_g, u8 prim_b, u8 env_r, u8 env_g, u8 env_b, u8 prim_a);
void func_8214127C(Particle* arg0, CameraNode* arg1) {
    func_8216936C(arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->env_r, arg0->env_g, arg0->env_b, arg0->prim_a);
    ParticleGfx_DrawModelQuad(arg1, arg0->worldPosition, arg0->scale, D_82190E50);
}

/**
 * Draw the particle using its world position, scale, color/angle parameters, and the selected vertex template.
 * Seen in play (2026-11-13) in the 165-move sweep (Pay Day, Ice Punch, Ice Beam, Blizzard, Psybeam,
 * Aurora Beam): it emitted the particle's prim and env colors (e.g. env 0064FF) with the prim/env
 * combiner, then the rotated camera-facing quad.
 */
void ParticleGfx_DrawBillboardPrimEnvRotatedQuad(Particle* arg0, CameraNode* arg1) {
    ParticleGfx_SetPrimEnvColorCombine(arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->env_r, arg0->env_g, arg0->env_b, arg0->prim_a);
    ParticleGfx_DrawModelQuadRotated(arg1, arg0->worldPosition, arg0->scale, D_82190E50, arg0->rotation.z);
}

/**
 * Particle callback of the Fire Spin animation. Player sweep (all 165 moves used in battle): only
 * Fire Spin reached this function.
 */
void BattleAnim_FireSpinParticleDraw(Particle* arg0, CameraNode* arg1) {
    ParticleGfx_SetPrimEnvColorCombine(arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->env_r, arg0->env_g, arg0->env_b, arg0->prim_a);
    ParticleGfx_DrawModelQuad(arg1, arg0->worldPosition, arg0->scale, D_82191000);
}

void func_82141428(Particle* arg0, CameraNode* arg1) {
    ParticleGfx_SetPrimEnvColorCombine(arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->env_r, arg0->env_g, arg0->env_b, arg0->prim_a);
    ParticleGfx_DrawModelQuad(arg1, arg0->worldPosition, arg0->scale, D_82191080);
}

void func_821414B4(Particle* arg0, CameraNode* arg1) {
    ParticleGfx_SetPrimEnvColorCombine(arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->env_r, arg0->env_g, arg0->env_b, arg0->prim_a);
    ParticleGfx_DrawModelQuad(arg1, arg0->worldPosition, arg0->scale, D_82191040);
}

void func_82141540(Particle* arg0, CameraNode* arg1) {
    ParticleGfx_SetPrimEnvColorCombine(arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->env_r, arg0->env_g, arg0->env_b, arg0->prim_a);
    ParticleGfx_DrawModelQuad(arg1, arg0->worldPosition, arg0->scale, D_82191440);
}

/**
 * Particle callback of the Thunder Wave animation. Player sweep (all 165 moves used in battle):
 * only Thunder Wave reached this function.
 */
s32 BattleAnim_ThunderWaveParticleDraw(Particle* arg0, UNUSED CameraNode* arg1) {
    gSPClearGeometryMode(gDisplayListHead++, G_CULL_BACK);

    ParticleGfx_SetPrimEnvColorCombine(arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->env_r, arg0->env_g, arg0->env_b, arg0->prim_a);
    ParticleGfx_DrawTransformedQuad(arg0->worldPosition, arg0->rotation, arg0->scale, D_82191440);

    gSPSetGeometryMode(gDisplayListHead++, G_CULL_BACK);
}

/**
 * Draw the particle using its world position, scale, color/angle parameters, and the selected vertex template.
 * Seen in play (2026-11-13) in the 165-move sweep (Razor Wind, Whirlwind, Slam, Water Gun and
 * others): it emitted the particle's prim and env colors (e.g. prim 00FFFFFF, env 0032FF) with the
 * prim/env combiner, then the transformed quad. Was
 * ParticleGfx_DrawBillboardPrimEnvTransformedQuad, but the quad uses the particle's own rotation,
 * not the camera.
 */
void ParticleGfx_DrawPrimEnvTransformedQuad(Particle* arg0, CameraNode* arg1) {
    ParticleGfx_SetPrimEnvColorCombine(arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->env_r, arg0->env_g, arg0->env_b, arg0->prim_a);
    ParticleGfx_DrawTransformedQuad(arg0->worldPosition, arg0->rotation, arg0->scale, D_821917C0);
}
