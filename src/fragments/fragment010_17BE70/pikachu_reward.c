/* Stadium Zero fragment010_17BE70. */
/* C ported from the Stadium 1 decomp: src/fragments/pikachu_reward/pikachu_reward.c, src/game_state.c. */

#include "fragments/pikachu_reward/pikachu_reward.h"
#include "geo_render.h"
#include "model_animation.h"
#include "display_object_textures.h"
#include "model_renderer.h"
#include "graphics_textures.h"
#include "ui_graphics.h"
#include "pokemon_stats.h"
#include "text_system.h"
#include "gb_save.h"
#include "jpeg_stream.h"
#include "audio_fade.h"
#include "audio_stored_fade.h"
#include "audio_sfx.h"
#include "cry.h"
#include "gfx_buffer.h"
#include "gfx_rect.h"
#include "DDC0.h"
#include "matrix.h"
#include "geo_layout.h"
#include "memory.h"
#include "stage_loader.h"
#include "util.h"
extern GraphNode* D_81702010;
extern GraphNode* D_81702014;
extern unk_D_86002F30* D_81702018;
extern DisplayObject D_81702020[4];
extern unk_D_832025C8 D_817025C0;
extern s32 D_81701B04;
extern char* D_81701B08;
extern u32 D_81701B4C[];

#include "game_state.h"
#include "functions.h"
#include "input.h"
#include "save_data.h"
#include "audio_commands.h"
#include "gallery.h"
#include "gb_data.h"
#include "jpeg_stream.h"
#include "gfx_buffer.h"
#include "DDC0.h"
#include "session.h"
#include "save_data.h"
#include "minigame_dispatch.h"
#include "gb_save.h"
#include "gb_tower_audio.h"
#include "leo.h"
#include "display_object_textures.h"
#include "pokemon_stats.h"
#include "controller.h"
#include "dp_intro.h"
#include "gb_tower.h"
#include "memory.h"
#include "rsp.h"
#include "stage_loader.h"
#include "lib/ultralib/include/PR/os_internal_reg.h"
extern u16 D_8006BBB0[16][256];
extern s32 pad_D_80075660;
extern s32 pad_D_80075664;
extern s32 gCurrentGameState;
extern s32 gLastGameState;
extern s32 pad_D_80075670;
extern s16 D_800733D4;
extern s16 D_800733D8;
extern unk_D_800AE520 D_800AF990;
extern s32 pad_D_800AE534[2];
extern SessionContext gSessionContext;

#include "m2c_macros.h"

s32 PikachuReward_PositionSurfingPikachuModel(s32 arg0, DisplayObject* arg1);
void Controller_PollInputs(void);
void PikachuReward_UpdateFollowerVisibility(void);
s32 PikachuReward_RenderFrame(u8 arg0);
void PikachuReward_DrawTextBoxPanel(s16 arg0, s16 arg1, s16 arg2, s16 arg3);
void PikachuReward_DrawSelectionCursor(s16 arg0, s16 arg1);
void PikachuReward_ShowTextForFrames(char* arg0, s32 arg1);
void PikachuReward_ScrollTextIn(s8* arg0);
void PikachuReward_PlayIntroCamera(void);
void PikachuReward_SetupFollowerModel(DisplayObject* arg0, s16 arg1, s16 arg2, s16 arg3);
void PikachuReward_SetupScene(void);

void PikachuReward_UpdateLeadPikachuAnimation(void);

s32 PikachuReward_PositionSurfingPikachuModel(s32 arg0, DisplayObject* arg1) {
    if (arg0 == 2) {
        arg1->rotation.z -= 0x80;
        arg1->position.x = D_81702020->position.x;
        arg1->position.y = D_81702020->position.y + 70.0f;
    }
    return 0;
}

typedef struct Rec81700064 {
    /* 0x00 */ u8 id;
    /* 0x01 */ u8 unk01[0x4F];
} Rec81700064; // size = 0x50
s32 func_80020AFC(M2C_UNK, s32, M2C_UNK, M2C_UNK);
s32 func_80020CE4(void*, s32, s32);
M2C_UNK func_80020C60(s32);
s32 func_80021894(s32);
extern s32 D_817025C4;
extern Rec81700064 D_817025C8[];
extern s8* D_817027A8;

s32 func_81700064(s32 arg0) {
    s32 i;
    s32 handle;

    if ((arg0 != -1) && (func_80021894(arg0) != 0)) {
        handle = func_80020AFC(0x20, arg0, 0, 0);
        D_817025C4 = func_80020CE4(D_817025C8, 6, handle);
        func_80020C60(handle);
        for (i = 0; i < D_817025C4; i++) {
            if (D_817025C8[i].id == 0x19) {
                D_817027A8 = (s8*)&D_817025C8[i];
                return 1;
            }
        }
    }
    return 0;
}

extern s8 *D_817027A8;

s32 func_81700130(void) {
    s32 var_v1;
    s8 *var_v0;

    var_v0 = D_817027A8;
    var_v1 = 0;
loop_1:
    if (M2C_FIELD(var_v0, u8 *, 9) != 0) {
        var_v1 += 1;
        var_v0 += 1;
        if (var_v1 != 4) {
            goto loop_1;
        }
    }
    return var_v1;
}

void Controller_PollInputs(void) {
    Cont_StartReadInputs();
    Cont_ReadInputs();
    Input_ResetRepeatState();
}

extern s32 D_81701B00;
void PikachuReward_UpdateLeadPikachuAnimation(void) {
    static s32 D_83202004 = 0;

    if ((D_81702020[0].transformAnim.animationId != 0x9) && (D_81702020[0].transformAnim.animationId != 5)) {
        D_83202004++;
        if (D_83202004 == 0x3C) {
            D_83202004 = 0;
            ModelAnim_SetEventTrack(&D_81702020[0], -1);
            ModelAnim_SetEventTrack(&D_81702020[0], 0xA);
        }
    }

    if ((D_81702020[0].transformAnim.animationId != 0) && (ModelAnim_IsFinished(&D_81702020[0]) != 0)) {
        if (D_81701B00 != 0) {
            D_81702020[0].node.flags &= ~1;
        } else {
            ModelAnim_SetAnimation(&D_81702020[0], 0);
        }
    }
}

void PikachuReward_UpdateFollowerVisibility(void) {
    if (D_81701B04 == -1) {
        D_81702020[1].node.flags &= ~1;
        D_81702020[2].node.flags &= ~1;
        D_81702020[3].node.flags &= ~1;
        return;
    }

    switch (D_81701B04) {
        case 0x0:
            D_81702020[1].node.flags |= 1;
            break;

        case 0x8:
            D_81702020[2].node.flags |= 1;
            break;

        case 0x10:
            D_81702020[3].node.flags |= 1;
            break;

        case 0x46:
            D_81702020[1].node.flags &= ~1;
            break;

        case 0x4E:
            D_81702020[2].node.flags &= ~1;
            break;

        case 0x56:
            D_81702020[3].node.flags &= ~1;
            break;
    }

    if (D_81701B04 < 0x57) {
        D_81701B04++;
    }
}

s32 PikachuReward_RenderFrame(u8 arg0) {
    GeoRender_AdvanceFrameCounter();
    PikachuReward_UpdateLeadPikachuAnimation();
    PikachuReward_UpdateFollowerVisibility();
    BgStage_DrawFrame();
    GfxImage_FillCurrent(&gDisplayListHead, 1);
    Geo_RenderRootNode(D_81702010);
    return 0;
}

void PikachuReward_DrawBlinkingStarIcon(s16 arg0, s16 arg1) {
    s32 var_a3;

    if (D_817025C0.unk_00 < 0x10) {
        var_a3 = D_817025C0.unk_00 * 0x10;
    } else if (D_817025C0.unk_00 < 0x23) {
        var_a3 = 0xFF;
    } else if (D_817025C0.unk_00 < 0x32) {
        var_a3 = (-D_817025C0.unk_00 * 0x10) + 0x320;
    } else {
        var_a3 = 0;
    }

    D_817025C0.unk_00++;
    if (D_817025C0.unk_00 >= 0x3D) {
        D_817025C0.unk_00 = 0;
    }

    Gfx_SetEnvColor(0xFF, 0xFF, 0xFF, var_a3);
    Font_DrawCharAt(arg0, arg1, 0x2177);
}

void PikachuReward_DrawTextBoxPanel(s16 arg0, s16 arg1, s16 arg2, s16 arg3) {
    Color_RGB8 sp24 = { 0x00, 0x00, 0x32 };
    Color_RGB8 sp20 = { 0x00, 0x00, 0xC8 };

    Ui_DrawGradientPanel(arg0, arg1, arg2, arg3, &sp24, &sp20);
}

void PikachuReward_DrawSelectionCursor(s16 arg0, s16 arg1) {
    gSPDisplayList(gDisplayListHead++, D_80060290);

    Gfx_DrawTextureRgba16(arg0, arg1, 0x18, 0xE, Util_ConvertAddrToVirtAddr(D_8FC00090), 0x18, 0x200000);

    gSPDisplayList(gDisplayListHead++, gUiRestoreTextureDL);
}

void PikachuReward_ShowTextForFrames(char* arg0, s32 arg1) {
    while (arg1-- > 0) {
        Controller_PollInputs();
        PikachuReward_RenderFrame(0);
        PikachuReward_DrawTextBoxPanel(0x1E, 0x20, 0x104, 0x30);
        Font_BeginTranslucentTextRendering();
        Font_SetActive(2, 0);
        Font_SetLineHeight(0x10);
        Font_Printf(0x2E, 0x28, arg0);
        Font_EndTexturedTextRendering();
        BgStage_AdvanceFrame();
    }

    D_81701B08 = arg0;
}

M2C_UNK func_81700160();

void PikachuReward_ShowTextWaitForA(char* arg0, s32 arg1) {
    D_817025C0.unk_00 = 0x10;

    do {
        func_81700160();
        PikachuReward_RenderFrame(0);
        PikachuReward_DrawTextBoxPanel(0x1E, 0x20, 0x104, 0x30);
        Font_BeginTranslucentTextRendering();
        Font_SetActive(2, 0);
        Font_SetLineHeight(0x10);
        Font_Printf(0x2E, 0x28, arg0);
        if (arg1 != 0) {
            PikachuReward_DrawBlinkingStarIcon(0x104, 0x38);
        }
        Font_EndTexturedTextRendering();
        BgStage_AdvanceFrame();
    } while (!BTN_IS_PRESSED(gPlayer1Controller, BTN_A));

    Audio_PlaySoundEffectById(1);
    D_81701B08 = arg0;
}

void PikachuReward_ScrollTextIn(s8* arg0) {
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
        Font_Printf(0x2E, y1 - i * 4, D_81701B08);
        Font_Printf(0x2E, y2 - i * 4, arg0);
        Font_EndTexturedTextRendering();
        BgStage_AdvanceFrame();
    }

    D_81701B08 = arg0;
}

extern char** D_83202020;
extern char D_81701EFC[];
extern char D_81701F04[];
s32 PikachuReward_ConfirmYesNoPrompt(char* arg0) {
    s32 temp_s3;
    s32 var_a2;
    s32 var_s1;
    s32 var_s2;

    var_s2 = 1;
    var_s1 = 0;

    do {
        Controller_PollInputs();
        if (BTN_IS_PRESSED(gPlayer1Controller, BTN_DUP | BTN_DDOWN)) {
            Audio_PlaySoundEffectById(SFX_MENU_SCROLL);
            var_s1 ^= 1;
        } else if (BTN_IS_PRESSED(gPlayer1Controller, BTN_A)) {
            var_s2 = 0;
        } else if (BTN_IS_PRESSED(gPlayer1Controller, BTN_B)) {
            var_s1 = 1;
            var_s2 = 0;
        }

        temp_s3 = var_s1 == 0;
        PikachuReward_RenderFrame(0);
        PikachuReward_DrawTextBoxPanel(0x1E, 0x20, 0x104, 0x30);
        PikachuReward_DrawTextBoxPanel(0xD2, 0x54, 0x50, 0x2C);
        PikachuReward_DrawSelectionCursor(0xDA, (var_s1 * 0x10) + 0x5C);
        Font_BeginTranslucentTextRendering();
        Font_SetActive(2, 0);
        Font_SetLineHeight(0x10);
        Font_Printf(0x2E, 0x28, arg0);

        if (temp_s3 != 0) {
            var_a2 = 0;
        } else {
            var_a2 = 0xFF;
        }

        Gfx_SetEnvColor(0xFF, 0xFF, var_a2, 0xFF);
        Font_Printf(0xF2, 0x5C, D_81701EFC);

        if (var_s1 == 1) {
            var_a2 = 0;
        } else {
            var_a2 = 0xFF;
        }

        Gfx_SetEnvColor(0xFF, 0xFF, var_a2, 0xFF);
        Font_Printf(0xF2, 0x6C, D_81701F04);
        Font_EndTexturedTextRendering();
        BgStage_AdvanceFrame();
    } while (var_s2 != 0);

    if (temp_s3 != 0) {
        Audio_PlaySoundEffectById(SFX_MENU_CONFIRM);
    } else {
        Audio_PlaySoundEffectById(SFX_MENU_BACK);
    }
    return temp_s3;
}

extern unk_D_832027C8 D_832027C8;
extern char** D_8320201C;
typedef struct MoveNameEntryZ {
    /* 0x00 */ char unk00[4];
    /* 0x04 */ char* name;
    /* 0x08 */ char unk08[4];
} MoveNameEntryZ; // size = 0xC
extern MoveNameEntryZ D_8006A9D4[];

s32 PikachuReward_SelectMoveToForget(char* arg0) {
    s32 var_a2;
    s32 var_s0;
    s32 var_s4;

    var_s4 = 1;
    var_s0 = 0;

    while (var_s4 != 0) {
        Controller_PollInputs();

        if (BTN_IS_PRESSED(gPlayer1Controller, BTN_DUP)) {
            Audio_PlaySoundEffectById(SFX_MENU_SCROLL);
            var_s0--;
            if (var_s0 < 0) {
                var_s0 = 3;
            }
        }

        if (BTN_IS_PRESSED(gPlayer1Controller, BTN_DDOWN)) {
            Audio_PlaySoundEffectById(SFX_MENU_SCROLL);
            var_s0++;
            if (var_s0 >= 4) {
                var_s0 = 0;
            }
        } else if (BTN_IS_PRESSED(gPlayer1Controller, BTN_A)) {
            if ((M2C_FIELD(D_817027A8 + var_s0, u8*, 9) == 0xF) || (M2C_FIELD(D_817027A8 + var_s0, u8*, 9) == 0x13) ||
                (M2C_FIELD(D_817027A8 + var_s0, u8*, 9) == 0x46) || (M2C_FIELD(D_817027A8 + var_s0, u8*, 9) == 0x94)) {
                Audio_PlaySoundEffectById(SFX_MENU_ERROR);
            } else {
                var_s4 = 0;
                Audio_PlaySoundEffectById(SFX_MENU_CONFIRM);
            }
        } else if (BTN_IS_PRESSED(gPlayer1Controller, BTN_B)) {
            var_s4 = 0;
            var_s0 = -1;
            Audio_PlaySoundEffectById(SFX_MENU_BACK);
        }

        PikachuReward_RenderFrame(0);
        PikachuReward_DrawTextBoxPanel(0x1E, 0x20, 0x82, 0x30);
        PikachuReward_DrawTextBoxPanel(0x96, 0x20, 0x8C, 0x4C);
        PikachuReward_DrawSelectionCursor(0x9E, (var_s0 * 0x10) + 0x28);
        Font_BeginTranslucentTextRendering();
        Font_SetActive(2, 0);
        Font_SetLineHeight(0x10);
        Font_Printf(0x2E, 0x28, arg0);

        if (var_s0 == 0) {
            var_a2 = 0;
        } else {
            var_a2 = 0xFF;
        }
        Gfx_SetEnvColor(0xFF, 0xFF, var_a2, 0xFF);
        Font_Printf(0xB6, 0x28, D_8006A9D4[M2C_FIELD(D_817027A8, u8*, 9) - 1].name);

        if (var_s0 == 1) {
            var_a2 = 0;
        } else {
            var_a2 = 0xFF;
        }
        Gfx_SetEnvColor(0xFF, 0xFF, var_a2, 0xFF);
        Font_Printf(0xB6, 0x38, D_8006A9D4[M2C_FIELD(D_817027A8, u8*, 0xA) - 1].name);

        if (var_s0 == 2) {
            var_a2 = 0;
        } else {
            var_a2 = 0xFF;
        }
        Gfx_SetEnvColor(0xFF, 0xFF, var_a2, 0xFF);
        Font_Printf(0xB6, 0x48, D_8006A9D4[M2C_FIELD(D_817027A8, u8*, 0xB) - 1].name);

        if (var_s0 == 3) {
            var_a2 = 0;
        } else {
            var_a2 = 0xFF;
        }
        Gfx_SetEnvColor(0xFF, 0xFF, var_a2, 0xFF);
        Font_Printf(0xB6, 0x58, D_8006A9D4[M2C_FIELD(D_817027A8, u8*, 0xC) - 1].name);

        Font_EndTexturedTextRendering();
        BgStage_AdvanceFrame();
    }

    return var_s0;
}

M2C_UNK func_80005B98(M2C_UNK);                     /* extern */
M2C_UNK func_8000A7FC(M2C_UNK);                     /* extern */
M2C_UNK func_800199F8(M2C_UNK *, M2C_UNK);          /* extern */
M2C_UNK func_80019A90(M2C_UNK *, M2C_UNK);          /* extern */
M2C_UNK func_81700588(s32, M2C_UNK);                /* extern */
M2C_UNK func_8170070C(s32);                         /* extern */
extern s32 D_81701B00;
extern s32 D_81701B1C;
extern M2C_UNK D_FLT_81702020;

void func_81700D7C(void) {
    func_8170070C(D_81701B1C);
    M2C_FIELD(&D_FLT_81702020, s16 *, 0x20) = -0x800;
    func_800199F8(&D_FLT_81702020, 5);
    func_80019A90(&D_FLT_81702020, 0);
    D_81701B00 = 1;
    func_81700588(D_81701B1C, 0x46);
    func_80005B98(0x1E);
    func_8000A7FC(0x3C);
    func_81700588(D_81701B1C, 0x1E);
}

M2C_UNK func_80005B98(M2C_UNK);                     /* extern */
M2C_UNK func_8000A7B0(M2C_UNK);                     /* extern */
M2C_UNK func_800199F8(M2C_UNK *, M2C_UNK);          /* extern */
M2C_UNK func_80019A90(M2C_UNK *, M2C_UNK);          /* extern */
M2C_UNK func_800414B0(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK); /* extern */
M2C_UNK func_81700588(s32, M2C_UNK);                /* extern */
M2C_UNK func_8170070C(s32);                         /* extern */
extern s32 D_81701B00;
extern s32 D_81701B48;
extern M2C_UNK D_FLT_81702020;

void func_81700E04(void) {
    func_800199F8(&D_FLT_81702020, 9);
    func_80019A90(&D_FLT_81702020, 6);
    func_800414B0(0, 0x39, 0x19, 0);
    D_81701B00 = 1;
    func_8000A7B0(0x13);
    func_8170070C(D_81701B48);
    func_81700588(D_81701B48, 0x98);
    func_80005B98(0x1E);
    func_81700588(D_81701B48, 0x1E);
}

void PikachuReward_PlayIntroCamera(void) {
    s32 i;
    CameraNode* temp_s1 = D_81702010->children;

    D_81702020->rotation.y = 0x1000;

    for (i = 0; i < 120; i++) {
        Controller_PollInputs();
        temp_s1->view.targetPosition.y = 0x320 - ((i * 0x1E0) / 120);
        temp_s1->view.eyePosition.y = 0x320 - ((i * 0x1E0) / 120);
        D_81702020->rotation.y += 0x200;
        PikachuReward_RenderFrame(0);
        BgStage_AdvanceFrame();
    }
}

M2C_UNK func_80006780();                            /* extern */
M2C_UNK func_800199F8(M2C_UNK *, M2C_UNK);          /* extern */
M2C_UNK func_81700160();                            /* extern */
M2C_UNK func_81700370(M2C_UNK);                     /* extern */
M2C_UNK func_81700468(s16, s16, s16, s16);          /* extern */
M2C_UNK func_81700630(s32, M2C_UNK);                /* extern */
M2C_UNK func_8170070C(s32);                         /* extern */
s32 func_817008B4(s32);                             /* extern */
extern s32 D_81701B0C;
extern s32 D_81701B10;
extern s32 D_81701B14;
extern s32 D_81701B18;
extern M2C_UNK D_FLT_81702020;

s32 func_81700F78(void) {
    s16 var_s0;
    s16 var_s1;
    s32 var_s2;

    var_s0 = 0x14;
    var_s1 = 0x10;
    func_800199F8(&D_FLT_81702020, 8);
    var_s2 = 0;
    do {
        func_81700160();
        func_81700370(0);
        func_81700468((s16) (0xA0 - (var_s0 / 2)), (s16) (0x38 - (var_s1 / 2)), var_s0, var_s1);
        func_80006780();
        var_s2 += 1;
        var_s0 += 0x1E;
        var_s1 += 4;
    } while (var_s2 != 8);
    func_81700630(D_81701B0C, 1);
    func_8170070C(D_81701B10);
    func_81700630(D_81701B10, 1);
loop_3:
    func_8170070C(D_81701B14);
    if (func_817008B4(D_81701B14) != 0) {
        return 1;
    }
    func_8170070C(D_81701B18);
    if (func_817008B4(D_81701B18) != 0) {
        func_81700D7C();
        return 0;
    }
    goto loop_3;
}

typedef struct SpeciesNameEntry817010E8 {
    /* 0x00 */ char* name;
    /* 0x04 */ char unk04[8];
} SpeciesNameEntry817010E8; // size = 0xC

extern SpeciesNameEntry817010E8 D_8006A9CC[];
extern s32 D_81701B20;
extern s32 D_81701B24;
extern s32 D_81701B28;
extern s32 D_81701B2C;
extern s32 D_81701B30;
extern s32 D_81701B34;
extern s32 D_81701B38;
extern char* D_81701B3C;
extern s32 D_81701B40;
s32 func_81700A80(s32);
void func_8003FE58(s32, s32, s32);
s32 func_800564D4(char*, const char*, ...);

s32 func_817010E8(void) {
    char (*text)[0x78];
    s32 result;
    s32 choice;
    char buf[0x78];

    result = func_81700130();
    if (result == 4) {
        /* Reading buf through this pointer is what gives the ROM's register allocation. */
        text = &buf;
    while (TRUE) {
        func_8170070C(D_81701B20);
        func_81700630(D_81701B20, 1);
        func_8170070C(D_81701B24);
        func_81700630(D_81701B24, 1);
        func_8170070C(D_81701B28);
        if (func_817008B4(D_81701B28) != 0) {
            func_8170070C(D_81701B30);
            choice = func_81700A80(D_81701B30);
            if (choice >= 0) {
                func_81700588(D_81701B34, 0x1E);
                func_800199F8(&D_FLT_81702020, 0xA);
                D_81701B04 = 0;
                func_8003FE58(0x85, 0x19, 0);
                func_81700630(D_81701B38, 1);
                func_800564D4(buf, D_81701B3C, D_8006A9CC[M2C_FIELD(D_817027A8 + choice, u8*, 9)].name);
                func_8000A7FC(0x3C);
                func_8170070C((s32)*text);
                func_81700630((s32)buf, 1);
                func_8170070C(D_81701B40);
                func_81700630(D_81701B40, 1);
                D_81701B04 = -1;
                return choice;
            }
        }
        func_8170070C(D_81701B2C);
        if (func_817008B4(D_81701B2C) != 0) {
            func_81700D7C();
            return -1;
        }
    }
    }
    func_8000A7FC(0x3C);
    return result;
}

extern char* D_81701B44;
extern char D_81701F0C[];
extern char D_81701F20[];
extern char D_81701F30[];
extern char D_81701F54[];
extern char D_81701F74[];
extern char D_81701F94[];
extern char D_81701FA8[];
extern char D_81701FC4[];
extern char D_81701FE4[];
void PikachuReward_ShowSaveStatusScreen(s32 arg0) {
    PikachuReward_RenderFrame(0);
    PikachuReward_DrawTextBoxPanel(0x1E, 0x20, 0x104, 0x30);

    if (arg0 == 0) {
        PikachuReward_DrawTextBoxPanel(0x4C, 0x64, 0xA8, 0x28);
    } else {
        PikachuReward_DrawTextBoxPanel(0x30, 0x54, 0xE0, 0x78);
    }

    Font_BeginTranslucentTextRendering();
    Font_SetActive(2, 0);
    Font_SetLineHeight(0x10);
    Font_Printf(0x2E, 0x28, D_81701B44);

    if (arg0 == 0) {
        Font_BeginTranslucentTextRendering();
        Font_SetActive(4, -1);
        Font_Printf(0x5C, 0x70, D_81701F0C);
        Font_EndTexturedTextRendering();
    } else {
        Font_Printf(0x40, 0x84, D_81701F20);
        Font_Printf(0x40, 0x94, D_81701F30);
        Font_Printf(0x40, 0xA4, D_81701F54);
        Font_Printf(0x40, 0xB4, D_81701F74);
        Gfx_SetEnvColor(0xFF, 0xFF, 0, 0xFF);
        Font_Printf(0x94, 0x84, D_81701F94);
        Gfx_SetEnvColor(0xFF, 0xFF, 0x64, 0xFF);

        if (arg0 == 2) {
            Font_SetActive(4, -2);
            Font_Printf(0x4C, 0x64, D_81701FA8);
        } else if (arg0 == 3) {
            Font_Printf(0x40, 0x5C, D_81701FC4);
            Font_Printf(0x40, 0x6C, D_81701FE4);
        }
    }

    Font_EndTexturedTextRendering();
    BgStage_AdvanceFrame();
}

s32 func_80020AFC(M2C_UNK, s32, M2C_UNK, M2C_UNK);  /* extern */
M2C_UNK func_80020C60(s32);                         /* extern */
M2C_UNK func_80020DF0(M2C_UNK *, s32, s32);         /* extern */
s32 func_80021B30(s32);                             /* extern */
s32 func_80021FF4(s32);                             /* extern */
M2C_UNK func_80022118(s32);                         /* extern */
M2C_UNK func_80022188(s32);                         /* extern */
M2C_UNK func_817012C0(M2C_UNK);                     /* extern */
extern s32 D_817025C4;
extern Rec81700064 D_817025C8[];

void func_817014A4(s32 arg0) {
    M2C_UNK var_s0;
    s32 temp_v0;
    s32 temp_v0_2;

    temp_v0 = func_80020AFC(0x20, arg0, 0, 1);
    func_80020DF0(&D_817025C8, D_817025C4, temp_v0);
    func_80020C60(temp_v0);
    func_817012C0(0);
    func_817012C0(0);
    func_80022118(arg0);
    if (func_80021FF4(arg0) == 0) {
        do {
            var_s0 = 2;
loop_3:
            temp_v0_2 = func_80021B30(arg0);
            if (temp_v0_2 == 1) {
                var_s0 = 1;
            }
            if (temp_v0_2 == 3) {
                var_s0 = 3;
            }
            func_817012C0(var_s0);
            if (temp_v0_2 != 2) {
                goto loop_3;
            }
            func_817012C0(0);
            func_817012C0(0);
        } while (func_80021FF4(arg0) == 0);
    }
    func_80022188(arg0);
}

void func_8003F96C(s32, s32);
M2C_UNK func_81700588(s32, M2C_UNK);
M2C_UNK func_8170070C(s32);
M2C_UNK func_81700630(s32, M2C_UNK);
extern u8 D_8006B2E5;
extern s8* D_8170201C;
M2C_UNK func_817015B0(s32 arg0) {
    s32 i;

    func_8003F96C(0x19, 0);
    func_8170070C((s32)D_81701B44);
    func_81700588((s32)D_81701B44, 1);
    for (i = func_81700130(); i < 4; i++) {
        M2C_FIELD(D_817027A8 + i, u8*, 9) = 0;
        M2C_FIELD(D_817027A8 + i, u8*, 0x20) = 0;
    }
    M2C_FIELD(D_817027A8 + arg0, u8*, 9) = 0x39;
    M2C_FIELD(D_817027A8 + arg0, u8*, 0x20) = D_8006B2E5;
    func_817014A4(M2C_FIELD(D_8170201C, u8*, 0x1094));
    func_81700630((s32)D_81701B44, 1);
    func_81700E04();
}

M2C_UNK func_80005B98(M2C_UNK);                     /* extern */
M2C_UNK func_800067BC(M2C_UNK);                     /* extern */
M2C_UNK func_80006828(M2C_UNK, M2C_UNK *);          /* extern */
M2C_UNK func_8000A7B0(M2C_UNK);                     /* extern */
M2C_UNK func_81700E98();                            /* extern */
s32 func_81700F78();                                /* extern */
s32 func_817010E8();                                /* extern */
M2C_UNK func_817015B0(s32);                         /* extern */

void func_81701710(void) {
    s32 temp_v0;

    func_8000A7B0(0x11);
    func_800067BC(2);
    func_80005B98(0x28);
    func_80006828(0xA, &func_81700370);
    func_81700E98();
    if (func_81700F78() != 0) {
        temp_v0 = func_817010E8();
        if (temp_v0 >= 0) {
            func_817015B0(temp_v0);
        }
    }
    func_800067BC(2);
}

void PikachuReward_SetupFollowerModel(DisplayObject* arg0, s16 arg1, s16 arg2, s16 arg3) {
    Model_InitDisplayObject(arg0, 0, 0, D_81702014);
    ModelAnim_BindTransformCurve(arg0, 0, D_8FC011C4, 0x10000);
    arg0->node.flags &= ~1;
    Vec3f_SetComponentsDuplicate(&arg0->scale, 1.5f, 1.5f, 1.5f);
    arg0->position.x = arg1;
    arg0->position.y = arg2;
    arg0->rotation.z = arg3;
}

void PikachuReward_SetupScene(void) {
    MemoryBlock* temp_v0;
    s32 i;

    temp_v0 = MainPool_AllocState(main_pool_get_available(), 0);
    D_81702010 = process_geo_layout(temp_v0, D_81701B4C);
    D_81702014 = process_geo_layout(temp_v0, D_8FC01070);

    MainPool_FinalizeAllocation(temp_v0);
    ModelRenderer_InitDisplayRoots();

    for (i = 0; i < 4; i++) {
        ModelRenderer_AttachDisplayObject(&D_81702020[i]);
    }

    Model_InitDisplayObject(&D_81702020[0], 0, 0, D_81702018->unk_08->unk_00[0]);
    Vec3f_SetComponentsDuplicate(&D_81702020[0].scale, 16.0f, 16.0f, 16.0f);
    ModelAnim_SetAnimation(&D_81702020[0], 0);
    D_81702020->node.renderFlags &= ~0x40;
    PikachuReward_SetupFollowerModel(&D_81702020[1], -0x50, 0x17C, 0x1800);
    PikachuReward_SetupFollowerModel(&D_81702020[2], 0, 0x17C, 0);
    PikachuReward_SetupFollowerModel(&D_81702020[3], 0x50, 0x17C, -0x1800);
}

extern char** D_83202020;
extern char** D_8320201C;
extern unk_D_832027C8 D_832027C8;
extern s8* D_8170201C;

extern u8 D_81000000[];
extern u8 D_8FC00000[];
extern u8 D_01000000[];
extern u8 D_0015B1A0[];
extern u8 D_0015E220[];
extern u8 D_0042C4A0[];
extern u8 D_0042CC80[];
extern u8 D_002E0BE0[];
extern u8 D_002E2B90[];
s32 func_81700064(s32);
void func_8001A194(s32, s32);

void func_81701710(void);

s32 Stadium_BonusPikachuReward(UNUSED s32 arg0, s32 arg1) {
    UNUSED s32 pad;
    StageContext* sp20;

    D_8170201C = (s8*)arg1;
    main_pool_push_state('PIKA');

    if ((M2C_FIELD(D_8170201C, u16*, 0x1096) & 0x20) && (func_81700064(M2C_FIELD(D_8170201C, u8*, 0x1094)) != 0)) {
        Gfx_InitDisplayListBuffers(0x10000, 0);
        sp20 = StageContext_Allocate(0, 1, 3, 1, 2, 1);
        func_8001A194(6, 0);

        Fragment_Load(((((u32)D_81000000) & 0x0FF00000) >> 0x14) - 0x10, D_0015B1A0, D_0015E220);
        Fragment_Load(((((u32)D_8FC00000) & 0x0FF00000) >> 0x14) - 0x10, D_0042C4A0, D_0042CC80);
        Asset_LoadToSegment(((u32)D_01000000 & 0x0F000000) >> 0x18, D_002E0BE0, D_002E2B90, 0);

        PokeIcon_OpenModelArchives();
        D_81702018 = Model_LoadForPokemon((BattleMon*)D_817027A8);
        PikachuReward_SetupScene();
        StageContext_Activate(sp20);
        func_81701710();
        StageContext_Deactivate();
        Font_Free();
        Gfx_FreeDisplayListBuffers();
    }

    main_pool_pop_state('PIKA');
    return 0;
}
