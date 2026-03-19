
#include <stdio.h>
#include <assert.h>
#include "log/log.h"
#include "error.h"
#include "shader_program.h"

static GLuint CreateShader(const char* sourcePath, GLenum type)
{
    FILE* sourceFile = fopen(sourcePath, "rb");
    if (sourceFile == NULL)
    {
        LogError("SHADER", "failed to read %s", sourcePath);
        exit(EXIT_FAILURE);
    }

    fseek(sourceFile, 0, SEEK_END);
    const long size = ftell(sourceFile);
    rewind(sourceFile);

    char sourceCode[size+1];
    size_t numCharsRead = fread(sourceCode, 1, size, sourceFile);
    assert(numCharsRead == size);
    sourceCode[size] = '\0';
    fclose(sourceFile);

    GLuint shader = glCreateShader(type);
    const char* sourceCodePtr = (const char*)sourceCode;
    glShaderSource(shader, 1, &sourceCodePtr, NULL);
    glCompileShader(shader);

    GLint success = GL_FALSE;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (success != GL_TRUE)
    {
        GLsizei infoLogLength = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

        char infoLog[infoLogLength+1];
        glGetShaderInfoLog(shader, infoLogLength, NULL, infoLog);

        LogError("SHADER", "failed to compile %s:\n%s", sourcePath, infoLog);
        exit(EXIT_FAILURE);
    }
    glCheckErrors();
    LogVerbose("SHADER", "compiled %s", sourcePath);
    
    return shader;
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

        LogError("PROGRAM", "failed to link\n%s", infoLog);
        exit(EXIT_FAILURE);
    }
    glCheckErrors();
    LogVerbose("PROGRAM", "linked");
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

        LogError("PROGRAM", "failed to validate\n%s", infoLog);
        exit(EXIT_FAILURE);
    }
    glCheckErrors();
    LogVerbose("PROGRAM", "validated");
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
    GLuint computeShader = CreateShader(computeShaderPath, GL_COMPUTE_SHADER);
    glAttachShader(shaderProgram.ID, computeShader);
    Link(shaderProgram);
    Validate(shaderProgram);
    glDetachShader(shaderProgram.ID, computeShader);
    glDeleteShader(computeShader);
    glCheckErrors();

    return shaderProgram;
}

ShaderProgram ShaderProgramCreateV(const char* vertexShaderPath)
{
    ShaderProgram shaderProgram;
    shaderProgram.ID = glCreateProgram();
    GLuint vertexShader = CreateShader(vertexShaderPath, GL_VERTEX_SHADER);
    glAttachShader(shaderProgram.ID, vertexShader);
    Link(shaderProgram);
    Validate(shaderProgram);
    glDetachShader(shaderProgram.ID, vertexShader);
    glDeleteShader(vertexShader);
    glCheckErrors();

    return shaderProgram;
}

ShaderProgram ShaderProgramCreateVF(
    const char* vertexShaderPath,
    const char* fragmentShaderPath)
{
    ShaderProgram shaderProgram;
    shaderProgram.ID = glCreateProgram();
    GLuint vertexShader = CreateShader(vertexShaderPath, GL_VERTEX_SHADER);
    GLuint fragmentShader = CreateShader(fragmentShaderPath, GL_FRAGMENT_SHADER);
    glAttachShader(shaderProgram.ID, vertexShader);
    glAttachShader(shaderProgram.ID, fragmentShader);
    Link(shaderProgram);
    Validate(shaderProgram);
    glDetachShader(shaderProgram.ID, vertexShader);
    glDetachShader(shaderProgram.ID, fragmentShader);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glCheckErrors();

    return shaderProgram;
}

ShaderProgram ShaderProgramCreateVGF(
    const char* vertexShaderPath,
    const char* geometryShaderPath,
    const char* fragmentShaderPath)
{
    ShaderProgram shaderProgram;
    shaderProgram.ID = glCreateProgram();
    GLuint vertexShader = CreateShader(vertexShaderPath, GL_VERTEX_SHADER);
    GLuint geometryShader = CreateShader(geometryShaderPath, GL_GEOMETRY_SHADER);
    GLuint fragmentShader = CreateShader(fragmentShaderPath, GL_FRAGMENT_SHADER);
    glAttachShader(shaderProgram.ID, vertexShader);
    glAttachShader(shaderProgram.ID, geometryShader);
    glAttachShader(shaderProgram.ID, fragmentShader);
    Link(shaderProgram);
    Validate(shaderProgram);
    glDetachShader(shaderProgram.ID, vertexShader);
    glDetachShader(shaderProgram.ID, geometryShader);
    glDetachShader(shaderProgram.ID, fragmentShader);
    glDeleteShader(vertexShader);
    glDeleteShader(geometryShader);
    glDeleteShader(fragmentShader);
    glCheckErrors();

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
    GLuint vertexShader = CreateShader(vertexShaderPath, GL_VERTEX_SHADER);
    GLuint tessControlShader = CreateShader(tessControlShaderPath, GL_TESS_CONTROL_SHADER);
    GLuint tessEvaluationShader = CreateShader(tessEvaluationShaderPath, GL_TESS_EVALUATION_SHADER);
    GLuint fragmentShader = CreateShader(fragmentShaderPath, GL_FRAGMENT_SHADER);
    glAttachShader(shaderProgram.ID, vertexShader);
    glAttachShader(shaderProgram.ID, tessControlShader);
    glAttachShader(shaderProgram.ID, tessEvaluationShader);
    glAttachShader(shaderProgram.ID, fragmentShader);
    Link(shaderProgram);
    Validate(shaderProgram);
    glDetachShader(shaderProgram.ID, vertexShader);
    glDetachShader(shaderProgram.ID, tessControlShader);
    glDetachShader(shaderProgram.ID, tessEvaluationShader);
    glDetachShader(shaderProgram.ID, fragmentShader);
    glDeleteShader(vertexShader);
    glDeleteShader(tessControlShader);
    glDeleteShader(tessEvaluationShader);
    glDeleteShader(fragmentShader);
    glCheckErrors();

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
    GLuint vertexShader = CreateShader(vertexShaderPath, GL_VERTEX_SHADER);
    GLuint tessControlShader = CreateShader(tessControlShaderPath, GL_TESS_CONTROL_SHADER);
    GLuint tessEvaluationShader = CreateShader(tessEvaluationShaderPath, GL_TESS_EVALUATION_SHADER);
    GLuint geometryShader = CreateShader(geometryShaderPath, GL_GEOMETRY_SHADER);
    GLuint fragmentShader = CreateShader(fragmentShaderPath, GL_FRAGMENT_SHADER);
    glAttachShader(shaderProgram.ID, vertexShader);
    glAttachShader(shaderProgram.ID, tessControlShader);
    glAttachShader(shaderProgram.ID, tessEvaluationShader);
    glAttachShader(shaderProgram.ID, geometryShader);
    glAttachShader(shaderProgram.ID, fragmentShader);
    Link(shaderProgram);
    Validate(shaderProgram);
    glDetachShader(shaderProgram.ID, vertexShader);
    glDetachShader(shaderProgram.ID, tessControlShader);
    glDetachShader(shaderProgram.ID, tessEvaluationShader);
    glDetachShader(shaderProgram.ID, geometryShader);
    glDetachShader(shaderProgram.ID, fragmentShader);
    glDeleteShader(vertexShader);
    glDeleteShader(tessControlShader);
    glDeleteShader(tessEvaluationShader);
    glDeleteShader(geometryShader);
    glDeleteShader(fragmentShader);
    glCheckErrors();

    return shaderProgram;
}

void ShaderProgramDelete(ShaderProgram shaderProgram)
{
    glDeleteProgram(shaderProgram.ID);
    glCheckErrors();
    LogVerbose("PROGRAM", "deleted");
}

void ShaderProgramBind(ShaderProgram shaderProgram)
{
    glUseProgram(shaderProgram.ID);
    glCheckErrors();
    LogVerbose("PROGRAM", "binded");
}

void ShaderProgramSetUniformi(ShaderProgram shaderProgram, const char* uniform, int value)
{
    glUniform1i(GetUniformLocation(shaderProgram, uniform), value);
    glCheckErrors();
}

void ShaderProgramSetUniformu(ShaderProgram shaderProgram, const char* uniform, unsigned int value)
{
    glUniform1ui(GetUniformLocation(shaderProgram, uniform), value);
    glCheckErrors();
}

void ShaderProgramSetUniformf(ShaderProgram shaderProgram, const char* uniform, float value)
{
    glUniform1f(GetUniformLocation(shaderProgram, uniform), value);
    glCheckErrors();
}

void ShaderProgramSetUniform2i(ShaderProgram shaderProgram, const char* uniform, ivec2 vector)
{
    glUniform2i(GetUniformLocation(shaderProgram, uniform), vector[0], vector[1]);
    glCheckErrors();
}

void ShaderProgramSetUniform3i(ShaderProgram shaderProgram, const char* uniform, ivec3 vector)
{
    glUniform3i(GetUniformLocation(shaderProgram, uniform), vector[0], vector[1], vector[2]);
    glCheckErrors();
}

void ShaderProgramSetUniform4i(ShaderProgram shaderProgram, const char* uniform, ivec4 vector)
{
    glUniform4i(GetUniformLocation(shaderProgram, uniform), vector[0], vector[1], vector[2], vector[3]);
    glCheckErrors();
}

void ShaderProgramSetUniform2f(ShaderProgram shaderProgram, const char* uniform, vec2 vector)
{
    glUniform2f(GetUniformLocation(shaderProgram, uniform), vector[0], vector[1]);
    glCheckErrors();
}

void ShaderProgramSetUniform3f(ShaderProgram shaderProgram, const char* uniform, vec3 vector)
{
    glUniform3f(GetUniformLocation(shaderProgram, uniform), vector[0], vector[1], vector[2]);
    glCheckErrors();
}

void ShaderProgramSetUniform4f(ShaderProgram shaderProgram, const char* uniform, vec4 vector)
{
    glUniform4f(GetUniformLocation(shaderProgram, uniform), vector[0], vector[1], vector[2], vector[3]);
    glCheckErrors();
}

void ShaderProgramSetUniformMat2f(ShaderProgram shaderProgram, const char* uniform, mat2 matrix)
{
    glUniformMatrix2fv(GetUniformLocation(shaderProgram, uniform), 1, GL_FALSE, (float*)matrix);
    glCheckErrors();
}

void ShaderProgramSetUniformMat2x3f(ShaderProgram shaderProgram, const char* uniform, mat2x3 matrix)
{
    glUniformMatrix2x3fv(GetUniformLocation(shaderProgram, uniform), 1, GL_FALSE, (float*)matrix);
    glCheckErrors();
}

void ShaderProgramSetUniformMat2x4f(ShaderProgram shaderProgram, const char* uniform, mat2x4 matrix)
{
    glUniformMatrix2x4fv(GetUniformLocation(shaderProgram, uniform), 1, GL_FALSE, (float*)matrix);
    glCheckErrors();
}

void ShaderProgramSetUniformMat3x2f(ShaderProgram shaderProgram, const char* uniform, mat3x2 matrix)
{
    glUniformMatrix3x2fv(GetUniformLocation(shaderProgram, uniform), 1, GL_FALSE, (float*)matrix);
    glCheckErrors();
}

void ShaderProgramSetUniformMat3f(ShaderProgram shaderProgram, const char* uniform, mat3 matrix)
{
    glUniformMatrix3fv(GetUniformLocation(shaderProgram, uniform), 1, GL_FALSE, (float*)matrix);
    glCheckErrors();
}

void ShaderProgramSetUniformMat3x4f(ShaderProgram shaderProgram, const char* uniform, mat3x4 matrix)
{
    glUniformMatrix3x4fv(GetUniformLocation(shaderProgram, uniform), 1, GL_FALSE, (float*)matrix);
    glCheckErrors();
}

void ShaderProgramSetUniformMat4x2f(ShaderProgram shaderProgram, const char* uniform, mat4x2 matrix)
{
    glUniformMatrix4x2fv(GetUniformLocation(shaderProgram, uniform), 1, GL_FALSE, (float*)matrix);
    glCheckErrors();
}

void ShaderProgramSetUniformMat4x3f(ShaderProgram shaderProgram, const char* uniform, mat4x3 matrix)
{
    glUniformMatrix4x3fv(GetUniformLocation(shaderProgram, uniform), 1, GL_FALSE, (float*)matrix);
    glCheckErrors();
}

void ShaderProgramSetUniformMat4f(ShaderProgram shaderProgram, const char* uniform, mat4 matrix)
{
    glUniformMatrix4fv(GetUniformLocation(shaderProgram, uniform), 1, GL_FALSE, (float*)matrix);
    glCheckErrors();
}

