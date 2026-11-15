# COM battle AI (fragment012, from 0x82183AE0)

This started as a first-pass reading of the code. The player agent has since
checked the entry points and most move pickers in game (Free Battle, 1P vs
COM); see `docs/annotation/player-verification.md` for what was run. Names that
still carry `@unverified` were seen running but their rules were not tested. Function names are in
`src/fragments/battle/com_ai*.c`.

## Entry points

| Function | When it runs | Result |
|---|---|---|
| `BattleAi_SelectTeam` | team selection | writes the chosen party indices; seeds the AI's random source |
| `BattleAi_ChooseTurnAction` | every COM turn | 0..3 = move slot, 4 + n = switch to party slot n (also stored in `D_821CF2A4`) |
| `BattleAi_RecordUsedMove` | after both sides pick, before the moves run | learns the opponent's moves and PP, and who moved first |

`BattleAi_ChooseTurnAction` tries `BattleAi_ChooseSwitch` first. If it doesn't
switch, it calls `BattleAi_ChooseRandomMove` (mode 3) or `BattleAi_ChooseMove`.
Then `BattleAi_FindSlotWithPp` runs on the result.

## Model

The AI keeps its own copy of both sides, which the battle engine never reads:

- `D_821CF618` (COM) and `D_821CF998` (opponent) are 0x380 bytes each and are cleared together (0x700).
- `D_821CF294` and `D_821CF298` point at those two sides.
- `D_821CF29C` and `D_821CF2A0` point at the active battler records.

Side layout:

| Offset | Field |
|---|---|
| 0x000 | party (`TeamRoster` / `BattleMon[6]` at +0x1C) |
| 0x004 | 6 battler records, 0x90 bytes each |
| 0x364 | f32 switch threshold (0.5, or 10.0 from mode 2; decays each turn) |
| 0x368 | AI mode (0..3) |
| 0x369 | opponent party slot last seen in battle |
| 0x36A | turns that opponent has stayed in |
| 0x36C | bit mask of picked / still-usable party slots |

Battler record layout (offsets from the record, which is slot + 4 in `BattleSlotZ` terms):

| Offset | Field |
|---|---|
| 0x00 | owning side |
| 0x04 | s32 pick score (team selection) |
| 0x08 | f32 damage ratio against the active opponent |
| 0x0C | battle Pokemon, `BattleMonRuntime` layout (0x64 bytes): species 0x17, HP 0x18, status 0x21, types 0x28/0x29, moves 0x2B..0x2E, max HP 0x34, speed 0x3A, PP 0x3E..0x41, disabled move 0x63, stat stages 0x68..0x6F (7 = neutral) |
| 0x70 | HP at the previous turn |
| 0x72 | damage taken last turn |
| 0x74 | species (copied at init) |
| 0x75 | own party bit (1 << slot) |
| 0x76 | mask of opponents this battler has been seen to outspeed |
| 0x77 | mask of opponents it has Leech Seeded |
| 0x78 | number of moves |
| 0x7A | consecutive recharge turns |
| 0x7C..0x7E | last three moves used |

In the source these are `ComSide` and `ComBattler` (src/fragments/battle/battle.h); the battler's
battle Pokémon is `ComBattler.mon`, a `BattleMonRuntime`, so record offset 0x18 is `mon.hp`.

## Rules the AI encodes

- **Damage estimate** (`BattleAi_EstimateDamage`):
  - Starts from the engine's damage function (`func_8210EED8`).
  - Multi-hit moves count double, and high-critical-hit moves get +75%.
  - Never counts status moves, healing moves, Self-Destruct or Explosion as damage.
- **Hidden information**: when the opponent's moves are not revealed, `BattleAi_GetBestDamage` assumes any move its species can learn from the `D_82194578` list.
- **Sleep Clause**: `BattleAi_SleepClauseAllows`.
- **Heal timing** (`BattleAi_ChooseMove`): the COM only heals when it moves first and slot 0 does not knock the opponent out, and never when it took more than half its max HP last turn.
- **Thunder Wave**: the paralysis picker stops at the first usable paralysis move, so a Thunder Wave in an earlier slot than Stun Spore blocks both against a Ground type (seen in game).
- **Team levels**: three picks must sum to 150..155 (`BattleAi_LevelSumAllowed`, Nintendo Cup '97 rules).
- **Per-trainer picks** (`BattleAi_AddTrainerPickScore`):
  - Hand-written preferences keyed by the COM trainer's id word (0x6974, 0x95EC, 0x6299, 0xC0FC, 0x3C5E, 0x813A, 0x77CB, 0xBBBD, 0x940F, 0xD870, 0xCD7E, 0x4FC7).
  - The ids are the `trainerId` words of the tournament trainer templates in nintendo_cup_teams
    (`D_82400400`, read from the fragment's data): 0x755B ほっかいどう (Hokkaido), 0x6974 とうほくＡ, 0xCD7E とうほくＢ,
    0x4FC7 ほくりく, 0xC0FC かんとうＡ１, 0xC3E5 かんとうＡ２, 0x95EC かんとうＢ, 0x6299 ちゅうぶＡ, 0x3C5E ちゅうぶＢ,
    0x813A かんさい, 0x77CB ちゅうごくＡ, 0xBBBD ちゅうごくＢ, 0xD870 しこく, 0x940F きゅうしゅうＡ, 0x14FC きゅうしゅうＢ
    (regional players), and 0x473B むしとりしょうねん (Bug Catcher), 0x4353 かじばどろぼう, 0x3F6B とりつかい (Bird Keeper).
- **Random source**: `BattleAi_RandomPercent` is separate from the battle engine's RNG (`Battle_Random`). Seeding it to fixed values makes the COM deterministic for a given battle.
