/* Fixed-layout split (from FreeBattle_DrawScreen); original translation-unit boundaries remain unconfirmed. */

#include "global.h"
#include "m2c_macros.h"
#include "free_battle_setup.h"


void FreeBattle_SetScreenState(s8*, s32, s32);
extern s32 D_8200ACFC;
extern s32 D_8200AD00;
extern s32 D_8200AC50;

typedef struct List82004518 {
    /* 0x00 */ char** items;
    /* 0x04 */ s8 count;
    /* 0x08 */ s32 unk8;
} List82004518;
void FreeBattle_InitBattleModeWindow(s8* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void FreeBattle_InitMenuWindow(s8* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9);
void FreeBattle_InitCupSelect(s8* arg0, s32 arg1, s32 arg2, s32 arg3);
void FreeBattle_InitOpponentSelect(s8* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
void FreeBattle_InitEntryScreen(s8* arg0);
void FreeBattle_InitPopupMenu(s8* arg0, s32 arg1, s32 arg2, List82004518* arg3, s8* arg4, Color_RGBA8 arg5);
void func_82007C30(s8* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s8* arg6);
void BlinkingTextBox_Init(s8* arg0, s32 arg1, s32 arg2, s32 arg3, u32 arg4);
s32 Save_GetProgressFlags(void);
extern u8 D_82009014[];
extern u8 D_82009004[];
extern u8 D_82008FCC[];
extern u8 D_82008FD8[];
extern u8 D_82009D4C[];
extern u8 D_82008F9C[];
extern u8 D_82008FA4[];
extern u8 D_82009D64[];
extern u8 D_82008FBC[];
extern u8 D_82008FC4[];
extern u8 D_82009D7C[];
extern u8 D_82008FAC[];
extern u8 D_82008FB4[];
extern u8 D_82009D9C[];
extern u8 D_82008FE4[];
extern u8 D_82008FEC[];
extern u8 D_82009DBC[];
extern u8 D_82008FFC[];
extern u8 D_82009DCC[];
extern u8 D_82008FF4[];
extern u8 D_82009DE4[];
extern List82004518 D_82009278[];
extern List82004518* D_820093E0[];
extern u8 D_82008F54[];
extern u8 D_82009DFC[];

/**
 * Opens the window for screen state `arg1`: battle mode, rules, tournaments, cup, opponent, entry and popups.
 * Seen in play (2026-11-13) ran as each Free Battle window opened in turn: battle mode, rules
 * (フリーバトル), たいせんする, the opponent picker (1P VS COM) and the entry list.
 */
void FreeBattle_SetScreenState(s8* arg0, s32 arg1, s32 arg2) {
    s8* view;

    switch (arg1) {
        case 1:
            if (!(arg2 & 2)) {
                FreeBattle_InitBattleModeWindow(arg0 + 0x4378, 0x78, 0x63, (s32)D_82009014, (s32)D_82009004);
            }
            view = arg0 + 0x4378;
            break;
        case 2:
            if (!(arg2 & 2)) {
                FreeBattle_InitMenuWindow(arg0 + 0x43E4, 0x40, 0x74, 0x198, 0xCE, (s32)D_82008FCC, 3, (s32)D_82008FD8, 3, (s32)D_82009D4C);
            }
            view = arg0 + 0x43E4;
            break;
        case 3:
            if (!(arg2 & 2)) {
                FreeBattle_InitMenuWindow(arg0 + 0x43E4, 0x40, 0x74, 0x1C0, 0x11E, (s32)D_82008F9C, 2, (s32)D_82008FA4, 7, (s32)D_82009D64);
            }
            view = arg0 + 0x43E4;
            break;
        case 7:
            if (!(arg2 & 2)) {
                M2C_FIELD(arg0, s32*, 0x4358) = 1;
                M2C_FIELD(arg0, s32*, 0x435C) = 0;
                M2C_FIELD(arg0, s32*, 0x4360) = 0;
                M2C_FIELD(arg0, s32*, 0x4364) = 0;
                M2C_FIELD(arg0, s32*, 0x432C) = 1;
                M2C_FIELD(arg0, s32*, 0x433C) = 0;
                M2C_FIELD(arg0, s32*, 0x4338) = 0;
                M2C_FIELD(arg0, s32*, 0x4334) = 0;
                M2C_FIELD(arg0, s32*, 0x4330) = 0;
                M2C_FIELD(arg0, s32*, 0x4370) = 1;
                M2C_FIELD(arg0, s32*, 0x4374) = 1;
                FreeBattle_InitMenuWindow(arg0 + 0x4468, 0x50, 0x8C, 0x1C0, 0xAE, (s32)D_82008FBC, 2, (s32)D_82008FC4, 3, (s32)D_82009D7C);
            }
            view = arg0 + 0x4468;
            break;
        case 8:
            if (!(arg2 & 2)) {
                M2C_FIELD(arg0, s32*, 0x4358) = 1;
                M2C_FIELD(arg0, s32*, 0x435C) = 0;
                M2C_FIELD(arg0, s32*, 0x4360) = 0;
                M2C_FIELD(arg0, s32*, 0x4364) = 0;
                M2C_FIELD(arg0, s32*, 0x432C) = 1;
                M2C_FIELD(arg0, s32*, 0x433C) = 0;
                M2C_FIELD(arg0, s32*, 0x4338) = 0;
                M2C_FIELD(arg0, s32*, 0x4334) = 0;
                M2C_FIELD(arg0, s32*, 0x4330) = 0;
                M2C_FIELD(arg0, s32*, 0x4370) = 2;
                M2C_FIELD(arg0, s32*, 0x4374) = 2;
                FreeBattle_InitMenuWindow(arg0 + 0x4468, 0x50, 0x8C, 0x1C0, 0xAE, (s32)D_82008FAC, 2, (s32)D_82008FB4, 3, (s32)D_82009D9C);
            }
            view = arg0 + 0x4468;
            break;
        case 9:
            if (!(arg2 & 2)) {
                FreeBattle_InitCupSelect(arg0 + 0x44EC, 0x60, 0xA4, Save_GetProgressFlags() & 0xFF);
            }
            view = arg0 + 0x44EC;
            break;
        case 4:
            if (!(arg2 & 2)) {
                M2C_FIELD(arg0, s32*, 0x4370) = 0;
                switch (M2C_FIELD(arg0, s32*, 0x4374)) {
                    case 0:
                        FreeBattle_InitMenuWindow(arg0 + 0x4468, 0x50, 0x8C, 0x1AC, 0x92, (s32)D_82008FE4, 2, (s32)D_82008FEC, 2, (s32)D_82009DBC);
                        break;
                    case 1:
                        FreeBattle_InitMenuWindow(arg0 + 0x4468, 0x50, 0x8C, 0x1AC, 0x92, (s32)D_82008FE4, 2, (s32)D_82008FFC, 2, (s32)D_82009DCC);
                        break;
                    case 2:
                        FreeBattle_InitMenuWindow(arg0 + 0x4468, 0x50, 0x8C, 0x1AC, 0x92, (s32)D_82008FE4, 2, (s32)D_82008FF4, 2, (s32)D_82009DE4);
                        break;
                }
            }
            view = arg0 + 0x4468;
            break;
        case 5:
            if (!(arg2 & 2)) {
                FreeBattle_InitOpponentSelect(arg0 + 0x4554, 0xB0, 0x54, M2C_FIELD(arg0, s32*, 0x5010), M2C_FIELD(arg0, s32*, 0x5014), M2C_FIELD(arg0, s32*, 0x5018));
            }
            view = arg0 + 0x4554;
            break;
        case 10:
            if (!(arg2 & 2)) {
                FreeBattle_InitEntryScreen(arg0);
            }
            view = arg0 + 0x46A4;
            break;
        case 12:
            if (!(arg2 & 2)) {
                FreeBattle_InitPopupMenu(arg0 + 0x4E50, 0x26, 0x5A, &D_82009278[M2C_FIELD(arg0, s32*, 0x4374)], arg0 + 0x4F08, *(Color_RGBA8*)D_82008F54);
            }
            view = arg0 + 0x4E50;
            break;
        case 13:
            if (!(arg2 & 2)) {
                FreeBattle_InitPopupMenu(arg0 + 0x4EAC, 0x36, 0x72, M2C_FIELD(arg0, s32*, 0x4E84) + D_820093E0[M2C_FIELD(arg0, s32*, 0x4374)], arg0 + 0x4F1C, *(Color_RGBA8*)D_82008F54);
            }
            view = arg0 + 0x4EAC;
            break;
        case 14:
            if (!(arg2 & 2)) {
                func_82007C30(arg0 + 0x4F30, 0x25, 0x50, M2C_FIELD(arg0, s32*, 0x4374), D_8200ACFC, D_8200AD00, (s8*)D_8200AC50);
            }
            view = arg0 + 0x4F30;
            break;
        case 11:
            if (!(arg2 & 2)) {
                BlinkingTextBox_Init(arg0 + 0x4E1C, (s32)D_82009DFC, 0, 1, 0);
            }
            break;
    }
    if (arg2 & 1) {
        M2C_FIELD(M2C_FIELD(arg0, s8**, 8), s32*, 0x24) = 7;
        M2C_FIELD(arg0, s32*, 4) = arg1;
        M2C_FIELD(arg0, s8**, 0xC) = view;
    } else {
        M2C_FIELD(arg0, s32*, 0) = arg1;
        M2C_FIELD(arg0, s8**, 8) = view;
        M2C_FIELD(arg0, s32*, 4) = 0;
    }
}

u8 GbSave_GetSaveState(s32 arg0);
u8 func_8000B2E8(void);

/**
 * FreeBattle_InitBattleModeScreen
 *
 * Recomputes two masks in the object at arg0 and then calls
 * FreeBattle_SetScreenState(arg0, 1, 0). Word +0x5018 gets bit i set for each i in 0..3
 * where GbSave_GetSaveState(i) returns 0. Word +0x5010 is set to func_8000B2E8()
 * and word +0x5014 to the number of bits among bits 0..3 of that value that
 * are set.
 * Seen in play (2026-11-13) ran once as the バトルモード window (フリーバトル / トーナメント) opened from the main
 * menu.
 */
void FreeBattle_InitBattleModeScreen(s32 arg0) {
    s32 i;

    M2C_FIELD(arg0, s32*, 0x5018) = 0;
    for (i = 0; i < 4; i++) {
        if (GbSave_GetSaveState(i) == 0) {
            M2C_FIELD(arg0, s32*, 0x5018) |= 1 << i;
        }
    }
    M2C_FIELD(arg0, s32*, 0x5010) = func_8000B2E8();
    M2C_FIELD(arg0, s32*, 0x5014) = 0;
    for (i = 0; i < 4; i++) {
        if ((M2C_FIELD(arg0, s32*, 0x5010) >> i) & 1) {
            M2C_FIELD(arg0, s32*, 0x5014) += 1;
        }
    }
    FreeBattle_SetScreenState((s8*)arg0, 1, 0);
}

void FreeBattle_AddPresetTeams(void*);
void FreeBattle_LoadGbTeams(void*);
void func_80027804(void*, void*, s32, s32);
/**
 * Builds the team list from the GB cartridges and rentals and opens the entry list.
 * Seen in play: A on COM opens 「エントリーポケモンのせんたく」 and runs this.
 */
void FreeBattle_InitEntryScreen(s8 *arg0)
{
  s32 i;
  M2C_FIELD(arg0, s32*, 0x4368) = (!((M2C_FIELD(arg0, s32*, 0x4370)) == 0)) || (!((M2C_FIELD(arg0, s32*, 0x4374)) == 0));
  M2C_FIELD(arg0, s32*, 0x436C) = ((M2C_FIELD(arg0, s32*, 0x4370)) == 0) && ((M2C_FIELD(arg0, s32*, 0x4374)) == 0);
  func_80027410(arg0 + 0x4310, (s32) (arg0 + 0x10), 0x214, 0x20, 0);
  FreeBattle_LoadGbTeams(arg0 + 0x4310);
  if (M2C_FIELD(arg0, s32*, 0x4368))
  {
    FreeBattle_AddRentalEntry((void *) (arg0 + 0x4310));
  }
  if (M2C_FIELD(arg0, s32*, 0x436C))
  {
    FreeBattle_AddPresetTeams(arg0 + 0x4310);
  }
  func_80027804(arg0 + 0x4320, arg0 + 0x4290, 0x20, 0);
  FreeBattle_BuildTeamPointers((void *) (arg0 + 0x4320), (void *) (arg0 + 0x4310));
  FreeBattle_MarkIneligibleMons((void *) (arg0 + 0x4310), M2C_FIELD(arg0, s32*, 0x4374));
  M2C_FIELD(arg0, s32*, 0x4354) = 0;
    for (i = 0; i < 5; i++) { M2C_FIELD(arg0, s32*, (0x4340 + (i * 4))) = 0;
  }

  FreeBattle_InitEntrySelect(arg0 + 0x4690, 0x30, 0x5C, (s32) (arg0 + 0x4320), (s32) (arg0 + 0x4340), M2C_FIELD(arg0, s32*, 0x4374));
}

void BgStage_DrawFrame(void);
M2C_UNK Ui_DrawTintedScreenBackground(M2C_UNK, M2C_UNK, u8, u8, s32);
extern u8 D_82008F50[];
void FreeBattle_DrawBattleModeWindow(s8*);
void FreeBattle_DrawMenuWindow(s8*, s32);
void FreeBattle_DrawPopupMenu(s8*, s32);
void func_82007D94(s8*, s32);
void FreeBattle_DrawOpponentSelect(s8*);
void func_82006DF8(FreeBattleTeamOpponentWindow*);
void FreeBattle_DrawCupSelect(s8*, s32);
void FreeBattle_DrawRentalScreen(s8*);
void BlinkingTextBox_Draw(s8*);
/**
 * Draws the battle setup screen for its current state.
 * Seen in play: runs every frame on the battle menu screens.
 */
M2C_UNK FreeBattle_DrawScreen(s32 arg0) {
    s8* base = (s8*)arg0;

    BgStage_DrawFrame();
    Ui_DrawTintedScreenBackground(0x38, 0x1E0, D_82008F50[0], D_82008F50[1], D_82008F50[2]);
    switch (*(s32*)base) {
        case 1:
            FreeBattle_DrawBattleModeWindow(base + 0x4378);
            break;
        case 2:
        case 3:
            FreeBattle_DrawMenuWindow(base + 0x43E4, 2);
            break;
        case 4:
            FreeBattle_DrawMenuWindow(base + 0x43E4, 0x10);
            FreeBattle_DrawMenuWindow(base + 0x4468, 2);
            break;
        case 12:
            FreeBattle_DrawPopupMenu(base + 0x4E50, 2);
            break;
        case 13:
            FreeBattle_DrawPopupMenu(base + 0x4E50, 0x10);
            FreeBattle_DrawPopupMenu(base + 0x4EAC, 0);
            break;
        case 14:
            func_82007D94(base + 0x4F30, 0);
            break;
        case 5:
            FreeBattle_DrawMenuWindow(base + 0x43E4, 0x10);
            FreeBattle_DrawMenuWindow(base + 0x4468, 0x10);
            FreeBattle_DrawOpponentSelect(base + 0x4554);
            break;
        case 6:
            FreeBattle_DrawMenuWindow(base + 0x43E4, 0x10);
            FreeBattle_DrawMenuWindow(base + 0x4468, 0x10);
            func_82006DF8(base + 0x45C8);
            break;
        case 7:
        case 8:
            FreeBattle_DrawMenuWindow(base + 0x43E4, 0x10);
            FreeBattle_DrawMenuWindow(base + 0x4468, 2);
            break;
        case 9:
            FreeBattle_DrawMenuWindow(base + 0x43E4, 0x10);
            FreeBattle_DrawMenuWindow(base + 0x4468, 0x10);
            FreeBattle_DrawCupSelect(base + 0x44EC, 2);
            break;
        case 10:
            FreeBattle_DrawRentalScreen(base + 0x4690);
            break;
        case 11:
            FreeBattle_DrawRentalScreen(base + 0x4690);
            BlinkingTextBox_Draw(base + 0x4E1C);
            break;
    }
}

typedef struct Blob82004E9C {
    s32 data[0x85];
} Blob82004E9C;
typedef struct Blobs82004E9C {
    s8 pad[0x10];
    Blob82004E9C blobs[1];
} Blobs82004E9C;

void func_80027814(s8*, s8*, s32);
s32 func_8002BC14(s32);
void func_8003F6AC(s32);
s32 Audio_PlayCommand(u32 arg0, s32 arg1, s32 arg2);
void FreeBattle_ClearIndices(void*, s32, s32);
void FreeBattle_InitEntryListCursor(s8*);
s32 FreeBattle_UpdateEntrySelect(s8*);
void FreeBattle_CommitEntries(s8*);
s32 FreeBattle_UpdateMenuWindow(s8*);
s32 FreeBattle_UpdatePopupMenu(s8*);
s32 FreeBattle_UpdateOpponentSelect(s8*);
s32 FreeBattle_UpdateBattleModeWindow(s8*);
s32 FreeBattle_UpdateCupSelect(s8*);
s32 func_82008044(s8*);
extern s32 D_800603C0;
extern s32 D_82008F84;
extern u8 D_8200AC58[];

/**
 * Runs the battle setup screen's state machine for one frame.
 * Seen in play (2026-11-13) ran every frame from the battle mode window through the entry list.
 */
s32 FreeBattle_UpdateScreen(s8* arg0) {
    s32 ret;
    s32 res;
    s32 pad; // FAKE: unused stack word
    s32 idx;
    s32 sel;

    ret = 0;
    res = M2C_FIELD(arg0, s32*, 4);
    if (res != 0) {
        if (M2C_FIELD(M2C_FIELD(arg0, s8**, 8), s32*, 0x28) == 4) {
            M2C_FIELD(arg0, s32*, 0) = res;
            if (res == 0xF) {
                ret = 1;
            } else {
                M2C_FIELD(arg0, s32*, 4) = 0;
                M2C_FIELD(arg0, s8**, 8) = M2C_FIELD(arg0, s8**, 0xC);
            }
            return ret;
        }
        if ((M2C_FIELD(M2C_FIELD(arg0, s8**, 8), s32*, 0x28) != 1) && (M2C_FIELD(M2C_FIELD(arg0, s8**, 8), s32*, 0x28) != 2)) {
            return 0;
        }
    }
    switch (M2C_FIELD(arg0, s32*, 0)) {
        case 1:
            res = FreeBattle_UpdateBattleModeWindow(arg0 + 0x4378);
            if (res == -1) {
                FreeBattle_SetScreenState(arg0, 0xF, 1);
                D_82008F84 = 0x8040;
            } else if (res == 1) {
                FreeBattle_SetScreenState(arg0, 2, 1);
            } else if (res == 2) {
                FreeBattle_SetScreenState(arg0, 3, 1);
            }
            break;
        case 3:
            res = FreeBattle_UpdateMenuWindow(arg0 + 0x43E4);
            if (res == -1) {
                FreeBattle_SetScreenState(arg0, 1, 1);
            } else if (res == 1) {
                FreeBattle_SetScreenState(arg0, 8, 0);
            } else if (res == 2) {
                FreeBattle_SetScreenState(arg0, 7, 0);
            }
            break;
        case 2:
            res = FreeBattle_UpdateMenuWindow(arg0 + 0x43E4);
            if (res == -1) {
                FreeBattle_SetScreenState(arg0, 1, 1);
            } else if (res == 1) {
                M2C_FIELD(arg0, s32*, 0x4374) = 0;
                FreeBattle_SetScreenState(arg0, 4, 0);
            } else if (res == 2) {
                M2C_FIELD(arg0, s32*, 0x4374) = 2;
                FreeBattle_SetScreenState(arg0, 4, 0);
            } else if (res == 3) {
                M2C_FIELD(arg0, s32*, 0x4374) = 1;
                FreeBattle_SetScreenState(arg0, 4, 0);
            }
            break;
        case 4:
            res = FreeBattle_UpdateMenuWindow(arg0 + 0x4468);
            if (res == -1) {
                FreeBattle_SetScreenState(arg0, 2, 3);
            } else if (res == 1) {
                FreeBattle_SetScreenState(arg0, 5, 0);
            } else if (res == 2) {
                M2C_FIELD(arg0, s32*, 0x4408) = 7;
                FreeBattle_SetScreenState(arg0, 0xC, 1);
            }
            break;
        case 12:
            res = FreeBattle_UpdatePopupMenu(arg0 + 0x4E50);
            if (res == -1) {
                sel = (M2C_FIELD(arg0, s32*, 0x4370) == 0) ? 2 : 3;
                FreeBattle_SetScreenState(arg0, sel, 1);
            } else if (res > 0) {
                func_8003F6AC(2);
                if (res == D_82009278[M2C_FIELD(arg0, s32*, 0x4374)].count) {
                    FreeBattle_SetScreenState(arg0, 0xE, 1);
                } else {
                    FreeBattle_SetScreenState(arg0, 0xD, 0);
                }
            }
            break;
        case 13:
            res = func_8002BC14(D_800603C0);
            if ((res == -1) || (res == 1)) {
                func_8003F6AC(3);
                FreeBattle_SetScreenState(arg0, 0xC, 3);
            }
            break;
        case 14:
            if (func_82008044(arg0 + 0x4F30) == -1) {
                FreeBattle_SetScreenState(arg0, 0xC, 1);
            }
            break;
        case 5:
            res = FreeBattle_UpdateOpponentSelect(arg0 + 0x4554);
            if (res == -1) {
                FreeBattle_SetScreenState(arg0, 4, 3);
            } else if (res == 1) {
                M2C_FIELD(arg0, s32*, 0x4358) = 1;
                M2C_FIELD(arg0, s32*, 0x435C) = 0;
                M2C_FIELD(arg0, s32*, 0x4364) = 0;
                M2C_FIELD(arg0, s32*, 0x432C) = 1;
                M2C_FIELD(arg0, s32*, 0x433C) = 0;
                M2C_FIELD(arg0, s32*, 0x4338) = 0;
                M2C_FIELD(arg0, s32*, 0x4334) = 0;
                M2C_FIELD(arg0, s32*, 0x4330) = 0;
                M2C_FIELD(arg0, s32*, 0x4360) = M2C_FIELD(arg0, s32*, 0x45B8);
                M2C_FIELD(arg0, s32*, 0x4328 + M2C_FIELD(arg0, s32*, 0x45B8) * 4) = 1;
                M2C_FIELD(arg0, s32*, 0x448C) = 7;
                M2C_FIELD(arg0, s32*, 0x4408) = 7;
                FreeBattle_SetScreenState(arg0, 0xA, 1);
            }
            break;
        case 7:
            res = FreeBattle_UpdateMenuWindow(arg0 + 0x4468);
            if (res == -1) {
                FreeBattle_SetScreenState(arg0, 3, 3);
            } else if (res == 1) {
                M2C_FIELD(arg0, s32*, 0x501C) = 0;
                M2C_FIELD(arg0, s32*, 0x4408) = 7;
                FreeBattle_SetScreenState(arg0, 0xA, 1);
            } else if (res == 2) {
                M2C_FIELD(arg0, s32*, 0x4408) = 7;
                FreeBattle_SetScreenState(arg0, 0xC, 1);
            }
            break;
        case 8:
            res = FreeBattle_UpdateMenuWindow(arg0 + 0x4468);
            if (res == -1) {
                FreeBattle_SetScreenState(arg0, 3, 3);
            } else if (res == 1) {
                FreeBattle_SetScreenState(arg0, 9, 0);
            } else if (res == 2) {
                M2C_FIELD(arg0, s32*, 0x4408) = 7;
                FreeBattle_SetScreenState(arg0, 0xC, 1);
            }
            break;
        case 9:
            res = FreeBattle_UpdateCupSelect(arg0 + 0x44EC);
            if (res == -1) {
                FreeBattle_SetScreenState(arg0, 8, 3);
            } else if (res > 0) {
                M2C_FIELD(arg0, s32*, 0x4408) = 7;
                M2C_FIELD(arg0, s32*, 0x448C) = 7;
                M2C_FIELD(arg0, s32*, 0x501C) = M2C_FIELD(arg0, s32*, 0x4520);
                FreeBattle_SetScreenState(arg0, 0xA, 1);
            }
            break;
        case 10:
            res = FreeBattle_UpdateEntrySelect(arg0 + 0x4690);
            if (res == -1) {
                if (M2C_FIELD(arg0, s32*, 0x43AC) == 0) {
                    FreeBattle_SetScreenState(arg0, 2, 1);
                } else {
                    FreeBattle_SetScreenState(arg0, 3, 1);
                }
            } else if (res == 1) {
                if (M2C_FIELD(arg0, s32*, 0x4DC4) != 0) {
                    M2C_FIELD(arg0, s32*, 0x4318)++;
                    M2C_FIELD(arg0, u8*, 0x4758) |= 1;
                    ((Blob82004E9C*)(arg0 + 0x10))[M2C_FIELD(arg0, s32*, 0x4318) - 1] = *(Blob82004E9C*)(arg0 + 0x4758);
                    idx = M2C_FIELD(arg0, s32*, 0x4328) + ((M2C_FIELD(arg0, s32*, 0x4368) != 0) ? -1 : 0);
                    func_80027814(arg0 + 0x4320, (s8*)&((Blobs82004E9C*)arg0)->blobs[M2C_FIELD(arg0, s32*, 0x4318) - 1], idx);
                } else {
                    idx = M2C_FIELD(arg0, s32*, 0x46D8);
                }
                M2C_FIELD(arg0, s32*, 0x4340 + M2C_FIELD(arg0, s32*, 0x4354) * 4) = M2C_FIELD(arg0, s32*, 0x4290 + idx * 4);
                M2C_FIELD(arg0, s32*, 0x4354)++;
                if (M2C_FIELD(arg0, s32*, 0x4354) < 5) {
                loop:
                    if (((s32*)(arg0 + 0x432C))[M2C_FIELD(arg0, s32*, 0x4354)] == 0) {
                        M2C_FIELD(arg0, s32*, 0x4354)++;
                        if (M2C_FIELD(arg0, s32*, 0x4354) < 5) {
                            goto loop;
                        }
                    }
                }
                if (M2C_FIELD(arg0, s32*, 0x4354) >= 5) {
                    FreeBattle_CommitEntries(arg0);
                    Audio_PlayCommand(0x53, 0, 0);
                    FreeBattle_SetScreenState(arg0, 0xB, 0);
                } else {
                    M2C_FIELD(arg0, s32*, 0x4DC8) = M2C_FIELD(arg0, s32*, 0x4354) + 1;
                    if (M2C_FIELD(arg0, s32*, 0x4DC4) != 0) {
                        FreeBattle_ClearIndices(D_8200AC58, (M2C_FIELD(arg0, s32*, 0x46D8) * 6) % 24, 6);
                    }
                    FreeBattle_InitEntryListCursor(arg0 + 0x4690);
                }
            }
            break;
        case 11:
            if (M2C_FIELD(arg0, s32*, 0x4E3C) >= 0x19) {
                M2C_FIELD(arg0, s32*, 0x4E40) = 1;
                ret = 1;
                D_82008F84 = 0x8050;
            }
            break;
    }
    return ret;
}

/*
 * FreeBattle_RestoreMenuState
 *
 * Writes two words in the structure `arg0` points to, derived from the
 * bytes D_800AE8F0[0] and D_800AE8F0[1] of the session context, and then
 * calls FreeBattle_SetScreenState(arg0, 2, 0) or FreeBattle_SetScreenState(arg0, 3, 0).
 *
 *   D_800AE8F0[0] == 0:
 *     arg0->0x43AC = 0
 *     arg0->0x4418 = 0 if D_800AE8F0[1] == 0, else 1 if it is 2, else 2
 *     FreeBattle_SetScreenState(arg0, 2, 0)
 *   otherwise:
 *     arg0->0x43AC = 1
 *     arg0->0x4418 = 0 if D_800AE8F0[0] == 2, else 1
 *     FreeBattle_SetScreenState(arg0, 3, 0)
 *
 * FreeBattle_SetScreenState is still assembly, so what the 2 / 3 select is not
 * established.  The first argument of every call is `arg0` itself; the ROM
 * never writes $a0 before the call, so it is the caller's argument passed
 * through.
 */
extern s8 D_800AE8F0;

/**
 * Reopens the rule menu with the choice saved from the previous visit.
 * Not reached in play (2026-11-13): did not run in a tour of the main menu, Pokédex, party, Lab,
 * registration, Free Battle setup and a COM battle (opening, a switch, running, a Pound turn).
 * @unverified Name and comment guessed from the code.
 */
void FreeBattle_RestoreMenuState(s32 arg0) {
    s32 var_v0;

    if (D_800AE8F0 == 0) {
        M2C_FIELD((void*)arg0, s32 *, 0x43AC) = 0;
        if (((s8*)&D_800AE8F0)[1] == 0) {
            M2C_FIELD((void*)arg0, s32 *, 0x4418) = 0;
        } else {
            if (((s8*)&D_800AE8F0)[1] == 2) {
                var_v0 = 1;
            } else {
                var_v0 = 2;
            }
            M2C_FIELD((void*)arg0, s32 *, 0x4418) = var_v0;
        }
        FreeBattle_SetScreenState((s8*)arg0, 2, 0);
        return;
    }
    M2C_FIELD((void*)arg0, s32 *, 0x43AC) = 1;
    if (D_800AE8F0 == 2) {
        M2C_FIELD((void*)arg0, s32 *, 0x4418) = 0;
    } else {
        M2C_FIELD((void*)arg0, s32 *, 0x4418) = 1;
    }
    FreeBattle_SetScreenState((s8*)arg0, 3, 0);
}

extern s32 D_8200AD28;
extern s32 D_8200AD2C;
extern M2C_UNK D_8200AD30;
s32 func_80025BD8(void);
void func_80027FF8(void*, s32);
s32 func_80002D98(s32);
void func_8200573C(void) {
    D_8200AD2C = func_80025BD8();
    if (D_8200AD2C != -1) {
        func_80027FF8(&D_8200AD30, D_8200AD2C);
    }
    D_8200AD28 = func_80002D98(0x5020);
    FreeBattle_InitBattleModeScreen(D_8200AD28);
}

typedef struct Col8200579C { u8 r, g, b, a; } Col8200579C;
extern s32 D_820090D4;
extern s32 D_820090D8;
/*
 * Second name for D_820090D4. The fade-out store in this function family
 * (also func_8200579C, func_8900429C, LabPCList_UpdateFade, func_8A101B30) does not
 * share the counter's address with the load before it, which only happens
 * when the two accesses name different symbols.
 */
extern s32 D_820090D4_2;
extern M2C_UNK D_82009E10;
M2C_UNK GbSave_DrawSummaryBar(M2C_UNK, M2C_UNK *, M2C_UNK *, s32);
void BgStage_DrawFrame(void);
M2C_UNK Ui_DrawTintedScreenBackground(M2C_UNK, M2C_UNK, u8, u8, s32);
void func_8002C8D8(Col8200579C*, Col8200579C, f32);
s32 func_8200579C(s32 arg0) {
    Col8200579C sp2C;
    M2C_UNK *var_a1;
    s32 n;

    n = D_820090D4;
    if (n >= 8) {
        D_820090D8 = 1;
    }
    if (D_820090D8 != 0) {
        n--;
        D_820090D4_2 = n;
    }
    BgStage_DrawFrame();
    if (D_8200AD2C == -1) {
        var_a1 = NULL;
    } else {
        var_a1 = &D_8200AD30;
    }
    GbSave_DrawSummaryBar(0, var_a1, &D_82009E10, D_8200AD2C);
    n = D_820090D4;
    func_8002C8D8(&sp2C, *(Col8200579C*)&D_82008F50, n / (f64)8.0f);
    Ui_DrawTintedScreenBackground(0x38, 0x1E0, sp2C.r, sp2C.g, sp2C.b);
    if (D_820090D8 == 0) {
        n = D_820090D4;
        n++;
        D_820090D4 = n;
    }
    return 0;
}

void Cont_StartReadInputs(void);                            /* extern */
void Cont_ReadInputs(void);                            /* extern */
M2C_UNK FreeBattle_DrawScreen(s32);                         /* extern */
s32 FreeBattle_UpdateScreen(s8*);
extern s32 D_8200AD28;

/**
 * One frame of the battle setup screen.
 * Seen in play: runs every frame on the battle menu screens (バトルモード, たいせんルールせんたく).
 */
void FreeBattle_RunFrame(s32 arg0) {
    Cont_StartReadInputs();
    Cont_ReadInputs();
    FreeBattle_DrawScreen(D_8200AD28);
    FreeBattle_UpdateScreen((s8*) D_8200AD28);
}

M2C_UNK GbSave_DrawSummaryBar(M2C_UNK, M2C_UNK *, M2C_UNK *, s32); /* extern */
M2C_UNK FreeBattle_DrawScreen(s32);                         /* extern */
extern M2C_UNK D_82009E18;
extern s32 D_8200AD28;
extern s32 D_8200AD2C;
extern M2C_UNK D_8200AD30;

/**
 * Draws the setup screen and the GB save summary bar.
 * Seen in play: runs as 「エントリーけってい」 fades out after both teams are entered.
 */
s32 FreeBattle_DrawScreenWithSummary(s32 arg0) {
    M2C_UNK *var_a1;

    FreeBattle_DrawScreen(D_8200AD28);
    if (D_8200AD2C == -1) {
        var_a1 = NULL;
    } else {
        var_a1 = &D_8200AD30;
    }
    GbSave_DrawSummaryBar(0, var_a1, &D_82009E18, D_8200AD2C);
    return 0;
}

M2C_UNK func_80002DC0(s32);                         /* extern */
extern s32 D_8200AD28;

void func_82005958(void) {
    func_80002DC0(D_8200AD28);
}

extern s32 D_8200AD08[8];
extern s32 D_8200AC40;
extern s32 D_820090DC[8];
s32 func_800044AC(s32, s32);

void func_8200597C(void) {
    s32 i;

    for (i = 0; i < 8; i++) {
        D_8200AD08[i] = func_800044AC(D_8200AC40, D_820090DC[i]);
    }
}

s32 Font_Init(s32 load_size, s32 side);
s8 *PokeIcon_AllocFramebuffers(s32 arg0);
u16* func_80018F2C(s32, s32, s32, s32, s32, s32, s32, s32);
s32 func_80017FDC(s32, s32, s32, s32);
s32 func_80004154(u8*, u8*, s32, s32);
void PokeIcon_OpenModelArchives(void);
void func_800040B4(s32, u8*, u8*);
void func_80003EB8(s32, u8*, u8*, s32);
s32 func_80001B10(u8*);
void FreeBattle_RestoreMenuState(s32);
void func_80005B98(s32);
void func_80006828(s32, void*);
void func_8000A7B0(s32);
void func_80006998(s32);
void func_8000A7FC(s32);
void func_80006724(void);
void func_8000675C(void);
s32 func_8200579C(s32);
extern u8 D_81000000[];
extern u8 D_0015B1A0[];
extern u8 D_0015E220[];
extern u8 D_01000000[];
extern u8 D_002E0BE0[];
extern u8 D_002E2B90[];
extern u8 D_0A000000[];
extern u8 D_0A000C80[];
extern u8 D_0A0016D0[];
extern u8 D_003FFD60[];
extern u8 D_00400F70[];
extern u8 D_04000000[];
extern u8 D_004076E0[];
extern u8 D_05000000[];
extern u8 D_004199E0[];
extern u8 D_0042C4A0[];
extern u8 D_002F5940[];
extern u8 D_003139C0[];
extern s32 D_8200AC44;
extern u16* D_8200AC48;
extern s32 D_8200AC4C;
extern s32 D_8200AC50;
extern s32 D_8200ACFC;
extern s32 D_8200AD00;
extern s32 D_8200AD04;
extern s32 D_8200AD28;
extern s8 D_800AE8F0;
extern s32 D_82008F84;
M2C_UNK func_820059EC(void) {
    Font_Init(0x3C, 0);
    D_8200AC44 = PokeIcon_AllocFramebuffers(1);
    D_8200AC48 = func_80018F2C(D_8200AC44, 0x80, 0x78, 0, 0, 0x78, 0x78, 0);
    *D_8200AC48 &= ~2;
    *D_8200AC48 &= ~4;
    D_8200AC4C = 0;
    D_8200AC50 = func_80017FDC(D_8200AC44, 0x28, 0x28, 0x28);
    D_8200AC40 = func_80004154(D_002F5940, D_003139C0, 1, 1);
    PokeIcon_OpenModelArchives();

    func_800040B4(((((u32)D_81000000) & 0x0FF00000) >> 0x14) - 0x10, D_0015B1A0, D_0015E220);
    func_80003EB8(((u32)D_01000000 & 0x0F000000) >> 0x18, D_002E0BE0, D_002E2B90, 0);
    func_80003EB8(((u32)D_0A000000 & 0x0F000000) >> 0x18, D_003FFD60, D_00400F70, 0);
    func_80003EB8(((u32)D_04000000 & 0x0F000000) >> 0x18, D_00400F70, D_004076E0, 0);
    func_80003EB8(((u32)D_05000000 & 0x0F000000) >> 0x18, D_004199E0, D_0042C4A0, 0);

    D_8200ACFC = func_80001B10(D_0A000000);
    D_8200AD00 = func_80001B10(D_0A000C80);
    D_8200AD04 = func_80001B10(D_0A0016D0);
    func_8200597C();
    func_8200573C();
    func_8000675C();

    if (M2C_FIELD(&D_800AE8F0, u16*, 0x1096) & 0x100) {
        M2C_FIELD(&D_800AE8F0, u16*, 0x1096) &= ~0x100;
        FreeBattle_RestoreMenuState(D_8200AD28);
        func_80005B98(0xF);
        func_80006828(0x11, FreeBattle_DrawScreenWithSummary);
        func_8000A7B0(9);
    } else {
        func_80006828(8, func_8200579C);
    }
    func_80006828(0, FreeBattle_RunFrame);

    if (D_82008F84 == 0x8050) {
        func_80006998(0xFFFF);
        func_80005B98(0xF);
        func_80006828(0x11, FreeBattle_DrawScreenWithSummary);
        func_8000A7FC(0xF);
    } else {
        func_80006828(8, func_8200579C);
    }
    func_80006724();
    func_82005958();
}

M2C_UNK func_8000256C(M2C_UNK);                     /* extern */
M2C_UNK func_80002620(M2C_UNK);                     /* extern */
M2C_UNK func_80025BA0(s32, M2C_UNK *, M2C_UNK *, M2C_UNK, s32); /* extern */
M2C_UNK func_820059EC();                            /* extern */
M2C_UNK func_82008F14();                            /* extern */
extern s8 D_00235D70;
extern s8 D_00238BD0;
extern s8 D_800AE8F0;
extern s32 D_82008F84;
extern s8* D_8200ACF8;
extern s8 D_88000000;
s32 func_82005CCC(s32 arg0, M2C_UNK arg1)
{
  s32 temp_v1;
  func_8000256C(0x4D454E54);
  D_8200ACF8 = &D_800AE8F0;
  if (arg0 == 1)
  {
    func_82008F14();
  }
  else
  {
    func_820059EC();
  }
  func_80002620(0x4D454E54);
  temp_v1 = D_82008F84;
  if (temp_v1 == 0x8040)
  {
    func_80025BA0((((u32) (((s32) (&D_88000000)) & 0x0FF00000)) >> 0x14) - 0x10, &D_00235D70, &D_00238BD0, 0, 0);
  }
  return D_82008F84;
}
