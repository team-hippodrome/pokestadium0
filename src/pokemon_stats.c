/* Stadium Zero resident code. */
/* C ported from the Stadium 1 decomp: src/pokemon_stats.c. */

#include "pokemon_stats.h"
#include "save_data.h"
#include "util.h"
#include "m2c_macros.h"
extern u8 D_8006B8C4[0x420];
typedef struct unk_func_800228F0_sp24 {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ u16 unk_02;
    /* 0x04 */ char unk_04[0x10];
    /* 0x14 */ char unk_14[0x8];
} unk_func_800228F0_sp24;
extern u8 gDexToInternalIndex[];
extern u8 gInternalIndexToDex[];
extern u32 D_800AD330;
extern u8 D_800AD334;
extern u8 D_800AD335;
extern GbSaveMainData D_800AD338;

s32 Deck_CloseAndFlush(DeckHandle* arg0);
s32 Deck_ReadEntries(u8* arg0, s32 arg1, DeckHandle* arg2);
s32 Deck_WriteEntries(u8* arg0, s32 arg1, DeckHandle* arg2);

s32 Deck_GetCount(s32 arg0, s32 arg1, s32 arg2);
s32 Deck_ReadEntry(s32 arg0, s32 arg1, s32 arg2, s32 arg3, BattleMon* arg4);
s32 Deck_WriteEntry(s32 arg0, s32 arg1, s32 arg2, s32 arg3, BattleMon* arg4);

/** Closes a deck handle, writing back changes. */
s32 Deck_CloseAndFlush(DeckHandle* arg0) {
    s32 sp1C = 0;

    if ((arg0->deckType & 0x10) && (arg0->flags & 1)) {
        Save_CommitTypedRecord(arg0->deckType, arg0->index);
        sp1C = 1;
    }

    Util_Free(arg0);

    return sp1C;
}

void func_80020CC8(s32 *arg0, s32 arg1) {
    if (M2C_FIELD(arg0, s16 *, 8) >= arg1) {
        M2C_FIELD(arg0, s16 *, 0xA) = arg1;
    }
}

/** Reads the entries of a deck. */
s32 Deck_ReadEntries(u8* arg0, s32 arg1, DeckHandle* arg2) {
    s32 var_s3;
    s32 var_s4;
    s32 var_v1;
    s32 tmp;

    var_s4 = 0;
    var_s3 = arg1 - 1;
    tmp = arg1 > 0;

    if (tmp) {}  // karodo

    if (tmp != 0) {
        for (; arg2->cursor < arg2->count;) {
            var_v1 = 0;
            switch (arg2->deckType & 0xF0) {
                case 16:
                    var_v1 = Deck_ReadSaveEntry(arg2->deckType, arg2->index, arg2->cursor, arg0);
                    break;

                case 32:
                    var_v1 = Deck_ReadEntry(arg2->deckType, arg2->port, arg2->index, arg2->cursor, arg0);
                    break;
            }

            tmp = var_s3 > 0;
            if (var_v1 == 0) {
                break;
            }

            arg2->cursor++;
            var_s3 -= 1;
            var_s4 += 1;
            arg0 += arg2->entrySize;

            if (!tmp) {
                break;
            }
        }
    }
    return var_s4;
}

/** Writes the entries of a deck. */
s32 Deck_WriteEntries(u8* arg0, s32 arg1, DeckHandle* arg2) {
    s32 var_s2;
    s32 var_s4;
    s32 var_s5;
    s32 tmp;

    var_s5 = 0;
    var_s4 = arg1 - 1;
    tmp = arg1 > 0;

    if (tmp) {}  // karodo

    if (tmp) {
        for (; arg2->cursor < arg2->capacity;) {
            var_s2 = 0;
            switch (arg2->deckType & 0xF0) {
                case 16:
                    var_s2 = Save_WriteTypedRecord(arg2->deckType, arg2->index, arg2->cursor, arg0);
                    arg2->count = Deck_GetSaveEntryCount(arg2->deckType, arg2->index);
                    break;

                case 32:
                    var_s2 = Deck_WriteEntry(arg2->deckType, arg2->port, arg2->index, arg2->cursor, arg0);
                    arg2->count = Deck_GetCount(arg2->deckType, arg2->port, arg2->index);
                    break;
            }

            tmp = var_s4 > 0;
            if (var_s2 == 0) {
                break;
            }

            var_s4 -= 1;
            arg2->cursor++;
            var_s5 += 1;
            arg0 += arg2->entrySize;
            arg2->flags |= 1;

            if (!tmp) {
                break;
            }
        }
    }

    return var_s5;
}
