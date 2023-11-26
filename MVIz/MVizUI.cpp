#include"../platforms/OpenGL_Base/OpenGL_UI.h"
#include"../platforms/OpenGL_Base/OpenGL_Graph.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include"../includes/stb/stb_image_write.h"

#include"./MVizGraph.cpp"

// Since we will be using openGL platform so all are adjusted and hard coded accordingly..

using _ButtonProps = Abs::ButtonProps;
using _PanelProps = Abs::PanelProps;
using _InputFieldProps = Abs::InputFieldProps;

// temporary for now..
using MvPanel = OpenGL::OpenGL_Panel;
using MvButton = OpenGL::OpenGL_Button;
using MvInputField = OpenGL::OpenGL_InpField;

static int zoom_level = 10;
static bool showSidePanel = true;

// quad is made up of 6 vertices i.e two triangle so multiplied by 6
#define QUAD_PP_RGB_VBO_COUNT 6
#define SIDE_ELEMENT_COUNT 5
#define SIDE_PANEL_OFFSET QUAD_PP_RGB_VBO_COUNT*SIDE_ELEMENT_COUNT

static void static_submit_expression();
static void static_clear_expression();
static void static_toggle_btn();
static void static_zoom_in();
static void static_zoom_out();
static void static_expand_inputField();
static void static_save_image();

class MVizUI : public OpenGL::OpenGL_UI
{
    public:
    MVizUI(OpenGL::OpenGL_Win *target): OpenGL_UI(target) 
    {
        // Initialzing the graph..
        Abs::GraphInfo graphInfo("Graph", fVec2(800, 600), Abs::ScreenPosition::TOP_RIGHT, Abs::NumberingScale::NORMAL);
        m_graph = new MVizGraph(*((OpenGL::OpenGL_Win*)m_targetWindow), graphInfo);
    }

    void initializeUIPaint()
    {
        MvPanel *sidePanel = GetNewPanel(fVec2(-0.6, 0), fVec2(0.8, 2), Color(0.4), "Input Panel", nullptr);
        // MvPanel *bottomPanel = GetNewPanel(fVec2(0, -0.8), fVec2(2, 0.4), Color(0.2), "Next graph", nullptr);
        MvInputField *expField = GetNewInputField(fVec2(-0.6, 0.5), fVec2(0.7, 0.2), Color(0.2), "Expression", nullptr, nullptr);
        MvButton *submitBtn = GetNewButton(fVec2(-0.8, -0.5), fVec2(0.25, 0.15), Color(0.05, 0.8, 0.1), "Submit", static_submit_expression);
        MvButton *clearBtn = GetNewButton(fVec2(-0.4, -0.5), fVec2(0.25, 0.15), Color(0.95, 0.05, 0.05), "Clear", static_clear_expression);
        MvButton *expandSlot = GetNewButton(fVec2(-0.6, -0.7), fVec2(0.7, 0.15), Color(0.2), "Add Slot", static_expand_inputField);
        MvButton *saveImage = GetNewButton(fVec2(-0.6, -0.9), fVec2(0.7, 0.15), Color(0.34, 0.75, 0.98), "Save Image", static_save_image);

        sidePanel->AttachElement(submitBtn);
        sidePanel->AttachElement(clearBtn);
        sidePanel->AttachElement(expField);
        sidePanel->AttachElement(expandSlot);
        sidePanel->AttachElement(saveImage);
        
        MvPanel *toggleWrapper = GetNewPanel(fVec2(-0.95,0.85), fVec2(0.1, 0.12), Color(1), "", nullptr);
        MvButton *toggleBtn = GetNewButton(fVec2(-0.95,0.85), fVec2(0.08, 0.1), Color(0.2), "=", static_toggle_btn);
        toggleWrapper->AttachElement(toggleBtn);

        MvPanel *rightSidePanel = GetNewPanel(fVec2(0.95, 0.8), fVec2(0.08, 0.1), Color(0.8), "", nullptr);
        MvButton *zoomIn = GetNewButton(fVec2(0.95, 0.9), fVec2(0.08, 0.1), Color(0.5), "+", static_zoom_in);
        MvButton *zoomOut = GetNewButton(fVec2(0.95, 0.75), fVec2(0.08, 0.1), Color(0.5), "-", static_zoom_out);
        rightSidePanel->AttachElement(zoomIn);
        rightSidePanel->AttachElement(zoomOut);
        m_UIElementList.push_back(sidePanel);
        // m_UIElementList.push_back(bottomPanel);
        // AttachPanel("Bottom Panel", bottomPanel);
        AttachPanel("Input Panel", sidePanel);
        AttachPanel("Toggle", toggleWrapper);
        AttachPanel("Right Util", rightSidePanel);

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
        delete[] (OpenGL::OpenGL_Win*)m_targetWindow;
        m_UIElementList.clear();
    }

    void Render() override
    {
        m_graph->Render();
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

    MvInputField* GetNewInputField(fVec2 pos, fVec2 dim, Color bgCol, String placeholder, ClickEventCallback cEvent, ClickEventCallback changeEvent, String text="")
    {
        _InputFieldProps newInpField(pos, dim, bgCol, placeholder, cEvent, changeEvent, text);
        return GetNewInputField(newInpField);
    }

    protected:
    OpenGL::OpenGL_Graph *m_graph;
    std::vector<MvPanel*> m_UIElementList;

    friend void static_submit_expression();
    friend void static_toggle_btn();
    friend void static_zoom_in();
    friend void static_zoom_out();
    friend void static_clear_expression();
    friend void static_save_image();
};

// All the static methods for button callback or inputfield callback will reside here..
static void static_submit_expression()
{
    OpenGL::OpenGL_Win *targetWindow = (OpenGL::OpenGL_Win*)glfwGetWindowUserPointer(OpenGL::OpenGL_Win::GetWindow());    
    MVizUI *targetUI = (MVizUI*)targetWindow->m_targetApp->GetReference(Abs::AppRef::UI);
    targetUI->m_graph->SetExpression(targetWindow->m_lastStringScan);
}

static void static_clear_expression()
{
    OpenGL::OpenGL_Win *targetWindow = (OpenGL::OpenGL_Win*)glfwGetWindowUserPointer(OpenGL::OpenGL_Win::GetWindow());    
    if(targetWindow->m_keySubscriber!=nullptr)
    {
        targetWindow->m_keySubscriber->clear();
    }
}

static void static_toggle_btn()
{
    OpenGL::OpenGL_Win *targetWindow = (OpenGL::OpenGL_Win*)glfwGetWindowUserPointer(OpenGL::OpenGL_Win::GetWindow());    
    MVizUI *targetUI = (MVizUI*)targetWindow->m_targetApp->GetReference(Abs::AppRef::UI);
    if(!showSidePanel)
    {
        targetUI->m_startingCount = 0;
    }
    else
    {
        targetUI->m_startingCount = SIDE_PANEL_OFFSET+6;
    }
    showSidePanel = !showSidePanel;
    
    std::cout << "I am here to toggle panel" << std::endl;
}

static void static_zoom_in()
{
    zoom_level--;
    if(zoom_level<1)
    {
        zoom_level = 1;
        std::cout << "Cannot go below the given zoom level" << std::endl;
        return;
    }
    OpenGL::OpenGL_Win *targetWindow = (OpenGL::OpenGL_Win*)glfwGetWindowUserPointer(OpenGL::OpenGL_Win::GetWindow());    
    MVizUI *targetUI = (MVizUI*)targetWindow->m_targetApp->GetReference(Abs::AppRef::UI);
    targetUI->m_graph->SetRange(zoom_level);
    targetUI->m_graph->SetExpression(targetUI->m_graph->GetLastExpression());
    // OpenGL::OpenGL_Sha *tempSha = targetWindow->GetRawShader("../res/Shaders/Graph/Wave/");
    // Mat4 scaleFactor(zoom_level);
    // tempSha->UseProgram();
    // tempSha->SetUniformMat4("modal", scaleFactor);
}

static void static_zoom_out()
{
    zoom_level++;
    if(zoom_level>20)
    {
        zoom_level = 20;
        std::cout << "Cannot go above the given zoom level" << std::endl;
        return;
    }
    OpenGL::OpenGL_Win *targetWindow = (OpenGL::OpenGL_Win*)glfwGetWindowUserPointer(OpenGL::OpenGL_Win::GetWindow());    
    MVizUI *targetUI = (MVizUI*)targetWindow->m_targetApp->GetReference(Abs::AppRef::UI);
    targetUI->m_graph->SetRange(zoom_level);
    targetUI->m_graph->SetExpression(targetUI->m_graph->GetLastExpression());
    // OpenGL::OpenGL_Sha *tempSha = targetWindow->GetRawShader("../res/Shaders/Graph/Wave/");
    // fMat4 scaleFactor(zoom_level);
    // tempSha->UseProgram();
    // tempSha->SetUniformMat4("modal", scaleFactor);
}

static void static_expand_inputField()
{
    std::cout << "To expand the input field" << std::endl;
}

static String getCurrentDateTimeString()
{
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d-%X", &tstruct);

    return buf;
}

static void static_save_image()
{
    static_toggle_btn();
    std::cout << "Saving the image!!" << std::endl;
    String filepath = getCurrentDateTimeString();
    filepath += ".png";
    std::cout << filepath << std::endl;
    int width, height;
    glfwGetFramebufferSize(OpenGL::OpenGL_Win::GetWindow(), &width, &height);
    GLsizei nrChannels = 3;
    GLsizei stride = nrChannels * width;
    stride += (stride % 4) ? (4 - stride % 4) : 0;
    GLsizei bufferSize = stride * height;
    std::vector<char> buffer(bufferSize);
    glPixelStorei(GL_PACK_ALIGNMENT, 4);
    glReadBuffer(GL_FRONT);
    glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, buffer.data());
    stbi_flip_vertically_on_write(true);
    stbi_write_png(filepath.c_str(), width, height, nrChannels, buffer.data(), stride);
}
