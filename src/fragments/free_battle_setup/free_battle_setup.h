/* Declarations for the free_battle_setup fragment (src/fragments/free_battle_setup/). */
#ifndef FRAGMENT_FREE_BATTLE_SETUP_H
#define FRAGMENT_FREE_BATTLE_SETUP_H

#include "global.h"
#include "gb_save.h"
#include "menu.h"

/* One battle mode card of the battle mode window (D_8200752C rows). */
typedef struct FreeBattleModeEntry {
    /* 0x0 */ s32 unk0;
    /* 0x4 */ char* text; // description printed under the cards for the cursor card; swapping the two entries' texts showed the トーナメント (Tournament) text under フリーバトル (Free Battle)
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
    /* 0x2C */ LabeledButton buttons[3]; // はい (Yes), いいえ (No), レンタル (Rental) under 「このデータでエントリーします。」 (Enter with this data) in play; the third only with hasThirdButton
    /* 0xE0 */ ChoiceCursor choice;
    /* 0xEC */ s32 hasThirdButton; // @unverified: arg3 of FreeBattle_InitRentalConfirm; choice.count is 3 with it, else 2 (1 and 3 with the レンタル button in play; poking 0 later did not hide it)
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
} FreeBattleMonGridWindow; // size = 0xE0 (FreeBattleScreen.monGridWindow is followed by connectedControllerMask)

/* The Free Battle setup screen: its state machine and every window it switches between
   (FreeBattle_SetScreenState). Only the part after 0x4318 is laid out here; the entry screen
   code in free_battle_setup_4.c still reaches 0x10-0x4318 through raw offsets. */
typedef struct FreeBattleScreen {
    /* 0x0000 */ s32 state; // @unverified: FreeBattle_SetScreenState's arg1 when it opens a window
    /* 0x0004 */ s32 pendingState; // @unverified: arg1 when the window is opened on top (arg2 & 1), else 0
    /* 0x0008 */ s8* view; // @unverified: window that is shown; set to state 7 (+0x24) when another opens on top
    /* 0x000C */ s8* nextView; // @unverified: window opened on top of view (arg2 & 1)
    /* 0x0010 */ char unk0010[0x431C];
    /* 0x432C */ s32 unk_432C;
    /* 0x4330 */ s32 unk_4330;
    /* 0x4334 */ s32 unk_4334;
    /* 0x4338 */ s32 unk_4338;
    /* 0x433C */ s32 unk_433C;
    /* 0x4340 */ char unk4340[0x18];
    /* 0x4358 */ s32 unk_4358;
    /* 0x435C */ s32 unk_435C;
    /* 0x4360 */ s32 unk_4360;
    /* 0x4364 */ s32 unk_4364;
    /* 0x4368 */ char unk4368[0x8];
    /* 0x4370 */ s32 unk_4370;
    /* 0x4374 */ s32 unk_4374;
    /* 0x4378 */ FreeBattleModeWindow modeWindow; // @unverified: state 1, FreeBattle_InitBattleModeWindow
    /* 0x43E4 */ MenuWindow menuWindow; // @unverified: states 2 and 3, FreeBattle_InitMenuWindow
    /* 0x4468 */ MenuWindow ruleMenuWindow; // @unverified: states 4, 7 and 8, FreeBattle_InitMenuWindow
    /* 0x44EC */ FreeBattleCupWindow cupWindow; // @unverified: state 9, FreeBattle_InitCupSelect
    /* 0x4554 */ FreeBattleOpponentWindow opponentWindow; // @unverified: state 5, FreeBattle_InitOpponentSelect
    /* 0x45C8 */ char unk45C8[0xDC];
    /* 0x46A4 */ char entryScreen[0x778]; // @unverified: state 10's view, set up by FreeBattle_InitEntryScreen
    /* 0x4E1C */ char textBox[0x34]; // @unverified: state 11, BlinkingTextBox_Init
    /* 0x4E50 */ char popupMenu[0x5C]; // @unverified: state 12, FreeBattle_InitPopupMenu
    /* 0x4EAC */ char popupMenu2[0x5C]; // @unverified: state 13, FreeBattle_InitPopupMenu
    /* 0x4F08 */ char popupMenuText[0x14]; // @unverified: text buffer passed with popupMenu
    /* 0x4F1C */ char popupMenu2Text[0x14]; // @unverified: text buffer passed with popupMenu2
    /* 0x4F30 */ FreeBattleMonGridWindow monGridWindow; // @unverified: state 14, func_82007C30
    /* 0x5010 */ s32 connectedControllerMask; // @unverified: func_8000B2E8 (the controller-present mask controller.c builds gControllers from)
    /* 0x5014 */ s32 connectedControllerCount; // @unverified: bits set in connectedControllerMask
    /* 0x5018 */ s32 gbSaveReadyMask; // @unverified: bit i set when GbSave_GetSaveState(i) is 0
    /* 0x501C */ s32 unk_501C;
} FreeBattleScreen; // size = 0x5020

#endif // FRAGMENT_FREE_BATTLE_SETUP_H
