/* Stadium Zero fragment034_369F50: the trainer cap with the eight tournament badges. */

/*
 * The VS scene (VsScene_Run) loads this fragment and builds its two models in VsScene_LoadGeoLayout:
 * - D_8EB300B0 (drawn by D_822033D0): a red-and-white trainer cap with eight badge slots, one per
 *   tournament round. The slots use three badge kinds: four red, three silver and one gold.
 * - D_8EB37440 (drawn by D_82203538): the sparkles around the badge just won. A switch node picks
 *   the sparkle color for the round: dark red (0x960000) for rounds 1-4, silver (0xCDCDE1) for
 *   rounds 5-7, gold (0xFFFF00) for round 8.
 * Seen in play (2026-11-14) after winning round 1 of the L1-30 Monster Ball Cup: after かち the cap
 * spins in over the flames, the round 1 badge flies onto it with sparkles, and
 * トーナメントをつづけますか？ (Tournament_RunContinuePrompt) is asked over it. All eight functions
 * here ran every frame of that screen.
 */

#include "global.h"
#include "gfx_buffer.h"
#include "m2c_macros.h"
#include "tournament_badge_cap.h"

extern Gfx sBadgeMaterialDL[];
extern s32 sBadgeTextureScroll;
extern u16 sGoldBadgeEdgeTex[];
Gfx* BadgeCap_BuildBadgeTextureDL(Gfx* gfx, Gfx* mesh, void* texture, s32 shiftS, s32 shiftT, s32 scaleS,
                                  s32 scaleT);

extern DisplayObject* D_8006049C;

/**
 * Switch-case callback of the sparkle model: on traversal (event 2) it shows the child for the
 * current round, taken from the drawing DisplayObject's callbackArg (VsScene sets it to
 * roundOrDemoId - 1). Children 0-3, 4-6 and 7 set the red, silver and gold sparkle colors.
 * Seen in play (2026-11-14): ran on the round 1 win screen with callbackArg 0. Hiding D_82203538
 * (the model this callback belongs to) removed only the sparkles. The colors per child are read
 * from the model's display lists, not seen in play.
 */
void BadgeSparkle_SelectRoundColor(s32 event, GeoSwitchCaseNode* node) {
    if (event == 2) {
        node->selectedChild = (s16) D_8006049C->node.callbackArg;
    }
}

/**
 * Writes a badge's material: sBadgeMaterialDL, then the 32x32 RGBA16 `texture` (wrapping, with
 * the given shifts and texture scale), with the tile scrolled vertically by sBadgeTextureScroll,
 * and branches to `mesh`, the node's own display list. Returns the end of what it wrote.
 * Seen in play (2026-11-14): called by each badge callback below every frame of the round 1 win
 * screen.
 */
Gfx* BadgeCap_BuildBadgeTextureDL(Gfx* gfx, Gfx* mesh, void* texture, s32 shiftS, s32 shiftT, s32 scaleS,
                                  s32 scaleT) {
    gSPDisplayList(gfx++, sBadgeMaterialDL);
    gSPTexture(gfx++, scaleS, scaleT, 0, G_TX_RENDERTILE, G_ON);
    gDPLoadTextureBlock(gfx++, texture, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0, G_TX_WRAP | G_TX_NOMIRROR,
                        G_TX_WRAP | G_TX_NOMIRROR, 5, 5, shiftS, shiftT);
    gDPSetTileSize(gfx++, G_TX_RENDERTILE, 0, sBadgeTextureScroll, 0x7C, sBadgeTextureScroll + 0x7C);
    gSPBranchList(gfx++, mesh);
    return gfx;
}

extern u16 sRedBadgeRingTex[];

/**
 * Display-list callback for a red badge's faceted outer ring (sRedBadgeRingTex). The node's
 * callbackArg is the ring mesh.
 * Seen in play (2026-11-14): filling sRedBadgeRingTex with red turned the round 1 badge's outer
 * ring red in its close-up, and nothing else.
 */
void BadgeCap_DrawRedBadgeRing(s32 event, GeoDisplayListNode* node) {
    if (event == 2) {
        node->displayList = Gfx_AllocDisplayList(0x58);
        BadgeCap_BuildBadgeTextureDL(node->displayList, (Gfx*)node->node.callbackArg, sRedBadgeRingTex, 1, 1,
                                     0x1F40, 0x1F40);
    }
}

extern u16 sRedBadgeEdgeTex[];

/**
 * Display-list callback for the side band of a red badge's ring (sRedBadgeEdgeTex).
 * Seen in play (2026-11-14): filling sRedBadgeEdgeTex with green tinted the round 1 badge seen
 * edge-on on the cap; the front-on close-up did not change.
 */
void BadgeCap_DrawRedBadgeEdge(s32 event, GeoDisplayListNode* node) {
    if (event == 2) {
        node->displayList = Gfx_AllocDisplayList(0x58);
        BadgeCap_BuildBadgeTextureDL(node->displayList, (Gfx*)node->node.callbackArg, sRedBadgeEdgeTex, 1, 1,
                                     0x1F40, 0x1F40);
    }
}

extern u16 sSilverBadgeRingTex[];

/**
 * Display-list callback for a silver badge's ring (sSilverBadgeRingTex, a white marble texture).
 * Three slots on the cap use it, matching the silver sparkles of rounds 5-7.
 * @unverified Ran on the round 1 win screen, but no silver badge was on screen to see.
 */
void BadgeCap_DrawSilverBadgeRing(s32 event, GeoDisplayListNode* node) {
    if (event == 2) {
        node->displayList = Gfx_AllocDisplayList(0x58);
        BadgeCap_BuildBadgeTextureDL(node->displayList, (Gfx*)node->node.callbackArg, sSilverBadgeRingTex, 0, 0xF,
                                     0x1F40, 0x206C);
    }
}

extern u16 sSilverBadgeEdgeTex[];

/**
 * Display-list callback for the side band of a silver badge's ring (sSilverBadgeEdgeTex, grey bands).
 * @unverified Ran on the round 1 win screen, but no silver badge was on screen to see.
 */
void BadgeCap_DrawSilverBadgeEdge(s32 event, GeoDisplayListNode* node) {
    if (event == 2) {
        node->displayList = Gfx_AllocDisplayList(0x58);
        BadgeCap_BuildBadgeTextureDL(node->displayList, (Gfx*)node->node.callbackArg, sSilverBadgeEdgeTex, 0, 1,
                                     0xFA0, 0xFA0);
    }
}

extern u16 sGoldBadgeRingTex[];

/**
 * Display-list callback for the gold badge's ring (sGoldBadgeRingTex, a gold marble texture). One
 * slot on the cap uses it, matching the gold sparkles of round 8 (the final).
 * @unverified Ran on the round 1 win screen, but the gold badge was not on screen to see.
 */
void BadgeCap_DrawGoldBadgeRing(s32 event, GeoDisplayListNode* node) {
    if (event == 2) {
        node->displayList = Gfx_AllocDisplayList(0x58);
        BadgeCap_BuildBadgeTextureDL(node->displayList, (Gfx*)node->node.callbackArg, sGoldBadgeRingTex, 2, 0xE,
                                     0xFA0, 0xFA0);
    }
}

/**
 * Display-list callback for the side band of the gold badge's ring (sGoldBadgeEdgeTex, yellow
 * bands). It also steps sBadgeTextureScroll down by one, wrapping from below 0 to 0x7F, which
 * scrolls every badge texture since BadgeCap_BuildBadgeTextureDL offsets all of them by it.
 * Seen in play (2026-11-14): sBadgeTextureScroll went 102, 100, 100 over three frames of the round 1
 * win screen. @unverified that this node is the gold badge's edge.
 */
void BadgeCap_DrawGoldBadgeEdge(s32 event, GeoDisplayListNode* node) {
    if (event == 2) {
        sBadgeTextureScroll--;
        if (sBadgeTextureScroll < 0) {
            sBadgeTextureScroll = 0x7F;
        }
        node->displayList = Gfx_AllocDisplayList(0x58);
        BadgeCap_BuildBadgeTextureDL(node->displayList, (Gfx*)node->node.callbackArg, sGoldBadgeEdgeTex, 1, 1,
                                     0x1F40, 0x1F40);
    }
}
