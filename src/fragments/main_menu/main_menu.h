/* Declarations for the main_menu fragment (src/fragments/main_menu/). */
#ifndef FRAGMENT_MAIN_MENU_H
#define FRAGMENT_MAIN_MENU_H

#include "global.h"
#include "stdarg.h"
#include "moves.h"
#include "m2c_macros.h"
#include "gb_save.h"
#include "menu.h"
#include "table_view.h"

/* An image drawn with MainMenu_DrawImageWithAlpha: one row of D_88002034 (an item's picture). */
typedef struct MainMenuImage {
    /* 0x00 */ s32 x; // @unverified: added to the item's position in MainMenu_DrawItem
    /* 0x04 */ s32 y;
    /* 0x08 */ s32 width;
    /* 0x0C */ s32 height;
    /* 0x10 */ s32 stride; // @unverified: pixels per row of `pixels` (MainMenu_DrawImageWithAlpha)
    /* 0x14 */ u8* pixels;
} MainMenuImage; // size = 0x18

/* The prompt トーナメントのつづきをする？ (Continue the tournament?) (MainMenu_InitPromptWindow). */
typedef struct MainMenuPromptWindow {
    /* 0x00 */ Window window;
    /* 0x2C */ WindowFrame textFrame; // @unverified: the inner box behind the question text
    /* 0x4C */ Menu menu;
    /* 0x70 */ PointerList itemList;
    /* 0x7C */ u16 itemFlags[3];
    /* 0x82 */ char pad82[0x2];
} MainMenuPromptWindow; // size = 0x84

/* The confirm window of a main menu item: picture, description and two buttons (MainMenu_InitMessageWindow). */
typedef struct MainMenuMessageWindow {
    /* 0x00 */ Window window;
    /* 0x2C */ Color_RGBA8 color; // @unverified: same color as window.frame.color
    /* 0x30 */ char unk30[0x4];
    /* 0x34 */ char* text; // printed at the top right of the window (the item description; swapping it with text2 in play swapped the two texts)
    /* 0x38 */ char* text2; // printed in the lower half next to the buttons (「はいりますか？」, Enter?)
    /* 0x3C */ LabeledButton yesButton; // @unverified: label D_880023C0, cursor 0 returns 1
    /* 0x78 */ LabeledButton noButton; // @unverified: label D_880023C8, cursor 1 returns -1
    /* 0xB4 */ ChoiceCursor choice;
    /* 0xC0 */ MainMenuImage* image; // @unverified: a row of D_88002034, drawn at the top left
} MainMenuMessageWindow; // size = 0xC4

/* The 3x3 grid of main menu items, with its fade in and out (MainMenu_InitItemList). */
typedef struct MainMenuItemList {
    /* 0x000 */ s32 fadeState; // @unverified: 0 fading in, 1-2 shown, 3 fading out, 4 gone (MainMenu_StepItemFade)
    /* 0x004 */ s32 fadeTimer; // @unverified: counts up; 0xD starts the fade out
    /* 0x008 */ GridMenu menu;
    /* 0x030 */ u8 itemBuffer[9][0x30];
    /* 0x1E0 */ ByteMatrix items;
    /* 0x1F0 */ u16 itemFlags[9]; // @unverified: bit 0 = disabled; set for the items the save cannot use
    /* 0x202 */ char pad202[0x2];
} MainMenuItemList; // size = 0x204

/* A window with one line of text (MainMenu_InitTextWindow): the GBのカートリッジがない (no GB cartridge) warning. */
typedef struct MainMenuTextWindow {
    /* 0x00 */ Window window;
    /* 0x2C */ char unk2C[0x4];
    /* 0x30 */ char* text;
} MainMenuTextWindow; // size = 0x34

/* The main menu screen, allocated into D_88002B20 by MainMenu_Init. */
typedef struct MainMenuScreen {
    /* 0x000 */ s32 state; // 1 prompt, 2 item grid, 3 item confirm window; in play 2 on the grid, 3 after A on バトル (Battle), 2 again after B
    /* 0x004 */ s32 nextState; // 4 = leave with `result` once the grid has faded (set by はい in play); 2 = back to the grid
    /* 0x008 */ s32 result; // returned by MainMenu_UpdateScreen; from MainMenu_LoadSelectedFragment (0x8040 after はい on バトル in play)
    /* 0x00C */ s32 mode; // arg1 of MainMenu_InitScreen; above 0 shows the text window (4 with no GB cart; poking 0 hid the 「GBのカートリッジがない」 window)
    /* 0x010 */ char unk10[0x1C];
    /* 0x02C */ MainMenuItemList itemList;
    /* 0x230 */ char unk230[0x4];
    /* 0x234 */ MainMenuMessageWindow messageWindow;
    /* 0x2F8 */ MainMenuTextWindow textWindow;
    /* 0x32C */ MainMenuPromptWindow promptWindow;
} MainMenuScreen; // size = 0x3B0

extern u8 D_88000000[];

// main_menu.c
void func_88000FE0(void);
void func_8800075C(void);

#endif // FRAGMENT_MAIN_MENU_H
