#ifndef TYPES_STAGE_LOADER_TYPES_H
#define TYPES_STAGE_LOADER_TYPES_H

/* Struct types that were defined identically in each of these files; this is
 * now the one definition they all include:
 * src/stage_loader.c
 * src/stage_loader_2.c
 */

typedef struct unk_D_80068CA0 {
    /* 0x00 */ struct unk_D_80068CA0* next;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s8 unk_08[4];
} unk_D_80068CA0;

#endif /* TYPES_STAGE_LOADER_TYPES_H */
