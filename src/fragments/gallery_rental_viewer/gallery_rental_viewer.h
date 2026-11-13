#ifndef _FRAGMENT47_H_
#define _FRAGMENT47_H_

#include "global.h"
#include "src/gallery.h"
#include "src/geo_layout.h"
#include "src/fragments/gallery_backgrounds/gallery_backgrounds.h"

typedef struct unk_D_838067F0_0168_0000 {
    union {
        struct {
            /* 0x000 */ u8 unk_000;
            /* 0x001 */ u8 unk_001;
            /* 0x002 */ u8 unk_002;
            /* 0x003 */ u8 unk_003;
        };
        s32 raw;
    };
    /* 0x004 */ BattleMon unk_004;
    /* 0x058 */ u16 unk_058[0x640];
} unk_D_838067F0_0168_0000; // size = 0xCD8

typedef struct unk_D_838067F0_0168 {
    /* 0x0000 */ unk_D_838067F0_0168_0000 unk_0000[3];
    /* 0x2688 */ struct unk_D_838067F0_0168* unk_2688;
    /* 0x268C */ struct unk_D_838067F0_0168* unk_268C;
    /* 0x2690 */ s16 unk_2690;
    /* 0x2692 */ s16 unk_2692;
    /* 0x2694 */ char unk2694[0x4];
} unk_D_838067F0_0168; // size = 0x2698

typedef struct unk_D_838067F0_003C {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ u8 unk_02[1];
    /* 0x03 */ char unk03[0x13];
} unk_D_838067F0_003C; // size = 0x16

typedef struct unk_D_8380548C {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ s16 unk_0C;
} unk_D_8380548C; // size = 0xE

#endif // _FRAGMENT47_H_
