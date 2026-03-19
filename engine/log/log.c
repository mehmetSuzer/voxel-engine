
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <pthread.h>
#include "log.h"

static LogSeverity minSeverity = LogSeverityInfo;
static pthread_mutex_t logMutex = PTHREAD_MUTEX_INITIALIZER;

void LogSetMinSeverity(LogSeverity severity)
{
    pthread_mutex_lock(&logMutex);
    minSeverity = severity;
    pthread_mutex_unlock(&logMutex);
}

void Log(LogSeverity severity, const char* category, const char* __restrict__ format, ...)
{
    if (severity < minSeverity)
    {
        return;
    }

    pthread_mutex_lock(&logMutex);

    struct timespec ts;
    timespec_get(&ts, TIME_UTC);

    struct tm tm_info;
    localtime_r(&ts.tv_sec, &tm_info);

    char timeBuffer[32];
    snprintf(timeBuffer, sizeof(timeBuffer), "%02d:%02d:%02d.%03ld",
        tm_info.tm_hour,
        tm_info.tm_min,
        tm_info.tm_sec,
        ts.tv_nsec / 1000000);

    const char* severityStr = 
        (severity == LogSeverityVerbose) ? "VERBOSE" :
        (severity == LogSeverityDebug)   ? "DEBUG"   :
        (severity == LogSeverityInfo)    ? "INFO"    :
        (severity == LogSeverityWarning) ? "WARNING" :
        (severity == LogSeverityError)   ? "ERROR"   : "UNKNOWN";

    printf("[%s] [%-7s] [%-8s] ", timeBuffer, severityStr, category);

    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);

    printf("\n");

    pthread_mutex_unlock(&logMutex);
}

