#ifndef TYPES_GB_TOWER_EMULATOR_86CB0_TYPES_H
#define TYPES_GB_TOWER_EMULATOR_86CB0_TYPES_H

/* Struct types that were defined identically in each of these files; this is
 * now the one definition they all include:
 * src/fragments/fragment000_80C00/gb_tower_emulator_86CB0.c
 * src/fragments/fragment000_80C00/gb_tower_emulator_86CB0_81113A44.c
 */

typedef struct AudioStreamFlags {
    u8 pad0 : 4;
    u8 active : 1;
    u8 pad1 : 3;
} AudioStreamFlags;

#endif /* TYPES_GB_TOWER_EMULATOR_86CB0_TYPES_H */
