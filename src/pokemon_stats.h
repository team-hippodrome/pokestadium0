/* Declarations for src/pokemon_stats.c, src/pokemon_stats_2.c. */
#ifndef POKEMON_STATS_H
#define POKEMON_STATS_H

#include "global.h"
#include "m2c_macros.h"
#include "gb_data.h"

typedef enum {
    POKEMON_ROM_NONE = 0,
    POKEMON_ROM_RED = 1,
    POKEMON_ROM_GREEN = 2,
    POKEMON_ROM_BLUE = 3,
    POKEMON_ROM_YELLOW = 7,
} PokemonRomType;

typedef struct GbSavePortSnapshot {
    /* 0x000 */ u8 unk_000;
    /* 0x001 */ u8 unk_001;
    /* 0x002 */ u16 unk_002;
    /* 0x004 */ char unk_004[11];
    /* 0x00F */ GbSaveParty unk_00F;
} GbSavePortSnapshot; // size >= 0x1A3

typedef struct GbSaveBoxPair {
    /* 0x000 */ GbSaveBoxEntry unk_000;
    /* 0x000 */ GbSaveBoxEntry unk_014;
    /* 0x028 */ char unk028[0x43A];
} GbSaveBoxPair; // size = 0x462

typedef struct GbSaveBoxBank {
    /* 0x0000 */ GbSaveBoxPair unk_0000[6];
    /* 0x1A4C */ char unk1A4C[0x14];
} GbSaveBoxBank; // size = 0x1A60

typedef struct GbSaveBoxData {
    /* 0x0000 */ GbSaveBoxBank unk_0000[2];
} GbSaveBoxData; // size = 0x34C0

typedef struct GbSavePlayerIdentity {
    /* 0x00 */ u16 unk_00;
    /* 0x02 */ char unk_02[11];
    /* 0x0D */ u8 unk_0D[2];
    /* 0x0F */ char unkF[0x1];
} GbSavePlayerIdentity; // size = 0x10

typedef struct GbSavePort {
    /* 0x00 */ u16 unk_00;
    /* 0x02 */ u8 unk_02;
    /* 0x03 */ u8 unk_03;
    /* 0x04 */ u8 unk_04;
    /* 0x05 */ u8 unk_05;
    /* 0x06 */ u8 unk_06[0x13];
    /* 0x19 */ u8 unk_19[0x20];
    /* 0x39 */ char unk39[0x7];
    /* 0x40 */ GbSavePlayerIdentity unk_40;
    /* 0x50 */ GbSaveMainData* unk_50;
    /* 0x54 */ GbSaveBoxData* unk_54;
} GbSavePort; // size = 0x58

#include "game_state.h"
#include "table_view.h"

// pokemon_stats.c
s32 Deck_CloseAndFlush(DeckHandle* arg0);
s32 Deck_ReadEntries(u8* arg0, s32 arg1, DeckHandle* arg2);
s32 Deck_WriteEntries(u8* arg0, s32 arg1, DeckHandle* arg2);
M2C_UNK func_80020C60(s32);                         /* extern */
void func_80020DF0(s32, s32, s32);

// pokemon_stats_2.c
s32 GbSave_HasPlayerNameMarker(u8* arg0);
s32 GbSave_VerifyChecksum(u8* arg0, u8* arg1);
void GbSave_ComputeChecksum(u8* arg0, u8* arg1);
s32 GbSave_VerifyWriteback(u8* arg0, s32 arg1);
s8 GbCart_IdentifyGame(s32 arg0);
s32 GbSave_CheckMainDataUnchanged(s32 arg0);
s32 GbSave_ReadMainData(s32 arg0);
s32 GbSave_WriteMainDataChecksum(s32 arg0);
s32 GbSave_ReadBoxBank(s32 arg0, s32 arg1);
s32 GbSave_WriteBoxBank(s32 arg0, s32 arg1);
void GbSave_ReleasePortBuffers(s32 arg0, u32 arg1);
void GbSave_CheckSavedAtPokemonCenter(s32 arg0);
s32 GbSave_OpenMainData(s32 arg0);
s32 GbSave_EnsureMainDataLoaded(s32 arg0);
s32 GbSave_OpenBoxData(s32 arg0);
s32 GbSave_LoadPort(s32 arg0);
s32 GbSave_PollCartRemoval(s32 arg0);
void GbSave_ForceReloadPort(s32 arg0);
s32 GbSave_ScanAllPorts(void);
s32 GbSave_WriteBoxBanks(s32 arg0);
s32 GbSave_CommitMainData(s32 arg0);
s32 GbSave_RebuildAndWriteSave(s32 arg0);
void GbSave_ValidateBeforeWrite(s32 arg0);
void GbSave_RequirePakPresent(s32 arg0);
GbSaveBoxEntry* GbSave_GetBoxEntry(s32 arg0, s32 arg1);
void GbSave_LoadMainPokemon(BattleMon* arg0, s32 arg1, s32 arg2);
void GbSave_SaveMainPokemon(unk_func_88205880_00D0* arg0, s32 arg1, s32 arg2);
void GbSave_LoadBoxPokemon(BattleMon* arg0, s32 arg1, s32 arg2, s32 arg3);
void GbSave_SaveBoxPokemon(BattleMon* arg0, s32 arg1, s32 arg2, s32 arg3);
s32 GbSave_GetBoxEntryCount(s32 arg0, s32 arg1);
void GbSave_SetBoxEntryCount(s32 arg0, s32 arg1, s32 arg2);
s32 Deck_GetCapacity(s32 arg0);
s32 Deck_GetEntrySize(s32 arg0);
s32 Deck_GetCount(s32 arg0, s32 arg1, s32 arg2);
void Deck_DeleteEntry(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void Deck_AppendEntry(s32 arg0, s32 arg1, s32 arg2);
s32 Deck_ReadEntry(s32 arg0, s32 arg1, s32 arg2, s32 arg3, BattleMon* arg4);
s32 Deck_WriteEntry(s32 arg0, s32 arg1, s32 arg2, s32 arg3, unk_func_88205880_00D0* arg4);
s32 GbSave_GetPresentPortMask(void);
u8 GbSave_GetSaveState(s32 arg0);
s32 GbSave_GetPortAvailability(s32 arg0);
u8 GbSave_GetPortGame(s32 arg0);
s32 GbSave_RefreshPlayerIdentity(s32 arg0);
void GbSave_CopyPlayerIdentity(s32 arg0, void* arg1);
s32 GbSave_GetTrainerId(s32 arg0);
void GbSave_SetTrainerId(s32 arg0, u16 arg1);
s32 GbSave_GetBoxCount(s32 arg0);
s32 GbSave_SavedAtPokemonCenter(s32 arg0);
s32 GbSave_HasPokedex(s32 arg0);
s32 GbSave_CopyPortSnapshot(s32 arg0, GbSavePortSnapshot* arg1);
void GbSave_MarkSpeciesHeld(char* arg0, s32 arg1, u8* arg2);
void GbSave_RebuildHeldSpecies(s32 arg0);
s32 GbSave_GetSpeciesProgressLevel(s32 arg0, s32 arg1);
s32 GbSave_CountSeenSpecies(s32 arg0);
s32 GbSave_CountOwnedSpecies(s32 arg0);
s32 GbSave_CountHeldSpecies(s32 arg0);
s32 func_80022B40();                                /* extern */
s32 func_8002207C(s32);

// functions defined in assembly
char* GbSave_GetPlayerName(s32 arg0, char* arg1);
void GbSave_SetSeenOwnedBits(s32 arg0, s32 arg1, s32 arg2);

#endif // POKEMON_STATS_H
