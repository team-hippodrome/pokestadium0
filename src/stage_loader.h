/* Declarations for src/stage_loader.c. */
#ifndef STAGE_LOADER_H
#define STAGE_LOADER_H

#include "global.h"
#include "stdarg.h"
#include "moves.h"
#include "m2c_macros.h"
#include <ultra64.h>
#include <macros.h>
#include "gfx_rect.h"

typedef struct StageContext {
    /* 0x00 */ s16 width;
    /* 0x02 */ s16 height;
    /* 0x04 */ s16 clearLeft;
    /* 0x06 */ s16 clearRight;
    /* 0x08 */ s16 clearTop;
    /* 0x0A */ s16 clearBottom;
    /* 0x0C */ s8 zoom; // 1 selects 640x480; other values select 320x240.
    /* 0x0D */ s8 antiAlias; // @unverified: copied to DisplayFrame.antiAlias, the column of the VI mode table D_8005F664; 1 in every caller
    /* 0x0E */ s8 renderTargetCount; // Number of slots used in renderTargets.
    /* 0x0F */ s8 hasDepthBuffer;
    /* 0x10 */ s8 retracesPerFrame; // @unverified: copied to DisplayFrame.retracesPerFrame; 2 in most screens, 1 in the GB Tower team prep
    /* 0x11 */ u8 fadeMode; // 0 transparent, 1 opaque, 2 fading in, 3 fading out.
    /* 0x12 */ u8 fadeDuration;
    /* 0x13 */ u8 fadeFrame;
    /* 0x14 */ u16 clearColor; // RGBA5551 framebuffer clear/fade color.
    /* 0x16 */ s8 renderTargetIndex; // Current target; advances after recording the frame request.
    /* 0x17 */ u8 pad17;
    // Color-buffer descriptors with optional depth buffers. StageLoader_SetupFrame
    // selects their img_p as the RDP color destination through gDPSetColorImage.
    union {
        /* 0x18 */ GfxImage* renderTargets[3];
        /* 0x18 */ GfxImage* unk_18[3];
    };
} StageContext; // size = 0x24

typedef StageContext unk_func_80007444;

#define MEMORY_POOL_LEFT  0

#define MEMORY_POOL_RIGHT 1

/* Struct types that were defined identically in each of these files; this is
 * now the one definition they all include:
 * src/stage_loader.c
 * src/stage_loader_2.c
 */

// A string queued by HAL_Printf or TextRenderer_QueuePersistentString.
typedef struct QueuedString {
    /* 0x00 */ struct QueuedString* next; // @unverified: list link walked by the string queue draw
    /* 0x04 */ s16 x; // @unverified: TextRenderer_DrawString x
    /* 0x06 */ s16 y; // @unverified: TextRenderer_DrawString y
    /* 0x08 */ s8 text[4]; // @unverified: NUL-terminated string, allocated past the struct end (HAL_Printf)
} QueuedString;

// stage_loader.c
s32 StageFade_StartFromOpaque(s32 arg0);
s32 StageFade_StartFromTransparent(s32 arg0);
void Profiler_SetDisplayModes(u32 arg0, u32 arg1);
void Gfx_SetDefaultRenderState(void);
void Gfx_SetDefaultGeometryState(void);
void StageLoader_ResetGraphicsState(void);
void StageLoader_SetupFrame(void);
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
void BgStage_DrawFrame(void);                            /* extern */
M2C_UNK func_80006780();                            /* extern */
M2C_UNK func_800067BC(M2C_UNK);                     /* extern */

// functions defined in assembly
s32 StageFade_Start(s32 arg0);

#endif // STAGE_LOADER_H
