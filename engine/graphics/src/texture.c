
#include <math.h>
#include <string.h>
#include <assert.h>
#include "texture.h"
#include "log/log.h"
#include "glad/glad.h"

TextureID textureCreate(const TextureCreateInfo* textureCreateInfo)
{
    assert(textureCreateInfo != NULL);

    const GLsizei width  = textureCreateInfo->width;
    const GLsizei height = textureCreateInfo->height;
    const GLsizei depth  = textureCreateInfo->depth;

    const GLenum target = 
        (depth >  1 && height >  1 && width > 1) ? GL_TEXTURE_3D :
        (depth == 1 && height >  1 && width > 1) ? GL_TEXTURE_2D :
        (depth == 1 && height == 1 && width > 1) ? GL_TEXTURE_1D : GL_NONE;

    if (target == GL_NONE)
    {
        logError("TEXTURE", "incompatible dimensions: (%i, %i, %i)", width, height, depth);
        return TEXTURE_NULL;
    }

    GLuint textureID = 0;
    glCreateTextures(target, 1, &textureID);

    const bool generateMipmap = textureCreateInfo->minFilter != TextureMinFilterNearest && 
                                textureCreateInfo->minFilter != TextureMinFilterLinear;

    const GLsizei greatestDimension = (width > height) ? ((width > depth) ? width : depth) : ((height > depth) ? height : depth);
    const GLsizei mipmapLevelCount = (generateMipmap) ? (GLsizei)floorf(log2f((float)greatestDimension)) + 1 : 1;
    const GLenum internalFormat = internalFormatToNative(textureCreateInfo->internalFormat);

    if      (target == GL_TEXTURE_1D) { glTextureStorage1D(textureID, mipmapLevelCount, internalFormat, width);                }
    else if (target == GL_TEXTURE_2D) { glTextureStorage2D(textureID, mipmapLevelCount, internalFormat, width, height);        }
    else                              { glTextureStorage3D(textureID, mipmapLevelCount, internalFormat, width, height, depth); }

    glTextureParameteri(textureID, GL_TEXTURE_WRAP_S, textureWrapToNative(textureCreateInfo->wrapS));
    glTextureParameteri(textureID, GL_TEXTURE_WRAP_T, textureWrapToNative(textureCreateInfo->wrapT));
    glTextureParameteri(textureID, GL_TEXTURE_WRAP_R, textureWrapToNative(textureCreateInfo->wrapR));
    glTextureParameteri(textureID, GL_TEXTURE_MIN_FILTER, textureMinFilterToNative(textureCreateInfo->minFilter));
    glTextureParameteri(textureID, GL_TEXTURE_MAG_FILTER, textureMagFilterToNative(textureCreateInfo->magFilter));
    glTextureParameterf(textureID, GL_TEXTURE_MAX_ANISOTROPY, textureCreateInfo->maxAnisotropy);
    glTextureParameterfv(textureID, GL_TEXTURE_BORDER_COLOR, textureCreateInfo->borderColour);

    logVerbose("TEXTURE", "texture %u is created with dimensions (%i, %i, %i)", textureID, width, height, depth);
    return textureID;
}

void textureFill(TextureID textureID, const TextureFillInfo* textureFillInfo)
{
    assert(textureFillInfo != NULL);

    const GLsizei width  = textureFillInfo->width;
    const GLsizei height = textureFillInfo->height;
    const GLsizei depth  = textureFillInfo->depth;
   
    const GLint xOffset = textureFillInfo->xOffset;
    const GLint yOffset = textureFillInfo->yOffset;
    const GLint zOffset = textureFillInfo->zOffset;

    const GLenum target = 
        (depth >  1 && height >  1 && width > 1) ? GL_TEXTURE_3D :
        (depth == 1 && height >  1 && width > 1) ? GL_TEXTURE_2D :
        (depth == 1 && height == 1 && width > 1) ? GL_TEXTURE_1D : GL_NONE;

    if (target == GL_NONE)
    {
        logError("TEXTURE", "incompatible dimensions: (%i, %i, %i)", width, height, depth);
        return;
    }

    const void* data = textureFillInfo->data;
    const GLint mipmapLevel = textureFillInfo->mipmapLevel;
    const GLenum dataType = dataTypeToNative(textureFillInfo->dataType);
    const GLenum externalFormat = externalFormatToNative(textureFillInfo->externalFormat);

    if (target == GL_TEXTURE_1D) 
    { 
        glTextureSubImage1D(textureID, mipmapLevel, xOffset, width, externalFormat, dataType, data);
    }
    else if (target == GL_TEXTURE_2D) 
    { 
        glTextureSubImage2D(textureID, mipmapLevel, xOffset, yOffset, width, height, externalFormat, dataType, data);
    }
    else 
    { 
        glTextureSubImage3D(textureID, mipmapLevel, xOffset, yOffset, zOffset, width, height, depth, externalFormat, dataType, data); 
    }

    logVerbose("TEXTURE", "texture %u is filled with offsets (%i, %i, %i) and dimensions (%i, %i, %i)", 
        textureID, xOffset, yOffset, zOffset, width, height, depth);
}

TextureID textureCreateCubeMap(const TextureCreateCubeMapInfo* textureCreateCubeMapInfo)
{
    assert(textureCreateCubeMapInfo != NULL);

    GLuint textureID = 0;
    glCreateTextures(GL_TEXTURE_CUBE_MAP, 1, &textureID);

    const GLsizei size = textureCreateCubeMapInfo->size;
    const GLsizei mipmapLevelCount = (GLsizei)floorf(log2f((float)size)) + 1;
    const GLenum internalFormatNative = internalFormatToNative(textureCreateCubeMapInfo->internalFormat);

    glTextureStorage2D(textureID, mipmapLevelCount, internalFormatNative, size, size);

    glTextureParameteri(textureID, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTextureParameteri(textureID, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTextureParameteri(textureID, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTextureParameteri(textureID, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTextureParameteri(textureID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTextureParameterf(textureID, GL_TEXTURE_MAX_ANISOTROPY, textureCreateCubeMapInfo->maxAnisotropy);

    logVerbose("TEXTURE", "cube map %u is created with size %i", textureID, size);
    return textureID;
}

void textureFillCubeMap(TextureID textureID, const TextureFillCubeMapInfo* textureFillCubeMapInfo)
{
    assert(textureFillCubeMapInfo != NULL);

    const GLsizei size = textureFillCubeMapInfo->size;
    const GLenum dataType = dataTypeToNative(textureFillCubeMapInfo->dataType);
    const GLenum externalFormat = externalFormatToNative(textureFillCubeMapInfo->externalFormat);

    const void* faceData[6] = {
        textureFillCubeMapInfo->rightData,  // +x
        textureFillCubeMapInfo->leftData,   // -X
        textureFillCubeMapInfo->topData,    // +Y
        textureFillCubeMapInfo->bottomData, // -Y
        textureFillCubeMapInfo->backData,   // +Z
        textureFillCubeMapInfo->frontData,  // -Z
    };
    const GLint faceCount = (GLint)(sizeof(faceData) / sizeof(faceData[0]));

    for (GLint face = 0; face < faceCount; ++face)
    {
        if (faceData[face] != NULL)
        {
            glTextureSubImage3D(textureID, 0, 0, 0, face, size, size, 1, externalFormat, dataType, faceData[face]);
        }
    }

    logVerbose("TEXTURE", "cube map %u is filled", textureID);
}

void textureDestroy(TextureID textureID)
{
    glDeleteTextures(1, &textureID);
    logVerbose("TEXTURE", "destroyed: %u", textureID);
}

#ifndef NDEBUG
void textureSetLabel(TextureID textureID, const char* label)
{
    glObjectLabel(GL_TEXTURE, textureID, (label == NULL) ? 0 : -1, label);
}

void textureGetLabel(TextureID textureID, int32_t maxLabelLength, int32_t* labelLengthOut, char* labelOut)
{
    glGetObjectLabel(GL_TEXTURE, textureID, maxLabelLength, labelLengthOut, labelOut);
}
#endif

bool textureIsActive(TextureID textureID)
{
    return (glIsTexture(textureID) == GL_TRUE);
}

void textureGenerateMipmap(TextureID textureID)
{
    glGenerateTextureMipmap(textureID);
}

void textureGetImage(TextureID textureID, const TextureGetImageInfo* textureGetImageInfo, size_t bufferSize, void* bufferOut)
{
    assert(textureGetImageInfo != NULL && bufferOut != NULL);

    glGetTextureSubImage(
        textureID,
        textureGetImageInfo->mipmapLevel,
        textureGetImageInfo->xOffset,
        textureGetImageInfo->yOffset,
        textureGetImageInfo->zOffset,
        textureGetImageInfo->width,
        textureGetImageInfo->height,
        textureGetImageInfo->depth,
        dataTypeToNative(textureGetImageInfo->dataType),
        externalFormatToNative(textureGetImageInfo->externalFormat),
        bufferSize,
        bufferOut);
}

void textureBindSampler(TextureID textureID, uint32_t unit)
{
    assert(unit < 32);
    glBindTextureUnit(unit, textureID);
    logVerbose("TEXTURE", "texture %u is bound to %u", textureID, unit);
}

void textureBindImage(
    TextureID textureID, 
    uint32_t unit, 
    uint32_t mipmapLevel, 
    bool layered, 
    uint32_t layer, 
    AccessPolicy accessPolicy, 
    ExternalFormat externalFormat)
{
    assert(unit < 32);
    const GLenum accessPolicyNative = accessPolicyToNative(accessPolicy);
    const GLenum externalFormatNative = externalFormatToNative(externalFormat);
    glBindImageTexture(unit, textureID, mipmapLevel, layered, layer, accessPolicyNative, externalFormatNative);
    logVerbose("TEXTURE", "image binded: %u", textureID);
}

void textureGetDimensions(TextureID textureID, uint32_t mipmapLevel, uint32_t* widthOut, uint32_t* heightOut, uint32_t* depthOut)
{
    GLint width  = 0;
    GLint height = 0;
    GLint depth  = 0;
    glGetTextureLevelParameteriv(textureID, mipmapLevel, GL_TEXTURE_WIDTH,  &width);
    glGetTextureLevelParameteriv(textureID, mipmapLevel, GL_TEXTURE_HEIGHT, &height);
    glGetTextureLevelParameteriv(textureID, mipmapLevel, GL_TEXTURE_DEPTH,  &depth);
    if (widthOut  != NULL) { *widthOut  = (uint32_t)width;  }
    if (heightOut != NULL) { *heightOut = (uint32_t)height; }
    if (depthOut  != NULL) { *depthOut  = (uint32_t)depth;  }
}

