
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <pthread.h>
#include "log/log.h"

#ifdef NDEBUG
    static LogSeverity minSeverity = LogSeverityWarning;
#else
    static LogSeverity minSeverity = LogSeverityVerbose;
#endif

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static FILE* file = NULL;

void logSetMinSeverity(LogSeverity severity)
{
    pthread_mutex_lock(&mutex);
    minSeverity = severity;
    pthread_mutex_unlock(&mutex);
}

void logSetLogFile(const char* filename)
{
    pthread_mutex_lock(&mutex);

    if (file != NULL)
    {
        fclose(file);
        file = NULL;
    }

    if (filename == NULL)
    {
        pthread_mutex_unlock(&mutex);
        return;
    }

    file = fopen(filename, "a");
    if (file == NULL)
    {
        pthread_mutex_unlock(&mutex);
        logWarning("LOG", "failed to create/find %s", filename);
        return;
    }

    pthread_mutex_unlock(&mutex);
}

void __logImplementation(LogSeverity severity, const char* __restrict__ category, const char* __restrict__ format, ...)
{
    if (severity < minSeverity)
    {
        return;
    }

    pthread_mutex_lock(&mutex);

    struct timespec ts;
    timespec_get(&ts, TIME_UTC);

    struct tm tm_info;

#ifdef _WIN32
    localtime_s(&tm_info, &ts.tv_sec);
#else
    localtime_r(&ts.tv_sec, &tm_info);
#endif

    char timeBuffer[32] = {0};
    snprintf(timeBuffer, sizeof(timeBuffer), "%02d:%02d:%02d.%03ld",
        tm_info.tm_hour,
        tm_info.tm_min,
        tm_info.tm_sec,
        ts.tv_nsec / 1000000);

    const char* severityStr = 
        (severity == LogSeverityVerbose) ? "VERBOSE" :
        (severity == LogSeverityInfo   ) ? "INFO"    :
        (severity == LogSeverityWarning) ? "WARNING" :
        (severity == LogSeverityError  ) ? "ERROR"   : "UNKNOWN";

    char logBuffer[LOG_MAX_LENGTH] = {0};
    const int offset = snprintf(logBuffer, LOG_MAX_LENGTH, "[%s] [%-7s] [%-8s] ", timeBuffer, severityStr, category);

    va_list args;
    va_start(args, format);
    vsnprintf(logBuffer + offset, LOG_MAX_LENGTH - offset, format, args);
    va_end(args);

    printf("%s\n", logBuffer);

    if (file != NULL)
    {
        fprintf(file, "%s\n", logBuffer);
    }

    pthread_mutex_unlock(&mutex);
}

