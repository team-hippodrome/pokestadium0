/* Declarations for the gb_tower_team_prep fragment (src/fragments/gb_tower_team_prep/). */
#ifndef FRAGMENT_GB_TOWER_TEAM_PREP_H
#define FRAGMENT_GB_TOWER_TEAM_PREP_H

#include "global.h"

// gb_tower_team_prep.c
void GbTower_LoadPartyFromDeck(s32 arg0);
s32 GbTower_TeamPrepFrameCallback(u8 arg0);
void GbTower_BuildPartyResult(GbTowerLaunchParams* arg0);
s32 GbTower_TeamPrep(s32 arg0, GbTowerLaunchParams* arg1);

#endif // FRAGMENT_GB_TOWER_TEAM_PREP_H
