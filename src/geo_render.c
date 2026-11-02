/* Stadium Zero resident code. */
/* C ported from the Stadium 1 decomp: src/geo_render.c, src/model_animation.c, src/model_animation_events.c. */

#include "geo_render.h"
#include "geo_render.h"
#include "graphics_textures.h"
#include "graphics_textures.h"
#include "model_animation.h"
#include "model_animation_events.h"
#include "gfx_buffer.h"
#include "gfx_rect.h"
#include "battle_hud.h"
#include "matrix.h"
#include "memmap.h"
#include "util.h"
#include "variables.h"
typedef void (*func_D_8006F0A4)(GraphNode* arg0);
typedef struct unk_D_800AA8C8 {
    /* 0x0000 */ MtxF unk_0000[64];
    /* 0x1000 */ MtxF* unk_1000[32];
    /* 0x1080 */ s8 unk_1080[32];
    /* 0x10A0 */ s32 unk_10A0;
} unk_D_800AA8C8;
extern s32 D_80060480;
extern u16 D_80060484;
extern CameraNode* D_80060488;
extern unk_D_86002F34_alt1* D_8006048C;
extern unk_D_86002F34_alt1* D_80060490;
extern CameraNode* D_80060494;
extern unk_D_86002F34_alt1* D_80060498;
extern DisplayObject* D_8006049C;
extern func_D_8006F0A4 D_8006062C[];
extern s32 D_800AB244;
extern u8 pad_D_800AA6E8[0x1E0];
extern unk_D_800AA8C8 D_800AB460;
extern unk_D_800AB970 D_800AC508;
#pragma SWAP_FUNCTION_WORDS(func_80011D14, 0xD0, 0xAFB80024, 0x00063403)

#include "model_animation.h"
#include "util.h"
#include "matrix.h"
#include "model_animation_events.h"
typedef struct unk_func_80016B30_arg0 {
    /* 0x00 */ Vec3s vec;
    /* 0x06 */ s16 unk_06;
} unk_func_80016B30_arg0;
typedef union AnimFixedFrame {
    struct {
        s16 whole;
        s16 fraction; // low 16 bits; signed declaration retained for matching
    };
    s32 raw;
} AnimFixedFrame;
typedef struct TransformAnimRaw {
    /* 0x00 */ s16 animationId;
    /* 0x04 */ TransformAnimData* data;
    /* 0x08 */ AnimFixedFrame frameFixed;
    /* 0x0C */ s32 speedFixed;
    /* 0x10 */ char unk10[0x2];
    /* 0x12 */ u16 lastRenderFrame;
} TransformAnimRaw;

#include "model_animation_events.h"
#include "util.h"

#include "m2c_macros.h"

void GeoRender_InitMatrixStack(void);
void GeoRender_CommitMatrix(void);
void GeoRender_SetMatrix(MtxF* arg0);
void GeoRender_PushMultipliedMatrix(MtxF* arg0);
void GeoRender_PushScaledMatrix(Vec3f* arg0);
MtxF* GeoRender_GetRelativeMatrix(s32 arg0);
void GeoRender_ResetTransformStack(void);
void GeoRender_PushScale(Vec3f* arg0);
f32 ModelAnim_EvaluateTranslationChannel(unk_D_800ABCC0* arg0, s32 arg1);
s16 ModelAnim_EvaluateRotationChannel(unk_D_800ABCC0* arg0, s32 arg1);
s32 ModelAnim_ResolveEventIndex(s32 arg0, unk_func_80017540_arg1* arg1, s32 arg2);
Vtx* GeoOverlay_BuildFadeQuad(CameraOverlay* arg0, CameraOrthographic* arg1);
void GeoOverlay_DrawFadeQuad(CameraOverlay* arg0, CameraOrthographic* arg1);
Vtx* GeoOverlay_BuildRotatingQuad(CameraOverlay* arg0);
void GeoOverlay_DrawRotatingQuad(CameraOverlay* arg0, UNUSED CameraOrthographic* arg1);
void GeoOverlay_Draw(CameraOverlay* arg0, CameraOrthographic* arg1);
void GeoRender_SetCombineMode(Gfx* arg0, arg1_func_81407874_014_000_010* arg1);
void Geo_ProcessNodeChildren(GraphNode* arg0);
void Geo_NodeReference(GraphNode* arg0);
void Geo_NodeCamera(GraphNode* arg0);
void Geo_NodeType3Pass(GraphNode* arg0);
void Geo_NodeOrtho(GraphNode* arg0);
void Geo_NodePerspective(GraphNode* arg0);
void Geo_NodeBackground(GraphNode* arg0);
void Geo_NodeClearDepth(UNUSED GraphNode* arg0);
void Geo_NodeType9Empty(UNUSED GraphNode* arg0);
void Geo_NodeType12Empty(UNUSED GraphNode* arg0);
void Geo_NodeSwitchCase(GraphNode* arg0);
void Geo_NodeTranslateRotate(GraphNode* arg0);
void Geo_NodeTranslate(GraphNode* arg0);
void GeoRender_RecordAnchorPosition(s32 arg0);
void Geo_NodeAnchor(GraphNode* arg0);
void Geo_RenderRootNode(GraphNode* node);
void Geo_ProcessCallbacks(GraphNode* arg0, s32 arg1);
void GeoRender_SetMode(s32 arg0);
void GeoRender_AdvanceFrameCounter(void);
s32 GeoRender_IsModelFrameCurrent(void);
Vec3f* GeoRender_FindAnchorPosition(DisplayObject* display_object, s16 lookup_id, Vec3f* dest);

void func_80011D14(Vtx* arg0, CameraOverlay* arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5, s16 arg6,
                   s16 arg7);
void Geo_NodeModelPartRoot(GraphNode* arg0);

void GeoRender_InitMatrixStack(void) {
    D_800AB460.unk_10A0 = 0;
    D_800AB460.unk_1080[0] = 0;
    MtxF_Identity(&D_800AB460.unk_0000[0]);
    D_800AB460.unk_1000[0] = Gfx_AllocDisplayList(sizeof(Mtx) * 1);
    MtxF_ToFixed(D_800AB460.unk_1000[0], D_800AB460.unk_0000);
}

void GeoRender_CommitMatrix(void) {
    D_800AB460.unk_1080[D_800AB460.unk_10A0] = 0;
    D_800AB460.unk_1000[D_800AB460.unk_10A0] = Gfx_AllocDisplayList(sizeof(MtxF) * 1);
    MtxF_ToFixed(D_800AB460.unk_1000[D_800AB460.unk_10A0], &D_800AB460.unk_0000[D_800AB460.unk_10A0]);
}

void GeoRender_SetMatrix(MtxF* arg0) {
    MtxF_Copy(&D_800AB460.unk_0000[D_800AB460.unk_10A0], arg0);
    D_800AB460.unk_1080[D_800AB460.unk_10A0] = 0;
    D_800AB460.unk_1000[D_800AB460.unk_10A0] = Gfx_AllocDisplayList(sizeof(MtxF) * 1);
    MtxF_ToFixed(D_800AB460.unk_1000[D_800AB460.unk_10A0], &D_800AB460.unk_0000[D_800AB460.unk_10A0]);
}

void GeoRender_PushMultipliedMatrix(MtxF* arg0) {
    MtxF* temp_a0;

    D_800AB460.unk_10A0++;
    temp_a0 = &D_800AB460.unk_0000[D_800AB460.unk_10A0];

    MtxF_Multiply(&temp_a0[0], arg0, &temp_a0[-1]);
    D_800AB460.unk_1080[D_800AB460.unk_10A0] = 0;
    D_800AB460.unk_1000[D_800AB460.unk_10A0] = Gfx_AllocDisplayList(sizeof(MtxF) * 1);
    MtxF_ToFixed(D_800AB460.unk_1000[D_800AB460.unk_10A0], &D_800AB460.unk_0000[D_800AB460.unk_10A0]);
}

void GeoRender_PushScaledMatrix(Vec3f* arg0) {
    MtxF* temp_a0;

    D_800AB460.unk_10A0++;
    temp_a0 = &D_800AB460.unk_0000[D_800AB460.unk_10A0];

    MtxF_ScaleRows(&temp_a0[0], &temp_a0[-1], arg0);

    D_800AB460.unk_1080[D_800AB460.unk_10A0] = 0;
    D_800AB460.unk_1000[D_800AB460.unk_10A0] = Gfx_AllocDisplayList(sizeof(MtxF) * 1);

    MtxF_ToFixed(D_800AB460.unk_1000[D_800AB460.unk_10A0], &D_800AB460.unk_0000[D_800AB460.unk_10A0]);
}

MtxF* GeoRender_GetRelativeMatrix(s32 arg0) {
    MtxF* var_v1 = NULL;

    if (arg0 <= 0) {
        var_v1 = &(&D_800AB460.unk_0000[D_800AB460.unk_10A0])[arg0];
    }

    return var_v1;
}

void GeoRender_ResetTransformStack(void) {
    D_800AC508.unk_180 = 0;
    D_800AC508.unk_000[0] = D_80060464;
}

void GeoRender_PushScale(Vec3f* arg0) {
    D_800AC508.unk_000[D_800AC508.unk_180 + 1].x = D_800AC508.unk_000[D_800AC508.unk_180].x * arg0->x;
    D_800AC508.unk_000[D_800AC508.unk_180 + 1].y = D_800AC508.unk_000[D_800AC508.unk_180].y * arg0->y;
    D_800AC508.unk_000[D_800AC508.unk_180 + 1].z = D_800AC508.unk_000[D_800AC508.unk_180].z * arg0->z;

    D_800AC508.unk_180++;
}

extern s32 D_800ABCF0;
extern unk_D_800ABCC0 D_800ABCC0[2];
/*
 * func_8001148C
 *
 * Fills the global record D_800AC690 from the object `arg0` and the data
 * block arg0->unk_4 (`temp_s1`):
 *
 *   - if arg1 != 0, arg0->unk_8 = func_80011774(arg0) first;
 *   - arg0->unk_12 (halfword at 0x12) = D_80060484;
 *   - D_800AC690[0] = 1;  D_800AC690[1] = first halfword of the block & 4;
 *     D_800AC690 word 4 = the block pointer;
 *     D_800AC690 halfword 2 = (arg0->unk_8) >> 16, clamped to 0 if negative;
 *   - D_800AC690 words 8, 0xC, 0x10, 0x14 = func_80002C80 of the block's
 *     words at 0xC, 0x10, 0x14, 0x18.
 *
 * What the record is used for is not established; func_80011774 and
 * func_80002C80 are not described here.
 */
s32 func_80002C80(s32);
s32 func_80011774(TransformAnimRaw* arg0);
extern u8 D_800AC690;

void func_8001148C(void *arg0, s32 arg1) {
    s16 *temp_s1;

    temp_s1 = M2C_FIELD(arg0, s16 **, 4);
    if (arg1 != 0) {
        M2C_FIELD(arg0, s32 *, 8) = func_80011774((TransformAnimRaw*)arg0);
    }
    M2C_FIELD(arg0, u16 *, 0x12) = (u16) D_80060484;
    M2C_FIELD(&D_800AC690, s8 *, 0) = 1;
    M2C_FIELD(&D_800AC690, s8 *, 1) = (s8) (*M2C_FIELD(arg0, s16 **, 4) & 4);
    M2C_FIELD(&D_800AC690, s16 *, 2) = (s16) ((s32) M2C_FIELD(arg0, s32 *, 8) >> 0x10);
    M2C_FIELD(&D_800AC690, s16 **, 4) = temp_s1;
    M2C_FIELD(&D_800AC690, s32 *, 8) = func_80002C80(M2C_FIELD(temp_s1, s32 *, 0xC));
    M2C_FIELD(&D_800AC690, s32 *, 0xC) = func_80002C80(M2C_FIELD(temp_s1, s32 *, 0x10));
    M2C_FIELD(&D_800AC690, s32 *, 0x10) = func_80002C80(M2C_FIELD(temp_s1, s32 *, 0x14));
    M2C_FIELD(&D_800AC690, s32 *, 0x14) = func_80002C80(M2C_FIELD(temp_s1, s32 *, 0x18));
    if (M2C_FIELD(&D_800AC690, s16 *, 2) < 0) {
        M2C_FIELD(&D_800AC690, s16 *, 2) = 0;
    }
}

f32 ModelAnim_EvaluateTranslationChannel(unk_D_800ABCC0* arg0, s32 arg1) {
    f32 ret;
    s32 var_a2;
    unk_D_800ABCC0_008* temp_v0 = &arg0->unk_08[arg1];

    if (temp_v0->unk_00 == 1) {
        ret = temp_v0->unk_04 / 1000.0f;
    } else {
        if (arg0->unk_02 < temp_v0->unk_00) {
            var_a2 = temp_v0->unk_04 + arg0->unk_02;
        } else {
            var_a2 = (temp_v0->unk_04 + temp_v0->unk_00) - 1;
        }

        ret = arg0->unk_0C[var_a2] / 1000.0f;
    }

    return ret;
}

s16 ModelAnim_EvaluateRotationChannel(unk_D_800ABCC0* arg0, s32 arg1) {
    s32 var_a1;
    s16 var_v1;
    unk_D_800ABCC0_008* temp_v0 = &arg0->unk_08[arg1];

    if (temp_v0->unk_01 == 1) {
        var_v1 = temp_v0->unk_06 * 0x10;
    } else {
        if (arg0->unk_02 < temp_v0->unk_01) {
            var_a1 = temp_v0->unk_06 + arg0->unk_02;
        } else {
            var_a1 = (temp_v0->unk_06 + temp_v0->unk_01) - 1;
        }
        var_v1 = PackedBits_ReadSigned(arg0->unk_10, var_a1, 0xC) * 0x10;
    }
    return var_v1;
}

f32 ModelAnim_EvaluateScaleChannel(unk_D_800ABCC0* arg0, s32 arg1) {
    f32 var_fv1;
    s16 var_a2;
    s32 var_a1;
    unk_D_800ABCC0_008* temp_v0 = &arg0->unk_08[arg1];

    if (temp_v0->unk_02 == 1) {
        if (arg0->unk_01 != 0) {
            var_fv1 = (s16)temp_v0->unk_08;
        } else {
            var_a2 = temp_v0->unk_08 * 0x10;
            var_fv1 = var_a2 >> 4;
        }
    } else {
        if (arg0->unk_02 < temp_v0->unk_02) {
            var_a1 = temp_v0->unk_08 + arg0->unk_02;
        } else {
            var_a1 = (temp_v0->unk_08 + temp_v0->unk_02) - 1;
        }

        if (arg0->unk_01 != 0) {
            var_fv1 = PackedBits_ReadSigned(arg0->unk_14, var_a1, 0x10);
        } else {
            var_fv1 = PackedBits_ReadSigned(arg0->unk_14, var_a1, 0xC);
        }
    }

    return var_fv1;
}

s32 func_80011774(TransformAnimRaw* arg0) {
    AnimFixedFrame spC;
    AnimFixedFrame* ptr;
    TransformAnimData* temp_v0;

    ptr = &spC;
    temp_v0 = arg0->data;
    spC.raw = arg0->frameFixed.raw;
    if (arg0->lastRenderFrame != D_80060484) {
        spC.raw += arg0->speedFixed;
        if (arg0->speedFixed >= 0) {
            if (ptr->whole >= temp_v0->endFrame) {
                if (temp_v0->flags & 2) {
                    ptr->whole = temp_v0->endFrame - 1;
                } else {
                    ptr->whole = temp_v0->loopStart;
                }
            }
        } else {
            if (ptr->whole < temp_v0->loopStart) {
                if (temp_v0->flags & 2) {
                    ptr->whole = temp_v0->loopStart;
                } else {
                    ptr->whole = temp_v0->endFrame - 1;
                }
            }
        }
    }

    return spC.raw;
}

#ifdef NON_MATCHING
/* TODO: decompile func_80011838; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_80011838.s")
#endif

s32 ModelAnim_ResolveEventIndex(s32 arg0, unk_func_80017540_arg1* arg1, s32 arg2) {
    unk_func_80017540_arg1* temp_v0 = &arg1[arg2];
    s32 ret;

    if (arg0 < temp_v0->unk_00) {
        ret = arg0 + temp_v0->unk_02;
    } else {
        ret = (temp_v0->unk_02 + temp_v0->unk_00) - 1;
    }
    return ret;
}

s16 ModelAnim_AdvanceEventFrame(EventTrackState* arg0) {
    s16 var_v1;
    EventTrackData* temp_v0;

    var_v1 = arg0->frame;
    temp_v0 = arg0->data;

    if (arg0->lastRenderFrame != D_80060484) {
        var_v1 += 1;
        if (var_v1 >= temp_v0->endFrame) {
            if (temp_v0->flags & 2) {
                var_v1 = temp_v0->endFrame - 1;
            } else {
                var_v1 = temp_v0->loopStart;
            }
        }
    }
    return var_v1;
}

Vtx* GeoOverlay_BuildFadeQuad(CameraOverlay* arg0, CameraOrthographic* arg1) {
    u8 sp47;
    Vtx* temp_v0 = Gfx_AllocDisplayList(sizeof(Vtx) * 4);

    if (temp_v0 != NULL) {
        switch (arg0->mode) {
            case 1:
                sp47 = 0xFF;
                break;

            case 2:
                sp47 = 0xFF - ((arg0->stepIndex * 0xFF) / arg0->stepCount);
                break;

            case 3:
                sp47 = (arg0->stepIndex * 0xFF) / arg0->stepCount;
                break;
        }

        Gfx_SetVertexAttributes(&temp_v0[0], arg1->unk_04, arg1->unk_10, -1, 0, 0, arg0->color.r, arg0->color.g, arg0->color.b, sp47);
        Gfx_SetVertexAttributes(&temp_v0[1], arg1->unk_04, arg1->unk_0C, -1, 0, 0, arg0->color.r, arg0->color.g, arg0->color.b, sp47);
        Gfx_SetVertexAttributes(&temp_v0[2], arg1->unk_08, arg1->unk_0C, -1, 0, 0, arg0->color.r, arg0->color.g, arg0->color.b, sp47);
        Gfx_SetVertexAttributes(&temp_v0[3], arg1->unk_08, arg1->unk_10, -1, 0, 0, arg0->color.r, arg0->color.g, arg0->color.b, sp47);
    }

    return temp_v0;
}

void GeoOverlay_DrawFadeQuad(CameraOverlay* arg0, CameraOrthographic* arg1) {
    Vtx* temp_v0 = GeoOverlay_BuildFadeQuad(arg0, arg1);

    if (temp_v0 != NULL) {
        gDPSetCombineMode(gDisplayListHead++, G_CC_SHADE, G_CC_SHADE);
        gDPSetRenderMode(gDisplayListHead++, G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2);

        gSPVertex(gDisplayListHead++, (u32)temp_v0 & 0x1FFFFFFF, 4, 0);
        gSP2Triangles(gDisplayListHead++, 0, 1, 2, 0, 0, 2, 3, 0);
    }

    if (arg0->mode != 1) {
        arg0->stepIndex++;
        if (arg0->stepIndex == arg0->stepCount) {
            if (arg0->mode == 2) {
                arg0->mode = 0;
            } else {
                arg0->mode = 1;
            }
        }
    }
}

#ifdef NON_MATCHING
/* TODO: decompile func_80011D14; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_80011D14.s")
#endif

Vtx* GeoOverlay_BuildRotatingQuad(CameraOverlay* arg0) {
    Vtx* temp_v0 = Gfx_AllocDisplayList(sizeof(Vtx) * 8);
    Vtx* temp_s0;
    s16 temp_s2;
    s16 temp_s4;
    s16 temp_s5;

    if (temp_v0 != NULL) {
        temp_s0 = temp_v0;

        temp_s4 = arg0->unk_10 + (((arg0->unk_14 - arg0->unk_10) * arg0->stepIndex) / arg0->stepCount);
        temp_s5 = arg0->unk_12 + (((arg0->unk_16 - arg0->unk_12) * arg0->stepIndex) / arg0->stepCount);
        temp_s2 = arg0->unk_0C + (((arg0->unk_0E - arg0->unk_0C) * arg0->stepIndex) / arg0->stepCount);

        if (arg0->mode == 2) {
            func_80011D14(temp_s0++, arg0, temp_s4, temp_s5, -temp_s2, -temp_s2, -0x1F, 0x3F);
            func_80011D14(temp_s0++, arg0, temp_s4, temp_s5, temp_s2, -temp_s2, 0x1F, 0x3F);
            func_80011D14(temp_s0++, arg0, temp_s4, temp_s5, temp_s2, temp_s2, 0x1F, 0);
            func_80011D14(temp_s0++, arg0, temp_s4, temp_s5, -temp_s2, temp_s2, -0x1F, 0);
        } else {
            func_80011D14(temp_s0++, arg0, temp_s4, temp_s5, -temp_s2, -temp_s2, 0, 0x3F);
            func_80011D14(temp_s0++, arg0, temp_s4, temp_s5, temp_s2, -temp_s2, 0x3F, 0x3F);
            func_80011D14(temp_s0++, arg0, temp_s4, temp_s5, temp_s2, temp_s2, 0x3F, 0);
            func_80011D14(temp_s0++, arg0, temp_s4, temp_s5, -temp_s2, temp_s2, 0, 0);
        }

        func_80011D14(temp_s0++, arg0, temp_s4, temp_s5, -0x7D0, -0x7D0, 0, 0);
        func_80011D14(temp_s0++, arg0, temp_s4, temp_s5, 0x7D0, -0x7D0, 0, 0);
        func_80011D14(temp_s0++, arg0, temp_s4, temp_s5, 0x7D0, 0x7D0, 0, 0);
        func_80011D14(temp_s0++, arg0, temp_s4, temp_s5, -0x7D0, 0x7D0, 0, 0);
    }

    arg0->unk_18 += arg0->unk_1A;
    return temp_v0;
}

void GeoOverlay_DrawRotatingQuad(CameraOverlay* arg0, UNUSED CameraOrthographic* arg1) {
    Vtx* temp_v0 = GeoOverlay_BuildRotatingQuad(arg0);

    if (temp_v0 != 0) {
        gDPSetCombineMode(gDisplayListHead++, G_CC_SHADE, G_CC_SHADE);
        gDPSetRenderMode(gDisplayListHead++, G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2);

        gSPVertex(gDisplayListHead++, (u32)temp_v0 & 0x1FFFFFFF, 8, 0);
        gSP2Triangles(gDisplayListHead++, 0, 4, 1, 0, 1, 4, 5, 0);
        gSP2Triangles(gDisplayListHead++, 1, 5, 2, 0, 2, 5, 6, 0);
        gSP2Triangles(gDisplayListHead++, 2, 6, 7, 0, 2, 7, 3, 0);
        gSP2Triangles(gDisplayListHead++, 3, 4, 0, 0, 3, 7, 4, 0);

        gDPPipeSync(gDisplayListHead++);

        gDPSetCombineMode(gDisplayListHead++, G_CC_MODULATEIDECALA, G_CC_MODULATEIDECALA);
        gDPSetRenderMode(gDisplayListHead++, G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2);
        gDPSetTextureFilter(gDisplayListHead++, G_TF_BILERP);

        if (arg0->unk_02 == 0) {
            gDPLoadTextureBlock(gDisplayListHead++, arg0->unk_1C, G_IM_FMT_IA, G_IM_SIZ_8b, 64, 64, 0,
                                G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, 6, 6, G_TX_NOLOD, G_TX_NOLOD);
        } else {
            gDPLoadTextureBlock(gDisplayListHead++, arg0->unk_1C, G_IM_FMT_IA, G_IM_SIZ_8b, 32, 64, 0,
                                G_TX_MIRROR | G_TX_WRAP, G_TX_MIRROR | G_TX_WRAP, 5, 6, G_TX_NOLOD, G_TX_NOLOD);
        }

        gSPTexture(gDisplayListHead++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);

        gSPVertex(gDisplayListHead++, (u32)temp_v0 & 0x1FFFFFFF, 4, 0);
        gSP2Triangles(gDisplayListHead++, 0, 1, 2, 0, 0, 2, 3, 0);

        gSPTexture(gDisplayListHead++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF);
        gDPSetTextureFilter(gDisplayListHead++, G_TF_BILERP);
    }

    arg0->stepIndex++;
    if (arg0->stepIndex == arg0->stepCount) {
        if (arg0->mode == 4) {
            arg0->mode = 0;
        } else {
            arg0->mode = 1;
        }
    }
}

void GeoOverlay_Draw(CameraOverlay* arg0, CameraOrthographic* arg1) {
    if (arg0->mode != 0) {
        gDPPipeSync(gDisplayListHead++);

        gDPSetCycleType(gDisplayListHead++, G_CYC_1CYCLE);
        gSPClearGeometryMode(gDisplayListHead++, G_ZBUFFER | G_LIGHTING);
        gSPPerspNormalize(gDisplayListHead++, 0xFFFF);
        gSPMatrix(gDisplayListHead++, (u32)arg1->unk_00 & 0x1FFFFFFF, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
        gSPMatrix(gDisplayListHead++, (u32)&gIdentityMtx & 0x1FFFFFFF, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

        if ((arg0->mode == 1) || (arg0->mode == 2) || (arg0->mode == 3)) {
            GeoOverlay_DrawFadeQuad(arg0, arg1);
        } else {
            GeoOverlay_DrawRotatingQuad(arg0, arg1);
        }

        gDPPipeSync(gDisplayListHead++);
        gDPSetCycleType(gDisplayListHead++, G_CYC_2CYCLE);
    }
}

void GeoRender_SetCombineMode(Gfx* arg0, arg1_func_81407874_014_000_010* arg1) {
    gDPSetCombine(arg0++,
                  GCCc0w0(arg1->unk_00, arg1->unk_02, arg1->unk_04, arg1->unk_06) | GCCc1w0(arg1->unk_08, arg1->unk_0A),

                  GCCc0w1(arg1->unk_01, arg1->unk_03, arg1->unk_05, arg1->unk_07) |
                      GCCc1w1(arg1->unk_09, arg1->unk_0C, arg1->unk_0E, arg1->unk_0B, arg1->unk_0D, arg1->unk_0F));
}

#ifdef NON_MATCHING
/* TODO: decompile func_800128E0; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_800128E0.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_8001298C; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_8001298C.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_80012A80; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_80012A80.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_80012C00; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_80012C00.s")
#endif

M2C_UNK func_8001298C();                            /* extern */

void func_80012CC0(s8 *arg0, s8 *arg1) {
    if (M2C_FIELD(arg0, s32 *, 8) & 0xFF) {
        func_8001298C();
    }
    M2C_FIELD(arg0, s32 *, 8) = (s32) M2C_FIELD(arg1, s32 *, 0x14);
}

#ifdef NON_MATCHING
/* TODO: decompile func_80012D04; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_80012D04.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_80012DC8; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_80012DC8.s")
#endif

/*
 * func_80012E68
 *
 * If the word at arg0 + 0x0C is non-zero, appends a G_TEXTURE command with
 * both scales 0xFFFF and the texture off (gSPTexture(..., 0xFFFF, 0xFFFF, 0,
 * G_TX_RENDERTILE, G_OFF)) to the display list. Then clears the words at
 * arg0 + 0x0C, + 0x10 and + 0x14. The second argument is not used (retail only
 * spills it to its stack home).
 */
void func_80012E68(s32* arg0, s32 arg1) {
    if (arg0[3] != 0) {
        gSPTexture(gDisplayListHead++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF);
    }
    arg0[3] = 0;
    arg0[4] = 0;
    arg0[5] = 0;
}

extern s16 D_8006F2A4[];
extern unk_D_800ABB28* D_800ABCB8;
extern s16 D_80060624[];

void GeoRender_BindTexture(unk_D_800ABB28* arg0, unk_D_800ABB10* arg1) {
    unk_D_86002F34_alt11_018* temp_t0;
    s32 var_a3;

    if (M2C_FIELD(arg0, void**, 0xC) == NULL) {
        gSPTexture(gDisplayListHead++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
    }

    if ((M2C_FIELD(arg0, void**, 0xC) != M2C_FIELD(arg1, void**, 0x18)) || (M2C_FIELD(arg0, Gfx**, 0x14) != M2C_FIELD(arg1, Gfx**, 0x20))) {
        temp_t0 = M2C_FIELD(arg1, unk_D_86002F34_alt11_018**, 0x18);
        if (M2C_FIELD(arg1, void**, 0x1C) != NULL) {
            gSPDisplayList(gDisplayListHead++, M2C_FIELD(M2C_FIELD(arg1, void**, 0x1C), Gfx**, 8));
        } else {
            gDPSetTextureLUT(gDisplayListHead++, G_TT_NONE);
        }

        if (temp_t0->unk_01 == 0) {
            if ((temp_t0->unk_02 % D_80060624[0]) == 0) {
                gDPSetTextureImage(gDisplayListHead++, temp_t0->fmt, G_IM_SIZ_16b, 1, temp_t0->texture);
            } else {
                gDPSetTextureImage(gDisplayListHead++, temp_t0->fmt, G_IM_SIZ_8b, temp_t0->unk_02 >> 1,
                                   temp_t0->texture);
            }
        } else if ((temp_t0->unk_02 % D_80060624[temp_t0->unk_01]) == 0) {
            if (temp_t0->unk_01 == 3) {
                var_a3 = 3;
            } else {
                var_a3 = 2;
            }

            gDPSetTextureImage(gDisplayListHead++, temp_t0->fmt, var_a3, 1, temp_t0->texture);
        } else {
            gDPSetTextureImage(gDisplayListHead++, temp_t0->fmt, temp_t0->unk_01, temp_t0->unk_02, temp_t0->texture);
        }

        gSPDisplayList(gDisplayListHead++, M2C_FIELD(arg1, Gfx**, 0x20));
    }

    M2C_FIELD(arg0, void**, 0xC) = M2C_FIELD(arg1, void**, 0x18);
    M2C_FIELD(arg0, void**, 0x10) = M2C_FIELD(arg1, void**, 0x1C);
    M2C_FIELD(arg0, void**, 0x14) = M2C_FIELD(arg1, void**, 0x20);
}

extern unk_D_800ABB28* D_800ABCB8;
#ifdef NON_MATCHING
/* TODO: decompile func_80013148; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_80013148.s")
#endif

/*
 * func_800132C8
 *
 * Emits display-list commands for one object, `arg1`. `*arg0` caches the
 * last matrix address handled: when arg1's word at offset 0xC differs from
 * it, the cache is updated and a gSPMatrix (G_MTX_NOPUSH | G_MTX_LOAD |
 * G_MTX_MODELVIEW) for that address masked to a physical address is
 * emitted. Then arg1's word at offset 8 is emitted as a gSPDisplayList
 * target; if it lies in 0x81000000..0x8FFFFFFF (the fragment address range)
 * it is first run through Memmap_GetFragmentVaddr. The meaning of the two
 * fields is inferred from how they are used, not from a declaration.
 * Matching note: the extra registers m2c shows as arguments to the
 * Memmap_GetFragmentVaddr call are leftovers, not arguments.
 */
void func_800132C8(s32* arg0, void* arg1) {
    if (*arg0 != M2C_FIELD(arg1, s32*, 0xC)) {
        *arg0 = M2C_FIELD(arg1, s32*, 0xC);
        gSPMatrix(gDisplayListHead++, M2C_FIELD(arg1, u32*, 0xC) & 0x1FFFFFFF, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    }
    if ((M2C_FIELD(arg1, u32*, 8) >= 0x81000000U) && (M2C_FIELD(arg1, u32*, 8) < 0x90000000U)) {
        gSPDisplayList(gDisplayListHead++, Memmap_GetFragmentVaddr(M2C_FIELD(arg1, void**, 8)));
    } else {
        gSPDisplayList(gDisplayListHead++, M2C_FIELD(arg1, u32*, 8));
    }
}

#ifdef NON_MATCHING
/* TODO: decompile func_80013398; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_80013398.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_800135FC; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_800135FC.s")
#endif

void Geo_ProcessNodeChildren(GraphNode* arg0) {
    GraphNode* temp_s2 = arg0->children;
    GraphNode* var_s0 = temp_s2;

    if (temp_s2 != NULL) {
        do {
            if (var_s0->flags & 1) {
                D_800AB244 = 0;
                if (var_s0->callback != NULL) {
                    D_800AB244 = var_s0->callback(2, var_s0);
                }
                D_8006062C[var_s0->type](var_s0);
            }
            var_s0 = var_s0->nextSibling;
        } while (var_s0 != temp_s2);
    }
}

void Geo_NodeReference(GraphNode* arg0) {
    UNUSED s32 pad;
    GraphNode* temp_a1 = ((unk_D_86002F34*)arg0)->unk_18;

    if ((temp_a1 != NULL) && (temp_a1->flags & 1)) {
        D_800AB244 = 0;
        if (temp_a1->callback != NULL) {
            D_800AB244 = temp_a1->callback(2, temp_a1);
        }
        D_8006062C[temp_a1->type](temp_a1);
    }

    Geo_ProcessNodeChildren(arg0);
}

void Geo_NodeCamera(GraphNode* arg0) {
    UNUSED MtxF pad_mtx;
    CameraNode* arg = (CameraNode*)arg0;
    CameraOrthographic* temp_s2 = &arg->orthographic;
    CameraView* temp_s1 = &arg->view;
    CameraPerspective* sp48 = &arg->perspective;
    CameraViewport* temp_s0 = &arg->viewport;

    temp_s0->rspViewport = Gfx_AllocDisplayList(sizeof(Vp) * 1);
    temp_s2->unk_00 = Gfx_AllocDisplayList(sizeof(Mtx) * 1);
    sp48->projectionMatrix = Gfx_AllocDisplayList(sizeof(MtxF) * 1);
    temp_s1->fixedMatrix = Gfx_AllocDisplayList(sizeof(MtxF) * 1);
    temp_s1->unk_44 = Gfx_AllocDisplayList(sizeof(LookAt) * 1);

    temp_s0->rspViewport->vp.vtrans[0] = (temp_s0->x * 4) + (temp_s0->width * 2);
    temp_s0->rspViewport->vp.vtrans[1] = (temp_s0->y * 4) + (temp_s0->height * 2);
    temp_s0->rspViewport->vp.vtrans[2] = 0x1FF;

    temp_s0->rspViewport->vp.vscale[0] = temp_s0->width * 2;
    temp_s0->rspViewport->vp.vscale[1] = temp_s0->height * 2;
    temp_s0->rspViewport->vp.vscale[2] = 0x1FF;

    gSPViewport(gDisplayListHead++, (u32)temp_s0->rspViewport & 0x1FFFFFFF);
    gDPSetScissorFrac(gDisplayListHead++, G_SC_NON_INTERLACE, temp_s0->x * 4.0f, temp_s0->y * 4.0f,
                      (temp_s0->x + temp_s0->width) * 4.0f, (temp_s0->y + temp_s0->height) * 4.0f);

    guOrtho(temp_s2->unk_00, temp_s2->unk_04, temp_s2->unk_08, temp_s2->unk_0C, temp_s2->unk_10, temp_s2->unk_14, temp_s2->unk_18, temp_s2->unk_1C);
    guPerspective(sp48->projectionMatrix, &sp48->unk_04, sp48->verticalFieldOfView, sp48->unk_0C, sp48->nearPlane, sp48->farPlane, sp48->unk_18);
    guLookAtReflectF(&temp_s1->floatMatrix, temp_s1->unk_44, temp_s1->eyePosition.x, temp_s1->eyePosition.y, temp_s1->eyePosition.z, temp_s1->targetPosition.x,
                     temp_s1->targetPosition.y, temp_s1->targetPosition.z, temp_s1->upDirection.x, temp_s1->upDirection.y, temp_s1->upDirection.z);
    MtxF_ToFixed(temp_s1->fixedMatrix, &temp_s1->floatMatrix);

    D_80060488 = arg;
    if ((arg->overlay.mode != 1) && (arg->node.children != NULL)) {
        Geo_ProcessNodeChildren(&arg->node);
    }
    GeoOverlay_Draw(&arg->overlay, temp_s2);
    Gfx_ApplyScissorRect(&gDisplayListHead);
    D_80060488 = NULL;
}

void Geo_NodeType3Pass(GraphNode* arg0) {
    D_8006048C = arg0;
    Geo_ProcessNodeChildren(arg0);
    D_8006048C = NULL;
}

extern u8 D_800AC690;
extern u8 D_800AC6A8;

void Geo_NodeModelRoot(GraphNode* arg0) {
    unk_D_86002F34_alt1* arg = (unk_D_86002F34_alt1*)arg0;

    if (arg->node.children != NULL) {
        arg->unk_1D = 0;
        arg->lights = Gfx_AllocDisplayList(sizeof(Lights7));
        arg->unk_1C = 0;
        arg->lights->a.l.col[0] = 0;
        arg->lights->a.l.col[1] = 0;
        arg->lights->a.l.col[2] = 0;

        gSPClearGeometryMode(gDisplayListHead++, G_ZBUFFER | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING |
                                                     G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH);
        gSPSetGeometryMode(gDisplayListHead++, G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH);
        gSPTexture(gDisplayListHead++, 0, 0, 0, G_TX_RENDERTILE, G_OFF);
        gDPSetCycleType(gDisplayListHead++, G_CYC_2CYCLE);

        D_800AC690 = 0;
        D_800AC6A8 = 0;
        GeoRender_InitMatrixStack();
        GeoRender_ResetTransformStack();

        gSPMatrix(gDisplayListHead++, (u32)D_800AB460.unk_1000[D_800AB460.unk_10A0] & 0x1FFFFFFF,
                  G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

        D_80060490 = arg;
        Geo_ProcessNodeChildren(arg0);
        D_80060490 = NULL;
    }

    arg->unk_1A = D_80060484;
}

#ifdef NON_MATCHING
/* TODO: decompile func_80013DC8; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_80013DC8.s")
#endif

void Geo_NodeOrtho(GraphNode* arg0) {
    if ((D_80060494 == NULL) && (arg0->children != NULL)) {
        gSPPerspNormalize(gDisplayListHead++, 0xFFFF);
        gSPMatrix(gDisplayListHead++, (u32)D_80060488->orthographic.unk_00 & 0x1FFFFFFF,
                  G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);

        Geo_NodeModelPartRoot(arg0);
    }
}

void Geo_NodePerspective(GraphNode* arg0) {
    if ((D_80060494 == NULL) && (arg0->children != NULL)) {
        gSPLookAt(gDisplayListHead++, (u32)&D_80060488->view.unk_44->l & 0x1FFFFFFF);

        gSPPerspNormalize(gDisplayListHead++, D_80060488->perspective.unk_04);

        gSPMatrix(gDisplayListHead++, (u32)D_80060488->perspective.projectionMatrix & 0x1FFFFFFF,
                  G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
        gSPMatrix(gDisplayListHead++, (u32)D_80060488->view.fixedMatrix & 0x1FFFFFFF,
                  G_MTX_NOPUSH | G_MTX_MUL | G_MTX_PROJECTION);

        Geo_NodeModelPartRoot(arg0);
    }
}

void Geo_NodeBackground(GraphNode* arg0) {
    unk_D_86002F34_alt2* arg = (unk_D_86002F34_alt2*)arg0;
    CameraViewport* ptr = &D_80060488->viewport;

    GfxImage_FillRectangle(&gDisplayListHead, ptr->x, ptr->y, ptr->width, ptr->height, arg->unk_18);

    gDPPipeSync(gDisplayListHead++);
    gDPSetCycleType(gDisplayListHead++, G_CYC_2CYCLE);
}

void Geo_NodeClearDepth(UNUSED GraphNode* arg0) {
    CameraViewport* ptr = &D_80060488->viewport;

    GfxImage_ClearDepthRectangle(&gDisplayListHead, ptr->x, ptr->y, ptr->width, ptr->height);

    gDPPipeSync(gDisplayListHead++);
    gDPSetCycleType(gDisplayListHead++, G_CYC_2CYCLE);
}

void Geo_NodeType9Empty(UNUSED GraphNode* arg0) {
}

void func_80014164(GraphNode* arg0) {
    unk_D_86002F34_alt3* arg = (unk_D_86002F34_alt3*)arg0;

    D_80060490->unk_1D = 1;

    gSPFogPosition(gDisplayListHead++, arg->unk_18, arg->unk_1A);
    gSPSetGeometryMode(gDisplayListHead++, G_FOG);
    gDPSetColor(gDisplayListHead++, G_SETFOGCOLOR, arg->unk_1C);
}

void func_8001426C(GraphNode* arg0) {
    unk_D_86002F34_alt4* arg = (unk_D_86002F34_alt4*)arg0;
    Light* light;
    Ambient* ambient;

    if (D_80060490->unk_1C >= 7) {
        return;
    }

    light = &D_80060490->lights->l[D_80060490->unk_1C];
    ambient = &D_80060490->lights->a;

    *(u32*)light->l.col = arg->unk_18.rgba;
    *(u32*)light->l.colc = arg->unk_18.rgba;

    light->l.dir[0] = (120.0f * COSS(arg->unk_1C)) * SINS(arg->unk_1E);
    light->l.dir[1] = (120.0f) * SINS(arg->unk_1C);
    light->l.dir[2] = (120.0f * COSS(arg->unk_1C)) * COSS(arg->unk_1E);

    ambient->l.col[0] += ((arg->unk_18.r * arg->unk_18.a) / 100);
    if (ambient->l.col[0] > 0xFF) {
        ambient->l.col[0] = 0xFF;
    }

    ambient->l.col[1] += ((arg->unk_18.g * arg->unk_18.a) / 100);
    if (ambient->l.col[1] > 0xFF) {
        ambient->l.col[1] = 0xFF;
    }

    ambient->l.col[2] += ((arg->unk_18.b * arg->unk_18.a) / 100);
    if (ambient->l.col[2] > 0xFF) {
        ambient->l.col[2] = 0xFF;
    }

    D_80060490->unk_1C++;
}

void Geo_NodeType12Empty(UNUSED GraphNode* arg0) {
}

void Geo_NodeAmbientLight(GraphNode* arg0) {
    unk_D_86002F34_alt4* arg = (unk_D_86002F34_alt4*)arg0;
    s32 i;
    Lights7* lights;

    lights = D_80060490->lights;
    if ((arg->unk_18.r == 0xFF) && (arg->unk_18.g == 0xFF) && (arg->unk_18.b == 0xFF)) {
        lights->a.l.colc[0] = lights->a.l.col[0];
        lights->a.l.colc[1] = lights->a.l.col[1];
        lights->a.l.colc[2] = lights->a.l.col[2];
    } else {
        lights->a.l.colc[0] = lights->a.l.col[0] = arg->unk_18.r;
        lights->a.l.colc[1] = lights->a.l.col[1] = arg->unk_18.g;
        lights->a.l.colc[2] = lights->a.l.col[2] = arg->unk_18.b;
    }

    gSPSetGeometryMode(gDisplayListHead++, G_LIGHTING);
    gMoveWd(gDisplayListHead++, 2, 0, D_80060490->unk_1C * 0x18);

    for (i = 0; i < D_80060490->unk_1C; i++) {
        gSPLight(gDisplayListHead++, &D_80060490->lights->l[i], i + 1);
    }

    gSPLight(gDisplayListHead++, D_80060490->lights, i + 1);
}

extern unk_D_86002F34_alt11* D_800604A0;
extern Gfx D_01002580[];
M2C_UNK func_800135FC(u8, s32, M2C_UNK, s32);
void Geo_NodeShadowContext(GraphNode* arg0) {
    unk_D_86002F34_alt11* arg = (unk_D_86002F34_alt11*)arg0;
    MtxF* temp_v0 = &D_800AB460.unk_0000[D_800AB460.unk_10A0];
    Vec3f sp2C;
    Vec3s sp24;

    if (D_8006049C->node.renderFlags & 2) {
        Vec3f_SetComponentsDuplicate(&sp2C, temp_v0->xw, 0.0f, temp_v0->zw);
        Vec3s_SetComponents(&sp24, 0, D_8006049C->rotation.y, 0);
        MtxF_SetRotationTranslationF(&D_800AB460.unk_0000[D_800AB460.unk_10A0 + 1], &sp2C, &sp24);

        D_800AB460.unk_10A0++;

        GeoRender_CommitMatrix();
        func_800135FC(0, (s32)D_01002580, 0, 1);

        D_800AB460.unk_10A0--;
    }

    D_800604A0 = arg;
    Geo_ProcessNodeChildren(arg0);
    D_800604A0 = NULL;
}

M2C_UNK func_8001380C();                            /* extern */
void func_8001473C(s8 *arg0)
{
  unsigned char temp_f6;
 goto dummy_label_201075; dummy_label_201075: ;
 do { } while (0);
  ;
  if ((((s16) ((s32) (*((f32 *) (((s8 *) ((&(*((s8 *) (&D_800AB460)))) + ((*((s32 *) (((s8 *) (&(*((s8 *) (&D_800AB460))))) + 0x10A0))) << 6))) + 0x38))))) >= (*((s16 *) (((s8 *) arg0) + 0x18)))) && (((s16) ((s32) (*((f32 *) (((s8 *) ((&(*((s8 *) (&D_800AB460)))) + ((*((s32 *) (((s8 *) (&(*((s8 *) (&D_800AB460))))) + 0x10A0))) << 6))) + 0x38))))) < (*((s16 *) (((s8 *) arg0) + 0x1A)))))
  {
    func_8001380C();
  }
}

void Geo_NodeSwitchCase(GraphNode* arg0) {
    unk_D_86002F34_alt3* arg = (unk_D_86002F34_alt3*)arg0;
    s32 i;
    GraphNode* var_a1 = arg->node.children;

    if (var_a1 != NULL) {
        for (i = 0; i < arg->unk_1A; i++) {
            var_a1 = var_a1->nextSibling;
        }
    }

    if (var_a1->flags & 1) {
        D_8006062C[var_a1->type](var_a1);
    }
}

void Geo_NodeTranslateRotate(GraphNode* arg0) {
    MtxF sp20;
    unk_D_86002F34_alt5* arg = (unk_D_86002F34_alt5*)arg0;

    MtxF_SetRotationTranslationF(&sp20, &arg->unk_18, &arg->unk_24);
    GeoRender_PushMultipliedMatrix(&sp20);
    Geo_ProcessNodeChildren(arg0);

    D_800AB460.unk_10A0--;
}

void Geo_NodeTranslate(GraphNode* arg0) {
    unk_D_86002F34_alt5* arg = (unk_D_86002F34_alt5*)arg0;

    GeoRender_PushScaledMatrix(&arg->unk_18);
    Geo_ProcessNodeChildren(arg0);

    D_800AB460.unk_10A0--;
}

#ifdef NON_MATCHING
/* TODO: decompile func_800148AC; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_800148AC.s")
#endif

/*
 * func_80014BF0
 *
 * If the word at +0x18 of arg0 is not 0, calls
 * func_800135FC(byte at +3, that word, D_800AB248[halfword at +0x1C],
 * byte at +2 & 4), and then in every case calls func_8001380C(arg0)
 * (Geo_ProcessNodeChildren in symbol_addrs.txt).  D_800AB248 is read as an
 * array of words indexed by a signed halfword of arg0.  What func_800135FC
 * does with these values is not established (it is still assembly).
 *
 * Context from the Stadium 1 decomp (not proof for this ROM): there, the
 * first 0x18 bytes of a geometry-graph node (GraphNode) hold the type at +0,
 * flags at +1, renderFlags at +2 and renderLayer at +3, with node-specific
 * fields after them, and handlers of this shape end by calling
 * Geo_ProcessNodeChildren.  So arg0 here is probably such a node, the byte at
 * +3 its render layer and bit 4 of the byte at +2 its display-list flag.
 */
extern s32 D_800AB248[];

void func_80014BF0(void *arg0) {
    s32 temp_a1;

    temp_a1 = M2C_FIELD(arg0, s32 *, 0x18);
    if (temp_a1 != 0) {
        func_800135FC(M2C_FIELD(arg0, u8 *, 3), temp_a1, D_800AB248[M2C_FIELD(arg0, s16 *, 0x1C)], M2C_FIELD(arg0, u8 *, 2) & 4);
    }
    func_8001380C(arg0);
}

void func_80011838(EventTrackState*, s32);
void func_8000E41C(MtxF*, MtxF*, MtxF*, Vec3f*);
extern s32 D_800AB44C;
void func_80014C4C(GraphNode* arg0) {
    MtxF sp28;
    DisplayObject* arg = (DisplayObject*)arg0;

    if (D_80060490->unk_18 == arg->rootId) {
        arg->anchorCount = 0;
        if (arg->transformAnim.data != NULL) {
            ModelAnim_BeginCurveContext(&arg->transformAnim, arg->node.renderFlags & 0x20);
        }
        if (arg->eventTrack.data != NULL) {
            func_80011838(&arg->eventTrack, arg->node.renderFlags & 0x20);
        }

        if (arg->node.renderFlags & 0x10) {
            MtxF_Multiply(&sp28, &arg->matrix, &D_800AB460.unk_0000[D_800AB460.unk_10A0]);
        } else if (arg->node.renderFlags & 8) {
            func_8000E41C(&sp28, &D_80060488->view.floatMatrix, &D_800AB460.unk_0000[D_800AB460.unk_10A0], &arg->position);
        } else if (arg->node.renderFlags & 0x80) {
            MtxF_SetRotationAndTransformTranslation(&sp28, &arg->position, &arg->rotation);
            MtxF_Multiply(&sp28, &sp28, &D_800AB460.unk_0000[D_800AB460.unk_10A0]);
        } else {
            MtxF_SetRotationTranslationF(&sp28, &arg->position, &arg->rotation);
            MtxF_Multiply(&sp28, &sp28, &D_800AB460.unk_0000[D_800AB460.unk_10A0]);
        }

        MtxF_ScaleRows(&D_800AB460.unk_0000[D_800AB460.unk_10A0 + 1], &sp28, &arg->scale);

        if (!(arg->node.renderFlags & 4)) {
            D_800AB460.unk_10A0++;

            GeoRender_CommitMatrix();
            D_8006049C = arg;
            D_800AB44C = arg->fogColor.rgba;

            if ((D_8006048C->unk_18 < 0) && (arg->objectType > 0)) {
                ModelAnim_UpdateDisplayObjectAnimation(arg->effectSlot, arg->objectType);
                Geo_ProcessNodeChildren(arg0);
                ModelAnim_FinalizeDisplayObjectAnimation(arg->effectSlot, arg->objectType);
            } else {
                Geo_ProcessNodeChildren(arg0);
            }

            D_800AB44C = 0xFFFFFF00;
            D_8006049C = NULL;
        }

        D_800AC690 = 0;
        D_800AC6A8 = 0;
        D_800AB460.unk_10A0 -= 1;
    }
}

M2C_UNK func_80011294(s32);                         /* extern */
M2C_UNK func_800135FC(u8, s32, M2C_UNK, s32);       /* extern */
M2C_UNK func_8001380C(s8 *);                      /* extern */

void func_80014E78(s8 *arg0) {
    s32 temp_a1;

    func_80011294(arg0 + 0x1C);
    temp_a1 = M2C_FIELD(arg0, s32 *, 0x18);
    if (temp_a1 != 0) {
        func_800135FC(M2C_FIELD(arg0, u8 *, 3), temp_a1, 0, M2C_FIELD(arg0, u8 *, 2) & 4);
    }
    func_8001380C(arg0);
    M2C_FIELD(&D_800AB460, s32 *, 0x10A0) = (s32) (M2C_FIELD(&D_800AB460, s32 *, 0x10A0) - 1);
}

M2C_UNK func_800135FC(u8, s32, M2C_UNK, s32);
M2C_UNK func_8001380C();
void func_8000E41C(MtxF*, MtxF*, MtxF*, Vec3f*);
M2C_UNK func_8001380C(s8 *);
M2C_UNK func_80011210(MtxF *);                      /* extern */

void func_80014EDC(s8 *arg0) {
    MtxF sp28;
    s32 temp_a1;

    func_8000E41C(&sp28, &D_80060488->view.floatMatrix, &D_800AB460.unk_0000[D_800AB460.unk_10A0], arg0 + 0x1C);
    D_800AB460.unk_10A0 += 1;
    func_80011210(&sp28);
    temp_a1 = M2C_FIELD(arg0, s32 *, 0x18);
    if (temp_a1 != 0) {
        func_800135FC(M2C_FIELD(arg0, u8 *, 3), temp_a1, 0, M2C_FIELD(arg0, u8 *, 2) & 4);
    }
    func_8001380C(arg0);
    D_800AB460.unk_10A0 -= 1;
}

M2C_UNK func_800135FC(u8, s32, M2C_UNK, s32);       /* extern */
M2C_UNK func_8001380C(s8 *);                      /* extern */
void func_80014F78(s8 *arg0)
{
  s32 new_var;
  s32 temp_a1;
  temp_a1 = *((s32 *) (((s8 *) arg0) + 0x18));
  new_var = temp_a1;
  if (new_var != 0)
  {
    if ((!arg0) && (!arg0))
    {
    }
    func_800135FC(*((u8 *) (((s8 *) arg0) + 3)), new_var, 0, (*((u8 *) (((s8 *) arg0) + 2))) & 4);
  }
  func_8001380C((0, arg0));
}

#ifdef NON_MATCHING
/* TODO: decompile func_80014FC4; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_80014FC4.s")
#endif

void GeoRender_RecordAnchorPosition(s32 arg0) {
    MtxF* temp_a1;
    ModelAnchor* ptr;

    if (D_8006049C != NULL) {
        if (D_8006049C->anchorCount < 0xC) {
            ptr = &D_8006049C->anchors[D_8006049C->anchorCount++];
            temp_a1 = &D_800AB460.unk_0000[D_800AB460.unk_10A0];

            ptr->id = arg0;
            ptr->position.x = temp_a1->mf[3][0];
            ptr->position.y = temp_a1->mf[3][1];
            ptr->position.z = temp_a1->mf[3][2];
        }
    }
}

void Geo_NodeAnchor(GraphNode* arg0) {
    unk_D_86002F34_alt3* arg = (unk_D_86002F34_alt3*)arg0;

    GeoRender_RecordAnchorPosition(arg->unk_18);
    Geo_ProcessNodeChildren(arg0);
}

#ifdef NON_MATCHING
/* TODO: decompile func_800152AC; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_800152AC.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_80015330; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_80015330.s")
#endif

void Geo_RenderRootNode(GraphNode* node) {
    unk_D_86002F34_alt1* arg = (unk_D_86002F34_alt1*)node;

    if (node->flags & 1) {
        gDPPipeSync(gDisplayListHead++);

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

        D_8006048C = arg;
        Geo_ProcessNodeChildren(node);
        D_8006048C = NULL;
    }

    D_80060480 = 0;
}

void Geo_ProcessCallbacks(GraphNode* arg0, s32 arg1) {
    GraphNode* var_s1 = arg0;
    GraphNode** var_s0;

    do {
        if (var_s1->callback != NULL) {
            var_s1->callback(arg1, var_s1);
        }

        if (var_s1->children != NULL) {
            switch (var_s1->type) {
                default:
                    var_s0 = NULL;
                    break;

                case 2:
                    var_s0 = &D_80060488;
                    break;

                case 4:
                    var_s0 = &D_80060490;
                    break;

                case 6:
                    var_s0 = &D_80060498;
                    break;

                case 0x16:
                    var_s0 = &D_8006049C;
                    break;
            }

            if (var_s0 != NULL) {
                *var_s0 = var_s1;
            }

            Geo_ProcessCallbacks(var_s1->children, arg1);

            if (var_s0 != NULL) {
                *var_s0 = NULL;
            }
        }

        var_s1 = var_s1->nextSibling;
    } while (var_s1 != arg0);
}

void GeoRender_SetMode(s32 arg0) {
    D_80060480 = arg0;
}

void GeoRender_AdvanceFrameCounter(void) {
    D_80060484++;
}

s32 GeoRender_IsModelFrameCurrent(void) {
    s32 var_v1 = 1;

    if (D_80060490 != NULL) {
        var_v1 = D_80060490->unk_1A == D_80060484;
    }
    return var_v1;
}

Vec3f* GeoRender_FindAnchorPosition(DisplayObject* display_object, s16 lookup_id, Vec3f* dest) {
    s32 i;
    // FAKE
    s32 var_v0;
    u8 temp_v1;
    DisplayObject* var_a2;

    for (i = 0; i < display_object->anchorCount; i++) {
        if (lookup_id == display_object->anchors[i].id) {
            if (dest != NULL) {
                *dest = display_object->anchors[i].position;
            }
            return &display_object->anchors[i].position;
        }
    }

    return NULL;
}
