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
    /* 0x01 */ u8 unk_01;
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

typedef struct CachedMoveData {
    /* 0x00 */ u8 lastMove;
    /* 0x01 */ u8 effect;
    /* 0x02 */ u8 power;
    /* 0x03 */ u8 type;
    /* 0x04 */ u8 accuracy;
    /* 0x05 */ u8 pp;
} CachedMoveData; // size = 0x6

typedef struct BattleMonRuntime {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ char unk02[0x2];
    /* 0x04 */ u8 unk_04;
    /* 0x05 */ u8 unk_05;
    /* 0x06 */ char unk06[0x5];
    /* 0x0B */ u8 species; // national Pokédex number; Transform copies the target's
    /* 0x0C */ u16 hp; // the HP the HUD, the COM AI and fainting follow
    /* 0x0E */ u16 hpAfterPoisonBurn; // HP once this turn's poison or burn damage is taken
    /* 0x10 */ u16 hpAfterLeechSeed; // the user's HP after the drain, the target's after the heal; 900 when none is pending
    /* 0x12 */ u16 pendingHp; // HP while damage is worked out; 0xFFFF between turns
    /* 0x14 */ u8 rosterIndex; // copy of ActivePokemonState.rosterIndex
    /* 0x15 */ u8 pendingStatusCondition;
    /* 0x16 */ u8 restSleepTurns[6]; // per brought Pokémon (rosterIndex + teamMemberIndex * 3): sleep turns left from Rest, which sets 2
    /* 0x1C */ u8 type1;
    /* 0x1D */ u8 type2;
    /* 0x1E */ u8 catchRate; // copied from BattleMon.catchRate
    /* 0x1F */ u8 moves[4];
    /* 0x23 */ char unk23[0x1];
    /* 0x24 */ u16 dvs; // Gen 1 DVs (IVs), copied from BattleMon.dvs; Transform copies the target's
    /* 0x26 */ u8 level;
    /* 0x28 */ u16 maxHp;
    /* 0x2A */ u16 modifiedAttack;
    /* 0x2C */ u16 modifiedDefense;
    /* 0x2E */ u16 speed;
    /* 0x30 */ u16 modifiedSpecial;
    /* 0x32 */ u8 pp[4];
    /* 0x36 */ u16 baseHp; // gBaseStats[species].baseHP
    /* 0x38 */ u16 unmodifiedAttack;
    /* 0x3A */ u16 unmodifiedDefense;
    /* 0x3C */ u16 unmodifiedSpeed;
    /* 0x3E */ u16 unmodifiedSpecial;
    /* 0x40 */ char unk40[0x4];
    /* 0x44 */ CachedMoveData moveCache;
    /* 0x4A */ u8 unk_4A;
    /* 0x4B */ u8 unk_4B;
    /* 0x4C */ u8 immobilizedReason;
    /* 0x4D */ u8 volatileStatusFlags;
    /* 0x4E */ u8 uniqueStatusFlags;
    /* 0x4F */ u8 effectTurnsLeft;
    /* 0x50 */ u8 confusionTurnsLeft;
    /* 0x51 */ u8 toxicCounter;
    /* 0x52 */ u8 disabledMoveState;
    /* 0x53 */ u8 unk_53;
    /* 0x54 */ u16 effectCounter;
    /* 0x56 */ u8 scaleResize;
    /* 0x57 */ u8 disabledMove;
    /* 0x58 */ u8 lastMove;
    /* 0x59 */ u8 substituteHp;
    /* 0x5A */ u8 usedMove;
    /* 0x5B */ u8 receivedCritFlag; // the last hit taken: 1 critical hit, 2 one-hit KO
    /* 0x5C */ u8 statStages[8]; // 1-13, 7 is neutral: Attack, Defense, Speed, Special, accuracy, evasion; the last 2 are never used
} BattleMonRuntime; // size = 0x64

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
    /* 0x018 */ s32 trainerId; // @unverified: id word BattleAi_AddTrainerPickScore switches the COM picks on (0x6974, 0x95EC, ...)
    /* 0x01C */ BattleMon pokemonPicked[6];
    /* 0x1FC */ ExtendedRosterInfo* rosterInfo;
    /* 0x200 */ char unk200[0x4];
} TeamRoster; // size = 0x204 (Stadium 1: 0x21C)

// One side of a battle: its trainer(s) (two in a tag battle), the Pokémon model it shows and model load state.
typedef struct BattleSide {
    /* 0x00 */ u8 modelFlags; // @unverified: bit 0x80 asks for the side's model to be reloaded, 0x10 is set once it is loaded (owner_animation.c, phases_2.c)
    /* 0x01 */ u8 tagTeamSize;
    /* 0x02 */ s16 displayModel;
    /* 0x04 */ BattleMon* displayMon; // @unverified: party BattleMon whose model the side shows (set with displayModel)
    /* 0x08 */ TeamRoster* teamMember[2];
    /* 0x10 */ ModelLoadContext* unk_10;
    /* 0x14 */ ModelNodeView* loadedModel;
    /* 0x18 */ ModelNodeView* unk_18;
    /* 0x1C */ u8 unk_1C;
    /* 0x1D */ u8 assetIsBusy;
    /* 0x1E */ u8 unk_1E;
    /* 0x20 */ s32 unk_20;
    /* 0x24 */ arg1_func_80019420* unk_24;
} BattleSide; // size = 0x28

// Offsets are for US 1.0. In VERSION_JP, TeamRoster and ExtendedRosterInfo are 0x18 bytes shorter,
// so rosterInfo starts at 0x0814, battleSides at 0x10D4, and the struct is 0x1138 bytes.
typedef struct SessionContext {
    /* 0x0000 */ s8 mode;
    /* 0x0001 */ s8 ruleCategory;
    /* 0x0002 */ s8 modeSelection; // Cup division or castle location, depending on mode.
    /* 0x0003 */ s8 roundOrDemoId; // One-based battle round; scene ID in non-battle attract demos.
    /* 0x0004 */ TeamRoster trainerSlots[4];
    /* 0x0874 */ ExtendedRosterInfo rosterInfo[4];
    /* 0x1194 */ BattleSide battleSides[2];
    /* 0x11E4 */ u8 opponentHistory[2][4]; // Eight contiguous entries; the first subscript is not a battle side.
    /* 0x11EC */ u8 aiDifficulty; // Free Battle: 0 = Hard, 1 = Normal, 2 = Easy.
    /* 0x11ED */ u8 timeLimitsEnabled;
    /* 0x11EE */ u8 battleLimitMinutes;
    /* 0x11EF */ u8 moveLimitSeconds;
    /* 0x11F0 */ u8 gbStarterChoice;
    /* 0x11F1 */ char unk11F1[0x1];
    /* 0x11F2 */ u8 inRound2;
    /* 0x11F3 */ u8 continueCount;
    /* 0x11F4 */ u8 unk_11F4;
    /* 0x11F5 */ u8 sessionFlags;
    /* 0x11F6 */ u16 transitionFlags;
} SessionContext; // size = 0x11F8 (JP: 0x1138)

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

typedef struct UnkStruct80083CA0_2 {
    /* 0x000 */ OSThread thread;
    /* 0x1B0 */ OSMesg unk_1B0;
    /* 0x1B4 */ char unk1B4[0xC];
    /* 0x1C0 */ OSMesgQueue unk_1C0;
    /* 0x1D8 */ s32 unk_1D8;
    /* 0x1DC */ s32 unk_1DC;
    /* 0x1E0 */ u8 unk1E0[0x800];
    /* 0x9E0 */ struct unk_D_80068BB0* unk_9E0;
    /* 0x9E4 */ OSMesg unk_9E4;
    /* 0x9E8 */ OSMesg unk_9E8;
    /* 0x9EC */ OSMesgQueue unk_9EC;
    /* 0xA04 */ OSMesgQueue unk_A04;
    /* 0xA1C */ char unkA1C[0x4];
    /* 0xA20 */ UnkStruct80001380 unk_A20;
    /* 0xA88 */ u16 unk_A88;
    /* 0xA8A */ u8 unk_A8A;
    /* 0xA8B */ u8 unk_A8B;
    /* 0xA8C */ UnkArray4 unk_A8C;
    /* 0xA9C */ UnkArray4 unk_A9C;
    /* 0xAAC */ UnkArray4 unk_AAC;
    /* 0xABC */ char unkABC[0x4];
} UnkStruct80083CA0_2; // size = 0xAC0

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
