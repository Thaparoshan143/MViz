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
        glDrawArrays(GL_LINES, 0, (HOR_LINE_COUNT+VER_LINE_COUNT)*4);
    }

    void OpenGL_Graph::initializeGraph()
    {
        float *boxVertices = getGraphVert(iVec2(HOR_LINE_COUNT, VER_LINE_COUNT));

        m_VAO.Bind();
        m_VBO.Bind();
        glBufferData(GL_ARRAY_BUFFER, sizeof(float)*(HOR_LINE_COUNT+VER_LINE_COUNT)*4, boxVertices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (const void*)0);
        glEnableVertexAttribArray(0);  
    }

	float* OpenGL_Graph::getGraphVert(iVec2 stripeCount)
	{
		float *tempVert = new float[stripeCount.x*4+stripeCount.y*4];
		fVec2 offset = fVec2(2.0/(stripeCount.x+1), 2.0/(stripeCount.y+1));
		float counter = float(-1);

		for(uint i=0;i<stripeCount.x;i++)
		{
			counter += offset.x;
			*(tempVert+4*i) = *(tempVert+4*i+2) = counter;
			*(tempVert+4*i+1) = 1;
			*(tempVert+4*i+3) = -1;
		}
		counter = float(-1);
        uint ptrOffset = 4*stripeCount.x;
		for(uint i=0;i<stripeCount.y;i++)
		{
			counter += offset.y;
			*(tempVert+4*i+1 + ptrOffset) = *(tempVert+4*i+3 + ptrOffset) = counter;
			*(tempVert+4*i + ptrOffset) = -1;
			*(tempVert+4*i+2 + ptrOffset) = 1;
		}

		return tempVert;
	}
}