/* Stadium Zero fragment009_175570. */

#include "global.h"
#include "game_state.h"
#include "hal_libc.h"
#include "math_util.h"
#include "m2c_macros.h"

// A demo team: the roster's name strings and its six Pokémon.
typedef struct DemoTeamTemplate {
    /* 0x00 */ u16 unk_00;
    /* 0x02 */ u16 unk_02;
    /* 0x04 */ char* unk_04;
    /* 0x08 */ char* unk_08;
    /* 0x0C */ char* unk_0C;
    /* 0x10 */ BattleMon mons[6];
} DemoTeamTemplate; // size = 0x1F0

extern Controller* D_800603C4;
extern DemoTeamTemplate D_82400400[];
extern s8 D_82405F10[];

void func_824000F0(s8* arg0, s32 arg1);
s32 func_82400118(s8* arg0);

void func_82400020(TeamRoster* roster, ExtendedRosterInfo* info, DemoTeamTemplate* template, s32 arg3) {
    roster->isHuman = 3;
    roster->controllerPort = 1;
    roster->controller = D_800603C4;
    roster->unk_018 = template->unk_02;
    roster->numberOfPokemonBrought = 6;
    roster->rosterInfo = info;
    HAL_Strcpy(roster->trainerName, template->unk_0C);
    _bcopy(template->mons, roster->pokemonPicked, sizeof(roster->pokemonPicked));
    info->unk_000 = template->unk_00;
    info->numberOfPokemonCanBePicked = 6;
    info->unk_003 = arg3;
    _bcopy(roster->pokemonPicked, info->battleMon, sizeof(roster->pokemonPicked));
    HAL_Strcpy(info->unk004, template->unk_04);
    HAL_Strcpy(info->unk_014, template->unk_08);
}

void func_824000F0(s8 *arg0, s32 arg1) {
    M2C_FIELD(arg0, s8 *, 0) = 0;
    M2C_FIELD(arg0, s8 *, 1) = 1;
    M2C_FIELD(arg0, s16 *, 2) = 0;
    M2C_FIELD(arg0, s32 *, 4) = 0;
    M2C_FIELD(arg0, s32 *, 0x14) = 0;
    M2C_FIELD(arg0, s32 *, 8) = arg1;
    M2C_FIELD(arg0, s8 *, 0x1D) = 0;
    M2C_FIELD(arg0, s32 *, 0x20) = 0;
}

s32 func_82400118(s8* arg0) {
    s32 found;
    s32 i;
    s32 pick;

    do {
        found = FALSE;
        i = 0;
        do {
            pick = MathUtil_Random16() & 0xF;
        } while (pick == 0xF);
        for (i = 0; i < arg0[3] - 1; i++) {
            if (pick == ((u8*)arg0)[0x1084 + i]) {
                found = TRUE;
                break;
            }
        }
    } while (found);
    return pick;
}

void func_824001B4(s8 *arg0) {
    M2C_FIELD(arg0, s8 *, 2) = 0;
    M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, s8 **, 0x103C), s8 **, 0x1FC), s8 *, 3) = (s8) (M2C_FIELD(arg0, s8 *, 3) + 0x16);
    M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, s8 **, 0x1064), s8 **, 0x1FC), s8 *, 3) = (s8) (M2C_FIELD(arg0, s8 *, 3) + 0x16);
}

void func_824001E4(s8* arg0) {
    s32 round = arg0[3] - 1;
    TeamRoster* roster;
    s32 pick = func_82400118(arg0);

    arg0[1] = 1;
    arg0[0x1084 + round] = pick;
    arg0[0x817] = arg0[3] + 0x16;
    roster = (TeamRoster*)(arg0 + 0x208);
    func_82400020(roster, (ExtendedRosterInfo*)(arg0 + 0xA1C), &D_82400400[pick], pick);
    func_824000F0(arg0 + 0x105C, (s32)roster);
}

void func_82400270(s8* arg0) {
    TeamRoster* roster;
    s32 round = arg0[3] - 1;
    s32 pick = D_82405F10[arg0[2]] + round;

    arg0[1] = 2;
    arg0[0x1084 + round] = pick;
    arg0[0x817] = arg0[3] + 0x16;
    roster = (TeamRoster*)(arg0 + 0x208);
    func_82400020(roster, (ExtendedRosterInfo*)(arg0 + 0xA1C), &D_82400400[pick], round + 0xF);
    func_824000F0(arg0 + 0x105C, (s32)roster);
}

void func_82400304(s8* arg0) {
    s32 round = arg0[3] - 1;

    arg0[1] = 1;
    arg0[0x817] = arg0[3] + 0x16;
    func_82400020((TeamRoster*)(arg0 + 0x208), (ExtendedRosterInfo*)(arg0 + 0xA1C), &D_82400400[round], round);
    func_824000F0(arg0 + 0x105C, (s32)(arg0 + 0x208));
}

void func_824001E4(s8* arg0);
void func_82400270(s8* arg0);
void func_82400304(s8* arg0);

s32 func_82400374(s32 arg0, s8 *arg1) {
    s8 temp_v0;

    temp_v0 = *arg1;
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
