/* Stadium Zero resident code. */
/* C ported from the Stadium 1 decomp: src/stage_loader.c. */

#include "global.h"
#include "text_renderer.h"
#include "stage_loader.h"
#include "util.h"
#include "string.h"
#include "stdarg.h"
extern s32 gShowCPUProfiler;
extern s32 gShowMEMProfiler;
extern s32 D_80068C98_Pad[2];
extern unk_D_80068CA0* D_8005F760;
extern unk_D_80068CA0* D_8005F764;
extern s32 D_8005F768;
extern s32 D_80068CAC_Pad[1];
extern u32 D_8005F770[];
extern unk_D_800A7450 D_800AA170;
extern StageContext* stage;
extern char pad_D_800A74A8[0x8];
extern Gfx* D_800AA1D0;
s32 StageContext_IsHighResolution(void);
void TextRenderer_FlushQueuedStrings(Gfx**, s32);
void TextRenderer_ClearQueuedStrings(void);

void TextRenderer_SetupGlyphState(void);
void TextRenderer_RestoreState(void);
void TextRenderer_DrawGlyphSmall(s16 arg0, s16 arg1, s16 arg2);
void TextRenderer_DrawGlyphLarge(s16 arg0, s16 arg1, s16 arg2);
void TextRenderer_DrawString(s16 arg0, s16 arg1, s8* arg2, s32 arg3);
void TextRenderer_FlushQueuedStrings(Gfx** arg0, s32 arg1);
void TextRenderer_ClearQueuedStrings(void);
char* TextRenderer_FormatCopy(char* buffer, const char* data, size_t size);
s32 HAL_Printf(s16 x, s16 y, const char* fmt, ...);
s32 TextRenderer_QueuePersistentString(s16 x, s16 y, const char* fmt, ...);

/** Sets the render state for drawing glyphs. */
void TextRenderer_SetupGlyphState(void) {
    gDPPipeSync(D_800AA1D0++);
    gDPSetCycleType(D_800AA1D0++, G_CYC_1CYCLE);
    gDPSetTexturePersp(D_800AA1D0++, G_TP_NONE);
    gDPSetTextureFilter(D_800AA1D0++, G_TF_POINT);
    gDPSetPrimColor(D_800AA1D0++, 0, 0, 255, 255, 255, 255); // #FFFFFFFF
    gDPSetRenderMode(D_800AA1D0++, G_RM_TEX_EDGE, G_RM_TEX_EDGE2);
    gDPSetCombineMode(D_800AA1D0++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
    gDPLoadTextureBlock_4b(D_800AA1D0++, (u32)D_8005F770 & 0x1FFFFFFF, G_IM_FMT_IA, 96, 48, 0,
                           G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, 7, 6, G_TX_NOLOD, G_TX_NOLOD);
}

/** Restores the render state after drawing glyphs. */
void TextRenderer_RestoreState(void) {
    gDPPipeSync(D_800AA1D0++);
    gDPSetTexturePersp(D_800AA1D0++, G_TP_PERSP);
    gDPSetTextureFilter(D_800AA1D0++, G_TF_BILERP);
    gDPSetAlphaCompare(D_800AA1D0++, G_AC_NONE);
    gSPTexture(D_800AA1D0++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF);
}

/** Draws a small glyph at a position. */
void TextRenderer_DrawGlyphSmall(s16 arg0, s16 arg1, s16 arg2) {
    gSPTextureRectangle(D_800AA1D0++, arg0 * 4, arg1 * 4, (arg0 + 6) << 2, (arg1 + 8) << 2, G_TX_RENDERTILE,
                        ((arg2 % 16) * 6) << 5, (u16)(arg2 / 16) << 8, 0x0400, 0x0400);
}

/** Draws a large glyph at a position. */
void TextRenderer_DrawGlyphLarge(s16 arg0, s16 arg1, s16 arg2) {
    gSPTextureRectangle(D_800AA1D0++, arg0 * 8, arg1 * 8, (arg0 + 6) << 3, (arg1 + 8) << 3, G_TX_RENDERTILE,
                        ((arg2 % 16) * 6) << 5, (u16)(arg2 / 16) << 8, 0x0200, 0x0200);
}

/** Draws a string at a position. */
void TextRenderer_DrawString(s16 arg0, s16 arg1, s8* arg2, s32 arg3) {
    s32 temp_s0;

    while (*arg2 != 0) {
        temp_s0 = (*arg2++ & 0x7F) - 0x20;
        if (temp_s0 != 0) {
            if (arg3 == 0) {
                TextRenderer_DrawGlyphSmall(arg0, arg1, temp_s0);
            }

            if (arg3 == 1) {
                TextRenderer_DrawGlyphLarge(arg0, arg1, temp_s0);
            }
        }
        arg0 += 6;
    }
}

/** Draws and clears the queued strings. */
void TextRenderer_FlushQueuedStrings(Gfx** arg0, s32 arg1) {
    unk_D_80068CA0* var_s0 = D_8005F760;
    unk_D_80068CA0* var_s2 = D_8005F764;

    D_800AA1D0 = *arg0;

    if ((var_s0 != NULL) || (var_s2 != NULL)) {
        TextRenderer_SetupGlyphState();

        while (var_s0 != NULL) {
            unk_D_80068CA0* next = var_s0->next;

            TextRenderer_DrawString(var_s0->unk_04, var_s0->unk_06, var_s0->unk_08, arg1);
            Util_Free(var_s0);
            var_s0 = next;
        }

        while (var_s2 != NULL) {
            TextRenderer_DrawString(var_s2->unk_04, var_s2->unk_06, var_s2->unk_08, arg1);
            var_s2 = var_s2->next;
        }

        TextRenderer_RestoreState();
        D_8005F760 = NULL;
    }

    *arg0 = D_800AA1D0;

    D_8005F768++;
    if (D_8005F768 >= 0x384) {
        D_8005F768 = 0;
        if (D_8005F764 != NULL) {
            TextRenderer_ClearQueuedStrings();
        }
    }
}

/** Clears the queue of strings. */
void TextRenderer_ClearQueuedStrings(void) {
    unk_D_80068CA0* var_s0 = D_8005F764;

    while (var_s0 != NULL) {
        unk_D_80068CA0* next = var_s0->next;

        Util_Free(var_s0);
        var_s0 = next;
    }

    D_8005F764 = NULL;
}

/** Copies formatted bytes into a buffer and returns the pointer past them. */
char* TextRenderer_FormatCopy(char* buffer, const char* data, size_t size) {
    return (char*)memcpy(buffer, data, size) + size;
}

/** Formats text and draws it at a position. */
s32 HAL_Printf(s16 x, s16 y, const char* fmt, ...) {
    s32 sp124;
    char sp20[0x104];
    unk_D_80068CA0* sp1C;
    va_list args;

    va_start(args, fmt);

    sp124 = _Printf(TextRenderer_FormatCopy, sp20, fmt, args);

    if (sp124 > 0) {
        sp1C = Util_Malloc(sp124 + sizeof(unk_D_80068CA0));
        if (sp1C != NULL) {
            sp1C->unk_04 = x;
            sp1C->unk_06 = y;
            memcpy(sp1C->unk_08, &sp20, sp124);
            sp1C->unk_08[sp124] = 0;
            sp1C->next = D_8005F760;
            D_8005F760 = sp1C;
        }
    }

    va_end(args);

    return sp124;
}

/** Formats text and queues it to be drawn each frame. */
s32 TextRenderer_QueuePersistentString(s16 x, s16 y, const char* fmt, ...) {
    s32 sp124;
    char sp20[0x104];
    unk_D_80068CA0* sp1C;
    va_list args;

    va_start(args, fmt);

    D_8005F768 = 0;
    sp124 = _Printf(TextRenderer_FormatCopy, sp20, fmt, args);
    if (sp124 > 0) {
        sp1C = Util_Malloc(sp124 + sizeof(unk_D_80068CA0));
        if (sp1C != NULL) {
            sp1C->unk_04 = x;
            sp1C->unk_06 = y;
            memcpy(sp1C->unk_08, &sp20, sp124);
            sp1C->unk_08[sp124] = 0;
            sp1C->next = D_8005F764;
            D_8005F764 = sp1C;
        }
    }

    va_end(args);

    return sp124;
}
