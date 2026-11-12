/* Fixed-layout split; original translation-unit boundaries remain unconfirmed. */
#include "global.h"
#include "moves.h"
#include "pokemon.h"
#include "pokemon_types.h"
#include "fragments/particle_math/particle_math.h"
#include "jpeg_stream.h"
#include "controller.h"

struct BattleSlotZ;
extern struct BattleSlotZ* D_821CF294;
extern struct BattleSlotZ* D_821CF298;
extern u8* D_821CF29C;
extern s8* D_821CF2A0;

/**
 * Random move choice used in AI mode 3: picks a random usable move, with soft
 * checks that steer away from Self-Destruct, sleep moves, healing and Dream Eater
 * when they make little sense.
 * @unverified Name and comment guessed from the code (COM AI pass).
 */
s32 BattleAI_ChooseRandomMove(void) {
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
        byte = D_821CF29C[i + 0x2B];
        if (byte == 0) {
            break;
        }
        if ((D_821CF29C[i + 0x2B] != 0) && ((D_821CF29C[i + 0x3E] & 0x3F) != 0) && (D_821CF29C[0x63] != D_821CF29C[i + 0x2B])) {
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
    i = BattleAI_RandomPercent() % 4;
    while (cnt != 100) {
        if (slots[i] != 0) {
            switch (slots[i]) {
                case SELFDESTRUCT:
                case EXPLOSION:
                    if ((cnt < 0xA) && (BattleAI_GetHpPercent((s8 *) D_821CF29C) >= 0x33)) {
                        break;
                    }
                    if ((cnt < 0x32) && (BattleAI_RandomPercent() < 0x5F)) {
                        break;
                    }
                    if ((cnt < 0x50) && (BattleAI_CountUnfainted((u8 *) D_821CF294) == 1)) {
                        break;
                    }
                    return i;
                case SING:
                case SLEEP_POWDER:
                case HYPNOSIS:
                case LOVELY_KISS:
                case SPORE:
                    if ((cnt < 0x1E) && (BattleAI_SleepClauseAllows(D_821CF298) == 0)) {
                        break;
                    }
                    return i;
                case RECOVER:
                case SOFTBOILED:
                case REST:
                    if ((cnt < 0x32) && (BattleAI_GetHpPercent((s8 *) D_821CF29C) >= 0x5B)) {
                        break;
                    }
                    return i;
                case DREAM_EATER:
                    if ((cnt < 0x32) && ((((u8 *) D_821CF2A0)[0x21] & 7) == 0)) {
                        break;
                    }
                    if ((cnt < 0x32) && ((((u8 *) D_821CF2A0)[0x21] & 7) != 0) && (BattleAI_RandomPercent() < 0x50) && (BattleAI_CountUnfainted((u8 *) D_821CF298) != 1)) {
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
