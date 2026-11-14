/* Stadium Zero fragment031_3553C0. */
/* C ported from the Stadium 1 decomp: src/fragments/particle_data_library/particle_data_library_257DE0.c. */

#include "particle_data.h"
#include "geo_render.h"
#include "gfx_buffer.h"

#include "m2c_macros.h"

extern Gfx sFireOverlaySetupDL[];
extern void* sFireOverlayTextures[];
extern u16 D_80060484;

void FireFx_ScrollMaterialGeoCallback(s32 context, GeoDisplayListNode* node);
Gfx* FireFx_BuildFlickerOverlayDisplayList(Gfx* gfx, s32 frame, Gfx* mesh);
Gfx* FireFx_BuildScrollOverlayDisplayList(Gfx* gfx, Gfx* mesh);
Gfx* FireFx_BuildScrollMaterialDisplayList(Gfx* gfx);

/**
 * Writes a display list into `gfx` that sets up the translucent fire material, loads frame
 * `frame` (0-7) of the fire overlay texture in `sFireOverlayTextures` and draws `mesh` with it.
 * Returns the end of the written list.
 * Seen in play (2026-11-14): with frames 1-7 of `sFireOverlayTextures` recolored green,
 * the two trainer panels of the Free Battle VS scene turned green.
 */
Gfx* FireFx_BuildFlickerOverlayDisplayList(Gfx* gfx, s32 frame, Gfx* mesh) {
    gSPDisplayList(gfx++, sFireOverlaySetupDL);
    gDPLoadTextureBlock(gfx++, sFireOverlayTextures[frame], G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0, G_TX_CLAMP,
                        G_TX_CLAMP, 5, 5, 1, 1);
    gSPDisplayList(gfx++, mesh);
    gSPEndDisplayList(gfx++);
    return gfx;
}

/**
 * Geo callback for a flickering fire overlay: at render time (`context` 2) it draws the mesh
 * display list in the node's callback argument with the overlay frame picked by the global
 * frame counter. Used by the VS scene's trainer panels (fragment 032) and by fragment 033.
 * Seen in play (2026-11-14): breakpoint hit in the Free Battle and tournament VS scenes.
 */
void FireFx_FlickerOverlayGeoCallback(s32 context, GeoDisplayListNode* node) {
    if (context == 2) {
        node->displayList = Gfx_AllocDisplayList(0x50);
        FireFx_BuildFlickerOverlayDisplayList(node->displayList, D_80060484 & 7, (Gfx*)node->node.callbackArg);
    }
}

/**
 * Writes a display list into `gfx` that sets up the translucent fire material with the first
 * overlay frame, scrolls it one step along S per call (a full 32-texel turn every 128 calls)
 * and draws `mesh` with it. Returns the end of the written list.
 * Seen in play (2026-11-14): with frame 0 of `sFireOverlayTextures` recolored blue and
 * frames 1-7 green, the "VS" letters of the Free Battle VS scene stayed solid blue.
 */
Gfx* FireFx_BuildScrollOverlayDisplayList(Gfx* gfx, Gfx* mesh) {
    static s32 sScrollOverlayOffsetS;

    sScrollOverlayOffsetS--;
    if (sScrollOverlayOffsetS < 0) {
        sScrollOverlayOffsetS = 0x80;
    }
    gSPDisplayList(gfx++, sFireOverlaySetupDL);
    gDPLoadTextureBlock(gfx++, sFireOverlayTextures[0], G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0, G_TX_WRAP, G_TX_CLAMP,
                        5, 5, 1, 1);
    gDPSetTileSize(gfx++, G_TX_RENDERTILE, sScrollOverlayOffsetS, 0, (sScrollOverlayOffsetS + 0x1F) << 2, 0x7C);
    gSPDisplayList(gfx++, mesh);
    gSPEndDisplayList(gfx++);
    return gfx;
}

/**
 * Geo callback for a scrolling fire overlay: at render time (`context` 2) it draws the mesh
 * display list in the node's callback argument with the scrolling fire texture. Used by the
 * "VS" letters (fragment 032).
 * Seen in play (2026-11-14): breakpoint hit in the Free Battle and tournament VS scenes.
 */
void FireFx_ScrollOverlayGeoCallback(s32 context, GeoDisplayListNode* node) {
    if (context == 2) {
        node->displayList = Gfx_AllocDisplayList(0x58);
        FireFx_BuildScrollOverlayDisplayList(node->displayList, (Gfx*)node->node.callbackArg);
    }
}

/**
 * Same as FireFx_BuildScrollOverlayDisplayList without a mesh: writes only the fire material
 * and the scrolling texture (its own counter), leaving them set for the display lists drawn
 * after it. Returns the end of the written list.
 * Seen in play (2026-11-14): only in the tournament VS scene; with frame 0 of
 * `sFireOverlayTextures` recolored blue the round title (バトル-1, "Battle 1") turned blue.
 */
Gfx* FireFx_BuildScrollMaterialDisplayList(Gfx* gfx) {
    static s32 sScrollMaterialOffsetS;

    sScrollMaterialOffsetS--;
    if (sScrollMaterialOffsetS < 0) {
        sScrollMaterialOffsetS = 0x80;
    }
    gSPDisplayList(gfx++, sFireOverlaySetupDL);
    gDPLoadTextureBlock(gfx++, sFireOverlayTextures[0], G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0, G_TX_WRAP, G_TX_CLAMP,
                        5, 5, 1, 1);
    gDPSetTileSize(gfx++, G_TX_RENDERTILE, sScrollMaterialOffsetS, 0, (sScrollMaterialOffsetS + 0x1F) << 2, 0x7C);
    gSPEndDisplayList(gfx++);
    return gfx;
}

/**
 * Geo callback that sets up the scrolling fire material: at render time (`context` 2) it
 * rebuilds the node's display list with FireFx_BuildScrollMaterialDisplayList. Used by
 * the VS scene's round-title models in fragments 033 to 037.
 * Seen in play (2026-11-14): breakpoint hit in the tournament VS scene (round 1), not in
 * Free Battle.
 */
void FireFx_ScrollMaterialGeoCallback(s32 context, GeoDisplayListNode* node) {
    Gfx* gfx;

    if (context == 2) {
        gfx = (Gfx*)Gfx_AllocDisplayList(0x50);
        node->displayList = gfx;
        FireFx_BuildScrollMaterialDisplayList(gfx);
    }
}
