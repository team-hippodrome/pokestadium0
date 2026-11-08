/* Fixed-layout split; original translation-unit boundaries remain unconfirmed. */
#include "gb_tower_emulator_86CB0.h"

typedef struct AudioStreamFlags {
    u8 pad0 : 4;
    u8 active : 1;
    u8 pad1 : 3;
} AudioStreamFlags;

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
