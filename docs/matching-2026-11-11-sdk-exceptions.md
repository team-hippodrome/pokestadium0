# Original SDK exception and thread assembly — 2026-11-11

The complete, unmodified `lib/ultralib/src/os/exceptasm.s` now supplies five
conservative inventory owners (2,320 text bytes), replacing their extracted
listings in `src/libultra/os/exceptasm.c`. These owners count as original SDK assembly, not C.
The SDK's `Makefile.ido` specifies IDO 5.3 `-O1 -mips3 -32` for this file.

| Inventory owner | SDK function entries | Bytes |
| --- | --- | ---: |
| `func_8004DD80` | __osExceptionPreamble, __osException, send_mesg, handle_CpU | 1580 |
| `func_8004E3AC` | __osEnqueueAndYield | 256 |
| `func_8004E4AC` | __osEnqueueThread | 72 |
| `func_8004E4F4` | __osPopThread | 16 |
| `func_8004E504` | __osDispatchThread, __osCleanupThread | 396 |

The original 32-byte `.data` section is placed at `0x80077BF0` and the 80-byte
`.rodata` section at `0x8007F560`. The section solver derives these addresses
from original relocations; all references agree and the linked resident image
verifies the table contents. Established SDK entry/state aliases resolve
references without modifying original source. Local SDK assembly headers are
included in the receipt's header digest.

The first-pass owner inventory combines some real SDK functions. The checker
now compares each native function's complete instruction interval within its
containing owner, rejecting empty/unknown extents, misalignment, other image
segments, and intervals crossing an owner boundary. Two synthetic regressions
verify internal-entry comparison (including a deliberate instruction change)
and boundary rejection. Another verifies that changes to a local SDK header
invalidate the receipt digest. This changes neither the owner denominator nor
any C check. The full-ROM comparison remains the final gate for all padding,
relocations, data, and placement.

## Validation and counts

- 5,133 function checks in 482 files, zero failures. This includes nine actual
  entries in the five newly sourced inventory owners.
- `make rom COMPARE=1`: all 260 images and the full 16,777,216-byte ROM identical,
  SHA-256 `ed9f7cd7da795467c1e2b08ed1f878ff5aed906eae9ffe252074aef7a6703d8b`.
- `make test`: assembly regeneration and all 75 tests pass (10 SDK regressions).
- The first full-ROM pass preceded ledger promotion; the final pass supplies
  the receipt and generated coverage. Direct full-ROM `cmp` also passes.

Depends on PR #55 (which depends on #54). PR #52's ongoing matching and #53's
glossary work remain independent and are not counted here.

Complete inventory: 5,315 C unchanged + 25 original SDK assembly (+5) =
5,340 / 5,444 source-covered owners (98.1%), 1,155,628 text bytes (88.6%).
104 extracted owners remain: 98 ordinary and six handwritten. Ordinary C stays
5,315 / 5,413 (98.2%). The handwritten remainder consists of the custom watch
register setter, the early resident low-level routine, the resident decompressor,
the fragment jump-stub table, and the two GB emulator assembly owners.
Full source matching remains incomplete; keep hourly continuation enabled.
Private ROMs, extracted assets/listings, native tools, and build output remain
local. Original SDK source is unchanged and no PR is merged automatically.
