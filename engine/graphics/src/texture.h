
#pragma once

#include <cglm/cglm.h>
#include "glad/glad.h"

typedef enum TextureWrap
{
    TextureWrapRepeat            = GL_REPEAT,
    TextureWrapMirroredRepeat    = GL_MIRRORED_REPEAT,
    TextureWrapClampToEdge       = GL_CLAMP_TO_EDGE,
    TextureWrapClampToBorder     = GL_CLAMP_TO_BORDER,
    TextureWrapMirrorClampToEdge = GL_MIRROR_CLAMP_TO_EDGE,
} TextureWrap;

typedef enum TextureMinFilter
{
    TextureMinFilterNearest              = GL_NEAREST,
    TextureMinFilterLinear               = GL_LINEAR,
    TextureMinFilterNearestMipmapNearest = GL_NEAREST_MIPMAP_NEAREST,
    TextureMinFilterLinearMipmapNearest  = GL_LINEAR_MIPMAP_NEAREST,
    TextureMinFilterNearestMipmapLinear  = GL_NEAREST_MIPMAP_LINEAR,
    TextureMinFilterLinearMipmapLinear   = GL_LINEAR_MIPMAP_LINEAR,
} TextureMinFilter;

typedef enum TextureMagFilter
{
    TextureMagFilterNearest = GL_NEAREST,
    TextureMagFilterLinear  = GL_LINEAR,
} TextureMagFilter;

typedef struct Texture
{
    GLuint ID;
} Texture;

Texture textureCreate(
    const char* imagePath,
    TextureWrap wrapS,
    TextureWrap wrapT,
    TextureMinFilter minFilter,
    TextureMagFilter magFilter,
    vec4 borderColour);

void textureDelete(Texture texture);

void textureBind(Texture texture, unsigned int unit);

typedef struct CubeMap
{
    GLuint ID;
} CubeMap;

CubeMap cubeMapCreate(
    const char* rightFacePath,
    const char* leftFacePath,
    const char* topFacePath,
    const char* bottomFacePath,
    const char* backFacePath,
    const char* frontFacePath,
    TextureMinFilter minFilter,
    TextureMagFilter magFilter);

void cubeMapDelete(CubeMap cubeMap);

void cubeMapBind(CubeMap cubeMap, unsigned int unit);

