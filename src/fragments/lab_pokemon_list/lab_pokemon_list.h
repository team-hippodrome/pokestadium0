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

typedef struct unk_func_8830867C_02C_04C_018 {
    /* 0x00 */ char unk00[0x8];
    /* 0x08 */ WidgetNode* unk_08;
    /* 0x0C */ WidgetNode* unk_0C;
    /* 0x10 */ WidgetNode* unk_10;
    /* 0x14 */ WidgetNode* unk_14;
    /* 0x18 */ WidgetNode* unk_18;
    /* 0x1C */ WidgetNode* unk_1C;
} unk_func_8830867C_02C_04C_018; // size >= 0x20

typedef struct unk_func_8830867C_02C_04C {
    /* 0x00 */ char unk00[0xC];
    /* 0x0C */ WidgetGridMenuItem* unk_0C;
    /* 0x10 */ WidgetGridMenuInputCallback unk_10;
    /* 0x14 */ WidgetGridMenuSetStateCallback unk_14;
    /* 0x18 */ unk_func_8830867C_02C_04C_018* unk_18;
    /* 0x1C */ WidgetAnimatedFrame* unk_1C;
    /* 0x20 */ s32 unk_20;
    /* 0x24 */ s32 unk_24;
    /* 0x28 */ s32 unk_28;
    /* 0x2C */ s32 unk_2C;
    /* 0x30 */ char unk30[0x8];
    /* 0x38 */ s16 unk_38;
    /* 0x3A */ s16 unk_3A;
    /* 0x3C */ s16 unk_3C;
    /* 0x3E */ s16 unk_3E;
} unk_func_8830867C_02C_04C; // size = 0x40

typedef struct unk_func_8830867C_02C_050 {
    /* 0x00 */ WidgetNode unk_00;
    /* 0x2C */ struct unk_func_8830867C_02C* unk_2C;
} unk_func_8830867C_02C_050; // size = 0x30

typedef struct unk_func_8830867C_02C_0B4_030 {
    /* 0x00 */ WidgetNode unk_00;
    /* 0x2C */ char unk2C[0xC];
    /* 0x38 */ s32 unk_38;
    /* 0x3C */ char unk3C[0x18];
} unk_func_8830867C_02C_0B4_030; // size = 0x54

typedef struct unk_func_8830867C_02C_0B4 {
    /* 0x00 */ WidgetNode unk_00;
    /* 0x2C */ WidgetAnimatedPanel* unk_2C;
    /* 0x30 */ unk_func_8830867C_02C_0B4_030* unk_30;
    /* 0x34 */ PointerList unk_34;
} unk_func_8830867C_02C_0B4; // size = 0x40

typedef struct unk_func_8830867C_02C_0C0 {
    /* 0x00 */ unk_func_882173EC unk_00;
    /* 0x38 */ s32 unk_38;
} unk_func_8830867C_02C_0C0; // size = 0x3C

typedef struct unk_func_8830867C_034_03C_038_02C_000 {
    /* 0x00 */ char unk00[0x8];
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ char unk0C[0x10];
} unk_func_8830867C_034_03C_038_02C_000; // size = 0x1C

typedef struct unk_func_8830867C_034_03C_038_02C {
    /* 0x00 */ unk_func_8830867C_034_03C_038_02C_000* unk_00;
    /* 0x04 */ char unk04[0x4];
    /* 0x08 */ s32 unk_08;
} unk_func_8830867C_034_03C_038_02C; // size >= 0xC

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

typedef struct unk_func_8830867C_02C_144_000_alt {
    /* 0x00 */ char unk00[0x2C];
    /* 0x2C */ unk_func_8830867C_034_03C_038_02C unk_2C;
    /* 0x38 */ char unk_38[0x14];
    /* 0x4C */ unk_func_8830867C_034_03C_038_02C unk_4C;
} unk_func_8830867C_02C_144_000_alt; // size >= 0x58

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

typedef struct unk_func_8830867C_030_03C_034 {
    /* 0x00 */ u16 unk_00;
    /* 0x02 */ u16 unk_02;
    /* 0x04 */ char unk04[0x2];
    /* 0x06 */ u16 unk_06;
    /* 0x08 */ char unk08[0x2];
    /* 0x0A */ u16 unk_0A;
} unk_func_8830867C_030_03C_034; // size >= 0xC

typedef struct unk_func_8830867C_030 {
    /* 0x00 */ WidgetNode unk_00;
    /* 0x2C */ WidgetAnimatedPanel* unk_2C;
    /* 0x30 */ WidgetPoint unk_30;
    /* 0x34 */ WidgetPoint unk_34;
    /* 0x38 */ unk_func_885012A4* unk_38;
    /* 0x3C */ unk_func_88200FA0_030_030_1CEA00* unk_3C;
    /* 0x40 */ LabMonEntryList unk_40;
    /* 0x4C */ s32 unk_4C;
    /* 0x50 */ s32 unk_50;
} unk_func_8830867C_030; // size = 0x54

typedef struct unk_func_8830867C_034_034 {
    /* 0x00 */ WidgetNode unk_00;
    /* 0x2C */ char unk2C[0x4];
    /* 0x30 */ s32 unk_30;
} unk_func_8830867C_034_034; // size = 0x34

typedef struct unk_func_8830867C_034_03C_038 {
    /* 0x00 */ WidgetNode unk_00;
    /* 0x2C */ unk_func_8830867C_034_03C_038_02C* unk_2C;
    /* 0x30 */ char unk30[0x4];
    /* 0x34 */ u16* unk_34;
    /* 0x38 */ s32 unk_38;
    /* 0x3C */ char unk3C[0x8];
    /* 0x44 */ WidgetNode* unk_44;
    /* 0x48 */ char unk48[0xC];
} unk_func_8830867C_034_03C_038; // size = 0x54

typedef struct unk_func_8830867C_034_03C {
    /* 0x00 */ WidgetNode unk_00;
    /* 0x2C */ WidgetAnimatedPanel* unk_2C;
    /* 0x30 */ unk_func_88500994* unk_30;
    /* 0x34 */ unk_func_88500994* unk_34;
    /* 0x38 */ unk_func_8830867C_034_03C_038* unk_38[2];
    /* 0x40 */ char unk40[0x4];
} unk_func_8830867C_034_03C; // size = 0x44

typedef struct unk_func_8830867C_034_038 {
    /* 0x00 */ unk_func_8830867C_02C_048_000 unk_00;
    /* 0x24 */ struct unk_func_8830867C_034* unk_24;
} unk_func_8830867C_034_038; // size = 0x28

typedef struct unk_func_8830867C_034 {
    /* 0x00 */ WidgetNode unk_00;
    /* 0x2C */ WidgetAnimatedPanel* unk_2C;
    /* 0x30 */ unk_func_88200FA0_030_030_1CEA00* unk_30;
    /* 0x34 */ unk_func_8830867C_034_034* unk_34;
    /* 0x38 */ unk_func_8830867C_034_038* unk_38;
    /* 0x3C */ unk_func_8830867C_034_03C* unk_3C;
    /* 0x40 */ unk_func_8850878C* unk_40;
} unk_func_8830867C_034; // size = 0x44

typedef struct unk_func_8830867C_038_034 {
    /* 0x00 */ char** unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
} unk_func_8830867C_038_034; // size = 0xC

typedef struct unk_func_8830867C_038 {
    /* 0x00 */ WidgetNode unk_00;
    /* 0x2C */ WidgetAnimatedPanel* unk_2C;
    /* 0x30 */ unk_func_88200FA0_030_030_1CEA00* unk_30;
    /* 0x34 */ unk_func_8830867C_038_034 unk_34;
    /* 0x40 */ WidgetAnimatedPanel* unk_40;
} unk_func_8830867C_038; // size = 0x44

typedef struct unk_func_8830867C_03C_030 {
    /* 0x00 */ unk_func_8850878C* unk_00;
    /* 0x04 */ s32 unk_04;
} unk_func_8830867C_03C_030; // size = 0x8

typedef struct unk_func_8830867C_03C_04C {
    /* 0x00 */ unk_func_8830867C_02C_048_000 unk_00;
    /* 0x24 */ struct unk_func_8830867C_03C* unk_24;
} unk_func_8830867C_03C_04C; // size = 0x28

typedef struct unk_func_8830867C_03C {
    /* 0x00 */ WidgetNode unk_00;
    /* 0x2C */ WidgetAnimatedPanel* unk_2C;
    /* 0x30 */ unk_func_8830867C_03C_030 unk_30[2];
    /* 0x40 */ unk_func_8850878C* unk_40;
    /* 0x44 */ unk_func_8850878C* unk_44;
    /* 0x48 */ WidgetNode* unk_48;
    /* 0x4C */ unk_func_8830867C_03C_04C* unk_4C;
    /* 0x50 */ WidgetGridMenu* unk_50;
    /* 0x54 */ unk_func_8821421C_038_034* unk_54;
    /* 0x58 */ unk_func_8830867C_03C_058 unk_58[15];
    /* 0xD0 */ unk_func_8830867C_03C_0D0 unk_D0;
    /* 0xE0 */ u16 unk_E0;
} unk_func_8830867C_03C; // size = 0xE4

typedef struct unk_func_8830867C_040_030 {
    /* 0x00 */ unk_func_8850878C* unk_00;
    /* 0x04 */ u8* unk_04;
} unk_func_8830867C_040_030; // size = 0x8

typedef struct unk_func_8830867C_040_05C {
    /* 0x00 */ unk_func_8830867C_02C_048_000 unk_00;
    /* 0x24 */ struct unk_func_8830867C_040* unk_24;
} unk_func_8830867C_040_05C; // size = 0x28

typedef struct unk_func_8830867C_040 {
    /* 0x00 */ WidgetNode unk_00;
    /* 0x2C */ WidgetAnimatedPanel* unk_2C;
    /* 0x30 */ unk_func_8830867C_040_030 unk_30[4];
    /* 0x50 */ unk_func_8850878C* unk_50;
    /* 0x54 */ unk_func_8850878C* unk_54;
    /* 0x58 */ WidgetNode* unk_58;
    /* 0x5C */ unk_func_8830867C_040_05C* unk_5C;
    /* 0x60 */ WidgetGridMenu* unk_60;
    /* 0x64 */ unk_func_8821421C_038_034* unk_64;
    /* 0x68 */ PointerList unk_68;
    /* 0x74 */ u16 unk_74;
} unk_func_8830867C_040; // size = 0x78

typedef struct unk_func_8830867C_044_038 {
    /* 0x00 */ WidgetNode unk_00;
    /* 0x2C */ char unk2C[0x4];
    /* 0x30 */ UiNumberInput unk_30;
    /* 0x44 */ unk_func_8820E99C_030_044* unk_44;
} unk_func_8830867C_044_038; // size = 0x48

typedef struct unk_func_8830867C_044_040 {
    /* 0x00 */ unk_func_8830867C_02C_048_000 unk_00;
    /* 0x24 */ struct unk_func_8830867C_044* unk_24;
} unk_func_8830867C_044_040; // size = 0x28

typedef struct unk_func_8830867C_044 {
    /* 0x00 */ WidgetNode unk_00;
    /* 0x2C */ WidgetAnimatedPanel* unk_2C;
    /* 0x30 */ unk_func_8850878C* unk_30;
    /* 0x34 */ WidgetNode* unk_34;
    /* 0x38 */ unk_func_8830867C_044_038* unk_38;
    /* 0x3C */ unk_func_8830867C_044_038* unk_3C;
    /* 0x40 */ unk_func_8830867C_044_040* unk_40;
    /* 0x44 */ WidgetGridMenu* unk_44;
} unk_func_8830867C_044; // size = 0x48

typedef struct unk_func_8830867C_048_04C {
    /* 0x00 */ char unk00[0x1C];
    /* 0x1C */ s32 unk_1C;
    /* 0x20 */ char unk20[0x4];
} unk_func_8830867C_048_04C; // size = 0x24

typedef struct unk_func_8830867C_048_048 {
    /* 0x00 */ unk_func_8830867C_02C_048_000 unk_00;
    /* 0x24 */ struct unk_func_8830867C_048* unk_24;
} unk_func_8830867C_048_048; // size = 0x28

typedef struct unk_func_8830867C_048 {
    /* 0x00 */ WidgetNode unk_00;
    /* 0x2C */ WidgetAnimatedPanel* unk_2C;
    /* 0x30 */ WidgetAnimatedPanel* unk_30;
    /* 0x34 */ unk_func_88200FA0_030_030_1CEA00* unk_34;
    /* 0x38 */ unk_func_88200FA0_030_030_1CEA00* unk_38[2];
    /* 0x40 */ unk_func_88500994* unk_40;
    /* 0x44 */ unk_func_88500994* unk_44;
    /* 0x48 */ unk_func_8830867C_048_048* unk_48;
    /* 0x4C */ unk_func_8830867C_048_04C* unk_4C;
    /* 0x50 */ char unk_50[0x80];
} unk_func_8830867C_048; // size = 0xD0

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

typedef struct unk_func_8830867C_04C_030_02C {
    /* 0x00 */ unk_func_8830867C_04C_030_02C_000* unk_00;
    /* 0x04 */ char unk04[0x4];
    /* 0x08 */ s32 unk_08;
} unk_func_8830867C_04C_030_02C; // size >= 0xC

typedef struct unk_func_8830867C_04C_030 {
    /* 0x00 */ WidgetNode unk_00;
    /* 0x2C */ unk_func_8830867C_04C_030_02C* unk_2C;
    /* 0x30 */ char unk30[0x4];
    /* 0x34 */ u16* unk_34;
    /* 0x38 */ s32 unk_38;
    /* 0x3C */ char unk3C[0x2];
    /* 0x3E */ s16 unk_3E;
    /* 0x40 */ char unk40[0x18];
    /* 0x58 */ s32 unk_58;
    /* 0x5C */ char unk5C[0x14];
} unk_func_8830867C_04C_030; // size = 0x70

typedef void (*unk_func_8830867C_04C_078_030_040)();

typedef struct unk_func_8830867C_04C_078_030 {
    /* 0x00 */ WidgetNode unk_00;
    /* 0x2C */ void* unk_2C;
    /* 0x30 */ s32 unk_30;
    /* 0x34 */ u16* unk_34;
    /* 0x38 */ s32 unk_38;
    /* 0x3C */ s16 unk_3C;
    /* 0x3E */ s16 unk_3E;
    /* 0x40 */ unk_func_8830867C_04C_078_030_040 unk_40;
    /* 0x44 */ WidgetAnimatedFrame* unk_44;
    /* 0x48 */ s16 unk_48;
    /* 0x4A */ s16 unk_4A;
    /* 0x4C */ s16 unk_4C;
    /* 0x4E */ s16 unk_4E;
    /* 0x50 */ s16 unk_50;
    /* 0x52 */ s16 unk_52;
} unk_func_8830867C_04C_078_030; // size = 0x54

typedef struct unk_func_8830867C_04C_078_044 {
    /* 0x00 */ unk_func_88201DA0_034* unk_00;
    /* 0x04 */ s32 unk_04;
} unk_func_8830867C_04C_078_044; // size = 0x8

typedef struct unk_func_8830867C_04C_078 {
    /* 0x00 */ WidgetNode unk_00;
    /* 0x2C */ WidgetAnimatedPanel* unk_2C;
    /* 0x30 */ unk_func_8830867C_04C_078_030* unk_30;
    /* 0x34 */ ByteMatrix unk_34;
    /* 0x44 */ unk_func_8830867C_04C_078_044 unk_44[1];
    /* 0x4C */ char unk4C[0x18];
} unk_func_8830867C_04C_078; // size = 0x64

typedef struct unk_func_8830867C_04C_02C {
    /* 0x00 */ WidgetNode unk_00;
    /* 0x2C */ s32 unk_2C;
    /* 0x30 */ s32 unk_30;
} unk_func_8830867C_04C_02C; // size = 0x34

typedef struct unk_func_8830867C_04C_080 {
    /* 0x00 */ unk_func_8830867C_02C_048_000 unk_00;
    /* 0x24 */ struct unk_func_8830867C_04C* unk_24;
} unk_func_8830867C_04C_080; // size = 0x28

typedef struct unk_func_8830867C_04C {
    /* 0x00 */ WidgetNode unk_00;
    /* 0x2C */ unk_func_8830867C_04C_02C* unk_2C;
    /* 0x30 */ unk_func_8830867C_04C_030* unk_30;
    /* 0x34 */ unk_func_88500994* unk_34;
    /* 0x38 */ char unk_38[4];
    /* 0x3C */ char unk3C[0x3C];
    /* 0x78 */ unk_func_8830867C_04C_078* unk_78;
    /* 0x7C */ unk_func_8830867C_030* unk_7C;
    /* 0x80 */ unk_func_8830867C_04C_080* unk_80;
    /* 0x84 */ s32 unk_84;
    /* 0x88 */ BattleMon* unk_88; // maybe unk_func_8830867C_02C_0CC_000_008
    /* 0x8C */ s32 unk_8C;
    /* 0x90 */ unk_func_88503298* unk_90;
} unk_func_8830867C_04C; // size = 0x94

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

typedef struct unk_func_8830867C_02C_C54 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ u8 unk_08;
    /* 0x09 */ u8 unk_09;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ unk_func_8830867C_02C_C54_014 unk_14;
    /* 0x1C */ unk_func_8830867C_02C_C54_01C unk_1C;
    /* 0x24 */ unk_func_8830867C_02C_C54_024 unk_24;
    /* 0x2C */ u8 unk_2C;
} unk_func_8830867C_02C_C54; // size = 0x30

typedef struct unk_func_8830867C_054 {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ MemoryPool* unk_04;
    /* 0x08 */ WidgetNode* unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ WidgetNode* unk_14;
} unk_func_8830867C_054; // size = 0x18

typedef struct unk_func_8830867C_02C_0E4 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ ByteMatrix unk_0C;
    /* 0x1C */ s32 unk_1C;
} unk_func_8830867C_02C_0E4; // size = 0x20

typedef struct unk_func_8830867C_02C_0DC {
    /* 0x00 */ s32* unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ char unk0C[0xC];
    /* 0x18 */ s32 unk_18;
    /* 0x1C */ char unk1C[0xC];
    /* 0x28 */ s32 unk_28;
} unk_func_8830867C_02C_0DC; // size >= 0x2C

typedef struct unk_func_8830867C_02C {
    /* 0x000 */ WidgetNode unk_000;
    /* 0x02C */ WidgetAnimatedPanel* unk_02C;
    /* 0x030 */ unk_func_8850B254* unk_030;
    /* 0x034 */ unk_func_8830867C_02C_034* unk_034;
    /* 0x038 */ unk_func_88500994* unk_038;
    /* 0x03C */ PointerList unk_03C;
    /* 0x048 */ unk_func_8830867C_02C_048* unk_048;
    /* 0x04C */ unk_func_8830867C_02C_04C* unk_04C;
    /* 0x050 */ unk_func_8830867C_02C_050* unk_050;
    /* 0x054 */ WidgetNode* unk_054;
    /* 0x058 */ WidgetNode* unk_058;
    /* 0x05C */ WidgetNode* unk_05C;
    /* 0x060 */ WidgetNode* unk_060;
    /* 0x064 */ WidgetNode* unk_064;
    /* 0x068 */ WidgetNode* unk_068;
    /* 0x06C */ WidgetNode* unk_06C;
    /* 0x070 */ WidgetNode* unk_070;
    /* 0x074 */ WidgetNode* unk_074;
    /* 0x078 */ WidgetNode* unk_078;
    /* 0x07C */ WidgetNode* unk_07C;
    /* 0x080 */ WidgetNode* unk_080;
    /* 0x084 */ WidgetNode* unk_084;
    /* 0x088 */ WidgetNode* unk_088;
    /* 0x08C */ unk_func_8830867C_030* unk_08C;
    /* 0x090 */ unk_func_88509F48* unk_090;
    /* 0x094 */ unk_func_8830867C_034* unk_094;
    /* 0x098 */ unk_func_8830867C_038* unk_098;
    /* 0x09C */ unk_func_8830867C_03C* unk_09C;
    /* 0x0A0 */ unk_func_8830867C_040* unk_0A0;
    /* 0x0A4 */ unk_func_8830867C_044* unk_0A4;
    /* 0x0A8 */ unk_func_8830867C_048* unk_0A8;
    /* 0x0AC */ unk_func_8830867C_04C* unk_0AC;
    /* 0x0B0 */ unk_func_889000C4* unk_0B0;
    /* 0x0B4 */ unk_func_8830867C_02C_0B4* unk_0B4;
    /* 0x0B8 */ unk_func_8850CD44* unk_0B8;
    /* 0x0BC */ unk_func_882173EC* unk_0BC;
    /* 0x0C0 */ unk_func_8830867C_02C_0C0* unk_0C0;
    /* 0x0C4 */ unk_func_882173EC* unk_0C4;
    /* 0x0C8 */ unk_func_882173EC* unk_0C8;
    /* 0x0CC */ PointerList unk_0CC;
    /* 0x0D8 */ s32 unk_0D8;
    /* 0x0DC */ unk_func_8830867C_02C_0DC* unk_0DC;
    /* 0x0E0 */ s32 unk_0E0;
    /* 0x0E4 */ unk_func_8830867C_02C_0E4 unk_0E4[3];
    /* 0x144 */ unk_func_8830867C_02C_144 unk_144;
    /* 0x150 */ char unk150[0x4];
    /* 0x154 */ unk_func_8830867C_02C_154 unk_154[3];
    /* 0x1A8 */ unk_func_8830867C_02C_1A8 unk_1A8[3];
    /* 0x1D8 */ char unk1D8[0xA70];
    /* 0xC48 */ PointerList unk_C48;
    /* 0xC54 */ unk_func_8830867C_02C_C54 unk_C54;
    /* 0xC84 */ unk_func_8830867C_02C_C54 unk_C84;
    /* 0xCB4 */ s32 unk_CB4;
    /* 0xCB8 */ s32 unk_CB8;
    /* 0xCBC */ s32 unk_CBC;
    /* 0xCC0 */ s32 unk_CC0;
    /* 0xCC4 */ s32 unk_CC4;
    /* 0xCC8 */ s32 unk_CC8;
    /* 0xCCC */ unk_func_8850878C* unk_CCC;
    /* 0xCD0 */ s32 unk_CD0;
    /* 0xCD4 */ s32* unk_CD4;
    /* 0xCD8 */ FragmentEntry unk_CD8;
    /* 0xCDC */ unk_func_8830867C_054* unk_CDC;
} unk_func_8830867C_02C; // size = 0xCE0

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
    /* 0x10 */ char unk_10[0x10];
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
    /* 0x2C */ s32 anchorX; // @unverified: LabPCList_PlacePopup puts the popup next to this rectangle
    /* 0x30 */ s32 anchorY;
    /* 0x34 */ s32 anchorW;
    /* 0x38 */ s32 anchorH;
    /* 0x3C */ s32 unk_3C;
    /* 0x40 */ Menu menu;
    /* 0x64 */ PointerList itemList; // @unverified: the item strings: フシギダネをあつめる, おなじタイプをあつめる, いどうする, どうぐをつかう
    /* 0x70 */ s32 title; // @unverified: text of the title tab when nonzero (LabPCList_InitPopupMenu sets window style 0x800)
    /* 0x74 */ s32 limitX; // @unverified: LabPCList_PlacePopup keeps the popup left of this
    /* 0x78 */ s32 limitY; // @unverified: and above this
} LabPopupMenu; // @unverified: size = 0x7C

typedef struct Slot89102930 {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ char unk08[0x14];
} Slot89102930; // @unverified: size = 0x1C

#define LAB_PC_LIST_MAX_ROWS 466

/* The いちらん (Pokémon list) screen of the Lab PC (LabPCList_InitListWindow). Its functions used to
 * take it through a dozen partial views (Ctx891012A8, Ctx89100294, Big891003A4, ...). */
typedef struct LabPCListScreen {
    /* 0x0000 */ Window window; // @unverified: 564x382 (LabPCList_InitListWindow)
    /* 0x002C */ WindowFrame listFrame; // @unverified: the rows area, 552x302 at (6, 0x3A) in the window
    /* 0x004C */ WindowFrame headerFrame; // @unverified: the column header strip, 552x30 at (6, 6)
    /* 0x006C */ PointerList filteredRows; // @unverified: what PointerList_Filter leaves of rows (LabPCList_ApplyFiltersAndSort)
    /* 0x0078 */ s32 sortKey; // @unverified: index into D_8910D990, the comparator given to PointerList_Sort
    /* 0x007C */ s32 activeFilters; // @unverified: LabPCList_ApplyFiltersAndSort: 1 level, 2 type, 4 move, 8 and 0x10 (unk_9E58, unk_9E5C), 0x20
    /* 0x0080 */ s32 unk_0080;
    /* 0x0084 */ s32* columnWidths; // @unverified: pixel width of each detail column (LabPCList_GetColumnCursorX)
    /* 0x0088 */ s32 state; // @unverified: LabPCList_UpdateHeaderCursor sets 2 when it opens the sort menu
    /* 0x008C */ s32 focus; // @unverified: 0 = the rows, 1 = the header buttons, 2 = the column headers (R moved the focus to ニックネーム, ID, おや, ばしょ)
    /* 0x0090 */ char unk_0090[0x230 - 0x90];
    /* 0x0230 */ char sourceSelectWindow[0x3B4 - 0x230]; // @unverified: 「どこのポケモンを いちらん するか えらんでください。」 (LabPCList_UpdateSourceSelect)
    /* 0x03B4 */ Entry89100140 sources[3]; // @unverified: rows of sourceMatrix: てもち, ゲームボーイのボックス, 64カセットのボックス
    /* 0x0420 */ ByteMatrix sourceMatrix; // @unverified: over sources (func_89100140)
    /* 0x0430 */ char unk_0430[0x87B8 - 0x430];
    /* 0x87B8 */ void* rowBuffer[LAB_PC_LIST_MAX_ROWS]; // @unverified: storage of rows
    /* 0x8F00 */ void* filteredRowBuffer[LAB_PC_LIST_MAX_ROWS]; // @unverified: storage of filteredRows
    /* 0x9648 */ PointerList rows; // @unverified: the listed Pokémon, built from the chosen sources (func_89109C6C)
    /* 0x9654 */ LabPopupMenu popup; // @unverified: the A-button popup on a row: フシギダネをあつめる, おなじタイプをあつめる, いどうする, どうぐをつかう
    /* 0x96D0 */ LabPopupMenu subPopup; // @unverified: drawn over popup (LabPCList_DrawWindows)
    /* 0x974C */ LabPopupMenu subPopup2; // @unverified: drawn over subPopup
    /* 0x97C8 */ u16 popupItemFlags[3][16]; // @unverified: Menu.itemFlags of popups
    /* 0x9828 */ u8 unk_9828;
    /* 0x9829 */ u8 unk_9829;
    /* 0x982A */ char pad982A[2];
    /* 0x982C */ s32 unk_982C;
    /* 0x9830 */ char levelInputWindow[0x9918 - 0x9830]; // @unverified: レベルのにゅうりょく (LabPCList_InitLevelInputWindow)
    /* 0x9918 */ s32 unk_9918; // @unverified: LabPCList_CommitTypeFilter writes here; 0 turns the type filter off
    /* 0x991C */ s32 unk_991C;
    /* 0x9920 */ char typeFilterWindow[0x9B00 - 0x9920]; // @unverified: LabPCList_DrawTypeFilter
    /* 0x9B00 */ s32 unk_9B00; // @unverified: LabPCList_CommitMoveFilter writes here
    /* 0x9B04 */ s32 unk_9B04;
    /* 0x9B08 */ char moveFilterWindow[0x9E58 - 0x9B08]; // @unverified: LabPCList_DrawMoveFilter
    /* 0x9E58 */ s32 unk_9E58;
    /* 0x9E5C */ s32 unk_9E5C; // @unverified: number of types in unk_9E60/unk_9E61 for the おなじタイプをあつめる filter (LabPCList_UpdateMonMenu)
    /* 0x9E60 */ u8 unk_9E60;
    /* 0x9E61 */ u8 unk_9E61;
    /* 0x9E62 */ char pad9E62[2];
    /* 0x9E64 */ char unk_9E64[4];
    /* 0x9E68 */ Slot89102930 unk_9E68[3];
    /* 0x9EBC */ char unk_9EBC[0xB15C - 0x9EBC];
    /* 0xB15C */ s32 page; // @unverified: detail page 0-2 (ページおくり1/3); C-Right turned 1/3 to 2/3, the move columns
    /* 0xB160 */ ScrollList list; // @unverified: over rows (or filteredRows), 14 rows of 20 pixels
    /* 0xB1A4 */ u16 rowFlags[LAB_PC_LIST_MAX_ROWS]; // @unverified: Menu.itemFlags of list
    /* 0xB548 */ s32* pageColumnStart; // @unverified: first column index of each detail page (LabPCList_GetColumnCursorX)
    /* 0xB54C */ ChoiceCursor headerCursor; // @unverified: the header buttons; D-Left/D-Right moved it between ニックネーム, ID, おや, ばしょ
    /* 0xB558 */ s32 hasChanges; // @unverified: set by LabPCList_MoveMonTo and after an item is used; LabPCList_UpdateScreen then asks to save on exit
    /* 0xB55C */ char textBox[0xB594 - 0xB55C]; // @unverified: TextBox_Init, TextBox_Draw
    /* 0xB594 */ void* msg; // @unverified: message box given to LabPCList_MoveMonTo; last argument of LabPCList_InitListWindow
} LabPCListScreen; // size = 0xB598

#include "gfx_rect.h"
#include "poke_icon.h"

extern Gfx D_8910D028[];

// pokemon_list_2.c
void LabPCList_DrawPlainText(s32 arg0, s32 arg1, s8* arg2, s32 arg3, s32 arg4);

// pokemon_list_8.c
void LabPCList_Setup(void);

// popup_menus.c
void BattleMoveListWidget_DisableRestrictedMoves(unk_func_8830867C_04C_078* arg0);
void BattleInfoWidget_UpdateEntryFlags(unk_func_8830867C_034* arg0);
void BattleInfoWidget_ApplyEntrySelection(unk_func_8830867C_034* arg0, s32 arg1);
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
