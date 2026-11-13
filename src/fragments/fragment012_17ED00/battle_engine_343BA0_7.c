/* Stadium Zero fragment012_17ED00. */
/* C ported from the Stadium 1 decomp: src/fragments/battle_engine/battle_engine_343BA0.c. */

#include "fragments/battle_engine/battle_engine.h"
#include "gallery.h"
#include "gfx_buffer.h"
#include "math.h"
#include "math_util.h"
extern u8* sBattleAnimAssetPointers[256];
extern s16 sBattleAnimResourceList[0x10];
extern arg1_func_80019420* sBattleAnimResourceTablePointers[40];
extern s16 D_8219CAC0;
extern s16 D_8219CAC2;
extern Mtx D_8219CAC8;
extern s16 D_8219CB08;
extern s16 D_8219CB0A;
extern s16 D_8219CB0C;
extern s16 D_8219CB0E;
extern s16 D_8219CB10;
extern s16 D_8219CB12;
extern s16 D_8219CB14;
extern s16 D_8219CB16;
extern s16 D_8219CB18;
extern s16 D_8219CB1A;
extern const char D_821978C8[];

void Battle_GetTertiaryOwnerBonePositionUnused(Vec3f* arg0);
void BattleAnim_EffectSecondaryOwnerAnchorPosition(Vec3f* arg0);
void BattleAnim_EffectTertiaryOwnerBonePosition(Vec3f* arg0);
void BattleAnim_EffectSecondaryOwnerBonePosition(Vec3f* arg0);
f32 BattleAnim_EffectTertiaryOwnerModelScale(void);
f32 BattleAnim_EffectSecondaryOwnerModelScale(void);
void BattleAnim_ResetSharedEffectMatrix(void);
void BattleAnim_SetupStatRaiseRibbon(void);
s32 BattleAnim_RunStatRaiseRibbon(void);
void BattleAnim_DrawStatRaiseRibbon(void);
void BattleAnim_SetupStatLowerRibbon(void);
s32 BattleAnim_RunStatLowerRibbon(void);
void BattleAnim_DrawStatLowerRibbon(void);
void BattleAnim_EndEffect19RibbonMesh_Init(void);
s32 BattleAnim_EndEffect19RibbonMesh_Update(void);
void BattleAnim_EndEffect19RibbonMesh_Draw(void);
void BattleAnim_SetupHazeUseRibbonMesh(void);
s32 BattleAnim_RunHazeUseRibbonMesh(void);
void BattleAnim_DrawHazeUseRibbonMesh(void);
void BattleAnim_SetupSurfUseTerrainGrid(void);
s32 BattleAnim_RunSurfUseTerrainGrid(void);
void BattleAnim_DrawSurfUseTerrainGrid(void);

void Battle_GetTertiaryOwnerBonePositionUnused(Vec3f* arg0) {
    BattleAnim_GetTertiaryOwnerBonePosition(arg0);
}

void BattleAnim_EffectSecondaryOwnerAnchorPosition(Vec3f* arg0) {
    BattleAnim_GetSecondaryOwnerAnchorPosition(arg0);
}

void BattleAnim_EffectTertiaryOwnerBonePosition(Vec3f* arg0) {
    BattleAnim_GetTertiaryOwnerBonePosition(arg0);
}

void BattleAnim_EffectSecondaryOwnerBonePosition(Vec3f* arg0) {
    BattleAnim_GetSecondaryOwnerBonePosition(arg0);
}

f32 BattleAnim_EffectTertiaryOwnerModelScale(void) {
    return BattleAnim_GetTertiaryOwnerModelScale();
}

f32 BattleAnim_EffectSecondaryOwnerModelScale(void) {
    return BattleAnim_GetSecondaryOwnerModelScale();
}

extern char D_82197890[];
void BattleAnim_CalcVectorAtToDm(f32* arg0, f32* arg1, f32* arg2, f32* arg3, f32* arg4, f32* arg5) {
    Vec3f sp4C;
    Vec3f sp40;
    f32 sp3C;
    f32 sp38;
    f32 sp34;
    UNUSED s32 pad[3]; // FAKE: stack padding
    f32 sp24;
    f32 sp20;
    f32 sp1C;

    BattleAnim_EffectSecondaryOwnerAnchorPosition(&sp4C);
    BattleAnim_EffectTertiaryOwnerBonePosition(&sp40);

    sp3C = sp4C.x;
    sp38 = sp4C.y;
    sp34 = sp4C.z;

    sp24 = sp40.x - sp4C.x;
    sp20 = sp40.y - sp4C.y;
    sp1C = sp40.z - sp4C.z;

    if (sp24 == 0.0f && sp20 == 0.0f && sp1C == 0.0f) {
        rmonPrintf(D_82197890);
    }

    Vec3f_NormalizeComponents(&sp24, &sp20, &sp1C);

    *arg0 = sp3C;
    *arg1 = sp38;
    *arg2 = sp34;
    *arg3 = sp24;
    *arg4 = sp20;
    *arg5 = sp1C;
}

void BattleAnim_ResetSharedEffectMatrix(void) {
    guRotateRPY(&D_8219CAC8, 0.0f, 0.0f, 0.0f);
}

/**
 * Resets the shared effect matrix and spawns a rising stat ribbon (direction 0) at the effect
 * owner's bone, scaled by its model.
 * Seen in play (2026-11-13) ran for Swords Dance, Mist, Growth, Meditate, Agility, Double Team,
 * Harden, Minimize, Withdraw, Defense Curl, Barrier, Amnesia, Acid Armor and Sharpen (every self
 * stat raise, plus Mist). For Swords Dance the ribbon rose around the user.
 */
void BattleAnim_SetupStatRaiseRibbon(void) {
    Vec3f sp24;
    f32 sp20;

    BattleAnim_ResetSharedEffectMatrix();
    BattleAnim_EffectSecondaryOwnerBonePosition(&sp24);
    sp20 = BattleAnim_EffectSecondaryOwnerModelScale();
    StatRibbon_Init();
    StatRibbon_Spawn(sp24.x, sp24.y, sp24.z, 40.0f, sp20, 0);
}

/**
 * Part of the stat-raise ribbon (see BattleAnim_SetupStatRaiseRibbon).
 * Seen in play (2026-11-13) (unattended Free Battle in which every Pokémon knows only Metronome, 40
 * turns): ran.
 * @unverified Named after the ribbon seen in play; this function itself was not traced.
 */
s32 BattleAnim_RunStatRaiseRibbon(void) {
    return StatRibbon_UpdatePool();
}

/**
 * Part of the stat-raise ribbon (see BattleAnim_SetupStatRaiseRibbon).
 * Seen in play (2026-11-13) (unattended Free Battle in which every Pokémon knows only Metronome, 40
 * turns): ran.
 * @unverified Named after the ribbon seen in play; this function itself was not traced.
 */
void BattleAnim_DrawStatRaiseRibbon(void) {
    gSPMatrix(gDisplayListHead++, &D_8219CAC8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gDisplayListHead = StatRibbon_DrawPool(gDisplayListHead);
}

/**
 * Resets the shared effect matrix and spawns a falling stat ribbon (direction 1) at the effect
 * owner's bone, scaled by the tertiary owner's model.
 * Seen in play (2026-11-13) ran for Sand Attack, Tail Whip, Leer, Growl, Screech, Smokescreen,
 * Kinesis and Flash (every move that lowers the target's stat). For Growl the curtain came down in
 * front of the target.
 */
void BattleAnim_SetupStatLowerRibbon(void) {
    Vec3f sp24;
    f32 sp20;

    BattleAnim_ResetSharedEffectMatrix();
    BattleAnim_EffectSecondaryOwnerBonePosition(&sp24);
    sp20 = BattleAnim_EffectTertiaryOwnerModelScale();
    StatRibbon_Init();
    StatRibbon_Spawn(sp24.x, sp24.y, sp24.z, 40.0f, sp20, 1);
}

s32 BattleAnim_RunStatLowerRibbon(void) {
    return StatRibbon_UpdatePool();
}

void BattleAnim_DrawStatLowerRibbon(void) {
    gSPMatrix(gDisplayListHead++, &D_8219CAC8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gDisplayListHead = StatRibbon_DrawPool(gDisplayListHead);
}

void BattleAnim_EndEffect19RibbonMesh_Init(void) {
    Vec3f sp24;
    f32 sp20;

    BattleAnim_ResetSharedEffectMatrix();
    BattleAnim_EffectSecondaryOwnerBonePosition(&sp24);
    sp20 = BattleAnim_EffectTertiaryOwnerModelScale();
    StatRibbon_Init();
    StatRibbon_Spawn(sp24.x, sp24.y, sp24.z, 40.0f, sp20, 0);
    StatRibbon_Spawn(sp24.x, sp24.y, sp24.z, 38.0f, sp20, 1);
}

s32 BattleAnim_EndEffect19RibbonMesh_Update(void) {
    return StatRibbon_UpdatePool();
}

void BattleAnim_EndEffect19RibbonMesh_Draw(void) {
    gSPMatrix(gDisplayListHead++, &D_8219CAC8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gDisplayListHead = StatRibbon_DrawPool(gDisplayListHead);
}

/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Haze.
 */
void BattleAnim_SetupHazeUseRibbonMesh(void) {
    Vec3f sp24;
    f32 sp20;

    BattleAnim_ResetSharedEffectMatrix();
    BattleAnim_EffectSecondaryOwnerBonePosition(&sp24);
    sp20 = BattleAnim_EffectSecondaryOwnerModelScale();
    StatRibbon_Init();
    StatRibbon_Spawn(sp24.x, sp24.y, sp24.z, 40.0f, sp20, 0);
    StatRibbon_Spawn(sp24.x, sp24.y, sp24.z, 38.0f, sp20, 1);
}

/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Haze.
 */
s32 BattleAnim_RunHazeUseRibbonMesh(void) {
    return StatRibbon_UpdatePool();
}

/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Haze.
 */
void BattleAnim_DrawHazeUseRibbonMesh(void) {
    gSPMatrix(gDisplayListHead++, &D_8219CAC8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gDisplayListHead = StatRibbon_DrawPool(gDisplayListHead);
}

/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Surf.
 */
void BattleAnim_SetupSurfUseTerrainGrid(void) {
    Vec3f sp1C;

    BattleAnim_EffectSecondaryOwnerAnchorPosition(&sp1C);
    BattleAnim_ResetSharedEffectMatrix();

    if (sp1C.x < 0.0) {
        SurfTerrainGrid_Init(1, 0, 0x4650);
    } else {
        SurfTerrainGrid_Init(-1, 0, 0x4650);
    }
}

/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Surf.
 */
s32 BattleAnim_RunSurfUseTerrainGrid(void) {
    return SurfTerrainGrid_Update();
}

/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Surf.
 */
void BattleAnim_DrawSurfUseTerrainGrid(void) {
    gSPMatrix(gDisplayListHead++, &D_8219CAC8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gDisplayListHead = SurfTerrainGrid_Draw(gDisplayListHead);
}
