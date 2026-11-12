/* Fixed-layout split; original translation-unit boundaries remain unconfirmed. */
#include "battle_engine_309ED0.h"

void BattleScene_ResetAnimationStep(void) {
    sBattleScene.scene->modelReloadStep = 0;
}

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
            if (arg0->sessionTeams->uniqueStatusFlags & 0x10) {
                arg0->sessionTeams->uniqueStatusFlags &= ~0x90;
                func_82108A0C(arg0);
                sBattleScene.scene->modelReloadStep++;
            }
            break;

        case 2:
            break;
    }
    return sp1C;
}

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
            if (arg0->sessionTeams->uniqueStatusFlags & 0x10) {
                arg0->sessionTeams->uniqueStatusFlags &= ~0x90;
                Battle_ReloadSubstituteDoll(arg0);
                sBattleScene.scene->modelReloadStep++;
            }
            break;

        case 2:
            break;
    }
    return sp1C;
}

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
            if (arg0->sessionTeams->uniqueStatusFlags & 0x10) {
                arg0->sessionTeams->uniqueStatusFlags &= ~0x90;
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
                if (sActivePokemon[0]->sessionTeams->uniqueStatusFlags & 0x10) {
                    sActivePokemon[0]->sessionTeams->uniqueStatusFlags &= ~0x90;
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
                if (sActivePokemon[1]->sessionTeams->uniqueStatusFlags & 0x10) {
                    sActivePokemon[1]->sessionTeams->uniqueStatusFlags &= ~0x90;
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
