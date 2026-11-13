# Stadium Zero indirect-flow and text-gap validation

This refines the prior 259-image executable-section map without turning runtime-dependent callbacks or instruction-looking data into claimed matches. It is a Team Hippodrome original; the decompilation follows pret conventions, and pret is not involved with the recompilation.

## Scope and input

The analysis uses the Japanese-only original Pokémon Stadium input with SHA256 `ed9f7cd7da795467c1e2b08ed1f878ff5aed906eae9ffe252074aef7a6703d8b`. Each restored fragment is checked against the decoded-image hash in `docs/mappings/resident-fragments.json`, including compressed-wrapper restoration patches.

The analysis starts from the private repo's scaffold commit `55dba795d7ac465734a928a5251788044aba49f3`. These results were prepared before publication; repository history records their publication commit. No production compiler or rebuilt-ROM identity milestone is implied.

All offsets below are restored-image offsets. Add the corresponding image's link base for link-time addresses, not necessarily runtime allocation addresses. The method and raw evidence are in `tools/resolve_fragment_flow.py` and `evidence/focused-flow-disassembly.txt`.

## Transfer results

`flow-validation.json` now inventories **288 non-return indirect transfer sites**, compared with 228 in the prior reachable-code inventory. The additional sites were exposed while recovering formerly unseeded code; this is not a count of every possible transfer hidden anywhere in the ROM.

| Classification | Sites | Meaning |
|---|---:|---|
| Bounded static switch tables | 192 | LUI/ADDU/LW/JR sequence, matching unsigned bound and default branch, relocated table words, and valid local targets |
| Inspected masked/byte-indexed dispatch tables | 5 | Handwritten dispatch with a known table base and a bounded byte or masked index |
| Inspected register/coroutine protocols | 20 | Finite branch-selected function sets or paired nonstandard-link continuation sets |
| Known initializer candidates, runtime unresolved | 51 | Context dispatch table has ten inspected initializer targets, but runtime memory/alias writes are not excluded |
| Other runtime-dependent transfers | 20 | Eighteen callback sites in image 12 and two saved-continuation jumps in image 0 |

Thus **217 sites have static target sets and 71 remain runtime-unresolved**. “Resolved” means a target set under the documented static-entry/table contract, not that every target was exercised in an emulator or that runtime table mutation is impossible.

### Bounded switches

Each accepted switch requires more than a run of pointer-like words. The resolver identifies the index shift, an unsigned range check, and the default branch; every selected table word must carry a type-2 relocation and point into the image's checked text prefix.

The reaching-definition check follows the local direct-control-flow subgraph, including delay slots and branch-likely annulment. It does not treat skipped register writes as executed. This matters for image 16's switch at offset `0x2D14`: the bound is computed at `0x2CD4`, and the dispatch path skips intervening instructions that overwrite `$at` on other paths.

The local proof is deliberately scoped: it assumes entry through the inspected compiler-generated dispatch path. Arbitrary runtime entry into the middle of that path is not established or supported.

### Handwritten dispatch

Image 0's table base is initialized to link-time address `0x81152780` at offsets `0x17D9C/0x17DA0` and `0x187CC/0x18804`. The five inspected dispatches are:

| Site offset | Table offset | Entries | Index evidence |
|---|---|---:|---|
| 0x18898 | 0x52780 | 256 | Byte opcode, shifted left by two |
| 0x1A390 | 0x52B80 | 256 | Byte opcode, shifted left by two |
| 0x1BB10 | 0x540C0 | 16 | AND `0xF`, shifted left by two |
| 0x1BB28 | 0x54080 | 16 | AND `0xF`, shifted left by two |
| 0x1BD50 | 0x54100 | 32 | AND `0xF8`, shifted right by one |

Every table word is relocated and every stored target lies inside the checked image-0 prefix. These are input-specific inspected rules, not a universal fragment-format heuristic.

### Nonstandard link protocols

The important correction is not simply to rename `jalr` as a call. Some handwritten code writes a continuation into a register other than `$ra`.

- **Offset `0x3CD8`:** `$s3` selects one of four inspected comparator entries: `0x3BB4`, `0x3BD0`, `0x3BEC`, or `0x3C34`. Those comparators preserve `$s3` during the loop.
- **Offset `0x18594`:** the converter target in `$s5` is either an initial entry (`0x18298` or `0x183C4`) or one of fourteen resume PCs. The converter's `jalr $s5,$ra` instructions transfer back to `0x1859C` while writing the next converter resume PC into `$s5`. The caller's target set therefore has sixteen members, not just two.
- **Offset `0x1BF0C`:** `$v1` holds `0x1BF34`, `0x1BF44`, `0x1BF50`, or `0x1BF5C`. Three `jalr $v1,$ra` instructions resume the caller at `0x1BF14` while updating the unpacker's continuation.

These sets require entry through the inspected paired protocol. Treating the source `$ra` as an ordinary terminal return, or assuming every `jalr` writes `$ra`, loses the continuation edges.

### Runtime-dependent remainder

The 51 image-0 context calls load through the table based at `$fp+0x5C00`, with index computation varying by site. Inspected initialization stores give the following ten local candidates:

`0x1B780`, `0x1B844`, `0x1B8C0`, `0x1B8F0`, `0x1B90C`, `0x1B938`, `0x1B948`, `0x1B954`, `0x1B960`, and `0x1C460`.

The relevant stores are recorded per target in `flow-validation.json`. This is a candidate union across inspected initializer branches, not an exact per-call runtime target set; initialization order, active configuration, and unknown alias writes remain gates.

The two saved-continuation jumps are image-0 offsets `0x18108` and `0x1BBFC`, reading `$fp+0x388` and `$fp+0x354`. They are not mislabelled as bounded switch tables.

The eighteen image-12 callback sites are `0x4CA4`, `0x4CB4`, `0x4CC4`, `0x4D7C`, `0x1643C`, `0x3604C`, `0x36074`, `0x360B0`, `0x3622C`, `0x362E8`, `0x37044`, `0x370B4`, `0x3A748`, `0x3A9AC`, `0x3AA20`, `0x3AA38`, `0x3AA50`, and `0x3AA60`. The ledger records target-register writers, memory displacements, and backward-trace call boundaries rather than inventing function names or static targets.

Static examples show why runtime state matters: the loops at `0x37044` and `0x370B4` walk callback arrays beginning at link-time addresses `0x8219A838` and `0x8219A858`. Their null checks and pointer iteration are inspected in the evidence log; the actual live contents were not captured.

## Candidate-gap results

The prior map had **76,484 bytes** of gaps inside its candidate text prefixes. The new ledger accounts for every one of those bytes:

| Gap outcome | Bytes |
|---|---:|
| Added instruction evidence from references, traversal, and checked entry hypotheses | 64,708 |
| Remaining nonzero instruction candidates | 10,472 |
| Remaining zero words with unproven role | 1,304 |
| Total original candidate bytes | 76,484 |

This promotes approximately 84.6% of the original gap bytes: `64,708 / 76,484 × 100`. Total instruction-evidence coverage increases from **849,076 to 913,784 bytes**.

The remaining nonzero candidates all pass CPU-encoding, delay-slot, and local branch-target structural checks, with **zero structural failures**. They are still candidates: valid instruction structure, even inside a well-supported prefix, does not establish execution or a source-level function boundary. Direct call destinations are recorded by the structural ledger; that check does not independently prove all external callees.

Zero words remain separate. They may be padding, hazard NOPs, or unreachable instructions; no blanket padding declaration was made.

Additional entry hypotheses include relocated pointers into a checked prefix and negative stack adjustments found inside candidate gaps. Their promoted traversals must stay within the prior prefix and produce no rejected instructions or delay slots. These are static evidence rules, not emulator traces; the entry-seed provenance is retained.

Cross-fragment direct references add two entry seeds. Slot reuse stays explicit: the resolver does not choose one image merely because multiple images share a link base. The detailed edge inventory is `cross-fragment-edges.json`.

## Reproduction and validation

Run from the repository root with `requirements-mapping.txt` installed. PowerShell examples for the current Linux sandbox:

```powershell
& ./.venv/bin/python tools/resolve_fragment_flow.py baseroms/jp/baserom.z64
& ./.venv/bin/python tools/test_fragment_flow.py
& ./.venv/bin/python tools/test_fragment_sections.py
& ./.venv/bin/python tools/test_map_rom.py
```

The verification log records fourteen flow tests, eight section tests, and six storage-mapping tests. They cover branch-likely annulment, delay-slot definition arrival, bypassed versus executed register writes, refusal of unrelocated or overlong tables, nonstandard link-register handling, coroutine resume sets, table-target traversal, exact byte partitions, and explicit unresolved treatment of initializer candidates.

Regenerating the refinement is checked for byte-identical output hashes. These tests verify the mapping algorithm's stated invariants, not a game build, complete semantic analysis, or runtime behavior.

## Deliverables

- **`fragment-sections.json` and `.csv`:** updated evidence-labeled sections and per-image inventory.
- **`flow-validation.json`:** per-site target sets, runtime contracts, initializer-store evidence, entry hypotheses, and gap checks.
- **`indirect-transfers.csv`:** all 288 indirect sites, their status, and target/provenance information.
- **`text-gap-validation.csv`:** the accounting ledger for all original candidate-gap bytes.
- **`cross-fragment-edges.json`:** unique-slot and reused-slot direct-reference records.
- **`runtime-watchlist.csv`:** the 71 unresolved sites, target/link registers, inspected memory origins, link-time PCs, and known candidate offsets. Runtime breakpoint PCs must use the actual allocation map, not these link-time PCs blindly.
- **`evidence/`:** focused disassembly, tests, generation summaries, and reproducibility hashes.

No input ROM, decoded fragment binary, or extracted retail resource is included. The authored mapper and tests are preserved alongside these results in the Project.

## Sanity check and remaining gate

This is a substantial static-resolution milestone, not a claim that all indirect transfers or text gaps are solved. The 71 runtime-unresolved sites and 11,776 bytes of remaining candidates retain their explicit uncertainty. The inferred text-envelope bounds themselves have not been proved exhaustive; unseeded code outside those prefixes is not searched by this pass.

The next decisive evidence is a runtime trace capturing the target register before each unresolved transfer, the context or callback-array addresses and contents, and the active fragment allocation map. That can test the initializer assumptions and disambiguate live slots; an observed trace still must not be mistaken for exhaustive gameplay coverage. Production-toolchain identification, source integration, full-ROM rebuilding, and Stadium 1/2 library matching remain separate, unrun gates.
