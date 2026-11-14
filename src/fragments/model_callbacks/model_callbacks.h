/* Declarations for the model_callbacks fragment (src/fragments/model_callbacks/). */
#ifndef FRAGMENT_MODEL_CALLBACKS_H
#define FRAGMENT_MODEL_CALLBACKS_H

#include "global.h"
#include "m2c_macros.h"

typedef struct DisplayListAddresses {
    /* 0x00 */ u32 segments[2];
    /* 0x08 */ u32 textures[1];
} DisplayListAddresses; // size = 0xC

typedef struct DisplayListState {
    /* 0x00 */ char unk00[0x14];
    /* 0x14 */ DisplayListAddresses* addresses;
    /* 0x18 */ Gfx* gfx;
} DisplayListState; // size = 0x1C

extern u8 D_81000000[];

#endif // FRAGMENT_MODEL_CALLBACKS_H
