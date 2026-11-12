/* Stadium Zero fragment018_262620. */
/* C ported from the Stadium 1 decomp: src/fragments/pokedex/pokedex_2190D0.c. */

#include "fragments/pokedex/pokedex.h"
#include "geo_node.h"
#include "geo_render.h"
#include "display_object_textures.h"
#include "graphics_textures.h"
#include "gb_data.h"
#include "game_state.h"
#include "text_system.h"
#include "gb_save.h"
#include "gallery.h"
#include "audio_sfx_wrapper.h"
#include "jpeg_stream.h"
#include "gfx_buffer.h"
#include "matrix.h"
#include "geo_layout.h"
#include "memory.h"
#include "stage_loader.h"
#include "pokemon_stats.h"
typedef struct unk_D_88826A88 {
    /* 0x00 */ char unk_00[1]; // unk size
    /* 0x01 */ char unk01[0x2C];
    /* 0x2D */ char unk_2D[15];
    /* 0x3C */ char unk_3C[15];
    /* 0x4B */ char unk_4B[15];
    /* 0x5A */ s16 unk_5A;
} unk_D_88826A88;
typedef struct unk_D_88826CF0_004 {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
} unk_D_88826CF0_004;
typedef struct unk_D_88826CF0 {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ unk_D_88826CF0_004* unk_04[1];
    /* 0x08 */ char unk08[0x10];
    /* 0x18 */ s16 unk_18[1];
    /* 0x1A */ char unk1A[0xA];
} unk_D_88826CF0;
typedef struct unk_D_88825ECC {
    /* 0x00 */ char unk_00[14];
    /* 0x0E */ s16 unk_0E;
} unk_D_88825ECC;
typedef struct unk_D_88826444 {
    /* 0x00 */ s16 unk_00;
    /* 0x00 */ s16 unk_02;
} unk_D_88826444;
extern unk_func_80011B94 D_8A130250;
extern unk_func_80011B94 D_8A130270;
extern unk_func_80011B94 D_8A1302B0;
extern s32 pad_D_88826A40;
extern GraphNode* D_8A1302CC;
extern s16 D_8A1302D4;
extern s16 D_8A1302D6;
extern s16 D_8A1302D8;
extern s16 D_8A1302DA;
extern s16 D_8A1302DC;
extern s16 D_8A1302DE;
extern u16 D_8A130306;
extern s16 D_8A130308;
extern u8* D_8A130448;
extern f32 D_8A13044C;
extern s32 D_8A130450;
extern Mtx* D_8A130454;
extern unk_D_88826CF0 D_8A130458[36];
extern u8 D_8A12C8F0[];
extern u8 D_8A12C9E8[];
extern u8 D_8A12CCC0[];
extern u8 D_8A12CD48[];
extern u8 D_8A12CDD0[];
extern u8 D_8A12CE58[];
extern u8 D_8A12CEE0[];
extern u8 D_8A12CF68[];
extern u8 D_8A12D070[];
extern u8 D_8A12E788[];
extern u8 D_8A12E850[];
extern Gfx D_8A12E8F0[];
extern Gfx D_8A12E958[];
extern Gfx D_8A12E970[];
extern Gfx D_8A12E9C8[];
extern Gfx D_8A12EA30[];
extern Gfx D_8A12EA48[];
extern Vtx D_8A12EA60[][4];
extern Gfx D_8A12EB60[];
extern Gfx D_8A12EB90[];
extern Gfx D_8A12EBA0[];
extern Gfx D_8A12EC18[];
extern Gfx D_8A12EC40[];
extern Gfx D_8A12EC60[];
extern Gfx D_8A12ECD0[];
extern Gfx D_8A12ECF0[];
extern char D_8A12F2A4[0x24][20];
extern Vec3f D_8A12F838;
extern Vec3f D_8A12F844;
extern Vec3f D_8A12F850[];
extern unk_D_88826444 D_8A12FA00[];
extern s16 D_8A12FA90[];
extern s16 D_8A12FAD8[];

s32 Pokedex_FindNextMapArea(s32 arg0);
s32 Pokedex_FindPrevMapArea(s32 arg0);
void Pokedex_BuildMapMarkerDisplayList(void);
void Pokedex_BuildMapMarkersDisplayList(void);
void Pokedex_BuildOverviewMarkersDisplayList(void);
Gfx* Pokedex_DrawMapPinIcon(Gfx* arg0, s16 arg1, s16 arg2);
Gfx* func_8A1033CC(Gfx* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
void Pokedex_ResetCameraEase(void);
void Pokedex_UpdateCameraEaseSpeed(void);
void Pokedex_EaseVec3Toward(Vec3f* arg0, Vec3f* arg1);
void Pokedex_UpdateAreaMapFrame(void);
s32 Pokedex_GetCountTier(s32 arg0);
s32 Pokedex_CheckAreaMapExit(void);
void Pokedex_ExitAreaMapPool(void);

void Pokedex_BuildMapLabelsDisplayList(void);

s32 Pokedex_FindNextMapArea(s32 arg0) {
    s32 i;
    s32 idx;
    s32 a0 = arg0;

    for (i = 1; i < 36; i++) {
        idx = D_8A12FAD8[(arg0 + i) % 36] - 1;
        if (D_8A130458[idx].unk_00 == 1) {
            return D_8A12FA90[idx] - 1;
        }
    }
    return a0;
}

s32 Pokedex_FindPrevMapArea(s32 arg0) {
    s32 i;
    s32 idx;
    s32 a0 = arg0;

    for (i = 35; i > 0; i--) {
        idx = D_8A12FAD8[(arg0 + i) % 36] - 1;
        if (D_8A130458[idx].unk_00 == 1) {
            return D_8A12FA90[idx] - 1;
        }
    }
    return a0;
}

void Pokedex_BuildMapMarkerDisplayList(void) {
    Gfx* temp_v0 = Gfx_AllocDisplayList(sizeof(Gfx) * 5);

    D_8A130250.gfx = temp_v0;

    if (D_8A1302D4 == 1) {
        gSPDisplayList(temp_v0++, D_8A12ECF0);
    }
    gSPEndDisplayList(temp_v0++);
}

void Pokedex_BuildMapMarkersDisplayList(void) {
    s32 i;
    Mtx sp1A8;
    Mtx sp168;
    Vec3f* vec;
    MtxF sp124;
    Mtx spE0;
    Mtx* var_s1;
    s32 var_t5;
    CameraNode* temp_s2;
    CameraView* ptr;
    Gfx* temp_v0;
    s32 j;

    temp_s2 = D_8A1302CC->children;
    ptr = &temp_s2->view;

    temp_v0 = Gfx_AllocDisplayList(sizeof(Gfx) * 36 * 25);
    D_8A130270.gfx = temp_v0;
    D_8A130454 = Gfx_AllocDisplayList(sizeof(Mtx) * 36);
    var_s1 = D_8A130454;

    MtxF_SetLookAt(&ptr->floatMatrix, &ptr->eyePosition, &ptr->targetPosition, 0);
    MtxF_ExtractScale(&sp124, &temp_s2->view.floatMatrix);
    guMtxF2L(sp124.mf, &spE0);

    gSPDisplayList(temp_v0++, D_8A12E8F0);

    for (i = 0; i < 36; i++) {
        vec = &D_8A12F850[i];

        if (D_8A130458[i].unk_00 == 1) {
            if ((i + 1) == D_8A12FAD8[D_8A1302D6]) {
                gDPSetPrimColor(temp_v0++, 0xFF, 0xFF, 255, 150, 100, 255); // #FF9664FF
                guScale(&sp168, 8.0f, 8.0f, 8.0f);
            } else {
                gDPSetPrimColor(temp_v0++, 0xFF, 0xFF, 255, 255, 255, 255); // #FFFFFFFF
                guScale(&sp168, 4.0f, 4.0f, 4.0f);
            }
            guTranslate(&sp1A8, vec->x, vec->y, vec->z);
            guMtxCatL(&sp168, &sp1A8, &sp1A8);
            guMtxCatL(&spE0, &sp1A8, var_s1);

            gSPMatrix(temp_v0++, var_s1, G_MTX_PUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(temp_v0++, D_8A12E958);
            gSPPopMatrix(temp_v0++, G_MTX_MODELVIEW);
        }
        var_s1++;
    }

    gSPDisplayList(temp_v0++, D_8A12E970);
    var_s1 = D_8A130454;
    gSPDisplayList(temp_v0++, D_8A12E9C8);

    for (i = 0; i < 36; i++) {
        if (D_8A130458[i].unk_00 == 1) {
            gSPMatrix(temp_v0++, var_s1, G_MTX_PUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(temp_v0++, D_8A12EA30);
            gSPPopMatrix(temp_v0++, G_MTX_MODELVIEW);
        }
        var_s1++;
    }

    gSPDisplayList(temp_v0++, D_8A12EA48);
    gSPDisplayList(temp_v0++, D_8A12EB60);

    for (j = 0, var_t5 = 0x2580; j < 4; j++, var_t5 -= 0xC80) {
        gDPLoadTextureTile(temp_v0++, var_t5 + D_8A130448, G_IM_FMT_RGBA, G_IM_SIZ_16b, 80, 0, 0, 0, 80, 20, 0,
                           G_TX_MIRROR | G_TX_CLAMP, G_TX_MIRROR | G_TX_CLAMP, 7, 5, G_TX_NOLOD, G_TX_NOLOD);
        gDPPipeSync(temp_v0++);

        var_s1 = D_8A130454;

        for (i = 0; i < 36; i++) {
            if (D_8A130458[i].unk_00 == 1) {
                gSPMatrix(temp_v0++, var_s1, G_MTX_PUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                gSPVertex(temp_v0++, &D_8A12EA60[j][0], 4, 0);
                gSPDisplayList(temp_v0++, D_8A12EB90);
                gSPPopMatrix(temp_v0++, G_MTX_MODELVIEW);
            }
            var_s1++;
        }
    }

    gSPDisplayList(temp_v0++, D_8A12EBA0);
    gSPEndDisplayList(temp_v0++);
}

void Pokedex_BuildOverviewMarkersDisplayList(void) {
    s32 i;
    s32 temp_a0;
    s32 temp_v2;
    s32 temp_t1;
    s32 temp_t2;
    Gfx* temp_v0;

    temp_v0 = Gfx_AllocDisplayList(sizeof(Gfx) * 170);
    D_8A1302B0.gfx = temp_v0;

    if (D_8A1302D4 == 1) {
        gSPDisplayList(temp_v0++, D_8A12EC60);

        if ((D_8A130306 % 16) >= 8) {
            for (i = 0; i < 36; i++) {
                if (D_8A130458[i].unk_00 == 1) {
                    temp_a0 = D_8A12FA00[i].unk_00 * 8;
                    temp_a0 = temp_a0 + 0x52;
                    temp_v2 = D_8A12FA00[i].unk_02 * 8;
                    temp_v2 = temp_v2 + 0x32;

                    gDPPipeSync(temp_v0++);
                    gSPTextureRectangle(temp_v0++, temp_a0 << 2, temp_v2 << 2, (temp_a0 + 8) << 2, (temp_v2 + 8) << 2,
                                        G_TX_RENDERTILE, 0, 0, 0x0400, 0x0400);
                }
            }
        }

        temp_t1 = (D_8A12FA00[D_8A12FAD8[D_8A1302D6] - 1].unk_00 * 8) + 0x4F;
        temp_t2 = (D_8A12FA00[D_8A12FAD8[D_8A1302D6] - 1].unk_02 * 8) + 0x2F;

        gDPSetPrimColor(temp_v0++, 0xFF, 0xFF, 150, 30, 0, 255); // #961E00FF

        gDPPipeSync(temp_v0++);

        gDPLoadTextureBlock(temp_v0++, D_8A12D070, G_IM_FMT_IA, G_IM_SIZ_8b, 16, 16, 0, G_TX_MIRROR | G_TX_CLAMP,
                            G_TX_MIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

        gDPPipeSync(temp_v0++);

        gSPTextureRectangle(temp_v0++, temp_t1 << 2, temp_t2 << 2, (temp_t1 + 0xE) << 2, (temp_t2 + 0xE) << 2,
                            G_TX_RENDERTILE, 0, 0, 0x0400, 0x0400);

        gDPPipeSync(temp_v0++);
        gSPDisplayList(temp_v0++, D_8A12ECD0);
    }

    gSPEndDisplayList(temp_v0++);
}

Gfx* Pokedex_DrawMapPinIcon(Gfx* arg0, s16 arg1, s16 arg2) {
    gSPDisplayList(arg0++, D_8A12EC18);
    gDPSetPrimColor(arg0++, 0xFF, 0xFF, 255, 255, 255, 255); // #FFFFFFFF
    gDPPipeSync(arg0++);
    gDPLoadTextureBlock(arg0++, D_8A12E788, G_IM_FMT_IA, G_IM_SIZ_8b, 16, 12, 0, G_TX_MIRROR | G_TX_CLAMP,
                        G_TX_MIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    gDPPipeSync(arg0++);
    gSPTextureRectangle(arg0++, arg1 << 2, arg2 << 2, (arg1 + 0xF) << 2, (arg2 + 0xB) << 2, G_TX_RENDERTILE, 0, 0,
                        0x0400, 0x0400);
    gSPDisplayList(arg0++, D_8A12EC40);
    return arg0;
}

Gfx* func_8A1033CC(Gfx* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    u32 temp_v0 = strlen(D_8A12F2A4[D_8A1302D6]) * 8;
    s32 tmp;
    s32 y;
    gDPLoadTextureBlock(arg0++, D_8A12CCC0, G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 8, 0, G_TX_MIRROR | G_TX_CLAMP,
                        G_TX_MIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    y = arg2;
    tmp = arg1 + arg3;
    gSPTextureRectangle(arg0++, (tmp - 8) << 2, y << 2, tmp << 2, (y + 8) << 2, G_TX_RENDERTILE, 0, 0, 0x0400, 0x0400);
    switch (arg5) {
        case 0:
            gSPTextureRectangle(arg0++, ((tmp - arg3) + 0x3E) << 2, y << 2, (tmp - 8) << 2, (y + 8) << 2, G_TX_RENDERTILE, 0,
                                0, -0x0400, 0x0400);
            break;

        case 1:
            gSPTextureRectangle(arg0++, ((tmp - arg3) + 0x46) << 2, y << 2, (tmp - 8) << 2, (y + 8) << 2,
                                G_TX_RENDERTILE, 0, 0, -0x0400, 0x0400);
            break;

        case 2:
            gSPTextureRectangle(arg0++, ((tmp - arg3) + 8) << 2, y << 2, (tmp - 8) << 2, (y + 8) << 2, G_TX_RENDERTILE,
                                0, 0, -0x0400, 0x0400);
            break;

        default:
            break;
    }

    gDPLoadTextureBlock(arg0++, D_8A12CD48, G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 8, 0, G_TX_MIRROR | G_TX_CLAMP,
                        G_TX_MIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    y = arg2 + arg4;
    gSPTextureRectangle(arg0++, (tmp - 8) << 2, (y - 8) << 2, tmp << 2, y << 2, G_TX_RENDERTILE, 0, 0, 0x0400,
                        0x0400);
    gSPTextureRectangle(arg0++, ((tmp - arg3) + 8) << 2, (y - 8) << 2, (tmp - 8) << 2, y << 2, G_TX_RENDERTILE, 0,
                        0, -0x0400, 0x0400);
    gSPTextureRectangle(arg0++, (tmp - 8) << 2, ((y - arg4) + 8) << 2, tmp << 2, (y - 8) << 2, G_TX_RENDERTILE, 0,
                        0, 0x0400, -0x0400);
    gDPLoadTextureBlock(arg0++, D_8A12CDD0, G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 8, 0, G_TX_MIRROR | G_TX_CLAMP,
                        G_TX_MIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    // idk
    tmp = arg1;
    gSPTextureRectangle(arg0++, tmp << 2, (y - 8) << 2, (tmp + 8) << 2, y << 2, G_TX_RENDERTILE, 0, 0, 0x0400,
                        0x0400);
    switch (arg5) {
        case 2:
            gSPTextureRectangle(arg0++, arg1 << 2, ((y - arg4) + 8) << 2, (arg1 + 8) << 2, (y - 8) << 2,
                                G_TX_RENDERTILE, 0, 0, 0x0400, -0x0400);
            break;

        case 0:
        case 1:
            gSPTextureRectangle(arg0++, arg1 << 2, (y - arg4) << 2, (arg1 + 8) << 2, (y - 8) << 2,
                                G_TX_RENDERTILE, 0, 0, 0x0400, -0x0400);

            break;

        default:
            break;
    }
    switch (arg5) {
        case 2:
            gDPLoadTextureBlock(arg0++, D_8A12CE58, G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 8, 0,
                                G_TX_MIRROR | G_TX_CLAMP, G_TX_MIRROR | G_TX_CLAMP,
                                G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            // dumb
            y = arg2;
            gSPTextureRectangle(arg0++, arg1 << 2, y << 2, (arg1 + 8) << 2, (y + 8) << 2,
                                G_TX_RENDERTILE, 0, 0, 0x0400, 0x0400);
            break;
        default:
            break;
    }
    if (arg6 == 1) {
        switch (D_8A1302DE) {
            case 0:
                gDPSetPrimColor(arg0++, 0xFF, 0xFF, 106, 40, 20, 200); // #6A2814C8
                break;

            case 1:
                gDPSetPrimColor(arg0++, 0xFF, 0xFF, 0, 44, 0, 200); // #002C00C8
                break;

            case 2:
                gDPSetPrimColor(arg0++, 0xFF, 0xFF, 0, 0, 139, 200); // #00008BC8
                break;

            case 3:
                gDPSetPrimColor(arg0++, 0xFF, 0xFF, 160, 160, 0, 200); // #A0A000C8
                break;

            default:
                break;
        }

        gDPLoadTextureBlock(arg0++, D_8A12E850, G_IM_FMT_IA, G_IM_SIZ_16b, 4, 4, 0, G_TX_MIRROR | G_TX_CLAMP,
                            G_TX_MIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        gSPTextureRectangle(arg0++, (tmp + 2) << 2, (arg2 + 2) << 2, ((tmp + arg3) - 2) << 2,
                            ((arg2 + arg4) - 2) << 2, G_TX_RENDERTILE, 0, 0, 0x0400, 0x0400);
        gDPSetPrimColor(arg0++, 0xFF, 0xFF, 255, 255, 255, 200); // #FFFFFFC8
    }
    y = arg2;
    switch (arg5) {
        case 2:
        default:
            break;

        case 1:
            gDPLoadTextureBlock(arg0++, D_8A12C8F0, G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 15, 0, G_TX_MIRROR | G_TX_CLAMP,
                                G_TX_MIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            // almost worse than the old fake
            tmp = arg1;
            arg3 = (tmp + temp_v0) - 0x10;
            arg4 = arg2 - 0xC;
            gSPTextureRectangle(arg0++, tmp << 2, arg4 << 2, arg3 << 2, (arg4 + 15) << 2,
                                G_TX_RENDERTILE, 0, 0, 0x0400, 0x0400);
            gDPLoadTextureBlock(arg0++, D_8A12C9E8, G_IM_FMT_RGBA, G_IM_SIZ_16b, 24, 15, 0, G_TX_MIRROR | G_TX_CLAMP,
                                G_TX_MIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            gSPTextureRectangle(arg0++, arg3 << 2, (y - 0xC) << 2,
                                (arg3 + 0x18) << 2, (arg2 + 3) << 2, G_TX_RENDERTILE, 0, 0,
                                0x0400, 0x0400);
            break;

        case 0:
            gDPLoadTextureBlock(arg0++, D_8A12CEE0, G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 8, 0, G_TX_MIRROR | G_TX_CLAMP,
                                G_TX_MIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            arg4 = arg2 - 5;
            gSPTextureRectangle(arg0++, tmp << 2, arg4 << 2, (arg1 + 0x2E) << 2, (arg4 + 8) << 2, G_TX_RENDERTILE, 0,
                                0, 0x0400, 0x0400);
            gDPLoadTextureBlock(arg0++, D_8A12CF68, G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 8, 0, G_TX_MIRROR | G_TX_CLAMP,
                                G_TX_MIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            gSPTextureRectangle(arg0++, (arg1 + 0x2E) << 2, (arg2 - 5) << 2, (arg1 + 0x3E) << 2, (arg2 + 3) << 2,
                                G_TX_RENDERTILE, 0, 0, 0x0400, 0x0400);
            break;
    }

    return arg0;
}

extern unk_func_80011B94 D_8A130290;
extern s16 D_8A130430;
extern Gfx D_8A12EBB8[];
extern Gfx D_8A12EBF0[];
extern Gfx D_8A12F128[];
extern Gfx D_8A12F150[];
/**
 * @unverified Name was previously used only by callers of this address; the definition was still func_.
 */
void Pokedex_BuildMapLabelsDisplayList(void) {
    s16 sp46;
    s16 sp44;
    s16 sp42;
    s16 sp40;
    s16 sp3E;
    s16 sp3C;
    UNUSED s32 pad; // FAKE: stack padding
    s32 temp_v0_2;
    Gfx* temp_v0;
    s32 sp2C;

    temp_v0 = Gfx_AllocDisplayList(sizeof(Gfx) * 450);
    D_8A130290.gfx = temp_v0;

    gSPDisplayList(temp_v0++, D_8A12EBB8);

    temp_v0 = func_8A1033CC(temp_v0, 0x1E, 0x14, 0x64, 0x10, 0, 1);

    if (D_8A1302DC == 1) {
        if (D_8A130430 > 0) {
            sp46 = 0xA0 - (D_8A130430 / 2);
            sp44 = D_8A130430;
            temp_v0 = func_8A1033CC(temp_v0, sp46, 0x78, D_8A130430, 0x14, 0, 1);
        }
    } else {
        if (D_8A1302D4 == 0) {
            sp2C = D_8A12FAD8[D_8A1302D6] - 1;
            temp_v0 = func_8A1033CC(temp_v0, 0xB9, 0xD2, 0x73, 0x10, 0, 1);
            if ((D_8A1302DA == 1) && (sp2C >= 0) && (D_8A130308 == 0) && (D_8A130430 > 0) && (D_8A130450 != 0)) {
                temp_v0_2 = (D_8A130458[sp2C].unk_02 * 0xA) - 0xA;
                sp42 = 0x8C - (D_8A130430 / 2);
                sp40 = 0xB4 - temp_v0_2;
                sp3E = D_8A130430 + 0x28;
                sp3C = temp_v0_2 + 0x14;
                temp_v0 = func_8A1033CC(temp_v0, sp42, sp40, sp3E, sp3C, 2, 1);
            }
        } else {
            temp_v0 = func_8A1033CC(func_8A1033CC(temp_v0, 0x4F, 0x2F, 0x97, 0x86, 0, 0), 0x4F, 0xB5, 0x97, 0x10, 2, 1);
        }
        temp_v0 = func_8A1033CC(temp_v0, 0x1E, 0xD2, 0x78, 0x10, 0, 1);
    }

    gSPDisplayList(temp_v0++, D_8A12EBF0);

    if ((D_8A1302DC == 0) && (D_8A1302D4 == 0)) {
        temp_v0 = Pokedex_DrawMapPinIcon(temp_v0, 0xBC, 0xD5);
    }
    if (D_8A1302D4 == 1) {
        temp_v0 = Pokedex_DrawMapPinIcon(temp_v0, 0x56, 0xB7);
    }

    gSPDisplayList(temp_v0++, D_8A12F128);

    if ((D_8A1302DC == 1) && (D_8A130430 > 0)) {
        gDPFillRectangle(temp_v0++, sp46 - 1, 119, sp46 + sp44 + 1, 141);
    }

    gDPFillRectangle(temp_v0++, 29, 19, 131, 37);
    gDPFillRectangle(temp_v0++, 184, 209, 301, 227);
    gDPFillRectangle(temp_v0++, 29, 209, 151, 227);

    if (D_8A1302D4 == 1) {
        gDPFillRectangle(temp_v0++, 79, 47, 232, 199);
    }

    if ((D_8A1302DA == 1) && (D_8A130308 == 0) && (D_8A130430 > 0)) {
        gDPFillRectangle(temp_v0++, sp42 - 1, sp40 - 1, sp42 + sp3E + 1, sp40 + sp3C + 1);
    }

    gSPDisplayList(temp_v0++, D_8A12F150);
    gSPEndDisplayList(temp_v0++);
}

void Pokedex_ResetCameraEase(void) {
    D_8A13044C = 8.0f;
    D_8A130450 = 0;
}

void Pokedex_UpdateCameraEaseSpeed(void) {
    D_8A13044C -= 0.5f;
    if (D_8A13044C < 1.0f) {
        D_8A13044C = 1.0f;
        D_8A130450++;
    }
}

void Pokedex_EaseVec3Toward(Vec3f* arg0, Vec3f* arg1) {
    f32 sp2C;
    f32 sp28;
    f32 sp24;
    f32 sp20;
    f32 sp1C;
    f32 temp_fv0;

    sp2C = arg1->x - arg0->x;
    sp28 = arg1->y - arg0->y;
    sp24 = arg1->z - arg0->z;

    sp20 = Math_AbsF32(sp2C);
    sp1C = Math_AbsF32(sp28);
    temp_fv0 = Math_AbsF32(sp24);
    if (sp20 < 1.0f) {
        arg0->x = arg1->x;
    } else {
        arg0->x += sp2C / D_8A13044C;
    }

    if (sp1C < 1.0f) {
        arg0->y = arg1->y;
    } else {
        arg0->y += sp28 / D_8A13044C;
    }

    if (temp_fv0 < 1.0f) {
        arg0->z = arg1->z;
    } else {
        arg0->z += sp24 / D_8A13044C;
    }

    if ((sp20 < 200.0f) && (sp1C < 200.0f) && (temp_fv0 < 200.0f)) {
        D_8A130308 = 0;
    } else {
        D_8A130308 = 1;
    }
}

void Pokedex_UpdateAreaMapFrame(void) {
    UNUSED s32 pad; // FAKE: stack padding
    CameraNode* node = D_8A1302CC->children;
    Vec3f* vec;
    Vec3f sp28;

    switch (D_8A1302DA) {
        case 0:
            Pokedex_EaseVec3Toward(&node->view.targetPosition, &D_8A12F838);
            Pokedex_EaseVec3Toward(&node->view.eyePosition, &D_8A12F844);
            break;

        case 1:
            vec = &D_8A12F850[D_8A12FAD8[D_8A1302D6] - 1];

            sp28.x = vec->x;
            sp28.y = vec->y + 1000.0f;
            sp28.z = vec->z + 700.0f;

            Pokedex_EaseVec3Toward(&node->view.targetPosition, vec);
            Pokedex_EaseVec3Toward(&node->view.eyePosition, &sp28);
            break;
    }

    Pokedex_UpdateCameraEaseSpeed();
    node->perspective.nearPlane = 100.0f;
    node->perspective.farPlane = 12800.0f;
    D_8A130306++;

    Pokedex_BuildMapMarkerDisplayList();
    Pokedex_BuildMapMarkersDisplayList();
    Pokedex_BuildOverviewMarkersDisplayList();
    Pokedex_BuildMapLabelsDisplayList();
}

s32 Pokedex_GetCountTier(s32 arg0) {
    s32 ret;

    if (arg0 < 2) {
        ret = 0;
    } else if (arg0 < 6) {
        ret = 1;
    } else if (arg0 < 0xB) {
        ret = 2;
    } else if (arg0 < 0x15) {
        ret = 3;
    } else if (arg0 < 0x29) {
        ret = 4;
    } else if (arg0 < 0x51) {
        ret = 5;
    } else if (arg0 < 0x64) {
        ret = 6;
    } else {
        ret = 7;
    }

    return ret;
}

typedef struct Label8A104B00 {
    /* 0x00 */ char text[0x2E];
    /* 0x2E */ s16 width;
} Label8A104B00; // size = 0x30
typedef struct Area8A104B00 {
    /* 0x00 */ char name[0xA];
    /* 0x0A */ s16 group;
} Area8A104B00; // size = 0xC
extern Label8A104B00 D_8A130310[];
extern s16 D_8A130438[];
extern Area8A104B00 D_8A12F574[];
extern char D_8A12F214[][0x12];
extern char D_8A12F190[];
extern char D_8A12F19C[];
extern char D_8A12F1B0[];
extern char D_8A12F1C8[];
extern char D_8A12F1FC[];
extern char D_8A12F204[];
extern char D_8A12F208[];
extern char D_8A12FD60[];
extern char D_8A12FD68[];
extern char D_8A12FD6C[];
extern char D_8A12FD70[];
extern char D_8A12FD74[];
extern char D_8A12FD8C[];
extern char D_8A12FDA0[];
extern char D_8A12FDBC[];
extern char D_8A12FDD4[];
extern char D_8A12FDE4[];
extern char D_8A12FDF0[];
extern char D_8A12FE04[];
extern char D_8A12FE14[];
extern char D_8A12FE18[];
extern char D_8A12FE1C[];
extern s16 D_8A130432;
extern char D_8A1302E8[];
extern s16 D_8A130446;
void func_800069CC(void);
s32 func_8A104B00(s32 arg0)
{
  char *name = D_8A12F2A4[D_8A1302D6];
  unk_D_88826CF0_004 *temp_s2;
  s32 temp_s0;
  char *str;
  s32 i;
  s32 tier;
  s32 var_a1;
  s32 j;
  s32 temp_s1;
  s32 temp_s4;
  s32 x;
  s32 idx;
  s32 sel;
  s32 pad[1]; // FAKE: unused stack word
  Pokedex_UpdateAreaMapFrame();
  GeoRender_AdvanceFrameCounter();
  func_800069CC();
  Geo_RenderRootNode(D_8A1302CC);
  Font_BeginTranslucentTextRendering();
  Font_SetActive(1, 0);
  Gfx_SetEnvColor(0xFF, 0xFF, 0xFF, 0xFF);
  Font_Printf(0x23, 0x17, D_8A12FD60, D_8A1302E8, D_8A12F190);
  D_8A130430 = 0;
  if (D_8A1302DC == 1)
  {
    sprintf(D_8A130310[0].text, D_8A12FD68, D_8A12F1C8);
    D_8A130430 = ((strlen(D_8A130310[0].text) * 5) + 0x1E) & 0xFFF8;
    Font_Printf(0xAF - (D_8A130430 / 2), 0x7D, D_8A12FD6C, D_8A130310[0].text);
  }
  else
  {
    if (D_8A1302D4 == 0)
    {
      temp_s0 = D_8A12FAD8[D_8A1302D6];
      temp_s0--;
      Font_Printf(0xCB, 0xD5, D_8A12FD70, D_8A12F19C);
      if (D_8A1302DA == 1)
      {
        unk_D_88826CF0 *ptr = &D_8A130458[temp_s0];
        if ((ptr->unk_00 == 1) && (D_8A130308 == 0))
        {
          s16 tmp = ptr->unk_02;
          if (tmp > 0)
          {
            for (i = 0; i < tmp; i++)
            {
              temp_s2 = ptr->unk_04[i];
              temp_s1 = temp_s2->unk_02;
              temp_s4 = temp_s2->unk_04;
              tier = Pokedex_GetCountTier(temp_s2->unk_06);
              str = D_8A12F574[ptr->unk_18[i]].name;
              if (D_8A130446 == 1)
              {
                if (temp_s1 == temp_s4)
                {
                  if (tmp >= 2)
                  {
                    sprintf(D_8A130310[i].text, D_8A12FD74, str, D_8A12F1FC, temp_s1, D_8A12F208, temp_s2->unk_06);
                  }
                  else
                  {
                    sprintf(D_8A130310[i].text, D_8A12FD8C, str, D_8A12F1FC, temp_s1, D_8A12F208, temp_s2->unk_06);
                  }
                }
                else
                  if (tmp >= 2)
                {
                  sprintf(D_8A130310[i].text, D_8A12FDA0, str, D_8A12F1FC, temp_s1, D_8A12F204, temp_s4, D_8A12F208, temp_s2->unk_06);
                }
                else
                {
                  sprintf(D_8A130310[i].text, D_8A12FDBC, str, D_8A12F1FC, temp_s1, D_8A12F204, temp_s4, D_8A12F208, temp_s2->unk_06);
                }
              }
              else
                if (temp_s1 == temp_s4)
              {
                if (tmp >= 2)
                {
                  sprintf(D_8A130310[i].text, D_8A12FDD4, str, D_8A12F1FC, temp_s1, D_8A12F214[tier]);
                }
                else
                {
                  sprintf(D_8A130310[i].text, D_8A12FDE4, str, D_8A12F1FC, temp_s1, D_8A12F214[tier]);
                }
              }
              else
                if (tmp >= 2)
              {
                sprintf(D_8A130310[i].text, D_8A12FDF0, str, D_8A12F1FC, temp_s1, D_8A12F204, temp_s4, D_8A12F214[tier]);
              }
              else
              {
                sprintf(D_8A130310[i].text, D_8A12FE04, str, D_8A12F1FC, temp_s1, D_8A12F204, temp_s4, D_8A12F214[tier]);
              }
              D_8A130430 = ((strlen(D_8A130310[i].text) * 5) + 0x32) & 0xFFF8;
              D_8A130310[i].width = D_8A130430;
            }

            var_a1 = 0;
            for (x = 0; x < 7; x++)
            {
              for (j = 0; j < tmp; j++)
              {
                idx = D_8A12F574[ptr->unk_18[j]].group;
                if (idx == x)
                {
                  D_8A130438[var_a1] = j;
                  var_a1 += 1;
                  if (var_a1 >= tmp)
                  {
                    x = 7;
                    break;
                  }
                }
              }

            }

            if (D_8A130450 != 0)
            {
              for (i = 0; i < tmp; i++)
              {
                sel = D_8A130438[i];
                if (D_8A130310[sel].width > 0)
                {
                  Font_Printf(0xA0 - (D_8A130430 / 2), ((i * 0xA) - (tmp * 0xA)) + 0xC3, D_8A12FE14, D_8A130310[sel].text);
                }
              }

            }
          }
        }
      }
    }
    else
    {
      Font_Printf(0x65, 0xB8, D_8A12FE18, D_8A12F1B0);
    }
    if ((D_8A130308 == 0) || (D_8A1302D6 == D_8A1302D8))
    {
      Font_Printf(0x54 - (strlen(name) * 2), 0xD5, D_8A12FE1C, name);
    }
  }
  D_8A130432 = D_8A130430;
  Font_EndTexturedTextRendering();
  return 0;
}

s32 Pokedex_CheckAreaMapExit(void) {
    if ((gPlayer1Controller->buttonPressed & 0x4000) && (D_8A1302DA == 0)) {
        return -1;
    }

    if (D_8A1302DC == 0) {
        if (gPlayer1Controller->buttonPressed & 0x10) {
            D_8A1302D4 = (D_8A1302D4 + 1) & 1;
            switch (D_8A1302D4) {
                case 0:
                    Audio_PlaySoundEffectByIdWrapper(SFX_MENU_BACK);
                    break;
                case 1:
                    Audio_PlaySoundEffectByIdWrapper(SFX_MENU_CONFIRM);
                    break;
            }
        }

        if (gPlayer1Controller->buttonPressed & 0x800) {
            D_8A1302D8 = D_8A1302D6;
            D_8A1302D6 = Pokedex_FindNextMapArea(D_8A1302D6);
            if (D_8A1302D8 != D_8A1302D6) {
                Audio_PlaySoundEffectByIdWrapper(SFX_MENU_SCROLL);
                Pokedex_ResetCameraEase();
            }
        }

        if (gPlayer1Controller->buttonPressed & 0x400) {
            D_8A1302D8 = D_8A1302D6;
            D_8A1302D6 = Pokedex_FindPrevMapArea(D_8A1302D6);
            if (D_8A1302D8 != D_8A1302D6) {
                Audio_PlaySoundEffectByIdWrapper(SFX_MENU_SCROLL);
                Pokedex_ResetCameraEase();
            }
        }

        switch (D_8A1302DA) {
            case 0:
                if (gPlayer1Controller->buttonPressed & 0x8000) {
                    D_8A1302DA = 1;
                    if (D_8A1302D4 == 1) {
                        D_8A1302D4 = 0;
                    }
                    D_8A1302D8 = D_8A1302D6;
                    Audio_PlaySoundEffectByIdWrapper(SFX_ZOOM_IN);
                    Pokedex_ResetCameraEase();
                }
                break;

            case 1:
                if (gPlayer1Controller->buttonPressed & 0x4000) {
                    D_8A1302DA = 0;
                    D_8A130308 = 1;
                    D_8A1302D8 = D_8A1302D6;
                    Audio_PlaySoundEffectByIdWrapper(SFX_ZOOM_OUT);
                    Pokedex_ResetCameraEase();
                }
                break;
        }
    }
    return 0;
}

#include "fragments/fragment018_262620/pokedex_214920_types.h"
extern unk_D_80064C60 D_80064C60[];
extern s16 D_8A130432;
extern s16 D_8A130446;
extern s16 D_8A1302E0;
extern char D_8A1302E8[];
extern void* D_8A1302D0;
extern s16 D_8A12FB20[];
extern unk_D_88826CF0_004* D_8A120708[];
extern unk_D_88826CF0_004* D_8A1212DC[];
extern unk_D_88826CF0_004* D_8A121EB0[];
extern unk_D_88826CF0_004* D_8A122AAC[];
extern u8 D_8A12FB98[];
extern u8 D_8F100000[];
extern u8 D_00326700[];
extern u8 D_003553C0[];
extern u8 D_003FEBD0[];
extern u8 D_003FFD60[];
void func_8A1053E8(s32 arg0, MainPoolState* arg1, UNUSED s32 arg2, PERSSZP* arg3, s32 arg4) {
    s32 i;
    CameraNode* ptr;
    MemoryBlock* sp44;
    unk_D_88826CF0_004* var_v1_2;

    sp44 = MainPool_InitState(arg1, 0x70800);
    D_8A1302D4 = 0;
    D_8A130308 = 0;
    D_8A1302DA = 0;
    D_8A130432 = 0;
    D_8A130446 = 0;

    for (i = 0; i < 36; i++) {
        D_8A130458[i].unk_00 = 0;
        D_8A130458[i].unk_02 = 0;
    }

    D_8A1302E0 = arg0 - 1;
    sprintf(D_8A1302E8, "%s", D_80064C60[D_8A1302E0].unk_00);
    main_pool_push_state('MAPV');

    D_8A130448 = main_pool_alloc(0x3200, 0);
    Pokedex_LoadIcon(D_8A130448, arg0);

    Fragment_LoadAndRelocateFromRomRange(sp44, (((u32)&D_8F100000 & 0x0FF00000) >> 0x14) - 0x10, (s32)D_00326700,
                  (s32)D_003553C0, arg3, arg4);

    D_8A1302D0 = BinArchive_GetFile(BinArchive_Open(D_003FEBD0, D_003FFD60, 1, 1), 0);
    GeoNode_CreateDisplayList(NULL, &D_8A130250, 5, NULL);
    D_8A1302DC = 1;

    for (i = 0; i < 59; i++) {
        if (D_8A12FB20[i] >= 0) {
            unk_D_88826CF0* temp_s0 = &D_8A130458[D_8A12FAD8[D_8A12FB20[i]] - 1];

            D_8A1302DE = GbSave_GameToCategoryIndex(GbSave_GetPortGame(GbSave_GetActivePort()));

            switch (D_8A1302DE) {
                case 0:
                    var_v1_2 = D_8A120708[i];
                    break;

                case 1:
                    var_v1_2 = D_8A1212DC[i];
                    break;

                case 2:
                    var_v1_2 = D_8A121EB0[i];
                    break;

                case 3:
                    var_v1_2 = D_8A122AAC[i];
                    break;

                default:
                    var_v1_2 = D_8A122AAC[i];
                    break;
            }

            while (true) {
                if (var_v1_2->unk_00 < 0) {
                    break;
                }

                if (D_8A1302E0 == var_v1_2->unk_00 - 1) {
                    temp_s0->unk_00 = 1;
                    temp_s0->unk_04[temp_s0->unk_02] = var_v1_2;
                    temp_s0->unk_18[temp_s0->unk_02] = i;
                    D_8A1302DC = 0;
                    temp_s0->unk_02++;
                }
                var_v1_2++;
            }
        }
    }

    D_8A1302D6 = Pokedex_FindNextMapArea(0);
    D_8A1302D8 = D_8A1302D6;
    GeoNode_CreateDisplayList(NULL, &D_8A1302B0, 5, NULL);
    GeoNode_CreateDisplayList(NULL, &D_8A130290, 5, NULL);
    GeoNode_CreateDisplayList(NULL, &D_8A130270, 4, NULL);
    D_8A1302CC = process_geo_layout(sp44, D_8A12FB98);
    ptr = (CameraNode*)D_8A1302CC->children;
    ptr->view.targetPosition = D_8A12F838;
    ptr->view.eyePosition = D_8A12F844;
}

void Pokedex_ExitAreaMapPool(void) {
    main_pool_pop_state('MAPV');
}
