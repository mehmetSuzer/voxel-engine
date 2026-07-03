
#pragma once

#include "mesh.h"
#include "material.h"

#define MODEL_MAX_MESH_MATERIAL_COUNT 4

typedef struct MeshMaterialPair
{
    MeshID meshID;
    MaterialID materialID;
} MeshMaterialPair;

typedef uint32_t ModelID;

ModelID modelCreate(const MeshMaterialPair* meshMaterialPairs, uint32_t meshMaterialPairCount);

void modelDestroy(ModelID modelID);

bool modelIsActive(ModelID modelID);

void modelDraw(ModelID modelID);

