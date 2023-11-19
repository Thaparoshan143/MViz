#include"./OpenGL_UI.h"

namespace OpenGL
{
    #define BTN_TRI_COUNT 6

    static void _submit_btn()
    {
        std::cout << "Hellow there i am submit button" << std::endl;
    }

    static void _cancel_btn()
    {
        std::cout << "Hellow there i am cancel button" << std::endl;
    }

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

        m_label = btnInfo._label;
        m_eventOnClick = btnCallback;
        m_isClickable = true;
    }

    void OpenGL_Button::OnClick(dVec2 mouPos, int mouCode)
    {
        // Currently on any mouse btn pressed it might be triggered if required with specific then expose property or check on logic..
        if(withinBoundary(GetBorder(this->m_pos, this->m_dim), mouPos) && mouCode>-1)
        {
            if(m_eventOnClick!=nullptr)
            {
                m_eventOnClick();
            }
            else
            std::cout << "Event call is not assigned!!" << std::endl;
        }
    }

    bool OpenGL_Button::withinBoundary(fVec4 border, fVec2 pos)
    {
        return border.x < pos.x && border.z > pos.x && border.y > pos.y && border.w < pos.y;
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

    OpenGL_UI::OpenGL_UI(OpenGL_Win &target, UIProps UIInfo) : m_target(target)
    {
        this->initializeUIBuffer();
    }

    void OpenGL_UI::AddElement(Abs::ButtonProps btnInfo, ClickEventCallback btnCallback)
    {
        OpenGL_Button *newBtn = new OpenGL_Button(btnInfo, btnCallback);
        m_btnList.push_back(newBtn);
        FreetypeText *newBtnLabel = new FreetypeText(m_target, btnInfo._label);
        m_btnLabelList.push_back(newBtnLabel);
        m_UIVBO.Append(getButtonVertices(btnInfo._pos, btnInfo._dim, btnInfo._bgCol), PP_RGB_COUNT*BTN_TRI_COUNT);
        this->m_UIVBO.LoadBuffer(GL_DYNAMIC_DRAW);

        m_triangleCount = this->m_UIVBO.m_data.GetCount()/(m_UIVAO.StrideCount());
    }

    void OpenGL_UI::RenderUI()
    {
        this->m_UIVAO.Bind();
        this->m_UIVBO.Bind();
        glUseProgram(m_UIShaderID);
        glDrawArrays(GL_TRIANGLES, 0, m_triangleCount);
        renderBtnText();
    }

    void OpenGL_UI::DispatchMouseEvents(dVec2 mouRef, int keyCode)
    {
        // Normalize mouseRefernce position
		OpenGL_Win *win = (OpenGL_Win*)glfwGetWindowUserPointer(m_target.GetWindow());
        iVec2 winSize = win->GetWindowSize();

        dVec2 normalizeMouPos = dVec2((mouRef.x-(winSize.x/2.0))/(winSize.x/2.0),(-mouRef.y+(winSize.y/2.0))/(winSize.y/2.0));

        // m_mouseEventQueue.DispatchEvents(mouRef, keyCode);
        for(int i=0;i<m_btnList.size();i++)
        {
            m_btnList[i]->OnClick(normalizeMouPos, keyCode);
        }
    }

    void OpenGL_UI::renderBtnText()
    {
        iVec2 winDim = m_target.GetWindowSize();
        fVec2 btnPos, btnScreenPos;
        for(int i=0;i<m_btnList.size();i++)
        {
            btnPos = m_btnList[i]->GetPos();
            btnScreenPos = fVec2(btnPos.x*(winDim.x/2.0)+winDim.x/2.0, -1*btnPos.y*(winDim.y/2.0)+winDim.y/2.0);
            // Adjusting the x offset and y offset to get better position of text render
            btnScreenPos.x -= (BTN_LABEL_OFFSET*m_btnList[i]->GetLabel().size());
            btnScreenPos.y += (BTN_LABEL_OFFSET*BTN_LABEL_OFFSET*m_btnList[i]->GetDim().y);
            m_btnLabelList[i]->RenderText(m_textShaderID, btnScreenPos.x, btnScreenPos.y, BTN_FONT_SIZE, Color(1));
        }
    }

    // All the code to load buffer and also create submodule to facilitate the total ui creation here..
    void OpenGL_UI::initializeUIBuffer()
    {
        this->m_UIVAO.UpdateFormat(Abs::BufferFormat::PP_RGB);
        m_UIShaderID = m_target.GetShaderID("../res/Shaders/UI/");
        m_textShaderID = m_target.GetShaderID("../res/Shaders/Text/");
        Abs::ButtonProps submitBtn(fVec2(0.5), fVec2(0.2), fVec3(0, 1, 0), "Submit");
        Abs::ButtonProps cancelBtn(fVec2(-0.5), fVec2(0.2), fVec3(1, 0, 0), "Cancel");
        Abs::ButtonProps optionBtn(fVec2(0.5, -0.5), fVec2(0.2), fVec3(0, 0, 1), "Option");
        AddElement(cancelBtn, _cancel_btn);
        AddElement(submitBtn, _submit_btn);
        AddElement(optionBtn, nullptr);
        this->m_UIVAO.EnableVertexAttrib();

        // At last finding the total triangle count to render on screen.
        m_triangleCount = this->m_UIVBO.m_data.GetCount()/(m_UIVAO.StrideCount());
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

		return temp;
    }
}