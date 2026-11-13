#ifndef _FRAGMENT17_H_
#define _FRAGMENT17_H_

#include "global.h"

typedef struct unk_D_86B0DAE0_000 {
    /* 0x00 */ u16 unk_00;
    /* 0x02 */ u16 unk_02;
    /* 0x04 */ u16 unk_04;
    /* 0x06 */ u16 unk_06;
    /* 0x08 */ u16 unk_08;
    /* 0x0A */ u16 unk_0A;
    /* 0x0C */ u16 unk_0C;
    /* 0x0E */ u16 unk_0E;
    /* 0x10 */ u16 unk_10;
    /* 0x12 */ u16 unk_12;
    /* 0x14 */ u16 unk_14;
    /* 0x16 */ u16 unk_16;
} unk_D_86B0DAE0_000; // size = 0x18

typedef struct unk_D_86B0DAE0 {
    /* 0x00 */ unk_D_86B0DAE0_000 unk_00;
    /* 0x18 */ unk_D_86B0DAE0_000 unk_18;
} unk_D_86B0DAE0; // size = 0x30

typedef struct unk_D_86B0FA7C {
    /* 0x00 */ CameraNode* unk_00;
    /* 0x04 */ Vec3f unk_04;
    /* 0x10 */ s16 unk_10;
    /* 0x12 */ s16 unk_12;
    /* 0x14 */ char unk14[0x2];
    /* 0x16 */ s16 unk_16;
    /* 0x18 */ s16 unk_18;
    /* 0x1C */ f32 unk_1C;
    /* 0x20 */ f32 unk_20;
    /* 0x24 */ s16 unk_24;
    /* 0x26 */ s16 unk_26;
    /* 0x28 */ char unk28[0x2];
    /* 0x2A */ s16 unk_2A;
    /* 0x2C */ s16 unk_2C;
    /* 0x30 */ f32 unk_30;
    /* 0x34 */ f32 unk_34;
    /* 0x38 */ f32 unk_38;
    /* 0x3C */ f32 unk_3C;
    /* 0x40 */ f32 unk_40;
    /* 0x44 */ f32 unk_44;
    /* 0x48 */ char unk48[0x34];
} unk_D_86B0FA7C; // size = 0x7C

typedef struct unk_D_86B0C264 {
    /* 0x00 */ Vec3f unk_00;
    /* 0x0C */ s16 unk_0C;
    /* 0x0E */ s16 unk_0E;
    /* 0x10 */ u16 unk_10;
    /* 0x10 */ u16 unk_12;
    /* 0x14 */ u16 unk_14;
    /* 0x14 */ u16 unk_16;
    /* 0x18 */ s16 unk_18;
    /* 0x1A */ s16 unk_1A;
} unk_D_86B0C264; // size = 0x1C

s32 Diorama_LogoRotateColorCallback(s32 arg0, GraphNode* arg1);
s32 Diorama_ScaleRotateCallbackA(s32 arg0, GraphNode* arg1);
s32 Diorama_ScaleRotateCallbackB(s32 arg0, GraphNode* arg1);
s32 Diorama_GroupStateCallback(s32 arg0, GraphNode* arg1);
void BattleAi_CalcAttack(void);
void func_8216D9D0(void);
void func_8216DA30(void);

s32 Completion_LightAngleCallbackA(s32 arg0, GraphNode* arg1);
s32 Completion_LightAngleCallbackB(s32 arg0, GraphNode* arg1);

s32 Stage_ShowIntro(void);

void UI_DrawTextureRgba16(u8* arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4);

void MewtwoIntro_DrawOverlay(void);

void func_8216DA50(void);
void BattleAnim_ClearEffectState(void);
void func_8216DA58(void);

#endif // _FRAGMENT17_H_
