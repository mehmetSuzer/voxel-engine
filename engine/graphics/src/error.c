
#include <assert.h>
#include "error.h"
#include "log/log.h"
#include "glad/glad.h"

static const char* errorStringFromNative(GLenum error)
{
    switch (error)
    {
        case GL_INVALID_ENUM:                  return "invalid enum";
        case GL_INVALID_VALUE:                 return "invalid value";
        case GL_INVALID_OPERATION:             return "invalid operation";
        case GL_STACK_OVERFLOW:                return "stack overflow";
        case GL_STACK_UNDERFLOW:               return "stack underflow";
        case GL_OUT_OF_MEMORY:                 return "out of memory";
        case GL_INVALID_FRAMEBUFFER_OPERATION: return "invalid framebuffer operation";
        case GL_CONTEXT_LOST:                  return "context lost";
    }

    assert(0);

    return "invalid error";
}

void __glCheckErrorsImplementation(const char* file, uint32_t line)
{
    GLenum error = GL_NO_ERROR;
    while ((error = glGetError()) != GL_NO_ERROR)
    {
        const char* errorString = errorStringFromNative(error);
        logError("OPENGL", "%s | %s (%u)", errorString, file, line);
    }
}

