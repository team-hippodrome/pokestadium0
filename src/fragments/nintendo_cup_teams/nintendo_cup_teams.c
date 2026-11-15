/* Stadium Zero fragment009_175570. */

#include "global.h"
#include "game_state.h"
#include "hal_libc.h"
#include "matrix.h"
#include "m2c_macros.h"
#include "nintendo_cup_teams.h"

extern Controller* D_800603C4;
extern DemoTeamTemplate D_82400400[];
extern s8 D_82405F10[];

void func_824000F0(BattleSide* arg0, TeamRoster* arg1);
s32 func_82400118(SessionContext* arg0);

void func_82400020(TeamRoster* roster, ExtendedRosterInfo* info, DemoTeamTemplate* template, s32 arg3) {
    roster->isHuman = 3;
    roster->controllerPort = 1;
    roster->controller = D_800603C4;
    roster->trainerId = template->trainerId;
    roster->numberOfPokemonBrought = 6;
    roster->rosterInfo = info;
    HAL_Strcpy(roster->trainerName, template->shortName);
    _bcopy(template->mons, roster->pokemonPicked, sizeof(roster->pokemonPicked));
    info->unk_000 = template->unk_00;
    info->numberOfPokemonCanBePicked = 6;
    info->trainerIndex = arg3;
    _bcopy(roster->pokemonPicked, info->battleMon, sizeof(roster->pokemonPicked));
    HAL_Strcpy(info->title, template->title);
    HAL_Strcpy(info->fullName, template->fullName);
}

void func_824000F0(BattleSide* arg0, TeamRoster* arg1) {
    arg0->modelFlags = 0;
    arg0->tagTeamSize = 1;
    arg0->displayModel = 0;
    arg0->displayMon = NULL;
    arg0->loadedModel = NULL;
    arg0->teamMember[0] = arg1;
    arg0->backgroundLoadFlags = 0;
    arg0->backgroundFileList = 0;
}

s32 func_82400118(SessionContext* arg0) {
    s32 found;
    s32 i;
    s32 pick;

    do {
        found = FALSE;
        i = 0;
        do {
            pick = MathUtil_Random16() & 0xF;
        } while (pick == 0xF);
        for (i = 0; i < arg0->roundOrDemoId - 1; i++) {
            if (pick == arg0->opponentHistory[0][i]) {
                found = TRUE;
                break;
            }
        }
    } while (found);
    return pick;
}

void func_824001B4(SessionContext* arg0) {
    arg0->modeSelection = 0;
    arg0->battleSides[0].teamMember[0]->rosterInfo->trainerIndex = arg0->roundOrDemoId + 0x16;
    arg0->battleSides[1].teamMember[0]->rosterInfo->trainerIndex = arg0->roundOrDemoId + 0x16;
}

void func_824001E4(SessionContext* arg0) {
    s32 round = arg0->roundOrDemoId - 1;
    TeamRoster* roster;
    s32 pick = func_82400118(arg0);

    arg0->ruleCategory = 1;
    arg0->opponentHistory[0][round] = pick;
    arg0->rosterInfo[0].trainerIndex = arg0->roundOrDemoId + 0x16;
    roster = &arg0->trainerSlots[1];
    func_82400020(roster, &arg0->rosterInfo[1], &D_82400400[pick], pick);
    func_824000F0(&arg0->battleSides[1], roster);
}

void func_82400270(SessionContext* arg0) {
    TeamRoster* roster;
    s32 round = arg0->roundOrDemoId - 1;
    s32 pick = D_82405F10[arg0->modeSelection] + round;

    arg0->ruleCategory = 2;
    arg0->opponentHistory[0][round] = pick;
    arg0->rosterInfo[0].trainerIndex = arg0->roundOrDemoId + 0x16;
    roster = &arg0->trainerSlots[1];
    func_82400020(roster, &arg0->rosterInfo[1], &D_82400400[pick], round + 0xF);
    func_824000F0(&arg0->battleSides[1], roster);
}

void func_82400304(SessionContext* arg0) {
    s32 round = arg0->roundOrDemoId - 1;

    arg0->ruleCategory = 1;
    arg0->rosterInfo[0].trainerIndex = arg0->roundOrDemoId + 0x16;
    func_82400020(&arg0->trainerSlots[1], &arg0->rosterInfo[1], &D_82400400[round], round);
    func_824000F0(&arg0->battleSides[1], &arg0->trainerSlots[1]);
}

void func_824001E4(SessionContext* arg0);
void func_82400270(SessionContext* arg0);
void func_82400304(SessionContext* arg0);

s32 func_82400374(s32 arg0, SessionContext* arg1) {
    s8 temp_v0;

    temp_v0 = arg1->mode;
    switch (temp_v0) {                              /* irregular */
    case 0:
        func_824001B4(arg1);
        break;
    case 1:
        func_824001E4(arg1);
        break;
    case 2:
        func_82400270(arg1);
        break;
    case -1:
        func_82400304(arg1);
        break;
    }
    return 0;
}
