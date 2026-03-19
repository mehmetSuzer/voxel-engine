
#include "log/log.h"
#include "graphics/camera.h"
#include "graphics/texture.h"
#include "graphics/world.h"
#include "graphics/graphics.h"
#include "graphics/light.h"
#include "host/host.h"

#define WINDOW_WIDTH  1200
#define WINDOW_HEIGHT 1000
#define WINDOW_TITLE  "Voxel Engine"
#define ASPECT_RATIO  ((float)WINDOW_WIDTH/(float)WINDOW_HEIGHT)

int main()
{
    LogSetMinSeverity(LogSeverityVerbose);

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
    GraphicsSetClearDepth(DEPTH_FURTHEST);

    ShaderProgram shaderProgram = ShaderProgramCreateVF(
        "shaders/terrain_vertex.glsl",
        "shaders/terrain_fragment.glsl");

    Texture textureAtlas = TextureCreate(
        "textures/dummy_atlas.png",
        TextureWrapRepeat,
        TextureWrapRepeat,
        TextureMinFilterNearestMipmapNearest,
        TextureMagFilterNearest,
        (vec4){0.0f, 0.0f, 0.0f, 1.0f});

    ShaderProgramBind(shaderProgram);
    TextureBind(textureAtlas, 0);
    ShaderProgramSetUniformi(shaderProgram, "textureAtlas", 0);

    WorldCreate();
    
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

    while (!WindowShouldClose(window))
    {
        if (WindowIsKeyPressed(window, KeyEscape))
        {
            WindowSetShouldClose(window);
        }

        const float cameraSpeed = 0.1f;
        if (WindowIsKeyPressed(window, KeyA))           { CameraTranslate(&camera, (vec3){-cameraSpeed, 0.0f, 0.0f}); }
        if (WindowIsKeyPressed(window, KeyD))           { CameraTranslate(&camera, (vec3){ cameraSpeed, 0.0f, 0.0f}); }
        if (WindowIsKeyPressed(window, KeyS))           { CameraTranslate(&camera, (vec3){0.0f, 0.0f,  cameraSpeed}); }
        if (WindowIsKeyPressed(window, KeyW))           { CameraTranslate(&camera, (vec3){0.0f, 0.0f, -cameraSpeed}); }
        if (WindowIsKeyPressed(window, KeySpace))       { CameraTranslate(&camera, (vec3){0.0f,  cameraSpeed, 0.0f}); }
        if (WindowIsKeyPressed(window, KeyControlLeft)) { CameraTranslate(&camera, (vec3){0.0f, -cameraSpeed, 0.0f}); }

        mat4 view, projection;
        CameraView(&camera, view);
        CameraProjection(&camera, ASPECT_RATIO, projection);
        ShaderProgramSetUniformMat4f(shaderProgram, "view", view);
        ShaderProgramSetUniformMat4f(shaderProgram, "projection", projection);

        ShaderProgramSetUniform3f(shaderProgram, "pointLight.colour", light.colour);
        ShaderProgramSetUniform3f(shaderProgram, "pointLight.position", light.position);
        ShaderProgramSetUniformf(shaderProgram, "pointLight.quadratic", light.quadratic);
        ShaderProgramSetUniformf(shaderProgram, "pointLight.linear", light.linear);
        ShaderProgramSetUniform3f(shaderProgram, "cameraPosition", camera.position);
        
        GraphicsClear(BufferBitColour | BufferBitDepth);
        WorldDraw(shaderProgram);

        WindowSwapBuffers(window);
        HostPollEvents();
    }

    TextureDelete(textureAtlas);
    ShaderProgramDelete(shaderProgram);
    WorldDelete();
    WindowDelete(window);
    HostTerminate();

    return 0;
}

