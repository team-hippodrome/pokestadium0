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

#include "m2c_macros.h"
extern Gfx D_80060950[];
extern Gfx D_800609A8[];

void Font_ResetContext(UNUSED s32 arg0, UNUSED s32 arg1);
s32 Font_GetSetIndexFromMask(s32 mask);
void Font_Free(void);
char* String_CopyBytesAndAdvance(char* buffer, const char* data, u32 size);
void Gfx_SetEnvColor(s32 r, s32 g, s32 b, s32 a);
void Gfx_SetPrimColor(s32 r, s32 g, s32 b, s32 a);
void Font_EndTexturedTextRendering(void);

void Font_ResetContext(UNUSED s32 arg0, UNUSED s32 arg1) {
    font_context = NULL;
}

s32 Font_GetSetIndexFromMask(s32 mask) {
    s32 index = 0;

    if (mask != 0x1) {
        if (mask == 0x2) {
            index = 1;
        } else if (mask == 0x4) {
            index = 2;
        } else if (mask == 0x8) {
            index = 3;
        } else if (mask == 0x10) {
            index = 4;
        } else if (mask == 0x20) {
            index = 5;
        }
    }

    return index;
}

/*
 * func_8001A118: registers one font set in the font context.
 *
 * Takes the next free slot index from func_8001A0A4 and fills the 8-byte
 * entry at that index in the table at the start of *font_context: three
 * size bytes (arg1, arg2, arg3 -- their meaning is not established; func_8001A194
 * passes e.g. 0x20/0x20/0x20 for mask 0x20 and 0xA/0xA/0x10 for mask 0x1) and
 * the pointer to the font file.  The slot index is then stored at
 * font_context + 0x38 (FontContext::unk_50, cleared by func_8001A194).
 *
 * `mask` is not used by the retail code; the empty `if (mask) {}` is only there
 * so IDO does not spill the unused argument register.
 */
typedef struct FontEntry8001A118 {
    /* 0x0 */ s8 size_a;
    /* 0x1 */ s8 size_b;
    /* 0x2 */ s8 size_c;
    /* 0x4 */ void* file;
} FontEntry8001A118; // size = 0x8
s32 func_8001A0A4(void);
void func_8001A118(s32 mask, s32 arg1, s32 arg2, s32 arg3, void* file);
void func_8001A118(s32 mask, s32 arg1, s32 arg2, s32 arg3, void* file) {
    s32 index;

    if (mask) {}
    index = func_8001A0A4();

    ((FontEntry8001A118*)font_context)[index].file = file;
    ((FontEntry8001A118*)font_context)[index].size_a = arg1;
    ((FontEntry8001A118*)font_context)[index].size_b = arg2;
    ((FontEntry8001A118*)font_context)[index].size_c = arg3;
    font_context->unk_50 = index;
}

/*
 * func_8001A194 (Font_Init in symbol_addrs.txt)
 *
 * Creates the font context.  Allocates a 0x3C-byte block from the main pool
 * on heap `side` (the second argument is passed straight through to
 * main_pool_alloc_with_func), tagged 'PRNT', with Font_ResetContext as the
 * free callback; opens the font archive (ROM range D_002B2C80..D_002E0BE0)
 * into font_context->unk_48 and clears the two bytes at +0x38 / +0x39.
 * Then, for every bit set in `load_size`, loads one font set with
 * func_8001A118 (mask, three size values, file number in the archive):
 *
 *   bit 0x20: file 5   bit 0x10: file 4   bit 0x08: file 3
 *   bit 0x04: file 2   bit 0x02: file 1   bit 0x01: file 0
 *
 * Always returns 1.
 *
 * The Stadium 1 version (Font_Init + Font_LoadSizes) is structured the same
 * way but zeroes the block with bzero, returns the context and calls a
 * three-argument Font_LoadSet; this Zero version is the older shape.  The
 * meaning of the three size values passed to func_8001A118 is not
 * established here (func_8001A118 is still assembly); the values are copied
 * from the retail code.
 */
extern u8 D_002B2C80[];
extern u8 D_002E0BE0[];
void func_8001A118(s32 mask, s32 arg1, s32 arg2, s32 arg3, void* file);

s32 func_8001A194(s32 load_size, s32 side) {
    font_context = main_pool_alloc_with_func(sizeof(*font_context), side, 'PRNT', (AllocateFunc)Font_ResetContext);
    font_context->unk_48 = BinArchive_Open(D_002B2C80, D_002E0BE0, 1, 1);
    font_context->unk_50 = 0;
    font_context->unk_51 = 0;

    if (load_size & 0x20) {
        func_8001A118(0x20, 0x20, 0x20, 0x20, BinArchive_GetFile(font_context->unk_48, 5));
    }
    if (load_size & 0x10) {
        func_8001A118(0x10, 0x18, 0x18, 0x18, BinArchive_GetFile(font_context->unk_48, 4));
    }
    if (load_size & 0x8) {
        func_8001A118(0x8, 0x14, 0x14, 0x18, BinArchive_GetFile(font_context->unk_48, 3));
    }
    if (load_size & 0x4) {
        func_8001A118(0x4, 0x10, 0x10, 0x10, BinArchive_GetFile(font_context->unk_48, 2));
    }
    if (load_size & 0x2) {
        func_8001A118(0x2, 0xC, 0xC, 0x10, BinArchive_GetFile(font_context->unk_48, 1));
    }
    if (load_size & 0x1) {
        func_8001A118(0x1, 0xA, 0xA, 0x10, BinArchive_GetFile(font_context->unk_48, 0));
    }
    return 1;
}

void Font_Free(void) {
    main_pool_try_free(font_context);
}

void Font_SetActive(s32 mask, s32 arg1) {
    if (font_context != NULL) {
        font_context->unk_50 = Font_GetSetIndexFromMask(mask);
        font_context->unk_51 = arg1;
        font_context->line_break_flag &= ~2;
    }
}

#ifdef NON_MATCHING
/* TODO: decompile func_8001A3E4; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_8001A3E4.s")
#endif

char* String_CopyBytesAndAdvance(char* buffer, const char* data, u32 size) {
    return (char*)memcpy(buffer, data, size) + size;
}

#ifdef NON_MATCHING
/* TODO: decompile func_8001A944; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_8001A944.s")
#endif

M2C_UNK func_8001A3E4(s16, s16, s16);               /* extern */
void func_8001AA60(s32 arg0, s32 arg1, s32 arg2) {
    func_8001A3E4(arg0, arg1, (s16) (arg2 & 0x7F7F));
}

void Gfx_SetEnvColor(s32 r, s32 g, s32 b, s32 a) {
    gDPSetEnvColor(gDisplayListHead++, r, g, b, a);
}

void Gfx_SetPrimColor(s32 r, s32 g, s32 b, s32 a) {
    gDPSetPrimColor(gDisplayListHead++, 0, 0, r, g, b, a);
}

extern s8 *D_800AD200;
void func_8001AB2C(s32 arg0) {
    M2C_FIELD(D_800AD200, s8 *, 0x3A) = arg0;
}

extern s8 *D_800AD200;

void func_8001AB3C(void) {
    M2C_FIELD(D_800AD200, u8 *, 0x3B) = (u8) (M2C_FIELD(D_800AD200, u8 *, 0x3B) | 4);
}

extern s8 *D_800AD200;

void func_8001AB54(void) {
    M2C_FIELD(D_800AD200, u8 *, 0x3B) = (u8) (M2C_FIELD(D_800AD200, u8 *, 0x3B) & 0xFFFB);
}

void Font_BeginTranslucentTextRendering(void) {
    font_context->line_break_flag = 0;
    font_context->line_height = 0x28;
    font_context->unk_4C = 0;

    gSPDisplayList(gDisplayListHead++, D_80060950);
}

void Font_EndTexturedTextRendering(void) {
    gSPDisplayList(gDisplayListHead++, D_80060990);
}

void Font_EnableTwoCycleTexturing(void) {
    font_context->line_break_flag |= 1;
    font_context->line_break_flag &= ~2;

    gSPDisplayList(gDisplayListHead++, D_800609A8);
}

extern Gfx D_800609D8[];

void Font_DisableTwoCycleTexturing(void) {
    M2C_FIELD(font_context, u8*, 0x3B) &= ~3;
    gSPDisplayList(gDisplayListHead++, D_800609D8);
}

#ifdef NON_MATCHING
/* TODO: decompile func_8001AC7C; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_8001AC7C.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_8001ADA0; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_8001ADA0.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_8001AFB0; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_8001AFB0.s")
#endif

/**
 * Builds a small display list in freshly allocated display-list memory:
 * lighting is switched off, textures are enabled with full scale, a two-cycle
 * combiner (TEXEL0 * ENVIRONMENT) is selected, the environment colour is set
 * to arg1, the caller's display list
 * arg0 is called, and lighting is switched back on.
 *
 * Note: 0x80 bytes are allocated but only the first 0x40 (eight commands)
 * are written.
 */
void func_8001B25C(Gfx* arg0, Color_RGBA8 arg1) {
    Gfx* gfx = Gfx_AllocDisplayList(0x80);

    gDPPipeSync(gfx++);
    gSPClearGeometryMode(gfx++, G_LIGHTING);
    gSPTexture(gfx++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
    gDPSetCombineLERP(gfx++, TEXEL0, 0, ENVIRONMENT, 0, TEXEL0, 0, ENVIRONMENT, 0, 0, 0, 0, COMBINED, 0, 0, 0,
                      COMBINED);
    gDPSetEnvColor(gfx++, arg1.r, arg1.g, arg1.b, arg1.a);
    gSPDisplayList(gfx++, arg0);
    gSPSetGeometryMode(gfx++, G_LIGHTING);
    gSPEndDisplayList(gfx++);
}

#ifdef NON_MATCHING
/* TODO: decompile func_8001B32C; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_8001B32C.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_8001B3AC; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_8001B3AC.s")
#endif
