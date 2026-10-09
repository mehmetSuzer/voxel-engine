
#pragma once

#define LOG_MAX_LENGTH 256U

typedef enum LogSeverity
{
    LogSeverityVerbose = 0,
    LogSeverityInfo    = 1,
    LogSeverityWarning = 2,
    LogSeverityError   = 3,

    LogSeverityCount,
} LogSeverity;

void logSetMinSeverity(LogSeverity minSeverity);
void logSetLogFile(const char* filename);

void __logImplementation(LogSeverity severity, const char* __restrict__ category, const char* __restrict__ format, ...);

#ifdef NDEBUG
    #define logVerbose(category, format, ...)   ((void)(0))
    #define logInfo(category, format, ...)      ((void)(0))
#else
    #define logVerbose(category, format, ...)   __logImplementation(LogSeverityVerbose, category, format, ##__VA_ARGS__)
    #define logInfo(category, format, ...)      __logImplementation(LogSeverityInfo, category, format, ##__VA_ARGS__)
#endif

#define logWarning(category, format, ...)   __logImplementation(LogSeverityWarning, category, format, ##__VA_ARGS__)
#define logError(category, format, ...)     __logImplementation(LogSeverityError, category, format, ##__VA_ARGS__)

