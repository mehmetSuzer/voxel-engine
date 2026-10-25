
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
    CompareFunction compareFunction;
    float minLevelOfDetail;
    float maxLevelOfDetail;
    float biasLevelOfDetail;
    float maxAnisotropy;
    float borderColour[4]; // matters only if wrapS, wrapT, or wrapR is TextureWrapClampToBorder
} SamplerCreateInfo;

void samplerGetDefaultCreateInfo(SamplerCreateInfo* samplerCreateInfoOut);

SamplerID samplerCreate(const SamplerCreateInfo* samplerCreateInfo);

void samplerDestroy(SamplerID samplerID);

#ifndef NDEBUG
void samplerSetLabel(SamplerID samplerID, const char* label);
void samplerGetLabel(SamplerID samplerID, int32_t maxLabelLength, int32_t* labelLengthOut, char* labelOut);
#endif

bool samplerIsActive(SamplerID samplerID);

void samplerBind(SamplerID samplerID, uint32_t unit);

