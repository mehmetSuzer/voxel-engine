
#pragma once

#include <cglm/cglm.h>

typedef struct Vertex
{
    vec3 position;
    vec3 normal;
    vec3 tangent;
    vec2 texCoord;
} Vertex;

void vertexLinkAttributes();

