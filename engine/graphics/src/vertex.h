
#pragma once

#include <cglm/cglm.h>
#include "vertex_array.h"

typedef void (*VertexLinkAttributesFunction)(VertexArrayID);

typedef struct VertexStatic
{
    vec3 position;
    vec3 normal;
    vec3 tangent;
    vec2 texCoords;
} VertexStatic;

void vertexStaticLinkAttributes(VertexArrayID VAO);

typedef struct VertexUI
{
    vec2 position;
    vec2 texCoords;
} VertexUI;

void vertexUILinkAttributes(VertexArrayID VAO);

typedef struct VertexSkinned
{
    vec3 position;
    vec3 normal;
    vec3 tangent;
    vec2 texCoords;
    uint32_t boneIDs[4];
    float weights[4];
} VertexSkinned;

void vertexSkinnedLinkAttributes(VertexArrayID VAO);

typedef uint32_t VertexVoxel;

void vertexVoxelLinkAttributes(VertexArrayID VAO);

