/* Stadium Zero resident code. */
/* C ported from the Stadium 1 decomp: src/fragments/pokemon_lab_support/pokemon_lab_support.c. */

#include "pokemon_lab_support.h"
#include "m2c_macros.h"

s32 LabPC_StatusToIconIndex(s32 arg0);

/** Converts a status condition bit mask to a status icon index. */
s32 LabPC_StatusToIconIndex(s32 arg0) {
    s32 v1;
    if (arg0 & 7) {
        v1 = 2;
    }
    else if (arg0 & 8) {
        v1 = 3;
    }
    else if (arg0 & 0x10) {
        v1 =  4;
    }
    else if (arg0 & 0x20) {
        v1 =  5;
    }
    else if (arg0 & 0x40) {
        v1 =  6;
    }
    else {
        v1 = 0;
    }
    return v1;
}

/**
 * Maps a move type id to its slot in the type-indexed tables: the Gen 1 type ids skip 9..19, so
 * ids 20 and up (Fire..Dragon) move down by 11. Used for the type icon and the move backdrop in the
 * party summary. @unverified: table layout inferred from the type ids.
 */
s32 Type_ToTableIndex(s32 type)
{
  type = type; // FAKE: self-assignment
  if (type >= 0x14)
  {
    type -= 0xB;
  }
  return type;
}
