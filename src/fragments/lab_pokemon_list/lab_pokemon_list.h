/* Declarations for the lab_pokemon_list fragment (src/fragments/lab_pokemon_list/). */
#ifndef FRAGMENT_LAB_POKEMON_LIST_H
#define FRAGMENT_LAB_POKEMON_LIST_H

#include "global.h"
#include "moves.h"
#include "pokemon.h"
#include "m2c_macros.h"
#include "game_state.h"
#include "gb_save.h"
#include "memory.h"
#include "menu.h"
#include "table_view.h"

// Seems to be >= 0x58 in other places?
typedef struct unk_func_8830867C_02C_144_000 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ char unk08[0x4];
    /* 0x0C */ unk_func_8830867C_02C_0CC_000_000* unk_0C;
    /* 0x10 */ char unk10[0x4];
    /* 0x14 */ s32 unk_14;
    /* 0x18 */ char unk18[0x8];
} unk_func_8830867C_02C_144_000; // size = 0x20

typedef struct unk_func_8830867C_02C_144 {
    /* 0x00 */ unk_func_8830867C_02C_144_000* unk_00;
    /* 0x04 */ char unk04[0x4];
    /* 0x08 */ s32 unk_08;
} unk_func_8830867C_02C_144; // size >= 0xC

typedef struct unk_func_8830867C_02C_154 {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ u8 unk_02;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ u8* unk_0C;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ s32 unk_14;
    /* 0x18 */ char unk18[0x4];
} unk_func_8830867C_02C_154; // size = 0x1C

typedef struct unk_func_8830867C_02C_1A8 {
    /* 0x00 */ u8* unk_00;
    /* 0x04 */ unk_func_8830867C_02C_154* unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
} unk_func_8830867C_02C_1A8; // size = 0x10

typedef struct unk_func_8830867C_04C_030_02C_000_000 {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ char unk02[0x6];
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ unk_func_8830867C_04C_030_02C_000_000_00C unk_0C;
} unk_func_8830867C_04C_030_02C_000_000; // size >= 0x18

typedef struct unk_func_8830867C_04C_030_02C_000 {
    /* 0x00 */ unk_func_8830867C_04C_030_02C_000_000* unk_00[1];
} unk_func_8830867C_04C_030_02C_000; // size >= 0x8

typedef void (*unk_func_8830867C_04C_078_030_040)();

typedef struct unk_func_8830867C_02C_C54_014 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ u8 unk_04[2];
} unk_func_8830867C_02C_C54_014; // size >= 0x8

typedef struct unk_func_8830867C_02C_C54_01C {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ u8 unk_04[2];
} unk_func_8830867C_02C_C54_01C; // size >= 0x8

typedef struct unk_func_8830867C_02C_C54_024 {
    /* 0x00 */ u8 unk_00[4];
    /* 0x04 */ s32 unk_04;
} unk_func_8830867C_02C_C54_024; // size >= 0x8

typedef struct unk_func_88309C38_arg2_004 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ Color_RGBA8 unk_04;
} unk_func_88309C38_arg2_004; // size >= 0x8

typedef struct unk_func_88309C38_arg2_00C {
    /* 0x00 */ char unk00[0x14];
    /* 0x14 */ s32 unk_14;
    /* 0x18 */ s32 unk_18;
} unk_func_88309C38_arg2_00C; // size >= 0x1C

typedef struct unk_func_88309C38_arg2 {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 unk_01;
    /* 0x04 */ unk_func_88309C38_arg2_004* unk_04;
    /* 0x08 */ char unk08[0x4];
    /* 0x0C */ unk_func_88309C38_arg2_00C* unk_0C;
    /* 0x10 */ char unk10[0x4];
    /* 0x14 */ s32 unk_14;
    /* 0x18 */ s32 unk_18;
} unk_func_88309C38_arg2; // size >= 0x1C

typedef struct unk_func_88310CA4_arg2 {
    /* 0x00 */ u8* unk_00;
    /* 0x04 */ u8* unk_04;
    /* 0x08 */ char unk08[0x4];
    /* 0x0C */ unk_func_88309C38_arg2_00C* unk_0C;
    /* 0x10 */ char unk10[0x4];
    /* 0x14 */ s32 unk_14;
    /* 0x18 */ s32 unk_18;
} unk_func_88310CA4_arg2; // size >= 0x1C

typedef struct unk_func_88313894_020 {
    /* 0x00 */ char unk00[0xC];
    /* 0x0C */ unk_func_8830867C_02C_0CC_000_000* unk_0C;
    /* 0x10 */ char unk10[0x4];
    /* 0x14 */ s32 unk_14;
    /* 0x18 */ char unk18[0x4];
    /* 0x1C */ s32 unk_1C;
} unk_func_88313894_020; // size = 0x20

/* Struct types that were defined identically in each of these files; this is
 * now the one definition they all include:
 * src/fragments/fragment016_252E10/89100020_89100914.c
 * src/fragments/fragment016_252E10/89100020_89102AB8.c
 * src/fragments/fragment016_252E10/89100020_89102C40.c
 * src/fragments/fragment016_252E10/89100020_89103620.c
 * src/fragments/fragment016_252E10/89100020_89103740.c
 */

typedef struct Entry89100FC4 {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 type;
    /* 0x04 */ const char* name;
    /* 0x08 */ s32 unk_08;
} Entry89100FC4; // size = 0xC

/* Struct types that were defined identically in each of these files; this is
 * now the one definition they all include:
 * src/fragments/fragment016_252E10/89100020_891012A8.c
 * src/fragments/fragment016_252E10/89100020_891019E4.c
 */


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

/* Struct types that were defined identically in each of these files; this is
 * now the one definition they all include:
 * src/fragments/fragment016_252E10/89100020_89102C40.c
 * src/fragments/fragment016_252E10/89100020_89103620.c
 * src/fragments/fragment016_252E10/89100020_89103740.c
 */

typedef struct Info891033A0 { u8 unk00[6]; u8 unk06; u8 unk07; u8 unk08[0xF]; } Info891033A0;

/* Struct types that were defined identically in each of these files; this is
 * now the one definition they all include:
 * src/fragments/fragment016_252E10/89100020.c
 * src/fragments/fragment016_252E10/89100020_891012A8.c
 * src/fragments/fragment016_252E10/89100020_891019E4.c
 */

typedef struct Entry89100140 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ ByteMatrix boxes; // @unverified: 0x20-byte rows: 1 for てもち, 8 for the GB boxes, 4 for the cartridge boxes (func_89100140); row +0xC = checked, +0x1C = Pokémon count (func_891053B0)
    /* 0x20 */ s32 unk_20;
} Entry89100140; // size = 0x24





/* Struct types that were defined identically in each of these files; this is
 * now the one definition they all include:
 * src/fragments/fragment016_252E10/89100020.c
 * src/fragments/fragment016_252E10/89100020_891012A8.c
 * src/fragments/fragment016_252E10/89100020_891019E4.c
 * src/fragments/fragment016_252E10/89100020_89102AB8.c
 */


/* Struct types that were defined identically in each of these files; this is
 * now the one definition they all include:
 * src/fragments/fragment016_252E10/89100020.c
 * src/fragments/fragment016_252E10/89100020_891012A8.c
 * src/fragments/fragment016_252E10/89100020_891019E4.c
 * src/fragments/fragment016_252E10/89100020_89102AB8.c
 * src/fragments/fragment016_252E10/89100020_89102C40.c
 * src/fragments/fragment016_252E10/89100020_89103620.c
 * src/fragments/fragment016_252E10/89100020_89103740.c
 */



/* A popup menu in the いちらん (Pokémon list) screen (LabPCList_InitPopupMenu, LabPCList_PlacePopup,
 * LabPCList_DrawPopupMenu): a window, the rectangle it opens next to, then its menu. */
typedef struct LabPopupMenu {
    /* 0x00 */ Window window;
    /* 0x2C */ s32 anchorX; // the rectangle the popup opens next to: the レベル header cell gave anchor (164, 130, 0, 22) and the popup opened at (164, 152)
    /* 0x30 */ s32 anchorY;
    /* 0x34 */ s32 anchorW;
    /* 0x38 */ s32 anchorH;
    /* 0x3C */ s32 unk_3C;
    /* 0x40 */ Menu menu;
    /* 0x64 */ PointerList itemList; // the item strings: count 4 for the row popup (ピカチュウをあつめる, おなじタイプをあつめる, いどうする, どうぐをつかう), 3 for the sort popup, 8 for the box list
    /* 0x70 */ s32 title; // text of the title tab when nonzero: set on the どこへ? popup, 0 on the untitled row and sort popups
    /* 0x74 */ s32 limitX; // right edge the popup stays left of: 596, the right of listFrame
    /* 0x78 */ s32 limitY; // bottom edge the popup stays above: 432, the bottom of listFrame
} LabPopupMenu; // size = 0x7C

typedef struct Slot89102930 {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ char unk08[0x14];
} Slot89102930; // @unverified: size = 0x1C

/* The レベルのにゅうりょく (level input) window of the いちらん screen: 「001 から 100」
 * (LabPCList_InitLevelInputWindow). */
typedef struct LabLevelInputWindow {
    /* 0x00 */ Window window;
    /* 0x2C */ LabeledButton clearButton; // かいじょ; flags bit 0 (greyed out) when no level filter is active
    /* 0x68 */ LabeledButton gatherButton; // あつめる
    /* 0xA4 */ DigitSelector minLevel; // the left 3-digit number; D-Up on its tens digit turned 001 into 011, and あつめる stored 11 in levelFilterMin
    /* 0xB8 */ DigitSelector maxLevel; // the right 3-digit number, 100 at open; D-Up on its hundreds digit wrapped it to 1
    /* 0xCC */ ChoiceCursor cursor; // count 2: 0 = あつめる, 1 = かいじょ (D-Down) when focus is 2
    /* 0xD8 */ s32 unk_D8;
    /* 0xDC */ s32 column; // D-Left/D-Right position: opens at 2 (ones digit of minLevel), 3-5 the digits of maxLevel (3 = hundreds), 6 the buttons
    /* 0xE0 */ s32 unk_E0;
    /* 0xE4 */ s32 focus; // 0 = minLevel, 1 = maxLevel, 2 = the buttons; followed column 2 -> 3 -> 6
} LabLevelInputWindow; // size = 0xE8

/* A list of boxes that opens next to the source-select window when a box source is checked
 * (func_8910576C): one row per box, ボックス%d (Box %d), each with a check mark. */
typedef struct LabBoxListWindow {
    /* 0x00 */ WindowFrame frame; // @unverified: 156 wide, 28 per row (func_8910576C)
    /* 0x20 */ Menu menu; // @unverified: items are the boxes of one source; itemFlags bit 3 = checked (func_8910587C)
} LabBoxListWindow; // size = 0x44

/* The source-select window of the いちらん screen: 「どこのポケモンを いちらん するか えらんでください。」
 * (Which Pokémon do you want to list? Choose.), a checkbox row per source and an ＯＫ button (func_89105C54). */
typedef struct LabSourceSelectWindow {
    /* 0x000 */ s32 openBoxList; // @unverified: 0 = none, 1 = gbBoxes, 2 = cartBoxes takes the input (func_89106254)
    /* 0x004 */ Window window; // @unverified: 308x206 (func_89105C54)
    /* 0x030 */ WindowFrame textFrame; // @unverified: frame of the prompt text (func_89105E70)
    /* 0x050 */ WindowFrame listFrame; // @unverified: frame of the source rows
    /* 0x070 */ Menu menu; // @unverified: the sources: てもち, ゲームボーイのボックス, 64カセットのボックス; itemFlags bit 3 = checked
    /* 0x094 */ LabeledButton okButton; // @unverified: ＯＫ (D_8910E024)
    /* 0x0D0 */ ChoiceCursor cursor; // @unverified: count 4: the three sources, then okButton (func_891060BC)
    /* 0x0DC */ LabBoxListWindow gbBoxes; // @unverified: boxes of row 1 (func_89105C54)
    /* 0x120 */ LabBoxListWindow cartBoxes; // @unverified: boxes of row 2
    /* 0x164 */ u16 itemFlags[4]; // @unverified: menu.itemFlags
    /* 0x16C */ u16 gbBoxFlags[8]; // @unverified: gbBoxes.menu.itemFlags
    /* 0x17C */ u16 cartBoxFlags[4]; // @unverified: cartBoxes.menu.itemFlags
} LabSourceSelectWindow; // size = 0x184

/* The move list of the item window: どの わざに つかいますか？ (On which move?) for a PP Up, どの わざを
 * わすれさせたい？ (Which move should it forget?) for a TM or HM (func_89104FC0). */
typedef struct LabMoveSelectWindow {
    /* 0x00 */ Window window; // @unverified: 168x132 (func_89104FC0)
    /* 0x2C */ Menu menu; // @unverified: rows drawn by func_89104EB4
    /* 0x50 */ ByteMatrix moveMatrix; // @unverified: over moves (func_89104FC0)
    /* 0x60 */ s32 moves[4]; // @unverified: move index - 1 of each slot, -1 when empty (func_89104FC0)
    /* 0x70 */ u16 itemFlags[4]; // @unverified: menu.itemFlags; bit 0 = an HM move, which cannot be forgotten (LabMoveSelect_DisableHmMoves)
    /* 0x78 */ s32 learnTimer; // @unverified: 60 frames: the old move fades out, at 29 it becomes learnMove (func_89105200)
    /* 0x7C */ s32 learnSlot; // @unverified: slot that learnMove replaces (func_89105340)
    /* 0x80 */ s32 learnMove; // @unverified: written to moves[learnSlot] (func_89105200)
} LabMoveSelectWindow; // size = 0x84

/* The どうぐをつかう (use an item) window of the いちらん screen: 「<name>がつかえるどうぐ」 (Items <name>
 * can use) over the Game Boy bag items (LabPCList_InitItemWindow). */
typedef struct LabItemWindow {
    /* 0x000 */ Window window; // @unverified: 388x366; title = D_89119BD0, the Pokémon's name and がつかえるどうぐ
    /* 0x02C */ WindowFrame textFrame; // @unverified: frame of the prompt text at the bottom (PcSort_DrawUseItemPrompt)
    /* 0x04C */ ScrollList list; // @unverified: the bag items, 8 rows; itemFlags bit 0 = cannot be used (func_89108450)
    /* 0x090 */ u16 confirmItemFlags[2]; // @unverified: confirmPopup.menu.itemFlags
    /* 0x094 */ LabPopupMenu confirmPopup; // @unverified: このどうぐをつかいますか？ (Use this item?) choice (mode 1)
    /* 0x110 */ LabMoveSelectWindow moveSelect; // @unverified: the move list of modes 2 to 4
    /* 0x194 */ char unk_194[0x1AC - 0x194];
    /* 0x1AC */ u8* mon; // @unverified: the Pokémon the item is used on; its species names the window (LabPCList_InitItemWindow)
    /* 0x1B0 */ s32 mode; // @unverified: 0 = pick an item, 1 = confirm, 2 = PP Up move, 3 = move to forget, 4 = learning (PcSort_DrawUseItemPrompt)
} LabItemWindow; // size = 0x1B4

/* What a used item did, shown by the message window: a title and a value change (LabPCList_DrawMessageWindow). */
typedef struct LabItemResult {
    /* 0x00 */ char* title; // @unverified: printed at the top of the message window
    /* 0x04 */ s32 kind; // @unverified: 0 = left and right are numbers (%4d, %d), 1 = they are strings
    /* 0x08 */ char* left; // @unverified: the value before
    /* 0x0C */ char* right; // @unverified: the value after, drawn right of an arrow (D_8910D2F0)
} LabItemResult; // size = 0x10

/* The window that shows a LabItemResult until A or B is pressed (LabPCList_InitMessageWindow). */
typedef struct LabMessageWindow {
    /* 0x00 */ Window window; // @unverified: 276x96 at (182, 234)
    /* 0x2C */ LabItemResult* message; // @unverified: LabPCList_InitMessageWindow arg3
} LabMessageWindow; // size = 0x30

/* One slot of a filter window: a button that shows the chosen type or move, ---- when empty. */
typedef struct LabFilterSlot {
    /* 0x00 */ LabeledButton button; // @unverified: label = the name of the choice (LabPCList_UpdateTypeFilter)
    /* 0x3C */ s32 index; // @unverified: row of the choice in the window's list, -1 when empty
} LabFilterSlot; // size = 0x40

/* The タイプであつめる (gather by type) window of the いちらん screen (LabPCList_InitTypeFilter). */
typedef struct LabTypeFilterWindow {
    /* 0x000 */ Window window; // @unverified: 342x288
    /* 0x02C */ LabFilterSlot slots[2]; // two empty type slots were seen in play
    /* 0x0AC */ LabeledButton clearButton; // かいじょ; flags bit 0 when no type filter is set
    /* 0x0E8 */ LabeledButton gatherButton; // あつめる
    /* 0x124 */ ChoiceCursor cursor; // @unverified: count 4: slots 0 and 1, gatherButton, clearButton (LabPCList_UpdateTypeFilter)
    /* 0x130 */ ScrollList list; // the numbered type list (1 ノーマル, 2 かくとう, ... 8 ゴースト); itemFlags bit 3 = in a slot
    /* 0x174 */ s8* names[15]; // @unverified: entries of D_80066AD8 (a name pointer first), skipping entry 6
    /* 0x1B0 */ u16 typeFlags[16]; // @unverified: list.itemFlags
    /* 0x1D0 */ PointerList typeList; // @unverified: over names, the items of list
    /* 0x1DC */ s32 mode; // @unverified: 0 = the buttons, 1 = the list (LabPCList_UpdateTypeFilter)
} LabTypeFilterWindow; // size = 0x1E0

/* The わざであつめる (gather by move) window of the いちらん screen (LabPCList_InitMoveFilter). */
typedef struct LabMoveFilterWindow {
    /* 0x000 */ Window window; // @unverified: typed from the function it is passed to
    /* 0x02C */ LabFilterSlot slots[4]; // @unverified: like LabTypeFilterWindow.slots
    /* 0x12C */ LabeledButton clearButton; // @unverified: かいじょ; flags bit 0 when no move filter is set
    /* 0x168 */ LabeledButton gatherButton; // @unverified: あつめる
    /* 0x1A4 */ ChoiceCursor cursor; // @unverified: count 6: the four slots, gatherButton, clearButton
    /* 0x1B0 */ ScrollList list; // the numbered move list (1 10まんボルト, 2 あくまのキッス, ...)
    /* 0x1F4 */ u16 moveFlags[164]; // @unverified: list.itemFlags
    /* 0x33C */ ByteMatrix moveMatrix; // @unverified: 164 one-byte rows over D_8910A978, the items of list
    /* 0x34C */ s32 mode; // @unverified: 0 = the buttons, 1 = the list
} LabMoveFilterWindow; // size = 0x350

#define LAB_PC_LIST_MAX_ROWS 466

/* The いちらん (Pokémon list) screen of the Lab PC (LabPCList_InitListWindow). Its functions used to
 * take it through a dozen partial views (Ctx891012A8, Ctx89100294, Big891003A4, ...). */
typedef struct LabPCListScreen {
    /* 0x0000 */ Window window; // 564x382 at (38, 72)
    /* 0x002C */ WindowFrame listFrame; // the column header row and the rows, 552x302 at (6, 0x3A) in the window
    /* 0x004C */ WindowFrame headerFrame; // the top bar (L タテ/ヨコきりかえ R, ページおくり 1/3), 552x30 at (6, 6) in the window
    /* 0x006C */ PointerList filteredRows; // what the filters leave of rows: 2 of 3 after the level filter 11-100 dropped ヒトカゲ Lv10
    /* 0x0078 */ s32 sortKey; // comparator index for PointerList_Sort (D_8910D990): たかいじゅん on レベル set 2 and the rows sorted by level
    /* 0x007C */ s32 activeFilters; // filter bits: 1 level (set by the level filter), 2 type (タイプであつめる), 0x10 おなじタイプをあつめる (seen 0x13); 4 move, 8, 0x20 from LabPCList_ApplyFiltersAndSort
    /* 0x0080 */ s32 unk_0080;
    /* 0x0084 */ s32* columnWidths; // pixel width of each detail column: 92, 52, 88, 56, 72, 72 on page 1 (ニックネーム .. タイプ2), 108 the moves, 72 the stats
    /* 0x0088 */ s32 state; // sub-screen: 0 the list, 1 the source choice, 3 the sort popup, 5 the type filter, 7 the row popup, 8 どこへ?, 9 the box list
    /* 0x008C */ s32 focus; // 0 = the rows, 1 = the column headers (R moved the focus there, L back)
    /* 0x0090 */ char unk_0090[0x230 - 0x90];
    /* 0x0230 */ LabSourceSelectWindow sourceSelectWindow; // 「どこのポケモンを いちらん するか えらんでください。」 ("Choose whose Pokémon to list.") with てもち, ゲームボーイのボックス, 64カセットのボックス, OK; shown at state 1
    /* 0x03B4 */ Entry89100140 sources[3]; // @unverified: rows of sourceMatrix: てもち, ゲームボーイのボックス, 64カセットのボックス
    /* 0x0420 */ ByteMatrix sourceMatrix; // @unverified: over sources (func_89100140)
    /* 0x0430 */ char unk_0430[0x87B8 - 0x430];
    /* 0x87B8 */ void* rowBuffer[LAB_PC_LIST_MAX_ROWS]; // @unverified: storage of rows
    /* 0x8F00 */ void* filteredRowBuffer[LAB_PC_LIST_MAX_ROWS]; // @unverified: storage of filteredRows
    /* 0x9648 */ PointerList rows; // the listed Pokémon from the chosen sources: count 2 with てもち, 3 with all three sources
    /* 0x9654 */ LabPopupMenu popup; // the A-button popup on a row (ピカチュウをあつめる, おなじタイプをあつめる, いどうする, どうぐをつかう) and the header sort popup
    /* 0x96D0 */ LabPopupMenu subPopup; // drawn over popup: どこへ? (てもちのポケモン, ゲームボーイのボックス, 64カセットのボックス) after いどうする
    /* 0x974C */ LabPopupMenu subPopup2; // drawn over subPopup: ボックス1 to ボックス8 after ゲームボーイのボックス
    /* 0x97C8 */ u16 popupItemFlags[3][16]; // @unverified: Menu.itemFlags of popups
    /* 0x9828 */ u8 levelFilterMin; // lowest level of the level filter: あつめる with 011から100 stored 11; LabPCList_ResetFilterState sets 1
    /* 0x9829 */ u8 levelFilterMax; // highest level of the level filter: 100 (ResetFilterState sets 100)
    /* 0x982A */ char pad982A[2];
    /* 0x982C */ s32 unk_982C;
    /* 0x9830 */ LabLevelInputWindow levelInputWindow;
    /* 0x9918 */ s32 typeFilterCount; // number of types in typeFilterTypes: 1 after あつめる (gather) with でんき (Electric); 0 turns the type filter off
    /* 0x991C */ u8 typeFilterTypes[4]; // the types to gather: 0x17 (Electric) seen in play
    /* 0x9920 */ LabTypeFilterWindow typeFilterWindow; // @unverified: LabPCList_DrawTypeFilter
    /* 0x9B00 */ u8 moveFilterMoves[4]; // @unverified: the moves to gather (LabPCList_CommitMoveFilter, func_891097E4)
    /* 0x9B04 */ s32 moveFilterCount; // @unverified: number of moves in moveFilterMoves; 0 turns the move filter off
    /* 0x9B08 */ LabMoveFilterWindow moveFilterWindow; // @unverified: LabPCList_DrawMoveFilter
    /* 0x9E58 */ s32 unk_9E58;
    /* 0x9E5C */ s32 sameTypeFilterCount; // number of types in sameTypeFilterTypes for おなじタイプをあつめる (gather the same type): 1 for ピカチュウ (Pikachu)
    /* 0x9E60 */ u8 sameTypeFilterTypes[2]; // the chosen Pokémon's types: 0x17 (Electric) for ピカチュウ
    /* 0x9E62 */ char pad9E62[2];
    /* 0x9E64 */ char unk_9E64[4];
    /* 0x9E68 */ Slot89102930 unk_9E68[3];
    /* 0x9EBC */ char unk_9EBC[0xB15C - 0x9EBC];
    /* 0xB15C */ s32 page; // detail page 0-2 (ページおくり1/3); C-Right turned 1/3 to 2/3 and 3/3
    /* 0xB160 */ ScrollList list; // over rows (or filteredRows), 14 rows of 20 pixels; D-Down moved list.cursor to 1
    /* 0xB1A4 */ u16 rowFlags[LAB_PC_LIST_MAX_ROWS]; // @unverified: Menu.itemFlags of list
    /* 0xB548 */ s32* pageColumnStart; // first column index of each detail page: 0, 6, 10
    /* 0xB54C */ ChoiceCursor headerCursor; // the column header cursor (count 7, 2 = first detail column): D-Right moved it over the headers, 2 = レベル on page 3, 6 = タイプ1 on page 1
    /* 0xB558 */ s32 hasChanges; // became 1 when いどうする moved ピカチュウ from てもち to GB box 1; LabPCList_UpdateScreen then asks to save on exit
    /* 0xB55C */ char textBox[0xB594 - 0xB55C]; // @unverified: TextBox_Init, TextBox_Draw
    /* 0xB594 */ void* msg; // @unverified: message box given to LabPCList_MoveMonTo; last argument of LabPCList_InitListWindow
} LabPCListScreen; // size = 0xB598

/* The いちらん screen with the windows over it (LabPCList_UpdateScreen, LabPCList_DrawScreen). */
typedef struct LabPCList {
    /* 0x0000 */ s32 state; // @unverified: 0 = the list, 1 = savePrompt, 2 = itemWindow, 3 = messageWindow (LabPCList_UpdateScreen)
    /* 0x0004 */ LabPCListScreen listScreen;
    /* 0xB59C */ SavePrompt savePrompt; // @unverified: asks to save on exit when listScreen.hasChanges
    /* 0xB600 */ LabItemWindow itemWindow; // @unverified: opened by どうぐをつかう
    /* 0xB7B4 */ LabMessageWindow messageWindow; // @unverified: shows message after an item is used
    /* 0xB7E4 */ LabItemResult message; // @unverified: filled by LabPCList_ApplyVitaminItem and LabPCList_ApplyPpUpItem
} LabPCList; // size = 0xB7F4

#include "gfx_rect.h"
#include "poke_icon.h"

extern Gfx D_8910D028[];

// pokemon_list_2.c
void LabPCList_DrawPlainText(s32 arg0, s32 arg1, s8* arg2, s32 arg3, s32 arg4);

// pokemon_list_8.c
void LabPCList_Setup(void);

// popup_menus.c
void BattleMoveListWidget_DisableRestrictedMoves(LabMoveSelectWindow* arg0);
void BattleInfoWidget_UpdateEntryFlags(LabBoxListWindow* arg0);
void BattleInfoWidget_ApplyEntrySelection(LabSourceSelectWindow* arg0, s32 arg1);
void func_89105C54(LabSourceSelectWindow* arg0, s32 arg1, s32 arg2, s8* arg3, Color_RGBA8 arg4);
void func_89105E70(LabSourceSelectWindow* arg0, s32 arg1);
s32 func_891060BC(LabSourceSelectWindow* arg0);
s32 func_89106254(LabSourceSelectWindow* arg0);
void LabPCList_InitTypeFilter(LabTypeFilterWindow* arg0, s32 x, s32 y, s32* arg3);
void LabPCList_DrawTypeFilter(LabTypeFilterWindow* arg0);
s32 LabPCList_UpdateTypeFilter(LabTypeFilterWindow* arg0);
void LabPCList_CommitTypeFilter(LabTypeFilterWindow* arg0, s32* arg1);
void LabPCList_InitMoveFilter(LabMoveFilterWindow* arg0, s32 x, s32 y, u8* arg3);
void LabPCList_DrawMoveFilter(LabMoveFilterWindow* arg0);
s32 LabPCList_UpdateMoveFilter(LabMoveFilterWindow* arg0);
void LabPCList_CommitMoveFilter(LabMoveFilterWindow* arg0, u8* arg1);
void func_891053E0(void);
void func_89108F0C(void);
s32 Move_NormalizeDisplayIndex(s32 arg0);

// pokemon_list_9.c
s32 LabPCList_CompareByLevelAsc(LabMonEntry*, LabMonEntry*);
s32 LabPCList_CompareByLevelDesc(LabMonEntry*, LabMonEntry*);
s32 LabPCList_CompareByHpAsc(LabMonEntry*, LabMonEntry*);
s32 LabPCList_CompareByHpDesc(LabMonEntry*, LabMonEntry*);
s32 LabPCList_CompareByAttackAsc(LabMonEntry*, LabMonEntry*);
s32 LabPCList_CompareByAttackDesc(LabMonEntry*, LabMonEntry*);
s32 LabPCList_CompareByDefenseAsc(LabMonEntry*, LabMonEntry*);
s32 LabPCList_CompareByDefenseDesc(LabMonEntry*, LabMonEntry*);
s32 LabPCList_CompareBySpeedAsc(LabMonEntry*, LabMonEntry*);
s32 LabPCList_CompareBySpeedDesc(LabMonEntry*, LabMonEntry*);
s32 LabPCList_CompareBySpecialAsc(LabMonEntry*, LabMonEntry*);
s32 LabPCList_CompareBySpecialDesc(LabMonEntry*, LabMonEntry*);
s32 LabPCList_CompareById(LabMonEntry*, LabMonEntry*);
s32 LabPCList_CompareByOtName(LabMonEntry* arg0, LabMonEntry* arg1);
s32 LabPCList_CompareByNickname(LabMonEntry*, LabMonEntry*);
s32 LabPCList_CompareBySpeciesRawId(LabMonEntry*, LabMonEntry*);
int LabPCList_FilterByLevelRange(LabMonEntry* arg0, u8* arg1);
s32 LabPCList_FilterByAnyType(LabMonEntry* arg0, unk_func_8830867C_02C_C54_01C* arg1);
s32 LabPCList_FilterByAnyMove(LabMonEntry* arg0, unk_func_8830867C_02C_C54_024* arg1);
s32 LabPCList_FilterBySpeciesId(LabMonEntry* arg0, s32* arg1);
s32 LabPCList_FilterByExactTypePair(LabMonEntry* arg0, unk_func_8830867C_02C_C54_014* arg1);

// pokemon_list_10.c
s32 LabPCList_CanLearnMoveByLevelUp(s32 arg0, s32 arg1);
void LabPCList_FlattenEntries(PointerList*, unk_func_8830867C_02C_144*);
void LabPCList_ReadDeckCategory(unk_func_8830867C_02C_154*);
void LabPCList_WriteDeckCategory(unk_func_8830867C_02C_154*);

// functions defined in assembly
s32 LabPCList_CompareByPointer(LabMonEntry*, LabMonEntry*);
void LabPCList_LoadAllBoxes(unk_func_8830867C_02C_144*);
void LabPCList_SaveDirtyBoxes(unk_func_8830867C_02C_144*, s32);
void LabPCList_InitDeckCategories(unk_func_8830867C_02C_154*, MemoryPool* arg1);
void LabPCList_BuildTmHmList(PointerList*, unk_func_8830867C_02C_1A8*, unk_func_8830867C_02C_154*, s32, s32);
void PokeIcon_AttachDepthBuffer(PokeIconRenderer*, ModelLoadContext*, GfxImage*);

#endif // FRAGMENT_LAB_POKEMON_LIST_H
