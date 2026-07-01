
#include <assert.h>
#include "error.h"
#include "texture.h"
#include "stb_image.h"
#include "log/log.h"
#include "glad/glad.h"

TextureID textureCreate(const char* texturePath)
{
    int width, height, channels;
    stbi_set_flip_vertically_on_load(1);
    unsigned char* pixels = stbi_load(texturePath, &width, &height, &channels, 0);
    if (pixels == NULL)
    {
        logError("TEXTURE", "failed to read %s", texturePath);
        return TEXTURE_NULL;
    }

    if (channels < 1 || channels > 4)
    {
        stbi_image_free(pixels);
        logError("TEXTURE", "unsupported channels (%i) for %s", channels, texturePath);
        return TEXTURE_NULL;
    }

    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    const int bytesPerRow = width * channels;
    const int alignment =
        (bytesPerRow % 8 == 0) ? 8 :
        (bytesPerRow % 4 == 0) ? 4 :
        (bytesPerRow % 2 == 0) ? 2 : 1;
    glPixelStorei(GL_UNPACK_ALIGNMENT, alignment);

    const GLenum externalFormat =
        (channels == 1) ? GL_RED :
        (channels == 2) ? GL_RG  :
        (channels == 3) ? GL_RGB : GL_RGBA;

    const GLenum internalFormat =
        (channels == 1) ? GL_R8   :
        (channels == 2) ? GL_RG8  :
        (channels == 3) ? GL_RGB8 : GL_RGBA8;

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

int textureIsActive(TextureID textureID)
{
    return (glIsTexture(textureID) == GL_TRUE);
}

void textureBind(TextureID textureID, unsigned int unit)
{
    assert(unit < 32u);
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, textureID);
    logVerbose("TEXTURE", "binded: %u", textureID);
    glCheckErrors();
}

