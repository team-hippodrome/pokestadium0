/* Stadium Zero fragment007_166580, second object (starts at 0x82008C40). */

#include "global.h"
#include "m2c_macros.h"
#include "free_battle_setup.h"
#include "game_state.h"

typedef struct { u8 b[9]; } Bytes9;
extern u8 D_8200AC30[];
s32 GbSave_GetTrainerId(s32 arg0);
s32 func_80020AFC(s32, s32, s32, s32);
u8 func_80020CE4(void*, s32, s32);
void func_80020C60(s32);
void func_80022D84(s32, void*);
void func_80058410(void*, void*, s32);
void func_8000A460(void*, void*);

/**
 * Fills the trainer slot `slot` and its roster info `info` for a human player on controller
 * `controllerPort` whose team comes from the GB cart in port `gbPort`: isHuman 1, the controller,
 * the trainer ID and name from that save, and up to six Pokémon read from the save's party
 * (Deck_Open(0x20, gbPort)). `info` gets the counts, gbPort as trainerIndex (the VS screen picture),
 * the 9-byte title D_8200AC30 and a copy of the party.
 * The pointers are recomputed at each use; keeping them in locals changes the stack frame.
 * Not reached in play: only FreeBattle_BuildGbCartSides calls it (see FreeBattle_SetupGbCartVersus).
 * @unverified Name from the code.
 */
void FreeBattle_LoadGbCartTrainer(TeamRoster* arg0, ExtendedRosterInfo* arg1, s32 arg2, s32 arg3) {
    s32 sp2C;

    arg0->isHuman = 1;
    arg0->controllerPort = arg2;
    arg0->controller = &gControllers[arg2];
    arg0->trainerId = GbSave_GetTrainerId(arg3);
    arg0->numberOfPokemonBrought = 0;
    arg0->rosterInfo = arg1;
    sp2C = func_80020AFC(0x20, arg3, 0, 0);
    arg0->numberOfPokemonBrought = func_80020CE4(arg0->pokemonPicked, 6, sp2C);
    func_80020C60(sp2C);
    func_80022D84(arg3, arg0->trainerName);
    arg1->unk_000 = 0;
    arg1->numberOfPokemonCanBePicked = arg0->numberOfPokemonBrought;
    arg1->trainerIndex = arg3;
    func_80058410(arg0->pokemonPicked, arg1->battleMon, 0x1E0);
    *(Bytes9*)arg1->title = *(Bytes9*)D_8200AC30;
    func_8000A460(arg1->fullName, arg0->trainerName);
}

/**
 * Clears a BattleSide: no models, no team members, no background files.
 * Not reached in play: only FreeBattle_BuildGbCartSides calls it (see FreeBattle_SetupGbCartVersus).
 * @unverified Name from the code.
 */
void FreeBattle_ClearBattleSide(BattleSide* arg0) {
    arg0->modelFlags = 0;
    arg0->tagTeamSize = 0;
    arg0->displayModel = 0;
    arg0->displayMon = NULL;
    arg0->loadedModel = NULL;
    arg0->teamMember[0] = NULL;
    arg0->teamMember[1] = NULL;
    arg0->backgroundLoadFlags = 0;
    arg0->backgroundFileList = 0;
}

/**
 * Builds gSessionContext's four trainer slots from GB carts: each argument is a one-based port
 * (0 for none), and a slot is filled (FreeBattle_LoadGbCartTrainer with port - 1 as both
 * controller and GB port) only when it is greater than 0. Slots 0 and 1 join battleSides[0],
 * slots 2 and 3 battleSides[1]; both sides are cleared first and every slot's isHuman is cleared.
 * Not reached in play: only FreeBattle_SetupGbCartVersus calls it.
 * @unverified Name from the code.
 */
void FreeBattle_BuildGbCartSides(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 temp;

    FreeBattle_ClearBattleSide(&gSessionContext.battleSides[0]);
    FreeBattle_ClearBattleSide(&gSessionContext.battleSides[1]);
    gSessionContext.trainerSlots[0].isHuman = 0;
    gSessionContext.trainerSlots[1].isHuman = 0;
    gSessionContext.trainerSlots[2].isHuman = 0;
    gSessionContext.trainerSlots[3].isHuman = 0;
    if (arg0 > 0) {
        temp = arg0 - 1;
        FreeBattle_LoadGbCartTrainer(&gSessionContext.trainerSlots[0], &gSessionContext.rosterInfo[0], temp, temp);
        gSessionContext.battleSides[0].teamMember[gSessionContext.battleSides[0].tagTeamSize] = &gSessionContext.trainerSlots[0];
        gSessionContext.battleSides[0].tagTeamSize = gSessionContext.battleSides[0].tagTeamSize + 1;
    }
    if (arg1 > 0) {
        temp = arg1 - 1;
        FreeBattle_LoadGbCartTrainer(&gSessionContext.trainerSlots[1], &gSessionContext.rosterInfo[1], temp, temp);
        gSessionContext.battleSides[0].teamMember[gSessionContext.battleSides[0].tagTeamSize] = &gSessionContext.trainerSlots[1];
        gSessionContext.battleSides[0].tagTeamSize = gSessionContext.battleSides[0].tagTeamSize + 1;
    }
    if (arg2 > 0) {
        temp = arg2 - 1;
        FreeBattle_LoadGbCartTrainer(&gSessionContext.trainerSlots[2], &gSessionContext.rosterInfo[2], temp, temp);
        gSessionContext.battleSides[1].teamMember[gSessionContext.battleSides[1].tagTeamSize] = &gSessionContext.trainerSlots[2];
        gSessionContext.battleSides[1].tagTeamSize = gSessionContext.battleSides[1].tagTeamSize + 1;
    }
    if (arg3 > 0) {
        temp = arg3 - 1;
        FreeBattle_LoadGbCartTrainer(&gSessionContext.trainerSlots[3], &gSessionContext.rosterInfo[3], temp, temp);
        gSessionContext.battleSides[1].teamMember[gSessionContext.battleSides[1].tagTeamSize] = &gSessionContext.trainerSlots[3];
        gSessionContext.battleSides[1].tagTeamSize = gSessionContext.battleSides[1].tagTeamSize + 1;
    }
}

M2C_UNK func_80021894(M2C_UNK);                     /* extern */
void FreeBattle_BuildGbCartSides(s32, s32, s32, s32);

/**
 * Loads the GB saves on ports 1 and 2 and builds a 1P (port 1) vs 2P (port 2) battle from the
 * teams on those carts, skipping the setup screen.
 * Not reached in play: FreeBattle_Main calls it only for `mode` 1, and both callers of the
 * fragment pass 0. A leftover quick-start path.
 * @unverified Name from the code.
 */
void FreeBattle_SetupGbCartVersus(void) {
    func_80021894(0);
    func_80021894(1);
    FreeBattle_BuildGbCartSides(1, 0, 2, 0);
}
