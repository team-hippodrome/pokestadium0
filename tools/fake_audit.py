#!/usr/bin/env python3
"""Find likely fakes (decomp slop and karodo) in src/ and rank them by function.

Usage:
    tools/fake_audit.py                 # ranked table of functions
    tools/fake_audit.py --unmarked      # suspicious lines that carry no FAKE/karodo comment
    tools/fake_audit.py --json out.json

The detector is heuristic. It flags code shapes that only exist to steer IDO's
register allocation or stack layout; a human or agent still decides whether a
flagged line is really a fake. Lines that already carry `// FAKE` or `// karodo`
(on the line itself or on the line above) count as marked.
"""
import argparse
import json
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
SKIP_DIRS = ("src/libultra", "src/libleo", "src/libnaudio", "src/libgsm")

# (name, regex, weight, kind). kind is "slop" or "karodo".
PATTERNS = [
    ("xor-zero", re.compile(r"\^\s*0\b(?!x)"), 5, "slop"),
    ("or-zero", re.compile(r"\|\s*0\b(?!x)"), 5, "slop"),
    ("plus-minus-nop", re.compile(r"[+-]\s*(\d+)\s*[-+]\s*\1\b"), 6, "slop"),
    ("times-one", re.compile(r"(?<![A-Za-z_)\]])\b[a-z_][a-z_0-9]*\s*\*\s*1\b(?![.0-9x])"), 4, "slop"),
    ("inc-dec-nop", re.compile(r"\b(\w+)(\+\+|--);\s*\1(--|\+\+);"), 6, "slop"),
    ("self-assign", re.compile(r"(?<![.>\w])(\w+)\s*=\s*\1\s*;"), 6, "slop"),
    ("double-not", re.compile(r"!!"), 3, "slop"),
    ("comma-expr", re.compile(r"(?:^|[^\w\s\]])\s*\(\s*0\s*,\s*[^,()]+\)"), 8, "slop"),
    ("permuter-var", re.compile(r"\bnew_var\d*\b"), 3, "slop"),
    ("expanded-macro", re.compile(r"_g->words\.w[01]\s*="), 2, "slop"),
    ("stack-pad", re.compile(r"\b(s32|u32|s8|u8|s16|u16|char|f32)\s+(pad|sp_?pad|unused|padding)\w*\s*(\[|;)"), 3, "slop"),
    ("register-kw", re.compile(r"\bregister\s"), 3, "slop"),
    ("void-cast-stmt", re.compile(r"^\s*\(void\)\s*\w+\s*;"), 2, "slop"),
    ("cast-chain", re.compile(r"\*\s*\(\(\s*\w+\s*\*+\s*\)\s*\(+\s*\w+\s*\*+\s*\)"), 4, "slop"),
    ("ptr-offset-cast", re.compile(r"\(\s*\(\s*(u8|s8|char)\s*\*\s*\)\s*[\w>.-]+\s*\+\s*0x[0-9A-Fa-f]+\s*\)"), 1, "slop"),
    ("m2c-field", re.compile(r"\bM2C_FIELD\("), 1, "slop"),
    ("m2c-error", re.compile(r"\bM2C_(ERROR|TRAP_IF|BREAK|CARRY|OVERFLOW)\b"), 8, "slop"),
    ("empty-if", re.compile(r"\bif\s*\([^;{}]*\)\s*\{\s*\}"), 3, "karodo"),
    ("empty-loop", re.compile(r"(?<!\}\s)(?<!\})\b(for|while)\s*\((?:[^;{}()]|\([^()]*\))*(;[^;{}]*;[^{}]*)?\)\s*(\{\s*\}|;)"), 3, "karodo"),
    ("do-while-0", re.compile(r"\}\s*while\s*\(\s*0\s*\)"), 3, "karodo"),
    ("goto", re.compile(r"\bgoto\s+\w+"), 2, "slop"),
]

MARK_RE = re.compile(r"//\s*(FAKE|karodo)|/\*\s*(FAKE|karodo)", re.I)
FUNC_START_RE = re.compile(r"^(?:static\s+)?(?:inline\s+)?[A-Za-z_][\w\s\*]*?\b(\w+)\s*\([^;]*\)\s*\{?\s*$")


def strip_comments(line):
    line = re.sub(r"/\*.*?\*/", "", line)
    return line.split("//", 1)[0]


def iter_sources():
    for dirpath, _, files in os.walk(os.path.join(ROOT, "src")):
        rel = os.path.relpath(dirpath, ROOT)
        if rel.startswith(SKIP_DIRS):
            continue
        for f in sorted(files):
            if f.endswith(".c"):
                yield os.path.join(rel, f)


def scan_file(path):
    with open(os.path.join(ROOT, path), encoding="utf-8", errors="replace") as fh:
        lines = fh.read().split("\n")
    funcs = []
    depth = 0
    cur = None
    in_block_comment = False
    in_asm = False
    for i, raw in enumerate(lines):
        if raw.startswith("#pragma GLOBAL_ASM") or raw.startswith("GLOBAL_ASM"):
            continue
        code = raw
        if in_block_comment:
            if "*/" in code:
                code = code.split("*/", 1)[1]
                in_block_comment = False
            else:
                continue
        if "/*" in code and "*/" not in code.split("/*", 1)[1]:
            code = code.split("/*", 1)[0]
            in_block_comment = True
        code = strip_comments(code)
        if depth == 0 and cur is None:
            m = FUNC_START_RE.match(code)
            if m and not code.strip().startswith(("if", "for", "while", "switch", "typedef", "struct")):
                cur = {"name": m.group(1), "file": path, "line": i + 1, "hits": [], "lines": 0}
        if cur is not None and depth > 0:
            marked = bool(MARK_RE.search(raw)) or (i > 0 and bool(MARK_RE.search(lines[i - 1])) and lines[i - 1].strip().startswith("//"))
            for name, rx, w, kind in PATTERNS:
                if rx.search(code):
                    cur["hits"].append({"line": i + 1, "pattern": name, "weight": w, "kind": kind,
                                        "marked": marked, "text": raw.strip()})
        opens = code.count("{")
        closes = code.count("}")
        depth += opens - closes
        if cur is not None:
            if depth > 0 or opens:
                cur["lines"] += 1
            if depth == 0 and (opens or closes):
                funcs.append(cur)
                cur = None
            elif depth == 0 and code.strip().endswith(";"):
                cur = None  # was a prototype
    for f in funcs:
        f["marked"] = sum(1 for h in f["hits"] if h["marked"])
        f["score"] = sum(h["weight"] for h in f["hits"])
    return [f for f in funcs if f["hits"]]


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--unmarked", action="store_true", help="list flagged lines without a FAKE/karodo comment")
    ap.add_argument("--json")
    ap.add_argument("--top", type=int, default=60)
    ap.add_argument("--exclude", default="m2c-field,ptr-offset-cast",
                    help="patterns left out of --unmarked (they are untyped access, handled by struct work)")
    args = ap.parse_args()
    funcs = []
    for path in iter_sources():
        funcs.extend(scan_file(path))
    if args.json:
        with open(args.json, "w") as fh:
            json.dump(funcs, fh, indent=1)
    if args.unmarked:
        skip = set(args.exclude.split(",")) if args.exclude else set()
        for f in funcs:
            for h in f["hits"]:
                if not h["marked"] and h["pattern"] not in skip:
                    print(f"{f['file']}:{h['line']}: [{h['pattern']}] {f['name']}: {h['text']}")
        return
    funcs.sort(key=lambda f: -f["score"])
    print(f"{'score':>5} {'marked':>6}  function  (file:line)  patterns")
    for f in funcs[: args.top]:
        pats = {}
        for h in f["hits"]:
            pats[h["pattern"]] = pats.get(h["pattern"], 0) + 1
        desc = ", ".join(f"{k}x{v}" for k, v in sorted(pats.items(), key=lambda kv: -kv[1]))
        print(f"{f['score']:>5} {f['marked']:>6}  {f['name']}  ({f['file']}:{f['line']})  {desc}")


if __name__ == "__main__":
    sys.exit(main())
