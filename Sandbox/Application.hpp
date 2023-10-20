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

        uint sine_VAO;
        OpenGL_VertBuff sine_VBO;
        glGenVertexArrays(1, &sine_VAO);
        glBindVertexArray(sine_VAO);
        sine_VBO.DirectLoad(sineVert, SINE_RES*(FREQ_COUNT*2+2));
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (const void*)0);
        glEnableVertexAttribArray(0);

        FreetypeText tempText(*this->m_mainWindow, "Render Text");

        // const int TRIANGLE_COUNT = 18;
        OpenGL_Sha sh("../res/shaders/");
        OpenGL_Sha shText("../res/Shaders/Text/");
        shText.CreateProgram();
        sh.UseProgram();
        fMat4 temp;
        temp = glm::translate(fMat4(1.0), glm::fvec3(-1.0, 0, 0)) * glm::scale(fMat4(), glm::fvec3(2.0, 1.0, 1.0));
        sh.SetUniformMat4("modal", temp);
        sh.SetUniformVec3("fColor", glm::fvec3(1.0, 0.5, 0.2));

        fMat4 utemp;
        utemp = glm::translate(fMat4(1.0), glm::fvec3(1.0, 0.0, 0.0)) * glm::scale(fMat4(), glm::fvec3(2.0, 1.0, 1.0));

        float i=0.0f;
        float d_i = 0.001f;

        // temporary right now here later move to the actual inherted applications..
        while (!m_mainWindow->ShouldCloseWindow())
        {
            glBindVertexArray(sine_VAO);
            sh.UseProgram();
            i += d_i;
            if (i > 1) {
                d_i = -d_i;
            }
            if (i < -1) {
                d_i = -d_i;
            }

            // temp = glm::translate(fMat4(1.0), glm::fvec3(-1.0+i, 0, 0));
            temp = glm::scale(fMat4(), glm::fvec3(1, i, 0));
            sh.SetUniformMat4("modal", temp);
            m_mainWindow->SetColor(1, 1, 1, 1);

            // glDrawArrays(GL_TRIANGLES, 0, TRIANGLE_COUNT);
            glLineWidth(1.0f);
            glDrawArrays(GL_LINE_STRIP_ADJACENCY, 0, SINE_RES*(FREQ_COUNT*2+2));

            temp = glm::rotate(fMat4(), glm::radians(i*360.0f), glm::fvec3(1.0, 0.0, 0.0));

            sh.SetUniformMat4("modal", temp);

            // glDrawArrays(GL_TRIANGLES, 0, TRIANGLE_COUNT);
            glLineWidth(1.0f);
            glDrawArrays(GL_LINE_STRIP_ADJACENCY, 0, SINE_RES*(FREQ_COUNT*2+2));

            tempText.RenderText(shText, 400, 300, 1, dVec3(0, 0, 0));

            m_mainWindow->SwapFrameBuffer();
            glfwPollEvents();
        }
    }

    void Sandbox_App::Initialize()
    {
        
    }
}