/* Stadium Zero fragment010_17BE70. */
/* C ported from the Stadium 1 decomp: src/fragments/pikachu_reward/pikachu_reward.c, src/game_state.c. */

/*
 * The Surfing Pikachu reward. VsScene queues this fragment (transitionFlags 0x20) after a tournament
 * win with a Game Boy team that brought a Pikachu without Surf. The scene congratulates the player,
 * offers Surf, lets them forget a move if Pikachu knows four, and writes the edited Pikachu back to
 * the Game Boy cartridge's party.
 *
 * Seen in play (2026-11-14, pj64-pokestadium-debug, a crafted Pocket Monsters Green save whose party
 * is one L50 Pikachu knowing ThunderShock, Growl, Thunder Wave and Flash; the post-round
 * transitionFlags were set to 0x21 after an L50-55 tournament round): every function in this file
 * hit a breakpoint. Picking Flash in the forget list played the error sound and stayed in the list,
 * picking Growl showed 「ピカチュウは なきごえの つかいかたを きれいに わすれた！」, and the cartridge
 * save afterwards held Surf (0x39, PP 15) in Growl's slot. Answering no twice showed
 * 「ピカチュウに なみのりを おぼえさせませんでした。」.
 */

#include "pikachu_reward.h"
#include "display_object_textures.h"
#include "font.h"
#include "gb_save.h"
#include "geo_layout.h"
#include "game_state.h"
#include "geo_render.h"
#include "gfx_buffer.h"
#include "graphics_textures.h"
#include "input.h"
#include "main_pool.h"
#include "matrix.h"
#include "memory_main.h"
#include "model_renderer.h"
#include "pokemon_stats.h"
#include "ui_graphics.h"
#include "util.h"

// Declared here instead of in a header: the callers of these disagree on their types.
void MainPool_FinalizeAllocation(struct MemoryBlock* block);
extern GraphNode* sSceneRootNode;
extern GraphNode* sQuestionMarkGeo;
extern unk_D_86002F30* sPikachuModel;
extern DisplayObject sSceneObjects[4];
extern unk_D_832025C8 sNextArrowBlink;
extern s32 sQuestionMarkTimer;
extern char* sShownText;
extern u32 sSceneGeoLayout[];

#include "functions.h"
#include "lib/ultralib/include/PR/os_internal_reg.h"
extern u16 D_8006BBB0[16][256];
extern s32 pad_D_80075660;
extern s32 pad_D_80075664;
extern s32 gCurrentGameState;
extern s32 gLastGameState;
extern s32 pad_D_80075670;
extern s16 gActiveGbPort;
extern s16 gActiveGbPortChanged;
extern unk_D_800AE520 D_800AF990;
extern s32 pad_D_800AE534[2];
extern SessionContext gSessionContext;

#include "m2c_macros.h"

s32 PikachuReward_SpinSunburst(s32 stage, DisplayObject* sunburst);
void Controller_PollInputs(void);
void PikachuReward_UpdateQuestionMarks(void);
s32 PikachuReward_RenderFrame(u8 unused);
void PikachuReward_DrawTextBoxPanel(s16 x, s16 y, s16 width, s16 height);
void PikachuReward_DrawSelectionCursor(s16 x, s16 y);
void PikachuReward_ShowTextForFrames(char* text, s32 frames);
void PikachuReward_ScrollTextIn(s8* text);
void PikachuReward_PlayIntroCamera(void);
void PikachuReward_SetupQuestionMarkModel(DisplayObject* mark, s16 x, s16 y, s16 rotation_z);
void PikachuReward_SetupScene(void);

void PikachuReward_UpdatePikachuAnimation(void);

/**
 * Geo callback of the scene's sunburst background: at stage 2 it spins the sunburst and keeps it
 * centered 70 units above Pikachu. Stubbing it in play stopped the rays from turning.
 */
s32 PikachuReward_SpinSunburst(s32 stage, DisplayObject* sunburst) {
    if (stage == 2) {
        sunburst->rotation.z -= 0x80;
        sunburst->position.x = sSceneObjects->position.x;
        sunburst->position.y = sSceneObjects->position.y + 70.0f;
    }
    return 0;
}

extern s32 sPartyCount;
extern BattleMon sPartyMons[];
extern BattleMon* sPikachuPartyMon;

/**
 * Reads the party of the Game Boy cartridge in `gb_port` and points sPikachuPartyMon at its first
 * Pikachu. Returns 1 when there is one, else 0 (and the scene is skipped).
 */
s32 PikachuReward_FindPikachuInCartParty(s32 gb_port) {
    s32 i;
    DeckHandle* handle;

    if ((gb_port != -1) && (GbSave_EnsureMainDataLoaded(gb_port) != 0)) {
        handle = Deck_Open(0x20, gb_port, 0, 0);
        sPartyCount = Deck_ReadEntries((u8*)sPartyMons, 6, handle);
        Deck_CloseAndFlush(handle);
        for (i = 0; i < sPartyCount; i++) {
            if (sPartyMons[i].species.id == 0x19) {
                sPikachuPartyMon = &sPartyMons[i];
                return 1;
            }
        }
    }
    return 0;
}

/** Returns how many moves Pikachu knows (the filled move slots before the first empty one). */
s32 PikachuReward_CountKnownMoves(void) {
    s32 count;
    s8 *move;

    move = (s8*)sPikachuPartyMon;
    count = 0;
loop_1:
    if (M2C_FIELD(move, u8 *, 9) != 0) {
        count += 1;
        move += 1;
        if (count != 4) {
            goto loop_1;
        }
    }
    return count;
}

/** Starts and finishes a controller read. */
void Controller_PollInputs(void) {
    Cont_StartReadInputs();
    Cont_ReadInputs();
    Input_ResetRepeatState();
}

extern s32 sHidePikachuWhenAnimDone;
/**
 * Updates Pikachu's model each frame: replays event track 0xA every 60 frames unless animation 5 or
 * 9 is playing, and when an animation ends either hides Pikachu (once an ending has started) or
 * returns to the idle animation 0.
 */
void PikachuReward_UpdatePikachuAnimation(void) {
    static s32 D_83202004 = 0;

    if ((sSceneObjects[0].transformAnim.animationId != 0x9) && (sSceneObjects[0].transformAnim.animationId != 5)) {
        D_83202004++;
        if (D_83202004 == 0x3C) {
            D_83202004 = 0;
            ModelAnim_SetEventTrack(&sSceneObjects[0], -1);
            ModelAnim_SetEventTrack(&sSceneObjects[0], 0xA);
        }
    }

    if ((sSceneObjects[0].transformAnim.animationId != 0) && (ModelAnim_IsFinished(&sSceneObjects[0]) != 0)) {
        if (sHidePikachuWhenAnimDone != 0) {
            sSceneObjects[0].node.flags &= ~1;
        } else {
            ModelAnim_SetAnimation(&sSceneObjects[0], 0);
        }
    }
}

/**
 * Pops up the three blue question marks over Pikachu's head while it forgets a move, one every 8
 * frames from sQuestionMarkTimer 0, and hides them again from frame 70. A timer of -1 hides them all.
 * Seen in play during 「１ ２ の ・・・ ポカン！」.
 */
void PikachuReward_UpdateQuestionMarks(void) {
    if (sQuestionMarkTimer == -1) {
        sSceneObjects[1].node.flags &= ~1;
        sSceneObjects[2].node.flags &= ~1;
        sSceneObjects[3].node.flags &= ~1;
        return;
    }

    switch (sQuestionMarkTimer) {
        case 0x0:
            sSceneObjects[1].node.flags |= 1;
            break;

        case 0x8:
            sSceneObjects[2].node.flags |= 1;
            break;

        case 0x10:
            sSceneObjects[3].node.flags |= 1;
            break;

        case 0x46:
            sSceneObjects[1].node.flags &= ~1;
            break;

        case 0x4E:
            sSceneObjects[2].node.flags &= ~1;
            break;

        case 0x56:
            sSceneObjects[3].node.flags &= ~1;
            break;
    }

    if (sQuestionMarkTimer < 0x57) {
        sQuestionMarkTimer++;
    }
}

/** Renders one frame of the Pikachu reward scene. */
s32 PikachuReward_RenderFrame(u8 unused) {
    GeoRender_AdvanceFrameCounter();
    PikachuReward_UpdatePikachuAnimation();
    PikachuReward_UpdateQuestionMarks();
    BgStage_DrawFrame();
    GfxImage_FillCurrent(&gDisplayListHead, 1);
    Geo_RenderRootNode(sSceneRootNode);
    return 0;
}

/** Draws the ▼ "press A" arrow at the text box's corner, fading it in and out over 61 frames. */
void PikachuReward_DrawBlinkingNextArrow(s16 x, s16 y) {
    s32 alpha;

    if (sNextArrowBlink.unk_00 < 0x10) {
        alpha = sNextArrowBlink.unk_00 * 0x10;
    } else if (sNextArrowBlink.unk_00 < 0x23) {
        alpha = 0xFF;
    } else if (sNextArrowBlink.unk_00 < 0x32) {
        alpha = (-sNextArrowBlink.unk_00 * 0x10) + 0x320;
    } else {
        alpha = 0;
    }

    sNextArrowBlink.unk_00++;
    if (sNextArrowBlink.unk_00 >= 0x3D) {
        sNextArrowBlink.unk_00 = 0;
    }

    Gfx_SetEnvColor(0xFF, 0xFF, 0xFF, alpha);
    Font_DrawCharAt(x, y, 0x2177);
}

/** Draws a blue gradient panel, the background of the text box and the menus. */
void PikachuReward_DrawTextBoxPanel(s16 x, s16 y, s16 width, s16 height) {
    Color_RGB8 sp24 = { 0x00, 0x00, 0x32 }; // #000032
    Color_RGB8 sp20 = { 0x00, 0x00, 0xC8 }; // #0000C8

    Ui_DrawGradientPanel(x, y, width, height, &sp24, &sp20);
}

/** Draws the pointing-hand selection cursor. */
void PikachuReward_DrawSelectionCursor(s16 x, s16 y) {
    gSPDisplayList(gDisplayListHead++, D_80060290);

    Gfx_DrawTextureRgba16(x, y, 0x18, 0xE, Util_ConvertAddrToVirtAddr(D_8FC00090), 0x18, 0x200000);

    gSPDisplayList(gDisplayListHead++, gUiRestoreTextureDL);
}

/** Shows `text` in the text box for `frames` frames. */
void PikachuReward_ShowTextForFrames(char* text, s32 frames) {
    while (frames-- > 0) {
        Controller_PollInputs();
        PikachuReward_RenderFrame(0);
        PikachuReward_DrawTextBoxPanel(0x1E, 0x20, 0x104, 0x30);
        Font_BeginTranslucentTextRendering();
        Font_SetActive(2, 0);
        Font_SetLineHeight(0x10);
        Font_Printf(0x2E, 0x28, text);
        Font_EndTexturedTextRendering();
        BgStage_AdvanceFrame();
    }

    sShownText = text;
}

/** Shows `text` in the text box until A is pressed, with the blinking ▼ arrow when `show_arrow`. */
void PikachuReward_ShowTextWaitForA(char* text, s32 show_arrow) {
    sNextArrowBlink.unk_00 = 0x10;

    do {
        Controller_PollInputs();
        PikachuReward_RenderFrame(0);
        PikachuReward_DrawTextBoxPanel(0x1E, 0x20, 0x104, 0x30);
        Font_BeginTranslucentTextRendering();
        Font_SetActive(2, 0);
        Font_SetLineHeight(0x10);
        Font_Printf(0x2E, 0x28, text);
        if (show_arrow != 0) {
            PikachuReward_DrawBlinkingNextArrow(0x104, 0x38);
        }
        Font_EndTexturedTextRendering();
        BgStage_AdvanceFrame();
    } while (!BTN_IS_PRESSED(gPlayer1Controller, BTN_A));

    Audio_PlaySoundEffectById(1);
    sShownText = text;
}

/** Scrolls the shown text up out of the text box over 8 frames while `text` scrolls in below it. */
void PikachuReward_ScrollTextIn(s8* text) {
    s32 i;
    s32 x1 = 0x1E;
    s32 x2 = 0x122;
    s32 y1 = 0x28;
    s32 y2 = 0x48;

    for (i = 1; i < 9; i++) {
        Controller_PollInputs();
        PikachuReward_RenderFrame(0);
        PikachuReward_DrawTextBoxPanel(0x1E, 0x20, 0x104, 0x30);

        gDPSetScissor(gDisplayListHead++, G_SC_NON_INTERLACE, x1, y1, x2, y2);

        Font_BeginTranslucentTextRendering();
        Font_SetActive(2, 0);
        Font_SetLineHeight(0x10);
        Font_Printf(0x2E, y1 - i * 4, sShownText);
        Font_Printf(0x2E, y2 - i * 4, text);
        Font_EndTexturedTextRendering();
        BgStage_AdvanceFrame();
    }

    sShownText = (char*)text;
}

extern char** D_83202020;
extern char sTextYes[];
extern char sTextNo[];
/**
 * Shows `question` with a はい/いいえ (yes/no) menu. D-pad up or down toggles, A confirms, B picks no.
 * Returns 1 for yes and 0 for no.
 */
s32 PikachuReward_ConfirmYesNoPrompt(char* question) {
    s32 is_yes;
    s32 blue;
    s32 cursor;
    s32 waiting;

    waiting = 1;
    cursor = 0;

    do {
        Controller_PollInputs();
        if (BTN_IS_PRESSED(gPlayer1Controller, BTN_DUP | BTN_DDOWN)) {
            Audio_PlaySoundEffectById(SFX_MENU_SCROLL);
            cursor ^= 1;
        } else if (BTN_IS_PRESSED(gPlayer1Controller, BTN_A)) {
            waiting = 0;
        } else if (BTN_IS_PRESSED(gPlayer1Controller, BTN_B)) {
            cursor = 1;
            waiting = 0;
        }

        is_yes = cursor == 0;
        PikachuReward_RenderFrame(0);
        PikachuReward_DrawTextBoxPanel(0x1E, 0x20, 0x104, 0x30);
        PikachuReward_DrawTextBoxPanel(0xD2, 0x54, 0x50, 0x2C);
        PikachuReward_DrawSelectionCursor(0xDA, (cursor * 0x10) + 0x5C);
        Font_BeginTranslucentTextRendering();
        Font_SetActive(2, 0);
        Font_SetLineHeight(0x10);
        Font_Printf(0x2E, 0x28, question);

        if (is_yes != 0) {
            blue = 0;
        } else {
            blue = 0xFF;
        }

        Gfx_SetEnvColor(0xFF, 0xFF, blue, 0xFF);
        Font_Printf(0xF2, 0x5C, sTextYes);

        if (cursor == 1) {
            blue = 0;
        } else {
            blue = 0xFF;
        }

        Gfx_SetEnvColor(0xFF, 0xFF, blue, 0xFF);
        Font_Printf(0xF2, 0x6C, sTextNo);
        Font_EndTexturedTextRendering();
        BgStage_AdvanceFrame();
    } while (waiting != 0);

    if (is_yes != 0) {
        Audio_PlaySoundEffectById(SFX_MENU_CONFIRM);
    } else {
        Audio_PlaySoundEffectById(SFX_MENU_BACK);
    }
    return is_yes;
}

extern unk_D_832027C8 D_832027C8;
extern char** D_8320201C;
typedef struct MoveNameEntryZ {
    /* 0x00 */ char unk00[4];
    /* 0x04 */ char* name;
    /* 0x08 */ char unk08[4];
} MoveNameEntryZ; // size = 0xC
extern MoveNameEntryZ D_8006A9D4[];

/**
 * Shows `prompt` next to Pikachu's four moves and returns the slot the player picks to forget, or
 * -1 for B. The HMs Cut, Fly, Strength and Flash (0x0F, 0x13, 0x46, 0x94) cannot be picked: A on
 * one plays the error sound and the list stays open (seen with Flash).
 */
s32 PikachuReward_SelectMoveToForget(char* prompt) {
    s32 blue;
    s32 cursor;
    s32 waiting;

    waiting = 1;
    cursor = 0;

    while (waiting != 0) {
        Controller_PollInputs();

        if (BTN_IS_PRESSED(gPlayer1Controller, BTN_DUP)) {
            Audio_PlaySoundEffectById(SFX_MENU_SCROLL);
            cursor--;
            if (cursor < 0) {
                cursor = 3;
            }
        }

        if (BTN_IS_PRESSED(gPlayer1Controller, BTN_DDOWN)) {
            Audio_PlaySoundEffectById(SFX_MENU_SCROLL);
            cursor++;
            if (cursor >= 4) {
                cursor = 0;
            }
        } else if (BTN_IS_PRESSED(gPlayer1Controller, BTN_A)) {
            if ((sPikachuPartyMon->moves[cursor] == 0xF) || (sPikachuPartyMon->moves[cursor] == 0x13) ||
                (sPikachuPartyMon->moves[cursor] == 0x46) || (sPikachuPartyMon->moves[cursor] == 0x94)) {
                Audio_PlaySoundEffectById(SFX_MENU_ERROR);
            } else {
                waiting = 0;
                Audio_PlaySoundEffectById(SFX_MENU_CONFIRM);
            }
        } else if (BTN_IS_PRESSED(gPlayer1Controller, BTN_B)) {
            waiting = 0;
            cursor = -1;
            Audio_PlaySoundEffectById(SFX_MENU_BACK);
        }

        PikachuReward_RenderFrame(0);
        PikachuReward_DrawTextBoxPanel(0x1E, 0x20, 0x82, 0x30);
        PikachuReward_DrawTextBoxPanel(0x96, 0x20, 0x8C, 0x4C);
        PikachuReward_DrawSelectionCursor(0x9E, (cursor * 0x10) + 0x28);
        Font_BeginTranslucentTextRendering();
        Font_SetActive(2, 0);
        Font_SetLineHeight(0x10);
        Font_Printf(0x2E, 0x28, prompt);

        if (cursor == 0) {
            blue = 0;
        } else {
            blue = 0xFF;
        }
        Gfx_SetEnvColor(0xFF, 0xFF, blue, 0xFF);
        Font_Printf(0xB6, 0x28, D_8006A9D4[sPikachuPartyMon->moves[0] - 1].name);

        if (cursor == 1) {
            blue = 0;
        } else {
            blue = 0xFF;
        }
        Gfx_SetEnvColor(0xFF, 0xFF, blue, 0xFF);
        Font_Printf(0xB6, 0x38, D_8006A9D4[sPikachuPartyMon->moves[1] - 1].name);

        if (cursor == 2) {
            blue = 0;
        } else {
            blue = 0xFF;
        }
        Gfx_SetEnvColor(0xFF, 0xFF, blue, 0xFF);
        Font_Printf(0xB6, 0x48, D_8006A9D4[sPikachuPartyMon->moves[2] - 1].name);

        if (cursor == 3) {
            blue = 0;
        } else {
            blue = 0xFF;
        }
        Gfx_SetEnvColor(0xFF, 0xFF, blue, 0xFF);
        Font_Printf(0xB6, 0x58, D_8006A9D4[sPikachuPartyMon->moves[3] - 1].name);

        Font_EndTexturedTextRendering();
        BgStage_AdvanceFrame();
    }

    return cursor;
}

extern s32 sHidePikachuWhenAnimDone;
extern char* sTextSurfNotLearned;

/**
 * Ending when the player declines Surf: 「ピカチュウに なみのりを おぼえさせませんでした。」
 * ("Pikachu did not learn Surf."), Pikachu turns away and leaves, and the scene fades out.
 */
void PikachuReward_ShowDeclinedEnding(void) {
    PikachuReward_ScrollTextIn(sTextSurfNotLearned);
    sSceneObjects[0].rotation.y = -0x800;
    ModelAnim_SetAnimation(&sSceneObjects[0], 5);
    ModelAnim_SetEventTrack(&sSceneObjects[0], 0);
    sHidePikachuWhenAnimDone = 1;
    PikachuReward_ShowTextForFrames(sTextSurfNotLearned, 0x46);
    StageFade_Start(0x1E);
    Audio_StopMusic(0x3C);
    PikachuReward_ShowTextForFrames(sTextSurfNotLearned, 0x1E);
}

M2C_UNK Announcer_CallMove(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK); /* extern */
extern s32 sHidePikachuWhenAnimDone;
extern char* sTextTakeCareOfPikachu;

/**
 * Ending after Pikachu learns Surf: Pikachu surfs off on its board to Surf's sound (move 0x39,
 * species 0x19) and music 0x13 while 「ピカチュウを だいじに してあげてね。」 ("Take good care of
 * Pikachu.") shows, then the scene fades out.
 */
void PikachuReward_ShowSuccessEnding(void) {
    ModelAnim_SetAnimation(&sSceneObjects[0], 9);
    ModelAnim_SetEventTrack(&sSceneObjects[0], 6);
    Announcer_CallMove(0, 0x39, 0x19, 0);
    sHidePikachuWhenAnimDone = 1;
    Audio_PlayMusicIfChanged(0x13);
    PikachuReward_ScrollTextIn(sTextTakeCareOfPikachu);
    PikachuReward_ShowTextForFrames(sTextTakeCareOfPikachu, 0x98);
    StageFade_Start(0x1E);
    PikachuReward_ShowTextForFrames(sTextTakeCareOfPikachu, 0x1E);
}

/** Lowers the camera onto Pikachu over 120 frames while Pikachu spins in. */
void PikachuReward_PlayIntroCamera(void) {
    s32 i;
    CameraNode* camera = sSceneRootNode->children;

    sSceneObjects->rotation.y = 0x1000;

    for (i = 0; i < 120; i++) {
        Controller_PollInputs();
        camera->view.targetPosition.y = 0x320 - ((i * 0x1E0) / 120);
        camera->view.eyePosition.y = 0x320 - ((i * 0x1E0) / 120);
        sSceneObjects->rotation.y += 0x200;
        PikachuReward_RenderFrame(0);
        BgStage_AdvanceFrame();
    }
}

extern char* sTextCongratulations;
extern char* sTextSurfReward;
extern char* sTextTeachSurfPrompt;
extern char* sTextStopLearningSurfPrompt;

/**
 * Opens the text box, shows 「おめでとう！ ピカチュウを つかって ゆうしょうしました。」
 * ("Congratulations! You won the tournament with Pikachu.") and 「ごほうびに ピカチュウが なみのりを
 * おぼえられるように してあげます。」 ("As a reward, Pikachu can learn Surf."), then asks whether to
 * teach Surf until the player says yes (returns 1) or confirms giving up (declined ending, returns 0).
 */
s32 PikachuReward_ShowIntroAndConfirm(void) {
    s16 width;
    s16 height;
    s32 i;

    width = 0x14;
    height = 0x10;
    ModelAnim_SetAnimation(&sSceneObjects[0], 8);
    i = 0;
    do {
        Controller_PollInputs();
        PikachuReward_RenderFrame(0);
        PikachuReward_DrawTextBoxPanel((s16) (0xA0 - (width / 2)), (s16) (0x38 - (height / 2)), width, height);
        BgStage_AdvanceFrame();
        i += 1;
        width += 0x1E;
        height += 4;
    } while (i != 8);
    PikachuReward_ShowTextWaitForA(sTextCongratulations, 1);
    PikachuReward_ScrollTextIn(sTextSurfReward);
    PikachuReward_ShowTextWaitForA(sTextSurfReward, 1);
loop_3:
    PikachuReward_ScrollTextIn(sTextTeachSurfPrompt);
    if (PikachuReward_ConfirmYesNoPrompt(sTextTeachSurfPrompt) != 0) {
        return 1;
    }
    PikachuReward_ScrollTextIn(sTextStopLearningSurfPrompt);
    if (PikachuReward_ConfirmYesNoPrompt(sTextStopLearningSurfPrompt) != 0) {
        PikachuReward_ShowDeclinedEnding();
        return 0;
    }
    goto loop_3;
}

typedef struct SpeciesNameEntry817010E8 {
    /* 0x00 */ char* name;
    /* 0x04 */ char unk04[8];
} SpeciesNameEntry817010E8; // size = 0xC

// The move name table (D_8006A9D4) seen from 8 bytes earlier, so [move].name is the name of move id `move`.
extern SpeciesNameEntry817010E8 D_8006A9CC[];
extern char* sTextWantsToLearnSurf;
extern char* sTextFourMovesAlready;
extern char* sTextForgetMovePrompt;
extern char* sTextGiveUpSurfPrompt;
extern char* sTextWhichMoveToForget;
extern char* sTextOneTwo;
extern char* sTextOneTwoPoof;
extern char* sTextForgotMoveFormat;
extern char* sTextAndThen;
void Audio_PlayMoveSound(s32, s32, s32);

/**
 * Returns the move slot Surf goes into: the first empty slot when Pikachu knows fewer than four
 * moves, else the slot the player picks to forget after 「しかし ピカチュウは わざを４つ おぼえるので
 * せいいっぱいだ！」 (with the 「１ ２ の ・・・ ポカン！」 question marks and 「ピカチュウは %sの
 * つかいかたを きれいに わすれた！」). Returns -1 when the player gives up Surf instead.
 */
s32 PikachuReward_ResolveMoveSlot(void) {
    char (*text)[0x78];
    s32 result;
    s32 choice;
    char buf[0x78];

    result = PikachuReward_CountKnownMoves();
    if (result == 4) {
        /* Reading buf through this pointer is what gives the ROM's register allocation. */
        text = &buf; // FAKE
    while (TRUE) {
        PikachuReward_ScrollTextIn(sTextWantsToLearnSurf);
        PikachuReward_ShowTextWaitForA(sTextWantsToLearnSurf, 1);
        PikachuReward_ScrollTextIn(sTextFourMovesAlready);
        PikachuReward_ShowTextWaitForA(sTextFourMovesAlready, 1);
        PikachuReward_ScrollTextIn(sTextForgetMovePrompt);
        if (PikachuReward_ConfirmYesNoPrompt(sTextForgetMovePrompt) != 0) {
            PikachuReward_ScrollTextIn(sTextWhichMoveToForget);
            choice = PikachuReward_SelectMoveToForget(sTextWhichMoveToForget);
            if (choice >= 0) {
                PikachuReward_ShowTextForFrames(sTextOneTwo, 0x1E);
                ModelAnim_SetAnimation(&sSceneObjects[0], 0xA);
                sQuestionMarkTimer = 0;
                Audio_PlayMoveSound(0x85, 0x19, 0);
                PikachuReward_ShowTextWaitForA(sTextOneTwoPoof, 1);
                sprintf(buf, sTextForgotMoveFormat, D_8006A9CC[sPikachuPartyMon->moves[choice]].name);
                Audio_StopMusic(0x3C);
                PikachuReward_ScrollTextIn((s8*)*text);
                PikachuReward_ShowTextWaitForA(buf, 1);
                PikachuReward_ScrollTextIn(sTextAndThen);
                PikachuReward_ShowTextWaitForA(sTextAndThen, 1);
                sQuestionMarkTimer = -1;
                return choice;
            }
        }
        PikachuReward_ScrollTextIn(sTextGiveUpSurfPrompt);
        if (PikachuReward_ConfirmYesNoPrompt(sTextGiveUpSurfPrompt) != 0) {
            PikachuReward_ShowDeclinedEnding();
            return -1;
        }
    }
    }
    Audio_StopMusic(0x3C);
    return result;
}

extern char* sTextLearnedSurf;
extern char sTextSaving[];
extern char sTextSaveHelpLine1[];
extern char sTextSaveHelpLine2[];
extern char sTextSaveHelpLine3[];
extern char sTextSaveHelpLine4[];
extern char sTextDontTurnOffPower[];
extern char sTextSaveFailed[];
extern char sTextWrongCartridgeLine1[];
extern char sTextWrongCartridgeLine2[];
/**
 * Draws one frame of the cartridge save screen under 「ピカチュウは あたらしく なみのりを おぼえた！」.
 * `status` 0 shows 「レポートちゅうです」 ("Saving"); 1 shows how to reseat the Game Boy cartridge
 * without turning off the N64; 2 adds 「レポートできませんでした」 ("Could not save"); 3 adds
 * 「カートリッジがちがいます または データが かわってしまいました」 ("Wrong cartridge, or the data
 * changed"). Only status 0 was seen in play.
 */
void PikachuReward_ShowSaveStatusScreen(s32 status) {
    PikachuReward_RenderFrame(0);
    PikachuReward_DrawTextBoxPanel(0x1E, 0x20, 0x104, 0x30);

    if (status == 0) {
        PikachuReward_DrawTextBoxPanel(0x4C, 0x64, 0xA8, 0x28);
    } else {
        PikachuReward_DrawTextBoxPanel(0x30, 0x54, 0xE0, 0x78);
    }

    Font_BeginTranslucentTextRendering();
    Font_SetActive(2, 0);
    Font_SetLineHeight(0x10);
    Font_Printf(0x2E, 0x28, sTextLearnedSurf);

    if (status == 0) {
        Font_BeginTranslucentTextRendering();
        Font_SetActive(4, -1);
        Font_Printf(0x5C, 0x70, sTextSaving);
        Font_EndTexturedTextRendering();
    } else {
        Font_Printf(0x40, 0x84, sTextSaveHelpLine1);
        Font_Printf(0x40, 0x94, sTextSaveHelpLine2);
        Font_Printf(0x40, 0xA4, sTextSaveHelpLine3);
        Font_Printf(0x40, 0xB4, sTextSaveHelpLine4);
        Gfx_SetEnvColor(0xFF, 0xFF, 0, 0xFF);
        Font_Printf(0x94, 0x84, sTextDontTurnOffPower);
        Gfx_SetEnvColor(0xFF, 0xFF, 0x64, 0xFF);

        if (status == 2) {
            Font_SetActive(4, -2);
            Font_Printf(0x4C, 0x64, sTextSaveFailed);
        } else if (status == 3) {
            Font_Printf(0x40, 0x5C, sTextWrongCartridgeLine1);
            Font_Printf(0x40, 0x6C, sTextWrongCartridgeLine2);
        }
    }

    Font_EndTexturedTextRendering();
    BgStage_AdvanceFrame();
}

extern s32 sPartyCount;
extern BattleMon sPartyMons[];

/**
 * Writes the edited party back to the Game Boy cartridge in `gb_port`, showing the save screen, and
 * keeps asking the player to reseat the cartridge until the write succeeds. Seen in play: the
 * cartridge save held Surf afterwards.
 */
void PikachuReward_SaveToCartridge(s32 gb_port) {
    M2C_UNK status;
    DeckHandle* handle;
    s32 poll;

    handle = Deck_Open(0x20, gb_port, 0, 1);
    Deck_WriteEntries((u8*)&sPartyMons, sPartyCount, handle);
    Deck_CloseAndFlush(handle);
    PikachuReward_ShowSaveStatusScreen(0);
    PikachuReward_ShowSaveStatusScreen(0);
    GbSave_ValidateBeforeWrite(gb_port);
    if (GbSave_CommitMainData(gb_port) == 0) {
        do {
            status = 2;
loop_3:
            poll = GbSave_PollCartRemoval(gb_port);
            if (poll == 1) {
                status = 1;
            }
            if (poll == 3) {
                status = 3;
            }
            PikachuReward_ShowSaveStatusScreen(status);
            if (poll != 2) {
                goto loop_3;
            }
            PikachuReward_ShowSaveStatusScreen(0);
            PikachuReward_ShowSaveStatusScreen(0);
        } while (GbSave_CommitMainData(gb_port) == 0);
    }
    GbSave_RequirePakPresent(gb_port);
}

void Audio_PlayCry(s32, s32);
extern u8 D_8006B2E5;
extern SessionContext* sSessionContext;
/**
 * Plays Pikachu's cry, shows 「ピカチュウは あたらしく なみのりを おぼえた！」 ("Pikachu learned Surf!"),
 * clears the move slots after the known moves, puts Surf (0x39) with its full PP in `move_slot`,
 * saves the party to the cartridge and plays the success ending. D_8006B2E5 is Surf's PP in
 * gMoveData. Seen in play with `move_slot` 1 (Growl's slot).
 */
void PikachuReward_TeachSurfToPikachu(s32 move_slot) {
    s32 i;

    Audio_PlayCry(0x19, 0);
    PikachuReward_ScrollTextIn(sTextLearnedSurf);
    PikachuReward_ShowTextForFrames(sTextLearnedSurf, 1);
    for (i = PikachuReward_CountKnownMoves(); i < 4; i++) {
        sPikachuPartyMon->moves[i] = 0;
        sPikachuPartyMon->pp[i] = 0;
    }
    sPikachuPartyMon->moves[move_slot] = 0x39;
    sPikachuPartyMon->pp[move_slot] = D_8006B2E5;
    PikachuReward_SaveToCartridge(sSessionContext->teamGbPort);
    PikachuReward_ShowTextWaitForA(sTextLearnedSurf, 1);
    PikachuReward_ShowSuccessEnding();
}


/** Runs the reward scene: music 0x11, fade in, intro camera, the Surf offer, and Surf if accepted. */
void PikachuReward_RunSequence(void) {
    s32 slot;

    Audio_PlayMusicIfChanged(0x11);
    StageLoader_RunFrames(2);
    StageFade_Start(0x28);
    BgStage_RunUntilCondition(0xA, PikachuReward_RenderFrame);
    PikachuReward_PlayIntroCamera();
    if (PikachuReward_ShowIntroAndConfirm() != 0) {
        slot = PikachuReward_ResolveMoveSlot();
        if (slot >= 0) {
            PikachuReward_TeachSurfToPikachu(slot);
        }
    }
    StageLoader_RunFrames(2);
}

/** Sets up one of the three question-mark models at (`x`, `y`), turned by `rotation_z`, hidden. */
void PikachuReward_SetupQuestionMarkModel(DisplayObject* mark, s16 x, s16 y, s16 rotation_z) {
    Model_InitDisplayObject(mark, 0, 0, sQuestionMarkGeo);
    ModelAnim_BindTransformCurve(mark, 0, D_8FC011C4, 0x10000);
    mark->node.flags &= ~1;
    Vec3f_SetComponentsDuplicate(&mark->scale, 1.5f, 1.5f, 1.5f);
    mark->position.x = x;
    mark->position.y = y;
    mark->rotation.z = rotation_z;
}

/** Sets up the scene: Pikachu's model (object 0, scale 16) and the three question marks (objects 1-3). */
void PikachuReward_SetupScene(void) {
    MemoryBlock* block;
    s32 i;

    block = MainPool_AllocState(main_pool_get_available(), 0);
    sSceneRootNode = process_geo_layout(block, sSceneGeoLayout);
    sQuestionMarkGeo = process_geo_layout(block, D_8FC01070);

    MainPool_FinalizeAllocation(block);
    ModelRenderer_InitDisplayRoots();

    for (i = 0; i < 4; i++) {
        ModelRenderer_AttachDisplayObject(&sSceneObjects[i]);
    }

    Model_InitDisplayObject(&sSceneObjects[0], 0, 0, sPikachuModel->unk_08->unk_00[0]);
    Vec3f_SetComponentsDuplicate(&sSceneObjects[0].scale, 16.0f, 16.0f, 16.0f);
    ModelAnim_SetAnimation(&sSceneObjects[0], 0);
    sSceneObjects->node.renderFlags &= ~0x40;
    PikachuReward_SetupQuestionMarkModel(&sSceneObjects[1], -0x50, 0x17C, 0x1800);
    PikachuReward_SetupQuestionMarkModel(&sSceneObjects[2], 0, 0x17C, 0);
    PikachuReward_SetupQuestionMarkModel(&sSceneObjects[3], 0x50, 0x17C, -0x1800);
}

extern char** D_83202020;
extern char** D_8320201C;
extern unk_D_832027C8 D_832027C8;
extern SessionContext* sSessionContext;

extern u8 D_81000000[];
extern u8 D_8FC00000[];
extern u8 D_01000000[];
extern u8 D_0015B1A0[];
extern u8 D_0015E220[];
extern u8 D_0042C4A0[];
extern u8 D_0042CC80[];
extern u8 D_002E0BE0[];
extern u8 D_002E2B90[];
s32 Font_Init(s32 load_size, s32 side);


/**
 * Fragment entry: `session` is gSessionContext. Runs the reward scene when VsScene set
 * transitionFlags 0x20 and the cartridge in teamGbPort has a Pikachu in its party.
 */
s32 Stadium_BonusPikachuReward(UNUSED s32 arg0, s32 session) {
    UNUSED s32 pad; // FAKE: stack padding
    StageContext* stage;

    sSessionContext = (SessionContext*)session;
    main_pool_push_state('PIKA');

    if ((sSessionContext->transitionFlags & 0x20) && (PikachuReward_FindPikachuInCartParty(sSessionContext->teamGbPort) != 0)) {
        Gfx_InitDisplayListBuffers(0x10000, 0);
        stage = StageContext_Allocate(0, 1, 3, 1, 2, 1);
        Font_Init(6, 0);

        Fragment_Load(((((u32)D_81000000) & 0x0FF00000) >> 0x14) - 0x10, D_0015B1A0, D_0015E220);
        Fragment_Load(((((u32)D_8FC00000) & 0x0FF00000) >> 0x14) - 0x10, D_0042C4A0, D_0042CC80);
        Asset_LoadToSegment(((u32)D_01000000 & 0x0F000000) >> 0x18, D_002E0BE0, D_002E2B90, 0);

        PokeIcon_OpenModelArchives();
        sPikachuModel = Model_LoadForPokemon(sPikachuPartyMon);
        PikachuReward_SetupScene();
        StageContext_Activate(stage);
        PikachuReward_RunSequence();
        StageContext_Deactivate();
        Font_Free();
        Gfx_FreeDisplayListBuffers();
    }

    main_pool_pop_state('PIKA');
    return 0;
}
