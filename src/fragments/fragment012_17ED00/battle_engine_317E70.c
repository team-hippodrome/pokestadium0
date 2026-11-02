/* Stadium Zero fragment012_17ED00. */
/* C ported from the Stadium 1 decomp: src/fragments/battle_engine/battle_engine_317E70.c, src/fragments/battle_engine/battle_engine_359F90.c, src/fragments/particle_math/particle_math_26F9B0.c. */

#include "fragments/battle_engine/battle_engine.h"
#include "geo_render.h"
#include "model_renderer.h"
#include "matrix.h"
#include "fragments/particle_math/particle_math.h"
#include "memory.h"

#include "fragments/particle_math/particle_math.h"

#include "fragments/battle_engine/battle_engine.h"
#include "gb_data.h"
#include "text_system.h"
#include "matrix.h"
#include "moves.h"
typedef struct unk_D_843C4DA0 {
    /* 0x00 */ u16 unk_00;
    /* 0x02 */ u8 unk_02;
    /* 0x03 */ u8 unk_03;
    /* 0x04 */ u8 unk_04;
    /* 0x05 */ u8 unk_05;
    /* 0x06 */ char unk06[0x3];
    /* 0x09 */ u8 unk_09;
    /* 0x0A */ char unk0A[0xA];
    /* 0x13 */ u8 unk_13;
    /* 0x14 */ char unk14[0x1];
    /* 0x15 */ u8 unk_15;
    /* 0x16 */ char unk16[0x1];
    /* 0x17 */ u8 unk_17;
    /* 0x18 */ char unk18[0xB];
    /* 0x22 */ u8 unk_22;
    /* 0x24 */ u16 unk_24;
    /* 0x26 */ u16 unk_26;
    /* 0x28 */ u16 unk_28;
    /* 0x2A */ u16 unk_2A;
    /* 0x2C */ u16 unk_2C;
    /* 0x2E */ char unk2E[0x1E];
} unk_D_843C4DA0;
extern u8 sBattleMoveFailed;
extern u8 sBattleCritFlag;
extern u8 D_82199F4E;
extern u16 sBattleDamage;
extern s32 pad_D_843C4DD0;
extern s32 pad_D_843C4DD4;
extern s32 pad_D_843C4DD8;
extern s32 pad_D_843C4DDC;
extern s32 pad_D_843C4DE0;
extern s32 pad_D_843C4DE4;
extern s32 pad_D_843C4DE8;
extern s32 sTypeEffectiveness;
extern s32 pad_D_843C4DF0[21];
extern u8 sConfused;
extern u8 sStatCanBeChangedFurther;
extern s32 pad_D_843C4E48[252];
extern BattleMonRuntime* sBattleUser;
extern BattleMonRuntime* sBattleTarget;
extern BattleMonRuntime D_8219A3C8[2];
extern StatStageMultiplier gStatStageMultipliers[];
extern u8 sTypeEffects[];
extern u8 sHighCritMoves[];
#define PRINTF(x) ((void)(x))

#include "m2c_macros.h"

s32 func_8211EF74(s32, s32, s32, ...);

void BattleAnim_EffectEndNop(void);
s32 func_82111DC4(void);
s32 Battle_CheckFaintAfterMove(void);

void Battle_CheckAllBroughtFainted_HP(ActivePokemon* arg0);
void Battle_CheckAllBroughtFainted_Status(ActivePokemon* arg0);
void Battle_CheckAllBroughtFainted_PP(ActivePokemon* arg0);
void Battle_CheckAllBroughtFainted_Level(ActivePokemon* arg0);

void BattleAnim_EffectEndNop(void) {
}

M2C_UNK func_82110FC0();                            /* extern */
M2C_UNK func_821115F4();                            /* extern */
extern s32 D_8218C784;
extern s8 *D_8219A3C0;
extern s8 *D_8219A3C4;
extern s32 D_8219A520;
extern s8 *D_8219A5A0;

s32 func_821119F8(void) {
    u8 temp_v0;

    temp_v0 = M2C_FIELD(D_8219A3C4, u8 *, 0x58);
    if ((temp_v0 == 0x77) || (temp_v0 == 0)) {
        M2C_FIELD(D_8219A5A0, s32 *, 0x48) = 0x1C;
        func_8211EF74(D_8219A520 + 0x88, 0x20, D_8218C784);
        return 0;
    }
    M2C_FIELD(D_8219A3C0, u8 *, 0x5A) = temp_v0;
    func_821115F4();
    func_82110FC0();
    return 1;
}

#ifdef NON_MATCHING
/* TODO: decompile func_82111A78; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_82111A78.s")
#endif

extern TypeEffectivenessEntry D_8218AC50[];
extern u8 D_82199F3F;

/*
 * func_82111AC4
 *
 * Applies a type-chart table to sBattleDamage. moveType is
 * sBattleUser->moveCache.unk_03. If it equals either of sBattleUser's two
 * type bytes (roster[6], roster[7]), sBattleDamage is increased by half of
 * itself and bit 0x80 of D_82199F3F is set. Then every 3-byte entry of the
 * table at D_8218AC50 (ended by a first byte of 0xFF) whose first byte is
 * moveType and whose second byte equals either of sBattleTarget's two type
 * bytes: D_82199F3F = (D_82199F3F & 0x80) + entry multiplier,
 * sBattleDamage = sBattleDamage * multiplier / 10, and sBattleMoveFailed is
 * set to 1 if the result is 0.
 *
 * The four type bytes are read into locals before the first test, as in the
 * retail code. func_8210EB28 walks the same table. Stadium 1's equivalent is
 * Battle_ApplyTypeEffectAndSTAB, which has extra Struggle and effectiveness
 * counting logic that this version does not.
 */
void func_82111AC4(void) {
    TypeEffectivenessEntry* entry;
    u8 userType1;
    u8 userType2;
    u8 targetType1;
    u8 targetType2;
    u8 moveType;

    userType1 = sBattleUser->roster[6];
    userType2 = sBattleUser->roster[7];
    targetType1 = sBattleTarget->roster[6];
    targetType2 = sBattleTarget->roster[7];
    moveType = sBattleUser->moveCache.unk_03;
    if ((moveType == userType1) || (moveType == userType2)) {
        sBattleDamage += sBattleDamage >> 1;
        D_82199F3F |= 0x80;
    }
    entry = D_8218AC50;
    while (entry->unk_00 != 0xFF) {
        if ((entry->unk_00 == moveType) && ((entry->unk_01 == targetType1) || (entry->unk_01 == targetType2))) {
            D_82199F3F = (D_82199F3F & 0x80) + entry->unk_02;
            sBattleDamage = (sBattleDamage * entry->unk_02) / 10;
            if (sBattleDamage == 0) {
                sBattleMoveFailed = 1;
            }
        }
        entry++;
    }
}

s32 Battle_Effect_Counter(void) {
    if (sBattleUser->usedMove != 0x44) {
        return 1;
    }

    sBattleMoveFailed = 1;

    if (sBattleTarget->usedMove == 0x44) {
        return 0;
    }

    if (sBattleTarget->moveCache.unk_02 == 0) {
        return 0;
    }

    if ((sBattleTarget->moveCache.unk_03 == 0) || (sBattleTarget->moveCache.unk_03 == 1)) {
        if (sBattleDamage == 0) {
            return 0;
        }

        if (sBattleDamage >= 0x8000) {
            sBattleDamage = 0xFFFF;
        } else {
            sBattleDamage *= 2;
        }

        sBattleMoveFailed = 0;
        HandleMoveEffectFlags();
        return 0;
    }
    return 0;
}

extern u8 D_82199F32;
extern u8 D_80065CED[];
extern u8 D_8218ADEC[];
s32 func_8210FA2C(s32, u8*, s32);
s32 func_8210F3F0(void);
s32 func_82111CD4(void) {
    UNUSED s32 pad;
    s32 v;

    D_82199F32 = 0;
    v = D_80065CED[M2C_FIELD(D_8219A3C0, u8*, 0xB) * 23] >> 1;
    if (M2C_FIELD(D_8219A3C0, u8*, 0x46) == 0) {
        return 0;
    }
    if (M2C_FIELD(D_8219A3C0, u8*, 0x4D) & 4) {
        v >>= 1;
    } else {
        v <<= 1;
        if (v >= 0x100) {
            v = 0xFF;
        }
    }
    if (func_8210FA2C(M2C_FIELD(D_8219A3C0, u8*, 0x44), D_8218ADEC, 4) != 0) {
        v <<= 2;
        if (v >= 0x100) {
            v = 0xFF;
        }
    } else {
        v >>= 1;
    }
    if (func_8210F3F0() >= v) {
        return 0;
    }
    D_82199F32 = 1;
    return 1;
}

s32 func_82111DC4(void) {
    return 1;
}

#ifdef NON_MATCHING
/* TODO: decompile func_82111DCC; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_82111DCC.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_821125C0; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_821125C0.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_821129E4; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_821129E4.s")
#endif

void Battle_CheckAllBroughtFainted_HP(ActivePokemon* arg0) {
    ActivePokemonState* ptr1 = &arg0->state;
    BattleMon* temp_v0;
    s32 i;
    s32 var_s2 = 0;

    for (i = 0; i < BattleScene_GetTeamMemberTeamSize(arg0); i++) {
        if (i == ptr1->rosterIndex) {
            var_s2 += arg0->state.runtime.unk_0E;
        } else {
            temp_v0 = &arg0->teamRoster->pokemonPicked[i];
            var_s2 += temp_v0->hp;
        }
    }

    if (arg0->sessionTeams->tagTeamSize == 2) {
        for (i = 0; i < BattleScene_GetPartnerTeamSize(arg0); i++) {
            temp_v0 = &arg0->sessionTeams->teamMember[!ptr1->teamMemberIndex]->pokemonPicked[i];
            var_s2 += temp_v0->hp;
        }
    }

    if (var_s2 == 0) {
        Battle_ResetEntityState(arg0);
        ptr1->unk_2D = 0x12;
    } else {
        Battle_HandleFaint(arg0);
    }
}

void func_82112C1C(ActivePokemon* arg0) {
    ActivePokemonState* ptr1 = &arg0->state;
    BattleMon* temp_v0;
    s32 i;
    s32 var_s2 = 0;

    for (i = 0; i < BattleScene_GetTeamMemberTeamSize(arg0); i++) {
        if (i == ptr1->rosterIndex) {
            var_s2 += M2C_FIELD(arg0, u16*, 0x7D6);
        } else {
            temp_v0 = &arg0->teamRoster->pokemonPicked[i];
            var_s2 += temp_v0->hp;
        }
    }

    if (arg0->sessionTeams->tagTeamSize == 2) {
        for (i = 0; i < BattleScene_GetPartnerTeamSize(arg0); i++) {
            temp_v0 = &arg0->sessionTeams->teamMember[!ptr1->teamMemberIndex]->pokemonPicked[i];
            var_s2 += temp_v0->hp;
        }
    }

    if (var_s2 == 0) {
        Battle_ResetEntityState(arg0);
        ptr1->unk_2D = 0x12;
    } else {
        Battle_HandleFaint(arg0);
    }
}

void func_82112D5C(ActivePokemon* arg0) {
    ActivePokemonState* ptr1 = &arg0->state;
    BattleMon* temp_v0;
    s32 i;
    s32 var_s2 = 0;

    for (i = 0; i < BattleScene_GetTeamMemberTeamSize(arg0); i++) {
        if (i == ptr1->rosterIndex) {
            var_s2 += M2C_FIELD(arg0, u16*, 0x7D8);
        } else {
            temp_v0 = &arg0->teamRoster->pokemonPicked[i];
            var_s2 += temp_v0->hp;
        }
    }

    if (arg0->sessionTeams->tagTeamSize == 2) {
        for (i = 0; i < BattleScene_GetPartnerTeamSize(arg0); i++) {
            temp_v0 = &arg0->sessionTeams->teamMember[!ptr1->teamMemberIndex]->pokemonPicked[i];
            var_s2 += temp_v0->hp;
        }
    }

    if (var_s2 == 0) {
        Battle_ResetEntityState(arg0);
        ptr1->unk_2D = 0x12;
    } else {
        Battle_HandleFaint(arg0);
    }
}

void func_82112E9C(ActivePokemon* arg0) {
    ActivePokemonState* ptr1 = &arg0->state;
    BattleMon* temp_v0;
    s32 i;
    s32 var_s2 = 0;

    for (i = 0; i < BattleScene_GetTeamMemberTeamSize(arg0); i++) {
        if (i == ptr1->rosterIndex) {
            var_s2 += M2C_FIELD(arg0, u16*, 0x7D2);
        } else {
            temp_v0 = &arg0->teamRoster->pokemonPicked[i];
            var_s2 += temp_v0->hp;
        }
    }

    if (arg0->sessionTeams->tagTeamSize == 2) {
        for (i = 0; i < BattleScene_GetPartnerTeamSize(arg0); i++) {
            temp_v0 = &arg0->sessionTeams->teamMember[!ptr1->teamMemberIndex]->pokemonPicked[i];
            var_s2 += temp_v0->hp;
        }
    }

    if (var_s2 == 0) {
        Battle_ResetEntityState(arg0);
        ptr1->unk_2D = 0x12;
    } else {
        Battle_HandleFaint(arg0);
    }
}

s32 Battle_CheckSideDefeatAfterResidualStatus(ActivePokemon* arg0) {
    ActivePokemonState* ptr1 = &arg0->state;
    BattleMon* temp_v0;
    s32 i;
    s32 var_s2;

    if (arg0->state.runtime.unk_15 & 0x18) {
        var_s2 = 0;
        if (arg0->state.runtime.unk_0E == 0) {
            for (i = 0; i < BattleScene_GetTeamMemberTeamSize(arg0); i++) {
                temp_v0 = &arg0->teamRoster->pokemonPicked[i];
                var_s2 += temp_v0->hp;
            }

            if (arg0->sessionTeams->tagTeamSize == 2) {
                for (i = 0; i < BattleScene_GetPartnerTeamSize(arg0); i++) {
                    temp_v0 = &arg0->sessionTeams->teamMember[!ptr1->teamMemberIndex]->pokemonPicked[i];
                    var_s2 += temp_v0->hp;
                }
            }

            if (var_s2 == 0) {
                ptr1->unk_2D = 0x12;
                return 1;
            }
            Battle_HandleFaint(arg0);
        }
        return 1;
    }
    return 0;
}

s32 Battle_CheckFaintAfterMove(void) {
    if (sBattleTarget->unk_0C == 0) {
        Battle_CheckAllBroughtFainted_Level(sActivePokemon[!sBattleScene.scene->unk_2C]);
    }

    if (sBattleUser->unk_0C == 0) {
        Battle_CheckAllBroughtFainted_Level(sActivePokemon[sBattleScene.scene->unk_2C]);
    }

    if ((sBattleUser->unk_0C != 0) && (sBattleTarget->unk_0C != 0) && (sBattleUser->unk_12 == 0)) {
        Battle_CheckAllBroughtFainted_PP(sActivePokemon[sBattleScene.scene->unk_2C]);
        return 0;
    } else if ((sBattleUser->unk_0C != 0) && (sBattleTarget->unk_0C != 0) && (sBattleUser->unk_15 & 0x18) &&
               (sBattleUser->unk_0E == 0)) {
        Battle_CheckAllBroughtFainted_HP(sActivePokemon[sBattleScene.scene->unk_2C]);
        return 0;
    } else if ((sBattleUser->unk_0C != 0) && (sBattleTarget->unk_0C != 0) && (sBattleUser->unk_4D & 0x80) &&
               (sBattleUser->unk_10 == 0)) {
        Battle_CheckAllBroughtFainted_Status(sActivePokemon[sBattleScene.scene->unk_2C]);
        return 0;
    }
}

#ifdef NON_MATCHING
/* TODO: decompile func_821132C8; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_821132C8.s")
#endif

void BeginBattleForEntity(ActivePokemon* arg0) {
    ActivePokemonState* sp24;
    ActivePokemonState* sp20;
    BattleMonRuntime* ptr1;
    BattleMonRuntime* ptr2;

    ptr1 = &arg0->state.runtime;

    sp24 = &sActivePokemon[0]->state;
    sp20 = &sActivePokemon[1]->state;

    ptr2 = &sActivePokemon[BattleScene_GetParticipantSideIndex(arg0) == 0]->state.runtime;

    sp24->unk_2A = 0;
    sp20->unk_2A = 0;
    ptr1->unk_12 = 0xFFFF;
    ptr2->unk_12 = 0xFFFF;

    sConfused = 1;
    sStatCanBeChangedFurther = 1;

    sBattleScene.scene->unk_48 = 0;
    sBattleScene.scene->unk_4C = 0;

    sBattleUser = ptr1;
    sBattleTarget = ptr2;

    Battle_ResetEntityState(arg0);
    Vec3f_SetComponentsDuplicate(&arg0->modelTransform.unk_00, 0.0f, 0.0f, 0.0f);
    Vec3f_SetComponentsDuplicate(&arg0->modelTransform.rotation, 0.0f, 0.0f, 0.0f);
    Battle_InitPokemonRuntimeState(arg0);

    if (arg0 == sActivePokemon[0]) {
        Battle_ResetTransientRuntimeState(0, 1);
    } else {
        Battle_ResetTransientRuntimeState(1, 0);
    }
}
