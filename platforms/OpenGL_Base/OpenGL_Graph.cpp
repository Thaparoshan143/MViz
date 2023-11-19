#include"./OpenGL_Graph.h"

namespace OpenGL
{
    OpenGL_Graph::OpenGL_Graph(OpenGL_Win &target, Abs::GraphInfo gi) : Abs::Graph(gi), m_target(target), m_VAO(Abs::BufferFormat::PPP_RGB)
    {
        initializeGraph();
    }

    void OpenGL_Graph::RenderGraph()
    {
		glUseProgram(m_graphShaderID);
        m_VAO.Bind();
        m_VBO.Bind();
		glLineWidth(0.5f);
        glDrawArrays(GL_LINES, (this->m_gi.numinfo)*2, (this->m_gi.numinfo+this->m_gi.numinfo)*4);
		glLineWidth(1.0f);
        glDrawArrays(GL_LINES, 0, (this->m_gi.numinfo+this->m_gi.numinfo)*2);
		glLineWidth(2.0f);
        glDrawArrays(GL_LINES, (this->m_gi.numinfo+this->m_gi.numinfo)*4, (this->m_gi.numinfo+this->m_gi.numinfo)*4 + 8);
		renderLabeling();
		// renderNumbering();
    }

    void OpenGL_Graph::initializeGraph()
    {
        float *graphVert = getGraphVert(iVec2(this->m_gi.numinfo, this->m_gi.numinfo), 1);
        float *graphVertScale = getGraphVert(iVec2(this->m_gi.numinfo, this->m_gi.numinfo), 0.02);
		float graphAxis[] = {-1, 0, 1, 0, 0, 1, 0, -1};
		String *origin = new String("0");
		m_numberLabel.push_back(origin);
		m_number = new FreetypeText(m_target, *m_numberLabel[0]);

		m_VBO.Append(graphVertScale, (this->m_gi.numinfo+this->m_gi.numinfo)*4);
		m_VBO.Append(graphVert, (this->m_gi.numinfo+this->m_gi.numinfo)*4);
		m_VBO.Append(graphAxis, 8);
		m_VBO.LoadBuffer();
		m_VAO.EnableVertexAttribMan(2);
		m_textShaderID = m_target.GetShaderID("../res/Shaders/Text/");
		m_graphShaderID = m_target.GetShaderID("../res/Shaders/Graph/Plane/");
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

	// for now just rendering the origin i.e 0 below contains the required for all labeling but has scaling problem in vector find alternative...
	void OpenGL_Graph::renderLabeling()
	{
		OpenGL_Win *win = (OpenGL_Win*)glfwGetWindowUserPointer(m_target.GetWindow());
		iVec2 winSize = win->GetWindowSize();

		m_number->RenderText(m_textShaderID, (winSize.x/2)-20, (winSize.y/2)+20, 0.8, fVec3(0));
	}

	// NOT WORKING.. CURRENTLY
	// find the way to store the render text at once or to use vector for freetype...then it might work.. 
	// void OpenGL_Graph::renderNumbering()
	// {
	// 	// Populating the text first...
	// 	String textCount;
	// 	float numCount = -10;
	// 	float offset = 20.0/(this->m_gi.numinfo-1);

	// 	// X-axis numbering 
	// 	for(int i=0;i<this->m_gi.numinfo;i++)
	// 	{
	// 		textCount = std::to_string(numCount);
	// 		m_number.push_back(FreetypeText(m_target, textCount));
	// 		numCount += offset;
	// 	}

	// 	numCount = -10;
	// 	// Y-axis numbering
	// 	for(int i=0;i<this->m_gi.numinfo;i++)
	// 	{
	// 		textCount = std::to_string(numCount);
	// 		m_number.push_back(FreetypeText(m_target, textCount));
	// 		numCount += offset;
	// 	}

	// 	float numberingScale = 0.8f;
	// 	// black color text
	// 	fVec3 numberCol = fVec3(0);
	// 	float xOffset = 0, yOffset = 0, xIncrement, yIncrement;
	// 	OpenGL_Win *mainWin = (OpenGL_Win*)glfwGetWindowUserPointer(m_target.m_window);
	// 	iVec2 screenSize = mainWin->GetWindowSize();
	// 	// X render
	// 	yOffset = screenSize.y/2 + 20;
	// 	xIncrement = screenSize.x / this->m_gi.numinfo;
	// 	for(int i=0;i<m_number.size()/2+1;i++)
	// 	{
	// 		xOffset += xIncrement;
	// 		if(xOffset == screenSize.x/2)
	// 		{
	// 			xOffset += xIncrement;
	// 		}
	// 		m_number[i].RenderText(m_textSha, xOffset, yOffset, numberingScale, numberCol);
	// 	}
	// 	// Y render
	// 	xOffset = screenSize.x/2 - 20;
	// 	yOffset = 0;
	// 	for(int i=m_number.size()/2+1;i<m_number.size();i++)
	// 	{
	// 		yOffset += yIncrement;
	// 		if(yOffset == screenSize.y/2)
	// 		{
	// 			yOffset += yIncrement;
	// 		}
	// 		m_number[i].RenderText(m_textSha, xOffset, yOffset, numberingScale, numberCol);
	// 	}
	// }
}