/* Declarations for src/display_object_textures.c. */
#ifndef DISPLAY_OBJECT_TEXTURES_H
#define DISPLAY_OBJECT_TEXTURES_H

#include "global.h"
#include "asset_archive.h"
#include "memory.h"

typedef struct ModelLoadRequest {
    /* 0x00 */ s16 kind; // @unverified: 1 = one model, 2 = a list of resource files (PokeIcon_ThreadMain)
    /* 0x02 */ s16 fileIndex; // @unverified: archive file index
    /* 0x04 */ OSMesgQueue* queue; // @unverified: queue the request is sent back on when done
    /* 0x08 */ void* result; // @unverified: loaded data, or the output list for kind 2
    /* 0x0C */ void* fileList; // @unverified: -1-terminated file index list for kind 2
    /* 0x10 */ MainPoolState* pool; // @unverified: memory the request loads into
    /* 0x14 */ s32 size; // @unverified: pool size in, used size out
    /* 0x18 */ arg1_func_80010CA8 colorVariant; // @unverified: color variant applied to the loaded model
} ModelLoadRequest; // size = 0x1C

typedef struct ModelLoaderArchives {
    /* 0x00 */ BinArchive* modelArchive; // @unverified: archive of the Pokémon models (Model_LoadByArchiveIndex)
    /* 0x04 */ s32 resourceArchive; // @unverified: archive of the battle resource tables (BattleAnim_LoadResourceTable)
    /* 0x08 */ s32 scratchBuffer; // @unverified: load buffer passed to BinArchive_LoadFileToPool
    /* 0x0C */ s32 previewGeoNode; // @unverified: geo node saved by PokeIcon_CaptureGeoNode
    /* 0x10 */ BinArchive* unk_10;
} ModelLoaderArchives; // size >= 0x14

typedef struct ModelLoaderThread {
    /* 0x000 */ OSThread thread; // @unverified: loader thread (PokeIcon_ThreadMain)
    /* 0x1B0 */ u8 stack[0x800]; // @unverified: thread stack, its end is passed to osCreateThread
    /* 0x9B0 */ OSMesg requestMsgs[8]; // @unverified: buffer of requestQueue (osCreateMesgQueue count 8)
    /* 0x9D0 */ OSMesgQueue requestQueue; // @unverified: load requests for the thread
    /* 0x9E8 */ OSMesg diskMsg; // @unverified: buffer of diskQueue
    /* 0x9EC */ OSMesgQueue diskQueue; // @unverified: disk transfer completion (Fragment_LoadFromLbaRange)
    /* 0xA04 */ ModelLoaderArchives archives; // @unverified: open archives
} ModelLoaderThread; // size >= 0xA18

#include "game_state.h"
#include "memmap.h"

extern ModelLoaderThread D_800AC7A0;

// display_object_textures.c
void func_80016D40(GeoTextureBankNode* arg0, arg1_func_80010CA8 arg1);
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
void PokeIcon_LoadModelArchive(ModelLoadRequest* arg0);
void PokeIcon_LoadMultipleModels(ModelLoadRequest* arg0);
void PokeIcon_ThreadMain(UNUSED void* arg0);
void PokeIcon_StartThread(void);
s8 *PokeIcon_AllocFramebuffers(s32 arg0);
void PokeIcon_OpenModelArchives(void);
s32 PokeIcon_RequestFrameLoad(ModelLoadContext* arg0, u16 arg1, arg1_func_80010CA8 arg2);
s32 PokeIcon_RequestBackgroundLoad(ModelLoadContext* arg0, s32 arg1, s32 arg2);
s32 PokeIcon_ApplyLoadResult(ModelLoadContext* arg0, ModelLoadRequest* arg1);
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
