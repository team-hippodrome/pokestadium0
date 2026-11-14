/* Stadium Zero fragment001_15B1A0: model display-list callbacks. */
#include "global.h"
#include "model_callbacks.h"
#include "gfx_buffer.h"
#include "geo_render.h"
#include "model_renderer_callbacks.h"
#include "battle_hud.h"
#include "vector_math.h"

extern s16 D_800AFB28;
Gfx* func_80032D90(Gfx* gfx);

typedef struct ModelParticle {
    /* 0x00 */ s16 active;
    /* 0x02 */ char unk02[0x2];
    /* 0x04 */ Vec3f position;
    /* 0x10 */ Vec3f velocity;
    /* 0x1C */ Vec3f scale;
    /* 0x28 */ s16 misc;
    /* 0x2A */ char unk2A[0x2];
} ModelParticle; // size = 0x2C

extern Vec3f D_8100239C;
extern Vec3f D_810023A8;
extern Vec3f D_810023B4;
extern ModelParticle D_810028A0[][10];
extern s32 D_81002C10;
extern s32 D_81002C14;
extern Vec3f D_810023C0;

typedef struct ModelParticleTiming {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04[3];
    /* 0x0A */ s16 unk_0A;
} ModelParticleTiming; // size = 0xC

extern ModelParticleTiming D_810022A0[18];
extern s16 D_81002378[18];
extern CameraNode* D_80060488;
extern Gfx D_810023D0[];
extern s16 D_81002C20;

typedef struct ModelScrollTextures {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s32 unk_04[6];
} ModelScrollTextures; // size = 0x1C

typedef struct ModelScrollTexturesState {
    /* 0x00 */ char unk00[0x14];
    /* 0x14 */ u32* unk_14;
    /* 0x18 */ Gfx* unk_18;
} ModelScrollTexturesState; // size = 0x1C

typedef struct TextureState {
    /* 0x00 */ char unk00[0x14];
    /* 0x14 */ u32* textures;
    /* 0x18 */ Gfx* gfx;
} TextureState; // size = 0x1C

extern s16 D_800AFB26;

void func_81000510(s32 arg0, s32 arg1) {
    s32 pad[2];
    Vec3f sp1C = D_8100239C;
    Vec3f sp10 = D_810023A8;
    Vec3f sp4 = D_810023B4;

    D_810028A0[arg0][arg1].active = 0;
    D_810028A0[arg0][arg1].misc = 0;
    D_810028A0[arg0][arg1].position = sp1C;
    D_810028A0[arg0][arg1].velocity = sp10;
    D_810028A0[arg0][arg1].scale = sp4;
}

void func_8100060C(s32 arg0) {
    s32 i;

    for (i = 0; i < 10; i++) {
        func_81000510(arg0, i);
    }
}

void func_8100065C(void) {
    D_81002C10 = 0;
    D_81002C14 = 0;
}

void func_81000670(ModelParticle* arg0) {
    s32 var_v0;
    Vec3f sp90;
    Vec3f sp84;
    Vec3f sp78;
    s32 var_s1;
    f32 temp_fv0_2;
    Vec3f sp64 = D_810023C0;
    f32 sp60;
    f32 sp5C;
    f32 sp58;
    u32 pad[2];
    f32 var_fs0;

    var_s1 = 10;
    guMtxXFMF(GeoRender_GetRelativeMatrix(-1)->mf, 0, 0, 0, &sp90.x, &sp90.y, &sp90.z);
    guMtxXFMF(GeoRender_GetRelativeMatrix(0)->mf, 0, 0, 0, &sp84.x, &sp84.y, &sp84.z);
    sp60 = D_8006049C->scale.x;
    sp5C = D_8006049C->scale.y;
    sp58 = D_8006049C->scale.z;
    switch (D_8006049C->objectType) {
        case 0x6D:
        case 0x6E:
            var_fs0 = 0.5f;
            break;
        case 0x92:
            var_fs0 = 1.0f;
            sp64.x = 0.1f;
            sp64.y = 0.1f;
            sp64.z = 0.1f;
            sp84.x += (f32)((guRandom() % 10) - 5) * sp60;
            sp84.y += (f32)((guRandom() % 10) - 5) * sp5C;
            sp84.z += (f32)((guRandom() % 10) - 5) * sp58;
            break;
        case 0x4D:
            var_fs0 = 0.5f;
            sp64.x = 0.002f;
            sp64.y = 0.002f;
            sp64.z = 0.002f;
            sp84.x += (f32)((guRandom() % 20) - 10) * sp60;
            sp84.y += (f32)((guRandom() % 20) - 10) * sp5C;
            sp84.z += (f32)((guRandom() % 20) - 10) * sp58;
            break;
        case 0x4E:
            var_fs0 = 0.5f;
            sp64.x = 0.05f;
            sp64.y = 0.05f;
            sp64.z = 0.05f;
            sp84.x += (f32)((guRandom() % 20) - 10) * sp60;
            sp84.y += (f32)((guRandom() % 10) - 5) * sp5C;
            sp84.z += (f32)((guRandom() % 20) - 10) * sp58;
            break;
        case 0x90:
            var_fs0 = 0.0f;
            sp64.x = 0.5f;
            sp64.y = 0.5f;
            sp64.z = 0.5f;
            sp84.x += (f32)((guRandom() % 20) - 10) * sp60;
            sp84.y += (f32)((guRandom() % 20) - 10) * sp5C;
            sp84.z += (f32)((guRandom() % 20) - 10) * sp58;
            break;
        case 0x86:
            var_fs0 = 0.0f;
            sp64.x = 0.5f;
            sp64.y = 0.5f;
            sp64.z = 0.5f;
            sp84.x += (f32)((guRandom() % 60) - 30) * sp60;
            sp84.y += (f32)((guRandom() % 40) - 10) * sp5C;
            sp84.z += (f32)((guRandom() % 60) - 30) * sp58;
            break;
        case 0x5C:
            var_fs0 = 0.0f;
            var_s1 = 3;
            sp64.x = 20.0f;
            sp64.y = 20.0f;
            sp64.z = 20.0f;
            break;
        default:
            var_fs0 = 0.0f;
            break;
    }
    for (var_v0 = 0; var_v0 < 10; var_v0++) {
        if (var_v0 >= var_s1) {
            break;
        }
        if (arg0->active == 0) {
            sp78.x = sp84.x - sp90.x;
            sp78.y = sp84.y - sp90.y;
            sp78.z = sp84.z - sp90.z;
            temp_fv0_2 = sqrtf((sp78.x * sp78.x) + (sp78.y * sp78.y) + (sp78.z * sp78.z));
            if (temp_fv0_2 > 0.0f) {
                sp78.x /= temp_fv0_2;
                sp78.y /= temp_fv0_2;
                sp78.z /= temp_fv0_2;
            }
            arg0->velocity.x = (f32)(var_fs0 * sp78.x);
            arg0->velocity.y = (f32)(var_fs0 * sp78.y);
            arg0->velocity.z = (f32)(var_fs0 * sp78.z);
            arg0->position = sp84;
            arg0->scale = sp64;
            arg0->misc = 0;
            arg0->active = 1;
            break;
        }
        arg0++;
    }
}

void func_81000CC8(ModelParticle* arg0) {
    s32 pad[1];
    s16 temp_v1;
    s32 var_a1;
    s16 temp_a0;
    s32 var_v0;
    s16* var_v1;

    var_a1 = D_8006049C->transformAnim.frameFixed >> 0x10;
    switch (D_8006049C->objectType) {
        case 0x6D:
        case 0x6E:
            temp_v1 = D_8006049C->transformAnim.animationId;
            temp_a0 = D_81002378[D_81002C14 % 18];
            switch (temp_v1) {
                case 4:
                    if (var_a1 == D_810022A0[temp_a0].unk_02) {
                        func_81000670(arg0);
                        return;
                    }
                    break;
                case 3:
                    var_v0 = 0;
                    var_v1 = &D_810022A0[temp_a0].unk_00;
                    do {
                        if (var_a1 == var_v1[2]) {
                            func_81000670(arg0);
                        }
                        var_v0 += 2;
                        var_v1++;
                    } while (var_v0 != 6);
                    return;
                    break;
                case 2:
                    if (var_a1 == D_810022A0[temp_a0].unk_0A) {
                        func_81000670(arg0);
                        return;
                    }
                    break;
                default:
                    if (var_a1 == D_810022A0[temp_a0].unk_00) {
                        func_81000670(arg0);
                        return;
                    }
                    return;
            }
            break;
        case 0x92:
            if ((guRandom() % 60) == 0) {
                func_81000670(arg0);
                return;
            }
            break;
        case 0x90:
            if ((guRandom() % 30) == 0) {
                func_81000670(arg0);
                return;
            }
            break;
        case 0x86:
            if ((guRandom() % 7) == 0) {
                func_81000670(arg0);
                return;
            }
            break;
        case 0x5C:
            if ((var_a1 & 7) == 0) {
                func_81000670(arg0);
                return;
            }
            break;
        case 0x4D:
        case 0x4E:
            if ((guRandom() % 7) == 0) {
                func_81000670(arg0);
            }
            break;
    }
}

Gfx* func_81000F18(Gfx* gfx, ModelParticle* arg1, DisplayListAddresses* arg2, s16 arg3) {
    Mtx* sp1EC;
    Mtx sp1A8;
    Mtx sp168;
    Mtx sp128;
    s32 pad;
    MtxF spE4;
    DisplayObject* ptr;

    sp1EC = Gfx_AllocDisplayList(0x40);
    MtxF_ExtractScale(&spE4, &D_80060488->view.floatMatrix);
    guMtxF2L(spE4.mf, &sp128);
    guScale(&sp1A8, D_8006049C->scale.x * arg1->scale.x * 0.1f, D_8006049C->scale.y * arg1->scale.y * 0.1f,
            D_8006049C->scale.z * arg1->scale.z * 0.1f);
    guTranslate(&sp168, arg1->position.x, arg1->position.y, arg1->position.z);
    guMtxCatL(&sp1A8, &sp168, sp1EC);
    guMtxCatL(&sp128, sp1EC, sp1EC);
    gSPMatrix(gfx++, sp1EC, G_MTX_PUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(gfx++, arg2->segments[0]);
    switch (D_8006049C->objectType) {
        case 0x6D:
        case 0x6E:
            gDPLoadTextureBlock_4b(gfx++, arg2->textures[arg1->misc / 2], G_IM_FMT_I, 32, 32, 0,
                                   G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK,
                                   G_TX_NOLOD, G_TX_NOLOD);
            gDPSetPrimColor(gfx++, 0, 0, 0x0A, 0x00, 0x00, 0xC8 - (arg1->misc * 0xD));
            break;
        case 0x5C:
            gDPLoadTextureBlock_4b(gfx++, arg2->textures[arg1->misc / 2], G_IM_FMT_I, 32, 32, 0,
                                   G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK,
                                   G_TX_NOLOD, G_TX_NOLOD);
            gDPSetEnvColor(gfx++, 0x32, 0x14, 0x46, 0x00);
            if (arg1->misc < 0xA) {
                gDPSetPrimColor(gfx++, 0, 0, 0x64, 0x46, 0x82, 0xFF);
            } else {
                gDPSetPrimColor(gfx++, 0, 0, 0x64, 0x46, 0x82, 0x28F - (arg1->misc * 0x28));
            }
            break;
        case 0x92:
        case 0x4D:
        case 0x4E:
            gDPLoadTextureBlock_4b(gfx++, arg2->textures[arg1->misc / 2], G_IM_FMT_I, 32, 32, 0,
                                   G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK,
                                   G_TX_NOLOD, G_TX_NOLOD);
            gDPSetPrimColor(gfx++, 0, 0, 0xFF, 0xFF, 0x00, 0xFA - (arg1->misc * 3));
            break;
        case 0x86:
        case 0x90:
            gDPLoadTextureBlock(gfx++, arg2->textures[arg1->misc / 2], G_IM_FMT_IA, G_IM_SIZ_16b, 32, 32, 0,
                                G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK,
                                G_TX_NOLOD, G_TX_NOLOD);
            if (arg1->misc < 4) {
                gDPSetPrimColor(gfx++, 0, 0, 0xFF, 0xFF, 0xFF, (arg1->misc * 0x14) + 0xB4);
            } else {
                gDPSetPrimColor(gfx++, 0, 0, 0xFF, 0xFF, 0xFF, 0x122 - (arg1->misc * 0xA));
            }
            break;
        default:
            gDPLoadTextureBlock_4b(gfx++, arg2->textures[arg1->misc / 2], G_IM_FMT_I, 32, 32, 0,
                                   G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK,
                                   G_TX_NOLOD, G_TX_NOLOD);
            gDPSetPrimColor(gfx++, 0, 0, 0x0A, 0x00, 0x00, 0xC8 - (arg1->misc * 0xD));
            break;
    }
    gSPDisplayList(gfx++, arg2->segments[1]);
    gSPPopMatrix(gfx++, G_MTX_MODELVIEW);
    if (ModelPhase_IsIdle() == 0) {
        ptr = D_8006049C;
        switch (ptr->objectType) {
            case 0x6D:
            case 0x6E:
                arg1->position.y += 0.5f * ptr->scale.y;
                arg1->misc++;
                arg1->scale.x += 0.1f;
                arg1->scale.y += 0.1f;
                arg1->scale.z += 0.1f;
                if (arg1->misc >= 0x10) {
                    arg1->active = 0;
                }
                break;
            case 0x5C:
                arg1->misc++;
                if (arg1->misc >= 0x10) {
                    arg1->active = 0;
                }
                break;
            case 0x92:
                arg1->position.y += 1.5f * ptr->scale.y;
                arg1->misc++;
                arg1->scale.x += 0.005f;
                arg1->scale.y += 0.005f;
                arg1->scale.z += 0.005f;
                if (arg1->misc >= 0x10) {
                    arg1->active = 0;
                }
                break;
            case 0x4D:
                arg1->position.y += 0.75f * ptr->scale.y;
                arg1->misc++;
                arg1->scale.x += 0.005f;
                arg1->scale.y += 0.005f;
                arg1->scale.z += 0.005f;
                if (arg1->misc >= 0x10) {
                    arg1->active = 0;
                }
                break;
            case 0x4E:
                arg1->position.y += ptr->scale.y;
                arg1->misc++;
                arg1->scale.x += 0.005f;
                arg1->scale.y += 0.005f;
                arg1->scale.z += 0.005f;
                if (arg1->misc >= 0x10) {
                    arg1->active = 0;
                }
                break;
            case 0x90:
                arg1->position.y -= 0.5f * ptr->scale.y;
                if (arg1->misc < 4) {
                    arg1->scale.x += 0.15f;
                    arg1->scale.y += 0.15f;
                    arg1->scale.z += 0.15f;
                } else {
                    arg1->scale.x -= 0.075f;
                    arg1->scale.y -= 0.075f;
                    arg1->scale.z -= 0.075f;
                }
                arg1->misc++;
                if ((arg1->misc >= 0xC) || (arg1->position.y < 0.0f)) {
                    arg1->active = 0;
                }
                break;
            case 0x86:
                if (arg1->misc < 4) {
                    arg1->scale.x += 0.15f;
                    arg1->scale.y += 0.15f;
                    arg1->scale.z += 0.15f;
                } else {
                    arg1->scale.x -= 0.075f;
                    arg1->scale.y -= 0.075f;
                    arg1->scale.z -= 0.075f;
                }
                arg1->misc++;
                if ((arg1->misc >= 0xC) || (arg1->position.y < 0.0f)) {
                    arg1->active = 0;
                }
                break;
            default:
                arg1->misc++;
                if (arg1->misc >= 0x10) {
                    arg1->active = 0;
                }
                break;
        }
        arg1->position.x = (f32)(arg1->position.x + arg1->velocity.x);
        arg1->position.y = (f32)(arg1->position.y + arg1->velocity.y);
        arg1->position.z = (f32)(arg1->position.z + arg1->velocity.z);
        arg1->velocity.x *= 0.9f;
        arg1->velocity.y *= 0.9f;
        arg1->velocity.z *= 0.9f;
    }
    return gfx;
}

Gfx* func_81001A64(Gfx* gfx, ModelParticle* arg1, DisplayListAddresses* arg2, s16 arg3) {
    s32 i;

    for (i = 0; i < 10; i++, arg1++) {
        if (arg1->active == 1) {
            gfx = func_81000F18(gfx, arg1, arg2, arg3);
            D_81002C10++;
        }
    }
    return gfx;
}

void func_81001B24(s32 arg0, DisplayListState* state) {
    s32 pad0[2];
    DisplayListAddresses* sp4C;
    s32 pad;
    s16 temp_v1;
    s32 pad3[3];
    ModelParticle* sp1C;
    s32 sp18;
    ModelParticle* temp_a1;
    Gfx* gfx;
    s32 pad4[1];

    sp4C = state->addresses;
    if (arg0 == 0) {
    } else if (arg0 == 2) {
        if (D_81002C14 == 0) {
            state->gfx = Gfx_AllocDisplayList(0x418);
        } else {
            state->gfx = Gfx_AllocDisplayList(8);
        }
        gfx = state->gfx;
        temp_v1 = D_8006049C->effectSlot;
        if ((temp_v1 < 2) && (D_81002C10 >= 0) && (D_81002C10 < 11)) {
            temp_a1 = D_810028A0[temp_v1];
            sp1C = temp_a1;
            sp18 = temp_v1;
            func_81000CC8(temp_a1);
            if (D_81002C14 == 0) {
                gfx = func_81001A64(gfx, temp_a1, sp4C, temp_v1);
            }
        }
        gSPEndDisplayList(gfx++);
    }
    D_81002C14++;
}
