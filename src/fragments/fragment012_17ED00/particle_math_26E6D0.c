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
 * Seen in play (2026-11-13) in the 165-move sweep (Pay Day, Ice Punch, Horn Attack, Pin Missile,
 * Ice Beam and others): it emitted an IA texture load (FD700000) of the passed texture with the
 * 32x32 tile (G_LOADBLOCK 071FF200).
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
 * Seen in play (2026-11-13) in the 165-move sweep (Solarbeam): it emitted an I texture load
 * (FD900000) of the passed texture 0x8033CB00 with the 32x32 block (070FF400).
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
 * Seen in play (2026-11-13) in the 165-move sweep (Mega Punch, Pin Missile, Water Gun, Thunderbolt
 * and others): from base 0x8033DA50 it loaded 0x8033DE50, frame 2 of the 0x200-byte 32x32 I4
 * frames, picked by gParticleFrameMod4.
 */
void ParticleGfx_LoadTextureCallbackI4FrameMod4_32x32(UNUSED Particle* arg0, u8* texture) {
    ParticleGfx_LoadTextureI4Alias(&texture[gParticleFrameMod4 * (32 * 32 / 2)], 32, 32);
}

/**
 * Load a texture frame selected by the shared particle clock using ParticleGfx_LoadTextureI4Alias.
 * Seen in play (2026-11-13) in the 165-move sweep (Water Gun, Hydro Pump, Surf, Waterfall): from
 * base 0x8033F250 it loaded 0x8033F650, frame 2 of the 32x32 I4 frames, picked by
 * gParticleFrameDiv2 & 3.
 */
void ParticleGfx_LoadTextureCallbackI4FrameDiv2Mod4_32x32(UNUSED Particle* arg0, u8* texture) {
    ParticleGfx_LoadTextureI4Alias(&texture[(gParticleFrameDiv2 & 3) * (32 * 32 / 2)], 32, 32);
}

/**
 * Load a texture frame selected by the shared particle clock using ParticleGfx_LoadTextureI4Alias.
 * Seen in play (2026-11-13) in a Free Battle switch (1P switched to its second Pokémon) it ran
 * while the new Pokémon was sent out.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void ParticleGfx_LoadTextureCallbackI4FrameDiv4Mod4_32x32(UNUSED Particle* arg0, u8* texture) {
    ParticleGfx_LoadTextureI4Alias(&texture[(gParticleFrameDiv4 & 3) * (32 * 32 / 2)], 32, 32);
}

/**
 * Load a texture frame selected by the shared particle clock using ParticleGfx_LoadTextureI4Alias.
 * Seen in play (2026-11-13) in the 165-move sweep (Hydro Pump, Ice Beam, Psybeam, Bubblebeam, Hyper
 * Beam): from base 0x80342AE0 it loaded 0x80342CE0 and 0x803432E0 (frames 1 and 4 of 8), picked by
 * gParticleFrameDiv2 & 7.
 */
void ParticleGfx_LoadTextureCallbackI4FrameDiv2Mod8_32x32(UNUSED Particle* arg0, u8* texture) {
    ParticleGfx_LoadTextureI4Alias(&texture[(gParticleFrameDiv2 & 7) * (32 * 32 / 2)], 32, 32);
}
