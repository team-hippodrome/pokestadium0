/* Declarations for the pikachu_reward fragment (src/fragments/pikachu_reward/). */
#ifndef FRAGMENT_PIKACHU_REWARD_H
#define FRAGMENT_PIKACHU_REWARD_H

#include "global.h"
#include "PR/leo.h"
#include "game_state.h"

typedef struct unk_D_832025C8 {
    /* 0x000 */ s32 unk_00;
    /* 0x004 */ char unk04[0x1FC];
} unk_D_832025C8; // size = 0x200

typedef struct unk_D_832027C8 {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ u8 unk_02;
    /* 0x04 */ BattleMon unk_04;
} unk_D_832027C8; // size = 0x58

#define BTN_DUP         0x0800

#define BTN_DDOWN       0x0400

#define BTN_IS_PRESSED(controller, combo) (((controller)->buttonPressed & (combo)) != 0)

// pikachu_reward.c
s32 PikachuReward_SpinSunburst(s32 stage, DisplayObject* sunburst);
s32 PikachuReward_FindPikachuInCartParty(s32 gb_port);
s32 PikachuReward_CountKnownMoves(void);
void Controller_PollInputs(void);
void PikachuReward_UpdatePikachuAnimation(void);
void PikachuReward_UpdateQuestionMarks(void);
s32 PikachuReward_RenderFrame(u8 unused);
void PikachuReward_DrawBlinkingNextArrow(s16 x, s16 y);
void PikachuReward_DrawTextBoxPanel(s16 x, s16 y, s16 width, s16 height);
void PikachuReward_DrawSelectionCursor(s16 x, s16 y);
void PikachuReward_ShowTextForFrames(char* text, s32 frames);
void PikachuReward_ShowTextWaitForA(char* text, s32 show_arrow);
void PikachuReward_ScrollTextIn(s8* text);
s32 PikachuReward_ConfirmYesNoPrompt(char* question);
s32 PikachuReward_SelectMoveToForget(char* prompt);
void PikachuReward_ShowDeclinedEnding(void);
void PikachuReward_ShowSuccessEnding(void);
void PikachuReward_PlayIntroCamera(void);
s32 PikachuReward_ShowIntroAndConfirm(void);
s32 PikachuReward_ResolveMoveSlot(void);
void PikachuReward_ShowSaveStatusScreen(s32 status);
void PikachuReward_SaveToCartridge(s32 gb_port);
void PikachuReward_TeachSurfToPikachu(s32 move_slot);
void PikachuReward_RunSequence(void);
void PikachuReward_SetupQuestionMarkModel(DisplayObject* mark, s16 x, s16 y, s16 rotation_z);
void PikachuReward_SetupScene(void);
s32 Stadium_BonusPikachuReward(UNUSED s32 arg0, s32 session);

#endif // FRAGMENT_PIKACHU_REWARD_H
