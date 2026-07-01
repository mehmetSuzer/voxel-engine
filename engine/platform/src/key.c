
#include <assert.h>
#include <GLFW/glfw3.h>
#include "log/log.h"
#include "platform/key.h"

int keyToNative(Key key)
{
    switch (key)
    {
        // Letters
        case KeyA:              return GLFW_KEY_A;
        case KeyB:              return GLFW_KEY_B;
        case KeyC:              return GLFW_KEY_C;
        case KeyD:              return GLFW_KEY_D;
        case KeyE:              return GLFW_KEY_E;
        case KeyF:              return GLFW_KEY_F;
        case KeyG:              return GLFW_KEY_G;
        case KeyH:              return GLFW_KEY_H;
        case KeyI:              return GLFW_KEY_I;
        case KeyJ:              return GLFW_KEY_J;
        case KeyK:              return GLFW_KEY_K;
        case KeyL:              return GLFW_KEY_L;
        case KeyM:              return GLFW_KEY_M;
        case KeyN:              return GLFW_KEY_N;
        case KeyO:              return GLFW_KEY_O;
        case KeyP:              return GLFW_KEY_P;
        case KeyQ:              return GLFW_KEY_Q;
        case KeyR:              return GLFW_KEY_R;
        case KeyS:              return GLFW_KEY_S;
        case KeyT:              return GLFW_KEY_T;
        case KeyU:              return GLFW_KEY_U;
        case KeyV:              return GLFW_KEY_V;
        case KeyW:              return GLFW_KEY_W;
        case KeyX:              return GLFW_KEY_X;
        case KeyY:              return GLFW_KEY_Y;
        case KeyZ:              return GLFW_KEY_Z;
        // Numbers (top row)
        case KeyNum0:           return GLFW_KEY_0;
        case KeyNum1:           return GLFW_KEY_1;
        case KeyNum2:           return GLFW_KEY_2;
        case KeyNum3:           return GLFW_KEY_3;
        case KeyNum4:           return GLFW_KEY_4;
        case KeyNum5:           return GLFW_KEY_5;
        case KeyNum6:           return GLFW_KEY_6;
        case KeyNum7:           return GLFW_KEY_7;
        case KeyNum8:           return GLFW_KEY_8;
        case KeyNum9:           return GLFW_KEY_9;
        // Function keys
        case KeyF1:             return GLFW_KEY_F1;
        case KeyF2:             return GLFW_KEY_F2;
        case KeyF3:             return GLFW_KEY_F3;
        case KeyF4:             return GLFW_KEY_F4;
        case KeyF5:             return GLFW_KEY_F5;
        case KeyF6:             return GLFW_KEY_F6;
        case KeyF7:             return GLFW_KEY_F7;
        case KeyF8:             return GLFW_KEY_F8;
        case KeyF9:             return GLFW_KEY_F9;
        case KeyF10:            return GLFW_KEY_F10;
        case KeyF11:            return GLFW_KEY_F11;
        case KeyF12:            return GLFW_KEY_F12;
        // Special keys
        case KeyEscape:         return GLFW_KEY_ESCAPE;
        case KeyTab:            return GLFW_KEY_TAB;
        case KeyCapsLock:       return GLFW_KEY_CAPS_LOCK;
        case KeyShiftLeft:      return GLFW_KEY_LEFT_SHIFT;
        case KeyShiftRight:     return GLFW_KEY_RIGHT_SHIFT;
        case KeyControlLeft:    return GLFW_KEY_LEFT_CONTROL;
        case KeyControlRight:   return GLFW_KEY_RIGHT_CONTROL;
        case KeyAltLeft:        return GLFW_KEY_LEFT_ALT;
        case KeyAltRight:       return GLFW_KEY_RIGHT_ALT;
        case KeySpace:          return GLFW_KEY_SPACE;
        case KeyEnter:          return GLFW_KEY_ENTER;
        case KeyBackspace:      return GLFW_KEY_BACKSPACE;
        case KeyInsert:         return GLFW_KEY_INSERT;
        case KeyDelete:         return GLFW_KEY_DELETE;
        case KeyHome:           return GLFW_KEY_HOME;
        case KeyEnd:            return GLFW_KEY_END;
        case KeyPageUp:         return GLFW_KEY_PAGE_UP;
        case KeyPageDown:       return GLFW_KEY_PAGE_DOWN;
        case KeyArrowUp:        return GLFW_KEY_UP;
        case KeyArrowDown:      return GLFW_KEY_DOWN;
        case KeyArrowLeft:      return GLFW_KEY_LEFT;
        case KeyArrowRight:     return GLFW_KEY_RIGHT;
        // Punctuation / symbols
        case KeyMinus:          return GLFW_KEY_MINUS;
        case KeyEqual:          return GLFW_KEY_EQUAL;
        case KeyBracketLeft:    return GLFW_KEY_LEFT_BRACKET;
        case KeyBracketRight:   return GLFW_KEY_RIGHT_BRACKET;
        case KeyBackslash:      return GLFW_KEY_BACKSLASH;
        case KeySemicolon:      return GLFW_KEY_SEMICOLON;
        case KeyApostrophe:     return GLFW_KEY_APOSTROPHE;
        case KeyComma:          return GLFW_KEY_COMMA;
        case KeyPeriod:         return GLFW_KEY_PERIOD;
        case KeySlash:          return GLFW_KEY_SLASH;
        case KeyGraveAccent:    return GLFW_KEY_GRAVE_ACCENT;
        // Numpad
        case KeyNumPad0:        return GLFW_KEY_KP_0;
        case KeyNumPad1:        return GLFW_KEY_KP_1;
        case KeyNumPad2:        return GLFW_KEY_KP_2;
        case KeyNumPad3:        return GLFW_KEY_KP_3;
        case KeyNumPad4:        return GLFW_KEY_KP_4;
        case KeyNumPad5:        return GLFW_KEY_KP_5;
        case KeyNumPad6:        return GLFW_KEY_KP_6;
        case KeyNumPad7:        return GLFW_KEY_KP_7;
        case KeyNumPad8:        return GLFW_KEY_KP_8;
        case KeyNumPad9:        return GLFW_KEY_KP_9;
        case KeyNumPadDecimal:  return GLFW_KEY_KP_DECIMAL;
        case KeyNumPadDivide:   return GLFW_KEY_KP_DIVIDE;
        case KeyNumPadMultiply: return GLFW_KEY_KP_MULTIPLY;
        case KeyNumPadSubtract: return GLFW_KEY_KP_SUBTRACT;
        case KeyNumPadAdd:      return GLFW_KEY_KP_ADD;
        case KeyNumPadEnter:    return GLFW_KEY_KP_ENTER;
        case KeyNumPadEqual:    return GLFW_KEY_KP_EQUAL;
        // Lock / misc
        case KeyNumLock:        return GLFW_KEY_NUM_LOCK;
        case KeyScrollLock:     return GLFW_KEY_SCROLL_LOCK;
        case KeyPause:          return GLFW_KEY_PAUSE;
    }
    
    logError("KEY", "invalid key");
    assert(0);

    return GLFW_KEY_UNKNOWN;
}

