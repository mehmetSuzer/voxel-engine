
#pragma once

#include "enums.h"
#include "vertex.h"

typedef unsigned int MeshID;

MeshID meshCreate(const Vertex* vertices, unsigned int vertexCount, const unsigned int* indices, unsigned int indexCount, DrawMode drawMode);
void meshDestroy(MeshID meshID);
void meshDraw(MeshID meshID);

