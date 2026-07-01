
#include "error.h"
#include "sampler.h"
#include "log/log.h"
#include "glad/glad.h"

void samplerGetDefaultCreateInfo(SamplerCreateInfo* samplerCreateInfoOut)
{
    samplerCreateInfoOut->textureMinFilter = TextureMinFilterNearestMipmapLinear;
    samplerCreateInfoOut->textureMagFilter = TextureMagFilterLinear;

    samplerCreateInfoOut->textureWrapS = TextureWrapRepeat;
    samplerCreateInfoOut->textureWrapT = TextureWrapRepeat;
    samplerCreateInfoOut->textureWrapR = TextureWrapRepeat;

    samplerCreateInfoOut->minLOD  = -1000.0f;
    samplerCreateInfoOut->maxLOD  =  1000.0f;
    samplerCreateInfoOut->biasLOD =  0.0f;

    samplerCreateInfoOut->compareMode = CompareModeNone;
    samplerCreateInfoOut->compareFunc = CompareFuncLessEqual;

    samplerCreateInfoOut->borderColour[0] = 0.0f;
    samplerCreateInfoOut->borderColour[1] = 0.0f;
    samplerCreateInfoOut->borderColour[2] = 0.0f;
    samplerCreateInfoOut->borderColour[3] = 0.0f;
}

SamplerID samplerCreate(const SamplerCreateInfo* samplerCreateInfo)
{ 
    GLuint samplerID;
    glGenSamplers(1, &samplerID);

    glSamplerParameteri(samplerID, GL_TEXTURE_MIN_FILTER, textureMinFilterToNative(samplerCreateInfo->textureMinFilter));
    glSamplerParameteri(samplerID, GL_TEXTURE_MAG_FILTER, textureMagFilterToNative(samplerCreateInfo->textureMagFilter));

    glSamplerParameteri(samplerID, GL_TEXTURE_WRAP_S, textureWrapToNative(samplerCreateInfo->textureWrapS));
    glSamplerParameteri(samplerID, GL_TEXTURE_WRAP_T, textureWrapToNative(samplerCreateInfo->textureWrapT));
    glSamplerParameteri(samplerID, GL_TEXTURE_WRAP_R, textureWrapToNative(samplerCreateInfo->textureWrapR));

    glSamplerParameterf(samplerID, GL_TEXTURE_MIN_LOD, samplerCreateInfo->minLOD);
    glSamplerParameterf(samplerID, GL_TEXTURE_MAX_LOD, samplerCreateInfo->maxLOD);
    glSamplerParameterf(samplerID, GL_TEXTURE_LOD_BIAS, samplerCreateInfo->biasLOD);

    glSamplerParameteri(samplerID, GL_TEXTURE_COMPARE_MODE, compareModeToNative(samplerCreateInfo->compareMode));
    glSamplerParameteri(samplerID, GL_TEXTURE_COMPARE_FUNC, compareFuncToNative(samplerCreateInfo->compareFunc));

    glSamplerParameterfv(samplerID, GL_TEXTURE_BORDER_COLOR, samplerCreateInfo->borderColour);
    glCheckErrors();

    return samplerID;
}

void samplerDestroy(SamplerID samplerID)
{
    glDeleteSamplers(1, &samplerID);
    glCheckErrors();
}

int samplerIsActive(SamplerID samplerID)
{
    return (glIsSampler(samplerID) == GL_TRUE);
}

void samplerBind(SamplerID samplerID, unsigned int unit)
{
    glBindSampler(unit, samplerID);
    logVerbose("SAMPLER", "binded: %u", samplerID);
    glCheckErrors();
}

