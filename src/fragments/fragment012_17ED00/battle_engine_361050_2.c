/* Stadium Zero fragment012_17ED00. */
/* C ported from the Stadium 1 decomp: src/fragments/battle_engine/battle_engine_313250.c, src/fragments/battle_engine/battle_engine_343BA0.c, src/fragments/battle_engine/battle_engine_361050.c, src/fragments/battle_prep/battle_prep_39ED60.c, src/fragments/clefairy_game/clefairy_game.c, src/fragments/cup_select/cup_select.c, src/fragments/demo_scenes/demo_scenes_15FA60.c, src/fragments/demo_scenes/demo_scenes_169A40.c, src/fragments/demo_scenes/demo_scenes_16A0E0.c. */

#include "fragments/battle_engine/battle_engine.h"
#include "math.h"
#include "jpeg_stream.h"
#include "gb_data.h"
extern unk_D_843C5568 gBattleAI_ActivePokemon[2];
extern s32 pad_D_843C60A0;
extern u16 D_82199F50;
extern u16 D_82199F52;
extern u16 D_82199F54;
extern u16 D_82199F56;
extern u16 D_82199F58;
extern u8 D_82199F32;
extern unk_D_843C6148 D_8219A494;
typedef struct unk_func_8437F068_sp28 {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 unk_01;
} unk_func_8437F068_sp28;
typedef struct unk_func_8437F85C_sp74 {
    /* 0x00 */ s32 unk_00[6];
} unk_func_8437F85C_sp74;

#include "fragments/battle_prep/battle_prep.h"
#include "geo_render.h"
#include "display_object_textures.h"
#include "model_renderer.h"
#include "ui_graphics.h"
#include "audio_commands_category2.h"
#include "gfx_rect.h"
#include "matrix.h"
#include "math_util.h"
#include "memmap.h"
#include "memory.h"

#include "global.h"
#include "fragments/particle_math/particle_math.h"
#include "jpeg_stream.h"
#include "controller.h"
#include "geo_render.h"
#include "model_animation.h"
#include "model_animation_events.h"
#include "geo_layout.h"
#include "display_object_textures.h"
#include "model_renderer.h"
#include "graphics_textures.h"
#include "input.h"
#include "ui_graphics.h"
#include "text_system.h"
#include "jpeg_stream.h"
#include "audio_sfx.h"
#include "audio_loop_point.h"
#include "gfx_buffer.h"
#include "gfx_rect.h"
#include "controller.h"
#include "fragments/widget_toolkit/widget_toolkit.h"
#include "memory.h"
#include "stage_loader.h"
typedef struct unk_D_861054C0 {
    /* 0x000 */ s16 unk_000;
    /* 0x002 */ s16 unk_002;
    /* 0x004 */ char pad4[4];
    /* 0x008 */ DisplayObject unk_008;
    /* 0x170 */ s16 unk_170;
    /* 0x172 */ u16 unk_172;
    /* 0x174 */ s16 unk_174[0xC];
    /* 0x18C */ s16 unk_18C;
    /* 0x18E */ s16 unk_18E[0xC];
    /* 0x1A6 */ s16 unk_1A6;
    /* 0x1A8 */ s16 unk_1A8;
    /* 0x1AA */ s16 unk_1AA;
    /* 0x1AC */ s16 unk_1AC;
    /* 0x1AE */ s16 unk_1AE;
    /* 0x1B0 */ s16 unk_1B0;
    /* 0x1B2 */ s16 unk_1B2;
    /* 0x1B4 */ s16 unk_1B4;
    /* 0x1B6 */ char pad1B6[2];
    /* 0x1B8 */ f32 unk_1B8;
    /* 0x1BC */ f32 unk_1BC;
} unk_D_861054C0;
typedef struct unk_D_86105EA0 {
    /* 0x000 */ char unk000[0x4];
    /* 0x004 */ DisplayObject unk_004;
} unk_D_86105EA0;
typedef struct unk_D_86106450 {
    /* 0x000 */ s16 unk_000;
    /* 0x002 */ s16 unk_002;
    /* 0x004 */ DisplayObject unk_004;
    /* 0x16C */ ModelNodeView* unk_16C;
} unk_D_86106450;
void ClefairyGame_DespawnPatternIcons(void);
void ClefairyGame_SpawnPatternIcons(void);
typedef struct unk_D_861047B8 {
    /* 0x00 */ u8 unk_00[6];
    /* 0x06 */ u8 unk_06[4];
} unk_D_861047B8;
typedef struct unk_D_86104984 {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
} unk_D_86104984;
typedef struct unk_D_861049B4 {
    /* 0x00 */ u32* unk_00;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
} unk_D_861049B4;
typedef struct unk_D_86104B5C {
    /* 0x00 */ u8 unk_00[3];
} unk_D_86104B5C;
extern s32 pad_86104B64[];

#include "fragments/cup_select/cup_select.h"
#include "geo_render.h"
#include "model_renderer.h"
#include "graphics_textures.h"
#include "input.h"
#include "save_data.h"
#include "jpeg_stream.h"
#include "audio_sfx.h"
#include "matrix.h"
#include "controller.h"
#include "geo_layout.h"
#include "memmap.h"
#include "memory.h"
#include "stage_loader.h"
#define SELECTED_CUP 0
#define SELECTING_DIVISION 1
#define SELECTED_DIVISION 2
extern BinArchive* sCupBackgroundBin;
extern void* sCupBackground;
extern GraphNode* sRenderNode;
extern GraphNode* sDivisionRender;
extern GraphNode* sArrowRender;
extern DisplayObject sDivisionListings[4];
extern DisplayObject sArrows[3];
extern s16 sHoveredDivision;
extern s16 sLatestUnlockedDivision;
extern u32 sRenderBlock[];
extern u32 sDivisionBlock[];
extern u32 sArrowBlock[];

#include "fragments/battle_engine/battle_engine.h"
#include "geo_node.h"
#include "model_animation.h"
#include "text_system.h"
#include "audio_commands.h"
#include "matrix.h"
#include "memory.h"
#include "util.h"

#include "fragments/battle_engine/battle_engine.h"
#include "gallery.h"
#include "gfx_buffer.h"
#include "math.h"
#include "math_util.h"
extern u8* sBattleAnimAssetPointers[256];
extern s16 sBattleAnimResourceList[0x10];
extern arg1_func_80019420* sBattleAnimResourceTablePointers[40];
extern s16 D_8219CAC0;
extern s16 D_8219CAC2;
extern Mtx D_8219CAC8;
extern s16 D_8219CB08;
extern s16 D_8219CB0A;
extern s16 D_8219CB0C;
extern s16 D_8219CB0E;
extern s16 D_8219CB10;
extern s16 D_8219CB12;
extern s16 D_8219CB14;
extern s16 D_8219CB16;
extern s16 D_8219CB18;
extern s16 D_8219CB1A;
extern const char D_821978C8[];

#include "fragments/demo_scenes/demo_scenes.h"
#include "geo_render.h"
#include "model_animation.h"
#include "geo_layout.h"
#include "display_object_textures.h"
#include "model_renderer.h"
#include "graphics_textures.h"
#include "input.h"
#include "save_data.h"
#include "text_system.h"
#include "jpeg_stream.h"
#include "audio_loop_point.h"
#include "gfx_rect.h"
#include "matrix.h"
#include "controller.h"
#include "fragments/particle_math/particle_math.h"
#include "memory.h"
#include "stage_loader.h"
typedef struct unk_D_86B0E5D8 {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ u8 unk_04;
    /* 0x05 */ u8 unk_05;
    /* 0x06 */ u8 unk_06;
    /* 0x07 */ u8 unk_07;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
} unk_D_86B0E5D8;
s32 Diorama_LogoRotateColorCallback(s32, GraphNode*);
s32 Diorama_ScaleRotateCallbackA(s32, GraphNode*);
s32 Diorama_ScaleRotateCallbackB(s32, GraphNode*);
s32 Diorama_GroupStateCallback(s32, GraphNode*);

#include "fragments/demo_scenes/demo_scenes.h"
#include "geo_render.h"
#include "model_animation.h"
#include "geo_layout.h"
#include "display_object_textures.h"
#include "model_renderer.h"
#include "graphics_textures.h"
#include "input.h"
#include "save_data.h"
#include "jpeg_stream.h"
#include "gfx_buffer.h"
#include "gfx_rect.h"
#include "DDC0.h"
#include "matrix.h"
#include "controller.h"
#include "memory.h"
#include "stage_loader.h"

#include "fragments/demo_scenes/demo_scenes.h"
#include "geo_render.h"
#include "model_animation.h"
#include "geo_layout.h"
#include "display_object_textures.h"
#include "model_renderer.h"
#include "graphics_textures.h"
#include "input.h"
#include "text_system.h"
#include "jpeg_stream.h"
#include "audio_loop_point.h"
#include "gfx_buffer.h"
#include "gfx_rect.h"
#include "matrix.h"
#include "controller.h"
#include "memory.h"
#include "stage_loader.h"
#include "fragments/fragment012_17ED00/battle_engine_361050_2_types.h"
extern unk_D_86B10BE0 D_8219A82C;

void func_8216D990(void);
void func_8216D998(void);
void func_8216D9A0(void);
void func_8216D9A8(void);
void func_8216D9B0(void);
void func_8216D9B8(void);
void BattleScene_IntroStepNop(UNUSED CameraNode* arg0);
void func_8216D9C8(UNUSED s32 arg0);
void func_8216D9D0(void);
void BattleAnim_DrawStoredColorOverlay(void);
void BattleAnim_ReinitAuxiliaryEffects(void);
void func_8216DA30(void);
void MewtwoIntro_DrawOverlay(void);
s32 BattleAnim_DefaultStartEffect_CompleteImmediately(void);
s32 BattleAnim_DefaultEndEffect_CompleteImmediately(void);
void func_8216DA50(void);
void func_8216DA58(void);

void func_8216D990(void) {
}

void func_8216D998(void) {
}

void func_8216D9A0(void) {
}

void func_8216D9A8(void) {
}

void func_8216D9B0(void) {
}

void func_8216D9B8(void) {
}

void BattleScene_IntroStepNop(UNUSED CameraNode* arg0) {
}

void func_8216D9C8(UNUSED s32 arg0) {
}

void func_8216D9D0(void) {
}

void BattleAnim_DrawStoredColorOverlay(void) {
    BattleAnim_DrawFullScreenColorOverlay(gSavedPrimColorR, gSavedPrimColorG, gSavedPrimColorB, 0xFF);
}

void BattleAnim_ReinitAuxiliaryEffects(void) {
    AuxiliaryEffect_Init();
}

void func_8216DA30(void) {
}

void MewtwoIntro_DrawOverlay(void) {
}

s32 BattleAnim_DefaultStartEffect_CompleteImmediately(void) {
    return -1;
}

s32 BattleAnim_DefaultEndEffect_CompleteImmediately(void) {
    return -1;
}

void func_8216DA50(void) {
}

void func_8216DA58(void) {
}
