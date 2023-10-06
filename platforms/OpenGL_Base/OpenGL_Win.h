#pragma once

#include"../../includes/GLAD/glad.h"
#include"../../includes/GLFW/glfw3.h"

#include"../../Core/Base/Window.h"


namespace Sandbox
{
	class OpenGL_Win : private Abs::Window
	{
		public:
		OpenGL_Win();
		OpenGL_Win(int w, int h, String t);

		~OpenGL_Win();
		
		inline GLFWwindow* GetWindow() {	return m_window;	}
		void SetActive() override;
		void SetColor(float r, float g, float b, float a = 1.0) override;
		inline bool ShouldCloseWindow() override {	return glfwWindowShouldClose(this->m_window);	};
		void SwapFrameBuffer() override;

		private:
		GLFWwindow *m_window;

		void initializeOpenGLWindow(int w, int h, String t);
	};
}