/* Fixed-layout split; original translation-unit boundaries remain unconfirmed. */
#include "battle.h"

// Declared here instead of in a header: the callers of these disagree on their types.
void func_821020FC(ActivePokemon*);
void func_8210211C(ActivePokemon* active_pokemon);

/**
 * Resets the scene's model-reload step to 0.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (164 of the moves).
 * @unverified Name guessed from the code.
 */
void BattleScene_ResetAnimationStep(void) {
    sBattleScene.scene->modelReloadStep = 0;
}

/**
 * Model reload for a Pokemon with state flag 0x2000 (not while moveEffectKind is 0x19):
 * step 0 marks the model pending, step 1 waits for the reload bit (0x10), clears 0x90 and
 * reloads the model. Returns 1 while in progress.
 */
s32 func_82124A50(ActivePokemon* arg0) {
    UNUSED s32 pad[2]; // FAKE: stack padding
    s32 sp1C = 0;

    if (!(arg0->state.flags & 0x2000)) {
        return 0;
    }

    if (sBattleScene.scene->moveEffectKind == 0x19) {
        return 0;
    }

    switch (sBattleScene.scene->modelReloadStep) {
        case 0:
            func_8210211C(arg0);
            sp1C = 1;
            sBattleScene.scene->modelReloadStep++;
            break;

        case 1:
            sp1C = 1;
            if (arg0->sessionTeams->modelFlags & 0x10) {
                arg0->sessionTeams->modelFlags &= ~0x90;
                func_82108A0C(arg0);
                sBattleScene.scene->modelReloadStep++;
            }
            break;

        case 2:
            break;
    }
    return sp1C;
}

/**
 * Steps the model reload for one Pokemon whose state flag 0x2000 is set: step 0 starts the
 * reload, step 1 waits for the Substitute bit (0x10) in its team status flags, clears 0x90 and
 * reloads the doll. Returns 1 while the reload is still in progress.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (134 of the moves).
 * @unverified Name guessed from the code.
 */
s32 BattleScene_AdvanceOwnerAnimation98(ActivePokemon* arg0) {
    UNUSED s32 pad[2]; // FAKE: stack padding
    s32 sp1C = 0;

    if (!(arg0->state.flags & 0x2000)) {
        return 0;
    }

    switch (sBattleScene.scene->modelReloadStep) {
        case 0:
            func_821020FC(arg0);
            sp1C = 1;
            sBattleScene.scene->modelReloadStep++;
            break;

        case 1:
            sp1C = 1;
            if (arg0->sessionTeams->modelFlags & 0x10) {
                arg0->sessionTeams->modelFlags &= ~0x90;
                Battle_ReloadSubstituteDoll(arg0);
                sBattleScene.scene->modelReloadStep++;
            }
            break;

        case 2:
            break;
    }
    return sp1C;
}

/**
 * Same as func_82124A50 for state flag 0x1000.
 */
s32 func_82124BF8(ActivePokemon* arg0) {
    UNUSED s32 pad[2]; // FAKE: stack padding
    s32 sp1C = 0;

    if (!(arg0->state.flags & 0x1000)) {
        return 0;
    }

    switch (sBattleScene.scene->modelReloadStep) {
        case 0:
            func_8210211C(arg0);
            sp1C = 1;
            sBattleScene.scene->modelReloadStep++;
            break;

        case 1:
            sp1C = 1;
            if (arg0->sessionTeams->modelFlags & 0x10) {
                arg0->sessionTeams->modelFlags &= ~0x90;
                func_82108A0C(arg0);
                Battle_ClearRuntimeFlags(arg0, 0x3800);
                sBattleScene.scene->modelReloadStep++;
            }
            break;

        case 2:
            break;
    }
    return sp1C;
}


/**
 * Same model-reload steps as BattleScene_AdvanceOwnerAnimation98, run for side 0 and then
 * side 1 (each only if its flag 0x2000 is set). Runs only when scene field unk_44 is 1.
 * Returns 1 while a reload is still in progress.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (164 of the moves).
 * @unverified Name guessed from the code.
 */
s32 BattleScene_AdvanceBothOwnerAnimations(void) {
    UNUSED s32 pad[2]; // FAKE: stack padding
    s32 sp1C = 0;
    ActivePokemonState* temp_a1 = &sActivePokemon[0]->state;
    ActivePokemonState* temp_a2 = &sActivePokemon[1]->state;

    if (sBattleScene.scene->unk_44 != 1) {
        return 0;
    }

    if (!(temp_a1->flags & 0x2000) && !(temp_a2->flags & 0x2000)) {
        return 0;
    }

    switch (sBattleScene.scene->modelReloadStep) {
        case 0:
            if (temp_a1->flags & 0x2000) {
                func_821020FC(sActivePokemon[0]);
            }
            sp1C = 1;
            sBattleScene.scene->modelReloadStep = sBattleScene.scene->modelReloadStep + 1;
            break;

        case 1:
            sp1C = 1;
            if (temp_a1->flags & 0x2000) {
                if (sActivePokemon[0]->sessionTeams->modelFlags & 0x10) {
                    sActivePokemon[0]->sessionTeams->modelFlags &= ~0x90;
                    func_821089D0(sActivePokemon[0]);
                    sBattleScene.scene->modelReloadStep += 1;
                }
            } else {
                sBattleScene.scene->modelReloadStep = sBattleScene.scene->modelReloadStep + 1;
            }
            break;

        case 2:
            if (temp_a2->flags & 0x2000) {
                func_821020FC(sActivePokemon[1]);
            }
            sp1C = 1;
            sBattleScene.scene->modelReloadStep = sBattleScene.scene->modelReloadStep + 1;
            break;

        case 3:
            sp1C = 1;
            if (temp_a2->flags & 0x2000) {
                if (sActivePokemon[1]->sessionTeams->modelFlags & 0x10) {
                    sActivePokemon[1]->sessionTeams->modelFlags &= ~0x90;
                    func_821089D0(sActivePokemon[1]);
                    sBattleScene.scene->modelReloadStep += 1;
                }
            } else {
                sBattleScene.scene->modelReloadStep = sBattleScene.scene->modelReloadStep + 1;
            }
            break;

        case 4:
            break;
    }

    return sp1C;
}
