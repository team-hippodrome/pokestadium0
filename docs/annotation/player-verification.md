# Player verification log

The player agent plays Stadium Zero in pj64-pokestadium-debug (branch
`claude/project-thread-qy0mpa`, headless under Xvfb, driven through the agent
server) and checks the first pass's `@unverified` names against what the game
does. A name loses its tag only when the game showed it doing what the name
says. This file records how each check was made, so it can be repeated.

## Setup used

- Main menu > バトル (Battle) > フリーバトル (Free Battle) > Free Battle rules >
  たいせんする, 1P vs COM. 1P takes the ガール (Girl) preset team (Nidoqueen
  lead, L20), COM the むしとり (Bug Catcher) team (L25: Pikachu, Pinsir, Ditto,
  Gengar, Nidoking, a sixth).
- Zero's battle command menu: A たたかう (Fight), B ポケモン (Pokémon), Start
  にげる (Run). After A the move list is hidden; holding R (かくにん) shows it.
  Moves are picked with the C buttons: C-Up slot 0, C-Right slot 1, C-Down
  slot 2, C-Left slot 3. L (もどる) goes back.
- Experiments patch the COM's battle Pokémon (`BattleMonRuntime` at the
  `BattleAi_ChooseTurnAction` a0) at the moment that function is entered: moves
  at +0x1F, PP at +0x32, HP at +0x0C, status at +0x15.

## COM AI (fragment012, `battle_engine_com_ai*.c`)

Call order seen with execution breakpoints on every function of the five files:

- Team order screen, right after the battle fragment loads: `BattleAi_SelectTeam`
  → `BattleAi_StirRandom` → `BattleAi_RandomPercent`, then `BattleAi_InitSide`
  twice (`BattleAi_LoadBattlerFromPartyMon` for the COM's own team,
  `BattleAi_LoadBattlerFromSpecies` for the player's hidden team), then
  `BattleAi_PickTeam(6)` → `BattleAi_PickNextPokemon` → the pick scorers.
- Each turn, when the command menu opens: `BattleAi_ChooseTurnAction` →
  `BattleAi_CopyVisibleBattleState`, `BattleAi_ChooseSwitch`,
  `BattleAi_ChooseMove` → the pickers → `BattleAi_ReplaceHyperBeam` →
  `BattleAi_FindSlotWithPp`.
- After both sides have picked, before the moves run: `BattleAi_RecordUsedMove`.

| Function | Evidence | Result |
|---|---|---|
| `BattleAi_SelectTeam`, `BattleAi_InitSide`, `BattleAi_PickTeam`, `BattleAi_PickNextPokemon` | Run once, at the team order screen, with a pick count of 6 | verified |
| `BattleAi_RandomPercent`, `BattleAi_StirRandom` | Returns seen: 90, 0, 79, 63, 95, 80, 31, 1 | verified |
| `BattleAi_LoadBattlerFromSpecies` | Called with species 31 (Nidoqueen, national dex) and level 20 for the player's lead | verified |
| `BattleAi_CalcStat`, `BattleAi_CalcMaxHp`, `BattleAi_CalcAttack`/`Defense`/`Speed`/`Special` | Inputs were Nidoqueen's base stats 90/82/87/76/75; CalcStat(82, 0xFFFF, 20) = 50, matching the Gen 1 formula with DV 0 and maximum stat experience | verified |
| `BattleAi_GetBestDamage`, `BattleAi_MayKnowMove`, `BattleAi_SpeciesCanLearnMove`, `BattleAi_EstimateDamage` | With the player's moves hidden, damage was estimated for Mega Punch, Mega Kick, Horn Drill, Body Slam, Ice Beam, Blizzard... (Nidoqueen's TM moves): Ice Beam 44, Blizzard 56 | verified |
| `BattleAi_HasType` | HasType(Nidoqueen, Poison) = 1; Pikachu is neither Ice nor Poison (0) | verified |
| `BattleAi_GetHpPercent` | 100 at full HP | verified |
| `BattleAi_MovesFirst` | 1 for the L25 COM against the L20 Nidoqueen; the COM moved first in game | verified |
| `BattleAi_ChooseTurnAction` | Returned 0 and Nidoking used slot 0 (Earthquake); returned 9 (4 + party slot 5) when frozen and the COM recalled Nidoking (「もういい！ もどれ！」) | verified |
| `BattleAi_ChooseSwitch` | -1 normally, 5 when the active Pokémon was frozen | verified |
| `BattleAi_ChooseMove`, `BattleAi_PickStrongestMove` | Slot 0 (Earthquake) taken when it knocks the opponent out; doc comment rewritten with the order seen | verified |
| `BattleAi_PickSleepMove` | Given Hypnosis: picked, used, 「ニドニドは ねむってしまった」 | verified |
| `BattleAi_PickStatLowerMove` | Given Tail Whip (slot 3): picked | verified |
| `BattleAi_PickStatBoostMove` | Given Swords Dance: picked, 「つるぎのまいを つかった！」 | verified |
| `BattleAi_PickBoomMove` | Given Explosion at 10 HP: picked, 「だいばくはつ！」 | verified |
| `BattleAi_PickParalysisMove` | Given Thunder Wave and Stun Spore against Ground-type Nidoqueen: -1 (the first usable paralysis move decides) | verified |
| `BattleAi_PickToxicOrLeechSeed` | Given Toxic against Poison-type Nidoqueen: -1 | verified |
| `BattleAi_RecordUsedMove` | After the player chose Poison Sting, the AI's record of the player held move 40 with 55 PP | verified; doc comment added |
| `BattleAi_PickHealingMove` | Given Recover at 20/79 HP: -1, because the patched HP looked like 59 damage taken last turn; doc comment now gives that rule | still `@unverified` |
| `BattleAi_FindSlotWithPp`, `BattleAi_ReplaceHyperBeam`, `BattleAi_CopyVisibleBattleState`, `BattleAi_SleepClauseAllows`, `BattleAi_MayHaveSleepMove`, pick scorers | Seen running in the order above; their rules were not tested | still `@unverified` |

Related engine function: `Battle_DetermineMoveOrder` returned 1 when the COM
(side 1) moved first.

### Field note for the struct pass

`BattleMonRuntime.displayHp` (0x0C) is the Pokémon's real HP: the HUD, the
COM AI and fainting all follow it. `currentHp` (0x12) is 0xFFFF between turns
and only holds an HP value while damage is being worked out.
