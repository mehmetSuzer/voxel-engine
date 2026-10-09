
#include "graphics/camera.h"

void cameraTranslate(Camera* camera, const vec3 localDelta)
{
    vec3 worldDeltaForAxis = GLM_VEC3_ZERO_INIT;

    glm_quat_rotatev(camera->rotation, GLM_XUP, worldDeltaForAxis);
    glm_vec3_scale(worldDeltaForAxis, localDelta[0], worldDeltaForAxis);
    glm_vec3_add(camera->position, worldDeltaForAxis, camera->position);

    glm_quat_rotatev(camera->rotation, GLM_YUP, worldDeltaForAxis);
    glm_vec3_scale(worldDeltaForAxis, localDelta[1], worldDeltaForAxis);
    glm_vec3_add(camera->position, worldDeltaForAxis, camera->position);

    glm_quat_rotatev(camera->rotation, GLM_ZUP, worldDeltaForAxis);
    glm_vec3_scale(worldDeltaForAxis, localDelta[2], worldDeltaForAxis);
    glm_vec3_add(camera->position, worldDeltaForAxis, camera->position);
}

void cameraRotate(Camera* camera, float dx, float dy, float sensitivity)
{
    const float pitch = -dy * sensitivity;
    const float yaw   = -dx * sensitivity;

    versor qPitch = GLM_QUAT_IDENTITY_INIT;
    versor qYaw   = GLM_QUAT_IDENTITY_INIT;

    glm_quatv(qPitch, pitch, GLM_XUP);
    glm_quatv(qYaw,   yaw,   GLM_YUP);

    glm_quat_mul(camera->rotation, qYaw, camera->rotation);
    glm_quat_mul(camera->rotation, camera->rotation, qPitch);
    glm_quat_normalize(camera->rotation);
}

void cameraZoom(Camera* camera, float scroll, float sensitivity)
{
    const float deltaFovWidth = scroll * sensitivity;
    camera->fovWidth += deltaFovWidth;
}

void cameraView(Camera* camera, mat4 viewOut)
{
    versor inverseRotation = GLM_QUAT_IDENTITY_INIT;
    glm_quat_inv(camera->rotation, inverseRotation);
    glm_quat_mat4(inverseRotation, viewOut);

    vec3 negativePosition = GLM_VEC3_ZERO_INIT;
    glm_vec3_negate_to(camera->position, negativePosition);
    glm_translate(viewOut, negativePosition);
}

void cameraProjection(Camera* camera, float aspectRatio, mat4 projectionOut)
{
    glm_perspective(camera->fovWidth, aspectRatio, camera->near, camera->far, projectionOut);
}

