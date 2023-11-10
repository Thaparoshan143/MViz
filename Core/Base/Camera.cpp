#include "Camera.h"

namespace Abs {
    Camera::Camera(float fov, float aspect, float near_clipping_plane, float far_clipping_plane) {
        m_projectionMatrix = glm::perspective(glm::radians(fov), aspect, near_clipping_plane, far_clipping_plane);
    }

    void Camera::LookAt(fVec3 pos, fVec3 front, fVec3 up) {
        m_viewMatrix = glm::lookAt(pos, pos + front, up);
    }

    Mat4 Camera::GetProjectionMatrix() { return m_projectionMatrix; }
    
    Mat4 Camera::GetViewMatrix() { return m_viewMatrix; }
}