#ifndef _FRAGMENT65_H_
#define _FRAGMENT65_H_

#include "global.h"

typedef struct GymLeaderCastleTrainer {
    /* 0x00 */ u8 loaded;
    /* 0x02 */ s16 portraitX;
    /* 0x04 */ s32 portrait;
    /* 0x08 */ char* name;
} GymLeaderCastleTrainer; // size = 0xC

typedef struct CastleMapNode {
    /* 0x00 */ u8 index;
    /* 0x01 */ u8 nodeState;
    /* 0x02 */ s16 labelX;
    /* 0x04 */ s16 labelY;
    /* 0x06 */ s16 cursorX;
    /* 0x08 */ s16 cursorY;
    /* 0x0A */ s16 markerX;
    /* 0x0C */ s16 markerY;
    /* 0x0E */ s16 markerWidth;
    /* 0x10 */ s16 markerHeight;
    /* 0x12 */ s16 pulsing;
    /* 0x14 */ s8 upNeighbor;
    /* 0x15 */ s8 downNeighbor;
    /* 0x16 */ s8 leftNeighbor;
    /* 0x17 */ s8 rightNeighbor;
    /* 0x18 */ Color_RGBA8 color;
    /* 0x1C */ u8* texture;
    /* 0x20 */ s16 bossTitle;
    /* 0x22 */ s16 fileNumber;
    /* 0x24 */ u8* infoPanelTexture;
} CastleMapNode; // size = 0x28

void func_821853FC(void);

#endif // _FRAGMENT65_H_
