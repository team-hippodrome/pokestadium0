# Stadium Zero library overlap

This is a ROM-backed first-pass library comparison dated 2026-10-10, not a donor-C compiler verification or source landing. Stadium 1 is the stronger starting point in the scoped results below; Stadium 2 independently corroborates several common routines. Results come from `library-overlap.csv`, `summary.json`, and `tools/compare_library_overlap.py`.

## Inputs and scope

- **Zero:** Japanese original, local input MD5 `c46e087d966a35095df96799b0b4ffae`, SHA256 `ed9f7cd7da795467c1e2b08ed1f878ff5aed906eae9ffe252074aef7a6703d8b`. All 5,444 current assembly-owner ranges were read, their input hashes checked, and restored fragment hashes checked against the mapping manifest.
- **Stadium 1:** US v1.0 ROM MD5 `ed1378bc12115f71209a77844965ba50`, matching the donor README target. The inspected [Stadium 1 repository revision](https://github.com/michiiik/pokestadium/tree/61ab5896988e55a1355dcaae7c4302785ea97f21) supplies 501 named function extents in library-labeled resident segments.
- **Stadium 2:** US ROM MD5 `1561c75d11cedf356a8ddb1a4a5f9d5d`, matching the donor README target. The inspected [Stadium 2 repository revision](https://github.com/michiiik/pokestadiumgs/tree/d3def6af9ae318ea8ceb1872d54985ec255b1244) supplies 282 named function extents in library-labeled resident segments.
- **Boundary evidence:** donor `yamls/us/rom.yaml` provides module extents; `linker_scripts/us/symbol_addrs*.txt` provides entry points. An extent runs to the next named entry in that module, or its module end. These are inferred symbol extents, not recovered original C function-size metadata.
- **Coverage difference:** Stadium 1 names `libultra`, `libnaudio`, `libleo`, `libnumus`, and `libgsm` segments. The current Stadium 2 YAML labels only `libultra` as library segments; its unlabelled audio/game code was not searched as an independently classified library inventory. This is not evidence that Stadium 2 lacks those libraries.

## Results

Counts in this table are donor function extents, not pair counts and not landed C functions. Each donor entry is assigned its strongest tier; exact results and address-masked results are mutually exclusive.

| Donor | Extents tested | Entire extent byte-identical | Code identical, padding differs | Address-masked candidates | No whole-owner hit |
|---|---:|---:|---:|---:|---:|
| Stadium 1 US | 501 | 90 | 2 | 123 | 286 |
| Stadium 2 US | 282 | 46 | 3 | 23 | 210 |

For triage, require a unique Zero owner for a donor hit and at least 32 canonical code bytes. This arbitrary minimum reduces tiny-function collisions; it is not proof of semantics or compilation.

| Donor | Entire extent identical, qualified | Padding-only difference, qualified | Address-masked, qualified |
|---|---:|---:|---:|
| Stadium 1 US | 56 | 2 | 101 |
| Stadium 2 US | 26 | 3 | 18 |

Deduplicating both donor sets gives **58 distinct qualified exact-code Zero owners**, totalling **7,768 canonical code bytes**, and **101 additional qualified address-masked owners**. All 159 qualified owners are resident code, and the Stadium 2 qualified results do not add an owner beyond the Stadium 1 set. These figures are deliberately narrower than the 394 raw candidate owners, which include short/ambiguous patterns.

### Stadium 1 library breakdown

| Library | Tested | Entire extent exact | Padding-only | Address-masked | No hit |
|---|---:|---:|---:|---:|---:|
| libultra | 263 | 80 | 1 | 64 | 118 |
| libnaudio | 44 | 2 | 1 | 29 | 12 |
| libleo | 81 | 1 | 0 | 28 | 52 |
| libnumus | 104 | 7 | 0 | 2 | 95 |
| libgsm | 9 | 0 | 0 | 0 | 9 |

Stadium 2's scoped libultra inventory yields 46 entire-extent exact hits, 3 padding-only hits, 23 masked candidates and 210 no-hits. This comparison supports prioritizing Stadium 1 library reuse investigations, but unequal classification coverage prevents using the totals as a global cross-game similarity measure.

## Concrete candidates

Names below are donor symbol identities associated with matching bytes, not newly landed Zero semantic names. Zero retains its existing pragma owner names.

| Donor routine | Zero owner | Evidence | Canonical bytes |
|---|---|---|---:|
| `_bcopy` | `func_80058410` | Entire extent exact in both donors | 784 |
| `bzero` / `_bzero` | `func_8004FD20` | Entire extent exact in both donors | 156 |
| `__ll_div` | `func_8004DBCC` | Entire extent exact in both donors | 92 |
| `memcpy` | `func_80056690` | Stadium 1 extent exact; Stadium 2 differs only in padding | 44 |
| `strlen` | `func_800566BC` | Entire extent exact in both donors | 40 |
| `strchr` | `func_800566E4` | Stadium 1 extent exact; Stadium 2 differs only in padding | 64 |
| `guMtxF2L` | `func_80053330` | Stadium 1 entire extent exact | 256 |
| `guMtxCatF` | `func_80055410` | Stadium 1 entire extent exact | 360 |
| `osInvalDCache` | `func_80056730` | Entire extent exact in both donors | 172 |
| `osInvalICache` | `func_80056810` | Entire extent exact in both donors | 116 |
| `Audio_RelocatePointerArray` | `func_8003A598` | Stadium 1 entire extent exact | 160 |
| `leoVerifyRTC` | `func_8004B810` | Stadium 1 entire extent exact | 176 |
| `osSendMesg` | `func_8004CFB0` | Address-masked candidate in both donors | 332 |
| `osRecvMesg` | `func_8004D1C0` | Address-masked candidate in both donors | 312 |
| `n_alAudioFrame` | `func_80044790` | Stadium 1 address-masked candidate | 360 |
| `n_alSynNew` | `func_800444C0` | Stadium 1 address-masked candidate | 720 |
| `n_alAdpcmPull` | `func_80046B20` | Stadium 1 address-masked candidate | 1,084 |

The source for the basic string routines is present in [Stadium 1 ultralib string.c](https://github.com/michiiik/pokestadium/blob/61ab5896988e55a1355dcaae7c4302785ea97f21/lib/ultralib/src/libc/string.c). The inspected [Stadium 1 osSendMesg source](https://github.com/michiiik/pokestadium/blob/61ab5896988e55a1355dcaae7c4302785ea97f21/lib/ultralib/src/os/sendmesg.c) is also available as a source-reuse starting point, not an already verified Zero compiler match.

## Comparison rules

- **Exact extent:** all bytes of the donor symbol extent equal the whole Zero owner extent, including any included alignment words.
- **Padding-only:** code bytes equal after removing zero alignment words following a terminal `jr ra` or direct `j` plus its delay slot. The delay slot is never stripped. An internal return followed by nonzero instructions does not trigger trimming.
- **Address mask:** direct `j`/`jal` retain their opcode but lose the 26-bit target. Adjacent `lui` and compatible low-address instructions are masked only if they use the same base register and reconstruct an address in `0x80000000..0xBFFFFFFF`. Registers, branch displacements, stack offsets and non-address immediates remain unchanged.
- **Mask limitations:** non-adjacent HI/LO pairs are deliberately untouched. Masked hits do not validate the identity of callees or global objects; exact equality of remaining words does not establish semantics.
- **No loose opcode tier:** instruction-only/mnemonic similarity was not used or counted. It would be weaker evidence than the tiers reported here.
- **No arbitrary substring promotion:** comparisons require whole-owner equality after the stated transformations. Callable aliases inside shared Zero owners were not separately split, so a no-hit may reflect boundaries or layout rather than absent code.

## Source integration gates

The [Stadium 1 Makefile](https://github.com/michiiik/pokestadium/blob/61ab5896988e55a1355dcaae7c4302785ea97f21/Makefile) selects `ULTRALIB_VERSION := I_P` and `ULTRALIB_TARGET := libultra_rom`. The [Stadium 2 Makefile](https://github.com/michiiik/pokestadiumgs/blob/d3def6af9ae318ea8ceb1872d54985ec255b1244/Makefile) selects version `L` and target `libultra`. These inspected settings are donor facts, not a recovered SDK version for Zero.

No donor library was compiled during this pass, no Zero pragma was replaced, and no functions were renamed. Before import or landing, confirm source availability and attribution, reproduce the applicable donor production-toolchain baseline, recover Zero's compiler/SDK configuration, compare fresh compiled objects and resolved address references, and establish Zero's extraction/link/data/full-ROM verifier. Recomp attribution remains Team Hippodrome; the decomp follows pret conventions without implying pret involvement in the recomp.

## Reproduction

Use the pinned donor revisions above. With supplied local ROMs and donor clones under `.analysis/reference`, run the following PowerShell commands with a Python environment containing `requirements-overlap.txt`:

```powershell
python -m unittest discover -s tools -p "test_*.py" -v
python tools/compare_library_overlap.py `
    --stadium1-rom "path/to/Stadium1-USA.z64" `
    --stadium2-rom "path/to/Stadium2-USA.z64" `
    --zero-rom "baseroms/jp/baserom.z64"
```

The scanner validates ROM identity before comparison and writes only metadata, hashes, counts and offsets. Retail ROM bytes, extracted assets, generated assembly, and donor libraries are not added to this report bundle.

## Validation and sanity check

The full local test suite passed **45 tests**, including 10 synthetic scanner controls and the existing 35 mapping/flow/pragma tests. The successful scan verified every Zero owner input hash and both donor ROM MD5s; `summary.json` records donor revisions and SHA256s.

This is a bounded comparison of current inferred owner extents against explicitly library-labeled resident donor modules, not an exhaustive function-recovery proof. Small repeated routines can match coincidentally; the 32-byte/unique-owner filter is a triage convention. Zero SDK identity, donor C codegen for Zero, reference/object relocation identity, production build baselines, source-integration fidelity, and a full rebuilt Zero ROM are unverified.
