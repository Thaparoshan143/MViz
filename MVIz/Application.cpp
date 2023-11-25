#include"../platforms/OpenGL_Base/OpenGL_App.h"
#include"./MVizUI.cpp"
#include"./Math/Calculator/calculator.cpp"

#define DEFAULT_SCR_WIDTH 800
#define DEFAULT_SCR_HEIGHT 600

// This is just temporary 
#define FREQ_COUNT 5
// it is the total no of vertex count in single sine wave #note: hgher the number more better the curve
#define SINE_RES 20
#define SINE_AMP_Y 0.6


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

    std::vector<float> wave_temp = Calculate("sin(x)", -10, 10, 0.015625, 10, true);

    // float *sineVert = Util::_get_sine_ver2(FREQ_COUNT, SINE_RES, SINE_AMP_Y);
    float *waveVert = &wave_temp[0];
    int vertSize = wave_temp.size();
    // uint wave_VAO;
    OpenGL_VertArrObj wave_VAO;
    OpenGL_VertBuffObj wave_VBO;
    wave_VBO.DirectLoad(waveVert, vertSize);
    wave_VAO.EnableVertexAttribMan(2);
    m_targetUI->InitializeUI();

    OpenGL_Sha sh("../res/Shaders/Graph/Wave/");
    sh.UseProgram();
    sh.SetUniformVec3("fColor", glm::fvec3(1, 0.5, 0.2));

    float i = 0.0f;
    float d_i = 0.005f;

    Mat4 temp;

    // Main Loop starts in while block..
    while(!m_targetWindow->ShouldCloseWindow())
    {
        m_targetWindow->SetColor(MAIN_BG, MAIN_BG, MAIN_BG, 1.0f);

        wave_VAO.Bind();
        sh.UseProgram();
        
        i += d_i;
        if (i > 1) {
            d_i = -d_i;
        }
        if (i < -1) {       
            d_i = -d_i;
        }

        // temp = glm::translate(fMat4(1.0), glm::fvec3(-1.0+i, 0, 0));
        // temp = glm::scale(fMat4(), glm::fvec3(1, i, 0));
        temp = glm::mat4(1.0);
        sh.SetUniformMat4("modal", temp);

        glLineWidth(5.0f);
        glDrawArrays(GL_LINE_STRIP_ADJACENCY, 0, vertSize / 2);

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