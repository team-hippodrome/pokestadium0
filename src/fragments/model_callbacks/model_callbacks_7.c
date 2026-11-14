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

void func_81001FD0(Gfx* gfx, ModelScrollTextures* arg1) {
    s16 temp_v0;
    s32 var_a3;
    ModelScrollTextures* p;

    p = arg1;
    if (D_8006049C->textureMode == 0) {
        temp_v0 = 0x4000;
        // FAKE
        if ((arg1 && arg1) && arg1) {}
        var_a3 = D_800AFB26;
        temp_v0 = temp_v0 - (arg1->unk_00 * var_a3);
        // FAKE
        arg1 = NULL;
        var_a3 = D_800AFB26;
        gDPLoadTextureBlock(gfx++, p->unk_04[var_a3 & 0x7], G_IM_FMT_RGBA, G_IM_SIZ_16b, 64, 32, 0,
                            G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_CLAMP, 6, 5, G_TX_NOLOD, G_TX_NOLOD);
        gDPSetTileSize(gfx++, 0, temp_v0, 0, ((temp_v0 + 63) << 2), 124);
    }
    gSPEndDisplayList(gfx++);
}

void func_81002108(s32 arg0, ModelScrollTexturesState* arg1) {
    s32 temp_v0;
    s32 sp18;

    if (arg0 == 2) {
        sp18 = arg1->unk_14;
        temp_v0 = Gfx_AllocDisplayList(0x50);
        arg1->unk_18 = temp_v0;
        func_81001FD0(temp_v0, sp18);
    }
}

Gfx* func_81002150(Gfx* gfx, u32* textures, s32 index) {
    gDPLoadTextureBlock(gfx++, textures[index + 1], G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD, G_TX_NOLOD);
    gSPEndDisplayList(gfx++);
    return gfx;
}

void func_81002208(s32 arg0, TextureState* state) {
    s32 index;
    u32* textures;

    if (arg0 == 2) {
        textures = state->textures;
        state->gfx = (Gfx*)Gfx_AllocDisplayList(0x50);
        if (D_8006049C->objectType == 0x58) {
            index = (s32)D_8006049C->transformAnim.frameFixed >> 0x10;
            if (index >= 0x42) {
                index = index - 0x42;
            } else {
                index = 0;
            }
        } else {
            index = D_80060484 & 7;
        }
        func_81002150(state->gfx, textures, index);
    }
}
