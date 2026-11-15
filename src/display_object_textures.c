/* Stadium Zero resident code. */
/* C ported from the Stadium 1 decomp: src/display_object_textures.c. */

#include "display_object_textures.h"
#include "geo_layout.h"
#include "dma.h"
#include "memmap.h"
#include "memory.h"
#include "util.h"
#include <PR/os_internal_reg.h>
#include <PR/leo.h>
#include "memory.h"
typedef struct ret_func_unk_D_800ABE10 {
    /* 0x00 */ char unk00[0x3];
    /* 0x03 */ u8 unk_03;
    /* 0x04 */ char unk04[0x4];
    /* 0x08 */ unk_D_86002F34** unk_08;
    /* 0x0C */ char unk0C[0x8];
    /* 0x14 */ func_unk_D_800ABE10 unk_14;
} ret_func_unk_D_800ABE10;
extern unk_D_800ABE10 D_800AC7A0;

#include "m2c_macros.h"

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
void PokeIcon_StartThread(void);
unk_D_86002F30* Model_LoadByArchiveIndex(s32 arg0);
unk_D_86002F30* Model_LoadForPokemon(BattleMon* arg0);
arg1_func_80019420* BattleAnim_LoadResourceTable(s32 arg0);
Fragment* Fragment_LoadAndRelocateFromRomRange(MainPoolState* arg0, u32 arg1, s32 arg2, s32 arg3, PERSSZP* arg4, s32 arg5);

void PokeIcon_ThreadMain(UNUSED void* arg0);

void func_80016D40(unk_D_86002F34* arg0, arg1_func_80010CA8 arg1) {
    s32 i;
    s32 j;
    unk_D_86002F34_018* var_s2 = arg0->unk_18;
    unk_D_86002F34_01C* var_s4 = arg0->unk_1C;

    for (i = 0; i < arg0->unk_24; i++, var_s2++) {
        if (var_s2->unk_00 == 0) {
            if (var_s2->type == unk_D_86002F34_018_GFX_TYPE_2) {
                u16* var_s1 = (u16*)var_s2->texture;
                for (j = 0; j < var_s2->num_texels; j++, var_s1++) *var_s1 = Color_AdjustRGB5551(*var_s1, arg1);
            }
            if (var_s2->type == unk_D_86002F34_018_GFX_TYPE_3) {
                u32* var_s1 = var_s2->texture;
                for (j = 0; j < var_s2->num_texels; j++, var_s1++) *var_s1 = Color_AdjustRGBA8(*var_s1, arg1);
            }
        }
    }
    for (i = 0; i < arg0->unk_25; i++, var_s4++) {
        u16* var_s1 = var_s4->unk_04;
        for (j = 0; j < var_s4->unk_00; j++, var_s1++) *var_s1 = Color_AdjustRGB5551(*var_s1, arg1);
    }
}

/** Allocates a fragment and decodes a JPEG image into it. */
Fragment* Jpeg_AllocAndDecodeFragment(MemoryBlock* arg0, PRESJPEG* arg1, PRESJPEG* arg2) {
    Fragment* sp1C;
    s32 sp18;
    s32 temp_v0_2;

    sp18 = arg0->size;
    sp1C = MainPool_AllocAligned(arg0, arg2->unk_0C + 0x100, 0x10);

    if (sp1C != NULL) {
        temp_v0_2 = Jpeg_DecodeImage(sp1C, arg2->unk_0C + 0x100, (u8*)arg2 + arg2->unk_08);
        if (temp_v0_2 == 0) {
            MainPool_ResetStateToOffset(arg0, sp18);
            sp1C = NULL;
        } else {
            MainPool_ResetStateToOffset(arg0, sp18 + temp_v0_2);
        }
    }
    return sp1C;
}

/** Allocates a fragment and decompresses a Yay0 asset into it. */
Fragment* Yay0_AllocAndDecompressFragment(MainPoolState* arg0, PERSSZP* arg1, PERSSZP* arg2) {
    u8* sp1C = MainPool_AllocAligned(arg0, arg2->decompressed_size2, 0x10);

    if (sp1C != NULL) {
        Yay0_DecompressAndRelocate(arg2, sp1C);
    }
    return sp1C;
}

/** Allocates a fragment and copies an uncompressed asset into it. */
Fragment* Asset_AllocAndCopyFragment(MainPoolState* arg0, PERSSZP* arg1, s32 arg2, u32 arg3) {
    u32* sp1C;

    sp1C = MainPool_AllocAligned(arg0, arg3, 0x10);
    if (sp1C != NULL) {
        Util_Memcpy(sp1C, (u8*)arg1 + arg2, arg3 >> 2);
    }
    return sp1C;
}

/** Loads a fragment from a ROM range into a pool, decompressing it as needed. */
Fragment* Fragment_LoadFromRomRange(MainPoolState* arg0, s32 start, s32 end, PERSSZP* arg3, s32 arg4) {
    UNUSED s32 pad; // FAKE: stack padding
    u32 size = ALIGN16(end - start);
    Fragment* var_v1 = NULL;

    if (arg4 >= size) {
        Dma_WriteChunks(arg3, start, end, 0);

        if (((u32*)arg3->magic)[0] == 'PERS' && (((u32*)arg3->magic)[1] == '-SZP')) {
            var_v1 = Yay0_AllocAndDecompressFragment(arg0, arg3, arg3);
        } else if (((u32*)arg3->magic)[0] == 'PRES' && (((u32*)arg3->magic)[1] == 'JPEG')) {
            var_v1 = Jpeg_AllocAndDecodeFragment(arg0, arg3, arg3);
        } else {
            var_v1 = Asset_AllocAndCopyFragment(arg0, arg3, 0, size);
        }
    }

    return var_v1;
}

/**
 * Loads a fragment from a block-address range into a pool, decompressing it as
 * needed.
 */
Fragment* Fragment_LoadFromLbaRange(MainPoolState* arg0, unk_func_800041C0* arg1, PERSSZP* arg2, u32 arg3) {
    s32 sp3C;
    Fragment* sp38;
    PERSSZP* temp_s1;

    LeoLBAToByte(arg1->unk_00, arg1->unk_02, &sp3C);
    sp3C = ALIGN16(sp3C);

    if (arg3 >= sp3C) {
        temp_s1 = arg1->unk_04 + (u8*)arg2;

        Storage_QueueDiskTransfer(0, arg2, arg1->unk_00, arg1->unk_02, &D_800AC7A0.unk_9EC, 0);
        osRecvMesg(&D_800AC7A0.unk_9EC, NULL, 1);

        if (((u32*)temp_s1->magic)[0] == 'PERS' && (((u32*)temp_s1->magic)[1] == '-SZP')) {
            sp38 = Yay0_AllocAndDecompressFragment(arg0, arg2, temp_s1);
        } else if (((u32*)temp_s1->magic)[0] == 'PRES' && (((u32*)temp_s1->magic)[1] == 'JPEG')) {
            sp38 = Jpeg_AllocAndDecodeFragment(arg0, arg2, temp_s1);
        } else {
            sp38 = Asset_AllocAndCopyFragment(arg0, arg2, arg1->unk_04, arg1->unk_08);
        }
    }

    return sp38;
}

/** Relocates a fragment's pointers and commits it to its pool. */
void Fragment_RelocateAndCommit(MainPoolState* arg0, u32 arg1, Fragment* arg2) {
    Memmap_RelocateFragment(arg1, arg2);
    MainPool_ResetStateToOffset(arg0, ((u32)arg2 + arg2->sizeInRam) - (u32)arg0->listHeadR);
}

/** Loads an archive file into a pool from a ROM range. */
Fragment* BinArchive_LoadFileFromRomRange(MainPoolState* arg0, BinArchive* arg1, BinArchiveFile* arg2, u32 arg3, s32 arg4) {
    s32 temp_a1 = arg1->unk_04 + arg2->offset;

    return Fragment_LoadFromRomRange(arg0, temp_a1, arg2->size + temp_a1, arg3, arg4);
}

/** Loads an archive file into a pool from a block-address range. */
Fragment* BinArchive_LoadFileFromLbaRange(MainPoolState* arg0, BinArchive* arg1, BinArchiveFile* arg2, u32 arg3, s32 arg4) {
    unk_func_800041C0 sp1C;

    Storage_SetByteRange(&sp1C, arg1->unk_04, arg2->offset, arg2->size);
    return Fragment_LoadFromLbaRange(arg0, &sp1C, arg3, arg4);
}

/** Loads an archive file into a pool, choosing the ROM or block-address path. */
Fragment* BinArchive_LoadFileToPool(MainPoolState* arg0, BinArchive* arg1, s32 arg2, u32 arg3, s32 arg4) {
    s32 pad[4]; // FAKE: stack padding
    Fragment* var_s0 = NULL;
    BinArchiveFile* sp2C = (u8*)arg1 + sizeof(BinArchive) + (arg2 * sizeof(BinArchiveFile));

    if (arg2 < arg1->num_files) {
        if (arg1->unk_00 & 1) {
            var_s0 = (u8*)arg1 + sp2C->offset;
        } else if (!(arg1->unk_00 & 4) && (sp2C->unk_08 != NULL)) {
            var_s0 = sp2C->unk_08;
        } else {
            if (arg1->unk_00 & 0x80) {
                var_s0 = BinArchive_LoadFileFromLbaRange(arg0, arg1, sp2C, arg3, arg4);
            } else {
                var_s0 = BinArchive_LoadFileFromRomRange(arg0, arg1, sp2C, arg3, arg4);
            }

            if (var_s0 != NULL) {
                if ((((u32*)var_s0->magic)[0] == 'FRAG') && (((u32*)var_s0->magic)[1] == 'MENT')) {
                    Fragment_RelocateAndCommit(arg0, arg1->unk_02, var_s0);
                }
                sp2C->unk_08 = var_s0;
            }
        }
    }

    return var_s0;
}

/** Builds the graph node tree for a fragment's geo layout. */
s32 Fragment_ProcessGeoLayout(MemoryBlock* arg0, Fragment* arg1, arg1_func_80010CA8 arg2) {
    s32 i;
    unk_D_86002F34* temp_v0_2;
    ret_func_unk_D_800ABE10* temp_v0;
    ret_func_unk_D_800ABE10* (*func)(s32, s32) = arg1;

    temp_v0 = func(0, 0);
    temp_v0->unk_14 = arg1;

    for (i = 0; i < temp_v0->unk_03; i++) {
        temp_v0_2 = process_geo_layout(arg0, temp_v0->unk_08[i]);

        if (temp_v0_2->node.type == 0xE) {
            temp_v0_2->unk_28 = arg1;
            if (arg2.raw != 0) {
                func_80016D40(temp_v0_2, arg2);
            }
        }
        temp_v0->unk_08[i] = temp_v0_2;
    }

    return temp_v0;
}

/** Builds graph node trees for every geo layout in a list. */
void Fragment_ProcessGeoLayoutList(MemoryBlock* arg0, arg1_func_80019420* arg1) {
    while (arg1->unk_00) {
        if (arg1->unk_00 == 3) {
            arg1->unk_04 = process_geo_layout(arg0, arg1->unk_04);
        }

        arg1++;
    }
}

/** Loads a Pokemon icon model archive on the loader thread. */
void PokeIcon_LoadModelArchive(unk_func_80019600* arg0) {
    UNUSED s32 pad; // FAKE: stack padding
    MemoryBlock* sp28;
    Fragment* sp24;

    sp28 = MainPool_InitState(arg0->pool, arg0->size);
    sp24 = BinArchive_LoadFileToPool(sp28, D_800AC7A0.unk_A04.unk_00, arg0->unk_02, D_800AC7A0.unk_A04.unk_08, 0x28000);

    if (sp24 != NULL) {
        arg0->unk_08 = Fragment_ProcessGeoLayout(sp28, sp24, arg0->unk_18);
    } else {
        arg0->unk_08 = 0;
    }

    arg0->size = sp28->size + 0x10;
}

/** Loads several Pokemon icon models on the loader thread. */
void PokeIcon_LoadMultipleModels(unk_func_80019600* arg0) {
    Fragment* temp_v0;
    MainPoolState* temp_s3;
    s32 var_s2;
    s32* temp_s6;
    s16* var_s0;

    temp_s6 = arg0->unk_08;
    var_s2 = 0;
    temp_s3 = MainPool_InitState(arg0->pool, arg0->size);
    var_s0 = arg0->unk_0C;

    while (*var_s0 != -1) {
        temp_v0 = BinArchive_LoadFileToPool(temp_s3, D_800AC7A0.unk_A04.unk_04, *var_s0, D_800AC7A0.unk_A04.unk_08, 0x28000);
        if (temp_v0 == NULL) {
            break;
        }

        temp_s6[var_s2] = temp_v0 + 1;
        Fragment_ProcessGeoLayoutList(temp_s3, temp_v0 + 1);
        var_s0++;
        var_s2++;
    }

    temp_s6[var_s2] = 0;
    arg0->size = temp_s3->listHeadL + 1;
}

/** Main loop of the thread that loads Pokemon icon models on request. */
void PokeIcon_ThreadMain(UNUSED void* arg0) {
    unk_func_80019600* sp34;

    __osSetFpcCsr(0x01000F00);

    while (true) {
        osRecvMesg(&D_800AC7A0.unk_9D0, &sp34, 1);

        switch (sp34->unk_00) {
            case 1:
                PokeIcon_LoadModelArchive(sp34);
                break;

            case 2:
                PokeIcon_LoadMultipleModels(sp34);
                break;
        }

        if (sp34->queue != NULL) {
            osSendMesg(sp34->queue, sp34, 1);
        }
    }
}

/** Creates the message queues and starts the icon loader thread. */
void PokeIcon_StartThread(void) {
    osCreateMesgQueue(&D_800AC7A0.unk_9D0, &D_800AC7A0.unk_9B0, 8);
    osCreateMesgQueue(&D_800AC7A0.unk_9EC, &D_800AC7A0.unk_9E8, 1);
    osCreateThread(&D_800AC7A0.unk_000, 7, PokeIcon_ThreadMain, NULL, &D_800AC7A0.unk_9B0, 0xA);
    osStartThread(&D_800AC7A0.unk_000);
}

s8 *func_800023C4(M2C_UNK, M2C_UNK);              /* extern */
M2C_UNK func_800567E0(s8 *, s8 *, M2C_UNK);     /* extern */

/** Allocates the framebuffers used by the icon loader. */
s8 *PokeIcon_AllocFramebuffers(s32 arg0) {
    s8 *temp_v0;

    temp_v0 = func_800023C4(0x64, 1);
    M2C_FIELD(temp_v0, s8 *, 1) = 0;
    M2C_FIELD(temp_v0, s8 *, 2) = 0;
    M2C_FIELD(temp_v0, s32 *, 0x18) = 0;
    M2C_FIELD(temp_v0, s8 **, 4) = NULL;
    M2C_FIELD(temp_v0, s8 **, 8) = NULL;
    M2C_FIELD(temp_v0, s8 **, 0xC) = NULL;
    M2C_FIELD(temp_v0, s32 *, 0x20) = 0;
    M2C_FIELD(temp_v0, s8 *, 0) = (s8) arg0;
    if (arg0 & 1) {
        M2C_FIELD(temp_v0, s8 **, 4) = func_800023C4(0x3C000, 1);
        if (arg0 & 4) {
            M2C_FIELD(temp_v0, s8 **, 8) = func_800023C4(0x3C000, 1);
        }
    }
    if (arg0 & 2) {
        M2C_FIELD(temp_v0, s8 **, 0xC) = func_800023C4(0x18000, 1);
    }
    func_800567E0(temp_v0 + 0x24, temp_v0 + 0x3C, 2);
    func_800567E0(temp_v0 + 0x44, temp_v0 + 0x5C, 2);
    return temp_v0;
}

s32 func_80004154(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK); /* extern */
extern s32 D_800AD1A4;
extern s32 D_800AD1A8;
extern s32 D_800AD1AC;

/**
 * Seen in play (2026-11-13) (tour of menus and a COM battle): ran in the Pokédex, the party screen,
 * Lab sort, registration, the Lab PC and Free Battle setup.
 * @unverified Name was previously used only by callers of this address; the definition was still func_.
 */
void PokeIcon_OpenModelArchives(void) {
    D_800AD1A4 = func_80004154(0x500000, 0, 1, 1);
    D_800AD1A8 = func_80004154(0x4A8000, 0, 1, 1);
    D_800AD1AC = func_800023C4(0x28000, 1);
}

/** Sends a model load request to the icon loader thread. */
s32 PokeIcon_RequestFrameLoad(ModelLoadContext* arg0, u16 arg1, arg1_func_80010CA8 arg2) {
    s32 sp1C;
    sp18_func_800198E4* sp18;
    s32 var_v1;

    sp1C = 0;
    if ((arg0->flags & 1) && !(arg0->pendingLoads & 1)) {
        sp18 = Util_Malloc(sizeof(sp18_func_800198E4));
        if (sp18 != NULL) {
            var_v1 = arg0->bufferIndex;
            if (arg0->flags & 4) {
                var_v1 ^= 1;
            }

            sp18->unk_00 = 1;
            sp18->unk_02 = arg1 - 1;
            sp18->unk_04 = &arg0->modelQueue;
            sp18->unk_08 = 0;
            sp18->unk_0C = 0;
            sp18->unk_10 = arg0->modelBuffers[var_v1];
            sp18->unk_14 = 0x3C000;
            sp18->unk_18 = arg2;

            if ((arg0->loadedModel != NULL) && (arg0->loadedModel->modelId == arg1) && (arg0->colorVariant.raw == sp18->unk_18.raw)) {
                osSendMesg(sp18->unk_04, sp18, 1);
            } else {
                osSendMesg(&D_800AC7A0.unk_9D0, sp18, 1);
            }

            arg0->pendingLoads |= 1;
            sp1C = 1;
        }
    }

    return sp1C;
}

/** Sends a background model load request to the icon loader thread. */
s32 PokeIcon_RequestBackgroundLoad(ModelLoadContext* arg0, s32 arg1, s32 arg2) {
    s32 sp1C = 0;
    sp18_func_800198E4* temp_v0;

    if ((arg0->flags & 2) && !(arg0->pendingLoads & 2)) {
        temp_v0 = Util_Malloc(sizeof(sp18_func_800198E4));
        if (temp_v0 != NULL) {
            temp_v0->unk_00 = 2;
            temp_v0->unk_02 = 0;
            temp_v0->unk_04 = &arg0->backgroundQueue;
            temp_v0->unk_08 = arg2;
            temp_v0->unk_0C = arg1;
            temp_v0->unk_10 = arg0->backgroundBuffer;
            temp_v0->unk_14 = 0x18000;

            osSendMesg(&D_800AC7A0.unk_9D0, temp_v0, 1);

            sp1C = 1;
            arg0->pendingLoads |= 2;
        }
    }

    return sp1C;
}

/** Applies a load result received from the icon loader thread. */
s32 PokeIcon_ApplyLoadResult(ModelLoadContext* arg0, sp18_func_800198E4* arg1) {
    s32 sp1C = 0;

    switch (arg1->unk_00) {
        case 1:
            arg0->pendingLoads &= ~1;
            if (arg1->unk_08 != 0) {
                if (arg0->flags & 4) {
                    arg0->bufferIndex ^= 1;
                }
                arg0->loadedModel = arg1->unk_08;
                arg0->modelSize = arg1->unk_14;
                arg0->colorVariant = arg1->unk_18;
            }
            sp1C = 1;
            break;

        case 2:
            arg0->pendingLoads &= ~2;
            arg0->loadedBackground = arg1->unk_08;
            arg0->backgroundSize = arg1->unk_14;
            sp1C = 1;
            break;
    }

    Util_Free(arg1);
    return sp1C;
}

/** Checks whether the icon loader has finished a requested model. */
s32 PokeIcon_PollFrameLoad(ModelLoadContext* arg0) {
    sp18_func_800198E4* sp1C;
    s32 sp18 = 0;

    if (osRecvMesg(&arg0->modelQueue, &sp1C, 0) != -1) {
        sp18 = PokeIcon_ApplyLoadResult(arg0, sp1C);
    }

    return sp18;
}

/**
 * Seen in play (2026-11-13) (tour of menus and a COM battle): ran in the battle opening, a switch
 * in battle and a Pound turn.
 * @unverified Name was previously used only by callers of this address; the definition was still func_.
 */
s32 PokeIcon_PollBackgroundLoad(ModelLoadContext* arg0) {
    sp18_func_800198E4* sp1C;
    s32 sp18 = 0;

    if (osRecvMesg((OSMesgQueue*)((u8*)arg0 + 0x44), &sp1C, 0) != -1) {
        sp18 = PokeIcon_ApplyLoadResult(arg0, sp1C);
    }

    return sp18;
}

M2C_UNK func_80017BA0(s32, s32);                    /* extern */
M2C_UNK func_8004D1C0(s32, s32 *, M2C_UNK);         /* extern */

void func_80017D00(s32 arg0) {
    s32 sp1C;

    func_8004D1C0(arg0 + 0x24, &sp1C, 1);
    func_80017BA0(arg0, sp1C);
}

M2C_UNK func_80017BA0(s32, s32);                    /* extern */
M2C_UNK func_8004D1C0(s32, s32 *, M2C_UNK);         /* extern */

/** Blocks until the icon loader finishes a background load. */
void PokeIcon_WaitBackgroundLoad(s32 arg0) {
    s32 sp1C;

    func_8004D1C0(arg0 + 0x44, &sp1C, 1);
    func_80017BA0(arg0, sp1C);
}

/** Loads a model by its archive index. */
unk_D_86002F30* Model_LoadByArchiveIndex(s32 arg0) {
    Fragment* sp2C;
    arg1_func_80010CA8 sp28;
    unk_D_86002F30* sp24 = NULL;
    MemoryBlock* sp20;

    sp2C = BinArchive_GetFile(D_800AC7A0.unk_A04.unk_00, arg0 - 1);
    if (sp2C != NULL) {
        sp20 = MainPool_AllocState(main_pool_get_available(), 0);
        sp28.raw = 0;
        sp24 = Fragment_ProcessGeoLayout(sp20, sp2C, sp28);
        MainPool_FinalizeAllocation(sp20);
    }

    return sp24;
}

/** Loads the model for a Pokemon. */
unk_D_86002F30* Model_LoadForPokemon(BattleMon* arg0) {
    Fragment* sp2C;
    arg1_func_80010CA8 sp28;
    unk_D_86002F30* sp24 = NULL;
    MemoryBlock* sp20;

    sp2C = BinArchive_GetFile(D_800AC7A0.unk_A04.unk_00, arg0->species.id - 1);
    if (sp2C != NULL) {
        sp20 = MainPool_AllocState(main_pool_get_available(), 0);
        Model_ComputeSizeVariant(&sp28, arg0);
        sp24 = Fragment_ProcessGeoLayout(sp20, sp2C, sp28);
        MainPool_FinalizeAllocation(sp20);
    }
    return sp24;
}

/** Loads a battle animation resource table. */
arg1_func_80019420* BattleAnim_LoadResourceTable(s32 arg0) {
    Fragment* sp24;
    arg1_func_80019420* sp20;
    MemoryBlock* sp1C;

    sp20 = NULL;
    sp24 = BinArchive_GetFile(D_800AC7A0.unk_A04.unk_04, arg0);
    if (sp24 != NULL) {
        sp1C = MainPool_AllocState(main_pool_get_available(), 0);
        sp20 = sp24->data;
        Fragment_ProcessGeoLayoutList(sp1C, sp20);
        MainPool_FinalizeAllocation(sp1C);
    }
    return sp20;
}

/** Loads a fragment from a ROM range and relocates it. */
Fragment* Fragment_LoadAndRelocateFromRomRange(MainPoolState* arg0, u32 arg1, s32 arg2, s32 arg3, PERSSZP* arg4, s32 arg5) {
    Fragment* sp24 = Fragment_LoadFromRomRange(arg0, arg2, arg3, arg4, arg5);

    if (sp24 != NULL) {
        Fragment_RelocateAndCommit(arg0, arg1, sp24);
    }
    return sp24;
}
