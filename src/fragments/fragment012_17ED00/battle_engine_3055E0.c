/* Stadium Zero fragment012_17ED00. */
/* C ported from the Stadium 1 decomp: src/fragments/battle_engine/battle_engine_3055E0.c, src/fragments/battle_engine/battle_engine_317E70.c, src/fragments/battle_engine/battle_engine_328F10.c, src/fragments/clefairy_game/clefairy_game.c, src/fragments/demo_scenes/demo_scenes_15FA60.c, src/fragments/lab_pc_list/lab_pc_list_1E46B0.c, src/fragments/metapod_game/metapod_game.c. */

#include "fragments/battle_engine/battle_engine.h"
#include "moves.h"
#include "geo_render.h"
#include "matrix.h"
#include "pokemon.h"
extern unk_D_843901B0 gCameraPreset;
extern f32 gCameraDistTarget;
extern f32 D_8219A534;

#include "fragments/battle_engine/battle_engine.h"
#include "geo_render.h"
#include "model_renderer.h"
#include "matrix.h"
#include "fragments/particle_math/particle_math.h"
#include "memory.h"

#include "fragments/battle_engine/battle_engine.h"

#include "fragments/clefairy_game/clefairy_game.h"
#include "geo_render.h"
#include "model_animation.h"
#include "model_animation_events.h"
#include "geo_layout.h"
#include "display_object_textures.h"
#include "model_renderer.h"
#include "graphics_textures.h"
#include "input.h"
#include "ui_graphics.h"
#include "text_system.h"
#include "jpeg_stream.h"
#include "audio_sfx.h"
#include "audio_loop_point.h"
#include "gfx_buffer.h"
#include "gfx_rect.h"
#include "controller.h"
#include "fragments/widget_toolkit/widget_toolkit.h"
#include "fragments/minigame_shared_graphics/minigame_shared_graphics.h"
#include "memory.h"
#include "stage_loader.h"
typedef struct unk_D_861054C0 {
    /* 0x000 */ s16 unk_000;
    /* 0x002 */ s16 unk_002;
    /* 0x004 */ char pad4[4];
    /* 0x008 */ DisplayObject unk_008;
    /* 0x170 */ s16 unk_170;
    /* 0x172 */ u16 unk_172;
    /* 0x174 */ s16 unk_174[0xC];
    /* 0x18C */ s16 unk_18C;
    /* 0x18E */ s16 unk_18E[0xC];
    /* 0x1A6 */ s16 unk_1A6;
    /* 0x1A8 */ s16 unk_1A8;
    /* 0x1AA */ s16 unk_1AA;
    /* 0x1AC */ s16 unk_1AC;
    /* 0x1AE */ s16 unk_1AE;
    /* 0x1B0 */ s16 unk_1B0;
    /* 0x1B2 */ s16 unk_1B2;
    /* 0x1B4 */ s16 unk_1B4;
    /* 0x1B6 */ char pad1B6[2];
    /* 0x1B8 */ f32 unk_1B8;
    /* 0x1BC */ f32 unk_1BC;
} unk_D_861054C0;
typedef struct unk_D_86105EA0 {
    /* 0x000 */ char unk000[0x4];
    /* 0x004 */ DisplayObject unk_004;
} unk_D_86105EA0;
typedef struct unk_D_86106450 {
    /* 0x000 */ s16 unk_000;
    /* 0x002 */ s16 unk_002;
    /* 0x004 */ DisplayObject unk_004;
    /* 0x16C */ ModelNodeView* unk_16C;
} unk_D_86106450;
void ClefairyGame_DespawnPatternIcons(void);
void ClefairyGame_SpawnPatternIcons(void);
typedef struct unk_D_861047B8 {
    /* 0x00 */ u8 unk_00[6];
    /* 0x06 */ u8 unk_06[4];
} unk_D_861047B8;
typedef struct unk_D_86104984 {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
} unk_D_86104984;
typedef struct unk_D_861049B4 {
    /* 0x00 */ u32* unk_00;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
} unk_D_861049B4;
typedef struct unk_D_86104B5C {
    /* 0x00 */ u8 unk_00[3];
} unk_D_86104B5C;
extern s32 pad_86104B64[];

#include "fragments/demo_scenes/demo_scenes.h"
#include "geo_render.h"
#include "model_animation.h"
#include "geo_layout.h"
#include "display_object_textures.h"
#include "model_renderer.h"
#include "graphics_textures.h"
#include "input.h"
#include "save_data.h"
#include "text_system.h"
#include "jpeg_stream.h"
#include "audio_loop_point.h"
#include "gfx_rect.h"
#include "matrix.h"
#include "controller.h"
#include "fragments/particle_math/particle_math.h"
#include "memory.h"
#include "stage_loader.h"
typedef struct unk_D_86B0E5D8 {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ u8 unk_04;
    /* 0x05 */ u8 unk_05;
    /* 0x06 */ u8 unk_06;
    /* 0x07 */ u8 unk_07;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
} unk_D_86B0E5D8;
s32 Diorama_LogoRotateColorCallback(s32, GraphNode*);
s32 Diorama_ScaleRotateCallbackA(s32, GraphNode*);
s32 Diorama_ScaleRotateCallbackB(s32, GraphNode*);
s32 Diorama_GroupStateCallback(s32, GraphNode*);

#include "fragments/lab_pc_list/lab_pc_list.h"
#include "gb_data.h"
#include "save_data.h"
#include "game_state.h"
#include "table_view.h"
#include "gb_save.h"
#include "hal_libc.h"
#include "memory.h"
extern Gfx D_8910D028[];
typedef struct unk_func_88316214 {
    /* 0x00 */ char unk00[0x2C];
    /* 0x2C */ u8 unk_2C;
} unk_func_88316214;
typedef struct unk_func_88316304 {
    /* 0x00 */ unk_func_8830867C_02C_0CC_000** unk_00;
    /* 0x04 */ char unk04[0x4];
    /* 0x08 */ u8 unk_08;
    /* 0x09 */ char unk09[0x8];
    /* 0x11 */ u8 unk_11[1];
} unk_func_88316304;
typedef struct unk_func_883164C0 {
    /* 0x00 */ char unk00[0x5C];
} unk_func_883164C0;

#include "fragments/metapod_game/metapod_game.h"
#include "geo_render.h"
#include "model_animation.h"
#include "model_animation_events.h"
#include "display_object_textures.h"
#include "model_renderer.h"
#include "graphics_textures.h"
#include "ui_graphics.h"
#include "text_system.h"
#include "jpeg_stream.h"
#include "audio_sound_state.h"
#include "audio_sfx.h"
#include "audio_channel.h"
#include "audio_loop_point.h"
#include "audio_commands_category2.h"
#include "audio_category_fade.h"
#include "gfx_buffer.h"
#include "gfx_rect.h"
#include "fragments/widget_toolkit/widget_toolkit.h"
#include "fragments/particle_math/particle_math.h"
#include "geo_layout.h"
#include "memory.h"
#include "stage_loader.h"
typedef struct MiniRockInfo {
    /* 0x00 */ Vec3f unk_00;
    /* 0x0C */ Vec3s unk_0C;
    /* 0x12 */ s16 unk_12;
    /* 0x14 */ s16 unk_14;
    /* 0x16 */ s16 unk_16;
} MiniRockInfo;
extern MiniActor miniMetapods[4];
extern MiniActor miniMetapodRocks[20];
extern MiniActor* miniMetapodPtr;
extern MiniActor* miniRockPtr;
extern Vec3f miniMetapodInfo[];
extern MiniRockInfo miniRockInfos[];

#include "m2c_macros.h"
f32 func_82107EC8();

f32 BattleScene_ScaleCameraDistance(ActivePokemon* arg0, f32 arg1, f32 arg2);
s32 BattleScene_AdvanceCameraSubstepCounter(s32 arg0);
s32 BattleScene_AdvanceCameraFrameCounter(s32 frame_limit);
s32 BattleScene_AdvanceCameraFrameCounterUntil(s32 arg0);
s32 BattleScene_IsCameraFrameCounterAtLeast(s32 arg0);
void BattleScene_SetActivePokemonIndex(s32 arg0);
void BattleScene_ResetCameraFrameCounter(void);
void BattleScene_ResetCameraSubstepCounter(void);
void BattleScene_SetCameraAtAndEyeFromAngles(CameraNode* camera, f32 x, f32 y, f32 z, f32 distance, s16 rotation_x, s16 rotation_y);
void BattleScene_SetCameraModeAndStep(s32 camera_mode, s32 camera_step);
void BattleScene_SetCameraClipPlanes(CameraNode* camera_node, f32 near_plane, f32 far_plane);
void BattleScene_SetCameraSubstate(s32 arg0, u16 arg1);
s32 BattleScene_IsCameraAngleSettled(s16 arg0, s16 arg1);
void BattleScene_SetCameraAtFromPosition(CameraNode* arg0, Vec3f arg1, s16 arg2, s16 arg3, f32 arg4, f32 arg5);
void BattleScene_SetCameraEyeFromPosition(CameraNode* arg0, Vec3f arg1, s16 arg2, s16 arg3, f32 arg4, f32 arg5);
void BattleScene_SetCameraEyeFromAt(CameraNode* arg0, s16 arg1, s16 arg2, f32 arg3, f32 arg4);
void BattleScene_SetCameraEyeAndStoreAngles(CameraNode* arg0, Vec3f arg1, s16 arg2, s16 arg3, f32 arg4, f32 arg5);
void BattleScene_SetCameraEyeAndStoreAnglesFromAt(CameraNode* arg0, s16 arg1, s16 arg2, f32 arg3, f32 arg4);
void BattleScene_CameraHelperNop(UNUSED CameraNode* arg0);
void BattleScene_RecenterCameraOnOwner(CameraNode* arg0, ActivePokemon* arg1);
void BattleScene_ApproachCameraZoom(CameraNode* arg0, ActivePokemon* arg1);
void BattleAnim_GetOwnerModelBoundsScaled(ActivePokemon* arg0, Vec3f* arg1);
void BattleAnim_StartEffect140StartEffect139Alias(void);
void BattleAnim_StartEffect142StartEffect141Alias(void);
void ClefairyGame_HidePatternIcons(void);
void ClefairyGame_ShowPatternIcons(void);
void func_821247F0(void);
s32 func_82124810(CameraNode* arg0, ActivePokemon* arg1);
void func_82124874(void);

void BattleScene_SetCameraAnglesAndDistance(s16 arg0, s16 arg1, f32 arg2);
void BattleScene_SetCameraAtFromAnchor(ActivePokemon* arg0, CameraNode* arg1, Vec3f arg2, s16 arg3, s16 arg4, f32 arg5, f32 arg6);
void BattleAnim_StartEffect139DualRepeatingSparks(void);
void BattleAnim_StartEffect141GridRiseAndFallingBurst(void);
void ClefairyGame_DespawnPatternIcons(void);
void ClefairyGame_SpawnPatternIcons(void);
void Diorama_RenderFrame(void);
s32 LabPCList_CompareBySpeciesGroup(unk_func_8830867C_02C_0CC* arg0, unk_func_8830867C_02C_0CC* arg1);

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

#ifdef NON_MATCHING
/* TODO: decompile func_82121954; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_82121954.s")
#endif

extern f32 D_FLT_82196230;
extern f32 D_FLT_82196234;
s32 func_82121954(ActivePokemon*, s32, ActivePokemon*, s16, f32);
/*
 * func_82121C3C
 *
 * Unless the scene's unk_1C is one of 4, 7, 8, 9, 0xA or 0xB, it calls
 * func_82121954 once for each of the two active Pokemon (sActivePokemon[0]
 * and [1]).  Each call gets the Pokemon (twice), arg0, the halfword at offset
 * 0x34 of that Pokemon's state block, and a float (D_FLT_82196230 for the
 * first Pokemon, D_FLT_82196234 for the second).  Bit 0 of the byte at offset 1
 * of the Pokemon is set when the call returns non-zero and cleared when it
 * returns zero.  What func_82121954 tests and what that bit means is not
 * established here.
 * Note: sActivePokemon[0]/[1] are re-read after each call rather than held in
 * locals, which is what the ROM does.
 */
void func_82121C3C(s32 arg0) {
    ActivePokemonState* first_state = &sActivePokemon[0]->state;
    ActivePokemonState* second_state = &sActivePokemon[1]->state;
    s32 mode = sBattleScene.scene->unk_1C;
    if ((mode != 4) && (mode != 8) && (mode != 7) && (mode != 0xB) && (mode != 9) && (mode != 0xA)) {
        if (func_82121954(sActivePokemon[0], arg0, sActivePokemon[0], M2C_FIELD(first_state, s16*, 0x34), D_FLT_82196230) != 0) {
            M2C_FIELD(sActivePokemon[0], u8*, 1) |= 1;
        } else {
            M2C_FIELD(sActivePokemon[0], u8*, 1) &= 0xFFFE;
        }
        if (func_82121954(sActivePokemon[1], arg0, sActivePokemon[1], M2C_FIELD(second_state, s16*, 0x34), D_FLT_82196234) != 0) {
            M2C_FIELD(sActivePokemon[1], u8*, 1) |= 1;
        } else {
            M2C_FIELD(sActivePokemon[1], u8*, 1) &= 0xFFFE;
        }
    }
}

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

void func_82121D5C(s32, s32);
/*
 * func_82121DAC
 *
 * Only runs when the scene's unk_18 is 2.  It then checks the scene's unk_44
 * against 1, 2, 5, 6, 9 and 0xA in turn (the field is re-read after every
 * call, so a call may change it and a later check can then also succeed) and
 * calls func_82121D5C(value, argument) for each match: with 0x32 for 1, 5 and
 * 9, and with 0 for 2, 6 and 0xA.  Before the calls for 2, 6 and 0xA it also
 * copies the scene's unk_2A into unk_2C.  What unk_44 values 1/2, 5/6 and 9/0xA
 * stand for, and what func_82121D5C does with them, is not established here.
 */
void func_82121DAC(void) {
    if (sBattleScene.scene->unk_18 == 2) {
        if (sBattleScene.scene->unk_44 == 1) {
            func_82121D5C(1, 0x32);
        }
        if (sBattleScene.scene->unk_44 == 2) {
            sBattleScene.scene->unk_2C = sBattleScene.scene->unk_2A;
            func_82121D5C(2, 0);
        }
        if (sBattleScene.scene->unk_44 == 5) {
            func_82121D5C(5, 0x32);
        }
        if (sBattleScene.scene->unk_44 == 6) {
            sBattleScene.scene->unk_2C = sBattleScene.scene->unk_2A;
            func_82121D5C(6, 0);
        }
        if (sBattleScene.scene->unk_44 == 9) {
            func_82121D5C(9, 0x32);
        }
        if (sBattleScene.scene->unk_44 == 0xA) {
            sBattleScene.scene->unk_2C = sBattleScene.scene->unk_2A;
            func_82121D5C(0xA, 0);
        }
    }
}

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

extern s8 *D_8219A5A0;

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

M2C_UNK func_8000EEBC(s32, s32, f32, s16, s32);     /* extern */
extern s8 *D_8219A5A0;

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
    func_8000EEBC(arg0 + 0xB4, arg0 + 0xA8, M2C_FIELD(D_8219A5A0, f32 *, 0x5C), M2C_FIELD(D_8219A5A0, s16 *, 0x58), (s32) var_v0);
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

extern s8 *D_8219A5A0;

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

extern f32 D_FLT_82189354[][4];

/*
 * func_8212239C
 *
 * Prepares a participant's camera anchor point at +0x5D0 and saves the camera.
 * The anchor starts as the vector at +0x5DC (Vec3f_SetComponentsDuplicate), then
 * its Y (+0x5D4) is rebuilt as that vector's Y (+0x5E0) plus the display
 * object's Y position minus the object type's table entry
 * (D_FLT_82189354[type][0], the resting height func_82107790 uses). The
 * camera's target and eye are then copied into the scene's saved-target (+0xA8)
 * and saved-eye (+0xB4) slots, and the distance and angles from the anchor to
 * the camera target are stored in the model transform at +0x38 / +0x30 / +0x32
 * (the same fields func_82122A7C reads).
 *
 * The `pad` local only reproduces the retail stack frame (12 unused bytes).
 */
void func_8212239C(ActivePokemon* arg0, CameraNode* arg1) {
    UNUSED s32 pad[3];
    u8* ptr = (u8*)&arg0->modelTransform;

    Vec3f_SetComponentsDuplicate(&M2C_FIELD(arg0, Vec3f*, 0x5D0), M2C_FIELD(arg0, f32*, 0x5DC), M2C_FIELD(arg0, f32*, 0x5E0), M2C_FIELD(arg0, f32*, 0x5E4));
    M2C_FIELD(arg0, f32*, 0x5D4) = M2C_FIELD(arg0, f32*, 0x5E0) + (arg0->displayObject.position.y - D_FLT_82189354[arg0->displayObject.objectType][0]);
    BattleAnim_Vec3fCopy(&M2C_FIELD(sBattleScene.scene, Vec3f*, 0xA8), &arg1->view.targetPosition);
    BattleAnim_Vec3fCopy(&M2C_FIELD(sBattleScene.scene, Vec3f*, 0xB4), &arg1->view.eyePosition);
    BattleAnim_CalculateDistanceAngles(&M2C_FIELD(arg0, Vec3f*, 0x5D0), &arg1->view.targetPosition, &M2C_FIELD(ptr, f32*, 0x38), &M2C_FIELD(ptr, s16*, 0x30), &M2C_FIELD(ptr, s16*, 0x32));
}

extern u8 D_8219A4F4;
void func_82121D78(CameraNode* arg0, f32 arg1, f32 arg2);

/*
 * func_82122458
 *
 * Sets the camera's clip planes (BattleScene_SetCameraClipPlanes, func_82121D78)
 * for the current battle phase: always 20 / 4000 first; then 20 / 32000 while the
 * scene's phase value (unk_1C) is 4 or 8; and 60 / 32000 when that value is 9,
 * D_8219A4F4 is 5 and unk_20 is not 0x1D. What the phase values and D_8219A4F4
 * stand for has not been established. The meaning of the two floats as near/far
 * planes comes from the Stadium 1 name of func_82121D78.
 */
void func_82122458(CameraNode* arg0) {
    s32 var_v0;

    func_82121D78(arg0, 20.0f, 4000.0f);
    var_v0 = sBattleScene.scene->unk_1C;
    if ((var_v0 == 4) || (var_v0 == 8)) {
        func_82121D78(arg0, 20.0f, 32000.0f);
        var_v0 = sBattleScene.scene->unk_1C;
    }
    if ((var_v0 == 9) && (D_8219A4F4 == 5) && (sBattleScene.scene->unk_20 != 0x1D)) {
        func_82121D78(arg0, 60.0f, 32000.0f);
    }
}

void BattleScene_ClearCameraOffsetVectors(void) {
    Vec3f_SetComponentsDuplicate(&sBattleScene.scene->unk_94, 0.0f, 0.0f, 0.0f);
    Vec3f_SetComponentsDuplicate(&sBattleScene.scene->unk_A0, 0.0f, 0.0f, 0.0f);
}

typedef struct { f32 v; f32 pad[3]; } CameraTargetOffsetRow;
extern f32 D_FLT_82189358[];

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

/*
 * func_821227C0
 *
 * Called at the end of func_821228B0.  Measures distance and angles between
 * the scene's saved eye (+0xB4) and saved target (+0xA8) vectors with
 * BattleAnim_CalculateDistanceAngles.  Only when the last angle output,
 * divided by 182 (0xB6, about one degree in 16-bit angle units), is exactly
 * 90 or -90 does it go on: it measures the same pair of vectors on the camera
 * node, eases the resulting distance towards the scene distance (1.5 times it,
 * with speed 1.0, when the participant's object type is 0x65; otherwise the
 * scene distance itself with speed 0.5), and passes the camera node's eye and
 * target vectors, the eased distance and the two angles to func_8000EEBC.
 * What func_8000EEBC does with them is not established here.
 * Note: the "pad" array only reproduces the retail frame size.
 */
void func_821227C0(CameraNode* arg0, ActivePokemon* arg1) {
    UNUSED s32 pad[9];
    f32 sp38;
    s16 sp36;
    s16 sp34;
    f32 sp30;
    s16 sp2E;
    s16 sp2C;
    BattleAnim_CalculateDistanceAngles(&M2C_FIELD(sBattleScene.scene, Vec3f*, 0xB4), &M2C_FIELD(sBattleScene.scene, Vec3f*, 0xA8), &sp30, &sp2E, &sp2C);
    if (((sp2C / 182) == 0x5A) || ((sp2C / 182) == -0x5A)) {
        BattleAnim_CalculateDistanceAngles(&M2C_FIELD(arg0, Vec3f*, 0xB4), &M2C_FIELD(arg0, Vec3f*, 0xA8), &sp38, &sp36, &sp34);
        if (arg1->displayObject.objectType == 0x65) {
            BattleAnim_ApproachF(&sp38, sp30 * 1.5f, 1.0f);
        } else {
            BattleAnim_ApproachF(&sp38, sp30, 0.5f);
        }
        func_8000EEBC((s32)arg0 + 0xB4, (s32)arg0 + 0xA8, sp38, sp36, sp34);
    }
}

void func_821227C0(CameraNode*, ActivePokemon*);

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

void func_82121908(ActivePokemon* arg0, Vec3f* arg1);
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

extern f32 D_FLT_82189350[][4];
extern f32 D_FLT_82196240;

/*
 * func_82122A7C
 *
 * Moves the camera's target point towards the participant. Works out the
 * participant's camera anchor (func_82121908) and its distance/angles to the
 * point stored at +0x5D0, then eases camera->view.targetPosition: if that
 * distance is at least the object type's table width (D_FLT_82189350[type][0])
 * the new goal is the anchor offset by the model transform's own distance and
 * angles (+0x38, +0x30, +0x32 within the transform); otherwise the goal is the
 * scene's stored vector at +0xA8. The target then moves along the direction to
 * the goal by D_FLT_82196240 times the remaining distance.
 */
void func_82122A7C(CameraNode* arg0, ActivePokemon* arg1) {
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
    if (D_FLT_82189350[arg1->displayObject.objectType][0] <= sp34) {
        Camera_ComputeEyeFromAngles(&sp50, &sp44, M2C_FIELD(ptr, f32*, 0x38), M2C_FIELD(ptr, s16*, 0x30), M2C_FIELD(ptr, s16*, 0x32));
        BattleAnim_CalculateDistanceAngles(&sp38, &sp44, &sp34, &sp32, &sp30);
    } else {
        BattleAnim_CalculateDistanceAngles(&sp38, &M2C_FIELD(sBattleScene.scene, Vec3f*, 0xA8), &sp34, &sp32, &sp30);
    }
    Camera_ComputeEyeFromAngles(&sp38, sp28, sp34 * D_FLT_82196240, sp32, sp30);
}

extern f32 D_FLT_82189350[][4];
extern f32 D_FLT_82196244;

/*
 * func_82122B9C
 *
 * Variant of func_82122A7C that is skipped while the participant's
 * modelTransformId is 6 or 4 and eases the camera target by
 * D_FLT_82196244 instead of D_FLT_82196240 (see func_82122A7C for the
 * step-by-step description). The meaning of transform ids 4 and 6 has not been
 * established.
 */
void func_82122B9C(CameraNode* arg0, ActivePokemon* arg1) {
    u8* ptr = (u8*)&arg1->modelTransform;
    Vec3f sp58;
    Vec3f sp4C;
    Vec3f sp40;
    f32 sp3C;
    s16 sp3A;
    s16 sp38;
    Vec3f* sp30;

    if ((arg1->modelTransformId != 6) && (arg1->modelTransformId != 4)) {
        func_82121908(arg1, &sp58);
        BattleAnim_CalculateDistanceAngles(&sp58, &M2C_FIELD(arg1, Vec3f*, 0x5D0), &sp3C, &sp3A, &sp38);
        sp30 = &arg0->view.targetPosition;
        BattleAnim_Vec3fCopy(&sp40, sp30);
        if (D_FLT_82189350[arg1->displayObject.objectType][0] <= sp3C) {
            Camera_ComputeEyeFromAngles(&sp58, &sp4C, M2C_FIELD(ptr, f32*, 0x38), M2C_FIELD(ptr, s16*, 0x30), M2C_FIELD(ptr, s16*, 0x32));
            BattleAnim_CalculateDistanceAngles(&sp40, &sp4C, &sp3C, &sp3A, &sp38);
        } else {
            BattleAnim_CalculateDistanceAngles(&sp40, &M2C_FIELD(sBattleScene.scene, Vec3f*, 0xA8), &sp3C, &sp3A, &sp38);
        }
        Camera_ComputeEyeFromAngles(&sp40, sp30, sp3C * D_FLT_82196244, sp3A, sp38);
    }
}

extern f32 D_FLT_82189350[][4];
extern f32 D_FLT_82196248;
extern f32 D_FLT_8219624C;

/*
 * func_82122CCC
 *
 * Variant of func_82122A7C: the distance threshold is the object type's table
 * width multiplied by D_FLT_82196248 (rather than the bare width), and the
 * camera target is eased by D_FLT_8219624C times the remaining distance. See
 * func_82122A7C for the step-by-step description.
 */
void func_82122CCC(CameraNode* arg0, ActivePokemon* arg1) {
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
    if ((D_FLT_82189350[arg1->displayObject.objectType][0] * D_FLT_82196248) <= sp34) {
        Camera_ComputeEyeFromAngles(&sp50, &sp44, M2C_FIELD(ptr, f32*, 0x38), M2C_FIELD(ptr, s16*, 0x30), M2C_FIELD(ptr, s16*, 0x32));
        BattleAnim_CalculateDistanceAngles(&sp38, &sp44, &sp34, &sp32, &sp30);
    } else {
        BattleAnim_CalculateDistanceAngles(&sp38, &M2C_FIELD(sBattleScene.scene, Vec3f*, 0xA8), &sp34, &sp32, &sp30);
    }
    Camera_ComputeEyeFromAngles(&sp38, sp28, sp34 * D_FLT_8219624C, sp32, sp30);
}

void func_82122CCC(CameraNode* arg0, ActivePokemon* arg1);
void func_82107DDC(ActivePokemon* active_pokemon, Vec3f* out);

/*
 * func_82122DFC
 *
 * Earlier relative of Stadium 1's BattleScene_FrameCamera (that version also
 * handles underground and Fire Spin cases, which this one does not). Unless the
 * participant is an Onix it first runs func_82122CCC. It then saves the camera's
 * current target and eye, asks func_82107DDC for the participant's anchor and
 * sets the camera from it using the facing angle and a distance from
 * BattleScene_ScaleCameraDistance(3.5, 300). The new eye distance and angles are
 * compared with the saved ones: the distance is approached by 0.05, the Y angle
 * is stepped by 0x111 and the X angle by 0x5B per call, and the camera is
 * rebuilt from those values. The target is also moved one hundredth of the way
 * from its saved position to its new one. Returns 1 once both angles have
 * reached their goals, otherwise 0.
 */
s32 func_82122DFC(CameraNode* arg0, ActivePokemon* arg1) {
    Vec3f sp5C;
    Vec3f sp50;
    Vec3f sp44;
    f32 sp40;
    s16 sp3E;
    s16 sp3C;
    s16 sp3A;
    s16 sp38;
    s16 sp36;
    s16 sp34;

    if (arg1->displayObject.objectType != ONIX) {
        func_82122CCC(arg0, arg1);
    }
    BattleAnim_Vec3fCopy(&sp50, &arg0->view.targetPosition);
    BattleAnim_Vec3fCopy(&sp44, &arg0->view.eyePosition);
    func_82107DDC(arg1, &sp5C);
    gCameraDistTarget = BattleScene_ScaleCameraDistance(arg1, 3.5f, 300.0f);
    BattleScene_SetCameraEyeFromPosition(arg0, sp5C, 0, BattleScene_GetParticipantFacingAngle(arg1), gCameraDistTarget, 0.0f);
    BattleAnim_CalculateDistanceAngles(&arg0->view.targetPosition, &arg0->view.eyePosition, &D_8219A534, &sp34, &sp38);
    BattleAnim_CalculateDistanceAngles(&sp50, &sp44, &gCameraDistTarget, &sp36, &sp3A);
    BattleAnim_ApproachF(&gCameraDistTarget, D_8219A534, 0.05f);
    BattleAnim_StepToS16(&sp3A, sp38, 0x111);
    BattleAnim_StepToS16(&sp36, sp34, 0x5B);
    BattleAnim_CalculateDistanceAngles(&sp50, &arg0->view.targetPosition, &sp40, &sp3E, &sp3C);
    Camera_ComputeEyeFromAngles(&sp50, &arg0->view.targetPosition, sp40 / 100.0f, sp3E, sp3C);
    BattleScene_SetCameraEyeFromAt(arg0, sp36, sp3A, gCameraDistTarget, 0.0f);
    if ((sp34 == sp36) && (sp38 == sp3A)) {
        return 1;
    }
    return 0;
}

extern f32 D_FLT_82189350[][4];
extern f32 D_FLT_82196250;
extern f32 D_FLT_82196254;

/*
 * func_82122FD8
 *
 * Variant of func_82122A7C that first copies the scene's vector at +0xB4 into
 * the camera's eye position. The distance threshold is the object type's table
 * width scaled by D_FLT_82196250 and the camera target is eased by
 * D_FLT_82196254 times the remaining distance. See func_82122A7C for the
 * step-by-step description.
 */
void func_82122FD8(CameraNode* arg0, ActivePokemon* arg1) {
    u8* ptr = (u8*)&arg1->modelTransform;
    Vec3f sp58;
    Vec3f sp4C;
    UNUSED s32 pad[3];
    Vec3f sp34;
    f32 sp30;
    s16 sp2E;
    s16 sp2C;

    BattleAnim_Vec3fCopy(&arg0->view.eyePosition, &M2C_FIELD(sBattleScene.scene, Vec3f*, 0xB4));
    func_82121908(arg1, &sp58);
    BattleAnim_CalculateDistanceAngles(&sp58, &M2C_FIELD(arg1, Vec3f*, 0x5D0), &sp30, &sp2E, &sp2C);
    BattleAnim_Vec3fCopy(&sp34, &arg0->view.targetPosition);
    if ((D_FLT_82189350[arg1->displayObject.objectType][0] * D_FLT_82196250) <= sp30) {
        Camera_ComputeEyeFromAngles(&sp58, &sp4C, M2C_FIELD(ptr, f32*, 0x38), M2C_FIELD(ptr, s16*, 0x30), M2C_FIELD(ptr, s16*, 0x32));
        BattleAnim_CalculateDistanceAngles(&sp34, &sp4C, &sp30, &sp2E, &sp2C);
    } else {
        BattleAnim_CalculateDistanceAngles(&sp34, &M2C_FIELD(sBattleScene.scene, Vec3f*, 0xA8), &sp30, &sp2E, &sp2C);
    }
    Camera_ComputeEyeFromAngles(&sp34, &arg0->view.targetPosition, sp30 * D_FLT_82196254, sp2E, sp2C);
}

// Zero passes an extra, unused 4-byte struct by value; its type is a guess.
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

extern const f32 D_FLT_82196258;
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

#ifdef NON_MATCHING
/* TODO: decompile func_82123684; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_82123684.s")
#endif

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

extern const f64 D_DBL_82196260;
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

extern const f32 D_FLT_82196268;
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

extern f32 D_8219A530;
extern f32 D_8219A534;
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

#ifdef NON_MATCHING
// Matches the ROM, but uses rodata data that is not placed in this file yet.
extern f32 D_8219A530;
void func_821243DC(CameraNode* arg0, ActivePokemon* arg1, f32 arg2) {
    BattleAnim_GetOwnerDefaultAnchorPosition(arg1, &sBattleScene.scene->unk_D0);
    M2C_FIELD(sBattleScene.scene, f32*, 0x8C) = Math_StepToF(M2C_FIELD(sBattleScene.scene, f32*, 0x98), 2.8f, 0.45f, 0.45f);
    BattleAnim_ApproachF(&sBattleScene.scene->unk_74, 0.0f, M2C_FIELD(sBattleScene.scene, f32*, 0x8C));
    D_8219A530 = BattleScene_ScaleCameraDistance(arg1, 5.0f, 400.0f);
    BattleScene_SetCameraAtFromAnchor(arg1, arg0, sBattleScene.scene->unk_D0, 0, arg1->facingDirection << 14, sBattleScene.scene->unk_74, 0.0f);
    BattleScene_SetCameraEyeFromPosition(arg0, sBattleScene.scene->unk_D0, 0, arg1->facingDirection * 0x1555, D_8219A530, arg2);
    if (M2C_FIELD(arg0, f32*, 0xAC) <= 15.0f) {
        M2C_FIELD(arg0, f32*, 0xAC) = 15.0f;
    }
}
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_821243DC.s")
#endif

void func_82124544(CameraNode* arg0, ActivePokemon* arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, s16 arg6) {
    BattleAnim_GetOwnerDefaultAnchorPosition(arg1, &M2C_FIELD(sBattleScene.scene, Vec3f*, 0xC0));
    M2C_FIELD(sBattleScene.scene, f32*, 0x74) = BattleScene_ScaleCameraDistance(arg1, arg2, 50.0f * arg3);
    M2C_FIELD(sBattleScene.scene, f32*, 0x5C) = BattleScene_ScaleCameraDistance(arg1, arg4, 50.0f * arg5);
    BattleScene_SetCameraAtFromAnchor(arg1, arg0, M2C_FIELD(sBattleScene.scene, Vec3f*, 0xC0), 0, BattleScene_GetParticipantFacingAngle(arg1), 0.0f, 0.0f);
    BattleScene_SetCameraEyeFromAt(arg0, arg6, BattleScene_GetParticipantFacingAngle(arg1), M2C_FIELD(sBattleScene.scene, f32*, 0x74), 0.0f);
}

extern f32 D_FLT_82196274;
f32 func_8000F23C(f32, f32, f32, f32);
void func_8210C1A8(f32*, f32, f32);
s32 func_82107CC4(s32);
void func_8212254C(s32, s32, Vec3f, s32, s32, f32, f32);
void func_82122684(s32, s16, s16, f32, f32);
void func_82124664(s32 arg0, s32 arg1, s16 arg2) {
    f32 temp = D_FLT_82196274;

    M2C_FIELD(sBattleScene.scene, f32*, 0x8C) = func_8000F23C(M2C_FIELD(sBattleScene.scene, f32*, 0x98), 2.5f, temp, temp);
    func_8210C1A8(&sBattleScene.scene->unk_74, sBattleScene.scene->unk_5C, M2C_FIELD(sBattleScene.scene, f32*, 0x8C));
    func_8212254C(arg1, arg0, sBattleScene.scene->unk_D0, 0, func_82107CC4(arg1), 0.0f, 0.0f);
    func_82122684(arg0, arg2, func_82107CC4(arg1), sBattleScene.scene->unk_74, 0.0f);
}

void BattleAnim_GetOwnerModelBoundsScaled(ActivePokemon* arg0, Vec3f* arg1) {
    BattleScene_GetParticipantModelBoundsScaled(arg0, arg1);
}

void BattleAnim_StartEffect140StartEffect139Alias(void) {
    BattleAnim_StartEffect139DualRepeatingSparks();
}

void BattleAnim_StartEffect142StartEffect141Alias(void) {
    BattleAnim_StartEffect141GridRiseAndFallingBurst();
}

void ClefairyGame_HidePatternIcons(void) {
    ClefairyGame_DespawnPatternIcons();
}

void ClefairyGame_ShowPatternIcons(void) {
    ClefairyGame_SpawnPatternIcons();
}

// Called with (CameraNode*, ActivePokemon*); the arguments pass through untouched.
void func_821247F0(void) {
    Diorama_RenderFrame();
}

s32 func_82124810(CameraNode* arg0, ActivePokemon* arg1) {
    return LabPCList_CompareBySpeciesGroup((unk_func_8830867C_02C_0CC*)arg0, (unk_func_8830867C_02C_0CC*)arg1);
}

void func_82124830(s8 *arg0, ActivePokemon* arg1)
{
  if (arg0)
  {
  }
  func_82124054((CameraNode*)arg0, arg1);
  if ((*((f32 *) (((s8 *) arg0) + 0xB8))) <= 20.0f)
  {
    *((f32 *) (((s8 *) arg0) + 0xB8)) = 20.0f;
  }
}

// Called with (CameraNode*, ActivePokemon*); the arguments pass through untouched.
void func_82124874(void) {
    MiniFx_UpdateParticles();
}

void func_82124894(CameraNode* arg0, ActivePokemon* arg1) {
    BattleAnim_GetOwnerDefaultAnchorPosition(arg1, &sBattleScene.scene->unk_D0);
    gCameraDistTarget = BattleScene_ScaleCameraDistance(arg1, 3.5f, 300.0f);
    BattleScene_SetCameraAtFromAnchor(arg1, arg0, sBattleScene.scene->unk_D0, 0, BattleScene_GetParticipantFacingAngle(arg1), 0.0f, 0.0f);
    BattleScene_SetCameraEyeFromPosition(arg0, sBattleScene.scene->unk_D0, 0, BattleScene_GetParticipantFacingAngle(arg1), gCameraDistTarget, 0.0f);
}

#ifdef NON_MATCHING
/* TODO: decompile func_82124984; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_82124984.s")
#endif
