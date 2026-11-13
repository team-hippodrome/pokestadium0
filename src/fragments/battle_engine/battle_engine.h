#ifndef _FRAGMENT62_H_
#define _FRAGMENT62_H_

#include "global.h"
#include "src/game_state.h"
#include "src/3D140.h"
#include "src/gfx_rect.h"
#include "src/stage_loader.h"
#include "src/fragments/demo_scenes/demo_scenes.h"
#include "src/fragments/particle_math/particle_math.h"

typedef s32 (*func_D_84390300)(void);
typedef void (*func_D_84390320)(void);

typedef struct unk_D_84390010_654_09C {
    /* 0x00 */ s32 unk00[4];
} unk_D_84390010_654_09C; // size = 0x10

typedef struct unk_D_84390010_654_0AC {
    /* 0x00 */ char unk00[0x10];
} unk_D_84390010_654_0AC; // size = 0x10

typedef struct unk_D_84390010_168 {
    /* 0x000 */ DisplayObject displayObject;
    /* 0x168 */ char unk168[0x1];
    /* 0x169 */ u8 minimized;
    /* 0x16A */ s16 unk_16A;
    /* 0x16C */ s16 unk_16C;
    /* 0x16E */ char unk16E[0x2];
} PokemonAfterimage; // size = 0x170

typedef struct ActivePokemonState {
    /* 0x00 */ char unk00[0x4];
    /* 0x04 */ u32 selectedCommand;
    /* 0x08 */ s32 rosterIndex;
    /* 0x0C */ s32 selectedMoveIndex;
    /* 0x10 */ u32 selectedCommandOption;
    /* 0x14 */ s32 moveIndex;
    /* 0x18 */ u32 actionChosen;
    /* 0x1C */ u8 showingCommandOptions;
    /* 0x1E */ u16 actionDelayTimer;
    /* 0x20 */ char unk20[0x8];
    /* 0x28 */ u16 unk_28;
    /* 0x2A */ u8 moveSelectionLocked;
    /* 0x2B */ u8 teamMemberIndex;
    /* 0x2C */ u8 ownerTeamMemberIndex;
    /* 0x2D */ u8 replacementState;
    /* 0x2E */ u8 unk_2D;
    /* 0x2F */ u8 alpha;
    /* 0x30 */ u8 unk_2F;
    /* 0x32 */ u16 unk_30;
    /* 0x34 */ char unk32[0x2];
    /* 0x36 */ u16 flags;
    /* 0x38 */ u16 unk_36;
    /* 0x3A */ BattleMonRuntime runtime;
    /* 0xA0 */ unk_D_84390010_654_09C unk_9C;
    /* 0xB0 */ unk_D_84390010_654_0AC unk_AC;
    /* 0xC0 */ s16 model;
    /* 0xC2 */ s16 unk_BE;
    /* 0xC4 */ char unkC0[1];
    /* 0xC5 */ u8 moveSlotIllegality[4];
    /* 0xCC */ Controller* controller;
} ActivePokemonState; // size = 0xD0

typedef struct ThumbnailState {
    /* 0x000 */ DisplayObject displayObject;
    /* 0x168 */ CameraNode* camera;
    /* 0x16C */ s32 tagTeam;
    /* 0x170 */ char unk170_zero[0x4];
    /* 0x174 */ s32 showing;
    /* 0x178 */ char unk174[0x4];
    /* 0x17C */ s32 side;
    /* 0x180 */ s32 idleAnimation;
    /* 0x184 */ s32 idleTimer;
    /* 0x188 */ s16 rotationX;
    /* 0x18A */ s16 rotationY;
    /* 0x18C */ f32 x;
    /* 0x190 */ s32 status;
    /* 0x194 */ f32 z;
    /* 0x198 */ f32 y;
    /* 0x19C */ char unk198[0x4];
} ThumbnailState; // size = 0x1A0

typedef struct MonCaptionState {
    /* 0x00 */ s32 active;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s8 unk_08[4];
    /* 0x0C */ char unk0C[0x3C];
    /* 0x48 */ s8 unk_48[4];
    /* 0x4C */ char unk4C[0x3C];
} MonCaptionState; // size = 0x88

typedef struct SpeciesLearnsetBuffer {
    /* 0x00 */ u8 unk_00[10];
    /* 0x0A */ u8 unk_0A[4];
    /* 0x0E */ char unk0E[0x12];
} SpeciesLearnsetBuffer; // size = 0x20

typedef struct SwayLayoutConfig {
    /* 0x00 */ Vec3f frontCameraShotOffset;
    /* 0x0C */ Vec3f backCameraShotOffset;
    /* 0x18 */ u8 unk_18;
    /* 0x19 */ u8 unk_19;
    /* 0x1A */ u8 unk_1A;
    /* 0x1B */ u8 unk_1B;
    /* 0x1C */ char unk1C[4];
} SwayLayoutConfig; // size = 0x20

typedef struct SwayState {
    /* 0x00 */ Vec3f unk_00;
    /* 0x0C */ Vec3f rotation;
    /* 0x18 */ Vec3f unk_18;
    /* 0x24 */ char unk24[0x18];
} SwayState; // size = 0x3C

typedef struct ActivePokemon {
    /* 0x000 */ DisplayObject displayObject;
    /* 0x168 */ PokemonAfterimage afterimages[3];
    /* 0x5B8 */ SwayState modelTransform;
    /* 0x5F4 */ f32 y;
    /* 0x5F8 */ f32 rotationZ;
    /* 0x5FC */ f32 oscillationAmplitude;
    /* 0x600 */ s16 oscillationVelocityEasePhase;
    /* 0x602 */ s16 oscillationPhase;
    /* 0x604 */ s16 oscillationAngularVelocity;
    /* 0x608 */ s32 doubleTeamTimer;
    /* 0x60C */ s32 facingDirection;
    /* 0x610 */ s32 modelTransformId;
    /* 0x614 */ s32 modelTransformTimer;
    /* 0x618 */ char unk4BC[0x4];
    /* 0x61C */ s32 animationState;
    /* 0x620 */ s32 animationTimer;
    /* 0x624 */ DisplayObject pokeBall;
    /* 0x78C */ ActivePokemonState state;
    /* 0x85C */ BattleSessionTeams* sessionTeams;
    /* 0x860 */ TeamRoster* teamRoster;
    /* 0x864 */ ThumbnailState thumbnail;
    /* 0xA04 */ MonCaptionState captionState;
    /* 0xA8C */ SpeciesLearnsetBuffer redBlueLearnsets[3];
    /* 0xAEC */ SpeciesLearnsetBuffer yellowLearnsets[3];
} ActivePokemon; // size = 0xB4C

typedef struct MovePresentationCue {
    /* 0x00 */ u8 id;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ u8 defaultAnchor;
    /* 0x03 */ u8 alternateAnchor;
    /* 0x04 */ u8 animationDuration;
    /* 0x05 */ u8 flags1;
    /* 0x06 */ u8 currentFrame;
    /* 0x07 */ u8 endFrame;
    /* 0x08 */ u8 unk_08;
    /* 0x09 */ u8 unk_09;
    /* 0x0A */ u8 frameCounter;
} MovePresentationCue; // size = 0xB (Stadium 1: 0x10)

typedef struct unk_D_8438E7B0 {
    /* 0x000 */ MovePresentationCue moveCues[165];
    /* 0x717 */ MovePresentationCue idleCues;
    /* 0x722 */ MovePresentationCue unkA60;
    /* 0x72D */ MovePresentationCue faintCue;
    /* 0x738 */ MovePresentationCue hitCue;
    /* 0x743 */ MovePresentationCue chargeCues[6];
    /* 0x785 */ MovePresentationCue sleepIdleCue;
    /* 0x790 */ MovePresentationCue flyingIdleCue;
    /* 0x79B */ MovePresentationCue unk_B10;
    /* 0x7A6 */ MovePresentationCue hitReactionOverride;
    /* 0x7B1 */ MovePresentationCue unkB30[5];
    /* 0x7E8 */ u8 unkB30_tail;
    /* 0x7E9 */ u8 wakeUpEventTrack;
} PokemonBattleCues; // size >= 0x7EA

// moveCues[] has one entry per move, so cue indices past the last move alias the
// named cues that follow it (each MovePresentationCue is 0xB bytes in Zero).
#define BATTLE_CUE_IDLE 165       // idleCues (0x717)
#define BATTLE_CUE_A60 166        // unkA60 (0x722)
#define BATTLE_CUE_FAINT 167      // faintCue (0x72D)
#define BATTLE_CUE_HIT 168        // hitCue (0x738)
#define BATTLE_CUE_SLEEP_IDLE 175 // sleepIdleCue (0x785)
#define BATTLE_CUE_B00 176        // flyingIdleCue (0x790)

// Gen 1 type-effectiveness multipliers, in tenths; see sTypeEffectiveness.
#define TYPE_EFFECTIVENESS_NONE 0
#define TYPE_EFFECTIVENESS_NOT_VERY 5
#define TYPE_EFFECTIVENESS_NEUTRAL 10
#define TYPE_EFFECTIVENESS_SUPER 20

typedef struct BattleScene {
    /* 0x00 */ char unk00[0x8];
    /* 0x08 */ s8 visibilityPolicy;
    /* 0x0C */ s32 bRollShotIndex;
    /* 0x10 */ s32 substepFrameCounter;
    /* 0x14 */ s32 stepFrameTimer;
    /* 0x18 */ u16 transitionStage;
    /* 0x1A */ u8 hitReactionKind;
    /* 0x1C */ s32 mode;
    /* 0x20 */ s32 phaseStep;
    /* 0x24 */ s32 modelReloadStep;
    /* 0x28 */ char unk28[0x2];
    /* 0x2A */ u16 sideCurrentlySwitching;
    /* 0x2C */ u16 actingSide;
    /* 0x2E */ u16 transitionStyle;
    /* 0x30 */ s32 transitionStep;
    /* 0x34 */ s32 actionPass;
    /* 0x38 */ s32 phase;
    /* 0x3C */ s32 phaseSubstep;
    /* 0x40 */ s32 winner;
    /* 0x44 */ s32 unk_44;
    /* 0x48 */ s32 moveEffectKind;
    /* 0x4C */ s32 rageFollowupPhase;
    /* 0x50 */ s32 cameraPresetId;
    /* 0x54 */ u8 heightShotSide;
    /* 0x56 */ s16 unk_56;
    /* 0x58 */ s16 rotationX; // camera pitch about the look-at point
    /* 0x5A */ s16 rotationY; // camera yaw about the look-at point (the B-roll orbit sweeps it)
    /* 0x5C */ f32 distance;
    /* 0x60 */ f32 verticalFieldOfView;
    /* 0x64 */ char unk64[0x4];
    /* 0x68 */ f32 shakeAmplitude;
    /* 0x6C */ f32 unk_6C;
    /* 0x70 */ f32 targetDistance;
    /* 0x74 */ f32 unk_74;
    /* 0x78 */ u8 nextPhase;
    /* 0x7A */ s16 shakeAngle;
    /* 0x7C */ char unk7C[0x8];
    /* 0x84 */ Vec3f unk_94;
    /* 0x90 */ Vec3f unk_A0;
    /* 0x9C */ char unkAC[0xC];
    /* 0xA8 */ Vec3f unk_B8;
    /* 0xB4 */ Vec3f unk_C4;
    /* 0xC0 */ Vec3f unk_D0;
    /* 0xCC */ CameraNode* camera;
} BattleScene; // size = 0xD0 (Stadium 1: 0xE0)

typedef struct unk_D_84390240 {
    /* 0x00 */ BattleScene* scene;
    /* 0x04 */ char unk04[0x3C];
} unk_D_84390240; // size = 0x40

typedef void (*BattleSceneStateCallback)(ActivePokemon*);

typedef struct BattleSceneStateRow {
    /* 0x00 */ s16 unk_00;
    /* 0x04 */ BattleSceneStateCallback unk_04[7];
    /* 0x20 */ s32 unk_20;
    /* 0x24 */ s32 mode;
    /* 0x28 */ s32 unk_28;
} BattleSceneStateRow; // size = 0x2C

typedef struct unk_D_843C4E44 {
    /* 0x000 */ u8 unk_000;
    /* 0x001 */ u8 unk_001;
    /* 0x3F2 */ char unk02[0x3F2];
} unk_D_843C4E44; // size >= 0x3F4

typedef struct unk_D_843C4DEC {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ char unk04[0x54];
} unk_D_843C4DEC; // size = 0x58

typedef struct BattleSceneStateTickSlot {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ BattleSceneStateCallback callback;
} BattleSceneStateTickSlot; // size = 0x8

typedef struct TagTeamPartners {
    /* 0x00 */ u8 firstPartner;
    /* 0x01 */ u8 secondPartner;
    /* 0x02 */ char names[14];
} TagTeamPartners; // size = 0x10

typedef struct unk_D_84390178 {
    /* 0x00 */ s32 timeLeft;
    /* 0x04 */ char unk04[0x14];
} unk_D_84390178; // size >= 0x18

typedef struct SpeciesModelTransform {
    /* 0x00 */ Vec3f coordinates;
    /* 0x0C */ s16 rotationX;
    /* 0x0E */ s16 rotationY;
    /* 0x10 */ s16 unk_10;
    /* 0x12 */ u16 idleTimer;
    /* 0x14 */ char unk14[0xC];
} SpeciesModelTransform; // size = 0x20

typedef struct unk_D_84390028 {
    /* 0x00 */ f32 width;
    /* 0x04 */ f32 height;
    /* 0x08 */ f32 restingHeight;
    /* 0x0C */ f32 cameraTargetOffsetY;
} ModelDimensions; // size = 0x10

typedef struct unk_D_84384608 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ u16 unk_04;
} unk_D_84384608; // size = 0x8

typedef struct unk_D_843847BC {
    /* 0x00 */ s16 x;
    /* 0x02 */ s16 y;
    /* 0x04 */ s16 width;
    /* 0x08 */ f32 verticalFieldOfView;
    /* 0x0C */ f32 nearPlane;
    /* 0x10 */ f32 farPlane;
    /* 0x14 */ s16 unk_14;
} ThumbnailSettings; // size = 0x18

typedef struct unk_D_843901B0 {
    /* 0x00 */Vec3f unk_00;
    /* 0x0C */s16 unk_0C;
    /* 0x0E */s16 unk_0E;
    /* 0x10 */char unk10[0x2];
    /* 0x12 */s16 unk_12;
    /* 0x14 */s16 unk_14;
    /* 0x18 */f32 unk_18;
    /* 0x1C */f32 unk_1C;
    /* 0x20 */s16 unk_20;
    /* 0x22 */s16 unk_22;
    /* 0x24 */char unk24[0x2];
    /* 0x26 */s16 unk_26;
    /* 0x28 */s16 unk_28;
    /* 0x2C */f32 unk_2C;
    /* 0x30 */f32 unk_30;
    /* 0x34 */f32 unk_34;
    /* 0x38 */f32 unk_38;
    /* 0x3C */f32 unk_3C;
} unk_D_843901B0; // size >= 0x40

typedef struct unk_D_843901A0_4C8 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ Vec3f unk_14;
    /* 0x20 */ f32 unk_20;
    /* 0x24 */ f32 unk_24;
    /* 0x28 */ s16 unk_28;
    /* 0x2A */ s16 unk_2A;
} unk_D_843901A0_4C8; // size = 0x2C

typedef struct unk_D_843901A0 {
    /* 0x000 */ u8 unk_000;
    /* 0x004 */ s32 unk_004;
    /* 0x008 */ u8 unk_008[4];
    /* 0x00C */ char unk00C[0x3C];
    /* 0x048 */ u8 unk_048[64];
    /* 0x088 */ s8 unk_088[64];
    /* 0x0C8 */ s8 unk_0C8[64];
    /* 0x148 */ s8 unk_108[64];
    /* 0x148 */ s8 unk_148[64];
    /* 0x188 */ s8 unk_188[64];
    /* 0x1C8 */ s8 unk_1C8[64];
    /* 0x208 */ s8 unk_208[64];
    /* 0x248 */ s8 unk_248[64];
    /* 0x288 */ s8 unk_288[64];
    /* 0x2C8 */ s8 unk_2C8[64];
    /* 0x2C8 */ s8 unk_308[64];
    /* 0x348 */ s8 unk_348[64];
    /* 0x388 */ s8 unk_388[64];
    /* 0x3C8 */ s8 unk_3C8[64];
    /* 0x408 */ s8 unk_408[64];
    /* 0x448 */ s8 unk_448[2][64];
    /* 0x4C8 */ unk_D_843901A0_4C8 unk_4C8;
} unk_D_843901A0; // size = 0x4F4

typedef struct unk_D_84385790 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ Color_RGBA8 unk_04;
} unk_D_84385790; // size = 0x8

typedef struct arg1_func_84344CE8 {
    /* 0x00 */ char unk00[0x14];
    /* 0x14 */ u8* unk_14;
    /* 0x18 */ Gfx* unk_18;
} arg1_func_84344CE8; // size >= 0x1C

typedef struct arg1_func_8434E21C {
    /* 0x00 */ u8* unk_00;
    /* 0x04 */ u8* unk_04;
    /* 0x08 */ char unk08[0x2];
    /* 0x0A */ s16 unk_0A;
} arg1_func_8434E21C; // size >= 0xC

typedef struct RibbonMeshVertexState {
    /* 0x00 */ f32 unk_00;
    /* 0x04 */ f32 unk_04;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ s16 unk_0C;
    /* 0x0E */ s16 unk_0E;
    /* 0x10 */ Color_RGBA8 unk_10;
    /* 0x14 */ f32 unk_14;
    /* 0x18 */ f32 unk_18;
} RibbonMeshVertexState; // size = 0x1C

typedef struct RibbonMesh {
    /* 0x000 */ s32 unk_000;
    /* 0x004 */ f32 unk_004;
    /* 0x008 */ f32 unk_008;
    /* 0x00C */ f32 unk_00C;
    /* 0x010 */ f32 unk_010;
    /* 0x014 */ f32 unk_014;
    /* 0x018 */ s16 unk_018;
    /* 0x01A */ s16 unk_01A;
    /* 0x01C */ s16 unk_01C;
    /* 0x01E */ s16 unk_01E;
    /* 0x020 */ f32 unk_020;
    /* 0x024 */ s32 unk_024;
    /* 0x028 */ s32 unk_028;
    /* 0x02C */ s32 unk_02C;
    /* 0x030 */ s32 unk_030;
    /* 0x034 */ s32 unk_034;
    /* 0x038 */ s32 unk_038;
    /* 0x03C */ s32 unk_03C;
    /* 0x040 */ s32 unk_040;
    /* 0x044 */ s32 unk_044;
    /* 0x048 */ char unk048[0x8];
    /* 0x050 */ Vtx unk_050[31 * 2];
    /* 0x430 */ RibbonMeshVertexState unk_430[31 * 2];
} RibbonMesh; // size = 0xAF8

typedef struct unk_D_843975E8 {
    /* 0x00 */ f32 unk_00;
    /* 0x04 */ f32 unk_04;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ f32 unk_10;
    /* 0x14 */ f32 unk_14;
    /* 0x18 */ f32 unk_18;
    /* 0x1C */ f32 unk_1C;
    /* 0x20 */ f32 unk_20;
    /* 0x24 */ char unk24[0x4];
} unk_D_843975E8; // size = 0x28

typedef struct Radial20Node {
    /* 0x00 */ f32 unk_00;
    /* 0x04 */ u8 unk_04;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ Vec3f unk_10;
    /* 0x1C */ Vec3f unk_1C;
    /* 0x28 */ char unk28[0x20];
} Radial20Node; // size = 0x48

typedef struct Radial20 {
    /* 0x000 */ s16 unk_000;
    /* 0x002 */ s16 unk_002;
    /* 0x004 */ s16 unk_004;
    /* 0x006 */ s16 unk_006;
    /* 0x008 */ s16 unk_008;
    /* 0x00A */ Color_RGBA8 unk_00A; // Stadium 1 follows this with a Color_RGB8
    /* 0x010 */ f32 unk_014;
    /* 0x014 */ f32 unk_018;
    /* 0x018 */ Vtx* unk_01C;
    /* 0x01C */ char unk020[0x18];
    /* 0x034 */ s32 unk_038[3];
    /* 0x040 */ Radial20Node unk_048[20];
} Radial20; // size = 0x5E0 (Stadium 1: 0x5E8)

typedef struct Trail40Node {
    /* 0x00 */ f32 unk_00;
    /* 0x04 */ f32 unk_04;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ f32 unk_10;
    /* 0x14 */ f32 unk_14;
    /* 0x18 */ s16 unk_18;
    /* 0x1A */ s16 unk_1A;
} Trail40Node; // size = 0x1C

typedef struct Trail40 {
    /* 0x0000 */ s16 unk_0000;
    /* 0x0002 */ s16 unk_0002;
    /* 0x0004 */ s16 unk_0004;
    /* 0x0008 */ f32 unk_0008;
    /* 0x000C */ Vtx* unk_000C;
    /* 0x0010 */ Mtx* unk_0010;
    /* 0x0014 */ Trail40Node unk_0014[16][16];
} Trail40; // size >= 0x1C14

typedef struct Trail40VariantNode {
    /* 0x00 */ f32 unk_00;
    /* 0x04 */ f32 unk_04;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ f32 unk_10;
    /* 0x14 */ f32 unk_14;
    /* 0x18 */ s16 unk_18;
    /* 0x1A */ s16 unk_1A;
    /* 0x1C */ f32 unk_1C;
} Trail40VariantNode; // size = 0x20

typedef struct Trail40Variant {
    /* 0x0000 */ s16 unk_0000;
    /* 0x0002 */ s16 unk_0002;
    /* 0x0004 */ s16 unk_0004;
    /* 0x0008 */ f32 unk_0008;
    /* 0x000C */ Vtx* unk_000C;
    /* 0x0010 */ Mtx* unk_0010;
    /* 0x0014 */ Trail40VariantNode unk_0014[16][16];
} Trail40Variant; // size >= 0x2014

typedef struct TexturedRibbonSheetNode {
    /* 0x00 */ f32 unk_00;
    /* 0x08 */ u8 unk_04;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ Vec3f unk_0C;
    /* 0x18 */ Vec3f unk_18;
    /* 0x24 */ Vec3f unk_24;
    /* 0x30 */ Vtx unk_30[2];
} TexturedRibbonSheetNode; // size = 0x50

typedef struct TexturedRibbonSheet {
    /* 0x000 */ s16 unk_000;
    /* 0x002 */ s16 unk_002;
    /* 0x004 */ s16 unk_004;
    /* 0x006 */ s16 unk_006;
    /* 0x008 */ s16 unk_008;
    /* 0x00A */ Color_RGB8 unk_00A;
    /* 0x010 */ f32 unk_010;
    /* 0x014 */ f32 unk_014;
    /* 0x018 */ Vtx* unk_018;
    /* 0x01C */ char unk01C[0x1C];
    /* 0x038 */ TexturedRibbonSheetNode unk_038[10];
} TexturedRibbonSheet; // size = 0x358

typedef struct FourStreamTrailNode {
    /* 0x00 */ u8 unk_00;
    /* 0x04 */ f32 unk_04;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ Vec3f unk_0C;
    /* 0x18 */ Vec3f unk_18;
    /* 0x24 */ f32 unk_24;
    /* 0x28 */ f32 unk_28;
    /* 0x2C */ Vec3f unk_2C;
    /* 0x38 */ Vec3f unk_38;
} FourStreamTrailNode; // size = 0x44

typedef struct FourStreamTrail {
    /* 0x000 */ s16 unk_000;
    /* 0x002 */ s16 unk_002;
    /* 0x004 */ s16 unk_004;
    /* 0x006 */ s16 unk_006;
    /* 0x008 */ Color_RGB8 unk_008;
    /* 0x00C */ f32 unk_00C;
    /* 0x010 */ f32 unk_010;
    /* 0x014 */ f32 unk_014;
    /* 0x018 */ Vtx* unk_018;
    /* 0x01C */ Vec3f unk_01C;
    /* 0x028 */ char unk028[0xC];
    /* 0x034 */ FourStreamTrailNode unk_034[15];
} FourStreamTrail; // size = 0x430

typedef struct OwnerLinkedFourStreamNode {
    /* 0x00 */ u8 unk_00;
    /* 0x04 */ f32 unk_04;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ Vec3f unk_0C;
    /* 0x18 */ Vec3f unk_18;
    /* 0x24 */ f32 unk_24;
    /* 0x28 */ f32 unk_28;
    /* 0x2C */ Vec3f unk_2C;
    /* 0x38 */ Vec3f unk_38;
} OwnerLinkedFourStreamNode; // size = 0x44

typedef struct OwnerLinkedFourStream {
    /* 0x000 */ s16 unk_000;
    /* 0x002 */ s16 unk_002;
    /* 0x004 */ s16 unk_004;
    /* 0x006 */ s16 unk_006;
    /* 0x008 */ Color_RGB8 unk_008;
    /* 0x00C */ f32 unk_00C;
    /* 0x010 */ f32 unk_010;
    /* 0x014 */ f32 unk_014;
    /* 0x018 */ Vtx* unk_018;
    /* 0x01C */ Vec3f unk_01C;
    /* 0x028 */ char unk028[0xC];
    /* 0x034 */ Particle* unk_034;
    /* 0x038 */ OwnerLinkedFourStreamNode unk_038[15];
} OwnerLinkedFourStream; // size = 0x434

typedef struct OwnerAnchoredFourStreamNode {
    /* 0x00 */ u8 unk_00;
    /* 0x04 */ f32 unk_04;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ Vec3f unk_0C;
    /* 0x18 */ Vec3f unk_18;
    /* 0x24 */ f32 unk_24;
    /* 0x28 */ f32 unk_28;
    /* 0x2C */ Vec3f unk_2C;
    /* 0x38 */ Vec3f unk_38;
} OwnerAnchoredFourStreamNode; // size = 0x44

typedef struct OwnerAnchoredFourStream {
    /* 0x000 */ s16 unk_000;
    /* 0x002 */ s16 unk_002;
    /* 0x004 */ s16 unk_004;
    /* 0x006 */ s16 unk_006;
    /* 0x008 */ Color_RGB8 unk_008;
    /* 0x010 */ f32 unk_00C;
    /* 0x010 */ f32 unk_010;
    /* 0x014 */ Vtx* unk_014;
    /* 0x018 */ Particle* unk_018;
    /* 0x01C */ OwnerAnchoredFourStreamNode unk_01C[15];
    /* 0x418 */ f32 unk_418;
} OwnerAnchoredFourStream; // size = 0x41C

typedef struct Trail50EffectNode {
    /* 0x00 */ u8 unk_00;
    /* 0x04 */ f32 unk_04;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ Vec3f unk_0C;
    /* 0x18 */ Vec3f unk_18;
    /* 0x24 */ Vec3f unk_24;
    /* 0x30 */ f32 unk_30;
    /* 0x34 */ f32 unk_34;
    /* 0x38 */ Vec3f unk_38;
    /* 0x44 */ Vec3f unk_44;
} Trail50EffectNode; // size = 0x50

typedef struct Trail50Effect {
    /* 0x000 */ s16 unk_000;
    /* 0x002 */ s16 unk_002;
    /* 0x004 */ s16 unk_004;
    /* 0x006 */ s16 unk_006;
    /* 0x008 */ s16 unk_008;
    /* 0x00A */ Color_RGB8 unk_00A;
    /* 0x010 */ f32 unk_010;
    /* 0x014 */ f32 unk_014;
    /* 0x018 */ f32 unk_018;
    /* 0x01C */ char unk01C[0x4];
    /* 0x020 */ Vtx* unk_020;
    /* 0x024 */ Vec3f unk_024;
    /* 0x030 */ char unk030[0x10];
    /* 0x040 */ Trail50EffectNode unk_040[10];
} Trail50Effect; // size = 0x360

typedef struct unk_D_843C2C00_0B0 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ u8 unk_04;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ Vec3f unk_10;
    /* 0x1C */ f32 unk_1C;
    /* 0x20 */ f32 unk_20;
    /* 0x24 */ f32 unk_24;
} unk_D_843C2C00_0B0; // size = 0x28

typedef struct unk_D_843C2C00_064 {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
} unk_D_843C2C00_064; // size = 0xC

typedef struct unk_D_843C2C00_024 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ s32 unk_14;
    /* 0x18 */ s32 unk_18;
    /* 0x1C */ s32 unk_1C;
} unk_D_843C2C00_024; // size = 0x20

typedef struct unk_D_84389CE0 {
    /* 0x00 */ Color_RGBA8 unk_00;
    /* 0x04 */ u8 unk_04;
} unk_D_84389CE0; // size = 0x8

typedef struct DoubleTextureTrail {
    /* 0x000 */ s16 unk_000;
    /* 0x002 */ s16 unk_002;
    /* 0x004 */ s16 unk_004;
    /* 0x008 */ f32 unk_008;
    /* 0x00C */ f32 unk_00C;
    /* 0x010 */ f32 unk_010;
    /* 0x014 */ f32 unk_014;
    /* 0x018 */ Vtx* unk_018;
    /* 0x01C */ s32 unk_01C;
    /* 0x020 */ s32 unk_020;
    /* 0x024 */ unk_D_843C2C00_024 unk_024;
    /* 0x044 */ unk_D_843C2C00_024 unk_044;
    /* 0x064 */ unk_D_843C2C00_064 unk_064;
    /* 0x070 */ unk_D_843C2C00_064 unk_070;
    /* 0x07C */ unk_D_84389CE0 unk_07C;
    /* 0x081 */ unk_D_84389CE0 unk_081;
    /* 0x086 */ Color_RGBA8 unk_086;
    /* 0x08C */ f32 unk_08C;
    /* 0x090 */ f32 unk_090;
    /* 0x094 */ s16 unk_094;
    /* 0x096 */ char unk096[0x1A];
    /* 0x0B0 */ unk_D_843C2C00_0B0 unk_0B0[10];
} DoubleTextureTrail; // size = 0x240

typedef struct AuxiliaryEffectNode {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ Vec3f unk_0C;
} AuxiliaryEffectNode; // size = 0x18

typedef struct AuxiliaryEffect {
    /* 0x000 */ s16 unk_000;
    /* 0x002 */ char pad002[2];
    /* 0x004 */ AuxiliaryEffectNode unk_004[20];
} AuxiliaryEffect; // size = 0x1E4

typedef struct unk_D_843C3508_0A4 {
    /* 0x00 */ f32 unk_00;
    /* 0x04 */ f32 unk_04;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ Vec3f unk_0C;
    /* 0x18 */ Vec3f unk_18;
} unk_D_843C3508_0A4; // size = 0x24

typedef struct unk_D_843C3508 {
    /* 0x000 */ s16 unk_000;
    /* 0x002 */ s16 unk_002;
    /* 0x004 */ s16 unk_004;
    /* 0x006 */ s16 unk_006;
    /* 0x008 */ unk_D_84389CE0 unk_008;
    /* 0x00D */ unk_D_84389CE0 unk_00D;
    /* 0x014 */ f32 unk_014;
    /* 0x018 */ f32 unk_018;
    /* 0x01C */ s16 unk_01C;
    /* 0x020 */ s32 unk_020;
    /* 0x024 */ s32 unk_024;
    /* 0x028 */ unk_D_843C2C00_024 unk_028;
    /* 0x048 */ unk_D_843C2C00_024 unk_048;
    /* 0x068 */ unk_D_843C2C00_064 unk_068;
    /* 0x074 */ unk_D_843C2C00_064 unk_074;
    /* 0x080 */ f32 unk_080;
    /* 0x084 */ f32 unk_084;
    /* 0x088 */ Vtx* unk_088;
    /* 0x08C */ char unk08C[0x18];
    /* 0x0A4 */ unk_D_843C3508_0A4 unk_0A4[20];
} unk_D_843C3508; // size = 0x374

typedef struct StatStageMultiplier {
    /* 0x00 */ u8 multiplier;
    /* 0x01 */ u8 divisor;
} StatStageMultiplier; // size = 0x2

typedef struct TypeEffectivenessEntry {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ u8 unk_02;
} TypeEffectivenessEntry; // size = 0x3

typedef struct BattleAiMonState {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ u8 unk_02;
    /* 0x03 */ u8 unk_03;
    /* 0x04 */ u8 unk_04;
    /* 0x05 */ u8 unk_05[1];
    /* 0x0C */ char unk06[0xC];
    /* 0x12 */ BattleMonRuntime unk_12;
} BattleAiMonState; // size = 0x76

typedef struct BattleAiTeamState {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 unk_01[2];
    /* 0x03 */ u8 unk_03;
    /* 0x04 */ u8 unk_04[2];
    /* 0x06 */ u8 unk_06;
    /* 0x07 */ u8 unk_07[1];
    /* 0x08 */ u8 unk_08;
    /* 0x09 */ u8 unk_09;
    /* 0x0A */ u8 unk_0A[1];
    /* 0x0B */ char unk0B[0x5];
    /* 0x10 */ u8 unk_10;
    /* 0x11 */ u8 unk_11;
    /* 0x12 */ u8 unk_12;
    /* 0x13 */ u8 unk_13;
    /* 0x14 */ BattleAiMonState unk_14[1];
} BattleAiTeamState; // size >= 0x8A

typedef struct unk_D_843C5568 {
    /* 0x000 */ u8 unk_000;
    /* 0x001 */ u8 unk_001;
    /* 0x002 */ u8 unk_002;
    /* 0x003 */ u8 unk_003;
    /* 0x004 */ u8 unk_004;
    /* 0x005 */ u8 unk_005;
    /* 0x006 */ u8 unk_006;
    /* 0x007 */ u8 unk_007;
    /* 0x008 */ u8 unk_008;
    /* 0x009 */ char unk009[0x3];
    /* 0x00C */ u8 unk_00C[1];
    /* 0x00D */ char unk00D[0x5];
    /* 0x012 */ u8 unk_012;
    /* 0x013 */ char unk013[0x3];
    /* 0x016 */ BattleAiMonState unk_016[1];
    /* 0x08C */ char unk08C[0x510];
} unk_D_843C5568; // size = 0x59C

typedef struct BattleAiScoredMove {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ u8 unk_02;
    /* 0x03 */ u8 unk_03;
    /* 0x04 */ u8 unk_04;
    /* 0x05 */ u8 unk_05;
    /* 0x06 */ u8 unk_06;
    /* 0x07 */ u8 unk_07;
    /* 0x08 */ u8 unk_08;
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ s16 unk_0C;
    /* 0x0E */ s16 unk_0E;
    /* 0x10 */ s16 unk_10;
    /* 0x12 */ s16 unk_12;
    /* 0x14 */ s16 unk_14;
    /* 0x16 */ s16 unk_16;
    /* 0x18 */ s16 unk_18;
    /* 0x1A */ s16 unk_1A;
    /* 0x1C */ s16 unk_1C;
    /* 0x1E */ s16 unk_1E;
    /* 0x20 */ s16 unk_20;
    /* 0x24 */ s32 unk_24;
    /* 0x28 */ s32 unk_28;
} BattleAiScoredMove; // size = 0x2C

typedef struct SpeciesLevelUpLearnset {
    /* 0x00 */ u8 unk_00[1];
    /* 0x01 */ char unk01[9];
    /* 0x0A */ u8 unk_0A[1];
    /* 0x0B */ char unk0B[0x15];
} SpeciesLevelUpLearnset; // size = 0x20

typedef struct AIDecisionScratch {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ u8 unk_02;
    /* 0x04 */ s32 unk_04[1];
    /* 0x08 */ char unk08[0xC];
} AIDecisionScratch; // size = 0x14

typedef struct AIDifficultyConfig {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ u8 unk_04;
    /* 0x05 */ u8 unk_05;
    /* 0x06 */ u8 unk_06;
    /* 0x07 */ u8 unk_07;
    /* 0x08 */ u8 unk_08;
    /* 0x09 */ u8 unk_09;
    /* 0x0A */ u8 unk_0A;
    /* 0x0B */ u8 unk_0B;
    /* 0x0C */ u8 unk_0C;
    /* 0x0D */ u8 unk_0D;
    /* 0x0E */ u8 unk_0E;
    /* 0x0F */ u8 unk_0F;
    /* 0x10 */ u8 unk_10;
    /* 0x11 */ char unk11[0x3];
} AIDifficultyConfig; // size = 0x14

typedef struct unk_D_843C60F0 {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ u8 unk_02;
    /* 0x03 */ char unk03[0x9];
    /* 0x0C */ AIDecisionScratch unk_0C[3];
} unk_D_843C60F0; // size >= 0x48

typedef struct unk_D_843C6148 {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ u8 unk_02;
    /* 0x03 */ u8 unk_03;
    /* 0x04 */ u8 unk_04;
    /* 0x05 */ u8 unk_05;
    /* 0x06 */ char unk06[0x2];
} unk_D_843C6148; // size <= 0x8

typedef struct unk_func_8438220C {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ char unk01[0x3];
    /* 0x04 */ BattleAiScoredMove unk_04[4];
    /* 0xB4 */ u8 unk_B4;
    /* 0xB8 */ s32 unk_B8;
} unk_func_8438220C; // size = 0xBC

typedef struct unk_func_8437F85C_arg3 {
    /* 0x00 */ u8 unk_00[3][3];
} unk_func_8437F85C_arg3; // size = 0x3

extern PokemonBattleCues* sSideBattleCues[];
extern SpeciesModelTransform* sSidePresentationTransform[];

extern TagTeamPartners* sPlayerTagTeam[];
extern u8 sPokemonWithAlternateSleepIdle[];
extern u8 sAerodactyl;
extern u8 sFearow;
extern u8 sFarfetchD;
extern u8 sDoduoEvoLine[];
extern s16 sChargeMoveCues[];
extern ThumbnailSettings sSideThumbnailSettings[2];










extern BattleSceneStateCallback sBattleSceneStateTickSentinel;
extern BattleSceneStateRow sBattleSceneStateRowTable[];









extern ParticleDescriptor gBattleAnimParticleDescriptors[86];
extern func_D_84390320 gMoveAnimEffectStartFuncs[];
extern func_D_84390320 gMoveAnimEffectEndFuncs[];
extern func_D_84390320 gMoveAnimEffectStartUpdateFuncs[];
extern func_D_84390320 gMoveAnimEffectEndUpdateFuncs[];
extern func_D_84390320 gMoveAnimEffectStartDrawFuncs[];
extern func_D_84390320 gMoveAnimEffectEndDrawFuncs[];
extern Gfx D_82193350[];

extern Gfx D_821941F0[];

extern StatStageMultiplier gStatStageMultipliers[];

extern u8 sTypeEffects[];
extern u8* sSide1PokemonThumbnailImage;
extern u8* sSide2PokemonThumbnailImage;

extern u8 sBattleMoveFailed;
extern u8 sBattleCritFlag;


extern s32 sTypeEffectiveness;
//extern unk_D_843C4E44 D_843C4E44;
extern u8 sConfused;
extern u8 sStatCanBeChangedFurther;
extern u16 sBattleDamage;
extern BattleMonRuntime* sBattleUser;
extern BattleMonRuntime* sBattleTarget;


extern ActivePokemon* sActivePokemon[2];
extern ActivePokemon* sSide1ActivePokemon;
extern ActivePokemon* sSide2ActivePokemon;
extern ModelDimensions sPokemonModelDimensions[2];

extern char** sBattleMessagesTable;
extern char** sPokemonNameTable;
extern char** sMoveNameTable;
extern char** sStatusConditionNameTable;
extern char** sBattleControllerDisconnectedMessage;






extern unk_D_843901A0* gBattleMessageQueues;
extern unk_D_843901B0 gCameraPreset;


extern s32 sMultihitCount;
extern s32 sMultihitCountdown;

extern unk_D_84390240 sBattleScene;

extern s32 gBattleAnimFrameCounter;
extern s32 gBattleAnimSpawnDelay;
extern s16 gBattleAnimCurrentAnchor;
extern s16 gBattleAnimDefaultAnchor;
extern ActivePokemon* gBattleAnimCurrentOwner;
extern ActivePokemon* gBattleAnimSecondaryOwner;
extern ActivePokemon* gBattleAnimTertiaryOwner;
extern s32 D_811842A0;
extern s32 D_8219A830;
extern func_D_84390300 gBattleAnimEffectUpdateFuncs[8];
extern func_D_84390320 gBattleAnimEffectDrawFuncs[8];


extern s16 gSavedPrimColorR;
extern s16 gSavedPrimColorG;
extern s16 gSavedPrimColorB;
extern s16 gSavedPrimColorA;
extern s16 gPrimColorR;
extern s16 gPrimColorG;
extern s16 gPrimColorB;
extern s16 gPrimColorA;
extern s16 gEnvColorR;
extern s16 gEnvColorG;
extern s16 gEnvColorB;
extern s16 gEnvColorA;
extern s16 gFogColorR;
extern s16 gFogColorG;
extern s16 gFogColorB;
extern s16 gFogColorA;
extern s16 gBlendColorR;
extern s16 gBlendColorG;
extern s16 gBlendColorB;
extern s16 gBlendColorA;
extern f32 D_8219C590[26];
extern u8* sBattleAnimAssetPointers[256];
extern s16 sBattleAnimResourceList[0x10];
extern arg1_func_80019420* sBattleAnimResourceTablePointers[40];



s32 Battle_StageGeoDispatchCallback(s32 event, GraphNode* node);
s32 Battle_StageLightAngleCallbackA(s32 event, unk_D_86002F34_alt18* light);
s32 Battle_StageLightAngleCallbackB(s32 event, unk_D_86002F34_alt18* light);
s32 Battle_StageMaterialTintCallback(s32 event, DisplayObject* object);
void Battle_SetStageTintColor(u8 r, u8 g, u8 b);
void Battle_SetStageScale(f32 scale);
u16 Battle_TintTexel16(u16 color);
void Battle_DrawStageBackdrop(void);
void Battle_RenderActivePokemonThumbnail(GraphNode* thumbnail_root, DepthBuffer* thumbnail);
void Battle_DrawClippedTextureRect(s32 x1, s32 y1, s32 x2, s32 y2);
void Battle_DrawTexturedRectSegment(s32 x1, s32 y1, s32 draw_width, s32 height, u8* texture, s32 load_width);
void Battle_FillActivePokemonThumbnail(GraphNode* thumbnail_root, DepthBuffer* thumbnail);
void Battle_ResetFaintBatches(void);
void Battle_UpdateFaintBatches(void);
void func_8180050C(void);
void func_82100CB8(void);
s32 BattleScene_UpdateFrame(s32 fade_mode);
s32 BattleScene_UpdatePausedFrame(s32 fade_mode);
void Battle_UpdateCompletionGate(void);
s32 Battle_FrameCallback(s32 fade_mode);
void Battle_CompleteRosterOrder(u8* roster_order, s32 number_of_pokemon_picked);
void Battle_SelectComRoster(void);
void BattleScene_InitializeParticipantPresentation(BattleSessionTeams* side, unk_D_86002F30* model);
void BattleScene_Init(StageContext* stage_context);
void func_82100CC0(void);
s32 Battle_Main(s32 arg0, SessionContext* arg1);

void BattleScene_ClearStateTickCallbacks(void);
void BattleScene_QueueRowEffectList3(ActivePokemon* actor, s32 effect_entry);
void BattleAnim_PlayMoveEffectScript(ActivePokemon* user, s32 move_id);
void BattleAnim_PlayChargingMoveEffectScript(ActivePokemon* user, s32 move_id);
void BattleAnim_PlayMoveEffectEnd(ActivePokemon* user, s32 move_id);
void BattleScene_TickClearAnimRecordIfLoaded(ActivePokemon* active_pokemon);
void BattleScene_TickStartRowAnimRecord(ActivePokemon* active_pokemon);
void BattleScene_TickQueueRowEffectList3AtAnimEnd(ActivePokemon* active_pokemon);
void BattleScene_ResetStateFrameCounter(ActivePokemon* active_pokemon);
void BattleScene_ResetOpponentStateFrameCounter(ActivePokemon* active_pokemon);
void BattleAnim_SetFlagForRockThrowingMoves(ActivePokemon* active_pokemon);
void BattleAnim_ClearRockThrowingMoveFlag(ActivePokemon* active_pokemon);
s32 BattleAnim_IsAssetLoadBusy(s8 *arg0);
s32 BattleAnim_PollAssetLoadBusyFlags(ActivePokemon* active_pokemon);
s32 BattleAnim_IsSessionBusy(ActivePokemon* active_pokemon);
s32 BattleAnim_TryRegisterAssetTables(ActivePokemon* active_pokemon);
void BattleScene_LoadMoveResourceList(ActivePokemon* active_pokemon);
void BattleScene_LoadRowResourceList(ActivePokemon* active_pokemon);
void BattleScene_ReloadMoveResourceList(ActivePokemon* active_pokemon);
void Battle_MakeSubstitute(ActivePokemon* active_pokemon);
void BattleScene_DestroySubstitute(ActivePokemon* active_pokemon);
s32 BattleScene_FindU16InByteArray(u16 lookup_value, u8* array, s32 array_length);
void Battle_MarkIllegalMoves(ActivePokemon* pokemon, u16 pokemon_id, SpeciesLearnsetBuffer* red_blue_learnset, SpeciesLearnsetBuffer* yellow_learnset);
void Battle_InitializeMoveIllegalityMask(ActivePokemon* active_pokemon);
void Battle_DmaLoadLevelUpLearnset(u8 species, u32 destination);
void Battle_DmaLoadSpeciesLearnsets(s32 species_index, SpeciesLearnsetBuffer* red_blue_learnset, SpeciesLearnsetBuffer* yellow_learnset);
void Battle_LoadAnimationAndMarkMoveIllegality(ActivePokemon* pokemon, s32 mark_move_illegality);
void BattleScene_TickRow10CleanupAndEnterState18(ActivePokemon* active_pokemon);
void BattleScene_EnterRow3StartMoveAnim(ActivePokemon* active_pokemon);
void BattleScene_TickRow3PlayMoveEffectScript(ActivePokemon* active_pokemon);
void BattleScene_TickRow3PostEffectCamera(ActivePokemon* active_pokemon);
void Battle_HandleStatBoostingMoveAnimation(ActivePokemon* active_pokemon);
void BattleScene_MakeGoldenWhenHarden(ActivePokemon* active_pokemon);
void BattleScene_EnterRow21StartAnimRecord0(ActivePokemon* active_pokemon);
void BattleScene_TickRow22PlaySpeciesSound(ActivePokemon* active_pokemon);
void BattleScene_EnterRow19StartMoveAnimMidFrame(ActivePokemon* active_pokemon);
void BattleScene_TickRow19PlayMoveEffectScript(ActivePokemon* active_pokemon);
void BattleScene_TickRow19PostEffectCamera(ActivePokemon* active_pokemon);
void BattleScene_StartHitReactionAnim(ActivePokemon* active_pokemon);
void BattleScene_HandleLassoMoves(ActivePokemon* active_pokemon);
void BattleScene_TickRow4PostEndCamera(ActivePokemon* active_pokemon);
void BattleScene_EnterRow15StartAnimA80Seq30(ActivePokemon* active_pokemon);
s32 BattleScene_IsOpponentRowCheckpointReached(ActivePokemon* active_pokemon);
s32 BattleScene_IsRowZeroCheckpointReached(ActivePokemon* active_pokemon);
void BattleScene_StartHitCueAnimation(ActivePokemon* active_pokemon);
void BattleScene_EnterRowAnim166WithCry(ActivePokemon* active_pokemon);
void BattleScene_TickRow1PlayOwnerCry(ActivePokemon* active_pokemon);
void BattleScene_TickRow16PlayCryAndSpeciesSound(ActivePokemon* active_pokemon);
void BattleScene_TickRow18PlayCryAndSpeciesSound(ActivePokemon* active_pokemon);
void BattleScene_TickAssetLoadQueueRowEffectList3(ActivePokemon* active_pokemon);
void BattleScene_TickQueueRowEffectList3OnFirstFrame(ActivePokemon* active_pokemon);
void BattleScene_TickRow21CleanupAndEnterState18(ActivePokemon* active_pokemon);
void BattleScene_ResetOwnerModelIfLoaded(ActivePokemon* active_pokemon);
void BattleScene_EnterChargeTurnRow(ActivePokemon* active_pokemon);
void BattleScene_TickRow8PlayMoveEffectScriptB(ActivePokemon* active_pokemon);
void BattleScene_EnterRow9SetEventTrack(ActivePokemon* active_pokemon);
void BattleScene_EnterRow9QueueEffectList6(ActivePokemon* active_pokemon);
void BattleScene_Row12Slot1CameraCleanup(ActivePokemon* active_pokemon);
void BattleScene_Row13PlaySequences14And21(ActivePokemon* active_pokemon);
void BattleScene_TickPlaySpeciesSequence33(ActivePokemon* active_pokemon);
void BattleScene_TickQueueList3Selector2OrC(ActivePokemon* active_pokemon);
void BattleScene_TickQueueList3Selector2OrCFromB10(ActivePokemon* active_pokemon);
void BattleScene_EnterRow11StartHitReactionAnim(ActivePokemon* active_pokemon);
void BattleScene_TickRow14PlayMoveEffectEnd(ActivePokemon* active_pokemon);
s32 BattleScene_GetOpponentEffectCheckpoint(ActivePokemon* active_pokemon);
void BattleScene_TickRow11QueueEffectList6(ActivePokemon* active_pokemon);
void BattleScene_TickRow11PostEndCamera(ActivePokemon* active_pokemon);
void BattleScene_StateCallbackNop(ActivePokemon* active_pokemon);
void BattleScene_RegisterStateTickCallback(ActivePokemon* active_pokemon, BattleSceneStateCallback callback);
void BattleScene_SetOpponentEventTrackA6(ActivePokemon* active_pokemon);
void BattleScene_EnterStateRow(ActivePokemon* active_pokemon, s32 row_index);
void BattleScene_TickStateCallbacks(void);
void Battle_StopBeingGoldAfterHarden(ActivePokemon* active_pokemon);
void BattleAnim_SetModelEventTrackFromRow(ActivePokemon* pokemon, s32 cue_index);
s32 BattleAnim_TrySetModelEventTrackFromRow(ActivePokemon* active_pokemon, s32 cue_index, s32 event_state);
void BattleAnim_SetModelEventTrackAndState(ActivePokemon* active_pokemon, s32 cue_index, s32 event_state);
s32 BattleScene_IsParticipantIncapacitated(ActivePokemon* active_pokemon);
s32 BattleScene_IsRowWaitComplete(ActivePokemon* active_pokemon, s32 frame_limit);
s32 BattleScene_IsRowWaitCompleteWithEventCount(ActivePokemon* active_pokemon, s32 frame_limit);
s32 Battle_IsRowAnimationSettled(ActivePokemon* active_pokemon, s32 frame_limit);
s32 BattleScene_IsMoveKeyedRowWaitComplete(ActivePokemon* active_pokemon, s32 frame_limit);
s32 BattleScene_IsRowAnimWaitComplete(ActivePokemon* active_pokemon, s32 frame_limit);
void BattleScene_TryQueueIdleCueEffect(ActivePokemon* active_pokemon);
void Battle_SetRuntimeFlags(ActivePokemon* active_pokemon, u16 flag);
s32 Battle_ClearRuntimeFlags(s8 *arg0, unsigned short arg1);
void BattleScene_ResetParticipantAnimationFlags(ActivePokemon* active_pokemon);
void BattleScene_ResetBothParticipantsAnimationState(void);
void Battle_ClearOpponentHopFlagAndSyncMove(ActivePokemon* active_pokemon);
void BattleScene_CleanupParticipantHideFlag(ActivePokemon* active_pokemon);
void BattleScene_CleanupOpponentSpecialAnimFlag(ActivePokemon* active_pokemon);
void BattleScene_CleanupOpponentAnimationFlags(ActivePokemon* active_pokemon);
void BattleScene_CleanupParticipantEffectMode(ActivePokemon* active_pokemon);
void BattleAnim_TickParticipantStatusAnimation(ActivePokemon* active_pokemon);
void BattleAnim_TriggerStatusAfflictionCry(ActivePokemon* active_pokemon);
void BattleScene_AllocateParticipantRecord(BattleSessionTeams* session_teams, s32 side_index);
void BattleScene_AllocateParticipants(BattleSessionTeams* battle_teams);
void BattleScene_InitializeParticipantController(ActivePokemon* active_pokemon);
void BattleScene_InitializeParticipantModel(ActivePokemon* active_pokemon);
void BattleScene_InitializeParticipantOwnerModel(ActivePokemon* active_pokemon);
void BattleScene_InitializeParticipantSecondaryModels(ActivePokemon* active_pokemon, UNUSED s32* secondary_models);
void BattleScene_InitializeParticipantAuxiliaryModel(ActivePokemon* active_pokemon);
void BattleScene_InitializePresentation(UNUSED BattleSessionTeams* session_teams);
void BattleScene_ResetParticipantAuxTransform(UNUSED ActivePokemon* owner, ActivePokemon* active_pokemon, s32 facing_direction);
void BattleScene_InitializeRuntime(BattleSessionTeams* session_teams);
void BattleScene_UpdateParticipantsAndQueueEffects(UNUSED ActivePokemon* side1_pokemon, UNUSED ActivePokemon* side2_pokemon);
s32 BattleScene_DispatchLifecycle(s32 lifecycle_stage, BattleSessionTeams* session_teams);
void func_82105E64(ActivePokemon* active_pokemon);
void BattleScene_StateRow56EnterNop(ActivePokemon* active_pokemon);
void BattleScene_StateRow5Slot3Nop(ActivePokemon* active_pokemon);
void BattleScene_StateRow5Slot4Nop(ActivePokemon* active_pokemon);
void BattleScene_StateRow5Slot5Nop(ActivePokemon* active_pokemon);
void BattleScene_StateRow5Slot6Nop(ActivePokemon* active_pokemon);
void BattleScene_StateRow7Slot5Nop(ActivePokemon* active_pokemon);
void BattleScene_StateRow6Slot6Nop(ActivePokemon* active_pokemon);
void BattleScene_StateRow6Slot5Nop(ActivePokemon* active_pokemon);
void BattleScene_StateRow6Slot4Nop(ActivePokemon* active_pokemon);
void BattleScene_StateRow6Slot3Nop(ActivePokemon* active_pokemon);

void func_82142678(UNUSED ActivePokemon* active_pokemon, UNUSED s32 unused);
void func_821597B8(UNUSED ActivePokemon* active_pokemon, UNUSED s32 unused);
void BattleScene_StateRow7Slot4Nop(ActivePokemon* active_pokemon);


void BattleThumbnail_TriggerOwnerModelAnimation(ActivePokemon* active_pokemon);
void BattleThumbnail_ClearParticipantOwnerIdleFlags(ActivePokemon* active_pokemon);
void BattleThumbnail_SetParticipantOwnerIdleFlags(ActivePokemon* active_pokemon);
void BattleThumbnail_ClearBothOwnerIdleFlags(void);
void BattleThumbnail_SetBothOwnerIdleFlags(void);
void BattleThumbnail_SetFlagToUpdatePokemonThumbnail(CameraNode* camera);
void BattleThumbnail_LoadOwnerCameraFramingConstants(ActivePokemon* active_pokemon);
void BattleThumbnail_SetupOwnerCameraFraming(ActivePokemon* side1_pokemon, ActivePokemon* side2_pokemon);
void BattleThumbnail_OwnerCameraLifecycleNop(void);
void BattleThumbnail_ApplyOwnerCameraFraming(ActivePokemon* active_pokemon);
void BattleThumbnail_TickOwnerCameraFraming(ActivePokemon* active_pokemon);
void BattleThumbnail_InitializeOwnerCameraFraming(CameraNode* side1_camera_node, ActivePokemon* side1_pokemon, CameraNode* side2_camera_node, ActivePokemon* side2_pokemon);
void BattleThumbnail_TickOwnerSlideIn(ActivePokemon* active_pokemon, s32 delta);
void BattleThumbnail_TickOwnerSlideOut(ActivePokemon* active_pokemon, s32 delta);
void BattleThumbnail_TickOwnerSlideAnimation(ActivePokemon* active_pokemon);
void BattleThumbnail_TickBothOwnerSlideAnimations(ActivePokemon* side1_pokemon, ActivePokemon* side2_pokemon);
s32 BattleThumbnail_DispatchOwnerCameraLifecycle(s32 state, CameraNode* side1_camera_node, CameraNode* side2_camera_node);

s32 BattleScene_ByteArrayContains(u8 lookup, u8* array, s32 array_length);
BattleMon* BattleScene_GetParticipantSessionMon(ActivePokemon* active_pokemon);
s32 BattleScene_IsPartnerPikachu(ActivePokemon* active_pokemon);
f32 BattleScene_GetParticipantModelRestingHeight(ActivePokemon* active_pokemon);
f32 BattleScene_GetParticipantModelWidth(ActivePokemon* active_pokemon);
f32 BattleScene_GetParticipantModelHeight(ActivePokemon* active_pokemon);
f32 BattleScene_GetParticipantCameraTargetOffsetY(ActivePokemon* active_pokemon);
void BattleScene_PositionParticipantModel(ActivePokemon* active_pokemon);
f32 BattleScene_GetParticipantModelXOffset(ActivePokemon* active_pokemon);
void BattleScene_SetParticipantModelScale(ActivePokemon* arg0, f32 arg1);
s32 BattleScene_GetTeamMemberTeamSize(ActivePokemon* active_pokemon);
s32 BattleScene_GetPartnerTeamSize(ActivePokemon* active_pokemon);
s32 BattleScene_GetParticipantSideIndex(ActivePokemon* active_pokemon);
u8 BattleScene_GetMoveCueDefaultAnchor(ActivePokemon* active_pokemon);
u8 BattleScene_GetMoveCueAlternateAnchor(ActivePokemon* active_pokemon);
s16 BattleScene_GetHitCueDefaultAnchor(ActivePokemon* active_pokemon);
s32 BattleScene_GetHitCueAlternateAnchor(ActivePokemon* active_pokemon);
f32 BattleScene_GetParticipantModelBoundsHeight(ActivePokemon* active_pokemon);
f32 BattleScene_GetParticipantUnscaledBoundsHeight(ActivePokemon* active_pokemon);
s16 BattleScene_GetParticipantUsedMove(ActivePokemon* active_pokemon);
void BattleScene_GetParticipantModelBoundsScaled(ActivePokemon* arg0, Vec3f* arg1);
void BattleScene_GetParticipantModelRotation(ActivePokemon* arg0, Vec3s* arg1);
u16 Battle_GetActiveMonHp(ActivePokemon* active_pokemon);
s16 BattleScene_GetParticipantFacingAngle(s8 *arg0);
s32 BattleAnim_GetSpeciesBySideIndex(s32 arg0);
s32 BattleAnim_GetOwnerSpecies(ActivePokemon* active_pokemon);
u8 BattleScene_IsParticipantModelVisible(ActivePokemon* active_pokemon);
void BattleScene_GetParticipantModelPosition(ActivePokemon* arg0, Vec3f* arg1);
void BattleAnim_GetOwnerDefaultAnchorPosition(ActivePokemon* arg0, Vec3f* arg1);
void BattleScene_GetParticipantRestingPosition(ActivePokemon* arg0, Vec3f* arg1);
void BattleScene_GetParticipantPokeBallPosition(ActivePokemon* arg0, Vec3f* arg1);
f32 BattleAnim_GetOwnerModelHeight(ActivePokemon* active_pokemon);
f32 BattleScene_GetParticipantModelRadiusScaled(ActivePokemon* active_pokemon);
ModelNodeView* Battle_GetLoadedModelNode(ActivePokemon* active_pokemon, s32 node_index);
s32 Battle_GetDisplayModelId(ActivePokemon* active_pokemon, UNUSED s32 unused);
char* Battle_GetActiveMoveName(ActivePokemon* active_pokemon);
u8* Battle_GetActiveMonNickname(ActivePokemon* active_pokemon);
void BattleScene_SetParticipantModelTransform(ActivePokemon* active_pokemon, s32 transform_id, s32 transform_timer);
void Battle_ReturnToIdleAnimIfFinished(ActivePokemon* active_pokemon, ActivePokemon* animated_pokemon);
void Battle_ResetModelToIdleAnim(ActivePokemon* active_pokemon);
void Battle_SetModelToHitAnim(ActivePokemon* active_pokemon);
void BattleScene_BindParticipantTeamRoster(ActivePokemon* active_pokemon, s32 team_member_index);
void BattleScene_SetParticipantTeamMember(ActivePokemon* active_pokemon, s32 team_member_index);
void BattleScene_SetParticipantController(ActivePokemon* active_pokemon, Controller* controller);
void BattleScene_RebindParticipantTeamMember(ActivePokemon* arg0, s32 arg1);
s32 Battle_FreezeClauseInEffect(ActivePokemon* active_pokemon);
s32 Battle_SleepClauseInEffect(ActivePokemon* active_pokemon);
s32 BattleScene_GetCombinedTeamSize(ActivePokemon* active_pokemon);
u8 BattleScene_GetRosterTeamSize(TeamRoster* arg0);
s32 BattleScene_GetParticipantDisplayPlayerNumber(ActivePokemon* active_pokemon);
void BattleScene_ReinitParticipantBodyModel(ActivePokemon* owner, ActivePokemon* pokemon, s16 object_type);
void BattleScene_ReinitParticipantThumbnailModel(ActivePokemon* arg0, ThumbnailState* arg1, s16 arg2);
void BattleScene_ReinitParticipantAfterimages(ActivePokemon* arg0, s16 arg1);
void Battle_ResetEventTrack(ActivePokemon* active_pokemon);
void Battle_LoadOwnerModelForSpecies(ActivePokemon* active_pokemon);
void Battle_LoadOwnerModelForSwitchIn(ActivePokemon* active_pokemon);
void Battle_ResetOwnerModelToSubstituteDoll(ActivePokemon* active_pokemon);
void Battle_ReloadSubstituteDoll(ActivePokemon* active_pokemon);
void Battle_ReloadDisplayModel(ActivePokemon* active_pokemon);


void BattleAnim_InitSwayOffset(ActivePokemon* pokemon, f32 y, s16 theta);
void BattleAnim_UpdateTransform(ActivePokemon* owner, ActivePokemon* animated_pokemon, f32 height, f32 delta_y, s32 delta_theta);
void BattleAnim_UpdateSwayPhysicsToTarget(UNUSED ActivePokemon* owner, ActivePokemon* animated_object, f32 target, f32 delta, s32 theta0, s32 theta1);
void BattleScene_HideParticipantSecondaryModels(ActivePokemon* active_pokemon);
void BattleScene_ShowSecondaryModelsAtMainTransform(ActivePokemon* pokemon);
void BattleScene_UpdateSecondaryModelOrbit(ActivePokemon* pokemon);
void BattleScene_ShowSecondaryModelsAtMainPose(ActivePokemon* active_pokemon);
s32 BattleScene_ShrinkSecondaryModelsToScale(ActivePokemon* active_pokemon);
void BattleScene_ShowSecondaryModelsStaggeredFrame(ActivePokemon* active_pokemon);
void BattleScene_UpdateSecondaryModelTrailPosition(ActivePokemon* pokemon, s16 new_position);
void BattleScene_ResetParticipantModelFlags(ActivePokemon* active_pokemon);
void BattleAnim_DoubleTeamContinue(ActivePokemon* owner, ActivePokemon* animated_pokemon);
void BattleAnim_DoubleTeam(ActivePokemon* owner, ActivePokemon* animated_pokemon);
void BattleAnim_PokeBallLandStart(UNUSED ActivePokemon* owner, ActivePokemon* animated_pokemon);
void BattleAnim_PokeBallLandContinue(ActivePokemon* owner, ActivePokemon* animated_pokemon);
void BattleAnim_FlyStart(UNUSED ActivePokemon* owner, ActivePokemon* animated_pokemon);
void BattleAnim_FlyContinue(ActivePokemon* owner, ActivePokemon* animated_pokemon);
void BattleAnim_WaterfallStart(UNUSED ActivePokemon* owner, ActivePokemon* animated_pokemon);
void BattleAnim_WaterfallContinue(ActivePokemon* owner, ActivePokemon* animated_pokemon);
void BattleAnim_WaterfallEnd(UNUSED ActivePokemon* owner, UNUSED ActivePokemon* animated_pokemon);
void BattleAnim_Waterfall(ActivePokemon* owner, ActivePokemon* animated_pokemon);
s32 BattleAnim_ApproachAngleAndCheckThreshold(ActivePokemon* pokemon, s16 phase, s16 camera_offset_scale);
void BattleAnim_SubmissionEnd(ActivePokemon* owner, ActivePokemon* animated_pokemon);
void BattleAnim_Submission(ActivePokemon* owner, ActivePokemon* animated_pokemon);
void BattleAnim_DigEnd(ActivePokemon* owner, ActivePokemon* animated_pokemon);
void BattleAnim_Dig(ActivePokemon* owner, ActivePokemon* animated_pokemon);
void BattleAnim_AgilityContinue(ActivePokemon* owner, ActivePokemon* animated_pokemon);
void BattleAnim_AgilityEnd(ActivePokemon* owner, ActivePokemon* animated_pokemon);
void BattleAnim_Agility(ActivePokemon* owner, ActivePokemon* animated_pokemon);
void BattleAnim_DoubleTeamContinue(UNUSED ActivePokemon* owner, ActivePokemon* animated_pokemon);
void BattleAnim_DoubleTeam(ActivePokemon* owner, ActivePokemon* animated_pokemon);
void BattleAnim_ResetOwnerFacingAndExitStatusIdle(ActivePokemon* arg0);
void BattleAnim_SeismicTossContinue(UNUSED ActivePokemon* owner, ActivePokemon* animated_pokemon);
void BattleAnim_SeismicToss(ActivePokemon* owner, ActivePokemon* animated_pokemon);
void BattleAnim_Minimize(ActivePokemon* owner, ActivePokemon* animated_pokemon);
void BattleAnim_WithdrawContinue(ActivePokemon* owner, UNUSED ActivePokemon* animated_pokemon);
void BattleAnim_Withdraw(ActivePokemon* owner, ActivePokemon* animated_pokemon);
void BattleAnim_MeditateStart(ActivePokemon* owner, ActivePokemon* animated_pokemon);
void BattleAnim_MeditateContinue(ActivePokemon* owner, ActivePokemon* animated_pokemon);
void BattleAnim_MeditateEnd(ActivePokemon* owner, ActivePokemon* animated_pokemon);
void BattleAnim_Meditate(ActivePokemon* owner, ActivePokemon* animated_pokemon);
void BattleAnim_SquishHitReactionStart(ActivePokemon* owner, ActivePokemon* animated_pokemon);
void BattleAnim_SquishHitReactionContinue(ActivePokemon* owner, ActivePokemon* animated_pokemon);
void BattleAnim_BindHitReactionStart(UNUSED ActivePokemon* owner, ActivePokemon* animated_pokemon);
void BattleAnim_BindHitReactionContinue(ActivePokemon* owner, ActivePokemon* animated_pokemon);
void BattleAnim_SurfContinue(ActivePokemon* owner, ActivePokemon* animated_pokemon);
void BattleAnim_Surf(ActivePokemon* owner, ActivePokemon* animated_pokemon);
void BattleAnim_TransformNop(UNUSED ActivePokemon* owner, UNUSED ActivePokemon* animated_pokemon);
void BattleAnim_PlayTransformInducingAnimation(s32 side_index);
void BattleAnim_SetOwnerSecondaryStatusFlags(ActivePokemon* arg0, u8 arg1, u8 arg2);
void BattleAnim_ClearOwnerSecondaryStatusFlags(ActivePokemon* arg0);
void BattleAnim_InitSecondarySwayOffset(ActivePokemon* arg0, f32 arg1, s16 arg2);
void BattleAnim_UpdateSecondarySwayPhysics(ActivePokemon* arg0, ActivePokemon* arg1, UNUSED f32 arg2, UNUSED f32 arg3, UNUSED s32 arg4);
void BattleAnim_SecondaryStatusCaseBSub0(UNUSED ActivePokemon* arg0, ActivePokemon* arg1);
void BattleAnim_SecondaryStatusCaseBSub1(ActivePokemon* arg0, ActivePokemon* arg1);
void BattleAnim_SecondaryStatusCaseB(ActivePokemon* arg0, ActivePokemon* arg1);
void BattleAnim_SecondaryStatusDefault(UNUSED ActivePokemon* arg0, UNUSED ActivePokemon* arg1);
void BattleAnim_UpdateOwnerSecondaryStatusAnimation(s32 arg0);


void BattleAnim_CalculateDistanceAngles(Vec3f* arg0, Vec3f* arg1, f32* arg2, s16* arg3, s16* arg4);
Vec3f* BattleAnim_Vec3fSetZero(Vec3f* arg0);
Vec3f* BattleAnim_Vec3fOffsetByPolarXZ(Vec3f* arg0, Vec3f* arg1, f32 arg2, s16 arg3);
void BattleAnim_Vec3fSetPolarXZ(Vec3f* dest_vector, f32 magnitude, s16 theta);
Vec3f* BattleAnim_Vec3fCopy(Vec3f* dest, Vec3f* src);
Vec3s* BattleAnim_Vec3sCopy(Vec3s* arg0, Vec3s* arg1);
Vec3f* BattleAnim_Vec3fScaleComponents(Vec3f* arg0, f32 arg1, f32 arg2, f32 arg3);
s16 BattleAnim_Atan2sFromPoints(f32 arg0, f32 arg1, f32 arg2, f32 arg3);
f32 BattleAnim_Vec3fDistance(Vec3f arg0, Vec3f arg1);
f32 BattleAnim_Distance2D(f32 arg0, f32 arg1, f32 arg2, f32 arg3);
s32 BattleAnim_RandomIntWithWarmup(f32 arg0);
u16 BattleAnim_RandomRange(s32 range);
s32 BattleAnim_StepToS16(s16* dest, s16 finish, s16 rate);
s32 BattleAnim_StepToS16VariableRate(s16* arg0, s16 arg1, f32 arg2);
void BattleAnim_ApproachF(f32* dest, f32 value, f32 speed);
void BattleAnim_ApproachS16(s16* dest, s16 value, s16 speed);
void BattleAnim_ApproachU16(u16* dest, u16 value, s16 speed);
void Battle_ComputeSplineWeightsVariantA(f32* arg0, f32 arg1);
void Battle_ComputeSplineWeightsVariantB(f32* arg0, f32 arg1);
void Battle_ComputeSplineWeightsVariantC(f32* arg0, f32 arg1);
void Battle_ComputeSplineWeightsVariantD(f32* arg0, f32 arg1);
void Battle_ComputeSplineWeightsVariantE(f32* arg0, f32 arg1);


void BattleScene_InitializePresentationTimers(void);
void BattleScene_QuantizePresentationTimer(void);
s32 BattleScene_TickPresentationTimer(void);
s32 BattleScene_IsPresentationCountdownComplete(void);
s32 Battle_ClassifyHpTier(s32 arg0, s32 arg1);
s32 BattleScene_DetermineWinner(void);
s32 BattleScene_UpdateResultPresentation(void);
s32 BattleScene_IsActionSelectionTimerExpired(void);
void BattleScene_ResetActionSelectionTimer(void);
s32 BattleScene_TickActionSelectionTimers(void);
void BattleScene_ResetActionSelectionTimers(void);
s32 BattleScene_ApplyForcedActionDelay(ActivePokemon* active_pokemon);
void BattleScene_SyncActiveHpToPartyState(void);
s32 BattleScene_SelectFallbackWhenNoUsableMoves(ActivePokemon* active_pokemon);
s32 BattleScene_IsMoveUnavailable(ActivePokemon* arg0, s32 arg1);
void BattleScene_AutoSelectAvailableMove(ActivePokemon* active_pokemon);
void BattleScene_AutoSelectReplacementMon(ActivePokemon* active_pokemon);
void BattleScene_SelectActiveController(ActivePokemon* active_pokemon);
void BattleScene_HandleActionSelectionCancel(s32 arg0);
void Battle_InitializeActiveRuntimeState(void);
s32 BattleScene_CpuHasNoUsableMoves(ActivePokemon* active_pokemon);
s32 BattleScene_HandleCpuFaintedSwitch(ActivePokemon* arg0, ActivePokemon* arg1);
void BattleScene_CompleteCpuForcedAction(ActivePokemon* arg0, UNUSED ActivePokemon* arg1);
void BattleScene_AutoConfirmCpuMove(ActivePokemon* arg0, ActivePokemon* arg1);
void BattleScene_ApplyCpuChoice(ActivePokemon* arg0, ActivePokemon* arg1);
s32 BattleScene_ApplyCpuSwitchChoice(ActivePokemon* arg0, ActivePokemon* arg1);
s32 BattleScene_CollectCpuAction(ActivePokemon* arg0, ActivePokemon* arg1);
void BattleScene_ForfeitPrompt(ActivePokemon* active_pokemon);
void BattleScene_CommitPlayerSwitchAction(ActivePokemon* active_pokemon);
s32 BattleScene_ValidateSelectedPartyMember(ActivePokemon* active_pokemon);
void BattleScene_QueuePartySelectionConfirmMessage(ActivePokemon* active_pokemon);
void BattleScene_AssignActiveCoopController(ActivePokemon* arg0, s32 arg1);
void BattleScene_HandlePartySlotCursorInput(ActivePokemon* arg0, Controller* arg1);
void BattleScene_HandlePlayerPartySelection(ActivePokemon* active_pokemon);
void BattleScene_CommitSelectedMoveAction(ActivePokemon* active_pokemon);
s32 BattleScene_HandleNoUsableMoveSelection(ActivePokemon* active_pokemon);
s32 BattleScene_ValidateSelectedMove(ActivePokemon* active_pokemon);
void BattleScene_SelectMoveFromButtons(ActivePokemon* active_pokemon);
void BattleScene_HandlePlayerMoveSelection(ActivePokemon* active_pokemon);
s32 BattleScene_HandlePlayerMoveSelectionLocked(ActivePokemon* arg0, UNUSED Controller* arg1);
void BattleScene_ConfirmForcedMoveRepeat(ActivePokemon* active_pokemon);
void BattleScene_PollActionMenuRequestButtons(ActivePokemon* active_pokemon);
s32 BattleScene_HandlePlayerActionInput(ActivePokemon* active_pokemon);
s32 BattleScene_HandlePlayerFaintedSwitch(ActivePokemon* arg0, ActivePokemon* arg1);
void BattleScene_ShowParticipantOwnerAndSecondaryModels(void);
void BattleScene_HideParticipantOwnerAndSecondaryModels(void);
void BattleScene_AdvanceAttractInputScript(void);
void BattleScene_CheckForcedActionCondition(ActivePokemon* arg0, ActivePokemon* arg1);
void BattleScene_TickAttractModeInput(void);
void BattleScene_CollectPlayerAction(ActivePokemon* arg0, ActivePokemon* arg1);
void BattleScene_CollectActions(void);
void BattleScene_UpdateActionCollection(void);
void BattleScene_UpdateActionSelectPhase(void);


void func_8110FC30(void);
void BattleHud_DrawTranslucentShadowRect(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void BattleHud_DrawGradientRect(s32 arg0, s32 arg1, s32 arg2, s32 arg3, Color_RGB8* arg4, Color_RGB8* arg5);
void Battle_DrawGradientRectWrapper(s32 arg0, s32 arg1, s32 arg2, s32 arg3, Color_RGB8* arg4, Color_RGB8* arg5);
void func_8110FE90(void);
void BattleHud_DrawHpBar(s32 arg0, s32 arg1, f32 arg2, s32 arg3);
void BattleHud_Noop(void);
void BattleHud_DrawLevelNumber(s32 arg0, s32 arg1, s32 arg2);
void BattleHud_DrawHpFractionText(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void BattleHud_DrawTrainerNameLabel(s16 arg0, s16 arg1, s32 arg2, s32 arg3, s32 arg4);
void BattleHud_DrawTrainerNameLabelBlink(s16 arg0, s16 arg1, s32 arg2, s32 arg3, u16 arg4, s32 arg5);
void BattleHud_DrawTrainerNameLabelAuto(ActivePokemon* arg0, TeamRoster* arg1, s16 arg2, s16 arg3, s32 arg4, u16 arg5, s32 arg6);
void BattleHud_DrawMonInfoPanel(ActivePokemon* arg0, BattleMon* arg1, unk_D_84385790* arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 argA);
s32 BattleHud_DrawBorderTile(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8* arg4);
void func_88400100(void);
void BattleHud_DrawBoxBorder(s16 arg0, s16 arg1, s16 arg2, s16 arg3);
void BattleHud_DrawParticipantTimer(s16 arg0, s16 arg1);
void BattleHud_DrawBattleTimer(s16 arg0, s16 arg1);
void BattleHud_DrawPartyBallRow(ActivePokemon* arg0, s16 arg1, s16 arg2);
void BattleHud_DrawMonStatusBoxPlayer(ActivePokemon* arg0, s16 arg1, s16 arg2, u16 arg3, s32 arg4);
void BattleHud_DrawMonStatusBoxOpponent(ActivePokemon* arg0, s16 arg1, s16 arg2, u16 arg3, s32 arg4);
void BattleHud_DrawThreeOptionLabelBar(ActivePokemon* arg0, s16 arg1, s16 arg2, s32 arg3);
void BattleHud_DrawTwoOptionLabelBar(ActivePokemon* arg0, s16 arg1, s16 arg2, s32 arg3);
void BattleHud_DrawOneOptionLabelBar(ActivePokemon* arg0, s16 arg1, s16 arg2, s32 arg3);
void Battle_DrawRightAlignedText(s32 arg0, s32 arg1, char* arg2);
s32 BattleHud_DrawMovePpTextLTR(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 BattleHud_DrawMovePpTextRTL(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void BattleHud_DrawMoveSelectMenu(ActivePokemon* arg0, s16 arg1, s16 arg2, s32 arg3);
void BattleHud_DrawForfeitConfirmDialog(s16 arg0, s16 arg1, s16 arg2, s32 arg3);
void BattleHud_DrawPlainText(s16 arg0, s16 arg1, char* arg2);
void BattleHud_DrawDoublesRosterRow(ActivePokemon* arg0, TeamRoster* arg1, BattleMon* arg2, s32 arg3, s32 arg4, s32 arg5);
void BattleHud_DrawPartyRosterRow(ActivePokemon* arg0, TeamRoster* arg1, BattleMon* arg2, s32 arg3, s32 arg4, s32 arg5);
void BattleHud_DrawTeamStatusList(ActivePokemon* arg0, TeamRoster* arg1, s16 arg2, s16 arg3, s32 arg4);
void BattleHud_DrawDoublesTeamStatusList(ActivePokemon* arg0, s16 arg1, s16 arg2, s32 arg3);
void BattleHud_DrawCompactMonStatusBox(ActivePokemon* arg0, s16 arg1, s16 arg2, s32 arg3);
void BattleHud_DrawMessageBox(s32 arg0, s16 arg1, s16 arg2, char* arg3);
s32 Battle_DrawTextIfNonEmpty(char* arg0, s16 arg1, s16 arg2);
void BattleHud_DrawExpandingCaptionBox(unk_D_843901A0_4C8* arg0, s16 arg1, s16 arg2, Vec3f arg3);
void BattleHud_InitCaptionBoxPopup(unk_D_843901A0_4C8* arg0, s16 arg1, s16 arg2);
s32 BattleHud_UpdateCaptionBoxPopup(unk_D_843901A0_4C8* arg0, s16 arg1, s16 arg2);
void BattleHud_DrawExpandingCaptionBoxBlack(unk_D_843901A0_4C8* arg0, s16 arg1, s16 arg2, Vec3f arg3);
void BattleHud_InitCaptionBoxPopupBlack(unk_D_843901A0_4C8* arg0, s16 arg1, s16 arg2);
s32 BattleHud_UpdateCaptionBoxPopupBlack(unk_D_843901A0_4C8* arg0, s16 arg1, s16 arg2);
void BattleHud_DrawTextBox(s32 arg0, s16 arg1, s16 arg2, char* arg3);
void BattleHud_DrawTwoOptionCursorMenu(ActivePokemon* arg0, s16 arg1, s16 arg2, s32 arg3);
void BattleScene_DrawStripWipeIfActive(void);
void Battle_DrawScrollingTextureRect(s16 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5, s16 arg6, s16 arg7);
void Battle_DrawTiledStripSegment(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8* arg4, s32 arg5);
void Battle_DrawSpectatorModeBackgroundPanel(void);
void Battle_DrawSpectatorModeIndicator(void);
void Battle_DrawSpectatorModeScrollingText(void);
void BattleHud_DrawOwnSideStatus(ActivePokemon* arg0, ActivePokemonState* arg1);
void BattleHud_DrawOpponentSideStatus(ActivePokemon* arg0, ActivePokemonState* arg1);


void Battle_ClearAllMessageQueues(void);
void Battle_ClearMessageCursor(void);
void Battle_SimpleStringFormat(s8* arg0, s8* arg1, ...);
void Battle_QueueMessage(s8* arg0, s8 arg1);
void Battle_QueueStatusText(char* arg0, s32 arg1);
void func_884022A4(void);
void Battle_DrawCompactStatusBoxesIfVisible(void);
void Battle_QueueMoveCategoryUsedMessage(void);
void Battle_QueueMoveCategoryMessage(void);
void Battle_QueueMetronomeMoveMessage(void);
void BattleBox_Open(s32 arg0);
void BattleBox_Close(void);
void BattleBox_PlayTextBlip(s8* arg0);
void BattleBox_DrawMessage(unk_D_843901A0_4C8* arg0, s16 arg1, s16 arg2);
s32 BattleBox_SelectMessage(unk_D_843901A0_4C8* arg0);
void BattleBox_Update(s16 arg0, s16 arg1);
void BattleScene_ClearParticipantMessageBuffer(ActivePokemon* active_pokemon);
void BattleScene_BuildParticipantMessage(ActivePokemon* arg0, s32 arg1);
void BattleScene_RevealParticipantMessageChars(ActivePokemon* active_pokemon);
void BattleScene_TickHudTimers(void);
void Battle_InitMessageQueues(void);
void BattleScene_ResetMessageQueue(void);
void Battle_RenderHud(void);


s32 BattleScene_AreBothParticipantModelsCompact(void);
s32 BattleScene_SkipUnavailableBRollShot(UNUSED ActivePokemon* arg0, CameraNode* arg1);
s32 BattleScene_IsEitherActivePokemonFainted(UNUSED ActivePokemon* arg0, UNUSED CameraNode* arg1);
void BattleScene_BRollCameraSetupArenaOrbit(CameraNode* arg0);
void BattleScene_BRollCameraSetupRotatingArenaOverview(CameraNode* arg0);
void BattleScene_IntroCameraStep4Or6(CameraNode* arg0, s32 arg1);
void BattleScene_IntroCameraStep8Or10(CameraNode* arg0, s32 arg1);
void BattleScene_IntroCameraStep12Or14(CameraNode* arg0, s32 arg1);
void BattleScene_IntroCameraStep16(CameraNode* arg0);
void BattleScene_IntroCameraStep18(CameraNode* arg0);
void BattleScene_IntroCameraStep20(CameraNode* arg0);
void BattleScene_IntroCameraStep22Or24(CameraNode* arg0, s32 arg1);
void BattleScene_SelectNextBRollCameraShot(CameraNode* arg0);
void BattleScene_BRollCameraUpdateArenaOrbit(CameraNode* arg0);
void BattleScene_BRollCameraUpdateRotatingArenaOverview(CameraNode* arg0);
void BattleScene_IntroCameraAnimationHoldStep(CameraNode* arg0);
void BattleScene_BRollCameraUpdatePresetHold(CameraNode* arg0);
void BattleScene_IntroCameraWideHoldStep(CameraNode* arg0);
void BattleScene_IntroCameraHeightShotSwapStep(CameraNode* arg0);
void BattleScene_IntroCameraHeightShotStep(CameraNode* arg0);
void BattleScene_IntroCameraTimedHoldStep(CameraNode* arg0);
void BattleScene_IntroCameraFinalHoldStep(CameraNode* arg0);
void BattleScene_UpdateBRollCameraSequence(CameraNode* arg0);


f32 BattleScene_ScaleCameraDistance(ActivePokemon* arg0, f32 arg1, f32 arg2);
s32 BattleScene_AdvanceCameraSubstepCounter(s32 arg0);
s32 BattleScene_AdvanceCameraFrameCounter(s32 frame_limit);
s32 BattleScene_AdvanceCameraFrameCounterUntil(s32 arg0);
s32 BattleScene_IsCameraFrameCounterAtLeast(s32 arg0);
void BattleScene_SetActivePokemonIndex(s32 arg0);
void BattleScene_ResetCameraFrameCounter(void);
void BattleScene_ResetCameraSubstepCounter(void);
void BattleScene_SetCameraAtAndEyeFromAngles(CameraNode* camera, f32 x, f32 y, f32 z, f32 distance, s16 rotation_x, s16 rotation_y);
void BattleScene_GetOwnerCameraAnchor(ActivePokemon* arg0, Vec3f* arg1);
void BattleScene_GetOwnerBoneOrDefaultAnchor(ActivePokemon* pokemon, Vec3f* dest, s32 lookup_id);
void BattleScene_SetCameraModeAndStep(s32 camera_mode, s32 camera_step);
void BattleScene_SetCameraClipPlanes(CameraNode* arg0, f32 arg1, f32 arg2);
void BattleScene_SetCameraSubstate(s32 arg0, u16 arg1);
void BattleScene_ApplyCameraPhaseDefaults(void);
void BattleScene_SetDamageShakeAmplitude(ActivePokemon* active_pokemon);
void BattleScene_ApplyCameraShake(CameraNode* arg0);
void BattleScene_StartCameraShake(UNUSED ActivePokemon* active_pokemon);
s32 BattleScene_IsCameraAngleSettled(s16 arg0, s16 arg1);
s32 BattleScene_ApproachCameraRotationY(s32 arg0, s16 arg1, s16 arg2);
s32 BattleScene_ApproachCameraRotationYNoEyeUpdate(UNUSED CameraNode* arg0, s16 arg1, s16 arg2);
void BattleScene_SetCameraAnglesAndDistance(s16 arg0, s16 arg1, f32 arg2);
void BattleScene_SetCameraSendOutShot(CameraNode* arg0, s32 arg1);
void BattleScene_ClampCameraEyeFloor(CameraNode* arg0);
void BattleScene_UpdateCameraModelOffset(ActivePokemon* arg0, CameraNode* arg1);
void BattleScene_ClearCameraOffsetVectors(void);
void BattleScene_SetCameraAtFromAnchor(ActivePokemon* arg0, CameraNode* arg1, Vec3f arg2, s16 arg3, s16 arg4, f32 arg5, f32 arg6);
void BattleScene_SetCameraAtFromPosition(CameraNode* arg0, Vec3f arg1, s16 arg2, s16 arg3, f32 arg4, f32 arg5);
void BattleScene_SetCameraEyeFromPosition(CameraNode* arg0, Vec3f arg1, s16 arg2, s16 arg3, f32 arg4, f32 arg5);
void BattleScene_SetCameraEyeFromAt(CameraNode* arg0, s16 arg1, s16 arg2, f32 arg3, f32 arg4);
void BattleScene_SetCameraEyeAndStoreAngles(CameraNode* arg0, Vec3f arg1, s16 arg2, s16 arg3, f32 arg4, f32 arg5);
void BattleScene_SetCameraEyeAndStoreAnglesFromAt(CameraNode* arg0, s16 arg1, s16 arg2, f32 arg3, f32 arg4);
void BattleScene_CameraHelperNop(UNUSED CameraNode* arg0);
void BattleScene_SnapFloatPair(f32* arg0, f32* arg1);
void BattleScene_ApplyOwnerFramingAdjustments(CameraNode* arg0, ActivePokemon* arg1, UNUSED f32 arg2);
void BattleScene_RecomputeCameraDistance(CameraNode* arg0, ActivePokemon* arg1);
void BattleScene_ReframeAndRecomputeDistance(CameraNode* arg0, ActivePokemon* arg1);
void BattleScene_ReframeAndRecomputeDistanceForSwitch(CameraNode* arg0, ActivePokemon* arg1);
void BattleScene_ApplyOwnerFramingOnly(CameraNode* arg0, ActivePokemon* arg1);
void BattleScene_UpdateCameraTargetFromOwner(CameraNode* arg0, ActivePokemon* arg1);
s32 BattleScene_FrameCamera(CameraNode* arg0, ActivePokemon* arg1);
void BattleScene_ApproachCameraTargetFromOwner(CameraNode* arg0, ActivePokemon* arg1);
void BattleScene_UpdateCameraVerticalFraming(CameraNode* arg0, ActivePokemon* arg1);
void BattleScene_RecenterCameraOnOwner(CameraNode* arg0, ActivePokemon* arg1);
void BattleScene_ApproachCameraTarget(CameraNode* arg0, ActivePokemon* arg1);
void BattleScene_ApproachCameraZoom(CameraNode* arg0, ActivePokemon* arg1);
s32 BattleScene_ApproachCloseCameraShot(CameraNode* arg0, ActivePokemon* arg1);
s32 BattleScene_AnimateCameraPreset(CameraNode* arg0, ActivePokemon* arg1, s32 arg2, s32 arg3);
s32 BattleScene_AnimateCameraPresetToOwner(CameraNode* arg0, ActivePokemon* arg1);
void BattleScene_CameraPresetNop(UNUSED CameraNode* arg0);
void BattleScene_ApplyCameraPreset(CameraNode* arg0, ActivePokemon* arg1, s32 arg2);
void BattleScene_SetCameraPresetAtAngles(s16 arg0, s16 arg1, s16 arg2, s16 arg3);
void BattleScene_SetCameraPresetAtDistances(f32 arg0, f32 arg1);
void BattleScene_SetCameraPresetEyeAngles(s16 arg0, s16 arg1, s16 arg2, s16 arg3);
void BattleScene_SetCameraPresetEyeDistances(f32 arg0, f32 arg1);
void BattleScene_SetCameraPresetSmoothing(f32 arg0, f32 arg1);
void BattleScene_LoadCameraPreset(unk_D_86B0C160* arg0, CameraNode* arg1, ActivePokemon* arg2);
void BattleScene_LoadCameraPresetUnscaled(unk_D_86B0C160* arg0, CameraNode* arg1);
s32 BattleScene_AnimateCameraIntro(CameraNode* arg0, ActivePokemon* arg1);
s32 BattleScene_AreActivePokemonHeightsSeparated(UNUSED CameraNode* arg0);
void BattleScene_SetCameraActivePokemonHeightShot(CameraNode* arg0, s32 arg1);
s32 BattleScene_ApproachCameraActivePokemonHeightShot(CameraNode* arg0, s32 arg1);
void BattleScene_SetCameraOwnerShot(CameraNode* arg0, ActivePokemon* arg1);
void BattleScene_SetCameraOwnerWideShot(CameraNode* arg0, ActivePokemon* arg1);
void BattleScene_SetCameraPresetClose(CameraNode* arg0, ActivePokemon* arg1);
void BattleScene_SetCameraPresetAngledClose(CameraNode* arg0, ActivePokemon* arg1, s32 arg2);
void BattleScene_SetCameraPresetOffsetClose(CameraNode* arg0, ActivePokemon* arg1, s32 arg2);
void BattleScene_SetCameraPresetLowClose(CameraNode* arg0, ActivePokemon* arg1);
void BattleScene_SetCameraPresetWide(CameraNode* arg0, ActivePokemon* arg1, s32 arg2);
void BattleScene_SetCameraPresetWideStatic(CameraNode* arg0, ActivePokemon* arg1, s32 arg2);
void BattleScene_SetCameraPresetFromTable(CameraNode* arg0, ActivePokemon* arg1, s32 arg2, s32 arg3);
void BattleScene_CameraShotTargetStandard(CameraNode* arg0, ActivePokemon* arg1);
void BattleScene_CameraShotTargetAngled(CameraNode* arg0, ActivePokemon* arg1);
void BattleScene_CameraShotTargetHigh(CameraNode* arg0, ActivePokemon* arg1);
void BattleScene_CameraShotTargetLow(CameraNode* arg0, ActivePokemon* arg1);
void BattleScene_CameraShotTargetClose(CameraNode* arg0, ActivePokemon* arg1);
void BattleScene_SetCameraFollowPresetNear(CameraNode* arg0, ActivePokemon* arg1);
void BattleScene_SetCameraOwnerStandardShot(CameraNode* arg0, ActivePokemon* arg1);
void BattleScene_SelectCameraPreset(ActivePokemon* arg0, CameraNode* arg1, s32 arg2, s32 arg3);
void BattleScene_SelectCameraFollowPreset(ActivePokemon* arg0, CameraNode* arg1, s32 arg2);
void BattleScene_SelectCameraShot(ActivePokemon* arg0, CameraNode* arg1, s32 arg2);


void BattleScene_ApplyModelAnimationSlot5A(ActivePokemon* active_pokemon);
void BattleScene_ResetAnimationStep(void);
s32 BattleScene_AdvanceOwnerAnimation(ActivePokemon* active_pokemon);
s32 BattleScene_AdvanceOwnerAnimation98(ActivePokemon* active_pokemon);
s32 BattleScene_AdvanceOwnerAnimationAndClearFlags(ActivePokemon* active_pokemon);
s32 BattleScene_AdvanceDoublesOwnerAnimation(ActivePokemon* active_pokemon);
s32 BattleScene_AdvanceBothOwnerAnimations(void);
void BattleScene_ClearInactiveOwnerAnimationFlags(void);
void func_8110DC90(void);
s32 BattleScene_AnimateDisplayedHpToRuntime(ActivePokemon* active_pokemon);
void BattleScene_ClearPhaseFlag(void);
void BattleScene_SetPhaseFlag(void);
void BattleScene_SetPhase(UNUSED CameraNode* arg0, s32 arg1);
void BattleScene_SaveCameraFov(CameraNode* arg0);
void BattleScene_ResetCameraFov(CameraNode* arg0);
s32 BattleScene_GetAnimationTimingField0D(ActivePokemon* active_pokemon);
s32 BattleScene_GetMappedAnimationTimingField0D(ActivePokemon* active_pokemon);
s32 BattleScene_GetAnimationTimingField0E(ActivePokemon* active_pokemon);
s32 BattleScene_GetMappedAnimationTimingField0E(ActivePokemon* active_pokemon);
s32 BattleScene_GetCameraShotDuration(ActivePokemon* active_pokemon);
void Battle_StartTurn(void);
void BattleScene_InitializeSwitchActions(void);
s32 BattleScene_PrepareReplacementTransition(void);
void BattleScene_BeginBattlePhase(void);
s32 BattleScene_TransitionToPhaseFull(s32 arg0);
s32 BattleScene_TransitionToPhase(s32 arg0);
s32 BattleScene_TransitionToPhaseDuplicate(s32 arg0);
void BattleScene_SwitchActiveSideAndSetPhase(CameraNode* arg0);
void Battle_ActSecondAttacker(u8 arg0);
void BattleScene_PhaseResumeSaved(void);
void BattleScene_CleanupActionAndAdvance(void);
s32 BattleScene_HandleFaintStatusCompletion(void);
void BattleScene_CompleteActionPhase(void);
void BattleScene_ResolveDisplayedHpCompletion(CameraNode* arg0);
void BattleScene_UpdateDisplayedHpAndTransition(CameraNode* arg0);
void BattleScene_WaitForDisplayedHpAnimations(CameraNode* arg0);
s32 BattleScene_ActionPresentationTransitionCheck(void);
s32 BattleScene_ActionPresentationCleanupCheck(void);
s32 BattleScene_PrepareResidualStatusPresentation(void);
void BattleScene_UpdateActiveOwnerPointers(void);
void BattleScene_InitializeBattlePresentation(CameraNode* arg0);
void BattleScene_SendOutPresentationFinalize(CameraNode* arg0);
s32 BattleScene_ResetOwnerStatusPresentation(ActivePokemon* active_pokemon);
void BattleScene_FaintStepStart(CameraNode* arg0);
void BattleScene_FaintStepCollapse(CameraNode* arg0);
void BattleScene_FaintStepVanish(CameraNode* arg0);
void BattleScene_FaintStepFinishVanish(CameraNode* arg0);
void BattleScene_CompleteSendOutPresentation(CameraNode* arg0);
void func_82126A1C(UNUSED CameraNode* arg0);
void BattleScene_SetupSendOutOwnerShot(CameraNode* arg0);
void BattleScene_CompleteSendOutCameraFade(UNUSED CameraNode* arg0);
void BattleScene_CompleteSendOutExtendedFade(UNUSED CameraNode* arg0);
void BattleScene_AdvanceSendOutFollowupCamera(CameraNode* arg0);
void BattleScene_PhaseSendOut(CameraNode* arg0);
void BattleScene_FaintStepEnd(UNUSED CameraNode* arg0);
void BattleScene_PhaseFaint(CameraNode* arg0);
void BattleScene_ResetOwnerPresentationFlags(ActivePokemon* active_pokemon);
void BattleScene_InitializeIntroCamera(CameraNode* arg0);
void BattleScene_AdvanceIntroCamera(CameraNode* arg0);
void BattleScene_PhaseIntro(CameraNode* arg0);
void BattleScene_SetMonMoveResourceFlag(ActivePokemon* active_pokemon);
void BattleScene_PrepareMoveResourcePresentation(UNUSED CameraNode* arg0);
void BattleScene_SelectActionCameraPreset(CameraNode* arg0);
s32 BattleScene_AdvanceActionPresentationSetup(CameraNode* arg0);
void BattleScene_ActionSetupCameraStep(CameraNode* arg0);
void BattleScene_RefreshActionCameraPreset(CameraNode* arg0);
void BattleScene_SelectActionCameraPresetFromTiming(CameraNode* arg0, s32 arg1);
s32 BattleScene_ApplyActionCameraMode(CameraNode* arg0, s32 arg1);
void BattleScene_CleanupActionPresentation(UNUSED CameraNode* arg0);
s32 BattleScene_WaitForActionCameraDuration(UNUSED CameraNode* arg0);
void BattleScene_ActionSetupAnimationDefault(CameraNode* arg0);
void BattleScene_ActionSetupAnimationVariantA(CameraNode* arg0);
void BattleScene_ActionSetupAnimationVariantB(CameraNode* arg0);
void BattleScene_ActionSetupAnimationVariantC(CameraNode* arg0);
void BattleScene_ActionSetupAnimationVariantD(CameraNode* arg0);
void BattleScene_ActionSetupAnimationStep(CameraNode* arg0);
void BattleScene_StopSpecialOwnerAnimation(ActivePokemon* active_pokemon);
s32 BattleScene_IsSpecialOwnerAnimation(ActivePokemon* active_pokemon);
void BattleScene_CompleteHpUpdateTransition(CameraNode* arg0, s32* arg1, s32* arg2);
void BattleScene_RunBasicHpTransition(CameraNode* arg0);
void BattleScene_RunConditionalHpTransition(CameraNode* arg0);
void BattleScene_RunMoveEffectEndHpTransition(CameraNode* arg0);
void BattleScene_RunActionEffectHpTransition(CameraNode* arg0);
void func_8110DC98(void);
void func_8110E714(void);
void BattleScene_RunRepeatedHitHpTransition(CameraNode* arg0);
void BattleScene_ActionSetupFinalizeStep(CameraNode* arg0);
void BattleScene_PhaseCommand(CameraNode* arg0);
void BattleScene_Phase3(CameraNode* arg0);
s32 BattleScene_PhaseSelectMoveAnim(void);
void BattleScene_Phase7(CameraNode* arg0);
void BattleScene_PhaseBide(CameraNode* arg0);
void BattleScene_Phase27(CameraNode* arg0);
void BattleScene_PhaseExplosion(CameraNode* arg0);
void BattleScene_Phase28(CameraNode* arg0);
void BattleScene_Phase15(CameraNode* arg0);
void BattleScene_Phase25(CameraNode* arg0);
s32 BattleScene_EndStatusAnimationsAndCommit(ActivePokemon* active_pokemon);
void BattleScene_Phase29(CameraNode* arg0);
void BattleScene_Phase12(CameraNode* arg0);
void BattleScene_PhaseDigUnder(CameraNode* arg0);
void BattleScene_PhaseChargeUp(CameraNode* arg0);
void BattleScene_Phase17(CameraNode* arg0);
void BattleScene_PhaseConfusionSelfHit(CameraNode* arg0);
void BattleScene_Phase31(CameraNode* arg0);
void func_8210186C(void);
void BattleScene_Phase4(UNUSED CameraNode* arg0);
void BattleScene_Phase16(CameraNode* arg0);
void BattleScene_PhaseMoveMissed(CameraNode* arg0);
void BattleScene_PhaseResidualDamageWithoutMove(CameraNode* arg0);
void BattleScene_PhaseDrainDamage(CameraNode* arg0);
void BattleScene_Phase10(CameraNode* arg0);
void BattleScene_PhaseAttackHitRecoil(CameraNode* arg0);
void BattleScene_PhaseResidualDamageFaintCheck(CameraNode* arg0);
void BattleScene_ClearMonStatusAnimations(ActivePokemon* active_pokemon);
void BattleScene_PhaseWithdraw(CameraNode* arg0);
void BattleScene_PhaseWithdrawSwitch(CameraNode* arg0);
void BattleScene_UpdatePhase(CameraNode* arg0);


void BattleScene_IntroSetupCamera(CameraNode* arg0);
void BattleScene_IntroSendOutFirstMon(UNUSED CameraNode* arg0);
void BattleScene_IntroSendOutSecondMon(UNUSED CameraNode* arg0);
void BattleScene_IntroNarrowFov(CameraNode* arg0);
void BattleScene_IntroPanCamera(CameraNode* arg0);
void BattleScene_IntroWaitFirstMonAnim(UNUSED CameraNode* arg0);
void BattleScene_IntroRevealFirstMon(CameraNode* arg0);
void BattleScene_IntroFirstMonSettle(CameraNode* arg0);
void BattleScene_IntroRevealSecondMon(CameraNode* arg0);
void BattleScene_IntroSecondMonSettle(CameraNode* arg0);
void BattleScene_IntroStepNop(UNUSED CameraNode* arg0);
void BattleScene_IntroInitNop(void);
void BattleScene_UpdateIntroSequence(CameraNode* arg0);


void BattleScene_FinalPresentationFrameActiveOwner(CameraNode* arg0);
void BattleScene_FinalPresentationFrameOwner0(CameraNode* arg0);
void BattleScene_RunFinalPresentation(CameraNode* arg0, UNUSED ActivePokemon* arg1, UNUSED ActivePokemon* arg2);
void BattleScene_AllocateMemory(void);
void BattleScene_UpdateCameraDefaultModeNoop(UNUSED CameraNode* arg0);
void BattleScene_UpdateCameraOwner0FramingModeNoop(UNUSED CameraNode* arg0);
void BattleScene_AvoidDegenerateCameraLookAt(CameraNode* arg0);
void BattleScene_TickCameraSubstateDefault(CameraNode* arg0);
void BattleScene_TickCameraSubstateStripWipe(CameraNode* arg0);
void BattleScene_TickCameraSubstate(CameraNode* arg0);
u16 BattleScene_IsOwnerInViewWedge(ActivePokemon* arg0, CameraNode* arg1, ActivePokemon* a2, s16 arg3, f32 arg4);
u16 BattleScene_IsOwnerInViewWedgeAlt(ActivePokemon* arg0, CameraNode* arg1, ActivePokemon* a2, s16 arg3, f32 arg4);
void BattleScene_UpdateBothOwnersVisibilityCulling(CameraNode* arg0);
void BattleScene_UpdateOpponentVisibilityCulling(CameraNode* arg0);
void func_8210F4E0(void);
void BattleScene_ShowBothOwners(void);
void BattleScene_HideOpponentOwner(void);
void BattleScene_HideActiveOwner(void);
void BattleScene_HideFaintedOwners(void);
void BattleScene_UpdateOwnerVisibilitySingle(CameraNode* arg0);
void BattleScene_UpdateOwnerVisibilityDouble(CameraNode* arg0);
void BattleScene_Update(CameraNode* arg0);
s32 BattleScene_Dispatch(s32 arg0, CameraNode* arg1);


void BattleAnim_StartFreezeStatusAnimation(ActivePokemon* active_pokemon);
void BattleAnim_RestoreBaseModelAnimation(ActivePokemon* active_pokemon);
void BattleAnim_ClearFreezeStatusAnimation(ActivePokemon* active_pokemon);
void BattleAnim_ResetFreezeStatusAndRestoreAnimation(ActivePokemon* active_pokemon);
void BattleAnim_ClearFreezeStatusAnimationIfThawed(ActivePokemon* active_pokemon);
void BattleAnim_UpdateSleepStatusAnimation(ActivePokemon* active_pokemon);
s32 BattleAnim_EndSleepStatusAnimation(s32 arg0);
void BattleAnim_ClearSleepStatusAnimation(ActivePokemon* active_pokemon);


void BattleAnim_PlaySoundEffect1(void);
void BattleAnim_PlaySoundEffect2(void);
void BattleAnim_PlaySoundEffect3(void);
void BattleAnim_PlaySoundEffect8(void);
void BattleAnim_PlayOwnerCry(ActivePokemon* active_pokemon, s16 species);
void BattleAnim_PlaySpeciesSequence33(ActivePokemon* active_pokemon);
void Battle_TriggerTrainerPresentationCue(ActivePokemon* active_pokemon);
void BattleAnim_PlaySpeciesReactionSound(ActivePokemon* active_pokemon, BattleMonRuntime* runtime, s32 reaction_kind);
void BattleScene_ConfigureAudioChannelGroupsByTeam(void);
void BattleScene_ConfigureAudioChannelGroupCounts(void);
void BattleScene_SelectBattleMusic(void);
void BattleScene_StartBattleMusic(void);
void BattleAnim_PlayBattleSequenceById(ActivePokemon* active_pokemon, s32 sequence_id);
void BattleAnim_RunEffectInitStart(s16 arg0);
void BattleAnim_RunEffectInitEnd(s16 arg0);
void BattleAnim_RegisterEffectSlot(func_D_84390300 arg0, func_D_84390320 arg1);
void BattleAnim_RunEffectList(s32 arg0, s32 arg1, s32 arg2);
void BattleAnim_ProcessQueuedEffects(void);
void BattleAnim_UpdateFrame(UNUSED CameraNode* arg0);
void BattleAnim_SetQueuedEffectList(u8 effect_list_index);
u8 BattleAnim_GetCurrentEffectList(void);
void BattleAnim_SetQueuedResourceListId(u8 arg0);
u8 BattleAnim_GetQueuedResourceListId(void);
s16 BattleAnim_GetQueuedMoveId(void);
void BattleAnim_QueueMoveEffect(s32 arg0, s32 arg1, s32 arg2, s16 arg3, s16 arg4);
void BattleAnim_QueueMoveEffectScript(s32 move_id, ActivePokemon* user, ActivePokemon* user_fallback, s16 default_anchor, s16 alternate_anchor);
void BattleAnim_QueueMoveEffectEnd(s32 move_id, ActivePokemon* user, ActivePokemon* user_fallback, s16 default_anchor, s16 alternate_anchor);
void BattleAnim_QueueChargingMoveEffectScript(s32 move_id, ActivePokemon* user, ActivePokemon* user_fallback, s16 default_anchor, s16 alternate_anchor);
void BattleAnim_QueueEffectList3(s32 move_id, ActivePokemon* user, ActivePokemon* user_fallback, s16 default_anchor, s16 alternative_anchor);
void BattleAnim_QueueEffectList6(s32 move_id, ActivePokemon* owner);
void BattleAnim_QueueEffectList5(s32 arg0, ActivePokemon* arg1);
void BattleAnim_QueueEffectList6Alt(s32 arg0, ActivePokemon* arg1);
void BattleAnim_QueueEffectList9(s32 arg0);
void BattleAnim_QueueEffectList(u8 arg0, s32 arg1);
void BattleAnim_StopOwnerCategoryParticles(u8 category, ActivePokemon* owner);
void BattleAnim_RegisterAssetTable(arg1_func_80019420* arg0);
void BattleAnim_ResetAssetTable(void);
void BattleAnim_BuildResourceListForMove(s16 arg0);
void BattleAnim_LoadMoveResourceList(BattleSessionTeams* battle_session_teams, s16 move_id);
void BattleAnim_LoadModeResourceList(BattleSessionTeams* battle_session_teams, s16 mode);
void BattleAnim_RegisterAllAssetTables(void);
void BattleAnim_RegisterAssetTablesForSession(BattleSessionTeams* battle_session_teams);
void BattleAnim_ResetDisplayContexts(void);
Particle* BattleAnim_GetOwnerContextParticle(DisplayObject* arg0);
DisplayObject* BattleAnim_AllocOwnerDisplayContext(Particle* arg0);
void BattleAnim_FreeOwnerDisplayContext(DisplayObject* arg0);
DisplayObject* BattleAnim_AllocParticleDisplayContext(Particle* arg0);
void BattleAnim_FreeParticleDisplayContext(DisplayObject* arg0);
void BattleAnim_InitModelWithAnim(DisplayObject* arg0, s16 arg1, s16 arg2);
void BattleAnim_SetModelAnimFrame(DisplayObject* arg0, s16 arg1);
void BattleAnim_InitModel(DisplayObject* arg0, s16 arg1);
void BattleAnim_BindModelAnim(DisplayObject* arg0, s16 arg1);
void BattleAnim_BindModelAnimReversed(DisplayObject* arg0, s16 arg1);
s32 BattleAnim_IsModelAnimComplete(DisplayObject* arg0);
void BattleAnim_UpdateEffectCallbacks(UNUSED CameraNode* arg0);
void BattleAnim_DrawEffectCallbacks(UNUSED CameraNode* arg0);
void BattleAnim_UpdateCamera(CameraNode* arg0);
s32 BattleAnim_DispatchPresentation(s32 arg0, CameraNode* arg1);
void BattleAnim_Initialize(void);
void BattleAnim_Reset(void);
void BattleAnim_GetPointAlongCameraRay(Vec3f* arg0, f32 arg1);
void BattleAnim_GetCameraEyeAngles(s16* arg0, s16* arg1);
void BattleAnim_GetCameraEyeYaw(s16* arg0);
void BattleAnim_GetCameraLookAngles(s16* arg0, s16* arg1);
void BattleAnim_GetCameraLookYaw(s16* arg0);
void BattleAnim_GetCameraStoredAngles76(s16* arg0, s16* arg1);
void BattleAnim_GetCameraStoredYaw78(s16* arg0);
void BattleAnim_GetCameraStoredAngles70(s16* arg0, s16* arg1);
void BattleAnim_GetCameraStoredYaw72(s16* arg0);


void BattleAnim_InitParticleSystem(void);
BattleAnimEffectSlot* BattleAnim_AllocEffectSlot(void);
void BattleAnim_FreeEffectSlot(BattleAnimEffectSlot* arg0);
void BattleAnim_InitializeParticleChain(Particle* arg0, Vec3f arg1, Vec3s arg2, s32 arg3, s32 arg4);
void BattleAnim_CloneParticleState(Particle* arg0, Particle* arg1, ParticleUpdateCallback arg2, ParticleDescriptor* arg3, s32 arg4);
void BattleAnim_EmitParticleBurst(Particle* arg0, ParticleUpdateCallback arg1, ParticleDescriptor* arg2, s16 arg3);
void BattleAnim_EmitParticleBurstWithMetadata(Particle* arg0, ParticleUpdateCallback arg1, ParticleDescriptor* arg2, s16 arg3, s16 arg4, s16 arg5);
Particle* BattleAnim_CreateProceduralParticle(s16 arg0, s16 arg1, s32 arg2, f32 arg3);
void BattleAnim_ReleaseParticleModel(Particle* arg0);
void BattleAnim_DestroyParticle(Particle* arg0);
void BattleAnim_InitializeParticleAnchor(Particle* arg0);
void BattleAnim_UpdateParticleAnchor(Particle* arg0);
void BattleAnim_UpdateParticleCameraScale(Particle* arg0);
void BattleAnim_UpdateOrDestroyParticle(Particle* arg0);
void BattleAnim_UpdateParticlePool(void);
void BattleAnim_InitializeParticleFromEffect(Particle* arg0, ActivePokemon* arg1, BattleAnimEffectSlot* arg2, s16 arg3);
void BattleAnim_SpawnEffectParticles(BattleAnimEffectSlot* arg0, s32 arg1);
void BattleAnim_SpawnStandardParticles(s8 *arg0);
void BattleAnim_SpawnBatchedParticles(s8* arg0);
void BattleAnim_SpawnSingleParticle(BattleAnimEffectSlot* arg0);
void BattleAnim_DispatchParticleEmission(BattleAnimEffectSlot* arg0);
void BattleAnim_TickEffectSlots(void);
void BattleAnim_UpdateEffects(void);
void BattleAnim_CleanupEffectsRetainingCategories47(void);
void BattleAnim_CleanupEffectsRetainingCategory4(void);
s32 BattleAnim_GetMoveFailedFlag(void);
void BattleAnim_UpdateMoveFailedFlag(void);
void BattleAnim_ClearEffectCallbacks(void);
s32 BattleAnim_IsEffectSpawningEnabled(void);
void BattleAnim_DisableEffectSpawning(void);
void BattleAnim_EnableEffectSpawning(void);
void BattleAnim_DisableEffectSpawningAlias(void);
void BattleAnim_CleanupEffects(s32 cleanup_mode);
void BattleAnim_StopParticlesForOwnerCategory(u8 arg0, ActivePokemon* arg1);
void BattleAnim_ResetSpawnDelay(void);
void BattleAnim_SetSpawnDelay(s32 arg0);
void BattleAnim_AddSpawnDelay(s32 arg0);
void BattleAnim_ResetSpawnDelayAlias(void);
BattleAnimEffectSlot* BattleAnim_CreateEffectSlot(s32 arg0, s32 arg1, s8 arg2, func_unk_D_8140E724 arg3, ParticleDescriptor* arg4, ActivePokemon* arg5, s16 arg6, s16 arg7, u8 arg8, u8 arg9, u8 argA, u8 argB);
BattleAnimEffectSlot* BattleAnim_CreateEffectSlotForCurrentOwner(s32 arg0, func_unk_D_8140E724 arg1, ParticleDescriptor* arg2, s16 arg3, s16 arg4, u8 arg5, u8 arg6, u8 arg7, u8 arg8);
BattleAnimEffectSlot* BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(s32 arg0, s32 arg1, s8 arg2, func_unk_D_8140E724 arg3, ParticleDescriptor* arg4, s16 arg5, s16 arg6, u8 arg7, u8 arg8, u8 arg9, u8 argA);
BattleAnimEffectSlot* BattleAnim_SpawnGlobalTintColorFadeDetach(s32 arg0, s16 arg1, u8 arg2);
BattleAnimEffectSlot* BattleAnim_SpawnWhiteHueChange(s32 arg0, s16 arg1, s16 arg2, u8 arg3, u8 arg4);
BattleAnimEffectSlot* BattleAnim_SpawnDescriptor25AlphaHoldFadeOutFullAlpha(s32 arg0, s16 arg1, s16 arg2, u8 arg3);
BattleAnimEffectSlot* BattleAnim_SpawnDescriptor25AlphaHoldFadeOut(s32 arg0, s16 arg1, s16 arg2, u8 arg3, u8 arg4);
BattleAnimEffectSlot* BattleAnim_SpawnDescriptor25AlphaHoldFadeOutRepeating(s32 arg0, s32 arg1, s8 arg2, s16 arg3, s16 arg4, u8 arg5, u8 arg6);
BattleAnimEffectSlot* BattleAnim_SpawnDescriptor25AlphaFadeInHoldFullAlpha(s32 arg0, s16 arg1, s16 arg2, u8 arg3);
BattleAnimEffectSlot* BattleAnim_SpawnDescriptor25AlphaFadeInHold(s32 arg0, s16 arg1, s16 arg2, u8 arg3, u8 arg4);
BattleAnimEffectSlot* BattleAnim_SpawnDescriptor25AlphaFadeInHoldRepeating(s32 arg0, s32 arg1, s8 arg2, s16 arg3, s16 arg4, u8 arg5, u8 arg6);
BattleAnimEffectSlot* BattleAnim_SpawnDescriptor25AlphaHoldDetachFullAlpha(s32 arg0, s16 arg1, u8 arg2);
BattleAnimEffectSlot* BattleAnim_SpawnDescriptor25AlphaHoldDetach(s32 arg0, s16 arg1, u8 arg2, u8 arg3);
BattleAnimEffectSlot* BattleAnim_SpawnDescriptor25AlphaHoldDetachRepeating(s32 arg0, s32 arg1, s8 arg2, s16 arg3, u8 arg4, u8 arg5);
BattleAnimEffectSlot* BattleAnim_SpawnDescriptor25PaletteFadeOut(s32 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4);
BattleAnimEffectSlot* BattleAnim_SpawnDescriptor25PaletteFadeIn(s32 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4);
BattleAnimEffectSlot* BattleAnim_SpawnOwnerModelTintRampDetach(s32 arg0, u8 arg1, s16 arg2, s16 arg3, s16 arg4);
BattleAnimEffectSlot* BattleAnim_SpawnOwnerModelTintPulseDetach(s32 arg0, s16 arg1, u8 arg2, s16 arg3, s16 arg4, s16 arg5);
BattleAnimEffectSlot* BattleAnim_SpawnOwnerModelTintHoldFadeDetach(s32 arg0, s16 arg1, u8 arg2, s16 arg3, s16 arg4);
BattleAnimEffectSlot* BattleAnim_SpawnBeamBoomWaterfallHueChange(s32 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4);
BattleAnimEffectSlot* BattleAnim_SpawnOwnerModelTintPaletteApproachInactiveAlt(s32 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4);
BattleAnimEffectSlot* BattleAnim_SpawnIceBeamBlizzardHitHueChange(s32 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5);
BattleAnimEffectSlot* BattleAnim_SpawnOwnerModelTintPaletteCycleVariant(s32 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5);
BattleAnimEffectSlot* BattleAnim_SpawnDrainFlameHueChange(s32 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5);
BattleAnimEffectSlot* BattleAnim_SpawnOwnerModelTintRandomPaletteCycle(s32 arg0, s16 arg1, u8 arg2);
BattleAnimEffectSlot* BattleAnim_SpawnRainbowHueChange(s32 arg0, s16 arg1, s16 arg2, u8 arg3);
BattleAnimEffectSlot* BattleAnim_SpawnInvisibility(s32 arg0, s16 arg1, s16 arg2, s16 arg3);
BattleAnimEffectSlot* BattleAnim_SpawnOwnerModelAlphaFadeFullPreset(s32 arg0);
BattleAnimEffectSlot* BattleAnim_SpawnOwnerModelAlphaFadeZeroStartPreset(s32 arg0);
BattleAnimEffectSlot* BattleAnim_SpawnCategory17MarkerSlot(s32 arg0, u8 arg1);
BattleAnimEffectSlot* BattleAnim_SpawnCategory19MarkerSlot(s32 arg0, u8 arg1);
void BattleAnim_EffectStartNop(void);
void BattleAnim_EffectEndNop(void);
void BattleAnim_SetEffectState(s32 arg0);
void BattleAnim_ClearEffectStateFlag(void);
s32 BattleAnim_GetEffectStateFlag(void);
s32 BattleAnim_IsCurrentOwnerSpecies(s32 arg0);
s32 BattleAnim_GetSecondaryOwnerSpecies(void);
s32 BattleAnim_GetTertiaryOwnerSpecies(void);
void BattleAnim_GetOwnerBonePosition(ActivePokemon* arg0, s16 arg1, Vec3f* arg2);
void BattleAnim_GetCurrentOwnerBonePosition(Vec3f* arg0);
void BattleAnim_GetSecondaryOwnerBonePosition(Vec3f* arg0);
void BattleAnim_GetTertiaryOwnerBonePosition(Vec3f* arg0);
void BattleAnim_GetSecondaryOwnerAnchorPosition(Vec3f* arg0);
void BattleAnim_GetTertiaryOwnerBone9Position(Vec3f* arg0);
void BattleAnim_GetOwnerModelBoundsScaled(ActivePokemon* arg0, Vec3f* arg1);
f32 BattleAnim_GetSpeciesBaseScale(ActivePokemon* active_pokemon);
f32 BattleAnim_GetOwnerModelScale(ActivePokemon* active_pokemon);
void BattleAnim_GetOwnerSpeciesBaseScaleAlias(ActivePokemon* active_pokemon);
f32 BattleAnim_GetSecondaryOwnerModelScale(void);
void BattleAnim_GetSecondaryOwnerSpeciesBaseScale(void);
f32 BattleAnim_GetTertiaryOwnerModelScale(void);
void BattleAnim_GetTertiaryOwnerSpeciesBaseScale(void);
s32 BattleAnim_GetCameraContext(void);
Particle* BattleAnim_SpawnSecondaryOwnerParticle(Vec3f arg0, u8 arg1);
void BattleAnim_SetParticlePosition(Particle* arg0, Vec3f arg1);
void BattleAnim_MarkParticleInactive(Particle* arg0);
s16 BattleAnim_GetParticleAngleYToTertiaryOwner(Particle* arg0);
void BattleAnim_SetGlobalTintFromParticle(Particle* arg0);
void BattleAnim_LoadGlobalTintToParticle(Particle* arg0);


void BattleAnim_InitStingerTrailColor(Particle* arg0);
void BattleAnim_UpdateNeedleBlueFadeGrow(s8 *arg0);
void BattleAnim_InitStingerTrailColorDuplicate(Particle* arg0);
void BattleAnim_UpdateSecondaryOwnerParticleBlueGrow(s8 *arg0);
void BattleAnim_InitStingerMoveParticle(Particle* arg0, u8 arg1);


s32 BattleAnim_DrawAsset95Ia8Billboard(Particle* arg0, CameraNode* arg1);
void BattleAnim_DrawAsset76Ia8FrameWithAsset77I4Overlay(Particle* arg0, CameraNode* arg1);
void BattleAnim_DrawFlameHit(Particle* arg0, CameraNode* arg1);
void BattleAnim_DrawFlameUse(Particle* arg0, CameraNode* arg1);
void BattleAnim_DrawSleepMoveAnimatedI4(Particle* arg0, CameraNode* arg1);
s32 BattleAnim_DrawDigRocks(Particle* arg0, UNUSED CameraNode* arg1);
void BattleAnim_DrawAssets27And28LayeredI4QuadVariantA(Particle* arg0, UNUSED CameraNode* arg1);
void BattleAnim_DrawAssets27And28LayeredI4QuadVariantB(Particle* arg0, UNUSED CameraNode* arg1);
void BattleAnim_DrawMistLightest(Particle* arg0, UNUSED CameraNode* arg1);
void BattleAnim_DrawAsset87AnimatedI4Quad(Particle* arg0, UNUSED CameraNode* arg1);
void BattleAnim_DrawI4AtlasYScaled(Particle* arg0, u8* arg1);
void BattleAnim_DrawAsset19I4AtlasYScaled(Particle* arg0, UNUSED CameraNode* arg1);
void BattleAnim_DrawAsset5EI4AtlasYScaled(Particle* arg0, UNUSED CameraNode* arg1);
void BattleAnim_DrawAsset1AFrameI4Quad(Particle* arg0, UNUSED CameraNode* arg1);
void BattleAnim_DrawAsset1CRgba16Quad(Particle* arg0, UNUSED CameraNode* arg1);
void BattleAnim_DrawAsset1ERgba16Quad(Particle* arg0, UNUSED CameraNode* arg1);
void BattleAnim_DrawAssetC3Rgba16Quad(Particle* arg0, UNUSED CameraNode* arg1);
void BattleAnim_DrawAsset1DRotatedI4Quad(Particle* arg0, UNUSED CameraNode* arg1);
void BattleAnim_DrawParticleNoop(UNUSED Particle* arg0, UNUSED CameraNode* arg1);
void BattleAnim_DrawAsset13FrameI4YScaledQuadA(Particle* arg0, UNUSED CameraNode* arg1);
void BattleAnim_DrawAsset13FrameI4YScaledQuadB(Particle* arg0, UNUSED CameraNode* arg1);
void BattleAnim_DrawAsset13FrameI4YScaledQuadC(Particle* arg0, UNUSED CameraNode* arg1);
void BattleAnim_DrawAsset13FrameI4ModelQuadA(Particle* arg0, CameraNode* arg1);
void BattleAnim_DrawAsset13FrameI4ModelQuadB(Particle* arg0, CameraNode* arg1);
void BattleAnim_DrawAsset13FrameI4ModelQuadC(Particle* arg0, CameraNode* arg1);
void BattleAnim_DrawAsset1BI4TriangleA(Particle* arg0, UNUSED CameraNode* arg1);
void BattleAnim_DrawAsset1BI4TriangleB(Particle* arg0, UNUSED CameraNode* arg1);
void BattleAnim_DrawAsset13FrameDiv2I4Quad(Particle* arg0, UNUSED CameraNode* arg1);
void BattleAnim_DrawAsset18FrameI4ModelQuad(Particle* arg0, CameraNode* arg1);
void BattleAnim_DrawAssetA9I4XYScaledQuad(Particle* arg0, UNUSED CameraNode* arg1);
void BattleAnim_DrawParticleFullScreenColorOverlay(Particle* arg0, UNUSED CameraNode* arg1);


void BattleAnim_SetupBackgroundRecolor(Particle* arg0);
void BattleAnim_CallbackGlobalTintColorFadeDetach(Particle* arg0);
void BattleAnim_SetupTargetHueChange(Particle* arg0);
void BattleAnim_CallbackOwnerModelTintRampDetach(Particle* arg0);
void BattleAnim_SetupUserHueChange(Particle* arg0);
void BattleAnim_RunUserHueChange(Particle* arg0);
void func_82113660(void);
void BattleAnim_CallbackOwnerModelTintHoldFadeDetach(Particle* arg0);
void BattleAnim_SetupOwnerModelTintPaletteApproachInactive(Particle* arg0);
void BattleAnim_CallbackOwnerModelTintPaletteApproachInactive(Particle* arg0);
void BattleAnim_SetupOwnerModelTintPaletteApproach(Particle* arg0);
void BattleAnim_CallbackOwnerModelTintPaletteApproach(Particle* arg0);
void BattleAnim_SetupIceBeamBlizzardHitHueChange(Particle* arg0);
void BattleAnim_RunIceBeamBlizzardHitHueChange(Particle* arg0);
void BattleAnim_SetupOwnerModelTintPaletteApproachRampDown(Particle* arg0);
void BattleAnim_CallbackOwnerModelTintPaletteApproachRampDown(Particle* arg0);
void BattleAnim_SetupDrainFlameHueChange(Particle* arg0);
void BattleAnim_CallbackOwnerModelTintPaletteFade(s8 *arg0);
void BattleAnim_SetupOwnerModelTintRandomPaletteCycle(Particle* arg0);
void BattleAnim_CallbackOwnerModelTintRandomPaletteCycle(Particle* arg0);
void BattleAnim_SetupRainbowHueChange(Particle* arg0);
void BattleAnim_RunRainbowHueChange(Particle* arg0);
void BattleAnim_SetupInvisibility(Particle* arg0);
void BattleAnim_CallbackOwnerModelAlphaFade(s8 *arg0);
void BattleAnim_SetupParticleRecolorTransparent(Particle* arg0);
void BattleAnim_CallbackStartEffect125OwnerColorAlphaFade(Particle* arg0);
void BattleAnim_SetupWhiteHueChange(Particle* arg0);
void BattleAnim_RunWhiteHueChange(Particle* arg0);
void BattleAnim_SetupDescriptor25AlphaHoldFadeOut(s8 *arg0);
void BattleAnim_RunFullScreenHueChange(Particle* arg0);
void BattleAnim_SetupDescriptor25AlphaFadeInHold(Particle* arg0);
void BattleAnim_RunPokemonAndFullScreenHueChange(Particle* arg0);
void BattleAnim_SetupDescriptor25AlphaHoldDetach(Particle* arg0);
void BattleAnim_CallbackDescriptor25AlphaHoldDetach(s8 *arg0);
void BattleAnim_SetupDescriptor25PaletteFadeOut(Particle* arg0);
void BattleAnim_CallbackDescriptor25PaletteFadeOut(Particle* arg0);
void BattleAnim_SetupDescriptor25PaletteFadeIn(Particle* arg0);
void BattleAnim_CallbackDescriptor25PaletteFadeIn(Particle* arg0);


void BattleAnim_SetupFireBreathFlameFading(Particle* arg0, s16 arg1);
void BattleAnim_ContinueFireBreathFlameFading(Particle* arg0);
void BattleAnim_RunFireBreathFlameFading(Particle* arg0);
void BattleAnim_SetupUnusedDescriptor4FColorCycleScaleFadeVariant(Particle* arg0);
void BattleAnim_MotionUnusedDescriptor4FColorCycleScaleFadeVariant(Particle* arg0);
void BattleAnim_CallbackUnusedDescriptor4FColorCycleScaleFadeVariant(Particle* arg0);
void BattleAnim_SetupFireBreathFlameGeometry(Particle* arg0);
void BattleAnim_ContinueFireBreathFlameGeometry(Particle* arg0);
void BattleAnim_FlameAlphaScaleFade(Particle* arg0);
void BattleAnim_SetupFireBreathFlameColoration(Particle* arg0, s16 arg1);
void BattleAnim_ContinueFireBreathFlameColoration(Particle* arg0);
void BattleAnim_FlameRotatingFallColorCycle(Particle* arg0);
void BattleAnim_SetupExpandingHitSpark(Particle* arg0);
void BattleAnim_RunExpandingHitSpark(Particle* arg0);
void BattleAnim_RunPsybeamHitSparkDrift(Particle* arg0);
void BattleAnim_CallbackUnusedGrowFadeVariant(Particle* arg0);
void BattleAnim_SetupOscillatingFlameUnderneathPokemon(Particle* arg0);
void BattleAnim_CallbackStartEffect104DelayedSpiralFade(Particle* arg0);
void BattleAnim_SetupFireSpinFlame(Particle* arg0);
void BattleAnim_CallbackEndEffect29Descriptor02RotatingScaleGrow(Particle* arg0);
void BattleAnim_SetupUnusedVariant2(Particle* arg0);
void BattleAnim_CallbackUnusedVariant2(Particle* arg0);
void BattleAnim_SetupEmberProjectileAfterimages(Particle* arg0);
void BattleAnim_CallbackStartEffect22Descriptor4ABurstChild(Particle* arg0);
void BattleAnim_SetupEmberProjectile(Particle* arg0);
void BattleAnim_CallbackStartEffect22Descriptor46BurstEmitter(Particle* arg0);
void BattleAnim_SetupEmberBurstEmitter(Particle* arg0);
void BattleAnim_CallbackStartEffect22Descriptor34RotatingPaletteScaleFade(Particle* arg0);
void BattleAnim_SetupEmberUseEffect(Particle* arg0);
void BattleAnim_RunEmberUseEffect(Particle* arg0);
void BattleAnim_GetExplosionParticleColor(Particle* arg0, u8 arg1);
void func_82116D20(void);
void BattleAnim_FirePunchEmberEggBombColorChange(Particle* arg0);
void BattleAnim_SetupBackgroundBombExplosion(Particle* arg0);
void BattleAnim_RunBackgroundBombExplosion(Particle* arg0);
void BattleAnim_SetupBoomSmallExplosion(Particle* arg0);
void BattleAnim_CallbackEndEffects81And82Descriptor46AnimatedFade(Particle* arg0);
void BattleAnim_SetupEggBombHitEffect(Particle* arg0);
void BattleAnim_CallbackEndEffect40Descriptor48SpreadScaleAlphaFade(s8 *arg0);
void BattleAnim_SetupSecondaryBombExplosion(Particle* arg0);
void BattleAnim_CallbackEndEffect40Descriptor3DSpreadRisingColorFade(Particle* arg0);
void BattleAnim_SetupEmberHitFireball(Particle* arg0);
void BattleAnim_CallbackEndEffect56Descriptor46RisingScaleAlphaFade(s8 *arg0);
void BattleAnim_SetupEmberHitSmoke(Particle* arg0);
void BattleAnim_EmberSpreadScaleAlphaRise(Particle* arg0);
void BattleAnim_SetupFirePunchLingeringHitSpark(Particle* arg0);
void BattleAnim_CallbackEndEffects54And56Descriptor3DRisingColorScaleFade(Particle* arg0);
void BattleAnim_SetupAfterImpactSmoke(Particle* arg0);
void BattleAnim_CallbackEndEffects40And54Descriptor46SpreadScaleFade(Particle* arg0);
void BattleAnim_SetupFirePunchHitEffect(Particle* arg0);
void BattleAnim_CallbackEndEffect54Descriptor46DelayedColorAlphaFade(Particle* arg0);
void BattleAnim_SetupFlamethrowerHitRotation(Particle* arg0, s16 arg1, s16 arg2);
void BattleAnim_RunFlamethrowerHitRotation(Particle* arg0, s32 arg1);
void BattleAnim_RunFlamethrowerHitRotationWeak(Particle* arg0);
void BattleAnim_RunFlamethrowerHitRotationStrong(Particle* arg0);
void BattleAnim_SetupFireBlastHitFrontFlames(Particle* arg0);
void BattleAnim_ContinueFireBlastHitFrontFlames(Particle* arg0);
void BattleAnim_CallbackEndEffects15And22And59Descriptor3DRotatingAlphaScaleFade(Particle* arg0);
void BattleAnim_SetupDaimonji(Particle* arg0);
void BattleAnim_ContinueDaimonji(Particle* arg0);
void BattleAnim_RunDaimonji(Particle* arg0);
void BattleAnim_SetupDaimonjiColoration(Particle* arg0);
void BattleAnim_CallbackEndEffect59Descriptor4FColorScaleFade(Particle* arg0);
void ParticleEffect_InitSetRotatingPaletteNoTint(void);
void BattleAnim_InitializeEmberHit(void);
void ParticleEffect_InitSetTintRampDelayedColorFade(void);
void ParticleEffect_InitSmokeSetWithMarker(void);
void BattleAnim_InitializeFlamethrowerHit(void);
void ParticleEffect_InitSmokeSetTexture1(void);
void BattleAnim_InitializeDragonRageHit(void);
void ParticleEffect_InitSmokeSetLongDuration(void);
void ParticleEffect_InitFireSet(void);
void func_82116D28(void);
void ParticleEffect_InitNoop(void);
void BattleAnim_InitializeEggBombHit(void);
void func_8211F3E4(void);
void BattleAnim_InitializeFireBlastHit(void);


void BattleAnim_SetupSurfHitSpark(Particle* arg0);
void BattleAnim_CallbackEndEffect16Descriptor45DelayedRotatingMotion(Particle* arg0);
void BattleAnim_SetupBubbleBubbles(Particle* arg0, s16 arg1);
void BattleAnim_RunBubbleBubbles(Particle* arg0);
void BattleAnim_SetupBubbleBeamBubblesSlow(Particle* arg0);
void BattleAnim_ContinueBubbleBeamBubblesSlow(Particle* arg0);
void BattleAnim_CallbackStartEffects77And120Descriptor45DeceleratingSparkFade(Particle* arg0);
void BattleAnim_SetupBubbleBeamBubblesFast(Particle* arg0);
void BattleAnim_CallbackStartEffects77And120Descriptor45AimedSparkFade(Particle* arg0);
void BattleAnim_SetupUnusedRotatingSparkVariant(Particle* arg0);
void BattleAnim_MotionUnusedRotatingSparkVariant(Particle* arg0);
void BattleAnim_CallbackUnusedRotatingSparkVariant(Particle* arg0);
void BattleAnim_SetupUnusedAimedSparkVariant(Particle* arg0);
void BattleAnim_CallbackUnusedAimedSparkVariant(Particle* arg0);
void BattleAnim_SetupWaterGunAndHydroPumpEmitterFade(Particle* arg0);
void BattleAnim_RunWaterGunAndHydroPumpEmitterFade(Particle* arg0);
void BattleAnim_SetupHydroPumpBurstChild(Particle* arg0);
void BattleAnim_CallbackStartEffect58Descriptor0ABurstChild(Particle* arg0);
void BattleAnim_SetupHydroPumpMetadataBurstChild(Particle* arg0);
void BattleAnim_CallbackStartEffect58Descriptor08MetadataBurstChild(Particle* arg0);
void BattleAnim_SetupHydroPumpBurstEmitter(Particle* arg0);
void BattleAnim_RunHydroPumpBurstEmitter(Particle* arg0);
void BattleAnim_SetupWaterGunProjectileChild(Particle* arg0);
void BattleAnim_CallbackStartEffect6Descriptor0ABurstChild(Particle* arg0);
void BattleAnim_SetupWaterGunProjectileMetadata(Particle* arg0);
void BattleAnim_CallbackStartEffect6Descriptor08MetadataBurstChild(Particle* arg0);
void BattleAnim_SetupWaterGunProjectile(Particle* arg0);
void BattleAnim_RunWaterGunProjectile(Particle* arg0);
void BattleAnim_SetupIceBeamColdBreath(Particle* arg0);
void BattleAnim_ContinueIceBeamColdBreath(Particle* arg0);
void BattleAnim_CallbackStartEffect47Descriptor4AAnimatedScaleFade(Particle* arg0);
void BattleAnim_SetupMegaKickAndPunchProjectile(Particle* arg0);
void BattleAnim_RunMegaKickAndPunchProjectile(Particle* arg0);
void BattleAnim_SetupInitialBeamEmanator(Particle* arg0);
void BattleAnim_RunInitialBeamEmanator(Particle* arg0);
void BattleAnim_SetupPulsingBeamEmanator(Particle* arg0);
void BattleAnim_CallbackSharedDescriptor53ScalePulseCycle(Particle* arg0);
void BattleAnim_SetupStrongBeamHitEffect(Particle* arg0);
void BattleAnim_RunStrongBeamHitEffect(Particle* arg0);
void BattleAnim_SetupPsybeamHitSparkFlicker(Particle* arg0);
void BattleAnim_RunPsybeamHitSparkFlicker(Particle* arg0);
void BattleAnim_SetupAuroraBeamHitSpark(Particle* arg0);
void BattleAnim_RunAuroraBeamHitSpark(Particle* arg0);
void BattleAnim_SetupStrongOutwardMovingLargeHitSpark(Particle* arg0);
void BattleAnim_CallbackSharedDescriptor19AnimatedFadeMotion(Particle* arg0);
void BattleAnim_SetupBlizzardHitUpwardColdAir(Particle* arg0);
void BattleAnim_CallbackEndEffect23Descriptor19AnimatedFade(Particle* arg0);
void BattleAnim_SetupWaterGunHitEffect(Particle* arg0);
void BattleAnim_CallbackEndEffect2Descriptor19AnimatedAlphaFade(Particle* arg0);
void BattleAnim_SetupWeakBeamHitEffect(Particle* arg0);
void BattleAnim_CallbackSharedDescriptor19RecolorAnimatedFade(Particle* arg0);
void BattleAnim_SetupTriAttackHitSpark(Particle* arg0);
void BattleAnim_CallbackEndEffect86Descriptor19ModePositionedAnimFade(Particle* arg0);
void BattleAnim_SetupStrongOutwardMovingSmallHitSpark(Particle* arg0);
void BattleAnim_CallbackSharedDescriptor19DelayedAnimatedGrowFade(Particle* arg0);
void BattleAnim_SetupUnusedIndexedFadeVariantA(Particle* arg0);
void BattleAnim_CallbackUnusedIndexedFadeVariantA(Particle* arg0);
void BattleAnim_SetupUnusedIndexedFadeVariantB(Particle* arg0);
void BattleAnim_CallbackUnusedIndexedFadeVariantB(Particle* arg0);
void BattleAnim_SetupBubbleBubbleBeamSharedEffect(Particle* arg0);
void BattleAnim_CallbackEndEffects34And53Descriptor45RotatingBounceFade(Particle* arg0);
void BattleAnim_SetupHydroPumpColorShiftFade(Particle* arg0);
void BattleAnim_CallbackEndEffect27Descriptor4BGrowColorShiftFade(Particle* arg0);
void BattleAnim_SetupWaterGunEmitterColoration(Particle* arg0);
void BattleAnim_CallbackEndEffect2Descriptor4BModeColorShiftFade(Particle* arg0);
void BattleAnim_SetupHydroPumpWaterGunProjectileHit(Particle* arg0);
void BattleAnim_CallbackEndEffects2And27Descriptor0AFallingSparkFade(Particle* arg0);
void BattleAnim_StartMegaPunchEffect(void);
void BattleAnim_StartEffect2Descriptor08IndexedScaleDelayFade(void);
void BattleAnim_SpawnTimedFireballEffect(void);
void BattleAnim_InitializeBubbleHit(void);
void BattleAnim_InitializeWaterGunUse(void);
void BattleAnim_InitializeWaterGunHit(void);
void BattleAnim_InitializeHydroPumpUse(void);
void InitAdvancedParticleCombo(void);
void BattleAnim_StartEffect47TintDescriptor53ScalePulseAndDescriptor4AFade(void);
void BattleAnim_StartEffect4TintDescriptor53ScalePulse(void);
void InitSmallGlowEffectSet(void);
void BattleAnim_StartEffect26TintDescriptor53ScalePulse(void);
void InitParticleEffectSet_WithFade(void);
void InitParticleEffectSet_WithDifferentTiming(void);
void InitParticleEffectSet_Single(void);
void InitParticleComboVariant(void);
void InitParticleEffectSet_WithMultiple(void);
void InitParticleEffectSet_WithTimedFireball(void);
void BattleAnim_InitializeBubbleBeamHit(void);
void BattleAnim_EndEffect69PaletteRotateWithExpandingHoldFade(void);
void BattleAnim_InitializeHyperBeamHit(void);
void BattleAnim_EndEffect71PaletteApproachWithExpandingScaleFades(void);
void BattleAnim_EndEffect71PaletteApproachWithExpandingScaleFades(void);
void BattleAnim_InitializeTriAttackHit(void);


void BattleAnim_SetupStrongElectricSpark(Particle* arg0);
void BattleAnim_CallbackStartEffects18And73Descriptor11ScatterRiseFade(Particle* arg0);
void BattleAnim_ApplyThunderThunderboltUseRadialOffset(Particle* arg0);
void BattleAnim_SetupThunderThunderboltUseEffect(Particle* arg0);
void BattleAnim_RunThunderThunderboltUseEffect(Particle* arg0);
void BattleAnim_SetupDelayedRisingColumnFade(Particle* arg0);
void BattleAnim_RunDeterministicRotatingBoltOfLightning(Particle* arg0);
void BattleAnim_SetupDelayedRisingColumnRandomScale(Particle* arg0);
void BattleAnim_RunRandomRotatingBoltOfLightning(Particle* arg0);
void BattleAnim_SetupSharedDirectionalSprayFade(Particle* arg0);
void BattleAnim_CallbackSharedDirectionalSprayFade(Particle* arg0);
void BattleAnim_SetupDirectionalSprayScaledFade(Particle* arg0);
void BattleAnim_CallbackSharedDescriptor13DirectionalSprayScaledFade(Particle* arg0);
void BattleAnim_SetupThunderShockOuterJolts(Particle* arg0);
void BattleAnim_CallbackStartEffect59EndEffect28DirectionalStreamFade(Particle* arg0);
void BattleAnim_SetupUnregisteredStraightDirectionalStreamFade(Particle* arg0);
void BattleAnim_CallbackUnregisteredStraightDirectionalStreamFade(Particle* arg0);
void BattleAnim_SetupEndEffect28Descriptor10UpwardBurstFade(Particle* arg0);
void BattleAnim_CallbackEndEffect28Descriptor10UpwardBurstFade(Particle* arg0);
void BattleAnim_SetupEndEffect28Descriptor10WideScatterBurstFade(Particle* arg0);
void BattleAnim_CallbackEndEffect28Descriptor10WideScatterBurstFade(Particle* arg0);
void BattleAnim_InitializeThunderThunderboltUse(void);
void BattleAnim_CreateSprayColumnEffect(void);
void BattleAnim_CreateSprayColumnEffectTrigger(void);
void BattleAnim_InitializeThunderShockUse(void);
void BattleAnim_CreateBurstStreamEffect(void);
void BattleAnim_InitializeThunderPunchUse(void);
void BattleAnim_InitializeHyperBeamHitSequence(void);


void BattleAnim_InitStartEffect135Descriptor1CRisingScale(Particle* arg0);
void BattleAnim_CallbackStartEffect135Descriptor1CRisingScaleFade(Particle* arg0);
void BattleAnim_InitStartEffect135ExpandingFlash(Particle* arg0);
void BattleAnim_CallbackStartEffect135ExpandingFlashFade(Particle* arg0);
void BattleAnim_InitStartEffect139Descriptor42FallingScale(Particle* arg0);
void BattleAnim_CallbackStartEffect139Descriptor42FallingScaleFade(Particle* arg0);
void BattleAnim_InitStartEffect139Descriptor22SpinFade(Particle* arg0);
void BattleAnim_CallbackStartEffect139Descriptor22SpinFadeSpark(Particle* arg0);
void BattleAnim_InitStartEffect141Descriptor1CGridRise(Particle* arg0);
void BattleAnim_CallbackStartEffect141Descriptor1CGridRiseFade(Particle* arg0);
void BattleAnim_InitExplosionOrbit(Particle* arg0);
void BattleAnim_ExplosionOrbitSwirl(Particle* arg0);
void BattleAnim_InitExplosionBurst(Particle* arg0);
void BattleAnim_ExplosionBurstEmitter(Particle* arg0);
s16 BattleAnim_GetSessionModeEffectParam(void);
void BattleAnim_StartEffect139DualRepeatingSparks(void);
void BattleAnim_StartEffect140StartEffect139Alias(void);
void BattleAnim_StartEffect141GridRiseAndFallingBurst(void);
void BattleAnim_StartEffect142StartEffect141Alias(void);
void BattleAnim_StartEffect135ExpandingFlashAndRisingScaleFade(void);
void BattleAnim_StartEffect134ModeOrbitAndMetadataBurst(void);
void BattleAnim_StartEffect143ModeOrbitAndMetadataBurst(void);
void BattleAnim_StartEffect133ModeOrbitBurstAndEffect135Followup(void);
void BattleAnim_StartEffect122GlobalAndOwnerTintFade(void);


void BattleAnim_UnusedResetAppearanceAndAdvance(Particle* arg0);
void BattleAnim_CallbackUnusedGenericFadeApproach(Particle* arg0);
void BattleAnim_SetupOrphanDescriptor2BSpinFade(Particle* arg0);
void BattleAnim_CallbackOrphanDescriptor2BSpinFade(Particle* arg0);
void BattleAnim_SetupOrphanDescriptor2EScatterFade(Particle* arg0);
void BattleAnim_CallbackOrphanDescriptor2EScatterFade(Particle* arg0);
void BattleAnim_SetupPetalDanceLingeringHitEffect(Particle* arg0);
void BattleAnim_RunPetalDanceLingeringHitEffect(Particle* arg0);
void BattleAnim_SetupSlowFallingHitEffect(Particle* arg0);
void BattleAnim_RunSlowFallingHitEffect(Particle* arg0);
void func_8211F3EC(void);
void BattleAnim_OrphanDescriptor2BAnd2EEmitterSequence(void);
void BattleAnim_InitializePetalDanceHit(void);
void BattleAnim_InitializeWingAttackHit(void);


void BattleAnim_InitializeThunderWaveUse(void);
void ParticleEffect_RegisterSmoke(void);
void BattleAnim_StartSleepMovePhaseFadeOut(void);
void BattleAnim_InitializeAmnesiaUse(void);
void BattleAnim_ApplySpeciesMotionOffset(Particle*);
void BattleAnim_StartEffect14ModelAnimAndMoveKeyedTintParticles(void);
void ParticleEffect_RegisterCallbacks(void);
void ParticleEffect_RegisterParticleNodes(void);
void ParticleEffect_RegisterEffectE0(void);
void BattleAnim_StartEffect76Descriptor33FadeAndDescriptor47ScaleMotion(void);
void BattleAnim_StartEffect53Descriptor33FadeAndDescriptor47ScaleMotion(void);
void BattleAnim_StartEffect8ModelBurstAndVerticalFade(void);
void BattleAnim_InitializeLeechSeedHit(void);
void BattleAnim_InitializePayDayHit(void);
void ParticleEffect_RegisterSparkle(void);
void ParticleEffect_RegisterAll(void);
void BattleAnim_InitializeDizzyPunchHit(void);
void ParticleEffect_RegisterColorAnim(void);
void BattleAnim_InitializeDrainingMoveHit(void);
void ParticleEffect_RegisterLargeExplosion(void);
void BattleAnim_InitializeTeleportUse(void);
void BattleAnim_InitializeRockThrowRockSlideUse(void);
void BattleAnim_InitializeRockSlideRockThrowHit(void);
void BattleAnim_InitializeStrengthUse(void);
void BattleAnim_InitializeStrengthHit(void);
void BattleAnim_InitializeEggBombUse(void);
void BattleAnim_InitializeSoftBoiledUse(void);
void BattleAnim_InitializeStrongWind(void);
void BattleAnim_ApplySpeciesXZOffsetVariantA(Particle*);
void BattleAnim_InitializeRazorWindUse(void);


void BattleAnim_SetupReflectiveCamera(void);
void BattleAnim_SelectParticleModelFrames(Particle* arg0, s32 arg1);
void BattleAnim_CallbackInitModelAnimWait(Particle* arg0);
void BattleAnim_InitializeParticleModel(Particle* arg0);
void BattleAnim_RunScaryEyes(Particle* arg0);
void BattleAnim_RunDreamEaterUseEffect(Particle* arg0);
void BattleAnim_CallbackInitModelAnimMode2(Particle* arg0);
void BattleAnim_RunFillScreenOverlay(Particle* arg0);
Gfx* BattleAnim_BuildAnimatedTileDisplayList(Gfx* arg0, u8* arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5, s16 arg6, s16 arg7, s16 arg8, s16 arg9, s16 argA, s16 argB);
Gfx* BattleAnim_BuildAnimatedTileDisplayListFromStruct(Gfx* arg0, arg1_func_8434E21C* arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5, s16 arg6, s16 arg7, s16 arg8, s16 arg9, s16 argA, s16 argB);
void Gfx_SetParticlePrimEnvColors(Gfx* arg0);
void ParticleEffect_AllocateGfxIfNeeded(s32 arg0, arg1_func_84344CE8* arg1);
void Gfx_DrawParticleTextureWithParams(Gfx* arg0, arg1_func_8434E21C* arg1, UNUSED u16 arg2);
void ParticleEffect_AllocateGfxAndDraw(s32 arg0, arg1_func_84344CE8* arg1);
void BattleAnim_SetupMove86EndDescriptor24(Particle* arg0);
void BattleAnim_RunThunderWaveHitEffect(Particle* arg0);
void BattleAnim_ApplyMove86SpeciesOffset(Particle* arg0);
void BattleAnim_SetupMove86StartDescriptor24(Particle* arg0);
void BattleAnim_CallbackMove86StartDescriptor24(Particle* arg0);
void BattleAnim_InitializeThunderWaveUse(void);
void ParticleEffect_RegisterSmoke(void);
void BattleAnim_ApplyEffect1SpeciesMotion(Particle* arg0);
void BattleAnim_SetupSleepMovePhaseFadeOut(Particle* arg0);
void BattleAnim_SleepMovePhaseFadeOut(Particle* arg0);
void BattleAnim_StartSleepMovePhaseFadeOut(void);
void BattleAnim_ApplyModelSpeciesOffset(Particle* arg0);
void BattleAnim_InitModelAnimationSlot(Particle* arg0, s16 arg1);
void BattleAnim_ConfuseRayAmnesiaModelAnimWait(Particle* arg0);
void BattleAnim_InitializeAmnesiaUse(void);
void BattleAnim_ApplySpeciesMotionOffset(Particle* arg0);
void BattleAnim_StartEffect14ModelAnimAndMoveKeyedTintParticles(void);
void BattleAnim_BuildReflectiveTextureDisplayList(Gfx* arg0, s32 arg1, u16 arg2);
void BattleAnim_AllocateReflectiveTextureDisplayList(s32 arg0, arg1_func_84344CE8* arg1);
void BattleAnim_ApplyEffect125ModelScaleOffset(Particle* arg0);
void BattleAnim_InitEffect125Model(Particle* arg0, UNUSED s16 arg1);
void BattleAnim_CallbackStartEffect125ModelBurstEmitter(Particle* arg0);
void BattleAnim_BuildEffect125DisplayList(Gfx* arg0, u16 arg1);
void BattleAnim_AllocateEffect125DisplayList(s32 arg0, arg1_func_84344CE8* arg1);
void ParticleEffect_RegisterCallbacks(void);
void BattleAnim_InitEffect65Overlay(Particle* arg0);
void BattleAnim_RunSporePowderMoveOverlay(Particle* arg0);
void ParticleEffect_RegisterParticleNodes(void);
void BattleAnim_InitEffect28Overlay(Particle* arg0);
void BattleAnim_RunGasAttack(Particle* arg0);
void ParticleEffect_RegisterEffectE0(void);
void BattleAnim_StartEffect76Descriptor33FadeAndDescriptor47ScaleMotion(void);
void BattleAnim_StartEffect53Descriptor33FadeAndDescriptor47ScaleMotion(void);
void BattleAnim_SetupLeechSeedUseEffect1(Particle* arg0);
void BattleAnim_CallbackStartEffect8Descriptor4ABurstChild(Particle* arg0);
void BattleAnim_SetupLeechSeedUseEffect2(Particle* arg0);
void BattleAnim_CallbackStartEffect8ModelBurstEmitter(Particle* arg0);
void BattleAnim_ApplyEffect31SpeciesOffset(Particle* arg0);
void BattleAnim_InitEffect31Model(Particle* arg0);
void BattleAnim_CallbackMove73EndEffect31SpawnDescriptor42(Particle* arg0);
void BattleAnim_StartEffect8ModelBurstAndVerticalFade(void);
void BattleAnim_InitializeLeechSeedHit(void);
void BattleAnim_InitializePayDayHit(void);
void ParticleEffect_DrawSimple(Gfx* arg0, u8* arg1);
void ParticleEffect_CreateSimpleDL(s32 arg0, arg1_func_84344CE8* arg1);
void BattleAnim_SetupBlizzardHitSpark(Particle* arg0);
void BattleAnim_CallbackStartEffect34SpecialModelFadeIn(Particle* arg0);
void BattleAnim_SetupBlizzard(Particle* arg0);
void BattleAnim_CallbackEndEffect23Descriptor4AAnimatedFade(Particle* arg0);
void ParticleEffect_RegisterSparkle(void);
void ParticleEffect_RegisterAll(void);
void ParticleEffect_DrawNode(Gfx* arg0, s32 arg1, u16 arg2);
void ParticleEffect_CreateNodeDL(s32 arg0, arg1_func_84344CE8* arg1);
void ParticleEffect_DrawNodeVariant(Gfx* arg0, arg1_func_8434E21C* arg1, UNUSED u16 arg2);
void ParticleEffect_CreateNodeVariantDL(s32 arg0, arg1_func_84344CE8* arg1);
void ParticleEffect_DrawSimpleOffsetTileNoCamera(Gfx* arg0, u8* arg1, UNUSED u16 arg2);
void ParticleEffect_CreateSimpleOffsetTileNoCameraDL(s32 arg0, arg1_func_84344CE8* arg1);
void func_8211F580(void);
void BattleAnim_ApplyMove146SpeciesOffset(Particle* arg0);
void BattleAnim_InitMove146Model(Particle* arg0);
void BattleAnim_RunDizzyPunchHitEffect(Particle* arg0);
void BattleAnim_InitializeDizzyPunchHit(void);
void BattleAnim_InitEffect49Model(Particle* arg0);
void BattleAnim_CallbackEndEffect49Model33Anim34WaitCleanup(Particle* arg0);
void BattleAnim_CallbackEndEffect21ModelAnimWait(Particle* arg0);
void BattleAnim_BuildEffect49DisplayList(Gfx* arg0, UNUSED s32 arg1, UNUSED u16 arg2);
void BattleAnim_AllocateEffect49DisplayList(s32 arg0, arg1_func_84344CE8* arg1);
void ParticleEffect_RegisterColorAnim(void);
void BattleAnim_InitializeDrainingMoveHit(void);
void BattleAnim_SetupFlyUpwardMovementEffect(Particle* arg0);
void BattleAnim_RunFlyUpwardMovementEffect(Particle* arg0);
void ParticleEffect_RegisterLargeExplosion(void);
void BattleAnim_InitEffect86Model(Particle* arg0);
void BattleAnim_RunFlyUpwardMovementEffect(Particle* arg0);
void BattleAnim_InitializeTeleportUse(void);
void BattleAnim_BuildEffect63DisplayList(Gfx* arg0, s32 arg1, u16 arg2);
void BattleAnim_AllocateEffect63DisplayList(s32 arg0, arg1_func_84344CE8* arg1);
void BattleAnim_BuildEffect75DisplayList(Gfx* arg0, UNUSED s32 arg1, UNUSED u16 arg2);
void BattleAnim_AllocateEffect75DisplayList(s32 arg0, arg1_func_84344CE8* arg1);
void BattleAnim_InitRockModel(Particle* arg0);
void BattleAnim_RockModelAnimWait(Particle* arg0);
void BattleAnim_InitEffects10And50Model(Particle* arg0);
void BattleAnim_CallbackEndEffects10And50ModelAnimColorFade(Particle* arg0);
void BattleAnim_ApplyRockSpeciesScaleOffset(Particle* arg0);
void BattleAnim_InitRockModel38(Particle* arg0);
void BattleAnim_RockModelFadeIn(Particle* arg0);
void Gfx_DrawParticleAlpha(Gfx* arg0, s32 arg1, u16 arg2);
void Particle_CreateDisplayList_Alpha(s32 arg0, arg1_func_84344CE8* arg1);
void Gfx_DrawParticleTexture4b(Gfx* arg0, u8* arg1, UNUSED u16 arg2);
void Particle_CreateDisplayList_Texture4b(s32 arg0, arg1_func_84344CE8* arg1);
void Gfx_DrawParticleGreenPrim(Gfx* arg0, u8* arg1, UNUSED u16 arg2);
void Particle_CreateDisplayList_GreenPrim(s32 arg0, arg1_func_84344CE8* arg1);
void BattleAnim_InitializeRockThrowRockSlideUse(void);
void BattleAnim_InitializeRockSlideRockThrowHit(void);
void BattleAnim_InitializeStrengthUse(void);
void BattleAnim_InitializeStrengthHit(void);
void BattleAnim_InitializeEggBombUse(void);
void BattleAnim_InitializeSoftBoiledUse(void);
void BattleAnim_SetupStrongWinds(Particle* arg0);
void BattleAnim_CallbackStartEffect10Model60AlphaFadeIn(Particle* arg0);
void Gfx_DrawParticleCyanEnv(Gfx* arg0, arg1_func_8434E21C* arg1, UNUSED u16 arg2);
void Particle_CreateDisplayList_CyanEnv(s32 arg0, arg1_func_84344CE8* arg1);
void Gfx_DrawParticleBluePrim(Gfx* arg0, arg1_func_8434E21C* arg1, UNUSED u16 arg2);
void Particle_CreateDisplayList_BluePrim(s32 arg0, arg1_func_84344CE8* arg1);
void BattleAnim_InitializeStrongWind(void);
void BattleAnim_InitializeRazorWindUse(void);
void BattleAnim_ApplySpeciesXZOffsetVariantA(Particle* arg0);
void BattleAnim_RunBoomUseEffect1(Particle* arg0);
void BattleAnim_CallbackStartEffects50And82ScalePulse_InitParticle(Particle* arg0);
void BattleAnim_RunBoomUseEffect2(Particle* arg0);
void BattleAnim_SetupBoomUseEffect3(Particle* arg0);
void BattleAnim_CallbackStartEffects50And82Descriptor48AnimatedScaleFade(Particle* arg0);
void BattleAnim_SetupBoomUseEffect4(Particle* arg0);
void BattleAnim_CallbackStartEffects50And82Descriptor4AAnimatedVerticalFade(Particle* arg0);
void Gfx_DrawParticleCustomColors(Gfx* arg0, arg1_func_8434E21C* arg1, UNUSED u16 arg2);
void Particle_CreateDisplayList_CustomColors(s32 arg0, arg1_func_84344CE8* arg1);
void BattleAnim_CallbackStartEffects50And82CenterModelScalePaletteFade(Particle* arg0);
void BattleAnim_RunBoomUseEffect6(Particle* arg0);
void BattleAnim_CallbackEndEffects81And82ModelScalePaletteFade(Particle* arg0);
void BattleAnim_SetupBoomHitEffect2(Particle* arg0);
void BattleAnim_CallbackEndEffects81And82Descriptor4AAnimatedColorFade(Particle* arg0);
void BattleAnim_SetupBoomHitEffect3(Particle* arg0);
void BattleAnim_CallbackEndEffects81And82Descriptor4FAnimatedPaletteFade(Particle* arg0);
void BattleAnim_InitializeBoomUse(void);
void BattleAnim_InitializeBoomHit(void);
void func_821351EC(UNUSED s32 arg0, UNUSED s32 arg1);
void ParticleEffect_Noop(UNUSED s32 arg0, UNUSED s32 arg1);
void BattleAnim_SetupBitingEffect(Particle* arg0);
void BattleAnim_CallbackStartEffects71And74And111SpecialModelColorCycle(Particle* arg0);
void Gfx_DrawParticleFromTempColors(Gfx* arg0, s32 arg1, u16 arg2);
void Particle_CreateDisplayList_TempColors(s32 arg0, arg1_func_84344CE8* arg1);
void BattleAnim_InitializeClampViceGripUse(void);
void BattleAnim_InitializeGuillotineUse(void);
void BattleAnim_InitializeBitingMoveUse(void);
void BattleAnim_InitializeBitingMoveHit(void);
void BattleAnim_EndEffect83TintRampAndDescriptor34Burst(void);
void Gfx_DrawParticleDualTileDiagonal4(Gfx* arg0, u8* arg1, UNUSED u16 arg2);
void Particle_CreateDisplayList_DualTileDiagonal4(s32 arg0, arg1_func_84344CE8* arg1);
void Gfx_DrawParticleDualTileAntiDiagonal1(Gfx* arg0, u8* arg1, UNUSED u16 arg2);
void Particle_CreateDisplayList_DualTileAntiDiagonal1(s32 arg0, arg1_func_84344CE8* arg1);
void BattleAnim_InitializeSwordsDanceUse(void);
f32 BattleAnim_GetSpeciesScaleAdjust(Particle* arg0);
void BattleAnim_CallbackStartEffect69ModelPhaseWait(Particle* arg0);
void BattleAnim_StartEffect69ModelPhaseWaitAndFallingParticles(void);
void BattleAnim_ApplySpeciesXZOffsetVariantB(Particle* arg0);
void BattleAnim_InitializeDigUse(void);
void BattleAnim_EndEffect78ModelAnimDelayedMotionAndFallingParticles(void);
void BattleAnim_ApplySpeciesYOffsetVariantA(Particle* arg0);
void BattleAnim_InitializeKinesisUse(void);
void BattleAnim_StartEffect79ModelAnimWaitAndDescriptor25AlphaFade(void);
void BattleAnim_ApplySpeciesYOffsetVariantB(Particle* arg0);
void BattleAnim_InitializeBonemerangUse(void);
void BattleAnim_SludgeModelAnimFinish_InitParticle(Particle* arg0);
void BattleAnim_SludgeModelAnimFinish(Particle* arg0);
void BattleAnim_SetupSlimePuddle(Particle* arg0);
void BattleAnim_RunSlimePuddle(Particle* arg0);
void Gfx_DrawParticlePaletteBased(Gfx* arg0, u8* arg1, UNUSED u16 arg2);
void Gfx_ParticlePaletteCallback(s32 arg0, arg1_func_84344CE8* arg1);
void Gfx_ParticlePaletteDL(Gfx* arg0, UNUSED arg1_func_8434E21C* arg1, UNUSED u16 arg2);
void Gfx_ParticlePaletteColorOnlyCallback(s32 arg0, arg1_func_84344CE8* arg1);
s16 BattleAnim_GetSlimeVariantIndex(void);
s16 BattleAnim_GetMoveKeyedTintRampParam(void);
s16 BattleAnim_GetMoveKeyedTrailVariantParam(void);
void BattleAnim_InitializeSlimeMove(void);
void ParticleEffect_PaletteMultiBurst(void);
f32 BattleAnim_GetSpeciesScaleAndApplyYOffset(Particle* arg0);
void Gfx_ParticleTextureTileCallback(Gfx* arg0, arg1_func_8434E21C* arg1, UNUSED u16 arg2);
void Gfx_ParticleTextureTileAllocCallback(s32 arg0, arg1_func_84344CE8* arg1);
void Gfx_ParticleRedPrimCallback(Gfx* arg0, UNUSED arg1_func_8434E21C* arg1, UNUSED u16 arg2);
void Gfx_ParticleRedPrimAllocCallback(s32 arg0, arg1_func_84344CE8* arg1);
void BattleAnim_InitializeGlareLeerUse(void);
void BattleAnim_InitializeHyperBeamUseSequence(void);
void BattleAnim_InitializeEarthquakeFissureUse(void);
void BattleAnim_InitializeEarthquakeFissureHit(void);
void BattleAnim_InitializeEarthquakeHit(void);
void BattleAnim_StartEffect87ModelTintAlphaFadeAndVerticalFade(void);
void ParticleEffect_MultiNodeEffect88Palette7(void);
void Gfx_PokemonPortraitCallback(Gfx* arg0, u8 arg1, UNUSED u16 arg2);
void Gfx_PokemonPortraitAllocCallback(s32 arg0, arg1_func_84344CE8* arg1);
void BattleAnim_InitializeSpeedLines(void);
void ParticleEffect_PortraitBurstInit(void);
void BattleAnim_InitializeWithdrawUse(void);
void ParticleEffect_PortraitBurstCheck(void);
f32 BattleAnim_GetSpeciesScaleAndOffset(Particle* arg0);
void ParticleEffect_SimpleBurstAnimWaitDelayedTintFade(void);
void ParticleEffect_SimpleBurstTintPulseAnimWaitPaletteC(void);
void BattleAnim_ApplySpeciesYOffsetVariantC(Particle* arg0);
void BattleAnim_CallbackStartEffects95To97EndEffects62And63ModelFadeIn_InitParticle(Particle* arg0);
void BattleAnim_RunPsychedelicOverlay(Particle* arg0);
void Gfx_PaletteParticleDL(Gfx* arg0, u8* arg1, UNUSED u16 arg2);
void Gfx_PaletteParticleDLCallback(s32 arg0, arg1_func_84344CE8* arg1);
void ParticleEffect_PaletteMultiBurstCleanupWithTintFade(void);
void BattleAnim_InitializeDreamEaterHit(void);
void BattleAnim_CreateDrainingMoveOverlay(void);
void BattleAnim_InitializeMeditateUse(void);
void ParticleEffect_PaletteBurstVariant2Model8EDelayedFadeOut(void);
void ParticleEffect_FireworkBurst(void);
void BattleAnim_SetupConfuseRayUseSpotlight(Particle* arg0);
void BattleAnim_CallbackStartEffects21And93ModelAlphaAnchorFollow(Particle* arg0);
void BattleAnim_SetupConfuseRayHitSpotlight(Particle* arg0);
void BattleAnim_CallbackEndEffect60Model42AnimC2RotationYFollow(Particle* arg0);
void Gfx_WaterAnimPrimEnvDL(Gfx* arg0, u8 arg1, UNUSED u16 arg2);
void Gfx_WaterAnimPrimEnvDLCallback(s32 arg0, arg1_func_84344CE8* arg1);
void ParticleEffect_WaterAnimBurst(void);
void ParticleEffect_WaterAnimBurstTintFadeOnly(void);
void ParticleEffect_WaterAnimFirework(void);
void ParticleEffect_WaterAnimFireworkModel42RotationFollow(void);
void Gfx_WaterAnimDL(Gfx* arg0, u8* arg1, UNUSED u16 arg2);
void Gfx_WaterAnimDLCallback(s32 arg0, arg1_func_84344CE8* arg1);
f32 BattleAnim_GetSpeciesScaleAdjustSmall(Particle* arg0);
void BattleAnim_InitializeWaterfallUse(void);
void ParticleEffect_FireballBurst(void);
void BattleAnim_InitializeSurfUseSpray(void);
void BattleAnim_InitializeSurfHit(void);
void ParticleEffect_SimpleBurstAnimWaitDelayedAlphaFadeOut(void);
void BattleAnim_SetupBarrageEffect(Particle* arg0);
void BattleAnim_CallbackStartEffect101EndEffect65Descriptor4ABurstChild(Particle* arg0);
void BattleAnim_SetupBarrageUseEffect1(Particle* arg0);
void BattleAnim_CallbackStartEffect101ModelBurstEmitter(Particle* arg0);
void BattleAnim_InitializeBarrageUse(void);
void BattleAnim_SetupBarrageHitEffect(Particle* arg0);
void BattleAnim_CallbackMove140EndEffect65EmitDescriptor4A(Particle* arg0);
void BattleAnim_InitializeBarrageHit(void);
void BattleAnim_SetupPsywaveEffect(Particle* arg0);
void BattleAnim_RunPsywaveEffect(Particle* arg0);
void Gfx_SimpleNodeDL(Gfx* arg0, arg1_func_8434E21C* arg1, UNUSED u16 arg2);
void Gfx_SimpleNodeDLCallback(s32 arg0, arg1_func_84344CE8* arg1);
void BattleAnim_InitializePsywaveUse(void);
void ParticleEffect_SimpleNodeBurst(void);
void BattleAnim_RunConfusionPsychicHitEffect(Particle* arg0);
void ParticleEffect_AlphaBurst(void);
void ParticleEffect_AlphaBurstPalette17(void);
void ParticleEffect_AlphaFirework(void);
void ParticleEffect_AlphaFireworkPalette17(void);
f32 BattleAnim_GetSpeciesScaleAdjustTiny(Particle* arg0);
void BattleAnim_StartEffect3ModelTintAndVerticalFade(void);
void BattleAnim_InitializeBideRageUseSequence(void);
void ParticleEffect_InitFire(void);
void ParticleEffect_InitSmoke(void);
void BattleAnim_InitializeSkyAttackHit(void);
void ParticleEffect_DrawQuad(Gfx* arg0, arg1_func_8434E21C* arg1, UNUSED u16 arg2);
void ParticleEffect_AllocateDisplayList(s32 arg0, arg1_func_84344CE8* arg1);
void BattleAnim_InitializeThunderHitSequence(void);
void ParticleEffect_TriggerSpecial(void);
void BattleAnim_MegaHitModelFade(Particle* arg0);
void ParticleEffect_TriggerAnother(void);
void BattleAnim_InitializeDrillPeckUse(void);
void BattleAnim_InitializeDrillPeckHit(void);
void BattleAnim_InitializeHornDrillUse(void);
void ParticleEffect_TriggerDefaultPalette1CWithTintRamps(void);
void BattleAnim_RunWeakSpear(Particle* arg0);
void ParticleEffect_CreateWithCallback(void);
void ParticleEffect_CreateCallback(void);
void BattleAnim_CallbackEndEffect79DefaultDescriptorPaletteFade(Particle* arg0);
void BattleAnim_InitializeVerticalLandingHitSpark(void);
void ParticleEffect_SetMode(void);
void BattleAnim_CallbackStartEffects127And128Descriptor39ScaleFade_InitParticle(Particle* arg0);
void BattleAnim_CallbackStartEffects127And128Descriptor39ScaleFade(Particle* arg0);
void BattleAnim_StartEffect127Descriptor39ScaleFade(void);
void BattleAnim_StartEffect128Descriptor39ScaleFade(void);
void ParticleEffect_CreateTypeX(void);
void ParticleEffect_CreateSmoke(void);
void ParticleEffect_CreateSmokeHighPriority(void);
void BattleAnim_CallbackStartEffect132Descriptor39DelayedRiseFade_InitParticle(Particle* arg0);
void BattleAnim_CallbackStartEffect132Descriptor39DelayedRiseFade(Particle* arg0);
void ParticleEffect_CreateDual(void);
void BattleAnim_SetupSlashingMoveUse(Particle* arg0);
void BattleAnim_CallbackSharedDescriptor29ScaleAnimFade(Particle* arg0);
void BattleAnim_SetupRazorWindHitEffect(Particle* arg0);
void BattleAnim_RunRazorWindHitEffect(Particle* arg0);
void BattleAnim_SetupPetalDanceRazorLeafHitEffect(Particle* arg0);
void BattleAnim_RunPetalDanceRazorLeafHitEffect(Particle* arg0);
void BattleAnim_CallbackSharedOwnerKeyedGrowColorFade_InitParticle(Particle* arg0);
void BattleAnim_CallbackSharedOwnerKeyedGrowColorFade(Particle* arg0);
void BattleAnim_CallbackSharedOwnerKeyedGrowColorAlphaFade_InitParticle(Particle* arg0);
void BattleAnim_CallbackSharedOwnerKeyedGrowColorAlphaFade(Particle* arg0);
void BattleAnim_SlashGrowFade_InitParticle(Particle* arg0);
void BattleAnim_SlashGrowFade(Particle* arg0);
void BattleAnim_CallbackEndEffect88Descriptor2AOwnerKeyedAnimGrowFade_InitParticle(Particle* arg0);
void BattleAnim_CallbackEndEffect88Descriptor2AOwnerKeyedAnimGrowFade(Particle* arg0);
void BattleAnim_HeavyHitBurstChild_InitParticle(Particle* arg0);
void BattleAnim_HeavyHitBurstChild(Particle* arg0);
void BattleAnim_CallbackSharedTieredSmallRiseImpulseFade_InitParticle(Particle* arg0);
void BattleAnim_CallbackSharedTieredSmallRiseImpulseFade(Particle* arg0);
void BattleAnim_CallbackSharedTieredLargeRiseImpulseFade_InitParticle(Particle* arg0);
void BattleAnim_CallbackSharedTieredLargeRiseImpulseFade(Particle* arg0);
void BattleAnim_SetupSandAttackUseEffect(Particle* arg0);
void BattleAnim_CallbackStartEffect31Descriptor49TieredRiseImpulseFade(Particle* arg0);
void BattleAnim_SetupUnusedRiseImpulseVariant(Particle* arg0);
void BattleAnim_CallbackUnusedRiseImpulseVariant(Particle* arg0);
void BattleAnim_SetupSandAttackHitEffect(Particle* arg0);
void BattleAnim_CallbackEndEffect55Descriptor49RiseGravityFade(Particle* arg0);
void BattleAnim_HeavyHitAnimatedRiseFade_InitParticle(Particle* arg0);
void BattleAnim_HeavyHitAnimatedRiseFade(Particle* arg0);
void BattleAnim_SetupIceBeamIcePunchEffect(Particle* arg0);
void BattleAnim_CallbackEndEffect67Descriptor3DAnimatedGravityFade(Particle* arg0);
void BattleAnim_CallbackOrphanDescriptor34ColorFadeDetach_InitParticle(Particle* arg0);
void BattleAnim_CallbackOrphanDescriptor34ColorFadeDetach(Particle* arg0);
void BattleAnim_SetupGroundedCircularHitSpark(Particle* arg0);
void BattleAnim_RunGroundedCircularHitSpark(Particle* arg0);
void BattleAnim_SetupUnusedGlitterVariant(Particle* arg0);
void BattleAnim_CallbackUnusedGlitterVariant(Particle* arg0);
void BattleAnim_SetupPointyMoveHitSparkChild(Particle* arg0);
void BattleAnim_CallbackEndEffects37And38Descriptor38BurstChild(Particle* arg0);
void BattleAnim_SetupPhysicalHitPurpleSmoke(Particle* arg0);
void BattleAnim_RunPhysicalHitPurpleSmoke(Particle* arg0);
void BattleAnim_SwiftBurstChild_InitParticle(Particle* arg0);
void BattleAnim_SwiftBurstChild(Particle* arg0);
void BattleAnim_SetupSwiftHitEffect2(Particle* arg0);
void BattleAnim_RunSwiftHitEffect2(Particle* arg0);
void BattleAnim_SetupSharedScalePulseFallSetup(Particle* arg0);
void BattleAnim_RunSparkleHit(Particle* arg0);
void BattleAnim_SetupBlizzardHitEffect(Particle* arg0);
void BattleAnim_RunBlizzardHitEffect(Particle* arg0);
void BattleAnim_CallbackEndEffect67Descriptor42ScalePulseFallFade(Particle* arg0);
void BattleAnim_SetupThunderPunchHitEffect(Particle* arg0);
void BattleAnim_RunThunderPunchHitEffect(Particle* arg0);
void BattleAnim_SetupDefaultHitSpark(Particle* arg0);
void BattleAnim_RunDefaultHitSpark(Particle* arg0);
void BattleAnim_SetupStrongPurpleHitSmoke(Particle* arg0);
void BattleAnim_RunStrongPurpleHitSmoke(Particle* arg0);
void BattleAnim_SetupPointyMoveHitSpark(Particle* arg0);
s32 BattleAnim_RunPointyMoveHitSpark(Particle* arg0);
void BattleAnim_SetupFirePunchUseEffect1(Particle* arg0);
void BattleAnim_RunFirePunchUseEffect1(Particle* arg0);
void BattleAnim_SetupFirePunchUseEffect2(Particle* arg0);
void BattleAnim_CallbackStartEffect56Descriptor46AnimColorImpulseFade(Particle* arg0);
void BattleAnim_SetupThunderPunchUseEffect(Particle* arg0);
void BattleAnim_CallbackStartEffect73Descriptor15AnimatedColorImpulseFade(Particle* arg0);
void BattleAnim_RecolorParticleByQueuedMoveId(Particle* arg0);
void BattleAnim_PowderCloudScaleMotion_InitParticle(Particle* arg0);
void BattleAnim_PowderCloudScaleMotion(Particle* arg0);
void BattleAnim_CallbackStartEffect81Descriptor4BGrowColorShiftFade_InitParticle(Particle* arg0);
void BattleAnim_CallbackStartEffect81Descriptor4BGrowColorShiftFade(Particle* arg0);
void BattleAnim_SetupAcidArmorUseEffect2(Particle* arg0);
void BattleAnim_RunAcidArmorUseEffect2(Particle* arg0);
void BattleAnim_InitSharedVerticalFadeParticle_ApplySpeciesOffset(Particle* arg0);
void BattleAnim_InitSharedVerticalFadeParticle(Particle* arg0);
void BattleAnim_CallbackSharedAnimatedVerticalFade(Particle* arg0);
void BattleAnim_ApplySpeciesKeyedSpawnOffset(Particle* arg0);
void BattleAnim_CallbackEndEffect16MultiDescriptorAnimatedFallFade(Particle* arg0);
void BattleAnim_CallbackStartEffect69EndEffect78Descriptor4AFallFade(Particle* arg0);
void BattleAnim_CallbackStartEffect69EndEffect78Descriptor30YThresholdFall(Particle* arg0);
void BattleAnim_SetupBarrageUseEffect2(Particle* arg0);
void BattleAnim_RunBarrageUseEffect2(Particle* arg0);
void BattleAnim_CallbackDescriptor50BurstChild_InitParticle(Particle* arg0);
void BattleAnim_CallbackDescriptor50BurstChild(Particle* arg0);
void BattleAnim_CallbackDescriptor50BurstEmitter_InitParticle(Particle* arg0);
void BattleAnim_CallbackDescriptor50BurstEmitter(Particle* arg0);
void func_82124EF4(void);
void BattleAnim_CallbackUnusedFallingTrailVariant(Particle* arg0);
void BattleAnim_SetupSolarBeamUseEffect(Particle* arg0);
void BattleAnim_RunSolarBeamUseEffect(Particle* arg0);
void BattleAnim_SetupQiChargeChild(Particle* arg0);
void BattleAnim_RunQiChargeChild(Particle* arg0);
void BattleAnim_SetupQiCharge(Particle* arg0);
void BattleAnim_SolarbeamMimicBurstEmitter(Particle* arg0);
void BattleAnim_CallbackDescriptor26BurstChild_InitParticle(Particle* arg0);
void BattleAnim_CallbackDescriptor26BurstChild(Particle* arg0);
void BattleAnim_CallbackDescriptor26BurstEmitter_InitParticle(Particle* arg0);
void BattleAnim_CallbackDescriptor26BurstEmitter(Particle* arg0);
void BattleAnim_SetupUnusedGrowingSparkVariant(Particle* arg0);
void BattleAnim_CallbackUnusedGrowingSparkVariant(Particle* arg0);
void BattleAnim_RunStrongContactMoveHitSpark(void);
void BattleAnim_InitializeUniqueSharedHitSpark(void);
void BattleAnim_InitializeLowKickHit(void);
void BattleAnim_InitializeDefaultLimbForMove(void);
void BattleAnim_InitializeSpecialLimbForMove(void);
void BattleAnim_InitializePointyMoveHitSparks(void);
void BattleAnim_InitializePoisonStingTwineedleHit(void);
void BattleAnim_InitializeFuryAttackGustHit(void);
void BattleAnim_InitializeIcePunchUse(void);
void BattleAnim_InitializeIcePunchHit(void);
void ParticleEffect_CollisionSetup(void);
void BattleAnim_OrphanDescriptor34Emitter(void);
void BattleAnim_InitializeSubmissionUse(void);
void BattleAnim_InitializeStompHit(void);
void BattleAnim_InitializeGroundedCircularHitSpark(void);
void BattleAnim_InitializeSubmissionHit(void);
void BattleAnim_InitializeBitingMoveEndEffect(void);
void BattleAnim_StartEffect7GlobalTintFade(void);
void BattleAnim_InitializeSwiftHit(void);
void BattleAnim_StartEffect137Descriptor3FRisingFade(void);
void ParticleEffect_TextureNodeSetup(void);
void BattleAnim_InitializeCutEffect(void);
void ParticleEffect_HandleCollisionSetup(void);
void BattleAnim_StartEffect13SecondaryOwnerSpeciesBranch(void);
void BattleAnim_InitializeScratchSlashHit(void);
void ParticleEffect_ConditionalStateSetup(void);
void ParticleEffect_CollisionResponseSwitch(void);
void ParticleEffect_CollisionAndBurstSetup(void);
void BattleAnim_InitializeVineWhipUse(void);
void BattleAnim_InitializeVineWhipHit(void);
void ParticleEffect_AdditionalNodeSetup(void);
void BattleAnim_InitializeRazorWindHit(void);
void BattleAnim_StartEffect11GlobalTintFade(void);
void BattleAnim_InitializeRazorLeafHit(void);
void ParticleEffect_SmallNodeSetupGlobalTintFade17(void);
void BattleAnim_InitializePetalDanceHitSequence(void);
void ParticleEffect_ModeSpecificSetup(void);
void ParticleEffect_ComplexNodeSetup(void);
void BattleAnim_InitializeSandAttackHit(void);
void ParticleEffect_AdvancedModeSetup(void);
void BattleAnim_StartEffect16TintDescriptor34Sequence(void);
void ParticleEffect_FullSetupTintFadeOutAndRestore(void);
void ParticleEffect_FinalSetupSpiralAndVerticalFade(void);
void BattleAnim_InitializeStruggleThrashUse(void);
void BattleAnim_InitializeDoubleEdgeTakeDownUse(void);
void BattleAnim_InitializeBodySlamUse(void);
void BattleAnim_InitializeEarthquakeFissureHitSequence(void);
void BattleAnim_EndEffectUnusedVerticalFadeAndDelayedFrameSequence(void);
void BattleAnim_InitializeDefenseCurlSharpenUseSequence(void);
void BattleAnim_InitializeSubstituteTransformUse(void);
void BattleAnim_InitializeQiCharge(s32 arg0);
void ParticleEffect_GroupSetupTintAndDefaultBurst(void);
void BattleAnim_StartEffect105TintDefaultBurstAndDescriptor3CSequence(void);
void ParticleEffect_SimpleGroupSetup(void);
void BattleAnim_InitializeRecoverUse(void);
void ParticleEffect_FinalGroupSetup(void);

// 3438B0
void BattleAnim_RenderNop1(void);
void BattleAnim_RenderNop2(void);
void BattleAnim_DrawFullScreenColorOverlay(u8, u8, u8, u8);
void BattleAnim_RenderEffectsFrame(CameraNode*);


void BattleAnim_NoopUpdateHook(void);
void func_821329F0(void);
void func_82132E20(void);
void func_8213436C(void);
void func_82135100(void);
void func_82136010(void);
void func_82136018(void);
void func_82140D50(void);
void func_82143C08(void);
void func_82146674(void);
void func_821336E4(UNUSED s32 arg0);
void func_8216D9C8(UNUSED s32 arg0);
void func_821491CC(void);
void BattleAnim_DrawStoredColorOverlay(void);
void BattleAnim_ReinitAuxiliaryEffects(void);
void BattleAnim_DefaultStartEffect_Init(void);
void BattleAnim_DefaultEndEffect_Init(void);
s32 BattleAnim_DefaultStartEffect_CompleteImmediately(void);
s32 BattleAnim_DefaultEndEffect_CompleteImmediately(void);
void BattleAnim_DefaultStartEffect_Draw(void);
void BattleAnim_DefaultEndEffect_Draw(void);
void Battle_GetTertiaryOwnerBonePositionUnused(Vec3f* arg0);
void BattleAnim_EffectSecondaryOwnerAnchorPosition(Vec3f* arg0);
void BattleAnim_EffectTertiaryOwnerBonePosition(Vec3f* arg0);
void BattleAnim_EffectSecondaryOwnerBonePosition(Vec3f* arg0);
f32 BattleAnim_EffectTertiaryOwnerModelScale(void);
f32 BattleAnim_EffectSecondaryOwnerModelScale(void);
void BattleAnim_CalcVectorAtToDm(f32* arg0, f32* arg1, f32* arg2, f32* arg3, f32* arg4, f32* arg5);
void BattleAnim_CalcVectorAtToDm2(f32* arg0, f32* arg1, f32* arg2, f32* arg3, f32* arg4, f32* arg5);
void BattleAnim_ResetSharedEffectMatrix(void);
void BattleAnim_SetupMistUseRibbonMesh(void);
s32 BattleAnim_RunMistUseRibbonMesh(void);
void BattleAnim_DrawMistUseRibbonMesh(void);
void BattleAnim_EndEffect1RibbonMesh_Init(void);
s32 BattleAnim_EndEffect1RibbonMesh_Update(void);
void BattleAnim_EndEffect1RibbonMesh_Draw(void);
void BattleAnim_EndEffect19RibbonMesh_Init(void);
s32 BattleAnim_EndEffect19RibbonMesh_Update(void);
void BattleAnim_EndEffect19RibbonMesh_Draw(void);
void BattleAnim_SetupHazeUseRibbonMesh(void);
s32 BattleAnim_RunHazeUseRibbonMesh(void);
void BattleAnim_DrawHazeUseRibbonMesh(void);
void BattleAnim_SetupSurfUseTerrainGrid(void);
s32 BattleAnim_RunSurfUseTerrainGrid(void);
void BattleAnim_DrawSurfUseTerrainGrid(void);
void BattleAnim_EndEffect16_NoOpInit(void);
s32 BattleAnim_SurfCompleteImmediately(void);
void BattleAnim_EndEffect16_NoOpDraw(void);
void BattleAnim_StartEffect19Radial20_EmitVariantD(void);
void BattleAnim_StartTrappingLassoMove_Init(void);
s32 BattleAnim_StartTrappingLassoMove_Update(void);
void BattleAnim_StartTrappingLassoMove_Draw(void);
void BattleAnim_EndEffect9Radial20_Init(void);
s32 BattleAnim_EndEffect9Radial20_Update(void);
void BattleAnim_EndEffect9Radial20_Draw(void);
void BattleAnim_StartEffect7TexturedRibbonSheet_Emit(void);
void BattleAnim_SetupSwiftUseRibbonSheet(void);
s32 BattleAnim_RunSwiftUseRibbonSheet(void);
void BattleAnim_DrawSwiftUseRibbonSheet(void);
void BattleAnim_StartEffect33Radial20_EmitVariantC(void);
void BattleAnim_SetupStringShotUseRadial(void);
s32 BattleAnim_RunStringShotUseRadial(void);
void BattleAnim_DrawStringShotUseRadial(void);
void BattleAnim_SetupStringShotHitRadial(void);
s32 BattleAnim_RunStringShotHitRadial(void);
void BattleAnim_DrawStringShotHitRadial(void);
void BattleAnim_EndEffect33Radial20_Init(void);
s32 BattleAnim_RunDisableHitRadial(void);
void BattleAnim_DrawDisableHitRadial(void);
void BattleAnim_StartEffect98Radial20_EmitVariantD(void);
void BattleAnim_SetupDisableUseRadial(void);
s32 BattleAnim_RunDisableUseRadial(void);
void BattleAnim_DrawDisableUseRadial(void);
void BattleAnim_SetupRazorLeafUseTrail(void);
s32 BattleAnim_RunRazorLeafUseTrail(void);
void BattleAnim_DrawRazorLeafUseTrail(void);
void BattleAnim_SetupPetalDanceUseTrail(void);
s32 BattleAnim_RunPetalDanceUseTrail(void);
void BattleAnim_DrawPetalDanceUseTrail(void);
void BattleAnim_SetupHypnosisScreechUseTrail(void);
s32 BattleAnim_RunHypnosisScreechUseTrail(void);
void BattleAnim_DrawHypnosisScreechUseTrail(void);
void BattleAnim_SetupSingUseTrail(void);
s32 BattleAnim_RunSingUseTrail(void);
void BattleAnim_DrawSingUseTrail(void);
void BattleAnim_SetupKinesisSupersonicUseTrail(void);
s32 BattleAnim_RunKinesisSupersonicUseTrail(void);
void BattleAnim_DrawKinesisSupersonicUseTrail(void);
void BattleAnim_SetupSonicBoomUseFourStream(void);
s32 BattleAnim_RunSonicBoomUseFourStream(void);
void BattleAnim_DrawSonicBoomUseFourStream(void);
void BattleAnim_SetupSpikeCannonUseFourStream(void);
s32 BattleAnim_RunSpikeCannonUseFourStream(void);
void BattleAnim_DrawSpikeCannonUseFourStream(void);
void BattleAnim_StingerMoves_Init(void);
s32 BattleAnim_StingerMoves_Update(void);
void BattleAnim_StingerMoves_Draw(void);
void BattleAnim_EmitTriAttackUseRadial(void);
void BattleAnim_SetupTriAttackUseRadial(void);
s32 BattleAnim_RunTriAttackUseRadial(void);
void BattleAnim_DrawTriAttackUseRadial(void);
void BattleAnim_SeedAuroraBeamUseDoubleTextureTrail(void);
void BattleAnim_SetupAuroraBeamUseDoubleTextureTrail(void);
s32 BattleAnim_RunAuroraBeamUseDoubleTextureTrail(void);
void BattleAnim_DrawAuroraBeamUseDoubleTextureTrail(void);
void BattleAnim_SeedIceBeamUseSixSlotTrail(void);
void BattleAnim_SetupIceBeamUseSixSlotTrail(void);
s32 BattleAnim_RunIceBeamUseSixSlotTrail(void);
void BattleAnim_DrawIceBeamUseSixSlotTrail(void);
void BattleAnim_SeedPsybeamUseDoubleTextureTrail(void);
void BattleAnim_SetupPsybeamUseDoubleTextureTrail(void);
s32 BattleAnim_RunPsybeamUseDoubleTextureTrail(void);
void BattleAnim_DrawPsybeamUseDoubleTextureTrail(void);
void BattleAnim_StartEffect77DoubleTextureTrail_Seed(void);
void BattleAnim_StartEffect77DoubleTextureTrail_Init(void);
s32 BattleAnim_StartEffect77DoubleTextureTrail_Update(void);
void BattleAnim_StartEffect77DoubleTextureTrail_Draw(void);
void BattleAnim_SeedSolarBeamUseDoubleTextureTrail(void);
void BattleAnim_SetupSolarBeamUseDoubleTextureTrail(void);
s32 BattleAnim_RunSolarBeamUseDoubleTextureTrail(void);
void BattleAnim_DrawSolarBeamUseDoubleTextureTrail(void);
void BattleAnim_SeedHyperBeamUseDoubleTextureTrail(void);
void BattleAnim_SeedHyperBeamUseSixSlotTrail(void);
void BattleAnim_SetupHyperBeamUseCombinedTrail(void);
s32 BattleAnim_RunHyperBeamUseCombinedTrail(void);
void BattleAnim_DrawHyperBeamUseCombinedTrail(void);


void MistHaze_Init(void);
void MistHaze_Configure(RibbonMesh* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9);
void MistHaze_Spawn(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5);
void MistHaze_UpdateEnvAlpha(RibbonMesh* arg0);
s32 MistHaze_Update(RibbonMesh* arg0);
s32 MistHaze_UpdatePool(void);
Gfx* MistHaze_Draw(Gfx* arg0, RibbonMesh* arg1);
Gfx* MistHaze_DrawPool(Gfx* arg0);
void SurfTerrainGrid_BuildCameraBounds(unk_D_843975E8* arg0, f32 arg1);
f32 SurfTerrainGrid_SampleHeightAndSlope(f32 arg0, f32 arg1, f32* arg2);
s32 SurfTerrainGrid_UpdateWaves(void);
void SurfTerrainGrid_Init(s32 arg0, s16 arg1, s16 arg2);
s32 SurfTerrainGrid_Update(void);
Gfx* SurfTerrainGrid_Draw(Gfx* arg0);


void LassoHit_Init(f32 arg0, f32 arg1, f32 arg2, f32 arg3, u8 arg4, u8 arg5, u8 arg6, u8 arg7, u8 arg8, u8 arg9);
f32 Strip400_GetTailFadeRatio(void);
s32 LassoHit_Update(void);
Gfx* Strip400_Draw(Gfx* arg0);
void Radial20_ResetPool(void);
void TriAttackRadial_EmitVariantA(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, s16 arg6, u8 arg7, u8 arg8, u8 arg9, u8 argA, f32 argB, f32 argC, f32 argD, s16 argE);
void Radial20_VariantB(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, s16 arg6, u8 arg7, u8 arg8, u8 arg9, u8 argA, f32 argB, f32 argC, f32 argD, s16 argE);
void Radial20_VariantC(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, s16 arg6, u8 arg7, u8 arg8, u8 arg9, u8 argA, f32 argB, f32 argC, f32 argD, s16 argE);
void Radial20_VariantD(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, s16 arg6, u8 arg7, u8 arg8, u8 arg9, u8 argA, u8 argB, u8 argC, u8 argD, f32 argE, f32 argF, f32 arg10, s16 arg11);
void Radial20_VariantE(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, s16 arg6, u8 arg7, u8 arg8, u8 arg9, u8 argA, f32 argB, f32 argC, f32 argD, s16 argE);
void Radial20_RotateVertexOffset(f32 arg0, UNUSED Vec3f* arg1, Vec3f* arg2, f32 arg3, UNUSED f32 arg4, UNUSED f32 arg5, UNUSED f32 arg6);
void Radial20_UpdateNode(Radial20* arg0);
s32 Radial20_IsComplete(void);
Gfx* Radial20_Draw(Gfx* arg0);


void HypnosisScreechTrail_Init(s16 arg0);
void HypnosisScreechTrail_Start(s32 arg0, s32 arg1);
void HypnosisScreechTrailNode_FillVertex(Trail40Node* arg0, Vtx* arg1);
s32 HypnosisScreechTrail_IsComplete(void);
void Trail40_Reset(void);
Gfx* HypnosisScreechTrail_Draw(Gfx* arg0);


void SingTrail_ApplyRippleAtPoint(s16 arg0, s16 arg1);
void SingTrail_InitPool(s16 arg0);
void SingTrail_UpdateNodes(s32 arg0, s32 arg1);
void SingTrail_WriteVertex(Trail40VariantNode* arg0, Vtx* arg1);
s32 SingTrail_AdvanceTimer(void);
void Trail40Variant_SetupCameraTransform(void);
Gfx* SingTrail_BuildGfx(Gfx* arg0);


void Trail40GridAlt_Init(s16 arg0);
void Trail40GridAlt_Start(s32 arg0, s32 arg1);
void Trail40GridAlt_FillVertex(Trail40Node* arg0, Vtx* arg1);
s32 Trail40GridAlt_IsComplete(void);
void Trail40GridAlt_Reset(void);
Gfx* Trail40GridAlt_Draw(Gfx* arg0);


void SwiftRibbonSheet_Init(void);
void SwiftRibbonSheet_Start(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, u8 arg6, u8 arg7, u8 arg8, u8 arg9, f32 argA, s16 argB);
void SwiftRibbonSheet_Update(f32 arg0, Vec3f* arg1, f32 arg2);
void SwiftRibbonSheet_UpdateRecord(TexturedRibbonSheet* arg0);
s32 SwiftRibbonSheet_IsComplete(void);
Gfx* SwiftRibbonSheet_Draw(Gfx* arg0);


Gfx* Gfx_DrawThickLine(Gfx* arg0, Vec3f* arg1, Vec3f* arg2, Vec3f* arg3, f32 arg4, u8 arg5, u8 arg6, u8 arg7, u8 arg8);


void FourStreamTrail_Init(void);
void FourStreamTrail_Start(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, u8 arg6, u8 arg7, u8 arg8, u8 arg9, f32 argA, f32 argB, f32 argC, s16 argD);
void FourStreamTrail_Update(f32 arg0, Vec3f* arg1, f32 arg2, f32 arg3);
void FourStreamTrail_UpdateNodeChain(FourStreamTrail* arg0);
s32 FourStreamTrail_IsComplete(void);
Gfx* FourStreamTrail_Draw(Gfx* arg0);


void SpikeCannonFourStream_Init(void);
void SpikeCannonFourStream_Start(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, u8 arg6, u8 arg7, u8 arg8, u8 arg9, f32 argA, f32 argB, f32 argC, s16 argD);
void SpikeCannonFourStream_Update(f32 arg0, Vec3f* arg1, f32 arg2);
void SpikeCannonFourStream_UpdateNodeChain(OwnerLinkedFourStream* arg0);
s32 SpikeCannonFourStream_IsComplete(void);
Gfx* SpikeCannonFourStream_Draw(Gfx* arg0);


void OwnerAnchoredFourStream_Init(void);
void OwnerAnchoredFourStream_Start(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, u8 arg6, u8 arg7, u8 arg8, u8 arg9, f32 argA, f32 argB, f32 argC, s16 argD);
void OwnerAnchoredFourStream_Update(f32 arg0, Vec3f* arg1, f32 arg2);
void OwnerAnchoredFourStream_UpdateNodeChain(OwnerAnchoredFourStream* arg0);
s32 OwnerAnchoredFourStream_IsComplete(void);
Gfx* OwnerAnchoredFourStream_Draw(Gfx* arg0);


void PetalDanceTrail_Init(void);
void PetalDanceTrail_Start(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, u8 arg6, u8 arg7, u8 arg8, u8 arg9, f32 argA, f32 argB, f32 argC, s16 argD);
void PetalDanceTrail_Update(f32 arg0, Vec3f* arg1, f32 arg2);
void PetalDanceTrail_AdvanceNodes(Trail50Effect* arg0);
s32 PetalDanceTrail_IsComplete(void);
Gfx* PetalDanceTrail_Draw(Gfx* arg0);


void RazorLeafTrail_Init(void);
void RazorLeafTrail_Start(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, u8 arg6, u8 arg7, u8 arg8, u8 arg9, f32 argA, f32 argB, f32 argC, s16 argD);
void RazorLeafTrail_Update(f32 arg0, Vec3f* arg1, f32 arg2);
void RazorLeafTrail_AdvanceNodes(Trail50Effect* arg0);
s32 RazorLeafTrail_IsComplete(void);
Gfx* RazorLeafTrail_Draw(Gfx* arg0);


void DoubleTextureTrail_InitPool(void);
void DoubleTextureTrail_Spawn(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9, f32 argA, s16 argB, s32 argC, s32 argD, s16 argE, s16 argF, s16 arg10, s16 arg11, s16 arg12, s16 arg13, s16 arg14, s16 arg15, unk_D_843C2C00_024* arg16, unk_D_843C2C00_024* arg17, u8 arg18, u8 arg19, u8 arg1A, u8 arg1B, u8 arg1C, u8 arg1D, u8 arg1E, u8 arg1F, u8 arg20, u8 arg21, u8 arg22, u8 arg23, u8 arg24);
void DoubleTextureTrail_RotateVertexOffset(f32 arg0, Vec3f* arg1, f32 arg2);
void DoubleTextureTrail_Update(DoubleTextureTrail* arg0);
s32 DoubleTextureTrail_UpdateAll(void);
Gfx* WaterParticle_DrawPass(Gfx* arg0, DoubleTextureTrail* arg1, s16 arg2, s16 arg3);
Gfx* DoubleTextureTrail_LoadTextures(Gfx* arg0, DoubleTextureTrail* arg1);
Gfx* DoubleTextureTrail_DrawAll(Gfx* arg0);


void HyperBeamIceBeamTrail_ResetPool(void);
void HyperBeamIceBeamTrail_Spawn(s16 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, u8 arg7, u8 arg8, u8 arg9, u8 argA, u8 argB, u8 argC, u8 argD, u8 argE, u8 argF, f32 arg10, f32 arg11, f32 arg12, s16 arg13, s32 arg14, s32 arg15, s16 arg16, s16 arg17, s16 arg18, s16 arg19, s16 arg1A, s16 arg1B, s16 arg1C, s16 arg1D, unk_D_843C2C00_024* arg1E, unk_D_843C2C00_024* arg1F);
void HyperBeamIceBeamTrail_ComputeCameraRelativeOffset(s32 arg0, Vec3f* arg1, Vec3f* arg2, Vec3f* arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7);
void HyperBeamIceBeamTrail_ComputeRotatedOffset(f32 arg0, Vec3f* arg1, Vec3f* arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6);
void HyperBeamIceBeamTrail_UpdateSlot(unk_D_843C3508* arg0);
s32 HyperBeamIceBeamTrail_UpdateAll(void);
Gfx* HyperBeamIceBeamTrail_DrawSegments(Gfx* arg0, unk_D_843C3508* arg1);
Gfx* HyperBeamIceBeamTrail_LoadTextures(Gfx* arg0, unk_D_843C3508* arg1);
Gfx* HyperBeamIceBeamTrail_DrawAll(Gfx* arg0);
void AuxiliaryEffect_Init(void);
s16 AuxiliaryEffect_Alloc(void);
void AuxiliaryEffect_Spawn(s16 arg0, f32 arg1, f32 arg2, f32 arg3, s16 arg4, f32 arg5);
void AuxiliaryEffect_Update(s16 arg0);
Gfx* AuxiliaryEffect_DrawOne(Gfx* arg0, AuxiliaryEffectNode* arg1, MtxF* arg2);
Gfx* AuxiliaryEffect_Draw(s16 arg0, Gfx* arg1);
void func_8216D978(void);
void func_8216D980(void);
s32 AuxEffect_GetId(s32 arg0);


void BattleScene_SetStripWipeState(s32 arg0, s32 arg1);
s32 BattleScene_GetStripWipeState(void);
void BattleScene_UpdateStripWipe(void);
Gfx* BattleScene_BuildStripWipeDisplayList(Gfx* arg0, s32 arg1);
void BattleScene_DrawStripWipe(void);


void func_8216D988(void);


void func_8210FA74(void);
u8 Battle_Random(void);
u8 Battle_RandomAccuracy(void);
void ShowDamageMessage(s32 arg0, s32 arg1);
void Battle_ResetTransientRuntimeState(s32 arg0, s32 arg1);
void Battle_FormatDamageComment(ActivePokemon* active_pokemon);
void Battle_ApplyDamageRandomFactor(void);
u16 Battle_DetermineMoveOrder(ActivePokemon* arg0, ActivePokemon* arg1);
s32 IsByteInArray(u8 arg0, u8* arg1, s32 arg2);
void Battle_SetActiveMoveFromSlotIndex(void);
s32 Battle_CheckMoveSuccess(void);
void ComputePokemonStat(s32 arg0, BattleMon* arg1);
void ComputeAllPokemonStats(BattleMon* arg0);
void InitBattleParameters(void);
s32 Battle_CalcDamage(void);
void Battle_ApplyDamage(void);
void Battle_DecrementPP(s32 arg0);
void ApplyAccuracyStageMultipliers(void);
void MarkAttackFailed(void);
void Battle_MoveHitTest(void);
void Battle_ApplyAnimStateEffects(s32 arg0);
void ApplyParalysisSpeedCut(ActivePokemon* active_pokemon);
void ApplyBurnAttackCut(ActivePokemon* active_pokemon);
void Battle_InitPokemonRuntimeState(ActivePokemon* active_pokemon);
s32 Battle_IsPartyMemberAlive(ActivePokemon* active_pokemon);
void func_82110FB0(void);
void func_82110FB8(void);
void Battle_LoadMoveCache(void);
void Battle_HandleBuildingRage(void);
void Battle_DisplayEffectiveness(void);
void Battle_PrintCriticalOHKOText(void);
void Battle_ApplyAttackToTarget(void);
void Battle_PrintMoveFailureText(void);
void Battle_RefundSelectedMovePp(void);
s32 Battle_Effect_Metronome(void);
void Battle_ApplyPoisonOrBurnDamage(void);
void Battle_ApplyLeechSeedDamage(void);
s32 Battle_ApplyResidualEffects(void);
void func_82111870(void);
s32 Battle_TryLoadFollowupMoveFromTarget(void);
void Battle_ApplyTypeEffectAndSTAB(void);
s32 Battle_Effect_Counter(void);
s32 Battle_CheckCriticalHit(void);
s32 Battle_CheckMonCanAct(void);
void ProcessBattleTurn(void);
void Battle_HandleFaint(ActivePokemon* active_pokemon);
void Battle_CheckAllBroughtFainted_PoisonBurn(ActivePokemon* active_pokemon);
void Battle_CheckAllBroughtFainted_Status(ActivePokemon* active_pokemon);
void Battle_CheckAllBroughtFainted_PendingHp(ActivePokemon* active_pokemon);
void Battle_CheckAllBroughtFainted_Hp(ActivePokemon* active_pokemon);
s32 Battle_CheckSideDefeatAfterResidualStatus(ActivePokemon* active_pokemon);
s32 Battle_CheckFaintAfterMove(void);
void Battle_ResolveMonAction(void);
void BeginBattleForEntity(ActivePokemon* active_pokemon);


u16 Battle_ApplyStatStageMultiplier(u16* arg0, u16 arg1, u8 arg2);
void Battle_Effect_Sleep(void);
void Battle_Effect_Poison(void);
void Battle_Effect_DrainHP(void);
void BattleEffect_Explosion(void);
void Battle_Effect_SecondaryStatusChance(void);
void BattleEffect_ApplyStatBoost(void);
void Battle_Effect_RaiseOwnStat(void);
void Battle_Effect_LowerStat(void);
void BattleEffect_Bide(void);
void BattleEffect_Thrash(void);
void Battle_Effect_ForceSwitchOrFlee(void);
void BattleEffect_MultiHit(void);
void Battle_Effect_Flinch(void);
void BattleEffect_OHKO(void);
void Battle_Effect_TwoTurnMove(void);
void Battle_Effect_Trap(void);
void Battle_Effect_Mist(void);
void Battle_Effect_FocusEnergy(void);
void Battle_Effect_Recoil(void);
void Battle_Effect_ConfuseChance(void);
void Battle_Effect_Confuse(void);
void Battle_Effect_Paralyze(void);
void Battle_Effect_Substitute(void);
void BattleEffect_Recharge(void);
void BattleEffect_Rage(void);
void BattleEffect_Mimic(void);
void Battle_Effect_LeechSeed(void);
void Battle_Effect_Splash(void);
void Battle_Effect_Disable(void);
void Battle_Effect_PayDay(void);
void Battle_Effect_Conversion(void);
void Battle_Effect_Haze(void);
void Battle_Effect_Heal(void);
void Battle_Effect_Transform(void);
void Battle_Effect_ReflectLightScreen(void);
void BattleEffect_RunMoveEffect(void);
void BattleEffect_ExecuteMoveEffect(void);


void BattleAi_LoadConfiguration(s32 arg0, u32 arg1);
void func_8216D990(void);
s32 BattleAi_RandomBelowInclusive(s32 arg0);
void BattleAi_SeedRandomState(u8 arg0);
u8 BattleAi_EstimateCriticalHitChance(BattleMonRuntime* arg0, BattleMonRuntime* arg1, u8 arg2);
u16 BattleAi_ApplyMoveEffectDamageOverride(BattleMonRuntime* arg0, BattleMonRuntime* arg1);
void BattleAi_ClampDamageRatio(void);
void BattleAi_ApplyTypeEffectAndStab(BattleMonRuntime* arg0, BattleMonRuntime* arg1);
void BattleAi_PrepareDamageCalcState(BattleMonRuntime* arg0, BattleMonRuntime* arg1, u8 arg2);
void BattleAi_CalcDamage(BattleMonRuntime* arg0, BattleMonRuntime* arg1);
u16 BattleAi_PredictDamage(BattleMonRuntime* arg0, BattleMonRuntime* arg1, u8 arg2, u8 arg3);
void BattleAi_ResetTeamState(BattleAiMonState* arg0);
s32 BattleAi_ScaleSignedRatio(s32 arg0, s32 arg1);
void BattleAi_AppendTrainerTeamSpecies(TeamRoster* arg0);
s32 BattleAi_FindSpeciesIndex(s32 arg0);
s32 BattleAi_IsThresholdMet(u8 arg0, u8 arg1);
u16 BattleAi_ScaleStatHigh(BattleMonRuntime* arg0);
u16 BattleAi_ScaleStatLow(BattleMonRuntime* arg0);
f32 Battle_GetTypeEffectiveness(u8 arg0, BattleMonRuntime* arg1);
s32 BattleAi_AllCandidatesResistType(u8 arg0, BattleAiTeamState* arg1);
s32 BattleAi_IsTypeMatchupAllowed(u8 arg0, u8 arg1);
s32 BattleAi_HasCandidateStatusMask(BattleAiTeamState* arg0, u8 arg1);
u8 BattleAi_ClassifyMoveAvailability(BattleAiMonState* arg0, BattleAiMonState* arg1, u8 arg2);
void func_8216D998(void);
u8 BattleAi_FindHeuristicMove(BattleAiMonState* arg0, BattleAiMonState* arg1, u8 arg2, u8* arg3);
u8 BattleAi_SelectBestHeuristicCandidate(BattleAiMonState* arg0, BattleAiTeamState* arg1, u8* arg2, u8 arg3, u8* arg4);
s32 BattleAi_IsPriorityTableMove(u8 arg0, u8 arg1);
u8 BattleAi_ScoreCategorySetLowPP(BattleAiMonState* arg0, BattleAiMonState* arg1);
u8 BattleAi_ScoreCategorySetReady(BattleAiMonState* arg0, BattleAiMonState* arg1);
u8 BattleAi_HasExactlyOneUsableCandidate(BattleAiTeamState* arg0);
void BattleAi_InitializeOrderCandidates(TeamRoster* arg0, TeamRoster* arg1, TeamRoster* arg2, unk_D_843C5568* arg3, s32 arg4);
void BattleAi_UpdateRememberedMoveCandidate(BattleAiMonState* arg0, u8 arg1);
u16 BattleAi_ScoreMove(BattleMonRuntime* arg0, BattleMonRuntime* arg1, u8 arg2);
void BattleAi_PickBestMove(BattleMonRuntime* arg0, BattleMonRuntime* arg1, u16* arg2, u8* arg3, u8 arg4, u8 arg5);
s32 BattleAi_ScoreAllCandidateMoves(BattleAiMonState* arg0, BattleAiMonState* arg1, u8* arg2, u8 arg3);
s32 BattleAi_ScoreAllCandidateMovesRatioToMaxHp(BattleAiMonState* arg0, BattleAiMonState* arg1, u8* arg2, u8 arg3);
s32 BattleAi_ScoreAllCandidateMovesRatioToCurrentHp(BattleAiMonState* arg0, BattleAiMonState* arg1, u8* arg2, u8 arg3);
void func_8216D9A0(void);
u8 BattleAi_CalcStagedMovePower(BattleMonRuntime* arg0, BattleMonRuntime* arg1, u8 arg2, u8 arg3);
void BattleAi_ApplyInverseWeightScale(u8 arg0, u8* arg1);
void BattleAi_BuildMoveCandidateScores(BattleAiMonState* arg0, BattleAiMonState* arg1, s32 arg2, u8 arg3, u8 arg4, BattleAiScoredMove* arg5);
s32 BattleAi_HasScoredMoveAtValue(BattleAiScoredMove* arg0, u8 arg1, u8 arg2);
s32 BattleAi_IsCandidateScoreBelowPeers(BattleAiScoredMove* arg0, u8 arg1, u8 arg2, u8 arg3);
u8 BattleAi_HasOtherCandidateAtLeastScore(BattleAiScoredMove* arg0, u8 arg1, u8 arg2, u8 arg3);
void BattleAi_ApplyTypeResistance(BattleAiTeamState* arg0, BattleAiTeamState* arg1, u8 arg2, BattleAiScoredMove* arg3, u8 arg4);
s32 BattleAi_IsScoreBetter(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 BattleAi_SelectBestScoredMove(BattleAiMonState* arg0, UNUSED BattleAiMonState* arg1, u8 arg2, BattleAiScoredMove* arg3);
s32 BattleAi_ChooseMoveForCandidate(void);
u16 BattleAi_ComputeDifficultyThreshold(u8 arg0, u8 arg1);
u8 BattleAi_GetPpWeight(u8 arg0);
void BattleAi_InitTeamContext(TeamRoster* arg0, TeamRoster* arg1, BattleAiTeamState* arg2, u8 arg3);
s32 BattleAi_IsSpeciesUnselected(BattleAiTeamState* arg0, u8* arg1, u8 arg2);
s32 BattleAi_IsSpeciesInList(BattleAiTeamState* arg0, u8* arg1, u8 arg2, u8 arg3);
s32 BattleAi_MeetsHpBudgetConstraint(BattleAiTeamState* arg0, u8* arg1, u8 arg2, s32 arg3);
s32 BattleAi_IsCandidateEligible(BattleAiTeamState* arg0, u8* arg1, u8 arg2, u8 arg3);
s32 BattleAi_GroupSharesTypeWeakness(BattleAiTeamState* arg0, u8* arg1, u8 arg2);
s32 BattleAi_ScoreAllTeamCandidates(BattleAiTeamState* arg0, BattleAiTeamState* arg1, u8* arg2, s32* arg3);
s32 BattleAi_InsertRankedCandidateGroup(BattleAiTeamState* arg0, s32* arg1, s32 arg2, unk_func_8437F85C_arg3* arg3, u8* arg4, u8 arg5, u8 arg6);
void BattleAi_SelectRandomFallbackOrder(BattleAiTeamState* arg0, u8* arg1, s32 arg2);
s32 BattleAi_SelectRandomUsableCandidate(BattleAiTeamState* arg0);
s32 BattleAi_SelectRandomUsableMoveSlot(BattleMonRuntime* arg0);
s32 BattleAi_SelectTeamOrder(BattleAiTeamState* arg0, u8* arg1, s32* arg2, u8 arg3);
s32 BattleAi_SelectLeadFromScoredGroup(BattleAiTeamState* arg0, BattleAiTeamState* arg1, u8* arg2, u8* arg3, s32* arg4);
s32 BattleAi_TryBuildScoredOrder(BattleAiTeamState* arg0, BattleAiTeamState* arg1, u8* arg2, u8* arg3, s32 arg4);
void BattleAi_UpdateTeamAdvantageBias(void);
u8 BattleAi_SelectBestSwitchCandidateIndex(BattleAiTeamState* arg0, BattleAiTeamState* arg1);
u8 BattleAi_SelectBestAttackTargetIndex(BattleAiMonState* arg0, s32* arg1, s32* arg2, BattleAiTeamState* arg3, u8 arg4, s32 arg5);
s32 BattleAi_ScoreSwitchUrgencyFromThreatMove(BattleAiMonState* arg0, BattleAiMonState* arg1, u8 arg2);
s32 BattleAi_ComputeAttackTargetScore(unk_func_8438220C* arg0);
s32 BattleAi_ScoreAttackOption(BattleAiMonState* arg0, BattleAiMonState* arg1, BattleAiTeamState* arg2, u8* arg3, s32* arg4, s32* arg5, s32* arg6, s32* arg7, s32* arg8);
s32 BattleAi_ScoreAttackOptionDoubles(BattleAiMonState* arg0, BattleAiMonState* arg1, BattleAiTeamState* arg2, u8* arg3, unk_func_8438220C* arg4);
u8 BattleAi_ScoreAttackVsSwitch(BattleAiMonState* arg0, BattleAiMonState* arg1, BattleAiTeamState* arg2, BattleAiTeamState* arg3, u8* arg4, unk_func_8438220C* arg5);
u16 BattleAi_ApplyStatStageModifier(u16* arg0, u16 arg1, u8 arg2);
void BattleAi_SimulateStatBoostGuess(BattleMonRuntime* arg0, BattleMonRuntime* arg1, u8 arg2, u8 arg3);
void BattleAi_BuildAllCandidateMoveScores(unk_func_8438220C* arg0);
void BattleAi_RefineAllCandidateMoveScores(unk_func_8438220C* arg0);
u8 BattleAi_DecideFinalAction(unk_func_8438220C* arg0);
s32 BattleAi_DecideAction(void);
s32 BattleAi_ResolveTiedActionChoice(s32 arg0);
s32 BattleAi_MatchesLastMoveCategory(u8 arg0, u8 arg1);
s32 BattleAi_IsDiscouragedRepeatCategory(u8 arg0, u8 arg1);
s32 BattleAi_IsBannedRandomMove(u8 arg0);
s32 BattleAi_OpponentCannotAct(s8* arg0, s8* arg1);
s32 BattleAi_IsMoveExcludedForSpecies(BattleMonRuntime* arg0, s32 arg1, u8 arg2, u8 arg3);
s32 BattleAi_IsMoveIneffective(BattleMonRuntime* arg0, BattleMonRuntime* arg1, u8 arg2);
void BattleAi_SyncTeamStateFromRuntime(void);

void BattleAi_RecordUsedMove(UNUSED s32 arg0, UNUSED s32 arg1, s32 arg2);
s32 BattleAi_ChooseAction(UNUSED s32 arg0);
void BattleAi_InitTrainerRecords(void);
s32 BattleAi_ResolveRandomMove(s32 arg0, s32 arg1);

#endif // _FRAGMENT62_H_
