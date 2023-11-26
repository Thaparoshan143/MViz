#pragma once

#include <vector>

#include"../../Core/Base/Types.h"
#include"../../Core/Base/BaseUI.h"
#include"./OpenGL_Buff.h"
#include"./OpenGL_Win.h"
#include"./OpenGL_Text.h"

#define QUAD_TRI_COUNT 6

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
        ~OpenGL_UI() {}
        // Callback yet to be attached to the Button Props... later on, remove first argument and only pass button props when adding new button...

        virtual void InitializeUI();
        void AttachPanel(String id, Abs::Panel *newPan) override  {   UIManager::AttachPanel(id, newPan); updateBuffer(id); }
        void DispatchMouseEvents(dVec2 mouPos, int mouCode) override; 
        void Render() override;
        
        uint m_startingCount;

        protected:
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
        float* getQuadVertices(fVec2 pos, fVec2 dim, fVec3 col);
        void updateTriangleCount();
        void renderText();
        void renderQuad();
    };
}