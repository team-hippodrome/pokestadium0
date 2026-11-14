/* Stadium Zero fragment012_17ED00. */
/* C ported from the Stadium 1 decomp: src/fragments/battle_engine/battle_engine_313250.c, src/fragments/battle_engine/battle_engine_343BA0.c, src/fragments/battle_engine/battle_engine_361050.c, src/fragments/battle_prep/battle_prep_39ED60.c, src/fragments/clefairy_game/clefairy_game.c, src/fragments/cup_select/cup_select.c, src/fragments/demo_scenes/demo_scenes_15FA60.c, src/fragments/demo_scenes/demo_scenes_169A40.c, src/fragments/demo_scenes/demo_scenes_16A0E0.c. */

#include "battle.h"
#include "asset_archive.h"
#include "math.h"
extern s32 pad_D_843C60A0;
extern u16 D_82199F50;
extern u16 D_82199F52;
extern u16 D_82199F54;
extern u16 D_82199F56;
extern u16 D_82199F58;
extern u8 D_82199F32;
extern MoveData D_8219A494;

#include "global.h"

void ClefairyGame_DespawnPatternIcons(void);
void func_82123D4C(void);

extern s32 pad_86104B64[];

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

#include "math.h"
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

s32 Diorama_LogoRotateColorCallback(s32, GraphNode*);
s32 Diorama_ScaleRotateCallbackA(s32, GraphNode*);
s32 Diorama_ScaleRotateCallbackB(s32, GraphNode*);
s32 Diorama_GroupStateCallback(s32, GraphNode*);

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

/**
 * Empty.
 */
void func_8216D990(void) {
}

/**
 * Empty.
 */
void func_8216D998(void) {
}

/**
 * Empty.
 */
void func_8216D9A0(void) {
}

/**
 * Empty.
 */
void func_8216D9A8(void) {
}

/**
 * Empty.
 */
void func_8216D9B0(void) {
}

/**
 * Empty.
 */
void func_8216D9B8(void) {
}

/**
 * Intro camera step that does nothing.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal or j,
 * no pointer word, no lui/addiu pair in any fragment), so play cannot reach it.
 * @unverified Name from Stadium 1.
 */
void BattleScene_IntroStepNop(UNUSED CameraNode* arg0) {
}

/**
 * Empty.
 */
void func_8216D9C8(UNUSED s32 arg0) {
}

/**
 * Empty.
 */
void func_8216D9D0(void) {
}

/**
 * Draws a full-screen overlay in the saved primitive color, fully opaque.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal or j,
 * no pointer word, no lui/addiu pair in any fragment), so play cannot reach it.
 * @unverified Name from Stadium 1.
 */
void BattleAnim_DrawStoredColorOverlay(void) {
    BattleAnim_DrawFullScreenColorOverlay(gSavedPrimColorR, gSavedPrimColorG, gSavedPrimColorB, 0xFF);
}

/**
 * Calls AuxiliaryEffect_Init.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (164 of the moves).
 * @unverified Name from Stadium 1.
 */
void BattleAnim_ReinitAuxiliaryEffects(void) {
    AuxiliaryEffect_Init();
}

/**
 * Empty.
 */
void func_8216DA30(void) {
}

/**
 * Empty draw hook.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (112 of the moves).
 * @unverified Name from Stadium 1.
 */
void MewtwoIntro_DrawOverlay(void) {
}

/**
 * Update hook for start effects with nothing to run: returns -1 (done) right away.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (130 of the moves).
 * @unverified Name from Stadium 1.
 */
s32 BattleAnim_DefaultStartEffect_CompleteImmediately(void) {
    return -1;
}

/**
 * Update hook for end effects with nothing to run: returns -1 (done) right away.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (112 of the moves).
 * @unverified Name from Stadium 1.
 */
s32 BattleAnim_DefaultEndEffect_CompleteImmediately(void) {
    return -1;
}

/**
 * Empty.
 */
void func_8216DA50(void) {
}

/**
 * Empty.
 */
void func_8216DA58(void) {
}
