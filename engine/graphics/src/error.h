
#pragma once

#include <stdint.h>

void __glCheckErrorsImplementation(const char* file, uint32_t line);

#ifdef NDEBUG
    #define glCheckErrors() ((void)(0))
#else
    #define glCheckErrors() __glCheckErrorsImplementation(__FILE_NAME__, __LINE__)
#endif

