
#pragma once

#include <stdbool.h>
#include "graphics/enums.h"

typedef uint32_t TextureID;

#define TEXTURE_NULL ((TextureID)0)

TextureID textureCreate(const char* texturePath);

void textureDestroy(TextureID textureID);

bool textureIsActive(TextureID textureID);

void textureBindSampler(TextureID textureID, uint32_t unit);
void textureBindImage(TextureID textureID, uint32_t unit, int32_t mipLevel, AccessPolicy accessPolicy, ExternalFormat externalFormat);

