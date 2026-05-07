
#include <string.h>
#include "error.h"
#include "material.h"
#include "log/log.h"

#define MATERIAL_MAX_TEXTURE_COUNT 4u

typedef struct Material
{
    ShaderProgramID shaderProgram;
    TextureID textures[MATERIAL_MAX_TEXTURE_COUNT];
    unsigned int textureCount;
    SamplerID samplers[MATERIAL_MAX_TEXTURE_COUNT];
    unsigned int samplerCount;
} Material;

static Material* materials = NULL;
static unsigned int materialCount = 0u;

MaterialID materialCreate(const MaterialCreateInfo* materialCreateInfo)
{
    const unsigned int newMaterialCount = materialCount + 1u;
    materials = (Material*)realloc(materials, newMaterialCount * sizeof(Material));

    materials[materialCount].shaderProgram = materialCreateInfo->shaderProgram;
    materials[materialCount].textureCount = materialCreateInfo->textureCount;
    materials[materialCount].samplerCount = materialCreateInfo->samplerCount;
    memcpy(materials[materialCount].textures, materialCreateInfo->textures, materialCreateInfo->textureCount * sizeof(TextureID));
    memcpy(materials[materialCount].samplers, materialCreateInfo->samplers, materialCreateInfo->samplerCount * sizeof(SamplerID));

    const MaterialID material = materialCount;
    materialCount = newMaterialCount;
    return material;
}

void materialDestroy(MaterialID material)
{
    const unsigned int newMaterialCount = materialCount - 1u;
    if (newMaterialCount == 0u)
    {
        free(materials);
        materials = NULL;
        materialCount = 0u;
    }
    else
    {
        materials[material] = materials[newMaterialCount];
        materials = (Material*)realloc(materials, newMaterialCount * sizeof(Material));
        materialCount = newMaterialCount;
    }
}

void materialDestroyWithDependencies(MaterialID material)
{
    shaderProgramDestroy(materials[material].shaderProgram);
    for (unsigned int i = 0u; i < materials[material].textureCount; ++i)
    {
        textureDestroy(materials[material].textures[i]);
    }
    for (unsigned int i = 0u; i < materials[material].samplerCount; ++i)
    {
        samplerDestroy(materials[material].samplers[i]);
    }
    materialDestroy(material);
}

void materialBind(MaterialID material)
{
    const Material* mat = &materials[material];
    shaderProgramBind(mat->shaderProgram);
    for (unsigned int unit = 0u; unit < mat->textureCount; ++unit)
    {
        textureBind(mat->textures[unit], unit);
    }
    for (unsigned int unit = 0u; unit < mat->samplerCount; ++unit)
    {
        samplerBind(mat->samplers[unit], unit);
    }
}

void materialDestroyAll()
{
    free(materials);
    materials = NULL;
    materialCount = 0u;
}

void materialDestroyAllWithDependencies()
{
    for (unsigned int material = 0u; material < materialCount; ++material)
    {
        materialDestroyWithDependencies(material);
    }
}

