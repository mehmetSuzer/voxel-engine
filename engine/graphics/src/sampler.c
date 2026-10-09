
#include <stddef.h>
#include <assert.h>
#include "sampler.h"
#include "log/log.h"
#include "glad/glad.h"

void samplerGetDefaultCreateInfo(SamplerCreateInfo* samplerCreateInfoOut)
{
    assert(samplerCreateInfoOut != NULL);

    samplerCreateInfoOut->textureWrapS = TextureWrapRepeat;
    samplerCreateInfoOut->textureWrapT = TextureWrapRepeat;
    samplerCreateInfoOut->textureWrapR = TextureWrapRepeat;

    samplerCreateInfoOut->textureMinFilter = TextureMinFilterLinearMipmapLinear;
    samplerCreateInfoOut->textureMagFilter = TextureMagFilterLinear;

    samplerCreateInfoOut->compareMode = CompareModeNone;
    samplerCreateInfoOut->compareFunction = CompareFunctionLessEqual;

    samplerCreateInfoOut->minLevelOfDetail = -1000.0f;
    samplerCreateInfoOut->maxLevelOfDetail = 1000.0f;
    samplerCreateInfoOut->biasLevelOfDetail = 0.0f;
    samplerCreateInfoOut->maxAnisotropy = 1.0f;

    samplerCreateInfoOut->borderColour[0] = 0.0f;
    samplerCreateInfoOut->borderColour[1] = 0.0f;
    samplerCreateInfoOut->borderColour[2] = 0.0f;
    samplerCreateInfoOut->borderColour[3] = 1.0f;
}

SamplerID samplerCreate(const SamplerCreateInfo* samplerCreateInfo)
{ 
    assert(samplerCreateInfo != NULL);
    
    GLuint samplerID = 0;
    glCreateSamplers(1, &samplerID);

    glSamplerParameteri(samplerID, GL_TEXTURE_WRAP_S, textureWrapToNative(samplerCreateInfo->textureWrapS));
    glSamplerParameteri(samplerID, GL_TEXTURE_WRAP_T, textureWrapToNative(samplerCreateInfo->textureWrapT));
    glSamplerParameteri(samplerID, GL_TEXTURE_WRAP_R, textureWrapToNative(samplerCreateInfo->textureWrapR));

    glSamplerParameteri(samplerID, GL_TEXTURE_MIN_FILTER, textureMinFilterToNative(samplerCreateInfo->textureMinFilter));
    glSamplerParameteri(samplerID, GL_TEXTURE_MAG_FILTER, textureMagFilterToNative(samplerCreateInfo->textureMagFilter));

    glSamplerParameteri(samplerID, GL_TEXTURE_COMPARE_MODE, compareModeToNative(samplerCreateInfo->compareMode));
    glSamplerParameteri(samplerID, GL_TEXTURE_COMPARE_FUNC, compareFunctionToNative(samplerCreateInfo->compareFunction));

    glSamplerParameterf(samplerID, GL_TEXTURE_MIN_LOD, samplerCreateInfo->minLevelOfDetail);
    glSamplerParameterf(samplerID, GL_TEXTURE_MAX_LOD, samplerCreateInfo->maxLevelOfDetail);
    glSamplerParameterf(samplerID, GL_TEXTURE_LOD_BIAS, samplerCreateInfo->biasLevelOfDetail);
    glSamplerParameterf(samplerID, GL_TEXTURE_MAX_ANISOTROPY, samplerCreateInfo->maxAnisotropy);

    glSamplerParameterfv(samplerID, GL_TEXTURE_BORDER_COLOR, samplerCreateInfo->borderColour);

    logVerbose("SAMPLER", "created: %u", samplerID);
    return samplerID;
}

void samplerDestroy(SamplerID samplerID)
{
    glDeleteSamplers(1, &samplerID);
    logVerbose("SAMPLER", "destroyed: %u", samplerID);
}

bool samplerIsActive(SamplerID samplerID)
{
    return (glIsSampler(samplerID) == GL_TRUE);
}

void samplerBind(SamplerID samplerID, uint32_t unit)
{
    glBindSampler(unit, samplerID);
    logVerbose("SAMPLER", "sampler %u is bound to unit %u", samplerID, unit);
}

