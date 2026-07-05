
#include "error.h"
#include "sampler.h"
#include "log/log.h"
#include "glad/glad.h"

void samplerGetDefaultCreateInfo(SamplerCreateInfo* samplerCreateInfoOut)
{
    samplerCreateInfoOut->textureWrapS = TextureWrapRepeat;
    samplerCreateInfoOut->textureWrapT = TextureWrapRepeat;
    samplerCreateInfoOut->textureWrapR = TextureWrapRepeat;

    samplerCreateInfoOut->textureMinFilter = TextureMinFilterNearestMipmapLinear;
    samplerCreateInfoOut->textureMagFilter = TextureMagFilterLinear;

    samplerCreateInfoOut->compareMode = CompareModeNone;
    samplerCreateInfoOut->compareFunc = CompareFuncLessEqual;

    samplerCreateInfoOut->minLOD = -1000.0f;
    samplerCreateInfoOut->maxLOD =  1000.0f;
    samplerCreateInfoOut->biasLOD = 0.0f;
    samplerCreateInfoOut->maxAnisotropy = 1.0f;

    samplerCreateInfoOut->borderColour[0] = 0.0f;
    samplerCreateInfoOut->borderColour[1] = 0.0f;
    samplerCreateInfoOut->borderColour[2] = 0.0f;
    samplerCreateInfoOut->borderColour[3] = 1.0f;
}

SamplerID samplerCreate(const SamplerCreateInfo* samplerCreateInfo)
{ 
    GLuint samplerID;
    glCreateSamplers(1, &samplerID);

    glSamplerParameteri(samplerID, GL_TEXTURE_WRAP_S, textureWrapToNative(samplerCreateInfo->textureWrapS));
    glSamplerParameteri(samplerID, GL_TEXTURE_WRAP_T, textureWrapToNative(samplerCreateInfo->textureWrapT));
    glSamplerParameteri(samplerID, GL_TEXTURE_WRAP_R, textureWrapToNative(samplerCreateInfo->textureWrapR));

    glSamplerParameteri(samplerID, GL_TEXTURE_MIN_FILTER, textureMinFilterToNative(samplerCreateInfo->textureMinFilter));
    glSamplerParameteri(samplerID, GL_TEXTURE_MAG_FILTER, textureMagFilterToNative(samplerCreateInfo->textureMagFilter));

    glSamplerParameteri(samplerID, GL_TEXTURE_COMPARE_MODE, compareModeToNative(samplerCreateInfo->compareMode));
    glSamplerParameteri(samplerID, GL_TEXTURE_COMPARE_FUNC, compareFuncToNative(samplerCreateInfo->compareFunc));

    glSamplerParameterf(samplerID, GL_TEXTURE_MIN_LOD, samplerCreateInfo->minLOD);
    glSamplerParameterf(samplerID, GL_TEXTURE_MAX_LOD, samplerCreateInfo->maxLOD);
    glSamplerParameterf(samplerID, GL_TEXTURE_LOD_BIAS, samplerCreateInfo->biasLOD);
    glSamplerParameterf(samplerID, GL_TEXTURE_MAX_ANISOTROPY, samplerCreateInfo->maxAnisotropy);

    glSamplerParameterfv(samplerID, GL_TEXTURE_BORDER_COLOR, samplerCreateInfo->borderColour);
    glCheckErrors();

    logVerbose("SAMPLER", "created: %u", samplerID);
    return samplerID;
}

void samplerDestroy(SamplerID samplerID)
{
    glDeleteSamplers(1, &samplerID);
    glCheckErrors();
    logVerbose("SAMPLER", "destroyed: %u", samplerID);
}

bool samplerIsActive(SamplerID samplerID)
{
    return (glIsSampler(samplerID) == GL_TRUE);
}

void samplerBind(SamplerID samplerID, uint32_t unit)
{
    glBindSampler(unit, samplerID);
    glCheckErrors();
    logVerbose("SAMPLER", "binded: %u", samplerID);
}

void samplerBindMultiple(const SamplerID* samplers, uint32_t firstUnit, uint32_t count)
{
    glBindSamplers(firstUnit, count, samplers);
    glCheckErrors();
    for (uint32_t i = 0; i < count; ++i)
    {
        logVerbose("SAMPLER", "binded: %u", samplers[i]);
    }
}

