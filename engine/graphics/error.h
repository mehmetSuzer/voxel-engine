
#pragma once

void glCheckErrorsInternal(const char* file, int line);

#ifndef NDEBUG
    #define glCheckErrors() glCheckErrorsInternal(__FILE__, __LINE__)
#else
    #define glCheckErrors() ((void)(0))
#endif

