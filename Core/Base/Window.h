#pragma once

#include"../../includes/GLM/glm/glm.hpp"

#include<iostream>
#include<map>

typedef std::string String;
typedef glm::ivec2 iVec2;
typedef glm::dvec2 dVec2;

namespace Abs
{
    class Window
    {
        public:
        Window() {}

        virtual void SetActive() = 0;
        virtual inline bool ShouldCloseWindow() = 0;
        virtual void SetColor(float r, float g, float b, float a) = 0;
        virtual void SwapFrameBuffer() = 0;
        // virtual void WaitForSecond(double sec) = 0;
        
        protected:
        iVec2 m_winSize;
        dVec2 m_mouPos;
    };
}