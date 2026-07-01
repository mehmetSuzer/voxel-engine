
#include <assert.h>
#include "error.h"
#include "log/log.h"
#include "glad/glad.h"

static const char* glErrorToString(GLenum errorCode)
{
    switch (errorCode)
    {
        case GL_INVALID_ENUM:                  return "invalid enum";
        case GL_INVALID_VALUE:                 return "invalid value";
        case GL_INVALID_OPERATION:             return "invalid operation";
        case GL_STACK_OVERFLOW:                return "stack overflow";
        case GL_STACK_UNDERFLOW:               return "stack underflow";
        case GL_OUT_OF_MEMORY:                 return "out of memory";
        case GL_INVALID_FRAMEBUFFER_OPERATION: return "invalid framebuffer operation";
        case GL_CONTEXT_LOST:                  return "context lost";
        default:                               return "unknown error";
    }

    assert(0);

    return "invalid error code";
}

void __glCheckErrorsImplementation(const char* file, int line)
{
    GLenum errorCode;
    while ((errorCode = glGetError()) != GL_NO_ERROR)
    {
        const char* error = glErrorToString(errorCode);
        logError("OPENGL", "%s | %s (%i)", error, file, line);
    }
}

