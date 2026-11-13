/* Fixed-layout split; original translation-unit boundaries remain unconfirmed. */
#include "gb_tower_emulator_86CB0.h"

extern u8 D_81138690[];
void AudioSeq_SequencePlayerDisableChannels(u8*, s32);
s32 AudioLoad_IsFontLoadComplete(s32);
s32 AudioLoad_IsSeqLoadComplete(s32);
void AudioLoad_SetFontLoadStatus(s32, s32);
void AudioLoad_SetSeqLoadStatus(s32, s32);
extern M2C_UNK D_81184380;
u8* AudioPlayback_GetInstrumentInner(s32, s32);
typedef struct TradeFlags81112E00 {
    u8 bit7 : 1;
    u8 bit6 : 1;
    u8 rest : 6;
} TradeFlags81112E00;
typedef struct AudioStreamFlags {
    u8 pad0 : 4;
    u8 active : 1;
    u8 pad1 : 3;
} AudioStreamFlags;

extern u16 D_81138A96;
extern u32 D_81138A90;
extern s16 D_81180700;
extern s16 D_81180702;
extern u8* D_81180704;
extern GbApuWrite D_81180848[GB_APU_WRITE_QUEUE_LEN];
extern u8 D_81182468[0x40];
extern s32 D_811824A8;
extern unk_D_8122EEA8 D_811824B8;
extern OSMesgQueue D_811824C0;
extern OSMesg D_811824D8[GB_APU_WRITE_QUEUE_LEN + 1];
extern unk_D_81234690 D_811858B8;
extern volatile s32 D_811858F0;
extern s32 D_811858F8;
extern s32 D_811858FC;
extern s16* D_811859B8[3];
extern s16 D_811859C4[3];
extern u32 D_811859CC;
extern volatile u32 D_811859D4;
extern unk_D_81287B08_jp D_81287B08_jp[];
extern OSMesgQueue* D_812896A0_jp;
extern s32 D_81138A70;
extern u8 D_81138A80[0x10];
extern s32 D_81138AD0;
extern s32 D_81138AD4;
extern s32 D_81138AD8;
extern u16 D_81138ADC[32];
extern u8 D_81138B1C[0x10];
extern u8 D_81138B2C[0x4];
extern u8 D_81138B30[0x10];
extern u8 D_81138B40[0x10];
extern u32 D_81138B50[9];
extern s32 D_81138B80;
extern GbAudioStream D_81138B84;
extern struct GbEmuListZ D_81184928;
extern GbEmuListZ D_81184928;
extern GbEmuEntryZ D_811847C8[1];
extern s16 D_811858CC;
extern Entry811151C8 D_81184668[];

/**
 * Reads the argument of a control-flow command of kind `kind` from the script stream. Zelda 64 audio driver (seqplayer.c), same position and shape.
 * No caller in play (2026-11-13): nothing that runs reaches it, not even through callbacks, data
 * tables or fragment headers.
 * @unverified Name and comment guessed from the code.
 */
u16 AudioSeq_GetScriptControlFlowArgument(u8** stream, u8 kind) {
    u8 flags = D_81138690[kind];
    u16 value = 0;

    if (((flags & 0xFF) & 3) == 1) {
        if (!(flags & 0x80)) {
            value = AudioSeq_ScriptReadU8(stream);
        } else {
            value = AudioSeq_ScriptReadS16(stream);
        }
    }
    return value;
}

typedef struct SeqScriptState811126B8 {
    /* 0x00 */ u8* pc;
    /* 0x04 */ u8* stack[4];
    /* 0x14 */ u8 remLoopIters[4];
    /* 0x18 */ u8 depth;
    /* 0x19 */ s8 value;
} SeqScriptState811126B8;

typedef struct SeqPlayer811126B8 {
    /* 0x00 */ u8 unk00[0x18];
    /* 0x18 */ u8* seqData;
} SeqPlayer811126B8;

u16 AudioSeq_ScriptReadCompressedU16(u8** arg0);

/**
 * Runs a script control-flow command (end, call, loop, jump, branch). Zelda 64 audio driver.
 * No caller in play (2026-11-13): nothing that runs reaches it, not even through callbacks, data
 * tables or fragment headers.
 * @unverified Name and comment guessed from the code.
 */
s32 AudioSeq_HandleScriptFlowControl(SeqPlayer811126B8* seq_player, SeqScriptState811126B8* state, s32 cmd, s32 cmd_arg) {
    u8 depth;

    switch (cmd) {
        case 0xFF:
            if (state->depth == 0) {
                return -1;
            }
            state->pc = state->stack[--state->depth];
            break;
        case 0xFD:
            return AudioSeq_ScriptReadCompressedU16(&state->pc);
        case 0xFE:
            return 1;
        case 0xFC:
            depth = state->depth;
            state->stack[depth] = state->pc;
            state->depth++;
            state->pc = seq_player->seqData + (u16)cmd_arg;
            break;
        case 0xF8:
            depth = state->depth;
            state->remLoopIters[depth] = cmd_arg;
            state->stack[state->depth++] = state->pc;
            break;
        case 0xF7:
            state->remLoopIters[state->depth - 1]--;
            if (state->remLoopIters[state->depth - 1] != 0) {
                state->pc = state->stack[state->depth - 1];
            } else {
                state->depth--;
            }
            break;
        case 0xF6:
            state->depth--;
            break;
        case 0xF5:
        case 0xF9:
        case 0xFA:
        case 0xFB:
            if (cmd == 0xFA && state->value != 0) {
                break;
            }
            if (cmd == 0xF9 && state->value >= 0) {
                break;
            }
            if (cmd == 0xF5 && state->value < 0) {
                break;
            }
            state->pc = seq_player->seqData + (u16)cmd_arg;
            break;
        case 0xF2:
        case 0xF3:
        case 0xF4:
            if (cmd == 0xF3 && state->value != 0) {
                break;
            }
            if (cmd == 0xF2 && state->value >= 0) {
                break;
            }
            state->pc += (s8)(cmd_arg & 0xFF);
            break;
    }
    return 0;
}

#include "fragments/fragment000_80C00/gb_tower_emulator_86CB0_types_2.h"
extern Item8111539C D_81184850;

void AudioPlayback_InitNoteLists(void*);
typedef struct Bits81112894 {
    u8 b80 : 1;
    u8 b40 : 1;
    u8 b20 : 1;
    u8 b10 : 1;
    u8 b08 : 1;
    u8 b04 : 1;
    u8 b02 : 1;
    u8 b01 : 1;
} Bits81112894;
extern u8 D_81136998[];
/**
 * Resets a sequence channel to its defaults. Zelda 64 audio driver.
 * Not reached in play (2026-11-13): did not run in a GB player session (boot, Continue, menus) or
 * in a tour of the menus and a COM battle.
 * @unverified Name and comment guessed from the code.
 */
void AudioSeq_InitSequenceChannel(void* obj) {
    s8* arg0 = obj;
    s32 i;

    if ((Item8111539C*)arg0 != &D_81184850) {
        ((Bits81112894*)arg0)->b80 = 0;
        ((Bits81112894*)arg0)->b40 = 0;
        ((Bits81112894*)arg0)->b20 = 0;
        ((Bits81112894*)arg0)->b10 = 0;
        ((Bits81112894*)arg0)->b08 = 0;
        ((Bits81112894*)arg0)->b04 = 0;
        M2C_FIELD(arg0, s16*, 0x24) = 0;
        ((Bits81112894*)arg0)->b02 = 0;
        M2C_FIELD(arg0, s8*, 9) = 0;
        M2C_FIELD(arg0, u8*, 1) = 0xFF;
        M2C_FIELD(arg0, s8*, 0x78) = 0;
        M2C_FIELD(arg0, s8*, 0xA) = 0x40;
        M2C_FIELD(arg0, u8*, 0xB) = 0x80;
        M2C_FIELD(arg0, s8*, 0xD) = 0;
        M2C_FIELD(arg0, s8*, 0xE) = 0;
        M2C_FIELD(arg0, s32*, 0x40) = 0;
        M2C_FIELD(arg0, s8*, 8) = 0;
        M2C_FIELD(arg0, s8*, 4) = 0;
        M2C_FIELD(arg0, s8*, 0xC) = 0;
        M2C_FIELD(arg0, s8*, 5) = 3;
        M2C_FIELD(arg0, s8*, 6) = 1;
        M2C_FIELD(arg0, s16*, 0x1E) = 0;
        M2C_FIELD(arg0, u8**, 0x80) = D_81136998;
        M2C_FIELD(arg0, s8*, 0x7C) = 0x20;
        M2C_FIELD(arg0, s16*, 0x14) = 0x800;
        M2C_FIELD(arg0, s16*, 0x10) = 0x800;
        M2C_FIELD(arg0, s8*, 0x7D) = 0;
        M2C_FIELD(arg0, s16*, 0x16) = 0;
        M2C_FIELD(arg0, s16*, 0x12) = 0;
        M2C_FIELD(arg0, s16*, 0x18) = 0;
        M2C_FIELD(arg0, s16*, 0x1A) = 0;
        M2C_FIELD(arg0, s16*, 0x1C) = 0;
        M2C_FIELD(arg0, s32*, 0xD0) = 0;
        M2C_FIELD(arg0, s16*, 0x20) = 0;
        M2C_FIELD(arg0, s8*, 0xF) = 0;
        M2C_FIELD(arg0, f32*, 0x2C) = 1.0f;
        M2C_FIELD(arg0, f32*, 0x28) = 1.0f;
        M2C_FIELD(arg0, f32*, 0x38) = 1.0f;
        for (i = 0; i < 8; i++) {
            M2C_FIELD(arg0, s8*, 0xC4 + i) = -1;
        }
        ((Bits81112894*)arg0)->b01 = 0;
        AudioPlayback_InitNoteLists(arg0 + 0x84);
    }
}

extern struct GbEmuListZ D_81184928;
typedef struct Pair811129E0 { u8 a; u8 pad[3]; s32 b; } Pair811129E0;
typedef struct Part811129E0 {
    u8 b80 : 1;
    u8 b40 : 1;
    u8 b20 : 1;
    u8 b10 : 1;
    u8 b08 : 1;
    u8 b04 : 1;
    u8 b02 : 1;
    u8 b01 : 1;
    u8 unk01;
    u8 unk02;
    u8 unk03;
    u8 unk04;
    u8 pad05;
    u8 unk06;
    u8 pad07;
    u8 unk08;
    char pad09[0xF];
    Pair811129E0 unk18;
    char pad20[2];
    s16 unk22;
    f32 unk24;
    f32 unk28;
    f32 unk2C;
    char pad30[0x10];
    s16 unk40;
    s16 unk42;
    s16 unk44;
    s32 unk48;
    s32 unk4C;
    char pad50[4];
    void* owner;
    char pad58[0x18];
    u8 unk70;
} Part811129E0;
typedef struct Owner811129E0 {
    char pad0[0x50];
    Part811129E0* slots[11];
    Pair811129E0 unk7C;
} Owner811129E0;
s32 AudioSeq_AudioListPopBack(s8*);
void AudioPlayback_SeqLayerNoteDecay();
/**
 * Gives channel `arg0` a layer in slot `arg1`, taking one from the free list when needed. Zelda 64 audio driver.
 * No caller in play (2026-11-13): nothing that runs reaches it, not even through callbacks, data
 * tables or fragment headers.
 * @unverified Name and comment guessed from the code.
 */
s32 AudioSeq_SeqChannelSetLayer(Owner811129E0* arg0, s32 arg1) {
    Part811129E0* p;
    s32 pad; // FAKE: stack padding
    if (arg0->slots[arg1] == NULL) {
        arg0->slots[arg1] = (Part811129E0*)AudioSeq_AudioListPopBack((s8*)&D_81184928);
        if (arg0->slots[arg1] == NULL) {
            arg0->slots[arg1] = NULL;
            return -1;
        }
    } else {
        AudioPlayback_SeqLayerNoteDecay(arg0->slots[arg1]);
    }
    p = arg0->slots[arg1];
    p->owner = arg0;
    p->unk18 = arg0->unk7C;
    p->b80 = 1;
    p->b20 = 0;
    p->b10 = 0;
    p->b40 = 0;
    p->b02 = 0;
    p->unk18.a = 0;
    p->b01 = 0;
    p->unk01 = 0x40;
    p->unk08 = 0;
    p->unk70 = 0;
    p->unk03 = 0;
    p->unk04 = 0x80;
    p->unk06 = 0x40;
    p->unk22 = 0;
    p->unk40 = 0;
    p->unk42 = 0;
    p->unk44 = 0;
    p->unk48 = 0;
    p->unk4C = 0;
    p->unk02 = 0xFF;
    p->unk24 = 1.0f;
    p->unk28 = 1.0f;
    p->unk2C = 0.0f;
    return 0;
}

/**
 * Decays the layer's note and turns the layer off. Zelda 64 audio driver.
 * Not reached in play (2026-11-13): did not run in a GB player session (boot, Continue, menus) or
 * in a tour of the menus and a COM battle.
 * @unverified Name and comment guessed from the code.
 */
void AudioSeq_SeqLayerDisable(Particle31FlagsA* arg0) {
    if (arg0 != NULL) {
        AudioPlayback_SeqLayerNoteDecay(arg0);
        arg0->b80 = 0;
        arg0->b40 = 1;
    }
}

/**
 * Returns layer slot `arg1` of a channel to the free list. Zelda 64 audio driver.
 * Not reached in play (2026-11-13): did not run in a GB player session (boot, Continue, menus) or
 * in a tour of the menus and a COM battle.
 * @unverified Name and comment guessed from the code.
 */
void AudioSeq_SeqLayerFree(s8** arg0, s32 arg1) {
    s8* temp = arg0[arg1 + 0x14];

    if (temp != NULL) {
        AudioSeq_AudioListPushBack((s8*)&D_81184928, temp + 0x74);
        AudioSeq_SeqLayerDisable((Particle31FlagsA*)temp);
        arg0[arg1 + 0x14] = NULL;
    }
}

/** Resets all particle slots of a display object. */
void AudioSeq_SequenceChannelDisable(DisplayObject* arg0) {
    s32 i;

    for (i = 0; i < 4; i++) {
        AudioSeq_SeqLayerFree(arg0, i);
    }
    AudioPlayback_NotePoolClear((s8*)arg0 + 0x84);
    ((Particle31Flags*)arg0)->b80 = 0;
    ((Particle31Flags*)arg0)->b40 = 1;
}

/**
 * Resets each channel selected in `mask`. Zelda 64 audio driver.
 * No caller in play (2026-11-13): nothing that runs reaches it, not even through callbacks, data
 * tables or fragment headers.
 * @unverified Name and comment guessed from the code.
 */
void AudioSeq_SequencePlayerSetupChannels(s8* arg0, u16 mask) {
    s32 i;
    s8* item;

    for (i = 0; i < 16; i++) {
        if (mask & 1) {
            item = M2C_FIELD(arg0, s8**, 0x34 + i * 4);
            M2C_FIELD(item, u8*, 7) = M2C_FIELD(arg0, u8*, 5);
            M2C_FIELD(item, u8*, 3) = M2C_FIELD(arg0, u8*, 3);
            M2C_FIELD(item, u8*, 2) = M2C_FIELD(arg0, u8*, 2);
        }
        mask = (s32)mask >> 1;
    }
}

void func_81112B84(Item8111539C*);

/**
 * Disables each channel selected in `channel_bits`. Zelda 64 audio driver.
 * Not reached in play (2026-11-13): did not run in a GB player session (boot, Continue, menus) or
 * in a tour of the menus and a COM battle.
 * @unverified Name and comment guessed from the code.
 */
void AudioSeq_SequencePlayerDisableChannels(u8* seqPlayer, s32 channel_bits) {
    Item8111539C* channel;
    s32 i;

    for (i = 0; i < 16; i++) {
        channel = M2C_FIELD(seqPlayer, Item8111539C**, 0x34 + i * 4);
        if (((u32)channel != (u32)&D_81184850) == 1) {
            func_81112B84(channel);
        }
    }
}

/**
 * Starts channel `arg1` at script address `arg2`. Zelda 64 audio driver.
 * No caller in play (2026-11-13): nothing that runs reaches it, not even through callbacks, data
 * tables or fragment headers.
 * @unverified Name and comment guessed from the code.
 */
void AudioSeq_SequenceChannelEnable(Particle2D68** arg0, u8 arg1, s32 arg2) {
    Particle2D68* p = arg0[arg1 + 13];
    s32 i;

    p->unk_78 = 0;
    p->unk_60 = arg2;
    p->b80 = 1;
    p->b40 = 0;
    p->unk_1E = 0;
    for (i = 0; i < 4; i++) {
        if (p->unk_50[i] != NULL) {
            AudioSeq_SeqLayerFree((s8**)p, i);
        }
    }
}

/**
 * Stops a sequence player: disables its channels, clears its note pool and marks its data discardable. Zelda 64 audio driver.
 * Not reached in play (2026-11-13): did not run in a GB player session (boot, Continue, menus) or
 * in a tour of the menus and a COM battle.
 * @unverified Name and comment guessed from the code.
 */
void AudioSeq_SequencePlayerDisable(u8* arg0) {
    AudioSeq_SequencePlayerDisableChannels(arg0, 0xFFFF);
    AudioPlayback_NotePoolClear((s8*)arg0 + 0x98);
    ((TradeFlags81112E00*)arg0)->bit6 = 1;
    ((TradeFlags81112E00*)arg0)->bit7 = 0;
    if (AudioLoad_IsSeqLoadComplete(arg0[4]) != 0) {
        AudioLoad_SetSeqLoadStatus(arg0[4], 3);
    }
    if (AudioLoad_IsFontLoadComplete(arg0[5]) != 0) {
        AudioLoad_SetFontLoadStatus(arg0[5], 4);
    }
    if (arg0[5] == M2C_FIELD(&D_81184380, s16*, 0x3E)) {
        M2C_FIELD(&D_81184380, s32*, 0x20) = 1;
    } else if (arg0[5] == M2C_FIELD(&D_81184380, s16*, 0x4A)) {
        M2C_FIELD(&D_81184380, s32*, 0x20) = 0;
    }
}

/**
 * Appends an item to the end of a list if it is on no list. Zelda 64 audio driver.
 * Not reached in play (2026-11-13): did not run in a GB player session (boot, Continue, menus) or
 * in a tour of the menus and a COM battle.
 * @unverified Name and comment guessed from the code.
 */
void AudioSeq_AudioListPushBack(s8 *arg0, s8 *arg1)
{
  if ((*((s8 **) (((s8 *) arg1) + 0))) == 0)
  {
    *((s8 **) (((s8 *) (*((s8 **) (((s8 *) arg0) + 0)))) + 4)) = arg1; // FAKE: decomp slop, raw pointer casts stand in for struct fields
    *((s8 **) (((s8 *) arg1) + 0)) = (s8 *) (*((s8 **) (((s8 *) arg0) + 0))); // FAKE: decomp slop, raw pointer casts stand in for struct fields
    *((s8 **) (((s8 *) arg1) + 4)) = arg0;
    *((s8 **) (((s8 *) arg0) + 0)) = arg1;
    *((s32 *) (((s8 *) arg0) + 8)) = ((s32) ((*((s32 *) (((s8 *) arg0) + 8))) + 1)) ^ 0; // FAKE: decomp slop, raw pointer casts stand in for struct fields
    *((s32 *) (((s8 *) arg1) + 0xC)) = (s32) (*((s32 *) (((s8 *) arg0) + 0xC))); // FAKE: decomp slop, raw pointer casts stand in for struct fields
  }
}

/**
 * Removes and returns the last item of a list, or 0 when it is empty. Zelda 64 audio driver.
 * No caller in play (2026-11-13): nothing that runs reaches it, not even through callbacks, data
 * tables or fragment headers.
 * @unverified Name and comment guessed from the code.
 */
s32 AudioSeq_AudioListPopBack(s8 *arg0) {
    s8 *temp_v1;

    temp_v1 = M2C_FIELD(arg0, s8 **, 0);
    if (temp_v1 == arg0) {
        return 0;
    }
    M2C_FIELD(M2C_FIELD(temp_v1, s8 **, 0), s8 **, 4) = arg0;
    M2C_FIELD(arg0, s8 **, 0) = (s8 *) M2C_FIELD(temp_v1, s8 **, 0);
    M2C_FIELD(temp_v1, s8 **, 0) = NULL;
    M2C_FIELD(arg0, s32 *, 8) = (s32) (M2C_FIELD(arg0, s32 *, 8) - 1);
    return M2C_FIELD(temp_v1, s32 *, 8);
}

/**
 * Puts every sequence layer on the free list. Zelda 64 audio driver.
 * Not reached in play (2026-11-13): did not run in a GB player session (boot, Continue, menus) or
 * in a tour of the menus and a COM battle.
 * @unverified Name and comment guessed from the code.
 */
void AudioSeq_InitLayerFreelist(void) {
    s32 i;

    D_81184928.next = &D_81184928;
    D_81184928.prev = &D_81184928;
    D_81184928.count = 0;
    D_81184928.unk_0C = 0;
    for (i = 0; i < 1; i++) {
        D_811847C8[i].owner = &D_811847C8[i];
        D_811847C8[i].next = NULL;
        AudioSeq_AudioListPushBack((s8*)&D_81184928, (s8*)&D_811847C8[i].next);
    }
}

/**
 * Reads one byte from the script stream. Zelda 64 audio driver.
 * No caller in play (2026-11-13): nothing that runs reaches it, not even through callbacks, data
 * tables or fragment headers.
 * @unverified Name and comment guessed from the code.
 */
u8 AudioSeq_ScriptReadU8(u8 **arg0)
{
  u8 new_var; // FAKE: permuter temp
  u8 *temp_a1;
  new_var = *(*arg0);
  temp_a1 = *arg0;
  *arg0 = temp_a1 + 1;
  return new_var; // FAKE: permuter temp
}

/**
 * Reads a big-endian 16-bit value from the script stream. Zelda 64 audio driver.
 * No caller in play (2026-11-13): nothing that runs reaches it, not even through callbacks, data
 * tables or fragment headers.
 * @unverified Name and comment guessed from the code.
 */
s16 AudioSeq_ScriptReadS16(u8** arg0) {
    s16 tmp = *(*arg0)++ << 8;

    tmp = *(*arg0)++ | tmp;
    return tmp;
}

/**
 * AudioSeq_ScriptReadCompressedU16
 *
 * Reads a one- or two-byte value from the byte stream whose current position
 * is stored at *arg0, advancing that position. If the first byte has bit 7
 * clear it is the result. Otherwise the result is ((first & 0x7F) << 8) |
 * second byte, and the position advances past both bytes.
 * No caller in play (2026-11-13): nothing that runs reaches it, not even through callbacks, data
 * tables or fragment headers.
 * @unverified Name guessed from the code; comment kept.
 */
u16 AudioSeq_ScriptReadCompressedU16(u8** arg0) {
    u16 v;

    v = *(*arg0)++;
    if (v & 0x80) {
        v = (v << 8) & 0x7F00;
        v = *(*arg0)++ | v;
    }
    return v;
}

typedef struct Particle303C {
    u32 b80 : 1;
    u32 b40 : 1;
    u32 b20 : 1;
    u32 b10 : 1;
    u32 rest : 28;
    char pad04[0x3C];
    s16 unk40;
    s16 unk42;
    char pad44[4];
    s32 unk48;
} Particle303C;
void AudioSeq_SeqLayerProcessScriptStep1();
s32 AudioSeq_SeqLayerProcessScriptStep2();
s32 AudioSeq_SeqLayerProcessScriptStep3();
s32 AudioSeq_SeqLayerProcessScriptStep4();
s32 AudioSeq_SeqLayerProcessScriptStep5();
/**
 * Runs a layer's script for one tick. Zelda 64 audio driver.
 * No caller in play (2026-11-13): nothing that runs reaches it, not even through callbacks, data
 * tables or fragment headers.
 * @unverified Name and comment guessed from the code.
 */
void AudioSeq_SeqLayerProcessScript(Particle303C* arg0) {
    s32 ret;
    if (arg0->b80) {
        if (arg0->unk40 >= 2) {
            arg0->unk40--;
            if (!arg0->b20 && arg0->unk42 >= arg0->unk40) {
                AudioPlayback_SeqLayerNoteDecay((Particle31FlagsA*)arg0);
                arg0->b20 = 1;
            }
        } else {
            AudioSeq_SeqLayerProcessScriptStep1(arg0);
            ret = AudioSeq_SeqLayerProcessScriptStep2(arg0);
            if (ret != -1) {
                ret = AudioSeq_SeqLayerProcessScriptStep3(arg0, ret);
                if (ret != -1) {
                    ret = AudioSeq_SeqLayerProcessScriptStep4(arg0, ret);
                }
                if (ret != -1) {
                    AudioSeq_SeqLayerProcessScriptStep5(arg0, ret);
                }
                if (arg0->b20 == 1 && (arg0->unk48 != 0 || arg0->b10)) {
                    AudioPlayback_SeqLayerNoteDecay((Particle31FlagsA*)arg0);
                }
            }
        }
    }
}

/**
 * Decays or releases the layer's note before the next script command. Zelda 64 audio driver.
 * No caller in play (2026-11-13): nothing that runs reaches it, not even through callbacks, data
 * tables or fragment headers.
 * @unverified Name and comment guessed from the code.
 */
void AudioSeq_SeqLayerProcessScriptStep1(Particle3140* arg0) {
    if (!arg0->b10) {
        AudioPlayback_SeqLayerNoteDecay((Particle31FlagsA*)arg0);
    } else if (arg0->unk_48 != NULL && arg0 == arg0->unk_48->unk_48) {
        AudioPlayback_SeqLayerNoteDecay((Particle31FlagsA*)arg0);
    }
    switch (arg0->unk_08 & ~0x80) {
        case 1:
        case 2:
            arg0->unk_08 = 0;
            break;
    }
    arg0->b04 = 1;
}

s8* AudioPlayback_AllocNote(s8*);
void AudioEffects_InitVibrato(void*);

typedef struct Sample811131CC {
    /* 0x00 */ u32 codec : 4;
    /* 0x00 */ u32 medium : 2;
    /* 0x00 */ u32 rest : 26;
} Sample811131CC;

typedef struct Sound811131CC {
    /* 0x00 */ Sample811131CC* sample;
} Sound811131CC;

typedef struct Layer811131CC {
    /* 0x00 */ u32 enabled : 1;
    /* 0x00 */ u32 finished : 1;
    /* 0x00 */ u32 stopSomething : 1;
    /* 0x00 */ u32 continuousNotes : 1;
    /* 0x00 */ u32 bit3 : 1;
    /* 0x00 */ u32 ignoreDrumPan : 1;
    /* 0x00 */ u32 bit6 : 1;
    /* 0x00 */ u32 bit1 : 1;
    /* 0x01 */ u32 pad01 : 16;
    /* 0x03 */ u8 status;
    /* 0x04 */ u8 pad04[0x48 - 0x04];
    /* 0x48 */ struct Note811131CC* note;
    /* 0x4C */ u8 pad4C[4];
    /* 0x50 */ Sound811131CC* sound;
} Layer811131CC;

typedef struct Note811131CC {
    /* 0x00 */ u8 pad00[0x44];
    /* 0x44 */ Layer811131CC* parentLayer;
} Note811131CC;

/**
 * Gets a note for the layer, reusing the current one for the same sound. Zelda 64 audio driver.
 * No caller in play (2026-11-13): nothing that runs reaches it, not even through callbacks, data
 * tables or fragment headers.
 * @unverified Name and comment guessed from the code.
 */
s32 AudioSeq_SeqLayerProcessScriptStep5(Layer811131CC* layer, u32 same_sound) {
    Note811131CC* note;

    if (!layer->stopSomething && layer->sound != NULL && layer->sound->sample->codec == 2 &&
        layer->sound->sample->medium != 0) {
        layer->stopSomething = 1;
        return -1;
    }

    if (layer->continuousNotes == 1 && layer->bit1 == 1) {
        return 0;
    }

    if (layer->continuousNotes != 1 || layer->note == NULL || !layer->status || same_sound != 1 ||
        layer != layer->note->parentLayer) {
        if (same_sound == 0) {
            AudioPlayback_SeqLayerNoteDecay((Particle31FlagsA*)layer);
        }
        layer->note = (Note811131CC*)AudioPlayback_AllocNote((s8*)layer);
    }
    if (layer->note != NULL && layer->note->parentLayer == layer) {
        note = layer->note;
        AudioEffects_InitVibrato(note);
    }
    return 0;
}

typedef struct SeqPlayer811132E4 {
    /* 0x00 */ u8 unk00[0xE];
    /* 0x0E */ s16 transposition;
    /* 0x10 */ u8 unk10[0x18 - 0x10];
    /* 0x18 */ u8* seqData;
    /* 0x1C */ u8 unk1C[0x90 - 0x1C];
    /* 0x90 */ u8* velocityTable;
    /* 0x94 */ u8* durationTable;
} SeqPlayer811132E4;

typedef struct Channel811132E4 {
    /* 0x00 */ u8 unk00[0x24];
    /* 0x24 */ s16 transposition;
    /* 0x26 */ u8 unk26[0x4C - 0x26];
    /* 0x4C */ struct SeqPlayer811132E4* seqPlayer;
} Channel811132E4;

typedef struct ScriptState811132E4 {
    /* 0x00 */ u8* pc;
} ScriptState811132E4;

typedef struct Layer811132E4 {
    /* 0x00 */ u8 enabled : 1;
    /* 0x00 */ u8 finished : 1;
    /* 0x00 */ u8 stopSomething : 1;
    /* 0x00 */ u8 continuousNotes : 1;
    /* 0x00 */ u8 bit3 : 1;
    /* 0x00 */ u8 notePropertiesNeedInit : 1;
    /* 0x00 */ u8 ignoreDrumPan : 1;
    /* 0x00 */ u8 bit1 : 1;
    /* 0x01 */ s8 unk01;
    /* 0x02 */ u8 instOrWave;
    /* 0x03 */ u8 unk03;
    /* 0x04 */ u8 noteDuration;
    /* 0x05 */ u8 portamentoTargetNote;
    /* 0x06 */ u8 pan;
    /* 0x07 */ u8 unk07;
    /* 0x08 */ u8 portamentoMode;
    /* 0x09 */ u8 unk09[0x18 - 0x09];
    /* 0x18 */ u8 releaseRate;
    /* 0x19 */ u8 unk19[3];
    /* 0x1C */ u8* envelope;
    /* 0x20 */ s16 portamentoTime;
    /* 0x22 */ s16 transposition;
    /* 0x24 */ u8 unk24[4];
    /* 0x28 */ f32 freqScale;
    /* 0x2C */ u8 unk2C[4];
    /* 0x30 */ f32 velocitySquare;
    /* 0x34 */ u8 unk34[0x3C - 0x34];
    /* 0x3C */ s16 shortNoteDefaultDelay;
    /* 0x3E */ u8 unk3E[0x4C - 0x3E];
    /* 0x4C */ u8* instrument;
    /* 0x50 */ u8 unk50[4];
    /* 0x54 */ Channel811132E4* channel;
    /* 0x58 */ ScriptState811132E4 scriptState;
} Layer811132E4;

extern f32 D_81136378[];
u8 AudioSeq_GetInstrument(u8* arg0, u8 arg1, u8** arg2, u8* arg3);

/**
 * Runs layer script commands until a note command. Zelda 64 audio driver.
 * No caller in play (2026-11-13): nothing that runs reaches it, not even through callbacks, data
 * tables or fragment headers.
 * @unverified Name and comment guessed from the code.
 */
s32 AudioSeq_SeqLayerProcessScriptStep2(Layer811132E4* layer) {
    Channel811132E4* channel = layer->channel;
    ScriptState811132E4* state = &layer->scriptState;
    SeqPlayer811132E4* seqPlayer = channel->seqPlayer;
    u8 cmd;
    u8 cmd_arg8;
    u16 cmd_arg16;
    u16 velocity;

    while (1) {
        cmd = AudioSeq_ScriptReadU8(&state->pc);
        if (cmd <= 0xC0) {
            return cmd;
        }
        if (cmd >= 0xF2) {
            cmd_arg16 = AudioSeq_GetScriptControlFlowArgument(&state->pc, cmd);
            if (AudioSeq_HandleScriptFlowControl(seqPlayer, state, cmd, cmd_arg16) == 0) {
                continue;
            }
            AudioSeq_SeqLayerDisable((Particle31FlagsA*)layer);
            return -1;
        }

        switch (cmd) {
            case 0xC1:
            case 0xCA:
                cmd_arg8 = *(state->pc++);
                if (cmd == 0xC1) {
                    layer->velocitySquare = (f32)(cmd_arg8 * cmd_arg8) / 16129.0f;
                } else {
                    layer->pan = cmd_arg8;
                }
                break;
            case 0xC9:
            case 0xC2:
                cmd_arg8 = *(state->pc++);
                if (cmd == 0xC9) {
                    layer->noteDuration = cmd_arg8;
                } else {
                    layer->transposition = cmd_arg8;
                }
                break;
            case 0xC4:
            case 0xC5:
                if (cmd == 0xC4) {
                    layer->continuousNotes = 1;
                } else {
                    layer->continuousNotes = 0;
                }
                layer->bit1 = 0;
                AudioPlayback_SeqLayerNoteDecay((Particle31FlagsA*)layer);
                break;
            case 0xC3:
                cmd_arg16 = AudioSeq_ScriptReadCompressedU16(&state->pc);
                layer->shortNoteDefaultDelay = cmd_arg16;
                break;
            case 0xC6:
                cmd = AudioSeq_ScriptReadU8(&state->pc);
                if (cmd >= 0x7F) {
                    if (cmd == 0x7F) {
                        layer->instOrWave = 0;
                    } else {
                        layer->instOrWave = cmd;
                        layer->instrument = NULL;
                    }
                    if (cmd == 0xFF) {
                        layer->releaseRate = 0;
                    }
                    break;
                }
                if ((layer->instOrWave = AudioSeq_GetInstrument((u8*)channel, cmd, &layer->instrument, &layer->releaseRate)) == 0) {
                    layer->instOrWave = 0xFF;
                }
                break;
            case 0xC7:
                layer->portamentoMode = AudioSeq_ScriptReadU8(&state->pc);
                cmd = AudioSeq_ScriptReadU8(&state->pc);
                cmd += channel->transposition;
                cmd += layer->transposition;
                cmd += seqPlayer->transposition;
                if (cmd >= 0x80) {
                    cmd = 0;
                }
                layer->portamentoTargetNote = cmd;
                if (layer->portamentoMode & 0x80) {
                    layer->portamentoTime = *(state->pc++);
                    break;
                }
                cmd_arg16 = AudioSeq_ScriptReadCompressedU16(&state->pc);
                layer->portamentoTime = cmd_arg16;
                break;
            case 0xC8:
                layer->portamentoMode = 0;
                break;
            case 0xCB:
                cmd_arg16 = AudioSeq_ScriptReadS16(&state->pc);
                layer->envelope = seqPlayer->seqData + cmd_arg16;
            case 0xCF:
                layer->releaseRate = AudioSeq_ScriptReadU8(&state->pc);
                break;
            case 0xCC:
                layer->ignoreDrumPan = 1;
                break;
            case 0xCD:
                layer->unk01 = AudioSeq_ScriptReadU8(&state->pc);
                break;
            case 0xCE:
                layer->freqScale = D_81136378[(u8)(AudioSeq_ScriptReadU8(&state->pc) + 0x80)];
                break;
            default:
                switch (cmd & 0xF0) {
                    case 0xD0:
                        velocity = seqPlayer->velocityTable[cmd & 0xF];
                        layer->velocitySquare = (f32)(velocity * velocity) / 16129.0f;
                        break;
                    case 0xE0:
                        layer->noteDuration = seqPlayer->durationTable[cmd & 0xF];
                        break;
                }
                break;
        }
    }
}

typedef struct Sound81113650 {
    /* 0x00 */ u8* sample;
    /* 0x04 */ f32 tuning;
} Sound81113650;

typedef struct Drum81113650 {
    /* 0x00 */ u8 releaseRate;
    /* 0x01 */ u8 pan;
    /* 0x02 */ u8 unk02[2];
    /* 0x04 */ Sound81113650 sound;
    /* 0x0C */ u8* envelope;
} Drum81113650;

typedef struct SeqPlayer81113650 {
    /* 0x00 */ u8 unk00[8];
    /* 0x08 */ u16 tempo;
    /* 0x0A */ u8 unk0A[4];
    /* 0x0E */ s16 transposition;
} SeqPlayer81113650;

typedef struct Channel81113650 {
    /* 0x00 */ u32 enabled : 1;
    /* 0x00 */ u32 finished : 1;
    /* 0x00 */ u32 stopScript : 1;
    /* 0x00 */ u32 stopSomething2 : 1;
    /* 0x00 */ u32 hasInstrument : 1;
    /* 0x00 */ u32 rest : 27;
    /* 0x04 */ u8 unk04[3];
    /* 0x07 */ u8 bankId;
    /* 0x08 */ u8 unk08[0x22 - 0x08];
    /* 0x22 */ s16 instOrWave;
    /* 0x24 */ s16 transposition;
    /* 0x26 */ u8 unk26[0x48 - 0x26];
    /* 0x48 */ u8* instrument;
    /* 0x4C */ SeqPlayer81113650* seqPlayer;
} Channel81113650;

typedef struct Portamento81113650 {
    /* 0x00 */ u8 mode;
    /* 0x04 */ f32 cur;
    /* 0x08 */ f32 speed;
    /* 0x0C */ f32 extent;
} Portamento81113650;

typedef struct Layer81113650 {
    /* 0x00 */ u8 enabled : 1;
    /* 0x00 */ u8 finished : 1;
    /* 0x00 */ u8 stopSomething : 1;
    /* 0x00 */ u8 continuousNotes : 1;
    /* 0x00 */ u8 bit3 : 1;
    /* 0x00 */ u8 notePropertiesNeedInit : 1;
    /* 0x00 */ u8 ignoreDrumPan : 1;
    /* 0x00 */ u8 bit1 : 1;
    /* 0x01 */ u8 unk01;
    /* 0x02 */ u8 instOrWave;
    /* 0x03 */ u8 unk03[2];
    /* 0x05 */ u8 portamentoTargetNote;
    /* 0x06 */ u8 pan;
    /* 0x07 */ u8 unk07;
    /* 0x08 */ Portamento81113650 portamento;
    /* 0x18 */ u8 releaseRate;
    /* 0x19 */ u8 unk19[3];
    /* 0x1C */ u8* envelope;
    /* 0x20 */ u16 portamentoTime;
    /* 0x22 */ s16 transposition;
    /* 0x24 */ f32 freqScale;
    /* 0x28 */ f32 bendPitch;
    /* 0x2C */ u8 unk2C[0x40 - 0x2C];
    /* 0x40 */ s16 delay;
    /* 0x42 */ u8 unk42[2];
    /* 0x44 */ s16 duration;
    /* 0x46 */ u8 unk46[0x4C - 0x46];
    /* 0x4C */ u8* instrument;
    /* 0x50 */ Sound81113650* sound;
    /* 0x54 */ Channel81113650* channel;
} Layer81113650;

extern f32 D_81136778[];
extern s16 D_811858EC;
typedef struct Reverb81113650 {
    /* 0x000 */ u8 unk000[0x110];
    /* 0x110 */ Sound81113650 sound;
    /* 0x118 */ u8 unk118[0x158 - 0x118];
} Reverb81113650; // size = 0x158

extern Reverb81113650 D_81184110[];
u8* AudioPlayback_GetInstrumentTunedSample(u8* arg0, s32 arg1);
u8* AudioPlayback_GetDrum(s32 arg0, s32 arg1);

/**
 * Sets up the note's instrument, pitch and velocity from a note command. Zelda 64 audio driver.
 * No caller in play (2026-11-13): nothing that runs reaches it, not even through callbacks, data
 * tables or fragment headers.
 * @unverified Name and comment guessed from the code.
 */
s32 AudioSeq_SeqLayerProcessScriptStep4(Layer81113650* layer, s32 cmd_semitone) {
    s32 same_sound = 1;
    s32 instOrWave;
    s32 vel;
    f32 temp_f14;
    f32 temp_f2;
    Portamento81113650* portamento;
    f32 freqScale;
    f32 freq_scale2;
    Sound81113650* sound;
    u8* instrument;
    Drum81113650* drum;
    f32 tuning;
    Channel81113650* channel;
    SeqPlayer81113650* seqPlayer;
    u8 semitone = cmd_semitone;

    instOrWave = layer->instOrWave;
    channel = layer->channel;
    seqPlayer = channel->seqPlayer;

    if (instOrWave == 0xFF) {
        if (!channel->hasInstrument) {
            return -1;
        }
        instOrWave = channel->instOrWave;
    }

    switch (instOrWave) {
        case 0:
            semitone += channel->transposition + layer->transposition;
            drum = (Drum81113650*)AudioPlayback_GetDrum(channel->bankId, semitone);
            if (drum == NULL) {
                layer->stopSomething = 1;
                layer->duration = layer->delay;
                return -1;
            }
            sound = &drum->sound;
            layer->envelope = drum->envelope;
            layer->releaseRate = drum->releaseRate;
            if (!layer->ignoreDrumPan) {
                layer->pan = drum->pan;
            }
            layer->sound = sound;
            layer->freqScale = sound->tuning;
            break;

        default:
            semitone += seqPlayer->transposition + channel->transposition + layer->transposition;
            if (semitone >= 0x80) {
                layer->stopSomething = 1;
                return -1;
            }
            if (layer->instOrWave == 0xFF) {
                instrument = channel->instrument;
            } else {
                instrument = layer->instrument;
            }
            if (layer->portamento.mode != 0) {
                vel = (semitone > layer->portamentoTargetNote) ? semitone : layer->portamentoTargetNote;
                if (instrument != NULL) {
                    sound = (Sound81113650*)AudioPlayback_GetInstrumentTunedSample(instrument, vel);
                    same_sound = (layer->sound == sound);
                    layer->sound = sound;
                    tuning = sound->tuning;
                } else {
                    layer->sound = NULL;
                    tuning = 1.0f;
                    if (instOrWave >= 0xC0) {
                        layer->sound = &D_81184110[instOrWave - 0xC0].sound;
                    }
                }
                temp_f2 = D_81136778[(s32)semitone] * tuning; // FAKE: no-op cast; only changes the spill slot
                temp_f14 = D_81136778[layer->portamentoTargetNote] * tuning;
                portamento = &layer->portamento;
                switch (layer->portamento.mode & ~0x80) {
                    case 1:
                    case 3:
                    case 5:
                        freq_scale2 = temp_f2;
                        freqScale = temp_f14;
                        break;
                    case 2:
                    case 4:
                        freqScale = temp_f2;
                        freq_scale2 = temp_f14;
                        break;
                    default:
                        freqScale = temp_f2;
                        freq_scale2 = temp_f2;
                        break;
                }
                portamento->extent = (freq_scale2 / freqScale) - 1.0f;
                if (layer->portamento.mode & 0x80) {
                    portamento->speed = 32512.0f * (f32)(s32)seqPlayer->tempo /
                                        ((f32)layer->delay * (f32)D_811858EC * (f32)(s32)layer->portamentoTime);
                } else {
                    portamento->speed = 127.0f / (f32)(s32)layer->portamentoTime;
                }
                portamento->cur = 0.0f;
                layer->freqScale = freqScale;
                if ((layer->portamento.mode & ~0x80) == 5) {
                    layer->portamentoTargetNote = semitone;
                }
                break;
            }
            if (instrument != NULL) {
                sound = (Sound81113650*)AudioPlayback_GetInstrumentTunedSample(instrument, semitone);
                same_sound = (sound == layer->sound);
                layer->sound = sound;
                layer->freqScale = D_81136778[(s32)semitone] * sound->tuning; // FAKE: no-op cast
            } else {
                layer->sound = NULL;
                layer->freqScale = D_81136778[(s32)semitone]; // FAKE: no-op cast
                if (instOrWave >= 0xC0) {
                    layer->sound = &D_81184110[instOrWave - 0xC0].sound;
                }
            }
            break;
    }
    layer->duration = layer->delay;
    layer->freqScale *= layer->bendPitch;
    return same_sound;
}
