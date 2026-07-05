
#include <GLFW/glfw3.h>
#include "log/log.h"
#include "platform/platform.h"

static void monitorCallback(GLFWmonitor* monitor, int event)
{
    const char* name = glfwGetMonitorName(monitor);
    const char* state = (event == GLFW_CONNECTED) ? "connected" : "disconnected";
    logInfo("MONITOR", "%s is %s", name, state);
}

static void errorCallback(int error, const char* description)
{
    switch (error)
    {
        case GLFW_NOT_INITIALIZED:      logError("PLATFORM", "not initialised: %s", description);           break;
        case GLFW_NO_CURRENT_CONTEXT:   logError("PLATFORM", "no current context: %s", description);        break;
        case GLFW_NO_WINDOW_CONTEXT:    logError("PLATFORM", "no window context: %s", description);         break;
        case GLFW_INVALID_ENUM:         logError("PLATFORM", "invalid enum: %s", description);              break;
        case GLFW_INVALID_VALUE:        logError("PLATFORM", "invalid value: %s", description);             break;
        case GLFW_OUT_OF_MEMORY:        logError("PLATFORM", "out of memory: %s", description);             break;
        case GLFW_API_UNAVAILABLE:      logError("PLATFORM", "API unavailable: %s", description);           break;
        case GLFW_VERSION_UNAVAILABLE:  logError("PLATFORM", "version unavailable: %s", description);       break;
        case GLFW_FORMAT_UNAVAILABLE:   logError("PLATFORM", "format unavailable: %s", description);        break;
        case GLFW_PLATFORM_ERROR:       logError("PLATFORM", "platform error: %s", description);            break;
        default:                        logError("PLATFORM", "unknown error (%i): %s", error, description); break;
    }
}

bool platformInit(void)
{
    if (!glfwInit())
    {
        logError("PLATFORM", "failed to initialise");
        return false;
    }

    const int openGLMajor = 4;
    const int openGLMinor = 6;
    logInfo("PLATFORM", "OpenGL Core %i.%i", openGLMajor, openGLMinor);

    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, openGLMajor);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, openGLMinor);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
#endif

    glfwWindowHint(GLFW_RED_BITS, 8);
    glfwWindowHint(GLFW_GREEN_BITS, 8);
    glfwWindowHint(GLFW_BLUE_BITS, 8);
    glfwWindowHint(GLFW_ALPHA_BITS, 8);
    glfwWindowHint(GLFW_DEPTH_BITS, 24);
    glfwWindowHint(GLFW_STENCIL_BITS, 8);
    glfwWindowHint(GLFW_SAMPLES, 4); // MSAA
    glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
    glfwWindowHint(GLFW_SRGB_CAPABLE, GLFW_TRUE);

    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);               // Allows the user to resize the window by dragging its edges/corners.
    glfwWindowHint(GLFW_VISIBLE, GLFW_TRUE);                  // Controls whether the window is shown immediately after creation.
    glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);                // Toggles OS window decorations (title bar, borders, close/minimize buttons).
    glfwWindowHint(GLFW_FOCUSED, GLFW_TRUE);                  // Requests that the window receives input focus when created.
    glfwWindowHint(GLFW_AUTO_ICONIFY, GLFW_TRUE);             // Automatically minimizes (iconifies) the window when it loses focus in fullscreen mode.
    glfwWindowHint(GLFW_FLOATING, GLFW_FALSE);                // Makes the window “always on top”.
    glfwWindowHint(GLFW_MAXIMIZED, GLFW_FALSE);               // Controls whether the window starts maximized.
    glfwWindowHint(GLFW_CENTER_CURSOR, GLFW_FALSE);           // Centers the mouse cursor in the window when it is created or shown.
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_FALSE); // Requests an alpha-capable framebuffer that allows window transparency.
    glfwWindowHint(GLFW_FOCUS_ON_SHOW, GLFW_TRUE);            // Gives the window focus when it is shown via glfwShowWindow().
    glfwWindowHint(GLFW_SCALE_TO_MONITOR, GLFW_FALSE);        // Automatically scales the window size based on monitor DPI.
    glfwWindowHint(GLFW_REFRESH_RATE, GLFW_DONT_CARE);        // Let the OS choose the best refresh rate

    glfwSetMonitorCallback(monitorCallback);
    glfwSetErrorCallback(errorCallback);

    int glfwMajor    = 0;
    int glfwMinor    = 0;
    int glfwRevision = 0;
    glfwGetVersion(&glfwMajor, &glfwMinor, &glfwRevision);
    logInfo("PLATFORM", "GLFW %i.%i.%i", glfwMajor, glfwMinor, glfwRevision);

    const int platform = glfwGetPlatform();
    const char* platformName = 
        (platform == GLFW_PLATFORM_WIN32  ) ? "Win32"   : 
        (platform == GLFW_PLATFORM_COCOA  ) ? "Cocoa"   : 
        (platform == GLFW_PLATFORM_WAYLAND) ? "Wayland" : 
        (platform == GLFW_PLATFORM_X11    ) ? "X11"     : 
        (platform == GLFW_PLATFORM_NULL   ) ? "Null"    : "unknown platform";
    logInfo("PLATFORM", "%s is detected", platformName);

    GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
    const char* monitorName = glfwGetMonitorName(primaryMonitor);
    logInfo("PLATFORM", "%s is detected", monitorName);    

    const GLFWvidmode* videoMode = glfwGetVideoMode(primaryMonitor);
    logInfo("PLATFORM", "%ix%i %i Hz", videoMode->width, videoMode->height, videoMode->refreshRate);

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

GLFunctionLoader platformGetGLFunctionLoader(void)
{
    return (GLFunctionLoader)glfwGetProcAddress;
}

bool platformIsExtensionSupported(const char* extension)
{
    return (glfwExtensionSupported(extension) == GLFW_TRUE);
}

