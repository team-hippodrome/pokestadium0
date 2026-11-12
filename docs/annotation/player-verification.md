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

`BattleMonRuntime.hp` (0x0C, was `displayHp`) is the Pokémon's real HP: the HUD, the
COM AI and fainting all follow it. `pendingHp` (0x12, was `currentHp`) is 0xFFFF between turns
and only holds an HP value while damage is being worked out.

## Battle command phase (`8210C6B0.c`)

Breakpoints on every function of the file while playing the command menu,
the Fight menu, the Pokémon menu, a faint on each side, a sleeping COM and a
battle with all PP at 0.

| Function | Evidence | Result |
|---|---|---|
| `Battle_ChooseActionsForMode`, `Battle_ChooseActions` | Run every frame of the command phase in Free Battle (mode 1); `Battle_ChooseActions` calls `BattleScene_CollectPlayerAction` for 1P and `BattleScene_CollectCpuAction` for the COM | verified |
| `BattleMenu_TickTimeout`, `BattleMenu_ResetTimeout` | Watched D_FLT_82199EB0: 0 when the phase opens, then 1, 2 … 150 and held; reset after both actions commit. The COM's pick is timed off it; nothing times out | renamed `BattleMenu_TickCommandTimer`, `BattleMenu_ResetCommandTimer` |
| `func_8210CBD4` | Runs in the Fight menu after A; L backs out, holding R shows the move list | named `BattleMenu_UpdateMoveMenu` |
| `BattleMenu_HandleMoveButtons` | C-Up used slot 0 (Poison Sting); the R list shows C-Up 0, C-Right 1, C-Down 2, C-Left 3 | verified |
| `BattleMenu_CommitMoveSelection` | Called when both actions are in and 1P picked Fight | verified |
| `func_8210D1B0` | Runs in the Pokémon menu after B | named `BattleMenu_UpdateSwitchMenu` |
| `BattleMenu_MapButtonsToActionChoice` | In the Pokémon menu B sent out パルパル (Paras, party slot 2); the list maps C-Up 0, C-Left 1, B 2, C-Right 3, C-Down 4, A 5 | renamed `BattleMenu_HandleSwitchButtons` |
| `func_8210CD58` | Called at commit when 1P picked a switch; copies actionChosen into rosterIndex | named `BattleMenu_CommitSwitchSelection` |
| `BattleScene_HandlePlayerForcedActionState` | Took over when 1P's Nidoqueen fainted: forced Pokémon menu without L | renamed `BattleScene_HandlePlayerFaintedSwitch` |
| `BattleScene_WaitForCpuChoice` | When the COM's Pinsir fainted it called the AI at frame 60, which returned 9; Gengar (slot 5) came out | renamed `BattleScene_HandleCpuFaintedSwitch` |
| `BattleScene_CompleteCpuMoveAction` | Taken when the COM was asleep: it confirms Fight without a choice | renamed `BattleScene_AutoConfirmCpuMove` |
| `BattleMenu_GetUsableMovePpMask` | Returned 1 (not a PP mask) for a COM with all PP at 0; the COM then used Struggle | renamed `BattleMenu_MustStruggle` |
| `func_8210C8A0` | With all PP at 0, A showed 「ニドニドは だすことの できる わざが ない」 and a second A used Struggle | named `BattleMenu_HandleNoUsableMoves` |
| `BattleScene_UpdateBRollCameraSequence` | Runs every frame of the command phase (it calls `Battle_ChooseActionsForMode`) while the camera cuts between idle shots of both Pokémon, as seen on screen | verified |
| `BattleMenu_TakeControlOnBPress`, `BattleMenu_TakeControlOnCButtonPress` | Run in 1P too (B at the command menu, the forced Pokémon menu), but the tag-team handover they describe needs a two-player team, which was not tested | still `@unverified` |
| `BattleMenu_TryConfirmMove`, `BattleDemo_PlayScriptedInput`, `Battle_PrepareTurnInput`, `Battle_InitParticipantRuntime`, `Battle_InitBothParticipants` | Not reached by these tests (the demo functions belong to battle mode 5) | still `@unverified` |

## Model transform table (`battle_engine_move_model_transforms_82109AF4.c`)

Each move was put into 1P's slot 0 at the command menu and used; the
transform id at ActivePokemon +0x610 (`modelTransformId`) was sampled every
other frame on both sides, and breakpoints on every function of the file
showed which handler ran.

| Case | Seen for | Handler | Result |
|---|---|---|---|
| 2 | 12 frames on 1P's side during a recall (「もういい！ もどれ！」); nothing during the next send-out | `BattleAnim_PokeBallLand` | still `@unverified`, doc comment notes it |
| 3 | Fly | `BattleAnim_Fly` (+ Start, Continue) | verified |
| 4 | Submission | `BattleAnim_Submission` (+ Start, Continue) | verified |
| 5 | Dig | `BattleAnim_Dig` (+ Start, Continue) | verified |
| 6 | Agility | `BattleAnim_Agility` (+ Start) | verified |
| 7 | Double Team (the COM's Pinsir, every run) | `BattleAnim_DoubleTeam` (+ Start) | verified |
| 8 | Seismic Toss | `BattleAnim_SeismicToss` (+ Start) | verified |
| 9 | Minimize | `BattleAnim_Minimize` (+ Start, Continue) | verified |
| 10 | Surf | `BattleAnim_Surf` (+ Start, Continue) | verified |
| 12 | Withdraw | `BattleAnim_Withdraw` (+ Start) | verified |
| 13 | Meditate | `BattleAnim_Meditate` | verified |
| 14 | Waterfall (user's side) | `BattleAnim_Waterfall` (+ Start, Continue) | verified |
| 15 | Body Slam, Stomp (target's side) | `BattleAnim_SquishHitReaction` | verified |
| 16 | Bind, Wrap, Constrict (target's side) | `BattleAnim_LassoMoveHitReaction` | renamed `BattleAnim_BindHitReaction` (+ Start, Continue) |

No transform for: Vice Grip, Crabhammer, Hyper Beam, Splash, Teleport,
Barrier, Harden, Defense Curl, Growth, Rest, Whirlwind, Roar, Rolling Kick,
Jump Kick, Hi Jump Kick, Earthquake, Fissure, Thrash, Petal Dance, Transform,
Substitute, Mimic, Metronome, Rage, Reflect, Light Screen, Mist. Case 1
(`BattleAnim_PokeBallThrow`) and case 11 (`func_8210A3DC`) were not seen.

## Battle phases (`BattleScene_UpdatePhase`, `battle_engine_3438B0_82130628.c`)

sBattleScene.scene->phase (+0x38) logged every frame, with Battle_Random
patched to a constant (`jr ra; li v0,N`) to force confusion and paralysis.
Each turn ran 0 → 1 → 2 → 7 → 3 → effect → 4. The first pass named the case
handlers from this log (78fed92), and these lost their tags:

| Phase | Seen | Handler |
|---|---|---|
| 0 | start of every turn | `BattleScene_InitTurnPresentation` |
| 1 | command menu open | `BattleScene_PhaseCommand` |
| 2 | first action of the turn (see the correction below) | `BattleScene_PhaseFirstAction` |
| 7 | a move that acts on the user, such as COM's Double Team | `BattleScene_PhaseSelfEffect` |
| 3 | second action of the turn | `BattleScene_PhaseSecondAction` |
| 8 | the move missed | `BattleScene_PhaseMoveMissed` |
| 6 | poison damage right after the poisoned COM moved | `BattleScene_PhaseResidualDamageAfterMove` |
| 29 | Haze | `BattleScene_PhaseHaze` |
| 22 | Confuse Ray | `BattleScene_PhaseConfuseRay` |
| 20 | confusion self-hit (Pinsir 75 → 63, Battle_Random = 255) | `BattleScene_PhaseConfusionSelfHit` |
| 31 | 「からだが しびれて うごけない」 (Battle_Random = 0) | `BattleScene_PhaseFullParalysis` |
| 5 | Pinsir drops to 0 and shows ひんし | `BattleScene_PhaseFaint` |
| 18 | Gengar sent out after the faint | `BattleScene_PhaseSendOutAfterFaint` |

Phases 9 and 11 never came up.

**Correction (later the same day).** The first version of this table called
2 "both actions committed", 7 "first mover acts", 3 "second mover acts" and 8
"move damage", and those names were confirmed too early. In those turns COM
always moved first with Double Team, which also raised its evasion, so the
1P moves listed for 8 were misses. Turns with COM's speed patched to 1 so that
1P moved first, and a forced miss, showed what the phases really are:

- 1P first: 1 → 2 (1P's move: rows 3 and 4) → 3 (short) → 7 (COM's Double Team).
- COM first: 1 → 2 (short) → 7 (COM's Double Team) → 3 (1P's move).
- Battle_Random forced to 255: 2 → 8, row 12 on the user, 「しかし ニドニドの こうげきは はずれた！」.

So 2 and 3 are the first and second action, each running the per-move
presentation steps, 7 is the presentation for moves that act on the user
(moveEffectKind 7), and 8 is the miss. Renamed to `BattleScene_PhaseFirstAction`,
`BattleScene_PhaseSecondAction`, `BattleScene_PhaseSelfEffect` and
`BattleScene_PhaseMoveMissed`.

## Particle helpers (`particle_math_269820_2.c`)

Breakpoints on the 33 helpers named in 5ea6285, with the Particle at a0 read
before and after each call, over Pinsir's Double Team and 1P using
Thunderbolt, Ice Beam, Flamethrower, Psychic, Hyper Beam, Razor Leaf,
Earthquake, Solar Beam, Fire Blast, Blizzard, Thunder, Swift, Sludge and
Bubble Beam. Only these ran, and each did what its name says:

| Function | Call seen | Change |
|---|---|---|
| `Particle_SetOrigin` | (p, 0, 0, 0) | origin (-23.6, 125.3, -142.3) → (0, 0, 0) |
| `Particle_SetRotation` | (p, 0, 0, 0) | rotation x, y → 0 |
| `Particle_AnimateFramesForwardLooped`, `...ThenAdvance` | (p, 0, 7, 1, ...) | textureFrame 0 → 1 → 2 as frameTimer runs |
| `Particle_DecreaseRotationXTo` | (p, -0x1800, 0x800) | rotation.x 0xD6C → 0x56C |
| `Particle_ApplyRotationStepY` | Solar Beam | rotation.y 0x404A → 0x444A |
| `Particle_CopyMotionStepToOffsetXZ` | Solar Beam | motionOffset x, z set, y untouched |
| `Particle_AddRotationXYZ` | (p, 0x5F8, -0x35C, 0), Bubble Beam | rotation.x +0x5F8, rotation.y -0x35C |

The other 25 helpers did not run for any of these moves and keep `@unverified`.

## Battle HUD and menu drawing (`battle_engine_31D9F0_*.c`, `battle_engine_3020D0.c`)

Breakpoints while opening the command menu, the Fight menu (A, then R held),
the Pokémon menu (B) and the surrender prompt (Start, 「こうさんしますか？ いいえ はい」):

- Every frame: `Battle_RenderHud` → `BattleMenu_DrawSide0Menus` (1P box, the
  six party balls under it, `BattleMenu_DrawCommandMenu`) and
  `BattleMenu_DrawSide1Menus` (COM box).
- After A: `BattleMenu_DrawBackConfirmBar` (the 「L もどる R かくにん」 bar).
- While R is held: `BattleMenu_DrawMovePanel` with the PP text helpers.
- After Start: `BattleMenu_DrawSurrenderPromptWithCursor`.

These lost their tags. Not reached: `BattleMenu_DrawSurrenderPrompt`,
`BattleMenu_DrawConfirmButton`, `BattleHud_DrawCompactMonStatusBox` and the
`BattleDebug_*` overlays.

## Faint steps (`battle_engine_309ED0_82124E80.c`)

scene->phaseStep (+0x20) logged during phase 5 while Pinsir fainted to Poison
Sting, with a screenshot at each step. The steps carried Stadium 1 send-out
names; renamed after what each showed:

| Step | Frames | Shown | Was | Now |
|---|---|---|---|---|
| 0 | 1–2 | (setup) | `BattleScene_AdvanceSendOutPreparation` | `BattleScene_FaintStepStart` |
| 1 | ~60 | 「カイのすけは たおれた！」, fainting animation | `BattleScene_AdvanceSendOutCamera` | `BattleScene_FaintStepCollapse` |
| 2 | ~12 | turns into light and vanishes | `BattleScene_AdvanceSendOutCameraClose` | `BattleScene_FaintStepVanish` |
| 3 | ~2 | marks the Pokémon fainted | `BattleScene_FinishSendOutCameraClose` | `BattleScene_FaintStepFinishVanish` |
| 4 | — | picks phase 4 / 5 / winner | `BattleScene_CompleteSendOutFollowup` | `BattleScene_FaintStepEnd` |

Phase 34 (`func_82126E34`) runs the same steps 0–3 with its own step 4
(`func_82126D20`); it was not seen in play.

## Move execution (`ProcessBattleTurn` callees, `battle_engine_317E70.c`, `battle_engine_359F90.c`)

These were `func_` names. Breakpoints over a turn where COM's Pinsir used
Double Team and then 1P's Nidorino used Thunderbolt (savestate at the command
menu, 1P move slot 0 patched to Thunderbolt):

| Function | What the game did |
|---|---|
| `Battle_CheckForDisobedience` (was `func_82111DC4`) | Called once per move, returned 1 every time. Zero has no disobedience. |
| `BattleMessage_PrintUsedMove` (was `func_821102F0`) | Called once per move before damage; the box then read 「ニドニドの １０まんボルト！」. |
| `ActivePokemon_GetMoveName` (was `func_82107F68`) | Returned 「かげぶんしん」 for Pinsir and 「１０まんボルト」 for Nidorino. |
| `Battle_RandomizeDamage` (was `func_8210F8E8`) | Damage 23 → 20 and 23 → 19 in two runs; 23 → 23 with Battle_Random forced to 255. |
| `Battle_CalcHitChance` (was `func_82110890`) | Accuracy 255 → 168 against evasion stage 8 (+1 after Double Team), which is 255 × 66/100. |
| `Battle_MoveHitTest` (was `HandleMoveEffectFlags`) | Calls the two above; with Battle_Random forced to 255 it called `Battle_MoveMissed`. |
| `Battle_MoveMissed` (was `func_82110984`) | Called only in the forced-miss run; the box read 「しかし ニドニドの こうげきは はずれた！」 and Pinsir kept 75/75. |

`Battle_CheckExplosionVsSubstitute` (was `func_82111A78`) runs after every
move, but its body does nothing in Zero, so it keeps `@unverified`.

## Menus and messages seen in the scenario sweep

One-shot breakpoints on the unnamed fragment012 functions while playing
scripted scenarios (a normal turn, a switch from the Pokémon menu, Struggle,
the surrender prompt). Named from the code and what was on screen when each ran:

| Function | Seen |
|---|---|
| `BattleMenu_UpdateSurrenderPrompt` (was `func_8210D4B4`) | Every frame of 「こうさんしますか？ いいえ はい」 after Start. |
| `BattleMenu_DrawSwitchPanel`, `BattleMenu_DrawSwitchPanelEntry` (were `func_8211B900`, `func_8211AEA4`) | Every frame while the Pokémon menu (B) was open, called from `BattleMenu_DrawSide0Menus`. |
| `BattleMessage_TickTypewriter` (was `func_8211F0DC`) | Every frame from `Battle_RenderHud`; the box filled one character a frame. |
| `BattleScene_PhaseWithdraw` (was `BattleScene_PhaseWithdrawFainted`) | Ran for a voluntary switch, so it is not only for fainted Pokémon. |
| `BattleScene_PhaseSubstitute` (was `func_8212D820`) | Phase 25 in the per-move sweep for Substitute (164) only. |

`Battle_StartTurn`, `ActivePokemon_ShowCaption`, `ActivePokemon_TickCaptionTypewriter`,
`BattleMessage_DrawBox` and `BattleHud_DrawCaptionBox` ran in the same
scenarios, but what they draw wasn't isolated, so they keep `@unverified`.

## Per-move sweep (rows and phases)

`msweep2.py` (in the session's helper scripts, not committed) loads the
command-menu savestate, puts move N in 1P's first slot, sets COM's speed to 1
so 1P acts first, uses the move and runs 900 frames. It logs every
`BattleScene_EnterStateRow` call (side, row), every write to the scene's phase
and the first call of each unnamed fragment012 function. Results so far:

| Moves | Phases after 1 → 2 | Rows on 1P |
|---|---|---|
| Pound, Karate Chop, Mega Punch, Fire/Ice/Thunder Punch, Scratch, Vice Grip, Gust, Wing Attack, Thunderbolt and most damaging moves | 3 | 3 (move use), 4 (hit reaction) |
| Double Slap (3), Comet Punch (4), Double Kick (24) | 3 | 3, 19 (repeat hit), 4, 4 |
| Guillotine (12), Whirlwind (18) | 8 (miss) | 3, 12 |
| Razor Wind (13) | 14 (charge up) | 8 |
| Swords Dance (14) | 7 (self effect) | 3 |
| Fly (19) | 12 (fly up) | 8 |
| Substitute (164) | 25 | (none) |
| Struggle (165) | 9 (recoil) | 3, 4 |

Bind (20) held COM's Pinsir: its turn ran phase 17 with row 9 on Pinsir.
Row names given from this: row 3 `BattleScene_EnterMoveUseRow`, row 4
`BattleScene_EnterHitReactionRow`, row 19 `BattleScene_EnterRepeatHitRow`,
row 9 `BattleScene_EnterCannotMoveRow`. Two first-pass row names had the row
number off by one and were fixed (`BattleScene_TickRow21CleanupAndEnterState18`,
`BattleScene_TickRow22PlaySpeciesSound`).

## Damage and failure messages

From the command-menu savestate with COM's speed set to 1, 1P's first move
patched, and Battle_Random patched just before the move was entered:

| Check | Result | Confirms |
|---|---|---|
| Ember on Pinsir, `sBattleCritFlag` set to 1 when `Battle_PrintCriticalOHKOText` was entered | 「きゅうしょに あたった！」, then 「こうかは ばつぐんだ！」, Pinsir 75 → 54 | `Battle_PrintCriticalOHKOText`, `Battle_DisplayEffectiveness` |
| Sonic Boom | Pinsir 75 → 55 | `Battle_ApplyAttackToTarget` (fixed 20 damage) |
| Jump Kick with Battle_Random = 255 | 「しかし ニドニドの こうげきは はずれた！」「いきおい あまって ニドニドは じめんに ぶつかった！」, Nidorino 69 → 68, phases 2 → 16 → 3 | `Battle_PrintMoveFailureText`, `BattleScene_PhaseCrashDamage` |

Battle_Random has to be patched before the move is entered: the turn's
first action is resolved when both actions are committed (`Battle_StartTurn`),
not when its presentation plays. A constant 0 or 1 also hangs the game,
because `Battle_RandomizeDamage` and some effects loop until the roll is in range.

### Full sweep, all 165 moves

Phases each move's turn passed through (1P acting first), and the rows entered on 1P:

| Phase / row | Moves | Name |
|---|---|---|
| phase 8 | Guillotine, Horn Drill, Fissure (target higher level), Whirlwind, Roar, Teleport, Counter, Dream Eater on an awake target | `BattleScene_PhaseMoveMissed` |
| phase 9 | Take Down, Double-Edge, Submission, Struggle | `BattleScene_PhaseRecoilDamage` |
| phase 12 / 13 | Fly / Dig | `BattleScene_PhaseFlyUp` / `BattleScene_PhaseDigUnder` |
| phase 14 | Razor Wind, Solar Beam, Skull Bash, Sky Attack | `BattleScene_PhaseChargeUp` |
| phase 15 | Transform | `BattleScene_PhaseTransform` |
| phase 17 (COM's turn) | after Bind, Wrap, Fire Spin, Clamp, and after the sleep moves | `BattleScene_PhaseCannotMove` |
| phase 20 (COM's turn) | after Supersonic, Confuse Ray | `BattleScene_PhaseConfusionSelfHit` |
| phase 22 | the 13 status moves | `BattleScene_PhaseInflictStatus` |
| phase 25 | Substitute | `BattleScene_PhaseSubstitute` |
| phase 26 | Sand Attack, Tail Whip, Leer, Growl, String Shot, Screech, Smokescreen, Kinesis, Flash | `BattleScene_PhaseLowerStat` |
| phase 27 | Bide | `BattleScene_PhaseBide` |
| phase 28 | Recover, Soft-Boiled, Rest (at full HP), Mirror Move | `BattleScene_PhaseMoveFailedMessage` |
| phase 29 | Haze | `BattleScene_PhaseHaze` |
| phase 30, then 5 | Self-Destruct, Explosion | `BattleScene_PhaseExplosion` |
| phase 31 (COM's turn) | after Stun Spore, Thunder Wave | `BattleScene_PhaseFullParalysis` |
| phase 32 | Disable | `BattleScene_PhaseDisable` |
| row 8 | Razor Wind, Fly, Solar Beam, Dig, Skull Bash, Sky Attack | `BattleScene_EnterChargeTurnRow` |
| row 11 | the stat-lowering moves and the 6 damaging moves with a stat-down side effect | `BattleScene_TickStatDown*` |
| row 14 | the 13 status moves | `BattleScene_TickStatusHitEnd` |
| row 19 | the 10 multi-hit moves | `BattleScene_EnterRepeatHitRow` |

Effect handlers ran for exactly their Gen 1 move sets (for example
`Battle_Effect_Sleep`: Sing, Sleep Powder, Hypnosis, Lovely Kiss, Spore;
`Battle_Effect_FreezeBurnParalyze`: the 13 moves with a burn, freeze or
paralysis side effect; `Battle_Effect_Flinch`: Stomp, Rolling Kick, Headbutt,
Bite, Low Kick, Bone Club, Hyper Fang), so their tags are gone.

Phase 21 (`BattleScene_PhaseHeal`) wasn't seen in the sweep because Nidorino
was at full HP. With its HP set to 30, Recover healed it (「ニドニドは
たいりょくを かいふくした！」), but the phase watch missed the transition, so
that name keeps `@unverified`.

## Move-specific animation callbacks and presentation rows

The same 165-move sweep recorded which unnamed functions each move reached.
42 functions were reached by only one or two moves, and they are named after
those moves (`BattleAnim_Initialize<Move>Use` for the effect inits,
`BattleAnim_<Move>Particle{Update,Draw}` for particle callbacks). Each doc
lists the moves. Where a move already had an init with that name, the new one
waits for the claim check below (Thunder Wave, Dig, Confusion, Psychic).

From `sBattleSceneStateRowTable` and the rows each move entered:

| Row | Entered by | Seen with | Names |
|---|---|---|---|
| 0 | `BattleScene_FaintStepStart` | Self-Destruct, Explosion | `BattleScene_TickFaintRowPlayLandingSound`, `BattleScene_TickFaintRowQueueCollapseEffect` |
| 15 | `BattleScene_PhaseConfusionSelfHit` | Supersonic, Confuse Ray (COM hurt itself) | `BattleScene_EnterConfusionSelfHitRow` |
| 18 | `BattleScene_PhaseSendOutAfterFaint`, rows 10 and 21 | Transform | `BattleScene_TickSendOutRowPlayCry` |
| 22 | a confused Pokemon's turn | Supersonic, Confuse Ray | `BattleScene_EnterConfusedRow` (`@unverified`) |

`BattleScene_UseMoveStepMultiHit` (use-move variant 10) ran for exactly the
ten multi-hit moves. Sounds can't be heard in the headless run, so the
landing-sound names keep `@unverified`.

## Effect inits, from the effect-id dispatcher

Move animations start through two tables indexed by effect id:
`sMoveAnimEffectStartInitFuncs` (`BattleAnim_RunEffectInitStart`, called when
the move is used) and `D_8218EA6C` (`BattleAnim_RunEffectInitEnd`, called at
the impact, about 128 frames later). With breakpoints on just those two
dispatchers, each of the 165 moves was used once and the effect ids logged
(the COM's turn left out). This is exact, unlike the many-breakpoint sweeps.

* 160 table entries ran for a known set of moves. Each now says which in its
  doc, and the `@unverified` tag is gone where the name matched.
* The `...Use` names belong to the start table and the `...Hit` names to the
  end table, as the first pass guessed.
* 24 names were wrong or generic and are renamed after the moves that ran
  them. Examples: `ParticleEffect_InitExplosionSet` is
  `BattleAnim_InitializeFlamethrowerHit`, and `InitParticleEffectSet_WithComplex`
  is `BattleAnim_InitializeHyperBeamHit`. `BattleAnim_InitializeWaterfallUseA`
  is Waterfall's end init, so it is now `BattleAnim_InitializeWaterfallHit`.
  `func_82153FD8`, `func_8215E2C4` and `func_8215E1A8` are the Thunder Wave,
  Confusion and Psychic end inits.
* Dig's first turn uses start init 69, now `BattleAnim_InitializeDigBurrowUse`.
  `BattleAnim_InitializeDigUse` (start 52) never ran, so it keeps its tag. It
  may be the second turn, which the 700-frame window doesn't reach. The same
  goes for Sky Attack's and Solar Beam's other halves, and for Recover and
  Soft-Boiled, which fail at full HP.

Caveat for the earlier sweeps: with dozens of execution breakpoints set, the
debugger missed some hits that it caught with two breakpoints set. For
example, `BattleAnim_InitializeIceBeamHit` was missed with 21 breakpoints and
caught with 2. So "only move X reached this" in the earlier per-function sweep
can undercount the moves. The move that was seen did reach the function.

## Battle opening and order select

The opening was screenshotted 20 frames after each `BattleScene_RunOpeningSendOut`
step began:

1. The stadium lights overhead.
2. The camera coming down.
3. Side 0's and then side 1's Poke Ball trails.
4. The field with the landing ball's shadow.
5. The white flash.
6. 「ゆけっ！イワイワ」, then 「ゆけっ！ニドのすけ」.

All step names fit, and the tags are gone except for the 3-frame asset wait and
the orbit, which a still frame can't tell apart.

On the order select screen (`battle_order_select.c`, Free Battle against the
COM), presses were matched to the functions they reached:

* Each pick reaches `BattleMenu_AppendOrderSlotIcon`, the level-sum check and
  the completeness check.
* L reaches `BattleMenu_ResetOrderSlotIcons`.
* The sixth pick opens 「これで いいですか？ はい えらびなおす」
  (`BattleMenu_DrawOrderSelectConfirmPrompt`, `..._ConfirmInput`).

The level-total notice needs cup rules and wasn't triggered.
`BattleMenu_DrawBottomActionButtons` didn't run from the mid-screen
savestate. It does run when the order screen is entered fresh (seen before a
モンスターボールカップ round, with 「＊L ボタンでもどる ＊R ボタンでかくにん」
along the bottom), so it is confirmed.

## Re-check after the debugger fix

The missed breakpoint hits came from two places. One was a resume race in
the debugger, now fixed. The other was in my sweep script: `emu.wait_frames`
resumes a stop that lands just before the call. The script now waits with
`emu.wait_break` and never resumes a stop it hasn't seen.

I re-ran the sweep for the 50 functions named above. Each move-specific
callback reached the same moves as before, so those docs stand. The confusion
callbacks depend on the dice, and this time they ran after Psybeam's
confusion side effect. Watching one on screen showed that use-move variant 11
is the self-hit, 「わけも わからず じぶんを こうげきした！」 with red ?! marks.
It is now `BattleScene_UseMoveStepConfusionSelfHit`.

The cartridge check screen comes after the title: 「ポケモンの カートリッジが
セット されていません。…」 with an 「オプション」 button. The first pass had its
loop and draw functions as `Options_RunTitle` and `Options_DrawTitle`. They
are now `TransferPak_RunCartridgeCheckScreen` and
`TransferPak_DrawCartridgeCheckScreen`. C-Right opens the options menu, and A
on バックアップ opens the clear-save prompt, so those names are confirmed.

## Menus walked through in play

With no Game Boy cartridge, the main menu greys out ずかん, てもち, GB and
とうろく, so only バトル and OFF can be entered. Walked and screenshotted:

* The cartridge check screen and オプション, including the clear-save prompt.
* メインメニュー and the バトル description window.
* バトルモード (`FreeBattle_DrawBattleModeCard`).
* たいせんルールせんたく and each rule's たいせんする / ルールをみる (the rules
  list popup).
* あいてをせんたく (1P VS COM; 2P to 4P dimmed).
* エントリーポケモンのせんたく: the Free Battle preset teams, the L50～55 and
  L1～30 rental grids with the 「レンタルしますか？」 status window, and
  「このデータでエントリーします。」. Then エントリーけってい, which builds the
  battle rosters.
* トーナメントせんたく and カップせんたく (only モンスターボールカップ open).
* The tournament VS scene (`VsScene_*`): the stadium, a zoom into the big
  screen's flames, the 「バトル」 title, then 「トレーナー 1P VS トレーナー
  むしとり しょうねん」.

Functions that ran on each screen were caught with breakpoints. A name lost
its tag only where the screen showed what the name says. About 30 helpers on
these screens got names from their code and from the moment they ran.

Not reached: the screens after a tournament win. Scripted inputs in a
tournament battle didn't land reliably, and setting COM HP mid-battle stalled
the next send-out once.

## The GB item with a Japanese cartridge

These screens were played with Pocket Monsters Green (Rev 1) in an emulated
Transfer Pak. Julius uploaded the cartridges, which are used only locally and
are never committed. With the pak inserted, the main menu enables GB but warns
「GBのポケモンがいない」, because the save is blank. ずかん, てもち and とうろく
stay greyed out.

* Cartridge check. `GbPak_IdentifyCartridge` compares the header with a table
  holding YELLOW, BLUE, GREEN and RED. Each entry needs destination 0 (Japan)
  and licensee 01, and the version byte is not compared. So Zero accepts
  Pocket Monsters Pikachu (Yellow) even though its title screen predates it.
* Streaming. Red, Green and Blue are streamed bank by bank while the game
  runs, behind the 「ロードちゅう」 banner. Each bank's two 0x2000-byte halves
  are summed and compared with tables for Red v0/v1, Green v0/v1 and Blue v0
  (D_811223F4 ... D_81122774). Yellow has no table, so it is copied whole
  before play. All five tables match the uploaded dumps.
* Mapper writes. `GbPak_WriteMapperRegister` (was WriteFilledRegisterBlock)
  writes a 32-byte block with the value only in its last byte. The debugger
  read byte 0, so the ROM bank never changed and the first bank checksum
  failed with 「64GBパックが ただしくセットされていません」. That was fixed in the
  debugger (pj64-pokestadium-debug 455668a).
* Boot hand-off. During streaming the GB runs a boot stub that ends in
  `jr $` at 0x100. Once the GB PC reaches 0x100, `GbEmu_UpdateFrame` puts the
  real header bytes back. The emulated pak loads faster than the stub runs, so
  the hand-off was done by hand. After that Green showed its copyright screen
  and the Gengar and Nidorino intro inside Zero's GB frame
  (「△でメニュー」).
* The GB CPU core is the asm function func_81118018. It keeps the GB PC in
  `s7` and dispatches on the opcode byte; the handler at 0x81119090 is `jr e`.

## A Gen 1 save: てもち, ずかん and the full main menu

A Pocket Monsters Green save was built by hand. Its offsets come from Green's
own save routine: name at 0xA598, main data at 0xA59E (0x737 bytes), party
at 0xAED5 (0x158 bytes) and the checksum at 0xB594. The save holds three
level-5 starters with nicknames ハナ, ヒノコ and カメ, and the trainer サトシ
with ID 12345. Zero showed exactly these on the cartridge screen and in
てもち, so the party, nickname, OT and ID offsets are right.

* てもち (`PartyScreen_*`, fragment019). The screen has a party list, an
  action menu (つよさをみる / ならびかえ / やめる) and the つよさをみる page
  (`MonSummary_*`). That page shows the 3D model (rotated with the C buttons),
  No., level, HP, status, stats, types, ID, OT, Exp and 「あと 44で L6」, but
  no moves. ならびかえ asks 「どこに いどうしますか？」 and moves the Pokémon.
* ずかん unlocks with the got-Pokédex flag (`GbSave_HasPokedex`, bit 0x20 at
  save offset 0x29ED). Without it the menu warns 「ずかんをもっていない」.
* The current map (save offset 0x2600) must be a Pokémon Center
  (`GbSave_CheckSavedAtPokemonCenter`, table `sPokemonCenterMapIds`: 0x29,
  0x3A, 0x40, 0x44, 0x51, 0x59, 0x85, 0x8D, 0x9A, 0xAB, 0xAE, 0xB6). Without it
  the menu warns 「ポケモンセンターにいない」. With it the menu gains せいとん and
  いちらん and shows the Pokémon Stadium logo.

## ずかん (Pokédex)

The ずかん item opens ずかんもくじ (fragment018). The list shows 001 フシギダネ,
004 ヒトカゲ and 007 ゼニガメ with caught icons. The counts window shows
みつけたかず / つかまえたかず / もっているかず 3 / 3 / 3. The menu has
データをみる / なきごえ / ぶんぷをみる / やめる, and the sort bar shows
ばんごうじゅん.
データをみる shows the 3D model, No.001, たねポケモン, 0.7m, 6.9kg and the dex
text. なきごえ plays the cry. ぶんぷをみる flies over a 3D Kanto map titled
「フシギダネのすみか」, marked 「せいそくちふめい」 because starters aren't wild.
28 `Pokedex_*` names were confirmed this way.

## とうろく (registration)

The とうろく item opens fragment008. The menu has ポケモンを とうろくする,
とうろくした ポケモンをみる and とうろくした ポケモンをけす. Its description reads
「GBカートリッジの てもちポケモンの「データ」だけを きろくする。ポケモンそのものは
いどうしない。」. Registering listed the 1P cartridge's party (サトシ,
IDNo/12345, ハナ, ヒノコ and カメ at L5) and asked 「このポケモンをとうろくする？」.
After はい the party went into slot 01, shown with Ditto placeholders until the
copy finished. Then came 「メタモンのへんしんがおわりました。ポケモンは
GBカートリッジに そのまま のこっています。」. 32 `Registration_*` names were
confirmed. The view and delete lists were not opened.

## いちらん and せいとん

* いちらん (fragment016, `LabPCList_*`) opens on the window 「どこのポケモンを
  いちらん するか えらんでください。」, which offers てもち, ゲームボーイのボックス
  and 64カセットのボックス (boxes 1-4). The table lists ポケモン, ニックネーム,
  ID, おや, ばしょ and タイプ1/2 under 「Lタテ／ヨコきりかえR」 and
  「ページおくり1／3」. The Stadium 1 name at 0x89104998
  (BattlePrep_UpdateSingleBattleIntroFrame) is this screen's setup:
  `LabPCList_Setup`.
* せいとん (fragment015) opens a menu with three entries:
  * ポケモンを いどうする opens `PcSort_*` (ポケモンのせいり). It shows てもち
    03/06 and GBのボックス1 00/30, and asks 「どこからいどうする？」 and
    「どこへいどうする？」 over てもち, GBのボックス1-8 and 64のボックス1-4.
  * どうぐを いどうする opens `LabItem_*` (どうぐのせいり). It shows てもちの どうぐ
    000/020 and サトシのパソコン 000/050.
  * ボックスを いどうする opens `PcBox_*` (ボックスのそうさ). It shows GBのカートリッジ
    ボックス1-8 and 64のカセット ボックス1-4, with 「64へボックスをいどうする」.

## Per-move sweep over the tagged battle functions

Each of the 165 moves was used once from 1P, with breakpoints on all 1,061
tagged fragment012 functions, and the moves each function ran for were
recorded (757 of them ran). A move-named function lost its tag when every
move in its name was among the moves it ran for, and it ran for at most 8
moves; 226 names passed. A few descriptive names with tight move sets were
also confirmed this way, for example `BattleEffect_OHKO` (Guillotine, Horn
Drill, Fissure), the stinger trail (Poison Sting, Twineedle, Pin Missile) and
the fire-breath flames (Flamethrower, Dragon Rage, Fire Spin, Fire Blast).
`BattleAnim_InitializeCutSlashScratchEffect` ran only for Cut, so it is now
`BattleAnim_InitializeCutEffect`.

## Switch, surrender, faint and COM healing

These scenarios start from a COM free battle (1P ガール team, COM むしとり team).

* Switch: B, then C-Left, sent Onix (イワワ) in for Nidorino. This ran
  `BeginBattleForEntity`, the runtime-state init and reset pair, and the roster
  selection helpers.
* Surrender: Start opens 「こうさんしますか？ いいえ はい」. Choosing はい shows both
  teams, then COM's かち screen. `BattleMenu_DrawSurrenderPrompt` never ran and
  has no direct callers; the prompt on screen is drawn by
  `BattleMenu_DrawSurrenderPromptWithCursor`.
* Faint: COM's Pinsir (カイのすけ) was set to 1 HP and speed 1. Poison Sting
  (こうかは ばつぐんだ！) knocked it out (ひんし), then 「もういい！ もどれ！」. COM
  picked Gengar behind the R かくにん button (`BattleMenu_DrawConfirmButton`) and
  sent it out with ゆけっ！ゲンのすけ (`ActivePokemon_GetPokeBallAimPoint`).
* COM healing: Gengar was set to 20/ 72 HP with Recover in slot 3.
  `BattleAi_PickHealingMove` returned 3 and Gengar used じこさいせい (HP 56/ 72),
  but only after offset 0x72 of the AI record was cleared. That offset held 52
  although Gengar had not been hit, so it is not "damage taken last turn".
* Poison: writing 0x08 to the runtime status byte (+0x15) put どく on COM
  Gengar's HUD and it lost 4/ 72 HP at the end of its turn. With Gengar at
  3/ 72 HP the poison knocked it out (「ゲンのすけは どく」, ひんし) and COM sent
  out Pikachu. At commit, `BattleMonRuntime` +0x0E was 0 while HP was still 3:
  `Battle_ApplyPoisonOrBurnDamage` stages the HP left after the poison or burn
  damage there, so the field is now `hpAfterPoisonBurn`. The check that ran
  is now `Battle_CheckAllBroughtFainted_PoisonBurn` (was
  `Battle_CheckDefeatAtStatusHp`). `BattleScene_PhaseResidualDamageFaintCheck`
  did not run for this knockout, so it keeps its tag.
* COM team pick: confirming 1P's order ran `Battle_SelectComRoster` and the
  `BattleAi_*` pick helpers once, before the first send-out. COM brought
  Pinsir, Gengar and Pikachu. The pick helpers' scoring is not shown on
  screen, so they keep their tags.
* COM's view of 1P: after Nidorino had used Poison Sting and Tail Whip, the
  AI record of Nidorino listed only those two moves and HP 44 (HUD 44/ 69),
  which confirms `BattleAi_CopyVisibleBattleState`.

## Sweep cross-check against move lists in comments

Several effect functions name their moves in the comment, not the function
name. Where the per-move sweep ran the function for exactly those moves, the
tag came off (31 names: the Egg Bomb blasts, the Boom small explosions, the
after-impact smoke, the falling leaves and feathers, the lightest mist, the
hue change, the hit sparks, the slime variants, Surf's splash, the lasso hit,
the stinger trail colors, the Disable radial, and the single-move trail
starters for Petal Dance, Razor Leaf, Spike Cannon, Swift, and the Hyper Beam
and Ice Beam trail). Where the sweep and the comment disagree, the evidence
line says how. For example, Bide does not use the flame under the Pokémon,
and Disable does not use the lasso hit.
* Faint checks: the four `Battle_CheckAllBroughtFainted_*` variants differ
  only in which HP field of the active Pokémon they add up. The one that ran
  when Pinsir was knocked out reads `hp`, so `_Level` is now `_Hp`. `_PP`
  reads `pendingHp` and is now `_PendingHp`, though it still has its tag
  because it never ran.

## Battle mechanics checked in RAM

These checks used breakpoints on entry and return, with the runtime fields read
on both sides of the call.

* Paralysis: Thunder Wave paralysed Pinsir (status 0x40), and
  `ApplyParalysisSpeedCut` took its Speed from 50 to 12.
* Burn: with Pinsir's status set to 0x10, `ApplyBurnAttackCut` took its
  Attack from 71 to 35.
* PP: Poison Sting went from 35 to 34 PP in `Battle_DecrementPP`.
* Move order: `Battle_DetermineMoveOrder` returned 1 (COM first) at Speed 50,
  and 0 once Pinsir's Speed was set to 1. The battle followed both results.
* Critical hits: `Battle_CheckCriticalHit` returned 1 with the random roll
  forced to 2 for that call, and the game showed きゅうしょに あたった！
* Damage: Nidorino's Poison Sting on Pinsir went through `Battle_CalcDamage`
  (base 4, the Gen 1 formula), `Battle_ApplyTypeEffectAndSTAB` (6 for the
  same-type bonus, then 12 for Poison against Bug), the random roll (10), and
  `Battle_ApplyDamage` (75 to 65 HP). `Battle_LoadMoveCache` had loaded
  Poison Sting's six data bytes (28 02 0F 03 FF 23).
* Messages: `BattleMessage_Format` built 「ニドニドのどくばり!」 with id 0x18,
  and 「こうかは ばつぐんだ！」 with id 0x29.
* Battle start: `BattleScene_SendOutSide0` ran as 1P's Poké Ball burst open,
  and `BattleScene_SendOutSide1` ran just after 1P's Onix was out.
  `ActivePokemon_GetNickname` returned ニドニド for 1P's Nidorino.
* COM AI helpers: `BattleAi_CanUseMove` returned each of Pinsir's four moves
  (all with PP left), and `BattleAi_FindUsableHealingMove` returned Recover
  for Gengar once Recover was in its moves, and 0 for Nidorino.
