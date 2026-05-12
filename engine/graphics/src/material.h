
#pragma once

#include "texture.h"
#include "sampler.h"
#include "shader_program.h"

#define MATERIAL_MAX_TEXTURE_COUNT 4u
#define MATERIAL_MAX_SAMPLER_COUNT 4u

typedef unsigned int MaterialID;

typedef struct MaterialCreateInfo
{
    ShaderProgramID shaderProgramID;
    TextureID textureIDs[MATERIAL_MAX_TEXTURE_COUNT];
    unsigned int textureCount;
    SamplerID samplerIDs[MATERIAL_MAX_SAMPLER_COUNT];
    unsigned int samplerCount;
} MaterialCreateInfo;

MaterialID materialCreate(const MaterialCreateInfo* materialCreateInfo);

void materialDestroy(MaterialID materialID);
void materialDestroyWithDependencies(MaterialID materialID);
void materialDestroyAll();
void materialDestroyAllWithDependencies();

int materialIsActive(MaterialID materialID);

void materialBind(MaterialID materialID);

