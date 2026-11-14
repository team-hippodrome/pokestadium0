/* Declarations for src/model_vertex.c, src/model_vertex_2.c, src/model_vertex_3.c, src/model_vertex_4.c. */
#ifndef MODEL_VERTEX_H
#define MODEL_VERTEX_H

#include "global.h"

#include "model_vertex_draw.h"

// model_vertex_2.c
void Model_RebuildVertexData(StadiumModel* model, MtxF* mtx);
void Model_UnusedStub(void);

// model_vertex_3.c
void Model_InitializeVertexPositions(ModelSegment*, MtxF*, ModelVertex*);

// model_vertex_4.c
void Model_UnusedStub2(void);

#endif // MODEL_VERTEX_H
