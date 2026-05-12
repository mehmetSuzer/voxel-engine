
#pragma once

#include "mesh.h"
#include "material.h"

#define MODEL_MAX_MESH_MATERIAL_COUNT 4u

typedef struct MeshMaterialPair
{
    MeshID meshID;
    MaterialID materialID;
} MeshMaterialPair;

typedef unsigned int ModelID;

ModelID modelCreate(const MeshMaterialPair* meshMaterialPairs, unsigned int meshMaterialPairCount);

void modelDestroy(ModelID modelID);

int modelIsActive(ModelID modelID);

void modelDraw(ModelID modelID);

