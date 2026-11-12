/* Stadium Zero resident code. */
/* C ported from the Stadium 1 decomp: src/3D140_2.c. */

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
#include "33FE0_types.h"
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
    /* 0x7C */ u32 unk_7C;
    /* 0x80 */ s32 unk_80;
} unk_D_800FCB48;
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
extern u8 sMusicSeqTables[0x134];

void Audio_QueueSequenceIdWrapper(u32 arg0);

void Audio_QueueSequenceId(u32 arg0);

void Audio_QueueSequenceIdWrapper(u32 arg0) {
    Audio_QueueSequenceId(arg0);
}
