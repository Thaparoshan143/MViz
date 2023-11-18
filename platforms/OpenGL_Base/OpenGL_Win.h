#pragma once

#include"../../includes/GLAD/glad.h"
#include"../../includes/GLFW/glfw3.h"

#include"../../Core/Base/Window.h"
#include"../../Core/Base/Application.h"
#include"./OpenGL_Inp.h"

namespace OpenGL
{
	class OpenGL_Win : public Abs::Window
	{
		public:
		OpenGL_Win(WindowInfo &wi, Abs::Application *targetApp);

		~OpenGL_Win();
		
		inline GLFWwindow* GetWindow() {	return m_window;	}
		void SetActive() override;
		void SetColor(float r, float g, float b, float a = 1.0) override;
		inline bool ShouldCloseWindow() override {	return glfwWindowShouldClose(this->m_window);	};
		void SwapFrameBuffer() override;

		EventQueue<dVec2, int> m_mouEventQueue;
		GLFWwindow *m_window;
		Abs::Application *m_targetApp;
		
		void initializeOpenGLWindow(int w, int h, String t);
	};

    // All the input handling function will be static as we need to query all the poll event continuously for entire application life time
    static void static_mouse_button_callback(GLFWwindow *window, int button, int action, int mods);
	static void static_mouse_scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
	static void static_mouse_position_callback(GLFWwindow *window, double xpos, double ypos);
	static void static_key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);

	static void static_framesize_callback(GLFWwindow* window, int width, int height);
}

