
#pragma once

#include "texture.h"
#include "sampler.h"
#include "shader_program.h"

#define MATERIAL_MAX_TEXTURE_COUNT 4
#define MATERIAL_MAX_SAMPLER_COUNT 4

typedef uint32_t MaterialID;

typedef struct MaterialCreateInfo
{
    ShaderProgramID shaderProgramID;
    TextureID textureIDs[MATERIAL_MAX_TEXTURE_COUNT];
    uint32_t textureCount;
    SamplerID samplerIDs[MATERIAL_MAX_SAMPLER_COUNT];
    uint32_t samplerCount;
} MaterialCreateInfo;

MaterialID materialCreate(const MaterialCreateInfo* materialCreateInfo);

void materialDestroy(MaterialID materialID);
void materialDestroyWithDependencies(MaterialID materialID);
void materialDestroyAll();
void materialDestroyAllWithDependencies();

bool materialIsActive(MaterialID materialID);

void materialBind(MaterialID materialID);

