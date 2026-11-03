/* Stadium Zero resident code. */
/* C ported from the Stadium 1 decomp: src/3D140.c. */

#include "3D140.h"
#include "lib/ultralib/include/PR/leo.h"
#include "audio_commands.h"
#include "libnumus/player.h"
#include "3D140.h"
#include "gb_audio.h"
#include "libnaudio/n_libaudio_sc.h"
#include "libnaudio/n_libaudio_sn_sc.h"
#include "audio_stream.h"
#include "gb_audio_render.h"
#include "audio_loop_point.h"
typedef union {
    struct {
        s16 type;
    } gen;
    struct {
        s16 type;
        struct AudioInfo* info;
    } done;
} AudioMsg;
typedef struct AudioInfo {
    /* 0x00 */ s16* data;
    /* 0x04 */ s16 frameSamples;
    /* 0x08 */ AudioMsg msg;
} AudioInfo;
#define NUM_ACMD_LISTS 2
#define NUM_OUTPUT_BUFFERS 2
#define MAX_MESGS 3
#define NUM_DMA_BUFFERS 48
#define SAMPLES 184
typedef struct AMAudioMgr {
    /* 0x000 */ Acmd* ACMDList[NUM_ACMD_LISTS];
    /* 0x008 */ AudioInfo* audioInfo[NUM_OUTPUT_BUFFERS];
    /* 0x010 */ char unk10[0x228];
    ///* 0x010 */ OSThread thread;
    ///* 0x1C0 */ OSMesgQueue audioFrameMsgQ;
    ///* 0x1D8 */ OSMesg audioFrameMsgBuf[MAX_MESGS];
    ///* 0x1E0 */ OSMesgQueue audioReplyMsgQ;
    ///* 0x1F8 */ OSMesg audioReplyMsgBuf[MAX_MESGS];
    /* 0x238 */ ALGlobals g;
} AMAudioMgr;
typedef struct AMDMABuffer {
    /* 0x00 */ ALLink node;
    /* 0x08 */ u32 startAddr;
    /* 0x0C */ u32 lastFrame;
    /* 0x10 */ char* ptr;
} AMDMABuffer;
typedef struct AMDMAState {
    /* 0x00 */ u8 initialized;
    /* 0x04 */ AMDMABuffer* firstUsed;
    /* 0x08 */ AMDMABuffer* firstFree;
} AMDMAState;
typedef struct unk_D_800FCB48 {
    /* 0x00 */ u16 unk_00[16];
    /* 0x20 */ s32 unk_20;
    /* 0x24 */ s32 unk_24;
    /* 0x28 */ u16 unk_28[16];
    /* 0x48 */ s32 unk_48;
    /* 0x4C */ s32 unk_4C;
    /* 0x50 */ u16 unk_50[16];
    /* 0x70 */ s32 unk_70;
    /* 0x74 */ s32 unk_74;
    /* 0x78 */ u32 unk_78;
    /* 0x7C */ s32 unk_7C;
    /* 0x80 */ s32 unk_80;
} unk_D_800FCB48;
typedef struct unk_D_80078548 {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 unk_01;
} unk_D_80078548;
extern s32 D_80075C30;
extern s8 D_800B3CE0;
extern u8 D_800B3CE8;
extern s32 D_800B3CEC;
extern AMAudioMgr __am;
extern AMDMAState dmaState;
extern s32 minFrameSize;
extern u32 frameSize;
extern s32 maxFrameSize;
extern s32 maxRSPCmds;
extern OSMesgQueue audDMAMessageQ;
extern AMDMABuffer* dmaBuffs;
extern OSIoMesg* audDMAIOMesgBuf;
extern OSMesg* audDMAMessageBuf;
extern u32 dmaBufferLen;
extern OSPiHandle* D_800B3FC0[4];
void Audio_QueueSoundWithFallbackList(u16, u16*, u8*);
u32 Battle_EstimateMoveDamage(u32, BattleMonRuntime*, BattleMonRuntime*);
s32 Battle_MapCategoryIdToCompactIndex(u8);
ALDMAproc __amDmaNew(AMDMAState** state);
extern u8 D_80075E04[4];
extern f32 D_80075E08;
extern u8 D_80075E10[4];
extern u16 D_80075E14;
extern u32 D_80075E18;
extern s32 D_80075E20;
extern u32 audFrameCt;
extern u32 nextDMA;
extern u32 curAcmdList;
extern AudioInfo* lastInfo;
extern s32 min_only_one;
extern s32 mus_active_fade_handle;
extern f32 mus_fade_start_volume;
extern u8 mus_fade_target_volume;
extern f32 mus_fade_step_rate;
extern u8 mus_sound_effect_blocked;
void Audio_UpdateBattleAudioFrame(void);
#define FRAME_LAG 1

#include "m2c_macros.h"

s32 __amDMA(s32 addr, s32 len, void* state);
ALDMAproc __amDmaNew(AMDMAState** state);
void __clearAudioDMA(void);
void Cry_SetEnabled(s32 arg0);
void Cry_PlayFromPokedex(s32 arg0);
s32 Cry_IsPlaying(void);
s32 Audio_GetDiskReadyStatus(u8* arg0);
void Audio_SetDiskReadyPolling(s32 arg0);

#ifdef NON_MATCHING
/* TODO: decompile func_8003A890; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_8003A890.s")
#endif

s32 n_alEnvmixerParam(N_PVoice* filter, s32 paramID, void* param) {
    N_PVoice* e = filter;

    switch (paramID) {
        case (AL_FILTER_ADD_UPDATE):
            if (e->em_ctrlTail) {
                e->em_ctrlTail->next = (ALParam*)param;
            } else {
                e->em_ctrlList = (ALParam*)param;
            }
            e->em_ctrlTail = (ALParam*)param;
            break;
        case (AL_FILTER_RESET):
            e->em_first = 1;
            e->em_motion = AL_STOPPED;
            e->em_volume = 1;
            e->rs_delta = 0.0;
            e->rs_first = 1;
            e->rs_upitch = 0;
            n_alLoadParam(e, AL_FILTER_RESET, param);
            break;
        case (AL_FILTER_START):
            e->em_motion = AL_PLAYING;
            break;
        default:
            n_alLoadParam(e, paramID, param);
            break;
    }
    return 0;
}

#ifdef NON_MATCHING
/* TODO: decompile func_8003AECC; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_8003AECC.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_8003B0F8; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_8003B0F8.s")
#endif

s16 func_8003B280(s16 arg0, s32 arg1, s16 arg2, u16 arg3) {
    s32 delta;

    arg1 >>= 3;
    if (arg1 == 0) {
        return arg0;
    }
    delta = ((s32)(arg3 * arg1) >> 16) + (arg2 * arg1);
    arg0 += delta;
    return arg0;
}

#ifdef NON_MATCHING
/* TODO: decompile func_8003B2E0; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_8003B2E0.s")
#endif

s32 __amDMA(s32 addr, s32 len, void* state) {
    void* foundBuffer;
    s32 delta;
    AMDMABuffer* sp34;
    OSIoMesg* ioMesg;
    AMDMABuffer* dmaPtr;
    AMDMABuffer* lastDmaPtr;
    OSPiHandle* sp2C;
    s32 buffEnd;

    if (D_80075C30 & 0x80000000) {
        return osVirtualToPhysical(addr);
    }

    sp2C = D_800B3FC0[0];
    dmaPtr = dmaState.firstUsed;
    lastDmaPtr = NULL;
    while (dmaPtr) {
        buffEnd = dmaPtr->startAddr + dmaBufferLen;

        if (dmaPtr->startAddr > addr) {
            break;
        }

        if (buffEnd >= (addr + len)) {
            dmaPtr->lastFrame = audFrameCt;
            return osVirtualToPhysical(dmaPtr->ptr + addr - dmaPtr->startAddr);
        }

        lastDmaPtr = dmaPtr;
        dmaPtr = dmaPtr->node.next;
    }

    dmaPtr = dmaState.firstFree;
    if (!dmaPtr) {
        return osVirtualToPhysical(dmaState.firstUsed);
    }

    dmaState.firstFree = dmaPtr->node.next;
    alUnlink(&dmaPtr->node);

    if (lastDmaPtr != NULL) {
        alLink(&dmaPtr->node, &lastDmaPtr->node);
    } else if (dmaState.firstUsed) {
        lastDmaPtr = dmaState.firstUsed;

        dmaState.firstUsed = dmaPtr;
        dmaPtr->node.next = lastDmaPtr;
        dmaPtr->node.prev = NULL;

        lastDmaPtr->node.prev = &dmaPtr->node;
    } else {
        dmaState.firstUsed = dmaPtr;
        dmaPtr->node.next = NULL;
        dmaPtr->node.prev = NULL;
    }

    foundBuffer = dmaPtr->ptr;
    delta = addr & 1;
    addr -= delta;
    dmaPtr->startAddr = addr;
    dmaPtr->lastFrame = audFrameCt;

    ioMesg = audDMAIOMesgBuf + nextDMA++;
    ioMesg->hdr.pri = OS_MESG_PRI_HIGH;
    ioMesg->hdr.retQueue = &audDMAMessageQ;
    ioMesg->devAddr = addr;
    ioMesg->dramAddr = foundBuffer;
    ioMesg->size = dmaBufferLen;

    osInvalDCache(foundBuffer, dmaBufferLen);
    osEPiStartDma(sp2C, ioMesg, OS_READ);

    return osVirtualToPhysical(foundBuffer) + delta;
}

#ifdef NON_MATCHING
/* TODO: decompile func_8003B868; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_8003B868.s")
#endif

ALDMAproc __amDmaNew(AMDMAState** state) {
    if (!dmaState.initialized) {
        dmaState.firstUsed = NULL;
        dmaState.firstFree = &dmaBuffs[0];
        dmaState.initialized = TRUE;
    }

    *state = &dmaState;

    return __amDMA;
}

void __clearAudioDMA(void) {
    s32 i;
    void* sp40;
    AMDMABuffer* var_s0_2;
    ALLink* node;

    for (i = 0; i < nextDMA; i++) {
        osRecvMesg(&audDMAMessageQ, &sp40, 0);
    }

    var_s0_2 = dmaState.firstUsed;
    while (var_s0_2 != NULL) {
        node = var_s0_2->node.next;

        if ((var_s0_2->lastFrame + FRAME_LAG) < audFrameCt) {
            if (var_s0_2 == dmaState.firstUsed) {
                dmaState.firstUsed = var_s0_2->node.next;
            }

            alUnlink(var_s0_2);

            if (dmaState.firstFree != NULL) {
                alLink(var_s0_2, dmaState.firstFree);
            } else {
                dmaState.firstFree = var_s0_2;
                var_s0_2->node.next = NULL;
                var_s0_2->node.prev = NULL;
            }
        }

        var_s0_2 = node;
    }

    nextDMA = 0;
}

extern s32 D_80075E00;

void func_8003BC9C(s32 arg0) {
    switch (arg0) {                                 /* irregular */
    case 0:
        D_80075E00 = 0;
        return;
    case 1:
        D_80075E00 = 1;
        return;
    case 2:
        D_80075E00 = 2;
        return;
    default:
        D_80075E00 = 1;
        return;
    }
}

void Cry_SetEnabled(s32 arg0) {
    const f32 D_8007C7C0 = 0.8000000119f;
    if (arg0 != 0) {
        func_80044BA8(0x7D00, 0x78, 0x640);
        D_80075E04[0] = 1;
        D_80075E08 = D_8007C7C0;
        return;
    }
    D_80075E04[0] = 0;
}

void Cry_PlayFromPokedex(s32 arg0) {
    if (D_80075E04[0] == 0) {
        func_80044BA8(0x7D00, 0x78, 0x320);
        D_80075E04[0] = 1;
        D_80075E10[0] = 1;
        D_80075E08 = 0.0f;
        D_80075E14 = arg0;
        D_80075E18 = 0;
        D_800B3CE0 = 0;
    }
}

void func_8003BDB0(void) {
    switch (D_80075E10[0]) {
        case 1:
            func_8003C110(D_80075E14);
            D_80075E10[0]++;
            D_80075E18 = 0;
            break;
        case 2:
            if (++D_80075E18 >= 2) {
                D_80075E18 = 0;
                D_80075E10[0]++;
                D_800B3CE0 = 1;
            }
            break;
        case 3:
            if (func_8003E058() == 0) {
                D_80075E10[0]++;
                D_80075E18 = 0;
            }
            break;
        case 4:
            if (D_80075E18 >= 0x1F) {
                D_80075E10[0]++;
            }
            D_80075E18++;
            break;
        case 5:
            D_80075E10[0] = 0;
            D_80075E04[0] = 0;
            D_800B3CE0 = 0;
            break;
    }
}

s32 Cry_IsPlaying(void) {
    return D_80075E04[0];
}

s32 func_800384D8();                                /* extern */
M2C_UNK func_80058100(s32);                         /* extern */
extern s8 D_80075E0C;
extern s32 D_80075E30;
extern s8 D_800B3F78;
extern s32 D_800B3F94;

s32 func_8003BED8(s32 arg0) {
    if (arg0 == 0) {
        if (func_800384D8() != 0) {
            return 0;
        }
        D_80075E0C = 1;
        goto block_5;
    }
    func_80058100(D_800B3F94);
    D_80075E30 = 0;
    D_800B3F78 = 0;
    D_80075E0C = 0;
block_5:
    return 1;
}

s32 Audio_GetDiskReadyStatus(u8* arg0) {
    if (D_80075E20 == 0) {
        *arg0 = 7;
        return 8;
    }
    *arg0 = D_800B3CE8;
    return D_800B3CEC;
}

void Audio_SetDiskReadyPolling(s32 arg0) {
    if (arg0 == 1) {
        D_80075E20 = 1;
        return;
    }
    D_80075E20 = 0;
}
