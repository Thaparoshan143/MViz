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
        String _text = "MViz Graph";
        FreetypeText _temp1(_text, "Sansita");
        FreetypeText _temp2(_text, "OpenSans");
        FreetypeText _temp3(_text, "RaceSport");
        uint _textShaderID = this->GetShaderID("../res/Shaders/Text/projbased/");
        Mat4 temp(1.0f);

        Abs::PanelProps sidePanelInfo(fVec2(-0.6,0), fVec2(0.8,2), fVec3(0.5), "Title", nullptr);
        Abs::PanelProps bottomPanelInfo(fVec2(0,-0.8), fVec2(2,0.4), fVec3(0.2), "Bottom", nullptr);
        Abs::PanelProps outerPanelProps(fVec2(0.6, 0), fVec2(0.8, 2), fVec3(1, 0.5, 0.2), "lavel", nullptr);
        Abs::PanelProps innerPanelProps(fVec2(0.65, 0), fVec2(0.7, 1.6), fVec3(1, 0, 0.2), "laaael", nullptr);

        Abs::ButtonProps _btnProps(fVec2(0.7, 0.5), fVec2(0.5, 0.2), fVec3(0, 0.5, 0), "Btn", nullptr);
        Abs::Button *_btn = new Abs::Button(_btnProps);
        Abs::ButtonProps _btnPropsBtn(fVec2(0.7, -0.5), fVec2(0.5, 0.2), fVec3(0, 0.5, 1), "Btn Hover", nullptr);
        Abs::Button *_btnBtn = new Abs::Button(_btnPropsBtn);

        Abs::Panel *innerPanel = new Abs::Panel(innerPanelProps);
        innerPanel->AttachElement(_btn);
        innerPanel->AttachElement(_btnBtn);
        Abs::Panel *outerPanel = new Abs::Panel(outerPanelProps);
        outerPanel->AttachElement(innerPanel);

        Abs::Panel *sidePanel = new Abs::Panel(sidePanelInfo);
        Abs::Panel *bottomPanel = new Abs::Panel(bottomPanelInfo);
        m_targetUI->AttachPanel("Side Panel", sidePanel);
        m_targetUI->AttachPanel("Bottom", bottomPanel);
        m_targetUI->AttachPanel("Nested Panel", outerPanel);

        // temporary right now here later move to the actual inherted applications..
        while (!m_targetWindow->ShouldCloseWindow())
        {
            m_targetWindow->SetColor(1, 1, 1, 1);
            mainGraph.RenderGraph();

            sine_VAO.Bind();
            sh.UseProgram();
            i += d_i;
            if (i > 1) {
                d_i = -d_i;
            }
            if (i < -1) {       
                d_i = -d_i;
            }

            // temp = glm::translate(fMat4(1.0), glm::fvec3(-1.0+i, 0, 0));
            // temp = glm::scale(fMat4(), glm::fvec3(1, i, 0));
            temp = glm::mat4(1.0);
            sh.SetUniformMat4("modal", temp);

            glLineWidth(1.0f);
            glDrawArrays(GL_LINE_STRIP_ADJACENCY, 0, sin_size);

            m_targetUI->Render();
            _temp1.RenderText(_textShaderID, 0, 0.9, 1.4, Color(0.6, 0, 0.5), false);
            _temp2.RenderText(_textShaderID, 0, 0.2, 1.8, Color(0, 1, 0.5), false);
            _temp3.RenderText(_textShaderID, 0, -0.5, 1.5, Color(0.6, 1, 0), false);

            m_targetWindow->SwapFrameBuffer();
            glfwPollEvents();
        }
    }


    void Sandbox_App::Initialize()
    {
        
    }
}