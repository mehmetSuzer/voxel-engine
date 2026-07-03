
#pragma once

#include "key.h"
#include "mouse.h"

typedef enum WindowFlag
{
    WindowFlagResizable        = 0, // Allows the user to manually adjust the window's dimensions by dragging its borders or corners.
    WindowFlagDecorated        = 1, // Enables standard window borders, title bars, and close/minimize/maximize buttons provided by the operating system.
    WindowFlagAlwaysOnTop      = 2, // Forces the window to stay floating above all other standard application windows even when it loses focus.
    WindowFlagAutoIconified    = 3, // Automatically minimizes the window to the taskbar if a full-screen window on the same monitor loses input focus.
    WindowFlagFocusedOnShow    = 4, // Automatically steals input focus and brings the window to the foreground the moment it transitions to being visible.
    WindowFlagMousePassThrough = 5, // Disables mouse cursor tracking over the window, allowing click events to pass directly to applications beneath it.
    WindowFlagCount,
} WindowFlag;

typedef enum WindowState
{
    WindowStateFocused                   = 0, // Indicates whether the window currently has active keyboard input focus and is receiving user keystrokes.
    WindowStateIconified                 = 1, // Indicates whether the window is currently minimized down to the operating system's taskbar or dock.
    WindowStateMaximised                 = 2, // Indicates whether the window has been expanded to fill the entire usable screen area of the monitor.
    WindowStateVisible                   = 3, // Indicates whether the window is currently unhidden and drawn on screen, regardless of whether it is obscured by other windows.
    WindowStateHovered                   = 4, // Indicates whether the mouse cursor is currently positioned anywhere within the window's client area.
    WindowStateHasTransparentFramebuffer = 5, // Indicates whether the window's underlying pixel buffer supports alpha transparency, allowing the desktop background to show through.
    WindowStateCount,
} WindowState;

typedef enum CursorMode
{
    CursorModeNormal      = 0, // Keeps the cursor fully visible and allows it to move freely across the screen and interact with other applications.
    CursorModeHidden      = 1, // Hides the mouse cursor from view while still allowing it to move freely and leave the window boundaries.
    CursorModeLocked      = 2, // Hides the cursor and locks it to the center of the window, providing infinite relative movement data for first-person camera controls.
    CursorModeCaptured    = 3, // Keeps the cursor visible but confines its movement strictly inside the window borders, ideal for RTS or top-down strategy games.
    CursorModeUnavailable = 4, // Represents an uninitialized or unsupported cursor state, used solely as a read-only error token when querying input configurations.
    CursorModeCount,
} CursorMode;

typedef struct Window Window;

Window* windowCreate(int32_t width, int32_t height, const char* title);

void windowDestroy(Window* window);

void windowMakeContextCurrent(Window* window);

void windowShow(Window* window);
void windowHide(Window* window);

void windowMaximise(Window* window);
void windowIconify(Window* window);
void windowRestore(Window* window);

void windowSetTitle(Window* window, const char* title);

int windowGetFlag(Window* window, WindowFlag windowFlag);
void windowSetFlag(Window* window, WindowFlag windowFlag, bool enabled);

int windowGetState(Window* window, WindowState windowState);

void windowGetWindowSize(Window* window, int32_t* widthOut, int32_t* heightOut);
void windowSetWindowSize(Window* window, int32_t width, int32_t height);

void windowGetFramebufferSize(Window* window, int32_t* widthOut, int32_t* heightOut);

void windowGetWindowPosition(Window* window, int32_t* xOut, int32_t* yOut);
void windowSetWindowPosition(Window* window, int32_t x, int32_t y);

void windowGetContentScale(Window* window, float* xOut, float* yOut);
bool windowHasNonNativeScale(Window* window);

bool windowIsFullScreen(Window* window);
void windowSetFullScreen(Window* window, bool enabled);

bool windowShouldClose(Window* window);
void windowSetShouldClose(Window* window);

bool windowIsKeyPressed(Window* window, Key key);
bool windowIsKeyReleased(Window* window, Key key);

bool windowIsMouseButtonPressed(Window* window, MouseButton mouseButton);
bool windowIsMouseButtonReleased(Window* window, MouseButton mouseButton);

void windowGetCursorPosition(Window* window, double* xOut, double* yOut);
void windowSetCursorPosition(Window* window, double x, double y);

CursorMode windowGetCursorMode(Window* window);
void windowSetCursorMode(Window* window, CursorMode cursorMode);

bool windowIsStickyKeysEnabled(Window* window);
void windowEnableStickyKeys(Window* window, bool enabled);

bool windowIsStickyMouseButtonsEnabled(Window* window);
void windowEnableStickyMouseButtons(Window* window, bool enabled);

bool windowIsLockKeyModsEnabled(Window* window);
void windowEnableLockKeyMods(Window* window, bool enabled);
    
bool windowIsRawMouseMotionEnabled(Window* window);
void windowEnableRawMouseMotion(Window* window, bool enabled);

// ------------------ OPENGL SPECIFIC ------------------ //

void windowMakeContextCurrent(Window* window);
bool windowIsVSyncEnabled(Window* window);
void windowSetVSync(Window* window, bool enabled);
void windowSwapBuffers(Window* window);

// ----------------------------------------------------- //

