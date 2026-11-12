/* Stadium Zero resident code. */
/* C ported from the Stadium 1 decomp: src/input.c. */

#include "global.h"
#include "input.h"
extern s32 pad_D_800AC880[0x2];
extern s32 D_800AB02C;
extern Controller* D_800AB030;

void Input_ResetRepeatState(void);

void Input_ResetRepeatState(void) {
}

void func_8001B5F8(s32 x1, s32 y1, s32 width, s32 height, s32 mode) {
    s32 xh = (x1 + width) << 2;
    s32 yh = (y1 + height) << 2;
    s32 dsdx = 0x400;

    if (mode == G_CYC_COPY) {
        xh -= 4;
        yh -= 4;
        dsdx = 0x1000;
    }
    gSPTextureRectangle(gDisplayListHead++, x1 << 2, y1 << 2, xh, yh, G_TX_RENDERTILE, 0, 0, dsdx, 0x400);
}

void func_8001B5F8(s32, s32, s32, s32, s32);

void Gfx_DrawTextureRgba32(s32 x1, s32 y1, s32 draw_width, s32 height, u8* texture, s32 load_width, s32 texture_spread_x_mode) {
    gDPLoadTextureBlock(gDisplayListHead++, texture, G_IM_FMT_RGBA, G_IM_SIZ_32b, load_width, height, 0,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                        G_TX_NOLOD);

    func_8001B5F8(x1, y1, draw_width, height, texture_spread_x_mode);
}

void Gfx_DrawTextureRgba16(s32 x1, s32 y1, s32 draw_width, s32 height, u8* texture, s32 load_width, s32 texture_spread_x_mode) {
    gDPLoadTextureBlock(gDisplayListHead++, texture, G_IM_FMT_RGBA, G_IM_SIZ_16b, load_width, height, 0,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                        G_TX_NOLOD);

    func_8001B5F8(x1, y1, draw_width, height, texture_spread_x_mode);
}

void func_8000A610(s32, s32, s32, s32, s32, s32, s32);
void func_8001BA54(s32 x1, s32 y1, s32 draw_width, s32 height, u8* texture, s32 load_width, s32 mode) {
    gDPLoadTextureBlock(gDisplayListHead++, texture, G_IM_FMT_RGBA, G_IM_SIZ_16b, load_width, height, 0,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                        G_TX_NOLOD);
    if (mode == G_CYC_COPY) {
        func_8000A610(x1, y1, x1 + draw_width - 1, y1 + height - 1, 0x1000, 0x400, mode);
    } else {
        func_8000A610(x1, y1, x1 + draw_width - 1, y1 + height - 1, 0x400, 0x400, mode);
    }
}

void Gfx_DrawTextureIa8(s32 x1, s32 y1, s32 draw_width, s32 height, u8* texture, s32 load_width, s32 texture_spread_x_mode) {
    gDPLoadTextureBlock(gDisplayListHead++, texture, G_IM_FMT_IA, G_IM_SIZ_8b, load_width, height, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    func_8001B5F8(x1, y1, draw_width, height, texture_spread_x_mode);
}

void Gfx_DrawTextureIa16(s32 x1, s32 y1, s32 draw_width, s32 height, u8* texture, s32 load_width, s32 texture_spread_x_mode) {
    gDPLoadTextureBlock(gDisplayListHead++, texture, G_IM_FMT_IA, G_IM_SIZ_16b, load_width, height, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    func_8001B5F8(x1, y1, draw_width, height, texture_spread_x_mode);
}

void Gfx_DrawTextureI4(s32 x1, s32 y1, s32 draw_width, s32 height, u8* texture, s32 load_width, s32 texture_spread_x_mode) {
    gDPLoadTextureBlock_4b(gDisplayListHead++, texture, G_IM_FMT_I, load_width, height, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                           G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

    func_8001B5F8(x1, y1, draw_width, height, texture_spread_x_mode);
}

void Gfx_DrawTextureI8(s32 x1, s32 y1, s32 draw_width, s32 height, u8* texture, s32 load_width, s32 texture_spread_x_mode) {
    gDPLoadTextureBlock(gDisplayListHead++, texture, G_IM_FMT_I, G_IM_SIZ_8b, load_width, height, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

    func_8001B5F8(x1, y1, draw_width, height, texture_spread_x_mode);
}

void Gfx_DrawTextureI16(s32 x1, s32 y1, s32 draw_width, s32 height, u8* texture, s32 load_width, s32 texture_spread_x_mode) {
    gDPLoadTextureBlock(gDisplayListHead++, texture, G_IM_FMT_I, G_IM_SIZ_16b, load_width, height, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

    func_8001B5F8(x1, y1, draw_width, height, texture_spread_x_mode);
}


void Gfx_DrawTextureRgba16Ia8(s32 x1, s32 y1, s32 draw_width, s32 height, u8* texture, u8* texture_multi, s32 load_width, s32 texture_x_spread_mode) {
    gDPLoadTextureBlock(gDisplayListHead++, texture, G_IM_FMT_RGBA, G_IM_SIZ_16b, load_width, height, 0,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                        G_TX_NOLOD);
    gDPLoadMultiBlock(gDisplayListHead++, texture_multi, 0x0100, 1, G_IM_FMT_I, G_IM_SIZ_8b, load_width, height, 0,
                      G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                      G_TX_NOLOD);

    func_8001B5F8(x1, y1, draw_width, height, texture_x_spread_mode);
}

extern u8 D_02000000[];
void func_8001C97C(s32 y) {
    s32 x;

    gDPLoadTextureBlock(gDisplayListHead++, D_02000000 + (y % 128) * 128, G_IM_FMT_I, G_IM_SIZ_8b, 128, 16, 0,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                        G_TX_NOLOD);
    for (x = 0; x < 640; x += 128) {
        gSPTextureRectangle(gDisplayListHead++, x << 2, y << 2, (x + 128) << 2, (y + 16) << 2, G_TX_RENDERTILE, 0, 0,
                            0x400, 0x400);
    }
}

void func_8001CC90(s32 start, s32 end, s32 r, s32 g, s32 b) {
    s32 y;

    gDPPipeSync(gDisplayListHead++);
    gDPSetCycleType(gDisplayListHead++, G_CYC_1CYCLE);
    gDPSetRenderMode(gDisplayListHead++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
    gDPSetCombineLERP(gDisplayListHead++, TEXEL0, 0, ENVIRONMENT, 0, TEXEL0, 0, ENVIRONMENT, 0, TEXEL0, 0, ENVIRONMENT, 0,
                      TEXEL0, 0, ENVIRONMENT, 0);
    gDPSetScissor(gDisplayListHead++, G_SC_NON_INTERLACE, 0, 0, 640, 480);
    gDPSetTexturePersp(gDisplayListHead++, G_TP_NONE);
    gDPSetEnvColor(gDisplayListHead++, r, g, b, 255);
    start &= ~1;
    end = (end + 1) & ~1;
    for (y = start; y < end; y += 16) {
        func_8001C97C(y);
    }
    gDPPipeSync(gDisplayListHead++);
    gDPSetTexturePersp(gDisplayListHead++, G_TP_PERSP);
}

void func_8001CE20(s32 x, s32 y, s32 width, s32 height) {
    s32 n;

    gDPLoadTextureBlock(gDisplayListHead++, D_02000000 + (y % 128) * 128, G_IM_FMT_I, G_IM_SIZ_8b, 128, 16, 0,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                        G_TX_NOLOD);
    if (x % 128 != 0) {
        UNUSED s32 pad; // FAKE: stack padding
        n = 128 - x % 128;
        gSPTextureRectangle(gDisplayListHead++, x << 2, y << 2, (x + n) << 2, (y + height) << 2, G_TX_RENDERTILE,
                            (x % 128) << 5, 0, 0x400, 0x400);
        width -= n;
        x += n;
    }
    while (width >= 128) {
        gSPTextureRectangle(gDisplayListHead++, x << 2, y << 2, (x + 128) << 2, (y + height) << 2, G_TX_RENDERTILE, 0,
                            0, 0x400, 0x400);
        width -= 128;
        x += 128;
    }
    if (width != 0) {
        gSPTextureRectangle(gDisplayListHead++, x << 2, y << 2, (x + width) << 2, (y + height) << 2, G_TX_RENDERTILE,
                            0, 0, 0x400, 0x400);
    }
}

void func_8001D148(s32 x, s32 y, s32 width, s32 height, s32 r, s32 g, s32 b) {
    UNUSED s32 pad[7]; // FAKE: stack padding
    s32 s;
    s32 n;

    gDPPipeSync(gDisplayListHead++);
    gDPSetCycleType(gDisplayListHead++, G_CYC_1CYCLE);
    gDPSetRenderMode(gDisplayListHead++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
    gDPSetCombineLERP(gDisplayListHead++, TEXEL0, 0, ENVIRONMENT, 0, TEXEL0, 0, ENVIRONMENT, 0, TEXEL0, 0, ENVIRONMENT, 0,
                      TEXEL0, 0, ENVIRONMENT, 0);
    gDPSetScissor(gDisplayListHead++, G_SC_NON_INTERLACE, 0, 0, 640, 480);
    gDPSetTexturePersp(gDisplayListHead++, G_TP_NONE);
    gDPSetEnvColor(gDisplayListHead++, r, g, b, 255);
    s = y % 16;
    if (s != 0) {
        n = 16 - s;
        if (height < n) {
            n = height;
        }
        func_8001CE20(x, y, width, n);
        y += n;
        height -= n;
    }
    while (height >= 16) {
        func_8001CE20(x, y, width, 16);
        height -= 16;
        y += 16;
    }
    if (height != 0) {
        func_8001CE20(x, y, width, height);
    }
    gDPPipeSync(gDisplayListHead++);
    gDPSetTexturePersp(gDisplayListHead++, G_TP_PERSP);
}
