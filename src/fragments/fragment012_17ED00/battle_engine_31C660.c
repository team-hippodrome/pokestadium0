/* Stadium Zero fragment012_17ED00. */
/* C ported from the Stadium 1 decomp: src/fragments/battle_engine/battle_engine_31C660.c, src/fragments/battle_engine/battle_engine_35DF70.c. */

#include "fragments/battle_engine/battle_engine.h"
#include "model_renderer.h"

#include "fragments/battle_engine/battle_engine.h"
#include "moves.h"
#include "text_system.h"

s32 func_8211EF74(s32, s32, s32, ...);
extern s32 D_8219A520;
s32 func_82107F88(ActivePokemon*);
typedef void (*func_D_8438AE50)(void);
extern func_D_8438AE50 sMoveEffectHandlers[];

void func_82113660(void);
void BattleEffect_Explosion(void);

void func_82113660(void) {
}

extern s32 D_8218C7BC;
extern s32 D_8218C7C0;
extern s32 D_8218C7C4;
void func_82113668(void) {
    s32 sp24;
    s32 var_v1;

    sBattleScene.scene->unk_48 = 0x16;
    sp24 = sBattleTarget->unk_4D & 0x20;
    sBattleTarget->unk_4D &= ~0x20;

    if (sp24 == 0) {
        if (sBattleTarget->unk_15 & 7) {
            sConfused = 0;
            func_8211EF74(D_8219A520 + 0x88, -0x80, D_8218C7BC, func_82107F88(sActivePokemon[!sBattleScene.scene->unk_2C]));
            return;
        }

        if (sBattleTarget->unk_15 == 0) {
            HandleMoveEffectFlags();
            if ((sBattleMoveFailed == 0) && (Battle_SleepClauseInEffect(sActivePokemon[!sBattleScene.scene->unk_2C]) == 0)) {
                goto block_9;
            }
        }
        sConfused = 0;
        func_8211EF74(D_8219A520 + 0x88, -0x7F, D_8218C7C0, func_82107F88(sActivePokemon[!sBattleScene.scene->unk_2C]));
        return;
    }

block_9:
    if (Battle_SleepClauseInEffect(sActivePokemon[!sBattleScene.scene->unk_2C]) != 0) {
        sConfused = 0;
        func_8211EF74(D_8219A520 + 0x88, -0x7F, D_8218C7C0, func_82107F88(sActivePokemon[!sBattleScene.scene->unk_2C]));
    } else {
        do {
            var_v1 = Battle_Random() & 3;
        } while (var_v1 == 0);
        sBattleTarget->unk_15 = var_v1;
        func_8211EF74(D_8219A520 + 0x88, -0x7E, D_8218C7C4, func_82107F88(sActivePokemon[!sBattleScene.scene->unk_2C]));
    }
}

extern s32 D_8218C7C8;
extern s32 D_8218C7CC;
extern s32 D_8218C7D0;
extern s32 D_8218C7D4;

// Matches the ROM, but uses rodata data that is not placed in this file yet.
void Battle_Effect_Poison(void) {
    s32 sp1C = D_8219A520 + 0x88;

    if (!(sBattleTarget->unk_4D & 0x10) && (sBattleTarget->unk_15 == 0) && (sBattleTarget->roster[6] != 3) &&
        (sBattleTarget->roster[7] != 3)) {
        switch (sBattleUser->moveCache.unk_01) {
            case 2:
                if (sBattleScene.scene->unk_48 != 0x18) {
                    sBattleScene.scene->unk_48 = 0;
                    sp1C = D_8219A520 + 0x208;
                } else {
                    sp1C = D_8219A520 + 0x308;
                }

                if (Battle_Random() >= 0x34) {
                    return;
                }
                break;

            case 33:
                sBattleScene.scene->unk_48 = 0;
                sp1C = D_8219A520 + 0x208;
                if (Battle_Random() >= 0x67) {
                    return;
                }
                break;

            default:
                sBattleScene.scene->unk_48 = 0x16;
                sTypeEffectiveness = 0xA;
                HandleMoveEffectFlags();
                if (sBattleMoveFailed != 0) {
                    func_8211EF74(sp1C, -0x7D, D_8218C7C8, func_82107F88(sActivePokemon[!sBattleScene.scene->unk_2C]));
                    return;
                }
                break;
        }

        sBattleTarget->unk_15 |= 8;
        if (sBattleUser->moveCache.lastMove == TOXIC) {
            sBattleTarget->unk_4E |= 1;
            sBattleTarget->unk_51 = 0;
            func_8211EF74(sp1C, -0x7C, D_8218C7CC, func_82107F88(sActivePokemon[!sBattleScene.scene->unk_2C]));
        } else {
            func_8211EF74(sp1C, -0x7B, D_8218C7D0, func_82107F88(sActivePokemon[!sBattleScene.scene->unk_2C]));
        }
    } else if (sBattleUser->moveCache.unk_01 == 0x42) {
        if (sBattleScene.scene->unk_48 != 0x18) {
            sBattleMoveFailed = 1;
            sBattleScene.scene->unk_48 = 0x16;
            sConfused = 0;
        }
        func_8211EF74(sp1C, -0x7A, D_8218C7D4, func_82107F88(sActivePokemon[!sBattleScene.scene->unk_2C]));
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

    if (sBattleUser->unk_28 < sBattleUser->unk_0C + sBattleDamage) {
        sBattleUser->unk_0C = sBattleUser->unk_28;
    } else {
        sBattleUser->unk_0C += sBattleDamage;
    }

    if (sBattleUser->moveCache.unk_01 == 8) {
        func_8211EF74(D_8219A520 + 0x208, -0x79, D_8218C7D8, func_82107F88(sActivePokemon[!sBattleScene.scene->unk_2C]));
    } else {
        func_8211EF74(D_8219A520 + 0x208, -0x78, D_8218C7DC, func_82107F88(sActivePokemon[!sBattleScene.scene->unk_2C]));
    }
}

/**
 * Faint the user of Explosion/Self-Destruct and clear its major status and Leech Seed.
 * @unverified Name and comment from Stadium 1.
 */
void BattleEffect_Explosion(void) {
    sBattleScene.scene->unk_48 = 0x1E;
    sBattleUser->unk_0C = 0;
    sBattleUser->unk_15 = 0;
    sBattleUser->unk_4D &= ~0x80;
}

extern s32 D_8218C7E0;
extern s32 D_8218C7E4;
extern s32 D_8218C7E8;
extern s32 D_8218C7EC;
void func_82113CD0(void) {
    if (sBattleTarget->unk_4D & 0x10) {
        return;
    }

    if (sBattleTarget->unk_15 != 0) {
        if ((sBattleTarget->unk_15 & 0x20) && (sBattleUser->moveCache.unk_03 == 0x14)) {
            sBattleTarget->unk_15 = 0;
            func_8211EF74(D_8219A520 + 0x88, -0x77, D_8218C7E0, func_82107F88(sActivePokemon[!sBattleScene.scene->unk_2C]));
        }
        return;
    }

    if ((sBattleTarget->roster[6] != (*sBattleUser).moveCache.unk_03) &&
        (sBattleTarget->roster[7] != (*sBattleUser).moveCache.unk_03)) {
        if ((sBattleUser->moveCache.unk_01 < 7) || (sBattleUser->moveCache.lastMove == BLIZZARD)) {
            if (Battle_Random() >= 0x1A) {
                return;
            }
        } else if (Battle_Random() >= 0x4D) {
            return;
        }

        switch (sBattleUser->moveCache.unk_01) {
            case 4:
            case 34:
                sBattleTarget->unk_15 = 0x10;
                ApplyBurnAttackCut(sActivePokemon[!sBattleScene.scene->unk_2C]);
                func_8211EF74(D_8219A520 + 0x208, -0x76, D_8218C7E4, func_82107F88(sActivePokemon[!sBattleScene.scene->unk_2C]));
                break;

            case 5:
            case 35:
                if (Battle_FreezeClauseInEffect(sActivePokemon[!sBattleScene.scene->unk_2C]) == 0) {
                    sBattleTarget->unk_4D &= ~0x20;
                    sBattleTarget->unk_15 = 0x20;
                    func_8211EF74(D_8219A520 + 0x208, -0x75, D_8218C7E8, func_82107F88(sActivePokemon[!sBattleScene.scene->unk_2C]));
                }
                break;

            case 6:
            case 36:
                sBattleTarget->unk_15 = 0x40;
                ApplyParalysisSpeedCut(sActivePokemon[!sBattleScene.scene->unk_2C]);
                func_8211EF74(D_8219A520 + 0x208, -0x74, D_8218C7EC, func_82107F88(sActivePokemon[!sBattleScene.scene->unk_2C]));
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

    sBattleScene.scene->unk_4C = 0xA;

    var_a3 = 1;
    sp24 = sBattleUser->moveCache.unk_01 - 0xA;

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
                    sp18 = &sBattleUser->unk_38;
                    sp1C = &sBattleUser->unk_2A;
                    break;

                case 1:
                    sp18 = &sBattleUser->unk_3A;
                    sp1C = &sBattleUser->unk_2C;
                    break;

                case 2:
                    sp18 = &sBattleUser->unk_3C;
                    sp1C = &sBattleUser->speed;
                    break;

                case 3:
                    sp18 = &sBattleUser->unk_3E;
                    sp1C = &sBattleUser->unk_30;
                    break;
            }

            if (*sp1C != 0x3E7) {
                *sp1C = (*sp18 * D_8218ADF4[sBattleUser->unk_5C[sp24] - 1].unk_00) /
                        D_8218ADF4[sBattleUser->unk_5C[sp24] - 1].unk_01;
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
            func_8211EF74(D_8219A520 + 0x2C8, (s8)(sp24 + 0x8D), (&D_8218C7F0)[sp24], func_82107F88(sActivePokemon[!sBattleScene.scene->unk_2C]));
        } else {
            func_8211EF74(D_8219A520 + 0x2C8, (s8)(sp24 + 0x93), (&D_8218C808)[sp24], func_82107F88(sActivePokemon[!sBattleScene.scene->unk_2C]));
        }

        ApplyParalysisSpeedCut(sActivePokemon[!sBattleScene.scene->unk_2C]);
        ApplyBurnAttackCut(sActivePokemon[!sBattleScene.scene->unk_2C]);
    } else {
    block_29:
        func_8211EF74(D_8219A520 + 0x2C8, -0x67, D_8218C820);
    }
}

extern u8 sStatCanBeChangedFurther;
void func_821142B8(void) {
    s32 sp24;
    s32 var_a3;
    u16* sp1C;
    u16* sp18;

    sBattleScene.scene->unk_48 = 7;

    var_a3 = 1;
    sp24 = sBattleUser->moveCache.unk_01 - 0xA;

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
                    sp18 = &sBattleUser->unk_38;
                    sp1C = &sBattleUser->unk_2A;
                    break;

                case 1:
                    sp18 = &sBattleUser->unk_3A;
                    sp1C = &sBattleUser->unk_2C;
                    break;

                case 2:
                    sp18 = &sBattleUser->unk_3C;
                    sp1C = &sBattleUser->speed;
                    break;

                case 3:
                    sp18 = &sBattleUser->unk_3E;
                    sp1C = &sBattleUser->unk_30;
                    break;
            }

            if (*sp1C != 0x3E7) {
                *sp1C = (*sp18 * D_8218ADF4[sBattleUser->unk_5C[sp24] - 1].unk_00) /
                        D_8218ADF4[sBattleUser->unk_5C[sp24] - 1].unk_01;
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
            func_8211EF74(D_8219A520 + 0x88, (s8)(sp24 + 0x8D), (&D_8218C7F0)[sp24], func_82107F88(sActivePokemon[sBattleScene.scene->unk_2C]));
        } else {
            func_8211EF74(D_8219A520 + 0x88, (s8)(sp24 + 0x93), (&D_8218C808)[sp24], func_82107F88(sActivePokemon[sBattleScene.scene->unk_2C]));
        }

        ApplyParalysisSpeedCut(sActivePokemon[sBattleScene.scene->unk_2C]);
        ApplyBurnAttackCut(sActivePokemon[sBattleScene.scene->unk_2C]);
    } else {
    block_29:
        sStatCanBeChangedFurther = 0;
        func_8211EF74(D_8219A520 + 0x88, -0x67, D_8218C820);
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

    if (sBattleUser->moveCache.unk_01 < 0x44) {
        sBattleScene.scene->unk_48 = 0x1A;
    } else {
        sBattleScene.scene->unk_1A = 3;
    }

    if (sBattleTarget->unk_4D & 0x10) {
        goto end;
    }

    sp24 = sBattleUser->moveCache.unk_01;
    sp20 = 1;

    if (sp24 >= 0x44) {
        if (Battle_Random() < 0x55) {
            sp24 -= 0x44;
            goto block_14;
        }
    } else {
        HandleMoveEffectFlags();

        if (sBattleMoveFailed != 0) {
            goto end;
        }

        if (sBattleTarget->unk_4C & 0x40) {
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
                        sp18 = &sBattleTarget->unk_38;
                        sp1C = &sBattleTarget->unk_2A;
                        break;

                    case 1:
                        sp18 = &sBattleTarget->unk_3A;
                        sp1C = &sBattleTarget->unk_2C;
                        break;

                    case 2:
                        sp18 = &sBattleTarget->unk_3C;
                        sp1C = &sBattleTarget->speed;
                        break;

                    case 3:
                        sp18 = &sBattleTarget->unk_3E;
                        sp1C = &sBattleTarget->unk_30;
                        break;
                }

                if (*sp1C != 1) {
                    *sp1C = (*sp18 * D_8218ADF4[sBattleTarget->unk_5C[sp24] - 1].unk_00) /
                            D_8218ADF4[sBattleTarget->unk_5C[sp24] - 1].unk_01;
                    if (*sp1C == 0) {
                        *sp1C = 1;
                    }
                } else {
                    goto block_39;
                }
            }

            if (sp20 == 2) {
                func_8211EF74(D_8219A520 + 0x208, (s8)(sp24 + 0x9A), (&D_8218C824)[sp24], func_82107F88(sActivePokemon[!sBattleScene.scene->unk_2C]));
            } else {
                func_8211EF74(D_8219A520 + 0x208, (s8)(sp24 + 0xA0), (&D_8218C83C)[sp24], func_82107F88(sActivePokemon[!sBattleScene.scene->unk_2C]));
            }

            ApplyParalysisSpeedCut(sActivePokemon[!sBattleScene.scene->unk_2C]);

            ApplyBurnAttackCut(sActivePokemon[!sBattleScene.scene->unk_2C]);
            return;
        }
    }

block_39:
    if (sBattleUser->moveCache.unk_01 < 0x44) {
        sConfused = 0;
        sStatCanBeChangedFurther = 0;
        func_8211EF74(D_8219A520 + 0x208, -0x5A, D_8218C854);
        return;
    }

end:
    if (sBattleUser->moveCache.unk_01 < 0x44) {
        sConfused = 0;
        sStatCanBeChangedFurther = 0;
        if (D_82199F36 == 0) {
            func_8211EF74(D_8219A520 + 0x208, -0x59, D_8218C858);
        }
    } else {
        sStatCanBeChangedFurther = 0;
    }
}
