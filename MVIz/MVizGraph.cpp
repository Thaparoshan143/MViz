#include"../platforms/OpenGL_Base/OpenGL_Graph.h"
#include"./Math/Calculator/calculator.cpp"

#define STEP_COUNT_OFFSET 0.015625

class MVizGraph : public OpenGL::OpenGL_Graph
{
    public:
    MVizGraph(OpenGL::OpenGL_Win &target, Abs::NumberingScale numScale) : OpenGL_Graph(target, numScale)
    {
         initializeBuffers();
    }

    ~MVizGraph()
    {
        m_waveBuffMap.clear();
    }

    void Render()
    {
        OpenGL_Graph::Render();

        static int index = 0, starting = 0;
        m_waveVAO.Bind();
        m_waveVBO.Bind();
        glUseProgram(m_waveShaderID);
        glLineWidth(5.0f);
        for(auto &item : m_waveBuffMap)
        {
            if(item.second.size()==0)
                continue;
		    glUniform3f(m_colLocation, index==0, index==1, index==2);
            glDrawArrays(GL_LINE_STRIP_ADJACENCY, starting, (item.second.size()/2));
            starting += (item.second.size()/2);
            index++;
        }
        starting = 0;
        index = 0;
    }

    void SetExpression(Abs::InputField *field, String expression) override
    {
        if(expression.size()>0)
        {
            m_lastExpression = expression;
        }
        else
        {
            reloadVBO();
            return;
        }
        std::cout << "Set expression called with expression : " << expression << std::endl;
        if(m_waveBuffMap.count(field)!=0)
        {
            std::cout << "==> Modifying existing field" << std::endl;
            m_waveBuffMap[field] = Calculate(expression, -1 * m_range, m_range, STEP_COUNT_OFFSET, m_range, true);
            m_waveExpMap[field] = expression;
        }
        else
        {
            std::cout << "==> Inserting new field" << std::endl;
            m_waveBuffMap.insert({ field, Calculate(expression, -1 * m_range, m_range, STEP_COUNT_OFFSET, m_range, true) });
            m_waveExpMap.insert({ field, expression });
        }
        reloadVBO();
    }

    void ReloadExpression() override
    {
        for(auto &item : m_waveExpMap)
        {
            SetExpression(item.first, item.second);
        }
    }

    protected:
    uint m_waveShaderID;
    uint m_colLocation;
    OpenGL::OpenGL_VertArrObj m_waveVAO;
    OpenGL::OpenGL_VertBuffObj m_waveVBO;

    void reloadVBO()
    {
        Abs::SfVec newWaveBuffer(1024*3);

        for(auto &item : m_waveBuffMap)
        {
            float *temp = &item.second[0];
            if(item.second.size()!=0)
            newWaveBuffer.Append(temp, item.second.size());
        }

        m_waveVBO.DirectLoad(newWaveBuffer.GetData(), newWaveBuffer.GetCount());
    }

    void initializeBuffers()
    {
        m_waveVBO.Bind();
        m_waveVAO.Bind();
        m_waveVAO.EnableVertexAttribMan(2);

        OpenGL::OpenGL_Sha *waveSha = m_target.GetRawShader("../res/Shaders/Graph/Wave/");
        waveSha->UseProgram();

        m_waveShaderID = waveSha->GetProgramID();
        m_colLocation = glGetUniformLocation(m_waveShaderID, "fColor");
        waveSha->SetUniformVec3("fColor", Color(1, 0.5, 0.2));
        waveSha->SetUniformMat4("modal", glm::mat4(1.0));
    }
};
