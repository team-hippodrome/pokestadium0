/* Stadium Zero resident code. */
/* C ported from the Stadium 1 decomp: src/stage_loader.c. */

#include "global.h"
#include "stage_loader.h"
#include "memory.h"
#include "string.h"
#include "dp_intro.h"
#include "gfx_rect.h"
#include "gfx_buffer.h"
#include "memmap.h"
#include "util.h"
#include "profiler.h"
#include "stdarg.h"
#include "stage_loader_types.h"
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
DepthBuffer* StageContext_GetCurrentImage(void);
s32 StageContext_IsHighResolution(void);

s32 StageFade_Start(s32 arg0);
void StageLoader_SetupFrame(void);
void BgStage_DrawFrame(void);

extern Gfx D_8005F728[];
void func_80005980(void) {
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

extern s8 *D_800AA184;
s32 func_80005B98(s32 arg0) {
    s32 var_v1;

    var_v1 = 0;
    if (((D_800AA184 != NULL) && (M2C_FIELD(D_800AA184, u8 *, 0x11) == 1)) || (M2C_FIELD(D_800AA184, u8 *, 0x11) == 0)) {
        if (M2C_FIELD(D_800AA184, u8 *, 0x11) == 1) {
            M2C_FIELD(D_800AA184, u8 *, 0x11) = 2U;
        } else {
            M2C_FIELD(D_800AA184, u8 *, 0x11) = 3U;
        }
        var_v1 = 1;
        M2C_FIELD(D_800AA184, s8 *, 0x13) = 0;
        M2C_FIELD(D_800AA184, s8 *, 0x12) = arg0;
    }
    return var_v1;
}

s32 StageFade_StartFromOpaque(s32 arg0) {
    s32 ret = 0;

    if ((stage != NULL) && (stage->fadeMode == 1)) {
        ret = StageFade_Start(arg0);
    }

    return ret;
}

s32 StageFade_StartFromTransparent(s32 arg0) {
    s32 ret = 0;

    if ((stage != NULL) && (stage->fadeMode == 0)) {
        ret = StageFade_Start(arg0);
    }

    return ret;
}

void Profiler_SetDisplayModes(u32 arg0, u32 arg1) {
    if (arg0 < 3) {
        gShowCPUProfiler = arg0;
    }

    if (arg1 < 2) {
        gShowMEMProfiler = arg1;
    }
}

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

void Gfx_SetDefaultGeometryState(void) {
    gSPClearGeometryMode(gDisplayListHead++, G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN |
                                                 G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH);
    gSPSetGeometryMode(gDisplayListHead++, G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH);
    gSPTexture(gDisplayListHead++, 0, 0, 0, G_TX_RENDERTILE, G_OFF);
}

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
void func_80005980(void);
void func_80002EC8(Gfx**);

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

    func_80005980();

    if (gShowCPUProfiler != 0) {
        print_profiler_metrics();
    }

    TextRenderer_FlushQueuedStrings(&gDisplayListHead, StageContext_IsHighResolution());

    if (gShowCPUProfiler != 0) {
        draw_profiler(gShowCPUProfiler - 1);
    }

    if ((gShowCPUProfiler != 0) && (gShowMEMProfiler != 0)) {
        func_80002EC8(&gDisplayListHead);
    }

    gDPFullSync(gDisplayListHead++);
    gSPEndDisplayList(gDisplayListHead++);

    Gfx_AllocDisplayList(0);
}

void StageLoader_SwapDisplayListAndReset(void) {
    Gfx_SwapDisplayListBuffer();
    StageLoader_ResetGraphicsState();
}

void StageLoader_BeginFrame(void) {
    StageLoader_SetupFrame();
    D_800AA170.unk_00 = stage->unk_10;
    D_800AA170.zoom = stage->zoom;
    D_800AA170.unk_02 = stage->unk_0D;
    D_800AA170.unk_03 = stage->renderTargetIndex;
    D_800AA170.unk_0C = stage->renderTargets[stage->renderTargetIndex];
    Gfx_GetDisplayListRange(&D_800AA170.unk_04, &D_800AA170.unk_08);
    stage->renderTargetIndex++;
    if (stage->renderTargetIndex == stage->renderTargetCount) {
        stage->renderTargetIndex = 0;
    }
}

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

StageContext* StageContext_Allocate(s8 zoom, s8 arg1, s8 render_target_count, s8 has_depth_buffer, s8 arg4, s32 allocate_render_targets) {
    StageContext* temp_v0 = main_pool_alloc(sizeof(StageContext), 0);

    if (temp_v0 != NULL) {
        if (zoom == 1) {
            temp_v0->width = 0x280, temp_v0->height = 0x1E0;
        } else {
            temp_v0->width = 0x140, temp_v0->height = 0xF0;
        }

        temp_v0->fadeMode = 1;
        temp_v0->zoom = zoom;
        temp_v0->unk_0D = arg1;
        temp_v0->renderTargetCount = render_target_count;
        temp_v0->hasDepthBuffer = has_depth_buffer;
        temp_v0->unk_10 = arg4;
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

StageContext* StageContext_GetCurrent(void) {
    return stage;
}

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

void StageContext_Activate(StageContext* arg0) {
    stage = arg0;
    Display_QueueFramebufferRequest(NULL);
    Display_WaitForCompletion();
    Display_ClearFramebufferLine(arg0->clearColor);
    StageLoader_SwapDisplayListAndReset();
}

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

void StageLoader_WaitForRetrace(void) {
    while (Display_IsFrameReady() == 0) {}
}

void StageLoader_UpdateSegments(void) {
    Memmap_SetSegments(&gDisplayListHead);
}

s32 BgStage_AdvanceFrame(void) {
    StageLoader_BeginFrame();
    Display_QueueFramebufferRequest(&D_800AA170);
    Display_WaitForCompletion();
    StageLoader_SwapDisplayListAndReset();
}

void StageLoader_RunFrames(s32 timer) {
    while (timer-- > 0) {
        StageLoader_FillFrame();
        StageLoader_BeginFrame();
        Display_QueueFramebufferRequest(&D_800AA170);
        Display_WaitForCompletion();
        StageLoader_SwapDisplayListAndReset();
    }
}

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

void StageContext_SetClearColor(u16 color) {
    if (stage != NULL) {
        stage->clearColor = color;
        Display_ClearFramebufferLine(color);
    }
}

void BgStage_DrawFrame(void) {
    if (stage != NULL) {
        GfxImage_SetRenderTarget(&gDisplayListHead, stage->renderTargets[stage->renderTargetIndex]);
        gDPSetScissor(gDisplayListHead++, G_SC_NON_INTERLACE, stage->clearLeft, stage->clearTop, stage->clearRight + 1, stage->clearBottom + 1);
        gDPSetCycleType(gDisplayListHead++, G_CYC_1CYCLE);
    }
}

DepthBuffer* StageContext_GetCurrentImage(void) {
    DepthBuffer* ret = NULL;

    if (stage != NULL) {
        ret = stage->renderTargets[stage->renderTargetIndex];
    }

    return ret;
}

s32 StageContext_IsHighResolution(void) {
    s32 ret = 0;

    if (stage != NULL) {
        ret = stage->zoom == 1;
    }

    return ret;
}

extern s8 *D_800AA184;

s32 func_80006B50(s32 *arg0, s32 *arg1, s32 *arg2, s32 *arg3) {
    s16 temp_v1;
    s16 temp_v1_2;
    s16 temp_v1_3;
    s16 temp_v1_4;
    s32 var_v1;

    if (D_800AA184 == NULL) {
        return 0;
    }
    temp_v1 = M2C_FIELD(D_800AA184, s16 *, 4);
    if (*arg0 < temp_v1) {
        *arg0 = (s32) temp_v1;
    }
    temp_v1_2 = M2C_FIELD(D_800AA184, s16 *, 6);
    if (temp_v1_2 < *arg2) {
        *arg2 = (s32) temp_v1_2;
    }
    temp_v1_3 = M2C_FIELD(D_800AA184, s16 *, 8);
    if (*arg1 < temp_v1_3) {
        *arg1 = (s32) temp_v1_3;
    }
    temp_v1_4 = M2C_FIELD(D_800AA184, s16 *, 0xA);
    if (temp_v1_4 < *arg3) {
        *arg3 = (s32) temp_v1_4;
    }
    var_v1 = *arg2 >= *arg0;
    if (var_v1 != 0) {
        var_v1 = *arg3 >= *arg1;
    }
    return var_v1;
}
