
#pragma once

#include "glad/glad.h"

#define SHADER_INVALID_ID 0u

typedef struct Shader
{
    GLuint ID;
} Shader;

Shader shaderCreate(const char* shaderPath, GLenum type);
void shaderDestroy(Shader shader);

