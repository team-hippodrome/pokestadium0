/* Stadium Zero resident code. */
/* C ported from the Stadium 1 decomp: src/dma.c. */

#include "global.h"
#include "dma.h"
#include "rsp.h"
extern s16 D_8008704C;

s32 Storage_QueueRomRead(s32 arg0, void* arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
s32 Storage_QueueSramTransfer(s32 arg0, void* arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
s32 Storage_QueueDiskTransfer(s32 arg0, void* arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
s32 Storage_QueueDiskIdRead(s32 arg0, s32 arg1);
s32 Storage_QueueDiskSeek(s32 arg0, s32 arg1, s32 arg2);
s32 Storage_QueueDiskMotorOff(s32 arg0, s32 arg1);
s32 Storage_QueueDiskReset(s32 arg0, s32 arg1);
s32 Storage_QueueRtcWrite(void* arg0, s32 arg1, s32 arg2);
s16 Storage_GetDiskStatus(void);
s32 Storage_QueueRtcRead(void* arg0, s32 arg1, s32 arg2);

/** Queues a ROM read request for the storage thread. */
s32 Storage_QueueRomRead(s32 arg0, void* arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    struct UnkStruct80000E80* temp_v0;

    temp_v0 = Util_Malloc(0x2C);
    if (temp_v0 != NULL) {
        if (arg0 == 0) {
            temp_v0->unk0 = 0xF0;
        } else {
            temp_v0->unk0 = 0xF1;
        }
        temp_v0->unk1C = arg2;
        temp_v0->unk24 = arg3;
        temp_v0->unk20 = arg1;
        temp_v0->unk28 = arg4;
        Storage_QueueRequest(temp_v0, arg5);
    }
    return temp_v0 == NULL;
}

/** Queues an SRAM read or write request for the storage thread. */
s32 Storage_QueueSramTransfer(s32 arg0, void* arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    struct UnkStruct80000E80* temp_v0;

    temp_v0 = Util_Malloc(0x2C);
    if (temp_v0 != NULL) {
        if (arg0 == 0) {
            temp_v0->unk0 = 0xF2;
        } else {
            temp_v0->unk0 = 0xF3;
        }
        temp_v0->unk1C = arg2;
        temp_v0->unk24 = arg3;
        temp_v0->unk20 = arg1;
        temp_v0->unk28 = arg4;
        Storage_QueueRequest(temp_v0, arg5);
    }
    return temp_v0 == NULL;
}

/** Queues a 64DD disk read or write request for the storage thread. */
s32 Storage_QueueDiskTransfer(s32 arg0, void* arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    struct UnkStruct80000E80* temp_v0;

    temp_v0 = Util_Malloc(0x2C);
    if (temp_v0 != NULL) {
        if (arg0 == 0) {
            temp_v0->unk0 = 5;
        } else {
            temp_v0->unk0 = 6;
        }
        temp_v0->unk1C = arg2;
        temp_v0->unk24 = arg3;
        temp_v0->unk20 = arg1;
        temp_v0->unk28 = arg4;
        Storage_QueueRequest(temp_v0, arg5);
    }
    return temp_v0 == NULL;
}

/** Queues a 64DD disk ID read request. */
s32 Storage_QueueDiskIdRead(s32 arg0, s32 arg1) {
    struct UnkStruct80000E80* temp_v0;

    temp_v0 = Util_Malloc(0x2C);
    if (temp_v0 != NULL) {
        temp_v0->unk0 = 0xC;
        temp_v0->unk20 = &D_80084D10;
        temp_v0->unk28 = arg0;
        Storage_QueueRequest(temp_v0, arg1);
    }
    return temp_v0 == NULL;
}

/** Queues a 64DD seek request. */
s32 Storage_QueueDiskSeek(s32 arg0, s32 arg1, s32 arg2) {
    struct UnkStruct80000E80* temp_v0;

    temp_v0 = Util_Malloc(0x2C);
    if (temp_v0 != NULL) {
        temp_v0->unk0 = 7;
        temp_v0->unk1C = arg0;
        temp_v0->unk28 = arg1;
        Storage_QueueRequest(temp_v0, arg2);
    }
    return temp_v0 == NULL;
}

/** Queues a request to stop the 64DD spindle motor. */
s32 Storage_QueueDiskMotorOff(s32 arg0, s32 arg1) {
    struct UnkStruct80000E80* temp_v0;

    temp_v0 = Util_Malloc(0x2C);
    if (temp_v0 != NULL) {
        temp_v0->unk0 = 8;
        temp_v0->unk1C = 0;
        temp_v0->unk28 = arg0;
        Storage_QueueRequest(temp_v0, arg1);
    }
    return temp_v0 == NULL;
}

/** Queues a 64DD reset request. */
s32 Storage_QueueDiskReset(s32 arg0, s32 arg1) {
    struct UnkStruct80000E80* temp_v0;

    temp_v0 = Util_Malloc(0x2C);
    if (temp_v0 != NULL) {
        temp_v0->unk0 = 8;
        temp_v0->unk1C = 4;
        temp_v0->unk28 = arg0;
        Storage_QueueRequest(temp_v0, arg1);
    }
    return temp_v0 == NULL;
}

/** Queues a request to set the 64DD real-time clock. */
s32 Storage_QueueRtcWrite(void* arg0, s32 arg1, s32 arg2) {
    struct UnkStruct80000E80* temp_v0;

    temp_v0 = Util_Malloc(0x2C);
    if (temp_v0 != NULL) {
        temp_v0->unk0 = 0xE;
        temp_v0->unk20 = arg0;
        temp_v0->unk28 = arg1;
        Storage_QueueRequest(temp_v0, arg2);
    }
    return temp_v0 == NULL;
}

/** Returns the 64DD drive status. */
s16 Storage_GetDiskStatus(void) {
    return D_8008704C;
}

/** Queues a request to read the 64DD real-time clock. */
s32 Storage_QueueRtcRead(void* arg0, s32 arg1, s32 arg2) {
    struct UnkStruct80000E80* temp_v0;

    temp_v0 = Util_Malloc(0x2C);
    if (temp_v0 != NULL) {
        temp_v0->unk0 = 0xD;
        temp_v0->unk20 = arg0;
        temp_v0->unk28 = arg1;
        Storage_QueueRequest(temp_v0, arg2);
    }
    return temp_v0 == NULL;
}
