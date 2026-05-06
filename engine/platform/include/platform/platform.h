
#pragma once

void platformInit();
void platformTerminate();

double platformGetTime();
void platformSetTime(double time);

void platformPollEvents();
void platformWaitEvents();
void platformWaitEventsTimeout(double timeout);
void platformPostEmptyEvent();

// --------------------- OPENGL SPECIFIC --------------------- //
typedef void*(*GLFunctionLoader)(const char*);
GLFunctionLoader platformGetGLFunctionLoader();
int platformIsExtensionSupported(const char* extension);
// ----------------------------------------------------------- //

