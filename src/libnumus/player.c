/* Stadium Zero resident code. */
/* C ported from the Stadium 1 decomp: src/libnumus/player.c. */

#include "libnumus/player.h"
#include "3D140.h"
#include "libnaudio/n_synsetpriority.h"
typedef u8* (*command_func_t)(channel_t*, u8*);
typedef u8* (*api_func_t)(u8*);
extern s32 mus_song_stop_countdown;
extern u8 mus_voice_start_immediate_mode;
extern command_func_t command_func_jumptable[];
extern api_func_t api_func_jumptable[];
extern ALPlayer plr_player;
extern ALHeap heap;
extern s32 pad_D_800FC7C8;
extern u32 max_channels;
extern channel_t* mus_channels;
extern u32 mus_vsyncs_per_second;
extern u32 mus_next_frame_time;
extern u16 mus_master_volume_effects;
extern u16 mus_master_volume_songs;
extern u32 mus_current_handle;
extern s32 mus_random_seed;
extern u8* mus_command_queue;
extern s32 mus_command_queue_size;
extern u32 mus_command_queue_max_size;
extern u8 mus_use_fixed_pan_mode;
extern u32 mus_current_frame_counter;
extern audio_voice_t* mus_voices;
extern audio_voice_t* mus_free_voice_1;
extern audio_voice_t* mus_free_voice_2;
extern audio_voice_t* mus_releasing_voice_3;
extern audio_voice_t* mus_releasing_voice_4;
extern ALHeap* audio_heap;
extern u32 mus_num_vvoices;
extern s32 mus_free_voices_count;
extern s32 mus_releasing_voices_count;

#include "m2c_macros.h"

u8* Audio_EnableVoiceVelocityFromStream(channel_t* cp, u8* ptr);
u8* Audio_DisableVoiceVelocityFromStream(channel_t* cp, u8* ptr);
u8* Audio_DisableVoicePeriodicPitchModulation(channel_t* cp, u8* ptr);
u8* Audio_SkipVoiceCommandWord(UNUSED channel_t* cp, u8* ptr);
u8* Audio_SkipVoiceCommandByte(UNUSED channel_t* cp, u8* ptr);
void Audio_RelocateSoundBankWrapper(s32 arg0, s32 arg1);
f32 Audio_ExpApproximation(f32 arg0);
void Audio_RelocateSoundBank(u8* arg0, s32 arg1);
s32 Audio_RandomScale(s32 arg0);
void Audio_FillBytes(u8* arg0, u8 arg1, u32 arg2);
void Audio_RelocatePointerArray(u8* arg0, u32 arg1, u32 arg2);

s32 func_80036640(s8 *arg0, M2C_UNK arg1) {
    M2C_FIELD(arg0, s32 *, 0x58) = 0;
    M2C_FIELD(arg0, s32 *, 0x54) = 0;
    M2C_FIELD(arg0, s32 *, 0x84) = 0;
    M2C_FIELD(arg0, s16 *, 0xB2) = 0;
    M2C_FIELD(arg0, s32 *, 0x5C) = 0;
    return 0;
}

u8* Audio_SetVoiceSampleIndex(channel_t* cp, u8* ptr) {
    u16 wave = *ptr++;

    if (wave & 0x80) {
        wave = (wave & 0x7F) << 8;
        wave |= *ptr++;
    }

    cp->wave = wave;
    return ptr;
}

u8* Audio_EnableVoicePitchSlide(channel_t* cp, u8* ptr) {
    cp->port = *ptr++;
    if (cp->port) {
        cp->port_base = cp->base_note;
    }
    return ptr;
}

s32 func_800366BC(s8 *arg0, s32 arg1) {
    M2C_FIELD(arg0, s8 *, 0xC6) = 0;
    return arg1;
}

u8* func_800366C8(channel_t* cp, u8* ptr) {
    u8 value;

    value = *ptr++;
    if (value == 0) {
        value = 1;
    }
    cp->env_speed = value;
    cp->env_speed_calc = 0x400 / value;
    cp->env_init_vol = 0;

    ptr++;

    value = *ptr++;
    if (value == 0) {
        value = 1;
    }
    cp->env_attack_speed = value;
    cp->env_max_vol = *ptr++;
    cp->env_attack_calc = (1.0 / (f32)value) * (f32)(cp->env_max_vol - cp->env_init_vol);

    value = *ptr++;
    if (value == 0) {
        value = 1;
    }
    cp->env_decay_speed = value;
    cp->env_sustain_vol = *ptr++;
    cp->env_decay_calc = (1.0 / (f32)value) * (f32)(cp->env_sustain_vol - cp->env_max_vol);

    value = *ptr++;
    if (value == 0) {
        value = 1;
    }
    cp->env_release_speed = value;

    return ptr;
}

extern u32 D_800B364C;
u8* Audio_SetVoiceSequenceTempo(channel_t* cp, u8* ptr) {
    s32 i;
    s32 temp_lo;
    s32 temp2;
    channel_t* sp;

    temp_lo = ((*ptr++ * 0x6000) / 120) / (s32)D_800B364C;
    temp2 = (cp->temscale * temp_lo) >> 7;

    if (cp->IsFX != 0) {
        cp->channel_tempo = temp_lo;
    } else {
        for (i = 0, sp = mus_channels; i < (s32)max_channels; i++, sp++) {
            if (sp->song_addr == cp->song_addr) {
                sp->channel_tempo_save = temp_lo;
                sp->channel_tempo = temp2;
            }
        }
    }

    return ptr;
}

u8* Audio_SetVoiceReleaseDuration(channel_t* cp, u8* ptr) {
    cp->endit = *ptr++;
    cp->cutoff = 0;
    return ptr;
}

u8* Audio_SetVoiceFixedDuration(channel_t* cp, u8* ptr) {
    s16 tmp = *ptr++ << 8;

    tmp |= *ptr++;

    cp->cutoff = tmp;
    cp->endit = 0;

    return ptr;
}

u8* Audio_EnableVoiceVibrato(channel_t* cp, u8* ptr) {
    cp->vib_delay = *ptr++;
    cp->vib_speed = *ptr++;
    cp->vib_amount = (f32)*ptr++ / 50.0;
    return ptr;
}

u8* Audio_EnableVoiceVibratoDown(channel_t* cp, u8* ptr) {
    cp->vib_delay = *ptr++;
    cp->vib_speed = *ptr++;
    cp->vib_amount = -(f32)*ptr++ / 50.0;

    return ptr;
}

s32 func_800369DC(s8 *arg0, s32 arg1) {
    M2C_FIELD(arg0, s8 *, 0xE8) = 0;
    M2C_FIELD(arg0, f32 *, 0x78) = 0.0f;
    return arg1;
}

u8* Audio_SetVoiceDurationOverride(channel_t* cp, u8* ptr) {
    u8 value = *ptr++;

    if (value < 0x80) {
        cp->fixed_length = value;
    } else {
        cp->fixed_length = (value & 0x7F) << 8;
        cp->fixed_length += *ptr++;
    }
    return ptr;
}

s32 func_80036A34(s8 *arg0, s32 arg1) {
    M2C_FIELD(arg0, s8 *, 0xC5) = 1;
    return arg1;
}

s8 *func_80036A44(s8 *arg0, u8 *arg1) {
    M2C_FIELD(arg0, u8 *, 0xC7) = (u8) *arg1;
    return arg1 + 1;
}

s32 func_80036A54(s8 *arg0, s32 arg1) {
    M2C_FIELD(arg0, s8 *, 0xC8) = 1;
    return arg1;
}

u8* Audio_SetVoiceFinePitch(channel_t* cp, u8* ptr) {
    s32 value = *ptr++;

    if (value & 0x80) {
        value |= ~0xFF;
    }
    cp->freqoffset -= cp->distort;
    cp->distort = (f32)value / 100.0;
    cp->freqoffset += cp->distort;
    return ptr;
}

u8* Audio_SetVoiceEnvelopeFromTable(channel_t* cp, u8* ptr) {
    s32 value = *ptr++;

    if (value & 0x80) {
        value = (value & 0x7F) << 8;
        value |= *ptr++;
    }

    Audio_SetVoiceVolumeEnvelope(cp, (u8*)&cp->song_addr->env_table[value]);
    return ptr;
}

u8* Audio_EnableVoiceVelocityFromStream(channel_t* cp, u8* ptr) {
    cp->velocity_on = 1;
    return ptr;
}

u8* Audio_DisableVoiceVelocityFromStream(channel_t* cp, u8* ptr) {
    cp->velocity_on = 0;
    return ptr;
}

s32 func_80036B44(s8 *arg0, s32 arg1) {
    M2C_FIELD(arg0, s8 *, 0xEA) = 1;
    return arg1;
}

s32 func_80036B54(s8 *arg0, s32 arg1) {
    M2C_FIELD(arg0, s8 *, 0xEA) = 0;
    return arg1;
}

// Zero's channel_t keeps its for/next stack four bytes lower than Stadium 1's.
typedef struct ChannelForStackZero {
    /* 0x000 */ char unk_000[0xEE];
    /* 0x0EE */ u8 for_stack_count;
    /* 0x0F0 */ u8* for_stack[FORNEXT_DEPTH];
    /* 0x100 */ u8* for_stackvol[FORNEXT_DEPTH];
    /* 0x110 */ u8* for_stackpb[FORNEXT_DEPTH];
    /* 0x120 */ u16 for_vol_count[FORNEXT_DEPTH];
    /* 0x128 */ u16 for_pb_count[FORNEXT_DEPTH];
    /* 0x130 */ u8 for_count[FORNEXT_DEPTH];
    /* 0x134 */ u8 for_volume[FORNEXT_DEPTH];
    /* 0x138 */ u8 for_pitchbend[FORNEXT_DEPTH];
} ChannelForStackZero;

u8* Audio_PushVoiceLoopState(channel_t* cp, u8* ptr) {
    u8 index = ((ChannelForStackZero*)cp)->for_stack_count;

    ((ChannelForStackZero*)cp)->for_count[index] = *ptr++;

    ((ChannelForStackZero*)cp)->for_stack[index] = ptr;
    ((ChannelForStackZero*)cp)->for_stackvol[index] = cp->pvolumebase;
    ((ChannelForStackZero*)cp)->for_stackpb[index] = cp->ppitchbendbase;

    ((ChannelForStackZero*)cp)->for_volume[index] = cp->volume;
    ((ChannelForStackZero*)cp)->for_pitchbend[index] = cp->pitchbend;

    ((ChannelForStackZero*)cp)->for_vol_count[index] = cp->cont_vol_repeat_count;
    ((ChannelForStackZero*)cp)->for_pb_count[index] = cp->cont_pb_repeat_count;

    ((ChannelForStackZero*)cp)->for_stack_count++;
    return ptr;
}

u8* Audio_PopVoiceLoopState(channel_t* cp, u8* ptr) {
    s32 index = M2C_FIELD(cp, u8*, 0xEE) - 1;

    if (((u8*)((u8*)cp + 0x130))[index] != 0xFF) {
        ((u8*)((u8*)cp + 0x130))[index]--;
        if (!((u8*)((u8*)cp + 0x130))[index]) {
            M2C_FIELD(cp, u8*, 0xEE) = index;
            index = -1;
        }
    }

    if (index >= 0) {
        ptr = ((u8**)((u8*)cp + 0xF0))[index];

        cp->pvolumebase = ((u8**)((u8*)cp + 0x100))[index];
        cp->ppitchbendbase = ((u8**)((u8*)cp + 0x110))[index];
        cp->volume = ((u8*)((u8*)cp + 0x134))[index];

        cp->pitchbend = ((u8*)((u8*)cp + 0x138))[index];
        cp->cont_vol_repeat_count = ((u16*)((u8*)cp + 0x120))[index];
        cp->cont_pb_repeat_count = ((u16*)((u8*)cp + 0x128))[index];
        cp->bendrange = 0.03125f;
        cp->pitchbend_calc = cp->pitchbend * cp->bendrange;
    }

    return ptr;
}

s8 *func_80036D04(s8 *arg0, s8 *arg1) {
    M2C_FIELD(arg0, u8 *, 0xEB) = (u8) M2C_FIELD(arg1, u8 *, 0);
    M2C_FIELD(arg0, u8 *, 0xE1) = (u8) M2C_FIELD(arg1, u8 *, 1);
    M2C_FIELD(arg0, u8 *, 0xE2) = (u8) M2C_FIELD(arg1, u8 *, 2);
    return arg1 + 3;
}

s32 func_80036D24(s8 *arg0, s32 arg1) {
    M2C_FIELD(arg0, s8 *, 0xE1) = 0;
    return arg1;
}

s32 func_80036D30(s8 *arg0, s32 arg1) {
    M2C_FIELD(arg0, s8 *, 0xE5) = 1;
    return arg1;
}

u8* Audio_DisableVoicePeriodicPitchModulation(channel_t* cp, u8* ptr) {
    cp->wobble_on_speed = 0;
    return ptr;
}

u8* Audio_SetVoiceDefaultVelocity(channel_t* cp, u8* ptr) {
    M2C_FIELD(cp, u8*, 0xE6) = *ptr++;
    M2C_FIELD(cp, u8*, 0xE5) = 0;
    return ptr;
}

s8 *func_80036D60(s8 *arg0, u8 *arg1) {
    M2C_FIELD(arg0, s8 *, 0xCB) = (s8) ((s32) *arg1 / 2);
    return arg1 + 1;
}

u8* Audio_SkipVoiceCommandWord(UNUSED channel_t* cp, u8* ptr) {
    ptr++;
    ptr++;
    return ptr;
}

u8* Audio_SetVoiceSubEnvelopePointer(channel_t* cp, u8* ptr) {
    u8* addr = (u8*)&cp->song_addr->num_channels + cp->song_addr->drum_table[*ptr++];

    cp->pdrums = addr;
    return ptr;
}

s32 func_80036DB4(s8 *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0x90) = 0;
    return arg1;
}

u8* Audio_SkipVoiceCommandByte(UNUSED channel_t* cp, u8* ptr) {
    #ifdef _AUDIODEBUG
        osSyncPrintf("PLAYER_COMMANDS.C: Audio_SkipVoiceCommandByte -  %d (channel frame=%d)\n", *ptr++,  cp->channel_frame);
        return ptr;
    #else
        ptr++;
        return ptr;
    #endif
}

u8* Audio_SetVoiceEnvelopePointers(channel_t* cp, u8* ptr) {
    s32 tmp0;
    s32 tmp2;

    tmp0 = *ptr++ << 8;
    tmp0 += *ptr++;

    tmp2 = *ptr++ << 8;
    tmp2 += *ptr++;

    cp->pvolumebase = &cp->pvolumebase_offset[tmp2];
    cp->cont_vol_repeat_count = 1;

    tmp2 = *ptr++ << 8;
    tmp2 += *ptr++;

    cp->ppitchbendbase = &cp->ppitchbendbase_offset[tmp2];
    cp->cont_pb_repeat_count = 1;

    return &cp->pbase[tmp0];
}

s8 *func_80036E30(s8 *arg0, u8 *arg1) {
    M2C_FIELD(arg0, u8 *, 0xDE) = (u8) *arg1;
    return arg1 + 1;
}

u8* Audio_SetRandomVoiceDetune(channel_t* cp, u8* ptr) {
    cp->transpose = Audio_RandomScale(*ptr++);
    cp->transpose += *ptr++;
    return ptr;
}

u8* Audio_SetRandomVoiceVolume(channel_t* cp, u8* ptr) {
    cp->volume = Audio_RandomScale(*ptr++);
    cp->volume += *ptr++;
    return ptr;
}

u8* func_80036EE0(channel_t* cp, u8* ptr) {
    M2C_FIELD(cp, u8*, 0xCB) = Audio_RandomScale(*ptr++);
    M2C_FIELD(cp, u8*, 0xCB) += *ptr++;
    return ptr;
}

s8 *func_80036F30(s8 *arg0, u8 *arg1) {
    M2C_FIELD(arg0, u8 *, 0xCA) = (u8) *arg1;
    return arg1 + 1;
}

M2C_UNK func_80037828(s32, s32, s32, s32, s32);
extern s32 D_800B3638;
extern s8* D_800B3640;
u8* func_80036F40(s8* cp, u8* ptr) {
    s32 id = *ptr++;
    s32 ret;
    s32 i;
    s8* p;

    if (id >= 0x80) {
        id = ((id & 0x7F) << 8) + *ptr++;
    }
    ret = func_80037828(id, M2C_FIELD(cp, u8*, 0xCA), M2C_FIELD(cp, s16*, 0xBC), 0, M2C_FIELD(cp, s32*, 0x60)++);
    M2C_FIELD(cp, s32*, 0x60)--;
    if (ret == 0) {
        return ptr;
    }
    p = D_800B3640;
    for (i = 0; i < D_800B3638; i++, p += 0x148) {
        if (ret == M2C_FIELD(p, s32*, 0x5C)) {
            M2C_FIELD(p, s32*, 0x5C) = M2C_FIELD(cp, s32*, 0x5C);
            M2C_FIELD(p, s32*, 0x88) = M2C_FIELD(cp, s32*, 0x88);
            M2C_FIELD(p, s16*, 0xAA) = M2C_FIELD(cp, s16*, 0xAA);
            M2C_FIELD(p, s32*, 0x38) = M2C_FIELD(cp, s32*, 0x38);
            M2C_FIELD(p, s32*, 0x3C) = M2C_FIELD(cp, s32*, 0x3C);
        }
    }
    return ptr;
}

u8* Audio_SetVoiceVolumeScale(channel_t* cp, u8* ptr) {
    cp->bendrange = (f32)*ptr++ * 0.015625;
    cp->pitchbend_calc = SQ(cp->pitchbend);
    return ptr;
}

u8* Audio_SetVoicePanModulation(channel_t* cp, u8* ptr) {
    M2C_FIELD(cp, u8*, 0xE7) = *ptr++;
    if (!M2C_FIELD(cp, u8*, 0xE7)) {
        M2C_FIELD(cp, u16*, 0xBC) = 0x80;
    }
    return ptr;
}

s32 func_8003821C(s32, s32, s32, s32, s32, s32, s32);

/**
 * Command handler (same shape as func_80036F40): reads a sound id from `ptr`, either one
 * byte, or, when that byte is >= 0x80, two bytes as ((first & 0x7F) << 8) + second. It
 * then starts that sound with func_8003821C, passing the channel's offsets 0x140 and
 * 0x13C, the id, the s16 at 0xAA, the s16 at 0xBC, 0 and the channel's offset-0x60 value
 * (`priority`), which is incremented across the call and decremented again afterwards.
 * If func_8003821C returns a non-zero handle, every channel whose offset-0x5C handle
 * equals it receives this channel's handle (0x5C), 0x88, 0xAA, 0x38 and 0x3C fields.
 * Returns the advanced command pointer. What the started object is is not established.
 */
u8* func_800370AC(s8* cp, u8* ptr) {
    u32 id = *ptr++;
    s32 ret;
    s32 i;
    s8* p;

    if (id >= 0x80) {
        id = ((id & 0x7F) << 8) + *ptr++;
    }
    ret = func_8003821C(M2C_FIELD(cp, s32*, 0x140), M2C_FIELD(cp, s32*, 0x13C), id, M2C_FIELD(cp, s16*, 0xAA), M2C_FIELD(cp, s16*, 0xBC), 0, M2C_FIELD(cp, s32*, 0x60)++);
    M2C_FIELD(cp, s32*, 0x60)--;
    if (ret == 0) {
        return ptr;
    }
    p = D_800B3640;
    for (i = 0; i < D_800B3638; i++, p += 0x148) {
        if (ret == M2C_FIELD(p, s32*, 0x5C)) {
            M2C_FIELD(p, s32*, 0x5C) = M2C_FIELD(cp, s32*, 0x5C);
            M2C_FIELD(p, s32*, 0x88) = M2C_FIELD(cp, s32*, 0x88);
            M2C_FIELD(p, s16*, 0xAA) = M2C_FIELD(cp, s16*, 0xAA);
            M2C_FIELD(p, s32*, 0x38) = M2C_FIELD(cp, s32*, 0x38);
            M2C_FIELD(p, s32*, 0x3C) = M2C_FIELD(cp, s32*, 0x3C);
        }
    }
    return ptr;
}

typedef struct PlayerChannelZero_1E {
    /* 0x00 */ char unk00[0x1E];
    /* 0x1E */ u8 unk_1E;
    /* 0x1F */ char unk1F[0x5];
} PlayerChannelZero_1E; // size = 0x24

/* Block passed as the first argument of func_8003B2E0 (synthesizer set-up).
 * Field meanings beyond what func_800371A4 writes are not established. */
typedef struct SynInitCfgZero {
    /* 0x00 */ s32 f00;
    /* 0x04 */ s32 f04;
    /* 0x08 */ s32 f08;
    /* 0x0C */ s32 f0C;
    /* 0x10 */ s32 f10;
    /* 0x14 */ s32 f14;
    /* 0x18 */ s32 f18;
    /* 0x1C */ s8 f1C;
} SynInitCfgZero;

/* Block passed as the second argument of func_8003B2E0; filled from the init
 * configuration at offsets 0x18, 0x20 and 0x1C. */
typedef struct SynInitRateZero {
    /* 0x00 */ s32 f00;
    /* 0x04 */ s32 f04;
    /* 0x08 */ s32 f08;
} SynInitRateZero;

extern s32* D_800B3648;
extern s8* D_800B3664;
extern s8* D_800B3668;
extern s32 D_800B365C;
extern s32 D_800B3CC8;
extern s32 D_800B3CCC;
extern s32 D_800B3CD0;
void func_800374E0(s32, s32);
void func_8003A2B8(s8*);
extern s32 D_80000300;
extern s32 D_80075C34;
extern s32 D_800B3644;
extern s32 D_800B3650;
extern s32 D_800B3660;
extern s32 D_800B3CC4;
extern PlayerChannelZero_1E D_800B3670[45];
extern ALPlayer D_800B3610;
extern ALHeap D_800B3628;
extern void* D_800B363C;
void func_8003A564(void*, s32, s32);
s32 func_8003B2E0(SynInitCfgZero*, SynInitRateZero*, s32, s32, s32);
void func_800468F0(ALPlayer*);
void* func_8005C0D0(s32, s32, void*, s32, s32);
void func_800388BC();

/**
 * Sound-player initialisation (the Stadium Zero counterpart of the retail libmus
 * initialiser). `arg0` is the caller's configuration block:
 *   0x00 channel count (D_800B3638)        0x04 ALHeap* used for all allocation
 *   0x08 pointer stored in D_800B3664 and D_800B3668
 *   0x0C -> D_800B3644, 0x10 -> D_800B3648 (the song table that func_80037828 indexes)
 *   0x14, 0x18, 0x1C, 0x20, 0x24, 0x28: values forwarded to func_8003B2E0.
 * Steps: set D_800B364C to 50 if the word at 0x80000300 is 0 (osTvType == PAL), else 60,
 * and D_800B3650 to 1000000 / D_800B364C; allocate and zero the 0x1C-byte-per-channel
 * table D_800B363C and the 0x148-byte-per-channel array D_800B3640; build the two
 * parameter blocks and call func_8003B2E0; call func_800374E0(7, 0x7FFF); reset the
 * handle counter D_800B365C to 1 and D_800B3660 to 0x12345678, and clear D_800B3CC4,
 * D_800B3CC8, D_800B3CCC, D_80075C34 and D_800B3CD0;
 * register the player at D_800B3610 (handler func_800388BC, clientData = itself) with
 * func_800468F0; clear offsets 0xDD and 0x30 and call func_8003A2B8 on every channel;
 * set the byte at offset 0x1E of all 45 entries of D_800B3670 to 5; finally copy the
 * ALHeap into D_800B3628 and return its used size (cur - base).
 * The `pad` local only reserves the stack slot the retail frame has there.
 * What the 0x1C-byte table and several configuration words are is not established.
 */
s32 func_800371A4(s8* arg0) {
    s32 i;
    s32 off;
    UNUSED s32* pad;
    SynInitCfgZero cfg;
    SynInitRateZero rate;

    D_800B3638 = M2C_FIELD(arg0, s32*, 0);
    D_800B3644 = M2C_FIELD(arg0, s32*, 0xC);
    D_800B3648 = M2C_FIELD(arg0, s32**, 0x10);
    if (D_80000300 == 0) {
        D_800B364C = 0x32;
    } else {
        D_800B364C = 0x3C;
    }
    D_800B3650 = 0xF4240 / (s32)D_800B364C;
    D_800B363C = func_8005C0D0(0, 0, M2C_FIELD(arg0, void**, 4), 1, D_800B3638 * 0x1C);
    D_800B3640 = func_8005C0D0(0, 0, M2C_FIELD(arg0, void**, 4), 1, D_800B3638 * 0x148);
    func_8003A564(D_800B363C, 0, D_800B3638 * 0x1C);
    func_8003A564(D_800B3640, 0, D_800B3638 * 0x148);
    D_800B3668 = D_800B3664 = M2C_FIELD(arg0, s8**, 8);
    cfg.f00 = 0x2D;
    cfg.f04 = D_800B3638;
    cfg.f08 = M2C_FIELD(arg0, s32*, 0x14);
    cfg.f10 = 0;
    cfg.f1C = 2;
    cfg.f18 = 0;
    cfg.f14 = M2C_FIELD(arg0, s32*, 4);
    rate.f00 = M2C_FIELD(arg0, s32*, 0x18);
    rate.f04 = M2C_FIELD(arg0, s32*, 0x20);
    rate.f08 = M2C_FIELD(arg0, s32*, 0x1C);
    func_8003B2E0(&cfg, &rate, M2C_FIELD(arg0, s32*, 0x24), M2C_FIELD(arg0, s32*, 0x28), D_800B364C);
    func_800374E0(7, 0x7FFF);
    D_800B365C = 1;
    D_800B3660 = 0x12345678;
    D_800B3CC4 = 0;
    D_800B3CC8 = 0;
    D_800B3CCC = 0;
    D_80075C34 = 0;
    D_800B3CD0 = 0;
    D_800B3610.next = NULL;
    D_800B3610.handler = func_800388BC;
    D_800B3610.clientData = &D_800B3610;
    func_800468F0(&D_800B3610);
    for (i = 0, off = 0; i < D_800B3638; i++, off += 0x148) {
        M2C_FIELD(D_800B3640 + off, s8*, 0xDD) = 0;
        M2C_FIELD(D_800B3640 + off, s32*, 0x30) = 0;
        func_8003A2B8(off + D_800B3640);
    }
    for (i = 0; i < 45; i++) {
        D_800B3670[i].unk_1E = 5;
    }
    D_800B3628 = *M2C_FIELD(arg0, ALHeap**, 4);
    return D_800B3628.cur - D_800B3628.base;
}

extern s16 D_800B3654;
extern s16 D_800B3656;
void func_800374E0(s32 arg0, s32 arg1) {
    if (arg0 & 1) {
        D_800B3654 = arg1;
    }
    if (arg0 & 2) {
        D_800B3656 = arg1;
    }
}

s32 func_8004D300(s32);
extern s32 D_800B3CC8;
extern s32 D_800B365C;
extern s32 D_800B366C;
void func_8003A598(void*, void*, s32);
void func_8003A2B8(s8*);
u32 func_8003A4A8();
s32 func_80037508(s32* song) {
    UNUSED s32 pad;
    s32 handle;
    s32 mask;
    s32 count;
    s32 i;
    s8* cp;
    s32 index;

    mask = func_8004D300(1);
    D_800B3CC8 = 1;
    func_8004D300(mask);
    count = song[0];
    if ((u32)song[1] < 0x400) {
        func_8003A598(&song[1], song, 5);
        func_8003A598(song[1], song, count);
        func_8003A598(song[2], song, count);
        func_8003A598(song[3], song, count);
    }
    mask = func_8004D300(1);
    handle = D_800B365C++;
    func_8004D300(mask);
    for (i = 0; i < count; i++) {
        if (((s32*)song[1])[i] == 0) {
            continue;
        }
        index = func_8003A4A8(song, i);
        if (index == -1) {
            continue;
        }
        cp = D_800B3640 + index * 0x148;
        func_8003A2B8(cp);
        mask = func_8004D300(1);
        M2C_FIELD(cp, s32*, 0x88) = D_800B366C;
        M2C_FIELD(cp, s32*, 0x84) = (s32)song;
        M2C_FIELD(cp, s32*, 0x58) = M2C_FIELD(cp, s32*, 0x98) = ((s32*)song[2])[i];
        M2C_FIELD(cp, s32*, 0x54) = M2C_FIELD(cp, s32*, 0x94) = ((s32*)song[3])[i];
        M2C_FIELD(cp, s32*, 0x30) = M2C_FIELD(cp, s32*, 0x8C) = ((s32*)song[1])[i];
        M2C_FIELD(cp, s32*, 0x5C) = handle;
        func_8004D300(mask);
    }
    mask = func_8004D300(1);
    D_800B3CC8 = 0;
    func_8004D300(mask);
    return handle;
}

extern s32 D_800B3CCC;
extern s32* D_800B3648;
s32 func_8003A638(channel_t*, s32, s32, s32, s32);

/**
 * Claims the first free channel and starts it. With the D_800B3CCC flag set to 1 (each
 * write made with interrupts masked via osSetIntMask(1)), it scans the channel array for
 * one whose `pdata` is NULL, marks it in use by storing -1 there, and calls
 * func_8003A638(channel, ...) on it, then clears the flag and returns that call's result.
 * Returns 0 (and clears the flag) if no channel is free.
 * Same as func_80037828 with arg1 = arg2 = 0x80 and the last argument always taken from
 * D_800B3648[song] (D_800B3648 is a pointer to a table of s32).
 */
s32 func_800376E8(s32 song) {
    channel_t* cp;
    s32 i;
    s32 found;
    s32 arg;
    u32 mask;
    s32 ret;

    found = 0;
    mask = osSetIntMask(1);
    D_800B3CCC = 1;
    osSetIntMask(mask);
    cp = mus_channels;
    i = 0;
    arg = D_800B3648[song];
    for (; i < (s32)max_channels; i++, cp++) {
        mask = osSetIntMask(1);
        if (cp->pdata == NULL) {
            cp->pdata = (u8*)-1;
            found = 1;
        }
        osSetIntMask(mask);
        if (found != 0) {
            ret = func_8003A638(cp, song, 0x80, 0x80, arg);
            mask = osSetIntMask(1);
            D_800B3CCC = 0;
            osSetIntMask(mask);
            return ret;
        }
    }
    mask = osSetIntMask(1);
    D_800B3CCC = 0;
    osSetIntMask(mask);
    return 0;
}

extern s32 D_800B3CCC;
extern s32* D_800B3648;
s32 func_8003A638(channel_t*, s32, s32, s32, s32);

/**
 * Claims the first free channel and starts it. With the D_800B3CCC flag set to 1 (each
 * write made with interrupts masked via osSetIntMask(1)), it scans the channel array for
 * one whose `pdata` is NULL, marks it in use by storing -1 there, and calls
 * func_8003A638(channel, ...) on it, then clears the flag and returns that call's result.
 * Returns 0 (and clears the flag) if no channel is free.
 * Arguments: song, arg1, arg2, arg3 (unused), arg4. The call is
 * func_8003A638(channel, song, arg1, arg2, arg4), where arg4 is first replaced by
 * D_800B3648[song] if song is not 0xFFFF and arg4 is -1. D_800B3648 is read as a
 * pointer to a table of s32 (the retail code loads it with lw).
 * What the table and the started object are is not established.
 */
s32 func_80037828(s32 song, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    channel_t* cp;
    s32 i;
    s32 found;
    u32 mask;
    s32 ret;

    found = 0;
    mask = osSetIntMask(1);
    D_800B3CCC = 1;
    osSetIntMask(mask);
    if ((song != 0xFFFF) && (arg4 == -1)) {
        arg4 = D_800B3648[song];
    }
    for (i = 0, cp = mus_channels; i < (s32)max_channels; i++, cp++) {
        mask = osSetIntMask(1);
        if (cp->pdata == NULL) {
            cp->pdata = (u8*)-1;
            found = 1;
        }
        osSetIntMask(mask);
        if (found != 0) {
            ret = func_8003A638(cp, song, arg1, arg2, arg4);
            mask = osSetIntMask(1);
            D_800B3CCC = 0;
            osSetIntMask(mask);
            return ret;
        }
    }
    mask = osSetIntMask(1);
    D_800B3CCC = 0;
    osSetIntMask(mask);
    return 0;
}

/**
 * For every channel whose type matches `flags` (MUSFLAG_EFFECTS selects channels whose
 * u16 at offset 0xB2 is nonzero, MUSFLAG_SONGS those where it is 0), sets `duration`
 * (offset 0x38) to arg1 and `duration_scale` (offset 0x3C) to arg1, or to 1 when arg1
 * is 0, with interrupts masked (osSetIntMask(1), then restored). Companion of
 * func_80037AC4, which does the same for one handle.
 */
void func_8003798C(s32 flags, s32 duration) {
    channel_t* cp;
    s32 scale;
    s32 i;
    u32 mask;

    scale = (duration != 0) ? duration : 1;
    mask = osSetIntMask(1);

    for (i = 0, cp = mus_channels; i < (s32)max_channels; i++, cp++) {
        if (((M2C_FIELD(cp, u16 *, 0xB2) != 0) && (flags & MUSFLAG_EFFECTS)) || ((M2C_FIELD(cp, u16 *, 0xB2) == 0) && (flags & MUSFLAG_SONGS))) {
            cp->duration = duration;
            cp->duration_scale = scale;
        }
    }

    osSetIntMask(mask);
}

/**
 * Counts the channels that are in use: `pdata` (offset 0x30) is neither NULL nor -1, and
 * the channel's type matches `flags` (MUSFLAG_EFFECTS selects channels whose u16 at
 * offset 0xB2 is nonzero, MUSFLAG_SONGS those where it is 0). Does not mask interrupts.
 * Written with the offset-0xB2 field read through M2C_FIELD: player.h places the
 * equivalent `IsFX` at 0xBA, which does not match this build's data.
 */
s32 func_80037A48(s32 flags) {
    channel_t* cp;
    s32 i;
    s32 count;

    for (i = 0, cp = mus_channels, count = 0; i < (s32)max_channels; i++, cp++) {
        if ((cp->pdata != NULL) && (cp->pdata != (u8*)-1)) {
            if (((M2C_FIELD(cp, u16 *, 0xB2) != 0) && (flags & MUSFLAG_EFFECTS)) || ((M2C_FIELD(cp, u16 *, 0xB2) == 0) && (flags & MUSFLAG_SONGS))) {
                count++;
            }
        }
    }

    return count;
}

/**
 * For every channel whose handle equals `handle`, sets `duration` (offset 0x38) to
 * arg1 and `duration_scale` (offset 0x3C) to arg1, or to 1 when arg1 is 0, with
 * interrupts masked (osSetIntMask(1), then restored). Returns the number of channels
 * changed; returns 0 without doing anything for handle 0. Same shape as func_80037D4C.
 * The declaration order of the locals is what produces the retail stack layout.
 */
s32 func_80037AC4(s32 handle, s32 duration) {
    channel_t* cp;
    s32 scale;
    s32 count;
    s32 i;
    u32 mask;

    if (handle == 0) {
        return 0;
    }

    scale = (duration != 0) ? duration : 1;
    mask = osSetIntMask(1);

    for (i = 0, count = 0, cp = mus_channels; i < (s32)max_channels; i++, cp++) {
        if (handle == cp->handle) {
            cp->duration = duration;
            cp->duration_scale = scale;
            count++;
        }
    }

    osSetIntMask(mask);

    return count;
}

s32 func_80037B7C(s32 handle) {
    channel_t* cp;
    s32 i;
    s32 count;
    u32 mask;

    if (handle == 0) {
        return 0;
    }

    mask = osSetIntMask(1);

    for (i = 0, count = 0, cp = mus_channels; i < (s32)max_channels; i++, cp++) {
        if (handle == cp->handle) {
            count++;
        }
    }

    osSetIntMask(mask);

    return count;
}

/**
 * Sets the field at channel offset 0xAA (`volume_scale` in player.h) to arg1 on every
 * channel whose handle equals `handle`, with interrupts masked (osSetIntMask(1), then
 * restored). Returns the number of channels changed; returns 0 without doing anything
 * for handle 0. Same shape as func_80037D4C.
 */
s32 func_80037C04(s32 handle, s32 arg1) {
    channel_t* cp;
    s32 i;
    s32 count;
    u32 mask;

    if (handle == 0) {
        return 0;
    }

    mask = osSetIntMask(1);

    for (i = 0, count = 0, cp = mus_channels; i < (s32)max_channels; i++, cp++) {
        if (handle == cp->handle) {
            cp->volume_scale = arg1;
            count++;
        }
    }

    osSetIntMask(mask);

    return count;
}

/**
 * For every channel whose handle equals `handle`, stores arg1 at channel offset 0xBC
 * (`sweep_amount` / `channel_tempo_save` in player.h) and sets the byte at 0xCC
 * (`pan_current`) to 0xFF, with interrupts masked (osSetIntMask(1), then restored).
 * Returns the number of channels changed; returns 0 without doing anything for handle 0.
 * Same shape as func_80037D4C.
 */
s32 func_80037CA4(s32 handle, s32 arg1) {
    channel_t* cp;
    s32 i;
    s32 count;
    u32 mask;

    if (handle == 0) {
        return 0;
    }

    mask = osSetIntMask(1);

    for (i = 0, count = 0, cp = mus_channels; i < (s32)max_channels; i++, cp++) {
        if (handle == cp->handle) {
            cp->sweep_amount = arg1;
            cp->pan_current = 0xFF;
            count++;
        }
    }

    osSetIntMask(mask);

    return count;
}

s32 func_80037D4C(s32 handle, f32 offset) {
    channel_t* cp;
    s32 i;
    s32 count;
    u32 mask;

    if (handle == 0) {
        return 0;
    }

    mask = osSetIntMask(1);

    for (i = 0, count = 0, cp = mus_channels; i < (s32)max_channels; i++, cp++) {
        if (handle == cp->handle) {
            count++;
            cp->freqoffset = cp->distort + offset;
        }
    }

    osSetIntMask(mask);

    return count;
}

/**
 * Sets the tempo scale for every channel whose handle equals `handle`. The tempo is
 * clamped to 1..0x100 (values <= 0 become 1, values above 0x100 become 0x100). For each
 * matching channel it stores the clamped value in `temscale` (offset 0xA4) and sets
 * `channel_tempo` (offset 0xA8) to (u16 at offset 0xB4 * tempo) >> 7. Returns the
 * number of channels changed; returns 0 for handle 0. Unlike its neighbours it does
 * not mask interrupts. The field at 0xB4 is unnamed in player.h.
 */
s32 func_80037DF4(s32 handle, s32 tempo) {
    channel_t* cp;
    s32 i;
    s32 count;

    if (handle == 0) {
        return 0;
    }

    if (tempo <= 0) {
        tempo = 1;
    } else if (tempo > 0x100) {
        tempo = 0x100;
    }

    for (i = 0, cp = mus_channels, count = 0; i < (s32)max_channels; i++, cp++) {
        if (handle == cp->handle) {
            cp->temscale = tempo;
            count++;
            cp->channel_tempo = (M2C_FIELD(cp, u16 *, 0xB4) * tempo) >> 7;
        }
    }

    return count;
}

/**
 * Clamps `value` to 0..0x7F, then for every channel whose handle equals `handle` stores
 * it in `reverb_intensity` (offset 0xDF) and sets `reverb_mix` (offset 0xE0) to 0xFF,
 * with interrupts masked (osSetIntMask(1), then restored). Returns the number of
 * channels changed; returns 0 without doing anything for handle 0.
 */
s32 func_80037E84(s32 handle, s32 value) {
    channel_t* cp;
    s32 i;
    s32 count;
    u32 mask;

    if (handle == 0) {
        return 0;
    }

    if (value < 0) {
        value = 0;
    } else if (value > 0x7F) {
        value = 0x7F;
    }

    mask = osSetIntMask(1);

    for (i = 0, count = 0, cp = mus_channels; i < (s32)max_channels; i++, cp++) {
        if (handle == cp->handle) {
            cp->reverb_intensity = value;
            cp->reverb_mix = 0xFF;
            count++;
        }
    }

    osSetIntMask(mask);

    return count;
}

void Audio_RelocateSoundBankWrapper(s32 arg0, s32 arg1) {
    Audio_RelocateSoundBank(arg0, arg1);
}

/**
 * With interrupts masked (func_8004D300 is libultra's osSetIntMask), records
 * arg0 in D_800B366C if it is non-NULL and bit 0 of its word at offset 0x10 is
 * set, restores the interrupt mask, then calls func_80037508(arg1).
 */
void func_80037F68(void* arg0, s32* arg1) {
    s32 prevMask;

    prevMask = func_8004D300(1);
    if ((arg0 != NULL) && (M2C_FIELD(arg0, s32*, 0x10) & 1)) {
        D_800B366C = (s32)arg0;
    }
    func_8004D300(prevMask);
    func_80037508(arg1);
}

M2C_UNK func_800376E8(M2C_UNK);                     /* extern */
extern s8 *D_800B3664;
extern s8 *D_800B3668;

void func_80037FCC(s8 *arg0, M2C_UNK arg1) {
    if ((arg0 != NULL) && (M2C_FIELD(arg0, s32 *, 0x10) & 1)) {
        D_800B3664 = arg0;
    }
    func_800376E8(arg1);
    D_800B3664 = D_800B3668;
}

M2C_UNK func_80037828(s32, s32, s32, s32, s32);     /* extern */
extern s8 *D_800B3664;
extern s8 *D_800B3668;

void func_80038014(s8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    if ((arg0 != NULL) && (M2C_FIELD(arg0, s32 *, 0x10) & 1)) {
        D_800B3664 = arg0;
    }
    func_80037828(arg1, arg2, arg3, arg4, arg5);
    D_800B3664 = D_800B3668;
}

extern s32 D_800B3638;
extern s8* D_800B3640;
s32 Team_IsOpponentIndexUsed(s32 arg0) {
    s32 i;
    s8* p;

    if (arg0 == 0) {
        return 0;
    }
    p = D_800B3640;
    for (i = 0; i < D_800B3638; i++, p += 0x148) {
        if (arg0 == M2C_FIELD(p, s32*, 0x5C)) {
            return M2C_FIELD(p, s32*, 0x88);
        }
    }

    return 0;
}

extern u8 D_800B368E;
extern PlayerChannelZero_1E D_800B3694[44];

s32 func_800380D0(void) {
    s32 i;

    if (D_800B368E) {
        return 1;
    }
    for (i = 0; i < 44; i++) {
        if (D_800B3694[i].unk_1E) {
            return 1;
        }
    }
    return 0;
}

/**
 * Initialises channel `cp` as a new sound: calls func_8003A2B8(cp) to reset it, then
 * stores arg0 at offsets 0x88 and 0x140, arg1 at 0x13C, arg3 + 0x100 at 0xB2 (the
 * type word that func_80037A48 and func_8003798C test), arg4 at 0xAA, arg5 at 0xBC and
 * arg6 at 0x60 (`priority`). With interrupts masked (func_8004D300(1) is osSetIntMask),
 * it assigns the next handle D_800B365C++ to offset 0x5C and loads
 * ((s32*)arg1[+0xC])[arg3] into offsets 0x8C and 0x30 (`pbase` / `pdata`).
 * Returns the new handle. What arg0, arg1 and arg3 index is not established.
 */
s32 func_8003815C(s32 arg0, s32 arg1, s8* cp, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    s32 mask;
    s32 table;
    s32 val;

    func_8003A2B8(cp);
    M2C_FIELD(cp, s32*, 0x88) = arg0;
    M2C_FIELD(cp, s16*, 0xB2) = arg3 + 0x100;
    M2C_FIELD(cp, s16*, 0xAA) = arg4;
    M2C_FIELD(cp, s16*, 0xBC) = arg5;
    M2C_FIELD(cp, s32*, 0x60) = arg6;
    table = M2C_FIELD(arg1, s32*, 0xC);
    M2C_FIELD(cp, s32*, 0x140) = arg0;
    M2C_FIELD(cp, s32*, 0x13C) = arg1;
    mask = func_8004D300(1);
    M2C_FIELD(cp, s32*, 0x5C) = D_800B365C;
    D_800B365C++;
    val = ((s32*)table)[arg3];
    M2C_FIELD(cp, s32*, 0x8C) = val;
    M2C_FIELD(cp, s32*, 0x30) = val;
    func_8004D300(mask);
    return M2C_FIELD(cp, s32*, 0x5C);
}

#ifdef NON_MATCHING
/* TODO: decompile func_8003821C; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_8003821C.s")
#endif

/*
 * func_8003834C
 *
 * Calls func_8003821C with all seven of its own arguments and returns the
 * result, with a flag word around the call: D_800B3CCC is set to 1 before
 * the call and back to 0 after it.  Each write to the flag is made with
 * interrupts masked: osSetIntMask (func_8004D300, per symbol_addrs.txt) is
 * called with 1 (OS_IM_NONE), the flag is written, and the previous mask it
 * returned is restored.  What the flag is used for is not established.
 */
extern s32 D_800B3CCC;
s32 func_8003821C(s32, s32, s32, s32, s32, s32, s32); /* extern */

s32 func_8003834C(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    s32 ret;
    s32 mask;

    mask = func_8004D300(1);
    D_800B3CCC = 1;
    func_8004D300(mask);
    ret = func_8003821C(arg0, arg1, arg2, arg3, arg4, arg5, arg6);
    mask = func_8004D300(1);
    D_800B3CCC = 0;
    func_8004D300(mask);
    return ret;
}

void func_8003A710(void*);

/**
 * Starts a sound on the first free channel without masking interrupts (compare
 * func_8003821C, which does the same with osSetIntMask(1) around each claim). Returns -1
 * at once if D_800B3CCC or D_800B3CC8 is non-zero. Otherwise, if bit 0 of the word at
 * arg1+4 is clear it calls func_8003A710(arg1); if arg6 is -1 it is replaced by
 * ((s32*)arg1[+8])[arg2]. It then scans the D_800B3640 channel array (0x148 bytes each,
 * D_800B3638 entries) for one whose word at offset 0x30 is 0, marks it in use by storing
 * -1 there, and returns func_8003815C(arg0, arg1, channel, arg2, arg3, arg4, arg6). If
 * no channel is free it returns 0. arg5 is not used. What arg0 and arg1 point to is not
 * established (func_8003815C stores them at channel offsets 0x88/0x140 and 0x13C).
 */
s32 func_800383DC(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, UNUSED s32 arg5, s32 arg6) {
    s32 ret;
    s32* tbl;
    s8* p;
    u32 i;

    ret = 0;
    if ((D_800B3CCC != 0) || (D_800B3CC8 != 0)) {
        return -1;
    }
    if (!(M2C_FIELD(arg1, s32*, 4) & 1)) {
        func_8003A710((void*)arg1);
    }
    if ((u32)arg6 == 0xFFFFFFFFU) {
        tbl = (s32*)M2C_FIELD(arg1, s32*, 8);
        arg6 = *(s32*)(arg2 * 4 + (s32)tbl);
    }
    for (i = 0, p = D_800B3640; i < (u32)D_800B3638; i++, p += 0x148) {
        if (M2C_FIELD(p, s32*, 0x30) == 0) {
            M2C_FIELD(p, s32*, 0x30) = -1;
            ret = func_8003815C(arg0, arg1, p, arg2, arg3, arg4, arg6);
            break;
        }
    }
    return ret;
}

/*
 * func_800384D8
 *
 * Returns 1 if func_80037A48(3) is non-zero. Otherwise scans the byte at
 * offset 0x1E of each of the 45 entries of the 0x24-byte table at
 * D_800B3670 (the same table func_800380D0 scans, which starts one entry
 * later at D_800B3694 and reads the first entry's byte as D_800B368E) and
 * returns that byte plus 10 for the first entry whose byte is not 5;
 * returns 0 if all of them are 5.
 *
 * What the table entries are, and what the value 5 and the +10 mean, is not
 * established. Matching note: the loop is written over 45 entries from
 * D_800B3670; reading the first byte separately as D_800B368E followed by a
 * loop over D_800B3694 gives different register allocation.
 */
s32 func_80037A48(M2C_UNK);                         /* extern */
extern PlayerChannelZero_1E D_800B3670[45];
s32 func_800384D8(void) {
    s32 i;

    if (func_80037A48(3) != 0) {
        return 1;
    }
    for (i = 0; i < 45; i++) {
        if (D_800B3670[i].unk_1E != 5) {
            return D_800B3670[i].unk_1E + 0xA;
        }
    }
    return 0;
}

#ifdef NON_MATCHING
/* TODO: decompile func_80038588; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_80038588.s")
#endif

s32 func_8004D300(s32);                             /* extern */
extern s32 D_800B3638;
extern s8 *D_800B3640;

s32 func_800386E4(s32 arg0, s32 arg1) {
    s32 temp_a0;
    s32 var_s1;
    s32 var_s2;
    s32 var_s3;
    s8 *var_s0;

    if (arg0 == 0) {
        return 0;
    }
    if (arg1 != 0) {
        var_s3 = arg1;
    } else {
        var_s3 = 1;
    }
    var_s0 = D_800B3640;
    var_s1 = 0;
    var_s2 = 0;
    if (D_800B3638 > 0) {
        do {
            temp_a0 = func_8004D300(1);
            if (arg0 == M2C_FIELD(var_s0, s32 *, 0x5C)) {
                M2C_FIELD(var_s0, s32 *, 0x38) = arg1;
                M2C_FIELD(var_s0, s32 *, 0x3C) = var_s3;
                var_s2 += 1;
            }
            func_8004D300(temp_a0);
            var_s1 += 1;
            var_s0 += 0x148;
        } while (var_s1 < D_800B3638);
    }
    return var_s2;
}

extern s32 D_80075C34;
extern s8 D_8007754C;
s32 func_8004D300(s32);

/**
 * Sets a new value for every channel and for D_80075C34. A zero `arg0` is replaced by 1.
 * Each part runs with interrupts masked via func_8004D300(1) (osSetIntMask) and the
 * previous mask restored afterwards: first the byte D_8007754C is cleared; then every
 * entry of the D_800B3640 channel array (D_800B3638 entries of 0x148 bytes) gets the value
 * in offsets 0x38 and 0x3C (the compiled code derives the second copy through a
 * redundant `arg0 != 0 ? arg0 : 1`, kept here so the code matches); finally D_80075C34
 * is set to the value. Compare func_800386E4, which writes the same two fields only on
 * the channels whose handle (offset 0x5C) matches. What the fields mean is not
 * established.
 * Matching note: the value is kept in `arg0` itself; a separate local makes the frame
 * 8 bytes larger.
 */
void func_800387BC(s32 arg0) {
    s32 mask;
    s32 hi;
    s32 i;
    s8* p;

    if (arg0 == 0) {
        arg0 = 1;
    }
    if (arg0 != 0) {
        hi = arg0;
    } else {
        hi = 1;
    }
    mask = func_8004D300(1);
    D_8007754C = 0;
    func_8004D300(mask);
    mask = func_8004D300(1);
    for (i = 0, p = D_800B3640; i < D_800B3638; i++, p += 0x148) {
        M2C_FIELD(p, s32*, 0x38) = arg0;
        M2C_FIELD(p, s32*, 0x3C) = hi;
    }
    func_8004D300(mask);
    mask = func_8004D300(1);
    D_80075C34 = arg0;
    func_8004D300(mask);
}

s32 func_8004D300(s32);                             /* extern */
extern s8 D_8007754C;
extern s32 D_800B3CD0;

void func_80038880(void) {
    s32 temp_v0;

    temp_v0 = func_8004D300(1);
    D_8007754C = 0;
    D_800B3CD0 = 1;
    func_8004D300(temp_v0);
}

#ifdef NON_MATCHING
/* TODO: decompile func_800388BC; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_800388BC.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_80039010; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_80039010.s")
#endif

s32 Audio_ComputeVoiceVolume(channel_t* cp) {
    u32 volume = cp->volume * cp->env_current_vol * cp->velocity * cp->volume_scale;

    volume >>= 0xD;
    if (volume >= 0x8000) {
        volume = 0x7FFF;
    }

    if (cp->IsFX == 0) {
        volume *= mus_master_volume_songs;
    } else {
        volume *= mus_master_volume_effects;
    }

    volume >>= 0xF;

    if (cp->duration != -1) {
        volume = (cp->duration * volume) / cp->duration_scale;
    }

    return volume;
}

f32 Audio_AdvanceVoicePitch(channel_t* arg0, f32 offset) {
    f32 temp_fv1;
    f32 var_fv1;
    f32 var_fv1_2;
    s32 temp_lo;

    temp_fv1 = arg0->base_note;
    if (arg0->port != 0) {
        if (arg0->port >= arg0->wobble_frame) {
            var_fv1_2 = ((temp_fv1 - arg0->last_note) / arg0->port);
            var_fv1_2 *= arg0->wobble_frame;
            temp_fv1 = arg0->last_note + var_fv1_2;
        }
        arg0->port_base = temp_fv1;
    }

    temp_lo = arg0->transpose * (1 - arg0->ignore_transpose);

    arg0->ignore_transpose = 0;

    temp_fv1 += (offset + arg0->pitchbend_calc + temp_lo);
    if (temp_fv1 == arg0->pitch_current) {
        return 0.0f;
    }
    arg0->pitch_current = temp_fv1;

    temp_fv1 = Audio_ExpApproximation(temp_fv1 * 0.0833333333333333287);
    if (temp_fv1 > 2.0) {
        temp_fv1 = 2.0f;
        arg0->velocity = 0;
    }

    return temp_fv1;
}

void Audio_UpdateVoicePlaybackEnd(channel_t* arg0) {
    if (M2C_FIELD(arg0, u16*, 0xA6) != 0x7FFF) {
        if (M2C_FIELD(arg0, u16*, 0xBE) != 0) {
            M2C_FIELD(arg0, s64*, 0x28) = (s32)(M2C_FIELD(arg0, u16*, 0xBE) << 8) + M2C_FIELD(arg0, s64*, 0x20);
        } else {
            M2C_FIELD(arg0, s64*, 0x28) = M2C_FIELD(arg0, s64*, 0x18) - (s32)(M2C_FIELD(arg0, u16*, 0xC0) << 8);
        }
    } else {
        M2C_FIELD(arg0, s64*, 0x28) = 0x7FFFFFFF;
    }

    M2C_FIELD(arg0, u8*, 0xD2) = M2C_FIELD(arg0, u8*, 0xCE);
    M2C_FIELD(arg0, u8*, 0xD3) = M2C_FIELD(arg0, u8*, 0xCD);
    M2C_FIELD(arg0, u8*, 0xD1) = 1;
}

#ifdef NON_MATCHING
/* TODO: decompile func_800395D0; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_800395D0.s")
#endif

void func_80039A44(channel_t* cp) {
    M2C_FIELD(cp, u32*, 0xA0) = M2C_FIELD(cp, u64*, 0x20);
    M2C_FIELD(cp, u8*, 0xEC) = 0;
    M2C_FIELD(cp, u8*, 0xED) = M2C_FIELD(cp, s16*, 0xBC) & 0x80;
}

void Audio_AdvancePanModulation(channel_t* arg0) {
    u32 temp_v1;
    u32 var_v0;

    do {
        arg0->sweep_frame += 0x100;

        temp_v1 = (M2C_FIELD(arg0, u8*, 0xE7) * 2) + M2C_FIELD(arg0, u8*, 0xEC);
        if (temp_v1 < 0x80) {
            M2C_FIELD(arg0, u8*, 0xEC) = temp_v1;
            continue;
        }

        M2C_FIELD(arg0, u8*, 0xEC) = temp_v1 & 0x7F;
        temp_v1 >>= 7;
        if (M2C_FIELD(arg0, u8*, 0xED) == 0) {
            var_v0 = arg0->sweep_amount;
            var_v0 += temp_v1;
            if (var_v0 >= 0xFF) {
                var_v0 = 0xFE;
                M2C_FIELD(arg0, u8*, 0xED) = 1;
            }
            arg0->sweep_amount = var_v0;
        } else {
            var_v0 = arg0->sweep_amount;
            var_v0 -= temp_v1;
            if ((var_v0 >= 0xFF) || (var_v0 == 0)) {
                var_v0 = 1;
                M2C_FIELD(arg0, u8*, 0xED) = 0;
            }
            arg0->sweep_amount = var_v0;
        }
    } while (arg0->sweep_frame < M2C_FIELD(arg0, u64*, 0x0));

    arg0->pan_current = 0xFF;
}

#define CH_U8(ch, off) (*(u8*)((u8*)(ch) + (off)))
#define CH_S8(ch, off) (*(s8*)((u8*)(ch) + (off)))

f32 Audio_AdvancePeriodicPitchModulation(channel_t* arg0) {
    CH_U8(arg0, 0xE3)--;
    if (!CH_U8(arg0, 0xE3)) {
        if (CH_S8(arg0, 0xE4) == 0) {
            CH_S8(arg0, 0xE4) = CH_S8(arg0, 0xEB);
            CH_U8(arg0, 0xE3) = CH_U8(arg0, 0xE1);
        } else {
            CH_S8(arg0, 0xE4) = 0;
            CH_U8(arg0, 0xE3) = CH_U8(arg0, 0xE2);
        }
    }

    return CH_S8(arg0, 0xE4);
}

#undef CH_U8
#undef CH_S8

f32 Audio_ComputeSinePitchModulation(channel_t* arg0) {
    s32 temp_v0 = M2C_FIELD(arg0, u16*, 0xB6) - M2C_FIELD(arg0, u8*, 0xC4);
    f32 tmp;

    if (temp_v0 > 0) {
        tmp = M2C_FIELD(arg0, f32*, 0x40) * __sinf(((temp_v0 / (f32)(u32)M2C_FIELD(arg0, u8*, 0xE8)) * 2) * 3.14159260000000007);
        M2C_FIELD(arg0, f32*, 0x78) = tmp;
    }
    return M2C_FIELD(arg0, f32*, 0x78);
}

void Audio_AdvancePitchEnvelope(channel_t* arg0) {
    s32 tmp;

    do {
        M2C_FIELD(arg0, u64*, 0x8) += 0x100;

        arg0->cont_vol_repeat_count--;
        if (arg0->cont_vol_repeat_count) {
            continue;
        }

        tmp = *arg0->pvolumebase++;
        if (tmp >= 0x80u) {
            arg0->volume = tmp & 0x7F;

            tmp = *arg0->pvolumebase++;
            if (tmp >= 0x80u) {
                arg0->cont_vol_repeat_count = (tmp & 0x7F) << 8;
                arg0->cont_vol_repeat_count += *arg0->pvolumebase++ + 2;
            } else {
                arg0->cont_vol_repeat_count = tmp + 2;
            }
        } else {
            arg0->volume = tmp;
            arg0->cont_vol_repeat_count = 1;
        }
    } while (M2C_FIELD(arg0, u64*, 0x8) < M2C_FIELD(arg0, u64*, 0x0));
}

void Audio_AdvanceVolumeEnvelope(channel_t* arg0) {
    u8 tmp;

    do {
        M2C_FIELD(arg0, u64*, 0x10) += 0x100;

        arg0->cont_pb_repeat_count--;
        if (arg0->cont_pb_repeat_count) {
            continue;
        }

        tmp = *arg0->ppitchbendbase++;
        if (tmp >= 0x80) {
            arg0->pitchbend = (f32)(tmp & 0x7F) - 64.0;
            arg0->pitchbend_calc = arg0->pitchbend * arg0->bendrange;
            tmp = *arg0->ppitchbendbase++;
            if (tmp >= 0x80) {
                arg0->cont_pb_repeat_count = (tmp & 0x7F) << 8;
                arg0->cont_pb_repeat_count += *arg0->ppitchbendbase++ + 2;
            } else {
                arg0->cont_pb_repeat_count = tmp + 2;
            }
        } else {
            arg0->pitchbend = (f32)(tmp)-64.0;
            arg0->pitchbend_calc = arg0->pitchbend * arg0->bendrange;
            arg0->cont_pb_repeat_count = 1;
        }
    } while (M2C_FIELD(arg0, u64*, 0x10) < M2C_FIELD(arg0, u64*, 0x0));
}

f32 Audio_ExpApproximation(f32 arg0) {
    f32 temp_fa1;
    f32 temp_fv1;

    if (arg0 == 0.0f) {
        return 1.0f;
    }

    if (arg0 > 0.0f) {
        temp_fv1 = SQ(arg0);
        temp_fa1 = SQ(temp_fv1);
        return (arg0 * 0.693147180559944953) + 1.0 + (temp_fv1 * 0.240226506959100999) +
               ((temp_fv1 * arg0) * 0.055504108664821597) + (temp_fa1 * 0.00961812910762848035) +
               ((temp_fa1 * arg0) * 0.00133335581464283999) + ((temp_fa1 * temp_fv1) * 0.000154035303933816006);
    } else {
        arg0 = -arg0;
        temp_fv1 = SQ(arg0);
        temp_fa1 = SQ(temp_fv1);
        return 1.0 / ((arg0 * 0.693147180559944953) + 1.0 + (temp_fv1 * 0.240226506959100999) +
                      ((temp_fv1 * arg0) * 0.055504108664821597) + (temp_fa1 * 0.00961812910762848035) +
                      ((temp_fa1 * arg0) * 0.00133335581464283999) + ((temp_fa1 * temp_fv1) * 0.000154035303933816006));
    }
}

void Audio_RelocateSoundBank(u8* arg0, s32 arg1) {
    UNUSED s32 pad;
    u32 i;
    f32 var_fv0;
    SoundBank* soundbank = arg0;
    u8 temp_v1;

    if (soundbank->flags & 1) {
        return;
    }

    soundbank->flags |= 1;

    Audio_RelocatePointerArray(&soundbank->basenote, arg0, 3);
    Audio_RelocatePointerArray(soundbank->wave_list, arg0, soundbank->count);

    for (i = 0; i < soundbank->count; i++) {
        f32* ptr = &soundbank->detune[i];

        temp_v1 = *(u8*)ptr;
        if (temp_v1 & 0x80) {
            var_fv0 = -(0x100 - temp_v1);
        } else {
            var_fv0 = (s32)temp_v1;
        }
        *ptr = var_fv0 / 100.0;

        temp_v1 = soundbank->basenote[i] - 0x30;
        if (temp_v1 & 0x80) {
            var_fv0 = -(0x100 - temp_v1);
        } else {
            var_fv0 = (s32)temp_v1;
        }
        *ptr += var_fv0;

        if (soundbank->wave_list[i]->flags == 0) {
            u32 tmp = soundbank->wave_list[i]->base;

            if ((tmp & 0xFF000000) != 0xFF000000) {
                tmp += arg1;
                soundbank->wave_list[i]->base = tmp;
            }

            soundbank->wave_list[i]->flags = 1;

            if (soundbank->wave_list[i]->waveInfo.rawWave.loop != NULL) {
                soundbank->wave_list[i]->waveInfo.rawWave.loop =
                    (u32)soundbank + (u32)soundbank->wave_list[i]->waveInfo.rawWave.loop;
            }

            if (soundbank->wave_list[i]->type == AL_ADPCM_WAVE) {
                soundbank->wave_list[i]->waveInfo.adpcmWave.book =
                    (u32)soundbank + (u32)soundbank->wave_list[i]->waveInfo.adpcmWave.book;
            }
        }
    }

    osWritebackDCacheAll();
}

s32 Audio_RandomScale(s32 arg0) {
    s32 i;
    s32 tmp;
    f32 tmpf;

    for (i = 0; i < 8; i++) {
        tmp = mus_random_seed & 0x48000000;
        mus_random_seed <<= 1;
        if ((tmp == 0x48000000) || (tmp == 0x08000000)) {
            mus_random_seed |= 1;
        }
    }

    tmpf = mus_random_seed / 65536.0f;
    tmpf /= 65536.0f;
    return arg0 * tmpf;
}

void func_8003A2B8(s8* cp) {
    u8* ptr;
    s32 i;
    s32 tempo;

    M2C_FIELD(cp, s32*, 0x34) = 0;
    M2C_FIELD(cp, s32*, 0x144) = 0;
    M2C_FIELD(cp, s64*, 0x0) = 0;
    M2C_FIELD(cp, s64*, 0x8) = 0;
    M2C_FIELD(cp, s64*, 0x10) = 0;
    M2C_FIELD(cp, s64*, 0x18) = 0;
    M2C_FIELD(cp, s64*, 0x20) = 0;
    M2C_FIELD(cp, s64*, 0x28) = 0;

    ptr = (u8*)cp + 0x34;
    for (i = 0x34; i < 0x148; i++) {
        *ptr++ = 0;
    }

    M2C_FIELD(cp, u16*, 0xAC) = 0xFFFF;
    M2C_FIELD(cp, u8*, 0xE0) = 0xFF;
    M2C_FIELD(cp, u8*, 0xCC) = 0xFF;
    M2C_FIELD(cp, f32*, 0x48) = 99.9f;
    tempo = 0x6000 / (s32)D_800B364C;
    M2C_FIELD(cp, s16*, 0xB4) = tempo;
    M2C_FIELD(cp, s16*, 0xA8) = tempo;
    M2C_FIELD(cp, s64*, 0x18) = M2C_FIELD(cp, s64*, 0x0) = 0;
    M2C_FIELD(cp, s16*, 0xA6) = 1;
    M2C_FIELD(cp, u8*, 0xE5) = 0;
    M2C_FIELD(cp, u8*, 0xE6) = 0x7F;
    M2C_FIELD(cp, s16*, 0xB8) = 0;
    M2C_FIELD(cp, u8*, 0xC5) = 0;
    M2C_FIELD(cp, u8*, 0xCA) = 0x7F;
    M2C_FIELD(cp, u8*, 0xCB) = 0x40;
    M2C_FIELD(cp, s16*, 0xAE) = 1;
    M2C_FIELD(cp, s16*, 0xB0) = 1;
    M2C_FIELD(cp, s32*, 0x38) = -1;
    M2C_FIELD(cp, u8*, 0xE7) = 0;
    M2C_FIELD(cp, f32*, 0x7C) = 0.03125f;
    func_80036640(cp, 0);
    M2C_FIELD(cp, s16*, 0xAA) = 0x80;
    M2C_FIELD(cp, s16*, 0xBC) = 0x80;
    M2C_FIELD(cp, s16*, 0xA4) = 0x80;
    M2C_FIELD(cp, u8*, 0xCD) = 1;
    M2C_FIELD(cp, u8*, 0xD4) = 1;
    M2C_FIELD(cp, u8*, 0xCF) = 0x7F;
    M2C_FIELD(cp, u8*, 0xD5) = 0xFF;
    M2C_FIELD(cp, f32*, 0x6C) = 1.0f;
    M2C_FIELD(cp, f32*, 0x70) = 0.003921568859f;
    M2C_FIELD(cp, f32*, 0x44) = 0.0f;
    M2C_FIELD(cp, f32*, 0x50) = 0.0f;
    M2C_FIELD(cp, f32*, 0x68) = 0.0f;
    M2C_FIELD(cp, f32*, 0x9C) = 0.0f;
    M2C_FIELD(cp, u8*, 0xD0) = 0x7F;
    M2C_FIELD(cp, u8*, 0xDC) = 0xF;
    M2C_FIELD(cp, u32*, 0xD8) = 1;
    M2C_FIELD(cp, u8*, 0xE8) = 0;
    M2C_FIELD(cp, u8*, 0xE1) = 0;
    M2C_FIELD(cp, s16*, 0xB2) = 0;
    M2C_FIELD(cp, u8*, 0xDD) = 0;
}

s32 func_8004D300(s32);                             /* extern */
extern s8 *D_800B3640;

u32 func_8003A4A8(s32 arg0, M2C_UNK arg1) {
    s32 temp_a0;
    s32 var_s2;
    u32 var_s1;
    s8 *var_s0;

    var_s2 = 0;
    var_s0 = D_800B3640;
    var_s1 = 0;
    if (D_800B3638 != 0) {
loop_2:
        temp_a0 = func_8004D300(1);
        if (M2C_FIELD(var_s0, s32 *, 0x30) == 0) {
            M2C_FIELD(var_s0, s32 *, 0x30) = -1;
            var_s2 = 1;
        }
        func_8004D300(temp_a0);
        if (var_s2 != 0) {
            return var_s1;
        }
        var_s1 += 1;
        var_s0 += 0x148;
        if (var_s1 >= (u32) D_800B3638) {
            goto block_7;
        }
        goto loop_2;
    }
block_7:
    return -1U;
}

void Audio_FillBytes(u8* arg0, u8 arg1, u32 arg2) {
    u8* a0 = arg0;

    while (arg2--) {
        *a0++ = arg1;
    }
}

void Audio_RelocatePointerArray(u8* arg0, u32 arg1, u32 arg2) {
    u32* ptr = arg0;
    u32 i;

    for (i = 0; i < arg2; i++) {
        if (ptr[i] != 0) {
            ptr[i] += arg1;
        }
    }
}

/**
 * Initialises channel `cp` as a new sound (a sibling of func_8003815C): calls
 * func_8003A2B8(cp) to reset it, then stores D_800B3668 at offset 0x88, arg1 at the
 * s16 at 0xB2 (the type word), arg2 at 0xAA, arg3 at 0xBC and arg4 at 0x60 (`priority`).
 * It then raises the interrupt mask with func_8004D300, takes the next handle
 * D_800B365C++ for offset 0x5C, loads ((s32*)D_800B3644)[arg1] into offsets 0x8C and 0x30,
 * restores the mask and returns the handle. The argument of the first func_8004D300 call is
 * an uninitialised stack local in the retail code (`lw $a0, 0x20($sp)`, not the constant
 * 1 that func_8003815C passes); `uninit` reproduces that and must not be given a value.
 * What the table at D_800B3644 holds is not established.
 */
s32 func_8003A638(channel_t* cp, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 val;
    s32 uninit;
    s32 mask;

    func_8003A2B8((s8*)cp);
    M2C_FIELD(cp, s32*, 0x88) = (s32)D_800B3668;
    M2C_FIELD(cp, s16*, 0xB2) = arg1;
    M2C_FIELD(cp, s16*, 0xAA) = arg2;
    M2C_FIELD(cp, s16*, 0xBC) = arg3;
    M2C_FIELD(cp, s32*, 0x60) = arg4;
    mask = func_8004D300(uninit);
    M2C_FIELD(cp, s32*, 0x5C) = D_800B365C;
    D_800B365C++;
    val = ((s32*)D_800B3644)[arg1];
    M2C_FIELD(cp, s32*, 0x8C) = val;
    M2C_FIELD(cp, s32*, 0x30) = val;
    func_8004D300(mask);
    return M2C_FIELD(cp, s32*, 0x5C);
}
