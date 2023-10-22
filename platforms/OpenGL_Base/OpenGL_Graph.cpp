#include"./OpenGL_Graph.h"

namespace OpenGL
{
    OpenGL_Graph::OpenGL_Graph(OpenGL_Win target, Abs::GraphInfo gi) : Abs::Graph(gi), m_target(target)
    {
        m_text = nullptr;
        m_VAO = OpenGL_VertArrObj(Abs::PPP_RGB);
    }
}