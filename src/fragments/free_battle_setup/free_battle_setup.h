/* Declarations for the free_battle_setup fragment (src/fragments/free_battle_setup/). */
#ifndef FRAGMENT_FREE_BATTLE_SETUP_H
#define FRAGMENT_FREE_BATTLE_SETUP_H

#include "global.h"

/* Struct types that were defined identically in each of these files; this is
 * now the one definition they all include:
 * src/fragments/fragment007_166580.c
 * src/fragments/fragment007_166580_3.c
 */

typedef struct Entry82000058 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ u8 unk_04[0x50];
} Entry82000058; // size = 0x54

/* Struct types that were defined identically in each of these files; this is
 * now the one definition they all include:
 * src/fragments/fragment007_166580.c
 * src/fragments/fragment007_166580_4.c
 */

typedef struct Mon82000258 {
    /* 0x00 */ char unk00[0x28];
    /* 0x28 */ u8 level;
    /* 0x29 */ char unk29[0x2B];
} Mon82000258; // size = 0x54

#endif // FRAGMENT_FREE_BATTLE_SETUP_H
