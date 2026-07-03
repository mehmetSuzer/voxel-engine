
#include <assert.h>
#include "error.h"
#include "texture.h"
#include "stb_image.h"
#include "log/log.h"
#include "glad/glad.h"

TextureID textureCreate(const char* texturePath)
{
    int width = 0; 
    int height = 0;
    int channelCount = 0;
    stbi_set_flip_vertically_on_load(1);
    stbi_uc* pixels = stbi_load(texturePath, &width, &height, &channelCount, 0);
    if (pixels == NULL)
    {
        logError("TEXTURE", "failed to read %s", texturePath);
        return TEXTURE_NULL;
    }

    if (width == 0 || height == 0 || channelCount == 0)
    {
        logError("TEXTURE", "failed to detect dimensions: (W, H, C) = (%i, %i, %i)", width, height, channelCount);
        return TEXTURE_NULL;
    }

    if (channelCount < 1 || channelCount > 4)
    {
        stbi_image_free(pixels);
        logError("TEXTURE", "unsupported channel count (%i) for %s", channelCount, texturePath);
        return TEXTURE_NULL;
    }

    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    const int bytesPerRow = width * channelCount;
    const int alignment =
        (bytesPerRow % 8 == 0) ? 8 :
        (bytesPerRow % 4 == 0) ? 4 :
        (bytesPerRow % 2 == 0) ? 2 : 1;
    glPixelStorei(GL_UNPACK_ALIGNMENT, alignment);

    const GLenum externalFormat =
        (channelCount == 1) ? GL_RED :
        (channelCount == 2) ? GL_RG  :
        (channelCount == 3) ? GL_RGB : GL_RGBA;

    const GLenum internalFormat =
        (channelCount == 1) ? GL_R8   :
        (channelCount == 2) ? GL_RG8  :
        (channelCount == 3) ? GL_RGB8 : GL_RGBA8;

    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, externalFormat, GL_UNSIGNED_BYTE, pixels);

    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
    stbi_image_free(pixels);
    glCheckErrors();

    logVerbose("TEXTURE", "created from %s", texturePath);
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

void textureBindSampler(TextureID textureID, uint32_t unit)
{
    assert(unit < 32);
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, textureID);
    logVerbose("TEXTURE", "binded: %u", textureID);
    glCheckErrors();
}

void textureBindImage(TextureID textureID, uint32_t unit, int32_t mipLevel, AccessPolicy accessPolicy, ExternalFormat externalFormat)
{
    assert(unit < 32);
    glBindImageTexture(unit, textureID, mipLevel, GL_FALSE, 0, accessPolicyToNative(accessPolicy), externalFormatToNative(externalFormat));
    glCheckErrors();
}

