#include"./OpenGL_UI.h"

namespace OpenGL
{
    // panel implementation
    OpenGL_Panel::OpenGL_Panel(Abs::PanelProps panelInfo) : Panel(panelInfo)
    {
        std::cout << "I am inside the constructor Panel" << std::endl;
    }

    // button implementation
    OpenGL_Button::OpenGL_Button(Abs::ButtonProps btnInfo, Abs::ClickEventCallback btnCallback)
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
    OpenGL_InpField::OpenGL_InpField(Abs::InputFieldProps inpFieldInfo, Abs::ClickEventCallback inpFieldCallback)
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

    
}