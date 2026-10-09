
#pragma once

void __glCheckErrorsImplementation(const char* file, int line);

#ifdef NDEBUG
    #define glCheckErrors() ((void)(0))
#else
    #define glCheckErrors() __glCheckErrorsImplementation(__FILE_NAME__, __LINE__)
#endif

