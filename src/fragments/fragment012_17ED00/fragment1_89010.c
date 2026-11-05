/* Fixed-layout split; original translation-unit boundaries remain unconfirmed. */
#include "fragment1_89010.h"

void func_821323D0(UNUSED s32 arg0) {
}

void BattleAnim_NoopUpdateHook(void) {
}

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

void func_821325E8(s32 arg0) {
    if (func_82101FD4(D_82199DE0) != 0) {
        M2C_FIELD(D_8219A5A0, s32 *, 0x20) = (s32) (M2C_FIELD(D_8219A5A0, s32 *, 0x20) + 1);
    }
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_82132628.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_821326E4.s")
