
#include "shader.h"
#include "shader_program.h"

static void Attach(ShaderProgram shaderProgram, Shader shader)
{
    glAttachShader(shaderProgram.ID, shader.ID);
}

static void Detach(ShaderProgram shaderProgram, Shader shader)
{
    glDetachShader(shaderProgram.ID, shader.ID);
}

static void Link(ShaderProgram shaderProgram)
{
    glLinkProgram(shaderProgram.ID);
    
    GLint success = GL_FALSE;
    glGetProgramiv(shaderProgram.ID, GL_LINK_STATUS, &success);
    
    if (success != GL_TRUE)
    {
        GLsizei infoLogLength = 0;
        glGetProgramiv(shaderProgram.ID, GL_INFO_LOG_LENGTH, &infoLogLength);

        char infoLog[infoLogLength+1];
        glGetProgramInfoLog(shaderProgram.ID, infoLogLength, NULL, infoLog);

        printf("Failed to link the shader program.\n%s\n", infoLog);
        exit(EXIT_FAILURE);
    }
}

static void Validate(ShaderProgram shaderProgram)
{
    glValidateProgram(shaderProgram.ID);
    
    GLint success = GL_FALSE;
    glGetProgramiv(shaderProgram.ID, GL_VALIDATE_STATUS, &success);
    
    if (success != GL_TRUE)
    {
        GLsizei infoLogLength = 0;
        glGetProgramiv(shaderProgram.ID, GL_INFO_LOG_LENGTH, &infoLogLength);

        char infoLog[infoLogLength+1];
        glGetProgramInfoLog(shaderProgram.ID, infoLogLength, NULL, infoLog);

        printf("Failed to validate the shader program.\n%s\n", infoLog);
        exit(EXIT_FAILURE);
    }
}

static GLint GetUniformLocation(ShaderProgram shaderProgram, const char* uniform)
{
    const GLint location = glGetUniformLocation(shaderProgram.ID, uniform);
    assert(location != -1);
    return location;
}

ShaderProgram ShaderProgramCreateC(const char* computeShaderPath)
{
    ShaderProgram shaderProgram;
    shaderProgram.ID = glCreateProgram();
    Shader computeShader = ShaderCreate(computeShaderPath, ShaderTypeCompute);
    Attach(shaderProgram, computeShader);
    Link(shaderProgram);
    Detach(shaderProgram, computeShader);
    ShaderDelete(computeShader);
}

ShaderProgram ShaderProgramCreateV(const char* vertexShaderPath)
{
    ShaderProgram shaderProgram;
    shaderProgram.ID = glCreateProgram();
    Shader vertexShader = ShaderCreate(vertexShaderPath, ShaderTypeVertex);
    Attach(shaderProgram, vertexShader);
    Link(shaderProgram);
    Detach(shaderProgram, vertexShader);
    ShaderDelete(vertexShader);
}

ShaderProgram ShaderProgramCreateVF(
    const char* vertexShaderPath,
    const char* fragmentShaderPath)
{
    ShaderProgram shaderProgram;
    shaderProgram.ID = glCreateProgram();
    Shader vertexShader = ShaderCreate(vertexShaderPath, ShaderTypeVertex);
    Shader fragmentShader = ShaderCreate(fragmentShaderPath, ShaderTypeFragment);
    Attach(shaderProgram, vertexShader);
    Attach(shaderProgram, fragmentShader);
    Link(shaderProgram);
    Detach(shaderProgram, vertexShader);
    Detach(shaderProgram, fragmentShader);
    ShaderDelete(vertexShader);
    ShaderDelete(fragmentShader);
}

ShaderProgram ShaderProgramCreateVGF(
    const char* vertexShaderPath,
    const char* geometryShaderPath,
    const char* fragmentShaderPath)
{
    ShaderProgram shaderProgram;
    shaderProgram.ID = glCreateProgram();
    Shader vertexShader = ShaderCreate(vertexShaderPath, ShaderTypeVertex);
    Shader geometryShader = ShaderCreate(geometryShaderPath, ShaderTypeGeometry);
    Shader fragmentShader = ShaderCreate(fragmentShaderPath, ShaderTypeFragment);
    Attach(shaderProgram, vertexShader);
    Attach(shaderProgram, geometryShader);
    Attach(shaderProgram, fragmentShader);
    Link(shaderProgram);
    Detach(shaderProgram, vertexShader);
    Detach(shaderProgram, geometryShader);
    Detach(shaderProgram, fragmentShader);
    ShaderDelete(vertexShader);
    ShaderDelete(geometryShader);
    ShaderDelete(fragmentShader);
}

ShaderProgram ShaderProgramCreateVTTF(
    const char* vertexShaderPath,
    const char* tessControlShaderPath,
    const char* tessEvaluationShaderPath,
    const char* fragmentShaderPath)
{
    ShaderProgram shaderProgram;
    shaderProgram.ID = glCreateProgram();
    Shader vertexShader = ShaderCreate(vertexShaderPath, ShaderTypeVertex);
    Shader tessControlShader = ShaderCreate(tessControlShaderPath, ShaderTypeTessControl);
    Shader tessEvaluationShader = ShaderCreate(tessEvaluationShaderPath, ShaderTypeTessEvaluation);
    Shader fragmentShader = ShaderCreate(fragmentShaderPath, ShaderTypeFragment);
    Attach(shaderProgram, vertexShader);
    Attach(shaderProgram, tessControlShader);
    Attach(shaderProgram, tessEvaluationShader);
    Attach(shaderProgram, fragmentShader);
    Link(shaderProgram);
    Detach(shaderProgram, vertexShader);
    Detach(shaderProgram, tessControlShader);
    Detach(shaderProgram, tessEvaluationShader);
    Detach(shaderProgram, fragmentShader);
    ShaderDelete(vertexShader);
    ShaderDelete(tessControlShader);
    ShaderDelete(tessEvaluationShader);
    ShaderDelete(fragmentShader);
}

ShaderProgram ShaderProgramCreateVTTGF(
    const char* vertexShaderPath,
    const char* tessControlShaderPath,
    const char* tessEvaluationShaderPath,
    const char* geometryShaderPath,
    const char* fragmentShaderPath)
{
    ShaderProgram shaderProgram;
    shaderProgram.ID = glCreateProgram();
    Shader vertexShader = ShaderCreate(vertexShaderPath, ShaderTypeVertex);
    Shader tessControlShader = ShaderCreate(tessControlShaderPath, ShaderTypeTessControl);
    Shader tessEvaluationShader = ShaderCreate(tessEvaluationShaderPath, ShaderTypeTessEvaluation);
    Shader geometryShader = ShaderCreate(geometryShaderPath, ShaderTypeGeometry);
    Shader fragmentShader = ShaderCreate(fragmentShaderPath, ShaderTypeFragment);
    Attach(shaderProgram, vertexShader);
    Attach(shaderProgram, tessControlShader);
    Attach(shaderProgram, tessEvaluationShader);
    Attach(shaderProgram, geometryShader);
    Attach(shaderProgram, fragmentShader);
    Link(shaderProgram);
    Detach(shaderProgram, vertexShader);
    Detach(shaderProgram, tessControlShader);
    Detach(shaderProgram, tessEvaluationShader);
    Detach(shaderProgram, geometryShader);
    Detach(shaderProgram, fragmentShader);
    ShaderDelete(vertexShader);
    ShaderDelete(tessControlShader);
    ShaderDelete(tessEvaluationShader);
    ShaderDelete(geometryShader);
    ShaderDelete(fragmentShader);
}

void ShaderProgramDelete(ShaderProgram shaderProgram)
{
    glDeleteProgram(shaderProgram.ID);
}

void ShaderProgramBind(ShaderProgram shaderProgram)
{
    glUseProgram(shaderProgram.ID);
}

void ShaderProgramSetUniformi(ShaderProgram shaderProgram, const char* uniform, int value)
{
    glProgramUniform1i(shaderProgram.ID, GetUniformLocation(shaderProgram, uniform), value);
}

void ShaderProgramSetUniformu(ShaderProgram shaderProgram, const char* uniform, unsigned int value)
{
    glProgramUniform1ui(shaderProgram.ID, GetUniformLocation(shaderProgram, uniform), value);
}

void ShaderProgramSetUniformf(ShaderProgram shaderProgram, const char* uniform, float value)
{
    glProgramUniform1f(shaderProgram.ID, GetUniformLocation(shaderProgram, uniform), value);
}

void ShaderProgramSetUniform2i(ShaderProgram shaderProgram, const char* uniform, ivec2 vector)
{
    glProgramUniform2i(shaderProgram.ID, GetUniformLocation(shaderProgram, uniform), vector[0], vector[1]);
}

void ShaderProgramSetUniform3i(ShaderProgram shaderProgram, const char* uniform, ivec3 vector)
{
    glProgramUniform3i(shaderProgram.ID, GetUniformLocation(shaderProgram, uniform), vector[0], vector[1], vector[2]);
}

void ShaderProgramSetUniform4i(ShaderProgram shaderProgram, const char* uniform, ivec4 vector)
{
    glProgramUniform4i(shaderProgram.ID, GetUniformLocation(shaderProgram, uniform), vector[0], vector[1], vector[2], vector[3]);
}

void ShaderProgramSetUniform2f(ShaderProgram shaderProgram, const char* uniform, vec2 vector)
{
    glProgramUniform2f(shaderProgram.ID, GetUniformLocation(shaderProgram, uniform), vector[0], vector[1]);
}

void ShaderProgramSetUniform3f(ShaderProgram shaderProgram, const char* uniform, vec3 vector)
{
    glProgramUniform3f(shaderProgram.ID, GetUniformLocation(shaderProgram, uniform), vector[0], vector[1], vector[2]);
}

void ShaderProgramSetUniform4f(ShaderProgram shaderProgram, const char* uniform, vec4 vector)
{
    glProgramUniform4f(shaderProgram.ID, GetUniformLocation(shaderProgram, uniform), vector[0], vector[1], vector[2], vector[3]);
}

void ShaderProgramSetUniformMat2f(ShaderProgram shaderProgram, const char* uniform, mat2 matrix)
{
    glProgramUniformMatrix2fv(shaderProgram.ID, GetUniformLocation(shaderProgram, uniform), 1, GL_FALSE, (float*)matrix);
}

void ShaderProgramSetUniformMat2x3f(ShaderProgram shaderProgram, const char* uniform, mat2x3 matrix)
{
    glProgramUniformMatrix2x3fv(shaderProgram.ID, GetUniformLocation(shaderProgram, uniform), 1, GL_FALSE, (float*)matrix);
}

void ShaderProgramSetUniformMat2x4f(ShaderProgram shaderProgram, const char* uniform, mat2x4 matrix)
{
    glProgramUniformMatrix2x4fv(shaderProgram.ID, GetUniformLocation(shaderProgram, uniform), 1, GL_FALSE, (float*)matrix);
}

void ShaderProgramSetUniformMat3x2f(ShaderProgram shaderProgram, const char* uniform, mat3x2 matrix)
{
    glProgramUniformMatrix3x2fv(shaderProgram.ID, GetUniformLocation(shaderProgram, uniform), 1, GL_FALSE, (float*)matrix);
}

void ShaderProgramSetUniformMat3f(ShaderProgram shaderProgram, const char* uniform, mat3 matrix)
{
    glProgramUniformMatrix3fv(shaderProgram.ID, GetUniformLocation(shaderProgram, uniform), 1, GL_FALSE, (float*)matrix);
}

void ShaderProgramSetUniformMat3x4f(ShaderProgram shaderProgram, const char* uniform, mat3x4 matrix)
{
    glProgramUniformMatrix3x4fv(shaderProgram.ID, GetUniformLocation(shaderProgram, uniform), 1, GL_FALSE, (float*)matrix);
}

void ShaderProgramSetUniformMat4x2f(ShaderProgram shaderProgram, const char* uniform, mat4x2 matrix)
{
    glProgramUniformMatrix4x2fv(shaderProgram.ID, GetUniformLocation(shaderProgram, uniform), 1, GL_FALSE, (float*)matrix);
}

void ShaderProgramSetUniformMat4x3f(ShaderProgram shaderProgram, const char* uniform, mat4x3 matrix)
{
    glProgramUniformMatrix4x3fv(shaderProgram.ID, GetUniformLocation(shaderProgram, uniform), 1, GL_FALSE, (float*)matrix);
}

void ShaderProgramSetUniformMat4f(ShaderProgram shaderProgram, const char* uniform, mat4 matrix)
{
    glProgramUniformMatrix4fv(shaderProgram.ID, GetUniformLocation(shaderProgram, uniform), 1, GL_FALSE, (float*)matrix);
}

