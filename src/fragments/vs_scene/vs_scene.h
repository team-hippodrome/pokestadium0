/* Declarations for the vs_scene fragment (src/fragments/vs_scene/). */
#ifndef FRAGMENT_VS_SCENE_H
#define FRAGMENT_VS_SCENE_H

#include "global.h"
#include "game_state.h"

// One side's trainer panel on the VS screen (D_82203170[2]). The demo stadium geo fragments
// (geo_model_032/033) read the same array through D_80060490's callbackArg.
typedef struct VsSceneSide {
    /* 0x00 */ u8 teamLayout; // @unverified: VsScene_PrepareTeams sets 0 when ruleCategory != 0, 2 for a two-trainer side, else 1
    /* 0x01 */ char unk01[0x3];
    /* 0x04 */ void* trainerFile; // BinArchive file picked by rosterInfo[0]->trainerIndex in VsScene_PrepareTeams: the trainer portrait; swapping the two sides' pointers swapped the portraits in play
    /* 0x08 */ u8* iconImages[6]; // @unverified: PokeIcon_GetImage results for the side's Pokémon (VsScene_LoadTeamIcons)
    /* 0x20 */ u8* hpBarImages[6]; // @unverified: images of the D_82203210 render targets func_82201084 draws HP bars into
    /* 0x38 */ TeamRoster* teamMember[2];
    /* 0x40 */ ExtendedRosterInfo* rosterInfo[2];
} VsSceneSide; // size = 0x48

#define BTN_DLEFT       0x0200

#define BTN_DRIGHT      0x0100

// vs_scene.c
s32 Completion_LightAngleCallbackA(s32 arg0, GraphNode* arg1);

#endif // FRAGMENT_VS_SCENE_H
