/* Declarations for the model_callbacks fragment (src/fragments/model_callbacks/). */
#ifndef FRAGMENT_MODEL_CALLBACKS_H
#define FRAGMENT_MODEL_CALLBACKS_H

#include "global.h"
#include "m2c_macros.h"

/*
 * Fragment 001 holds the display-list callbacks of the Pokémon model data
 * (fragments 106-258, image index = species + 105). Model data calls them
 * through the table of `j` slots at the fragment entry (func_81000020). Each
 * callback gets a phase and its node state; in phase 2 it allocates a display
 * list, builds it, and stores it in the state.
 */

/* Display-list segments and texture addresses that a model node hands its callback. */
typedef struct DisplayListAddresses {
    /* 0x00 */ u32 segments[2];
    /* 0x08 */ u32 textures[1];
} DisplayListAddresses; // size = 0xC

typedef struct DisplayListState {
    /* 0x00 */ char unk00[0x14];
    /* 0x14 */ DisplayListAddresses* addresses;
    /* 0x18 */ Gfx* gfx;
} DisplayListState; // size = 0x1C

/* Texture strip that scrolls along S (Moltres's wing flames). */
typedef struct ModelScrollStrip {
    /* 0x00 */ s16 scrollSpeed;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s32 textures[6];
} ModelScrollStrip; // size = 0x1C

typedef struct ModelScrollStripState {
    /* 0x00 */ char unk00[0x14];
    /* 0x14 */ ModelScrollStrip* strip;
    /* 0x18 */ Gfx* gfx;
} ModelScrollStripState; // size = 0x1C

typedef struct TextureState {
    /* 0x00 */ char unk00[0x14];
    /* 0x14 */ u32* textures;
    /* 0x18 */ Gfx* gfx;
} TextureState; // size = 0x1C

/* One billboard particle of a species effect (smoke, embers, snow, bubbles). */
typedef struct ModelParticle {
    /* 0x00 */ s16 active;
    /* 0x02 */ char unk02[0x2];
    /* 0x04 */ Vec3f position;
    /* 0x10 */ Vec3f velocity;
    /* 0x1C */ Vec3f scale;
    /* 0x28 */ s16 age; // frames since spawn; also picks the texture frame (age / 2)
    /* 0x2A */ char unk2A[0x2];
} ModelParticle; // size = 0x2C

#define MODEL_PARTICLE_COUNT 10

/* Animation frames on which Koffing and Weezing release smoke, per animation. @unverified */
typedef struct ModelSmokeSpawnFrames {
    /* 0x00 */ s16 defaultFrame;
    /* 0x02 */ s16 animation4Frame;
    /* 0x04 */ s16 animation3Frames[3];
    /* 0x0A */ s16 animation2Frame;
} ModelSmokeSpawnFrames; // size = 0xC

extern u8 D_81000000[];

Gfx* ModelCallback_BuildIndexedTextureList(Gfx* gfx, DisplayListAddresses* addresses, s32 index);
void ModelCallback_IndexedTexture(s32 phase, DisplayListState* state);
Gfx* ModelCallback_BuildFlameTextureList(Gfx* gfx, DisplayListAddresses* addresses, s32 index);
void ModelCallback_FlameTexture(s32 phase, DisplayListState* state);
void ModelCallback_BuildTwoSegmentList(Gfx* gfx, DisplayListAddresses* addresses);
void ModelCallback_TwoSegments(s32 phase, DisplayListState* state);
void ModelCallback_BuildDefaultModeList(Gfx* gfx, s32* address);
void ModelCallback_DefaultModeSegment(s32 phase, DisplayListState* state);
void ModelParticle_ResetSlot(s32 effect_slot, s32 index);
void ModelParticle_ResetEffectSlot(s32 effect_slot);
void ModelParticle_ResetFrameCounters(void);
void ModelParticle_Spawn(ModelParticle* particles);
void ModelParticle_UpdateSpawn(ModelParticle* particles);
Gfx* ModelParticle_Draw(Gfx* gfx, ModelParticle* particle, DisplayListAddresses* addresses, s16 effect_slot);
Gfx* ModelParticle_DrawAll(Gfx* gfx, ModelParticle* particles, DisplayListAddresses* addresses, s16 effect_slot);
void ModelCallback_Particles(s32 phase, DisplayListState* state);
void ModelCallback_BuildBaseAndDefaultModeList(Gfx* gfx, DisplayListAddresses* addresses);
void ModelCallback_BaseAndDefaultModeSegments(s32 phase, DisplayListState* state);
void func_81001CE0(Gfx* gfx, DisplayListAddresses* addresses);
void ModelCallback_DualScrollTexture(s32 phase, DisplayListState* state);
void ModelCallback_BuildScrollStripList(Gfx* gfx, ModelScrollStrip* strip);
void ModelCallback_ScrollStrip(s32 phase, ModelScrollStripState* state);
Gfx* ModelCallback_BuildSelectedTextureList(Gfx* gfx, u32* textures, s32 index);
void ModelCallback_SelectedTexture(s32 phase, TextureState* state);

#endif // FRAGMENT_MODEL_CALLBACKS_H
