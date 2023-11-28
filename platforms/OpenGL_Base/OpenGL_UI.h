#pragma once

#include <vector>

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
    };

    class OpenGL_UI : public Abs::UIManager
    {
        public:
        OpenGL_UI(OpenGL_Win *target);
        ~OpenGL_UI() {}

        virtual void InitializeUI();
        void AttachPanel(String id, Abs::Panel *newPan) override  {   UIManager::AttachPanel(id, newPan); updateBuffer(id); }
        void DispatchMouseEvents(dVec2 mouPos, int mouCode) override; 
        void Render() override;
        
        uint m_startingCount;

        protected:
        OpenGL_VertArrObj m_UIVAO;
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