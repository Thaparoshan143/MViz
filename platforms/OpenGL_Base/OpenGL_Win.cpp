#include"OpenGL_Win.h"

namespace OpenGL
{
	OpenGL_Win::OpenGL_Win()
	{
		initializeOpenGLWindow(500, 500, "Opengl Window");
	}

	OpenGL_Win::OpenGL_Win(int w, int h, String t)
	{
		initializeOpenGLWindow(w, h, t);
	}

	OpenGL_Win::~OpenGL_Win()
	{
		glfwTerminate();
	}

	void OpenGL_Win::SetActive()
	{
		glfwMakeContextCurrent(this->m_window);
	}

	void OpenGL_Win::SetColor(float r, float g, float b, float a)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(r, g, b, a);
	}

	void OpenGL_Win::SwapFrameBuffer()
	{
		glfwSwapBuffers(this->m_window);
	}


	void OpenGL_Win::initializeOpenGLWindow(int w, int h, String t)
	{
		// loading basic glfw library and more
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		#ifdef __APPLE__
			glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		#endif
		if(!glfwInit())
		{
			exit(-1);
		}

		this->m_window = glfwCreateWindow(w, h, t.c_str(), NULL, NULL);
		this->SetActive();

		// loader glad check if everything is loaded for use 
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to initialize GLAD" << std::endl;
			exit(-2);
		}

		// Setting user pointer is left to do properly
		// glfwSetWindowUserPointer(this->m_window, this);
	}
}