/* Fixed-layout split; original translation-unit boundaries remain unconfirmed. */
#include "global.h"
#include "moves.h"
#include "pokemon.h"
#include "pokemon_types.h"
#include "m2c_macros.h"
#include "battle.h"

extern ComBattler* D_821CF29C;
extern ComBattler* D_821CF2A0;
s32 BattleAi_GetBestDamage(ComBattler* arg0, ComBattler* arg1, s32 arg2);
s32 BattleAi_MovesFirst(ComBattler* arg0, ComBattler* arg1);
s32 BattleAi_CanUseMove(ComBattler* arg0, s32 arg1);
s32 BattleAi_EstimateDamage(BattleMonRuntime*, BattleMonRuntime*, u8);

/**
 * If the chosen move is Hyper Beam but it would not knock the opponent out, looks
 * for another damaging move that would, trying stronger move groups only in later
 * rounds. Returns the move slot to use.
 * Seen in play (2026-11-13) (tour of menus and a COM battle): ran in the battle opening and a
 * switch in battle.
 * @unverified Name and comment guessed from the code (COM AI pass).
 */
s32 BattleAi_ReplaceHyperBeam(s32 arg0) {
    s32 i;
    s32 tier;
    s32 best;
    s32 threshold;
    s32 v;
    u8 move;

    if (arg0 >= 0 && arg0 < 4 && BattleAi_GetBestDamage((u8*)D_821CF2A0, D_821CF29C, 0) < D_821CF29C->mon.hp && D_821CF29C->mon.moves[arg0] == HYPER_BEAM) {
        threshold = D_821CF2A0->mon.hp - BattleAi_EstimateDamage((s8*)&D_821CF29C->mon, (s8*)&D_821CF2A0->mon, 0x3F) * 9 / 10;
        best = -1;
        if (threshold > 0) {
            for (tier = 0; tier < 4; tier++) {
                for (i = 0; i < 4; i++) {
                    if (D_821CF29C->mon.moves[i] == 0) {
                        break;
                    }
                    if (BattleAi_MovesFirst((s8*)D_821CF29C, D_821CF2A0) != 0 || D_821CF29C->mon.moves[i] == QUICK_ATTACK) {
                        move = D_821CF29C->mon.moves[i];
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
                                v = BattleAi_EstimateDamage((s8*)&D_821CF29C->mon, (s8*)&D_821CF2A0->mon, move) * 9 / 10;
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
 */
s32 BattleAi_PickStrongestMove(s32 arg0) {
    s32 i;
    s32 best = -1;
    s32 best_idx = -1;
    s32 v;

    for (i = 0; i < 4; i++) {
        if (D_821CF29C->mon.moves[i] == 0) {
            break;
        }
        if (BattleAi_CanUseMove((s8*)D_821CF29C, D_821CF29C->mon.moves[i]) != 0) {
            v = BattleAi_EstimateDamage((s8*)&D_821CF29C->mon, (s8*)&D_821CF2A0->mon, D_821CF29C->mon.moves[i]);
            if (best < v) {
                best = v;
                best_idx = i;
            }
        }
    }
    best = best * 9 / 10;
    if ((D_821CF2A0->mon.hp != 0) && (arg0 < (best * 100) / D_821CF2A0->mon.hp)) {
        return best_idx;
    }
    return -1;
}

extern ComSide* D_821CF294;
s32 BattleAi_GetHpPercent(ComBattler*);
s32 BattleAi_CountUnfainted(ComSide*);
s32 BattleAi_FindUsableHealingMove(ComBattler*);
s32 BattleAi_OpponentCannotAct(ComBattler*, ComBattler*);
s32 BattleAi_PickSetupMove(ComBattler*);
s32 BattleAi_PickStatBoostMove(ComBattler*);
s32 BattleAi_PickHealingMove(ComBattler*);
s32 BattleAi_PickToxicOrLeechSeed(ComBattler*);
s32 BattleAi_PickStatLowerMove(ComBattler*, s8 *);
s32 BattleAi_IsMoveUseful(u8);
s32 BattleAi_PickParalysisMove(ComBattler*, ComBattler*);
s32 BattleAi_PickSleepMove(ComBattler*, ComBattler*);
s32 BattleAi_PickBoomMove(ComBattler*, ComBattler*);
/**
 * Normal move choice. In order:
 * - heal, but only when the COM moves first and slot 0 is not a move that knocks the opponent out
 *   (BattleAi_PickStrongestMove with the opponent's HP percent);
 * - set up when the opponent cannot act (BattleAi_OpponentCannotAct), otherwise Toxic or Leech Seed,
 *   paralysis, sleep, then a stat-lowering move;
 * - a move doing more than half the opponent's HP, a stat boost, Self-Destruct or Explosion when about
 *   to faint, or the strongest move;
 * then BattleAi_ReplaceHyperBeam, and finally the first move that is useful.
 * Each step was seen picking its move in game (Hypnosis, Tail Whip, Swords Dance, Explosion, Earthquake).
 */
s32 BattleAi_ChooseMove(void)
{
  s32 r;
  s32 i;
  s32 j;

  BattleAi_MovesFirst((s8 *) D_821CF29C, D_821CF2A0);
  r = -1;
  if ((BattleAi_MovesFirst((s8 *) D_821CF29C, D_821CF2A0) != 0) && (BattleAi_OpponentCannotAct((s8 *) D_821CF29C, D_821CF2A0) == 0) && (!(D_821CF2A0->mon.pendingStatusCondition & 0x27)) && (BattleAi_PickStrongestMove(BattleAi_GetHpPercent(D_821CF2A0)) != 0))
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
    if ((((BattleAi_MovesFirst((s8 *) D_821CF29C, D_821CF2A0) != 0) && (BattleAi_GetHpPercent((s8 *) D_821CF29C) < 0x14)) || ((BattleAi_MovesFirst((s8 *) D_821CF29C, D_821CF2A0) == 0) && ((D_821CF29C->mon.hp / 2) < ((BattleAi_GetBestDamage((u8 *) D_821CF2A0, D_821CF29C, 0) * 0x5A) / 100))) || ((BattleAi_FindUsableHealingMove((s8 *) D_821CF29C) == 0) && (BattleAi_GetHpPercent((s8 *) D_821CF29C) < 0x28))) && (BattleAi_CountUnfainted(D_821CF294) >= 2))
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
        if (D_821CF29C->mon.moves[i] == 0)
        {
          break;
        }
        if ((BattleAi_CanUseMove((s8 *) D_821CF29C, D_821CF29C->mon.moves[i]) != 0) && ((j != 0) || (BattleAi_IsMoveUseful(D_821CF29C->mon.moves[i]) != 0)))
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
 * Seen in play (2026-11-13) (tour of menus and a COM battle): ran in the battle opening and a
 * switch in battle.
 * @unverified Name and comment guessed from the code (COM AI pass).
 */
s32 BattleAi_FindSlotWithPp(s32 arg0) {
    s32 i;
    u8* base;
    u8* cur;
    u8* me;
    u8 v;

    base = (u8*)D_821CF29C;
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
extern ComSide D_821CF618;
extern ComSide D_821CF998;
extern ComSide* D_821CF298;
extern s32 D_821CF288;
void func_80058410(u8 *, u8 *, s32);
void BattleAi_CopyVisibleBattleState(s8 *, u8 *);
void BattleAi_ResetBattleStats(BattleMonRuntime*, BattleMon *);
s32 BattleAi_ChooseSwitch(void);
s32 BattleAi_ChooseRandomMove(void);
/**
 * Per-turn COM entry point. Copies both active Pokemon (arg0 own, arg1 opponent's
 * visible state) into the AI's model, updates its turn bookkeeping, then returns
 * a move slot (0..3) or 4 + a party slot to switch, also stored in D_821CF2A4.
 */
s32 BattleAi_ChooseTurnAction(u8* arg0, u8* arg1, s32 arg2, s32 arg3) {
    s32 move;
    s32 r;
    s32 one; // FAKE

    D_821CF294 = &D_821CF618;
    D_821CF298 = &D_821CF998;
    D_821CF29C = &D_821CF294->battlers[arg2];
    D_821CF2A0 = &D_821CF298->battlers[arg3];
    D_821CF2A8 = arg0;
    D_821CF2AC = arg1;
    func_80058410(arg0, (u8*)&D_821CF29C->mon, 0x64);
    if (D_821CF29C->prevHp != D_821CF29C->mon.hp) {
        if (D_821CF29C->mon.receivedCritFlag != 0) {
            D_821CF29C->damageTaken = (D_821CF29C->prevHp - D_821CF29C->mon.hp) / 2;
        } else {
            D_821CF29C->damageTaken = D_821CF29C->prevHp - D_821CF29C->mon.hp;
        }
        D_821CF29C->prevHp = D_821CF29C->mon.hp;
    }
    BattleAi_CopyVisibleBattleState((s8*)&D_821CF2A0->mon, arg1);
    if (D_821CF29C->mon.uniqueStatusFlags & 1) {
        D_821CF29C->rechargeTurns++;
    } else {
        D_821CF29C->rechargeTurns = 0;
    }
    if (D_821CF294->switchThreshold >= 0.5) {
        D_821CF294->switchThreshold -= D_DBL_82198A10;
    }
    if (arg3 != D_821CF294->lastOpponentSlot) {
        move = D_821CF294->lastOpponentSlot;
        if (move < D_821CF288) {
            BattleAi_ResetBattleStats(&D_821CF298->battlers[D_821CF294->lastOpponentSlot].mon, &D_821CF298->roster->pokemonPicked[move]);
        }
        D_821CF294->lastOpponentSlot = arg3;
        D_821CF294->opponentTurnsIn = 0;
    } else {
        D_821CF294->opponentTurnsIn++;
    }
    for (move = 0; move < D_821CF288; move++) {
        D_821CF294->battlers[move].unk_7B = arg0[move + 0x16];
        D_821CF298->battlers[move].unk_7B = arg1[move + 0x16];
    }

    move = BattleAi_ChooseSwitch();
    if ((move >= 0) && (D_821CF29C->partyBit != ((one = 1) << move))) { // FAKE: one
        r = -1;
        if ((D_821CF29C->mon.hp != 0) && (BattleAi_GetHpPercent((s8*)D_821CF29C) < 0x23) &&
            (BattleAi_CountUnfainted(D_821CF294) >= 2) && (BattleAi_PickBoomMove((s8*)D_821CF29C, D_821CF2A0) >= 0)) {
            r = BattleAi_PickBoomMove((s8*)D_821CF29C, D_821CF2A0);
        }
        if (r < 0) {
            BattleAi_ResetBattleStats(&D_821CF29C->mon, &D_821CF294->roster->pokemonPicked[move]);
            r = move + 4;
        }
    } else if ((D_821CF294->mode == 3) && (BattleAi_GetHpPercent(D_821CF2A0) >= 31)) {
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
 * Learns the opponent's chosen move once both sides have picked their actions
 * (called from Battle_StartTurn, before the moves run): the move goes into the
 * first empty move slot of the AI's opponent record with its maximum PP minus
 * one, or one PP is taken off a move already recorded. arg2 is 0 when the COM
 * acts first, 1 when it acts second and 2 for a move used later in the turn.
 * In game, after a Poison Sting the record held move 40 with 55 PP (35 + 3 PP Ups - 1).
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
            if (D_821CF2A0->mon.moves[i] == 0) {
                D_821CF2A0->mon.moves[i] = move;
                pp = D_8006B18F[D_821CF2AC[0x5A] * 6];
                bonus = (pp / 5 >= 8) ? 7 : pp / 5;
                pp += bonus * 3;
                D_821CF2A0->mon.pp[i] = pp - 1;
                break;
            }
            if ((move == D_821CF2A0->mon.moves[i]) && ((pp = D_821CF2A0->mon.pp[i]) != 0)) {
                D_821CF2A0->mon.pp[i] = pp - 1;
                break;
            }
        }
    }
    if ((arg2 < 2) && (D_821CF2A4 < 4) && (D_821CF29C->mon.moves[D_821CF2A4] == LEECH_SEED)) {
        D_821CF29C->leechSeededMask |= D_821CF2A0->partyBit;
    }
    if (arg2 < 2) {
        D_821CF29C->lastMoves[2] = D_821CF29C->lastMoves[1];
        D_821CF29C->lastMoves[1] = D_821CF29C->lastMoves[0];
        D_821CF29C->lastMoves[0] = D_821CF29C->mon.usedMove;
    }
    if (!(D_821CF2AC[0x4E] & 8)) {
        if (arg2 == 0) {
            if (((D_821CF2A8[0x5A] != QUICK_ATTACK) || (D_821CF2AC[0x5A] == QUICK_ATTACK)) && ((D_821CF2A8[0x5A] == COUNTER) || (D_821CF2AC[0x5A] != COUNTER))) {
                D_821CF29C->outspedMask |= D_821CF2A0->partyBit;
            }
        } else if (arg2 == 1) {
            if (((D_821CF2AC[0x5A] != QUICK_ATTACK) || (D_821CF2A8[0x5A] == QUICK_ATTACK)) && ((D_821CF2AC[0x5A] == COUNTER) || (D_821CF2A8[0x5A] != COUNTER))) {
                D_821CF29C->outspedMask &= ~D_821CF2A0->partyBit;
            }
        }
    }
}
