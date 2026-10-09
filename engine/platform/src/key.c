
#include <assert.h>
#include <GLFW/glfw3.h>
#include "log/log.h"
#include "platform/key.h"

int32_t keyToNative(Key key)
{
    switch (key)
    {
        // Letter keys

        case KeyA: return GLFW_KEY_A;
        case KeyB: return GLFW_KEY_B;
        case KeyC: return GLFW_KEY_C;
        case KeyD: return GLFW_KEY_D;
        case KeyE: return GLFW_KEY_E;
        case KeyF: return GLFW_KEY_F;
        case KeyG: return GLFW_KEY_G;
        case KeyH: return GLFW_KEY_H;
        case KeyI: return GLFW_KEY_I;
        case KeyJ: return GLFW_KEY_J;
        case KeyK: return GLFW_KEY_K;
        case KeyL: return GLFW_KEY_L;
        case KeyM: return GLFW_KEY_M;
        case KeyN: return GLFW_KEY_N;
        case KeyO: return GLFW_KEY_O;
        case KeyP: return GLFW_KEY_P;
        case KeyQ: return GLFW_KEY_Q;
        case KeyR: return GLFW_KEY_R;
        case KeyS: return GLFW_KEY_S;
        case KeyT: return GLFW_KEY_T;
        case KeyU: return GLFW_KEY_U;
        case KeyV: return GLFW_KEY_V;
        case KeyW: return GLFW_KEY_W;
        case KeyX: return GLFW_KEY_X;
        case KeyY: return GLFW_KEY_Y;
        case KeyZ: return GLFW_KEY_Z;

        // Number keys

        case KeyNumber0: return GLFW_KEY_0;
        case KeyNumber1: return GLFW_KEY_1;
        case KeyNumber2: return GLFW_KEY_2;
        case KeyNumber3: return GLFW_KEY_3;
        case KeyNumber4: return GLFW_KEY_4;
        case KeyNumber5: return GLFW_KEY_5;
        case KeyNumber6: return GLFW_KEY_6;
        case KeyNumber7: return GLFW_KEY_7;
        case KeyNumber8: return GLFW_KEY_8;
        case KeyNumber9: return GLFW_KEY_9;

        // Printable special keys

        case KeySpace:        return GLFW_KEY_SPACE;
        case KeyApostrophe:   return GLFW_KEY_APOSTROPHE;
        case KeyComma:        return GLFW_KEY_COMMA;
        case KeyMinus:        return GLFW_KEY_MINUS;
        case KeyPeriod:       return GLFW_KEY_PERIOD;
        case KeySlash:        return GLFW_KEY_SLASH;
        case KeySemicolon:    return GLFW_KEY_SEMICOLON;
        case KeyEqual:        return GLFW_KEY_EQUAL;
        case KeyLeftBracket:  return GLFW_KEY_LEFT_BRACKET;
        case KeyRightBracket: return GLFW_KEY_RIGHT_BRACKET;
        case KeyBackslash:    return GLFW_KEY_BACKSLASH;
        case KeyGraveAccent:  return GLFW_KEY_GRAVE_ACCENT;
        case KeyWorld1:       return GLFW_KEY_WORLD_1;
        case KeyWorld2:       return GLFW_KEY_WORLD_2;

        // Function keys

        case KeyF1:  return GLFW_KEY_F1;
        case KeyF2:  return GLFW_KEY_F2;
        case KeyF3:  return GLFW_KEY_F3;
        case KeyF4:  return GLFW_KEY_F4;
        case KeyF5:  return GLFW_KEY_F5;
        case KeyF6:  return GLFW_KEY_F6;
        case KeyF7:  return GLFW_KEY_F7;
        case KeyF8:  return GLFW_KEY_F8;
        case KeyF9:  return GLFW_KEY_F9;
        case KeyF10: return GLFW_KEY_F10;
        case KeyF11: return GLFW_KEY_F11;
        case KeyF12: return GLFW_KEY_F12;
        case KeyF13: return GLFW_KEY_F13;
        case KeyF14: return GLFW_KEY_F14;
        case KeyF15: return GLFW_KEY_F15;
        case KeyF16: return GLFW_KEY_F16;
        case KeyF17: return GLFW_KEY_F17;
        case KeyF18: return GLFW_KEY_F18;
        case KeyF19: return GLFW_KEY_F19;
        case KeyF20: return GLFW_KEY_F20;
        case KeyF21: return GLFW_KEY_F21;
        case KeyF22: return GLFW_KEY_F22;
        case KeyF23: return GLFW_KEY_F23;
        case KeyF24: return GLFW_KEY_F24;
        case KeyF25: return GLFW_KEY_F25;

        // Control keys

        case KeyEscape:      return GLFW_KEY_ESCAPE;
        case KeyEnter:       return GLFW_KEY_ENTER;
        case KeyTab:         return GLFW_KEY_TAB;
        case KeyBackspace:   return GLFW_KEY_BACKSPACE;
        case KeyInsert:      return GLFW_KEY_INSERT;
        case KeyDelete:      return GLFW_KEY_DELETE;
        case KeyLeftArrow:   return GLFW_KEY_LEFT;
        case KeyRightArrow:  return GLFW_KEY_RIGHT;
        case KeyDownArrow:   return GLFW_KEY_DOWN;
        case KeyUpArrow:     return GLFW_KEY_UP;
        case KeyPageUp:      return GLFW_KEY_PAGE_UP;
        case KeyPageDown:    return GLFW_KEY_PAGE_DOWN;
        case KeyHome:        return GLFW_KEY_HOME;
        case KeyEnd:         return GLFW_KEY_END;
        case KeyCapsLock:    return GLFW_KEY_CAPS_LOCK;
        case KeyScrollLock:  return GLFW_KEY_SCROLL_LOCK;
        case KeyNumLock:     return GLFW_KEY_NUM_LOCK;
        case KeyPrintScreen: return GLFW_KEY_PRINT_SCREEN;
        case KeyPause:       return GLFW_KEY_PAUSE;

        // Numpad keys

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

        // Modifier keys

        case KeyLeftShift:    return GLFW_KEY_LEFT_SHIFT;
        case KeyRightShift:   return GLFW_KEY_RIGHT_SHIFT;
        case KeyLeftControl:  return GLFW_KEY_LEFT_CONTROL;
        case KeyRightControl: return GLFW_KEY_RIGHT_CONTROL;
        case KeyLeftAlt:      return GLFW_KEY_LEFT_ALT;
        case KeyRightAlt:     return GLFW_KEY_RIGHT_ALT;
        case KeyLeftSuper:    return GLFW_KEY_LEFT_SUPER;
        case KeyRightSuper:   return GLFW_KEY_RIGHT_SUPER;
        case KeyMenu:         return GLFW_KEY_MENU;
    }

    logError("KEY", "invalid key");
    assert(0);

    return GLFW_KEY_UNKNOWN;
}

