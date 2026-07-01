
#include <assert.h>
#include <GLFW/glfw3.h>
#include "log/log.h"
#include "platform/mouse.h"

int mouseButtonToNative(MouseButton mouseButton)
{
    switch (mouseButton)
    {
        case MouseButton1:  return GLFW_MOUSE_BUTTON_1;
        case MouseButton2:  return GLFW_MOUSE_BUTTON_2;
        case MouseButton3:  return GLFW_MOUSE_BUTTON_3;
        case MouseButton4:  return GLFW_MOUSE_BUTTON_4;
        case MouseButton5:  return GLFW_MOUSE_BUTTON_5;
        case MouseButton6:  return GLFW_MOUSE_BUTTON_6;
        case MouseButton7:  return GLFW_MOUSE_BUTTON_7;
        case MouseButton8:  return GLFW_MOUSE_BUTTON_8;
    }

    logError("MOUSE", "invalid button");
    assert(0);

    return GLFW_MOUSE_BUTTON_1;
}

