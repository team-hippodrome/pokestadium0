/* Stadium Zero fragment012_17ED00. */
/* C ported from the Stadium 1 decomp: src/fragments/battle_engine/battle_engine_309ED0.c, src/fragments/battle_engine/battle_engine_main.c. */

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

#include "fragments/battle_engine/battle_engine.h"
#include "model_animation.h"
#include "model_renderer.h"
#include "audio_commands.h"
#include "3D140.h"
#include "audio_fade.h"
#include "audio_loop_point.h"
#include "cry.h"
#include "matrix.h"
extern s32 pad_D_84390210[4];
extern s32 sMultihitCount;
extern s32 sMultihitCountdown;

s32 Battle_StageGeoDispatchCallback(s32 event, GraphNode* node);
s32 Battle_StageLightAngleCallbackA(s32 event, unk_D_86002F34_alt18* light);
s32 Battle_StageMaterialTintCallback(s32 event, DisplayObject* object);
void Battle_SetStageScale(f32 scale);
void Battle_RenderActivePokemonThumbnail(GraphNode* thumbnail_root, DepthBuffer* thumbnail);
void Battle_DrawTexturedRectSegment(s32 x1, s32 y1, s32 draw_width, s32 height, u8* texture, s32 load_width);
void Battle_FillActivePokemonThumbnail(GraphNode* thumbnail_root, DepthBuffer* thumbnail);
void func_82100CB8(void);
void func_82100CC0(void);
s32 BattleScene_UpdateFrame(s32 fade_mode);
s32 BattleScene_UpdatePausedFrame(s32 fade_mode);
void Battle_CompleteRosterOrder(u8* roster_order, s32 number_of_pokemon_picked);
void BattleScene_InitializeParticipantPresentation(BattleSessionTeams* side, unk_D_86002F30* model);
void func_8210186C(void);

void Battle_DrawStageBackdrop(void);
void Battle_DrawClippedTextureRect(s32 x1, s32 y1, s32 x2, s32 y2);
void Battle_UpdateFaintBatches(void);

// called every frame: bug boy in GLC
// Geo_ProcessNodeChildren invokes render callbacks with event 2.
s32 Battle_StageGeoDispatchCallback(s32 event, GraphNode* node) {
    if (event == 2) {
        BattleAnim_DispatchPresentation(5, &sStageCamera);
    }
    return 0;
}

// called every frame: bug boy in GLC
// Orient the first stage light relative to the current camera's viewing axis.
s32 Battle_StageLightAngleCallbackA(s32 event, unk_D_86002F34_alt18* light) {
    UNUSED s32 pad; // FAKE: stack padding
    f32 distance;
    s16 angle_x;
    s16 angle_y;

    if (event == 2) {
        Vec3f_CalculateDistanceAngles(&D_80060488->view.targetPosition, &D_80060488->view.eyePosition, &distance, &angle_x, &angle_y);
        light->unk_1C = angle_x + 0x2000;
        light->unk_1E = angle_y - 0x2000;
    }
    return 0;
}

// called every frame: bug boy in GLC
// Apply presentation effects to each of the three stage-layout containers.
s32 Battle_StageMaterialTintCallback(s32 event, DisplayObject* object) {
    if (event == 2) {
        Vec3f_SetComponentsDuplicate(&object->scale, sStageScale, sStageScale, sStageScale);
        object->textureTint.rgba = sTintColor.rgba;
    }
    return 0;
}

extern u8 D_8007838C[4];
extern u8 D_82198D28[];

/**
 * Stores the RGB tint applied to the battle stage.
 * @unverified Name from the header prototype; comment guessed from the code.
 */
void Battle_SetStageTintColor(u8 r, u8 g, u8 b) {
    D_82198D28[0] = r;
    D_82198D28[1] = g;
    D_82198D28[2] = b;
}

// Called at the start of battles
// Uniform scale consumed by the stage material callbacks, not the Pokemon models.
void Battle_SetStageScale(f32 scale) {
    sStageScale = scale;
}

extern s32 D_82198D1C;
extern u8 D_8F908980[];
extern u8 D_8FA08900[];
extern u8 D_8FB08900[];
extern Gfx D_80060398[];

/**
 * called every frame: bug boy in GLC
 * Archive entry 2 returns a tagged backdrop value: NULL clears depth, -1 fills
 * black, a value below 0x10000 is RGBA5551, and larger values address a texture.
 * The 4 x 64 RGBA32 texture stretches over the upper half; its last row fills below.
 * @unverified Name was previously used only by callers of this address; the definition was still func_. Comment from Stadium 1.
 */
void Battle_DrawStageBackdrop(void) {
    void* tex;
    s16 left;
    s16 right;
    s16 top;
    s16 middle;
    s16 bottom;
    s16 texture_step_y;

    if ((D_82198D1C > 0) && (sStageScale == 1.0f)) {
        left = sStageCamera.viewport.x;
        right = sStageCamera.viewport.width + left;
        top = sStageCamera.viewport.y;
        middle = (sStageCamera.viewport.height / 2) + top;
        bottom = sStageCamera.viewport.height + top;
        texture_step_y = 0x10000 / (sStageCamera.viewport.height / 2);

        switch (D_82198D1C) {
            case 1: tex = Memmap_GetFragmentVaddr(D_8F908980); break;
            case 2: tex = Memmap_GetFragmentVaddr(D_8FA08900); break;
            case 3: tex = Memmap_GetFragmentVaddr(D_8FB08900); break;
        }

        if ((sStageCamera.viewport.width < 0x140) || (sStageCamera.viewport.height < 0xF0)) {
            GfxImage_FillCurrent(&gDisplayListHead, 1);
        } else {
            GfxImage_ClearDepthRectangle(&gDisplayListHead, 0, 0, 0x140, 0xF0);
        }

        gDPSetCycleType(gDisplayListHead++, G_CYC_1CYCLE);
        gDPSetTexturePersp(gDisplayListHead++, G_TP_NONE);
        gDPSetCombineMode(gDisplayListHead++, G_CC_MODULATEI_PRIM, G_CC_MODULATEI_PRIM);
        gDPSetPrimColor(gDisplayListHead++, 0, 0, sTintColor.r, sTintColor.g, sTintColor.b, 255);
        gSPClearGeometryMode(gDisplayListHead++, G_ZBUFFER | G_LIGHTING);
        gDPLoadTextureBlock(gDisplayListHead++, tex, G_IM_FMT_RGBA, G_IM_SIZ_32b, 4, 64, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        gSPTextureRectangle(gDisplayListHead++, left << 2, top << 2, right << 2, middle << 2, G_TX_RENDERTILE, 0, 0, 0, texture_step_y);
        gSPTextureRectangle(gDisplayListHead++, left << 2, middle << 2, right << 2, bottom << 2, G_TX_RENDERTILE, 0, 0x07E0, 0, 0);
        gSPDisplayList(gDisplayListHead++, D_80060398);
        return;
    }
    GfxImage_FillCurrent(&gDisplayListHead, 1);
}

/*
    Makes and Freezes the thumbnail of active pokemon
*/
// Capture only when camera flag 0x10 requests a refresh. Restoring the viewport
// keeps the camera's on-screen placement separate from its off-screen render size.
void Battle_RenderActivePokemonThumbnail(GraphNode* thumbnail_root, DepthBuffer* thumbnail) {
    CameraNode* camera_node = thumbnail_root->children;
    CameraViewport viewport;

    if (camera_node->node.flags & 0x10) {
        viewport = camera_node->viewport;

        camera_node->viewport.x = 0;
        camera_node->viewport.y = 0;
        camera_node->viewport.width = 76;
        camera_node->viewport.height = 76;

        GfxImage_SetRenderTarget(&gDisplayListHead, thumbnail);
        GfxImage_FillCurrent(&gDisplayListHead, 0x10D);
        Geo_RenderRootNode(thumbnail_root);

        camera_node->node.flags &= ~0x10;

        camera_node->viewport = viewport;
    }
}

s32 func_80006B50(s32 *, s32 *, s32 *, s32 *);
/**
 * called every frame: bug boy in GLC
 * Use clipped destination offsets as 10.5 texture coordinates with a half-texel bias.
 * @src/gfx_rect.c
 * @unverified Name was previously used only by callers of this address; the definition was still func_. Comment from Stadium 1.
 */
void Battle_DrawClippedTextureRect(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 x0 = arg0;
    s32 y0 = arg1;

    if (func_80006B50(&arg0, &arg1, &arg2, &arg3) != 0) {
        x0 = ((arg0 - x0) << 5) + 16;
        y0 = ((arg1 - y0) << 5) + 16;
        gSPTextureRectangle(gDisplayListHead++, arg0 << 2, arg1 << 2, (arg2 + 1) << 2, (arg3 + 1) << 2,
                            G_TX_RENDERTILE, x0, y0, 0x800, 0x800);
    }
}

// called every frame: bug boy in GLC
// Load full-width source rows and draw at half size using the clipped rectangle helper.
void Battle_DrawTexturedRectSegment(s32 x1, s32 y1, s32 draw_width, s32 height, u8* texture, s32 load_width) {
    gDPLoadTextureBlock(gDisplayListHead++, texture, G_IM_FMT_RGBA, G_IM_SIZ_16b, load_width, (height * 2) + 2, 0,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                        G_TX_NOLOD);

    Battle_DrawClippedTextureRect(x1, y1, (x1 + draw_width) - 1, (y1 + height) - 1);
}

/*
    Fills in the texture of the pokemon thumbnail
*/
// Blit the captured side image as four strips, producing a 37 x 37 thumbnail.
void Battle_FillActivePokemonThumbnail(GraphNode* thumbnail_root, DepthBuffer* thumbnail) {
    s32 x;
    s32 y;
    CameraNode* camera_node = thumbnail_root->children;
    CameraViewport* viewport = &thumbnail_root->children->viewport;
    s32 image_address;

    x = viewport->x;
    y = viewport->y;

    camera_node++;

    gDPPipeSync(gDisplayListHead++);

    gDPSetCycleType(gDisplayListHead++, G_CYC_1CYCLE);
    gDPSetRenderMode(gDisplayListHead++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
    gDPSetCombineMode(gDisplayListHead++, G_CC_DECALRGBA, G_CC_DECALRGBA);
    gDPSetTexturePersp(gDisplayListHead++, G_TP_NONE);
    gDPSetTextureFilter(gDisplayListHead++, G_TF_AVERAGE);

    image_address = thumbnail->img_p;
    Battle_DrawTexturedRectSegment(x, y, 37, 10, image_address, 76);
    image_address = thumbnail->img_p + 0xBE0;
    Battle_DrawTexturedRectSegment(x, y + 10, 37, 10, image_address, 76);
    image_address = thumbnail->img_p + 0x17C0;
    Battle_DrawTexturedRectSegment(x, y + 20, 37, 10, image_address, 76);
    image_address = thumbnail->img_p + 0x23A0;
    Battle_DrawTexturedRectSegment(x, y + 30, 37, 7, image_address, 76);

    gDPPipeSync(gDisplayListHead++);

    gDPSetTexturePersp(gDisplayListHead++, G_TP_PERSP);
    gDPSetTextureFilter(gDisplayListHead++, G_TF_BILERP);
}

/**
 * Clear the faint-batch stamps for every picked Pokemon, including teammate rosters.
 * BattleMon.unk_25 is written by Battle_UpdateFaintBatches when its current HP reaches zero.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void Battle_ResetFaintBatches(void) {
    s32 side_index;
    s32 trainer_index;
    s32 pokemon_index;
    TeamRoster* roster;
    BattleSessionTeams* side = &sBattleSides[0];

    for (side_index = 0; side_index < 2; side_index++, side++) {
        for (trainer_index = 0; trainer_index < side->tagTeamSize; trainer_index++) {
            roster = side->teamMember[trainer_index];
            for (pokemon_index = 0; pokemon_index < roster->numberOfPokemonBrought; pokemon_index++) {
                roster->pokemonPicked[pokemon_index].unk_25 = 0;
            }
        }
    }
}

/**
 * called every frame: bug boy in GLC
 * Stamp newly observed zero-HP Pokemon with the same batch number this frame.
 * Increment once per nonempty batch, so simultaneous faints share a stamp.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void Battle_UpdateFaintBatches(void) {
    s32 side_index;
    s32 trainer_index;
    s32 pokemon_index;
    s32 found_faint = 0;
    TeamRoster* roster;
    BattleSessionTeams* side = &sBattleSides[0];

    for (side_index = 0; side_index < 2; side_index++, side++) {
        for (trainer_index = 0; trainer_index < side->tagTeamSize; trainer_index++) {
            roster = side->teamMember[trainer_index];
            for (pokemon_index = 0; pokemon_index < roster->numberOfPokemonBrought; pokemon_index++) {
                if ((roster->pokemonPicked[pokemon_index].unk_25 == 0) && (roster->pokemonPicked[pokemon_index].hp == 0)) {
                    found_faint = 1;
                    roster->pokemonPicked[pokemon_index].unk_25 = sNextFaintBatch;
                }
            }
        }
    }

    if (found_faint != 0) {
        sNextFaintBatch += 1;
    }
}

// Empty retail hook; its intended purpose is not established.
void func_82100CB8(void) {
}

// Empty retail hook; no purpose is established by callers in this fragment.
void func_82100CC0(void) {
}

// called every frame: bug boy in GLC
// Advance simulation/presentation, capture dirty thumbnails, then draw the scene and UI.
s32 BattleScene_UpdateFrame(s32 fade_mode) {
    s32 battle_result;

    GeoRender_AdvanceFrameCounter();
    ModelAnim_UpdateFrameChangeState();
    BattleScene_DispatchLifecycle(2, sBattleSides);
    BattleThumbnail_DispatchOwnerCameraLifecycle(2, &sSide1ThumbnailCamera, &sSide2ThumbnailCamera);
    battle_result = BattleScene_Dispatch(2, &sStageCamera);
    BattleAnim_DispatchPresentation(2, &sStageCamera);
    Battle_RenderActivePokemonThumbnail(sSide1ThumbnailRoot, sSide1PokemonThumbnail);
    Battle_RenderActivePokemonThumbnail(sSide2ThumbnailRoot, sSide2PokemonThumbnail);
    BgStage_DrawFrame();
    Battle_DrawStageBackdrop();
    Geo_RenderRootNode(sStageRoot);
    BattleScene_DispatchLifecycle(5, sBattleSides);
    Battle_FillActivePokemonThumbnail(sSide1ThumbnailRoot, sSide1PokemonThumbnail);
    Battle_FillActivePokemonThumbnail(sSide2ThumbnailRoot, sSide2PokemonThumbnail);
    Battle_UpdateFaintBatches();

    if (battle_result == 1) {
        sBattleSides[0].unk_1C = 1;
    }

    if (battle_result == 2) {
        sBattleSides[1].unk_1C = 1;
    }

    return battle_result;
}

/*
    No idea what the hell this is, it's not drawing the Run selection cursor and nothing else in battle would use START
    Stadium doesn't have pausing so it's not that either
    preliminary guess: unused pausing debug option, sIsPaused can never be 1 through the current code
*/
// Dormant frame-step path: this translation unit initializes the selector to zero
// and never sets it to one. A steps and Start resumes only while fade_mode is zero.
s32 BattleScene_UpdatePausedFrame(s32 fade_mode) {
    s32 battle_result = 0;

    if ((fade_mode == 0) && BTN_IS_PRESSED(gPlayer1Controller, BTN_A)) {
        battle_result = BattleScene_UpdateFrame(fade_mode);
    } else {
        ModelAnim_UpdateFrameChangeState();
        BgStage_DrawFrame();
        Battle_DrawStageBackdrop();
        Geo_RenderRootNode(sStageRoot);
        BattleScene_DispatchLifecycle(5, sBattleSides);
        Battle_FillActivePokemonThumbnail(sSide1ThumbnailRoot, sSide1PokemonThumbnail);
        Battle_FillActivePokemonThumbnail(sSide2ThumbnailRoot, sSide2PokemonThumbnail);
    }

    if ((fade_mode == 0) && BTN_IS_PRESSED(gPlayer1Controller, BTN_START)) {
        sIsPaused = 0;
    }
    return battle_result;
}

extern SessionContext* D_82198D10;
extern s32 D_82198D30;
extern u8 D_82198D24;
extern u8* D_800603C0;
s32 func_800010B8(void);
s32 func_8003BF40(u8*);
void func_8000D304(void);
/**
 * triggers every frame: bug boy in GLC
 * Count the initial two callbacks toward zero; once the gate is zero, the attract
 * demo battle (mode 16) can request exit on a button press. The normal path waits for the scene result.
 * @unverified Name was previously used only by callers of this address; the definition was still func_. Comment from Stadium 1.
 */
void Battle_UpdateCompletionGate(void) {
    u8 sp1F;
    if (D_82198D30 < 0) {
        D_82198D30++;
    } else if (D_82198D30 == 0) {
        if (D_82198D10->mode == 5) {
            if (*(u16*)(D_800603C0 + 8) != 0) {
                D_82198D30 = 1;
            }
        } else if (D_82198D10->mode == 3) {
            if (*(u16*)(D_800603C0 + 8) != 0) {
                D_82198D30 = 1;
            } else if (func_800010B8() != 0) {
                if (func_8003BF40(&sp1F) != 8) {
                    sp1F &= 1;
                    if ((sp1F ^ D_82198D24) & D_82198D24) {
                        func_8000D304();
                        D_82198D30 = 1;
                    }
                    D_82198D24 = sp1F;
                }
            }
        }
    }
}

extern SessionContext* D_82198D10;
void func_8000A7FC(s32);

/**
 * triggers every frame: bug boy in GLC
 * BgStage_WaitForCondition passes the current fade mode and starts the exit fade
 * after a nonzero return. Latch 2 prevents repeating the audio shutdown request.
 * @src/stage_loader.c
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
s32 Battle_FrameCallback(s32 fade_mode) {
    s32 battle_result = 0;

    Cont_StartReadInputs();
    Trainer_RequestPokeIcon(&sBattleSides[0]);
    PokeIcon_WaitFrameLoadForObject(&sBattleSides[0]);
    Trainer_RequestPokeIcon(&sBattleSides[1]);
    PokeIcon_WaitFrameLoadForObject(&sBattleSides[1]);
    Cont_ReadInputs();
    Input_ResetRepeatState();

    switch (sIsPaused) {
        case 0:
            battle_result = BattleScene_UpdateFrame(fade_mode);
            break;

        case 1:
            battle_result = BattleScene_UpdatePausedFrame(fade_mode);
            break;
    }

    if ((battle_result != 0) && (sCompletionGate <= 0)) {
        sCompletionGate = 1;
    }

    Battle_UpdateCompletionGate();
    PokeIcon_RequestBackgroundForObject(&sBattleSides[0]);
    PokeIcon_RequestBackgroundForObject(&sBattleSides[1]);

    if ((fade_mode != 2) && (sCompletionGate == 1)) {
        sCompletionGate = 2;
        AudioFrameUpdate(0);
        if (D_82198D10->mode != 4) {
            func_8000A7FC(0x1E);
        }
        return 1;
    }
    return 0;
}

// triggers on battle start: bug boy in glc
// Preserve the picked prefix and append missing roster indices 0..5 in order.
// This completes the copy order; it does not choose additional battle participants.
void Battle_CompleteRosterOrder(u8* roster_order, s32 number_of_pokemon_picked) {
    s32 roster_index;
    s32 picked_index;

    for (roster_index = 0; roster_index < 6; roster_index++) {
        for (picked_index = 0; picked_index < number_of_pokemon_picked; picked_index++) {
            if (roster_index == roster_order[picked_index]) {
                break;
            }
        }

        if (picked_index == number_of_pokemon_picked) {
            roster_order[number_of_pokemon_picked++] = roster_index;
        }
    }
}

extern u8 D_82189170[];
extern u8 D_82189174[];
void BattleAi_SelectTeam(TeamRoster*, TeamRoster*, s32, u8*, s32);

/**
 * triggers on battle start: bug boy in glc
 * Ask the COM selection routine for the picked prefix, then copy the brought
 * roster in that order. numberOfPokemonChosen keeps only the prefix length.
 * @src/fragments/battle_engine/battle_engine_com_decision_logic.c
 * Seen in play (2026-11-12): ran once when 1P confirmed its order for a COM free battle, before
 * the first send-out; COM then brought Pinsir (カイのすけ), Gengar (ゲンのすけ) and Pikachu (ピカのすけ) in that
 * order.
 */
void Battle_SelectComRoster(void) {
    UNUSED s32 pad; // FAKE: stack padding
    u8 order_of_picked_pokemon[8];
    s32 difficulty;
    TeamRoster* com_roster;
    TeamRoster* player_roster;
    s32 number_of_pokemon_picked;
    s32 i;


    player_roster = *(TeamRoster**)((u8*)D_82198D10 + 0x103C);
    com_roster = *(TeamRoster**)((u8*)D_82198D10 + 0x1064);
    switch (D_82198D10->mode) {
        case 0:
            difficulty = D_82189170[D_82198D10->ruleCategory];
            break;
        case 1:
            difficulty = 0;
            break;
        case 2:
            difficulty = D_82189174[D_82198D10->modeSelection];
            break;
    }

    if (com_roster->isHuman & 2) {
        number_of_pokemon_picked = com_roster->rosterInfo->numberOfPokemonCanBePicked;
        if (player_roster->numberOfPokemonBrought < number_of_pokemon_picked) {
            number_of_pokemon_picked = player_roster->numberOfPokemonBrought;
        }
        BattleAi_SelectTeam(player_roster, com_roster, difficulty, order_of_picked_pokemon, number_of_pokemon_picked);
        Battle_CompleteRosterOrder(order_of_picked_pokemon, number_of_pokemon_picked);
        com_roster->numberOfPokemonBrought = number_of_pokemon_picked;

        for (i = 0; i < com_roster->rosterInfo->numberOfPokemonCanBePicked; i++) {
            com_roster->pokemonPicked[i] = com_roster->rosterInfo->battleMon[order_of_picked_pokemon[i]];
        }
    }
}

// triggers at the start of battle: bug boy in glc
// Seed icon/presentation state from the side's first trainer and first picked Pokemon.
void BattleScene_InitializeParticipantPresentation(BattleSessionTeams* side, unk_D_86002F30* model) {
    TeamRoster* first_trainer = side->teamMember[0];

    side->unk_18 = model->unk_08->unk_00[0];
    side->uniqueStatusFlags |= 0xA0;
    side->unk_1C = 0;
    side->displayModel = first_trainer->pokemonPicked[0].species.id;
    side->unk_04 = first_trainer->pokemonPicked;
    Trainer_RequestPokeIcon(side);
}

typedef struct Unit82101324 {
    /* 0x00 */ char unk00[0x10];
    /* 0x10 */ ModelLoadContext* framebuffers;
    /* 0x14 */ char unk14[0x14];
} Unit82101324; // size = 0x28

extern Unit82101324* D_82198D14;
extern s32 D_82198D1C;
extern s32 D_82198D20;
extern s32 D_82198D18;
extern DepthBuffer* D_82198CFC;
extern DepthBuffer* D_82198D00;
extern DepthBuffer* D_82198D04;
extern u8* D_82198D08;
extern u8* D_82198D0C;
extern GraphNode* D_82198CF0;
extern GraphNode* D_82198CF4;
extern GraphNode* D_82198CF8;
extern CameraNode D_82198A20;
extern CameraNode D_82198B10;
extern CameraNode D_82198C00;
extern u8 D_82188DD0[];
extern u8 D_82188E90[];
extern u8 D_82188F50[];
extern u8 D_82189010[];
extern u8 D_821890D0[];
extern u8 D_82189120[];
extern u8 D_81000000[];
extern u8 D_8F300000[];
extern u8 D_8F900000[];
extern u8 D_8FA00000[];
extern u8 D_8FB00000[];
extern u8 D_01000000[];
extern u8 D_03000000[];
extern u8 D_0015B1A0[];
extern u8 D_0015E220[];
extern u8 D_002E0BE0[];
extern u8 D_002E2B90[];
extern u8 D_003F53F0[];
extern u8 D_003FC1A0[];
extern u8 D_00320820[];
extern u8 D_00326700[];
extern u8 D_003139C0[];
extern u8 D_00317EF0[];
extern u8 D_0031C300[];
s32 Font_Init(s32 load_size, s32 side);
s32 func_800040B4(s32, u8*, u8*);
void func_82101178(void);
void func_821012D8(Unit82101324*, unk_D_86002F30*);
void func_82100B84(void);
void func_821070E0(s32, Unit82101324*);
void func_821076FC(s32, CameraNode*, CameraNode*);
void func_82134CC0(s32, CameraNode*);
void func_821370DC(s32, CameraNode*);

s32 func_82101324(s32* arg0) { // FAKE: s32 return (value unused) fixes caller regalloc
    UNUSED s32 pad; // FAKE
    MemoryBlock* block;
    unk_D_86002F30* model;

    Battle_SetStageTintColor(0xFF, 0xFF, 0xFF);
    Battle_SetStageScale(1.0f);
    if (D_82198D10->mode == 4) {
        Font_Init(4, 0);
    } else {
        Font_Init(3, 0);
    }
    D_82198D14[0].framebuffers = PokeIcon_AllocFramebuffers(3);
    D_82198D14[1].framebuffers = PokeIcon_AllocFramebuffers(3);
    PokeIcon_OpenModelArchives();
    D_82198CFC = main_pool_alloc(0x10, 0);
    GfxImage_Initialize(D_82198CFC, 0, 2, 0x4C, 0x4C, ((s32**)((s32**)arg0)[6])[3][2]);
    D_82198D00 = GfxImage_Allocate(0, 2, 0x4C, 0x4C, 0);
    D_82198D04 = GfxImage_Allocate(0, 2, 0x4C, 0x4C, 0);
    GfxImage_AttachDepthBuffer(D_82198D00, D_82198CFC);
    GfxImage_AttachDepthBuffer(D_82198D04, D_82198CFC);
    D_82198D08 = D_82198D00->img_p;
    D_82198D0C = D_82198D04->img_p;
    func_800040B4(((u32)((s32)D_81000000 & 0x0FF00000) >> 0x14) - 0x10, D_0015B1A0, D_0015E220);
    Asset_LoadToSegment((u32)((s32)D_01000000 & 0x0F000000) >> 0x18, D_002E0BE0, D_002E2B90, 0);
    Asset_LoadToSegment((u32)((s32)D_03000000 & 0x0F000000) >> 0x18, D_003F53F0, D_003FC1A0, 0);
    switch (D_82198D1C) {
        case 0:
            func_800040B4(((u32)((s32)D_8F300000 & 0x0FF00000) >> 0x14) - 0x10, D_00320820, D_00326700);
            break;
        case 1:
            func_800040B4(((u32)((s32)D_8F900000 & 0x0FF00000) >> 0x14) - 0x10, D_003139C0, D_00317EF0);
            break;
        case 2:
            func_800040B4(((u32)((s32)D_8FA00000 & 0x0FF00000) >> 0x14) - 0x10, D_00317EF0, D_0031C300);
            break;
        case 3:
            func_800040B4(((u32)((s32)D_8FB00000 & 0x0FF00000) >> 0x14) - 0x10, D_0031C300, D_00320820);
            break;
    }
    model = Model_LoadByArchiveIndex(0x99);
    func_82101178();
    func_821012D8(&D_82198D14[0], model);
    func_821012D8(&D_82198D14[1], model);
    func_82100B84();
    GeoNode_CreateCamera(NULL, &D_82198A20, 0, 0, 0x140, 0xF0);
    GeoNode_CreateCamera(NULL, &D_82198B10, 0x1E, 0x50, 0x4C, 0x4C);
    GeoNode_CreateCamera(NULL, &D_82198C00, 0xE2, 0x50, 0x4C, 0x4C);
    GeoCamera_SetPerspective(&D_82198A20, 30.0f, 192.0f, 24576.0f);
    ModelRenderer_InitDisplayRoots();
    func_821070E0(0, D_82198D14);
    func_821076FC(0, &D_82198B10, &D_82198C00);
    func_82134CC0(0, &D_82198A20);
    func_821370DC(0, &D_82198A20);
    block = MainPool_AllocState(main_pool_get_available(), 0);
    switch (D_82198D1C) {
        case 0:
            D_82198CF0 = process_geo_layout(block, D_82188DD0);
            break;
        case 1:
            D_82198CF0 = process_geo_layout(block, D_82188E90);
            break;
        case 2:
            D_82198CF0 = process_geo_layout(block, D_82188F50);
            break;
        case 3:
            D_82198CF0 = process_geo_layout(block, D_82189010);
            break;
    }
    D_82198CF4 = process_geo_layout(block, D_821890D0);
    D_82198CF8 = process_geo_layout(block, D_82189120);
    MainPool_FinalizeAllocation(block);
    func_821070E0(3, D_82198D14);
    func_821076FC(3, &D_82198B10, &D_82198C00);
    func_82134CC0(3, &D_82198A20);
    func_821370DC(3, &D_82198A20);
    D_82198D20 = 1;
    D_82198D18 = 0;
}

void func_8210186C(void) {
}

extern s32 D_82198D1C;
extern u8 D_82198D24;
void Audio_PlayMusicIfChanged(s32);
s32 Storage_GetDiskStatus(void);
void Audio_SetDiskReadyPolling(s32);
void Audio_WaitForIdle(s32);
s32 func_82101324(s32* arg0); // FAKE: see definition
s32 func_82101874(s32 arg0, SessionContext *arg1)
{
  StageContext *stage_context;
  SessionContext *new_var2; // FAKE
  SessionContext *ctx;
  int new_var; // FAKE
  ctx = (D_82198D10 = arg1);
  sBattleSides = (BattleSessionTeams *) (((u8 *) arg1) + 0x1034);
  sCompletionGate = -2;
  new_var2 = ctx; // FAKE
  if (ctx->mode == 0)
  {
    D_82198D1C = 0;
  }
  else
    if (ctx->roundOrDemoId < 7)
  {
    D_82198D1C = 1;
  }
  else
    if (new_var2->roundOrDemoId == 7)
  {
    D_82198D1C = 2;
  }
  else
    if (ctx->roundOrDemoId == 8)
  {
    D_82198D1C = 3;
  }
  main_pool_push_state('BATL');
  Gfx_InitDisplayListBuffers(0x20000, 0);
  stage_context = StageContext_Allocate(0, 1, 3, 1, 2, 1);
  func_82101324((s32*)stage_context);
  switch (D_82198D10->mode)
  {
    case 3:
      Audio_PlayMusicIfChanged(1);
      if (Storage_GetDiskStatus() != 0)
    {
      D_82198D24 = 0;
      Audio_SetDiskReadyPolling(1);
    }
      break;

    case 4:
      Audio_PlayMusicIfChanged(8);
      break;

    case 6:
      Audio_PlayMusicIfChanged(0xB);
      break;

    default:
      Audio_PlayMusicIfChanged(0x32);
      break;

  }

  StageContext_Activate(stage_context);
  new_var = 1; // FAKE
  StageLoader_RunFrames(new_var);
  BgStage_WaitForCondition(Battle_FrameCallback, 0x20, 0x10);
  StageLoader_RunFrames(2);
  switch (D_82198D10->mode)
  {
    case 3:
      if (Storage_GetDiskStatus() != 0)
    {
      Audio_SetDiskReadyPolling(2);
    }
      Audio_WaitForIdle(1);
      break;

    case 4:
      StageLoader_RunFrames(0x1E);
      break;

    case 5:
      StageLoader_RunFrames(0xF);
      Audio_WaitForIdle(1);
      break;

    case 6:
      StageLoader_RunFrames(0x1E);
      Audio_WaitForIdle(1);
      break;

  }

  StageContext_Deactivate();
  Gfx_FreeDisplayListBuffers();
  main_pool_pop_state('BATL');
  return 0;
}
