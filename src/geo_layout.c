/* Stadium Zero resident code. */
/* C ported from the Stadium 1 decomp: src/geo_layout.c. */

#include "geo_layout.h"
#include "matrix.h"
#include "util.h"
extern GeoLayoutCommandProc GeoLayoutJumpTable[];
extern MemoryBlock* gGraphNodePool;
extern GraphNode* gCurRootGraphNode;
extern u32 gGeoLayoutStack[16];
extern GraphNode* gCurGraphNodeList[32];
extern s16 gCurGraphNodeIndex;
extern s16 gGeoLayoutStackIndex;
extern s16 gGeoLayoutReturnIndex;
extern u8* gGeoLayoutCommand;

void geo_layout_cmd_branch_and_link(void);
void geo_layout_cmd_end(void);
void geo_layout_cmd_jump(void);
void geo_layout_cmd_branch(void);
void geo_layout_cmd_return(void);
void geo_layout_cmd_open_node(void);
void geo_layout_cmd_close_node(void);
void register_graph_node(GraphNode* arg0);
void geo_layout_cmd_attach_node(void);
void geo_layout_cmd_set_callback(void);
void geo_layout_cmd_create_container(void);
void geo_layout_cmd_create_reference(void);
void geo_layout_cmd_create_camera(void);
void geo_layout_cmd_create_type3(void);
void geo_layout_cmd_create_type4(void);
void geo_layout_cmd_create_ortho(void);
void geo_layout_cmd_create_perspective(void);
void geo_layout_cmd_create_background(void);
void geo_layout_cmd_create_clear_depth(void);
void geo_layout_cmd_noop(void);
void geo_layout_cmd_create_fog(void);
void geo_layout_cmd_create_light(void);
void geo_layout_cmd_skip(void);
void geo_layout_cmd_create_ambient_light(void);
void geo_layout_cmd_create_texture_bank(void);
void geo_layout_cmd_create_shadow(void);
void geo_layout_cmd_create_cull_distance(void);
void geo_layout_cmd_create_switch_case(void);
void geo_layout_cmd_create_translate_rotate(void);
void geo_layout_cmd_create_translate(void);
void geo_layout_cmd_create_animated_part(void);
void geo_layout_cmd_create_display_list_part(void);
void geo_layout_cmd_create_model_part(void);
void geo_layout_cmd_create_display_list_matrix(void);
void geo_layout_cmd_create_billboard(void);
void geo_layout_cmd_create_display_list(void);
void geo_layout_cmd_create_material(void);
void geo_layout_cmd_create_anchor(void);
void geo_layout_cmd_set_node_flag4(void);
void geo_layout_cmd_create_group(void);
GraphNode* process_geo_layout(MemoryBlock* pool, void* segptr);

/*
  0x00: Branch and store return address
   cmd+0x04: void *branchTarget
*/
void geo_layout_cmd_branch_and_link(void) {
    u8* cmd = (void*)gGeoLayoutCommand;

    cmd += 0;

    gGeoLayoutStack[gGeoLayoutStackIndex++] = (uintptr_t)(cmd + CMD_PROCESS_OFFSET(8));
    gGeoLayoutStack[gGeoLayoutStackIndex++] = (gCurGraphNodeIndex << 16) + gGeoLayoutReturnIndex;
    gGeoLayoutReturnIndex = gGeoLayoutStackIndex;
    gGeoLayoutCommand = Util_ConvertAddrToVirtAddr(cur_geo_cmd_ptr(0x04));
}

// 0x01: Terminate geo layout
/**
 * Geo layout command: ends the current layout and returns to the caller's
 * stack frame.
 */
void geo_layout_cmd_end(void) {
    gGeoLayoutStackIndex = gGeoLayoutReturnIndex;
    gGeoLayoutReturnIndex = gGeoLayoutStack[--gGeoLayoutStackIndex] & 0xFFFF;
    gCurGraphNodeIndex = gGeoLayoutStack[gGeoLayoutStackIndex] >> 16;
    gGeoLayoutCommand = (u8*)gGeoLayoutStack[--gGeoLayoutStackIndex];
}

/*
  0x02: Jump to address
    cmd+0x04: void *jumpTarget
*/
void geo_layout_cmd_jump(void) {
    u8* cmd = (void*)gGeoLayoutCommand;

    cmd += 0;

    gGeoLayoutCommand = Util_ConvertAddrToVirtAddr(cur_geo_cmd_ptr(0x04));
}

/*
  0x03: Branch
    cmd+0x04: void *branchTarget
*/
void geo_layout_cmd_branch(void) {
    u8* cmd = (void*)gGeoLayoutCommand;

    cmd += 0;

    // unlike in sm64, this argument doesnt seem to be optional.
    gGeoLayoutStack[gGeoLayoutStackIndex++] = (uintptr_t)(cmd + CMD_PROCESS_OFFSET(8));
    gGeoLayoutCommand = Util_ConvertAddrToVirtAddr(cur_geo_cmd_ptr(0x04));
}

// 0x04: Return from branch
/** Geo layout command: returns to the command address saved on the stack. */
void geo_layout_cmd_return(void) {
    gGeoLayoutCommand = (u8*)gGeoLayoutStack[--gGeoLayoutStackIndex];
}

// 0x05: Open node
/**
 * Geo layout command: makes the current node the parent of the nodes that
 * follow.
 */
void geo_layout_cmd_open_node(void) {
    gCurGraphNodeList[gCurGraphNodeIndex + 1] = gCurGraphNodeList[gCurGraphNodeIndex];
    gCurGraphNodeIndex++;
    gGeoLayoutCommand += 0x04 << CMD_SIZE_SHIFT;
}

// 0x06: Close node
/** Geo layout command: ends the current parent node. */
void geo_layout_cmd_close_node(void) {
    gCurGraphNodeIndex--;
    gGeoLayoutCommand += 0x04 << CMD_SIZE_SHIFT;
}

/**
 * Adds a node to the layout being built, as a child of the current parent or
 * as the root.
 */
void register_graph_node(GraphNode* arg0) {
    if (arg0 != NULL) {
        gCurGraphNodeList[gCurGraphNodeIndex] = arg0;
        if (gCurGraphNodeIndex == 0) {
            if (gCurRootGraphNode == NULL) {
                gCurRootGraphNode = arg0;
            }
        } else {
            GraphNode_AppendChild(gCurGraphNodeList[gCurGraphNodeIndex - 1], arg0);
        }
    }
}

/** Geo layout command: registers an existing node. */
void geo_layout_cmd_attach_node(void) {
    GeoLayoutCmdAttachNode* cmd = (GeoLayoutCmdAttachNode*)gGeoLayoutCommand;

    register_graph_node(&cmd->node->node);

    gGeoLayoutCommand += sizeof(GeoLayoutCmdAttachNode);
}

/** Geo layout command: sets a callback on the current node. */
void geo_layout_cmd_set_callback(void) {
    GeoLayoutCmdSetCallback* cmd = (GeoLayoutCmdSetCallback*)gGeoLayoutCommand;

    if (gCurGraphNodeList[gCurGraphNodeIndex] != NULL) {
        GeoNode_SetCallback(gCurGraphNodeList[gCurGraphNodeIndex], cmd->callback, cmd->callbackArg);
    }

    gGeoLayoutCommand += sizeof(GeoLayoutCmdSetCallback);
}

/** Geo layout command: creates a container node. */
void geo_layout_cmd_create_container(void) {
    register_graph_node(GeoNode_CreateContainer(gGraphNodePool, NULL));

    gGeoLayoutCommand += sizeof(GeoLayoutCmdCreateContainer);
}

/** Geo layout command: creates a reference node. */
void geo_layout_cmd_create_reference(void) {
    GeoLayoutCmdCreateReference* cmd = (GeoLayoutCmdCreateReference*)gGeoLayoutCommand;

    register_graph_node(GeoNode_CreateWithReference(gGraphNodePool, NULL, cmd->target));

    gGeoLayoutCommand += sizeof(GeoLayoutCmdCreateReference);
}

/** Geo layout command: creates a camera node. */
void geo_layout_cmd_create_camera(void) {
    GeoLayoutCmdCreateCamera* cmd = (GeoLayoutCmdCreateCamera*)gGeoLayoutCommand;
    CameraNode* temp_v0 =
        GeoNode_CreateCamera(gGraphNodePool, NULL, cmd->viewportX, cmd->viewportY, cmd->viewportWidth, cmd->viewportHeight);

    if (temp_v0 != NULL) {
        temp_v0->perspective.verticalFieldOfView = cmd->fovY;
        Vec3f_FromVec3s(&temp_v0->view.targetPosition, &cmd->target);
        Camera_ComputeEyeFromAngles(&temp_v0->view.targetPosition, &temp_v0->view.eyePosition, cmd->distance, (cmd->pitchDegrees << 0xF) / 180,
                      (cmd->yawDegrees << 0xF) / 180);
    }

    register_graph_node(&temp_v0->node);

    gGeoLayoutCommand += sizeof(GeoLayoutCmdCreateCamera);
}

/** Geo layout command: creates a type3 node. */
void geo_layout_cmd_create_type3(void) {
    GeoLayoutCmdCreateType3* cmd = (GeoLayoutCmdCreateType3*)gGeoLayoutCommand;

    register_graph_node(GeoNode_CreateType3(gGraphNodePool, NULL, cmd->unk_02));

    gGeoLayoutCommand += sizeof(GeoLayoutCmdCreateType3);
}

/** Geo layout command: creates a type4 node. */
void geo_layout_cmd_create_type4(void) {
    GeoLayoutCmdCreateType4* cmd = (GeoLayoutCmdCreateType4*)gGeoLayoutCommand;

    register_graph_node(GeoNode_CreateType4(gGraphNodePool, NULL, cmd->rootId));

    gGeoLayoutCommand += sizeof(GeoLayoutCmdCreateType4);
}

/** Geo layout command: creates a ortho node. */
void geo_layout_cmd_create_ortho(void) {
    GeoLayoutCmdCreateOrtho* cmd = (GeoLayoutCmdCreateOrtho*)gGeoLayoutCommand;

    register_graph_node(GeoNode_CreateOrtho(gGraphNodePool, NULL, cmd->renderFlags));

    gGeoLayoutCommand += sizeof(GeoLayoutCmdCreateOrtho);
}

/** Geo layout command: creates a perspective node. */
void geo_layout_cmd_create_perspective(void) {
    GeoLayoutCmdCreatePerspective* cmd = (GeoLayoutCmdCreatePerspective*)gGeoLayoutCommand;

    register_graph_node(GeoNode_CreatePerspective(gGraphNodePool, NULL, cmd->renderFlags));

    gGeoLayoutCommand += sizeof(GeoLayoutCmdCreatePerspective);
}

/** Geo layout command: creates a background node. */
void geo_layout_cmd_create_background(void) {
    GeoLayoutCmdCreateBackground* cmd = (GeoLayoutCmdCreateBackground*)gGeoLayoutCommand;

    register_graph_node(GeoNode_CreateBackground(gGraphNodePool, NULL, cmd->r, cmd->g, cmd->b));

    gGeoLayoutCommand += sizeof(GeoLayoutCmdCreateBackground);
}

/** Geo layout command: creates a clear depth node. */
void geo_layout_cmd_create_clear_depth(void) {
    register_graph_node(GeoNode_CreateClearDepth(gGraphNodePool, NULL));

    gGeoLayoutCommand += sizeof(GeoLayoutCmdCreateClearDepth);
}

/** Geo layout command: does nothing. */
void geo_layout_cmd_noop(void) {
}

/** Geo layout command: creates a fog node. */
void geo_layout_cmd_create_fog(void) {
    GeoLayoutCmdCreateFog* cmd = (GeoLayoutCmdCreateFog*)gGeoLayoutCommand;

    register_graph_node(GeoNode_CreateFog(gGraphNodePool, NULL, cmd->near, cmd->far, cmd->r, cmd->g, cmd->b, 0xFF));

    gGeoLayoutCommand += sizeof(GeoLayoutCmdCreateFog);
}

/** Geo layout command: creates a light node. */
void geo_layout_cmd_create_light(void) {
    GeoLayoutCmdCreateLight* cmd = (GeoLayoutCmdCreateLight*)gGeoLayoutCommand;

    register_graph_node(GeoNode_CreateLight(gGraphNodePool, NULL, (cmd->pitchDegrees << 0xF) / 180, (cmd->yawDegrees << 0xF) / 180, cmd->r,
                                cmd->g, cmd->b, cmd->a));

    gGeoLayoutCommand += sizeof(GeoLayoutCmdCreateLight);
}

/** Geo layout command: skips over an unused command. */
void geo_layout_cmd_skip(void) {
    gGeoLayoutCommand += sizeof(GeoLayoutCmdSkip);
}

/** Geo layout command: creates a ambient light node. */
void geo_layout_cmd_create_ambient_light(void) {
    GeoLayoutCmdCreateAmbientLight* cmd = (GeoLayoutCmdCreateAmbientLight*)gGeoLayoutCommand;

    register_graph_node(GeoNode_CreateAmbientLight(gGraphNodePool, NULL, cmd->r, cmd->g, cmd->b));

    gGeoLayoutCommand += sizeof(GeoLayoutCmdCreateAmbientLight);
}

/** Geo layout command: creates a texture bank node. */
void geo_layout_cmd_create_texture_bank(void) {
    GeoLayoutCmdCreateTextureBank* cmd = (GeoLayoutCmdCreateTextureBank*)gGeoLayoutCommand;

    register_graph_node(GeoNode_CreateTextureBank(gGraphNodePool, NULL, cmd->textureCount, cmd->textures, cmd->paletteCount, cmd->palettes, cmd->vertexCount,
                                cmd->vertices));

    gGeoLayoutCommand += sizeof(GeoLayoutCmdCreateTextureBank);
}

/** Geo layout command: creates a shadow node. */
void geo_layout_cmd_create_shadow(void) {
    GeoLayoutCmdCreateShadow* cmd = (GeoLayoutCmdCreateShadow*)gGeoLayoutCommand;

    register_graph_node(GeoNode_CreateShadow(gGraphNodePool, NULL, cmd->shape, cmd->scaleXPercent, cmd->scaleZPercent, cmd->heightOffset));

    gGeoLayoutCommand += sizeof(GeoLayoutCmdCreateShadow);
}

/** Geo layout command: creates a cull distance node. */
void geo_layout_cmd_create_cull_distance(void) {
    GeoLayoutCmdCreateCullDistance* cmd = (GeoLayoutCmdCreateCullDistance*)gGeoLayoutCommand;

    register_graph_node(GeoNode_CreateCullDistance(gGraphNodePool, NULL, cmd->unk_04, cmd->unk_06));

    gGeoLayoutCommand += sizeof(GeoLayoutCmdCreateCullDistance);
}

/** Geo layout command: creates a switch case node. */
void geo_layout_cmd_create_switch_case(void) {
    GeoLayoutCmdCreateSwitchCase* cmd = (GeoLayoutCmdCreateSwitchCase*)gGeoLayoutCommand;

    register_graph_node(GeoNode_CreateSwitchCase(gGraphNodePool, NULL, cmd->unk_01, cmd->selectedChild));

    gGeoLayoutCommand += sizeof(GeoLayoutCmdCreateSwitchCase);
}

/** Geo layout command: creates a translate rotate node. */
void geo_layout_cmd_create_translate_rotate(void) {
    Vec3s sp30;
    Vec3f sp24;
    UNUSED s32 pad; // FAKE: stack padding
    GeoLayoutCmdCreateTranslateRotate* cmd = (GeoLayoutCmdCreateTranslateRotate*)gGeoLayoutCommand;

    Vec3f_FromVec3s(&sp24, &cmd->translation);
    Vec3s_SetComponents(&sp30, (cmd->rotationDegrees.x << 0xF) / 180, (cmd->rotationDegrees.y << 0xF) / 180, (cmd->rotationDegrees.z << 0xF) / 180);
    register_graph_node(GeoNode_CreateTranslateRotate(gGraphNodePool, NULL, &sp24, &sp30));

    gGeoLayoutCommand += sizeof(GeoLayoutCmdCreateTranslateRotate);
}

/** Geo layout command: creates a translate node. */
void geo_layout_cmd_create_translate(void) {
    Vec3f sp24;
    GeoLayoutCmdCreateTranslate* cmd = (GeoLayoutCmdCreateTranslate*)gGeoLayoutCommand;

    sp24.x = cmd->translationX / 65536.0f;
    sp24.y = cmd->translationY / 65536.0f;
    sp24.z = cmd->translationZ / 65536.0f;
    register_graph_node(GeoNode_CreateTranslate(gGraphNodePool, NULL, &sp24));

    gGeoLayoutCommand += sizeof(GeoLayoutCmdCreateTranslate);
}

/** Geo layout command: creates a animated part node. */
void geo_layout_cmd_create_animated_part(void) {
    Vec3f sp3C;
    s16 var_a3 = 1;
    GeoLayoutCmdCreateAnimatedPart* cmd = (GeoLayoutCmdCreateAnimatedPart*)gGeoLayoutCommand;

    sp3C.x = cmd->scaleX / 65536.0f;
    sp3C.y = cmd->scaleY / 65536.0f;
    sp3C.z = cmd->scaleZ / 65536.0f;

    if (cmd->flags & 1) {
        var_a3 = 0;
    }

    if (cmd->flags & 2) {
        var_a3 |= 2;
    }

    register_graph_node(
        GeoNode_CreateAnimatedPart(gGraphNodePool, NULL, cmd->matrixSlot, var_a3, cmd->channelGroup, &cmd->translation, &cmd->rotation, &sp3C));

    gGeoLayoutCommand += sizeof(GeoLayoutCmdCreateAnimatedPart);
}

/** Geo layout command: creates a display list part node. */
void geo_layout_cmd_create_display_list_part(void) {
    GeoLayoutCmdCreateDisplayListPart* cmd = (GeoLayoutCmdCreateDisplayListPart*)gGeoLayoutCommand;

    register_graph_node(GeoNode_CreateDisplayListPart(gGraphNodePool, NULL, cmd->renderLayer, cmd->displayList, cmd->matrixSlot));

    gGeoLayoutCommand += sizeof(GeoLayoutCmdCreateDisplayListPart);
}

/** Geo layout command: creates a model part node. */
void geo_layout_cmd_create_model_part(void) {
    Vec3s sp40;
    Vec3f sp34;
    Vec3f sp28;
    DisplayObject* tmp;
    GeoLayoutCmdCreateModelPart* cmd = (GeoLayoutCmdCreateModelPart*)gGeoLayoutCommand;

    Vec3f_FromVec3s(&sp34, &cmd->position);

    sp28.x = cmd->scaleXPercent / 100.0f;
    sp28.y = cmd->scaleYPercent / 100.0f;
    sp28.z = cmd->scaleZPercent / 100.0f;

    Vec3s_SetComponents(&sp40, (cmd->rotationDegrees.x << 0xF) / 180, (cmd->rotationDegrees.y << 0xF) / 180, (cmd->rotationDegrees.z << 0xF) / 180);
    tmp = GeoNode_CreateModelPart(gGraphNodePool, NULL, cmd->objectType, &sp34, &sp40, &sp28);
    register_graph_node(tmp);

    gGeoLayoutCommand += sizeof(GeoLayoutCmdCreateModelPart);
}

/** Geo layout command: creates a display list matrix node. */
void geo_layout_cmd_create_display_list_matrix(void) {
    Vec3f sp34;
    Vec3s sp2C;
    GeoDisplayListMatrixNode* tmp;
    GeoLayoutCmdCreateDisplayListMatrix* cmd = (GeoLayoutCmdCreateDisplayListMatrix*)gGeoLayoutCommand;

    Vec3f_FromVec3s(&sp34, &cmd->translation);
    Vec3s_SetComponents(&sp2C, (cmd->rotationDegrees.x << 0xF) / 180, (cmd->rotationDegrees.y << 0xF) / 180, (cmd->rotationDegrees.z << 0xF) / 180);
    tmp = GeoNode_CreateDisplayListMatrixFromTransform(gGraphNodePool, NULL, cmd->renderLayer, cmd->displayList, &sp34, &sp2C);
    register_graph_node(tmp);

    gGeoLayoutCommand += sizeof(GeoLayoutCmdCreateDisplayListMatrix);
}

/** Geo layout command: creates a scale node. */
void geo_layout_cmd_create_billboard(void) {
    Vec3f sp2C;
    GeoBillboardNode* tmp;
    GeoLayoutCmdCreateBillboard* cmd = (GeoLayoutCmdCreateBillboard*)gGeoLayoutCommand;

    Vec3f_FromVec3s(&sp2C, &cmd->position);
    tmp = GeoNode_CreateBillboard(gGraphNodePool, NULL, cmd->renderLayer, cmd->displayList, &sp2C, cmd->unk_08 / 65536.0f);
    register_graph_node(tmp);

    gGeoLayoutCommand += sizeof(GeoLayoutCmdCreateBillboard);
}

/** Geo layout command: creates a display list node. */
void geo_layout_cmd_create_display_list(void) {
    GeoLayoutCmdCreateDisplayList* cmd = (GeoLayoutCmdCreateDisplayList*)gGeoLayoutCommand;

    register_graph_node(GeoNode_CreateDisplayList(gGraphNodePool, NULL, cmd->renderLayer, cmd->displayList));

    gGeoLayoutCommand += sizeof(GeoLayoutCmdCreateDisplayList);
}

/** Geo layout command: creates a material node. */
void geo_layout_cmd_create_material(void) {
    GeoLayoutCmdCreateMaterial* cmd = (GeoLayoutCmdCreateMaterial*)gGeoLayoutCommand;

    register_graph_node(GeoNode_CreateMaterial(gGraphNodePool, NULL, cmd->mode, cmd->eventIndex, cmd->displayList, cmd->textureIndex, cmd->paletteIndex,
                                cmd->r, cmd->g, cmd->b, cmd->a));

    gGeoLayoutCommand += sizeof(GeoLayoutCmdCreateMaterial);
}

/** Geo layout command: creates a anchor node. */
void geo_layout_cmd_create_anchor(void) {
    GeoLayoutCmdCreateAnchor* cmd = (GeoLayoutCmdCreateAnchor*)gGeoLayoutCommand;

    register_graph_node(GeoNode_CreateAnchor(gGraphNodePool, NULL, cmd->anchorId));

    gGeoLayoutCommand += sizeof(GeoLayoutCmdCreateAnchor);
}

/** Geo layout command: sets flag 4 on the current node. */
void geo_layout_cmd_set_node_flag4(void) {
    GeoLayoutCmdSetNodeFlag4* cmd = (GeoLayoutCmdSetNodeFlag4*)gGeoLayoutCommand;

    if (gCurGraphNodeList[gCurGraphNodeIndex] != NULL) {
        gCurGraphNodeList[gCurGraphNodeIndex]->renderFlags |= 4;
    }

    gGeoLayoutCommand += sizeof(GeoLayoutCmdSetNodeFlag4);
}

/** Geo layout command: creates a group node. */
void geo_layout_cmd_create_group(void) {
    GeoLayoutCmdCreateGroup* cmd = (GeoLayoutCmdCreateGroup*)gGeoLayoutCommand;

    register_graph_node(GeoNode_CreateGroup(gGraphNodePool, NULL, cmd->renderLayer, cmd->unk_04, cmd->unk_06, cmd->unk_08, cmd->unk_0A,
                                cmd->unk_02, cmd->unk_03, cmd->unk_0C, cmd->r, cmd->g, cmd->b, cmd->a));

    gGeoLayoutCommand += sizeof(GeoLayoutCmdCreateGroup);
}

/**
 * Builds a graph node tree from a geo layout command stream and returns its
 * root.
 */
GraphNode* process_geo_layout(MemoryBlock* pool, void* segptr) {
    // set by register_scene_graph_node when gCurGraphNodeIndex is 0
    // and gCurRootGraphNode is NULL
    gCurRootGraphNode = NULL;

    // gGeoNumViews seems to have been removed in this version of geo_script.c
    gCurGraphNodeIndex = 0;

    gGeoLayoutStackIndex = 2;
    gGeoLayoutReturnIndex = 2; // stack index is often copied here?

    gGeoLayoutCommand = Util_ConvertAddrToVirtAddr(segptr);

    gGraphNodePool = pool;

    gCurGraphNodeList[0] = 0;

    gGeoLayoutStack[0] = 0;
    gGeoLayoutStack[1] = 0;

    while (gGeoLayoutCommand != NULL) {
        GeoLayoutJumpTable[gGeoLayoutCommand[0x00]]();
    }

    return gCurRootGraphNode;
}
