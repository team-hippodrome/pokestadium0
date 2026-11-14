/* Declarations for src/fragments/registration/. */
#ifndef REGISTRATION_H
#define REGISTRATION_H

#include "global.h"
#include "m2c_macros.h"
#include "menu.h"

/* A team as the registration lists hold it (Registration_LoadRegisteredTeams, Registration_LoadGbTeams). */
typedef struct RegisteredTeam {
    /* 0x000 */ u8 unk_00; // @unverified: cleared by the loaders
    /* 0x001 */ u8 source; // @unverified: 0x10 = a registered team in the Stadium save, 0x20 = a Game Boy party
    /* 0x002 */ u8 pak; // @unverified: the Transfer Pak (controller) of a Game Boy party
    /* 0x003 */ u8 slot; // @unverified: save slot of a registered team; Registration_FindFreeSlot for a new one
    /* 0x004 */ s32 trainerId; // @unverified: Deck_GetSaveEntryTrainerId or GbSave_GetTrainerId
    /* 0x008 */ u8 name[0x10]; // @unverified: trainer name, Deck_GetSaveEntryName or func_80022D84
    /* 0x018 */ ByteMatrix mons; // rows of TeamMonSlot in monBuffer; count = Pokémon read
    /* 0x028 */ TeamMonSlot monBuffer[6];
} RegisteredTeam; // size = 0x220

/* Steps through `steps` steps of `framesPerStep` frames (Registration_InitTimer, Registration_StepTimer). */
typedef struct RegistrationTimer {
    /* 0x00 */ s32 frame; // @unverified: counts up to steps * framesPerStep (or down to 0)
    /* 0x04 */ s32 steps; // @unverified: the number of Pokémon in the team
    /* 0x08 */ s32 framesPerStep; // @unverified: 15; a sound plays each step
} RegistrationTimer; // size = 0xC

/* A question with はい/いいえ (yes/no) buttons (Registration_InitConfirmWindow). */
typedef struct RegistrationConfirmWindow {
    /* 0x00 */ Window window;
    /* 0x2C */ LabeledButton yesButton; // @unverified: label D_88102F14; cursor 0 returns 1
    /* 0x68 */ LabeledButton noButton; // @unverified: label D_88102F1C; cursor 1 returns -1
    /* 0xA4 */ ChoiceCursor choice;
    /* 0xB0 */ char* text; // @unverified: the question, printed at the top
} RegistrationConfirmWindow; // size = 0xB4

/* A window with one message (Registration_InitMessageWindow). */
typedef struct RegistrationMessageWindow {
    /* 0x00 */ Window window;
    /* 0x2C */ char* text;
} RegistrationMessageWindow; // size = 0x30

/* The team list of the register, view and delete screens (Registration_InitTeamList). */
typedef struct RegistrationTeamList {
    /* 0x000 */ s32 unk_00; // @unverified: cleared by Registration_InitTeamList
    /* 0x004 */ s32 state; // @unverified: 0-2 = browsing in mode 0-2, then confirm (3, 6), timer (4, 7) and message (5, 8) states
    /* 0x008 */ Window window;
    /* 0x034 */ char unk34[0x20];
    /* 0x054 */ ScrollList list; // three 100-pixel team rows (Registration_DrawTeamRow)
    /* 0x098 */ u16 itemFlags[16];
    /* 0x0B8 */ PointerList* teams; // RegisteredTeam pointers
    /* 0x0BC */ s32 mode; // @unverified: 0 register a Game Boy party, 1 view, 2 delete (Registration_Open*List)
    /* 0x0C0 */ RegisteredTeam selectedTeam; // @unverified: copy of the team under the cursor
    /* 0x2E0 */ RegistrationMessageWindow messageWindow;
    /* 0x310 */ RegistrationConfirmWindow confirmWindow;
    /* 0x3C4 */ RegistrationTimer timer;
} RegistrationTeamList; // size = 0x3D0

/* The registration screen (Registration_InitScreen). */
typedef struct RegistrationScreen {
    /* 0x0000 */ s32 state; // @unverified: 0 the main menu, 1 a team list
    /* 0x0004 */ MenuWindow mainMenu;
    /* 0x0088 */ RegistrationTeamList teamList;
    /* 0x0458 */ RegisteredTeam teamBuffer[16];
    /* 0x2658 */ RegisteredTeam* teamPointers[16];
    /* 0x2698 */ ByteMatrix teamTable; // rows in teamBuffer
    /* 0x26A8 */ PointerList teamPointerList; // pointers in teamPointers, one per row of teamTable
} RegistrationScreen; // size = 0x26B4

typedef struct Color88100D9C {
    u8 c[4];
} Color88100D9C;

typedef struct IconCache8810173C {
    /* 0x00 */ s32* slots;
    /* 0x04 */ s32 base;
    /* 0x08 */ s32 count;
    /* 0x0C */ s32 start;
} IconCache8810173C; // size = 0x10


// registration.c
s32 Registration_FindFreeSlot(void);
void Registration_ReadTeam(s32 arg0, s32 arg1, s32 arg2, ByteMatrix* arg3);
void Registration_WriteTeam(s8 *arg0, M2C_UNK arg1);
void Registration_WriteAllTeams(PointerList* arg0);
void Registration_LoadRegisteredTeams(ByteMatrix* arg0);
void Registration_LoadGbTeams(ByteMatrix* arg0);
void Registration_DrawMenuRow(s32 arg0, s32 arg1, char* arg2, s32 arg3, s32 arg4, s32* arg5);
void Registration_InitMainMenu(MenuWindow* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, M2C_UNK* arg5, s32 arg6, M2C_UNK* arg7, s32 arg8, M2C_UNK* arg9);
void Registration_DrawMainMenu(MenuWindow* arg0, s32 arg1);
s32 Registration_UpdateMainMenu(MenuWindow* arg0);
void Registration_InitConfirmWindow(RegistrationConfirmWindow* arg, s32 arg1, s32 arg2, s32 arg3);
void Registration_DrawConfirmWindow(RegistrationConfirmWindow* arg0);
s32 Registration_UpdateConfirmWindow(RegistrationConfirmWindow* arg0);
void Registration_InitMessageWindow(RegistrationMessageWindow* arg0, s32 arg1, s32 arg2, s32 arg3);
void Registration_DrawMessageWindow(RegistrationMessageWindow* arg0);
s32 Registration_UpdateMessageWindow(s32 arg0);
void Registration_FillTrainerPanel(s32 arg0, s32 arg1, Color88100D9C arg2);
void Registration_FillTeamPanel(s32 arg0, s32 arg1, Color88100D9C arg2);
void Registration_DrawRowBorders(s32 arg0, s32 arg1, Color88100D9C arg2);
void Registration_DrawTrainerPanel(s32 arg0, s32 arg1, s32 arg2, RegisteredTeam* arg3);
void Registration_FillRowBackground(s32 x, s32 y, s32 height);
void Registration_DrawMonCell(s32 x, s32 y, u8* entry, s32 id, s32 color, IconCache8810173C* cache);
void Registration_DrawEmptyMonCell(s32 arg0, s32 arg1);
void func_88101478(s32 x, s32 y, u8* entry, s32 frame, s32 color, s32* anim);
void Registration_InitTimer(RegistrationTimer* arg0, s32 arg1);
void Registration_InitTimerFull(RegistrationTimer* arg0, s32 arg1);
s32 Registration_IsTimerDone(s8 *arg0);
s32 Registration_IsTimerAtStart(s32 *arg0);
s32 Registration_StepTimer(RegistrationTimer* arg0);
s32 Audio_QueueSoundAvoidingRecent(s32* arg0);
s32 Registration_GetTimer(s32 *arg0);
void Registration_DrawTeamRow(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
void Registration_DrawTeamRowWithTrainer(s32 arg0, s32 arg1, RegisteredTeam* arg2, s32 arg3, s32 arg4);
void Registration_ClearIndices(s32* arg0, s32 arg1, s32 arg2);
void Registration_SetListMode(RegistrationTeamList* arg0, s32 arg1);
void Registration_InitTeamList(RegistrationTeamList* arg0, s32 arg1, s32 arg2, s8 *arg3, s32 arg4);
void Registration_DrawTeamListRow(RegistrationTeamList* arg0);
void Registration_DrawTeamList(RegistrationTeamList* arg0);
s32 Registration_UpdateTeamList(RegistrationTeamList* arg0);
void Registration_BuildTeamPointers(s32* arg0, s32* arg1);
void Registration_OpenViewList(RegistrationScreen* arg0);
void Registration_OpenDeleteList(RegistrationScreen* arg0);
void Registration_OpenRegisterList(RegistrationScreen* arg0);
void Registration_InitScreen(RegistrationScreen* arg0);
M2C_UNK Registration_DrawScreen(RegistrationScreen* arg0);
s32 Registration_UpdateScreen(RegistrationScreen* arg0);
void Registration_AllocScreen(void);
s32 Registration_UpdateFade(s32 arg0);
void Registration_RunFrame(s32 arg0);
void Registration_FreeScreen(void);
s32 Registration_Init(s32 arg0, s32 arg1);

#endif // REGISTRATION_H
