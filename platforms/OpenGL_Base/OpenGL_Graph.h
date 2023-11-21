#pragma once

#include"../../Core/Base/Graph.h"
#include"./OpenGL_Text.h"
#include"./OpenGL_Buff.h"

namespace OpenGL
{
    class OpenGL_Graph : public Abs::Graph
    {
        public:
        OpenGL_Graph(OpenGL_Win &target, Abs::GraphInfo gi);

        void RenderGraph();

        protected:
        OpenGL_VertArrObj m_VAO;
        OpenGL_VertBuffObj m_VBO;
        uint m_textShaderID, m_graphShaderID;
        OpenGL_Win &m_target;
        FreetypeText *m_number;

        void initializeGraph();
        float* getGraphVert(iVec2 stripeCount, float height);
        void renderLabeling();
    };
}
