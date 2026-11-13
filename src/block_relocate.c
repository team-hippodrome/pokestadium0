/* Stadium Zero resident code. */

#include "global.h"
#include "m2c_macros.h"

void func_80037F48(s32, s32);

void func_8003A6F0(s32 arg0) {
    func_80037F48(arg0, arg0);
}

/*
 * func_8003A710
 *
 * Relocates a loaded block in place: adds the block's own address to the word
 * at +0x08 and to the table offset at +0x0C, then to each of the `count` words
 * of that table, and sets bit 0 of the flags word at +0x04.  `i` doubles as the
 * offset temporary, which is what reproduces the retail register choice.
 */
typedef struct RelocHeader8003A710 {
    /* 0x00 */ u32 count;
    /* 0x04 */ s32 flags;
    /* 0x08 */ u32 unk08;
    /* 0x0C */ u32 table;
} RelocHeader8003A710;

void func_8003A710(RelocHeader8003A710* arg0) {
    u32 n;
    u32 i;
    u32* p;

    n = arg0->count;
    i = arg0->unk08;
    arg0->unk08 = (u32)arg0 + i;
    i = arg0->table;
    arg0->table = (u32)arg0 + i;
    p = (u32*)arg0->table;
    for (i = 0; i < n; i++) {
        *p++ += (u32)arg0;
    }
    arg0->flags |= 1;
}

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
