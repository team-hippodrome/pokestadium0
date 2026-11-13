/* Stadium Zero fragment012_17ED00. */
/* C ported from the Stadium 1 decomp: src/fragments/battle_engine/battle_engine_helper.c. */

#include "fragments/battle_engine/battle_engine.h"
#include "model_animation.h"
#include "model_animation_events.h"
#include "model_renderer.h"
#include "text_system.h"
#include "matrix.h"
#include "pokemon.h"
#include "status.h"

#include "m2c_macros.h"

void func_8210840C(ActivePokemon*, ActivePokemon*, s32);
void func_82108648(ActivePokemon*, s32);

f32 BattleScene_GetParticipantModelXOffset(ActivePokemon* active_pokemon);
void BattleScene_SetParticipantModelScale(ActivePokemon* active_pokemon, f32 scale);
s32 BattleScene_GetParticipantSideIndex(ActivePokemon* active_pokemon);
void BattleScene_GetParticipantModelRotation(ActivePokemon* pokemon, Vec3s* dest);
s32 BattleAnim_GetSpeciesBySideIndex(s32 side);
s32 BattleAnim_GetOwnerSpecies(ActivePokemon* active_pokemon);
u8 BattleScene_IsParticipantModelVisible(ActivePokemon* active_pokemon);
void BattleScene_GetParticipantModelPosition(ActivePokemon* pokemon, Vec3f* dest);

extern f32 D_FLT_82189354[][4];

void BattleScene_PositionParticipantModel(ActivePokemon* active_pokemon) {
    if (BattleScene_GetParticipantSideIndex(active_pokemon) == 0) {
        if (active_pokemon->displayObject.objectType == GYARADOS) {
            Vec3f_SetComponentsDuplicate(&active_pokemon->displayObject.position, -200.0f, D_FLT_82189354[active_pokemon->displayObject.objectType][0], 0.0f);
        } else if ((active_pokemon->displayObject.objectType == VENUSAUR) || (active_pokemon->displayObject.objectType == LAPRAS)) {
            Vec3f_SetComponentsDuplicate(&active_pokemon->displayObject.position, -175.0f, D_FLT_82189354[active_pokemon->displayObject.objectType][0], 0.0f);
        } else if (active_pokemon->displayObject.objectType == ONIX) {
            Vec3f_SetComponentsDuplicate(&active_pokemon->displayObject.position, -200.0f, D_FLT_82189354[active_pokemon->displayObject.objectType][0], 7.5000005f);
        } else {
            Vec3f_SetComponentsDuplicate(&active_pokemon->displayObject.position, -150.0f, D_FLT_82189354[active_pokemon->displayObject.objectType][0], 0.0f);
        }
    } else if ((active_pokemon->displayObject.objectType == GYARADOS) || (active_pokemon->displayObject.objectType == ONIX)) {
        Vec3f_SetComponentsDuplicate(&active_pokemon->displayObject.position, 200.0f, D_FLT_82189354[active_pokemon->displayObject.objectType][0], 0.0f);
    } else if ((active_pokemon->displayObject.objectType == VENUSAUR) || (active_pokemon->displayObject.objectType == LAPRAS)) {
        Vec3f_SetComponentsDuplicate(&active_pokemon->displayObject.position, 175.0f, D_FLT_82189354[active_pokemon->displayObject.objectType][0], 0.0f);
    } else {
        Vec3f_SetComponentsDuplicate(&active_pokemon->displayObject.position, 150.0f, D_FLT_82189354[active_pokemon->displayObject.objectType][0], 0.0f);
    }
}

f32 BattleScene_GetParticipantModelXOffset(ActivePokemon* active_pokemon) {
    if (BattleScene_GetParticipantSideIndex(active_pokemon) == 0) {
        if ((active_pokemon->displayObject.objectType == GYARADOS) || (active_pokemon->displayObject.objectType == ONIX)) {
            return -200.0f;
        }

        if ((active_pokemon->displayObject.objectType == VENUSAUR) || (active_pokemon->displayObject.objectType == LAPRAS)) {
            return -175.0f;
        }
        return -150.0f;
    }

    if ((active_pokemon->displayObject.objectType == GYARADOS) || (active_pokemon->displayObject.objectType == ONIX)) {
        return 200.0f;
    }

    if ((active_pokemon->displayObject.objectType == VENUSAUR) || (active_pokemon->displayObject.objectType == LAPRAS)) {
        return 175.0f;
    }

    return 150.0f;
}

void func_821079E8(s16 value) {
    ActivePokemonState* side1 = &sActivePokemon[0]->state;
    ActivePokemonState* side2 = &sActivePokemon[1]->state;
    M2C_FIELD(side1, s16*, 0x34) = value;
    M2C_FIELD(side2, s16*, 0x34) = value;
}

void BattleScene_SetParticipantModelScale(ActivePokemon* active_pokemon, f32 scale) {
    active_pokemon->displayObject.scale.x = scale;
    active_pokemon->displayObject.scale.y = scale;
    active_pokemon->displayObject.scale.z = scale;
}

u8 func_82107A30(s8 *arg0) {
    return M2C_FIELD(M2C_FIELD(arg0, s8 **, 0x860), u8 *, 2);
}

//@unverified
/**
 * Returns how many Pokemon the other member of arg0's tag team brought
 * (teamMember[1] when arg0 is member 0, otherwise teamMember[0]).
 */
u8 func_82107A3C(ActivePokemon* arg0) {
    s32 other = arg0->state.teamMemberIndex == 0;

    return arg0->sessionTeams->teamMember[other]->numberOfPokemonBrought;
}

s32 BattleScene_GetParticipantSideIndex(ActivePokemon* active_pokemon) {
    if (active_pokemon == sSide1ActivePokemon) {
        return 0;
    }
    return 1;
}

u8 BattleScene_GetMoveCueDefaultAnchor(ActivePokemon* active_pokemon) {
    UNUSED s32 pad;
    UNUSED s16 pad2;
    s16 move_index = active_pokemon->state.runtime.usedMove - 1;
    MovePresentationCue* move_cue = &sSideBattleCues[BattleScene_GetParticipantSideIndex(active_pokemon)]->moveCues[move_index];

    return move_cue->defaultAnchor;
}

u8 BattleScene_GetMoveCueAlternateAnchor(ActivePokemon* active_pokemon) {
    UNUSED s32 pad;
    UNUSED s16 pad2;
    s16 move_index = active_pokemon->state.runtime.usedMove - 1;
    MovePresentationCue* move_cue = &sSideBattleCues[BattleScene_GetParticipantSideIndex(active_pokemon)]->moveCues[move_index];

    return move_cue->alternateAnchor;
}

s16 BattleScene_GetHitCueDefaultAnchor(ActivePokemon* active_pokemon) {
    MovePresentationCue* hit_cue = &sSideBattleCues[BattleScene_GetParticipantSideIndex(active_pokemon)]->hitCue;

    return hit_cue->defaultAnchor;
}

s16 func_82107B54(ActivePokemon* active_pokemon) {
    MovePresentationCue* hit_cue = &sSideBattleCues[BattleScene_GetParticipantSideIndex(active_pokemon)]->hitCue;

    return M2C_FIELD(hit_cue, u8*, 3);
}

extern f32 D_FLT_82189350[][4];

/*
 * func_82107B88
 *
 * Returns the participant's scaled model width: the table entry for its object
 * type (first float of each 0x10-byte entry of D_FLT_82189350, the same table
 * whose second float func_82107790 reads as a resting height), doubled, divided
 * by 50, times the display object's Y scale. Zero-side relative of the width
 * term used by BattleScene_GetParticipantModelWidth in Stadium 1.
 */
f32 func_82107B88(ActivePokemon* active_pokemon) {
    return ((D_FLT_82189350[active_pokemon->displayObject.objectType][0] * 2) / 50.0f) * active_pokemon->displayObject.scale.y;
}

extern f32 D_FLT_82189350[][4];

/*
 * func_82107BC4
 *
 * Same as func_82107B88 without the final scale factor: the table width for the
 * participant's object type, doubled and divided by 50.
 */
f32 func_82107BC4(ActivePokemon* active_pokemon) {
    return (D_FLT_82189350[active_pokemon->displayObject.objectType][0] * 2) / 50.0f;
}

u8 func_82107BF4(s8 *arg0) {
    return M2C_FIELD(arg0, u8 *, 0x820);
}

extern f32 D_FLT_8218935C[][4];

void func_82107BFC(s8* arg0, Vec3f* out) {
    out->x = M2C_FIELD(arg0, f32*, 0x30) * (D_FLT_8218935C[M2C_FIELD(arg0, s16*, 0x1A) - 1][0] * 2 / 50.0f);
    out->y = M2C_FIELD(arg0, f32*, 0x34) * (D_FLT_8218935C[M2C_FIELD(arg0, s16*, 0x1A) - 1][1] * 2 / 50.0f);
    out->z = M2C_FIELD(arg0, f32*, 0x30) * (D_FLT_8218935C[M2C_FIELD(arg0, s16*, 0x1A) - 1][0] * 2 / 50.0f);
}

void BattleScene_GetParticipantModelRotation(ActivePokemon* pokemon, Vec3s* dest) {
    dest->x = pokemon->displayObject.rotation.x;
    dest->y = pokemon->displayObject.rotation.y;
    dest->z = pokemon->displayObject.rotation.z;
}

u16 Battle_GetActiveMonHp(ActivePokemon* active_pokemon) {
    BattleMon* party_pokemon = &active_pokemon->teamRoster->pokemonPicked[active_pokemon->state.rosterIndex];

    return party_pokemon->hp;
}

s16 func_82107CC4(s8 *arg0) {
    return (s16) (M2C_FIELD(arg0, s32 *, 0x60C) << 0xE);
}

s32 BattleAnim_GetSpeciesBySideIndex(s32 side) {
    return sActivePokemon[side]->displayObject.objectType;
}

s32 BattleAnim_GetOwnerSpecies(ActivePokemon* active_pokemon) {
    return active_pokemon->displayObject.objectType;
}

u8 BattleScene_IsParticipantModelVisible(ActivePokemon* active_pokemon) {
    s32 visible = active_pokemon->displayObject.node.flags & 1;
    return visible;
}

void BattleScene_GetParticipantModelPosition(ActivePokemon* pokemon, Vec3f* dest) {
    dest->x = pokemon->displayObject.position.x;
    dest->y = pokemon->displayObject.position.y;
    dest->z = pokemon->displayObject.position.z;
}

f32 func_82107EC8(ActivePokemon*);
void func_82107D24(ActivePokemon *arg0, u8 *arg1) {
    if (*D_FLT_82189354[arg0->displayObject.objectType] != 0.0f) {
        M2C_FIELD(arg1, f32 *, 0) = (f32) arg0->displayObject.position.x;
        M2C_FIELD(arg1, f32 *, 4) = (f32) arg0->displayObject.position.y;
        M2C_FIELD(arg1, f32 *, 8) = (f32) arg0->displayObject.position.z;
    } else {
        M2C_FIELD(arg1, f32 *, 0) = (f32) arg0->displayObject.position.x;
        M2C_FIELD(arg1, f32 *, 4) = (f32) (func_82107EC8(arg0) + arg0->displayObject.position.y);
        M2C_FIELD(arg1, f32 *, 8) = (f32) arg0->displayObject.position.z;
    }
    if (M2C_FIELD(arg1, f32 *, 4) < 0.0f) {
        M2C_FIELD(arg1, f32 *, 4) = func_82107EC8(arg0);
    }
}

f32 func_8210791C(ActivePokemon*);
f32 func_82107EC8(ActivePokemon*);
void func_82107DDC(ActivePokemon* active_pokemon, Vec3f* out) {
    if (D_FLT_82189354[active_pokemon->displayObject.objectType][0] != 0.0f) {
        out->x = func_8210791C(active_pokemon);
        out->y = active_pokemon->displayObject.position.y;
        out->z = 0.0f;
    } else {
        out->x = func_8210791C(active_pokemon);
        out->y = func_82107EC8(active_pokemon) + active_pokemon->displayObject.position.y;
        out->z = 0.0f;
    }
    if (out->y < 0.0f) {
        out->y = func_82107EC8(active_pokemon);
    }
}

void func_82107EA0(s8 *arg0, s8 *arg1) {
    M2C_FIELD(arg1, f32 *, 0) = (f32) M2C_FIELD(arg0, f32 *, 0x648);
    M2C_FIELD(arg1, f32 *, 4) = (f32) (M2C_FIELD(arg0, f32 *, 0x64C) + 2.5f);
    M2C_FIELD(arg1, f32 *, 8) = (f32) M2C_FIELD(arg0, f32 *, 0x650);
}

extern f32 D_FLT_82189350[][4];

/*
 * func_82107EC8
 *
 * Returns the table width (first float of the object type's entry in
 * D_FLT_82189350) unscaled when modelTransformId is 0x10, otherwise the same
 * width times the display object's Y scale. What transform 0x10 is has not been
 * established; the value is used literally here.
 */
f32 func_82107EC8(ActivePokemon* active_pokemon) {
    if (active_pokemon->modelTransformId == 0x10) {
        return D_FLT_82189350[active_pokemon->displayObject.objectType][0];
    }
    return D_FLT_82189350[active_pokemon->displayObject.objectType][0] * active_pokemon->displayObject.scale.y;
}

extern f32 D_FLT_8218934C[][4];
f32 func_82107F18(ActivePokemon* active_pokemon) {
    return D_FLT_8218934C[active_pokemon->displayObject.objectType][0] * active_pokemon->displayObject.scale.y;
}

ModelNodeView* Battle_GetLoadedModelNode(ActivePokemon* active_pokemon, s32 node_index) {
    return active_pokemon->sessionTeams->loadedModel->unk_00[2]->unk_00[node_index];
}

s16 func_82107F58(s8 *arg0, M2C_UNK arg1) {
    return M2C_FIELD(M2C_FIELD(arg0, s8 **, 0x85C), s16 *, 2);
}

typedef struct {
    /* 0x0 */ s32 unk_00;
    /* 0x4 */ s32 unk_04;
    /* 0x8 */ s32 unk_08;
} unk_D_8006A9CC; // size = 0xC
extern unk_D_8006A9CC D_8006A9CC[];

s32 func_82107F68(u8* arg0) {
    return D_8006A9CC[arg0[0x80A]].unk_00;
}

//@unverified
/**
 * Returns the unk_30 bytes (the 11-byte name buffer) of arg0's party Pokemon in
 * the roster of tag-team member state.unk_2D_zero.
 */
u8* func_82107F88(ActivePokemon* arg0) {
    return arg0->sessionTeams->teamMember[arg0->state.unk_2D_zero]->pokemonPicked[arg0->state.rosterIndex].unk_30;
}

void BattleScene_InitializeParticipantOwnerModel(ActivePokemon* active_pokemon) {
    ThumbnailState* presentation = &active_pokemon->thumbnail;
    ModelNodeView* model_view;
    s16 model_id;

    model_view = Battle_GetLoadedModelNode(active_pokemon, 0);
    model_id = Battle_GetDisplayModelId(active_pokemon, 0);
    ModelRenderer_AttachDisplayObject(&presentation->displayObject);

    if (active_pokemon == sActivePokemon[0]) {
        presentation->displayObject.effectSlot = 2;
        Model_InitDisplayObject(&presentation->displayObject, 1, model_id, model_view);
    } else {
        presentation->displayObject.effectSlot = 3;
        Model_InitDisplayObject(&presentation->displayObject, 2, model_id, model_view);
    }

    ModelAnim_SetAnimation(&presentation->displayObject, 0);
    ModelAnim_SetFrame(&presentation->displayObject, 0);
    presentation->displayObject.node.renderFlags &= ~0x40;
    Vec3f_SetComponentsDuplicate(&presentation->displayObject.position, 0.0f, 0.0f, 0.0f);
}

void BattleScene_InitializeParticipantSecondaryModels(ActivePokemon* pokemon, s32* secondary_models) {
    ModelNodeView* model_node;
    s16 object_type;
    s32 i;
    PokemonAfterimage* afterimage;
    model_node = Battle_GetLoadedModelNode(pokemon, 0);
    object_type = func_82107F58((s8*)pokemon, 0);
    for (i = 0; i < 3; i++) {
        afterimage = &pokemon->afterimages[i];
        ModelRenderer_AttachDisplayObject(&afterimage->displayObject);
        if (pokemon == sActivePokemon[0]) {
            M2C_FIELD(secondary_models, u8*, 0xA6) = 2;
        } else {
            M2C_FIELD(secondary_models, u8*, 0xA6) = 3;
        }
        Model_InitDisplayObject(&afterimage->displayObject, 0, object_type, model_node);
        ModelAnim_SetFrame(&afterimage->displayObject, 0);
        ModelAnim_SetAnimation(&afterimage->displayObject, 0);
        afterimage->displayObject.node.renderFlags &= ~0x40;
        if (pokemon == sActivePokemon[0]) {
            BattleScene_PositionParticipantModel(pokemon);
            afterimage->displayObject.rotation.y = 0x4000;
        } else {
            BattleScene_PositionParticipantModel(pokemon);
            afterimage->displayObject.rotation.y = -0x4000;
        }
        afterimage->displayObject.node.flags &= ~1;
    }
}

extern f32 D_82199DF0[][4];
void func_8000D41C(Vec3f*, f32, f32, f32);
void func_8210213C(ActivePokemon*);
void func_821081D0(ActivePokemon* active_pokemon) {
    s32 side;
    UNUSED s32 pad;
    ModelNodeView* model_view;
    s16 model_id;

    side = BattleScene_GetParticipantSideIndex(active_pokemon);
    model_view = Battle_GetLoadedModelNode(active_pokemon, 0);
    model_id = Battle_GetDisplayModelId(active_pokemon, 0);
    ModelRenderer_AttachDisplayObject(&active_pokemon->displayObject);

    if (active_pokemon == sActivePokemon[0]) {
        active_pokemon->displayObject.effectSlot = 0;
    } else {
        active_pokemon->displayObject.effectSlot = 1;
    }

    Model_InitDisplayObject(&active_pokemon->displayObject, 0, model_id, model_view);
    func_8210213C(active_pokemon);
    ModelAnim_SetAnimation(&active_pokemon->displayObject, 0);
    ModelAnim_SetFrame(&active_pokemon->displayObject, 0);

    active_pokemon->sessionTeams->unk_04 = &active_pokemon->teamRoster->pokemonPicked[active_pokemon->state.rosterIndex];
    if ((active_pokemon->displayObject.objectType == DIGLETT) || (active_pokemon->displayObject.objectType == DUGTRIO)) {
        active_pokemon->displayObject.node.renderFlags &= ~0x40;
    } else {
        active_pokemon->displayObject.node.renderFlags |= 0x40;
    }

    if (active_pokemon == sActivePokemon[0]) {
        BattleScene_PositionParticipantModel(active_pokemon);
        active_pokemon->displayObject.rotation.y = 0x4000;
    } else {
        BattleScene_PositionParticipantModel(active_pokemon);
        active_pokemon->displayObject.rotation.y = -0x4000;
    }
    func_8000D41C(&M2C_FIELD(active_pokemon, Vec3f*, 0x5DC), M2C_FIELD(active_pokemon, s32*, 0x60C) * D_82199DF0[side][0], D_82199DF0[side][1], D_82199DF0[side][2]);
}

void BattleScene_InitializeParticipantAuxiliaryModel(ActivePokemon* active_pokemon) {
    DisplayObject* auxiliary_model = &active_pokemon->pokeBall;
    ModelNodeView* model_view = active_pokemon->sessionTeams->unk_18;

    ModelRenderer_AttachDisplayObject(auxiliary_model);
    auxiliary_model->effectSlot = 2;
    Model_InitDisplayObject(auxiliary_model, 0, 153, model_view);
    ModelAnim_SetAnimation(auxiliary_model, 0);

    auxiliary_model->node.renderFlags &= ~0x20;
    auxiliary_model->node.flags &= ~1;

    if (active_pokemon == sActivePokemon[0]) {
        Vec3f_SetComponentsDuplicate(&auxiliary_model->position, -50.0f, 2.0f, 0.0f);
        M2C_FIELD(auxiliary_model, s16*, 0x20) = 0x4000;
    } else {
        Vec3f_SetComponentsDuplicate(&auxiliary_model->position, 50.0f, 2.0f, 0.0f);
        M2C_FIELD(auxiliary_model, s16*, 0x20) = -0x4000;
    }
}

void BattleScene_ReinitParticipantBodyModel(ActivePokemon* owner, ActivePokemon* pokemon, s16 object_type) {
    UNUSED s32 pad;
    ModelNodeView* model_node = Battle_GetLoadedModelNode(owner, 0);
    s32 side = BattleScene_GetParticipantSideIndex(owner);
    UNUSED s32 pad2;

    ModelRenderer_ClearDisplayObject(&pokemon->displayObject);

    if (owner == sActivePokemon[0]) {
        pokemon->displayObject.effectSlot = 0;
    } else {
        pokemon->displayObject.effectSlot = 1;
    }

    Model_InitDisplayObject(&pokemon->displayObject, 0, object_type, model_node);
    func_8210213C(owner);
    ModelAnim_SetFrame(&pokemon->displayObject, 0);
    ModelAnim_SetAnimation(&pokemon->displayObject, 0);

    owner->sessionTeams->unk_04 = &owner->teamRoster->pokemonPicked[owner->state.rosterIndex];
    if ((pokemon->displayObject.objectType == DIGLETT) || (pokemon->displayObject.objectType == DUGTRIO)) {
        pokemon->displayObject.node.renderFlags &= 0xFFBF;
    } else {
        pokemon->displayObject.node.renderFlags |= 0x40;
    }

    if (!(owner->state.flags & ACTIVE_AIRBORNE)) {
        if (owner == sActivePokemon[0]) {
            BattleScene_PositionParticipantModel(owner);
            pokemon->displayObject.rotation.y = 0x4000;
        } else {
            BattleScene_PositionParticipantModel(owner);
            pokemon->displayObject.rotation.y = -0x4000;
        }
    }
    func_8000D41C(&M2C_FIELD(owner, Vec3f*, 0x5DC), M2C_FIELD(owner, s32*, 0x60C) * D_82199DF0[side][0], D_82199DF0[side][1], D_82199DF0[side][2]);
}

void BattleScene_ReinitParticipantThumbnailModel(ActivePokemon* pokemon, ThumbnailState* thumbnail, s16 object_type) {
    ModelNodeView* model_node;

    model_node = Battle_GetLoadedModelNode(pokemon, 0);
    ModelRenderer_ClearDisplayObject(&thumbnail->displayObject);

    if (pokemon == sActivePokemon[0]) {
        thumbnail->displayObject.effectSlot = 0x2;
    } else {
        thumbnail->displayObject.effectSlot = 0x3;
    }

    if (pokemon == sActivePokemon[0]) {
        Model_InitDisplayObject(&thumbnail->displayObject, 1, object_type, model_node);
    } else {
        Model_InitDisplayObject(&thumbnail->displayObject, 2, object_type, model_node);
    }

    ModelAnim_SetFrame(&thumbnail->displayObject, 0);
    ModelAnim_SetAnimation(&thumbnail->displayObject, 0);
    thumbnail->displayObject.node.renderFlags &= ~0x40;
}

void BattleScene_ReinitParticipantAfterimages(ActivePokemon* pokemon, s16 object_type) {
    s32 i;
    ModelNodeView* model_node;
    PokemonAfterimage* afterimage;

    model_node = Battle_GetLoadedModelNode(pokemon, 0);

    for (i = 0; i < 3; i++) {
        afterimage = &pokemon->afterimages[i];

        ModelRenderer_ClearDisplayObject(&afterimage->displayObject);
        if (pokemon == sActivePokemon[0]) {
            afterimage->displayObject.effectSlot = 2;
        } else {
            afterimage->displayObject.effectSlot = 3;
        }

        Model_InitDisplayObject(&afterimage->displayObject, 0, object_type, model_node);
        ModelAnim_SetFrame(&afterimage->displayObject, 0);
        ModelAnim_SetAnimation(&afterimage->displayObject, 0);

        afterimage->displayObject.node.renderFlags &= ~0x40;

        if (pokemon == sActivePokemon[0]) {
            Vec3f_SetComponentsDuplicate(&afterimage->displayObject.position, -150.0f, 0.0f, 0.0f);
            afterimage->displayObject.rotation.y = 0x4000;
        } else {
            Vec3f_SetComponentsDuplicate(&afterimage->displayObject.position, 150.0f, 0.0f, 0.0f);
            afterimage->displayObject.rotation.y = -0x4000;
        }

        afterimage->displayObject.node.flags &= ~1;
    }
}

void Battle_ResetEventTrack(ActivePokemon* active_pokemon) {
    if (active_pokemon->state.flags & ACTIVE_SLEEP) {
        BattleAnim_TrySetModelEventTrackFromRow(active_pokemon, 0xAF, 2);
    } else {
        active_pokemon->state.unk_36 = 0;
        ModelAnim_SetEventFrame(&active_pokemon->displayObject, 0);
        ModelAnim_SetEventTrack(&active_pokemon->displayObject, -1);
    }
}

void Battle_LoadOwnerModelForSpecies(ActivePokemon* active_pokemon) {
    ActivePokemonState* state = &active_pokemon->state;
    UNUSED s32 pad[3];
    s16 object_type;

    Battle_GetLoadedModelNode(active_pokemon, 0);
    object_type = Battle_GetDisplayModelId(active_pokemon, 0);
    func_8210840C(active_pokemon, active_pokemon, object_type);
    BattleScene_ReinitParticipantThumbnailModel(active_pokemon, &active_pokemon->thumbnail, object_type);
    func_82108648(active_pokemon, object_type);
    Battle_ResetEventTrack(active_pokemon);
    state->flags &= 0x3800;
    Vec3f_SetComponentsDuplicate(&active_pokemon->displayObject.scale, 1.0f, 1.0f, 1.0f);
}

void func_821088BC(ActivePokemon* active_pokemon) {
    ActivePokemonState* state = &active_pokemon->state;
    UNUSED s32 pad[3];
    s16 object_type;

    Battle_GetLoadedModelNode(active_pokemon, 0);
    object_type = Battle_GetDisplayModelId(active_pokemon, 0);
    func_8210840C(active_pokemon, active_pokemon, object_type);
    BattleScene_ReinitParticipantThumbnailModel(active_pokemon, &active_pokemon->thumbnail, object_type);
    func_82108648(active_pokemon, object_type);
    Battle_ResetEventTrack(active_pokemon);
    M2C_FIELD(state, u8*, 0x2E) = 0;
    state->flags &= 0x3800;
    Vec3f_SetComponentsDuplicate(&active_pokemon->displayObject.scale, 1.0f, 1.0f, 1.0f);
}

void Battle_ResetOwnerModelToSubstituteDoll(ActivePokemon* active_pokemon) {
    Model_SetMaterialColor(&active_pokemon->displayObject, 0xFF, 0xFF, 0xFF, active_pokemon->state.alpha = 0xFF);
    active_pokemon->state.model = active_pokemon->displayObject.objectType;
    func_8210840C(active_pokemon, active_pokemon, SUBSTITUTE_DOLL);
    func_82108648(active_pokemon, SUBSTITUTE_DOLL);
    Battle_ResetEventTrack(active_pokemon);
}

void Battle_ReloadSubstituteDoll(ActivePokemon* active_pokemon) {
    func_8210840C(active_pokemon, active_pokemon, SUBSTITUTE_DOLL);
    func_82108648(active_pokemon, SUBSTITUTE_DOLL);
    Battle_ResetEventTrack(active_pokemon);
}

void Battle_ReloadDisplayModel(ActivePokemon* active_pokemon) {
    UNUSED s32 pad[3];
    ActivePokemonState* state = &active_pokemon->state;
    s16 object_type = Battle_GetDisplayModelId(active_pokemon, 0);

    state->alpha = 0xFF;
    Model_SetMaterialColor(&active_pokemon->displayObject, 0xFF, 0xFF, 0xFF, state->alpha);
    func_8210840C(active_pokemon, active_pokemon, object_type);
    func_82108648(active_pokemon, object_type);
    Battle_ResetEventTrack(active_pokemon);
}

void func_82108A88(s8 *arg0, s32 arg1, s32 arg2) {
    M2C_FIELD(arg0, s32 *, 0x610) = arg1;
    M2C_FIELD(arg0, s32 *, 0x614) = arg2;
}

void Battle_ReturnToIdleAnimIfFinished(ActivePokemon* active_pokemon, ActivePokemon* animated_pokemon) {
    s32 idx;
    MovePresentationCue* idle_cue;
    MovePresentationCue* flying_cue;
    MovePresentationCue* sleep_idle_cue;
    ActivePokemonState* pokemon_state = &active_pokemon->state;

    idx = BattleScene_GetParticipantSideIndex(active_pokemon);
    idle_cue = (MovePresentationCue*)((u8*)sSideBattleCues[idx] + 0x717);
    idx = BattleScene_GetParticipantSideIndex(active_pokemon);
    flying_cue = (MovePresentationCue*)((u8*)sSideBattleCues[idx] + 0x790);
    idx = BattleScene_GetParticipantSideIndex(active_pokemon);
    sleep_idle_cue = (MovePresentationCue*)((u8*)sSideBattleCues[idx] + 0x785);
    if (!(pokemon_state->flags & 0x4002)) {
        if ((BattleAnim_IsSessionBusy(active_pokemon) == 0) && (animated_pokemon->displayObject.transformAnim.animationId != -1) &&
            (ModelAnim_IsFinished(&animated_pokemon->displayObject) == 1)) {
            if (pokemon_state->flags & 0x200) {
                ModelAnim_SetAnimation(&animated_pokemon->displayObject, flying_cue->id);
            } else if ((pokemon_state->flags & 1) && ((animated_pokemon->displayObject.objectType == 0x39) || (animated_pokemon->displayObject.objectType == 0x67))) {
                ModelAnim_SetAnimation(&animated_pokemon->displayObject, sleep_idle_cue->id);
            } else {
                if (animated_pokemon->displayObject.objectType == DITTO) {
                    idx = BattleAnim_RandomRange(5);
                    ModelAnim_SetAnimation(&animated_pokemon->displayObject, idx + 13);
                } else {
                    ModelAnim_SetAnimation(&animated_pokemon->displayObject, idle_cue->id);
                }
            }
            ModelAnim_SetFrame(&animated_pokemon->displayObject, 0);
        }
    }
}

void Battle_ResetModelToIdleAnim(ActivePokemon* active_pokemon) {
    s32 idx;
    ActivePokemonState* state;
    u8* idle_cue;
    u8* flying_idle_cue;
    u8* sleep_idle_cue;

    state = &active_pokemon->state;
    idx = BattleScene_GetParticipantSideIndex(active_pokemon);
    idle_cue = (u8*)sSideBattleCues[idx] + 0x717;
    idx = BattleScene_GetParticipantSideIndex(active_pokemon);
    flying_idle_cue = (u8*)sSideBattleCues[idx] + 0x790;
    idx = BattleScene_GetParticipantSideIndex(active_pokemon);
    sleep_idle_cue = (u8*)sSideBattleCues[idx] + 0x785;

    if (!(state->flags & 0x4002) && (BattleAnim_IsSessionBusy(active_pokemon) == 0) && (active_pokemon->displayObject.transformAnim.animationId != -1)) {
        if (state->flags & 0x200) {
            ModelAnim_SetAnimation(&active_pokemon->displayObject, *flying_idle_cue);
        } else if ((state->flags & 1) && ((active_pokemon->displayObject.objectType == 0x39) || (active_pokemon->displayObject.objectType == 0x67))) {
            ModelAnim_SetAnimation(&active_pokemon->displayObject, *sleep_idle_cue);
        } else if (active_pokemon->displayObject.objectType == 0x84) {
            ModelAnim_SetAnimation(&active_pokemon->displayObject, BattleAnim_RandomRange(5) + 13);
        } else {
            ModelAnim_SetAnimation(&active_pokemon->displayObject, *idle_cue);
        }
        ModelAnim_SetFrame(&active_pokemon->displayObject, 0);
    }
}

void Battle_SetModelToHitAnim(ActivePokemon* active_pokemon) {
    extern PokemonBattleCues* D_82189180[];
    MovePresentationCue* hit_cue = &D_82189180[BattleScene_GetParticipantSideIndex(active_pokemon)]->hitCue;

    if (active_pokemon->displayObject.transformAnim.animationId != -1) {
        ModelAnim_SetFrame(&active_pokemon->displayObject, 0);
        ModelAnim_SetAnimation(&active_pokemon->displayObject, hit_cue->id);
    }
}

void func_82108DC8(s8 *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0x860) = (s32) M2C_FIELD((M2C_FIELD(arg0, s32 *, 0x85C) + (arg1 * 4)), s32 *, 8);
}

void func_82108DE0(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s8 *, 0x7B7) = arg1;
}

void func_82108DE8(s8 *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0x858) = arg1;
}

void func_82108DF0(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s8 *, 0x7B9) = arg1;
}

void BattleScene_RebindParticipantTeamMember(ActivePokemon* pokemon, s32 team_member_index) {
    ActivePokemonState* state = &pokemon->state;

    BattleScene_BindParticipantTeamRoster(pokemon, team_member_index);
    BattleScene_SetParticipantTeamMember(pokemon, team_member_index);
    M2C_FIELD(pokemon, s32*, 0x9D0) = M2C_FIELD(state, s32*, 0x8);
    M2C_FIELD(pokemon, s32*, 0x9D4) = M2C_FIELD(state, u8*, 0x2B);
}

s32 Battle_FreezeClauseInEffect(ActivePokemon* active_pokemon) {
    s32 i;
    ActivePokemonState* state;
    BattleMon* pokemon;

    state = &active_pokemon->state;

    for (i = 0; i < BattleScene_GetTeamMemberTeamSize(active_pokemon); i++) {
        pokemon = &active_pokemon->teamRoster->pokemonPicked[i];
        if ((pokemon->statusCondition & STATUS_FREEZE) && (active_pokemon->state.runtime.roster[state->rosterIndex + state->teamMemberIndex * 3] == 0)) {
            return 1;
        }
    }

    if (active_pokemon->sessionTeams->tagTeamSize == 2) {
        for (i = 0; i < BattleScene_GetPartnerTeamSize(active_pokemon); i++) {
            pokemon = &active_pokemon->sessionTeams->teamMember[state->teamMemberIndex == 0]->pokemonPicked[i];
            if ((pokemon->statusCondition & STATUS_FREEZE) &&
                (active_pokemon->state.runtime.roster[state->rosterIndex + (state->teamMemberIndex == 0) * 3] == 0)) {
                return 1;
            }
        }
    }

    return 0;
}

s32 Battle_SleepClauseInEffect(ActivePokemon* active_pokemon) {
    s32 i;
    ActivePokemonState* state;
    BattleMon* pokemon;

    state = &active_pokemon->state;

    for (i = 0; i < BattleScene_GetTeamMemberTeamSize(active_pokemon); i++) {
        pokemon = &active_pokemon->teamRoster->pokemonPicked[i];
        if ((pokemon->statusCondition & STATUS_SLEEP_MASK) && (active_pokemon->state.runtime.roster[state->rosterIndex + state->teamMemberIndex * 3] == 0)) {
            return 1;
        }
    }

    if (active_pokemon->sessionTeams->tagTeamSize == 2) {
        for (i = 0; i < BattleScene_GetPartnerTeamSize(active_pokemon); i++) {
            pokemon = &active_pokemon->sessionTeams->teamMember[state->teamMemberIndex == 0]->pokemonPicked[i];
            if ((pokemon->statusCondition & STATUS_SLEEP_MASK) && (active_pokemon->state.runtime.roster[state->rosterIndex + (state->teamMemberIndex == 0) * 3] == 0)) {
                return 1;
            }
        }
    }
    return 0;
}
