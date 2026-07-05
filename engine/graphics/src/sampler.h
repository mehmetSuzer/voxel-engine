
#pragma once

#include <stdbool.h>
#include "graphics/enums.h"

typedef uint32_t SamplerID;

#define SAMPLER_NULL ((SamplerID)0)

typedef struct SamplerCreateInfo
{
    TextureWrap textureWrapS;
    TextureWrap textureWrapT;
    TextureWrap textureWrapR;
    TextureMinFilter textureMinFilter;
    TextureMagFilter textureMagFilter;
    CompareMode compareMode;
    CompareFunc compareFunc;
    float minLOD;
    float maxLOD;
    float biasLOD;
    float maxAnisotropy;
    float borderColour[4]; // only matters if wrapS, wrapT, or wrapR is WrapClampToBorder
} SamplerCreateInfo;

void samplerGetDefaultCreateInfo(SamplerCreateInfo* samplerCreateInfoOut);

SamplerID samplerCreate(const SamplerCreateInfo* samplerCreateInfo);

void samplerDestroy(SamplerID samplerID);

bool samplerIsActive(SamplerID samplerID);

void samplerBind(SamplerID samplerID, uint32_t unit);
void samplerBindMultiple(const SamplerID* samplers, uint32_t firstUnit, uint32_t count);

