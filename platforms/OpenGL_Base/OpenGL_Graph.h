#pragma once

#include"../../Core/Base/Graph.h"
#include"./OpenGL_Text.h"
#include"./OpenGL_Buff.h"

#define RANGE_MUL_FACTOR 5
#define LABEL_COL 0

namespace OpenGL
{
    class OpenGL_Graph : public Abs::Graph
    {
        public:
        OpenGL_Graph(OpenGL_Win &target, Abs::NumberingScale numScale);

        virtual void Render();
        virtual void SetExpression(String exp) = 0;
        String GetLastExpression() {    return m_lastExpression;    }
        void SetRange(int range) {  m_range = range*RANGE_MUL_FACTOR;    m_numberLabel[1] = std::to_string(-m_range);  m_numberLabel[2] = std::to_string(m_range);  m_numberLabel[3] = std::to_string(m_range);  m_numberLabel[4] = std::to_string(-m_range);   }
        virtual void ScaleWaveBuffer(int range) = 0;

        protected:
        OpenGL_VertArrObj m_VAO;
        OpenGL_VertBuffObj m_VBO;
        uint m_textShaderID, m_graphShaderID;
        OpenGL_Win &m_target;
        std::vector<FreetypeText*> m_labelList;
        String m_lastExpression;
        int m_range;

        void initializeGraph();
        float* getGraphVert(iVec2 stripeCount, float height);
        void renderLabeling();
    };
}
