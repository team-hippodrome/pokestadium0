/* Declarations for src/model_renderer.c. */
#ifndef MODEL_RENDERER_H
#define MODEL_RENDERER_H

#include "global.h"
#include "stdarg.h"
#include "moves.h"
#include "m2c_macros.h"

typedef struct unk_func_8001C248 {
    /* 0x000 */ DisplayNodeHeader node;
    /* 0x018 */ s16 unk_018;
    /* 0x01A */ s16 unk_01A;
    /* 0x01C */ u8 unk_01C;
    /* 0x01D */ u8 backgroundLoadFlags; // @unverified: 0x80 requested, 0x40 loading, 0x20 wait, 0x10 done (PokeIcon_RequestBackgroundForObject)
    /* 0x01E */ char unk01E[0x2];
    /* 0x020 */ s32 backgroundFileList; // @unverified: passed as the file list to PokeIcon_RequestBackgroundLoad
    /* 0x024 */ s32* loadedBackground; // @unverified: gets ModelLoadContext.loadedBackground when the load finishes
} unk_func_8001C248; // size >= 0x28

#include "game_state.h"

// model_renderer.c
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
void PokeIcon_PollFrameLoadForObject(unk_func_8001C248* arg0);
void PokeIcon_WaitFrameLoadForObject(unk_func_8001C248* arg0);
void PokeIcon_RequestBackgroundForObject(unk_func_8001C248* arg0);
void PokeIcon_PollBackgroundForObject(unk_func_8001C248* arg0);
void Model_InitDisplayObject(DisplayObject* display_object, s16 root_id, s16 object_type, ModelNodeView* child); /* extern */

// functions defined in assembly
arg1_func_80010CA8* Model_ComputeSizeVariant(arg1_func_80010CA8* arg0, BattleMon* arg1);
void Trainer_RequestPokeIcon(BattleSide* arg0);

#endif // MODEL_RENDERER_H
