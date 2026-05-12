
#pragma once

#include "enums.h"
#include "vertex.h"

typedef unsigned int MeshID;

MeshID meshCreatePBR(const VertexPBR* vertices, unsigned int vertexCount, const unsigned int* indices, unsigned int indexCount, DrawMode drawMode);
MeshID meshCreateVoxel(const VertexVoxel* vertices, unsigned int vertexCount, const unsigned int* indices, unsigned int indexCount, DrawMode drawMode);

void meshDestroy(MeshID meshID);
void meshDestroyAll();

int meshIsActive(MeshID meshID);

void meshDraw(MeshID meshID);

