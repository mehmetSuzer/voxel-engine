
#include <GLFW/glfw3.h>
#include "log/log.h"
#include "platform/platform.h"

static void monitorCallback(GLFWmonitor* monitor, int event)
{
    const char* name = glfwGetMonitorName(monitor);
    const char* state = (event == GLFW_CONNECTED) ? "connected" : "disconnected";
    logInfo("PLATFORM", "monitor %s is %s", name, state);
}

static void errorCallback(int error, const char* description)
{
    switch (error)
    {
        case GLFW_NOT_INITIALIZED:       logError("PLATFORM", "not initialised: %s", description);           break;
        case GLFW_NO_CURRENT_CONTEXT:    logError("PLATFORM", "no current context: %s", description);        break;
        case GLFW_INVALID_ENUM:          logError("PLATFORM", "invalid enum: %s", description);              break;
        case GLFW_INVALID_VALUE:         logError("PLATFORM", "invalid value: %s", description);             break;
        case GLFW_OUT_OF_MEMORY:         logError("PLATFORM", "out of memory: %s", description);             break;
        case GLFW_API_UNAVAILABLE:       logError("PLATFORM", "API unavailable: %s", description);           break;
        case GLFW_VERSION_UNAVAILABLE:   logError("PLATFORM", "version unavailable: %s", description);       break;
        case GLFW_PLATFORM_ERROR:        logError("PLATFORM", "platform error: %s", description);            break;
        case GLFW_FORMAT_UNAVAILABLE:    logError("PLATFORM", "format unavailable: %s", description);        break;
        case GLFW_NO_WINDOW_CONTEXT:     logError("PLATFORM", "no window context: %s", description);         break;
        case GLFW_CURSOR_UNAVAILABLE:    logError("PLATFORM", "cursor unavailable: %s", description);        break;
        case GLFW_FEATURE_UNAVAILABLE:   logError("PLATFORM", "feature unavailable: %s", description);       break;
        case GLFW_FEATURE_UNIMPLEMENTED: logError("PLATFORM", "feature unimplemented: %s", description);     break;
        case GLFW_PLATFORM_UNAVAILABLE:  logError("PLATFORM", "platform unavailable: %s", description);      break;
        default:                         logError("PLATFORM", "unknown error (%i): %s", error, description); break;
    }
}

bool platformInit(void)
{
    if (!glfwInit())
    {
        logError("PLATFORM", "failed to initialise");
        return false;
    }

    const int openGLVersionMajor = 4;
    const int openGLVersionMinor = 6;
    logInfo("PLATFORM", "OpenGL Core %i.%i", openGLVersionMajor, openGLVersionMinor);

    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, openGLVersionMajor);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, openGLVersionMinor);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
#endif

    const int MSAASampleCount = 4;
    glfwWindowHint(GLFW_RED_BITS, 8);
    glfwWindowHint(GLFW_GREEN_BITS, 8);
    glfwWindowHint(GLFW_BLUE_BITS, 8);
    glfwWindowHint(GLFW_ALPHA_BITS, 8);
    glfwWindowHint(GLFW_DEPTH_BITS, 24);
    glfwWindowHint(GLFW_STENCIL_BITS, 8);
    glfwWindowHint(GLFW_SAMPLES, MSAASampleCount);
    glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
    glfwWindowHint(GLFW_SRGB_CAPABLE, GLFW_TRUE);

#ifdef NDEBUG
    glfwWindowHint(GLFW_CONTEXT_NO_ERROR, GLFW_TRUE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_FALSE);
#else
    glfwWindowHint(GLFW_CONTEXT_NO_ERROR, GLFW_FALSE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#endif

    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);               // Allows the user to resize the window by dragging its edges/corners.
    glfwWindowHint(GLFW_VISIBLE, GLFW_TRUE);                  // Controls whether the window is shown immediately after creation.
    glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);                // Toggles OS window decorations (title bar, borders, close/minimise buttons).
    glfwWindowHint(GLFW_FOCUSED, GLFW_TRUE);                  // Requests that the window receives input focus when created.
    glfwWindowHint(GLFW_AUTO_ICONIFY, GLFW_TRUE);             // Automatically minimises (iconifies) the window when it loses focus in fullscreen mode.
    glfwWindowHint(GLFW_FLOATING, GLFW_FALSE);                // Makes the window “always on top”.
    glfwWindowHint(GLFW_MAXIMIZED, GLFW_FALSE);               // Controls whether the window starts maximised.
    glfwWindowHint(GLFW_CENTER_CURSOR, GLFW_FALSE);           // Centers the mouse cursor in the window when it is created or shown.
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_FALSE); // Requests an alpha-capable framebuffer that allows window transparency.
    glfwWindowHint(GLFW_FOCUS_ON_SHOW, GLFW_TRUE);            // Gives the window focus when it is shown via glfwShowWindow().
    glfwWindowHint(GLFW_SCALE_TO_MONITOR, GLFW_FALSE);        // Automatically scales the window size based on monitor DPI.
    glfwWindowHint(GLFW_REFRESH_RATE, GLFW_DONT_CARE);        // Lets the OS choose the best refresh rate.

    glfwSetMonitorCallback(monitorCallback);
    glfwSetErrorCallback(errorCallback);

    int glfwVersionMajor    = 0;
    int glfwVersionMinor    = 0;
    int glfwVersionRevision = 0;
    glfwGetVersion(&glfwVersionMajor, &glfwVersionMinor, &glfwVersionRevision);
    logInfo("PLATFORM", "GLFW %i.%i.%i", glfwVersionMajor, glfwVersionMinor, glfwVersionRevision);

    const int platformNative = glfwGetPlatform();
    const char* platform = 
        (platformNative == GLFW_PLATFORM_WIN32)   ? "Win32"   : 
        (platformNative == GLFW_PLATFORM_COCOA)   ? "Cocoa"   : 
        (platformNative == GLFW_PLATFORM_WAYLAND) ? "Wayland" : 
        (platformNative == GLFW_PLATFORM_X11)     ? "X11"     : 
        (platformNative == GLFW_PLATFORM_NULL)    ? "Null"    : "unknown";
    logInfo("PLATFORM", "platform is %s", platform);

    GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
    const char* monitorName = glfwGetMonitorName(primaryMonitor);
    logInfo("PLATFORM", "primary monitor is %s", monitorName);    

    const GLFWvidmode* videoMode = glfwGetVideoMode(primaryMonitor);
    logInfo("PLATFORM", "video mode is %ix%i %i Hz", videoMode->width, videoMode->height, videoMode->refreshRate);

    logInfo("PLATFORM", "initialised");
    return true;
}

void platformTerminate(void)
{
    glfwTerminate();
    logInfo("PLATFORM", "terminated");
}

double platformGetTime(void)
{
    return glfwGetTime();
}

void platformSetTime(double time)
{
    glfwSetTime(time);
    logVerbose("PLATFORM", "time is set to % .6f", time);
}

void platformPollEvents(void)
{
    glfwPollEvents();
}

void platformWaitEvents(void)
{
    glfwWaitEvents();
}

void platformWaitEventsTimeout(double timeout)
{
    glfwWaitEventsTimeout(timeout);
}

void platformPostEmptyEvent(void)
{
    glfwPostEmptyEvent();
}

OpenGLFunctionLoader platformGetOpenGLFunctionLoader(void)
{
    return (OpenGLFunctionLoader)glfwGetProcAddress;
}

bool platformIsExtensionSupported(const char* extension)
{
    return (glfwExtensionSupported(extension) == GLFW_TRUE);
}

