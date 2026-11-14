/* Stadium Zero resident code. */
/* C ported from the Stadium 1 decomp: src/poke_icon.c. */

#include "poke_icon.h"
#include "display_object_textures.h"
#include "geo_node.h"
#include "geo_render.h"
#include "matrix.h"
#include "memory_main.h"
#include "model_renderer.h"
extern DisplayObject* D_800AD1C0;
s32 PokeIcon_CapturePreviewGeoNode(s32, GraphNode*);
s32 PokeIcon_CaptureGeoNode(s32, GraphNode*);

#include "m2c_macros.h"

s32 PokeIcon_CaptureGeoNode(s32 arg0, GraphNode* arg1);

/** Stores a geo node so the icon renderer can find it. */
s32 PokeIcon_CaptureGeoNode(s32 arg0, GraphNode* arg1) {
    if (arg0 == 0) {
        D_800AC7A0.archives.previewGeoNode = arg1;
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

/** Creates the render list for a Pokemon icon. */
PokeIconRenderer* PokeIcon_CreateRenderList(ModelLoadContext* arg0, s16 arg1, s16 arg2, s16 arg3) {
    s32 var_s0;
    DepthBuffer* temp_a1;
    s32 i;
    PokeIconRenderer* temp_v0 = main_pool_alloc(0x18, 0);

    if (temp_v0 != NULL) {
        temp_v0->flags = 0;
        temp_v0->nextSlot = 0;
        temp_v0->lastRenderedSlot = -1;
        temp_v0->slotCount = arg1;
        temp_v0->slots = main_pool_alloc(arg1 * sizeof(PokeIconSlot), 0);
        temp_v0->loadContext = arg0;
        temp_v0->depthImage = GfxImage_Allocate(0, 2, arg2, arg3, 1);

        for (i = 0; i < arg1; i++) {
            temp_v0->slots[i].flags = 0;
            temp_v0->slots[i].source.raw = 0;
            temp_v0->slots[i].image = GfxImage_Allocate(0, 2, arg2, arg3, 0);
            GfxImage_AttachDepthBuffer(temp_v0->slots[i].image, temp_v0->depthImage);
            bzero(temp_v0->slots[i].image->img_p, arg2 * arg3 * 2);
        }

        func_80017F54((s8*)temp_v0, arg2, arg3);
    }
    return temp_v0;
}

M2C_UNK func_80017D00(s32);                         /* extern */
M2C_UNK func_800199E4(s32);                         /* extern */
M2C_UNK func_8004FD20(s32, s32, u16, u16);          /* extern */

void func_80018168(PokeIconRenderer* arg0) {
    s32 var_s0;
    s32 var_s2;
    u16 temp_a2;
    u16 temp_a3;
    PokeIconSlot* temp_v0;
    DepthBuffer* temp_v1;

    if (arg0->flags & 1) {
        func_80017D00((s32)arg0->loadContext);
        func_800199E4((s32)arg0->displayObject);
    }
    arg0->flags = 0U;
    arg0->nextSlot = 0;
    arg0->lastRenderedSlot = -1;
    var_s2 = 0;
    if ((s32) arg0->slotCount > 0) {
        var_s0 = 0;
        do {
            temp_v0 = (PokeIconSlot*)((s8*)arg0->slots + var_s0);
            temp_v1 = temp_v0->image;
            temp_a2 = temp_v1->width;
            temp_a3 = temp_v1->height;
            temp_v0->flags = 0;
            ((PokeIconSlot*)((s8*)arg0->slots + var_s0))->source.raw = 0;
            func_8004FD20((s32)((PokeIconSlot*)((s8*)arg0->slots + var_s0))->image->img_p, temp_a2 * temp_a3 * 2, temp_a2, temp_a3);
            var_s2 += 1;
            var_s0 += 0x14;
        } while (var_s2 < (s32) arg0->slotCount);
    }
}

void func_80018234(PokeIconRenderer* arg0, s32 arg1, s32 arg2, u16 arg3) {
    DepthBuffer* buf;
    UNUSED s32 pad; // FAKE: stack padding

    if (arg1 < arg0->slotCount) {
        buf = arg0->slots[arg1].image;
        func_8004FD20((s32)buf->img_p, buf->width * buf->height * 2, buf->width, buf->height);
        if ((arg2 <= 0) || (arg2 >= 0x98)) {
            arg2 = 0x98;
        }
        arg0->slots[arg1].flags = 1;
        arg0->slots[arg1].fillColor = arg3 & 0xFFFE;
        arg0->slots[arg1].source.raw = arg2;
        arg0->slots[arg1].scale = *(s16*)&gSpeciesDataById[arg2 - 1][0x1A] / 100.0f;
        arg0->slots[arg1].colorVariant.raw = 0;
    }
}

void Model_ComputeNicknameColorVariant(arg1_func_80010CA8*);
void func_8001833C(PokeIconRenderer* arg0, s32 arg1, BattleMon* arg2, u16 arg3) {
    DepthBuffer* buf;
    UNUSED s32 pad; // FAKE: stack padding

    if (arg1 < arg0->slotCount) {
        buf = arg0->slots[arg1].image;
        func_8004FD20((s32)buf->img_p, buf->width * buf->height * 2, buf->width, buf->height);
        if ((arg2->species.id > 0) && (arg2->species.id < 0x98)) {
            arg0->slots[arg1].flags = 3;
            arg0->slots[arg1].source.ptr = (u8*)arg2;
            arg0->slots[arg1].fillColor = arg3 & 0xFFFE;
            arg0->slots[arg1].scale = *(s16*)&gSpeciesDataById[arg2->species.id - 1][0x1A] / 100.0f;
            Model_ComputeNicknameColorVariant(&arg0->slots[arg1].colorVariant);
        } else {
            arg0->slots[arg1].flags = 1;
            arg0->slots[arg1].fillColor = arg3 & 0xFFFE;
            arg0->slots[arg1].source.raw = 0x98;
            arg0->slots[arg1].scale = *(s16*)&gSpeciesDataById[0x97][0x1A] / 100.0f;
            arg0->slots[arg1].colorVariant.raw = 0;
        }
    }
}

/** Adjusts the colors of a rendered icon image. */
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
 * Seen in play (2026-11-13) (tour of menus and a COM battle): ran in the party screen, registration
 * and Free Battle setup.
 * @unverified Name was previously used only by callers of this address; the definition was still func_.
 */
void PokeIcon_RenderSlot(PokeIconRenderer* arg0, s32 arg1) {
    Vec3s sp38;
    PokeIconSlot* temp_s1;
    ModelNodeView* sp30;

    temp_s1 = &arg0->slots[arg1];
    sp30 = arg0->loadContext->loadedModel->modelRoot->unk_00[0];

    ModelRenderer_ClearDisplayObject(arg0->displayObject);
    ModelAnim_ClearTransformChannel(arg0->displayObject);

    if (temp_s1->flags & 2) {
        sp38.x = (s16)(D_80064C5C[*temp_s1->source.ptr - 1].unk_14 >> 0x10) >> 5;
        sp38.y = (s16)(D_80064C5C[*temp_s1->source.ptr - 1].unk_14 >> 5) >> 6;
        sp38.z = (s16)(D_80064C5C[*temp_s1->source.ptr - 1].unk_14 << 5) >> 5;
        Model_InitDisplayObject(arg0->displayObject, 0, *temp_s1->source.ptr, sp30);
        ModelAnim_SetAnimation(arg0->displayObject, 0);
        ModelAnim_SetFrame(arg0->displayObject, D_80064C5C[*temp_s1->source.ptr - 1].unk_01);
        Vec3f_FromVec3s(&arg0->displayObject->position, &sp38);
    } else {
        sp38.x = (s16)(D_80064C5C[temp_s1->source.raw - 1].unk_14 >> 0x10) >> 5;
        sp38.y = (s16)(D_80064C5C[temp_s1->source.raw - 1].unk_14 >> 5) >> 6;
        sp38.z = (s16)(D_80064C5C[temp_s1->source.raw - 1].unk_14 << 5) >> 5;
        Model_InitDisplayObject(arg0->displayObject, 0, temp_s1->source.speciesId, sp30);
        ModelAnim_SetAnimation(arg0->displayObject, 0);
        ModelAnim_SetFrame(arg0->displayObject, D_80064C5C[temp_s1->source.raw - 1].unk_01);
        Vec3f_FromVec3s(&arg0->displayObject->position, &sp38);
    }
    arg0->displayObject->node.renderFlags &= ~0x40;
    arg0->displayObject->node.renderFlags |= 0x80;
    Vec3f_SetComponentsDuplicate(&arg0->displayObject->scale, temp_s1->scale, temp_s1->scale, temp_s1->scale);
    GfxImage_SetRenderTarget(&gDisplayListHead, arg0->slots[arg1].image);
    GeoRender_AdvanceFrameCounter();
    GeoRender_SetMode(3);
    Geo_RenderRootNode(arg0->rootNode);
    GfxImage_FillCurrent(&gDisplayListHead, arg0->slots[arg1].fillColor);
    GeoRender_SetMode(1);
    Geo_RenderRootNode(arg0->rootNode);
}

/** Processes the next pending icon slot. */
s32 PokeIcon_ProcessNextSlot(PokeIconRenderer* arg0, s32 arg1) {
    s32 i;
    s32 var_v0;
    s32 sp24;
    s32 sp20;
    PokeIconSlot* temp_v0_2;

    sp24 = -1;
    sp20 = arg0->nextSlot;
    if (arg0->flags & 1) {
        if (arg1 == 1) {
            var_v0 = PokeIcon_WaitFrameLoad(arg0->loadContext);
        } else {
            var_v0 = PokeIcon_PollFrameLoad(arg0->loadContext);
        }
        if (var_v0 != 0) {
            arg0->flags &= 0xFFFE;
            arg0->slots[sp20].flags &= 0xFFFE;
            PokeIcon_RenderSlot(arg0, sp20);
            arg0->lastRenderedSlot = sp20;
            sp24 = sp20;
            arg0->nextSlot++;
            if (arg0->nextSlot >= arg0->slotCount) {
                arg0->nextSlot = 0;
            }
        }
    } else {
        for (i = 0; i < arg0->slotCount; i++) {
            temp_v0_2 = &arg0->slots[sp20];
            if (temp_v0_2->flags & 1) {
                arg0->flags |= 1;
                if (temp_v0_2->flags & 2) {
                    PokeIcon_RequestFrameLoad(arg0->loadContext, *temp_v0_2->source.ptr, temp_v0_2->colorVariant);
                } else {
                    PokeIcon_RequestFrameLoad(arg0->loadContext, temp_v0_2->source.speciesId, temp_v0_2->colorVariant);
                }
                arg0->nextSlot = sp20;
                break;
            } else {
                sp20 += 1;
                if (sp20 >= arg0->slotCount) {
                    sp20 = 0;
                }
            }
        }
    }
    return sp24;
}

/** Processes every pending icon slot. */
s32 PokeIcon_ProcessAllSlots(PokeIconRenderer* arg0, s32 arg1) {
    UNUSED s32 pad; // FAKE: stack padding
    arg1_func_80010CA8 sp48;
    s32 sp44;
    s32 var_s1;
    PokeIconSlot* temp_s0;
    PokeIconSlot* temp_s1;
    s32 i;

    sp44 = -1;
    var_s1 = arg0->nextSlot;
    if (arg0->lastRenderedSlot >= 0) {
        temp_s0 = &arg0->slots[arg0->lastRenderedSlot];
        if (temp_s0->flags & 4) {
            while (Display_IsFrameReady() == 0) {}
            PokeIcon_AdjustImageColors(temp_s0->image, temp_s0->colorVariant);
            temp_s0->flags &= ~4;
        }
    }

    for (i = 0; i < arg0->slotCount; i++) {
        temp_s1 = &arg0->slots[var_s1];
        if (temp_s1->flags & 1) {
            if (Display_IsFrameReady() == 0) {
                do { } while (Display_IsFrameReady() == 0); }

            sp48.raw = 0;
            if (temp_s1->flags & 2) {
                PokeIcon_RequestFrameLoad(arg0->loadContext, *temp_s1->source.ptr, sp48);
                if (temp_s1->colorVariant.raw != 0) {
                    temp_s1->flags |= 4;
                }
            } else {
                PokeIcon_RequestFrameLoad(arg0->loadContext, temp_s1->source.speciesId, sp48);
            }

            PokeIcon_WaitFrameLoad(arg0->loadContext);
            arg0->slots[var_s1].flags &= ~1;
            PokeIcon_RenderSlot(arg0, var_s1);
            sp44 = var_s1;
            arg0->nextSlot = var_s1;
            arg0->lastRenderedSlot = var_s1;
            arg0->nextSlot++;
            if (arg0->nextSlot >= arg0->slotCount) {
                arg0->nextSlot = 0;
            }
            break;
        }

        var_s1 += 1;
        if (var_s1 >= arg0->slotCount) {
            var_s1 = 0;
        }
    }

    return sp44;
}

/** Renders the next icon slot and waits for it to finish. */
s32 PokeIcon_RenderNextSlotBlocking(PokeIconRenderer* arg0, s32 arg1) {
    s32 i;
    s32 var_a2;
    s32 var_s0;
    PokeIconSlot* temp_a0;
    PokeIconSlot* temp_s1;

    var_a2 = -1;
    var_s0 = arg0->nextSlot;
    temp_a0 = arg0->slots;

    for (i = 0; i < arg0->slotCount; i++) {
        temp_s1 = &arg0->slots[var_s0];
        if (temp_s1->flags & 1) {
            while (Display_IsFrameReady() == 0) {}

            if (temp_s1->flags & 2) {
                PokeIcon_RequestFrameLoad(arg0->loadContext, *temp_s1->source.ptr, temp_s1->colorVariant);
            } else {
                PokeIcon_RequestFrameLoad(arg0->loadContext, temp_s1->source.speciesId, temp_s1->colorVariant);
            }
            PokeIcon_WaitFrameLoad(arg0->loadContext);
            arg0->slots[var_s0].flags &= ~1;
            PokeIcon_RenderSlot(arg0, var_s0);
            arg0->nextSlot = var_s0;
            var_a2 = var_s0;
            arg0->nextSlot++;
            arg0->lastRenderedSlot = var_s0;
            if (arg0->nextSlot >= arg0->slotCount) {
                arg0->nextSlot = 0;
            }
            break;
        } else {
            var_s0 += 1;
            if (var_s0 >= arg0->slotCount) {
                var_s0 = 0;
            }
        }
    }
    return var_a2;
}

/** Redraws an icon slot. */
void PokeIcon_RedrawSlot(PokeIconRenderer* arg0, s32 arg1) {
    s32 i;

    if (arg1 == arg0->lastRenderedSlot) {
        GfxImage_SetRenderTarget(&gDisplayListHead, arg0->slots[arg1].image);
        GfxImage_FillCurrent(&gDisplayListHead, arg0->slots[arg1].fillColor);
        GeoRender_SetMode(1);
        Geo_RenderRootNode(arg0->rootNode);
        return;
    }
    for (i = arg0->slotCount; i > 0; i--) {
        if (arg0->slots[i - 1].flags & 1) {
            break;
        }
    }
    if (i == 0) {
        arg0->slots[arg1].flags |= 1;
    }
}

/** Returns the rendered image of an icon slot. */
s32 PokeIcon_GetImage(s8* arg0, s32 arg1) {
    s32 var_v1;

    var_v1 = 0;
    if (arg1 < (s32) ((PokeIconRenderer*)arg0)->slotCount) {
        var_v1 = (s32)((PokeIconRenderer*)arg0)->slots[arg1].image->img_p;
    }
    return var_v1;
}

/** Returns whether every icon slot is idle. */
s32 PokeIcon_AreSlotsIdle(PokeIconRenderer* arg0) {
    s32 i;

    for (i = 0; i < arg0->slotCount; i++) {
        if (arg0->slots[i].flags & 5) {
            return 0;
        }
    }
    return 1;
}
