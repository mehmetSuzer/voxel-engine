
#pragma once

#include <stdbool.h>
#include <cglm/cglm.h>
#include "graphics/enums.h"

typedef uint32_t TextureID;

#define TEXTURE_NULL ((TextureID)0)

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
    vec4 borderColour);

TextureID textureCreateFromImage(
    const char* texturePath,
    TextureWrap wrapS,
    TextureWrap wrapT,
    TextureMinFilter minFilter,
    TextureMagFilter magFilter,
    vec4 borderColour);

TextureID textureCreateFromMemory(
    const uint8_t* data,
    uint32_t length,
    TextureWrap wrapS,
    TextureWrap wrapT,
    TextureMinFilter minFilter,
    TextureMagFilter magFilter,
    vec4 borderColour);

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
    vec4 borderColour);

void textureDestroy(TextureID textureID);

bool textureIsActive(TextureID textureID);

void textureGenerateMipmap(TextureID textureID);

void textureGetImage(TextureID textureID, int32_t mipmapLevel, ExternalFormat externalFormat, DataType dataType, int32_t size, void* bufferOut);

void textureGetImageRange(
    TextureID textureID, 
    int32_t mipmapLevel, 
    ivec3 offsets,
    ivec3 dimensions,
    ExternalFormat externalFormat, 
    DataType dataType, 
    int32_t size, 
    void* bufferOut);

void textureBindSampler(TextureID textureID, uint32_t unit);
void textureBindImage(TextureID textureID, uint32_t unit, int32_t mipLevel, AccessPolicy accessPolicy, ExternalFormat externalFormat);

void textureGetDimensions(TextureID textureID, int32_t mipmapLevel, int32_t* widthOut, int32_t* heightOut);

