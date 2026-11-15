/* Stadium Zero resident code. */

#include "global.h"

extern OSDevMgr D_80079370;
extern u32 D_8007938C;
extern OSThread D_80104100;
extern u8 D_801042B0[];
extern OSMesgQueue D_801052B0;
extern OSMesg D_801052C8[5];
extern OSIoMesg D_801052E0;
extern OSIoMesg D_801052F8;
void __osTimerServicesInit(void);
void func_80058980(void);
void func_8005BF00(void*);
void func_8005BD80(OSPri pri) {
    u32 saved_mask;
    OSPri old_pri;
    OSPri my_pri;

    if (D_80079370.active) {
        return;
    }
    __osTimerServicesInit();
    D_8007938C = 0;
    osCreateMesgQueue(&D_801052B0, D_801052C8, 5);
    D_801052E0.hdr.type = OS_MESG_TYPE_VRETRACE;
    D_801052E0.hdr.pri = OS_MESG_PRI_NORMAL;
    D_801052E0.hdr.retQueue = NULL;
    D_801052F8.hdr.type = OS_MESG_TYPE_COUNTER;
    D_801052F8.hdr.pri = OS_MESG_PRI_NORMAL;
    D_801052F8.hdr.retQueue = NULL;
    osSetEventMesg(OS_EVENT_VI, &D_801052B0, &D_801052E0);
    osSetEventMesg(OS_EVENT_COUNTER, &D_801052B0, &D_801052F8);
    old_pri = -1;
    my_pri = osGetThreadPri(NULL);

    if (my_pri < pri) {
        old_pri = my_pri;
        osSetThreadPri(NULL, pri);
    }

    saved_mask = __osDisableInt();
    D_80079370.active = TRUE;
    D_80079370.thread = &D_80104100;
    D_80079370.cmdQueue = &D_801052B0;
    D_80079370.evtQueue = &D_801052B0;
    D_80079370.acsQueue = NULL;
    D_80079370.dma = NULL;
    D_80079370.edma = NULL;
    osCreateThread(&D_80104100, 0, func_8005BF00, &D_80079370, &D_801042B0[0x1000], pri);
    func_80058980();
    osStartThread(&D_80104100);
    __osRestoreInt(saved_mask);

    if (old_pri != -1) {
        osSetThreadPri(NULL, old_pri);
    }
}

typedef struct S0ViContext {
    /* 0x00 */ u16 state;
    /* 0x02 */ u16 retraceCount;
    /* 0x04 */ void* framep;
    /* 0x08 */ void* modep;
    /* 0x0C */ u32 control;
    /* 0x10 */ OSMesgQueue* msgq;
    /* 0x14 */ OSMesg msg;
} S0ViContext;
extern OSTime __osCurrentTime;
extern u32 __osBaseCounter;
extern u32 __osViIntrCount;
void __osViSwapContext(void);
void __osTimerInterrupt(void);
S0ViContext* Audio_GetActiveVoiceCount(void);
void func_8005BF00(void* arg) {
    S0ViContext* vc;
    OSDevMgr* dm;
    OSIoMesg* mb;
    static u16 D_80105310;
    s32 first;
    u32 count;

    mb = NULL;
    first = 0;
    vc = Audio_GetActiveVoiceCount();
    D_80105310 = vc->retraceCount;
    if (D_80105310 == 0) {
        D_80105310 = 1;
    }
    dm = (OSDevMgr*)arg;

    while (TRUE) {
        osRecvMesg(dm->evtQueue, (OSMesg)&mb, OS_MESG_BLOCK);
        switch (mb->hdr.type) {
            case OS_MESG_TYPE_VRETRACE:
                __osViSwapContext();
                D_80105310--;

                if (D_80105310 == 0) {
                    vc = Audio_GetActiveVoiceCount();
                    if (vc->msgq != NULL) {
                        osSendMesg(vc->msgq, vc->msg, OS_MESG_NOBLOCK);
                    }
                    D_80105310 = vc->retraceCount;
                }

                __osViIntrCount++;

                if (first) {
                    count = osGetCount();
                    __osCurrentTime = count;
                    first = 0;
                }

                count = __osBaseCounter;
                __osBaseCounter = osGetCount();
                count = __osBaseCounter - count;
                __osCurrentTime = __osCurrentTime + count;
                break;
            case OS_MESG_TYPE_COUNTER:
                __osTimerInterrupt();
                break;
            default:
                break;
        }
    }
}
