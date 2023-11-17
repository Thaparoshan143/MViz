#pragma once

#include"../../Core/Base/Types.h"
#include"../../Core/Base/MouseEvent.h"
#include"../../Core/Base/KeyEvent.h"

#include"../../includes/GLAD/glad.h"
#include"../../includes/GLFW/glfw3.h"

#include<vector>

namespace OpenGL 
{
    #define MOUSE_BUTTON_LEFT GLFW_MOUSE_BUTTON_LEFT        // 0
    #define MOUSE_BUTTON_RIGHT GLFW_MOUSE_BUTTON_RIGHT      // 1
    #define MOUSE_BUTTON_MIDDLE GLFW_MOUSE_BUTTON_MIDDLE    // 2

    template<class T, class U>
    class EventQueue
    {
        public:
        EventQueue() {}
        void AddEvent(void (*event)(T refVal, U keyCode))
        {
            m_root.push_back(event);
        }

        void DispatchEvents(T refVal, U keyCode)
        {
            for(auto event : m_root)
            { 
                event(refVal, keyCode);
            }
        }

        ~EventQueue() {}

        private:
        std::vector<void(*)(T refVal, U keyCode)> m_root;
    };  
}
