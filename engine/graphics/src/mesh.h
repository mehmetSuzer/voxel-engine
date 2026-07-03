
#pragma once

#include <stdbool.h>
#include "vertex.h"
#include "graphics/enums.h"

typedef uint32_t MeshID;

MeshID meshCreatePBR(const VertexPBR* vertices, uint32_t vertexCount, const uint32_t* indices, uint32_t indexCount, DrawMode drawMode);
MeshID meshCreateVoxel(const VertexVoxel* vertices, uint32_t vertexCount, const uint32_t* indices, uint32_t indexCount, DrawMode drawMode);

void meshDestroy(MeshID meshID);
void meshDestroyAll();

bool meshIsActive(MeshID meshID);

void meshDraw(MeshID meshID);

