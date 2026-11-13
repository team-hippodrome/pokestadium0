/* Declarations for src/audio_commands.c, src/audio_commands_2.c, src/audio_commands_3.c, src/audio_commands_4.c. */
#ifndef AUDIO_COMMANDS_H
#define AUDIO_COMMANDS_H

#include "global.h"
#include "m2c_macros.h"
#include "stdarg.h"
#include "moves.h"

#ifdef M2C
#define ENTRY_SIZE 1
#else
#define ENTRY_SIZE
#endif

typedef struct File1Header {
    /* 0x00 */ u32 offset1;
    /* 0x04 */ u32 wave_tables_offset;
    /* 0x08 */ u32 num_files;
    /* 0x0C */ u32 files[1];
} File1Header; // size >= 0x10

typedef struct File2SubHeader1 {
    /* 0x00 */ u32 offset1;
    /* 0x04 */ u32 offset2;
    /* 0x08 */ u32 wave_tables_offset;
} File2SubHeader1; // size = 0xC

typedef struct File2SubHeader2 {
    /* 0x00 */ u32 num_files;
    /* 0x04 */ u32 offset1;
    /* 0x08 */ u32 wave_tables_offset;
} File2SubHeader2; // size = 0xC

typedef union {
    File1Header file1;
    ALSeqFile seq;
    File2SubHeader2 file2sub2;
} FileHeaders;

typedef struct unk_D_800FC6CC {
    /* 0x00 */ u32 unk_00;
    /* 0x04 */ u32 unk_04;
} unk_D_800FC6CC; // size = 0x8

typedef struct unk_D_800FC6D4_entry {
    /* 0x00 */ u16 unk_00;
    /* 0x02 */ u8 unk_02;
    /* 0x03 */ u8 unk_03;
} unk_D_800FC6D4_entry; // size = 0x4

typedef struct unk_D_800FC6D4_008 {
    /* 0x00 */ u32 unk_00;
    /* 0x04 */ u8 unk_04;
} unk_D_800FC6D4_008; // size = 0x5

typedef struct unk_D_800FC6D4 {
    /* 0x00 */ u16 flags;
    /* 0x02 */ u16 num_entries;
    /* 0x04 */ u16 unk_04;
    /* 0x06 */ u16 unk_06;
    /* 0x08 */ unk_D_800FC6D4_008* offset;
    /* 0x0C */ char unk_0C[0x4];
    /* 0x10 */ unk_D_800FC6D4_entry entries[ENTRY_SIZE];
} unk_D_800FC6D4; // size = 0x10

typedef struct MoveSoundEntry { u8 unk0[0x6]; } MoveSoundEntry;

typedef struct MoveSoundTable { u8 header[0x10]; MoveSoundEntry entries[1]; } MoveSoundTable;

/* Struct types that were defined identically in each of these files; this is
 * now the one definition they all include:
 * src/audio_commands.c
 * src/audio_commands_2.c
 */

typedef struct unk_D_80077970 {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ u8 unk_02;
    /* 0x03 */ u8 unk_03;
    /* 0x04 */ u8 unk_04;
} unk_D_80077970;

extern unk_D_800FC6CC* D_800B41E4;

extern u8* D_800B41E8;

extern unk_D_800FC6D4* D_800FD688;

extern s16* D_800B41EC;

extern u32* gAudioRegions;

// audio_commands.c
void Audio_CreateFrameTaskWrapper(void* arg0);
void Audio_RelocateOffsets(u32* arg0, u32 arg1, s32 arg2);
void Audio_FadeAndClearStoredSounds(void);
M2C_UNK func_8003F6AC(M2C_UNK);                     /* extern */

// audio_commands_2.c
s32 Audio_PlayCommand(u32 arg0, s32 arg1, s32 arg2);

// audio_commands_4.c
void Audio_UpdateBattleAudioFrame(void);
s32 Audio_LoadWaveTablesAndMusic(u8*);
void Audio_ClearWaveDataLoaded(void);
void func_80043A10(void);

// libultra/audio/synthesizer.c
void func_80056950(void);

#endif // AUDIO_COMMANDS_H
