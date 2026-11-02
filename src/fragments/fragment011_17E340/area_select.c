/* Stadium Zero fragment011_17E340. */
/* C ported from the Stadium 1 decomp: src/fragments/area_select/area_select.c, src/fragments/battle_engine/battle_engine_3055E0.c, src/fragments/battle_engine/battle_engine_main.c. */

#include "fragments/area_select/area_select.h"
#include "graphics_textures.h"
#include "input.h"
#include "game_state.h"
#include "save_data.h"
#include "text_system.h"
#include "jpeg_stream.h"
#include "audio_sfx.h"
#include "cry.h"
#include "gfx_buffer.h"
#include "DDC0.h"
#include "matrix.h"
#include "controller.h"
#include "memory.h"
#include "stage_loader.h"
#include "math_util.h"
#include "variables.h"
typedef struct AreaSelectEntryConfig {
    /* 0x00 */ s16 x;
    /* 0x02 */ s16 y;
    /* 0x04 */ s16 orbitRadius;
    /* 0x06 */ s8 upArea;
    /* 0x07 */ s8 downArea;
    /* 0x08 */ s8 leftArea;
    /* 0x09 */ s8 rightArea;
    /* 0x0A */ Color_RGBA8 exitColor;
} AreaSelectEntryConfig;
typedef struct AreaSelectMagnemitePoint {
    /* 0x00 */ s16 x;
    /* 0x02 */ s16 y;
    /* 0x04 */ s16 diameter;
} AreaSelectMagnemitePoint;
typedef struct AreaSelectMagnemiteTrail {
    /* 0x00 */ s16 centerX;
    /* 0x02 */ s16 centerY;
    /* 0x04 */ s16 orbitRadius;
    /* 0x06 */ s16 scalePercent;
    /* 0x08 */ s16 orbitAngle;
    /* 0x0A */ s16 spriteFrame;
    // FAKE: AdvanceMagnemiteTrail and DrawAndAdvanceMagnemites access six
    // afterimages; this four-element declaration gives overlapping 0x24-byte trails.
    /* 0x0C */ AreaSelectMagnemitePoint afterimages[4];
} AreaSelectMagnemiteTrail;
typedef struct AreaSelectExitFade {
    /* 0x00 */ s16 x;
    /* 0x02 */ s16 y;
    /* 0x04 */ s16 halfExtent;
    /* 0x06 */ s16 blackBlendAlpha;
    /* 0x08 */ Color_RGBA8 color;
} AreaSelectExitFade;
extern s16 sAreaSelectBackgroundFadeAlpha;
extern s16 sAreaSelectGlowDiameter;
extern s16 sAreaSelectStateIds[];
extern u8* sAreaSelectNameBannerTextures[];
#define AREA_STADIUM 0
#define AREA_FREE_BATTLE 1
#define AREA_GYM_LEADER_CASTLE 2
#define AREA_VS_MEWTWO 3
#define AREA_MINIGAMES 4
#define AREA_HALL_OF_FAME 5
#define AREA_OAKS_LAB 6
#define AREA_GB_TOWER 7
#define AREA_NONE 8
#define AREA_SELECT_INTRO 0
#define AREA_SELECT_INPUT 1
#define AREA_SELECT_MOVE 2
#define AREA_SELECT_SHRINK 3
#define AREA_SELECT_CANCEL 4
#define AREA_SELECT_EXIT_FADE 5
#define AREA_SELECT_MEWTWO_EXIT 6
#define AREA_SELECT_DONE 7
#define AREA_SELECT_REVEAL_MEWTWO 8
extern AreaSelectEntryConfig sAreaSelectEntryConfigs[9];
extern u8* sAreaSelectMagnemiteTextures[];
extern char** sAreaSelectStrings;
extern BinArchive* sAreaSelectBackgroundArchive;
extern Vp sAreaSelectViewport;
extern Mtx sAreaSelectProjectionMtx;
extern u8* sAreaSelectCurrentBackground;
extern u8* sAreaSelectNextBackground;
extern AreaSelectExitFade sAreaSelectExitFade;
extern AreaSelectMagnemiteTrail sAreaSelectMagnemiteTrails[3];
extern s32 pad_D_822031D0[0x2];
extern s16 sAreaSelectSelectedIndex;
extern s16 sAreaSelectPreviousIndex;
extern s16 sAreaSelectTransitionFrame;
extern ModeSettings sAreaSelectModeSettings;
extern GameOptions sAreaSelectGameOptions;
#define AREA_BACKGROUND_NIGHT_DODRIO 2
#define AREA_BACKGROUND_DAY_DODRIO 1
#define AREA_BACKGROUND_DAY_DODUO 19
#define AREA_BACKGROUND_DAY_NORMAL 18

#include "fragments/battle_engine/battle_engine.h"
#include "moves.h"
#include "geo_render.h"
#include "matrix.h"
#include "pokemon.h"
extern unk_D_843901B0 gCameraPreset;
extern f32 gCameraDistTarget;
extern f32 D_8219A534;

#include "fragments/battle_engine/battle_engine.h"
#include "game_state.h"
#include "geo_node.h"
#include "geo_render.h"
#include "display_object_textures.h"
#include "model_renderer.h"
#include "graphics_textures.h"
#include "input.h"
#include "battle_hud.h"
#include "3D140.h"
#include "jpeg_stream.h"
#include "audio_loop_point.h"
#include "gfx_buffer.h"
#include "matrix.h"
#include "controller.h"
#include "geo_layout.h"
#include "memmap.h"
#include "memory.h"
extern CameraNode sStageCamera;
extern unk_D_8690A610 sStageFog;
extern GraphNode sStageLayout0;
extern GraphNode sStageLayout1;
extern GraphNode sStageLayout3;
extern CameraNode sSide1ThumbnailCamera;
extern CameraNode sSide2ThumbnailCamera;
extern u8* sSide1PokemonThumbnailImage;
extern u8* sSide2PokemonThumbnailImage;
extern void* sStageBackdrop;
extern GraphNode* sStageRoot;
extern GraphNode* sSide1ThumbnailRoot;
extern GraphNode* sSide2ThumbnailRoot;
extern DepthBuffer* sSide1PokemonThumbnail;
extern DepthBuffer* sSide2PokemonThumbnail;
extern BattleSessionTeams* sBattleSides;
extern s32 sIsPaused;
extern s32 sNextFaintBatch;
extern Color_RGBA8_u32 sTintColor;
extern f32 sStageScale;
extern s32 sCompletionGate;
extern u8 sBattleModeDispatch[];
extern u32 sStageGeoLayout[];
extern u32 sSide1ThumbnailLayout[];
extern u32 sSide2ThumbnailLayout[];

#include "m2c_macros.h"

void AreaSelect_PollInput(void);
void BattleScene_CameraPresetNop(UNUSED CameraNode* arg0);
void func_8180050C(void);

extern s32 D_818008A8;

s32 func_81800020(s32 arg0, s8 *arg1) {
    if (arg0 == 2) {
        M2C_FIELD(arg1, s16 *, 0x1A) = (s16) D_818008A8;
    }
    return 0;
}

void AreaSelect_PollInput(void) {
    Cont_StartReadInputs();
    Cont_ReadInputs();
    Input_ResetRepeatState();
}

void BattleScene_CameraPresetNop(UNUSED CameraNode* arg0) {
    if (arg0) {}
}

M2C_UNK func_80005928(M2C_UNK *, M2C_UNK);          /* extern */
M2C_UNK func_800069CC();                            /* extern */
M2C_UNK func_8001560C(s32);                         /* extern */
M2C_UNK func_800158C0();                            /* extern */
extern M2C_UNK D_800AA150;
extern s32 D_818008A0;
extern M2C_UNK D_818008B0;

s32 func_81800074(s32 arg0) {
    M2C_FIELD(&D_818008B0, s16 *, 0x20) = (s16) (M2C_FIELD(&D_818008B0, s16 *, 0x20) - 0xC0);
    func_800158C0();
    func_800069CC();
    func_80005928(&D_800AA150, 1);
    func_8001560C(D_818008A0);
    return 0;
}

/*
 * func_818000D0
 *
 * Draws a rectangular vertical-gradient panel.  The four arguments are the
 * panel's x, y, width and height (as s16), passed straight on to
 * Ui_DrawGradientPanel.  The top colour is dark blue (R0 G0 B50) and the
 * bottom colour is a brighter blue (R0 G0 B200).
 */
void func_818000D0(s16 arg0, s16 arg1, s16 arg2, s16 arg3) {
    Color_RGB8 sp24 = { 0x00, 0x00, 0x32 }; /* top colour    */
    Color_RGB8 sp20 = { 0x00, 0x00, 0xC8 }; /* bottom colour */

    Ui_DrawGradientPanel(arg0, arg1, arg2, arg3, &sp24, &sp20);
}

#ifdef NON_MATCHING
/* TODO: decompile func_8180014C; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment011_17E340/func_8180014C.s")
#endif

M2C_UNK func_80006780();
M2C_UNK func_8180003C();

/*
 * func_81800320
 *
 * Reads the pointer at offset 0xC of the object that D_818008A0 holds (once,
 * before the loop; called `target` below) and then runs 30 iterations
 * (var_s0 goes 0, -350, ... down to -10500 in steps of -0x15E, var_s2 goes
 * 0, 1500, ... in steps of 0x5DC). Each iteration:
 *  - calls func_8180003C();
 *  - stores (f32)(s16)(var_s0 / 30 + 0xDC) at target + 0xB8 and target + 0xAC;
 *  - stores (f32)(s16)(var_s2 / 30 + 0x4B0) at target + 0xB0;
 *  - calls func_81800074(0) and func_80006780().
 * The divisions are signed C divisions by 30 (truncating toward zero). What
 * the three float fields are is not established from this function.
 *
 * Matching notes: the declaration order (var_s0, var_s2, target) and the
 * initialisation order (var_s0, target, var_s2) decide which saved registers
 * the three values get. The `(var_s0 ^ 0)` in the loop test is a
 * matching-only construct (found with decomp-permuter): it only swaps the
 * operand order of the final `bne` to the retail order; `(var_s0 | 0)` does
 * the same.
 */
void func_81800320(void) {
    f32 temp_f0;
    s32 var_s0;
    s32 var_s2;
    void* target;

    var_s0 = 0;
    target = *(void**)((s8*)D_818008A0 + 0xC);
    var_s2 = 0;
    do {
        func_8180003C();
        temp_f0 = (f32)(s16)((var_s0 / 30) + 0xDC);
        *(f32*)((s8*)target + 0xB8) = temp_f0;
        *(f32*)((s8*)target + 0xAC) = temp_f0;
        *(f32*)((s8*)target + 0xB0) = (f32)(s16)((var_s2 / 30) + 0x4B0);
        func_81800074(0);
        func_80006780();
        var_s0 -= 0x15E;
        var_s2 += 0x5DC;
    } while ((var_s0 ^ 0) != -0x2904);
}

M2C_UNK func_80006780();                            /* extern */
M2C_UNK func_8180003C();                            /* extern */

void func_8180042C(void) {
    s16 var_s0;
    s16 var_s1;
    s32 var_s2;

    var_s0 = 0x3A;
    var_s1 = 0x18;
    var_s2 = 0;
    do {
        func_8180003C();
        func_81800074(0);
        func_818000D0((s16) (0x140 - (var_s0 / 2)), (s16) (0x196 - (var_s1 / 2)), var_s0, var_s1);
        func_80006780();
        var_s2 += 1;
        var_s0 += 0x1E;
        var_s1 += 6;
    } while (var_s2 != 8);
}

// Empty retail hook; its intended purpose is not established.
void func_8180050C(void) {
}

M2C_UNK func_80005B98(M2C_UNK);                     /* extern */
M2C_UNK func_800067BC(M2C_UNK);                     /* extern */
M2C_UNK func_80006998(M2C_UNK);                     /* extern */
M2C_UNK func_8000A7FC(M2C_UNK);                     /* extern */
M2C_UNK func_800407B0(M2C_UNK, M2C_UNK, M2C_UNK);   /* extern */
M2C_UNK func_8180014C(M2C_UNK, M2C_UNK);            /* extern */
void func_81800320(void);

void func_81800514(void) {
    func_800067BC(2);
    func_80005B98(0x1E);
    func_81800320();
    func_8180042C();
    func_800407B0(0x51, 0, 0);
    func_8000A7FC(0x1F4);
    func_8180014C(0x64, 1);
    func_80006998(1);
    func_80005B98(0x1E);
    func_8180014C(0x28, 0);
    func_800067BC(2);
}

extern u32 D_81800760[];
extern u32 D_8EA1B414[];
extern ModelNodeView* D_818008A4;
extern s16 D_818008D0;
void TransferPak_InitScene(void) {
    UNUSED s32 pad;
    MemoryBlock* sp18;

    sp18 = MainPool_AllocState(main_pool_get_available(), 0);

    D_818008A0 = (s32)process_geo_layout(sp18, D_81800760);
    D_818008A4 = (ModelNodeView*)process_geo_layout(sp18, D_8EA1B414);
    MainPool_FinalizeAllocation(sp18);
    ModelRenderer_InitDisplayRoots();
    ModelRenderer_AttachDisplayObject((DisplayObject*)&D_818008B0);
    Model_InitDisplayObject((DisplayObject*)&D_818008B0, 0, 0, D_818008A4);
    D_818008D0 = 0x4000;
}

M2C_UNK func_8000256C(M2C_UNK);
M2C_UNK func_80002620(M2C_UNK);
M2C_UNK func_80003EB8(u32, M2C_UNK *, M2C_UNK *, M2C_UNK);
M2C_UNK func_800040B4(s32, M2C_UNK *, M2C_UNK *);
M2C_UNK func_80005040(M2C_UNK, M2C_UNK);
M2C_UNK func_800050AC();
s32 func_8000645C(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, s32, s32);
M2C_UNK func_80006680(s32);
M2C_UNK func_800066C8();
M2C_UNK func_8001A194(M2C_UNK, M2C_UNK);
M2C_UNK func_8001A360();
M2C_UNK func_81800594();
extern M2C_UNK D_002E0BE0;
extern M2C_UNK D_002E2B90;
extern M2C_UNK D_0042CC80;
extern M2C_UNK D_00434C00;
extern M2C_UNK D_01000000;
extern s32 D_818008A8;
extern s32 D_818008AC;
extern M2C_UNK D_8EA00000;

/*
 * func_81800634
 *
 * Stores arg1 into D_818008AC and D_818008A8; D_818008A8 is changed to 3 if
 * arg1 is 4. Then it calls func_8000256C(0x54435550), func_80005040(0x10000, 0),
 * func_8000645C(1, 1, 2, 1, 2, 1) (result kept in a local), func_8001A194(0x10, 0),
 * func_80003EB8 and func_800040B4 with the segment-derived arguments below,
 * func_81800594(), func_80006680(result of func_8000645C), func_81800514(),
 * func_800066C8(), func_8001A360(), func_800050AC() and finally
 * func_80002620(0x54435550). Returns 0. arg0 is not used.
 *
 * Matching notes:
 *  - The test reads D_818008A8 back (`if (D_818008A8 == 4)`) instead of testing
 *    arg1. The compiler forwards the just-stored value, so the machine code
 *    compares a1, but the extra read uses up one temporary register number and
 *    makes the later constants land in t7/t8/t9 as in the retail code.
 *  - The unused `pad` local reserves the stack slot that sp20 needs to be at
 *    0x20(sp).
 * What the calls do is not established from this function.
 */
s32 func_81800634(s32 arg0, s32 arg1) {
    UNUSED s32 pad;
    s32 sp20;

    D_818008AC = arg1;
    D_818008A8 = arg1;
    if (D_818008A8 == 4) {
        D_818008A8 = 3;
    }
    func_8000256C(0x54435550);
    func_80005040(0x10000, 0);
    sp20 = func_8000645C(1, 1, 2, 1, 2, 1);
    func_8001A194(0x10, 0);
    func_80003EB8((u32)((s32)&D_01000000 & 0x0F000000) >> 0x18, &D_002E0BE0, &D_002E2B90, 0);
    func_800040B4(((u32)((s32)&D_8EA00000 & 0x0FF00000) >> 0x14) - 0x10, &D_0042CC80, &D_00434C00);
    func_81800594();
    func_80006680(sp20);
    func_81800514();
    func_800066C8();
    func_8001A360();
    func_800050AC();
    func_80002620(0x54435550);
    return 0;
}
