
#pragma once

typedef unsigned int TextureID;

#define TEXTURE_NULL ((TextureID)0)

TextureID textureCreate(const char* texturePath);
void textureDestroy(TextureID texture);

int textureIsActive(TextureID texture);

void textureBind(TextureID texture, unsigned int unit);

