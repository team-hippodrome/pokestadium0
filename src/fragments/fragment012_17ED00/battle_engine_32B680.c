/* Stadium Zero fragment012_17ED00. */
/* C ported from the Stadium 1 decomp: src/fragments/battle_engine/battle_engine_304060.c, src/fragments/battle_engine/battle_engine_32B680.c. */

#include "fragments/battle_engine/battle_engine.h"
#include "model_animation.h"
#include "geo_render.h"
#include "gfx_buffer.h"
#include "matrix.h"
#include "math_util.h"

#include "fragments/battle_engine/battle_engine.h"
#include "model_animation.h"
#include "matrix.h"
typedef struct unk_D_843859E0 {
    /* 0x00 */ u8 unk_00;
    /* 0x04 */ f32 unk_04;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ f32 unk_0C;
} unk_D_843859E0;

#include "m2c_macros.h"

void func_8211F580(void);
void BattleScene_BRollCameraUpdateRotatingArenaOverview(CameraNode* arg0);

void BattleScene_SelectNextBRollCameraShot(CameraNode* arg0);

void func_8211F580(void) {
}

extern f32 D_FLT_8218935C[][4];
/**
 * Seen in play (2026-11-13) (tour of menus and a COM battle): ran in the battle opening, a switch
 * in battle and running from battle.
 * @unverified Name was previously used only by callers of this address; the definition was still func_.
 */
s32 BattleScene_AreBothParticipantModelsCompact(void) {
    if ((D_FLT_8218935C[M2C_FIELD(sActivePokemon[0], s16*, 0x1A) - 1][1] + D_FLT_8218935C[M2C_FIELD(sActivePokemon[1], s16*, 0x1A) - 1][1] <= 85.0f) &&
        (D_FLT_8218935C[M2C_FIELD(sActivePokemon[0], s16*, 0x1A) - 1][2] == 0.0f) &&
        (D_FLT_8218935C[M2C_FIELD(sActivePokemon[1], s16*, 0x1A) - 1][2] == 0.0f) &&
        (M2C_FIELD(sActivePokemon[0], f32*, 0x28) == 0.0f) &&
        (M2C_FIELD(sActivePokemon[1], f32*, 0x28) == 0.0f)) {
        return 1;
    }
    return 0;
}

s32 BattleScene_SkipUnavailableBRollShot(UNUSED ActivePokemon* arg0, CameraNode* arg1) {
    ActivePokemonState* ptr = &sActivePokemon[sBattleScene.scene->actingSide]->state;

    if ((ptr->unk_2D == 0x10) || ((ptr->flags & 0x4000) != 0)) {
        BattleScene_SelectNextBRollCameraShot(arg1);
        return 1;
    }
    return 0;
}

extern Vec3f D_8218B630;
extern Vec3f D_8218B63C;
void BattleScene_BRollCameraSetupArenaOrbit(CameraNode* arg0) {
    BattleScene_SetCameraClipPlanes(arg0, 20.0f, 4000.0f);
    BattleScene_ResetCameraFrameCounter();
    if (BattleScene_AreBothParticipantModelsCompact() != 0) {
        BattleScene_SetCameraAtFromPosition(arg0, D_8218B63C, 0, 0, 0.0f, 0.0f);
        BattleScene_SetCameraEyeAndStoreAngles(arg0, D_8218B63C, 0x5B0, 0, 750.0f, 0.0f);
    } else {
        BattleScene_SetCameraAtFromPosition(arg0, D_8218B630, 0, 0, 0.0f, 0.0f);
        BattleScene_SetCameraEyeAndStoreAngles(arg0, D_8218B630, 0x5B0, 0, 750.0f, 0.0f);
    }
    arg0->view.eyePosition.z *= 0.6;
    sBattleScene.scene->phaseStep++;
}

void BattleScene_BRollCameraSetupRotatingArenaOverview(CameraNode* arg0) {
    BattleScene_SetCameraClipPlanes(arg0, 20.0f, 4000.0f);
    BattleScene_ResetCameraFrameCounter();
    if (BattleScene_AreBothParticipantModelsCompact() != 0) {
        BattleScene_SetCameraAtFromPosition(arg0, D_8218B63C, 0, 0, 0.0f, 0.0f);
        BattleScene_SetCameraEyeAndStoreAngles(arg0, D_8218B63C, 0x1A4E, 0, 1000.0f, 0.0f);
    } else {
        BattleScene_SetCameraAtFromPosition(arg0, D_8218B630, 0, 0, 0.0f, 0.0f);
        BattleScene_SetCameraEyeAndStoreAngles(arg0, D_8218B630, 0x1A4E, 0, 1000.0f, 0.0f);
    }
    sBattleScene.scene->phaseStep++;
}

void func_821224F4(CameraNode*);
void func_82121D78(CameraNode*, f32, f32);
void func_8212187C(s32);
void func_821351F8(CameraNode*, ActivePokemon*);
/**
 * Sets up the battle camera and presentation on the acting Pokémon.
 * @unverified Name from Stadium 1.
 */
void BattleScene_InitializeBattlePresentation(CameraNode* arg0) {
    func_821224F4(arg0);
    func_82121D78(arg0, 20.0f, 4000.0f);
    func_8212187C(0);
    func_821351F8(arg0, sActivePokemon[sBattleScene.scene->actingSide]);
    sBattleScene.scene->phaseStep++;
}

s32 func_8211F644(ActivePokemon*, CameraNode*);
void func_82104C68(ActivePokemon*, s32);
void func_8211FA34(CameraNode* arg0) {
    ActivePokemon* pokemon;

    func_821224F4(arg0);
    func_82121D78(arg0, 20.0f, 4000.0f);
    func_8212187C(0);
    pokemon = sActivePokemon[sBattleScene.scene->actingSide];
    if (func_8211F644(pokemon, arg0) == 0) {
        func_821351F8(arg0, pokemon);
        func_82104C68(pokemon, 0x10);
        sBattleScene.scene->phaseStep++;
    }
}

void func_8211FAC4(CameraNode* arg0) {
    ActivePokemon* pokemon;

    func_821224F4(arg0);
    func_82121D78(arg0, 20.0f, 4000.0f);
    func_8212187C(1);
    pokemon = sActivePokemon[sBattleScene.scene->actingSide];
    if (func_8211F644(pokemon, arg0) == 0) {
        func_821351F8(arg0, pokemon);
        func_82104C68(pokemon, 0x10);
        sBattleScene.scene->phaseStep++;
    }
}

f32 BattleScene_GetParticipantHeight(ActivePokemon*);
void BattleCamera_CaptureModelOrbit(ActivePokemon*, CameraNode*);
void func_8211FB54(CameraNode* arg0) {
    UNUSED s32 pad; // FAKE: stack padding
    f32 dist;
    UNUSED s32 pad2; // FAKE: stack padding
    s16 angle;
    ActivePokemon* pokemon;

    func_821224F4(arg0);
    func_82121D78(arg0, 20.0f, 4000.0f);
    func_8212187C(0);
    pokemon = sActivePokemon[sBattleScene.scene->actingSide];
    if (func_8211F644(pokemon, arg0) == 0) {
        func_82104C68(pokemon, 0x10);
        BattleAnim_GetOwnerDefaultAnchorPosition(pokemon, &sBattleScene.scene->unk_D0);
        dist = BattleScene_ScaleCameraDistance(pokemon, 3.5f, 300.0f);
        angle = BattleScene_GetParticipantFacingAngle(pokemon);
        BattleScene_SetCameraAtFromPosition(arg0, sBattleScene.scene->unk_D0, 0, angle, 0.0f, BattleScene_GetParticipantHeight(pokemon) * 1.5f);
        BattleScene_SetCameraEyeFromPosition(arg0, sBattleScene.scene->unk_D0, 0, BattleScene_GetParticipantFacingAngle(pokemon), dist, 0.0f);
        BattleCamera_CaptureModelOrbit(pokemon, arg0);
        sBattleScene.scene->phaseStep++;
    }
}

void func_8211FCC8(CameraNode* arg0) {
    UNUSED s32 pad[2]; // FAKE: stack padding
    f32 sp4C;
    UNUSED CameraNode** pad2 = &arg0;
    u16 sp46;
    f32 dist;
    ActivePokemon* pokemon;
    func_821224F4(arg0); func_8212187C(0); func_82121D78(arg0, 20.0f, 4000.0f);
    pokemon = sActivePokemon[sBattleScene.scene->actingSide];
    if (func_8211F644(pokemon, arg0) == 0) {
        func_82104C68(pokemon, 1);
        BattleAnim_GetOwnerDefaultAnchorPosition(pokemon, &sBattleScene.scene->unk_D0);
        dist = BattleScene_GetParticipantModelRadiusScaled(pokemon) * 3.5f;
        sp46 = BattleAnim_RandomRange(3);
        dist *= BattleAnim_GetSpeciesBaseScale(pokemon) * 0.5 * sp46 + 1.0;
        if (dist > 500.0f) dist = 500.0f;
        sp46 = BattleAnim_RandomRange(4);
        sp4C = BattleScene_GetParticipantHeight(pokemon) * sp46;
        BattleScene_SetCameraAtFromAnchor(pokemon, arg0, sBattleScene.scene->unk_D0, 0, 0, 0.0f, 0);
        BattleScene_SetCameraEyeFromPosition(arg0, sBattleScene.scene->unk_D0, 0, 0x4000 - BattleAnim_RandomRange(0xB4) * 0xB6, dist, sp4C);
        BattleCamera_CaptureModelOrbit(pokemon, arg0); sBattleScene.scene->phaseStep++;
    }
}

void func_8211FF08(CameraNode* arg0) {
    UNUSED s32 pad[2]; // FAKE: stack padding
    f32 sp4C;
    UNUSED CameraNode** pad2 = &arg0;
    u16 sp46;
    f32 dist;
    ActivePokemon* pokemon;
    func_821224F4(arg0); func_8212187C(1); func_82121D78(arg0, 20.0f, 4000.0f);
    pokemon = sActivePokemon[sBattleScene.scene->actingSide];
    if (func_8211F644(pokemon, arg0) == 0) {
        func_82104C68(pokemon, 1);
        BattleAnim_GetOwnerDefaultAnchorPosition(pokemon, &sBattleScene.scene->unk_D0);
        dist = BattleScene_GetParticipantModelRadiusScaled(pokemon) * 3.5f;
        sp46 = BattleAnim_RandomRange(3);
        dist *= BattleAnim_GetSpeciesBaseScale(pokemon) * 0.5f * sp46 + 1.0f;
        if (dist > 500.0f) dist = 500.0f;
        sp46 = BattleAnim_RandomRange(4);
        sp4C = BattleScene_GetParticipantHeight(pokemon) * sp46;
        BattleScene_SetCameraAtFromAnchor(pokemon, arg0, sBattleScene.scene->unk_D0, 0, 0, 0.0f, 0);
        BattleScene_SetCameraEyeFromPosition(arg0, sBattleScene.scene->unk_D0, 0, 0x4000 - BattleAnim_RandomRange(0xB4) * 0xB6, dist, sp4C);
        BattleCamera_CaptureModelOrbit(pokemon, arg0); sBattleScene.scene->phaseStep++;
    }
}

extern f32 D_FLT_82196040;

/**
 * Intro camera shot (compare func_8212054C and func_821202AC). Clears the camera offset
 * vectors, calls func_8212187C(1), and takes the active Pokemon selected by scene->unk_2C.
 * Unless BattleScene_SkipUnavailableBRollShot handles it, it enters state row 0x10, stores the
 * Pokemon's default anchor position in scene->unk_D0, derives a camera distance (factor
 * 3.5f, base 300.0f), aims the camera at the anchor using the Pokemon's facing angle and
 * a height offset of -BattleScene_GetParticipantHeight(ap), puts the eye at the same anchor with
 * -BattleScene_GetParticipantHeight(ap) * 0.2f, calls BattleCamera_CaptureModelOrbit(ap, camera) and advances
 * scene->unk_20.
 * `pad` only reserves the stack slot the retail frame has between `dist` and `angle`.
 */
void func_82120134(CameraNode* arg0) {
    ActivePokemon* ap;
    f32 dist;
    UNUSED s32 pad; // FAKE: stack padding
    s16 angle;

    BattleScene_ClearCameraOffsetVectors();
    func_8212187C(1);
    ap = sActivePokemon[sBattleScene.scene->actingSide];
    if (BattleScene_SkipUnavailableBRollShot(ap, arg0) == 0) {
        BattleScene_EnterStateRow(ap, 0x10);
        BattleAnim_GetOwnerDefaultAnchorPosition(ap, &sBattleScene.scene->unk_D0);
        dist = BattleScene_ScaleCameraDistance(ap, 3.5f, 300.0f);
        angle = BattleScene_GetParticipantFacingAngle(ap);
        BattleScene_SetCameraAtFromAnchor(ap, arg0, sBattleScene.scene->unk_D0, 0, angle, 0.0f, -BattleScene_GetParticipantHeight(ap));
        angle = BattleScene_GetParticipantFacingAngle(ap);
        BattleScene_SetCameraEyeFromPosition(arg0, sBattleScene.scene->unk_D0, 0, angle, dist, -BattleScene_GetParticipantHeight(ap) * 0.2f);
        BattleCamera_CaptureModelOrbit(ap, arg0);
        sBattleScene.scene->phaseStep += 1;
    }
}

/**
 * Intro camera shot, a variant of func_82120418 (and func_8212054C). After clearing the
 * camera offset vectors it takes the active Pokemon selected by scene->unk_2C and, unless
 * BattleScene_SkipUnavailableBRollShot handles it, saves the camera's vertical field of view in
 * scene->unk_60 and widens it to 100.0f; enters state row 0x10; stores the Pokemon's default
 * anchor position in scene->unk_D0 and the camera distance (factor 4.0f, base 300.0f) in
 * scene->unk_74; aims the camera at the anchor with its facing angle and puts the eye at
 * the same anchor, again using the facing angle, with the s16 at scene offset 0x6E set to
 * -0x1554 (that store is made inside the argument list, as in the retail code); and
 * finally advances scene->unk_20. The meaning of the s16 at 0x6E is not established
 * (it lies inside the unk_6C field of the BattleScene header).
 */
void func_821202AC(CameraNode* arg0) {
    ActivePokemon* ap;

    BattleScene_ClearCameraOffsetVectors();
    ap = sActivePokemon[sBattleScene.scene->actingSide];
    if (BattleScene_SkipUnavailableBRollShot(ap, arg0) == 0) {
        sBattleScene.scene->verticalFieldOfView = arg0->perspective.verticalFieldOfView;
        arg0->perspective.verticalFieldOfView = 100.0f;
        BattleScene_EnterStateRow(ap, 0x10);
        BattleAnim_GetOwnerDefaultAnchorPosition(ap, &sBattleScene.scene->unk_D0);
        sBattleScene.scene->unk_74 = BattleScene_ScaleCameraDistance(ap, 4.0f, 300.0f);
        BattleScene_SetCameraAtFromAnchor(ap, arg0, sBattleScene.scene->unk_D0, 0, BattleScene_GetParticipantFacingAngle(ap), 0.0f, 0);
        BattleScene_SetCameraEyeFromPosition(arg0, sBattleScene.scene->unk_D0, (M2C_FIELD(sBattleScene.scene, s16*, 0x6E) = -0x1554), BattleScene_GetParticipantFacingAngle(ap), sBattleScene.scene->unk_74, 0.0f);
        sBattleScene.scene->phaseStep += 1;
    }
}

void func_82120418(CameraNode* arg0) {
    ActivePokemon* ap;

    BattleScene_ClearCameraOffsetVectors();
    ap = sActivePokemon[sBattleScene.scene->actingSide];
    if (BattleScene_SkipUnavailableBRollShot(ap, arg0) == 0) {
        BattleScene_EnterStateRow(ap, 0x10);
        BattleAnim_GetOwnerDefaultAnchorPosition(ap, &sBattleScene.scene->unk_D0);
        sBattleScene.scene->unk_74 = BattleScene_ScaleCameraDistance(ap, 8.0f, 300.0f);
        BattleScene_SetCameraAtFromAnchor(ap, arg0, sBattleScene.scene->unk_D0, 0, BattleScene_GetParticipantFacingAngle(ap), 0.0f, 0);
        BattleScene_SetCameraEyeFromPosition(arg0, sBattleScene.scene->unk_D0, 0, BattleScene_GetParticipantFacingAngle(ap), sBattleScene.scene->unk_74, 0.0f);
        sBattleScene.scene->phaseStep += 1;
    }
}

void BattleCamera_CaptureModelOrbit(ActivePokemon*, CameraNode*);
void func_8212054C(CameraNode* arg0) {
    ActivePokemon* ap;

    BattleScene_ClearCameraOffsetVectors();
    ap = sActivePokemon[sBattleScene.scene->actingSide];
    if (BattleScene_SkipUnavailableBRollShot(ap, arg0) == 0) {
        BattleScene_EnterStateRow(ap, 0x10);
        BattleAnim_GetOwnerDefaultAnchorPosition(ap, &sBattleScene.scene->unk_D0);
        sBattleScene.scene->unk_74 = BattleScene_ScaleCameraDistance(ap, 3.5f, 300.0f);
        BattleScene_SetCameraAtFromAnchor(ap, arg0, sBattleScene.scene->unk_D0, 0, BattleScene_GetParticipantFacingAngle(ap), 0.0f, 0);
        BattleScene_SetCameraEyeFromPosition(arg0, sBattleScene.scene->unk_D0, 0, BattleScene_GetParticipantFacingAngle(ap), sBattleScene.scene->unk_74, 0.0f);
        BattleCamera_CaptureModelOrbit(ap, arg0);
        sBattleScene.scene->phaseStep += 1;
    }
}

void func_8212054C(CameraNode*);
s32 func_8212068C(UNUSED s32 arg0, CameraNode* arg1) {
    ActivePokemon* p = sActivePokemon[sBattleScene.scene->actingSide];

    if ((p->displayObject.objectType == 0x71) || (p->displayObject.objectType == 0x79)) {
        sBattleScene.scene->phaseStep = 0x16;
        func_8212054C(arg1);
        return 1;
    }
    return 0;
}

typedef struct BRollShotSequence {
    s32 shots[12];
} BRollShotSequence;
extern BRollShotSequence D_8218B240;
extern f32 D_FLT_82189350[][4];
void func_82121434(CameraNode*);
void func_8212188C(void);
void func_82121C3C(CameraNode*);
void func_82108C0C(ActivePokemon*);
s32 func_8210C020(s32);
void func_8211F6B8(CameraNode*);
void func_8211F84C(CameraNode*);
void func_8211FB54(CameraNode*);
void func_8211FCC8(CameraNode*);
void func_8211FF08(CameraNode*);
void func_82120134(CameraNode*);
void func_8211FA34(CameraNode*);
void func_8211FAC4(CameraNode*);
void func_821202AC(CameraNode*);
void func_82120418(CameraNode*);

/**
 * Seen in play (2026-11-13) while the command menu waits for input (scene mode 1, phase 0) it
 * cycles the idle B-roll shots: bRollShotIndex went 9, 10, 11, then wrapped to 1, and phaseStep
 * went 7, 9, 3, 7. Stadium 1 names the same function BattleScene_SelectNextBRollCameraShot.
 */
void BattleScene_SelectNextBRollCameraShot(CameraNode* arg0) {
    ActivePokemon* p;
    ActivePokemonState* st;
    BRollShotSequence seq = D_8218B240;

    if (sBattleScene.scene->mode == 9) {
        func_82121434(arg0);
        return;
    }
    if (seq.shots[sBattleScene.scene->bRollShotIndex] == 0xFF) {
        sBattleScene.scene->bRollShotIndex = 0;
    }
    sBattleScene.scene->phaseStep = seq.shots[sBattleScene.scene->bRollShotIndex];
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
    if ((sBattleScene.scene->phaseStep == 5) || (sBattleScene.scene->phaseStep == 0xB)) {
        p = sActivePokemon[sBattleScene.scene->actingSide];
        st = &p->state;
        if (st) {}  // karodo
        if ((st->flags & 0x200) || (p->displayObject.objectType == 0x8E)) {
            if (func_8210C020(0x64) & 1) {
                sBattleScene.scene->phaseStep = 0x10;
                func_821202AC(arg0);
            } else {
                sBattleScene.scene->phaseStep = 0x12;
                func_821202AC(arg0);
            }
        } else if ((func_8212068C(p, arg0) == 0) &&
                   (D_FLT_82189350[sActivePokemon[sBattleScene.scene->actingSide]->displayObject.objectType][0] <= 27.0f)) {
            sBattleScene.scene->phaseStep = 0x14;
            func_82120418(arg0);
        }
    }
    func_82121C3C(arg0);
}

extern const f64 D_DBL_821960A0;
void BattleScene_BRollCameraUpdateArenaOrbit(CameraNode* arg0) {
    if (BattleScene_ApproachCameraRotationY(arg0, 0xB6, 0x78DC) != 0) {
        BattleScene_SelectNextBRollCameraShot(arg0);
    } else {
        arg0->view.eyePosition.z *= 0.6;
    }
}

/**
 * Seen in play (2026-11-13) B-roll step 3 at the command menu: each frame rotationY (scene+0x5A)
 * fell by 0xB6 while rotationX stayed 0x1A4E and the distance 1000, so the eye circled the look-at
 * point (0, 100, 0) at a fixed height (eye x 0 to -776, z 800 to 193 over 80 frames).
 */
void BattleScene_BRollCameraUpdateRotatingArenaOverview(CameraNode* arg0) {
    if (BattleScene_ApproachCameraRotationY(arg0, 0xB6, 0x78DC) != 0) {
        BattleScene_SelectNextBRollCameraShot(arg0);
    }
}

extern f32 D_FLT_82189358[][4];
void BattleScene_SelectNextBRollCameraShot(CameraNode*);
/*
 * func_82120AC8
 *
 * Eases the scene float at +0x8C towards 0.1 (speed 0.02) and then eases the
 * camera node's float at +0xB8 towards a goal made of two parts: a per-object
 * table value, D_FLT_82189358[objectType][0] for the active Pokemon at index
 * sBattleScene.scene->unk_2C (D_FLT_82189358 is the table at 0x82189350 shifted
 * by 8, i.e. column 2 of D_FLT_82189350, the table func_82135BE4 in
 * battle_engine_343BA0_4.c reads column 0 of), plus the scene float at +0xC4.  The speed is the scene float at
 * +0x8C.  When the camera float is still below that goal plus 0.5 it calls
 * BattleScene_SelectNextBRollCameraShot(arg0).  What the floats mean is not established here.
 * Note: the sums are written with the scene float first, which is what
 * reproduces the retail FPU register allocation.
 */
void func_82120AC8(CameraNode* arg0) {
    BattleAnim_ApproachF(&M2C_FIELD(sBattleScene.scene, f32*, 0x8C), 0.1f, 0.02f);
    BattleAnim_ApproachF(&M2C_FIELD(arg0, f32*, 0xB8),
                         M2C_FIELD(sBattleScene.scene, f32*, 0xC4) + D_FLT_82189358[M2C_FIELD(sActivePokemon[sBattleScene.scene->actingSide], s16*, 0x1A)][0],
                         M2C_FIELD(sBattleScene.scene, f32*, 0x8C));
    if (M2C_FIELD(arg0, f32*, 0xB8) < (M2C_FIELD(sBattleScene.scene, f32*, 0xC4) + D_FLT_82189358[M2C_FIELD(sActivePokemon[sBattleScene.scene->actingSide], s16*, 0x1A)][0] + 0.5f)) {
        BattleScene_SelectNextBRollCameraShot(arg0);
    }
}

void BattleScene_SelectNextBRollCameraShot(CameraNode*);
void func_82122FD8(CameraNode*, ActivePokemon*);
s32 func_821217DC(M2C_UNK);
/*
 * func_82120BB8
 *
 * Same logic as BattleScene_BRollCameraUpdatePresetHold, but the Pokemon is fetched into a local only
 * after the early-out test.  It reads the state of the active Pokemon at index
 * sBattleScene.scene->unk_2C.  If its state byte unk_2D is 0x10 or bit 0x4000
 * is set in its state flags, it calls BattleScene_SelectNextBRollCameraShot(arg0).  Otherwise it calls
 * func_82122FD8(arg0, that Pokemon) and, when func_821217DC(0x3C) returns
 * non-zero, BattleScene_SelectNextBRollCameraShot(arg0).  What the state byte and the flags mean is
 * not established here.
 * Note: m2c passed the Pokemon pointer to the first call; the ROM leaves a0
 * untouched at the BattleScene_SelectNextBRollCameraShot calls, so arg0 is passed there.  Declaring
 * the Pokemon local after the state pointer, and assigning it only after the
 * early return, is what reproduces the register allocation (found with the
 * decomp-permuter).
 */
void func_82120BB8(CameraNode* arg0) {
    ActivePokemon* pokemon;
    ActivePokemonState* st = &sActivePokemon[sBattleScene.scene->actingSide]->state;

    if ((st->unk_2D == 0x10) || (st->flags & 0x4000)) {
        BattleScene_SelectNextBRollCameraShot(arg0);
        return;
    }
    pokemon = sActivePokemon[sBattleScene.scene->actingSide];
    func_82122FD8(arg0, pokemon);
    if (func_821217DC(0x3C) != 0) {
        BattleScene_SelectNextBRollCameraShot(arg0);
    }
}

extern f32 D_FLT_82189358[][4];
void BattleScene_SelectNextBRollCameraShot(CameraNode*);
/*
 * func_82120C44
 *
 * Variant of func_82120AC8 (see there for the floats involved) with a goal of
 * D_FLT_82189358[objectType][0] + 1.5 * (scene float +0xC4).  Same early-out as
 * func_82120BB8/BattleScene_BRollCameraUpdatePresetHold: when the active Pokemon at index
 * sBattleScene.scene->unk_2C has state byte unk_2D == 0x10 or state flag bit
 * 0x4000 it just calls BattleScene_SelectNextBRollCameraShot(arg0).  Otherwise it eases the scene float
 * at +0x8C towards 0.1 (speed 0.02), eases the camera node's float at +0xB8
 * towards the goal with the scene float +0x8C as the speed, and calls
 * BattleScene_SelectNextBRollCameraShot(arg0) once the goal minus 0.5 is below the camera float.
 * Note: operand order of the first sum matches the ROM's FPU register use.
 */
void func_82120C44(CameraNode* arg0) {
    ActivePokemonState* st = &sActivePokemon[sBattleScene.scene->actingSide]->state;

    if ((st->unk_2D == 0x10) || (st->flags & 0x4000)) {
        BattleScene_SelectNextBRollCameraShot(arg0);
        return;
    }
    BattleAnim_ApproachF(&M2C_FIELD(sBattleScene.scene, f32*, 0x8C), 0.1f, 0.02f);
    BattleAnim_ApproachF(&M2C_FIELD(arg0, f32*, 0xB8),
                         M2C_FIELD(sBattleScene.scene, f32*, 0xC4) * 1.5f + D_FLT_82189358[M2C_FIELD(sActivePokemon[sBattleScene.scene->actingSide], s16*, 0x1A)][0],
                         M2C_FIELD(sBattleScene.scene, f32*, 0x8C));
    if (((D_FLT_82189358[M2C_FIELD(sActivePokemon[sBattleScene.scene->actingSide], s16*, 0x1A)][0] + M2C_FIELD(sBattleScene.scene, f32*, 0xC4) * 1.5f) - 0.5f) < M2C_FIELD(arg0, f32*, 0xB8)) {
        BattleScene_SelectNextBRollCameraShot(arg0);
    }
}

void BattleScene_SelectNextBRollCameraShot(CameraNode*);
s32 func_82135734(CameraNode*, ActivePokemon*);
s32 func_821217DC(M2C_UNK);
void func_82120D94(CameraNode* arg0) {
    ActivePokemonState* st = &sActivePokemon[sBattleScene.scene->actingSide]->state;

    if ((st->unk_2D == 0x10) || (st->flags & 0x4000)) {
        BattleScene_SelectNextBRollCameraShot(arg0);
    } else if (sBattleScene.scene->mode == 9) {
        if (func_82135734(arg0, sActivePokemon[sBattleScene.scene->actingSide]) != 0) {
            BattleScene_SelectNextBRollCameraShot(arg0);
        }
    } else if ((func_821217DC(0x5A) != 0) || (func_82135734(arg0, sActivePokemon[sBattleScene.scene->actingSide]) != 0)) {
        BattleScene_SelectNextBRollCameraShot(arg0);
    }
}

void func_82122628(s32, Vec3f, s32, s32, f32, f32);
/*
 * func_82120E70
 *
 * Same early-out as func_82120BB8: when the active Pokemon at index
 * sBattleScene.scene->unk_2C has state byte unk_2D == 0x10 or state flag bit
 * 0x4000 it just calls BattleScene_SelectNextBRollCameraShot(arg0).  Otherwise it steps the scene
 * halfword at +0x6E towards 0x149E (step 0x2D) with BattleAnim_StepToS16,
 * calls func_82122628 with arg0, the scene's Vec3f at +0xC0, that halfword,
 * the Pokemon's facing angle (BattleScene_GetParticipantFacingAngle), the scene
 * float unk_74 and 0.0, and eases the camera node's float at +0x2C towards the
 * scene float unk_60 (speed 0.08).  When the camera float is below unk_60 + 1.0
 * it snaps the float to unk_60 and calls BattleScene_SelectNextBRollCameraShot(arg0).  What the fields
 * mean is not established here.
 */
void func_82120E70(CameraNode* arg0) {
    ActivePokemonState* st = &sActivePokemon[sBattleScene.scene->actingSide]->state;
    f32 temp_f0;

    if ((st->unk_2D == 0x10) || (st->flags & 0x4000)) {
        BattleScene_SelectNextBRollCameraShot(arg0);
        return;
    }
    BattleAnim_StepToS16(&M2C_FIELD(sBattleScene.scene, s16*, 0x6E), 0x149E, 0x2D);
    func_82122628((s32)arg0, sBattleScene.scene->unk_D0, M2C_FIELD(sBattleScene.scene, s16*, 0x6E),
                  BattleScene_GetParticipantFacingAngle(sActivePokemon[sBattleScene.scene->actingSide]), sBattleScene.scene->unk_74, 0.0f);
    BattleAnim_ApproachF(&M2C_FIELD(arg0, f32*, 0x2C), sBattleScene.scene->verticalFieldOfView, 0.08f);
    temp_f0 = sBattleScene.scene->verticalFieldOfView;
    if (M2C_FIELD(arg0, f32*, 0x2C) < (temp_f0 + 1.0f)) {
        M2C_FIELD(arg0, f32*, 0x2C) = temp_f0;
        BattleScene_SelectNextBRollCameraShot(arg0);
    }
}

extern f32 D_FLT_821960A8;
f32 func_82121750(ActivePokemon*, f32, f32);
/*
 * func_82120FB0
 *
 * Sibling of func_82120E70, with the same early-out: when the active Pokemon
 * at index sBattleScene.scene->unk_2C has state byte unk_2D == 0x10 or state
 * flag bit 0x4000 it just calls BattleScene_SelectNextBRollCameraShot(arg0).  Otherwise it asks
 * func_82121750(Pokemon, 2.5, 300.0) for a float, eases the scene float unk_74
 * towards it (speed 0.08), calls func_82122628 with arg0, the scene's Vec3f at
 * +0xC0, 0, the Pokemon's facing angle, unk_74 and 0.0, and calls
 * BattleScene_SelectNextBRollCameraShot(arg0) while unk_74 is still below that float plus
 * 0.2f.  What the fields and func_82121750 mean is not established
 * here.
 */
void func_82120FB0(CameraNode* arg0) {
    ActivePokemonState* st = &sActivePokemon[sBattleScene.scene->actingSide]->state;
    f32 temp_f0;

    if ((st->unk_2D == 0x10) || (st->flags & 0x4000)) {
        BattleScene_SelectNextBRollCameraShot(arg0);
        return;
    }
    temp_f0 = func_82121750(sActivePokemon[sBattleScene.scene->actingSide], 2.5f, 300.0f);
    BattleAnim_ApproachF(&sBattleScene.scene->unk_74, temp_f0, 0.08f);
    func_82122628((s32)arg0, sBattleScene.scene->unk_D0, 0,
                  BattleScene_GetParticipantFacingAngle(sActivePokemon[sBattleScene.scene->actingSide]), sBattleScene.scene->unk_74, 0.0f);
    if (sBattleScene.scene->unk_74 < (temp_f0 + 0.2f)) {
        BattleScene_SelectNextBRollCameraShot(arg0);
    }
}

void func_82122A7C(CameraNode*, ActivePokemon*);

/**
 * BattleScene_BRollCameraUpdatePresetHold
 *
 * Reads the state of the active Pokemon at index sBattleScene.scene->unk_2C,
 * the same entry func_82120D94 and func_8212116C use. If its state byte
 * unk_2D is 0x10 or bit 0x4000 is set in its state flags, it calls
 * BattleScene_SelectNextBRollCameraShot(arg0). Otherwise it calls func_82122A7C(arg0, that Pokemon)
 * and, when func_821217DC(0x3C) returns non-zero, BattleScene_SelectNextBRollCameraShot(arg0). What
 * the state byte and the flags mean is not established here.
 * Note: m2c passed the Pokemon pointer to the first two calls. The ROM leaves
 * a0 untouched at the BattleScene_SelectNextBRollCameraShot call, so arg0 is passed there; at the
 * func_82122A7C call the Pokemon is the second argument (the form that
 * matches, with the Pokemon re-read exactly as func_82120D94 does).
 * Not reached in play (2026-11-13): no move in the 165-move battle sweep called it (each move used
 * once, from the command menu to the end of its turn).
 * @unverified Name was previously used only by callers of this address; the definition was still func_.
 */
void BattleScene_BRollCameraUpdatePresetHold(CameraNode* arg0) {
    ActivePokemonState* st = &sActivePokemon[sBattleScene.scene->actingSide]->state;

    if ((st->unk_2D == 0x10) || (st->flags & 0x4000)) {
        BattleScene_SelectNextBRollCameraShot(arg0);
        return;
    }
    func_82122A7C(arg0, sActivePokemon[sBattleScene.scene->actingSide]);
    if (func_821217DC(0x3C) != 0) {
        BattleScene_SelectNextBRollCameraShot(arg0);
    }
}

s32 func_82135734(CameraNode*, ActivePokemon*);
void func_8212188C(void);
void func_8212116C(CameraNode* arg0) {
    func_82135734(arg0, sActivePokemon[sBattleScene.scene->actingSide]);
    if (M2C_FIELD(sBattleScene.scene, s8*, 1) == 0x10) {
        func_8212188C();
        sBattleScene.scene->phaseStep = 0x1B;
    }
}

s32 func_821217DC(M2C_UNK);                         /* extern */
extern s8 *D_8219A5A0;

void func_821211D4(s32 arg0) {
    if (func_821217DC(0x1B8) != 0) {
        M2C_FIELD(D_8219A5A0, s32 *, 0x20) = 0x1D;
    }
}

/*
 * func_8212120C
 *
 * Sets the camera's clip planes to 20.0f (near) and 4000.0f (far), the same
 * call that BattleScene_InitializeBattlePresentation makes.  Then, if any of
 * the bits in 0xE03F is set in the halfword at offset 8 of the structure that
 * D_800603C0 points to, calls Audio_FadeCategoriesAndStreams(1) and stores 3 at offset 0x40 of
 * the structure that D_8219A5A0 points to.  What those two structures are is
 * not established from this function alone.
 */
extern u8* D_800603C0;
void Audio_FadeCategoriesAndStreams(s32 arg0);

void func_8212120C(CameraNode* arg0) {
    func_82121D78(arg0, 20.0f, 4000.0f);
    if (*(u16*)(D_800603C0 + 8) & 0xE03F) {
        Audio_FadeCategoriesAndStreams(1);
        M2C_FIELD(D_8219A5A0, s32 *, 0x40) = 3;
    }
}
