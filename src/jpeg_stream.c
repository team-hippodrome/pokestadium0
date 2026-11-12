/* Stadium Zero resident code. */
/* C ported from the Stadium 1 decomp: src/jpeg_stream.c. */

#include "jpeg_stream.h"
#include "jpeg_stream.h"
#include "flash.h"
#include "dma.h"
#include "dp_intro.h"
#include "util.h"
#include "lib/ultralib/include/PR/leo.h"
#include "controller.h"
s32 func_80005014(void);
#include "m2c_macros.h"
typedef enum {
    JPEG_MARKER_START_OF_FRAME = 0xC0,
    JPEG_MARKER_HUFFMAN_TABLE = 0xC4,
    JPEG_MARKER_RESTART0 = 0xD0,
    JPEG_MARKER_RESTART7 = 0xD7,
    JPEG_MARKER_START_OF_IMAGE = 0xD8,
    JPEG_MARKER_END_OF_IMAGE = 0xD9,
    JPEG_MARKER_START_OF_SCAN = 0xDA,
    JPEG_MARKER_QUANTIZATION_TABLE = 0xDB,
} JpegStreamMarker;
extern u8 D_800A94F0[0x200];
extern OSMesgQueue D_800A96F0;
extern OSMesg D_800A9708;
extern u64 njpgdspMainTextStart[];
extern u64 njpgdspMainDataStart[];

s32 Jpeg_ReadBigEndianU16(u8* arg0);
void Jpeg_ParseStreamMarkers(unk_func_80003680_sp300* arg0, u8* arg1);
void Jpeg_InitializeDspTask(UnkStruct80001380* arg0, unk_func_80003680_sp90* arg1);
void Jpeg_BuildDspOutput(unk_func_80003680_sp90* arg0, u8(arg1)[2][0x80], unk_func_80003680_sp300* arg2);

s32 Jpeg_ReadBigEndianU16(u8* arg0) {
    return ((arg0[0] << 8) | arg0[1]) & 0xFFFF;
}

void Jpeg_ParseStreamMarkers(unk_func_80003680_sp300* arg0, u8* arg1) {
    s32 temp_v0_2;
    s32 var_s2;
    s32 var_v0;
    u8 temp_t6;
    s32 temp_v0;

    var_s2 = 1;
    arg0->unk_01 = 0;

    while (var_s2 != 0) {
        // JPEG data consists of streams, which are identified by a marker.
        // Each marker is in the form [0xFF, 0xID] where ID identifies the type of stream.
        if (*arg1++ == 0xFF) {
            temp_v0 = *arg1++;
            switch (temp_v0) {
                case 0:
                    break;

                case JPEG_MARKER_END_OF_IMAGE:
                    var_s2 = 0;
                    break;

                case JPEG_MARKER_QUANTIZATION_TABLE:
                    arg0->quantization_table = arg1 + 2;
                    arg1 += Jpeg_ReadBigEndianU16(arg1);
                    break;

                case JPEG_MARKER_HUFFMAN_TABLE:
                    arg0->huffman_table = arg1 + 2;
                    arg1 += Jpeg_ReadBigEndianU16(arg1);
                    break;

                case JPEG_MARKER_START_OF_FRAME:
                    arg0->start_of_frame = arg1 + 2;
                    arg1 += Jpeg_ReadBigEndianU16(arg1);
                    break;

                case JPEG_MARKER_START_OF_SCAN:
                    arg1 += Jpeg_ReadBigEndianU16(arg1);
                    arg0->start_of_scan = arg1;
                    break;

                case JPEG_MARKER_START_OF_IMAGE:
                    break;

                default:
                    if ((temp_v0 >= JPEG_MARKER_RESTART0) && (temp_v0 <= JPEG_MARKER_RESTART7)) {
                        arg0->unk_01 = 1;
                    } else {
                        arg1 += Jpeg_ReadBigEndianU16(arg1);
                    }
                    break;
            }
        }
    }

    // Checking the second component's ID,
    // this seems weird as it will break entirely if number of components is less than 3.
    // Looking at every JPEG used in the Stadium rom, no JPEGs use this ID, they're all 0x22.
    if (arg0->start_of_frame[7] == 0x21) {
        arg0->unk_00 = 0;
    } else {
        arg0->unk_00 = 2;
    }

    arg0->width = (arg0->start_of_frame[3] << 8) | arg0->start_of_frame[4];
    arg0->height = (arg0->start_of_frame[1] << 8) | arg0->start_of_frame[2];
}

void Jpeg_InitializeDspTask(UnkStruct80001380* arg0, unk_func_80003680_sp90* arg1) {
    arg0->task.t.type = 4;
    arg0->task.t.flags = 0;
    arg0->task.t.ucode_boot = rspbootTextStart;
    arg0->task.t.ucode_boot_size = (u32)_binary_assets_us_F3DEX2_bin_start - (u32)rspbootTextStart;
    arg0->task.t.ucode = njpgdspMainTextStart;
    arg0->task.t.ucode_size = 0x1000;
    arg0->task.t.ucode_data = njpgdspMainDataStart;
    arg0->task.t.ucode_data_size = 0x800;
    arg0->task.t.dram_stack = NULL;
    arg0->task.t.dram_stack_size = 0;
    arg0->task.t.output_buff = NULL;
    arg0->task.t.output_buff_size = NULL;
    arg0->task.t.data_ptr = arg1;
    arg0->task.t.data_size = 0x20;
    arg0->task.t.yield_data_ptr = D_800A94F0;
    arg0->task.t.yield_data_size = 0x200;

    osCreateMesgQueue(&arg0->queue, &arg0->mesg, 1);
}

void Jpeg_BuildDspInput(s8 *arg0, s32 arg1, s8 *arg2)
{
  *((s32 *) (((s8 *) arg0) + 0)) = (s32) (*((s32 *) (((s8 *) arg2) + 0x14))); // FAKE: decomp slop, raw pointer casts stand in for struct fields
  *((u8 *) (((s8 *) arg0) + 4)) = (u8) (*((u8 *) (((s8 *) arg2) + 0))); // FAKE: decomp slop, raw pointer casts stand in for struct fields
  *((s8 *) (((s8 *) arg0) + 5)) = 0;
  *((s32 *) (((s8 *) arg0) + 8)) = arg1;
  *((s32 *) (((s8 *) arg0) + 0xC)) = (s32) (arg1 + 0xA8);
  *((s32 *) (((s8 *) arg0) + 0x10)) = (s32) (arg1 + 0x54);
  *((s32 *) (((s8 *) arg0) + 0x14)) = (s32) (arg1 + 0xFC);
  *((u8 *) (((s8 *) arg0) + 0x18)) = (u8) (*((u8 *) (((s8 *) arg2) + 1))); // FAKE: decomp slop, raw pointer casts stand in for struct fields
}

void Jpeg_BuildDspOutput(unk_func_80003680_sp90* arg0, u8(arg1)[2][0x80], unk_func_80003680_sp300* arg2) {
    arg0->unk_00 = 0;
    arg0->unk_08 = arg2->unk_00;
    arg0->unk_04 = 1;
    arg0->unk_0C = (u32)&arg1[0] & 0x1FFFFFFF;
    arg0->unk_10 = (u32)&arg1[1] & 0x1FFFFFFF;
    arg0->unk_14 = (u32)&arg1[1] & 0x1FFFFFFF;
}

/**
 * Spins (with a capped counter) until func_80005014 returns 0 and at least one
 * controller is connected.
 * @unverified Name and comment guessed from the code.
 */
void Jpeg_WaitForControllerReady(void) {
    s32 timeout = 0;

    while ((func_80005014() != 0) || (Cont_GetControllerBits() == 0)) {
        if (timeout < 1000000) {
            timeout++;
        }
    }
}

s32 Jpeg_DecodeImage(u32 addr, s32 arg1, u8* arg2) {
    UnkStruct80001380 sp318;
    unk_func_80003680_sp300 sp300;
    u8 sp200[2][0x80];
    JpegHuffmanTable spB0[4];
    u16* temp_s0;
    u8* temp_s3;
    unk_func_80003680_sp90 sp90;
    JpegDecoder sp74;
    JpegDecoderState sp60;
    u32 var_s1;
    s32 i;
    s32 j;
    s32 var_s4 = 0;
    s32 var_s2 = 0;

    temp_s3 = Util_Malloc(0x110);
    temp_s0 = Util_Malloc(0x210);

    Jpeg_ParseStreamMarkers(&sp300, arg2);
    JpegUtils_ProcessQuantizationTable(sp300.quantization_table, sp200, 2);
    JpegUtils_ProcessHuffmanTable(sp300.huffman_table, spB0, temp_s3, temp_s0, 4);

    Util_Free(temp_s0);
    Util_Free(temp_s3);

    Jpeg_BuildDspInput(&sp74, &spB0, &sp300);
    Jpeg_BuildDspOutput(&sp90, &sp200, &sp300);
    Jpeg_InitializeDspTask(&sp318, &sp90);
    Jpeg_WaitForControllerReady();

    for (i = 0; i < sp300.height; i += 16) {
        for (j = 0; j < sp300.width; j += 16) {
            if (arg1 < (var_s2 + 0x300)) {
                return 0;
            }

            if (Jpeg_DecodeMcus(&sp74, addr, 1, var_s4, &sp60) != 0) {
                return 0;
            }

            sp90.unk_00 = addr & 0x1FFFFFFF;
            Sched_SubmitTask(&sp318, 1);
            var_s4 = 1;
            Sched_WaitForTaskMessage(&sp318);

            addr += 0x200;
            var_s2 += 0x200;
        }
    }

    return var_s2;
}
