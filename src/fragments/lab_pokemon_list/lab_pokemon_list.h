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

/* The レベルのにゅうりょく (level input) window of the いちらん screen: 「001 から 100」
 * (LabPCList_InitLevelInputWindow). */
typedef struct LabLevelInputWindow {
    /* 0x00 */ Window window;
    /* 0x2C */ LabeledButton clearButton; // かいじょ; flags bit 0 (greyed out) when no level filter is active
    /* 0x68 */ LabeledButton gatherButton; // あつめる
    /* 0xA4 */ DigitSelector minLevel; // @unverified: 3 digits, 1 to 100 (LabPCList_InitLevelInputWindow)
    /* 0xB8 */ DigitSelector maxLevel; // @unverified: 3 digits, 1 to 100
    /* 0xCC */ ChoiceCursor cursor; // @unverified: count 2
    /* 0xD8 */ s32 unk_D8;
    /* 0xDC */ s32 column; // @unverified: L/R position: 0-2 the digits of minLevel, 3-5 of maxLevel, 6 the buttons (LabPCList_UpdateLevelInput)
    /* 0xE0 */ s32 unk_E0;
    /* 0xE4 */ s32 focus; // @unverified: 0 = minLevel, 1 = maxLevel, 2 = the buttons
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
    /* 0x0230 */ LabSourceSelectWindow sourceSelectWindow; // @unverified: 「どこのポケモンを いちらん するか えらんでください。」 (LabPCList_UpdateSourceSelect)
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
    /* 0x9828 */ u8 levelFilterMin; // @unverified: play note on LabPCList_RunLevelFilter: あつめる with 006から100 stored 6 here
    /* 0x9829 */ u8 levelFilterMax; // @unverified: and 100 here; LabPCList_ResetFilterState sets 1 and 100
    /* 0x982A */ char pad982A[2];
    /* 0x982C */ s32 unk_982C;
    /* 0x9830 */ LabLevelInputWindow levelInputWindow;
    /* 0x9918 */ s32 typeFilterCount; // @unverified: number of types in typeFilterTypes (LabPCList_CommitTypeFilter); 0 turns the type filter off
    /* 0x991C */ u8 typeFilterTypes[4]; // @unverified: the types to gather (LabPCList_CommitTypeFilter, func_89109720)
    /* 0x9920 */ LabTypeFilterWindow typeFilterWindow; // @unverified: LabPCList_DrawTypeFilter
    /* 0x9B00 */ u8 moveFilterMoves[4]; // @unverified: the moves to gather (LabPCList_CommitMoveFilter, func_891097E4)
    /* 0x9B04 */ s32 moveFilterCount; // @unverified: number of moves in moveFilterMoves; 0 turns the move filter off
    /* 0x9B08 */ LabMoveFilterWindow moveFilterWindow; // @unverified: LabPCList_DrawMoveFilter
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
