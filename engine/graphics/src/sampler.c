
#include "error.h"
#include "sampler.h"
#include "glad/glad.h"

void samplerGetDefaultCreateInfo(SamplerCreateInfo* samplerCreateInfoOut)
{
    samplerCreateInfoOut->minFilter = MinFilterNearestMipmapLinear;
    samplerCreateInfoOut->magFilter = MagFilterLinear;

    samplerCreateInfoOut->wrapS = WrapRepeat;
    samplerCreateInfoOut->wrapT = WrapRepeat;
    samplerCreateInfoOut->wrapR = WrapRepeat;

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
    GLuint sampler;
    glGenSamplers(1, &sampler);

    glSamplerParameteri(sampler, GL_TEXTURE_MIN_FILTER, minFilterToCode(samplerCreateInfo->minFilter));
    glSamplerParameteri(sampler, GL_TEXTURE_MAG_FILTER, magFilterToCode(samplerCreateInfo->magFilter));

    glSamplerParameteri(sampler, GL_TEXTURE_WRAP_S, wrapToCode(samplerCreateInfo->wrapS));
    glSamplerParameteri(sampler, GL_TEXTURE_WRAP_T, wrapToCode(samplerCreateInfo->wrapT));
    glSamplerParameteri(sampler, GL_TEXTURE_WRAP_R, wrapToCode(samplerCreateInfo->wrapR));

    glSamplerParameterf(sampler, GL_TEXTURE_MIN_LOD, samplerCreateInfo->minLOD);
    glSamplerParameterf(sampler, GL_TEXTURE_MAX_LOD, samplerCreateInfo->maxLOD);
    glSamplerParameterf(sampler, GL_TEXTURE_LOD_BIAS, samplerCreateInfo->biasLOD);

    glSamplerParameteri(sampler, GL_TEXTURE_COMPARE_MODE, compareModeToCode(samplerCreateInfo->compareMode));
    glSamplerParameteri(sampler, GL_TEXTURE_COMPARE_FUNC, compareFuncToCode(samplerCreateInfo->compareFunc));

    glSamplerParameterfv(sampler, GL_TEXTURE_BORDER_COLOR, samplerCreateInfo->borderColour);
    glCheckErrors();

    return sampler;
}

void samplerDestroy(SamplerID sampler)
{
    glDeleteSamplers(1, &sampler);
    glCheckErrors();
}

int samplerIsActive(SamplerID sampler)
{
    return (glIsSampler(sampler) == GL_TRUE);
}

void samplerBind(SamplerID sampler, unsigned int unit)
{
    glBindSampler(unit, sampler);
    glCheckErrors();
}

