
#pragma once

#include <GLFW/glfw3.h>

typedef enum
{
    KeyUnknown = GLFW_KEY_UNKNOWN,

    // Letters

    KeyA = GLFW_KEY_A,
    KeyB = GLFW_KEY_B,
    KeyC = GLFW_KEY_C,
    KeyD = GLFW_KEY_D,
    KeyE = GLFW_KEY_E,
    KeyF = GLFW_KEY_F,
    KeyG = GLFW_KEY_G,
    KeyH = GLFW_KEY_H,
    KeyI = GLFW_KEY_I,
    KeyJ = GLFW_KEY_J,
    KeyK = GLFW_KEY_K,
    KeyL = GLFW_KEY_L,
    KeyM = GLFW_KEY_M,
    KeyN = GLFW_KEY_N,
    KeyO = GLFW_KEY_O,
    KeyP = GLFW_KEY_P,
    KeyQ = GLFW_KEY_Q,
    KeyR = GLFW_KEY_R,
    KeyS = GLFW_KEY_S,
    KeyT = GLFW_KEY_T,
    KeyU = GLFW_KEY_U,
    KeyV = GLFW_KEY_V,
    KeyW = GLFW_KEY_W,
    KeyX = GLFW_KEY_X,
    KeyY = GLFW_KEY_Y,
    KeyZ = GLFW_KEY_Z,

    // Numbers (top row)

    KeyNum0 = GLFW_KEY_0,
    KeyNum1 = GLFW_KEY_1,
    KeyNum2 = GLFW_KEY_2,
    KeyNum3 = GLFW_KEY_3,
    KeyNum4 = GLFW_KEY_4,
    KeyNum5 = GLFW_KEY_5,
    KeyNum6 = GLFW_KEY_6,
    KeyNum7 = GLFW_KEY_7,
    KeyNum8 = GLFW_KEY_8,
    KeyNum9 = GLFW_KEY_9,

    // Function keys

    KeyF1  = GLFW_KEY_F1,
    KeyF2  = GLFW_KEY_F2,
    KeyF3  = GLFW_KEY_F3,
    KeyF4  = GLFW_KEY_F4,
    KeyF5  = GLFW_KEY_F5,
    KeyF6  = GLFW_KEY_F6,
    KeyF7  = GLFW_KEY_F7,
    KeyF8  = GLFW_KEY_F8,
    KeyF9  = GLFW_KEY_F9,
    KeyF10 = GLFW_KEY_F10,
    KeyF11 = GLFW_KEY_F11,
    KeyF12 = GLFW_KEY_F12,

    // Special keys

    KeyEscape       = GLFW_KEY_ESCAPE,
    KeyTab          = GLFW_KEY_TAB,
    KeyCapsLock     = GLFW_KEY_CAPS_LOCK,
    KeyShiftLeft    = GLFW_KEY_LEFT_SHIFT,
    KeyShiftRight   = GLFW_KEY_RIGHT_SHIFT,
    KeyControlLeft  = GLFW_KEY_LEFT_CONTROL,
    KeyControlRight = GLFW_KEY_RIGHT_CONTROL,
    KeyAltLeft      = GLFW_KEY_LEFT_ALT,
    KeyAltRight     = GLFW_KEY_RIGHT_ALT,
    KeySpace        = GLFW_KEY_SPACE,
    KeyEnter        = GLFW_KEY_ENTER,
    KeyBackspace    = GLFW_KEY_BACKSPACE,
    KeyInsert       = GLFW_KEY_INSERT,
    KeyDelete       = GLFW_KEY_DELETE,
    KeyHome         = GLFW_KEY_HOME,
    KeyEnd          = GLFW_KEY_END,
    KeyPageUp       = GLFW_KEY_PAGE_UP,
    KeyPageDown     = GLFW_KEY_PAGE_DOWN,
    KeyArrowUp      = GLFW_KEY_UP,
    KeyArrowDown    = GLFW_KEY_DOWN,
    KeyArrowLeft    = GLFW_KEY_LEFT,
    KeyArrowRight   = GLFW_KEY_RIGHT,

    // Punctuation / symbols

    KeyMinus        = GLFW_KEY_MINUS,
    KeyEqual        = GLFW_KEY_EQUAL,
    KeyBracketLeft  = GLFW_KEY_LEFT_BRACKET,
    KeyBracketRight = GLFW_KEY_RIGHT_BRACKET,
    KeyBackslash    = GLFW_KEY_BACKSLASH,
    KeySemicolon    = GLFW_KEY_SEMICOLON,
    KeyApostrophe   = GLFW_KEY_APOSTROPHE,
    KeyComma        = GLFW_KEY_COMMA,
    KeyPeriod       = GLFW_KEY_PERIOD,
    KeySlash        = GLFW_KEY_SLASH,
    KeyGraveAccent  = GLFW_KEY_GRAVE_ACCENT,

    // Numpad

    KeyNumPad0        = GLFW_KEY_KP_0,
    KeyNumPad1        = GLFW_KEY_KP_1,
    KeyNumPad2        = GLFW_KEY_KP_2,
    KeyNumPad3        = GLFW_KEY_KP_3,
    KeyNumPad4        = GLFW_KEY_KP_4,
    KeyNumPad5        = GLFW_KEY_KP_5,
    KeyNumPad6        = GLFW_KEY_KP_6,
    KeyNumPad7        = GLFW_KEY_KP_7,
    KeyNumPad8        = GLFW_KEY_KP_8,
    KeyNumPad9        = GLFW_KEY_KP_9,
    KeyNumPadDecimal  = GLFW_KEY_KP_DECIMAL,
    KeyNumPadDivide   = GLFW_KEY_KP_DIVIDE,
    KeyNumPadMultiply = GLFW_KEY_KP_MULTIPLY,
    KeyNumPadSubtract = GLFW_KEY_KP_SUBTRACT,
    KeyNumPadAdd      = GLFW_KEY_KP_ADD,
    KeyNumPadEnter    = GLFW_KEY_KP_ENTER,
    KeyNumPadEqual    = GLFW_KEY_KP_EQUAL,

    // Lock / misc
    
    KeyNumLock    = GLFW_KEY_NUM_LOCK,
    KeyScrollLock = GLFW_KEY_SCROLL_LOCK,
    KeyPause      = GLFW_KEY_PAUSE,
} Key;

