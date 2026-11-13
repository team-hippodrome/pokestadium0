#ifndef _FRAGMENT43_H_
#define _FRAGMENT43_H_

#include "global.h"
#include "gallery.h"

typedef struct unk_D_83407B18_008 {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ char unk_0A[0x2];
} unk_D_83407B18_008; // size >= 0xC

typedef struct unk_D_83407B18 {
    /* 0x00 */ unk_D_83407B00 unk_00;
    /* 0x08 */ unk_D_83407B18_008 unk_08;
    /* 0x14 */ char unk14[0x4];
} unk_D_83407B18; // size = 0x18

void func_82183DA4(void);

#endif // _FRAGMENT43_H_
