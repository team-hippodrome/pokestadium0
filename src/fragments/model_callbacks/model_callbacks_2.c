/* Stadium Zero fragment 001 (model callbacks): Animated texture callbacks (Charizard and Moltres flames). */
#include "global.h"
#include "model_callbacks.h"
#include "gfx_buffer.h"
#include "geo_render.h"
#include "model_renderer_callbacks.h"
#include "battle_hud.h"
#include "vector_math.h"

extern s16 D_800AFB28;
Gfx* func_80032D90(Gfx* gfx);

/**
 * Builds a display list that loads I16 texture `index` between the two segments.
 * @unverified No model data uses this callback (play and a scan of the model fragments).
 */
Gfx* ModelCallback_BuildIndexedTextureList(Gfx* gfx, DisplayListAddresses* addresses, s32 index) {
    gSPDisplayList(gfx++, addresses->segments[0]);
    gDPSetTextureImage(gfx++, G_IM_FMT_I, G_IM_SIZ_16b, 1, addresses->textures[index]);
    gDPSetTile(gfx++, G_IM_FMT_I, G_IM_SIZ_16b, 0, 0x0000, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK,
               G_TX_NOLOD, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOLOD);
    gDPLoadSync(gfx++);
    gDPLoadBlock(gfx++, 7, 0, 0, 0x3FF, 0x200);
    gDPPipeSync(gfx++);
    gDPSetTile(gfx++, G_IM_FMT_I, G_IM_SIZ_8b, 4, 0, 0, 0, G_TX_CLAMP, 0, 0, G_TX_CLAMP, 0, 0);
    gDPSetTileSize(gfx++, 0, 0, 0, 0x7C, 0xFC);
    gSPDisplayList(gfx++, addresses->segments[1]);
    gSPEndDisplayList(gfx++);
    return gfx;
}

/**
 * Phase 2: builds ModelCallback_BuildIndexedTextureList with a texture that changes every frame (frame counter % 8).
 * @unverified No model data uses this callback.
 */
void ModelCallback_IndexedTexture(s32 phase, DisplayListState* state) {
    Gfx* gfx;
    DisplayListAddresses* addresses;

    if (phase == 2) {
        addresses = state->addresses;
        gfx = Gfx_AllocDisplayList(80);
        state->gfx = gfx;
        ModelCallback_BuildIndexedTextureList(gfx, addresses, D_80060484 & 7);
    }
}

/**
 * Builds a display list that loads the IA8 32x64 flame texture `index` and draws the
 * slot vertices. Charizard's tail flame and Moltres's crest (both hit in Free Battle).
 */
Gfx* ModelCallback_BuildFlameTextureList(Gfx* gfx, DisplayListAddresses* addresses, s32 index) {
    gDPLoadTextureBlock(gfx++, addresses->textures[index], G_IM_FMT_IA, G_IM_SIZ_8b, 32, 64, 0,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                        G_TX_NOLOD);
    ModelRenderer_UpdateSlotVertices();
    {
        Gfx* gfx2 = func_80032D90(gfx);
        gSPEndDisplayList(gfx2++);
        return gfx2;
    }
}

/**
 * Phase 2: builds the flame texture list. The frame advances every frame, offset by
 * D_800AFB28 so two flames differ. Used by Charmander, Charmeleon, Charizard, Magmar and
 * Moltres model data; hit for Charizard and Moltres in Free Battle.
 */
void ModelCallback_FlameTexture(s32 phase, DisplayListState* state) {
    Gfx* gfx;
    DisplayListAddresses* addresses;

    if (phase == 2) {
        addresses = state->addresses;
        gfx = Gfx_AllocDisplayList(320);
        state->gfx = gfx;
        ModelCallback_BuildFlameTextureList(gfx, addresses, (D_80060484 + D_800AFB28 * 3) % 8);
    }
}
