/* Declarations for src/gb_save.c. */
#ifndef GB_SAVE_H
#define GB_SAVE_H

#include "global.h"
#include "controller.h"
#include "game_state.h"
#include "m2c_macros.h"

/* One Pokémon of a team in a team list: a flags word, then the Pokémon read from the save
 * (Registration_ReadTeam, FreeBattle_ReadTeam). */
typedef struct TeamMonSlot {
    /* 0x00 */ s32 flags; // @unverified: cleared for each Pokémon read; Free Battle tests bits 0x1, 0x10, 0x26 and 0x40
    /* 0x04 */ BattleMon mon; // @unverified: filled by func_80020CE4 from the save
} TeamMonSlot; // size = 0x54

/* The rect, style and fill of a window: all that Window_SetRect and Window_DrawFrame touch. Some
 * windows draw a second, inner frame of only these fields (MainMenuPromptWindow.textFrame). */
typedef struct WindowFrame {
    /* 0x00 */ s32 x; // 64 for the Free Battle rule window; poking 200 moved it right
    /* 0x04 */ s32 y;
    /* 0x08 */ s32 width; // 408 for the rule window
    /* 0x0C */ s32 height;
    /* 0x10 */ s32 unk_10; // cleared by Window_SetRect
    /* 0x14 */ s32 style; // @unverified: Window_DrawFrame: bit 0 = no fill, 2|4 = two-color fill, 0x800 = title tab from `title`
    /* 0x18 */ Color_RGBA8 color; // @unverified: fill color (Window_DrawFrame)
    /* 0x1C */ Color_RGBA8 color2; // @unverified: second fill color with style bits 2|4
} WindowFrame; // size = 0x20

/* The header of a window (Window_SetRect, Window_DrawFrame and the screens that embed one). */
typedef struct Window {
    /* 0x00 */ WindowFrame frame;
    /* 0x20 */ char* title; // text of the title tab with style 0x800: 「たいせんルールせんたく」 in the rule window
    /* 0x24 */ s32 animTimer; // @unverified: frames into the open or close animation; 7 starts the close (state 3, then 4 at 11)
    /* 0x28 */ s32 state; // 0..4, 2 while the rule window is open; the Free Battle windows take input only in states 1 and 2; 4 = closed
} Window; // size = 0x2C

/* A two-choice row of labeled buttons (はい/いいえ, yes/no) driven by func_8002B390. */
typedef struct ChoiceCursor {
    /* 0x00 */ Controller* controller; // @unverified: gControllers (D_800603C0), as in Menu.controller
    /* 0x04 */ s32 cursor; // @unverified: 0 = the first button, 1 = the second (MainMenu_UpdateMessageWindow)
    /* 0x08 */ s32 count; // @unverified: 2 in MainMenu_InitMessageWindow
} ChoiceCursor; // size = 0xC

/* A button with a label (Window_InitLabeled, Window_DrawLabeled). */
typedef struct LabeledButton {
    /* 0x00 */ s32 x;
    /* 0x04 */ s32 y;
    /* 0x08 */ s32 width;
    /* 0x0C */ s32 height;
    /* 0x10 */ s32 flags; // @unverified: OR'd into the label's color flags by Window_DrawLabeled; bit 3 = highlighted
    /* 0x14 */ char unk14[0xC];
    /* 0x20 */ Color_RGBA8 color; // @unverified: highlight fill (Window_DrawLabeled)
    /* 0x24 */ s32 unk_24;
    /* 0x28 */ s32 fontSize; // @unverified: first argument of func_8001A384 in Window_DrawLabeled; 8 by default
    /* 0x2C */ s32 labelX; // @unverified: label x offset in the button; 6 by default
    /* 0x30 */ s32 labelY; // @unverified: label y offset in the button; 2 by default
    /* 0x34 */ s32 unk_34;
    /* 0x38 */ char* label;
} LabeledButton; // size = 0x3C

typedef struct unk_func_8002EBD8_arg0 {
    /* 0x00 */ char unk00[0x8];
    /* 0x08 */ u16 unk_08;
} unk_func_8002EBD8_arg0; // size >= 0xA

typedef struct unk_func_8002E128_arg0 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
} unk_func_8002E128_arg0; // size >= 0x10

typedef struct unk_func_8002DCB8_arg0 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
} unk_func_8002DCB8_arg0; // size >= 0xC

typedef struct unk_func_8002DD98_arg0 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
} unk_func_8002DD98_arg0; // size >= 0xC

typedef struct unk_func_8002DE78_arg0 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
} unk_func_8002DE78_arg0; // size >= 0x10

typedef struct unk_func_8002D860 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
} unk_func_8002D860; // size = 0xC

typedef struct unk_func_8820E99C_030_030 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
} unk_func_8820E99C_030_030; // size = 0x14

typedef struct unk_func_8830867C_044_038_030 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
} unk_func_8830867C_044_038_030; // size = 0x14

typedef struct unk_D_8007596C {
    /* 0x00 */ u16 unk_00;
    /* 0x02 */ u16 unk_02;
} unk_D_8007596C; // size = 0x4

#define BTN_A           0x8000

#define BTN_B           0x4000

#include "fragments/battle/battle.h"

// gb_save.c
void GbSave_BuildPortSummary(unk_func_8002D860* arg0, s32 arg1);
s32 Ui_AdjustVerticalSelection(unk_func_8002DCB8_arg0* arg0, s32 arg1);
s32 Ui_HandleVerticalSelectionInput(s32 arg0);
s32 Ui_AdjustHorizontalSelection(unk_func_8002DD98_arg0* arg0, s32 arg1);
void Ui_AdjustSteppedScrollSelection(unk_func_8002DE78_arg0* arg0);
s32 Ui_AdjustNumericSelection(unk_func_8830867C_044_038_030* arg0, s32 arg1);
s32 Ui_HandleNumericSelectionInput(unk_func_8820E99C_030_030* arg0);
s32 Ui_AdjustSteppedRangeSelection(unk_func_8002E128_arg0* arg0);
s32 GbSave_GameToCategoryIndex(s32 arg0);
Color_RGBA8 Color_InterpolateFromGray(Color_RGBA8 arg0, f32 arg1);
s32 BattleMon_CountMoves(u8* arg0);
void BattleInfoWidget_DrawLabel(s32 arg0, s32 arg1, char* arg2, s32 arg3, s32 arg4);
void Particle_SetVelocityXZFromRotationY(Particle* arg0);
s32 Particle_Field7C_SetXZFromField74AngleY_0B278(void *arg0);
void Font_SetColorForFlags(s32);
s32 BattleMon_GetMoveIndexChecked();                /* extern */
void Trade_DrawSolidFillRect(s32 arg0, s32 arg1, s32 arg2, s32 arg3, Color_RGB8 arg4);

// functions defined in assembly
s32 Trade_DrawBox3DModel(s32 arg0, GraphNode* arg1);

#endif // GB_SAVE_H
