# COM battle AI (fragment012, from 0x82183AE0)

Everything here is a first-pass reading of the code and is `@unverified`: no
player agent or human has checked it in game yet. Function names are in
`src/fragments/fragment012_17ED00/battle_engine_com_ai*.c`.

## Entry points

| Function | When it runs | Result |
|---|---|---|
| `BattleAI_SelectTeam` | team selection | writes the chosen party indices; seeds the AI's random source |
| `BattleAI_ChooseTurnAction` | every COM turn | 0..3 = move slot, 4 + n = switch to party slot n (also stored in `D_821CF2A4`) |
| `BattleAI_RecordUsedMove` | after both sides act | learns the opponent's moves and PP, and who moved first |

`BattleAI_ChooseTurnAction` tries `BattleAI_ChooseSwitch` first. If it doesn't
switch, it calls `BattleAI_ChooseRandomMove` (mode 3) or `BattleAI_ChooseMove`.
Then `BattleAI_FindSlotWithPp` runs on the result.

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

`BattleSlotZ` in the source is the same memory, viewed four bytes early, so
`BattleSlotZ.hp` is record 0x18. Turning these into one proper `ComSide` /
`ComBattler` pair is left for the struct pass; the code reaches the fields
through raw `u8 *` offsets today.

## Rules the AI encodes

- **Damage estimate** (`BattleAI_EstimateDamage`):
  - Starts from the engine's damage function (`func_8210EED8`).
  - Multi-hit moves count double, and high-critical-hit moves get +75%.
  - Never counts status moves, healing moves, Self-Destruct or Explosion as damage.
- **Hidden information**: when the opponent's moves are not revealed, `BattleAI_GetBestDamage` assumes any move its species can learn from the `D_82194578` list.
- **Sleep Clause**: `BattleAI_SleepClauseAllows`.
- **Team levels**: three picks must sum to 150..155 (`BattleAI_LevelSumAllowed`, Nintendo Cup '97 rules).
- **Per-trainer picks** (`BattleAI_AddTrainerPickScore`):
  - Hand-written preferences keyed by the COM trainer's id word (0x6974, 0x95EC, 0x6299, 0xC0FC, 0x3C5E, 0x813A, 0x77CB, 0xBBBD, 0x940F, 0xD870, 0xCD7E, 0x4FC7).
  - Which trainer each id belongs to is not established yet.
- **Random source**: `BattleAI_RandomPercent` is separate from the battle engine's RNG (`Battle_Random`). Seeding it to fixed values makes the COM deterministic for a given battle.
