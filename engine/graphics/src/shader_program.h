
#pragma once

#include <cglm/cglm.h>
#include "glad/glad.h"

// Vertex Shader:           .vert
// Tess Control Shader:     .tesc
// Tess Evaluation Shader:  .tese
// Geometry Shader:         .geom
// Fragment Shader:         .frag
// Compute Shader:          .comp

#define SHADER_PROGRAM_INVALID_ID 0u

typedef struct ShaderProgram
{
    GLuint ID;
} ShaderProgram;

ShaderProgram shaderProgramCreateC(const char* computeShaderPath);
ShaderProgram shaderProgramCreateV(const char* vertexShaderPath);
ShaderProgram shaderProgramCreateVF(
    const char* vertexShaderPath,
    const char* fragmentShaderPath);
ShaderProgram shaderProgramCreateVGF(
    const char* vertexShaderPath,
    const char* geometryShaderPath,
    const char* fragmentShaderPath);
ShaderProgram shaderProgramCreateVTTF(
    const char* vertexShaderPath,
    const char* tessControlShaderPath,
    const char* tessEvaluationShaderPath,
    const char* fragmentShaderPath);
ShaderProgram shaderProgramCreateVTTGF(
    const char* vertexShaderPath,
    const char* tessControlShaderPath,
    const char* tessEvaluationShaderPath,
    const char* geometryShaderPath,
    const char* fragmentShaderPath);


void shaderProgramDestroy(ShaderProgram shaderProgram);

void shaderProgramBind(ShaderProgram shaderProgram);

void shaderProgramSetUniformi(ShaderProgram shaderProgram, const char* uniform, int          value);
void shaderProgramSetUniformu(ShaderProgram shaderProgram, const char* uniform, unsigned int value);
void shaderProgramSetUniformf(ShaderProgram shaderProgram, const char* uniform, float        value);

void shaderProgramSetUniform2i(ShaderProgram shaderProgram, const char* uniform, ivec2 vector);
void shaderProgramSetUniform3i(ShaderProgram shaderProgram, const char* uniform, ivec3 vector);
void shaderProgramSetUniform4i(ShaderProgram shaderProgram, const char* uniform, ivec4 vector);

void shaderProgramSetUniform2f(ShaderProgram shaderProgram, const char* uniform, vec2 vector);
void shaderProgramSetUniform3f(ShaderProgram shaderProgram, const char* uniform, vec3 vector);
void shaderProgramSetUniform4f(ShaderProgram shaderProgram, const char* uniform, vec4 vector);

void shaderProgramSetUniformMat2f  (ShaderProgram shaderProgram, const char* uniform, mat2   matrix);
void shaderProgramSetUniformMat2x3f(ShaderProgram shaderProgram, const char* uniform, mat2x3 matrix);
void shaderProgramSetUniformMat2x4f(ShaderProgram shaderProgram, const char* uniform, mat2x4 matrix);
void shaderProgramSetUniformMat3x2f(ShaderProgram shaderProgram, const char* uniform, mat3x2 matrix);
void shaderProgramSetUniformMat3f  (ShaderProgram shaderProgram, const char* uniform, mat3   matrix);
void shaderProgramSetUniformMat3x4f(ShaderProgram shaderProgram, const char* uniform, mat3x4 matrix);
void shaderProgramSetUniformMat4x2f(ShaderProgram shaderProgram, const char* uniform, mat4x2 matrix);
void shaderProgramSetUniformMat4x3f(ShaderProgram shaderProgram, const char* uniform, mat4x3 matrix);
void shaderProgramSetUniformMat4f  (ShaderProgram shaderProgram, const char* uniform, mat4   matrix);

