// Macro to solve the conflict of double including of vertgenerator.hpp file (that is just for generating random vertx to draw now in testing..)
#define VERTGENERATOR_HPP

#include"OpenGL_App.h"

namespace OpenGL
{
	OpenGL_App::OpenGL_App()
	{
		ApplicationInfo appInfo(500, 500, "Sandbox Application");
		initializeApp(appInfo);
	}

	OpenGL_App::OpenGL_App(ApplicationInfo &appInfo) 
	{
		initializeApp(appInfo);
	}

	OpenGL_App::~OpenGL_App()
	{
		// free all the heap allocated block for this
		delete[] this->m_mainWindow;
	}

	ApplicationInfo OpenGL_App::GetAppInfo()
	{
		return m_appInfo;
	}

	void OpenGL_App::initializeApp(ApplicationInfo &appInfo)
	{
		this->m_appInfo = appInfo;
		this->m_mainWindow = new OpenGL_Win(m_appInfo.width, m_appInfo.height, m_appInfo.name);
	}

	void OpenGL_App::Initialize()
	{
		glEnable(GL_BLEND);
		glEnable(GL_BACK);
		glEnable(GL_LINE_SMOOTH);

	}

	void OpenGL_App::Loop()
	{

	}
}