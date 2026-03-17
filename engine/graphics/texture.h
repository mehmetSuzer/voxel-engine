
#pragma once

#include <cglm/cglm.h>
#include "glad/glad.h"

typedef enum
{
    TextureWrapRepeat            = GL_REPEAT,
    TextureWrapMirroredRepeat    = GL_MIRRORED_REPEAT,
    TextureWrapClampToEdge       = GL_CLAMP_TO_EDGE,
    TextureWrapClampToBorder     = GL_CLAMP_TO_BORDER,
    TextureWrapMirrorClampToEdge = GL_MIRROR_CLAMP_TO_EDGE,
} TextureWrap;

typedef enum
{
    TextureMinFilterNearest              = GL_NEAREST,
    TextureMinFilterLinear               = GL_LINEAR,
    TextureMinFilterNearestMipmapNearest = GL_NEAREST_MIPMAP_NEAREST,
    TextureMinFilterLinearMipmapNearest  = GL_LINEAR_MIPMAP_NEAREST,
    TextureMinFilterNearestMipmapLinear  = GL_NEAREST_MIPMAP_LINEAR,
    TextureMinFilterLinearMipmapLinear   = GL_LINEAR_MIPMAP_LINEAR,
} TextureMinFilter;

typedef enum
{
    TextureMagFilterNearest = GL_NEAREST,
    TextureMagFilterLinear  = GL_LINEAR,
} TextureMagFilter;

typedef struct
{
    GLuint ID;
} Texture;

Texture TextureCreate(
    const char* imagePath,
    TextureWrap wrapS,
    TextureWrap wrapT,
    TextureMinFilter minFilter,
    TextureMagFilter magFilter,
    vec4 borderColour);

void TextureDelete(Texture texture);

void TextureBind(Texture texture, unsigned int unit);

typedef struct
{
    GLuint ID;
} CubeMap;

CubeMap CubeMapCreate(
    const char* rightFacePath,
    const char* leftFacePath,
    const char* topFacePath,
    const char* bottomFacePath,
    const char* backFacePath,
    const char* frontFacePath,
    TextureMinFilter minFilter,
    TextureMagFilter magFilter);

void CubeMapDelete(CubeMap cubeMap);

void CubeMapBind(CubeMap cubeMap, unsigned int unit);

