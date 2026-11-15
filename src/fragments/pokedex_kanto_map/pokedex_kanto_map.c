/**
 * Stadium Zero fragment030_326700: the 3D Kanto map model that the Pokedex habitat screen
 * ("ぶんぷをみる" / "View area") loads (pokedex fragment, func_8A1053E8). Its two geo callbacks
 * scroll the textures of the sea plane and of the rivers every frame.
 */

#include "global.h"
#include "gfx_buffer.h"
#include "m2c_macros.h"
#include "pokedex_kanto_map.h"

extern s32 sKantoMapSeaScrollS;
extern s32 sKantoMapSeaScrollT;
extern s32 sKantoMapRiversScrollS;
extern s32 sKantoMapRiversScrollT;
extern Gfx sKantoMapSeaMaterialDL[];
extern Gfx sKantoMapSeaMeshDL[];
extern Gfx sKantoMapRiversMaterialDL[];
extern Gfx sKantoMapRiversMeshDL[];

Gfx* KantoMap_BuildSeaDisplayList(Gfx* gfx);
Gfx* KantoMap_BuildRiversDisplayList(Gfx* gfx);

/**
 * Writes the sea's display list: material, both texture tiles scrolled diagonally by one texel
 * per frame (tile 1 only along S), then a branch to the sea mesh. Seen in play (2026-11-14):
 * cutting sKantoMapSeaMeshDL short blanked the open sea around Kanto on the habitat screen.
 */
Gfx* KantoMap_BuildSeaDisplayList(Gfx* gfx) {
    if (++sKantoMapSeaScrollS >= 0x80) {
        sKantoMapSeaScrollS = 0;
    }
    if (++sKantoMapSeaScrollT >= 0x80) {
        sKantoMapSeaScrollT = 0;
    }
    gSPDisplayList(gfx++, sKantoMapSeaMaterialDL);
    gDPSetTileSize(gfx++, G_TX_RENDERTILE, sKantoMapSeaScrollS, sKantoMapSeaScrollT, sKantoMapSeaScrollS + 0x7C, sKantoMapSeaScrollT + 0x7C);
    gDPSetTileSize(gfx++, 1, sKantoMapSeaScrollS, 0, sKantoMapSeaScrollS + 0x7C, 0x7C);
    gSPBranchList(gfx++, sKantoMapSeaMeshDL);
    return gfx;
}

/**
 * Geo callback of the sea node. On the render pass (call_context 2, from Geo_ProcessNodeChildren) it builds a
 * fresh scrolling display list for the node. Seen in play: hit every frame with call_context 2.
 */
void KantoMap_SeaGeoCallback(s32 call_context, GeoDisplayListNode* node) {
    if (call_context == 2) {
        node->displayList = Gfx_AllocDisplayList(0x20);
        KantoMap_BuildSeaDisplayList(node->displayList);
    }
}

/**
 * Writes the rivers' display list: material, texture scrolled by -2 texels along S and +1 along
 * T per frame, then a branch to the river mesh. Seen in play (2026-11-14): cutting
 * sKantoMapRiversMeshDL short left the river channels empty on the habitat screen.
 */
Gfx* KantoMap_BuildRiversDisplayList(Gfx* gfx) {
    sKantoMapRiversScrollS -= 2;
    if (sKantoMapRiversScrollS < 0) {
        sKantoMapRiversScrollS = 0xFF;
    }
    if (++sKantoMapRiversScrollT >= 0x80) {
        sKantoMapRiversScrollT = 0;
    }
    gSPDisplayList(gfx++, sKantoMapRiversMaterialDL);
    gDPSetTileSize(gfx++, G_TX_RENDERTILE, sKantoMapRiversScrollS, sKantoMapRiversScrollT, sKantoMapRiversScrollS + 0x7C, sKantoMapRiversScrollT + 0x7C);
    gSPBranchList(gfx++, sKantoMapRiversMeshDL);
    return gfx;
}

/**
 * Geo callback of the river node; same as KantoMap_SeaGeoCallback for the rivers. Seen in play:
 * hit every frame with call_context 2.
 */
void KantoMap_RiversGeoCallback(s32 call_context, GeoDisplayListNode* node) {
    if (call_context == 2) {
        node->displayList = Gfx_AllocDisplayList(24);
        KantoMap_BuildRiversDisplayList(node->displayList);
    }
}
