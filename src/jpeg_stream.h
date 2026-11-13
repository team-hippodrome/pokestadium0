/* Declarations for src/jpeg_stream.c. */
#ifndef JPEG_STREAM_H
#define JPEG_STREAM_H

#include "global.h"

typedef struct ret_func_8000484C {
	/* 0x00 */ char unk00[0x90];
	/* 0x90 */ s32 unk_90;
} ret_func_8000484C; // size >= 0x94

typedef struct Yay0 {
    /* 0x00 */ char magic[0x4]; // Yay0
    /* 0x04 */ u32 decompressed_size;
    /* 0x08 */ u32 link_table_offset;
    /* 0x0C */ u32 byte_chunk_offset;
} Yay0; // size = 0x10

typedef struct unk_func_80003680_sp300 {
    /* 0x00 */ u8 unk_00; // mode
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ char unk02[0x2];
    /* 0x04 */ s16 width;
    /* 0x06 */ s16 height;
    /* 0x08 */ u8* quantization_table;
    /* 0x0C */ u8* huffman_table;
    /* 0x10 */ u8* start_of_frame;
    /* 0x14 */ u8* start_of_scan;
} unk_func_80003680_sp300; // size = 0x18

typedef struct unk_func_80003680_sp90 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ s32 unk_14;
} unk_func_80003680_sp90; // size >= 0x18

#include "scheduler.h"

// jpeg_stream.c
s32 Jpeg_ReadBigEndianU16(u8* arg0);
void Jpeg_ParseStreamMarkers(unk_func_80003680_sp300* arg0, u8* arg1);
void Jpeg_InitializeDspTask(UnkStruct80001380* arg0, unk_func_80003680_sp90* arg1);
void Jpeg_BuildDspInput(s8 *arg0, s32 arg1, s8 *arg2);
void Jpeg_BuildDspOutput(unk_func_80003680_sp90* arg0, u8(arg1)[2][0x80], unk_func_80003680_sp300* arg2);
s32 Jpeg_DecodeImage(u32 addr, s32 arg1, u8* arg2);

#endif // JPEG_STREAM_H
