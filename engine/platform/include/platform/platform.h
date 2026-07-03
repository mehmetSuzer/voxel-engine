
#pragma once

#include <stdbool.h>

bool platformInit(void);
void platformTerminate(void);

double platformGetTime(void);
void platformSetTime(double time);

void platformPollEvents(void);
void platformWaitEvents(void);
void platformWaitEventsTimeout(double timeout);
void platformPostEmptyEvent(void);

// --------------------- OPENGL SPECIFIC --------------------- //

typedef void*(*GLFunctionLoader)(const char*);

GLFunctionLoader platformGetGLFunctionLoader(void);
bool platformIsExtensionSupported(const char* extension);

// ----------------------------------------------------------- //

