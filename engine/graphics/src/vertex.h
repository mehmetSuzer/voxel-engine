
#pragma once

#include <cglm/cglm.h>

typedef struct VertexPBR
{
    vec3 position;
    vec3 normal;
    vec3 tangent;
    vec2 texCoord;
} VertexPBR;

void vertexPBRLinkAttributes();

typedef unsigned int VertexVoxel;

void vertexVoxelLinkAttributes();

