/* Stadium Zero resident code. */
/* C ported from the Stadium 1 decomp: src/model_renderer.c. */

#include "global.h"
#include "model_renderer.h"
#include "display_object_textures.h"
#include "gb_data.h"
#include "geo_node.h"
#include "geo_render.h"
#include "hal_libc.h"
#include "matrix.h"
extern struct DisplayNodeHeader D_800AD1D0;
extern struct DisplayNodeHeader D_800AD1E8;

void ModelRenderer_InitDisplayRoots(void);
void ModelRenderer_AttachDisplayObject(DisplayObject* display_object);
void ModelRenderer_AttachSecondaryDisplayObject(DisplayObject* arg0);
void ModelRenderer_ClearDisplayObject(DisplayObject* arg0);
s32 ModelAnim_SetAnimation(DisplayObject* display_object, s32 id);
s32 ModelAnim_SetEventTrack(DisplayObject* display_object, s32 track_id);
void Model_SetMaterialColor(DisplayObject* display_object, u8 r, u8 g, u8 b, u8 alpha);
void Model_SetMaterialAlpha(DisplayObject* arg0, u8 arg1);
void Model_SetMaterialTextureMode(DisplayObject* display_object, u8 texture_mode);
ModelAnimationBank* ModelAnim_GetAnimationRecord(DisplayObject* arg0, s32 arg1);

/** Creates the root graph nodes that display objects attach to. */
void ModelRenderer_InitDisplayRoots(void) {
    GeoNode_CreateContainer(0, &D_800AD1D0);
    GeoNode_CreateContainer(0, &D_800AD1E8);
}

/** Attaches a display object to the primary display root. */
void ModelRenderer_AttachDisplayObject(DisplayObject* display_object) {
    GeoNode_CreateModelPart(NULL, display_object, 0, &D_80060450, &D_8006045C, &D_80060464);
    GraphNode_AppendChild(&D_800AD1D0, &display_object->node);
    display_object->effectSlot = 0;
    display_object->node.flags &= ~1;
}

/** Attaches a display object to the secondary display root. */
void ModelRenderer_AttachSecondaryDisplayObject(DisplayObject* arg0) {
    GeoNode_CreateModelPart(NULL, arg0, 0, &D_80060450, &D_8006045C, &D_80060464);
    GraphNode_AppendChild(&D_800AD1E8, &arg0->node);
    arg0->node.flags &= ~1;
}

// FAKE: battle_hud.c defines func_800325B0 with one parameter, but this call
// passes object_type as a second argument (a1) in the ROM.
void func_800325B0(u32 arg0, u32 arg1);

/** Initializes a display object for a root and object type. */
void Model_InitDisplayObject(DisplayObject* display_object, s16 root_id, s16 object_type, ModelNodeView* child) {
    DisplayObject* obj; // FAKE

    GraphNode_AppendChild(&display_object->node, child);
    MtxF_Identity(&display_object->matrix);
    display_object->rootId = root_id;
    display_object->objectType = object_type;
    display_object->alpha = 0xFF;
    display_object->textureMode = 0;
    display_object->node.flags |= 0x1;
    display_object->node.renderFlags &= ~0x4;
    obj = display_object;
    obj->node.renderFlags |= 0x20;
    obj->node.renderFlags |= 0x40;
    obj->node.renderFlags &= ~0x2;
    display_object->fogColor.rgba = 0xFFFFFF00;
    display_object->textureTint.rgba = 0xFFFFFF00;
    display_object->transformAnim.animationId = -1;
    display_object->transformAnim.data = 0;
    display_object->eventTrack.trackId = -1;
    display_object->eventTrack.data = 0;
    display_object->node.renderFlags &= ~0x8;
    if (object_type > 0) {
        func_800325B0(obj->effectSlot, object_type);
    }
}

/** Detaches a display object from its children. */
void ModelRenderer_ClearDisplayObject(DisplayObject* arg0) {
    arg0->node.children = NULL;
    arg0->node.flags &= ~1;
}

/** Binds the animation with the given id from the object's model asset. */
s32 ModelAnim_SetAnimation(DisplayObject* display_object, s32 id) {
    ModelAssetNode* asset_node = display_object->node.children;
    ModelAnimationBank* animation_bank = asset_node->getAnimationBank(0, 0);

    if (id == -1) {
        ModelAnim_ClearTransformChannel(display_object);
    } else if (id < animation_bank->transformCount) {
        ModelAnim_BindTransformCurve(display_object, id, animation_bank->transformTracks[id], 0x10000);
        return 1;
    }

    return 0;
}

/** Binds the event track with the given id from the object's model asset. */
s32 ModelAnim_SetEventTrack(DisplayObject* display_object, s32 track_id) {
    ModelAssetNode* asset_node = display_object->node.children;
    ModelAnimationBank* animation_bank = asset_node->getAnimationBank(0, 0);

    if (track_id == -1) {
        ModelAnim_ClearEventTrack(display_object);
    } else if (track_id < animation_bank->eventTrackCount) {
        ModelAnim_BindEventTrack(display_object, track_id, animation_bank->eventTracks[track_id]);
        return 1;
    }

    return 0;
}

/** Sets the material color of a display object. */
void Model_SetMaterialColor(DisplayObject* display_object, u8 r, u8 g, u8 b, u8 alpha) {
    Color_SetRGBA(&display_object->fogColor, r, g, b, alpha);
}

/** Sets the material alpha (LOD fraction) of a display object. */
void Model_SetMaterialAlpha(DisplayObject* arg0, u8 arg1) {
    arg0->alpha = arg1;
}

/*
    known modes:
    - 1 = Gold (Harden)

*/
void Model_SetMaterialTextureMode(DisplayObject* display_object, u8 texture_mode) {
    display_object->textureMode = texture_mode;
}

/**
 * Returns the animation bank record with the given index for a display object.
 */
ModelAnimationBank* ModelAnim_GetAnimationRecord(DisplayObject* arg0, s32 arg1) {
    ModelAnimationBank* var_v1 = NULL;

    if (arg0 == NULL) {
        arg0 = D_8006049C;
    }

    if (arg0 != NULL) {
        ModelAssetNode* tmp = arg0->node.children;

        var_v1 = tmp->getAnimationBank(arg1, 0);
    }

    return var_v1;
}

extern unk_D_8006FF00 D_80064C5C[];

/**
 * Derive the material color variant from a non-default nickname, OT id, and OT name.
 * Seen in play (2026-11-13) (tour of menus and a COM battle): ran in the party screen,
 * registration, Free Battle setup and a switch in battle.
 * @unverified Name and comment from Stadium 1, matched by code similarity.
 */
arg1_func_80010CA8* Model_ComputeNicknameColorVariant(arg1_func_80010CA8* arg0, BattleMon* arg1) {
    UNUSED s32 pad; // FAKE: stack padding
    char sp38[0xB];
    arg1_func_80010CA8 sp34;
    unk_D_8006FF00* sp30;
    UNUSED s32 pad2; // FAKE: stack padding
    u8 var_a0;
    s8* var_v1;

    sp30 = &D_80064C5C[arg1->species.id - 1];
    sp34.raw = 0;

    Text_CopySpeciesName(sp38, arg1->species.id);

    if (HAL_Strcmp(arg1->nickname, sp38) != 0) {
        var_a0 = ((arg1->otId >> 8) & 0xFF) + (arg1->otId & 0xFF);

        if (1) {}  // karodo

        var_v1 = arg1->nickname;
        while (*var_v1) {
            var_a0 += *var_v1++ & 0xFF;
            var_a0 += 0;
        }

        var_v1 = (s8*)arg1 + 0x40;
        while (*var_v1) {
            var_a0 += *var_v1++ & 0xFF;
            var_a0 += 0;
        }

        sp34.unk_00 = ((((sp30->unk_12 - sp30->unk_10) << 6) * var_a0) / 255) + (sp30->unk_10 << 6);
    }

    *arg0 = sp34;
    return arg0;
}

typedef struct IconLoader19D08 {
    u8 flags;
    char pad01[0x17];
    s32 loadedModel;
} IconLoader19D08;
typedef struct Obj80019D08 {
    u8 flags;
    u16 unk_02;
    BattleMon* unk_04;
    char pad08[8];
    IconLoader19D08* unk_10;
    s32 unk_14;
} Obj80019D08;
s32 func_80005014(void);
void func_8001799C(IconLoader19D08*, u16, arg1_func_80010CA8);
void func_80017D00(IconLoader19D08*);

void func_80019D08(Obj80019D08* arg0) {
    arg1_func_80010CA8 sp24;

    sp24.raw = 0;
    if (!(arg0->flags & 0x40) && (arg0->flags & 0x80)) {
        if (arg0->unk_04 != NULL) {
            Model_ComputeSizeVariant(&sp24, arg0->unk_04);
        }
        if (!(arg0->unk_10->flags & 4)) {
            while (func_80005014() != 0) {}
        }
        func_8001799C(arg0->unk_10, arg0->unk_02, sp24);
        arg0->flags |= 0x40;
        arg0->flags &= ~0x10;
        if (arg0->flags & 0x20) {
            func_80017D00(arg0->unk_10);
            arg0->unk_14 = arg0->unk_10->loadedModel;
            arg0->flags &= ~0xE0;
        }
    }
}

/** Polls the icon loader for a display object's frame load. */
void PokeIcon_PollFrameLoadForObject(unk_func_8001C248* arg0) {
    if (PokeIcon_PollFrameLoad(arg0->node.callback)) {
        arg0->node.callbackArg = arg0->node.callback->loadedModel;
        arg0->node.type &= ~0xE0;
        arg0->node.type |= 0x10;
    }
}

/** Waits for the icon loader to finish a display object's frame load. */
void PokeIcon_WaitFrameLoadForObject(unk_func_8001C248* arg0) {
    if (arg0->node.type & 0x40 && PokeIcon_WaitFrameLoad(arg0->node.callback) != 0) {
        arg0->node.callbackArg = arg0->node.callback->loadedModel;
        arg0->node.type &= ~0xE0;
        arg0->node.type |= 0x10;
    }
}

/** Requests a background load for a display object. */
void PokeIcon_RequestBackgroundForObject(unk_func_8001C248* arg0) {
    if (!(arg0->unk_01D & 0x40) && (arg0->unk_01D & 0x80)) {
        PokeIcon_RequestBackgroundLoad(arg0->node.callback, arg0->unk_020, arg0->unk_024);
        arg0->unk_01D |= 0x40;
        arg0->unk_01D &= ~0x10;
        if (arg0->unk_01D & 0x20) {
            PokeIcon_WaitBackgroundLoad(arg0->node.callback);
            arg0->unk_024 = arg0->node.callback->loadedBackground;
            arg0->unk_01D &= ~0xE0;
        }
    }
}

/** Polls the icon loader for a display object's background load. */
void PokeIcon_PollBackgroundForObject(unk_func_8001C248* arg0) {
    if (PokeIcon_PollBackgroundLoad(arg0->node.callback) != 0) {
        arg0->unk_024 = arg0->node.callback->loadedBackground;
        arg0->unk_01D &= ~0xE0;
        arg0->unk_01D |= 0x10;
    }
}

extern u8 D_8006081F[];
extern u8 D_8005E7D2[];
extern u8 D_8005E47F[];
extern u8 D_8005E37F[];
s32 func_80019F70(u16 arg0) {
    s32 c = arg0;
    s32 ret = 0;

    if (c >= 0x21 && c < 0x7F) {
        ret = D_8006081F[c];
    } else if (c >= 0x2122 && c < 0x2178) {
        ret = D_8005E7D2[c];
    } else if (c >= 0x2330 && c < 0x233A) {
        ret = c - 0x2320;
    } else if (c >= 0x2341 && c < 0x235B) {
        ret = c - 0x2327;
    } else if (c >= 0x2361 && c < 0x237B) {
        ret = c - 0x22CC;
    } else if (c >= 0x2421 && c < 0x2474) {
        ret = D_8005E47F[c] + 0xAF;
    } else if (c >= 0x2521 && c < 0x2574) {
        ret = D_8005E37F[c] + 0x45;
    } else if (c == 0x2574) {
        ret = 0xFF;
    }
    return ret;
}
