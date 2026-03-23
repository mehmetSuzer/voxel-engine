
#pragma once

#include <GLFW/glfw3.h>

typedef GLFWvidmode VideoMode;

typedef struct Monitor
{
    GLFWmonitor* handle;
} Monitor;

void HostInit();
void HostTerminate();

double HostGetTime();
void HostSetTime(double time);

void HostPollEvents();
void HostWaitEvents();
void HostWaitEventsTimeout(double timeout);
void HostPostEmptyEvent();

Monitor MonitorGetPrimary();
void MonitorGetAll(Monitor* monitorsOut, int* countOut, int maxCount);
const char* MonitorGetName(Monitor* monitor);
void MonitorGetPosition(Monitor* monitor, int* xOut, int* yOut);
void MonitorGetWorkArea(Monitor* monitor, int* xOut, int* yOut, int* widthOut, int* heightOut);
void MonitorGetPhysicalSize(Monitor* monitor, int* widthMM, int* heightMM);
void MonitorGetContentScale(Monitor* monitor, float* scaleX, float* scaleY);
void MonitorGetVideoModes(Monitor* monitor, VideoMode* videoModesOut, int* countOut, int maxCount);

// ----------------------- OpenGL related -----------------------
typedef void*(*GLFunctionLoader)(const char*);
GLFunctionLoader HostGetGLFunctionLoader();
int HostIsExtensionSupported(const char* extension);
// --------------------------------------------------------------

