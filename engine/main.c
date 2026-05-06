
#include "log/log.h"
#include "graphics/camera.h"
#include "graphics/texture.h"
#include "graphics/world.h"
#include "graphics/graphics.h"
#include "graphics/light.h"
#include "platform/platform.h"
#include "platform/window.h"

#define WINDOW_WIDTH  1200
#define WINDOW_HEIGHT 1000
#define WINDOW_TITLE  "Voxel Engine"
#define ASPECT_RATIO  ((float)WINDOW_WIDTH/(float)WINDOW_HEIGHT)

int main()
{
    platformInit();
    Window* window = windowCreate(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
    windowMakeContextCurrent(window);

    graphicsInit((GLADloadproc)platformGetGLFunctionLoader());
    graphicsViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    
    graphicsEnable(CapabilityDepthTest);
    graphicsDepthWriteEnable(1);
    graphicsDepthFunc(TestFuncLess);
    graphicsDepthRange(0.0f, 1.0f);

    graphicsEnable(CapabilityCullFace);
    graphicsCullFace(FaceBack);
    graphicsFrontFace(FrontFaceCCW);

    graphicsPolygonMode(FaceBoth, PolygonModeFill);

    graphicsClearColour((vec4){0.2f, 0.3f, 0.3f, 1.0f});
    graphicsClearDepth(DEPTH_FURTHEST);

    ShaderProgram shaderProgram = shaderProgramCreateVF("shaders/terrain.vert", "shaders/terrain.frag");

    Texture textureAtlas = textureCreate(
        "textures/dummy_atlas.png",
        TextureWrapRepeat,
        TextureWrapRepeat,
        TextureMinFilterNearestMipmapNearest,
        TextureMagFilterNearest,
        (vec4){0.0f, 0.0f, 0.0f, 1.0f});

    shaderProgramBind(shaderProgram);
    textureBind(textureAtlas, 0);
    shaderProgramSetUniformi(shaderProgram, "textureAtlas", 0);

    worldCreate();
    
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

    while (!windowShouldClose(window))
    {
        if (windowIsKeyPressed(window, KeyEscape))
        {
            windowSetShouldClose(window);
        }

        const float cameraSpeed = 0.1f;
        if (windowIsKeyPressed(window, KeyA))           { cameraTranslate(&camera, (vec3){-cameraSpeed, 0.0f, 0.0f}); }
        if (windowIsKeyPressed(window, KeyD))           { cameraTranslate(&camera, (vec3){ cameraSpeed, 0.0f, 0.0f}); }
        if (windowIsKeyPressed(window, KeyS))           { cameraTranslate(&camera, (vec3){0.0f, 0.0f,  cameraSpeed}); }
        if (windowIsKeyPressed(window, KeyW))           { cameraTranslate(&camera, (vec3){0.0f, 0.0f, -cameraSpeed}); }
        if (windowIsKeyPressed(window, KeySpace))       { cameraTranslate(&camera, (vec3){0.0f,  cameraSpeed, 0.0f}); }
        if (windowIsKeyPressed(window, KeyControlLeft)) { cameraTranslate(&camera, (vec3){0.0f, -cameraSpeed, 0.0f}); }

        mat4 view, projection;
        cameraView(&camera, view);
        cameraProjection(&camera, ASPECT_RATIO, projection);
        shaderProgramSetUniformMat4f(shaderProgram, "view", view);
        shaderProgramSetUniformMat4f(shaderProgram, "projection", projection);

        shaderProgramSetUniform3f(shaderProgram, "pointLight.colour", light.colour);
        shaderProgramSetUniform3f(shaderProgram, "pointLight.position", light.position);
        shaderProgramSetUniformf(shaderProgram, "pointLight.quadratic", light.quadratic);
        shaderProgramSetUniformf(shaderProgram, "pointLight.linear", light.linear);
        shaderProgramSetUniform3f(shaderProgram, "cameraPosition", camera.position);
        
        graphicsClear(BufferBitColour | BufferBitDepth);
        worldDraw(shaderProgram);

        windowSwapBuffers(window);
        platformPollEvents();
    }

    textureDelete(textureAtlas);
    shaderProgramDelete(shaderProgram);
    worldDelete();
    windowDestroy(window);
    platformTerminate();

    return 0;
}

