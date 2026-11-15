/* Stadium Zero fragment018_262620: the Pokédex's ぶんぷをみる (habitat) area map. Areas are numbered 1-36
 * (sMapAreas, sAreaPinPositions); "slots" are the same 36 areas in route order (sSlotToArea), the order
 * D-Up / D-Down step through and sAreaNames lists. */
/* C ported from the Stadium 1 decomp: src/fragments/pokedex/pokedex_2190D0.c. */

#include "pokedex.h"
#include "audio_sfx_wrapper.h"
#include "display_object_textures.h"
#include "font.h"
#include "gb_save.h"
#include "geo_layout.h"
#include "geo_render.h"
#include "gfx_buffer.h"
#include "graphics_textures.h"
#include "matrix.h"
#include "memory_main.h"
#include "pokemon_stats.h"
#include "vector_math.h"

// Declared here instead of in a header: the callers of these disagree on their types.
void* MainPool_InitState(struct MainPoolState* block, s32 size);
/* One wild encounter row of a location table (one table per GB game, ended by species < 0).
 * Seen in play (2026-11-14): ポッポ on 2ばんどうろ showed レベル 3〜5 たくさんみかける. */
typedef struct PokedexEncounter {
    /* 0x00 */ s16 species; // dex number
    /* 0x02 */ s16 minLevel;
    /* 0x04 */ s16 maxLevel;
    /* 0x06 */ s16 rate; // Pokedex_GetEncounterRateTier turns it into the みかける wording
} PokedexEncounter; // size = 0x8

/* One map area (pin) of the area map, filled by Pokedex_LoadAreaMap for the shown species. */
typedef struct PokedexMapArea {
    /* 0x00 */ s16 hasSpecies; // 1 = the species lives here and a pin is drawn
    /* 0x02 */ s16 count; // number of encounters and locations below
    /* 0x04 */ PokedexEncounter* encounters[5];
    /* 0x18 */ s16 locations[6]; // index into the location names
} PokedexMapArea; // size = 0x24

/* An area's square on the GB map overlay, in 8-pixel cells. */
typedef struct PokedexGbMapCell {
    /* 0x00 */ s16 x;
    /* 0x02 */ s16 y;
} PokedexGbMapCell; // size = 0x4
extern GeoDisplayListNode sGbMapNode;
extern GeoDisplayListNode sAreaPinsNode;
extern GeoDisplayListNode sGbMapMarkersNode;
extern GraphNode* sAreaMapRoot;
extern s16 sGbMapShown;
extern s16 sSelectedSlot;
extern s16 sPrevSelectedSlot;
extern s16 sAreaMapZoomed;
extern s16 sHabitatUnknown;
extern s16 sGbGameCategory;
extern u16 sAreaMapFrameCounter;
extern s16 sCameraMoving;
extern u8* sSpeciesIcon;
extern f32 sCameraEaseDivisor;
extern s32 sCameraSettledFrames;
extern Mtx* sAreaPinMatrices;
extern PokedexMapArea sMapAreas[36];
extern u8 D_8A12C8F0[];
extern u8 D_8A12C9E8[];
extern u8 D_8A12CCC0[];
extern u8 D_8A12CD48[];
extern u8 D_8A12CDD0[];
extern u8 D_8A12CE58[];
extern u8 D_8A12CEE0[];
extern u8 D_8A12CF68[];
extern u8 D_8A12D070[];
extern u8 D_8A12E788[];
extern u8 D_8A12E850[];
extern Gfx D_8A12E8F0[];
extern Gfx D_8A12E958[];
extern Gfx D_8A12E970[];
extern Gfx D_8A12E9C8[];
extern Gfx D_8A12EA30[];
extern Gfx D_8A12EA48[];
extern Vtx D_8A12EA60[][4];
extern Gfx D_8A12EB60[];
extern Gfx D_8A12EB90[];
extern Gfx D_8A12EBA0[];
extern Gfx D_8A12EC18[];
extern Gfx D_8A12EC40[];
extern Gfx D_8A12EC60[];
extern Gfx D_8A12ECD0[];
extern Gfx D_8A12ECF0[];
extern char sAreaNames[0x24][20];
extern Vec3f sOverviewCameraTarget;
extern Vec3f sOverviewCameraEye;
extern Vec3f sAreaPinPositions[];
extern PokedexGbMapCell sGbMapCells[];
extern s16 sAreaToSlot[];
extern s16 sSlotToArea[];

/**
 * Returns the next slot after `current_slot` (wrapping) whose area has the species, or `current_slot`.
 * Seen in play (2026-11-14): D-Up on ポッポ's map went from 2ばんどうろ to 3ばんどうろ; Pokedex_LoadAreaMap
 * calls it with 0 to pick the first area.
 */
s32 Pokedex_FindNextMapArea(s32 current_slot) {
    s32 i;
    s32 idx;
    s32 a0 = current_slot;

    for (i = 1; i < 36; i++) {
        idx = sSlotToArea[(current_slot + i) % 36] - 1;
        if (sMapAreas[idx].hasSpecies == 1) {
            return sAreaToSlot[idx] - 1;
        }
    }
    return a0;
}

/**
 * Returns the previous slot before `current_slot` (wrapping) whose area has the species, or `current_slot`.
 * Seen in play (2026-11-14): D-Down went from 3ばんどうろ back to 2ばんどうろ.
 */
s32 Pokedex_FindPrevMapArea(s32 current_slot) {
    s32 i;
    s32 idx;
    s32 a0 = current_slot;

    for (i = 35; i > 0; i--) {
        idx = sSlotToArea[(current_slot + i) % 36] - 1;
        if (sMapAreas[idx].hasSpecies == 1) {
            return sAreaToSlot[idx] - 1;
        }
    }
    return a0;
}

/**
 * Builds sGbMapNode's display list: the GB-style Kanto map overlay (D_8A12ECF0) while sGbMapShown.
 * Seen in play (2026-11-14): R on ポッポ's map showed the GB map (Rボタンで GBマップをけす).
 */
void Pokedex_BuildGbMapDisplayList(void) {
    Gfx* temp_v0 = Gfx_AllocDisplayList(sizeof(Gfx) * 5);

    sGbMapNode.displayList = temp_v0;

    if (sGbMapShown == 1) {
        gSPDisplayList(temp_v0++, D_8A12ECF0);
    }
    gSPEndDisplayList(temp_v0++);
}

/**
 * Builds sAreaPinsNode's display list: a signpost pin at each area that has the species, facing the camera,
 * with the species icon (sSpeciesIcon) on it; the selected area's pin is twice the size and orange.
 * Seen in play (2026-11-14): pins over ポッポ's routes, the 2ばんどうろ pin large and orange.
 */
void Pokedex_BuildAreaPinsDisplayList(void) {
    s32 i;
    Mtx sp1A8;
    Mtx sp168;
    Vec3f* vec;
    MtxF sp124;
    Mtx spE0;
    Mtx* var_s1;
    s32 var_t5;
    CameraNode* temp_s2;
    CameraView* ptr;
    Gfx* temp_v0;
    s32 j;

    temp_s2 = sAreaMapRoot->children;
    ptr = &temp_s2->view;

    temp_v0 = Gfx_AllocDisplayList(sizeof(Gfx) * 36 * 25);
    sAreaPinsNode.displayList = temp_v0;
    sAreaPinMatrices = Gfx_AllocDisplayList(sizeof(Mtx) * 36);
    var_s1 = sAreaPinMatrices;

    MtxF_SetLookAt(&ptr->floatMatrix, &ptr->eyePosition, &ptr->targetPosition, 0);
    MtxF_ExtractScale(&sp124, &temp_s2->view.floatMatrix);
    guMtxF2L(sp124.mf, &spE0);

    gSPDisplayList(temp_v0++, D_8A12E8F0);

    for (i = 0; i < 36; i++) {
        vec = &sAreaPinPositions[i];

        if (sMapAreas[i].hasSpecies == 1) {
            if ((i + 1) == sSlotToArea[sSelectedSlot]) {
                gDPSetPrimColor(temp_v0++, 0xFF, 0xFF, 255, 150, 100, 255); // #FF9664FF
                guScale(&sp168, 8.0f, 8.0f, 8.0f);
            } else {
                gDPSetPrimColor(temp_v0++, 0xFF, 0xFF, 255, 255, 255, 255); // #FFFFFFFF
                guScale(&sp168, 4.0f, 4.0f, 4.0f);
            }
            guTranslate(&sp1A8, vec->x, vec->y, vec->z);
            guMtxCatL(&sp168, &sp1A8, &sp1A8);
            guMtxCatL(&spE0, &sp1A8, var_s1);

            gSPMatrix(temp_v0++, var_s1, G_MTX_PUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(temp_v0++, D_8A12E958);
            gSPPopMatrix(temp_v0++, G_MTX_MODELVIEW);
        }
        var_s1++;
    }

    gSPDisplayList(temp_v0++, D_8A12E970);
    var_s1 = sAreaPinMatrices;
    gSPDisplayList(temp_v0++, D_8A12E9C8);

    for (i = 0; i < 36; i++) {
        if (sMapAreas[i].hasSpecies == 1) {
            gSPMatrix(temp_v0++, var_s1, G_MTX_PUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(temp_v0++, D_8A12EA30);
            gSPPopMatrix(temp_v0++, G_MTX_MODELVIEW);
        }
        var_s1++;
    }

    gSPDisplayList(temp_v0++, D_8A12EA48);
    gSPDisplayList(temp_v0++, D_8A12EB60);

    for (j = 0, var_t5 = 0x2580; j < 4; j++, var_t5 -= 0xC80) {
        gDPLoadTextureTile(temp_v0++, var_t5 + sSpeciesIcon, G_IM_FMT_RGBA, G_IM_SIZ_16b, 80, 0, 0, 0, 80, 20, 0,
                           G_TX_MIRROR | G_TX_CLAMP, G_TX_MIRROR | G_TX_CLAMP, 7, 5, G_TX_NOLOD, G_TX_NOLOD);
        gDPPipeSync(temp_v0++);

        var_s1 = sAreaPinMatrices;

        for (i = 0; i < 36; i++) {
            if (sMapAreas[i].hasSpecies == 1) {
                gSPMatrix(temp_v0++, var_s1, G_MTX_PUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                gSPVertex(temp_v0++, &D_8A12EA60[j][0], 4, 0);
                gSPDisplayList(temp_v0++, D_8A12EB90);
                gSPPopMatrix(temp_v0++, G_MTX_MODELVIEW);
            }
            var_s1++;
        }
    }

    gSPDisplayList(temp_v0++, D_8A12EBA0);
    gSPEndDisplayList(temp_v0++);
}

/**
 * Builds sGbMapMarkersNode's display list while sGbMapShown: a blinking square on each area that has the
 * species (sGbMapCells, 8-pixel cells) and the red cursor (D_8A12D070) on the selected one.
 * Seen in play (2026-11-14): squares and the red cursor on 2ばんどうろ on the GB map.
 */
void Pokedex_BuildGbMapMarkersDisplayList(void) {
    s32 i;
    s32 temp_a0;
    s32 temp_v2;
    s32 temp_t1;
    s32 temp_t2;
    Gfx* temp_v0;

    temp_v0 = Gfx_AllocDisplayList(sizeof(Gfx) * 170);
    sGbMapMarkersNode.displayList = temp_v0;

    if (sGbMapShown == 1) {
        gSPDisplayList(temp_v0++, D_8A12EC60);

        if ((sAreaMapFrameCounter % 16) >= 8) {
            for (i = 0; i < 36; i++) {
                if (sMapAreas[i].hasSpecies == 1) {
                    temp_a0 = sGbMapCells[i].x * 8;
                    temp_a0 = temp_a0 + 0x52;
                    temp_v2 = sGbMapCells[i].y * 8;
                    temp_v2 = temp_v2 + 0x32;

                    gDPPipeSync(temp_v0++);
                    gSPTextureRectangle(temp_v0++, temp_a0 << 2, temp_v2 << 2, (temp_a0 + 8) << 2, (temp_v2 + 8) << 2,
                                        G_TX_RENDERTILE, 0, 0, 0x0400, 0x0400);
                }
            }
        }

        temp_t1 = (sGbMapCells[sSlotToArea[sSelectedSlot] - 1].x * 8) + 0x4F;
        temp_t2 = (sGbMapCells[sSlotToArea[sSelectedSlot] - 1].y * 8) + 0x2F;

        gDPSetPrimColor(temp_v0++, 0xFF, 0xFF, 150, 30, 0, 255); // #961E00FF

        gDPPipeSync(temp_v0++);

        gDPLoadTextureBlock(temp_v0++, D_8A12D070, G_IM_FMT_IA, G_IM_SIZ_8b, 16, 16, 0, G_TX_MIRROR | G_TX_CLAMP,
                            G_TX_MIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

        gDPPipeSync(temp_v0++);

        gSPTextureRectangle(temp_v0++, temp_t1 << 2, temp_t2 << 2, (temp_t1 + 0xE) << 2, (temp_t2 + 0xE) << 2,
                            G_TX_RENDERTILE, 0, 0, 0x0400, 0x0400);

        gDPPipeSync(temp_v0++);
        gSPDisplayList(temp_v0++, D_8A12ECD0);
    }

    gSPEndDisplayList(temp_v0++);
}

/**
 * Draws the R button icon (D_8A12E788, 16x12) at (x, y).
 * Seen in play (2026-11-14): beside ボタンでGBマップ at (188, 213), and beside ボタンでGBマップをけす at
 * (86, 183) while the GB map was shown.
 */
Gfx* Pokedex_DrawRButtonIcon(Gfx* gfx, s16 x, s16 y) {
    gSPDisplayList(gfx++, D_8A12EC18);
    gDPSetPrimColor(gfx++, 0xFF, 0xFF, 255, 255, 255, 255); // #FFFFFFFF
    gDPPipeSync(gfx++);
    gDPLoadTextureBlock(gfx++, D_8A12E788, G_IM_FMT_IA, G_IM_SIZ_8b, 16, 12, 0, G_TX_MIRROR | G_TX_CLAMP,
                        G_TX_MIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    gDPPipeSync(gfx++);
    gSPTextureRectangle(gfx++, x << 2, y << 2, (x + 0xF) << 2, (y + 0xB) << 2, G_TX_RENDERTILE, 0, 0,
                        0x0400, 0x0400);
    gSPDisplayList(gfx++, D_8A12EC40);
    return gfx;
}

/**
 * Draws a label box frame of `width` x `height` at (left, top) from 8x8 corner and edge tiles. `style` picks
 * the tab on top (0 the short title tab, 1 the long one, 2 none) and `filled` 1 fills the box with the GB
 * game's color (sGbGameCategory: red, green, blue, yellow).
 * Seen in play (2026-11-14, Green save): the dark green boxes of ポッポのすみか, the area name, the
 * level / rate line and the R button hint.
 */
Gfx* Pokedex_DrawLabelFrame(Gfx* gfx, s32 left, s32 top, s32 width, s32 height, s32 style, s32 filled) {
    u32 temp_v0 = strlen(sAreaNames[sSelectedSlot]) * 8;
    s32 tmp;
    s32 y;
    gDPLoadTextureBlock(gfx++, D_8A12CCC0, G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 8, 0, G_TX_MIRROR | G_TX_CLAMP,
                        G_TX_MIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    y = top;
    tmp = left + width;
    gSPTextureRectangle(gfx++, (tmp - 8) << 2, y << 2, tmp << 2, (y + 8) << 2, G_TX_RENDERTILE, 0, 0, 0x0400, 0x0400);
    switch (style) {
        case 0:
            gSPTextureRectangle(gfx++, ((tmp - width) + 0x3E) << 2, y << 2, (tmp - 8) << 2, (y + 8) << 2, G_TX_RENDERTILE, 0,
                                0, -0x0400, 0x0400);
            break;

        case 1:
            gSPTextureRectangle(gfx++, ((tmp - width) + 0x46) << 2, y << 2, (tmp - 8) << 2, (y + 8) << 2,
                                G_TX_RENDERTILE, 0, 0, -0x0400, 0x0400);
            break;

        case 2:
            gSPTextureRectangle(gfx++, ((tmp - width) + 8) << 2, y << 2, (tmp - 8) << 2, (y + 8) << 2, G_TX_RENDERTILE,
                                0, 0, -0x0400, 0x0400);
            break;

        default:
            break;
    }

    gDPLoadTextureBlock(gfx++, D_8A12CD48, G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 8, 0, G_TX_MIRROR | G_TX_CLAMP,
                        G_TX_MIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    y = top + height;
    gSPTextureRectangle(gfx++, (tmp - 8) << 2, (y - 8) << 2, tmp << 2, y << 2, G_TX_RENDERTILE, 0, 0, 0x0400,
                        0x0400);
    gSPTextureRectangle(gfx++, ((tmp - width) + 8) << 2, (y - 8) << 2, (tmp - 8) << 2, y << 2, G_TX_RENDERTILE, 0,
                        0, -0x0400, 0x0400);
    gSPTextureRectangle(gfx++, (tmp - 8) << 2, ((y - height) + 8) << 2, tmp << 2, (y - 8) << 2, G_TX_RENDERTILE, 0,
                        0, 0x0400, -0x0400);
    gDPLoadTextureBlock(gfx++, D_8A12CDD0, G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 8, 0, G_TX_MIRROR | G_TX_CLAMP,
                        G_TX_MIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    // idk
    tmp = left;
    gSPTextureRectangle(gfx++, tmp << 2, (y - 8) << 2, (tmp + 8) << 2, y << 2, G_TX_RENDERTILE, 0, 0, 0x0400,
                        0x0400);
    switch (style) {
        case 2:
            gSPTextureRectangle(gfx++, left << 2, ((y - height) + 8) << 2, (left + 8) << 2, (y - 8) << 2,
                                G_TX_RENDERTILE, 0, 0, 0x0400, -0x0400);
            break;

        case 0:
        case 1:
            gSPTextureRectangle(gfx++, left << 2, (y - height) << 2, (left + 8) << 2, (y - 8) << 2,
                                G_TX_RENDERTILE, 0, 0, 0x0400, -0x0400);

            break;

        default:
            break;
    }
    switch (style) {
        case 2:
            gDPLoadTextureBlock(gfx++, D_8A12CE58, G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 8, 0,
                                G_TX_MIRROR | G_TX_CLAMP, G_TX_MIRROR | G_TX_CLAMP,
                                G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            // dumb
            y = top;
            gSPTextureRectangle(gfx++, left << 2, y << 2, (left + 8) << 2, (y + 8) << 2,
                                G_TX_RENDERTILE, 0, 0, 0x0400, 0x0400);
            break;
        default:
            break;
    }
    if (filled == 1) {
        switch (sGbGameCategory) {
            case 0:
                gDPSetPrimColor(gfx++, 0xFF, 0xFF, 106, 40, 20, 200); // #6A2814C8
                break;

            case 1:
                gDPSetPrimColor(gfx++, 0xFF, 0xFF, 0, 44, 0, 200); // #002C00C8
                break;

            case 2:
                gDPSetPrimColor(gfx++, 0xFF, 0xFF, 0, 0, 139, 200); // #00008BC8
                break;

            case 3:
                gDPSetPrimColor(gfx++, 0xFF, 0xFF, 160, 160, 0, 200); // #A0A000C8
                break;

            default:
                break;
        }

        gDPLoadTextureBlock(gfx++, D_8A12E850, G_IM_FMT_IA, G_IM_SIZ_16b, 4, 4, 0, G_TX_MIRROR | G_TX_CLAMP,
                            G_TX_MIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        gSPTextureRectangle(gfx++, (tmp + 2) << 2, (top + 2) << 2, ((tmp + width) - 2) << 2,
                            ((top + height) - 2) << 2, G_TX_RENDERTILE, 0, 0, 0x0400, 0x0400);
        gDPSetPrimColor(gfx++, 0xFF, 0xFF, 255, 255, 255, 200); // #FFFFFFC8
    }
    y = top;
    switch (style) {
        case 2:
        default:
            break;

        case 1:
            gDPLoadTextureBlock(gfx++, D_8A12C8F0, G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 15, 0, G_TX_MIRROR | G_TX_CLAMP,
                                G_TX_MIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            // almost worse than the old fake
            tmp = left;
            width = (tmp + temp_v0) - 0x10;
            height = top - 0xC;
            gSPTextureRectangle(gfx++, tmp << 2, height << 2, width << 2, (height + 15) << 2,
                                G_TX_RENDERTILE, 0, 0, 0x0400, 0x0400);
            gDPLoadTextureBlock(gfx++, D_8A12C9E8, G_IM_FMT_RGBA, G_IM_SIZ_16b, 24, 15, 0, G_TX_MIRROR | G_TX_CLAMP,
                                G_TX_MIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            gSPTextureRectangle(gfx++, width << 2, (y - 0xC) << 2,
                                (width + 0x18) << 2, (top + 3) << 2, G_TX_RENDERTILE, 0, 0,
                                0x0400, 0x0400);
            break;

        case 0:
            gDPLoadTextureBlock(gfx++, D_8A12CEE0, G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 8, 0, G_TX_MIRROR | G_TX_CLAMP,
                                G_TX_MIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            height = top - 5;
            gSPTextureRectangle(gfx++, tmp << 2, height << 2, (left + 0x2E) << 2, (height + 8) << 2, G_TX_RENDERTILE, 0,
                                0, 0x0400, 0x0400);
            gDPLoadTextureBlock(gfx++, D_8A12CF68, G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 8, 0, G_TX_MIRROR | G_TX_CLAMP,
                                G_TX_MIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            gSPTextureRectangle(gfx++, (left + 0x2E) << 2, (top - 5) << 2, (left + 0x3E) << 2, (top + 3) << 2,
                                G_TX_RENDERTILE, 0, 0, 0x0400, 0x0400);
            break;
    }

    return gfx;
}

extern GeoDisplayListNode sLabelFramesNode;
extern s16 sLabelWidth;
extern Gfx D_8A12EBB8[];
extern Gfx D_8A12EBF0[];
extern Gfx D_8A12F128[];
extern Gfx D_8A12F150[];
/**
 * Builds sLabelFramesNode's display list: the label boxes (Pokedex_DrawLabelFrame) behind the area map's
 * text, the R button icon, and their fills. The level / rate box is sized from sLabelWidth and the
 * species' encounter count; the せいそくちふめい box is used when sHabitatUnknown.
 * Seen in play (2026-11-14): ポッポのすみか, 2ばんどうろ, レベル 3〜5 たくさんみかける (when zoomed) and the
 * R button hint; earlier (2026-11-13) the せいそくちふめい box for フシギダネ.
 */
void Pokedex_BuildLabelFramesDisplayList(void) {
    s16 sp46;
    s16 sp44;
    s16 sp42;
    s16 sp40;
    s16 sp3E;
    s16 sp3C;
    UNUSED s32 pad; // FAKE: stack padding
    s32 temp_v0_2;
    Gfx* temp_v0;
    s32 sp2C;

    temp_v0 = Gfx_AllocDisplayList(sizeof(Gfx) * 450);
    sLabelFramesNode.displayList = temp_v0;

    gSPDisplayList(temp_v0++, D_8A12EBB8);

    temp_v0 = Pokedex_DrawLabelFrame(temp_v0, 0x1E, 0x14, 0x64, 0x10, 0, 1);

    if (sHabitatUnknown == 1) {
        if (sLabelWidth > 0) {
            sp46 = 0xA0 - (sLabelWidth / 2);
            sp44 = sLabelWidth;
            temp_v0 = Pokedex_DrawLabelFrame(temp_v0, sp46, 0x78, sLabelWidth, 0x14, 0, 1);
        }
    } else {
        if (sGbMapShown == 0) {
            sp2C = sSlotToArea[sSelectedSlot] - 1;
            temp_v0 = Pokedex_DrawLabelFrame(temp_v0, 0xB9, 0xD2, 0x73, 0x10, 0, 1);
            if ((sAreaMapZoomed == 1) && (sp2C >= 0) && (sCameraMoving == 0) && (sLabelWidth > 0) && (sCameraSettledFrames != 0)) {
                temp_v0_2 = (sMapAreas[sp2C].count * 0xA) - 0xA;
                sp42 = 0x8C - (sLabelWidth / 2);
                sp40 = 0xB4 - temp_v0_2;
                sp3E = sLabelWidth + 0x28;
                sp3C = temp_v0_2 + 0x14;
                temp_v0 = Pokedex_DrawLabelFrame(temp_v0, sp42, sp40, sp3E, sp3C, 2, 1);
            }
        } else {
            temp_v0 = Pokedex_DrawLabelFrame(Pokedex_DrawLabelFrame(temp_v0, 0x4F, 0x2F, 0x97, 0x86, 0, 0), 0x4F, 0xB5, 0x97, 0x10, 2, 1);
        }
        temp_v0 = Pokedex_DrawLabelFrame(temp_v0, 0x1E, 0xD2, 0x78, 0x10, 0, 1);
    }

    gSPDisplayList(temp_v0++, D_8A12EBF0);

    if ((sHabitatUnknown == 0) && (sGbMapShown == 0)) {
        temp_v0 = Pokedex_DrawRButtonIcon(temp_v0, 0xBC, 0xD5);
    }
    if (sGbMapShown == 1) {
        temp_v0 = Pokedex_DrawRButtonIcon(temp_v0, 0x56, 0xB7);
    }

    gSPDisplayList(temp_v0++, D_8A12F128);

    if ((sHabitatUnknown == 1) && (sLabelWidth > 0)) {
        gDPFillRectangle(temp_v0++, sp46 - 1, 119, sp46 + sp44 + 1, 141);
    }

    gDPFillRectangle(temp_v0++, 29, 19, 131, 37);
    gDPFillRectangle(temp_v0++, 184, 209, 301, 227);
    gDPFillRectangle(temp_v0++, 29, 209, 151, 227);

    if (sGbMapShown == 1) {
        gDPFillRectangle(temp_v0++, 79, 47, 232, 199);
    }

    if ((sAreaMapZoomed == 1) && (sCameraMoving == 0) && (sLabelWidth > 0)) {
        gDPFillRectangle(temp_v0++, sp42 - 1, sp40 - 1, sp42 + sp3E + 1, sp40 + sp3C + 1);
    }

    gSPDisplayList(temp_v0++, D_8A12F150);
    gSPEndDisplayList(temp_v0++);
}

/**
 * Restarts the area map camera's easing: divisor 8, no settled frames.
 * Seen in play (2026-11-14): A (zoom in) and D-Up / D-Down (next / previous area) on ポッポ's map.
 */
void Pokedex_ResetCameraEase(void) {
    sCameraEaseDivisor = 8.0f;
    sCameraSettledFrames = 0;
}

/**
 * Lowers the camera easing divisor by 0.5 a frame down to 1, then counts settled frames (sCameraSettledFrames),
 * which gate the area's level / rate text.
 * Seen in play (2026-11-14): every area map frame.
 */
void Pokedex_UpdateCameraEaseSpeed(void) {
    sCameraEaseDivisor -= 0.5f;
    if (sCameraEaseDivisor < 1.0f) {
        sCameraEaseDivisor = 1.0f;
        sCameraSettledFrames++;
    }
}

/**
 * Moves `current` toward `target` by 1/sCameraEaseDivisor of the distance on each axis, snapping within 1;
 * sets sCameraMoving while any axis is 200 or more away.
 * Seen in play (2026-11-14): eased the camera's eye and target when zooming in on 2ばんどうろ.
 */
void Pokedex_EaseVec3Toward(Vec3f* current, Vec3f* target) {
    f32 sp2C;
    f32 sp28;
    f32 sp24;
    f32 sp20;
    f32 sp1C;
    f32 temp_fv0;

    sp2C = target->x - current->x;
    sp28 = target->y - current->y;
    sp24 = target->z - current->z;

    sp20 = Math_AbsF32(sp2C);
    sp1C = Math_AbsF32(sp28);
    temp_fv0 = Math_AbsF32(sp24);
    if (sp20 < 1.0f) {
        current->x = target->x;
    } else {
        current->x += sp2C / sCameraEaseDivisor;
    }

    if (sp1C < 1.0f) {
        current->y = target->y;
    } else {
        current->y += sp28 / sCameraEaseDivisor;
    }

    if (temp_fv0 < 1.0f) {
        current->z = target->z;
    } else {
        current->z += sp24 / sCameraEaseDivisor;
    }

    if ((sp20 < 200.0f) && (sp1C < 200.0f) && (temp_fv0 < 200.0f)) {
        sCameraMoving = 0;
    } else {
        sCameraMoving = 1;
    }
}

/**
 * Per-frame area map update: eases the camera to the overview (zoomed out) or above the selected area
 * (sAreaMapZoomed), sets the clip planes, and rebuilds the four display lists.
 * Seen in play (2026-11-14): every frame of ポッポ's map.
 */
void Pokedex_UpdateAreaMapFrame(void) {
    UNUSED s32 pad; // FAKE: stack padding
    CameraNode* node = sAreaMapRoot->children;
    Vec3f* vec;
    Vec3f sp28;

    switch (sAreaMapZoomed) {
        case 0:
            Pokedex_EaseVec3Toward(&node->view.targetPosition, &sOverviewCameraTarget);
            Pokedex_EaseVec3Toward(&node->view.eyePosition, &sOverviewCameraEye);
            break;

        case 1:
            vec = &sAreaPinPositions[sSlotToArea[sSelectedSlot] - 1];

            sp28.x = vec->x;
            sp28.y = vec->y + 1000.0f;
            sp28.z = vec->z + 700.0f;

            Pokedex_EaseVec3Toward(&node->view.targetPosition, vec);
            Pokedex_EaseVec3Toward(&node->view.eyePosition, &sp28);
            break;
    }

    Pokedex_UpdateCameraEaseSpeed();
    node->perspective.nearPlane = 100.0f;
    node->perspective.farPlane = 12800.0f;
    sAreaMapFrameCounter++;

    Pokedex_BuildGbMapDisplayList();
    Pokedex_BuildAreaPinsDisplayList();
    Pokedex_BuildGbMapMarkersDisplayList();
    Pokedex_BuildLabelFramesDisplayList();
}

/**
 * Maps an encounter rate (out of 256) to the 8 tiers of sEncounterRateTierText: 0 いるかもしんない,
 * 1 あまりみかけない, 2 たまにみかける, 3 ときどきみかける, 4 けっこうみかける, 5 たくさんみかける,
 * 6 うじゃうじゃいる, 7 かならずみつかる (thresholds 2, 6, 11, 21, 41, 81, 100).
 * Seen in play (2026-11-14): rate 45 for ポッポ on 2ばんどうろ gave たくさんみかける.
 */
s32 Pokedex_GetEncounterRateTier(s32 rate) {
    s32 ret;

    if (rate < 2) {
        ret = 0;
    } else if (rate < 6) {
        ret = 1;
    } else if (rate < 0xB) {
        ret = 2;
    } else if (rate < 0x15) {
        ret = 3;
    } else if (rate < 0x29) {
        ret = 4;
    } else if (rate < 0x51) {
        ret = 5;
    } else if (rate < 0x64) {
        ret = 6;
    } else {
        ret = 7;
    }

    return ret;
}

typedef struct Label8A104B00 {
    /* 0x00 */ char text[0x2E];
    /* 0x2E */ s16 width;
} Label8A104B00; // size = 0x30
typedef struct Area8A104B00 {
    /* 0x00 */ char name[0xA];
    /* 0x0A */ s16 group;
} Area8A104B00; // size = 0xC
extern Label8A104B00 sAreaLabels[];
extern s16 sAreaLabelOrder[];
extern Area8A104B00 sEncounterLocations[];
extern char sEncounterRateTierText[][0x12];
extern char D_8A12F190[];
extern char D_8A12F19C[];
extern char D_8A12F1B0[];
extern char D_8A12F1C8[];
extern char D_8A12F1FC[];
extern char D_8A12F204[];
extern char D_8A12F208[];
extern char D_8A12FD60[];
extern char D_8A12FD68[];
extern char D_8A12FD6C[];
extern char D_8A12FD70[];
extern char D_8A12FD74[];
extern char D_8A12FD8C[];
extern char D_8A12FDA0[];
extern char D_8A12FDBC[];
extern char D_8A12FDD4[];
extern char D_8A12FDE4[];
extern char D_8A12FDF0[];
extern char D_8A12FE04[];
extern char D_8A12FE14[];
extern char D_8A12FE18[];
extern char D_8A12FE1C[];
extern s16 sLastLabelWidth;
extern char sAreaMapSpeciesName[];
extern s16 sShowEncounterPercent;
void BgStage_DrawFrame(void);
/**
 * Draws one frame of the area map (also its BgStage_RunUntilCondition fade callback): updates the camera,
 * renders the 3D map, and prints %sのすみか (habitat), the area name, ボタンでGBマップ / ボタンでGBマップを
 * けす, and while zoomed in and settled the area's lines "location レベル min〜max tier" (or
 * かくりつ %d%% when sShowEncounterPercent, which nothing sets), or せいそくちふめい (habitat unknown).
 * Seen in play (2026-11-14): ポッポのすみか, 2ばんどうろ, レベル 3〜5 たくさんみかける; 2026-11-13
 * フシギダネのすみか with せいそくちふめい.
 */
s32 Pokedex_DrawAreaMapScreen(UNUSED u8 unused)
{
  char *name = sAreaNames[sSelectedSlot];
  PokedexEncounter *temp_s2;
  s32 temp_s0;
  char *str;
  s32 i;
  s32 tier;
  s32 var_a1;
  s32 j;
  s32 temp_s1;
  s32 temp_s4;
  s32 x;
  s32 idx;
  s32 sel;
  s32 pad[1]; // FAKE: unused stack word
  Pokedex_UpdateAreaMapFrame();
  GeoRender_AdvanceFrameCounter();
  BgStage_DrawFrame();
  Geo_RenderRootNode(sAreaMapRoot);
  Font_BeginTranslucentTextRendering();
  Font_SetActive(1, 0);
  Gfx_SetEnvColor(0xFF, 0xFF, 0xFF, 0xFF);
  Font_Printf(0x23, 0x17, D_8A12FD60, sAreaMapSpeciesName, D_8A12F190);
  sLabelWidth = 0;
  if (sHabitatUnknown == 1)
  {
    sprintf(sAreaLabels[0].text, D_8A12FD68, D_8A12F1C8);
    sLabelWidth = ((strlen(sAreaLabels[0].text) * 5) + 0x1E) & 0xFFF8;
    Font_Printf(0xAF - (sLabelWidth / 2), 0x7D, D_8A12FD6C, sAreaLabels[0].text);
  }
  else
  {
    if (sGbMapShown == 0)
    {
      temp_s0 = sSlotToArea[sSelectedSlot];
      temp_s0--;
      Font_Printf(0xCB, 0xD5, D_8A12FD70, D_8A12F19C);
      if (sAreaMapZoomed == 1)
      {
        PokedexMapArea *ptr = &sMapAreas[temp_s0];
        if ((ptr->hasSpecies == 1) && (sCameraMoving == 0))
        {
          s16 tmp = ptr->count;
          if (tmp > 0)
          {
            for (i = 0; i < tmp; i++)
            {
              temp_s2 = ptr->encounters[i];
              temp_s1 = temp_s2->minLevel;
              temp_s4 = temp_s2->maxLevel;
              tier = Pokedex_GetEncounterRateTier(temp_s2->rate);
              str = sEncounterLocations[ptr->locations[i]].name;
              if (sShowEncounterPercent == 1)
              {
                if (temp_s1 == temp_s4)
                {
                  if (tmp >= 2)
                  {
                    sprintf(sAreaLabels[i].text, D_8A12FD74, str, D_8A12F1FC, temp_s1, D_8A12F208, temp_s2->rate);
                  }
                  else
                  {
                    sprintf(sAreaLabels[i].text, D_8A12FD8C, str, D_8A12F1FC, temp_s1, D_8A12F208, temp_s2->rate);
                  }
                }
                else
                  if (tmp >= 2)
                {
                  sprintf(sAreaLabels[i].text, D_8A12FDA0, str, D_8A12F1FC, temp_s1, D_8A12F204, temp_s4, D_8A12F208, temp_s2->rate);
                }
                else
                {
                  sprintf(sAreaLabels[i].text, D_8A12FDBC, str, D_8A12F1FC, temp_s1, D_8A12F204, temp_s4, D_8A12F208, temp_s2->rate);
                }
              }
              else
                if (temp_s1 == temp_s4)
              {
                if (tmp >= 2)
                {
                  sprintf(sAreaLabels[i].text, D_8A12FDD4, str, D_8A12F1FC, temp_s1, sEncounterRateTierText[tier]);
                }
                else
                {
                  sprintf(sAreaLabels[i].text, D_8A12FDE4, str, D_8A12F1FC, temp_s1, sEncounterRateTierText[tier]);
                }
              }
              else
                if (tmp >= 2)
              {
                sprintf(sAreaLabels[i].text, D_8A12FDF0, str, D_8A12F1FC, temp_s1, D_8A12F204, temp_s4, sEncounterRateTierText[tier]);
              }
              else
              {
                sprintf(sAreaLabels[i].text, D_8A12FE04, str, D_8A12F1FC, temp_s1, D_8A12F204, temp_s4, sEncounterRateTierText[tier]);
              }
              sLabelWidth = ((strlen(sAreaLabels[i].text) * 5) + 0x32) & 0xFFF8;
              sAreaLabels[i].width = sLabelWidth;
            }

            var_a1 = 0;
            for (x = 0; x < 7; x++)
            {
              for (j = 0; j < tmp; j++)
              {
                idx = sEncounterLocations[ptr->locations[j]].group;
                if (idx == x)
                {
                  sAreaLabelOrder[var_a1] = j;
                  var_a1 += 1;
                  if (var_a1 >= tmp)
                  {
                    x = 7;
                    break;
                  }
                }
              }

            }

            if (sCameraSettledFrames != 0)
            {
              for (i = 0; i < tmp; i++)
              {
                sel = sAreaLabelOrder[i];
                if (sAreaLabels[sel].width > 0)
                {
                  Font_Printf(0xA0 - (sLabelWidth / 2), ((i * 0xA) - (tmp * 0xA)) + 0xC3, D_8A12FE14, sAreaLabels[sel].text);
                }
              }

            }
          }
        }
      }
    }
    else
    {
      Font_Printf(0x65, 0xB8, D_8A12FE18, D_8A12F1B0);
    }
    if ((sCameraMoving == 0) || (sSelectedSlot == sPrevSelectedSlot))
    {
      Font_Printf(0x54 - (strlen(name) * 2), 0xD5, D_8A12FE1C, name);
    }
  }
  sLastLabelWidth = sLabelWidth;
  Font_EndTexturedTextRendering();
  return 0;
}

/**
 * Handles area map input: B on the overview returns -1 (leave). Unless the habitat is unknown, R toggles the
 * GB map, D-Up / D-Down move to the next / previous area, A zooms in on it and B zooms back out.
 * Seen in play (2026-11-14): each of these on ポッポ's map.
 */
s32 Pokedex_HandleAreaMapInput(void) {
    if ((gPlayer1Controller->buttonPressed & 0x4000) && (sAreaMapZoomed == 0)) {
        return -1;
    }

    if (sHabitatUnknown == 0) {
        if (gPlayer1Controller->buttonPressed & 0x10) {
            sGbMapShown = (sGbMapShown + 1) & 1;
            switch (sGbMapShown) {
                case 0:
                    Audio_PlaySoundEffectByIdWrapper(SFX_MENU_BACK);
                    break;
                case 1:
                    Audio_PlaySoundEffectByIdWrapper(SFX_MENU_CONFIRM);
                    break;
            }
        }

        if (gPlayer1Controller->buttonPressed & 0x800) {
            sPrevSelectedSlot = sSelectedSlot;
            sSelectedSlot = Pokedex_FindNextMapArea(sSelectedSlot);
            if (sPrevSelectedSlot != sSelectedSlot) {
                Audio_PlaySoundEffectByIdWrapper(SFX_MENU_SCROLL);
                Pokedex_ResetCameraEase();
            }
        }

        if (gPlayer1Controller->buttonPressed & 0x400) {
            sPrevSelectedSlot = sSelectedSlot;
            sSelectedSlot = Pokedex_FindPrevMapArea(sSelectedSlot);
            if (sPrevSelectedSlot != sSelectedSlot) {
                Audio_PlaySoundEffectByIdWrapper(SFX_MENU_SCROLL);
                Pokedex_ResetCameraEase();
            }
        }

        switch (sAreaMapZoomed) {
            case 0:
                if (gPlayer1Controller->buttonPressed & 0x8000) {
                    sAreaMapZoomed = 1;
                    if (sGbMapShown == 1) {
                        sGbMapShown = 0;
                    }
                    sPrevSelectedSlot = sSelectedSlot;
                    Audio_PlaySoundEffectByIdWrapper(SFX_ZOOM_IN);
                    Pokedex_ResetCameraEase();
                }
                break;

            case 1:
                if (gPlayer1Controller->buttonPressed & 0x4000) {
                    sAreaMapZoomed = 0;
                    sCameraMoving = 1;
                    sPrevSelectedSlot = sSelectedSlot;
                    Audio_PlaySoundEffectByIdWrapper(SFX_ZOOM_OUT);
                    Pokedex_ResetCameraEase();
                }
                break;
        }
    }
    return 0;
}

extern unk_D_80064C60 D_80064C60[];
extern s16 sLastLabelWidth;
extern s16 sShowEncounterPercent;
extern s16 sAreaMapSpeciesIndex;
extern char sAreaMapSpeciesName[];
extern void* D_8A1302D0;
extern s16 sLocationToSlot[];
extern PokedexEncounter* sRedEncounters[];
extern PokedexEncounter* sGreenEncounters[];
extern PokedexEncounter* sBlueEncounters[];
extern PokedexEncounter* sYellowEncounters[];
extern u8 sAreaMapGeoLayout[];
extern u8 D_8F100000[];
extern u8 D_00326700[];
extern u8 D_003553C0[];
extern u8 D_003FEBD0[];
extern u8 D_003FFD60[];
/**
 * Loads the area map for `species` (dex number): resets the map state, loads the species icon for the pins,
 * loads and relocates the map model (into `pool`, using `load_buffer`), and fills sMapAreas from the
 * encounter tables of the cartridge's game (red, green, blue or yellow). sHabitatUnknown stays 1 when no
 * table lists the species. Then picks the first area and builds the scene graph.
 * Seen in play (2026-11-14): species 16 (ポッポ) from a Green cartridge, sGbGameCategory 1.
 */
void Pokedex_LoadAreaMap(s32 species, MainPoolState* pool, UNUSED s32 pool_size, PERSSZP* load_buffer, s32 load_buffer_size) {
    s32 i;
    CameraNode* ptr;
    MemoryBlock* sp44;
    PokedexEncounter* var_v1_2;

    sp44 = MainPool_InitState(pool, 0x70800);
    sGbMapShown = 0;
    sCameraMoving = 0;
    sAreaMapZoomed = 0;
    sLastLabelWidth = 0;
    sShowEncounterPercent = 0;

    for (i = 0; i < 36; i++) {
        sMapAreas[i].hasSpecies = 0;
        sMapAreas[i].count = 0;
    }

    sAreaMapSpeciesIndex = species - 1;
    sprintf(sAreaMapSpeciesName, "%s", D_80064C60[sAreaMapSpeciesIndex].unk_00);
    MainPool_PushState('MAPV');

    sSpeciesIcon = MainPool_Alloc(0x3200, 0);
    Pokedex_LoadIcon(sSpeciesIcon, species);

    Fragment_LoadAndRelocateFromRomRange(sp44, (((u32)&D_8F100000 & 0x0FF00000) >> 0x14) - 0x10, (s32)D_00326700,
                  (s32)D_003553C0, load_buffer, load_buffer_size);

    D_8A1302D0 = BinArchive_GetFile(BinArchive_Open(D_003FEBD0, D_003FFD60, 1, 1), 0);
    GeoNode_CreateDisplayList(NULL, &sGbMapNode, 5, NULL);
    sHabitatUnknown = 1;

    for (i = 0; i < 59; i++) {
        if (sLocationToSlot[i] >= 0) {
            PokedexMapArea* temp_s0 = &sMapAreas[sSlotToArea[sLocationToSlot[i]] - 1];

            sGbGameCategory = GbSave_GameToCategoryIndex(GbSave_GetPortGame(GbSave_GetActivePort()));

            switch (sGbGameCategory) {
                case 0:
                    var_v1_2 = sRedEncounters[i];
                    break;

                case 1:
                    var_v1_2 = sGreenEncounters[i];
                    break;

                case 2:
                    var_v1_2 = sBlueEncounters[i];
                    break;

                case 3:
                    var_v1_2 = sYellowEncounters[i];
                    break;

                default:
                    var_v1_2 = sYellowEncounters[i];
                    break;
            }

            while (true) {
                if (var_v1_2->species < 0) {
                    break;
                }

                if (sAreaMapSpeciesIndex == var_v1_2->species - 1) {
                    temp_s0->hasSpecies = 1;
                    temp_s0->encounters[temp_s0->count] = var_v1_2;
                    temp_s0->locations[temp_s0->count] = i;
                    sHabitatUnknown = 0;
                    temp_s0->count++;
                }
                var_v1_2++;
            }
        }
    }

    sSelectedSlot = Pokedex_FindNextMapArea(0);
    sPrevSelectedSlot = sSelectedSlot;
    GeoNode_CreateDisplayList(NULL, &sGbMapMarkersNode, 5, NULL);
    GeoNode_CreateDisplayList(NULL, &sLabelFramesNode, 5, NULL);
    GeoNode_CreateDisplayList(NULL, &sAreaPinsNode, 4, NULL);
    sAreaMapRoot = GeoLayout_Process(sp44, sAreaMapGeoLayout);
    ptr = (CameraNode*)sAreaMapRoot->children;
    ptr->view.targetPosition = sOverviewCameraTarget;
    ptr->view.eyePosition = sOverviewCameraEye;
}

/**
 * Pops the 'MAPV' pool state that Pokedex_LoadAreaMap pushed.
 * Seen in play (2026-11-14): ran as the area map closed.
 */
void Pokedex_ExitAreaMapPool(void) {
    MainPool_PopState('MAPV');
}
