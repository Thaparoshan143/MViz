#pragma once

#include"../../Core/Base/Types.h"
#include"../../Core/Base/BaseUI.h"
// Include once firgured out how the target is binded...
// #include"./OpenGL_Text.h"

namespace OpenGL
{
    class OpenGL_Panel : public Abs::Panel 
    {
        public:
        OpenGL_Panel(Abs::PanelProps panelInfo);

        private:
    };

    class OpenGL_Button : public Abs::Button
    {
        public:
        OpenGL_Button(Abs::ButtonProps btnInfo, Abs::ClickEventCallback btnCallback);
        void OnClick(dVec2 mouPos, int mouCode);

        private:
        // first figure out how to bind this with the target or render window...
        // FreetypeText m_label;
        static bool withinBoundary(fVec4 border, fVec2 pos);
    };

    class OpenGL_InpField : public Abs::InputField
    {
        public:
        OpenGL_InpField(Abs::InputFieldProps inpFieldInfo, Abs::ClickEventCallback inpFieldCallback);

        // inline String GetText() {  return m_text.m_text;  }

        private:
        // FreetypeText m_text;
    };
}