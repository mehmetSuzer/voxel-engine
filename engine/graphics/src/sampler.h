
#pragma once

#include "enums.h"

typedef unsigned int SamplerID;

#define SAMPLER_NULL ((SamplerID)0)

typedef struct SamplerCreateInfo
{
    MinFilter minFilter;
    MagFilter magFilter;
    Wrap wrapS;
    Wrap wrapT;
    Wrap wrapR;
    float minLOD;
    float maxLOD;
    float biasLOD;
    CompareMode compareMode;
    CompareFunc compareFunc;
    float borderColour[4]; // only matters if wrapS, wrapT, or wrapR is WrapClampToBorder
} SamplerCreateInfo;

void samplerGetDefaultCreateInfo(SamplerCreateInfo* samplerCreateInfoOut);

SamplerID samplerCreate(const SamplerCreateInfo* samplerCreateInfo);
void samplerDestroy(SamplerID sampler);

void samplerBind(SamplerID sampler, unsigned int unit);

int samplerIsActive(SamplerID sampler);

