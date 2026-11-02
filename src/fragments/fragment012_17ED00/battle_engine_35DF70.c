/* Stadium Zero fragment012_17ED00. */
/* C ported from the Stadium 1 decomp: src/fragments/battle_engine/battle_engine_35DF70.c. */

#include "fragments/battle_engine/battle_engine.h"
#include "moves.h"
#include "text_system.h"
typedef void (*func_D_8438AE50)(void);
extern func_D_8438AE50 sMoveEffectHandlers[];

#include "m2c_macros.h"

s32 func_8211EF74(s32, s32, s32, ...);
extern s32 D_8219A520;
s32 func_82107F88(ActivePokemon*);

void Battle_Effect_Bide(void);
void Battle_Effect_Thrash(void);
void Battle_Effect_MultiHit(void);
void Battle_Effect_Recharge(void);
void Battle_Effect_Rage(void);
void Battle_ExecuteMoveEffect(void);

void Battle_RunMoveEffect(void);

void Battle_Effect_Bide(void) {
    sBattleScene.scene->unk_48 = 0x1B;
    sBattleUser->moveCache.unk_01 = 0;
    sBattleUser->unk_4C |= 1;
    sBattleUser->unk_54 = 0;
    sBattleUser->unk_4F = (Battle_Random() & 1) + 2;
}

void Battle_Effect_Thrash(void) {
    sBattleUser->moveCache.unk_01 = 0;
    sBattleUser->unk_4C |= 2;
    sBattleUser->unk_4F = (Battle_Random() & 1) + 2;
}

extern s32 D_8218C870;
extern s32 D_8218C874;

void Battle_Effect_ForceSwitchOrFlee(void) {
    if (sBattleUser->moveCache.lastMove == TELEPORT) {
        sBattleScene.scene->unk_48 = 8;
        func_8211EF74(D_8219A520 + 0x88, -0x53, D_8218C870);
        return;
    }
    sBattleScene.scene->unk_48 = 8;
    func_8211EF74(D_8219A520 + 0x88, -0x52, D_8218C874, func_82107F88(sActivePokemon[!sBattleScene.scene->unk_2C]));
}

void Battle_Effect_MultiHit(void) {
    s32 var_v1;

    if (!(sBattleUser->unk_4C & 4)) {
        sBattleUser->unk_4C |= 4;

        switch (sBattleUser->moveCache.unk_01) {
            case 0x4D:
                sBattleUser->moveCache.unk_01 = 2;

            case 0x2C:
                sBattleUser->unk_54 = 2;
                sBattleUser->unk_4F = sBattleUser->unk_54;
                break;

            default:
                var_v1 = Battle_Random() & 3;
                if (var_v1 >= 2) {
                    var_v1 = Battle_Random() & 3;
                }
                sBattleUser->unk_4F = sBattleUser->unk_54 = var_v1 + 2;
                break;
        }

        sMultihitCount = sBattleUser->unk_54 - 1;
        sBattleScene.scene->unk_48 = 0x18;
    }
}

s32 func_8210F3F0(void);

/*
 * func_82114C20
 *
 * Does nothing if bit 0x10 of sBattleTarget->unk_4D is set. Otherwise it clears
 * bit 0x20 of sBattleTarget->unk_4D, calls func_8210F3F0(), and sets bit 0x08
 * of sBattleTarget->unk_4C when the result is below a limit: 0x1A when
 * sBattleUser->moveCache.unk_01 is 0x1F, otherwise 0x4D. (func_8210F3F0 is
 * called exactly once on each path.) What the flag bits and the limits mean
 * is not established from this function.
 *
 * The return type is void: the early `return`s compile to a jump to the
 * epilogue with no value in v0, as in the retail code.
 */
void func_82114C20(void) {
    if (!(sBattleTarget->unk_4D & 0x10)) {
        sBattleTarget->unk_4D &= 0xFFDF;
        if (sBattleUser->moveCache.unk_01 == 0x1F) {
            if (func_8210F3F0() >= 0x1A) {
                return;
            }
        } else if (func_8210F3F0() >= 0x4D) {
            return;
        }
        sBattleTarget->unk_4C |= 8;
    }
}

void Battle_Effect_OHKO(void) {
    sBattleDamage = 0;
    sBattleCritFlag = 0xFF;
    if (sBattleUser->speed < sBattleTarget->speed) {
        sBattleMoveFailed = 1;
        return;
    }
    sBattleDamage = 0xFFFF;
    sBattleCritFlag = 2;
}

#ifdef NON_MATCHING
/* TODO: decompile func_82114D10; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_82114D10.s")
#endif

extern u8* D_8219A3C0;
extern u8* D_8219A3C4;
s32 func_8210F3F0(void);
void func_82114F9C(void) {
    s32 v;

    if (!(D_8219A3C0[0x4C] & 0x20)) {
        D_8219A3C4[0x4D] &= ~0x20;
        D_8219A3C0[0x4C] |= 0x20;
        v = func_8210F3F0() & 3;
        if (v >= 2) {
            v = func_8210F3F0() & 3;
        }
        D_8219A3C0[0x4F] = v + 1;
    }
}

extern s32 D_8218C890;
extern s32 D_8218C894;

// Matches the ROM, but uses rodata data that is not placed in this file yet.
void Battle_Effect_Mist(void) {
    if (sBattleUser->unk_4D & 2) {
        sBattleScene.scene->unk_48 = 7;
        func_8211EF74(D_8219A520 + 0x88, -0x4B, D_8218C890);
        return;
    }
    sBattleScene.scene->unk_48 = 7;
    sBattleUser->unk_4D |= 2;
    func_8211EF74(D_8219A520 + 0x88, -0x4A, D_8218C894, func_82107F88(sActivePokemon[sBattleScene.scene->unk_2C]));
}

extern s32 D_8218C898;
extern s32 D_8218C89C;

void Battle_Effect_FocusEnergy(void) {
    sBattleScene.scene->unk_48 = 7;
    if (sBattleUser->unk_4D & 4) {
        func_8211EF74(D_8219A520 + 0x88, -0x49, D_8218C898);
        return;
    }
    sBattleUser->unk_4D |= 4;
    func_8211EF74(D_8219A520 + 0x88, -0x48, D_8218C89C, func_82107F88(sActivePokemon[sBattleScene.scene->unk_2C]));
}

extern s32 D_8218C8A0;

void Battle_Effect_Recoil(void) {
    s32 var_v1;

    sBattleUser->unk_12 = sBattleUser->unk_0C;

    if (sBattleUser->moveCache.lastMove == STRUGGLE) {
        var_v1 = sBattleDamage >> 1;
    } else {
        var_v1 = sBattleDamage >> 2;
    }

    if (var_v1 == 0) {
        var_v1 += 1;
    }

    if (sBattleUser->unk_12 < var_v1) {
        sBattleUser->unk_12 = 0;
    } else {
        sBattleUser->unk_12 -= var_v1;
    }

    sBattleTarget->unk_12 = sBattleTarget->unk_0C;
    func_8211EF74(D_8219A520 + 0x408, -0x47, D_8218C8A0, func_82107F88(sActivePokemon[sBattleScene.scene->unk_2C]));
    sBattleScene.scene->unk_48 = 9;
}

extern u8 D_82199FCD;
extern s32 D_8218C8A4;
void Battle_Effect_ConfuseChance(void) {
    if ((Battle_Random() < 0x1A) && !(sBattleTarget->unk_4C & 0x80)) {
        sBattleScene.scene->unk_1A = 3;
        D_82199FCD = 0;
        sBattleTarget->unk_4C |= 0x80;
        sBattleTarget->unk_50 = (Battle_Random() & 3) + 2;
        func_8211EF74(D_8219A520 + 0x208, -0x46, D_8218C8A4, func_82107F88(sActivePokemon[!sBattleScene.scene->unk_2C]));
    }
}

extern s32 D_8218C8A8;
extern s32 D_8218C8AC;

// Matches the ROM, but uses rodata data that is not placed in this file yet.
extern u8 D_82199F36;

void Battle_Effect_Confuse(void) {
    sBattleScene.scene->unk_48 = 0x16;
    sConfused = 0;

    if (!(sBattleTarget->unk_4D & 0x10)) {
        HandleMoveEffectFlags();
        if ((sBattleMoveFailed == 0) && !(sBattleTarget->unk_4C & 0x80)) {
            sConfused = 1;
            sBattleTarget->unk_4C |= 0x80;
            sBattleTarget->unk_50 = (Battle_Random() & 3) + 2;
            func_8211EF74(D_8219A520 + 0x88, -0x45, D_8218C8A8, func_82107F88(sActivePokemon[!sBattleScene.scene->unk_2C]));
            return;
        }
    }

    if (D_82199F36 == 0) {
        func_8211EF74(D_8219A520 + 0x88, -0x44, D_8218C8AC);
    }
}

extern s32 D_8218C8B0;
extern s32 D_8218C8B4;
extern s32 D_8218C8B8;

// Matches the ROM, but uses rodata data that is not placed in this file yet.
void Battle_Effect_Paralyze(void) {
    sBattleScene.scene->unk_48 = 0x16;
    if (sBattleTarget->unk_15 == 0) {
        if ((sBattleUser->moveCache.unk_03 != 0x17) || ((sBattleTarget->roster[6] != 4) && (sBattleTarget->roster[7] != 4))) {
            HandleMoveEffectFlags();
            if (sBattleMoveFailed == 0) {
                sBattleTarget->unk_15 |= 0x40;
                ApplyParalysisSpeedCut(sActivePokemon[!sBattleScene.scene->unk_2C]);
                func_8211EF74(D_8219A520 + 0x88, -0x43, D_8218C8B0, func_82107F88(sActivePokemon[!sBattleScene.scene->unk_2C]));
                return;
            }
        } else {
            sConfused = 0;
            func_8211EF74(D_8219A520 + 0x88, -0x42, D_8218C8B4);
            return;
        }
    }

    sConfused = 0;
    func_8211EF74(D_8219A520 + 0x88, -0x41, D_8218C8B8, func_82107F88(sActivePokemon[!sBattleScene.scene->unk_2C]));
}

extern s32 D_8218C910;
extern s32 D_8218C914;
extern s32 D_8218C918;
void func_82105E38(ActivePokemon*, s32);

void Battle_Effect_Substitute(void) {
    s32 temp_v1;

    sBattleScene.scene->unk_48 = 0x19;
    if (sBattleUser->unk_4D & 0x10) {
        func_8211EF74(D_8219A520 + 0x88, -0x2B, D_8218C910, func_82107F88(sActivePokemon[sBattleScene.scene->unk_2C]));
        return;
    }

    temp_v1 = sBattleUser->unk_28 >> 2;
    if (sBattleUser->unk_0C < temp_v1) {
        func_8211EF74(D_8219A520 + 0x88, -0x2A, D_8218C914);
        return;
    }

    func_82105E38(sActivePokemon[sBattleScene.scene->unk_2C], 0x2800);
    sBattleUser->unk_59 = temp_v1;
    sBattleUser->unk_0C -= temp_v1;
    sBattleUser->unk_4D |= 0x10;
    func_8211EF74(D_8219A520 + 0x88, -0x29, D_8218C918, func_82107F88(sActivePokemon[sBattleScene.scene->unk_2C]));
}

void Battle_Effect_Recharge(void) {
    sBattleUser->unk_4D |= 0x20;
}

void Battle_Effect_Rage(void) {
    sBattleUser->unk_4D |= 0x40;
}

#ifdef NON_MATCHING
/* TODO: decompile func_8211576C; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_8211576C.s")
#endif

extern s32 D_8218C8C4;
extern s32 D_8218C8C8;

// Matches the ROM, but uses rodata data that is not placed in this file yet.
void Battle_Effect_LeechSeed(void) {
    HandleMoveEffectFlags();

    if ((sBattleMoveFailed == 0) && (sBattleTarget->roster[6] != 0x16) && (sBattleTarget->roster[7] != 0x16)) {
        if (!(sBattleTarget->unk_4D & 0x80)) {
            sBattleTarget->unk_4D |= 0x80;
            func_8211EF74(D_8219A520 + 0x88, -0x3E, D_8218C8C4, func_82107F88(sActivePokemon[!sBattleScene.scene->unk_2C]));
            return;
        }
    }

    sBattleScene.scene->unk_48 = 8;
    func_8211EF74(D_8219A520 + 0x88, -0x3D, D_8218C8C8, func_82107F88(sActivePokemon[!sBattleScene.scene->unk_2C]));
}

s32 func_8211EF74(s32, s32, s32, ...);
extern s32 D_8218C8CC;
extern s32 D_8219A520;
extern s8 *D_8219A5A0;

void func_821159D0(void) {
    M2C_FIELD(D_8219A5A0, s32 *, 0x48) = 7;
    func_8211EF74(D_8219A520 + 0x88, -0x3C, D_8218C8CC);
}

typedef struct {
    /* 0x0 */ s32 unk_00;
    /* 0x4 */ s32 unk_04;
    /* 0x8 */ s32 unk_08;
} unk_D_8006A9CC; // size = 0xC
extern unk_D_8006A9CC D_8006A9CC[];
extern s32 D_8218C8D0;
extern s32 D_8218C8D4;
void func_82115A14(void) {
    s32 slot;
    s32 turns;
    s32 name;

    HandleMoveEffectFlags();
    if (sBattleMoveFailed == 0) {
        sBattleScene.scene->unk_48 = 0x20;
        if (sBattleTarget->unk_52 == 0) {
            do {
                slot = Battle_Random() & 3;
            } while (sBattleTarget->moves[slot] == 0);
            turns = Battle_Random() & 7;
            sBattleTarget->unk_52 = (slot << 4) + turns + 1;
            sBattleTarget->unk_57 = sBattleTarget->moves[slot];
            name = D_8006A9CC[sBattleTarget->unk_57].unk_00;
            func_8211EF74(D_8219A520 + 0x88, -0x3B, D_8218C8D0, func_82107F88(sActivePokemon[!sBattleScene.scene->unk_2C]), name);
            return;
        }
    }

    sBattleScene.scene->unk_48 = 8;
    func_8211EF74(D_8219A520 + 0x88, -0x3A, D_8218C8D4);
}

s32 func_8211EF74(s32, s32, s32, ...);
extern s32 D_8218C8D8;
extern s32 D_8219A520;

void func_82115B64(void) {
    func_8211EF74(D_8219A520 + 0x88, -0x39, D_8218C8D8);
}

extern s32 D_8218C8DC;
extern s32 D_8218C8E0;

// Matches the ROM, but uses rodata data that is not placed in this file yet.
void Battle_Effect_Conversion(void) {
    sBattleScene.scene->unk_48 = 7;
    if (!(sBattleTarget->unk_4C & 0x40)) {
        sBattleUser->roster[6] = sBattleTarget->roster[6];
        sBattleUser->roster[7] = sBattleTarget->roster[7];
        func_8211EF74(D_8219A520 + 0x88, -0x38, D_8218C8DC, func_82107F88(sActivePokemon[!sBattleScene.scene->unk_2C]));
    } else {
        func_8211EF74(D_8219A520 + 0x88, -0x37, D_8218C8E0);
    }
}

extern s32 D_8218C8E4;

void Battle_Effect_Haze(void) {
    s32 i;
    BattleMonRuntime* temp_t0 = &sActivePokemon[0]->state.runtime;
    BattleMonRuntime* temp_a3 = &sActivePokemon[1]->state.runtime;

    sBattleScene.scene->unk_48 = 0x1D;

    for (i = 0; i < 8; i++) {
        temp_t0->unk_5C[i] = 7;
        temp_a3->unk_5C[i] = 7;
    }

    temp_t0->unk_2A = temp_t0->unk_38;
    temp_t0->unk_2C = temp_t0->unk_3A;
    temp_t0->speed = temp_t0->unk_3C;
    temp_t0->unk_30 = temp_t0->unk_3E;
    temp_a3->unk_2A = temp_a3->unk_38;
    temp_a3->unk_2C = temp_a3->unk_3A;
    temp_a3->speed = temp_a3->unk_3C;
    temp_a3->unk_30 = temp_a3->unk_3E;

    if (sBattleTarget->unk_15 & 0x27) {
        sBattleTarget->usedMove = 0xFF;
    }

    sBattleTarget->unk_15 = 0;

    temp_t0->unk_52 = temp_a3->unk_52 = 0;
    temp_t0->unk_57 = temp_a3->unk_57 = 0;
    temp_t0->unk_4C &= ~0x80;
    temp_t0->unk_4D &= 0x78;
    temp_t0->unk_4E &= 8;
    temp_a3->unk_4C &= ~0x80;
    temp_a3->unk_4D &= 0x78;
    temp_a3->unk_4E &= 8;
    sBattleUser->scaleResize = 0;
    sBattleTarget->scaleResize = 0;

    func_8211EF74(D_8219A520 + 0x88, -0x36, D_8218C8E4);
}

extern s32 D_8218C8E8;
extern s32 D_8218C8EC;
extern s32 D_8218C8F0;
extern s32 D_8218C8F4;

void func_82115DE0(void) {
    u8 temp_v0;
    ActivePokemonState* temp_a1;
    BattleMonRuntime* temp_a2;

    temp_a1 = &sActivePokemon[sBattleScene.scene->unk_2C]->state;
    temp_a2 = &sActivePokemon[sBattleScene.scene->unk_2C]->state.runtime;

    sBattleScene.scene->unk_48 = 0x15;
    if (sBattleUser->unk_0C != sBattleUser->unk_28) {
        if (sBattleUser->moveCache.lastMove == REST) {
            temp_v0 = sBattleUser->unk_15;

            sBattleUser->unk_15 = 2;
            temp_a2->roster[temp_a1->rosterIndex + temp_a1->teamMemberIndex * 3] = 2;

            if (temp_v0 != 0) {
                func_8211EF74(D_8219A520 + 0x88, -0x35, D_8218C8E8, func_82107F88(sActivePokemon[sBattleScene.scene->unk_2C]));
            } else {
                func_8211EF74(D_8219A520 + 0x88, -0x34, D_8218C8EC, func_82107F88(sActivePokemon[sBattleScene.scene->unk_2C]));
            }
            sBattleUser->unk_0C += sBattleUser->unk_28;
        } else {
            sBattleUser->unk_0C += sBattleUser->unk_28 / 2;
        }

        if (sBattleUser->unk_28 < sBattleUser->unk_0C) {
            sBattleUser->unk_0C = sBattleUser->unk_28;
        }

        func_8211EF74(D_8219A520 + 0x148, -0x33, D_8218C8F0, func_82107F88(sActivePokemon[sBattleScene.scene->unk_2C]));
        return;
    }

    sBattleScene.scene->unk_48 = 0x1C;
    sBattleMoveFailed = 1;
    func_8211EF74(D_8219A520 + 0x88, -0x32, D_8218C8F4);
}

#ifdef NON_MATCHING
/* TODO: decompile func_82115FCC; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_82115FCC.s")
#endif

extern s32 D_8218C900;
extern s32 D_8218C904;
extern s32 D_8218C908;
extern s32 D_8218C90C;

// Matches the ROM, but uses rodata data that is not placed in this file yet.
void Battle_Effect_ReflectLightScreen(void) {
    sBattleScene.scene->unk_48 = 7;
    if (sBattleUser->moveCache.unk_01 == 0x40) {
        if (!(sBattleUser->unk_4E & 2)) {
            sBattleUser->unk_4E |= 2;
            func_8211EF74(D_8219A520 + 0x88, -0x2F, D_8218C900, func_82107F88(sActivePokemon[sBattleScene.scene->unk_2C]));
        } else {
            func_8211EF74(D_8219A520 + 0x88, -0x2E, D_8218C904);
        }
    } else if (!(sBattleUser->unk_4E & 4)) {
        sBattleUser->unk_4E |= 4;
        func_8211EF74(D_8219A520 + 0x88, -0x2D, D_8218C908, func_82107F88(sActivePokemon[sBattleScene.scene->unk_2C]));
    } else {
        func_8211EF74(D_8219A520 + 0x88, -0x2C, D_8218C90C);
    }
}

void Battle_RunMoveEffect(void) {
    BattleMonRuntime* ptr = &sActivePokemon[sBattleScene.scene->unk_2C]->state.runtime;
    s32 idx = ptr->moveCache.unk_01;

    if (sMoveEffectHandlers[idx - 1] != NULL) {
        sMoveEffectHandlers[idx - 1]();
    }
}

void Battle_ExecuteMoveEffect(void) {
    Battle_RunMoveEffect();
}
