#include "../../Core/Base/Input.h"

namespace Abs {
    bool Input::IsMouseButtonPressed(OpenGL::OpenGL_Win& window, MouseCode button) {
        int state = glfwGetMouseButton(window.GetWindow(), static_cast<int>(button));
        return state == GLFW_PRESS;
    }

    iVec2 Input::GetMousePosition(OpenGL::OpenGL_Win& window, MouseCode button) {
        double xpos, ypos;
        glfwGetCursorPos(window.GetWindow(), &xpos, &ypos);
        return { xpos, ypos };
    }
}
