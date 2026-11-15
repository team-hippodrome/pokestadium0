# Stadium Zero conditional pragma scaffold

The source tree now contains **5,444 first-pass assembly owners in 188 C files**, using `#ifdef NON_MATCHING` / `#else` / `#pragma GLOBAL_ASM(...)` / `#endif`. Runtime capture is not required to preserve an unresolved indirect transfer inside an assembly owner; all 71 watchlist sites are included.

The later [production build](production-build.md) now assembles this inventory,
compiles the explicit C registry, and passes the full-ROM gate. The scaffold
source files retain their TODO slots; the registry selects C directly from
`candidates/`. The extraction and first-pass boundary caveats below still apply.

## Source layout and conditional pattern

`src/main.c` owns the scoped resident CPU text after the boot entry. `src/fragments/fragmentNNN_ROMOFFSET.c` contains one source unit per executable fragment image, including independently named images that reuse the `0x8FF00000` link slot. There are 187 fragment source units and one resident source unit.

Each block has this layout:

```c
#ifdef NON_MATCHING
/* TODO: decompile func_80000460; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_80000460.s")
#endif
```

The conditional direction follows the inspected [Stadium 1 example](https://github.com/michiiik/pokestadium/blob/61ab5896988e55a1355dcaae7c4302785ea97f21/src/misc_stubs.c). Region-specific `asm/.../nonmatchings/...` pragma paths also appear in the inspected [Stadium 2 source](https://github.com/michiiik/pokestadiumgs/blob/7c7d7fe15dc948bafcb35ddfd05541a3c3f852a8/src/10BB0.c).

The `NON_MATCHING` branch is deliberately a TODO slot, not a fabricated `void` function or guessed ABI. Defining that flag removes the pragma until a real C candidate is added; this is not a functioning nonmatching game build.

## Static extraction and boundaries

The generator uses pinned spimdisasm `1.42.4` against only the established resident CPU envelope and the 187 fragment candidate text prefixes. It never scans the whole ROM as CPU text. Compressed images are decoded and restored through the existing validated manifest.

Default IDO-oriented boundary detection is a disassembly heuristic, not confirmation of the original compiler. Non-call branches and resolved switch/dispatch edges crossing inferred boundaries are conservatively kept in one assembly owner. Thirty-four additional callable labels are preserved as aliases inside shared owners, rather than forcing switch cases or coroutine continuations into separate source functions.

Reused slots get unique names such as `func_8FF00020_106` inside `fragment106_5009A0.c`. The suffix identifies the image, not a recovered semantic name.

One 900-byte resident candidate range, ROM `[0xA1CC,0xA550)`, is excluded because it contains invalid CPU instruction encodings. The generator restarts clean-region analysis with fresh contexts so calls decoded from that invalid span cannot seed fake functions elsewhere. The meaning or restoration of this range is unresolved; it is not silently relabelled as a function.

The generated owners cover 1,303,636 text bytes. These are assembly-owner ranges, not a verified original function count, recovered translation-unit partition, or matching-C coverage figure.

## Reproduction

Since the [first matching pass](matching.md) split and edited `src/`, regenerate only the assembly with `tools/generate_pragmas.py baseroms/jp/baserom.z64 --asm-only`; the source-file description below is the original scaffold layout.

The repo contains C pragma owners, the generator, tests, and `docs/pragma-inventory.json`. Assembly is generated under ignored `asm/jp/nonmatchings/`; neither a ROM nor retail resource binaries are added to Git.

On Windows, from the repo root:

```powershell
python -m venv .venv
& .\.venv\Scripts\python.exe -m pip install -r requirements-mapping.txt
& .\.venv\Scripts\python.exe tools/generate_pragmas.py baseroms/jp/baserom.z64
& .\.venv\Scripts\python.exe tools/generate_pragmas.py baseroms/jp/baserom.z64 --check
& .\.venv\Scripts\python.exe tools/test_pragmas.py
```

The tested Linux sandbox uses `.venv/bin/python` instead of `.venv\Scripts\python.exe`. The input SHA256 remains `ed9f7cd7da795467c1e2b08ed1f878ff5aed906eae9ffe252074aef7a6703d8b`.

The generator refuses to overwrite a C source edited since its recorded generated hash. This protects future C candidates; regenerated output is not allowed to erase human work merely because its generated banner remains.

## Verification and sanity check

Tests check every pragma path, conditional block, unique symbol name, resource-only exclusion, unresolved-site ownership, source hash, and scoped assembly-listing bytes. Host C syntax checks run in both conditional modes and are explicitly not asm-processor or IDO builds.

All seven new pragma tests pass, alongside the existing twenty-eight mapping and flow tests, for thirty-five passing tests in this environment. The generator's `--check` also passes against the complete local source and assembly output.

Assembly listing word annotations reproduce each owner's input interval byte-for-byte, and regeneration is deterministic. The original scaffold validation did not prove symbolic mnemonic reassembly.
The production build now supplies assembler syntax normalization, absolute symbol
addresses, fixed linker placement, and the full-ROM gate. Original compiler
settings remain a research question beyond individually accepted candidates.

The runtime capture workstream is paused. These source files are usable decompilation starting points without claiming that indirect target sets or inferred boundaries have become fully verified.
