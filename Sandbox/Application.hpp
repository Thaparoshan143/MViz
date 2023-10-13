#pragma once
#include"../platforms/OpenGL_Base/OpenGL_App.h"

#include"./Window.hpp"

#define FREQ_COUNT 5
#define SINE_RES 20

namespace Sandbox 
{
    class Sandbox_App : private OpenGL::OpenGL_App 
    {
        public:
        Sandbox_App() : OpenGL::OpenGL_App() {}
        Sandbox_App(ApplicationInfo &ai) : OpenGL::OpenGL_App(ai) {}

        void Initialize();
        void Loop();
    };

    void Sandbox_App::Loop()
    {
        using namespace OpenGL;

        // const int TRIANGLE_COUNT = 18;
        OpenGL_Sha sh("../res/Shaders/");
        sh.CreateProgram();
        sh.UseProgram();
        fMat4 temp;
        temp = glm::translate(fMat4(1.0), glm::fvec3(-1.0, 0, 0)) * glm::scale(fMat4(), glm::fvec3(2.0, 1.0, 1.0));
        sh.SetUniformMat4("modal", temp);
        sh.SetUniformVec3("fColor", glm::fvec3(1.0, 0.5, 0.2));

        float i=0.0f;
        // temporary right now here later move to the actual inherted applications..
        while (!this->m_mainWindow->ShouldCloseWindow())
        {
            i+=0.001f;
            if(i>1)
            {
                i=0.0f;
            }

            // temp = glm::translate(fMat4(1.0), glm::fvec3(-1.0+i, 0, 0));
            temp = glm::rotate(fMat4(), glm::radians(i*360.0f), glm::fvec3(1.0, 0.0, 0.0));
            sh.SetUniformMat4("modal", temp);
            m_mainWindow->SetColor(1, 1, 1, 1);

            // glDrawArrays(GL_TRIANGLES, 0, TRIANGLE_COUNT);
            glLineWidth(1.0f);
            glDrawArrays(GL_LINE_STRIP_ADJACENCY, 0, SINE_RES*(FREQ_COUNT*2+2));

            m_mainWindow->SwapFrameBuffer();
            glfwPollEvents();
        }
    }

    void Sandbox_App::Initialize()
    {
        using namespace OpenGL;
            // float boxVert[] = {
        // 	0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,		//0
        // 	-0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,	//1	
        // 	0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,	//2
        // 	// 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,		//0
        // 	// -0.8f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,	//1	
        // 	// 0.9f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,	//2
        // };

        float *boxVert = Util::_get_rect_ver3_col<float>(Util::fVec3(0), Util::fVec3(0.8), Util::fVec3(0.6));
        float *sineVert = Util::_get_sine_ver2(FREQ_COUNT);

        for(int i=0;i<=SINE_RES*FREQ_COUNT*1;i++)
        {
            std::cout << "x : " << *(sineVert+2*i) << "\t\t || y : " << *(sineVert+2*i+1) << std::endl;
        }

        uint VAO;
        OpenGL_VertBuff boxVertices;
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);
        // boxVertices.Bind();
        // boxVertices.Append(boxVert, 18);
        // boxVertices.LoadBuffer();
        boxVertices.DirectLoad(sineVert, SINE_RES*(FREQ_COUNT*2+2));
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (const void*)0);
        glEnableVertexAttribArray(0);
        // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (const void*)(sizeof(float)*3));
        // glEnableVertexAttribArray(1);
        free(boxVert);
    }
}
