/* Declarations for src/fragments/vs_results_board/ (fragment 033, the VS scene results board). */
#ifndef FRAGMENT_VS_RESULTS_BOARD_H
#define FRAGMENT_VS_RESULTS_BOARD_H

#include "global.h"
#include "game_state.h"
#include "fragments/vs_scene/vs_scene.h"

// Geo callback node; callbackArg holds a team index, or (team << 16) | slot.
typedef struct DemoGeoNode {
    /* 0x00 */ GraphNode node;
    /* 0x18 */ Gfx* displayList; // @unverified: built by the geo callbacks as in GeoDisplayListNode
    /* 0x1C */ char unk1C[0x4];
    /* 0x20 */ s16 unk_20;
    /* 0x22 */ s16 unk_22;
    /* 0x24 */ void* unk_24;
} DemoGeoNode;

// vs_results_board.c
s32 VsResults_CheckBootCode(s32 display_list);
Gfx* VsResults_WritePortraitGfx(Gfx* gfx, void* trainer_file);
void VsResults_PortraitCallback(s32 event, DemoGeoNode* node);
void VsResults_TitleTextCallback(s32 event, DemoGeoNode* node);
void VsResults_NameTextCallback(s32 event, DemoGeoNode* node);
void VsResults_NicknameCallback(s32 event, DemoGeoNode* node);
void VsResults_SelectLayout(s32 event, GeoModelRootNode* node);
Gfx* VsResults_WriteRowIconGfx(Gfx* gfx, void* icon_image);
void VsResults_RowIconCallback(s32 event, DemoGeoNode* node);
Gfx* VsResults_WriteGridIconGfx(Gfx* gfx, void* icon_image);
void VsResults_GridIconCallback(s32 event, DemoGeoNode* node);
Gfx* VsResults_WriteHpBarGfx(Gfx* gfx, void* hp_bar_image);
void VsResults_HpBarCallback(s32 event, DemoGeoNode* node);

#endif // FRAGMENT_VS_RESULTS_BOARD_H
