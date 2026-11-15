/* Declarations for src/asset_archive.c. */
#ifndef ASSET_ARCHIVE_H
#define ASSET_ARCHIVE_H

#include "global.h"

typedef struct PERSSZP {
    /* 0x00 */ char magic[0x8]; // PERS-SZP
    /* 0x08 */ u32 header_size;
    /* 0x0C */ u32 decompressed_size1; // How do these differ?
    /* 0x10 */ u32 decompressed_size2;
    /* 0x14 */ u32 unk_14;
} PERSSZP; // sze = 0x18

typedef struct PRESJPEG {
    /* 0x00 */ char magic[0x8]; // PRESJPEG
    /* 0x08 */ u32 unk_08; // header size? always 0x10
    /* 0x0C */ u32 unk_0C;
} PRESJPEG; // size = 0x10

typedef struct BinArchive {
    union {
        struct {
            /* 0x00 */ u16 unk_00;
            /* 0x02 */ u16 unk_02;
        };
        s32 raw;
    };
    /* 0x04 */ u32 unk_04;
    /* 0x08 */ u32 total_size;
    /* 0x0C */ u32 num_files;
} BinArchive; // size = 0x10

typedef struct BinArchiveFile {
    /* 0x00 */ u32 offset;
    /* 0x04 */ u32 size;
    /* 0x08 */ u32 unk_08;
    /* 0x0C */ char unk0C[0x4];
} BinArchiveFile; // size = 0x10

typedef struct unk_func_800041C0 {
    /* 0x00 */ u16 unk_00;
    /* 0x02 */ u16 unk_02;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
} unk_func_800041C0; // size >= 0x8

typedef void (*ret_func_80004454)(void);

#include "memmap.h"
#include "memory.h"

// asset_archive.c
void Dma_InitializeCompletionQueue(void);
void Yay0_DecompressAndRelocate(u8* in_header, u8* memory);
void Dma_ReadChunks(u8* arg0, s32 arg1, s32 arg2, s32 arg3);
void Dma_WriteChunks(u32 write_start, u32 buffer_start, u32 buffer_end, s32 arg3);
void* Jpeg_LoadDecodedImage(u8* addr, PRESJPEG* arg1, s32 side);
s32 Yay0_LoadDecompressedAsset(s32 arg0, PERSSZP* arg1, s32 side);
u32* Asset_CopyUncompressed(u8* arg0, s32 arg1, u32 arg2, s32 arg3);
void* Asset_LoadCompressed(u8* romStart, u8* romEnd, s32 arg2, s32 arg3);
void* Storage_LoadAssetByLbaRange(unk_func_800041C0* arg0, s32 arg1);
unk_func_800041C0* Storage_SetLbaRange(unk_func_800041C0* arg0, s32 arg1, s32 arg2);
unk_func_800041C0* Storage_SetByteRange(unk_func_800041C0* arg0, u32 arg1, u32 offset, u32 size);
void Storage_PrefetchLbaRange(s32 arg0, s32 arg1, s32 arg2);
void Memmap_ClearSegmentOnBlockFree(u32 block_addr, u32 addr);
u8* Asset_LoadToSegment(s32 id, u8* rom_start, u8* rom_end, s32 arg3);
MainPoolBlock* Asset_LoadToSegmentByLbaRange(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void Fragment_FreeCallback(u32 base_addr, u32 addr);
void Fragment_Register(s32 arg0, Fragment* addr);
ret_func_80004454 Fragment_Load(s32 arg0, u8* romStart, u8* romEnd);
void* Fragment_LoadByLbaRange(s32 arg0, s32 arg1, s32 arg2);
BinArchive* BinArchive_Open(u8* romStart, u8* romEnd, s32 arg2, s32 arg3);
void* BinArchive_LoadByLbaRange(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void BinArchive_Free(void* arg0);
Fragment* BinArchive_LoadFileFromRom(BinArchive* arg0, BinArchiveFile* arg1);
void* BinArchive_LoadFileBuffered(BinArchive* arg0, BinArchiveFile* arg1);
void* BinArchive_GetFile(BinArchive* archive, s32 file_number);
s32 BinArchive_GetCachedFile(BinArchive* archive, s32 file_number);

#endif // ASSET_ARCHIVE_H
