#pragma once

#include"../../Core/Base/Application.h"

#include"./OpenGL_Win.h"
#include"./OpenGL_Graph.h"
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
		OpenGL_App();
		OpenGL_App(ApplicationInfo &appInfo);

		~OpenGL_App();

		// might not be necessary once actual application is made out for the application based working...
		void InitializeOpenGL();

		inline ApplicationInfo GetAppInfo();

		public:
		OpenGL_Win *m_mainWindow;

		// helper function for initalizing application class
		void initializeApp(ApplicationInfo &appInfo);
	};

}