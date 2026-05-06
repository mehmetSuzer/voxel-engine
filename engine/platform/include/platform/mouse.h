
#pragma once

typedef enum MouseButton
{
    MouseButton1 = 0,
    MouseButton2 = 1,
    MouseButton3 = 2,
    MouseButton4 = 3,
    MouseButton5 = 4,
    MouseButton6 = 5,
    MouseButton7 = 6,
    MouseButton8 = 7,
    MouseButtonCount,

    MouseButtonLeft   = MouseButton1, // Same as MouseButton1
    MouseButtonRight  = MouseButton2, // Same as MouseButton2
    MouseButtonMiddle = MouseButton3, // Same as MouseButton3
} MouseButton;

int mouseButtonToPlatformCode(MouseButton mouseButton);

