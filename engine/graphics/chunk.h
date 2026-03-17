
#pragma once

#include <cglm/cglm.h>
#include "glad/glad.h"

#define CHUNK_SIZE 32

typedef unsigned char Voxel;

#define VOXEL_AIR     ((Voxel)0)
#define VOXEL_BLACK   ((Voxel)1)
#define VOXEL_RED     ((Voxel)2)
#define VOXEL_GREEN   ((Voxel)3)
#define VOXEL_BLUE    ((Voxel)4)
#define VOXEL_YELLOW  ((Voxel)5)
#define VOXEL_MAGENTA ((Voxel)6)
#define VOXEL_CYAN    ((Voxel)7)
#define VOXEL_WHITE   ((Voxel)8)

typedef struct
{
    GLuint VAO;
    GLuint VBO;
    GLsizei numVertices;
    vec3 worldPosition;
    Voxel voxels[CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE];
} Chunk;

void ChunkCreate(Chunk* chunkOut);

void ChunkDelete(const Chunk* chunk);

void ChunkDraw(const Chunk* chunk);

