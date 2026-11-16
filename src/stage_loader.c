/* Stadium Zero resident code. */
/* C ported from the Stadium 1 decomp: src/stage_loader.c. */

#include "global.h"
#include "stage_loader.h"
#include "dp_intro.h"
#include "gfx_buffer.h"
#include "memmap.h"
#include "memory_main.h"
#include "profiler.h"
#include "text_renderer.h"
#include "string.h"
#include "stdarg.h"
extern s32 gShowCPUProfiler;
extern s32 gShowMEMProfiler;
extern s32 D_80068C98_Pad[2];
extern QueuedString* D_8005F760;
extern QueuedString* D_8005F764;
extern s32 D_8005F768;
extern s32 D_80068CAC_Pad[1];
extern u32 D_8005F770[];
extern DisplayFrame D_800AA170;
extern StageContext* stage;
extern char pad_D_800A74A8[0x8];
extern Gfx* D_800AA1D0;
s32 StageContext_IsHighResolution(void);
void TextRenderer_FlushQueuedStrings(Gfx**, s32);
void TextRenderer_ClearQueuedStrings(void);

#include "m2c_macros.h"

s32 StageFade_StartFromOpaque(s32 arg0);
s32 StageFade_StartFromTransparent(s32 arg0);
void Profiler_SetDisplayModes(u32 arg0, u32 arg1);
void Gfx_SetDefaultRenderState(void);
void Gfx_SetDefaultGeometryState(void);
void StageLoader_ResetGraphicsState(void);
void StageLoader_SwapDisplayListAndReset(void);
void StageLoader_BeginFrame(void);
void StageLoader_FillFrame(void);
StageContext* StageContext_Allocate(s8 zoom, s8 arg1, s8 render_target_count, s8 has_depth_buffer, s8 arg4, s32 allocate_render_targets);
StageContext* StageContext_GetCurrent(void);
void StageContext_SaveAndSwitch(StageContext* arg0);
void StageContext_Activate(StageContext* arg0);
void StageContext_Deactivate(void);
void StageLoader_WaitForRetrace(void);
void StageLoader_UpdateSegments(void);
s32 BgStage_AdvanceFrame(void);
void StageLoader_RunFrames(s32 timer);
s32 BgStage_RunUntilCondition(u32 timer, s32 (*f)(u8));
s32 BgStage_WaitForCondition(s32 (*arg0)(u8), s32 arg1, s32 arg2);
void StageContext_SetClearColor(u16 color);
GfxImage* StageContext_GetCurrentImage(void);
s32 StageContext_IsHighResolution(void);

s32 StageFade_Start(s32 arg0);
void StageLoader_SetupFrame(void);
void BgStage_DrawFrame(void);

extern Gfx D_8005F728[];
/**
 * Draws the full-screen fade in the stage clear color: opaque in mode 1, fading out in mode 2,
 * fading in in mode 3, over fadeDuration frames. At the end mode 2 drops to 0 (no fade) and mode 3
 * holds at 1 (opaque). Seen in play: the fades between menus come from StageFade_Start.
 */
void StageFade_Draw(void) {
    u8 a;
    u8 b;
    u8 g;
    u8 r;
    StageContext* v0 = stage;

    if (stage->fadeMode == 0) {
        return;
    }

    r = RGBA16_GET_R(stage->clearColor);
    g = RGBA16_GET_G(stage->clearColor);
    b = RGBA16_GET_B(stage->clearColor);

    r = (r << 3) | (r >> 2);
    g = (g << 3) | (g >> 2);
    b = (b << 3) | (b >> 2);

    switch (stage->fadeMode) {
        case 1:
            a = 255;
            break;

        case 2:
            a = (255 - ((stage->fadeFrame * 255) / stage->fadeDuration));
            break;

        case 3:
            a = ((stage->fadeFrame * 255) / stage->fadeDuration);
            break;
    }

    gDPSetEnvColor(gDisplayListHead++, r, g, b, a);
    gSPDisplayList(gDisplayListHead++, D_8005F728);

    if (stage->fadeMode == 1) {
        return;
    }

    stage->fadeFrame++;
    if (stage->fadeFrame == stage->fadeDuration) {
        if (stage->fadeMode == 2) {
            stage->fadeMode = 0;
        } else {
            stage->fadeMode = 1;
        }
    }
}

/**
 * Starts a fade of `duration` frames: from opaque it fades the screen in (mode 2), from clear it
 * fades to the clear color (mode 3). Returns 0 if a fade is already running.
 */
s32 StageFade_Start(s32 duration) {
    s32 var_v1;

    var_v1 = 0;
    if (((stage != NULL) && (stage->fadeMode == 1)) || (stage->fadeMode == 0)) {
        if (stage->fadeMode == 1) {
            stage->fadeMode = 2U;
        } else {
            stage->fadeMode = 3U;
        }
        var_v1 = 1;
        stage->fadeFrame = 0;
        stage->fadeDuration = duration;
    }
    return var_v1;
}

/** Starts a fade in from fully opaque if the stage is in that fade mode. */
s32 StageFade_StartFromOpaque(s32 arg0) {
    s32 ret = 0;

    if ((stage != NULL) && (stage->fadeMode == 1)) {
        ret = StageFade_Start(arg0);
    }

    return ret;
}

/** Starts a fade from fully transparent if the stage is in that fade mode. */
s32 StageFade_StartFromTransparent(s32 arg0) {
    s32 ret = 0;

    if ((stage != NULL) && (stage->fadeMode == 0)) {
        ret = StageFade_Start(arg0);
    }

    return ret;
}

/** Selects which CPU and RDP profiler displays are shown. */
void Profiler_SetDisplayModes(u32 arg0, u32 arg1) {
    if (arg0 < 3) {
        gShowCPUProfiler = arg0;
    }

    if (arg1 < 2) {
        gShowMEMProfiler = arg1;
    }
}

/** Emits display list commands that set the default RDP render state. */
void Gfx_SetDefaultRenderState(void) {
    gDPPipeSync(gDisplayListHead++);
    gDPPipelineMode(gDisplayListHead++, G_PM_1PRIMITIVE);
    gDPSetTextureLOD(gDisplayListHead++, G_TL_TILE);
    gDPSetTextureLUT(gDisplayListHead++, G_TT_NONE);
    gDPSetTextureDetail(gDisplayListHead++, G_TD_CLAMP);
    gDPSetTexturePersp(gDisplayListHead++, G_TP_PERSP);
    gDPSetTextureFilter(gDisplayListHead++, G_TF_BILERP);
    gDPSetTextureConvert(gDisplayListHead++, G_TC_FILT);
    gDPSetCombineKey(gDisplayListHead++, G_CK_NONE);
    gDPSetAlphaCompare(gDisplayListHead++, G_AC_NONE);
    gDPSetColorDither(gDisplayListHead++, G_CD_MAGICSQ);
    gDPSetAlphaDither(gDisplayListHead++, G_AD_PATTERN);
    gDPSetCycleType(gDisplayListHead++, G_CYC_1CYCLE);
    gDPSetRenderMode(gDisplayListHead++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
    gDPSetCombineMode(gDisplayListHead++, G_CC_SHADE, G_CC_SHADE);
    gDPPipeSync(gDisplayListHead++);
}

/** Emits display list commands that set the default RSP geometry state. */
void Gfx_SetDefaultGeometryState(void) {
    gSPClearGeometryMode(gDisplayListHead++, G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN |
                                                 G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH);
    gSPSetGeometryMode(gDisplayListHead++, G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH);
    gSPTexture(gDisplayListHead++, 0, 0, 0, G_TX_RENDERTILE, G_OFF);
}

/** Resets the graphics state and segment map for a new frame. */
void StageLoader_ResetGraphicsState(void) {
    GfxImage_ResetCurrent();
    Memmap_SetSegmentMap(0, 0x80000000, osMemSize);
    Memmap_SetSegments(&gDisplayListHead);
    Gfx_SetDefaultRenderState();
    Gfx_SetDefaultGeometryState();
}

extern Mtx D_800AA188;
extern Mtx D_8005F688;
extern Vp D_8005F6C8;
extern Vp D_8005F6D8;
void StageFade_Draw(void);
void Util_DrawMemoryProfiler(Gfx**);

#ifdef ENGLISH
#include "subtitles_en.h"

// Frames a subtitle stays up after its clip ends, so short clips can be read.
#define SUBTITLE_HOLD_FRAMES 45

extern FontContext* font_context;
void Font_SetActive(s32 mask, s32 arg1);
void Font_BeginTranslucentTextRendering(void);
void Font_EndTexturedTextRendering(void);
void Gfx_SetEnvColor(s32 r, s32 g, s32 b, s32 a);
void Font_Printf(s32 x, s32 y, const char* fmt, ...);
void Ui_DrawPrimColorRect(s32 x, s32 y, s32 w, s32 h, s32 r, s32 g, s32 b, s32 a);
s32 Audio_QueueSetMonoOutputCommand(s32 handle); // despite the name: nonzero while sound `handle` plays
s32 Save_GetOptionFlags(void);
extern void* D_800AE8E0; // the save data the options byte lives in

typedef struct SubtitleFontSet {
    /* 0x0 */ u8 advance;
    /* 0x1 */ u8 height;
    /* 0x2 */ u8 width;
    /* 0x4 */ u8* glyphs;
} SubtitleFontSet; // size = 0x8, one of the six at the start of font_context

extern s32 D_800B41A0; // SYSSFX.WBK's effect table, the system sounds (some play battle samples)
extern s32 D_800B41A4; // BTLSFX.WBK's effect table, the battle sound effects
extern s32 D_800B41A8; // JIKKYOU.WBK's effect table, the announcer

static const char* sSubtitleLine = NULL; // what is being said, NULL for nothing
static s32 sSubtitleHandle = 0;          // its sound handle, for Audio_QueueSetMonoOutputCommand
static s32 sSubtitleHold = 0;
static s32 sSubtitlesOff = 0;

// Called on the audio thread whenever effect `id` of the bank whose effect table is `effects`
// starts playing as sound `handle` (func_8003815C). A sound without a line, such as a hit, leaves
// the subtitle on screen alone.
void Subtitles_OnSound(s32 effects, s32 id, s32 handle) {
    const char* line = NULL;

    if ((handle == 0) || (handle == -1) || (id < 0)) {
        return;
    }
    if ((effects == D_800B41A8) && (id < ARRAY_COUNT(sSubtitleAnnouncer))) {
        line = sSubtitleAnnouncer[id];
    } else if ((effects == D_800B41A4) && (id < ARRAY_COUNT(sSubtitleBattle))) {
        line = sSubtitleBattle[id];
    } else if ((effects == D_800B41A0) && (id < ARRAY_COUNT(sSubtitleSystem))) {
        line = sSubtitleSystem[id];
    }
    if (line != NULL) {
        sSubtitleHandle = handle;
        sSubtitleHold = SUBTITLE_HOLD_FRAMES;
        sSubtitleLine = line;
    }
}

// Draws the line being said on a translucent box in the lower left of the screen, between the
// battle HUD panels and above the battle message box (as in pokestadium-complete), while its sound
// plays and SUBTITLE_HOLD_FRAMES after, with the smallest font set the screen loaded. A screen
// without a font context gets no subtitle.
void Subtitles_Draw(void) {
    const char* line = sSubtitleLine;
    s32 scale = StageContext_IsHighResolution() ? 2 : 1; // 640x480 or 320x240 stage
    SubtitleFontSet* set;
    const char* p;
    s32 index;
    s32 lines;
    s32 line_height;
    s32 height;
    s32 y;

    // The Options screen's Subtitles row: mask 4 of the options byte, set for off. The save data is
    // only in memory on the menus (a battle has none), so the last value seen is kept.
    if (D_800AE8E0 != NULL) {
        sSubtitlesOff = Save_GetOptionFlags() & 4;
    }
    if (line == NULL) {
        return;
    }
    if (Audio_QueueSetMonoOutputCommand(sSubtitleHandle) == 0) {
        if (sSubtitleHold == 0) {
            sSubtitleLine = NULL;
            return;
        }
        sSubtitleHold--;
    }
    if ((font_context == NULL) || sSubtitlesOff) {
        return;
    }
    // Screens select sets they never loaded, and an unloaded slot holds stale pool bytes.
    for (index = 0; index < 6; index++) {
        set = &((SubtitleFontSet*)font_context)[index];
        if (((u32)set->glyphs >= 0x80001000) && ((u32)set->glyphs < 0x803F0000) && (set->height != 0)) {
            break;
        }
    }
    if (index == 6) {
        return;
    }
    line_height = set->height + 1;
    for (lines = 1, p = line; *p != '\0'; p++) {
        if (*p == '\n') {
            lines++;
        }
    }
    height = (lines * line_height) + (6 * scale);
    y = (176 * scale) - height; // the battle message box starts at y 179

    Ui_DrawPrimColorRect(8 * scale, y, 216 * scale, height, 0, 0, 0, 0xA0);
    Font_BeginTranslucentTextRendering();
    Font_SetActive(1 << index, 0);
    font_context->line_height = line_height;
    Gfx_SetEnvColor(0xFF, 0xFF, 0xFF, 0xFF);
    Font_Printf(14 * scale, y + (3 * scale), "%s", line);
    Font_EndTexturedTextRendering();
}
#endif

/** Sets the render target and viewport for the frame. */
void StageLoader_SetupFrame(void) {
    GfxImage_SetRenderTarget(&gDisplayListHead, stage->renderTargets[stage->renderTargetIndex]);
    guOrtho(&D_800AA188, 0.0f, 320.0f, 0.0f, 240.0f, -2.0f, 2.0f, 1.0f);
    Gfx_SetDefaultRenderState();
    Gfx_SetDefaultGeometryState();

    gSPMatrix(gDisplayListHead++, (u32)&D_8005F688 & 0x1FFFFFFF, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPMatrix(gDisplayListHead++, (u32)&D_800AA188 & 0x1FFFFFFF, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    gSPPerspNormalize(gDisplayListHead++, 0xFFFF);

    if (stage->zoom == 1) {
        gSPViewport(gDisplayListHead++, (u32)&D_8005F6D8 & 0x1FFFFFFF);
        gDPSetScissor(gDisplayListHead++, G_SC_NON_INTERLACE, 0, 0, stage->width, stage->height);
    } else {
        gSPViewport(gDisplayListHead++, (u32)&D_8005F6C8 & 0x1FFFFFFF);
        gDPSetScissor(gDisplayListHead++, G_SC_NON_INTERLACE, 0, 0, stage->width, stage->height);
    }

    StageFade_Draw();

    if (gShowCPUProfiler != 0) {
        Profiler_PrintMetrics();
    }

    TextRenderer_FlushQueuedStrings(&gDisplayListHead, StageContext_IsHighResolution());
#ifdef ENGLISH
    Subtitles_Draw(); // on top of everything the stage drew this frame
#endif

    if (gShowCPUProfiler != 0) {
        Profiler_Draw(gShowCPUProfiler - 1);
    }

    if ((gShowCPUProfiler != 0) && (gShowMEMProfiler != 0)) {
        Util_DrawMemoryProfiler(&gDisplayListHead);
    }

    gDPFullSync(gDisplayListHead++);
    gSPEndDisplayList(gDisplayListHead++);

    Gfx_AllocDisplayList(0);
}

/** Swaps the display list buffer and resets graphics state. */
void StageLoader_SwapDisplayListAndReset(void) {
    Gfx_SwapDisplayListBuffer();
    StageLoader_ResetGraphicsState();
}

/** Begins a frame: sets up the render target and the frame parameters. */
void StageLoader_BeginFrame(void) {
    StageLoader_SetupFrame();
    D_800AA170.retracesPerFrame = stage->retracesPerFrame;
    D_800AA170.hiRes = stage->zoom;
    D_800AA170.antiAlias = stage->antiAlias;
    D_800AA170.renderTargetIndex = stage->renderTargetIndex;
    D_800AA170.framebuffer = stage->renderTargets[stage->renderTargetIndex];
    Gfx_GetDisplayListRange(&D_800AA170.dlist, &D_800AA170.dlistSize);
    stage->renderTargetIndex++;
    if (stage->renderTargetIndex == stage->renderTargetCount) {
        stage->renderTargetIndex = 0;
    }
}

/** Draws the stage background over the frame. */
void StageLoader_FillFrame(void) {
    BgStage_DrawFrame();

    gDPPipeSync(gDisplayListHead++);
    gDPSetRenderMode(gDisplayListHead++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
    gDPSetCycleType(gDisplayListHead++, G_CYC_FILL);
    gDPSetFillColor(gDisplayListHead++, (stage->clearColor << 0x10) | stage->clearColor);
    gDPFillRectangle(gDisplayListHead++, stage->clearLeft, stage->clearTop, stage->clearRight,
                     stage->clearBottom);
    gDPPipeSync(gDisplayListHead++);
    gDPSetCycleType(gDisplayListHead++, G_CYC_1CYCLE);
}

/**
 * Allocates a stage context with the given zoom, render targets and depth
 * buffer.
 */
StageContext* StageContext_Allocate(s8 zoom, s8 arg1, s8 render_target_count, s8 has_depth_buffer, s8 arg4, s32 allocate_render_targets) {
    StageContext* temp_v0 = MainPool_Alloc(sizeof(StageContext), 0);

    if (temp_v0 != NULL) {
        if (zoom == 1) {
            temp_v0->width = 640, temp_v0->height = 480;
        } else {
            temp_v0->width = 320, temp_v0->height = 240;
        }

        temp_v0->fadeMode = 1;
        temp_v0->zoom = zoom;
        temp_v0->antiAlias = arg1;
        temp_v0->renderTargetCount = render_target_count;
        temp_v0->hasDepthBuffer = has_depth_buffer;
        temp_v0->retracesPerFrame = arg4;
        temp_v0->clearColor = Display_GetFramebufferClearColor();
        temp_v0->renderTargetIndex = 0;
        temp_v0->clearLeft = 0;
        temp_v0->clearRight = temp_v0->width - 1;
        temp_v0->clearTop = 0;
        temp_v0->clearBottom = temp_v0->height - 1;

        temp_v0->renderTargets[0] = 0;
        temp_v0->renderTargets[1] = 0;
        temp_v0->renderTargets[2] = 0;

        if (allocate_render_targets != 0) {
            s32 i;

            for (i = 0; i < temp_v0->renderTargetCount; i++) {
                temp_v0->renderTargets[i] =
                    GfxImage_Allocate(0, IMAGE_SIZE_BITS_16b, temp_v0->width, temp_v0->height, MEMORY_POOL_RIGHT);
            }

            if (temp_v0->hasDepthBuffer == 1) {
                void* temp_s3 =
                    GfxImage_Allocate(0, IMAGE_SIZE_BITS_16b, temp_v0->width, temp_v0->height, MEMORY_POOL_LEFT);

                for (i = 0; i < temp_v0->renderTargetCount; i++) {
                    GfxImage_AttachDepthBuffer(temp_v0->renderTargets[i], temp_s3);
                }
            }
        }
    }

    return temp_v0;
}

/** Returns the current stage context. */
StageContext* StageContext_GetCurrent(void) {
    return stage;
}

/**
 * Copies the current stage's fade state into another context and makes it
 * current.
 */
void StageContext_SaveAndSwitch(StageContext* arg0) {
    arg0->fadeMode = stage->fadeMode;
    arg0->fadeDuration = stage->fadeDuration;
    arg0->fadeFrame = stage->fadeFrame;
    arg0->clearColor = stage->clearColor;

    if (stage->renderTargetIndex < arg0->renderTargetCount) {
        arg0->renderTargetIndex = stage->renderTargetIndex;
    } else {
        arg0->renderTargetIndex = 0;
    }

    stage = arg0;
}

/** Makes a stage context current, after waiting for the pending frame. */
void StageContext_Activate(StageContext* arg0) {
    stage = arg0;
    Display_QueueFramebufferRequest(NULL);
    Display_WaitForCompletion();
    Display_ClearFramebufferLine(arg0->clearColor);
    StageLoader_SwapDisplayListAndReset();
}

/** Draws a final frame and deactivates the current stage context. */
void StageContext_Deactivate(void) {
    if (stage != NULL) {
        StageLoader_FillFrame();
        StageLoader_BeginFrame();
        Display_QueueFramebufferRequest(&D_800AA170);
        Display_WaitForCompletion();
        Display_WaitForFrames(2);
        stage = NULL;
    }
}

/** Waits until the next frame is ready. */
void StageLoader_WaitForRetrace(void) {
    while (Display_IsFrameReady() == 0) {}
}

/** Emits the segment base commands for the current segment map. */
void StageLoader_UpdateSegments(void) {
    Memmap_SetSegments(&gDisplayListHead);
}

/** Draws one frame and waits for it to complete. */
s32 BgStage_AdvanceFrame(void) {
    StageLoader_BeginFrame();
    Display_QueueFramebufferRequest(&D_800AA170);
    Display_WaitForCompletion();
    StageLoader_SwapDisplayListAndReset();
}

/** Runs the given number of frames. */
void StageLoader_RunFrames(s32 timer) {
    while (timer-- > 0) {
        StageLoader_FillFrame();
        StageLoader_BeginFrame();
        Display_QueueFramebufferRequest(&D_800AA170);
        Display_WaitForCompletion();
        StageLoader_SwapDisplayListAndReset();
    }
}

/**
 * Runs frames until a condition function returns nonzero or the timer expires.
 */
s32 BgStage_RunUntilCondition(u32 timer, s32 (*f)(u8)) {
    s32 var_s1 = 0;

    if (timer == 0) {
        while (var_s1 == 0) {
            var_s1 = f(stage->fadeMode);
            BgStage_AdvanceFrame();
        }
    } else {
        while (timer-- > 0) {
            var_s1 = f(stage->fadeMode);
            BgStage_AdvanceFrame();
            if (var_s1 != 0) {
                break;
            }
        }
    }
    return var_s1;
}

/** Waits for a condition function to hold, with a timeout. */
s32 BgStage_WaitForCondition(s32 (*arg0)(u8), s32 arg1, s32 arg2) {
    s32 temp_v0;
    s32 var_s0;
    s32 var_s2;

    var_s2 = 0;
    var_s0 = 1;
    StageFade_StartFromOpaque(arg1);

    while (var_s0 != 0) {
        temp_v0 = arg0(stage->fadeMode);
        if (var_s2 == 0) {
            if (temp_v0 != 0) {
                var_s2 = temp_v0;
                StageFade_StartFromTransparent(arg2);
            }
        } else if (stage->fadeMode == 1) {
            var_s0 = 0;
        }
        BgStage_AdvanceFrame();
    }

    return var_s2;
}

/** Sets the stage's clear color and clears the framebuffer to it. */
void StageContext_SetClearColor(u16 color) {
    if (stage != NULL) {
        stage->clearColor = color;
        Display_ClearFramebufferLine(color);
    }
}

/** Draws the stage background into the current render target. */
void BgStage_DrawFrame(void) {
    if (stage != NULL) {
        GfxImage_SetRenderTarget(&gDisplayListHead, stage->renderTargets[stage->renderTargetIndex]);
        gDPSetScissor(gDisplayListHead++, G_SC_NON_INTERLACE, stage->clearLeft, stage->clearTop, stage->clearRight + 1, stage->clearBottom + 1);
        gDPSetCycleType(gDisplayListHead++, G_CYC_1CYCLE);
    }
}

/**
 * Returns the current stage's depth buffer image, or NULL when there is no
 * stage.
 */
GfxImage* StageContext_GetCurrentImage(void) {
    GfxImage* ret = NULL;

    if (stage != NULL) {
        ret = stage->renderTargets[stage->renderTargetIndex];
    }

    return ret;
}

/** Returns whether the current stage uses the high-resolution mode. */
s32 StageContext_IsHighResolution(void) {
    s32 ret = 0;

    if (stage != NULL) {
        ret = stage->zoom == 1;
    }

    return ret;
}


/**
 * Clips the rectangle (*x1, *y1)-(*x2, *y2) to the stage's clear area. Returns 1 when something is
 * left, 0 when it is empty or there is no stage.
 */
s32 Stage_ClipRectToClearArea(s32 *x1, s32 *y1, s32 *x2, s32 *y2) {
    s16 temp_v1;
    s16 temp_v1_2;
    s16 temp_v1_3;
    s16 temp_v1_4;
    s32 var_v1;

    if (stage == NULL) {
        return 0;
    }
    temp_v1 = stage->clearLeft;
    if (*x1 < temp_v1) {
        *x1 = (s32) temp_v1;
    }
    temp_v1_2 = stage->clearRight;
    if (temp_v1_2 < *x2) {
        *x2 = (s32) temp_v1_2;
    }
    temp_v1_3 = stage->clearTop;
    if (*y1 < temp_v1_3) {
        *y1 = (s32) temp_v1_3;
    }
    temp_v1_4 = stage->clearBottom;
    if (temp_v1_4 < *y2) {
        *y2 = (s32) temp_v1_4;
    }
    var_v1 = *x2 >= *x1;
    if (var_v1 != 0) {
        var_v1 = *y2 >= *y1;
    }
    return var_v1;
}
