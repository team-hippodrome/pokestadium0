/* Stadium Zero fragment016_252E10. */
/* C ported from the Stadium 1 decomp: src/fragments/lab_pc_list/lab_pc_list_1E46B0.c. */

#include "lab_pokemon_list.h"
#include "gb_data.h"
extern Gfx D_8910D028[];

#include "m2c_macros.h"

s32 LabPCList_CompareByLevelAsc(LabMonEntry* a, LabMonEntry* b);
s32 LabPCList_CompareByLevelDesc(LabMonEntry* a, LabMonEntry* b);
s32 LabPCList_CompareByHpAsc(LabMonEntry* a, LabMonEntry* b);
s32 LabPCList_CompareByHpDesc(LabMonEntry* a, LabMonEntry* b);
s32 LabPCList_CompareByAttackAsc(LabMonEntry* a, LabMonEntry* b);
s32 LabPCList_CompareByAttackDesc(LabMonEntry* a, LabMonEntry* b);
s32 LabPCList_CompareByDefenseAsc(LabMonEntry* a, LabMonEntry* b);
s32 LabPCList_CompareByDefenseDesc(LabMonEntry* a, LabMonEntry* b);
s32 LabPCList_CompareBySpeedAsc(LabMonEntry* a, LabMonEntry* b);
s32 LabPCList_CompareBySpeedDesc(LabMonEntry* a, LabMonEntry* b);
s32 LabPCList_CompareBySpecialAsc(LabMonEntry* a, LabMonEntry* b);
s32 LabPCList_CompareBySpecialDesc(LabMonEntry* a, LabMonEntry* b);
s32 LabPCList_CompareById(LabMonEntry* a, LabMonEntry* b);
s32 LabPCList_CompareByNickname(LabMonEntry* a, LabMonEntry* b);
s32 LabPCList_CompareBySpeciesNumber(LabMonEntry* a, LabMonEntry* b);
int LabPCList_FilterByLevelRange(LabMonEntry* entryArg, u8* range);
s32 LabPCList_FilterByAnyType(LabMonEntry* entry, unk_func_8830867C_02C_C54_01C* filterArg);
s32 LabPCList_FilterByAnyMove(LabMonEntry* a0, unk_func_8830867C_02C_C54_024* a1);
s32 LabPCList_FilterBySpeciesId(LabMonEntry* entry, s32* species);
s32 LabPCList_FilterByExactTypePair(LabMonEntry* entry, unk_func_8830867C_02C_C54_014* filterArg);

s32 LabPCList_CompareByPointer(LabMonEntry* a, LabMonEntry* b);

/**
 * Tie-break comparison: by entry address, which is the order the sources were loaded in.
 * Seen in play (2026-11-14) in いちらん: ran under every sort.
 */
s32 LabPCList_CompareByPointer(LabMonEntry* a, LabMonEntry* b) {
    s32 var_v1 = a->unk_00->unk_00->unk_0C - b->unk_00->unk_00->unk_0C;

    if (var_v1 == 0) {
        var_v1 = a->unk_00->unk_04 - b->unk_00->unk_04;
        if (var_v1 == 0) {
            var_v1 = a->unk_04 - b->unk_04;
        }
    }
    return var_v1;
}

/** List comparison: level, ascending. */
s32 LabPCList_CompareByLevelAsc(LabMonEntry* a, LabMonEntry* b) {
    s32 var_v0 = a->mon.level - b->mon.level;
    s32 ret;

    if (var_v0 != 0) {
        ret = var_v0;
    } else {
        ret = LabPCList_CompareByPointer(a, b);
    }
    return ret;
}

/** List comparison: level, descending. */
s32 LabPCList_CompareByLevelDesc(LabMonEntry* a, LabMonEntry* b) {
    s32 var_v0 = b->mon.level - a->mon.level;
    s32 ret;

    if (var_v0 != 0) {
        ret = var_v0;
    } else {
        ret = LabPCList_CompareByPointer(a, b);
    }
    return ret;
}

/** List comparison: HP, ascending. */
s32 LabPCList_CompareByHpAsc(LabMonEntry* a, LabMonEntry* b) {
    s32 var_v0 = a->mon.maxHp - b->mon.maxHp;
    s32 ret;

    if (var_v0 != 0) {
        ret = var_v0;
    } else {
        ret = LabPCList_CompareByPointer(a, b);
    }
    return ret;
}

/** List comparison: HP, descending. */
s32 LabPCList_CompareByHpDesc(LabMonEntry* a, LabMonEntry* b) {
    s32 var_v0 = b->mon.maxHp - a->mon.maxHp;
    s32 ret;

    if (var_v0 != 0) {
        ret = var_v0;
    } else {
        ret = LabPCList_CompareByPointer(a, b);
    }
    return ret;
}

/** List comparison: Attack, ascending. */
s32 LabPCList_CompareByAttackAsc(LabMonEntry* a, LabMonEntry* b) {
    s32 var_v0 = a->mon.attack - b->mon.attack;
    s32 ret;

    if (var_v0 != 0) {
        ret = var_v0;
    } else {
        ret = LabPCList_CompareByPointer(a, b);
    }
    return ret;
}

/** List comparison: Attack, descending. */
s32 LabPCList_CompareByAttackDesc(LabMonEntry* a, LabMonEntry* b) {
    s32 var_v0 = b->mon.attack - a->mon.attack;
    s32 ret;

    if (var_v0 != 0) {
        ret = var_v0;
    } else {
        ret = LabPCList_CompareByPointer(a, b);
    }
    return ret;
}

/** List comparison: Defense, ascending. */
s32 LabPCList_CompareByDefenseAsc(LabMonEntry* a, LabMonEntry* b) {
    s32 var_v0 = a->mon.defense - b->mon.defense;
    s32 ret;

    if (var_v0 != 0) {
        ret = var_v0;
    } else {
        ret = LabPCList_CompareByPointer(a, b);
    }
    return ret;
}

/** List comparison: Defense, descending. */
s32 LabPCList_CompareByDefenseDesc(LabMonEntry* a, LabMonEntry* b) {
    s32 var_v0 = b->mon.defense - a->mon.defense;
    s32 ret;

    if (var_v0 != 0) {
        ret = var_v0;
    } else {
        ret = LabPCList_CompareByPointer(a, b);
    }
    return ret;
}

/** List comparison: Speed, ascending. */
s32 LabPCList_CompareBySpeedAsc(LabMonEntry* a, LabMonEntry* b) {
    s32 var_v0 = a->mon.speed - b->mon.speed;
    s32 ret;

    if (var_v0 != 0) {
        ret = var_v0;
    } else {
        ret = LabPCList_CompareByPointer(a, b);
    }
    return ret;
}

/** List comparison: Speed, descending. */
s32 LabPCList_CompareBySpeedDesc(LabMonEntry* a, LabMonEntry* b) {
    s32 var_v0 = b->mon.speed - a->mon.speed;
    s32 ret;

    if (var_v0 != 0) {
        ret = var_v0;
    } else {
        ret = LabPCList_CompareByPointer(a, b);
    }
    return ret;
}

/** List comparison: Special, ascending. */
s32 LabPCList_CompareBySpecialAsc(LabMonEntry* a, LabMonEntry* b) {
    s32 var_v0 = a->mon.special - b->mon.special;
    s32 ret;

    if (var_v0 != 0) {
        ret = var_v0;
    } else {
        ret = LabPCList_CompareByPointer(a, b);
    }
    return ret;
}

/** List comparison: Special, descending. */
s32 LabPCList_CompareBySpecialDesc(LabMonEntry* a, LabMonEntry* b) {
    s32 var_v0 = b->mon.special - a->mon.special;
    s32 ret;

    if (var_v0 != 0) {
        ret = var_v0;
    } else {
        ret = LabPCList_CompareByPointer(a, b);
    }
    return ret;
}

/** List comparison: by ID. */
s32 LabPCList_CompareById(LabMonEntry* a, LabMonEntry* b) {
    s32 var_v0 = a->mon.otId - b->mon.otId;
    s32 ret;

    if (var_v0 != 0) {
        ret = var_v0;
    } else {
        ret = LabPCList_CompareByPointer(a, b);
    }
    return ret;
}

/**
 * List comparison: by location (party, then GB boxes, then 64 boxes, in load order). Also the default order.
 * Seen in play (2026-11-14) in いちらん: ばしょでならべる ordered the list てもち, GB 1, GB 2.
 */
s32 LabPCList_CompareByLocation(LabMonEntry* a, LabMonEntry* b) {
    return LabPCList_CompareByPointer(a, b);
}

/**
 * Seen in play (2026-11-12) in いちらん: ran when the list was sorted from the おや (OT) column's
 * popup.
 */
s32 LabPCList_CompareByOtName(LabMonEntry* a, LabMonEntry* b) {
    s32 var_v0;
    s32 ret;

    var_v0 = Text_CompareGlyphCodes(a->mon.otName, b->mon.otName);
    if (var_v0 != 0) {
        ret = var_v0;
    } else {
        ret = LabPCList_CompareByPointer(a, b);
    }
    return ret;
}

/** List comparison: by nickname. */
s32 LabPCList_CompareByNickname(LabMonEntry* a, LabMonEntry* b) {
    s32 var_v0;
    s32 ret;

    var_v0 = Text_CompareGlyphCodes(a->mon.nickname, b->mon.nickname);
    if (var_v0 != 0) {
        ret = var_v0;
    } else {
        ret = LabPCList_CompareByPointer(a, b);
    }
    return ret;
}

typedef struct LabNameEntryZ {
    /* 0x00 */ u8 pad00[4];
    /* 0x04 */ u8* name;
    /* 0x08 */ u8 pad08[0x14];
} LabNameEntryZ; // size = 0x1C
extern LabNameEntryZ D_80064C5C[];
s32 Text_CompareGlyphCodes(u8*, u8*);

/**
 * List comparison: by species name in kana order.
 * Seen in play (2026-11-14) in いちらん: アイウエオじゅんにならべる ordered イシツブテ, カビゴン, コイキング, ...
 */
s32 LabPCList_CompareBySpeciesName(u8* a, u8* b) {
    s32 ret;
    s32 var_v1;

    ret = Text_CompareGlyphCodes(D_80064C5C[a[8] - 1].name, D_80064C5C[b[8] - 1].name);
    if (ret != 0) {
        var_v1 = ret;
    } else {
        var_v1 = LabPCList_CompareByPointer((LabMonEntry*)a, (LabMonEntry*)b);
    }
    return var_v1;
}

/**
 * List comparison: by Pokédex number.
 * Seen in play (2026-11-14) in いちらん: ポケモンばんごうでならべる ordered フシギダネ, ヒトカゲ, ゼニガメ, ポッポ, コラッタ, ピカチュウ, プリン, ...
 */
s32 LabPCList_CompareBySpeciesNumber(LabMonEntry* a, LabMonEntry* b) {
    s32 var_v0 = a->mon.species.id - b->mon.species.id;
    s32 ret;

    if (var_v0 != 0) {
        ret = var_v0;
    } else {
        ret = LabPCList_CompareByPointer(a, b);
    }
    return ret;
}

/** List filter: keeps entries whose level is in a range. */
int LabPCList_FilterByLevelRange(LabMonEntry* entry_arg, u8* range) {
    LabMonEntry* entry = entry_arg;
    return (entry->mon.level >= range[0]) && (range[1] >= entry->mon.level);
}

/** List filter: keeps entries with any of the given types. */
s32 LabPCList_FilterByAnyType(LabMonEntry* entry, unk_func_8830867C_02C_C54_01C* filter_arg) {
    UNUSED s32 pad; // FAKE: stack padding
    s32 i;
    s32 j;
    s32 var_v1;
    unk_func_8830867C_02C_C54_01C* filter = filter_arg;
    s32 idx = entry->mon.species.id - 1;
    u8 spC[2];

    spC[0] = gSpeciesData[idx].type1;
    spC[1] = gSpeciesData[idx].type2;

    if (spC[0] == spC[1]) {
        var_v1 = 1;
    } else {
        var_v1 = 2;
    }

    for (i = 0; i < filter->unk_00; i++) {
        for (j = 0; j < var_v1; j++) {
            if (filter->unk_04[i] == spC[j]) {
                break;
            }
        }

        if (j >= var_v1) {
            return 0;
        }
    }

    return 1;
}

/** List filter: keeps entries that know any of the given moves. */
s32 LabPCList_FilterByAnyMove(LabMonEntry* entry_arg, unk_func_8830867C_02C_C54_024* filter_arg) {
    LabMonEntry* entry = entry_arg;
    unk_func_8830867C_02C_C54_024* filter = filter_arg;
    s32 i;
    s32 j;
    s32 temp_v0 = BattleMon_CountMoves(&entry->mon);

    for (i = 0; i < filter->unk_04; i++) {
        for (j = 0; j < temp_v0; j++) {
            if (filter->unk_00[i] == entry->mon.moves[j]) {
                break;
            }
        }

        if (j >= temp_v0) {
            return 0;
        }
    }

    return 1;
}

/** List filter: keeps entries of the given species. */
s32 LabPCList_FilterBySpeciesId(LabMonEntry* entry, s32* species) {
    return entry->mon.species.id == *species;
}

/** List filter: keeps entries with exactly the given pair of types. */
s32 LabPCList_FilterByExactTypePair(LabMonEntry* entry, unk_func_8830867C_02C_C54_014* filter_arg) {
    UNUSED s32 pad; // FAKE: stack padding
    s32 i;
    s32 j;
    s32 var_v1;
    unk_func_8830867C_02C_C54_014* filter = filter_arg;
    s32 idx = entry->mon.species.id - 1;
    s32 sp8[2];

    sp8[0] = gSpeciesData[idx].type1;
    sp8[1] = gSpeciesData[idx].type2;

    if (sp8[0] == sp8[1]) {
        var_v1 = 1;
    } else {
        var_v1 = 2;
    }

    if (var_v1 != filter->unk_00) {
        return 0;
    }

    for (i = 0; i < filter->unk_00; i++) {
        for (j = 0; j < var_v1; j++) {
            if (filter->unk_04[i] == sp8[j]) {
                break;
            }
        }

        if (j >= var_v1) {
            return 0;
        }
    }

    return 1;
}

extern M2C_UNK D_80064C4C;
/**
 * List filter: keeps the species that Free Battle accepts (bit 0 of the species table's flags at +0xC).
 * Seen in play (2026-11-14) in いちらん: バトルようのポケモンをあつめる left only ピカチュウ and カビゴン of twelve.
 * D_80064C4C + species * 0x1C is the flags byte of the Free Battle species table D_80064C5C.
 * Matching note: the table is indexed through a byte pointer; the untyped word extern would scale
 * the 0x1C stride by 4 and read a word.
 */
s32 LabPCList_FilterByBattleEligible(void *entry, M2C_UNK unused) {
    return (*((u8 *)&D_80064C4C + (M2C_FIELD(entry, u8 *, 8) * 0x1C)) & 1) != 0;
}
