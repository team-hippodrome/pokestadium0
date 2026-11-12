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

void func_8211EF74(s32, s32, s32, ...);

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

// FAKE: decomp slop. Raw offset casts stand in for battle mon fields.
void func_82111A78(void)
{
  if (((*((u8 *) (((s8 *) D_8219A3C0) + 0x44))) == 0x78) || ((*((u8 *) (((s8 *) D_8219A3C0) + 0x44))) == 0x99))
  {
    if ((*((u8 *) (((s8 *) D_8219A3C4) + 0x4C))) & 0x40)
    {
      return;
    }
    if (*((u8 *) (((s8 *) D_8219A3C4) + 0x1C)) == 8)
    {
      return;
    }
    if ((s32) D_8219A3C4 == 8) // FAKE: second use of constant 8 pools it into v1
    {
    }
    if ((!D_8219A3C4) && (!D_8219A3C4)) // FAKE
    {
    }
  }
}

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

typedef struct MoveName82111DCC {
    /* 0x0 */ char* name;
    /* 0x4 */ char unk4[0x8];
} MoveName82111DCC; // size = 0xC

s32 func_82107F88(ActivePokemon*);
extern s32 D_8218C718;
extern s32 D_8218C71C;
extern s32 D_8218C720;
extern s32 D_8218C724;
extern s32 D_8218C728;
extern s32 D_8218C72C;
extern s32 D_8218C730;
extern s32 D_8218C734;
extern s32 D_8218C738;
extern s32 D_8218C73C;
extern s32 D_8218C740;
extern s32 D_8218C744;
extern s32 D_8218C748;
extern s32 D_8218C74C;
extern s32 D_8218C750;
extern MoveName82111DCC D_8006A9CC[];

s32 func_82111DCC(void) {
    BattleMonRuntime* sp34;
    char* sp30;
    u16 sp2E;
    u8 sp2D;
    ActivePokemonState* temp_v0;
    BattleMonRuntime* temp_v1;

    temp_v0 = &sActivePokemon[sBattleScene.scene->unk_2C]->state;
    temp_v1 = &sActivePokemon[sBattleScene.scene->unk_2C]->state.runtime;

    if (sBattleUser->unk_15 & 7) {
        sBattleUser->unk_15 = (sBattleUser->unk_15 & 7) - 1;
        if (temp_v1->roster[temp_v0->rosterIndex + temp_v0->teamMemberIndex * 3] != 0) {
            temp_v1->roster[temp_v0->rosterIndex + temp_v0->teamMemberIndex * 3]--;
        }
        if (sBattleUser->unk_15 != 0) {
            func_8211EF74(D_8219A520 + 0x88, 5, D_8218C718, func_82107F88(sActivePokemon[sBattleScene.scene->unk_2C]));
            sBattleScene.scene->unk_48 = 0x11;
        } else {
            func_8211EF74(D_8219A520 + 0x88, 6, D_8218C71C, func_82107F88(sActivePokemon[sBattleScene.scene->unk_2C]));
            sBattleScene.scene->unk_48 = 0x11;
        }
        sBattleUser->unk_58 = 0;
        return 0;
    }

    if (sBattleUser->unk_15 & 0x20) {
        func_8211EF74(D_8219A520 + 0x88, 7, D_8218C720, func_82107F88(sActivePokemon[sBattleScene.scene->unk_2C]));
        sBattleUser->unk_58 = 0;
        sBattleScene.scene->unk_48 = 0x11;
        return 0;
    }

    if (sBattleTarget->unk_4C & 0x20) {
        func_8211EF74(D_8219A520 + 0x88, 8, D_8218C724, func_82107F88(sActivePokemon[sBattleScene.scene->unk_2C]));
        sBattleScene.scene->unk_48 = 0x11;
        return 0;
    }

    if (sBattleUser->unk_4C & 8) {
        func_8211EF74(D_8219A520 + 0x88, 9, D_8218C728, func_82107F88(sActivePokemon[sBattleScene.scene->unk_2C]));
        sBattleUser->unk_4C &= 0xFFF7;
        sBattleScene.scene->unk_48 = 0x1C;
        return 0;
    }

    if (sBattleUser->unk_4D & 0x20) {
        sBattleUser->unk_4D &= ~0x20;
        sBattleScene.scene->unk_48 = 0x11;
        func_8211EF74(D_8219A520 + 0x88, 0xA, D_8218C72C, func_82107F88(sActivePokemon[sBattleScene.scene->unk_2C]));
        return 0;
    }

    if (sBattleUser->unk_52 != 0) {
        sBattleUser->unk_52--;
        if (!(sBattleUser->unk_52 & 0xF)) {
            sBattleUser->unk_52 = 0;
            sBattleUser->unk_57 = 0;
            func_8211EF74(D_8219A520 + 0x388, 0xB, D_8218C730, func_82107F88(sActivePokemon[sBattleScene.scene->unk_2C]));
        }
    }

    if (sBattleUser->unk_4C & 0x80) {
        sBattleUser->unk_50--;
        if (sBattleUser->unk_50 == 0) {
            sBattleUser->unk_4C &= 0xFF7F;
            func_8211EF74(D_8219A520 + 0x188, 0xC, D_8218C734, func_82107F88(sActivePokemon[sBattleScene.scene->unk_2C]));
        } else {
            func_8211EF74(D_8219A520 + 0x188, 0xD, D_8218C738, func_82107F88(sActivePokemon[sBattleScene.scene->unk_2C]));
            if (func_8210F3F0() >= 0x80) {
                sBattleScene.scene->unk_48 = 0x14;
                sBattleUser->unk_4C &= 0x80;
                func_8211EF74(D_8219A520 + 0x148, 0xE, D_8218C73C);

                sp2E = sBattleTarget->unk_2C;
                sBattleTarget->unk_2C = sBattleUser->unk_2C;
                sp2D = sBattleUser->moveCache.unk_01;
                sBattleUser->moveCache.unk_01 = 0;
                sBattleCritFlag = 0;
                sBattleUser->moveCache.unk_02 = 0x28;
                sBattleUser->moveCache.unk_03 = 0;
                InitBattleParameters();
                Battle_CalcDamage();
                sBattleUser->moveCache.unk_01 = sp2D;
                sBattleTarget->unk_2C = sp2E;

                sp34 = sBattleUser;
                sBattleUser = sBattleTarget;
                sBattleTarget = sp34;
                Battle_ApplyDamage();
                sBattleTarget = sBattleUser;
                sBattleUser = sp34;
                goto label1;
            }
        }
    }

    if ((sBattleUser->unk_57 != 0) && (sBattleUser->unk_57 == sBattleUser->usedMove)) {
        sBattleUser->unk_4C &= 0xFFEF;
        sp30 = D_8006A9CC[sBattleUser->usedMove].name;
        func_8211EF74(D_8219A520 + 0x88, 0xF, D_8218C740, func_82107F88(sActivePokemon[sBattleScene.scene->unk_2C]), sp30);
        sBattleScene.scene->unk_48 = 0x11;
        return 0;
    }

    if ((sBattleUser->unk_15 & 0x40) && (func_8210F3F0() < 0x3F)) {
        func_8211EF74(D_8219A520 + 0x88, 0x10, D_8218C744, func_82107F88(sActivePokemon[sBattleScene.scene->unk_2C]));
        sBattleScene.scene->unk_48 = 0x1F;
    label1:
        sBattleUser->unk_4C &= 0xFF8C;
        return 0;
    }

    if (sBattleUser->unk_4C & 1) {
        sBattleUser->moveCache.lastMove = 0;
        sBattleUser->unk_54 += sBattleDamage;
        sBattleUser->unk_4F -= 1;
        if (sBattleUser->unk_4F != 0) {
            sBattleScene.scene->unk_48 = 0x1B;
            return 0;
        }
        sBattleUser->unk_4C &= 0xFFFE;
        func_8211EF74(D_8219A520 + 0xC8, 0x11, D_8218C748, func_82107F88(sActivePokemon[sBattleScene.scene->unk_2C]));
        sBattleUser->moveCache.unk_02 = 1;
        sBattleDamage = sBattleUser->unk_54 * 2;
        if (!sBattleDamage) {
            sBattleMoveFailed = 1;
        }
        sBattleUser->unk_54 = 0;
        sBattleUser->moveCache.lastMove = BIDE;
        return 5;
    }

    if (sBattleUser->unk_4C & 2) {
        sBattleUser->moveCache.lastMove = THRASH;
        func_8211EF74(D_8219A520 + 0xC8, 0x12, D_8218C74C, func_82107F88(sActivePokemon[sBattleScene.scene->unk_2C]));
        sBattleUser->unk_4F -= 1;
        if (sBattleUser->unk_4F != 0) {
            return 4;
        }
        sBattleUser->unk_4C &= 0xFFFD;
        sBattleUser->unk_4C |= 0x80;
        sBattleUser->unk_50 = (func_8210F3F0() & 3) + 2;
        return 4;
    }

    if (sBattleUser->unk_4C & 0x20) {
        func_8211EF74(D_8219A520 + 0xC8, 0x13, D_8218C750, func_82107F88(sActivePokemon[sBattleScene.scene->unk_2C]));
        sBattleUser->unk_4F -= 1;
        return 6;
    }

    if (sBattleUser->unk_4D & 0x40) {
        sBattleUser->moveCache.unk_01 = 0;
        return 3;
    }
    return 2;
}

extern u8 D_82199F41;
extern u8 D_82199F36;
extern u8 D_82199F43;
extern u8 D_8218AD4C[];
extern u8 D_8218AD5C[];
extern u8 D_8218AD60[];
extern u8 D_8218AD64[];
extern u8 D_8218AD80[];
extern u8 D_8218AD8C[];
extern s32 D_8218C714;
/* "%d". It sits in the middle of this TU's debug strings, away from the jump
   table that is this file's placed .rodata, so it is referenced by address. */
extern char D_8219574C[];
void func_82105E38(ActivePokemon*, s32);
void func_821102F0(void);
void func_8210F8E8(void);

/* Resolve the current action: move selection, hit and damage checks, then effect dispatch.
   Stadium 1 calls it ProcessBattleTurn. */
void func_821125C0(void) {
    s8 sp2C[12];
    u8 effect;
    BattleMonRuntime* user;

    if (sBattleUser->usedMove != 0xFF) {
        sBattleMoveFailed = 0;
        D_82199F41 = 0;
        D_82199F36 = 0;
        D_82199F3F = 0xA;

        switch (func_82111DCC()) {
            case 2:
                Battle_ExecuteMoveAnimation();
                if (sBattleUser->unk_4C & 0x10) {
                    sBattleUser->unk_4C &= ~(0x40 | 0x10);
                    func_82105E38(sActivePokemon[sBattleScene.scene->unk_2C], 8);
                } else {
                    if (func_82111DC4() == 0) {
                        user = sBattleUser;
                        goto block_29a;
                    }
                block_5:
                    switch (sBattleUser->moveCache.unk_01) {
                        case 0x27:
                        case 0x2B:
                            Battle_ExecuteMoveEffect();
                            return;
                    }
                }
            case 3:
                func_821102F0();
                Battle_DecrementPP(sBattleScene.scene->unk_2C);
                if (IsByteInArray(sBattleUser->moveCache.unk_01, D_8218AD4C, 0x10) != 0) {
                    Battle_ExecuteMoveEffect();
                    return;
                }
                if (IsByteInArray(sBattleUser->moveCache.unk_01, D_8218AD5C, 2) != 0) {
                    Battle_ExecuteMoveEffect();
                }
            case 4:
                if (IsByteInArray(sBattleUser->moveCache.unk_01, D_8218AD60, 2) == 0) {
                    func_82111CD4();
                    if (Battle_Effect_Counter() != 0) {
                        InitBattleParameters();
                        if (Battle_CalcDamage() == 0) {
                            effect = sBattleUser->moveCache.unk_01;
                            goto block_29;
                        }
                        func_82111AC4();
                        func_8210F8E8();
                    } else {
                        goto block_24;
                    }
                }
                HandleMoveEffectFlags();
            case 5:
            block_24:
                if (sBattleMoveFailed != 0) {
                    user = sBattleUser;
                    effect = user->moveCache.unk_01;
                    switch (effect) {
                        case 7: // Explosion / Self-Destruct
                            goto block_28;
                        default:
                            goto block_29;
                    }
                }
            case 6:
                // FAKE: the self-assignment leaves a no-code statement on the case 6
                // entry, which keeps the case 7 branch above (b to the next instruction).
                user = sBattleUser;
                user = user;
            block_28:
                func_82111A78();
                user = sBattleUser;
            block_29a:
                effect = user->moveCache.unk_01;
            block_29:
                switch (effect) {
                    case 9: // Mirror Move
                        if (func_821119F8() == 0) {
                            break;
                        }
                        D_82199F41 = 0;
                        goto block_5;
                    case 0x53: // Metronome
                        Battle_Effect_Metronome();
                        goto block_5;
                    default:
                        if (IsByteInArray(effect, D_8218AD64, 0x1B) != 0) {
                            Battle_ExecuteMoveEffect();
                            return;
                        }
                        if (sBattleMoveFailed != 0) {
                            Battle_QueueMoveFailureAndApplyRecoil();
                            if (sBattleUser->moveCache.unk_01 != 7) {
                                break;
                            }
                        } else {
                            Battle_ApplyDamageAnimation();
                            Battle_PlayMoveSound();
                            Battle_UpdateBattleLog();
                            D_82199F36 = 1;
                        }
                        if (IsByteInArray(sBattleUser->moveCache.unk_01, D_8218AD80, 0xA) != 0) {
                            Battle_ExecuteMoveEffect();
                        }
                        if (sBattleTarget->unk_0C == 0) {
                            return;
                        }
                        Battle_ApplyRageContinuation();
                        if (sBattleUser->unk_4C & 4) {
                            sBattleUser->unk_4F--;
                            if (sBattleUser->unk_4F != 0) {
                                goto block_28;
                            }
                            sBattleUser->unk_4C &= ~4;
                            sprintf(sp2C, D_8219574C, sBattleUser->unk_54);
                            func_8211EF74(D_8219A520 + 0x3C8, 4, D_8218C714, sp2C);
                            sBattleScene.scene->unk_1A = 1;
                            sBattleUser->unk_54 = 0;
                        }
                        if (sBattleUser->moveCache.unk_01 == 0) {
                            break;
                        }
                        if (IsByteInArray(sBattleUser->moveCache.unk_01, D_8218AD8C, 0x10) != 0) {
                            break;
                        }
                        Battle_ExecuteMoveEffect();
                        break;
                }
                break;
            default:
                break;
        }
    }
    D_82199F43 = 0;
}

s32 func_82107A5C(ActivePokemon*);
s32 func_82107F88(ActivePokemon*);
void func_8210F730(ActivePokemon*);
extern s32 D_8218C710;
void func_821129E4(ActivePokemon* arg0) {
    UNUSED s32 pad;
    s32 sp1C = func_82107A5C(arg0);
    ActivePokemonState* temp_a10;
    BattleMonRuntime* temp_a11;
    BattleMonRuntime* temp_a01;

    temp_a10 = &sActivePokemon[sp1C]->state;
    temp_a11 = &sActivePokemon[sp1C]->state.runtime;
    temp_a01 = &sActivePokemon[!sp1C]->state.runtime;

    temp_a01->unk_54 = 0;
    temp_a01->unk_58 = 0;
    temp_a01->unk_4C &= ~4;

    temp_a11->unk_4A = 0;
    temp_a11->unk_4B = 0;
    temp_a11->unk_4C = 0;
    temp_a11->unk_4D &= 0x80;
    temp_a11->unk_4E = 0;
    temp_a11->unk_52 = 0;
    temp_a11->unk_57 = 0;
    temp_a11->scaleResize = 0;
    temp_a11->unk_58 = 0;

    if (temp_a10->unk_2D != 0xF) {
        temp_a10->unk_2D = 0x11;
    }

    func_8210F730(arg0);
    func_8211EF74((s32)&((u8(*)[0x40])(D_8219A520 + 0x448))[sp1C], 3, D_8218C710, func_82107F88(sActivePokemon[sp1C]));
}

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

void func_82110B44(ActivePokemon*);
void func_8210F2F4(ActivePokemon*);
void func_821125C0(void);
void func_821132C8(void)
{
  BattleMonRuntime *sp1C = &sActivePokemon[sBattleScene.scene->unk_2C]->state.runtime;
  BattleMonRuntime *sp18 = &sActivePokemon[!sBattleScene.scene->unk_2C]->state.runtime;
  ActivePokemonState *ptr1 = &sActivePokemon[0]->state;
  ActivePokemonState *ptr2 = &sActivePokemon[1]->state;
  ptr1->unk_2A = 0;
  ptr2->unk_2A = 0;
  sConfused = 1;
  sStatCanBeChangedFurther = 1;
  sBattleScene.scene->unk_1A = 0;
  sBattleScene.scene->unk_4C = 0;
  sBattleScene.scene->unk_48 = 0;
  sp1C->unk_12 = 0xFFFF;
  sp18->unk_12 = 0xFFFF;
  Battle_ClearAllMessageQueues();
  func_82110B44(sActivePokemon[0]);
  func_82110B44(sActivePokemon[1]);
  sBattleUser = sp1C;
  sBattleTarget = sp18;
  if ((sBattleScene.scene->unk_1C == 6) || (sBattleScene.scene->unk_1C == 5))
  {
    sBattleUser->unk_0C = 0x384;
    sBattleTarget->unk_0C = 0x384;
    func_8210F2F4(sActivePokemon[0]);
    func_8210F2F4(sActivePokemon[1]);
    func_821125C0();
    sBattleUser->unk_0C = 0x384;
    sBattleTarget->unk_0C = 0x384;
    sBattleUser->unk_0E = 0x384;
    sBattleTarget->unk_0E = 0x384;
    sBattleUser->unk_10 = 0x384;
    sBattleTarget->unk_10 = 0x384;
    func_8210F2F4(sActivePokemon[0]);
    func_8210F2F4(sActivePokemon[1]);
    Battle_ApplyResidualEffects();
    if (sp1C->unk_4F == 0)
    {
      sp1C->unk_4C &= ~0x20;
    }
    if (!sp18->unk_4F)
    {
      sp18->unk_4C &= ~0x20;
    }
    ((BattleMonRuntime *) D_8219A3C0)->unk_0C = 0x384; // FAKE: alias of sBattleUser via s8* symbol
    ((BattleMonRuntime *) D_8219A3C4)->unk_0C = 0x384; // FAKE: alias of sBattleTarget
    ((BattleMonRuntime *) D_8219A3C0)->unk_0E = 0x384; // FAKE
    ((BattleMonRuntime *) D_8219A3C4)->unk_0E = 0x384; // FAKE
    ((BattleMonRuntime *) D_8219A3C0)->unk_10 = 0x384; // FAKE
    ((BattleMonRuntime *) D_8219A3C4)->unk_10 = 0x384; // FAKE
    func_8210F2F4(sActivePokemon[0]);
    func_8210F2F4(sActivePokemon[1]);
    return;
  }
  func_821125C0();
  Battle_ApplyResidualEffects();
  if (sp1C->unk_4F == 0)
  {
    sp1C->unk_4C &= ~0x20;
  }
  if (sp18->unk_4F == 0)
  {
    sp18->unk_4C &= ~0x20;
  }
  Battle_CheckFaintAfterMove();
}

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
