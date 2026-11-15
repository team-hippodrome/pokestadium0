/* Stadium Zero resident code. */
/* C ported from the Stadium 1 decomp: src/gfx_rect.c. */

#include "global.h"
#include "gfx_rect.h"
#include "memory_main.h"
extern DepthBuffer* D_8005F670;

#include "m2c_macros.h"

void GfxImage_Initialize(DepthBuffer* arg0, s32 fmt, s32 size, s32 width, s32 height, u32 img_p);
void GfxImage_AttachDepthBuffer(DepthBuffer* img, DepthBuffer* depth);
DepthBuffer* GfxImage_GetCurrent(void);
void GfxImage_FillRectangle(Gfx** gfx_p, s32 arg1, s32 arg2, s32 arg3, s32 arg4, u16 fill_color);
void GfxImage_ClearDepthRectangle(Gfx** gfx_p, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void GfxImage_FillCurrent(Gfx** gfx_p, u16 fill_color);

/** Initializes an image with a format, size and dimensions. */
void GfxImage_Initialize(DepthBuffer* arg0, s32 fmt, s32 size, s32 width, s32 height, u32 img_p) {
    arg0->fmt = fmt;
    arg0->size = size;
    arg0->width = width;
    arg0->height = height;
    arg0->img_p = (u8*)ALIGN64(img_p);
    arg0->depth_p = NULL;
}

/** Allocates an image of the given format and size. */
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

/** Attaches a depth buffer to an image. */
void GfxImage_AttachDepthBuffer(DepthBuffer* img, DepthBuffer* depth) {
    if ((depth->size == IMAGE_SIZE_BITS_16b) && (img->width == depth->width) && (img->height == depth->height)) {
        img->depth_p = depth;
    }
}

/**
 * Seen in play (2026-11-13) (tour of menus and a COM battle): ran in the main menu, the Pokédex,
 * the party screen, the Lab list, Lab sort, registration, the Lab PC, Free Battle setup, the battle
 * opening, a switch in battle, running from battle and a Pound turn.
 * @unverified Name was previously used only by callers of this address; the definition was still func_.
 */
void GfxImage_ResetCurrent(void) {
    D_8005F670 = 0;
}

/** Returns the current render target image. */
DepthBuffer* GfxImage_GetCurrent(void) {
    return D_8005F670;
}

/**
 * Seen in play (2026-11-13) in the 165-move sweep: it emitted G_RDPPIPESYNC, a G_SETOTHERMODE_L,
 * G_SETZIMG (FE000000, depth buffer 0x00225180) and G_SETCIMG (FF...), and advanced the passed
 * display-list pointer.
 */
void GfxImage_SetRenderTarget(Gfx** gfx_p, DepthBuffer* arg1) {
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

/**
 * Seen in play (2026-11-13) in the 165-move sweep: it emitted G_RDPPIPESYNC and G_SETSCISSOR
 * ED000000 005003C0, the full 320x240 screen.
 */
void Gfx_ApplyScissorRect(Gfx** gfx_p) {
    Gfx* gfx = *gfx_p;

    gDPPipeSync(gfx++);
    gDPSetScissor(gfx++, G_SC_NON_INTERLACE, 0, 0, D_8005F670->width, D_8005F670->height);
    *gfx_p = gfx;
}

/** Emits commands that fill a rectangle of the current image with a color. */
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

/** Emits commands that clear a rectangle of the current depth buffer. */
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

/** Emits commands that fill the whole current image with a color. */
void GfxImage_FillCurrent(Gfx** gfx_p, u16 fill_color) {
    GfxImage_FillRectangle(gfx_p, 0, 0, D_8005F670->width, D_8005F670->height, (fill_color << 0x10) | fill_color);
}
