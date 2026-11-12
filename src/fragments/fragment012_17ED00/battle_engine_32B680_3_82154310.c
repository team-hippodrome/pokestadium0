/* Fixed-layout split; original translation-unit boundaries remain unconfirmed. */
#include "battle_engine_32B680_3.h"

/**
 * @unverified Name was previously used only by callers of this address; the definition was still func_.
 */
void BattleAnim_ApplyModelSpeciesOffset(Particle* arg0) {
    f32 offset = 0.0f;

    switch (BattleAnim_GetOwnerSpecies(arg0->unk_10)) {
        case 0xF:
            offset = -13.0f;
            break;
        case 0x16:
            offset = -15.0f;
            break;
        case 0x19:
            offset = -10.0f;
            break;
        case 0x22:
            offset = 10.0f;
            break;
        case 0x3B:
            offset = 25.0f;
            break;
        case 0x4C:
            offset = -10.0f;
            break;
        case 0x52:
            offset = -8.0f;
            break;
        case 0x5B:
            offset = -12.0f;
            break;
        case 0x67:
            offset = 5.0f;
            Particle_Field38_AddXZFromField94Y_08ED0(arg0, 10.0f);
            break;
        case 0x79:
            offset = -8.0f;
            break;
        case 0x7F:
            offset = 5.0f;
            break;
        case 0x80:
            offset = -12.0f;
            break;
        case 0x82:
            offset = -10.0f;
            Particle_Field1C_SetScaled_0B938(arg0, 0.15f);
            break;
        case 0x86:
            offset = -5.0f;
            Particle_Field38_AddXZFromField94YOffsetMinus90_0901C(arg0, 5.0f);
            break;
        case 0x87:
            offset = -15.0f;
            break;
    }
    Particle_Field38_AddYScaled_08E90(arg0, offset);
}
