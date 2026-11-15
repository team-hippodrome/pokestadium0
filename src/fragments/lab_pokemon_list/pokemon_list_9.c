/* Stadium Zero fragment016_252E10. */
/* C ported from the Stadium 1 decomp: src/fragments/lab_pc_list/lab_pc_list_1E46B0.c. */

#include "lab_pokemon_list.h"
#include "gb_data.h"
extern Gfx D_8910D028[];

#include "m2c_macros.h"

s32 LabPCList_CompareByLevelAsc(LabMonEntry* arg0, LabMonEntry* arg1);
s32 LabPCList_CompareByLevelDesc(LabMonEntry* arg0, LabMonEntry* arg1);
s32 LabPCList_CompareByHpAsc(LabMonEntry* arg0, LabMonEntry* arg1);
s32 LabPCList_CompareByHpDesc(LabMonEntry* arg0, LabMonEntry* arg1);
s32 LabPCList_CompareByAttackAsc(LabMonEntry* arg0, LabMonEntry* arg1);
s32 LabPCList_CompareByAttackDesc(LabMonEntry* arg0, LabMonEntry* arg1);
s32 LabPCList_CompareByDefenseAsc(LabMonEntry* arg0, LabMonEntry* arg1);
s32 LabPCList_CompareByDefenseDesc(LabMonEntry* arg0, LabMonEntry* arg1);
s32 LabPCList_CompareBySpeedAsc(LabMonEntry* arg0, LabMonEntry* arg1);
s32 LabPCList_CompareBySpeedDesc(LabMonEntry* arg0, LabMonEntry* arg1);
s32 LabPCList_CompareBySpecialAsc(LabMonEntry* arg0, LabMonEntry* arg1);
s32 LabPCList_CompareBySpecialDesc(LabMonEntry* arg0, LabMonEntry* arg1);
s32 LabPCList_CompareById(LabMonEntry* arg0, LabMonEntry* arg1);
s32 LabPCList_CompareByNickname(LabMonEntry* arg0, LabMonEntry* arg1);
s32 LabPCList_CompareBySpeciesRawId(LabMonEntry* arg0, LabMonEntry* arg1);
int LabPCList_FilterByLevelRange(LabMonEntry* a0, u8* arg1);
s32 LabPCList_FilterByAnyType(LabMonEntry* arg0, unk_func_8830867C_02C_C54_01C* a1);
s32 LabPCList_FilterByAnyMove(LabMonEntry* a0, unk_func_8830867C_02C_C54_024* a1);
s32 LabPCList_FilterBySpeciesId(LabMonEntry* arg0, s32* arg1);
s32 LabPCList_FilterByExactTypePair(LabMonEntry* arg0, unk_func_8830867C_02C_C54_014* a1);

s32 LabPCList_CompareByPointer(LabMonEntry* arg0, LabMonEntry* arg1);

s32 func_891091C0(LabMonEntry* arg0, LabMonEntry* arg1) {
    s32 var_v1 = arg0->unk_00->unk_00->unk_0C - arg1->unk_00->unk_00->unk_0C;

    if (var_v1 == 0) {
        var_v1 = arg0->unk_00->unk_04 - arg1->unk_00->unk_04;
        if (var_v1 == 0) {
            var_v1 = arg0->unk_04 - arg1->unk_04;
        }
    }
    return var_v1;
}

/** List comparison: level, ascending. */
s32 LabPCList_CompareByLevelAsc(LabMonEntry* arg0, LabMonEntry* arg1) {
    s32 var_v0 = arg0->mon.level - arg1->mon.level;
    s32 ret;

    if (var_v0 != 0) {
        ret = var_v0;
    } else {
        ret = LabPCList_CompareByPointer(arg0, arg1);
    }
    return ret;
}

/** List comparison: level, descending. */
s32 LabPCList_CompareByLevelDesc(LabMonEntry* arg0, LabMonEntry* arg1) {
    s32 var_v0 = arg1->mon.level - arg0->mon.level;
    s32 ret;

    if (var_v0 != 0) {
        ret = var_v0;
    } else {
        ret = LabPCList_CompareByPointer(arg0, arg1);
    }
    return ret;
}

/** List comparison: HP, ascending. */
s32 LabPCList_CompareByHpAsc(LabMonEntry* arg0, LabMonEntry* arg1) {
    s32 var_v0 = arg0->mon.maxHp - arg1->mon.maxHp;
    s32 ret;

    if (var_v0 != 0) {
        ret = var_v0;
    } else {
        ret = LabPCList_CompareByPointer(arg0, arg1);
    }
    return ret;
}

/** List comparison: HP, descending. */
s32 LabPCList_CompareByHpDesc(LabMonEntry* arg0, LabMonEntry* arg1) {
    s32 var_v0 = arg1->mon.maxHp - arg0->mon.maxHp;
    s32 ret;

    if (var_v0 != 0) {
        ret = var_v0;
    } else {
        ret = LabPCList_CompareByPointer(arg0, arg1);
    }
    return ret;
}

/** List comparison: Attack, ascending. */
s32 LabPCList_CompareByAttackAsc(LabMonEntry* arg0, LabMonEntry* arg1) {
    s32 var_v0 = arg0->mon.attack - arg1->mon.attack;
    s32 ret;

    if (var_v0 != 0) {
        ret = var_v0;
    } else {
        ret = LabPCList_CompareByPointer(arg0, arg1);
    }
    return ret;
}

/** List comparison: Attack, descending. */
s32 LabPCList_CompareByAttackDesc(LabMonEntry* arg0, LabMonEntry* arg1) {
    s32 var_v0 = arg1->mon.attack - arg0->mon.attack;
    s32 ret;

    if (var_v0 != 0) {
        ret = var_v0;
    } else {
        ret = LabPCList_CompareByPointer(arg0, arg1);
    }
    return ret;
}

/** List comparison: Defense, ascending. */
s32 LabPCList_CompareByDefenseAsc(LabMonEntry* arg0, LabMonEntry* arg1) {
    s32 var_v0 = arg0->mon.defense - arg1->mon.defense;
    s32 ret;

    if (var_v0 != 0) {
        ret = var_v0;
    } else {
        ret = LabPCList_CompareByPointer(arg0, arg1);
    }
    return ret;
}

/** List comparison: Defense, descending. */
s32 LabPCList_CompareByDefenseDesc(LabMonEntry* arg0, LabMonEntry* arg1) {
    s32 var_v0 = arg1->mon.defense - arg0->mon.defense;
    s32 ret;

    if (var_v0 != 0) {
        ret = var_v0;
    } else {
        ret = LabPCList_CompareByPointer(arg0, arg1);
    }
    return ret;
}

/** List comparison: Speed, ascending. */
s32 LabPCList_CompareBySpeedAsc(LabMonEntry* arg0, LabMonEntry* arg1) {
    s32 var_v0 = arg0->mon.speed - arg1->mon.speed;
    s32 ret;

    if (var_v0 != 0) {
        ret = var_v0;
    } else {
        ret = LabPCList_CompareByPointer(arg0, arg1);
    }
    return ret;
}

/** List comparison: Speed, descending. */
s32 LabPCList_CompareBySpeedDesc(LabMonEntry* arg0, LabMonEntry* arg1) {
    s32 var_v0 = arg1->mon.speed - arg0->mon.speed;
    s32 ret;

    if (var_v0 != 0) {
        ret = var_v0;
    } else {
        ret = LabPCList_CompareByPointer(arg0, arg1);
    }
    return ret;
}

/** List comparison: Special, ascending. */
s32 LabPCList_CompareBySpecialAsc(LabMonEntry* arg0, LabMonEntry* arg1) {
    s32 var_v0 = arg0->mon.special - arg1->mon.special;
    s32 ret;

    if (var_v0 != 0) {
        ret = var_v0;
    } else {
        ret = LabPCList_CompareByPointer(arg0, arg1);
    }
    return ret;
}

/** List comparison: Special, descending. */
s32 LabPCList_CompareBySpecialDesc(LabMonEntry* arg0, LabMonEntry* arg1) {
    s32 var_v0 = arg1->mon.special - arg0->mon.special;
    s32 ret;

    if (var_v0 != 0) {
        ret = var_v0;
    } else {
        ret = LabPCList_CompareByPointer(arg0, arg1);
    }
    return ret;
}

/** List comparison: by ID. */
s32 LabPCList_CompareById(LabMonEntry* arg0, LabMonEntry* arg1) {
    s32 var_v0 = arg0->mon.otId - arg1->mon.otId;
    s32 ret;

    if (var_v0 != 0) {
        ret = var_v0;
    } else {
        ret = LabPCList_CompareByPointer(arg0, arg1);
    }
    return ret;
}

s32 func_89109580(LabMonEntry* arg0, LabMonEntry* arg1) {
    return func_891091C0(arg0, arg1);
}

/**
 * Seen in play (2026-11-12) in いちらん: ran when the list was sorted from the おや (OT) column's
 * popup.
 */
s32 LabPCList_CompareByOtName(LabMonEntry* arg0, LabMonEntry* arg1) {
    s32 var_v0;
    s32 ret;

    var_v0 = Text_CompareGlyphCodes(arg0->mon.otName, arg1->mon.otName);
    if (var_v0 != 0) {
        ret = var_v0;
    } else {
        ret = LabPCList_CompareByPointer(arg0, arg1);
    }
    return ret;
}

/** List comparison: by nickname. */
s32 LabPCList_CompareByNickname(LabMonEntry* arg0, LabMonEntry* arg1) {
    s32 var_v0;
    s32 ret;

    var_v0 = Text_CompareGlyphCodes(arg0->mon.nickname, arg1->mon.nickname);
    if (var_v0 != 0) {
        ret = var_v0;
    } else {
        ret = LabPCList_CompareByPointer(arg0, arg1);
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

s32 func_89109638(u8* arg0, u8* arg1) {
    s32 ret;
    s32 var_v1;

    ret = Text_CompareGlyphCodes(D_80064C5C[arg0[8] - 1].name, D_80064C5C[arg1[8] - 1].name);
    if (ret != 0) {
        var_v1 = ret;
    } else {
        var_v1 = LabPCList_CompareByPointer((LabMonEntry*)arg0, (LabMonEntry*)arg1);
    }
    return var_v1;
}

/** List comparison: by raw species ID. */
s32 LabPCList_CompareBySpeciesRawId(LabMonEntry* arg0, LabMonEntry* arg1) {
    s32 var_v0 = arg0->mon.species.id - arg1->mon.species.id;
    s32 ret;

    if (var_v0 != 0) {
        ret = var_v0;
    } else {
        ret = LabPCList_CompareByPointer(arg0, arg1);
    }
    return ret;
}

/** List filter: keeps entries whose level is in a range. */
int LabPCList_FilterByLevelRange(LabMonEntry* a0, u8* arg1) {
    LabMonEntry* arg0 = a0;
    return (arg0->mon.level >= arg1[0]) && (arg1[1] >= arg0->mon.level);
}

/** List filter: keeps entries with any of the given types. */
s32 LabPCList_FilterByAnyType(LabMonEntry* arg0, unk_func_8830867C_02C_C54_01C* a1) {
    UNUSED s32 pad; // FAKE: stack padding
    s32 i;
    s32 j;
    s32 var_v1;
    unk_func_8830867C_02C_C54_01C* arg1 = a1;
    s32 idx = arg0->mon.species.id - 1;
    u8 spC[2];

    spC[0] = gSpeciesData[idx].type1;
    spC[1] = gSpeciesData[idx].type2;

    if (spC[0] == spC[1]) {
        var_v1 = 1;
    } else {
        var_v1 = 2;
    }

    for (i = 0; i < arg1->unk_00; i++) {
        for (j = 0; j < var_v1; j++) {
            if (arg1->unk_04[i] == spC[j]) {
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
s32 LabPCList_FilterByAnyMove(LabMonEntry* a0, unk_func_8830867C_02C_C54_024* a1) {
    LabMonEntry* arg0 = a0;
    unk_func_8830867C_02C_C54_024* arg1 = a1;
    s32 i;
    s32 j;
    s32 temp_v0 = BattleMon_CountMoves(&arg0->mon);

    for (i = 0; i < arg1->unk_04; i++) {
        for (j = 0; j < temp_v0; j++) {
            if (arg1->unk_00[i] == arg0->mon.moves[j]) {
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
s32 LabPCList_FilterBySpeciesId(LabMonEntry* arg0, s32* arg1) {
    return arg0->mon.species.id == *arg1;
}

/** List filter: keeps entries with exactly the given pair of types. */
s32 LabPCList_FilterByExactTypePair(LabMonEntry* arg0, unk_func_8830867C_02C_C54_014* a1) {
    UNUSED s32 pad; // FAKE: stack padding
    s32 i;
    s32 j;
    s32 var_v1;
    unk_func_8830867C_02C_C54_014* arg1 = a1;
    s32 idx = arg0->mon.species.id - 1;
    s32 sp8[2];

    sp8[0] = gSpeciesData[idx].type1;
    sp8[1] = gSpeciesData[idx].type2;

    if (sp8[0] == sp8[1]) {
        var_v1 = 1;
    } else {
        var_v1 = 2;
    }

    if (var_v1 != arg1->unk_00) {
        return 0;
    }

    for (i = 0; i < arg1->unk_00; i++) {
        for (j = 0; j < var_v1; j++) {
            if (arg1->unk_04[i] == sp8[j]) {
                break;
            }
        }

        if (j >= var_v1) {
            return 0;
        }
    }

    return 1;
}

/*
 * func_89109960
 *
 * Returns 1 if bit 0 of the first byte of the entry at index `i` of the
 * 0x1C-byte-stride table at D_80064C4C is set, otherwise 0, where `i` is the
 * byte at offset 8 of arg0. arg1 is not used.
 *
 * What the table and the record arg0 are is not established. Matching note:
 * the table is indexed through a byte pointer; the untyped word extern would
 * scale the 0x1C stride by 4 and read a word.
 */
extern M2C_UNK D_80064C4C;
s32 func_89109960(void *arg0, M2C_UNK arg1) {
    return (*((u8 *)&D_80064C4C + (M2C_FIELD(arg0, u8 *, 8) * 0x1C)) & 1) != 0;
}
