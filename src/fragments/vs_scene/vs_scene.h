/* Declarations for the vs_scene fragment (src/fragments/vs_scene/). */
#ifndef FRAGMENT_VS_SCENE_H
#define FRAGMENT_VS_SCENE_H

#include "global.h"

#define BTN_DLEFT       0x0200

#define BTN_DRIGHT      0x0100

typedef struct unk_D_86B0DAE0_000 {
    /* 0x00 */ u16 unk_00;
    /* 0x02 */ u16 unk_02;
    /* 0x04 */ u16 unk_04;
    /* 0x06 */ u16 unk_06;
    /* 0x08 */ u16 unk_08;
    /* 0x0A */ u16 unk_0A;
    /* 0x0C */ u16 unk_0C;
    /* 0x0E */ u16 unk_0E;
    /* 0x10 */ u16 unk_10;
    /* 0x12 */ u16 unk_12;
    /* 0x14 */ u16 unk_14;
    /* 0x16 */ u16 unk_16;
} unk_D_86B0DAE0_000; // size = 0x18

typedef struct unk_D_86B0DAE0 {
    /* 0x00 */ unk_D_86B0DAE0_000 unk_00;
    /* 0x18 */ unk_D_86B0DAE0_000 unk_18;
} unk_D_86B0DAE0; // size = 0x30

// vs_scene.c
s32 Completion_LightAngleCallbackA(s32 arg0, GraphNode* arg1);

#endif // FRAGMENT_VS_SCENE_H
