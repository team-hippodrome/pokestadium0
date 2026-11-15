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

void GeoLayout_CmdBranchAndLink(void);
void GeoLayout_CmdEnd(void);
void GeoLayout_CmdJump(void);
void GeoLayout_CmdBranch(void);
void GeoLayout_CmdReturn(void);
void GeoLayout_CmdOpenNode(void);
void GeoLayout_CmdCloseNode(void);
void GeoLayout_RegisterGraphNode(GraphNode* arg0);
void GeoLayout_CmdAttachNode(void);
void GeoLayout_CmdSetCallback(void);
void GeoLayout_CmdCreateContainer(void);
void GeoLayout_CmdCreateReference(void);
void GeoLayout_CmdCreateCamera(void);
void GeoLayout_CmdCreateType3(void);
void GeoLayout_CmdCreateType4(void);
void GeoLayout_CmdCreateOrtho(void);
void GeoLayout_CmdCreatePerspective(void);
void GeoLayout_CmdCreateBackground(void);
void GeoLayout_CmdCreateClearDepth(void);
void GeoLayout_CmdNoop(void);
void GeoLayout_CmdCreateFog(void);
void GeoLayout_CmdCreateLight(void);
void GeoLayout_CmdSkip(void);
void GeoLayout_CmdCreateAmbientLight(void);
void GeoLayout_CmdCreateTextureBank(void);
void GeoLayout_CmdCreateShadow(void);
void GeoLayout_CmdCreateCullDistance(void);
void GeoLayout_CmdCreateSwitchCase(void);
void GeoLayout_CmdCreateTranslateRotate(void);
void GeoLayout_CmdCreateTranslate(void);
void GeoLayout_CmdCreateAnimatedPart(void);
void GeoLayout_CmdCreateDisplayListPart(void);
void GeoLayout_CmdCreateModelPart(void);
void GeoLayout_CmdCreateDisplayListMatrix(void);
void GeoLayout_CmdCreateBillboard(void);
void GeoLayout_CmdCreateDisplayList(void);
void GeoLayout_CmdCreateMaterial(void);
void GeoLayout_CmdCreateAnchor(void);
void GeoLayout_CmdSetNodeFlag4(void);
void GeoLayout_CmdCreateGroup(void);
GraphNode* GeoLayout_Process(MemoryBlock* pool, void* segptr);

/*
  0x00: Branch and store return address
   cmd+0x04: void *branchTarget
*/
void GeoLayout_CmdBranchAndLink(void) {
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
void GeoLayout_CmdEnd(void) {
    gGeoLayoutStackIndex = gGeoLayoutReturnIndex;
    gGeoLayoutReturnIndex = gGeoLayoutStack[--gGeoLayoutStackIndex] & 0xFFFF;
    gCurGraphNodeIndex = gGeoLayoutStack[gGeoLayoutStackIndex] >> 16;
    gGeoLayoutCommand = (u8*)gGeoLayoutStack[--gGeoLayoutStackIndex];
}

/*
  0x02: Jump to address
    cmd+0x04: void *jumpTarget
*/
void GeoLayout_CmdJump(void) {
    u8* cmd = (void*)gGeoLayoutCommand;

    cmd += 0;

    gGeoLayoutCommand = Util_ConvertAddrToVirtAddr(cur_geo_cmd_ptr(0x04));
}

/*
  0x03: Branch
    cmd+0x04: void *branchTarget
*/
void GeoLayout_CmdBranch(void) {
    u8* cmd = (void*)gGeoLayoutCommand;

    cmd += 0;

    // unlike in sm64, this argument doesnt seem to be optional.
    gGeoLayoutStack[gGeoLayoutStackIndex++] = (uintptr_t)(cmd + CMD_PROCESS_OFFSET(8));
    gGeoLayoutCommand = Util_ConvertAddrToVirtAddr(cur_geo_cmd_ptr(0x04));
}

// 0x04: Return from branch
/** Geo layout command: returns to the command address saved on the stack. */
void GeoLayout_CmdReturn(void) {
    gGeoLayoutCommand = (u8*)gGeoLayoutStack[--gGeoLayoutStackIndex];
}

// 0x05: Open node
/**
 * Geo layout command: makes the current node the parent of the nodes that
 * follow.
 */
void GeoLayout_CmdOpenNode(void) {
    gCurGraphNodeList[gCurGraphNodeIndex + 1] = gCurGraphNodeList[gCurGraphNodeIndex];
    gCurGraphNodeIndex++;
    gGeoLayoutCommand += 0x04 << CMD_SIZE_SHIFT;
}

// 0x06: Close node
/** Geo layout command: ends the current parent node. */
void GeoLayout_CmdCloseNode(void) {
    gCurGraphNodeIndex--;
    gGeoLayoutCommand += 0x04 << CMD_SIZE_SHIFT;
}

/**
 * Adds a node to the layout being built, as a child of the current parent or
 * as the root.
 */
void GeoLayout_RegisterGraphNode(GraphNode* arg0) {
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
void GeoLayout_CmdAttachNode(void) {
    GeoLayoutCmdAttachNode* cmd = (GeoLayoutCmdAttachNode*)gGeoLayoutCommand;

    GeoLayout_RegisterGraphNode(&cmd->node->node);

    gGeoLayoutCommand += sizeof(GeoLayoutCmdAttachNode);
}

/** Geo layout command: sets a callback on the current node. */
void GeoLayout_CmdSetCallback(void) {
    GeoLayoutCmdSetCallback* cmd = (GeoLayoutCmdSetCallback*)gGeoLayoutCommand;

    if (gCurGraphNodeList[gCurGraphNodeIndex] != NULL) {
        GeoNode_SetCallback(gCurGraphNodeList[gCurGraphNodeIndex], cmd->callback, cmd->callbackArg);
    }

    gGeoLayoutCommand += sizeof(GeoLayoutCmdSetCallback);
}

/** Geo layout command: creates a container node. */
void GeoLayout_CmdCreateContainer(void) {
    GeoLayout_RegisterGraphNode(GeoNode_CreateContainer(gGraphNodePool, NULL));

    gGeoLayoutCommand += sizeof(GeoLayoutCmdCreateContainer);
}

/** Geo layout command: creates a reference node. */
void GeoLayout_CmdCreateReference(void) {
    GeoLayoutCmdCreateReference* cmd = (GeoLayoutCmdCreateReference*)gGeoLayoutCommand;

    GeoLayout_RegisterGraphNode(GeoNode_CreateWithReference(gGraphNodePool, NULL, cmd->target));

    gGeoLayoutCommand += sizeof(GeoLayoutCmdCreateReference);
}

/** Geo layout command: creates a camera node. */
void GeoLayout_CmdCreateCamera(void) {
    GeoLayoutCmdCreateCamera* cmd = (GeoLayoutCmdCreateCamera*)gGeoLayoutCommand;
    CameraNode* temp_v0 =
        GeoNode_CreateCamera(gGraphNodePool, NULL, cmd->viewportX, cmd->viewportY, cmd->viewportWidth, cmd->viewportHeight);

    if (temp_v0 != NULL) {
        temp_v0->perspective.verticalFieldOfView = cmd->fovY;
        Vec3f_FromVec3s(&temp_v0->view.targetPosition, &cmd->target);
        Camera_ComputeEyeFromAngles(&temp_v0->view.targetPosition, &temp_v0->view.eyePosition, cmd->distance, (cmd->pitchDegrees << 0xF) / 180,
                      (cmd->yawDegrees << 0xF) / 180);
    }

    GeoLayout_RegisterGraphNode(&temp_v0->node);

    gGeoLayoutCommand += sizeof(GeoLayoutCmdCreateCamera);
}

/** Geo layout command: creates a type3 node. */
void GeoLayout_CmdCreateType3(void) {
    GeoLayoutCmdCreateType3* cmd = (GeoLayoutCmdCreateType3*)gGeoLayoutCommand;

    GeoLayout_RegisterGraphNode(GeoNode_CreateType3(gGraphNodePool, NULL, cmd->unk_02));

    gGeoLayoutCommand += sizeof(GeoLayoutCmdCreateType3);
}

/** Geo layout command: creates a type4 node. */
void GeoLayout_CmdCreateType4(void) {
    GeoLayoutCmdCreateType4* cmd = (GeoLayoutCmdCreateType4*)gGeoLayoutCommand;

    GeoLayout_RegisterGraphNode(GeoNode_CreateType4(gGraphNodePool, NULL, cmd->rootId));

    gGeoLayoutCommand += sizeof(GeoLayoutCmdCreateType4);
}

/** Geo layout command: creates a ortho node. */
void GeoLayout_CmdCreateOrtho(void) {
    GeoLayoutCmdCreateOrtho* cmd = (GeoLayoutCmdCreateOrtho*)gGeoLayoutCommand;

    GeoLayout_RegisterGraphNode(GeoNode_CreateOrtho(gGraphNodePool, NULL, cmd->renderFlags));

    gGeoLayoutCommand += sizeof(GeoLayoutCmdCreateOrtho);
}

/** Geo layout command: creates a perspective node. */
void GeoLayout_CmdCreatePerspective(void) {
    GeoLayoutCmdCreatePerspective* cmd = (GeoLayoutCmdCreatePerspective*)gGeoLayoutCommand;

    GeoLayout_RegisterGraphNode(GeoNode_CreatePerspective(gGraphNodePool, NULL, cmd->renderFlags));

    gGeoLayoutCommand += sizeof(GeoLayoutCmdCreatePerspective);
}

/** Geo layout command: creates a background node. */
void GeoLayout_CmdCreateBackground(void) {
    GeoLayoutCmdCreateBackground* cmd = (GeoLayoutCmdCreateBackground*)gGeoLayoutCommand;

    GeoLayout_RegisterGraphNode(GeoNode_CreateBackground(gGraphNodePool, NULL, cmd->r, cmd->g, cmd->b));

    gGeoLayoutCommand += sizeof(GeoLayoutCmdCreateBackground);
}

/** Geo layout command: creates a clear depth node. */
void GeoLayout_CmdCreateClearDepth(void) {
    GeoLayout_RegisterGraphNode(GeoNode_CreateClearDepth(gGraphNodePool, NULL));

    gGeoLayoutCommand += sizeof(GeoLayoutCmdCreateClearDepth);
}

/** Geo layout command: does nothing. */
void GeoLayout_CmdNoop(void) {
}

/** Geo layout command: creates a fog node. */
void GeoLayout_CmdCreateFog(void) {
    GeoLayoutCmdCreateFog* cmd = (GeoLayoutCmdCreateFog*)gGeoLayoutCommand;

    GeoLayout_RegisterGraphNode(GeoNode_CreateFog(gGraphNodePool, NULL, cmd->near, cmd->far, cmd->r, cmd->g, cmd->b, 0xFF));

    gGeoLayoutCommand += sizeof(GeoLayoutCmdCreateFog);
}

/** Geo layout command: creates a light node. */
void GeoLayout_CmdCreateLight(void) {
    GeoLayoutCmdCreateLight* cmd = (GeoLayoutCmdCreateLight*)gGeoLayoutCommand;

    GeoLayout_RegisterGraphNode(GeoNode_CreateLight(gGraphNodePool, NULL, (cmd->pitchDegrees << 0xF) / 180, (cmd->yawDegrees << 0xF) / 180, cmd->r,
                                cmd->g, cmd->b, cmd->a));

    gGeoLayoutCommand += sizeof(GeoLayoutCmdCreateLight);
}

/** Geo layout command: skips over an unused command. */
void GeoLayout_CmdSkip(void) {
    gGeoLayoutCommand += sizeof(GeoLayoutCmdSkip);
}

/** Geo layout command: creates a ambient light node. */
void GeoLayout_CmdCreateAmbientLight(void) {
    GeoLayoutCmdCreateAmbientLight* cmd = (GeoLayoutCmdCreateAmbientLight*)gGeoLayoutCommand;

    GeoLayout_RegisterGraphNode(GeoNode_CreateAmbientLight(gGraphNodePool, NULL, cmd->r, cmd->g, cmd->b));

    gGeoLayoutCommand += sizeof(GeoLayoutCmdCreateAmbientLight);
}

/** Geo layout command: creates a texture bank node. */
void GeoLayout_CmdCreateTextureBank(void) {
    GeoLayoutCmdCreateTextureBank* cmd = (GeoLayoutCmdCreateTextureBank*)gGeoLayoutCommand;

    GeoLayout_RegisterGraphNode(GeoNode_CreateTextureBank(gGraphNodePool, NULL, cmd->textureCount, cmd->textures, cmd->paletteCount, cmd->palettes, cmd->vertexCount,
                                cmd->vertices));

    gGeoLayoutCommand += sizeof(GeoLayoutCmdCreateTextureBank);
}

/** Geo layout command: creates a shadow node. */
void GeoLayout_CmdCreateShadow(void) {
    GeoLayoutCmdCreateShadow* cmd = (GeoLayoutCmdCreateShadow*)gGeoLayoutCommand;

    GeoLayout_RegisterGraphNode(GeoNode_CreateShadow(gGraphNodePool, NULL, cmd->shape, cmd->scaleXPercent, cmd->scaleZPercent, cmd->heightOffset));

    gGeoLayoutCommand += sizeof(GeoLayoutCmdCreateShadow);
}

/** Geo layout command: creates a cull distance node. */
void GeoLayout_CmdCreateCullDistance(void) {
    GeoLayoutCmdCreateCullDistance* cmd = (GeoLayoutCmdCreateCullDistance*)gGeoLayoutCommand;

    GeoLayout_RegisterGraphNode(GeoNode_CreateCullDistance(gGraphNodePool, NULL, cmd->unk_04, cmd->unk_06));

    gGeoLayoutCommand += sizeof(GeoLayoutCmdCreateCullDistance);
}

/** Geo layout command: creates a switch case node. */
void GeoLayout_CmdCreateSwitchCase(void) {
    GeoLayoutCmdCreateSwitchCase* cmd = (GeoLayoutCmdCreateSwitchCase*)gGeoLayoutCommand;

    GeoLayout_RegisterGraphNode(GeoNode_CreateSwitchCase(gGraphNodePool, NULL, cmd->unk_01, cmd->selectedChild));

    gGeoLayoutCommand += sizeof(GeoLayoutCmdCreateSwitchCase);
}

/** Geo layout command: creates a translate rotate node. */
void GeoLayout_CmdCreateTranslateRotate(void) {
    Vec3s sp30;
    Vec3f sp24;
    UNUSED s32 pad; // FAKE: stack padding
    GeoLayoutCmdCreateTranslateRotate* cmd = (GeoLayoutCmdCreateTranslateRotate*)gGeoLayoutCommand;

    Vec3f_FromVec3s(&sp24, &cmd->translation);
    Vec3s_SetComponents(&sp30, (cmd->rotationDegrees.x << 0xF) / 180, (cmd->rotationDegrees.y << 0xF) / 180, (cmd->rotationDegrees.z << 0xF) / 180);
    GeoLayout_RegisterGraphNode(GeoNode_CreateTranslateRotate(gGraphNodePool, NULL, &sp24, &sp30));

    gGeoLayoutCommand += sizeof(GeoLayoutCmdCreateTranslateRotate);
}

/** Geo layout command: creates a translate node. */
void GeoLayout_CmdCreateTranslate(void) {
    Vec3f sp24;
    GeoLayoutCmdCreateTranslate* cmd = (GeoLayoutCmdCreateTranslate*)gGeoLayoutCommand;

    sp24.x = cmd->translationX / 65536.0f;
    sp24.y = cmd->translationY / 65536.0f;
    sp24.z = cmd->translationZ / 65536.0f;
    GeoLayout_RegisterGraphNode(GeoNode_CreateTranslate(gGraphNodePool, NULL, &sp24));

    gGeoLayoutCommand += sizeof(GeoLayoutCmdCreateTranslate);
}

/** Geo layout command: creates a animated part node. */
void GeoLayout_CmdCreateAnimatedPart(void) {
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

    GeoLayout_RegisterGraphNode(
        GeoNode_CreateAnimatedPart(gGraphNodePool, NULL, cmd->matrixSlot, var_a3, cmd->channelGroup, &cmd->translation, &cmd->rotation, &sp3C));

    gGeoLayoutCommand += sizeof(GeoLayoutCmdCreateAnimatedPart);
}

/** Geo layout command: creates a display list part node. */
void GeoLayout_CmdCreateDisplayListPart(void) {
    GeoLayoutCmdCreateDisplayListPart* cmd = (GeoLayoutCmdCreateDisplayListPart*)gGeoLayoutCommand;

    GeoLayout_RegisterGraphNode(GeoNode_CreateDisplayListPart(gGraphNodePool, NULL, cmd->renderLayer, cmd->displayList, cmd->matrixSlot));

    gGeoLayoutCommand += sizeof(GeoLayoutCmdCreateDisplayListPart);
}

/** Geo layout command: creates a model part node. */
void GeoLayout_CmdCreateModelPart(void) {
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
    GeoLayout_RegisterGraphNode(tmp);

    gGeoLayoutCommand += sizeof(GeoLayoutCmdCreateModelPart);
}

/** Geo layout command: creates a display list matrix node. */
void GeoLayout_CmdCreateDisplayListMatrix(void) {
    Vec3f sp34;
    Vec3s sp2C;
    GeoDisplayListMatrixNode* tmp;
    GeoLayoutCmdCreateDisplayListMatrix* cmd = (GeoLayoutCmdCreateDisplayListMatrix*)gGeoLayoutCommand;

    Vec3f_FromVec3s(&sp34, &cmd->translation);
    Vec3s_SetComponents(&sp2C, (cmd->rotationDegrees.x << 0xF) / 180, (cmd->rotationDegrees.y << 0xF) / 180, (cmd->rotationDegrees.z << 0xF) / 180);
    tmp = GeoNode_CreateDisplayListMatrixFromTransform(gGraphNodePool, NULL, cmd->renderLayer, cmd->displayList, &sp34, &sp2C);
    GeoLayout_RegisterGraphNode(tmp);

    gGeoLayoutCommand += sizeof(GeoLayoutCmdCreateDisplayListMatrix);
}

/** Geo layout command: creates a scale node. */
void GeoLayout_CmdCreateBillboard(void) {
    Vec3f sp2C;
    GeoBillboardNode* tmp;
    GeoLayoutCmdCreateBillboard* cmd = (GeoLayoutCmdCreateBillboard*)gGeoLayoutCommand;

    Vec3f_FromVec3s(&sp2C, &cmd->position);
    tmp = GeoNode_CreateBillboard(gGraphNodePool, NULL, cmd->renderLayer, cmd->displayList, &sp2C, cmd->unk_08 / 65536.0f);
    GeoLayout_RegisterGraphNode(tmp);

    gGeoLayoutCommand += sizeof(GeoLayoutCmdCreateBillboard);
}

/** Geo layout command: creates a display list node. */
void GeoLayout_CmdCreateDisplayList(void) {
    GeoLayoutCmdCreateDisplayList* cmd = (GeoLayoutCmdCreateDisplayList*)gGeoLayoutCommand;

    GeoLayout_RegisterGraphNode(GeoNode_CreateDisplayList(gGraphNodePool, NULL, cmd->renderLayer, cmd->displayList));

    gGeoLayoutCommand += sizeof(GeoLayoutCmdCreateDisplayList);
}

/** Geo layout command: creates a material node. */
void GeoLayout_CmdCreateMaterial(void) {
    GeoLayoutCmdCreateMaterial* cmd = (GeoLayoutCmdCreateMaterial*)gGeoLayoutCommand;

    GeoLayout_RegisterGraphNode(GeoNode_CreateMaterial(gGraphNodePool, NULL, cmd->mode, cmd->eventIndex, cmd->displayList, cmd->textureIndex, cmd->paletteIndex,
                                cmd->r, cmd->g, cmd->b, cmd->a));

    gGeoLayoutCommand += sizeof(GeoLayoutCmdCreateMaterial);
}

/** Geo layout command: creates a anchor node. */
void GeoLayout_CmdCreateAnchor(void) {
    GeoLayoutCmdCreateAnchor* cmd = (GeoLayoutCmdCreateAnchor*)gGeoLayoutCommand;

    GeoLayout_RegisterGraphNode(GeoNode_CreateAnchor(gGraphNodePool, NULL, cmd->anchorId));

    gGeoLayoutCommand += sizeof(GeoLayoutCmdCreateAnchor);
}

/** Geo layout command: sets flag 4 on the current node. */
void GeoLayout_CmdSetNodeFlag4(void) {
    GeoLayoutCmdSetNodeFlag4* cmd = (GeoLayoutCmdSetNodeFlag4*)gGeoLayoutCommand;

    if (gCurGraphNodeList[gCurGraphNodeIndex] != NULL) {
        gCurGraphNodeList[gCurGraphNodeIndex]->renderFlags |= 4;
    }

    gGeoLayoutCommand += sizeof(GeoLayoutCmdSetNodeFlag4);
}

/** Geo layout command: creates a group node. */
void GeoLayout_CmdCreateGroup(void) {
    GeoLayoutCmdCreateGroup* cmd = (GeoLayoutCmdCreateGroup*)gGeoLayoutCommand;

    GeoLayout_RegisterGraphNode(GeoNode_CreateGroup(gGraphNodePool, NULL, cmd->renderLayer, cmd->unk_04, cmd->unk_06, cmd->unk_08, cmd->unk_0A,
                                cmd->unk_02, cmd->unk_03, cmd->unk_0C, cmd->r, cmd->g, cmd->b, cmd->a));

    gGeoLayoutCommand += sizeof(GeoLayoutCmdCreateGroup);
}

/**
 * Builds a graph node tree from a geo layout command stream and returns its
 * root.
 */
GraphNode* GeoLayout_Process(MemoryBlock* pool, void* segptr) {
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
