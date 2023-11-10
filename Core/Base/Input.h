#pragma once

#include "KeyCodes.h"
#include "MouseEvent.h"

namespace Abs {
    class Input {
        public:
            static bool IsKeyPressed(KeyCode key);
            static bool IsKeyReleased(KeyCode key);
    };
}