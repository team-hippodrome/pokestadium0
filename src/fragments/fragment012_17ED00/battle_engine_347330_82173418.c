/* Fixed-layout split; original translation-unit boundaries remain unconfirmed. */
#include "battle_engine_347330.h"

/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Surf.
 */
Gfx* SurfTerrainGrid_Draw(Gfx* arg0) {
    static Gfx D_84388F80[] = {
        gsDPPipeSync(),
        gsDPSetCycleType(G_CYC_2CYCLE),
        gsSPClearGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN |
                              G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH | G_CLIPPING | 0x0040F9FA),
        gsSPSetGeometryMode(G_ZBUFFER | G_SHADE | G_SHADING_SMOOTH),
        gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
        gsDPPipeSync(),
        gsDPSetTexturePersp(G_TP_PERSP),
        gsDPSetTextureDetail(G_TD_CLAMP),
        gsDPSetTextureLOD(G_TL_TILE),
        gsDPSetTextureLUT(G_TT_NONE),
        gsDPSetTextureConvert(G_TC_FILT),
        gsDPSetTextureFilter(G_TF_BILERP),
        gsDPSetRenderMode(G_RM_PASS, G_RM_ZB_XLU_SURF2),
        gsDPSetCombineLERP(TEXEL1, TEXEL0, PRIM_LOD_FRAC, TEXEL0, 0, 0, 0, PRIMITIVE, PRIMITIVE, ENVIRONMENT, COMBINED,
                           ENVIRONMENT, COMBINED, 0, SHADE, 0),
        gsSPEndDisplayList(),
    };
    static Gfx D_84388FF8[] = {
        gsDPPipeSync(),
        gsDPSetCycleType(G_CYC_2CYCLE),
        gsSPClearGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN |
                              G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH | G_CLIPPING | 0x0040F9FA),
        gsSPSetGeometryMode(G_SHADE | G_SHADING_SMOOTH),
        gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
        gsDPPipeSync(),
        gsDPSetRenderMode(G_RM_PASS, G_RM_XLU_SURF2),
        gsDPSetCombineLERP(TEXEL1, TEXEL0, PRIM_LOD_FRAC, TEXEL0, TEXEL1, TEXEL0, PRIM_LOD_FRAC, TEXEL0, PRIMITIVE,
                           ENVIRONMENT, COMBINED, ENVIRONMENT, COMBINED, 0, PRIMITIVE, 0),
        gsDPSetColorDither(G_CD_NOISE),
        gsDPSetPrimColor(0, 0x80, 0, 50, 255, 100),
        gsDPSetEnvColor(0, 100, 255, 100),
        gsSPEndDisplayList(),
    };

    unk_D_843951D0_1010* var_v1;
    Vtx* vtx;
    s32 i;
    s32 j;
    f32 sp134;
    f32 sp130;
    f32 sp12C;
    f32 sp128;
    f32 sp124;
    f32 sp120;
    f32 sp11C;
    f32 temp_fv0;
    Vtx* temp_v0;
    f32 sp110;
    s16 var_a2;
    s16 var_t0;
    s32 idx1;
    s32 idx2;

    sWaterHeightMap.unk_000C = Gfx_AllocDisplayList(sizeof(Vtx) * 16 * 16);
    vtx = sWaterHeightMap.unk_000C;
    var_v1 = &sWaterHeightMap.grid[0][0];

    for (i = 0; i < 16; i++) {
        for (j = 0; j < 16; j++) {
            vtx->v.ob[0] = var_v1->unk_00;
            vtx->v.ob[1] = var_v1->unk_04;
            vtx->v.ob[2] = var_v1->unk_08;
            vtx->v.tc[0] = (i * 0x800) / 3;
            vtx->v.tc[1] = (j * 0x800) / 3;
            vtx->v.cn[3] = var_v1->unk_10;
            vtx++;
            var_v1++;
        }
    }

    gSPDisplayList(arg0++, D_84388F80);
    gDPPipeSync(arg0++);

    if (sWaterHeightMap.unk_0000 < 0xA) {
        var_a2 = 0;
        var_t0 = (sWaterHeightMap.unk_0000 * 0xFF) / 10;
    } else if (sWaterHeightMap.unk_0000 < 0x14) {
        var_a2 = ((sWaterHeightMap.unk_0000 * 0xFF) - 0x9F6) / 10;
        var_t0 = 0xFF;
    } else {
        var_a2 = 0xFF;
        var_t0 = 0xFF;
    }

    gDPSetPrimColor(arg0++, 0, 0xB4, 255, 255, 255, var_t0);
    gDPSetEnvColor(arg0++, 0, 0x64, 0xC8, var_a2);
    gDPSetBlendColor(arg0++, 255, 255, 255, 255); // #FFFFFFFF

    gDPLoadTextureTile_4b(arg0++, sBattleAnimAssetPointers[0xB8], G_IM_FMT_I, 32, 0, 0, 0, 31, 31, 0, G_TX_NOMIRROR | G_TX_WRAP,
                          G_TX_NOMIRROR | G_TX_WRAP, 5, 5, 1, 1);
    gDPSetTileSize(arg0++, G_TX_RENDERTILE, D_821A1B20, -D_821A1B20, D_821A1B20 + 0x1F, 0x1F - D_821A1B20);

    gDPLoadMultiTile_4b(arg0++, sBattleAnimAssetPointers[0xB9], 0x0100, 1, G_IM_FMT_I, 32, 0, 0, 0, 31, 31, 0,
                        G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, 5, 5, 1, 1);
    gDPSetTileSize(arg0++, 1, D_821A1B22, D_821A1B22, D_821A1B22 + 0x1F, D_821A1B22 + 0x1F);

    vtx = sWaterHeightMap.unk_000C;
    for (i = 0; i < 15; i++) {
        for (j = 0; j < 15; j++) {
            idx1 = (i + 0) * 16 + j;
            idx2 = (i + 1) * 16 + j;
            gSPVertex(arg0++, &vtx[idx1 + 0], 1, 0);
            gSPVertex(arg0++, &vtx[idx1 + 1], 1, 1);
            gSPVertex(arg0++, &vtx[idx2 + (0 * 16) + 0], 1, 2);
            gSPVertex(arg0++, &vtx[idx1 + (1 * 16) + 1], 1, 3);
            gSP2Triangles(arg0++, 0, 2, 1, 0, 2, 3, 1, 0);
        }
    }

    sp12C = (D_821A1B28.unk_00 - D_821A1B28.unk_0C) + D_821A1B28.unk_18;
    sp130 = (D_821A1B28.unk_04 - D_821A1B28.unk_10) + D_821A1B28.unk_1C;
    sp134 = (D_821A1B28.unk_08 - D_821A1B28.unk_14) + D_821A1B28.unk_20;
    sp11C = SurfTerrainGrid_SampleHeightAndSlope(sp12C, sp134, &sp110);

    sp120 = D_821A1B28.unk_00 + D_821A1B28.unk_0C + D_821A1B28.unk_18;
    sp124 = D_821A1B28.unk_04 + D_821A1B28.unk_10 + D_821A1B28.unk_1C;
    sp128 = D_821A1B28.unk_08 + D_821A1B28.unk_14 + D_821A1B28.unk_20;
    temp_fv0 = SurfTerrainGrid_SampleHeightAndSlope(sp120, sp128, &sp110);

    if ((sp130 < sp11C) || (sp124 < temp_fv0)) {
        temp_v0 = Gfx_AllocDisplayList(sizeof(Vtx) * 4);

        temp_v0[0].v.ob[0] = (D_821A1B28.unk_00 - D_821A1B28.unk_0C) - D_821A1B28.unk_18;
        temp_v0[0].v.ob[1] = sp11C;
        temp_v0[0].v.ob[2] = (D_821A1B28.unk_08 - D_821A1B28.unk_14) - D_821A1B28.unk_20;
        temp_v0[0].v.tc[0] = 0;
        temp_v0[0].v.tc[1] = 0;

        temp_v0[1].v.ob[0] = (D_821A1B28.unk_00 + D_821A1B28.unk_0C) - D_821A1B28.unk_18;
        temp_v0[1].v.ob[1] = sp11C;
        temp_v0[1].v.ob[2] = (D_821A1B28.unk_08 + D_821A1B28.unk_14) - D_821A1B28.unk_20;
        temp_v0[1].v.tc[0] = 0x3E0;
        temp_v0[1].v.tc[1] = 0;

        temp_v0[2].v.ob[0] = sp12C;
        temp_v0[2].v.ob[1] = sp130;
        temp_v0[2].v.ob[2] = sp134;
        temp_v0[2].v.tc[0] = 0;
        temp_v0[2].v.tc[1] = 0x3E0;

        temp_v0[3].v.ob[0] = sp120;
        temp_v0[3].v.ob[1] = sp124;
        temp_v0[3].v.ob[2] = sp128;
        temp_v0[3].v.tc[0] = 0x3E0;
        temp_v0[3].v.tc[1] = 0x3E0;

        gSPDisplayList(arg0++, D_84388FF8);
        gDPLoadTextureTile_4b(arg0++, sBattleAnimAssetPointers[0xBA], G_IM_FMT_I, 32, 0, 0, 0, 31, 31, 0, G_TX_NOMIRROR | G_TX_WRAP,
                              G_TX_NOMIRROR | G_TX_WRAP, 5, 5, 15, G_TX_NOLOD);
        gDPSetTileSize(arg0++, G_TX_RENDERTILE, D_821A1B24, 0, D_821A1B24 + 0x1F, 0x001F);
        gDPLoadMultiTile_4b(arg0++, sBattleAnimAssetPointers[0xBA], 0x0100, 1, G_IM_FMT_I, 32, 0, 0, 0, 31, 31, 0,
                            G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, 5, 5, 14, G_TX_NOLOD);
        gDPSetTileSize(arg0++, 1, -D_821A1B24, 0, 0x1F - D_821A1B24, 0x001F);
        gSPVertex(arg0++, temp_v0, 4, 0);
        gSP2Triangles(arg0++, 0, 2, 1, 0, 2, 3, 1, 0);
    }

    return arg0;
}
