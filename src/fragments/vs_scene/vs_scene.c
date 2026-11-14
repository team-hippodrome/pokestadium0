/* Stadium Zero fragment013_232510. */
/*
 * The VS scene: the stadium's big screen before and after every Free Battle and tournament battle.
 * Entry point VsScene_Run(kind, session); see VsSceneKind in vs_scene.h. Seen in play (2026-11-14):
 *
 * Before a battle (VsScene_Play): the camera flies from the field into the big screen's flames
 * (VsScene_ZoomIntoScreen), then VsScene_PlayTitleAndRevealTeams plays, in tournaments only, the
 * flaming round title (バトル-2 etc.) and then the two trainer panels: they slide in, the VS letters
 * fly in, and the panels flip over to show each side's Pokémon. That flip is a model animation curve
 * (D_8F5054AC), not code; the panel's contents come from the geo callbacks in
 * src/fragments/vs_trainer_panel (fragment 032: VsPanel_PortraitCallback, VsPanel_TitleTextCallback,
 * VsPanel_NameTextCallback, VsPanel_IconCallback, VsPanel_NicknameCallback).
 * VsScene_ZoomOutOfScreen then pulls back to the field.
 *
 * After a battle: VsScene_PlayFreeBattleResults or VsScene_PlayTournamentResults show the results
 * board (icons of the Pokémon brought, HP bars draining to what is left, a red cross on each fainted
 * one, VsScene_PlayResultsBoard), then かち/まけ (VsScene_PlayWinLose). After a tournament win,
 * Tournament_PlayBadgeAward puts the round's badge on the trainer cap, asks
 * Tournament_RunContinuePrompt, and Tournament_PlayNextRoundTitle plays the next round's title and
 * panels in the same scene.
 */
/* C ported from the Stadium 1 decomp: src/fragments/demo_scenes/demo_scenes_161E60.c, src/fragments/jigglypuff_doodle/jigglypuff_doodle.c. */

#include "vs_scene.h"
#include "display_object_textures.h"
#include "font.h"
#include "fragments/cartridge_check/cartridge_check.h"
#include "gb_save.h"
#include "geo_layout.h"
#include "geo_render.h"
#include "gfx_buffer.h"
#include "graphics_textures.h"
#include "input.h"
#include "main_pool.h"
#include "matrix.h"
#include "memory_main.h"
#include "model_renderer.h"
#include "save_data.h"
#include "ui_graphics.h"
#include "global.h"
#include "m2c_macros.h"

// Declared here instead of in a header: the callers of these disagree on their types.
void MainPool_FinalizeAllocation(struct MemoryBlock* block);
extern u8 D_30074E0[];
extern u8 D_30092E0[];
extern u8 D_300B6E0[];
extern u8 D_300B980[];
extern u8 D_300BAD0[];
extern u8 D_300BED0[];
extern u8 D_300C2D0[];

extern u8* D_82202C1C[];
extern u8* D_82202C3C[];
extern u8 D_82202C60[];
extern u8 D_82202C7C[];
extern u8 D_82202CD0[];
extern u8 D_82202CEC[];
extern u8 D_82202D40[];
extern u8 D_82202DDC[];
extern u8 D_82202E9C[];
extern u8 D_82202F5C[];
extern u8 D_8220301C[];
extern VsSceneSide D_82203170[2];
extern DisplayObject* D_82203200;
extern GfxImage* D_82203208;
extern GfxImage* D_82203210[12];
extern GraphNode* D_82203240;
extern GraphNode* D_82203244;
extern GraphNode* D_82203248;
extern GraphNode* D_8220324C;
extern ModelNodeView* D_82203250;
extern ModelNodeView* D_82203254;
extern ModelNodeView* D_82203258;
extern BinArchive* D_8220325C;
extern s32 D_82203264;
extern DisplayObject D_82203268;
extern DisplayObject D_822033D0;
extern s16 D_822033E8;
extern DisplayObject D_82203538;
extern s32 D_8220354C;
extern s16 D_82203550;
extern Color_RGBA8 D_822036A0;
extern SessionContext* D_822036A4; // the session (gSessionContext) passed to VsScene_Run
extern s32 D_822036A8;
s32 Audio_PlayCommand(u32 arg0, s32 arg1, s32 arg2);
s32 VsScene_LightFollowCameraCallback(s32, GraphNode*);
s32 Completion_LightAngleCallbackB(s32, GraphNode*);

#include "math.h"


s32 VsScene_LightFollowCameraCallback(s32 phase, GraphNode* node);
void VsScene_UnusedStubA(void);
void VsScene_UnusedStubB(void);

/**
 * Camera node callback: sets the perspective (fov 39, near 50, far 6400) and eye position on the first call.
 * Seen in play (2026-11-13) ran as the VS screen started; the scene then showed the stadium's big
 * screen head-on.
 */
void VsScene_SetupCamera(s32 phase, CameraNode* camera) {
    if (phase == 0) {
        GeoCamera_SetPerspective(camera, 39.0f, 50.0f, 6400.0f);
        GeoCamera_SetEyeAtUp(camera, 0.0f, 0.0f, 1507.0f, 0.0f, 0.0f, -165.0f, 0);
    }
}

/**
 * Geo light callback: each draw (phase 2) points the light along the current camera's view,
 * pitch + 0x2000 and yaw - 0x2000. Stadium 1 calls its version Completion_LightAngleCallbackA.
 * Seen in play (2026-11-14) ran with phase 2 every frame of the tournament VS scene.
 */
s32 VsScene_LightFollowCameraCallback(s32 phase, GraphNode* node) {
    GeoLightNode* ptr = (GeoLightNode*)node;
    f32 sp28;
    s16 sp26;
    s16 sp24;

    if (phase == 2) {
        Vec3f_CalculateDistanceAngles(&D_80060488->view.targetPosition, &D_80060488->view.eyePosition, &sp28, &sp26, &sp24);
        ptr->pitch = sp26 + 0x2000;
        ptr->yaw = sp24 - 0x2000;
    }
    return 0;
}

/**
 * Geo callback: at layout build (phase 0) stores the node itself in the variable its callbackArg
 * (offset 0x14) points to. The three tournament stadium layouts (D_82202DDC, D_82202E9C, D_82202F5C)
 * pass &D_82203200, which VsScene_LoadGeoLayout then animates with D_8F20A788.
 * Seen in play (2026-11-14) ran in the tournament VS scene.
 */
void VsScene_StoreNodeCallback(s32 phase, s8 *node)
{
  s8 **new_var; // FAKE: permuter temp
  if (phase == 0)
  {
    new_var = *((s8 ***) (((s8 *) node) + 0x14));
    *new_var = node;
  }
}

void Cont_StartReadInputs(void);                            /* extern */
void Cont_ReadInputs(void);                            /* extern */
M2C_UNK func_8001B5F0();                            /* extern */

/**
 * Makes the per-frame calls the scene runs before drawing (Cont_StartReadInputs, Cont_ReadInputs, func_8001B5F0).
 * Seen in play (2026-11-13) ran every frame of the VS screen.
 */
s32 VsScene_BeginFrame(void) {
    Cont_StartReadInputs();
    Cont_ReadInputs();
    func_8001B5F0();
    return 0;
}


/**
 * Pushes the 'ICON' pool state and decides, per side, whether its team is shown.
 * Seen in play: runs as the VS scene opens before a tournament battle.
 */
void VsScene_PrepareTeams(void) {
    VsSceneSide* team;
    s32 i;

    main_pool_push_state('ICON');

    for (i = 0, team = D_82203170; i < 2; i++, team++) {
        if (D_822036A4->ruleCategory != 0) {
            team->teamLayout = 0;
        } else if (D_822036A4->battleSides[i].tagTeamSize == 2) {
            team->teamLayout = 2;
        } else {
            team->teamLayout = 1;
        }

        team->teamMember[0] = D_822036A4->battleSides[i].teamMember[0];
        team->rosterInfo[0] = D_822036A4->battleSides[i].teamMember[0]->rosterInfo;
        team->trainerFile = BinArchive_GetFile(D_8220325C, team->rosterInfo[0]->trainerIndex);

        if (D_822036A4->battleSides[i].tagTeamSize == 2) {
            team->teamMember[1] = D_822036A4->battleSides[i].teamMember[1];
            team->rosterInfo[1] = D_822036A4->battleSides[i].teamMember[1]->rosterInfo;
        } else {
            team->teamMember[1] = NULL;
            team->rosterInfo[1] = NULL;
        }
    }
}

uintptr_t Memmap_GetFragmentVaddr(void* addr);
void GfxImage_FillCurrent(Gfx** gfx_p, u16 fill_color);
extern u8 D_8F908980[];
extern u8 D_8FA08900[];
extern u8 D_8FB08900[];
extern Gfx D_80060398[];
/**
 * Draws the VS scene's backdrop: one of three full-screen stadium images (D_822036A8 1 to 3),
 * otherwise a plain fill.
 * Seen in play: runs every frame of the VS scene.
 * @unverified Which image is which not checked.
 */
void VsScene_DrawBackground(void) {
    uintptr_t img;

    if (D_822036A8 > 0) {
        switch (D_822036A8) {
            case 1:
                img = Memmap_GetFragmentVaddr(D_8F908980);
                break;
            case 2:
                img = Memmap_GetFragmentVaddr(D_8FA08900);
                break;
            case 3:
                img = Memmap_GetFragmentVaddr(D_8FB08900);
                break;
        }
        gDPSetCycleType(gDisplayListHead++, G_CYC_1CYCLE);
        gDPSetTexturePersp(gDisplayListHead++, G_TP_NONE);
        gDPSetCombineMode(gDisplayListHead++, G_CC_DECALRGB, G_CC_DECALRGB);
        gSPClearGeometryMode(gDisplayListHead++, G_ZBUFFER | G_LIGHTING);
        gDPLoadTextureBlock(gDisplayListHead++, img, G_IM_FMT_RGBA, G_IM_SIZ_32b, 4, 64, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                            G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        gSPTextureRectangle(gDisplayListHead++, 0, 0, 0x500, 0x200, G_TX_RENDERTILE, 0, 0, 0, 0x200);
        gSPTextureRectangle(gDisplayListHead++, 0, 0x200, 0x500, 0x3C0, G_TX_RENDERTILE, 0, 0x7E0, 0, 0);
        gSPDisplayList(gDisplayListHead++, D_80060398);
        return;
    }
    GfxImage_FillCurrent(&gDisplayListHead, 1);
}

extern u8* D_86B10828;
extern GraphNode* D_86B106B4;
void VsScene_DrawBackground(void);

/**
 * Draws one frame of the scene into the offscreen image.
 * Seen in play (2026-11-13) ran every frame of the VS screen.
 */
s32 VsScene_DrawFrameToImage(s32 unused) {
    s32 sp24 = VsScene_BeginFrame();

    GeoRender_AdvanceFrameCounter();
    PokeIcon_ProcessNextSlot((PokeIconRenderer*)D_82203264, 0);
    GfxImage_SetRenderTarget(&gDisplayListHead, D_82203208);
    GfxImage_ClearDepthRectangle(&gDisplayListHead, 0, 0, 0x140, 0xF0);
    Geo_RenderRootNode(D_82203244);
    BgStage_DrawFrame();
    VsScene_DrawBackground();
    Geo_RenderRootNode(D_82203240);
    return sp24;
}

/**
 * Draws one frame of the scene over the background stage.
 * Seen in play: draws the VS scene's frames while the 「バトル」 title and VS panels play.
 */
s32 VsScene_DrawFrame(s32 unused) {
    s32 sp24 = VsScene_BeginFrame();

    GeoRender_AdvanceFrameCounter();
    PokeIcon_ProcessNextSlot((PokeIconRenderer*)D_82203264, 0);
    BgStage_DrawFrame();
    GfxImage_ClearDepthRectangle(&gDisplayListHead, 0, 0, 0x140, 0xF0);
    Geo_RenderRootNode(D_82203244);
    return sp24;
}

M2C_UNK func_80006780();                            /* extern */
s32 func_80027214(s8 *, s32);                       /* extern */

/*
 * VsScene_ZoomIntoScreen
 *
 * Reads the word at offset 0xC of D_82203240 (the `children` pointer of
 * that GraphNode; call it `rec`), fills two
 * 0x3C-byte local buffers with func_800273E8: from D_82202CD0 and D_82202CEC
 * when D_822036A4->mode is 0, from D_82202C60 and D_82202C7C otherwise.
 * Then, while func_80027214(buf1, rec + 0xA8) returns non-zero, it calls
 * func_80027214(buf2, rec + 0xB4), then VsScene_DrawFrameToImage(0) and
 * func_80006780(), and stops as soon as VsScene_DrawFrameToImage returns non-zero.
 *
 * Same buffer pair and loop as CartridgeCheck_PlayExitToTitle. What the buffers, the record
 * and the helpers are is not established.
 *
 * Matching notes: `sp3C` is a stack local (as m2c reported it), the
 * 0x3C-byte arrays are real arrays (a scalar in their place gives a frame
 * of 72 bytes instead of 184), and the empty `do { } while (0);` has no
 * meaning of its own: decomp-permuter found it as the only change that
 * swaps the registers of the two buffer addresses (s3/s4) to the ROM's.
 */
/**
 * Moves the camera along its path from the stadium view into the big screen, drawing a frame each
 * step until the path ends or VsScene_DrawFrameToImage reports done.
 * Seen in play: the camera flies from the stadium (seen from the field) into the big screen's
 * flames.
 */
void VsScene_ZoomIntoScreen(void) {
    s8 sp7C[0x3C];
    s8 sp40[0x3C];
    s32 sp3C;
    s32 temp_s0_2;

    sp3C = (s32)D_82203240->children;
    if (D_822036A4->mode == 0) {
        func_800273E8(sp7C, (s32) &D_82202CD0);
        func_800273E8(sp40, (s32) &D_82202CEC);
    } else {
        func_800273E8(sp7C, (s32) &D_82202C60);
        func_800273E8(sp40, (s32) &D_82202C7C);
    }
    do {  // karodo
    } while (0);
    while (func_80027214(sp7C, sp3C + 0xA8) != 0) {
        func_80027214(sp40, sp3C + 0xB4);
        temp_s0_2 = VsScene_DrawFrameToImage(0);
        func_80006780();
        if (temp_s0_2 != 0) {
            break;
        }
    }
}

extern s8 D_82202C98;
extern s8 D_82202CB4;
extern s8 D_82202D08;
extern s8 D_82202D24;
M2C_UNK func_80005B98(M2C_UNK);
M2C_UNK func_8000A7FC(M2C_UNK);
/**
 * The reverse of VsScene_ZoomIntoScreen: moves the camera along the path from the big screen back
 * out to the stadium (D_82202D08/D_82202D24 in Free Battle, D_82202C98/D_82202CB4 in tournaments),
 * one frame per step. On step 20 it calls func_80005B98(0x20) and func_8000A7FC(0x3C) (@unverified:
 * the screen fades to white as the step runs).
 * Seen in play (2026-11-14) at the end of the pre-battle panels, the results board and the
 * next-round panels: the camera pulls back out of the screen to the field, then the screen fades.
 */
void VsScene_ZoomOutOfScreen(void) {
    s8 sp8C[0x3C];
    s8 sp50[0x3C];
    s32 i = 0;
    s32 rec;
    s32 done;

    rec = (s32)D_82203240->children;
    if (D_822036A4->mode == 0) {
        func_800273E8(sp8C, (s32) &D_82202D08);
        func_800273E8(sp50, (s32) &D_82202D24);
    } else {
        func_800273E8(sp8C, (s32) &D_82202C98);
        func_800273E8(sp50, (s32) &D_82202CB4);
    }
    do {  // karodo
    } while (0);
    while (func_80027214(sp8C, rec + 0xA8) != 0) {
        if (i++ == 0x14) {
            func_80005B98(0x20);
            func_8000A7FC(0x3C);
        }
        func_80027214(sp50, rec + 0xB4);
        done = VsScene_DrawFrameToImage(0);
        func_80006780();
        if (done != 0) {
            break;
        }
    }
}

/**
 * Empty. Nothing in the ROM calls it or holds its address (jal, j and pointer scan of every built
 * fragment, 2026-11-14).
 * @unverified Unreachable, so never seen in play.
 */
void VsScene_UnusedStubA(void) {
}

/**
 * Empty. Nothing in the ROM calls it or holds its address (same scan as VsScene_UnusedStubA).
 * @unverified Unreachable, so never seen in play.
 */
void VsScene_UnusedStubB(void) {
}


/**
 * Requests the icon of each Pokémon on a side's team (all it could pick, up to six) into icon slots
 * sideIndex * 6 onward and stores the images for the trainer panel's back.
 * Seen in play (2026-11-14): these are the six icons the panels show after they flip over
 * (イワイワ, パルパル, ... for the girl's Free Battle team).
 */
void VsScene_LoadTeamIcons(VsSceneSide* side, s32 sideIndex) {
    s32 i;
    s32 slot = sideIndex * 6;

    for (i = 0; i < 6; i++) {
        if (i < side->rosterInfo[0]->numberOfPokemonCanBePicked) {
            func_8001833C((PokeIconRenderer*)D_82203264, slot, &side->rosterInfo[0]->battleMon[i], 1);
        }
        side->iconImages[i] = PokeIcon_GetImage((PokeIconRenderer*)D_82203264, slot++);
    }
}

extern u8 D_8EC145CC[];
extern u8 D_8ED0FACC[];
extern u8 D_8EE0FDE0[];
extern u8 D_8F5054AC[];
extern u8 D_8F5054C8[];
/**
 * The pre-battle reveal: plays the round title, then the two trainer panels, which flip over to
 * reveal each side's Pokémon. Formerly VsScene_PlayBattleTitle.
 *
 * 1. Audio command 0x3C with a track by rule category (Free Battle 6, L1-30 1, L50-55 by cup 2-5)
 *    and, in tournaments, the round.
 * 2. Tournaments only (mode != 0): the round title model (model roundOrDemoId on D_82203248, the
 *    geo layout VsScene_LoadGeoLayout picked by round) runs one curve and is cleared:
 *    D_8EC145CC for rounds 1-6 (100 frames), D_8ED0FACC for round 7 and D_8EE0FDE0 for round 8
 *    (110 frames each). Seen: バトル-2 flies in letter by letter over the flames and shrinks away.
 * 3. The trainer panels (model on D_8220324C, geo layout D_8F504830 in vs_trainer_panel; its
 *    VsPanel_* callbacks fill in portrait, トレーナー, name, the six icons from VsScene_LoadTeamIcons
 *    and nicknames).
 *    Curve D_8F5054AC (160 frames) when neither side is a two-trainer team: the 1P panel slides in
 *    from the top right and the other side's from the bottom, the V and S letters fly in, then both
 *    panels rotate about their horizontal axis so their backs, with the team's Pokémon, face the
 *    camera. Curve D_8F5054C8 (100 frames) is used when either side has teamLayout 2
 *    (@unverified: no two-trainer battle was played).
 * The panel model is left on screen for VsScene_ZoomOutOfScreen.
 * Seen in play (2026-11-14) before a Free Battle (1P vs COM: panels and flip only) and from
 * Tournament_PlayNextRoundTitle before Monster Ball Cup round 2 (バトル-2, then 1P vs かじばどろぼう).
 */
void VsScene_PlayTitleAndRevealTeams(void) {
    s32 track;
    s32 pad; // FAKE
    DisplayObject* obj = (DisplayObject*)((GraphNode*)D_82203244->children)->children;
    s32 pad2; // FAKE

    switch (D_822036A4->ruleCategory) {
        case 0:
            if (!D_82203244->children) { // FAKE: karodo, empty if needed for regalloc
            }
            track = 6;
            break;
        case 1:
            track = 1;
            break;
        case 2:
            switch (D_822036A4->modeSelection) {
                case 0:
                    track = 2;
                    break;
                case 1:
                    track = 3;
                    break;
                case 2:
                    track = 4;
                    break;
                case 3:
                    track = 5;
                    break;
            }
            break;
    }
    if (D_822036A4->mode == 0) {
        Audio_PlayCommand(0x3C, 0, track);
    } else {
        Audio_PlayCommand(0x3C, D_822036A4->roundOrDemoId, track);
    }
    obj->rootId = D_822036A4->roundOrDemoId;
    if (D_822036A4->mode != 0) {
        if (D_822036A4->roundOrDemoId == 7) {
            Model_InitDisplayObject(&D_82203268, D_822036A4->roundOrDemoId, 0, (ModelNodeView*)D_82203248);
            ModelAnim_BindTransformCurve(&D_82203268, 1, D_8ED0FACC, 0x10000);
            BgStage_RunUntilCondition(0x6E, (s32(*)(u8))VsScene_DrawFrame);
            ModelRenderer_ClearDisplayObject(&D_82203268);
        } else if (D_822036A4->roundOrDemoId == 8) {
            Model_InitDisplayObject(&D_82203268, D_822036A4->roundOrDemoId, 0, (ModelNodeView*)D_82203248);
            ModelAnim_BindTransformCurve(&D_82203268, 1, D_8EE0FDE0, 0x10000);
            BgStage_RunUntilCondition(0x6E, (s32(*)(u8))VsScene_DrawFrame);
            ModelRenderer_ClearDisplayObject(&D_82203268);
        } else {
            Model_InitDisplayObject(&D_82203268, D_822036A4->roundOrDemoId, 0, (ModelNodeView*)D_82203248);
            ModelAnim_BindTransformCurve(&D_82203268, 1, D_8EC145CC, 0x10000);
            BgStage_RunUntilCondition(0x64, (s32(*)(u8))VsScene_DrawFrame);
            ModelRenderer_ClearDisplayObject(&D_82203268);
        }
    }
    Model_InitDisplayObject(&D_82203268, D_822036A4->roundOrDemoId, 0, (ModelNodeView*)D_8220324C);
    if ((D_82203170[0].teamLayout == 2) || (D_82203170[1].teamLayout == 2)) {
        ModelAnim_BindTransformCurve(&D_82203268, 1, D_8F5054C8, 0x10000);
        BgStage_RunUntilCondition(0x64, (s32(*)(u8))VsScene_DrawFrame);
    } else {
        ModelAnim_BindTransformCurve(&D_82203268, 1, D_8F5054AC, 0x10000);
        BgStage_RunUntilCondition(0xA0, (s32(*)(u8))VsScene_DrawFrame);
    }
}

extern u8 D_82400000[];
extern u8 D_00175570[];
extern u8 D_0017BE70[];
void VsScene_ZoomIntoScreen(void);
void VsScene_PlayTitleAndRevealTeams(void);
void VsScene_ZoomOutOfScreen(void);

/**
 * VS_SCENE_PRE_BATTLE: runs the VS scene before a battle: loads the session's trainer data
 * (fragment 009), both teams and their icons, places the camera (Free Battle or tournament
 * stadium), fades in with the scene music (0x12 Free Battle, 6 tournament), zooms into the big
 * screen, plays the round title and the trainer panel reveal, and zooms back out.
 * Seen in play: before the first モンスターボールカップ round, the stadium, the flaming 「バトル」 title on its
 * big screen, and 「トレーナー 1P VS トレーナー むしとり しょうねん」; before a Free Battle (2026-11-14)
 * the same without a title.
 */
void VsScene_Play(void) {
    CameraNode* camera = D_82203240->children;

    Fragment_LoadAndCall((((u32)D_82400000 & 0x0FF00000) >> 0x14) - 0x10, D_00175570, D_0017BE70, 0,
                         (u32)D_822036A4);
    VsScene_PrepareTeams();
    VsScene_LoadTeamIcons(&D_82203170[0], 0);
    VsScene_LoadTeamIcons(&D_82203170[1], 1);
    if (D_822036A4->mode == 0) {
        Vec3f_FromVec3s(&camera->view.targetPosition, (Vec3s*)(D_82202CEC + 2));
        Vec3f_FromVec3s(&camera->view.eyePosition, (Vec3s*)(D_82202CD0 + 2));
    } else {
        Vec3f_FromVec3s(&camera->view.targetPosition, (Vec3s*)(D_82202C7C + 2));
        Vec3f_FromVec3s(&camera->view.eyePosition, (Vec3s*)(D_82202C60 + 2));
    }
    StageLoader_RunFrames(2);
    StageFade_Start(0x80);
    if (D_822036A4->mode == 0) {
        Audio_PlayMusicIfChanged(0x12);
    } else {
        Audio_PlayMusicIfChanged(6);
    }
    BgStage_RunUntilCondition(0x40, VsScene_DrawFrameToImage);
    VsScene_ZoomIntoScreen();
    VsScene_PlayTitleAndRevealTeams();
    VsScene_ZoomOutOfScreen();
    ModelRenderer_ClearDisplayObject(&D_82203268);
    if (D_822036A4->sessionFlags & 2) {
        Save_ResetAndCommitTypedRecord(0x15, 0);
        D_822036A4->sessionFlags &= ~3;
    }
}

M2C_UNK Save_GetGbTowerSettings(s8 *, M2C_UNK);               /* extern */
M2C_UNK Save_SetGbTowerFrameTier(s8);                          /* extern */

/**
 * Unlocks the next GB Tower frame (reads the count with func_80025100, stores it + 1 with
 * func_80025168) and sets transitionFlags 0x8 for the first unlock, 0x10 for the second.
 * Named by the save-format thread from play (docs/annotation/n64-save-format.md on its branch);
 * not played again here.
 */
void Tournament_UnlockGbTowerFrame(void) {
    s8 sp1F;

    Save_GetGbTowerSettings(&sp1F, 0);
    switch (sp1F) {                                 /* irregular */
    case 0:
        Save_SetGbTowerFrameTier((s8) (sp1F + 1));
        D_822036A4->transitionFlags |= 8;
        return;
    case 1:
        Save_SetGbTowerFrameTier((s8) (sp1F + 1));
        D_822036A4->transitionFlags |= 0x10;
        return;
    }
}


/**
 * Sets transitionFlags 0x20 when the player's team came from a GB cartridge (port teamGbPort 0-3,
 * no rental on the team) and it brought a non-rental Pikachu (species 0x19) that does not know Surf
 * (move 0x39), presumably to start the Surfing Pikachu reward (fragment 010).
 * @unverified Not reached in play: needs a cup won with a GB Pikachu.
 */
void Tournament_CheckSurfPikachuReward(void) {
    SessionContext* state = D_822036A4;
    s32 player = state->teamGbPort;
    TeamRoster* roster;
    ExtendedRosterInfo* info;
    BattleMon* mon;
    s32 i;
    s32 j;

    if ((player >= 0) && (player < 4)) {
        roster = state->battleSides[0].teamMember[0];
        info = roster->rosterInfo;
        for (i = 0; i < info->numberOfPokemonCanBePicked; i++) {
            if (info->battleMon[i].species.isRental != 0) {
                return;
            }
        }

        for (i = 0; i < roster->numberOfPokemonBrought; i++) {
            mon = &roster->pokemonPicked[i];
            if ((mon->species.id == 0x19) && (mon->species.isRental == 0)) {
                for (j = 0; j < 4; j++) {
                    if (mon->moves[j] == 0) {
                        break;
                    }
                    if (mon->moves[j] == 0x39) {
                        return;
                    }
                }
                state->transitionFlags |= 0x20;
                return;
            }
        }
    }
}

s32 Save_GetProgressFlags(void);
void Save_SetProgressFlags(u16 arg0);

/**
 * The cup champion handler, called by Tournament_PlayBadgeAward after round 8: sets transitionFlags
 * 0x2 (and 0x4 for an L1-30 or Master Ball cup clear), records the cleared cup in the progress
 * flags and saves record 0x14; the first clear also unlocks a GB Tower frame and checks the Surfing
 * Pikachu reward. The game then loads fragment 011, the cup-cleared trophy scene.
 * Named by the save-format thread from play (docs/annotation/n64-save-format.md on its branch);
 * not played again here.
 */
void Tournament_RecordCupClear(void) {
    u16 lo = Save_GetProgressFlags() & 0xFF;
    u16 hi = (Save_GetProgressFlags() >> 8) & 0xFF;

    D_822036A4->transitionFlags |= 2;

    if (D_822036A4->mode == 1) {
        D_822036A4->transitionFlags |= 4;
        Tournament_CheckSurfPikachuReward();
        if (!(hi & 1)) {
            hi |= 1;
            Save_SetProgressFlags((hi << 8) | lo);
            Tournament_UnlockGbTowerFrame();
            Save_CommitTypedRecord(0x14, 0);
        }
    } else if (D_822036A4->mode == 2) {
        if (D_822036A4->modeSelection >= lo) {
            lo++;
            Save_SetProgressFlags((hi << 8) | lo);
            Save_CommitTypedRecord(0x14, 0);
        }
        if (D_822036A4->modeSelection == 3) {
            D_822036A4->transitionFlags |= 4;
            Tournament_CheckSurfPikachuReward();
            if (!(hi & 2)) {
                hi |= 2;
                Save_SetProgressFlags((hi << 8) | lo);
                Tournament_UnlockGbTowerFrame();
                Save_CommitTypedRecord(0x14, 0);
            }
        }
    }
}

/**
 * @unverified Name was previously used only by callers of this address; the definition was still func_.
 */
void BattleHud_DrawHpBarTexture(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4); //@src/ui_graphics.c

/**
 * Draws the HP bar of every Pokémon both teams brought, each into its own slot
 * image in D_82203210 (team i owns slots i * 6 to i * 6 + 5).
 *
 * The bar shows max(hp, maxHp * percent / 100) out of maxHp. VsScene_PlayResultsBoard calls this
 * with percent counting from 100 down to 0 in steps of 4, so each bar starts full and drains to
 * the Pokémon's current HP.
 * Seen in play (2026-11-14): on the tournament results board the bars drained to the HP left.
 *
 * A side with teamLayout 2 has two trainers (teamMember[0] and teamMember[1]) that use
 * three slots each; any other side has one trainer that uses all six slots.
 *
 * Each branch declares its own mon/hp/scaled. With one shared set, the loop
 * constant 2 is kept in a2 instead of retail's a0.
 */
void VsScene_DrawHpBars(s32 percent) {
    s32 i;
    s32 j;
    s32 k;
    VsSceneSide* p;

    for (i = 0; i < 2; i++) {
        p = &D_82203170[i];
        if (p->teamLayout == 2) {
            BattleMon* mon;
            s32 hp;
            s32 scaled;

            for (j = 0; j < 2; j++) {
                mon = p->teamMember[j]->pokemonPicked;
                for (k = 0; k < p->teamMember[j]->numberOfPokemonBrought; k++, mon++) {
                    scaled = (mon->maxHp * percent) / 100;
                    hp = (mon->hp >= scaled) ? mon->hp : scaled;
                    GfxImage_SetRenderTarget(&gDisplayListHead, D_82203210[i * 6 + j * 3 + k]);
                    BattleHud_DrawHpBarTexture(0, 0, 104, hp, mon->maxHp);
                }
            }
        } else {
            BattleMon* mon;
            s32 hp;
            s32 scaled;

            mon = p->teamMember[0]->pokemonPicked;
            for (k = 0; k < p->teamMember[0]->numberOfPokemonBrought; k++, mon++) {
                scaled = (mon->maxHp * percent) / 100;
                hp = (mon->hp >= scaled) ? mon->hp : scaled;
                GfxImage_SetRenderTarget(&gDisplayListHead, D_82203210[i * 6 + k]);
                BattleHud_DrawHpBarTexture(0, 0, 104, hp, mon->maxHp);
            }
        }
    }
}

extern u8 D_8F625700[];
void func_8001C058(s32, s32, s32, s32, u8*, s32, s32);

/**
 * Draws the red cross (64x64 texture D_8F625700 tinted #FF3214) over a Pokémon's icon image on the
 * results board.
 * Seen in play (2026-11-14): crosses appeared on the three fainted COM Pokémon after a tournament win.
 */
void VsScene_DrawFaintCross(GfxImage* iconImage) {
    u8* sp34 = (u8*)Util_ConvertAddrToVirtAddr((uintptr_t)D_8F625700);

    GfxImage_SetRenderTarget(&gDisplayListHead, iconImage);
    gSPDisplayList(gDisplayListHead++, gUiEnvTintTextureDL);
    gDPSetEnvColor(gDisplayListHead++, 255, 50, 20, 255); // #FF3214FF
    func_8001C058(0, 0, 0x40, 0x20, sp34, 0x40, 0);
    func_8001C058(0, 0x20, 0x40, 0x20, sp34 + 0x400, 0x40, 0);
    gSPDisplayList(gDisplayListHead++, gUiRestoreTextureDL);
}

/**
 * For the results board: requests the icons of the Pokémon a side brought into battle (three per
 * trainer for a two-trainer side, else up to six) into icon slots sideIndex * 6 onward, and stores
 * each icon image and its HP bar image (D_82203210[slot]). Formerly VsScene_LoadTagTeamIcons.
 * Seen in play (2026-11-14) at the start of the Free Battle and tournament results boards (the
 * three brought Pokémon per side in a tournament, six in Free Battle).
 */
void VsScene_LoadBroughtIcons(VsSceneSide* side, s32 sideIndex) {
    s32 slot = sideIndex * 6;
    s32 i;
    s32 j;

    if (side->teamLayout == 2) {
        for (i = 0; i < 2; i++) {
            for (j = 0; j < 3; j++) {
                if (j < side->teamMember[i]->numberOfPokemonBrought) {
                    func_8001833C((PokeIconRenderer*)D_82203264, slot, &side->teamMember[i]->pokemonPicked[j], 1);
                }
                side->iconImages[i * 3 + j] = PokeIcon_GetImage((PokeIconRenderer*)D_82203264, slot);
                side->hpBarImages[i * 3 + j] = D_82203210[slot]->img_p;
                slot++;
            }
        }
    } else {
        for (j = 0; j < 6; j++) {
            if (j < side->teamMember[0]->numberOfPokemonBrought) {
                func_8001833C((PokeIconRenderer*)D_82203264, slot, &side->teamMember[0]->pokemonPicked[j], 1);
            }
            side->iconImages[j] = PokeIcon_GetImage((PokeIconRenderer*)D_82203264, slot);
            side->hpBarImages[j] = D_82203210[slot]->img_p;
            slot++;
        }
    }
}

/**
 * Draws the fainted cross (VsScene_DrawFaintCross) and plays audio command 0x3D/2 for every brought
 * Pokémon whose faintBatch equals batch. VsScene_PlayResultsBoard calls it for batch 1 to 12 in a
 * Free Battle, 1 to 6 otherwise.
 * Seen in play (2026-11-14): all three COM Pokémon fainted in the same turn, got batch 1 and were
 * crossed out together.
 */
void VsScene_MarkFaintedBatch(s32 batch) {
    s32 idx;
    UNUSED s32 pad[2]; // FAKE: stack padding
    TeamRoster* team;
    s32 k;
    s32 j;
    s32 i;

    for (i = 0; i != 2; i++) {
        if (D_822036A4->battleSides[i].tagTeamSize == 2) {
            for (j = 0; j != 2; j++) {
                team = D_822036A4->battleSides[i].teamMember[j];
                // Fake match: an empty check found by the permuter fixes register allocation.
                if (team == NULL && team == NULL && team == NULL) {  // FAKE
                }
                for (k = 0; k < team->numberOfPokemonBrought; k++) {
                    if (batch == team->pokemonPicked[k].faintBatch) {
                        idx = i * 6 + j * 3 + k;
                        VsScene_DrawFaintCross(((PokeIconRenderer*)D_82203264)->slots[idx].image);
                        Audio_PlayCommand(0x3D, 2, idx + 1);
                    }
                }
            }
        } else {
            team = D_822036A4->battleSides[i].teamMember[0];
            for (k = 0; k < team->numberOfPokemonBrought; k++) {
                if (batch == (team->pokemonPicked + k)->faintBatch) {
                    idx = i * 6 + k;
                    VsScene_DrawFaintCross(((PokeIconRenderer*)D_82203264)->slots[idx].image);
                    Audio_PlayCommand(0x3D, 2, idx + 1);
                }
            }
        }
    }
}

/**
 * Returns 1 when any Pokémon either side brought has hp below maxHp, else 0. Decides whether the
 * results board plays the HP-drain sound (audio command 0x3D/1).
 * Seen in play (2026-11-14) ran on the results board.
 */
s32 VsScene_AnyMonDamaged(void) {
    VsSceneSide* p;
    BattleMon* mon;
    s32 i;
    s32 j;
    s32 k;

    for (i = 0; i < 2; i++) {
        p = &D_82203170[i];
        if (p->teamLayout == 2) {
            for (j = 0; j < 2; j++) {
                mon = p->teamMember[j]->pokemonPicked;
                for (k = 0; k < p->teamMember[j]->numberOfPokemonBrought; k++, mon++) {
                    if (mon->hp < mon->maxHp) {
                        return 1;
                    }
                }
            }
        } else {
            mon = p->teamMember[0]->pokemonPicked;
            for (k = 0; k < p->teamMember[0]->numberOfPokemonBrought; k++, mon++) {
                if (mon->hp < mon->maxHp) {
                    return 1;
                }
            }
        }
    }
    return 0;
}

M2C_UNK func_80006780();                            /* extern */
M2C_UNK func_80006828(M2C_UNK, M2C_UNK (*)(M2C_UNK)); /* extern */
s32 func_80018E24(s32);                             /* extern */
s32 Audio_PlayCommand(u32 arg0, s32 arg1, s32 arg2);   /* extern */
M2C_UNK VsScene_DrawFrame(M2C_UNK);                     /* extern */
void VsScene_DrawHpBars(s32);
void VsScene_MarkFaintedBatch(s32);
s32 VsScene_AnyMonDamaged();                                /* extern */

/**
 * The results board: drains the HP bars from full to the HP left over 26 steps (with the drain
 * sound when VsScene_AnyMonDamaged), waits until every icon is rendered, then crosses out the
 * fainted Pokémon batch by batch (VsScene_MarkFaintedBatch, 6 or 8 frames apart) and waits 30
 * frames.
 * Seen in play (2026-11-14) after a Free Battle surrender and after a tournament round win.
 */
void VsScene_PlayResultsBoard(void) {
    s32 var_s0;
    s32 var_s0_2;
    s32 var_s0_3;

    Audio_PlayCommand(0x3D, 0, 0);
    func_80006828(5, VsScene_DrawFrame);
    if (VsScene_AnyMonDamaged() != 0) {
        Audio_PlayCommand(0x3D, 1, 0);
    }
    var_s0 = 0x64;
    do {
        VsScene_DrawHpBars(var_s0);
        VsScene_DrawFrame(0);
        func_80006780();
        var_s0 -= 4;
    } while (var_s0 >= 0);
    if (func_80018E24(D_82203264) == 0) {
        do {
            VsScene_DrawFrame(0);
            func_80006780();
        } while (func_80018E24(D_82203264) == 0);
    }
    var_s0_2 = 1;
    if ((D_822036A4->mode == 0) && (D_822036A4->ruleCategory == 0)) {
        var_s0_3 = 1;
        do {
            VsScene_MarkFaintedBatch(var_s0_3);
            func_80006828(6, VsScene_DrawFrame);
            var_s0_3 += 1;
        } while (var_s0_3 != 0xD);
    } else {
        do {
            VsScene_MarkFaintedBatch(var_s0_2);
            func_80006828(8, VsScene_DrawFrame);
            var_s0_2 += 1;
        } while (var_s0_2 != 7);
    }
    func_80006828(0x1E, VsScene_DrawFrame);
}

M2C_UNK func_8001107C(M2C_UNK *, M2C_UNK, M2C_UNK *); /* extern */
s32 Audio_PlayCommand(u32 arg0, s32 arg1, s32 arg2);   /* extern */
extern M2C_UNK D_8F6256E0;

/**
 * Shows the outcome: audio command 0x3D/3 when side 0 won (battleSides[0].unk_1C == 1), 0x3D/4
 * otherwise, then runs curve D_8F6256E0 on the board model for 150 frames: the board flips back to
 * the trainer panels, かち (win) and まけ (lose) fly onto them, and the loser's panel shatters.
 * Seen in play (2026-11-14): after a Free Battle surrender 1P got まけ and its panel broke; after a
 * tournament win 1P got かち.
 */
void VsScene_PlayWinLose(void) {
    if (D_822036A4->battleSides[0].unk_1C == 1) {
        Audio_PlayCommand(0x3D, 3, 0);
    } else {
        Audio_PlayCommand(0x3D, 4, 0);
    }
    D_82203268.node.renderFlags |= 0x20;
    func_8001107C(&D_82203268, 0, &D_8F6256E0);
    func_80006828(0x96, &VsScene_DrawFrame);
}

extern Color_RGB8 D_8220308C;
extern Color_RGB8 D_82203090;
extern char D_822030CC[];
extern char D_822030EC[];
extern char D_822030F8[];
extern char D_82203108[];
extern char D_82203128[];
extern char D_8220314C[];
extern u8 D_8F625F00[];
extern Gfx D_80060290[];
void Tournament_SaveContinueData(void);

/**
 * Asks トーナメントをつづけますか？ (Continue the tournament?) with つづける (Continue) / ちゅうだんする (Quit), plus the GB cartridge warning.
 * Seen in play (2026-11-13) after winning tournament round 1 it showed トーナメントをつづけますか？ with つづける /
 * ちゅうだんする; つづける went on to the round 2 VS screen (サトシ vs かじばどろぼう).
 */
s32 Tournament_RunContinuePrompt(void) {
    Color_RGB8 top = D_8220308C;
    Color_RGB8 bottom = D_82203090;
    s32 sel = 0;
    s32 x;
    u8* tex;
    s32 pad; // FAKE

    D_822033D0.node.renderFlags &= ~0x20;
    D_82203538.node.renderFlags &= ~0x20;
    do {
        VsScene_DrawFrame(0);
        if (gPlayer1Controller->buttonPressed & (BTN_DLEFT | BTN_DRIGHT)) {
            Audio_PlaySoundEffectById(1);
            sel ^= 1;
        }
        Ui_DrawGradientPanel(0x1E, 0xAA, 0x104, 0x32, &top, &bottom);
        Font_BeginTranslucentTextRendering();
        Font_SetActive(2, 0);
        Font_Printf(0x4B, 0xB2, D_822030CC);
        Gfx_SetEnvColor(0xFF, 0xFF, (sel == 0) ? 0 : 0xFF, 0xFF);
        Font_Printf(0x55, 0xC6, D_822030EC);
        Gfx_SetEnvColor(0xFF, 0xFF, (sel == 1) ? 0 : 0xFF, 0xFF);
        Font_Printf(0xAA, 0xC6, D_822030F8);
        Font_EndTexturedTextRendering();
        gSPDisplayList(gDisplayListHead++, D_80060290);
        tex = D_8F625F00; // FAKE: temp stops the address being hoisted
        x = ((sel == 0) ? 0x21 : 0x76) + 0x1E;
        Gfx_DrawTextureRgba16(x, 0xC5, 0x18, 0xE, (u8*)Util_ConvertAddrToVirtAddr((uintptr_t)tex), 0x18, 0x200000);
        gSPDisplayList(gDisplayListHead++, D_80060398);
        func_80006780();
    } while (!(gPlayer1Controller->buttonPressed & BTN_A));
    if (sel == 1) {
        Audio_PlaySoundEffectById(0x1D);
        Tournament_SaveContinueData();
        do {
            VsScene_DrawFrame(0);
            Ui_DrawGradientPanel(0x1E, 0xAA, 0x104, 0x32, &top, &bottom);
            Font_BeginTranslucentTextRendering();
            Font_SetActive(2, 0);
            Font_Printf(0x34, 0xAF, D_82203108);
            Font_Printf(0x34, 0xBD, D_82203128);
            Font_Printf(0x34, 0xCB, D_8220314C);
            Font_EndTexturedTextRendering();
            func_80006780();
        } while (gPlayer1Controller->buttonPressed == 0);
        Audio_PlayCommand(0x56, 0, 0);
    }
    D_822033D0.node.renderFlags |= 0x20;
    D_82203538.node.renderFlags |= 0x20;
    return sel;
}

void Tournament_RecordCupClear(void);
s32 Tournament_RunContinuePrompt(void);

/**
 * After a tournament round, if side 0 won (battleSides[0].unk_1C == 1): the trainer cap
 * (D_822033D0, geo D_8EB300B0) and its sparkles (D_82203538, geo D_8EB37440) run the round's curves
 * from D_82202C1C and D_82202C3C, and the round's badge lands on the cap (audio 0x50, 0x51, and
 * 0x52 for the final). After round 8 it calls Tournament_RecordCupClear; otherwise it asks
 * Tournament_RunContinuePrompt and returns its answer (1 = quit). Returns 0 when side 0 lost.
 * Seen in play (2026-11-14) after winning Monster Ball Cup round 1: the cap with the badge, then
 * トーナメントをつづけますか？. The fragment 034 thread saw the badge and sparkles too.
 */
s32 Tournament_PlayBadgeAward(void) {
    s32 sp24 = 0;

    if (D_822036A4->battleSides[0].unk_1C == 1) {
        Model_InitDisplayObject(&D_822033D0, 1, 0, D_82203254);
        Model_InitDisplayObject(&D_82203538, 1, 0, D_82203258);
        ModelAnim_BindTransformCurve(&D_822033D0, 1, D_82202C1C[D_822036A4->roundOrDemoId], 0x10000);
        ModelAnim_BindTransformCurve(&D_82203538, 1, D_82202C3C[D_822036A4->roundOrDemoId], 0x10000);
        Audio_PlayCommand(0x50, 0, 0);
        D_8220354C = D_822036A4->roundOrDemoId - 1;
        if (D_822036A4->roundOrDemoId == 8) {
            BgStage_RunUntilCondition(0x5A, VsScene_DrawFrame);
            Audio_PlayCommand(0x51, 0, 0);
            BgStage_RunUntilCondition(0x19, VsScene_DrawFrame);
            Audio_PlayCommand(0x52, 0, 0);
            BgStage_RunUntilCondition(0x37, VsScene_DrawFrame);
            Tournament_RecordCupClear();
        } else {
            BgStage_RunUntilCondition(0x55, VsScene_DrawFrame);
            Audio_PlayCommand(0x51, 0, 0);
            BgStage_RunUntilCondition(0xF, VsScene_DrawFrame);
            sp24 = Tournament_RunContinuePrompt();
        }
    }
    return sp24;
}

extern u8 D_8F625614[];
extern u8 D_8F61F87C[];
void VsScene_LoadBroughtIcons(VsSceneSide* side, s32 sideIndex);
void VsScene_DrawHpBars(s32);
void VsScene_ZoomOutOfScreen(void);
void func_80041374(s32 arg0, s32 arg1);

/**
 * VS_SCENE_FREE_BATTLE_RESULTS: the scene after a Free Battle. Loads the brought Pokémon's icons,
 * puts the camera on the stadium, zooms into the big screen, plays the results board and
 * かち/まけ, and zooms back out (music 0xD).
 * Seen in play (2026-11-14) after surrendering a Free Battle against COM.
 */
void VsScene_PlayFreeBattleResults(void) {
    CameraNode* camera = D_82203240->children;

    VsScene_PrepareTeams();
    VsScene_LoadBroughtIcons(&D_82203170[0], 0);
    VsScene_LoadBroughtIcons(&D_82203170[1], 1);
    Vec3f_SetComponentsDuplicate(&camera->view.targetPosition, -1200.0f, 300.0f, 0.0f);
    Vec3f_SetComponentsDuplicate(&camera->view.eyePosition, 200.0f, 50.0f, 0.0f);
    StageLoader_RunFrames(2);
    Model_InitDisplayObject(&D_82203268, 1, 0, D_82203250);
    if (D_822036A4->battleSides[0].unk_1C == 1) {
        ModelAnim_BindTransformCurve(&D_82203268, 1, D_8F625614, 0x10000);
    } else {
        ModelAnim_BindTransformCurve(&D_82203268, 1, D_8F61F87C, 0x10000);
    }
    D_82203268.node.renderFlags &= ~0x20;
    StageFade_Start(0x20);
    Audio_PlayMusicIfChanged(0xD);
    VsScene_DrawHpBars(0x64);
    VsScene_ZoomIntoScreen();
    VsScene_PlayResultsBoard();
    VsScene_PlayWinLose();
    func_80041374(0x3D, 0);
    VsScene_ZoomOutOfScreen();
    ModelRenderer_ClearDisplayObject(&D_82203268);
    D_822036A4->transitionFlags |= 1;
}

extern u8 D_82400000[];
extern u8 D_00175570[];
extern u8 D_0017BE70[];
void VsScene_PrepareTeams(void);
void VsScene_PlayTitleAndRevealTeams(void);

/**
 * After the badge award: if side 0 won and the round is below 8, advances roundOrDemoId, reloads the
 * trainer data (fragment 009), the next opponent's team and icons, and plays the next round's title
 * and panel reveal (VsScene_PlayTitleAndRevealTeams) in the same scene with music 0xF. After round
 * 8 it waits 32 frames. Either way it sets transitionFlags 0x1.
 * Seen in play (2026-11-14): choosing つづける after round 1 played バトル-2 and the panels of 1P vs
 * かじばどろぼう (breakpoint: called from VsScene_PlayTournamentResults).
 */
void Tournament_PlayNextRoundTitle(void) {
    SessionContext* state = D_822036A4;

    if (state->battleSides[0].unk_1C == 1) {
        if (state->roundOrDemoId < 8) {
            state->roundOrDemoId++;
            ModelRenderer_ClearDisplayObject(&D_82203268);
            main_pool_pop_state('ICON');
            Fragment_LoadAndCall((((u32)D_82400000 & 0x0FF00000) >> 0x14) - 0x10, D_00175570, D_0017BE70, 0,
                                 (u32)D_822036A4);
            VsScene_PrepareTeams();
            VsScene_LoadTeamIcons(&D_82203170[0], 0);
            VsScene_LoadTeamIcons(&D_82203170[1], 1);
            D_822033E8 = D_822036A4->roundOrDemoId;
            D_82203550 = D_822036A4->roundOrDemoId;
            Audio_PlayMusicIfChanged(0xF);
            VsScene_PlayTitleAndRevealTeams();
        } else {
            BgStage_RunUntilCondition(0x20, VsScene_DrawFrame);
            D_822036A4->transitionFlags |= 1;
        }
    } else {
        state->transitionFlags |= 1;
    }
}

/**
 * VS_SCENE_TOURNAMENT_RESULTS: the scene after a tournament battle. Results board and かち/まけ as
 * in Free Battle (music 0xD, 0x10 for the final), then the badge award; quitting at the continue
 * prompt sets transitionFlags 0x41, continuing plays the next round's title and panels.
 * Seen in play (2026-11-14) after winning Monster Ball Cup round 1.
 */
void VsScene_PlayTournamentResults(void) {
    CameraNode* camera = D_82203240->children;

    VsScene_PrepareTeams();
    VsScene_LoadBroughtIcons(&D_82203170[0], 0);
    VsScene_LoadBroughtIcons(&D_82203170[1], 1);
    Vec3f_SetComponentsDuplicate(&camera->view.targetPosition, -1200.0f, 300.0f, 0.0f);
    Vec3f_SetComponentsDuplicate(&camera->view.eyePosition, 200.0f, 50.0f, 0.0f);
    StageLoader_RunFrames(2);
    Model_InitDisplayObject(&D_82203268, 1, 0, D_82203250);
    if (D_822036A4->battleSides[0].unk_1C == 1) {
        ModelAnim_BindTransformCurve(&D_82203268, 1, D_8F625614, 0x10000);
    } else {
        ModelAnim_BindTransformCurve(&D_82203268, 1, D_8F61F87C, 0x10000);
    }
    D_82203268.node.renderFlags &= ~0x20;
    StageFade_Start(0x20);
    if (D_822036A4->roundOrDemoId < 8) {
        Audio_PlayMusicIfChanged(0xD);
    } else {
        Audio_PlayMusicIfChanged(0x10);
    }
    VsScene_DrawHpBars(0x64);
    VsScene_ZoomIntoScreen();
    VsScene_PlayResultsBoard();
    VsScene_PlayWinLose();
    if (Tournament_PlayBadgeAward() != 0) {
        D_822036A4->transitionFlags |= 0x41;
    } else {
        Tournament_PlayNextRoundTitle();
    }
    func_80041374(0x3D, 0);
    VsScene_ZoomOutOfScreen();
    ModelRenderer_ClearDisplayObject(&D_82203268);
}


/**
 * Allocates twelve 104x12 images for the names and clears them.
 * Seen in play (2026-11-13) ran once as the VS screen (flames behind the stadium screen) started
 * after the Free Battle teams were confirmed.
 */
void VsScene_AllocNameImages(void) {
    s32 i;
    s32 j;

    for (i = 0; i < 12; i++) {
        D_82203210[i] = GfxImage_Allocate(0, 2, 0x68, 0xC, 0);
        for (j = 0; j < 0x68 * 0xC; j++) {
            ((u16*)D_82203210[i]->img_p)[j] = 0xFFFE;
        }
    }
}

extern u8 D_8EC13F98[];
extern u8 D_8ED0E1A0[];
extern u8 D_8EE0F378[];
extern u8 D_8F504830[];
extern u8 D_8F619890[];
extern u8 D_8EB300B0[];
extern u8 D_8EB37440[];
extern u8 D_8F20A788[];
void func_800270B4(s32 arg0, s32 arg1, s32 arg2, u8* arg3, s32 arg4, s32 arg5);

/**
 * Builds the scene's geo layouts: the stadium for the current stage kind (D_822036A8: Free Battle,
 * or tournament rounds 1-6, 7, 8), the scene root, the round title for `round`, the trainer panels
 * (vs_trainer_panel), the results board (vs_results_board), the badge cap and its sparkles
 * (tournament_badge_cap).
 * Seen in play (2026-11-13) ran once as the VS screen started; 2026-11-14 called from VsScene_Run.
 */
void VsScene_LoadGeoLayout(s32 round) {
    MemoryBlock* block = MainPool_AllocState(main_pool_get_available(), 0);

    switch (D_822036A8) {
        case 0:
            D_82203240 = process_geo_layout(block, D_8220301C);
            break;

        case 1:
            D_82203240 = process_geo_layout(block, D_82202DDC);
            break;

        case 2:
            D_82203240 = process_geo_layout(block, D_82202E9C);
            break;

        case 3:
            D_82203240 = process_geo_layout(block, D_82202F5C);
            break;
    }

    D_82203244 = process_geo_layout(block, D_82202D40);
    if ((round > 0) && (round < 7)) {
        D_82203248 = process_geo_layout(block, D_8EC13F98);
    } else if (round == 7) {
        D_82203248 = process_geo_layout(block, D_8ED0E1A0);
    } else if (round == 8) {
        D_82203248 = process_geo_layout(block, D_8EE0F378);
    }
    D_8220324C = process_geo_layout(block, D_8F504830);
    D_82203250 = (ModelNodeView*)process_geo_layout(block, D_8F619890);
    D_82203254 = (ModelNodeView*)process_geo_layout(block, D_8EB300B0);
    D_82203258 = (ModelNodeView*)process_geo_layout(block, D_8EB37440);
    MainPool_FinalizeAllocation(block);

    if (D_822036A8 == 0) {
        func_800270B4(0, 0xD89, -0x2C07, D_82203208->img_p, 0x16A8, 0x10FE);
    } else {
        func_800270B4(0, 0, 0, D_82203208->img_p, 0xC80, 0x960);
        ModelAnim_BindTransformCurve(D_82203200, 1, D_8F20A788, 0x10000);
    }
    VsScene_AllocNameImages();
    ModelRenderer_InitDisplayRoots();
    ModelRenderer_AttachDisplayObject(&D_82203268);
    ModelRenderer_AttachDisplayObject(&D_822033D0);
    ModelRenderer_AttachDisplayObject(&D_82203538);
    Color_SetRGB(&D_822036A0, 0xFF, 0xFF, 0xFF);
}

extern StageContext* D_82203204;
extern ModelLoadContext* D_82203260;
extern u8 D_01000000[];
extern u8 D_81000000[];
extern u8 D_8EB00000[];
extern u8 D_8EC00000[];
extern u8 D_8ED00000[];
extern u8 D_8EE00000[];
extern u8 D_8F200000[];
extern u8 D_8F300000[];
extern u8 D_8F500000[];
extern u8 D_8F600000[];
extern u8 D_8F900000[];
extern u8 D_8FA00000[];
extern u8 D_8FB00000[];
extern u8 D_0015B1A0[];
extern u8 D_0015E220[];
extern u8 D_002E0BE0[];
extern u8 D_002E2B90[];
extern u8 D_002F5940[];
extern u8 D_003139C0[];
extern u8 D_00317EF0[];
extern u8 D_0031C300[];
extern u8 D_00320820[];
extern u8 D_00326700[];
extern u8 D_003553C0[];
extern u8 D_0035C390[];
extern u8 D_0035E790[];
extern u8 D_00369F50[];
extern u8 D_0037B090[];
extern u8 D_00380D60[];
extern u8 D_00385D60[];
extern u8 D_0038A540[];
s32 Save_LoadSram(void);
s32 Font_Init(s32 load_size, s32 side);

#define DEMO_FRAGMENT_ID(vram) ((((u32)(vram) & 0x0FF00000) >> 0x14) - 0x10)

/**
 * Entry point of the VS scene: pushes the 'BTLS' pool state, loads the stage and model fragments
 * for the round, and runs the scene of the given kind (VsSceneKind): VsScene_Play before a battle,
 * VsScene_PlayFreeBattleResults or VsScene_PlayTournamentResults after one. For the tournament
 * results the stage is the next round's (round + 1, at most 8).
 * Seen in play (2026-11-14): its calls to VsScene_LoadGeoLayout (VsScene_Run+0x464) and
 * VsScene_PlayFreeBattleResults (VsScene_Run+0x4B0) were caught by breakpoints, before a Free Battle,
 * after one and after a tournament round.
 */
s32 VsScene_Run(s32 kind, SessionContext* session) {
    s32 round;
    s32 sp24;

    D_822036A4 = session;
    round = 0;
    D_822036A4->transitionFlags = 0;

    if (kind == VS_SCENE_PRE_BATTLE) {
        round = D_822036A4->roundOrDemoId;
    } else if (kind == VS_SCENE_TOURNAMENT_RESULTS) {
        round = D_822036A4->roundOrDemoId + 1;
        if (round >= 9) {
            round = 8;
        }
    }

    if (D_822036A4->mode == 0) {
        D_822036A8 = 0;
    } else if (round < 7) {
        D_822036A8 = 1;
    } else if (round == 7) {
        D_822036A8 = 2;
    } else if (round >= 8) {
        D_822036A8 = 3;
    }
    sp24 = round;

    main_pool_push_state('BTLS');
    Save_LoadSram();
    Gfx_InitDisplayListBuffers(0x10000, 0);
    D_82203204 = StageContext_Allocate(0, 1, 3, 1, 2, 1);
    D_82203208 = GfxImage_Allocate(0, 2, 0x140, 0xF0, 1);
    GfxImage_AttachDepthBuffer(D_82203208, D_82203204->renderTargets[0]->depth_p);
    Font_Init(0x2A, 0);
    Asset_LoadToSegment(((u32)D_01000000 & 0x0F000000) >> 0x18, D_002E0BE0, D_002E2B90, 0);
    Fragment_Load(DEMO_FRAGMENT_ID(D_81000000), D_0015B1A0, D_0015E220);
    Fragment_Load(DEMO_FRAGMENT_ID(D_8F200000), D_003553C0, D_0035C390);
    Fragment_Load(DEMO_FRAGMENT_ID(D_8F500000), D_0035C390, D_0035E790);
    Fragment_Load(DEMO_FRAGMENT_ID(D_8F600000), D_0035E790, D_00369F50);
    Fragment_Load(DEMO_FRAGMENT_ID(D_8EB00000), D_00369F50, D_0037B090);

    switch (D_822036A8) {
        case 0:
            Fragment_Load(DEMO_FRAGMENT_ID(D_8F300000), D_00320820, D_00326700);
            break;

        case 1:
            Fragment_Load(DEMO_FRAGMENT_ID(D_8F900000), D_003139C0, D_00317EF0);
            break;

        case 2:
            Fragment_Load(DEMO_FRAGMENT_ID(D_8FA00000), D_00317EF0, D_0031C300);
            break;

        case 3:
            Fragment_Load(DEMO_FRAGMENT_ID(D_8FB00000), D_0031C300, D_00320820);
            break;
    }

    if ((sp24 > 0) && (sp24 < 7)) {
        Fragment_Load(DEMO_FRAGMENT_ID(D_8EC00000), D_0037B090, D_00380D60);
    } else if (sp24 == 7) {
        Fragment_Load(DEMO_FRAGMENT_ID(D_8ED00000), D_00380D60, D_00385D60);
    } else if (sp24 == 8) {
        Fragment_Load(DEMO_FRAGMENT_ID(D_8EE00000), D_00385D60, D_0038A540);
    }

    D_82203260 = PokeIcon_AllocFramebuffers(5);
    D_82203264 = (s32)PokeIcon_CreateRenderList(D_82203260, 0xC, 0x40, 0x40);
    D_8220325C = BinArchive_Open(D_002F5940, D_003139C0, 1, 1);
    PokeIcon_OpenModelArchives();
    VsScene_LoadGeoLayout(sp24);
    StageContext_Activate(D_82203204);

    switch (kind) {
        case VS_SCENE_PRE_BATTLE:
            VsScene_Play();
            break;

        case VS_SCENE_FREE_BATTLE_RESULTS:
            VsScene_PlayFreeBattleResults();
            break;

        case VS_SCENE_TOURNAMENT_RESULTS:
            VsScene_PlayTournamentResults();
            break;
    }

    StageContext_Deactivate();
    Display_DisableBlackout();
    Gfx_FreeDisplayListBuffers();
    main_pool_pop_state('BTLS');
    return 0;
}
