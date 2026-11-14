/* Declarations for the gb_tower_team_prep fragment (src/fragments/gb_tower_team_prep/). */
#ifndef FRAGMENT_GB_TOWER_TEAM_PREP_H
#define FRAGMENT_GB_TOWER_TEAM_PREP_H

#include "global.h"

// gb_tower_team_prep.c
void GbTower_LoadPartyFromDeck(s32 port);
s32 GbTower_PartyIconsFrameCallback(u8 fadeMode);
void GbTower_FillLaunchParams(GbTowerLaunchParams* params);
s32 GbTower_PreparePartyIcons(s32 port, GbTowerLaunchParams* params);

#endif // FRAGMENT_GB_TOWER_TEAM_PREP_H
