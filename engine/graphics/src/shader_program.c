
#include <stdio.h>
#include <assert.h>
#include "error.h"
#include "shader_program.h"
#include "log/log.h"
#include "glad/glad.h"

#define SHADER_NULL 0u

static char* readFile(const char* filePath, size_t* sizeOut)
{
    FILE* file = fopen(filePath, "rb");
    if (file == NULL)
    {
        logError("SHADER", "failed to read %s", filePath);
        if (sizeOut != NULL) { *sizeOut = 0ul; }
        return NULL;
    }

    fseek(file, 0l, SEEK_END);
    size_t size = (size_t)ftell(file);
    rewind(file);

    char* buffer = (char*)malloc((size + 1ul) * sizeof(char));
    size = fread(buffer, 1ul, size, file);
    buffer[size] = '\0';
    fclose(file);

    if (sizeOut != NULL) { *sizeOut = size; }
    return buffer;
}

static GLuint createShader(const char* shaderPath, GLenum type)
{
    char* shaderCode = readFile(shaderPath, NULL);
    if (shaderCode == NULL)
    {
        return SHADER_NULL;
    }

    const GLuint shader = glCreateShader(type);
    const char* source = shaderCode;
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);
    free(shaderCode);

    GLint success = GL_FALSE;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (success != GL_TRUE)
    {
        GLsizei infoLogLength = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

        char* infoLog = (char*)malloc((infoLogLength + 1ul) * sizeof(char));
        glGetShaderInfoLog(shader, infoLogLength, NULL, infoLog);
        infoLog[infoLogLength] = '\0';

        logError("SHADER", "failed to compile %s:\n%s", shaderPath, infoLog);
        free(infoLog);

        glDeleteShader(shader);
        return shader;
    }
    glCheckErrors();

    logVerbose("SHADER", "%s is compiled", shaderPath);
    return shader;
}

static void destroyShader(GLuint shader)
{
    glDeleteShader(shader);
}

static void attachShader(ShaderProgramID shaderProgram, GLuint shader)
{
    glAttachShader(shaderProgram, shader);
}

static void detachShader(ShaderProgramID shaderProgram, GLuint shader)
{
    glDetachShader(shaderProgram, shader);
}

static GLint linkShaderProgram(ShaderProgramID shaderProgram)
{
    glLinkProgram(shaderProgram);
    
    GLint success = GL_FALSE;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    
    if (success != GL_TRUE)
    {
        GLsizei infoLogLength = 0;
        glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &infoLogLength);

        char* infoLog = (char*)malloc((infoLogLength + 1ul) * sizeof(char));
        glGetProgramInfoLog(shaderProgram, infoLogLength, NULL, infoLog);
        infoLog[infoLogLength] = '\0';

        logError("PROGRAM", "failed to link\n%s", infoLog);
        free(infoLog);
        return success;
    }
    glCheckErrors();

    logVerbose("PROGRAM", "linked");
    return success;
}

static GLint validateShaderProgram(ShaderProgramID shaderProgram)
{
    glValidateProgram(shaderProgram);
    
    GLint success = GL_FALSE;
    glGetProgramiv(shaderProgram, GL_VALIDATE_STATUS, &success);
    
    if (success != GL_TRUE)
    {
        GLsizei infoLogLength = 0;
        glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &infoLogLength);

        char* infoLog = (char*)malloc((infoLogLength + 1ul) * sizeof(char));
        glGetProgramInfoLog(shaderProgram, infoLogLength, NULL, infoLog);
        infoLog[infoLogLength] = '\0';

        logError("PROGRAM", "failed to validate\n%s", infoLog);
        free(infoLog);
        return success;
    }
    glCheckErrors();
    
    logVerbose("PROGRAM", "validated");
    return success;
}

static GLint getUniformLocation(ShaderProgramID shaderProgram, const char* uniform)
{
    const GLint location = glGetUniformLocation(shaderProgram, uniform);
    assert(location != -1);
    return location;
}

ShaderProgramID shaderProgramCreateC(const char* computeShaderPath)
{
    GLuint computeShader = SHADER_NULL;
    ShaderProgramID shaderProgram = SHADER_PROGRAM_NULL;

    computeShader = createShader(computeShaderPath, GL_COMPUTE_SHADER);
    if (computeShader == SHADER_NULL) { goto cleanup; }

    shaderProgram = glCreateProgram();
    attachShader(shaderProgram, computeShader);

    if (linkShaderProgram(shaderProgram)     != GL_TRUE) { goto cleanup; }
    if (validateShaderProgram(shaderProgram) != GL_TRUE) { goto cleanup; }

    detachShader(shaderProgram, computeShader);
    destroyShader(computeShader);
    glCheckErrors();

    return shaderProgram;

cleanup:
    if (computeShader != SHADER_NULL)
    {
        detachShader(shaderProgram, computeShader);
        destroyShader(computeShader);
    }
    if (shaderProgram != SHADER_PROGRAM_NULL)
    {
        glDeleteProgram(shaderProgram);
        shaderProgram = SHADER_PROGRAM_NULL;
    }

    return shaderProgram;
}

ShaderProgramID shaderProgramCreateV(const char* vertexShaderPath)
{
    GLuint vertexShader = SHADER_NULL;
    ShaderProgramID shaderProgram = SHADER_PROGRAM_NULL;

    vertexShader = createShader(vertexShaderPath, GL_VERTEX_SHADER);
    if (vertexShader == SHADER_NULL) { goto cleanup; }

    shaderProgram = glCreateProgram();
    attachShader(shaderProgram, vertexShader);

    if (linkShaderProgram(shaderProgram)     != GL_TRUE) { goto cleanup; }
    if (validateShaderProgram(shaderProgram) != GL_TRUE) { goto cleanup; }

    detachShader(shaderProgram, vertexShader);
    destroyShader(vertexShader);
    glCheckErrors();

    return shaderProgram;

cleanup:
    if (vertexShader != SHADER_NULL)
    {
        detachShader(shaderProgram, vertexShader);
        destroyShader(vertexShader);
    }
    if (shaderProgram != SHADER_PROGRAM_NULL)
    {
        glDeleteProgram(shaderProgram);
        shaderProgram = SHADER_PROGRAM_NULL;
    }

    return shaderProgram;
}

ShaderProgramID shaderProgramCreateVF(
    const char* vertexShaderPath,
    const char* fragmentShaderPath)
{
    GLuint vertexShader = SHADER_NULL;
    GLuint fragmentShader = SHADER_NULL;
    ShaderProgramID shaderProgram = SHADER_PROGRAM_NULL;

    vertexShader = createShader(vertexShaderPath, GL_VERTEX_SHADER);
    if (vertexShader == SHADER_NULL) { goto cleanup; }
    fragmentShader = createShader(fragmentShaderPath, GL_FRAGMENT_SHADER);
    if (fragmentShader == SHADER_NULL) { goto cleanup; }

    shaderProgram = glCreateProgram();
    attachShader(shaderProgram, vertexShader);
    attachShader(shaderProgram, fragmentShader);

    if (linkShaderProgram(shaderProgram)     != GL_TRUE) { goto cleanup; }
    if (validateShaderProgram(shaderProgram) != GL_TRUE) { goto cleanup; }

    detachShader(shaderProgram, vertexShader);
    destroyShader(vertexShader);
    detachShader(shaderProgram, fragmentShader);
    destroyShader(fragmentShader);
    glCheckErrors();

    return shaderProgram;

cleanup:
    if (vertexShader != SHADER_NULL)
    {
        detachShader(shaderProgram, vertexShader);
        destroyShader(vertexShader);
    }
    if (fragmentShader != SHADER_NULL)
    {
        detachShader(shaderProgram, fragmentShader);
        destroyShader(fragmentShader);
    }
    if (shaderProgram != SHADER_PROGRAM_NULL)
    {
        glDeleteProgram(shaderProgram);
        shaderProgram = SHADER_PROGRAM_NULL;
    }

    return shaderProgram;
}

ShaderProgramID shaderProgramCreateVGF(
    const char* vertexShaderPath,
    const char* geometryShaderPath,
    const char* fragmentShaderPath)
{
    GLuint vertexShader = SHADER_NULL;
    GLuint geometryShader = SHADER_NULL;
    GLuint fragmentShader = SHADER_NULL;
    ShaderProgramID shaderProgram = SHADER_PROGRAM_NULL;

    vertexShader = createShader(vertexShaderPath, GL_VERTEX_SHADER);
    if (vertexShader == SHADER_NULL) { goto cleanup; }
    geometryShader = createShader(geometryShaderPath, GL_GEOMETRY_SHADER);
    if (geometryShader == SHADER_NULL) { goto cleanup; }
    fragmentShader = createShader(fragmentShaderPath, GL_FRAGMENT_SHADER);
    if (fragmentShader == SHADER_NULL) { goto cleanup; }

    shaderProgram = glCreateProgram();
    attachShader(shaderProgram, vertexShader);
    attachShader(shaderProgram, geometryShader);
    attachShader(shaderProgram, fragmentShader);

    if (linkShaderProgram(shaderProgram)     != GL_TRUE) { goto cleanup; }
    if (validateShaderProgram(shaderProgram) != GL_TRUE) { goto cleanup; }

    detachShader(shaderProgram, vertexShader);
    destroyShader(vertexShader);
    detachShader(shaderProgram, geometryShader);
    destroyShader(geometryShader);
    detachShader(shaderProgram, fragmentShader);
    destroyShader(fragmentShader);
    glCheckErrors();

    return shaderProgram;

cleanup:
    if (vertexShader != SHADER_NULL)
    {
        detachShader(shaderProgram, vertexShader);
        destroyShader(vertexShader);
    }
    if (geometryShader != SHADER_NULL)
    {
        detachShader(shaderProgram, geometryShader);
        destroyShader(geometryShader);
    }
    if (fragmentShader != SHADER_NULL)
    {
        detachShader(shaderProgram, fragmentShader);
        destroyShader(fragmentShader);
    }
    if (shaderProgram != SHADER_PROGRAM_NULL)
    {
        glDeleteProgram(shaderProgram);
        shaderProgram = SHADER_PROGRAM_NULL;
    }

    return shaderProgram;
}

ShaderProgramID shaderProgramCreateVTTF(
    const char* vertexShaderPath,
    const char* tessControlShaderPath,
    const char* tessEvaluationShaderPath,
    const char* fragmentShaderPath)
{
    GLuint vertexShader = SHADER_NULL;
    GLuint tessControlShader = SHADER_NULL;
    GLuint tessEvaluationShader = SHADER_NULL;
    GLuint fragmentShader = SHADER_NULL;
    ShaderProgramID shaderProgram = SHADER_PROGRAM_NULL;

    vertexShader = createShader(vertexShaderPath, GL_VERTEX_SHADER);
    if (vertexShader == SHADER_NULL) { goto cleanup; }
    tessControlShader = createShader(tessControlShaderPath, GL_TESS_CONTROL_SHADER);
    if (tessControlShader == SHADER_NULL) { goto cleanup; }
    tessEvaluationShader = createShader(tessEvaluationShaderPath, GL_TESS_EVALUATION_SHADER);
    if (tessEvaluationShader == SHADER_NULL) { goto cleanup; }
    fragmentShader = createShader(fragmentShaderPath, GL_FRAGMENT_SHADER);
    if (fragmentShader == SHADER_NULL) { goto cleanup; }

    shaderProgram = glCreateProgram();
    attachShader(shaderProgram, vertexShader);
    attachShader(shaderProgram, tessControlShader);
    attachShader(shaderProgram, tessEvaluationShader);
    attachShader(shaderProgram, fragmentShader);

    if (linkShaderProgram(shaderProgram)     != GL_TRUE) { goto cleanup; }
    if (validateShaderProgram(shaderProgram) != GL_TRUE) { goto cleanup; }

    detachShader(shaderProgram, vertexShader);
    destroyShader(vertexShader);
    detachShader(shaderProgram, tessControlShader);
    destroyShader(tessControlShader);
    detachShader(shaderProgram, tessEvaluationShader);
    destroyShader(tessEvaluationShader);
    detachShader(shaderProgram, fragmentShader);
    destroyShader(fragmentShader);
    glCheckErrors();

    return shaderProgram;

cleanup:
    if (vertexShader != SHADER_NULL)
    {
        detachShader(shaderProgram, vertexShader);
        destroyShader(vertexShader);
    }
    if (tessControlShader != SHADER_NULL)
    {
        detachShader(shaderProgram, tessControlShader);
        destroyShader(tessControlShader);
    }
    if (tessEvaluationShader != SHADER_NULL)
    {
        detachShader(shaderProgram, tessEvaluationShader);
        destroyShader(tessEvaluationShader);
    }
    if (fragmentShader != SHADER_NULL)
    {
        detachShader(shaderProgram, fragmentShader);
        destroyShader(fragmentShader);
    }
    if (shaderProgram != SHADER_PROGRAM_NULL)
    {
        glDeleteProgram(shaderProgram);
        shaderProgram = SHADER_PROGRAM_NULL;
    }

    return shaderProgram;
}

ShaderProgramID shaderProgramCreateVTTGF(
    const char* vertexShaderPath,
    const char* tessControlShaderPath,
    const char* tessEvaluationShaderPath,
    const char* geometryShaderPath,
    const char* fragmentShaderPath)
{
    GLuint vertexShader = SHADER_NULL;
    GLuint tessControlShader = SHADER_NULL;
    GLuint tessEvaluationShader = SHADER_NULL;
    GLuint geometryShader = SHADER_NULL;
    GLuint fragmentShader = SHADER_NULL;
    ShaderProgramID shaderProgram = SHADER_PROGRAM_NULL;

    vertexShader = createShader(vertexShaderPath, GL_VERTEX_SHADER);
    if (vertexShader == SHADER_NULL) { goto cleanup; }
    tessControlShader = createShader(tessControlShaderPath, GL_TESS_CONTROL_SHADER);
    if (tessControlShader == SHADER_NULL) { goto cleanup; }
    tessEvaluationShader = createShader(tessEvaluationShaderPath, GL_TESS_EVALUATION_SHADER);
    if (tessEvaluationShader == SHADER_NULL) { goto cleanup; }
    geometryShader = createShader(geometryShaderPath, GL_GEOMETRY_SHADER);
    if (geometryShader == SHADER_NULL) { goto cleanup; }
    fragmentShader = createShader(fragmentShaderPath, GL_FRAGMENT_SHADER);
    if (fragmentShader == SHADER_NULL) { goto cleanup; }

    shaderProgram = glCreateProgram();
    attachShader(shaderProgram, vertexShader);
    attachShader(shaderProgram, tessControlShader);
    attachShader(shaderProgram, tessEvaluationShader);
    attachShader(shaderProgram, geometryShader);
    attachShader(shaderProgram, fragmentShader);

    if (linkShaderProgram(shaderProgram)     != GL_TRUE) { goto cleanup; }
    if (validateShaderProgram(shaderProgram) != GL_TRUE) { goto cleanup; }

    detachShader(shaderProgram, vertexShader);
    destroyShader(vertexShader);
    detachShader(shaderProgram, tessControlShader);
    destroyShader(tessControlShader);
    detachShader(shaderProgram, tessEvaluationShader);
    destroyShader(tessEvaluationShader);
    detachShader(shaderProgram, geometryShader);
    destroyShader(geometryShader);
    detachShader(shaderProgram, fragmentShader);
    destroyShader(fragmentShader);
    glCheckErrors();

    return shaderProgram;

cleanup:
    if (vertexShader != SHADER_NULL)
    {
        detachShader(shaderProgram, vertexShader);
        destroyShader(vertexShader);
    }
    if (tessControlShader != SHADER_NULL)
    {
        detachShader(shaderProgram, tessControlShader);
        destroyShader(tessControlShader);
    }
    if (tessEvaluationShader != SHADER_NULL)
    {
        detachShader(shaderProgram, tessEvaluationShader);
        destroyShader(tessEvaluationShader);
    }
    if (geometryShader != SHADER_NULL)
    {
        detachShader(shaderProgram, geometryShader);
        destroyShader(geometryShader);
    }
    if (fragmentShader != SHADER_NULL)
    {
        detachShader(shaderProgram, fragmentShader);
        destroyShader(fragmentShader);
    }
    if (shaderProgram != SHADER_PROGRAM_NULL)
    {
        glDeleteProgram(shaderProgram);
        shaderProgram = SHADER_PROGRAM_NULL;
    }

    return shaderProgram;
}

void shaderProgramDestroy(ShaderProgramID shaderProgram)
{
    glDeleteProgram(shaderProgram);
    glCheckErrors();
    logVerbose("PROGRAM", "destroyed");
}

int shaderProgramIsActive(ShaderProgramID shaderProgram)
{
    return (glIsProgram(shaderProgram) == GL_TRUE);
}

void shaderProgramBind(ShaderProgramID shaderProgram)
{
    glUseProgram(shaderProgram);
    glCheckErrors();
    logVerbose("PROGRAM", "binded");
}

void shaderProgramSetUniformi(ShaderProgramID shaderProgram, const char* uniform, int value)
{
    glUniform1i(getUniformLocation(shaderProgram, uniform), value);
    glCheckErrors();
}

void shaderProgramSetUniformu(ShaderProgramID shaderProgram, const char* uniform, unsigned int value)
{
    glUniform1ui(getUniformLocation(shaderProgram, uniform), value);
    glCheckErrors();
}

void shaderProgramSetUniformf(ShaderProgramID shaderProgram, const char* uniform, float value)
{
    glUniform1f(getUniformLocation(shaderProgram, uniform), value);
    glCheckErrors();
}

void shaderProgramSetUniform2i(ShaderProgramID shaderProgram, const char* uniform, ivec2 vector)
{
    glUniform2i(getUniformLocation(shaderProgram, uniform), vector[0], vector[1]);
    glCheckErrors();
}

void shaderProgramSetUniform3i(ShaderProgramID shaderProgram, const char* uniform, ivec3 vector)
{
    glUniform3i(getUniformLocation(shaderProgram, uniform), vector[0], vector[1], vector[2]);
    glCheckErrors();
}

void shaderProgramSetUniform4i(ShaderProgramID shaderProgram, const char* uniform, ivec4 vector)
{
    glUniform4i(getUniformLocation(shaderProgram, uniform), vector[0], vector[1], vector[2], vector[3]);
    glCheckErrors();
}

void shaderProgramSetUniform2f(ShaderProgramID shaderProgram, const char* uniform, vec2 vector)
{
    glUniform2f(getUniformLocation(shaderProgram, uniform), vector[0], vector[1]);
    glCheckErrors();
}

void shaderProgramSetUniform3f(ShaderProgramID shaderProgram, const char* uniform, vec3 vector)
{
    glUniform3f(getUniformLocation(shaderProgram, uniform), vector[0], vector[1], vector[2]);
    glCheckErrors();
}

void shaderProgramSetUniform4f(ShaderProgramID shaderProgram, const char* uniform, vec4 vector)
{
    glUniform4f(getUniformLocation(shaderProgram, uniform), vector[0], vector[1], vector[2], vector[3]);
    glCheckErrors();
}

void shaderProgramSetUniformMat2f(ShaderProgramID shaderProgram, const char* uniform, mat2 matrix)
{
    glUniformMatrix2fv(getUniformLocation(shaderProgram, uniform), 1, GL_FALSE, (float*)matrix);
    glCheckErrors();
}

void shaderProgramSetUniformMat2x3f(ShaderProgramID shaderProgram, const char* uniform, mat2x3 matrix)
{
    glUniformMatrix2x3fv(getUniformLocation(shaderProgram, uniform), 1, GL_FALSE, (float*)matrix);
    glCheckErrors();
}

void shaderProgramSetUniformMat2x4f(ShaderProgramID shaderProgram, const char* uniform, mat2x4 matrix)
{
    glUniformMatrix2x4fv(getUniformLocation(shaderProgram, uniform), 1, GL_FALSE, (float*)matrix);
    glCheckErrors();
}

void shaderProgramSetUniformMat3x2f(ShaderProgramID shaderProgram, const char* uniform, mat3x2 matrix)
{
    glUniformMatrix3x2fv(getUniformLocation(shaderProgram, uniform), 1, GL_FALSE, (float*)matrix);
    glCheckErrors();
}

void shaderProgramSetUniformMat3f(ShaderProgramID shaderProgram, const char* uniform, mat3 matrix)
{
    glUniformMatrix3fv(getUniformLocation(shaderProgram, uniform), 1, GL_FALSE, (float*)matrix);
    glCheckErrors();
}

void shaderProgramSetUniformMat3x4f(ShaderProgramID shaderProgram, const char* uniform, mat3x4 matrix)
{
    glUniformMatrix3x4fv(getUniformLocation(shaderProgram, uniform), 1, GL_FALSE, (float*)matrix);
    glCheckErrors();
}

void shaderProgramSetUniformMat4x2f(ShaderProgramID shaderProgram, const char* uniform, mat4x2 matrix)
{
    glUniformMatrix4x2fv(getUniformLocation(shaderProgram, uniform), 1, GL_FALSE, (float*)matrix);
    glCheckErrors();
}

void shaderProgramSetUniformMat4x3f(ShaderProgramID shaderProgram, const char* uniform, mat4x3 matrix)
{
    glUniformMatrix4x3fv(getUniformLocation(shaderProgram, uniform), 1, GL_FALSE, (float*)matrix);
    glCheckErrors();
}

void shaderProgramSetUniformMat4f(ShaderProgramID shaderProgram, const char* uniform, mat4 matrix)
{
    glUniformMatrix4fv(getUniformLocation(shaderProgram, uniform), 1, GL_FALSE, (float*)matrix);
    glCheckErrors();
}

