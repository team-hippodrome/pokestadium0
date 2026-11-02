/* Stadium Zero fragment012_17ED00. */
/* C ported from the Stadium 1 decomp: src/fragments/battle_engine/battle_engine_359F90.c. */

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

s32 func_82107F88(ActivePokemon*);

s32 func_8211EF74(s32, s32, s32, ...);
extern s32 D_8219A520;

void ComputeAllPokemonStats(BattleMon* arg0);
void func_82110FB0(void);
void func_82110FB8(void);
void Battle_ExecuteMoveAnimation(void);
s32 Battle_Effect_Metronome(void);
void Battle_ApplyPoisonOrBurnDamage(void);
void func_82111870(void);

u8 Battle_Random(void);
void ComputePokemonStat(s32 arg0, BattleMon* arg1);
void Battle_IncrementMoveUsage(void);

void ComputeAllPokemonStats(BattleMon* arg0) {
    ComputePokemonStat(0, arg0);
    ComputePokemonStat(1, arg0);
    ComputePokemonStat(2, arg0);
    ComputePokemonStat(3, arg0);
    ComputePokemonStat(4, arg0);
}

extern u16 D_82199F54;
extern u16 D_82199F58;
extern u16 D_82199F56;
extern u16 D_82199F52;
extern u16 D_843C4DCC;
void InitBattleParameters(void) {
    sBattleDamage = 0;
    D_82199F52 = sBattleUser->moveCache.unk_02;
    if (D_82199F52) {
        if (sBattleUser->moveCache.unk_03 < 0x14) {
            D_82199F56 = sBattleTarget->unk_2C;
            if (sBattleTarget->unk_4E & 4) {
                D_82199F56 *= 2;
            }

            if (sBattleCritFlag != 0) {
                D_82199F56 = sBattleTarget->unk_3A;
                D_82199F54 = sBattleUser->unk_38;
            } else {
                D_82199F54 = sBattleUser->unk_2A;
            }
        } else {
            D_82199F56 = sBattleTarget->unk_30;
            if (sBattleTarget->unk_4E & 2) {
                D_82199F56 *= 2;
            }

            if (sBattleCritFlag != 0) {
                D_82199F56 = sBattleTarget->unk_3E;
                D_82199F54 = sBattleUser->unk_3E;
            } else {
                D_82199F54 = sBattleUser->unk_30;
            }
        }

        if (D_82199F54 & 0xFF00) {
            if (D_82199F56 & 0xFF00) {
                D_82199F54 >>= 2;
                D_82199F56 >>= 2;
                if (D_82199F54 == 0) {
                    D_82199F54 = 1;
                }
            }
        }

        D_82199F58 = sBattleUser->unk_26;
        if (sBattleCritFlag != 0) {
            D_82199F58 *= 2;
        }
    }
}

extern u16 D_82199F52;
extern u16 D_82199F56;
extern u16 D_82199F58;
extern u16 D_82199F54;
extern u16 D_82199F58;
s32 Battle_CalcDamage(void) {
    s32 temp_v0 = sBattleUser->moveCache.unk_01;

    if (temp_v0 == 7) {
        D_82199F56 >>= 1;
        if (D_82199F56 == 0) {
            D_82199F56 = 1;
        }
    }

    if ((temp_v0 != 0x1D) && (temp_v0 != 0x1E)) {
        if (temp_v0 == 0x26) {
            return Battle_CheckMoveSuccess();
        }

        if (D_82199F52 == 0) {
            return 0;
        }
    }

    sBattleDamage += (((((D_82199F58 * 2) / 5) + 2) * D_82199F52 * D_82199F54) / D_82199F56) / 50;
    if (sBattleDamage > 0x3E4) {
        sBattleDamage = 0x3E4;
    }
    sBattleDamage += 2;

    return 1;
}

#ifdef NON_MATCHING
/* TODO: decompile func_8211009C; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_8211009C.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_821102F0; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_821102F0.s")
#endif

void Battle_DecrementPP(s32 arg0) {
    BattleMonRuntime* temp_v0;
    ActivePokemonState* temp_a1;
    BattleMon* temp_a2;

    temp_v0 = &sActivePokemon[arg0]->state.runtime;
    temp_a1 = &sActivePokemon[arg0]->state;
    temp_a2 = &sActivePokemon[arg0]->teamRoster->pokemonPicked[temp_a1->rosterIndex];

    if ((temp_v0->usedMove != 0xA5) && !(temp_v0->unk_4C & 7) && !(temp_v0->unk_4D & 0x40)) {
        temp_v0->unk_32[temp_a1->unk_0C]--;
        if (!(temp_v0->unk_4E & 8)) {
            temp_a2->unk_20[temp_a1->unk_0C] -= 1;
        }
    }
}

extern s8 *D_8219A3C0;
extern s8 *D_8219A3C4;
extern u8 D_8218AC34[][2];
void func_82110890(void) {

    s32 idx = ((u8*)D_8219A3C0)[0x60];
    s32 i;
    s32 v;

    i = ((u8*)D_8219A3C4)[0x61];
    i = 14 - i;
    v = ((u8*)D_8219A3C0)[0x48] * D_8218AC34[idx - 1][0] / D_8218AC34[idx - 1][1];
    if (v == 0) {
        v = 1;
    }
    v = v * D_8218AC34[i - 1][0] / D_8218AC34[i - 1][1];
    if (v == 0) {
        v = 1;
    }
    if (v >= 0x100) {
        v = 0xFF;
    }
    ((u8*)D_8219A3C0)[0x48] = v;
}

extern s8 D_82199F31;
extern s16 D_82199F50;
extern s8 *D_8219A3C0;
extern s8 *D_8219A3C4;
extern s8 *D_8219A5A0;

void func_82110984(void) {
    s32 temp_v0;

    D_82199F50 = 0;
    temp_v0 = M2C_FIELD(D_8219A5A0, s32 *, 0x1C);
    if ((temp_v0 == 5) || (temp_v0 == 9) || (temp_v0 == 6) || (temp_v0 == 0xA)) {
        if (M2C_FIELD(D_8219A3C4, u8 *, 0x4C) & 0x40) {
            D_82199F31 = 1;
        } else {
            D_82199F31 = 0;
        }
    } else {
        D_82199F31 = 1;
    }
    M2C_FIELD(D_8219A3C0, u8 *, 0x4C) = (u8) (M2C_FIELD(D_8219A3C0, u8 *, 0x4C) & 0xFFDF);
}

void func_82110984(void);
s32 func_8210F3F0(void);
void func_82110A10(void) {
    s8* p = D_8219A3C0;
    u8 effect = M2C_FIELD(p, u8*, 0x45);

    if ((effect == 8) && !(M2C_FIELD(D_8219A3C4, u8*, 0x15) & 7)) {
        func_82110984();
        return;
    }
    if (M2C_FIELD(D_8219A3C4, u8*, 0x4D) & 0x10) {
        if (effect == 0x11) {
            return;
        }
        if ((effect == 3) || (effect == 8)) {
            func_82110984();
            return;
        }
    }
    if (M2C_FIELD(D_8219A3C4, u8*, 0x4C) & 0x40) {
        func_82110984();
        return;
    }
    if ((((effect >= 0x12) && (effect < 0x1A)) || ((effect >= 0x3A) && (effect < 0x42))) && (M2C_FIELD(D_8219A3C4, u8*, 0x4D) & 2)) {
        func_82110984();
        return;
    }
    if (M2C_FIELD(p, u8*, 0x4D) & 1) {
        return;
    }
    func_82110890();
    if (func_8210F3F0() >= M2C_FIELD(D_8219A3C0, u8*, 0x48)) {
        func_82110984();
    }
}

void func_82110B44(ActivePokemon* arg0) {
    BattleMon* ptr = &arg0->teamRoster->pokemonPicked[arg0->state.rosterIndex];

    ptr->statusCondition = arg0->state.runtime.unk_15;
}

void ApplyParalysisSpeedCut(ActivePokemon* arg0) {
    BattleMonRuntime* temp_v0 = &arg0->state.runtime;

    if (arg0->state.runtime.unk_15 & 0x40) {
        temp_v0->speed >>= 2;
        if (temp_v0->speed == 0) {
            temp_v0->speed = 1;
        }
    }
}

void ApplyBurnAttackCut(ActivePokemon* arg0) {
    BattleMonRuntime* temp_v0 = &arg0->state.runtime;

    if (arg0->state.runtime.unk_15 & 0x10) {
        temp_v0->unk_2A >>= 1;
        if (temp_v0->unk_2A == 0) {
            temp_v0->unk_2A = 1;
        }
    }
}

void func_8210F24C(ActivePokemon*);
void func_80041940(s32, s32, s32);

void Battle_InitPokemonRuntimeState(ActivePokemon* arg0) {
    ActivePokemonState* sp28;
    BattleMonRuntime* sp24;
    BattleMon* sp34;
    s32 i;
    s32 j;

    sp28 = &arg0->state;
    sp24 = &arg0->state.runtime;
    sp34 = &arg0->sessionTeams->teamMember[sp28->unk_2D_zero]->pokemonPicked[sp28->rosterIndex];

    sp24->unk_14 = sp28->rosterIndex;
    sp24->id = sp34->unk_00.unk_00;
    sp24->unk_0C = sp34->hp;
    sp24->unk_15 = sp34->statusCondition;
    sp24->roster[6] = sp34->unk_06;
    sp24->roster[7] = sp34->unk_07;
    sp24->roster[8] = sp34->unk_08;

    sp24->moves[0] = sp34->unk_09[0];
    sp24->moves[1] = sp34->unk_09[1];
    sp24->moves[2] = sp34->unk_09[2];
    sp24->moves[3] = sp34->unk_09[3];
    sp24->unk_24 = sp34->unk_1E;

    sp24->unk_32[0] = sp34->unk_20[0];
    sp24->unk_32[1] = sp34->unk_20[1];
    sp24->unk_32[2] = sp34->unk_20[2];
    sp24->unk_32[3] = sp34->unk_20[3];

    if ((sp34->unk_09[0] == 0) || (sp34->unk_09[0] >= 0xA6)) {
        sp24->unk_32[0] = 0;
    }

    if ((sp34->unk_09[1] == 0) || (sp34->unk_09[1] >= 0xA6)) {
        sp24->unk_32[1] = 0;
    }

    if ((sp34->unk_09[2] == 0) || (sp34->unk_09[2] >= 0xA6)) {
        sp24->unk_32[2] = 0;
    }

    if ((sp34->unk_09[3] == 0) || (sp34->unk_09[3] >= 0xA6)) {
        sp24->unk_32[3] = 0;
    }

    for (i = 0; i < 4; i++) {
        if (sp34->unk_09[i] == 0) {
            for (j = i; j < 4; j++) {
                sp24->unk_32[j] = 0;
                sp24->moves[j] = sp34->unk_09[j] = 0;
            }
            break;
        }
    }

    sp24->unk_26 = sp34->unk_24;
    sp24->unk_28 = sp34->unk_26;
    sp24->unk_2A = sp34->unk_28;
    sp24->unk_2C = sp34->unk_2A;
    sp24->speed = sp34->unk_2C;
    sp24->unk_30 = sp34->unk_2E;

    ApplyParalysisSpeedCut(arg0);
    ApplyBurnAttackCut(arg0);

    sp24->unk_36 = gBaseStats[sp24->id].baseHP;
    sp24->unk_38 = sp34->unk_28;
    sp24->unk_3A = sp34->unk_2A;
    sp24->unk_3C = sp34->unk_2C;
    sp24->unk_3E = sp34->unk_2E;

    // clang-format off
    for (i = 0; i < 8; i++) { sp24->unk_5C[i] = 7; }
    // clang-format on

    func_8210F24C(arg0);
    func_80041940(BattleScene_GetParticipantSideIndex(arg0), sp34->hp, sp34->unk_26);
}

s32 func_82110EAC(s8 *arg0)
{
  int new_var;
  if ((*((u16 *) (((s8 *) ((*((s32 *) (((s8 *) arg0) + 0x860))) + ((*((s32 *) (((s8 *) arg0) + 0x7A4))) * 0x50))) + (new_var = -0x32)))) != 0)
  {
    return 1;
  }
  return 0;
}

#ifdef NON_MATCHING
/* TODO: decompile func_82110EE4; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_82110EE4.s")
#endif

void func_82110FB0(void) {
}

void func_82110FB8(void) {
}

void Battle_ExecuteMoveAnimation(void) {
    sBattleUser->moveCache.lastMove = gMoveData[sBattleUser->usedMove - 1].unk_00;
    sBattleUser->moveCache.unk_01 = gMoveData[sBattleUser->usedMove - 1].unk_01;
    sBattleUser->moveCache.unk_02 = gMoveData[sBattleUser->usedMove - 1].unk_02;
    sBattleUser->moveCache.unk_03 = gMoveData[sBattleUser->usedMove - 1].unk_03;
    sBattleUser->moveCache.unk_04 = gMoveData[sBattleUser->usedMove - 1].unk_04;
    sBattleUser->moveCache.unk_05 = gMoveData[sBattleUser->usedMove - 1].unk_05;
}

extern s32 D_8218C780;
void Battle_ApplyRageContinuation(void) {
    BattleMonRuntime* sp1C;

    if ((sBattleTarget->unk_4D & 0x40) && ((sBattleTarget->unk_5C[0]) != 0xD)) {
        sp1C = sBattleUser;

        sBattleUser = sBattleTarget;
        sBattleUser->moveCache.lastMove = 0;
        sBattleUser->moveCache.unk_01 = 10;

        func_8211EF74(D_8219A520 + 0x348, 0x1F, D_8218C780, func_82107F88(sActivePokemon[!sBattleScene.scene->unk_2C]));
        Battle_ApplyRageStatBoost();

        sBattleUser->moveCache.lastMove = RAGE;
        sBattleUser->moveCache.unk_01 = 0;

        sBattleUser = sp1C;
    }
}

extern u8 D_843C4DB3;
extern u8 D_82199F3F;

extern s32 D_8218C7A8;
extern s32 D_8218C7AC;

// Matches the ROM, but uses rodata data that is not placed in this file yet.
void Battle_UpdateBattleLog(void) {
    sTypeEffectiveness = D_82199F3F & 0x7F;
    if (sTypeEffectiveness >= 0xB) {
        func_8211EF74(D_8219A520 + 0x88, 0x29, D_8218C7A8);
    } else if (sTypeEffectiveness < 0xA) {
        func_8211EF74(D_8219A520 + 0x88, 0x2A, D_8218C7AC);
    }
}

extern s32 D_8218C778;
extern s32 D_8218C77C;

// Matches the ROM, but uses rodata data that is not placed in this file yet.
void Battle_PlayMoveSound(void) {
    BattleMonRuntime* sp1C = &sActivePokemon[!sBattleScene.scene->unk_2C]->state.runtime;

    switch (sBattleCritFlag) {
        case 1:
            func_8211EF74(D_8219A520 + 0x148, 0x1D, D_8218C778);
            sBattleScene.scene->unk_1A = 2;
            break;
        case 2:
            func_8211EF74(D_8219A520 + 0x148, 0x1E, D_8218C77C);
            sBattleScene.scene->unk_1A = 2;
            break;
    }
    sp1C->unk_5B = sBattleCritFlag;
    sBattleCritFlag = 0;
}

#ifdef NON_MATCHING
/* TODO: decompile func_821112AC; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_821112AC.s")
#endif

extern u8 D_82199F3F;
#ifdef NON_MATCHING
/* TODO: decompile func_821113E8; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_821113E8.s")
#endif

void Battle_IncrementMoveUsage(void) {
    ActivePokemonState* state;
    BattleMon* mon;

    mon = &sActivePokemon[sBattleScene.scene->unk_2C]->teamRoster->pokemonPicked[sActivePokemon[sBattleScene.scene->unk_2C]->state.rosterIndex];
    state = &sActivePokemon[sBattleScene.scene->unk_2C]->state;

    sBattleUser->unk_32[state->unk_0C]++;
    mon->unk_20[state->unk_0C]++;
}

s32 Battle_Effect_Metronome(void) {
    s32 move_pulled;

    Battle_IncrementMoveUsage();
    do {
        do {
            move_pulled = Battle_Random();
        } while (move_pulled == 0 || move_pulled >= 0xA5);
    } while (move_pulled == METRONOME);
    sBattleUser->usedMove = move_pulled;
    Battle_ExecuteMoveAnimation();
    return 1;
}

void Battle_ApplyPoisonOrBurnDamage(void) {
    u16 var_a0;

    if (sBattleUser->unk_12 != 0xFFFF) {
        sBattleUser->unk_0E = sBattleUser->unk_12;
    } else {
        sBattleUser->unk_0E = sBattleUser->unk_0C;
    }

    var_a0 = (sBattleUser->unk_28 >> 4) & 0xFFFF;
    if (var_a0 == 0) {
        var_a0++;
    }

    if (sBattleUser->unk_4E & 1) {
        sBattleUser->unk_51++;
        var_a0 *= sBattleUser->unk_51;
    }

    if (sBattleUser->unk_0E < var_a0) {
        sBattleUser->unk_0E = 0;
    } else {
        sBattleUser->unk_0E -= var_a0;
    }

    sBattleUser->unk_10 = sBattleUser->unk_0E;
}

/*
 * func_8211176C
 *
 * Works on two BattleMonRuntime records: sBattleUser (D_8219A3C0, "A" below)
 * and sBattleTarget (D_8219A3C4, "B" below). Both pointers are re-read on every
 * access, as in the retail code.
 *
 *  1. If bits 0x18 of A->unk_15 are clear, A->unk_10 = A->unk_12, or A->unk_0C
 *     when unk_12 is 0xFFFF.
 *  2. amount = (A->unk_28 >> 4) & 0xFFFF, raised to 1 if that is 0.
 *  3. If A->unk_4E & 1, A->unk_51 is incremented and amount becomes
 *     (amount * A->unk_51) & 0xFFFF (unsigned multiply).
 *  4. If A->unk_10 < amount, A->unk_10 = 0 and amount = A->unk_10 (so 0);
 *     otherwise A->unk_10 -= amount.
 *  5. B->unk_10 = B->unk_0C, then B->unk_10 += amount, then B->unk_10 is
 *     replaced by B->unk_28 if B->unk_28 < B->unk_10 (compared as ints).
 *
 * What the fields mean (current/maximum values, the unk_4E bit and the unk_51
 * counter) is not established from this function.
 *
 * Matching notes: reusing the single temporary `v` for the intermediate values
 * matters; with a separate local for each use the compiler picked a2 instead of
 * a1 for the address register. The two-step `v = ...; amount = v & 0xFFFF`
 * forms and the (u32) cast on the multiply (which fixes the operand order of
 * the multu) are matching choices, not meaning.
 */
void func_8211176C(void) {
    s32 amount;
    s32 v;

    if (!(sBattleUser->unk_15 & 0x18)) {
        v = sBattleUser->unk_12;
        if (v != 0xFFFF) {
            sBattleUser->unk_10 = v;
        } else {
            sBattleUser->unk_10 = sBattleUser->unk_0C;
        }
    }
    v = (sBattleUser->unk_28 >> 4) & 0xFFFF;
    amount = v;
    if (v == 0) {
        v = v + 1;
        amount = v & 0xFFFF;
    }
    if (sBattleUser->unk_4E & 1) {
        sBattleUser->unk_51 += 1;
        v = (u32)amount * sBattleUser->unk_51;
        amount = v & 0xFFFF;
    }
    v = sBattleUser->unk_10;
    if (v < amount) {
        sBattleUser->unk_10 = 0;
        amount = sBattleUser->unk_10;
    } else {
        sBattleUser->unk_10 = v - amount;
    }
    sBattleTarget->unk_10 = sBattleTarget->unk_0C;
    sBattleTarget->unk_10 = sBattleTarget->unk_10 + amount;
    v = sBattleTarget->unk_28;
    if (v < sBattleTarget->unk_10) {
        sBattleTarget->unk_10 = v;
    }
}

void func_82111870(void) {
}

extern s32 D_8218C704;
extern s32 D_8218C708;
extern s32 D_8218C70C;

// Matches the ROM, but uses rodata data that is not placed in this file yet.
void func_8211176C(void);
void func_82111870(void);

s32 Battle_ApplyResidualEffects(void) {
    if (sBattleTarget->unk_0C == 0) {
        return 0;
    }

    if (sBattleUser->unk_15 & 0x18) {
        if (sBattleUser->unk_15 & 8) {
            func_8211EF74(D_8219A520 + 0x248, 0, D_8218C704, func_82107F88(sActivePokemon[sBattleScene.scene->unk_2C]));
        } else {
            func_8211EF74(D_8219A520 + 0x248, 1, D_8218C708, func_82107F88(sActivePokemon[sBattleScene.scene->unk_2C]));
        }
        Battle_ApplyPoisonOrBurnDamage();
        sBattleTarget->unk_0E = sBattleTarget->unk_0C;
    }

    if (sBattleUser->unk_4D & 0x80) {
        func_8211176C();
        func_82111870();
        func_8211EF74(D_8219A520 + 0x288, 2, D_8218C70C, func_82107F88(sActivePokemon[sBattleScene.scene->unk_2C]));
    }

    if (sBattleUser->unk_0C != 0) {
        return 0;
    }
    return 1;
}
