/* Fixed-layout split; original translation-unit boundaries remain unconfirmed. */
#include "gb_tower_emulator_86CB0.h"

extern u8 D_81138690[];
void func_81112CE8(u8*, s32);
s32 func_8110CA2C(s32);
s32 func_8110CA68(s32);
void func_8110CAE0(s32, s32);
void func_8110CB10(s32, s32);
extern M2C_UNK D_81184380;
u8* func_81110CA8(s32, s32);
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

u16 func_81112650(u8** stream, u8 kind) {
    u8 flags = D_81138690[kind];
    u16 value = 0;

    if (((flags & 0xFF) & 3) == 1) {
        if (!(flags & 0x80)) {
            value = func_81112FB0(stream);
        } else {
            value = func_81112FC4(stream);
        }
    }
    return value;
}

#ifdef NON_MATCHING
/* TODO: decompile func_811126B8; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_811126B8.s")
#endif

typedef struct Item8111539C {
    /* 0x00 */ u32 active : 1;
    /* 0x00 */ u32 unk00 : 31;
    /* 0x04 */ char unk04[0x48];
    /* 0x4C */ void* owners[2];
} Item8111539C;
extern Item8111539C D_81184850;

void func_811110E0(void*);
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
void func_81112894(void* obj) {
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
        func_811110E0(arg0 + 0x84);
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
s32 func_81112EEC(s8*);
void func_81111090();
s32 func_811129E0(Owner811129E0* arg0, s32 arg1) {
    Part811129E0* p;
    s32 pad;
    if (arg0->slots[arg1] == NULL) {
        arg0->slots[arg1] = (Part811129E0*)func_81112EEC((s8*)&D_81184928);
        if (arg0->slots[arg1] == NULL) {
            arg0->slots[arg1] = NULL;
            return -1;
        }
    } else {
        func_81111090(arg0->slots[arg1]);
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

void func_81112AF8(Particle31FlagsA* arg0) {
    if (arg0 != NULL) {
        func_81111090(arg0);
        arg0->b80 = 0;
        arg0->b40 = 1;
    }
}

void func_81112B34(s8** arg0, s32 arg1) {
    s8* temp = arg0[arg1 + 0x14];

    if (temp != NULL) {
        func_81112EAC((s8*)&D_81184928, temp + 0x74);
        func_81112AF8((Particle31FlagsA*)temp);
        arg0[arg1 + 0x14] = NULL;
    }
}

void Particle31_ResetAllSlots(DisplayObject* arg0) {
    s32 i;

    for (i = 0; i < 4; i++) {
        func_81112B34(arg0, i);
    }
    func_811111E0((s8*)arg0 + 0x84);
    ((Particle31Flags*)arg0)->b80 = 0;
    ((Particle31Flags*)arg0)->b40 = 1;
}

void func_81112BF0(s8* arg0, u16 mask) {
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

void func_81112CE8(u8* seqPlayer, s32 channelBits) {
    Item8111539C* channel;
    s32 i;

    for (i = 0; i < 16; i++) {
        channel = M2C_FIELD(seqPlayer, Item8111539C**, 0x34 + i * 4);
        if (((u32)channel != (u32)&D_81184850) == 1) {
            func_81112B84(channel);
        }
    }
}

void func_81112D68(Particle2D68** arg0, u8 arg1, s32 arg2) {
    Particle2D68* p = arg0[arg1 + 13];
    s32 i;

    p->unk_78 = 0;
    p->unk_60 = arg2;
    p->b80 = 1;
    p->b40 = 0;
    p->unk_1E = 0;
    for (i = 0; i < 4; i++) {
        if (p->unk_50[i] != NULL) {
            func_81112B34((s8**)p, i);
        }
    }
}

void func_81112E00(u8* arg0) {
    func_81112CE8(arg0, 0xFFFF);
    func_811111E0((s8*)arg0 + 0x98);
    ((TradeFlags81112E00*)arg0)->bit6 = 1;
    ((TradeFlags81112E00*)arg0)->bit7 = 0;
    if (func_8110CA68(arg0[4]) != 0) {
        func_8110CB10(arg0[4], 3);
    }
    if (func_8110CA2C(arg0[5]) != 0) {
        func_8110CAE0(arg0[5], 4);
    }
    if (arg0[5] == M2C_FIELD(&D_81184380, s16*, 0x3E)) {
        M2C_FIELD(&D_81184380, s32*, 0x20) = 1;
    } else if (arg0[5] == M2C_FIELD(&D_81184380, s16*, 0x4A)) {
        M2C_FIELD(&D_81184380, s32*, 0x20) = 0;
    }
}

void func_81112EAC(s8 *arg0, s8 *arg1)
{
  if ((*((s8 **) (((s8 *) arg1) + 0))) == 0)
  {
    *((s8 **) (((s8 *) (*((s8 **) (((s8 *) arg0) + 0)))) + 4)) = arg1;
    *((s8 **) (((s8 *) arg1) + 0)) = (s8 *) (*((s8 **) (((s8 *) arg0) + 0)));
    *((s8 **) (((s8 *) arg1) + 4)) = arg0;
    *((s8 **) (((s8 *) arg0) + 0)) = arg1;
    *((s32 *) (((s8 *) arg0) + 8)) = ((s32) ((*((s32 *) (((s8 *) arg0) + 8))) + 1)) ^ 0;
    *((s32 *) (((s8 *) arg1) + 0xC)) = (s32) (*((s32 *) (((s8 *) arg0) + 0xC)));
  }
}

s32 func_81112EEC(s8 *arg0) {
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

void func_81112F2C(void) {
    s32 i;

    D_81184928.next = &D_81184928;
    D_81184928.prev = &D_81184928;
    D_81184928.count = 0;
    D_81184928.unk_0C = 0;
    for (i = 0; i < 1; i++) {
        D_811847C8[i].owner = &D_811847C8[i];
        D_811847C8[i].next = NULL;
        func_81112EAC((s8*)&D_81184928, (s8*)&D_811847C8[i].next);
    }
}

u8 func_81112FB0(u8 **arg0)
{
  u8 new_var;
  u8 *temp_a1;
  new_var = *(*arg0);
  temp_a1 = *arg0;
  *arg0 = temp_a1 + 1;
  return new_var;
}

s16 func_81112FC4(u8** arg0) {
    s16 tmp = *(*arg0)++ << 8;

    tmp = *(*arg0)++ | tmp;
    return tmp;
}

/*
 * func_81112FFC
 *
 * Reads a one- or two-byte value from the byte stream whose current position
 * is stored at *arg0, advancing that position. If the first byte has bit 7
 * clear it is the result. Otherwise the result is ((first & 0x7F) << 8) |
 * second byte, and the position advances past both bytes.
 */
u16 func_81112FFC(u8** arg0) {
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
void func_81113140();
s32 func_811132E4();
s32 func_81113A44();
s32 func_81113650();
s32 func_811131CC();
void func_8111303C(Particle303C* arg0) {
    s32 ret;
    if (arg0->b80) {
        if (arg0->unk40 >= 2) {
            arg0->unk40--;
            if (!arg0->b20 && arg0->unk42 >= arg0->unk40) {
                func_81111090((Particle31FlagsA*)arg0);
                arg0->b20 = 1;
            }
        } else {
            func_81113140(arg0);
            ret = func_811132E4(arg0);
            if (ret != -1) {
                ret = func_81113A44(arg0, ret);
                if (ret != -1) {
                    ret = func_81113650(arg0, ret);
                }
                if (ret != -1) {
                    func_811131CC(arg0, ret);
                }
                if (arg0->b20 == 1 && (arg0->unk48 != 0 || arg0->b10)) {
                    func_81111090((Particle31FlagsA*)arg0);
                }
            }
        }
    }
}

void func_81113140(Particle3140* arg0) {
    if (!arg0->b10) {
        func_81111090((Particle31FlagsA*)arg0);
    } else if (arg0->unk_48 != NULL && arg0 == arg0->unk_48->unk_48) {
        func_81111090((Particle31FlagsA*)arg0);
    }
    switch (arg0->unk_08 & ~0x80) {
        case 1:
        case 2:
            arg0->unk_08 = 0;
            break;
    }
    arg0->b04 = 1;
}

#ifdef NON_MATCHING
/* TODO: decompile func_811131CC; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_811131CC.s")
#endif

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
s32 func_811126B8(void*, void*, s32, s32);
u8 func_81113E84(u8* arg0, u8 arg1, u8** arg2, u8* arg3);

s32 func_811132E4(Layer811132E4* layer) {
    Channel811132E4* channel = layer->channel;
    ScriptState811132E4* state = &layer->scriptState;
    SeqPlayer811132E4* seqPlayer = channel->seqPlayer;
    u8 cmd;
    u8 cmdArg8;
    u16 cmdArg16;
    u16 velocity;

    while (1) {
        cmd = func_81112FB0(&state->pc);
        if (cmd <= 0xC0) {
            return cmd;
        }
        if (cmd >= 0xF2) {
            cmdArg16 = func_81112650(&state->pc, cmd);
            if (func_811126B8(seqPlayer, state, cmd, cmdArg16) == 0) {
                continue;
            }
            func_81112AF8((Particle31FlagsA*)layer);
            return -1;
        }

        switch (cmd) {
            case 0xC1:
            case 0xCA:
                cmdArg8 = *(state->pc++);
                if (cmd == 0xC1) {
                    layer->velocitySquare = (f32)(cmdArg8 * cmdArg8) / 16129.0f;
                } else {
                    layer->pan = cmdArg8;
                }
                break;
            case 0xC9:
            case 0xC2:
                cmdArg8 = *(state->pc++);
                if (cmd == 0xC9) {
                    layer->noteDuration = cmdArg8;
                } else {
                    layer->transposition = cmdArg8;
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
                func_81111090((Particle31FlagsA*)layer);
                break;
            case 0xC3:
                cmdArg16 = func_81112FFC(&state->pc);
                layer->shortNoteDefaultDelay = cmdArg16;
                break;
            case 0xC6:
                cmd = func_81112FB0(&state->pc);
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
                if ((layer->instOrWave = func_81113E84((u8*)channel, cmd, &layer->instrument, &layer->releaseRate)) == 0) {
                    layer->instOrWave = 0xFF;
                }
                break;
            case 0xC7:
                layer->portamentoMode = func_81112FB0(&state->pc);
                cmd = func_81112FB0(&state->pc);
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
                cmdArg16 = func_81112FFC(&state->pc);
                layer->portamentoTime = cmdArg16;
                break;
            case 0xC8:
                layer->portamentoMode = 0;
                break;
            case 0xCB:
                cmdArg16 = func_81112FC4(&state->pc);
                layer->envelope = seqPlayer->seqData + cmdArg16;
            case 0xCF:
                layer->releaseRate = func_81112FB0(&state->pc);
                break;
            case 0xCC:
                layer->ignoreDrumPan = 1;
                break;
            case 0xCD:
                layer->unk01 = func_81112FB0(&state->pc);
                break;
            case 0xCE:
                layer->freqScale = D_81136378[(u8)(func_81112FB0(&state->pc) + 0x80)];
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

#ifdef NON_MATCHING
/* TODO: decompile func_81113650; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_81113650.s")
#endif

typedef struct SeqPlayer81113A44 {
    /* 0x00 */ u32 enabled : 1;
    /* 0x00 */ u32 finished : 1;
    /* 0x00 */ u32 muted : 1;
    /* 0x00 */ u32 rest : 29;
    /* 0x04 */ u8 unk04[0xD8 - 0x04];
    /* 0xD8 */ s32 skipTicks;
} SeqPlayer81113A44;

typedef struct Channel81113A44 {
    /* 0x00 */ u32 enabled : 1;
    /* 0x00 */ u32 finished : 1;
    /* 0x00 */ u32 stopScript : 1;
    /* 0x00 */ u32 stopSomething2 : 1;
    /* 0x00 */ u32 hasInstrument : 1;
    /* 0x00 */ u32 stereoHeadsetEffects : 1;
    /* 0x00 */ u32 largeNotes : 1;
    /* 0x00 */ u32 rest : 17;
    /* 0x03 */ u8 muteBehavior;
    /* 0x04 */ u8 unk04[9];
    /* 0x0D */ u8 velocityRandomVariance;
    /* 0x0E */ u8 gateTimeRandomVariance;
    /* 0x0F */ u8 unk0F[0x4C - 0x0F];
    /* 0x4C */ SeqPlayer81113A44* seqPlayer;
} Channel81113A44;

typedef struct ScriptState81113A44 {
    /* 0x00 */ u8* pc;
} ScriptState81113A44;

typedef struct Layer81113A44 {
    /* 0x00 */ u8 enabled : 1;
    /* 0x00 */ u8 finished : 1;
    /* 0x00 */ u8 stopSomething : 1;
    /* 0x00 */ u8 continuousNotes : 1;
    /* 0x00 */ u8 rest : 4;
    /* 0x01 */ u8 unk01[3];
    /* 0x04 */ u8 gateTime;
    /* 0x05 */ u8 unk05[0x2C - 0x05];
    /* 0x2C */ f32 velocitySquare2;
    /* 0x30 */ f32 velocitySquare;
    /* 0x34 */ u8 unk34[0x3C - 0x34];
    /* 0x3C */ s16 shortNoteDefaultDelay;
    /* 0x3E */ s16 lastDelay;
    /* 0x40 */ s16 delay;
    /* 0x42 */ s16 gateDelay;
    /* 0x44 */ u8 unk44[0x54 - 0x44];
    /* 0x54 */ Channel81113A44* channel;
    /* 0x58 */ ScriptState81113A44 scriptState;
} Layer81113A44;

extern u32 D_811859CC;

#ifdef NON_MATCHING
// Matches the ROM, but uses rodata data that is not placed in this file yet.
s32 func_81113A44(Layer81113A44* layer, s32 cmd) {
    ScriptState81113A44* state = &layer->scriptState;
    u16 delay;
    s32 velocity;
    Channel81113A44* channel = layer->channel;
    SeqPlayer81113A44* seqPlayer = channel->seqPlayer;
    s32 intDelta;
    f32 floatDelta;

    if (cmd == 0xC0) {
        layer->delay = func_81112FFC(&state->pc);
        layer->stopSomething = 1;
        return -1;
    }

    layer->stopSomething = 0;

    if (channel->largeNotes == 1) {
        switch (cmd & 0xC0) {
            case 0x00:
                delay = func_81112FFC(&state->pc);
                velocity = *(state->pc++);
                layer->gateTime = *(state->pc++);
                layer->lastDelay = delay;
                break;
            case 0x40:
                delay = func_81112FFC(&state->pc);
                velocity = *(state->pc++);
                layer->gateTime = 0;
                layer->lastDelay = delay;
                break;
            case 0x80:
                delay = layer->lastDelay;
                velocity = *(state->pc++);
                layer->gateTime = *(state->pc++);
                break;
        }
        if (velocity > 0x7F || velocity < 0) {
            velocity = 0x7F;
        }
        layer->velocitySquare = (f32)velocity * (f32)velocity / 16129.0f;
        cmd -= (cmd & 0xC0);
    } else {
        switch (cmd & 0xC0) {
            case 0x00:
                delay = func_81112FFC(&state->pc);
                layer->lastDelay = delay;
                break;
            case 0x40:
                delay = layer->shortNoteDefaultDelay;
                break;
            case 0x80:
                delay = layer->lastDelay;
                break;
        }
        cmd -= (cmd & 0xC0);
    }

    if (channel->velocityRandomVariance != 0) {
        floatDelta = layer->velocitySquare * (f32)(D_811859CC % channel->velocityRandomVariance) / 100.0f;
        if ((D_811859CC & 0x8000) != 0) {
            floatDelta = -floatDelta;
        }
        layer->velocitySquare2 = layer->velocitySquare + floatDelta;
        if (layer->velocitySquare2 < 0.0f) {
            layer->velocitySquare2 = 0.0f;
        } else if (layer->velocitySquare2 > 1.0f) {
            layer->velocitySquare2 = 1.0f;
        }
    } else {
        layer->velocitySquare2 = layer->velocitySquare;
    }

    layer->delay = delay;
    layer->gateDelay = (layer->gateTime * delay) >> 8;
    if (channel->gateTimeRandomVariance != 0) {
        intDelta = (layer->gateDelay * (D_811859CC % channel->velocityRandomVariance)) / 100;
        if ((D_811859CC & 0x4000) != 0) {
            intDelta = -intDelta;
        }
        layer->gateDelay += intDelta;
        if (layer->gateDelay < 0) {
            layer->gateDelay = 0;
        } else if (layer->gateDelay > layer->delay) {
            layer->gateDelay = layer->delay;
        }
    }

    if ((seqPlayer->muted && (channel->muteBehavior & 0x50)) || channel->stopSomething2) {
        layer->stopSomething = 1;
        return -1;
    }
    if (seqPlayer->skipTicks != 0) {
        layer->stopSomething = 1;
        return -1;
    }
    return cmd;
}
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_81113A44.s")
#endif

/**
 * Splits the byte arg1 into two nibbles and stores each non-zero one in arg0:
 * the low nibble at offset 5 and the high nibble at offset 6. A zero nibble
 * leaves the corresponding byte unchanged. (arg1 itself is reused for the
 * high nibble, which is what the retail register use needs.)
 */
void func_81113E54(u8* arg0, u8 arg1) {
    s32 low;

    low = arg1 & 0xF;
    if (low != 0) {
        arg0[5] = low;
    }
    arg1 = arg1 >> 4;
    if (arg1 != 0) {
        arg0[6] = arg1;
    }
}

u8 func_81113E84(u8* arg0, u8 arg1, u8** arg2, u8* arg3) {
    u8* p = func_81110CA8(arg0[7], arg1);

    if (p == NULL) {
        *arg2 = NULL;
        return 0;
    }
    M2C_FIELD(arg3, s32*, 4) = M2C_FIELD(p, s32*, 4);
    arg3[0] = p[3];
    *arg2 = p;
    arg1++;
    return arg1;
}

void func_81113EF4(u8* arg0, u8 arg1) {
    s16 ret;

    if (arg1 >= 0x80) {
        M2C_FIELD(arg0, s16*, 0x22) = arg1;
        M2C_FIELD(arg0, s32*, 0x48) = 0;
    } else if (arg1 == 0x7F) {
        M2C_FIELD(arg0, s16*, 0x22) = 0;
        M2C_FIELD(arg0, s32*, 0x48) = 1;
    } else {
        ret = M2C_FIELD(arg0, s16*, 0x22) = func_81113E84(arg0, arg1, (u8**)(arg0 + 0x48), arg0 + 0x7C);
        if (ret == 0) {
            ((AudioStreamFlags*)arg0)->active = 0;
            return;
        }
    }
    ((AudioStreamFlags*)arg0)->active = 1;
}

void func_81113F84(u8* arg0, u8 arg1) {
    *(f32*)(arg0 + 0x2C) = (f32)(s32)arg1 / 127.0f;
}

#ifdef NON_MATCHING
/* TODO: decompile func_81113FA8; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_81113FA8.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_81114B54; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_81114B54.s")
#endif

void func_811151C8(s32 arg0) {
    u32 i;

    for (i = 0; i < D_811858CC; i++) {
        if (D_81184668[i].b80 == 1) {
            func_81114B54((s8*)&D_81184668[i]);
            func_81111DC8((s8*)&D_81184668[i]);
        }
    }
    func_81110798();
}

// FAKE: decomp slop. Raw pointer-offset casts stand in for struct fields.
void func_81115254(s8 *arg0)
{
  s8 *new_var;
  s32 temp_t8;
  if ((*((s32 *) (((s8 *) arg0) + 0xD8))) > 0)
  {
    do
    {
      func_81114B54(arg0);
      func_81111DC8(arg0);
      new_var = (s8 *) arg0;
      temp_t8 = (unsigned long long) ((*((s32 *) (new_var + 0xD8))) - 1);
      *((s32 *) (((s8 *) arg0) + 0xD8)) = temp_t8;
    }
    while (temp_t8 > 0);
  }
}

typedef struct Chan811152A4 {
    /* 0x00 */ u8 bit80 : 1;
    /* 0x00 */ u8 bits : 5;
    /* 0x00 */ u8 bit02 : 1;
    /* 0x00 */ u8 bit01 : 1;
    /* 0x01 */ u8 unk01;
    /* 0x02 */ u8 unk02;
    /* 0x03 */ char unk03[5];
    /* 0x08 */ s16 unk08;
    /* 0x0A */ s16 unk0A;
    /* 0x0C */ s16 unk0C;
    /* 0x0E */ s16 unk0E;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ char unk16[6];
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ char unk30[4];
    /* 0x34 */ void* items[16];
    /* 0x74 */ char unk74[0x1C];
    /* 0x90 */ void* unk90;
    /* 0x94 */ void* unk94;
    /* 0x98 */ char unk98[0x44];
    /* 0xDC */ s32 unkDC;
    /* 0xE0 */ char unkE0[0x7C];
} Chan811152A4; // size = 0x15C
extern u8 D_81136978[];
extern u8 D_81136988[];
void func_81112894(void*);
void func_811152A4(s32 arg0) {
    Chan811152A4* chan = (Chan811152A4*)&D_81184668[arg0];
    s32 i;

    func_81112E00((u8*)chan);
    chan->bit02 = 0;
    chan->unk10 = 0;
    chan->unk01 = 1;
    chan->unk12 = 0;
    chan->unk14 = 0;
    chan->unk0A = 0;
    chan->unk08 = 0x1680;
    chan->unk0C = 0;
    chan->unk0E = 0;
    chan->unk02 = 0;
    chan->unk90 = D_81136978;
    chan->unk94 = D_81136988;
    chan->unkDC = 0;
    chan->unk1C = 1.0f;
    chan->unk2C = 1.0f;
    chan->unk20 = 0.0f;
    chan->unk24 = 0.0f;
    chan->unk28 = 0.5f;
    for (i = 0; i < 16; i++) {
        func_81112894(chan->items[i]);
    }
}

typedef struct Rec8111539C {
    /* 0x00 */ char unk00[0x34];
    /* 0x34 */ Item8111539C* items[16];
    /* 0x74 */ char unk74[0xE8];
} Rec8111539C;
extern u8 D_811842C0[];
extern Item8111539C D_81184850;
void* func_811097E8(void*, s32);
void func_8111539C(s32 arg0) {
    Rec8111539C* rec = (Rec8111539C*)&D_81184668[arg0];
    s32 i;
    s32 j;
    Item8111539C* item;

    for (i = 0; i < 16; i++) {
        rec->items[i] = func_811097E8(D_811842C0, 0xD4);
        if (rec->items[i] == NULL) {
            rec->items[i] = &D_81184850;
        } else {
            item = rec->items[i];
            item->active = 0;
            item->owners[0] = rec;
            for (j = 0; j < 1; j++) {
                item->owners[j + 1] = NULL;
            }
        }
    }
}

typedef struct Emu81115480 {
    u8 b80 : 1;
    u8 rest : 7;
    char pad01[0x53];
    s32 unk54;
    char pad58[0x2C];
} Emu81115480; // size = 0x84
typedef struct Rec81115480 {
    u8 b80 : 1;
    u8 b40 : 1;
    u8 b20 : 1;
    u8 b10 : 1;
    u8 b08 : 1;
    u8 b04 : 1;
    u8 b02 : 1;
    u8 b01 : 1;
    u8 pad01[2];
    u8 unk03;
    char pad04[0x30];
    Item8111539C* items[16];
    char pad74[0x24];
    u8 unk98[0xBC];
    s8 unk154;
    char pad155[7];
} Rec81115480; // size = 0x15C
void func_811110E0(void*);
void func_81115480(void) {
    s32 i;
    s32 j;
    Rec81115480* rec;

    func_81112F2C();
    for (i = 0; i < 1; i++) {
        ((Emu81115480*)D_811847C8)[i].unk54 = 0;
        ((Emu81115480*)D_811847C8)[i].b80 = 0;
    }
    for (i = 0; i < 1; i++) {
        rec = (Rec81115480*)&D_81184668[i];
        for (j = 0; j < 16; j++) {
            rec->items[j] = &D_81184850;
        }
        rec->unk154 = -1;
        rec->unk03 = 0x60;
        rec->b80 = 0;
        rec->b20 = 0;
        rec->b08 = 0;
        rec->b10 = 0;
        func_811110E0(rec->unk98);
        func_811152A4(i);
    }
}

void func_811155A0(void) {
    func_812103F0_jp();
}

void GbApu_SetActiveFlag(void) {
    func_8121036C_jp(0xF1000000, 0);
    D_81138A70 = 1;
}

void GbApu_ClearActiveFlag(void) {
    func_8121036C_jp(0xF2000000, 0);
    D_81138A70 = 0;
}

void func_81215C14_jp(s32 arg0, s32 arg1, u8 arg2) {
    unk_D_81287B08_jp* ch = &D_81287B08_jp[arg0];
    f32 target;

    ch->unk_012 = 0;
    target = ((s32)arg2 / 100.0f) * ch->unk_01C;
    ch->unk_024 = ch->unk_01C;
    if (arg1 == 0) {
        ch->unk_01C = target;
        return;
    }
    ch->unk_001 = 0;
    ch->unk_012 = arg1;
    ch->unk_020 = (target - ch->unk_01C) / arg1;
}

void func_81215C9C_jp(s32 arg0, s32 arg1) {
    unk_D_81287B08_jp* ch = &D_81287B08_jp[arg0];

    ch->unk_012 = 0;
    if (arg1 == 0) {
        ch->unk_01C = ch->unk_024;
        return;
    }
    ch->unk_001 = 0;
    ch->unk_012 = arg1;
    ch->unk_020 = (ch->unk_024 - ch->unk_01C) / arg1;
}

void func_81115704(void) {
}

void func_81215D0C_jp(s32 arg0, s32 arg1, s32 arg2) {
    func_81210390_jp(((arg0 & 0xFF) << 16) | 0x08000000 | ((arg1 & 0xFF) << 8), arg2);
}

void func_81215D50_jp(void) {
    func_8121036C_jp(0x82020100, 0);
    func_812103F0_jp();
    func_8121036C_jp(0xF8000000, 0);
}

void func_81215D8C_jp(s32 arg0, s32 arg1, s32 arg2) {
    func_81210390_jp(0x06020002, arg1);
    func_81210390_jp(0x06020001, arg0);
    func_81210390_jp(0x06020000, arg2);
}

void func_81215DDC_jp(void) {
    func_81210390_jp(0x06020004, -1);
}

void GbApu_SetNoisePeriodBounds(s32 arg0, s32 arg1) {
    D_81138AD0 = arg0;
    D_81138AD4 = arg1;
}
