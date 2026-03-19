
#pragma once

typedef enum LogSeverity
{
    LogSeverityVerbose = 0,
    LogSeverityDebug   = 1,
    LogSeverityInfo    = 2,
    LogSeverityWarning = 3,
    LogSeverityError   = 4,
} LogSeverity;

void LogSetMinSeverity(LogSeverity severity);
void Log(LogSeverity severity, const char* category, const char* __restrict__ format, ...);

#define LogVerbose(category, format, ...) Log(LogSeverityVerbose, category, format, ##__VA_ARGS__)
#define LogDebug(category, format, ...)   Log(LogSeverityDebug, category, format, ##__VA_ARGS__)
#define LogInfo(category, format, ...)    Log(LogSeverityInfo, category, format, ##__VA_ARGS__)
#define LogWarning(category, format, ...) Log(LogSeverityWarning, category, format, ##__VA_ARGS__)
#define LogError(category, format, ...)   Log(LogSeverityError, category, format, ##__VA_ARGS__)

