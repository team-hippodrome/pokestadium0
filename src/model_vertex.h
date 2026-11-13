/* Declarations for src/model_vertex.c, src/model_vertex_2.c, src/model_vertex_3.c, src/model_vertex_4.c. */
#ifndef MODEL_VERTEX_H
#define MODEL_VERTEX_H

#include "global.h"

/* Struct types that were defined identically in each of these files; this is
 * now the one definition they all include:
 * src/33FE0.c
 * src/DDC0.c
 * src/DDC0_2.c
 * src/DDC0_3.c
 * src/save_data.c
 */

typedef struct unk_D_800A8480 {
  /* 0x0000 */ OSThread thread;
  /* 0x01B0 */ char unk01B0[0x2030];
} unk_D_800A8480;

#include "model_vertex_draw.h"

// model_vertex_2.c
void func_80033BBC(StadiumModel* model, MtxF* mtx);
void func_80033750(void);

// model_vertex_3.c
void Model_InitializeVertexPositions(ModelSegment*, MtxF*, ModelVertex*);

// model_vertex_4.c
void func_800350E0(void);

#endif // MODEL_VERTEX_H
