#ifndef TYPES_GB_TOWER_EMULATOR_86920_TYPES_H
#define TYPES_GB_TOWER_EMULATOR_86920_TYPES_H

/* Struct types that were defined identically in each of these files; this is
 * now the one definition they all include:
 * src/fragments/fragment000_80C00/gb_tower_emulator_86920.c
 * src/fragments/fragment000_80C00/gb_tower_emulator_86920_8110B880.c
 */

typedef struct unk_func_81206FA0 {
  /* 0x00 */ s32 unk_00;
  /* 0x04 */ s32 unk_04;
  /* 0x08 */ s32 unk_08;
  /* 0x0C */ s32 unk_0C;
} unk_func_81206FA0;

typedef struct unk_D_812346E0 {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
} unk_D_812346E0;

typedef struct unk_D_81231450 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
} unk_D_81231450;

typedef struct unk_D_81234650 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
} unk_D_81234650;

typedef struct Rec81109678Flags {
    /* 0x0 */ u8 bit7 : 1;
    /* 0x0 */ u8 bit6 : 1;
    /* 0x0 */ u8 rest : 6;
} Rec81109678Flags;

typedef struct Rec81109678 {
    /* 0x00 */ u8 pad00[0x30];
    /* 0x30 */ u8 unk_30;
    /* 0x31 */ u8 pad31[2];
    /* 0x33 */ u8 unk_33;
    /* 0x34 */ u8 unk_34;
    /* 0x35 */ u8 pad35[0x44 - 0x35];
    /* 0x44 */ Rec81109678Flags* unk_44;
    /* 0x48 */ u8 pad48[0x5C - 0x48];
    /* 0x5C */ u8 unk_5C;
    /* 0x5D */ u8 unk_5D;
    /* 0x5E */ u8 pad5E[0x6C - 0x5E];
    /* 0x6C */ f32 unk_6C;
    /* 0x70 */ u8 pad70[0xB4 - 0x70];
    /* 0xB4 */ u32 enabled : 1;
    /* 0xB4 */ u32 restB4 : 31;
    /* 0xB8 */ u8 padB8[0xCC - 0xB8];
} Rec81109678; // size = 0xCC

typedef struct CacheEntry81109C0C {
    /* 0x00 */ u8* ramAddr;
    /* 0x04 */ u32 size;
    /* 0x08 */ s16 tableType;
    /* 0x0A */ s16 id;
} CacheEntry81109C0C; // size = 0xC

typedef struct Pool81109C0C {
    /* 0x00 */ u8* startRamAddr;
    /* 0x04 */ u8* curRamAddr;
    /* 0x08 */ s32 size;
    /* 0x0C */ s32 numEntries;
} Pool81109C0C; // size = 0x10

typedef struct SeqPlayer81109C0C {
    /* 0x000 */ u32 enabled : 1;
    /* 0x000 */ u32 rest0 : 31;
    /* 0x004 */ u8 seqId;
    /* 0x005 */ u8 pad5[0x15C - 0x5];
} SeqPlayer81109C0C; // size = 0x15C

typedef struct Entry8110A368 { s32 val; char pad4[6]; s16 key; } Entry8110A368;

typedef struct Tbl8110A368 { u32 count; char pad4[0x10]; Entry8110A368 entries[1]; } Tbl8110A368;

typedef struct Voice8110AA50 {
    /* 0x000 */ char unk000[0xC];
    /* 0x00C */ u16 unk_0C;
    /* 0x00E */ char unk00E[0x14A];
} Voice8110AA50; // size = 0x158

typedef struct ReverbSettingsAFF0 {
    /* 0x00 */ u8 downsampleRate;
    /* 0x01 */ u8 windowSize;
    /* 0x02 */ u16 decayRatio;
    /* 0x04 */ u16 unk_4;
    /* 0x06 */ u16 unk_6;
    /* 0x08 */ u16 unk_8;
    /* 0x0A */ s8 unk_A;
    /* 0x0C */ u16 unk_C;
    /* 0x0E */ s16 lowPassFilterCutoffLeft;
    /* 0x10 */ s16 lowPassFilterCutoffRight;
} ReverbSettingsAFF0; // size = 0x12

typedef struct AudioSpecAFF0 {
    /* 0x00 */ u32 frequency;
    /* 0x04 */ u8 unk_04;
    /* 0x05 */ u8 numNotes;
    /* 0x06 */ u8 numSequencePlayers;
    /* 0x07 */ u8 numReverbs;
    /* 0x08 */ ReverbSettingsAFF0* reverbSettings;
    /* 0x0C */ u16 unk_0C;
    /* 0x10 */ s32 persistentSeqMem;
    /* 0x14 */ s32 persistentFontMem;
    /* 0x18 */ s32 persistentSampleMem;
    /* 0x1C */ s32 temporarySeqMem;
    /* 0x20 */ s32 temporaryFontMem;
    /* 0x24 */ s32 temporarySampleMem;
    /* 0x28 */ s32 persistentSampleCacheSize;
    /* 0x2C */ s32 temporarySampleCacheSize;
} AudioSpecAFF0; // size = 0x30

typedef struct LoopAFF0 {
    /* 0x00 */ u32 start;
    /* 0x04 */ u32 end;
    /* 0x08 */ u32 count;
} LoopAFF0;

typedef struct SampleAFF0 {
    /* 0x00 */ u32 codec : 4;
    /* 0x00 */ u32 medium : 2;
    /* 0x00 */ u32 unk_bit26 : 1;
    /* 0x00 */ u32 unk_bit25 : 1;
    /* 0x01 */ u32 size : 24;
    /* 0x04 */ s16* sampleAddr;
    /* 0x08 */ struct LoopAFF0* loop;
    /* 0x0C */ void* book;
} SampleAFF0; // size = 0x10

typedef struct ReverbItemAFF0 {
    /* 0x00 */ s16 numSamplesAfterDownsampling;
    /* 0x02 */ s16 chunkLen;
    /* 0x04 */ s16* toDownsampleLeft;
    /* 0x08 */ s16* toDownsampleRight;
    /* 0x0C */ u8 unk0C[8];
} ReverbItemAFF0; // size = 0x14

typedef struct SynthesisReverbAFF0 {
    /* 0x000 */ u8 resampleFlags;
    /* 0x001 */ u8 useReverb;
    /* 0x002 */ u8 framesToIgnore;
    /* 0x003 */ u8 curFrame;
    /* 0x004 */ u8 downsampleRate;
    /* 0x005 */ s8 unk_05;
    /* 0x006 */ u16 windowSize;
    /* 0x008 */ u16 unk_08;
    /* 0x00A */ u16 unk_0A;
    /* 0x00C */ u16 decayRatio;
    /* 0x00E */ s16 unk_0E;
    /* 0x010 */ u16 unk_10;
    /* 0x012 */ u16 unk_12;
    /* 0x014 */ s32 nextRingBufPos;
    /* 0x018 */ s32 unk_18;
    /* 0x01C */ s32 bufSizePerChan;
    /* 0x020 */ s16* leftRingBuf;
    /* 0x024 */ s16* rightRingBuf;
    /* 0x028 */ void* unk_28;
    /* 0x02C */ void* unk_2C;
    /* 0x030 */ void* unk_30;
    /* 0x034 */ void* unk_34;
    /* 0x038 */ ReverbItemAFF0 items[2][5];
    /* 0x100 */ s16* filterLeft;
    /* 0x104 */ s16* filterRight;
    /* 0x108 */ s16* filterLeftState;
    /* 0x10C */ s16* filterRightState;
    /* 0x110 */ SampleAFF0* soundSample;
    /* 0x114 */ f32 soundTuning;
    /* 0x118 */ SampleAFF0 sample;
    /* 0x128 */ LoopAFF0 loop;
    /* 0x134 */ u8 unk134[0x158 - 0x134];
} SynthesisReverbAFF0; // size = 0x158

typedef struct SessionSplitAFF0 {
    /* 0x00 */ s32 miscPoolSize;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 cachePoolSize;
} SessionSplitAFF0;

typedef struct PoolAFF0 {
    /* 0x00 */ u8* start;
    /* 0x04 */ u8* cur;
    /* 0x08 */ s32 size;
    /* 0x0C */ s32 count;
} PoolAFF0;

#endif /* TYPES_GB_TOWER_EMULATOR_86920_TYPES_H */
