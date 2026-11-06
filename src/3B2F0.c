/* Stadium Zero resident code. */

#include "global.h"
#include "m2c_macros.h"

void func_80037F48(s32, s32);

void func_8003A6F0(s32 arg0) {
    func_80037F48(arg0, arg0);
}

#ifdef NON_MATCHING
/* TODO: decompile func_8003A710; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_8003A710.s")
#endif

typedef struct Unk8003A7AC {
    /* 0x00 */ s32 size;
    /* 0x04 */ s32 flags;
    /* 0x08 */ s32 unk08[2];
    /* 0x10 */ u8 data[1];
} Unk8003A7AC;
s32 func_8003A7AC(Unk8003A7AC* arg0) {
    s32 end = arg0->size + (s32)arg0;

    func_80037F48((s32)arg0->data, end);
    arg0->flags |= 1;
    return (s32)arg0->data;
}
