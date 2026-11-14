/* Stadium Zero resident code. */
/* C ported from the Stadium 1 decomp: src/poke_icon.c. */

#include "poke_icon.h"
#include "display_object_textures.h"
#include "font.h"
#include "geo_layout.h"
#include "geo_render.h"
#include "graphics_textures.h"
#include "input.h"
#include "main_pool.h"
#include "matrix.h"
#include "memory_main.h"
#include "model_renderer.h"

// Declared here instead of in a header: the callers of these disagree on their types.
void MainPool_FinalizeAllocation(struct MemoryBlock* block);
extern DisplayObject* D_800AD1C0;
s32 PokeIcon_CapturePreviewGeoNode(s32, GraphNode*);
s32 PokeIcon_CaptureGeoNode(s32, GraphNode*);

s32 PokeIcon_CapturePreviewGeoNode(s32 arg0, GraphNode* arg1);
void PokeIcon_InitPreviewScene(PokeModelPreview* arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4);
PokeModelPreview* PokeIcon_CreateModelPreview(ModelLoadContext* arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5,
                                 s16 arg6, u8* arg7);
s32 PokeIcon_HandlePreviewInput(Vec3s* arg0);
s32 func_800193EC(Vec3s* arg0);
void PokeIcon_AdvancePreviewMotion(PokeModelPreview* arg0);
void PokeIcon_UpdatePreview(PokeModelPreview* arg0);

/** Stores a geo node so the preview renderer can find it. */
s32 PokeIcon_CapturePreviewGeoNode(s32 arg0, GraphNode* arg1) {
    if (arg0 == 0) {
        D_800AD1C0 = arg1;
    }
    return 0;
}

/** Initializes the preview scene of a Pokemon model. */
void PokeIcon_InitPreviewScene(PokeModelPreview* arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4) {
    static u32 D_8006F3E0[] = {
        0x0C00FFFF, 0x05000000, 0x0B00001E, 0x00000000, 0x010000E0, 0x00000000,
        0x0000000A, 0x015404E2, 0x05000000, 0x0D000000, 0x05000000, 0x14000000,
        0x002D013B, 0xFFFFFF32, 0x16FFFFFF, 0x0F000001, 0x05000000, 0x1F000000,
        0x00000000, 0x00000000, 0xFF060000, 0x00640064, 0x00640000, 0x08000000,
        PokeIcon_CapturePreviewGeoNode, 0x00000000, 0x06000000, 0x06000000, 0x06000000, 0x06000000,
        0x01000000, 0x00000000,
    };
    MemoryBlock* sp24;
    MemoryBlock* temp_v0;

    sp24 = MainPool_AllocState(main_pool_get_available(), 0);
    arg0->rootNode = process_geo_layout(sp24, D_8006F3E0);
    arg0->displayObject = D_800AD1C0;
    MainPool_FinalizeAllocation(sp24);
    GeoCamera_SetViewport(arg0->rootNode->children, arg1, arg2, arg3, arg4);
    GeoCamera_SetPerspective(arg0->rootNode->children, 30.0f, 100.0f, 12800.0f);
}

/**
 * Allocates a Pokémon model preview of arg1 x arg2 pixels with its own color and depth
 * images, then sets up its preview scene.
 */
PokeModelPreview* PokeIcon_CreateModelPreview(ModelLoadContext* arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5,
                                 s16 arg6, u8* arg7) {
    PokeModelPreview* temp_v0 = main_pool_alloc(sizeof(PokeModelPreview), 0);

    if (temp_v0 != NULL) {
        temp_v0->flags = 6;
        temp_v0->loadContext = arg0;
        temp_v0->source = 0;
        temp_v0->width = arg1;
        temp_v0->height = arg2;
        temp_v0->backgroundWidth = arg5;
        temp_v0->backgroundHeight = arg6;
        temp_v0->backgroundImage = arg7;
        temp_v0->colorImage = GfxImage_Allocate(0, 2, arg1, arg2, 0);
        temp_v0->depthImage = GfxImage_Allocate(0, 2, arg1, arg2, 1);
        GfxImage_AttachDepthBuffer(temp_v0->colorImage, temp_v0->depthImage);
        PokeIcon_InitPreviewScene(temp_v0, arg3, arg4, arg5, arg6);
    }
    return temp_v0;
}

extern SpeciesInfo D_80064C5C[];

/** Sets the Pokemon shown in the preview. */
void PokeIcon_SetPreviewMon(PokeModelPreview* arg0, BattleMon* arg1, u16 arg2) {
    arg1_func_80010CA8 sp2C;
    s16 tmp1 = (s16)(D_80064C5C[arg1->species.id - 1].unk_14 >> 0x10) >> 5;
    s16 tmp2 = (s16)(D_80064C5C[arg1->species.id - 1].unk_14 >> 5) >> 6;
    s16 tmp3 = (s16)(D_80064C5C[arg1->species.id - 1].unk_14 << 5) >> 5;

    arg0->flags |= 1;
    arg0->source = arg1;
    arg0->spinSpeed = 0x100;
    arg0->idleTimer = 0;
    arg0->fillColor = arg2;
    arg0->scale = D_80064C5C[arg1->species.id - 1].modelScale / 100.0f;

    arg0->displayObject->position.x = tmp1;
    arg0->displayObject->position.y = tmp2;
    arg0->displayObject->position.z = tmp3;

    arg0->displayObject->rotation = D_8006045C;
    Model_ComputeSizeVariant(&sp2C, arg1);
    PokeIcon_RequestFrameLoad(arg0->loadContext, arg1->species.id, sp2C);
    PokeIcon_WaitFrameLoad(arg0->loadContext);
    ModelRenderer_ClearDisplayObject(arg0->displayObject);
    Model_InitDisplayObject(arg0->displayObject, 0, arg1->species.id, arg0->loadContext->loadedModel->modelRoot->unk_00[0]);
    ModelAnim_SetAnimation(arg0->displayObject, 1);
    arg0->displayObject->node.renderFlags &= ~0x40;
    arg0->displayObject->node.renderFlags |= 0x80;
}

extern SpeciesInfo D_80064C5C[];

/** Sets the species shown in the preview. */
void PokeIcon_SetPreviewSpecies(PokeModelPreview* arg0, s32 arg1, u16 arg2) {
    arg1_func_80010CA8 sp34;
    s16 tmp1 = (s16)(D_80064C5C[arg1 - 1].unk_14 >> 0x10) >> 5;
    s16 tmp2 = (s16)(D_80064C5C[arg1 - 1].unk_14 >> 5) >> 6;
    s16 tmp3 = (s16)(D_80064C5C[arg1 - 1].unk_14 << 5) >> 5;

    arg0->flags &= ~1;
    arg0->source = arg1;
    arg0->spinSpeed = 0x100;
    arg0->idleTimer = 0;
    arg0->fillColor = arg2;
    arg0->scale = D_80064C5C[arg1 - 1].modelScale / 100.0f;

    arg0->displayObject->position.x = tmp1;
    arg0->displayObject->position.y = tmp2;
    arg0->displayObject->position.z = tmp3;

    arg0->displayObject->rotation = D_8006045C;
    sp34.raw = 0;
    PokeIcon_RequestFrameLoad(arg0->loadContext, arg1, sp34);
    PokeIcon_WaitFrameLoad(arg0->loadContext);
    ModelRenderer_ClearDisplayObject(arg0->displayObject);
    Model_InitDisplayObject(arg0->displayObject, 0, arg1, arg0->loadContext->loadedModel->modelRoot->unk_00[0]);
    ModelAnim_SetAnimation(arg0->displayObject, 1);
    arg0->displayObject->node.renderFlags &= ~0x40;
    arg0->displayObject->node.renderFlags |= 0x80;
}

/** Handles the controller input that rotates the preview. */
s32 PokeIcon_HandlePreviewInput(Vec3s* arg0) {
    s32 var_v1 = 0;

    if (gPlayer1Controller->buttonDown & 0x800) {
        var_v1 = 1;
        arg0->x += 0x400;
    }

    if (gPlayer1Controller->buttonDown & 0x400) {
        var_v1 = 1;
        arg0->x -= 0x400;
    }

    if (gPlayer1Controller->buttonDown & 0x200) {
        var_v1 = 1;
        arg0->y += 0x400;
    }

    if (gPlayer1Controller->buttonDown & 0x100) {
        var_v1 = 1;
        arg0->y -= 0x400;
    }

    return var_v1;
}

s32 func_800193EC(Vec3s* arg0) {
    return 0;
}

/** Advances the preview model's rotation. */
void PokeIcon_AdvancePreviewMotion(PokeModelPreview* arg0) {
    s32 var_a0;
    Vec3s* sp18 = &arg0->displayObject->rotation;
    s16 var_a2;
    s16 temp_lo;

    if (arg0->spinSpeed < 0x100) {
        arg0->spinSpeed += 0x10;
    }
    sp18->y += arg0->spinSpeed;
    var_a2 = arg0->spinSpeed;

    if (sp18->x < 0) {
        var_a0 = -sp18->x;
    } else {
        var_a0 = sp18->x;
    }

    temp_lo = var_a0 / 12;
    if (temp_lo < 8) {
        temp_lo = 8;
    }

    if (temp_lo < var_a2) {
        var_a2 = temp_lo;
    }
    sp18->x = Math_StepToS(sp18->x, 0, var_a2);
}

/** Updates the preview scene for the frame. */
void PokeIcon_UpdatePreview(PokeModelPreview* arg0) {
    f32 temp_fv0;
    s16 temp_v0_2;
    s32 temp_v0;
    s32 var_v1;

    var_v1 = 0;
    if (arg0->flags & 2) {
        var_v1 = PokeIcon_HandlePreviewInput(&arg0->displayObject->rotation);
        if (var_v1 == 0) {
            var_v1 = func_800193EC(&arg0->displayObject->rotation);
        }
    }

    if (var_v1 != 0) {
        arg0->spinSpeed = 0;
        arg0->idleTimer = 0x78;
    } else if (arg0->flags & 4) {
        if (arg0->idleTimer > 0) {
            arg0->idleTimer--;
        } else {
            PokeIcon_AdvancePreviewMotion(arg0);
        }
    }

    Vec3f_SetComponentsDuplicate(&D_800AD1C0->scale, arg0->scale, arg0->scale, arg0->scale);
}

/** Draws the preview scene. */
void PokeIcon_DrawPreview(PokeModelPreview* arg0) {
    s32 var_v0;
    s32 var_s2;
    s32 i;

    if (arg0->backgroundImage == 0) {
        GfxImage_FillCurrent(&gDisplayListHead, arg0->fillColor);
        return;
    }

    var_s2 = arg0->backgroundImage;

    gDPPipeSync(gDisplayListHead++);
    gDPSetCycleType(gDisplayListHead++, G_CYC_COPY);
    gDPSetRenderMode(gDisplayListHead++, G_RM_NOOP, G_RM_NOOP2);
    gDPSetTexturePersp(gDisplayListHead++, G_TP_NONE);

    for (i = 0; i < arg0->backgroundHeight; i += 8) {
        var_v0 = arg0->backgroundHeight - i;
        if (var_v0 >= 9) {
            var_v0 = 8;
        }
        Gfx_DrawTextureRgba16(0, i, arg0->backgroundWidth, var_v0, var_s2, arg0->width, 0x200000);
        var_s2 += arg0->width * 0x10;
    }

    gDPPipeSync(gDisplayListHead++);
    gDPSetTexturePersp(gDisplayListHead++, G_TP_PERSP);

    GfxImage_ClearDepthRectangle(&gDisplayListHead, 0, 0, arg0->backgroundWidth, arg0->backgroundHeight);
}

extern s32 D_800AC834;
extern s32 D_800AD1C4;
void func_80019564();
extern char D_80079A60[];
extern char D_80079A70[];

/** Updates the preview and renders it to its render target. */
u8* PokeIcon_RenderPreview(PokeModelPreview* arg0) {
    PokeIcon_UpdatePreview(arg0);
    GfxImage_SetRenderTarget(&gDisplayListHead, arg0->colorImage);
    func_80019564(arg0);
    GeoRender_AdvanceFrameCounter();
    Geo_RenderRootNode(arg0->rootNode);

    if (D_800AD1C4 > 0) {
        Font_BeginTranslucentTextRendering();
        Font_SetActive(8, -4);

        switch (D_800AD1C4) {
            case 1:
                Font_Printf(0, 0x64, D_80079A60, arg0->scale, (s32)arg0->displayObject->position.y);
                break;

            case 2:
                Font_Printf(0, 0x64, D_80079A70, (s32)arg0->displayObject->position.x, (s32)arg0->displayObject->position.z);
                break;
        }
        Font_EndTexturedTextRendering();
    }
    return arg0->colorImage->img_p;
}
