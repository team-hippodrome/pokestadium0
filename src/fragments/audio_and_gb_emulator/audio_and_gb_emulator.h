/* Declarations for the audio_and_gb_emulator fragment (src/fragments/audio_and_gb_emulator/). */
#ifndef FRAGMENT_AUDIO_AND_GB_EMULATOR_H
#define FRAGMENT_AUDIO_AND_GB_EMULATOR_H

#include "global.h"
#include "m2c_macros.h"

/* Struct types that were defined identically in each of these files; this is
 * now the one definition they all include:
 * src/fragments/fragment000_80C00/gb_tower_emulator_7F9A0.c
 * src/fragments/fragment000_80C00/gb_tower_emulator_7F9A0_81102C20.c
 */

typedef struct unk_D_8122C4FA {
  /* 0x00 */ u8 unk_00;
  /* 0x01 */ u8 unk_01;
} unk_D_8122C4FA;

typedef struct unk_D_8122B2F8 {
  /* 0x000000 */ char unk000000[0x1FEAE8];
} unk_D_8122B2F8;

typedef struct unk_D_8122B1E8 {
  /* 0x00 */ OSMesg mesg[1];
  /* 0x04 */ OSMesgQueue queue;
  /* 0x1C */ char unk1C[0x4];
  /* 0x20 */ s32 unk_20;
  /* 0x24 */ s32 unk_24;
  /* 0x28 */ void* unk_28;
  /* 0x2C */ s32 unk_2C;
  /* 0x30 */ char unk30[0x8];
  /* 0x38 */ s32 unk_38;
  /* 0x3C */ s32 unk_3C;
  /* 0x40 */ void* unk_40;
  /* 0x44 */ char unk44[0x4];
  /* 0x48 */ void* unk_48;
  /* 0x4C */ void* unk_4C;
  /* 0x50 */ u32 unk_50;
  /* 0x54 */ s32 unk_54;
  /* 0x58 */ void* unk_58;
  /* 0x5C */ s32 unk_5C;
  /* 0x60 */ char unk60[0x8];
} unk_D_8122B1E8;

typedef struct unk_D_8120D7F3 {
    u8 pad[0x116];
    u8 unk116;
} unk_D_8120D7F3;

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

typedef struct GbApuChannelState {
  /* 0x00 */ u8 unk_00;
  /* 0x02 */ char unk02[0x02];
  /* 0x04 */ s32 unk_04;
  /* 0x08 */ union {
      u16 unk_00;
      s32 unk_02;
  } unk_08;
  /* 0x0C */ u32 unk_0C;
  /* 0x10 */ u16 unk_10;
  /* 0x12 */ u16 unk_12;
  /* 0x14 */ s32 unk_14;
  /* 0x18 */ s32 unk_18;
  /* 0x1C */ s32 unk_1C;
  /* 0x20 */ u8 unk_20;
  /* 0x21 */ u8 unk_21;
  /* 0x22 */ char unk22[0x2];
  /* 0x24 */ u32 unk_24;
  /* 0x28 */ u32 unk_28;
  /* 0x2C */ char unk2C[0x1];
  /* 0x2D */ u8 unk_2D;
  /* 0x2E */ u8 unk_2E;
  /* 0x2F */ char unk2F[0x1];
  /* 0x30 */ u32 unk_30;
  /* 0x34 */ u32 unk_34;
  /* 0x38 */ u8 unk_38;
  /* 0x39 */ u8 unk_39;
  /* 0x3A */ u8 unk_3A;
  /* 0x3B */ u8 unk_3B;
  /* 0x3C */ u8 unk_3C;
  /* 0x3D */ char unk3D[0x3];
  /* 0x40 */ u32 unk_40;
  /* 0x44 */ u16 unk_44;
  /* 0x46 */ u16 unk46;
  /* 0x48 */ u32 unk_48;
  /* 0x4C */ u8 unk_4C;
  /* 0x4D */ char unk4D[0x3];
} GbApuChannelState;

typedef struct unk_D_8122EEA8 {
  /* 0x00 */ u8 unk_00;
  /* 0x01 */ u8 unk_01;
  /* 0x02 */ u8 unk_02;
  /* 0x03 */ u8 unk_03;
} unk_D_8122EEA8;

typedef struct GbApuRegs {
    /* 0x00 NR10 */ u32 : 1;
                    u32 sweepTime : 3;
                    u32 sweepDir : 1;
                    u32 sweepShift : 3;
    /* 0x01 NR11 */ u32 duty1 : 2;
                    u32 length1 : 6;
    /* 0x02 NR12 */ u32 volume1 : 4;
                    u32 envDir1 : 1;
                    u32 envSweep1 : 3;
    /* 0x03 NR13 */ u32 freqLo1 : 8;
    /* 0x04 NR14 */ u32 trigger1 : 1;
                    u32 counter1 : 1;
                    u32 : 3;
                    u32 freqHi1 : 3;
    /* 0x05 */      u32 : 8;
    /* 0x06 NR21 */ u32 duty2 : 2;
                    u32 length2 : 6;
    /* 0x07 NR22 */ u32 volume2 : 4;
                    u32 envDir2 : 1;
                    u32 envSweep2 : 3;
    /* 0x08 NR23 */ u32 freqLo2 : 8;
    /* 0x09 NR24 */ u32 trigger2 : 1;
                    u32 counter2 : 1;
                    u32 : 3;
                    u32 freqHi2 : 3;
    /* 0x0A NR30 */ u32 waveOn : 1;
                    u32 : 7;
    /* 0x0B NR31 */ u32 length3 : 8;
    /* 0x0C NR32 */ u32 : 1;
                    u32 level3 : 2;
                    u32 : 5;
    /* 0x0D NR33 */ u32 freqLo3 : 8;
    /* 0x0E NR34 */ u32 trigger3 : 1;
                    u32 counter3 : 1;
                    u32 : 3;
                    u32 freqHi3 : 3;
    /* 0x0F */      u32 : 8;
    /* 0x10 NR41 */ u32 : 2;
                    u32 length4 : 6;
    /* 0x11 NR42 */ u32 volume4 : 4;
                    u32 envDir4 : 1;
                    u32 envSweep4 : 3;
    /* 0x12 NR43 */ u16 shift4 : 4;
                    u32 width4 : 1;
                    u32 ratio4 : 3;
    /* 0x13 NR44 */ u32 trigger4 : 1;
                    u32 counter4 : 1;
                    u32 : 6;
    /* 0x14 NR50 */ u32 vinLeft : 1;
                    u32 leftVolume : 3;
                    u32 vinRight : 1;
                    u32 rightVolume : 3;
    /* 0x15 NR51 */ u32 noiseLeft : 1;
                    u32 waveLeft : 1;
                    u32 sq2Left : 1;
                    u32 sq1Left : 1;
                    u32 noiseRight : 1;
                    u32 waveRight : 1;
                    u32 sq2Right : 1;
                    u32 sq1Right : 1;
    /* 0x16 NR52 */ u32 power : 1;
                    u32 : 7;
    /* 0x17 */      u32 : 8;
} GbApuRegs;

#define GB_APU_REGS (*(GbApuRegs*)D_81138A80)

#define GB_APU_WRITE_QUEUE_LEN 1800

typedef struct GbApuWrite {
    /* 0x0 */ u8 reg;
    /* 0x1 */ u8 value;
    /* 0x2 */ u16 time;
} GbApuWrite;

typedef union GbApuMesg {
    OSMesg mesg;
    GbApuWrite write;
} GbApuMesg;

// One Transfer Pak channel of the Game Boy emulator (D_811561C8[4]). Merges the three identical
// copies that gb_emu_draw.c, gb_emu_frame.c and gb_pak.c had.
typedef struct GbPakChannel {
    /* 0x00 */ char unk00[0x48]; // the start of an OSGbpakId (osGbpakReadId in gb_emu_draw.c)
    /* 0x48 */ u8 romSize; // @unverified: OSGbpakId.rom_size; 4 selects a 512 KiB ROM, else 1 MiB (gb_emu_draw.c)
    /* 0x49 */ char unk49[0x3];
    /* 0x4C */ u8 maskRomVersion; // @unverified: OSGbpakId.version; picks the bank list of a game revision (gb_emu_draw.c)
    /* 0x4D */ char unk4D[0x1];
    /* 0x4E */ u8 checksum[2];
    /* 0x50 */ OSPfs* pfs;
    /* 0x54 */ u8* buf;
    /* 0x58 */ u8* romBuf;
    /* 0x5C */ u8* sramBuf;
    /* 0x60 */ volatile u8* bankState;
    /* 0x64 */ volatile u8* sramState;
    /* 0x68 */ u8* bankList;
    /* 0x6C */ u8* bankEntry;
    /* 0x70 */ u8* ramBuf;
    /* 0x74 */ u8* blockState;
    /* 0x78 */ u8* verifyBuf;
    /* 0x7C */ u8* blockDirty;
    /* 0x80 */ s32 size;
    /* 0x84 */ s32 sum;
    /* 0x88 */ char unk88[0x4];
    /* 0x8C */ s32 addr;
    /* 0x90 */ u32 ramSize;
    /* 0x94 */ s32 sramAddr;
    /* 0x98 */ u8 unk98;
    /* 0x99 */ volatile u8 request;
    /* 0x9A */ volatile u8 error;
    /* 0x9B */ u8 status;
    /* 0x9C */ u8 channel;
    /* 0x9D */ char unk9D[0x3];
    /* 0xA0 */ u8 gameIndex; // @unverified: GbPak_IdentifyCartridge, 0 not a supported game; colorIndex is gameIndex - 1
    /* 0xA1 */ u8 unkA1;
    /* 0xA2 */ u8 unkA2;
    /* 0xA3 */ char unkA3[0x1];
} GbPakChannel; // size = 0xA4

typedef struct unk_D_81234690 {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ u16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ s16 unk_0C;
    /* 0x0E */ s16 unk_0E;
    /* 0x10 */ s16 unk_10;
    /* 0x12 */ s16 unk_12;
    /* 0x14 */ s16 unk_14;
    /* 0x16 */ u8 pad16[0x18 - 0x16];
    /* 0x18 */ f32 unk_18;
    /* 0x1C */ f32 unk_1C;
    /* 0x20 */ f32 unk_20;
    /* 0x24 */ f32 unk_24;
    /* 0x28 */ u8 pad28[0x38 - 0x28];
} unk_D_81234690;

typedef struct unk_D_81287B08_jp {
    /* 0x000 */ u8 unk_000;
    /* 0x001 */ u8 unk_001;
    /* 0x002 */ char unk002[0x10];
    /* 0x012 */ s16 unk_012;
    /* 0x014 */ char unk014[0x8];
    /* 0x01C */ f32 unk_01C;
    /* 0x020 */ f32 unk_020;
    /* 0x024 */ f32 unk_024;
    /* 0x028 */ char unk028[0x134];
} unk_D_81287B08_jp;

typedef struct GbAudioStream {
    /* 0x0 */ s32 id;
    /* 0x4 */ s32 pos;
} GbAudioStream;

#define GB_AUDIO_STREAM_DATA ((s8**)D_8115265C)

#define GB_AUDIO_STREAM_SIZE ((s32*)D_81152680)

typedef struct GbStereoSample {
    /* 0x0 */ s16 left;
    /* 0x2 */ s16 right;
} GbStereoSample;

typedef struct Particle31FlagsA {
    u8 b80 : 1;
    u8 b40 : 1;
} Particle31FlagsA;

typedef struct Particle31Flags {
    u8 b80 : 1;
    u8 b40 : 1;
} Particle31Flags;

typedef struct Particle2D68 {
    u8 b80 : 1;
    u8 b40 : 1;
    char pad01[0x1E - 1];
    s16 unk_1E;
    char pad20[0x50 - 0x20];
    s8* unk_50[4];
    s32 unk_60;
    char pad64[0x78 - 0x64];
    u8 unk_78;
} Particle2D68;

typedef struct GbEmuListZ {
    /* 0x00 */ void* next;
    /* 0x04 */ void* prev;
    /* 0x08 */ s32 count;
    /* 0x0C */ s32 unk_0C;
} GbEmuListZ; // size = 0x10

typedef struct GbEmuEntryZ {
    /* 0x00 */ u8 pad00[0x74];
    /* 0x74 */ void* next;
    /* 0x78 */ void* prev;
    /* 0x7C */ struct GbEmuEntryZ* owner;
    /* 0x80 */ s32 unk_80;
} GbEmuEntryZ; // size = 0x84

typedef struct Particle3140 {
    u32 b80 : 1;
    u32 b40 : 1;
    u32 b20 : 1;
    u32 b10 : 1;
    u32 b08 : 1;
    u32 b04 : 1;
    u32 rest : 26;
    char pad04[4];
    u8 unk_08;
    char pad09[0x48 - 0x09];
    struct Particle3140* unk_48;
} Particle3140;

struct SeqPlayer81114B54;

typedef struct Entry811151C8 {
    u32 b80 : 1;
    char pad[0x15C - 4];
} Entry811151C8;

/* Struct types that were defined identically in each of these files; this is
 * now the one definition they all include:
 * src/fragments/fragment000_80C00/gb_tower_emulator_86CB0.c
 * src/fragments/fragment000_80C00/gb_tower_emulator_86CB0_81113A44.c
 */

typedef struct AudioStreamFlags {
    u8 pad0 : 4;
    u8 active : 1;
    u8 pad1 : 3;
} AudioStreamFlags;

/* Struct types that were defined identically in each of these files; this is
 * now the one definition they all include:
 * src/fragments/fragment000_80C00/gb_tower_emulator_86CB0.c
 * src/fragments/fragment000_80C00/gb_tower_emulator_86CB0_81114B54.c
 */

typedef struct Item8111539C {
    /* 0x00 */ u32 active : 1;
    /* 0x00 */ u32 unk00 : 31;
    /* 0x04 */ char unk04[0x48];
    /* 0x4C */ void* owners[2];
} Item8111539C;

// Yay0 files in fragment1_misc_yay0 (retail ROM 0xADC80), named by their retail ROM address.
// Offsets from the segment rather than fixed addresses, so they follow it when an earlier
// segment changes size.
#define D_F4130 (fragment1_misc_yay0_ROM_START + 0x464B0)

#define D_F4920 (fragment1_misc_yay0_ROM_START + 0x46CA0)

#define D_F5450 (fragment1_misc_yay0_ROM_START + 0x477D0)

#define D_FDE40 (fragment1_misc_yay0_ROM_START + 0x501C0)

#define D_102BA0 (fragment1_misc_yay0_ROM_START + 0x54F20)

#include "fragments/battle/battle.h"

extern u8 gGbMemoryMap[];

extern u16 D_81138A96;

extern u32 D_81138A90;

extern s16 D_81180700;

extern s16 D_81180702;

extern u8* D_81180704;

extern GbApuChannelState gGbApuSquare1;

extern GbApuChannelState gGbApuSquare2;

extern GbApuChannelState gGbApuWave;

extern GbApuChannelState gGbApuNoise;

extern GbApuWrite D_81180848[GB_APU_WRITE_QUEUE_LEN];

extern u8 D_81182468[0x40];

extern s32 D_811824A8;

extern unk_D_8122EEA8 D_811824B8;

extern OSMesgQueue D_811824C0;

extern OSMesg D_811824D8[GB_APU_WRITE_QUEUE_LEN + 1];

extern volatile s32 D_811858F0;

extern s32 D_811858F8;

extern s32 D_811858FC;

extern s16* D_811859B8[3];

extern s16 D_811859C4[3];

extern u32 D_811859CC;

extern unk_D_81287B08_jp D_81287B08_jp[];

extern OSMesgQueue* D_812896A0_jp;

extern s32 D_81138A70;

extern u8 D_81138A80[0x10];

extern s32 D_81138AD0;

extern s32 D_81138AD4;

extern s32 D_81138AD8;

extern u16 D_81138ADC[32];

extern u8 D_81138B1C[0x10];

extern u8 D_81138B2C[0x4];

extern u8 D_81138B30[0x10];

extern u8 D_81138B40[0x10];

extern u32 D_81138B50[9];

extern s32 D_81138B80;

extern GbAudioStream D_81138B84;

extern GbAudioStream D_81138B8C;

extern GbAudioStream D_81138B94;

extern u8 D_8115265C[0x24];

extern u8 D_81152680[0x24];

extern struct GbEmuListZ D_81184928;

extern GbEmuEntryZ D_811847C8[1];

extern s16 D_811858CC;

// audio_load_2.c
void func_8110DC90(void);
void func_8110DC98(void);
void func_8110E714(void);
s32 BattleScene_EndStatusAnimationsAndCommit(ActivePokemon* active_pokemon);
s32 BattleAnim_EndSleepStatusAnimation(s32 arg0);
void Battle_ApplyAnimStateEffects(s32 arg0);

// audio_thread.c
s32 Audio_CountCategorySounds(s32 arg0);
void func_8110FD6C(s32 cmd, s32 arg1);
void func_8110FC30(void);
void func_8110FE90(void);
void BattleAnim_DisableEffectSpawning(void);
void BattleAnim_DisableEffectSpawningAlias(void);
void BattleAnim_EffectStartNop(void);
void BattleAnim_ClearEffectStateFlag(void);

// audio_playback.c
void AudioPlayback_ProcessNotes(void);

// audio_seqplayer.c
void AudioSeq_SeqLayerDisable(Particle31FlagsA* arg0);
void AudioSeq_SeqLayerFree(s8** arg0, s32 arg1);
void Particle31_ResetAllSlots(DisplayObject* arg0);
void AudioSeq_SequenceChannelEnable(Particle2D68** arg0, u8 arg1, s32 arg2);
s32 AudioSeq_AudioListPopBack(s8 *arg0);
void AudioSeq_InitLayerFreelist(void);
u8 AudioSeq_ScriptReadU8(u8 **arg0);
s16 AudioSeq_ScriptReadS16(u8** arg0);
void AudioSeq_SeqLayerProcessScriptStep1(Particle3140* arg0);

// audio_seqplayer_2.c
/*
 * func_81113F84
 *
 * Stores (float)arg1 / 127.0f into the float at offset 0x2C of the object
 * arg0 points to.  arg1 is an unsigned byte (the generated code masks it
 * with 0xFF), so the stored value runs from 0.0 to 255/127 (about 2.0);
 * the stored value is 1.0 when arg1 is 127.  What the field at +0x2C
 * represents is not known.
 */
void func_81113F84(u8* arg0, u8 arg1);

// audio_seqplayer_3.c
void func_811155A0(void);
void GbApu_SetActiveFlag(void);
void GbApu_ClearActiveFlag(void);
void func_81215C14_jp(s32 arg0, s32 arg1, u8 arg2);
void func_81215C9C_jp(s32 arg0, s32 arg1);
void func_81115704(void);
void func_81215D0C_jp(s32 arg0, s32 arg1, s32 arg2);
void func_81215D50_jp(void);
void func_81215D8C_jp(s32 arg0, s32 arg1, s32 arg2);
void func_81215DDC_jp(void);
void GbApu_SetNoiseLoopBounds(s32 arg0, s32 arg1);
void func_81114B54(struct SeqPlayer81114B54*);
void func_811151C8(s32 arg0);
void func_81115254(s8 *arg0);

// gb_apu.c
u32 GbApu_FreqToStep(u16 arg0);
u32 GbApu_ConfigureNoiseTable(u16 arg0, u16 arg1, u16 arg2);
u32 GbApu_FreqToStep2x(u16 arg0);
void func_81115AF0(void);
s32 GbApu_GetWaveformSample(u32 arg0, s32 arg1);
u16 GbApu_UpdateSquare1Channel(void);
s32 GbApu_UpdateSquare2Channel(void);
u16 GbApu_UpdateWaveChannel(void);
u16 func_81207C5C_Empty(void);
u16 GbApu_UpdateNoiseChannel(void);
void GbApu_WriteRegister(u16 reg, u8 value);
void GbApu_RenderBuffer(s32 numSamples, s16* out);
void GbApu_QueueRegisterWrite(u16 arg0, u8 arg1, u16 arg2);
void GbApu_ResetChannels(void);
void GbAudio_RampToSilence(void);
void func_811173F4(void);
u8 GbMem_ReadIoRegister(u16 arg0);
void GbAudio_SetMenuSoundMode(s32 arg0);
void GbAudio_PlayMenuSound(s32 arg0);

// gb_apu_2.c
void func_811177E8(s32 numSamples, s16* out);
void func_81117AFC(UNUSED s32 arg0);
void func_81218104_jp(UNUSED s32 arg0);

// functions defined in assembly
void BattleAnim_ClearFreezeStatusAnimation(ActivePokemon* active_pokemon);

#endif // FRAGMENT_AUDIO_AND_GB_EMULATOR_H
