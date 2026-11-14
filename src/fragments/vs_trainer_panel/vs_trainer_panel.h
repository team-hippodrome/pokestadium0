/* Declarations for src/fragments/vs_trainer_panel/ (fragment 032, the VS screen's trainer panels). */
#ifndef VS_TRAINER_PANEL_H
#define VS_TRAINER_PANEL_H

#include "global.h"
#include "fragments/geo_model_033/geo_model_033.h"

// vs_trainer_panel.c
s32 VsPanel_CheckBootCode(s32 displayList);
void VsPanel_SelectTitleRound(s32 event, GeoModelRootNode* node);
Gfx* VsPanel_WritePortraitGfx(Gfx* gfx, void* trainerFile);
void VsPanel_PortraitCallback(s32 event, DemoGeoNode* node);
void VsPanel_TitleTextCallback(s32 event, DemoGeoNode* node);
void VsPanel_NameTextCallback(s32 event, DemoGeoNode* node);
Gfx* VsPanel_WriteIconGfx(Gfx* gfx, void* iconImage);
void VsPanel_IconCallback(s32 event, DemoGeoNode *node);
void VsPanel_NicknameCallback(s32 event, DemoGeoNode* node);

#endif // VS_TRAINER_PANEL_H
