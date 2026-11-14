/* Declarations for the battle_order_select fragment (src/fragments/battle_order_select/). */
#ifndef FRAGMENT_BATTLE_ORDER_SELECT_H
#define FRAGMENT_BATTLE_ORDER_SELECT_H

#include "global.h"
#include "game_state.h"

typedef struct OrderSidebarIcons {
    /* 0x00 */ s8 iconCount; // @unverified: picks so far; BattleMenu_AppendOrderSlotIcon appends at this index
    /* 0x01 */ s8 isCom; // @unverified: the single trainer's isHuman has bit 1 set (2 = COM, as FreeBattle_CopyTeamToRoster sets)
    /* 0x02 */ s8 slotIcons[6]; // @unverified: per order slot, high nibble picking port + 1; -1 marks slots 3-5 unused (func_823003B8)
    /* 0x08 */ s8 slotIconGrowth[6]; // @unverified: 1 grow, -1 shrink (BattleMenu_ResetOrderSlotIcons), passed to BattleMenu_DrawSidebarRowTypeIcon
    /* 0x0E */ s8 firstPort; // @unverified: lower controller port of the side's trainers (func_823003B8)
    /* 0x0F */ s8 secondPort; // @unverified: the other tag partner's port, -1 without one
} OrderSidebarIcons; // size = 0x10

typedef struct OrderSelectPanel {
    /* 0x00 */ s8 panelIndex; // @unverified: index in D_82302B48, set by BattleMenu_AddOrderSelectPanel
    /* 0x01 */ s8 controllerPort; // @unverified: copied from the roster's controllerPort
    /* 0x02 */ s8 partnerPanelIndex; // -1 for none (both panels of a COM Free Battle); a tag partner's panel is reset with this one
    /* 0x03 */ s8 sidebarTeam; // @unverified: which sidebar column (team 0/1) gets the pick icons
    /* 0x04 */ char unk04[0x1];
    /* 0x05 */ s8 state; // 0 picking, 1 confirm prompt, 2 level-sum notice, 3 ready (じゅんび かんりょう！, "Ready!", on the COM panel)
    /* 0x06 */ s8 redrawFrames; // @unverified: set to 2 on every change and counted down while the panel redraws
    /* 0x07 */ s8 unk_07;
    /* 0x08 */ s8 readyBlinkTimer; // @unverified: 0..0x3C cycle that fades the ready panel
    /* 0x09 */ s8 showingSummary; // 1 while R (かくにん, "Check") is held
    /* 0x0A */ s8 confirmCursor; // @unverified: D-pad left/right toggles it at the confirm prompt; 0 accepts, 1 picks again
    /* 0x0B */ s8 pickCount; // Pokémon picked so far (2 after B and C-Left)
    /* 0x0C */ s8 pickedSlots[6]; // party slots in pick order (B 0, C-Left 1, C-Up 2, A 3, C-Down 4, C-Right 5)
    /* 0x12 */ s16 x; // panel position given to BattleMenu_AddOrderSelectPanel (1P's panel 0x50, 0x21)
    /* 0x14 */ s16 y;
    /* 0x16 */ s8 candidateCount; // rosterInfo->numberOfPokemonCanBePicked (6)
    /* 0x17 */ char unk17[0x1];
    /* 0x18 */ BattleMon* candidates; // rosterInfo->battleMon
    /* 0x1C */ TeamRoster* roster;
} OrderSelectPanel; // size = 0x20

typedef struct unk_D_848035FC {
    /* 0x00 */ Color_RGB8 unk_00;
    /* 0x04 */ u8* unk_04;
} unk_D_848035FC; // size = 0x8

typedef struct unk_D_84803548 {
    /* 0x00 */ u16 unk_00;
    /* 0x02 */ u16 unk_02;
} unk_D_84803548; // size = 0x4

#define BTN_L           0x0020

#define BTN_R           0x0010

#define BTN_CUP         0x0008

#define BTN_CDOWN       0x0004

#define BTN_CLEFT       0x0002

#define BTN_CRIGHT      0x0001

#include "controller.h"

// battle_order_select.c
void BattleMenu_DrawBottomActionButtons(void);
void BattleMenu_DrawSidebarLeadIcon(s32 arg0, s32 arg1, OrderSidebarIcons* arg2);
s32 BattleMenu_DrawSidebarRowTypeIcon(s32 arg0, s32 arg1, s8 arg2, s8 arg3);
void BattleMenu_DrawTeamOrderSidebarTeam0(void);
void BattleMenu_DrawTeamOrderSidebarTeam1(void);
void BattleMenu_AppendOrderSlotIcon(s32 arg0, s32 arg1);
void BattleMenu_ResetOrderSlotIcons(s32 arg0);
void BattleMenu_DrawPanelBorder(s16 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4);
void BattleMenu_DrawOrderSelectPanel_Ready(OrderSelectPanel* arg0);
void BattleMenu_DrawConfirmButtonLabel(OrderSelectPanel* arg0);
void BattleMenu_DrawOrderSelectPanel(OrderSelectPanel* arg0);
s32 BattleMenu_IsSlotAlreadySelected(OrderSelectPanel* arg0, s8 arg1);
void BattleMenu_HandleOrderSelectPanel_PartyInput(Controller* arg0, OrderSelectPanel* arg1);
void BattleMenu_HandleOrderSelectPanel_ConfirmInput(Controller* arg0, OrderSelectPanel* arg1);
void BattleMenu_HandleOrderSelectPanel_LevelCapNoticeInput(Controller* arg0, OrderSelectPanel* arg1);
s32 BattleMenu_UpdateOrderSelectPanel(s32 arg0, OrderSelectPanel* arg1);
s32 BattleMenu_UpdateOrderSelect(s32 arg0);
void BattleMenu_SetLeadTagTeamMember(BattleSide* arg0, OrderSidebarIcons* arg1);
void BattleMenu_AppendUnpickedSlots(s8* arg0, s32 arg1);
void BattleMenu_CommitOrderSelection(void);
void BattleMenu_AddOrderSelectPanel(s16 arg0, s16 arg1, TeamRoster* arg2, s32 arg3, s32 arg4);
void BattleMenu_InitOrderSelectPanels(SessionContext* arg0);
s32 BattleMenu_RunOrderSelectScreen(s32 arg0, s32 arg1);

// functions defined in assembly
void BattleMenu_InitTeamOrderState(OrderSidebarIcons* arg0, BattleSide* arg1, s32 arg2);
void BattleMenu_SelectOrderSlot(OrderSelectPanel* arg0, s8 arg1, s32 arg2);

#endif // FRAGMENT_BATTLE_ORDER_SELECT_H
