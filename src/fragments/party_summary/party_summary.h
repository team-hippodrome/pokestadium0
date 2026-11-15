/* Declarations for the party_summary fragment (src/fragments/party_summary/). */
#ifndef FRAGMENT_PARTY_SUMMARY_H
#define FRAGMENT_PARTY_SUMMARY_H

#include "global.h"
#include "m2c_macros.h"
#include "asset_archive.h"
#include "menu.h"

typedef struct unk_D_84B1A598 {
    /* 0x0000 */ char unk0000[0x1];
    /* 0x0001 */ u8 unk_0001;
    /* 0x0002 */ u8 unk_0002;
    /* 0x0003 */ u8 unk_0003;
    /* 0x0004 */ GraphNode* unk_0004;
    /* 0x0008 */ DisplayObject unk_0008[128];
    /* 0xB408 */ BinArchive* unk_B408;
    /* 0xB40C */ BinArchive* unk_B40C;
} unk_D_84B1A598; // size >= 0xB410

typedef struct BattlePrepRuleWindow {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ char unk06[0x2];
} BattlePrepRuleWindow; // size >= 0x8

typedef struct unk_D_84B26640_010_010 {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ s8 unk_01;
    /* 0x02 */ s8 unk_02;
    /* 0x04 */ DisplayObject* unk_04;
    /* 0x08 */ GeoTextureBankNode* unk_08;
} unk_D_84B26640_010; // size = 0xC

typedef struct unk_D_84B26640 {
    /* 0x00 */ unk_D_84B26640_010 unk_00;
    /* 0x0C */ char unk0C[0x4];
    /* 0x10 */ unk_D_84B26640_010 unk_10;
    /* 0x1C */ BattlePrepRuleWindow unk_1C;
    /* 0x24 */ BattlePrepRuleWindow unk_24;
} unk_D_84B26640; // size = 0x30

typedef struct unk_func_84B067B4 {
    /* 0x000 */ char unk00[0x10];
    /* 0x010 */ char unk_010[4];
    /* 0x014 */ char unk14[0x24];
    /* 0x038 */ u16 unk_038;
    /* 0x03A */ char unk03A[0x1F6];
} unk_func_84B067B4; // size = 0x230

typedef struct unk_D_88605B00 {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
} unk_D_88605B00;

typedef struct Entry80066AA0 {
    /* 0x00 */ const char* str;
    /* 0x04 */ u8 r, g, b, a;
} Entry80066AA0;

typedef struct Color82000BC4 {
    u8 r, g, b, a;
} Color82000BC4;

typedef struct Entry80066AD8 {
    const char* str;
    Color82000BC4 color;
} Entry80066AD8;

#include "game_state.h"

/* The てもち (party) list window: one row per party Pokémon (PartyScreen_InitList, PartyScreen_DrawList). */
typedef struct PartyListWindow {
    /* 0x00 */ Window window; // @unverified: typed from the function it is passed to
    /* 0x2C */ Menu menu; // rows drawn by PartyScreen_DrawListRow; items = PartyScreen.monList; D-Down moved menu.cursor to カコ
    /* 0x50 */ u16 itemFlags[6]; // bit 3 = the Pokémon picked first when reordering: {0, 8, ...} after ならびかえ on カコ, cleared after the swap
} PartyListWindow; // size = 0x5C

/* The menu that opens on a party Pokémon (PartyScreen_InitActionMenu): 3 rows. */
typedef struct PartyActionMenuWindow {
    /* 0x00 */ Window window; // @unverified: typed from the function it is passed to
    /* 0x2C */ Menu menu; // rows drawn by PartyScreen_DrawActionMenuRow: つよさをみる, ならびかえ, やめる
    /* 0x50 */ PointerList items; // func_80027804 over the 3 strings D_8A203364 (count 3)
    /* 0x5C */ u16 itemFlags[3]; // @unverified: bit 0 = disabled (PartyScreen_UpdateActionMenu)
    /* 0x62 */ char pad62[0x2];
} PartyActionMenuWindow; // size = 0x64

/* The summary page of one party Pokémon (MonSummary_InitPageWindow, MonSummary_DrawPage). */
typedef struct MonSummaryWindow {
    /* 0x00 */ Window window; // @unverified: typed from the function it is passed to
    /* 0x2C */ s32 mon; // the BattleMon shown: &PartyScreen.mons[0] (ハナ) after つよさをみる on it
    /* 0x30 */ s32 moveSlot; // @unverified: the move picked with the C buttons (MonSummary_GetCButtonPage)
    /* 0x34 */ s32 modelLoaded; // 1 once func_80019008 loaded the Pokémon's model (the ピカチュウ model was up)
} MonSummaryWindow; // size = 0x38

/* The てもち (party) screen (func_8A2024D0, PartyScreen_Update, PartyScreen_Draw). */
typedef struct PartyScreen {
    /* 0x000 */ s32 state; // 1 = the list, 2 = the action menu, 3 = picking the second Pokémon of ならびかえ, 4 = the summary, 6 = the save prompt (seen in play)
    /* 0x004 */ s32 nextState; // becomes state once activeWindow has closed: 4 while the action menu closed for つよさをみる
    /* 0x008 */ Window* activeWindow; // the window taking input: listWindow at state 1, actionMenu at 2, summaryWindow at 4
    /* 0x00C */ Window* nextWindow; // becomes activeWindow once it has closed: summaryWindow while the action menu closed
    /* 0x010 */ PartyListWindow listWindow; // the てもち list window
    /* 0x06C */ s32 swapIndex; // reorder: the Pokémon picked first (listWindow.menu.cursor): 1 after ならびかえ on カコ
    /* 0x070 */ PartyActionMenuWindow actionMenu; // the A-button menu つよさをみる / ならびかえ / やめる
    /* 0x0D4 */ MonSummaryWindow summaryWindow; // the つよさをみる page
    /* 0x10C */ SavePrompt savePrompt; // 「ないようが へんこうされています」 at state 6 after a reorder
    /* 0x170 */ ByteMatrix monTable; // rows = mons, 0x50 bytes each: capacity 6, count 2
    /* 0x180 */ PointerList monList; // over monPointers, count 2; items of listWindow.menu
    /* 0x18C */ BattleMon* monPointers[6]; // swapped when reordering: {&mons[1], &mons[0]} after swapping ハナ and カコ, and the list showed カコ first
    /* 0x1A4 */ BattleMon mons[6]; // rows of monTable: mons[0] Lv25 ハナ, mons[1] Lv10 カコ
    /* 0x384 */ s32 dirty; // 1 after a reorder; B then opened the save prompt (state 6)
} PartyScreen; // size >= 0x388

extern Entry80066AA0 D_80066AA8;

extern char D_8A21D850[];

extern char D_8A21D854[];

extern char D_8A21D858[];

extern s8* D_8A21DA50;

extern Color_RGBA8 D_8A203304;

extern Entry80066AD8 D_80066AD8[];

extern Gfx D_80060270[];

extern s32 D_8A21DA4C;

extern Color_RGBA8 D_8A203300;

extern s32 D_8A21DA40;

extern M2C_UNK D_8A21DA80;

extern u8 D_0015B1A0[];

extern u8 D_0015E220[];

extern u8 D_003DCB60[];

extern u8 D_003F53C0[];

extern u8 D_8A203438[];

extern ModelLoadContext* D_8A21DA48;

extern BinArchive* D_8A21DA54;

extern void* D_8A21DA58;

extern void* D_8A21DA60[4];

// party_screen.c
void MonSummary_DrawStatusCondition(s32 arg0, s32 arg1, BattleMon* arg2);
void PartyScreen_DrawHpLevel(s32 arg0, s32 arg1, BattleMon* arg2, s32 arg3);
void UI_DrawTextureRgba16(s32 arg0, s32 arg1, s32 arg2);
/* PartyScreen_DrawListRow is defined in lab_pc_icons.c. */

void PartyScreen_InitList(PartyListWindow* arg0, s32 arg1, s32 arg2, s32 arg3);
void PartyScreen_DrawActionMenuRow(s32 arg0, s32 arg1, char* arg2, s32 arg3, s32 arg4);
void PartyScreen_DrawActionMenu(PartyActionMenuWindow* arg0);
void MonSummary_DrawTypeName(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void MonSummary_DrawSpeciesName(s32 arg0, s32 arg1, BattleMon* arg2);
void MonSummary_DrawStats(s32, s32, BattleMon*);
void MonSummary_DrawHeader();
void MonSummary_DrawTrainerInfo(s32, s32, s32);
void func_8A2010C8(s32, s32, s32, s32);

// mon_summary.c
void BattlePrep_RenderFrame(void);
s32 LabPC_ComputeExpForLevel(s32 arg0, s32 arg1);
void MonSummary_DrawModelPreview(s32 arg0, s32 arg1, s32 arg2);
s32 MonSummary_DrawMoveInfo(s32, s32, s32, s32);
void MonSummary_DrawPage(MonSummaryWindow* arg0, s32 arg1);
s32 MonSummary_GetCButtonPage(MonSummaryWindow* arg0);
void PartyScreen_DrawBackground(void);
void func_8A202390(ByteMatrix* arg0);
void PartyScreen_Draw(void*);
void LabPC_WriteDeckBack(s32* arg0, s32 arg1);
void func_8A202904(PartyScreen* arg0, s32 arg1, s32 arg2);
M2C_UNK PartyScreen_Update(PartyScreen*);
void PartyScreen_RunFrame(s32 arg0);
s32 func_8A202F50(u8);
s32 MonSummary_Init(UNUSED s32 arg0, UNUSED s32 arg1, UNUSED s32 arg2);

#endif // FRAGMENT_PARTY_SUMMARY_H
