/* Declarations for the disk_error_screen fragment (src/fragments/disk_error_screen/). */
#ifndef FRAGMENT_DISK_ERROR_SCREEN_H
#define FRAGMENT_DISK_ERROR_SCREEN_H

#include "global.h"
#include "asset_archive.h"
#include "game_state.h"
#include "gfx_rect.h"

typedef struct unk_D_83407AC8 {
    /* 0x00 */ u16 unk_00;
    /* 0x02 */ u8 unk_02;
    /* 0x03 */ s8 unk_03[11];
    /* 0x0E */ s8 unk_0E[11];
} unk_D_83407AC8; // size >= 0x1A

typedef struct unk_D_83403C60 {
    /* 0x00 */ BattleMon unk_00;
    /* 0x54 */ char unk54[0x18];
    /* 0x6C */ u8 unk_6C;
    /* 0x6D */ char unk6D[0x3];
    /* 0x70 */ unk_D_83407AC8 unk_70;
    /* 0x8A */ char unk8A[0x2];
} unk_D_83403C60; // size = 0x8C

typedef struct unk_func_80031270_024 {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ char pad2[0x12];
    /* 0x14 */ s32 unk_14;
    /* 0x18 */ s16 unk_18;
    /* 0x1A */ s16 unk_1A;
    /* 0x1C */ s32 unk_1C;
} unk_func_80031270_024; // size = 0x20

typedef struct unk_func_80031270 {
    /* 0x00 */ u16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ GfxImage* unk_08;
    /* 0x0C */ GfxImage* unk_0C;
    /* 0x10 */ ModelLoadContext* unk_10;
    /* 0x14 */ BinArchive* unk_14;
    /* 0x18 */ unk_D_83403C60* unk_18;
    /* 0x1C */ GraphNode* unk_1C;
    /* 0x20 */ DisplayObject* unk_20;
    /* 0x24 */ unk_func_80031270_024* unk_24;
    /* 0x28 */ GraphNode* unk_28;
    /* 0x2C */ GraphNode* unk_2C;
    /* 0x30 */ GraphNode* unk_30;
    /* 0x34 */ s32 unk_34;
} unk_func_80031270; // size = 0x38

#endif // FRAGMENT_DISK_ERROR_SCREEN_H
