#ifndef TYPES_33FE0_TYPES_H
#define TYPES_33FE0_TYPES_H

/* Struct types that were defined identically in each of these files; this is
 * now the one definition they all include:
 * src/33FE0.c
 * src/3D140.c
 * src/3D140_2.c
 */

typedef struct AMDMABuffer {
    /* 0x00 */ ALLink node;
    /* 0x08 */ u32 startAddr;
    /* 0x0C */ u32 lastFrame;
    /* 0x10 */ char* ptr;
} AMDMABuffer;

typedef struct AMDMAState {
    /* 0x00 */ u8 initialized;
    /* 0x04 */ AMDMABuffer* firstUsed;
    /* 0x08 */ AMDMABuffer* firstFree;
} AMDMAState;

typedef struct unk_D_80078548 {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 unk_01;
} unk_D_80078548;

#endif /* TYPES_33FE0_TYPES_H */
