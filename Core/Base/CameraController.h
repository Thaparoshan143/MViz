#pragma once

#include "../../Core/Base/Types.h"
#include "Camera.h"
#include "../../Core/Base/Input.h"

namespace Abs {
    class CameraController {
        public:
            CameraController(float fov, float aspect, float near_clipping_plane, float far_clipping_plane);
            ~CameraController() = default;

            Camera& GetCamera();
            void ProcessInput(float delta_time);
            void OnUpdate(float delta_time);

        private:
            Camera m_camera;

            fVec3 m_position;
            fVec3 m_front;
            fVec3 m_up;

            float m_yaw;
            float m_pitch;
            float m_aspect;
            float m_near;
            float m_far;
            float m_fov;

            bool m_updateLookAt;

    };
}