
#include <assert.h>
#include "error.h"
#include "texture.h"
#include "stb_image.h"
#include "log/log.h"
#include "glad/glad.h"
#include "utils/macros.h"

TextureID textureCreateEmpty(
    uint32_t width,
    uint32_t height,
    uint32_t channelCount,
    InternalFormat internalFormat,
    bool mipmapEnabled,
    TextureWrap wrapS,
    TextureWrap wrapT,
    TextureMinFilter minFilter,
    TextureMagFilter magFilter,
    vec4 borderColour)
{
    GLuint textureID;
    glCreateTextures(GL_TEXTURE_2D, 1, &textureID);
    
    const GLsizei mipmapLevelCount = (!mipmapEnabled || minFilter == TextureMinFilterNearest || minFilter == TextureMinFilterLinear) ? 1 
        : (GLsizei)floorf(log2f((float)GREATER(width, height))) + 1;

    glTextureStorage2D(textureID, mipmapLevelCount, internalFormatToNative(internalFormat), width, height);

    glTextureParameteri(textureID, GL_TEXTURE_WRAP_S, textureWrapToNative(wrapS));
    glTextureParameteri(textureID, GL_TEXTURE_WRAP_T, textureWrapToNative(wrapT));
    glTextureParameteri(textureID, GL_TEXTURE_MIN_FILTER, textureMinFilterToNative(minFilter));
    glTextureParameteri(textureID, GL_TEXTURE_MAG_FILTER, textureMagFilterToNative(magFilter));
    glTextureParameterfv(textureID, GL_TEXTURE_BORDER_COLOR, borderColour);

    logVerbose("TEXTURE", "created empty (%ux%ux%u)", width, height, channelCount);
    return textureID;
}

TextureID textureCreateFromImage(
    const char* imagePath,
    TextureWrap wrapS,
    TextureWrap wrapT,
    TextureMinFilter minFilter,
    TextureMagFilter magFilter,
    vec4 borderColour)
{
    int width = 0; 
    int height = 0;
    int channelCount = 0;
    stbi_set_flip_vertically_on_load(true);
    stbi_uc* pixels = stbi_load(imagePath, &width, &height, &channelCount, STBI_default);

    if (pixels == NULL)
    {
        logError("TEXTURE", "failed to load from image %s", imagePath);
        return TEXTURE_NULL;
    }
    if (width == 0 || height == 0 || channelCount == 0)
    {
        stbi_image_free(pixels);
        logError("TEXTURE", "failed to detect dimensions: (WxHxC) = (%ix%ix%i)", width, height, channelCount);
        return TEXTURE_NULL;
    }
    if (channelCount < 1 || channelCount > 4)
    {
        stbi_image_free(pixels);
        logError("TEXTURE", "unsupported channel count (%i) for image %s", channelCount, imagePath);
        return TEXTURE_NULL;
    }

    GLuint textureID;
    glCreateTextures(GL_TEXTURE_2D, 1, &textureID);

    const GLenum externalFormat =
        (channelCount == 1) ? GL_RED :
        (channelCount == 2) ? GL_RG  :
        (channelCount == 3) ? GL_RGB : GL_RGBA;

    const GLenum internalFormat =
        (channelCount == 1) ? GL_R8   :
        (channelCount == 2) ? GL_RG8  :
        (channelCount == 3) ? GL_RGB8 : GL_RGBA8;

    const GLsizei mipmapLevelCount = 
        (minFilter == TextureMinFilterNearest || minFilter == TextureMinFilterLinear) ? 1 : (GLsizei)floorf(log2f((float)GREATER(width, height))) + 1;

    glTextureStorage2D(textureID, mipmapLevelCount, internalFormat, width, height);
    glTextureSubImage2D(textureID, 0, 0, 0, width, height, externalFormat, GL_UNSIGNED_BYTE, pixels);

    glTextureParameteri(textureID, GL_TEXTURE_WRAP_S, textureWrapToNative(wrapS));
    glTextureParameteri(textureID, GL_TEXTURE_WRAP_T, textureWrapToNative(wrapT));
    glTextureParameteri(textureID, GL_TEXTURE_MIN_FILTER, textureMinFilterToNative(minFilter));
    glTextureParameteri(textureID, GL_TEXTURE_MAG_FILTER, textureMagFilterToNative(magFilter));
    glTextureParameterfv(textureID, GL_TEXTURE_BORDER_COLOR, borderColour);

    if (mipmapLevelCount > 1)
    {
        glGenerateTextureMipmap(textureID);
    }

    stbi_image_free(pixels);
    glCheckErrors();

    logVerbose("TEXTURE", "created from image %s", imagePath);
    return textureID;
}

TextureID textureCreateFromMemory(
    const uint8_t* data,
    uint32_t length,
    TextureWrap wrapS,
    TextureWrap wrapT,
    TextureMinFilter minFilter,
    TextureMagFilter magFilter,
    vec4 borderColour)
{
    int width = 0; 
    int height = 0;
    int channelCount = 0;
    stbi_set_flip_vertically_on_load(true);
    stbi_uc* pixels = stbi_load_from_memory(data, (int)length, &width, &height, &channelCount, STBI_default);

    if (pixels == NULL)
    {
        logError("TEXTURE", "failed to load from memory %p (%u bytes)", (void*)data, length);
        return TEXTURE_NULL;
    }
    if (width == 0 || height == 0 || channelCount == 0)
    {
        stbi_image_free(pixels);
        logError("TEXTURE", "failed to detect dimensions: (WxHxC) = (%ix%ix%i)", width, height, channelCount);
        return TEXTURE_NULL;
    }
    if (channelCount < 1 || channelCount > 4)
    {
        stbi_image_free(pixels);
        logError("TEXTURE", "unsupported channel count (%i) for memory %p (%u bytes)", channelCount, (void*)data, length);
        return TEXTURE_NULL;
    }

    GLuint textureID;
    glCreateTextures(GL_TEXTURE_2D, 1, &textureID);

    const GLenum externalFormat =
        (channelCount == 1) ? GL_RED :
        (channelCount == 2) ? GL_RG  :
        (channelCount == 3) ? GL_RGB : GL_RGBA;

    const GLenum internalFormat =
        (channelCount == 1) ? GL_R8   :
        (channelCount == 2) ? GL_RG8  :
        (channelCount == 3) ? GL_RGB8 : GL_RGBA8;

    const GLsizei mipmapLevelCount = 
        (minFilter == TextureMinFilterNearest || minFilter == TextureMinFilterLinear) ? 1 : (GLsizei)floorf(log2f((float)GREATER(width, height))) + 1;

    glTextureStorage2D(textureID, mipmapLevelCount, internalFormat, width, height);
    glTextureSubImage2D(textureID, 0, 0, 0, width, height, externalFormat, GL_UNSIGNED_BYTE, pixels);

    glTextureParameteri(textureID, GL_TEXTURE_WRAP_S, textureWrapToNative(wrapS));
    glTextureParameteri(textureID, GL_TEXTURE_WRAP_T, textureWrapToNative(wrapT));
    glTextureParameteri(textureID, GL_TEXTURE_MIN_FILTER, textureMinFilterToNative(minFilter));
    glTextureParameteri(textureID, GL_TEXTURE_MAG_FILTER, textureMagFilterToNative(magFilter));
    glTextureParameterfv(textureID, GL_TEXTURE_BORDER_COLOR, borderColour);

    if (mipmapLevelCount > 1)
    {
        glGenerateTextureMipmap(textureID);
    }

    stbi_image_free(pixels);
    glCheckErrors();

    logVerbose("TEXTURE", "created from memory %p (%u)", (void*)data, length);
    return textureID;
}

TextureID textureCreateFromRawData(
    const uint8_t* pixels,
    uint32_t width,
    uint32_t height,
    uint32_t channelCount,
    ExternalFormat externalFormat,
    TextureWrap wrapS,
    TextureWrap wrapT,
    TextureMinFilter minFilter,
    TextureMagFilter magFilter,
    vec4 borderColour)
{
    GLuint textureID;
    glCreateTextures(GL_TEXTURE_2D, 1, &textureID);

    const GLenum internalFormat =
        (channelCount == 1) ? GL_R8   :
        (channelCount == 2) ? GL_RG8  :
        (channelCount == 3) ? GL_RGB8 : GL_RGBA8;

    const GLsizei mipmapLevelCount = 
        (minFilter == TextureMinFilterNearest || minFilter == TextureMinFilterLinear) ? 1 : (GLsizei)floorf(log2f((float)GREATER(width, height))) + 1;

    glTextureStorage2D(textureID, mipmapLevelCount, internalFormat, width, height);
    glTextureSubImage2D(textureID, 0, 0, 0, width, height, externalFormat, GL_UNSIGNED_BYTE, pixels);

    glTextureParameteri(textureID, GL_TEXTURE_WRAP_S, textureWrapToNative(wrapS));
    glTextureParameteri(textureID, GL_TEXTURE_WRAP_T, textureWrapToNative(wrapT));
    glTextureParameteri(textureID, GL_TEXTURE_MIN_FILTER, textureMinFilterToNative(minFilter));
    glTextureParameteri(textureID, GL_TEXTURE_MAG_FILTER, textureMagFilterToNative(magFilter));
    glTextureParameterfv(textureID, GL_TEXTURE_BORDER_COLOR, borderColour);

    if (mipmapLevelCount > 1)
    {
        glGenerateTextureMipmap(textureID);
    }
    glCheckErrors();

    logVerbose("TEXTURE", "created from raw data %p (%ux%ux%u)", (void*)pixels, width, height, channelCount);
    return textureID;
}

void textureDestroy(TextureID textureID)
{
    glDeleteTextures(1, &textureID);
    glCheckErrors();
}

bool textureIsActive(TextureID textureID)
{
    return (glIsTexture(textureID) == GL_TRUE);
}

void textureGenerateMipmap(TextureID textureID)
{
    glGenerateTextureMipmap(textureID);
    glCheckErrors();
}

void textureGetImage(TextureID textureID, int32_t mipmapLevel, ExternalFormat externalFormat, DataType dataType, int32_t size, void* bufferOut)
{
    glGetTextureImage(textureID, mipmapLevel, externalFormatToNative(externalFormat), dataTypeToNative(dataType), size, bufferOut);
    glCheckErrors();
}

void textureGetImageRange(
    TextureID textureID, 
    int32_t mipmapLevel, 
    ivec3 offsets,
    ivec3 dimensions,
    ExternalFormat externalFormat, 
    DataType dataType, 
    int32_t size, 
    void* bufferOut)
{
    glGetTextureSubImage(textureID, mipmapLevel, offsets[0], offsets[1], offsets[2], 
        dimensions[0], dimensions[1], dimensions[2], externalFormatToNative(externalFormat), dataTypeToNative(dataType), size, bufferOut);
    glCheckErrors();
}

void textureBindSampler(TextureID textureID, uint32_t unit)
{
    assert(unit < 32);
    glBindTextureUnit(unit, textureID);
    logVerbose("TEXTURE", "sampler binded: %u", textureID);
    glCheckErrors();
}

void textureBindImage(TextureID textureID, uint32_t unit, int32_t mipLevel, AccessPolicy accessPolicy, ExternalFormat externalFormat)
{
    assert(unit < 32);
    glBindImageTexture(unit, textureID, mipLevel, GL_FALSE, 0, accessPolicyToNative(accessPolicy), externalFormatToNative(externalFormat));
    logVerbose("TEXTURE", "image binded: %u", textureID);
    glCheckErrors();
}

void textureGetDimensions(TextureID textureID, int32_t mipmapLevel, int32_t* widthOut, int32_t* heightOut)
{
    GLint width  = 0;
    GLint height = 0;
    glGetTextureLevelParameteriv(textureID, mipmapLevel, GL_TEXTURE_WIDTH, &width);
    glGetTextureLevelParameteriv(textureID, mipmapLevel, GL_TEXTURE_HEIGHT, &height);
    if (widthOut  != NULL) { *widthOut  = width;  }
    if (heightOut != NULL) { *heightOut = height; }
}

