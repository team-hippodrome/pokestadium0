/* Declarations for the geo_model_033 fragment (src/fragments/geo_model_033/). */
#ifndef FRAGMENT_GEO_MODEL_033_H
#define FRAGMENT_GEO_MODEL_033_H

#include "global.h"
#include "game_state.h"
#include "fragments/vs_scene/vs_scene.h"

// Geo callback node; callbackArg holds a team index, or (team << 16) | slot.
typedef struct DemoGeoNode {
    /* 0x00 */ GraphNode node;
    /* 0x18 */ Gfx* displayList; // @unverified: built by the geo callbacks as in GeoDisplayListNode
    /* 0x1C */ char unk1C[0x4];
    /* 0x20 */ s16 unk_20;
    /* 0x22 */ s16 unk_22;
    /* 0x24 */ void* unk_24;
} DemoGeoNode;

#endif // FRAGMENT_GEO_MODEL_033_H
