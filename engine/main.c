
#include <stdio.h>
#include <stdlib.h>
#include "graphics/graphics.h"
#include "host/host.h"

#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 600
#define WINDOW_TITLE  "Voxel Engine"
#define ASPECT_RATIO  ((float)WINDOW_WIDTH/(float)WINDOW_HEIGHT)

int main()
{
    HostInit();
    Window* window = WindowCreate(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
    WindowMakeContextCurrent(window);

    GraphicsInit((GLADloadproc)HostGetGLFunctionLoader());
    GraphicsSetViewport((Rectangle){0, 0, WINDOW_WIDTH, WINDOW_HEIGHT});
    GraphicsSetDepthTest((DepthTest){
        .enabled = 1,
        .writeEnabled = 1,
        .func = TestFuncLess,
    });
    GraphicsSetPolygonMode((PolygonMode){
        .face = FaceBoth,
        .mode = PolygonDrawModeFill,
    });
    GraphicsSetFaceCull((FaceCull){
        .enabled = 1,
        .cullFace = FaceBack,
        .frontFace = FrontFaceCCW,
    });
    
    GraphicsSetClearColour((vec4){0.2f, 0.3f, 0.3f, 1.0f});
    GraphicsSetClearDepth(0.0f);

    while (!WindowShouldClose(window))
    {
        if (WindowIsKeyPressed(window, KeyEscape))
        {
            WindowSetShouldClose(window);
        }

        GraphicsClear(BufferBitColour | BufferBitDepth);

        WindowSwapBuffers(window);
        HostPollEvents();
    }

    WindowDelete(window);
    HostTerminate();
    return 0;
}

