/*
 * Stadium Zero fragment038_38A540: models of the Game Boy cartridge check scene (fragment006),
 * i.e. the P-OS terminal desk (geo layout D_8F4886F8) and the three per-cartridge models, plus
 * the anti-piracy check hidden in the terminal's switch-node callback.
 */

#include "global.h"
#include "m2c_macros.h"
#include "cartridge_check_models.h"
#include "PR/rcp.h"

/**
 * Anti-piracy check. With interrupts masked and the PI idle, reads the cartridge ROM word at
 * 0x504 (inside the IPL3 boot code) straight over the bus. A genuine boot code has
 * `lui at, 0xA460` there; if the low half is anything else, returns -1 instead of `value`.
 * Seen in play (2026-11-14): stubbing it to return -1 froze the cartridge check screen
 * (pressing A no longer reached the "P-OS version 1.0 NOW LOADING" screen).
 * Stadium 1's counterpart is Pak_CheckPiIntegrity.
 */
s32 CartridgeCheckModels_CheckBootCode(s32 value) {
    OSIntMask prevMask;

    prevMask = osSetIntMask(OS_IM_NONE);
    if (!(IO_READ(PI_STATUS_REG) & (PI_STATUS_DMA_BUSY | PI_STATUS_IO_BUSY)) &&
        ((IO_READ(PHYS_TO_K1(PI_DOM1_ADDR2) + 0x504) & 0xFFFF) != 0xA460)) {
        value = -1;
    }
    osSetIntMask(prevMask);
    return value;
}

extern DisplayObject* D_8006049C;

/**
 * Geo callback of the P-OS terminal's switch node (in D_8F4886F8). On traversal (context 2) it
 * selects the child given by the rendered display object's callbackArg: fragment006 sets it to 1
 * when the terminal appears. Play (2026-11-14): poking the object's callbackArg to 1 showed the
 * terminal desk, 0 and 2 showed nothing.
 * Before that, the node's child list goes through CartridgeCheckModels_CheckBootCode, so on a
 * copy with a foreign boot code the list becomes -1 and the game hangs walking it.
 */
void CartridgeCheckModels_GeoSwitchTerminal(s32 context, GeoSwitchCaseNode* node) {
    if (context == 2) {
        node->node.children = (struct CameraNode*)CartridgeCheckModels_CheckBootCode((s32)node->node.children);
        node->selectedChild = (s16) D_8006049C->node.callbackArg;
    }
}
