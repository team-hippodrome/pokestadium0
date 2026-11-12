/* Stadium Zero resident code. */
/* C ported from the Stadium 1 decomp: src/DDC0.c. */

#include <PR/os_internal_reg.h>
#include "global.h"
#include "dp_intro.h"
#include "profiler.h"
#include "audio_loop_point.h"
#include "scheduler.h"
#include "gb_tower_audio.h"
#include "audio_commands.h"
#include "audio_category_fade.h"
#include "audio_sound_state.h"
#include "audio_channel.h"
#include "audio_loop_point.h"
#include "m2c_macros.h"
#include "33FE0_types_2.h"
extern s32 D_800AAE30;
extern s32 D_800AAF3C;

void Audio_ResetCurrentMusic(void);
void Audio_PlayMusicIfChanged(s32 arg0);
void Audio_StopMusic(s32 arg0);
s32 Audio_WaitForIdle(s32 arg0);
void Audio_FadeOutForShutdown(void);
void Audio_Disable(void);
void Audio_Enable(void);

void Audio_ResetCurrentMusic(void) {
    D_800AAF3C = -1;
}

void Audio_PlayMusicIfChanged(s32 arg0) {
    if (arg0 != D_800AAF3C) {
        if (D_800AAF3C >= 0) {
            Audio_FadeOutAll(0);
        }
        Audio_StartMusicTrack(arg0);
        D_800AAF3C = arg0;
    }
}

void Audio_StopMusic(s32 arg0) {
    if (D_800AAF3C >= 0) {
        Audio_FadeOutAll(arg0);
        D_800AAF3C = -1;
    }
}

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

void Audio_FadeOutForShutdown(void) {
    Audio_FadeCategoriesAndStreamsWithDuration(0x10);
}

void Audio_Disable(void) {
    D_800AAE30 = 0;
    Audio_SetEnabled(0);
}

void Audio_Enable(void) {
    Audio_SetEnabled(1);
    D_800AAE30 = 1;
}

M2C_UNK func_80004920(M2C_UNK *);                   /* extern */
M2C_UNK func_80004EA8(M2C_UNK *);                   /* extern */
M2C_UNK func_80004F34(s8 *, M2C_UNK);             /* extern */
M2C_UNK func_800082D0();                            /* extern */
M2C_UNK func_8003B868(s8 *);                      /* extern */
M2C_UNK func_8003BC9C(M2C_UNK);                     /* extern */
M2C_UNK func_8003E1F8();                            /* extern */
M2C_UNK func_80046170(M2C_UNK, M2C_UNK);            /* extern */
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
void func_8000A92C(s32 arg0) {
    func_800567E0(&D_800AAE48, &D_800AAE38, 1);
    func_80004EA8(&D_800AAE38);
    D_800AAE30 = 1;
    D_800AAF3C = -1;
    D_800AAF38 = 0;
    func_800567E0(&D_800AAE6C, &D_800AAE68, 1);
    func_800567E0(&D_800AAED4, &D_800AAED0, 1);
    func_8004CFB0(&D_800AAE6C, 0x444F4E45, 0);
    func_8004CFB0(&D_800AAED4, 0x444F4E45, 0);
    func_8003E1F8();
    func_8003BC9C(1);
    func_80046170(3, 4);
loop_1:
    func_80004920(&D_800AAE38);
    func_800082D0();
    if ((D_800AAE30 != 0) && (D_800A9710.unk_A38 < 0x15)) {
        func_8003B868(&D_800AAE68 + (D_800AAF38 * 0x68) + 0x20);
        func_80004F34(&D_800AAE68 + (D_800AAF38 * 0x68), 0);
    }
    D_800AAF38 ^= 1;
    func_800082D0();
    goto loop_1;
}
