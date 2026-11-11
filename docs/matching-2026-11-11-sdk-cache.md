# Original SDK cache and low-level routines — 2026-11-11

Eight additional owners (832 text bytes) build from complete, unmodified SDK
assembly already tracked in `lib/ultralib`. They remain assembly in the ledger
and are counted as original SDK source, separately from C.

| Owner | SDK symbol | Bytes | Original source |
| --- | --- | ---: | --- |
| `func_800093D0` | `__assertBreak` | 16 | `lib/ultralib/src/debug/assertbreak.s` |
| `func_8004FD20` | `_bzero` | 160 | `lib/ultralib/src/libc/bzero.s` |
| `func_80056730` | `osInvalDCache` | 176 | `lib/ultralib/src/os/invaldcache.s` |
| `func_80056810` | `osInvalICache` | 128 | `lib/ultralib/src/os/invalicache.s` |
| `func_800594D0` | `__osSetFpcCsr` | 16 | `lib/ultralib/src/os/setfpccsr.s` |
| `func_8004D300` | `osSetIntMask` | 160 | `lib/ultralib/src/os/setintmask.s` |
| `func_80052100` | `osWritebackDCache` | 128 | `lib/ultralib/src/os/writebackdcache.s` |
| `func_8005C0A0` | `osWritebackDCacheAll` | 48 | `lib/ultralib/src/os/writebackdcacheall.s` |

The existing native SDK profile supplies the original assembly recipe. The
`assertbreak` owner moves out of the two-owner `9FC0.c` into an include-only
wrapper. `setfpccsr` likewise moves to an assembly wrapper while the existing
`func_800594E0` C hardware read stays intact. The source registry and ledger
record both boundaries. No C owner is demoted or changed.

`osSetIntMask` also builds its original 128-byte interrupt-mask table. The
section solver places `.rodata` at `0x8007F490`, consistent with the SDK
relocations and retained table bytes; the linked-image gate verifies both.
New linker aliases identify that table, `_bzero`, and `__assertBreak`.
No original SDK source or toolchain binary is modified.

## Validation and counts

- 5,124 function checks in 481 files, zero failures.
- `make rom COMPARE=1`: all 260 images and the complete 16,777,216-byte ROM
  identical, SHA-256 `ed9f7cd7da795467c1e2b08ed1f878ff5aed906eae9ffe252074aef7a6703d8b`.
- `make test`: assembly regeneration check and all 72 tests pass.
- Ledger promotion follows the initial full-ROM pass; the final pass supplies
  the receipt and generated coverage. A direct full-ROM `cmp` also passes.

Based on PR #54; this PR depends on its native SDK integration. PR #52's
ongoing matching and PR #53's glossary changes remain independent and uncounted.

Complete inventory: 5,315 C unchanged, 20 original SDK assembly (+8), and
109 extracted owners remaining. Source coverage is 5,335 / 5,444 (98.0%),
1,153,308 text bytes (88.5%). Ordinary C stays 5,315 / 5,413 (98.2%). The
31 separately listed handwritten owners now comprise 20 original SDK owners
and 11 still extracted; all 98 ordinary remaining owners are extracted.
Full source matching is incomplete and hourly continuation stays enabled.
Private ROMs, extracted assets/listings, compiler binaries, and build output
remain local. No PR is merged automatically.
