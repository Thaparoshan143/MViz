#include"../platforms/OpenGL_Base/OpenGL_Graph.h"
#include"./Math/Calculator/calculator.cpp"

#define STEP_COUNT_OFFSET 0.015625

class MVizGraph : public OpenGL::OpenGL_Graph
{
    public:
    MVizGraph(OpenGL::OpenGL_Win &target, Abs::GraphInfo gi) : OpenGL_Graph(target, gi)
    {
        m_waveBuffer.reserve(1024);
        initializeBuffers();
    }

    ~MVizGraph()
    {
        m_waveBuffer.clear();
    }

    void Render()
    {
        // First rendering the graph itself..
        OpenGL_Graph::Render();

        m_waveVAO.Bind();
        m_waveVBO.Bind();
        glUseProgram(m_waveShaderID);
        glLineWidth(5.0f);
        glDrawArrays(GL_LINE_STRIP_ADJACENCY, 0, m_waveBuffer.size() / 2);
    }

    void SetExpression(String expression) override
    {
        if(expression.size()>0)
        {
            m_lastExpression = expression;
        }
        std::cout << "Set expression called with expression : " << expression << std::endl;
        m_waveBuffer = Calculate(expression, -1 * m_range, m_range, STEP_COUNT_OFFSET, m_range, true);
        reloadVBO();
    }

    protected:
    std::vector<float> m_waveBuffer;
    uint m_waveShaderID;
    OpenGL::OpenGL_VertArrObj m_waveVAO;
    OpenGL::OpenGL_VertBuffObj m_waveVBO;

    void reloadVBO()
    {
        float *tempVert = &m_waveBuffer[0];
        int vertSize = m_waveBuffer.size();
        m_waveVBO.DirectLoad(tempVert, vertSize);
    }

    void initializeBuffers()
    {
        m_waveVBO.Bind();
        m_waveVAO.Bind();
        m_waveVAO.EnableVertexAttribMan(2);

        OpenGL::OpenGL_Sha *waveSha = m_target.GetRawShader("../res/Shaders/Graph/Wave/");
        waveSha->UseProgram();
        m_waveShaderID = waveSha->GetProgramID();
        waveSha->SetUniformVec3("fColor", Color(1, 0.5, 0.2));
        waveSha->SetUniformMat4("modal", glm::mat4(5.0));
        // Giving the initial wave to start with
        m_range = 50;
        SetExpression("x^5 * (1/x^(x))");
    }
};
