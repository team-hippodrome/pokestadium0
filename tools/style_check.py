#!/usr/bin/env python3
"""Report style-guide violations (CONTRIBUTING.md) in src/.

Usage:
    pip install libclang==18.1.1        # into .venv; not needed for the ROM build
    .venv/bin/python tools/style_check.py [paths...]          # summary per file
    .venv/bin/python tools/style_check.py -v [paths...]       # every finding
    .venv/bin/python tools/style_check.py --rule nodoc -v src/fragments/n64_logo

Paths may be files or directories; the default is every .c and .h under src/
except the vendored libraries. The checker only reports. It never edits, and
make rom / make test stay the real gate. Some rules are heuristics: a finding
is a place to look, not proof of a violation, and the numbers rules
(hex-loop-bound, decimal-mask) only catch the shapes a regex can see.

Rules:
    nodoc            function definition without a /* */ comment directly above
    func-name        named function not in Domain_Purpose form, or over 50 chars
    local-name       argument or local that is not snake_case / argN / var_xx / spXX
    global-name      file-scope variable not gCamelCase / sCamelCase / D_XXXXXXXX
    struct-name      struct/union/typedef tag not TitleCase or unk_*
    jp-untranslated  Japanese string literal without a comment on its line or the line above
    terminology      GB Tower, Poke Cup, Pokeball, yaw/pitch/roll, British spelling, AI for COM
    hex-loop-bound   loop bound written in hex (counts are decimal)
    decimal-mask     bitmask written in decimal (masks are hex)
    color-comment    rgba/color-looking literal without a // #RRGGBB comment nearby
    unmarked-fake    tools/fake_audit.py --unmarked finding (run that tool for detail)
"""
import argparse
import collections
import os
import re
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
SKIP = ("src/libultra/", "src/libleo/", "src/libnaudio/", "src/libnumus/", "src/libgsm/")
CLANG_ARGS = ['-target', 'mips-unknown-linux-gnu', '-m32', '-I' + ROOT + '/include', '-I' + ROOT + '/src',
              '-I' + ROOT, '-I' + ROOT + '/lib/ultralib/include', '-I' + ROOT + '/lib/ultralib/include/PR',
              '-I' + ROOT + '/lib/ultralib/include/ido', '-D_LANGUAGE_C', '-DLANGUAGE_C', '-DVERSION_JP=1',
              '-D_MIPS_SZLONG=32', '-DF3DEX_GBI_2', '-DNDEBUG', '-D_FINALROM', '-DN_MICRO',
              '-DBUILD_VERSION=VERSION_I_P', '-Wno-everything', '-ferror-limit=0', '-fno-builtin',
              '-std=gnu89', '-nostdinc']

FUNC_OK = re.compile(r'^[A-Z][A-Za-z0-9]*(?:_[A-Za-z0-9]+)+$')
UNKNOWN_FUNC = re.compile(r'^func_[0-9A-Fa-f]{8}(_\w+)?$')
LOCAL_OK = re.compile(r'^(?:[a-z][a-z0-9]*(?:_[a-z0-9]+)*|arg[0-9A-F]+|var_\w+|sp[0-9A-Fa-f]\w*|D_[0-9A-F]{8}\w*|_\w*|temp_\w+|phi_\w+|_?pad\w*|unused\w*|i|j|k|x|y|z|[a-z]\d*|_)$')
GLOBAL_OK = re.compile(r'^(?:[gs][A-Z][A-Za-z0-9]*|D_[0-9A-Fa-f]{8}(?:_\w+)?|[A-Z][A-Z0-9_]*)$')
STRUCT_OK = re.compile(r'^(?:[A-Z][A-Za-z0-9]*|unk_\w+|_\w+|__\w+)$')
JP = re.compile(r'[　-ヿ一-鿿＀-￯]')
STRING = re.compile(r'"(?:[^"\\\n]|\\.)*"')
TERMS = [
    (re.compile(r'GB ?Tower|GbTower|gb_tower(?!\w*\.[ch]\b)', re.I), 'say GB Player (Zero), not GB Tower'),
    (re.compile(r'Pok[eé] ?Cup|PokeCup', re.I), 'never Poke Cup; Nintendo Cup'),
    (re.compile(r'[Pp]ok[eé]ball|POKEBALL'), 'Poké Ball is two words (PokeBall/POKE_BALL in identifiers)'),
    (re.compile(r'(?i:yaw)|(?<![A-Za-z-])(?:[Rr]oll|ROLL)(?![a-z])'), 'use rotationX/Y/Z, not yaw/pitch/roll'),
    (re.compile(r'colour|behaviour|initialis|normalis|optimis|centre|grey|analys(?:e|ing)|favour|honour|neighbour', re.I),
     'American spelling'),
    (re.compile(r'\b(?:enemy|opponent|cpu|CPU)\s+AI\b|\bAI\s+(?:trainer|player|opponent|side)\b'), 'trainers are COM, not AI'),
    (re.compile(r"Kid'?s Club|Victory Palace", re.I), 'repo names: Minigames / Hall of Fame'),
]
SKIP_TERM_LINE = re.compile(r'#include|//@|oldnotes|Stadium 1')
PITCH = re.compile(r'(?i:pitch)')
LOOP_HEX = re.compile(r'\bfor\s*\([^;]*;\s*\w+\s*<=?\s*(0x[0-9A-Fa-f]+)\s*;')
MASK_DEC = re.compile(r'[&|]\s*(\d{3,})\b(?![.\dx])|[&|]=\s*(\d{3,})\b(?![.\dx])')
POW2ISH = {2 ** n for n in range(32)} | {2 ** n - 1 for n in range(32)}
COLOR_CALL = re.compile(r'\b(?:gDPSet(?:Prim|Env|Fog|Blend|Fill)Color|\w*[Cc]olou?r\w*)\s*\(([^;]*)\)\s*;')
HEXCOLOR = re.compile(r'#[0-9A-Fa-f]{6}')


def files_from(paths):
    out = []
    listed = subprocess.run(['git', '-C', ROOT, 'ls-files', 'src'], capture_output=True, text=True).stdout.split()
    listed = [p for p in listed if p.endswith(('.c', '.h')) and not p.startswith(SKIP)]
    if not paths:
        return listed
    for p in paths:
        rp = os.path.relpath(os.path.abspath(p), ROOT)
        out += [f for f in listed if f == rp or f.startswith(rp.rstrip('/') + '/')]
    return out


def doc_above(lines, start):
    """True if the code line `start` (1-based) has a comment right above it."""
    i = start - 2
    while i >= 0 and lines[i].strip() == '':
        return False
    while i >= 0 and (lines[i].strip().startswith('#pragma') or lines[i].strip().startswith('#if')
                      or lines[i].strip().startswith('#else') or lines[i].strip().startswith('#endif')):
        i -= 1
    return i >= 0 and lines[i].rstrip().endswith('*/')


def clang_checks(rel, lines, idx, ci, out):
    path = os.path.join(ROOT, rel)
    tu = idx.parse(path, args=CLANG_ARGS)
    seen = set()
    for c in tu.cursor.walk_preorder():
        if c.location.file is None or os.path.abspath(c.location.file.name) != path:
            continue
        k = c.kind
        key = (k, c.spelling, c.location.line)
        if key in seen:
            continue
        seen.add(key)
        name = c.spelling
        ln = c.location.line
        if k == ci.CursorKind.FUNCTION_DECL and c.is_definition():
            # the definition line may be preceded by a return type line
            start = c.extent.start.line
            if not doc_above(lines, start):
                out.append((rel, start, 'nodoc', name))
            if not UNKNOWN_FUNC.match(name):
                if not FUNC_OK.match(name):
                    out.append((rel, ln, 'func-name', name))
                elif len(name) > 50:
                    out.append((rel, ln, 'func-name', '%s (%d chars)' % (name, len(name))))
        elif k in (ci.CursorKind.PARM_DECL, ci.CursorKind.VAR_DECL):
            par = c.semantic_parent
            if par is not None and par.kind == ci.CursorKind.FUNCTION_DECL:
                if k == ci.CursorKind.PARM_DECL and not par.is_definition():
                    continue
                if name and not LOCAL_OK.match(name):
                    out.append((rel, ln, 'local-name', name))
            elif k == ci.CursorKind.VAR_DECL and par is not None and par.kind == ci.CursorKind.TRANSLATION_UNIT:
                if c.is_definition() and name and not GLOBAL_OK.match(name):
                    out.append((rel, ln, 'global-name', name))
        elif k in (ci.CursorKind.STRUCT_DECL, ci.CursorKind.UNION_DECL, ci.CursorKind.TYPEDEF_DECL,
                   ci.CursorKind.ENUM_DECL):
            if name and 'unnamed' not in name and 'anonymous' not in name and not STRUCT_OK.match(name):
                if k == ci.CursorKind.TYPEDEF_DECL and re.match(r'^[a-z]\w*_t$|^[us]\d+$|^f\d+$', name):
                    continue
                out.append((rel, ln, 'struct-name', name))


def text_checks(rel, lines, out):
    for i, line in enumerate(lines, 1):
        code = line.split('//')[0]
        for m in STRING.finditer(line):
            if JP.search(m.group(0)):
                prev = lines[i - 2] if i > 1 else ''
                after = line[m.end():]
                if '//' not in after and '/*' not in after and not prev.strip().startswith(('//', '/*', '*')):
                    out.append((rel, i, 'jp-untranslated', m.group(0)[:40]))
                break
        if not SKIP_TERM_LINE.search(line):
            for rx, why in TERMS:
                m = rx.search(line)
                if m:
                    out.append((rel, i, 'terminology', '%s: %s' % (m.group(0), why)))
            if 'audio' not in rel and 'gb_' not in rel:
                m = PITCH.search(line)
                if m:
                    out.append((rel, i, 'terminology', '%s: use rotationX/Y/Z, not yaw/pitch/roll' % m.group(0)))
        m = LOOP_HEX.search(code)
        if m:
            v = int(m.group(1), 16)
            if v not in POW2ISH:
                out.append((rel, i, 'hex-loop-bound', m.group(1)))
        for m in MASK_DEC.finditer(code):
            v = int(m.group(1) or m.group(2))
            if v in POW2ISH or bin(v).count('1') <= 2:
                out.append((rel, i, 'decimal-mask', str(v)))
        m = COLOR_CALL.search(code)
        if m and len(re.findall(r'(?:^|,)\s*(?:0x[0-9A-Fa-f]+|\d+)\s*(?=,|$)', m.group(1))) >= 3:
            ctx = '\n'.join(lines[max(0, i - 2):i + 1])
            if not HEXCOLOR.search(ctx):
                out.append((rel, i, 'color-comment', m.group(0)[:60]))


def fake_checks(files, out):
    r = subprocess.run([sys.executable, os.path.join(ROOT, 'tools/fake_audit.py'), '--unmarked'],
                       capture_output=True, text=True, cwd=ROOT)
    fs = set(files)
    for line in r.stdout.splitlines():
        m = re.match(r'^(src/\S+?):(\d+):\s*(.*)$', line)
        if m and m.group(1) in fs:
            out.append((m.group(1), int(m.group(2)), 'unmarked-fake', m.group(3)[:60]))


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('paths', nargs='*')
    ap.add_argument('-v', action='store_true', help='list every finding')
    ap.add_argument('--rule', action='append', help='only these rules')
    ap.add_argument('--no-clang', action='store_true')
    a = ap.parse_args()
    files = files_from(a.paths)
    out = []
    ci = idx = None
    if not a.no_clang:
        import clang.cindex as ci
        idx = ci.Index.create()
    for rel in files:
        lines = open(os.path.join(ROOT, rel), encoding='utf-8', errors='surrogateescape').read().split('\n')
        text_checks(rel, lines, out)
        if ci and rel.endswith('.c'):
            clang_checks(rel, lines, idx, ci, out)
    fake_checks(files, out)
    if a.rule:
        out = [o for o in out if o[2] in a.rule]
    out.sort()
    if a.v:
        for f, ln, rule, msg in out:
            print('%s:%d: %s: %s' % (f, ln, rule, msg))
    per = collections.Counter((o[0], o[2]) for o in out)
    rules = collections.Counter(o[2] for o in out)
    if not a.v:
        byfile = collections.defaultdict(dict)
        for (f, r), n in per.items():
            byfile[f][r] = n
        for f in sorted(byfile):
            print('%-60s %s' % (f, ' '.join('%s=%d' % kv for kv in sorted(byfile[f].items()))))
    print('TOTAL', sum(rules.values()), ' '.join('%s=%d' % kv for kv in sorted(rules.items())))
    return 1 if out else 0


if __name__ == '__main__':
    sys.exit(main())
