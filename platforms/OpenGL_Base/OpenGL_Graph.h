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
        OpenGL_Graph(OpenGL_Win &target, Abs::GraphInfo gi);

        void RenderGraph();

        protected:
        OpenGL_VertArrObj m_VAO;
        OpenGL_VertBuffObj m_VBO;
        OpenGL_Sha m_graphSha;
        OpenGL_Sha m_textSha;
        OpenGL_Win &m_target;
        uint graphVBO, graphVAO;
        // std::vector<FreetypeText> m_number;

        void initializeGraph();
        float* getGraphVert(iVec2 stripeCount, float height);
        void renderNumbering();
    };
}
