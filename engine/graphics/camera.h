
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

void CameraTranslate(Camera* camera, vec3 localDelta);
void CameraRotate(Camera* camera, float dx, float dy, float sensitivity);
void CameraZoom(Camera* camera, float scroll, float sensitivity);

void CameraView(Camera* camera, mat4 viewOut);
void CameraProjection(Camera* camera, float aspectRatio, mat4 projectionOut);

