/* Stadium Zero fragment011_17E340. */
/*
 * Cup-cleared trophy scene. game_state.c loads this fragment after the player wins the final
 * (round 8) of a tournament, with the cup index as the second entry argument. The scene pulls
 * the camera back from a spinning trophy, opens a blue banner and shows the cup name with a
 * blinking クリアー！! ("Clear!!") under it.
 * Seen in play (2026-11-14): Poké Ball Cup win in the L1-30 tournament. Poking the trophy and
 * title indices at CupClear_InitScene showed the Ultra Ball and Master Ball trophies and the
 * ハイパーボールカップ / トーナメント titles.
 */

#include "cup_clear.h"
#include "asset_archive.h"
#include "font.h"
#include "fragments/battle/battle.h"
#include "geo_layout.h"
#include "graphics_textures.h"
#include "input.h"
#include "main_pool.h"
#include "memory_main.h"
#include "model_renderer.h"
#include "save_data.h"
#include "variables.h"

// Declared here instead of in a header: the callers of these disagree on their types.
void MainPool_FinalizeAllocation(struct MemoryBlock* block);

#include "m2c_macros.h"

void CupClear_PollInput(void);
void func_8180006C(UNUSED CameraNode* arg0);
void func_8180050C(void);

// Trophy model shown (0 Poké Ball, 1 Great Ball, 2 Ultra Ball, 3 Master Ball). The L50-55
// tournament (cup 4) shows the Master Ball trophy.
extern s32 sCupClearTrophyIndex;

/**
 * Geo callback of the trophy model's switch node: picks the child for sCupClearTrophyIndex.
 * Seen in play: runs with context 0 at load and 2 every frame; poking sCupClearTrophyIndex to 2
 * and 3 showed the Ultra Ball and Master Ball trophies.
 */
s32 CupClear_SelectTrophyCallback(s32 context, GeoSwitchCaseNode* node) {
    if (context == 2) {
        node->selectedChild = (s16) sCupClearTrophyIndex;
    }
    return 0;
}

/** Starts and finishes a controller read; runs once per frame of the scene. */
void CupClear_PollInput(void) {
    Cont_StartReadInputs();
    Cont_ReadInputs();
    Input_ResetRepeatState();
}

// No callers in the ROM (checked: no jal, no address word, no lui/addiu pair).
void func_8180006C(UNUSED CameraNode* arg0) {
    if (arg0) {}  // karodo
}

void GfxImage_FillCurrent(Gfx** gfx_p, u16 fill_color);
void BgStage_DrawFrame(void);
void Geo_RenderRootNode(GraphNode* node);
void GeoRender_AdvanceFrameCounter(void);
extern Gfx* gDisplayListHead;
extern GraphNode* sCupClearStageRoot;
extern DisplayObject sCupClearTrophy;

/**
 * Draws one frame of the scene: turns the trophy by 0xC0 and renders the stage.
 * Seen in play: runs every frame from the camera pull-back to the end of the banner.
 */
s32 CupClear_DrawFrame(UNUSED s32 arg0) {
    sCupClearTrophy.rotation.y -= 0xC0;
    GeoRender_AdvanceFrameCounter();
    BgStage_DrawFrame();
    GfxImage_FillCurrent(&gDisplayListHead, 1);
    Geo_RenderRootNode(sCupClearStageRoot);
    return 0;
}

/**
 * Draws the banner's blue vertical-gradient panel at x, y with the given width and height.
 * Seen in play: the banner behind the cup name.
 */
void CupClear_DrawBannerPanel(s16 x, s16 y, s16 width, s16 height) {
    Color_RGB8 top_color = { 0x00, 0x00, 0x32 };    // #000032
    Color_RGB8 bottom_color = { 0x00, 0x00, 0xC8 }; // #0000C8

    Ui_DrawGradientPanel(x, y, width, height, &top_color, &bottom_color);
}

s32 BgStage_AdvanceFrame(void);
void Gfx_SetPrimColor(s32 r, s32 g, s32 b, s32 a);
void Font_EnableTwoCycleTexturing(void);
void Font_DisableTwoCycleTexturing(void);
s32 CupClear_DrawFrame(s32 arg0);
// Title shown in the banner: 0-3 the four cups, 4 the L50-55 tournament.
extern s32 sCupClearTitleIndex;
extern char sCupClearPokeBallCupText[];   // "モンスターボールカップ" (Poké Ball Cup)
extern char sCupClearGreatBallCupText[];  // "スーパーボールカップ" (Great Ball Cup)
extern char sCupClearUltraBallCupText[];  // "ハイパーボールカップ" (Ultra Ball Cup)
extern char sCupClearMasterBallCupText[]; // "マスターボールカップ" (Master Ball Cup)
extern char sCupClearTournamentText[];    // "トーナメント" (Tournament)
extern char sCupClearClearText[];         // "クリアー！" (Clear!)
extern char sCupClearExclamationText[];   // "！" (!)

/**
 * Shows the banner for `frames` frames: the cup name, and under it クリアー！! ("Clear!!").
 * With `blink` set, the クリアー！! line is hidden on frames 0-9, 20-24 and 35-39.
 * Seen in play: 100 blinking frames, then 40 steady frames while the scene fades out.
 */
void CupClear_ShowBannerText(s32 frames, s32 blink) {
    s32 i;

    for (i = 0; i < frames; i++) {
        CupClear_PollInput();
        CupClear_DrawFrame(0);
        CupClear_DrawBannerPanel(0xAB, 0x172, 0x12A, 0x48);
        Font_BeginTranslucentTextRendering();
        Font_EnableTwoCycleTexturing();
        Font_SetActive(0x10, -1);
        Gfx_SetPrimColor(0xFF, 0xFF, 0x32, 0xFF);
        switch ((u32)sCupClearTitleIndex) {
            case 0:
                Font_Printf(0xC1, 0x17A, sCupClearPokeBallCupText);
                break;
            case 1:
                Font_Printf(0xCD, 0x17A, sCupClearGreatBallCupText);
                break;
            case 2:
                Font_Printf(0xCD, 0x17A, sCupClearUltraBallCupText);
                break;
            case 3:
                Font_Printf(0xCD, 0x17A, sCupClearMasterBallCupText);
                break;
            case 4:
                Font_Printf(0xFB, 0x17A, sCupClearTournamentText);
                break;
        }
        Font_DisableTwoCycleTexturing();
        if ((blink == 0) || ((i >= 10) && (i < 20)) || ((i >= 25) && (i < 35)) || (i >= 40)) {
            Gfx_SetEnvColor(0xFF, 0xFF, 0x96, 0xFF);
            Font_Printf(0x105, 0x19A, sCupClearClearText);
            Font_Printf(0x16B, 0x19A, sCupClearExclamationText);
        }
        Font_EndTexturedTextRendering();
        BgStage_AdvanceFrame();
    }
}

/*
 * Pulls the camera back from the trophy over 30 frames: the eye and target y go from 220
 * down to -130 and the eye z from 1200 out to 2700.
 * Seen in play: the trophy shrinks from a close-up during the first second of the scene.
 *
 * Matching notes: the declaration order (step_y, step_z, camera) and the initialization
 * order (step_y, camera, step_z) decide which saved registers the three values get. The
 * `(step_y ^ 0)` in the loop test is a matching-only construct (found with decomp-permuter):
 * it only swaps the operand order of the final `bne` to the retail order; `(step_y | 0)`
 * does the same.
 */
void CupClear_PullBackCamera(void) {
    f32 y;
    s32 step_y;
    s32 step_z;
    CameraNode* camera;

    step_y = 0;
    camera = sCupClearStageRoot->children;
    step_z = 0;
    do {
        CupClear_PollInput();
        y = (f32)(s16)((step_y / 30) + 220);
        camera->view.targetPosition.y = y;
        camera->view.eyePosition.y = y;
        camera->view.eyePosition.z = (f32)(s16)((step_z / 30) + 1200);
        CupClear_DrawFrame(0);
        BgStage_AdvanceFrame();
        step_y -= 350;
        step_z += 1500;
    } while ((step_y ^ 0) != -10500);  // FAKE
}

/**
 * Opens the banner panel over 8 frames, growing it from 58x24 to 268x66 around (320, 406).
 * Seen in play: the empty blue banner widens before the cup name appears.
 */
void CupClear_OpenBannerPanel(void) {
    s16 width;
    s16 height;
    s32 i;

    width = 58;
    height = 24;
    i = 0;
    do {
        CupClear_PollInput();
        CupClear_DrawFrame(0);
        CupClear_DrawBannerPanel((s16) (320 - (width / 2)), (s16) (406 - (height / 2)), width, height);
        BgStage_AdvanceFrame();
        i += 1;
        width += 30;
        height += 6;
    } while (i != 8);
}

// No callers in the ROM (checked: no jal, no address word, no lui/addiu pair).
void func_8180050C(void) {
}

s32 StageFade_Start(s32 arg0);
void StageLoader_RunFrames(s32 timer);
void StageContext_SetClearColor(u16 color);
void Audio_StopMusic(s32 arg0);
s32 Audio_PlayCommand(u32 arg0, s32 arg1, s32 arg2);   /* extern */
void CupClear_ShowBannerText(s32 frames, s32 blink);
void CupClear_PullBackCamera(void);

/**
 * Runs the scene: fade in, camera pull-back, banner, audio command 0x51 and a music stop,
 * 100 frames of blinking text, then a 30-frame fade out over 40 steady frames.
 * Seen in play after a Poké Ball Cup win.
 */
void CupClear_PlaySequence(void) {
    StageLoader_RunFrames(2);
    StageFade_Start(30);
    CupClear_PullBackCamera();
    CupClear_OpenBannerPanel();
    Audio_PlayCommand(0x51, 0, 0);
    Audio_StopMusic(500);
    CupClear_ShowBannerText(100, 1);
    StageContext_SetClearColor(1);
    StageFade_Start(30);
    CupClear_ShowBannerText(40, 0);
    StageLoader_RunFrames(2);
}

extern u32 sCupClearStageGeoLayout[];
extern u32 D_8EA1B414[];
extern ModelNodeView* sCupClearTrophyModel;
/**
 * Builds the stage and trophy graph from their geo layouts and attaches the trophy display
 * object, facing rotation.y 0x4000. Seen in play at the start of the scene.
 */
void CupClear_InitScene(void) {
    UNUSED s32 pad; // FAKE: stack padding
    MemoryBlock* block;

    block = MainPool_AllocState(main_pool_get_available(), 0);

    sCupClearStageRoot = (GraphNode*)process_geo_layout(block, sCupClearStageGeoLayout);
    sCupClearTrophyModel = (ModelNodeView*)process_geo_layout(block, D_8EA1B414);
    MainPool_FinalizeAllocation(block);
    ModelRenderer_InitDisplayRoots();
    ModelRenderer_AttachDisplayObject(&sCupClearTrophy);
    Model_InitDisplayObject(&sCupClearTrophy, 0, 0, sCupClearTrophyModel);
    sCupClearTrophy.rotation.y = 0x4000;
}

u32 main_pool_push_state(u32 arg);
u32 main_pool_pop_state(u32 arg);
u8* Asset_LoadToSegment(s32 id, u8* rom_start, u8* rom_end, s32 arg3);
void Gfx_InitDisplayListBuffers(u32 buffer_size, s32 pool_side);
void Gfx_FreeDisplayListBuffers(void);
void StageContext_Deactivate(void);
s32 Font_Init(s32 load_size, s32 side);
void Font_Free(void);
void CupClear_InitScene(void);
extern u8 D_002E0BE0[];
extern u8 D_002E2B90[];
extern u8 D_0042CC80[];
extern u8 D_00434C00[];
extern M2C_UNK D_01000000;
extern M2C_UNK D_8EA00000;

/**
 * Fragment entry. `cup` is the cleared cup (0 Poké Ball, 1 Great Ball, 2 Ultra Ball,
 * 3 Master Ball, 4 the L50-55 tournament, which shows the Master Ball trophy). Loads the
 * stage and trophy assets, runs the scene and frees everything again. Returns 0.
 * Seen in play: entered with cup 0 after a Poké Ball Cup win.
 *
 * Matching notes:
 *  - The test reads sCupClearTrophyIndex back instead of testing `cup`. The compiler
 *    forwards the just-stored value, so the machine code compares a1, but the extra read uses
 *    up one temporary register number and makes the later constants land in t7/t8/t9 as in
 *    the retail code.
 *  - The unused `pad` local reserves the stack slot that `stage` needs to be at 0x20(sp).
 */
s32 CupClear_Main(UNUSED s32 arg0, s32 cup) {
    UNUSED s32 pad; // FAKE: stack padding
    StageContext* stage;

    sCupClearTitleIndex = cup;
    sCupClearTrophyIndex = cup;
    if (sCupClearTrophyIndex == 4) {
        sCupClearTrophyIndex = 3;
    }
    main_pool_push_state('TCUP');
    Gfx_InitDisplayListBuffers(0x10000, 0);
    stage = StageContext_Allocate(1, 1, 2, 1, 2, 1);
    Font_Init(0x10, 0);
    Asset_LoadToSegment((u32)((s32)&D_01000000 & 0x0F000000) >> 0x18, D_002E0BE0, D_002E2B90, 0);
    Fragment_Load(((u32)((s32)&D_8EA00000 & 0x0FF00000) >> 0x14) - 0x10, D_0042CC80, D_00434C00);
    CupClear_InitScene();
    StageContext_Activate(stage);
    CupClear_PlaySequence();
    StageContext_Deactivate();
    Font_Free();
    Gfx_FreeDisplayListBuffers();
    main_pool_pop_state('TCUP');
    return 0;
}
