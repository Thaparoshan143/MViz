#include"../platforms/OpenGL_Base/OpenGL_UI.h"
#include"../platforms/OpenGL_Base/OpenGL_Graph.h"

// Since we will be using openGL platform so all are adjusted and hard coded accordingly..

using _ButtonProps = Abs::ButtonProps;
using _PanelProps = Abs::PanelProps;
using _InputFieldProps = Abs::InputFieldProps;

// temporary for now..
using MvPanel = OpenGL::OpenGL_Panel;
using MvButton = OpenGL::OpenGL_Button;
using MvInputField = OpenGL::OpenGL_InpField;

class MVizUI : public OpenGL::OpenGL_UI
{
    public:
    MVizUI(OpenGL::OpenGL_Win *target): OpenGL_UI(target) 
    {
        // Initialzing the graph..
        Abs::GraphInfo graphInfo("Graph", fVec2(800, 600), Abs::ScreenPosition::TOP_RIGHT, Abs::NumberingScale::NORMAL);
        m_graph = new OpenGL::OpenGL_Graph(*((OpenGL::OpenGL_Win*)m_targetWindow), graphInfo);
    }

    void initializeUIPaint()
    {
        MvPanel *sidePanel = GetNewPanel(fVec2(-0.7, 0), fVec2(0.6, 2), Color(0.8), "Input Panel", nullptr);
        MvPanel *bottomPanel = GetNewPanel(fVec2(0, -0.8), fVec2(2, 0.4), Color(0.2), "Next graph", nullptr);

        AttachPanel("Input Panel", sidePanel);
        AttachPanel("Bottom Panel", bottomPanel);

        m_isActive = true;
    }

    // All the UI that is required in MViz will be pushed from here..
    void InitializeUI() override
    {
        initializeUIPaint();

        OpenGL_UI::InitializeUI();
    }

    ~MVizUI()
    {
        delete[] m_graph;
    }

    void Render()
    {
        m_graph->RenderGraph();
        OpenGL_UI::Render();
    }

    void DispatchMouseEvents(dVec2 mouPos, int mouCode) override
    {
        OpenGL_UI::DispatchMouseEvents(mouPos, mouCode);
    }

    // The following are just wrappers to facilitate the fast creation of UI elements..
    MvPanel* GetNewPanel(_PanelProps panelProps)
    {
        MvPanel *_newPanel = new MvPanel(panelProps);
        return _newPanel;
    }

    MvPanel* GetNewPanel(fVec2 pos, fVec2 dim, Color bgCol, String title, ClickEventCallback cEvent)
    {
        _PanelProps newPanel(pos, dim, bgCol, title, cEvent);
        return GetNewPanel(newPanel);
    }
    
    MvButton* GetNewButton(_ButtonProps btnProps)
    {
        MvButton *_newBtn = new MvButton(btnProps);
        return _newBtn;
    }

    MvButton* GetNewButton(fVec2 pos, fVec2 dim, Color bgCol, String label, ClickEventCallback cEvent)
    {
        _ButtonProps newBtn(pos, dim, bgCol, label, cEvent);
        return GetNewButton(newBtn);
    }
    
    MvInputField* GetNewInputField(_InputFieldProps inpFieldProps)
    {
        MvInputField *_newInpField = new MvInputField(inpFieldProps);
        return _newInpField;
    }

    MvInputField* GetNewInputField(fVec2 pos, fVec2 dim, Color bgCol, String placeholder, ClickEventCallback cEvent, ClickEventCallback changeEvent, String text)
    {
        _InputFieldProps newInpField(pos, dim, bgCol, placeholder, cEvent, changeEvent, text);
        return GetNewInputField(newInpField);
    }

    private:
    OpenGL::OpenGL_Graph *m_graph;
};