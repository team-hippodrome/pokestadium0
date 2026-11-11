# Original SDK assembly continuation — 2026-11-11

This batch replaces extracted `GLOBAL_ASM` listings for 12 owners (1,520 inventory
text bytes) with the unmodified assembly sources already tracked in
`lib/ultralib`. These owners are original SDK assembly, not C.

| Owner | SDK symbol | Bytes | Original source |
| --- | --- | ---: | --- |
| `func_80057910` | `_bcmp` | 288 | `lib/ultralib/src/libc/bcmp.s` |
| `func_80058410` | `_bcopy` | 784 | `lib/ultralib/src/libc/bcopy.s` |
| `func_80053A80` | `osGetCount` | 16 | `lib/ultralib/src/os/getcount.s` |
| `func_80052470` | `__osGetSR` | 16 | `lib/ultralib/src/os/getsr.s` |
| `func_80058940` | `__osDisableInt` | 32 | `lib/ultralib/src/os/interrupt.s` |
| `func_80058960` | `__osRestoreInt` | 32 | `lib/ultralib/src/os/interrupt.s` |
| `func_800596E0` | `osMapTLBRdb` | 96 | `lib/ultralib/src/os/maptlbrdb.s` |
| `func_800539C0` | `__osProbeTLB` | 192 | `lib/ultralib/src/os/probetlb.s` |
| `func_8004CFA0` | `__osSetCause` | 16 | `lib/ultralib/src/os/setcause.s` |
| `func_80058350` | `__osSetCompare` | 16 | `lib/ultralib/src/os/setcompare.s` |
| `func_80051E50` | `__osSetCount` | 16 | `lib/ultralib/src/os/setcount.s` |
| `func_80052050` | `__osSetSR` | 16 | `lib/ultralib/src/os/setsr.s` |

The include-only wrappers use native IDO 5.3 `cc`/`as0`/`as1`, the SDK assembly
flags and `BUILD_VERSION=6`, with `-O1 -mips2` (`bcmp`/`bcopy` use `-O2`). No
extracted instructions, binary blobs, or instruction rewriting are introduced.
`ultralib-asm` provenance checks require exactly the declared SDK include.
The native symbol-table normalization changes only metadata and relocation
symbol indices, leaving assembled instructions and data intact. The resolver
ignores unused undefined SDK labels while retaining actual allocated-section
references. Regression tests check these invariants and SDK entry aliases.

## Validation

- `tools/check_functions.py -j4`: 5,116 functions in 473 files, zero failures.
- `make rom COMPARE=1`: all 260 linked images and the full 16,777,216-byte ROM
  identical; SHA-256 `ed9f7cd7da795467c1e2b08ed1f878ff5aed906eae9ffe252074aef7a6703d8b`.
- `make test`: assembly regeneration check and all 72 tests pass, including
  seven SDK tests with native assembler and GNU MIPS linker available.
- The first full-ROM pass preceded ledger promotion. A final pass with the
  promoted ledger supplies the committed receipt and generated coverage.

## Coverage and dependencies

Based on master `f4d70eb07254ccc221490545d0b4d6600b9c33ab`; no PR dependencies.
Existing PR #52's ongoing matching work and PR #53's glossary work are independent
and are not counted here. Upstream's C implementation of `sqrtf` is preserved.

The complete conservative inventory is 5,444 owners: 5,315 C (unchanged),
12 original SDK assembly, and 117 still using extracted assembly. C or original
SDK source covers 5,327 / 5,444 owners (97.9%), 1,152,476 text bytes (88.4%).
Upstream's ordinary C denominator remains 5,413, excluding 31 handwritten
assembly owners: 5,315 / 5,413 C (98.2%); 98 ordinary owners remain extracted.
Of the 31 handwritten owners, 12 now use original SDK source and 19 remain
extracted. Full source matching has not been achieved.

The three already identified SDK owners still extracted are `__osSetFpcCsr`
(16 bytes) and the two thread helpers from `exceptasm.s` (88 bytes). Their
existing mixed-source files need separate integration; this batch preserves
them. Other handwritten and ordinary owners remain for subsequent work.
Private ROMs, extracted listings/assets, native tools, and build output remain
local and ignored. No PR is merged automatically.
