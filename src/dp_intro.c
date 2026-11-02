/* Stadium Zero resident code. */
/* C ported from the Stadium 1 decomp: src/audio_loop_point.c, src/controller.c, src/dp_intro.c. */

#include "global.h"
#include <PR/os_internal_reg.h>
#include "dp_intro.h"
#include "scheduler.h"
#include "gfx_rect.h"
#include "crash_screen.h"
#include "profiler.h"
#include "memory.h"
extern u64 F3DEX2_data_bin[];
extern s32 D_800733F0;
extern UnkStruct80083CA0_2 D_800870A0;
extern u64 D_80087B88[0x100 / sizeof(u64)];
extern u64 D_80087C88[0x408 / sizeof(u64)];
extern u64 D_80088090[0xC08 / sizeof(u64)];
extern u64 D_80088C98[0x20000 / sizeof(u64)];
void Display_ClearFramebufferLine(u16 color);
void Display_SetBufferConfig(struct UnkArray4* arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4, s32 arg5, s32 arg6, s32 arg7);

#include "audio_loop_point.h"
#include "libnumus/player.h"
#include "audio_channel.h"
#include "audio_commands_category2.h"
#include "rom_device.h"
#include "audio_stream.h"
#include "audio_cache.h"
#include "3D140.h"
#include "audio_commands.h"

#include "global.h"
#include "controller.h"
#include "gb_tower.h"
#include "math_util.h"
extern Controller* gPlayer1Controller;
extern Controller* gPlayer2Controller;
extern Controller* gPlayer3Controller;
extern Controller* gPlayer4Controller;
extern Controller gControllers[4];
extern OSMesgQueue gSIEventMesgQueue;
extern u8 gControllerBits;
extern u8 gEepromProbe;
extern OSContStatus gControllerStatuses[4];
extern OSContPad gControllerPads[4];
extern OSMesg gSIEventMesgBuf[1];
extern OSMesg gEepromMesgBuf[1];
extern OSMesgQueue gEepromMesgQueue;

#include "m2c_macros.h"

void DisplayTask_Initialize(UnkStruct80001380* arg0);
void DisplayTask_Submit(UnkStruct80001380* arg0, struct UnkArray4* arg1, s32 arg2);
u16 Display_GetFramebufferClearColor(void);
void Display_WaitForCompletion(void);
void Display_QueueFramebufferRequest(void* arg0);
void Display_WaitForFrames(s32 arg0);
void Display_SetBufferConfig(struct UnkArray4* arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4, s32 arg5, s32 arg6, s32 arg7);
u32 Audio_GetSpecialSequenceState(void);
u8 Cont_GetControllerBits(void);

void DisplayTask_Initialize(UnkStruct80001380* arg0) {
    arg0->task.t.type = M_GFXTASK;
    arg0->task.t.flags = 0;
    arg0->task.t.ucode_boot = D_80087B88;
    arg0->task.t.ucode_boot_size = 0x100;
    arg0->task.t.ucode = _binary_assets_us_F3DEX2_bin_start;
    arg0->task.t.ucode_data = F3DEX2_data_bin;
    arg0->task.t.ucode_size = 0x1000;
    arg0->task.t.ucode_data_size = 0x800;
    arg0->task.t.dram_stack = (void*)ALIGN16((uintptr_t)D_80087C88);
    arg0->task.t.dram_stack_size = 0x400;
    arg0->task.t.yield_data_ptr = (void*)ALIGN16((uintptr_t)D_80088090);
    arg0->task.t.yield_data_size = 0xC00;
    arg0->task.t.output_buff = (D_80088C98);
    arg0->task.t.output_buff_size = (D_80088C98 + (0x20000 / sizeof(u64)));
    osCreateMesgQueue(&arg0->queue, &arg0->mesg, 1);
}

void DisplayTask_Submit(UnkStruct80001380* arg0, struct UnkArray4* arg1, s32 arg2) {
    arg0->task.t.data_ptr = (void*)(uintptr_t)arg1->unk_04;
    arg0->task.t.data_size = arg1->unk_08;
    Sched_SubmitTask(arg0, arg2);
}

extern u8 D_8005F664[][2];
extern OSViMode D_80077F40[];
M2C_UNK func_80001234(s8 arg0, s8 arg1) {
    osViSetMode(&D_80077F40[D_8005F664[arg0][arg1]]);
    osViSetSpecialFeatures(OS_VI_DITHER_FILTER_ON);
    osViSetSpecialFeatures(OS_VI_GAMMA_OFF);
    osViSetSpecialFeatures(OS_VI_DIVOT_ON);
}

extern M2C_UNK D_800870D0;

void func_800012AC(s8 *arg0) {
    if (arg0 == NULL) {
        M2C_FIELD(&D_800870D0, s32 *, 0xA88) = 0;
        M2C_FIELD(&D_800870D0, s32 *, 0xA8C) = 0;
        M2C_FIELD(&D_800870D0, s32 *, 0xA90) = 0;
        M2C_FIELD(&D_800870D0, u8 *, 0xA85) = (u8) M2C_FIELD(&D_800870D0, u8 *, 0xA95);
        M2C_FIELD(&D_800870D0, u8 *, 0xA86) = (u8) M2C_FIELD(&D_800870D0, u8 *, 0xA96);
        M2C_FIELD(&D_800870D0, u8 *, 0xA84) = (u8) M2C_FIELD(&D_800870D0, u8 *, 0xA94);
        return;
    }
    M2C_FIELD(&D_800870D0, u8 *, 0xA85) = (u8) M2C_FIELD(arg0, u8 *, 1);
    M2C_FIELD(&D_800870D0, u8 *, 0xA86) = (u8) M2C_FIELD(arg0, u8 *, 2);
    M2C_FIELD(&D_800870D0, u8 *, 0xA84) = (u8) M2C_FIELD(arg0, u8 *, 0);
    M2C_FIELD(&D_800870D0, s32 *, 0xA88) = (s32) M2C_FIELD(arg0, s32 *, 4);
    M2C_FIELD(&D_800870D0, s32 *, 0xA8C) = (s32) M2C_FIELD(arg0, s32 *, 8);
    M2C_FIELD(&D_800870D0, s32 *, 0xA90) = (s32) M2C_FIELD(arg0, s32 *, 0xC);
    M2C_FIELD(&D_800870D0, u8 *, 0xA87) = (u8) M2C_FIELD(arg0, u8 *, 3);
}

void func_8000460C(void*);
void func_80004920(void*);
void func_8000494C(void*);
M2C_UNK func_80001234(s8, s8);

#define DW(type, off) M2C_FIELD(&D_800870D0, type*, off)

void DisplayWorker_ProcessFrame(void) {
    s32 i;
    s32 sp20 = 0;

    if (DW(s32, 0xA98) != 0) {
        func_8000460C(&DW(u8, 0xA18));
    }

    if ((DW(s32, 0xA88) != 0) && (DW(s32, 0xA90) != DW(s32, 0xAB0)) && (DW(u8, 0xA87) != DW(u8, 0xAA7))) {
        DisplayTask_Submit((UnkStruct80001380*)&DW(u8, 0xA18), &DW(UnkArray4, 0xA84), 1);
        sp20 = 1;
    }

    for (i = 1; i < DW(u8, 0xAA4); i++) {
        func_80004920(&DW(u8, 0x9EC));
    }

    while (DW(s32, 0xA04) > 0) {
        func_8000494C(&DW(u8, 0x9EC));
    }

    if (DW(struct unk_D_80068BB0*, 0xAA0) != NULL) {
        osViSwapBuffer(DW(struct unk_D_80068BB0*, 0xAA0)->img_p);
        osViRepeatLine(0);
        if ((DW(u8, 0xAA5) != DW(u8, 0xA95)) || (DW(u8, 0xAA6) != DW(u8, 0xA96))) {
            func_80001234((s8)DW(u8, 0xA95), (s8)DW(u8, 0xA96));
        }
        osViBlack(0U);
        crash_screen_set_draw_info((u16*)DW(struct unk_D_80068BB0*, 0xAA0)->img_p, DW(struct unk_D_80068BB0*, 0xAA0)->width, 0x10);
    } else {
        osViRepeatLine(1);
        osViSwapBuffer(DW(struct unk_D_80068BB0*, 0x9B0)->img_p);
        if ((DW(u8, 0xAA5) != DW(u8, 0xA95)) || (DW(u8, 0xAA6) != DW(u8, 0xA96))) {
            func_80001234((s8)DW(u8, 0xA95), (s8)DW(u8, 0xA96));
        }
    }

    if ((sp20 == 0) && (DW(s32, 0xA88) != 0)) {
        DisplayTask_Submit((UnkStruct80001380*)&DW(u8, 0xA18), &DW(UnkArray4, 0xA84), 0);
    }

    DW(UnkArray4, 0xAA4) = DW(UnkArray4, 0xA94);
    DW(UnkArray4, 0xA94) = DW(UnkArray4, 0xA84);
    profiler_log_thread5_time(THREAD5_END);
    func_80004920(&DW(u8, 0x9EC));
}

#undef DW

#ifdef NON_MATCHING
/* TODO: decompile func_80001558; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_80001558.s")
#endif

extern u8 D_80087B74[];
extern u8 D_80087B64[];
extern OSMesgQueue D_80087ACC;
extern OSMesg D_80087ABC;
extern u8 D_80087AE8[];
extern OSMesgQueue D_80087A8C;
extern OSMesgQueue D_80087AA4;
void func_800594D0(u32);
void func_80001A30(void*, u8, u8, u8, u8, s32, s32, s32);
void func_80004EA8(OSMesg*);
void func_80001140(void*);
void func_800081E0(s32);
s32 func_8004D1C0(OSMesgQueue*, OSMesg*, s32);
s32 func_8004CFB0(OSMesgQueue*, OSMesg, s32);
void func_800012AC(s8* arg0);
void func_80001328(void);
void func_80001558(void);

#ifdef NON_MATCHING
/* TODO: decompile func_800016C4; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_800016C4.s")
#endif

void func_800016C4(void*);

void DisplayWorker_Initialize(void) {
    osCreateThread((OSThread*)&D_800870D0, 5, func_800016C4, NULL, &M2C_FIELD(&D_800870D0, s32*, 0x9B0), 0x28);
    osStartThread((OSThread*)&D_800870D0);
    osCreateMesgQueue(&M2C_FIELD(&D_800870D0, OSMesgQueue*, 0x9BC), &M2C_FIELD(&D_800870D0, OSMesg*, 0x9B4), 1);
    osCreateMesgQueue(&M2C_FIELD(&D_800870D0, OSMesgQueue*, 0x9D4), &M2C_FIELD(&D_800870D0, OSMesg*, 0x9B8), 1);
    M2C_FIELD(&D_800870D0, s16*, 0xA80) = 0;
    M2C_FIELD(&D_800870D0, u8*, 0xA82) = 0;
    M2C_FIELD(&D_800870D0, s32*, 0x9B0) = (s32)GfxImage_Allocate(0, IMAGE_SIZE_BITS_16b, 0x280, 1, MEMORY_POOL_RIGHT);
    Display_ClearFramebufferLine(1);
    Dma_WriteChunks(&D_80087B88, 0xB0000B70, 0xB0000C70, 0);
}

/*
 * Display_ClearFramebufferLine (func_80001948)
 *
 * Writes `color` into 640 consecutive 16-bit entries starting at the image
 * pointer of the image object stored at D_800870A0.unk_9E0 (the one-line,
 * 0x280-wide image allocated in the intro setup function just above). The
 * Stadium 1 version of this function ends with an osWritebackDCache call;
 * the ROM's code for this address has no such call, so none is written.
 * Matching note: the count is a signed local decremented in the loop
 * condition (`width-- > 0`), the form used by the Stadium 1 source.
 */
void Display_ClearFramebufferLine(u16 color) {
    s32 width = 640;
    u16* buf = (u16*)D_800870A0.unk_9E0->img_p;

    while (width-- > 0) {
        *(buf)++ = color;
    }
}

u16 Display_GetFramebufferClearColor(void) {
    u16* ptr = (u16*)D_800870A0.unk_9E0->img_p;
    return *ptr;
}

void Display_WaitForCompletion(void) {
    osRecvMesg(&D_800870A0.unk_A04, NULL, 1);
}

void Display_QueueFramebufferRequest(void* arg0) {
    osSendMesg(&D_800870A0.unk_9EC, arg0, 0);
}

void Display_WaitForFrames(s32 arg0) {
    while (arg0-- > 0) {
        Display_QueueFramebufferRequest(0);
        Display_WaitForCompletion();
    }
}

void Display_SetBufferConfig(struct UnkArray4* arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4, s32 arg5, s32 arg6, s32 arg7) {
    arg0->unk_01 = arg1;
    arg0->unk_02 = arg2;
    arg0->unk_00 = arg3;
    arg0->unk_03 = arg4;
    arg0->unk_04 = arg5;
    arg0->unk_08 = arg6;
    arg0->unk_0C = (struct unk_D_80068BB0*)(uintptr_t)arg7;
}

u32 Audio_GetSpecialSequenceState(void) {
    return D_80087B80;
}

M2C_UNK func_80001234(s8, s8);                      /* extern */
extern M2C_UNK D_800870D0;

void func_80001A78(void) {
    func_80001234(M2C_FIELD(&D_800870D0, s8 *, 0xAA5), M2C_FIELD(&D_800870D0, s8 *, 0xAA6));
}

extern M2C_UNK D_800870D0;

s32 func_80001AA4(void) {
    s32 var_v1;

    var_v1 = 1;
    if (M2C_FIELD(&D_800870D0, s32 *, 0xA98) != 0) {
        var_v1 = M2C_FIELD(&D_800870D0, s32 *, 0xA24) > 0;
    }
    return var_v1;
}

/*
 * Retrieve the current controller bits.
 */
u8 Cont_GetControllerBits(void) {
    return gControllerBits;
}
