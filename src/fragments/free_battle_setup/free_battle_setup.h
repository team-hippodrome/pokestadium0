/* Declarations for the free_battle_setup fragment (src/fragments/free_battle_setup/). */
#ifndef FRAGMENT_FREE_BATTLE_SETUP_H
#define FRAGMENT_FREE_BATTLE_SETUP_H

#include "global.h"
#include "gb_save.h"
#include "menu.h"

/* A window with a one-column menu (FreeBattle_InitMenuWindow, FreeBattle_InitPopupMenu). */
typedef struct FreeBattleMenuWindow {
    /* 0x00 */ Window window;
    /* 0x2C */ Menu menu;
    /* 0x50 */ PointerList itemList; // the item strings: フリーバトル, L 1～30 バトル, L50～55 バトル
    /* 0x5C */ u16 itemFlags[16]; // FreeBattle_InitMenuWindow only; the popup takes its flags from the caller
    /* 0x7C */ char** descriptions; // printed under the list for the cursor row: 「４０しゅるいの　ポケモンの　なかから」... for フリーバトル
    /* 0x80 */ s32 descriptionLines; // 3 in the rule window; the description box is 0x1C pixels per line
} FreeBattleMenuWindow; // size = 0x84

/* The opponent select window (FreeBattle_InitOpponentSelect): a menu of four opponents next to
 * the controller panel. */
typedef struct FreeBattleOpponentWindow {
    /* 0x00 */ Window window;
    /* 0x2C */ PointerList itemList;
    /* 0x38 */ Menu menu;
    /* 0x5C */ u16 itemFlags[4]; // 2P, 3P, 4P, COM; 1 1 1 0 (2P-4P greyed out) with one controller
    /* 0x64 */ s32 choice; // 2 + the row picked with A: 5 for COM
    /* 0x68 */ s32 controllerMask; // controllers plugged in, bit 1 << n for controller n + 1: 1 with only controller 1
    /* 0x6C */ char unk6C[0x4];
    /* 0x70 */ s32 unk_70; // passed to FreeBattle_DrawControllerPanel as `active`
} FreeBattleOpponentWindow; // size = 0x74

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
