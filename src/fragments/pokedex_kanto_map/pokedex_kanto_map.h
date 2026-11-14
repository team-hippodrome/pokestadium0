/* Declarations for src/fragments/pokedex_kanto_map/. */
#ifndef POKEDEX_KANTO_MAP_H
#define POKEDEX_KANTO_MAP_H

#include "global.h"

// pokedex_kanto_map.c
Gfx* KantoMap_BuildSeaDisplayList(Gfx* gfx);
void KantoMap_SeaGeoCallback(s32 call_context, GeoDisplayListNode* node);
Gfx* KantoMap_BuildRiversDisplayList(Gfx* gfx);
void KantoMap_RiversGeoCallback(s32 call_context, GeoDisplayListNode* node);

#endif // POKEDEX_KANTO_MAP_H
