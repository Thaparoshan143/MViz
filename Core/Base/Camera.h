#pragma once

#include "../../Core/Base/Types.h"

namespace Abs{
    class Camera {
        public:
            Camera(float fov, float aspect, float near_clipping_plane, float far_clipping_plane);

            void LookAt(fVec3 pos, fVec3 front, fVec3 up);
            Mat4 GetProjectionMatrix();
            Mat4 GetViewMatrix();

        private:
            Mat4 m_viewMatrix { 1.0f };
            Mat4 m_projectionMatrix;
    };
}