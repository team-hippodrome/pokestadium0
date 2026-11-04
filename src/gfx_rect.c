/* Stadium Zero resident code. */
/* C ported from the Stadium 1 decomp: src/gfx_rect.c. */

#include "global.h"
#include "gfx_rect.h"
#include "memory.h"
extern DepthBuffer* D_8005F670;

#include "m2c_macros.h"

void GfxImage_Initialize(DepthBuffer* arg0, s32 fmt, s32 size, s32 width, s32 height, u32 img_p);
void GfxImage_AttachDepthBuffer(DepthBuffer* img, DepthBuffer* depth);
DepthBuffer* GfxImage_GetCurrent(void);
void GfxImage_FillRectangle(Gfx** gfx_p, s32 arg1, s32 arg2, s32 arg3, s32 arg4, u16 fill_color);
void GfxImage_ClearDepthRectangle(Gfx** gfx_p, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void GfxImage_FillCurrent(Gfx** gfx_p, u16 fill_color);

void GfxImage_Initialize(DepthBuffer* arg0, s32 fmt, s32 size, s32 width, s32 height, u32 img_p) {
    arg0->fmt = fmt;
    arg0->size = size;
    arg0->width = width;
    arg0->height = height;
    arg0->img_p = (u8*)ALIGN64(img_p);
    arg0->depth_p = NULL;
}

DepthBuffer* GfxImage_Allocate(s32 fmt, s32 size, s32 width, s32 height, s32 side) {
    DepthBuffer* sp34;
    s32 size_bytes;
    s32 num_pixels = width * height;

    switch (size) {
        case IMAGE_SIZE_BITS_4b:
            size_bytes = (num_pixels + 1) / 2;
            break;

        case IMAGE_SIZE_BITS_8b:
            size_bytes = num_pixels;
            break;

        case IMAGE_SIZE_BITS_16b:
            size_bytes = num_pixels * 2;
            break;

        case IMAGE_SIZE_BITS_32b:
            size_bytes = num_pixels * 4;
            break;
    }

    // header + image size + rounding up to 64
    sp34 = main_pool_alloc(sizeof(DepthBuffer) + size_bytes + 64, side);
    // image data follows the header struct
    GfxImage_Initialize(sp34, fmt, size, width, height, (u8*)sp34 + sizeof(DepthBuffer));

    return sp34;
}

void GfxImage_AttachDepthBuffer(DepthBuffer* img, DepthBuffer* depth) {
    if ((depth->size == IMAGE_SIZE_BITS_16b) && (img->width == depth->width) && (img->height == depth->height)) {
        img->depth_p = depth;
    }
}

void func_80005324(void) {
    D_8005F670 = 0;
}

DepthBuffer* GfxImage_GetCurrent(void) {
    return D_8005F670;
}

void func_8000533C(Gfx** gfx_p, DepthBuffer* arg1) {
    Gfx* gfx = *gfx_p;

    gDPPipeSync(gfx++);

    if (arg1->depth_p != NULL) {
        gDPSetDepthSource(gfx++, G_ZS_PIXEL);
        gDPSetDepthImage(gfx++, (u32)arg1->depth_p->img_p & 0x1FFFFFFF);
    }

    gDPSetColorImage(gfx++, arg1->fmt, arg1->size, arg1->width, (u32)arg1->img_p & 0x1FFFFFFF);
    gDPSetScissor(gfx++, G_SC_NON_INTERLACE, 0, 0, arg1->width, arg1->height);
    D_8005F670 = arg1;
    *gfx_p = gfx;
}

#ifdef NON_MATCHING
/* TODO: decompile func_8000548C; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_8000548C.s")
#endif

void GfxImage_FillRectangle(Gfx** gfx_p, s32 arg1, s32 arg2, s32 arg3, s32 arg4, u16 fill_color) {
    if (D_8005F670 != NULL) {
        Gfx* gfx = *gfx_p;

        gDPPipeSync(gfx++);
        gDPSetRenderMode(gfx++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
        gDPSetCycleType(gfx++, G_CYC_FILL);

        if (D_8005F670->depth_p) {
            DepthBuffer* depth = D_8005F670->depth_p;

            gDPSetColorImage(gfx++, depth->fmt, depth->size, depth->width, (u32)depth->img_p & 0x1FFFFFFF);
            gDPSetFillColor(gfx++, 0xFFFCFFFC);
            gDPFillRectangle(gfx++, arg1, arg2, (arg1 + arg3) - 1, (arg2 + arg4) - 1);
            gDPPipeSync(gfx++);
            gDPSetColorImage(gfx++, D_8005F670->fmt, D_8005F670->size, D_8005F670->width,
                             (u32)D_8005F670->img_p & 0x1FFFFFFF);
        }

        gDPPipeSync(gfx++);
        gDPSetFillColor(gfx++, (fill_color << 0x10) | fill_color);
        gDPFillRectangle(gfx++, arg1, arg2, (arg1 + arg3) - 1, (arg2 + arg4) - 1);

        *gfx_p = gfx;
    }
}

void GfxImage_ClearDepthRectangle(Gfx** gfx_p, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    if (D_8005F670 != NULL && D_8005F670->depth_p != NULL) {
        Gfx* gfx = *gfx_p;
        DepthBuffer* depth = D_8005F670->depth_p;

        gDPPipeSync(gfx++);
        gDPSetRenderMode(gfx++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
        gDPSetCycleType(gfx++, G_CYC_FILL);
        gDPSetColorImage(gfx++, depth->fmt, depth->size, depth->width, (u32)depth->img_p & 0x1FFFFFFF);

        gDPSetFillColor(gfx++, 0xFFFCFFFC);
        gDPFillRectangle(gfx++, arg1, arg2, (arg1 + arg3) - 1, (arg2 + arg4) - 1);

        gDPPipeSync(gfx++);
        gDPSetColorImage(gfx++, D_8005F670->fmt, D_8005F670->size, D_8005F670->width,
                         (u32)D_8005F670->img_p & 0x1FFFFFFF);

        *gfx_p = gfx;
    }
}

void GfxImage_FillCurrent(Gfx** gfx_p, u16 fill_color) {
    GfxImage_FillRectangle(gfx_p, 0, 0, D_8005F670->width, D_8005F670->height, (fill_color << 0x10) | fill_color);
}
