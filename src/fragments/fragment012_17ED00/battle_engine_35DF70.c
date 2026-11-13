/* Stadium Zero fragment012_17ED00. */
/* C ported from the Stadium 1 decomp: src/fragments/battle_engine/battle_engine_35DF70.c. */

#include "fragments/battle_engine/battle_engine.h"
#include "moves.h"
#include "text_system.h"
typedef void (*func_D_8438AE50)(void);
extern func_D_8438AE50 sMoveEffectHandlers[];

#include "m2c_macros.h"

s32 BattleMessage_Format(s32, s32, s32, ...);
extern s32 D_8219A520;
s32 ActivePokemon_GetNickname(ActivePokemon*);

void BattleEffect_Bide(void);
void BattleEffect_Thrash(void);
void BattleEffect_MultiHit(void);
void BattleEffect_Recharge(void);
void BattleEffect_Rage(void);
void BattleEffect_ExecuteMoveEffect(void);

void BattleEffect_RunMoveEffect(void);

/**
 * Start Bide with a cleared damage accumulator and a two- or three-turn duration.
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Bide.
 */
void BattleEffect_Bide(void) {
    sBattleScene.scene->moveEffectKind = 0x1B;
    sBattleUser->moveCache.effect = 0;
    sBattleUser->immobilizedReason |= 1;
    sBattleUser->effectCounter = 0;
    sBattleUser->effectTurnsLeft = (Battle_Random() & 1) + 2;
}

/**
 * Lock Thrash/Petal Dance into a two- or three-turn continuation.
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Thrash, Petal Dance.
 */
void BattleEffect_Thrash(void) {
    sBattleUser->moveCache.effect = 0;
    sBattleUser->immobilizedReason |= 2;
    sBattleUser->effectTurnsLeft = (Battle_Random() & 1) + 2;
}

extern s32 D_8218C870;
extern s32 D_8218C874;

void Battle_Effect_ForceSwitchOrFlee(void) {
    if (sBattleUser->moveCache.lastMove == TELEPORT) {
        sBattleScene.scene->moveEffectKind = 8;
        BattleMessage_Format(D_8219A520 + 0x88, -0x53, D_8218C870);
        return;
    }
    sBattleScene.scene->moveEffectKind = 8;
    BattleMessage_Format(D_8219A520 + 0x88, -0x52, D_8218C874, ActivePokemon_GetNickname(sActivePokemon[!sBattleScene.scene->actingSide]));
}

/**
 * Initialize total/remaining hits; Twineedle then uses the secondary poison effect.
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Double Slap, Comet Punch, Double Kick, Fury Attack, Twineedle, Pin Missile, Spike Cannon,
 * Barrage, Fury Swipes, Bonemerang.
 */
void BattleEffect_MultiHit(void) {
    s32 var_v1;

    if (!(sBattleUser->immobilizedReason & 4)) {
        sBattleUser->immobilizedReason |= 4;

        switch (sBattleUser->moveCache.effect) {
            case 0x4D:
                sBattleUser->moveCache.effect = 2;

            case 0x2C:
                sBattleUser->effectCounter = 2;
                sBattleUser->effectTurnsLeft = sBattleUser->effectCounter;
                break;

            default:
                var_v1 = Battle_Random() & 3;
                if (var_v1 >= 2) {
                    var_v1 = Battle_Random() & 3;
                }
                sBattleUser->effectTurnsLeft = sBattleUser->effectCounter = var_v1 + 2;
                break;
        }

        sMultihitCount = sBattleUser->effectCounter - 1;
        sBattleScene.scene->moveEffectKind = 0x18;
    }
}

u8 Battle_Random(void);

/*
 * Battle_Effect_Flinch
 *
 * Does nothing if bit 0x10 of sBattleTarget->unk_4D is set. Otherwise it clears
 * bit 0x20 of sBattleTarget->unk_4D, calls Battle_Random(), and sets bit 0x08
 * of sBattleTarget->unk_4C when the result is below a limit: 0x1A when
 * sBattleUser->moveCache.unk_01 is 0x1F, otherwise 0x4D. (Battle_Random is
 * called exactly once on each path.) What the flag bits and the limits mean
 * is not established from this function.
 *
 * The return type is void: the early `return`s compile to a jump to the
 * epilogue with no value in v0, as in the retail code.
 */
/**
 * Move effects 0x1F and 0x25 (Gen 1 FlinchSideEffect): the 10% or 30% chance to make the target
 * flinch.
 * In the per-move sweep only Stomp (23) and Rolling Kick (27) of moves 1-27 ran it.
 */
void Battle_Effect_Flinch(void) {
    if (!(sBattleTarget->volatileStatusFlags & 0x10)) {
        sBattleTarget->volatileStatusFlags &= 0xFFDF;
        if (sBattleUser->moveCache.effect == 0x1F) {
            if (Battle_Random() >= 0x1A) {
                return;
            }
        } else if (Battle_Random() >= 0x4D) {
            return;
        }
        sBattleTarget->immobilizedReason |= 8;
    }
}

/**
 * Reject a slower OHKO user, otherwise set the damage sentinel and OHKO result.
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Guillotine, Horn Drill, Fissure.
 */
void BattleEffect_OHKO(void) {
    sBattleDamage = 0;
    sBattleCritFlag = 0xFF;
    if (sBattleUser->speed < sBattleTarget->speed) {
        sBattleMoveFailed = 1;
        return;
    }
    sBattleDamage = 0xFFFF;
    sBattleCritFlag = 2;
}

extern s32 D_8218C878;
extern s32 D_8218C87C;
extern s32 D_8218C880;
extern s32 D_8218C884;
extern s32 D_8218C888;
extern s32 D_8218C88C;

/**
 * Move effects 0x27 and 0x2B (Gen 1 ChargeEffect): the first turn of Razor Wind, Solar Beam,
 * Skull Bash, Sky Attack, Fly and Dig. Sets moveEffectKind 0x0C for Fly, 0x0D for Dig and 0x0E
 * otherwise.
 * In the per-move sweep Razor Wind (13) ran it and went on to phase 14.
 */
void Battle_Effect_Charge(void) {
    sBattleScene.scene->moveEffectKind = 0xE;
    sBattleUser->immobilizedReason |= 0x10;

    if ((sBattleUser->moveCache.effect == 0x2B) || (sBattleUser->moveCache.lastMove == DIG)) {
        sBattleUser->immobilizedReason |= 0x40;
        if (sBattleUser->moveCache.lastMove == DIG) {
            sBattleScene.scene->moveEffectKind = 0xD;
        }

        if (sBattleUser->moveCache.effect == 0x2B) {
            sBattleScene.scene->moveEffectKind = 0xC;
        }
    }

    switch (sBattleUser->moveCache.lastMove) {
        case RAZOR_WIND:
            BattleMessage_Format(D_8219A520 + 0xC8, -0x51, D_8218C878, ActivePokemon_GetNickname(sActivePokemon[sBattleScene.scene->actingSide]));
            break;
        case SOLARBEAM:
            BattleMessage_Format(D_8219A520 + 0xC8, -0x50, D_8218C87C, ActivePokemon_GetNickname(sActivePokemon[sBattleScene.scene->actingSide]));
            break;
        case SKULL_BASH:
            BattleMessage_Format(D_8219A520 + 0xC8, -0x4F, D_8218C880, ActivePokemon_GetNickname(sActivePokemon[sBattleScene.scene->actingSide]));
            break;
        case SKY_ATTACK:
            BattleMessage_Format(D_8219A520 + 0xC8, -0x4E, D_8218C884, ActivePokemon_GetNickname(sActivePokemon[sBattleScene.scene->actingSide]));
            break;
        case FLY:
            BattleMessage_Format(D_8219A520 + 0x148, -0x4D, D_8218C888, ActivePokemon_GetNickname(sActivePokemon[sBattleScene.scene->actingSide]));
            break;
        case DIG:
            BattleMessage_Format(D_8219A520 + 0x148, -0x4C, D_8218C88C, ActivePokemon_GetNickname(sActivePokemon[sBattleScene.scene->actingSide]));
            break;
    }
}

extern u8* D_8219A3C0;
extern u8* D_8219A3C4;
u8 Battle_Random(void);
/**
 * Move effect 0x2A (Gen 1 TrappingEffect): Wrap, Bind, Fire Spin and Clamp hold the target for
 * 2-5 turns.
 * In the per-move sweep only Bind (20) of moves 1-27 ran it, and COM's Pinsir then couldn't move
 * (phase 17).
 */
void Battle_Effect_Trapping(void) {
    s32 v;

    if (!(D_8219A3C0[0x4C] & 0x20)) {
        D_8219A3C4[0x4D] &= ~0x20;
        D_8219A3C0[0x4C] |= 0x20;
        v = Battle_Random() & 3;
        if (v >= 2) {
            v = Battle_Random() & 3;
        }
        D_8219A3C0[0x4F] = v + 1;
    }
}

extern s32 D_8218C890;
extern s32 D_8218C894;

// Matches the ROM, but uses rodata data that is not placed in this file yet.
void Battle_Effect_Mist(void) {
    if (sBattleUser->volatileStatusFlags & 2) {
        sBattleScene.scene->moveEffectKind = 7;
        BattleMessage_Format(D_8219A520 + 0x88, -0x4B, D_8218C890);
        return;
    }
    sBattleScene.scene->moveEffectKind = 7;
    sBattleUser->volatileStatusFlags |= 2;
    BattleMessage_Format(D_8219A520 + 0x88, -0x4A, D_8218C894, ActivePokemon_GetNickname(sActivePokemon[sBattleScene.scene->actingSide]));
}

extern s32 D_8218C898;
extern s32 D_8218C89C;

void Battle_Effect_FocusEnergy(void) {
    sBattleScene.scene->moveEffectKind = 7;
    if (sBattleUser->volatileStatusFlags & 4) {
        BattleMessage_Format(D_8219A520 + 0x88, -0x49, D_8218C898);
        return;
    }
    sBattleUser->volatileStatusFlags |= 4;
    BattleMessage_Format(D_8219A520 + 0x88, -0x48, D_8218C89C, ActivePokemon_GetNickname(sActivePokemon[sBattleScene.scene->actingSide]));
}

extern s32 D_8218C8A0;

void Battle_Effect_Recoil(void) {
    s32 var_v1;

    sBattleUser->pendingHp = sBattleUser->hp;

    if (sBattleUser->moveCache.lastMove == STRUGGLE) {
        var_v1 = sBattleDamage >> 1;
    } else {
        var_v1 = sBattleDamage >> 2;
    }

    if (var_v1 == 0) {
        var_v1 += 1;
    }

    if (sBattleUser->pendingHp < var_v1) {
        sBattleUser->pendingHp = 0;
    } else {
        sBattleUser->pendingHp -= var_v1;
    }

    sBattleTarget->pendingHp = sBattleTarget->hp;
    BattleMessage_Format(D_8219A520 + 0x408, -0x47, D_8218C8A0, ActivePokemon_GetNickname(sActivePokemon[sBattleScene.scene->actingSide]));
    sBattleScene.scene->moveEffectKind = 9;
}

extern u8 D_82199FCD;
extern s32 D_8218C8A4;
void Battle_Effect_ConfuseChance(void) {
    if ((Battle_Random() < 0x1A) && !(sBattleTarget->immobilizedReason & 0x80)) {
        sBattleScene.scene->hitReactionKind = 3;
        D_82199FCD = 0;
        sBattleTarget->immobilizedReason |= 0x80;
        sBattleTarget->confusionTurnsLeft = (Battle_Random() & 3) + 2;
        BattleMessage_Format(D_8219A520 + 0x208, -0x46, D_8218C8A4, ActivePokemon_GetNickname(sActivePokemon[!sBattleScene.scene->actingSide]));
    }
}

extern s32 D_8218C8A8;
extern s32 D_8218C8AC;

// Matches the ROM, but uses rodata data that is not placed in this file yet.
extern u8 D_82199F36;

void Battle_Effect_Confuse(void) {
    sBattleScene.scene->moveEffectKind = 0x16;
    sConfused = 0;

    if (!(sBattleTarget->volatileStatusFlags & 0x10)) {
        Battle_MoveHitTest();
        if ((sBattleMoveFailed == 0) && !(sBattleTarget->immobilizedReason & 0x80)) {
            sConfused = 1;
            sBattleTarget->immobilizedReason |= 0x80;
            sBattleTarget->confusionTurnsLeft = (Battle_Random() & 3) + 2;
            BattleMessage_Format(D_8219A520 + 0x88, -0x45, D_8218C8A8, ActivePokemon_GetNickname(sActivePokemon[!sBattleScene.scene->actingSide]));
            return;
        }
    }

    if (D_82199F36 == 0) {
        BattleMessage_Format(D_8219A520 + 0x88, -0x44, D_8218C8AC);
    }
}

extern s32 D_8218C8B0;
extern s32 D_8218C8B4;
extern s32 D_8218C8B8;

// Matches the ROM, but uses rodata data that is not placed in this file yet.
void Battle_Effect_Paralyze(void) {
    sBattleScene.scene->moveEffectKind = 0x16;
    if (sBattleTarget->pendingStatusCondition == 0) {
        if ((sBattleUser->moveCache.type != 0x17) || ((sBattleTarget->roster[6] != 4) && (sBattleTarget->roster[7] != 4))) {
            Battle_MoveHitTest();
            if (sBattleMoveFailed == 0) {
                sBattleTarget->pendingStatusCondition |= 0x40;
                ApplyParalysisSpeedCut(sActivePokemon[!sBattleScene.scene->actingSide]);
                BattleMessage_Format(D_8219A520 + 0x88, -0x43, D_8218C8B0, ActivePokemon_GetNickname(sActivePokemon[!sBattleScene.scene->actingSide]));
                return;
            }
        } else {
            sConfused = 0;
            BattleMessage_Format(D_8219A520 + 0x88, -0x42, D_8218C8B4);
            return;
        }
    }

    sConfused = 0;
    BattleMessage_Format(D_8219A520 + 0x88, -0x41, D_8218C8B8, ActivePokemon_GetNickname(sActivePokemon[!sBattleScene.scene->actingSide]));
}

extern s32 D_8218C910;
extern s32 D_8218C914;
extern s32 D_8218C918;
void ActivePokemon_SetStateFlags(ActivePokemon*, s32);

void Battle_Effect_Substitute(void) {
    s32 temp_v1;

    sBattleScene.scene->moveEffectKind = 0x19;
    if (sBattleUser->volatileStatusFlags & 0x10) {
        BattleMessage_Format(D_8219A520 + 0x88, -0x2B, D_8218C910, ActivePokemon_GetNickname(sActivePokemon[sBattleScene.scene->actingSide]));
        return;
    }

    temp_v1 = sBattleUser->maxHp >> 2;
    if (sBattleUser->hp < temp_v1) {
        BattleMessage_Format(D_8219A520 + 0x88, -0x2A, D_8218C914);
        return;
    }

    ActivePokemon_SetStateFlags(sActivePokemon[sBattleScene.scene->actingSide], 0x2800);
    sBattleUser->substituteHp = temp_v1;
    sBattleUser->hp -= temp_v1;
    sBattleUser->volatileStatusFlags |= 0x10;
    BattleMessage_Format(D_8219A520 + 0x88, -0x29, D_8218C918, ActivePokemon_GetNickname(sActivePokemon[sBattleScene.scene->actingSide]));
}

/**
 * Mark the user as needing a recharge turn; Battle_CheckMonCanAct consumes the flag.
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Hyper Beam.
 */
void BattleEffect_Recharge(void) {
    sBattleUser->volatileStatusFlags |= 0x20;
}

/**
 * Enable Rage's move lock and subsequent Attack boosts.
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Rage.
 */
void BattleEffect_Rage(void) {
    sBattleUser->volatileStatusFlags |= 0x40;
}

typedef struct {
    /* 0x0 */ s32 unk_00;
    /* 0x4 */ s32 unk_04;
    /* 0x8 */ s32 unk_08;
} unk_D_8006A9CC; // size = 0xC
extern unk_D_8006A9CC D_8006A9CC[];
extern u8 D_82199F37;
extern s32 D_8218C8BC;
extern s32 D_8218C8C0;

/**
 * Replace the selected move slot with a randomly chosen nonempty target move.
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Mimic.
 */
void BattleEffect_Mimic(void) {
    ActivePokemonState* sp34 = &sActivePokemon[sBattleScene.scene->actingSide]->state;
    UNUSED s32 pad; // FAKE: stack padding
    s32 var_t0;
    u8 temp_v0;

    sBattleScene.scene->moveEffectKind = 7;
    Battle_MoveHitTest();

    if ((sBattleMoveFailed == 0) && !(sBattleTarget->immobilizedReason & 0x40)) {
        D_82199F37 = 1;
        do {
            var_t0 = BattleAnim_RandomRange(4);
            if (var_t0 >= 4) {
                var_t0 = 3;
            }
            temp_v0 = sBattleTarget->moves[var_t0];
        } while (temp_v0 == 0);

        sBattleUser->moves[sp34->selectedMoveIndex] = temp_v0;
        BattleMessage_Format(D_8219A520 + 0x88, -0x40, D_8218C8BC, ActivePokemon_GetNickname(sActivePokemon[sBattleScene.scene->actingSide]), D_8006A9CC[sBattleTarget->moves[var_t0]].unk_00);
        return;
    }

    BattleMessage_Format(D_8219A520 + 0x88, -0x3F, D_8218C8C0);
}

extern s32 D_8218C8C4;
extern s32 D_8218C8C8;

// Matches the ROM, but uses rodata data that is not placed in this file yet.
void Battle_Effect_LeechSeed(void) {
    Battle_MoveHitTest();

    if ((sBattleMoveFailed == 0) && (sBattleTarget->roster[6] != 0x16) && (sBattleTarget->roster[7] != 0x16)) {
        if (!(sBattleTarget->volatileStatusFlags & 0x80)) {
            sBattleTarget->volatileStatusFlags |= 0x80;
            BattleMessage_Format(D_8219A520 + 0x88, -0x3E, D_8218C8C4, ActivePokemon_GetNickname(sActivePokemon[!sBattleScene.scene->actingSide]));
            return;
        }
    }

    sBattleScene.scene->moveEffectKind = 8;
    BattleMessage_Format(D_8219A520 + 0x88, -0x3D, D_8218C8C8, ActivePokemon_GetNickname(sActivePokemon[!sBattleScene.scene->actingSide]));
}

s32 BattleMessage_Format(s32, s32, s32, ...);
extern s32 D_8218C8CC;
extern s32 D_8219A520;
extern s8 *D_8219A5A0;

/**
 * Move effect 0x55 (Gen 1 SplashEffect).
 * In the per-move sweep only Splash ran it.
 */
void Battle_Effect_Splash(void) {
    M2C_FIELD(D_8219A5A0, s32 *, 0x48) = 7;
    BattleMessage_Format(D_8219A520 + 0x88, -0x3C, D_8218C8CC);
}

extern s32 D_8218C8D0;
extern s32 D_8218C8D4;
/**
 * Move effect 0x56 (Gen 1 DisableEffect): disables a random move of the target for 1-8 turns.
 * Sets moveEffectKind 0x20, or 8 when it fails.
 * In the per-move sweep only Disable ran it.
 */
void Battle_Effect_Disable(void) {
    s32 slot;
    s32 turns;
    s32 name;

    Battle_MoveHitTest();
    if (sBattleMoveFailed == 0) {
        sBattleScene.scene->moveEffectKind = 0x20;
        if (sBattleTarget->disabledMoveState == 0) {
            do {
                slot = Battle_Random() & 3;
            } while (sBattleTarget->moves[slot] == 0);
            turns = Battle_Random() & 7;
            sBattleTarget->disabledMoveState = (slot << 4) + turns + 1;
            sBattleTarget->disabledMove = sBattleTarget->moves[slot];
            name = D_8006A9CC[sBattleTarget->disabledMove].unk_00;
            BattleMessage_Format(D_8219A520 + 0x88, -0x3B, D_8218C8D0, ActivePokemon_GetNickname(sActivePokemon[!sBattleScene.scene->actingSide]), name);
            return;
        }
    }

    sBattleScene.scene->moveEffectKind = 8;
    BattleMessage_Format(D_8219A520 + 0x88, -0x3A, D_8218C8D4);
}

s32 BattleMessage_Format(s32, s32, s32, ...);
extern s32 D_8218C8D8;
extern s32 D_8219A520;

/**
 * Move effect 0x10 (Gen 1 PayDayEffect).
 * In the per-move sweep only Pay Day (6) ran it.
 */
void Battle_Effect_PayDay(void) {
    BattleMessage_Format(D_8219A520 + 0x88, -0x39, D_8218C8D8);
}

extern s32 D_8218C8DC;
extern s32 D_8218C8E0;

// Matches the ROM, but uses rodata data that is not placed in this file yet.
void Battle_Effect_Conversion(void) {
    sBattleScene.scene->moveEffectKind = 7;
    if (!(sBattleTarget->immobilizedReason & 0x40)) {
        sBattleUser->roster[6] = sBattleTarget->roster[6];
        sBattleUser->roster[7] = sBattleTarget->roster[7];
        BattleMessage_Format(D_8219A520 + 0x88, -0x38, D_8218C8DC, ActivePokemon_GetNickname(sActivePokemon[!sBattleScene.scene->actingSide]));
    } else {
        BattleMessage_Format(D_8219A520 + 0x88, -0x37, D_8218C8E0);
    }
}

extern s32 D_8218C8E4;

void Battle_Effect_Haze(void) {
    s32 i;
    BattleMonRuntime* temp_t0 = &sActivePokemon[0]->state.runtime;
    BattleMonRuntime* temp_a3 = &sActivePokemon[1]->state.runtime;

    sBattleScene.scene->moveEffectKind = 0x1D;

    for (i = 0; i < 8; i++) {
        temp_t0->unk_5C[i] = 7;
        temp_a3->unk_5C[i] = 7;
    }

    temp_t0->modifiedAttack = temp_t0->unmodifiedAttack;
    temp_t0->modifiedDefense = temp_t0->unmodifiedDefense;
    temp_t0->speed = temp_t0->unmodifiedSpeed;
    temp_t0->modifiedSpecial = temp_t0->unmodifiedSpecial;
    temp_a3->modifiedAttack = temp_a3->unmodifiedAttack;
    temp_a3->modifiedDefense = temp_a3->unmodifiedDefense;
    temp_a3->speed = temp_a3->unmodifiedSpeed;
    temp_a3->modifiedSpecial = temp_a3->unmodifiedSpecial;

    if (sBattleTarget->pendingStatusCondition & 0x27) {
        sBattleTarget->usedMove = 0xFF;
    }

    sBattleTarget->pendingStatusCondition = 0;

    temp_t0->disabledMoveState = temp_a3->disabledMoveState = 0;
    temp_t0->disabledMove = temp_a3->disabledMove = 0;
    temp_t0->immobilizedReason &= ~0x80;
    temp_t0->volatileStatusFlags &= 0x78;
    temp_t0->uniqueStatusFlags &= 8;
    temp_a3->immobilizedReason &= ~0x80;
    temp_a3->volatileStatusFlags &= 0x78;
    temp_a3->uniqueStatusFlags &= 8;
    sBattleUser->scaleResize = 0;
    sBattleTarget->scaleResize = 0;

    BattleMessage_Format(D_8219A520 + 0x88, -0x36, D_8218C8E4);
}

extern s32 D_8218C8E8;
extern s32 D_8218C8EC;
extern s32 D_8218C8F0;
extern s32 D_8218C8F4;

/**
 * Move effect 0x38 (Gen 1 HealEffect): Recover and Soft-Boiled restore half the max HP, Rest
 * restores it all and puts the user to sleep. Fails at full HP (moveEffectKind 0x1C), otherwise
 * sets moveEffectKind 0x15.
 * In the per-move sweep exactly Recover, Soft-Boiled and Rest ran it (at full HP, so all three
 * took the failed path to phase 28).
 */
void Battle_Effect_Heal(void) {
    u8 temp_v0;
    ActivePokemonState* temp_a1;
    BattleMonRuntime* temp_a2;

    temp_a1 = &sActivePokemon[sBattleScene.scene->actingSide]->state;
    temp_a2 = &sActivePokemon[sBattleScene.scene->actingSide]->state.runtime;

    sBattleScene.scene->moveEffectKind = 0x15;
    if (sBattleUser->hp != sBattleUser->maxHp) {
        if (sBattleUser->moveCache.lastMove == REST) {
            temp_v0 = sBattleUser->pendingStatusCondition;

            sBattleUser->pendingStatusCondition = 2;
            temp_a2->roster[temp_a1->rosterIndex + temp_a1->teamMemberIndex * 3] = 2;

            if (temp_v0 != 0) {
                BattleMessage_Format(D_8219A520 + 0x88, -0x35, D_8218C8E8, ActivePokemon_GetNickname(sActivePokemon[sBattleScene.scene->actingSide]));
            } else {
                BattleMessage_Format(D_8219A520 + 0x88, -0x34, D_8218C8EC, ActivePokemon_GetNickname(sActivePokemon[sBattleScene.scene->actingSide]));
            }
            sBattleUser->hp += sBattleUser->maxHp;
        } else {
            sBattleUser->hp += sBattleUser->maxHp / 2;
        }

        if (sBattleUser->maxHp < sBattleUser->hp) {
            sBattleUser->hp = sBattleUser->maxHp;
        }

        BattleMessage_Format(D_8219A520 + 0x148, -0x33, D_8218C8F0, ActivePokemon_GetNickname(sActivePokemon[sBattleScene.scene->actingSide]));
        return;
    }

    sBattleScene.scene->moveEffectKind = 0x1C;
    sBattleMoveFailed = 1;
    BattleMessage_Format(D_8219A520 + 0x88, -0x32, D_8218C8F4);
}

extern s32 D_8218C8F8;
extern s32 D_8218C8FC;
/* Transform: the user copies the target's species, moves, stats and stat stages. */
/**
 * Move effect 0x39 (Gen 1 TransformEffect): copies the target's species, types, moves (5 PP
 * each), stats and stat stages. Sets moveEffectKind 0x0F.
 * In the per-move sweep only Transform ran it.
 */
void Battle_Effect_Transform(void) {
    s32 i;
    ActivePokemonState* user;
    ActivePokemonState* target;

    user = &sActivePokemon[sBattleScene.scene->actingSide]->state;
    target = &sActivePokemon[!sBattleScene.scene->actingSide]->state;

    if (!(sBattleUser->immobilizedReason & 0x40)) {
        if (sBattleUser && sBattleUser) {} // FAKE
        sBattleScene.scene->moveEffectKind = 0xF;
        BattleMessage_Format(D_8219A520 + 0x148, -0x31, D_8218C8F8, ActivePokemon_GetNickname(sActivePokemon[sBattleScene.scene->actingSide]), ActivePokemon_GetNickname(sActivePokemon[!sBattleScene.scene->actingSide]));
        sBattleUser->uniqueStatusFlags |= 8;

        if (sBattleTarget->uniqueStatusFlags & 8) {
            user->unk_BE = target->unk_BE;
        } else {
            user->unk_BE = sBattleTarget->id;
        }

        sBattleUser->roster[6] = sBattleTarget->roster[6];
        sBattleUser->roster[7] = sBattleTarget->roster[7];
        sBattleUser->moves[0] = sBattleTarget->moves[0];
        sBattleUser->moves[1] = sBattleTarget->moves[1];
        sBattleUser->moves[2] = sBattleTarget->moves[2];
        sBattleUser->moves[3] = sBattleTarget->moves[3];
        sBattleUser->unk_24 = sBattleTarget->unk_24;
        sBattleUser->modifiedAttack = sBattleTarget->modifiedAttack;
        sBattleUser->modifiedDefense = sBattleTarget->modifiedDefense;
        sBattleUser->speed = sBattleTarget->speed;
        sBattleUser->modifiedSpecial = sBattleTarget->modifiedSpecial;

        for (i = 0; i < 4; i++) {
            if (sBattleTarget->moves[i] == 0) {
                break;
            }
            sBattleUser->pp[i] = 5;
        }

        sBattleUser->unmodifiedAttack = sBattleTarget->unmodifiedAttack;
        sBattleUser->unmodifiedDefense = sBattleTarget->unmodifiedDefense;
        sBattleUser->unmodifiedSpeed = sBattleTarget->unmodifiedSpeed;
        sBattleUser->unmodifiedSpecial = sBattleTarget->unmodifiedSpecial;

        for (i = 0; i < 8; i++) {
            sBattleUser->unk_5C[i] = sBattleTarget->unk_5C[i];
        }
    } else {
        BattleMessage_Format(D_8219A520 + 0x88, -0x30, D_8218C8FC);
    }
}

extern s32 D_8218C900;
extern s32 D_8218C904;
extern s32 D_8218C908;
extern s32 D_8218C90C;

// Matches the ROM, but uses rodata data that is not placed in this file yet.
void Battle_Effect_ReflectLightScreen(void) {
    sBattleScene.scene->moveEffectKind = 7;
    if (sBattleUser->moveCache.effect == 0x40) {
        if (!(sBattleUser->uniqueStatusFlags & 2)) {
            sBattleUser->uniqueStatusFlags |= 2;
            BattleMessage_Format(D_8219A520 + 0x88, -0x2F, D_8218C900, ActivePokemon_GetNickname(sActivePokemon[sBattleScene.scene->actingSide]));
        } else {
            BattleMessage_Format(D_8219A520 + 0x88, -0x2E, D_8218C904);
        }
    } else if (!(sBattleUser->uniqueStatusFlags & 4)) {
        sBattleUser->uniqueStatusFlags |= 4;
        BattleMessage_Format(D_8219A520 + 0x88, -0x2D, D_8218C908, ActivePokemon_GetNickname(sActivePokemon[sBattleScene.scene->actingSide]));
    } else {
        BattleMessage_Format(D_8219A520 + 0x88, -0x2C, D_8218C90C);
    }
}

/**
 * Dispatch the cached effect through its 1-based handler slot; NULL slots do nothing.
 * Seen in play (2026-11-12): in a turn where 1P's Poison Sting went first, it ran with effect 2,
 * the effect byte of Poison Sting's move cache.
 */
void BattleEffect_RunMoveEffect(void) {
    BattleMonRuntime* ptr = &sActivePokemon[sBattleScene.scene->actingSide]->state.runtime;
    s32 idx = ptr->moveCache.effect;

    if (sMoveEffectHandlers[idx - 1] != NULL) {
        sMoveEffectHandlers[idx - 1]();
    }
}

/**
 * Entry point used by the turn engine to invoke the cached move-effect handler.
 * Seen in play (2026-11-12): in a turn where 1P's Poison Sting went first, it ran at commit with
 * effect 2, the effect byte of Poison Sting's move cache, and called BattleEffect_RunMoveEffect.
 */
void BattleEffect_ExecuteMoveEffect(void) {
    BattleEffect_RunMoveEffect();
}
