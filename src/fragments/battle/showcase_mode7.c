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

void SceneMode7_UnusedNop(void);

/**
 * Empty.
 * @unverified Name guessed from the code.
 */
void SceneMode7_UnusedNop(void) {
}

M2C_UNK func_80006998(M2C_UNK);                     /* extern */
M2C_UNK func_8212188C();                            /* extern */
M2C_UNK func_82121D78(s32, M2C_UNK, M2C_UNK);       /* extern */
M2C_UNK BattleCamera_PlayShot(s8 *, s32, M2C_UNK);        /* extern */
M2C_UNK func_82136918(s32, M2C_UNK);                /* extern */
extern s8 *D_82199DE0;
extern s8 *D_8219A580;

/**
 * Scene mode 7 step 0: camera preset 0, clip planes 20-4000, picks side 0 as the featured
 * Pokemon, plays its camera shot 3, starts its model reaction 9, stops music and advances.
 * @unverified Name guessed from the code.
 */
void SceneMode7_StepInit(s32 camera) {
    s8 *sp1C;

    sp1C = D_82199DE0 + 0x78C;
    sBattleScene.scene->cameraPresetId = 0;
    func_82121D78(camera, 0x41A00000, 0x457A0000);
    func_8212188C();
    sBattleScene.scene->actingSide = 0U;
    D_8219A580 = (&D_82199DE0)[sBattleScene.scene->actingSide];
    M2C_FIELD(sp1C, s32 *, 8) = 0;
    BattleCamera_PlayShot(D_8219A580, camera, 3);
    func_82136918((s32)((ActivePokemon*)D_8219A580)->side, 9);
    func_80006998(0);
    sBattleScene.scene->phaseStep = (s32) (sBattleScene.scene->phaseStep + 1);
}

s32 func_82101FD4(s32);                             /* extern */

/**
 * Advances the phase step once the featured Pokemon's model is ready.
 * @unverified Name guessed from the code.
 */
void SceneMode7_StepWaitModelReady(s32 camera) {
    if (func_82101FD4(D_8219A580) != 0) {
        sBattleScene.scene->phaseStep = (s32) (sBattleScene.scene->phaseStep + 1);
    }
}

/*
 * SceneMode7_StepStartCameraPath
 *
 * Clears the byte at D_8219A4F1, calls BattleCamera_StartSpeciesPath(arg0, D_8219A580) and
 * func_82104C68(D_8219A580, 1), then adds 1 to
 * sBattleScene.scene->phaseStep, which is advanced by neighboring
 * functions in this file in the same way (see SceneMode7_StepWaitModelReady), so it
 * is a step counter.
 */
extern s8 D_8219A4F1;
void BattleCamera_StartSpeciesPath(CameraNode* arg0, s8* arg1);
void func_82104C68(s8* arg0, s32 arg1);

/**
 * Starts camera path 0x19 on the featured Pokemon with model reaction 1 and advances.
 * @unverified Name guessed from the code.
 */
void SceneMode7_StepStartCameraPath(CameraNode* camera) {
    D_8219A4F1 = 0;
    BattleCamera_StartSpeciesPath(camera, D_8219A580);
    func_82104C68(D_8219A580, 1);
    sBattleScene.scene->phaseStep = (s32) (sBattleScene.scene->phaseStep + 1);
}

/*
 * SceneMode7_StepFollowCameraPath
 *
 * Calls BattleCamera_StepPathLateEase(arg0, D_8219A580).  If that returns non-zero, adds 1
 * to sBattleScene.scene->phaseStep.
 * SceneMode7_StepWaitModelReady, just above, is the same pattern with func_82101FD4 and a
 * single argument.  What the counter at +0x20 counts is not established
 * from the code alone.
 */
s32 BattleCamera_StepPathLateEase(CameraNode* camera, ActivePokemon* active_pokemon);

/**
 * Advances the phase step once the camera path on the featured Pokemon finishes.
 * @unverified Name guessed from the code.
 */
void SceneMode7_StepFollowCameraPath(CameraNode* camera) {
    if (BattleCamera_StepPathLateEase(camera, D_8219A580) != 0) {
        sBattleScene.scene->phaseStep = (s32) (sBattleScene.scene->phaseStep + 1);
    }
}

M2C_UNK func_80006998(M2C_UNK);
s32 StageFade_Start(s32);
/**
 * Looks at the word at offset 8 of the state block (D_8219A580 + 0x78C, i.e.
 * ActivePokemonState::rosterIndex).  If rosterIndex + 1 is 6 or more as an
 * unsigned value (rosterIndex outside -1..4), it writes 3 to offset 0x40 and 7
 * to sBattleScene.scene->phaseStep and returns.
 * Otherwise it calls func_80006998(0) and StageFade_Start(5) and adds 1 to the
 * word at offset 0x20, the same step counter that SceneMode7_StepWaitModelReady and
 * SceneMode7_StepStartCameraPath advance.  What the two values written in the first case mean
 * is not established from the code alone.
 * Note: the local "st" is only there to reproduce the retail register use;
 * the ROM also computes D_8219A580 + 0x78C in a branch delay slot.
 * @unverified Name guessed from the code.
 */
void SceneMode7_StepFadeOutOrFinish(CameraNode* camera) {
    s8* st = D_8219A580 + 0x78C;
    if ((u32)(M2C_FIELD(st, s32*, 8) + 1) >= 6U) {
        sBattleScene.scene->winner = 3;
        sBattleScene.scene->phaseStep = 7;
        return;
    }
    func_80006998(0);
    StageFade_Start(5);
    sBattleScene.scene->phaseStep = (s32)(sBattleScene.scene->phaseStep + 1);
}

s32 func_821217DC(s32);
/**
 * Once func_821217DC(0xA) returns non-zero it advances the roster index of the
 * Pokemon in D_8219A580 (state.rosterIndex) by one and makes that roster entry
 * the current one in the session teams block: side->displayModel gets
 * the first byte of the new entry, side->unk_04 is pointed at the entry
 * itself, and bit 0x80 is set in side->uniqueStatusFlags.  It then adds
 * 1 to the word at sBattleScene.scene->phaseStep, the same
 * step counter that SceneMode7_StepWaitModelReady and SceneMode7_StepStartCameraPath advance.
 * The meaning of the entry's first byte and of flag 0x80 is not established
 * here.  Notes: the casts of D_8219A580 repeat because the ROM re-reads the
 * global for each statement, and "mon" is only used for the first read (the ROM
 * keeps its address in a register); camera is unused.
 * @unverified Name guessed from the code.
 */
void SceneMode7_StepLoadNextRosterPokemon(UNUSED CameraNode* camera) {
    ActivePokemonState* st = &((ActivePokemon*)D_8219A580)->state;
    BattleMon* mon;

    if (func_821217DC(10) != 0) {
        st->rosterIndex++;
        mon = &((ActivePokemon*)D_8219A580)->teamRoster->pokemonPicked[st->rosterIndex];
        ((ActivePokemon*)D_8219A580)->side->displayModel = mon->species.id;
        ((ActivePokemon*)D_8219A580)->side->displayMon = &((ActivePokemon*)D_8219A580)->teamRoster->pokemonPicked[st->rosterIndex];
        ((ActivePokemon*)D_8219A580)->side->modelFlags |= 0x80;
        sBattleScene.scene->phaseStep = sBattleScene.scene->phaseStep + 1;
    }
}

/**
 * Case 6 of the scene-state switch in SceneMode7_Update. The word at
 * D_8219A580 + 0x85C is a pointer to a flag byte. If bit 0x10 of that byte is
 * set, the code clears bits 0x10 and 0x80 in it (the mask is 0xFF6F), calls
 * Battle_LoadOwnerModelForSwitchIn with D_8219A580, calls StageFade_Start(0xF), and sets
 * sBattleScene.scene->phaseStep to 2, the field SceneMode7_Update switches on.
 * The argument is not used. What the flag bits and the
 * two calls mean is not established from this function.
 * @unverified Name guessed from the code.
 */
void SceneMode7_StepWaitModelReload(CameraNode* camera) {
    u8* flags;

    flags = &((ActivePokemon*)D_8219A580)->side->modelFlags;
    if (*flags & 0x10) {
        *flags &= 0xFF6F;
        Battle_LoadOwnerModelForSwitchIn(D_8219A580);
        StageFade_Start(0xF);
        sBattleScene.scene->phaseStep = 2;
    }
}

// Zero's version takes only the particle; the header keeps Stadium 1's callback signature.
/**
 * Steps the camera along the featured Pokémon's path in D_8219A580 with a late ease.
 * @unverified Name guessed from the code.
 */
void BattleCamera_StepFeaturedPokemonPath(Particle* camera) {
    BattleCamera_StepPathLateEase(camera, D_8219A580);
}

void SceneMode7_StepStartCameraPath(CameraNode* arg0);
void SceneMode7_StepFollowCameraPath(CameraNode* arg0);
void SceneMode7_StepFadeOutOrFinish(CameraNode* arg0);
void SceneMode7_StepLoadNextRosterPokemon(CameraNode* arg0);
void SceneMode7_StepWaitModelReload(CameraNode* arg0);

/**
 * Scene mode 7, a single-Pokemon showcase: runs the step for the current phase step.
 * @unverified Name guessed from the code.
 */
void SceneMode7_Update(CameraNode* camera) {
    switch (sBattleScene.scene->phaseStep) {
        case 0:
            SceneMode7_StepInit((s32)camera);
            break;
        case 1:
            SceneMode7_StepWaitModelReady((s32)camera);
            break;
        case 2:
            SceneMode7_StepStartCameraPath(camera);
            break;
        case 3:
            SceneMode7_StepFollowCameraPath(camera);
            break;
        case 4:
            SceneMode7_StepFadeOutOrFinish(camera);
            break;
        case 5:
            SceneMode7_StepLoadNextRosterPokemon(camera);
            break;
        case 6:
            SceneMode7_StepWaitModelReload(camera);
            break;
        case 7:
            BattleCamera_StepFeaturedPokemonPath((Particle*)camera);
            break;
    }
}
