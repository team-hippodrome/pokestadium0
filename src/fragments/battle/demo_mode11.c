/* Stadium Zero fragment012_17ED00. */
/* C ported from the Stadium 1 decomp: src/fragments/battle_engine/battle_engine_343BA0.c. */

#include "battle.h"
#include "math.h"
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

void SceneMode11_UnusedNop(void);
void SceneMode11_StepEnd(UNUSED s32 arg0);

/**
 * Empty.
 * @unverified Name guessed from the code.
 */
void SceneMode11_UnusedNop(void) {
}

void BattleScene_CameraShotTargetHighThunk(s32, s32);
void BattleScene_FrameParticipantFromAboveThunk(s32, s32);
void BattleScene_FrameParticipantFromBelowClamped(s32, s32);
void BattleScene_FrameParticipantFrontAltThunk(s32, s32);

/**
 * Runs one of four camera framings on Pokemon active_pokemon with camera, chosen by framing (0 the
 * high target shot, 1-3 BattleScene_FrameParticipantFromAboveThunk/830/874).
 * @unverified Name guessed from the code.
 */
void SceneMode11_FrameDemoPokemon(s32 active_pokemon, s32 camera, s32 framing) {
    switch (framing) {
        case 0:
            BattleScene_CameraShotTargetHighThunk(camera, active_pokemon);
            break;
        case 1:
            BattleScene_FrameParticipantFromAboveThunk(camera, active_pokemon);
            break;
        case 2:
            BattleScene_FrameParticipantFromBelowClamped(camera, active_pokemon);
            break;
        case 3:
            BattleScene_FrameParticipantFrontAltThunk(camera, active_pokemon);
            break;
    }
}

void BattleScene_GetParticipantAimPoint(s32, Vec3f*);
void func_8212254C(s32, s32, Vec3f, s32, s32, f32, f32);
void func_82122628(s32, Vec3f, s32, s32, f32, f32);
/**
 * Frames Pokemon active_pokemon from its aim point: target from angle 0x4000 at zoom, eye at the
 * angles (rotation_x, rotation_y) and the distance.
 * @unverified Name guessed from the code.
 */
void SceneMode11_FrameFromAimPoint(s32 camera, s32 active_pokemon, f32 distance, f32 zoom, s16 rotation_x, s16 rotation_y) {
    BattleScene_GetParticipantAimPoint(active_pokemon, &sBattleScene.scene->anchorPosition);
    func_8212254C(active_pokemon, camera, sBattleScene.scene->anchorPosition, 0, 0x4000, zoom, 0.0f);
    func_82122628(camera, sBattleScene.scene->anchorPosition, rotation_x, rotation_y, distance, 0.0f);
}

extern s16 D_8219A4F0[];
extern s8* D_8219A590;
void BattleCamera_PlayShot(s8* arg0, CameraNode* arg1, s32 arg2);

/**
 * Scene mode 11 step 0: clears the demo indices, sets clip planes 20-4000, picks side 0 as
 * the demo Pokemon, plays its camera shot 3, shrinks the stage to scale 0 and advances.
 * @unverified Name guessed from the code.
 */
void SceneMode11_StepInit(CameraNode* camera) {
    D_8219A4F0[0xE] = 0;
    D_8219A4F0[0xD] = 0;
    BattleScene_SetCameraClipPlanes(camera, 20.0f, 4000.0f);
    BattleScene_ResetCameraFrameCounter();
    sBattleScene.scene->actingSide = 0;
    D_8219A590 = (s8*)sActivePokemon[sBattleScene.scene->actingSide];
    BattleCamera_PlayShot(D_8219A590, camera, 3);
    Battle_SetStageScale(0.0f);
    sBattleScene.scene->phaseStep++;
}

s32 Audio_PlaySystemSound(s32);
void ModelAnim_SetAnimation(s8*, s32);
void ModelAnim_SetFrame(s8*, s32);
s32 func_82107A5C(s8*);
void BattleCamera_StartDemoPath(CameraNode*, s8*);
extern PokemonBattleCues* D_82189180[];
extern s16 D_8219A50C;
extern u8 D_8219A4F4;
extern u8 D_8219A594;
/**
 * Starts demo cut D_8219A50C (0-5) of scene mode 11: plays a sound, frames the demo
 * Pokemon (raising it by 500 in cut 1), and starts its move-cue animation and model
 * reaction from the cut tables. The cuts use the cues of Pound, Fly, Rolling Kick, Stomp,
 * Take Down and Hydro Pump.
 * @unverified Name guessed from the code.
 */
void SceneMode11_StartCut(CameraNode* camera) {
    u8 sp40[6] = { POUND, FLY, ROLLING_KICK, STOMP, TAKE_DOWN, HYDRO_PUMP };
    u8 sp38[6] = { 0, 12, 14, 15, 70, 27 };
    MovePresentationCue* cue = D_82189180[func_82107A5C(D_8219A590)]->moveCues + sp40[D_8219A50C] - 1;

    switch (D_8219A50C) {
        case 0:
            Audio_PlaySystemSound(0x12);
            SceneMode11_FrameDemoPokemon((s32)D_8219A590, (s32)camera, 3);
            ModelAnim_SetAnimation(D_8219A590, cue->id);
            ModelAnim_SetFrame(D_8219A590, sp38[D_8219A50C]);
            break;
        case 1:
            Audio_PlaySystemSound(0x13);
            ((ActivePokemon*)D_8219A590)->displayObject.position.y += 500.0;
            SceneMode11_FrameFromAimPoint((s32)camera, (s32)D_8219A590, 350.0f, 0.0f, -0x1C71, 0x38E3);
            ModelAnim_SetAnimation(D_8219A590, cue->id);
            ModelAnim_SetFrame(D_8219A590, sp38[D_8219A50C]);
            break;
        case 2:
            Audio_PlaySystemSound(0x14);
            ((ActivePokemon*)D_8219A590)->displayObject.rotation.y = -0x4000;
            SceneMode11_FrameFromAimPoint((s32)camera, (s32)D_8219A590, 300.0f, -75.0f, 0x71C, -0x2AAA);
            ModelAnim_SetAnimation(D_8219A590, cue->id);
            ModelAnim_SetFrame(D_8219A590, sp38[D_8219A50C]);
            break;
        case 3:
            Audio_PlaySystemSound(0x15);
            SceneMode11_FrameFromAimPoint((s32)camera, (s32)D_8219A590, 200.0f, 0.0f, 0x71C, 0x2AAA);
            ModelAnim_SetAnimation(D_8219A590, cue->id);
            ModelAnim_SetFrame(D_8219A590, sp38[D_8219A50C]);
            break;
        case 4:
            Audio_PlaySystemSound(0x16);
            ((ActivePokemon*)D_8219A590)->displayObject.rotation.y = -0x4000;
            SceneMode11_FrameFromAimPoint((s32)camera, (s32)D_8219A590, 600.0f, -200.0f, 0, -0x238E);
            ModelAnim_SetAnimation(D_8219A590, cue->id);
            ModelAnim_SetFrame(D_8219A590, sp38[D_8219A50C]);
            break;
        case 5:
            Audio_PlaySystemSound(0x17);
            ModelAnim_SetFrame(D_8219A590, sp38[D_8219A50C]);
            D_8219A4F4 = 0xA;
            BattleCamera_StartDemoPath(camera, D_8219A590);
            break;
    }
    D_8219A594 = 0;
}


/**
 * Starts the current demo cut and advances the phase step.
 * @unverified Name guessed from the code.
 */
void SceneMode11_StepStartCut(CameraNode* camera) {
    SceneMode11_StartCut(camera);
    sBattleScene.scene->phaseStep = (s32) (sBattleScene.scene->phaseStep + 1);
}

M2C_UNK BattleCamera_StepDemoPath(CameraNode*, s8*);
extern s16 D_8219A50C;
M2C_UNK Model_SetMaterialColor(s8 *, M2C_UNK, M2C_UNK, M2C_UNK, s32);
s32 BattleScene_AdvanceCameraFrameCounter(M2C_UNK);
extern u8 D_8219A594;
extern u8 D_8219A4F4;
s16 Math_StepToS32(s16, M2C_UNK, M2C_UNK, M2C_UNK);
void Announcer_CallMove(s32, s32, s32, s32);
void func_82104C68(s8*, s32);
/**
 * Fades the demo Pokemon in over 30 frames. Cuts 0-4 advance after 40 frames; cut 5 follows
 * the Pokemon with the camera and plays its sound when the scene state is 4.
 * @unverified Name guessed from the code.
 */
void SceneMode11_StepFadeInCut(CameraNode* camera) {
    D_8219A594 = Math_StepToS32(D_8219A594, 0xFF, 0x1E, 0x1E);
    Model_SetMaterialColor(D_8219A590, 0, 0, 0, 0xFF - D_8219A594);
    switch (*(u16*)&D_8219A50C) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
            if (BattleScene_AdvanceCameraFrameCounter(40) != 0) {
                sBattleScene.scene->phaseStep = (s32) (sBattleScene.scene->phaseStep + 1);
            }
            break;
        case 5:
            BattleCamera_StepDemoPath(camera, D_8219A590);
            if (sBattleScene.scene->splineSegment == 4) {
                Announcer_CallMove(0, 0x38, 9, 0);
                D_8219A4F4 = 1;
                func_82104C68(D_8219A590, 0x14);
                sBattleScene.scene->phaseStep = (s32) (sBattleScene.scene->phaseStep + 1);
            }
            break;
    }
}

/*
 * SceneMode11_StepHoldCut
 *
 * Entry 3 of the 7-way dispatch in SceneMode11_Update (see its comment).  Its
 * argument is typed CameraNode* in this file.  Sets D_8219A594 (a byte) to
 * 0xFF, then:
 *   - if D_8219A50C == 5: calls BattleCamera_StepDemoPath(arg0, D_8219A590); if the
 *     upper halfword of the word at offset 0x48 of the object
 *     D_8219A590 points to is 0x26, calls Audio_PlayMoveSound(0x38, 9, 0); and if
 *     BattleScene_AdvanceCameraFrameCounter(0x37) returns non-zero, sets sBattleScene.scene->winner
 *     to 3, calls func_80006998(0xFFFF),
 *     StageFade_StartFromTransparent(4) and Audio_FadeAndClearStoredSounds(), and sets
 *     sBattleScene.scene->phaseStep to 6;
 *   - otherwise adds 1 to sBattleScene.scene->phaseStep.
 *
 * The second argument of BattleCamera_StepDemoPath is D_8219A590; the first is
 * `arg0` passed straight through (the retail code loads it into $a1 and
 * leaves $a0 untouched).  What these values mean is not established.
 */
M2C_UNK StageFade_StartFromTransparent(M2C_UNK);
M2C_UNK func_80006998(M2C_UNK);
M2C_UNK Audio_PlayMoveSound(M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK Audio_FadeAndClearStoredSounds();
s32 BattleScene_AdvanceCameraFrameCounter(M2C_UNK);
M2C_UNK BattleCamera_StepDemoPath(CameraNode*, s8*);
extern s16 D_8219A50C;
extern u8 D_8219A594;

/**
 * Holds the demo cut at full alpha. Cut 5 follows the Pokemon, plays move sound 0x38 on
 * frame 0x26 of its animation, and after 55 frames stops the audio and sets phase step 6;
 * other cuts advance at once.
 * @unverified Name guessed from the code.
 */
void SceneMode11_StepHoldCut(CameraNode* camera) {
    D_8219A594 = 0xFF;
    if (D_8219A50C == 5) {
        BattleCamera_StepDemoPath(camera, D_8219A590);
        if (((s32) M2C_FIELD(D_8219A590, s32 *, 0x48) >> 0x10) == 0x26) {
            Audio_PlayMoveSound(0x38, 9, 0);
        }
        if (BattleScene_AdvanceCameraFrameCounter(55) != 0) {
            sBattleScene.scene->winner = 3;
            func_80006998(0xFFFF);
            StageFade_StartFromTransparent(4);
            Audio_FadeAndClearStoredSounds();
            sBattleScene.scene->phaseStep = 6;
        }
    } else {
        sBattleScene.scene->phaseStep = (s32) (sBattleScene.scene->phaseStep + 1);
    }
}

typedef struct Arr82133534 { u8 b[7]; } Arr82133534;
extern Arr82133534 D_8218B350;
s16 Math_StepToS32(s16, M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK Model_SetMaterialColor(s8 *, M2C_UNK, M2C_UNK, M2C_UNK, s32);
/**
 * Scene mode 11 step 4: fades the demo Pokémon out and, after 8 frames, loads the next species from
 * the cut model list (D_8218B350) or ends the sequence at 0xFF.
 * @unverified Name guessed from the code.
 */
void SceneMode11_StepFadeOutAndSwapModel(CameraNode *camera)
{
  s32 pad[2]; // FAKE: stack padding
  Arr82133534 sp28 = D_8218B350;
  s32 v;
  D_8219A594 = Math_StepToS32(D_8219A594, 0, 0x28, 0x28);
  Model_SetMaterialColor(D_8219A590, 0, 0, 0, 0xFF - D_8219A594);
  if (BattleScene_AdvanceCameraFrameCounter(8) != 0)
  {
    D_8219A4F0[0xE]++;
    v = sp28.b[D_8219A4F0[0xE]];
    if (v == 0xFF)
    {
      sBattleScene.scene->phaseStep = 6;
 if (1) { }  // karodo
    }
    else
    {
      ((ActivePokemon*)D_8219A590)->side->displayModel = v; // FAKE: cast because D_8219A590 is declared s8*
      ((ActivePokemon*)D_8219A590)->side->modelFlags |= 0x80;
      sBattleScene.scene->phaseStep++;
    }
  }
}

M2C_UNK Model_SetMaterialColor(s8 *, M2C_UNK, M2C_UNK, M2C_UNK, s32); /* extern */
void Battle_LoadOwnerModelForSwitchIn(ActivePokemon* active_pokemon);                      /* extern */
M2C_UNK func_8213B31C(M2C_UNK);                     /* extern */
extern s8 *D_8219A590;
extern u8 D_8219A594;

/**
 * Once the demo Pokemon's model reload is done (bit 0x10), reloads its switch-in model,
 * restarts the demo cut at full alpha and sets phase step 2.
 * @unverified Name guessed from the code.
 */
void SceneMode11_StepWaitModelReload(s32 camera) {
    u8 *temp_v0;

    if (((ActivePokemon*)D_8219A590)->side->modelFlags & 0x10) {
        func_8213B31C(2);
        temp_v0 = &((ActivePokemon*)D_8219A590)->side->modelFlags;
        *temp_v0 &= 0xFF6F;
        Battle_LoadOwnerModelForSwitchIn(D_8219A590);
        SceneMode11_StartCut(camera);
        Model_SetMaterialColor(D_8219A590, 0, 0, 0, 0xFF);
        D_8219A594 = 0;
        sBattleScene.scene->phaseStep = 2;
    }
}

/**
 * Empty.
 * @unverified Name guessed from the code.
 */
void SceneMode11_StepEnd(UNUSED s32 unused) {
}

void SceneMode11_StepFadeInCut(CameraNode* arg0);
void SceneMode11_StepHoldCut(CameraNode* arg0);
void SceneMode11_StepFadeOutAndSwapModel(CameraNode* arg0);

/**
 * Scene mode 11 (a demo sequence of move cuts): runs the step for the current phase step
 * (sBattleScene.scene->phaseStep, 0-6): 0 SceneMode11_StepInit, 1 SceneMode11_StepStartCut,
 * 2 SceneMode11_StepFadeInCut, 3 SceneMode11_StepHoldCut, 4 SceneMode11_StepFadeOutAndSwapModel,
 * 5 SceneMode11_StepWaitModelReload, 6 SceneMode11_StepEnd. Any other step does nothing.
 * Stadium 1 has the same switch shape in BattleScene_PhaseFaintAfterResidualDamage.
 * @unverified Name guessed from the code.
 */
void SceneMode11_Update(CameraNode* camera) {
    switch (sBattleScene.scene->phaseStep) {
        case 0:
            SceneMode11_StepInit(camera);
            break;

        case 1:
            SceneMode11_StepStartCut(camera);
            break;

        case 2:
            SceneMode11_StepFadeInCut(camera);
            break;

        case 3:
            SceneMode11_StepHoldCut(camera);
            break;

        case 4:
            SceneMode11_StepFadeOutAndSwapModel(camera);
            break;

        case 5:
            SceneMode11_StepWaitModelReload((s32)camera);
            break;

        case 6:
            SceneMode11_StepEnd((s32)camera);
            break;
    }
}
