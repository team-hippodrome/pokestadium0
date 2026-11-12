/* Fixed-layout split; original translation-unit boundaries remain unconfirmed. */
#include "battle_engine_move_model_transforms.h"

void BattleScene_UpdateSecondaryModelTrailPosition(ActivePokemon* pokemon, s16 new_position) {
    s32 i;
    f32 distance;
    s16 angle_x;
    s16 angle_y;
    UNUSED s32 pad; // FAKE: stack padding
    f32 eye[3] = { 0.5f, 0.4f, 0.3f };    // Zero afterimage spacing at D_821891D8
    f32 rate[3] = { 0.98f, 0.96f, 0.95f }; // D_84384644

    for (i = 0; i < 2; i++) {
        ModelAnim_SetFrame(&pokemon->afterimages[i].displayObject, pokemon->displayObject.transformAnim.frameFixed >> 0x10);
        ModelAnim_SetAnimation(&pokemon->afterimages[i].displayObject, pokemon->displayObject.transformAnim.animationId);
        Vec3f_CalculateDistanceAngles(&pokemon->displayObject.position, &pokemon->afterimages[i].displayObject.position, &distance, &angle_x, &angle_y);
        Camera_ComputeEyeFromAngles(&pokemon->displayObject.position, &pokemon->afterimages[i].displayObject.position, eye[i] * distance, angle_x, angle_y);
        BattleAnim_StepToS16(&pokemon->afterimages[i].displayObject.rotation.y, pokemon->displayObject.rotation.y, rate[i] * new_position);
    }
}


void BattleScene_ResetParticipantModelFlags(ActivePokemon* active_pokemon) {
    BattleScene_SetParticipantModelTransform(active_pokemon, 0, 0);
}

/**
 * Places the Poke Ball above the field on this Pokemon's side and starts its sway.
 * @unverified Name and comment guessed from the code.
 */
void BattleAnim_PokeBallThrowStart(UNUSED ActivePokemon* owner, ActivePokemon* animated_pokemon) {
    animated_pokemon->pokeBall.node.flags |= 1;
    if (animated_pokemon == sActivePokemon[0]) {
        Vec3f_SetComponentsDuplicate(&animated_pokemon->pokeBall.position, 35.0f, 50.0f, -250.0f);
    } else {
        Vec3f_SetComponentsDuplicate(&animated_pokemon->pokeBall.position, -35.0f, 50.0f, -250.0f);
    }
    BattleAnim_InitSwayOffset(animated_pokemon, 20.0f, 0x1FFE);
    animated_pokemon->modelTransformTimer++;
    animated_pokemon->pokeBall.node.renderFlags &= ~0x20;
    ModelAnim_SetFrame(&animated_pokemon->pokeBall, 0);
}

/**
 * Spins the Poke Ball and lets it fall; hides it once it drops below the floor.
 * @unverified Name and comment guessed from the code.
 */
void BattleAnim_PokeBallThrowContinue(ActivePokemon* owner, ActivePokemon* animated_pokemon) {
    if (animated_pokemon == sSide1ActivePokemon) {
        BattleAnim_UpdateSwayPhysicsToTarget(owner, animated_pokemon, 0, 0, 0x1FFE, 0x4440);
    } else {
        BattleAnim_UpdateSwayPhysicsToTarget(owner, animated_pokemon, 0, 0, 0x1FFE, 0x3BB8);
    }

    animated_pokemon->pokeBall.rotation.x += 5461;
    animated_pokemon->pokeBall.rotation.z += 3640;

    if (animated_pokemon->pokeBall.position.y < 0) {
        animated_pokemon->pokeBall.node.flags &= ~1;
        animated_pokemon->pokeBall.position.y = 0.0f;
        animated_pokemon->modelTransform.rotation.y = 0.0f;
        BattleScene_ResetParticipantModelFlags(animated_pokemon);
    }
}

/**
 * Poke Ball throw model transform (case 1): start, then continue.
 * @unverified Name and comment guessed from the code.
 */
void BattleAnim_PokeBallThrow(s32 arg0, s8 *arg1) {
    s32 temp_v0;

    temp_v0 = M2C_FIELD(arg1, s32 *, 0x614);
    switch (temp_v0) {                              /* irregular */
    case 0:
        BattleAnim_PokeBallThrowStart((ActivePokemon*)arg0, (ActivePokemon*)arg1);
        /* fallthrough */
    case 1:
        BattleAnim_PokeBallThrowContinue(arg0, arg1);
        return;
    }
}

void BattleAnim_PokeBallLandStart(UNUSED ActivePokemon* owner, ActivePokemon* animated_pokemon) {
    Vec3f_SetComponentsDuplicate(&animated_pokemon->pokeBall.position, animated_pokemon->facingDirection * -150.0f, 100.0f, 0.0f);
    animated_pokemon->modelTransformTimer++;
    BattleAnim_InitSwayOffset(animated_pokemon, 0.0f, 16380);
    animated_pokemon->pokeBall.node.flags |= 1;
    animated_pokemon->pokeBall.node.renderFlags &= ~0x20;
    ModelAnim_SetFrame(&animated_pokemon->pokeBall, 0);
}

void BattleAnim_PokeBallLandContinue(ActivePokemon* owner, ActivePokemon* animated_pokemon) {
    animated_pokemon->pokeBall.rotation.x += 5461;
    animated_pokemon->pokeBall.rotation.z += 3640;

    BattleAnim_UpdateSwayPhysicsToTarget(owner, animated_pokemon, 0.0f, 0.0f, NINETY_DEGREES, 0);

    if (animated_pokemon->pokeBall.position.y < 0) {
        animated_pokemon->pokeBall.rotation.x = 0;
        animated_pokemon->pokeBall.rotation.z = 0;
        if (animated_pokemon == sSide1ActivePokemon) {
            animated_pokemon->pokeBall.rotation.y = NINETY_DEGREES;
        } else {
            animated_pokemon->pokeBall.rotation.y = -NINETY_DEGREES;
        }
        animated_pokemon->modelTransform.rotation.y = 0.0f;
        animated_pokemon->pokeBall.position.y = 2.5f;
        BattleScene_ResetParticipantModelFlags(animated_pokemon);
    }
}

/**
 * Poke Ball landing model transform (case 2).
 * @unverified Name and comment guessed from the code.
 */
void BattleAnim_PokeBallLand(s32 arg0, s8 *arg1) {
    s32 temp_v0;

    temp_v0 = M2C_FIELD(arg1, s32 *, 0x614);
    switch (temp_v0) {                              /* irregular */
    case 0:
        func_82109E60((ActivePokemon*)arg0, (ActivePokemon*)arg1);
        /* fallthrough */
    case 1:
        func_82109EF8(arg0, arg1);
        return;
    }
}

/**
 * fly start
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void BattleAnim_FlyStart(UNUSED ActivePokemon* owner, ActivePokemon* animated_pokemon) {
    Vec3f_SetComponentsDuplicate(&animated_pokemon->modelTransform, 0.0f, 0.0f, 0.0f);
    Vec3f_SetComponentsDuplicate(&animated_pokemon->modelTransform.rotation, 0.0f, 0.0f, 0.0f);
    BattleAnim_InitSwayOffset(animated_pokemon, sModelTransformConstants[0], NINETY_DEGREES);
    BattleScene_ShowSecondaryModelsStaggeredFrame(animated_pokemon);
    animated_pokemon->modelTransformTimer++;
}

/**
 * fly continue
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void BattleAnim_FlyContinue(ActivePokemon* owner, ActivePokemon* animated_pokemon) {
    BattleAnim_UpdateTransform(owner, animated_pokemon, 7.0f, 0.1f, NINETY_DEGREES);
    BattleScene_UpdateSecondaryModelTrailPosition(animated_pokemon, 0);
    if (owner->displayObject.position.y - D_FLT_82189354[M2C_FIELD(owner, s16*, 0x1A)][0] >= 800.0f) {
        M2C_FIELD(animated_pokemon, f32*, 0x5C8) = 0.0f;
        BattleScene_ResetParticipantModelFlags(animated_pokemon);
        BattleScene_HideParticipantSecondaryModels(animated_pokemon);
    }
}

/**
 * Fly model transform (case 3).
 * @unverified Name and comment guessed from the code.
 */
void BattleAnim_Fly(s32 arg0, s8 *arg1) {
    s32 temp_v0;

    temp_v0 = M2C_FIELD(arg1, s32 *, 0x614);
    switch (temp_v0) {                              /* irregular */
    case 0:
        func_82109FFC(arg0);
        /* fallthrough */
    case 1:
        func_8210A084(arg0, arg1);
        return;
    }
}

/**
 * waterfall init
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void BattleAnim_WaterfallStart(UNUSED ActivePokemon* owner, ActivePokemon* animated_pokemon) {
    Vec3f_SetComponentsDuplicate(&animated_pokemon->modelTransform, 0.0f, 0.0f, 0.0f);
    Vec3f_SetComponentsDuplicate(&animated_pokemon->modelTransform.rotation, 0.0f, 0.0f, 0.0f);
    BattleAnim_InitSwayOffset(animated_pokemon, sModelTransformConstants[0], NINETY_DEGREES);
    animated_pokemon->modelTransformTimer++;
}

/**
 * waterfall continue
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void BattleAnim_WaterfallContinue(ActivePokemon* owner, ActivePokemon* animated_pokemon) {
    BattleAnim_UpdateTransform(owner, animated_pokemon, 3.0f, 0.01f, NINETY_DEGREES);
    if (owner->displayObject.position.y - D_FLT_82189354[M2C_FIELD(owner, s16*, 0x1A)][0] >= 300.0f) {
        animated_pokemon->modelTransformTimer++;
        M2C_FIELD(animated_pokemon, f32*, 0x5C8) = 0.0f;
    }
}

void BattleAnim_WaterfallEnd(UNUSED ActivePokemon* owner, UNUSED ActivePokemon* animated_pokemon) {
}

/**
 * Waterfall's animation: climb a waterfall
 * https://youtu.be/Dn5oyCQ3wUs?t=1360
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void BattleAnim_Waterfall(ActivePokemon* owner, ActivePokemon* animated_pokemon) {
    switch (animated_pokemon->modelTransformTimer) {
        case 0:
            BattleAnim_WaterfallStart(owner, animated_pokemon);

        case 1:
            BattleAnim_WaterfallContinue(owner, animated_pokemon);
            break;

        case 2:
            BattleAnim_WaterfallEnd(owner, animated_pokemon);
            break;
    }
}

void func_8210A2F4(UNUSED ActivePokemon* owner, ActivePokemon* animated_pokemon) {
    Vec3f_SetComponentsDuplicate(&animated_pokemon->modelTransform, 0.0f, 0.0f, 0.0f);
    Vec3f_SetComponentsDuplicate(&animated_pokemon->modelTransform.rotation, 0.0f, 0.0f, 0.0f);
    BattleAnim_InitSwayOffset(animated_pokemon, sModelTransformConstants[0], 0x2AAA);
    animated_pokemon->modelTransformTimer++;
}

void func_8210A374(ActivePokemon* owner, ActivePokemon* animated_pokemon) {
    BattleAnim_UpdateTransform(owner, animated_pokemon, 9.0f, 0.9f, 0x2AAA);
    if (owner->displayObject.position.y < 0.0f) {
        animated_pokemon->modelTransform.rotation.y = 0;
        BattleScene_ResetParticipantModelFlags(animated_pokemon);
    }
}

void func_8210A3DC(s32 arg0, s8 *arg1) {
    s32 temp_v0;

    temp_v0 = M2C_FIELD(arg1, s32 *, 0x614);
    switch (temp_v0) {                              /* irregular */
    case 0:
        func_8210A2F4((ActivePokemon*)arg0, (ActivePokemon*)arg1);
        /* fallthrough */
    case 1:
        func_8210A374(arg0, arg1);
        return;
    }
}

s32 BattleAnim_ApproachAngleAndCheckThreshold(ActivePokemon* pokemon, s16 phase, s16 camera_offset_scale) {
    pokemon->displayObject.rotation.y -= phase;

    if (phase > 0) {
        if ((camera_offset_scale >= pokemon->displayObject.rotation.y) && ((camera_offset_scale - phase) < pokemon->displayObject.rotation.y)) {
            return 1;
        }
    } else if ((pokemon->displayObject.rotation.y >= camera_offset_scale) && (pokemon->displayObject.rotation.y < (camera_offset_scale - phase))) {
        return 1;
    }

    return 0;
}

/**
 * Submission: resets the oscillation and the phase counter.
 * @unverified Name and comment guessed from the code.
 */
void BattleAnim_SubmissionStart(s32 arg0, s8 *arg1) {
    func_821099CC(arg1);
    M2C_FIELD(arg1, s16 *, 0x602) = 0;
    M2C_FIELD(arg1, s16 *, 0x600) = 0;
    M2C_FIELD(arg1, s32 *, 0x61C) = 0;
    M2C_FIELD(arg1, s32 *, 0x614) = (s32) (M2C_FIELD(arg1, s32 *, 0x614) + 1);
}

/**
 * Submission: spins the model and counts three turns before the end step.
 * @unverified Name and comment guessed from the code.
 */
void BattleAnim_SubmissionContinue(s32 arg0, s8 *arg1) {
    M2C_FIELD(arg1, s16 *, 0x602) = func_8000F1FC(M2C_FIELD(arg1, s16 *, 0x602), 0x3330, 0x16C, 0x16C);
    if (func_8210A430(arg0, M2C_FIELD(arg1, s16 *, 0x602), (s16) (M2C_FIELD(arg1, s32 *, 0x60C) << 0xE)) != 0) {
        M2C_FIELD(arg1, s32 *, 0x61C) = (s32) (M2C_FIELD(arg1, s32 *, 0x61C) + 1);
    }
    func_82109AF4(arg1, M2C_FIELD(arg1, s16 *, 0x602));
    if (M2C_FIELD(arg1, s32 *, 0x61C) == 3) {
        M2C_FIELD(arg1, s32 *, 0x614) = (s32) (M2C_FIELD(arg1, s32 *, 0x614) + 1);
    }
}

void BattleAnim_SubmissionEnd(ActivePokemon* owner, ActivePokemon* animated_pokemon) {
    f32 angle_offset = NINETY_DEGREES - owner->displayObject.rotation.y;
    f32 angle_offset_fractional;
    s16 new_phase;
    s32 done;

    angle_offset_fractional = (131072.0 - angle_offset) / 131072.0;
    if (angle_offset_fractional >= 1.0f) {
        angle_offset_fractional -= 1.0f;
    }

    new_phase = (animated_pokemon->oscillationPhase * angle_offset_fractional) * D_DBL_82194920;
    if (new_phase < 3640) {
        new_phase = 3640;
    }
    done = BattleAnim_ApproachAngleAndCheckThreshold(owner, new_phase, animated_pokemon->facingDirection << 14);
    BattleScene_UpdateSecondaryModelTrailPosition(animated_pokemon, new_phase);

    if (done != 0) {
        owner->displayObject.rotation.y = animated_pokemon->facingDirection << 14;
        BattleScene_ResetParticipantModelFlags(animated_pokemon);
        BattleScene_HideParticipantSecondaryModels(animated_pokemon);
    }
}

/**
 * Submission model transform (case 4).
 * @unverified Name and comment guessed from the code.
 */
void BattleAnim_Submission(ActivePokemon* owner, ActivePokemon* animated_pokemon) {
    switch (animated_pokemon->modelTransformTimer) {
        case 0:
            BattleAnim_SubmissionStart(owner, animated_pokemon);

        case 1:
            BattleAnim_SubmissionContinue(owner, animated_pokemon);
            break;

        case 2:
            func_8210A584(owner, animated_pokemon);
            break;
    }
}

/**
 * Dig: resets the oscillation and the phase counter.
 * @unverified Name and comment guessed from the code.
 */
void BattleAnim_DigStart(s32 arg0, s8 *arg1) {
    func_821099CC(arg1);
    M2C_FIELD(arg1, s16 *, 0x602) = 0;
    M2C_FIELD(arg1, s16 *, 0x600) = 0;
    M2C_FIELD(arg1, s32 *, 0x61C) = 0;
    M2C_FIELD(arg1, s32 *, 0x614) = (s32) (M2C_FIELD(arg1, s32 *, 0x614) + 1);
}

/**
 * Dig: spins the model and counts three turns before it sinks.
 * @unverified Name and comment guessed from the code.
 */
void BattleAnim_DigContinue(s32 arg0, s8 *arg1) {
    M2C_FIELD(arg1, s16 *, 0x602) = func_8000F1FC(M2C_FIELD(arg1, s16 *, 0x602), 0x3FFC, 0x16C, 0x16C);
    if (func_8210A430(arg0, M2C_FIELD(arg1, s16 *, 0x602), (s16) (M2C_FIELD(arg1, s32 *, 0x60C) << 0xE)) != 0) {
        M2C_FIELD(arg1, s32 *, 0x61C) = (s32) (M2C_FIELD(arg1, s32 *, 0x61C) + 1);
    }
    func_82109AF4(arg1, M2C_FIELD(arg1, s16 *, 0x602));
    if (M2C_FIELD(arg1, s32 *, 0x61C) >= 3) {
        M2C_FIELD(arg1, s32 *, 0x614) = (s32) (M2C_FIELD(arg1, s32 *, 0x614) + 1);
    }
}

f32 BattleScene_GetParticipantHeight(s8*);
void func_8210A7D8(s32 arg0, s8* arg1) {
    func_8210A430(arg0, M2C_FIELD(arg1, s16*, 0x602), (s16)(M2C_FIELD(arg1, s32*, 0x60C) << 0xE));
    func_82109AF4(arg1, M2C_FIELD(arg1, s16*, 0x602));
    BattleAnim_ApproachF((f32*)(arg0 + 0x28), -(BattleScene_GetParticipantHeight(arg1) * 2.6), 0.04f);
    if (*(f32*)(arg0 + 0x28) <= -(BattleScene_GetParticipantHeight(arg1) * 2.5)) {
        func_8000D700(arg0 + 0x1E, 0, (s16)(M2C_FIELD(arg1, s32*, 0x60C) << 0xE), 0);
        func_82109C88(arg1);
        func_8210942C((s32)arg1);
    }
}

/**
 * Dig model transform (case 5).
 * @unverified Name and comment guessed from the code.
 */
void BattleAnim_Dig(ActivePokemon* owner, ActivePokemon* animated_pokemon) {
    switch (animated_pokemon->modelTransformTimer) {
        case 0:
            BattleAnim_DigStart(owner, animated_pokemon);

        case 1:
            BattleAnim_DigContinue(owner, animated_pokemon);
            break;

        case 2:
            func_8210A7D8(owner, animated_pokemon);
            break;
    }
}

/**
 * Agility: resets the oscillation, the facing and the transform.
 * @unverified Name and comment guessed from the code.
 */
void BattleAnim_AgilityStart(s32 arg0, s8 *arg1) {
    M2C_FIELD(arg1, s16 *, 0x602) = 0;
    M2C_FIELD(arg1, s16 *, 0x600) = 0;
    M2C_FIELD(arg1, s32 *, 0x61C) = 0;
    M2C_FIELD(arg1, f32 *, 0x5FC) = 0.0f;
    func_82107790(arg1);
    func_8000D700(arg0 + 0x1E, 0, (s16) (M2C_FIELD(arg1, s32 *, 0x60C) << 0xE), 0);
    func_821099CC(arg1);
    M2C_FIELD(arg1, s32 *, 0x614) = (s32) (M2C_FIELD(arg1, s32 *, 0x614) + 1);
}

void BattleAnim_AgilityContinue(ActivePokemon* owner, ActivePokemon* animated_pokemon) {
    f32 magnitude;
    Vec3f zero_vector = { 0.0f, 0.0f, 0.0f }; // D_84384654

    BattleAnim_ApproachF(&animated_pokemon->oscillationAmplitude, 50.0f, 0.1f);
    animated_pokemon->oscillationPhase += 0xE38;
    magnitude = SINS(animated_pokemon->oscillationPhase) * animated_pokemon->oscillationAmplitude;
    BattleAnim_Vec3fSetPolarXZ(&zero_vector, magnitude, owner->displayObject.rotation.y);
    BattleScene_PositionParticipantModel(animated_pokemon);
    Vec3f_AddInPlace(&owner->displayObject.position, &zero_vector);
    BattleScene_UpdateSecondaryModelTrailPosition(animated_pokemon, 0);

    if (animated_pokemon->oscillationAmplitude > 49.0f) {
        animated_pokemon->modelTransformTimer++;
    }
}

void BattleAnim_AgilityEnd(ActivePokemon* owner, ActivePokemon* animated_pokemon) {
    f32 magnitude;
    Vec3f zero_vector = { 0.0f, 0.0f, 0.0f };

    BattleAnim_ApproachF(&animated_pokemon->oscillationAmplitude, 0.0f, 0.1f);
    animated_pokemon->oscillationPhase += 3640;

    magnitude = SINS(animated_pokemon->oscillationPhase) * animated_pokemon->oscillationAmplitude;
    BattleAnim_Vec3fSetPolarXZ(&zero_vector, magnitude, owner->displayObject.rotation.y);

    BattleScene_PositionParticipantModel(animated_pokemon);
    Vec3f_AddInPlace(&owner->displayObject.position, &zero_vector);
    BattleScene_UpdateSecondaryModelTrailPosition(animated_pokemon, 0);

    if (animated_pokemon->oscillationAmplitude <= 0.5f) {
        BattleScene_PositionParticipantModel(animated_pokemon);
        Vec3s_SetComponents(&owner->displayObject.rotation, 0, animated_pokemon->facingDirection << 0xE, 0);
        BattleScene_ResetParticipantModelFlags(animated_pokemon);
        BattleScene_HideParticipantSecondaryModels(animated_pokemon);
    }
}

/**
 * Agility model transform (case 6).
 * @unverified Name and comment guessed from the code.
 */
void BattleAnim_Agility(ActivePokemon* owner, ActivePokemon* animated_pokemon) {
    switch (animated_pokemon->modelTransformTimer) {
        case 0:
            BattleAnim_AgilityStart(owner, animated_pokemon);

        case 1:
            func_8210A9B4(owner, animated_pokemon);
            break;

        case 2:
            func_8210AAA4(owner, animated_pokemon);
            break;
    }
}

/**
 * Double Team: shows the secondary models at the main transform and resets the orbit timer.
 * @unverified Name and comment guessed from the code.
 */
void BattleAnim_DoubleTeamStart(s32 arg0, s8 *arg1) {
    BattleScene_ShowSecondaryModelsAtMainTransform(arg1);
    M2C_FIELD(arg1, s32 *, 0x608) = 0;
    func_82107790(arg1);
    func_8000D700(arg0 + 0x1E, 0, (s16) (M2C_FIELD(arg1, s32 *, 0x60C) << 0xE), 0);
    M2C_FIELD(arg1, s32 *, 0x614) = (s32) (M2C_FIELD(arg1, s32 *, 0x614) + 1);
}

void BattleAnim_DoubleTeamContinue(UNUSED ActivePokemon* owner, ActivePokemon* animated_pokemon) {
    BattleScene_UpdateSecondaryModelOrbit(animated_pokemon);
    animated_pokemon->doubleTeamTimer++;
    if (animated_pokemon->doubleTeamTimer == 60) {
        BattleScene_ResetParticipantModelFlags(animated_pokemon);
        BattleScene_HideParticipantSecondaryModels(animated_pokemon);
    }
}

/**
 * Double Team model transform: shows the secondary copies, then orbits them for
 * 60 frames (transform case 7, the same slot as Stadium 1).
 * @unverified Was named BattleAnim_PokeBallThrow; renamed because it runs
 * BattleAnim_DoubleTeamContinue.
 */
void BattleAnim_DoubleTeam(ActivePokemon* owner, ActivePokemon* animated_pokemon) {
    switch (animated_pokemon->modelTransformTimer) {
        case 0:
            BattleAnim_DoubleTeamStart(owner, animated_pokemon);

        case 1:
            BattleAnim_DoubleTeamContinue(owner, animated_pokemon);
            break;
    }
}

void BattleAnim_ResetOwnerFacingAndExitStatusIdle(ActivePokemon* arg0) {
    UNUSED s32 pad; // FAKE: stack padding
    CameraNode* sp18 = sBattleScene.scene->camera;

    BattleScene_PositionParticipantModel(arg0);
    Vec3s_SetComponents(&arg0->displayObject.rotation, 0, arg0->facingDirection << 0xE, 0);
    Vec3f_SetComponentsDuplicate(&sp18->view.upDirection, 0.0f, 1.0f, 0.0f);
    BattleScene_ResetParticipantModelFlags(arg0);
}

/**
 * Seismic Toss: resets the oscillation and facing.
 * @unverified Name and comment guessed from the code.
 */
void BattleAnim_SeismicTossStart(s32 arg0, s8 *arg1) {
    M2C_FIELD(arg1, s16 *, 0x602) = 0;
    M2C_FIELD(arg1, s16 *, 0x604) = 0;
    M2C_FIELD(arg1, s16 *, 0x600) = 0;
    M2C_FIELD(arg1, s32 *, 0x61C) = 0;
    M2C_FIELD(arg1, f32 *, 0x5FC) = 0.0f;
    func_82107790(arg1);
    func_8000D700(arg0 + 0x1E, 0, (s16) (M2C_FIELD(arg1, s32 *, 0x60C) << 0xE), 0);
    M2C_FIELD(arg1, s32 *, 0x614) = (s32) (M2C_FIELD(arg1, s32 *, 0x614) + 1);
}

void BattleAnim_SeismicTossContinue(UNUSED ActivePokemon* owner, ActivePokemon* animated_pokemon) {
    CameraNode* camera = sBattleScene.scene->camera;
    f32 normal_x;
    f32 normal_z;
    f32 flip_angle;
    f32 x;
    f32 y;
    f32 z;
    f32 norm;
    f32 normal_y;

    BattleAnim_StepToS16(&animated_pokemon->oscillationVelocityEasePhase, 1456, 60);
    BattleAnim_StepToS16(&animated_pokemon->oscillationAngularVelocity, -32768, animated_pokemon->oscillationVelocityEasePhase);

    x = camera->view.targetPosition.x - camera->view.eyePosition.x;
    y = camera->view.targetPosition.y - camera->view.eyePosition.y;
    z = camera->view.targetPosition.z - camera->view.eyePosition.z;

    norm = sqrtf(SQ(x) + SQ(y) + SQ(z));

    normal_x = x / norm;
    normal_y = y / norm;
    normal_z = z / norm;

    flip_angle = 1.0 - COSS(animated_pokemon->oscillationAngularVelocity);

    camera->view.upDirection.x = (flip_angle * normal_x * normal_y) - (SINS(animated_pokemon->oscillationAngularVelocity) * normal_z);
    camera->view.upDirection.y = COSS(animated_pokemon->oscillationAngularVelocity) + ((flip_angle * normal_y) * normal_y);
    camera->view.upDirection.z = (SINS(animated_pokemon->oscillationAngularVelocity) * normal_x) + ((flip_angle * normal_y) * normal_z);

    if (animated_pokemon->displayObject.position.y < 0.0f) {
        animated_pokemon->displayObject.position.y = 0.0f;
    }
}

/**
 * Seismic Toss model transform (case 8).
 * @unverified Name and comment guessed from the code.
 */
void BattleAnim_SeismicToss(ActivePokemon* owner, ActivePokemon* animated_pokemon) {
    switch (animated_pokemon->modelTransformTimer) {
        case 0:
            BattleAnim_SeismicTossStart(owner, animated_pokemon);

        case 1:
            func_8210AE34(owner, animated_pokemon);
            break;
    }
}

/**
 * Minimize: skips when the model is already scaled; otherwise starts shrinking.
 * @unverified Name and comment guessed from the code.
 */
void BattleAnim_MinimizeStart(s8 *arg0, s8 *arg1) {
    if (M2C_FIELD(arg0, f32 *, 0x34) != 1.0f) {
        func_82109C88(arg1);
        return;
    }
    func_82109764(arg1);
    M2C_FIELD(arg1, s32 *, 0x614) = (s32) (M2C_FIELD(arg1, s32 *, 0x614) + 1);
}

/**
 * Minimize: eases the model scale toward 0.65.
 * @unverified Name and comment guessed from the code.
 */
void BattleAnim_MinimizeContinue(s32 arg0, s32 arg1) {
    func_8210C1A8(arg0 + 0x30, 0x3F266666, 0x3D23D70A);
    func_8210C1A8(arg0 + 0x34, 0x3F266666, 0x3D23D70A);
    func_8210C1A8(arg0 + 0x38, 0x3F266666, 0x3D23D70A);
    if (func_82109824(arg1) != 0) {
        func_82109C88(arg1);
        func_8210942C(arg1);
    }
}

/**
 * Minimize model transform (case 9).
 * @unverified Name and comment guessed from the code.
 */
void BattleAnim_Minimize(ActivePokemon* owner, ActivePokemon* animated_pokemon) {
    switch (animated_pokemon->modelTransformTimer) {
        case 0:
            BattleAnim_MinimizeStart(owner, animated_pokemon);

        case 1:
            BattleAnim_MinimizeContinue(owner, animated_pokemon);
            break;
    }
}

/**
 * Withdraw: advances straight to the continue step.
 * @unverified Name and comment guessed from the code.
 */
void BattleAnim_WithdrawStart(s32 arg0, s8 *arg1) {
    M2C_FIELD(arg1, s32 *, 0x614) = (s32) (M2C_FIELD(arg1, s32 *, 0x614) + 1);
}

void BattleAnim_WithdrawContinue(ActivePokemon* owner, UNUSED ActivePokemon* animated_pokemon) {
    owner->displayObject.scale.x = Math_StepToF(owner->displayObject.scale.x, 0.0f, 0.05f, 0.05f);
    owner->displayObject.scale.y = Math_StepToF(owner->displayObject.scale.y, 0.0f, 0.05f, 0.05f);
    owner->displayObject.scale.z = Math_StepToF(owner->displayObject.scale.z, 0.0f, 0.05f, 0.05f);

    if (owner->displayObject.scale.y <= 0.1) {
        Vec3f_SetComponentsDuplicate(&owner->displayObject.scale, 0.001f, 0.001f, 0.001f);
    }
}

/**
 * Withdraw model transform (case 12).
 * @unverified Name and comment guessed from the code.
 */
void BattleAnim_Withdraw(ActivePokemon* owner, ActivePokemon* animated_pokemon) {
    switch (animated_pokemon->modelTransformTimer) {
        case 0:
            BattleAnim_WithdrawStart(owner, animated_pokemon);

        case 1:
            func_8210B164(owner, animated_pokemon);
            break;
    }
}

void BattleAnim_MeditateStart(UNUSED ActivePokemon* owner, ActivePokemon* animated_pokemon) {
    animated_pokemon->oscillationVelocityEasePhase = 364;
    animated_pokemon->oscillationPhase = 0;
    animated_pokemon->oscillationAngularVelocity = 0;
    animated_pokemon->oscillationAmplitude = 0.4f;
    animated_pokemon->modelTransform.rotation.x = owner->displayObject.scale.x;
    animated_pokemon->modelTransform.rotation.y = owner->displayObject.scale.y;
    animated_pokemon->modelTransform.rotation.z = owner->displayObject.scale.z;
    animated_pokemon->modelTransformTimer++;
}

void BattleAnim_MeditateContinue(ActivePokemon* owner, ActivePokemon* animated_pokemon) {
    f32 scale_resize;

    // clang-format off
    if ((animated_pokemon->oscillationVelocityEasePhase >= 0) && (animated_pokemon->oscillationVelocityEasePhase <= 0x8000)) { animated_pokemon->oscillationVelocityEasePhase += 45; }
    // clang-format on

    animated_pokemon->oscillationAngularVelocity = SINS(animated_pokemon->oscillationVelocityEasePhase) * 182.0f * 15.0f;

    if ((animated_pokemon->oscillationPhase >= 0) && (animated_pokemon->oscillationPhase <= NINETY_DEGREES)) {
        animated_pokemon->oscillationPhase += animated_pokemon->oscillationAngularVelocity;
    }

    scale_resize = 1.0f;

    owner->displayObject.scale.x = scale_resize - (SINS(animated_pokemon->oscillationPhase) * animated_pokemon->oscillationAmplitude);
    owner->displayObject.scale.y = (SINS(animated_pokemon->oscillationPhase) * animated_pokemon->oscillationAmplitude) + scale_resize;
    owner->displayObject.scale.z = scale_resize - (SINS(animated_pokemon->oscillationPhase) * animated_pokemon->oscillationAmplitude);

    if ((animated_pokemon->oscillationPhase >= NINETY_DEGREES) && (animated_pokemon->oscillationPhase >= NINETY_DEGREES)) {
        animated_pokemon->oscillationAngularVelocity = 5460;
        animated_pokemon->modelTransformTimer++;
    }
}

void BattleAnim_MeditateEnd(ActivePokemon* owner, ActivePokemon* animated_pokemon) {
    f32 scale_resize;
    f32 sin_value;

    animated_pokemon->oscillationPhase += animated_pokemon->oscillationAngularVelocity;
    sin_value = SINS(animated_pokemon->oscillationPhase) * animated_pokemon->oscillationAmplitude;
    if (sin_value <= 0.01f) {
        animated_pokemon->oscillationAngularVelocity += 1092;
        animated_pokemon->oscillationAmplitude *= 0.8f;
        if (1) {} //karodo
        sin_value = SINS(animated_pokemon->oscillationPhase) * animated_pokemon->oscillationAmplitude;
    }

    scale_resize = 1.0f;

    owner->displayObject.scale.x = scale_resize - sin_value;
    owner->displayObject.scale.y = (SINS(animated_pokemon->oscillationPhase) * animated_pokemon->oscillationAmplitude) + scale_resize;
    owner->displayObject.scale.z = scale_resize - (SINS(animated_pokemon->oscillationPhase) * animated_pokemon->oscillationAmplitude);

    if (animated_pokemon->oscillationAmplitude <= 0.01f) {
        owner->displayObject.scale.x = animated_pokemon->modelTransform.rotation.x;
        owner->displayObject.scale.y = animated_pokemon->modelTransform.rotation.y;
        owner->displayObject.scale.z = animated_pokemon->modelTransform.rotation.z;
        BattleScene_ResetParticipantModelFlags(animated_pokemon);
    }
}

/**
 * Meditate model transform (case 13).
 * @unverified Name and comment guessed from the code.
 */
void BattleAnim_Meditate(ActivePokemon* owner, ActivePokemon* animated_pokemon) {
    switch (animated_pokemon->modelTransformTimer) {
        case 0:
            func_8210B280(owner, animated_pokemon);

        case 1:
            func_8210B2C4(owner, animated_pokemon);
            break;

        case 2:
            func_8210B3F0(owner, animated_pokemon);
            break;
    }
}

void BattleAnim_SquishHitReactionStart(ActivePokemon* owner, ActivePokemon* animated_pokemon) {
    animated_pokemon->oscillationAngularVelocity = 1820;
    animated_pokemon->oscillationAmplitude = 0.4f;
    animated_pokemon->modelTransform.rotation.x = owner->displayObject.scale.x;
    animated_pokemon->modelTransform.rotation.y = owner->displayObject.scale.y;
    animated_pokemon->modelTransform.rotation.z = owner->displayObject.scale.z;
    animated_pokemon->modelTransformTimer++;
}


void BattleAnim_SquishHitReactionContinue(ActivePokemon* owner, ActivePokemon* animated_pokemon) {
    BattleMonRuntime* runtime = &animated_pokemon->state.runtime;
    s16 angular_velocity;

    animated_pokemon->oscillationAngularVelocity += 0xCCC;
    angular_velocity = animated_pokemon->oscillationAngularVelocity;

    animated_pokemon->oscillationAmplitude = Math_StepToF(animated_pokemon->oscillationAmplitude, 0.0f, 0.02f, 0.02f);

    if (angular_velocity > 0) {
        angular_velocity *= -1;
    }

    if (runtime->scaleResize == 0) {
        owner->displayObject.scale.x = 1.0f - (SINS(angular_velocity) * animated_pokemon->oscillationAmplitude);
        owner->displayObject.scale.y = (SINS(angular_velocity) * animated_pokemon->oscillationAmplitude) + 1.0f;
        owner->displayObject.scale.z = 1.0f - (SINS(angular_velocity) * animated_pokemon->oscillationAmplitude);
    } else {
        owner->displayObject.scale.x = 0.65 - (SINS(angular_velocity) * animated_pokemon->oscillationAmplitude);
        owner->displayObject.scale.y = (SINS(angular_velocity) * animated_pokemon->oscillationAmplitude) + 0.65;
        owner->displayObject.scale.z = 0.65 - (SINS(angular_velocity) * animated_pokemon->oscillationAmplitude);
    }

    if (animated_pokemon->oscillationAmplitude <= 0.01f) {
        if (runtime->scaleResize == 0) {
            Vec3f_SetComponentsDuplicate(&owner->displayObject.scale, 1.0f, 1.0f, 1.0f);
        } else {
            Vec3f_SetComponentsDuplicate(&owner->displayObject.scale, 0.65f, 0.65f, 0.65f);
        }
        BattleScene_ResetParticipantModelFlags(animated_pokemon);
    }
}


/**
 * Squish hit reaction model transform (case 15).
 * @unverified Name and comment guessed from the code.
 */
void BattleAnim_SquishHitReaction(s32 arg0, s8 *arg1) {
    s32 temp_v0;

    temp_v0 = M2C_FIELD(arg1, s32 *, 0x614);
    switch (temp_v0) {                              /* irregular */
    case 0:
        func_8210B58C(arg0);
        /* fallthrough */
    case 1:
        func_8210B5C8(arg0, arg1);
        return;
    }
}


/**
 * Lasso hit reaction: sets up a small fast oscillation from the owner's scale.
 * @unverified Name and comment guessed from the code.
 */
void BattleAnim_LassoMoveHitReactionStart(ActivePokemon* owner, ActivePokemon* animated_pokemon) {
    animated_pokemon->oscillationAngularVelocity = 0x4000;
    animated_pokemon->oscillationAmplitude = 0.1f;
    animated_pokemon->modelTransform.rotation.x = owner->displayObject.scale.x;
    animated_pokemon->modelTransform.rotation.y = owner->displayObject.scale.y;
    animated_pokemon->modelTransform.rotation.z = owner->displayObject.scale.z;
    animated_pokemon->doubleTeamTimer = 0;
    animated_pokemon->modelTransformTimer++;
}


void BattleAnim_LassoMoveHitReactionContinue(ActivePokemon* owner, ActivePokemon* animated_pokemon) {
    BattleMonRuntime* runtime = &animated_pokemon->state.runtime;
    f32 scale_delta;
    UNUSED s32 pad; // FAKE: stack padding

    if (runtime->scaleResize == 0) {
        scale_delta = (1.0f - Strip400_GetTailFadeRatio()) * 0.6f;
        BattleAnim_ApproachF(&owner->displayObject.scale.x, 1.0f - scale_delta, 0.5f);
        BattleAnim_ApproachF(&owner->displayObject.scale.y, 1.0f + scale_delta, 0.5f);
        BattleAnim_ApproachF(&owner->displayObject.scale.z, 1.0f - scale_delta, 0.5f);
    } else {
        scale_delta = (1.0f - Strip400_GetTailFadeRatio()) * 0.3f;
        BattleAnim_ApproachF(&owner->displayObject.scale.x, 0.65 - scale_delta, 0.5f);
        BattleAnim_ApproachF(&owner->displayObject.scale.y, scale_delta + 0.65, 0.5f);
        BattleAnim_ApproachF(&owner->displayObject.scale.z, 0.65 - scale_delta, 0.5f);
    }

    if (animated_pokemon->doubleTeamTimer++ == 0x96) {
        if (runtime->scaleResize == 0) {
            Vec3f_SetComponentsDuplicate(&owner->displayObject.scale, 1.0f, 1.0f, 1.0f);
        } else {
            Vec3f_SetComponentsDuplicate(&owner->displayObject.scale, 0.65f, 0.65f, 0.65f);
        }
        BattleScene_ResetParticipantModelFlags(animated_pokemon);
    }
}


/**
 * Lasso move hit reaction model transform (case 16).
 * @unverified Name and comment guessed from the code.
 */
void BattleAnim_LassoMoveHitReaction(s32 arg0, s8 *arg1) {
    s32 temp_v0;

    temp_v0 = M2C_FIELD(arg1, s32 *, 0x614);
    switch (temp_v0) {                              /* irregular */
    case 0:
        BattleAnim_LassoMoveHitReactionStart((ActivePokemon*)arg0, (ActivePokemon*)arg1);
        /* fallthrough */
    case 1:
        func_8210B824(arg0, arg1);
        return;
    }
}

/**
 * Surf: resets the animation counter.
 * @unverified Name and comment guessed from the code.
 */
void BattleAnim_SurfStart(s32 arg0, s8 *arg1) {
    M2C_FIELD(arg1, s32 *, 0x61C) = 0;
    M2C_FIELD(arg1, s32 *, 0x614) = (s32) (M2C_FIELD(arg1, s32 *, 0x614) + 1);
}

extern f32 D_FLT_8218935C[][4];
/**
 * Surf: keeps the rider on the wave height from SurfTerrainGrid_SampleHeightAndSlope.
 * @unverified Name and comment guessed from the code.
 */
void BattleAnim_SurfContinue(ActivePokemon* owner, ActivePokemon* animated_pokemon) {
    f32 rotation_x;
    f32 water_height;
    f32* model_row;

    animated_pokemon->animationState++;
    water_height = SurfTerrainGrid_SampleHeightAndSlope(owner->displayObject.position.x, owner->displayObject.position.z, &rotation_x);
    model_row = D_FLT_8218935C[owner->displayObject.objectType];
    owner->displayObject.position.y = model_row[-2] + (water_height + 5.0f);
    owner->displayObject.rotation.x = (s16)rotation_x * 182;
    if (animated_pokemon->animationState == 200) {
        owner->displayObject.position.y = model_row[-2];
        owner->displayObject.rotation.x = 0;
        func_82109C88((s8*)animated_pokemon);
    }
}

/**
 * Surf model transform (case 10).
 * @unverified Name and comment guessed from the code.
 */
void BattleAnim_Surf(ActivePokemon* owner, ActivePokemon* animated_pokemon) {
    switch (animated_pokemon->modelTransformTimer) {
        case 0:
            BattleAnim_SurfStart(owner, animated_pokemon);

        case 1:
            BattleAnim_SurfContinue(owner, animated_pokemon);
            break;
    }
}

void BattleAnim_DrawParticleNoop(UNUSED Particle* arg0, UNUSED CameraNode* arg1) {
}


void BattleAnim_PlayTransformInducingAnimation(s32 side_index) {
    ActivePokemon* owner = sActivePokemon[side_index];
    ActivePokemon* animated_pokemon = sActivePokemon[side_index];

    // Zero renumbers the transforms, so the cases call the Zero functions by address.
    switch (sActivePokemon[side_index]->modelTransformId) {
        case 0:
            BattleAnim_DrawParticleNoop((Particle*)owner, (CameraNode*)animated_pokemon);
            break;
        case 1:
            BattleAnim_PokeBallThrow((s32)owner, (s8*)animated_pokemon);
            break;
        case 2:
            BattleAnim_PokeBallLand((s32)owner, (s8*)animated_pokemon);
            break;
        case 3:
            BattleAnim_Fly((s32)owner, (s8*)animated_pokemon);
            break;
        case 4:
            BattleAnim_Submission(owner, animated_pokemon);
            break;
        case 5:
            BattleAnim_Dig(owner, animated_pokemon);
            break;
        case 6:
            BattleAnim_Agility(owner, animated_pokemon);
            break;
        case 7:
            BattleAnim_DoubleTeam(owner, animated_pokemon);
            break;
        case 8:
            BattleAnim_SeismicToss(owner, animated_pokemon);
            break;
        case 9:
            BattleAnim_Minimize(owner, animated_pokemon);
            break;
        case 10:
            BattleAnim_Surf(owner, animated_pokemon);
            break;
        case 11:
            func_8210A3DC((s32)owner, (s8*)animated_pokemon);
            break;
        case 12:
            BattleAnim_Withdraw(owner, animated_pokemon);
            break;
        case 13:
            BattleAnim_Meditate(owner, animated_pokemon);
            break;
        case 14:
            BattleAnim_Waterfall(owner, animated_pokemon);
            break;
        case 15:
            BattleAnim_SquishHitReaction((s32)owner, (s8*)animated_pokemon);
            break;
        case 16:
            BattleAnim_LassoMoveHitReaction((s32)owner, (s8*)animated_pokemon);
            break;
        default:
            BattleScene_ResetParticipantModelFlags(animated_pokemon);
            break;
    }
}
