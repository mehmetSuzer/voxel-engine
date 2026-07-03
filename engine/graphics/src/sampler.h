
#pragma once

#include <stdbool.h>
#include "graphics/enums.h"

typedef uint32_t SamplerID;

#define SAMPLER_NULL ((SamplerID)0)

typedef struct SamplerCreateInfo
{
    TextureMinFilter textureMinFilter;
    TextureMagFilter textureMagFilter;
    TextureWrap textureWrapS;
    TextureWrap textureWrapT;
    TextureWrap textureWrapR;
    float minLOD;
    float maxLOD;
    float biasLOD;
    CompareMode compareMode;
    CompareFunc compareFunc;
    float borderColour[4]; // only matters if wrapS, wrapT, or wrapR is WrapClampToBorder
} SamplerCreateInfo;

void samplerGetDefaultCreateInfo(SamplerCreateInfo* samplerCreateInfoOut);

SamplerID samplerCreate(const SamplerCreateInfo* samplerCreateInfo);

void samplerDestroy(SamplerID samplerID);

bool samplerIsActive(SamplerID samplerID);

void samplerBind(SamplerID samplerID, uint32_t unit);

