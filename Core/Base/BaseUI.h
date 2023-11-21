#pragma once

#include<iostream>

#include"./Types.h"

typedef void (*ClickEventCallback)();

namespace Abs
{
    struct ButtonProps
    {
        public:
        ButtonProps(fVec2 p, fVec2 d, fVec3 bc, String l)
        {
            _pos = p;
            _dim = d;
            _bgCol = bc;
            _label = l;
        }

        fVec2 _pos, _dim;
        fVec3 _bgCol;
        String _label;
    };

    struct PanelProps
    {
        public:
        PanelProps(fVec2 p, fVec2 d, fVec3 bc)
        {
            _pos = p;
            _dim = d;
            _bgCol = bc;
        }

        fVec2 _pos, _dim;
        fVec3 _bgCol;
    };

    struct InputFieldProps
    {
        public:
        InputFieldProps(fVec2 p, fVec2 d, fVec3 bc, String t)
        {
            _pos = p;
            _dim = d;
            _bgCol = bc;
            _text = t;
        }

        fVec2 _pos, _dim;
        fVec3 _bgCol;
        String _text;
    };

    class BaseUI
    {
        public:
        BaseUI(){}

        inline fVec2 GetPos() {    return m_pos;   }
        inline fVec2 GetDim() {    return m_dim;   }
        inline fVec3 GetBgCol() {    return m_bgCol;   }

        // figure out which scale using either -1 to 1 or the screen real scale to return the actual working border point..
        // for now returning for -1 to 1 scale state.. review for future
        static fVec4 GetBorder(fVec2 pos, fVec2 dim)
        {
            // returing the x and y cordinates to check whether the mouse is withing the boundry region or not..
            return fVec4(pos.x-dim.x/2.0, pos.y+dim.y/2.0, pos.x+dim.x/2.0, pos.y-dim.y/2.0);
        }

        static bool withinBoundary(fVec4 border, fVec2 pos)
        {
            return border.x < pos.x && border.z > pos.x && border.y > pos.y && border.w < pos.y;
        }

        fVec2 m_pos;
        fVec2 m_dim;
        fVec3 m_bgCol;
    };

    class Panel : public BaseUI
    {
        public:
        Panel()
        {
            this->m_pos = fVec2(0);
            this->m_dim = fVec2(0);
            this->m_bgCol = fVec3(0);
        }

        Panel(PanelProps panInfo)
        {
            this->m_pos = panInfo._pos;
            this->m_dim = panInfo._dim;
            this->m_bgCol = panInfo._bgCol;
        }
    };

    class Button : public BaseUI
    {
        public:
        Button()
        {
            this->m_pos = fVec2(0);
            this->m_dim = fVec2(0.2);
            this->m_bgCol = fVec3(0);
            m_eventOnClick = nullptr;
            m_isClickable = true;
        }
        
        bool m_isClickable;
        ClickEventCallback m_eventOnClick;
    };

    class InputField : public BaseUI
    {
        public:
        InputField()
        {
            this->m_pos = fVec2(0);
            this->m_dim = fVec2(0.2);
            this->m_bgCol = fVec3(0);
            m_eventOnChange = nullptr;
            m_isClickable = true;
        }
        
        bool m_isClickable;
        ClickEventCallback m_eventOnChange;
    };
}