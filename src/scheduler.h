/* Declarations for src/scheduler.c. */
#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "global.h"

// A task (graphics, audio or JPEG) handed to the scheduler thread.
typedef struct SchedTask {
    /* 0x00 */ OSMesg mesg; // buffer of queue
    /* 0x04 */ OSMesgQueue queue; // gets 'DONE' when the task finished
    /* 0x1C */ u16 state; // @unverified: from Sched_StartTask/Sched_HandleRspCompletion: 0 queued, 1 running, 2 yield requested, 3 RSP done
    /* 0x1E */ u16 rdpState; // @unverified: from Sched_StartTask/Sched_HandleRdpCompletion: 1 RDP busy, 2 RDP done (or no RDP work)
    /* 0x20 */ OSTask task;
    /* 0x60 */ char unk60[0x8];
} SchedTask; // size = 0x68

// A thread that gets a 'VTRE' message on every video retrace (func_800049E8).
typedef struct SchedClient {
    /* 0x00 */ OSMesg mesgBuf[4]; // @unverified: buffer of queue, created with 4 entries in DisplayWorker_ThreadMain
    /* 0x10 */ OSMesgQueue queue; // @unverified: func_800049E8 sends 'VTRE' to it, func_80004920 receives from it
    /* 0x28 */ struct SchedClient* next; // @unverified: list link walked in func_80004EA8 and Sched_RemoveClient
} SchedClient; // size = 0x2C

typedef struct Scheduler {
    /* 0x000 */ OSThread thread;
    /* 0x1B0 */ u8 threadStack[0x800]; // @unverified: Sched_Init passes its end (mesgBuf) as the thread's stack pointer
    /* 0x9B0 */ OSMesg mesgBuf[16]; // buffer of queue (also the top of threadStack)
    /* 0x9F0 */ OSMesgQueue queue;
    /* 0xA08 */ u64 time;
    /* 0xA10 */ SchedClient* clients; // @unverified: head of the retrace client list (func_80004EA8, func_800049E8)
    /* 0xA14 */ SchedTask* runningTask; // @unverified: the task on the RSP now (Sched_HandleRspEvent)
    /* 0xA18 */ SchedTask* audioTask; // @unverified: the audio task to run (Sched_HandleRetrace, Sched_HandleRspEvent)
    /* 0xA1C */ SchedTask* gfxTask; // @unverified: the graphics or JPEG task to run (Sched_SubmitTask, Sched_HandleRdpEvent)
    /* 0xA20 */ SchedTask* nextAudioTask; // @unverified: audio task waiting for the next retrace (Sched_SubmitTask, Sched_PromotePendingTasks)
    /* 0xA24 */ SchedTask* nextGfxTask; // @unverified: graphics task waiting for the next retrace (Sched_SubmitTask, Sched_PromotePendingTasks)
    /* 0xA28 */ s32 unk_A28;
    /* 0xA2C */ s32 unk_A2C;
    /* 0xA30 */ s32 unk_A30;
    /* 0xA34 */ s32 retraceCount; // @unverified: incremented in Sched_HandleRetrace
    /* 0xA38 */ s16 preNmiFrames; // @unverified: set to 1 by Sched_HandlePreNMI, counts retraces after it; osAfterPreNMI at 26
    /* 0xA3A */ char unkA3A[0x6];
} Scheduler; // size = 0xA40

extern Scheduler D_800A9710;

// scheduler.c
void Sched_Init(void);
void Sched_ResetTaskState(SchedTask* arg0);
void Sched_WaitForTaskMessage(SchedTask* arg0);
void Sched_RemoveClient(SchedClient* arg0);
void Sched_SubmitTask(SchedTask* arg0, s32 arg1);

#endif // SCHEDULER_H
