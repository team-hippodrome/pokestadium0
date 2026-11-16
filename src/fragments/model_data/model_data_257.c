/* Stadium Zero fragment257_B8BFE0: the Substitute doll model. */

#include "global.h"
#include "m2c_macros.h"
#include "model_data.h"

extern M2C_UNK sSubstituteDollModelHeader;

/**
 * Returns the Substitute doll model's header when `index` is 0, and NULL otherwise.
 * This fragment is file 151 of the model archive (ROM 0x500000), after the 151 species.
 * Seen in play: Free Battle, 1P Pikachu's first move poked to Substitute (0xA4); file 151
 * loaded the turn it ran, and the blue doll stood in Pikachu's place (ぶんしんが あらわれた).
 * Its header's species field reads 152 (SUBSTITUTE_DOLL).
 */
M2C_UNK *SubstituteDollModel_GetHeader(s32 index, UNUSED M2C_UNK arg1) {
    M2C_UNK *header;

    header = NULL;
    if (index == 0) {
        header = &sSubstituteDollModelHeader;
    }
    return header;
}
