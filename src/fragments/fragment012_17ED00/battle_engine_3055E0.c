/* Fixed-layout split; original translation-unit boundaries remain unconfirmed. */
#include "battle_engine_3055E0.h"

f32 BattleScene_ScaleCameraDistance(ActivePokemon* arg0, f32 arg1, f32 arg2) {
    f32 temp_fv1 = BattleScene_GetParticipantModelRadiusScaled(arg0) * arg1;

    if (arg2 < temp_fv1) {
        return arg2;
    }
    return temp_fv1;
}

s32 BattleScene_AdvanceCameraSubstepCounter(s32 arg0) {
    sBattleScene.scene->unk_10++;
    if (sBattleScene.scene->unk_10 >= arg0) {
        sBattleScene.scene->unk_10 = 0;
        return 1;
    }
    return 0;
}

s32 BattleScene_AdvanceCameraFrameCounter(s32 frame_limit) {
    sBattleScene.scene->unk_14++;
    if (sBattleScene.scene->unk_14 >= frame_limit) {
        sBattleScene.scene->unk_14 = 0;
        return 1;
    }
    return 0;
}

s32 BattleScene_AdvanceCameraFrameCounterUntil(s32 arg0) {
    if (sBattleScene.scene->unk_14 >= arg0) {
        return 1;
    }
    sBattleScene.scene->unk_14++;
    return 0;
}

s32 BattleScene_IsCameraFrameCounterAtLeast(s32 arg0) {
    if (sBattleScene.scene->unk_14 >= arg0) {
        return 1;
    }
    return 0;
}

void BattleScene_SetActivePokemonIndex(s32 arg0) {
    sBattleScene.scene->unk_2C = arg0;
}

void BattleScene_ResetCameraFrameCounter(void) {
    sBattleScene.scene->unk_14 = 0;
}

void BattleScene_ResetCameraSubstepCounter(void) {
    sBattleScene.scene->unk_10 = 0;
}

void BattleScene_SetCameraAtAndEyeFromAngles(CameraNode* camera, f32 x, f32 y, f32 z, f32 distance, s16 rotation_x, s16 rotation_y) {
    Vec3f_SetComponentsDuplicate(&camera->view.targetPosition, x, y, z);
    Camera_ComputeEyeFromAngles(&camera->view.targetPosition, &camera->view.eyePosition, distance, rotation_x, rotation_y);
}

void func_82121908(ActivePokemon* arg0, Vec3f* arg1) {
    if ((M2C_FIELD(arg0, s16*, 0x1A) == 0x52) || (M2C_FIELD(arg0, s16*, 0x1A) == 0x5F)) {
        GeoRender_FindAnchorPosition((DisplayObject*)arg0, 9, arg1);
    } else {
        GeoRender_FindAnchorPosition((DisplayObject*)arg0, 0x64, arg1);
    }
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_82121954.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_82121C3C.s")

void BattleScene_SetCameraModeAndStep(s32 camera_mode, s32 camera_step) {
    sBattleScene.scene->unk_1C = camera_mode;
    sBattleScene.scene->unk_20 = camera_step;
}

void BattleScene_SetCameraClipPlanes(CameraNode* camera_node, f32 near_plane, f32 far_plane) {
    camera_node->perspective.nearPlane = near_plane;
    camera_node->perspective.farPlane = far_plane;
}

void BattleScene_SetCameraSubstate(s32 arg0, u16 arg1) {
    sBattleScene.scene->unk_30 = arg0;
    sBattleScene.scene->unk_2E = arg1;
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_82121DAC.s")

void BattleScene_SetDamageShakeAmplitude(ActivePokemon* arg0) {
    BattleMon* ptr = &arg0->teamRoster->pokemonPicked[arg0->state.rosterIndex];

    sBattleScene.scene->unk_68 = ((ptr->hp - M2C_FIELD(arg0, u16*, 0x7D2)) / 996.0f) * 450.0f;

    if (sBattleScene.scene->unk_68 == 0.0f) {
        sBattleScene.scene->unk_68 = 0.0f;
    } else if (sBattleScene.scene->unk_68 <= 6.0f) {
        sBattleScene.scene->unk_68 = 6.0f;
    } else if (sBattleScene.scene->unk_68 >= 40.0f) {
        sBattleScene.scene->unk_68 = 40.0f;
    }

    M2C_FIELD(sBattleScene.scene, s16*, 0x6C) = 0;
}

void BattleScene_ApplyCameraShake(CameraNode* arg0) {
    UNUSED s32 pad;
    f32 sp30;
    f32 temp_fv0;
    s16 sp2A;
    s16 sp28;

    BattleAnim_CalculateDistanceAngles(&arg0->view.eyePosition, &arg0->view.targetPosition, &sp30, &sp28, &sp2A);
    M2C_FIELD(sBattleScene.scene, s16*, 0x6C) += 0x4000;
    BattleAnim_ApproachF(&M2C_FIELD(sBattleScene.scene, f32*, 0x68), 0.0f, 0.15f);

    temp_fv0 = M2C_FIELD(sBattleScene.scene, f32*, 0x68) * COSS(M2C_FIELD(sBattleScene.scene, s16*, 0x6C));

    arg0->view.eyePosition.y += temp_fv0 / 3.0f;
    arg0->view.targetPosition.y += temp_fv0 / 3.0f;
    arg0->view.eyePosition.x += temp_fv0 * SINS(sp2A + 0x4000);
    arg0->view.eyePosition.z += temp_fv0 * COSS(sp2A + 0x4000);
    arg0->view.targetPosition.x += temp_fv0 * SINS(sp2A + 0x4000);
    arg0->view.targetPosition.z += temp_fv0 * COSS(sp2A + 0x4000);
}

void func_82122104(s32 arg0) {
    M2C_FIELD(D_8219A5A0, f32 *, 0x68) = 30.0f;
    M2C_FIELD(D_8219A5A0, s16 *, 0x6C) = 0;
}

s32 BattleScene_IsCameraAngleSettled(s16 arg0, s16 arg1) {
    s16 temp_v1;
    s16 var_v1;

    temp_v1 = arg1 - arg0;
    var_v1 = arg1;
    if (temp_v1 > 0) {
        temp_v1 -= 0xE38;
        if (temp_v1 > 0) {
            var_v1 -= temp_v1;
        } else {
            var_v1 = arg1;
        }
    } else {
        temp_v1 += 0xE38;
        if (temp_v1 < 0) {
            var_v1 -= temp_v1;
        } else {
            var_v1 = arg1;
        }
    }

    if (var_v1 == arg1) {
        return 1;
    }
    return 0;
}

s32 func_821221C0(s32 arg0, s16 arg1, s16 arg2) {
    s16 var_v0;

    if (arg1 > 0) {
        M2C_FIELD(D_8219A5A0, s16 *, 0x5A) = (s16) (M2C_FIELD(D_8219A5A0, s16 *, 0x5A) - arg1);
        var_v0 = M2C_FIELD(D_8219A5A0, s16 *, 0x5A);
        if ((var_v0 < arg2) && ((arg2 - arg1) < var_v0)) {
            M2C_FIELD(D_8219A5A0, s16 *, 0x5A) = arg2;
            return 1;
        }
        goto block_7;
    }
    M2C_FIELD(D_8219A5A0, s16 *, 0x5A) = (s16) (M2C_FIELD(D_8219A5A0, s16 *, 0x5A) - arg1);
    var_v0 = M2C_FIELD(D_8219A5A0, s16 *, 0x5A);
    if ((arg2 < var_v0) && (var_v0 < (arg2 - arg1))) {
        M2C_FIELD(D_8219A5A0, s16 *, 0x5A) = arg2;
        return 1;
    }
block_7:
    func_8000EEBC(arg0 + 0xB4, arg0 + 0xA8, M2C_FIELD(D_8219A5A0, s32 *, 0x5C), M2C_FIELD(D_8219A5A0, s16 *, 0x58), (s32) var_v0);
    return 0;
}

s32 BattleScene_ApproachCameraRollNoEyeUpdate(UNUSED CameraNode* arg0, s16 arg1, s16 arg2) {
    M2C_FIELD(sBattleScene.scene, s16*, 0x5A) -= arg1;

    if (arg1 > 0) {
        if ((arg2 >= M2C_FIELD(sBattleScene.scene, s16*, 0x5A)) && (M2C_FIELD(sBattleScene.scene, s16*, 0x5A) >= (arg2 - arg1))) {
            M2C_FIELD(sBattleScene.scene, s16*, 0x5A) = arg2;
            return 1;
        }
    } else if ((M2C_FIELD(sBattleScene.scene, s16*, 0x5A) >= arg2) && ((arg2 - arg1) >= M2C_FIELD(sBattleScene.scene, s16*, 0x5A))) {
        M2C_FIELD(sBattleScene.scene, s16*, 0x5A) = arg2;
        return 1;
    }
    return 0;
}

void func_82122334(s16 arg0, s16 arg1, f32 arg2) {
    M2C_FIELD(D_8219A5A0, s16 *, 0x58) = arg0;
    M2C_FIELD(D_8219A5A0, s16 *, 0x5A) = arg1;
    M2C_FIELD(D_8219A5A0, f32 *, 0x5C) = arg2;
}

void func_82122374(s8 *arg0) {
    if (M2C_FIELD(arg0, f32 *, 0xAC) <= 15.0f) {
        M2C_FIELD(arg0, f32 *, 0xAC) = 15.0f;
    }
}

typedef struct BattleCameraModelState {
    u8 pad00[0x30]; s16 rotationX; s16 rotationY; u8 pad34[4]; f32 distance;
} BattleCameraModelState;
extern f32 D_FLT_82189354[][4];
void func_8212239C(ActivePokemon* pokemon, CameraNode* camera) {
    BattleCameraModelState* model = (BattleCameraModelState*)&pokemon->modelTransform;
    UNUSED s32 pad[3];
    Vec3f_SetComponentsDuplicate(&pokemon->modelTransform.unk_18, M2C_FIELD(pokemon, f32*, 0x5DC), M2C_FIELD(pokemon, f32*, 0x5E0), M2C_FIELD(pokemon, f32*, 0x5E4));
    pokemon->modelTransform.unk_18.y = M2C_FIELD(pokemon, f32*, 0x5E0) + (pokemon->displayObject.position.y - D_FLT_82189354[pokemon->displayObject.objectType][0]);
    BattleAnim_Vec3fCopy((Vec3f*)(D_8219A5A0 + 0xA8), &camera->view.targetPosition);
    BattleAnim_Vec3fCopy((Vec3f*)(D_8219A5A0 + 0xB4), &camera->view.eyePosition);
    BattleAnim_CalculateDistanceAngles(&pokemon->modelTransform.unk_18, &camera->view.targetPosition, &model->distance, &model->rotationX, &model->rotationY);
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_82122458.s")

void BattleScene_ClearCameraOffsetVectors(void) {
    Vec3f_SetComponentsDuplicate(&sBattleScene.scene->unk_94, 0.0f, 0.0f, 0.0f);
    Vec3f_SetComponentsDuplicate(&sBattleScene.scene->unk_A0, 0.0f, 0.0f, 0.0f);
}

void BattleScene_SetCameraAtFromAnchor(ActivePokemon* arg0, CameraNode* arg1, Vec3f arg2, s16 arg3, s16 arg4, f32 arg5, f32 arg6) {
    Camera_ComputeEyeFromAngles(&arg2, &arg1->view.targetPosition, arg5, arg3, arg4);
    arg1->view.targetPosition.y += arg6;
    arg1->view.targetPosition.y += ((CameraTargetOffsetRow*)D_FLT_82189358)[M2C_FIELD(arg0, s16*, 0x1A)].v;
}

void BattleScene_SetCameraAtFromPosition(CameraNode* arg0, Vec3f arg1, s16 arg2, s16 arg3, f32 arg4, f32 arg5) {
    Camera_ComputeEyeFromAngles(&arg1, &arg0->view.targetPosition, arg4, arg2, arg3);
    arg0->view.targetPosition.y += arg5;
}

void BattleScene_SetCameraEyeFromPosition(CameraNode* arg0, Vec3f arg1, s16 arg2, s16 arg3, f32 arg4, f32 arg5) {
    Camera_ComputeEyeFromAngles(&arg1, &arg0->view.eyePosition, arg4, arg2, arg3);
    arg0->view.eyePosition.y += arg5;
}

void BattleScene_SetCameraEyeFromAt(CameraNode* arg0, s16 arg1, s16 arg2, f32 arg3, f32 arg4) {
    Camera_ComputeEyeFromAngles(&arg0->view.targetPosition, &arg0->view.eyePosition, arg3, arg1, arg2);
    arg0->view.eyePosition.y += arg4;
}

void BattleScene_SetCameraEyeAndStoreAngles(CameraNode* arg0, Vec3f arg1, s16 arg2, s16 arg3, f32 arg4, f32 arg5) {
    BattleScene_SetCameraAnglesAndDistance(arg2, arg3, arg4);
    Camera_ComputeEyeFromAngles(&arg1, &arg0->view.eyePosition, arg4, arg2, arg3);
    arg0->view.eyePosition.y += arg5;
}

void BattleScene_SetCameraEyeAndStoreAnglesFromAt(CameraNode* arg0, s16 arg1, s16 arg2, f32 arg3, f32 arg4) {
    BattleScene_SetCameraAnglesAndDistance(arg1, arg2, arg3);
    Camera_ComputeEyeFromAngles(&arg0->view.targetPosition, &arg0->view.eyePosition, arg3, arg1, arg2);
    arg0->view.eyePosition.y += arg4;
}

void BattleScene_CameraHelperNop(UNUSED CameraNode* arg0) {
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_821227C0.s")

void func_821228B0(CameraNode* arg0, ActivePokemon* arg1) {
    u8* ptr = (u8*)&arg1->modelTransform;
    Vec3f sp50;
    Vec3f sp44;
    Vec3f sp38;
    f32 sp34;
    s16 sp32;
    s16 sp30;
    Vec3f* sp28;

    func_82121908(arg1, &sp50);
    BattleAnim_CalculateDistanceAngles(&sp50, &M2C_FIELD(arg1, Vec3f*, 0x5D0), &sp34, &sp32, &sp30);
    sp28 = &arg0->view.targetPosition;
    BattleAnim_Vec3fCopy(&sp38, sp28);
    Camera_ComputeEyeFromAngles(&sp50, &sp44, M2C_FIELD(ptr, f32*, 0x38), M2C_FIELD(ptr, s16*, 0x30), M2C_FIELD(ptr, s16*, 0x32));
    BattleAnim_CalculateDistanceAngles(&sp38, &sp44, &sp34, &sp32, &sp30);
    if (sp34 >= 5.0) {
        Camera_ComputeEyeFromAngles(&sp38, sp28, sp34 * 0.05f, sp32, sp30);
    }
    func_821227C0(arg0, arg1);
}

void BattleScene_ApproachCameraTarget(CameraNode* arg0, ActivePokemon* arg1) {
    SwayState* ptr = &arg1->modelTransform;
    Vec3f sp50;
    Vec3f sp44;
    Vec3f sp38;
    f32 sp34;
    s16 sp32;
    s16 sp30;
    UNUSED s32 pad;

    func_82121908(arg1, &sp50);
    BattleAnim_CalculateDistanceAngles(&sp50, &M2C_FIELD(arg1, Vec3f*, 0x5D0), &sp34, &sp32, &sp30);
    BattleAnim_Vec3fCopy(&sp38, &arg0->view.targetPosition);
    Camera_ComputeEyeFromAngles(&sp50, &sp44, M2C_FIELD(ptr, f32*, 0x38), M2C_FIELD(ptr, s16*, 0x30), M2C_FIELD(ptr, s16*, 0x32));
    BattleAnim_CalculateDistanceAngles(&sp38, &sp44, &sp34, &sp32, &sp30);
    Camera_ComputeEyeFromAngles(&sp38, &arg0->view.targetPosition, sp34 * 0.1f, sp32, sp30);
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_82122A7C.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_82122B9C.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_82122CCC.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_82122DFC.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_82122FD8.s")

void func_8212311C(CameraNode* arg0, ActivePokemon* arg1, Color_RGBA8 arg2) {
    Vec3f sp74;
    Vec3f sp68;
    Vec3f sp5C;
    f32 sp58;
    s16 sp56;
    s16 sp54;
    s16 sp52;
    s16 sp50;
    s16 sp4E;
    s16 sp4C;

    BattleAnim_Vec3fCopy(&sp68, &arg0->view.targetPosition);
    BattleAnim_Vec3fCopy(&sp5C, &arg0->view.eyePosition);
    BattleAnim_GetOwnerDefaultAnchorPosition(arg1, &sp74);
    gCameraDistTarget = BattleScene_ScaleCameraDistance(arg1, 3.5f, 300.0f);
    BattleScene_SetCameraAtFromAnchor(arg1, arg0, sp74, 0, BattleScene_GetParticipantFacingAngle(arg1), 0.0f, 0.0f);
    BattleScene_SetCameraEyeFromPosition(arg0, sp74, 0, BattleScene_GetParticipantFacingAngle(arg1), gCameraDistTarget, 0.0f);
    BattleAnim_CalculateDistanceAngles(&arg0->view.targetPosition, &arg0->view.eyePosition, &D_8219A534, &sp4C, &sp50);
    BattleAnim_CalculateDistanceAngles(&sp68, &sp5C, &gCameraDistTarget, &sp4E, &sp52);
    BattleAnim_ApproachF(&gCameraDistTarget, D_8219A534, 0.05f);
    BattleAnim_StepToS16(&sp52, sp50, 0x108);
    BattleAnim_StepToS16(&sp4E, sp4C, 0xB6);
    BattleAnim_CalculateDistanceAngles(&sp68, &arg0->view.targetPosition, &sp58, &sp56, &sp54);
    Camera_ComputeEyeFromAngles(&sp68, &arg0->view.targetPosition, sp58 / 6, sp56, sp54);
    BattleScene_SetCameraEyeFromAt(arg0, sp4E, sp52, gCameraDistTarget, 0.0f);
}

void func_82123314(CameraNode* arg0, ActivePokemon* arg1) {
    u8* ptr = (u8*)&arg1->modelTransform;
    Vec3f sp50;
    Vec3f sp44;
    Vec3f sp38;
    Vec3f sp2C;
    f32 sp28;
    s16 sp26;
    s16 sp24;

    func_82121908(arg1, &sp50);
    BattleAnim_Vec3fCopy(&sp38, &arg0->view.targetPosition);
    Camera_ComputeEyeFromAngles(&sp50, &sp44, M2C_FIELD(ptr, f32*, 0x38), M2C_FIELD(ptr, s16*, 0x30), M2C_FIELD(ptr, s16*, 0x32));
    BattleAnim_CalculateDistanceAngles(&sp38, &sp44, &sp28, &sp26, &sp24);
    Camera_ComputeEyeFromAngles(&sp38, &sp2C, sp28 * D_FLT_82196258, sp26, sp24);
    arg0->view.targetPosition.y = sp2C.y;
    if (arg0->view.targetPosition.y <= 15.0f) {
        arg0->view.targetPosition.y = 15.0f;
    }
}

void BattleScene_RecenterCameraOnOwner(CameraNode* arg0, ActivePokemon* arg1) {
    Vec3f sp74;
    Vec3f sp68;
    Vec3f sp5C;
    f32 sp58;
    s16 sp56;
    s16 sp54;
    s16 sp52;
    s16 sp50;
    s16 sp4E;
    s16 sp4C;

    BattleAnim_Vec3fCopy(&sp68, &arg0->view.targetPosition);
    BattleAnim_Vec3fCopy(&sp5C, &arg0->view.eyePosition);
    BattleAnim_GetOwnerDefaultAnchorPosition(arg1, &sp74);
    gCameraDistTarget = BattleScene_ScaleCameraDistance(arg1, 3.5f, 300.0f);
    BattleScene_SetCameraAtFromAnchor(arg1, arg0, sp74, 0, BattleScene_GetParticipantFacingAngle(arg1), 0.0f, 0.0f);
    BattleScene_SetCameraEyeFromPosition(arg0, sp74, 0, BattleScene_GetParticipantFacingAngle(arg1), gCameraDistTarget, 0.0f);
    BattleAnim_CalculateDistanceAngles(&arg0->view.targetPosition, &arg0->view.eyePosition, &D_8219A534, &sp4C, &sp50);
    BattleAnim_CalculateDistanceAngles(&sp68, &sp5C, &gCameraDistTarget, &sp4E, &sp52);
    BattleAnim_ApproachF(&gCameraDistTarget, D_8219A534, 0.05f);
    BattleAnim_StepToS16(&sp52, sp50, 0x108);
    BattleAnim_StepToS16(&sp4E, sp4C, 0xB6);
    BattleAnim_CalculateDistanceAngles(&sp68, &arg0->view.targetPosition, &sp58, &sp56, &sp54);
    Camera_ComputeEyeFromAngles(&sp68, &arg0->view.targetPosition, sp58 / 8, sp56, sp54);
    BattleScene_SetCameraEyeFromAt(arg0, sp4E, sp52, gCameraDistTarget, 0.0f);
}

void BattleScene_ApproachCameraZoom(CameraNode* arg0, ActivePokemon* arg1) {
    s16 sp26;
    s16 sp24;

    gCameraDistTarget = BattleScene_ScaleCameraDistance(arg1, 8.0f, 500.0f);
    BattleAnim_CalculateDistanceAngles(&arg0->view.targetPosition, &arg0->view.eyePosition, &D_8219A534, &sp26, &sp24);
    BattleAnim_ApproachF(&D_8219A534, gCameraDistTarget, 0.03f);
    BattleAnim_StepToS16(&sp26, 0xE38, 0x5B);
    BattleScene_SetCameraEyeFromAt(arg0, sp26, sp24, D_8219A534, 0.0f);
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_82123684.s")

void BattleScene_SetCameraOwnerWideShot(CameraNode* arg0, ActivePokemon* arg1) {
    f32 sp3C;

    BattleAnim_GetOwnerDefaultAnchorPosition(arg1, &sBattleScene.scene->unk_D0);
    sp3C = BattleScene_ScaleCameraDistance(arg1, 8.0f, 300.0f);
    BattleScene_SetCameraAtFromAnchor(arg1, arg0, sBattleScene.scene->unk_D0, 0, BattleScene_GetParticipantFacingAngle(arg1), 0.0f, 0.0f);
    BattleScene_SetCameraEyeFromAt(arg0, 0, arg1->facingDirection << 0xE, sp3C, 0.0f);
}

void BattleScene_SetCameraPresetClose(CameraNode* arg0, ActivePokemon* arg1) {
    BattleAnim_GetOwnerDefaultAnchorPosition(arg1, &M2C_FIELD(sBattleScene.scene, Vec3f*, 0xC0));
    gCameraDistTarget = BattleScene_ScaleCameraDistance(arg1, 1.0f, 100.0f);
    D_8219A534 = BattleScene_ScaleCameraDistance(arg1, 5.0f, 300.0f);
    BattleScene_SetCameraAtFromAnchor(arg1, arg0, M2C_FIELD(sBattleScene.scene, Vec3f*, 0xC0), 0, BattleScene_GetParticipantFacingAngle(arg1), gCameraDistTarget, 0.0f);
    BattleScene_SetCameraEyeFromPosition(arg0, M2C_FIELD(sBattleScene.scene, Vec3f*, 0xC0), 0, BattleScene_GetParticipantFacingAngle(arg1) - (arg1->facingDirection * 0x31C7), D_8219A534, 0.0f);
}

void BattleScene_SetCameraFollowPresetNear(CameraNode* arg0, ActivePokemon* arg1) {
    s16 sp3E;

    BattleAnim_GetOwnerDefaultAnchorPosition(arg1, &M2C_FIELD(sBattleScene.scene, Vec3f*, 0xC0));
    gCameraDistTarget = BattleScene_ScaleCameraDistance(arg1, 1.2f, 100.0f);
    D_8219A534 = BattleScene_ScaleCameraDistance(arg1, 5.0f, 300.0f);
    BattleScene_SetCameraAtFromAnchor(arg1, arg0, M2C_FIELD(sBattleScene.scene, Vec3f*, 0xC0), 0, BattleScene_GetParticipantFacingAngle(arg1), gCameraDistTarget, 0.0f);
    sp3E = BattleScene_GetParticipantFacingAngle(arg1);
    BattleScene_SetCameraEyeFromPosition(arg0, M2C_FIELD(sBattleScene.scene, Vec3f*, 0xC0), 0, sp3E - (arg1->facingDirection * 0x1555), D_8219A534, func_82107EC8(arg1) * 2.0f);
}

void BattleScene_SetCameraPresetLowClose(CameraNode* arg0, ActivePokemon* arg1) {
    s16 sp3E;

    BattleAnim_GetOwnerDefaultAnchorPosition(arg1, &M2C_FIELD(sBattleScene.scene, Vec3f*, 0xC0));
    gCameraDistTarget = BattleScene_ScaleCameraDistance(arg1, 1.2f, 100.0f);
    D_8219A534 = BattleScene_ScaleCameraDistance(arg1, 5.0f, 300.0f);
    BattleScene_SetCameraAtFromAnchor(arg1, arg0, M2C_FIELD(sBattleScene.scene, Vec3f*, 0xC0), 0, BattleScene_GetParticipantFacingAngle(arg1), gCameraDistTarget, 0.0f);
    sp3E = BattleScene_GetParticipantFacingAngle(arg1);
    BattleScene_SetCameraEyeFromPosition(arg0, M2C_FIELD(sBattleScene.scene, Vec3f*, 0xC0), 0, sp3E - (arg1->facingDirection * 0x1555), D_8219A534,
                  -func_82107EC8(arg1) * D_DBL_82196260);
    if (M2C_FIELD(arg0, f32*, 0xAC) <= 15.0f) {
        M2C_FIELD(arg0, f32*, 0xAC) = 15.0f;
    }
}

void BattleScene_CameraShotTargetClose(CameraNode* arg0, ActivePokemon* arg1) {
    BattleAnim_GetOwnerDefaultAnchorPosition(arg1, &sBattleScene.scene->unk_D0);
    gCameraDistTarget = BattleScene_ScaleCameraDistance(arg1, 3.5f, 300.0f);
    BattleScene_SetCameraAtFromAnchor(arg1, arg0, sBattleScene.scene->unk_D0, 0, BattleScene_GetParticipantFacingAngle(arg1), 0.0f, 0.0f);
    BattleScene_SetCameraEyeFromPosition(arg0, sBattleScene.scene->unk_D0, 0, BattleScene_GetParticipantFacingAngle(arg1), gCameraDistTarget, 0.0f);
}

void func_82123D4C(CameraNode* arg0, ActivePokemon* arg1) {
    BattleAnim_GetOwnerDefaultAnchorPosition(arg1, &sBattleScene.scene->unk_D0);
    gCameraDistTarget = BattleScene_ScaleCameraDistance(arg1, 3.5f, 300.0f);
    BattleScene_SetCameraAtFromAnchor(arg1, arg0, sBattleScene.scene->unk_D0, 0, BattleScene_GetParticipantFacingAngle(arg1), 0.0f, 0.0f);
    BattleScene_SetCameraEyeFromPosition(arg0, sBattleScene.scene->unk_D0, 0, BattleScene_GetParticipantFacingAngle(arg1), gCameraDistTarget, 0.0f);
}

void BattleScene_CameraShotTargetHigh(CameraNode* arg0, ActivePokemon* arg1) {
    BattleAnim_GetOwnerDefaultAnchorPosition(arg1, &M2C_FIELD(sBattleScene.scene, Vec3f*, 0xC0));
    gCameraDistTarget = BattleScene_ScaleCameraDistance(arg1, 5.0f, 400.0f);
    BattleScene_SetCameraAtFromAnchor(arg1, arg0, M2C_FIELD(sBattleScene.scene, Vec3f*, 0xC0), 0, arg1->facingDirection << 0xE, 0.0f, 0.0f);
    BattleScene_SetCameraEyeFromPosition(arg0, M2C_FIELD(sBattleScene.scene, Vec3f*, 0xC0), 0, arg1->facingDirection * 0xE38, gCameraDistTarget, 0.0f);
}

void func_82123F44(CameraNode* arg0, ActivePokemon* arg1) {
    BattleAnim_GetOwnerDefaultAnchorPosition(arg1, &M2C_FIELD(sBattleScene.scene, Vec3f*, 0xC0));
    gCameraDistTarget = BattleScene_ScaleCameraDistance(arg1, 5.0f, 400.0f);
    BattleScene_SetCameraAtFromAnchor(arg1, arg0, M2C_FIELD(sBattleScene.scene, Vec3f*, 0xC0), 0, arg1->facingDirection << 0xE, 0.0f, 0.0f);
    BattleScene_SetCameraEyeFromPosition(arg0, M2C_FIELD(sBattleScene.scene, Vec3f*, 0xC0), 0, arg1->facingDirection * 0xE38, gCameraDistTarget, 2.0f * func_82107EC8(arg1));
}

void func_82124054(CameraNode* arg0, ActivePokemon* arg1) {
    BattleAnim_GetOwnerDefaultAnchorPosition(arg1, &M2C_FIELD(sBattleScene.scene, Vec3f*, 0xC0));
    gCameraDistTarget = BattleScene_ScaleCameraDistance(arg1, 5.0f, 400.0f);
    BattleScene_SetCameraAtFromAnchor(arg1, arg0, M2C_FIELD(sBattleScene.scene, Vec3f*, 0xC0), 0, arg1->facingDirection << 0xE, 0.0f, 0.0f);
    BattleScene_SetCameraEyeFromPosition(arg0, M2C_FIELD(sBattleScene.scene, Vec3f*, 0xC0), 0, arg1->facingDirection * 0xE38, gCameraDistTarget, -func_82107EC8(arg1) * D_FLT_82196268);
    if (M2C_FIELD(arg0, f32*, 0xAC) <= 15.0f) {
        M2C_FIELD(arg0, f32*, 0xAC) = 15.0f;
    }
}

void func_82124194(CameraNode* arg0, ActivePokemon* arg1) {
    BattleAnim_GetOwnerDefaultAnchorPosition(arg1, &sBattleScene.scene->unk_D0);
    gCameraDistTarget = BattleScene_ScaleCameraDistance(arg1, 3.5f, 300.0f);
    BattleScene_SetCameraAtFromAnchor(arg1, arg0, sBattleScene.scene->unk_D0, 0, BattleScene_GetParticipantFacingAngle(arg1), 0.0f, 0.0f);
    BattleScene_SetCameraEyeFromPosition(arg0, sBattleScene.scene->unk_D0, 0, BattleScene_GetParticipantFacingAngle(arg1), gCameraDistTarget, 0.0f);
}

void func_82124284(CameraNode* arg0, ActivePokemon* arg1, f32 arg2) {
    BattleAnim_GetOwnerDefaultAnchorPosition(arg1, &sBattleScene.scene->unk_D0);
    D_8219A530 = BattleScene_ScaleCameraDistance(arg1, 3.5f, 200.0f);
    D_8219A534 = BattleScene_ScaleCameraDistance(arg1, 5.0f, 400.0f);
    BattleScene_SetCameraAtFromAnchor(arg1, arg0, sBattleScene.scene->unk_D0, 0, arg1->facingDirection << 14, sBattleScene.scene->unk_74 = D_8219A530, 0.0f);
    BattleScene_SetCameraEyeFromPosition(arg0, sBattleScene.scene->unk_D0, 0, arg1->facingDirection * 0x1555, D_8219A534, arg2);
    if (M2C_FIELD(arg0, f32*, 0xAC) <= 15.0f) {
        M2C_FIELD(arg0, f32*, 0xAC) = 15.0f;
    }
}
