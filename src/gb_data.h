/* Declarations for src/gb_data.c. */
#ifndef GB_DATA_H
#define GB_DATA_H

#include "global.h"
#include "m2c_macros.h"
#include "game_state.h"

#define STAT_HP 1

#define STAT_SPECIAL 2

#define STAT_SPEED 3

#define STAT_DEFENSE 4

#define STAT_ATTACK 5

// Shifted, one-based view used by gBaseStats. Its named stat fields and
// unk_13 address the same bytes as SpeciesData's stats and growthRate.
typedef struct PokemonStats {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ u8 unk_02;
    /* 0x03 */ u8 unk_03;
    /* 0x04 */ u8 unk_04;
    /* 0x05 */ u8 unk_05;
    /* 0x06 */ u8 baseHP;
    /* 0x07 */ u8 baseSpecial;
    /* 0x08 */ u8 baseSpeed;
    /* 0x09 */ u8 baseDefense;
    /* 0x0A */ u8 baseAttack;
    /* 0x0B */ char unk0B[0x4];
    /* 0x0F */ u8 unk_0F[1];
    /* 0x10 */ char unk10[0x3];
    /* 0x13 */ u8 unk_13;
    /* 0x14 */ char unk14[0x3];
} PokemonStats; // size = 0x17

// Red/Blue base data without the sprite dimensions and sprite pointers.
typedef struct SpeciesData {
    /* 0x00 */ u8 speciesId;
    /* 0x01 */ u8 baseHitPoints;
    /* 0x02 */ u8 baseAttack;
    /* 0x03 */ u8 baseDefense;
    /* 0x04 */ u8 baseSpeed;
    /* 0x05 */ u8 baseSpecial;
    /* 0x06 */ u8 type1;
    /* 0x07 */ u8 type2;
    /* 0x08 */ u8 catchRate;
    /* 0x09 */ u8 baseExperience;
    /* 0x0A */ u8 startingMoves[4];
    /* 0x0E */ u8 growthRate;
    /* 0x0F */ u8 tmHmLearnset[7]; // TM01-TM50, then HM01-HM05, least-significant bit first.
    /* 0x16 */ u8 padding;
} SpeciesData; // size = 0x17

typedef struct unk_D_80071D88 {
    /* 0x00 */ char* type_name;
    /* 0x04 */ Color_RGBA8 color;
} unk_D_80071D88; // size = 0x8

// A Gen 1 box Pokemon record (pokered box_struct), copied to and from BattleMon by
// func_8001FE84 and Pokemon_ToGbRecord. Multi-byte fields are big-endian byte arrays.
typedef struct GbPokemonRecord {
    /* 0x00 */ u8 species; // Gen 1 internal index (0x54 Pikachu seen in play); Species_FromInternalIndex gives BattleMon.species.id
    /* 0x01 */ u8 hp[2]; // Current HP, big-endian
    /* 0x03 */ u8 boxLevel; // Level
    /* 0x04 */ u8 status; // @unverified: BattleMon.statusCondition; pokered box_struct
    /* 0x05 */ u8 type1; // Gen 1 type ID (0x17 Electric, 0x14 Fire)
    /* 0x06 */ u8 type2; // Gen 1 type ID; same as type1 for single-type species
    /* 0x07 */ u8 catchRate; // Catch rate (190 Pikachu, 45 Charmander)
    /* 0x08 */ u8 moves[4]; // Move IDs; shown in the せいとん summary
    /* 0x0C */ u8 otId[2]; // Original trainer ID, big-endian
    /* 0x0E */ u8 exp[3]; // Experience, 24-bit big-endian
    /* 0x11 */ u8 statExp[5][2]; // @unverified: BattleMon.statExp: HP, Attack, Defense, Speed, Special; pokered box_struct
    /* 0x1B */ u8 dvs[2]; // DVs (Atk/Def, Spd/Spc nibbles), big-endian
    /* 0x1D */ u8 pp[4]; // PP of each move
} GbPokemonRecord; // size = 0x21

// A Gen 1 party Pokemon record (pokered party_struct).
typedef struct GbPokemonRecordExt {
    /* 0x00 */ GbPokemonRecord box; // The box record
    /* 0x21 */ u8 level; // Level (party copy)
    // Big-endian u16 stats, read and written with GbData_ReadU16BE/GbData_WriteU16BE. Byte arrays
    // keep the record unaligned: GbSaveParty places it at even and odd offsets.
    /* 0x22 */ u8 stats[5][2]; // Max HP, Attack, Defense, Speed, Special, big-endian; the せいとん summary shows them
} GbPokemonRecordExt; // size = 0x2C

typedef struct DeckHandle {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ u8 unk_02;
    /* 0x03 */ u8 unk_03;
    /* 0x04 */ u8 unk_04;
    /* 0x05 */ u8 unk_05;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
} DeckHandle; // size = 0xC

// The party block of a Japanese Gen 1 save (pokered wPartyCount..wPartyMonNicks, names 6 bytes),
// at offset 0x955 of GbSaveMainData (SRAM 0x2ED5).
typedef struct GbSaveParty {
    /* 0x000 */ u8 count; // Party size; せいとん shows it as 02/06
    /* 0x001 */ u8 species[7]; // Internal species indices ended by 0xFF
    /* 0x008 */ GbPokemonRecordExt mons[6]; // The party Pokemon
    /* 0x110 */ char otNames[6][6]; // Original trainer names, GB charset, 0x50-terminated
    /* 0x134 */ char nicknames[6][6]; // Nicknames, GB charset, 0x50-terminated; shown in せいとん
} GbSaveParty; // size = 0x158

// One Pokemon box of a Japanese Gen 1 save (30 Pokemon, names 6 bytes), as returned by
// GbSave_GetBoxEntry: the current box in GbSaveMainData, or one of the four boxes of a box bank.
typedef struct GbSaveBox {
    /* 0x000 */ u8 count; // Pokemon in the box; せいとん shows it as 00/30
    /* 0x001 */ u8 species[31]; // @unverified: internal species indices ended by 0xFF (GbSave_SetBoxEntryCount); pokered wBoxSpecies
    /* 0x020 */ GbPokemonRecord mons[30]; // @unverified: GbSave_SaveBoxPokemon; pokered wBoxMons
    /* 0x3FE */ char otNames[30][6]; // @unverified: GbSave_SaveBoxPokemon; pokered wBoxMonOT
    /* 0x4B2 */ char nicknames[30][6]; // @unverified: GbSave_SaveBoxPokemon; pokered wBoxMonNicks
} GbSaveBox; // size = 0x566

// The main data of a Japanese Gen 1 save: the 0x1020 bytes read from SRAM 0x2580 (GbSave_ReadMainData)
// into GbSavePort.mainData. Offsets match a Pocket Monsters Green save; see pokered's SRAM layout.
typedef struct GbSaveMainData {
    /* 0x000 */ char unk000[0x18];
    /* 0x018 */ u8 playerName[6]; // GB charset, 0x50-terminated (SRAM 0x2598); checksummed from here (GbSave_VerifyChecksum)
    /* 0x01E */ u8 pokedexOwned[19]; // One bit per National Dex number, bit (n - 1)
    /* 0x031 */ u8 pokedexSeen[19]; // One bit per National Dex number, bit (n - 1)
    // The two item lists hold 2-byte {item ID, quantity} entries ended by an ID of 0xFF. The code copies
    // them through BattleMon.species (Deck_ReadEntry decks 34 and 35), so they keep that type: the quantity
    // sits in BattleMonSpecies.isRental (seen in play: quantities 3, 5, 2).
    /* 0x044 */ u8 numBagItems; // Bag item count; せいとん shows it as 003/020
    /* 0x045 */ BattleMonSpecies bagItems[20]; // {item ID, quantity} pairs ended by an ID of 0xFF
    /* 0x06D */ u8 unk_06D; // Untouched; pokered puts the bag list 0xFF terminator here.
    /* 0x06E */ char unk06E[0x3];
    /* 0x071 */ u8 rivalName[6]; // GB charset, 0x50-terminated
    /* 0x077 */ char unk077[0x4];
    /* 0x07B */ u8 playerId[2]; // Big-endian; the cartridge screen shows it as ID No.
    /* 0x07D */ char unk07D[0x3];
    /* 0x080 */ u8 currentMap; // Map ID; a Pokemon Center (0x29) sets GbSavePort.flags 0x4000 (GbSave_CheckSavedAtPokemonCenter)
    /* 0x081 */ char unk081[0x1DB];
    /* 0x25C */ u8 numBoxItems; // PC item count; せいとん shows it as 001/050
    /* 0x25D */ BattleMonSpecies boxItems[50]; // {item ID, quantity} pairs ended by an ID of 0xFF
    /* 0x2C1 */ u8 unk_2C1; // Untouched; pokered puts the PC item list 0xFF terminator here.
    /* 0x2C2 */ u8 currentBox[2]; // @unverified: read as a big-endian u16 >> 8: bit 0x80 boxes in use, low bits the box (GbSave_GetBoxCount); pokered wCurrentBoxNum
    /* 0x2C4 */ char unk2C4[0x1A9];
    /* 0x46D */ s8 pokedexEventFlags; // Event flag byte at SRAM 0x29ED: bit 0x20 got the Pokedex (GbSave_HasPokedex); set, ずかん (Pokedex) is enabled on the main menu
    /* 0x46E */ char unk46E[0xA5];
    /* 0x513 */ s8 unk_513; // bit 0 read by func_80022F48
    /* 0x514 */ char unk514[0x441];
    /* 0x955 */ GbSaveParty party;
    /* 0xAAD */ GbSaveBox currentBoxData; // @unverified: GbSave_GetBoxEntry for the current box; pokered wBoxDataStart
    /* 0x1013 */ char unk1013[0x1];
    /* 0x1014 */ u8 checksum; // (sum of 0x18..0x1013 & 0xFF) ^ 0xFF; SRAM 0x3594 (GbSave_ComputeChecksum)
    /* 0x1015 */ char unk1015[0xB];
} GbSaveMainData; // size = 0x1020

#include "table_view.h"

extern PokemonStats gBaseStats[];

// Indexed by species ID - 1: Bulbasaur through Mew, then the Substitute doll.
extern SpeciesData gSpeciesData[152];

// gb_data.c
u16 GbData_ReadU16BE(u8* arg0);
u32 GbData_ReadU24BE(u8* arg0);
void GbData_WriteU16BE(u8* arg0, s32 arg1);
void GbData_WriteU24BE(u8* arg0, s32 arg1);
char* Text_UntranscodeName(char* arg0, char* arg1);
char* Text_TranscodeName(char* arg0, char* arg1);
char* Text_UntranscodeFixedName(char* arg0, char* arg1);
s8* Text_CopyString(s8* arg0, s8* arg1);
char* Text_CopySpeciesName(char* arg0, s32 arg1);
char* Text_GetTmHmName(s32 arg0, char* arg1);
void Pokemon_FromGbRecordExt(BattleMon* arg0, GbPokemonRecordExt* arg1);
void Pokemon_ToGbRecord(BattleMon* arg0, GbPokemonRecord* arg1);
void Pokemon_ToGbRecordExt(unk_func_88205880_00D0* arg0, GbPokemonRecordExt* arg1);
u16 StatExpSqrt(u16 arg0);
void func_80020188(void);
u32 CalculateStatValue(s32 statId, s32 speciesId, u16 statModifier, u16 level, u16 dvBits);
void Pokemon_RecalcStats(BattleMon* arg0);
u16 Pokemon_StatExpForTarget(s32 arg0, s32 arg1, u16 arg2, u16 arg3, u16 arg4);
u32 Pokemon_ExpForLevel(s32 arg0, u16 arg1);
s32 func_80020AFC(M2C_UNK, s32, M2C_UNK, M2C_UNK);  /* extern */
u16 Pokemon_LevelFromExp(s32 arg0, u32 arg1);
void Pokemon_PrepareBattleMon(BattleMon* arg0);
u8 Move_GetIdFromTableIndex(s32 tm_hm_index);
u8 Species_FromInternalIndex(s32 arg0);
u8 func_80020984(s32 arg0);
void Deck_InitializeSaveBackend(DeckHandle* arg0);
void Deck_InitializeBoxBackend(DeckHandle* arg0);
DeckHandle* Deck_Open(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
DeckHandle* Deck_OpenAndSetName(s32 arg0, s32 arg1, s32 arg2, s32 arg3, char* arg4, u16 arg5);
s32 Deck_CloseAndFlushBox(DeckHandle* arg0);

// functions defined in assembly
void Pokemon_FromGbRecord(BattleMon* arg0, GbPokemonRecord* arg1);

#endif // GB_DATA_H
