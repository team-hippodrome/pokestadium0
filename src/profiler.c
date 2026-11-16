/* Stadium Zero resident code. */
/* C ported from the Stadium 1 decomp: src/profiler.c. */

#include "global.h"
#include "profiler.h"
#include "scheduler.h"
extern struct Profiler gProfiler;
#define UNK_FPS_60_APPROX_VALUE 770296

void Profiler_LogThread5Time(enum ProfilerGameEvent eventID);
void Profiler_LogThread4Time(void);
void Profiler_LogGfxTime(enum ProfilerGfxEvent eventID);
void Profiler_LogVblankTime(void);
void Profiler_DrawRect(s32 ulx, s32 lrx, s32 uly_in, u16 color);
void Profiler_DrawBarCpu(OSTime clockBase, OSTime clockStart, OSTime clockEnd, s16 posY, u16 color);
void Profiler_DrawBarCpuKeepMax(OSTime start, OSTime end, s16 posY, s16* last_max, s16* reset_ctr);
void Profiler_DrawReferenceBars(void);
void Profiler_DrawMode1(void);
void Profiler_DrawMode0(void);
void Profiler_Draw(s32 profiler_mode);
void Profiler_PrintMetrics(void);
void Profiler_ClearData(void);
u32 Profiler_SetGetTimeDiff(enum SetGetTimeDiff state);

// log the current osTime to the appropriate idx for current thread5 processes.
/** Logs a time stamp for thread 5 events. */
void Profiler_LogThread5Time(enum ProfilerGameEvent event_id) {
    if (event_id == THREAD5_START) {
        gProfiler.profiler_data[gProfiler.frameIdx1].gameTimes[event_id] = D_800A9710.time;
    } else {
        gProfiler.profiler_data[gProfiler.frameIdx1].gameTimes[event_id] = osGetTime();
    }

    // event ID 3 is the last profiler event for after incrementing
    // buffers: increment the Info after updating.
    if (event_id == THREAD5_END) {
        if (gProfiler.frameIdx1 == 2) {
            gProfiler.frameIdx1 = 0;
        } else {
            gProfiler.frameIdx1++;
        }
        gProfiler.profiler_data[gProfiler.frameIdx1].numSoundTimes = 0;
    }
}

// log the audio system before and after osTimes in pairs to the soundTimes array.
/** Logs a time stamp for thread 4. */
void Profiler_LogThread4Time(void) {
    struct ProfilerFrameData* profiler = &gProfiler.profiler_data[gProfiler.frameIdx1];

    if (profiler->numSoundTimes < ARRAY_COUNT(profiler->soundTimes)) {
        profiler->soundTimes[profiler->numSoundTimes++] = osGetTime();
    }
}

// log the times for gfxTimes: RSP completes, and RDP completes.
/** Logs a time stamp for a graphics event. */
void Profiler_LogGfxTime(enum ProfilerGfxEvent event_id) {
    if (event_id == TASKS_QUEUED) {
        if (gProfiler.frameIdx2 == 2) {
            gProfiler.frameIdx2 = 0;
        } else {
            gProfiler.frameIdx2++;
        }
        gProfiler.profiler_data[gProfiler.frameIdx2].numVblankTimes = 0;
    }
    gProfiler.profiler_data[gProfiler.frameIdx2].gfxTimes[event_id] = osGetTime();
}

// log the times between vblank started and ended.
/** Logs a time stamp for the vertical blank. */
void Profiler_LogVblankTime(void) {
    struct ProfilerFrameData* profiler = &gProfiler.profiler_data[gProfiler.frameIdx2];

    if (profiler->numVblankTimes < ARRAY_COUNT(profiler->vblankTimes)) {
        profiler->vblankTimes[profiler->numVblankTimes++] = osGetTime();
    }
}

/*
 * Render the actual rectangle for the profiler display.
 */
void Profiler_DrawRect(s32 ulx, s32 lrx, s32 uly_in, u16 color) {
    s32 uly = uly_in;
    s32 lry = uly + 2;

    if (StageContext_IsHighResolution() != 0) {
        ulx <<= 1;
        lrx <<= 1;
        uly <<= 1;
        lry <<= 1;
    }

    gDPPipeSync(gDisplayListHead++);
    gDPSetFillColor(gDisplayListHead++, (color << 0x10) | color);
    gDPFillRectangle(gDisplayListHead++, ulx, uly, lrx, lry);
}

// Draw the CPU bar.
/** Draws one CPU profiler bar from a start and end time. */
void Profiler_DrawBarCpu(OSTime clock_base, OSTime clock_start, OSTime clock_end, s16 pos_y, u16 color) {
    s64 duration_start, duration_end;
    s32 rect_x1, rect_x2;

    // set the duration to start, and floor to 0 if the result is below 0.
    if ((duration_start = clock_start - clock_base) < 0) {
        duration_start = 0;
    }
    // like the above, but with end.
    if ((duration_end = clock_end - clock_base) < 0) {
        duration_end = 0;
    }

    // calculate the x coordinates of where start and end begins, respectively.
    // convert the cycles to microseconds, but multiply by 3 before converting them
    // to nanoseconds. So why not just use OS_CYCLES_TO_NSEC?
    rect_x1 = ((OS_CYCLES_TO_USEC(duration_start)) * 3ULL / 1000ULL) + 30;
    rect_x2 = ((OS_CYCLES_TO_USEC(duration_end)) * 3ULL / 1000ULL) + 30;

    if (rect_x1 > 225) {
        rect_x1 = 225;
    }
    if (rect_x2 > 225) {
        rect_x2 = 225;
    }

    // perform the render if start is less than end. in most cases, it should be.
    if (rect_x1 < rect_x2) {
        Profiler_DrawRect(rect_x1, rect_x2, pos_y, color);
    }
}

/*
 * Similar to Profiler_DrawBarCpu, draw a CPU bar, but this time, draw it based on
 * the maximum value observed in the last 16 calls. This may be useful for observing
 * quick rises in lag over a duration period.
 */
void Profiler_DrawBarCpuKeepMax(OSTime start, OSTime end, s16 pos_y, s16* last_max, s16* reset_ctr) {
    s64 duration;
    s32 ulx;
    s32 lrx;

    // set the duration, and floor to 0 if the result is below 0.
    if ((duration = end - start) < 0) {
        duration = 0;
    }

    // like earlier, multiply by 3 and convert to nsec by dividing by 1000.
    // why not just use OS_CYCLES_TO_NSEC?
    lrx = (OS_CYCLES_TO_USEC(duration) * 3ULL / 1000ULL) + 30;
    if (lrx > 225) {
        lrx = 225;
    }

    // Keep the maximum lrx seen in the last 16 calls. If a new max is seen, reset
    // the counter to start over and set the new observed maximum.
    if (++*reset_ctr > 15 || *last_max < lrx) {
        *reset_ctr = 0;
        *last_max = lrx;
    }

    // now that we have a max, build the coordinates to make the rect.
    lrx = *last_max;
    ulx = lrx - 4;
    if (ulx < 30) {
        ulx = 30;
    }

    if (ulx < lrx) {
        Profiler_DrawRect(ulx, lrx, pos_y, GPACK_RGBA5551(160, 200, 248, 1)); // #A0C8F8
    }
}

/** Draws the reference maximum bars under the profiler bars. */
void Profiler_DrawReferenceBars(void) {
    // Draws the reference "max" bars underneath the real thing.
    Profiler_DrawRect(30, 79, 220, GPACK_RGBA5551(40, 80, 255, 1));    // Blue
    Profiler_DrawRect(79, 128, 220, GPACK_RGBA5551(255, 255, 40, 1));  // Yellow
    Profiler_DrawRect(128, 177, 220, GPACK_RGBA5551(255, 120, 40, 1)); // Orange
    Profiler_DrawRect(177, 226, 220, GPACK_RGBA5551(255, 40, 40, 1));  // Red
}

/*
 * Draw Profiler Mode 1. This mode draws a traditional per-event bar for durations
 * of tasks recorded by the profiler calls of various threads.
 */
void Profiler_DrawMode1(void) {
    s32 i;
    struct ProfilerFrameData* profiler;
    struct ProfilerFrameData* profiler_2;
    OSTime clock_base;

    // set profiler pointers. first pointer is for game+sound profiler and 2nd is for gfx and vblank.
    profiler = &gProfiler.profiler_data[(gProfiler.frameIdx1 == 0) ? 2 : gProfiler.frameIdx1 - 1];
    profiler_2 = &gProfiler.profiler_data[(gProfiler.frameIdx2 == 0) ? 2 : gProfiler.frameIdx2 - 1];

    // calculate the clock_base.
    clock_base = profiler->gameTimes[0] - UNK_FPS_60_APPROX_VALUE;

    // (yellow)
    Profiler_DrawBarCpu(clock_base, profiler->gameTimes[0], profiler->gameTimes[1], 212,
                          GPACK_RGBA5551(255, 255, 40, 1)); // #FFFF28

    // (orange)
    Profiler_DrawBarCpu(clock_base, profiler->gameTimes[1], profiler->gameTimes[2], 212,
                          GPACK_RGBA5551(255, 120, 40, 1)); // #FF7828

    // we need to get the amount of finished numSoundTimes pairs, so get rid of the odd bit to get the
    // limit of finished pairs.
    profiler->numSoundTimes &= 0xFFFE;

    // draw the sound update times. (red)
    for (i = 0; i < profiler->numSoundTimes; i += 2) {
        Profiler_DrawBarCpu(clock_base, profiler->soundTimes[i], profiler->soundTimes[i + 1], 212,
                              GPACK_RGBA5551(255, 40, 40, 1)); // #FF2828
    }

    //! RSP and RDP run in parallel, so while they are not absolutely guaranteed to return in order,
    //  it is theoretically possible they might not. In all cases, the RDP should finish later than RSP.
    //  Thus, this is not really a bug in practice, but should still be noted that the C doesn't check
    //  this.
    Profiler_DrawBarCpu(clock_base, profiler_2->gfxTimes[0], profiler_2->gfxTimes[1], 216,
                          GPACK_RGBA5551(255, 255, 40, 1)); // #FFFF28
    Profiler_DrawBarCpu(clock_base, profiler_2->gfxTimes[1], profiler_2->gfxTimes[2], 216,
                          GPACK_RGBA5551(255, 120, 40, 1)); // #FF7828

    // like earlier, toss the odd bit.
    profiler_2->numVblankTimes &= 0xFFFE;

    // render the vblank time pairs. (red)
    for (i = 0; i < profiler_2->numVblankTimes; i += 2) {
        Profiler_DrawBarCpu(clock_base, profiler_2->vblankTimes[i], profiler_2->vblankTimes[i + 1], 216,
                              GPACK_RGBA5551(255, 40, 40, 1)); // #FF2828
    }

    Profiler_DrawReferenceBars();
}

/*
 * Draw Profiler Mode 0. This mode renders bars over each other to make it
 * easier to see which processes take the longest.
 */
void Profiler_DrawMode0(void) {
    s32 i; // set profiler pointers. first pointer is for game+sound profiler and 2nd is for gfx and vblank.
    struct ProfilerFrameData* profiler =
        &gProfiler.profiler_data[(gProfiler.frameIdx1 == 0) ? 2 : gProfiler.frameIdx1 - 1];
    OSTime clock_start =
        profiler->gameTimes[0] <= profiler->soundTimes[0] ? profiler->gameTimes[0] : profiler->soundTimes[0];
    OSTime game_duration = profiler->gameTimes[1] - clock_start;
    OSTime render_duration = profiler->gameTimes[2] - profiler->gameTimes[1];
    OSTime task_start = 0;
    struct ProfilerFrameData* profiler_2 =
        &gProfiler.profiler_data[(gProfiler.frameIdx2 == 0) ? 2 : gProfiler.frameIdx2 - 1];
    OSTime rsp_duration = profiler_2->gfxTimes[1] - profiler_2->gfxTimes[0];
    OSTime rdp_duration = profiler_2->gfxTimes[2] - profiler_2->gfxTimes[0];
    OSTime vblank = 0;
    static s16 s_render_last_max = 0;
    static s16 s_render_reset_ctr = 0;
    static s16 sRDPLastMax = 0;
    static s16 sRDPResetCtr = 0;

    // like above functions, toss the odd bit.
    profiler->numSoundTimes &= 0xFFFE;

    // sound duration seems to be rendered with empty space and not actually drawn.
    for (i = 0; i < profiler->numSoundTimes; i += 2) {
        // calculate sound duration of max - min
        u64 sound_duration = profiler->soundTimes[i + 1] - profiler->soundTimes[i];
        task_start += sound_duration;
        // was the sound time minimum less than game execution?
        if (profiler->soundTimes[i] < profiler->gameTimes[1]) {
            // overlay the game_duration onto the profiler by subtracting the sound_duration.
            game_duration -= sound_duration;
        } else if (profiler->soundTimes[i] < profiler->gameTimes[2]) {
            // overlay the render_duration onto the profiler by subtracting the sound_duration.
            render_duration -= sound_duration;
        }
    }

    // same as above. toss the odd bit.
    profiler_2->numVblankTimes &= 0xFFFE;

    for (i = 0; i < profiler_2->numVblankTimes; i += 2) {
        vblank += (profiler_2->vblankTimes[i + 1] - profiler_2->vblankTimes[i]);
    }

    // draw sound duration as the first bar. (red)
    clock_start = 0;
    Profiler_DrawBarCpu(0, clock_start, clock_start + task_start, 212, GPACK_RGBA5551(255, 40, 40, 1)); // #FF2828

    // draw game execution duration. (yellow)
    clock_start += task_start;
    Profiler_DrawBarCpu(0, clock_start, clock_start + game_duration, 212, GPACK_RGBA5551(255, 255, 40, 1)); // #FFFF28

    // draw render duration. (orange)
    clock_start += game_duration;
    Profiler_DrawBarCpu(0, clock_start, clock_start + render_duration, 212, GPACK_RGBA5551(255, 120, 40, 1)); // #FF7828

    Profiler_DrawBarCpuKeepMax(0, clock_start + render_duration, 212, &s_render_last_max, &s_render_reset_ctr);

    // Draw bottom profilers.

    // rdp duration (orange)
    Profiler_DrawBarCpu(0, 0, rdp_duration, 216, GPACK_RGBA5551(255, 120, 40, 1)); // #FF7828
    // rsp duration (yellow)
    Profiler_DrawBarCpu(0, 0, rsp_duration, 216, GPACK_RGBA5551(255, 255, 40, 1)); // #FFFF28
    // vblank duration (red)
    Profiler_DrawBarCpu(0, 0, vblank, 216, GPACK_RGBA5551(255, 40, 40, 1)); // #FF2828

    Profiler_DrawBarCpuKeepMax(0, rdp_duration, 216, &sRDPLastMax, &sRDPResetCtr);

    Profiler_DrawReferenceBars();
}

// Draw the Profiler per frame.
/** Draws the profiler display. */
void Profiler_Draw(s32 profiler_mode) {
    s32 ulx;
    s32 uly;
    s32 ulx_off;
    s32 uly_off;

    gDPPipeSync(gDisplayListHead++);
    gDPSetCycleType(gDisplayListHead++, G_CYC_FILL);
    gDPSetRenderMode(gDisplayListHead++, G_RM_NOOP, G_RM_NOOP2);

    ulx = 30;
    uly = 211;
    ulx_off = 196;
    uly_off = 9;

    if (StageContext_IsHighResolution() != 0) {
        ulx <<= 1;
        uly <<= 1;
        ulx_off <<= 1;
        uly_off <<= 1;
    }

    gDPPipeSync(gDisplayListHead++);
    gDPSetFillColor(gDisplayListHead++, 0x00010001);
    gDPFillRectangle(gDisplayListHead++, ulx, uly, ulx + ulx_off, uly + uly_off);

    if (profiler_mode == 0) {
        Profiler_DrawMode0();
    } else {
        Profiler_DrawMode1();
    }
}

/*
 * Print the CPU and RCP metrics to the screen, using a scale to approximate it to a scale near 0.0-1.0.
 * Based on the 770296 value documented earlier (it is close to a 60 FPS approximation), it may have been
 * used to measure for undesired lag (values above 1.0) when printed to the screen.
 */
void Profiler_PrintMetrics(void) {
    struct ProfilerFrameData* profiler =
        &gProfiler.profiler_data[(gProfiler.frameIdx1 == 0) ? 2 : gProfiler.frameIdx1 - 1];
    struct ProfilerFrameData* profiler_2 =
        &gProfiler.profiler_data[(gProfiler.frameIdx2 == 0) ? 2 : gProfiler.frameIdx2 - 1];
    s32 pad[3]; // FAKE: stack padding; i dont understand. but ok.

    HAL_Printf(240, 210, "CPU:%5.3f",
               ((profiler->gameTimes[2] - profiler->gameTimes[0])) * (1 / (float)UNK_FPS_60_APPROX_VALUE));
    HAL_Printf(240, 220, "RCP:%5.3f",
               ((profiler_2->gfxTimes[2] - profiler_2->gfxTimes[0])) * (1 / (float)UNK_FPS_60_APPROX_VALUE));
}

// reset the profiler data to uninitialized 0s.
/** Clears the profiler data. */
void Profiler_ClearData(void) {
    bzero(&gProfiler.profiler_data[0], sizeof(struct ProfilerFrameData));
    gProfiler.frameIdx1 = 1;
    gProfiler.frameIdx2 = 1;
}

// unused. seems to be intended to set a static OSTime and then get the last difference (in usec)
// since the last set.
/** Starts or stops a timer and returns the elapsed time. */
u32 Profiler_SetGetTimeDiff(enum SetGetTimeDiff state) {
    u32 ret = 0;
    static OSTime sBackupTime = 0ULL;

    switch (state) {
        case SET_TIME:
            sBackupTime = osGetTime();
            ret = 0;
            break;
        case GET_TIME_DIFF:
            ret = OS_CYCLES_TO_USEC(osGetTime() - sBackupTime);
            break;
    }
    return ret;
}
