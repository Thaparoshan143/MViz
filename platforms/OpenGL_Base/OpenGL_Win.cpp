#include"OpenGL_Win.h"

namespace OpenGL
{
	OpenGL_Win::OpenGL_Win()
	{
		this->m_wi = WindowInfo(800, 600, "OpenGL Window");
		initializeOpenGLWindow(800, 600, "OpenGL Window");
	}

	OpenGL_Win::OpenGL_Win(WindowInfo &wi)
	{
		this->m_wi = wi;
		initializeOpenGLWindow(wi.width, wi.height, wi.title);
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
		std::cout << "I am OpenGL Window !!";
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
		glfwSetWindowUserPointer(this->m_window, this);

		// Registering all the callbacks for mouse and keyboard (static method inside OpenGL_Inp)
		glfwSetMouseButtonCallback(this->m_window, static_mouse_button_callback);
		glfwSetCursorPosCallback(this->m_window, static_mouse_position_callback);
		glfwSetScrollCallback(this->m_window, static_mouse_scroll_callback);
		glfwSetKeyCallback(this->m_window, static_key_callback);

		glfwSetFramebufferSizeCallback(this->m_window, static_framesize_callback);
	}


	// All the static methods for input definition 
	static void static_mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
    {
        if(action == GLFW_PRESS)
        {
            Abs::MouseButtonPressedEvent mbpressed(Abs::MouseCode(button));
			#if DEBUG_LOG
            std::cout << "Mouse button pressed!!\n";
			#endif
        }
        else if(action == GLFW_RELEASE)
        {
            Abs::MouseButtonReleasedEvent mbreleased(Abs::MouseCode(button));
			#if DEBUG_LOG
            std::cout << "Mouse button released!!\n";
			#endif
        }
    }

	static void static_mouse_scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
	{
		#if DEBUG_LOG
		std::cout << "Mouse scrolled : " << std::endl;
		std::cout << "XOffset : " << xoffset << "\nYOffset : " << yoffset << std::endl;
		#endif
	}

	static void static_mouse_position_callback(GLFWwindow *window, double xpos, double ypos)
	{
		#if DEBUG_LOG
		std::cout << "Mouse moved : " << std::endl;
		std::cout << "X : " << xpos << "\nY : " << ypos << std::endl;
		#endif
	}

	static void static_key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
	{
		if(action == GLFW_PRESS)
		{
			Abs::KeyButtonPressedEvent kbpressed(key);
			#if DEBUG_LOG
			std::cout << "Key pressed!! - " << char(key) << std::endl;
			#endif
		}
		else if(action == GLFW_RELEASE)
		{
			Abs::KeyButtonReleasedEvent kbreleased(key);
			#if DEBUG_LOG
			std::cout << "Key released!! - " << char(key) << std::endl;
			#endif
		}
	}

	static void static_framesize_callback(GLFWwindow *window, int width, int height)
	{
		OpenGL_Win *win = (OpenGL_Win*)glfwGetWindowUserPointer(window);

		// for the initialize window the provided size is different that the size later provided by callback so required adjustment..
		// Screen size has to be halfed for proper functining, once take a look why? for now leave it..
		win->m_wi.width = width/2;
		win->m_wi.height = height/2;
	}
}