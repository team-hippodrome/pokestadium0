#ifndef TYPES_89100020_891012A8_TYPES_H
#define TYPES_89100020_891012A8_TYPES_H

/* Struct types that were defined identically in each of these files; this is
 * now the one definition they all include:
 * src/fragments/fragment016_252E10/89100020_891012A8.c
 * src/fragments/fragment016_252E10/89100020_891019E4.c
 */

typedef struct Ctx891012A8 {
    /* 0x0000 */ char unk0000[0x34];
    /* 0x0034 */ s32 right;
    /* 0x0038 */ char unk0038[0x84 - 0x38];
    /* 0x0084 */ s32* widths;
    /* 0x0088 */ char unk0088[0xB15C - 0x88];
    /* 0xB15C */ s32 mode;
    /* 0xB160 */ char unkB160[0xB548 - 0xB160];
    /* 0xB548 */ s32* ranges;
} Ctx891012A8;

typedef struct Entry891012A8 {
    /* 0x00 */ u8 unk00[8];
    /* 0x08 */ u8 species;
    /* 0x09 */ u8 unk09[0x16 - 0x09];
    /* 0x16 */ u16 level;
    /* 0x18 */ u8 unk18[0x2C - 0x18];
    /* 0x2C */ u8 unk2C;
    /* 0x2D */ u8 unk2D;
    /* 0x2E */ u16 stats[5];
    /* 0x38 */ char nickname[0x10];
    /* 0x48 */ char trainer[0x10];
} Entry891012A8;

#endif /* TYPES_89100020_891012A8_TYPES_H */
