# GB Tower buffer and resource helpers — 2026-11-02

This batch adds **8 owners / 604 text bytes** built from genuine matching C
beyond PR #28 in `gb_tower_emulator_86920.c`.

| Owner | Behavior | Text bytes |
| --- | --- | ---: |
| `func_8110A848` | Clear eight halfwords in the original grouped store order | 48 |
| `func_8110A878` | Copy an eight-halfword row from the first table | 84 |
| `func_8110A8CC` | Copy an eight-halfword row using the second table's one-based index | 88 |
| `func_8110BEE4` | Update a matching reference address and its two-bit kind | 68 |
| `func_8110CFEC` | Return a byte list after its count prefix, or NULL for an empty list | 104 |
| `func_8110D1B8` | Check the busy flag, clear a slot word, and forward the operation | 92 |
| `func_8110D3D4` | Resolve an index and call the loader with a local output word | 52 |
| `func_8110D840` | Select one of three existing table pointers, defaulting to NULL | 68 |

The table copies use flat halfword arrays and the original eight-element row
stride. This corrects the extra pointer scaling in the initial candidates.
The clear helper retains the retail four-element grouping and store order.
The reference update uses a partial structure with an unsigned-char bitfield
for bits 3:2; it preserves the other bits in the byte and the original signed
source-byte load. The partial structures describe only the fields used here.

The byte-list helper loads its offset as a halfword, advances past the count
byte as an integer, and preserves the live table-pointer reload after writing
the output count. The slot wrapper reuses the existing `0x15C`-byte slot view,
whose declaration moves before its first use without changing its layout.
The load wrapper declares its index before the output word, reproducing the
retail stack slot. The table selector uses a single result variable to retain
the retail return paths.

No inline assembly, instruction words, code blobs, or comparison exceptions
were introduced. Other private GB Tower candidates still differ and are not
counted as matches.

Verified totals: **4,453 / 5,444 C owners (81.8%)**, **812,248 text bytes
(62.3%)**, and **991 remaining assembly owners**. Full source matching remains
incomplete. No recorded matching C is held for data placement.

Validation: `make rom` with comparison enabled passes all **260 linked images**
and the complete **16,777,216-byte ROM**, SHA-256
`ed9f7cd7da795467c1e2b08ed1f878ff5aed906eae9ffe252074aef7a6703d8b`.
Direct checks pass **4,256 functions in 426 files**, with zero failures.
All **65 tests pass**. The ledger, coverage, and production receipt describe
this passing build.

Depends on [PR #28](https://github.com/team-hippodrome/pokestadium0/pull/28)
and targets its branch. Private ROMs, extracted assembly/assets, compiler
binaries, and toolchains remain local.
