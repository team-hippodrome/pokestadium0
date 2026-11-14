/* Fixed-layout split; original translation-unit boundaries remain unconfirmed. */
#include "battle.h"
#include "geo_node.h"
#include "matrix.h"
#include "model_renderer.h"

/**
 * Starts a sway or arc: sets the height y, splits it into Z and Y components by angle
 * theta, and sets the default speed.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (2 of the moves).
 * @unverified Name from Stadium 1.
 */
void BattleAnim_InitSwayOffset(ActivePokemon* pokemon, f32 y, s16 theta) {
    pokemon->y = y;
    pokemon->modelTransform.rotation.z = COSS(theta) * y;
    pokemon->modelTransform.rotation.y = SINS(theta) * y;
    pokemon->rotationZ = D_FLT_82194900;
}

/**
 * Moves the owner model one step along its sway arc toward height, by delta_y and
 * delta_theta, offsetting its position sideways from its facing.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (2 of the moves).
 * @unverified Name from Stadium 1.
 */
void BattleAnim_UpdateTransform(ActivePokemon* owner, ActivePokemon* animated_pokemon, f32 height, f32 delta_y, s32 delta_theta) {
    f32 temp_attacker_rotation_z;
    f32 temp_attacker_y1;
    f32 base_y_rotation;
    UNUSED s32 pad; // FAKE: stack padding
    Vec3f rotation;
    UNUSED s32 pad2; // FAKE: stack padding
    f32 z_rotation_factor;
    f32 y_rotation_factor;
    f32 temp_attacker_y2;

    temp_attacker_rotation_z = animated_pokemon->rotationZ;
    temp_attacker_y1 = animated_pokemon->y;
    base_y_rotation = 18.0f;
    animated_pokemon->y = Math_StepToF(temp_attacker_y1, height, delta_y, delta_y);

    temp_attacker_y2 = animated_pokemon->y;
    if (height <= temp_attacker_y2) {
        if (&animated_pokemon->modelTransform.rotation) {}  // FAKE
        temp_attacker_y2 = 0.0f;
    }

    rotation.z = COSS(delta_theta) * temp_attacker_y2;
    rotation.y = SINS(delta_theta) * temp_attacker_y2;

    z_rotation_factor = -temp_attacker_rotation_z * ((temp_attacker_y1 * animated_pokemon->modelTransform.rotation.z) + rotation.z);
    y_rotation_factor = -base_y_rotation - (temp_attacker_rotation_z * ((temp_attacker_y1 * animated_pokemon->modelTransform.rotation.y) + rotation.y));

    animated_pokemon->modelTransform.rotation.z = (animated_pokemon->modelTransform.rotation.z + rotation.z + (z_rotation_factor * D_FLT_82194904));
    animated_pokemon->modelTransform.rotation.y = (animated_pokemon->modelTransform.rotation.y + rotation.y + (y_rotation_factor * D_FLT_82194908));

    rotation.y = animated_pokemon->modelTransform.rotation.y;
    animated_pokemon->modelTransform.rotation.x = 0.0f;

    BattleAnim_Vec3fSetPolarXZ(&rotation, animated_pokemon->modelTransform.rotation.z, owner->displayObject.rotation.y + NINETY_DEGREES);
    Vec3f_AddInPlace(&owner->displayObject.position, &rotation);
}

/**
 * Moves the Poké Ball one step along its arc toward target, offsetting it in direction
 * theta1.
 * Not reached in play (2026-11-13): did not run in the 165-move battle sweep (each move used once,
 * from the command menu to the end of its turn) or in a tour of the menus and a COM battle.
 * @unverified Name from Stadium 1.
 */
void BattleAnim_UpdateSwayPhysicsToTarget(UNUSED ActivePokemon* owner, ActivePokemon* animated_object, f32 target, f32 delta, s32 theta0, s32 theta1) {
    f32 object_z;
    f32 object_y;
    f32 adjustment;
    UNUSED s32 pad; // FAKE: stack padding
    Vec3f rotation;
    UNUSED s32 pad2; // FAKE: stack padding
    f32 adjusted_z_rotation;
    f32 adjusted_y_rotation;
    f32 temp_object_y;

    object_z = animated_object->rotationZ;
    object_y = animated_object->y;
    adjustment = 20.0f;
    animated_object->y = Math_StepToF(object_y, target, delta, delta);

    temp_object_y = animated_object->y;
    if (target <= temp_object_y) {
        if (&animated_object->modelTransform.rotation) {}  // FAKE
        temp_object_y = 0.0f;
    }

    rotation.z = COSS(theta0) * temp_object_y;
    rotation.y = SINS(theta0) * temp_object_y;

    adjusted_z_rotation = -object_z * ((object_y * animated_object->modelTransform.rotation.z) + rotation.z);
    adjusted_y_rotation = -adjustment - (object_z * ((object_y * animated_object->modelTransform.rotation.y) + rotation.y));

    animated_object->modelTransform.rotation.z = (animated_object->modelTransform.rotation.z + rotation.z + (adjusted_z_rotation * D_FLT_8219490C));
    animated_object->modelTransform.rotation.y = (animated_object->modelTransform.rotation.y + rotation.y + (adjusted_y_rotation * D_FLT_82194910));
    rotation.y = animated_object->modelTransform.rotation.y;
    animated_object->modelTransform.rotation.x = 0.0f;

    BattleAnim_Vec3fSetPolarXZ(&rotation, animated_object->modelTransform.rotation.z, theta1);
    Vec3f_AddInPlace(&animated_object->pokeBall.position, &rotation);
}

/**
 * Hides the Pokémon's three afterimages and resets their scale.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (11 of the moves).
 * @unverified Name from Stadium 1.
 */
void BattleScene_HideParticipantSecondaryModels(ActivePokemon* active_pokemon) {
    s32 i;

    for (i = 0; i < 3; i++) {
        Vec3f_SetComponentsDuplicate(&active_pokemon->afterimages[i].displayObject.scale, 1.0f, 1.0f, 1.0f);
        active_pokemon->afterimages[i].displayObject.node.flags &= ~1;
        active_pokemon->afterimages[i].minimized = 0;
    }
}


/**
 * Seen in play (2026-11-13) (unattended Free Battle in which every Pokémon knows only Metronome, 70
 * turns): ran.
 * @unverified Name was previously used only by callers of this address; the definition was still func_.
 */
void BattleScene_ShowSecondaryModelsAtMainTransform(ActivePokemon* pokemon) {
    s32 i;
    s16 sp64[] = { 0x0, 0xE38, 0xF1C8 }; // D_821891A8

    for (i = 0; i < 3; i++) {
        pokemon->afterimages[i].orbitSpeed = 0;
        pokemon->afterimages[i].orbitAngle = sp64[i];
        pokemon->afterimages[i].displayObject.lodFraction = 0;
        pokemon->afterimages[i].displayObject.node.flags |= 1;
        BattleAnim_Vec3fCopy(&pokemon->afterimages[i].displayObject.position, &pokemon->displayObject.position);
        BattleAnim_Vec3sCopy(&pokemon->afterimages[i].displayObject.rotation, &pokemon->displayObject.rotation);
        BattleAnim_Vec3fCopy(&pokemon->afterimages[i].displayObject.scale, &pokemon->displayObject.scale);
    }
}


/**
 * Double Team step: fades the afterimages to alpha 60, speeds up their orbit and places
 * each one around the Pokémon, copying its animation.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (1 of the moves).
 * @unverified Name from Stadium 1.
 */
void BattleScene_UpdateSecondaryModelOrbit(ActivePokemon* pokemon) {
    s32 i;
    f32 tmp;
    Vec3f sp5C = { 0.0f, 0.0f, 0.0f };         // D_84384610
    f32 sp4C[] = { 0.3f, -0.4f, -0.2f, 0.4f }; // D_8438461C

    for (i = 0; i < 3; i++) {
        pokemon->afterimages[i].displayObject.lodFraction = Math_StepToS32(pokemon->afterimages[i].displayObject.lodFraction, 0x3C, 5, 5);
        pokemon->afterimages[i].orbitSpeed = Math_StepToS32(pokemon->afterimages[i].orbitSpeed, 0x38E, 0x64, 0x64);
        pokemon->afterimages[i].orbitSpeed = Math_StepToS32(pokemon->afterimages[i].orbitSpeed, 0x38E, 0x64, 0x64);
        pokemon->afterimages[i].orbitAngle += pokemon->afterimages[i].orbitSpeed;

        tmp = SINS(pokemon->afterimages[i].orbitAngle) * (BattleScene_GetParticipantModelRadiusScaled(pokemon) * sp4C[i]);
        BattleAnim_Vec3fSetPolarXZ(&sp5C, tmp, pokemon->displayObject.rotation.y);

        pokemon->afterimages[i].displayObject.position.x = pokemon->displayObject.position.x + sp5C.x;
        pokemon->afterimages[i].displayObject.position.y = pokemon->displayObject.position.y + sp5C.y;
        pokemon->afterimages[i].displayObject.position.z = pokemon->displayObject.position.z + sp5C.z;

        ModelAnim_SetFrame(&pokemon->afterimages[i].displayObject, pokemon->displayObject.transformAnim.frameFixed >> 0x10);
        ModelAnim_SetAnimation(&pokemon->afterimages[i].displayObject, pokemon->displayObject.transformAnim.animationId);
    }
}


/**
 * Shows the first two afterimages at the Pokémon's position at alpha 60.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (1 of the moves).
 * @unverified Name from Stadium 1.
 */
void BattleScene_ShowSecondaryModelsAtMainPose(ActivePokemon* active_pokemon) {
    s32 i;

    for (i = 0; i < 2; i++) {
        active_pokemon->afterimages[i].minimized = 0;
        active_pokemon->afterimages[i].displayObject.lodFraction = 0x3C;
        active_pokemon->afterimages[i].displayObject.node.flags |= 1;
        Vec3f_SetComponentsDuplicate(&active_pokemon->afterimages[i].displayObject.scale, 1.0f, 1.0f, 1.0f);
        BattleAnim_Vec3fCopy(&active_pokemon->afterimages[i].displayObject.position, &active_pokemon->displayObject.position);
    }
}


/**
 * Steps the two afterimages: each follows the Pokemon's position and shrinks toward 0.65 at
 * its own speed. Returns 1 once both are done.
 */
s32 func_82109824(ActivePokemon* arg0) {
    s32 i;
    s32 count;
    Vec3f speeds = D_821891CC;

    count = 0;
    for (i = 0; i < 2; i++) {
        BattleAnim_Vec3fCopy(&arg0->afterimages[i].displayObject.position, &arg0->displayObject.position);
        BattleAnim_ApproachF(&arg0->afterimages[i].displayObject.scale.x, 0.65f, (&speeds.x)[i]);
        BattleAnim_ApproachF(&arg0->afterimages[i].displayObject.scale.y, 0.65f, (&speeds.x)[i]);
        BattleAnim_ApproachF(&arg0->afterimages[i].displayObject.scale.z, 0.65f, (&speeds.x)[i]);
        ModelAnim_SetFrame(&arg0->afterimages[i].displayObject, arg0->displayObject.transformAnim.frameFixed >> 16);
        ModelAnim_SetAnimation(&arg0->afterimages[i].displayObject, arg0->displayObject.transformAnim.animationId);
        if (arg0->afterimages[i].displayObject.scale.y < 0.68f) {
            arg0->afterimages[i].minimized = 1;
        }
    }
    for (i = 0; i < 2; i++) {
        if (arg0->afterimages[i].minimized == 1) {
            count++;
        }
    }
    if (count == 2) {
        return 1;
    }
    return 0;
}


/**
 * Shows the first two afterimages exactly on the Pokémon, copying its animation, pose
 * and scale, at alpha 65 and 61.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (10 of the moves).
 * @unverified Name from Stadium 1.
 */
void BattleScene_ShowSecondaryModelsStaggeredFrame(ActivePokemon* active_pokemon) {
    s32 i;

    for (i = 0; i < 2; i++) {
        active_pokemon->afterimages[i].minimized = 0;
        active_pokemon->afterimages[i].displayObject.lodFraction = 0x41 - i * 4;
        active_pokemon->afterimages[i].displayObject.node.flags |= 1;

        ModelAnim_SetFrame(&active_pokemon->afterimages[i].displayObject, active_pokemon->displayObject.transformAnim.frameFixed >> 0x10);
        ModelAnim_SetAnimation(&active_pokemon->afterimages[i].displayObject, active_pokemon->displayObject.transformAnim.animationId);
        Vec3f_SetComponentsDuplicate(&active_pokemon->afterimages[i].displayObject.scale, 1.0f, 1.0f, 1.0f);
        BattleAnim_Vec3fCopy(&active_pokemon->afterimages[i].displayObject.position, &active_pokemon->displayObject.position);
        BattleAnim_Vec3sCopy(&active_pokemon->afterimages[i].displayObject.rotation, &active_pokemon->displayObject.rotation);
        BattleAnim_Vec3fCopy(&active_pokemon->afterimages[i].displayObject.scale, &active_pokemon->displayObject.scale);
    }
}
