/* Fixed-layout split; original translation-unit boundaries remain unconfirmed. */
#include "global.h"
#include "moves.h"
#include "pokemon.h"
#include "pokemon_types.h"
#include "m2c_macros.h"

extern u8* D_821CF29C;
extern s8* D_821CF2A0;
s32 BattleAi_GetBestDamage(u8 *arg0, u8 *arg1, s32 arg2);
s32 BattleAi_MovesFirst(s8 *arg0, s8 *arg1);
s32 BattleAi_CanUseMove(s8 *arg0, s32 arg1);
s32 BattleAi_EstimateDamage(s8 *, s8 *, u8);

/**
 * If the chosen move is Hyper Beam but it would not knock the opponent out, looks
 * for another damaging move that would, trying stronger move groups only in later
 * rounds. Returns the move slot to use.
 * @unverified Name and comment guessed from the code (COM AI pass).
 */
s32 BattleAi_ReplaceHyperBeam(s32 arg0) {
    s32 i;
    s32 tier;
    s32 best;
    s32 threshold;
    s32 v;
    u8 move;

    if (arg0 >= 0 && arg0 < 4 && BattleAi_GetBestDamage((u8*)D_821CF2A0, D_821CF29C, 0) < M2C_FIELD(D_821CF29C, u16*, 0x18) && (D_821CF29C + arg0)[0x2B] == HYPER_BEAM) {
        threshold = M2C_FIELD(D_821CF2A0, u16*, 0x18) - BattleAi_EstimateDamage((s8*)D_821CF29C + 0xC, D_821CF2A0 + 0xC, 0x3F) * 9 / 10;
        best = -1;
        if (threshold > 0) {
            for (tier = 0; tier < 4; tier++) {
                for (i = 0; i < 4; i++) {
                    if ((D_821CF29C + i)[0x2B] == 0) {
                        break;
                    }
                    if (BattleAi_MovesFirst((s8*)D_821CF29C, D_821CF2A0) != 0 || (D_821CF29C + i)[0x2B] == QUICK_ATTACK) {
                        move = (D_821CF29C + i)[0x2B];
                        switch (move) {
                            case BIND:
                            case SLAM:
                            case MEGA_KICK:
                            case HYDRO_PUMP:
                            case SUBMISSION:
                            case EGG_BOMB:
                            case 0x80: /* Clamp; the CLAMP name is taken by the macro */
                            case FURY_SWIPES:
                                if (tier < 3) {
                                    break;
                                }
                            case DOUBLESLAP:
                            case COMET_PUNCH:
                            case MEGA_PUNCH:
                            case ROLLING_KICK:
                            case FURY_ATTACK:
                            case WRAP:
                            case TAKE_DOWN:
                            case PIN_MISSILE:
                            case SONICBOOM:
                            case BLIZZARD:
                            case LOW_KICK:
                            case BONE_CLUB:
                            case FIRE_BLAST:
                            case HI_JUMP_KICK:
                            case BARRAGE:
                            case CRABHAMMER:
                            case BONEMERANG:
                            case ROCK_SLIDE:
                            case HYPER_FANG:
                            case SUPER_FANG:
                                if (tier < 2) {
                                    break;
                                }
                            case CUT:
                            case FLY:
                            case JUMP_KICK:
                            case TACKLE:
                            case RAZOR_LEAF:
                                if (tier < 1) {
                                    break;
                                }
                            case POUND:
                            case KARATE_CHOP:
                            case PAY_DAY:
                            case FIRE_PUNCH:
                            case ICE_PUNCH:
                            case THUNDERPUNCH:
                            case SCRATCH:
                            case VICEGRIP:
                            case GUST:
                            case WING_ATTACK:
                            case VINE_WHIP:
                            case STOMP:
                            case DOUBLE_KICK:
                            case HEADBUTT:
                            case HORN_ATTACK:
                            case BODY_SLAM:
                            case DOUBLE_EDGE:
                            case POISON_STING:
                            case TWINEEDLE:
                            case BITE:
                            case ACID:
                            case EMBER:
                            case FLAMETHROWER:
                            case WATER_GUN:
                            case SURF:
                            case ICE_BEAM:
                            case PSYBEAM:
                            case BUBBLEBEAM:
                            case AURORA_BEAM:
                            case PECK:
                            case DRILL_PECK:
                            case SEISMIC_TOSS:
                            case STRENGTH:
                            case ABSORB:
                            case MEGA_DRAIN:
                            case DRAGON_RAGE:
                            case THUNDERSHOCK:
                            case THUNDERBOLT:
                            case EARTHQUAKE:
                            case DIG:
                            case CONFUSION:
                            case PSYCHIC_M:
                            case QUICK_ATTACK:
                            case NIGHT_SHADE:
                            case LICK:
                            case SLUDGE:
                            case WATERFALL:
                            case SWIFT:
                            case SPIKE_CANNON:
                            case CONSTRICT:
                            case LEECH_LIFE:
                            case BUBBLE:
                            case DIZZY_PUNCH:
                            case TRI_ATTACK:
                            case SLASH:
                                v = BattleAi_EstimateDamage((s8*)D_821CF29C + 0xC, D_821CF2A0 + 0xC, move) * 9 / 10;
                                if (best < v && threshold < v) {
                                    best = v;
                                    arg0 = i;
                                }
                                break;
                        }
                    }
                }
            }
        }
    }
    return arg0;
}

/**
 * Returns the slot of the usable move with the highest estimated damage if that
 * damage is more than arg0 percent of the opponent's HP, otherwise -1.
 * @unverified Name and comment guessed from the code (COM AI pass).
 */
s32 BattleAi_PickStrongestMove(s32 arg0) {
    s32 i;
    s32 best = -1;
    s32 best_idx = -1;
    s32 v;

    for (i = 0; i < 4; i++) {
        if ((D_821CF29C + i)[0x2B] == 0) {
            break;
        }
        if (BattleAi_CanUseMove((s8*)D_821CF29C, (D_821CF29C + i)[0x2B]) != 0) {
            v = BattleAi_EstimateDamage((s8*)D_821CF29C + 0xC, D_821CF2A0 + 0xC, (D_821CF29C + i)[0x2B]);
            if (best < v) {
                best = v;
                best_idx = i;
            }
        }
    }
    best = best * 9 / 10;
    if ((M2C_FIELD(D_821CF2A0, u16 *, 0x18) != 0) && (arg0 < (best * 100) / M2C_FIELD(D_821CF2A0, u16 *, 0x18))) {
        return best_idx;
    }
    return -1;
}

extern void *D_821CF294;
s32 BattleAi_GetHpPercent(s8 *);
s32 BattleAi_CountUnfainted(void *);
s32 BattleAi_FindUsableHealingMove(s8 *);
s32 BattleAi_OpponentCannotAct(s8 *, s8 *);
s32 BattleAi_PickSetupMove(s8 *);
s32 BattleAi_PickStatBoostMove(s8 *);
s32 BattleAi_PickHealingMove(s8 *);
s32 BattleAi_PickToxicOrLeechSeed(s8 *);
s32 BattleAi_PickStatLowerMove(s8 *, s8 *);
s32 BattleAi_IsMoveUseful(u8);
s32 BattleAi_PickParalysisMove(s8 *, s8 *);
s32 BattleAi_PickSleepMove(s8 *, s8 *);
s32 BattleAi_PickBoomMove(s8 *, s8 *);
/**
 * Normal move choice. In order: heal, set up when the opponent cannot act
 * (BattleAi_OpponentCannotAct), status the opponent, lower its stats, finish it with a strong move, boost,
 * explode when about to faint, or take the strongest move; then
 * BattleAi_ReplaceHyperBeam, and finally the first move that is useful.
 * @unverified Name and comment guessed from the code (COM AI pass).
 */
s32 BattleAi_ChooseMove(void)
{
  s32 r;
  s32 i;
  s32 j;

  BattleAi_MovesFirst((s8 *) D_821CF29C, D_821CF2A0);
  r = -1;
  if ((BattleAi_MovesFirst((s8 *) D_821CF29C, D_821CF2A0) != 0) && (BattleAi_OpponentCannotAct((s8 *) D_821CF29C, D_821CF2A0) == 0) && (!(((u8 *) D_821CF2A0)[0x21] & 0x27)) && (BattleAi_PickStrongestMove(BattleAi_GetHpPercent(D_821CF2A0)) != 0))
  {
    r = BattleAi_PickHealingMove((s8 *) D_821CF29C);
  }
  if (r < 0)
  {
    if (BattleAi_OpponentCannotAct((s8 *) D_821CF29C, D_821CF2A0) != 0)
    {
      r = BattleAi_PickSetupMove((s8 *) D_821CF29C);
    }
    else
    {
      r = BattleAi_PickToxicOrLeechSeed((s8 *) D_821CF29C);
      if (r < 0)
      {
        r = BattleAi_PickParalysisMove((s8 *) D_821CF29C, D_821CF2A0);
      }
      if (r < 0)
      {
        r = BattleAi_PickSleepMove((s8 *) D_821CF29C, D_821CF2A0);
      }
      if ((r < 0) && ((BattleAi_FindUsableHealingMove(D_821CF2A0) != 0) || (BattleAi_GetHpPercent(D_821CF2A0) >= 21)))
      {
        r = BattleAi_PickStatLowerMove((s8 *) D_821CF29C, D_821CF2A0);
      }
    }
  }
  if (r < 0)
  {
    r = BattleAi_PickStrongestMove(50);
    if ((r < 0) && ((BattleAi_PickStrongestMove(30) != 0) || (BattleAi_FindUsableHealingMove(D_821CF2A0) != 0)) && ((BattleAi_GetHpPercent(D_821CF2A0) >= 51) || (BattleAi_GetHpPercent((s8 *) D_821CF29C) >= 0x51)))
    {
      r = BattleAi_PickStatBoostMove((s8 *) D_821CF29C);
    }
  }
  if (r < 0)
  {
    if ((((BattleAi_MovesFirst((s8 *) D_821CF29C, D_821CF2A0) != 0) && (BattleAi_GetHpPercent((s8 *) D_821CF29C) < 0x14)) || ((BattleAi_MovesFirst((s8 *) D_821CF29C, D_821CF2A0) == 0) && ((M2C_FIELD(D_821CF29C, u16 *, 0x18) / 2) < ((BattleAi_GetBestDamage((u8 *) D_821CF2A0, D_821CF29C, 0) * 0x5A) / 100))) || ((BattleAi_FindUsableHealingMove((s8 *) D_821CF29C) == 0) && (BattleAi_GetHpPercent((s8 *) D_821CF29C) < 0x28))) && (BattleAi_CountUnfainted(D_821CF294) >= 2))
    {
      r = BattleAi_PickBoomMove((s8 *) D_821CF29C, D_821CF2A0);
    }
    if (r < 0)
    {
      r = BattleAi_PickStrongestMove(0);
    }
  }
  r = BattleAi_ReplaceHyperBeam(r);
  if (r < 0)
  {
    for (j = 0; (j < 10) && (r < 0); j++)
    {
      for (i = 0; i < 4; i++)
      {
        if ((D_821CF29C + i)[0x2B] == 0)
        {
          break;
        }
        if ((BattleAi_CanUseMove((s8 *) D_821CF29C, (D_821CF29C + i)[0x2B]) != 0) && ((j != 0) || (BattleAi_IsMoveUseful((D_821CF29C + i)[0x2B]) != 0)))
        {
          r = i;
          break;
        }
      }
    }
  }
  if (r < 0)
  {
    r = 0;
  }
  return r;
}


/**
 * If move slot arg0 has no PP left, returns another slot holding the same move
 * with PP; otherwise arg0.
 * @unverified Name and comment guessed from the code (COM AI pass).
 */
s32 BattleAi_FindSlotWithPp(s32 arg0) {
    s32 i;
    u8* base;
    u8* cur;
    u8* me;
    u8 v;

    base = D_821CF29C;
    me = base + arg0;
    i = 0;
    if (!(me[0x3E] & 0x3F)) {
        cur = base;
        do {
            v = cur[0x2B];
            if (v == 0) {
                break;
            }
            if ((i != arg0) && (v != 0) && (v == me[0x2B]) && (cur[0x3E] & 0x3F)) {
                return i;
            }
            i++;
            cur++;
        } while (i != 4);
    }
    return arg0;
}

extern f64 D_DBL_82198A10;
extern s32 D_821CF2A4;
extern u8 *D_821CF2A8;
extern u8 *D_821CF2AC;
typedef struct Slot90 { u8 *roster; u8 data[0x8C]; } Slot90;
extern Slot90 D_821CF618[6];
extern Slot90 D_821CF998[6];
extern Slot90 *D_821CF298;
extern s32 D_821CF288;
void func_80058410(u8 *, u8 *, s32);
void BattleAi_CopyVisibleBattleState(s8 *, u8 *);
void BattleAi_ResetBattleStats(u8 *, u8 *);
s32 BattleAi_ChooseSwitch(void);
s32 BattleAi_ChooseRandomMove(void);
/**
 * Per-turn COM entry point. Copies both active Pokemon (arg0 own, arg1 opponent's
 * visible state) into the AI's model, updates its turn bookkeeping, then returns
 * a move slot (0..3) or 4 + a party slot to switch, also stored in D_821CF2A4.
 * @unverified Name and comment guessed from the code (COM AI pass).
 */
s32 BattleAi_ChooseTurnAction(u8* arg0, u8* arg1, s32 arg2, s32 arg3) {
    s32 move;
    s32 r;
    s32 one; // FAKE

    D_821CF294 = D_821CF618;
    D_821CF298 = D_821CF998;
    D_821CF29C = ((Slot90*)D_821CF294)[arg2].data;
    D_821CF2A0 = (s8*)D_821CF298[arg3].data;
    D_821CF2A8 = arg0;
    D_821CF2AC = arg1;
    func_80058410(arg0, D_821CF29C + 0xC, 0x64);
    if (M2C_FIELD(D_821CF29C, u16*, 0x18) != M2C_FIELD(D_821CF29C, u16*, 0x70)) {
        if (D_821CF29C[0x67] != 0) {
            M2C_FIELD(D_821CF29C, s16*, 0x72) = (M2C_FIELD(D_821CF29C, u16*, 0x70) - M2C_FIELD(D_821CF29C, u16*, 0x18)) / 2;
        } else {
            M2C_FIELD(D_821CF29C, s16*, 0x72) = M2C_FIELD(D_821CF29C, u16*, 0x70) - M2C_FIELD(D_821CF29C, u16*, 0x18);
        }
        M2C_FIELD(D_821CF29C, u16*, 0x70) = M2C_FIELD(D_821CF29C, u16*, 0x18);
    }
    BattleAi_CopyVisibleBattleState(D_821CF2A0 + 0xC, arg1);
    if (D_821CF29C[0x5A] & 1) {
        D_821CF29C[0x7A]++;
    } else {
        D_821CF29C[0x7A] = 0;
    }
    if (M2C_FIELD(D_821CF294, f32*, 0x364) >= 0.5) {
        M2C_FIELD(D_821CF294, f32*, 0x364) -= D_DBL_82198A10;
    }
    if (arg3 != ((u8*)D_821CF294)[0x369]) {
        move = ((u8*)D_821CF294)[0x369];
        if (move < D_821CF288) {
            BattleAi_ResetBattleStats(D_821CF298[((u8*)D_821CF294)[0x369]].data + 0xC, D_821CF298->roster + move * 0x50 + 0x1C);
        }
        ((u8*)D_821CF294)[0x369] = arg3;
        ((u8*)D_821CF294)[0x36A] = 0;
    } else {
        ((u8*)D_821CF294)[0x36A]++;
    }
    for (move = 0; move < D_821CF288; move++) {
        ((u8*)D_821CF294)[move * 0x90 + 0x7F] = arg0[move + 0x16];
        D_821CF298[move].data[0x7B] = arg1[move + 0x16];
    }

    move = BattleAi_ChooseSwitch();
    if ((move >= 0) && (D_821CF29C[0x75] != ((one = 1) << move))) { // FAKE: one
        r = -1;
        if ((M2C_FIELD(D_821CF29C, u16*, 0x18) != 0) && (BattleAi_GetHpPercent((s8*)D_821CF29C) < 0x23) &&
            (BattleAi_CountUnfainted(D_821CF294) >= 2) && (BattleAi_PickBoomMove((s8*)D_821CF29C, D_821CF2A0) >= 0)) {
            r = BattleAi_PickBoomMove((s8*)D_821CF29C, D_821CF2A0);
        }
        if (r < 0) {
            BattleAi_ResetBattleStats(D_821CF29C + 0xC, *(u8**)D_821CF294 + move * 0x50 + 0x1C);
            r = move + 4;
        }
    } else if ((((u8*)D_821CF294)[0x368] == 3) && (BattleAi_GetHpPercent(D_821CF2A0) >= 31)) {
        r = BattleAi_ChooseRandomMove();
    } else {
        r = BattleAi_ChooseMove();
    }
    if ((r >= 0) && (r < 4) && (r < 4)) { // FAKE: repeated r < 4
        r = BattleAi_FindSlotWithPp(r);
    }
    D_821CF2A4 = r;
    return r;
}

extern s32 D_821CF2A4;
extern u8* D_821CF2A8;
extern u8* D_821CF2AC;
extern u8 D_8006B18F[];

/**
 * @unverified Name was previously used only by callers of this address; the definition was still func_.
 */
void BattleAi_RecordUsedMove(s32 arg0, s32 arg1, s32 arg2) {
    s32 i;
    s32 pp;
    s32 bonus;
    s32 move;

    if (D_821CF2A4 == 0xFEDC) {
        return;
    }
    move = D_821CF2AC[0x5A];
    if (move != 0) {
        for (i = 0; i < 4; i++) {
            if (((u8*)D_821CF2A0)[0x2B + i] == 0) {
                ((u8*)D_821CF2A0)[0x2B + i] = move;
                pp = D_8006B18F[D_821CF2AC[0x5A] * 6];
                bonus = (pp / 5 >= 8) ? 7 : pp / 5;
                pp += bonus * 3;
                ((u8*)D_821CF2A0)[0x3E + i] = pp - 1;
                break;
            }
            if ((move == ((u8*)D_821CF2A0)[0x2B + i]) && ((pp = ((u8*)D_821CF2A0)[0x3E + i]) != 0)) {
                ((u8*)D_821CF2A0)[0x3E + i] = pp - 1;
                break;
            }
        }
    }
    if ((arg2 < 2) && (D_821CF2A4 < 4) && ((D_821CF29C + D_821CF2A4)[0x2B] == LEECH_SEED)) {
        D_821CF29C[0x77] |= ((u8*)D_821CF2A0)[0x75];
    }
    if (arg2 < 2) {
        D_821CF29C[0x7E] = D_821CF29C[0x7D];
        D_821CF29C[0x7D] = D_821CF29C[0x7C];
        D_821CF29C[0x7C] = D_821CF29C[0x66];
    }
    if (!(D_821CF2AC[0x4E] & 8)) {
        if (arg2 == 0) {
            if (((D_821CF2A8[0x5A] != QUICK_ATTACK) || (D_821CF2AC[0x5A] == QUICK_ATTACK)) && ((D_821CF2A8[0x5A] == COUNTER) || (D_821CF2AC[0x5A] != COUNTER))) {
                D_821CF29C[0x76] |= ((u8*)D_821CF2A0)[0x75];
            }
        } else if (arg2 == 1) {
            if (((D_821CF2AC[0x5A] != QUICK_ATTACK) || (D_821CF2A8[0x5A] == QUICK_ATTACK)) && ((D_821CF2AC[0x5A] == COUNTER) || (D_821CF2A8[0x5A] != COUNTER))) {
                D_821CF29C[0x76] &= ~((u8*)D_821CF2A0)[0x75];
            }
        }
    }
}
