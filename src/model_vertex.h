/* Declarations for src/model_vertex.c, src/model_vertex_2.c, src/model_vertex_3.c, src/model_vertex_4.c. */
#ifndef MODEL_VERTEX_H
#define MODEL_VERTEX_H

#include "global.h"

#include "model_vertex_draw.h"

// model_vertex_2.c
void func_80033BBC(StadiumModel* model, MtxF* mtx);
void func_80033750(void);

// model_vertex_3.c
void Model_InitializeVertexPositions(ModelSegment*, MtxF*, ModelVertex*);

// model_vertex_4.c
void func_800350E0(void);

#endif // MODEL_VERTEX_H
