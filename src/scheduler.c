/* Stadium Zero resident code. */
/* C ported from the Stadium 1 decomp: src/scheduler.c. */

#include "scheduler.h"
#include "game_state.h"
#include "DDC0.h"
#include "profiler.h"
extern unk_D_800A62E0 D_800A9710;

#include "m2c_macros.h"

void Sched_ResetTaskState(UnkStruct80001380* arg0);
void Sched_WaitForTaskMessage(UnkStruct80001380* arg0);
s32 Sched_StartTask(UnkStruct80001380* arg0);
s32 Sched_RequestTaskYield(UnkStruct80001380* arg0);
s32 Sched_HandleRspCompletion(UnkStruct80001380* arg0);
void Sched_HandleRdpCompletion(UnkStruct80001380* arg0);
void Sched_PromotePendingTasks(void);
void func_800049E0(void);
UnkStruct80001380* Sched_TryStartTask(UnkStruct80001380* arg0);
void Sched_StartPendingTask(void);
s32 Sched_TryYieldActiveTask(void);
void Sched_HandleRspEvent(void);
void Sched_HandleRdpEvent(void);
void Sched_Init(void);
void Sched_SubmitTask(UnkStruct80001380* arg0, s32 arg1);

void Sched_ThreadEntry(void* arg0);

/** Writes back the data cache and resets a task's scheduler state. */
void Sched_ResetTaskState(UnkStruct80001380* arg0) {
    osWritebackDCacheAll();
    arg0->unk_1C = 0;
    arg0->unk_1E = 0;
}

/** Blocks until a task's completion message arrives. */
void Sched_WaitForTaskMessage(UnkStruct80001380* arg0) {
    void* sp1C;

    osRecvMesg(&arg0->queue, &sp1C, 1);
}

/**
 * Starts a task on the RSP and RDP if it is ready, returning whether it
 * started.
 */
s32 Sched_StartTask(UnkStruct80001380* arg0) {
    s32 var_v1 = 0;

    if (arg0->unk_1C == 2) {
        osSpTaskLoad(&arg0->task);
        osSpTaskStartGo(&arg0->task);
        arg0->unk_1C = 1;
        var_v1 = 1;
    } else if (arg0->unk_1C == 0) {
        switch (arg0->task.t.type) {
            case M_AUDTASK:
                profiler_log_vblank_time();
                break;

            case M_GFXTASK:
                profiler_log_gfx_time(TASKS_QUEUED);
                arg0->unk_1E = 1;
                osDpSetStatus(0x3C0);
                break;

            case 4:
                arg0->unk_1E = 2;
                break;
        }

        osSpTaskLoad(&arg0->task);
        osSpTaskStartGo(&arg0->task);

        arg0->unk_1C = 1;
        var_v1 = 1;
    }
    return var_v1;
}

/** Asks the running task to yield the RSP. */
s32 Sched_RequestTaskYield(UnkStruct80001380* arg0) {
    s32 var_v1 = 0;

    switch (arg0->task.t.type) {
        case 1:
        case 4:
            if (arg0->unk_1C == 1) {
                arg0->unk_1C = 2;
                osSpTaskYield();
                var_v1 = 1;
            }
            break;
    }

    return var_v1;
}

/** Handles an RSP completion event for a task. */
s32 Sched_HandleRspCompletion(UnkStruct80001380* arg0) {
    s32 sp24 = 0;

    if (arg0->unk_1C == 2) {
        if (osSpTaskYielded(&arg0->task) == 0) {
            arg0->unk_1C = 3;
            switch (arg0->task.t.type) {
                case M_GFXTASK:
                    profiler_log_gfx_time(RSP_COMPLETE);
                    if (arg0->unk_1E == 2) {
                        osSendMesg(&arg0->queue, 'DONE', 0);
                    }
                    break;

                case 4:
                    osSendMesg(&arg0->queue, 'DONE', 0);
                    break;
            }
        }
        sp24 = 1;
    } else {
        switch (arg0->task.t.type) {
            case M_AUDTASK:
                if (arg0->unk_1C == 1) {
                    profiler_log_vblank_time();
                    osSendMesg(&arg0->queue, 'DONE', 0);
                }
                break;

            case M_GFXTASK:
                profiler_log_gfx_time(RSP_COMPLETE);
                if (arg0->unk_1E == 2) {
                    osSendMesg(&arg0->queue, 'DONE', 0);
                }
                break;

            case 4:
                osSendMesg(&arg0->queue, 'DONE', 0);
                break;
        }
        arg0->unk_1C = 3;
    }
    return sp24;
}

/** Handles an RDP completion event for a task. */
void Sched_HandleRdpCompletion(UnkStruct80001380* arg0) {
    profiler_log_gfx_time(RDP_COMPLETE);
    if (arg0->unk_1C == 3) {
        osSendMesg(&arg0->queue, 'DONE', 0);
    }
    arg0->unk_1E = 2;
}

M2C_UNK func_8004D1C0(s32, s32 *, M2C_UNK);         /* extern */

s32 func_80004920(s32 arg0) {
    s32 sp1C;

    func_8004D1C0(arg0 + 0x10, &sp1C, 1);
    return sp1C;
}

s32 func_8000494C(s8 *arg0) {
    s32 sp1C;

    sp1C = 0x4E554C4C;
    if (M2C_FIELD(arg0, s32 *, 0x18) != 0) {
        func_8004D1C0(arg0 + 0x10, &sp1C, 1);
    }
    return sp1C;
}

/** Moves queued tasks into the pending slots. */
void Sched_PromotePendingTasks(void) {
    if ((D_800A9710.unk_A18 == NULL) && (D_800A9710.unk_A20 != NULL)) {
        D_800A9710.unk_A18 = D_800A9710.unk_A20;
        D_800A9710.unk_A20 = NULL;
    }

    if ((D_800A9710.unk_A1C == NULL) && (D_800A9710.unk_A24 != NULL)) {
        D_800A9710.unk_A1C = D_800A9710.unk_A24;
        D_800A9710.unk_A24 = NULL;
    }
}

void func_800049E0(void) {
}

M2C_UNK func_8004CFB0(s8 *, s32, M2C_UNK);        /* extern */
extern s8 *D_800AA120;

void func_800049E8(s32 arg0) {
    s8 *var_s0;

    var_s0 = D_800AA120;
    if (var_s0 != NULL) {
        do {
            func_8004CFB0(var_s0 + 0x10, arg0, 0);
            var_s0 = M2C_FIELD(var_s0, s8 **, 0x28);
        } while (var_s0 != NULL);
    }
}

/** Tries to start a task; returns it when it started and NULL otherwise. */
UnkStruct80001380* Sched_TryStartTask(UnkStruct80001380* arg0) {
    if (arg0 != NULL) {
        if (Sched_StartTask(arg0) == 0) {
            arg0 = NULL;
        }
    }
    return arg0;
}

/** Starts the pending task when the RSP is idle. */
void Sched_StartPendingTask(void) {
    if (D_800A9710.unk_A14 == NULL) {
        D_800A9710.unk_A14 = Sched_TryStartTask(D_800A9710.unk_A1C);
    }
}

/** Tries to make the active task yield for a waiting one. */
s32 Sched_TryYieldActiveTask(void) {
    s32 ret = 0;

    if (D_800A9710.unk_A14 != NULL) {
        ret = Sched_RequestTaskYield(D_800A9710.unk_A14);
    }

    return ret;
}

M2C_UNK func_8000A8BC();                            /* extern */
M2C_UNK func_80026980();                            /* extern */
extern s16 D_800AA148;

/**
 * Handles the pre-NMI (reset button) message: sets D_800AA148 and calls the
 * shutdown hooks func_8000A8BC and func_80026980.
 * Not reached in play (2026-11-13): did not run in a tour of the main menu, Pokédex, party, Lab,
 * registration, Free Battle setup and a COM battle (opening, a switch, running, a Pound turn).
 * @unverified Name from Stadium 1, where the same call sits in the same place.
 */
void Sched_HandlePreNMI(void) {
    D_800AA148 = 1;
    func_8000A8BC();
    func_80026980();
}

/**
 * Seen in play (2026-11-13) (tour of menus and a COM battle): ran in the main menu, the Pokédex,
 * the party screen, the Lab list, Lab sort, registration, the Lab PC, Free Battle setup, the battle
 * opening, a switch in battle, running from battle and a Pound turn.
 * @unverified Name from Stadium 1, matched by code similarity.
 */
void Sched_HandleRetrace(void) {
    D_800A9710.time = osGetTime();
    D_800A9710.unk_A34++;

    if ((D_800A9710.unk_A38 > 0) && (D_800A9710.unk_A38 < 0x1E)) {
        D_800A9710.unk_A38++;
        if (D_800A9710.unk_A38 == 0x1A) {
            osAfterPreNMI();
        }
    }

    Sched_PromotePendingTasks();

    if (D_800A9710.unk_A18 != NULL) {
        if (D_800A9710.unk_A14 == NULL) {
            D_800A9710.unk_A14 = Sched_TryStartTask(D_800A9710.unk_A18);
        } else {
            Sched_TryYieldActiveTask();
        }
    } else if ((D_800A9710.unk_A1C != NULL) && (D_800A9710.unk_A14 == NULL)) {
        D_800A9710.unk_A14 = Sched_TryStartTask(D_800A9710.unk_A1C);
    }

    func_800049E8('VTRE');
}

/**
 * Handles an RSP event: finishes or yields the active task and starts the
 * next.
 */
void Sched_HandleRspEvent(void) {
    UnkStruct80001380* sp24 = D_800A9710.unk_A14;
    s32 tmp = Sched_HandleRspCompletion(D_800A9710.unk_A14);

    D_800A9710.unk_A14 = NULL;

    if (tmp) {
        D_800A9710.unk_A14 = Sched_TryStartTask(D_800A9710.unk_A18);
    }

    if (sp24->unk_1C == 3) {
        switch (sp24->task.t.type) {
            case M_AUDTASK:
                D_800A9710.unk_A18 = 0;
                D_800A9710.unk_A28 = 0;
                D_800A9710.unk_A14 = Sched_TryStartTask(D_800A9710.unk_A1C);
                break;

            case M_GFXTASK:
                if (D_800A9710.unk_A1C->unk_1E == 2) {
                    D_800A9710.unk_A1C = NULL;
                    D_800A9710.unk_A2C = 0;
                }
                break;

            case 4:
                D_800A9710.unk_A1C = NULL;
                D_800A9710.unk_A30 = 0;
                break;
        }
    }
}

/** Handles an RDP event: finishes the RDP task and notifies its client. */
void Sched_HandleRdpEvent(void) {
    Sched_HandleRdpCompletion(D_800A9710.unk_A1C);
    if (D_800A9710.unk_A1C->unk_1C == 3) {
        D_800A9710.unk_A1C = NULL;
        D_800A9710.unk_A2C = 0;
    }
}

/*
 * Sched_ThreadEntry  (owner func_80004D14)
 *
 * Main loop of the graphics scheduler thread.  Start-up:
 *   - set the FPU control/status register to 0x01000F00 (the underflow,
 *     overflow, divide-by-zero and invalid-operation exceptions enabled;
 *     the flush-to-zero bit set),
 *   - create the scheduler's 16-entry message queue,
 *   - register the queue for the video retrace message (0x66) and for the
 *     RSP-done (0x64), RDP-done (0x65) and pre-NMI (0x68) OS events.
 * Then it blocks on the queue forever and dispatches on the message:
 *   0x66 video retrace    -> Sched_HandleRetrace
 *   0x64 RSP finished     -> Sched_HandleRspEvent
 *   0x65 RDP finished     -> Sched_HandleRdpEvent
 *   0x67 start next task  -> Sched_StartPendingTask (sent by other
 *                            scheduler code with osSendMesg)
 *   0x68 pre-NMI          -> Sched_HandlePreNMI
 * Unknown messages are ignored.  `arg0` is the thread argument and is unused.
 */
void Sched_ThreadEntry(void* arg0) {
    s32 sp24;

    __osSetFpcCsr(0x01000F00);
    osCreateMesgQueue(&D_800A9710.queue, D_800A9710.stack, 0x10);
    osViSetEvent(&D_800A9710.queue, 0x66, 1);
    osSetEventMesg(4, &D_800A9710.queue, 0x64);   /* OS_EVENT_SP */
    osSetEventMesg(9, &D_800A9710.queue, 0x65);   /* OS_EVENT_DP */
    osSetEventMesg(0xE, &D_800A9710.queue, 0x68); /* OS_EVENT_PRENMI */

    while (true) {
        osRecvMesg(&D_800A9710.queue, &sp24, 1);

        switch (sp24) {
            case 0x66:
                Sched_HandleRetrace();
                break;

            case 0x64:
                Sched_HandleRspEvent();
                break;

            case 0x65:
                Sched_HandleRdpEvent();
                break;

            case 0x67:
                Sched_StartPendingTask();
                break;

            case 0x68:
                Sched_HandlePreNMI();
                break;
        }
    }
}

/** Initializes the scheduler state. */
void Sched_Init(void) {
    D_800A9710.unk_A10 = NULL;
    D_800A9710.unk_A14 = NULL;
    D_800A9710.unk_A18 = 0;
    D_800A9710.unk_A1C = NULL;
    D_800A9710.unk_A20 = NULL;
    D_800A9710.unk_A24 = NULL;
    D_800A9710.unk_A28 = 0;
    D_800A9710.unk_A2C = 0;
    osCreateThread(&D_800A9710.thread, 3, Sched_ThreadEntry, NULL, D_800A9710.stack, 0x64);
    osStartThread(&D_800A9710.thread);
}

void func_80004EA8(s8 *arg0)
{
  s8 *var_a1;
  s8 *var_v1;
  if ((*((s8 **) (((s8 *) (&(*((s8 *) (&D_800A9710))))) + 0xA10))) == 0) // FAKE: decomp slop, raw pointer casts stand in for struct fields
  {
    *((s8 **) ((&(*((s8 *) (&D_800A9710)))) + 0xA10)) = arg0;
  }
  else
  {
    var_v1 = *((s8 **) (((s8 *) (&(*((s8 *) (&D_800A9710))))) + 0xA10)); // FAKE: decomp slop, raw pointer casts stand in for struct fields
    var_a1 = *((s8 **) (((s8 *) (*((s8 **) (((s8 *) (&(*((s8 *) (&D_800A9710))))) + 0xA10)))) + 0x28)); // FAKE: decomp slop, raw pointer casts stand in for struct fields
    if (var_a1 != 0)
    {
      do
      {
        var_v1 = var_a1;
        var_a1 = *((s8 **) (((s8 *) var_a1) + 0x28));
      }
      while (var_a1 != 0);
    }
    *((s8 **) (((s8 *) var_v1) + 0x28)) = arg0;
  }
  *((s32 *) (((s8 *) arg0) + 0x28)) = 0;
}

/** Removes a client from the scheduler's client list. */
void Sched_RemoveClient(unk_D_800AA660* arg0) {
    unk_D_800AA660** var_v0 = &D_800A9710.unk_A10;
    unk_D_800AA660* var_v1 = D_800A9710.unk_A10;

    while (var_v1 != NULL) {
        if (var_v1 == arg0) {
            *var_v0 = M2C_FIELD(var_v1, unk_D_800AA660**, 0x28);
            break;
        }
        var_v0 = &M2C_FIELD(var_v1, unk_D_800AA660**, 0x28);
        var_v1 = M2C_FIELD(var_v1, unk_D_800AA660**, 0x28);
    }
}

/** Submits a task to the scheduler's queue for a client. */
void Sched_SubmitTask(UnkStruct80001380* arg0, s32 arg1) {
    if (arg0 != NULL) {
        Sched_ResetTaskState(arg0);

        switch (arg0->task.t.type) {
            case 2:
                D_800A9710.unk_A20 = arg0;
                break;

            case 1:
                if ((arg1 != 0) && (D_800A9710.unk_A1C == NULL)) {
                    D_800A9710.unk_A1C = arg0;
                    D_800A9710.unk_A24 = NULL;
                    osSendMesg(&D_800A9710.queue, 0x67, 0);
                } else {
                    D_800A9710.unk_A24 = arg0;
                }
                break;

            case 4:
                if (D_800A9710.unk_A1C == NULL) {
                    D_800A9710.unk_A1C = arg0;
                    D_800A9710.unk_A24 = NULL;
                    osSendMesg(&D_800A9710.queue, 0x67, 0);
                }
                break;
        }
    }
}

s32 func_80005014(void) {
    s32 var_v1;

    var_v1 = M2C_FIELD(&D_800A9710, s32 *, 0xA1C) != 0;
    if (var_v1 == 0) {
        var_v1 = M2C_FIELD(&D_800A9710, s32 *, 0xA24) != 0;
    }
    return var_v1;
}
