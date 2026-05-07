
#pragma once

#include <cglm/cglm.h>

// Vertex Shader:           .vert
// Tess Control Shader:     .tesc
// Tess Evaluation Shader:  .tese
// Geometry Shader:         .geom
// Fragment Shader:         .frag
// Compute Shader:          .comp

typedef unsigned int ShaderProgramID;

#define SHADER_PROGRAM_NULL ((ShaderProgramID)0)

ShaderProgramID shaderProgramCreateC(const char* computeShaderPath);
ShaderProgramID shaderProgramCreateV(const char* vertexShaderPath);
ShaderProgramID shaderProgramCreateVF(
    const char* vertexShaderPath,
    const char* fragmentShaderPath);
ShaderProgramID shaderProgramCreateVGF(
    const char* vertexShaderPath,
    const char* geometryShaderPath,
    const char* fragmentShaderPath);
ShaderProgramID shaderProgramCreateVTTF(
    const char* vertexShaderPath,
    const char* tessControlShaderPath,
    const char* tessEvaluationShaderPath,
    const char* fragmentShaderPath);
ShaderProgramID shaderProgramCreateVTTGF(
    const char* vertexShaderPath,
    const char* tessControlShaderPath,
    const char* tessEvaluationShaderPath,
    const char* geometryShaderPath,
    const char* fragmentShaderPath);

void shaderProgramDestroy(ShaderProgramID shaderProgram);

int shaderProgramIsActive(ShaderProgramID shaderProgram);

void shaderProgramBind(ShaderProgramID shaderProgram);

void shaderProgramSetUniformi(ShaderProgramID shaderProgram, const char* uniform, int          value);
void shaderProgramSetUniformu(ShaderProgramID shaderProgram, const char* uniform, unsigned int value);
void shaderProgramSetUniformf(ShaderProgramID shaderProgram, const char* uniform, float        value);

void shaderProgramSetUniform2i(ShaderProgramID shaderProgram, const char* uniform, ivec2 vector);
void shaderProgramSetUniform3i(ShaderProgramID shaderProgram, const char* uniform, ivec3 vector);
void shaderProgramSetUniform4i(ShaderProgramID shaderProgram, const char* uniform, ivec4 vector);

void shaderProgramSetUniform2f(ShaderProgramID shaderProgram, const char* uniform, vec2 vector);
void shaderProgramSetUniform3f(ShaderProgramID shaderProgram, const char* uniform, vec3 vector);
void shaderProgramSetUniform4f(ShaderProgramID shaderProgram, const char* uniform, vec4 vector);

void shaderProgramSetUniformMat2f  (ShaderProgramID shaderProgram, const char* uniform, mat2   matrix);
void shaderProgramSetUniformMat2x3f(ShaderProgramID shaderProgram, const char* uniform, mat2x3 matrix);
void shaderProgramSetUniformMat2x4f(ShaderProgramID shaderProgram, const char* uniform, mat2x4 matrix);
void shaderProgramSetUniformMat3x2f(ShaderProgramID shaderProgram, const char* uniform, mat3x2 matrix);
void shaderProgramSetUniformMat3f  (ShaderProgramID shaderProgram, const char* uniform, mat3   matrix);
void shaderProgramSetUniformMat3x4f(ShaderProgramID shaderProgram, const char* uniform, mat3x4 matrix);
void shaderProgramSetUniformMat4x2f(ShaderProgramID shaderProgram, const char* uniform, mat4x2 matrix);
void shaderProgramSetUniformMat4x3f(ShaderProgramID shaderProgram, const char* uniform, mat4x3 matrix);
void shaderProgramSetUniformMat4f  (ShaderProgramID shaderProgram, const char* uniform, mat4   matrix);

