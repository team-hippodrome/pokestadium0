#ifndef TYPES_GB_TOWER_EMULATOR_86CB0_TYPES_2_H
#define TYPES_GB_TOWER_EMULATOR_86CB0_TYPES_2_H

/* Struct types that were defined identically in each of these files; this is
 * now the one definition they all include:
 * src/fragments/fragment000_80C00/gb_tower_emulator_86CB0.c
 * src/fragments/fragment000_80C00/gb_tower_emulator_86CB0_81114B54.c
 */

typedef struct Item8111539C {
    /* 0x00 */ u32 active : 1;
    /* 0x00 */ u32 unk00 : 31;
    /* 0x04 */ char unk04[0x48];
    /* 0x4C */ void* owners[2];
} Item8111539C;

#endif /* TYPES_GB_TOWER_EMULATOR_86CB0_TYPES_2_H */
