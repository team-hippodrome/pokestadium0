/* Stadium Zero resident code. */
/* C ported from the Stadium 1 decomp: src/gb_data.c, src/pokemon_stats.c. */

#include "gb_data.h"
#include "string.h"
#include "gb_data.h"
#include "save_data.h"
#include "text_system.h"
#include "gb_tower.h"
#include "hal_libc.h"
#include "util.h"
extern const char sStatusNames[7][4];
extern const char sTypeNames[17][4];
extern const char sMoveNames[166][8];
extern SpeciesData gSpeciesData[152];
extern unk_D_80071D88 sStatusDisplayInfo[8];
extern char sMoveComments[165][8];
extern unk_D_80072338 gMoveDisplayInfo[166];
extern MoveData gMoveData[165];
extern char* D_8006B570[84];

#include "pokemon_stats.h"
#include "gb_data.h"
#include "save_data.h"
#include "text_system.h"
#include "gb_tower.h"
#include "hal_libc.h"
#include "util.h"
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

#include "m2c_macros.h"

u16 GbData_ReadU16BE(u8* arg0);
u32 GbData_ReadU24BE(u8* arg0);
void GbData_WriteU16BE(u8* arg0, s32 arg1);
void GbData_WriteU24BE(u8* arg0, s32 arg1);
char* Text_UntranscodeFixedName(char* arg0, char* arg1);
char* Text_CopySpeciesName(char* arg0, s32 arg1);
char* Text_GetTmHmName(s32 arg0, char* arg1);
void Pokemon_FromGbRecordExt(BattleMon* arg0, GbPokemonRecordExt* arg1);
void Pokemon_ToGbRecordExt(unk_func_88205880_00D0* arg0, GbPokemonRecordExt* arg1);
u16 StatExpSqrt(u16 square);
void func_80020188(void);
u16 GetPokemonDV(s32 statId, u16 dvBits);
u32 CalculateStatValue(s32 statId, s32 speciesId, u16 statModifier, u16 level, u16 dvBits);
void Pokemon_RecalcStats(BattleMon* arg0);
u16 Pokemon_StatExpForTarget(s32 arg0, s32 arg1, u16 arg2, u16 arg3, u16 arg4);
u32 Pokemon_ExpForLevel(s32 arg0, u16 arg1);
u16 Pokemon_LevelFromExp(s32 arg0, u32 arg1);
void Pokemon_PrepareBattleMon(BattleMon* arg0);
u8 Move_GetIdFromTableIndex(s32 tm_hm_index);
u8 func_80020984(s32 arg0);
u8 Species_FromInternalIndex(s32 arg0);
void Deck_InitializeSaveBackend(DeckHandle* arg0);
void Deck_InitializeBoxBackend(DeckHandle* arg0);
DeckHandle* Deck_Open(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
DeckHandle* Deck_OpenAndSetName(s32 arg0, s32 arg1, s32 arg2, s32 arg3, char* arg4, u16 arg5);
s32 Deck_CloseAndFlushBox(DeckHandle* arg0);

char* Text_UntranscodeName(char* arg0, char* arg1);
s8* Text_CopyString(s8* arg0, s8* arg1);
void Pokemon_FromGbRecord(BattleMon* arg0, GbPokemonRecord* arg1);
void Pokemon_ToGbRecord(s8 *arg0, s8 *arg1);
s32 Deck_WriteEntries(u8* arg0, s32 arg1, DeckHandle* arg2);
s32 GbSave_HasPlayerNameMarker(u8* arg0);
s32 Deck_GetCapacity(s32 arg0);
s32 Deck_GetEntrySize(s32 arg0);
s32 Deck_GetCount(s32 arg0, s32 arg1, s32 arg2);
void Deck_DeleteEntry(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

/** Reads a big-endian 16-bit value from a byte buffer. */
u16 GbData_ReadU16BE(u8* arg0) {
    return (arg0[0] << 8) | arg0[1];
}

/** Reads a big-endian 24-bit value from a byte buffer. */
u32 GbData_ReadU24BE(u8* arg0) {
    return (arg0[0] << 16) | (arg0[1] << 8) | arg0[2];
}

/** Writes a 16-bit value to a byte buffer in big-endian order. */
void GbData_WriteU16BE(u8* arg0, s32 arg1) {
    arg0[0] = (arg1 >> 8) & 0xFF;
    arg0[1] = arg1 & 0xFF;
}

/** Writes a 24-bit value to a byte buffer in big-endian order. */
void GbData_WriteU24BE(u8* arg0, s32 arg1) {
    arg0[0] = (arg1 >> 16) & 0xFF;
    arg0[1] = (arg1 >> 8) & 0xFF;
    arg0[2] = (arg1) & 0xFF;
}

extern char* D_80076FD0_jp;
extern u16 D_80076FD4_jp[0x100];
/**
 * Converts a Game Boy name (terminated by 0x50) to EUC-JP; code 0x5D expands to the
 * 10-byte trainer name D_80076FD0_jp points at.
 * Seen in play (2026-11-13) with a JP Green cart, the party, registration, Pokédex, list and sort
 * screens called it to build their names: the output buffers read サトシ (the trainer) and フシ (a
 * nickname), as shown on screen.
 */
char* Text_UntranscodeName(char* arg0, char* arg1) {
    char* sp34 = arg0;

    while (*arg1 != 'P') {
        if (*arg1 == ']') {
            memcpy(arg0, D_80076FD0_jp, 10);
            arg0 += 10;
        } else {
            *arg0++ = (D_80076FD4_jp[*arg1] >> 8) & 0xFF;
            *arg0++ = D_80076FD4_jp[*arg1] & 0xFF;
        }
        arg1++;
    }

    *arg0++ = '\x0';

    return sp34;
}

/**
 * Converts an EUC-JP name back to Game Boy character codes by searching D_80076FD4_jp;
 * the full-width space 0xA1A1 becomes 0x7F.
 * Not reached in play (2026-11-13): did not run in a tour of the main menu, Pokédex, party, Lab,
 * registration, Free Battle setup and a COM battle (opening, a switch, running, a Pound turn).
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
char* Text_TranscodeName(char* arg0, char* arg1) {
    char* sp1C = arg0;
    s32 i;
    u16 c;

    if (HAL_Strcmp(arg1, D_80076FD0_jp) == 0) {
        *arg0++ = ']';
    } else {
        while (*(s8*)arg1 != 0) {
            c = (((u8*)arg1)[0] << 8) | ((u8*)arg1)[1];
            if (c == 0xA1A1) {
                *arg0++ = 0x7F;
            } else {
                for (i = 0; i < 0x100; i++) {
                    if (c == D_80076FD4_jp[i]) {
                        *arg0++ = i;
                        break;
                    }
                }
            }
            arg1 += 2;
        }
    }

    *arg0++ = 'P';

    return sp1C;
}

/** Converts a fixed-length Game Boy name to the game's text encoding. */
char* Text_UntranscodeFixedName(char* arg0, char* arg1) {
    char sp18[6];

    _bcopy(arg1, sp18, 5);

    sp18[5] = 'P';

    return Text_UntranscodeName(arg0, sp18);
}

/**
 * Copies a two-byte EUC-JP string, clearing bit 0 of the first byte of katakana ヘ, ベ, ペ
 * (0xA5D8-0xA5DA) and リ (0xA5EA), which turns them into hiragana へ, べ, ぺ, り.
 * Seen in play (2026-11-13) (tour of menus and a COM battle): ran in the party screen,
 * registration, Free Battle setup and a switch in battle.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
s8* Text_CopyString(s8* arg0, s8* arg1) {
    s8* ret = arg0;
    u16 c;

    while (*arg1 != 0) {
        c = (((u8*)arg1)[0] << 8) | ((u8*)arg1)[1];
        if ((c == 0xA5EA) || ((c >= 0xA5D8) && (c < 0xA5DA))) {
            *arg0++ = *arg1++ & 0xFE;
        } else {
            *arg0++ = *arg1++;
        }
        *arg0++ = *arg1++;
    }

    *arg0 = 0;

    return ret;
}

/** Copies a species' name string into a buffer. */
char* Text_CopySpeciesName(char* arg0, s32 arg1) {
    Text_CopyString(arg0, (char*)*(u32*)D_80064C44[arg1]);
    return arg0;
}

/** Builds the name of a TM or HM into a buffer. */
char* Text_GetTmHmName(s32 arg0, char* arg1) {
    // "ひでんマシン%02d"
    static const char D_0007CCA0[] = { 164, 210, 164, 199, 164, 243, 165, 222, 165, 183,
                                       165, 243, 37, 48, 50, 100, 0, 0, 0, 0 };
    // "わざマシン%02d"
    static const char D_0007CCB4[] = { 164, 239, 164, 182, 165, 222, 165, 183,
                                       165, 243, 37, 48, 50, 100, 0, 0 };

    if ((arg0 > 0) && (arg0 < 84)) {
        HAL_Strcpy(arg1, D_8006B570[arg0 - 1]);
    } else if ((arg0 >= 196) && (arg0 < 201)) {
        sprintf(arg1, D_0007CCA0, arg0 - 195, arg0);
    } else if ((arg0 >= 201) && (arg0 < 0xFF)) {
        sprintf(arg1, D_0007CCB4, arg0 - 200, arg0);
    } else {
        HAL_Strcpy(arg1, D_8006B570[6]);
    }

    return arg1;
}

s16 func_8001FAB0(s8 *);                          /* extern */
s32 func_8001FAC8(s8 *);                          /* extern */
M2C_UNK func_80056690(s8 *, s8 *, M2C_UNK);     /* extern */

void func_8001FE84(s8 *arg0, s8 *arg1) {
    M2C_FIELD(arg0, s8 *, 0) = Species_FromInternalIndex(M2C_FIELD(arg1, u8 *, 0));
    M2C_FIELD(arg0, s8 *, 1) = 0;
    M2C_FIELD(arg0, s16 *, 2) = func_8001FAB0(arg1 + 1);
    M2C_FIELD(arg0, u8 *, 4) = (u8) M2C_FIELD(arg1, u8 *, 3);
    M2C_FIELD(arg0, u8 *, 5) = (u8) M2C_FIELD(arg1, u8 *, 4);
    M2C_FIELD(arg0, u8 *, 6) = (u8) M2C_FIELD(arg1, u8 *, 5);
    M2C_FIELD(arg0, u8 *, 7) = (u8) M2C_FIELD(arg1, u8 *, 6);
    M2C_FIELD(arg0, u8 *, 8) = (u8) M2C_FIELD(arg1, u8 *, 7);
    M2C_FIELD(arg0, s16 *, 0xE) = func_8001FAB0(arg1 + 0xC);
    M2C_FIELD(arg0, s32 *, 0x10) = func_8001FAC8(arg1 + 0xE);
    M2C_FIELD(arg0, s16 *, 0x14) = func_8001FAB0(arg1 + 0x11);
    M2C_FIELD(arg0, s16 *, 0x16) = func_8001FAB0(arg1 + 0x13);
    M2C_FIELD(arg0, s16 *, 0x18) = func_8001FAB0(arg1 + 0x15);
    M2C_FIELD(arg0, s16 *, 0x1A) = func_8001FAB0(arg1 + 0x17);
    M2C_FIELD(arg0, s16 *, 0x1C) = func_8001FAB0(arg1 + 0x19);
    M2C_FIELD(arg0, s16 *, 0x1E) = func_8001FAB0(arg1 + 0x1B);
    func_80056690(arg0 + 9, arg1 + 8, 4);
    func_80056690(arg0 + 0x20, arg1 + 0x1D, 4);
}

/** Converts an extended Game Boy Pokemon record to a battle Pokemon. */
void Pokemon_FromGbRecordExt(BattleMon* arg0, GbPokemonRecordExt* arg1) {
    Pokemon_FromGbRecord(arg0, &arg1->unk_00);
    arg0->level = arg1->unk_21;
    arg0->maxHp = GbData_ReadU16BE(arg1->unk_22);
    arg0->attack = GbData_ReadU16BE(arg1->unk_24);
    arg0->defense = GbData_ReadU16BE(arg1->unk_26);
    arg0->speed = GbData_ReadU16BE(arg1->unk_28);
    arg0->special = GbData_ReadU16BE(arg1->unk_2A);
}

M2C_UNK func_8001FAE8(s8 *, u16);                 /* extern */
M2C_UNK func_8001FAF8(s8 *, s32);                 /* extern */
M2C_UNK func_80056690(s8 *, s8 *, M2C_UNK);     /* extern */

/** Converts a battle Pokemon to a Game Boy Pokemon record. */
void Pokemon_ToGbRecord(s8 *arg0, s8 *arg1) {
    M2C_FIELD(arg1, s8 *, 0) = func_80020984(M2C_FIELD(arg0, u8 *, 0));
    func_8001FAE8(arg1 + 1, M2C_FIELD(arg0, u16 *, 2));
    M2C_FIELD(arg1, u8 *, 3) = (u8) M2C_FIELD(arg0, u8 *, 4);
    M2C_FIELD(arg1, u8 *, 4) = (u8) M2C_FIELD(arg0, u8 *, 5);
    M2C_FIELD(arg1, u8 *, 5) = (u8) M2C_FIELD(arg0, u8 *, 6);
    M2C_FIELD(arg1, u8 *, 6) = (u8) M2C_FIELD(arg0, u8 *, 7);
    M2C_FIELD(arg1, u8 *, 7) = (u8) M2C_FIELD(arg0, u8 *, 8);
    func_8001FAE8(arg1 + 0xC, M2C_FIELD(arg0, u16 *, 0xE));
    func_8001FAF8(arg1 + 0xE, M2C_FIELD(arg0, s32 *, 0x10));
    func_8001FAE8(arg1 + 0x11, M2C_FIELD(arg0, u16 *, 0x14));
    func_8001FAE8(arg1 + 0x13, M2C_FIELD(arg0, u16 *, 0x16));
    func_8001FAE8(arg1 + 0x15, M2C_FIELD(arg0, u16 *, 0x18));
    func_8001FAE8(arg1 + 0x17, M2C_FIELD(arg0, u16 *, 0x1A));
    func_8001FAE8(arg1 + 0x19, M2C_FIELD(arg0, u16 *, 0x1C));
    func_8001FAE8(arg1 + 0x1B, M2C_FIELD(arg0, u16 *, 0x1E));
    func_80056690(arg1 + 8, arg0 + 9, 4);
    func_80056690(arg1 + 0x1D, arg0 + 0x20, 4);
}

/** Converts a battle Pokemon to an extended Game Boy Pokemon record. */
void Pokemon_ToGbRecordExt(unk_func_88205880_00D0* arg0, GbPokemonRecordExt* arg1) {
    Pokemon_ToGbRecord(arg0->unk_000, arg1);
    arg1->unk_21 = arg0->unk_000[0].level;
    GbData_WriteU16BE(arg1->unk_22, arg0->unk_000[0].maxHp);
    GbData_WriteU16BE(arg1->unk_24, arg0->unk_000[0].attack);
    GbData_WriteU16BE(arg1->unk_26, arg0->unk_000[0].defense);
    GbData_WriteU16BE(arg1->unk_28, arg0->unk_000[0].speed);
    GbData_WriteU16BE(arg1->unk_2A, arg0->unk_000[0].special);
}

/** Returns the integer square root used for stat experience, found by search. */
u16 StatExpSqrt(u16 square) {
    u16 i;

    for (i = 1; i < 255; i++) {
        if (SQ(i) >= square) {
            break;
        }
    }
    return i;
}

void func_80020188(void) {
}

u16 GetPokemonDV(s32 stat_id, u16 dv_bits) { //GetPokemonDV
    u16 dv_value;

    switch (stat_id) {
        case STAT_HP: // HP DV (derived from the LSBs of other DVs)
            dv_value = ((dv_bits & 0x1000) >> 9)  // Special DV bit 0 → HP DV bit 0
                    | ((dv_bits & 0x0100) >> 6)  // Speed DV bit 0 → HP DV bit 1
                    | ((dv_bits & 0x0010) >> 3)  // Defense DV bit 0 → HP DV bit 2
                    | (dv_bits & 0x0001);        // Attack DV bit 0 → HP DV bit 3
            break;

        case STAT_SPECIAL: // Special DV
            dv_value = (dv_bits >> 12) & 0xF;
            break;

        case STAT_SPEED: // Speed DV
            dv_value = (dv_bits >> 8) & 0xF;
            break;

        case STAT_DEFENSE: // Defense DV
            dv_value = (dv_bits >> 4) & 0xF;
            break;

        case STAT_ATTACK: // Attack DV
            dv_value = dv_bits & 0xF;
            break;
    }

    return dv_value;
}

/** Calculates a stat from the base stat, DVs, stat experience and level. */
u32 CalculateStatValue(s32 stat_id, s32 species_id, u16 stat_modifier, u16 level, u16 dv_bits) {
    u16 stat_value;
    u16 base_stat;
    u16 dv_value;

    switch (stat_id) {
        case STAT_HP:
            base_stat = gBaseStats[species_id].baseHP;
            break;
        case STAT_SPECIAL:
            base_stat = gBaseStats[species_id].baseSpecial;
            break;
        case STAT_SPEED:
            base_stat = gBaseStats[species_id].baseSpeed;
            break;
        case STAT_DEFENSE:
            base_stat = gBaseStats[species_id].baseDefense;
            break;
        case STAT_ATTACK:
            base_stat = gBaseStats[species_id].baseAttack;
            break;
    }

    // Get the Pokémon's DV for the stat (or HP DV)
    dv_value = GetPokemonDV(stat_id, dv_bits);

    // Compute the preliminary stat value
    stat_value = (((StatExpSqrt(stat_modifier) / 4) + ((base_stat + dv_value) * 2)) * level) / 100;

    // Add final adjustments
    if (stat_id == STAT_HP) {
        stat_value += level + 10;
    } else {
        stat_value += 5;
    }

    // Cap at 999
    if (stat_value > 999) {
        stat_value = 999;
    }

    return stat_value;
}

/** Recalculates a Pokemon's level and all of its stats. */
void Pokemon_RecalcStats(BattleMon* arg0) {
    arg0->level = Pokemon_LevelFromExp(arg0->species.id, arg0->unk_10);
    arg0->maxHp = CalculateStatValue(1, arg0->species.id, arg0->unk_14, arg0->level, arg0->unk_1E);
    arg0->attack = CalculateStatValue(2, arg0->species.id, arg0->unk_16, arg0->level, arg0->unk_1E);
    arg0->defense = CalculateStatValue(3, arg0->species.id, arg0->unk_18, arg0->level, arg0->unk_1E);
    arg0->speed = CalculateStatValue(4, arg0->species.id, arg0->unk_1A, arg0->level, arg0->unk_1E);
    arg0->special = CalculateStatValue(5, arg0->species.id, arg0->unk_1C, arg0->level, arg0->unk_1E);
}

/** Searches for the stat experience that produces a target stat value. */
u16 Pokemon_StatExpForTarget(s32 arg0, s32 arg1, u16 arg2, u16 arg3, u16 arg4) {
    s32 i;
    s32 tmp;

    for (i = 1; i < 0xFFFF; i += 2) {
        tmp = CalculateStatValue(arg0, arg1, i + 2, arg3, arg4);
        if (arg2 < tmp) {
            break;
        }
    }

    return i;
}

/**
 * Returns the experience points needed to reach a level for the species'
 * growth rate.
 */
u32 Pokemon_ExpForLevel(s32 arg0, u16 arg1) {
    u32 sp4;

    switch (gBaseStats[arg0].unk_13) {
        case 0:
            sp4 = arg1 * arg1 * arg1;
            break;

        case 1:
            sp4 = (((arg1 * arg1 * arg1 * 3) / 4) + (arg1 * 10 * arg1)) - 30;
            break;

        case 2:
            sp4 = (((arg1 * arg1 * arg1 * 3) / 4) + (arg1 * 20 * arg1)) - 30;
            break;

        case 3:
            sp4 = ((((arg1 * arg1 * arg1 * 6) / 5) - (arg1 * 15 * arg1)) + (arg1 * 100)) - 140;
            break;

        case 4:
            sp4 = (arg1 * arg1 * arg1 * 4) / 5;
            break;

        case 5:
            sp4 = (arg1 * arg1 * arg1 * 5) / 4;
            break;
    }

    return sp4;
}

// The Japanese build compiles the functions from here through Deck_WriteEntries into the
// gb_data object (gb_data.c includes this file with POKEMON_STATS_HEAD_ONLY defined); the
// Japanese pokemon_stats object starts at GbSave_HasPlayerNameMarker.
/** Returns the level for an experience total. */
u16 Pokemon_LevelFromExp(s32 arg0, u32 arg1) {
    s32 i;

    for (i = 1; i < 100; i++) {
        if (arg1 < Pokemon_ExpForLevel(arg0, i + 1)) {
            break;
        }
    }

    return i;
}

/** Fills in a battle Pokemon's derived data before battle. */
void Pokemon_PrepareBattleMon(BattleMon* arg0) {
    s32 i;
    s32 temp_a3;
    s32 var_v0;
    s32 idx;

    Pokemon_RecalcStats(arg0);
    arg0->statusCondition = 0;
    arg0->hp = arg0->maxHp;

    for (i = 0; i < 4; i++) {
        if (arg0->moves[i] != 0) {
            temp_a3 = (arg0->pp[i] >> 6) & 3;
            var_v0 = gMoveData[arg0->moves[i] - 1].pp;

            if (var_v0 >= 0x28) {
                var_v0 = var_v0 + (temp_a3 * 7);
            } else {
                var_v0 = var_v0 + ((var_v0 / 5) * temp_a3);
            }

            arg0->pp[i] = (temp_a3 << 6) + var_v0;
        }
    }
}

/** Returns the move id for a TM or HM table index. */
u8 Move_GetIdFromTableIndex(s32 tm_hm_index) {
    extern u8 D_8006B8C4[];

    return D_8006B8C4[tm_hm_index];
}

u8 func_80020984(s32 arg0) {
    extern u8 D_8006B8FB[];

    return D_8006B8FB[arg0];
}

/** Converts a Game Boy internal species index to the species id. */
u8 Species_FromInternalIndex(s32 arg0) {
    extern u8 D_8006B993[];

    return D_8006B993[arg0];
}

extern s8 D_8006BA53;
u8 func_800209A4(s32 arg0) {
    return *(&D_8006BA53 + arg0);
}

extern s8 D_8006BAEB;
u8 func_800209B4(s32 arg0) {
    return *(&D_8006BAEB + arg0);
}

/** Initializes a deck that is stored in the save data. */
void Deck_InitializeSaveBackend(DeckHandle* arg0) {
    if (arg0->unk_00 == 1) {
        arg0->unk_04 |= 1;
        Deck_SetSaveEntryCount(arg0->unk_01, arg0->unk_03, 0);
    }

    arg0->unk_05 = Deck_GetSaveRecordSize(arg0->unk_01);
    arg0->unk_06 = Deck_GetSaveRecordCapacity(arg0->unk_01);
    arg0->unk_08 = Deck_GetSaveEntryCount(arg0->unk_01, arg0->unk_03);

    if (arg0->unk_00 == 2) {
        arg0->unk_0A = arg0->unk_08;
    } else {
        arg0->unk_0A = 0;
    }
}

/** Initializes a deck that is stored in a box. */
void Deck_InitializeBoxBackend(DeckHandle* arg0) {
    if (arg0->unk_00 == 1) {
        arg0->unk_04 |= 1;
        Deck_DeleteEntry(arg0->unk_01, arg0->unk_02, arg0->unk_03, 0);
    }

    arg0->unk_05 = Deck_GetEntrySize(arg0->unk_01);
    arg0->unk_06 = Deck_GetCapacity(arg0->unk_01);
    arg0->unk_08 = Deck_GetCount(arg0->unk_01, arg0->unk_02, arg0->unk_03);

    if (arg0->unk_00 == 2) {
        arg0->unk_0A = arg0->unk_08;
    } else {
        arg0->unk_0A = 0;
    }
}

/** Opens a deck handle for a save slot. */
DeckHandle* Deck_Open(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    DeckHandle* sp1C;

    sp1C = Util_Malloc(sizeof(DeckHandle));
    if (sp1C != NULL) {
        sp1C->unk_00 = arg3;
        sp1C->unk_01 = arg0;
        sp1C->unk_02 = arg1;
        sp1C->unk_03 = arg2;
        sp1C->unk_04 = 0;

        switch (arg0 & 0xF0) {
            case 16:
                Deck_InitializeSaveBackend(sp1C);
                break;

            case 32:
                Deck_InitializeBoxBackend(sp1C);
                break;
        }
    }

    return sp1C;
}

/** Opens a deck handle and sets its name. */
DeckHandle* Deck_OpenAndSetName(s32 arg0, s32 arg1, s32 arg2, s32 arg3, char* arg4, u16 arg5) {
    DeckHandle* sp24;
    DeckHandle* temp_v0;
    DeckHandle* var_v1;

    sp24 = Deck_Open(arg0, arg1, arg2, 1);
    if ((sp24 != NULL) && (arg0 & 0xF0)) {
        Deck_SetSaveEntryTrainerIdAndName(arg0, arg2, arg3, arg4, arg5);
    }
    return sp24;
}

/** Closes a deck handle, writing back a modified box. */
s32 Deck_CloseAndFlushBox(DeckHandle* arg0) {
    s32 sp1C = 0;

    if ((arg0->unk_01 & 0x10) && (arg0->unk_04 & 1)) {
        Save_InvalidateTypedRecord(arg0->unk_01, arg0->unk_03);
        sp1C = 1;
    }

    Util_Free(arg0);

    return sp1C;
}
