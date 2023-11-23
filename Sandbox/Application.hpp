#pragma once
#include"../platforms/OpenGL_Base/OpenGL_App.h"
#include"../platforms/OpenGL_Base/OpenGL_Graph.h"
#include"../MViz/Math/Calculator/calculator.cpp"

#define FREQ_COUNT 5
// it is the total no of vertex count in single sine wave #note: hgher the number more better the curve
#define SINE_RES 20
#define SINE_AMP_Y 0.6

namespace Sandbox 
{
    class Sandbox_App : private OpenGL::OpenGL_App 
    {
        public:
        Sandbox_App(ApplicationInfo &ai) : OpenGL::OpenGL_App(ai) { }

        void Initialize() override;
        void Loop() override;
    };

    void Sandbox_App::Loop()
    {
        using namespace OpenGL;

        // float *sineVert = Util::_get_sine_ver2(FREQ_COUNT, SINE_RES, SINE_AMP_Y);
        std::vector<float> sin_temp = Calculate("x", -10, 10, 0.02, 5, true);

        // std::vector<float> container;
        // int index = 0;

        // for (float i = -1; i <= 1; i += 0.002) {
        //     container.push_back(i);
        //     container.push_back(sin_temp[index]);
        //     index++;
        // }

        // float *sineVert = &container[0];
        // int sin_size = container.size();

        float *sineVert = &sin_temp[0];
        int sin_size = sin_temp.size();

        // uint sine_VAO;
        OpenGL_VertArrObj sine_VAO;
        OpenGL_VertBuffObj sine_VBO;
        sine_VBO.DirectLoad(sineVert, sin_size);
        sine_VAO.EnableVertexAttribMan(2);

        OpenGL_Sha sh("../res/Shaders/");
        sh.UseProgram();
        sh.SetUniformVec3("fColor", glm::fvec3(1, 0.5, 0.2));
 
        float i = 0.0f;
        float d_i = 0.005f;

        Abs::GraphInfo graphInfo("Graph", m_targetWindow->GetWindowSize(), Abs::ScreenPosition::TOP_RIGHT, Abs::NumberingScale::NORMAL);
        OpenGL_Graph mainGraph(*m_targetWindow, graphInfo);
        String _text = "Normalized Text";
        FreetypeText _temp(_text, "Sansita");
        uint _textShaderID = this->GetShaderID("../res/Shaders/Text/projbased/");
        // temporary right now here later move to the actual inherted applications..
        while (!m_targetWindow->ShouldCloseWindow())
        {
            m_targetWindow->SetColor(1, 1, 1, 1);
            mainGraph.RenderGraph();
            
            // sine_VAO.Bind();
            // sh.UseProgram();
            // i += d_i;
            // if (i > 1) {
            //     d_i = -d_i;
            // }
            // if (i < -1) {       
            //     d_i = -d_i;
            // }

            // // temp = glm::translate(fMat4(1.0), glm::fvec3(-1.0+i, 0, 0));
            // // temp = glm::scale(fMat4(), glm::fvec3(1, i, 0));
            // temp = glm::mat4(1.0);
            // sh.SetUniformMat4("modal", temp);

            // glLineWidth(1.0f);
            // glDrawArrays(GL_LINE_STRIP_ADJACENCY, 0, sin_size);

            // _temp.RenderText(_textShaderID, 400, 300, 1, Color(0));
            // m_targetUI->Render();

            m_targetWindow->SwapFrameBuffer();
            glfwPollEvents();
        }
    }


    void Sandbox_App::Initialize()
    {
        
    }
}