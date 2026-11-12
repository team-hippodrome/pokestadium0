/* Stadium Zero fragment012_17ED00. */
/* C ported from the Stadium 1 decomp: src/fragments/particle_math/particle_math_26E6D0.c. */

#include "fragments/particle_math/particle_math.h"
extern u8 gParticlePalette[][3];
extern u8 gParticlePaletteSetA[];
extern u8 gParticlePaletteSetB[];
extern u8 gParticleRandomPaletteIndices[];
extern u8 gParticlePalettePairs[][2];

#include "m2c_macros.h"

void ParticleGfx_LoadTextureCallbackIa8_32x32(UNUSED Particle* arg0, u8* texture);
void ParticleGfx_LoadTextureCallbackI4_32x32(UNUSED Particle* arg0, u8* texture);
void ParticleGfx_LoadTextureCallbackI4FrameMod4_32x32(UNUSED Particle* arg0, u8* texture);
void ParticleGfx_LoadTextureCallbackI4FrameDiv2Mod4_32x32(UNUSED Particle* arg0, u8* texture);
void ParticleGfx_LoadTextureCallbackI4FrameDiv4Mod4_32x32(UNUSED Particle* arg0, u8* texture);
void ParticleGfx_LoadTextureCallbackI4FrameDiv2Mod8_32x32(UNUSED Particle* arg0, u8* texture);

M2C_UNK func_8216BBF8(s32, M2C_UNK, M2C_UNK);       /* extern */

void func_82140B70(s8 *arg0, s32 arg1) {
    func_8216BBF8((M2C_FIELD(arg0, s8 *, 0xC3) << 0xA) + arg1, 0x20, 0x20);
}

/**
 * Load the supplied texture using ParticleGfx_LoadTextureIa8.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void ParticleGfx_LoadTextureCallbackIa8_32x32(UNUSED Particle* arg0, u8* texture) {
    ParticleGfx_LoadTextureIa8(texture, 32, 32);
}

M2C_UNK func_8216BBF8(s32, M2C_UNK, M2C_UNK);       /* extern */

void func_82140BD0(s8 *arg0, s32 arg1) {
    func_8216BBF8((M2C_FIELD(arg0, s8 *, 0xC3) << 0xB) + arg1, 0x20, 0x40);
}

/**
 * Load the supplied texture using ParticleGfx_LoadTextureI4Alias.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void ParticleGfx_LoadTextureCallbackI4_32x32(UNUSED Particle* arg0, u8* texture) {
    ParticleGfx_LoadTextureI4Alias(texture, 32, 32);
}

M2C_UNK func_8216BFE8(s32, M2C_UNK, M2C_UNK);       /* extern */

void func_82140C30(s8 *arg0, s32 arg1) {
    func_8216BFE8((M2C_FIELD(arg0, s8 *, 0xC3) << 9) + arg1, 0x20, 0x20);
}

/**
 * Load a texture frame selected by the shared particle clock using ParticleGfx_LoadTextureI4Alias.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void ParticleGfx_LoadTextureCallbackI4FrameMod4_32x32(UNUSED Particle* arg0, u8* texture) {
    ParticleGfx_LoadTextureI4Alias(&texture[gParticleFrameMod4 * (32 * 32 / 2)], 32, 32);
}

/**
 * Load a texture frame selected by the shared particle clock using ParticleGfx_LoadTextureI4Alias.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void ParticleGfx_LoadTextureCallbackI4FrameDiv2Mod4_32x32(UNUSED Particle* arg0, u8* texture) {
    ParticleGfx_LoadTextureI4Alias(&texture[(gParticleFrameDiv2 & 3) * (32 * 32 / 2)], 32, 32);
}

/**
 * Load a texture frame selected by the shared particle clock using ParticleGfx_LoadTextureI4Alias.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void ParticleGfx_LoadTextureCallbackI4FrameDiv4Mod4_32x32(UNUSED Particle* arg0, u8* texture) {
    ParticleGfx_LoadTextureI4Alias(&texture[(gParticleFrameDiv4 & 3) * (32 * 32 / 2)], 32, 32);
}

/**
 * Load a texture frame selected by the shared particle clock using ParticleGfx_LoadTextureI4Alias.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void ParticleGfx_LoadTextureCallbackI4FrameDiv2Mod8_32x32(UNUSED Particle* arg0, u8* texture) {
    ParticleGfx_LoadTextureI4Alias(&texture[(gParticleFrameDiv2 & 7) * (32 * 32 / 2)], 32, 32);
}
