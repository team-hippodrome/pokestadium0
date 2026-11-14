/* Declarations for src/gfx_rect.c. */
#ifndef GFX_RECT_H
#define GFX_RECT_H

#include "global.h"
#include "stdarg.h"
#include "moves.h"
#include "m2c_macros.h"

// image size in bits
typedef enum IMAGE_SIZE_BITS {
	IMAGE_SIZE_BITS_4b  = 0,
	IMAGE_SIZE_BITS_8b  = 1,
	IMAGE_SIZE_BITS_16b = 2,
	IMAGE_SIZE_BITS_32b = 3,
} IMAGE_SIZE_BITS;

typedef enum IMAGE_FMT {
	IMAGE_FMT_RGBA = 0,
	IMAGE_FMT_YUV  = 1,
	IMAGE_FMT_CI   = 2,
	IMAGE_FMT_IA   = 3,
	IMAGE_FMT_I    = 4,
} IMAGE_FMT;

typedef struct GfxImage {
	/* 0x00 */ u16 fmt;
	/* 0x02 */ u16 size;
	/* 0x04 */ u16 width;
	/* 0x06 */ u16 height;
	/* 0x08 */ u8* img_p;
	/* 0x0C */ struct GfxImage* depth_p;
} GfxImage; // size = 0x10; a color or depth image header followed by its pixels (GfxImage_Allocate)

// gfx_rect.c
void Gfx_ApplyScissorRect(Gfx** gfx_p);
void GfxImage_Initialize(GfxImage* arg0, s32 fmt, s32 size, s32 width, s32 height, u32 img_p);
GfxImage* GfxImage_Allocate(s32 fmt, s32 size, s32 width, s32 height, s32 side);
void GfxImage_AttachDepthBuffer(GfxImage* img, GfxImage* depth);
void GfxImage_ResetCurrent(void);
GfxImage* GfxImage_GetCurrent(void);
void GfxImage_SetRenderTarget(Gfx** gfx_p, GfxImage* arg1);
void GfxImage_FillRectangle(Gfx** gfx_p, s32 arg1, s32 arg2, s32 arg3, s32 arg4, u16 fill_color);
void GfxImage_ClearDepthRectangle(Gfx** gfx_p, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void GfxImage_FillCurrent(Gfx** gfx_p, u16 fill_color);
M2C_UNK func_80005770(M2C_UNK *, M2C_UNK, M2C_UNK, M2C_UNK, s32); /* extern */
M2C_UNK func_800051C0(s32, M2C_UNK, M2C_UNK, M2C_UNK, s32, s32); /* extern */
M2C_UNK func_800052E8(s32, s32);                    /* extern */

#endif // GFX_RECT_H
