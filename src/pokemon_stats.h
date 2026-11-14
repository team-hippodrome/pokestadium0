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

// The cached trainer of a port (GbSave_RefreshPlayerIdentity, GbSave_CopyPlayerIdentity).
typedef struct GbSavePlayerIdentity {
    /* 0x00 */ u16 playerId; // @unverified: GbSaveMainData.playerId
    /* 0x02 */ u8 playerName[6]; // @unverified: GbSaveMainData.playerName; a 0x50 terminator when no save (GbSave_ScanAllPorts)
} GbSavePlayerIdentity; // size = 0x8

// Zero's per-port Game Boy save state (sGbSavePorts, D_800AD210); Stadium 1's is 0x58 bytes.
typedef struct GbSavePort {
    /* 0x00 */ u16 flags; // @unverified: 1 main data loaded, 2 box data loaded, 0x20 take the next checksum read as the reference (GbSave_ReadMainData), 0x4000 saved at a Pokemon Center
    /* 0x02 */ u8 gameType; // PokemonRomType (GbCart_IdentifyGame), @unverified
    /* 0x03 */ u8 saveState; // @unverified: GbSave_ScanAllPorts: 0 loaded, 1 no cartridge, 2 not a Pokemon cartridge, 3 main data unreadable
    /* 0x04 */ u8 checksum; // @unverified: the save checksum when read (GbSave_ReadMainData); later reads must match
    /* 0x05 */ u8 heldSpecies[19]; // one bit per species held in the party or boxes (GbSave_RebuildHeldSpecies, GbSave_CountHeldSpecies)
    /* 0x18 */ u8 pakId[0x20]; // @unverified: identifies the cartridge across a removal (GbTower_ProbePak, GbTower_VerifyPakStillInserted)
    /* 0x38 */ GbSavePlayerIdentity identity;
    /* 0x40 */ GbSaveMainData* mainData; // @unverified: 0x1020 bytes from SRAM 0x2580, allocated as 'DAT0'+port (GbSave_OpenMainData)
    /* 0x44 */ u8* boxData; // @unverified: two 0x15A0-byte box banks from SRAM 0x4000 and 0x6000, four GbSaveBox each, allocated as 'BOX0'+port (GbSave_OpenBoxData)
} GbSavePort; // size = 0x48

// A copy of a port's save summary (GbSave_CopyPortSnapshot).
typedef struct GbSavePortSnapshot {
    /* 0x000 */ u8 gameType; // @unverified: GbSavePort.gameType
    /* 0x001 */ u8 checksum; // @unverified: GbSavePort.checksum
    /* 0x002 */ u16 playerId; // @unverified: GbSavePort.identity.playerId
    /* 0x004 */ u8 playerName[6]; // @unverified: GbSavePort.identity.playerName
    /* 0x00A */ GbSaveParty party; // @unverified: GbSaveMainData.party
} GbSavePortSnapshot; // size = 0x162

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
GbSaveBox* GbSave_GetBoxEntry(s32 arg0, s32 arg1);
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
