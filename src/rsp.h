/* Declarations for src/rsp.c. */
#ifndef RSP_H
#define RSP_H

#include "global.h"
#include "PR/leo.h"

// A request for the storage thread (thread20_rsp), allocated by the Storage_Queue* functions in dma.c.
// It starts with the space of a LEOCmd, which the 64DD requests use (see StorageLeoRequest).
typedef struct StorageRequest {
    /* 0x00 */ u8 command; // @unverified: 0xF0/0xF1 ROM read, 0xF2/0xF3 SRAM read/write, else a LEO command (5 read, 6 write, 7 seek, ...)
    /* 0x01 */ char filler1[0x1B];
    /* 0x1C */ s32 devAddr; // @unverified: ROM or SRAM address, or 64DD LBA
    /* 0x20 */ void* dramAddr; // @unverified: passed as the DMA RAM address
    /* 0x24 */ s32 size; // @unverified: bytes, or the number of LBAs on the 64DD
    /* 0x28 */ s32 replyQueue; // @unverified: OSMesgQueue* that gets the result, or 0
} StorageRequest; // size = 0x2C

// The StorageRequest of the 64DD commands that take a LEOCmd.
typedef struct StorageLeoRequest {
    LEOCmd cmd;
    union {
        u32 lba;
        struct {
            char filler0[0x3];
            LEOSpdlMode mode;
        };
    };
    void *addr;
} StorageLeoRequest;

// The storage thread's queues (D_80087000), created in func_80000C14.
typedef struct StorageQueues {
    /* 0x00 */ OSMesg ioMesg; // @unverified: receives the PI DMA completion in Storage_ReadSram/Storage_ReadRom
    /* 0x04 */ OSMesgQueue piCmdQueue; // @unverified: the PI manager's command queue (osCreatePiManager in func_80000C14)
    /* 0x1C */ OSMesgQueue requestQueue; // @unverified: StorageRequest pointers for thread20_rsp (Storage_QueueRequest)
    /* 0x34 */ OSMesgQueue ioDoneQueue; // @unverified: PI and LEO completion messages
} StorageQueues; // size = 0x4C

// rsp.c
s32 Storage_InitializeLeoManager(void);
OSPiHandle *Storage_GetSramHandle(void);
s32 Storage_ReadSram(StorageRequest* arg0);
s32 Storage_WriteSram(StorageRequest* arg0);
s32 Storage_ReadRom(StorageRequest* arg0, s32 arg1);
void *Storage_WaitForIoMessage(void);
void *Storage_ReadDisk(StorageRequest* arg0);
void *Storage_WriteDisk(StorageRequest* arg0);
void *Storage_ReadDiskId(StorageLeoRequest* arg0);
void *Storage_SeekDisk(StorageLeoRequest* arg0);
void *Storage_SetDiskMotor(StorageLeoRequest* arg0);
void *Storage_ReadRtc(StorageLeoRequest* arg0);
void *Storage_WriteRtc(StorageLeoRequest* arg0);
void thread20_rsp(void *arg);
void Storage_ResetDisk(void);
void Storage_QueueRequest(void* arg0, s32 arg1);

#endif // RSP_H
