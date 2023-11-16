#pragma once

#include"../../Core/Base/Types.h"
#include"../../Core/Base/BaseUI.h"
#include"./OpenGL_Buff.h"
#include"./OpenGL_Sha.h"
#include"./OpenGL_Win.h"
// Include once firgured out how the target is binded...
// #include"./OpenGL_Text.h"

namespace OpenGL
{
    class OpenGL_UI;
    struct UIProps
    {

    };

    class OpenGL_Panel : public Abs::Panel 
    {
        public:
        OpenGL_Panel(Abs::PanelProps panelInfo);

        private:
    };

    class OpenGL_Button : public Abs::Button
    {
        public:
        OpenGL_Button(Abs::ButtonProps btnInfo, ClickEventCallback btnCallback);
        void OnClick(dVec2 mouPos, int mouCode);

        private:
        // first figure out how to bind this with the target or render window...
        // FreetypeText m_label;
        static bool withinBoundary(fVec4 border, fVec2 pos);
        OpenGL_Button* GetSelf() { return this; }
        friend OpenGL_UI;
    };

    class OpenGL_InpField : public Abs::InputField
    {
        public:
        OpenGL_InpField(Abs::InputFieldProps inpFieldInfo, ClickEventCallback inpFieldCallback);

        // inline String GetText() {  return m_text.m_text;  }

        private:
        // FreetypeText m_text;
    };

    class OpenGL_UI
    {
        public:
        OpenGL_UI(OpenGL_Win &target, UIProps UIInfo);

        // Callback yet to be attached to the Button Props... later on, remove first argument and only pass button props when adding new button...
        void AddElement(OpenGL_Button btn, Abs::ButtonProps);

        private:
        std::vector<OpenGL_Button*> m_btnList;
        OpenGL_VertArrObj m_UIVAO;
        // Better option might be using map system, like for btn, input field and so on... we can use mapping for individual VBO...
        OpenGL_VertBuffObj m_UIVBO;
        OpenGL_Sha m_UIShader;
        OpenGL_Win &target;
    };
}