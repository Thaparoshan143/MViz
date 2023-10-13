#pragma once

#include"../platforms/OpenGL_Base/OpenGL_Win.h"

namespace Sandbox 
{
    class Sandbox_Window : private OpenGL::OpenGL_Win 
    {
        Sandbox_Window() : OpenGL::OpenGL_Win() {}
    };
}