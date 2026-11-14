/* Declarations for the free_battle_setup fragment (src/fragments/free_battle_setup/). */
#ifndef FRAGMENT_FREE_BATTLE_SETUP_H
#define FRAGMENT_FREE_BATTLE_SETUP_H

#include "global.h"
#include "gb_save.h"
#include "menu.h"

/* One battle mode card of the battle mode window (D_8200752C rows). */
typedef struct FreeBattleModeEntry {
    /* 0x0 */ s32 unk0;
    /* 0x4 */ char* text; // @unverified: description printed under the cards for the cursor card
    /* 0x8 */ s32 unk8;
} FreeBattleModeEntry; // size = 0xC

/* The battle mode window: a 2x1 grid of cards and the description of the cursor card
 * (FreeBattle_InitBattleModeWindow). */
typedef struct FreeBattleModeWindow {
    /* 0x00 */ Window window;
    /* 0x2C */ GridMenu menu;
    /* 0x54 */ ByteMatrix items; // rows in `modes`
    /* 0x64 */ u16 itemFlags[2];
    /* 0x68 */ FreeBattleModeEntry* modes;
} FreeBattleModeWindow; // size = 0x6C

/* The cup select window (FreeBattle_InitCupSelect): up to four cups. */
typedef struct FreeBattleCupWindow {
    /* 0x00 */ Window window;
    /* 0x2C */ Menu menu;
    /* 0x50 */ ByteMatrix items; // 8-byte rows from D_820091C4
    /* 0x60 */ u16 itemFlags[4]; // @unverified: 0x100 for the cups below arg3, 1 (disabled) for those past the next one
} FreeBattleCupWindow; // size = 0x68

/* A message window with one number (FreeBattle_InitDuplicateWarning). */
typedef struct FreeBattleDuplicateWarning {
    /* 0x00 */ Window window;
    /* 0x2C */ char unk2C[0x20];
    /* 0x4C */ s32 value; // @unverified: printed with the format D_8200A0B0
} FreeBattleDuplicateWarning; // size = 0x50

/* A yes/no question asked of one controller (FreeBattle_InitLevelSumWarning). */
typedef struct FreeBattleLevelSumWarning {
    /* 0x00 */ Window window;
    /* 0x2C */ LabeledButton yesButton; // @unverified: label D_8200A188
    /* 0x68 */ LabeledButton noButton; // @unverified: label D_8200A190
    /* 0xA4 */ ChoiceCursor choice;
    /* 0xB0 */ Controller* controller; // @unverified: the player asked; read by func_8002BC14
} FreeBattleLevelSumWarning; // size = 0xB4

/* A yes/no question with a number, asked of one controller (FreeBattle_InitShortageWarning). */
typedef struct FreeBattleShortageWarning {
    /* 0x00 */ Window window;
    /* 0x2C */ LabeledButton yesButton; // @unverified: label D_8200A114
    /* 0x68 */ LabeledButton noButton; // @unverified: label D_8200A11C
    /* 0xA4 */ ChoiceCursor choice;
    /* 0xB0 */ s32 count; // @unverified: printed twice with the format D_8200A124
    /* 0xB4 */ Controller* controller; // @unverified: the player asked; read by func_8002BC14
} FreeBattleShortageWarning; // size = 0xB8

/* The confirm window of the rental and entry screens: two or three buttons (FreeBattle_InitRentalConfirm). */
typedef struct FreeBattleRentalConfirm {
    /* 0x00 */ Window window;
    /* 0x2C */ LabeledButton buttons[3]; // @unverified: labels D_8200A1EC, D_8200A1F4, D_8200A1FC; the third only with hasThirdButton
    /* 0xE0 */ ChoiceCursor choice;
    /* 0xEC */ s32 hasThirdButton; // @unverified: arg3 of FreeBattle_InitRentalConfirm; choice.count is 3 with it, else 2
} FreeBattleRentalConfirm; // size = 0xF0

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

/* The opponent select window with partners, 「あいてをせんたく」 (Choose your opponent) with two
 * menus (func_82006C74): your side (1P, 1P&2P, 1P&3P, 1P&4P), then the other side (2P, 3P, 4P,
 * 2P&3P, 2P&4P, 3P&4P, COM). */
typedef struct FreeBattleTeamOpponentWindow {
    /* 0x00 */ u32 focus; // @unverified: 1 while the side menu has the cursor, 0 for the opponent menu (func_82007030)
    /* 0x04 */ Window window;
    /* 0x30 */ PointerList sideItemList; // D_82009190
    /* 0x3C */ PointerList opponentItemList; // D_820091A0
    /* 0x48 */ Menu sideMenu;
    /* 0x6C */ Menu opponentMenu;
    /* 0x90 */ u16 sideItemFlags[4];
    /* 0x98 */ u16 opponentItemFlags[7];
    /* 0xA6 */ char padA6[0x2];
    /* 0xA8 */ u32 players[4]; // @unverified: [0] [1] your side, [2] [3] the other side: 1-4 = 1P-4P, 5 = COM, 0 = nobody
    /* 0xB8 */ u32 playerCount; // @unverified: players in use, 2 to 4
    /* 0xBC */ s32 controllerMask; // @unverified: as FreeBattleOpponentWindow.controllerMask; clear bits disable the matching options
    /* 0xC0 */ char unkC0[0x4];
    /* 0xC4 */ s32 unk_C4; // passed to FreeBattle_DrawControllerPanel as `active`
} FreeBattleTeamOpponentWindow; // size = 0xC8

/* One of the two configurations of the Pokémon grid window (D_820091EC). */
typedef struct FreeBattleMonGridConfig {
    /* 0x0 */ char* title; // @unverified: copied to window.title
    /* 0x4 */ BattleMon* mons; // @unverified: row buffer for FreeBattleMonGridWindow.mons; arg4/arg5 of func_82007C30
    /* 0x8 */ s32 count; // @unverified: rows in mons
} FreeBattleMonGridConfig; // size = 0xC

/* A 7x6 grid of Pokémon with their names and icons (func_82007C30, func_82007D94). */
typedef struct FreeBattleMonGridWindow {
    /* 0x00 */ Window window;
    /* 0x2C */ char unk2C[0xA0];
    /* 0xCC */ ByteMatrix mons; // rows of BattleMon; the cell shows nickname and icon
    /* 0xDC */ PokeIconRenderer* icons; // @unverified: icon set built by func_80018168/func_80018234, drawn with PokeIcon_GetImage
} FreeBattleMonGridWindow; // size >= 0xE0, the screen's layout after it is not established

#endif // FRAGMENT_FREE_BATTLE_SETUP_H
