/* Fixed-layout split; original translation-unit boundaries remain unconfirmed. */
#include "global.h"
#include "moves.h"
#include "pokemon.h"
#include "pokemon_types.h"
#include "battle.h"

extern ComSide* D_821CF294;
extern ComSide* D_821CF298;
extern ComBattler* D_821CF29C;
extern ComBattler* D_821CF2A0;

/**
 * Random move choice used in AI mode 3: picks a random usable move, with soft
 * checks that steer away from Self-Destruct, sleep moves, healing and Dream Eater
 * when they make little sense.
 * Seen in play (2026-11-13) in a Pokémon Cup (L1～30, モンスターボールカップ) battle it ran twice when the COM
 * picked its first move, so the cup's first opponent uses this AI mode.
 * @unverified Name and comment guessed from the code (COM AI pass).
 */
s32 BattleAi_ChooseRandomMove(void) {
    s32 byte;
    s32 i;
    s32 acc;
    u8 slots[4];
    s32 cnt;

    for (i = 0; i < 4; i++) {
        slots[i] = 0;
    }
    acc = 0;
    for (i = 0; i < 4; i++) {
        byte = D_821CF29C->mon.moves[i];
        if (byte == 0) {
            break;
        }
        if ((D_821CF29C->mon.moves[i] != 0) && ((D_821CF29C->mon.pp[i] & 0x3F) != 0) && (D_821CF29C->mon.disabledMove != D_821CF29C->mon.moves[i])) {
            slots[i] = byte;
        } else {
            slots[i] = 0;
        }
        acc |= slots[i];
    }
    if (acc == 0) {
        return 0;
    }
    cnt = 0;
    i = BattleAi_RandomPercent() % 4;
    while (cnt != 100) {
        if (slots[i] != 0) {
            switch (slots[i]) {
                case SELFDESTRUCT:
                case EXPLOSION:
                    if ((cnt < 10) && (BattleAi_GetHpPercent((s8 *) D_821CF29C) >= 0x33)) {
                        break;
                    }
                    if ((cnt < 50) && (BattleAi_RandomPercent() < 95)) {
                        break;
                    }
                    if ((cnt < 80) && (BattleAi_CountUnfainted(D_821CF294) == 1)) {
                        break;
                    }
                    return i;
                case SING:
                case SLEEP_POWDER:
                case HYPNOSIS:
                case LOVELY_KISS:
                case SPORE:
                    if ((cnt < 30) && (BattleAi_SleepClauseAllows(D_821CF298) == 0)) {
                        break;
                    }
                    return i;
                case RECOVER:
                case SOFTBOILED:
                case REST:
                    if ((cnt < 50) && (BattleAi_GetHpPercent((s8 *) D_821CF29C) >= 0x5B)) {
                        break;
                    }
                    return i;
                case DREAM_EATER:
                    if ((cnt < 50) && ((D_821CF2A0->mon.pendingStatusCondition & 7) == 0)) {
                        break;
                    }
                    if ((cnt < 50) && ((D_821CF2A0->mon.pendingStatusCondition & 7) != 0) && (BattleAi_RandomPercent() < 80) && (BattleAi_CountUnfainted(D_821CF298) != 1)) {
                        break;
                    }
                    return i;
                default:
                    return i;
            }
        }
        i++;
        cnt++;
        i = i % 4;
    }
    return 0;
}
