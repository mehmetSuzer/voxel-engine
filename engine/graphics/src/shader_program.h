
#pragma once

#include <cglm/cglm.h>

// Vertex Shader:          .vert
// Tess Control Shader:    .tesc
// Tess Evaluation Shader: .tese
// Geometry Shader:        .geom
// Fragment Shader:        .frag
// Compute Shader:         .comp

typedef uint32_t ShaderProgramID;

#define SHADER_PROGRAM_NULL ((ShaderProgramID)0)

ShaderProgramID shaderProgramCreateC(
    const char* computeShaderPath);
ShaderProgramID shaderProgramCreateV(
    const char* vertexShaderPath);
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

void shaderProgramDestroy(ShaderProgramID shaderProgramID);

bool shaderProgramIsActive(ShaderProgramID shaderProgramID);

void shaderProgramBind(ShaderProgramID shaderProgramID);

void shaderProgramSetUniformSampler(ShaderProgramID shaderProgramID, const char* uniform, uint32_t sampler);

void shaderProgramSetUniformi(ShaderProgramID shaderProgramID, const char* uniform, int32_t  value);
void shaderProgramSetUniformu(ShaderProgramID shaderProgramID, const char* uniform, uint32_t value);
void shaderProgramSetUniformf(ShaderProgramID shaderProgramID, const char* uniform, float    value);

void shaderProgramSetUniform2i(ShaderProgramID shaderProgramID, const char* uniform, const ivec2 vector);
void shaderProgramSetUniform3i(ShaderProgramID shaderProgramID, const char* uniform, const ivec3 vector);
void shaderProgramSetUniform4i(ShaderProgramID shaderProgramID, const char* uniform, const ivec4 vector);

void shaderProgramSetUniform2f(ShaderProgramID shaderProgramID, const char* uniform, const vec2 vector);
void shaderProgramSetUniform3f(ShaderProgramID shaderProgramID, const char* uniform, const vec3 vector);
void shaderProgramSetUniform4f(ShaderProgramID shaderProgramID, const char* uniform, const vec4 vector);

void shaderProgramSetUniformMat2f  (ShaderProgramID shaderProgramID, const char* uniform, const mat2   matrix);
void shaderProgramSetUniformMat2x3f(ShaderProgramID shaderProgramID, const char* uniform, const mat2x3 matrix);
void shaderProgramSetUniformMat2x4f(ShaderProgramID shaderProgramID, const char* uniform, const mat2x4 matrix);
void shaderProgramSetUniformMat3x2f(ShaderProgramID shaderProgramID, const char* uniform, const mat3x2 matrix);
void shaderProgramSetUniformMat3f  (ShaderProgramID shaderProgramID, const char* uniform, const mat3   matrix);
void shaderProgramSetUniformMat3x4f(ShaderProgramID shaderProgramID, const char* uniform, const mat3x4 matrix);
void shaderProgramSetUniformMat4x2f(ShaderProgramID shaderProgramID, const char* uniform, const mat4x2 matrix);
void shaderProgramSetUniformMat4x3f(ShaderProgramID shaderProgramID, const char* uniform, const mat4x3 matrix);
void shaderProgramSetUniformMat4f  (ShaderProgramID shaderProgramID, const char* uniform, const mat4   matrix);

