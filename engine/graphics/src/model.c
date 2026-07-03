
#include <string.h>
#include "model.h"
#include "log/log.h"

typedef struct Model
{
    MeshMaterialPair meshMaterialPairs[MODEL_MAX_MESH_MATERIAL_COUNT];
    uint32_t meshMaterialPairCount;
    bool active;
} Model;

typedef struct ModelArray
{
    Model* data;
    uint32_t size;
    uint32_t capacity;
} ModelArray;

static ModelArray modelArray = {0};

static ModelID modelArrayPush(const Model* model)
{
    ModelID modelID = 0;
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

    const uint32_t newCapacity = (modelArray.capacity != 0) ? 2 * modelArray.capacity : 8;
    modelArray.data = (Model*)realloc(modelArray.data, newCapacity * sizeof(Model));
    modelArray.capacity = newCapacity;

    memcpy(&modelArray.data[modelID], model, sizeof(Model));
    modelArray.size++;
    return modelID;
}

ModelID modelCreate(const MeshMaterialPair* meshMaterialPairs, uint32_t meshMaterialPairCount)
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

bool modelIsActive(ModelID modelID)
{
    return (modelID < modelArray.size && modelArray.data[modelID].active);
}

void modelDraw(ModelID modelID)
{
    const Model* model = &modelArray.data[modelID];
    for (uint32_t i = 0; i < model->meshMaterialPairCount; ++i)
    {
        materialBind(model->meshMaterialPairs[i].materialID);
        meshDraw(model->meshMaterialPairs[i].meshID);
    }
    logVerbose("MODEL", "drawn: %u", modelID);
}

