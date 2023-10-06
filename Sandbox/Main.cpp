#include <iostream>

#include"../platforms/OpenGL_Base/OpenGL_App.h"

using namespace Sandbox;

// #define SCR_WIDTH 800
// #define SCR_HEIGHT 600

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

int main(int argc, char *arg[])
{
	int screenWidth = (GetIntFromCharPtr(arg[1]) && argc!=1) ? GetIntFromCharPtr(arg[1]) : 800;
	int screenHeight = (GetIntFromCharPtr(arg[2]) && argc!=1) ? GetIntFromCharPtr(arg[2]) : 600;
	String appName = (String(arg[3]) != "" && argc!=1) ? String(arg[3]): String("Default");

	std::cout << "==> Application Info <==" << std::endl;
	std::cout << "Screen Width : " << screenWidth << std::endl;
	std::cout << "Screen Height : " << screenHeight << std::endl;
	std::cout << "App Name : " << appName << std::endl;

	// ApplicationInfo sandboxInfo(SCR_WIDTH, SCR_HEIGHT, "Sandbox APP Yo");
	ApplicationInfo appInfo(screenWidth, screenHeight, appName);
	OpenGL_App *mainApplication = new OpenGL_App(appInfo);

	mainApplication->Initialize();
	mainApplication->Loop();

	return 0;
}