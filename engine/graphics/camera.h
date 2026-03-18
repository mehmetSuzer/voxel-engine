
#pragma once

#include <cglm/cglm.h>
#include <cglm/call.h>

typedef struct
{
    vec3 position;
    versor rotation;
    float fovWidth;
    float near;
    float far;
} Camera;

void CameraTranslate(Camera* camera, vec3 localDelta);
void CameraRotate(Camera* camera, float dx, float dy, float sensitivity);
void CameraView(Camera* camera, mat4 view);
void CameraProjection(Camera* camera, float aspectRatio, mat4 projection);

