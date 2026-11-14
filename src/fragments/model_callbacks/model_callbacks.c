/* Stadium Zero fragment001_15B1A0: model display-list callbacks. */
#include "global.h"
#include "model_callbacks.h"
#include "gfx_buffer.h"
#include "geo_render.h"
#include "model_renderer_callbacks.h"
#include "battle_hud.h"
#include "vector_math.h"

extern s16 D_800AFB28;
Gfx* func_80032D90(Gfx* gfx);

typedef struct ModelParticle {
    /* 0x00 */ s16 active;
    /* 0x02 */ char unk02[0x2];
    /* 0x04 */ Vec3f position;
    /* 0x10 */ Vec3f velocity;
    /* 0x1C */ Vec3f scale;
    /* 0x28 */ s16 misc;
    /* 0x2A */ char unk2A[0x2];
} ModelParticle; // size = 0x2C

extern Vec3f D_8100239C;
extern Vec3f D_810023A8;
extern Vec3f D_810023B4;
extern ModelParticle D_810028A0[][10];
extern s32 D_81002C10;
extern s32 D_81002C14;
extern Vec3f D_810023C0;

typedef struct ModelParticleTiming {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04[3];
    /* 0x0A */ s16 unk_0A;
} ModelParticleTiming; // size = 0xC

extern ModelParticleTiming D_810022A0[18];
extern s16 D_81002378[18];
extern CameraNode* D_80060488;
extern Gfx D_810023D0[];
extern s16 D_81002C20;

typedef struct ModelScrollTextures {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s32 unk_04[6];
} ModelScrollTextures; // size = 0x1C

typedef struct ModelScrollTexturesState {
    /* 0x00 */ char unk00[0x14];
    /* 0x14 */ u32* unk_14;
    /* 0x18 */ Gfx* unk_18;
} ModelScrollTexturesState; // size = 0x1C

typedef struct TextureState {
    /* 0x00 */ char unk00[0x14];
    /* 0x14 */ u32* textures;
    /* 0x18 */ Gfx* gfx;
} TextureState; // size = 0x1C

extern s16 D_800AFB26;

#ifdef NON_MATCHING
/* TODO: decompile func_81000020; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment001_15B1A0/func_81000020.s")
#endif
