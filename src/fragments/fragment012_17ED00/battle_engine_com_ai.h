#ifndef BATTLE_ENGINE_COM_AI_H
#define BATTLE_ENGINE_COM_AI_H

#include "global.h"

/*
 * BattleSlotZ is a 0x90-byte view of the AI's side model (D_821CF618 /
 * D_821CF998) shifted by four bytes: each side is a party pointer followed by
 * six 0x90-byte battler records, and D_821CF29C / D_821CF2A0 point at a
 * record (slot + 4). In record terms the battle Pokemon (BattleMonRuntime,
 * 0x64 bytes) starts at +0xC; see docs/annotation/com-ai.md.
 */
typedef struct BattleSlotZ {
    /* 0x00 */ TeamRoster* roster;
    /* 0x04 */ u8 pad04[4];
    /* 0x08 */ s32 pickScore;
    /* 0x0C */ f32 matchupRatio;
    /* 0x10 */ u8 pad10[0xB];
    /* 0x1B */ u8 species;
    /* 0x1C */ u16 hp;
    /* 0x1E */ u8 pad1E[7];
    /* 0x25 */ u8 status;
    /* 0x26 */ u8 pad26[6];
    /* 0x2C */ u8 type1;
    /* 0x2D */ u8 type2;
    /* 0x2E */ u8 pad2E[8];
    /* 0x36 */ u8 level;
    /* 0x37 */ u8 pad37[0x27];
    /* 0x5E */ u8 unk_5E;
    /* 0x5F */ u8 pad5F[0x20];
    /* 0x7F */ u8 unk_7F;
    /* 0x80 */ u8 pad80[0x10];
} BattleSlotZ; // size = 0x90

#endif /* BATTLE_ENGINE_COM_AI_H */
