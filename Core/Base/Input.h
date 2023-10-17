#pragma once

#include"./Types.h"
#include"./MouseCode.h"
#include"../../platforms/OpenGL_Base/OpenGL_Win.h"

namespace Abs {
    class Input {
        public:
            static bool IsMouseButtonPressed(OpenGL::OpenGL_Win& window, MouseCode button);
            static iVec2 GetMousePosition(OpenGL::OpenGL_Win& window, MouseCode button);
    };
}
