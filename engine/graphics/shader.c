
#include <stdio.h>
#include <stdlib.h>
#include "shader.h"

Shader ShaderCreate(const char* sourcePath, ShaderType type)
{
    FILE* sourceFile = fopen(sourcePath, "rb");
    if (sourceFile == NULL)
    {
        printf("Failed to open shader file %s.\n", sourcePath);
        exit(EXIT_FAILURE);
    }

    fseek(sourceFile, 0, SEEK_END);
    long size = ftell(sourceFile);
    rewind(sourceFile);

    char sourceCode[size+1];
    fread(sourceCode, 1, size, sourceFile);
    sourceCode[size] = '\0';
    fclose(sourceFile);

    Shader shader;
    shader.ID = glCreateShader((GLenum)type);
    const char* sourceCodePtr = (const char*)sourceCode;
    glShaderSource(shader.ID, 1, &sourceCodePtr, NULL);
    glCompileShader(shader.ID);

    GLint success = GL_FALSE;
    glGetShaderiv(shader.ID, GL_COMPILE_STATUS, &success);

    if (success != GL_TRUE)
    {
        GLsizei infoLogLength = 0;
        glGetShaderiv(shader.ID, GL_INFO_LOG_LENGTH, &infoLogLength);

        char infoLog[infoLogLength+1];
        glGetShaderInfoLog(shader.ID, infoLogLength, NULL, infoLog);

        printf("Failed to compile %s.\n%s\n", sourcePath, infoLog);
        exit(EXIT_FAILURE);
    }
    
    return shader;
}

void ShaderDelete(Shader shader)
{
    glDeleteShader(shader.ID);
}

