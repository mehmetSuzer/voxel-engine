
#pragma once

#include <GLFW/glfw3.h>

typedef enum
{
    GamepadButtonA           = GLFW_GAMEPAD_BUTTON_A,
    GamepadButtonB           = GLFW_GAMEPAD_BUTTON_B,
    GamepadButtonX           = GLFW_GAMEPAD_BUTTON_X,
    GamepadButtonY           = GLFW_GAMEPAD_BUTTON_Y,
    GamepadButtonLeftBumper  = GLFW_GAMEPAD_BUTTON_LEFT_BUMPER,
    GamepadButtonRightBumper = GLFW_GAMEPAD_BUTTON_RIGHT_BUMPER,
    GamepadButtonBack        = GLFW_GAMEPAD_BUTTON_BACK,
    GamepadButtonGuide       = GLFW_GAMEPAD_BUTTON_GUIDE,
    GamepadButtonStart       = GLFW_GAMEPAD_BUTTON_START,
    GamepadButtonLeftThumb   = GLFW_GAMEPAD_BUTTON_LEFT_THUMB,
    GamepadButtonRightThumb  = GLFW_GAMEPAD_BUTTON_RIGHT_THUMB,
    GamepadButtonDPadUp      = GLFW_GAMEPAD_BUTTON_DPAD_UP,
    GamepadButtonDPadRight   = GLFW_GAMEPAD_BUTTON_DPAD_RIGHT,
    GamepadButtonDPadDown    = GLFW_GAMEPAD_BUTTON_DPAD_DOWN,
    GamepadButtonDPadLeft    = GLFW_GAMEPAD_BUTTON_DPAD_LEFT,
    GamepadButtonCross       = GLFW_GAMEPAD_BUTTON_CROSS, // same as A on some controllers
    GamepadButtonCircle      = GLFW_GAMEPAD_BUTTON_CIRCLE,
    GamepadButtonSquare      = GLFW_GAMEPAD_BUTTON_SQUARE,
    GamepadButtonTriangle    = GLFW_GAMEPAD_BUTTON_TRIANGLE,
} GamepadButton;

typedef enum
{
    GamepadAxisLeftX        = GLFW_GAMEPAD_AXIS_LEFT_X,
    GamepadAxisLeftY        = GLFW_GAMEPAD_AXIS_LEFT_Y,
    GamepadAxisRightX       = GLFW_GAMEPAD_AXIS_RIGHT_X,
    GamepadAxisRightY       = GLFW_GAMEPAD_AXIS_RIGHT_Y,
    GamepadAxisLeftTrigger  = GLFW_GAMEPAD_AXIS_LEFT_TRIGGER,
    GamepadAxisRightTrigger = GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER,
} GamepadAxis;

