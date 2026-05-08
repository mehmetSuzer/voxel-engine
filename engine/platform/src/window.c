
#include <assert.h>
#include <stdlib.h>
#include <GLFW/glfw3.h>
#include "log/log.h"
#include "utils/macros.h"
#include "platform/window.h"

struct Window
{
    GLFWwindow* handle;
    int isFullScreen;
    int windowedPositionX;
    int windowedPositionY;
    int windowedWidth;
    int windowedHeight;
    // ------- OPENGL SPECIFIC ------- //
    int isVSyncEnabled;
    // ------------------------------- //
};

static int windowFlagToCode(WindowFlag windowFlag)
{
    switch (windowFlag)
    {
        case WindowFlagResizable:           return GLFW_RESIZABLE;
        case WindowFlagDecorated:           return GLFW_DECORATED;
        case WindowFlagAlwaysOnTop:         return GLFW_FLOATING;
        case WindowFlagAutoIconified:       return GLFW_AUTO_ICONIFY;
        case WindowFlagFocusedOnShow:       return GLFW_FOCUS_ON_SHOW;
        case WindowFlagMousePassThrough:    return GLFW_MOUSE_PASSTHROUGH;
    }

    logError("WINDOW", "invalid flag");
    assert(0);

    return GLFW_RESIZABLE;
}

static int windowStateToCode(WindowState windowState)
{
    switch (windowState)
    {
        case WindowStateFocused:                    return GLFW_FOCUSED;
        case WindowStateIconified:                  return GLFW_ICONIFIED;
        case WindowStateMaximised:                  return GLFW_MAXIMIZED;
        case WindowStateVisible:                    return GLFW_VISIBLE;
        case WindowStateHovered:                    return GLFW_HOVERED;
        case WindowStateHasTransparentFramebuffer:  return GLFW_TRANSPARENT_FRAMEBUFFER;
    }

    logError("WINDOW", "invalid state");
    assert(0);

    return GLFW_FOCUSED;
}

static int cursorModeToCode(CursorMode cursorMode)
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

static CursorMode cursorModeFromCode(int platformCode)
{
    switch (platformCode)
    {
        case GLFW_CURSOR_NORMAL:        return CursorModeNormal;
        case GLFW_CURSOR_HIDDEN:        return CursorModeHidden;
        case GLFW_CURSOR_DISABLED:      return CursorModeLocked;
        case GLFW_CURSOR_CAPTURED:      return CursorModeCaptured;
        case GLFW_CURSOR_UNAVAILABLE:   return CursorModeUnavailable;
    }

    logError("WINDOW", "invalid cursor mode");
    assert(0);

    return CursorModeNormal;
}

// ------------------------------------------- WINDOW CALLBACKS ------------------------------------------- //

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

static void keyCallback(GLFWwindow* handle, int key, int scancode, int action, int mods)
{
    Window* window = (Window*)glfwGetWindowUserPointer(handle);
    UNUSED(key); UNUSED(scancode); UNUSED(action); UNUSED(mods);
}

static void charCallback(GLFWwindow* handle, unsigned int codepoint)
{
    Window* window = (Window*)glfwGetWindowUserPointer(handle);
    UNUSED(codepoint);
}

static void charModsCallback(GLFWwindow* handle, unsigned int codepoint, int mods)
{
    Window* window = (Window*)glfwGetWindowUserPointer(handle);
    UNUSED(codepoint); UNUSED(mods);
}

static void mouseButtonCallback(GLFWwindow* handle, int button, int action, int mods)
{
    Window* window = (Window*)glfwGetWindowUserPointer(handle);
    UNUSED(button); UNUSED(action); UNUSED(mods);
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

Window* windowCreate(int width, int height, const char* title)
{
    Window* window = (Window*)calloc(1, sizeof(Window));
    window->handle = glfwCreateWindow(width, height, title, NULL, NULL);

    if (window->handle == NULL)
    {
        logError("WINDOW", "failed to create");
        free(window);
        return NULL;
    }
    
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

    windowSetVSync(window, TRUE);
    
    logInfo("WINDOW", "created");
    return window;
}

void windowDestroy(Window* window)
{
    glfwDestroyWindow(window->handle);
    logInfo("WINDOW", "destroyed");
    free(window);
}

void windowShow(Window* window)
{
    glfwShowWindow(window->handle);
    logVerbose("WINDOW", "shown");
}

void windowHide(Window* window)
{
    glfwHideWindow(window->handle);
    logVerbose("WINDOW", "hidden");
}

void windowMaximise(Window* window)
{
    glfwMaximizeWindow(window->handle);
    logVerbose("WINDOW", "maximised");
}

void windowIconify(Window* window)
{
    glfwIconifyWindow(window->handle);
    logVerbose("WINDOW", "iconified");
}

void windowRestore(Window* window)
{
    glfwRestoreWindow(window->handle);
    logVerbose("WINDOW", "restored");
}

void windowSetTitle(Window* window, const char* title)
{
    glfwSetWindowTitle(window->handle, title);
    logVerbose("WINDOW", "title: %s", title);
}

int windowGetFlag(Window* window, WindowFlag windowFlag)
{
    return (glfwGetWindowAttrib(window->handle, windowFlagToCode(windowFlag)) == GLFW_TRUE);
}

void windowSetFlag(Window* window, WindowFlag windowFlag, int enabled)
{
    glfwSetWindowAttrib(window->handle, windowFlagToCode(windowFlag), (enabled) ? GLFW_TRUE : GLFW_FALSE);
    const char* message = 
        (windowFlag == WindowFlagResizable       ) ? "resizable"          :
        (windowFlag == WindowFlagDecorated       ) ? "decorated"          :
        (windowFlag == WindowFlagAlwaysOnTop     ) ? "always-on-top"      :
        (windowFlag == WindowFlagAutoIconified   ) ? "auto-iconified"     :
        (windowFlag == WindowFlagFocusedOnShow   ) ? "focus-on-top"       :
        (windowFlag == WindowFlagMousePassThrough) ? "mouse-pass-through" : "unknown";
    logVerbose("WINDOW", "%s flag is %s", message, (enabled) ? "enabled" : "disabled");
}

int windowGetState(Window* window, WindowState windowState)
{
    return (glfwGetWindowAttrib(window->handle, windowStateToCode(windowState)) == GLFW_TRUE);
}

void windowGetWindowSize(Window* window, int* widthOut, int* heightOut)
{
    glfwGetWindowSize(window->handle, widthOut, heightOut);
}

void windowSetWindowSize(Window* window, int width, int height)
{
    glfwSetWindowSize(window->handle, width, height);
    logVerbose("WINDOW", "size: (%i, %i)", width, height);
}

void windowGetFramebufferSize(Window* window, int* widthOut, int* heightOut)
{
    glfwGetFramebufferSize(window->handle, widthOut, heightOut);
}

void windowGetWindowPosition(Window* window, int* xOut, int* yOut)
{
    glfwGetWindowPos(window->handle, xOut, yOut);
}

void windowSetWindowPosition(Window* window, int x, int y)
{
    glfwSetWindowPos(window->handle, x, y);
    logVerbose("WINDOW", "position: (%i, %i)", x, y);
}

void windowGetContentScale(Window* window, float* xOut, float* yOut)
{
    glfwGetWindowContentScale(window->handle, xOut, yOut);
}

int windowHasNonNativeScale(Window* window)
{
    float xScale = 1.0f;
    float yScale = 1.0f;
    windowGetContentScale(window, &xScale, &yScale);
    return (xScale != 1.0f || yScale != 1.0f);
}

int windowIsFullScreen(Window* window)
{
    return window->isFullScreen;
}

void windowSetFullScreen(Window* window, int enabled)
{
    if (window->isFullScreen == enabled)
    { 
        return;
    }
    
    if (enabled)
    {
        windowGetWindowPosition(window, &window->windowedPositionX, &window->windowedPositionY);
        windowGetWindowSize(window, &window->windowedWidth, &window->windowedHeight);
        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* videoMode = glfwGetVideoMode(monitor);
        glfwSetWindowMonitor(window->handle, monitor, 0, 0, videoMode->width, videoMode->height, videoMode->refreshRate);
    }
    else
    {
        glfwSetWindowMonitor(window->handle, NULL, window->windowedPositionX, window->windowedPositionY, window->windowedWidth, window->windowedHeight, 0);
    }
    window->isFullScreen = enabled;
    logVerbose("WINDOW", "full screen is %s", (enabled) ? "enabled" : "disabled");
}

int windowShouldClose(Window* window)
{
    return glfwWindowShouldClose(window->handle);
}

void windowSetShouldClose(Window* window)
{
    glfwSetWindowShouldClose(window->handle, GLFW_TRUE);
    logVerbose("WINDOW", "closed");
}

int windowIsKeyPressed(Window* window, Key key)
{
    return (glfwGetKey(window->handle, keyToCode(key)) == GLFW_PRESS);
}

int windowIsKeyReleased(Window* window, Key key)
{
    return (glfwGetKey(window->handle, keyToCode(key)) == GLFW_RELEASE);
}

int windowIsMouseButtonPressed(Window* window, MouseButton mouseButton)
{
    return (glfwGetMouseButton(window->handle, mouseButtonToCode(mouseButton)) == GLFW_PRESS);
}

int windowIsMouseButtonReleased(Window* window, MouseButton mouseButton)
{
    return (glfwGetMouseButton(window->handle, mouseButtonToCode(mouseButton)) == GLFW_RELEASE);
}

void windowGetCursorPosition(Window* window, double* xOut, double* yOut)
{
    glfwGetCursorPos(window->handle, xOut, yOut);
}

void windowSetCursorPosition(Window* window, double x, double y)
{
    glfwSetCursorPos(window->handle, x, y);
    logVerbose("CURSOR", "position: (% .6f, % .6f)", x, y);
}

CursorMode windowGetCursorMode(Window* window)
{
    const int glfwCursorMode = glfwGetInputMode(window->handle, GLFW_CURSOR);
    const CursorMode cursorMode = cursorModeFromCode(glfwCursorMode);
    return cursorMode;
}

void windowSetCursorMode(Window* window, CursorMode cursorMode)
{
    if (cursorMode == CursorModeUnavailable) 
    { 
        return;
    }

    glfwSetInputMode(window->handle, GLFW_CURSOR, cursorModeToCode(cursorMode));

    const char* message = 
        (cursorMode == CursorModeNormal  ) ? "normal"   :
        (cursorMode == CursorModeHidden  ) ? "hidden"   :
        (cursorMode == CursorModeLocked  ) ? "locked"   :
        (cursorMode == CursorModeCaptured) ? "captured" : "unknown";
    logVerbose("CURSOR", "%s mode", message);
}

int windowIsStickyKeysEnabled(Window* window)
{
    return (glfwGetInputMode(window->handle, GLFW_STICKY_KEYS) == GLFW_TRUE);
}

void windowEnableStickyKeys(Window* window, int enabled)
{
    glfwSetInputMode(window->handle, GLFW_STICKY_KEYS, (enabled) ? GLFW_TRUE : GLFW_FALSE);
    logVerbose("WINDOW", "sticky keys are %s", (enabled) ? "enabled" : "disabled");
}

int windowIsStickyMouseButtonsEnabled(Window* window)
{
    return (glfwGetInputMode(window->handle, GLFW_STICKY_MOUSE_BUTTONS) == GLFW_TRUE);
}

void windowEnableStickyMouseButtons(Window* window, int enabled)
{
    glfwSetInputMode(window->handle, GLFW_STICKY_MOUSE_BUTTONS, (enabled) ? GLFW_TRUE : GLFW_FALSE);
    logVerbose("WINDOW", "sticky mouse buttons are %s", (enabled) ? "enabled" : "disabled");
}

int windowIsLockKeyModsEnabled(Window* window)
{
    return (glfwGetInputMode(window->handle, GLFW_LOCK_KEY_MODS) == GLFW_TRUE);
}

void windowEnableLockKeyMods(Window* window, int enabled)
{
    glfwSetInputMode(window->handle, GLFW_LOCK_KEY_MODS, (enabled) ? GLFW_TRUE : GLFW_FALSE);
    logVerbose("WINDOW", "lock key mods are %s", (enabled) ? "enabled" : "disabled");
}
    
int windowIsRawMouseMotionEnabled(Window* window)
{
    return (glfwGetInputMode(window->handle, GLFW_RAW_MOUSE_MOTION) == GLFW_TRUE);
}

void windowEnableRawMouseMotion(Window* window, int enabled)
{
    if (glfwRawMouseMotionSupported() != GLFW_TRUE)
    {
        logWarning("WINDOW", "raw mouse motion is not supported");
        return;
    }

    glfwSetInputMode(window->handle, GLFW_RAW_MOUSE_MOTION, (enabled) ? GLFW_TRUE : GLFW_FALSE);
    logVerbose("WINDOW", "raw mouse motion is %s", (enabled) ? "enabled" : "disabled");
}

// ------------------------------------ OPENGL SPECIFIC ------------------------------------ //

void windowMakeContextCurrent(Window* window)
{
    glfwMakeContextCurrent(window->handle);
    logVerbose("WINDOW", "context has changed");
}

int windowIsVSyncEnabled(Window* window)
{
    return window->isVSyncEnabled;
}

void windowSetVSync(Window* window, int enabled)
{
    GLFWwindow* currentWindow = glfwGetCurrentContext();
    glfwMakeContextCurrent(window->handle);
    glfwSwapInterval((enabled) ? 1 : 0);
    window->isVSyncEnabled = enabled;
    glfwMakeContextCurrent(currentWindow);
    logVerbose("WINDOW", "VSync is %s", (enabled) ? "enabled" : "disabled");
}

void windowSwapBuffers(Window* window)
{
    glfwSwapBuffers(window->handle);
}

// ----------------------------------------------------------------------------------------- //

