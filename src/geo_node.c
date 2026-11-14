/* Stadium Zero resident code. */
/* C ported from the Stadium 1 decomp: src/geo_node.c, src/model_animation.c, src/model_animation_events.c. */

#include "global.h"
#include "geo_node.h"
#include "matrix.h"
#include "util.h"

// Declared here instead of in a header: the callers of these disagree on their types.
void* MainPool_AllocAligned(struct MainPoolState* state, s32 arg1, s32 arg2);

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


void GeoNode_Init(GraphNode* arg0, u8 arg1);
void GeoNode_SetCallback(GraphNode* arg0, GraphNodeCallback arg1, void* arg2);
GraphNode* GeoNode_CreateContainer(MainPoolState* arg0, GraphNode* arg1);
GeoReferenceNode* GeoNode_CreateWithReference(MainPoolState* arg0, GeoReferenceNode* arg1, GraphNode* arg2);
CameraNode* GeoNode_CreateCamera(MemoryBlock* arg0, CameraNode* arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5);
GeoType3Node* GeoNode_CreateType3(MemoryBlock* arg0, GeoType3Node* arg1, s16 arg2);
GeoBackgroundNode* GeoNode_CreateBackground(MainPoolState* arg0, GeoBackgroundNode* arg1, u8 arg2, u8 arg3, u8 arg4);
GeoClearDepthNode* GeoNode_CreateClearDepth(MainPoolState* arg0, GeoClearDepthNode* arg1);
GeoFogNode* GeoNode_CreateFog(s32 arg0, GeoFogNode* arg1, s16 arg2, s16 arg3, u8 r, u8 g, u8 b, u8 a);
GeoLightNode* GeoNode_CreateLight(MainPoolState* arg0, GeoLightNode* arg1, s16 arg2, s16 arg3, u8 r, u8 g,
                                    u8 b, u8 a);
GeoAmbientLightNode* GeoNode_CreateAmbientLight(MainPoolState* arg0, GeoAmbientLightNode* arg1, u8 r, u8 g, u8 b);
GeoTextureBankNode* GeoNode_CreateTextureBank(MainPoolState* arg0, GeoTextureBankNode* arg1, s32 arg2, GeoTexture* arg3, s32 arg4,
                              GeoPalette* arg5, s32 arg6, Vtx* arg7);
GeoShadowNode* GeoNode_CreateShadow(MainPoolState* arg0, GeoShadowNode* arg1, s16 arg2, s16 arg3, s16 arg4,
                                    s16 arg5);
GeoCullDistanceNode* GeoNode_CreateCullDistance(MainPoolState* arg0, GeoCullDistanceNode* arg1, s16 arg2, s16 arg3);
GeoSwitchCaseNode* GeoNode_CreateSwitchCase(MainPoolState* arg0, GeoSwitchCaseNode* arg1, s16 arg2, s16 arg3);
GeoTranslateRotateNode* GeoNode_CreateTranslateRotate(MainPoolState* arg0, GeoTranslateRotateNode* arg1, Vec3f* arg2, Vec3s* arg3);
GeoTranslateNode* GeoNode_CreateTranslate(MainPoolState* arg0, GeoTranslateNode* arg1, Vec3f* arg2);
GeoAnimatedPartNode* GeoNode_CreateAnimatedPart(MainPoolState* arg0, GeoAnimatedPartNode* arg1, s16 arg2, s16 arg3, s16 arg4,
                                   Vec3s* arg5, Vec3s* arg6, Vec3f* arg7);
GeoDisplayListPartNode* GeoNode_CreateDisplayListPart(MainPoolState* arg0, GeoDisplayListPartNode* arg1, s32 arg2, Gfx* arg3, s16 arg4);
DisplayObject* GeoNode_CreateModelPart(MainPoolState* arg0, DisplayObject* arg1, s16 arg2, Vec3f* arg3,
                                      Vec3s* arg4, Vec3f* arg5);
GeoDisplayListMatrixNode* GeoNode_CreateDisplayListMatrix(MainPoolState* arg0, GeoDisplayListMatrixNode* arg1, s32 arg2, Gfx* arg3, MtxF* arg4);
GeoDisplayListMatrixNode* GeoNode_CreateDisplayListMatrixFromTransform(MainPoolState* arg0, GeoDisplayListMatrixNode* arg1, s32 arg2, Gfx* arg3, Vec3f* arg4,
                                   Vec3s* arg5);
GeoBillboardNode* GeoNode_CreateBillboard(MainPoolState* arg0, GeoBillboardNode* arg1, s32 arg2, Gfx* arg3, Vec3f* arg4,
                                   f32 arg5);
GeoDisplayListNode* GeoNode_CreateDisplayList(MainPoolState* arg0, GeoDisplayListNode* arg1, s32 arg2, Gfx* arg3);
GeoMaterialNode* GeoNode_CreateMaterial(MainPoolState* arg0, GeoMaterialNode* arg1, s16 arg2, s16 arg3, Gfx* arg4,
                                    s16 arg5, s16 arg6, u8 r, u8 g, u8 b, u8 a);
GeoAnchorNode* GeoNode_CreateAnchor(MainPoolState* arg0, GeoAnchorNode* arg1, s16 arg2);
GeoGroupNode* GeoNode_CreateGroup(MainPoolState* arg0, GeoGroupNode* arg1, s32 arg2, s16 arg3, s16 arg4,
                                    s16 arg5, s16 arg6, s16 arg7, s16 arg8, s32 arg9, u8 r, u8 g, u8 b, u8 a);
void GeoCamera_SetViewport(CameraNode* arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4);
void GeoCamera_SetPerspective(CameraNode* arg0, f32 arg1, f32 arg2, f32 arg3);
void GeoCamera_SetEyeAtUp(CameraNode* arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, s32 arg7);
void GeoCamera_SetBackground(CameraNode* arg0, s16 arg1, s16 arg2, u8 arg3, u8 arg4, u8 arg5);
void GeoCamera_SetBackgroundTexture(CameraNode* arg0, s16 arg1, s16 arg2, s32 arg3, u32 arg4);
void GraphNode_AppendChild(GraphNode* arg0, GraphNode* arg1);
void GraphNode_RemoveChild(GraphNode* arg0, GraphNode* arg1);
GraphNode* GraphNode_GetChildAtIndex(GraphNode* arg0, s32 arg1);
void ModelAnim_ClearTransformChannel(DisplayObject* display_object);
s32 ModelAnim_BindTransformCurve(DisplayObject* display_object, s16 animation_id, void* address, s32 speed);
s32 ModelAnim_SetSpeed(DisplayObject* display_object, s32 speed);
void ModelAnim_SetFrame(DisplayObject* display_object, s16 animation_timer);
s32 ModelAnim_HasCrossedFrame(DisplayObject* arg0, s16 arg1);
s32 ModelAnim_IsAnimationDone(DisplayObject* display_object);
s32 ModelAnim_IsFinished(DisplayObject* arg0);
void ModelAnim_ClearEventTrack(DisplayObject* arg0);
s16 ModelAnim_BindEventTrack(DisplayObject* arg0, s16 arg1, s32 arg2);
void ModelAnim_SetEventFrame(DisplayObject* display_object, s16 frame_number);

/**
 * Initializes the common header of a graph node with its type and default
 * flags.
 */
void GeoNode_Init(GraphNode* arg0, u8 arg1) {
    if (arg0 != NULL) {
        arg0->type = arg1;
        arg0->flags = 0x11;
        arg0->renderFlags = 0;
        arg0->renderLayer = 0;
        arg0->prevSibling = arg0;
        arg0->nextSibling = arg0;
        arg0->children = NULL;
        arg0->callback = NULL;
        arg0->callbackArg = NULL;
    }
}

/**
 * Sets the callback and its argument on a graph node, converting the callback
 * address to a virtual address.
 */
void GeoNode_SetCallback(GraphNode* arg0, GraphNodeCallback arg1, void* arg2) {
    if (arg1 != NULL) {
        arg1 = Util_ConvertAddrToVirtAddr(arg1);
    }

    if (arg0 != NULL) {
        arg0->callbackArg = arg2;
        arg0->callback = arg1;
        if (arg1 != NULL) {
            arg1(0, arg0);
        }
    }
}

/** Allocates a container graph node, or initializes the given storage. */
GraphNode* GeoNode_CreateContainer(MainPoolState* arg0, GraphNode* arg1) {
    if (arg0 != NULL) {
        arg1 = MainPool_AllocAligned(arg0, sizeof(struct GraphNode), 4);
    }

    if (arg1 != NULL) {
        GeoNode_Init(arg1, 0);
    }

    return arg1;
}

/** Allocates a graph node that references another graph node. */
GeoReferenceNode* GeoNode_CreateWithReference(MainPoolState* arg0, GeoReferenceNode* arg1, GraphNode* arg2) {
    if (arg0 != NULL) {
        arg1 = MainPool_AllocAligned(arg0, sizeof(GeoReferenceNode), 4);
    }

    if (arg1 != NULL) {
        arg1->target = arg2;
        GeoNode_Init(arg1, 1);
    }

    return arg1;
}

/** Allocates a camera graph node with the given viewport. */
CameraNode* GeoNode_CreateCamera(MemoryBlock* arg0, CameraNode* arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5) {
    if (arg0 != NULL) {
        arg1 = MainPool_AllocAligned(arg0, sizeof(CameraNode), 4);
    }

    if (arg1 != NULL) {
        GeoCamera_SetViewport(arg1, arg2, arg3, arg4, arg5);
        GeoCamera_SetPerspective(arg1, 30.0f, 100.0f, 12800.0f);
        GeoCamera_SetEyeAtUp(arg1, 0.0f, 512.0f, 4096.0f, 0.0f, 0.0f, 0.0f, 0);
        GeoCamera_SetBackground(arg1, 2, 0, 0, 0, 0);
        GeoNode_Init(arg1, 2);
    }
    return arg1;
}

/** Allocates a type 3 graph node. */
GeoType3Node* GeoNode_CreateType3(MemoryBlock* arg0, GeoType3Node* arg1, s16 arg2) {
    if (arg0 != NULL) {
        arg1 = MainPool_AllocAligned(arg0, sizeof(GeoType3Node), 4);
    }

    if (arg1 != NULL) {
        arg1->unk_18 = arg2;
        GeoNode_Init(arg1, 3);
    }

    return arg1;
}

/** Allocates a type 4 (model root) graph node. */
GeoModelRootNode* GeoNode_CreateType4(MemoryBlock* arg0, GeoModelRootNode* arg1, s16 arg2) {
    if (arg0 != NULL) {
        arg1 = MainPool_AllocAligned(arg0, 0x24, 4);
    }

    if (arg1 != NULL) {
        arg1->rootId = arg2;
        arg1->unk_1A = 0;
        GeoNode_Init(arg1, 4);
    }

    return arg1;
}

/** Allocates an orthographic projection graph node. */
GeoOrthoNode* GeoNode_CreateOrtho(MainPoolState* arg0, GeoOrthoNode* arg1, s16 arg2) {
    if (arg0 != NULL) {
        arg1 = MainPool_AllocAligned(arg0, 0x60, 4);
    }

    if (arg1 != NULL) {
        GeoNode_Init(arg1, 5);
        arg1->node.renderFlags |= arg2 & 3;
    }

    return arg1;
}

/** Allocates a perspective projection graph node. */
GeoPerspectiveNode* GeoNode_CreatePerspective(MainPoolState* arg0, GeoPerspectiveNode* arg1, s16 arg2) {
    if (arg0 != NULL) {
        arg1 = MainPool_AllocAligned(arg0, 0x60 /* sizeof(GeoPerspectiveNode) */, 4);
    }

    if (arg1 != NULL) {
        GeoNode_Init(arg1, 6);
        arg1->node.renderFlags |= arg2 & 3;
    }

    return arg1;
}

/** Allocates a background graph node with the given fill color. */
GeoBackgroundNode* GeoNode_CreateBackground(MainPoolState* arg0, GeoBackgroundNode* arg1, u8 arg2, u8 arg3, u8 arg4) {
    u32 temp_v0;

    if (arg0 != NULL) {
        arg1 = MainPool_AllocAligned(arg0, sizeof(GeoBackgroundNode), 4);
    }

    if (arg1 != NULL) {
        temp_v0 = ((arg2 >> 3) << 0xB) | ((arg3 >> 3) << 6) | ((arg4 >> 3) << 1) | 1;
        arg1->fillColor = (temp_v0 << 0x10) | temp_v0;
        GeoNode_Init(arg1, 7);
    }
    return arg1;
}

/** Allocates a graph node that clears the depth buffer. */
GeoClearDepthNode* GeoNode_CreateClearDepth(MainPoolState* arg0, GeoClearDepthNode* arg1) {
    if (arg0 != NULL) {
        arg1 = MainPool_AllocAligned(arg0, sizeof(GeoClearDepthNode), 4);
    }

    if (arg1 != NULL) {
        GeoNode_Init(arg1, 8);
    }

    return arg1;
}

/** Allocates a fog graph node with a fog range and color. */
GeoFogNode* GeoNode_CreateFog(s32 arg0, GeoFogNode* arg1, s16 arg2, s16 arg3, u8 r, u8 g, u8 b, u8 a) {
    if (arg0 != 0) {
        arg1 = MainPool_AllocAligned(arg0, sizeof(GeoFogNode), 4);
    }

    if (arg1 != NULL) {
        arg1->fog.near = arg2;
        arg1->fog.far = arg3;
        arg1->fog.color.rgba = (r << 0x18) | (g << 0x10) | (b << 8) | a;
        GeoNode_Init(arg1, 0xA);
    }

    return arg1;
}

/**
 * Allocates a directional light graph node (type 0xB) with a color and two s16 light
 * parameters (stored at 0x1C and 0x1E). Allocates from arg0 if given, else uses arg1.
 */
GeoLightNode* GeoNode_CreateLight(MainPoolState* arg0, GeoLightNode* arg1, s16 arg2, s16 arg3, u8 r, u8 g,
                                    u8 b, u8 a) {
    if (arg0 != NULL) {
        arg1 = MainPool_AllocAligned(arg0, sizeof(GeoLightNode), 4);
    }

    if (arg1 != NULL) {
        arg1->color.r = r;
        arg1->color.g = g;
        arg1->color.b = b;
        arg1->color.a = a;
        arg1->pitch = arg2;
        arg1->yaw = arg3;
        GeoNode_Init(arg1, 0xB);
    }

    return arg1;
}

/** Allocates an ambient light graph node with the given color. */
GeoAmbientLightNode* GeoNode_CreateAmbientLight(MainPoolState* arg0, GeoAmbientLightNode* arg1, u8 r, u8 g, u8 b) {
    if (arg0 != NULL) {
        arg1 = MainPool_AllocAligned(arg0, sizeof(GeoAmbientLightNode), 4);
    }

    if (arg1 != NULL) {
        arg1->r = r;
        arg1->g = g;
        arg1->b = b;
        GeoNode_Init(arg1, 0xD);
    }

    return arg1;
}

/**
 * Allocates a graph node of type 0xE that holds three tables with their counts (arg3/arg2,
 * arg5/arg4, arg7/arg6): a texture bank (textures, palettes, vertices) for the material nodes below it.
 */
GeoTextureBankNode* GeoNode_CreateTextureBank(MainPoolState* arg0, GeoTextureBankNode* arg1, s32 arg2, GeoTexture* arg3, s32 arg4,
                              GeoPalette* arg5, s32 arg6, Vtx* arg7) {
    if (arg0 != NULL) {
        arg1 = MainPool_AllocAligned(arg0, sizeof(GeoTextureBankNode), 4);
    }

    if (arg1 != NULL) {
        arg1->textures = arg3;
        arg1->palettes = arg5;
        arg1->vertices = arg7;
        arg1->textureCount = arg2;
        arg1->paletteCount = arg4;
        arg1->vertexCount = arg6;
        arg1->unk_28 = NULL;
        GeoNode_Init(arg1, 0xE);
    }

    return arg1;
}

/**
 * Allocates a shadow graph node (type 0xF) with four s16 parameters.
 */
GeoShadowNode* GeoNode_CreateShadow(MainPoolState* arg0, GeoShadowNode* arg1, s16 arg2, s16 arg3, s16 arg4,
                                    s16 arg5) {
    if (arg0 != NULL) {
        arg1 = MainPool_AllocAligned(arg0, sizeof(GeoShadowNode), 4);
    }

    if (arg1 != NULL) {
        arg1->shape = arg2;
        arg1->scaleXPercent = arg3;
        arg1->scaleZPercent = arg4;
        arg1->heightOffset = arg5;
        GeoNode_Init(arg1, 0xF);
    }

    return arg1;
}

/** Allocates a graph node that culls its children beyond a distance range. */
GeoCullDistanceNode* GeoNode_CreateCullDistance(MainPoolState* arg0, GeoCullDistanceNode* arg1, s16 arg2, s16 arg3) {
    if (arg0 != NULL) {
        arg1 = MainPool_AllocAligned(arg0, sizeof(GeoCullDistanceNode), 4);
    }

    if (arg1 != NULL) {
        arg1->unk_18 = arg2;
        arg1->unk_1A = arg3;
        GeoNode_Init(arg1, 0x10);
    }

    return arg1;
}

/**
 * Allocates a switch-case graph node that processes one child chosen by index.
 */
GeoSwitchCaseNode* GeoNode_CreateSwitchCase(MainPoolState* arg0, GeoSwitchCaseNode* arg1, s16 arg2, s16 arg3) {
    if (arg0 != NULL) {
        arg1 = MainPool_AllocAligned(arg0, sizeof(GeoSwitchCaseNode), 4);
    }

    if (arg1 != NULL) {
        arg1->unk_18 = arg2;
        arg1->selectedChild = arg3;
        GeoNode_Init(arg1, 0x11);
    }

    return arg1;
}

/** Allocates a graph node with a translation and a rotation. */
GeoTranslateRotateNode* GeoNode_CreateTranslateRotate(MainPoolState* arg0, GeoTranslateRotateNode* arg1, Vec3f* arg2, Vec3s* arg3) {
    if (arg0 != NULL) {
        arg1 = MainPool_AllocAligned(arg0, sizeof(GeoTranslateRotateNode), 4);
    }

    if (arg1 != NULL) {
        arg1->translation = *arg2;
        arg1->rotation = *arg3;
        GeoNode_Init(arg1, 0x12);
    }

    return arg1;
}

/** Allocates a graph node with a translation. */
GeoTranslateNode* GeoNode_CreateTranslate(MainPoolState* arg0, GeoTranslateNode* arg1, Vec3f* arg2) {
    if (arg0 != NULL) {
        arg1 = MainPool_AllocAligned(arg0, sizeof(GeoTranslateNode), 4);
    }

    if (arg1 != NULL) {
        arg1->translation = *arg2;
        GeoNode_Init(arg1, 0x13);
    }

    return arg1;
}

/**
 * Allocates an animated part graph node (type 0x14) with a translation, rotation and
 * scale and three s16 part parameters.
 */
GeoAnimatedPartNode* GeoNode_CreateAnimatedPart(MainPoolState* arg0, GeoAnimatedPartNode* arg1, s16 arg2, s16 arg3, s16 arg4,
                                   Vec3s* arg5, Vec3s* arg6, Vec3f* arg7) {
    if (arg0 != NULL) {
        arg1 = MainPool_AllocAligned(arg0, sizeof(GeoAnimatedPartNode), 4);
    }

    if (arg1 != NULL) {
        arg1->translation = *arg5;
        arg1->rotation = *arg6;
        arg1->scale = *arg7;
        arg1->matrixSlot = arg2;
        arg1->transformMode = arg3;
        arg1->channelGroup = arg4;
        GeoNode_Init(arg1, 0x14);
    }

    return arg1;
}

/** Allocates a graph node that draws a display list as a model part. */
GeoDisplayListPartNode* GeoNode_CreateDisplayListPart(MainPoolState* arg0, GeoDisplayListPartNode* arg1, s32 arg2, Gfx* arg3, s16 arg4) {
    if (arg0 != NULL) {
        arg1 = MainPool_AllocAligned(arg0, sizeof(GeoDisplayListPartNode), 4);
    }

    if (arg1 != NULL) {
        arg1->displayList = arg3;
        arg1->matrixSlot = arg4;
        GeoNode_Init(arg1, 0x15);
        arg1->node.renderLayer = arg2;
    }

    return arg1;
}

/**
 * Allocates a model part display object (graph node type 0x16) at a position, rotation
 * and scale, with full alpha, white fog and tint, and no animation.
 */
DisplayObject* GeoNode_CreateModelPart(MainPoolState* arg0, DisplayObject* arg1, s16 arg2, Vec3f* arg3,
                                      Vec3s* arg4, Vec3f* arg5) {
    if (arg0 != 0) {
        arg1 = MainPool_AllocAligned(arg0, sizeof(DisplayObject), 4);
    }

    if (arg1 != NULL) {
        arg1->rootId = 0;
        arg1->objectType = arg2;
        arg1->position = *arg3;
        arg1->scale = *arg5;
        arg1->rotation = *arg4;
        arg1->alpha = 0xFF;
        arg1->textureMode = 0;
        arg1->effectSlot = 0;
        arg1->fogColor.rgba = 0xFFFFFF00;
        arg1->textureTint.rgba = 0xFFFFFF00;
        arg1->transformAnim.animationId = 0;
        arg1->transformAnim.data = NULL;
        arg1->transformAnim.frameFixed = 0;
        arg1->transformAnim.speedFixed = 0x10000;
        arg1->transformAnim.lastRenderFrame = 0;
        arg1->eventTrack.trackId = 0;
        arg1->eventTrack.data = NULL;
        arg1->eventTrack.frame = 0;
        arg1->eventTrack.lastRenderFrame = 0;
        GeoNode_Init(&arg1->node, 0x16);
        arg1->node.renderFlags |= 0x60;
    }

    return arg1;
}

/** Allocates a graph node that draws a display list with its own matrix. */
GeoDisplayListMatrixNode* GeoNode_CreateDisplayListMatrix(MainPoolState* arg0, GeoDisplayListMatrixNode* arg1, s32 arg2, Gfx* arg3, MtxF* arg4) {
    if (arg0 != NULL) {
        arg1 = MainPool_AllocAligned(arg0, sizeof(GeoDisplayListMatrixNode), 4);
    }

    if (arg1 != NULL) {
        arg1->displayList = arg3;
        if (arg4 == NULL) {
            MtxF_Identity(&arg1->matrix);
        } else {
            MtxF_Copy(&arg1->matrix, arg4);
        }
        GeoNode_Init(arg1, 0x17);
        arg1->node.renderLayer = arg2;
    }

    return arg1;
}

/**
 * Builds a matrix from a translation and rotation, then allocates a display list matrix
 * node with it.
 */
GeoDisplayListMatrixNode* GeoNode_CreateDisplayListMatrixFromTransform(MainPoolState* arg0, GeoDisplayListMatrixNode* arg1, s32 arg2, Gfx* arg3, Vec3f* arg4,
                                   Vec3s* arg5) {
    MtxF sp20;

    MtxF_SetRotationTranslationF(&sp20, arg4, arg5);
    return GeoNode_CreateDisplayListMatrix(arg0, arg1, arg2, arg3, &sp20);
}

/**
 * Allocates a scale graph node (type 0x18) on render layer arg2 that draws display list
 * arg3 at offset arg4 scaled by arg5.
 */
GeoBillboardNode* GeoNode_CreateBillboard(MainPoolState* arg0, GeoBillboardNode* arg1, s32 arg2, Gfx* arg3, Vec3f* arg4,
                                   f32 arg5) {
    if (arg0 != NULL) {
        arg1 = MainPool_AllocAligned(arg0, sizeof(GeoBillboardNode), 4);
    }

    if (arg1 != NULL) {
        arg1->position = *arg4;
        arg1->unk_28 = arg5;
        arg1->displayList = arg3;
        GeoNode_Init(arg1, 0x18);
        arg1->node.renderLayer = arg2;
    }

    return arg1;
}

/** Allocates a graph node that draws a display list. */
GeoDisplayListNode* GeoNode_CreateDisplayList(MainPoolState* arg0, GeoDisplayListNode* arg1, s32 arg2, Gfx* arg3) {
    if (arg0 != NULL) {
        arg1 = MainPool_AllocAligned(arg0, sizeof(GeoDisplayListNode), 4);
    }

    if (arg1 != NULL) {
        arg1->displayList = arg3;
        GeoNode_Init(arg1, 0x19);
        arg1->node.renderLayer = arg2;
    }

    return arg1;
}

/**
 * Allocates a material graph node (type 0x1A) with a display list, size parameters
 * and an RGBA color.
 */
GeoMaterialNode* GeoNode_CreateMaterial(MainPoolState* arg0, GeoMaterialNode* arg1, s16 arg2, s16 arg3, Gfx* arg4,
                                    s16 arg5, s16 arg6, u8 r, u8 g, u8 b, u8 a) {
    if (arg0 != NULL) {
        arg1 = MainPool_AllocAligned(arg0, sizeof(GeoMaterialNode), 4);
    }

    if (arg1 != NULL) {
        arg1->mode = arg2;
        arg1->eventIndex = arg3;
        arg1->displayList = arg4;
        arg1->textureIndex = arg5;
        arg1->paletteIndex = arg6;
        arg1->color.rgba = (r << 0x18) | (g << 0x10) | (b << 8) | a;
        GeoNode_Init(arg1, 0x1A);
    }

    return arg1;
}

/**
 * Allocates an anchor graph node that records a position for attaching other
 * objects.
 */
GeoAnchorNode* GeoNode_CreateAnchor(MainPoolState* arg0, GeoAnchorNode* arg1, s16 arg2) {
    if (arg0 != NULL) {
        arg1 = MainPool_AllocAligned(arg0, sizeof(GeoAnchorNode), 4);
    }

    if (arg1 != NULL) {
        arg1->anchorId = arg2;
        GeoNode_Init(arg1, 0x1B);
    }

    return arg1;
}

/**
 * Allocates a group graph node (type 0x1C) on render layer arg2 with six s16 parameters, a
 * word parameter and an RGBA color.
 */
GeoGroupNode* GeoNode_CreateGroup(MainPoolState* arg0, GeoGroupNode* arg1, s32 arg2, s16 arg3, s16 arg4,
                                    s16 arg5, s16 arg6, s16 arg7, s16 arg8, s32 arg9, u8 r, u8 g, u8 b, u8 a) {
    if (arg0 != NULL) {
        arg1 = MainPool_AllocAligned(arg0, sizeof(GeoGroupNode), 4);
    }

    if (arg1 != NULL) {
        arg1->unk_1C = arg3;
        arg1->unk_1E = arg4;
        arg1->unk_20 = arg5;
        arg1->unk_22 = arg6;
        arg1->unk_18 = arg7;
        arg1->unk_1A = arg8;
        arg1->unk_24 = arg9;
        arg1->unk_28.rgba = (r << 0x18) | (g << 0x10) | (b << 8) | a;
        GeoNode_Init(arg1, 0x1C);
        arg1->node.renderLayer = arg2;
    }

    return arg1;
}

/** Sets the viewport rectangle of a camera node. */
void GeoCamera_SetViewport(CameraNode* arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4) {
    arg0->viewport.x = arg1;
    arg0->viewport.y = arg2;
    arg0->viewport.width = arg3;
    arg0->viewport.height = arg4;

    arg0->orthographic.unk_04 = -arg3 * 0.5f;
    arg0->orthographic.unk_08 = arg3 * 0.5f;
    arg0->orthographic.unk_10 = arg4 * 0.5f;
    arg0->orthographic.unk_0C = -arg4 * 0.5f;
    arg0->orthographic.unk_14 = -2.0f;
    arg0->orthographic.unk_18 = 2.0f;
    arg0->orthographic.unk_1C = 1.0f;
}

/**
 * Sets the field of view and clip planes of a camera node, deriving the aspect
 * ratio from its viewport.
 */
void GeoCamera_SetPerspective(CameraNode* arg0, f32 arg1, f32 arg2, f32 arg3) {
    arg0->perspective.unk_0C = (f32)arg0->viewport.width / arg0->viewport.height;
    arg0->perspective.verticalFieldOfView = arg1;
    arg0->perspective.nearPlane = arg2;
    arg0->perspective.farPlane = arg3;
    arg0->perspective.unk_18 = 1.0f;
}

/** Sets the eye position, look-at point and up vector of a camera node. */
void GeoCamera_SetEyeAtUp(CameraNode* arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, s32 arg7) {
    CameraView* sp1C = &arg0->view;
    f32 sp28 = arg4 - arg1;
    f32 sp24 = arg6 - arg3;
    f32 temp_fv1_2 = -1.0 / sqrtf(SQ(sp28) + SQ(sp24));

    sp28 *= temp_fv1_2;
    sp24 *= temp_fv1_2;

    Vec3f_SetComponentsDuplicate(&sp1C->eyePosition, arg1, arg2, arg3);
    Vec3f_SetComponentsDuplicate(&sp1C->targetPosition, arg4, arg5, arg6);
    Vec3f_SetComponentsDuplicate(&sp1C->upDirection, SINS(arg7) * sp24, COSS(arg7), -SINS(arg7) * sp28);
}

/** Sets the fill color overlay of a camera node. */
void GeoCamera_SetBackground(CameraNode* arg0, s16 arg1, s16 arg2, u8 arg3, u8 arg4, u8 arg5) {
    CameraOverlay* ptr = &arg0->overlay;

    if (arg2 < 2) {
        if ((arg1 == 2) || (arg1 == 4)) {
            ptr->mode = 0;
        } else {
            ptr->mode = 1;
        }
    } else {
        ptr->mode = arg1;
        ptr->stepCount = arg2;
        ptr->stepIndex = 1;
        ptr->color.r = arg3;
        ptr->color.g = arg4;
        ptr->color.b = arg5;
    }
}

/** Sets the background texture overlay of a camera node. */
void GeoCamera_SetBackgroundTexture(CameraNode* arg0, s16 arg1, s16 arg2, s32 arg3, u32 arg4) {
    CameraOverlay* ptr = &arg0->overlay;
    ptr->unk_0C = arg1;
    ptr->unk_0E = arg2;
    ptr->unk_10 = 0;
    ptr->unk_12 = 0;
    ptr->unk_14 = 0;
    ptr->unk_16 = 0;
    ptr->unk_18 = 0;
    ptr->unk_1A = 0;
    ptr->unk_02 = 0;
    ptr->unk_1C = D_1000800;
}

/** Appends a node to the end of a parent graph node's child list. */
void GraphNode_AppendChild(GraphNode* arg0, GraphNode* arg1) {
    GraphNode* temp_v0;
    GraphNode* temp_v1;

    if ((arg0 != NULL) && (arg1 != NULL)) {
        temp_v0 = arg0->children;
        if (temp_v0 == NULL) {
            arg0->children = arg1;
            arg1->prevSibling = arg1;
            arg1->nextSibling = arg1;
        } else {
            temp_v1 = temp_v0->prevSibling;
            arg1->nextSibling = temp_v0;
            arg1->prevSibling = temp_v1;
            temp_v0->prevSibling = arg1;
            temp_v1->nextSibling = arg1;
        }
    }
}

/** Unlinks a node from its sibling list. */
void GraphNode_RemoveChild(GraphNode* arg0, GraphNode* arg1) {
    arg1->prevSibling->nextSibling = arg1->nextSibling;
    arg1->nextSibling->prevSibling = arg1->prevSibling;
    if ((CameraNode*)arg1 == arg0->children) {
        if (arg1 == arg1->nextSibling) {
            arg0->children = NULL;
            return;
        }
        arg0->children = (CameraNode*)arg1->nextSibling;
    }
}

/** Returns the child of a graph node at the given index. */
GraphNode* GraphNode_GetChildAtIndex(GraphNode* arg0, s32 arg1) {
    GraphNode* var_v1;
    s32 i;
    var_v1 = (GraphNode*)arg0->children;
    if (var_v1 != NULL) {
        for (i = 0; i < arg1; i++) {
            var_v1 = var_v1->nextSibling;
        }
    }
    return var_v1;
}

/** Detaches the transform animation from a display object. */
void ModelAnim_ClearTransformChannel(DisplayObject* display_object) {
    display_object->transformAnim.animationId = -1;
    display_object->transformAnim.data = NULL;
}

/**
 * Attaches a transform animation curve to a display object and sets its
 * playback speed.
 */
s32 ModelAnim_BindTransformCurve(DisplayObject* display_object, s16 animation_id, void* address, s32 speed) {
    TransformAnimData* transform_addr = Util_ConvertAddrToVirtAddr(address);
    TransformAnimState* transform_anim = &display_object->transformAnim;

    if ((transform_addr != transform_anim->data) || (animation_id != transform_anim->animationId)) {
        transform_anim->animationId = animation_id;
        transform_anim->data = transform_addr;
        transform_anim->frameFixed = (transform_addr->startFrame << 16) - speed;
    }

    transform_anim->speedFixed = speed;
    return transform_anim->frameFixed >> 16;
}

/** Sets the playback speed of a display object's transform animation. */
s32 ModelAnim_SetSpeed(DisplayObject* display_object, s32 speed) {
    display_object->transformAnim.speedFixed = speed;
    return display_object->transformAnim.frameFixed >> 0x10;
}

/** Sets the current frame of a display object's transform animation. */
void ModelAnim_SetFrame(DisplayObject* display_object, s16 animation_timer) {
    display_object->transformAnim.frameFixed = (animation_timer << 0x10) - display_object->transformAnim.speedFixed;
}

/**
 * Returns whether the transform animation has reached or passed the given
 * frame.
 */
s32 ModelAnim_HasCrossedFrame(DisplayObject* arg0, s16 arg1) {
    TransformAnimState* ptr = &arg0->transformAnim;
    s32 temp_v0 = ptr->frameFixed + ptr->speedFixed;
    s32 arg = arg1 << 0x10;
    s32 var_a2;
    s32 v = ptr->speedFixed;

    if (v >= 0) {
        var_a2 = ptr->frameFixed < arg;
        if (var_a2 != 0) {
            var_a2 = temp_v0 >= arg;
        }
    } else {
        var_a2 = (arg < ptr->frameFixed);
        if (var_a2 != 0) {
            var_a2 = arg >= temp_v0;
        }
    }

    return var_a2;
}

/** Returns whether the transform animation has reached its final frame. */
s32 ModelAnim_IsAnimationDone(DisplayObject* display_object) {
    return ModelAnim_HasCrossedFrame(display_object, display_object->transformAnim.data->endFrame - 1);
}

/** Returns whether the transform animation is on or past its last frame. */
s32 ModelAnim_IsFinished(DisplayObject* arg0) {
    return arg0->transformAnim.frameFixed >= ((arg0->transformAnim.data->endFrame - 1) << 0x10);
}

/** Detaches the event track from a display object. */
void ModelAnim_ClearEventTrack(DisplayObject* arg0) {
    arg0->eventTrack.trackId = -1;
    arg0->eventTrack.data = 0;
}

/** Attaches an event track to a display object. */
s16 ModelAnim_BindEventTrack(DisplayObject* arg0, s16 arg1, s32 arg2) {
    EventTrackData* temp_v0 = Util_ConvertAddrToVirtAddr(arg2);
    EventTrackState* ptr = &arg0->eventTrack;

    if ((temp_v0 != ptr->data) || (arg1 != ptr->trackId)) {
        ptr->trackId = arg1;
        ptr->data = temp_v0;
        ptr->frame = temp_v0->startFrame - 1;
    }

    return ptr->frame;
}

/** Sets the current frame of a display object's event track. */
void ModelAnim_SetEventFrame(DisplayObject* display_object, s16 frame_number) {
    display_object->eventTrack.frame = frame_number - 1;
}
