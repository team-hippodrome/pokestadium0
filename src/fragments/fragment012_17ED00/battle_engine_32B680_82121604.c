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

extern f32 D_FLT_8218935C[][4];
extern Vec3f D_8218B630;
extern Vec3f D_8218B63C;
void func_821224F4(CameraNode*);
void func_82121D78(CameraNode*, f32, f32);
void func_8212187C(s32);
void BattleCamera_CaptureModelOrbit(ActivePokemon*, CameraNode*);
extern f32 D_FLT_82196040;
void BattleCamera_CaptureModelOrbit(ActivePokemon*, CameraNode*);
void func_8212054C(CameraNode*);
extern const f64 D_DBL_821960A0;
extern f32 D_FLT_82189358[][4];
void BattleScene_SelectNextBRollCameraShot(CameraNode*);
void BattleScene_SelectNextBRollCameraShot(CameraNode*);
void func_82122FD8(CameraNode*, ActivePokemon*);
s32 func_821217DC(M2C_UNK);
extern f32 D_FLT_82189358[][4];
void BattleScene_SelectNextBRollCameraShot(CameraNode*);
void BattleScene_SelectNextBRollCameraShot(CameraNode*);
s32 func_821217DC(M2C_UNK);
void func_82122628(s32, Vec3f, s32, s32, f32, f32);
extern f32 D_FLT_821960A8;
void func_82122A7C(CameraNode*, ActivePokemon*);
void func_8212188C(void);
extern s8 *D_8219A5A0;
extern u8* D_800603C0;

void func_82120A34(CameraNode*);
void func_82120A90(CameraNode*);
void func_82121434(CameraNode*);
/**
 * Not reached in play (2026-11-13): no move in the 165-move battle sweep called it (each move used
 * once, from the command menu to the end of its turn).
 * @unverified Name was previously used only by callers of this address; the definition was still func_.
 */
void Rental_TeamSlotsUpdate(CameraNode* arg0) {
    switch (sBattleScene.scene->phaseStep) {
        case 1:
            func_82120A34(arg0);
            break;
        case 3:
            func_82120A90(arg0);
            break;
        case 5:
            func_82120AC8(arg0);
            break;
        case 7:
            func_82120BB8(arg0);
            break;
        case 9:
            func_82120BB8(arg0);
            break;
        case 11:
            func_82120C44(arg0);
            break;
        case 13:
            func_82120D94(arg0);
            break;
        case 15:
            func_82120D94(arg0);
            break;
        case 17:
            func_82120E70(arg0);
            break;
        case 19:
            func_82120E70(arg0);
            break;
        case 21:
            func_82120FB0(arg0);
            break;
        case 23:
            BattleScene_BRollCameraUpdatePresetHold(arg0);
            break;
        case 25:
            func_8212116C(arg0);
            break;
        case 27:
            func_821211D4((s32)arg0);
            break;
        case 29:
            func_8212120C(arg0);
            break;
        case 50:
            func_82121434(arg0);
            break;
    }
}
