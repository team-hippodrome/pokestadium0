/* Stadium Zero fragment258_B91160: the Poké Ball model. */

#include "global.h"
#include "m2c_macros.h"
#include "model_data.h"

extern M2C_UNK sPokeBallModelHeader;

/**
 * Returns the Poké Ball model's header when `index` is 0, and NULL otherwise.
 * This fragment is file 152 of the model archive (ROM 0x500000), after the 151 species.
 * Seen in play: BattleScene_Init loads it with Model_LoadByArchiveIndex(0x99) for both
 * sides; overwriting its two textures in RAM (band texture green, button circle red)
 * recolored the ball that lands and opens at every send-out. Its header's species field
 * also reads 152.
 */
M2C_UNK *PokeBallModel_GetHeader(s32 index, UNUSED M2C_UNK arg1) {
    M2C_UNK *header;

    header = NULL;
    if (index == 0) {
        header = &sPokeBallModelHeader;
    }
    return header;
}
