#pragma once

#include <vector>

#include"../../Core/Base/Types.h"
#include"../../Core/Base/BaseUI.h"
#include"./OpenGL_Buff.h"
#include"./OpenGL_Win.h"
#include"./OpenGL_Text.h"


#define BTN_FONT_SIZE 0.7
#define BTN_LABEL_OFFSET 0.05

#define FIELD_FONT_SIZE 0.6
#define FIELD_LABEL_OFFSET 0.016

#define QUAD_TRI_COUNT 6
#define BTN_TRI_COUNT 6
#define INPFIELD_TRI_COUNT 6

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
        OpenGL_Button(Abs::ButtonProps btnInfo);
        
    };

    class OpenGL_InpField : public Abs::InputField
    {
        public:
        OpenGL_InpField(Abs::InputFieldProps inpFieldInfo);

        // Will return true if is in active state
        bool IsActive();
    };

    class OpenGL_UI : public Abs::UIManager
    {
        public:
        OpenGL_UI(OpenGL_Win *target);

        // Callback yet to be attached to the Button Props... later on, remove first argument and only pass button props when adding new button...

        void AttachPanel(String id, Abs::Panel *newPan) override  {   UIManager::AttachPanel(id, newPan); updateBuffer(id); }
        void DispatchMouseEvents(dVec2 mouPos, int mouCode) override; 
        void Render() override;
        // void DispatchKeyboardEvent(int keyCode);

        private:
        // Later migrate to the renderer
        OpenGL_VertArrObj m_UIVAO;
        // Better option might be using map system, like for btn, input field and so on... we can use mapping for individual VBO...
        OpenGL_VertBuffObj m_UIVBO;
        uint m_UIShaderID;
        uint m_textShaderID;
        uint m_triangleCount;
        std::map<FreetypeText*, fVec2> m_textList;

        dVec2 normalizeMouPos(dVec2 mouPos);
        void getVBOFromMap(String id);
        void panelRecursiveVBO(Abs::Panel *pan);
        void updateBuffer(String id);
        void initializeUIBuffer();
        float* getQuadVertices(fVec2 pos, fVec2 dim, fVec3 col);
        void updateTriangleCount();
        void renderText();
        void renderQuad();
    };
}