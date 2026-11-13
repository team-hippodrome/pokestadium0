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
    /* 0x34 */ unk_func_88200FA0_030_038 unk_34;
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
    /* 0x40 */ unk_func_8830867C_02C_0CC unk_40;
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
    /* 0x68 */ unk_func_88205880_A030 unk_68;
    /* 0x74 */ u16 unk_74;
} unk_func_8830867C_040; // size = 0x78

typedef struct unk_func_8830867C_044_038 {
    /* 0x00 */ WidgetNode unk_00;
    /* 0x2C */ char unk2C[0x4];
    /* 0x30 */ unk_func_8830867C_044_038_030 unk_30;
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
    /* 0x34 */ unk_func_88201DA0_038 unk_34;
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
    /* 0x0C */ unk_func_8820BE14_06C unk_0C;
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
    /* 0x03C */ unk_func_88200FA0_030_038 unk_03C;
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
    /* 0x0CC */ unk_func_88200FA0_030_038 unk_0CC;
    /* 0x0D8 */ s32 unk_0D8;
    /* 0x0DC */ unk_func_8830867C_02C_0DC* unk_0DC;
    /* 0x0E0 */ s32 unk_0E0;
    /* 0x0E4 */ unk_func_8830867C_02C_0E4 unk_0E4[3];
    /* 0x144 */ unk_func_8830867C_02C_144 unk_144;
    /* 0x150 */ char unk150[0x4];
    /* 0x154 */ unk_func_8830867C_02C_154 unk_154[3];
    /* 0x1A8 */ unk_func_8830867C_02C_1A8 unk_1A8[3];
    /* 0x1D8 */ char unk1D8[0xA70];
    /* 0xC48 */ unk_func_88200FA0_030_038 unk_C48;
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

typedef struct unk_func_88316128 {
    /* 0x00 */ char unk00[0x8];
    /* 0x08 */ u8 unk_08;
    /* 0x09 */ char unk09[0xD];
    /* 0x16 */ u16 unk_16;
    /* 0x18 */ char unk18[0x14];
    /* 0x2C */ u8 unk_2C;
    /* 0x2E */ u16 unk_2E;
    /* 0x30 */ u16 unk_30;
    /* 0x32 */ u16 unk_32;
    /* 0x34 */ u16 unk_34;
    /* 0x36 */ u16 unk_36;
    /* 0x38 */ u8 unk_38;
    /* 0x39 */ char unk39[0xA];
    /* 0x43 */ u8 unk_43;
} unk_func_88316128; // size >= 0x44

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

typedef struct Ctx891012A8 {
    /* 0x0000 */ char unk0000[0x34];
    /* 0x0034 */ s32 right;
    /* 0x0038 */ char unk0038[0x84 - 0x38];
    /* 0x0084 */ s32* widths;
    /* 0x0088 */ char unk0088[0xB15C - 0x88];
    /* 0xB15C */ s32 mode;
    /* 0xB160 */ char unkB160[0xB548 - 0xB160];
    /* 0xB548 */ s32* ranges;
} Ctx891012A8;

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

typedef struct Ctx89100140 {
    /* 0x000 */ char unk000[0x3B4];
    /* 0x3B4 */ Entry89100140 unk_3B4[3];
    /* 0x420 */ char unk_420[1];
} Ctx89100140;

typedef struct Ctx89100294 {
    /* 0x0000 */ char unk0000[0x8C];
    /* 0x008C */ s32 unk8C;
    /* 0x0090 */ char unk0090[0xB15C - 0x90];
    /* 0xB15C */ s32 mode;
    /* 0xB160 */ char unkB160[0xB548 - 0xB160];
    /* 0xB548 */ s32* ranges;
    /* 0xB54C */ s32 unkB54C;
    /* 0xB550 */ s32 unkB550;
    /* 0xB554 */ s32 unkB554;
} Ctx89100294;

typedef struct Big891003A4 {
    /* 0x0000 */ char unk0000[0xB15C];
    /* 0xB15C */ s32 unkB15C;
    /* 0xB160 */ char unkB160[0x20];
    /* 0xB180 */ s32 unkB180;
    /* 0xB184 */ char unkB184[0x3C4];
    /* 0xB548 */ u8* unkB548;
    /* 0xB54C */ char unkB54C[0xC];
    /* 0xB558 */ s32 unkB558;
    /* 0xB55C */ char unkB55C[0x38];
    /* 0xB594 */ s32 unkB594;
} Big891003A4;

typedef struct Ctx89100688 {
    /* 0x0000 */ char unk0000[0x2C];
    /* 0x002C */ s32 x;
    /* 0x0030 */ s32 y;
    /* 0x0034 */ char unk0034[0x84 - 0x34];
    /* 0x0084 */ s32* widths;
    /* 0x0088 */ char unk0088[0xB15C - 0x88];
    /* 0xB15C */ s32 mode;
    /* 0xB160 */ char unkB160[0xB548 - 0xB160];
    /* 0xB548 */ s32* ranges;
    /* 0xB54C */ s32 unkB54C;
    /* 0xB550 */ s32 cursor;
} Ctx89100688;

/* Struct types that were defined identically in each of these files; this is
 * now the one definition they all include:
 * src/fragments/fragment016_252E10/89100020.c
 * src/fragments/fragment016_252E10/89100020_891012A8.c
 * src/fragments/fragment016_252E10/89100020_891019E4.c
 * src/fragments/fragment016_252E10/89100020_89102AB8.c
 */

typedef struct LabPCInitialStateFields {
    u8 pad0000[0x9828];
    u8 unk_9828;
    u8 unk_9829;
    u8 pad982A[2];
    s32 unk_982C;
    u8 pad9830[0xE8];
    s32 unk_9918;
    u8 pad991C[0x1E8];
    s32 unk_9B04;
} LabPCInitialStateFields;

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

typedef struct Rgba891024A4 { u8 r, g, b, a; } Rgba891024A4;

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
s32 LabPCList_CompareByLevelAsc(unk_func_88316128*, unk_func_88316128*);
s32 LabPCList_CompareByLevelDesc(unk_func_88316128*, unk_func_88316128*);
s32 LabPCList_CompareByHpAsc(unk_func_88316128*, unk_func_88316128*);
s32 LabPCList_CompareByHpDesc(unk_func_88316128*, unk_func_88316128*);
s32 LabPCList_CompareByAttackAsc(unk_func_88316128*, unk_func_88316128*);
s32 LabPCList_CompareByAttackDesc(unk_func_88316128*, unk_func_88316128*);
s32 LabPCList_CompareByDefenseAsc(unk_func_88316128*, unk_func_88316128*);
s32 LabPCList_CompareByDefenseDesc(unk_func_88316128*, unk_func_88316128*);
s32 LabPCList_CompareBySpeedAsc(unk_func_88316128*, unk_func_88316128*);
s32 LabPCList_CompareBySpeedDesc(unk_func_88316128*, unk_func_88316128*);
s32 LabPCList_CompareBySpecialAsc(unk_func_88316128*, unk_func_88316128*);
s32 LabPCList_CompareBySpecialDesc(unk_func_88316128*, unk_func_88316128*);
s32 LabPCList_CompareById(unk_func_88316128*, unk_func_88316128*);
s32 LabPCList_CompareByOtName(unk_func_88316128* arg0, unk_func_88316128* arg1);
s32 LabPCList_CompareByNickname(unk_func_88316128*, unk_func_88316128*);
s32 LabPCList_CompareBySpeciesRawId(unk_func_8830867C_02C_0CC*, unk_func_8830867C_02C_0CC*);
int LabPCList_FilterByLevelRange(unk_func_8830867C_02C_0CC* arg0, u8* arg1);
s32 LabPCList_FilterByAnyType(unk_func_8830867C_02C_0CC* arg0, unk_func_8830867C_02C_C54_01C* arg1);
s32 LabPCList_FilterByAnyMove(unk_func_8830867C_02C_0CC* arg0, unk_func_8830867C_02C_C54_024* arg1);
s32 LabPCList_FilterBySpeciesId(unk_func_8830867C_02C_0CC* arg0, s32* arg1);
s32 LabPCList_FilterByExactTypePair(unk_func_8830867C_02C_0CC* arg0, unk_func_8830867C_02C_C54_014* arg1);

// pokemon_list_10.c
s32 LabPCList_CanLearnMoveByLevelUp(s32 arg0, s32 arg1);
void LabPCList_FlattenEntries(unk_func_88200FA0_030_038*, unk_func_8830867C_02C_144*);
void LabPCList_ReadDeckCategory(unk_func_8830867C_02C_154*);
void LabPCList_WriteDeckCategory(unk_func_8830867C_02C_154*);

// functions defined in assembly
s32 LabPCList_CompareByPointer(unk_func_88316128*, unk_func_88316128*);
void LabPCList_LoadAllBoxes(unk_func_8830867C_02C_144*);
void LabPCList_SaveDirtyBoxes(unk_func_8830867C_02C_144*, s32);
void LabPCList_InitDeckCategories(unk_func_8830867C_02C_154*, MemoryPool* arg1);
void LabPCList_BuildTmHmList(unk_func_88200FA0_030_038*, unk_func_8830867C_02C_1A8*, unk_func_8830867C_02C_154*, s32, s32);
void PokeIcon_AttachDepthBuffer(unk_func_8001A024*, ModelLoadContext*, DepthBuffer*);

#endif // FRAGMENT_LAB_POKEMON_LIST_H
