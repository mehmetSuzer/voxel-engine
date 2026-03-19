
#include <stdio.h>
#include "glad/glad.h"
#include "log/log.h"
#include "error.h"

void glCheckErrorsInternal(const char* file, int line)
{
    GLenum errorCode;
    while ((errorCode = glGetError()) != GL_NO_ERROR)
    {
        const char* error;
        switch (errorCode)
        {
            case GL_INVALID_ENUM:                  error = "Invalid Enum";                  break;
            case GL_INVALID_VALUE:                 error = "Invalid Value";                 break;
            case GL_INVALID_OPERATION:             error = "Invalid Operation";             break;
            case GL_STACK_OVERFLOW:                error = "Stack Overflow";                break;
            case GL_STACK_UNDERFLOW:               error = "Stack Underflow";               break;
            case GL_OUT_OF_MEMORY:                 error = "Out of Memory";                 break;
            case GL_INVALID_FRAMEBUFFER_OPERATION: error = "Invalid Framebuffer Operation"; break;
            case GL_CONTEXT_LOST:                  error = "Context Lost";                  break;
            default:                               error = "Unknown Error";                 break;
        }
        LogError("GL", "%s | %s (%i)", error, file, line);
    }
}

