/* Declarations for src/audio_manager.c. */
#ifndef AUDIO_MANAGER_H
#define AUDIO_MANAGER_H

#include "global.h"

/* Struct types that were defined identically in each of these files; this is
 * now the one definition they all include:
 * src/33FE0.c
 * src/3D140.c
 * src/3D140_2.c
 */

typedef struct AMDMABuffer {
    /* 0x00 */ ALLink node;
    /* 0x08 */ u32 startAddr;
    /* 0x0C */ u32 lastFrame;
    /* 0x10 */ char* ptr;
} AMDMABuffer;

typedef struct AMDMAState {
    /* 0x00 */ u8 initialized;
    /* 0x04 */ AMDMABuffer* firstUsed;
    /* 0x08 */ AMDMABuffer* firstFree;
} AMDMAState;

typedef struct unk_D_80078548 {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 unk_01;
} unk_D_80078548;

typedef struct CachedMoveData {
    /* 0x00 */ u8 lastMove;
    /* 0x01 */ u8 effect;
    /* 0x02 */ u8 power;
    /* 0x03 */ u8 type;
    /* 0x04 */ u8 accuracy;
    /* 0x05 */ u8 pp;
} CachedMoveData; // size = 0x6

typedef struct BattleMonRuntime {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ char unk02[0x2];
    /* 0x04 */ u8 unk_04;
    /* 0x05 */ u8 unk_05;
    /* 0x06 */ char unk06[0x5];
    /* 0x0B */ u8 species; // national Pokédex number; Transform copies the target's
    /* 0x0C */ u16 hp; // the HP the HUD, the COM AI and fainting follow
    /* 0x0E */ u16 hpAfterPoisonBurn; // HP once this turn's poison or burn damage is taken
    /* 0x10 */ u16 hpAfterLeechSeed; // the user's HP after the drain, the target's after the heal; 900 when none is pending
    /* 0x12 */ u16 pendingHp; // HP while damage is worked out; 0xFFFF between turns
    /* 0x14 */ u8 rosterIndex; // copy of ActivePokemonState.rosterIndex
    /* 0x15 */ u8 pendingStatusCondition;
    /* 0x16 */ u8 restSleepTurns[6]; // per brought Pokémon (rosterIndex + teamMemberIndex * 3): sleep turns left from Rest, which sets 2
    /* 0x1C */ u8 type1;
    /* 0x1D */ u8 type2;
    /* 0x1E */ u8 catchRate; // copied from BattleMon.catchRate
    /* 0x1F */ u8 moves[4];
    /* 0x23 */ char unk23[0x1];
    /* 0x24 */ u16 dvs; // Gen 1 DVs (IVs), copied from BattleMon.dvs; Transform copies the target's
    /* 0x26 */ u8 level;
    /* 0x28 */ u16 maxHp;
    /* 0x2A */ u16 modifiedAttack;
    /* 0x2C */ u16 modifiedDefense;
    /* 0x2E */ u16 speed;
    /* 0x30 */ u16 modifiedSpecial;
    /* 0x32 */ u8 pp[4];
    /* 0x36 */ u16 baseHp; // gBaseStats[species].baseHP
    /* 0x38 */ u16 unmodifiedAttack;
    /* 0x3A */ u16 unmodifiedDefense;
    /* 0x3C */ u16 unmodifiedSpeed;
    /* 0x3E */ u16 unmodifiedSpecial;
    /* 0x40 */ char unk40[0x4];
    /* 0x44 */ CachedMoveData moveCache;
    /* 0x4A */ u8 unk_4A;
    /* 0x4B */ u8 unk_4B;
    /* 0x4C */ u8 immobilizedReason;
    /* 0x4D */ u8 volatileStatusFlags;
    /* 0x4E */ u8 uniqueStatusFlags;
    /* 0x4F */ u8 effectTurnsLeft;
    /* 0x50 */ u8 confusionTurnsLeft;
    /* 0x51 */ u8 toxicCounter;
    /* 0x52 */ u8 disabledMoveState;
    /* 0x53 */ u8 unk_53;
    /* 0x54 */ u16 effectCounter;
    /* 0x56 */ u8 scaleResize;
    /* 0x57 */ u8 disabledMove;
    /* 0x58 */ u8 lastMove;
    /* 0x59 */ u8 substituteHp;
    /* 0x5A */ u8 usedMove;
    /* 0x5B */ u8 receivedCritFlag; // the last hit taken: 1 critical hit, 2 one-hit KO
    /* 0x5C */ u8 statStages[8]; // 1-13, 7 is neutral: Attack, Defense, Speed, Special, accuracy, evasion; the last 2 are never used
} BattleMonRuntime; // size = 0x64

typedef struct amConfig {
    /* 0x00 */ u32 outputRate;
    /* 0x04 */ u32 framesPerField;
    /* 0x08 */ u32 maxACMDSize;
} amConfig; // size = 0xC

extern s32 mus_active_fade_handle;

extern f32 mus_fade_start_volume;

extern u8 mus_fade_target_volume;

extern f32 mus_fade_step_rate;

extern u8 mus_sound_effect_blocked;

// audio_manager.c
void amCreateAudioMgr(ALSynConfig* c, amConfig* amc, u32 num_dma_buffers, s32 arg3, s32 arg4);
void __clearAudioDMA(void);
void Cry_PlayFromPokedex(s32);
s32 Cry_IsPlaying(void);
s32 Audio_SetEnabled(s32);

// functions defined in assembly
OSTask* Audio_CreateFrameTask(OSTask*);
void AudioFrameUpdate(s32 arg0);

#endif // AUDIO_MANAGER_H
