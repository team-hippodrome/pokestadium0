/* Stadium Zero fragment 001 (model callbacks): Entry slot table that model data calls its callbacks through. */
#include "global.h"
#include "model_callbacks.h"
#include "gfx_buffer.h"
#include "geo_render.h"
#include "model_renderer_callbacks.h"
#include "battle_hud.h"
#include "vector_math.h"

/**
 * Handwritten jump-stub table (func_81000020 and func_81000028), not C: each 8-byte slot is
 * `j <callback>; nop`. Model data names its geo callbacks by these fixed slot addresses, so the
 * callbacks themselves can sit anywhere. Slot 0 jumps to ModelCallback_IndexedTexture; the
 * 40 slots of func_81000028 jump to callbacks in the battle fragment (for example
 * BattleAnim_AllocateReflectiveTextureDisplayList) and in this fragment (ModelCallback_TwoSegments).
 * Counted with the handwritten asm, not as a match.
 */
#ifdef NON_MATCHING
/* Handwritten jump stubs; there is no C version. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment001_15B1A0/func_81000020.s")
#endif
