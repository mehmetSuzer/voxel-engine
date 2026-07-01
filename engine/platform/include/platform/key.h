
#pragma once

typedef enum Key
{
    KeyUnknown = -1,

    // Letters

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

    // Numbers (top row)

    KeyNum0 = 26,
    KeyNum1 = 27,
    KeyNum2 = 28,
    KeyNum3 = 29,
    KeyNum4 = 30,
    KeyNum5 = 31,
    KeyNum6 = 32,
    KeyNum7 = 33,
    KeyNum8 = 34,
    KeyNum9 = 35,

    // Function keys

    KeyF1  = 36,
    KeyF2  = 37,
    KeyF3  = 38,
    KeyF4  = 39,
    KeyF5  = 40,
    KeyF6  = 41,
    KeyF7  = 42,
    KeyF8  = 43,
    KeyF9  = 44,
    KeyF10 = 45,
    KeyF11 = 46,
    KeyF12 = 47,

    // Special keys

    KeyEscape       = 48,
    KeyTab          = 49,
    KeyCapsLock     = 50,
    KeyShiftLeft    = 51,
    KeyShiftRight   = 52,
    KeyControlLeft  = 53,
    KeyControlRight = 54,
    KeyAltLeft      = 55,
    KeyAltRight     = 56,
    KeySpace        = 57,
    KeyEnter        = 58,
    KeyBackspace    = 59,
    KeyInsert       = 60,
    KeyDelete       = 61,
    KeyHome         = 62,
    KeyEnd          = 63,
    KeyPageUp       = 64,
    KeyPageDown     = 65,
    KeyArrowUp      = 66,
    KeyArrowDown    = 67,
    KeyArrowLeft    = 68,
    KeyArrowRight   = 69,

    // Punctuation / symbols

    KeyMinus        = 70,
    KeyEqual        = 71,
    KeyBracketLeft  = 72,
    KeyBracketRight = 73,
    KeyBackslash    = 74,
    KeySemicolon    = 75,
    KeyApostrophe   = 76,
    KeyComma        = 77,
    KeyPeriod       = 78,
    KeySlash        = 79,
    KeyGraveAccent  = 80,

    // Numpad

    KeyNumPad0        = 81,
    KeyNumPad1        = 82,
    KeyNumPad2        = 83,
    KeyNumPad3        = 84,
    KeyNumPad4        = 85,
    KeyNumPad5        = 86,
    KeyNumPad6        = 87,
    KeyNumPad7        = 88,
    KeyNumPad8        = 89,
    KeyNumPad9        = 90,
    KeyNumPadDecimal  = 91,
    KeyNumPadDivide   = 92,
    KeyNumPadMultiply = 93,
    KeyNumPadSubtract = 94,
    KeyNumPadAdd      = 95,
    KeyNumPadEnter    = 96,
    KeyNumPadEqual    = 97,

    // Lock / misc
    
    KeyNumLock    =  98,
    KeyScrollLock =  99,
    KeyPause      = 100,

    KeyCount,
} Key;

int keyToNative(Key key);

