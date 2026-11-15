/* Stadium Zero fragment012_17ED00. */
/* C ported from the Stadium 1 decomp: src/fragments/battle_engine/battle_engine_343BA0.c, src/fragments/particle_math/particle_math_26E6D0.c. */

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

#include "fragments/particle_math/particle_math.h"
extern u8 gParticlePalette[][3];
extern u8 gParticlePaletteSetA[];
extern u8 gParticlePaletteSetB[];
extern u8 gParticleRandomPaletteIndices[];
extern u8 gParticlePalettePairs[][2];

#include "m2c_macros.h"

void func_82140D50(void);
void ParticleGfx_LoadTextureCallbackI4FrameMod10_32x64(UNUSED Particle* arg0, u8* texture);
void ParticleGfx_LoadTextureCallbackI4_64x64(UNUSED Particle* arg0, u8* texture);
void ParticleGfx_LoadTextureCallbackI4FrameMod8_64x64(UNUSED Particle* arg0, u8* texture);

/**
 * Empty.
 */
void func_82140D50(void) {
}

M2C_UNK func_8216C008(s32, M2C_UNK, M2C_UNK);       /* extern */

void func_82140D58(s8 *arg0, s32 arg1) {
    func_8216C008((M2C_FIELD(arg0, s8 *, 0xC3) * 0x120) + arg1, 0x18, 0x18);
}

/**
 * Load a texture frame selected by the shared particle clock using ParticleGfx_LoadTextureI4Alias.
 * Seen in play (2026-11-13) in the 165-move sweep (Fire Spin): from base 0x80342970 it loaded
 * 0x80344170, frame 6 of the 0x400-byte 32x64 I4 frames, with G_LOADBLOCK 071FF400 (2048 texels).
 */
void ParticleGfx_LoadTextureCallbackI4FrameMod10_32x64(UNUSED Particle* arg0, u8* texture) {
    ParticleGfx_LoadTextureI4Alias(&texture[(gParticleFrameCounter % 10) * (32 * 64 / 2)], 32, 64);
}

M2C_UNK func_8216BFE8(s32, M2C_UNK, M2C_UNK);       /* extern */

void func_82140DD8(s8 *arg0, s32 arg1) {
    func_8216BFE8((M2C_FIELD(arg0, s8 *, 0xC3) << 0xA) + arg1, 0x20, 0x40);
}

/**
 * Load the supplied texture using ParticleGfx_LoadTextureI4Alias.
 * Seen in play (2026-11-13) in the 165-move sweep (Thunder Wave): it emitted an I texture load of
 * 0x8033B120 with G_LOADBLOCK 073FF200 (4096 texels, 64x64).
 */
void ParticleGfx_LoadTextureCallbackI4_64x64(UNUSED Particle* arg0, u8* texture) {
    ParticleGfx_LoadTextureI4Alias(texture, 64, 64);
}

/**
 * Load a texture frame selected by the shared particle clock using ParticleGfx_LoadTextureI4Alias.
 * Seen in play (2026-11-13) in the 165-move sweep (Thunderpunch, Thunderbolt, Thunder): from base
 * 0x8033B950 it loaded the base and 0x8033F150, frame 7 of the 0x800-byte 64x64 I4 frames.
 */
void ParticleGfx_LoadTextureCallbackI4FrameMod8_64x64(UNUSED Particle* arg0, u8* texture) {
    ParticleGfx_LoadTextureI4Alias(&texture[gParticleFrameMod8 * (64 * 64 / 2)], 64, 64);
}
