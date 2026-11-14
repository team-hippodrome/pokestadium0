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

struct unk_func_8821421C_07C;

struct unk_func_8820E99C;

struct unk_func_8821421C_02C;

/* A two-digit number picker (func_8002B638). */
typedef struct DigitSelector {
    /* 0x00 */ s32 value; // @unverified: the ×count LabItem_DrawCountSelector prints (seen drawn as ×01 ... ×05 for ほのおのいし, fire stone)
    /* 0x04 */ s32 min; // @unverified: 1 in LabItem_InitCountSelector
    /* 0x08 */ s32 max; // @unverified: arg3 of LabItem_InitCountSelector
    /* 0x0C */ s32 digitCount; // @unverified: 2
    /* 0x10 */ s32 digit; // @unverified: the digit the cursor is on, 0 = ones, 1 = tens (the frame moves left by 0x16 per digit)
} DigitSelector; // size = 0x14

/* The ×count selector of the Lab item screens (LabItem_InitCountSelector), with a text box for a count
 * over the limit. */
typedef struct LabItemCountSelector {
    /* 0x00 */ s32 state; // @unverified: 1 while the text box D_89018474 is up
    /* 0x04 */ Window window;
    /* 0x30 */ s32 limit; // @unverified: arg4; a value above it opens the text box, then is set back to it
    /* 0x34 */ DigitSelector count;
    /* 0x48 */ s32 textBox; // first word of a TextBox (TextBox_Init, TextBox_Draw); its size is not established
} LabItemCountSelector;

/* A yes/no question in the Lab item screens (LabItem_InitConfirmWindow). */
typedef struct LabItemConfirmWindow {
    /* 0x00 */ Window window;
    /* 0x2C */ char unk2C[0x4];
    /* 0x30 */ char* text; // @unverified: printed at the top left (arg4)
    /* 0x34 */ LabeledButton yesButton; // @unverified: label D_89018460
    /* 0x70 */ LabeledButton noButton; // @unverified: label D_89018468
    /* 0xAC */ ChoiceCursor choice;
} LabItemConfirmWindow; // size = 0xB8

typedef struct unk_func_88208C5C {
    /* 0x00 */ WidgetNode unk_00;
    /* 0x2C */ unk_func_8850143C* unk_2C;
    /* 0x30 */ s32 unk_30;
    /* 0x34 */ s32 unk_34;
    /* 0x38 */ s32 unk_38;
} unk_func_88208C5C; // size = 0x3C

typedef struct unk_func_882079D8 {
    /* 0x00 */ WidgetNode unk_00;
    /* 0x2C */ unk_func_88205880_00D0* unk_2C;
} unk_func_882079D8; // size = 0x30

typedef struct unk_func_8820BE14_030 {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ MemoryPool* unk_04;
    /* 0x08 */ WidgetLinkHeader* unk_08;
    /* 0x0C */ unk_func_88205880_00D0* unk_0C;
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
    /* 0x002C */ unk_func_88205880_00D0* unk_002C;
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
    /* 0x90 */ struct unk_func_8821421C_07C* unk_90;
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

typedef struct unk_func_8821421C_07C {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ char unk_08[4]; // unk size
    /* 0x0C */ char unk0C[0x8];
} unk_func_8821421C_07C; // size = 0x14

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

typedef struct Rgba89000D50 {
    /* 0x00 */ u8 r, g, b, a;
} Rgba89000D50; // size = 0x4

typedef struct ColorPair890017FC {
    /* 0x0 */ Color_RGBA8 prim;
    /* 0x4 */ Color_RGBA8 env;
} ColorPair890017FC;

typedef struct Col89002C10 { u8 r, g, b, a; } Col89002C10;

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
void LabItem_LoadGamePakBoxSlots(unk_func_8821421C_07C* arg0);
s32 LabItem_FindOrAllocateGamePakBoxSlot(unk_func_8821421C_07C* arg0, s32 arg1, char* arg2);
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
