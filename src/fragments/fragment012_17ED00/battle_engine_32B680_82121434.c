/* Fixed-layout split; original translation-unit boundaries remain unconfirmed. */
#include "fragments/battle_engine/battle_engine.h"
#include "model_animation.h"
#include "geo_render.h"
#include "gfx_buffer.h"
#include "matrix.h"
#include "math_util.h"
#include "fragments/battle_engine/battle_engine.h"
#include "model_animation.h"
#include "matrix.h"
#include "m2c_macros.h"
void func_8211F580(void);
void BattleScene_IntroCameraRollStepNoFov(CameraNode* arg0);
void BattleScene_SelectNextIntroCameraShot(CameraNode* arg0);
extern f32 D_FLT_8218935C[][4];
extern Vec3f D_8218B630;
extern Vec3f D_8218B63C;
void func_821224F4(CameraNode*);
void func_82121D78(CameraNode*, f32, f32);
void func_8212187C(s32);
void func_821351F8(CameraNode*, ActivePokemon*);
s32 func_8211F644(ActivePokemon*, CameraNode*);
void func_82104C68(ActivePokemon*, s32);
f32 BattleScene_GetParticipantHeight(ActivePokemon*);
void func_8212239C(ActivePokemon*, CameraNode*);
extern f32 D_FLT_82196040;
void func_8212239C(ActivePokemon*, CameraNode*);
void func_8212054C(CameraNode*);
extern const f64 D_DBL_821960A0;
extern f32 D_FLT_82189358[][4];
void BattleScene_SelectNextIntroCameraShot(CameraNode*);
void BattleScene_SelectNextIntroCameraShot(CameraNode*);
void func_82122FD8(CameraNode*, ActivePokemon*);
s32 func_821217DC(M2C_UNK);
extern f32 D_FLT_82189358[][4];
void BattleScene_SelectNextIntroCameraShot(CameraNode*);
void BattleScene_SelectNextIntroCameraShot(CameraNode*);
s32 func_82135734(CameraNode*, ActivePokemon*);
s32 func_821217DC(M2C_UNK);
void func_82122628(s32, Vec3f, s32, s32, f32, f32);
extern f32 D_FLT_821960A8;
f32 func_82121750(ActivePokemon*, f32, f32);
void func_82122A7C(CameraNode*, ActivePokemon*);
s32 func_82135734(CameraNode*, ActivePokemon*);
void func_8212188C(void);
extern s8 *D_8219A5A0;
extern u8* D_800603C0;
void Audio_FadeCategoriesAndStreams(s32 arg0);

extern u8 D_8219A4F4;
extern u8* D_8218B2B8[];
void func_8211F9C4(CameraNode*);
void func_82121C3C(CameraNode*);
void func_82108C0C(ActivePokemon*);

void func_82121434(CameraNode* arg0) {
    if (D_8219A4F4 == 5) {
        sBattleScene.scene->phaseStep = 0x18;
        func_8211F9C4(arg0);
        return;
    }
    if (D_8218B2B8[D_8219A4F4][sBattleScene.scene->bRollShotIndex] == 0xFF) {
        sBattleScene.scene->bRollShotIndex = 0;
    }
    sBattleScene.scene->phaseStep = D_8218B2B8[D_8219A4F4][sBattleScene.scene->bRollShotIndex];
    sBattleScene.scene->bRollShotIndex++;
    func_82108C0C(sActivePokemon[0]);
    func_82108C0C(sActivePokemon[1]);
    func_8212188C();
    switch (sBattleScene.scene->phaseStep) {
        case 0:
            func_8211F6B8(arg0);
            break;
        case 2:
            func_8211F84C(arg0);
            break;
        case 4:
            func_8211FB54(arg0);
            break;
        case 6:
            func_8211FCC8(arg0);
            break;
        case 8:
            func_8211FF08(arg0);
            break;
        case 10:
            func_82120134(arg0);
            break;
        case 12:
            func_8211FA34(arg0);
            break;
        case 14:
            func_8211FAC4(arg0);
            break;
        case 16:
            func_821202AC(arg0);
            break;
        case 18:
            func_821202AC(arg0);
            break;
        case 20:
            func_82120418(arg0);
            break;
        case 22:
            func_8212054C(arg0);
            break;
    }
    func_82121C3C(arg0);
}
