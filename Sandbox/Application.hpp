#pragma once
#include"../platforms/OpenGL_Base/OpenGL_App.h"

#define FREQ_COUNT 5
// it is the total no of vertex count in single sine wave #note: hgher the number more better the curve
#define SINE_RES 20
#define SINE_AMP_Y 0.6

namespace Sandbox 
{
    class Sandbox_App : private OpenGL::OpenGL_App 
    {
        public:
        Sandbox_App() : OpenGL::OpenGL_App() {}
        Sandbox_App(ApplicationInfo &ai) : OpenGL::OpenGL_App(ai) { }

        void Initialize() override;
        void Loop() override;
    };

    void Sandbox_App::Loop()
    {
        using namespace OpenGL;

        float *sineVert = Util::_get_sine_ver2(FREQ_COUNT, SINE_RES, SINE_AMP_Y);

        // uint sine_VAO;
        OpenGL_VertArrObj sine_VAO;
        OpenGL_VertBuffObj sine_VBO;
        sine_VBO.DirectLoad(sineVert, SINE_RES*(FREQ_COUNT*2+2));
        sine_VAO.EnableVertexAttribMan(2);

        OpenGL_Sha sh("../res/shaders/");
        OpenGL_Sha shText("../res/Shaders/Text/");
        shText.CreateProgram();
        sh.UseProgram();
        fMat4 temp;
        temp = glm::translate(fMat4(1.0), glm::fvec3(-1.0, 0, 0)) * glm::scale(fMat4(), glm::fvec3(2.0, 1.0, 1.0));
        sh.SetUniformMat4("modal", temp);
        sh.SetUniformVec3("fColor", glm::fvec3(1, 0.5, 0.2));
 
        fMat4 utemp;
        utemp = glm::translate(fMat4(1.0), glm::fvec3(1.0, 0.0, 0.0)) * glm::scale(fMat4(), glm::fvec3(2.0, 1.0, 1.0));

        float i = 0.0f;
        float d_i = 0.005f;

        Abs::GraphInfo graphInfo("Graph", m_mainWindow->GetWindowSize(), Abs::ScreenPosition::TOP_RIGHT, Abs::NumberingInfo::NORMAL);
        OpenGL_Graph mainGraph(*m_mainWindow, graphInfo);

        // temporary right now here later move to the actual inherted applications..
        while (!m_mainWindow->ShouldCloseWindow())
        {
            m_mainWindow->SetColor(1, 1, 1, 1);
            sine_VAO.Bind();
            sh.UseProgram();
            i += d_i;
            if (i > 1) {
                d_i = -d_i;
            }
            if (i < -1) {       
                d_i = -d_i;
            }

            temp = glm::translate(fMat4(1.0), glm::fvec3(-1.0+i, 0, 0));
            temp = glm::scale(fMat4(), glm::fvec3(1, i, 0));
            sh.SetUniformMat4("modal", temp);

            glLineWidth(1.0f);
            glDrawArrays(GL_LINE_STRIP_ADJACENCY, 0, SINE_RES*(FREQ_COUNT*2+2));

            m_mainUI->RenderUI();
            mainGraph.RenderGraph();

            m_mainWindow->SwapFrameBuffer();
            glfwPollEvents();
        }
    }


    void Sandbox_App::Initialize()
    {
        
    }
}