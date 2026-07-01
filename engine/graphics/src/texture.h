
#pragma once

#include "graphics/enums.h"

typedef unsigned int TextureID;

#define TEXTURE_NULL ((TextureID)0)

TextureID textureCreate(const char* texturePath);

void textureDestroy(TextureID textureID);

int textureIsActive(TextureID textureID);

void textureBind(TextureID textureID, unsigned int unit);

