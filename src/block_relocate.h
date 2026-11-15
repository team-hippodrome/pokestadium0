/* Declarations for src/block_relocate.c. */
#ifndef BLOCK_RELOCATE_H
#define BLOCK_RELOCATE_H

#include "global.h"

typedef struct RelocHeader8003A710 {
    /* 0x00 */ u32 count;
    /* 0x04 */ s32 flags;
    /* 0x08 */ u32 unk08;
    /* 0x0C */ u32 table;
} RelocHeader8003A710;

typedef struct Unk8003A7AC {
    /* 0x00 */ s32 size;
    /* 0x04 */ s32 flags;
    /* 0x08 */ s32 unk08[2];
    /* 0x10 */ u8 data[1];
} Unk8003A7AC;

// block_relocate.c
void func_8003A6F0(s32 arg0);
void func_8003A710(RelocHeader8003A710* arg0);
s32 func_8003A7AC(Unk8003A7AC* arg0);

#endif // BLOCK_RELOCATE_H
