/* Stadium Zero resident code. */
/* C ported from the Stadium 1 decomp: src/battle_hud.c. */

#include "battle_hud.h"
#include "model_renderer_callbacks.h"
#include "geo_render.h"
#include "util.h"
#include "memmap.h"
#include "fragments/particle_data_library/particle_data_library.h"
extern s32 D_800AFB20;
extern s16 D_800AFB24;

void ModelAnim_UpdateFrameChangeState(void);
s32 ModelPhase_IsIdle(void);
u8 ModelRenderer_GetActiveMode(void);
void Gfx_SetCombineMode(Gfx* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 arg10, s32 arg11, s32 arg12, s32 arg13, s32 arg14, s32 arg15, s32 arg16);

/** Records whether the geo render frame counter changed since the last update. */
void ModelAnim_UpdateFrameChangeState(void) {
    D_800AFB24 = (D_800AFB20 == D_80060484) ? 1 : 0;
    D_800AFB20 = D_80060484;
}

/** Returns whether the model phase is idle; always 0. */
s32 ModelPhase_IsIdle(void) {
    return 0;
}

/** Returns the active effect mode of the current model renderer slot. */
u8 ModelRenderer_GetActiveMode(void) {
    u8 ret = *(u8*)Memmap_GetSegmentVaddr(&D_8006049C->effectSlot);
    return ret;
}

extern s16 D_800AF7AE;
extern s16 D_800AFB26;
extern s16 D_800AFB30[];
extern u8 D_8100060C[];

void func_800325B0(u32 arg0) {
    void (*func)(u32);

    D_800AFB26 = 0;
    D_800AFB30[arg0 & 1] = 0;
    if (arg0 < 2) {
        ModelRenderer_ClearSlotModels(arg0);
        func = Util_ConvertAddrToVirtAddr(D_8100060C);
        func(arg0);
    }
}

extern s16 D_800AF7B0[2];
extern s16 D_800AFB28;
extern u8 D_8100065C[];
/** Updates the animation of a display object. */
void ModelAnim_UpdateDisplayObjectAnimation(u32 arg0, u32 arg1) {
    s32 (*func)(void);

    D_800AFB28 = 0;
    func = Util_ConvertAddrToVirtAddr(D_8100065C);
    func();

    if (arg0 < 2) {
        switch (D_800AFB30[arg0]) {
            default:
                D_800AFB30[arg0] = 1;
                return;
            case 0:
                D_800AFB30[arg0] = 1;
                return;
            case 1:
                D_800AFB30[arg0] = 2;
                return;
            case 2:
                D_800AFB30[arg0] = 3;
                break;
            case 3:
                break;
        }
    }
}

extern s16 D_800AF7B4[2];
extern s16 D_800AFB2C[2];
/** Finalizes the animation update of a display object. */
void ModelAnim_FinalizeDisplayObjectAnimation(u32 arg0, u32 arg1) {
    if (ModelPhase_IsIdle() == 0) {
        D_800AFB26++;
    }

    if ((arg1 != 0) && (arg0 < 2)) {
        if (D_800AFB28 == 0) {
            D_800AFB2C[arg0] = 0;
        } else {
            D_800AFB2C[arg0] = 1;
        }
    }
}

/** Writes a color combiner setting from its individual terms. */
void Gfx_SetCombineMode(Gfx* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 arg10, s32 arg11, s32 arg12, s32 arg13, s32 arg14, s32 arg15, s32 arg16) {
    gDPSetCombine(arg0++, GCCc0w0(arg1, arg3, arg5, arg7) | GCCc1w0(arg9, arg11), GCCc0w1(arg2, arg4, arg6, arg8) | GCCc1w1(arg10, arg13, arg15, arg12, arg14, arg16));
}
