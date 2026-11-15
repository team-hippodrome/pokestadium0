/* Declarations for src/display_object_textures.c. */
#ifndef DISPLAY_OBJECT_TEXTURES_H
#define DISPLAY_OBJECT_TEXTURES_H

#include "global.h"
#include "asset_archive.h"
#include "memory.h"

typedef struct unk_func_80019600 {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ OSMesgQueue* queue;
    /* 0x08 */ void* unk_08;
    /* 0x0C */ void* unk_0C;
    /* 0x10 */ MainPoolState* pool;
    /* 0x14 */ s32 size;
    /* 0x18 */ arg1_func_80010CA8 unk_18;
} unk_func_80019600; // size >= 0x1C

typedef struct sp18_func_800198E4 {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ u16 unk_02;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ s32 unk_14;
    /* 0x18 */ arg1_func_80010CA8 unk_18;
} sp18_func_800198E4; // size = 0x1C

typedef struct unk_D_800ABE10_A04 {
    /* 0x00 */ BinArchive* unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ BinArchive* unk_10;
} unk_D_800ABE10_A04; // size >= 0x14

typedef struct unk_D_800ABE10 {
    /* 0x000 */ OSThread unk_000;
    /* 0x1B0 */ char unk1B0[0x800];
    /* 0x9B0 */ OSMesg unk_9B0;
    /* 0x9B4 */ char unk9B4[0x1C];
    /* 0x9D0 */ OSMesgQueue unk_9D0;
    /* 0x9E8 */ OSMesg unk_9E8;
    /* 0x9EC */ OSMesgQueue unk_9EC;
    /* 0xA04 */ unk_D_800ABE10_A04 unk_A04;
} unk_D_800ABE10; // size >= 0xA18

#include "game_state.h"
#include "memmap.h"

extern unk_D_800ABE10 D_800AC7A0;

// display_object_textures.c
void func_80016D40(unk_D_86002F34* arg0, arg1_func_80010CA8 arg1);
Fragment* Jpeg_AllocAndDecodeFragment(MemoryBlock* arg0, PRESJPEG* arg1, PRESJPEG* arg2);
Fragment* Yay0_AllocAndDecompressFragment(MainPoolState* arg0, PERSSZP* arg1, PERSSZP* arg2);
Fragment* Asset_AllocAndCopyFragment(MainPoolState* arg0, PERSSZP* arg1, s32 arg2, u32 arg3);
Fragment* Fragment_LoadFromRomRange(MainPoolState* arg0, s32 start, s32 end, PERSSZP* arg3, s32 arg4);
Fragment* Fragment_LoadFromLbaRange(MainPoolState* arg0, unk_func_800041C0* arg1, PERSSZP* arg2, u32 arg3);
void Fragment_RelocateAndCommit(MainPoolState* arg0, u32 arg1, Fragment* arg2);
Fragment* BinArchive_LoadFileFromRomRange(MainPoolState* arg0, BinArchive* arg1, BinArchiveFile* arg2, u32 arg3, s32 arg4);
Fragment* BinArchive_LoadFileFromLbaRange(MainPoolState* arg0, BinArchive* arg1, BinArchiveFile* arg2, u32 arg3, s32 arg4);
Fragment* BinArchive_LoadFileToPool(MainPoolState* arg0, BinArchive* arg1, s32 arg2, u32 arg3, s32 arg4);
s32 Fragment_ProcessGeoLayout(MemoryBlock* arg0, Fragment* arg1, arg1_func_80010CA8 arg2);
void Fragment_ProcessGeoLayoutList(MemoryBlock* arg0, arg1_func_80019420* arg1);
void PokeIcon_LoadModelArchive(unk_func_80019600* arg0);
void PokeIcon_LoadMultipleModels(unk_func_80019600* arg0);
void PokeIcon_ThreadMain(UNUSED void* arg0);
void PokeIcon_StartThread(void);
s8 *PokeIcon_AllocFramebuffers(s32 arg0);
void PokeIcon_OpenModelArchives(void);
s32 PokeIcon_RequestFrameLoad(ModelLoadContext* arg0, u16 arg1, arg1_func_80010CA8 arg2);
s32 PokeIcon_RequestBackgroundLoad(ModelLoadContext* arg0, s32 arg1, s32 arg2);
s32 PokeIcon_ApplyLoadResult(ModelLoadContext* arg0, sp18_func_800198E4* arg1);
s32 PokeIcon_PollFrameLoad(ModelLoadContext* arg0);
s32 PokeIcon_PollBackgroundLoad(ModelLoadContext* arg0);
void PokeIcon_WaitBackgroundLoad(s32 arg0);
unk_D_86002F30* Model_LoadByArchiveIndex(s32 arg0);
unk_D_86002F30* Model_LoadForPokemon(BattleMon* arg0);
arg1_func_80019420* BattleAnim_LoadResourceTable(s32 arg0);
Fragment* Fragment_LoadAndRelocateFromRomRange(MainPoolState* arg0, u32 arg1, s32 arg2, s32 arg3, PERSSZP* arg4, s32 arg5);

// functions defined in assembly
s32 PokeIcon_WaitFrameLoad(ModelLoadContext* arg0);

#endif // DISPLAY_OBJECT_TEXTURES_H
