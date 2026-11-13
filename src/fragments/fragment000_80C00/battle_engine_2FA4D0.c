/* Stadium Zero fragment000_80C00. */
/* Audio driver, matching OoT src/audio/internal/thread.c in function order. The driver is
 * Nintendo's "Nas" library (original names Nas_*); this revision sits between SM64 Shindou and
 * OoT. See docs/annotation/audio-driver.md for the per-function mapping. */
/* C ported from the Stadium 1 decomp: src/audio_sound_state.c, src/fragments/battle_engine/battle_engine_2FA4D0.c, src/fragments/battle_engine/battle_engine_317E70.c. */

#include "fragments/battle_engine/battle_engine.h"
#include "graphics_textures.h"
#include "ui_graphics.h"
#include "status_icons.h"
#include "game_state.h"
#include "text_system.h"
#include "3D140.h"
#include "gfx_buffer.h"
#include "gfx_rect.h"
#include "matrix.h"
#include "controller.h"
#include "memmap.h"
#include "memory.h"

#include "audio_sound_state.h"
#include "libnumus/player.h"
#include "audio_stream.h"
#include "3D140.h"
#include "audio_commands.h"

#include "fragments/battle_engine/battle_engine.h"
#include "geo_render.h"
#include "model_renderer.h"
#include "matrix.h"
#include "fragments/particle_math/particle_math.h"
#include "memory.h"

#include "m2c_macros.h"

void func_8110FC30(void);
void func_8110FC38(void);
void func_8110FC40(void);
void func_8110FE90(void);
s32 AudioThread_GetFontsForSequence(s32 arg0);
void AudioThread_ResetExternalPool(void);
void func_81110164(void);
void AudioThread_InitMesgQueues(void);

void AudioThread_InitMesgQueuesImpl(void);

/**
 * Empty.
 * No OoT counterpart. Zero's audio thread file starts with three empty stubs; OoT's thread.c starts
 * with AudioThread_Update.
 */
void func_8110FC30(void) {
}

/**
 * Empty.
 * See func_8110FC30.
 */
void func_8110FC38(void) {
}

/**
 * Empty.
 * See func_8110FC30.
 */
void func_8110FC40(void) {
}

M2C_UNK func_800567E0(M2C_UNK *, M2C_UNK *, M2C_UNK); /* extern */
extern u8 D_811861DA;
extern u8 D_811861DB;
extern s8 D_811861DC;
extern M2C_UNK D_811861E0;
extern M2C_UNK D_811861E8;
extern M2C_UNK *D_81186200;
extern M2C_UNK D_81186208;
extern M2C_UNK D_81186218;
extern OSMesgQueue* D_81186230;
extern M2C_UNK D_81186234;
extern M2C_UNK D_81186238;
extern M2C_UNK *D_81186250;

/**
 * Corresponds to OoT AudioThread_InitMesgQueuesImpl (original name Nap_AudioPortInit). Same three
 * queues of 1, 4 and 1 messages. Stadium 1's name BattleAnim_DisableEffectSpawning did not fit.
 * Not reached in play (2026-11-13): did not run in a GB player session (boot, Continue, menus) or
 * in a tour of the menus and a COM battle.
 * @unverified Name was previously used only by callers of this address; the definition was still func_.
 */
void AudioThread_InitMesgQueuesImpl(void) {
    D_811861DA = 0;
    D_811861DB = 0;
    D_811861DC = 0;
    D_81186200 = &D_811861E8;
    D_81186230 = &D_81186218;
    D_81186250 = &D_81186238;
    func_800567E0(D_81186200, &D_811861E0, 1);
    func_800567E0(D_81186230, &D_81186208, 4);
    func_800567E0(D_81186250, &D_81186234, 1);
}

extern s32 D_811859D8[][2];

/**
 * Appends a command to the 256-entry audio command ring; drops it when the ring is full.
 * Corresponds to OoT AudioThread_QueueCmd (original name Nap_PortSet).
 * @unverified Name follows the counterpart; not checked in play.
 */
void AudioThread_QueueCmd(DisplayObject* arg0, s32* arg1) {
    s32* entry = D_811859D8[D_811861DA & 0xFF]; // FAKE: no-op mask on a u8

    entry[0] = (s32)arg0;
    entry[1] = *arg1;
    if (D_811861DB == ++D_811861DA) {
        D_811861DA--;
    }
}

/*
 * AudioThread_QueueCmdF32
 *
 * Calls AudioThread_QueueCmd(arg0, &value) where `value` is a local copy of the
 * second argument, so the callee receives it by pointer.  Siblings
 * AudioThread_QueueCmdS8 / AudioThread_QueueCmdU16 do the same after shifting an s8 / s16
 * left by 24 / 16 bits; this one passes the word through unchanged.
 *
 * arg0 is declared s32 because the one known caller of the twin function
 * AudioThread_QueueCmdS32 passes the constant 0xF9000000 there, so it is a plain
 * word and not necessarily an object pointer.  The cast below only
 * satisfies the DisplayObject* prototype of AudioThread_QueueCmd used by the
 * siblings and produces no code.
 *
 * AudioThread_QueueCmdS32 compiles to identical machine code (the original source
 * probably differed in a type that cannot be recovered from the assembly).
 */
void AudioThread_QueueCmd(DisplayObject* arg0, s32* arg1);
/**
 * Queues a command with an f32 argument.
 * Corresponds to OoT AudioThread_QueueCmdF32 (original name Nap_SetF32).
 * @unverified Name follows the counterpart; not checked in play.
 */
void AudioThread_QueueCmdF32(s32 arg0, s32 arg1) {
    AudioThread_QueueCmd((DisplayObject*)arg0, &arg1);
}

/*
 * AudioThread_QueueCmdS32
 *
 * Passes arg0 and the address of a stack copy of arg1 on to AudioThread_QueueCmd.
 * This is the function the project's symbol list also knows as
 * AudioThread_QueueCmdS32(s32 cmd, s32 arg1); callers pass a 32-bit command word
 * such as 0xF9000000 or 0xF1000000 as the first argument, which is why arg0
 * is an s32 here.  The cast only satisfies the DisplayObject* prototype of
 * AudioThread_QueueCmd used by the sibling functions and produces no code.
 *
 * It is a machine-code twin of AudioThread_QueueCmdF32; the two cannot be told apart
 * from the assembly.  The address-style name is kept because the other C
 * functions in this file (e.g. AudioThread_QueueCmdS8) also use address names.
 */
void AudioThread_QueueCmd(DisplayObject* arg0, s32* arg1);
/**
 * Queues a command with an s32 argument.
 * Corresponds to OoT AudioThread_QueueCmdS32 (original name Nap_SetS32).
 * @unverified Name follows the counterpart; not checked in play.
 */
void AudioThread_QueueCmdS32(s32 arg0, s32 arg1) {
    AudioThread_QueueCmd((DisplayObject*)arg0, &arg1);
}

void AudioThread_QueueCmd(DisplayObject* arg0, s32* arg1);
/**
 * Queues a command with an s8 argument in the top byte.
 * Corresponds to OoT AudioThread_QueueCmdS8 (original name Nap_SetS8).
 * @unverified Name follows the counterpart; not checked in play.
 */
void AudioThread_QueueCmdS8(DisplayObject* arg0, s8 arg1) {
    s32 sp1C = arg1 << 24;

    AudioThread_QueueCmd(arg0, &sp1C);
}

/**
 * Queues a command with a u16 argument in the top half.
 * Corresponds to OoT AudioThread_QueueCmdU16 (original name Nap_SetU16).
 * @unverified Name follows the counterpart; not checked in play.
 */
void AudioThread_QueueCmdU16(DisplayObject* arg0, s16 arg1) {
    s32 sp1C = arg1 << 16;

    AudioThread_QueueCmd(arg0, &sp1C);
}

extern s32 D_811381D8;
s32 func_8004CFB0(OSMesgQueue*, s32, s32);

/**
 * Sends the queued command range to the audio thread and tracks the largest batch seen.
 * Corresponds to OoT AudioThread_ScheduleProcessCmds (original name Nap_SendStart).
 * @unverified Name follows the counterpart; not checked in play.
 */
// No return statement: retail leaves the send result in v0 and AudioThread_ResetAudioHeap returns it.
s32 AudioThread_ScheduleProcessCmds(void) {
    s32 head;
    s32 tail;
    s32 count = ((head = D_811861DA) - (tail = D_811861DB) + 0x100) & 0xFF;

    if (D_811381D8 < count) {
        D_811381D8 = count;
    }
    head = ((u8)tail << 8) | (u8)head; // FAKE: reuses head for the message
    if (func_8004CFB0(D_81186230, head, 0) != -1) {
        D_811861DB = D_811861DA;
    }
}

/**
 * Drops the commands queued since the last send.
 * Corresponds to OoT AudioThread_ResetCmdQueue (original name Nap_FlushPort).
 * @unverified Name follows the counterpart; not checked in play.
 */
void AudioThread_ResetCmdQueue(void) {
    (*(u8 *)&D_811861DB) = (*(u8 *)&D_811861DA);
    (*(s8 *)&D_811861DC) = 0;
}

/**
 * Empty.
 * No OoT counterpart. It sits where OoT has AudioThread_ProcessCmd (Nap_Process1Command) and
 * AudioThread_ProcessCmds (Nap_AudioPortProcess).
 */
void func_8110FE90(void) {
}

s32 func_8004D1C0(M2C_UNK *, u32 *, M2C_UNK);       /* extern */
extern M2C_UNK D_811855D8;

/**
 * Polls the external load queue: returns the message's top byte and stores its low 24 bits in
 * `arg0`, or returns 0.
 * Corresponds to OoT func_800E5E20. OoT leaves it unnamed; the name is MM's.
 * @unverified Name follows the counterpart; not checked in play.
 */
u32 AudioThread_GetExternalLoadQueueMsg(s32 *arg0) {
    u32 sp1C;

    if (func_8004D1C0(&D_811855D8, &sp1C, 0) == -1) {
        *arg0 = 0;
        return 0U;
    }
    *arg0 = sp1C & 0xFFFFFF;
    return sp1C >> 0x18;
}

/**
 * Returns the number of sounds active in an audio category.
 * Corresponds to OoT AudioThread_GetFontsForSequence. Stadium 1's name Audio_CountCategorySounds
 * did not fit.
 */
s32 AudioThread_GetFontsForSequence(s32 arg0) {
    return AudioLoad_GetFontsForSequence(arg0);
}

extern u8 D_81184658;

/*
 * AudioThread_CheckSpecChange
 *
 * Calls func_8004D1C0 once with the queue pointer in D_81186250, the address
 * of a local word and a third argument of 0 (see AudioThread_ClearSpecChangeQueue). Returns 0 if
 * that call returns -1; otherwise returns 1 when the word it stored equals
 * D_81184658 and 0 when it does not. The caller-visible meaning of the
 * comparison is not established here.
 * Matching note: the unused leading `pad` local moves `sp18` to the ROM's
 * stack offset (sp+0x18); the two returns are written as separate
 * `return 0` / `return 1` paths because that is the form that compiles to the
 * ROM's branch layout.
 * Corresponds to OoT func_800E5EDC (original name Nap_CheckSpecChange). OoT leaves it unnamed; the
 * name follows the original.
 */
s32 AudioThread_CheckSpecChange(void) {
    UNUSED s32 pad; // FAKE: stack padding
    u32 sp18;

    if (func_8004D1C0(D_81186250, &sp18, 0) == -1) {
        return 0;
    }
    if (sp18 != D_81184658) {
        return 0;
    }
    return 1;
}

/*
 * AudioThread_ClearSpecChangeQueue
 *
 * Calls func_8004D1C0 with the queue pointer in D_81186250, the address of a
 * local word and a third argument of 0, repeatedly until it returns -1. The
 * received word is never read, so the loop only discards what the call hands
 * back. (dp_intro.c declares func_8004D1C0 as taking an OSMesgQueue*, and the
 * other callers pass 1 as the third argument; what 0 and -1 mean to the
 * callee is not established here.)
 * Matching note: the -1 is kept in a local assigned inside the loop body.
 * With a literal -1 in the condition the compiler hands out the saved
 * registers in a different order. Declaring `neg` before `sp28` puts `sp28`
 * at the ROM's stack offset (sp+0x28).
 * Corresponds to OoT func_800E5F34 (original name __ClearSpecChangeQ). OoT leaves it unnamed; the
 * name follows the original (MM: AudioThread_WaitForAudioResetQueueP).
 */
void AudioThread_ClearSpecChangeQueue(void) {
    s32 neg;
    u32 sp28;

    do {
        neg = -1;
    } while (func_8004D1C0(D_81186250, &sp28, 0) != neg);
}

extern u8* D_86B0E5E8;
extern GraphNode* D_86B0E5D0;
void AudioThread_ClearSpecChangeQueue(void);
void AudioThread_QueueCmdS32(s32, s32);
s32 AudioThread_ScheduleProcessCmds(void);
extern volatile u8 D_81184657;
extern u8 D_81184658;
/**
 * Queues an audio heap reset to spec `arg0` (command 0xF9) and sends it.
 * Corresponds to OoT AudioThread_ResetAudioHeap (original name Nap_StartSpecChange).
 * @unverified Name follows the counterpart; not checked in play.
 */
s32 AudioThread_ResetAudioHeap(s32 arg0) {
    s32 v;
    u32 sp18;

    AudioThread_ClearSpecChangeQueue();
    v = D_81184657;
    if (v != 0) {
        AudioThread_ResetCmdQueue();
        if (arg0 == D_81184658) {
            return 0;
        }
        if (v >= 3) {
            return 0;
        }
        func_8004D1C0(D_81186250, &sp18, 1);
    }
    AudioThread_ClearSpecChangeQueue();
    AudioThread_QueueCmdS32(0xF9000000, arg0);
    return AudioThread_ScheduleProcessCmds();
}

extern volatile s32 D_811859D4;

/**
 * Sets the volatile flag D_811859D4 to 1, calls AudioThread_ResetAudioHeap(0), then
 * clears the volatile byte D_81184657.
 * Corresponds to OoT AudioThread_PreNMIInternal (original name Nap_StartReset).
 */
void AudioThread_PreNMIInternal(void) {
    D_811859D4 = 1;
    AudioThread_ResetAudioHeap(0);
    D_81184657 = 0;
}

typedef struct unk_D_81184668 {
    /* 0x000 */ u32 unk_000_31 : 1;
    /* 0x000 */ u32 unk_000_0 : 31;
    /* 0x004 */ char unk004[0x30];
    /* 0x034 */ s8* unk_034[(0x15C - 0x34) / 4];
} unk_D_81184668; // size = 0x15C

extern unk_D_81184668 D_81184668[];

/**
 * Returns IO port `arg2` of channel `arg1` of sequence player `arg0`, or -1 when the player is off.
 * Corresponds to OoT AudioThread_GetChannelIO (original name Nap_ReadSubPort).
 * @unverified Name follows the counterpart; not checked in play.
 */
s8 AudioThread_GetChannelIO(s32 arg0, s32 arg1, s32 arg2) {
    unk_D_81184668* ch = &D_81184668[arg0];
    s8* p;

    if (ch->unk_000_31) {
        p = ch->unk_034[arg1];
        return (p + arg2)[0xC4];
    }
    return -1;
}

extern s8 D_811847BC;
/**
 * Returns IO port `arg1` of sequence player `arg0`.
 * Corresponds to OoT AudioThread_GetSeqPlayerIO (original name Nap_ReadGrpPort).
 * @unverified Name follows the counterpart; not checked in play.
 */
s8 AudioThread_GetSeqPlayerIO(s32 arg0, s32 arg1) {
    return *(&D_811847BC + ((arg0 * 0x15C) + arg1));
}

M2C_UNK func_811098C0(M2C_UNK *, s32, M2C_UNK);     /* extern */
extern M2C_UNK D_811842A0;

/**
 * Sets up the external allocation pool.
 * Corresponds to OoT AudioThread_InitExternalPool.
 * @unverified Name follows the counterpart; not checked in play.
 */
void AudioThread_InitExternalPool(s32 arg0, M2C_UNK arg1) {
    func_811098C0(&D_811842A0, arg0, arg1);
}

/**
 * Clears the battle effect state flag.
 * Corresponds to OoT AudioThread_ResetExternalPool. Stadium 1's name
 * BattleAnim_ClearEffectStateFlag did not fit.
 */
void AudioThread_ResetExternalPool(void) {
    D_811842A0 = 0;
}

/**
 * Empty.
 * No OoT counterpart; OoT's no-op command handlers are elsewhere in thread.c.
 */
void func_81110164(void) {
}

/**
 * Sets up the audio thread message queues.
 * Corresponds to OoT AudioThread_InitMesgQueues (original name Nas_InitGAudio). Stadium 1's name
 * BattleAnim_DisableEffectSpawningAlias did not fit.
 */
void AudioThread_InitMesgQueues(void) {
    AudioThread_InitMesgQueuesImpl();
}
