/* Declarations for the gb_player_party_icons fragment (src/fragments/gb_player_party_icons/). */
#ifndef FRAGMENT_GB_PLAYER_PARTY_ICONS_H
#define FRAGMENT_GB_PLAYER_PARTY_ICONS_H

#include "global.h"

// gb_player_party_icons.c
void GbPlayer_LoadPartyFromDeck(s32 port);
s32 GbPlayer_PartyIconsFrameCallback(u8 fadeMode);
void GbPlayer_FillLaunchParams(GbPlayerLaunchParams* params);
s32 GbPlayer_PreparePartyIcons(s32 port, GbPlayerLaunchParams* params);

#endif // FRAGMENT_GB_PLAYER_PARTY_ICONS_H
