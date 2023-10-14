#pragma once

#include<iostream>

#include"../../includes/GLM/glm/glm.hpp"

namespace Abs
{
    typedef std::string String;
    typedef glm::fvec2 fVec2;
    typedef glm::fvec3 fVec3;
    typedef void (*ClickEventCallback);

    class BaseUI
    {
        public:
        BaseUI(){}

        inline fVec2 GetPos() {    return m_pos;   }
        inline fVec2 GetDim() {    return m_dim;   }
        inline fVec3 GetBgCol() {    return m_bgCol;   }



        protected:
        fVec2 m_pos;
        fVec2 m_dim;
        fVec3 m_bgCol;
    };

    class Panel : private BaseUI
    {
        Panel()
        {
            this->m_pos = fVec2(0);
            this->m_dim = fVec2(0);
            this->m_bgCol = fVec3(0);
        }


    };

    class Button : private BaseUI
    {
        Button()
        {
            this->m_pos = fVec2(0);
            this->m_dim = fVec2(0.2);
            this->m_bgCol = fVec3(0);
            m_label = "Button";
            m_eventOnClick = nullptr;
            m_isClickable = true;
        }

        private:    
        String m_label;
        bool m_isClickable;
        ClickEventCallback m_eventOnClick;

    };

    class InputField : private BaseUI
    {
        InputField()
        {
            this->m_pos = fVec2(0);
            this->m_dim = fVec2(0.2);
            this->m_bgCol = fVec3(0);
            m_placeholder = "This is placeholder";
            m_text = "";
            m_eventOnChange = nullptr;
            m_isClickable = true;
        }

        inline String GetText() {  return m_text;  }

        private:    
        String m_placeholder;
        String m_text;
        bool m_isClickable;
        ClickEventCallback m_eventOnChange;

    };
}