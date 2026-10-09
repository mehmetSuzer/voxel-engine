
#pragma once

#include <stdint.h>

typedef enum Key
{
    KeyUnknown = -1,

    // Letter keys

    KeyA =  0,
    KeyB =  1,
    KeyC =  2,
    KeyD =  3,
    KeyE =  4,
    KeyF =  5,
    KeyG =  6,
    KeyH =  7,
    KeyI =  8,
    KeyJ =  9,
    KeyK = 10,
    KeyL = 11,
    KeyM = 12,
    KeyN = 13,
    KeyO = 14,
    KeyP = 15,
    KeyQ = 16,
    KeyR = 17,
    KeyS = 18,
    KeyT = 19,
    KeyU = 20,
    KeyV = 21,
    KeyW = 22,
    KeyX = 23,
    KeyY = 24,
    KeyZ = 25,

    // Numbers keys

    KeyNumber0 = 26,
    KeyNumber1 = 27,
    KeyNumber2 = 28,
    KeyNumber3 = 29,
    KeyNumber4 = 30,
    KeyNumber5 = 31,
    KeyNumber6 = 32,
    KeyNumber7 = 33,
    KeyNumber8 = 34,
    KeyNumber9 = 35,

    // Printable special keys

    KeySpace        = 36,
    KeyApostrophe   = 37,
    KeyComma        = 38,
    KeyMinus        = 39,
    KeyPeriod       = 40,
    KeySlash        = 41,
    KeySemicolon    = 42,
    KeyEqual        = 43,
    KeyLeftBracket  = 44,
    KeyRightBracket = 45,
    KeyBackslash    = 46,
    KeyGraveAccent  = 47,
    KeyWorld1       = 48,
    KeyWorld2       = 49,

    // Function keys

    KeyF1  = 50,
    KeyF2  = 51,
    KeyF3  = 52,
    KeyF4  = 53,
    KeyF5  = 54,
    KeyF6  = 55,
    KeyF7  = 56,
    KeyF8  = 57,
    KeyF9  = 58,
    KeyF10 = 59,
    KeyF11 = 60,
    KeyF12 = 61,
    KeyF13 = 62,
    KeyF14 = 63,
    KeyF15 = 64,
    KeyF16 = 65,
    KeyF17 = 66,
    KeyF18 = 67,
    KeyF19 = 68,
    KeyF20 = 69,
    KeyF21 = 70,
    KeyF22 = 71,
    KeyF23 = 72,
    KeyF24 = 73,
    KeyF25 = 74,

    // Control keys

    KeyEscape      = 75,
    KeyEnter       = 76,
    KeyTab         = 77,
    KeyBackspace   = 78,
    KeyInsert      = 79,
    KeyDelete      = 80,
    KeyLeftArrow   = 81,
    KeyRightArrow  = 82,
    KeyDownArrow   = 83,
    KeyUpArrow     = 84,
    KeyPageUp      = 85,
    KeyPageDown    = 86,
    KeyHome        = 87,
    KeyEnd         = 88,
    KeyCapsLock    = 89,
    KeyScrollLock  = 90,
    KeyNumLock     = 91,
    KeyPrintScreen = 92,
    KeyPause       = 93,

    // Numpad keys

    KeyNumPad0        = 94,
    KeyNumPad1        = 95,
    KeyNumPad2        = 96,
    KeyNumPad3        = 97,
    KeyNumPad4        = 98,
    KeyNumPad5        = 99,
    KeyNumPad6        = 100,
    KeyNumPad7        = 101,
    KeyNumPad8        = 102,
    KeyNumPad9        = 103,
    KeyNumPadDecimal  = 104,
    KeyNumPadDivide   = 105,
    KeyNumPadMultiply = 106,
    KeyNumPadSubtract = 107,
    KeyNumPadAdd      = 108,
    KeyNumPadEnter    = 109,
    KeyNumPadEqual    = 110,

    // Modifier keys

    KeyLeftShift    = 111,
    KeyRightShift   = 112,
    KeyLeftControl  = 113,
    KeyRightControl = 114,
    KeyLeftAlt      = 115,
    KeyRightAlt     = 116,
    KeyLeftSuper    = 117,
    KeyRightSuper   = 118,
    KeyMenu         = 119,

    KeyCount,
} Key;

int32_t keyToNative(Key key);

