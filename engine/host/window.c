
#include <stdlib.h>
#include "log/log.h"
#include "window.h"

#define UNUSED(x) (void)(x)

struct Window
{
    GLFWwindow* handle;
    int isVSyncEnabled;
    int isFullScreen;
    int windowedPositionX;
    int windowedPositionY;
    int windowedWidth;
    int windowedHeight;
};

// ------------------------------------------- WINDOW CALLBACKS ------------------------------------------- //

static void FramebufferSizeCallback(GLFWwindow* handle, int width, int height)
{
    Window* window = (Window*)glfwGetWindowUserPointer(handle);
    UNUSED(width); UNUSED(height);
}

static void WindowPositionCallback(GLFWwindow* handle, int xPosition, int yPosition)
{
    Window* window = (Window*)glfwGetWindowUserPointer(handle);
    UNUSED(xPosition); UNUSED(yPosition);
}

static void WindowSizeCallback(GLFWwindow* handle, int width, int height)
{
    Window* window = (Window*)glfwGetWindowUserPointer(handle);
    UNUSED(width); UNUSED(height);
}

static void WindowCloseCallback(GLFWwindow* handle)
{
    Window* window = (Window*)glfwGetWindowUserPointer(handle);
}

static void WindowRefreshCallback(GLFWwindow* handle)
{
    Window* window = (Window*)glfwGetWindowUserPointer(handle);
}

static void WindowFocusCallback(GLFWwindow* handle, int focused)
{
    Window* window = (Window*)glfwGetWindowUserPointer(handle);
    UNUSED(focused);
}

static void WindowIconifyCallback(GLFWwindow* handle, int iconified)
{
    Window* window = (Window*)glfwGetWindowUserPointer(handle);
    UNUSED(iconified);
}

static void WindowMaximiseCallback(GLFWwindow* handle, int maximised)
{
    Window* window = (Window*)glfwGetWindowUserPointer(handle);
    UNUSED(maximised);
}

static void WindowContentScaleCallback(GLFWwindow* handle, float xScale, float yScale)
{
    Window* window = (Window*)glfwGetWindowUserPointer(handle);
    UNUSED(xScale); UNUSED(yScale);
}

// ------------------------------------------- INPUT CALLBACKS ------------------------------------------- //

static void KeyCallback(GLFWwindow* handle, int key, int scancode, int action, int mods)
{
    Window* window = (Window*)glfwGetWindowUserPointer(handle);
    UNUSED(key); UNUSED(scancode); UNUSED(action); UNUSED(mods);
}

static void CharCallback(GLFWwindow* handle, unsigned int codepoint)
{
    Window* window = (Window*)glfwGetWindowUserPointer(handle);
    UNUSED(codepoint);
}

static void CharModsCallback(GLFWwindow* handle, unsigned int codepoint, int mods)
{
    Window* window = (Window*)glfwGetWindowUserPointer(handle);
    UNUSED(codepoint); UNUSED(mods);
}

static void MouseButtonCallback(GLFWwindow* handle, int button, int action, int mods)
{
    Window* window = (Window*)glfwGetWindowUserPointer(handle);
    UNUSED(button); UNUSED(action); UNUSED(mods);
}

static void CursorPositionCallback(GLFWwindow* handle, double xPosition, double yPosition)
{
    Window* window = (Window*)glfwGetWindowUserPointer(handle);
    UNUSED(xPosition); UNUSED(yPosition);
}

static void CursorEnterCallback(GLFWwindow* handle, int entered)
{
    Window* window = (Window*)glfwGetWindowUserPointer(handle);
    UNUSED(entered);
}

static void ScrollCallback(GLFWwindow* handle, double xOffset, double yOffset)
{
    Window* window = (Window*)glfwGetWindowUserPointer(handle);
    UNUSED(xOffset); UNUSED(yOffset);
}

static void DropCallback(GLFWwindow* handle, int count, const char** paths)
{
    Window* window = (Window*)glfwGetWindowUserPointer(handle);
    UNUSED(count); UNUSED(paths);
}

// ------------------------------------------------------------------------------------------------------- //

static void SetCallbacks(Window* window)
{
    glfwSetWindowUserPointer(window->handle, window);

    glfwSetFramebufferSizeCallback(window->handle, FramebufferSizeCallback);
    glfwSetWindowPosCallback(window->handle, WindowPositionCallback);
    glfwSetWindowSizeCallback(window->handle, WindowSizeCallback);
    glfwSetWindowCloseCallback(window->handle, WindowCloseCallback);
    glfwSetWindowRefreshCallback(window->handle, WindowRefreshCallback);
    glfwSetWindowFocusCallback(window->handle, WindowFocusCallback);
    glfwSetWindowIconifyCallback(window->handle, WindowIconifyCallback);
    glfwSetWindowMaximizeCallback(window->handle, WindowMaximiseCallback);
    glfwSetWindowContentScaleCallback(window->handle, WindowContentScaleCallback);

    glfwSetKeyCallback(window->handle, KeyCallback);
    glfwSetCharCallback(window->handle, CharCallback);
    glfwSetCharModsCallback(window->handle, CharModsCallback);
    glfwSetMouseButtonCallback(window->handle, MouseButtonCallback);
    glfwSetCursorPosCallback(window->handle, CursorPositionCallback);
    glfwSetCursorEnterCallback(window->handle, CursorEnterCallback);
    glfwSetScrollCallback(window->handle, ScrollCallback);
    glfwSetDropCallback(window->handle, DropCallback);
}

Window* WindowCreate(int width, int height, const char* title)
{
    Window* window = (Window*)calloc(1, sizeof(Window));
    window->handle = glfwCreateWindow(width, height, title, NULL, NULL);

    if (window->handle == NULL)
    {
        LogError("WINDOW", "failed to create");
        exit(EXIT_FAILURE);
    }
    
    WindowSetVSync(window, 1);
    SetCallbacks(window);
    LogVerbose("WINDOW", "created");

    return window;
}

void WindowDelete(Window* window)
{
    glfwDestroyWindow(window->handle);
    free(window);
    LogVerbose("WINDOW", "deleted");
}

void WindowMakeContextCurrent(Window* window)
{
    glfwMakeContextCurrent(window->handle);
    LogVerbose("WINDOW", "made context current");
}

void WindowShow(Window* window)
{
    glfwShowWindow(window->handle);
    LogVerbose("WINDOW", "shown");
}

void WindowHide(Window* window)
{
    glfwHideWindow(window->handle);
    LogVerbose("WINDOW", "hidden");
}

void WindowMaximise(Window* window)
{
    glfwMaximizeWindow(window->handle);
    LogVerbose("WINDOW", "maximised");
}

void WindowIconify(Window* window)
{
    glfwIconifyWindow(window->handle);
    LogVerbose("WINDOW", "iconified");
}

void WindowRestore(Window* window)
{
    glfwRestoreWindow(window->handle);
    LogVerbose("WINDOW", "restored");
}

void WindowSetTitle(Window* window, const char* title)
{
    glfwSetWindowTitle(window->handle, title);
    LogVerbose("WINDOW", "title: %s", title);
}

int WindowGetFlag(Window* window, WindowFlag flag)
{
    return (glfwGetWindowAttrib(window->handle, (int)flag) == GLFW_TRUE);
}

void WindowSetFlag(Window* window, WindowFlag flag, int enabled)
{
    glfwSetWindowAttrib(window->handle, (int)flag, (enabled) ? GLFW_TRUE : GLFW_FALSE);
    const char* message = 
        (flag == WindowFlagResizable       ) ? "resizable"          :
        (flag == WindowFlagDecorated       ) ? "decorated"          :
        (flag == WindowFlagAlwaysOnTop     ) ? "always-on-top"      :
        (flag == WindowFlagAutoIconified   ) ? "auto-iconified"     :
        (flag == WindowFlagFocusedOnShow   ) ? "focus-on-top"       :
        (flag == WindowFlagMousePassThrough) ? "mouse-pass-through" : "unknown flag";
    const char* state = (enabled) ? "enabled" : "disabled";
    LogVerbose("WINDOW", "%s %s", message, state);
}

int WindowGetState(Window* window, WindowState state)
{
    return (glfwGetWindowAttrib(window->handle, (int)state) == GLFW_TRUE);
}

void WindowGetWindowSize(Window* window, int* widthOut, int* heightOut)
{
    glfwGetWindowSize(window->handle, widthOut, heightOut);
}

void WindowSetWindowSize(Window* window, int width, int height)
{
    glfwSetWindowSize(window->handle, width, height);
    LogVerbose("WINDOW", "size: (%i, %i)", width, height);
}

void WindowGetFramebufferSize(Window* window, int* widthOut, int* heightOut)
{
    glfwGetFramebufferSize(window->handle, widthOut, heightOut);
}

void WindowGetWindowPosition(Window* window, int* xOut, int* yOut)
{
    glfwGetWindowPos(window->handle, xOut, yOut);
}

void WindowSetWindowPosition(Window* window, int x, int y)
{
    glfwSetWindowPos(window->handle, x, y);
    LogVerbose("WINDOW", "position: (%i, %i)", x, y);
}

void WindowGetContentScale(Window* window, float* xOut, float* yOut)
{
    glfwGetWindowContentScale(window->handle, xOut, yOut);
}

int WindowHasNonNativeScale(Window* window)
{
    float xScale = 1.0f;
    float yScale = 1.0f;
    WindowGetContentScale(window, &xScale, &yScale);
    return (xScale != 1.0f || yScale != 1.0f);
}

int WindowIsFullScreen(Window* window)
{
    return window->isFullScreen;
}

void WindowSetFullScreen(Window* window, int enabled)
{
    if (window->isFullScreen == enabled)
    { 
        return;
    }
    
    if (enabled)
    {
        WindowGetWindowPosition(window, &window->windowedPositionX, &window->windowedPositionY);
        WindowGetWindowSize(window, &window->windowedWidth, &window->windowedHeight);
        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* videoMode = glfwGetVideoMode(monitor);
        glfwSetWindowMonitor(window->handle, monitor, 0, 0, videoMode->width, videoMode->height, videoMode->refreshRate);
    }
    else
    {
        glfwSetWindowMonitor(window->handle, NULL, window->windowedPositionX, window->windowedPositionY, window->windowedWidth, window->windowedHeight, 0);
    }
    window->isFullScreen = enabled;
    LogVerbose("WINDOW", "full screen %s", (enabled) ? "enabled" : "disabled");
}

int WindowIsVSyncEnabled(Window* window)
{
    return window->isVSyncEnabled;
}

void WindowSetVSync(Window* window, int enabled)
{
    GLFWwindow* currentWindow = glfwGetCurrentContext();
    glfwMakeContextCurrent(window->handle);
    glfwSwapInterval((enabled) ? 1 : 0);
    window->isVSyncEnabled = enabled;
    glfwMakeContextCurrent(currentWindow);
    LogVerbose("WINDOW", "vsync %s", (enabled) ? "enabled" : "disabled");
}

int WindowShouldClose(Window* window)
{
    return glfwWindowShouldClose(window->handle);
}

void WindowSetShouldClose(Window* window)
{
    glfwSetWindowShouldClose(window->handle, GLFW_TRUE);
    LogVerbose("WINDOW", "closed");
}

void WindowSwapBuffers(Window* window)
{
    glfwSwapBuffers(window->handle);
}

int WindowIsKeyPressed(Window* window, Key key)
{
    return (glfwGetKey(window->handle, (int)key) == GLFW_PRESS);
}

int WindowIsKeyReleased(Window* window, Key key)
{
    return (glfwGetKey(window->handle, (int)key) == GLFW_RELEASE);
}

int WindowIsMouseButtonPressed(Window* window, MouseButton mouseButton)
{
    return (glfwGetMouseButton(window->handle, (int)mouseButton) == GLFW_PRESS);
}

int WindowIsMouseButtonReleased(Window* window, MouseButton mouseButton)
{
    return (glfwGetMouseButton(window->handle, (int)mouseButton) == GLFW_RELEASE);
}

void WindowGetCursorPosition(Window* window, double* xOut, double* yOut)
{
    glfwGetCursorPos(window->handle, xOut, yOut);
}

void WindowSetCursorPosition(Window* window, double x, double y)
{
    glfwSetCursorPos(window->handle, x, y);
    LogVerbose("CURSOR", "position: (% .6f, % .6f)", x, y);
}

CursorMode WindowGetCursorMode(Window* window)
{
    return (CursorMode)glfwGetInputMode(window->handle, GLFW_CURSOR);
}

void WindowSetCursorMode(Window* window, CursorMode mode)
{
    if (mode == CursorModeUnavailable) 
    { 
        return;
    }
    glfwSetInputMode(window->handle, GLFW_CURSOR, (int)mode);

    const char* message = 
        (mode == CursorModeNormal  ) ? "normal"   :
        (mode == CursorModeHidden  ) ? "hidden"   :
        (mode == CursorModeLocked  ) ? "locked"   :
        (mode == CursorModeCaptured) ? "captured" : "unknown mode";
    LogVerbose("CURSOR", "%s mode", message);
}

int WindowIsStickyKeysEnabled(Window* window)
{
    return (glfwGetInputMode(window->handle, GLFW_STICKY_KEYS) == GLFW_TRUE);
}

void WindowEnableStickyKeys(Window* window, int enabled)
{
    glfwSetInputMode(window->handle, GLFW_STICKY_KEYS, (enabled) ? GLFW_TRUE : GLFW_FALSE);
    LogVerbose("WINDOW", "sticky keys %s", (enabled) ? "enabled" : "disabled");
}

int WindowIsStickyMouseButtonsEnabled(Window* window)
{
    return (glfwGetInputMode(window->handle, GLFW_STICKY_MOUSE_BUTTONS) == GLFW_TRUE);
}

void WindowEnableStickyMouseButtons(Window* window, int enabled)
{
    glfwSetInputMode(window->handle, GLFW_STICKY_MOUSE_BUTTONS, (enabled) ? GLFW_TRUE : GLFW_FALSE);
    LogVerbose("WINDOW", "sticky mouse buttons %s", (enabled) ? "enabled" : "disabled");
}

int WindowIsLockKeyModsEnabled(Window* window)
{
    return (glfwGetInputMode(window->handle, GLFW_LOCK_KEY_MODS) == GLFW_TRUE);
}

void WindowEnableLockKeyMods(Window* window, int enabled)
{
    glfwSetInputMode(window->handle, GLFW_LOCK_KEY_MODS, (enabled) ? GLFW_TRUE : GLFW_FALSE);
    LogVerbose("WINDOW", "lock key mods %s", (enabled) ? "enabled" : "disabled");
}
    
int WindowIsRawMouseMotionEnabled(Window* window)
{
    return (glfwGetInputMode(window->handle, GLFW_RAW_MOUSE_MOTION) == GLFW_TRUE);
}

void WindowEnableRawMouseMotion(Window* window, int enabled)
{
    glfwSetInputMode(window->handle, GLFW_RAW_MOUSE_MOTION, (enabled) ? GLFW_TRUE : GLFW_FALSE);
    LogVerbose("WINDOW", "raw mouse motion %s", (enabled) ? "enabled" : "disabled");
}

