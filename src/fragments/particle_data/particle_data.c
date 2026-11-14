/* Stadium Zero fragment031_3553C0. */

#include "global.h"
#include "particle_data.h"
#include "gfx_buffer.h"
#include "m2c_macros.h"

extern Gfx sFlameBackdropPreTextureDL[];
extern Gfx sFlameBackdropPostTextureDL[];
extern void* sFlameBackdropTextures[];
extern u16 D_80060484;

Gfx* FireFx_BuildFlameBackdropDisplayList(Gfx* gfx, s32 frame);

/**
 * Writes the VS scene's fire backdrop into `gfx`: two quads around a load of frame `frame`
 * (0-7) of the 32x32 RGBA16 flame strip in `sFlameBackdropTextures`. Returns the end of the
 * written list.
 * Seen in play (2026-11-14): recoloring `sFlameBackdropTextures` turned the full-screen fire
 * behind the Free Battle VS panels green, and in the tournament VS scene it turned the fire
 * on the stadium's big screen and behind the round title green.
 */
Gfx* FireFx_BuildFlameBackdropDisplayList(Gfx* gfx, s32 frame) {
    gSPDisplayList(gfx++, sFlameBackdropPreTextureDL);
    gDPLoadTextureBlock(gfx++, sFlameBackdropTextures[frame], G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0, G_TX_CLAMP, G_TX_CLAMP,
                        G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    gSPDisplayList(gfx++, sFlameBackdropPostTextureDL);
    gSPEndDisplayList(gfx++);
    return gfx;
}

/**
 * Geo callback of the VS scene's fire backdrop node (fragment013, 0x82202DA8): at render
 * time (`context` 2) it rebuilds the node's display list with the flame frame picked by the
 * global frame counter, so the fire cycles through its eight frames.
 * Seen in play (2026-11-14): breakpoint hit every frame of the Free Battle and tournament
 * VS scenes.
 */
void FireFx_FlameBackdropGeoCallback(s32 context, GeoDisplayListNode* node) {
    if (context == 2) {
        node->displayList = Gfx_AllocDisplayList(0x50);
        FireFx_BuildFlameBackdropDisplayList(node->displayList, D_80060484 & 7);
    }
}
