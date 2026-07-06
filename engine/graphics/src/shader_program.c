
#include <stdio.h>
#include <assert.h>
#include "shader_program.h"
#include "log/log.h"
#include "glad/glad.h"

#define SHADER_NULL 0

static char* readFile(const char* filePath, size_t* sizeOut)
{
    FILE* file = fopen(filePath, "rb");
    if (file == NULL)
    {
        logError("SHADER", "failed to read %s", filePath);
        if (sizeOut != NULL) { *sizeOut = 0; }
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    size_t size = (size_t)ftell(file);
    rewind(file);

    char* buffer = (char*)malloc((size + 1) * sizeof(char));
    size = fread(buffer, 1, size, file);
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

        char* infoLog = (char*)malloc((infoLogLength + 1) * sizeof(char));
        glGetShaderInfoLog(shader, infoLogLength, NULL, infoLog);
        infoLog[infoLogLength] = '\0';

        logError("SHADER", "failed to compile %s:\n%s", shaderPath, infoLog);
        free(infoLog);

        glDeleteShader(shader);
        return shader;
    }

    logVerbose("SHADER", "%s is compiled", shaderPath);
    return shader;
}

static void destroyShader(GLuint shader)
{
    glDeleteShader(shader);
}

static void attachShader(ShaderProgramID shaderProgramID, GLuint shader)
{
    glAttachShader(shaderProgramID, shader);
}

static void detachShader(ShaderProgramID shaderProgramID, GLuint shader)
{
    glDetachShader(shaderProgramID, shader);
}

static GLint linkShaderProgram(ShaderProgramID shaderProgramID)
{
    glLinkProgram(shaderProgramID);
    
    GLint success = GL_FALSE;
    glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &success);
    
    if (success != GL_TRUE)
    {
        GLsizei infoLogLength = 0;
        glGetProgramiv(shaderProgramID, GL_INFO_LOG_LENGTH, &infoLogLength);

        char* infoLog = (char*)malloc((infoLogLength + 1) * sizeof(char));
        glGetProgramInfoLog(shaderProgramID, infoLogLength, NULL, infoLog);
        infoLog[infoLogLength] = '\0';

        logError("PROGRAM", "failed to link\n%s", infoLog);
        free(infoLog);
        return success;
    }

    logVerbose("PROGRAM", "linked: %u", shaderProgramID);
    return success;
}

static GLint validateShaderProgram(ShaderProgramID shaderProgramID)
{
    glValidateProgram(shaderProgramID);
    
    GLint success = GL_FALSE;
    glGetProgramiv(shaderProgramID, GL_VALIDATE_STATUS, &success);
    
    if (success != GL_TRUE)
    {
        GLsizei infoLogLength = 0;
        glGetProgramiv(shaderProgramID, GL_INFO_LOG_LENGTH, &infoLogLength);

        char* infoLog = (char*)malloc((infoLogLength + 1) * sizeof(char));
        glGetProgramInfoLog(shaderProgramID, infoLogLength, NULL, infoLog);
        infoLog[infoLogLength] = '\0';

        logError("PROGRAM", "failed to validate\n%s", infoLog);
        free(infoLog);
        return success;
    }
    
    logVerbose("PROGRAM", "validated: %u", shaderProgramID);
    return success;
}

static GLint getUniformLocation(ShaderProgramID shaderProgramID, const char* uniform)
{
    const GLint location = glGetUniformLocation(shaderProgramID, uniform);
    assert(location != -1);
    return location;
}

ShaderProgramID shaderProgramCreateC(const char* computeShaderPath)
{
    GLuint computeShader = SHADER_NULL;
    ShaderProgramID shaderProgramID = SHADER_PROGRAM_NULL;

    computeShader = createShader(computeShaderPath, GL_COMPUTE_SHADER);
    if (computeShader == SHADER_NULL) { goto cleanup; }

    shaderProgramID = glCreateProgram();
    attachShader(shaderProgramID, computeShader);

    if (linkShaderProgram(shaderProgramID)     != GL_TRUE) { goto cleanup; }
    if (validateShaderProgram(shaderProgramID) != GL_TRUE) { goto cleanup; }

    detachShader(shaderProgramID, computeShader);
    destroyShader(computeShader);

    logVerbose("PROGRAM", "created: %u", shaderProgramID);
    return shaderProgramID;

cleanup:
    if (computeShader != SHADER_NULL)
    {
        detachShader(shaderProgramID, computeShader);
        destroyShader(computeShader);
    }
    if (shaderProgramID != SHADER_PROGRAM_NULL)
    {
        glDeleteProgram(shaderProgramID);
        shaderProgramID = SHADER_PROGRAM_NULL;
    }

    logVerbose("PROGRAM", "failed to created");
    return shaderProgramID;
}

ShaderProgramID shaderProgramCreateV(const char* vertexShaderPath)
{
    GLuint vertexShader = SHADER_NULL;
    ShaderProgramID shaderProgramID = SHADER_PROGRAM_NULL;

    vertexShader = createShader(vertexShaderPath, GL_VERTEX_SHADER);
    if (vertexShader == SHADER_NULL) { goto cleanup; }

    shaderProgramID = glCreateProgram();
    attachShader(shaderProgramID, vertexShader);

    if (linkShaderProgram(shaderProgramID)     != GL_TRUE) { goto cleanup; }
    if (validateShaderProgram(shaderProgramID) != GL_TRUE) { goto cleanup; }

    detachShader(shaderProgramID, vertexShader);
    destroyShader(vertexShader);

    logVerbose("PROGRAM", "created: %u", shaderProgramID);
    return shaderProgramID;

cleanup:
    if (vertexShader != SHADER_NULL)
    {
        detachShader(shaderProgramID, vertexShader);
        destroyShader(vertexShader);
    }
    if (shaderProgramID != SHADER_PROGRAM_NULL)
    {
        glDeleteProgram(shaderProgramID);
        shaderProgramID = SHADER_PROGRAM_NULL;
    }

    logVerbose("PROGRAM", "failed to created");
    return shaderProgramID;
}

ShaderProgramID shaderProgramCreateVF(
    const char* vertexShaderPath,
    const char* fragmentShaderPath)
{
    GLuint vertexShader = SHADER_NULL;
    GLuint fragmentShader = SHADER_NULL;
    ShaderProgramID shaderProgramID = SHADER_PROGRAM_NULL;

    vertexShader = createShader(vertexShaderPath, GL_VERTEX_SHADER);
    if (vertexShader == SHADER_NULL) { goto cleanup; }
    fragmentShader = createShader(fragmentShaderPath, GL_FRAGMENT_SHADER);
    if (fragmentShader == SHADER_NULL) { goto cleanup; }

    shaderProgramID = glCreateProgram();
    attachShader(shaderProgramID, vertexShader);
    attachShader(shaderProgramID, fragmentShader);

    if (linkShaderProgram(shaderProgramID)     != GL_TRUE) { goto cleanup; }
    if (validateShaderProgram(shaderProgramID) != GL_TRUE) { goto cleanup; }

    detachShader(shaderProgramID, vertexShader);
    destroyShader(vertexShader);
    detachShader(shaderProgramID, fragmentShader);
    destroyShader(fragmentShader);

    logVerbose("PROGRAM", "created: %u", shaderProgramID);
    return shaderProgramID;

cleanup:
    if (vertexShader != SHADER_NULL)
    {
        detachShader(shaderProgramID, vertexShader);
        destroyShader(vertexShader);
    }
    if (fragmentShader != SHADER_NULL)
    {
        detachShader(shaderProgramID, fragmentShader);
        destroyShader(fragmentShader);
    }
    if (shaderProgramID != SHADER_PROGRAM_NULL)
    {
        glDeleteProgram(shaderProgramID);
        shaderProgramID = SHADER_PROGRAM_NULL;
    }

    logVerbose("PROGRAM", "failed to created");
    return shaderProgramID;
}

ShaderProgramID shaderProgramCreateVGF(
    const char* vertexShaderPath,
    const char* geometryShaderPath,
    const char* fragmentShaderPath)
{
    GLuint vertexShader = SHADER_NULL;
    GLuint geometryShader = SHADER_NULL;
    GLuint fragmentShader = SHADER_NULL;
    ShaderProgramID shaderProgramID = SHADER_PROGRAM_NULL;

    vertexShader = createShader(vertexShaderPath, GL_VERTEX_SHADER);
    if (vertexShader == SHADER_NULL) { goto cleanup; }
    geometryShader = createShader(geometryShaderPath, GL_GEOMETRY_SHADER);
    if (geometryShader == SHADER_NULL) { goto cleanup; }
    fragmentShader = createShader(fragmentShaderPath, GL_FRAGMENT_SHADER);
    if (fragmentShader == SHADER_NULL) { goto cleanup; }

    shaderProgramID = glCreateProgram();
    attachShader(shaderProgramID, vertexShader);
    attachShader(shaderProgramID, geometryShader);
    attachShader(shaderProgramID, fragmentShader);

    if (linkShaderProgram(shaderProgramID)     != GL_TRUE) { goto cleanup; }
    if (validateShaderProgram(shaderProgramID) != GL_TRUE) { goto cleanup; }

    detachShader(shaderProgramID, vertexShader);
    destroyShader(vertexShader);
    detachShader(shaderProgramID, geometryShader);
    destroyShader(geometryShader);
    detachShader(shaderProgramID, fragmentShader);
    destroyShader(fragmentShader);

    logVerbose("PROGRAM", "created: %u", shaderProgramID);
    return shaderProgramID;

cleanup:
    if (vertexShader != SHADER_NULL)
    {
        detachShader(shaderProgramID, vertexShader);
        destroyShader(vertexShader);
    }
    if (geometryShader != SHADER_NULL)
    {
        detachShader(shaderProgramID, geometryShader);
        destroyShader(geometryShader);
    }
    if (fragmentShader != SHADER_NULL)
    {
        detachShader(shaderProgramID, fragmentShader);
        destroyShader(fragmentShader);
    }
    if (shaderProgramID != SHADER_PROGRAM_NULL)
    {
        glDeleteProgram(shaderProgramID);
        shaderProgramID = SHADER_PROGRAM_NULL;
    }

    logVerbose("PROGRAM", "failed to created");
    return shaderProgramID;
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
    ShaderProgramID shaderProgramID = SHADER_PROGRAM_NULL;

    vertexShader = createShader(vertexShaderPath, GL_VERTEX_SHADER);
    if (vertexShader == SHADER_NULL) { goto cleanup; }
    tessControlShader = createShader(tessControlShaderPath, GL_TESS_CONTROL_SHADER);
    if (tessControlShader == SHADER_NULL) { goto cleanup; }
    tessEvaluationShader = createShader(tessEvaluationShaderPath, GL_TESS_EVALUATION_SHADER);
    if (tessEvaluationShader == SHADER_NULL) { goto cleanup; }
    fragmentShader = createShader(fragmentShaderPath, GL_FRAGMENT_SHADER);
    if (fragmentShader == SHADER_NULL) { goto cleanup; }

    shaderProgramID = glCreateProgram();
    attachShader(shaderProgramID, vertexShader);
    attachShader(shaderProgramID, tessControlShader);
    attachShader(shaderProgramID, tessEvaluationShader);
    attachShader(shaderProgramID, fragmentShader);

    if (linkShaderProgram(shaderProgramID)     != GL_TRUE) { goto cleanup; }
    if (validateShaderProgram(shaderProgramID) != GL_TRUE) { goto cleanup; }

    detachShader(shaderProgramID, vertexShader);
    destroyShader(vertexShader);
    detachShader(shaderProgramID, tessControlShader);
    destroyShader(tessControlShader);
    detachShader(shaderProgramID, tessEvaluationShader);
    destroyShader(tessEvaluationShader);
    detachShader(shaderProgramID, fragmentShader);
    destroyShader(fragmentShader);

    logVerbose("PROGRAM", "created: %u", shaderProgramID);
    return shaderProgramID;

cleanup:
    if (vertexShader != SHADER_NULL)
    {
        detachShader(shaderProgramID, vertexShader);
        destroyShader(vertexShader);
    }
    if (tessControlShader != SHADER_NULL)
    {
        detachShader(shaderProgramID, tessControlShader);
        destroyShader(tessControlShader);
    }
    if (tessEvaluationShader != SHADER_NULL)
    {
        detachShader(shaderProgramID, tessEvaluationShader);
        destroyShader(tessEvaluationShader);
    }
    if (fragmentShader != SHADER_NULL)
    {
        detachShader(shaderProgramID, fragmentShader);
        destroyShader(fragmentShader);
    }
    if (shaderProgramID != SHADER_PROGRAM_NULL)
    {
        glDeleteProgram(shaderProgramID);
        shaderProgramID = SHADER_PROGRAM_NULL;
    }

    logVerbose("PROGRAM", "failed to created");
    return shaderProgramID;
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
    ShaderProgramID shaderProgramID = SHADER_PROGRAM_NULL;

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

    shaderProgramID = glCreateProgram();
    attachShader(shaderProgramID, vertexShader);
    attachShader(shaderProgramID, tessControlShader);
    attachShader(shaderProgramID, tessEvaluationShader);
    attachShader(shaderProgramID, geometryShader);
    attachShader(shaderProgramID, fragmentShader);

    if (linkShaderProgram(shaderProgramID)     != GL_TRUE) { goto cleanup; }
    if (validateShaderProgram(shaderProgramID) != GL_TRUE) { goto cleanup; }

    detachShader(shaderProgramID, vertexShader);
    destroyShader(vertexShader);
    detachShader(shaderProgramID, tessControlShader);
    destroyShader(tessControlShader);
    detachShader(shaderProgramID, tessEvaluationShader);
    destroyShader(tessEvaluationShader);
    detachShader(shaderProgramID, geometryShader);
    destroyShader(geometryShader);
    detachShader(shaderProgramID, fragmentShader);
    destroyShader(fragmentShader);

    logVerbose("PROGRAM", "created: %u", shaderProgramID);
    return shaderProgramID;

cleanup:
    if (vertexShader != SHADER_NULL)
    {
        detachShader(shaderProgramID, vertexShader);
        destroyShader(vertexShader);
    }
    if (tessControlShader != SHADER_NULL)
    {
        detachShader(shaderProgramID, tessControlShader);
        destroyShader(tessControlShader);
    }
    if (tessEvaluationShader != SHADER_NULL)
    {
        detachShader(shaderProgramID, tessEvaluationShader);
        destroyShader(tessEvaluationShader);
    }
    if (geometryShader != SHADER_NULL)
    {
        detachShader(shaderProgramID, geometryShader);
        destroyShader(geometryShader);
    }
    if (fragmentShader != SHADER_NULL)
    {
        detachShader(shaderProgramID, fragmentShader);
        destroyShader(fragmentShader);
    }
    if (shaderProgramID != SHADER_PROGRAM_NULL)
    {
        glDeleteProgram(shaderProgramID);
        shaderProgramID = SHADER_PROGRAM_NULL;
    }

    logVerbose("PROGRAM", "failed to created");
    return shaderProgramID;
}

void shaderProgramDestroy(ShaderProgramID shaderProgramID)
{
    glDeleteProgram(shaderProgramID);
    logVerbose("PROGRAM", "destroyed: %u", shaderProgramID);
}

bool shaderProgramIsActive(ShaderProgramID shaderProgramID)
{
    return (glIsProgram(shaderProgramID) == GL_TRUE);
}

void shaderProgramBind(ShaderProgramID shaderProgramID)
{
    glUseProgram(shaderProgramID);
    logVerbose("PROGRAM", "binded: %u", shaderProgramID);
}

void shaderProgramSetUniformSampler(ShaderProgramID shaderProgramID, const char* uniform, uint32_t sampler)
{
    glProgramUniform1i(shaderProgramID, getUniformLocation(shaderProgramID, uniform), (GLint)sampler);
}

void shaderProgramSetUniformi(ShaderProgramID shaderProgramID, const char* uniform, int32_t value)
{
    glProgramUniform1i(shaderProgramID, getUniformLocation(shaderProgramID, uniform), value);
}

void shaderProgramSetUniformu(ShaderProgramID shaderProgramID, const char* uniform, uint32_t value)
{
    glProgramUniform1ui(shaderProgramID, getUniformLocation(shaderProgramID, uniform), value);
}

void shaderProgramSetUniformf(ShaderProgramID shaderProgramID, const char* uniform, float value)
{
    glProgramUniform1f(shaderProgramID, getUniformLocation(shaderProgramID, uniform), value);
}

void shaderProgramSetUniform2i(ShaderProgramID shaderProgramID, const char* uniform, ivec2 vector)
{
    glProgramUniform2i(shaderProgramID, getUniformLocation(shaderProgramID, uniform), vector[0], vector[1]);
}

void shaderProgramSetUniform3i(ShaderProgramID shaderProgramID, const char* uniform, ivec3 vector)
{
    glProgramUniform3i(shaderProgramID, getUniformLocation(shaderProgramID, uniform), vector[0], vector[1], vector[2]);
}

void shaderProgramSetUniform4i(ShaderProgramID shaderProgramID, const char* uniform, ivec4 vector)
{
    glProgramUniform4i(shaderProgramID, getUniformLocation(shaderProgramID, uniform), vector[0], vector[1], vector[2], vector[3]);
}

void shaderProgramSetUniform2f(ShaderProgramID shaderProgramID, const char* uniform, vec2 vector)
{
    glProgramUniform2f(shaderProgramID, getUniformLocation(shaderProgramID, uniform), vector[0], vector[1]);
}

void shaderProgramSetUniform3f(ShaderProgramID shaderProgramID, const char* uniform, vec3 vector)
{
    glProgramUniform3f(shaderProgramID, getUniformLocation(shaderProgramID, uniform), vector[0], vector[1], vector[2]);
}

void shaderProgramSetUniform4f(ShaderProgramID shaderProgramID, const char* uniform, vec4 vector)
{
    glProgramUniform4f(shaderProgramID, getUniformLocation(shaderProgramID, uniform), vector[0], vector[1], vector[2], vector[3]);
}

void shaderProgramSetUniformMat2f(ShaderProgramID shaderProgramID, const char* uniform, mat2 matrix)
{
    glProgramUniformMatrix2fv(shaderProgramID, getUniformLocation(shaderProgramID, uniform), 1, GL_FALSE, (float*)matrix);
}

void shaderProgramSetUniformMat2x3f(ShaderProgramID shaderProgramID, const char* uniform, mat2x3 matrix)
{
    glProgramUniformMatrix2x3fv(shaderProgramID, getUniformLocation(shaderProgramID, uniform), 1, GL_FALSE, (float*)matrix);
}

void shaderProgramSetUniformMat2x4f(ShaderProgramID shaderProgramID, const char* uniform, mat2x4 matrix)
{
    glProgramUniformMatrix2x4fv(shaderProgramID, getUniformLocation(shaderProgramID, uniform), 1, GL_FALSE, (float*)matrix);
}

void shaderProgramSetUniformMat3x2f(ShaderProgramID shaderProgramID, const char* uniform, mat3x2 matrix)
{
    glProgramUniformMatrix3x2fv(shaderProgramID, getUniformLocation(shaderProgramID, uniform), 1, GL_FALSE, (float*)matrix);
}

void shaderProgramSetUniformMat3f(ShaderProgramID shaderProgramID, const char* uniform, mat3 matrix)
{
    glProgramUniformMatrix3fv(shaderProgramID, getUniformLocation(shaderProgramID, uniform), 1, GL_FALSE, (float*)matrix);
}

void shaderProgramSetUniformMat3x4f(ShaderProgramID shaderProgramID, const char* uniform, mat3x4 matrix)
{
    glProgramUniformMatrix3x4fv(shaderProgramID, getUniformLocation(shaderProgramID, uniform), 1, GL_FALSE, (float*)matrix);
}

void shaderProgramSetUniformMat4x2f(ShaderProgramID shaderProgramID, const char* uniform, mat4x2 matrix)
{
    glProgramUniformMatrix4x2fv(shaderProgramID, getUniformLocation(shaderProgramID, uniform), 1, GL_FALSE, (float*)matrix);
}

void shaderProgramSetUniformMat4x3f(ShaderProgramID shaderProgramID, const char* uniform, mat4x3 matrix)
{
    glProgramUniformMatrix4x3fv(shaderProgramID, getUniformLocation(shaderProgramID, uniform), 1, GL_FALSE, (float*)matrix);
}

void shaderProgramSetUniformMat4f(ShaderProgramID shaderProgramID, const char* uniform, mat4 matrix)
{
    glProgramUniformMatrix4fv(shaderProgramID, getUniformLocation(shaderProgramID, uniform), 1, GL_FALSE, (float*)matrix);
}

