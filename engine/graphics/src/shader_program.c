
#include <stdio.h>
#include <assert.h>
#include "error.h"
#include "shader.h"
#include "log/log.h"
#include "shader_program.h"

static void attachShader(ShaderProgram shaderProgram, Shader shader)
{
    glAttachShader(shaderProgram.ID, shader.ID);
}

static void detachShader(ShaderProgram shaderProgram, Shader shader)
{
    glDetachShader(shaderProgram.ID, shader.ID);
}

static GLint linkShaderProgram(ShaderProgram shaderProgram)
{
    glLinkProgram(shaderProgram.ID);
    
    GLint success = GL_FALSE;
    glGetProgramiv(shaderProgram.ID, GL_LINK_STATUS, &success);
    
    if (success != GL_TRUE)
    {
        GLsizei infoLogLength = 0;
        glGetProgramiv(shaderProgram.ID, GL_INFO_LOG_LENGTH, &infoLogLength);

        char* infoLog = (char*)malloc((infoLogLength + 1ul) * sizeof(char));
        glGetProgramInfoLog(shaderProgram.ID, infoLogLength, NULL, infoLog);
        infoLog[infoLogLength] = '\0';

        logError("PROGRAM", "failed to link\n%s", infoLog);
        free(infoLog);
        return success;
    }
    glCheckErrors();

    logVerbose("PROGRAM", "linked");
    return success;
}

static GLint validateShaderProgram(ShaderProgram shaderProgram)
{
    glValidateProgram(shaderProgram.ID);
    
    GLint success = GL_FALSE;
    glGetProgramiv(shaderProgram.ID, GL_VALIDATE_STATUS, &success);
    
    if (success != GL_TRUE)
    {
        GLsizei infoLogLength = 0;
        glGetProgramiv(shaderProgram.ID, GL_INFO_LOG_LENGTH, &infoLogLength);

        char* infoLog = (char*)malloc((infoLogLength + 1ul) * sizeof(char));
        glGetProgramInfoLog(shaderProgram.ID, infoLogLength, NULL, infoLog);
        infoLog[infoLogLength] = '\0';

        logError("PROGRAM", "failed to validate\n%s", infoLog);
        free(infoLog);
        return success;
    }
    glCheckErrors();
    
    logVerbose("PROGRAM", "validated");
    return success;
}

static GLint getUniformLocation(ShaderProgram shaderProgram, const char* uniform)
{
    const GLint location = glGetUniformLocation(shaderProgram.ID, uniform);
    assert(location != -1);
    return location;
}

ShaderProgram shaderProgramCreateC(const char* computeShaderPath)
{
    Shader computeShader = { .ID = SHADER_INVALID_ID, };
    ShaderProgram shaderProgram = { .ID = SHADER_PROGRAM_INVALID_ID, };

    computeShader = shaderCreate(computeShaderPath, GL_COMPUTE_SHADER);
    if (computeShader.ID == SHADER_INVALID_ID) { goto cleanup; }

    shaderProgram.ID = glCreateProgram();

    attachShader(shaderProgram, computeShader);

    if (linkShaderProgram(shaderProgram)     != GL_TRUE) { goto cleanup; }
    if (validateShaderProgram(shaderProgram) != GL_TRUE) { goto cleanup; }

    detachShader(shaderProgram, computeShader);
    shaderDestroy(computeShader);
    glCheckErrors();

    return shaderProgram;

cleanup:
    if (computeShader.ID != SHADER_INVALID_ID)
    {
        detachShader(shaderProgram, computeShader);
        shaderDestroy(computeShader);
    }
    if (shaderProgram.ID != SHADER_PROGRAM_INVALID_ID)
    {
        glDeleteProgram(shaderProgram.ID);
        shaderProgram.ID = SHADER_PROGRAM_INVALID_ID;
    }

    return shaderProgram;
}

ShaderProgram shaderProgramCreateV(const char* vertexShaderPath)
{
    Shader vertexShader = { .ID = SHADER_INVALID_ID, };
    ShaderProgram shaderProgram = { .ID = SHADER_PROGRAM_INVALID_ID, };

    vertexShader = shaderCreate(vertexShaderPath, GL_VERTEX_SHADER);
    if (vertexShader.ID == SHADER_INVALID_ID) { goto cleanup; }

    shaderProgram.ID = glCreateProgram();

    attachShader(shaderProgram, vertexShader);

    if (linkShaderProgram(shaderProgram)     != GL_TRUE) { goto cleanup; }
    if (validateShaderProgram(shaderProgram) != GL_TRUE) { goto cleanup; }

    detachShader(shaderProgram, vertexShader);
    shaderDestroy(vertexShader);
    glCheckErrors();

    return shaderProgram;

cleanup:
    if (vertexShader.ID != SHADER_INVALID_ID)
    {
        detachShader(shaderProgram, vertexShader);
        shaderDestroy(vertexShader);
    }
    if (shaderProgram.ID != SHADER_PROGRAM_INVALID_ID)
    {
        glDeleteProgram(shaderProgram.ID);
        shaderProgram.ID = SHADER_PROGRAM_INVALID_ID;
    }

    return shaderProgram;
}

ShaderProgram shaderProgramCreateVF(
    const char* vertexShaderPath,
    const char* fragmentShaderPath)
{
    Shader vertexShader = { .ID = SHADER_INVALID_ID, };
    Shader fragmentShader = {.ID = SHADER_INVALID_ID, };
    ShaderProgram shaderProgram = { .ID = SHADER_PROGRAM_INVALID_ID, };

    vertexShader = shaderCreate(vertexShaderPath, GL_VERTEX_SHADER);
    if (vertexShader.ID == SHADER_INVALID_ID) { goto cleanup; }
    fragmentShader = shaderCreate(fragmentShaderPath, GL_FRAGMENT_SHADER);
    if (fragmentShader.ID == SHADER_INVALID_ID) { goto cleanup; }

    shaderProgram.ID = glCreateProgram();

    attachShader(shaderProgram, vertexShader);
    attachShader(shaderProgram, fragmentShader);

    if (linkShaderProgram(shaderProgram)     != GL_TRUE) { goto cleanup; }
    if (validateShaderProgram(shaderProgram) != GL_TRUE) { goto cleanup; }

    detachShader(shaderProgram, vertexShader);
    shaderDestroy(vertexShader);
    detachShader(shaderProgram, fragmentShader);
    shaderDestroy(fragmentShader);
    glCheckErrors();

    return shaderProgram;

cleanup:
    if (vertexShader.ID != SHADER_INVALID_ID)
    {
        detachShader(shaderProgram, vertexShader);
        shaderDestroy(vertexShader);
    }
    if (fragmentShader.ID != SHADER_INVALID_ID)
    {
        detachShader(shaderProgram, fragmentShader);
        shaderDestroy(fragmentShader);
    }
    if (shaderProgram.ID != SHADER_PROGRAM_INVALID_ID)
    {
        glDeleteProgram(shaderProgram.ID);
        shaderProgram.ID = SHADER_PROGRAM_INVALID_ID;
    }

    return shaderProgram;
}

ShaderProgram shaderProgramCreateVGF(
    const char* vertexShaderPath,
    const char* geometryShaderPath,
    const char* fragmentShaderPath)
{
    Shader vertexShader = { .ID = SHADER_INVALID_ID, };
    Shader geometryShader = { .ID = SHADER_INVALID_ID, };
    Shader fragmentShader = { .ID = SHADER_INVALID_ID, };
    ShaderProgram shaderProgram = { .ID = SHADER_PROGRAM_INVALID_ID, };

    vertexShader = shaderCreate(vertexShaderPath, GL_VERTEX_SHADER);
    if (vertexShader.ID == SHADER_INVALID_ID) { goto cleanup; }
    geometryShader = shaderCreate(geometryShaderPath, GL_GEOMETRY_SHADER);
    if (geometryShader.ID == SHADER_INVALID_ID) { goto cleanup; }
    fragmentShader = shaderCreate(fragmentShaderPath, GL_FRAGMENT_SHADER);
    if (fragmentShader.ID == SHADER_INVALID_ID) { goto cleanup; }

    shaderProgram.ID = glCreateProgram();

    attachShader(shaderProgram, vertexShader);
    attachShader(shaderProgram, geometryShader);
    attachShader(shaderProgram, fragmentShader);

    if (linkShaderProgram(shaderProgram)     != GL_TRUE) { goto cleanup; }
    if (validateShaderProgram(shaderProgram) != GL_TRUE) { goto cleanup; }

    detachShader(shaderProgram, vertexShader);
    shaderDestroy(vertexShader);
    detachShader(shaderProgram, geometryShader);
    shaderDestroy(geometryShader);
    detachShader(shaderProgram, fragmentShader);
    shaderDestroy(fragmentShader);
    glCheckErrors();

    return shaderProgram;

cleanup:
    if (vertexShader.ID != SHADER_INVALID_ID)
    {
        detachShader(shaderProgram, vertexShader);
        shaderDestroy(vertexShader);
    }
    if (geometryShader.ID != SHADER_INVALID_ID)
    {
        detachShader(shaderProgram, geometryShader);
        shaderDestroy(geometryShader);
    }
    if (fragmentShader.ID != SHADER_INVALID_ID)
    {
        detachShader(shaderProgram, fragmentShader);
        shaderDestroy(fragmentShader);
    }
    if (shaderProgram.ID != SHADER_PROGRAM_INVALID_ID)
    {
        glDeleteProgram(shaderProgram.ID);
        shaderProgram.ID = SHADER_PROGRAM_INVALID_ID;
    }

    return shaderProgram;
}

ShaderProgram shaderProgramCreateVTTF(
    const char* vertexShaderPath,
    const char* tessControlShaderPath,
    const char* tessEvaluationShaderPath,
    const char* fragmentShaderPath)
{
    Shader vertexShader = { .ID = SHADER_INVALID_ID, };
    Shader tessControlShader = { .ID = SHADER_INVALID_ID, };
    Shader tessEvaluationShader = { .ID = SHADER_INVALID_ID, };
    Shader fragmentShader = { .ID = SHADER_INVALID_ID, };
    ShaderProgram shaderProgram = { .ID = SHADER_PROGRAM_INVALID_ID, };

    vertexShader = shaderCreate(vertexShaderPath, GL_VERTEX_SHADER);
    if (vertexShader.ID == SHADER_INVALID_ID) { goto cleanup; }
    tessControlShader = shaderCreate(tessControlShaderPath, GL_TESS_CONTROL_SHADER);
    if (tessControlShader.ID == SHADER_INVALID_ID) { goto cleanup; }
    tessEvaluationShader = shaderCreate(tessEvaluationShaderPath, GL_TESS_EVALUATION_SHADER);
    if (tessEvaluationShader.ID == SHADER_INVALID_ID) { goto cleanup; }
    fragmentShader = shaderCreate(fragmentShaderPath, GL_FRAGMENT_SHADER);
    if (fragmentShader.ID == SHADER_INVALID_ID) { goto cleanup; }

    shaderProgram.ID = glCreateProgram();

    attachShader(shaderProgram, vertexShader);
    attachShader(shaderProgram, tessControlShader);
    attachShader(shaderProgram, tessEvaluationShader);
    attachShader(shaderProgram, fragmentShader);

    if (linkShaderProgram(shaderProgram)     != GL_TRUE) { goto cleanup; }
    if (validateShaderProgram(shaderProgram) != GL_TRUE) { goto cleanup; }

    detachShader(shaderProgram, vertexShader);
    shaderDestroy(vertexShader);
    detachShader(shaderProgram, tessControlShader);
    shaderDestroy(tessControlShader);
    detachShader(shaderProgram, tessEvaluationShader);
    shaderDestroy(tessEvaluationShader);
    detachShader(shaderProgram, fragmentShader);
    shaderDestroy(fragmentShader);
    glCheckErrors();

    return shaderProgram;

cleanup:
    if (vertexShader.ID != SHADER_INVALID_ID)
    {
        detachShader(shaderProgram, vertexShader);
        shaderDestroy(vertexShader);
    }
    if (tessControlShader.ID != SHADER_INVALID_ID)
    {
        detachShader(shaderProgram, tessControlShader);
        shaderDestroy(tessControlShader);
    }
    if (tessEvaluationShader.ID != SHADER_INVALID_ID)
    {
        detachShader(shaderProgram, tessEvaluationShader);
        shaderDestroy(tessEvaluationShader);
    }
    if (fragmentShader.ID != SHADER_INVALID_ID)
    {
        detachShader(shaderProgram, fragmentShader);
        shaderDestroy(fragmentShader);
    }
    if (shaderProgram.ID != SHADER_PROGRAM_INVALID_ID)
    {
        glDeleteProgram(shaderProgram.ID);
        shaderProgram.ID = SHADER_PROGRAM_INVALID_ID;
    }

    return shaderProgram;
}

ShaderProgram shaderProgramCreateVTTGF(
    const char* vertexShaderPath,
    const char* tessControlShaderPath,
    const char* tessEvaluationShaderPath,
    const char* geometryShaderPath,
    const char* fragmentShaderPath)
{
    Shader vertexShader = { .ID = SHADER_INVALID_ID, };
    Shader tessControlShader = { .ID = SHADER_INVALID_ID, };
    Shader tessEvaluationShader = { .ID = SHADER_INVALID_ID, };
    Shader geometryShader = { .ID = SHADER_INVALID_ID, };
    Shader fragmentShader = { .ID = SHADER_INVALID_ID, };
    ShaderProgram shaderProgram = { .ID = SHADER_PROGRAM_INVALID_ID, };

    vertexShader = shaderCreate(vertexShaderPath, GL_VERTEX_SHADER);
    if (vertexShader.ID == SHADER_INVALID_ID) { goto cleanup; }
    tessControlShader = shaderCreate(tessControlShaderPath, GL_TESS_CONTROL_SHADER);
    if (tessControlShader.ID == SHADER_INVALID_ID) { goto cleanup; }
    tessEvaluationShader = shaderCreate(tessEvaluationShaderPath, GL_TESS_EVALUATION_SHADER);
    if (tessEvaluationShader.ID == SHADER_INVALID_ID) { goto cleanup; }
    geometryShader = shaderCreate(geometryShaderPath, GL_GEOMETRY_SHADER);
    if (geometryShader.ID == SHADER_INVALID_ID) { goto cleanup; }
    fragmentShader = shaderCreate(fragmentShaderPath, GL_FRAGMENT_SHADER);
    if (fragmentShader.ID == SHADER_INVALID_ID) { goto cleanup; }

    shaderProgram.ID = glCreateProgram();

    attachShader(shaderProgram, vertexShader);
    attachShader(shaderProgram, tessControlShader);
    attachShader(shaderProgram, tessEvaluationShader);
    attachShader(shaderProgram, geometryShader);
    attachShader(shaderProgram, fragmentShader);

    if (linkShaderProgram(shaderProgram)     != GL_TRUE) { goto cleanup; }
    if (validateShaderProgram(shaderProgram) != GL_TRUE) { goto cleanup; }

    detachShader(shaderProgram, vertexShader);
    shaderDestroy(vertexShader);
    detachShader(shaderProgram, tessControlShader);
    shaderDestroy(tessControlShader);
    detachShader(shaderProgram, tessEvaluationShader);
    shaderDestroy(tessEvaluationShader);
    detachShader(shaderProgram, geometryShader);
    shaderDestroy(geometryShader);
    detachShader(shaderProgram, fragmentShader);
    shaderDestroy(fragmentShader);
    glCheckErrors();

    return shaderProgram;

cleanup:
    if (vertexShader.ID != SHADER_INVALID_ID)
    {
        detachShader(shaderProgram, vertexShader);
        shaderDestroy(vertexShader);
    }
    if (tessControlShader.ID != SHADER_INVALID_ID)
    {
        detachShader(shaderProgram, tessControlShader);
        shaderDestroy(tessControlShader);
    }
    if (tessEvaluationShader.ID != SHADER_INVALID_ID)
    {
        detachShader(shaderProgram, tessEvaluationShader);
        shaderDestroy(tessEvaluationShader);
    }
    if (geometryShader.ID != SHADER_INVALID_ID)
    {
        detachShader(shaderProgram, geometryShader);
        shaderDestroy(geometryShader);
    }
    if (fragmentShader.ID != SHADER_INVALID_ID)
    {
        detachShader(shaderProgram, fragmentShader);
        shaderDestroy(fragmentShader);
    }
    if (shaderProgram.ID != SHADER_PROGRAM_INVALID_ID)
    {
        glDeleteProgram(shaderProgram.ID);
        shaderProgram.ID = SHADER_PROGRAM_INVALID_ID;
    }

    return shaderProgram;
}

void shaderProgramDestroy(ShaderProgram shaderProgram)
{
    glDeleteProgram(shaderProgram.ID);
    glCheckErrors();
    logVerbose("PROGRAM", "destroyed");
}

void shaderProgramBind(ShaderProgram shaderProgram)
{
    glUseProgram(shaderProgram.ID);
    glCheckErrors();
    logVerbose("PROGRAM", "binded");
}

void shaderProgramSetUniformi(ShaderProgram shaderProgram, const char* uniform, int value)
{
    glUniform1i(getUniformLocation(shaderProgram, uniform), value);
    glCheckErrors();
}

void shaderProgramSetUniformu(ShaderProgram shaderProgram, const char* uniform, unsigned int value)
{
    glUniform1ui(getUniformLocation(shaderProgram, uniform), value);
    glCheckErrors();
}

void shaderProgramSetUniformf(ShaderProgram shaderProgram, const char* uniform, float value)
{
    glUniform1f(getUniformLocation(shaderProgram, uniform), value);
    glCheckErrors();
}

void shaderProgramSetUniform2i(ShaderProgram shaderProgram, const char* uniform, ivec2 vector)
{
    glUniform2i(getUniformLocation(shaderProgram, uniform), vector[0], vector[1]);
    glCheckErrors();
}

void shaderProgramSetUniform3i(ShaderProgram shaderProgram, const char* uniform, ivec3 vector)
{
    glUniform3i(getUniformLocation(shaderProgram, uniform), vector[0], vector[1], vector[2]);
    glCheckErrors();
}

void shaderProgramSetUniform4i(ShaderProgram shaderProgram, const char* uniform, ivec4 vector)
{
    glUniform4i(getUniformLocation(shaderProgram, uniform), vector[0], vector[1], vector[2], vector[3]);
    glCheckErrors();
}

void shaderProgramSetUniform2f(ShaderProgram shaderProgram, const char* uniform, vec2 vector)
{
    glUniform2f(getUniformLocation(shaderProgram, uniform), vector[0], vector[1]);
    glCheckErrors();
}

void shaderProgramSetUniform3f(ShaderProgram shaderProgram, const char* uniform, vec3 vector)
{
    glUniform3f(getUniformLocation(shaderProgram, uniform), vector[0], vector[1], vector[2]);
    glCheckErrors();
}

void shaderProgramSetUniform4f(ShaderProgram shaderProgram, const char* uniform, vec4 vector)
{
    glUniform4f(getUniformLocation(shaderProgram, uniform), vector[0], vector[1], vector[2], vector[3]);
    glCheckErrors();
}

void shaderProgramSetUniformMat2f(ShaderProgram shaderProgram, const char* uniform, mat2 matrix)
{
    glUniformMatrix2fv(getUniformLocation(shaderProgram, uniform), 1, GL_FALSE, (float*)matrix);
    glCheckErrors();
}

void shaderProgramSetUniformMat2x3f(ShaderProgram shaderProgram, const char* uniform, mat2x3 matrix)
{
    glUniformMatrix2x3fv(getUniformLocation(shaderProgram, uniform), 1, GL_FALSE, (float*)matrix);
    glCheckErrors();
}

void shaderProgramSetUniformMat2x4f(ShaderProgram shaderProgram, const char* uniform, mat2x4 matrix)
{
    glUniformMatrix2x4fv(getUniformLocation(shaderProgram, uniform), 1, GL_FALSE, (float*)matrix);
    glCheckErrors();
}

void shaderProgramSetUniformMat3x2f(ShaderProgram shaderProgram, const char* uniform, mat3x2 matrix)
{
    glUniformMatrix3x2fv(getUniformLocation(shaderProgram, uniform), 1, GL_FALSE, (float*)matrix);
    glCheckErrors();
}

void shaderProgramSetUniformMat3f(ShaderProgram shaderProgram, const char* uniform, mat3 matrix)
{
    glUniformMatrix3fv(getUniformLocation(shaderProgram, uniform), 1, GL_FALSE, (float*)matrix);
    glCheckErrors();
}

void shaderProgramSetUniformMat3x4f(ShaderProgram shaderProgram, const char* uniform, mat3x4 matrix)
{
    glUniformMatrix3x4fv(getUniformLocation(shaderProgram, uniform), 1, GL_FALSE, (float*)matrix);
    glCheckErrors();
}

void shaderProgramSetUniformMat4x2f(ShaderProgram shaderProgram, const char* uniform, mat4x2 matrix)
{
    glUniformMatrix4x2fv(getUniformLocation(shaderProgram, uniform), 1, GL_FALSE, (float*)matrix);
    glCheckErrors();
}

void shaderProgramSetUniformMat4x3f(ShaderProgram shaderProgram, const char* uniform, mat4x3 matrix)
{
    glUniformMatrix4x3fv(getUniformLocation(shaderProgram, uniform), 1, GL_FALSE, (float*)matrix);
    glCheckErrors();
}

void shaderProgramSetUniformMat4f(ShaderProgram shaderProgram, const char* uniform, mat4 matrix)
{
    glUniformMatrix4fv(getUniformLocation(shaderProgram, uniform), 1, GL_FALSE, (float*)matrix);
    glCheckErrors();
}

