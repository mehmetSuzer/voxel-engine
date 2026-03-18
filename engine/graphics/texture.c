
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "texture.h"

Texture TextureCreate(
    const char* imagePath,
    TextureWrap wrapS,
    TextureWrap wrapT,
    TextureMinFilter minFilter,
    TextureMagFilter magFilter,
    vec4 borderColour)
{
    int width, height, channels;
    stbi_set_flip_vertically_on_load(1);
    unsigned char* pixels = stbi_load(imagePath, &width, &height, &channels, 0);

    if (pixels == NULL)
    {
        printf("Failed to read texture %s.\n", imagePath);
        exit(EXIT_FAILURE);
    }

    if (channels < 1 || channels > 4)
    {
        stbi_image_free(pixels);
        printf("Unsupported channel count %i for %s.\n", channels, imagePath);
        exit(EXIT_FAILURE);
    }

    Texture texture;
    glGenTextures(1, &texture.ID);
    glBindTexture(GL_TEXTURE_2D, texture.ID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (GLint)wrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (GLint)wrapT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (GLint)minFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (GLint)magFilter);
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, (float*)borderColour);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    const GLenum externalFormat =
        (channels == 1) ? GL_RED :
        (channels == 2) ? GL_RG  :
        (channels == 3) ? GL_RGB : GL_RGBA;

    const GLenum internalFormat =
        (channels == 1) ? GL_R8   :
        (channels == 2) ? GL_RG8  :
        (channels == 3) ? GL_RGB8 : GL_RGBA8;

    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, externalFormat, GL_UNSIGNED_BYTE, pixels);

    if (minFilter != TextureMinFilterNearest && minFilter != TextureMinFilterLinear)
    {
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    glBindTexture(GL_TEXTURE_2D, 0);
    stbi_image_free(pixels);

    return texture;
}

void TextureDelete(Texture texture)
{
    glDeleteTextures(1, &texture.ID);
}

void TextureBind(Texture texture, unsigned int unit)
{
    assert(unit < 32);
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, texture.ID);
}

CubeMap CubeMapCreate(
    const char* rightFacePath,
    const char* leftFacePath,
    const char* topFacePath,
    const char* bottomFacePath,
    const char* backFacePath,
    const char* frontFacePath,
    TextureMinFilter minFilter,
    TextureMagFilter magFilter)
{
    CubeMap cubeMap;
    glGenTextures(1, &cubeMap.ID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMap.ID);

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, (GLint)minFilter);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, (GLint)magFilter);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    const char* faces[6] = {
        rightFacePath, leftFacePath, 
        topFacePath, bottomFacePath, 
        backFacePath, frontFacePath
    };

    int width, height, channels;
    stbi_set_flip_vertically_on_load(0);

    for (unsigned int i = 0; i < 6; ++i)
    {
        unsigned char* pixels = stbi_load(faces[i], &width, &height, &channels, 0);
        if (pixels == NULL)
        {
            printf("Failed to load cube map face %s.\n", faces[i]);
            exit(EXIT_FAILURE);
        }
        if (channels < 1 || channels > 4)
        {
            stbi_image_free(pixels);
            printf("Unsupported channels count %i for %s.\n", channels, faces[i]);
            exit(EXIT_FAILURE);
        }

        const GLenum externalFormat =
            (channels == 1) ? GL_RED :
            (channels == 2) ? GL_RG :
            (channels == 3) ? GL_RGB : GL_RGBA;

        const GLint internalFormat =
            (channels == 1) ? GL_R8 :
            (channels == 2) ? GL_RG8 :
            (channels == 3) ? GL_RGB8 : GL_RGBA8;

        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, internalFormat, width, height, 0, externalFormat, GL_UNSIGNED_BYTE, pixels);
        stbi_image_free(pixels);
    }

    if (minFilter != TextureMinFilterNearest && minFilter != TextureMinFilterLinear)
    {
        glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
    }

    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    return cubeMap;
}

void CubeMapDelete(CubeMap cubeMap)
{
    glDeleteTextures(1, &cubeMap.ID);
}

void CubeMapBind(CubeMap cubeMap, unsigned int unit)
{
    assert(unit < 32);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMap.ID);
    glActiveTexture(GL_TEXTURE0 + unit);
}

