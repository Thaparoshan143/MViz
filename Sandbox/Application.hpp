#pragma once
#include"../platforms/OpenGL_Base/OpenGL_App.h"

#define FREQ_COUNT 5
// it is the total no of vertex count in single sine wave #note: hgher the number more better the curve
#define SINE_RES 20
#define SINE_AMP_Y 0.6

namespace Sandbox 
{
    // This are just temporary functions for test...
    void s_btnEvent1()
    {
        std::cout << "I am btn " << std::endl;
    }

    void s_btnEvent2(dVec2 mouPos, int mouCode)
    {
        static int count = 0;
        if(mouPos.x>500 && mouPos.y>400 && mouPos.x<800 && mouPos.y<600 && mouCode==MOUSE_BUTTON_LEFT)
        {
            count++;
            std::cout << "I am btn 2 event and triggered : " << count << std::endl;
        }
    }

    void s_btnEvent3(dVec2 mouPos, int mouCode)
    {
        static int count = 0;
        if(mouPos.x>500 && mouPos.y>400 && mouPos.x<800 && mouPos.y<600 && mouCode==MOUSE_BUTTON_RIGHT)
        {
            count++;
            std::cout << "I am btn 3 event and triggered : " << count << std::endl;
        }
    }

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

        FreetypeText tempText(*this->m_mainWindow, "0");

        // const int TRIANGLE_COUNT = 18;
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

        // OpenGL_Panel tempPanel;
        // OpenGL_Button tempButton;
        // OpenGL_InpField tempInputField;
        // m_mainWindow->m_mouEventQueue.AddEvent(s_btnEvent1);
        m_mainWindow->m_mouEventQueue.AddEvent(s_btnEvent2);
        m_mainWindow->m_mouEventQueue.AddEvent(s_btnEvent3);
        Abs::ButtonProps btnInfo1(fVec2(0), fVec2(0.3), fVec3(1), "Button 1");
        OpenGL_Button testBtn(btnInfo1, s_btnEvent1);


        // temporary right now here later move to the actual inherted applications..
        while (!m_mainWindow->ShouldCloseWindow())
        {
            m_mainWindow->SetColor(1, 1, 1, 1);
            // dVec2 mouPos = m_mainWindow->GetMousePos();
            // std::cout << mouPos.x << " | " << mouPos.y << std::endl;
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

            tempText.RenderText(shText, 380, 320, 0.7, dVec3(0, 0, 0));
            mainGraph.RenderGraph();

            m_mainWindow->SwapFrameBuffer();
            glfwPollEvents();
        }
    }


    void Sandbox_App::Initialize()
    {
        
    }
}