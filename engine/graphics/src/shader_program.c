
#include <assert.h>
#include "log/log.h"
#include "glad/glad.h"
#include "shader_program.h"

/*
static char* readFile("const char* filePath, size_t* sizeOut)
{
    FILE* file = fopen(filePath, "rb");
    if (file == NULL)
    {
        logError("PROGRAM", "failed to read %s", filePath);
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
*/

static GLuint createShader(const char* shaderSource, GLenum shaderType)
{
    if (shaderSource == NULL) { return 0; }

    const char* shaderName = 
        (shaderType == GL_VERTEX_SHADER)          ? "vertex"          :
        (shaderType == GL_TESS_CONTROL_SHADER)    ? "tess control"    :
        (shaderType == GL_TESS_EVALUATION_SHADER) ? "tess evaluation" :
        (shaderType == GL_GEOMETRY_SHADER)        ? "geometry"        :
        (shaderType == GL_FRAGMENT_SHADER)        ? "fragment"        :
        (shaderType == GL_COMPUTE_SHADER)         ? "compute"         : "unknown";

    const GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderSource, NULL);
    glCompileShader(shader);

    GLint success = GL_FALSE;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    
    if (success != GL_TRUE)
    {
        GLsizei infoLogLength = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

        char* infoLog = (char*)malloc((infoLogLength + 1) * sizeof(char));
        glGetShaderInfoLog(shader, infoLogLength, NULL, infoLog);
        infoLog[infoLogLength] = '\0';

        logError("PROGRAM", "failed to compile %s shader:\n%s", shaderName, infoLog);
        free(infoLog);

        glDeleteShader(shader);
        return 0;
    }

    logVerbose("PROGRAM", "compiled %s shader", shaderName);
    return shader;
}

static GLint linkShaderProgram(GLuint shaderProgramID)
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

        return GL_FALSE;
    }

    logVerbose("PROGRAM", "linked: %u", shaderProgramID);
    return GL_TRUE;
}

static GLint validateShaderProgram(GLuint shaderProgramID)
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

        return GL_FALSE;
    }
    
    logVerbose("PROGRAM", "validated: %u", shaderProgramID);
    return GL_TRUE;
}

static GLint getUniformLocation(GLuint shaderProgramID, const char* uniform)
{
    const GLint location = glGetUniformLocation(shaderProgramID, uniform);
    assert(location != -1);
    return location;
}

ShaderProgramID shaderProgramCreateGraphics(
    const char* vertexShaderSource,
    const char* tessControlShaderSource,
    const char* tessEvaluationShaderSource,
    const char* geometryShaderSource,
    const char* fragmentShaderSource)
{
    if (vertexShaderSource == NULL)
    {
        logError("PROGRAM", "vertex shader is missing");
        return SHADER_PROGRAM_NULL;
    }
    if (tessControlShaderSource != NULL && tessEvaluationShaderSource == NULL)
    {
        logError("PROGRAM", "tess control shader is given, but not tess evaluation shader");
        return SHADER_PROGRAM_NULL;
    }
    if (tessControlShaderSource == NULL && tessEvaluationShaderSource != NULL)
    {
        logError("PROGRAM", "tess evaluation shader is given, but not tess control shader");
        return SHADER_PROGRAM_NULL;
    }

    const GLuint shaderProgramID = glCreateProgram();
    if (shaderProgramID == 0)
    {
        logError("PROGRAM", "failed to create shader program object");
        return SHADER_PROGRAM_NULL;
    }

    const GLuint vertShader = createShader(vertexShaderSource, GL_VERTEX_SHADER);
    const GLuint tescShader = createShader(tessControlShaderSource, GL_TESS_CONTROL_SHADER);
    const GLuint teseShader = createShader(tessEvaluationShaderSource, GL_TESS_EVALUATION_SHADER);
    const GLuint geomShader = createShader(geometryShaderSource, GL_GEOMETRY_SHADER);
    const GLuint fragShader = createShader(fragmentShaderSource, GL_FRAGMENT_SHADER);

    if (vertexShaderSource         != NULL && vertShader == 0) { goto cleanup; }
    if (tessControlShaderSource    != NULL && tescShader == 0) { goto cleanup; }
    if (tessEvaluationShaderSource != NULL && teseShader == 0) { goto cleanup; }
    if (geometryShaderSource       != NULL && geomShader == 0) { goto cleanup; }
    if (fragmentShaderSource       != NULL && fragShader == 0) { goto cleanup; }

    if (vertShader != 0) { glAttachShader(shaderProgramID, vertShader); }
    if (tescShader != 0) { glAttachShader(shaderProgramID, tescShader); }
    if (teseShader != 0) { glAttachShader(shaderProgramID, teseShader); }
    if (geomShader != 0) { glAttachShader(shaderProgramID, geomShader); }
    if (fragShader != 0) { glAttachShader(shaderProgramID, fragShader); }

    if (linkShaderProgram(shaderProgramID)     != GL_TRUE) { goto cleanup; }
    if (validateShaderProgram(shaderProgramID) != GL_TRUE) { goto cleanup; }

    if (vertShader != 0) { glDetachShader(shaderProgramID, vertShader); glDeleteShader(vertShader); }
    if (tescShader != 0) { glDetachShader(shaderProgramID, tescShader); glDeleteShader(tescShader); }
    if (teseShader != 0) { glDetachShader(shaderProgramID, teseShader); glDeleteShader(teseShader); }
    if (geomShader != 0) { glDetachShader(shaderProgramID, geomShader); glDeleteShader(geomShader); }
    if (fragShader != 0) { glDetachShader(shaderProgramID, fragShader); glDeleteShader(fragShader); }

    logVerbose("PROGRAM", "created: %u", shaderProgramID);

    return shaderProgramID;

cleanup:
    if (vertShader != 0) { glDeleteShader(vertShader); }
    if (tescShader != 0) { glDeleteShader(tescShader); }
    if (teseShader != 0) { glDeleteShader(teseShader); }
    if (geomShader != 0) { glDeleteShader(geomShader); }
    if (fragShader != 0) { glDeleteShader(fragShader); }

    glDeleteProgram(shaderProgramID);
    logError("PROGRAM", "failed to create shader program");

    return SHADER_PROGRAM_NULL;
}

ShaderProgramID shaderProgramCreateCompute(const char* computeShaderSource)
{
    if (computeShaderSource == NULL)
    {
        logError("PROGRAM", "compute shader is missing");
        return SHADER_PROGRAM_NULL;
    }

    const GLuint shaderProgramID = glCreateProgram();
    if (shaderProgramID == 0)
    {
        logError("PROGRAM", "failed to create shader program object");
        return SHADER_PROGRAM_NULL;
    }

    const GLuint compShader = createShader(computeShaderSource, GL_COMPUTE_SHADER);

    if (computeShaderSource != NULL && compShader == 0) { goto cleanup; }

    glAttachShader(shaderProgramID, compShader);

    if (linkShaderProgram(shaderProgramID)     != GL_TRUE) { goto cleanup; }
    if (validateShaderProgram(shaderProgramID) != GL_TRUE) { goto cleanup; }

    glDetachShader(shaderProgramID, compShader);
    glDeleteShader(compShader);

    logVerbose("PROGRAM", "created: %u", shaderProgramID);

    return shaderProgramID;

cleanup:
    if (compShader != 0) { glDeleteShader(compShader); }

    glDeleteProgram(shaderProgramID);
    logError("PROGRAM", "failed to create shader program");

    return SHADER_PROGRAM_NULL;
}

void shaderProgramDestroy(ShaderProgramID shaderProgramID)
{
    glDeleteProgram(shaderProgramID);
    logVerbose("PROGRAM", "destroyed: %u", shaderProgramID);
}

#ifndef NDEBUG
void shaderProgramSetLabel(ShaderProgramID shaderProgramID, const char* label)
{
    glObjectLabel(GL_PROGRAM, shaderProgramID, (label == NULL) ? 0 : -1, label);
}

void shaderProgramGetLabel(ShaderProgramID shaderProgramID, int32_t maxLabelLength, int32_t* labelLengthOut, char* labelOut)
{
    glGetObjectLabel(GL_PROGRAM, shaderProgramID, maxLabelLength, labelLengthOut, labelOut);
}
#endif

bool shaderProgramIsActive(ShaderProgramID shaderProgramID)
{
    return (glIsProgram(shaderProgramID) == GL_TRUE);
}

void shaderProgramBind(ShaderProgramID shaderProgramID)
{
    glUseProgram(shaderProgramID);
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

void shaderProgramSetUniform2i(ShaderProgramID shaderProgramID, const char* uniform, const ivec2 vector)
{
    glProgramUniform2iv(shaderProgramID, getUniformLocation(shaderProgramID, uniform), 1, vector);
}

void shaderProgramSetUniform3i(ShaderProgramID shaderProgramID, const char* uniform, const ivec3 vector)
{
    glProgramUniform3iv(shaderProgramID, getUniformLocation(shaderProgramID, uniform), 1, vector);
}

void shaderProgramSetUniform4i(ShaderProgramID shaderProgramID, const char* uniform, const ivec4 vector)
{
    glProgramUniform4iv(shaderProgramID, getUniformLocation(shaderProgramID, uniform), 1, vector);
}

void shaderProgramSetUniform2f(ShaderProgramID shaderProgramID, const char* uniform, const vec2 vector)
{
    glProgramUniform2fv(shaderProgramID, getUniformLocation(shaderProgramID, uniform), 1, vector);
}

void shaderProgramSetUniform3f(ShaderProgramID shaderProgramID, const char* uniform, const vec3 vector)
{
    glProgramUniform3fv(shaderProgramID, getUniformLocation(shaderProgramID, uniform), 1, vector);
}

void shaderProgramSetUniform4f(ShaderProgramID shaderProgramID, const char* uniform, const vec4 vector)
{
    glProgramUniform4fv(shaderProgramID, getUniformLocation(shaderProgramID, uniform), 1, vector);
}

void shaderProgramSetUniformMat2f(ShaderProgramID shaderProgramID, const char* uniform, const mat2 matrix)
{
    glProgramUniformMatrix2fv(shaderProgramID, getUniformLocation(shaderProgramID, uniform), 1, GL_FALSE, matrix[0]);
}

void shaderProgramSetUniformMat2x3f(ShaderProgramID shaderProgramID, const char* uniform, const mat2x3 matrix)
{
    glProgramUniformMatrix2x3fv(shaderProgramID, getUniformLocation(shaderProgramID, uniform), 1, GL_FALSE, matrix[0]);
}

void shaderProgramSetUniformMat2x4f(ShaderProgramID shaderProgramID, const char* uniform, const mat2x4 matrix)
{
    glProgramUniformMatrix2x4fv(shaderProgramID, getUniformLocation(shaderProgramID, uniform), 1, GL_FALSE, matrix[0]);
}

void shaderProgramSetUniformMat3x2f(ShaderProgramID shaderProgramID, const char* uniform, const mat3x2 matrix)
{
    glProgramUniformMatrix3x2fv(shaderProgramID, getUniformLocation(shaderProgramID, uniform), 1, GL_FALSE, matrix[0]);
}

void shaderProgramSetUniformMat3f(ShaderProgramID shaderProgramID, const char* uniform, const mat3 matrix)
{
    glProgramUniformMatrix3fv(shaderProgramID, getUniformLocation(shaderProgramID, uniform), 1, GL_FALSE, matrix[0]);
}

void shaderProgramSetUniformMat3x4f(ShaderProgramID shaderProgramID, const char* uniform, const mat3x4 matrix)
{
    glProgramUniformMatrix3x4fv(shaderProgramID, getUniformLocation(shaderProgramID, uniform), 1, GL_FALSE, matrix[0]);
}

void shaderProgramSetUniformMat4x2f(ShaderProgramID shaderProgramID, const char* uniform, const mat4x2 matrix)
{
    glProgramUniformMatrix4x2fv(shaderProgramID, getUniformLocation(shaderProgramID, uniform), 1, GL_FALSE, matrix[0]);
}

void shaderProgramSetUniformMat4x3f(ShaderProgramID shaderProgramID, const char* uniform, const mat4x3 matrix)
{
    glProgramUniformMatrix4x3fv(shaderProgramID, getUniformLocation(shaderProgramID, uniform), 1, GL_FALSE, matrix[0]);
}

void shaderProgramSetUniformMat4f(ShaderProgramID shaderProgramID, const char* uniform, const mat4 matrix)
{
    glProgramUniformMatrix4fv(shaderProgramID, getUniformLocation(shaderProgramID, uniform), 1, GL_FALSE, matrix[0]);
}

