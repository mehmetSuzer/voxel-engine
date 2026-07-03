
#include "log/log.h"
#include "utils/macros.h"
#include "platform/platform.h"
#include "platform/window.h"
#include "graphics/camera.h"
#include "graphics/graphics.h"
#include "graphics/light.h"

#define WINDOW_WIDTH  1200
#define WINDOW_HEIGHT 1000
#define WINDOW_ASPECT_RATIO  ((float)WINDOW_WIDTH/(float)WINDOW_HEIGHT)

int main(void)
{
    if (!platformInit())
    {
        return EXIT_FAILURE;
    }

    Window* window = windowCreate(WINDOW_WIDTH, WINDOW_HEIGHT, "Voxel Engine");
    if (window == NULL)
    {
        platformTerminate();
        return EXIT_FAILURE;
    }
    windowMakeContextCurrent(window);

    if (!graphicsInit((GraphicsFunctionLoader)platformGetGLFunctionLoader()))
    {
        windowDestroy(window);
        platformTerminate();
        return EXIT_FAILURE;
    }

    graphicsViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    
    graphicsEnable(CapabilityDepthTest);
    graphicsDepthWriteEnable(true);
    graphicsDepthFunc(CompareFuncLess);
    graphicsDepthRange(0.0f, 1.0f);

    graphicsEnable(CapabilityCullFace);
    graphicsCullFace(FaceBack);
    graphicsFrontFace(FrontFaceCCW);

    graphicsPolygonMode(FaceBoth, PolygonModeFill);

    graphicsClearColour((vec4){0.2f, 0.3f, 0.3f, 1.0f});
    graphicsClearDepth(DEPTH_FURTHEST);

    Camera camera = {
        .position = {16.0f, 16.0f, 40.0f},
        .rotation = {0.0f, 0.0f, 0.0f, 1.0f},
        .fovWidth = GLM_PI_4f,
        .near = 0.1f,
        .far = 100.0f,
    };

    PointLight light = {
        .colour = {1.0f, 1.0f, 1.0f},
        .position = {16.0f, 40.0f, 16.0f},
        .quadratic = 0.005f,
        .linear = 0.001f,
    };
    UNUSED(light);

    while (!windowShouldClose(window))
    {
        if (windowIsKeyPressed(window, KeyEscape))
        {
            windowSetShouldClose(window);
        }

        const float cameraSpeed = 0.1f;
        if (windowIsKeyPressed(window, KeyA          )) { cameraTranslate(&camera, (vec3){-cameraSpeed, 0.0f, 0.0f}); }
        if (windowIsKeyPressed(window, KeyD          )) { cameraTranslate(&camera, (vec3){ cameraSpeed, 0.0f, 0.0f}); }
        if (windowIsKeyPressed(window, KeyS          )) { cameraTranslate(&camera, (vec3){0.0f, 0.0f,  cameraSpeed}); }
        if (windowIsKeyPressed(window, KeyW          )) { cameraTranslate(&camera, (vec3){0.0f, 0.0f, -cameraSpeed}); }
        if (windowIsKeyPressed(window, KeySpace      )) { cameraTranslate(&camera, (vec3){0.0f,  cameraSpeed, 0.0f}); }
        if (windowIsKeyPressed(window, KeyControlLeft)) { cameraTranslate(&camera, (vec3){0.0f, -cameraSpeed, 0.0f}); }

        graphicsClear(BufferBitColour | BufferBitDepth);

        windowSwapBuffers(window);
        platformPollEvents();
    }

    windowDestroy(window);
    platformTerminate();

    return 0;
}

