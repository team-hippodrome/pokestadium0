/* Declarations for src/fragments/tournament_badge_cap/. */
#ifndef TOURNAMENT_BADGE_CAP_H
#define TOURNAMENT_BADGE_CAP_H

#include "global.h"

// tournament_badge_cap.c
void BadgeSparkle_SelectRoundColor(s32 event, GeoSwitchCaseNode* node);
Gfx* BadgeCap_BuildBadgeTextureDL(Gfx* gfx, Gfx* mesh, void* texture, s32 shiftS, s32 shiftT, s32 scaleS,
                                  s32 scaleT);
void BadgeCap_DrawRedBadgeRing(s32 event, GeoDisplayListNode* node);
void BadgeCap_DrawRedBadgeEdge(s32 event, GeoDisplayListNode* node);
void BadgeCap_DrawSilverBadgeRing(s32 event, GeoDisplayListNode* node);
void BadgeCap_DrawSilverBadgeEdge(s32 event, GeoDisplayListNode* node);
void BadgeCap_DrawGoldBadgeRing(s32 event, GeoDisplayListNode* node);
void BadgeCap_DrawGoldBadgeEdge(s32 event, GeoDisplayListNode* node);

#endif // TOURNAMENT_BADGE_CAP_H
