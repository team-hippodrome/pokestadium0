/* Stadium Zero fragment012_17ED00. */
/* C ported from the Stadium 1 decomp: src/fragments/particle_math/particle_math_264380.c. */

#include "fragments/particle_math/particle_math.h"
extern Gfx gDL_ItemIcon[];
extern Gfx D_821904C8[];
extern Gfx D_82190548[];
extern Gfx gDL_BeginUIOverlay[];
extern Gfx gDL_EndColorFill[];
extern Gfx gDL_BeginColorFill[];
extern Vtx gVtx_UI_TriangleSmall[];
extern Vtx gVtx_UI_TriangleLarge[];
extern Vtx gVtx_UI_RectVertical[];
extern Vtx gVtx_UI_ComplexQuad[];
extern Vtx gFullscreenQuadVtx[];
extern Gfx D_82191900[];
extern Gfx D_82191910[];
extern Gfx gDL_PanelBackground[];

#include "m2c_macros.h"

void ParticleGfx_PipeSync(void);
void ParticleGfx_SetTextureState(void);
void ParticleGfx_NoopStub2(void);
void ParticleGfx_NoopStub3(void);
void ParticleGfx_SetPrimColor(u8 r, u8 g, u8 b, u8 a);
void ParticleGfx_SetFogColor(u8 r, u8 g, u8 b, u8 a);
void ParticleGfx_SetBlendColor(u8 r, u8 g, u8 b, u8 a);
void ParticleGfx_SetEnvColor(u8 r, u8 g, u8 b, u8 a);
void ParticleGfx_SetPrimEnvColorCombine(u8 prim_r, u8 prim_g, u8 prim_b, u8 env_r, u8 env_g, u8 env_b, u8 prim_a);
void ParticleGfx_SetPrimEnvNoiseCombine(u8 prim_r, u8 prim_g, u8 prim_b, u8 env_r, u8 env_g, u8 env_b, u8 prim_a);
void ParticleGfx_SetPrimEnvColorShadeCombine(u8 prim_r, u8 prim_g, u8 prim_b, u8 prim_a, u8 env_r, u8 env_g, u8 env_b, u8 env_a);
void ParticleGfx_SetPrimColorTextureCombine(u8 r, u8 g, u8 b, u8 a);
void ParticleGfx_SetPrimEnvLodCombine(u8 l, u8 prim_r, u8 prim_g, u8 prim_b, u8 prim_a, u8 env_r, u8 env_g, u8 env_b);
void ParticleGfx_SetPrimEnvLodTextureCombine(u8 l, u8 prim_r, u8 prim_g, u8 prim_b, u8 prim_a, u8 env_r, u8 env_g, u8 env_b);
void ParticleGfx_SetTextureAlphaCombine(u8 a);
void ParticleGfx_SetAnimatedTileSize(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void ParticleGfx_SetAnimatedAuxTileSize(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void ParticleGfx_SetAnimatedTileSizeOnList(Gfx* gfx, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void ParticleGfx_SetAnimatedAuxTileSizeOnList(Gfx* gfx, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void ParticleGfx_SetPartiallyAnimatedTileSize(Gfx* gfx, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void ParticleGfx_SetPartiallyAnimatedAuxTileSize(Gfx* gfx, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
/**
 * Append a 32-bit texture block load with caller-supplied format and addressing.
 * Not reached in play (2026-11-13): did not run in the 165-move battle sweep (each move used once,
 * from the command menu to the end of its turn) or in a tour of the menus and a COM battle.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void ParticleGfx_LoadTextureBlock32(u8* texture, s32 fmt, s32 width, s32 height, s32 cms, s32 cmt, s32 masks, s32 maskt, s32 shifts,
                   s32 shiftt);
/**
 * Append a 32-bit texture tile load with caller-supplied format and addressing.
 * Not reached in play (2026-11-13): did not run in the 165-move battle sweep (each move used once,
 * from the command menu to the end of its turn) or in a tour of the menus and a COM battle.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void ParticleGfx_LoadTextureTile32(u8* texture, s32 fmt, s32 width, s32 height, s32 cms, s32 cmt, s32 masks, s32 maskt, s32 shifts,
                   s32 shiftt);
/**
 * Append a 16-bit texture block load with caller-supplied format and addressing.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (5 of the moves).
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void ParticleGfx_LoadTextureBlock16(u8* texture, s32 fmt, s32 width, s32 height, s32 cms, s32 cmt, s32 masks, s32 maskt, s32 shifts,
                   s32 shiftt);
/**
 * Append a 16-bit texture tile load with caller-supplied format and addressing.
 * Not reached in play (2026-11-13): did not run in the 165-move battle sweep (each move used once,
 * from the command menu to the end of its turn) or in a tour of the menus and a COM battle.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void ParticleGfx_LoadTextureTile16(u8* texture, s32 fmt, s32 width, s32 height, s32 cms, s32 cmt, s32 masks, s32 maskt, s32 shifts,
                   s32 shiftt);
/**
 * Append a 8-bit texture block load with caller-supplied format and addressing.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (92 of the moves).
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void ParticleGfx_LoadTextureBlock8(u8* texture, s32 fmt, s32 width, s32 height, s32 cms, s32 cmt, s32 masks, s32 maskt, s32 shifts,
                   s32 shiftt);
/**
 * Append a 8-bit texture tile load with caller-supplied format and addressing.
 * Not reached in play (2026-11-13): did not run in the 165-move battle sweep (each move used once,
 * from the command menu to the end of its turn) or in a tour of the menus and a COM battle.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void ParticleGfx_LoadTextureTile8(u8* texture, s32 fmt, s32 width, s32 height, s32 cms, s32 cmt, s32 masks, s32 maskt, s32 shifts,
                   s32 shiftt);
/**
 * Append a 4-bit texture block load with caller-supplied format and addressing.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (110 of the moves).
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void ParticleGfx_LoadTextureBlock4(u8* texture, s32 fmt, s32 width, s32 height, s32 cms, s32 cmt, s32 masks, s32 maskt, s32 shifts,
                   s32 shiftt);
/**
 * Append a 4-bit texture tile load with caller-supplied format and addressing.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (10 of the moves).
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void ParticleGfx_LoadTextureTile4(u8* texture, s32 fmt, s32 width, s32 height, s32 cms, s32 cmt, s32 masks, s32 maskt, s32 shifts,
                   s32 shiftt);
/**
 * Load textures into the explicitly selected TMEM regions/tiles for multi-texture rendering.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (17 of the moves).
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void ParticleGfx_LoadTextureMultiBlock4(u8* texture, s32 tmem, s32 rtile, s32 fmt, s32 width, s32 height, s32 cms, s32 cmt, s32 masks,
                   s32 maskt, s32 shifts, s32 shiftt);
void ParticleGfx_LoadTextureRgba32(u8* texture, s32 width, s32 height);
void ParticleGfx_LoadTextureTileRgba32(u8* texture, s32 width, s32 height);
void ParticleGfx_LoadTextureRgba16(u8* texture, s32 width, s32 height);
void ParticleGfx_LoadTextureRgba16Dual(u8* texture1, u8* texture2, s32 width, s32 height);
void ParticleGfx_LoadTextureRgba16WrapS(u8* texture, s32 width, s32 height);
void ParticleGfx_LoadTextureRgba16WrapT(u8* texture, s32 width, s32 height);
void ParticleGfx_LoadTextureRgba16WrapST(u8* texture, s32 width, s32 height);
void ParticleGfx_LoadTextureRgba16WrapSWithMask(u8* texture, s32 width, s32 height, s32 masks);
void ParticleGfx_LoadTextureTileRgba16(u8* texture, s32 width, s32 height);
void ParticleGfx_LoadTextureIa16(u8* texture, s32 width, s32 height);
void ParticleGfx_LoadTextureTileIa16(u8* texture, s32 width, s32 height);
void ParticleGfx_LoadTextureIa8(u8* texture, s32 width, s32 height);
void ParticleGfx_LoadTextureTileIa8(u8* texture, s32 width, s32 height);
void ParticleGfx_LoadTextureIa8WrapST(u8* texture, s32 width, s32 height);
void ParticleGfx_LoadTextureI8(u8* texture, s32 width, s32 height);
void ParticleGfx_LoadTextureI8WrapST(u8* texture, s32 width, s32 height);
void ParticleGfx_LoadTextureTileI8(u8* texture, s32 width, s32 height);
void ParticleGfx_LoadTextureI8Alias(u8* texture, s32 width, s32 height);
void ParticleGfx_LoadTextureTileI8Alias(u8* texture, s32 width, s32 height);
void ParticleGfx_LoadTextureTileIa4(u8* texture, s32 width, s32 height);
void ParticleGfx_LoadTextureTileI4(u8* texture, s32 width, s32 height);
void ParticleGfx_LoadTextureIa4(u8* texture, s32 width, s32 height);
void ParticleGfx_LoadTextureI4(u8* texture, s32 width, s32 height);
void ParticleGfx_LoadTextureI4WrapST(u8* texture, s32 width, s32 height);
void ParticleGfx_LoadTextureI4Alias(u8* texture, s32 width, s32 height);
void ParticleGfx_LoadTextureTileI4Alias(u8* texture, s32 width, s32 height);
void ParticleGfx_LoadTextureI4WrapS(u8* texture, s32 width, s32 height);
void ParticleGfx_LoadTextureI4WrapSTNoMirror(u8* texture, s32 width, s32 height);
void ParticleGfx_LoadTextureI4MultiBlockWrapST(u8* texture, s32 width, s32 height);
void ParticleGfx_LoadTextureI4MultiBlockWrapSTWithShift(u8* texture, s32 width, s32 height, s32 shifts, s32 shiftt);
void ParticleGfx_LoadTextureCi8(u8* texture, s32 width, s32 height);
void ParticleGfx_LoadTextureCi8WrapSWithMask(u8* texture, s32 width, s32 height, s32 masks);
void ParticleGfx_LoadTextureTileCi8(u8* texture, s32 width, s32 height);
void ParticleGfx_LoadTextureDualRgba16I8(u8* texture1, u8* texture2, s32 width, s32 height);
void ParticleGfx_DrawQuadVertices(Vtx* arg0);
void ParticleGfx_NoopStub4(void);
void ParticleGfx_DrawTransformedQuad(Vec3f arg0, Vec3s arg1, f32 arg2, Vtx* arg3);
void ParticleGfx_DrawTransformedQuadYScaled(Vec3f arg0, Vec3s arg1, f32 arg3, Vtx* arg4);
void ParticleGfx_DrawTransformedQuadXYScaled(Vec3f arg0, Vec3s arg1, f32 arg2, f32 arg3, Vtx* arg4);
void ParticleGfx_DrawTransformedTriangle(Vec3f arg0, Vec3s arg1, f32 arg2, Vtx* arg3);
void ParticleGfx_DrawModelQuad(CameraNode* arg0, Vec3f arg1, f32 arg2, Vtx* arg3);
void ParticleGfx_DrawModelQuadRotated(CameraNode* arg0, Vec3f arg1, f32 arg2, Vtx* arg3, s16 arg4);
void ParticleGfx_DrawModelQuadYScaled(CameraNode* arg0, Vec3f arg1, f32 arg2, Vtx* arg3);
void ParticleGfx_DrawModelQuadRotatedYScaled(CameraNode* arg0, Vec3f arg1, f32 arg2, Vtx* arg3, s16 arg4);
void ParticleGfx_DrawModelTriangle(CameraNode* arg0, Vec3f arg1, f32 arg2, Vtx* arg3);
void ParticleGfx_DrawModelTriangleRotated(CameraNode* arg0, Vec3f arg1, f32 arg2, Vtx* arg3, s16 arg4);
void ParticleGfx_DrawI8TextureAtlas(u8* texture, Vtx* vtx, s32 arg2, s32 arg3, s32 width, s32 height);
void ParticleGfx_DrawIa16TextureAtlas(u8* texture, Vtx* vtx, s32 arg2, s32 arg3, s32 width, s32 height);
void ParticleGfx_DrawIa8TextureAtlas(u8* texture, Vtx* vtx, s32 arg2, s32 arg3, s32 width, s32 height);
void ParticleGfx_DrawI4TextureAtlas(u8* texture, Vtx* vtx, s32 arg2, s32 arg3, s32 width, s32 height);
void ParticleGfx_DrawI4TextureAtlasTiled(u8* texture, Vtx* vtx, s32 arg2, s32 arg3, s32 width, s32 height);

s32 ParticleGfx_TextureSizeLog2(s32 size);

/**
 * Append an RDP pipeline synchronization command.
 * Seen in play (2026-11-13) in the 165-move sweep (Pound and 134 other calls): each call emitted
 * one G_RDPPIPESYNC (E7000000 00000000) at gDisplayListHead.
 */
void ParticleGfx_PipeSync(void) {
    gDPPipeSync(gDisplayListHead++);
}

/**
 * Synchronize the RDP, select one-cycle mode, and disable RSP texturing.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void ParticleGfx_SetTextureState(void) {
    gDPPipeSync(gDisplayListHead++);
    gDPSetCycleType(gDisplayListHead++, G_CYC_1CYCLE);
    gSPTexture(gDisplayListHead++, 0x0001, 0x0001, 0, G_TX_RENDERTILE, G_OFF);
}

/**
 * Empty callback retained at its original entry point.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void ParticleGfx_NoopStub2(void) {
}

/**
 * Empty callback retained at its original entry point.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void ParticleGfx_NoopStub3(void) {
}

s32 func_82168F54(s32 arg0)
{
  s32 var_v1;
  arg0 = arg0; // FAKE: self-assignment
  var_v1 = 0;
  do
  {
    arg0 = arg0 / 2;
    var_v1 += 1;
  }
  while (arg0 != 1);
  return var_v1;
}

void func_82168F7C(void) {
    gDPSetRenderMode(gDisplayListHead++, 0x0C180000, 0x5978);
}

void func_82168FAC(u16* palette) {
    gDPLoadTLUT_pal256(gDisplayListHead++, palette);
}

/**
 * Write the supplied RGBA channels to the primitive color register (no pipe sync).
 * Seen in play (2026-11-13) in the 165-move sweep: with (FF, FF, FF, FF) it emitted G_SETPRIMCOLOR
 * FA000000 FFFFFFFF.
 */
void ParticleGfx_SetPrimColor(u8 r, u8 g, u8 b, u8 a) {
    gDPSetPrimColor(gDisplayListHead++, 0, 0, r, g, b, a);
}

/**
 * Synchronize the pipeline and write the supplied RGBA channels to the selected RDP color register.
 * Seen in play (2026-11-13) in the 165-move sweep: with (0, 0, 0, 0) it emitted G_RDPPIPESYNC then
 * G_SETFOGCOLOR F8000000 00000000.
 */
void ParticleGfx_SetFogColor(u8 r, u8 g, u8 b, u8 a) {
    gDPPipeSync(gDisplayListHead++);
    gDPSetFogColor(gDisplayListHead++, r, g, b, a);
}

/**
 * Synchronize the pipeline and write the supplied RGBA channels to the selected RDP color register.
 * Seen in play (2026-11-13) in the 165-move sweep: with (0, 0, 0, 0) it emitted G_RDPPIPESYNC then
 * G_SETBLENDCOLOR F9000000 00000000.
 */
void ParticleGfx_SetBlendColor(u8 r, u8 g, u8 b, u8 a) {
    gDPPipeSync(gDisplayListHead++);
    gDPSetBlendColor(gDisplayListHead++, r, g, b, a);
}

/**
 * Synchronize the pipeline and write the supplied RGBA channels to the selected RDP color register.
 * Seen in play (2026-11-13) in the 165-move sweep: with (FF, FF, 64, 00) it emitted G_RDPPIPESYNC
 * then G_SETENVCOLOR FB000000 FFFF6400.
 */
void ParticleGfx_SetEnvColor(u8 r, u8 g, u8 b, u8 a) {
    gDPPipeSync(gDisplayListHead++);
    gDPSetEnvColor(gDisplayListHead++, r, g, b, a);
}

void func_82169200(u8 arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5, u8 arg6) {
    gDPPipeSync(gDisplayListHead++);
    gDPSetPrimColor(gDisplayListHead++, 0, 0, arg0, arg1, arg2, arg6);
    gDPSetEnvColor(gDisplayListHead++, arg3, arg4, arg5, 0);
}

/**
 * Synchronize the pipeline, write the supplied color parameters, and select this wrapper's explicit RDP combiner.
 * Seen in play (2026-11-13) in the 165-move sweep (Pound, Fire Punch and others): it emitted
 * G_RDPPIPESYNC, G_SETPRIMCOLOR with the prim arguments (e.g. FFFF00FF), G_SETENVCOLOR with the env
 * arguments (e.g. F0282800) and G_SETCOMBINE FC3097FF 5FFEFE38.
 */
void ParticleGfx_SetPrimEnvColorCombine(u8 prim_r, u8 prim_g, u8 prim_b, u8 env_r, u8 env_g, u8 env_b, u8 prim_a) {
    gDPPipeSync(gDisplayListHead++);
    gDPSetPrimColor(gDisplayListHead++, 0, 0, prim_r, prim_g, prim_b, prim_a);
    gDPSetEnvColor(gDisplayListHead++, env_r, env_g, env_b, 0);
    gDPSetCombineLERP(gDisplayListHead++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0,
                      COMBINED, 0, 0, 0, COMBINED);
}

/**
 * Synchronize the pipeline, write the supplied color parameters, and select this wrapper's explicit RDP combiner.
 * Seen in play (2026-11-13) in the 165-move sweep (Sand Attack, Ember, Mist, powders, Smokescreen,
 * Haze): it emitted G_RDPPIPESYNC, G_SETPRIMCOLOR (e.g. FFFF64B4), G_SETENVCOLOR with alpha FF
 * (e.g. 969632FF) and G_SETCOMBINE FC767E60 F50FF37F.
 */
void ParticleGfx_SetPrimEnvNoiseCombine(u8 prim_r, u8 prim_g, u8 prim_b, u8 env_r, u8 env_g, u8 env_b, u8 prim_a) {
    gDPPipeSync(gDisplayListHead++);
    gDPSetPrimColor(gDisplayListHead++, 0, 0, prim_r, prim_g, prim_b, prim_a);
    gDPSetEnvColor(gDisplayListHead++, env_r, env_g, env_b, 255);
    gDPSetCombineLERP(gDisplayListHead++, NOISE, 0, ENV_ALPHA, 0, 0, 0, 0, TEXEL0, PRIMITIVE, ENVIRONMENT, COMBINED,
                      ENVIRONMENT, COMBINED, 0, PRIMITIVE, 0);
}

/**
 * Synchronize the pipeline, write the supplied color parameters, and select this wrapper's explicit RDP combiner.
 * Seen in play (2026-11-13) in the 165-move sweep (Sing, Sleep Powder, Hypnosis): it emitted
 * G_RDPPIPESYNC, G_SETPRIMCOLOR FFFFFFFF, G_SETENVCOLOR FFFFFFFF and G_SETCOMBINE FC309604
 * 5F12FFFF.
 */
void ParticleGfx_SetPrimEnvColorShadeCombine(u8 prim_r, u8 prim_g, u8 prim_b, u8 prim_a, u8 env_r, u8 env_g, u8 env_b, u8 env_a) {
    gDPPipeSync(gDisplayListHead++);
    gDPSetPrimColor(gDisplayListHead++, 0, 0, prim_r, prim_g, prim_b, prim_a);
    gDPSetEnvColor(gDisplayListHead++, env_r, env_g, env_b, env_a);
    gDPSetCombineLERP(gDisplayListHead++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0,
                      COMBINED, 0, SHADE, 0, COMBINED, 0, SHADE, 0);
}

/**
 * Synchronize the pipeline, write the supplied color parameters, and select this wrapper's explicit RDP combiner.
 * Not reached in play (2026-11-13): no move in the 165-move battle sweep called it (each move used
 * once, from the command menu to the end of its turn).
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void ParticleGfx_SetPrimColorTextureCombine(u8 r, u8 g, u8 b, u8 a) {
    gDPPipeSync(gDisplayListHead++);
    gDPSetPrimColor(gDisplayListHead++, 0, 0, r, g, b, a);
    gDPSetCombineLERP(gDisplayListHead++, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0,
                      COMBINED);
}

/**
 * Synchronize the pipeline, write the supplied color parameters, and select this wrapper's explicit RDP combiner.
 * Seen in play (2026-11-13) in the 165-move sweep (Mist, powders, Smokescreen, Haze, Smog): with l
 * = 0x80 it emitted G_SETPRIMCOLOR FA000080 (LOD fraction 0x80, e.g. 9600C800), G_SETENVCOLOR and
 * G_SETCOMBINE FC272C60 150C937F.
 */
void ParticleGfx_SetPrimEnvLodCombine(u8 l, u8 prim_r, u8 prim_g, u8 prim_b, u8 prim_a, u8 env_r, u8 env_g, u8 env_b) {
    gDPPipeSync(gDisplayListHead++);
    gDPSetPrimColor(gDisplayListHead++, 0, l, prim_r, prim_g, prim_b, prim_a);
    gDPSetEnvColor(gDisplayListHead++, env_r, env_g, env_b, 0);
    gDPSetCombineLERP(gDisplayListHead++, TEXEL1, TEXEL0, PRIM_LOD_FRAC, TEXEL0, TEXEL1, TEXEL0, PRIM_LOD_FRAC, TEXEL0,
                      PRIMITIVE, ENVIRONMENT, COMBINED, ENVIRONMENT, COMBINED, 0, PRIMITIVE, 0);
}

/**
 * Synchronize the pipeline, write the supplied color parameters, and select this wrapper's explicit RDP combiner.
 * Seen in play (2026-11-13) in the 165-move sweep (Flamethrower, Dragon Rage, Fire Spin, Fire
 * Blast): with l = 0x80 it emitted G_SETPRIMCOLOR FA000080, G_SETENVCOLOR and G_SETCOMBINE FC277E60
 * 150CF37F.
 */
void ParticleGfx_SetPrimEnvLodTextureCombine(u8 l, u8 prim_r, u8 prim_g, u8 prim_b, u8 prim_a, u8 env_r, u8 env_g, u8 env_b) {
    gDPPipeSync(gDisplayListHead++);
    gDPSetPrimColor(gDisplayListHead++, 0, l, prim_r, prim_g, prim_b, prim_a);
    gDPSetEnvColor(gDisplayListHead++, env_r, env_g, env_b, 0);
    gDPSetCombineLERP(gDisplayListHead++, TEXEL1, TEXEL0, PRIM_LOD_FRAC, TEXEL0, 0, 0, 0, TEXEL0, PRIMITIVE,
                      ENVIRONMENT, COMBINED, ENVIRONMENT, COMBINED, 0, PRIMITIVE, 0);
}

/**
 * Synchronize the pipeline, write the supplied color parameters, and select this wrapper's explicit RDP combiner.
 * Seen in play (2026-11-13) in the 165-move sweep (Psybeam): with a = 0xC8 it emitted
 * G_RDPPIPESYNC, G_SETPRIMCOLOR FFFFFFC8 and G_SETCOMBINE FC4097FF FFFFFE38.
 */
void ParticleGfx_SetTextureAlphaCombine(u8 a) {
    gDPPipeSync(gDisplayListHead++);
    gDPSetPrimColor(gDisplayListHead++, 0, 0, 255, 255, 255, a);
    gDPSetCombineLERP(gDisplayListHead++, SHADE, 0, TEXEL0, 0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0,
                      COMBINED);
}

/**
 * Write bounds for the render tile, scrolling S positively and T negatively with the particle clock.
 * Seen in play (2026-11-13) in the 165-move sweep (Sing, Mist, powders, Haze): it emitted one
 * G_SETTILESIZE (F2...) on the render tile whose bounds moved with the particle frame counter
 * between frames (e.g. F26129EE 008C4834).
 */
void ParticleGfx_SetAnimatedTileSize(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    gDPSetTileSize(gDisplayListHead++, G_TX_RENDERTILE, arg0 * gParticleFrameCounter, -arg1 * gParticleFrameCounter,
                   (((arg0 * gParticleFrameCounter) + arg2) - 1) << 2, (((-arg1 * gParticleFrameCounter) + arg3) - 1) << 2);
}

/**
 * Write bounds for auxiliary tile 1, scrolling S positively and T negatively with the particle clock.
 * Seen in play (2026-11-13) in the 165-move sweep (Flamethrower, Mist, powders, Fire Spin): it
 * emitted one G_SETTILESIZE on tile 1 (second word 01xxxxxx, e.g. F2000220 010FC97C) that moved
 * with the particle frame counter.
 */
void ParticleGfx_SetAnimatedAuxTileSize(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    gDPSetTileSize(gDisplayListHead++, 1, arg0 * gParticleFrameCounter, -arg1 * gParticleFrameCounter,
                   (((arg0 * gParticleFrameCounter) + arg2) - 1) << 2, (((-arg1 * gParticleFrameCounter) + arg3) - 1) << 2);
}

/**
 * Write bounds for the render tile, scrolling S positively and T negatively with the particle clock.
 * Seen in play (2026-11-13) in the 165-move sweep (Mega Punch, Pay Day, Gust, Fly and others): it
 * wrote a G_SETTILESIZE for the render tile into the passed list (e.g. F2098000 002DC07C) rather
 * than at gDisplayListHead.
 */
void ParticleGfx_SetAnimatedTileSizeOnList(Gfx* gfx, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    gDPSetTileSize(gfx, G_TX_RENDERTILE, arg1 * gParticleFrameCounter, -arg2 * gParticleFrameCounter, (((arg1 * gParticleFrameCounter) + arg3) - 1) << 2,
                   (((-arg2 * gParticleFrameCounter) + arg4) - 1) << 2);
}

/**
 * Write bounds for auxiliary tile 1, scrolling S positively and T negatively with the particle clock.
 * Seen in play (2026-11-13) in the 165-move sweep (Mega Punch, Pay Day, Gust, Fly and others): it
 * wrote a G_SETTILESIZE for tile 1 into the passed list (e.g. F284C000 011AC07C).
 */
void ParticleGfx_SetAnimatedAuxTileSizeOnList(Gfx* gfx, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    gDPSetTileSize(gfx, 1, arg1 * gParticleFrameCounter, -arg2 * gParticleFrameCounter, (((arg1 * gParticleFrameCounter) + arg3) - 1) << 2,
                   (((-arg2 * gParticleFrameCounter) + arg4) - 1) << 2);
}

/**
 * Write bounds for the render tile with fixed S and clock-scrolled negative T.
 * Seen in play (2026-11-13) in the 165-move sweep (Waterfall): it wrote a G_SETTILESIZE for the
 * render tile into the passed list (F2FF51C0 0005077C).
 */
void ParticleGfx_SetPartiallyAnimatedTileSize(Gfx* gfx, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    gDPSetTileSize(gfx, G_TX_RENDERTILE, arg1, -arg2 * gParticleFrameCounter, ((arg3 + arg1) - 1) << 2,
                   (((-arg2 * gParticleFrameCounter) + arg4) - 1) << 2);
}

/**
 * Write bounds for auxiliary tile 1 with fixed S and clock-scrolled negative T.
 * Seen in play (2026-11-13) in the 165-move sweep (Waterfall): it wrote a G_SETTILESIZE for tile 1
 * into the passed list (F20358E0 011503FC).
 */
void ParticleGfx_SetPartiallyAnimatedAuxTileSize(Gfx* gfx, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    gDPSetTileSize(gfx, 1, arg1, -arg2 * gParticleFrameCounter, ((arg3 + arg1) - 1) << 2,
                   (((-arg2 * gParticleFrameCounter) + arg4) - 1) << 2);
}

/**
 * Count successive halvings until size reaches one; callers must supply a size of at least two.
 * Seen in play (2026-11-13) in the 165-move sweep (Razor Wind, Whirlwind, Slam and others): it
 * returned 6 for size 0x40.
 */
s32 ParticleGfx_TextureSizeLog2(s32 arg0) {
    s32 temp_a1;
    s32 var_v0;
    s32 var_v1;

    var_v1 = 0;
    var_v0 = arg0;
    do {
        var_v1 += 1;
        temp_a1 = var_v0 / 2;
        var_v0 = temp_a1;
    } while (temp_a1 != 1);
    return var_v1;
}

void func_82169B14(s32 width, s32 height) {
    gDPPipeSync(gDisplayListHead++);
    gDPTileSync(gDisplayListHead++);
    gDPSetTile(gDisplayListHead++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0,
                 G_TX_CLAMP, 0, 0, G_TX_CLAMP, 0, 0);
    gDPTileSync(gDisplayListHead++);
    gDPSetTile(gDisplayListHead++, G_IM_FMT_RGBA, G_IM_SIZ_16b, ((width * 2 + 7) >> 3), 0, G_TX_RENDERTILE, 0,
                 G_TX_CLAMP, 0, 0, G_TX_CLAMP, 0, 0);
    gDPSetTileSize(gDisplayListHead++, G_TX_RENDERTILE, 0, 0, (width - 1) << 2, (height - 1) << 2);
}

void func_82169BF0(s32 width, s32 height) {
    gDPPipeSync(gDisplayListHead++);
    gDPTileSync(gDisplayListHead++);
    gDPSetTile(gDisplayListHead++, G_IM_FMT_RGBA, G_IM_SIZ_16b, ((width * 2 + 7) >> 3), 0, G_TX_LOADTILE, 0,
                 G_TX_CLAMP, 0, 0, G_TX_CLAMP, 0, 0);
    gDPTileSync(gDisplayListHead++);
    gDPSetTile(gDisplayListHead++, G_IM_FMT_RGBA, G_IM_SIZ_16b, ((width * 2 + 7) >> 3), 0, G_TX_RENDERTILE, 0,
                 G_TX_CLAMP, 0, 0, G_TX_CLAMP, 0, 0);
    gDPSetTileSize(gDisplayListHead++, G_TX_RENDERTILE, 0, 0, (width - 1) << 2, (height - 1) << 2);
}

void func_82169CCC(s32 width, s32 height) {
    gDPPipeSync(gDisplayListHead++);
    gDPTileSync(gDisplayListHead++);
    gDPSetTile(gDisplayListHead++, G_IM_FMT_RGBA, G_IM_SIZ_32b, 0, 0, G_TX_LOADTILE, 0,
                 G_TX_CLAMP, 0, 0, G_TX_CLAMP, 0, 0);
    gDPTileSync(gDisplayListHead++);
    gDPSetTile(gDisplayListHead++, G_IM_FMT_RGBA, G_IM_SIZ_32b, ((width * 2 + 7) >> 3), 0, G_TX_RENDERTILE, 0,
                 G_TX_CLAMP, 0, 0, G_TX_CLAMP, 0, 0);
    gDPSetTileSize(gDisplayListHead++, G_TX_RENDERTILE, 0, 0, (width - 1) << 2, (height - 1) << 2);
}

void func_82169DA8(s32 width, s32 height) {
    gDPPipeSync(gDisplayListHead++);
    gDPTileSync(gDisplayListHead++);
    gDPSetTile(gDisplayListHead++, G_IM_FMT_RGBA, G_IM_SIZ_32b, ((width * 2 + 7) >> 3), 0, G_TX_LOADTILE, 0,
                 G_TX_CLAMP, 0, 0, G_TX_CLAMP, 0, 0);
    gDPTileSync(gDisplayListHead++);
    gDPSetTile(gDisplayListHead++, G_IM_FMT_RGBA, G_IM_SIZ_32b, ((width * 2 + 7) >> 3), 0, G_TX_RENDERTILE, 0,
                 G_TX_CLAMP, 0, 0, G_TX_CLAMP, 0, 0);
    gDPSetTileSize(gDisplayListHead++, G_TX_RENDERTILE, 0, 0, (width - 1) << 2, (height - 1) << 2);
}

void func_82169E84(u8* texture, s32 width, s32 height) {
    gDPSetTextureImage(gDisplayListHead++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, texture);
    gDPLoadSync(gDisplayListHead++);
    gDPLoadBlock(gDisplayListHead++, G_TX_LOADTILE, 0, 0, width * height - 1, CALC_DXT(width, G_IM_SIZ_16b_BYTES));
}

void func_82169F74(void* img, s32 width, s32 height) {
    gDPSetTextureImage(gDisplayListHead++, G_IM_FMT_RGBA, G_IM_SIZ_16b, width, img);
    gDPLoadSync(gDisplayListHead++);
    gDPLoadTile(gDisplayListHead++, G_TX_LOADTILE, 0, 0, (width - 1) << G_TEXTURE_IMAGE_FRAC, (height - 1) << G_TEXTURE_IMAGE_FRAC);
}

void func_82169FF8(u8* texture, s32 width, s32 height) {
    gDPSetTextureImage(gDisplayListHead++, G_IM_FMT_RGBA, G_IM_SIZ_32b, 1, texture);
    gDPLoadSync(gDisplayListHead++);
    gDPLoadBlock(gDisplayListHead++, G_TX_LOADTILE, 0, 0, width * height - 1, CALC_DXT(width, G_IM_SIZ_32b_BYTES));
}

void func_8216A0E8(void* img, s32 width, s32 height) {
    gDPSetTextureImage(gDisplayListHead++, G_IM_FMT_RGBA, G_IM_SIZ_32b, width, img);
    gDPLoadSync(gDisplayListHead++);
    gDPLoadTile(gDisplayListHead++, G_TX_LOADTILE, 0, 0, (width - 1) << G_TEXTURE_IMAGE_FRAC, (height - 1) << G_TEXTURE_IMAGE_FRAC);
}

/**
 * Adds a 32-bit texture block load to the display list.
 * @unverified Name from Stadium 1.
 */
void ParticleGfx_LoadTextureBlock32(u8* texture, s32 fmt, s32 width, s32 height, s32 cms, s32 cmt, s32 masks, s32 maskt, s32 shifts,
                   s32 shiftt) {
    gDPLoadTextureBlock(gDisplayListHead++, texture, fmt, G_IM_SIZ_32b, width, height, 0, cms, cmt, masks, maskt,
                        shifts, shiftt);
}

/**
 * Adds a 32-bit texture tile load to the display list.
 * @unverified Name from Stadium 1.
 */
void ParticleGfx_LoadTextureTile32(u8* texture, s32 fmt, s32 width, s32 height, s32 cms, s32 cmt, s32 masks, s32 maskt, s32 shifts,
                   s32 shiftt) {
    gDPLoadTextureTile(gDisplayListHead++, texture, fmt, G_IM_SIZ_32b, width, 0, 0, 0, width - 1, height - 1, 0, cms,
                       cmt, masks, maskt, shifts, shiftt);
}

/**
 * Adds a 16-bit texture block load to the display list.
 * @unverified Name from Stadium 1.
 */
void ParticleGfx_LoadTextureBlock16(u8* texture, s32 fmt, s32 width, s32 height, s32 cms, s32 cmt, s32 masks, s32 maskt, s32 shifts,
                   s32 shiftt) {
    gDPLoadTextureBlock(gDisplayListHead++, texture, fmt, G_IM_SIZ_16b, width, height, 0, cms, cmt, masks, maskt,
                        shifts, shiftt);
}

/**
 * Adds a 16-bit texture tile load to the display list.
 * @unverified Name from Stadium 1.
 */
void ParticleGfx_LoadTextureTile16(u8* texture, s32 fmt, s32 width, s32 height, s32 cms, s32 cmt, s32 masks, s32 maskt, s32 shifts,
                   s32 shiftt) {
    gDPLoadTextureTile(gDisplayListHead++, texture, fmt, G_IM_SIZ_16b, width, 0, 0, 0, width - 1, height - 1, 0, cms,
                       cmt, masks, maskt, shifts, shiftt);
}

/**
 * Adds an 8-bit texture block load to the display list.
 * @unverified Name from Stadium 1.
 */
void ParticleGfx_LoadTextureBlock8(u8* texture, s32 fmt, s32 width, s32 height, s32 cms, s32 cmt, s32 masks, s32 maskt, s32 shifts,
                   s32 shiftt) {
    gDPLoadTextureBlock(gDisplayListHead++, texture, fmt, G_IM_SIZ_8b, width, height, 0, cms, cmt, masks, maskt, shifts,
                        shiftt);
}

/**
 * Adds an 8-bit texture tile load to the display list.
 * @unverified Name from Stadium 1.
 */
void ParticleGfx_LoadTextureTile8(u8* texture, s32 fmt, s32 width, s32 height, s32 cms, s32 cmt, s32 masks, s32 maskt, s32 shifts,
                   s32 shiftt) {
    gDPLoadTextureTile(gDisplayListHead++, texture, fmt, G_IM_SIZ_8b, width, 0, 0, 0, width - 1, height - 1, 0, cms,
                       cmt, masks, maskt, shifts, shiftt);
}

/**
 * Adds a 4-bit texture block load to the display list.
 * @unverified Name from Stadium 1.
 */
void ParticleGfx_LoadTextureBlock4(u8* texture, s32 fmt, s32 width, s32 height, s32 cms, s32 cmt, s32 masks, s32 maskt, s32 shifts,
                   s32 shiftt) {
    gDPLoadTextureBlock_4b(gDisplayListHead++, texture, fmt, width, height, 0, cms, cmt, masks, maskt, shifts, shiftt);
}

/**
 * Adds a 4-bit texture tile load to the display list.
 * @unverified Name from Stadium 1.
 */
void ParticleGfx_LoadTextureTile4(u8* texture, s32 fmt, s32 width, s32 height, s32 cms, s32 cmt, s32 masks, s32 maskt, s32 shifts,
                   s32 shiftt) {
    gDPLoadTextureTile_4b(gDisplayListHead++, texture, fmt, width, 0, 0, 0, width - 1, height - 1, 0, cms, cmt, masks,
                          maskt, shifts, shiftt);
}

/**
 * Adds a 4-bit texture block load into TMEM address tmem and render tile rtile to the
 * display list.
 * @unverified Name from Stadium 1.
 */
void ParticleGfx_LoadTextureMultiBlock4(u8* texture, s32 tmem, s32 rtile, s32 fmt, s32 width, s32 height, s32 cms, s32 cmt, s32 masks,
                   s32 maskt, s32 shifts, s32 shiftt) {
    gDPLoadMultiBlock_4b(gDisplayListHead++, texture, tmem, rtile, fmt, width, height, 0, cms, cmt, masks, maskt,
                         shifts, shiftt);
}

/**
 * Append an RGBA32 texture block load with the specified addressing modes.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void ParticleGfx_LoadTextureRgba32(u8* texture, s32 width, s32 height) {
    ParticleGfx_LoadTextureBlock32(texture, G_IM_FMT_RGBA, width, height, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                  G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
}

/**
 * Append an RGBA32 texture tile load with the specified addressing modes.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void ParticleGfx_LoadTextureTileRgba32(u8* texture, s32 width, s32 height) {
    ParticleGfx_LoadTextureTile32(texture, G_IM_FMT_RGBA, width, height, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                  G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
}

/**
 * Append an RGBA16 texture block load with the specified addressing modes.
 * Seen in play (2026-11-13) in the 165-move sweep (Wing Attack, Vine Whip, Petal Dance, String
 * Shot, Dig): it emitted G_SETTIMG FD100000 (RGBA 16b) with the texture address, G_SETTILE,
 * G_RDPLOADSYNC and G_LOADBLOCK for 32x32.
 */
void ParticleGfx_LoadTextureRgba16(u8* texture, s32 width, s32 height) {
    ParticleGfx_LoadTextureBlock16(texture, G_IM_FMT_RGBA, width, height, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                  G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
}

/**
 * Load textures into the explicitly selected TMEM regions/tiles for multi-texture rendering.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void ParticleGfx_LoadTextureRgba16Dual(u8* texture1, u8* texture2, s32 width, s32 height) {
    gDPLoadMultiTile(gDisplayListHead++, texture1, 0x000, G_TX_RENDERTILE, G_IM_FMT_RGBA, G_IM_SIZ_16b, width, height,
                     0, 0, width - 1, height - 1, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                     G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

    gDPLoadMultiTile(gDisplayListHead++, texture2, 0x100, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, width, height, 0, 0,
                     width - 1, height - 1, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK,
                     G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
}

/**
 * Append an RGBA16 texture block load with the specified addressing modes.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void ParticleGfx_LoadTextureRgba16WrapS(u8* texture, s32 width, s32 height) {
    s32 masks = ParticleGfx_TextureSizeLog2(width);

    ParticleGfx_LoadTextureBlock16(texture, G_IM_FMT_RGBA, width, height, G_TX_MIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_CLAMP, masks,
                  G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
}

/**
 * Append an RGBA16 texture block load with the specified addressing modes.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void ParticleGfx_LoadTextureRgba16WrapT(u8* texture, s32 width, s32 height) {
    s32 maskt = ParticleGfx_TextureSizeLog2(height);

    ParticleGfx_LoadTextureBlock16(texture, G_IM_FMT_RGBA, width, height, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_MIRROR | G_TX_WRAP,
                  G_TX_NOMASK, maskt, G_TX_NOLOD, G_TX_NOLOD);
}

/**
 * Append an RGBA16 texture block load with the specified addressing modes.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void ParticleGfx_LoadTextureRgba16WrapST(u8* texture, s32 width, s32 height) {
    s32 masks = ParticleGfx_TextureSizeLog2(width);
    s32 maskt = ParticleGfx_TextureSizeLog2(height);

    ParticleGfx_LoadTextureBlock16(texture, G_IM_FMT_RGBA, width, height, G_TX_MIRROR | G_TX_WRAP, G_TX_MIRROR | G_TX_WRAP, masks, maskt,
                  G_TX_NOLOD, G_TX_NOLOD);
}

/**
 * Append an RGBA16 texture block load with the specified addressing modes.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void ParticleGfx_LoadTextureRgba16WrapSWithMask(u8* texture, s32 width, s32 height, s32 masks) {
    ParticleGfx_LoadTextureBlock16(texture, G_IM_FMT_RGBA, width, height, G_TX_MIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_CLAMP, masks,
                  G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
}

/**
 * Append an RGBA16 texture tile load with the specified addressing modes.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void ParticleGfx_LoadTextureTileRgba16(u8* texture, s32 width, s32 height) {
    ParticleGfx_LoadTextureTile16(texture, G_IM_FMT_RGBA, width, height, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                  G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
}

/**
 * Append an IA16 texture block load with the specified addressing modes.
 * No caller in play (2026-11-13): it is only called from ParticleGfx_DrawIa16TextureAtlas, which
 * has no caller in the ROM itself.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void ParticleGfx_LoadTextureIa16(u8* texture, s32 width, s32 height) {
    ParticleGfx_LoadTextureBlock16(texture, G_IM_FMT_IA, width, height, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                  G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
}

/**
 * Append an IA16 texture tile load with the specified addressing modes.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void ParticleGfx_LoadTextureTileIa16(u8* texture, s32 width, s32 height) {
    ParticleGfx_LoadTextureTile16(texture, G_IM_FMT_IA, width, height, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                  G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
}

/**
 * Append an IA8 texture block load with the specified addressing modes.
 * Seen in play (2026-11-13) in the 165-move sweep (Pound and most hit moves): it emitted G_SETTIMG
 * FD700000 (IA, loaded as 16b) with the texture address, G_SETTILE F5700000 07080200, G_RDPLOADSYNC
 * and G_LOADBLOCK.
 */
void ParticleGfx_LoadTextureIa8(u8* texture, s32 width, s32 height) {
    ParticleGfx_LoadTextureBlock8(texture, G_IM_FMT_IA, width, height, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                  G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
}

/**
 * Append an IA8 texture tile load with the specified addressing modes.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void ParticleGfx_LoadTextureTileIa8(u8* texture, s32 width, s32 height) {
    ParticleGfx_LoadTextureTile8(texture, G_IM_FMT_IA, width, height, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                  G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
}

/**
 * Append an IA8 texture block load with the specified addressing modes.
 * Seen in play (2026-11-13) in the 165-move sweep (Water Gun, Hydro Pump): it emitted an IA texture
 * load (FD700000) whose G_SETTILE (07058160) sets mirror+wrap on S and T with mask 6 for 64x64.
 */
void ParticleGfx_LoadTextureIa8WrapST(u8* texture, s32 width, s32 height) {
    s32 masks = ParticleGfx_TextureSizeLog2(width);
    s32 maskt = ParticleGfx_TextureSizeLog2(height);

    ParticleGfx_LoadTextureBlock8(texture, G_IM_FMT_IA, width, height, G_TX_MIRROR | G_TX_WRAP, G_TX_MIRROR | G_TX_WRAP, masks, maskt,
                  G_TX_NOLOD, G_TX_NOLOD);
}

/**
 * Append an I8 texture block load with the specified addressing modes.
 * No caller in play (2026-11-13): it is only called from ParticleGfx_DrawI8TextureAtlas and
 * ParticleGfx_LoadTextureI8Alias, which have no caller in the ROM themselves.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void ParticleGfx_LoadTextureI8(u8* texture, s32 width, s32 height) {
    ParticleGfx_LoadTextureBlock8(texture, G_IM_FMT_I, width, height, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                  G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
}

/**
 * Append an I8 texture block load with the specified addressing modes.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void ParticleGfx_LoadTextureI8WrapST(u8* texture, s32 width, s32 height) {
    s32 masks = ParticleGfx_TextureSizeLog2(width);
    s32 maskt = ParticleGfx_TextureSizeLog2(height);

    ParticleGfx_LoadTextureBlock8(texture, G_IM_FMT_I, width, height, G_TX_MIRROR | G_TX_WRAP, G_TX_MIRROR | G_TX_WRAP, masks, maskt,
                  G_TX_NOLOD, G_TX_NOLOD);
}

/**
 * Append an I8 texture tile load with the specified addressing modes.
 * No caller in play (2026-11-13): it is only called from ParticleGfx_LoadTextureTileI8Alias, which
 * has no caller in the ROM itself.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void ParticleGfx_LoadTextureTileI8(u8* texture, s32 width, s32 height) {
    ParticleGfx_LoadTextureTile8(texture, G_IM_FMT_I, width, height, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                  G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
}

/**
 * Forward the texture and dimensions to the matching texture-load wrapper.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void ParticleGfx_LoadTextureI8Alias(u8* texture, s32 width, s32 height) {
    ParticleGfx_LoadTextureI8(texture, width, height);
}

/**
 * Forward the texture and dimensions to the matching texture-load wrapper.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void ParticleGfx_LoadTextureTileI8Alias(u8* texture, s32 width, s32 height) {
    ParticleGfx_LoadTextureTileI8(texture, width, height);
}

/**
 * Append an IA4 texture tile load with the specified addressing modes.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void ParticleGfx_LoadTextureTileIa4(u8* texture, s32 width, s32 height) {
    ParticleGfx_LoadTextureTile4(texture, G_IM_FMT_IA, width, height, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                  G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
}

/**
 * Append an I4 texture tile load with the specified addressing modes.
 * Seen in play (2026-11-13) in the 165-move sweep (Scratch, Cut, Vine Whip, Water Gun, Surf): it
 * emitted G_SETTIMG FD88000B (I, 8b) and G_LOADTILE (F4...) for a 24x24 texture, not a block load.
 */
void ParticleGfx_LoadTextureTileI4(u8* texture, s32 width, s32 height) {
    ParticleGfx_LoadTextureTile4(texture, G_IM_FMT_I, width, height, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                  G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
}

/**
 * Append an IA4 texture block load with the specified addressing modes.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void ParticleGfx_LoadTextureIa4(u8* texture, s32 width, s32 height) {
    ParticleGfx_LoadTextureBlock4(texture, G_IM_FMT_IA, width, height, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                  G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
}

/**
 * Append an I4 texture block load with the specified addressing modes.
 * Seen in play (2026-11-13) in the 165-move sweep (Pound and most hit moves): it emitted G_SETTIMG
 * FD900000 (I, loaded as 16b) with the texture address, G_SETTILE, G_RDPLOADSYNC and G_LOADBLOCK.
 */
void ParticleGfx_LoadTextureI4(u8* texture, s32 width, s32 height) {
    ParticleGfx_LoadTextureBlock4(texture, G_IM_FMT_I, width, height, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                  G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
}

/**
 * Append an I4 texture block load with the specified addressing modes.
 * Seen in play (2026-11-13) in the 165-move sweep (Razor Wind, Whirlwind, Slam and others): it
 * emitted an I texture load (FD900000) whose G_SETTILE (07058160) sets mirror+wrap on S and T with
 * mask 6 for 64x64.
 */
void ParticleGfx_LoadTextureI4WrapST(u8* texture, s32 width, s32 height) {
    s32 masks = ParticleGfx_TextureSizeLog2(width);
    s32 maskt = ParticleGfx_TextureSizeLog2(height);

    ParticleGfx_LoadTextureBlock4(texture, G_IM_FMT_I, width, height, G_TX_MIRROR | G_TX_WRAP, G_TX_MIRROR | G_TX_WRAP, masks, maskt,
                  G_TX_NOLOD, G_TX_NOLOD);
}

/**
 * Forward the texture and dimensions to the matching texture-load wrapper.
 * Seen in play (2026-11-13) in the 165-move sweep: it forwarded to ParticleGfx_LoadTextureI4 with
 * the same arguments and the same commands were emitted.
 */
void ParticleGfx_LoadTextureI4Alias(u8* texture, s32 width, s32 height) {
    ParticleGfx_LoadTextureI4(texture, width, height);
}

/**
 * Forward the texture and dimensions to the matching texture-load wrapper.
 * Seen in play (2026-11-13) in the 165-move sweep (Scratch, Cut and others): it forwarded to
 * ParticleGfx_LoadTextureTileI4 with the same arguments and the same commands were emitted.
 */
void ParticleGfx_LoadTextureTileI4Alias(u8* texture, s32 width, s32 height) {
    ParticleGfx_LoadTextureTileI4(texture, width, height);
}

/**
 * Append an I4 texture block load with the specified addressing modes.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void ParticleGfx_LoadTextureI4WrapS(u8* texture, s32 width, s32 height) {
    s32 masks = ParticleGfx_TextureSizeLog2(width);

    ParticleGfx_LoadTextureBlock4(texture, G_IM_FMT_I, width, height, G_TX_MIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_CLAMP, masks,
                  G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
}

/**
 * Append an I4 texture block load with the specified addressing modes.
 * Seen in play (2026-11-13) in the 165-move sweep (Sing, powders, Hypnosis): it emitted an I
 * texture load (FD900000) whose G_SETTILE (07018060) sets wrap without mirror on S and T with mask
 * 6.
 */
void ParticleGfx_LoadTextureI4WrapSTNoMirror(u8* texture, s32 width, s32 height) {
    s32 masks = ParticleGfx_TextureSizeLog2(width);
    s32 maskt = ParticleGfx_TextureSizeLog2(height);

    ParticleGfx_LoadTextureBlock4(texture, G_IM_FMT_I, width, height, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, masks,
                  maskt, G_TX_NOLOD, G_TX_NOLOD);
}

/**
 * Load textures into the explicitly selected TMEM regions/tiles for multi-texture rendering.
 * Seen in play (2026-11-13) in the 165-move sweep (Poisonpowder, Stun Spore, Sleep Powder): it
 * emitted an I texture load into TMEM 0x100 (G_SETTILE F5900100) with wrap, mask 6.
 */
void ParticleGfx_LoadTextureI4MultiBlockWrapST(u8* texture, s32 width, s32 height) {
    s32 tmem = 0x100;
    s32 rtile = 1;
    s32 masks = ParticleGfx_TextureSizeLog2(width);
    s32 maskt = ParticleGfx_TextureSizeLog2(height);

    ParticleGfx_LoadTextureMultiBlock4(texture, tmem, rtile, G_IM_FMT_I, width, height, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP,
                  masks, maskt, G_TX_NOLOD, G_TX_NOLOD);
}

/**
 * Load textures into the explicitly selected TMEM regions/tiles for multi-texture rendering.
 * Seen in play (2026-11-13) in the 165-move sweep (Flamethrower, Dragon Rage, Fire Spin, Fire
 * Blast): it emitted an I texture load into TMEM 0x100 (F5900100) whose tile word 07018462 carries
 * the S shift of 2.
 */
void ParticleGfx_LoadTextureI4MultiBlockWrapSTWithShift(u8* texture, s32 width, s32 height, s32 shifts, s32 shiftt) {
    s32 tmem = 0x100;
    s32 rtile = 1;
    s32 masks = ParticleGfx_TextureSizeLog2(width);
    s32 maskt = ParticleGfx_TextureSizeLog2(height);

    ParticleGfx_LoadTextureMultiBlock4(texture, tmem, rtile, G_IM_FMT_I, width, height, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP,
                  masks, maskt, shifts, shiftt);
}

/**
 * Append an CI8 texture block load with the specified addressing modes.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void ParticleGfx_LoadTextureCi8(u8* texture, s32 width, s32 height) {
    ParticleGfx_LoadTextureBlock8(texture, G_IM_FMT_CI, width, height, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                  G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
}

/**
 * Append an CI8 texture block load with the specified addressing modes.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void ParticleGfx_LoadTextureCi8WrapSWithMask(u8* texture, s32 width, s32 height, s32 masks) {
    ParticleGfx_LoadTextureBlock8(texture, G_IM_FMT_CI, width, height, G_TX_MIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_CLAMP, masks,
                  G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
}

/**
 * Append an CI8 texture tile load with the specified addressing modes.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void ParticleGfx_LoadTextureTileCi8(u8* texture, s32 width, s32 height) {
    ParticleGfx_LoadTextureTile8(texture, G_IM_FMT_CI, width, height, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                  G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
}

/**
 * Load textures into the explicitly selected TMEM regions/tiles for multi-texture rendering.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void ParticleGfx_LoadTextureDualRgba16I8(u8* texture1, u8* texture2, s32 width, s32 height) {
    gDPSetCombineLERP(gDisplayListHead++, 0, 0, 0, TEXEL0, 0, 0, 0, TEXEL1, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED);

    gDPLoadMultiBlock(gDisplayListHead++, texture2, 0x100, G_TX_RENDERTILE, G_IM_FMT_I, G_IM_SIZ_8b, width, height, 0,
                      G_TX_MIRROR | G_TX_CLAMP, G_TX_MIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                      G_TX_NOLOD);

    gDPLoadTextureBlock(gDisplayListHead++, texture1, G_IM_FMT_RGBA, G_IM_SIZ_16b, width, height, 0,
                        G_TX_MIRROR | G_TX_CLAMP, G_TX_MIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                        G_TX_NOLOD);

    gDPSetTile(gDisplayListHead++, G_IM_FMT_I, G_IM_SIZ_8b, ((width) + 7) >> 3, 0x0100, 1, 0, G_TX_NOMIRROR | G_TX_WRAP,
               G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD);

    gDPSetTileSize(gDisplayListHead++, 1, 0, 0, (width - 1) << 2, (height - 1) << 2);
}

/**
 * Load four vertices and emit two triangles.
 * Seen in play (2026-11-13) in the 165-move sweep (Mist, powders, Haze, Smog): it emitted G_VTX
 * 01004008 (four vertices from the argument) and G_DL to D_82191910.
 */
void ParticleGfx_DrawQuadVertices(Vtx* arg0) {
    gSPVertex(gDisplayListHead++, arg0, 4, 0);
    gSPDisplayList(gDisplayListHead++, D_82191910);
}

/**
 * Empty callback retained at its original entry point.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void ParticleGfx_NoopStub4(void) {
}

/**
 * Load the supplied position/rotation/scale transform, then draw the selected vertices.
 * Seen in play (2026-11-13) in the 165-move sweep (Scratch, Cut, Slam and others): it emitted G_MTX
 * DA380003, then G_VTX for four vertices and G_DL to D_82191910.
 */
void ParticleGfx_DrawTransformedQuad(Vec3f arg0, Vec3s arg1, f32 arg2, Vtx* arg3) {
    ParticleGfx_PushTransformMatrix(arg0, arg1, arg2);

    gSPVertex(gDisplayListHead++, arg3, 4, 0);
    gSPDisplayList(gDisplayListHead++, D_82191910);
}

/**
 * Load the supplied position/rotation/scale transform, then draw the selected vertices.
 * Seen in play (2026-11-13) in the 165-move sweep (Thunderpunch, Hyper Beam, Thundershock,
 * Thunderbolt, Thunder): it emitted G_MTX DA380003, then G_VTX for four vertices and G_DL to
 * D_82191910.
 */
void ParticleGfx_DrawTransformedQuadYScaled(Vec3f arg0, Vec3s arg1, f32 arg3, Vtx* arg4) {
    ParticleGfx_PushTransformMatrixYScaled(arg0, arg1, arg3);

    gSPVertex(gDisplayListHead++, arg4, 4, 0);
    gSPDisplayList(gDisplayListHead++, D_82191910);
}

/**
 * Load the supplied position/rotation/scale transform, then draw the selected vertices.
 * Not reached in play (2026-11-13): no move in the 165-move battle sweep called it (each move used
 * once, from the command menu to the end of its turn).
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void ParticleGfx_DrawTransformedQuadXYScaled(Vec3f arg0, Vec3s arg1, f32 arg2, f32 arg3, Vtx* arg4) {
    ParticleGfx_PushTransformMatrixXYScaled(arg0, arg1, arg2, arg3);

    gSPVertex(gDisplayListHead++, arg4, 4, 0);
    gSPDisplayList(gDisplayListHead++, D_82191910);
}

/**
 * Load the supplied position/rotation/scale transform, then draw the selected vertices.
 * Seen in play (2026-11-13) in a Free Battle switch (1P switched to its second Pokémon) it ran
 * while the new Pokémon was sent out.
 * Seen in play (2026-11-13) it also ran when COM sent out its next Pokémon (ゆけっ！ゲンのすけ) after its
 * first one fainted.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void ParticleGfx_DrawTransformedTriangle(Vec3f arg0, Vec3s arg1, f32 arg2, Vtx* arg3) {
    ParticleGfx_PushTransformMatrix(arg0, arg1, arg2);

    gSPVertex(gDisplayListHead++, arg3, 3, 0);
    gSPDisplayList(gDisplayListHead++, D_82191900);
}

/**
 * Load a camera-facing transform, then draw the selected quad or triangle vertices.
 * Seen in play (2026-11-13) in the 165-move sweep (Pound and most hit moves): called with the
 * battle camera, it emitted G_MTX DA380003, then G_VTX for four vertices and G_DL to D_82191910.
 */
void ParticleGfx_DrawModelQuad(CameraNode* arg0, Vec3f arg1, f32 arg2, Vtx* arg3) {
    ParticleGfx_PushBillboardMatrix(arg0, arg1, arg2);

    gSPVertex(gDisplayListHead++, arg3, 4, 0);
    gSPDisplayList(gDisplayListHead++, D_82191910);
}

/**
 * Load a camera-facing transform, then draw the selected quad or triangle vertices.
 * Seen in play (2026-11-13) in the 165-move sweep (Pay Day, Ice Punch, Ice Beam, Blizzard, Psybeam,
 * Aurora Beam): called with the battle camera, it emitted G_MTX DA380003, G_VTX and G_DL to
 * D_82191910.
 */
void ParticleGfx_DrawModelQuadRotated(CameraNode* arg0, Vec3f arg1, f32 arg2, Vtx* arg3, s16 arg4) {
    ParticleGfx_PushBillboardRotatedMatrix(arg0, arg1, arg2, arg4);

    gSPVertex(gDisplayListHead++, arg3, 4, 0);
    gSPDisplayList(gDisplayListHead++, D_82191910);
}

/**
 * Load a camera-facing transform, then draw the selected quad or triangle vertices.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void ParticleGfx_DrawModelQuadYScaled(CameraNode* arg0, Vec3f arg1, f32 arg2, Vtx* arg3) {
    ParticleGfx_PushBillboardMatrixYScaled(arg0, arg1, arg2);

    gSPVertex(gDisplayListHead++, arg3, 4, 0);
    gSPDisplayList(gDisplayListHead++, D_82191910);
}

/**
 * Load a camera-facing transform, then draw the selected quad or triangle vertices.
 * Seen in play (2026-11-13) in the 165-move sweep (Hyper Beam, Thundershock, Thunderbolt, Thunder):
 * called with the battle camera, it emitted G_MTX DA380003, G_VTX and G_DL to D_82191910.
 */
void ParticleGfx_DrawModelQuadRotatedYScaled(CameraNode* arg0, Vec3f arg1, f32 arg2, Vtx* arg3, s16 arg4) {
    ParticleGfx_PushBillboardRotatedMatrixYScaled(arg0, arg1, arg2, arg4);

    gSPVertex(gDisplayListHead++, arg3, 4, 0);
    gSPDisplayList(gDisplayListHead++, D_82191910);
}

/**
 * Load a camera-facing transform, then draw the selected quad or triangle vertices.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void ParticleGfx_DrawModelTriangle(CameraNode* arg0, Vec3f arg1, f32 arg2, Vtx* arg3) {
    ParticleGfx_PushBillboardMatrix(arg0, arg1, arg2);

    gSPVertex(gDisplayListHead++, arg3, 3, 0);
    gSPDisplayList(gDisplayListHead++, D_82191900);
}

/**
 * Load a camera-facing transform, then draw the selected quad or triangle vertices.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void ParticleGfx_DrawModelTriangleRotated(CameraNode* arg0, Vec3f arg1, f32 arg2, Vtx* arg3, s16 arg4) {
    ParticleGfx_PushBillboardRotatedMatrix(arg0, arg1, arg2, arg4);

    gSPVertex(gDisplayListHead++, arg3, 3, 0);
    gSPDisplayList(gDisplayListHead++, D_82191900);
}

/**
 * Walk the texture atlas in fixed-size chunks, loading each chunk and drawing its four corresponding vertices.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void ParticleGfx_DrawI8TextureAtlas(u8* texture, Vtx* vtx, s32 arg2, s32 arg3, s32 width, s32 height) {
    s32 i;
    s32 j;
    s32 var_s4 = 0;
    u8* var_s3 = texture;

    for (i = 0; i < arg3 / height; i++) {
        for (j = 0; j < arg2 / width; j++) {
            ParticleGfx_LoadTextureI8(var_s3, width, height);

            gSPVertex(gDisplayListHead++, &vtx[var_s4], 4, 0);
            gSPDisplayList(gDisplayListHead++, D_82191910);

            var_s3 += width * height;
            var_s4 += 4;
        }
    }

    gSPTexture(gDisplayListHead++, 0x0001, 0x0001, 0, G_TX_RENDERTILE, G_OFF);
}

/**
 * Walk the texture atlas in fixed-size chunks, loading each chunk and drawing its four corresponding vertices.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void ParticleGfx_DrawIa16TextureAtlas(u8* texture, Vtx* vtx, s32 arg2, s32 arg3, s32 width, s32 height) {
    s32 i;
    s32 j;
    s32 var_s4 = 0;
    u8* var_s3 = texture;

    for (i = 0; i < arg3 / height; i++) {
        for (j = 0; j < arg2 / width; j++) {
            ParticleGfx_LoadTextureIa16(var_s3, width, height);

            gSPVertex(gDisplayListHead++, &vtx[var_s4], 4, 0);
            gSPDisplayList(gDisplayListHead++, D_82191910);

            var_s3 += (width * height) * 2;
            var_s4 += 4;
        }
    }

    gSPTexture(gDisplayListHead++, 0x0001, 0x0001, 0, G_TX_RENDERTILE, G_OFF);
}

/**
 * Walk the texture atlas in fixed-size chunks, loading each chunk and drawing its four corresponding vertices.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void ParticleGfx_DrawIa8TextureAtlas(u8* texture, Vtx* vtx, s32 arg2, s32 arg3, s32 width, s32 height) {
    s32 i;
    s32 j;
    s32 var_s4 = 0;
    u8* var_s3 = texture;

    for (i = 0; i < arg3 / height; i++) {
        for (j = 0; j < arg2 / width; j++) {
            ParticleGfx_LoadTextureIa8(var_s3, width, height);

            gSPVertex(gDisplayListHead++, &vtx[var_s4], 4, 0);
            gSPDisplayList(gDisplayListHead++, D_82191910);

            var_s3 += width * height;
            var_s4 += 4;
        }
    }

    gSPTexture(gDisplayListHead++, 0x0001, 0x0001, 0, G_TX_RENDERTILE, G_OFF);
}

/**
 * Walk the texture atlas in fixed-size chunks, loading each chunk and drawing its four corresponding vertices.
 * Seen in play (2026-11-13) in the 165-move sweep (Scratch, Cut, Vine Whip): for a 64x64 atlas it
 * emitted an I texture load per chunk (FD900000 with 0x8033CA40, then 0x8033D240) each followed by
 * its quad.
 */
void ParticleGfx_DrawI4TextureAtlas(u8* texture, Vtx* vtx, s32 arg2, s32 arg3, s32 width, s32 height) {
    s32 i;
    s32 j;
    s32 var_s4 = 0;
    u8* var_s3 = texture;

    for (i = 0; i < arg3 / height; i++) {
        for (j = 0; j < arg2 / width; j++) {
            ParticleGfx_LoadTextureI4(var_s3, width, height);

            gSPVertex(gDisplayListHead++, &vtx[var_s4], 4, 0);
            gSPDisplayList(gDisplayListHead++, D_82191910);

            var_s3 += (width * height) / 2;
            var_s4 += 4;
        }
    }

    gSPTexture(gDisplayListHead++, 0x0001, 0x0001, 0, G_TX_RENDERTILE, G_OFF);
}

/**
 * Walk the texture atlas in fixed-size chunks, loading each chunk and drawing its four corresponding vertices.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void ParticleGfx_DrawI4TextureAtlasTiled(u8* texture, Vtx* vtx, s32 arg2, s32 arg3, s32 width, s32 height) {
    s32 i;
    s32 j;
    s32 var_s4 = 0;
    u8* var_s3 = texture;

    for (i = 0; i < arg3 / height; i++) {
        for (j = 0; j < arg2 / width; j++) {
            ParticleGfx_LoadTextureTileI4(var_s3, width, height);

            gSPVertex(gDisplayListHead++, &vtx[var_s4], 4, 0);
            gSPDisplayList(gDisplayListHead++, D_82191910);

            var_s3 += (width * height) / 2;
            var_s4 += 4;
        }
    }

    gSPTexture(gDisplayListHead++, 0x0001, 0x0001, 0, G_TX_RENDERTILE, G_OFF);
}
