
#pragma once

#include "window.h"

typedef enum
{
    PlatformWin32   = GLFW_PLATFORM_WIN32, 
    PlatformCocoa   = GLFW_PLATFORM_COCOA, 
    PlatformWayland = GLFW_PLATFORM_WAYLAND, 
    PlatformX11     = GLFW_PLATFORM_X11,
    PlatformNull    = GLFW_PLATFORM_NULL,
} Platform;

void HostInit();
void HostTerminate();

double HostGetTime();
void HostSetTime(double time);

void HostPollEvents();
void HostWaitEvents();
void HostWaitEventsTimeout(double timeout);
void HostPostEmptyEvent();

Platform HostGetPlatform();
int HostIsPlatformSupported(Platform platform);
void HostGetVersion(int* majorOut, int* minorOut, int* revisionOut);
const char* HostGetVersionString();

// TODO: abstract GLFW
GLFWmonitor* HostGetPrimaryMonitor();
GLFWmonitor** HostGetMonitors(int* count);

// ----------------------- OpenGL related -----------------------
typedef void*(*GLFunctionLoader)(const char*);
GLFunctionLoader HostGetGLFunctionLoader();
int HostIsExtensionSupported(const char* extension);
// --------------------------------------------------------------

