
#include <string.h>
#include "model.h"
#include "log/log.h"

typedef struct Model
{
    MeshMaterialPair meshMaterialPairs[MODEL_MAX_MESH_MATERIAL_COUNT];
    unsigned int meshMaterialPairCount;
    int active;
} Model;

typedef struct ModelArray
{
    Model* data;
    unsigned int size;
    unsigned int capacity;
} ModelArray;

static ModelArray modelArray = {0};

static ModelID modelArrayPush(const Model* model)
{
    ModelID modelID = 0u;
    while (modelID < modelArray.size && modelArray.data[modelID].active) 
    { 
        modelID++;
    }

    if (modelID < modelArray.size)
    {
        memcpy(&modelArray.data[modelID], model, sizeof(Model));
        return modelID;
    }

    if (modelID < modelArray.capacity)
    {
        memcpy(&modelArray.data[modelID], model, sizeof(Model));
        modelArray.size++;
        return modelID;
    }

    const unsigned int newCapacity = (modelArray.capacity != 0u) ? 2u * modelArray.capacity : 8u;
    modelArray.data = (Model*)realloc(modelArray.data, newCapacity * sizeof(Model));
    modelArray.capacity = newCapacity;

    memcpy(&modelArray.data[modelID], model, sizeof(Model));
    modelArray.size++;
    return modelID;
}

ModelID modelCreate(const MeshMaterialPair* meshMaterialPairs, unsigned int meshMaterialPairCount)
{
    Model model;
    model.active = true;
    model.meshMaterialPairCount = meshMaterialPairCount;
    memcpy(model.meshMaterialPairs, meshMaterialPairs, meshMaterialPairCount * sizeof(MeshMaterialPair));

    const ModelID modelID = modelArrayPush(&model);
    return modelID;
}

void modelDestroy(ModelID modelID)
{
    Model* model = &modelArray.data[modelID];
    *model = (Model){0};
}

int modelIsActive(ModelID modelID)
{
    return (modelID < modelArray.size && modelArray.data[modelID].active);
}

void modelDraw(ModelID modelID)
{
    const Model* model = &modelArray.data[modelID];

    for (unsigned int i = 0u; i < model->meshMaterialPairCount; ++i)
    {
        materialBind(model->meshMaterialPairs[i].materialID);
        meshDraw(model->meshMaterialPairs[i].meshID);
    }
    logVerbose("MODEL", "drawn: %u", modelID);
}

