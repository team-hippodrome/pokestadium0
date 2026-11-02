/* Stadium Zero fragment012_17ED00. */
/* C ported from the Stadium 1 decomp: src/fragments/battle_engine/battle_engine_3020D0.c, src/fragments/battle_engine/battle_engine_31D9F0.c, src/fragments/battle_engine/battle_engine_32A640.c. */

#include "fragments/battle_engine/battle_engine.h"
#include "graphics_textures.h"
#include "ui_graphics.h"
#include "status_icons.h"
#include "game_state.h"
#include "text_system.h"
#include "3D140.h"
#include "gfx_buffer.h"
#include "gfx_rect.h"
#include "matrix.h"
#include "controller.h"
#include "memmap.h"
#include "memory.h"
#include "stdarg.h"
#include "moves.h"
extern unk_D_843901A0* gBattleMessageQueues;

#include "fragments/battle_engine/battle_engine.h"
#include "model_renderer.h"

#include "fragments/battle_engine/battle_engine.h"

#include "m2c_macros.h"

void Battle_ClearAllMessageQueues(void);
void Battle_ClearMessageCursor(void);
void Battle_SimpleStringFormat(s8* arg0, s8* arg1, ...);
void func_8211F3E4(void);
void func_8211F3EC(void);
void BattleScene_ResetMessageQueue(void);

void func_8211B484(TeamRoster*, s32, s32, s32);
void func_8211B900(ActivePokemon*, s32, s32, s32);
void func_821196A4(ActivePokemon*, s32, s32, s32);
void func_82119364(ActivePokemon*, s32, s32, s32);
void func_82119CAC(ActivePokemon*, s32, s32, s32);
void func_8211C6C0(ActivePokemon*, s32, s32, s32);
void func_82118FD8(ActivePokemon*, s32, s32, s32);
void func_8211E890(ActivePokemon* arg0, ActivePokemonState* arg1) {
    TeamRoster* sp2C = arg0->sessionTeams->teamMember[M2C_FIELD(arg0, s32*, 0x9D4)];

    if (arg1->unk_10 == 3) {
        BattleHud_DrawMonStatusBoxPlayer(arg0, arg0->thumbnail.camera->viewport.x - 2, arg0->thumbnail.camera->viewport.y - 0x3A, arg1->unk_1E, 1);
    } else {
        BattleHud_DrawMonStatusBoxPlayer(arg0, arg0->thumbnail.camera->viewport.x - 2, arg0->thumbnail.camera->viewport.y - 0x3A, arg1->unk_1E, 0);
    }

    if ((arg1->unk_10 != 3) && (arg0->thumbnail.camera->viewport.x == 0x17)) {
        switch (arg1->unk_10) {
            case 2:
                if (arg1->unk_1C == 1) {
                    if ((arg0->sessionTeams->tagTeamSize == 2) && (arg0->teamRoster->numberOfPokemonBrought == 3)) {
                        func_8211B484(arg0->sessionTeams->teamMember[0], 0x60, 0xF, arg0->sessionTeams->teamMember[0]->controllerPort);
                        func_8211B484(arg0->sessionTeams->teamMember[1], 0xC6, 0xF, arg0->sessionTeams->teamMember[1]->controllerPort);
                    } else if (arg0->teamRoster->numberOfPokemonBrought == 3) {
                        func_8211B484(arg0->sessionTeams->teamMember[0], 0x60, 0xF, sp2C->controllerPort);
                    } else {
                        func_8211B900(arg0, 0x60, 0xF, sp2C->controllerPort);
                    }
                } else if (M2C_FIELD(arg1, u8*, 0x2E) == 0x10) {
                    func_821196A4(arg0, 0x60, 0xF, sp2C->controllerPort);
                } else {
                    func_82119364(arg0, 0x60, 0xF, sp2C->controllerPort);
                }
                break;
            case 1:
                if (arg1->unk_1C == 1) {
                    func_82119CAC(arg0, 0x60, 0xF, sp2C->controllerPort);
                } else {
                    func_82119364(arg0, 0x60, 0xF, sp2C->controllerPort);
                }
                break;
            case 4:
                func_8211C6C0(arg0, 0x5F, 0xE, sp2C->controllerPort);
                break;
            default:
                func_82118FD8(arg0, 0x60, 0xF, sp2C->controllerPort);
                break;
        }
    }
}

void func_82118738(ActivePokemon*, s16, s16, u16, s32);
void func_8211EB10(ActivePokemon* arg0, ActivePokemonState* arg1) {
    TeamRoster* sp2C = arg0->sessionTeams->teamMember[M2C_FIELD(arg0, s32*, 0x9D4)];

    if (arg1->unk_10 == 3) {
        func_82118738(arg0, arg0->thumbnail.camera->viewport.x - 0x20, arg0->thumbnail.camera->viewport.y - 2, arg1->unk_1E, 1);
    } else {
        func_82118738(arg0, arg0->thumbnail.camera->viewport.x - 0x20, arg0->thumbnail.camera->viewport.y - 2, arg1->unk_1E, 0);
    }

    if ((arg1->unk_10 != 3) && (arg0->thumbnail.camera->viewport.x == 0x103)) {
        switch (arg1->unk_10) {
            case 2:
                if (arg1->unk_1C == 1) {
                    if ((arg0->sessionTeams->tagTeamSize == 2) && (arg0->teamRoster->numberOfPokemonBrought == 3)) {
                        func_8211B484(arg0->sessionTeams->teamMember[0], 0x16, 0x79, arg0->sessionTeams->teamMember[0]->controllerPort);
                        func_8211B484(arg0->sessionTeams->teamMember[1], 0x7C, 0x79, arg0->sessionTeams->teamMember[1]->controllerPort);
                    } else if (arg0->teamRoster->numberOfPokemonBrought == 3) {
                        func_8211B484(arg0->sessionTeams->teamMember[0], 0x7C, 0x79, sp2C->controllerPort);
                    } else {
                        func_8211B900(arg0, 0x18, 0x79, sp2C->controllerPort);
                    }
                } else if (M2C_FIELD(arg1, u8*, 0x2E) == 0x10) {
                    func_821196A4(arg0, 0x9A, 0xCE, sp2C->controllerPort);
                } else {
                    func_82119364(arg0, 0x62, 0xCE, sp2C->controllerPort);
                }
                break;
            case 1:
                if (arg1->unk_1C == 1) {
                    func_82119CAC(arg0, 0x19, 0xA6, sp2C->controllerPort);
                } else {
                    func_82119364(arg0, 0x62, 0xCE, sp2C->controllerPort);
                }
                break;
            case 4:
                func_8211C6C0(arg0, 0x17, 0xBB, sp2C->controllerPort);
                break;
            default:
                func_82118FD8(arg0, 0x18, 0xCE, sp2C->controllerPort);
                break;
        }
    }
}

void Battle_ClearAllMessageQueues(void) {
    gBattleMessageQueues->unk_088[0] = 0;
    gBattleMessageQueues->unk_088[1] = 0;
    gBattleMessageQueues->unk_0C8[0] = 0;
    gBattleMessageQueues->unk_0C8[1] = 0;
    gBattleMessageQueues->unk_108[0] = 0;
    gBattleMessageQueues->unk_108[1] = 0;
    gBattleMessageQueues->unk_148[0] = 0;
    gBattleMessageQueues->unk_148[1] = 0;
    gBattleMessageQueues->unk_188[0] = 0;
    gBattleMessageQueues->unk_188[1] = 0;
    gBattleMessageQueues->unk_1C8[0] = 0;
    gBattleMessageQueues->unk_1C8[1] = 0;
    gBattleMessageQueues->unk_448[0][0] = 0;
    gBattleMessageQueues->unk_448[0][1] = 0;
    gBattleMessageQueues->unk_448[1][0] = 0;
    gBattleMessageQueues->unk_448[1][1] = 0;
    gBattleMessageQueues->unk_208[0] = 0;
    gBattleMessageQueues->unk_208[1] = 0;
    gBattleMessageQueues->unk_308[0] = 0;
    gBattleMessageQueues->unk_308[1] = 0;
    gBattleMessageQueues->unk_2C8[0] = 0;
    gBattleMessageQueues->unk_2C8[1] = 0;
    gBattleMessageQueues->unk_348[0] = 0;
    gBattleMessageQueues->unk_348[1] = 0;
    gBattleMessageQueues->unk_388[0] = 0;
    gBattleMessageQueues->unk_388[1] = 0;
    gBattleMessageQueues->unk_3C8[0] = 0;
    gBattleMessageQueues->unk_3C8[1] = 0;
    gBattleMessageQueues->unk_408[0] = 0;
    gBattleMessageQueues->unk_408[1] = 0;
}

void Battle_ClearMessageCursor(void) {
    gBattleMessageQueues->unk_004 = 0;
    gBattleMessageQueues->unk_048[0] = 0;
    gBattleMessageQueues->unk_048[1] = 0;
    gBattleMessageQueues->unk_008[0] = 0;
    gBattleMessageQueues->unk_008[1] = 0;
}

void Battle_SimpleStringFormat(s8* arg0, s8* arg1, ...) {
    va_list args;
    s8* src;
    s8* fmt;
    s32 len;

    len = 0;
    va_start(args, arg1);
    fmt = arg1;

    while (*fmt != 0) {
        if (*fmt != 0x25) {
            arg0[len++] = *fmt;
        } else {
            fmt++;
            if (*fmt == 0x73) {
                src = va_arg(args, s8*);
                while (*src != 0) {
                    arg0[len] = *src;
                    src++;
                    len++;
                }
            }
        }
        fmt++;
    }
    arg0[len] = 0;
}

void func_8211EF74(s8* arg0, s8 id, s8* arg1, ...) {
    va_list args;
    s8* src;
    s8* fmt;
    s32 len;

    arg0[0] = id;
    len = 1;
    va_start(args, arg1);
    fmt = arg1;

    while (*fmt != 0) {
        if (*fmt != 0x25) {
            arg0[len++] = *fmt;
        } else {
            fmt++;
            if (*fmt == 0x73) {
                src = va_arg(args, s8*);
                while (*src != 0) {
                    arg0[len] = *src;
                    src++;
                    len++;
                }
            }
        }
        fmt++;
    }
    arg0[len] = 0;
}

void func_8211EE8C(void);
void func_8211EEC0(void*, s8*);
void func_80042A6C(s32);
void func_80042FF8(s32);
extern void* D_8219A520;

void func_8211F034(s8* arg0, s32 side) {
    ActivePokemon* ap;

    func_8211EE8C();
    ap = sActivePokemon[side];
    *(u8*)D_8219A520 = (*(u8***)((u8*)ap + 0x85C))[*(s32*)((u8*)ap + 0x9D4) + 2][1];
    func_8211EEC0((u8*)D_8219A520 + 0x48, arg0 + 1);
    if (!(arg0[0] & 0x80)) {
        func_80042A6C(arg0[0] & 0x7F);
    } else {
        func_80042FF8(arg0[0] & 0x7F);
    }
    arg0[0] = 0;
}

#ifdef NON_MATCHING
/* TODO: decompile func_8211F0DC; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_8211F0DC.s")
#endif

void func_8211F0DC(void);
void Battle_DrawCompactStatusBoxesIfVisible(void) {
    ActivePokemon* ptr1 = sActivePokemon[0];
    ActivePokemon* ptr2 = sActivePokemon[1];

    if (sBattleScene.scene->unk_30 == 0) {
        BattleHud_DrawCompactMonStatusBox(ptr1, 0x15, 0xF, ptr1->sessionTeams->teamMember[M2C_FIELD(ptr1, s32*, 0x9D4)]->controllerPort);
        BattleHud_DrawCompactMonStatusBox(ptr2, 0xE1, 0xF, ptr2->sessionTeams->teamMember[M2C_FIELD(ptr2, s32*, 0x9D4)]->controllerPort);
        func_8211F0DC();
    }
}

void func_8211F274(s8 *arg0) {
    M2C_FIELD(arg0, s32 *, 0xA04) = 0;
    M2C_FIELD(arg0, s32 *, 0xA08) = 0;
    M2C_FIELD(arg0, s8 *, 0xA4C) = 0;
    M2C_FIELD(arg0, s8 *, 0xA0C) = 0;
}

/*
 * func_8211F288
 *
 * Starts a caption for the participant: stores the byte at index 1 of the
 * session entry selected by state.unk_2D_zero (+0x7B9) + 2 (from the table at
 * ActivePokemon +0x85C) into the byte D_8219A520 points to, sets
 * captionState.unk_00 to 1, and formats the string arg1 into
 * captionState.unk_48 with func_8211EEC0 (Battle_SimpleStringFormat). The
 * function is variadic: the extra arguments are the format's values, which is
 * why retail stores $a2/$a3 to their stack homes.
 */
void func_8211F288(ActivePokemon* arg0, s8* arg1, ...) {
    *(u8*)D_8219A520 = (*(u8***)((u8*)arg0 + 0x85C))[arg0->state.unk_2D_zero + 2][1];
    arg0->captionState.unk_00 = 1;
    func_8211EEC0(&arg0->captionState.unk_48, arg1);
}

void func_8211C43C(u8, s32, s32, s8*);
extern ActivePokemon* sSide1ActivePokemon;
void func_8211F2E0(ActivePokemon* arg0) {
    TeamRoster* roster = arg0->teamRoster;
    s8 c = arg0->captionState.unk_48[arg0->captionState.unk_04];

    if (c != 0) {
        if ((c == 0xA) || (c == 0x20)) {
            arg0->captionState.unk_08[arg0->captionState.unk_04] = c;
            arg0->captionState.unk_04++;
            c = arg0->captionState.unk_48[arg0->captionState.unk_04];
        }
        if ((c > 0x20) && (c < 0x40)) {
            arg0->captionState.unk_08[arg0->captionState.unk_04] = c;
            arg0->captionState.unk_04++;
        } else {
            arg0->captionState.unk_08[arg0->captionState.unk_04] = c;
            arg0->captionState.unk_08[arg0->captionState.unk_04 + 1] = arg0->captionState.unk_48[arg0->captionState.unk_04 + 1];
            arg0->captionState.unk_04 += 2;
        }
    }
    arg0->captionState.unk_08[arg0->captionState.unk_04] = 0;
    if (arg0->captionState.unk_48[0] != 0) {
        if (arg0 == sSide1ActivePokemon) {
            func_8211C43C(M2C_FIELD(roster, u8*, 1), 0x5F, 0xE, arg0->captionState.unk_08);
        } else {
            func_8211C43C(M2C_FIELD(roster, u8*, 1), 0x17, 0xBB, arg0->captionState.unk_08);
        }
    }
}

void func_8211F3E4(void) {
}

void func_8211F3EC(void) {
}

extern void* D_8219A520;

void func_8211F3F4(void) {
    D_8219A520 = main_pool_alloc(0x4C8, 0);
    bzero(D_8219A520, 0x4C8);
}

void BattleScene_ResetMessageQueue(void) {
    gBattleMessageQueues->unk_004 = 0;
    gBattleMessageQueues->unk_008[gBattleMessageQueues->unk_004] = 0;
    Battle_ClearMessageCursor();
}

#ifdef NON_MATCHING
/* TODO: decompile func_8211F46C; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_8211F46C.s")
#endif
