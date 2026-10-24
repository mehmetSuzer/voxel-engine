
#pragma once

#include <stdbool.h>
#include "key.h"
#include "mouse.h"

#define WINDOW_MAX_WIDTH  3840U
#define WINDOW_MAX_HEIGHT 2160U

typedef enum CursorMode
{
    CursorModeNormal      = 0, // Keeps the cursor fully visible and allows it to move freely across the screen.
    CursorModeHidden      = 1, // Hides the mouse cursor from view while still allowing it to move freely and leave the window boundaries.
    CursorModeLocked      = 2, // Hides the cursor and locks it to the center of the window, providing infinite relative movement data.
    CursorModeCaptured    = 3, // Keeps the cursor visible but confines its movement strictly inside the window borders.
    CursorModeUnavailable = 4, // Represents an uninitialised or unsupported cursor state, used solely as a read-only error token.
} CursorMode;

typedef struct Window Window;

Window* windowCreate(uint32_t width, uint32_t height, const char* title);

void windowDestroy(Window* window);

void windowMakeContextCurrent(Window* window);

void windowShow(Window* window);
void windowHide(Window* window);

void windowMaximise(Window* window);
void windowIconify(Window* window);
void windowRestore(Window* window);

void windowSetTitle(Window* window, const char* title);

void windowGetWindowSize(Window* window, uint32_t* widthOut, uint32_t* heightOut);
void windowSetWindowSize(Window* window, uint32_t width, uint32_t height);

void windowGetFramebufferSize(Window* window, uint32_t* widthOut, uint32_t* heightOut);

void windowGetWindowPosition(Window* window, int32_t* xOut, int32_t* yOut);
void windowSetWindowPosition(Window* window, int32_t x, int32_t y);

void windowGetContentScale(Window* window, float* xScaleOut, float* yScaleOut);
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
void windowSetStickyKeys(Window* window, bool enabled);

bool windowIsStickyMouseButtonsEnabled(Window* window);
void windowSetStickyMouseButtons(Window* window, bool enabled);

bool windowIsLockKeyModsEnabled(Window* window);
void windowSetLockKeyMods(Window* window, bool enabled);
    
bool windowIsRawMouseMotionEnabled(Window* window);
void windowSetRawMouseMotion(Window* window, bool enabled);

// ----------------------------------- WINDOW FRAME & LAYOUT ATTRIBUTES ----------------------------------- //

// Returns whether the user is allowed to manually adjust the window's dimensions by dragging its borders or corners.
bool windowIsResizable(Window* window);
void windowSetResizable(Window* window, bool enabled);

// Returns whether the standard window borders, title bars, and close/minimise/maximise buttons provided by the operating system are enabled.
bool windowIsDecorated(Window* window);
void windowSetDecorated(Window* window, bool enabled);

// Returns whether the window is forced to stay floating above all other standard application windows even when it loses focus.
bool windowIsAlwaysOnTop(Window* window);
void windowSetAlwaysOnTop(Window* window, bool enabled);

// Returns whether the window is automatically minimised to the taskbar if a full-screen window on the same monitor loses input focus.
bool windowIsAutoIconified(Window* window);
void windowSetAutoIconified(Window* window, bool enabled);

// Returns whether the window will automatically acquire focus when shown via windowShow.
bool windowIsFocusedOnShow(Window* window);
void windowSetFocusedOnShow(Window* window, bool enabled);

// Returns whether the window lets mouse inputs pass through to underneath windows/desktop.
bool windowIsMousePassThrough(Window* window);
void windowSetMousePassThrough(Window* window, bool enabled);

// ------------------------------------- WINDOW STATE ATTRIBUTES ----------------------------------------- //

// Returns whether the window currently has active keyboard input focus and is receiving user keystrokes.
bool windowIsFocused(Window* window);
// Returns whether the window is currently minimised down to the operating system's taskbar or dock.
bool windowIsIconified(Window* window);
// Returns whether the window has been expanded to fill the entire usable screen area of the monitor.
bool windowIsMaximised(Window* window);
// Returns whether the window is currently unhidden and drawn on screen, regardless of whether it is obscured by other windows.
bool windowIsVisible(Window* window);
// Returns whether the mouse cursor is currently positioned anywhere within the window's client area.
bool windowIsHovered(Window* window);
// Returns whether the window's underlying pixel buffer supports alpha transparency, allowing the desktop background to show through.
bool windowHasTransparentFramebuffer(Window* window);

// ------------------------------------------- OPENGL SPECIFIC ------------------------------------------- //

void windowMakeContextCurrent(Window* window);
bool windowIsVSyncEnabled(Window* window);
void windowSetVSync(Window* window, bool enabled);
void windowSwapBuffers(Window* window);

// ------------------------------------------------------------------------------------------------------- //

