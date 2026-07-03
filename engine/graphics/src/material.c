
#include <string.h>
#include "error.h"
#include "material.h"
#include "log/log.h"

typedef struct Material
{
    ShaderProgramID shaderProgramID;
    TextureID textureIDs[MATERIAL_MAX_TEXTURE_COUNT];
    uint32_t textureCount;
    SamplerID samplerIDs[MATERIAL_MAX_SAMPLER_COUNT];
    uint32_t samplerCount;
    bool active;
} Material;

typedef struct MaterialArray
{
    Material* data;
    uint32_t size;
    uint32_t capacity;
} MaterialArray;

static MaterialArray materialArray = {0};

static MaterialID materialArrayPush(const Material* material)
{
    MaterialID materialID = 0;
    while (materialID < materialArray.size && materialArray.data[materialID].active) 
    { 
        materialID++;
    }

    if (materialID < materialArray.size)
    {
        memcpy(&materialArray.data[materialID], material, sizeof(Material));
        return materialID;
    }

    if (materialID < materialArray.capacity)
    {
        memcpy(&materialArray.data[materialID], material, sizeof(Material));
        materialArray.size++;
        return materialID;
    }

    const uint32_t newCapacity = (materialArray.capacity != 0) ? 2 * materialArray.capacity : 8;
    materialArray.data = (Material*)realloc(materialArray.data, newCapacity * sizeof(Material));
    materialArray.capacity = newCapacity;

    memcpy(&materialArray.data[materialID], material, sizeof(Material));
    materialArray.size++;
    return materialID;
}

MaterialID materialCreate(const MaterialCreateInfo* materialCreateInfo)
{
    Material material;
    material.active = true;
    material.shaderProgramID = materialCreateInfo->shaderProgramID;
    material.textureCount = materialCreateInfo->textureCount;
    material.samplerCount = materialCreateInfo->samplerCount;
    memcpy(material.textureIDs, materialCreateInfo->textureIDs, materialCreateInfo->textureCount * sizeof(TextureID));
    memcpy(material.samplerIDs, materialCreateInfo->samplerIDs, materialCreateInfo->samplerCount * sizeof(SamplerID));

    const MaterialID materialID = materialArrayPush(&material);
    return materialID;
}

void materialDestroy(MaterialID materialID)
{
    Material* material = &materialArray.data[materialID];
    *material = (Material){0};
}

void materialDestroyWithDependencies(MaterialID materialID)
{
    Material* material = &materialArray.data[materialID];
    shaderProgramDestroy(material->shaderProgramID);
    for (uint32_t i = 0; i < material->textureCount; ++i)
    {
        textureDestroy(material->textureIDs[i]);
    }
    for (uint32_t i = 0; i < material->samplerCount; ++i)
    {
        samplerDestroy(material->samplerIDs[i]);
    }
    *material = (Material){0};
}

void materialDestroyAll()
{
    free(materialArray.data);
    materialArray.size = 0;
    materialArray.capacity = 0;
}

void materialDestroyAllWithDependencies()
{
    for (MaterialID materialID = 0; materialID < materialArray.size; ++materialID)
    {
        Material* material = &materialArray.data[materialID];
        if (material->active)
        {
            materialDestroyWithDependencies(materialID);
        }
    }
}

bool materialIsActive(MaterialID materialID)
{
    return (materialID < materialArray.size && materialArray.data[materialID].active);
}

void materialBind(MaterialID materialID)
{
    const Material* material = &materialArray.data[materialID];
    shaderProgramBind(material->shaderProgramID);
    for (uint32_t unit = 0; unit < material->textureCount; ++unit)
    {
        textureBindSampler(material->textureIDs[unit], unit);
    }
    for (uint32_t unit = 0; unit < material->samplerCount; ++unit)
    {
        samplerBind(material->samplerIDs[unit], unit);
    }
    logVerbose("MATERIAL", "binded: %u", materialID);
}

