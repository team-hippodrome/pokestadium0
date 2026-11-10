/* Stadium Zero resident code. */
/* C ported from the Stadium 1 decomp: src/graphics_textures.c. */

#include "global.h"
#include "graphics_textures.h"
#include "string.h"
#include "jpeg_stream.h"
#include "gfx_buffer.h"
#include "ui_graphics.h"
#include "gfx_rect.h"
#include "matrix.h"
#include "memory.h"
#include "stdarg.h"
#include "lib/ultralib/src/libc/xstdio.h"
extern FontContext* font_context;

void Gfx_SetVertexAttributes(Vtx* vertex, s16 x, s16 y, s16 z, s16 texture_x, s16 texture_y, u8 r, u8 g, u8 b, u8 alpha);
void Gfx_SetViewportDimensions(Vp* viewport, s16 width, s16 height);

void Gfx_SetVertexAttributes(Vtx* vertex, s16 x, s16 y, s16 z, s16 texture_x, s16 texture_y, u8 r, u8 g, u8 b, u8 alpha) {
    vertex->v.ob[0] = x;
    vertex->v.ob[1] = y;
    vertex->v.ob[2] = z;
    vertex->v.flag = 0;
    vertex->v.tc[0] = texture_x;
    vertex->v.tc[1] = texture_y;
    vertex->v.cn[0] = r;
    vertex->v.cn[1] = g;
    vertex->v.cn[2] = b;
    vertex->v.cn[3] = alpha;
}

void Gfx_SetViewportDimensions(Vp* viewport, s16 width, s16 height) {
    viewport->vp.vtrans[0] = width * 2;
    viewport->vp.vtrans[1] = height * 2;
    viewport->vp.vtrans[2] = 0x1FF;
    viewport->vp.vtrans[3] = 0;
    viewport->vp.vscale[0] = width * 2;
    viewport->vp.vscale[1] = height * 2;
    viewport->vp.vscale[2] = 0x1FF;
    viewport->vp.vscale[3] = 0;
}

s32 func_80006B50(s32*, s32*, s32*, s32*);

void func_8000A610(s32 x1, s32 y1, s32 x2, s32 y2, s32 stepX, s32 stepY, s32 mode) {
    s32 s = x1;
    s32 t = y1;

    if (func_80006B50(&x1, &y1, &x2, &y2) != 0) {
        if (mode != 0x200000) {
            x2 += 1; y2 += 1; // FAKE: both increments must share one source line (IDO schedules by line)
        }
        if (stepX != 0) {
            s = x1 - s;
        } else {
            s = 0;
        }
        if (stepY != 0) {
            t = y1 - t;
        } else {
            t = 0;
        }
        gSPTextureRectangle(gDisplayListHead++, x1 << 2, y1 << 2, x2 << 2, y2 << 2, G_TX_RENDERTILE, s << 5, t << 5, stepX, stepY);
    }
}
