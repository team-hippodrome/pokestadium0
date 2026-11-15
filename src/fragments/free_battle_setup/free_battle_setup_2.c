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
void GbSave_GetPlayerName(s32, void*);
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
void FreeBattle_LoadGbCartTrainer(TeamRoster* slot, ExtendedRosterInfo* info, s32 controllerPort, s32 gbPort) {
    s32 sp2C;

    slot->isHuman = 1;
    slot->controllerPort = controllerPort;
    slot->controller = &gControllers[controllerPort];
    slot->trainerId = GbSave_GetTrainerId(gbPort);
    slot->numberOfPokemonBrought = 0;
    slot->rosterInfo = info;
    sp2C = func_80020AFC(0x20, gbPort, 0, 0);
    slot->numberOfPokemonBrought = func_80020CE4(slot->pokemonPicked, 6, sp2C);
    func_80020C60(sp2C);
    GbSave_GetPlayerName(gbPort, slot->trainerName);
    info->unk_000 = 0;
    info->numberOfPokemonCanBePicked = slot->numberOfPokemonBrought;
    info->trainerIndex = gbPort;
    func_80058410(slot->pokemonPicked, info->battleMon, 0x1E0);
    *(Bytes9*)info->title = *(Bytes9*)D_8200AC30;
    func_8000A460(info->fullName, slot->trainerName);
}

/**
 * Clears a BattleSide: no models, no team members, no background files.
 * Not reached in play: only FreeBattle_BuildGbCartSides calls it (see FreeBattle_SetupGbCartVersus).
 * @unverified Name from the code.
 */
void FreeBattle_ClearBattleSide(BattleSide* side) {
    side->modelFlags = 0;
    side->tagTeamSize = 0;
    side->displayModel = 0;
    side->displayMon = NULL;
    side->loadedModel = NULL;
    side->teamMember[0] = NULL;
    side->teamMember[1] = NULL;
    side->backgroundLoadFlags = 0;
    side->backgroundFileList = 0;
}

/**
 * Builds gSessionContext's four trainer slots from GB carts: each argument is a one-based port
 * (0 for none), and a slot is filled (FreeBattle_LoadGbCartTrainer with port - 1 as both
 * controller and GB port) only when it is greater than 0. Slots 0 and 1 join battleSides[0],
 * slots 2 and 3 battleSides[1]; both sides are cleared first and every slot's isHuman is cleared.
 * Not reached in play: only FreeBattle_SetupGbCartVersus calls it.
 * @unverified Name from the code.
 */
void FreeBattle_BuildGbCartSides(s32 slot0Port, s32 slot1Port, s32 slot2Port, s32 slot3Port) {
    s32 temp;

    FreeBattle_ClearBattleSide(&gSessionContext.battleSides[0]);
    FreeBattle_ClearBattleSide(&gSessionContext.battleSides[1]);
    gSessionContext.trainerSlots[0].isHuman = 0;
    gSessionContext.trainerSlots[1].isHuman = 0;
    gSessionContext.trainerSlots[2].isHuman = 0;
    gSessionContext.trainerSlots[3].isHuman = 0;
    if (slot0Port > 0) {
        temp = slot0Port - 1;
        FreeBattle_LoadGbCartTrainer(&gSessionContext.trainerSlots[0], &gSessionContext.rosterInfo[0], temp, temp);
        gSessionContext.battleSides[0].teamMember[gSessionContext.battleSides[0].tagTeamSize] = &gSessionContext.trainerSlots[0];
        gSessionContext.battleSides[0].tagTeamSize = gSessionContext.battleSides[0].tagTeamSize + 1;
    }
    if (slot1Port > 0) {
        temp = slot1Port - 1;
        FreeBattle_LoadGbCartTrainer(&gSessionContext.trainerSlots[1], &gSessionContext.rosterInfo[1], temp, temp);
        gSessionContext.battleSides[0].teamMember[gSessionContext.battleSides[0].tagTeamSize] = &gSessionContext.trainerSlots[1];
        gSessionContext.battleSides[0].tagTeamSize = gSessionContext.battleSides[0].tagTeamSize + 1;
    }
    if (slot2Port > 0) {
        temp = slot2Port - 1;
        FreeBattle_LoadGbCartTrainer(&gSessionContext.trainerSlots[2], &gSessionContext.rosterInfo[2], temp, temp);
        gSessionContext.battleSides[1].teamMember[gSessionContext.battleSides[1].tagTeamSize] = &gSessionContext.trainerSlots[2];
        gSessionContext.battleSides[1].tagTeamSize = gSessionContext.battleSides[1].tagTeamSize + 1;
    }
    if (slot3Port > 0) {
        temp = slot3Port - 1;
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
