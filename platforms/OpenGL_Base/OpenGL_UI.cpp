#include"./OpenGL_UI.h"

namespace OpenGL
{
    // panel implementation
    OpenGL_Panel::OpenGL_Panel(Abs::PanelProps panelInfo) : Panel(panelInfo)
    {
        std::cout << "New Panel Created" << std::endl;
    }

    // button implementation
    OpenGL_Button::OpenGL_Button(Abs::ButtonProps btnInfo) : Button(btnInfo)
    {
        std::cout << "New Button Created" << std::endl;
    }

    // InputField implementation
    OpenGL_InpField::OpenGL_InpField(Abs::InputFieldProps inpFieldInfo) : InputField(inpFieldInfo)
    {
        std::cout << "I am inside the constructor Input Field OpenGL" << std::endl;
    }

    OpenGL_UI::OpenGL_UI(OpenGL_Win *target)
    {
        m_targetWindow = (OpenGL_Win*)target;
        this->initializeUIBuffer();
    }

    void OpenGL_UI::Render()
    {
        this->m_UIVAO.Bind();
        this->m_UIVBO.Bind();
        glUseProgram(m_UIShaderID);
        glDrawArrays(GL_TRIANGLES, 0, m_triangleCount);
        // renderBtnText();
        // renderInpFieldText();
    }

    // void OpenGL_UI::DispatchMouseEvents(dVec2 mouRef, int mouCode)
    // {
    //     // Normalize mouseRefernce position
	// 	OpenGL_Win *win = (OpenGL_Win*)glfwGetWindowUserPointer(m_targetWindow.GetWindow());
    //     iVec2 winSize = win->GetWindowSize();

    //     dVec2 normalizeMouPos = dVec2((mouRef.x-(winSize.x/2.0))/(winSize.x/2.0),(-mouRef.y+(winSize.y/2.0))/(winSize.y/2.0));
    //     m_isSubscriberActive = false;
    //     // m_mouseEventQueue.DispatchEvents(mouRef, keyCode);
    //     for(int i=0;i<m_btnList.size();i++)
    //     {
    //         m_btnList[i]->OnClick(normalizeMouPos, mouCode);
    //     }
    //     for(int i=0;i<m_inpFieldList.size();i++)
    //     {
    //         if(m_inpFieldList[i]->OnClick(normalizeMouPos, mouCode))
    //         {
    //             m_isSubscriberActive = true;
    //             m_targetWindow.SetKeySubscriber(m_inpFieldList[i]->GetRawText());
    //         }
    //     }
    //     if(!m_isSubscriberActive)
    //     {
    //         m_targetWindow.SetKeySubscriber(nullptr);
    //     }
    // }

    // void OpenGL_UI::DispatchKeyboardEvent(int keyCode)
    // {
    //     m_lastKeyValue += char(keyCode);
    //     if(m_keySubscriber!=nullptr)
    //     {
    //         *m_keySubscriber = String(m_lastKeyValue);
    //     }
    // }


    // All the code to load buffer and also create submodule to facilitate the total ui creation here..
    void OpenGL_UI::initializeUIBuffer()
    {
        this->m_UIVAO.UpdateFormat(Abs::BufferFormat::PP_RGB);
        OpenGL_Win *mainWin = (OpenGL_Win*)m_targetWindow;
        m_UIShaderID = mainWin->GetShaderID("../res/Shaders/UI/");
        m_textShaderID = mainWin->GetShaderID("../res/Shaders/Text/projbased/");
        this->m_UIVAO.EnableVertexAttrib();

        // At last finding the total triangle count to render on screen.
        updateTriangleCount();
    }

    float* OpenGL_UI::getQuadVertices(fVec2 pos, fVec2 dim, fVec3 col)
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

    void OpenGL_UI::updateTriangleCount()
    {
        m_triangleCount = this->m_UIVBO.m_data.GetCount()/(m_UIVAO.StrideCount());
    }
}