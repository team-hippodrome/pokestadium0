/* Stadium Zero fragment 001 (model callbacks): Scrolling texture strip (Moltres) and selected-texture (Grimer) callbacks. */
#include "global.h"
#include "model_callbacks.h"
#include "gfx_buffer.h"
#include "geo_render.h"
#include "model_renderer_callbacks.h"
#include "battle_hud.h"
#include "vector_math.h"

extern s16 D_800AFB26;

/**
 * Builds a display list that loads RGBA16 64x32 texture (frame & 7) of the strip, scrolled
 * along S by scrollSpeed per frame, only while textureMode is 0.
 */
void ModelCallback_BuildScrollStripList(Gfx* gfx, ModelScrollStrip* strip) {
    s16 scroll_s;
    s32 var_a3;
    ModelScrollStrip* p;

    p = strip;
    if (D_8006049C->textureMode == 0) {
        scroll_s = 0x4000;
        // FAKE
        if ((strip && strip) && strip) {}
        var_a3 = D_800AFB26;
        scroll_s = scroll_s - (strip->scrollSpeed * var_a3);
        // FAKE
        strip = NULL;
        var_a3 = D_800AFB26;
        gDPLoadTextureBlock(gfx++, p->textures[var_a3 & 0x7], G_IM_FMT_RGBA, G_IM_SIZ_16b, 64, 32, 0,
                            G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_CLAMP, 6, 5, G_TX_NOLOD, G_TX_NOLOD);
        gDPSetTileSize(gfx++, 0, scroll_s, 0, ((scroll_s + 63) << 2), 124);
    }
    gSPEndDisplayList(gfx++);
}

/**
 * Phase 2: builds the scrolling strip. Moltres's wing flames; also used by Ponyta and Rapidash
 * model data. Hit for Moltres in Free Battle.
 */
void ModelCallback_ScrollStrip(s32 phase, ModelScrollStripState* state) {
    Gfx* gfx;
    ModelScrollStrip* strip;

    if (phase == 2) {
        strip = state->strip;
        gfx = Gfx_AllocDisplayList(0x50);
        state->gfx = gfx;
        ModelCallback_BuildScrollStripList(gfx, strip);
    }
}

/**
 * Builds a display list that loads RGBA16 32x32 texture `index` of the list.
 * @unverified Only Grimer uses it, and Grimer cannot battle in Stadium Zero.
 */
Gfx* ModelCallback_BuildSelectedTextureList(Gfx* gfx, u32* textures, s32 index) {
    gDPLoadTextureBlock(gfx++, textures[index + 1], G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD, G_TX_NOLOD);
    gSPEndDisplayList(gfx++);
    return gfx;
}

/**
 * Phase 2: picks the texture and builds ModelCallback_BuildSelectedTextureList. Grimer follows its animation frame
 * (frame - 0x42 from frame 0x42 on); other models cycle every frame.
 * @unverified Only Grimer uses it, and Grimer cannot battle in Stadium Zero.
 */
void ModelCallback_SelectedTexture(s32 phase, TextureState* state) {
    s32 index;
    u32* textures;

    if (phase == 2) {
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
        ModelCallback_BuildSelectedTextureList(state->gfx, textures, index);
    }
}
