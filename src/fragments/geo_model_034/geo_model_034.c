/* Stadium Zero fragment034_369F50. */

#include "global.h"
#include "gfx_buffer.h"
#include "m2c_macros.h"

extern Gfx D_8EB43778[];
extern s32 D_8EB43770;
extern u16 D_8EB42F70[];
Gfx* func_8EB00040(Gfx* gfx, Gfx* next, void* texture, s32 shiftS, s32 shiftT, s32 scaleS, s32 scaleT);

extern s8 *D_8006049C;

void func_8EB00020(s32 arg0, s8 *arg1) {
    if (arg0 == 2) {
        M2C_FIELD(arg1, s16 *, 0x1A) = (s16) M2C_FIELD(D_8006049C, s32 *, 0x14);
    }
}

Gfx* func_8EB00040(Gfx* gfx, Gfx* next, void* texture, s32 shiftS, s32 shiftT, s32 scaleS, s32 scaleT) {
    gSPDisplayList(gfx++, D_8EB43778);
    gSPTexture(gfx++, scaleS, scaleT, 0, G_TX_RENDERTILE, G_ON);
    gDPLoadTextureBlock(gfx++, texture, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0, G_TX_WRAP | G_TX_NOMIRROR,
                        G_TX_WRAP | G_TX_NOMIRROR, 5, 5, shiftS, shiftT);
    gDPSetTileSize(gfx++, G_TX_RENDERTILE, 0, D_8EB43770, 0x7C, D_8EB43770 + 0x7C);
    gSPBranchList(gfx++, next);
    return gfx;
}

extern u16 D_8EB40770[];

void func_8EB0018C(s32 arg0, s8* arg1) {
    if (arg0 == 2) {
        M2C_FIELD(arg1, Gfx**, 0x18) = Gfx_AllocDisplayList(0x58);
        func_8EB00040(M2C_FIELD(arg1, Gfx**, 0x18), M2C_FIELD(arg1, Gfx**, 0x14), D_8EB40770, 1, 1, 0x1F40, 0x1F40);
    }
}

extern u16 D_8EB40F70[];

void func_8EB001F0(s32 arg0, s8* arg1) {
    if (arg0 == 2) {
        M2C_FIELD(arg1, Gfx**, 0x18) = Gfx_AllocDisplayList(0x58);
        func_8EB00040(M2C_FIELD(arg1, Gfx**, 0x18), M2C_FIELD(arg1, Gfx**, 0x14), D_8EB40F70, 1, 1, 0x1F40, 0x1F40);
    }
}

extern u16 D_8EB41770[];

void func_8EB00254(s32 arg0, s8* arg1) {
    if (arg0 == 2) {
        M2C_FIELD(arg1, Gfx**, 0x18) = Gfx_AllocDisplayList(0x58);
        func_8EB00040(M2C_FIELD(arg1, Gfx**, 0x18), M2C_FIELD(arg1, Gfx**, 0x14), D_8EB41770, 0, 0xF, 0x1F40, 0x206C);
    }
}

extern u16 D_8EB41F70[];

void func_8EB002B8(s32 arg0, s8* arg1) {
    if (arg0 == 2) {
        M2C_FIELD(arg1, Gfx**, 0x18) = Gfx_AllocDisplayList(0x58);
        func_8EB00040(M2C_FIELD(arg1, Gfx**, 0x18), M2C_FIELD(arg1, Gfx**, 0x14), D_8EB41F70, 0, 1, 0xFA0, 0xFA0);
    }
}

extern u16 D_8EB42770[];

void func_8EB0031C(s32 arg0, s8* arg1) {
    if (arg0 == 2) {
        M2C_FIELD(arg1, Gfx**, 0x18) = Gfx_AllocDisplayList(0x58);
        func_8EB00040(M2C_FIELD(arg1, Gfx**, 0x18), M2C_FIELD(arg1, Gfx**, 0x14), D_8EB42770, 2, 0xE, 0xFA0, 0xFA0);
    }
}

void func_8EB00380(s32 arg0, s8* arg1) {
    if (arg0 == 2) {
        D_8EB43770--;
        if (D_8EB43770 < 0) {
            D_8EB43770 = 0x7F;
        }
        M2C_FIELD(arg1, Gfx**, 0x18) = Gfx_AllocDisplayList(0x58);
        func_8EB00040(M2C_FIELD(arg1, Gfx**, 0x18), M2C_FIELD(arg1, Gfx**, 0x14), D_8EB42F70, 1, 1, 0x1F40, 0x1F40);
    }
}
