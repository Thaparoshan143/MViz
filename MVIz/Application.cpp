#include"../platforms/OpenGL_Base/OpenGL_App.h"
#include"./MVizUI.cpp"

#define DEFAULT_SCR_WIDTH 800
#define DEFAULT_SCR_HEIGHT 600

// to define wether to have black (0) or white (1) background
#define MAIN_BG 1

int GetIntFromCharPtr(const char *c)
{
	if(c==nullptr)
	{
		return 0;
	}

    int temp = 0;
    int ind = 0;

    while(*(c+ind)!='\0')
    {   
        temp += *(c+ind) - 48;
        temp *= 10;
        ind++;
    }

    return temp/10;
}

using AppInfo = ApplicationInfo;

using namespace OpenGL;

class MVizApp : protected OpenGL::OpenGL_App
{
    public:
    // Note: Do not use default constructor unless it is extremly necessary, pass proper appinfo
    MVizApp(AppInfo &appInfo);
    ~MVizApp();

    void Initialize() override;
    void Loop() override;
};

MVizApp::MVizApp(AppInfo &AppInfo) : OpenGL_App(AppInfo)
{
    std::cout << "MViz Application Created!!" << std::endl;
}

MVizApp::~MVizApp()
{

}

void MVizApp::Initialize()
{
    MVizUI *mainUI = new MVizUI(m_targetWindow);
    m_targetUI = mainUI;
}

void MVizApp::Loop()
{
    if(m_targetUI==nullptr)
    {
        std::cout << "Target UI not found.. please update first" << std::endl;
        return;
    }
    std::cout << "Application Successfully created!!" << std::endl;

    m_targetUI->InitializeUI();

    // Main Loop starts in while block..
    while(!m_targetWindow->ShouldCloseWindow())
    {
        m_targetWindow->SetColor(MAIN_BG, MAIN_BG, MAIN_BG, 1.0f);

        m_targetUI->Render();
        m_targetWindow->SwapFrameBuffer();
        glfwPollEvents();        
    }
}


// This is the entry point of the MViz Application... starting from here
int main(int argc, char *args[])
{
    int screenWidth = (argc!=1 && GetIntFromCharPtr(args[1])) ? GetIntFromCharPtr(args[1]) : DEFAULT_SCR_WIDTH;
    int screenHeight = (argc!=1 && GetIntFromCharPtr(args[2])) ? GetIntFromCharPtr(args[2]) : DEFAULT_SCR_HEIGHT;
    String appName = (argc!=1 && String(args[3]) != "") ? String(args[3]) : String("MViz");

    AppInfo MVizAppInfo(screenWidth, screenHeight, appName);
    
    MVizApp *mainApplication = new MVizApp(MVizAppInfo);

    if(mainApplication!=nullptr)
    {
        mainApplication->Initialize();
        mainApplication->Loop();
    }
    else
    {
        std::cout << "Failed to create Application. Try Again!!";
    }

    return 0;
}