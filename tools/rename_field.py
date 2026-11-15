"""Type-aware struct field rename.

Usage:
    pip install libclang==18.1.1      # any venv; not needed for the ROM build
    python tools/rename_field.py renames.json
where renames.json is [["StructName", "old_field", "new_field"], ...].

Every .c file under src/ is parsed with libclang; each member reference whose
field belongs to StructName (by declaration, not by spelling) is renamed, and
so is the field declaration. Other structs' fields with the same spelling are
left alone. Run make rom afterwards: a reference libclang could not resolve
shows up as an IDO "undefined" error.
"""
import sys,os,json,subprocess,collections
import clang.cindex as ci
root=os.path.dirname(os.path.dirname(os.path.abspath(__file__))); ren=json.load(open(sys.argv[1]))
want={(s,o):n for s,o,n in ren}
ARGS=['-target','mips-unknown-linux-gnu','-m32','-I'+root+'/include','-I'+root+'/src','-I'+root,'-I'+root+'/lib/ultralib/include','-I'+root+'/lib/ultralib/include/PR','-I'+root+'/lib/ultralib/include/ido','-D_LANGUAGE_C','-DLANGUAGE_C','-DVERSION_JP=1','-D_MIPS_SZLONG=32','-DF3DEX_GBI_2','-DNDEBUG','-D_FINALROM','-DN_MICRO','-DBUILD_VERSION=VERSION_I_P','-Wno-everything','-ferror-limit=0','-fno-builtin','-std=gnu89','-nostdinc']
idx=ci.Index.create()
files=[p for p in subprocess.run(['git','-C',root,'ls-files','src'],capture_output=True,text=True).stdout.split() if p.endswith('.c')]
edits=collections.defaultdict(set)  # path -> {(line,col,old,new)}
def struct_name(fd):
    p=fd.semantic_parent
    if p is None: return None
    n=p.spelling
    if not n or 'unnamed' in n or 'anonymous' in n:
        # typedef'd anonymous: find typedef name via type
        n=p.type.spelling
    return n
errs=0
misses=[]
for f in files:
    tu=idx.parse(os.path.join(root,f),args=ARGS,options=ci.TranslationUnit.PARSE_DETAILED_PROCESSING_RECORD*0)
    for c in tu.cursor.walk_preorder():
        k=c.kind
        if k==ci.CursorKind.MEMBER_REF_EXPR or k==ci.CursorKind.MEMBER_REF or k==ci.CursorKind.FIELD_DECL:
            fd=c.referenced if k!=ci.CursorKind.FIELD_DECL else c
            if fd is None or fd.kind!=ci.CursorKind.FIELD_DECL: continue
            sn=struct_name(fd)
            key=(sn,fd.spelling)
            if key in want:
                loc=c.location
                if k==ci.CursorKind.MEMBER_REF_EXPR:
                    toks=[t for t in c.get_tokens() if t.spelling==fd.spelling]
                    if toks: loc=toks[-1].location
                    else:
                        misses.append((f,c.location.line)); continue
                if loc.file is None: continue
                edits[os.path.relpath(loc.file.name,root)].add((loc.line,loc.column,fd.spelling,want[key]))
if misses: print('unresolved member references:', misses[:20])
os.chdir(root)
e={k:sorted(v) for k,v in edits.items()}

bad=0;n=0
for f,L in e.items():
    lines=open(f).read().split('\n')
    by=collections.defaultdict(set)
    for ln,col,old,new in L: by[ln].add((col,old,new))
    for ln,items in by.items():
        s=lines[ln-1].encode()
        for col,old,new in sorted(items,reverse=True):
            i=col-1
            if s[i:i+len(old)]!=old.encode(): bad+=1; print('mismatch',f,ln,col,old); continue
            s=s[:i]+new.encode()+s[i+len(old):]; n+=1
        lines[ln-1]=s.decode()
    open(f,'w').write('\n'.join(lines))
print('applied',n,'mismatch',bad)
