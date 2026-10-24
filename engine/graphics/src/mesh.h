
#pragma once

#include <stdbool.h>
#include "vertex.h"
#include "graphics/enums.h"

typedef uint32_t MeshID;

typedef struct MeshCreateInfo
{
#ifndef NDEBUG
    const char* label;
#endif
    VertexLinkAttributesFunction vertexLinkAttributeFunction;
    const void* vertices;
    const uint32_t* indices;
    uint32_t vertexCount;
    uint32_t indexCount;
    uint32_t vertexSize;
    DrawMode drawMode;
} MeshCreateInfo;

MeshID meshCreate(const MeshCreateInfo* meshCreateInfo);

void meshDestroy(MeshID meshID);
void meshDestroyAll();

bool meshIsActive(MeshID meshID);

void meshDraw(MeshID meshID);

