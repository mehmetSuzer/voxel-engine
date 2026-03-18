
#pragma once

#include "glad/glad.h"

typedef enum ShaderType
{
    ShaderTypeVertex         = GL_VERTEX_SHADER,
    ShaderTypeTessControl    = GL_TESS_CONTROL_SHADER,
    ShaderTypeTessEvaluation = GL_TESS_EVALUATION_SHADER,
    ShaderTypeGeometry       = GL_GEOMETRY_SHADER,
    ShaderTypeFragment       = GL_FRAGMENT_SHADER,
    ShaderTypeCompute        = GL_COMPUTE_SHADER,
} ShaderType;

typedef struct Shader
{
    GLuint ID;
} Shader;

Shader ShaderCreate(const char* sourcePath, ShaderType type);
void ShaderDelete(Shader shader);

