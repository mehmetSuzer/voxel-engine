
#pragma once

#include <cglm/cglm.h>
#include <cglm/call.h>

typedef struct Camera
{
    vec3 position;
    versor rotation;
    float fovWidth;
    float near;
    float far;
} Camera;

void cameraTranslate(Camera* camera, vec3 localDelta);
void cameraRotate(Camera* camera, float dx, float dy, float sensitivity);
void cameraZoom(Camera* camera, float scroll, float sensitivity);

void cameraView(Camera* camera, mat4 viewOut);
void cameraProjection(Camera* camera, float aspectRatio, mat4 projectionOut);

