/* Fixed-layout split; original translation-unit boundaries remain unconfirmed. */
#include "fragment1_89010.h"

/**
 * Battle opening, step 12: does nothing (the opening has ended).
 */
void BattleScene_OpeningStepNop(UNUSED s32 arg0) {
}

void BattleAnim_NoopUpdateHook(void) {
}

/**
 * Seen in play (2026-11-13) (scene mode forced to 4): step 0 was run by func_82134374 at scene
 * start, so the first update already saw step 1; the case 0 fall-through into case 1 was not
 * reached. Steps 1 to 3 ran in order (wait for assets, spinning overhead shot, then the side 1
 * throw). A COM Free Battle uses mode 8 (BattleScene_OpeningStepInitCamera and the other
 * OpeningStep functions) instead.
 */
void BattleScene_UpdateIntroSequence(CameraNode* arg0) {
    switch (sBattleScene.scene->phaseStep) {
        case 0:
            BattleScene_IntroStepInitOverheadCamera(arg0);

        case 1:
            BattleScene_IntroStepWaitForAssets(arg0);
            break;

        case 2:
            BattleScene_IntroStepSpinOverheadCamera(arg0);
            break;

        case 3:
            BattleScene_OpeningStepThrowSide1(arg0);
            break;

        case 4:
            BattleScene_OpeningStepLandSide0Ball(arg0);
            break;

        case 5:
            func_82131EC4(arg0);
            break;

        case 6:
            BattleScene_OpeningStepWaitSide0Ball(arg0);
            break;

        case 7:
            BattleScene_SendOutSide0(arg0);
            break;

        case 8:
            BattleScene_OpeningStepWaitSide0SendOut(arg0);
            break;

        case 9:
            BattleScene_SendOutSide1(arg0);
            break;

        case 10:
            BattleScene_OpeningStepWaitSide1SendOut(arg0);
            break;

        case 11:
            BattleScene_OpeningStepNop((s32)arg0);
            break;
    }
}

extern s32 D_82199DE0;
extern s8 *D_8219A5A0;
void func_8212188C(void);
void func_8000D41C(Vec3f*, f32, f32, f32);
void func_8210BCF0(Vec3f*, Vec3f*, s8*, s8*, s8*);
s32 Audio_PlayCommand(u32 arg0, s32 arg1, s32 arg2);
void func_80041914(s32, s32);
void func_82136918(u8*, s32);
/**
 * Battle opening, step 0 (BattleScene_RunOpeningSendOut): puts the camera high above the field
 * (target y 425), hides both Pokemon and starts the opening music (audio command 4).
 * Seen in play (COM battle opening): the screen opens on the stadium lights overhead.
 */
void BattleScene_OpeningStepInitCamera(CameraNode* arg0) {
    func_8212188C();
    func_8000D41C(&arg0->view.targetPosition, 0.0f, 425.0f, 0.0f);
    func_8000D41C(&arg0->view.eyePosition, -0.15f, 15.0f, 64.8f);
    func_8210BCF0(&arg0->view.targetPosition, &arg0->view.eyePosition, D_8219A5A0 + 0x74, D_8219A5A0 + 0x58, D_8219A5A0 + 0x5A);
    (*(u8**)&D_82199DE0)[1] &= ~1;
    ((u8**)&D_82199DE0)[1][1] &= ~1;
    Audio_PlayCommand(4, 0, 0);
    func_80041914(*(u8*)(*(u8**)(((u8**)&D_82199DE0)[0] + 0x860) + 2), *(u8*)(*(u8**)(((u8**)&D_82199DE0)[1] + 0x860) + 2));
    func_82136918(*(u8**)((*(u8**)&D_82199DE0) + 0x85C), 3);
    M2C_FIELD(D_8219A5A0, s32 *, 0x20)++;
}

/**
 * Battle opening, step 1: waits until the battle assets have loaded
 * (BattleAnim_PollAssetLoadBusyFlags).
 * Seen in play (2026-11-13) in a COM Free Battle opening it ran on the two frames after
 * BattleScene_OpeningStepInitCamera, then the step moved to 2.
 */
void BattleScene_OpeningStepWaitForAssets(s32 arg0) {
    if (func_82101FD4(D_82199DE0) != 0) {
        M2C_FIELD(D_8219A5A0, s32 *, 0x20) = (s32) (M2C_FIELD(D_8219A5A0, s32 *, 0x20) + 1);
    }
}

s32 func_821217DC(s32);
void func_8000EEBC(Vec3f*, Vec3f*, f32, s32, s32);
/**
 * Battle opening, step 2: orbits the high camera around the field for 15 frames.
 * Seen in play (2026-11-13) in a COM Free Battle opening the high camera circled the field: scene
 * rotationY rose by about 0x2D8 per call (-20, 702, 1427, ...) for 15 calls, then the step moved to
 * 3.
 */
void BattleScene_OpeningStepOrbitCamera(CameraNode* arg0) {
    if (func_821217DC(0xF) != 0) {
        sBattleScene.scene->phaseStep++;
    }
    M2C_FIELD(sBattleScene.scene, s16*, 0x5A) += 0x2D8;
    func_8000EEBC(&arg0->view.targetPosition, &arg0->view.eyePosition, sBattleScene.scene->unk_74, sBattleScene.scene->rotationX, M2C_FIELD(sBattleScene.scene, s16*, 0x5A));
    func_8210BCF0(&arg0->view.targetPosition, &arg0->view.eyePosition, D_8219A5A0 + 0x74, D_8219A5A0 + 0x58, D_8219A5A0 + 0x5A);
    M2C_FIELD(D_8219A5A0, f32*, 0x98) = 0.0f;
}

f32 func_8000F23C(f32, f32, f32, f32);
void func_8210C1A8(f32*, f32, f32);
void func_80041374(s32, s32);
M2C_UNK ActivePokemon_SetModelTransform(s8*, M2C_UNK, M2C_UNK);
M2C_UNK func_821365B0(M2C_UNK, s8*, s8*, M2C_UNK, s32);
/**
 * Battle opening, step 3: eases the camera down to field level over 110 frames, then starts side
 * 0's Poke Ball throw (model transform 1, effect list 8).
 * Seen in play: the camera comes down off the lights over about 220 frames, and side 0's Poke
 * Ball trail follows at once.
 */
void BattleScene_OpeningStepLowerCameraAndThrowSide0(CameraNode* arg0) {
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
        Audio_PlayCommand(1, 0xFE, 0);
        func_8000D41C(&arg0->view.targetPosition, 0.0f, 75.0f, 0.0f);
        func_8000D41C(&arg0->view.eyePosition, -1.79f, 0.075f, 155.2f);
        ActivePokemon_SetModelTransform(*(s8**)&D_82199DE0, 1, 0);
        func_821365B0(8, *(s8**)&D_82199DE0, *(s8**)&D_82199DE0, 0xFF, 0xFF);
        M2C_FIELD(D_8219A5A0, s32*, 0x20)++;
    }
}
