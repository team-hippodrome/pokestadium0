/* Stadium Zero resident code. */
/* C ported from the Stadium 1 decomp: src/leo.c. */

#include "leo.h"
#include "dma.h"
#include "PR/leo.h"
extern LeoBootDescriptor D_800AB200;
extern LeoBootState D_800AB210;
extern OSMesgQueue D_800AB218;
extern OSMesg D_800AB230;

#include "m2c_macros.h"

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

s32 Leo_ValidateBootDiskId(void);

s32 func_80057910(M2C_UNK *, M2C_UNK *, M2C_UNK);   /* extern */
M2C_UNK func_80058410(M2C_UNK *, M2C_UNK *, M2C_UNK); /* extern */
extern M2C_UNK D_800001A0;
extern u32 D_80000318;
extern M2C_UNK D_80060400;
extern M2C_UNK D_80060404;
extern M2C_UNK D_80084D11;
extern M2C_UNK D_80084D28;

/**
 * Not reached in play (2026-11-13): did not run in a tour of the main menu, Pokédex, party, Lab,
 * registration, Free Battle setup and a COM battle (opening, a switch, running, a Pound turn).
 * @unverified Name was previously used only by callers of this address; the definition was still func_.
 */
s32 Leo_ValidateBootDiskId(void) {
    if ((u32) D_80000318 < 0x800000U) {
        return 2;
    }
    if (func_80057910(&D_80084D28, &D_80060404, 2) != 0) {
        return 1;
    }
    if (func_80057910(&D_80084D11, &D_80060400, 3) != 0) {
        return 1;
    }
    if ((s32) D_80084D10.gameName[0] < 0x45) {
        return 1;
    }
    if ((s32) D_80084D10.gameName[0] >= 0x5B) {
        return 1;
    }
    if (D_80084D10.diskNumber != 1) {
        return 1;
    }
    func_80058410(&D_80084D10, &D_800001A0, 0x20);
    return 0;
}

/** Returns whether a disk's boot descriptor identifies a Pokemon disk. */
s32 Leo_AcceptPokemonDiskDescriptor(LeoBootDescriptor* arg0) {
    s32 var_v1 = 0;

    if (arg0->magic == 'POKE') {
        var_v1 = 1;
        D_800AB200 = *arg0;
    }

    return var_v1;
}

/** Queues a read of the disk ID and advances the boot state. */
s32 Leo_QueueDiskIdRead(void) {
    Storage_QueueDiskIdRead(&D_800AB218, 0);
    D_800AB210.state = 3;
    return 0;
}

/** Queues a disk reset and advances the boot state. */
s32 Leo_QueueDiskReset(void) {
    Storage_QueueDiskReset(&D_800AB218, 0);
    D_800AB210.state = 5;
    return 0;
}

/** Queues a read of the disk boot block. */
s32 Leo_QueueBootBlockRead(LeoBootDescriptor* arg0) {
    Storage_QueueDiskTransfer(0, arg0, 0x230, 1, &D_800AB218, 1);
    D_800AB210.leoError = 0;
    D_800AB210.errorKind = 0;
    D_800AB210.state = 7;
    return 0;
}

/** Queues a read of the disk payload. */
s32 Leo_QueueDiskPayloadRead(void) {
    Storage_QueueDiskTransfer(0, D_800AB200.loadAddr, D_800AB200.payloadLba, D_800AB200.payloadLbaCount, &D_800AB218, 1);
    D_800AB210.leoError = 0;
    D_800AB210.errorKind = 0;
    D_800AB210.state = 9;
    return 0;
}

/** Handles completion of the disk ID read. */
s32 Leo_HandleDiskIdCompletion(void) {
    s32 sp1C;

    if (osRecvMesg(&D_800AB218, &sp1C, 0) != -1) {
        switch (sp1C) {
            case 0:
                switch (Leo_ValidateBootDiskId()) {
                    case 0:
                        D_800AB210.leoError = sp1C;
                        D_800AB210.errorKind = 0;
                        D_800AB210.state = 6;
                        break;

                    case 1:
                        D_800AB210.leoError = sp1C;
                        D_800AB210.errorKind = 5;
                        D_800AB210.state = 4;
                        break;

                    case 2:
                        D_800AB210.errorKind = 4;
                        D_800AB210.state = 4;
                        D_800AB210.leoError = 0x2C;
                        break;
                }
                break;

            case 42:
                D_800AB210.state = 2;
                break;

            case 35:
                D_800AB210.state = 2;
                break;

            case 49:
                D_800AB210.leoError = sp1C;
                D_800AB210.errorKind = 2;
                D_800AB210.state = 2;
                break;

            case 2:
                D_800AB210.leoError = sp1C;
                D_800AB210.errorKind = 3;
                D_800AB210.state = 4;
                break;

            case 11:
                D_800AB210.leoError = sp1C;
                D_800AB210.errorKind = 1;
                D_800AB210.state = 4;
                break;

            case 34:
                D_800AB210.leoError = sp1C;
                D_800AB210.errorKind = 1;
                D_800AB210.state = 4;
                break;

            case 43:
                if (D_800AB210.resetRetries++ >= 0x1F) {
                    D_800AB210.errorKind = 1;
                }
                LeoResetClear();
                D_800AB210.state = 2;
                break;

            default:
                D_800AB210.leoError = sp1C;
                D_800AB210.errorKind = 1;
                D_800AB210.state = 4;
                break;
        }

        return 1;
    }

    return 0;
}

/** Handles completion of the disk reset. */
s32 Leo_HandleResetCompletion(void) {
    s32 sp1C;

    if (osRecvMesg(&D_800AB218, &sp1C, 0) != -1) {
        switch (sp1C) {
            default:
                D_800AB210.errorKind = 1;
                D_800AB210.state = 1;
                D_800AB210.leoError = sp1C;
                break;

            case 0:
                D_800AB210.state = 4;
                break;

            case 35:
                D_800AB210.state = 4;
                break;

            case 2:
                D_800AB210.state = 4;
                break;

            case 42:
                D_800AB210.leoError = 0;
                D_800AB210.errorKind = 0;
                D_800AB210.state = 2;
                break;

            case 47:
                D_800AB210.leoError = 0;
                D_800AB210.errorKind = 0;
                D_800AB210.state = 2;
                break;

            case 34:
                D_800AB210.leoError = sp1C;
                D_800AB210.errorKind = 1;
                D_800AB210.state = 1;
                break;
        }
        return 1;
    }

    return 0;
}

/** Handles completion of the boot block read and validates the disk. */
s32 Leo_HandleBootBlockCompletion(LeoBootDescriptor* arg0) {
    s32 sp24;
    UNUSED s32 pad; // FAKE: stack padding

    if (osRecvMesg(&D_800AB218, &sp24, 0) != -1) {
        switch (sp24) {
            case 0:
                if (Leo_AcceptPokemonDiskDescriptor(arg0) != 0) {
                    D_800AB210.state = 8;
                } else {
                    D_800AB210.errorKind = 5;
                    D_800AB210.state = 4;
                }
                break;

            case 0x23:
                D_800AB210.state = 8;
                break;

            case 0x2A:
                D_800AB210.state = 2;
                break;

            case 0x2F:
                D_800AB210.state = 2;
                break;

            case 0x31:
                D_800AB210.leoError = sp24;
                D_800AB210.errorKind = 2;
                D_800AB210.state = 2;
                break;

            case 2:
                D_800AB210.leoError = sp24;
                D_800AB210.errorKind = 3;
                D_800AB210.state = 4;
                break;

            case 0x22:
                D_800AB210.leoError = sp24;
                D_800AB210.errorKind = 1;
                D_800AB210.state = 4;
                break;

            default:
                D_800AB210.leoError = sp24;
                D_800AB210.errorKind = 1;
                D_800AB210.state = 4;
                break;
        }
        return 1;
    }

    return 0;
}

/** Handles completion of the payload read. */
s32 Leo_HandlePayloadCompletion(void) {
    s32 sp1C;

    if (osRecvMesg(&D_800AB218, &sp1C, 0) != -1) {
        switch (sp1C) {
            case 0:
                D_800AB210.state = 0xA;
                break;

            case 0x23:
                D_800AB210.state = 8;
                break;

            case 0x2A:
                D_800AB210.state = 2;
                break;

            case 0x2F:
                D_800AB210.state = 2;
                break;

            case 0x31:
                D_800AB210.leoError = sp1C;
                D_800AB210.errorKind = 2;
                D_800AB210.state = 2;
                break;

            case 2:
                D_800AB210.leoError = sp1C;
                D_800AB210.errorKind = 3;
                D_800AB210.state = 4;
                break;

            case 0x22:
                D_800AB210.leoError = sp1C;
                D_800AB210.errorKind = 1;
                D_800AB210.state = 4;
                break;

            default:
                D_800AB210.leoError = sp1C;
                D_800AB210.errorKind = 1;
                D_800AB210.state = 4;
                break;
        }
        return 1;
    }

    return 0;
}

/** Polls whether the disk drive is ready. */
s32 Leo_PollDiskReady(void) {
    UNUSED s32 pad; // FAKE: stack padding
    u8 sp23;
    s32 temp_v0 = LeoTestUnitReady(&sp23);

    switch (temp_v0) {
        case 0:
        case 8:
        case 35:
            break;

        default:
            D_800AB210.leoError = temp_v0;
            D_800AB210.errorKind = 1;
            break;

        case 42:
            D_800AB210.leoError = 0;
            D_800AB210.errorKind = 0;
            D_800AB210.state = 2;
            break;

        case 47:
            D_800AB210.leoError = 0;
            D_800AB210.errorKind = 0;
            D_800AB210.state = 2;
            break;
    }
    return 0;
}

void func_8000D0D4(void) {
}

/** Advances the disk boot state machine by one step. */
s32 Leo_RunBootStateMachine(LeoBootDescriptor* arg0) {
    s32 sp24 = 1;

    if (Storage_GetDiskStatus() != 0) {
        while (sp24 != 0) {
            switch (D_800AB210.state) {
                case 0:
                    sp24 = 0;
                    break;

                case 1:
                    sp24 = Leo_PollDiskReady();
                    break;

                case 2:
                    sp24 = Leo_QueueDiskIdRead();
                    break;

                case 3:
                    sp24 = Leo_HandleDiskIdCompletion();
                    break;

                case 4:
                    sp24 = Leo_QueueDiskReset();
                    break;

                case 5:
                    sp24 = Leo_HandleResetCompletion();
                    break;

                case 6:
                    sp24 = Leo_QueueBootBlockRead(arg0);
                    break;

                case 7:
                    sp24 = Leo_HandleBootBlockCompletion(arg0);
                    break;

                case 8:
                    sp24 = Leo_QueueDiskPayloadRead();
                    break;

                case 9:
                    sp24 = Leo_HandlePayloadCompletion();
                    break;

                case 10:
                    sp24 = 0;
                    break;
            }
        }
    }

    return (D_800AB210.state << 0x10) | (D_800AB210.errorKind << 8) | D_800AB210.leoError;
}

/** Sets the initial disk boot state from the drive status. */
s32 Leo_InitializeBootState(void) {
    s32 sp1C = Storage_GetDiskStatus();

    if (sp1C != 0) {
        D_800AB210.state = 2;
    } else {
        D_800AB210.state = 0;
    }

    D_800AB210.leoError = 0;
    D_800AB210.errorKind = 0;
    D_800AB210.resetRetries = 0;

    osCreateMesgQueue(&D_800AB218, &D_800AB230, 1);
    return sp1C;
}

/** Cancels the boot request that is in flight. */
void Leo_AbortPendingBootRequest(void) {
    s32 tmp = D_800AB210.state;

    if (tmp == 3) {
        osRecvMesg(&D_800AB218, NULL, 1);
        D_800AB210.state = 2;
    } else {
        switch (tmp) {
            case 5:
            case 7:
            case 9:
                osRecvMesg(&D_800AB218, NULL, 1);
                D_800AB210.state = 4;
                break;
        }
    }
}

/** Resets the boot state when the drive is ready. */
void Leo_ResetBootStateIfReady(void) {
    if (Storage_GetDiskStatus() != 0) {
        D_800AB210.state = 2;
        D_800AB210.leoError = 0;
        D_800AB210.errorKind = 0;
    }
}
