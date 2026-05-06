
#include <stdio.h>
#include <stdlib.h>
#include "error.h"
#include "shader.h"
#include "log/log.h"

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

Shader shaderCreate(const char* shaderPath, GLenum type)
{
    Shader shader = {
        .ID = SHADER_INVALID_ID,
    };

    char* shaderCode = readFile(shaderPath, NULL);
    if (shaderCode == NULL)
    {
        return shader;
    }

    const GLuint shaderID = glCreateShader(type);
    const char* source = shaderCode;
    glShaderSource(shaderID, 1, &source, NULL);
    glCompileShader(shaderID);
    free(shaderCode);

    GLint success = GL_FALSE;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);

    if (success != GL_TRUE)
    {
        GLsizei infoLogLength = 0;
        glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);

        char* infoLog = (char*)malloc((infoLogLength + 1ul) * sizeof(char));
        glGetShaderInfoLog(shaderID, infoLogLength, NULL, infoLog);
        infoLog[infoLogLength] = '\0';

        logError("SHADER", "failed to compile %s:\n%s", shaderPath, infoLog);
        free(infoLog);

        glDeleteShader(shaderID);
        return shader;
    }
    glCheckErrors();

    logVerbose("SHADER", "%s is compiled", shaderPath);
    shader.ID = shaderID;
    return shader;
}

void shaderDestroy(Shader shader)
{
    glDeleteShader(shader.ID);
}

