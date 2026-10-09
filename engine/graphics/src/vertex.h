
#pragma once

#include <cglm/cglm.h>

typedef struct VertexStatic
{
    vec3 position;
    vec3 normal;
    vec3 tangent;
    vec2 texture;
} VertexStatic;

typedef struct VertexStaticPacked
{
    vec3 positionXYZ;
    vec2 normalXY;
    vec2 tangentXY;
    vec2 textureUV;
} VertexStaticPacked;

typedef uint32_t VertexVoxel;

