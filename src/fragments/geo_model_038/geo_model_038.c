/* Stadium Zero fragment038_38A540. */

#include "global.h"
#include "m2c_macros.h"
#include "geo_model_038.h"

s32 func_8004D300(s32);                             /* extern */
s32 func_8F400020(s32 arg0) {
    s32 temp_a0;

    temp_a0 = func_8004D300(1);
    if (!((*(volatile s32 *)0xA4600010) & 3) && (((*(volatile s32 *)0xB0000504) & 0xFFFF) != 0xA460)) {
        arg0 = -1;
    }
    func_8004D300(temp_a0);
    return arg0;
}

s32 func_8F400020(s32);                             /* extern */
extern DisplayObject* D_8006049C;

void func_8F400088(s32 arg0, GeoSwitchCaseNode* arg1) {
    if (arg0 == 2) {
        // Without the expected cartridge bus response the child list becomes -1 (@unverified: looks like a copy protection check).
        arg1->node.children = (struct CameraNode*)func_8F400020((s32)arg1->node.children);
        arg1->selectedChild = (s16) D_8006049C->node.callbackArg;
    }
}
