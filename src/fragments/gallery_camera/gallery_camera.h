#ifndef _FRAGMENT15_H_
#define _FRAGMENT15_H_

#include "global.h"
#include "src/controller.h"
#include "src/model_renderer.h"

typedef struct unk_D_8690B2F8 {
    /* 0x00 */ f32 unk_00;
    /* 0x04 */ f32 unk_04;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ f32 unk_0C;
} unk_D_8690B2F8; // size >= 0x10

typedef struct unk_D_8690A710 {
    /* 0x000 */ char unk000[0x4];
    /* 0x004 */ f32 unk_004;
    /* 0x008 */ f32 unk_008;
    /* 0x00C */ s32 unk_00C;
    /* 0x010 */ char unk010[0x4];
    /* 0x014 */ u8 unk_014;
    /* 0x015 */ char unk015[0x16F];
} unk_D_8690A710; // size = 0x184

typedef struct unk_D_8690B350 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ s16 unk_0C;
    /* 0x0E */ s16 unk_0E;
} unk_D_8690B350; // size = 0x10

typedef struct unk_D_8690B360 {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ f32 unk_10;
    /* 0x14 */ f32 unk_14;
} unk_D_8690B360; // size = 0x18

typedef struct unk_D_8690B308 {
    /* 0x00 */ s16 unk_00[8];
    /* 0x18 */ f32 unk_10;
    /* 0x1C */ f32 unk_14;
    /* 0x20 */ f32 unk_18;
    /* 0x24 */ f32 unk_1C;
    /* 0x28 */ f32 unk_20;
    /* 0x2C */ f32 unk_24;
    /* 0x30 */ f32 unk_28;
    /* 0x34 */ f32 unk_2C;
    /* 0x38 */ s16 unk_30;
    /* 0x3A */ s16 unk_32;
    /* 0x3C */ s16 unk_34;
    /* 0x3E */ s16 unk_36;
} unk_D_8690B308; // size >= 0x38

typedef struct unk_D_8690B3C0 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
} unk_D_8690B3C0; // size >= 0x10

void func_82183DAC(void);

#endif // _FRAGMENT15_H_
