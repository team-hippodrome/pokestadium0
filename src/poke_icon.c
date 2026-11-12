/* Stadium Zero resident code. */
/* C ported from the Stadium 1 decomp: src/poke_icon.c. */

#include "poke_icon.h"
#include "geo_node.h"
#include "geo_render.h"
#include "model_animation.h"
#include "display_object_textures.h"
#include "model_renderer.h"
#include "graphics_textures.h"
#include "jpeg_stream.h"
#include "gfx_rect.h"
#include "matrix.h"
#include "dp_intro.h"
#include "geo_layout.h"
#include "memory.h"
extern DisplayObject* D_800AD1C0;
s32 PokeIcon_CapturePreviewGeoNode(s32, GraphNode*);
s32 PokeIcon_CaptureGeoNode(s32, GraphNode*);

#include "m2c_macros.h"

s32 PokeIcon_CaptureGeoNode(s32 arg0, GraphNode* arg1);

s32 PokeIcon_CaptureGeoNode(s32 arg0, GraphNode* arg1) {
    if (arg0 == 0) {
        D_800AC7A0.unk_A04.unk_0C = arg1;
    }
    return 0;
}

s32 main_pool_get_available(void);                                /* extern */
s32 func_80002B10(s32, M2C_UNK);                    /* extern */
M2C_UNK func_80002B60(s32);                         /* extern */
M2C_UNK func_80010B3C(s32, M2C_UNK, M2C_UNK, s16, s32); /* extern */
s8 *func_80016C70(s32, M2C_UNK *);                /* extern */
extern M2C_UNK D_80060740;
extern s32 D_800AD1B0;

void func_80017F54(s8 *arg0, s16 arg1, s16 arg2) {
    s32 sp24;
    s32 temp_v0;

    temp_v0 = func_80002B10(main_pool_get_available(), 0);
    sp24 = temp_v0;
    M2C_FIELD(arg0, s8 **, 0xC) = func_80016C70(temp_v0, &D_80060740);
    M2C_FIELD(arg0, s32 *, 0x10) = (s32) D_800AD1B0;
    func_80002B60(sp24);
    func_80010B3C(M2C_FIELD(M2C_FIELD(arg0, s8 **, 0xC), s32 *, 0xC), 0, 0, arg1, (s32) arg2);
}

unk_func_8001A024* PokeIcon_CreateRenderList(ModelLoadContext* arg0, s16 arg1, s16 arg2, s16 arg3) {
    s32 var_s0;
    DepthBuffer* temp_a1;
    s32 i;
    unk_func_8001A024* temp_v0 = main_pool_alloc(0x18, 0);

    if (temp_v0 != NULL) {
        temp_v0->unk_00 = 0;
        temp_v0->unk_02 = 0;
        temp_v0->unk_03 = -1;
        temp_v0->unk_01 = arg1;
        temp_v0->unk_08 = main_pool_alloc(arg1 * sizeof(unk_func_8001A024_008), 0);
        temp_v0->unk_04 = arg0;
        temp_v0->unk_14 = GfxImage_Allocate(0, 2, arg2, arg3, 1);

        for (i = 0; i < arg1; i++) {
            temp_v0->unk_08[i].unk_00 = 0;
            temp_v0->unk_08[i].unk_14.raw = 0;
            temp_v0->unk_08[i].unk_0C = GfxImage_Allocate(0, 2, arg2, arg3, 0);
            GfxImage_AttachDepthBuffer(temp_v0->unk_08[i].unk_0C, temp_v0->unk_14);
            bzero(temp_v0->unk_08[i].unk_0C->img_p, arg2 * arg3 * 2);
        }

        func_80017F54((s8*)temp_v0, arg2, arg3);
    }
    return temp_v0;
}

M2C_UNK func_80017D00(s32);                         /* extern */
M2C_UNK func_800199E4(s32);                         /* extern */
M2C_UNK func_8004FD20(s32, s32, u16, u16);          /* extern */

void func_80018168(s8 *arg0) {
    s32 var_s0;
    s32 var_s2;
    u16 temp_a2;
    u16 temp_a3;
    s8 *temp_v0;
    s8 *temp_v1;

    if (M2C_FIELD(arg0, u8 *, 0) & 1) {
        func_80017D00(M2C_FIELD(arg0, s32 *, 4));
        func_800199E4(M2C_FIELD(arg0, s32 *, 0x10));
    }
    M2C_FIELD(arg0, u8 *, 0) = 0U;
    M2C_FIELD(arg0, s8 *, 2) = 0;
    M2C_FIELD(arg0, s8 *, 3) = -1;
    var_s2 = 0;
    if ((s32) M2C_FIELD(arg0, u8 *, 1) > 0) {
        var_s0 = 0;
        do {
            temp_v0 = M2C_FIELD(arg0, s32 *, 8) + var_s0;
            temp_v1 = M2C_FIELD(temp_v0, s8 **, 0xC);
            temp_a2 = M2C_FIELD(temp_v1, u16 *, 4);
            temp_a3 = M2C_FIELD(temp_v1, u16 *, 6);
            M2C_FIELD(temp_v0, s16 *, 0) = 0;
            M2C_FIELD((M2C_FIELD(arg0, s32 *, 8) + var_s0), s32 *, 4) = 0;
            func_8004FD20(M2C_FIELD(M2C_FIELD((M2C_FIELD(arg0, s32 *, 8) + var_s0), s8 **, 0xC), s32 *, 8), temp_a2 * temp_a3 * 2, temp_a2, temp_a3);
            var_s2 += 1;
            var_s0 += 0x14;
        } while (var_s2 < (s32) M2C_FIELD(arg0, u8 *, 1));
    }
}

void func_80018234(unk_func_8001A024* arg0, s32 arg1, s32 arg2, u16 arg3) {
    DepthBuffer* buf;
    UNUSED s32 pad; // FAKE: stack padding

    if (arg1 < arg0->unk_01) {
        buf = arg0->unk_08[arg1].unk_0C;
        func_8004FD20((s32)buf->img_p, buf->width * buf->height * 2, buf->width, buf->height);
        if ((arg2 <= 0) || (arg2 >= 0x98)) {
            arg2 = 0x98;
        }
        arg0->unk_08[arg1].unk_00 = 1;
        arg0->unk_08[arg1].unk_02 = arg3 & 0xFFFE;
        arg0->unk_08[arg1].unk_14.raw = arg2;
        arg0->unk_08[arg1].unk_08 = *(s16*)&gSpeciesDataById[arg2 - 1][0x1A] / 100.0f;
        arg0->unk_08[arg1].unk_10.raw = 0;
    }
}

void Model_ComputeNicknameColorVariant(arg1_func_80010CA8*);
void func_8001833C(unk_func_8001A024* arg0, s32 arg1, BattleMon* arg2, u16 arg3) {
    DepthBuffer* buf;
    UNUSED s32 pad; // FAKE: stack padding

    if (arg1 < arg0->unk_01) {
        buf = arg0->unk_08[arg1].unk_0C;
        func_8004FD20((s32)buf->img_p, buf->width * buf->height * 2, buf->width, buf->height);
        if ((arg2->species.id > 0) && (arg2->species.id < 0x98)) {
            arg0->unk_08[arg1].unk_00 = 3;
            arg0->unk_08[arg1].unk_14.ptr = (u8*)arg2;
            arg0->unk_08[arg1].unk_02 = arg3 & 0xFFFE;
            arg0->unk_08[arg1].unk_08 = *(s16*)&gSpeciesDataById[arg2->species.id - 1][0x1A] / 100.0f;
            Model_ComputeNicknameColorVariant(&arg0->unk_08[arg1].unk_10);
        } else {
            arg0->unk_08[arg1].unk_00 = 1;
            arg0->unk_08[arg1].unk_02 = arg3 & 0xFFFE;
            arg0->unk_08[arg1].unk_14.raw = 0x98;
            arg0->unk_08[arg1].unk_08 = *(s16*)&gSpeciesDataById[0x97][0x1A] / 100.0f;
            arg0->unk_08[arg1].unk_10.raw = 0;
        }
    }
}

void PokeIcon_AdjustImageColors(u8* arg0, arg1_func_80010CA8 arg1) {
    s32 cond;
    u16* pixels = M2C_FIELD(arg0, u16**, 8);
    s32 count = M2C_FIELD(arg0, u16*, 6) * M2C_FIELD(arg0, u16*, 4);
    s32 size = count;

    if (!arg0) {}  // karodo

    size *= 2;

    osInvalDCache(pixels, size);

    cond = size >= 2;
    size -= 2;
    // clang-format off
    while (cond != 0) {
        *pixels = Color_AdjustRGB5551(*pixels, arg1);        cond = size >= 2;        size -= 2;
        pixels++;
    }
    // clang-format on
}

extern unk_D_8006FF00 D_80064C5C[];
/**
 * @unverified Name was previously used only by callers of this address; the definition was still func_.
 */
void PokeIcon_RenderSlot(unk_func_8001A024* arg0, s32 arg1) {
    Vec3s sp38;
    unk_func_8001A024_008* temp_s1;
    ModelNodeView* sp30;

    temp_s1 = &arg0->unk_08[arg1];
    sp30 = arg0->unk_04->loadedModel->modelRoot->unk_00[0];

    ModelRenderer_ClearDisplayObject(arg0->unk_10);
    ModelAnim_ClearTransformChannel(arg0->unk_10);

    if (temp_s1->unk_00 & 2) {
        sp38.x = (s16)(D_80064C5C[*temp_s1->unk_14.ptr - 1].unk_14 >> 0x10) >> 5;
        sp38.y = (s16)(D_80064C5C[*temp_s1->unk_14.ptr - 1].unk_14 >> 5) >> 6;
        sp38.z = (s16)(D_80064C5C[*temp_s1->unk_14.ptr - 1].unk_14 << 5) >> 5;
        Model_InitDisplayObject(arg0->unk_10, 0, *temp_s1->unk_14.ptr, sp30);
        ModelAnim_SetAnimation(arg0->unk_10, 0);
        ModelAnim_SetFrame(arg0->unk_10, D_80064C5C[*temp_s1->unk_14.ptr - 1].unk_01);
        Vec3f_FromVec3s(&arg0->unk_10->position, &sp38);
    } else {
        sp38.x = (s16)(D_80064C5C[temp_s1->unk_14.raw - 1].unk_14 >> 0x10) >> 5;
        sp38.y = (s16)(D_80064C5C[temp_s1->unk_14.raw - 1].unk_14 >> 5) >> 6;
        sp38.z = (s16)(D_80064C5C[temp_s1->unk_14.raw - 1].unk_14 << 5) >> 5;
        Model_InitDisplayObject(arg0->unk_10, 0, temp_s1->unk_14.unk_02, sp30);
        ModelAnim_SetAnimation(arg0->unk_10, 0);
        ModelAnim_SetFrame(arg0->unk_10, D_80064C5C[temp_s1->unk_14.raw - 1].unk_01);
        Vec3f_FromVec3s(&arg0->unk_10->position, &sp38);
    }
    arg0->unk_10->node.renderFlags &= ~0x40;
    arg0->unk_10->node.renderFlags |= 0x80;
    Vec3f_SetComponentsDuplicate(&arg0->unk_10->scale, temp_s1->unk_08, temp_s1->unk_08, temp_s1->unk_08);
    GfxImage_SetRenderTarget(&gDisplayListHead, arg0->unk_08[arg1].unk_0C);
    GeoRender_AdvanceFrameCounter();
    GeoRender_SetMode(3);
    Geo_RenderRootNode(arg0->unk_0C);
    GfxImage_FillCurrent(&gDisplayListHead, arg0->unk_08[arg1].unk_02);
    GeoRender_SetMode(1);
    Geo_RenderRootNode(arg0->unk_0C);
}

s32 PokeIcon_ProcessNextSlot(unk_func_8001A024* arg0, s32 arg1) {
    s32 i;
    s32 var_v0;
    s32 sp24;
    s32 sp20;
    unk_func_8001A024_008* temp_v0_2;

    sp24 = -1;
    sp20 = arg0->unk_02;
    if (arg0->unk_00 & 1) {
        if (arg1 == 1) {
            var_v0 = PokeIcon_WaitFrameLoad(arg0->unk_04);
        } else {
            var_v0 = PokeIcon_PollFrameLoad(arg0->unk_04);
        }
        if (var_v0 != 0) {
            arg0->unk_00 &= 0xFFFE;
            arg0->unk_08[sp20].unk_00 &= 0xFFFE;
            PokeIcon_RenderSlot(arg0, sp20);
            arg0->unk_03 = sp20;
            sp24 = sp20;
            arg0->unk_02++;
            if (arg0->unk_02 >= arg0->unk_01) {
                arg0->unk_02 = 0;
            }
        }
    } else {
        for (i = 0; i < arg0->unk_01; i++) {
            temp_v0_2 = &arg0->unk_08[sp20];
            if (temp_v0_2->unk_00 & 1) {
                arg0->unk_00 |= 1;
                if (temp_v0_2->unk_00 & 2) {
                    PokeIcon_RequestFrameLoad(arg0->unk_04, *temp_v0_2->unk_14.ptr, temp_v0_2->unk_10);
                } else {
                    PokeIcon_RequestFrameLoad(arg0->unk_04, temp_v0_2->unk_14.unk_02, temp_v0_2->unk_10);
                }
                arg0->unk_02 = sp20;
                break;
            } else {
                sp20 += 1;
                if (sp20 >= arg0->unk_01) {
                    sp20 = 0;
                }
            }
        }
    }
    return sp24;
}

s32 PokeIcon_ProcessAllSlots(unk_func_8001A024* arg0, s32 arg1) {
    UNUSED s32 pad; // FAKE: stack padding
    arg1_func_80010CA8 sp48;
    s32 sp44;
    s32 var_s1;
    unk_func_8001A024_008* temp_s0;
    unk_func_8001A024_008* temp_s1;
    s32 i;

    sp44 = -1;
    var_s1 = arg0->unk_02;
    if (arg0->unk_03 >= 0) {
        temp_s0 = &arg0->unk_08[arg0->unk_03];
        if (temp_s0->unk_00 & 4) {
            while (Display_IsFrameReady() == 0) {}
            PokeIcon_AdjustImageColors(temp_s0->unk_0C, temp_s0->unk_10);
            temp_s0->unk_00 &= ~4;
        }
    }

    for (i = 0; i < arg0->unk_01; i++) {
        temp_s1 = &arg0->unk_08[var_s1];
        if (temp_s1->unk_00 & 1) {
            if (Display_IsFrameReady() == 0) {
                do { } while (Display_IsFrameReady() == 0); }

            sp48.raw = 0;
            if (temp_s1->unk_00 & 2) {
                PokeIcon_RequestFrameLoad(arg0->unk_04, *temp_s1->unk_14.ptr, sp48);
                if (temp_s1->unk_10.raw != 0) {
                    temp_s1->unk_00 |= 4;
                }
            } else {
                PokeIcon_RequestFrameLoad(arg0->unk_04, temp_s1->unk_14.unk_02, sp48);
            }

            PokeIcon_WaitFrameLoad(arg0->unk_04);
            arg0->unk_08[var_s1].unk_00 &= ~1;
            PokeIcon_RenderSlot(arg0, var_s1);
            sp44 = var_s1;
            arg0->unk_02 = var_s1;
            arg0->unk_03 = var_s1;
            arg0->unk_02++;
            if (arg0->unk_02 >= arg0->unk_01) {
                arg0->unk_02 = 0;
            }
            break;
        }

        var_s1 += 1;
        if (var_s1 >= arg0->unk_01) {
            var_s1 = 0;
        }
    }

    return sp44;
}

s32 PokeIcon_RenderNextSlotBlocking(unk_func_8001A024* arg0, s32 arg1) {
    s32 i;
    s32 var_a2;
    s32 var_s0;
    unk_func_8001A024_008* temp_a0;
    unk_func_8001A024_008* temp_s1;

    var_a2 = -1;
    var_s0 = arg0->unk_02;
    temp_a0 = arg0->unk_08;

    for (i = 0; i < arg0->unk_01; i++) {
        temp_s1 = &arg0->unk_08[var_s0];
        if (temp_s1->unk_00 & 1) {
            while (Display_IsFrameReady() == 0) {}

            if (temp_s1->unk_00 & 2) {
                PokeIcon_RequestFrameLoad(arg0->unk_04, *temp_s1->unk_14.ptr, temp_s1->unk_10);
            } else {
                PokeIcon_RequestFrameLoad(arg0->unk_04, temp_s1->unk_14.unk_02, temp_s1->unk_10);
            }
            PokeIcon_WaitFrameLoad(arg0->unk_04);
            arg0->unk_08[var_s0].unk_00 &= ~1;
            PokeIcon_RenderSlot(arg0, var_s0);
            arg0->unk_02 = var_s0;
            var_a2 = var_s0;
            arg0->unk_02++;
            arg0->unk_03 = var_s0;
            if (arg0->unk_02 >= arg0->unk_01) {
                arg0->unk_02 = 0;
            }
            break;
        } else {
            var_s0 += 1;
            if (var_s0 >= arg0->unk_01) {
                var_s0 = 0;
            }
        }
    }
    return var_a2;
}

void PokeIcon_RedrawSlot(unk_func_8001A024* arg0, s32 arg1) {
    s32 i;

    if (arg1 == arg0->unk_03) {
        GfxImage_SetRenderTarget(&gDisplayListHead, arg0->unk_08[arg1].unk_0C);
        GfxImage_FillCurrent(&gDisplayListHead, arg0->unk_08[arg1].unk_02);
        GeoRender_SetMode(1);
        Geo_RenderRootNode(arg0->unk_0C);
        return;
    }
    for (i = arg0->unk_01; i > 0; i--) {
        if (arg0->unk_08[i - 1].unk_00 & 1) {
            break;
        }
    }
    if (i == 0) {
        arg0->unk_08[arg1].unk_00 |= 1;
    }
}

s32 PokeIcon_GetImage(s8 *arg0, s32 arg1) {
    s32 var_v1;

    var_v1 = 0;
    if (arg1 < (s32) M2C_FIELD(arg0, u8 *, 1)) {
        var_v1 = M2C_FIELD(M2C_FIELD((M2C_FIELD(arg0, s32 *, 8) + (arg1 * 0x14)), s8 **, 0xC), s32 *, 8);
    }
    return var_v1;
}

s32 PokeIcon_AreSlotsIdle(unk_func_8001A024* arg0) {
    s32 i;

    for (i = 0; i < arg0->unk_01; i++) {
        if (arg0->unk_08[i].unk_00 & 5) {
            return 0;
        }
    }
    return 1;
}
