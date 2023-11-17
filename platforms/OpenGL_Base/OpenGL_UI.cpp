#include"./OpenGL_UI.h"

namespace OpenGL
{
    #define BTN_TRI_COUNT 6
    // panel implementation
    OpenGL_Panel::OpenGL_Panel(Abs::PanelProps panelInfo) : Panel(panelInfo)
    {
        std::cout << "I am inside the constructor Panel" << std::endl;
    }

    // button implementation
    OpenGL_Button::OpenGL_Button(Abs::ButtonProps btnInfo, ClickEventCallback btnCallback)
    {
        this->m_pos = btnInfo._pos;
        this->m_dim = btnInfo._dim;
        this->m_bgCol = btnInfo._bgCol;

        // m_label.m_text = btnInfo._label;
        m_eventOnClick = btnCallback;
        m_isClickable = true;

        std::cout << "I am inside the constructor Button OpenGL" << std::endl;
    }

    void OpenGL_Button::OnClick(dVec2 mouPos, int mouCode)
    {
        // Currently on any mouse btn pressed it might be triggered if required with specific then expose property or check on logic..
        if(withinBoundary(GetBorder(this->m_pos, this->m_dim), mouPos) && mouCode>-1)
        {
            m_eventOnClick();
        }
    }

    bool OpenGL_Button::withinBoundary(fVec4 border, fVec2 pos)
    {
        return border.x < pos.x && border.z > pos.x && border.y < pos.y && border.w > pos.y;
    }

    // InputField implementation
    OpenGL_InpField::OpenGL_InpField(Abs::InputFieldProps inpFieldInfo, ClickEventCallback inpFieldCallback)
    {
        this->m_pos = inpFieldInfo._pos;
        this->m_dim = inpFieldInfo._dim;
        this->m_bgCol = inpFieldInfo._bgCol;
        // m_placeholder = inpFieldInfo._placeholder;
        // m_text = inpFieldInfo._text;
        m_eventOnChange = inpFieldCallback;
        m_isClickable = true;

        std::cout << "I am inside the constructor Input Field OpenGL" << std::endl;
    }

    OpenGL_UI::OpenGL_UI(OpenGL_Win &target, UIProps UIInfo) : m_target(target), m_UIShader("../res/Shaders/UI/")
    {
        this->initializeUIBuffer();
    }

    void OpenGL_UI::AddElement(OpenGL_Button btn, Abs::ButtonProps btnInfo)
    {

    }

    void OpenGL_UI::RenderUI()
    {
        this->m_UIVAO.Bind();
        this->m_UIVBO.Bind();
        this->m_UIShader.UseProgram();
        glDrawArrays(GL_TRIANGLES, 0, m_triangleCount);
    }

    // All the code to load buffer and also create submodule to facilitate the total ui creation here..
    void OpenGL_UI::initializeUIBuffer()
    {
        m_UIShader.CreateProgram();
        this->m_UIVAO.UpdateFormat(Abs::BufferFormat::PP_RGB);
        this->m_UIVBO.Append(getButtonVertices(fVec2(-0.5, -0.5), fVec2(0.2), fVec3(1,0.5,0.2)), PP_RGB_COUNT*BTN_TRI_COUNT);
        this->m_UIVBO.Append(getButtonVertices(fVec2(-0.5, 0), fVec2(0.2), fVec3(1,0.5,0.2)), PP_RGB_COUNT*BTN_TRI_COUNT);
        this->m_UIVBO.Append(getButtonVertices(fVec2(-0.5, 0.5), fVec2(0.2), fVec3(1,0.5,0.2)), PP_RGB_COUNT*BTN_TRI_COUNT);
        // float *temp = m_UIVBO.m_data.GetData();
        // std::cout << "BTN BUFFER TEST" << std::endl;
        // for(int i=0;i<m_UIVBO.m_data.GetCount();i++)
        // {
        //     std::cout << i+1 << " : " << *(temp+i) << std::endl;
        // }
        this->m_UIVBO.LoadBuffer(GL_STATIC_DRAW);
        this->m_UIVAO.EnableVertexAttrib();

        // At last finding the total triangle count to render on screen.
        m_triangleCount = this->m_UIVBO.m_data.GetCount()/(m_UIVAO.StrideCount());
        // std::cout << "Button tirangle count : " << m_triangleCount << std::endl;
    }

    float* OpenGL_UI::getButtonVertices(fVec2 pos, fVec2 dim, fVec3 col)
    {
        // the size of new is the size of one stride times the total no. of vertices required to draw rectangular by gldraw array method i.e 6 (2 triangle with 3 vertices each)
        float *temp = new float[PP_RGB_COUNT*BTN_TRI_COUNT];

		for(int i=0; i<BTN_TRI_COUNT;i++)
		{
			*(temp+PP_RGB_COUNT*i+2) = col.x;
			*(temp+PP_RGB_COUNT*i+3) = col.y;
			*(temp+PP_RGB_COUNT*i+4) = col.z;
		}

        // This vertices generation is on the -1 to 1 basis...
		float hw = dim.x/2;
		float hh = dim.y/2;

		temp[0] = pos.x - hw;
		temp[1] = pos.y - hh;

		temp[5] = temp[15] = pos.x - hw;
		temp[6] = temp[16] = pos.y + hh;

		temp[10] = temp[20] = pos.x + hw;
		temp[11] = temp[21] = pos.y - hh;

        temp[25] = pos.x + hw;
		temp[26] = pos.y + hh;

        // for(int i=0;i<30;i++)
        // {
        //     int count = -1;
        //     if(i%2==0)
        //     {
        //         count *= -1;
        //     }
        //     temp[i] = (i * count)/((i+1)/1.5);

        // }

		return temp;
    }
}