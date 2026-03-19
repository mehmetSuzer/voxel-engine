
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
    LogInfo("JOYSTICK", "%s %s", (event == GLFW_CONNECTED) ? "connected" : "disconnected", glfwGetJoystickName(jid));
}

void HostInit()
{
    if (!glfwInit())
    {
        LogError("GLFW", "failed to initialise");
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    LogInfo("GLFW", "OpenGL Core 3.3");

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
#endif

#ifndef NDEBUG
    glfwWindowHint(GLFW_CONTEXT_DEBUG, GLFW_TRUE);
    LogInfo("GLFW", "enabled context debug");
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

Platform HostGetPlatform()
{
    return (Platform)glfwGetPlatform();
}

int HostIsPlatformSupported(Platform platform)
{
    return (glfwPlatformSupported((int)platform) == GLFW_TRUE);
}

void HostGetVersion(int* majorOut, int* minorOut, int* revisionOut)
{
    glfwGetVersion(majorOut, minorOut, revisionOut);
}

const char* HostGetVersionString()
{
    return glfwGetVersionString();
}

GLFWmonitor* HostGetPrimaryMonitor()
{
    return glfwGetPrimaryMonitor();
}

GLFWmonitor** HostGetMonitors(int* count)
{
    return glfwGetMonitors(count);
}

GLFunctionLoader HostGetGLFunctionLoader()
{
    return (GLFunctionLoader)glfwGetProcAddress;
}

int HostIsExtensionSupported(const char* extension)
{
    return (glfwExtensionSupported(extension) == GLFW_TRUE);
}

