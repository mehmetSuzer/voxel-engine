
#include "camera.h"

void CameraTranslate(Camera* camera, vec3 localDelta)
{
    vec3 worldDeltaAxis;

    glm_quat_rotatev(camera->rotation, (vec3){1.0f, 0.0f, 0.0f}, worldDeltaAxis);
    glm_vec3_scale(worldDeltaAxis, localDelta[0], worldDeltaAxis);
    glm_vec3_add(camera->position, worldDeltaAxis, camera->position);

    glm_quat_rotatev(camera->rotation, (vec3){0.0f, 1.0f, 0.0f}, worldDeltaAxis);
    glm_vec3_scale(worldDeltaAxis, localDelta[1], worldDeltaAxis);
    glm_vec3_add(camera->position, worldDeltaAxis, camera->position);

    glm_quat_rotatev(camera->rotation, (vec3){0.0f, 0.0f, 1.0f}, worldDeltaAxis);
    glm_vec3_scale(worldDeltaAxis, localDelta[2], worldDeltaAxis);
    glm_vec3_add(camera->position, worldDeltaAxis, camera->position);
}

void CameraRotate(Camera* camera, float dx, float dy, float sensitivity)
{
    const float pitch = -dy * sensitivity;
    const float yaw   = -dx * sensitivity;

    versor qPitch, qYaw;
    glm_quatv(qPitch, pitch, (vec3){1.0f, 0.0f, 0.0f});
    glm_quatv(qYaw,   yaw,   (vec3){0.0f, 1.0f, 0.0f});

    glm_quat_mul(camera->rotation, qYaw, camera->rotation);
    glm_quat_mul(camera->rotation, camera->rotation, qPitch);
    glm_quat_normalize(camera->rotation);
}

void CameraView(Camera* camera, mat4 view)
{
    versor inverseRotation;
    glm_quat_inv(camera->rotation, inverseRotation);
    glm_quat_mat4(inverseRotation, view);

    vec3 negativePosition;
    glm_vec3_negate_to(camera->position, negativePosition);
    glm_translate(view, negativePosition);
}

void CameraProjection(Camera* camera, float aspectRatio, mat4 projection)
{
    glm_perspective(camera->fovWidth, aspectRatio, camera->near, camera->far, projection);
}

