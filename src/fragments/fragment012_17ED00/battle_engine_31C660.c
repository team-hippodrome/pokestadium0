/* Stadium Zero fragment012_17ED00. */
/* C ported from the Stadium 1 decomp: src/fragments/battle_engine/battle_engine_31C660.c, src/fragments/battle_engine/battle_engine_35DF70.c. */

#include "fragments/battle_engine/battle_engine.h"
#include "model_renderer.h"

#include "fragments/battle_engine/battle_engine.h"
#include "moves.h"
#include "text_system.h"

s32 BattleMessage_Format(s32, s32, s32, ...);
extern s32 D_8219A520;
s32 ActivePokemon_GetNickname(ActivePokemon*);
typedef void (*func_D_8438AE50)(void);
extern func_D_8438AE50 sMoveEffectHandlers[];

void func_82113660(void);
void BattleEffect_Explosion(void);

void func_82113660(void) {
}

extern s32 D_8218C7BC;
extern s32 D_8218C7C0;
extern s32 D_8218C7C4;
/**
 * Move effects 0x01 and 0x20 (Gen 1 SleepEffect): puts the target to sleep for 1-3 turns unless
 * it already has a status, the move misses or Sleep Clause applies. Sets moveEffectKind 0x16.
 * @unverified Name from its slots in sMoveEffectHandlers, which follow the Gen 1 effect table.
 */
void Battle_Effect_Sleep(void) {
    s32 sp24;
    s32 var_v1;

    sBattleScene.scene->moveEffectKind = 0x16;
    sp24 = sBattleTarget->volatileStatusFlags & 0x20;
    sBattleTarget->volatileStatusFlags &= ~0x20;

    if (sp24 == 0) {
        if (sBattleTarget->pendingStatusCondition & 7) {
            sConfused = 0;
            BattleMessage_Format(D_8219A520 + 0x88, -0x80, D_8218C7BC, ActivePokemon_GetNickname(sActivePokemon[!sBattleScene.scene->actingSide]));
            return;
        }

        if (sBattleTarget->pendingStatusCondition == 0) {
            Battle_MoveHitTest();
            if ((sBattleMoveFailed == 0) && (Battle_SleepClauseInEffect(sActivePokemon[!sBattleScene.scene->actingSide]) == 0)) {
                goto block_9;
            }
        }
        sConfused = 0;
        BattleMessage_Format(D_8219A520 + 0x88, -0x7F, D_8218C7C0, ActivePokemon_GetNickname(sActivePokemon[!sBattleScene.scene->actingSide]));
        return;
    }

block_9:
    if (Battle_SleepClauseInEffect(sActivePokemon[!sBattleScene.scene->actingSide]) != 0) {
        sConfused = 0;
        BattleMessage_Format(D_8219A520 + 0x88, -0x7F, D_8218C7C0, ActivePokemon_GetNickname(sActivePokemon[!sBattleScene.scene->actingSide]));
    } else {
        do {
            var_v1 = Battle_Random() & 3;
        } while (var_v1 == 0);
        sBattleTarget->pendingStatusCondition = var_v1;
        BattleMessage_Format(D_8219A520 + 0x88, -0x7E, D_8218C7C4, ActivePokemon_GetNickname(sActivePokemon[!sBattleScene.scene->actingSide]));
    }
}

extern s32 D_8218C7C8;
extern s32 D_8218C7CC;
extern s32 D_8218C7D0;
extern s32 D_8218C7D4;

// Matches the ROM, but uses rodata data that is not placed in this file yet.
void Battle_Effect_Poison(void) {
    s32 sp1C = D_8219A520 + 0x88;

    if (!(sBattleTarget->volatileStatusFlags & 0x10) && (sBattleTarget->pendingStatusCondition == 0) && (sBattleTarget->roster[6] != 3) &&
        (sBattleTarget->roster[7] != 3)) {
        switch (sBattleUser->moveCache.effect) {
            case 2:
                if (sBattleScene.scene->moveEffectKind != 0x18) {
                    sBattleScene.scene->moveEffectKind = 0;
                    sp1C = D_8219A520 + 0x208;
                } else {
                    sp1C = D_8219A520 + 0x308;
                }

                if (Battle_Random() >= 0x34) {
                    return;
                }
                break;

            case 33:
                sBattleScene.scene->moveEffectKind = 0;
                sp1C = D_8219A520 + 0x208;
                if (Battle_Random() >= 0x67) {
                    return;
                }
                break;

            default:
                sBattleScene.scene->moveEffectKind = 0x16;
                sTypeEffectiveness = 0xA;
                Battle_MoveHitTest();
                if (sBattleMoveFailed != 0) {
                    BattleMessage_Format(sp1C, -0x7D, D_8218C7C8, ActivePokemon_GetNickname(sActivePokemon[!sBattleScene.scene->actingSide]));
                    return;
                }
                break;
        }

        sBattleTarget->pendingStatusCondition |= 8;
        if (sBattleUser->moveCache.lastMove == TOXIC) {
            sBattleTarget->uniqueStatusFlags |= 1;
            sBattleTarget->toxicCounter = 0;
            BattleMessage_Format(sp1C, -0x7C, D_8218C7CC, ActivePokemon_GetNickname(sActivePokemon[!sBattleScene.scene->actingSide]));
        } else {
            BattleMessage_Format(sp1C, -0x7B, D_8218C7D0, ActivePokemon_GetNickname(sActivePokemon[!sBattleScene.scene->actingSide]));
        }
    } else if (sBattleUser->moveCache.effect == 0x42) {
        if (sBattleScene.scene->moveEffectKind != 0x18) {
            sBattleMoveFailed = 1;
            sBattleScene.scene->moveEffectKind = 0x16;
            sConfused = 0;
        }
        BattleMessage_Format(sp1C, -0x7A, D_8218C7D4, ActivePokemon_GetNickname(sActivePokemon[!sBattleScene.scene->actingSide]));
    }
}

extern s32 D_8218C7D8;
extern s32 D_8218C7DC;

// Matches the ROM, but uses rodata data that is not placed in this file yet.
void Battle_Effect_DrainHP(void) {
    sBattleDamage /= 2;
    if (sBattleDamage == 0) {
        sBattleDamage = 1;
    }

    if (sBattleUser->maxHp < sBattleUser->hp + sBattleDamage) {
        sBattleUser->hp = sBattleUser->maxHp;
    } else {
        sBattleUser->hp += sBattleDamage;
    }

    if (sBattleUser->moveCache.effect == 8) {
        BattleMessage_Format(D_8219A520 + 0x208, -0x79, D_8218C7D8, ActivePokemon_GetNickname(sActivePokemon[!sBattleScene.scene->actingSide]));
    } else {
        BattleMessage_Format(D_8219A520 + 0x208, -0x78, D_8218C7DC, ActivePokemon_GetNickname(sActivePokemon[!sBattleScene.scene->actingSide]));
    }
}

/**
 * Faint the user of Explosion/Self-Destruct and clear its major status and Leech Seed.
 * @unverified Name and comment from Stadium 1.
 */
void BattleEffect_Explosion(void) {
    sBattleScene.scene->moveEffectKind = 0x1E;
    sBattleUser->hp = 0;
    sBattleUser->pendingStatusCondition = 0;
    sBattleUser->volatileStatusFlags &= ~0x80;
}

extern s32 D_8218C7E0;
extern s32 D_8218C7E4;
extern s32 D_8218C7E8;
extern s32 D_8218C7EC;
/**
 * Move effects 0x04-0x06 and 0x22-0x24 (Gen 1 FreezeBurnParalyzeEffect): the 10% or 30% side
 * effect that burns, freezes or paralyzes the target. A Fire move thaws a frozen target.
 * In the per-move sweep only Fire Punch, Ice Punch and Thunder Punch (7-9) of moves 1-27 ran it.
 */
void Battle_Effect_FreezeBurnParalyze(void) {
    if (sBattleTarget->volatileStatusFlags & 0x10) {
        return;
    }

    if (sBattleTarget->pendingStatusCondition != 0) {
        if ((sBattleTarget->pendingStatusCondition & 0x20) && (sBattleUser->moveCache.type == 0x14)) {
            sBattleTarget->pendingStatusCondition = 0;
            BattleMessage_Format(D_8219A520 + 0x88, -0x77, D_8218C7E0, ActivePokemon_GetNickname(sActivePokemon[!sBattleScene.scene->actingSide]));
        }
        return;
    }

    if ((sBattleTarget->roster[6] != (*sBattleUser).moveCache.type) &&
        (sBattleTarget->roster[7] != (*sBattleUser).moveCache.type)) {
        if ((sBattleUser->moveCache.effect < 7) || (sBattleUser->moveCache.lastMove == BLIZZARD)) {
            if (Battle_Random() >= 0x1A) {
                return;
            }
        } else if (Battle_Random() >= 0x4D) {
            return;
        }

        switch (sBattleUser->moveCache.effect) {
            case 4:
            case 34:
                sBattleTarget->pendingStatusCondition = 0x10;
                ApplyBurnAttackCut(sActivePokemon[!sBattleScene.scene->actingSide]);
                BattleMessage_Format(D_8219A520 + 0x208, -0x76, D_8218C7E4, ActivePokemon_GetNickname(sActivePokemon[!sBattleScene.scene->actingSide]));
                break;

            case 5:
            case 35:
                if (Battle_FreezeClauseInEffect(sActivePokemon[!sBattleScene.scene->actingSide]) == 0) {
                    sBattleTarget->volatileStatusFlags &= ~0x20;
                    sBattleTarget->pendingStatusCondition = 0x20;
                    BattleMessage_Format(D_8219A520 + 0x208, -0x75, D_8218C7E8, ActivePokemon_GetNickname(sActivePokemon[!sBattleScene.scene->actingSide]));
                }
                break;

            case 6:
            case 36:
                sBattleTarget->pendingStatusCondition = 0x40;
                ApplyParalysisSpeedCut(sActivePokemon[!sBattleScene.scene->actingSide]);
                BattleMessage_Format(D_8219A520 + 0x208, -0x74, D_8218C7EC, ActivePokemon_GetNickname(sActivePokemon[!sBattleScene.scene->actingSide]));
                break;
        }
    }
}

extern StatStageMultiplier D_8218ADF4[];
extern s32 D_8218C7F0;
extern s32 D_8218C808;
extern s32 D_8218C820;
/**
 * Apply the Rage follow-up stat boost, using its separate message queue.
 * @unverified Name and comment from Stadium 1, matched by code similarity.
 */
void BattleEffect_ApplyStatBoost(void) {
    s32 sp24;
    s32 var_a3;
    u16* sp1C;
    u16* sp18;

    sBattleScene.scene->rageFollowupPhase = 0xA;

    var_a3 = 1;
    sp24 = sBattleUser->moveCache.effect - 0xA;

    if (sp24 >= 8) {
        var_a3 = 2;
        sp24 -= 0x28;
    }

    if (sBattleUser->unk_5C[sp24] != 0xD) {
        sBattleUser->unk_5C[sp24] += var_a3;
        if (sBattleUser->unk_5C[sp24] >= 0xE) {
            sBattleUser->unk_5C[var_a3] = 0xD;
        }

        if (sp24 < 4) {
            switch (sp24) {
                case 0:
                    sp18 = &sBattleUser->unmodifiedAttack;
                    sp1C = &sBattleUser->modifiedAttack;
                    break;

                case 1:
                    sp18 = &sBattleUser->unmodifiedDefense;
                    sp1C = &sBattleUser->modifiedDefense;
                    break;

                case 2:
                    sp18 = &sBattleUser->unmodifiedSpeed;
                    sp1C = &sBattleUser->speed;
                    break;

                case 3:
                    sp18 = &sBattleUser->unmodifiedSpecial;
                    sp1C = &sBattleUser->modifiedSpecial;
                    break;
            }

            if (*sp1C != 0x3E7) {
                *sp1C = (*sp18 * D_8218ADF4[sBattleUser->unk_5C[sp24] - 1].multiplier) /
                        D_8218ADF4[sBattleUser->unk_5C[sp24] - 1].divisor;
                if (*sp1C >= 0x3E8) {
                    *sp1C = 0x3E7;
                }
            } else {
                goto block_29;
            }
        }

        if (sBattleUser->moveCache.lastMove == MINIMIZE) {
            sBattleUser->scaleResize = 1;
        }

        if (var_a3 == 2) {
            BattleMessage_Format(D_8219A520 + 0x2C8, (s8)(sp24 + 0x8D), (&D_8218C7F0)[sp24], ActivePokemon_GetNickname(sActivePokemon[!sBattleScene.scene->actingSide]));
        } else {
            BattleMessage_Format(D_8219A520 + 0x2C8, (s8)(sp24 + 0x93), (&D_8218C808)[sp24], ActivePokemon_GetNickname(sActivePokemon[!sBattleScene.scene->actingSide]));
        }

        ApplyParalysisSpeedCut(sActivePokemon[!sBattleScene.scene->actingSide]);
        ApplyBurnAttackCut(sActivePokemon[!sBattleScene.scene->actingSide]);
    } else {
    block_29:
        BattleMessage_Format(D_8219A520 + 0x2C8, -0x67, D_8218C820);
    }
}

extern u8 sStatCanBeChangedFurther;
/**
 * Move effects 0x0A-0x0F and 0x32-0x37 (Gen 1 StatModifierUpEffect): raises one of the user's
 * stat stages by 1 or 2 and recomputes the stat. Sets moveEffectKind 7.
 * Ran in play for Swords Dance and COM's Double Team (「かいひりつが あがった！」).
 */
void Battle_Effect_StatUp(void) {
    s32 sp24;
    s32 var_a3;
    u16* sp1C;
    u16* sp18;

    sBattleScene.scene->moveEffectKind = 7;

    var_a3 = 1;
    sp24 = sBattleUser->moveCache.effect - 0xA;

    if (sp24 >= 8) {
        var_a3 = 2;
        sp24 -= 0x28;
    }

    if (sBattleUser->unk_5C[sp24] != 0xD) {
        sBattleUser->unk_5C[sp24] += var_a3;
        if (sBattleUser->unk_5C[sp24] >= 0xE) {
            sBattleUser->unk_5C[sp24] = 0xD;
        }

        if (sp24 < 4) {
            switch (sp24) {
                case 0:
                    sp18 = &sBattleUser->unmodifiedAttack;
                    sp1C = &sBattleUser->modifiedAttack;
                    break;

                case 1:
                    sp18 = &sBattleUser->unmodifiedDefense;
                    sp1C = &sBattleUser->modifiedDefense;
                    break;

                case 2:
                    sp18 = &sBattleUser->unmodifiedSpeed;
                    sp1C = &sBattleUser->speed;
                    break;

                case 3:
                    sp18 = &sBattleUser->unmodifiedSpecial;
                    sp1C = &sBattleUser->modifiedSpecial;
                    break;
            }

            if (*sp1C != 0x3E7) {
                *sp1C = (*sp18 * D_8218ADF4[sBattleUser->unk_5C[sp24] - 1].multiplier) /
                        D_8218ADF4[sBattleUser->unk_5C[sp24] - 1].divisor;
                if (*sp1C >= 0x3E8) {
                    *sp1C = 0x3E7;
                }
            } else {
                goto block_29;
            }
        }

        if (sBattleUser->moveCache.lastMove == MINIMIZE) {
            sBattleUser->scaleResize = 1;
        }

        if (var_a3 == 2) {
            BattleMessage_Format(D_8219A520 + 0x88, (s8)(sp24 + 0x8D), (&D_8218C7F0)[sp24], ActivePokemon_GetNickname(sActivePokemon[sBattleScene.scene->actingSide]));
        } else {
            BattleMessage_Format(D_8219A520 + 0x88, (s8)(sp24 + 0x93), (&D_8218C808)[sp24], ActivePokemon_GetNickname(sActivePokemon[sBattleScene.scene->actingSide]));
        }

        ApplyParalysisSpeedCut(sActivePokemon[sBattleScene.scene->actingSide]);
        ApplyBurnAttackCut(sActivePokemon[sBattleScene.scene->actingSide]);
    } else {
    block_29:
        sStatCanBeChangedFurther = 0;
        BattleMessage_Format(D_8219A520 + 0x88, -0x67, D_8218C820);
    }
}

extern StatStageMultiplier D_8218ADF4[];
extern u8 D_82199F36;
extern s32 D_8218C824;
extern s32 D_8218C83C;
extern s32 D_8218C854;
extern s32 D_8218C858;

// Matches the ROM, but uses rodata data that is not placed in this file yet.
void Battle_Effect_LowerStat(void) {
    s32 sp24;
    s32 sp20;
    u16* sp1C;
    u16* sp18;

    if (sBattleUser->moveCache.effect < 0x44) {
        sBattleScene.scene->moveEffectKind = 0x1A;
    } else {
        sBattleScene.scene->hitReactionKind = 3;
    }

    if (sBattleTarget->volatileStatusFlags & 0x10) {
        goto end;
    }

    sp24 = sBattleUser->moveCache.effect;
    sp20 = 1;

    if (sp24 >= 0x44) {
        if (Battle_Random() < 0x55) {
            sp24 -= 0x44;
            goto block_14;
        }
    } else {
        Battle_MoveHitTest();

        if (sBattleMoveFailed != 0) {
            goto end;
        }

        if (sBattleTarget->immobilizedReason & 0x40) {
            goto end;
        }

        sp24 -= 0x12;
        if (sp24 >= 9) {
            sp20 = 2;
            sp24 -= 0x28;
        }

    block_14:
        if (sBattleTarget->unk_5C[sp24] != 1) {
            sBattleTarget->unk_5C[sp24] -= sp20;
            if (sBattleTarget->unk_5C[sp24] <= 0) {
                sBattleTarget->unk_5C[sp24] = 1;
            }

            if (sp24 < 4) {
                switch (sp24) {
                    case 0:
                        sp18 = &sBattleTarget->unmodifiedAttack;
                        sp1C = &sBattleTarget->modifiedAttack;
                        break;

                    case 1:
                        sp18 = &sBattleTarget->unmodifiedDefense;
                        sp1C = &sBattleTarget->modifiedDefense;
                        break;

                    case 2:
                        sp18 = &sBattleTarget->unmodifiedSpeed;
                        sp1C = &sBattleTarget->speed;
                        break;

                    case 3:
                        sp18 = &sBattleTarget->unmodifiedSpecial;
                        sp1C = &sBattleTarget->modifiedSpecial;
                        break;
                }

                if (*sp1C != 1) {
                    *sp1C = (*sp18 * D_8218ADF4[sBattleTarget->unk_5C[sp24] - 1].multiplier) /
                            D_8218ADF4[sBattleTarget->unk_5C[sp24] - 1].divisor;
                    if (*sp1C == 0) {
                        *sp1C = 1;
                    }
                } else {
                    goto block_39;
                }
            }

            if (sp20 == 2) {
                BattleMessage_Format(D_8219A520 + 0x208, (s8)(sp24 + 0x9A), (&D_8218C824)[sp24], ActivePokemon_GetNickname(sActivePokemon[!sBattleScene.scene->actingSide]));
            } else {
                BattleMessage_Format(D_8219A520 + 0x208, (s8)(sp24 + 0xA0), (&D_8218C83C)[sp24], ActivePokemon_GetNickname(sActivePokemon[!sBattleScene.scene->actingSide]));
            }

            ApplyParalysisSpeedCut(sActivePokemon[!sBattleScene.scene->actingSide]);

            ApplyBurnAttackCut(sActivePokemon[!sBattleScene.scene->actingSide]);
            return;
        }
    }

block_39:
    if (sBattleUser->moveCache.effect < 0x44) {
        sConfused = 0;
        sStatCanBeChangedFurther = 0;
        BattleMessage_Format(D_8219A520 + 0x208, -0x5A, D_8218C854);
        return;
    }

end:
    if (sBattleUser->moveCache.effect < 0x44) {
        sConfused = 0;
        sStatCanBeChangedFurther = 0;
        if (D_82199F36 == 0) {
            BattleMessage_Format(D_8219A520 + 0x208, -0x59, D_8218C858);
        }
    } else {
        sStatCanBeChangedFurther = 0;
    }
}
