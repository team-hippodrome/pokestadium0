/* Stadium Zero resident code. */
/* C ported from the Stadium 1 decomp: src/DDC0.c. */

#include <PR/os_internal_reg.h>
#include "global.h"
#include "audio_music.h"
#include "audio_sound_state.h"
#include "fragments/battle/battle.h"
#include "rom_device.h"
#include "m2c_macros.h"

// Declared here instead of in a header: the callers of these disagree on their types.
s32 Audio_StartMusicTrack(s32 track_id);
void Audio_FadeOutAll(s32);
extern s32 D_800AAE30;
extern s32 D_800AAF3C;

void Audio_ResetCurrentMusic(void);
void Audio_PlayMusicIfChanged(s32 arg0);
void Audio_StopMusic(s32 arg0);
s32 Audio_WaitForIdle(s32 arg0);
void Audio_FadeOutForShutdown(void);
void Audio_Disable(void);
void Audio_Enable(void);

/** Marks that no music is current. */
void Audio_ResetCurrentMusic(void) {
    D_800AAF3C = -1;
}

/** Starts a music track unless it is already the current one. */
void Audio_PlayMusicIfChanged(s32 arg0) {
    if (arg0 != D_800AAF3C) {
        if (D_800AAF3C >= 0) {
            Audio_FadeOutAll(0);
        }
        Audio_StartMusicTrack(arg0);
        D_800AAF3C = arg0;
    }
}

/** Fades out the current music over the given time. */
void Audio_StopMusic(s32 arg0) {
    if (D_800AAF3C >= 0) {
        Audio_FadeOutAll(arg0);
        D_800AAF3C = -1;
    }
}

/** Waits for the audio system to become idle, returning nonzero on timeout. */
s32 Audio_WaitForIdle(s32 arg0) {
    s32 retvar = 0;

    if (arg0 != 0) {
        Audio_FadeCategoriesAndStreams(2);
    }
    while (Audio_GetActivityScore() != 0) {
        if (retvar < 1000000) {
            retvar++;
        } else if (retvar == 1000000) {
            Audio_FadeCategoriesAndStreamsDefault();
            retvar++;
        }
    }
    return retvar;
}

/** Fades out all audio categories ahead of a shutdown. */
void Audio_FadeOutForShutdown(void) {
    Audio_FadeCategoriesAndStreamsWithDuration(0x10);
}

/** Disables audio output. */
void Audio_Disable(void) {
    D_800AAE30 = 0;
    Audio_SetEnabled(0);
}

/** Enables audio output. */
void Audio_Enable(void) {
    Audio_SetEnabled(1);
    D_800AAE30 = 1;
}

M2C_UNK SchedClient_WaitMessage(M2C_UNK *);                   /* extern */
M2C_UNK Sched_AddClient(M2C_UNK *);                   /* extern */
M2C_UNK func_80004F34(s8 *, M2C_UNK);             /* extern */
M2C_UNK func_800082D0();                            /* extern */
M2C_UNK __amHandleFrame(s8 *);                      /* extern */
M2C_UNK Audio_SetOutputMode(M2C_UNK);                     /* extern */
M2C_UNK Audio_LoadSoundData();                            /* extern */
void Audio_SetChannelVolume(s32 arg0, u32 arg1);            /* extern */
M2C_UNK func_8004CFB0(M2C_UNK *, M2C_UNK, M2C_UNK); /* extern */
M2C_UNK func_800567E0(M2C_UNK *, M2C_UNK *, M2C_UNK); /* extern */
extern s32 D_800AAE30;
extern s8 D_800AAE38;
extern s8 D_800AAE48;
extern s8 D_800AAE68;
extern s8 D_800AAE6C;
extern s8 D_800AAED0;
extern s8 D_800AAED4;
extern s32 D_800AAF38;
extern s32 D_800AAF3C;
/**
 * Audio thread (id 4, started by Idle_ThreadEntry): sets up its queues, registers as a scheduler client,
 * loads the sound data, then each retrace builds and sends an audio frame task (__amHandleFrame) while
 * the console is not about to reset.
 */
void Audio_ThreadEntry(s32 arg0) {
    func_800567E0(&D_800AAE48, &D_800AAE38, 1);
    Sched_AddClient(&D_800AAE38);
    D_800AAE30 = 1;
    D_800AAF3C = -1;
    D_800AAF38 = 0;
    func_800567E0(&D_800AAE6C, &D_800AAE68, 1);
    func_800567E0(&D_800AAED4, &D_800AAED0, 1);
    func_8004CFB0(&D_800AAE6C, 0x444F4E45, 0);
    func_8004CFB0(&D_800AAED4, 0x444F4E45, 0);
    Audio_LoadSoundData();
    Audio_SetOutputMode(1);
    Audio_SetChannelVolume(3, 4);
loop_1:
    SchedClient_WaitMessage(&D_800AAE38);
    func_800082D0();
    if ((D_800AAE30 != 0) && (D_800A9710.preNmiFrames < 0x15)) {
        __amHandleFrame(&D_800AAE68 + (D_800AAF38 * 0x68) + 0x20);
        func_80004F34(&D_800AAE68 + (D_800AAF38 * 0x68), 0);
    }
    D_800AAF38 ^= 1;
    func_800082D0();
    goto loop_1;
}
