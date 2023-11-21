#include"../platforms/OpenGL_Base/OpenGL_App.h"


#define DEFAULT_SCR_WIDTH 1920
#define DEFAULT_SCR_HEIGHT 1080

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

    private:
    OpenGL_Graph *m_graph;
};

MVizApp::MVizApp(AppInfo &AppInfo) : OpenGL_App(AppInfo)
{
    Abs::GraphInfo graphInfo("Graph", m_mainWindow->GetWindowSize(), Abs::ScreenPosition::TOP_RIGHT, Abs::NumberingInfo::NORMAL);
    m_graph = new OpenGL_Graph(*m_mainWindow, graphInfo);
}

MVizApp::~MVizApp()
{
    delete[] m_graph;
}

void MVizApp::Initialize()
{

}

void MVizApp::Loop()
{
    // This is just temporary 
    #define FREQ_COUNT 5
    // it is the total no of vertex count in single sine wave #note: hgher the number more better the curve
    #define SINE_RES 20
    #define SINE_AMP_Y 0.6

    float *sineVert = Util::_get_sine_ver2(FREQ_COUNT, SINE_RES, SINE_AMP_Y);

    // uint sine_VAO;
    OpenGL_VertArrObj sine_VAO;
    OpenGL_VertBuffObj sine_VBO;
    sine_VBO.DirectLoad(sineVert, SINE_RES*(FREQ_COUNT*2+2));
    sine_VAO.EnableVertexAttribMan(2);

    OpenGL_Sha *sineSha = m_mainWindow->GetRawShader("../res/Shaders/Graph/Wave/");
    sineSha->UseProgram();
    fMat4 temp;
    temp = glm::translate(fMat4(1.0), glm::fvec3(-1.0, 0, 0)) * glm::scale(fMat4(), glm::fvec3(2.0, 1.0, 1.0));
    sineSha->SetUniformMat4("modal", temp);
    sineSha->SetUniformVec3("fColor", glm::fvec3(1, 0.5, 0.2));

    float i = 0.0f;
    float d_i = 0.005f;

    // Main Loop starts in while block..
    while(!m_mainWindow->ShouldCloseWindow())
    {
        m_mainWindow->SetColor(MAIN_BG, MAIN_BG, MAIN_BG, 1.0f);
        m_graph->RenderGraph();

        sine_VAO.Bind();
        sineSha->UseProgram();
        i += d_i;
        if (i > 1) {
            d_i = -d_i;
        }
        if (i < -1) {       
            d_i = -d_i;
        }

        temp = glm::translate(fMat4(1.0), glm::fvec3(-1.0+i, 0, 0));
        temp = glm::scale(fMat4(), glm::fvec3(1, i, 0));
        sineSha->SetUniformMat4("modal", temp);

        glLineWidth(1.0f);
        glDrawArrays(GL_LINE_STRIP_ADJACENCY, 0, SINE_RES*(FREQ_COUNT*2+2));

        m_mainUI->RenderUI();
        m_mainWindow->SwapFrameBuffer();
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