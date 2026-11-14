/* Declarations for src/save_data.c. */
#ifndef SAVE_DATA_H
#define SAVE_DATA_H

#include "global.h"
#include "stdarg.h"
#include "moves.h"
#include "m2c_macros.h"
#include "gb_data.h"
#include "pokemon_stats.h"

typedef struct GameOptions {
    /* 0x00 */ s16 gbTowerUnlockTier; // 0 = normal, 1 = Doduo, 2 = Dodrio.
    // Word carried into/out of GB Tower by State_GbTower; its pointer role is unknown.
    /* 0x04 */ struct GameOptions* unk_04;
} GameOptions; // size = 0x8

typedef struct ModeSettings {
    /* 0x00 */ u16 clearedModes; // Bit (1 << session mode); Mewtwo victory is bit 8.
    /* 0x02 */ char unk02[0x2];
    /* 0x04 */ u8 castleClears; // Highest completed castle location + 1, capped at 8.
    /* 0x05 */ u8 nintendoCupClears; // Highest completed division + 1, capped at 4.
    /* 0x06 */ u8 primeCupClears; // Highest completed division + 1, capped at 4.
    /* 0x07 */ u8 mewtwoUnlocked; // Set when clearedModes reaches 0xF8.
} ModeSettings; // size = 0x8

// Zero's 32 KiB cartridge SRAM, loaded whole into the buffer at D_800AE8E0
// (docs/n64-save-format.md). Every record is stored twice, primary then backup,
// and each copy ends with a SaveFooter. Fields without a tag were seen in play in pj64
// (2026-11-14: a team registered in とうろく, a Pokemon and items moved in せいとん, the
// sound options toggled, then the buffer read back and the footer sums recomputed).

// "POKE" and a u16 sum of every byte of the copy before it; "XXXX" and sum ^ 0xFF
// when invalidated. Written by Save_WriteFooter, checked by Save_RecordIsValid.
typedef struct SaveFooter {
    /* 0x0 */ u8 magic[4]; // "POKE" in every committed copy seen
    /* 0x4 */ u16 checksum; // Sum of every byte of the copy before it; recomputed from a box, team and item copy
} SaveFooter; // size = 0x6

// A Pokemon as kept in Zero's save: the Gen 1 box struct plus its names in the GB charset.
// Read by func_80023D3C and written by BattleMon_ToGbSaveRecord.
typedef struct SaveMonRecord {
    /* 0x00 */ GbPokemonRecord mon;
    /* 0x21 */ u8 nickname[6];
    /* 0x27 */ u8 otName[6];
} SaveMonRecord; // size = 0x2D

// Flags bit 0: present (teams set it when registered), bit 1: dirty.
typedef struct SaveTeamRecord {
    /* 0x000 */ s16 flags;
    /* 0x002 */ u8 trainerName[6]; // GB charset, 0x50-terminated.
    /* 0x008 */ u16 trainerId;
    /* 0x00A */ u8 secondName[8]; // @unverified: written by Deck_SetSaveEntryTrainerIdAndName, empty in every record seen
    /* 0x012 */ s16 count;
    /* 0x014 */ SaveMonRecord mons[6];
    /* 0x122 */ SaveFooter footer;
} SaveTeamRecord; // size = 0x128

typedef struct SaveBoxRecord {
    /* 0x000 */ s16 flags;
    /* 0x002 */ u8 trainerName[6]; // Empty in boxes.
    /* 0x008 */ u16 trainerId;
    /* 0x00A */ u8 secondName[8]; // @unverified: written by Deck_SetSaveEntryTrainerIdAndName, empty in every record seen
    /* 0x012 */ s16 count;
    /* 0x014 */ SaveMonRecord mons[30];
    /* 0x55A */ SaveFooter footer;
} SaveBoxRecord; // size = 0x560

typedef struct SaveItemSlot {
    /* 0x0 */ u8 id;
    /* 0x1 */ u8 quantity;
} SaveItemSlot; // size = 0x2

// One per trainer; the record whose name and ID match the cartridge is shown.
typedef struct SaveItemRecord {
    /* 0x00 */ s16 flags;
    /* 0x02 */ u8 trainerName[6];
    /* 0x08 */ u16 trainerId;
    /* 0x0A */ s16 count;
    /* 0x0C */ SaveItemSlot items[100];
    /* 0xD4 */ char unk_D4[0x6];
    /* 0xDA */ SaveFooter footer;
} SaveItemRecord; // size = 0xE0

// No screen using it was found; never written in play.
typedef struct SaveListRecord {
    /* 0x0000 */ s16 flags; // @unverified: bit 0 set on reset (Save_ClearTypedRecord)
    /* 0x0002 */ s16 count; // @unverified: Deck_SetSaveEntryCount
    /* 0x0004 */ SaveMonRecord mons[100]; // @unverified: Deck_ReadSaveEntry, Save_WriteTypedRecord
    /* 0x1198 */ char unk_1198[0x2];
    /* 0x119A */ SaveFooter footer;
} SaveListRecord; // size = 0x11A0

typedef struct SaveOptionsRecord {
    /* 0x0 */ s16 flags;
    /* 0x2 */ s8 towerFrames; // @unverified: per docs/n64-save-format.md, not rechecked. GB Tower picture frames unlocked: 0-2 (1 Doduo, 2 Dodrio).
    /* 0x3 */ u8 soundFlags; // Bit 0 mono sound, bit 1 commentary off.
    /* 0x4 */ s32 towerButtons; // @unverified: per docs/n64-save-format.md, not rechecked; 0 (START S, SELECT L) seen. GB Tower config: bits 8-15 START button, bits 0-7 SELECT button - 1.
    /* 0x8 */ u8 progress[2]; // @unverified: per docs/n64-save-format.md, not rechecked. Big-endian u16 (Save_GetProgressFlags): high byte bit 0 L50-55 won (code), bit 1 Master Ball Cup won; low byte L1-30 cups cleared.
    /* 0xA */ SaveFooter footer;
} SaveOptionsRecord; // size = 0x10

// Where a paused tournament stands; built by func_80025830 from gSessionContext.
typedef struct SaveContinueSession {
    /* 0x0 */ u8 mode; // @unverified: per docs/n64-save-format.md, not rechecked. 1 L50-55, 2 L1-30 cups.
    /* 0x1 */ u8 modeSelection; // @unverified: per docs/n64-save-format.md, not rechecked. Cup (0 Monster Ball Cup).
    /* 0x2 */ u8 round; // @unverified: per docs/n64-save-format.md, not rechecked. Next round: 3 after two wins.
    /* 0x3 */ u8 pad03; // @unverified: per docs/n64-save-format.md, not rechecked. Stack garbage.
    /* 0x4 */ u8 opponentHistory[8]; // @unverified: per docs/n64-save-format.md, not rechecked. Opponents faced so far.
} SaveContinueSession; // size = 0xC

// Tournament continue data, written at the continue-tournament prompt and read at the
// main menu. Cleared (flags 0) when the tournament is won.
typedef struct SaveContinueRecord {
    /* 0x000 */ s16 flags;
    /* 0x002 */ SaveContinueSession session;
    /* 0x00E */ s16 count;
    /* 0x010 */ SaveMonRecord team[6];
    /* 0x11E */ GbSavePortSnapshot gbSnapshot; // @unverified: per docs/n64-save-format.md, not rechecked. All zero for rentals; a GB team resumes only if the cartridge still matches.
    /* 0x280 */ u8 speciesFlagMask; // @unverified: bit n set when team[n]'s BattleMon.species.unk_01 == 1 (Save_WriteContinueData)
    /* 0x281 */ char unk_281[0x1];
    /* 0x282 */ SaveFooter footer;
} SaveContinueRecord; // size = 0x288

typedef struct SaveSram {
    /* 0x0000 */ SaveTeamRecord teams[16][2]; // Kind 16.
    /* 0x2500 */ SaveBoxRecord boxes[4][2]; // Kind 17.
    /* 0x5000 */ SaveItemRecord items[4][2]; // Kind 18.
    /* 0x5700 */ SaveListRecord list[2]; // Kind 19.
    /* 0x7A40 */ SaveOptionsRecord options[2]; // Kind 20.
    /* 0x7A60 */ SaveContinueRecord continueData[2]; // Kind 21.
    /* 0x7F70 */ char unk_7F70[0x90];
} SaveSram; // size = 0x8000

// save_data.c
u16 Save_Checksum(u8* arg0, s32 arg1);
s32 Save_RecordIsValid(u8* arg0, s32 arg1);
void Save_WriteFooter(u8* arg0, s32 arg1, s32 arg2);
s32 Save_IsTypedRecordFlagSet(s32 arg0, s32 arg1, s16 arg2);
void Save_CommitTypedRecord(s32 arg0, s32 arg1);
void Save_InvalidateTypedRecord(s32 arg0, s32 arg1);
void Save_ClearTypedRecord(s32 arg0, s32 arg1);
void Save_ResetAndCommitTypedRecord(s32 arg0, s32 arg1);
s32 Deck_GetSaveRecordCapacity(s32 arg0);
s32 Deck_GetSaveRecordSize(s32 arg0);
s32 Deck_IsSaveEntryPresent(s32 arg0, s32 arg1);
s32 Deck_GetSaveEntryTrainerId(s32 arg0, s32 arg1);
s32 Deck_GetSaveEntryName(s32 arg0, s32 arg1, u8* arg2);
void Deck_SetSaveEntryTrainerIdAndName(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u16 arg4);
void Deck_SetSaveEntryCount(s32 arg0, s32 arg1, s32 arg2);
s32 Deck_ReadSaveEntry(s32 arg0, s32 arg1, s32 arg2, u8* arg3);
s32 Save_WriteTypedRecord(s32 arg0, s32 arg1, s32 arg2, u8* arg3);
void Save_WriteContinueData(SaveContinueSession* arg0, GbSavePortSnapshot* arg1, BattleMon* arg2, s32 arg3);
void func_80024044(void);
s32 Audio_GetFreeVoiceCount(void);
void func_800245E0(s32 arg0, s32 arg1);

// functions defined in assembly
s16 Deck_GetSaveEntryCount(s32 arg0, s32 arg1);

#endif // SAVE_DATA_H
