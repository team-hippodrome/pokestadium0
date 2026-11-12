"""Rename camelCase local variables and parameters to snake_case.

Usage:
    pip install libclang==18.1.1      # any venv; not needed for the ROM build
    python tools/snake_locals.py [paths...]     # default: every .c under src/

The style guide asks for snake_case locals and arguments. A local or
parameter is renamed only when libclang resolves every use of it to the
same declaration, the new spelling does not already appear anywhere in the
file, and no use sits inside a macro expansion it could not map back.
m2c stack names (sp1C) and names with hex digits are left alone. Run
make rom afterwards: names do not change code generation, but a missed
reference fails the build.
"""
import sys, os, re, subprocess, collections
import clang.cindex as ci

root = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
ARGS = ['-target', 'mips-unknown-linux-gnu', '-m32', '-I' + root + '/include', '-I' + root + '/src', '-I' + root,
        '-I' + root + '/lib/ultralib/include', '-I' + root + '/lib/ultralib/include/PR',
        '-I' + root + '/lib/ultralib/include/ido', '-D_LANGUAGE_C', '-DLANGUAGE_C', '-DVERSION_JP=1',
        '-D_MIPS_SZLONG=32', '-DF3DEX_GBI_2', '-DNDEBUG', '-D_FINALROM', '-DN_MICRO',
        '-DBUILD_VERSION=VERSION_I_P', '-Wno-everything', '-ferror-limit=0', '-fno-builtin', '-std=gnu89',
        '-nostdinc']
CAMEL = re.compile(r'^[a-z][a-z0-9]*(?:[A-Z][a-z0-9]+)+[A-Z]?$')
SKIP_DIRS = ('src/libultra/', 'src/libnumus/')


def snake(n):
    return re.sub(r'(?<=[a-z0-9])([A-Z])', lambda m: '_' + m.group(1).lower(), n)


def ok_name(n):
    if not CAMEL.match(n) or re.match(r'^sp[0-9A-Fa-f]+$', n):
        return False
    if re.search(r'[0-9][A-F]', n):
        return False
    return True


def main():
    idx = ci.Index.create()
    files = sys.argv[1:] or [p for p in subprocess.run(['git', '-C', root, 'ls-files', 'src'], capture_output=True,
                                                        text=True).stdout.split() if p.endswith('.c')]
    files = [f for f in files if not f.startswith(SKIP_DIRS)]
    total = 0
    for f in files:
        path = os.path.join(root, f)
        text = open(path, encoding='utf-8', errors='surrogateescape').read()
        lines = text.split('\n')
        words = set(re.findall(r'\b\w+\b', text))
        tu = idx.parse(path, args=ARGS)
        decls = {}
        refs = collections.defaultdict(list)
        bad = set()
        for c in tu.cursor.walk_preorder():
            if c.location.file is None or os.path.abspath(c.location.file.name) != path:
                continue
            if c.kind in (ci.CursorKind.PARM_DECL, ci.CursorKind.VAR_DECL):
                if c.kind == ci.CursorKind.VAR_DECL and c.semantic_parent.kind != ci.CursorKind.FUNCTION_DECL:
                    continue
                if c.semantic_parent is None or c.semantic_parent.kind != ci.CursorKind.FUNCTION_DECL:
                    continue
                if not c.semantic_parent.is_definition():
                    continue
                if ok_name(c.spelling):
                    decls[c.hash] = c
                    refs[c.hash].append((c.location.line, c.location.column))
            elif c.kind == ci.CursorKind.DECL_REF_EXPR:
                r = c.referenced
                if r is not None and r.kind in (ci.CursorKind.PARM_DECL, ci.CursorKind.VAR_DECL) and ok_name(r.spelling):
                    refs[r.hash].append((c.location.line, c.location.column))
        edits = collections.defaultdict(list)
        for h, d in decls.items():
            old, new = d.spelling, snake(d.spelling)
            if new in words or old == new:
                continue
            locs = sorted(set(refs[h]))
            good = True
            for ln, col in locs:
                s = lines[ln - 1].encode('utf-8', 'surrogateescape')
                if s[col - 1:col - 1 + len(old)] != old.encode() or (col - 1 + len(old) < len(s) and re.match(rb'\w', s[col - 1 + len(old):col + len(old)])):
                    good = False
                    break
            if not good:
                continue
            # every textual use of the name inside the function must be one we resolved
            fn = d.semantic_parent
            ext = fn.extent
            body = '\n'.join(lines[ext.start.line - 1:ext.end.line])
            if len(re.findall(r'\b' + re.escape(old) + r'\b', body)) != len([l for l in locs if ext.start.line <= l[0] <= ext.end.line]):
                continue
            for ln, col in locs:
                edits[ln].append((col, old, new))
        if not edits:
            continue
        n = 0
        for ln, items in edits.items():
            s = lines[ln - 1].encode('utf-8', 'surrogateescape')
            for col, old, new in sorted(set(items), reverse=True):
                i = col - 1
                s = s[:i] + new.encode() + s[i + len(old):]
                n += 1
            lines[ln - 1] = s.decode('utf-8', 'surrogateescape')
        open(path, 'w', encoding='utf-8', errors='surrogateescape').write('\n'.join(lines))
        total += n
    print('renamed', total, 'uses')


if __name__ == '__main__':
    main()
