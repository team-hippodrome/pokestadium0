/* Declarations for src/fragments/nintendo_cup_teams/. */
#ifndef NINTENDO_CUP_TEAMS_H
#define NINTENDO_CUP_TEAMS_H

#include "global.h"
#include "game_state.h"

// A COM trainer's team for a tournament round (D_82400400[18]): 15 regional players
// (「ほっかいどう」 Hokkaido ... 「きゅうしゅうＢ」 Kyushu B) and 3 Gen 1 trainer classes.
typedef struct DemoTeamTemplate {
    /* 0x00 */ u16 unk_00; // copied to ExtendedRosterInfo.unk_000; 0, 1 or 2 in the data
    /* 0x02 */ u16 trainerId; // @unverified: copied to TeamRoster.trainerId (0x755B, 0x6974, ...)
    /* 0x04 */ char* title; // @unverified: region or 「トレーナー」 (Trainer), as in the ROM data
    /* 0x08 */ char* fullName; // @unverified: two-line real name or trainer class, as in the ROM data
    /* 0x0C */ char* shortName; // @unverified: copied to TeamRoster.trainerName, e.g. 「マサハル」
    /* 0x10 */ BattleMon mons[6];
} DemoTeamTemplate; // size = 0x1F0

// nintendo_cup_teams.c
void func_82400020(TeamRoster* roster, ExtendedRosterInfo* info, DemoTeamTemplate* template, s32 arg3);
void func_824000F0(BattleSide* arg0, TeamRoster* arg1);
s32 func_82400118(SessionContext* arg0);
void func_824001B4(SessionContext* arg0);
void func_824001E4(SessionContext* arg0);
void func_82400270(SessionContext* arg0);
void func_82400304(SessionContext* arg0);
s32 func_82400374(s32 arg0, SessionContext* arg1);

#endif // NINTENDO_CUP_TEAMS_H
