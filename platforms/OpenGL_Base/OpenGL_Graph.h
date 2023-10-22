#pragma once

#include"../../Core/Base/Graph.h"
#include"./OpenGL_Sha.h"
#include"./OpenGL_Text.h"
#include"./OpenGL_Buff.h"

namespace OpenGL
{
    class OpenGL_Graph : public Abs::Graph
    {
        public:
        OpenGL_Graph(OpenGL_Win target, Abs::GraphInfo gi);

        protected:
        OpenGL_VertArrObj m_VAO;
        FreetypeText *m_text;
        OpenGL_Win &m_target;
    };
}
