// Macro to solve the conflict of double including of vertgenerator.hpp file (that is just for generating random vertx to draw now in testing..)
#define VERTGENERATOR_HPP

#include"OpenGL_App.h"

namespace OpenGL
{
	OpenGL_App::OpenGL_App(ApplicationInfo &appInfo) 
	{
		std::cout << "OpenGL Application created!" << std::endl;
		this->m_targetWindow = new OpenGL_Win(appInfo, this);
		this->m_targetWindow->m_winInfo = appInfo;
		m_targetUI = nullptr;
		initializeGLEnable();
	}

	OpenGL_App::~OpenGL_App()
	{
		// free all the heap allocated block for this
		delete[] this->m_targetWindow;
		delete[] this->m_targetUI;
	}

	void OpenGL_App::UpdateTarget(OpenGL_Win *targetWindow)
	{
		m_targetWindow = targetWindow;
		m_targetWindow->m_winInfo = targetWindow->m_winInfo;
	}

	void OpenGL_App::UpdateTargetUI(OpenGL_UI *targetUI)
	{
		m_targetUI = targetUI;
	}

	void* OpenGL_App::GetReference(Abs::AppRef appRef)
	{
		if(appRef==Abs::AppRef::SELF)
		{
			return (OpenGL_App*)this;
		}
		else if(appRef==Abs::AppRef::WINDOW)
		{
			return (OpenGL_Win*)this->m_targetWindow;
		}
		else if(appRef==Abs::AppRef::UI)
		{
			return (OpenGL_UI*)this->m_targetUI;
		}
		else
		{
			std::cout << "Error while passing references..." << std::endl;
			return nullptr;
		}
	}

	ApplicationInfo OpenGL_App::GetAppInfo()
	{
		return m_targetWindow->GetWindowInfo();
	}

	void OpenGL_App::initializeGLEnable()
	{
		glEnable(GL_BLEND);
		// glEnable(GL_BACK);
		glEnable(GL_LINE_SMOOTH); 
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
}