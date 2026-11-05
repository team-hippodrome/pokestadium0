# Production ROM build

`make rom` builds a byte-identical Stadium Zero JP ROM from `src/`, extracted
opaque assets, and retained storage metadata. Every file listed in
`config/jp/sources.json` is compiled whole through
asm-processor, so its C functions and its `GLOBAL_ASM` owners come out of one
object. 4,721 of the 5,444 code owners are C; the remaining 723 are assembled
from the extracted listings. Current verified counts are in [COVERAGE.md](../COVERAGE.md). The build links the resident image and all 259
fragment images independently, preserving the fragments that share link
addresses. The verified output is 16,777,216 bytes:

```text
SHA-256 ed9f7cd7da795467c1e2b08ed1f878ff5aed906eae9ffe252074aef7a6703d8b
```

## Setup and commands

Install Python 3, GNU make, and GNU MIPS binutils (`mips-linux-gnu-as`, `ld`,
`objcopy`, `nm`). Put the privately supplied ROM at `baseroms/jp/baserom.z64`.

```sh
make init       # pinned Python packages, IDO, extraction
make rom        # COMPARE=1 by default; rebuilds objects and links every image
make test       # assembly regeneration check and repository tests
make coverage   # regenerate coverage from the verified receipt
```

`make setup` downloads the official `decompals/ido-static-recomp` v1.2 IDO 5.3
and 7.1 archives, verifies pinned SHA-256s, and installs them under the ignored
`tools/ido5.3` and `tools/ido7.1`.
macOS and Linux x86-64/ARM64 archives are supported; native validation was on
macOS ARM64. Override `IDO_CC` (5.3), `IDO71_CC`, `MIPS_BINUTILS_PREFIX`, `PYTHON`, or `JOBS` through
make variables or a local `.make_options`. Python dependencies are pinned by
`requirements-mapping.txt`.

The build does not need m2c installed. To generate further candidates, clone
`matt-kempster/m2c` into ignored `tools/m2c` and use `tools/m2c_easiest.py`.
m2c is the only C generation engine used by these batches.

Output is `build/pokestadium0-jp.z64`. Per-image ELF objects, generated linker
scripts, and maps live under `build/production/`. `make diff-init` builds these
artifacts. `make clean` removes build output while preserving private extraction
and tools; `make distclean` preserves them as well. `make rom ASM_ONLY=1` rebuilds
all 5,444 owners from assembly as an independent baseline.

## How `src/` files are built

* Compiler flags are IDO 7.1 `-O2 -mips2 -G 0` with the Stadium 1 defines.
  Files under `src/libultra/` that are just `#include "lib/ultralib/src/..."`
  have `"profile": "ultralib"` in `tools/cflags_overrides.json`: they are built
  with IDO 5.3 and ultralib's own 2.0I flags (the `-O1`/`-O2`/`-O3` choice
  follows `lib/ultralib/Makefile.ido`), without asm-processor.
  `tools/cflags_overrides.json` selects IDO 5.3 (libleo and the JPEG code)
  or `-signed` (`hal_libc.c`) per file.
* `GLOBAL_ASM` pragmas are pointed at normalized copies of the listings (the
  same `canonical_assembly` used for assembly owners, so `move`, control
  registers, division and 64-bit transfers keep their exact encodings).
  asm-processor (`tools/asm-processor`, upstream plus one change that lets
  `.set` toggles through) splices them into the object. Its prelude is
  `tools/asm_prelude.inc`.
* A file's object is placed at its first owner and must cover the file's owner
  span. IDO pads `.text` to 16 bytes; that padding may be dropped only when it
  is zero. When the last owner carries more padding than the object emits, the
  remainder comes from the erased (zero) owner bytes, and the image comparison
  checks it. An owner of another file inside a span is an error.
* `.text` is always linked. A file's own `.rodata`, `.data` or `.bss` is linked
  only when `config/jp/sections.json` gives its address; otherwise it is
  discarded and a reference to it fails the link. A placed `.rodata`/`.data`
  replaces the extracted asset bytes at that address (the image comparison
  checks them). Runtime `.bss` outside the stored image is `NOLOAD`. BSS
  addresses inside the stored image use non-allocating `INFO` sections: some
  fragments reuse relocation storage as scratch, so their original stored bytes
  must remain present while C references resolve to the runtime addresses. Both
  section sizes and the complete image bytes are still checked. Functions whose data cannot be
  placed yet are kept behind `#ifdef NON_MATCHING`.
* `tools/place_sections.py [--unwrap] src/file.c` solves those addresses: it
  compiles the file as the build does and solves every `.text` relocation into
  the file's data sections against the retail instructions, requiring one base
  per section. `--unwrap` first turns the file's held functions into plain C.
  This fails when `GLOBAL_ASM` functions' literals sit between the C functions'
  literals, because the object then lacks those bytes. When the next object's
  data starts inside a section's 16-byte zero padding (for example `DDC0_2.c`
  and `DDC0_3.c`, which are probably one original file), the entry records
  `{"address", "size"}` and only that zero padding is dropped.
* Undefined symbols resolve, in order, to another object in the same image,
  `linker_scripts/jp/symbol_addrs.txt`, or the address in an address-style name.

`config/jp/matching.json` still selects single-function m2c candidates from
`candidates/` for any owner whose file is not in `config/jp/sources.json`. With
every file registered, it currently selects nothing. Seventeen of its candidates
are not yet C in `src/` because their m2c declarations conflict with the
file's headers.

## What the gate verifies

Extraction validates the supplied ROM hash and the established mapping. It
removes every known owner interval from the extracted image assets, replacing
those bytes with zero. The linker includes only opaque gaps from these files;
all owner bytes must come from a newly compiled or assembled object. Tests check
that all 5,444 owner intervals are erased. Unknown ranges, boot code outside the
owner inventory, data, microcode, and resource-only images remain opaque assets.

The linker places each owner at its established image-relative address and
asserts its size. A C object's trailing alignment bytes may be trimmed only
when all trimmed bytes are zero. Address-bearing symbols retain their encoded
link addresses. GNU assembler syntax normalization preserves `addu`/`or` move
aliases, control registers, division instructions, and 64-bit transfers; no
raw-word fallback substitutes for assembly instructions.

For compressed fragments, extraction retains Yay0 masks, backreference topology,
wrapper metadata, restoration placeholders, and padding, while clearing all
literal bytes and restoration values. The builder emits literals and restored
words from the linked image and verifies every backreference. It then decodes
the result independently to check that it restores to the linked bytes. It
does not copy the original compressed code into the output.

The default gate checks every linked image hash and the complete ROM hash.
`build/production/receipt.json` records the result, compiler/binutils identity,
registry hashes, source file hashes, one digest over all headers, and build-tool
hashes. A build invalidates the
previous receipt before compiling, so a failed run cannot leave a success receipt.
The committed `docs/production-build-receipt.json` is the reviewed validation
snapshot. A direct `cmp` also verified the final ROM against the supplied input.

A negative control replaced one accepted function with different m2c-generated
C of the same function size. The compiler consumed it, the linked resident
image changed, and the default comparison failed. Restoring the original C and
building after `make clean` passed. The same control on the whole-file build
(`return temp_v0 != NULL;` in the first function of `src/dma.c`) fails with
`linked image bytes differ: resident`. This checks that C edits affect the actual
output and that the build has no fallback to retail owner bytes.

## Current constraints

This is a fixed-layout build. Owner sizes and image addresses are held constant;
a matching function is promoted by replacing its `GLOBAL_ASM` block in `src/`
with C and passing the full ROM gate. Data, `.rodata`, microcode and other
non-code ranges still come from the extracted assets.

`COMPARE=0` permits nonidentical fixed-layout output, but an owner size change or
an edit incompatible with the retained compression topology fails explicitly.
General relayout and a compressor matching the retail encoder are future work.
The original compiler settings and original function/translation-unit boundaries
remain unconfirmed beyond the individual candidates that now pass the full ROM
gate. No runtime or emulator acceptance is claimed.

Private ROMs, extracted assets and assembly, compiler binaries, and build output
are ignored and must not be committed. CI runs synthetic storage/assembler tests
without a ROM; full-ROM verification requires the private local input.
