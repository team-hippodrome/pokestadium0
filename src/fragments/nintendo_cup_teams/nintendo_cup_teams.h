/* Declarations for src/fragments/nintendo_cup_teams/. */
#ifndef NINTENDO_CUP_TEAMS_H
#define NINTENDO_CUP_TEAMS_H

#include "global.h"
#include "game_state.h"

// A COM trainer and team for one tournament round. sTournamentOpponents (0x82400400) holds 47:
// 0-14 are the Nintendo Cup '97 finalists of the Lv. 50-55 Tournament (「ほっかいどう」 Hokkaido ...
// 「きゅうしゅうＢ」 Kyushu B; romanizations in the glossary), and 15-46 are the Lv. 1-30 Tournament's
// four cups, eight rounds each. Every cup meets the same eight trainer classes in the same order
// (Bug Catcher, Burglar, Bird Keeper, Jr. Trainer♀, Super Nerd, Youngster, Jr. Trainer♂, Lass).
typedef struct TournamentOpponentTemplate {
    /* 0x00 */ u16 unk_00; // copied to ExtendedRosterInfo.unk_000; 0, 1 or 2 in the data
    /* 0x02 */ u16 trainerId; // @unverified: copied to TeamRoster.trainerId (0x755B, 0x6974, ...)
    /* 0x04 */ char* title; // @unverified: region or 「トレーナー」 (Trainer), as in the ROM data
    /* 0x08 */ char* fullName; // @unverified: two-line real name or trainer class, as in the ROM data
    /* 0x0C */ char* shortName; // @unverified: copied to TeamRoster.trainerName, e.g. 「マサハル」
    /* 0x10 */ BattleMon mons[6];
} TournamentOpponentTemplate; // size = 0x1F0

// nintendo_cup_teams.c
void TournamentOpponent_LoadTemplate(TeamRoster* roster, ExtendedRosterInfo* info, TournamentOpponentTemplate* template, s32 trainer_index);
void TournamentOpponent_InitBattleSide(BattleSide* side, TeamRoster* roster);
s32 TournamentOpponent_PickUnfacedFinalist(SessionContext* session);
void TournamentOpponent_SetUpFreeBattle(SessionContext* session);
void TournamentOpponent_SetUpLv50Round(SessionContext* session);
void TournamentOpponent_SetUpLv1To30Round(SessionContext* session);
void TournamentOpponent_SetUpFinalistByRound(SessionContext* session);
s32 TournamentOpponent_SetUpRound(s32 unused, SessionContext* session);

#endif // NINTENDO_CUP_TEAMS_H
