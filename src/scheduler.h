/* Declarations for src/scheduler.c. */
#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "global.h"

typedef struct UnkStruct80001380 {
    /* 0x00 */ OSMesg mesg;
    /* 0x04 */ OSMesgQueue queue;
    /* 0x1C */ u16 unk_1C;
    /* 0x1E */ u16 unk_1E;
    /* 0x20 */ OSTask task;
    /* 0x60 */ char unk60[0x8];
} UnkStruct80001380; // size = 0x68

typedef struct unk_D_800A62E0 {
    /* 0x000 */ OSThread thread;
    /* 0x1B0 */ char unk1B0[0x800];
    /* 0x9B0 */ u8 stack[64];
    /* 0x9F0 */ OSMesgQueue queue;
    /* 0xA08 */ u64 time;
    /* 0xA10 */ unk_D_800AA660* unk_A10;
    /* 0xA14 */ UnkStruct80001380* unk_A14;
    /* 0xA18 */ UnkStruct80001380* unk_A18;
    /* 0xA1C */ UnkStruct80001380* unk_A1C;
    /* 0xA20 */ UnkStruct80001380* unk_A20;
    /* 0xA24 */ UnkStruct80001380* unk_A24;
    /* 0xA28 */ s32 unk_A28;
    /* 0xA2C */ s32 unk_A2C;
    /* 0xA30 */ s32 unk_A30;
    /* 0xA34 */ s32 unk_A34;
    /* 0xA38 */ s16 unk_A38;
    /* 0xA3A */ char unkA3A[0x6];
} unk_D_800A62E0; // size = 0xA40

extern unk_D_800A62E0 D_800A9710;

// scheduler.c
void Sched_Init(void);
void Sched_ResetTaskState(UnkStruct80001380* arg0);
void Sched_WaitForTaskMessage(UnkStruct80001380* arg0);
void Sched_RemoveClient(unk_D_800AA660* arg0);
void Sched_SubmitTask(UnkStruct80001380* arg0, s32 arg1);

#endif // SCHEDULER_H
