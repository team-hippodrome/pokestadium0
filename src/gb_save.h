/* Declarations for src/gb_save.c. */
#ifndef GB_SAVE_H
#define GB_SAVE_H

#include "global.h"
#include "m2c_macros.h"

// A number changed with the d-pad, wrapping at both ends (Ui_AdjustSteppedRangeSelection, Ui_AdjustSteppedScrollSelection).
// Merges unk_func_8002E128_arg0 and unk_func_8002DE78_arg0.
typedef struct UiRangeValue {
    /* 0x00 */ s32 value; // @unverified: Ui_AdjustSteppedRangeSelection
    /* 0x04 */ s32 min; // @unverified: Ui_AdjustSteppedRangeSelection
    /* 0x08 */ s32 max; // @unverified: Ui_AdjustSteppedRangeSelection
    /* 0x0C */ s32 step; // @unverified: up/down add or subtract it, left/right ten times it (Ui_AdjustSteppedRangeSelection)
} UiRangeValue; // size = 0x10

// A menu cursor that wraps (Ui_AdjustVerticalSelection, Ui_AdjustHorizontalSelection).
// Merges unk_func_8002DCB8_arg0 and unk_func_8002DD98_arg0.
typedef struct UiSelection {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 index; // @unverified: Ui_AdjustVerticalSelection
    /* 0x08 */ s32 count; // @unverified: Ui_AdjustVerticalSelection
} UiSelection; // size = 0xC

// What GbSave_BuildPortSummary fills for one port; the trainer name follows the struct.
typedef struct GbSavePortSummary {
    /* 0x00 */ s32 isUnavailable; // @unverified: 1 when GbSave_GetSaveState is not 0
    /* 0x04 */ s32 gameType; // @unverified: GbSave_GetPortGame
    /* 0x08 */ s32 trainerId; // @unverified: GbSave_GetTrainerId
} GbSavePortSummary; // size = 0xC

// A number entered digit by digit (Ui_AdjustNumericSelection). Merges unk_func_8830867C_044_038_030
// and unk_func_8820E99C_030_030.
typedef struct UiNumberInput {
    /* 0x00 */ s32 value; // @unverified: Ui_AdjustNumericSelection
    /* 0x04 */ s32 min; // @unverified: Ui_AdjustNumericSelection
    /* 0x08 */ s32 max; // @unverified: Ui_AdjustNumericSelection
    /* 0x0C */ s32 digitCount; // @unverified: limit of cursorDigit (Ui_AdjustNumericSelection)
    /* 0x10 */ s32 cursorDigit; // @unverified: the digit up/down change, 0 the ones (Ui_AdjustNumericSelection)
} UiNumberInput; // size = 0x14

typedef struct unk_D_8007596C {
    /* 0x00 */ u16 unk_00;
    /* 0x02 */ u16 unk_02;
} unk_D_8007596C; // size = 0x4

#define BTN_A           0x8000

#define BTN_B           0x4000

#include "fragments/battle/battle.h"

// gb_save.c
void GbSave_BuildPortSummary(GbSavePortSummary* arg0, s32 arg1);
s32 Ui_AdjustVerticalSelection(UiSelection* arg0, s32 arg1);
s32 Ui_HandleVerticalSelectionInput(s32 arg0);
s32 Ui_AdjustHorizontalSelection(UiSelection* arg0, s32 arg1);
void Ui_AdjustSteppedScrollSelection(UiRangeValue* arg0);
s32 Ui_AdjustNumericSelection(UiNumberInput* arg0, s32 arg1);
s32 Ui_HandleNumericSelectionInput(UiNumberInput* arg0);
s32 Ui_AdjustSteppedRangeSelection(UiRangeValue* arg0);
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
