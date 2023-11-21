// Macro to solve the conflict of double including of vertgenerator.hpp file (that is just for generating random vertx to draw now in testing..)
#define VERTGENERATOR_HPP

#include"OpenGL_App.h"

namespace OpenGL
{
	OpenGL_App::OpenGL_App(ApplicationInfo &appInfo) 
	{
		this->m_mainWindow = new OpenGL_Win(appInfo, this);
		this->m_mainWindow->m_wi = appInfo;
		UIProps UIInfo;
		this->m_mainUI = new OpenGL_UI(*this->m_mainWindow, UIInfo);
		initializeGLEnable();
	}

	OpenGL_App::~OpenGL_App()
	{
		// free all the heap allocated block for this
		delete[] this->m_mainWindow;
		delete[] this->m_mainUI;
	}

	void* OpenGL_App::GetReference(Abs::AppRef appRef)
	{
		if(appRef==Abs::AppRef::SELF)
		{
			return (OpenGL_App*)this;
		}
		else if(appRef==Abs::AppRef::WINDOW)
		{
			return (OpenGL_Win*)this->m_mainWindow;
		}
		else if(appRef==Abs::AppRef::UI)
		{
			return (OpenGL_UI*)this->m_mainUI;
		}
		else
		{
			std::cout << "Error while passing references..." << std::endl;
			return nullptr;
		}
	}

	ApplicationInfo OpenGL_App::GetAppInfo()
	{
		return m_mainWindow->GetWindowInfo();
	}

	void OpenGL_App::initializeGLEnable()
	{
		glEnable(GL_BLEND);
		// glEnable(GL_BACK);
		glEnable(GL_LINE_SMOOTH); 
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
}