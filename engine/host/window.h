
#pragma once

#include "key.h"
#include "mouse.h"
#include "joystick.h"
#include "gamepad.h"

typedef enum
{
    WindowFlagResizable        = GLFW_RESIZABLE,
    WindowFlagDecorated        = GLFW_DECORATED,
    WindowFlagAlwaysOnTop      = GLFW_FLOATING,
    WindowFlagAutoIconified    = GLFW_AUTO_ICONIFY,
    WindowFlagFocusedOnShow    = GLFW_FOCUS_ON_SHOW,
    WindowFlagMousePassThrough = GLFW_MOUSE_PASSTHROUGH,
} WindowFlag;

typedef enum
{
    WindowStateFocused                   = GLFW_FOCUSED,
    WindowStateIconified                 = GLFW_ICONIFIED,
    WindowStateMaximised                 = GLFW_MAXIMIZED,
    WindowStateVisible                   = GLFW_VISIBLE,
    WindowStateHovered                   = GLFW_HOVERED,
    WindowStateHasTransparentFramebuffer = GLFW_TRANSPARENT_FRAMEBUFFER,
} WindowState;

typedef enum
{
    CursorModeNormal      = GLFW_CURSOR_NORMAL,      // Visible,   free
    CursorModeHidden      = GLFW_CURSOR_HIDDEN,      // Invisible, free
    CursorModeLocked      = GLFW_CURSOR_DISABLED,    // Invisible, locked
    CursorModeCaptured    = GLFW_CURSOR_CAPTURED,    // Visible,   locked
    CursorModeUnavailable = GLFW_CURSOR_UNAVAILABLE, // Read-only, do not use to set the cursor mode
} CursorMode;

typedef struct Window Window;

Window* WindowCreate(int width, int height, const char* title);

void WindowDelete(Window* window);

void WindowMakeContextCurrent(Window* window);

void WindowShow(Window* window);
void WindowHide(Window* window);

void WindowMaximise(Window* window);
void WindowIconify(Window* window);
void WindowRestore(Window* window);

void WindowSetTitle(Window* window, const char* title);

int WindowGetFlag(Window* window, WindowFlag flag);
void WindowSetFlag(Window* window, WindowFlag flag, int enabled);

int WindowGetState(Window* window, WindowState state);

void WindowGetWindowSize(Window* window, int* widthOut, int* heightOut);
void WindowSetWindowSize(Window* window, int width, int height);

void WindowGetFramebufferSize(Window* window, int* widthOut, int* heightOut);

void WindowGetWindowPosition(Window* window, int* xOut, int* yOut);
void WindowSetWindowPosition(Window* window, int x, int y);

void WindowGetContentScale(Window* window, float* xOut, float* yOut);
int WindowHasNonNativeScale(Window* window);

int WindowIsFullScreen(Window* window);
void WindowSetFullScreen(Window* window, int enabled);

int WindowIsVSyncEnabled(Window* window);
void WindowSetVSync(Window* window, int enabled);

int WindowShouldClose(Window* window);
void WindowSetShouldClose(Window* window);
void WindowSwapBuffers(Window* window);

int WindowIsKeyPressed(Window* window, Key key);
int WindowIsKeyReleased(Window* window, Key key);

int WindowIsMouseButtonPressed(Window* window, MouseButton mouseButton);
int WindowIsMouseButtonReleased(Window* window, MouseButton mouseButton);

void WindowGetCursorPosition(Window* window, double* xOut, double* yOut);
void WindowSetCursorPosition(Window* window, double x, double y);

CursorMode WindowGetCursorMode(Window* window);
void WindowSetCursorMode(Window* window, CursorMode mode);

int WindowIsStickyKeysEnabled(Window* window);
void WindowEnableStickyKeys(Window* window, int enabled);

int WindowIsStickyMouseButtonsEnabled(Window* window);
void WindowEnableStickyMouseButtons(Window* window, int enabled);

int WindowIsLockKeyModsEnabled(Window* window);
void WindowEnableLockKeyMods(Window* window, int enabled);
    
int WindowIsRawMouseMotionEnabled(Window* window);
void WindowEnableRawMouseMotion(Window* window, int enabled);

