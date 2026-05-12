
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
    GLuint samplerID;
    glGenSamplers(1, &samplerID);

    glSamplerParameteri(samplerID, GL_TEXTURE_MIN_FILTER, minFilterToCode(samplerCreateInfo->minFilter));
    glSamplerParameteri(samplerID, GL_TEXTURE_MAG_FILTER, magFilterToCode(samplerCreateInfo->magFilter));

    glSamplerParameteri(samplerID, GL_TEXTURE_WRAP_S, wrapToCode(samplerCreateInfo->wrapS));
    glSamplerParameteri(samplerID, GL_TEXTURE_WRAP_T, wrapToCode(samplerCreateInfo->wrapT));
    glSamplerParameteri(samplerID, GL_TEXTURE_WRAP_R, wrapToCode(samplerCreateInfo->wrapR));

    glSamplerParameterf(samplerID, GL_TEXTURE_MIN_LOD, samplerCreateInfo->minLOD);
    glSamplerParameterf(samplerID, GL_TEXTURE_MAX_LOD, samplerCreateInfo->maxLOD);
    glSamplerParameterf(samplerID, GL_TEXTURE_LOD_BIAS, samplerCreateInfo->biasLOD);

    glSamplerParameteri(samplerID, GL_TEXTURE_COMPARE_MODE, compareModeToCode(samplerCreateInfo->compareMode));
    glSamplerParameteri(samplerID, GL_TEXTURE_COMPARE_FUNC, compareFuncToCode(samplerCreateInfo->compareFunc));

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
    glCheckErrors();
}

