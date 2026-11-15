/* Declarations for the geo_model_033 fragment (src/fragments/geo_model_033/). */
#ifndef FRAGMENT_GEO_MODEL_033_H
#define FRAGMENT_GEO_MODEL_033_H

#include "global.h"

// One entry of the demo scenes' per-team array (fragment013's D_82203170), which the demo
// stadium fragments reach through D_80060490's callbackArg.
typedef struct DemoGeoTeam {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ char unk01[0x3];
    /* 0x04 */ void* unk_04;
    /* 0x08 */ void* unk_08[6];
    /* 0x20 */ void* unk_20[6];
    /* 0x38 */ u8* unk_38[2];
    /* 0x40 */ u8* unk_40[2];
} DemoGeoTeam; // size = 0x48

// Geo callback node; callbackArg holds a team index, or (team << 16) | slot.
typedef struct DemoGeoNode {
    /* 0x00 */ GraphNode node;
    /* 0x18 */ Gfx* unk_18;
    /* 0x1C */ char unk1C[0x4];
    /* 0x20 */ s16 unk_20;
    /* 0x22 */ s16 unk_22;
    /* 0x24 */ void* unk_24;
} DemoGeoNode;

#endif // FRAGMENT_GEO_MODEL_033_H
