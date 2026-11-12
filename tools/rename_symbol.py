#!/usr/bin/env python3
"""Rename symbols across the repository.

Usage:
    tools/rename_symbol.py OLD NEW
    tools/rename_symbol.py --map renames.txt     # one "OLD NEW" pair per line

Whole-word replacement in src/, include/, linker_scripts/jp/, yamls/ and
docs/function-matches.csv (c_name column only). It refuses to rename onto a name that already
exists, so two symbols never merge by accident. Run `make rom` afterwards;
a rename changes no code, but a missed reference fails the link.
"""
import argparse
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
DIRS = ["src", "include", "linker_scripts/jp", "yamls"]
FILES = ["docs/function-matches.csv"]
EXTS = (".c", ".h", ".txt", ".ld", ".yaml", ".inc", ".csv")


def targets():
    for d in DIRS:
        for dirpath, _, files in os.walk(os.path.join(ROOT, d)):
            for f in files:
                if f.endswith(EXTS):
                    yield os.path.join(dirpath, f)
    for f in FILES:
        yield os.path.join(ROOT, f)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("old", nargs="?")
    ap.add_argument("new", nargs="?")
    ap.add_argument("--map")
    args = ap.parse_args()
    pairs = []
    if args.map:
        for line in open(args.map):
            line = line.split("#", 1)[0].split()
            if len(line) == 2:
                pairs.append(tuple(line))
    elif args.old and args.new:
        pairs.append((args.old, args.new))
    else:
        ap.error("give OLD NEW or --map")
    mapping = dict(pairs)
    if len(mapping) != len(pairs):
        sys.exit("duplicate OLD names in map")
    paths = list(targets())
    texts = {p: open(p, encoding="utf-8", errors="surrogateescape").read() for p in paths}
    words = set()
    for t in texts.values():
        words.update(re.findall(r"\b[A-Za-z_]\w*\b", t))
    news = set(mapping.values())
    if len(news) != len(mapping):
        sys.exit("two OLD names map to the same NEW name")
    clash = sorted(n for n in news if n in words and n not in mapping)
    if clash:
        sys.exit("NEW names already in use: " + ", ".join(clash[:20]))
    rx = re.compile(r"\b(" + "|".join(re.escape(k) for k in sorted(mapping, key=len, reverse=True)) + r")\b")
    changed = 0
    for p, t in texts.items():
        if p.endswith("function-matches.csv"):
            # Column 1 (owner) is the address-keyed owner id; only c_name (column 4) is a C name.
            out = []
            for line in t.split("\n"):
                cols = line.split(",")
                if len(cols) > 3:
                    cols[3] = rx.sub(lambda m: mapping[m.group(1)], cols[3])
                out.append(",".join(cols))
            n = "\n".join(out)
        else:
            n = rx.sub(lambda m: mapping[m.group(1)], t)
        if n != t:
            with open(p, "w", encoding="utf-8", errors="surrogateescape") as fh:
                fh.write(n)
            changed += 1
    # A func_XXXXXXXX name implies its address; a real name needs a symbol_addrs entry.
    sym = os.path.join(ROOT, "linker_scripts/jp/symbol_addrs.txt")
    have = set(re.findall(r"^(\w+)\s*=", open(sym).read(), re.M))
    add = [f"{new} = 0x{old[5:]}; // type:func" for old, new in pairs
           if re.fullmatch(r"func_[0-9A-F]{8}", old) and new not in have]
    if add:
        with open(sym, "a") as fh:
            fh.write("\n".join(add) + "\n")
    print(f"renamed {len(mapping)} symbols in {changed} files; {len(add)} symbol_addrs entries added")


if __name__ == "__main__":
    main()
