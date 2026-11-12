/* Fixed-layout split; original translation-unit boundaries remain unconfirmed. */
#include "gb_tower_emulator_86CB0.h"

s32 func_8110CA2C(s32);
s32 func_8110CA68(s32);
void func_8110CAE0(s32, s32);
void func_8110CB10(s32, s32);
u16 func_81112650(u8** stream, u8 kind);
s32 func_811126B8(void*, void*, s32, s32);
void func_81112BF0(s8* arg0, u16 mask);
void func_81112E00(u8* arg0);
typedef struct Item8111539C {
    /* 0x00 */ u32 active : 1;
    /* 0x00 */ u32 unk00 : 31;
    /* 0x04 */ char unk04[0x48];
    /* 0x4C */ void* owners[2];
} Item8111539C;
void func_81112B84(Item8111539C*);

typedef struct ScriptState81114B54 {
    /* 0x00 */ u8* pc;
    /* 0x04 */ u8* stack[4];
    /* 0x14 */ u8 remLoopIters[4];
    /* 0x18 */ u8 depth;
    /* 0x19 */ s8 value;
} ScriptState81114B54;

typedef struct Channel81114B54 {
    /* 0x00 */ u32 enabled : 1;
    /* 0x00 */ u32 finished : 1;
    /* 0x00 */ u32 rest : 30;
} Channel81114B54;

typedef struct SeqPlayer81114B54 {
    /* 0x00 */ u32 enabled : 1;
    /* 0x00 */ u32 finished : 1;
    /* 0x00 */ u32 muted : 1;
    /* 0x00 */ u32 seqDmaInProgress : 1;
    /* 0x00 */ u32 bankDmaInProgress : 1;
    /* 0x00 */ u32 recalculateVolume : 1;
    /* 0x00 */ u32 stopScript : 1;
    /* 0x00 */ u32 applyBend : 1;
    /* 0x01 */ u8 state;
    /* 0x02 */ u8 noteAllocPolicy;
    /* 0x03 */ u8 muteBehavior;
    /* 0x04 */ u8 seqId;
    /* 0x05 */ u8 defaultBank;
    /* 0x06 */ u8 unk06[2];
    /* 0x08 */ u16 tempo;
    /* 0x0A */ u16 tempoAcc;
    /* 0x0C */ s16 tempoChange;
    /* 0x0E */ s16 transposition;
    /* 0x10 */ u16 delay;
    /* 0x12 */ u16 fadeTimer;
    /* 0x14 */ u16 storedFadeTimer;
    /* 0x16 */ u8 unk16[2];
    /* 0x18 */ u8* seqData;
    /* 0x1C */ f32 fadeVolume;
    /* 0x20 */ f32 fadeVelocity;
    /* 0x24 */ f32 volume;
    /* 0x28 */ f32 muteVolumeScale;
    /* 0x2C */ f32 fadeVolumeScale;
    /* 0x30 */ f32 appliedFadeVolume;
    /* 0x34 */ Channel81114B54* channels[16];
    /* 0x74 */ ScriptState81114B54 scriptState;
    /* 0x90 */ u8* shortNoteVelocityTable;
    /* 0x94 */ u8* shortNoteDurationTable;
    /* 0x98 */ u8 notePool[0xDC - 0x98];
    /* 0xDC */ s32 scriptCounter;
    /* 0xE0 */ u8 unkE0[0x154 - 0xE0];
    /* 0x154 */ s8 soundScriptIO[8];
} SeqPlayer81114B54;

extern s16 D_811858EC;
void func_81111340(void*, s32);
void func_81113FA8(Channel81114B54*);

void func_81114B54(SeqPlayer81114B54* seqPlayer) {
    u8 cmd;
    u8 loBits;
    u16 temp;
    s32 value;
    s32 i;
    u8* data;
    ScriptState81114B54* state;
    UNUSED s32 pad[4]; // FAKE: stack pad of unknown origin; only reserves frame space

    if (!seqPlayer->enabled) {
        return;
    }
    if (!func_8110CA68(seqPlayer->seqId) || !func_8110CA2C(seqPlayer->defaultBank)) {
        func_81112E00((u8*)seqPlayer);
        return;
    }
    func_8110CB10(seqPlayer->seqId, 2);
    func_8110CAE0(seqPlayer->defaultBank, 2);

    if (seqPlayer->muted && (seqPlayer->muteBehavior & 0x80)) {
        return;
    }

    seqPlayer->scriptCounter++;
    seqPlayer->tempoAcc += seqPlayer->tempo;
    seqPlayer->tempoAcc += seqPlayer->tempoChange;
    if (seqPlayer->tempoAcc < D_811858EC) {
        return;
    }
    seqPlayer->tempoAcc -= (u16)D_811858EC;

    if (seqPlayer->stopScript == 1) {
        return;
    }

    state = &seqPlayer->scriptState;
    if (seqPlayer->delay > 1) {
        seqPlayer->delay--;
    } else {
        seqPlayer->recalculateVolume = 1;
        while (1) {
            cmd = func_81112FB0(&state->pc);
            if (cmd >= 0xF2) {
                value = func_811126B8(seqPlayer, state, cmd, func_81112650(&state->pc, cmd));
                if (value != 0) {
                    if (value == -1) {
                        func_81112E00((u8*)seqPlayer);
                    } else {
                        seqPlayer->delay = value;
                    }
                    break;
                }
            } else if (cmd >= 0xC0) {
                switch (cmd) {
                    case 0xF1:
                        func_811111E0((s8*)&seqPlayer->notePool);
                        func_81111340(&seqPlayer->notePool, func_81112FB0(&state->pc));
                        break;
                    case 0xF0:
                        func_811111E0((s8*)&seqPlayer->notePool);
                        break;
                    case 0xDF:
                        seqPlayer->transposition = 0;
                    case 0xDE:
                        seqPlayer->transposition += (s8)func_81112FB0(&state->pc);
                        break;
                    case 0xDD:
                        seqPlayer->tempo = func_81112FB0(&state->pc) * 48;
                        if (seqPlayer->tempo > D_811858EC) {
                            seqPlayer->tempo = (u16)D_811858EC;
                        }
                        if ((s16)seqPlayer->tempo <= 0) {
                            seqPlayer->tempo = 1;
                        }
                        break;
                    case 0xDC:
                        seqPlayer->tempoChange = (s8)func_81112FB0(&state->pc) * 48;
                        break;
                    case 0xDA:
                        cmd = func_81112FB0(&state->pc);
                        temp = func_81112FC4(&state->pc);
                        switch (cmd) {
                            case 0:
                            case 1:
                                if (seqPlayer->state != 2) {
                                    seqPlayer->storedFadeTimer = temp;
                                    seqPlayer->state = cmd;
                                }
                                break;
                            case 2:
                                seqPlayer->fadeTimer = temp;
                                seqPlayer->state = cmd;
                                seqPlayer->fadeVelocity = (0.0f - seqPlayer->fadeVolume) / (s32)seqPlayer->fadeTimer;
                                break;
                        }
                        break;
                    case 0xDB:
                        value = func_81112FB0(&state->pc);
                        switch (seqPlayer->state) {
                            case 1:
                                seqPlayer->state = 0;
                                seqPlayer->fadeVolume = 0.0f;
                            case 0:
                                seqPlayer->fadeTimer = seqPlayer->storedFadeTimer;
                                if (seqPlayer->storedFadeTimer != 0) {
                                    seqPlayer->fadeVelocity = ((value / 127.0f) - seqPlayer->fadeVolume) / (s32)seqPlayer->fadeTimer;
                                } else {
                                    seqPlayer->fadeVolume = value / 127.0f;
                                }
                                break;
                            case 2:
                                break;
                        }
                        break;
                    case 0xD9:
                        seqPlayer->fadeVolumeScale = (s8)func_81112FB0(&state->pc) / 127.0f;
                        break;
                    case 0xD7:
                        temp = func_81112FC4(&state->pc);
                        func_81112BF0((s8*)seqPlayer, temp);
                        break;
                    case 0xD6:
                        func_81112FC4(&state->pc);
                        break;
                    case 0xD5:
                        seqPlayer->muteVolumeScale = (s8)func_81112FB0(&state->pc) / 127.0f;
                        break;
                    case 0xD4:
                        seqPlayer->muted = 1;
                        break;
                    case 0xD3:
                        seqPlayer->muteBehavior = func_81112FB0(&state->pc);
                        break;
                    case 0xD1:
                    case 0xD2:
                        temp = func_81112FC4(&state->pc);
                        data = seqPlayer->seqData + temp;
                        if (cmd == 0xD2) {
                            seqPlayer->shortNoteVelocityTable = data;
                        } else {
                            seqPlayer->shortNoteDurationTable = data;
                        }
                        break;
                    case 0xD0:
                        seqPlayer->noteAllocPolicy = func_81112FB0(&state->pc);
                        break;
                    case 0xCC:
                        state->value = func_81112FB0(&state->pc);
                        break;
                    case 0xC9:
                        state->value &= func_81112FB0(&state->pc);
                        break;
                    case 0xC8:
                        state->value -= func_81112FB0(&state->pc);
                        break;
                    case 0xC7:
                        cmd = func_81112FB0(&state->pc);
                        temp = func_81112FC4(&state->pc);
                        data = seqPlayer->seqData + temp;
                        *data = (u8)state->value + cmd;
                        break;
                    case 0xC6:
                        seqPlayer->stopScript = 1;
                        return;
                    case 0xC5:
                        seqPlayer->scriptCounter = (u16)func_81112FC4(&state->pc);
                        break;
                }
            } else {
                loBits = cmd & 0xF;
                switch (cmd & 0xF0) {
                    case 0x00:
                        state->value = seqPlayer->channels[loBits]->finished;
                        break;
                    case 0x10:
                        break;
                    case 0x20:
                        break;
                    case 0x50:
                        state->value -= seqPlayer->soundScriptIO[loBits];
                        break;
                    case 0x70:
                        seqPlayer->soundScriptIO[loBits] = state->value;
                        break;
                    case 0x80:
                        state->value = seqPlayer->soundScriptIO[loBits];
                        if (loBits < 2) {
                            seqPlayer->soundScriptIO[loBits] = -1;
                        }
                        break;
                    case 0x40:
                        func_81112B84((Item8111539C*)seqPlayer->channels[loBits]);
                        break;
                    case 0x90:
                        temp = func_81112FC4(&state->pc);
                        func_81112D68((Particle2D68**)seqPlayer, loBits, (s32)(seqPlayer->seqData + temp));
                        break;
                    case 0x60:
                    case 0xA0:
                        break;
                }
            }
        }
    }

    for (i = 0; i < 16; i++) {
        if (seqPlayer->channels[i]->enabled) {
            func_81113FA8(seqPlayer->channels[i]);
        }
    }
}

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
  s8 *new_var; // FAKE: permuter temp
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

/**
 * No callers.
 * @unverified Name and comment from Stadium 1.
 */
void GbApu_SetNoiseLoopBounds(s32 arg0, s32 arg1) {
    D_81138AD0 = arg0;
    D_81138AD4 = arg1;
}
