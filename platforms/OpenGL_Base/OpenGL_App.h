#pragma once

#include"../../Core/Base/Application.h"

#include"./OpenGL_Win.h"
#include"./OpenGL_Sha.h"
#include"./OpenGL_VertBuff.h"

namespace Sandbox
{
	struct ApplicationInfo
	{
		int width, height;
		String name;

		ApplicationInfo() {}
		ApplicationInfo(int w, int h, String n): width(w), height(h), name(n) {}	

		ApplicationInfo operator=(const ApplicationInfo &appInfo)
		{
			this->width = appInfo.width;
			this->height = appInfo.height;
			this->name = appInfo.name;

			return *this;
		}	
	};

	class OpenGL_App : private Abs::Application
	{
		public:
		OpenGL_App();
		OpenGL_App(ApplicationInfo &appInfo);

		~OpenGL_App();

		// might not be necessary once actual application is made out for the application based working...
		void Initialize() override;
		void Loop() override;

		inline ApplicationInfo GetAppInfo();

		private:
		OpenGL_Win *m_mainWindow;
		ApplicationInfo m_appInfo;

		// helper function for initalizing application class
		void initializeApp(ApplicationInfo &appInfo);
	};

}