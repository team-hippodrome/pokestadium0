/* Stadium Zero resident code. */
/* C ported from the Stadium 1 decomp: src/libleo/cjcreateleomanager.c (libleo, built at -O2). */

/*
 * This libleo module calls __osSetHWIntrRoutine with two arguments, as the
 * libultra headers before 2.0I-P declare it.
 */
#undef BUILD_VERSION
#define BUILD_VERSION 6 /* VERSION_I */
#include "global.h"

#include "libleo/internal.h"
OSPiHandle* osLeoDiskInit(void);
OSPiHandle* osDriveRomInit(void);
s32 __osLeoInterrupt(void);
void leoInitialize(OSPri compri, OSPri intpri, OSMesg* command_que_buf, u32 cmd_buff_size);
void leoCommand(void* cmd_blk_addr);

s32 LeoCJCreateLeoManager(OSPri comPri, OSPri intPri, OSMesg* cmdBuf, s32 cmdMsgCnt) {
    OSPiHandle* driveRomHandle;
    OSPiHandle* leoDiskHandle;
    volatile LEOCmdInquiry cmdBlockInq;
    UNUSED volatile LEOCmd cmdBlockID;
    UNUSED LEODiskID thisID;
    u32 stat;
    u32 data;

    if (__leoActive) {
        return LEO_ERROR_GOOD;
    }

    leoDiskHandle = osLeoDiskInit();
    driveRomHandle = osDriveRomInit();
    osEPiReadIo(leoDiskHandle, 0x05000508, &data);
    if (data & 0xFFFF) {
        return LEO_ERROR_DEVICE_COMMUNICATION_FAILURE;
    }
    __leoActive = 1;

    __osSetHWIntrRoutine(1, __osLeoInterrupt);
    leoInitialize(comPri, intPri, cmdBuf, cmdMsgCnt);

    if (osResetType == 1) {
        __leoSetReset();
    }

    cmdBlockInq.header.command = 2;
    cmdBlockInq.header.reserve1 = 0;
    cmdBlockInq.header.control = 0;
    cmdBlockInq.header.reserve3 = 0;
    leoCommand((void*)&cmdBlockInq);

    {
        volatile s32 dummy = (u32)&cmdBlockInq & 0xFFFFFF;

        while (dummy > 0) {
            dummy -= ((u32)__leoSetReset & 0xFFFFFF) | 0x403DF4;
        }
    }

    while (cmdBlockInq.header.status == 8) {
        ;
    }

    if (cmdBlockInq.header.status != 0) {
        return cmdBlockInq.header.sense;
    }

    __leoVersion.driver = cmdBlockInq.version;
    __leoVersion.drive = 5;
    __leoVersion.deviceType = cmdBlockInq.dev_type;
    __leoVersion.ndevices = cmdBlockInq.dev_num;

    stat = __leoVersion.driver & 0xF;
    if (stat == 4) {
        LEO_country_code = 0;
    } else if ((stat == 3) || (stat == 1)) {
        volatile u32 dummy;

        osEPiReadIo(driveRomHandle, 0x9FF00, &data);
        data = ((data & 0xFF000000) >> 0x18);
        dummy = 0x3ED98F23;
        if (data != 0xC3) {
            while (1) {}
        }

        dummy *= data;
        dummy -= (u32)&cmdBlockInq;
        LEO_country_code = 0xE848D316;
    } else {
        while (1) {}
    }

    return LEO_ERROR_GOOD;
}
