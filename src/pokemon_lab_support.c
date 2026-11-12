/* Stadium Zero resident code. */
/* C ported from the Stadium 1 decomp: src/fragments/pokemon_lab_support/pokemon_lab_support.c. */

#include "fragments/pokemon_lab_support/pokemon_lab_support.h"
#include "gb_save.h"
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

s32 func_8001FA8C(s32 arg0)
{
  arg0 = arg0; // FAKE: self-assignment
  if (arg0 >= 0x14)
  {
    arg0 -= 0xB;
  }
  return arg0;
}
