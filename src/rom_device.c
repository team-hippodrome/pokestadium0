/* Stadium Zero resident code. */
/* C ported from the Stadium 1 decomp: src/rom_device.c. */

#include "rom_device.h"
extern OSMesgQueue D_80100170;
extern OSPiHandle* D_80100188;

void Rom_DmaRead(u32 dev_addr, u32 dram_addr, u32 size);

extern OSMesg D_8010018C;
/**
 * Seen in play (2026-11-13) ran at boot (console reset, then N64 logo, opening, title and main
 * menu).
 * @unverified Name was previously used only by callers of this address; the definition was still func_.
 */
void Rom_InitDevice(s32 arg0) {
    if (arg0 == 1) {
        D_80100188 = osDriveRomInit();
    } else {
        D_80100188 = osCartRomInit();
    }

    osCreateMesgQueue(&D_80100170, &D_8010018C, 1);
}

/** Reads from a device address into memory with DMA and waits for completion. */
void Rom_DmaRead(u32 dev_addr, u32 dram_addr, u32 size) {
    OSIoMesg msg;
    u32 dev = dev_addr;
    u32 dram = dram_addr;
    s32 var_s0;

    while (size != 0) {
        if (size > 0x4000) {
            var_s0 = 0x4000;
        } else {
            var_s0 = size;
        }

        msg.hdr.pri = 0;
        msg.hdr.retQueue = &D_80100170;
        msg.dramAddr = dram;
        msg.devAddr = dev;
        msg.size = var_s0;

        osInvalDCache(msg.dramAddr, var_s0);
        osEPiStartDma(D_80100188, &msg, 0);
        osRecvMesg(&D_80100170, NULL, 1);

        dev += var_s0;
        dram += var_s0;
        size -= var_s0;
    }
}

void func_800374E0(s32, s32);

/** Sets the volume of an audio channel. */
void Audio_SetChannelVolume(s32 arg0, u32 arg1) {
    s32 var_a1;

    switch (arg1) {
        case 0:
            var_a1 = 0;
            break;
        case 1:
            var_a1 = 0x3FFF;
            break;
        case 2:
            var_a1 = 0x4FFF;
            break;
        case 3:
            var_a1 = 0x5FFF;
            break;
        case 4:
            var_a1 = 0x6FFF;
            break;
        case 5:
            var_a1 = 0x7FFF;
            break;
        default:
            var_a1 = 0x6FFF;
            break;
    }
    func_800374E0(arg0, var_a1);
}
