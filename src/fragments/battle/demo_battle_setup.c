#include "moves.h"
/* Stadium Zero fragment012_17ED00. */

#include "battle.h"
#include "m2c_macros.h"

/**
 * Copies the Pokemon's battle HP (0x7D2) into the first team member's HP.
 * @unverified Name guessed from the code.
 */
void DemoBattle_CopyHpToFirstMember(ActivePokemon* arg0) {
    BattleMon* mon = arg0->teamRoster->pokemonPicked;

    mon->hp = arg0->state.runtime.hp;
}

/*
 * DemoBattle_Setup
 *
 * Resets some fields of the battle scene object (sBattleScene.scene;
 * D_82199DE0 is sActivePokemon, an array
 * of two pointers):
 *
 *   - BattleScene_SetCameraSubstate(1, 0) is called.
 *   - The halfword at +0x2C of the scene object is saved, then cleared, and
 *     the halfword at +0x2A is written with the cleared value (0).
 *   - The word at +0x38 is cleared, and the halfword at +0x32 is cleared in
 *     the structure at 0x78C bytes into each of the two active Pokemon.
 *   - If the word at +0x1C is 9, the word at +0x44 is set to 10.
 *   - DemoBattle_SetupDemoMove is called with the saved halfword, and the halfword is
 *     then written back to +0x2C.
 *
 * What the individual fields mean and what DemoBattle_SetupDemoMove does are not
 * established here.  The saved value is kept in an s32 and DemoBattle_SetupDemoMove is
 * declared with an s32 parameter because that is what reproduces the retail
 * code (a word-sized stack spill and no halfword mask on the argument).
 */
M2C_UNK func_82121D8C(M2C_UNK, M2C_UNK);            /* extern */
void DemoBattle_SetupDemoMove();
extern M2C_UNK D_82199DE0;

/**
 * Sets up the scene mode 11 demo battle: switches the camera to mode 0 for both sides, runs
 * DemoBattle_SetupDemoMove for the selected side and restores the side index.
 * @unverified Name guessed from the code.
 */
void DemoBattle_Setup(void) {
    s32 saved;
    void *sp20;
    void *sp1C;

    sp20 = M2C_FIELD(&D_82199DE0, s32 *, 0) + 0x78C;
    sp1C = M2C_FIELD(&D_82199DE0, s32 *, 4) + 0x78C;
    func_82121D8C(1, 0);
    saved = sBattleScene.scene->actingSide;
    sBattleScene.scene->actingSide = 0U;
    sBattleScene.scene->sideCurrentlySwitching = (u16) sBattleScene.scene->actingSide;
    sBattleScene.scene->phase = 0;
    M2C_FIELD(sp20, s16 *, 0x32) = 0;
    M2C_FIELD(sp1C, s16 *, 0x32) = 0;
    if (sBattleScene.scene->mode == 9) {
        sBattleScene.scene->modeAfterTransition = 0xA;
    }
    DemoBattle_SetupDemoMove(saved);
    sBattleScene.scene->actingSide = saved;
}

void func_8211ED90(void);
extern s8 D_82199F31;
extern s32 D_82199F78;
extern s8 D_82199FCC;
extern s8 D_82199FCD;
/**
 * Sets up the demo move for the selected side: both sides get 900 HP, the move state is
 * reset, and the move picks the demo effect (String Shot, Harden/Minimize/Splash, Sing and
 * Rest each set their own effect kind; Sing puts the target and Rest the user to sleep).
 * @unverified Name guessed from the code.
 */
void DemoBattle_SetupDemoMove(void) {
    s8* self;
    s8* other;
    u16 idx;
    u8 move;

    idx = sBattleScene.scene->actingSide;
    self = ((s8**)&D_82199DE0)[idx];
    other = ((s8**)&D_82199DE0)[idx == 0] + 0x7C6;
    D_82199F31 = 0;
    D_82199F78 = 0x14;
    M2C_FIELD(self, s16*, 0x7D2) = 900;
    M2C_FIELD(other, s16*, 0xC) = 900;
    self += 0x7C6;
    DemoBattle_CopyHpToFirstMember(((s8**)&D_82199DE0)[(idx == 0) * 0]); // FAKE: keeps idx == 0 live
    DemoBattle_CopyHpToFirstMember(((s8**)&D_82199DE0)[1]);
    D_82199FCC = 1;
    D_82199FCD = 1;
    sBattleScene.scene->hitReactionKind = 0;
    sBattleScene.scene->moveEffectKind = 0;
    M2C_FIELD(self, u16*, 0x12) = 0xFFFF;
    M2C_FIELD(other, u16*, 0x12) = 0xFFFF;
    func_8211ED90();
    move = M2C_FIELD(self, u8*, 0x5A);
    switch (move) {
        case STRING_SHOT:
            sBattleScene.scene->hitReactionKind = 3;
            break;
        case HARDEN:
        case MINIMIZE:
        case SPLASH:
            sBattleScene.scene->moveEffectKind = 7;
            break;
        case SING:
            sBattleScene.scene->moveEffectKind = 0x16;
            M2C_FIELD(other, s8*, 0x15) = 3;
            break;
        case REST:
            sBattleScene.scene->moveEffectKind = 0x15;
            M2C_FIELD(self, s8*, 0x15) = 3;
            break;
    }
}

void func_82101AD0(void);
void func_82136708(s32, ActivePokemon*);
M2C_UNK func_8213B31C(M2C_UNK);

/**
 * Clears the Pokemon's status for the demo: plays reaction 3 if it was asleep, clears its
 * roster status byte, state flags and pending status, and resets both camera modes.
 * @unverified Name guessed from the code.
 */
void DemoBattle_ClearStatus(ActivePokemon* active_pokemon) {
    s32 pad; // FAKE: stack padding
    s8* sp20 = (s8*)active_pokemon->teamRoster + 0x1C;
    BattleMonRuntime* rt = &active_pokemon->state.runtime;

    func_82101AD0();
    if (rt->statusCondition & 7) {
        func_82136708(3, active_pokemon);
    }
    M2C_FIELD(sp20, s8*, 5) = 0;
    M2C_FIELD(active_pokemon, s16*, 0x7C2) = 0;
    rt->statusCondition = 0;
    func_8213B31C(1);
    func_8213B31C(2);
}

typedef struct Cue82133A44 {
    /* 0x0 */ u16 duration;
    /* 0x2 */ u16 value;
    /* 0x4 */ u16 unk4;
} Cue82133A44; // size = 0x6

typedef struct Scene82133A44 {
    /* 0x00 */ u8 flags;
    /* 0x01 */ s8 unk01;
    /* 0x02 */ s8 unk02;
    /* 0x03 */ u8 unk03;
    /* 0x04 */ u8 index;
    /* 0x05 */ char unk05[1];
    /* 0x06 */ s16 width;
    /* 0x08 */ s16 height;
    /* 0x0A */ char unk0A[2];
    /* 0x0C */ f32 dist;
    /* 0x10 */ f32 curDist;
    /* 0x14 */ s16 angle;
    /* 0x16 */ s16 unk16;
    /* 0x18 */ s16 unk18;
    /* 0x1A */ s16 timer;
    /* 0x1C */ s16 unk1C;
    /* 0x1E */ s16 unk_1E;
    /* 0x20 */ s16 unk_20;
} Scene82133A44;

extern Scene82133A44 D_8219A4F0;
extern Cue82133A44* D_8218B42C[][99];
extern s32 D_82199F18[2];
extern s32 D_82199F10[2];
extern u16 D_82199ED0[][0x12];

/**
 * Steps side 0's scripted demo input: when its timer runs out, takes the next (duration,
 * value) entry of the script for demo D_8219A4F0.index and outputs the value for one frame.
 * @unverified Name guessed from the code.
 */
void DemoBattle_StepScriptedInputSide0(void) {
    s32 i = 0; // FAKE: constant side index kept in a variable

    D_82199ED0[i][0] = 0;
    if (D_82199F18[i] == 0) {
        if ((D_82199F18[i] = D_8218B42C[i][D_8219A4F0.index][D_82199F10[i]].duration) != 0) {
            D_82199ED0[i][0] = D_8218B42C[i][D_8219A4F0.index][D_82199F10[i]].value;
            D_82199F10[i]++;
            D_8219A4F0.unk_1E = 0;
        }
    }
    if (D_82199F18[i] > 0) {
        D_82199F18[i]--;
    }
}

/**
 * Same as DemoBattle_StepScriptedInputSide0 for side 1.
 * @unverified Name guessed from the code.
 */
void DemoBattle_StepScriptedInputSide1(void) {
    s32 i = 1; // FAKE: constant side index kept in a variable

    D_82199ED0[i][0] = 0;
    if (D_82199F18[i] == 0) {
        if ((D_82199F18[i] = D_8218B42C[i][D_8219A4F0.index][D_82199F10[i]].duration) != 0) {
            D_82199ED0[i][0] = D_8218B42C[i][D_8219A4F0.index][D_82199F10[i]].value;
            D_82199F10[i]++;
            D_8219A4F0.unk_20 = 0;
        }
    }
    if (D_82199F18[i] > 0) {
        D_82199F18[i]--;
    }
}

typedef struct Step82133B6C {
    /* 0x00 */ s16 x;
    /* 0x02 */ s16 y;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ s16 unk06;
    /* 0x08 */ u8 move0;
    /* 0x09 */ u8 move1;
    /* 0x0A */ u8 unk0A;
    /* 0x0B */ u8 unk0B;
    /* 0x0C */ char unk0C[2];
} Step82133B6C; // size = 0xE
extern Step82133B6C D_8218B5D0[];
extern s8* D_82199DE4;
void func_80005B98(s32); // StageFade_Start; declared void here because the s32 prototype changes register allocation
void func_80006998(s32);
f32 func_8000F23C(f32, f32, f32, f32);
void func_80010B3C(void*, s16, s16, s16, s16);
void Battle_LoadOwnerModelForSwitchIn(ActivePokemon* active_pokemon);
void func_8210BE1C(f32*, f32, s16);
s16 func_8210BEE0(f32, f32, f32, f32);
f32 func_8210BFA4(f32, f32, f32, f32);
void func_82121D5C(s32, s32);
/**
 * Per-frame update for the scripted battle demo: advances the cue timers for
 * both sides (DemoBattle_StepScriptedInputSide0 / DemoBattle_StepScriptedInputSide1) and reacts to the cue flags in
 * D_82199ED0[side][0].
 * @unverified Name guessed from the code.
 */
void DemoBattle_Update(void) {
    s8* rt0 = ((s8**)&D_82199DE0)[0] + 0x78C;
    s8* rt1 = ((s8**)&D_82199DE0)[1] + 0x78C;
    s8* other0 = ((s8**)&D_82199DE0)[0] + 0x7C6;
    s8* other1 = ((s8**)&D_82199DE0)[1] + 0x7C6;
    UNUSED s32 pad; // FAKE
    s8** mons; // FAKE
    s32 side = 1; // FAKE: constant side index kept in a variable
    f32 vec[3];

    sBattleScene.scene->cameraPresetId = 0;
    mons = (s8**)&D_82199DE0;
    if (sBattleScene.scene->phaseStep != 29) {
        D_8219A4F0.unk_1E++;
        D_8219A4F0.unk_20++;
        D_8219A4F0.timer++;
        DemoBattle_StepScriptedInputSide0();
        DemoBattle_StepScriptedInputSide1();
        if (D_82199ED0[side][0] & 0x8000) {
            D_8219A4F0.unk03++;
            D_8219A4F0.unk1C++;
            D_8219A4F0.flags |= 8;
            D_8219A4F0.unk02 = 0;
        }
        if (D_82199ED0[side][0] & 0x4000) {
            D_8219A4F0.flags &= ~8;
        }
        if (D_8219A4F0.index == 5) {
            D_8219A4F0.unk16 = D_8218B5D0[D_8219A4F0.index].unk04;
            D_8219A4F0.unk18 = D_8218B5D0[D_8219A4F0.index].unk06;
            ((ActivePokemon*)((s8**)&D_82199DE0)[0])->displayObject.node.flags |= 1;
            if (D_82199ED0[0][0] & 0x8000) {
                D_8219A4F0.unk01 = 0;
                D_8219A4F0.flags |= 0xA0;
            }
            if (D_82199ED0[0][0] & 0x4000) {
                D_8219A4F0.unk01 = 0;
                D_8219A4F0.flags |= 0xC0;
            }
            if (D_82199ED0[0][0] & 0x20) {
                D_8219A4F0.flags &= ~0x80;
            }
        } else {
            if (D_82199ED0[0][0] & 0x1000) {
                M2C_FIELD(rt0, s32*, 4) = 0;
                M2C_FIELD(rt1, s32*, 4) = 0;
                if (M2C_FIELD(rt0, u8*, 0x2A) == 0) {
                    M2C_FIELD(other0, u8*, 0x5A) = D_8218B5D0[D_8219A4F0.index].move0;
                }
                M2C_FIELD(rt0, s32*, 0x10) = 3;
                if (M2C_FIELD(rt1, u8*, 0x2A) == 0) {
                    M2C_FIELD(other1, u8*, 0x5A) = D_8218B5D0[D_8219A4F0.index].move1;
                }
                M2C_FIELD(rt1, s32*, 0x10) = 3;
                if ((M2C_FIELD(rt0, s32*, 0x10) == 3) && (M2C_FIELD(rt1, s32*, 0x10) == 3)) {
                    DemoBattle_Setup();
                }
            }
            if (D_82199ED0[0][0] & 0x4000) {
                func_80006998(0);
                func_80005B98(0x14);
                D_8219A4F0.timer = 0;
                D_8219A4F0.flags &= ~8;
                D_8219A4F0.flags |= 0x10;
            }
            if ((D_8219A4F0.timer == 25) && (D_8219A4F0.flags & 0x10)) {
                if (D_8219A4F0.index == 4) {
                    ((ActivePokemon*)((s8**)&D_82199DE0)[0])->side->displayModel = 0x96;
                } else {
                    M2C_FIELD(M2C_FIELD(mons[0], u8**, 0x85C), s16*, 2) = D_8218B5D0[D_8219A4F0.index + 1].unk0A;
                }
                ((ActivePokemon*)((s8**)&D_82199DE0)[0])->side->modelFlags |= 0x80;
                D_8219A4F0.flags |= 2;
                D_8219A4F0.flags &= ~0x10;
                sBattleScene.scene->camera->perspective.verticalFieldOfView = 30.0f;
            }
            if (D_8219A4F0.flags & 2) {
                if (((ActivePokemon*)((s8**)&D_82199DE0)[0])->side->modelFlags & 0x10) {
                    ((ActivePokemon*)((s8**)&D_82199DE0)[0])->side->modelFlags &= ~0x90;
                    Battle_LoadOwnerModelForSwitchIn(((s8**)&D_82199DE0)[0]);
                    if (D_8219A4F0.index == 4) {
                        ((ActivePokemon*)((s8**)&D_82199DE0)[0])->side->displayModel = 0x96;
                    }
                    ((ActivePokemon*)((s8**)&D_82199DE0)[1])->side->displayModel = D_8218B5D0[D_8219A4F0.index + 1].unk0B;
                    ((ActivePokemon*)((s8**)&D_82199DE0)[1])->side->modelFlags |= 0x80;
                    D_8219A4F0.flags |= 4;
                    D_8219A4F0.flags &= ~2;
                }
            }
            if (D_8219A4F0.flags & 4) {
                if (((ActivePokemon*)((s8**)&D_82199DE0)[1])->side->modelFlags & 0x10) {
                    ((ActivePokemon*)((s8**)&D_82199DE0)[1])->side->modelFlags &= ~0x90;
                    Battle_LoadOwnerModelForSwitchIn(((s8**)&D_82199DE0)[1]);
                    D_8219A4F0.flags &= ~4;
                    func_80005B98(0x18);
                    D_82199F10[0] = 0;
                    D_82199F18[0] = 0;
                    D_8219A4F0.flags = D_82199F18[1] = D_82199F10[1] = 0;
                    D_8219A4F0.index++;
                    D_8219A4F0.timer = 0;
                    func_80010B3C(sBattleScene.scene->camera, 0, 0, 0x140, 0xF0);
                    sBattleScene.scene->bRollShotIndex = 0;
                    func_82121D5C(9, 0x32);
                    sBattleScene.scene->bRollShotIndex = 0;
                    DemoBattle_ClearStatus(((ActivePokemon**)&D_82199DE0)[0]);
                    DemoBattle_ClearStatus((ActivePokemon*)D_82199DE4);
                }
            }
            if (D_82199ED0[0][0] & 0x8000) {
                D_8219A4F0.unk16 = D_8218B5D0[D_8219A4F0.index].unk04;
                D_8219A4F0.unk18 = D_8218B5D0[D_8219A4F0.index].unk06;
                D_8219A4F0.width = 0x140;
                D_8219A4F0.height = 0xF0;
                D_8219A4F0.flags |= 1;
                D_8219A4F0.dist = func_8210BFA4(0.0f, 0.0f, D_8218B5D0[D_8219A4F0.index].x, D_8218B5D0[D_8219A4F0.index].y);
                D_8219A4F0.angle = func_8210BEE0(0.0f, 0.0f, D_8218B5D0[D_8219A4F0.index].x, D_8218B5D0[D_8219A4F0.index].y);
                D_8219A4F0.curDist = 0.0f;
            }
            if (D_8219A4F0.flags & 1) {
                D_8219A4F0.width = func_8000F23C(D_8219A4F0.width, 160.0f, 8.0f, 8.0f);
                D_8219A4F0.height = func_8000F23C(D_8219A4F0.height, 120.0f, 6.0f, 6.0f);
                D_8219A4F0.curDist = func_8000F23C(D_8219A4F0.curDist, D_8219A4F0.dist, D_8219A4F0.dist / 20.0f, D_8219A4F0.dist / 20.0f);
                func_8210BE1C(vec, D_8219A4F0.curDist, D_8219A4F0.angle);
                func_80010B3C(sBattleScene.scene->camera, vec[0], vec[2], D_8219A4F0.width, D_8219A4F0.height);
                if (D_8219A4F0.width == 0xA0) {
                    D_8219A4F0.flags &= ~1;
                }
            }
        }
    }
}
