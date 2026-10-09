
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <assert.h>
#include <pthread.h>
#include "log/log.h"

#define TIME_BUFFER_MAX_LENGTH 32U

typedef struct LogState
{
    FILE* file;
    pthread_mutex_t mutex;
    LogSeverity minSeverity;
} LogState;

static LogState logState = {
    .file = NULL,
    .mutex = PTHREAD_MUTEX_INITIALIZER,
    
#ifdef NDEBUG
    .minSeverity = LogSeverityWarning,
#else
    .minSeverity = LogSeverityVerbose,
#endif
};

void logSetMinSeverity(LogSeverity minSeverity)
{
    assert(LogSeverityVerbose <= minSeverity && minSeverity <= LogSeverityError);
    pthread_mutex_lock(&logState.mutex);
    logState.minSeverity = minSeverity;
    pthread_mutex_unlock(&logState.mutex);
}

void logSetLogFile(const char* filename)
{
    pthread_mutex_lock(&logState.mutex);

    if (logState.file != NULL)
    {
        fclose(logState.file);
        logState.file = NULL;
    }

    if (filename == NULL)
    {
        pthread_mutex_unlock(&logState.mutex);
        return;
    }

    logState.file = fopen(filename, "a");
    if (logState.file == NULL)
    {
        pthread_mutex_unlock(&logState.mutex);
        logWarning("LOG", "failed to create/open %s", filename);
        return;
    }

    pthread_mutex_unlock(&logState.mutex);
}

void __logImplementation(LogSeverity severity, const char* __restrict__ category, const char* __restrict__ format, ...)
{
    if (severity < logState.minSeverity)
    {
        return;
    }

    pthread_mutex_lock(&logState.mutex);

    struct timespec timeSinceEpoch = {0};
    timespec_get(&timeSinceEpoch, TIME_UTC);

    struct tm timeFormatted = {0};
#ifdef _WIN32
    localtime_s(&timeFormatted, &timeSinceEpoch.tv_sec);
#else
    localtime_r(&timeSinceEpoch.tv_sec, &timeFormatted);
#endif

    char timeBuffer[TIME_BUFFER_MAX_LENGTH] = {0};
    snprintf(timeBuffer, sizeof(timeBuffer), "%02i:%02i:%02i.%03li",
        timeFormatted.tm_hour,
        timeFormatted.tm_min,
        timeFormatted.tm_sec,
        timeSinceEpoch.tv_nsec / 1000000L);

    const char* severityString = 
        (severity == LogSeverityVerbose) ? "VERBOSE" :
        (severity == LogSeverityInfo)    ? "INFO"    :
        (severity == LogSeverityWarning) ? "WARNING" :
        (severity == LogSeverityError)   ? "ERROR"   : "UNKNOWN";

    char logBuffer[LOG_MAX_LENGTH] = {0};
    const int offset = snprintf(logBuffer, sizeof(logBuffer), "[%s] [%-7s] [%-8s] ", timeBuffer, severityString, category);

    va_list args;
    va_start(args, format);
    vsnprintf(logBuffer + offset, sizeof(logBuffer) - offset, format, args);
    va_end(args);

    printf("%s\n", logBuffer);

    if (logState.file != NULL)
    {
        fprintf(logState.file, "%s\n", logBuffer);
    }

    pthread_mutex_unlock(&logState.mutex);
}

