/* Stadium Zero fragment031_3553C0. */

#include "global.h"
#include "gfx_buffer.h"
#include "m2c_macros.h"

extern Gfx D_8F20E830[];
extern Gfx D_8F20E880[];
extern void* D_8F20E8A8[];
extern u16 D_80060484;

Gfx* func_8F200020(Gfx* gfx, s32 frame);

Gfx* func_8F200020(Gfx* gfx, s32 frame) {
    gSPDisplayList(gfx++, D_8F20E830);
    gDPLoadTextureBlock(gfx++, D_8F20E8A8[frame], G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0, G_TX_CLAMP, G_TX_CLAMP,
                        G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    gSPDisplayList(gfx++, D_8F20E880);
    gSPEndDisplayList(gfx++);
    return gfx;
}

void func_8F20010C(s32 arg0, s8* arg1) {
    if (arg0 == 2) {
        M2C_FIELD(arg1, Gfx**, 0x18) = Gfx_AllocDisplayList(0x50);
        func_8F200020(M2C_FIELD(arg1, Gfx**, 0x18), D_80060484 & 7);
    }
}
