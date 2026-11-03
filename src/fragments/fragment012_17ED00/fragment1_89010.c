/* Stadium Zero fragment012_17ED00. */
/* C ported from the Stadium 1 decomp: src/fragments/1/fragment1_89010.c, src/fragments/battle_engine/battle_engine_343BA0.c. */

#include "global.h"

#include "fragments/battle_engine/battle_engine.h"
#include "gallery.h"
#include "gfx_buffer.h"
#include "math.h"
#include "math_util.h"
extern u8* sBattleAnimAssetPointers[256];
extern s16 sBattleAnimResourceList[0x10];
extern arg1_func_80019420* sBattleAnimResourceTablePointers[40];
extern s16 D_8219CAC0;
extern s16 D_8219CAC2;
extern Mtx D_8219CAC8;
extern s16 D_8219CB08;
extern s16 D_8219CB0A;
extern s16 D_8219CB0C;
extern s16 D_8219CB0E;
extern s16 D_8219CB10;
extern s16 D_8219CB12;
extern s16 D_8219CB14;
extern s16 D_8219CB16;
extern s16 D_8219CB18;
extern s16 D_8219CB1A;
extern const char D_821978C8[];

#include "m2c_macros.h"

void func_821323D0(UNUSED s32 arg0);
void BattleAnim_NoopUpdateHook(void);

void func_821323D0(UNUSED s32 arg0) {
}

void BattleAnim_NoopUpdateHook(void) {
}

void func_82131880(CameraNode* arg0);
void func_821319FC(CameraNode* arg0);
void func_82131A3C(CameraNode* arg0);
void func_82131C64(CameraNode* arg0);
void func_82131D24(CameraNode* arg0);
void func_82131EC4(CameraNode* arg0);
void func_8213201C(CameraNode* arg0);
void func_82132088(CameraNode* arg0);
void func_821321A4(CameraNode* arg0);
void func_82132238(CameraNode* arg0);
void func_8213233C(CameraNode* arg0);

void BattleScene_UpdateIntroSequence(CameraNode* arg0) {
    switch (sBattleScene.scene->unk_20) {
        case 0:
            func_82131880(arg0);

        case 1:
            func_821319FC(arg0);
            break;

        case 2:
            func_82131A3C(arg0);
            break;

        case 3:
            func_82131C64(arg0);
            break;

        case 4:
            func_82131D24(arg0);
            break;

        case 5:
            func_82131EC4(arg0);
            break;

        case 6:
            func_8213201C(arg0);
            break;

        case 7:
            func_82132088(arg0);
            break;

        case 8:
            func_821321A4(arg0);
            break;

        case 9:
            func_82132238(arg0);
            break;

        case 10:
            func_8213233C(arg0);
            break;

        case 11:
            func_821323D0((s32)arg0);
            break;
    }
}

extern s32 D_82199DE0;
extern s8 *D_8219A5A0;
void func_8212188C(void);
void func_8000D41C(Vec3f*, f32, f32, f32);
void func_8210BCF0(Vec3f*, Vec3f*, s8*, s8*, s8*);
M2C_UNK func_800407B0(M2C_UNK, M2C_UNK, M2C_UNK);
void func_80041914(s32, s32);
void func_82136918(u8*, s32);
void func_821324D8(CameraNode* arg0) {
    func_8212188C();
    func_8000D41C(&arg0->view.targetPosition, 0.0f, 425.0f, 0.0f);
    func_8000D41C(&arg0->view.eyePosition, -0.15f, 15.0f, 64.8f);
    func_8210BCF0(&arg0->view.targetPosition, &arg0->view.eyePosition, D_8219A5A0 + 0x74, D_8219A5A0 + 0x58, D_8219A5A0 + 0x5A);
    (*(u8**)&D_82199DE0)[1] &= ~1;
    ((u8**)&D_82199DE0)[1][1] &= ~1;
    func_800407B0(4, 0, 0);
    func_80041914(*(u8*)(*(u8**)(((u8**)&D_82199DE0)[0] + 0x860) + 2), *(u8*)(*(u8**)(((u8**)&D_82199DE0)[1] + 0x860) + 2));
    func_82136918(*(u8**)((*(u8**)&D_82199DE0) + 0x85C), 3);
    M2C_FIELD(D_8219A5A0, s32 *, 0x20)++;
}

s32 func_82101FD4(s32);                             /* extern */
extern s32 D_82199DE0;
extern s8 *D_8219A5A0;

void func_821325E8(s32 arg0) {
    if (func_82101FD4(D_82199DE0) != 0) {
        M2C_FIELD(D_8219A5A0, s32 *, 0x20) = (s32) (M2C_FIELD(D_8219A5A0, s32 *, 0x20) + 1);
    }
}

#ifdef NON_MATCHING
/* TODO: decompile func_82132628; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_82132628.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_821326E4; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_821326E4.s")
#endif

#ifdef NON_MATCHING
// Matches the ROM, but uses rodata data that is not placed in this file yet.
void func_821324D8(CameraNode* arg0);
void func_82132628(CameraNode* arg0);
void func_821326E4(CameraNode* arg0);

void func_821328DC(CameraNode* arg0) {
    switch (sBattleScene.scene->unk_20) {
        case 0:
            func_821324D8(arg0);

        case 1:
            func_821325E8((s32)arg0);
            break;

        case 2:
            func_82132628(arg0);
            break;

        case 3:
            func_821326E4(arg0);
            break;

        case 4:
            func_82131C64(arg0);
            break;

        case 5:
            func_82131D24(arg0);
            break;

        case 6:
            func_82131EC4(arg0);
            break;

        case 7:
            func_8213201C(arg0);
            break;

        case 8:
            func_82132088(arg0);
            break;

        case 9:
            func_821321A4(arg0);
            break;

        case 10:
            func_82132238(arg0);
            break;

        case 11:
            func_8213233C(arg0);
            break;

        case 12:
            func_821323D0((s32)arg0);
            break;
    }
}
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_821328DC.s")
#endif
