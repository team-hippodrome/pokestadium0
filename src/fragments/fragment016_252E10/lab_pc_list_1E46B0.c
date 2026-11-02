/* Stadium Zero fragment016_252E10. */
/* C ported from the Stadium 1 decomp: src/fragments/lab_pc_list/lab_pc_list_1E46B0.c. */

#include "fragments/lab_pc_list/lab_pc_list.h"
#include "gb_data.h"
#include "save_data.h"
#include "game_state.h"
#include "table_view.h"
#include "gb_save.h"
#include "hal_libc.h"
#include "memory.h"
extern Gfx D_8910D028[];
typedef struct unk_func_88316214 {
    /* 0x00 */ char unk00[0x2C];
    /* 0x2C */ u8 unk_2C;
} unk_func_88316214;
typedef struct unk_func_88316304 {
    /* 0x00 */ unk_func_8830867C_02C_0CC_000** unk_00;
    /* 0x04 */ char unk04[0x4];
    /* 0x08 */ u8 unk_08;
    /* 0x09 */ char unk09[0x8];
    /* 0x11 */ u8 unk_11[1];
} unk_func_88316304;
typedef struct unk_func_883164C0 {
    /* 0x00 */ char unk00[0x5C];
} unk_func_883164C0;

#include "m2c_macros.h"

s32 LabPCList_CompareByLevelAsc(unk_func_88316128* arg0, unk_func_88316128* arg1);
s32 LabPCList_CompareByLevelDesc(unk_func_88316128* arg0, unk_func_88316128* arg1);
s32 LabPCList_CompareByHpAsc(unk_func_88316128* arg0, unk_func_88316128* arg1);
s32 LabPCList_CompareByHpDesc(unk_func_88316128* arg0, unk_func_88316128* arg1);
s32 LabPCList_CompareByAttackAsc(unk_func_88316128* arg0, unk_func_88316128* arg1);
s32 LabPCList_CompareByAttackDesc(unk_func_88316128* arg0, unk_func_88316128* arg1);
s32 LabPCList_CompareByDefenseAsc(unk_func_88316128* arg0, unk_func_88316128* arg1);
s32 LabPCList_CompareByDefenseDesc(unk_func_88316128* arg0, unk_func_88316128* arg1);
s32 LabPCList_CompareBySpeedAsc(unk_func_88316128* arg0, unk_func_88316128* arg1);
s32 LabPCList_CompareBySpeedDesc(unk_func_88316128* arg0, unk_func_88316128* arg1);
s32 LabPCList_CompareBySpecialAsc(unk_func_88316128* arg0, unk_func_88316128* arg1);
s32 LabPCList_CompareBySpecialDesc(unk_func_88316128* arg0, unk_func_88316128* arg1);
s32 LabPCList_CompareById(unk_func_88316128* arg0, unk_func_88316128* arg1);
s32 LabPCList_CompareByNickname(unk_func_88316128* arg0, unk_func_88316128* arg1);
s32 LabPCList_CompareBySpeciesRawId(unk_func_8830867C_02C_0CC* arg0, unk_func_8830867C_02C_0CC* arg1);
int LabPCList_FilterByLevelRange(unk_func_8830867C_02C_0CC* a0, u8* arg1);
s32 LabPCList_FilterByAnyType(unk_func_8830867C_02C_0CC* arg0, unk_func_8830867C_02C_C54_01C* a1);
s32 LabPCList_FilterByAnyMove(unk_func_8830867C_02C_0CC* a0, unk_func_8830867C_02C_C54_024* a1);
s32 LabPCList_FilterBySpeciesId(unk_func_8830867C_02C_0CC* arg0, s32* arg1);
s32 LabPCList_FilterByExactTypePair(unk_func_8830867C_02C_0CC* arg0, unk_func_8830867C_02C_C54_014* a1);

s32 LabPCList_CompareByPointer(unk_func_88316128* arg0, unk_func_88316128* arg1);

s32 func_891091C0(unk_func_8830867C_02C_0CC* arg0, unk_func_8830867C_02C_0CC* arg1) {
    s32 var_v1 = M2C_FIELD(arg0->unk_00[0], s32*, 0xC) - M2C_FIELD(arg1->unk_00[0], s32*, 0xC);

    if (var_v1 == 0) {
        var_v1 = (s32)arg0->unk_00[1] - (s32)arg1->unk_00[1];
        if (var_v1 == 0) {
            var_v1 = arg0->unk_04 - arg1->unk_04;
        }
    }
    return var_v1;
}

s32 LabPCList_CompareByLevelAsc(unk_func_88316128* arg0, unk_func_88316128* arg1) {
    s32 var_v0 = arg0->unk_2C - arg1->unk_2C;
    s32 ret;

    if (var_v0 != 0) {
        ret = var_v0;
    } else {
        ret = LabPCList_CompareByPointer(arg0, arg1);
    }
    return ret;
}

s32 LabPCList_CompareByLevelDesc(unk_func_88316128* arg0, unk_func_88316128* arg1) {
    s32 var_v0 = arg1->unk_2C - arg0->unk_2C;
    s32 ret;

    if (var_v0 != 0) {
        ret = var_v0;
    } else {
        ret = LabPCList_CompareByPointer(arg0, arg1);
    }
    return ret;
}

s32 LabPCList_CompareByHpAsc(unk_func_88316128* arg0, unk_func_88316128* arg1) {
    s32 var_v0 = arg0->unk_2E - arg1->unk_2E;
    s32 ret;

    if (var_v0 != 0) {
        ret = var_v0;
    } else {
        ret = LabPCList_CompareByPointer(arg0, arg1);
    }
    return ret;
}

s32 LabPCList_CompareByHpDesc(unk_func_88316128* arg0, unk_func_88316128* arg1) {
    s32 var_v0 = arg1->unk_2E - arg0->unk_2E;
    s32 ret;

    if (var_v0 != 0) {
        ret = var_v0;
    } else {
        ret = LabPCList_CompareByPointer(arg0, arg1);
    }
    return ret;
}

s32 LabPCList_CompareByAttackAsc(unk_func_88316128* arg0, unk_func_88316128* arg1) {
    s32 var_v0 = arg0->unk_30 - arg1->unk_30;
    s32 ret;

    if (var_v0 != 0) {
        ret = var_v0;
    } else {
        ret = LabPCList_CompareByPointer(arg0, arg1);
    }
    return ret;
}

s32 LabPCList_CompareByAttackDesc(unk_func_88316128* arg0, unk_func_88316128* arg1) {
    s32 var_v0 = arg1->unk_30 - arg0->unk_30;
    s32 ret;

    if (var_v0 != 0) {
        ret = var_v0;
    } else {
        ret = LabPCList_CompareByPointer(arg0, arg1);
    }
    return ret;
}

s32 LabPCList_CompareByDefenseAsc(unk_func_88316128* arg0, unk_func_88316128* arg1) {
    s32 var_v0 = arg0->unk_32 - arg1->unk_32;
    s32 ret;

    if (var_v0 != 0) {
        ret = var_v0;
    } else {
        ret = LabPCList_CompareByPointer(arg0, arg1);
    }
    return ret;
}

s32 LabPCList_CompareByDefenseDesc(unk_func_88316128* arg0, unk_func_88316128* arg1) {
    s32 var_v0 = arg1->unk_32 - arg0->unk_32;
    s32 ret;

    if (var_v0 != 0) {
        ret = var_v0;
    } else {
        ret = LabPCList_CompareByPointer(arg0, arg1);
    }
    return ret;
}

s32 LabPCList_CompareBySpeedAsc(unk_func_88316128* arg0, unk_func_88316128* arg1) {
    s32 var_v0 = arg0->unk_34 - arg1->unk_34;
    s32 ret;

    if (var_v0 != 0) {
        ret = var_v0;
    } else {
        ret = LabPCList_CompareByPointer(arg0, arg1);
    }
    return ret;
}

s32 LabPCList_CompareBySpeedDesc(unk_func_88316128* arg0, unk_func_88316128* arg1) {
    s32 var_v0 = arg1->unk_34 - arg0->unk_34;
    s32 ret;

    if (var_v0 != 0) {
        ret = var_v0;
    } else {
        ret = LabPCList_CompareByPointer(arg0, arg1);
    }
    return ret;
}

s32 LabPCList_CompareBySpecialAsc(unk_func_88316128* arg0, unk_func_88316128* arg1) {
    s32 var_v0 = arg0->unk_36 - arg1->unk_36;
    s32 ret;

    if (var_v0 != 0) {
        ret = var_v0;
    } else {
        ret = LabPCList_CompareByPointer(arg0, arg1);
    }
    return ret;
}

s32 LabPCList_CompareBySpecialDesc(unk_func_88316128* arg0, unk_func_88316128* arg1) {
    s32 var_v0 = arg1->unk_36 - arg0->unk_36;
    s32 ret;

    if (var_v0 != 0) {
        ret = var_v0;
    } else {
        ret = LabPCList_CompareByPointer(arg0, arg1);
    }
    return ret;
}

s32 LabPCList_CompareById(unk_func_88316128* arg0, unk_func_88316128* arg1) {
    s32 var_v0 = arg0->unk_16 - arg1->unk_16;
    s32 ret;

    if (var_v0 != 0) {
        ret = var_v0;
    } else {
        ret = LabPCList_CompareByPointer(arg0, arg1);
    }
    return ret;
}


s32 func_89109580(unk_func_8830867C_02C_0CC* arg0, unk_func_8830867C_02C_0CC* arg1) {
    return func_891091C0(arg0, arg1);
}

s32 func_891095A0(unk_func_88316128* arg0, unk_func_88316128* arg1) {
    s32 var_v0;
    s32 ret;

    var_v0 = Text_CompareGlyphCodes((u8*)arg0 + 0x48, (u8*)arg1 + 0x48);
    if (var_v0 != 0) {
        ret = var_v0;
    } else {
        ret = LabPCList_CompareByPointer(arg0, arg1);
    }
    return ret;
}

s32 LabPCList_CompareByNickname(unk_func_88316128* arg0, unk_func_88316128* arg1) {
    s32 var_v0;
    s32 ret;

    var_v0 = Text_CompareGlyphCodes(&arg0->unk_38, &arg1->unk_38);
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
        var_v1 = LabPCList_CompareByPointer((unk_func_88316128*)arg0, (unk_func_88316128*)arg1);
    }
    return var_v1;
}

s32 LabPCList_CompareBySpeciesRawId(unk_func_8830867C_02C_0CC* arg0, unk_func_8830867C_02C_0CC* arg1) {
    s32 var_v0 = *(u8*)&arg0->unk_08 - *(u8*)&arg1->unk_08;
    s32 ret;

    if (var_v0 != 0) {
        ret = var_v0;
    } else {
        ret = LabPCList_CompareByPointer(arg0, arg1);
    }
    return ret;
}

int LabPCList_FilterByLevelRange(unk_func_8830867C_02C_0CC* a0, u8* arg1) {
    unk_func_88316214* arg0 = a0;
    return (arg0->unk_2C >= arg1[0]) && (arg1[1] >= arg0->unk_2C);
}

s32 LabPCList_FilterByAnyType(unk_func_8830867C_02C_0CC* arg0, unk_func_8830867C_02C_C54_01C* a1) {
    UNUSED s32 pad;
    s32 i;
    s32 j;
    s32 var_v1;
    unk_func_8830867C_02C_C54_01C* arg1 = a1;
    s32 idx = *(u8*)&arg0->unk_08 - 1;
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

s32 LabPCList_FilterByAnyMove(unk_func_8830867C_02C_0CC* a0, unk_func_8830867C_02C_C54_024* a1) {
    unk_func_88316304* arg0 = a0;
    unk_func_8830867C_02C_C54_024* arg1 = a1;
    s32 i;
    s32 j;
    s32 temp_v0 = BattleMon_CountMoves(&arg0->unk_08);

    for (i = 0; i < arg1->unk_04; i++) {
        for (j = 0; j < temp_v0; j++) {
            if (arg1->unk_00[i] == arg0->unk_11[j]) {
                break;
            }
        }

        if (j >= temp_v0) {
            return 0;
        }
    }

    return 1;
}

s32 LabPCList_FilterBySpeciesId(unk_func_8830867C_02C_0CC* arg0, s32* arg1) {
    return *(u8*)&arg0->unk_08 == *arg1;
}

s32 LabPCList_FilterByExactTypePair(unk_func_8830867C_02C_0CC* arg0, unk_func_8830867C_02C_C54_014* a1) {
    UNUSED s32 pad;
    s32 i;
    s32 j;
    s32 var_v1;
    unk_func_8830867C_02C_C54_014* arg1 = a1;
    s32 idx = *(u8*)&arg0->unk_08 - 1;
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
