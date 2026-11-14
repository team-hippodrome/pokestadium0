/* Declarations for the vs_scene fragment (src/fragments/vs_scene/). */
#ifndef FRAGMENT_VS_SCENE_H
#define FRAGMENT_VS_SCENE_H

#include "global.h"
#include "game_state.h"

// One side's trainer panel on the VS screen (D_82203170[2]). The demo stadium geo fragments
// (vs_trainer_panel, geo_model_033) read the same array through D_80060490's callbackArg.
typedef struct VsSceneSide {
    /* 0x00 */ u8 teamLayout; // @unverified: VsScene_PrepareTeams sets 0 when ruleCategory != 0, 2 for a two-trainer side, else 1
    /* 0x01 */ char unk01[0x3];
    /* 0x04 */ void* trainerFile; // BinArchive file picked by rosterInfo[0]->trainerIndex in VsScene_PrepareTeams: the trainer portrait; swapping the two sides' pointers swapped the portraits in play
    /* 0x08 */ u8* iconImages[6]; // PokeIcon_GetImage results for the side's Pokémon (VsScene_LoadTeamIcons, VsScene_LoadBroughtIcons); seen on the panels and the results board
    /* 0x20 */ u8* hpBarImages[6]; // images of the D_82203210 render targets VsScene_DrawHpBars draws HP bars into; seen draining on the results board
    /* 0x38 */ TeamRoster* teamMember[2];
    /* 0x40 */ ExtendedRosterInfo* rosterInfo[2];
} VsSceneSide; // size = 0x48

#define BTN_DLEFT       0x0200

#define BTN_DRIGHT      0x0100

// First argument of VsScene_Run.
typedef enum VsSceneKind {
    /* 0 */ VS_SCENE_PRE_BATTLE,           // VsScene_Play: title and trainer panel reveal
    /* 1 */ VS_SCENE_FREE_BATTLE_RESULTS,  // VsScene_PlayFreeBattleResults
    /* 2 */ VS_SCENE_TOURNAMENT_RESULTS    // VsScene_PlayTournamentResults: results, badge, next round
} VsSceneKind;

// vs_scene.c
s32 VsScene_LightFollowCameraCallback(s32 phase, GraphNode* node);

#endif // FRAGMENT_VS_SCENE_H
