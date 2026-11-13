/* Declarations for src/fragments/nintendo_cup_teams/. */
#ifndef NINTENDO_CUP_TEAMS_H
#define NINTENDO_CUP_TEAMS_H

#include "global.h"
#include "game_state.h"

// A demo team: the roster's name strings and its six Pokémon.
typedef struct DemoTeamTemplate {
    /* 0x00 */ u16 unk_00;
    /* 0x02 */ u16 unk_02;
    /* 0x04 */ char* unk_04;
    /* 0x08 */ char* unk_08;
    /* 0x0C */ char* unk_0C;
    /* 0x10 */ BattleMon mons[6];
} DemoTeamTemplate; // size = 0x1F0

// nintendo_cup_teams.c
void func_82400020(TeamRoster* roster, ExtendedRosterInfo* info, DemoTeamTemplate* template, s32 arg3);
void func_824000F0(s8 *arg0, s32 arg1);
s32 func_82400118(s8* arg0);
void func_824001B4(s8 *arg0);
void func_824001E4(s8* arg0);
void func_82400270(s8* arg0);
void func_82400304(s8* arg0);
s32 func_82400374(s32 arg0, s8 *arg1);

#endif // NINTENDO_CUP_TEAMS_H
