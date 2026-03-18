
#include "shader.h"
#include "shader_program.h"

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
    if (location == -1)
    {
        printf("Failed to locate uniform %s.\n", uniform);
        exit(EXIT_FAILURE);
    }
    return location;
}

ShaderProgram ShaderProgramCreateC(const char* computeShaderPath)
{
    ShaderProgram shaderProgram;
    shaderProgram.ID = glCreateProgram();
    Shader computeShader = ShaderCreate(computeShaderPath, ShaderTypeCompute);
    glAttachShader(shaderProgram.ID, computeShader.ID);
    Link(shaderProgram);
    Validate(shaderProgram);
    glDetachShader(shaderProgram.ID, computeShader.ID);
    ShaderDelete(computeShader);
    return shaderProgram;
}

ShaderProgram ShaderProgramCreateV(const char* vertexShaderPath)
{
    ShaderProgram shaderProgram;
    shaderProgram.ID = glCreateProgram();
    Shader vertexShader = ShaderCreate(vertexShaderPath, ShaderTypeVertex);
    glAttachShader(shaderProgram.ID, vertexShader.ID);
    Link(shaderProgram);
    Validate(shaderProgram);
    glDetachShader(shaderProgram.ID, vertexShader.ID);
    ShaderDelete(vertexShader);
    return shaderProgram;
}

ShaderProgram ShaderProgramCreateVF(
    const char* vertexShaderPath,
    const char* fragmentShaderPath)
{
    ShaderProgram shaderProgram;
    shaderProgram.ID = glCreateProgram();
    Shader vertexShader = ShaderCreate(vertexShaderPath, ShaderTypeVertex);
    Shader fragmentShader = ShaderCreate(fragmentShaderPath, ShaderTypeFragment);
    glAttachShader(shaderProgram.ID, vertexShader.ID);
    glAttachShader(shaderProgram.ID, fragmentShader.ID);
    Link(shaderProgram);
    Validate(shaderProgram);
    glDetachShader(shaderProgram.ID, vertexShader.ID);
    glDetachShader(shaderProgram.ID, fragmentShader.ID);
    ShaderDelete(vertexShader);
    ShaderDelete(fragmentShader);
    return shaderProgram;
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
    glAttachShader(shaderProgram.ID, vertexShader.ID);
    glAttachShader(shaderProgram.ID, geometryShader.ID);
    glAttachShader(shaderProgram.ID, fragmentShader.ID);
    Link(shaderProgram);
    Validate(shaderProgram);
    glDetachShader(shaderProgram.ID, vertexShader.ID);
    glDetachShader(shaderProgram.ID, geometryShader.ID);
    glDetachShader(shaderProgram.ID, fragmentShader.ID);
    ShaderDelete(vertexShader);
    ShaderDelete(geometryShader);
    ShaderDelete(fragmentShader);
    return shaderProgram;
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
    glAttachShader(shaderProgram.ID, vertexShader.ID);
    glAttachShader(shaderProgram.ID, tessControlShader.ID);
    glAttachShader(shaderProgram.ID, tessEvaluationShader.ID);
    glAttachShader(shaderProgram.ID, fragmentShader.ID);
    Link(shaderProgram);
    Validate(shaderProgram);
    glDetachShader(shaderProgram.ID, vertexShader.ID);
    glDetachShader(shaderProgram.ID, tessControlShader.ID);
    glDetachShader(shaderProgram.ID, tessEvaluationShader.ID);
    glDetachShader(shaderProgram.ID, fragmentShader.ID);
    ShaderDelete(vertexShader);
    ShaderDelete(tessControlShader);
    ShaderDelete(tessEvaluationShader);
    ShaderDelete(fragmentShader);
    return shaderProgram;
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
    glAttachShader(shaderProgram.ID, vertexShader.ID);
    glAttachShader(shaderProgram.ID, tessControlShader.ID);
    glAttachShader(shaderProgram.ID, tessEvaluationShader.ID);
    glAttachShader(shaderProgram.ID, geometryShader.ID);
    glAttachShader(shaderProgram.ID, fragmentShader.ID);
    Link(shaderProgram);
    Validate(shaderProgram);
    glDetachShader(shaderProgram.ID, vertexShader.ID);
    glDetachShader(shaderProgram.ID, tessControlShader.ID);
    glDetachShader(shaderProgram.ID, tessEvaluationShader.ID);
    glDetachShader(shaderProgram.ID, geometryShader.ID);
    glDetachShader(shaderProgram.ID, fragmentShader.ID);
    ShaderDelete(vertexShader);
    ShaderDelete(tessControlShader);
    ShaderDelete(tessEvaluationShader);
    ShaderDelete(geometryShader);
    ShaderDelete(fragmentShader);
    return shaderProgram;
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
    glUniform1i(GetUniformLocation(shaderProgram, uniform), value);
}

void ShaderProgramSetUniformu(ShaderProgram shaderProgram, const char* uniform, unsigned int value)
{
    glUniform1ui(GetUniformLocation(shaderProgram, uniform), value);
}

void ShaderProgramSetUniformf(ShaderProgram shaderProgram, const char* uniform, float value)
{
    glUniform1f(GetUniformLocation(shaderProgram, uniform), value);
}

void ShaderProgramSetUniform2i(ShaderProgram shaderProgram, const char* uniform, ivec2 vector)
{
    glUniform2i(GetUniformLocation(shaderProgram, uniform), vector[0], vector[1]);
}

void ShaderProgramSetUniform3i(ShaderProgram shaderProgram, const char* uniform, ivec3 vector)
{
    glUniform3i(GetUniformLocation(shaderProgram, uniform), vector[0], vector[1], vector[2]);
}

void ShaderProgramSetUniform4i(ShaderProgram shaderProgram, const char* uniform, ivec4 vector)
{
    glUniform4i(GetUniformLocation(shaderProgram, uniform), vector[0], vector[1], vector[2], vector[3]);
}

void ShaderProgramSetUniform2f(ShaderProgram shaderProgram, const char* uniform, vec2 vector)
{
    glUniform2f(GetUniformLocation(shaderProgram, uniform), vector[0], vector[1]);
}

void ShaderProgramSetUniform3f(ShaderProgram shaderProgram, const char* uniform, vec3 vector)
{
    glUniform3f(GetUniformLocation(shaderProgram, uniform), vector[0], vector[1], vector[2]);
}

void ShaderProgramSetUniform4f(ShaderProgram shaderProgram, const char* uniform, vec4 vector)
{
    glUniform4f(GetUniformLocation(shaderProgram, uniform), vector[0], vector[1], vector[2], vector[3]);
}

void ShaderProgramSetUniformMat2f(ShaderProgram shaderProgram, const char* uniform, mat2 matrix)
{
    glUniformMatrix2fv(GetUniformLocation(shaderProgram, uniform), 1, GL_FALSE, (float*)matrix);
}

void ShaderProgramSetUniformMat2x3f(ShaderProgram shaderProgram, const char* uniform, mat2x3 matrix)
{
    glUniformMatrix2x3fv(GetUniformLocation(shaderProgram, uniform), 1, GL_FALSE, (float*)matrix);
}

void ShaderProgramSetUniformMat2x4f(ShaderProgram shaderProgram, const char* uniform, mat2x4 matrix)
{
    glUniformMatrix2x4fv(GetUniformLocation(shaderProgram, uniform), 1, GL_FALSE, (float*)matrix);
}

void ShaderProgramSetUniformMat3x2f(ShaderProgram shaderProgram, const char* uniform, mat3x2 matrix)
{
    glUniformMatrix3x2fv(GetUniformLocation(shaderProgram, uniform), 1, GL_FALSE, (float*)matrix);
}

void ShaderProgramSetUniformMat3f(ShaderProgram shaderProgram, const char* uniform, mat3 matrix)
{
    glUniformMatrix3fv(GetUniformLocation(shaderProgram, uniform), 1, GL_FALSE, (float*)matrix);
}

void ShaderProgramSetUniformMat3x4f(ShaderProgram shaderProgram, const char* uniform, mat3x4 matrix)
{
    glUniformMatrix3x4fv(GetUniformLocation(shaderProgram, uniform), 1, GL_FALSE, (float*)matrix);
}

void ShaderProgramSetUniformMat4x2f(ShaderProgram shaderProgram, const char* uniform, mat4x2 matrix)
{
    glUniformMatrix4x2fv(GetUniformLocation(shaderProgram, uniform), 1, GL_FALSE, (float*)matrix);
}

void ShaderProgramSetUniformMat4x3f(ShaderProgram shaderProgram, const char* uniform, mat4x3 matrix)
{
    glUniformMatrix4x3fv(GetUniformLocation(shaderProgram, uniform), 1, GL_FALSE, (float*)matrix);
}

void ShaderProgramSetUniformMat4f(ShaderProgram shaderProgram, const char* uniform, mat4 matrix)
{
    glUniformMatrix4fv(GetUniformLocation(shaderProgram, uniform), 1, GL_FALSE, (float*)matrix);
}

