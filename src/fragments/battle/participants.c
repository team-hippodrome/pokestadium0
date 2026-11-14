/* Stadium Zero fragment012_17ED00. */
/* C ported from the Stadium 1 decomp: src/fragments/battle_engine/battle_engine_helper.c. */

#include "battle.h"
#include "geo_node.h"
#include "matrix.h"
#include "model_renderer.h"
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

/**
 * Places the Pokémon's model on its side of the field: 150 units from the center (175
 * for Venusaur and Lapras, 200 for Gyarados and Onix), at the species' standing height.
 * Side 1 is at negative X.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (6 of the moves).
 * @unverified Name from Stadium 1.
 */
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

/**
 * Returns the X position BattleScene_PositionParticipantModel uses for this Pokémon: +-150,
 * +-175 for Venusaur and Lapras, +-200 for Gyarados and Onix (negative on side 1).
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (124 of the moves).
 * @unverified Name from Stadium 1.
 */
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

/**
 * Sets field 0x34 of both Pokemon's state (the camera clip mask) to value.
 */
void func_821079E8(s16 value) {
    ActivePokemonState* side1 = &sActivePokemon[0]->state;
    ActivePokemonState* side2 = &sActivePokemon[1]->state;
    M2C_FIELD(side1, s16*, 0x34) = value;
    M2C_FIELD(side2, s16*, 0x34) = value;
}

/**
 * Sets the Pokémon model's scale on all three axes.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal or j,
 * no pointer word, no lui/addiu pair in any fragment), so play cannot reach it.
 * @unverified Name from Stadium 1.
 */
void BattleScene_SetParticipantModelScale(ActivePokemon* active_pokemon, f32 scale) {
    active_pokemon->displayObject.scale.x = scale;
    active_pokemon->displayObject.scale.y = scale;
    active_pokemon->displayObject.scale.z = scale;
}

/**
 * Returns how many Pokemon the active Pokemon's trainer brought (teamRoster+0x2).
 * Seen in play (2026-11-13) in the 165-move sweep (Jump Kick, Sing, Hypnosis, Selfdestruct): it
 * returned 6 for both the 1P and the COM side in a six-on-six free battle.
 */
u8 ActivePokemon_GetBroughtCount(ActivePokemon* arg0) {
    return arg0->teamRoster->numberOfPokemonBrought;
}

// FAKE: decomp slop. Raw pointer-offset casts stand in for struct fields.
/**
 * Returns the brought count of the other team member's roster in the session
 * (teamMember[teamMemberIndex == 0]).
 * Not reached in play (2026-11-13): no move in the 165-move battle sweep called it (each move used
 * once, from the command menu to the end of its turn).
 * @unverified Name and comment guessed from the code.
 */
u8 ActivePokemon_GetPartnerBroughtCount(s8 *arg0)
{
  int new_var; // FAKE: permuter temp
  new_var = (*((u8 *) (((s8 *) arg0) + 0x7B7))) == 0;
  return *((u8 *) (((s8 *) (*((s8 **) (((s8 *) ((*((s32 *) (((s8 *) arg0) + 0x85C))) + (new_var * 4))) + 8)))) + 2)); // FAKE: decomp slop, raw pointer casts stand in for struct fields
}

/**
 * Returns 0 if this is side 1's active Pokémon, otherwise 1.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (165 of the moves).
 * @unverified Name from Stadium 1.
 */
s32 BattleScene_GetParticipantSideIndex(ActivePokemon* active_pokemon) {
    if (active_pokemon == sSide1ActivePokemon) {
        return 0;
    }
    return 1;
}

/**
 * Returns the default animation anchor of the move the Pokémon just used, from its side's
 * battle cue table.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (159 of the moves).
 * @unverified Name from Stadium 1.
 */
u8 BattleScene_GetMoveCueDefaultAnchor(ActivePokemon* active_pokemon) {
    UNUSED s32 pad; // FAKE: stack padding
    UNUSED s16 pad2; // FAKE: stack padding
    s16 move_index = active_pokemon->state.runtime.usedMove - 1;
    MovePresentationCue* move_cue = &sSideBattleCues[BattleScene_GetParticipantSideIndex(active_pokemon)]->moveCues[move_index];

    return move_cue->defaultAnchor;
}

/**
 * Returns the alternate animation anchor of the move the Pokémon just used, from its
 * side's battle cue table.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (159 of the moves).
 * @unverified Name from Stadium 1.
 */
u8 BattleScene_GetMoveCueAlternateAnchor(ActivePokemon* active_pokemon) {
    UNUSED s32 pad; // FAKE: stack padding
    UNUSED s16 pad2; // FAKE: stack padding
    s16 move_index = active_pokemon->state.runtime.usedMove - 1;
    MovePresentationCue* move_cue = &sSideBattleCues[BattleScene_GetParticipantSideIndex(active_pokemon)]->moveCues[move_index];

    return move_cue->alternateAnchor;
}

/**
 * Returns the default animation anchor of the side's hit cue.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (127 of the moves).
 * @unverified Name from Stadium 1.
 */
s16 BattleScene_GetHitCueDefaultAnchor(ActivePokemon* active_pokemon) {
    MovePresentationCue* hit_cue = &sSideBattleCues[BattleScene_GetParticipantSideIndex(active_pokemon)]->hitCue;

    return hit_cue->defaultAnchor;
}

/**
 * Returns the alternate anchor of the Pokemon's side hit cue.
 */
s16 func_82107B54(ActivePokemon* active_pokemon) {
    MovePresentationCue* hit_cue = &sSideBattleCues[BattleScene_GetParticipantSideIndex(active_pokemon)]->hitCue;

    return hit_cue->alternateAnchor;
}

extern f32 D_FLT_82189350[][4];

/**
 * BattleAnim_GetSpeciesBaseScale
 *
 * Returns the participant's scaled model width: the table entry for its object
 * type (first float of each 0x10-byte entry of D_FLT_82189350, the same table
 * whose second float func_82107790 reads as a resting height), doubled, divided
 * by 50, times the display object's Y scale. Zero-side relative of the width
 * term used by BattleScene_GetParticipantModelWidth in Stadium 1.
 * Seen in play (2026-11-13) (tour of menus and a COM battle): ran in the battle opening, a switch
 * in battle, running from battle and a Pound turn.
 * @unverified Name was previously used only by callers of this address; the definition was still func_.
 */
f32 BattleAnim_GetSpeciesBaseScale(ActivePokemon* active_pokemon) {
    return ((D_FLT_82189350[active_pokemon->displayObject.objectType][0] * 2) / 50.0f) * active_pokemon->displayObject.scale.y;
}

extern f32 D_FLT_82189350[][4];

/**
 * Returns the model's first size entry from D_FLT_82189350, doubled and divided by 50.
 * No caller in play (2026-11-13): nothing that runs reaches it, not even through callbacks, data
 * tables or fragment headers.
 * @unverified Name and comment guessed from the code.
 */
f32 ActivePokemon_GetSizeRatio(ActivePokemon* active_pokemon) {
    return (D_FLT_82189350[active_pokemon->displayObject.objectType][0] * 2) / 50.0f;
}

/**
 * Returns the Pokemon's move id (+0x820).
 */
u8 func_82107BF4(ActivePokemon* arg0) {
    return arg0->state.runtime.usedMove;
}

extern f32 D_FLT_8218935C[][4];

/**
 * Writes the participant's model size to out: DisplayObject scale (0x30/0x34) times the species
 * size table (D_FLT_8218935C) times 2/50, the same table BattleScene_GetParticipantModelRadiusScaled
 * reads. Was misnamed Trade_UpdateBoxSlotBob, a Stadium 1 trade-machine name.
 * Seen in play (2026-11-13) (tour of menus and a COM battle): ran in the battle opening and a
 * switch in battle.
 * @unverified Named from the code; the sweep hit it but did not check the values.
 */
void BattleScene_GetParticipantModelSizeScaled(ActivePokemon* arg0, Vec3f* out) {
    out->x = arg0->displayObject.scale.x * (D_FLT_8218935C[arg0->displayObject.objectType - 1][0] * 2 / 50.0f);
    out->y = arg0->displayObject.scale.y * (D_FLT_8218935C[arg0->displayObject.objectType - 1][1] * 2 / 50.0f);
    out->z = arg0->displayObject.scale.x * (D_FLT_8218935C[arg0->displayObject.objectType - 1][0] * 2 / 50.0f);
}

/**
 * Copies the Pokémon model's rotation into dest.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (146 of the moves).
 * @unverified Name from Stadium 1.
 */
void BattleScene_GetParticipantModelRotation(ActivePokemon* pokemon, Vec3s* dest) {
    dest->x = pokemon->displayObject.rotation.x;
    dest->y = pokemon->displayObject.rotation.y;
    dest->z = pokemon->displayObject.rotation.z;
}

/**
 * Returns the current HP of the Pokémon's picked-team entry.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (164 of the moves).
 * @unverified Name from Stadium 1.
 */
u16 Battle_GetActiveMonHp(ActivePokemon* active_pokemon) {
    BattleMon* party_pokemon = &active_pokemon->teamRoster->pokemonPicked[active_pokemon->state.rosterIndex];

    return party_pokemon->hp;
}

/**
 * Returns the Pokémon's facing direction (the s32 at 0x60C) as a binary angle, a quarter
 * turn per unit.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (164 of the moves).
 * @unverified Name from Stadium 1.
 */
s16 BattleScene_GetParticipantFacingAngle(ActivePokemon* arg0) {
    return (s16) (arg0->facingDirection << 0xE);
}

/**
 * Returns the species shown by the given side's active Pokémon model.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal or j,
 * no pointer word, no lui/addiu pair in any fragment), so play cannot reach it.
 * @unverified Name from Stadium 1.
 */
s32 BattleAnim_GetSpeciesBySideIndex(s32 side) {
    return sActivePokemon[side]->displayObject.objectType;
}

/**
 * Returns the species shown by the Pokémon's model (its object type, a national dex
 * number).
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (156 of the moves).
 * @unverified Name from Stadium 1.
 */
s32 BattleAnim_GetOwnerSpecies(ActivePokemon* active_pokemon) {
    return active_pokemon->displayObject.objectType;
}

/**
 * Returns the model's visible flag (node flag 1).
 * Not reached in play (2026-11-13): did not run in the 165-move battle sweep (each move used once,
 * from the command menu to the end of its turn) or in a tour of the menus and a COM battle.
 * @unverified Name from Stadium 1.
 */
u8 BattleScene_IsParticipantModelVisible(ActivePokemon* active_pokemon) {
    s32 visible = active_pokemon->displayObject.node.flags & 1;
    return visible;
}

/**
 * Copies the Pokémon model's position into dest.
 * Not reached in play (2026-11-13): did not run in the 165-move battle sweep (each move used once,
 * from the command menu to the end of its turn) or in a tour of the menus and a COM battle.
 * @unverified Name from Stadium 1.
 */
void BattleScene_GetParticipantModelPosition(ActivePokemon* pokemon, Vec3f* dest) {
    dest->x = pokemon->displayObject.position.x;
    dest->y = pokemon->displayObject.position.y;
    dest->z = pokemon->displayObject.position.z;
}

f32 BattleScene_GetParticipantHeight(ActivePokemon*);
/**
 * World point where effects aim at the participant: its position, raised by its
 * height for grounded species, never below its height.
 * Seen in play (2026-11-13) (tour of menus and a COM battle): ran in the battle opening, a switch
 * in battle, running from battle and a Pound turn.
 * @unverified Name and comment guessed from the code.
 */
void BattleScene_GetParticipantAimPoint(ActivePokemon *arg0, u8 *arg1) {
    if (*D_FLT_82189354[arg0->displayObject.objectType] != 0.0f) {
        M2C_FIELD(arg1, f32 *, 0) = (f32) arg0->displayObject.position.x;
        M2C_FIELD(arg1, f32 *, 4) = (f32) arg0->displayObject.position.y;
        M2C_FIELD(arg1, f32 *, 8) = (f32) arg0->displayObject.position.z;
    } else {
        M2C_FIELD(arg1, f32 *, 0) = (f32) arg0->displayObject.position.x;
        M2C_FIELD(arg1, f32 *, 4) = (f32) (BattleScene_GetParticipantHeight(arg0) + arg0->displayObject.position.y);
        M2C_FIELD(arg1, f32 *, 8) = (f32) arg0->displayObject.position.z;
    }
    if (M2C_FIELD(arg1, f32 *, 4) < 0.0f) {
        M2C_FIELD(arg1, f32 *, 4) = BattleScene_GetParticipantHeight(arg0);
    }
}

f32 func_8210791C(ActivePokemon*);
f32 BattleScene_GetParticipantHeight(ActivePokemon*);
/**
 * Like BattleScene_GetParticipantAimPoint, but in screen x (func_8210791C) with z 0.
 * Seen in play (2026-11-13) (tour of menus and a COM battle): ran in a Pound turn.
 * @unverified Name and comment guessed from the code.
 */
void BattleScene_GetParticipantScreenAimPoint(ActivePokemon* active_pokemon, Vec3f* out) {
    if (D_FLT_82189354[active_pokemon->displayObject.objectType][0] != 0.0f) {
        out->x = func_8210791C(active_pokemon);
        out->y = active_pokemon->displayObject.position.y;
        out->z = 0.0f;
    } else {
        out->x = func_8210791C(active_pokemon);
        out->y = BattleScene_GetParticipantHeight(active_pokemon) + active_pokemon->displayObject.position.y;
        out->z = 0.0f;
    }
    if (out->y < 0.0f) {
        out->y = BattleScene_GetParticipantHeight(active_pokemon);
    }
}

/**
 * Writes the Poke Ball's position, raised by 2.5 units, to `arg1`.
 * Seen in play (2026-11-12): ran during ゆけっ！ゲンのすけ, while the Poké Ball for COM's replacement
 * Gengar was in the air (its shadow on the floor), and not before.
 */
void ActivePokemon_GetPokeBallAimPoint(ActivePokemon* arg0, s8 *arg1) {
    M2C_FIELD(arg1, f32 *, 0) = (f32) arg0->pokeBall.position.x;
    M2C_FIELD(arg1, f32 *, 4) = (f32) (arg0->pokeBall.position.y + 2.5f);
    M2C_FIELD(arg1, f32 *, 8) = (f32) arg0->pokeBall.position.z;
}

extern f32 D_FLT_82189350[][4];

/**
 * BattleScene_GetParticipantHeight
 *
 * Returns the table width (first float of the object type's entry in
 * D_FLT_82189350) unscaled when modelTransformId is 0x10, otherwise the same
 * width times the display object's Y scale. What transform 0x10 is has not been
 * established; the value is used literally here.
 * Seen in play (2026-11-13) (tour of menus and a COM battle): ran in the battle opening, a switch
 * in battle, running from battle and a Pound turn.
 * @unverified Name guessed from the code; comment kept.
 */
f32 BattleScene_GetParticipantHeight(ActivePokemon* active_pokemon) {
    if (active_pokemon->modelTransformId == 0x10) {
        return D_FLT_82189350[active_pokemon->displayObject.objectType][0];
    }
    return D_FLT_82189350[active_pokemon->displayObject.objectType][0] * active_pokemon->displayObject.scale.y;
}

extern f32 D_FLT_8218934C[][4];
/**
 * Seen in play (2026-11-13) (tour of menus and a COM battle): ran in the battle opening, a switch
 * in battle, running from battle and a Pound turn.
 * @unverified Name was previously used only by callers of this address; the definition was still func_.
 */
f32 BattleScene_GetParticipantModelRadiusScaled(ActivePokemon* active_pokemon) {
    return D_FLT_8218934C[active_pokemon->displayObject.objectType][0] * active_pokemon->displayObject.scale.y;
}

/**
 * Returns node node_index of the model loaded for the Pokémon's session team.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (2 of the moves).
 * @unverified Name from Stadium 1.
 */
ModelNodeView* Battle_GetLoadedModelNode(ActivePokemon* active_pokemon, s32 node_index) {
    return active_pokemon->sessionTeams->loadedModel->unk_00[2]->unk_00[node_index];
}

/**
 * Returns the session's display model id (sessionTeams+0x2).
 * Seen in play (2026-11-13) (tour of menus and a COM battle): ran in the battle opening and a
 * switch in battle.
 * @unverified Name and comment guessed from the code.
 */
s16 ActivePokemon_GetDisplayModel(ActivePokemon* arg0, M2C_UNK arg1) {
    return arg0->sessionTeams->displayModel;
}

typedef struct {
    /* 0x0 */ s32 unk_00;
    /* 0x4 */ s32 unk_04;
    /* 0x8 */ s32 unk_08;
} unk_D_8006A9CC; // size = 0xC
extern unk_D_8006A9CC D_8006A9CC[];

/**
 * Returns the name string of the Pokemon's current move (move cache byte at 0x80A).
 */
s32 ActivePokemon_GetMoveName(u8* arg0) {
    return D_8006A9CC[arg0[0x80A]].unk_00;
}

// FAKE: decomp slop. Raw pointer-offset casts stand in for struct fields.
/**
 * Returns the nickname (+0x30 in BattleMon) of this Pokemon in the roster of the teammate named by state.replacementState.
 * Seen in play (2026-11-12): for 1P's Nidoqueen it returned the string ニドニド, the nickname shown on
 * its HUD.
 */
s32 ActivePokemon_GetNickname(s8 *arg0)
{
  unsigned int new_var; // FAKE: permuter temp
  return ((*((s32 *) (((s8 *) ((*((s32 *) (((s8 *) arg0) + 0x85C))) + ((*((u8 *) (((s8 *) arg0) + 0x7B9))) * 4))) + 8))) + ((*((s32 *) (((s8 *) arg0) + 0x794))) * 0x50)) + (new_var = 0x4C); // FAKE: decomp slop, raw pointer casts stand in for struct fields
}

/**
 * Creates the participant's owner (trainer) model.
 * Seen in play (2026-11-13) ran during the opening of a COM Free Battle, before the first command
 * menu.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
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

/**
 * Creates the participant's two hidden secondary models.
 * ^?????? this annotation seems like a hallucination
 * Seen in play (2026-11-13) ran during the opening of a COM Free Battle, before the first command
 * menu.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void BattleScene_InitializeParticipantSecondaryModels(ActivePokemon* pokemon, s32* secondary_models) {
    ModelNodeView* model_node;
    s16 object_type;
    s32 i;
    PokemonAfterimage* afterimage;
    model_node = Battle_GetLoadedModelNode(pokemon, 0);
    object_type = ActivePokemon_GetDisplayModel((s8*)pokemon, 0);
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
void ActivePokemon_LoadSpeciesModelAssets(ActivePokemon*);
/**
 * Creates and positions the participant's Pokemon model and loads its
 * presentation data.
 * Seen in play (2026-11-13) ran during the opening of a COM Free Battle, before the first command
 * menu.
 * @unverified Name was previously used only by callers of this address; the definition was still func_. Comment from Stadium 1.
 */
void BattleScene_InitializeParticipantModel(ActivePokemon* active_pokemon) {
    s32 side;
    UNUSED s32 pad; // FAKE: stack padding
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
    ActivePokemon_LoadSpeciesModelAssets(active_pokemon);
    ModelAnim_SetAnimation(&active_pokemon->displayObject, 0);
    ModelAnim_SetFrame(&active_pokemon->displayObject, 0);

    active_pokemon->sessionTeams->displayMon = &active_pokemon->teamRoster->pokemonPicked[active_pokemon->state.rosterIndex];
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
    func_8000D41C(&M2C_FIELD(active_pokemon, Vec3f*, 0x5DC), active_pokemon->facingDirection * D_82199DF0[side][0], D_82199DF0[side][1], D_82199DF0[side][2]);
}

/**
 * Creates the participant's hidden auxiliary model (model 154).
 * Seen in play (2026-11-13) ran during the opening of a COM Free Battle, before the first command
 * menu.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
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

/**
 * Reloads pokemon's model as object_type using owner's loaded model: picks the effect slot
 * by side, loads the species assets, resets the animation, hides Diglett and Dugtrio's
 * ground layer flag, and unless airborne puts the model back in place facing the other
 * side. Diglett is not in Zero's battle roster, so only the Dugtrio case comes up in
 * normal play.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (2 of the moves).
 * @unverified Name from Stadium 1.
 */
void BattleScene_ReinitParticipantBodyModel(ActivePokemon* owner, ActivePokemon* pokemon, s16 object_type) {
    UNUSED s32 pad; // FAKE: stack padding
    ModelNodeView* model_node = Battle_GetLoadedModelNode(owner, 0);
    s32 side = BattleScene_GetParticipantSideIndex(owner);
    UNUSED s32 pad2; // FAKE: stack padding

    ModelRenderer_ClearDisplayObject(&pokemon->displayObject);

    if (owner == sActivePokemon[0]) {
        pokemon->displayObject.effectSlot = 0;
    } else {
        pokemon->displayObject.effectSlot = 1;
    }

    Model_InitDisplayObject(&pokemon->displayObject, 0, object_type, model_node);
    ActivePokemon_LoadSpeciesModelAssets(owner);
    ModelAnim_SetFrame(&pokemon->displayObject, 0);
    ModelAnim_SetAnimation(&pokemon->displayObject, 0);

    owner->sessionTeams->displayMon = &owner->teamRoster->pokemonPicked[owner->state.rosterIndex];
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
    func_8000D41C(&M2C_FIELD(owner, Vec3f*, 0x5DC), owner->facingDirection * D_82199DF0[side][0], D_82199DF0[side][1], D_82199DF0[side][2]);
}

/**
 * Reloads the Pokémon's thumbnail model as object_type, using effect slot 2 or 3 and model
 * slot 1 or 2 depending on side.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (1 of the moves).
 * @unverified Name from Stadium 1.
 */
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

/**
 * Reloads the Pokémon's three afterimage models as object_type and hides them.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (2 of the moves).
 * @unverified Name from Stadium 1.
 */
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

/**
 * Clears the model's event track, or for a sleeping Pokémon sets the sleep event track.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (2 of the moves).
 * @unverified Name from Stadium 1.
 */
void Battle_ResetEventTrack(ActivePokemon* active_pokemon) {
    if (active_pokemon->state.flags & ACTIVE_SLEEP) {
        BattleAnim_TrySetModelEventTrackFromRow(active_pokemon, 0xAF, 2);
    } else {
        active_pokemon->state.modelEventTrackState = 0;
        ModelAnim_SetEventFrame(&active_pokemon->displayObject, 0);
        ModelAnim_SetEventTrack(&active_pokemon->displayObject, -1);
    }
}

/**
 * Reloads the Pokémon's body, thumbnail and afterimage models for the species it should
 * show, resets its event track, keeps only the substitute presentation flags and resets
 * its scale.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (1 of the moves).
 * @unverified Name from Stadium 1.
 */
void Battle_LoadOwnerModelForSpecies(ActivePokemon* active_pokemon) {
    ActivePokemonState* state = &active_pokemon->state;
    UNUSED s32 pad[3]; // FAKE: stack padding
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

/**
 * Same as Battle_LoadOwnerModelForSpecies, and also clears state field unk_2D. Used when
 * the Pokémon is sent out.
 * Not reached in play (2026-11-13): did not run in the 165-move battle sweep (each move used once,
 * from the command menu to the end of its turn) or in a tour of the menus and a COM battle.
 * @unverified Name from Stadium 1.
 */
void Battle_LoadOwnerModelForSwitchIn(ActivePokemon* active_pokemon) {
    ActivePokemonState* state = &active_pokemon->state;
    UNUSED s32 pad[3]; // FAKE: stack padding
    s16 object_type;

    Battle_GetLoadedModelNode(active_pokemon, 0);
    object_type = Battle_GetDisplayModelId(active_pokemon, 0);
    func_8210840C(active_pokemon, active_pokemon, object_type);
    BattleScene_ReinitParticipantThumbnailModel(active_pokemon, &active_pokemon->thumbnail, object_type);
    func_82108648(active_pokemon, object_type);
    Battle_ResetEventTrack(active_pokemon);
    state->faintState = 0;
    state->flags &= 0x3800;
    Vec3f_SetComponentsDuplicate(&active_pokemon->displayObject.scale, 1.0f, 1.0f, 1.0f);
}

/**
 * Swaps the Pokémon's model for the Substitute doll at full alpha, remembering the species
 * model it had.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (1 of the moves).
 * @unverified Name from Stadium 1.
 */
void Battle_ResetOwnerModelToSubstituteDoll(ActivePokemon* active_pokemon) {
    Model_SetMaterialColor(&active_pokemon->displayObject, 0xFF, 0xFF, 0xFF, active_pokemon->state.alpha = 0xFF);
    active_pokemon->state.model = active_pokemon->displayObject.objectType;
    func_8210840C(active_pokemon, active_pokemon, SUBSTITUTE_DOLL);
    func_82108648(active_pokemon, SUBSTITUTE_DOLL);
    Battle_ResetEventTrack(active_pokemon);
}

/**
 * Reloads the Substitute doll model for the Pokémon.
 * Not reached in play (2026-11-13): did not run in the 165-move battle sweep (each move used once,
 * from the command menu to the end of its turn) or in a tour of the menus and a COM battle.
 * @unverified Name from Stadium 1.
 */
void Battle_ReloadSubstituteDoll(ActivePokemon* active_pokemon) {
    func_8210840C(active_pokemon, active_pokemon, SUBSTITUTE_DOLL);
    func_82108648(active_pokemon, SUBSTITUTE_DOLL);
    Battle_ResetEventTrack(active_pokemon);
}

/**
 * Reloads the Pokémon's species model at full alpha (used after Substitute ends).
 * Not reached in play (2026-11-13): did not run in the 165-move battle sweep (each move used once,
 * from the command menu to the end of its turn) or in a tour of the menus and a COM battle.
 * @unverified Name from Stadium 1.
 */
void Battle_ReloadDisplayModel(ActivePokemon* active_pokemon) {
    UNUSED s32 pad[3]; // FAKE: stack padding
    ActivePokemonState* state = &active_pokemon->state;
    s16 object_type = Battle_GetDisplayModelId(active_pokemon, 0);

    state->alpha = 0xFF;
    Model_SetMaterialColor(&active_pokemon->displayObject, 0xFF, 0xFF, 0xFF, state->alpha);
    func_8210840C(active_pokemon, active_pokemon, object_type);
    func_82108648(active_pokemon, object_type);
    Battle_ResetEventTrack(active_pokemon);
}

/**
 * Sets the model transform id and its timer.
 * Seen in play (2026-11-13) (tour of menus and a COM battle): ran in the battle opening, a switch
 * in battle and a Pound turn.
 * @unverified Name and comment guessed from the code.
 */
void ActivePokemon_SetModelTransform(ActivePokemon* arg0, s32 arg1, s32 arg2) {
    arg0->modelTransformId = arg1;
    arg0->modelTransformTimer = arg2;
}

/**
 * Once the animated model's current animation finishes, starts its idle animation again:
 * the flying idle when airborne, the sleep idle for sleeping Primeape and Exeggutor, a
 * random one of five for Ditto, otherwise the normal idle. Does nothing while underground,
 * frozen or while the session is busy.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (165 of the moves).
 * @unverified Name from Stadium 1.
 */
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
    if (!(pokemon_state->flags & (ACTIVE_UNDERGROUND | ACTIVE_FREEZE))) {
        if ((BattleAnim_IsSessionBusy(active_pokemon) == 0) && (animated_pokemon->displayObject.transformAnim.animationId != -1) &&
            (ModelAnim_IsFinished(&animated_pokemon->displayObject) == 1)) {
            if (pokemon_state->flags & ACTIVE_AIRBORNE) {
                ModelAnim_SetAnimation(&animated_pokemon->displayObject, flying_cue->id);
            } else if ((pokemon_state->flags & ACTIVE_SLEEP) && ((animated_pokemon->displayObject.objectType == PRIMEAPE) || (animated_pokemon->displayObject.objectType == EXEGGUTOR))) {
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

/**
 * Starts the Pokémon's idle animation right away, picking it like
 * Battle_ReturnToIdleAnimIfFinished.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (164 of the moves).
 * @unverified Name from Stadium 1.
 */
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

    if (!(state->flags & (ACTIVE_UNDERGROUND | ACTIVE_FREEZE)) && (BattleAnim_IsSessionBusy(active_pokemon) == 0) && (active_pokemon->displayObject.transformAnim.animationId != -1)) {
        if (state->flags & ACTIVE_AIRBORNE) {
            ModelAnim_SetAnimation(&active_pokemon->displayObject, *flying_idle_cue);
        } else if ((state->flags & ACTIVE_SLEEP) && ((active_pokemon->displayObject.objectType == PRIMEAPE) || (active_pokemon->displayObject.objectType == EXEGGUTOR))) {
            ModelAnim_SetAnimation(&active_pokemon->displayObject, *sleep_idle_cue);
        } else if (active_pokemon->displayObject.objectType == DITTO) {
            ModelAnim_SetAnimation(&active_pokemon->displayObject, BattleAnim_RandomRange(5) + 13);
        } else {
            ModelAnim_SetAnimation(&active_pokemon->displayObject, *idle_cue);
        }
        ModelAnim_SetFrame(&active_pokemon->displayObject, 0);
    }
}

/**
 * Starts the Pokémon's hit animation from its first frame.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal or j,
 * no pointer word, no lui/addiu pair in any fragment), so play cannot reach it.
 * @unverified Name from Stadium 1.
 */
void Battle_SetModelToHitAnim(ActivePokemon* active_pokemon) {
    extern PokemonBattleCues* D_82189180[];
    MovePresentationCue* hit_cue = &D_82189180[BattleScene_GetParticipantSideIndex(active_pokemon)]->hitCue;

    if (active_pokemon->displayObject.transformAnim.animationId != -1) {
        ModelAnim_SetFrame(&active_pokemon->displayObject, 0);
        ModelAnim_SetAnimation(&active_pokemon->displayObject, hit_cue->id);
    }
}

/**
 * Points teamRoster at sessionTeams->teamMember[index].
 * Seen in play (2026-11-12): picked Onix's roster entry when it was switched in.
 */
void ActivePokemon_SelectTeamRoster(ActivePokemon* arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0x860) = (s32) M2C_FIELD((M2C_FIELD(arg0, s32 *, 0x85C) + (arg1 * 4)), s32 *, 8);
}

/**
 * Sets state.teamMemberIndex.
 * Seen in play (2026-11-12): set the switched-in team member (Onix).
 */
void ActivePokemon_SetTeamMemberIndex(ActivePokemon* arg0, s32 arg1) {
    M2C_FIELD(arg0, s8 *, 0x7B7) = arg1;
}

/**
 * Sets state.controller, the controller that drives this Pokemon's menu.
 * Seen in play (2026-11-13) in a Free Battle switch (1P switched to its second Pokémon) it ran when
 * B opened the Pokémon menu.
 * @unverified Name and comment guessed from the code.
 */
void ActivePokemon_SetController(ActivePokemon* arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0x858) = arg1;
}

/**
 * Sets state.replacementState.
 * Seen in play (2026-11-13) ran during the opening of a COM Free Battle, before the first command
 * menu.
 * @unverified Name and comment guessed from the code.
 */
void ActivePokemon_SetReplacementState(ActivePokemon* arg0, s32 arg1) {
    M2C_FIELD(arg0, s8 *, 0x7B9) = arg1;
}

/**
 * Binds the Pokémon slot to team member team_member_index and remembers its roster and
 * team member indexes.
 * Not reached in play (2026-11-13): did not run in the 165-move battle sweep (each move used once,
 * from the command menu to the end of its turn) or in a tour of the menus and a COM battle.
 * @unverified Name from Stadium 1.
 */
void BattleScene_RebindParticipantTeamMember(ActivePokemon* pokemon, s32 team_member_index) {
    ActivePokemonState* state = &pokemon->state;

    BattleScene_BindParticipantTeamRoster(pokemon, team_member_index);
    BattleScene_SetParticipantTeamMember(pokemon, team_member_index);
    pokemon->thumbnail.shownRosterIndex = state->rosterIndex;
    pokemon->thumbnail.shownTeamMemberIndex = state->teamMemberIndex;
}

/**
 * Freeze Clause check: returns 1 if a Pokémon on the trainer's team (or, in a two-trainer
 * team, the partner's) is already frozen. Each check also needs the runtime roster entry
 * for the active Pokémon's slot to be 0.
 * Not reached in play (2026-11-13): did not run in the 165-move battle sweep (each move used once,
 * from the command menu to the end of its turn) or in a tour of the menus and a COM battle.
 * @unverified Name from Stadium 1.
 */
s32 Battle_FreezeClauseInEffect(ActivePokemon* active_pokemon) {
    s32 i;
    ActivePokemonState* state;
    BattleMon* pokemon;

    state = &active_pokemon->state;

    for (i = 0; i < BattleScene_GetTeamMemberTeamSize(active_pokemon); i++) {
        pokemon = &active_pokemon->teamRoster->pokemonPicked[i];
        if ((pokemon->statusCondition & STATUS_FREEZE) && (active_pokemon->state.runtime.restSleepTurns[state->rosterIndex + state->teamMemberIndex * 3] == 0)) {
            return 1;
        }
    }

    if (active_pokemon->sessionTeams->tagTeamSize == 2) {
        for (i = 0; i < BattleScene_GetPartnerTeamSize(active_pokemon); i++) {
            pokemon = &active_pokemon->sessionTeams->teamMember[state->teamMemberIndex == 0]->pokemonPicked[i];
            if ((pokemon->statusCondition & STATUS_FREEZE) &&
                (active_pokemon->state.runtime.restSleepTurns[state->rosterIndex + (state->teamMemberIndex == 0) * 3] == 0)) {
                return 1;
            }
        }
    }

    return 0;
}

/**
 * Sleep Clause check: returns 1 if a Pokémon on the trainer's team (or, in a two-trainer
 * team, the partner's) is already asleep. Each check also needs the runtime roster entry
 * for the active Pokémon's slot to be 0.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (5 of the moves).
 * @unverified Name from Stadium 1.
 */
s32 Battle_SleepClauseInEffect(ActivePokemon* active_pokemon) {
    s32 i;
    ActivePokemonState* state;
    BattleMon* pokemon;

    state = &active_pokemon->state;

    for (i = 0; i < BattleScene_GetTeamMemberTeamSize(active_pokemon); i++) {
        pokemon = &active_pokemon->teamRoster->pokemonPicked[i];
        if ((pokemon->statusCondition & STATUS_SLEEP_MASK) && (active_pokemon->state.runtime.restSleepTurns[state->rosterIndex + state->teamMemberIndex * 3] == 0)) {
            return 1;
        }
    }

    if (active_pokemon->sessionTeams->tagTeamSize == 2) {
        for (i = 0; i < BattleScene_GetPartnerTeamSize(active_pokemon); i++) {
            pokemon = &active_pokemon->sessionTeams->teamMember[state->teamMemberIndex == 0]->pokemonPicked[i];
            if ((pokemon->statusCondition & STATUS_SLEEP_MASK) && (active_pokemon->state.runtime.restSleepTurns[state->rosterIndex + (state->teamMemberIndex == 0) * 3] == 0)) {
                return 1;
            }
        }
    }
    return 0;
}
