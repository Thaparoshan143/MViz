#pragma once

#include"../../Core/Base/Types.h"
#include"../../Core/Base/BaseUI.h"
#include"./OpenGL_Buff.h"
#include"./OpenGL_Sha.h"
#include"./OpenGL_Win.h"
#include"./OpenGL_Graph.h"
#include"./OpenGL_Text.h"

#define BTN_FONT_SIZE 0.7
#define BTN_LABEL_OFFSET 0.05

#define FIELD_FONT_SIZE 0.6
#define FIELD_LABEL_OFFSET 0.016

#define BTN_TRI_COUNT 6
#define INPFIELD_TRI_COUNT 6

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
        inline String GetLabel() { return m_label; }
        inline String* GetRawLabel() { return &this->m_label; }

        private:
        String m_label;
    };

    class OpenGL_InpField : public Abs::InputField
    {
        public:
        OpenGL_InpField(Abs::InputFieldProps inpFieldInfo, ClickEventCallback inpFieldCallback);

        // Will return true if is in active state
        bool OnClick(dVec2 mouPos, int mouCode);
        bool IsActive();
        // String GetKeyboardInput(String text);
        inline String GetText() { return this->m_text;}
        inline String* GetRawText() { return &this->m_text;}

        private:
        String m_text;
    };

    class OpenGL_UI
    {
        public:
        OpenGL_UI(OpenGL_Win &target, UIProps UIInfo);

        // Callback yet to be attached to the Button Props... later on, remove first argument and only pass button props when adding new button...
        void AddElement(Abs::ButtonProps btnInfo, ClickEventCallback btnCallback);
        void AddElement(Abs::InputFieldProps inpFieldInfo, ClickEventCallback fieldCallback);
        void RenderUI();
        void DispatchMouseEvents(dVec2 mouRef, int mouCode);
        // void DispatchKeyboardEvent(int keyCode);

        private:
        std::vector<OpenGL_Button*> m_btnList;
        std::vector<OpenGL_InpField*> m_inpFieldList;
        std::vector<FreetypeText*> m_btnLabelList;
        std::vector<FreetypeText*> m_inpFieldLabelList;
        // EventQueue<dVec2, int> m_mouseEventQueue;
        OpenGL_VertArrObj m_UIVAO;
        // Better option might be using map system, like for btn, input field and so on... we can use mapping for individual VBO...
        OpenGL_VertBuffObj m_UIVBO;
        uint m_UIShaderID;
        uint m_textShaderID;
        OpenGL_Win &m_target;
        uint m_triangleCount;
        bool m_isSubscriberActive;

        void initializeUIBuffer();
        float* getQuadVertices(fVec2 pos, fVec2 dim, fVec3 col);
        void renderBtnText();
        void renderInpFieldText();
        void updateTriangleCount();
    };
}