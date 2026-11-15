/* Stadium Zero fragment009_175570: COM opponents for each tournament round. */

#include "global.h"
#include "game_state.h"
#include "hal_libc.h"
#include "matrix.h"
#include "m2c_macros.h"
#include "nintendo_cup_teams.h"

extern Controller* D_800603C4;
extern TournamentOpponentTemplate sTournamentOpponents[];
extern s8 sCupFirstOpponent[];

/**
 * Fills a COM trainer slot from an opponent template: a COM controller on port 1, the template's
 * trainer id and short name, and all six of its Pokémon brought. The roster info gets the same
 * team plus the region (or 「トレーナー」) title and the full name, and `trainer_index` picks the
 * trainer picture the VS screen loads.
 * Seen in play (2026-11-14): in Lv. 50-55 Tournament round 1 it loaded template 0 with
 * trainer_index 0, and the VS screen showed 「ほっかいどう かとう かずひと」 (Hokkaido, Katou Kazuhito)
 * with that template's Lapras, Jolteon, Starmie, Alakazam, Tauros and Dugtrio.
 */
void TournamentOpponent_LoadTemplate(TeamRoster* roster, ExtendedRosterInfo* info, TournamentOpponentTemplate* template, s32 trainer_index) {
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
    info->trainerIndex = trainer_index;
    _bcopy(roster->pokemonPicked, info->battleMon, sizeof(roster->pokemonPicked));
    HAL_Strcpy(info->title, template->title);
    HAL_Strcpy(info->fullName, template->fullName);
}

/**
 * Resets a battle side to a single trainer, `roster`, with no model or background loaded yet.
 * Seen in play (2026-11-14): ran for side 2 right after the opponent template was loaded, in
 * both tournaments.
 */
void TournamentOpponent_InitBattleSide(BattleSide* side, TeamRoster* roster) {
    side->modelFlags = 0;
    side->tagTeamSize = 1;
    side->displayModel = 0;
    side->displayMon = NULL;
    side->loadedModel = NULL;
    side->teamMember[0] = roster;
    side->backgroundLoadFlags = 0;
    side->backgroundFileList = 0;
}

/**
 * Picks a random Nintendo Cup '97 finalist (0-14) that the player has not met in an earlier round
 * of this Lv. 50-55 Tournament, rerolling until the pick is not in `opponentHistory`.
 * Seen in play (2026-11-14): from the same savestate, round 1 picked finalist 0; with round
 * poked to 2 and finalist 0 poked into the round-1 history it picked 1 instead, and the VS
 * screen showed 「とうほくＡ ゆうき ようじろう」 (Tohoku A, Yuuki Youjirou).
 */
s32 TournamentOpponent_PickUnfacedFinalist(SessionContext* session) {
    s32 found;
    s32 i;
    s32 pick;

    do {
        found = FALSE;
        i = 0;
        do {
            pick = MathUtil_Random16() & 0xF;
        } while (pick == 15);
        for (i = 0; i < session->roundOrDemoId - 1; i++) {
            if (pick == session->opponentHistory[0][i]) {
                found = TRUE;
                break;
            }
        }
    } while (found);
    return pick;
}

/**
 * Mode 0 (Free Battle): loads no opponent, and gives both sides the default trainer picture
 * (round + 22).
 * Seen in play (2026-11-14): ran in a Free Battle against COM (mode 0), and the VS screen showed
 * the same 「トレーナー」 picture for 1P and COM.
 */
void TournamentOpponent_SetUpFreeBattle(SessionContext* session) {
    session->modeSelection = 0;
    session->battleSides[0].teamMember[0]->rosterInfo->trainerIndex = session->roundOrDemoId + 22;
    session->battleSides[1].teamMember[0]->rosterInfo->trainerIndex = session->roundOrDemoId + 22;
}

/**
 * Mode 1, the Lv. 50-55 Tournament: puts a random finalist the player has not met yet on side 2,
 * records the pick in `opponentHistory` and shows the finalist's own picture.
 * Seen in play (2026-11-14): ran on entering the L５０〜５５での トーナメント (Lv. 50-55 Tournament),
 * session mode 1, and set rule category 1.
 */
void TournamentOpponent_SetUpLv50Round(SessionContext* session) {
    s32 round = session->roundOrDemoId - 1;
    TeamRoster* roster;
    s32 pick = TournamentOpponent_PickUnfacedFinalist(session);

    session->ruleCategory = 1;
    session->opponentHistory[0][round] = pick;
    session->rosterInfo[0].trainerIndex = session->roundOrDemoId + 22;
    roster = &session->trainerSlots[1];
    TournamentOpponent_LoadTemplate(roster, &session->rosterInfo[1], &sTournamentOpponents[pick], pick);
    TournamentOpponent_InitBattleSide(&session->battleSides[1], roster);
}

/**
 * Mode 2, the Lv. 1-30 Tournament: puts the current cup's trainer for this round on side 2
 * (template sCupFirstOpponent[cup] + round) and shows that trainer class's picture (round + 15).
 * Seen in play (2026-11-14): on entering the モンスターボールカップ (Poké Ball Cup) of the
 * L １〜３０での トーナメント (Lv. 1-30 Tournament) it loaded template 15 (Bug Catcher) with
 * trainer_index 15 and set rule category 2; with the cup poked to 3 (Master Ball Cup) it
 * loaded template 39.
 */
void TournamentOpponent_SetUpLv1To30Round(SessionContext* session) {
    TeamRoster* roster;
    s32 round = session->roundOrDemoId - 1;
    s32 pick = sCupFirstOpponent[session->modeSelection] + round;

    session->ruleCategory = 2;
    session->opponentHistory[0][round] = pick;
    session->rosterInfo[0].trainerIndex = session->roundOrDemoId + 22;
    roster = &session->trainerSlots[1];
    TournamentOpponent_LoadTemplate(roster, &session->rosterInfo[1], &sTournamentOpponents[pick], round + 15);
    TournamentOpponent_InitBattleSide(&session->battleSides[1], roster);
}

/**
 * Mode -1: puts finalist number `round` on side 2, in table order instead of at random, with Lv. 50-55
 * rules. No code found that sets mode -1.
 * Seen in play (2026-11-14) only with RAM poked: mode -1 and round 3 at the Lv. 50-55
 * Tournament's start loaded finalist 2, and the VS screen showed that template's team
 * (Articuno, Jolteon, Tauros, Starmie, Jynx, Alakazam).
 */
void TournamentOpponent_SetUpFinalistByRound(SessionContext* session) {
    s32 round = session->roundOrDemoId - 1;

    session->ruleCategory = 1;
    session->rosterInfo[0].trainerIndex = session->roundOrDemoId + 22;
    TournamentOpponent_LoadTemplate(&session->trainerSlots[1], &session->rosterInfo[1], &sTournamentOpponents[round], round);
    TournamentOpponent_InitBattleSide(&session->battleSides[1], &session->trainerSlots[1]);
}

/**
 * Fragment entry, called by the VS scene before each tournament round (and again after each win):
 * sets up the COM opponent for `roundOrDemoId` by session mode.
 * Seen in play (2026-11-14): loaded by VsScene_Play and dispatched to the mode 0 (Free Battle),
 * 1 (Lv. 50-55), 2 (Lv. 1-30) and -1 (poked) handlers.
 */
s32 TournamentOpponent_SetUpRound(s32 unused, SessionContext* session) {
    s8 mode;

    mode = session->mode;
    switch (mode) {                              /* irregular */
    case 0:
        TournamentOpponent_SetUpFreeBattle(session);
        break;
    case 1:
        TournamentOpponent_SetUpLv50Round(session);
        break;
    case 2:
        TournamentOpponent_SetUpLv1To30Round(session);
        break;
    case -1:
        TournamentOpponent_SetUpFinalistByRound(session);
        break;
    }
    return 0;
}
