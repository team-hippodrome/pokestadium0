/* Declarations for the battle_order_select fragment (src/fragments/battle_order_select/). */
#ifndef FRAGMENT_BATTLE_ORDER_SELECT_H
#define FRAGMENT_BATTLE_ORDER_SELECT_H

#include "global.h"
#include "game_state.h"

typedef struct OrderSidebarIcons {
    /* 0x00 */ s8 iconCount; // pick balls so far; BattleMenu_AddSidebarPickBall appends at this index (0 after L in play)
    /* 0x01 */ s8 isCom; // the single trainer's isHuman has bit 1 set (2 = COM); selects the COM badge, seen on side 1
    /* 0x02 */ s8 slotIcons[6]; // per pick slot: high nibble picking port + 1, low nibble grow frame 0-3 (0x13 after 1P's pick); -1 marks slots 3-5 unused under tournament rules
    /* 0x08 */ s8 slotIconGrowth[6]; // 1 grow, -1 shrink (all -1 after L in play), passed to BattleMenu_DrawSidebarPickBall
    /* 0x0E */ s8 firstPort; // lower controller port of the side's trainers (0 for 1P in play)
    /* 0x0F */ s8 secondPort; // the other tag partner's port, -1 without one (-1 in play)
} OrderSidebarIcons; // size = 0x10

typedef struct OrderSelectPanel {
    /* 0x00 */ s8 panelIndex; // index in D_82302B48, set by BattleMenu_AddOrderSelectPanel (0 1P, 1 COM in play)
    /* 0x01 */ s8 controllerPort; // copied from the roster's controllerPort (0 for 1P, 1 for COM in play)
    /* 0x02 */ s8 partnerPanelIndex; // -1 for none (both panels of a COM Free Battle); a tag partner's panel is reset with this one
    /* 0x03 */ s8 sidebarTeam; // which sidebar column (team 0/1) gets the pick icons; with 1P's poked to 1 its first pick put no ball in the 1P column
    /* 0x04 */ char unk04[0x1];
    /* 0x05 */ s8 state; // 0 picking, 1 confirm prompt, 2 level-sum notice, 3 ready (じゅんび かんりょう！, "Ready!", on the COM panel)
    /* 0x06 */ s8 redrawFrames; // set to 2 on every change and counted down while BattleMenu_DrawOrderSelectPanel redraws the panel
    /* 0x07 */ s8 popupEraseFrames; // frames left repainting the prompt box with the background (set to 2 while a prompt shows); erased the closed level-sum notice in play
    /* 0x08 */ s8 readyBlinkTimer; // @unverified: 0..0x3C cycle that pulses a tag-team panel's ready text (tag teams not seen in play)
    /* 0x09 */ s8 highlightPicks; // 1 while R (かくにん, "Check") is held: picked names turn yellow
    /* 0x0A */ s8 confirmCursor; // at the これで いいですか？ (OK?) prompt: 0 はい (Yes), 1 えらびなおす (pick again); D-Right/D-Left toggled it in play
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
void BattleMenu_DrawScrollingInstructionPanel(void);
void BattleMenu_InitOrderSidebar(OrderSidebarIcons* sidebar, BattleSide* side, s32 rule_category);
void BattleMenu_DrawSidebarTrainerBadge(s32 x, s32 y, OrderSidebarIcons* sidebar);
s32 BattleMenu_DrawSidebarPickBall(s32 x, s32 y, s8 icon, s8 growth);
void BattleMenu_DrawTeamOrderSidebarTeam0(void);
void BattleMenu_DrawTeamOrderSidebarTeam1(void);
void BattleMenu_AddSidebarPickBall(s32 sidebar_team, s32 controller_port);
void BattleMenu_ShrinkSidebarPickBalls(s32 sidebar_team);
void BattleMenu_DrawPanelBorder(s16 x, s16 y, s16 width, s16 height, s16 controller_port);
void BattleMenu_DrawOrderSelectPartyGrid(OrderSelectPanel* panel);
void BattleMenu_DrawOrderSelectConfirmPrompt(OrderSelectPanel* panel);
void BattleMenu_DrawLevelSumOverNotice(OrderSelectPanel* panel);
void BattleMenu_DrawOrderSelectPanel_Ready(OrderSelectPanel* panel);
void BattleMenu_DrawTrainerNameLabel(OrderSelectPanel* panel);
void BattleMenu_DrawOrderSelectPanel(OrderSelectPanel* panel);
void BattleMenu_FeedScriptedComOrderInput(void);
s32 BattleMenu_IsSlotAlreadySelected(OrderSelectPanel* panel, s8 slot);
s32 BattleMenu_OrderExceedsLevelSumLimit(OrderSelectPanel* panel);
s32 BattleMenu_IsOrderComplete(OrderSelectPanel* panel);
void BattleMenu_PickOrderSlot(OrderSelectPanel* panel, s8 slot);
void BattleMenu_UndoSelections(OrderSelectPanel* panel);
void BattleMenu_HandleOrderSelectPanel_PartyInput(Controller* cont, OrderSelectPanel* panel);
void BattleMenu_HandleOrderSelectPanel_ConfirmInput(Controller* cont, OrderSelectPanel* panel);
void BattleMenu_HandleOrderSelectPanel_LevelSumNoticeInput(Controller* cont, OrderSelectPanel* panel);
s32 BattleMenu_UpdateOrderSelectPanel(s32 fade_mode, OrderSelectPanel* panel);
s32 BattleMenu_UpdateOrderSelect(s32 fade_mode);
void BattleMenu_SetLeadTagTeamMember(BattleSide* side, OrderSidebarIcons* sidebar);
void BattleMenu_AppendUnpickedSlots(s8* order, s32 count);
void BattleMenu_CommitOrderSelection(void);
void BattleMenu_AddOrderSelectPanel(s16 x, s16 y, TeamRoster* roster, s32 sidebar_team, s32 partner_panel_index);
void BattleMenu_InitOrderSelectPanels(SessionContext* session);
s32 BattleMenu_RunOrderSelectScreen(s32 arg0, s32 session);

#endif // FRAGMENT_BATTLE_ORDER_SELECT_H
