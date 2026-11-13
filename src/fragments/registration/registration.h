/* Declarations for src/fragments/registration/. */
#ifndef REGISTRATION_H
#define REGISTRATION_H

#include "global.h"
#include "m2c_macros.h"

typedef struct Color88100D9C {
    u8 c[4];
} Color88100D9C;

typedef struct IconCache8810173C {
    /* 0x00 */ s32* slots;
    /* 0x04 */ s32 base;
    /* 0x08 */ s32 count;
    /* 0x0C */ s32 start;
} IconCache8810173C; // size = 0x10

typedef struct {
    /* 0x00 */ char unk00[0x8];
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ char unk10[0x44];
    /* 0x54 */ s32** tables;
    /* 0x58 */ char unk58[0x4];
    /* 0x5C */ s32 index;
} IndexedDrawer;

// registration.c
s32 Registration_FindFreeSlot(void);
void Registration_ReadTeam(s32 arg0, s32 arg1, s32 arg2, s32* arg3);
void Registration_WriteTeam(s8 *arg0, M2C_UNK arg1);
void Registration_WriteAllTeams(void *arg0);
void Registration_LoadRegisteredTeams(s8* arg0);
void Registration_LoadGbTeams(s8* arg0);
void Registration_DrawMenuRow(s32 arg0, s32 arg1, char* arg2, s32 arg3, s32 arg4, s32* arg5);
void Registration_InitMainMenu(s8* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, M2C_UNK* arg5, s32 arg6, M2C_UNK* arg7, s32 arg8, M2C_UNK* arg9);
void Registration_DrawMainMenu(s8* arg0, s32 arg1);
s32 Registration_UpdateMainMenu(void* arg0);
void Registration_InitConfirmWindow(s8* arg, s32 arg1, s32 arg2, s32 arg3);
void Registration_DrawConfirmWindow(s8* arg0);
s32 Registration_UpdateConfirmWindow(s32 arg0);
void Registration_InitMessageWindow(void* arg0, s32 arg1, s32 arg2, s32 arg3);
void Registration_DrawMessageWindow(s8* arg0);
s32 Registration_UpdateMessageWindow(s32 arg0);
void Registration_FillTrainerPanel(s32 arg0, s32 arg1, Color88100D9C arg2);
void Registration_FillTeamPanel(s32 arg0, s32 arg1, Color88100D9C arg2);
void Registration_DrawRowBorders(s32 arg0, s32 arg1, Color88100D9C arg2);
void Registration_DrawTrainerPanel(s32 arg0, s32 arg1, s32 arg2, u8* arg3);
void Registration_FillRowBackground(s32 x, s32 y, s32 height);
void Registration_DrawMonCell(s32 x, s32 y, u8* entry, s32 id, s32 color, IconCache8810173C* cache);
void Registration_DrawEmptyMonCell(s32 arg0, s32 arg1);
void func_88101478(s32 x, s32 y, u8* entry, s32 frame, s32 color, s32* anim);
void Registration_InitTimer(s8 *arg0, s32 arg1);
void Registration_InitTimerFull(s8 *arg0, s32 arg1);
s32 Registration_IsTimerDone(s8 *arg0);
s32 Registration_IsTimerAtStart(s32 *arg0);
s32 Registration_StepTimer(s8* arg0);
s32 Audio_QueueSoundAvoidingRecent(s32* arg0);
s32 Registration_GetTimer(s32 *arg0);
void Registration_DrawTeamRow(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
void Registration_DrawTeamRowWithTrainer(s32 arg0, s32 arg1, s8* arg2, s32 arg3, s32 arg4);
void Registration_ClearIndices(s32* arg0, s32 arg1, s32 arg2);
void Registration_SetListMode(s8 *arg0, s32 arg1);
void Registration_InitTeamList(s8 *arg0, s32 arg1, s32 arg2, s8 *arg3, s32 arg4);
void Registration_DrawTeamListRow(IndexedDrawer* arg0);
void Registration_DrawTeamList(s8* arg0);
s32 Registration_UpdateTeamList(s8* arg0);
void Registration_BuildTeamPointers(s32* arg0, s32* arg1);
void Registration_OpenViewList(s32* arg0);
void Registration_OpenDeleteList(s32* arg0);
void Registration_OpenRegisterList(s32* arg0);
void Registration_InitScreen(s32 arg0);
M2C_UNK Registration_DrawScreen(s32 a);
s32 Registration_UpdateScreen(s32 arg0);
void Registration_AllocScreen(void);
s32 Registration_UpdateFade(s32 arg0);
void Registration_RunFrame(s32 arg0);
void Registration_FreeScreen(void);
s32 Registration_Init(s32 arg0, s32 arg1);

#endif // REGISTRATION_H
