#ifndef _373A0_H_
#define _373A0_H_

#include "global.h"

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

extern unk_D_800FC6CC* D_800B41E4;
extern u8* D_800B41E8;
extern unk_D_800FC6D4* D_800FD688;
extern s16* D_800B41EC;

extern u32* gAudioRegions;

s32 Audio_PlayCommand(u32 arg0, s32 arg1, s32 arg2);
void func_80056950(void);
void Audio_CreateFrameTaskWrapper(void* arg0);
void Audio_RelocateOffsets(u32* arg0, u32 arg1, s32 arg2);

#endif // _373A0_H_
