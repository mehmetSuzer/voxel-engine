
#pragma once

#include <stdbool.h>
#include "graphics/enums.h"

typedef uint32_t TextureID;

#define TEXTURE_NULL ((TextureID)0)

typedef struct TextureCreateInfo
{
    uint32_t width;
    uint32_t height;
    uint32_t depth;
    InternalFormat internalFormat;
    TextureWrap wrapS;
    TextureWrap wrapT;
    TextureWrap wrapR;
    TextureMinFilter minFilter;
    TextureMagFilter magFilter;
    float maxAnisotropy;
    float borderColour[4];
} TextureCreateInfo;

typedef struct TextureFillInfo
{
    const uint8_t* data;
    uint32_t level;
    uint32_t width;
    uint32_t height;
    uint32_t depth;
    uint32_t xOffset;
    uint32_t yOffset;
    uint32_t zOffset;
    DataType dataType;
    ExternalFormat externalFormat;
} TextureFillInfo;

typedef struct TextureCreateCubeMapInfo
{
    uint32_t size;
    InternalFormat internalFormat;
    float maxAnisotropy;
} TextureCreateCubeMapInfo;

typedef struct TextureFillCubeMapInfo
{
    const uint8_t* rightData;
    const uint8_t* leftData;
    const uint8_t* topData;
    const uint8_t* bottomData;
    const uint8_t* backData;
    const uint8_t* frontData;
    uint32_t size;
    DataType dataType;
    ExternalFormat externalFormat;
} TextureFillCubeMapInfo;

typedef struct TextureGetImageInfo
{
    uint32_t level;
    uint32_t width;
    uint32_t height;
    uint32_t depth;
    uint32_t xOffset;
    uint32_t yOffset;
    uint32_t zOffset;
    DataType dataType;
    ExternalFormat externalFormat;
} TextureGetImageInfo;

TextureID textureCreate(const TextureCreateInfo* textureCreateInfo);
void textureFill(TextureID textureID, const TextureFillInfo* textureFillInfo);

TextureID textureCreateCubeMap(const TextureCreateCubeMapInfo* textureCreateCubeMapInfo);
void textureFillCubeMap(TextureID textureID, const TextureFillCubeMapInfo* textureFillCubeMapInfo);

void textureDestroy(TextureID textureID);

bool textureIsActive(TextureID textureID);

void textureGenerateMipmap(TextureID textureID);

// 1D Texture: 0 <= xOffset <= width |      yOffset == 0      |      zOffset == 0     | width >= 1 | height == 1 | depth == 1
// 2D Texture: 0 <= xOffset <= width | 0 <= yOffset <= height |      zOffset == 0     | width >= 1 | height >= 1 | depth == 1
// 3D Texture: 0 <= xOffset <= width | 0 <= yOffset <= height | 0 <= zOffset <= depth | width >= 1 | height >= 1 | depth >= 1
// Cube Maps:  0 <= xOffset <= width | 0 <= yOffset <= height | 0 <= zOffset <= 5     | width >= 1 | height >= 1 | depth == 1
void textureGetImage(TextureID textureID, const TextureGetImageInfo* textureGetImageInfo, size_t bufferSize, void* bufferOut);

void textureBindSampler(TextureID textureID, uint32_t unit);

// 1D and 2D Textures:     layered = GL_FALSE | layer = 0
// Full 3D Textures:       layered = GL_TRUE  | layer = 0
// A Slice of 3D Textures: layered = GL_FALSE | layer = sliceIndex
// Full Cube Maps:         layered = GL_TRUE  | layer = 0
// A Face of Cube Maps:    layered = GL_FALSE | layer = faceIndex (0 to 5)
void textureBindImage(TextureID textureID, uint32_t unit, uint32_t level, bool layered, uint32_t layer, AccessPolicy accessPolicy, ExternalFormat externalFormat);

void textureGetDimensions(TextureID textureID, int32_t level, uint32_t* widthOut, uint32_t* heightOut, uint32_t* depthOut);

