#include"./OpenGL_Graph.h"

namespace OpenGL
{
    OpenGL_Graph::OpenGL_Graph(OpenGL_Win &target, Abs::NumberingScale gi) : Abs::Graph(gi), m_VAO(Abs::BufferFormat::PP), m_target(target)
    {
        initializeGraph();
    }

    void OpenGL_Graph::Render()
    {
		glUseProgram(m_graphShaderID);
        m_VAO.Bind();
        m_VBO.Bind();
		glLineWidth(1.0f);
        glDrawArrays(GL_LINES, 0, (this->m_numScale+this->m_numScale)*2);
		glLineWidth(0.5f);
        glDrawArrays(GL_LINES, (this->m_numScale)*2, (this->m_numScale+this->m_numScale)*4);
		glLineWidth(2.0f);
        glDrawArrays(GL_LINES, (this->m_numScale+this->m_numScale)*4, (this->m_numScale+this->m_numScale)*4 + 8);
		renderLabeling();
    }

    void OpenGL_Graph::initializeGraph()
    {
        float *graphVert = getGraphVert(iVec2(this->m_numScale, this->m_numScale), 1);
        float *graphVertScale = getGraphVert(iVec2(this->m_numScale, this->m_numScale), 0.02);
		float graphAxis[] = {-1, 0, 1, 0, 0, 1, 0, -1};
		m_range = 25;
		m_numberLabel.push_back(String(std::to_string(0)));
		m_numberLabel.push_back(String(std::to_string(-m_range)));
		m_numberLabel.push_back(String(std::to_string(m_range)));
		m_numberLabel.push_back(String(std::to_string(m_range)));
		m_numberLabel.push_back(String(std::to_string(-m_range)));

		FreetypeText::UpdateTarget(m_target.GetWindow());
		for(int i=0;i<m_numberLabel.size();i++)
		{
			FreetypeText *temp = new FreetypeText(m_numberLabel[i]);
			m_labelList.push_back(temp);
		}
		m_VBO.Append(graphVertScale, (this->m_numScale+this->m_numScale)*4);
		m_VBO.Append(graphVert, (this->m_numScale+this->m_numScale)*4);
		m_VBO.Append(graphAxis, 8);
		m_VBO.LoadBuffer();
		m_VAO.EnableVertexAttribMan(2);
		m_textShaderID = m_target.GetShaderID("../res/Shaders/Text/");
		m_graphShaderID = m_target.GetShaderID("../res/Shaders/Graph/Plane/");

		delete[] graphVert;
		delete[] graphVertScale;
    }

	float* OpenGL_Graph::getGraphVert(iVec2 stripeCount, float height)
	{
		float *tempVert = new float[stripeCount.x*4+stripeCount.y*4];
		fVec2 offset = fVec2(2.0/(stripeCount.x+1), (2.0/(stripeCount.y+1)));
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

	void OpenGL_Graph::renderLabeling()
	{
		// Here for the text rendering position is hardcoded...
		m_labelList[0]->RenderText(m_textShaderID, -0.02, -0.04, 0.5, fVec3(LABEL_COL), false);
		for(int i=1;i<m_labelList.size();i++)
		{
			if(i==1 || i==2)
			{
				m_labelList[i]->RenderText(m_textShaderID, pow(-1, i) * 0.97, -0.05, 0.6, fVec3(LABEL_COL), false);
			}
			else if(i==3 || i==4)
			{
				m_labelList[i]->RenderText(m_textShaderID, -0.04, pow(-1, i) * -0.97, 0.6, fVec3(LABEL_COL), false);
			}
		}
	}
}