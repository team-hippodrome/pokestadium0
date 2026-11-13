/* Stadium Zero fragment030_326700. */

#include "global.h"
#include "gfx_buffer.h"
#include "m2c_macros.h"

extern s32 D_8F100250;
extern s32 D_8F100254;
extern s32 D_8F100258;
extern s32 D_8F10025C;
extern Gfx D_8F1549C0[];
extern Gfx D_8F154A60[];
extern Gfx D_8F155550[];
extern Gfx D_8F1555B8[];

Gfx* func_8F100020(Gfx* gfx);
Gfx* func_8F100154(Gfx* gfx);

Gfx* func_8F100020(Gfx* gfx) {
    if (++D_8F100250 >= 0x80) {
        D_8F100250 = 0;
    }
    if (++D_8F100254 >= 0x80) {
        D_8F100254 = 0;
    }
    gSPDisplayList(gfx++, D_8F1549C0);
    gDPSetTileSize(gfx++, G_TX_RENDERTILE, D_8F100250, D_8F100254, D_8F100250 + 0x7C, D_8F100254 + 0x7C);
    gDPSetTileSize(gfx++, 1, D_8F100250, 0, D_8F100250 + 0x7C, 0x7C);
    gSPBranchList(gfx++, D_8F154A60);
    return gfx;
}

void func_8F100118(s32 arg0, s8* arg1) {
    if (arg0 == 2) {
        M2C_FIELD(arg1, Gfx**, 0x18) = Gfx_AllocDisplayList(0x20);
        func_8F100020(M2C_FIELD(arg1, Gfx**, 0x18));
    }
}

Gfx* func_8F100154(Gfx* gfx) {
    D_8F100258 -= 2;
    if (D_8F100258 < 0) {
        D_8F100258 = 0xFF;
    }
    if (++D_8F10025C >= 0x80) {
        D_8F10025C = 0;
    }
    gSPDisplayList(gfx++, D_8F155550);
    gDPSetTileSize(gfx++, G_TX_RENDERTILE, D_8F100258, D_8F10025C, D_8F100258 + 0x7C, D_8F10025C + 0x7C);
    gSPBranchList(gfx++, D_8F1555B8);
    return gfx;
}

void func_8F100214(s32 arg0, s8* arg1) {
    if (arg0 == 2) {
        M2C_FIELD(arg1, Gfx**, 0x18) = Gfx_AllocDisplayList(0x18);
        func_8F100154(M2C_FIELD(arg1, Gfx**, 0x18));
    }
}
