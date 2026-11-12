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

/** Clears the font context pointer. */
void Font_ResetContext(UNUSED s32 arg0, UNUSED s32 arg1) {
    font_context = NULL;
}

/** Returns the index of the font set selected by a bit mask. */
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
 * size bytes (arg1, arg2, arg3 -- their meaning is not established; Font_Init
 * passes e.g. 0x20/0x20/0x20 for mask 0x20 and 0xA/0xA/0x10 for mask 0x1) and
 * the pointer to the font file.  The slot index is then stored at
 * font_context + 0x38 (FontContext::unk_50, cleared by Font_Init).
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

    if (mask) {}  // karodo
    index = func_8001A0A4();

    ((FontEntry8001A118*)font_context)[index].file = file;
    ((FontEntry8001A118*)font_context)[index].size_a = arg1;
    ((FontEntry8001A118*)font_context)[index].size_b = arg2;
    ((FontEntry8001A118*)font_context)[index].size_c = arg3;
    font_context->unk_50 = index;
}

/*
 * Font_Init (Font_Init in symbol_addrs.txt)
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

/** Allocates the font context. */
s32 Font_Init(s32 load_size, s32 side) {
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

/** Frees the font context. */
void Font_Free(void) {
    main_pool_try_free(font_context);
}

/** Selects the active font set. */
void Font_SetActive(s32 mask, s32 arg1) {
    if (font_context != NULL) {
        font_context->unk_50 = Font_GetSetIndexFromMask(mask);
        font_context->unk_51 = arg1;
        font_context->line_break_flag &= ~2;
    }
}

typedef struct FontGlyphSet8001A3E4 {
    /* 0x0 */ u8 advance;
    /* 0x1 */ u8 height;
    /* 0x2 */ u8 width;
    /* 0x4 */ u8* tex;
} FontGlyphSet8001A3E4; // size = 0x8
s32 func_80019F70(u16);

// FAKE: gDP* macros are expanded by hand and several are joined on one line; IDO schedules by source line and only this layout matches
s32 func_8001A3E4(s16 x, s16 y, s16 chr)
{
  FontGlyphSet8001A3E4 *set = &((FontGlyphSet8001A3E4 *) font_context)[font_context->unk_50];
  s32 offset = (func_80019F70(chr) * set->width) * set->height;
  UNUSED s32 pad; // FAKE
  s16 lrx = (x + set->advance) * 4;
  s16 lry = (y + set->height) * 4;
  if ((font_context->line_break_flag & 1) && (!(font_context->line_break_flag & 2)))
  {
    font_context->line_break_flag |= 2;
    {
      {
        Gfx *_g = (Gfx *) (gDisplayListHead++);
        _g->words.w0 = ((((unsigned int) ((((unsigned int) 0xfd) & ((0x01 << 8) - 1)) << 24)) | ((unsigned int) ((((unsigned int) 4) & ((0x01 << 3) - 1)) << 21))) | ((unsigned int) ((((unsigned int) 2) & ((0x01 << 2) - 1)) << 19))) | ((unsigned int) ((((unsigned int) (1 - 1)) & ((0x01 << 12) - 1)) << 0)); // FAKE: hand-expanded gbi macro
        _g->words.w1 = (unsigned int) (set->tex + ((set->width << 8) * set->height)); // FAKE: hand-expanded gbi macro
      }
      ;
      { Gfx *_g = (Gfx *) (gDisplayListHead++); _g->words.w0 = (((((unsigned int) ((((unsigned int) 0xf5) & ((0x01 << 8) - 1)) << 24)) | ((unsigned int) ((((unsigned int) 4) & ((0x01 << 3) - 1)) << 21))) | ((unsigned int) ((((unsigned int) 2) & ((0x01 << 2) - 1)) << 19))) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 9) - 1)) << 9))) | ((unsigned int) ((((unsigned int) 0x0100) & ((0x01 << 9) - 1)) << 0)); _g->words.w1 = ((((((((unsigned int) ((((unsigned int) 7) & ((0x01 << 3) - 1)) << 24)) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 4) - 1)) << 20))) | ((unsigned int) ((((unsigned int) (0 | 0x2)) & ((0x01 << 2) - 1)) << 18))) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 4) - 1)) << 14))) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 4) - 1)) << 10))) | ((unsigned int) ((((unsigned int) (0 | 0x2)) & ((0x01 << 2) - 1)) << 8))) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 4) - 1)) << 4))) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 4) - 1)) << 0)); } // FAKE: hand-expanded gbi macro
      ;
 { Gfx *_g = (Gfx *) (gDisplayListHead++); _g->words.w0 = (unsigned int) ((((unsigned int) 0xe6) & ((0x01 << 8) - 1)) << 24); _g->words.w1 = 0; } ; { Gfx *_g = (Gfx *) (gDisplayListHead++); _g->words.w0 = (((unsigned int) ((((unsigned int) 0xf3) & ((0x01 << 8) - 1)) << 24)) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 12) - 1)) << 12))) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 12) - 1)) << 0)); _g->words.w1 = (((unsigned int) ((((unsigned int) 7) & ((0x01 << 3) - 1)) << 24)) | ((unsigned int) ((((unsigned int) ((((((set->width * set->height) + 1) >> 1) - 1) < 2047) ? ((((set->width * set->height) + 1) >> 1) - 1) : (2047))) & ((0x01 << 12) - 1)) << 12))) | ((unsigned int) ((((unsigned int) ((((1 << 11) + ((1 > ((set->width * 1) / 8)) ? (1) : ((set->width * 1) / 8))) - 1) / ((1 > ((set->width * 1) / 8)) ? (1) : ((set->width * 1) / 8)))) & ((0x01 << 12) - 1)) << 0)); } ; { Gfx *_g = (Gfx *) (gDisplayListHead++); _g->words.w0 = (unsigned int) ((((unsigned int) 0xe7) & ((0x01 << 8) - 1)) << 24); _g->words.w1 = 0; } ; { Gfx *_g = (Gfx *) (gDisplayListHead++); _g->words.w0 = (((((unsigned int) ((((unsigned int) 0xf5) & ((0x01 << 8) - 1)) << 24)) | ((unsigned int) ((((unsigned int) 4) & ((0x01 << 3) - 1)) << 21))) | ((unsigned int) ((((unsigned int) 1) & ((0x01 << 2) - 1)) << 19))) | ((unsigned int) ((((unsigned int) (((set->width * 1) + 7) >> 3)) & ((0x01 << 9) - 1)) << 9))) | ((unsigned int) ((((unsigned int) 0x0100) & ((0x01 << 9) - 1)) << 0)); _g->words.w1 = ((((((((unsigned int) ((((unsigned int) 1) & ((0x01 << 3) - 1)) << 24)) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 4) - 1)) << 20))) | ((unsigned int) ((((unsigned int) (0 | 0x2)) & ((0x01 << 2) - 1)) << 18))) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 4) - 1)) << 14))) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 4) - 1)) << 10))) | ((unsigned int) ((((unsigned int) (0 | 0x2)) & ((0x01 << 2) - 1)) << 8))) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 4) - 1)) << 4))) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 4) - 1)) << 0)); } ; { Gfx *_g = (Gfx *) (gDisplayListHead++); _g->words.w0 = (((unsigned int) ((((unsigned int) 0xf2) & ((0x01 << 8) - 1)) << 24)) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 12) - 1)) << 12))) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 12) - 1)) << 0)); _g->words.w1 = (((unsigned int) ((((unsigned int) 1) & ((0x01 << 3) - 1)) << 24)) | ((unsigned int) ((((unsigned int) ((set->width - 1) << 2)) & ((0x01 << 12) - 1)) << 12))) | ((unsigned int) ((((unsigned int) ((set->height - 1) << 2)) & ((0x01 << 12) - 1)) << 0)); } ; } ; } if (((s32) (set->tex + offset)) != font_context->unk_4C) { font_context->unk_4C = (s32) (set->tex + offset); { { Gfx *_g = (Gfx *) (gDisplayListHead++); _g->words.w0 = ((((unsigned int) ((((unsigned int) 0xfd) & ((0x01 << 8) - 1)) << 24)) | ((unsigned int) ((((unsigned int) 3) & ((0x01 << 3) - 1)) << 21))) | ((unsigned int) ((((unsigned int) 2) & ((0x01 << 2) - 1)) << 19))) | ((unsigned int) ((((unsigned int) (1 - 1)) & ((0x01 << 12) - 1)) << 0)); _g->words.w1 = (unsigned int) (set->tex + offset); } ; { Gfx *_g = (Gfx *) (gDisplayListHead++); _g->words.w0 = (((((unsigned int) ((((unsigned int) 0xf5) & ((0x01 << 8) - 1)) << 24)) | ((unsigned int) ((((unsigned int) 3) & ((0x01 << 3) - 1)) << 21))) | ((unsigned int) ((((unsigned int) 2) & ((0x01 << 2) - 1)) << 19))) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 9) - 1)) << 9))) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 9) - 1)) << 0)); _g->words.w1 = ((((((((unsigned int) ((((unsigned int) 7) & ((0x01 << 3) - 1)) << 24)) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 4) - 1)) << 20))) | ((unsigned int) ((((unsigned int) (0 | 0x2)) & ((0x01 << 2) - 1)) << 18))) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 4) - 1)) << 14))) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 4) - 1)) << 10))) | ((unsigned int) ((((unsigned int) (0 | 0x2)) & ((0x01 << 2) - 1)) << 8))) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 4) - 1)) << 4))) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 4) - 1)) << 0)); } ; { Gfx *_g = (Gfx *) (gDisplayListHead++); _g->words.w0 = (unsigned int) ((((unsigned int) 0xe6) & ((0x01 << 8) - 1)) << 24); _g->words.w1 = 0; } ; { Gfx *_g = (Gfx *) (gDisplayListHead++); _g->words.w0 = (((unsigned int) ((((unsigned int) 0xf3) & ((0x01 << 8) - 1)) << 24)) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 12) - 1)) << 12))) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 12) - 1)) << 0)); _g->words.w1 = (((unsigned int) ((((unsigned int) 7) & ((0x01 << 3) - 1)) << 24)) | ((unsigned int) ((((unsigned int) ((((((set->width * set->height) + 1) >> 1) - 1) < 2047) ? ((((set->width * set->height) + 1) >> 1) - 1) : (2047))) & ((0x01 << 12) - 1)) << 12))) | ((unsigned int) ((((unsigned int) ((((1 << 11) + ((1 > ((set->width * 1) / 8)) ? (1) : ((set->width * 1) / 8))) - 1) / ((1 > ((set->width * 1) / 8)) ? (1) : ((set->width * 1) / 8)))) & ((0x01 << 12) - 1)) << 0)); } // FAKE: hand-expanded gbi macro
      ;
      { Gfx *_g = (Gfx *) (gDisplayListHead++); _g->words.w0 = (unsigned int) ((((unsigned int) 0xe7) & ((0x01 << 8) - 1)) << 24); _g->words.w1 = 0; } // FAKE: hand-expanded gbi macro
      ;
      { Gfx *_g = (Gfx *) (gDisplayListHead++); _g->words.w0 = (((((unsigned int) ((((unsigned int) 0xf5) & ((0x01 << 8) - 1)) << 24)) | ((unsigned int) ((((unsigned int) 3) & ((0x01 << 3) - 1)) << 21))) | ((unsigned int) ((((unsigned int) 1) & ((0x01 << 2) - 1)) << 19))) | ((unsigned int) ((((unsigned int) (((set->width * 1) + 7) >> 3)) & ((0x01 << 9) - 1)) << 9))) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 9) - 1)) << 0)); _g->words.w1 = ((((((((unsigned int) ((((unsigned int) 0) & ((0x01 << 3) - 1)) << 24)) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 4) - 1)) << 20))) | ((unsigned int) ((((unsigned int) (0 | 0x2)) & ((0x01 << 2) - 1)) << 18))) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 4) - 1)) << 14))) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 4) - 1)) << 10))) | ((unsigned int) ((((unsigned int) (0 | 0x2)) & ((0x01 << 2) - 1)) << 8))) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 4) - 1)) << 4))) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 4) - 1)) << 0)); } // FAKE: hand-expanded gbi macro
      ;
      {
        Gfx *_g = (Gfx *) (gDisplayListHead++);
        _g->words.w0 = (((unsigned int) ((((unsigned int) 0xf2) & ((0x01 << 8) - 1)) << 24)) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 12) - 1)) << 12))) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 12) - 1)) << 0)); // FAKE: hand-expanded gbi macro
        _g->words.w1 = (((unsigned int) ((((unsigned int) 0) & ((0x01 << 3) - 1)) << 24)) | ((unsigned int) ((((unsigned int) ((set->width - 1) << 2)) & ((0x01 << 12) - 1)) << 12))) | ((unsigned int) ((((unsigned int) ((set->height - 1) << 2)) & ((0x01 << 12) - 1)) << 0)); // FAKE: hand-expanded gbi macro
      }
      ;
    }
    ;
  }
  {
    Gfx *_g = (Gfx *) (gDisplayListHead++);
    _g->words.w0 = (((unsigned int) ((((unsigned int) 0xe4) & ((0x01 << 8) - 1)) << 24)) | ((unsigned int) ((((unsigned int) lrx) & ((0x01 << 12) - 1)) << 12))) | ((unsigned int) ((((unsigned int) lry) & ((0x01 << 12) - 1)) << 0)); // FAKE: hand-expanded gbi macro
// FAKE: s16 casts on (x << 2) / (y << 2) in the texrect w1 word; they make IDO emit the matching sll/andi order
    _g->words.w1 = (((unsigned int) ((((unsigned int) 0) & ((0x01 << 3) - 1)) << 24)) | ((unsigned int) ((((unsigned int) ((s16) (x << 2))) & ((0x01 << 12) - 1)) << 12))) | ((unsigned int) ((((unsigned int) ((s16) (y << 2))) & ((0x01 << 12) - 1)) << 0));
    { Gfx *_g = (Gfx *) (gDisplayListHead++); _g->words.w0 = (unsigned int) ((((unsigned int) 0xe1) & ((0x01 << 8) - 1)) << 24); _g->words.w1 = (unsigned int) (((unsigned int) ((((unsigned int) 0) & ((0x01 << 16) - 1)) << 16)) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 16) - 1)) << 0))); } // FAKE: hand-expanded gbi macro
    ;
    {
      Gfx *_g = (Gfx *) (gDisplayListHead++);
      _g->words.w0 = (unsigned int) ((((unsigned int) 0xf1) & ((0x01 << 8) - 1)) << 24); // FAKE: hand-expanded gbi macro
      _g->words.w1 = (unsigned int) (((unsigned int) ((((unsigned int) 0x400) & ((0x01 << 16) - 1)) << 16)) | ((unsigned int) ((((unsigned int) 0x400) & ((0x01 << 16) - 1)) << 0))); // FAKE: hand-expanded gbi macro
    }
    ;
  }
  ;
  return (x + set->advance) + font_context->unk_51;
}

/** Copies bytes into a buffer and returns the pointer past the copy. */
char* String_CopyBytesAndAdvance(char* buffer, const char* data, u32 size) {
    return (char*)memcpy(buffer, data, size) + size;
}

s32 func_8001A3E4(s16, s16, s16);
void func_8001A944(s32 x, s32 y, const char* fmt, ...) {
    u8 buf[0x100];
    UNUSED s32 pad; // FAKE: stack padding
    s32 startX;
    s32 len;
    u8* p;
    s32 chr;
    s32 draw;
    va_list args;

    va_start(args, fmt);
    startX = x;
    len = _Printf(String_CopyBytesAndAdvance, (char*)buf, fmt, args);
    if (len > 0) {
        buf[len] = 0;
        chr = buf[0];
        p = &buf[1];
        while (chr != 0) {
            draw = 1;
            if (!(font_context->line_break_flag & 4) && (chr == 0xA)) {
                x = startX;
                draw = 0;
                y += font_context->line_height;
            }
            if (draw) {
                if (chr >= 0x80) {
                    if (*p != 0) {
                        chr = *p | (chr << 8);
                        p++;
                    }
                }
                x = func_8001A3E4(x, y, chr & 0x7F7F);
            }
            chr = *p;
            p++;
        }
    }
    va_end(args);
}

s32 func_8001A3E4(s16, s16, s16);
void func_8001AA60(s32 arg0, s32 arg1, s32 arg2) {
    func_8001A3E4(arg0, arg1, (s16) (arg2 & 0x7F7F));
}

/** Emits a command that sets the RDP environment color. */
void Gfx_SetEnvColor(s32 r, s32 g, s32 b, s32 a) {
    gDPSetEnvColor(gDisplayListHead++, r, g, b, a);
}

/** Emits a command that sets the RDP primitive color. */
void Gfx_SetPrimColor(s32 r, s32 g, s32 b, s32 a) {
    gDPSetPrimColor(gDisplayListHead++, 0, 0, r, g, b, a);
}

extern s8 *D_800AD200;
/** Sets the line height used for text. */
void Font_SetLineHeight(s32 arg0) {
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

/** Begins rendering text with translucency. */
void Font_BeginTranslucentTextRendering(void) {
    font_context->line_break_flag = 0;
    font_context->line_height = 0x28;
    font_context->unk_4C = 0;

    gSPDisplayList(gDisplayListHead++, D_80060950);
}

/** Ends textured text rendering by restoring the default state. */
void Font_EndTexturedTextRendering(void) {
    gSPDisplayList(gDisplayListHead++, D_80060990);
}

/** Enables two-cycle texturing for text. */
void Font_EnableTwoCycleTexturing(void) {
    font_context->line_break_flag |= 1;
    font_context->line_break_flag &= ~2;

    gSPDisplayList(gDisplayListHead++, D_800609A8);
}

extern Gfx D_800609D8[];

/** Disables two-cycle texturing for text. */
void Font_DisableTwoCycleTexturing(void) {
    font_context->line_break_flag &= ~3;
    gSPDisplayList(gDisplayListHead++, D_800609D8);
}

extern Gfx D_80060A00[];
/**
 * Draws a textured rectangle tinted with the given RGBA primitive color.
 * @unverified Name and comment guessed from the code.
 */
void Ui_DrawPrimColorRect(s32 x, s32 y, s32 w, s32 h, s32 r, s32 g, s32 b, s32 a) {
    gSPDisplayList(gDisplayListHead++, D_80060A00);
    gDPSetPrimColor(gDisplayListHead++, 0, 0, r, g, b, a);
    gSPTextureRectangle(gDisplayListHead++, x << 2, y << 2, (x + w) << 2, (y + h) << 2, G_TX_RENDERTILE, 0, 0, 0x1000, 0x0400);
    gDPSetTexturePersp(gDisplayListHead++, G_TP_PERSP);
}

Vtx* func_8001ADA0(s16 x, s16 y, s16 width, s16 height, u8* tex) {
    s16 w = (tex[0] * width) / 100;
    s16 h = (tex[1] * height) / 100;
    Vtx* vtx = Gfx_AllocDisplayList(sizeof(Vtx) * 4);

    Gfx_SetVertexAttributes(&vtx[0], x, y, 0, 0, 0, 0, 0, 0x7F, 0xFF);
    Gfx_SetVertexAttributes(&vtx[1], x, y - h, 0, 0, (tex[1] << 5) - 1, 0, 0, 0x7F, 0xFF);
    Gfx_SetVertexAttributes(&vtx[2], x + w, y - h, 0, (tex[0] << 5) - 1, (tex[1] << 5) - 1, 0, 0, 0x7F, 0xFF);
    Gfx_SetVertexAttributes(&vtx[3], x + w, y, 0, (tex[0] << 5) - 1, 0, 0, 0, 0x7F, 0xFF);
    return vtx;
}

typedef struct Glyph8001AFB0 {
    /* 0x0 */ u8 advance;
    /* 0x1 */ u8 height;
    /* 0x2 */ u8 width;
    /* 0x4 */ u8* file;
} Glyph8001AFB0;
s32 func_80019F70(u16);
s32 func_8001AFB0(Gfx** arg0, s16 x, s16 y, s16 arg3, s16 arg4, u16 chr) {
    Glyph8001AFB0* font = &((Glyph8001AFB0*)font_context)[font_context->unk_50];
    s32 offset = func_80019F70(chr) * font->width * font->height;
    Vtx* vtx = func_8001ADA0(x, y, arg3, arg4, (u8*)font);
    Gfx* dl = Gfx_AllocDisplayList(0xA0);
    Gfx* gfx = dl;

    gDPLoadTextureBlock(gfx++, font->file + offset, G_IM_FMT_IA, G_IM_SIZ_8b, font->width, font->height, 0,
                        G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    gSPVertex(gfx++, vtx, 4, 0);
    gSP2Triangles(gfx++, 0, 1, 2, 0, 0, 2, 3, 0);
    if (*arg0 == NULL) {
        gSPEndDisplayList(gfx++);
    } else {
        gSPBranchList(gfx++, *arg0);
    }
    *arg0 = dl;
    return ((font->advance + font_context->unk_51) * arg3) / 100;
}

/**
 * Builds a small display list in freshly allocated display-list memory:
 * lighting is switched off, textures are enabled with full scale, a two-cycle
 * combiner (TEXEL0 * ENVIRONMENT) is selected, the environment color is set
 * to arg1, the caller's display list
 * arg0 is called, and lighting is switched back on.
 *
 * Note: 0x80 bytes are allocated but only the first 0x40 (eight commands)
 * are written.
 */
Gfx* func_8001B25C(Gfx* arg0, Color_RGBA8_u32 arg1) {
    Gfx* dl = Gfx_AllocDisplayList(0x80);
    Gfx* gfx = dl;

    gDPPipeSync(gfx++);
    gSPClearGeometryMode(gfx++, G_LIGHTING);
    gSPTexture(gfx++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
    gDPSetCombineLERP(gfx++, TEXEL0, 0, ENVIRONMENT, 0, TEXEL0, 0, ENVIRONMENT, 0, 0, 0, 0, COMBINED, 0, 0, 0,
                      COMBINED);
    gDPSetEnvColor(gfx++, arg1.r, arg1.g, arg1.b, arg1.a);
    gSPDisplayList(gfx++, arg0);
    gSPSetGeometryMode(gfx++, G_LIGHTING);
    gSPEndDisplayList(gfx++);
    return dl;
}

typedef struct Glyph8001B32C {
    u8 unk0;
    u8 width;
    u8 unk2[6];
} Glyph8001B32C;

typedef struct Font8001B32C {
    Glyph8001B32C glyphs[7];
    u8 current;
    s8 spacing;
} Font8001B32C;

/**
 * Returns the x position at which `str` starts when centered on x, using the
 * current font's glyph width, spacing and the scale (percent).
 * @unverified Name and comment guessed from the code.
 */
s32 Font_GetCenteredStartX(s32 x, s32 scale, const char* str) {
    s32 width;
    Font8001B32C* font = (Font8001B32C*)D_800AD200;

    width = (font->glyphs[font->current].width + font->spacing) * scale / 100;

    return x - (((strlen(str) >> 1) * width) >> 1);
}

Gfx* func_8001B3AC(s16 x, s16 y, s16 arg2, s16 arg3, Color_RGBA8_u32 color, const char* fmt, ...) {
    u8 buf[0x100];
    UNUSED s32 pad[2]; // FAKE: stack padding
    s32 startX;
    Gfx* dl;
    s32 len;
    u8* p;
    s32 chr;
    va_list args;

    va_start(args, fmt);
    startX = x;
    dl = NULL;
    len = _Printf(String_CopyBytesAndAdvance, (char*)buf, fmt, args);
    if (len > 0) {
        buf[len] = 0;
        chr = buf[0];
        p = &buf[1];
        while (chr != 0) {
            if (chr == 0xA) {
                x = startX;
                y -= ((u8)((FontEntry8001A118*)D_800AD200)[M2C_FIELD(D_800AD200, u8*, 0x38)].size_b * ((arg3 * 0xB) / 10)) / 100;
            } else if (chr == 9) {
                x = Font_GetCenteredStartX(x, arg2, (const char*)p);
            } else {
                if (chr >= 0x80) {
                    if (*p != 0) {
                        chr = *p | (chr << 8);
                        p++;
                    }
                }
                x += func_8001AFB0(&dl, x, y, arg2, arg3, chr & 0x7F7F);
            }
            chr = *p;
            p++;
        }
    }
    if (dl != NULL) {
        dl = func_8001B25C(dl, color);
    }
    va_end(args);
    return dl;
}
