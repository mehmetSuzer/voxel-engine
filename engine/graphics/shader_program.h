
#pragma once

#include <cglm/cglm.h>
#include "glad/glad.h"

// Compute Shader:         .comp
// Vertex Shader:          .vert
// Tess Control Shader:    .tesc
// Tess Evaluation Shader: .tese
// Geometry Shader:        .geom
// Fragment Shader:        .frag

typedef struct ShaderProgram
{
    GLuint ID;
} ShaderProgram;

ShaderProgram ShaderProgramCreateC(const char* computeShaderPath);
ShaderProgram ShaderProgramCreateV(const char* vertexShaderPath);
ShaderProgram ShaderProgramCreateVF(
    const char* vertexShaderPath,
    const char* fragmentShaderPath);
ShaderProgram ShaderProgramCreateVGF(
    const char* vertexShaderPath,
    const char* geometryShaderPath,
    const char* fragmentShaderPath);
ShaderProgram ShaderProgramCreateVTTF(
    const char* vertexShaderPath,
    const char* tessControlShaderPath,
    const char* tessEvaluationShaderPath,
    const char* fragmentShaderPath);
ShaderProgram ShaderProgramCreateVTTGF(
    const char* vertexShaderPath,
    const char* tessControlShaderPath,
    const char* tessEvaluationShaderPath,
    const char* geometryShaderPath,
    const char* fragmentShaderPath);

void ShaderProgramDelete(ShaderProgram shaderProgram);

void ShaderProgramBind(ShaderProgram shaderProgram);

void ShaderProgramSetUniformi(ShaderProgram shaderProgram, const char* uniform, int          value);
void ShaderProgramSetUniformu(ShaderProgram shaderProgram, const char* uniform, unsigned int value);
void ShaderProgramSetUniformf(ShaderProgram shaderProgram, const char* uniform, float        value);

void ShaderProgramSetUniform2i(ShaderProgram shaderProgram, const char* uniform, ivec2 vector);
void ShaderProgramSetUniform3i(ShaderProgram shaderProgram, const char* uniform, ivec3 vector);
void ShaderProgramSetUniform4i(ShaderProgram shaderProgram, const char* uniform, ivec4 vector);

void ShaderProgramSetUniform2f(ShaderProgram shaderProgram, const char* uniform, vec2 vector);
void ShaderProgramSetUniform3f(ShaderProgram shaderProgram, const char* uniform, vec3 vector);
void ShaderProgramSetUniform4f(ShaderProgram shaderProgram, const char* uniform, vec4 vector);

void ShaderProgramSetUniformMat2f  (ShaderProgram shaderProgram, const char* uniform, mat2   matrix);
void ShaderProgramSetUniformMat2x3f(ShaderProgram shaderProgram, const char* uniform, mat2x3 matrix);
void ShaderProgramSetUniformMat2x4f(ShaderProgram shaderProgram, const char* uniform, mat2x4 matrix);
void ShaderProgramSetUniformMat3x2f(ShaderProgram shaderProgram, const char* uniform, mat3x2 matrix);
void ShaderProgramSetUniformMat3f  (ShaderProgram shaderProgram, const char* uniform, mat3   matrix);
void ShaderProgramSetUniformMat3x4f(ShaderProgram shaderProgram, const char* uniform, mat3x4 matrix);
void ShaderProgramSetUniformMat4x2f(ShaderProgram shaderProgram, const char* uniform, mat4x2 matrix);
void ShaderProgramSetUniformMat4x3f(ShaderProgram shaderProgram, const char* uniform, mat4x3 matrix);
void ShaderProgramSetUniformMat4f  (ShaderProgram shaderProgram, const char* uniform, mat4   matrix);

