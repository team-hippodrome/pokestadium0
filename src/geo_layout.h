/* Declarations for src/geo_layout.c. */
#ifndef GEO_LAYOUT_H
#define GEO_LAYOUT_H

#include "global.h"
#include "geo_node.h"

#define GEO_CMD_FLAGS_RESET 0

#define GEO_CMD_FLAGS_SET   1

#define GEO_CMD_FLAGS_CLEAR 2

#define CMD_SIZE_SHIFT (sizeof(void *) >> 3)

#define CMD_PROCESS_OFFSET(offset) (((offset) & 3) | (((offset) & ~3) << CMD_SIZE_SHIFT))

#define cur_geo_cmd_u8(offset) \
    (gGeoLayoutCommand[CMD_PROCESS_OFFSET(offset)])

#define cur_geo_cmd_s16(offset) \
    (*(s16 *) &gGeoLayoutCommand[CMD_PROCESS_OFFSET(offset)])

#define cur_geo_cmd_s32(offset) \
    (*(s32 *) &gGeoLayoutCommand[CMD_PROCESS_OFFSET(offset)])

#define cur_geo_cmd_u32(offset) \
    (*(u32 *) &gGeoLayoutCommand[CMD_PROCESS_OFFSET(offset)])

#define cur_geo_cmd_ptr(offset) \
    (*(void **) &gGeoLayoutCommand[CMD_PROCESS_OFFSET(offset)])

typedef void (*GeoLayoutCommandProc)(void);

typedef struct GeoLayoutCmdBranchAndLink {
    /* 0x00 */ u8 cmd;
    /* 0x02 */ u16 unk_02;
    /* 0x04 */ u8* unk_04;
} GeoLayoutCmdBranchAndLink; // size = 0x8

typedef struct GeoLayoutCmdEnd {
    /* 0x00 */ u8 cmd;
    /* 0x01 */ char pad[3];
} GeoLayoutCmdEnd; // size = 0x4

typedef struct GeoLayoutCmdJump {
    /* 0x00 */ u8 cmd;
    /* 0x04 */ u8* unk_04;
} GeoLayoutCmdJump; // size = 0x8

typedef struct GeoLayoutCmdBranch {
    /* 0x00 */ u8 cmd;
    /* 0x04 */ u8* unk_04;
} GeoLayoutCmdBranch; // size = 0x8

typedef struct GeoLayoutCmdReturn {
    /* 0x00 */ u8 cmd;
    /* 0x01 */ char pad[3];
} GeoLayoutCmdReturn; // size = 0x4

typedef struct GeoLayoutCmdOpenNode {
    /* 0x00 */ u8 cmd;
    /* 0x01 */ char pad[3];
} GeoLayoutCmdOpenNode; // size = 0x4

typedef struct GeoLayoutCmdCloseNode {
    /* 0x00 */ u8 cmd;
    /* 0x01 */ char pad[3];
} GeoLayoutCmdCloseNode; // size = 0x4

typedef struct GeoLayoutCmdAttachNode {
    /* 0x00 */ u8 cmd;
    /* 0x04 */ GeoFogNode* node; // @unverified: used by the AttachNode command
} GeoLayoutCmdAttachNode; // size = 0x8

typedef struct GeoLayoutCmdSetCallback {
    /* 0x00 */ u8 cmd;
    /* 0x04 */ GraphNodeCallback callback; // @unverified: used by the SetCallback command
    /* 0x08 */ unk_D_86002F34_000_014* callbackArg; // @unverified: used by the SetCallback command
} GeoLayoutCmdSetCallback; // size = 0xC

typedef struct GeoLayoutCmdCreateContainer {
    /* 0x00 */ u8 cmd;
    /* 0x01 */ char pad[3];
} GeoLayoutCmdCreateContainer; // size = 0x4

typedef struct GeoLayoutCmdCreateReference {
    /* 0x00 */ u8 cmd;
    /* 0x04 */ GraphNode* target; // @unverified: geo_layout_cmd: GeoNode_CreateReference argument
} GeoLayoutCmdCreateReference; // size = 0x8

typedef struct GeoLayoutCmdCreateCamera {
    /* 0x00 */ u8 cmd;
    /* 0x02 */ u16 fovY; // @unverified: geo_layout_cmd: GeoNode_CreateCamera argument, stored in perspective.verticalFieldOfView
    /* 0x04 */ u16 viewportX; // @unverified: geo_layout_cmd: GeoNode_CreateCamera argument
    /* 0x06 */ u16 viewportY; // @unverified: geo_layout_cmd: GeoNode_CreateCamera argument
    /* 0x08 */ s16 viewportWidth; // @unverified: geo_layout_cmd: GeoNode_CreateCamera argument
    /* 0x0A */ s16 viewportHeight; // @unverified: geo_layout_cmd: GeoNode_CreateCamera argument
    /* 0x0C */ Vec3s target; // @unverified: geo_layout_cmd: GeoNode_CreateCamera argument
    /* 0x12 */ s16 pitchDegrees; // @unverified: geo_layout_cmd: GeoNode_CreateCamera argument, degrees, converted to a binary angle
    /* 0x14 */ s16 yawDegrees; // @unverified: geo_layout_cmd: GeoNode_CreateCamera argument, degrees, converted to a binary angle
    /* 0x16 */ s16 distance; // @unverified: geo_layout_cmd: GeoNode_CreateCamera argument, eye distance from target for Camera_ComputeEyeFromAngles
} GeoLayoutCmdCreateCamera; // size = 0x18

typedef struct GeoLayoutCmdCreateType3 {
    /* 0x00 */ u8 cmd;
    /* 0x02 */ s16 unk_02;
} GeoLayoutCmdCreateType3; // size = 0x4

typedef struct GeoLayoutCmdCreateType4 {
    /* 0x00 */ u8 cmd;
    /* 0x02 */ s16 rootId; // @unverified: geo_layout_cmd: GeoNode_CreateType4 argument
} GeoLayoutCmdCreateType4; // size = 0x4

typedef struct GeoLayoutCmdCreateOrtho {
    /* 0x00 */ u8 cmd;
    /* 0x02 */ s16 renderFlags; // @unverified: geo_layout_cmd: GeoNode_CreateOrtho argument
} GeoLayoutCmdCreateOrtho; // size = 0x4

typedef struct GeoLayoutCmdCreatePerspective {
    /* 0x00 */ u8 cmd;
    /* 0x02 */ s16 renderFlags; // @unverified: geo_layout_cmd: GeoNode_CreatePerspective argument
} GeoLayoutCmdCreatePerspective; // size = 0x4

typedef struct GeoLayoutCmdCreateBackground {
    /* 0x00 */ u8 cmd;
    /* 0x01 */ u8 r; // @unverified: geo_layout_cmd: GeoNode_CreateBackground argument
    /* 0x02 */ u8 g; // @unverified: geo_layout_cmd: GeoNode_CreateBackground argument
    /* 0x03 */ u8 b; // @unverified: geo_layout_cmd: GeoNode_CreateBackground argument
} GeoLayoutCmdCreateBackground; // size = 0x4

typedef struct GeoLayoutCmdCreateClearDepth {
    /* 0x00 */ u8 cmd;
    /* 0x01 */ char pad[3];
} GeoLayoutCmdCreateClearDepth; // size = 0x4

typedef struct GeoLayoutCmdNoop {
    /* 0x00 */ u8 cmd;
    /* 0x01 */ char pad[3];
} GeoLayoutCmdNoop; // size = 0x4

typedef struct GeoLayoutCmdCreateFog {
    /* 0x00 */ u8 cmd;
    /* 0x01 */ u8 r;
    /* 0x02 */ u8 g;
    /* 0x03 */ u8 b;
    /* 0x04 */ s16 near; // @unverified: geo_layout_cmd: GeoNode_CreateFog argument
    /* 0x06 */ s16 far; // @unverified: geo_layout_cmd: GeoNode_CreateFog argument
} GeoLayoutCmdCreateFog; // size = 0x8

typedef struct GeoLayoutCmdCreateLight {
    /* 0x00 */ u8 cmd;
    /* 0x01 */ char pad[0x3];
    /* 0x04 */ s16 pitchDegrees; // @unverified: geo_layout_cmd: GeoNode_CreateLight argument, degrees, converted to a binary angle
    /* 0x06 */ s16 yawDegrees; // @unverified: geo_layout_cmd: GeoNode_CreateLight argument, degrees, converted to a binary angle
    /* 0x08 */ u8 r;
    /* 0x09 */ u8 g;
    /* 0x0A */ u8 b;
    /* 0x0B */ u8 a;
} GeoLayoutCmdCreateLight; // size = 0xC

typedef struct GeoLayoutCmdSkip {
    /* 0x00 */ u8 cmd;
    /* 0x01 */ char pad[0xB];
} GeoLayoutCmdSkip; // size = 0xC

typedef struct GeoLayoutCmdCreateAmbientLight {
    /* 0x00 */ u8 cmd;
    /* 0x01 */ u8 r;
    /* 0x02 */ u8 g;
    /* 0x03 */ u8 b;
} GeoLayoutCmdCreateAmbientLight; // size = 0x4

typedef struct GeoLayoutCmdCreateTextureBank {
    /* 0x00 */ u8 cmd;
    /* 0x02 */ s16 textureCount; // @unverified: geo_layout_cmd: GeoNode_CreateTextureBank argument
    /* 0x04 */ s16 paletteCount; // @unverified: geo_layout_cmd: GeoNode_CreateTextureBank argument
    /* 0x06 */ s16 vertexCount; // @unverified: geo_layout_cmd: GeoNode_CreateTextureBank argument
    /* 0x08 */ GeoTexture* textures; // @unverified: geo_layout_cmd: GeoNode_CreateTextureBank argument
    /* 0x0C */ GeoPalette* palettes; // @unverified: geo_layout_cmd: GeoNode_CreateTextureBank argument
    /* 0x10 */ Vtx* vertices; // @unverified: geo_layout_cmd: GeoNode_CreateTextureBank argument
} GeoLayoutCmdCreateTextureBank; // size = 0x14

typedef struct GeoLayoutCmdCreateShadow {
    /* 0x00 */ u8 cmd;
    /* 0x01 */ u8 shape; // @unverified: geo_layout_cmd: GeoNode_CreateShadow argument
    /* 0x02 */ s16 heightOffset; // @unverified: geo_layout_cmd: GeoNode_CreateShadow argument
    /* 0x04 */ s16 scaleXPercent; // @unverified: geo_layout_cmd: GeoNode_CreateShadow argument, percent (divided by 100)
    /* 0x06 */ s16 scaleZPercent; // @unverified: geo_layout_cmd: GeoNode_CreateShadow argument, percent (divided by 100)
} GeoLayoutCmdCreateShadow; // size = 0x8

typedef struct GeoLayoutCmdCreateCullDistance {
    /* 0x00 */ u8 cmd;
    /* 0x01 */ char pad[0x3];
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
} GeoLayoutCmdCreateCullDistance; // size = 0x8

typedef struct GeoLayoutCmdCreateSwitchCase {
    /* 0x00 */ u8 cmd;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ s16 selectedChild; // @unverified: geo_layout_cmd: GeoNode_CreateSwitchCase argument
} GeoLayoutCmdCreateSwitchCase; // size = 0x4

typedef struct GeoLayoutCmdCreateTranslateRotate {
    /* 0x00 */ u8 cmd;
    /* 0x01 */ char pad[0x3];
    /* 0x04 */ Vec3s rotationDegrees; // @unverified: geo_layout_cmd: GeoNode_CreateTranslateRotate argument, degrees, converted to binary angles
    /* 0x0A */ Vec3s translation; // @unverified: geo_layout_cmd: GeoNode_CreateTranslateRotate argument
} GeoLayoutCmdCreateTranslateRotate; // size = 0x10

typedef struct GeoLayoutCmdCreateTranslate {
    /* 0x00 */ u8 cmd;
    /* 0x01 */ char pad[0x3];
    /* 0x04 */ u32 translationX; // @unverified: geo_layout_cmd: GeoNode_CreateTranslate argument, 16.16 fixed point
    /* 0x08 */ u32 translationY; // @unverified: geo_layout_cmd: GeoNode_CreateTranslate argument, 16.16 fixed point
    /* 0x0C */ u32 translationZ; // @unverified: geo_layout_cmd: GeoNode_CreateTranslate argument, 16.16 fixed point
} GeoLayoutCmdCreateTranslate; // size = 0x10

typedef struct GeoLayoutCmdCreateAnimatedPart {
    /* 0x00 */ u8 cmd;
    /* 0x01 */ u8 matrixSlot; // @unverified: geo_layout_cmd: GeoNode_CreateAnimatedPart argument
    /* 0x02 */ u8 flags; // @unverified: geo_layout_cmd: GeoNode_CreateAnimatedPart argument
    /* 0x03 */ u8 channelGroup; // @unverified: geo_layout_cmd: GeoNode_CreateAnimatedPart argument
    /* 0x04 */ Vec3s translation; // @unverified: geo_layout_cmd: GeoNode_CreateAnimatedPart argument
    /* 0x0A */ Vec3s rotation; // @unverified: geo_layout_cmd: GeoNode_CreateAnimatedPart argument
    /* 0x10 */ u32 scaleX; // @unverified: geo_layout_cmd: GeoNode_CreateAnimatedPart argument, 16.16 fixed point
    /* 0x14 */ u32 scaleY; // @unverified: geo_layout_cmd: GeoNode_CreateAnimatedPart argument, 16.16 fixed point
    /* 0x18 */ u32 scaleZ; // @unverified: geo_layout_cmd: GeoNode_CreateAnimatedPart argument, 16.16 fixed point
} GeoLayoutCmdCreateAnimatedPart; // size = 0x1C

typedef struct GeoLayoutCmdCreateDisplayListPart {
    /* 0x00 */ u8 cmd;
    /* 0x01 */ u8 renderLayer; // @unverified: geo_layout_cmd: GeoNode_CreateDisplayListPart argument
    /* 0x02 */ s16 matrixSlot; // @unverified: geo_layout_cmd: GeoNode_CreateDisplayListPart argument
    /* 0x04 */ Gfx* displayList; // @unverified: geo_layout_cmd: GeoNode_CreateDisplayListPart argument
} GeoLayoutCmdCreateDisplayListPart; // size = 0x8

typedef struct GeoLayoutCmdCreateModelPart {
    /* 0x00 */ u8 cmd;
    /* 0x02 */ s16 objectType; // @unverified: geo_layout_cmd: GeoNode_CreateModelPart argument
    /* 0x04 */ Vec3s rotationDegrees; // @unverified: geo_layout_cmd: GeoNode_CreateModelPart argument, degrees, converted to binary angles
    /* 0x0A */ Vec3s position; // @unverified: geo_layout_cmd: GeoNode_CreateModelPart argument
    /* 0x10 */ s16 scaleXPercent; // @unverified: geo_layout_cmd: GeoNode_CreateModelPart argument, percent (divided by 100)
    /* 0x12 */ s16 scaleYPercent; // @unverified: geo_layout_cmd: GeoNode_CreateModelPart argument, percent (divided by 100)
    /* 0x14 */ s16 scaleZPercent; // @unverified: geo_layout_cmd: GeoNode_CreateModelPart argument, percent (divided by 100)
    /* 0x16 */ char pad[0x2];
} GeoLayoutCmdCreateModelPart; // size = 0x18

typedef struct GeoLayoutCmdCreateDisplayListMatrix {
    /* 0x00 */ u8 cmd;
    /* 0x01 */ u8 renderLayer; // @unverified: geo_layout_cmd: GeoNode_CreateDisplayListMatrix argument
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ Vec3s rotationDegrees; // @unverified: geo_layout_cmd: GeoNode_CreateDisplayListMatrix argument, degrees, converted to binary angles
    /* 0x0A */ Vec3s translation; // @unverified: geo_layout_cmd: GeoNode_CreateDisplayListMatrix argument
    /* 0x10 */ Gfx* displayList; // @unverified: geo_layout_cmd: GeoNode_CreateDisplayListMatrix argument
} GeoLayoutCmdCreateDisplayListMatrix; // size = 0x14

typedef struct GeoLayoutCmdCreateBillboard {
    /* 0x00 */ u8 cmd;
    /* 0x01 */ u8 renderLayer; // @unverified: geo_layout_cmd: GeoNode_CreateBillboard argument
    /* 0x02 */ Vec3s position; // @unverified: geo_layout_cmd: GeoNode_CreateBillboard argument
    /* 0x08 */ u32 unk_08;
    /* 0x0C */ Gfx* displayList; // @unverified: geo_layout_cmd: GeoNode_CreateBillboard argument
} GeoLayoutCmdCreateBillboard; // size = 0x10

typedef struct GeoLayoutCmdCreateDisplayList {
    /* 0x00 */ u8 cmd;
    /* 0x01 */ u8 renderLayer; // @unverified: geo_layout_cmd: GeoNode_CreateDisplayList argument
    /* 0x04 */ Gfx* displayList; // @unverified: geo_layout_cmd: GeoNode_CreateDisplayList argument
} GeoLayoutCmdCreateDisplayList; // size = 0x8

typedef struct GeoLayoutCmdCreateMaterial {
    /* 0x00 */ u8 cmd;
    /* 0x01 */ u8 mode; // @unverified: geo_layout_cmd: GeoNode_CreateMaterial argument
    /* 0x02 */ s16 eventIndex; // @unverified: geo_layout_cmd: GeoNode_CreateMaterial argument
    /* 0x04 */ Gfx* displayList; // @unverified: geo_layout_cmd: GeoNode_CreateMaterial argument
    /* 0x08 */ s16 textureIndex; // @unverified: geo_layout_cmd: GeoNode_CreateMaterial argument
    /* 0x0A */ s16 paletteIndex; // @unverified: geo_layout_cmd: GeoNode_CreateMaterial argument
    /* 0x0C */ u8 r;
    /* 0x0D */ u8 g;
    /* 0x0E */ u8 b;
    /* 0x0F */ u8 a;
} GeoLayoutCmdCreateMaterial; // size = 0x10

typedef struct GeoLayoutCmdCreateAnchor {
    /* 0x00 */ u8 cmd;
    /* 0x02 */ s16 anchorId; // @unverified: geo_layout_cmd: GeoNode_CreateAnchor argument
} GeoLayoutCmdCreateAnchor; // size = 0x4

typedef struct GeoLayoutCmdSetNodeFlag4 {
    /* 0x00 */ u8 cmd;
    /* 0x01 */ char pad[3];
} GeoLayoutCmdSetNodeFlag4; // size = 0x4

typedef struct GeoLayoutCmdCreateGroup {
    /* 0x00 */ u8 cmd;
    /* 0x01 */ u8 renderLayer; // @unverified: geo_layout_cmd: GeoNode_CreateGroup argument
    /* 0x02 */ u8 unk_02;
    /* 0x03 */ s8 unk_03;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ u8 r;
    /* 0x11 */ u8 g;
    /* 0x12 */ u8 b;
    /* 0x13 */ u8 a;
} GeoLayoutCmdCreateGroup; // size = 0x14

#include "memory.h"

// geo_layout.c
void geo_layout_cmd_branch_and_link(void); // cmd  0
void geo_layout_cmd_end(void); // cmd  1
void geo_layout_cmd_jump(void); // cmd  2
void geo_layout_cmd_branch(void); // cmd  3
void geo_layout_cmd_return(void); // cmd  4
void geo_layout_cmd_open_node(void); // cmd  5
void geo_layout_cmd_close_node(void); // cmd  6
void geo_layout_cmd_attach_node(void); // cmd  7
void geo_layout_cmd_set_callback(void); // cmd  8
void geo_layout_cmd_create_container(void); // cmd  9
void geo_layout_cmd_create_reference(void); // cmd 10
void geo_layout_cmd_create_camera(void); // cmd 11
void geo_layout_cmd_create_type3(void); // cmd 12
void geo_layout_cmd_create_type4(void); // cmd 13
void geo_layout_cmd_create_ortho(void); // cmd 14
void geo_layout_cmd_create_perspective(void); // cmd 15
void geo_layout_cmd_create_background(void); // cmd 16
void geo_layout_cmd_create_clear_depth(void); // cmd 17
void geo_layout_cmd_noop(void); // cmd 18
void geo_layout_cmd_create_fog(void); // cmd 19
void geo_layout_cmd_create_light(void); // cmd 20
void geo_layout_cmd_skip(void); // cmd 21
void geo_layout_cmd_create_ambient_light(void); // cmd 22
void geo_layout_cmd_create_texture_bank(void); // cmd 23
void geo_layout_cmd_create_shadow(void); // cmd 24
void geo_layout_cmd_create_cull_distance(void); // cmd 25
void geo_layout_cmd_create_switch_case(void); // cmd 26
void geo_layout_cmd_create_translate_rotate(void); // cmd 27
void geo_layout_cmd_create_translate(void); // cmd 28
void geo_layout_cmd_create_animated_part(void); // cmd 29
void geo_layout_cmd_create_display_list_part(void); // cmd 30
void geo_layout_cmd_create_model_part(void); // cmd 31
void geo_layout_cmd_create_display_list_matrix(void); // cmd 32
void geo_layout_cmd_create_billboard(void); // cmd 33
void geo_layout_cmd_create_display_list(void); // cmd 34
void geo_layout_cmd_create_material(void); // cmd 35
void geo_layout_cmd_create_anchor(void); // cmd 36
void geo_layout_cmd_set_node_flag4(void); // cmd 37
void geo_layout_cmd_create_group(void); // cmd 38
GraphNode* process_geo_layout(MemoryBlock*, void*);

#endif // GEO_LAYOUT_H
