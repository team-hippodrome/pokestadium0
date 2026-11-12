#ifndef ZERO_LAB_PC_ICONS_H
#define ZERO_LAB_PC_ICONS_H

/* Stadium Zero fragment019_293410. */
/* C ported from the Stadium 1 decomp: src/fragments/lab_pc_icons/lab_pc_icons.c. */

#include "fragments/lab_pc_icons/lab_pc_icons.h"
#include "display_object_textures.h"
#include "poke_icon.h"
#include "graphics_textures.h"
#include "ui_graphics.h"
#include "gb_data.h"
#include "table_view.h"
#include "text_system.h"
#include "gb_save.h"
#include "jpeg_stream.h"
#include "audio_sfx.h"
#include "memmap.h"
#include "memory.h"
#include "stage_loader.h"
#include "util.h"
#include "fragments/widget_tree/widget_tree.h"
#include "fragments/pokemon_lab_support/pokemon_lab_support.h"
typedef struct unk_D_88605B00 {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
} unk_D_88605B00;

#include "m2c_macros.h"

s32 LabPC_ComputeExpForLevel(s32 arg0, s32 arg1);

typedef struct Entry80066AA0 {
    /* 0x00 */ const char* str;
    /* 0x04 */ u8 r, g, b, a;
} Entry80066AA0;
extern Entry80066AA0 D_80066AA0[];
extern Entry80066AA0 D_80066AA8;
s32 func_8001FA30(u8);
void MonSummary_DrawStatusCondition(s32 arg0, s32 arg1, BattleMon* arg2);

extern M2C_UNK D_800734A8;
extern char D_8A21D850[];
extern char D_8A21D854[];
extern char D_8A21D858[];
void Font_SetColorForFlags(s32);
void MonSummary_DrawStatusCondition(s32, s32, BattleMon*);
void MonSummary_DrawHpLevel(s32 arg0, s32 arg1, BattleMon* arg2, s32 arg3);

extern s8* D_8A21DA50;
void UI_DrawTextureRgba16(s32 arg0, s32 arg1, s32 arg2);

/*
 * MonSummary_InitListWindow
 *
 * Initialises a record like Pokedex_InitEntryWindow does: Window_SetRect fills the first
 * five words with (arg1, arg2, 0x221, 0x168, 0), the words at +0x20, +0x24
 * and +0x28 are cleared and +0x14 is set to 0x1001.  It then calls
 * Menu_Init on the sub-object at arg0 + 0x2C with arg3, the area at
 * arg0 + 0x50, the callback MonSummary_DrawListRow and the constants 0x215 and 0x33.
 * What Menu_Init does is not established yet, so the roles of those
 * arguments are not named.
 */
M2C_UNK Menu_Init(s8 *, s32, s8 *, M2C_UNK *, s32, s32); /* extern */
/* MonSummary_DrawListRow is defined in lab_pc_icons.c. */

void MonSummary_InitListWindow(s8 *arg0, s32 arg1, s32 arg2, s32 arg3);

extern Color_RGBA8 D_8A203304;
void Ui_FillRectHighlighted(s32, s32, s32, s32, Color_RGBA8);

void MonSummary_DrawMenuRow(s32 arg0, s32 arg1, char* arg2, s32 arg3, s32 arg4);

s32 Particle_Field50_SetXZFromField7C_09BB4();                                /* extern */
M2C_UNK Menu_DrawItems(s8 *, s32, s32, M2C_UNK, s32); /* extern */

void MonSummary_DrawMenu(s8 *arg0);

typedef struct Color82000BC4 {
    u8 r, g, b, a;
} Color82000BC4;
typedef struct Entry80066AD8 {
    const char* str;
    Color82000BC4 color;
} Entry80066AD8;
extern Entry80066AD8 D_80066AD8[];
s32 Pokemon_GetTypeIndex(s32, s32);
void func_8001AB6C(void);
void func_8001A384(s32, s32);
void func_8001ABBC(void);
void func_8001AA9C(u8, u8, u8, u8);
void func_8001A944(s32, s32, const char*, ...);

void MonSummary_DrawTypeName(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

extern Gfx D_80060270[];
void func_80029028(s32, s32, s32, s32, Color_RGBA8);
void func_8001ABE8(void);
void func_8001AAE4(s32, s32, s32, s32);
void func_8001AC3C(void);
void MonSummary_DrawSpeciesName(s32 arg0, s32 arg1, BattleMon* arg2);

u8* func_800196F8(s32);
void BgStage_DrawFrame(void);
void func_8001B884(s32, s32, s32, s32, u8*, s32, s32);
extern s32 D_8A21DA4C;
void MonSummary_DrawModelPreview(s32 arg0, s32 arg1, s32 arg2);

M2C_UNK func_80019008(s32, s32, M2C_UNK);           /* extern */
M2C_UNK Ui_DrawTexturedDivider(s32, s32, s32, M2C_UNK *);    /* extern */
M2C_UNK func_80029864(s32, s32, s32, M2C_UNK *);    /* extern */
s32 Particle_Field50_SetXZFromField7C_09BB4();                                /* extern */
void MonSummary_DrawStats(s32, s32, BattleMon*);
void MonSummary_DrawHeader();
void MonSummary_DrawTrainerInfo(s32, s32, s32);
void func_8A2010C8(s32, s32, s32, s32);
void MonSummary_DrawSpeciesName();
s32 MonSummary_DrawMoveInfo(s32, s32, s32, s32);
void MonSummary_DrawModelPreview(s32, s32, s32);
extern s8 D_8007356C;
void MonSummary_DrawPage(s8 *arg0, s32 arg1);

s32 func_80022B40();                                /* extern */
s32 BattleMon_GetMoveIndexChecked();                /* extern */
M2C_UNK func_8003F6AC(M2C_UNK);                     /* extern */
extern s8 *D_800603C0;

s32 MonSummary_GetCButtonPage(s8 *arg0);

M2C_UNK Ui_DrawTintedScreenBackground(M2C_UNK, M2C_UNK, u8, u8, s32); /* extern */
extern M2C_UNK D_8A203300;

void MonSummary_DrawBackground(void);

s32 func_80020AFC(M2C_UNK, s32, M2C_UNK, M2C_UNK);  /* extern */
M2C_UNK func_80020C60(s32);                         /* extern */
s32 func_80020CE4(s32, s32, s32);                   /* extern */
extern s32 D_8A21DA40;

void func_8A202390(s8 *arg0);

void func_80022118(s32);
void func_80020DF0(s32, s32, s32);
s32 func_8002207C(s32);
void func_8002D7D4(s32);
void func_80022188(s32);
void MonSummary_DrawScreen(void*);

void LabPC_WriteDeckBack(s32* arg0, s32 arg1);

void func_8A202904(s8 *arg0, s32 arg1, s32 arg2);

void Cont_StartReadInputs(void);                            /* extern */
void Cont_ReadInputs(void);                            /* extern */
M2C_UNK func_800158C0();                            /* extern */
M2C_UNK func_8001B5F0();                            /* extern */
void MonSummary_DrawScreen(void*);
M2C_UNK MonSummary_UpdateScreen(M2C_UNK *);                   /* extern */
extern M2C_UNK D_8A21DA80;

void MonSummary_RunFrame(s32 arg0);

extern u8 D_81000000[];
extern u8 D_0015B1A0[];
extern u8 D_0015E220[];
extern u8 D_01000000[];
extern u8 D_002E0BE0[];
extern u8 D_002E2B90[];
extern u8 D_04000000[];
extern u8 D_00400F70[];
extern u8 D_004076E0[];
extern u8 D_88000000[];
extern u8 D_00235D70[];
extern u8 D_00238BD0[];
extern u8 D_003DCB60[];
extern u8 D_003F53C0[];
extern u8 D_8A203438[];
extern ModelLoadContext* D_8A21DA48;
extern BinArchive* D_8A21DA54;
extern void* D_8A21DA58;
extern void* D_8A21DA60[4];
void BattlePrep_RenderFrame(void);
s32 func_8A202F50(u8);
s32 MonSummary_Init(UNUSED s32 arg0, UNUSED s32 arg1, UNUSED s32 arg2);

#endif
