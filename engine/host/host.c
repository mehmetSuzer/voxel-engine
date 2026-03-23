
#include <stdlib.h>
#include "log/log.h"
#include "host.h"

static void ErrorCallback(int error, const char* description)
{
    switch (error)
    {
        case GLFW_NOT_INITIALIZED:
            LogError("GLFW", "not initialised: %s", description);
            exit(EXIT_FAILURE);
            break;
        case GLFW_NO_CURRENT_CONTEXT:
            LogError("GLFW", "no current context: %s", description);
            exit(EXIT_FAILURE);
            break;
        case GLFW_NO_WINDOW_CONTEXT:
            LogError("GLFW", "no window context: %s", description);
            exit(EXIT_FAILURE);
            break;
        case GLFW_INVALID_ENUM:
            LogError("GLFW", "invalid enum: %s", description);
            exit(EXIT_FAILURE);
            break;
        case GLFW_INVALID_VALUE:
            LogError("GLFW", "invalid value: %s", description);
            exit(EXIT_FAILURE);
            break;
        case GLFW_OUT_OF_MEMORY:
            LogError("GLFW", "out of memory: %s", description);
            exit(EXIT_FAILURE);
            break;
        case GLFW_API_UNAVAILABLE:
            LogError("GLFW", "API unavailable: %s", description);
            exit(EXIT_FAILURE);
            break;
        case GLFW_VERSION_UNAVAILABLE:
            LogError("GLFW", "version unavailable: %s", description);
            exit(EXIT_FAILURE);
            break;
        case GLFW_FORMAT_UNAVAILABLE:
            LogError("GLFW", "format unavailable: %s", description);
            exit(EXIT_FAILURE);
            break;
        case GLFW_PLATFORM_ERROR:
            LogError("GLFW", "platform error: %s", description);
            exit(EXIT_FAILURE);
            break;
        default:
            LogError("GLFW", "unknown error (%i): %s", error, description);
            exit(EXIT_FAILURE);
            break;
    }
}

static void JoystickCallback(int jid, int event)
{
    const char* joystickName = glfwGetJoystickName(jid);
    const char* state = (event == GLFW_CONNECTED) ? "connected" : "disconnected";
    LogInfo("JOYSTICK", "%s (%i) %s", joystickName, jid, state);
}

static void MonitorCallback(GLFWmonitor* glfwMonitor, int event)
{
    const char* name = glfwGetMonitorName(glfwMonitor);
    const char* state = (event == GLFW_CONNECTED) ? "connected" : "disconnected";
    LogInfo("MONITOR", "%s %s", name, state);
}

void HostInit()
{
    if (!glfwInit())
    {
        LogError("GLFW", "failed to initialise");
        exit(EXIT_FAILURE);
    }

    const int openGLMajor = 3;
    const int openGLMinor = 3;
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, openGLMajor);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, openGLMinor);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
#endif

    // TODO: If you want dynamically resizing viewports, enable GLFW_RESIZABLE
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

    glfwWindowHint(GLFW_RED_BITS, 8);
    glfwWindowHint(GLFW_GREEN_BITS, 8);
    glfwWindowHint(GLFW_BLUE_BITS, 8);
    glfwWindowHint(GLFW_ALPHA_BITS, 8);
    glfwWindowHint(GLFW_DEPTH_BITS, 24);
    glfwWindowHint(GLFW_STENCIL_BITS, 8);
    glfwWindowHint(GLFW_SAMPLES, 0); // MSAA
    glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
    glfwWindowHint(GLFW_SRGB_CAPABLE, GLFW_TRUE);

    glfwSetErrorCallback(ErrorCallback);
    glfwSetJoystickCallback(JoystickCallback);
    glfwSetMonitorCallback(MonitorCallback);

    int glfwMajor = 0;
    int glfwMinor = 0;
    int glfwRevision = 0;
    glfwGetVersion(&glfwMajor, &glfwMinor, &glfwRevision);
    LogInfo("GLFW", "version %i.%i.%i", glfwMajor, glfwMinor, glfwRevision);

    LogInfo("OPENGL", "core %i.%i", openGLMajor, openGLMinor);

    int platform = glfwGetPlatform();
    const char* platformName = 
        (platform == GLFW_PLATFORM_WIN32)   ? "Win32"   : 
        (platform == GLFW_PLATFORM_COCOA)   ? "Cocoa"   : 
        (platform == GLFW_PLATFORM_WAYLAND) ? "Wayland" : 
        (platform == GLFW_PLATFORM_X11)     ? "X11"     : 
        (platform == GLFW_PLATFORM_NULL)    ? "Null"    : "unknown";
    LogInfo("PLATFORM", "%s", platformName);

    GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
    const char* monitorName = glfwGetMonitorName(primaryMonitor);
    LogInfo("MONITOR", "%s detected", monitorName);    

    const GLFWvidmode* videoMode = glfwGetVideoMode(primaryMonitor);
    LogInfo("VIDEO", "%ix%i %i Hz", videoMode->width, videoMode->height, videoMode->refreshRate);
}

void HostTerminate()
{
    glfwTerminate();
    LogVerbose("GLFW", "terminated");
}

double HostGetTime()
{
    return glfwGetTime();
}

void HostSetTime(double time)
{
    glfwSetTime(time);
    LogVerbose("GLFW", "time: % .6f", time);
}

void HostPollEvents()
{
    glfwPollEvents();
}

void HostWaitEvents()
{
    glfwWaitEvents();
}

void HostWaitEventsTimeout(double timeout)
{
    glfwWaitEventsTimeout(timeout);
}

void HostPostEmptyEvent()
{
    glfwPostEmptyEvent();
}

Monitor MonitorGetPrimary()
{
    GLFWmonitor* handle = glfwGetPrimaryMonitor();
    return (Monitor){
        .handle = handle,
    };
}

void MonitorGetAll(Monitor* monitorsOut, int* countOut, int maxCount)
{
    GLFWmonitor** handles = glfwGetMonitors(countOut);
    if (*countOut > maxCount)
    {
        *countOut = maxCount;
    }

    for (int i = 0; i < *countOut; ++i)
    {
        monitorsOut[i] = (Monitor){ .handle = handles[i] };
    }
}

const char* MonitorGetName(Monitor* monitor)
{
    return glfwGetMonitorName(monitor->handle);
}

void MonitorGetPosition(Monitor* monitor, int* xOut, int* yOut)
{
    glfwGetMonitorPos(monitor->handle, xOut, yOut);
}

void MonitorGetWorkArea(Monitor* monitor, int* xOut, int* yOut, int* widthOut, int* heightOut)
{
    glfwGetMonitorWorkarea(monitor->handle, xOut, yOut, widthOut, heightOut);
}

void MonitorGetPhysicalSize(Monitor* monitor, int* widthMM, int* heightMM)
{
    glfwGetMonitorPhysicalSize(monitor->handle, widthMM, heightMM);
}

void MonitorGetContentScale(Monitor* monitor, float* scaleX, float* scaleY)
{
    glfwGetMonitorContentScale(monitor->handle, scaleX, scaleY);
}

void MonitorGetVideoModes(Monitor* monitor, VideoMode* videoModesOut, int* countOut, int maxCount)
{
    const GLFWvidmode* videoModes = glfwGetVideoModes(monitor->handle, countOut);
    if (*countOut > maxCount)
    {
        *countOut = maxCount;
    }

    for (int i = 0; i < *countOut; ++i)
    {
        videoModesOut[i] = videoModes[i];
    }
}

GLFunctionLoader HostGetGLFunctionLoader()
{
    return (GLFunctionLoader)glfwGetProcAddress;
}

int HostIsExtensionSupported(const char* extension)
{
    return (glfwExtensionSupported(extension) == GLFW_TRUE);
}

