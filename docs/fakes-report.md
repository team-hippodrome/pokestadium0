# Fakes worth replacing first

Snapshot of master `6622f65` plus the marking pass that added this file. Regenerate the raw data with `tools/fake_audit.py` (ranked table) or `tools/fake_audit.py --unmarked` (flagged lines that carry no `// FAKE` or `// karodo`). The detector is pattern based; a flagged line still needs a reader's judgment.

## Counts

| Kind | Lines |
|---|---|
| `// FAKE` comments in `src/` (after this pass) | 856 |
| `// karodo` comments | 68 |
| `M2C_FIELD(...)` untyped field accesses (struct work, not marked individually) | 5,897 |
| Files still in permuter brace style (`{` on its own line) | 62 |

The marking pass added `// FAKE` to 359 stack pads, 131 nested raw-pointer cast chains, 52 permuter `new_var` declarations, 16 hand-expanded gbi macros, 7 self-assignments, 6 `^ 0`, 2 `* 1`, 4 comma expressions and 2 karodo empty `if`s.

`M2C_FIELD` and single-level `*(T *)((u8 *)p + 0x..)` accesses are untyped struct access, not register tricks. They go away as structs are unified and are left unmarked so the real register-steering fakes stay visible.

## Ranked: really bad fakes

Rank weighs how much the fake obscures meaning and how likely a clean rewrite exists, not just how many fakes a function has. Battle and save code is ranked up because the libultraship port depends on reading it.

| # | Function | File | Why it is bad | Suggested alternative to try |
|---|---|---|---|---|
| 1 | `func_8001A3E4` | `src/graphics_textures_2.c` | 13 hand-expanded `gDPLoadTextureBlock`/`gDPSetTile` macro bodies, several joined on one line (IDO schedules by line). Unreadable and unportable. | Rewrite with `gDPLoadTextureBlock_4b` / `gDPSetTileSize` macros, keeping the original one-line grouping via a local macro. |
| 2 | `func_821125C0` (ProcessBattleTurn) | `fragments/fragment012_17ED00/battle_engine_317E70.c` | Core turn loop. `user = user;` self-assignment plus 8 m2c `goto`s. | Restructure the gotos into the Stadium 1 shape (`ProcessBattleTurn` in pokestadium `src/fragments/battle_engine/battle_engine_mechanics.c`) and drop the self-assignment. |
| 3 | `func_8217E34C` | `fragments/fragment012_17ED00/battle_engine_3540B0.c` | `new_var = (s8 *)((0, new_var));`, `new_var = new_var;` and raw `+0/+2/+4` casts on a 0x418-byte record. | Declare the record struct (s16 state, timer, limit at 0x0/0x2/0x4) and iterate a typed pointer. |
| 4 | `func_81109764` | `fragments/fragment000_80C00/gb_tower_emulator_86920.c` | Self-assignment, two permuter temps and a bitfield test written as `>> 0x1F` on a raw cast. | Typed 0x15C-byte entry with a sign-bit flag; GB Tower struct work should cover it. |
| 5 | `func_80027F20` | `src/gb_save.c` | Save data path. 8 permuter temps and a self-assignment. | Re-derive from Stadium 1's save code before porting. |
| 6 | `func_8002EDA8` / `func_8002ED70` | `src/2E480.c` | Scroll-menu tick: 29 raw casts into `ScrollMenu8002F6C4`, three stacked `if (1) {}`, 9 permuter pointers in the helper. | Fill in the menu struct fields 0x28–0x3C; the casts then become member reads, and the karodo may drop. |
| 7 | `func_820020EC` | `fragments/fragment007_166580.c` | Permuter temp, `pad[1]`, an alias kept only to pin s6, and 4 expanded gbi words. | Same macro rewrite as #1. |
| 8 | `func_89007264` | `fragments/fragment015_238BD0/89006FC0.c` | `arg0 = arg0;` plus 7 permuter temps. | Typed lab PC struct. |
| 9 | `func_8212C398` | `fragments/fragment012_17ED00/battle_engine_3438B0.c` | `D_8219A568 = 0 ^ 0;` and the whole body on one source line. | Split back to statements once the scheduling dependency is understood. |
| 10 | `func_8210F3F0` | `fragments/fragment012_17ED00/battle_engine_361050.c` | Battle random byte (callers compare it against accuracy/chance thresholds): `return (... ) ^ 0;` around a five-cast float expression. | Name the two double constants and write the expression plainly; the RNG must be readable for the port. |
| 11 | `func_821036F4` | `fragments/fragment012_17ED00/battle_engine_move_animation.c` | `species ^ 0` to keep a register live. | Try a `u8` species local. |
| 12 | `func_80039010` | `src/libnumus/player.c` | Two `temp_a0 ^ 0` stores among 42 `M2C_FIELD`s. | Use the libnumus player struct once known. |
| 13 | `func_81110798`, `func_81111784` | `fragments/fragment000_80C00/81110210.c` | `(priority >= 1) ^ 0` and `prioA ^ 0` in audio priority tests. | Signedness change on the priority fields. |
| 14 | `func_8A201EAC` | `fragments/fragment019_293410/lab_pc_icons_8A201598.c` | `temp_v0 ^ 0` plus 17 raw casts. | Struct work. |
| 15 | `func_82134DEC`, `BattleAnim_CallbackEndEffect56...InitParticle` | `battle_engine_315D50.c`, `battle_engine_31D9F0_2.c` | `arg0 * 1` / `sp36 * 1`. | Try a cast to the callee's parameter type instead. |
| 16 | `Trail40Variant_ApplyRippleAtPoint`, `func_89008EF0`, `func_81104930` | three files | Comma expressions `(0, x)`. | Usually a missing temp or a differently typed field. |
| 17 | `func_82185D44`, `func_81100C84`, `func_811030F0` | battle_engine_com_ai_2_82184DC8, 81100020, gb_tower_emulator_7F9A0 | 24–28 m2c `goto`s each in 150–450-line state machines. | Rebuild as `switch`/loops; no register trick involved, just unstructured output. |

## Fakes that are probably not worth chasing

- Stack pads (`s32 pad;`, `UNUSED s32 pad2;`): they reserve frame space for locals the original code had. Naming the real local later is nice but not urgent.
- Same-line statement grouping (`// FAKE: both stores must share one source line`): this reflects how IDO schedules; the original code may well have been a macro.
- `do { } while (0)` wrappers around one call: likely karodo from a stripped debug macro.
