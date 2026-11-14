/* Fixed-layout split; original translation-unit boundaries remain unconfirmed. */
#include "global.h"
#include "moves.h"
#include "pokemon.h"
#include "pokemon_types.h"
#include "battle.h"
#include "asset_archive.h"
extern s32 pad_D_84002D10;
extern s32 pad_D_84002D1C;
extern u8 D_50002A0[];
extern u8 D_50003F0[];
extern u8 D_5000BA0[];
extern u8 D_5000C90[];
extern u8 D_50011D0[];
extern u8 D_5001680[];
extern u8 D_50017E8[];
extern char** sUiText;
extern char** sTrainerNameText;
extern BinArchive* sTrainerDataArchive;
extern BinArchive* sPortraitArchive;
extern BinArchive* sBackgroundArchive;
extern u8* sGymLeaderCastleTexture;
extern u8* sEliteFourTexture;
extern s16 sCurrentHoverNodeIndex;
#define CHAMPION 11
#define ELITE_4 10
#define ELITE_4_TO_GLC 9
#define GLC_TO_ELITE_4 8
#define GIOVANNI 7
extern s16 sSelectedMapNode;
extern s16 sCursorMoveTimer;
extern s16 sRoomDescriptionHeight;
extern s16 sEliteFourTransition;
#include "math.h"
#include "m2c_macros.h"
void func_82183BA8(void);
void func_82183D9C(void);
void func_82183DA4(void);
void func_82183DAC(void);
void func_82183DB4(void);
void func_82183DBC(void);
void func_82183DC4(void);
void func_82183E1C(void);
void func_821853EC(void);
void func_821853F4(void);
void func_821853FC(void);
void func_82185404(void);
extern s32 D_821CF2B0;
extern u32 D_821CF2B4;
extern ComSide* D_821CF298;
extern Move82184ADC D_8006B190[];
extern u8 D_8218AC50[];

/* The definition has no return statement, so the value left in v0 by its last
 * call comes back. Reading it as u16 here is what makes IDO keep a saved copy. */
u16 BattleCalc_EstimateDamage(s8*, s8*, u8);
/**
 * Expected damage of a move from attacker arg0 to defender arg1 (both battle
 * Pokemon records). Starts from BattleCalc_EstimateDamage's damage, returns 0 for moves the AI
 * never uses for damage (status moves, healing, Self-Destruct, Explosion; Dream
 * Eater unless the target sleeps), doubles multi-hit moves, adds 75% for
 * high-critical moves, reduces two-turn moves when slower or the target knows Fly
 * or Dig, uses half the target's HP for Super Fang, and zeroes Fissure against
 * Flying and the OHKO moves against Ghost.
 */
s32 BattleAi_EstimateDamage(BattleMonRuntime* arg0, BattleMonRuntime* arg1, u8 move) {
    s32 score;
    s32 power;

    power = BattleCalc_EstimateDamage(arg0, arg1, move);
    score = power;
    switch (move) {
        case DREAM_EATER:
            if (arg1->pendingStatusCondition & 7) {
                break;
            }
        case LEECH_SEED:
        case SLEEP_POWDER:
        case THUNDER_WAVE:
        case HYPNOSIS:
        case TELEPORT:
        case DOUBLE_TEAM:
        case RECOVER:
        case MINIMIZE:
        case CONFUSE_RAY:
        case REFLECT:
        case SELFDESTRUCT:
        case SOFTBOILED:
        case LOVELY_KISS:
        case EXPLOSION:
        case REST:
            return 0;
    }
    if ((power >= 6) && (arg1->statStages[5] >= 8)) {
        if (BattleAi_RandomPercent() >= (-arg1->statStages[5] * 10) + 0x8C) {
            return 1;
        }
    }
    switch (move) {
        case DOUBLESLAP:
        case COMET_PUNCH:
        case BIND:
        case DOUBLE_KICK:
        case FURY_ATTACK:
        case WRAP:
        case TWINEEDLE:
        case PIN_MISSILE:
        case FIRE_SPIN:
        case 0x80: /* Clamp; the CLAMP name is taken by the macro */
        case SPIKE_CANNON:
        case BARRAGE:
        case FURY_SWIPES:
        case BONEMERANG:
            score += score;
            break;
        case KARATE_CHOP:
        case RAZOR_LEAF:
        case CRABHAMMER:
        case SLASH:
            score += (score / 2) + (score / 4);
            break;
        case RAZOR_WIND:
        case SOLARBEAM:
        case SKULL_BASH:
        case SKY_ATTACK:
            if ((arg0->speed < arg1->speed) ||
                (BattleAi_FindByte((u8*)arg1 + 0x1F, 1, 4, FLY) != 0) ||
                (BattleAi_FindByte((u8*)arg1 + 0x1F, 1, 4, DIG) != 0)) {
                score = 10;
            }
            break;
        case SUPER_FANG:
            score = arg1->hp / 2;
            break;
        case FISSURE:
            if ((arg1->type1 == TYPE_FLYING) || (arg1->type2 == TYPE_FLYING)) {
                score = 0;
            }
            break;
        case GUILLOTINE:
        case HORN_DRILL:
            if ((arg1->type1 == TYPE_GHOST) || (arg1->type2 == TYPE_GHOST)) {
                score = 0;
            }
            break;
    }
    return score;
}

extern u8 D_80065CF8[];

/**
 * Tests bit `bit` of the species' learnset bitfield (0x17 bytes per species at
 * D_80065CF8), with a few species patched in by hand.
 * Not reached in play (2026-11-13): did not run in the 165-move battle sweep (each move used once,
 * from the command menu to the end of its turn) or in a tour of the menus and a COM battle.
 * @unverified Name and comment guessed from the code (COM AI pass).
 */
s32 BattleAi_SpeciesHasLearnsetBit(species, bit) s32 species; s32 bit; {
    s32 byte_index;
    s32 bits;

    if (species == 0) {
        return 0;
    }

    bits = D_80065CF8[species * 0x17 + bit / 8];
    switch (species) {
        case 6:
            if (bit / 8 == 6) {
                bits |= 8;
            }
            break;
        case 0xC:
        case 0x30:
        case 0x31:
            if (bit / 8 == 6) {
                bits |= 0x40;
            }
            break;
        case 0x32:
        case 0x33:
        case 0x8D:
            if (bit / 8 == 6) {
                bits |= 4;
            }
            break;
    }
    return (1 << (bit & 7)) & bits;
}

extern u8 D_821944CF[];
extern u32 D_821945C4[];
/**
 * Returns the move if the battler's species can learn it, otherwise 0.
 * D_821944CF maps a move to its learnset bit index.
 */
s32 BattleAi_SpeciesCanLearnMove(ComBattler* arg0, s32 arg1) {
    s32 v = 0;

    if (arg1 != 0) {
        v = D_821944CF[arg1];
        if ((v != 0) && (v < 0x38)) {
            if (BattleAi_SpeciesHasLearnsetBit(arg0->mon.species, v - 1, v, arg1) != 0) {
                v = arg1;
            } else {
                v = 0;
            }
        } else if (v >= 0x38) {
            if (D_821945C4[arg0->mon.species] & (1 << (v + 8))) {
                v = arg1;
            } else {
                v = 0;
            }
        }
    }
    return v;
}

s32 BattleAi_SpeciesCanLearnMove(ComBattler*, s32);

/**
 * Returns the move if the battler is known to have it with PP left, or if its
 * species could learn it.
 */
s32 BattleAi_MayKnowMove(ComBattler* arg0, s32 arg1) {
    s32 i;
    u8* slot;

    for (i = 0, slot = (u8*)arg0; i < 4; i++, slot++) {
        if (slot[0x2B] == 0) {
            break;
        }
        if ((arg1 == slot[0x2B]) && (slot[0x3E] != 0)) {
            return arg1;
        }
    }
    return BattleAi_SpeciesCanLearnMove(arg0, arg1);
}

s32 BattleAi_MayKnowMove(ComBattler* arg0, s32 arg1);
s32 BattleAi_EstimateDamage(BattleMonRuntime*, BattleMonRuntime*, u8);
extern u8 D_82194578[];
/**
 * Highest BattleAi_EstimateDamage that attacker arg0 can do to arg1. Uses the
 * attacker's moves when they are known (the party flag bit 2, or a full move
 * list); otherwise it considers every move in the D_82194578 list the species
 * could learn, with Self-Destruct and Explosion only when arg2 > 0.
 */
s32 BattleAi_GetBestDamage(ComBattler* arg0, ComBattler* arg1, s32 arg2)
{
  s32 best = 0;
  s32 i;
  s32 d;
  unsigned long move;
  if (!((*(*(*((u8 ***) arg0)))) & 2))
  {
    goto check;
  }
  slots:
  for (i = 0; i < 4; i++)
  {
    if (arg0->mon.moves[i] == 0)
    {
      break;
    }
    if (BattleAi_CanUseMove((s8 *) arg0, arg0->mon.moves[i]) != 0)
    {
      d = BattleAi_EstimateDamage(((s8 *) arg0) + 0xC, ((s8 *) arg1) + 0xC, arg0->mon.moves[i]);
      if (best < d)
      {
        best = d;
      }
    }
  }


  goto end;
  check:
  if (arg0->mon.moves[3] != 0)
  {
    goto slots;
  }

  for (i = 0; i < 78; i++)
  {
    move = D_82194578[i];
    if (((move != 0) && (((move != SELFDESTRUCT) && (move != EXPLOSION)) || (arg2 > 0))) && (BattleAi_MayKnowMove(arg0, move) != 0))
    {
      d = BattleAi_EstimateDamage(((s8 *) arg0) + 0xC, ((s8 *) arg1) + 0xC, move);
      if (best < d)
      {
        best = d;
      }
    }
  }

  end:
  return best;

}

/**
 * Clears the switch-out volatile state of a battle Pokemon (arg0, BattleMonRuntime
 * layout), resets its in-battle stats to the party Pokemon's stats (arg1, BattleMon
 * layout) and resets all eight stat stages to 7 (neutral).
 * Seen in play (2026-11-13) (tour of menus and a COM battle): ran in a switch in battle.
 * @unverified Name and comment guessed from the code (COM AI pass).
 */
void BattleAi_ResetBattleStats(BattleMonRuntime* arg0, BattleMon *arg1)
{
  s32 var_v0;
  s8 *var_v1;
  arg0->unk_4A = 0;
  arg0->unk_4B = 0;
  arg0->immobilizedReason = 0;
  arg0->volatileStatusFlags = 0;
  arg0->uniqueStatusFlags = 0;
  arg0->disabledMoveState = 0;
  arg0->disabledMove = 0;
  arg0->scaleResize = 0;
  var_v1 = (s8 *) arg0;
  var_v0 = 0;
  arg0->modifiedAttack = (u16) arg1->attack;
  arg0->modifiedDefense = (u16) arg1->defense;
  arg0->speed = (u16) arg1->speed;
  var_v1 = (s8 *) var_v1;
  arg0->modifiedSpecial = (u16) arg1->special;
  do
  {
    var_v0 += 4;
    *((s8 *) (((s8 *) var_v1) + 0x5D)) = 7;
    *((s8 *) (var_v1 + 0x5E)) = 7;
    *((s8 *) (var_v1 + 0x5F)) = 7;
    var_v1 += 4;
    *((s8 *) (((s8 *) var_v1) + 0x58)) = 7;
  }
  while (var_v0 != 8);
}

/**
 * Empty.
 */
void func_821853EC(void) {
}

/**
 * Empty.
 */
void func_821853F4(void) {
}

/**
 * Empty.
 */
void func_821853FC(void) {
}

/**
 * Empty.
 */
void func_82185404(void) {
}

/**
 * Returns 1 if battler arg0 is expected to move before arg1: either it has
 * already been seen to move first against it (outspedMask against its partyBit) or its
 * speed is higher.
 */
s32 BattleAi_MovesFirst(ComBattler* arg0, ComBattler* arg1)
{
  if (arg0->outspedMask & arg1->partyBit)
  {
    return 1;
  }
  if (((s32) (arg1->mon.speed)) < ((s32) (arg0->mon.speed)))
  {
    return 1;
  }
  return 0;
}

extern u8 D_8438B0C4[];
/**
 * Returns 1 if battler arg1 is held by a trapping state (byte 0x58 bit 0x40) and
 * arg0 moves first, so arg1 cannot act this turn.
 * Seen in play (2026-11-13) (tour of menus and a COM battle): ran in the battle opening and a
 * switch in battle.
 * @unverified Name and comment guessed from the code (COM AI pass).
 */
s32 BattleAi_OpponentCannotAct(ComBattler* arg0, ComBattler* arg1) {
    if ((arg1->mon.immobilizedReason & 0x40) && (BattleAi_MovesFirst(arg0, arg1) != 0)) {
        return 1;
    }
    return 0;
}

extern ComBattler* D_821CF2A0;

/**
 * COM AI check: returns 1 when bit 0x10 of byte 0x59 of the AI's opponent record
 * (D_821CF2A0) is clear.
 */
s32 func_82185494(void) {
    return (D_821CF2A0->mon.volatileStatusFlags & 0x10) == 0;
}

/**
 * Picks a move to use while the opponent cannot act: a stat boost
 * while that stat stage is below +2, Counter, Bide, Mirror Move or Splash, or
 * Substitute above half HP. Returns the move slot or -1.
 * Seen in play (2026-11-13) (unattended all-Metronome Free Battle with randomized teams, battle 1
 * turn 25): ran once on the COM side. Which condition led to it was not logged.
 * @unverified Name and comment guessed from the code (COM AI pass).
 */
s32 BattleAi_PickSetupMove(ComBattler* arg0) {
    s32 i;
    s32 t;

    for (i = 0; i < 4; i++) {
        if (arg0->mon.moves[i] == 0) {
            return -1;
        }
        if (BattleAi_CanUseMove((s8*)arg0, arg0->mon.moves[i]) != 0) {
            switch (arg0->mon.moves[i]) {
                case SWORDS_DANCE:
                case GROWTH:
                case MEDITATE:
                case AGILITY:
                case DOUBLE_TEAM:
                case HARDEN:
                case MINIMIZE:
                case WITHDRAW:
                case DEFENSE_CURL:
                case BARRIER:
                case AMNESIA:
                case ACID_ARMOR:
                case SHARPEN:
                    t = (D_8006B190[arg0->mon.moves[i] - 1].unk01 - 10) & 7;
                    if (arg0->mon.statStages[t] < 9) {
                        return i;
                    }
                    break;
                case COUNTER:
                case BIDE:
                case MIRROR_MOVE:
                case SPLASH:
                    return i;
                case SUBSTITUTE:
                    if (func_82185494() != 0 && BattleAi_GetHpPercent((s8*)arg0) >= 0x33) {
                        return i;
                    }
                    break;
            }
        }
    }
    return -1;
}

extern s32 D_821CF288;
/**
 * Sleep Clause check. Returns 0 if a Pokemon of this side is asleep and its byte
 * 0x7F (copied from the battle state each turn, possibly "slept from Rest") is
 * clear; when arg0 is the opponent's side, an asleep active opponent also blocks.
 * Returns 1 when another sleep move may be used.
 * Seen in play (2026-11-13) (tour of menus and a COM battle): ran in the battle opening and a
 * switch in battle.
 * @unverified Name and comment guessed from the code (COM AI pass).
 */
s32 BattleAi_SleepClauseAllows(ComSide *arg0)
{
  s32 i;
  int new_var; // FAKE: permuter temp
  if ((arg0 == D_821CF298) && (D_821CF2A0->mon.pendingStatusCondition & 7))
  {
    new_var = !D_821CF288;
    if ((new_var && (!D_821CF288)) && (!D_821CF288))
    {
    }
    return 0;
  }
  for (i = 0; i < D_821CF288; i++)
  {
    if (((arg0->battlers[i].mon.hp != 0) && (arg0->battlers[i].mon.pendingStatusCondition & 7)) && (arg0->battlers[i].unk_7B == 0))
    {
      return 0;
    }
  }

  return 1;
}

extern u8 D_82194824[];
extern u8 D_82194840[];
/**
 * Returns 1 if the battler can use Sing, Sleep Powder, Hypnosis, Lovely Kiss or
 * Spore, or (when its moves are unknown) its species is one that could learn a
 * sleep move (D_82194824, and D_82194840 from level 50).
 * Seen in play (2026-11-13) (tour of menus and a COM battle): ran in a switch in battle.
 * @unverified Name and comment guessed from the code (COM AI pass).
 */
s32 BattleAi_MayHaveSleepMove(ComBattler* arg0) {
    s32 i;

    for (i = 0; i < 4; i++) {
        if (arg0->mon.moves[i] == 0) {
            goto check;
        }
        if (BattleAi_CanUseMove((s8*)arg0, arg0->mon.moves[i]) != 0) {
            switch (arg0->mon.moves[i]) {
                case 0:
                    goto check;
                case SING:
                case SLEEP_POWDER:
                case HYPNOSIS:
                case LOVELY_KISS:
                case SPORE:
                    return 1;
            }
        }
    }
    return 0;
check:
    if (BattleAi_FindByte(D_82194824, 1, 0x19, arg0->species) != 0) {
        return 1;
    }
    if ((arg0->mon.level >= 50) && (BattleAi_FindByte(D_82194840, 1, 8, arg0->species) != 0)) {
        return 1;
    }
    return 0;
}

/**
 * Picks a stat-boosting move while that stat stage is below +6. Returns the move
 * slot or -1.
 */
s32 BattleAi_PickStatBoostMove(ComBattler* arg0) {
    s32 i;
    s32 t;

    for (i = 0; i < 4; i++) {
        if (arg0->mon.moves[i] == 0) {
            return -1;
        }
        if (BattleAi_CanUseMove((s8*)arg0, arg0->mon.moves[i]) != 0) {
            switch (arg0->mon.moves[i]) {
                case SWORDS_DANCE:
                case GROWTH:
                case MEDITATE:
                case AGILITY:
                case DOUBLE_TEAM:
                case HARDEN:
                case MINIMIZE:
                case WITHDRAW:
                case DEFENSE_CURL:
                case BARRIER:
                case AMNESIA:
                case ACID_ARMOR:
                case SHARPEN:
                    t = (D_8006B190[arg0->mon.moves[i] - 1].unk01 - 10) & 7;
                    if (arg0->mon.statStages[t] < 13) {
                        return i;
                    }
                    break;
            }
        }
    }
    return -1;
}

extern ComBattler* D_821CF29C;
/**
 * Picks Recover or Softboiled, or Rest unless Rest was one of the last two moves,
 * when the COM is below 40% HP. Never heals when the last move was a healing
 * move, or when the value at 0x72 is more than half the max HP. Returns the move
 * slot or -1.
 * Seen in play (2026-11-12): COM's Gengar at 20/ 72 HP with Recover in slot 3 got
 * slot 3 back, then ゲンのすけは じこさいせいを した！ and its HP rose to 56/ 72.
 * 0x72 is not the damage this Pokémon took last turn: Gengar had not been hit, yet
 * 0x72 held 52 (left over after a super-effective Poison Sting knocked out the
 * Pinsir before it) and blocked the heal until it was cleared.
 */
s32 BattleAi_PickHealingMove(ComBattler* arg0)
{
  s32 i;
  if ((arg0->mon.uniqueStatusFlags & 1) || (((arg0->mon.maxHp) / 2) < (arg0->damageTaken)))
  {
    return -1;
  }
  switch (arg0->lastMoves[0])
  {
    case RECOVER:

    case SOFTBOILED:

    case REST:
      return -1;

  }

  if (BattleAi_GetHpPercent((s8 *) D_821CF29C) < 0x28)
  {
    for (i = 0; i < 4; i++)
    {
      if (arg0->mon.moves[i] == 0)
      {
        return -1;
      }
      if (BattleAi_CanUseMove((s8 *) arg0, arg0->mon.moves[i]) != 0)
      {
        switch (arg0->mon.moves[i])
        {
          case RECOVER:

          case SOFTBOILED:
            return i;

          case REST:
            if ((arg0->lastMoves[2] != REST) && (arg0->lastMoves[1] != REST))
          {
            return i;
            break;
          }

        }

      }
    }

  }
  return -1;
}

extern ComBattler* D_821CF29C;
s32 BattleAi_PickStrongestMove(s32);
/**
 * Picks Toxic against a healthy non-Poison opponent, or Leech Seed against a
 * poisoned non-Grass opponent that is not seeded yet. Returns the move slot or -1.
 */
s32 BattleAi_PickToxicOrLeechSeed(ComBattler* arg0) {
    s32 i;
    s32 r;

    if (func_82185494() == 0) {
        return -1;
    }
    if (D_821CF29C->lastMoves[0] == TOXIC) {
        return -1;
    }
    r = BattleAi_PickStrongestMove((BattleAi_GetHpPercent(D_821CF2A0) * 5) / 4);
    if (r >= 0) {
        return r;
    }
    if ((D_821CF2A0->mon.pendingStatusCondition == 0) && (BattleAi_HasType(D_821CF2A0, TYPE_POISON) == 0)) {
        for (i = 0; i < 4; i++) {
            if (arg0->mon.moves[i] == 0) {
                break;
            }
            if ((BattleAi_CanUseMove((s8 *)arg0, arg0->mon.moves[i]) != 0) && (arg0->mon.moves[i] == TOXIC)) {
                return i;
            }
        }
    }
    if (!(D_821CF2A0->mon.pendingStatusCondition & 8)) {
        return -1;
    }
    if ((D_821CF29C->leechSeededMask & D_821CF2A0->partyBit) || (BattleAi_HasType(D_821CF2A0, TYPE_GRASS) != 0)) {
        return -1;
    }
    {
        for (i = 0; i < 4; i++) {
            if (arg0->mon.moves[i] == 0) {
                break;
            }
            if ((BattleAi_CanUseMove((s8 *)arg0, arg0->mon.moves[i]) != 0) && (arg0->mon.moves[i] == LEECH_SEED)) {
                return i;
            }
        }
    }
    return -1;
}

extern u8 D_8006B18B[];
/**
 * Picks a stat-lowering move (Sand Attack, Tail Whip, Leer, Growl, String Shot,
 * Screech, Smokescreen, Kinesis, Flash) while the opponent's stage for that stat
 * is at least -1 and it was not the last move used. Returns the move slot or -1.
 */
s32 BattleAi_PickStatLowerMove(ComBattler* arg0, s32 arg1) {
    s32 i;
    s32 t;
    s32 pad; // FAKE: stack padding
    u8 *p;

    if (func_82185494() != 0) {
        i = 0;
        p = arg0;
        if (!(D_821CF2A0->mon.volatileStatusFlags & 2)) {
        loop:
            if (p[0x2B] == 0) goto end;
            if (BattleAi_CanUseMove((s8 *)arg0, p[0x2B]) != 0) {
                switch (p[0x2B]) {
                    case SAND_ATTACK:
                    case TAIL_WHIP:
                    case LEER:
                    case GROWL:
                    case STRING_SHOT:
                    case SCREECH:
                    case SMOKESCREEN:
                    case KINESIS:
                    case FLASH:
                        t = D_8006B18B[p[0x2B] * 6];
                        if (t >= 0x44) {
                            t -= 0x44;
                        } else {
                            t -= 0x12;
                            if (t >= 8) {
                                t -= 0x28;
                            }
                        }
                        t &= 7;
                        if ((D_821CF2A0->mon.statStages[t] >= 6) && (arg0->lastMoves[0] != p[0x2B])) {
                            return i;
                        }
                        break;
                }
            }
            i++;
            p++;
            if (i != 4) goto loop;
        }
    }
end:
    return -1;
}

/**
 * Returns 0 if a move would do nothing now: no damage by type, a status the
 * target already has or is immune to, a stat stage already at its limit, Haze
 * with nothing to reset, and similar checks keyed on the move's effect id.
 * Seen in play (2026-11-13) ran during the opening of a COM Free Battle, before the first command
 * menu.
 * @unverified Name and comment guessed from the code (COM AI pass).
 */
s32 BattleAi_IsMoveUseful(s32 move) {
    s32 v1;
    s32 i;

    if (D_8006B190[move - 1].power != 0) {
        if (BattleAi_GetTypeMultiplier((s8 *)D_821CF29C, D_821CF2A0, move) == 0) {
            fail:
            return 0;
        }
    }
    switch (D_8006B190[move - 1].unk01) {
        case 28:
            goto fail;
        case 66:
            if (func_82185494() == 0) {
                goto fail;
            }
            if (BattleAi_HasType(D_821CF2A0, TYPE_POISON) != 0) {
                goto fail;
            }
            if (D_821CF2A0->mon.pendingStatusCondition != 0) {
                goto fail;
            }
            if (BattleAi_OpponentCannotAct((s8 *)D_821CF29C, D_821CF2A0) == 0) {
                break;
            }
            return 0;
        case 3:
            if (func_82185494() == 0) {
                goto fail;
            }
            if (BattleAi_OpponentCannotAct((s8 *)D_821CF29C, D_821CF2A0) != 0) {
                goto fail;
            }
            /* fallthrough */
        case 7:
        case 24:
        case 82:
            if (BattleAi_OpponentCannotAct((s8 *)D_821CF29C, D_821CF2A0) == 0) {
                break;
            }
            return 0;
        case 4:
        case 5:
        case 6:
        case 34:
        case 35:
        case 36:
            if (func_82185494() == 0) {
                goto fail;
            }
            if (D_821CF2A0->mon.pendingStatusCondition != 0) {
                goto fail;
            }
            if (BattleAi_HasType(D_821CF2A0, D_8006B190[move - 1].type) == 0) {
                break;
            }
            return 0;
        case 8:
            if ((D_821CF2A0->mon.pendingStatusCondition & 7) == 0) {
                goto fail;
            }
            if (func_82185494() == 0) {
                goto fail;
            }
            if (BattleAi_OpponentCannotAct((s8 *)D_821CF29C, D_821CF2A0) == 0) {
                break;
            }
            return 0;
        case 10: case 11: case 12: case 13: case 14: case 15:
        case 50: case 51: case 52: case 53: case 54: case 55:
            v1 = D_8006B190[move - 1].unk01 - 10;
            v1 &= 7;
            if (D_821CF2A0->mon.statStages[v1] != 13) {
                break;
            }
            return 0;
        case 18: case 19: case 20: case 21: case 22: case 23:
        case 58: case 59: case 60: case 61: case 62: case 63:
            if (func_82185494() == 0) {
                goto fail;
            }
            if (D_821CF2A0->mon.volatileStatusFlags & 2) {
                goto fail;
            }
            v1 = D_8006B190[move - 1].unk01;
            if (v1 >= 0x44) {
                v1 -= 0x44;
            } else {
                if (BattleAi_OpponentCannotAct((s8 *)D_821CF29C, D_821CF2A0) != 0) {
                    goto fail;
                }
                v1 -= 0x12;
                if (v1 >= 8) {
                    v1 -= 0x28;
                }
            }
            v1 &= 7;
            if (D_821CF2A0->mon.statStages[v1] != 1) {
                break;
            }
            return 0;
        case 25:
            for (i = 0; i < 8; i++) {
                if (D_821CF29C->mon.statStages[i] != 7) {
                    goto done;
                }
                if (D_821CF2A0->mon.statStages[i] != 7) {
                    goto done;
                }
            }
            if (D_821CF29C->mon.pendingStatusCondition != 0) break;
            if (D_821CF2A0->mon.pendingStatusCondition != 0) break;
            if (D_821CF29C->mon.disabledMove != 0) break;
            if (D_821CF2A0->mon.disabledMove != 0) break;
            if (D_821CF29C->mon.immobilizedReason != 0) break;
            if (D_821CF29C->mon.volatileStatusFlags != 0) break;
            if (D_821CF29C->mon.uniqueStatusFlags != 0) break;
            if (D_821CF2A0->mon.immobilizedReason != 0) break;
            if (D_821CF2A0->mon.volatileStatusFlags != 0) break;
            if (D_821CF2A0->mon.uniqueStatusFlags != 0) break;
            if (D_821CF29C->mon.scaleResize != 0) break;
            if (D_821CF2A0->mon.scaleResize != 0) break;
            goto fail;
        case 29: case 30: case 44: case 77:
            if (!(D_821CF2A0->mon.immobilizedReason & 4)) {
                break;
            }
            return 0;
        case 31: case 37:
            if (func_82185494() != 0) {
                break;
            }
            return 0;
        case 32:
            if (D_821CF2A0->mon.pendingStatusCondition != 0) {
                goto fail;
            }
            if (BattleAi_OpponentCannotAct((s8 *)D_821CF29C, D_821CF2A0) != 0) {
                goto fail;
            }
            if (BattleAi_SleepClauseAllows(D_821CF298) != 0) {
                break;
            }
            return 0;
        case 38:
            if (BattleAi_MovesFirst((s8 *)D_821CF29C, D_821CF2A0) != 0) {
                break;
            }
            return 0;
        case 42:
            if (!(D_821CF29C->mon.immobilizedReason & 0x20)) {
                break;
            }
            return 0;
        case 46:
            if (!(D_821CF29C->mon.volatileStatusFlags & 2)) {
                break;
            }
            return 0;
        case 47:
            if (!(D_821CF29C->mon.volatileStatusFlags & 4)) {
                break;
            }
            return 0;
        case 49:
            if (func_82185494() == 0) {
                goto fail;
            }
            if (D_821CF2A0->mon.immobilizedReason & 0x80) {
                goto fail;
            }
            if (BattleAi_OpponentCannotAct((s8 *)D_821CF29C, D_821CF2A0) == 0) {
                break;
            }
            return 0;
        case 56:
            if (D_821CF29C->mon.hp != D_821CF29C->mon.maxHp) {
                break;
            }
            return 0;
        case 57:
            if (BattleAi_OpponentCannotAct((s8 *)D_821CF29C, D_821CF2A0) != 0) {
                goto fail;
            }
            if (func_82185494() != 0) {
                break;
            }
            return 0;
        case 64:
            if (!(D_821CF29C->mon.uniqueStatusFlags & 2)) {
                break;
            }
            return 0;
        case 65:
            if (!(D_821CF29C->mon.uniqueStatusFlags & 4)) {
                break;
            }
            return 0;
        case 67:
            if (D_821CF2A0->mon.pendingStatusCondition != 0) {
                goto fail;
            }
            if (D_8006B190[move - 1].type == 0x17) {
                if (BattleAi_HasType(D_821CF2A0, TYPE_GROUND) != 0) {
                    goto fail;
                }
            }
            if (BattleAi_OpponentCannotAct((s8 *)D_821CF29C, D_821CF2A0) == 0) {
                break;
            }
            return 0;
        case 79:
            if (func_82185494() == 0) {
                goto fail;
            }
            if (D_821CF29C->mon.hp >= (D_821CF29C->mon.maxHp >> 2)) {
                break;
            }
            return 0;
        case 84:
            if (BattleAi_OpponentCannotAct((s8 *)D_821CF29C, D_821CF2A0) != 0) {
                goto fail;
            }
            if (BattleAi_HasType(D_821CF2A0, TYPE_GRASS) != 0) {
                goto fail;
            }
            if (!(D_821CF2A0->mon.volatileStatusFlags & 0x80)) {
                break;
            }
            return 0;
        case 86:
            if (BattleAi_OpponentCannotAct((s8 *)D_821CF29C, D_821CF2A0) != 0) {
                goto fail;
            }
            if (D_821CF2A0->mon.disabledMoveState != 0) {
                goto fail;
            }
            break;
        case 0:
        default:
            break;
    }
done:
    return move;
}

extern ComBattler* D_821CF29C;
/**
 * Picks Thunder Wave (not against Ground types), Stun Spore or Glare against a
 * healthy opponent while both sides are above 30% HP. Returns the move slot or -1.
 */
s32 BattleAi_PickParalysisMove(ComBattler* arg0, ComBattler* arg1) {
    s32 i;

    if ((arg1->mon.pendingStatusCondition != 0) || (BattleAi_OpponentCannotAct(D_821CF29C, D_821CF2A0) != 0) || (BattleAi_GetHpPercent(D_821CF2A0) < 30) ||
        (BattleAi_GetHpPercent((s8*)D_821CF29C) < 0x1E)) {
        return -1;
    }
    for (i = 0; i < 4; i++) {
        if (arg0->mon.moves[i] == 0) {
            return -1;
        }
        if (BattleAi_CanUseMove((s8*)arg0, arg0->mon.moves[i]) != 0) {
            switch (arg0->mon.moves[i]) {
                case THUNDER_WAVE:
                    if (BattleAi_HasType((s8*)arg1, TYPE_GROUND) != 0) {
                        return -1;
                    }
                case STUN_SPORE:
                case GLARE:
                    return i;
            }
        }
    }
    return -1;
}

s32 BattleAi_SleepClauseAllows();
/**
 * Picks a sleep move against a healthy opponent when Sleep Clause allows it and
 * the last move was not already a sleep move. Returns the move slot or -1.
 */
s32 BattleAi_PickSleepMove(ComBattler* arg0, ComBattler* arg1) {
    s32 i;

    if ((arg1->mon.pendingStatusCondition != 0) || (BattleAi_OpponentCannotAct(D_821CF29C, D_821CF2A0) != 0) || (BattleAi_SleepClauseAllows(D_821CF298) == 0) ||
        (BattleAi_GetHpPercent(D_821CF2A0) < 30) || (BattleAi_GetHpPercent((s8*)D_821CF29C) < 0x1E)) {
        return -1;
    }
    switch (arg0->lastMoves[0]) {
        case SING:
        case SLEEP_POWDER:
        case HYPNOSIS:
        case LOVELY_KISS:
        case SPORE:
            return -1;
    }
    for (i = 0; i < 4; i++) {
        if (arg0->mon.moves[i] == 0) {
            return -1;
        }
        if (BattleAi_CanUseMove((s8*)arg0, arg0->mon.moves[i]) != 0) {
            switch (arg0->mon.moves[i]) {
                case SING:
                case SLEEP_POWDER:
                case HYPNOSIS:
                case LOVELY_KISS:
                    if (arg1->mon.statStages[5] < 9) {
                        return i;
                    }
                    break;
                case SPORE:
                    return i;
            }
        }
    }
    return -1;
}

/**
 * Picks a boom move (Self-Destruct or Explosion) unless the opponent cannot act.
 * Returns the move slot or -1.
 */
s32 BattleAi_PickBoomMove(ComBattler* arg0, ComBattler* arg1) {
    s32 i;

    if (BattleAi_OpponentCannotAct(arg0, arg1) != 0) {
        return -1;
    }
    for (i = 0; i < 4; i++) {
        if (arg0->mon.moves[i] == 0) {
            break;
        }
        if (BattleAi_CanUseMove((s8*)arg0, arg0->mon.moves[i]) != 0) {
            switch (arg0->mon.moves[i]) {
                case SELFDESTRUCT:
                case EXPLOSION:
                    return i;
            }
        }
    }
    return -1;
}

extern u8 D_821CF280[];
extern u8 D_821CF281;
extern ComSide* D_821CF294;

extern ComSide* D_821CF294;
extern u8 D_821CF280[];
extern u8 D_821CF281;

/**
 * Pick bonus for one COM trainer (id 0x6299) that wants at most one of Venusaur,
 * Chansey and Jynx: returns 10000 in the first pick round (arg0 == 0), and in
 * later rounds 10000 only if none of the Pokemon picked so far (D_821CF280,
 * D_821CF281) is one of the three; 0 otherwise.
 * Not reached in play (2026-11-13): no move in the 165-move battle sweep called it (each move used
 * once, from the command menu to the end of its turn).
 * @unverified Name and comment guessed from the code (COM AI pass).
 */
s32 BattleAi_NoVenusaurChanseyJynxPicked(s32 arg0) {
    switch (arg0) {
        case 2:
            if ((D_821CF294->battlers[D_821CF281].mon.species == VENUSAUR) || (D_821CF294->battlers[D_821CF281].mon.species == CHANSEY) || (D_821CF294->battlers[D_821CF281].mon.species == JYNX)) {
                return 0;
            }
        case 1:
            if ((D_821CF294->battlers[D_821CF280[0]].mon.species == VENUSAUR) || (D_821CF294->battlers[D_821CF280[0]].mon.species == CHANSEY) || (D_821CF294->battlers[D_821CF280[0]].mon.species == JYNX)) {
                return 0;
            }
        case 0:
            return 10000;
        default:
            return 0;
    }
}

/**
 * Copies a zero-terminated list of up to four moves into a four-byte array,
 * padding with zeros.
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Transform.
 */
void BattleAi_CopyMoveList(u8* arg0, u8* arg1) {
    s32 i;
    u8 c;

    for (i = 0; i < 4; i++) {
        c = *arg0;
        if (c == 0) {
            *arg1 = 0;
            arg1++;
        } else {
            *arg1 = c;
            arg1++;
            arg0++;
        }
    }
}

M2C_UNK func_80058410(s8*, s8*, M2C_UNK);

/**
 * Fills a battle Pokemon record (BattleMonRuntime layout) from a party Pokemon
 * (BattleMon layout): species, HP, status, types, moves, DVs, level, max HP,
 * stats and PP.
 */
void BattleAi_LoadBattlerFromPartyMon(BattleMonRuntime* arg0, BattleMon* arg1) {
    arg0->species = arg1->species.id;
    arg0->hp = arg1->hp;
    arg0->rosterIndex = arg1->boxLevel;
    arg0->pendingStatusCondition = arg1->statusCondition;
    arg0->type1 = arg1->type1;
    arg0->type2 = arg1->type2;
    BattleAi_CopyMoveList(arg1->moves, arg0->moves);
    arg0->dvs = arg1->dvs;
    arg0->level = arg1->level;
    arg0->maxHp = arg1->maxHp;
    arg0->modifiedAttack = arg1->attack;
    arg0->modifiedDefense = arg1->defense;
    arg0->speed = arg1->speed;
    arg0->modifiedSpecial = arg1->special;
    func_80058410(arg1->pp, arg0->pp, 4);
}

typedef struct BaseStats821868E8 { u8 species; u8 hp; u8 atk; u8 def; u8 spd; u8 spc; u8 type1; u8 type2; char unk08[0xF]; } BaseStats821868E8;
extern u8 D_80065D00[];
s32 BattleAi_CalcDefense(s32, s32);
s32 BattleAi_CalcSpeed(s32, s32);
s32 BattleAi_CalcSpecial(s32, s32);
/**
 * Fills a battle Pokemon record from base stats when the real party data is
 * hidden: species, HP and max HP, types, DVs 0x7777, level and stats computed with
 * BattleAi_CalcStat.
 */
void BattleAi_LoadBattlerFromSpecies(BattleMonRuntime* arg0, s32 species, s32 level) {
    BaseStats821868E8* stats;

    if (species != 0 && species < 0x98) {
        arg0->species = species;
        stats = &((BaseStats821868E8*)D_80065D00)[species - 1];
        arg0->hp = arg0->maxHp = BattleAi_CalcMaxHp(stats->hp, level);
        arg0->type1 = stats->type1;
        arg0->type2 = stats->type2;
        arg0->dvs = 0x7777;
        arg0->level = level;
        arg0->modifiedAttack = BattleAi_CalcAttack(stats->atk, level);
        arg0->modifiedDefense = BattleAi_CalcDefense(stats->def, level);
        arg0->speed = BattleAi_CalcSpeed(stats->spd, level);
        arg0->modifiedSpecial = BattleAi_CalcSpecial(stats->spc, level);
    }
}

M2C_UNK func_80058410(s8 *, s8 *, M2C_UNK);     /* extern */
extern ComBattler* D_821CF2A0;
// FAKE: decomp slop. Raw pointer-offset casts stand in for struct fields.
/**
 * Copies what the COM can see of the opponent's battle Pokemon arg1 into the AI's
 * record arg0: HP, status, last move, volatile state and stat stages. Moves and PP
 * are copied in full only when the opponent's flag bit 3 (0x4E) is set; otherwise
 * only the move just used is recorded.
 * Seen in play (2026-11-12): after two turns, COM's record of 1P's Nidoqueen held HP 44 (the HUD
 * showed 44/ 69) and only the two moves Nidoqueen had used, Poison Sting and Tail Whip, out of its
 * four.
 */
void BattleAi_CopyVisibleBattleState(BattleMonRuntime* arg0, BattleMonRuntime* arg1)
{
  long temp_v1;
  u8 *new_var; // FAKE: permuter temp
  arg0->maxHp = (u16) (arg1->maxHp);
  arg0->hp = (u16) (arg1->hp);
  arg0->pendingStatusCondition = (u8) (arg1->pendingStatusCondition);
  func_80058410(&arg1->moveCache, &arg0->moveCache, 6);
  arg0->unk_4A = (u8) (arg1->unk_4A);
  arg0->unk_4B = (u8) (arg1->unk_4B);
  arg0->immobilizedReason = (u8) (arg1->immobilizedReason);
  arg0->volatileStatusFlags = (u8) (arg1->volatileStatusFlags);
  arg0->uniqueStatusFlags = (u8) (arg1->uniqueStatusFlags);
  arg0->effectCounter = (u16) (arg1->effectCounter);
  arg0->scaleResize = (u8) (*(new_var = (u8 *) (((s8 *) arg1) + 0x56)));
  arg0->disabledMove = (u8) (arg1->disabledMove);
  arg0->lastMove = (u8) (arg1->lastMove);
  arg0->substituteHp = (u8) (arg1->substituteHp);
  arg0->usedMove = (u8) (arg1->usedMove);
  arg0->receivedCritFlag = (u8) (arg1->receivedCritFlag);
  func_80058410(arg1->statStages, arg0->statStages, 8);
  if ((arg1->uniqueStatusFlags) & 8)
  {
    BattleAi_CopyMoveList(arg1->moves, arg0->moves);
    func_80058410(arg1->pp, arg0->pp, 4);
    return;
  }
  temp_v1 = D_821CF2A0->moveCount;
  if (((s32) temp_v1) < 4)
  {
    arg0->moves[temp_v1] = arg1->moves[temp_v1];
    arg0->pp[D_821CF2A0->moveCount] = D_821CF2A0->unk_79;
  }
}

void func_8004FD20(void*, s32);

/**
 * Initializes one side of the AI's model from a party: links each battler to the
 * side, sets its party bit, loads it from the real data (party flag bit 1) or
 * from base stats, and counts its moves (stopping at an empty slot or Mimic). arg2 is the AI
 * mode byte; mode 2 and up raises the switch threshold to 10.
 */
void BattleAi_InitSide(ComSide *arg0, TeamRoster *arg1, s32 arg2)
{
  s32 i;
  s32 j;
  u8 species;
  u8 level;
  arg0->roster = arg1;
  arg0->mode = arg2;
  arg0->lastOpponentSlot = 0xFF;
  arg0->unk_36B = 0xFF;
  arg0->switchThreshold = 0.5f;
  if (arg2 >= 2)
  {
    arg0->switchThreshold = 10.0f;
  }
  for (i = 0; i < 6; i++)
  {
    func_8004FD20(&arg0->battlers[i], sizeof(ComBattler));
    arg0->battlers[i].partyBit = 1 << i;
    arg0->battlers[i].side = arg0;
    arg0->battlers[i].species = arg1->pokemonPicked[i].species.id;
    if (i < arg1->rosterInfo->numberOfPokemonCanBePicked)
    {
      species = arg1->pokemonPicked[i].species.id;
      if (((species != 0) && (arg1->pokemonPicked[i].hp != 0)) && (arg1->pokemonPicked[i].maxHp != 0))
      {
        level = arg1->pokemonPicked[i].level;
        if (level != 0)
        {
          j = 0; // FAKE: permuter; early init of the move counter
          level = arg1->pokemonPicked[i].level; // FAKE: permuter; redundant reload of level
          if (arg1->isHuman & 2)
          {
            BattleAi_LoadBattlerFromPartyMon(&arg0->battlers[i].mon, &arg1->pokemonPicked[i]);
            arg0->battlers[i].prevHp = arg0->battlers[i].mon.hp;
          }
          else
          {
            BattleAi_LoadBattlerFromSpecies(&arg0->battlers[i].mon, arg1->pokemonPicked[i].species.id, level);
          }
          for (j = 0; j < 4; j++)
          {
            if ((arg1->pokemonPicked[i].moves[j] == 0) || (arg1->pokemonPicked[i].moves[j] == MIMIC))
            {
              break;
            }
          }

        }
      }
    }
    arg0->battlers[i].moveCount = j;
    arg0->battlers[i].unk_79 = 0x10;
  }

}

extern u8 D_82194848[];
/**
 * Scores a candidate pick against one opponent Pokemon: large bonuses for being
 * unfainted, not frozen, not recharging and not asleep, smaller ones for a healing
 * move, Ice or Poison type, higher speed, and the type-weighted accuracy of its
 * damaging moves.
 * Seen in play (2026-11-13) (Free Battle, COM team selection after the order screen): called from
 * BattleAi_PickNextPokemon once per opponent Pokémon for each COM candidate.
 * @unverified Name and comment guessed from the code (COM AI pass).
 */
void BattleAi_AddMatchupPickScore(ComBattler* arg0, ComBattler* arg1) {
    s32 score;
    s32 i;
    s32 acc;

    switch (arg0->mon.species) {
        default:
            score = 0;
            break;
        case 0x84:
            score = 0;
            break;
        case 0x79:
            score = 0;
            break;
    }
    if (arg0->mon.hp != 0) {
        score = 32768;
    }
    if (!(arg0->mon.pendingStatusCondition & 0x20)) {
        score += 16384;
    }
    if (!(arg0->mon.uniqueStatusFlags & 1) || (arg0->rechargeTurns < 3)) {
        score += 8192;
    }
    if (!(arg0->mon.pendingStatusCondition & 7)) {
        score += 4096;
    }
    if (BattleAi_FindUsableHealingMove(arg0) != 0) {
        score += 512;
    }
    if ((BattleAi_HasType((s8 *)arg0, TYPE_ICE) != 0) || (BattleAi_HasType((s8 *)arg0, TYPE_POISON) != 0)) {
        score += 512;
    }
    if (arg1->mon.speed < arg0->mon.speed) {
        score += 768;
    }
    for (i = 0; i < 4; i++) {
        if (arg0->mon.moves[i] == 0) {
            break;
        }
        if ((BattleAi_CanUseMove((s8 *)arg0, arg0->mon.moves[i]) != 0) && (BattleAi_FindByte(D_82194848, 1, 0x2B, arg0->mon.moves[i]) != 0)) {
            acc = (D_8006B190[arg0->mon.moves[i]].unk04 * D_8006B190[arg0->mon.moves[i]].unk04) / 650;
            score += (((BattleAi_GetTypeMultiplier((s8 *)arg0, (s8 *)arg1, arg0->mon.moves[i]) * 8) / 100) * acc) / 100;
        }
    }
    arg0->pickScore += score;
}

/**
 * Level rule for the team picks: the levels of the three Pokemon must add up to
 * 150..155 (Nintendo Cup '97 rules). arg0 is the pick round.
 * Not reached in play (2026-11-13): no move in the 165-move battle sweep called it (each move used
 * once, from the command menu to the end of its turn).
 * @unverified Name and comment guessed from the code (COM AI pass).
 */
s32 BattleAi_LevelSumAllowed(s32 arg0, s32 arg1) {
    s32 i;
    s32 sum;

    if ((arg0 == 0) || (arg0 >= 3)) {
        return 1;
    }
    if (arg0 == 1) {
        for (i = 0; i < 6; i++) {
            if ((i != D_821CF280[0]) && (i != arg1)) {
                sum = D_821CF294->battlers[D_821CF280[0]].mon.level + D_821CF294->battlers[i].mon.level + D_821CF294->battlers[arg1].mon.level;
                if ((sum >= 150) && (sum < 156)) {
                    return 1;
                }
            }
        }
        return 0;
    }
    sum = D_821CF294->battlers[D_821CF280[0]].mon.level + D_821CF294->battlers[D_821CF280[1]].mon.level + D_821CF294->battlers[arg1].mon.level;
    if ((sum >= 150) && (sum < 156)) {
        return 1;
    }
    return 0;
}

extern ComSide* D_821CF294;
s32 BattleAi_LevelSumAllowed(s32, s32);

/**
 * Returns 1 if picking party slot arg2 in round arg1 keeps the team legal.
 * Seen in play (2026-11-13) (Free Battle, COM team selection): called as IsPickAllowed(0, 0, slot)
 * for slots 0, 1 and 2 and returned 1 each time; Free Battle has no level-sum rule, so
 * BattleAi_LevelSumAllowed did not run. Round 2 of the tournament (vs かじばどろぼう) made the same
 * three calls and returned 1, again without BattleAi_LevelSumAllowed (side byte +0x368 nonzero).
 * @unverified Name and comment guessed from the code (COM AI pass).
 */
s32 BattleAi_IsPickAllowed(s32 arg0, s32 arg1, s32 arg2) {
    if ((D_821CF294->mode != 0) || (arg0 != 0)) {
        return 1;
    }
    if (BattleAi_LevelSumAllowed(arg1, arg2) == 0) {
        return 0;
    } else {
        return 1;
    }
    return 1;
}

void BattleAi_AddTrainerPickScore(ComBattler*, s32);
/**
 * Scores every unfainted, unpicked (arg1 == 0) or picked (arg1 != 0) Pokemon of
 * the COM side and returns the best legal one, marking it as picked. arg0 is the
 * opponent battler to score against, or NULL for the whole opposing team.
 */
s32 BattleAi_PickNextPokemon(u8 *arg0, s32 arg1, s32 arg2, s32 arg3)
{
  s32 i;
  s32 j;
  s32 best;
  s32 best_score;

  for (i = 0; i < 6; i++)
  {
    D_821CF294->battlers[i].pickScore = -1;
    if ((D_821CF294->battlers[i].mon.hp != 0) && (((arg1 == 0) && (!(D_821CF294->usableMask & (1 << i)))) || ((arg1 != 0) && (D_821CF294->usableMask & (1 << i)))))
    {
      if (arg0 == NULL)
      {
        for (j = 0; j < 6; j++)
        {
          if ((D_821CF298->battlers[j].mon.hp != 0) && (D_821CF298->battlers[j].mon.species != 0) && (D_821CF298->battlers[j].mon.level != 0))
          {
            BattleAi_AddMatchupPickScore(&D_821CF294->battlers[i], &D_821CF298->battlers[j]);
          }
        }
      }
      else
      {
        BattleAi_AddMatchupPickScore(&D_821CF294->battlers[i], arg0);
      }
      if ((arg2 != 0) && (BattleAi_RandomPercent() < 40))
      {
        BattleAi_AddRandomPickScore((s8 *)&D_821CF294->battlers[i]);
      }
      if (D_821CF294->mode >= 2)
      {
        D_821CF294->battlers[i].pickScore += BattleAi_RandomPercent() * 1000;
      }
      else if (D_821CF294->mode == 1)
      {
        BattleAi_AddRandomPickScore((s8 *)&D_821CF294->battlers[i]);
      }
      BattleAi_AddTrainerPickScore(&D_821CF294->battlers[i], arg3);
    }
  }

  best_score = -1;
  best = -1;
  for (i = 0; i < 6; i++)
  {
    if ((D_821CF294->battlers[i].mon.hp != 0) && (((arg1 == 0) && (!(D_821CF294->usableMask & (1 << i)))) || ((arg1 != 0) && (D_821CF294->usableMask & (1 << i)))) && (BattleAi_IsPickAllowed(arg1, arg3, i) != 0))
    {
      if (best_score < D_821CF294->battlers[i].pickScore)
      {
        best_score = D_821CF294->battlers[i].pickScore;
        best = i;
      }
    }
  }

  if (best < 0)
  {
    return -1;
  }
  D_821CF294->usableMask |= 1 << best;
  return best;
}

s32 BattleAi_PickNextPokemon(u8 *, s32, s32, s32);
extern u8 D_821CF2B8[];
/**
 * Picks arg0 Pokemon for the COM team, then sometimes moves the one with the best
 * damage ratio against the opponent's team into the lead.
 */
s32 BattleAi_PickTeam(s32 arg0)
{
  s32 best;
  s32 i;
  f32 max;
  f32 scores[6];
  s32 r;
  s32 j;

  D_821CF288 = arg0;
  for (i = 0; i < D_821CF288; i++)
  {
    r = BattleAi_PickNextPokemon(0, 0, 1, i);
    if (r < 0)
    {
      return -1;
    }
    D_821CF280[i] = r;
  }

  for (i = 0; i < D_821CF288; i++)
  {
    scores[i] = 0.0f;
    for (j = 0; j < 6; j++)
    {
      if (D_821CF298->battlers[j].mon.hp != 0)
      {
        r = BattleAi_GetBestDamage(&D_821CF298->battlers[j], &D_821CF294->battlers[D_821CF280[i]], 0);
        if (r == 0)
        {
          scores[i] += 2.0f;
        }
        else
        {
          scores[i] += ((f32) BattleAi_GetBestDamage(&D_821CF294->battlers[D_821CF280[i]], &D_821CF298->battlers[j], 0)) / ((f32) r);
        }
      }
    }
  }

  max = 0.0f;
  best = 0;
  for (i = 0; i < D_821CF288; i++)
  {
    if (max < scores[i])
    {
      best = i;
      max = scores[i];
    }
  }

  if ((best != 0) && (BattleAi_RandomPercent() < 50))
  {
    i = D_821CF280[best]; // FAKE: i reused as swap temp
    D_821CF280[best] = D_821CF280[0];
    D_821CF280[0] = i;
  }

  for (i = 0; i < D_821CF288; i++)
  {
    func_80058410((s8 *) &D_821CF294->battlers[D_821CF280[i]], (s8 *) &D_821CF2B8[i * 0x90], 0x90);
  }

  for (i = 0; i < D_821CF288; i++)
  {
    func_80058410((s8 *) &D_821CF2B8[i * 0x90], (s8 *) &D_821CF294->battlers[i], 0x90);
    D_821CF294->battlers[i].partyBit = 1 << i;
  }

  D_821CF294->usableMask = (1 << D_821CF288) - 1;
  return 0;
}

extern ComSide D_821CF618;
extern ComSide D_821CF998;
extern s32 D_821CF2A4;
void func_8004FD20(void*, s32);
void BattleAi_InitSide(); /* real types are declared with the definition below */
s32 BattleAi_PickTeam(s32);

/**
 * Team-selection entry point. Seeds the AI random source, builds both sides from
 * the parties arg0 (COM) and arg1 (opponent) and writes the chosen party indices
 * to arg3. Returns 0, or nonzero when the picks fell back to the first slots.
 */
s32 BattleAi_SelectTeam(u8* arg0, u8* arg1, s32 arg2, s8* arg3, s32 arg4) {
    s32 j;
    s32 i;
    s32 ret;

    D_821CF2B0 = 0x3039;
    D_821CF2B4 = 0x1A85;
    BattleAi_StirRandom();
    func_8004FD20(&D_821CF618, 0x700);
    D_821CF2A4 = 0xFEDC;
    if (*arg0 & 2) {
        D_821CF294 = &D_821CF618;
        D_821CF298 = &D_821CF998;
    } else {
        D_821CF294 = &D_821CF998;
        D_821CF298 = &D_821CF618;
    }
    BattleAi_InitSide(D_821CF294, arg0, arg2);
    BattleAi_InitSide(D_821CF298, arg1, arg2);
    D_821CF294 = &D_821CF618;
    D_821CF298 = &D_821CF998;
    D_821CF29C = D_821CF294->battlers;
    D_821CF2A0 = D_821CF298->battlers;
    for (i = 0; i < 6; i++) {
        D_821CF280[i] = 0;
        D_821CF294->battlers[i].unk_7B = 0;
        D_821CF298->battlers[i].unk_7B = 0;
    }
    ret = BattleAi_PickTeam(arg4);
    if (ret == 0) {
        for (j = 0; j < arg4; j++) {
            arg3[j] = D_821CF280[j];
        }
    } else {
        for (i = 0; i < arg4; i++) {
            arg3[i] = i;
        }
    }
    return ret;
}

/**
 * Decides whether to switch and to whom. Returns a party slot or -1 to stay in.
 * A switch is forced when the active Pokemon fainted, is frozen or must recharge,
 * or is asleep with a low stage; otherwise candidates are tried in rounds that
 * relax the required damage ratio.
 */
s32 BattleAi_ChooseSwitch(void) {
    s32 flag;
    s32 r;
    f32 fa[6];
    f32 f20;
    s32 k;
    s32 best;
    s32 i;

    flag = 0;
    k = 0;
    best = -1;
    if (D_821CF29C->mon.hp == 0 || (D_821CF29C->mon.pendingStatusCondition & 0x20) || (D_821CF29C->mon.uniqueStatusFlags & 1)) {
        flag = 1;
    } else if ((D_821CF29C->mon.pendingStatusCondition & 7) && D_821CF29C->mon.statStages[5] < 10) {
        flag = 1;
    }
    if (D_821CF29C->mon.hp == 0) {
        D_821CF294->usableMask &= ~D_821CF29C->partyBit;
    }
    for (i = 0; i < D_821CF288; i++) {
        if ((r = BattleAi_GetBestDamage((u8*)D_821CF2A0, &D_821CF294->battlers[i], 0)) == 0) {
            fa[i] = 255.0f;
        } else {
            fa[i] = (f32)BattleAi_GetBestDamage(&D_821CF294->battlers[i], (u8*)D_821CF2A0, 0) / (f32)r;
        }
        // FAKE: the dead store to r is needed for the operand order
        if (D_821CF29C->partyBit == (r = 1 << i)) {
            f20 = fa[i];
        }
        D_821CF294->battlers[i].matchupRatio = fa[i];
    }
    do {
        for (i = 0; i < D_821CF288; i++) {
            if (D_821CF294->battlers[i].mon.hp == 0) {
                continue;
            }
            switch (k) {
            case 0:
                if (fa[i] - f20 < D_821CF294->switchThreshold) break;
                if (BattleAi_GetHpPercent((s8 *)&D_821CF294->battlers[i]) < 0x28) break;
            case 1:
            case 2:
                if (fa[i] < f20) break;
            case 3:
                if (D_821CF294->battlers[i].mon.pendingStatusCondition & 7) break;
            case 4:
                if (D_821CF294->battlers[i].mon.uniqueStatusFlags & 1) break;
            case 5:
                if (flag && BattleAi_PickBoomMove(&D_821CF294->battlers[i], (u8*)D_821CF2A0) < 0) break;
            case 6:
                if (flag && BattleAi_MovesFirst((s8*)&D_821CF294->battlers[i], D_821CF2A0) == 0) break;
            case 7:
                if (BattleAi_GetHpPercent((s8 *)&D_821CF294->battlers[i]) < 0x37) break;
            case 8:
                if (D_821CF294->battlers[i].mon.pendingStatusCondition & 0x20) break;
            default:
            case 9:
                D_821CF294->switchThreshold = 10.0f;
                best = i;
                f20 = fa[i] - D_821CF294->switchThreshold;
            }
        }
        k++;
        if (flag && k == 2) {
            f20 = -1.0f;
        }
    } while (flag && best < 0);
    if (!flag) {
        if (BattleAi_RandomPercent() < 70) {
            if (BattleAi_SleepClauseAllows(D_821CF294) != 0 && BattleAi_MayHaveSleepMove(D_821CF2A0) != 0) {
                return -1;
            }
        }
    }
    return best;
}

