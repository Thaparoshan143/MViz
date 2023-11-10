#include "CameraController.h"

namespace Abs {

    static float cameraSpeed = 4.0f;

    CameraController::CameraController(float fov, float aspect, float near_clipping_plane, float far_clipping_plane)
        : m_camera(glm::radians(fov), aspect, near_clipping_plane, far_clipping_plane),
          m_aspect(aspect),
          m_near(near_clipping_plane),
          m_far(far_clipping_plane),
          m_fov(fov)
    {

    }

    Camera& CameraController::GetCamera() { return m_camera; }

    void CameraController::ProcessInput(float delta_time) {
        if (Input::IsKeyPressed(Key::W)) {
            m_position += m_front * cameraSpeed * delta_time;
            m_updateLookAt = true;
        }

        if (Input::IsKeyPressed(Key::S)) {
            m_position -= m_front * cameraSpeed * delta_time;
            m_updateLookAt = true;
        }

        if (Input::IsKeyPressed(Key::A)) {
            m_position -= glm::normalize(glm::cross(m_front, m_up)) * cameraSpeed * delta_time;
            m_updateLookAt = true;
        }

        if (Input::IsKeyPressed(Key::D)) {
            m_position += glm::normalize(glm::cross(m_front, m_up)) * cameraSpeed * delta_time;
            m_updateLookAt = true;
        }
    }

    void CameraController::OnUpdate(float delta_time) {
        ProcessInput(delta_time);

        if (m_updateLookAt) {
            m_camera.LookAt(m_position, m_front, m_up);
            m_updateLookAt = false;
        }
    }
}