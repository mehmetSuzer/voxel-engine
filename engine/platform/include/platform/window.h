
#pragma once

#include "key.h"
#include "mouse.h"

typedef enum WindowFlag
{
    WindowFlagResizable        = 0,
    WindowFlagDecorated        = 1,
    WindowFlagAlwaysOnTop      = 2,
    WindowFlagAutoIconified    = 3,
    WindowFlagFocusedOnShow    = 4,
    WindowFlagMousePassThrough = 5,
    WindowFlagCount,
} WindowFlag;

typedef enum WindowState
{
    WindowStateFocused                   = 0,
    WindowStateIconified                 = 1,
    WindowStateMaximised                 = 2,
    WindowStateVisible                   = 3,
    WindowStateHovered                   = 4,
    WindowStateHasTransparentFramebuffer = 5,
    WindowStateCount,
} WindowState;

typedef enum CursorMode
{
    CursorModeNormal      = 0, // Visible,   free
    CursorModeHidden      = 1, // Invisible, free
    CursorModeLocked      = 2, // Invisible, locked
    CursorModeCaptured    = 3, // Visible,   locked
    CursorModeUnavailable = 4, // Read-only, do not use to set the cursor mode
    CursorModeCount,
} CursorMode;

typedef struct Window Window;

Window* windowCreate(int width, int height, const char* title);

void windowDestroy(Window* window);

void windowMakeContextCurrent(Window* window);

void windowShow(Window* window);
void windowHide(Window* window);

void windowMaximise(Window* window);
void windowIconify(Window* window);
void windowRestore(Window* window);

void windowSetTitle(Window* window, const char* title);

int windowGetFlag(Window* window, WindowFlag windowFlag);
void windowSetFlag(Window* window, WindowFlag windowFlag, int enabled);

int windowGetState(Window* window, WindowState windowState);

void windowGetWindowSize(Window* window, int* widthOut, int* heightOut);
void windowSetWindowSize(Window* window, int width, int height);

void windowGetFramebufferSize(Window* window, int* widthOut, int* heightOut);

void windowGetWindowPosition(Window* window, int* xOut, int* yOut);
void windowSetWindowPosition(Window* window, int x, int y);

void windowGetContentScale(Window* window, float* xOut, float* yOut);
int windowHasNonNativeScale(Window* window);

int windowIsFullScreen(Window* window);
void windowSetFullScreen(Window* window, int enabled);

int windowShouldClose(Window* window);
void windowSetShouldClose(Window* window);

int windowIsKeyPressed(Window* window, Key key);
int windowIsKeyReleased(Window* window, Key key);

int windowIsMouseButtonPressed(Window* window, MouseButton mouseButton);
int windowIsMouseButtonReleased(Window* window, MouseButton mouseButton);

void windowGetCursorPosition(Window* window, double* xOut, double* yOut);
void windowSetCursorPosition(Window* window, double x, double y);

CursorMode windowGetCursorMode(Window* window);
void windowSetCursorMode(Window* window, CursorMode cursorMode);

int windowIsStickyKeysEnabled(Window* window);
void windowEnableStickyKeys(Window* window, int enabled);

int windowIsStickyMouseButtonsEnabled(Window* window);
void windowEnableStickyMouseButtons(Window* window, int enabled);

int windowIsLockKeyModsEnabled(Window* window);
void windowEnableLockKeyMods(Window* window, int enabled);
    
int windowIsRawMouseMotionEnabled(Window* window);
void windowEnableRawMouseMotion(Window* window, int enabled);

// ------------------ OPENGL SPECIFIC ------------------ //
void windowMakeContextCurrent(Window* window);
int windowIsVSyncEnabled(Window* window);
void windowSetVSync(Window* window, int enabled);
void windowSwapBuffers(Window* window);
// ----------------------------------------------------- //

