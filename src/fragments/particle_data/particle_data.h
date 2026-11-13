/* Declarations for the particle_data fragment (src/fragments/particle_data/). */
#ifndef FRAGMENT_PARTICLE_DATA_H
#define FRAGMENT_PARTICLE_DATA_H

#include "global.h"

typedef struct DisplayListAddresses {
    /* 0x00 */ u32 segments[2];
    /* 0x08 */ u32 textures[1];
} DisplayListAddresses; // size = 0xC

typedef struct DisplayListState {
    /* 0x00 */ char unk00[0x14];
    /* 0x14 */ DisplayListAddresses* addresses;
    /* 0x18 */ Gfx* gfx;
} DisplayListState; // size = 0x1C

#endif // FRAGMENT_PARTICLE_DATA_H
