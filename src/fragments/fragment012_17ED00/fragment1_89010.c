/* Fixed-layout split; original translation-unit boundaries remain unconfirmed. */
#include "fragment1_89010.h"

void func_821323D0(UNUSED s32 arg0) {
}

void BattleAnim_NoopUpdateHook(void) {
}

void BattleScene_UpdateIntroSequence(CameraNode* arg0) {
    switch (sBattleScene.scene->phaseStep) {
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

s32 func_821217DC(s32);
void func_8000EEBC(Vec3f*, Vec3f*, f32, s32, s32);
void func_82132628(CameraNode* arg0) {
    if (func_821217DC(0xF) != 0) {
        sBattleScene.scene->phaseStep++;
    }
    M2C_FIELD(sBattleScene.scene, s16*, 0x5A) += 0x2D8;
    func_8000EEBC(&arg0->view.targetPosition, &arg0->view.eyePosition, M2C_FIELD(sBattleScene.scene, f32*, 0x74), M2C_FIELD(sBattleScene.scene, s16*, 0x58), M2C_FIELD(sBattleScene.scene, s16*, 0x5A));
    func_8210BCF0(&arg0->view.targetPosition, &arg0->view.eyePosition, D_8219A5A0 + 0x74, D_8219A5A0 + 0x58, D_8219A5A0 + 0x5A);
    M2C_FIELD(D_8219A5A0, f32*, 0x98) = 0.0f;
}

f32 func_8000F23C(f32, f32, f32, f32);
void func_8210C1A8(f32*, f32, f32);
void func_80041374(s32, s32);
M2C_UNK func_82108A88(s8*, M2C_UNK, M2C_UNK);
M2C_UNK func_821365B0(M2C_UNK, s8*, s8*, M2C_UNK, s32);
void func_821326E4(CameraNode* arg0) {
    s32 sp3C;
    s16 sp3A;
    s16 sp38;

    if (M2C_FIELD(D_8219A5A0, s32*, 0x14) == 0x3C) {
        func_80041374(4, 0x3C);
    }
    M2C_FIELD(D_8219A5A0, f32*, 0x98) = func_8000F23C(M2C_FIELD(D_8219A5A0, f32*, 0x98), 0.02f, 0.0007f, 0.0007f);
    (*(u8**)&D_82199DE0)[1] &= ~1;
    ((u8**)&D_82199DE0)[1][1] &= ~1;
    func_8210C1A8((f32*)(D_8219A5A0 + 0x74), 1250.0f, M2C_FIELD(D_8219A5A0, f32*, 0x98) / 2);
    func_8210C1A8(&arg0->view.targetPosition.y, 100.0f, M2C_FIELD(D_8219A5A0, f32*, 0x98));
    func_8210C1A8(&arg0->view.eyePosition.y, 450.0f, M2C_FIELD(D_8219A5A0, f32*, 0x98));
    M2C_FIELD(D_8219A5A0, s16*, 0x5A) += 0x2D8;
    func_8210BCF0(&arg0->view.targetPosition, &arg0->view.eyePosition, (s8*)&sp3C, (s8*)&sp3A, (s8*)&sp38);
    func_8000EEBC(&arg0->view.targetPosition, &arg0->view.eyePosition, M2C_FIELD(D_8219A5A0, f32*, 0x74), sp3A, M2C_FIELD(D_8219A5A0, s16*, 0x5A));
    if (func_821217DC(0x6E) != 0) {
        func_800407B0(1, 0xFE, 0);
        func_8000D41C(&arg0->view.targetPosition, 0.0f, 75.0f, 0.0f);
        func_8000D41C(&arg0->view.eyePosition, -1.79f, 0.075f, 155.2f);
        func_82108A88(*(s8**)&D_82199DE0, 1, 0);
        func_821365B0(8, *(s8**)&D_82199DE0, *(s8**)&D_82199DE0, 0xFF, 0xFF);
        M2C_FIELD(D_8219A5A0, s32*, 0x20)++;
    }
}
