
#include <assert.h>
#include <stdlib.h>
#include <GLFW/glfw3.h>
#include "log/log.h"
#include "utils/macros.h"
#include "platform/window.h"

struct Window
{
    GLFWwindow* handle;
    int windowedPositionX;
    int windowedPositionY;
    int windowedWidth;
    int windowedHeight;
    bool isFullScreen;
    
    // ------- OPENGL SPECIFIC ------- //

    bool isVSyncEnabled;

    // ------------------------------- //
};

static int cursorModeToNative(CursorMode cursorMode)
{
    switch (cursorMode)
    {
        case CursorModeNormal:      return GLFW_CURSOR_NORMAL;
        case CursorModeHidden:      return GLFW_CURSOR_HIDDEN;
        case CursorModeLocked:      return GLFW_CURSOR_DISABLED;
        case CursorModeCaptured:    return GLFW_CURSOR_CAPTURED;
        case CursorModeUnavailable: return GLFW_CURSOR_UNAVAILABLE;
    }

    logError("WINDOW", "invalid cursor mode");
    assert(0);

    return GLFW_CURSOR_NORMAL;
}

static CursorMode cursorModeFromNative(int cursorModeNative)
{
    switch (cursorModeNative)
    {
        case GLFW_CURSOR_NORMAL:      return CursorModeNormal;
        case GLFW_CURSOR_HIDDEN:      return CursorModeHidden;
        case GLFW_CURSOR_DISABLED:    return CursorModeLocked;
        case GLFW_CURSOR_CAPTURED:    return CursorModeCaptured;
        case GLFW_CURSOR_UNAVAILABLE: return CursorModeUnavailable;
    }

    logError("WINDOW", "invalid native cursor mode");
    assert(0);

    return CursorModeNormal;
}

// ------------------------------------------- WINDOW CALLBACKS ------------------------------------------ //

static void framebufferSizeCallback(GLFWwindow* handle, int width, int height)
{
    Window* window = (Window*)glfwGetWindowUserPointer(handle);
    UNUSED(width); UNUSED(height);
}

static void windowPositionCallback(GLFWwindow* handle, int xPosition, int yPosition)
{
    Window* window = (Window*)glfwGetWindowUserPointer(handle);
    UNUSED(xPosition); UNUSED(yPosition);
}

static void windowSizeCallback(GLFWwindow* handle, int width, int height)
{
    Window* window = (Window*)glfwGetWindowUserPointer(handle);
    UNUSED(width); UNUSED(height);
}

static void windowCloseCallback(GLFWwindow* handle)
{
    Window* window = (Window*)glfwGetWindowUserPointer(handle);
}

static void windowRefreshCallback(GLFWwindow* handle)
{
    Window* window = (Window*)glfwGetWindowUserPointer(handle);
}

static void windowFocusCallback(GLFWwindow* handle, int focused)
{
    Window* window = (Window*)glfwGetWindowUserPointer(handle);
    UNUSED(focused);
}

static void windowIconifyCallback(GLFWwindow* handle, int iconified)
{
    Window* window = (Window*)glfwGetWindowUserPointer(handle);
    UNUSED(iconified);
}

static void windowMaximiseCallback(GLFWwindow* handle, int maximised)
{
    Window* window = (Window*)glfwGetWindowUserPointer(handle);
    UNUSED(maximised);
}

static void windowContentScaleCallback(GLFWwindow* handle, float xScale, float yScale)
{
    Window* window = (Window*)glfwGetWindowUserPointer(handle);
    UNUSED(xScale); UNUSED(yScale);
}

// ------------------------------------------- INPUT CALLBACKS ------------------------------------------- //

static void keyCallback(GLFWwindow* handle, int keyNative, int scancode, int action, int modifierKeys)
{
    Window* window = (Window*)glfwGetWindowUserPointer(handle);
    UNUSED(keyNative); UNUSED(scancode); UNUSED(action); UNUSED(modifierKeys);
}

static void charCallback(GLFWwindow* handle, unsigned int codepoint)
{
    Window* window = (Window*)glfwGetWindowUserPointer(handle);
    UNUSED(codepoint);
}

static void charModsCallback(GLFWwindow* handle, unsigned int codepoint, int modifierKeys)
{
    Window* window = (Window*)glfwGetWindowUserPointer(handle);
    UNUSED(codepoint); UNUSED(modifierKeys);
}

static void mouseButtonCallback(GLFWwindow* handle, int button, int action, int modifierKeys)
{
    Window* window = (Window*)glfwGetWindowUserPointer(handle);
    UNUSED(button); UNUSED(action); UNUSED(modifierKeys);
}

static void cursorPositionCallback(GLFWwindow* handle, double xPosition, double yPosition)
{
    Window* window = (Window*)glfwGetWindowUserPointer(handle);
    UNUSED(xPosition); UNUSED(yPosition);
}

static void cursorEnterCallback(GLFWwindow* handle, int entered)
{
    Window* window = (Window*)glfwGetWindowUserPointer(handle);
    UNUSED(entered);
}

static void scrollCallback(GLFWwindow* handle, double xOffset, double yOffset)
{
    Window* window = (Window*)glfwGetWindowUserPointer(handle);
    UNUSED(xOffset); UNUSED(yOffset);
}

static void dropCallback(GLFWwindow* handle, int count, const char** paths)
{
    Window* window = (Window*)glfwGetWindowUserPointer(handle);
    UNUSED(count); UNUSED(paths);
}

// ------------------------------------------------------------------------------------------------------- //

Window* windowCreate(uint32_t width, uint32_t height, const char* title)
{
    assert(0 < width && width <= WINDOW_MAX_WIDTH);
    assert(0 < height && height <= WINDOW_MAX_HEIGHT);
    assert(title != NULL);

    Window* window = (Window*)calloc(1, sizeof(Window));
    window->handle = glfwCreateWindow((int)width, (int)height, title, NULL, NULL);

    if (window->handle == NULL)
    {
        logError("WINDOW", "failed to create");
        free(window);
        return NULL;
    }

    window->isFullScreen = false;
    windowSetVSync(window, true);

    glfwGetWindowSize(window->handle, &window->windowedWidth, &window->windowedHeight);
    windowGetWindowPosition(window, &window->windowedPositionX, &window->windowedPositionY);

    glfwSetWindowUserPointer(window->handle, window);

    glfwSetFramebufferSizeCallback(window->handle, framebufferSizeCallback);
    glfwSetWindowPosCallback(window->handle, windowPositionCallback);
    glfwSetWindowSizeCallback(window->handle, windowSizeCallback);
    glfwSetWindowCloseCallback(window->handle, windowCloseCallback);
    glfwSetWindowRefreshCallback(window->handle, windowRefreshCallback);
    glfwSetWindowFocusCallback(window->handle, windowFocusCallback);
    glfwSetWindowIconifyCallback(window->handle, windowIconifyCallback);
    glfwSetWindowMaximizeCallback(window->handle, windowMaximiseCallback);
    glfwSetWindowContentScaleCallback(window->handle, windowContentScaleCallback);

    glfwSetKeyCallback(window->handle, keyCallback);
    glfwSetCharCallback(window->handle, charCallback);
    glfwSetCharModsCallback(window->handle, charModsCallback);
    glfwSetMouseButtonCallback(window->handle, mouseButtonCallback);
    glfwSetCursorPosCallback(window->handle, cursorPositionCallback);
    glfwSetCursorEnterCallback(window->handle, cursorEnterCallback);
    glfwSetScrollCallback(window->handle, scrollCallback);
    glfwSetDropCallback(window->handle, dropCallback);
    
    logInfo("WINDOW", "created");
    return window;
}

void windowDestroy(Window* window)
{
    assert(window != NULL);
    glfwDestroyWindow(window->handle);
    logInfo("WINDOW", "destroyed");
    free(window);
}

void windowShow(Window* window)
{
    assert(window != NULL);
    glfwShowWindow(window->handle);
    logVerbose("WINDOW", "shown");
}

void windowHide(Window* window)
{
    assert(window != NULL);
    glfwHideWindow(window->handle);
    logVerbose("WINDOW", "hidden");
}

void windowMaximise(Window* window)
{
    assert(window != NULL);
    glfwMaximizeWindow(window->handle);
    logVerbose("WINDOW", "maximised");
}

void windowIconify(Window* window)
{
    assert(window != NULL);
    glfwIconifyWindow(window->handle);
    logVerbose("WINDOW", "iconified");
}

void windowRestore(Window* window)
{
    assert(window != NULL);
    glfwRestoreWindow(window->handle);
    logVerbose("WINDOW", "restored");
}

void windowSetTitle(Window* window, const char* title)
{
    assert(window != NULL);
    assert(title != NULL);
    glfwSetWindowTitle(window->handle, title);
    logVerbose("WINDOW", "new title: %s", title);
}

void windowGetWindowSize(Window* window, uint32_t* widthOut, uint32_t* heightOut)
{
    assert(window != NULL);
    int width = 0;
    int height = 0;
    glfwGetWindowSize(window->handle, &width, &height);
    if (widthOut  != NULL) { *widthOut  = (uint32_t)width;  }
    if (heightOut != NULL) { *heightOut = (uint32_t)height; }
}

void windowSetWindowSize(Window* window, uint32_t width, uint32_t height)
{
    assert(window != NULL);
    assert(0 < width && width <= WINDOW_MAX_WIDTH);
    assert(0 < height && height <= WINDOW_MAX_HEIGHT);
    glfwSetWindowSize(window->handle, (int)width, (int)height);
    logVerbose("WINDOW", "new size: (%u, %u)", width, height);
}

void windowGetFramebufferSize(Window* window, uint32_t* widthOut, uint32_t* heightOut)
{
    assert(window != NULL);
    int width = 0;
    int height = 0;
    glfwGetFramebufferSize(window->handle, &width, &height);
    if (widthOut  != NULL) { *widthOut  = (uint32_t)width;  }
    if (heightOut != NULL) { *heightOut = (uint32_t)height; }
}

void windowGetWindowPosition(Window* window, int32_t* xOut, int32_t* yOut)
{
    assert(window != NULL);
    int x = 0;
    int y = 0;
    if (glfwGetPlatform() != GLFW_PLATFORM_WAYLAND)
    {
        glfwGetWindowPos(window->handle, &x, &y);
    }
    if (xOut != NULL) { *xOut = (int32_t)x; }
    if (yOut != NULL) { *yOut = (int32_t)y; }
}

void windowSetWindowPosition(Window* window, int32_t x, int32_t y)
{
    assert(window != NULL);
    glfwSetWindowPos(window->handle, (int)x, (int)y);
    logVerbose("WINDOW", "new position: (%i, %i)", x, y);
}

void windowGetContentScale(Window* window, float* xScaleOut, float* yScaleOut)
{
    assert(window != NULL);
    glfwGetWindowContentScale(window->handle, xScaleOut, yScaleOut);
}

bool windowHasNonNativeScale(Window* window)
{
    assert(window != NULL);
    float xScale = 1.0f;
    float yScale = 1.0f;
    windowGetContentScale(window, &xScale, &yScale);
    return (xScale != 1.0f || yScale != 1.0f);
}

bool windowIsFullScreen(Window* window)
{
    assert(window != NULL);
    return window->isFullScreen;
}

void windowSetFullScreen(Window* window, bool enabled)
{
    assert(window != NULL);
    if (window->isFullScreen == enabled)
    { 
        return;
    }
    
    if (enabled)
    {
        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* videoMode = glfwGetVideoMode(monitor);
        glfwGetWindowSize(window->handle, &window->windowedWidth, &window->windowedHeight);
        windowGetWindowPosition(window, &window->windowedPositionX, &window->windowedPositionY);
        glfwSetWindowMonitor(window->handle, monitor, 0, 0, videoMode->width, videoMode->height, videoMode->refreshRate);
    }
    else
    {
        glfwSetWindowMonitor(
            window->handle, NULL, 
            window->windowedPositionX, 
            window->windowedPositionY, 
            window->windowedWidth, 
            window->windowedHeight, 
            GLFW_DONT_CARE);
    }
    window->isFullScreen = enabled;
    logVerbose("WINDOW", "full screen is %s", (enabled) ? "enabled" : "disabled");
}

bool windowShouldClose(Window* window)
{
    assert(window != NULL);
    return glfwWindowShouldClose(window->handle);
}

void windowSetShouldClose(Window* window)
{
    assert(window != NULL);
    glfwSetWindowShouldClose(window->handle, GLFW_TRUE);
    logVerbose("WINDOW", "closed");
}

bool windowIsKeyPressed(Window* window, Key key)
{
    assert(window != NULL);
    return (glfwGetKey(window->handle, (int)keyToNative(key)) == GLFW_PRESS);
}

bool windowIsKeyReleased(Window* window, Key key)
{
    assert(window != NULL);
    return (glfwGetKey(window->handle, (int)keyToNative(key)) == GLFW_RELEASE);
}

bool windowIsMouseButtonPressed(Window* window, MouseButton mouseButton)
{
    assert(window != NULL);
    return (glfwGetMouseButton(window->handle, (int)mouseButtonToNative(mouseButton)) == GLFW_PRESS);
}

bool windowIsMouseButtonReleased(Window* window, MouseButton mouseButton)
{
    assert(window != NULL);
    return (glfwGetMouseButton(window->handle, (int)mouseButtonToNative(mouseButton)) == GLFW_RELEASE);
}

void windowGetCursorPosition(Window* window, double* xOut, double* yOut)
{
    assert(window != NULL);
    glfwGetCursorPos(window->handle, xOut, yOut);
}

void windowSetCursorPosition(Window* window, double x, double y)
{
    assert(window != NULL);
    glfwSetCursorPos(window->handle, x, y);
    logVerbose("WINDOW", "new cursor position: (% .6f, % .6f)", x, y);
}

CursorMode windowGetCursorMode(Window* window)
{
    assert(window != NULL);
    const int cursorModeNative = glfwGetInputMode(window->handle, GLFW_CURSOR);
    const CursorMode cursorMode = cursorModeFromNative(cursorModeNative);
    return cursorMode;
}

void windowSetCursorMode(Window* window, CursorMode cursorMode)
{
    assert(window != NULL);
    if (cursorMode == CursorModeUnavailable) 
    { 
        return;
    }

    glfwSetInputMode(window->handle, GLFW_CURSOR, cursorModeToNative(cursorMode));

    const char* cursorModeName = 
        (cursorMode == CursorModeNormal  ) ? "normal"   :
        (cursorMode == CursorModeHidden  ) ? "hidden"   :
        (cursorMode == CursorModeLocked  ) ? "locked"   :
        (cursorMode == CursorModeCaptured) ? "captured" : "unknown";
    logVerbose("CURSOR", "%s mode", cursorModeName);
}

bool windowIsStickyKeysEnabled(Window* window)
{
    assert(window != NULL);
    return (glfwGetInputMode(window->handle, GLFW_STICKY_KEYS) == GLFW_TRUE);
}

void windowSetStickyKeys(Window* window, bool enabled)
{
    assert(window != NULL);
    glfwSetInputMode(window->handle, GLFW_STICKY_KEYS, (enabled) ? GLFW_TRUE : GLFW_FALSE);
    logVerbose("WINDOW", "sticky keys are %s", (enabled) ? "enabled" : "disabled");
}

bool windowIsStickyMouseButtonsEnabled(Window* window)
{
    assert(window != NULL);
    return (glfwGetInputMode(window->handle, GLFW_STICKY_MOUSE_BUTTONS) == GLFW_TRUE);
}

void windowSetStickyMouseButtons(Window* window, bool enabled)
{
    assert(window != NULL);
    glfwSetInputMode(window->handle, GLFW_STICKY_MOUSE_BUTTONS, (enabled) ? GLFW_TRUE : GLFW_FALSE);
    logVerbose("WINDOW", "sticky mouse buttons are %s", (enabled) ? "enabled" : "disabled");
}

bool windowIsLockKeyModsEnabled(Window* window)
{
    assert(window != NULL);
    return (glfwGetInputMode(window->handle, GLFW_LOCK_KEY_MODS) == GLFW_TRUE);
}

void windowSetLockKeyMods(Window* window, bool enabled)
{
    assert(window != NULL);
    glfwSetInputMode(window->handle, GLFW_LOCK_KEY_MODS, (enabled) ? GLFW_TRUE : GLFW_FALSE);
    logVerbose("WINDOW", "lock key mods are %s", (enabled) ? "enabled" : "disabled");
}
    
bool windowIsRawMouseMotionEnabled(Window* window)
{
    assert(window != NULL);
    return (glfwGetInputMode(window->handle, GLFW_RAW_MOUSE_MOTION) == GLFW_TRUE);
}

void windowSetRawMouseMotion(Window* window, bool enabled)
{
    assert(window != NULL);
    if (glfwRawMouseMotionSupported() != GLFW_TRUE)
    {
        logWarning("WINDOW", "raw mouse motion is not supported");
        return;
    }

    glfwSetInputMode(window->handle, GLFW_RAW_MOUSE_MOTION, (enabled) ? GLFW_TRUE : GLFW_FALSE);
    logVerbose("WINDOW", "raw mouse motion is %s", (enabled) ? "enabled" : "disabled");
}

// ----------------------------------- WINDOW FRAME & LAYOUT ATTRIBUTES ----------------------------------- //

bool windowIsResizable(Window* window) 
{
    assert(window != NULL);
    return (glfwGetWindowAttrib(window->handle, GLFW_RESIZABLE) == GLFW_TRUE);
}

void windowSetResizable(Window* window, bool enabled)
{
    assert(window != NULL);
    glfwSetWindowAttrib(window->handle, GLFW_RESIZABLE, (enabled) ? GLFW_TRUE : GLFW_FALSE);
    logVerbose("WINDOW", (enabled) ? "resizable now" : "not resizable anymore");
}

bool windowIsDecorated(Window* window)
{
    assert(window != NULL);
    return (glfwGetWindowAttrib(window->handle, GLFW_DECORATED) == GLFW_TRUE);
}

void windowSetDecorated(Window* window, bool enabled)
{
    assert(window != NULL);
    glfwSetWindowAttrib(window->handle, GLFW_DECORATED, (enabled) ? GLFW_TRUE : GLFW_FALSE);
    logVerbose("WINDOW", (enabled) ? "decorated now" : "not decorated anymore");
}

bool windowIsAlwaysOnTop(Window* window)
{
    assert(window != NULL);
    return (glfwGetWindowAttrib(window->handle, GLFW_FLOATING) == GLFW_TRUE);
}

void windowSetAlwaysOnTop(Window* window, bool enabled)
{
    assert(window != NULL);
    glfwSetWindowAttrib(window->handle, GLFW_FLOATING, (enabled) ? GLFW_TRUE : GLFW_FALSE);
    logVerbose("WINDOW", (enabled) ? "always-on-top now" : "not always-on-top anymore");
}

bool windowIsAutoIconified(Window* window)
{
    assert(window != NULL);
    return (glfwGetWindowAttrib(window->handle, GLFW_AUTO_ICONIFY) == GLFW_TRUE);
}

void windowSetAutoIconified(Window* window, bool enabled)
{
    assert(window != NULL);
    glfwSetWindowAttrib(window->handle, GLFW_AUTO_ICONIFY, (enabled) ? GLFW_TRUE : GLFW_FALSE);
    logVerbose("WINDOW", (enabled) ? "auto-iconified now" : "not auto-iconified anymore");
}

bool windowIsFocusedOnShow(Window* window)
{
    assert(window != NULL);
    return (glfwGetWindowAttrib(window->handle, GLFW_FOCUS_ON_SHOW) == GLFW_TRUE);
}

void windowSetFocusedOnShow(Window* window, bool enabled)
{
    assert(window != NULL);
    glfwSetWindowAttrib(window->handle, GLFW_FOCUS_ON_SHOW, (enabled) ? GLFW_TRUE : GLFW_FALSE);
    logVerbose("WINDOW", (enabled) ? "focused-on-show now" : "not focused-on-show anymore");
}

bool windowIsMousePassThrough(Window* window)
{
    assert(window != NULL);
    return (glfwGetWindowAttrib(window->handle, GLFW_MOUSE_PASSTHROUGH) == GLFW_TRUE);
}

void windowSetMousePassThrough(Window* window, bool enabled)
{
    assert(window != NULL);
    glfwSetWindowAttrib(window->handle, GLFW_MOUSE_PASSTHROUGH, (enabled) ? GLFW_TRUE : GLFW_FALSE);
    logVerbose("WINDOW", (enabled) ? "mouse-pass-through now" : "not mouse-pass-through anymore");
}

// ------------------------------------- WINDOW STATE ATTRIBUTES ----------------------------------------- //

bool windowIsFocused(Window* window)
{
    assert(window != NULL);
    return (glfwGetWindowAttrib(window->handle, GLFW_FOCUSED) == GLFW_TRUE);
}

bool windowIsIconified(Window* window)
{
    assert(window != NULL);
    return (glfwGetWindowAttrib(window->handle, GLFW_ICONIFIED) == GLFW_TRUE);
}

bool windowIsMaximised(Window* window)
{
    assert(window != NULL);
    return (glfwGetWindowAttrib(window->handle, GLFW_MAXIMIZED) == GLFW_TRUE);
}

bool windowIsVisible(Window* window)
{
    assert(window != NULL);
    return (glfwGetWindowAttrib(window->handle, GLFW_VISIBLE) == GLFW_TRUE);
}

bool windowIsHovered(Window* window)
{
    assert(window != NULL);
    return (glfwGetWindowAttrib(window->handle, GLFW_HOVERED) == GLFW_TRUE);
}

bool windowHasTransparentFramebuffer(Window* window)
{
    assert(window != NULL);
    return (glfwGetWindowAttrib(window->handle, GLFW_TRANSPARENT_FRAMEBUFFER) == GLFW_TRUE);
}

// ------------------------------------------- OPENGL SPECIFIC ------------------------------------------- //

void windowMakeContextCurrent(Window* window)
{
    assert(window != NULL);
    glfwMakeContextCurrent(window->handle);
    logVerbose("WINDOW", "context has changed");
}

bool windowIsVSyncEnabled(Window* window)
{
    assert(window != NULL);
    return window->isVSyncEnabled;
}

void windowSetVSync(Window* window, bool enabled)
{
    assert(window != NULL);
    GLFWwindow* currentWindow = glfwGetCurrentContext();
    glfwMakeContextCurrent(window->handle);
    glfwSwapInterval((enabled) ? 1 : 0);
    window->isVSyncEnabled = enabled;
    glfwMakeContextCurrent(currentWindow);
    logVerbose("WINDOW", "VSync is %s", (enabled) ? "enabled" : "disabled");
}

void windowSwapBuffers(Window* window)
{
    assert(window != NULL);
    glfwSwapBuffers(window->handle);
}

// ------------------------------------------------------------------------------------------------------- //

