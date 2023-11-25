#pragma once

#include"../../Core/Base/Application.h"

#include"./OpenGL_Win.h"
#include"./OpenGL_UI.h"

#define TESTING_MODE
#include"../../Core/Base/VertGenerator.hpp"

// using same info mode for both, contains width, height and the title of window
typedef WindowInfo ApplicationInfo;

namespace OpenGL
{
	class OpenGL_App : public Abs::Application
	{
		public:
		OpenGL_App(ApplicationInfo &appInfo);
		~OpenGL_App();

		void UpdateTarget(OpenGL_Win *targetWindow);
		void UpdateTargetUI(OpenGL_UI *targetUI);
		void* GetReference(Abs::AppRef appRef);
		uint GetShaderID(String path) {	return m_targetWindow->GetShaderID(path);	}
		OpenGL_Sha* GetRawShader(String path) {	return m_targetWindow->GetRawShader(path);	}
		inline ApplicationInfo GetAppInfo();

		public:
		OpenGL_Win *m_targetWindow;
		OpenGL_UI *m_targetUI;

		// might not be necessary once actual application is made out for the application based working...
		void initializeGLEnable();
	};

}