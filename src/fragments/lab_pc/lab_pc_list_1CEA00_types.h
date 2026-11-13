#ifndef TYPES_LAB_PC_LIST_1CEA00_TYPES_H
#define TYPES_LAB_PC_LIST_1CEA00_TYPES_H

/* Struct types that were defined identically in each of these files; this is
 * now the one definition they all include:
 * src/fragments/fragment015_238BD0/lab_pc_list_1CEA00.c
 * src/fragments/fragment015_238BD0/lab_pc_list_1CEA00_8900379C.c
 * src/fragments/fragment015_238BD0/lab_pc_list_1CEA00_89003880.c
 */

typedef struct Rgba89000D50 {
    /* 0x0 */ u8 r, g, b, a;
} Rgba89000D50; // size = 0x4

typedef struct ColorPair890017FC {
    /* 0x0 */ Color_RGBA8 prim;
    /* 0x4 */ Color_RGBA8 env;
} ColorPair890017FC;

typedef struct Col89002C10 { u8 r, g, b, a; } Col89002C10;

#endif /* TYPES_LAB_PC_LIST_1CEA00_TYPES_H */
