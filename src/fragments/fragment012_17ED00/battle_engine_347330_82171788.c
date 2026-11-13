/* Fixed-layout split; original translation-unit boundaries remain unconfirmed. */
#include "battle_engine_347330.h"

/**
 * Part of the stat-change ribbon (see StatRibbon_Spawn).
 * Not reached in play (2026-11-13): did not run in a tour of the main menu, Pokédex, party, Lab,
 * registration, Free Battle setup and a COM battle (opening, a switch, running, a Pound turn).
 * @unverified Named after the ribbon seen in play; this function itself was not traced.
 */
void StatRibbon_UpdateEnvAlpha(RibbonMesh* arg0) {
    s32 var_v0;

    if (arg0->unk_01C >= 0) {
        if ((arg0->unk_01A - 0x1E) < arg0->unk_018) {
            var_v0 = arg0->unk_044 - 0xA;
            if (var_v0 < 0) {
                var_v0 = 0;
            }
            arg0->unk_044 = var_v0;
        }
    } else {
        var_v0 = arg0->unk_044 + 8;
        if (var_v0 >= 0x100) {
            var_v0 = 0xFF;
        }
        arg0->unk_044 = var_v0;
    }
}

/**
 * Part of the stat-change ribbon (see StatRibbon_Spawn).
 * Not reached in play (2026-11-13): did not run in a tour of the main menu, Pokédex, party, Lab,
 * registration, Free Battle setup and a COM battle (opening, a switch, running, a Pound turn).
 * @unverified Named after the ribbon seen in play; this function itself was not traced.
 */
s32 StatRibbon_Update(RibbonMesh* arg0) {
    RibbonMeshVertexState* temp_s0;
    RibbonMeshVertexState* temp_s1;
    RibbonMeshVertexState* ptr;
    s32 i;
    f32 sp9C;
    f32 sp98;
    f32 sp94;
    f32 sp90;
    f32 sp8C;
    f32 sp88;
    f32 sp84;
    f32 sp80;
    f32 sp7C;
    f32 sp78;
    f32 temp_fa0;
    s16 temp_s6;
    s16 var_s5;
    Vtx* var_s2;
    s32 tmp;

    ptr = &arg0->unk_430[0];

    arg0->unk_018++;
    tmp = arg0->unk_018;

    sp9C = arg0->unk_010;
    sp80 = arg0->unk_004;
    sp7C = arg0->unk_008;
    sp78 = arg0->unk_00C;
    sp98 = arg0->unk_014;
    temp_s6 = arg0->unk_01C;
    sp84 = arg0->unk_020 * tmp;

    var_s2 = &arg0->unk_050[0];
    StatRibbon_UpdateEnvAlpha(arg0);

    var_s5 = 0;
    sp94 = 0.0f;
    sp90 = 0.0f;
    sp8C = 0.0f;
    sp88 = 0.0f;

    for (i = 0; i < 31; i++) {
        temp_s0 = ptr++;
        temp_s1 = ptr++;

        if (i == 0x1E) {
            sp94 = 0.0f;
            sp90 = 0.0f;
            sp8C = 0.0f;
            sp88 = 0.0f;
        }
        temp_s0->unk_18 += D_DBL_821979B8;
        temp_s0->unk_14 -= D_FLT_821979C0;

        if (temp_s6 != -1) {
            if (temp_s6 == 1) {
                temp_s0->unk_04 = ((((2.0 * __sinf(temp_s0->unk_14 + temp_s0->unk_18 + sp94)) -
                                     (__cosf(temp_s0->unk_14 + temp_s0->unk_18 + sp90) * 3.0)) +
                                    sp84) *
                                   sp98) +
                                  sp7C;
                temp_s1->unk_04 = (((((5.0 * __sinf(temp_s1->unk_14 + temp_s1->unk_18 + sp8C)) -
                                      (__cosf(temp_s1->unk_14 + temp_s1->unk_18 + sp88) * 3.0)) +
                                     sp84) *
                                    sp98) +
                                   sp7C) -
                                  50.0;

                if (temp_s1->unk_04 > 400.0) {
                    var_s5++;
                }

                if (temp_s0->unk_04 < 0.0) {
                    temp_s0->unk_04 = 0.0f;
                }

                if (temp_s1->unk_04 < 0.0) {
                    temp_s1->unk_04 = 0.0f;
                }
            }
        } else {
            temp_s0->unk_04 = sp7C - ((((2.0 * __sinf(temp_s0->unk_14 + temp_s0->unk_18 + sp94)) -
                                        (__cosf(temp_s0->unk_14 + temp_s0->unk_18 + sp90) * 3.0)) +
                                       sp84) *
                                      sp98);
            temp_s1->unk_04 = (sp7C - ((((5.0 * __sinf(temp_s1->unk_14 + temp_s1->unk_18 + sp8C)) -
                                         (__cosf(temp_s1->unk_14 + temp_s1->unk_18 + sp88) * 3.0)) +
                                        sp84) *
                                       sp98)) -
                              50.0;

            if (temp_s0->unk_04 < 0.0) {
                var_s5++;
                temp_s0->unk_04 = 0.0f;
            }

            if (temp_s1->unk_04 < 0.0) {
                temp_s1->unk_04 = 0.0f;
            }
        }

        temp_s1->unk_18 += D_DBL_821979C8;
        temp_s1->unk_14 += D_DBL_821979D0;

        var_s2->v.ob[0] = temp_s0->unk_00;
        var_s2->v.ob[1] = temp_s0->unk_04;
        var_s2->v.ob[2] = temp_s0->unk_08;
        var_s2->v.tc[0] = temp_s0->unk_0C;
        var_s2->v.tc[1] = temp_s0->unk_0E;
        var_s2->v.cn[0] = temp_s0->unk_10.r;
        var_s2->v.cn[1] = temp_s0->unk_10.g;
        var_s2->v.cn[2] = temp_s0->unk_10.b;
        var_s2->v.cn[3] = temp_s0->unk_10.a;
        var_s2++;

        var_s2->v.ob[0] = temp_s1->unk_00;
        var_s2->v.ob[1] = temp_s1->unk_04;
        var_s2->v.ob[2] = temp_s1->unk_08;
        var_s2->v.tc[0] = temp_s1->unk_0C;
        var_s2->v.tc[1] = temp_s1->unk_0E;
        var_s2->v.cn[0] = temp_s1->unk_10.r;
        var_s2->v.cn[1] = temp_s1->unk_10.g;
        var_s2->v.cn[2] = temp_s1->unk_10.b;
        var_s2->v.cn[3] = temp_s1->unk_10.a;
        var_s2++;

        sp94 += D_DBL_821979D8;
        sp90 += D_DBL_821979E0;
        sp8C += D_DBL_821979E8;
        sp88 += D_DBL_821979F0;
    }

    if (temp_s6 == 1) {
        f32 tmp1;
        f32 tmp2;

        temp_fa0 = ((guRandom() % 360) * TWO_PI_F) / 360.0f;
        tmp1 = __cosf(temp_fa0) * sp9C;
        tmp2 = __sinf(temp_fa0) * sp9C;

        AuxiliaryEffect_Spawn(arg0->unk_01E, sp80 + tmp1, sp7C + sp84, sp78 + tmp2, 0xA, 0.75f);
        AuxiliaryEffect_Update(arg0->unk_01E);
    }

    if (var_s5 >= 0x1F) {
        return -1;
    }
    return 0;
}

/**
 * Part of the stat-change ribbon (see StatRibbon_Spawn).
 * Not reached in play (2026-11-13): did not run in a tour of the main menu, Pokédex, party, Lab,
 * registration, Free Battle setup and a COM battle (opening, a switch, running, a Pound turn).
 * @unverified Named after the ribbon seen in play; this function itself was not traced.
 */
s32 StatRibbon_UpdatePool(void) {
    s32 i;
    s32 var_s2;
    RibbonMesh* ptr = &D_8219CB20[0];

    D_8219F700 = (D_8219F700 + 1) & 0x3FFF;
    D_8219F702 = (D_8219F702 - 1) & 0x3FFF;
    var_s2 = -1;

    for (i = 0; i < 4; i++, ptr++) {
        if (ptr->unk_000 == 1) {
            if (StatRibbon_Update(ptr) == 0) {
                var_s2 = 0;
            } else {
                ptr->unk_000 = 0;
            }
        }
    }

    return var_s2;
}

/**
 * Part of the stat-change ribbon (see StatRibbon_Spawn).
 * Not reached in play (2026-11-13): did not run in a tour of the main menu, Pokédex, party, Lab,
 * registration, Free Battle setup and a COM battle (opening, a switch, running, a Pound turn).
 * @unverified Named after the ribbon seen in play; this function itself was not traced.
 */
Gfx* StatRibbon_Draw(Gfx* arg0, RibbonMesh* arg1) {
    s32 i;
    Vtx* temp_v0 = Gfx_AllocDisplayList(sizeof(Vtx) * 62);
    Vtx* vtx = temp_v0;
    Vtx* var_a0 = &arg1->unk_050[0];

    for (i = 0; i < 31; i++) {
        *vtx++ = *var_a0++;
        *vtx++ = *var_a0++;
    }

    vtx = temp_v0;
    for (i = 0; i < 30; i++) {
        gSPVertex(arg0++, vtx, 4, 0);
        gSP2Triangles(arg0++, 0, 2, 1, 0, 2, 3, 1, 0);
        vtx += 2;
    }

    return arg0;
}


/**
 * Part of the stat-change ribbon (see StatRibbon_Spawn).
 * Not reached in play (2026-11-13): did not run in a tour of the main menu, Pokédex, party, Lab,
 * registration, Free Battle setup and a COM battle (opening, a switch, running, a Pound turn).
 * @unverified Named after the ribbon seen in play; this function itself was not traced.
 */
Gfx* StatRibbon_DrawPool(Gfx* arg0) {
    static Gfx D_84388E88[] = {
        gsDPPipeSync(),
        gsDPSetCycleType(G_CYC_2CYCLE),
        gsSPClearGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN |
                              G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH | G_CLIPPING | 0x0040F9FA),
        gsSPSetGeometryMode(G_ZBUFFER | G_SHADE | G_SHADING_SMOOTH),
        gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
        gsDPPipeSync(),
        gsDPSetRenderMode(G_RM_PASS, G_RM_AA_ZB_XLU_SURF2),
        gsDPSetTexturePersp(G_TP_PERSP),
        gsDPSetTextureDetail(G_TD_CLAMP),
        gsDPSetTextureLOD(G_TL_TILE),
        gsDPSetTextureLUT(G_TT_NONE),
        gsDPSetTextureConvert(G_TC_FILT),
        gsDPSetTextureFilter(G_TF_BILERP),
        gsDPSetCombineLERP(TEXEL1, TEXEL0, PRIM_LOD_FRAC, TEXEL0, TEXEL1, TEXEL0, PRIMITIVE, TEXEL0, PRIMITIVE,
                           ENVIRONMENT, COMBINED, ENVIRONMENT, COMBINED, 0, ENVIRONMENT, 0),
        gsSPEndDisplayList(),
    };

    static Gfx D_84388F00[] = {
        gsDPPipeSync(),
        gsDPSetCycleType(G_CYC_1CYCLE),
        gsSPClearGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN |
                              G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH | G_CLIPPING | 0x0040F9FA),
        gsSPSetGeometryMode(G_ZBUFFER | G_SHADE | G_SHADING_SMOOTH),
        gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
        gsDPPipeSync(),
        gsDPSetRenderMode(AA_EN | Z_CMP | IM_RD | CLR_ON_CVG | CVG_DST_SAVE | ZMODE_XLU | FORCE_BL |
                              GBL_c1(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA),
                          AA_EN | Z_CMP | IM_RD | CLR_ON_CVG | CVG_DST_SAVE | ZMODE_XLU | FORCE_BL |
                              GBL_c2(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA)),
        gsDPSetTexturePersp(G_TP_PERSP),
        gsDPSetTextureDetail(G_TD_CLAMP),
        gsDPSetTextureLOD(G_TL_TILE),
        gsDPSetTextureLUT(G_TT_NONE),
        gsDPSetTextureConvert(G_TC_FILT),
        gsDPSetTextureFilter(G_TF_BILERP),
        gsDPSetCombineMode(G_CC_MODULATEI, G_CC_MODULATEI),
        gsSPEndDisplayList(),
    };

    RibbonMesh* ptr = &D_8219CB20[0];
    s32 i;

    gSPDisplayList(arg0++, D_84388E88);
    gDPPipeSync(arg0++);
    gDPLoadTextureTile_4b(arg0++, sBattleAnimAssetPointers[0x43], G_IM_FMT_I, 32, 0, 0, 0, 31, 31, 0, G_TX_NOMIRROR | G_TX_WRAP,
                          G_TX_NOMIRROR | G_TX_WRAP, 5, 5, G_TX_NOLOD, G_TX_NOLOD);
    gDPSetTileSize(arg0++, G_TX_RENDERTILE, D_8219F700, 0, (D_8219F700 + 0x1F), 0x001F);
    gDPLoadMultiTile_4b(arg0++, sBattleAnimAssetPointers[0x44], 0x0100, 1, G_IM_FMT_I, 32, 0, 0, 0, 31, 31, 0,
                        G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, 5, 5, G_TX_NOLOD, G_TX_NOLOD);
    gDPSetTileSize(arg0++, 1, D_8219F702, 0, (D_8219F702 + 0x1F), 0x001F);

    for (i = 0; i < 4; i++, ptr++) {
        if (ptr->unk_000 == 1) {
            gDPSetPrimColor(arg0++, 0, ptr->unk_024, ptr->unk_028, ptr->unk_02C, ptr->unk_030, ptr->unk_034);
            gDPSetEnvColor(arg0++, ptr->unk_038, ptr->unk_03C, ptr->unk_040, ptr->unk_044);

            gSPClearGeometryMode(arg0++, G_CULL_BACK);
            gSPSetGeometryMode(arg0++, G_CULL_FRONT);

            arg0 = StatRibbon_Draw(arg0, ptr);

            gSPClearGeometryMode(arg0++, G_CULL_FRONT);
            gSPSetGeometryMode(arg0++, G_CULL_BACK);

            arg0 = StatRibbon_Draw(arg0, ptr);
        }
    }

    ptr = &D_8219CB20[0];
    for (i = 0; i < 4; i++, ptr++) {
        if (ptr->unk_000 == 1) {
            arg0 = AuxiliaryEffect_Draw(ptr->unk_01E, arg0);
        }
    }

    return arg0;
}


/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Surf.
 */
void SurfTerrainGrid_BuildCameraBounds(unk_D_843975E8* arg0, f32 arg1) {
    CameraNode* spB4 = BattleAnim_GetCameraContext();
    f32 spB0;
    f32 spAC;
    f32 spA8;
    f32 spA4;
    f32 spA0;
    f32 sp9C;
    f32 var_fs0;
    f32 sp94;
    UNUSED s32 pad; // FAKE: stack padding
    f32 sp8C;
    f32 sp44;
    f32 sp84;
    f32 sp80;
    f32 sp7C;
    f32 sp78;
    f32 sp74;
    f32 sp70;
    f32 sp40;
    f32 sp68;
    f32 sp64;
    f32 sp60;
    f32 sp5C;
    f32 sp58;
    f32 sp54;
    f32 sp50;
    f32 sp4C;
    f32 sp48;

    spB0 = spB4->view.eyePosition.x;
    spAC = spB4->view.eyePosition.y;
    spA8 = spB4->view.eyePosition.z;

    sp9C = spB4->view.targetPosition.x;
    spA0 = spB4->view.targetPosition.y;
    spA4 = spB4->view.targetPosition.z;

    sp78 = spB4->view.upDirection.x;
    sp74 = spB4->view.upDirection.y;
    sp70 = spB4->view.upDirection.z;

    sp4C = spB4->perspective.verticalFieldOfView;
    sp48 = sp4C / 30.0f;
    sp8C = spB4->perspective.nearPlane;

    sp84 = sp9C - spB0;
    sp80 = spA0 - spAC;
    sp7C = spA4 - spA8;

    Vec3f_NormalizeComponents(&sp84, &sp80, &sp7C);

    sp44 = (sp4C * TWO_PI) / 720.0;
    sp40 = sp8C + arg1;

    arg0->unk_00 = (sp40 * sp84) + spB0;
    arg0->unk_04 = (sp40 * sp80) + spAC;
    arg0->unk_08 = (sp40 * sp7C) + spA8;

    sp50 = __cosf(sp44);
    if (sp50 != 0.0) {
        var_fs0 = (__sinf(sp44) * sp40) / sp50;
    } else {
        var_fs0 = 0.0f;
    }

    var_fs0 = Math_AbsF32(var_fs0);
    sp94 = spB4->perspective.unk_0C * var_fs0 * sp48 * 1.2f;

    Vec3f_CrossProductComponents(sp84, sp80, sp7C, sp78, sp74, sp70, &sp68, &sp64, &sp60);
    Vec3f_CrossProductComponents(sp84, sp80, sp7C, sp68, sp64, sp60, &sp5C, &sp58, &sp54);
    Vec3f_NormalizeComponents(&sp68, &sp64, &sp60);
    Vec3f_NormalizeComponents(&sp5C, &sp58, &sp54);

    arg0->unk_0C = sp68 * sp94;
    arg0->unk_10 = sp64 * sp94;
    arg0->unk_14 = sp60 * sp94;

    arg0->unk_18 = sp5C * var_fs0;
    arg0->unk_1C = sp58 * var_fs0;
    arg0->unk_20 = sp54 * var_fs0;
}


/**
 * Samples the Surf water surface (sWaterHeightMap) at world position (x, z).
 *
 * Returns the water height (world Y) at that point and writes the surface tilt
 * in degrees, in the range [-90, 90], to *rotation_x. The surface is a 16x16
 * grid of vertices, so the height is found by picking the grid cell under
 * (x, z), picking one of the cell's two triangles, and evaluating that
 * triangle's plane at (x, z).
 *
 * Called by BattleAnim_SurfContinue to keep the Surf rider on the wave:
 * the return value is added to the model's base height and the tilt becomes its
 * X rotation. Also called by SurfTerrainGrid_Draw to compare the camera-aligned
 * quad corners against the water surface.
 * //@src/fragments/battle_engine/battle_engine_2F3CB0.c
 * //@src/fragments/battle_engine/battle_engine_ribbon_mesh_and_surf_grid.c SurfTerrainGrid_UpdateWaves
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Surf.
 */
f32 SurfTerrainGrid_SampleHeightAndSlope(f32 x, f32 z, f32* rotation_x) {
    UNUSED s32 pad1[2]; // FAKE: stack padding
    f32 height;
    // Corner naming: c<i><j> is the grid vertex at (cell_x + i, cell_z + j).
    // Each corner is read as world X, height (Y), world Z.
    f32 c00_x;
    f32 c00_y;
    f32 c00_z;
    f32 c10_x;
    f32 c10_y;
    f32 c10_z;
    f32 c01_x;
    f32 c01_y;
    f32 c01_z;
    f32 c11_x;
    f32 c11_y;
    f32 c11_z;
    UNUSED s32 pad2[8]; // FAKE: stack padding
    f32 dx_to_c11;
    f32 dz_to_c11;
    f32 dx_to_c10;
    f32 angle_deg;
    f32 dz_to_c10;
    s32 cell_z;
    s32 cell_x;
    // Normal of the triangle's plane (not normalized; only ratios are used).
    f32 normal_x;
    f32 normal_y;
    f32 normal_z;

    // Convert world position to the index of the grid cell containing it.
    // Grid vertex i sits at X = 150 * (i - 8) - 440 and vertex j at Z = 200 * (j - 8),
    // matching the layout built by SurfTerrainGrid_Init. Inverting that gives the indices below
    // (truncated to an integer, so the cell is the one whose lower corner is at or before x/z).
    cell_x = ((x + 440.0f) / 150.0f) + 8.0f;
    cell_z = (z / 200.0f) + 8.0f;

    // Clamp to 0..14 so that cell + 1 stays inside the 16 vertices of an axis; positions
    // outside the grid are sampled using the edge cell's plane extended outward.
    if (cell_x < 0) {
        cell_x = 0;
    }

    if (cell_x >= 15) {
        cell_x = 14;
    }

    if (cell_z < 0) {
        cell_z = 0;
    }

    if (cell_z >= 15) {
        cell_z = 14;
    }

    // Fetch the four corners of the cell as (X, height, Z) triples.
    c00_x = sWaterHeightMap.grid[cell_x][cell_z].unk_00;
    c00_y = sWaterHeightMap.grid[cell_x][cell_z].unk_04;
    c00_z = sWaterHeightMap.grid[cell_x][cell_z].unk_08;
    c10_x = sWaterHeightMap.grid[cell_x + 1][cell_z].unk_00;
    c10_y = sWaterHeightMap.grid[cell_x + 1][cell_z].unk_04;
    c10_z = sWaterHeightMap.grid[cell_x + 1][cell_z].unk_08;
    c01_x = sWaterHeightMap.grid[cell_x][cell_z + 1].unk_00;
    c01_y = sWaterHeightMap.grid[cell_x][cell_z + 1].unk_04;
    c01_z = sWaterHeightMap.grid[cell_x][cell_z + 1].unk_08;
    c11_x = sWaterHeightMap.grid[cell_x + 1][cell_z + 1].unk_00;
    c11_y = sWaterHeightMap.grid[cell_x + 1][cell_z + 1].unk_04;
    c11_z = sWaterHeightMap.grid[cell_x + 1][cell_z + 1].unk_08;

    // Horizontal offsets from the query point to the two far-side corners c10 and c11.
    dx_to_c10 = c10_x - x;
    // FAKE: repeats the c00_y load above.
    c00_y = sWaterHeightMap.grid[cell_x][cell_z].unk_04;
    dz_to_c10 = c10_z - z;
    dx_to_c11 = c11_x - x;
    dz_to_c11 = c11_z - z;

    // Choose which half of the cell to use. The cell is split into triangles
    // (c00, c10, c01) and (c11, c10, c01), sharing the c10-c01 diagonal. c10 and c11 have the
    // same X, so this comparison reduces to whether z is closer to the c10 row or the c11 row.
    // It is a cheap approximation of "which side of the diagonal", not an exact point-in-triangle
    // test, so near the diagonal the plane of the neighboring triangle may be used.
    if ((SQ(dx_to_c10) + SQ(dz_to_c10)) <= (SQ(dx_to_c11) + SQ(dz_to_c11))) {
        // Plane through c00, c10, c01: normal = (c10 - c00) x (c01 - c00).
        Vec3f_CrossProductComponents(c10_x - c00_x, c10_y - c00_y, c10_z - c00_z, c01_x - c00_x, c01_y - c00_y, c01_z - c00_z,
                      &normal_x, &normal_y, &normal_z);
        if (normal_y != 0.0) {
            // Plane equation n . (P - c00) = 0 solved for Y at (x, z).
            height = c00_y - ((((x - c00_x) * normal_x) + (normal_z * (z - c00_z))) / normal_y);
        } else {
            // Vertical plane: Y cannot be solved, so average the triangle's corner heights.
            height = (c00_y + c10_y + c01_y) / 3.0;
        }
    } else {
        // Plane through c11, c10, c01: normal = (c10 - c11) x (c01 - c11).
        Vec3f_CrossProductComponents(c10_x - c11_x, c10_y - c11_y, c10_z - c11_z, c01_x - c11_x, c01_y - c11_y, c01_z - c11_z,
                      &normal_x, &normal_y, &normal_z);
        if (normal_y != 0.0) {
            height = c11_y - ((((x - c11_x) * normal_x) + (normal_z * (z - c11_z))) / normal_y);
        } else {
            height = (c11_y + c10_y + c01_y) / 3.0;
        }
    }

    // MathUtil_Atan2s(y, x) measures the angle from the +y argument toward +x, so this is the angle
    // of the normal away from straight up in the X-Y plane: 0 on flat water, nonzero where the
    // height changes along X (the direction the waves travel). The Z component of the normal
    // is ignored, so side-to-side slope does not tilt the rider. The result is an s16 where
    // 65536 = 360 degrees; convert to degrees.
    angle_deg = MathUtil_Atan2s(normal_y, normal_x);
    angle_deg = (angle_deg * 360.0) / 65536.0;

    // The two triangles' cross products point in opposite vertical directions (one winds
    // up, the other down), so the normal can be flipped by 180 degrees. Fold into [-90, 90]
    // so both triangles give the same tilt for the same slope.
    if (angle_deg > 90.0f) {
        angle_deg -= 180.0f;
    }

    if (angle_deg < -90.0f) {
        angle_deg += 180.0f;
    }

    *rotation_x = angle_deg;
    return height;
}


/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Surf.
 */
s32 SurfTerrainGrid_UpdateWaves(void) {
    s32 i;
    s32 j;
    unk_D_843951D0_1010* ptr;
    f32 var_fv0;
    s32 temp_v0;
    f32 tmp;

    sWaterHeightMap.unk_0000++;
    if (sWaterHeightMap.unk_000A < sWaterHeightMap.unk_0000) {
        return -1;
    }

    if (sWaterHeightMap.unk_0000 < 0x3C) {
        ptr = &sWaterHeightMap.grid[0][0];
        for (j = 0; j < 16; j++) {
            ptr->unk_04 += (30.0 * __sinf((((sWaterHeightMap.unk_0000 + j) % 15) * TWO_PI_F) / 15.0f)) + 10.0;
            ptr++;
        }
        sWaterHeightMap.unk_0004 += D_DBL_82197A28;
    } else {
        if (((sWaterHeightMap.unk_0000 - 0x3C) % 90) < 0x46) {
            ptr = &sWaterHeightMap.grid[0][2];
            for (j = 0; j < 13; j++) {
                if (0) {}  // karodo
                if (ptr->unk_04 > 0.0) {
                    ptr->unk_04 -= 40.0;
                    if (ptr->unk_04 < 0.0) {
                        ptr->unk_04 = 0.0f;
                    }
                }
                ptr++;
            }
        } else {
            ptr = &sWaterHeightMap.grid[0][2];
            for (j = 0; j < 13; j++) {
                ptr->unk_04 += 30.0;
                ptr++;
            }
        }

        sWaterHeightMap.unk_0004 += D_DBL_82197A30;
        if (sWaterHeightMap.unk_0004 > D_DBL_82197A38) {
            sWaterHeightMap.unk_0004 = D_FLT_82197A40;
        }
    }

    ptr = &sWaterHeightMap.grid[0][0];
    for (i = 0; i < 16; i++) {
        for (j = 0; j < 16; j++) {
            temp_v0 = 1;

            tmp = ptr->unk_04;
            var_fv0 = 0.0f;
            if (i > 0) {
                temp_v0 = 2;
                var_fv0 += sWaterHeightMap.grid[i - 1][j].unk_04 - tmp;
            }

            if ((!ptr) && (!ptr)) {}  // FAKE

            if (j > 0) {
                var_fv0 += sWaterHeightMap.grid[i][j - 1].unk_04 - tmp;
            }

            if (j < 0xF) {
                var_fv0 += sWaterHeightMap.grid[i][j + 1].unk_04 - tmp;
            }

            temp_v0++;
            temp_v0++;
            if (temp_v0) {}  // karodo

            ptr->unk_0C = (var_fv0 * sWaterHeightMap.unk_0004) + tmp;
            ptr++;
        }
    }

    ptr = &sWaterHeightMap.grid[0][0];
    for (i = 0; i < 16; i++) {
        for (j = 0; j < 16; j++, ptr++) {
            ptr->unk_04 = ptr->unk_0C;
            if (ptr->unk_04 < 0.0) {
                ptr->unk_04 = 0.0f;
            }
        }
    }

    return 0;
}


/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Surf.
 */
void SurfTerrainGrid_Init(s32 arg0, s16 arg1, s16 arg2) {
    s32 i;
    s32 j;
    unk_D_843951D0_1010* ptr;

    sWaterHeightMap.unk_000A = arg2;
    sWaterHeightMap.unk_0000 = 0;
    sWaterHeightMap.unk_0004 = 0.0f;
    sWaterHeightMap.unk_0008 = arg1;

    ptr = &sWaterHeightMap.grid[0][0];

    for (i = 0; i < 16; i++) {
        for (j = 0; j < 16; j++, ptr++) {
            ptr->unk_00 = arg0 * (((i * 150.0f) - 1200.0f) - 440.0f);
            ptr->unk_04 = 1.0f;
            ptr->unk_08 = (j * 200.0f) - 1600.0f;
            ptr->unk_0C = 1.0f;
            ptr->unk_10 = 0xFF;

            if (i == 0xF) {
                ptr->unk_10 = 0;
            }

            if (j == 0xF) {
                ptr->unk_10 = 0;
            }

            if (j == 0) {
                ptr->unk_10 = 0;
            }
        }
    }

    D_821A1B20 = 0;
    D_821A1B22 = 8;
    D_821A1B24 = 0;

    if (arg1 > 0) {
        for (i = 0; i < arg1; i++) {
            SurfTerrainGrid_UpdateWaves();
        }

        SurfTerrainGrid_BuildCameraBounds(&D_821A1B28, 50.0f);
    }
}

/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Surf.
 */
s32 SurfTerrainGrid_Update(void) {
    UNUSED s32 pad[2]; // FAKE: stack padding
    s32 sp1C = SurfTerrainGrid_UpdateWaves();

    D_821A1B20 = (D_821A1B20 - 1) & 0x3FFF;
    D_821A1B22 = (D_821A1B22 - 1) & 0x3FFF;
    D_821A1B24 = (D_821A1B24 - 1) & 0x3FFF;
    SurfTerrainGrid_BuildCameraBounds(&D_821A1B28, 50.0f);

    return sp1C;
}
