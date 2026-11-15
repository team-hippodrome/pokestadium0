/* Declarations for src/leo.c. */
#ifndef LEO_H
#define LEO_H

#include "global.h"

// The boot block of a 64DD disk (LBA 0x230), checked by Leo_AcceptPokemonDiskDescriptor.
typedef struct LeoBootDescriptor {
    /* 0x00 */ s32 magic; // @unverified: 'POKE' (Leo_AcceptPokemonDiskDescriptor)
    /* 0x04 */ u16 payloadLba; // @unverified: Leo_QueueDiskPayloadRead
    /* 0x06 */ u16 payloadLbaCount; // @unverified: Leo_QueueDiskPayloadRead
    /* 0x08 */ void* loadAddr; // @unverified: payload destination, then passed to LeoBootGame (game_state.c)
    /* 0x0C */ s32 unk_0C;
} LeoBootDescriptor; // size = 0x10

// The 64DD boot state machine (D_800AB210, Leo_RunBootStateMachine).
typedef struct LeoBootState {
    /* 0x00 */ u16 state; // @unverified: 0-10, the case of Leo_RunBootStateMachine
    /* 0x02 */ u16 errorKind; // @unverified: 0-5, set with leoError on a failed step
    /* 0x04 */ u16 leoError; // @unverified: the LEO error code that failed a step
    /* 0x06 */ u16 resetRetries; // @unverified: counts LEO error 43 in Leo_HandleDiskIdCompletion; errorKind 1 after 32
} LeoBootState; // size = 0x8

extern LeoBootDescriptor D_800AB200;

// leo.c
s32 Leo_ValidateBootDiskId(void);
s32 Leo_AcceptPokemonDiskDescriptor(LeoBootDescriptor* arg0);
s32 Leo_QueueDiskIdRead(void);
s32 Leo_QueueDiskReset(void);
s32 Leo_QueueBootBlockRead(LeoBootDescriptor* arg0);
s32 Leo_QueueDiskPayloadRead(void);
s32 Leo_HandleDiskIdCompletion(void);
s32 Leo_HandleResetCompletion(void);
s32 Leo_HandleBootBlockCompletion(LeoBootDescriptor* arg0);
s32 Leo_HandlePayloadCompletion(void);
s32 Leo_PollDiskReady(void);
void func_8000D0D4(void);
s32 Leo_RunBootStateMachine(LeoBootDescriptor* arg0);
s32 Leo_InitializeBootState(void);
void Leo_AbortPendingBootRequest(void);
void Leo_ResetBootStateIfReady(void);

#endif // LEO_H
