
#pragma once

#include "texture.h"
#include "sampler.h"
#include "shader_program.h"

typedef unsigned int MaterialID;

typedef struct MaterialCreateInfo
{
    ShaderProgramID shaderProgram;
    const TextureID* textures;
    unsigned int textureCount;
    const SamplerID* samplers;
    unsigned int samplerCount;
} MaterialCreateInfo;

MaterialID materialCreate(const MaterialCreateInfo* materialCreateInfo);
void materialDestroy(MaterialID material);
void materialDestroyWithDependencies(MaterialID material);

void materialBind(MaterialID material);

void materialDestroyAll();

void materialDestroyAllWithDependencies();

