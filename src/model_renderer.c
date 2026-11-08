/* Stadium Zero resident code. */
/* C ported from the Stadium 1 decomp: src/model_renderer.c. */

#include "global.h"
#include "model_renderer.h"
#include "geo_node.h"
#include "model_animation.h"
#include "matrix.h"
#include "model_animation_events.h"
#include "battle_hud.h"
#include "gb_data.h"
#include "display_object_textures.h"
#include "game_state.h"
#include "dp_intro.h"
#include "hal_libc.h"
#include "geo_render.h"
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

void ModelRenderer_InitDisplayRoots(void) {
    GeoNode_CreateContainer(0, &D_800AD1D0);
    GeoNode_CreateContainer(0, &D_800AD1E8);
}

void ModelRenderer_AttachDisplayObject(DisplayObject* display_object) {
    GeoNode_CreateModelPart(NULL, display_object, 0, &D_80060450, &D_8006045C, &D_80060464);
    GraphNode_AppendChild(&D_800AD1D0, &display_object->node);
    display_object->effectSlot = 0;
    display_object->node.flags &= ~1;
}

void ModelRenderer_AttachSecondaryDisplayObject(DisplayObject* arg0) {
    GeoNode_CreateModelPart(NULL, arg0, 0, &D_80060450, &D_8006045C, &D_80060464);
    GraphNode_AppendChild(&D_800AD1E8, &arg0->node);
    arg0->node.flags &= ~1;
}

#ifdef NON_MATCHING
/* TODO: decompile func_80019924; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_80019924.s")
#endif

void ModelRenderer_ClearDisplayObject(DisplayObject* arg0) {
    arg0->node.children = NULL;
    arg0->node.flags &= ~1;
}

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

void Model_SetMaterialColor(DisplayObject* display_object, u8 r, u8 g, u8 b, u8 alpha) {
    Color_SetRGBA(&display_object->fogColor, r, g, b, alpha);
}

void Model_SetMaterialAlpha(DisplayObject* arg0, u8 arg1) {
    arg0->lodFraction = arg1;
}

/*
    known modes:
    - 1 = Gold (Harden)

*/
void Model_SetMaterialTextureMode(DisplayObject* display_object, u8 texture_mode) {
    display_object->textureMode = texture_mode;
}

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

arg1_func_80010CA8* func_80019BDC(arg1_func_80010CA8* arg0, BattleMon* arg1) {
    UNUSED s32 pad;
    char sp38[0xB];
    arg1_func_80010CA8 sp34;
    unk_D_8006FF00* sp30;
    UNUSED s32 pad2;
    u8 var_a0;
    s8* var_v1;

    sp30 = &D_80064C5C[arg1->unk_00.unk_00 - 1];
    sp34.raw = 0;

    Text_CopySpeciesName(sp38, arg1->unk_00.unk_00);

    if (HAL_Strcmp(arg1->unk_30, sp38) != 0) {
        var_a0 = ((arg1->unk_0E >> 8) & 0xFF) + (arg1->unk_0E & 0xFF);

        if (1) {}  // karodo

        var_v1 = arg1->unk_30;
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

void PokeIcon_PollFrameLoadForObject(unk_func_8001C248* arg0) {
    if (PokeIcon_PollFrameLoad(arg0->node.callback)) {
        arg0->node.callbackArg = arg0->node.callback->loadedModel;
        arg0->node.type &= ~0xE0;
        arg0->node.type |= 0x10;
    }
}

void PokeIcon_WaitFrameLoadForObject(unk_func_8001C248* arg0) {
    if (arg0->node.type & 0x40 && PokeIcon_WaitFrameLoad(arg0->node.callback) != 0) {
        arg0->node.callbackArg = arg0->node.callback->loadedModel;
        arg0->node.type &= ~0xE0;
        arg0->node.type |= 0x10;
    }
}

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
