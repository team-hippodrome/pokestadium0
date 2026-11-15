/* Stadium Zero fragment250_B2E0F0: Zapdos's model. */

#include "global.h"
#include "m2c_macros.h"
#include "model_data.h"

extern M2C_UNK sZapdosModelHeader;

/**
 * Returns Zapdos's model header when `index` is 0, and NULL otherwise.
 * This fragment is file 144 of the model archive (ROM 0x500000), which
 * Model_LoadForPokemon indexes by species - 1; Fragment_ProcessGeoLayout calls
 * it with (0, 0) and processes the geo layouts the header lists.
 * Seen in play: the Pokédex data view (データをみる) loaded this file for its species'
 * entry, and the model shown matched (2026-11-14, every entry No.001-151 swept).
 */
M2C_UNK *ZapdosModel_GetHeader(s32 index, UNUSED M2C_UNK arg1) {
    M2C_UNK *header;

    header = NULL;
    if (index == 0) {
        header = &sZapdosModelHeader;
    }
    return header;
}
