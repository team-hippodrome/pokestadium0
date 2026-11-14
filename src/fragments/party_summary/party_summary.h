/* Declarations for the party_summary fragment (src/fragments/party_summary/). */
#ifndef FRAGMENT_PARTY_SUMMARY_H
#define FRAGMENT_PARTY_SUMMARY_H

#include "global.h"
#include "m2c_macros.h"
#include "asset_archive.h"

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

extern Entry80066AA0 D_80066AA8;

extern char D_8A21D850[];

extern char D_8A21D854[];

extern char D_8A21D858[];

extern s8* D_8A21DA50;

extern Color_RGBA8 D_8A203304;

extern Entry80066AD8 D_80066AD8[];

extern Gfx D_80060270[];

extern s32 D_8A21DA4C;

extern M2C_UNK D_8A203300;

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

void PartyScreen_InitList(s8 *arg0, s32 arg1, s32 arg2, s32 arg3);
void PartyScreen_DrawActionMenuRow(s32 arg0, s32 arg1, char* arg2, s32 arg3, s32 arg4);
void PartyScreen_DrawActionMenu(s8 *arg0);
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
void MonSummary_DrawPage(s8 *arg0, s32 arg1);
s32 MonSummary_GetCButtonPage(s8 *arg0);
void PartyScreen_DrawBackground(void);
void func_8A202390(s8 *arg0);
void PartyScreen_Draw(void*);
void LabPC_WriteDeckBack(s32* arg0, s32 arg1);
void func_8A202904(s8 *arg0, s32 arg1, s32 arg2);
M2C_UNK PartyScreen_Update(M2C_UNK *);                   /* extern */
void PartyScreen_RunFrame(s32 arg0);
s32 func_8A202F50(u8);
s32 MonSummary_Init(UNUSED s32 arg0, UNUSED s32 arg1, UNUSED s32 arg2);

#endif // FRAGMENT_PARTY_SUMMARY_H
