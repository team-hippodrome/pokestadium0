#ifndef ZERO_BATTLE_ENGINE_3055E0_H
#define ZERO_BATTLE_ENGINE_3055E0_H

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

#include "model_renderer.h"
#include "fragments/particle_math/particle_math.h"
#include "memory.h"

#include "fragments/clefairy_game/clefairy_game.h"
#include "model_animation.h"
#include "model_animation_events.h"
#include "geo_layout.h"
#include "display_object_textures.h"
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
#include "save_data.h"
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
#include "game_state.h"
#include "table_view.h"
#include "gb_save.h"
#include "hal_libc.h"
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
#include "audio_sound_state.h"
#include "audio_channel.h"
#include "audio_commands_category2.h"
#include "audio_category_fade.h"
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
void func_82124874();

void BattleScene_SetCameraAnglesAndDistance(s16 arg0, s16 arg1, f32 arg2);
void BattleScene_SetCameraAtFromAnchor(ActivePokemon* arg0, CameraNode* arg1, Vec3f arg2, s16 arg3, s16 arg4, f32 arg5, f32 arg6);
void BattleAnim_StartEffect139DualRepeatingSparks(void);
void BattleAnim_StartEffect141GridRiseAndFallingBurst(void);
void Diorama_RenderFrame(void);
s32 LabPCList_CompareBySpeciesGroup(unk_func_8830867C_02C_0CC* arg0, unk_func_8830867C_02C_0CC* arg1);

void func_82121908(ActivePokemon* arg0, Vec3f* arg1);

void BattleScene_SetDamageShakeAmplitude(ActivePokemon* arg0);

void BattleScene_ApplyCameraShake(CameraNode* arg0);

extern s8 *D_8219A5A0;

void func_82122104(s32 arg0);

M2C_UNK func_8000EEBC(s32, s32, f32, s16, s32);     /* extern */

s32 func_821221C0(s32 arg0, s16 arg1, s16 arg2);

s32 BattleScene_ApproachCameraRollNoEyeUpdate(UNUSED CameraNode* arg0, s16 arg1, s16 arg2);

void func_82122334(s16 arg0, s16 arg1, f32 arg2);

void func_82122374(s8 *arg0);

void BattleScene_ClearCameraOffsetVectors(void);

typedef struct { f32 v; f32 pad[3]; } CameraTargetOffsetRow;
extern f32 D_FLT_82189358[];

void func_821227C0(CameraNode*, ActivePokemon*);

void func_821228B0(CameraNode* arg0, ActivePokemon* arg1);

void BattleScene_ApproachCameraTarget(CameraNode* arg0, ActivePokemon* arg1);

// Zero passes an extra, unused 4-byte struct by value; its type is a guess.
void func_8212311C(CameraNode* arg0, ActivePokemon* arg1, Color_RGBA8 arg2);

extern const f32 D_FLT_82196258;
void func_82123314(CameraNode* arg0, ActivePokemon* arg1);

void BattleScene_SetCameraOwnerWideShot(CameraNode* arg0, ActivePokemon* arg1);

void BattleScene_SetCameraPresetClose(CameraNode* arg0, ActivePokemon* arg1);

void BattleScene_SetCameraFollowPresetNear(CameraNode* arg0, ActivePokemon* arg1);

extern const f64 D_DBL_82196260;
void BattleScene_SetCameraPresetLowClose(CameraNode* arg0, ActivePokemon* arg1);

void BattleScene_CameraShotTargetClose(CameraNode* arg0, ActivePokemon* arg1);

void func_82123D4C(CameraNode* arg0, ActivePokemon* arg1);

void BattleScene_CameraShotTargetHigh(CameraNode* arg0, ActivePokemon* arg1);

void func_82123F44(CameraNode* arg0, ActivePokemon* arg1);

extern const f32 D_FLT_82196268;
void func_82124054(CameraNode* arg0, ActivePokemon* arg1);

void func_82124194(CameraNode* arg0, ActivePokemon* arg1);

extern f32 D_8219A530;
void func_82124284(CameraNode* arg0, ActivePokemon* arg1, f32 arg2);

void func_821243DC(CameraNode* arg0, ActivePokemon* arg1, f32 arg2);

void func_82124544(CameraNode* arg0, ActivePokemon* arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, s16 arg6);

extern f32 D_FLT_82196274;
f32 func_8000F23C(f32, f32, f32, f32);
void func_8210C1A8(f32*, f32, f32);
s32 func_82107CC4(s32);
void func_8212254C(s32, s32, Vec3f, s32, s32, f32, f32);
void func_82122684(s32, s16, s16, f32, f32);
void func_82124664(s32 arg0, s32 arg1, s16 arg2);

// Called with (CameraNode*, ActivePokemon*); the arguments pass through untouched.

void func_82124830(CameraNode* arg0, ActivePokemon* arg1);

// Called with (CameraNode*, ActivePokemon*); the arguments pass through untouched.

void func_82124894(CameraNode* arg0, ActivePokemon* arg1);

#endif
