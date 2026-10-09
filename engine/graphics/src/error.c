
#include <assert.h>
#include "error.h"
#include "log/log.h"
#include "glad/glad.h"

void __glCheckErrorsImplementation(const char* file, int line)
{
    GLenum errorNative = GL_NO_ERROR;
    while ((errorNative = glGetError()) != GL_NO_ERROR)
    {
        const char* error =
            (errorNative == GL_INVALID_ENUM)                  ? "invalid enum"                  :
            (errorNative == GL_INVALID_VALUE)                 ? "invalid value"                 :
            (errorNative == GL_INVALID_OPERATION)             ? "invalid operation"             :
            (errorNative == GL_STACK_OVERFLOW)                ? "stack overflow"                :
            (errorNative == GL_STACK_UNDERFLOW)               ? "stack underflow"               :
            (errorNative == GL_OUT_OF_MEMORY)                 ? "out of memory"                 :
            (errorNative == GL_INVALID_FRAMEBUFFER_OPERATION) ? "invalid framebuffer operation" :
            (errorNative == GL_CONTEXT_LOST)                  ? "context lost"                  : "unknown error";

        logError("OPENGL", "%s | %s (%i)", error, file, line);
    }
}

