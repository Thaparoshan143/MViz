#include"./OpenGL_Graph.h"

#define HOR_LINE_COUNT 21
#define VER_LINE_COUNT 21

namespace OpenGL
{
    OpenGL_Graph::OpenGL_Graph(OpenGL_Win &target, Abs::GraphInfo gi) : Abs::Graph(gi), m_target(target), m_graphSha("../res/Shaders/Graph/Plane/"), m_VAO(Abs::BufferFormat::PPP_RGB)
    {
        initializeGraph();
    }

    void OpenGL_Graph::RenderGraph()
    {
        m_graphSha.UseProgram();
        m_VAO.Bind();
        m_VBO.Bind();
		glLineWidth(1.0f);
        glDrawArrays(GL_LINES, 0, (HOR_LINE_COUNT+VER_LINE_COUNT)*2);
		glLineWidth(0.3f);
        glDrawArrays(GL_LINES, (HOR_LINE_COUNT+VER_LINE_COUNT)*2, (HOR_LINE_COUNT+VER_LINE_COUNT)*4);
    }

    void OpenGL_Graph::initializeGraph()
    {
        float *graphVert = getGraphVert(iVec2(HOR_LINE_COUNT, VER_LINE_COUNT), 1);
        float *graphVertScale = getGraphVert(iVec2(HOR_LINE_COUNT, VER_LINE_COUNT), 0.02);

		m_VBO.Append(graphVertScale, (HOR_LINE_COUNT+VER_LINE_COUNT)*4);
		m_VBO.Append(graphVert, (HOR_LINE_COUNT+VER_LINE_COUNT)*4);
		m_VBO.LoadBuffer();
		m_VAO.EnableVertexAttribMan(2);
    }

	float* OpenGL_Graph::getGraphVert(iVec2 stripeCount, float height)
	{
		float *tempVert = new float[stripeCount.x*4+stripeCount.y*4];
		fVec2 offset = fVec2(2.0/(stripeCount.x+1), 2.0/(stripeCount.y+1));
		float counter = float(-1);

		for(uint i=0;i<stripeCount.x;i++)
		{
			counter += offset.x;
			*(tempVert+4*i) = *(tempVert+4*i+2) = counter;
			*(tempVert+4*i+1) = height;
			*(tempVert+4*i+3) = -height;
		}
		counter = float(-1);
        uint ptrOffset = 4*stripeCount.x;
		for(uint i=0;i<stripeCount.y;i++)
		{
			counter += offset.y;
			*(tempVert+4*i+1 + ptrOffset) = *(tempVert+4*i+3 + ptrOffset) = counter;
			*(tempVert+4*i + ptrOffset) = -height;
			*(tempVert+4*i+2 + ptrOffset) = height;
		}

		return tempVert;
	}
}