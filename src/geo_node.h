/* Declarations for src/geo_node.c. */
#ifndef GEO_NODE_H
#define GEO_NODE_H

#include "global.h"
#include "math.h"
#include "moves.h"
#include "pokemon.h"
#include "status.h"
#include "m2c_macros.h"
#include "stdarg.h"

/* Struct types that were defined identically in each of these files; this is
 * now the one definition they all include:
 * src/geo_node.c
 * src/geo_render.c
 */

typedef struct unk_func_80016B30_arg0 {
    /* 0x00 */ Vec3s vec;
    /* 0x06 */ s16 unk_06;
} unk_func_80016B30_arg0;

#include "memory.h"

// geo_node.c
void GeoNode_Init(GraphNode* arg0, u8 arg1);
void GeoNode_SetCallback(GraphNode* arg0, GraphNodeCallback arg1, void* arg2);
GraphNode* GeoNode_CreateContainer(MainPoolState* arg0, GraphNode* arg1);
GeoReferenceNode* GeoNode_CreateWithReference(MainPoolState* arg0, GeoReferenceNode* arg1, GraphNode* arg2);
CameraNode* GeoNode_CreateCamera(MemoryBlock* arg0, CameraNode* arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5);
GeoType3Node* GeoNode_CreateType3(MemoryBlock* arg0, GeoType3Node* arg1, s16 arg2);
GeoModelRootNode* GeoNode_CreateType4(MemoryBlock* arg0, GeoModelRootNode* arg1, s16 arg2);
GeoOrthoNode* GeoNode_CreateOrtho(MainPoolState* arg0, GeoOrthoNode* arg1, s16 arg2);
GeoPerspectiveNode* GeoNode_CreatePerspective(MainPoolState* arg0, GeoPerspectiveNode* arg1, s16 arg2);
GeoBackgroundNode* GeoNode_CreateBackground(MainPoolState* arg0, GeoBackgroundNode* arg1, u8 arg2, u8 arg3, u8 arg4);
GeoClearDepthNode* GeoNode_CreateClearDepth(MainPoolState* arg0, GeoClearDepthNode* arg1);
GeoFogNode* GeoNode_CreateFog(s32 arg0, GeoFogNode* arg1, s16 arg2, s16 arg3, u8 r, u8 g, u8 b, u8 a);
GeoLightNode* GeoNode_CreateLight(MainPoolState* arg0, GeoLightNode* arg1, s16 arg2, s16 arg3, u8 r, u8 g, u8 b, u8 a);
GeoAmbientLightNode* GeoNode_CreateAmbientLight(MainPoolState* arg0, GeoAmbientLightNode* arg1, u8 r, u8 g, u8 b);
GeoTextureBankNode* GeoNode_CreateTextureBank(MainPoolState* arg0, GeoTextureBankNode* arg1, s32 arg2,
                              unk_D_86002F34_018* arg3, s32 arg4, unk_D_86002F34_01C* arg5,
                              s32 arg6, Vtx* arg7);
GeoShadowNode* GeoNode_CreateShadow(MainPoolState* arg0, GeoShadowNode* arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5);
GeoCullDistanceNode* GeoNode_CreateCullDistance(MainPoolState* arg0, GeoCullDistanceNode* arg1, s16 arg2, s16 arg3);
GeoSwitchCaseNode* GeoNode_CreateSwitchCase(MainPoolState* arg0, GeoSwitchCaseNode* arg1, s16 arg2, s16 arg3);
GeoTranslateRotateNode* GeoNode_CreateTranslateRotate(MainPoolState* arg0, GeoTranslateRotateNode* arg1, Vec3f* arg2, Vec3s* arg3);
GeoTranslateNode* GeoNode_CreateTranslate(MainPoolState* arg0, GeoTranslateNode* arg1, Vec3f* arg2);
GeoAnimatedPartNode* GeoNode_CreateAnimatedPart(MainPoolState* arg0, GeoAnimatedPartNode* arg1, s16 arg2, s16 arg3, s16 arg4, Vec3s* arg5, Vec3s* arg6, Vec3f* arg7);
GeoDisplayListPartNode* GeoNode_CreateDisplayListPart(MainPoolState* arg0, GeoDisplayListPartNode* arg1, s32 arg2, Gfx* arg3, s16 arg4);
DisplayObject* GeoNode_CreateModelPart(MainPoolState* arg0, DisplayObject* arg1, s16 arg2, Vec3f* arg3,
                                      Vec3s* arg4, Vec3f* arg5);
GeoDisplayListMatrixNode* GeoNode_CreateDisplayListMatrix(MainPoolState* arg0, GeoDisplayListMatrixNode* arg1, s32 arg2, Gfx* arg3, MtxF* arg4);
GeoDisplayListMatrixNode* GeoNode_CreateDisplayListMatrixFromTransform(MainPoolState* arg0, GeoDisplayListMatrixNode* arg1, s32 arg2, Gfx* arg3, Vec3f* arg4, Vec3s* arg5);
GeoBillboardNode* GeoNode_CreateBillboard(MainPoolState* arg0, GeoBillboardNode* arg1, s32 arg2, Gfx* arg3, Vec3f* arg4, f32 arg5);
GeoDisplayListNode* GeoNode_CreateDisplayList(MainPoolState* arg0, GeoDisplayListNode* arg1, s32 arg2, Gfx* arg3);
GeoMaterialNode* GeoNode_CreateMaterial(MainPoolState* arg0, GeoMaterialNode* arg1, s16 arg2, s16 arg3, Gfx* arg4, s16 arg5, s16 arg6, u8 r, u8 g, u8 b, u8 a);
GeoAnchorNode* GeoNode_CreateAnchor(MainPoolState* arg0, GeoAnchorNode* arg1, s16 arg2);
GeoGroupNode* GeoNode_CreateGroup(MainPoolState* arg0, GeoGroupNode* arg1, s32 arg2, s16 arg3, s16 arg4, s16 arg5, s16 arg6, s16 arg7, s16 arg8, s32 arg9,
                                    u8 r, u8 g, u8 b, u8 a);
void GeoCamera_SetViewport(CameraNode* arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4);
void GeoCamera_SetPerspective(CameraNode* arg0, f32 arg1, f32 arg2, f32 arg3);
void GeoCamera_SetEyeAtUp(CameraNode* arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, s32 arg7);
void GeoCamera_SetBackground(CameraNode* arg0, s16 arg1, s16 arg2, u8 arg3, u8 arg4, u8 arg5);
void GeoCamera_SetBackgroundTexture(CameraNode* arg0, s16 arg1, s16 arg2, s32 arg3, u32 arg4);
void GraphNode_AppendChild(GraphNode* parent, GraphNode* child);
void GraphNode_RemoveChild(GraphNode* arg0, GraphNode* arg1);
GraphNode* GraphNode_GetChildAtIndex(GraphNode* arg0, s32 arg1);
s32 func_8001104C(s32);                             /* extern */
s32 ModelAnim_IsAnimationDone(DisplayObject* display_object);
void func_80010F8C(void*, s32);
void func_80010F9C(void*, s32);
M2C_UNK func_80010F14(M2C_UNK *, M2C_UNK, M2C_UNK *, M2C_UNK); /* extern */
M2C_UNK func_8001107C(M2C_UNK *, M2C_UNK, M2C_UNK *); /* extern */
void ModelAnim_ClearTransformChannel(DisplayObject* arg0);
s32 ModelAnim_BindTransformCurve(DisplayObject* arg0, s16 arg1, void* arg2, s32 arg3);
s32 ModelAnim_SetSpeed(DisplayObject* display_object, s32 speed);
void ModelAnim_SetFrame(DisplayObject* display_object, s16 animation_timer);
s32 ModelAnim_HasCrossedFrame(DisplayObject* arg0, s16 arg1);
s32 ModelAnim_IsFinished(DisplayObject* arg0);
void ModelAnim_ClearEventTrack(DisplayObject* arg0);
s16 ModelAnim_BindEventTrack(DisplayObject* arg0, s16 arg1, s32 arg2);
void ModelAnim_SetEventFrame(DisplayObject* display_object, s16 frame_number);

#endif // GEO_NODE_H
