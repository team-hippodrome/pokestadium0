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

void ParticleGfx_LoadTextureCallbackI4FrameDiv2Mod8_64x64(UNUSED Particle* arg0, u8* texture) {
    ParticleGfx_LoadTextureI4Alias(&texture[(gParticleFrameDiv2 & 7) * (64 * 64 / 2)], 64, 64);
}

M2C_UNK func_8216BFE8(s32, M2C_UNK, M2C_UNK);       /* extern */

void func_82140EAC(s8 *arg0, s32 arg1) {
    func_8216BFE8((M2C_FIELD(arg0, s8 *, 0xC3) << 0xB) + arg1, 0x40, 0x40);
}

void ParticleGfx_LoadTextureCallbackI4WrapST_64x64(UNUSED Particle* arg0, u8* texture) {
    ParticleGfx_LoadTextureI4WrapST(texture, 64, 64);
}

void ParticleGfx_LoadTextureCallbackIa8WrapST_64x64(UNUSED Particle* arg0, u8* texture) {
    ParticleGfx_LoadTextureIa8WrapST(texture, 64, 64);
}

extern Vtx D_82190E50[];

void ParticleGfx_DrawBillboardPrim(Particle* arg0, CameraNode* arg1) {
    ParticleGfx_SetPrimColorTextureCombine(arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->prim_a);
    ParticleGfx_DrawModelQuad(arg1, arg0->worldPosition, arg0->scale, D_82190E50);
}

void ParticleGfx_DrawBillboardPrimEnv(Particle* arg0, CameraNode* arg1) {
    ParticleGfx_SetPrimEnvColorCombine(arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->env_r, arg0->env_g, arg0->env_b, arg0->prim_a);
    ParticleGfx_DrawModelQuad(arg1, arg0->worldPosition, arg0->scale, D_82190D90);
}

s32 ParticleGfx_DrawBillboardDoubleSided(Particle* arg0, UNUSED CameraNode* arg1) {
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

void ParticleGfx_DrawBillboardPrimEnvRotatedQuad(Particle* arg0, CameraNode* arg1) {
    ParticleGfx_SetPrimEnvColorCombine(arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->env_r, arg0->env_g, arg0->env_b, arg0->prim_a);
    ParticleGfx_DrawModelQuadRotated(arg1, arg0->worldPosition, arg0->scale, D_82190E50, arg0->rotation.z);
}

void func_8214139C(Particle* arg0, CameraNode* arg1) {
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

s32 func_821415CC(Particle* arg0, UNUSED CameraNode* arg1) {
    gSPClearGeometryMode(gDisplayListHead++, G_CULL_BACK);

    ParticleGfx_SetPrimEnvColorCombine(arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->env_r, arg0->env_g, arg0->env_b, arg0->prim_a);
    ParticleGfx_DrawTransformedQuad(arg0->worldPosition, arg0->rotation, arg0->scale, D_82191440);

    gSPSetGeometryMode(gDisplayListHead++, G_CULL_BACK);
}

void ParticleGfx_DrawBillboardPrimEnvTransformedQuad(Particle* arg0, CameraNode* arg1) {
    ParticleGfx_SetPrimEnvColorCombine(arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->env_r, arg0->env_g, arg0->env_b, arg0->prim_a);
    ParticleGfx_DrawTransformedQuad(arg0->worldPosition, arg0->rotation, arg0->scale, D_821917C0);
}
