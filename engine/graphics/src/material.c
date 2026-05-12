
#include <string.h>
#include "error.h"
#include "material.h"
#include "log/log.h"

typedef struct Material
{
    ShaderProgramID shaderProgram;
    TextureID textures[MATERIAL_MAX_TEXTURE_COUNT];
    unsigned int textureCount;
    SamplerID samplers[MATERIAL_MAX_SAMPLER_COUNT];
    unsigned int samplerCount;
    int active;
} Material;

typedef struct MaterialArray
{
    Material* data;
    unsigned int size;
    unsigned int capacity;
} MaterialArray;

static MaterialArray materialArray = {0};

static MaterialID materialArrayPush(const Material* material)
{
    MaterialID materialID = 0u;
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

    const unsigned int newCapacity = (materialArray.capacity != 0u) ? 2u * materialArray.capacity : 8u;
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
    material.shaderProgram = materialCreateInfo->shaderProgram;
    material.textureCount = materialCreateInfo->textureCount;
    material.samplerCount = materialCreateInfo->samplerCount;
    memcpy(material.textures, materialCreateInfo->textures, materialCreateInfo->textureCount * sizeof(TextureID));
    memcpy(material.samplers, materialCreateInfo->samplers, materialCreateInfo->samplerCount * sizeof(SamplerID));

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
    shaderProgramDestroy(material->shaderProgram);
    for (unsigned int i = 0u; i < material->textureCount; ++i)
    {
        textureDestroy(material->textures[i]);
    }
    for (unsigned int i = 0u; i < material->samplerCount; ++i)
    {
        samplerDestroy(material->samplers[i]);
    }
    *material = (Material){0};
}

void materialDestroyAll()
{
    free(materialArray.data);
    materialArray.size = 0u;
    materialArray.capacity = 0u;
}

void materialDestroyAllWithDependencies()
{
    for (MaterialID materialID = 0u; materialID < materialArray.size; ++materialID)
    {
        Material* material = &materialArray.data[materialID];
        if (material->active)
        {
            materialDestroyWithDependencies(materialID);
        }
    }
}

int materialIsActive(MaterialID materialID)
{
    return (materialID < materialArray.size && materialArray.data[materialID].active);
}

void materialBind(MaterialID materialID)
{
    const Material* material = &materialArray.data[materialID];
    shaderProgramBind(material->shaderProgram);
    for (unsigned int unit = 0u; unit < material->textureCount; ++unit)
    {
        textureBind(material->textures[unit], unit);
    }
    for (unsigned int unit = 0u; unit < material->samplerCount; ++unit)
    {
        samplerBind(material->samplers[unit], unit);
    }
}

