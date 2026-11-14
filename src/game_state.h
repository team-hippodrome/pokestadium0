/* Declarations for src/game_state.c. */
#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "global.h"
#include "PR/leo.h"
#include "stdarg.h"
#include "moves.h"
#include "m2c_macros.h"
#include "controller.h"
#include "dp_intro.h"
#include "scheduler.h"

typedef struct arg1_func_80019420 {
    /* 0x00 */ s8 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ void* unk_04;
} arg1_func_80019420; // size = 0x8

typedef struct unk_D_800AE520 {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 fragment_id;
    /* 0x04 */ u8* rom_start;
    /* 0x08 */ u8* rom_end;
    /* 0x0C */ s32 arg0;
    /* 0x10 */ s32 arg1;
} unk_D_800AE520; // size >= 0x14

typedef struct BattleMonSpecies {
    /* 0x00 */ u8 id;
    /* 0x01 */ u8 isRental; // 1 for a rental picked in the tournament entry screen (seen: a rented Pikachu); 0 for GB Pokemon (Pokemon_FromGbRecord). Free Battle rentals had 0. func_82200E2C skips its Pikachu-without-Surf check (likely the Surf Pikachu reward) when any team member has it
} BattleMonSpecies; // size = 0x2

typedef struct BattleMon {
    /* 0x00 */ BattleMonSpecies species;
    /* 0x02 */ u16 hp;
    /* 0x04 */ u8 boxLevel; // the Game Boy box record's level byte; set from level before a box save
    /* 0x05 */ u8 statusCondition;
    /* 0x06 */ u8 type1;
    /* 0x07 */ u8 type2;
    /* 0x08 */ u8 catchRate; // the Game Boy record's catch rate byte; 0xFF in rental Pokémon
    /* 0x09 */ u8 moves[4];
    /* 0x0D */ u8 pad0D;
    /* 0x0E */ u16 otId; // Original Trainer ID No.
    /* 0x10 */ u32 exp; // experience points: 8000 for a level 20 Onix, 15625 for a level 25 Ditto
    /* 0x14 */ u16 statExp[5]; // Gen 1 stat experience (EVs): HP, Attack, Defense, Speed, Special; vitamins add 2560
    /* 0x1E */ u16 dvs; // Gen 1 DVs (IVs), 4 bits per stat
    /* 0x20 */ u8 pp[4];
    /* 0x24 */ u8 level;
    /* 0x25 */ u8 faintBatch; // 0 while not fainted, else the sNextFaintBatch it fainted in
    /* 0x26 */ u16 maxHp;
    /* 0x28 */ u16 attack;
    /* 0x2A */ u16 defense;
    /* 0x2C */ u16 speed;
    /* 0x2E */ u16 special;
    /* 0x30 */ u8 nickname[13]; // EUC-JP, e.g. イワイワ
    /* 0x3D */ u8 gbOtNameHead[3]; // first 3 bytes of the Game Boy save's OT name, kept to write back unchanged
    /* 0x40 */ u8 otName[13]; // Original Trainer name, EUC-JP, e.g. ガール
    /* 0x4D */ u8 gbOtNameTail[3]; // last 3 bytes of the Game Boy save's OT name
} BattleMon; // size = 0x50

typedef struct ExtendedRosterInfo {
    /* 0x000 */ u16 unk_000;
    /* 0x002 */ u8 numberOfPokemonCanBePicked; // Only changes for Free Battle and VS Mewtwo, see @src/fragments/battle_engine/battle_engine_main.c
    /* 0x003 */ u8 unk_003;
    /* 0x004 */ char unk004[0x10];
    /* 0x014 */ char unk_014[4];
    /* 0x018 */ char unk018[0x10];
    /* 0x028 */ BattleMon battleMon[1];
    /* 0x078 */ char unk078[0x190];
} ExtendedRosterInfo; // size = 0x208 (Stadium 1: 0x248)

typedef struct TeamRoster {
    /* 0x000 */ u8 isHuman;
    /* 0x001 */ u8 controllerPort;
    /* 0x002 */ u8 numberOfPokemonBrought;
    /* 0x004 */ Controller* controller;
    /* 0x008 */ char trainerName[4];
    /* 0x00C */ char unk00C[0xC];
    /* 0x018 */ s32 unk_018;
    /* 0x01C */ BattleMon pokemonPicked[6];
    /* 0x1FC */ ExtendedRosterInfo* rosterInfo;
    /* 0x200 */ char unk200[0x4];
} TeamRoster; // size = 0x204 (Stadium 1: 0x21C)

typedef struct BattleSessionTeams {
    /* 0x00 */ u8 uniqueStatusFlags;
    /* 0x01 */ u8 tagTeamSize;
    /* 0x02 */ s16 displayModel;
    /* 0x04 */ TeamRoster* unk_04;
    /* 0x08 */ TeamRoster* teamMember[2];
    /* 0x10 */ ModelLoadContext* unk_10;
    /* 0x14 */ ModelNodeView* loadedModel;
    /* 0x18 */ ModelNodeView* unk_18;
    /* 0x1C */ u8 unk_1C;
    /* 0x1D */ u8 assetIsBusy;
    /* 0x1E */ u8 unk_1E;
    /* 0x20 */ s32 unk_20;
    /* 0x24 */ arg1_func_80019420* unk_24;
} BattleSessionTeams; // size = 0x28

// Zero's layout (offsets checked against func_80025910, func_8002572C and func_80025830, which
// reach these fields by raw offset). gSessionContext at 0x800AE8F0 is defined in game_state.c.
typedef struct SessionContext {
    /* 0x0000 */ s8 mode;
    /* 0x0001 */ s8 ruleCategory;
    /* 0x0002 */ s8 modeSelection; // Cup division or castle location, depending on mode.
    /* 0x0003 */ s8 roundOrDemoId; // One-based battle round; scene ID in non-battle attract demos.
    /* 0x0004 */ TeamRoster trainerSlots[4];
    /* 0x0814 */ ExtendedRosterInfo rosterInfo[4];
    /* 0x1034 */ BattleSessionTeams battleSides[2];
    /* 0x1084 */ u8 opponentHistory[2][4]; // Eight contiguous entries; the first subscript is not a battle side.
    /* 0x108C */ u8 aiDifficulty; // Free Battle: 0 = Hard, 1 = Normal, 2 = Easy.
    /* 0x108D */ u8 timeLimitsEnabled;
    /* 0x108E */ u8 battleLimitMinutes;
    /* 0x108F */ u8 moveLimitSeconds;
    /* 0x1090 */ u8 gbStarterChoice;
    /* 0x1091 */ char unk1091[0x1];
    /* 0x1092 */ u8 inRound2;
    /* 0x1093 */ u8 continueCount;
    /* 0x1094 */ u8 unk_1094; // @unverified: GB port of the continued team, 0xFF for rentals (func_80025A64)
    /* 0x1095 */ u8 sessionFlags;
    /* 0x1096 */ u16 transitionFlags;
} SessionContext; // size = 0x1098

#define RULE_CATEGORY_ANYTHING_GOES 0

#define RULE_CATEGORY_NINTENDO_CUP_97 1

#define RULE_CATEGORY_NINTENDO_CUP_98 2

#define RULE_CATEGORY_NINTENDO_CUP_99 3

#define RULE_CATEGORY_PETIT_CUP 4

#define RULE_CATEGORY_PIKA_CUP 5

#define RULE_CATEGORY_PRIME_CUP 6

#define RULE_CATEGORY_GYM_LEADER_CASTLE 7

#define RULE_CATEGORY_VS_MEWTWO 8

#define SESSION_MODE_ANYTHING_GOES 0

#define SESSION_MODE_NINTENDO_CUP_97 1

#define SESSION_MODE_NINTENDO_CUP_98 2

#define SESSION_MODE_NINTENDO_CUP_99 3

#define SESSION_MODE_PETIT_CUP 4

#define SESSION_MODE_PIKA_CUP 5

#define SESSION_MODE_PRIME_CUP 6

#define SESSION_MODE_GYM_LEADER_CASTLE 7

#define SESSION_MODE_VS_MEWTWO 8

#define SESSION_MODE_BATTLE_NOW 9

#define SESSION_MODE_EVENT_BATTLE 10

// 11-15 Unknown
#define SESSION_MODE_ATTRACT_DEMO_BATTLE 16

// 17, 18: Cutscenes
// 19, 20: Unknown
// 21-24: Cutscenes
#define SESSION_MODE_ATTRACT_DEMO_MINIGAME 25

// 26: Cutscene
#define SESSION_FLAG_REVEAL_MEWTWO 0x04

extern u16 D_8006BBB0[16][256];

extern s32 gCurrentGameState;

extern unk_D_800AE520 D_800AF990;

extern SessionContext gSessionContext;

// game_state.c
s32 Fragment_LoadAndCall(s32 arg0, u8* romStart, u8* romEnd, u32 arg3, u32 arg4);
void Fragment_QueueCall(s32 arg0, u8* arg1, u8* arg2, s32 arg3, s32 arg4);
TeamRoster* Trainer_GetSlots(void);
s32 GbSave_GetActivePort(void);
void GbSave_SetActivePort(s32 arg0);
void State_N64ddBootUnused(void);
void State_GbTower(void);
void State_FastN64Logo(void);
void func_800268DC(void);
void Game_ShutdownAndLoadFragment(s32 arg0, s32 arg1);
void Game_ResetStorageDevice(void);
void Display_DisableBlackout(void);
void func_800273E8(s8* arg0, s32 arg1);
M2C_UNK func_80025BE4(s32);                         /* extern */

#endif // GAME_STATE_H
