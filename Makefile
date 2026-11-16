# Stadium Zero JP: fixed-layout C/assembly ROM build.
-include .make_options
VERSION ?= jp
COMPARE ?= 1
VENV ?= .venv
PYTHON ?= $(VENV)/bin/python
IDO_CC ?= tools/ido5.3/cc
IDO71_CC ?= tools/ido7.1/cc
MIPS_BINUTILS_PREFIX ?= mips-linux-gnu-
JOBS ?= 4
ASM_ONLY ?= 0
ifeq ($(VERSION),jp)
else
$(error Only VERSION=jp is supported)
endif
.DEFAULT_GOAL := rom
.NOTPARALLEL:
.PHONY: all rom shift-test setup venv extract init diff-init test clean distclean coverage
all: rom

venv:
	@test -x $(PYTHON) || python3 -m venv $(VENV)
	$(PYTHON) -m pip install -r requirements.txt

setup: venv
	$(PYTHON) tools/setup_toolchain.py
	@command -v $(MIPS_BINUTILS_PREFIX)as >/dev/null
	@command -v $(MIPS_BINUTILS_PREFIX)ld >/dev/null
	@command -v $(MIPS_BINUTILS_PREFIX)objcopy >/dev/null
	@command -v $(MIPS_BINUTILS_PREFIX)nm >/dev/null

extract:
	$(PYTHON) -m splat split yamls/jp/mapping.yaml
	$(PYTHON) tools/generate_pragmas.py baseroms/jp/baserom.z64 --asm-only
	$(PYTHON) tools/production.py extract

init: setup extract

rom:
	@test -f assets/production/manifest.json || { echo 'Run make init first'; exit 1; }
	$(PYTHON) tools/production.py build --cc $(IDO_CC) --cc71 $(IDO71_CC) --prefix $(MIPS_BINUTILS_PREFIX) --compare $(COMPARE) --jobs $(JOBS) $(if $(filter 1,$(ASM_ONLY)),--asm-only,)

# Moves every piece of every image by SHIFT bytes and checks that each address followed: the
# proof that the build relocates. A shiftable ROM to edit is just `make rom COMPARE=0`.
SHIFT ?= 16
shift-test:
	@test -f assets/production/manifest.json || { echo 'Run make init first'; exit 1; }
	$(PYTHON) tools/production.py build --cc $(IDO_CC) --cc71 $(IDO71_CC) --prefix $(MIPS_BINUTILS_PREFIX) --jobs $(JOBS) --shift $(SHIFT)

diff-init: rom
	@echo 'Per-image ELF objects, generated linker scripts and maps: build/production/'

test:
	$(PYTHON) tools/generate_pragmas.py baseroms/jp/baserom.z64 --check
	$(PYTHON) -m unittest discover -s tools -p 'test_*.py'

coverage:
	$(PYTHON) ci/update_coverage.py

clean:
	rm -rf build

distclean: clean
	@echo 'Private extraction and toolchain preserved; remove explicitly if needed.'
