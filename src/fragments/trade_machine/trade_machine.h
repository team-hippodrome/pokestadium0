#ifndef _FRAGMENT41_H_
#define _FRAGMENT41_H_

#include "global.h"
#include "src/poke_icon.h"
#include "src/game_state.h"

typedef struct unk_D_82F20A88 {
    /* 0x000 */ s16 unk_000;
    /* 0x002 */ s16 unk_002;
    /* 0x004 */ s16 unk_004;
    /* 0x006 */ s16 unk_006;
    /* 0x008 */ s16 unk_008;
    /* 0x00A */ s16 unk_00A;
    /* 0x00C */ s16 unk_00C;
    /* 0x00E */ s16 unk_00E;
    /* 0x010 */ s16 unk_010;
    /* 0x012 */ s16 unk_012;
    /* 0x014 */ s16 unk_014;
    /* 0x018 */ f32 unk_018;
    /* 0x01C */ f32 unk_01C;
    /* 0x020 */ f32 unk_020;
    /* 0x024 */ u8* unk_024;
    /* 0x028 */ DisplayObject unk_028;
} unk_D_82F20A88; // size = 0x190

void Trade_DrawSolidFillRect(s32 arg0, s32 arg1, s32 arg2, s32 arg3, Color_RGB8 arg4);

s32 Trade_DrawBox3DModel(s32 arg0, GraphNode* arg1);

void Trade_DrawSaveSeqMessageBackdrop(s16 arg0, s16 arg1, s16 arg2, s16 arg3);

#endif // _FRAGMENT41_H_
