/* Declarations for src/geo_render.c. */
#ifndef GEO_RENDER_H
#define GEO_RENDER_H

#include "global.h"
#include "stdarg.h"
#include "moves.h"
#include "m2c_macros.h"

typedef struct unk_D_800AB970 {
    /* 0x000 */ Vec3f unk_000[1];
    /* 0x00C */ char unk00C[0x174];
    /* 0x180 */ s32 unk_180;
    /* 0x184 */ char unk184[0xC];
} unk_D_800AB970; // size = 0x190?

typedef struct unk_D_800ABB00 {
    /* 0x00 */ void* unk_00;
    /* 0x04 */ void* unk_04;
    /* 0x08 */ char unk08[0x8];
} unk_D_800ABB00; // size >= 0x10?

// Render state cache used while func_80013398 draws the layer lists.
typedef struct GeoLayerRenderState {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 primColor; // @unverified: last gDPSetPrimColor color (func_80012A80)
    /* 0x08 */ s32 fogColor; // @unverified: last G_SETFOGCOLOR word, compared with the layer entry (func_80012C00)
    /* 0x0C */ s32 texture; // @unverified: bound texture; 0 means none (GeoRender_DisableTexture/BindTexture)
    /* 0x10 */ s32 palette; // @unverified: cleared with texture in func_80012A80
    /* 0x14 */ s32 displayList; // @unverified: last material display list (GeoRender_BindTexture)
    /* 0x18 */ u8 combineMode; // @unverified: index into D_80060534 combine modes
    /* 0x19 */ u8 primLodFraction; // @unverified: last gDPSetPrimColor LOD fraction
    /* 0x1A */ u8 unk_1A;
    /* 0x1B */ u8 unk_1B;
    /* 0x1C */ u8 layer;
    /* 0x1D */ u8 flags;
    /* 0x1E */ u8 syncPending; // @unverified: set once a gDPPipeSync has been emitted for the entry
    /* 0x1F */ u8 unk_1F;
} GeoLayerRenderState; // size = 0x20

typedef struct GeoLayerEntry {
    /* 0x00 */ struct GeoLayerEntry* next;
    /* 0x04 */ u8 unk_04;
    /* 0x05 */ u8 textureMode;
    /* 0x06 */ u8 combineMode; // @unverified: index into D_80060534, compared with GeoLayerRenderState.combineMode (func_80012DC8)
    /* 0x07 */ u8 lodFraction;
    /* 0x08 */ s32 dl;
    /* 0x0C */ s32 mtx;
    /* 0x10 */ s32 primColor; // @unverified: RGBA word for gDPSetPrimColor (func_80012D04)
    /* 0x14 */ s32 fogColor; // @unverified: G_SETFOGCOLOR word; low byte nonzero enables fog (func_80012C00/func_80012CC0)
    /* 0x18 */ s32 texture; // @unverified: GeoTextureBankNode texture entry, 0 for none (GeoRender_BindTexture)
    /* 0x1C */ s32 palette; // @unverified: GeoTextureBankNode palette entry or 0 (GeoRender_BindTexture)
    /* 0x20 */ s32 materialDisplayList; // @unverified: called after the texture image is set (GeoRender_BindTexture)
} GeoLayerEntry; // size = 0x24

struct Root80013DC8;

typedef struct ModelAnimChannel {
    /* 0x00 */ u8 scaleKeyCount; // @unverified: keys in the scale curve; 1 means scaleIndex is the constant value (ModelAnim_Evaluate*Channel)
    /* 0x01 */ u8 rotationKeyCount; // @unverified: keys in the rotation curve; 1 means rotationIndex is the constant value (ModelAnim_Evaluate*Channel)
    /* 0x02 */ u8 translationKeyCount; // @unverified: keys in the translation curve; 1 means translationIndex is the constant value (ModelAnim_Evaluate*Channel)
    /* 0x03 */ u8 unk_03;
    /* 0x04 */ u16 scaleIndex; // @unverified: first key in scaleValues, or the constant value (ModelAnim_Evaluate*Channel)
    /* 0x06 */ u16 rotationIndex; // @unverified: first key in rotationValues, or the constant value (ModelAnim_Evaluate*Channel)
    /* 0x08 */ u16 translationIndex; // @unverified: first key in translationValues, or the constant value (ModelAnim_Evaluate*Channel)
} ModelAnimChannel; // size = 0xA

typedef struct ModelAnimCurveContext {
    /* 0x00 */ u8 active; // @unverified: set by ModelAnim_BeginCurveContext, cleared by the model root and model part nodes (ModelAnim_Evaluate*Channel)
    /* 0x01 */ u8 wideTranslation; // @unverified: TransformAnimData.flags & 4: translation keys are 16-bit instead of 12-bit (ModelAnim_Evaluate*Channel)
    /* 0x02 */ s16 frame; // @unverified: whole part of the playback frame, clamped to 0 (ModelAnim_Evaluate*Channel)
    /* 0x04 */ TransformAnimData* data;
    /* 0x08 */ ModelAnimChannel* channels; // @unverified: three channels (x, y, z) per animated part (ModelAnim_Evaluate*Channel)
    /* 0x0C */ s16* scaleValues; // @unverified: s16 thousandths (ModelAnim_Evaluate*Channel)
    /* 0x10 */ s16* rotationValues; // @unverified: 12-bit packed, scaled by 0x10 to binary angles (ModelAnim_Evaluate*Channel)
    /* 0x14 */ s16* translationValues; // @unverified: 12- or 16-bit packed whole units (ModelAnim_Evaluate*Channel)
} ModelAnimCurveContext; // size = 0x18

typedef struct unk_func_80017540_arg1 {
    /* 0x00 */ u16 unk_00;
    /* 0x02 */ u16 unk_02;
} unk_func_80017540_arg1; // size = 0x4

extern s32 D_80060480;

extern u16 D_80060484;

extern GeoType3Node* D_8006048C;

extern GeoModelRootNode* D_80060490;

extern CameraNode* D_80060494;

extern GeoModelRootNode* D_80060498;

extern DisplayObject* D_8006049C;

// geo_render.c
void GeoRender_InitMatrixStack(void);
void GeoRender_CommitMatrix(void);
void GeoRender_SetMatrix(MtxF* arg0);
void GeoRender_PushMultipliedMatrix(MtxF* arg0);
void GeoRender_PushScaledMatrix(Vec3f* arg0);
MtxF* GeoRender_GetRelativeMatrix(s32 arg0);
void GeoRender_ResetTransformStack(void);
void GeoRender_PushScale(Vec3f* arg0);
Vtx* GeoOverlay_BuildFadeQuad(CameraOverlay* arg0, CameraOrthographic* arg1);
void GeoOverlay_DrawFadeQuad(CameraOverlay* arg0, CameraOrthographic* arg1);
void func_80011D14(Vtx* arg0, CameraOverlay* arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5, s16 arg6, s16 arg7);
Vtx* GeoOverlay_BuildRotatingQuad(CameraOverlay* arg0);
void GeoOverlay_DrawRotatingQuad(CameraOverlay* arg0, UNUSED CameraOrthographic* arg1);
void GeoOverlay_Draw(CameraOverlay* arg0, CameraOrthographic* arg1);
void Geo_ProcessNodeChildren(GraphNode* arg0);
void Geo_NodeReference(GraphNode* arg0);
void Geo_NodeCamera(GraphNode* arg0);
void Geo_NodeType3Pass(GraphNode* arg0);
void Geo_NodeModelRoot(GraphNode* arg0);
void Geo_NodeModelPartRoot(struct Root80013DC8* arg0);
void Geo_NodeOrtho(GraphNode* arg0);
void Geo_NodePerspective(GraphNode* arg0);
void Geo_NodeBackground(GraphNode* arg0);
void Geo_NodeClearDepth(UNUSED GraphNode* arg0);
void Geo_NodeType9Empty(UNUSED GraphNode* arg0);
void Geo_NodeType12Empty(UNUSED GraphNode* arg0);
void Geo_NodeAmbientLight(GraphNode* arg0);
void Geo_NodeTextureBank(GraphNode* arg0);
void Geo_NodeSwitchCase(GraphNode* arg0);
void Geo_NodeTranslateRotate(GraphNode* arg0);
void Geo_NodeTranslate(GraphNode* arg0);
void Geo_NodeAnimatedPart(GraphNode* arg0);
void Geo_NodeDisplayListPart(void *arg0);
void Geo_NodeModelPart(GraphNode* arg0);
void Geo_NodeDisplayListMatrix(s8 *arg0);
void Geo_NodeBillboard(s8 *arg0);
void Geo_NodeDisplayList(s8 *arg0);
void GeoRender_RecordAnchorPosition(s32 arg0);
void Geo_NodeAnchor(GraphNode* arg0);
void Geo_NodeShadow(GraphNode* arg0);
void Geo_RenderRootNode(GraphNode* node);
void Geo_ProcessCallbacks(GraphNode* arg0, s32 arg1);
void GeoRender_SetMode(s32 arg0);
void GeoRender_AdvanceFrameCounter(void);
s32 GeoRender_IsModelFrameCurrent(void);
Vec3f* GeoRender_FindAnchorPosition(DisplayObject* display_object, s16 lookup_id, Vec3f* dest);
void GeoRender_SetCombineMode(Gfx* arg0, arg1_func_81407874_014_000_010* arg1);
void GeoRender_DisableTexture(s32* arg0, s32 arg1);
void GeoRender_BindTexture(GeoLayerRenderState* arg0, GeoLayerEntry* arg1);
M2C_UNK func_8001560C(s32);                         /* extern */
M2C_UNK func_800158C0();                            /* extern */
f32 ModelAnim_EvaluateScaleChannel(ModelAnimCurveContext* arg0, s32 arg1);
s16 ModelAnim_EvaluateRotationChannel(ModelAnimCurveContext* arg0, s32 arg1);
f32 ModelAnim_EvaluateTranslationChannel(ModelAnimCurveContext* arg0, s32 arg1);
void ModelAnim_BeginCurveContext(void *arg0, s32 arg1);
s32 ModelAnim_ResolveEventIndex(s32 arg0, unk_func_80017540_arg1* arg1, s32 arg2);
s16 ModelAnim_AdvanceEventFrame(EventTrackState* arg0);

// functions defined in assembly
void GeoRender_EnableTextureGeneration(UNUSED GeoLayerEntry* arg0);

#endif // GEO_RENDER_H
