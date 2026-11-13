/* Stadium Zero fragment012_17ED00. */
/* C ported from the Stadium 1 decomp: src/fragments/battle_engine/battle_engine_thumbnail.c. */

#include "fragments/battle_engine/battle_engine.h"
#include "model_animation.h"
#include "model_renderer.h"
#include "model_renderer_callbacks.h"
#include "matrix.h"
#include "status.h"

#include "m2c_macros.h"

void BattleThumbnail_SetupOwnerCameraFraming(ActivePokemon* side1_pokemon, ActivePokemon* side2_pokemon);
void BattleThumbnail_OwnerCameraLifecycleNop(void);
void BattleThumbnail_TickOwnerCameraFraming(ActivePokemon* active_pokemon);
s32 BattleThumbnail_DispatchOwnerCameraLifecycle(s32 state, CameraNode* side1_camera_node, CameraNode* side2_camera_node);

void BattleThumbnail_ClearBothOwnerIdleFlags(void);
void BattleThumbnail_SetBothOwnerIdleFlags(void);
void BattleThumbnail_LoadOwnerCameraFramingConstants(ActivePokemon* active_pokemon);
void BattleThumbnail_ApplyOwnerCameraFraming(ActivePokemon* active_pokemon);
void BattleThumbnail_InitializeOwnerCameraFraming(CameraNode* side1_camera_node, ActivePokemon* side1_pokemon, CameraNode* side2_camera_node, ActivePokemon* side2_pokemon);
void BattleThumbnail_TickBothOwnerSlideAnimations(ActivePokemon* side1_pokemon, ActivePokemon* side2_pokemon);

/*
    Sets up the camera framing for both pokemons's thumbnails.
*/
void BattleThumbnail_SetupOwnerCameraFraming(ActivePokemon* side1_pokemon, ActivePokemon* side2_pokemon) {
    if (sBattleScene.scene->mode == 1) {
        BattleThumbnail_SetBothOwnerIdleFlags();
    } else {
        BattleThumbnail_ClearBothOwnerIdleFlags();
    }
    BattleThumbnail_LoadOwnerCameraFramingConstants(side1_pokemon);
    BattleThumbnail_LoadOwnerCameraFramingConstants(side2_pokemon);
}

/*
    Nop
*/
void BattleThumbnail_OwnerCameraLifecycleNop(void) {
}

/**
 * Applies the sets coordinates for the Camera that generates the owner's thumbnail.
 * Seen in play (2026-11-13) (tour of menus and a COM battle): ran in the battle opening and a
 * switch in battle.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void BattleThumbnail_ApplyOwnerCameraFraming(ActivePokemon* active_pokemon) {
    s32 side;
    CameraNode* camera;
    f32 tmp_z;
    f32 tmp_y;

    camera = active_pokemon->thumbnail.camera;
    side = BattleScene_GetParticipantSideIndex(active_pokemon);

    active_pokemon->thumbnail.rotationX = sSidePresentationTransform[side]->rotationX;
    if (sSidePresentationTransform[side]->unk_10 == 0xFF) {
        active_pokemon->thumbnail.rotationY = sSidePresentationTransform[side]->rotationY * active_pokemon->thumbnail.side;
        tmp_z = sSidePresentationTransform[side]->coordinates.z * active_pokemon->thumbnail.side;
    } else {
        active_pokemon->thumbnail.rotationY = sSidePresentationTransform[side]->rotationY;
        tmp_z = sSidePresentationTransform[side]->coordinates.z;
    }

    active_pokemon->thumbnail.z = tmp_z;
    active_pokemon->thumbnail.x = sSidePresentationTransform[side]->coordinates.x;
    active_pokemon->thumbnail.idleTimer = sSidePresentationTransform[side]->idleTimer;
    tmp_y = sSidePresentationTransform[side]->coordinates.y;
    active_pokemon->thumbnail.y = tmp_y;

    BattleScene_SetCameraAtAndEyeFromAngles(camera, active_pokemon->thumbnail.displayObject.position.x + active_pokemon->thumbnail.z, active_pokemon->thumbnail.displayObject.position.y + tmp_y,
                  active_pokemon->thumbnail.displayObject.position.z, active_pokemon->thumbnail.x, active_pokemon->thumbnail.rotationX, active_pokemon->thumbnail.rotationY);
}

/*
    Updates the camera coordinates for the owner's thumbnail.
*/
void BattleThumbnail_TickOwnerCameraFraming(ActivePokemon* active_pokemon) {
    BattleThumbnail_ApplyOwnerCameraFraming(active_pokemon);
}

M2C_UNK func_82107290(s8 *, s8 *);              /* extern */
M2C_UNK func_82107408(s8 *);                      /* extern */

void func_82107428(s32 arg0, s8 *arg1, s32 arg2, s8 *arg3) {
    M2C_FIELD(arg1, s32 *, 0x9CC) = arg0;
    M2C_FIELD(arg3, s32 *, 0x9CC) = arg2;
    func_82107290(arg1, arg3);
    func_82107408(arg1);
    func_82107408(arg3);
}

s32 func_80032890(s32);
void func_80032840(s32);

/**
 * Handles the slide-in animation for the owner's thumbnail for when move selection is ongoing.
 * Seen in play (2026-11-13) (tour of menus and a COM battle): ran in the battle opening, a switch
 * in battle, running from battle and a Pound turn.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void BattleThumbnail_TickOwnerSlideIn(ActivePokemon* active_pokemon, s32 delta) {
    s16 var_a0; // FAKE
    CameraNode* camera_node;

    active_pokemon->thumbnail.camera->node.flags |= 1;
    active_pokemon->thumbnail.displayObject.node.flags |= 1;

    if (active_pokemon->thumbnail.side == 1) {
        // This Substitute condition can never actually fire as switching out a pokemon destroys the substitute.
        if ((active_pokemon->thumbnail.camera->viewport.x == -72) && !(active_pokemon->state.flags & 0x2000)) {
            BattleThumbnail_TriggerOwnerModelAnimation(active_pokemon);
        }

        if ((func_80032890(0) != 0) && (active_pokemon->thumbnail.status == 0)) {
            active_pokemon->thumbnail.status = 2;
            func_80032840(0);
        }
        active_pokemon->thumbnail.camera->viewport.x = Math_StepToS32(active_pokemon->thumbnail.camera->viewport.x, 0x17, delta, delta);
    } else {
        if ((active_pokemon->thumbnail.camera->viewport.x == 351) && !(active_pokemon->state.flags & 0x2000)) {
            BattleThumbnail_TriggerOwnerModelAnimation(active_pokemon);
        }

        active_pokemon->thumbnail.camera->viewport.x = Math_StepToS32(active_pokemon->thumbnail.camera->viewport.x, 0x103, delta, delta);

        if ((func_80032890(1) != 0) && (active_pokemon->thumbnail.status == 0)) {
            active_pokemon->thumbnail.status = 2;
            func_80032840(1);
        }
    }
}

s16 func_8000F1FC(s16, M2C_UNK, M2C_UNK, M2C_UNK);  /* extern */

void func_821075B4(s8 *arg0, M2C_UNK arg1) {
    s8 *temp_v1;
    s8 *temp_v1_2;

    if (M2C_FIELD(arg0, s32 *, 0x9E0) == 1) {
        M2C_FIELD(arg0, s32 *, 0x9F4) = 0;
        M2C_FIELD(M2C_FIELD(arg0, s8 **, 0x9CC), s16 *, 0x1C) = func_8000F1FC(M2C_FIELD(M2C_FIELD(arg0, s8 **, 0x9CC), s16 *, 0x1C), -0x48, arg1, arg1);
        temp_v1 = M2C_FIELD(arg0, s8 **, 0x9CC);
        if (M2C_FIELD(temp_v1, s16 *, 0x1C) == -0x48) {
            M2C_FIELD(temp_v1, u8 *, 1) = (u8) (M2C_FIELD(temp_v1, u8 *, 1) & 0xFFFE);
            M2C_FIELD(arg0, u8 *, 0x865) = (u8) (M2C_FIELD(arg0, u8 *, 0x865) & 0xFFFE);
        }
    } else {
        M2C_FIELD(arg0, s32 *, 0x9F4) = 0;
        M2C_FIELD(M2C_FIELD(arg0, s8 **, 0x9CC), s16 *, 0x1C) = func_8000F1FC(M2C_FIELD(M2C_FIELD(arg0, s8 **, 0x9CC), s16 *, 0x1C), 0x15F, arg1, arg1);
        temp_v1_2 = M2C_FIELD(arg0, s8 **, 0x9CC);
        if (M2C_FIELD(temp_v1_2, s16 *, 0x1C) == 0x15F) {
            M2C_FIELD(temp_v1_2, u8 *, 1) = (u8) (M2C_FIELD(temp_v1_2, u8 *, 1) & 0xFFFE);
            M2C_FIELD(arg0, u8 *, 0x865) = (u8) (M2C_FIELD(arg0, u8 *, 0x865) & 0xFFFE);
        }
    }
}

/**
 * Handles the slide animation for the owner's thumbnail.
 * Seen in play (2026-11-13) (tour of menus and a COM battle): ran in the battle opening, a switch
 * in battle, running from battle and a Pound turn.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void BattleThumbnail_TickOwnerSlideAnimation(ActivePokemon* active_pokemon) {
    switch (active_pokemon->thumbnail.showing) {
        case 0:
            BattleThumbnail_TickOwnerSlideOut(active_pokemon, 9);
            break;

        case 1:
            BattleThumbnail_TickOwnerSlideIn(active_pokemon, 9);
            break;
    }
}

/**
 * Avoids drawing the thumbnails in the attract demo
 * Seen in play (2026-11-13) (tour of menus and a COM battle): ran in the battle opening, a switch
 * in battle, running from battle and a Pound turn.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void BattleThumbnail_TickBothOwnerSlideAnimations(ActivePokemon* side1_pokemon, ActivePokemon* side2_pokemon) {
    BattleThumbnail_TickOwnerSlideAnimation(side1_pokemon);
    BattleThumbnail_TickOwnerSlideAnimation(side2_pokemon);
}

/*
    Dispatches the thumbnail's rendering based on the current of the battle
*/
s32 BattleThumbnail_DispatchOwnerCameraLifecycle(s32 state, CameraNode* side1_camera_node, CameraNode* side2_camera_node) {
    switch (state) {
        case 0:
            BattleThumbnail_OwnerCameraLifecycleNop();
            break;

        case 1:
        case 2:
            BattleThumbnail_TickBothOwnerSlideAnimations(sActivePokemon[0], sActivePokemon[1]);
            break;

        case 3:
            BattleThumbnail_InitializeOwnerCameraFraming(side1_camera_node, sActivePokemon[0], side2_camera_node, sActivePokemon[1]);
            break;
    }
    return 0;
}
