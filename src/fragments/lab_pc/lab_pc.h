/* Declarations for the lab_pc fragment (src/fragments/lab_pc/). */
#ifndef FRAGMENT_LAB_PC_H
#define FRAGMENT_LAB_PC_H

#include "global.h"
#include "controller.h"
#include "game_state.h"
#include "gb_save.h"
#include "memory.h"
#include "menu.h"
#include "table_view.h"

struct unk_func_8821421C_038_04C_000;

struct unk_func_8820B12C_02C;

struct unk_func_8821421C_034;

struct unk_func_8821421C_038;

struct unk_func_8821421C_03C;

struct LabItemSaveSlot;

struct unk_func_8820E99C;

struct unk_func_8821421C_02C;


/* The ×count selector of the Lab item screens (LabItem_InitCountSelector), with a text box for a count
 * over the limit. */
typedef struct LabItemCountSelector {
    /* 0x00 */ s32 state; // @unverified: 1 while the text box D_89018474 is up
    /* 0x04 */ Window window;
    /* 0x30 */ s32 limit; // @unverified: arg4; a value above it opens the text box, then is set back to it
    /* 0x34 */ DigitSelector count;
    /* 0x48 */ TextBox textBox; // @unverified: typed from the function it is passed to
} LabItemCountSelector; // size = 0x80

/* A yes/no question in the Lab item screens (LabItem_InitConfirmWindow). */
typedef struct LabItemConfirmWindow {
    /* 0x00 */ Window window;
    /* 0x2C */ char unk2C[0x4];
    /* 0x30 */ char* text; // @unverified: printed at the top left (arg4)
    /* 0x34 */ LabeledButton yesButton; // @unverified: label D_89018460
    /* 0x70 */ LabeledButton noButton; // @unverified: label D_89018468
    /* 0xAC */ ChoiceCursor choice;
} LabItemConfirmWindow; // size = 0xB8

/* One box of the Lab PC box screens (せいとん): its Pokémon and how many are stored. PcBox_ReadDeck fills
 * it from a deck, LabPC_WriteBoxEntries writes it back. */
typedef struct PcBoxStorage {
    /* 0x000 */ BattleMon mons[30]; // @unverified: typed from the function it is passed to
    /* 0x960 */ s32 count; // shown as N/30 beside the box name: 1 for GB box 1 holding ハナ
} PcBoxStorage; // size = 0x964

/* A row of the box tables of the box screens: a box and whether it was changed. */
typedef struct LabPCBoxEntry {
    /* 0x0 */ PcBoxStorage* box; // the PcBoxStorage of the row: gbBoxEntries[i].box = &gbBoxes[i] (stride 0x964)
    /* 0x4 */ s32 dirty; // set by the swaps: ボックスをならべかえる of GB box 1 and 2 set it on both; func_890070BC writes back the boxes that have it, PcBox_HasUnsavedChanges asks to save
} LabPCBoxEntry; // size = 0x8

/* The ほんとうにいいの？ はい/いいえ window of the box screens with the Pokémon's stats and moves
 * (PcBox_InitConfirmWindow, PcBox_DrawMonStatusWindow). Without a title it only shows the stats. */
typedef struct PcBoxConfirmWindow {
    /* 0x00 */ Window window; // 430x292 at (105, 125), the Pokémon status window of ボックスのなかをみる
    /* 0x2C */ LabeledButton yesButton; // @unverified: label D_89018E60
    /* 0x68 */ LabeledButton noButton; // @unverified: label D_89018E68
    /* 0xA4 */ ChoiceCursor choice; // count 2, the yes/no cursor
    /* 0xB0 */ BattleMon* mon; // the Pokémon shown: &gbBoxes[0].mons[0] (ハナ) after A on it in GB box 1
    /* 0xB4 */ char* title; // question printed above the buttons; NULL hides the buttons (NULL in the status view, no buttons drawn)
    /* 0xB8 */ s32 animLoaded; // 1 once func_80019008 loaded the Pokémon's image into anim (the ピカチュウ picture was up)
    /* 0xBC */ u16* anim; // renderer of the Pokémon picture from func_80018F2C; bits 1 and 2 of its flags cleared while a question is up
} PcBoxConfirmWindow; // size = 0xC0

/* The window of one box's Pokémon in the box screens (func_8900806C, PcBox_DrawList). */
typedef struct PcBoxListWindow {
    /* 0x00 */ Window window; // 552x342 at (44, 95), the ＧＢのボックス１ grid
    /* 0x2C */ GridMenu menu; // the 6x5 grid of the box: columns 6, cells 90x66
    /* 0x54 */ u16 itemFlags[30]; // @unverified: itemFlags of menu
    /* 0x90 */ s32 iconRenderer; // @unverified: PokeIconRenderer for the icons (func_8001833C, func_800189C0)
    /* 0x94 */ ByteMatrix mons; // rows over the box's mons, 0x50 bytes each: rows = gbBoxes[0].mons, count 1
} PcBoxListWindow; // size = 0xA4

/* The ボックスのそうさ window: six operation buttons and the GB and 64 box lists
 * (PcBox_InitOperationWindow, PcBox_UpdateOperationWindow). */
typedef struct PcBoxOperationWindow {
    /* 0x000 */ s32 state; // 1 = picking an operation, 2-6 = picking boxes, 7 = text box up (PcBox_UpdateOperationWindow); seen 1, 2, 5, 6
    /* 0x004 */ Window window; // the ボックスのそうさ window, 564x370 at (38, 83)
    /* 0x030 */ WindowFrame footerFrame; // the bottom strip with the operation name, 552x64 at (44, 383)
    /* 0x050 */ ImageButton backButton; // operation 5 「メニューへもどる」 (back to the menu), the top button
    /* 0x07C */ ImageButton moveToGbButton; // operation 1 「ＧＢへボックスをいどうする」 (move a box to the GB), third button
    /* 0x0A8 */ ImageButton moveTo64Button; // operation 0 「６４へボックスをいどうする」 (move a box to the 64), second button, highlighted at open
    /* 0x0D4 */ ImageButton reorderButton; // operation 2 「ボックスをならべかえる」 (reorder the boxes): swapped GB box 1 and 2 in play
    /* 0x100 */ ImageButton exchangeButton; // operation 3 「ボックスをいれかえる」 (exchange boxes), fifth button
    /* 0x12C */ ImageButton viewButton; // operation 4 「ボックスのなかをみる」 (look inside a box), the bottom button
    /* 0x158 */ ChoiceCursor operationCursor; // cursor = the operation 0-5 (titles D_8900A924), count = 6; D-Up from 0 went to 5, D-Down from 5 to 0 .. 4
    /* 0x164 */ ChoiceCursor boxCursor; // operation 4: count 12, 0-7 = the GB boxes, 8-11 the 64 boxes; 0 opened ＧＢのボックス１
    /* 0x170 */ Menu gbBoxMenu; // the GB box list (PcBox_DrawBoxName); items = gbBoxTable, D-Down moved its cursor to 1 while reordering
    /* 0x194 */ Menu stadiumBoxMenu; // the 64 box list (PcBox_DrawBoxCount); items = stadiumBoxTable
    /* 0x1B8 */ u16 gbBoxFlags[8]; // @unverified: itemFlags of gbBoxMenu
    /* 0x1C8 */ u16 stadiumBoxFlags[8]; // @unverified: itemFlags of stadiumBoxMenu
    /* 0x1D8 */ Menu* sourceMenu; // the box list picked first (PcBox_SetActiveLists): gbBoxMenu for ボックスをならべかえる
    /* 0x1DC */ Menu* targetMenu; // @unverified: the box list picked second (PcBox_SetActiveLists)
    /* 0x1E0 */ TextBox textBox; // @unverified: typed from the function it is passed to
    /* 0x218 */ s32 swapIndex; // operation 2: the first box picked, swapped with the second (1 after picking ボックス２)
} PcBoxOperationWindow; // size = 0x21C

/* The ボックスのそうさ screen (PcBox_Init, PcBox_UpdateScreen, PcBox_DrawScreen). */
typedef struct PcBoxScreen {
    /* 0x0000 */ s32 state; // 1 = operation window, 2 = box list, 3 = mon status, 4 = save prompt (PcBox_UpdateScreen); 1, 2, 3 seen in ボックスのなかをみる
    /* 0x0004 */ PcBoxOperationWindow operationWindow; // the ボックスのそうさ window
    /* 0x0220 */ SavePrompt savePrompt; // @unverified: typed from the function it is passed to
    /* 0x0284 */ PcBoxListWindow listWindow; // the box grid at state 2
    /* 0x0328 */ PcBoxConfirmWindow statusWindow; // the Pokémon status window at state 3
    /* 0x03E8 */ PcBoxStorage gbBoxes[8]; // read from deck 0x21 of the GB cart (D_89019108): gbBoxes[0].count 1 with ハナ, the others 0
    /* 0x4F08 */ PcBoxStorage stadiumBoxes[4]; // read from deck 0x11, the 64 boxes: stadiumBoxes[0].count 1 (64 box 1 shows 1/30)
    /* 0x7498 */ LabPCBoxEntry gbBoxEntries[8]; // {&gbBoxes[i], dirty}, the rows of gbBoxTable
    /* 0x74D8 */ LabPCBoxEntry stadiumBoxEntries[4]; // {&stadiumBoxes[i], dirty}, the rows of stadiumBoxTable
    /* 0x74F8 */ ByteMatrix gbBoxTable; // rows = gbBoxEntries (count 8, rowSize 8); items of operationWindow.gbBoxMenu
    /* 0x7508 */ ByteMatrix stadiumBoxTable; // rows = stadiumBoxEntries (count 4); items of operationWindow.stadiumBoxMenu
    /* 0x7518 */ s8* iconFramebuffers; // @unverified: PokeIcon_AllocFramebuffers
    /* 0x751C */ u16* monRenderer; // @unverified: func_80018F2C; the anim of statusWindow
    /* 0x7520 */ s32 iconRenderer; // @unverified: func_80017FDC; the icons of listWindow
} PcBoxScreen; // size = 0x7524

/* A box picker of the ポケモンを いどうする screen (PcSort_InitMenuWindow) over the box names D_8900A758.
 * LabItemMenuWindow is the same with room for 4 rows. */
typedef struct PcSortMenuWindow {
    /* 0x00 */ Window window; // @unverified: typed from the function it is passed to
    /* 0x2C */ Menu menu; // @unverified: typed from the function it is passed to
    /* 0x50 */ PointerList items; // @unverified: func_80027804 over the 13 names of D_8900A758
    /* 0x5C */ u16 itemFlags[13]; // @unverified: 0x100 = empty box, 0x200 = party of one, 0x400 = full box (PcSort_Disable*)
    /* 0x76 */ char pad76[0x2];
} PcSortMenuWindow; // size = 0x78

/* A pop-up list of the Lab item screens (LabItem_InitMenuWindow); PcSortMenuWindow with 4 rows. */
typedef struct LabItemMenuWindow {
    /* 0x00 */ Window window; // @unverified: typed from the function it is passed to
    /* 0x2C */ Menu menu; // @unverified: typed from the function it is passed to
    /* 0x50 */ PointerList items; // @unverified: func_80027804 over the names (LabItem_InitMenuWindow arg3)
    /* 0x5C */ u16 itemFlags[4]; // @unverified: typed from the function it is passed to
} LabItemMenuWindow; // size = 0x64

/* A Pokémon list of the ポケモンを いどうする screen (PcSort_InitMonList, PcSort_DrawMonList). */
typedef struct PcSortMonList {
    /* 0x00 */ ScrollList list; // @unverified: items = the box's ByteMatrix of BattleMon rows
    /* 0x44 */ u16 itemFlags[30]; // @unverified: typed from the function it is passed to
    /* 0x80 */ s32 x; // @unverified: typed from the function it is passed to
    /* 0x84 */ s32 y; // @unverified: typed from the function it is passed to
} PcSortMonList; // size = 0x88

/* An item list of the Lab item screens (LabItem_InitItemList, LabItem_DrawItemList). */
typedef struct LabItemList {
    /* 0x000 */ ScrollList list; // items = an item table with 2-byte rows (LabItem_DrawItemCountRow); D-Down moved list.cursor
    /* 0x044 */ u16 itemFlags[100]; // @unverified: typed from the function it is passed to
    /* 0x10C */ s32 x; // left of the list: 50 (left list) and 354 (right list)
    /* 0x110 */ s32 y; // top of the list: 123
} LabItemList; // size = 0x114

/* One of the 4 item saves of the ６４の カセット box (deck 0x12), listed in the データをけす window. */
typedef struct LabItemSaveSlot {
    /* 0x00 */ s32 present; // @unverified: Deck_IsSaveEntryPresent (LabItem_LoadGamePakBoxSlots)
    /* 0x04 */ s32 trainerId; // @unverified: Deck_GetSaveEntryTrainerId & 0xFFFF; printed as ID No/%05d
    /* 0x08 */ char trainerName[0xC]; // @unverified: Deck_GetSaveEntryName; printed as なまえ/%s (name)
} LabItemSaveSlot; // size = 0x14

/* The データをけす (delete data) window: 「セーブは４つぶんだけです けすデータをえらんでください」 (only 4 saves
 * fit, pick the data to delete) over the 4 LabItemSaveSlot rows (LabItem_InitDeleteDataWindow). */
typedef struct LabItemDeleteDataWindow {
    /* 0x00 */ Window window; // @unverified: typed from the function it is passed to
    /* 0x2C */ WindowFrame footerFrame; // @unverified: frame of the bottom strip with the message D_89018688
    /* 0x4C */ Menu menu; // @unverified: rows drawn by LabItem_DrawTrainerInfo
    /* 0x70 */ ByteMatrix slotTable; // @unverified: rows = the 4 LabItemSaveSlot, items of menu
    /* 0x80 */ u16 itemFlags[4]; // @unverified: itemFlags of menu
} LabItemDeleteDataWindow; // size = 0x88

/* The window of one item save picked in the データをけす window: three operation buttons and its item list
 * (func_89002E58, func_890032E4, func_8900352C). */
typedef struct LabItemSaveDataWindow {
    /* 0x000 */ s32 state; // @unverified: 1 = picking an operation, 2 = scrolling itemList (func_8900352C)
    /* 0x004 */ Window window; // @unverified: typed from the function it is passed to
    /* 0x030 */ WindowFrame footerFrame; // @unverified: frame of the bottom strip with the help line (func_8900323C)
    /* 0x050 */ ImageButton backButton; // @unverified: operation 2 「データせんたくにもどる」 (back to picking data)
    /* 0x07C */ ImageButton viewItemsButton; // @unverified: operation 1 「どうぐをかくにんする」 (check the items)
    /* 0x0A8 */ ImageButton discardButton; // @unverified: operation 0 「このデータをすてる」 (discard this data)
    /* 0x0D4 */ ChoiceCursor operationCursor; // @unverified: cursor = the operation 0-2 (titles D_8900A6CC), count = 3
    /* 0x0E0 */ LabItemList itemList; // @unverified: the save's items (func_89002E58 arg4)
    /* 0x1F4 */ LabItemSaveSlot* slot; // @unverified: name and ID drawn by func_890030C8
} LabItemSaveDataWindow; // size = 0x1F8

/* The どうぐのせいり (organize items) window: four operation buttons, two box pickers and two item lists
 * side by side (LabItem_InitOrganizeWindow, LabItem_UpdateOrganizeWindow, LabItem_DrawOrganizeWindow).
 * The boxes are 0 = てもちの どうぐ (bag), 1 = the PC (name from D_890190F0), 2 = ６４の カセット. */
typedef struct LabItemOrganizeWindow {
    /* 0x000 */ s32 state; // 1 = picking an operation, 2/3 = box pickers, 4-7 = item lists, 8 = count selector, 9-0xC = text box up; seen 1, 2, 3, 4, 5, 7, 8 in play
    /* 0x004 */ Window window; // @unverified: typed from the function it is passed to
    /* 0x030 */ WindowFrame footerFrame; // the bottom strip with the help line, 552x56 at (44, 391)
    /* 0x050 */ ImageButton backButton; // operation 3 「メニューへもどる」 (back to the menu), the top (house) button
    /* 0x07C */ ImageButton moveButton; // operation 0 「どうぐをいどうする」 (move items), highlighted at open
    /* 0x0A8 */ ImageButton reorderButton; // operation 1 「どうぐをならべかえる」 (reorder items); A on it emptied the right list for reordering
    /* 0x0D4 */ ImageButton exchangeButton; // @unverified: operation 2 「どうぐをいれかえる」 (exchange items)
    /* 0x100 */ ChoiceCursor operationCursor; // cursor = the operation 0-3 (titles D_8900A650), count = 4; D-Up from 0 went to 3 (メニューへもどる)
    /* 0x10C */ LabItemMenuWindow sourceBoxWindow; // state 2, sets leftBox: 「どこからいどうする？」 over てもちの どうぐ, サトシのパソコン, ６４の カセット
    /* 0x170 */ LabItemMenuWindow targetBoxWindow; // @unverified: state 3, sets rightBox (「どこへいどうする？」)
    /* 0x1D4 */ s32 leftBox; // the box shown in leftList: 0 (てもちの どうぐ)
    /* 0x1D8 */ s32 rightBox; // the box shown in rightList: 1 (サトシのパソコン); -1 while it shows reorderView (どうぐをならべかえる)
    /* 0x1DC */ char** boxNames; // @unverified: D_8900A5F4, the names of the 3 boxes
    /* 0x1E0 */ s32 boxCount; // 3, the row count of the box pickers
    /* 0x1E4 */ LabItemList leftList; // the left item list at (50, 123); D-Down moved its cursor
    /* 0x2F8 */ LabItemList rightList; // the right item list at (354, 123)
    /* 0x40C */ s32 swapIndex; // reorder: the first item picked in leftList (2 after picking ふしぎなアメ)
    /* 0x410 */ LabItemCountSelector countSelector; // move: how many of the item to move; ×01 box at (202, 195), max 5 for モンスターボール x5
    /* 0x490 */ ByteMatrix* tables; // @unverified: the 3 item tables of the boxes (func_89003650's list0..list2)
    /* 0x494 */ s32* dirty; // @unverified: one per table, set when it changed
    /* 0x498 */ s32* gamePakSlot; // @unverified: picking box 2 as target with -1 here ends the window with 1
    /* 0x49C */ ByteMatrix reorderView; // func_80027410 over the rows of tables[0] with no rows in use; rightList shows it (000/020) while reordering
    /* 0x4AC */ TextBox textBox; // @unverified: typed from the function it is passed to
} LabItemOrganizeWindow; // size = 0x4E4

/* The せいとん (organize) menu window of the Lab terminal, D_89028950: ポケモンを いどうする / どうぐを
 * いどうする / ボックスを いどうする with a description of the row under the cursor (LabTerminal_InitMenuWindow). */
typedef struct LabTerminalMenuWindow {
    /* 0x00 */ Window window; // 368x206 at (48, 92), the せいとん window
    /* 0x2C */ Menu menu; // rows drawn by LabTerminal_DrawMenuRow; D-Down moved menu.cursor 0 -> 1 (どうぐを いどうする)
    /* 0x50 */ PointerList items; // func_80027804 over the row names (arg5): count 3
    /* 0x5C */ u16 itemFlags[16]; // @unverified: itemFlags of menu; the main menu uses 3
    /* 0x7C */ char** descriptions; // printed under the rows for menu.cursor (D_8900A710): changed to てもちのどうぐを せいりする。 with cursor 1
    /* 0x80 */ s32 descriptionLines; // 3; height of the blue description fill in 0x1C-pixel lines (poking 1 shrank it to one line)
} LabTerminalMenuWindow; // size = 0x84

/* The どうぐのせいり screen, D_89019128 (func_89003650, LabItem_UpdateScreen, LabItem_DrawScreen). */
typedef struct LabItemScreen {
    /* 0x000 */ s32 state; // 1 = organizeWindow, 2 = save prompt (seen after メニューへもどる with changes), 3-6 = deleting a ６４の カセット save (LabItem_UpdateScreen)
    /* 0x004 */ LabItemOrganizeWindow organizeWindow; // the どうぐのせいり window, 564x372 at (38, 81)
    /* 0x4E8 */ SavePrompt savePrompt; // 「ないようが へんこうされています」 (contents changed): レポートしてやめる / レポートしないでやめる / キャンセル at state 2
    /* 0x54C */ LabItemConfirmWindow confirmWindow; // @unverified: typed from the function it is passed to
    /* 0x604 */ LabItemDeleteDataWindow deleteDataWindow; // @unverified: typed from the function it is passed to
    /* 0x68C */ LabItemSaveDataWindow saveDataWindow; // @unverified: typed from the function it is passed to
    /* 0x884 */ u8 bagItemRows[0x2A]; // rows of itemTables[0], 0x14 rows of 2 bytes {item, count}: 14 03, 04 05, 28 02 = キズぐすり x3, モンスターボール x5, ふしぎなアメ x2
    /* 0x8AE */ u8 pcItemRows[0x66]; // rows of itemTables[1], 0x32 rows of 2 bytes: 14 01 (キズぐすり x1), then 04 02 in front after 2 モンスターボール were moved in
    /* 0x914 */ u8 gamePakItemRows[0xCC]; // @unverified: rows of itemTables[2], 0x64 rows of 2 bytes
    /* 0x9E0 */ ByteMatrix itemTables[3]; // the bag (GB deck 0x23, capacity 20, shown 003/020), the PC (GB deck 0x22, 001/050) and the ６４の カセット (deck 0x12, capacity 100)
    /* 0xA10 */ s32 dirty[3]; // set when a table changed: {1, 1, 0} after moving モンスターボール from the bag to the PC; LabItem_SaveChanges writes those back
    /* 0xA1C */ s32 gamePakSlot; // @unverified: the LabItemSaveSlot itemTables[2] is read from and saved to; -1 = none free
    /* 0xA20 */ LabItemSaveSlot saveSlots[4]; // @unverified: LabItem_LoadGamePakBoxSlots
} LabItemScreen; // size = 0xA70

/* The window of the ポケモンを いどうする screen: six operation buttons, two box pickers and two
 * Pokémon lists side by side (PcSort_InitOrganizeWindow, PcSort_UpdateOrganizeWindow). */
typedef struct PcSortOrganizeWindow {
    /* 0x000 */ s32 state; // 1 = picking an operation, 2/3 = box pickers, 4-7 = Pokémon lists, 0xA-0xD = text box up; seen 1, 2, 3, 4, 5 and 0xA (さいごのポケモンです) in play
    /* 0x004 */ Window window; // the ポケモンのせいり window, 564x370 at (38, 83)
    /* 0x030 */ WindowFrame footerFrame; // the bottom strip, 552x108 at (44, 339): the operation name, or the Pokémon's stats and moves for みる
    /* 0x050 */ ImageButton moveButton; // operation 0 「ポケモンをいどうする」 (move), top left
    /* 0x07C */ ImageButton backButton; // operation 1 (back to the menu, house icon), top right
    /* 0x0A8 */ ImageButton exchangeButton; // operation 2 (いれかえる, exchange), middle left
    /* 0x0D4 */ ImageButton reorderButton; // operation 3 (ならべかえる, reorder), middle right
    /* 0x100 */ ImageButton viewButton; // operation 4 「ポケモンをみる」 (look), bottom left
    /* 0x12C */ ImageButton releaseButton; // operation 5 (にがす, release; the hand), bottom right
    /* 0x158 */ ByteMatrix buttonTable; // @unverified: rows = the six buttons, items of operationMenu
    /* 0x168 */ GridMenu operationMenu; // cursor = the operation, 2 columns: D-Right 0 -> 1, D-Down 1 -> 3, D-Left 3 -> 2, D-Down 2 -> 4
    /* 0x190 */ u16 operationFlags[6]; // @unverified: typed from the function it is passed to
    /* 0x19C */ PcSortMenuWindow sourceBoxWindow; // picks the box of leftList (state 2): てもち, GBのボックス1-8, 64のボックス1-4; てもち with one Pokémon gave さいごのポケモンです
    /* 0x214 */ PcSortMenuWindow targetBoxWindow; // picks the box of rightList (state 3)
    /* 0x28C */ s32 leftBox; // index into boxTables of leftList: 0 てもち, 1 GBのボックス1
    /* 0x290 */ s32 rightBox; // index into boxTables of rightList: 1 GBのボックス1, 12 64のボックス4; -1 while it shows partyView (みる)
    /* 0x294 */ PcSortMonList leftList; // the left Pokémon list at (52, 127)
    /* 0x31C */ PcSortMonList rightList; // the right Pokémon list at (384, 127)
    /* 0x3A4 */ s32 swapIndex; // @unverified: reorder: the first Pokémon picked in leftList
    /* 0x3A8 */ ByteMatrix* boxTables; // PcSortScreen.partyTable and the 12 box tables after it: index 1 = GB box 1, 12 = 64 box 4
    /* 0x3AC */ s32* dirty; // PcSortScreen.dirty, one per box table
    /* 0x3B0 */ ByteMatrix partyView; // a copy of boxTables[0] (rows = partyMons, capacity 6) with no rows in use, shown as 00/06 in rightList for みる
    /* 0x3C0 */ TextBox textBox; // @unverified: typed from the function it is passed to
} PcSortOrganizeWindow; // size = 0x3F8

/* The ポケモンを いどうする screen (PcSort_Init, PcSort_UpdateScreen, PcSort_DrawScreen). */
typedef struct PcSortScreen {
    /* 0x0000 */ s32 state; // @unverified: PcSort_UpdateScreen
    /* 0x0004 */ s8* iconFramebuffers; // @unverified: PokeIcon_AllocFramebuffers
    /* 0x0008 */ u16* monRenderer; // @unverified: func_80018F2C; the anim of statusWindow
    /* 0x000C */ s32 mode; // @unverified: PcSort_Init's arg1
    /* 0x0010 */ PcSortOrganizeWindow organizeWindow; // the ポケモンのせいり window
    /* 0x0408 */ SavePrompt savePrompt; // @unverified: typed from the function it is passed to
    /* 0x046C */ PcBoxConfirmWindow statusWindow; // @unverified: typed from the function it is passed to
    /* 0x052C */ BattleMon partyMons[6]; // read from deck 0x20 of the GB cart: partyMons[0] ヒトカゲ (4) Lv10, the only party Pokémon
    /* 0x070C */ BattleMon gbBoxMons[8][30]; // read from deck 0x21 of the GB cart: gbBoxMons[0][0] ピカチュウ (25) Lv25, the one moved there in いちらん
    /* 0x520C */ BattleMon stadiumBoxMons[4][30]; // @unverified: read from deck 0x11, the 64 boxes
    /* 0x778C */ ByteMatrix partyTable; // rows = partyMons, capacity 6, count 1 (shown 01/06); boxTables[0] of organizeWindow
    /* 0x779C */ ByteMatrix gbBoxTables[8]; // rows = gbBoxMons, capacity 30: box 1 count 1 (01/30), 0 after moving ハナ out
    /* 0x781C */ ByteMatrix stadiumBoxTables[4]; // rows = stadiumBoxMons: box 4 count 1 after moving ハナ there
    /* 0x785C */ s32 dirty[13]; // set when a table changed: [1] (GB box 1) and [12] (64 box 4) after moving ハナ; PcSort_SaveChanges writes those back
} PcSortScreen; // size = 0x7890

void PcBox_InitConfirmWindow(PcBoxConfirmWindow* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, u16* arg6);
s32 PcBox_UpdateConfirmCursor(PcBoxConfirmWindow* arg0);
void PcBox_DrawMonStatusWindow(PcBoxConfirmWindow* arg0);

typedef struct unk_func_88208C5C {
    /* 0x00 */ WidgetNode unk_00;
    /* 0x2C */ unk_func_8850143C* unk_2C;
    /* 0x30 */ s32 unk_30;
    /* 0x34 */ s32 unk_34;
    /* 0x38 */ s32 unk_38;
} unk_func_88208C5C; // size = 0x3C

typedef struct unk_func_882079D8 {
    /* 0x00 */ WidgetNode unk_00;
    /* 0x2C */ BattleMon* unk_2C;
} unk_func_882079D8; // size = 0x30

typedef struct unk_func_8820BE14_030 {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ MemoryPool* unk_04;
    /* 0x08 */ WidgetLinkHeader* unk_08;
    /* 0x0C */ BattleMon* unk_0C;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ WidgetNode* unk_14;
    /* 0x18 */ s32 unk_18;
} unk_func_8820BE14_030; // size >= 0x1C

// Copy of above with unk_2C changed just for fragment23_1AE680
typedef struct unk_func_88200FA0_030_030_1AE680 {
    /* 0x00 */ WidgetNode unk_00;
    /* 0x2C */ PointerList* unk_2C;
    /* 0x30 */ s32 unk_30;
    /* 0x34 */ u16* unk_34;
    /* 0x38 */ s32 unk_38;
    /* 0x3C */ s16 unk_3C;
    /* 0x3E */ s16 unk_3E;
    /* 0x40 */ unk_func_88200FA0_030_030_040 unk_40;
    /* 0x44 */ WidgetAnimatedFrame* unk_44;
    /* 0x48 */ s16 unk_48;
    /* 0x4A */ s16 unk_4A;
    /* 0x4C */ s16 unk_4C;
    /* 0x4E */ s16 unk_4E;
    /* 0x50 */ s16 unk_50;
    /* 0x52 */ s16 unk_52;
} unk_func_88200FA0_030_030_1AE680; // size = 0x54

typedef struct unk_func_8820B12C_02C_020 {
    /* 0x00 */ unk_func_88200FA0_030_030_1AE680 unk_00; // unk_func_882025E0_024
    /* 0x54 */ u16 unk_54;
    /* 0x56 */ u16 unk_56;
    /* 0x58 */ s32 unk_58;
    /* 0x5C */ s32 unk_5C;
    /* 0x60 */ s32 unk_60;
    /* 0x64 */ s32 unk_64;
    /* 0x68 */ s32 unk_68;
    /* 0x6C */ s32 unk_6C;
    /* 0x70 */ s32 unk_70;
    /* 0x74 */ WidgetUpdateCallback unk_74;
    /* 0x78 */ WidgetDrawCallback unk_78;
    /* 0x7C */ WidgetInputCallback unk_7C;
    /* 0x80 */ WidgetDrawCallback unk_80;
    /* 0x84 */ unk_func_8820BE14_02C_038_084* unk_84;
    /* 0x88 */ s32* unk_88;
    /* 0x8C */ u32 unk_8C;
} unk_func_8820B12C_02C_020; // size = 0x90

typedef s32 (*unk_func_8820B12C_02C_010)(struct unk_func_8820B12C_02C* arg0, Controller* arg1);

typedef void (*unk_func_8820B12C_02C_014)(struct unk_func_8820B12C_02C* arg0, s32 arg1);

typedef struct unk_func_8820B12C_02C {
    /* 0x00 */ char unk00[0x4];
    /* 0x04 */ struct unk_func_8820B12C_02C* unk_04;
    /* 0x08 */ struct unk_func_8820B12C_02C* unk_08;
    /* 0x0C */ char unk0C[0x4];
    /* 0x10 */ unk_func_8820B12C_02C_010 unk_10;
    /* 0x14 */ unk_func_8820B12C_02C_014 unk_14;
    /* 0x18 */ s32 unk_18;
    /* 0x1C */ s32 unk_1C;
    /* 0x20 */ unk_func_8820B12C_02C_020* unk_20[2];
    /* 0x28 */ s32 unk_28;
    /* 0x2C */ s32 unk_2C;
    /* 0x30 */ s32 unk_30;
    /* 0x34 */ s32 unk_34;
    /* 0x38 */ unk_func_88217740* unk_38;
    /* 0x3C */ unk_func_88509F48* unk_3C;
    /* 0x40 */ unk_func_8850CD44* unk_40;
    /* 0x44 */ FragmentEntry unk_44;
    /* 0x48 */ unk_func_8820BE14_030* unk_48;
    /* 0x4C */ unk_func_882173EC* unk_4C[2];
    /* 0x54 */ unk_func_882079D8* unk_54[2];
    /* 0x5C */ unk_func_8850878C* unk_5C[6];
    /* 0x74 */ s32 unk_74;
} unk_func_8820B12C_02C; // size = 0x78

typedef struct unk_func_8820B12C_000 {
    /* 0x00 */ char unk00[0x4];
    /* 0x04 */ struct unk_func_8820B12C_000* unk_04;
    /* 0x08 */ struct unk_func_8820B12C_000* unk_08;
    /* 0x0C */ char unk0C[0x4];
    /* 0x10 */ unk_func_8820B12C_02C_010 unk_10;
    /* 0x14 */ unk_func_8820B12C_02C_014 unk_14;
    /* 0x18 */ char unk18[0x4];
    /* 0x1C */ s32 unk_1C;
    /* 0x20 */ s32 unk_20;
    /* 0x24 */ struct unk_func_8820BE14_02C* unk_24;
} unk_func_8820B12C_000; // size = 0x28

typedef struct unk_func_8820B12C {
    /* 0x00 */ unk_func_8820B12C_000 unk_00;
    /* 0x28 */ WidgetGridMenu* unk_28;
    /* 0x2C */ unk_func_8820B12C_02C* unk_2C;
} unk_func_8820B12C; // size = 0x30

typedef struct unk_func_8820BE14_02C_070 {
    /* 0x0000 */ WidgetNode unk_0000;
    /* 0x002C */ BattleMon* unk_002C;
    /* 0x0030 */ s16 unk_0030;
    /* 0x0032 */ char unk0032[0x7];
    /* 0x0039 */ u8 unk_0039[2][0xC80];
} unk_func_8820BE14_02C_070; // size = 0x193C

typedef struct unk_func_8820BE14_02C_078_034 {
    /* 0x00 */ WidgetNode unk_00;
    /* 0x2C */ WidgetAnimatedPanel* unk_2C;
    /* 0x30 */ unk_func_88200FA0_030_030* unk_30;
} unk_func_8820BE14_02C_078_034; // size = 0x34

typedef struct unk_func_8820BE14_02C_078 {
    /* 0x00 */ WidgetNode unk_00;
    /* 0x2C */ WidgetAnimatedPanel* unk_2C;
    /* 0x30 */ unk_func_88200FA0_030_030* unk_30;
    /* 0x34 */ unk_func_8820BE14_02C_078_034* unk_34;
    /* 0x38 */ ByteMatrix unk_38;
    /* 0x48 */ s32 unk_48;
    /* 0x4C */ s32 unk_4C;
    /* 0x50 */ s32 unk_50;
    /* 0x54 */ s32 unk_54;
    /* 0x58 */ s32 unk_58;
    /* 0x5C */ s32 unk_5C;
} unk_func_8820BE14_02C_078; // size = 0x60

typedef struct unk_func_8820BE14_02C {
    /* 0x00 */ WidgetNode unk_00;
    /* 0x2C */ WidgetAnimatedPanel* unk_2C;
    /* 0x30 */ unk_func_88208C5C* unk_30[2];
    /* 0x38 */ unk_func_8820BE14_02C_038* unk_38[2];
    /* 0x40 */ unk_func_88217740* unk_40;
    /* 0x44 */ unk_func_882149A0* unk_44[8];
    /* 0x64 */ unk_func_88500994* unk_64;
    /* 0x68 */ unk_func_88500994* unk_68;
    /* 0x6C */ unk_func_88500994* unk_6C;
    /* 0x70 */ unk_func_8820BE14_02C_070* unk_70;
    /* 0x74 */ unk_func_8820B12C* unk_74;
    /* 0x78 */ unk_func_8820BE14_02C_078* unk_78[2];
    /* 0x80 */ unk_func_88509F48* unk_80;
    /* 0x84 */ unk_func_889000C4* unk_84;
    /* 0x88 */ unk_func_8850878C* unk_88;
    /* 0x8C */ ByteMatrix* unk_8C;
    /* 0x90 */ char unk90[0x10];
} unk_func_8820BE14_02C; // size = 0xA0

typedef struct unk_D_88217C6C {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ u8* unk_08;
    /* 0x0C */ s16 unk_0C;
    /* 0x10 */ Color_RGBA8* unk_10;
    /* 0x14 */ s32 unk_14;
} unk_D_88217C6C; // size = 0x18

typedef struct unk_func_8821421C_02C_06C_02C_068 {
    /* 0x00 */ WidgetNode unk_00;
    /* 0x2C */ s32 unk_2C;
} unk_func_8821421C_02C_06C_02C_068; // size = 0x30

typedef struct unk_func_8820E99C_030 {
    /* 0x00 */ WidgetNode unk_00;
    /* 0x2C */ WidgetAnimatedPanel* unk_2C;
    /* 0x30 */ UiNumberInput unk_30;
    /* 0x44 */ unk_func_8820E99C_030_044* unk_44;
} unk_func_8820E99C_030; // size = 0x48

typedef struct unk_func_8820E99C {
    /* 0x00 */ WidgetNode unk_00;
    /* 0x2C */ WidgetAnimatedPanel* unk_2C;
    /* 0x30 */ unk_func_8820E99C_030* unk_30;
    /* 0x34 */ s32 unk_34;
} unk_func_8820E99C; // size = 0x38

typedef struct unk_func_8821421C_034 {
    /* 0x00 */ WidgetNode unk_00;
    /* 0x2C */ WidgetAnimatedPanel* unk_2C;
    /* 0x30 */ WidgetGridMenu* unk_30;
    /* 0x34 */ unk_func_8850878C* unk_34;
} unk_func_8821421C_034; // size = 0x38

typedef struct unk_func_8821421C_038_02C {
    /* 0x00 */ WidgetNode unk_00;
    /* 0x2C */ unk_func_8850143C* unk_2C;
    /* 0x30 */ unk_func_8821421C_038_050* unk_30;
} unk_func_8821421C_038_02C; // size = 0x34

typedef struct spE8_func_882121E0 {
    /* 0x00 */ char* unk_00[3];
} spE8_func_882121E0; // size >= 0xC

typedef struct unk_func_8821421C_02C_030 {
    /* 0x00 */ WidgetNode unk_00;
    /* 0x2C */ unk_func_8850143C* unk_2C;
    /* 0x30 */ s32 unk_30;
    /* 0x34 */ s32 unk_34;
    /* 0x38 */ spE8_func_882121E0* unk_38;
} unk_func_8821421C_02C_030; // size = 0x3C

typedef struct unk_func_8821421C_02C_06C_02C_060_02C_000 {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 unk_01;
} unk_func_8821421C_02C_06C_02C_060_02C_000; // size = 0x2

typedef struct unk_func_8821421C_02C_06C_02C_060_02C {
    /* 0x00 */ unk_func_8821421C_02C_06C_02C_060_02C_000 unk_00;
    /* 0x02 */ unk_func_8821421C_02C_06C_02C_060_02C_000 unk_02;
} unk_func_8821421C_02C_06C_02C_060_02C; // size >= 0x4

typedef struct unk_func_8821421C_02C_06C_02C_060 {
    /* 0x00 */ WidgetNode unk_00;
    /* 0x2C */ unk_func_8821421C_02C_06C_02C_060_02C unk_2C;
} unk_func_8821421C_02C_06C_02C_060; // size = 0x30

typedef struct unk_func_8821421C_02C_06C_02C {
    /* 0x00 */ char unk00[0x10];
    /* 0x10 */ unk_func_882025E0_010 unk_10;
    /* 0x14 */ unk_func_882025E0_014 unk_14;
    /* 0x18 */ s32 unk_18;
    /* 0x1C */ s32 unk_1C;
    /* 0x20 */ unk_func_8820BE14_02C_038* unk_20[2];
    /* 0x28 */ struct unk_func_8820E99C* unk_28;
    /* 0x2C */ unk_func_8820BE14_02C_038* unk_2C[2];
    /* 0x34 */ struct unk_func_8820E99C* unk_34;
    /* 0x38 */ s32 unk_38;
    /* 0x3C */ s32 unk_3C;
    /* 0x40 */ s32 unk_40;
    /* 0x44 */ s32 unk_44;
    /* 0x48 */ unk_func_88217740* unk_48;
    /* 0x4C */ unk_func_88509F48* unk_4C;
    /* 0x50 */ unk_func_8850CD44* unk_50;
    /* 0x54 */ char unk54[0x4];
    /* 0x58 */ unk_func_882173EC* unk_58[2];
    /* 0x60 */ unk_func_8821421C_02C_06C_02C_060* unk_60[2];
    /* 0x68 */ unk_func_8821421C_02C_06C_02C_068* unk_68[2];
    /* 0x70 */ unk_func_8821421C_02C_06C_02C_060* unk_70[2];
    /* 0x78 */ unk_func_882025E0_03C unk_78[5];
} unk_func_8821421C_02C_06C_02C; // size = 0xB4

typedef struct unk_func_8821421C_02C_06C_000 {
    /* 0x00 */ char unk00[0x4];
    /* 0x04 */ struct unk_func_88203ED8_064* unk_04;
    /* 0x08 */ struct unk_func_88203ED8_064* unk_08;
    /* 0x0C */ char unk0C[0x4];
    /* 0x10 */ unk_func_8820B12C_02C_010 unk_10;
    /* 0x14 */ unk_func_8820B12C_02C_014 unk_14;
    /* 0x18 */ char unk18[0x4];
    /* 0x1C */ s32 unk_1C;
    /* 0x20 */ s32 unk_20;
    /* 0x24 */ struct unk_func_8821421C_02C* unk_24;
} unk_func_8821421C_02C_06C_000; // size = 0x28

typedef struct unk_func_8821421C_02C_06C {
    /* 0x00 */ unk_func_8821421C_02C_06C_000 unk_00;
    /* 0x28 */ WidgetGridMenu* unk_28;
    /* 0x2C */ unk_func_8821421C_02C_06C_02C* unk_2C;
} unk_func_8821421C_02C_06C; // size = 0x30

typedef struct unk_func_8821421C_02C_070 {
    /* 0x00 */ WidgetNode unk_00;
    /* 0x2C */ WidgetAnimatedPanel* unk_2C;
    /* 0x30 */ unk_func_88200FA0_030_030* unk_30;
    /* 0x34 */ PointerList unk_34;
    /* 0x40 */ s32 unk_40;
    /* 0x44 */ s32 unk_44;
    /* 0x48 */ s32 unk_48;
} unk_func_8821421C_02C_070; // size = 0x4C

typedef struct unk_func_8821421C_02C {
    /* 0x00 */ WidgetNode unk_00;
    /* 0x2C */ WidgetAnimatedPanel* unk_2C;
    /* 0x30 */ unk_func_8821421C_02C_030* unk_30[2];
    /* 0x38 */ unk_func_8820BE14_02C_038* unk_38[2];
    /* 0x40 */ unk_func_88217740* unk_40;
    /* 0x44 */ unk_func_882149A0* unk_44[6];
    /* 0x5C */ unk_func_88500994* unk_5C;
    /* 0x60 */ unk_func_88500994* unk_60;
    /* 0x64 */ unk_func_88500994* unk_64;
    /* 0x68 */ unk_func_8850878C* unk_68;
    /* 0x6C */ unk_func_8821421C_02C_06C* unk_6C;
    /* 0x70 */ unk_func_8821421C_02C_070* unk_70[2];
    /* 0x78 */ struct unk_func_8821421C_03C* unk_78;
    /* 0x7C */ struct unk_func_8821421C_03C* unk_7C;
    /* 0x80 */ s32 unk_80;
    /* 0x84 */ struct unk_func_8821421C_038* unk_84;
    /* 0x88 */ struct unk_func_8821421C_034* unk_88;
    /* 0x8C */ unk_func_88509F48* unk_8C;
    /* 0x90 */ LabItemSaveSlot* unk_90;
    /* 0x94 */ unk_func_882025E0_03C unk_94[1];
    /* 0xA0 */ unk_func_889000C4* unk_A0;
} unk_func_8821421C_02C; // size = 0xA4

typedef void (*unk_func_8821421C_038_04C_000_014)(struct unk_func_8821421C_038_04C_000*, Controller*);

typedef struct unk_func_8821421C_038_04C_000 {
    /* 0x00 */ char unk00[0x4];
    /* 0x04 */ struct unk_func_88203ED8_064* unk_04;
    /* 0x08 */ struct unk_func_88203ED8_064* unk_08;
    /* 0x0C */ char unk0C[0x4];
    /* 0x10 */ unk_func_8820B12C_02C_010 unk_10;
    /* 0x14 */ unk_func_8821421C_038_04C_000_014 unk_14;
    /* 0x18 */ char unk18[0x4];
    /* 0x1C */ s32 unk_1C;
    /* 0x20 */ s32 unk_20;
    /* 0x24 */ struct unk_func_8821421C_038* unk_24;
} unk_func_8821421C_038_04C_000; // size = 0x28

typedef struct unk_func_8821421C_038_04C {
    /* 0x00 */ unk_func_8821421C_038_04C_000 unk_00;
    /* 0x28 */ WidgetGridMenu* unk_28;
} unk_func_8821421C_038_04C; // size = 0x2C

typedef struct unk_func_8821421C_03C {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ ByteMatrix unk_04;
} unk_func_8821421C_03C; // size = 0x14


typedef struct unk_func_8821421C_038 {
    /* 0x00 */ WidgetNode unk_00;
    /* 0x2C */ unk_func_8821421C_038_02C* unk_2C;
    /* 0x30 */ unk_func_8820BE14_02C_038* unk_30;
    /* 0x34 */ unk_func_8821421C_038_034* unk_34;
    /* 0x38 */ unk_func_88500994* unk_38;
    /* 0x3C */ unk_func_88500994* unk_3C;
    /* 0x40 */ unk_func_8850878C* unk_40;
    /* 0x44 */ WidgetAnimatedPanel* unk_44;
    /* 0x48 */ unk_func_8821421C_034* unk_48;
    /* 0x4C */ unk_func_8821421C_038_04C* unk_4C;
    /* 0x50 */ unk_func_8821421C_038_050* unk_50[1];
    /* 0x54 */ char unk54[0xC];
    /* 0x60 */ s32 unk_60;
    /* 0x64 */ ByteMatrix unk_64;
    /* 0x74 */ char unk74[0x4];
} unk_func_8821421C_038; // size = 0x78

/* Struct types that were defined identically in each of these files; this is
 * now the one definition they all include:
 * src/fragments/fragment015_238BD0/lab_pc_list_1CEA00.c
 * src/fragments/fragment015_238BD0/lab_pc_list_1CEA00_8900379C.c
 * src/fragments/fragment015_238BD0/lab_pc_list_1CEA00_89003880.c
 */

/* The prim and env colors of a two-color fill or font (Ui_FillRectPrimEnvColor, LabItem_DrawTitleText). */
typedef struct PrimEnvColor {
    /* 0x0 */ Color_RGBA8 prim;
    /* 0x4 */ Color_RGBA8 env;
} PrimEnvColor; // size = 0x8


typedef void (*func889000C4)(unk_func_889000C4*, s32, WidgetAnimatedPanel*, s32, char**, MemoryPool*);

typedef void (*func889006D4)(unk_func_889000C4*, s32);

typedef void (*func889007AC)(unk_func_889000C4*);

typedef s32 (*func88900808)(unk_func_889000C4*, Controller*, s32);

typedef void (*func88900970)(unk_func_889000C4*, s32);

typedef struct unk_D_88400100 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ Color_RGBA8 unk_04;
} unk_D_88400100; // size = 0x8

typedef unk_D_88400100* (*func8840007C)(BattleMon*);

typedef unk_D_88400138* (*func884000C4)(s32);

struct unk_func_88203ED8_064;

// lab_items.c
void LabItem_ReadDeckEntries(s32 arg0, s32 arg1, s32 arg2, ByteMatrix* arg3);
void LabItem_WriteDeckBack(s32 arg0, s32 arg1, s32 arg2, ByteMatrix* arg3, s32 arg4, char* arg5, s32 arg6);
void LabItem_LoadGamePakBoxSlots(LabItemSaveSlot* arg0);
s32 LabItem_FindOrAllocateGamePakBoxSlot(LabItemSaveSlot* arg0, s32 arg1, char* arg2);
s32 LabItem_ComputeRemainingCapacity(s32 arg0, ByteMatrix* arg1);
s32 LabItem_ComputeMaxTransferQuantity(s32 arg0, ByteMatrix* arg1);
void func_8900020C(void);

// pc_sort.c
void func_89004708(void);
void func_89004710(void);

// functions defined in assembly
void LabItem_SubtractSelectedItemQuantity(unk_func_8820BE14_02C_038* arg0, s32 arg1);
void WidgetTree_RemoveScrollableGridEntry(unk_func_8820BE14_02C_038*);

#endif // FRAGMENT_LAB_PC_H
